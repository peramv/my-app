//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  VmConnection.cpp
// ^AUTHOR :  Ram Singaram, David Smith / Glen McNabb - for FAST
// ^DATE   :  March 2000
//
// ----------------------------------------------------------

#include <srcprag.h>
#pragma warning( disable: 4275 )
#include "vmconnection.hpp"
#include "vminterface.hpp"
#include <win32\vmdst.h>
#include <conditionmanager.hpp>
#include <eventsemaphore.hpp>
#include <assert.h>


namespace
{
   extern const I_CHAR *CLASSNAME = I_( "VmConnection" );
}

namespace CND
{
   extern const I_CHAR *BFCONMGR_CONDITION;
   extern const long ERR_VMCONNECTION_CREATE_EVENT;
   extern const long ERR_VMCONNECTION_CREATE_FAILED;
   extern const long ERR_VMCONNECTION_CONNECT_FAILED;
   extern const long ERR_VMCONNECTION_NOTIFY_FAILED;
   extern const long ERR_VMCONNECTION_DISCONNECT_FAILED;
   extern const long ERR_VMCONNECTION_REQUEST_FAILED;
   extern const long ERR_VMCONNECTION_WAITEVENT_FAILED;
   extern const long ERR_VM;
}

//******************************************************************************
VmConnection::VmConnection( const DStringA &hostId, const DStringA &connectionName )
: _connectionName(connectionName)
, _hostId(hostId)
, _description(hostId + ":" + connectionName)
, _connected(false)
, _eventHandle(NULL)
, _pszResponseBuffer(NULL)
, _pEventSemaphore( NULL )
, _dstraResponse( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING )

   _pszResponseBuffer = new char[32*1024];

   connect();
}

//******************************************************************************
VmConnection::~VmConnection()
{
   delete _pszResponseBuffer;

   if( _connected )
   {
      try
      {
         disconnect();
      }
      catch( ... )
      {
      }
   }
   if( _pEventSemaphore )
   {
      delete _pEventSemaphore;
   }
}

//******************************************************************************
void VmConnection::connect()
{
   // setup the names for the named objects
   sprintf( _appName,"%8.8s", _connectionName.c_str() );
   sprintf( _semName, "%8.8sSEM", _connectionName.c_str() );

   // initialize the connection structure
   memset( &_vmRequest, 0, sizeof( VMREQ ) );
   _vmRequest.Vm.usOpCode  = VM_OP_CONNECT;
   _vmRequest.Vm.usVersion = VM_VERSION;
   strcpy( _vmRequest.Vm.szIdent, _appName );
   _vmRequest.Vm.ulMsgSize = APP_MESSAGE_SIZE;
   _vmRequest.Vm.pszErrMsg = _errMsg;

   try
   {
      // close shared resources, just in case they are still hanging around
      // (if another app is using the same name, they are gonzo...)
      VMDll_Interface::get().VmDisconnectApp( _appName, _errMsg, APP_MESSAGE_SIZE );
   }
   catch( ... )
   {
   }

   // create the notification event
   _eventHandle = CreateEvent( NULL, FALSE, FALSE, _semName );
   if( _eventHandle == NULL )
   {
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_VMCONNECTION_CREATE_EVENT);
   }

   // connect to VM using the appropriate app name
   if( VM_S_OK != VMDll_Interface::get().VmConnectApp( _appName, _errMsg, APP_MESSAGE_SIZE ) )
   {
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_VMCONNECTION_CREATE_FAILED);
   }

   unsigned short rc;

   // setup VM semaphore notification
   rc = VMDll_Interface::get().VmNotifySem( _appName,
                                            _semName,
                                            VM_NOTIFY_RESPONSE|VM_BUFF_ALLOC,
                                            NULL,
                                            0L,
                                            _errMsg,
                                            APP_MESSAGE_SIZE );

   if( rc != VM_P_OK )
   {
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_VMCONNECTION_NOTIFY_FAILED);
   }

   // create the connection for the given host
   strcpy( _vmRequest.szHost, _hostId.c_str());

   _connected = true;
}

//******************************************************************************
void VmConnection::disconnect()
{

   // close shared resources
   VMDll_Interface::get().VmDisconnectApp( _appName, _errMsg, APP_MESSAGE_SIZE );
   CloseHandle( _eventHandle );

   _connected = false;
}

//******************************************************************************
void VmConnection::putRequest( const DStringA &viewName, 
                               const DStringA &request, 
                               bool bRecycleOnReceive, 
                               const BFData* pQuery, 
                               BFSecurity* pSecurity )
{
   unsigned short rc = VMDll_Interface::get().VmAppRequest( _appName,
                                                            NULL,
                                                            const_cast<char *>(_hostId.c_str()),
                                                            const_cast<char *>(viewName.c_str()),
                                                            VM_NEW_REQUEST,
                                                            (UCHAR*)(const_cast<char *>(request.c_str())),
                                                            (ULONG) request.size(),
                                                            0L,
                                                            VIEW_TIMEOUT,
                                                            _errMsg,
                                                            APP_MESSAGE_SIZE );

   if( rc != VM_P_OK )
   {
      // stale out this connection object
      if( _connected )
      {
         disconnect();
      }

      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("send"), CND::ERR_VMCONNECTION_REQUEST_FAILED );
   }

   return;
}

//******************************************************************************
const DStringA& VmConnection::getHostId() const
{
   return(_hostId);
}

//******************************************************************************
const unsigned long VmConnection::getViewReturnCode()
{
   return(_ulReturnCode);
}

//******************************************************************************
const DStringA& VmConnection::getDescription() const
{
   return(_description);
}

//******************************************************************************
bool VmConnection::isStale() const
{
   return(!_connected);
}

//******************************************************************************
const DStringA& VmConnection::getResponse()
{
   // clear out last response buffer...
   _dstraResponse = DStringA();

   if( WAIT_OBJECT_0 != WaitForSingleObject( _eventHandle, VIEW_TIMEOUT /*INFINITE*/ ) )
   {
      // stale out this connection object
      if( _connected )
         disconnect();

      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_( "getResponse" ), CND::ERR_VMCONNECTION_WAITEVENT_FAILED );
   }

   // Extract VIEW information
   PVMAPPRESP pVmResp = (PVMAPPRESP) VMDll_Interface::get().VmReadResponse( _appName );

   VMDSTRESP dstVmResp;
   VMDll_Interface::get().VmExtractResp( (unsigned char *)pVmResp, &dstVmResp );

   strncpy( _pszResponseBuffer, (char *) pVmResp->pbBuff, pVmResp->ulBuffSize );
   _pszResponseBuffer[ pVmResp->ulBuffSize ] = '\0';

   char szResponseCode[4];
   strncpy( szResponseCode, ((PRESPONSE_HEADER)_pszResponseBuffer)->pchReturnCode, 3 );
   szResponseCode[3] = '\0';
   _ulReturnCode = atol( szResponseCode );

   VMDll_Interface::get().VmFree( (void *) pVmResp );

   if( _ulReturnCode != 0 )
   {
      //the VM return code is not good we should add VM errors here
      DStringA dstraReturnCode( szResponseCode );
      THROWFROMFILEIDI2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("getResponse"), CND::ERR_VM, dstraReturnCode );
   }
   else
   {
      _dstraResponse = DStringA( _pszResponseBuffer );
   }

   return(_dstraResponse);
}

//******************************************************************************
const DStringA& VmConnection::getName() const
{
   return(_connectionName);
}

//******************************************************************************
bool VmConnection::shutdownAll()
{
   char szErrMsg[APP_MESSAGE_SIZE+1];
   return( VM_S_OK == VMDll_Interface::get().VmShutdownExe( VM_SHUTDOWN_ABNORMAL, szErrMsg, APP_MESSAGE_SIZE ) );
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfconmgr/VmConnection.cpp-arc  $
//
//   Rev 1.11   Oct 21 2009 10:38:44   purdyech
//LDAP Authorization Support
//
//   Rev 1.10   Mar 27 2009 10:10:10   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.9   Sep 27 2004 09:40:42   PURDYECH
//Clean up compiler warnings so that there are no complaints about silly things (like truncated debug names...)
//
//   Rev 1.8   Jan 27 2004 16:04:16   PURDYECH
//putRequest signature changed (see BFRecordConnection.hpp)
// 
//    Rev 1.7   Jan 27 2003 15:23:32   PURDYECH
// BFConnection changes
// 
//    Rev 1.6   Oct 09 2002 17:40:20   PURDYECH
// New PVCS Database
// 
//    Rev 1.5   Aug 29 2002 12:59:26   PURDYECH
// VMInterface fixes
// 
//    Rev 1.4   Jul 10 2001 13:54:22   IVESPAUL
// Added time-out.
//
//    Rev 1.3   Jun 26 2001 12:54:36   PURDYECH
// Infrastructure Release 1.9 Integration.
//
//    Rev 1.2   Jun 18 2001 10:22:46   IVESPAUL
// AdminCompany objects now contain twin FastHost objects.
//
//    Rev 1.1   May 22 2001 13:49:26   MCNABBGL
// server monitoring functionality, explicit server registration with connection manager, fastrequestor modifications
//

