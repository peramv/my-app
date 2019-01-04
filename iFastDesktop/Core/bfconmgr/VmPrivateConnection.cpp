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
// ^FILE   :  VMPrivateConnection.cpp
// ^AUTHOR :  Ram Singaram,David Smith
// ^DATE   :  March 2000
//
// ----------------------------------------------------------

#include <SrcPrag.h>
#include "VmPrivateConnection.hpp"
#include <conditionmanager.hpp>
#include "vminterface.hpp"

namespace
{
   extern const I_CHAR *CLASSNAME = I_( "VmPrivateConnection" );
}

namespace CND
{
   extern const I_CHAR *BFCONMGR_CONDITION;
   extern const long ERR_PRIVCONN_CREATE_EVENT;
   extern const long ERR_PRIVCONN_CREATE_FAILED;
   extern const long ERR_PRIVCONN_CONNECT_FAILED;
   extern const long ERR_PRIVCONN_NOTIFY_FAILED;
   extern const long ERR_PRIVCONN_REQUEST_FAILED;
   extern const long ERR_PRIVCONN_WAITEVENT_FAILED;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VmPrivateConnection::VmPrivateConnection( const DStringA &hostId, const DStringA &connectionName )
:  _connectionName(connectionName),
_hostId(hostId),
_description(hostId + ":" + connectionName),
_connected(false),
_eventHandle(NULL),
_response(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING )

   connect();
}

VmPrivateConnection::~VmPrivateConnection()
{
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
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void
VmPrivateConnection::connect()
{

   // setup the names for the named objects
   sprintf( _appName,"%8.8s", _connectionName.c_str() );
   sprintf( _semName, "%8.8sSEM", _connectionName.c_str() ); 

   // initialize the private connection structure
   memset( &_vmPrivate, 0, sizeof( VMPRIV ) );
   _vmPrivate.Vm.usOpCode  = VM_OP_PRIVATE;
   _vmPrivate.Vm.usVersion = VM_VERSION;
   strcpy( _vmPrivate.Vm.szIdent, _appName );
   _vmPrivate.Vm.ulMsgSize = APP_MESSAGE_SIZE;
   _vmPrivate.Vm.pszErrMsg = _errMsg;

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
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_PRIVCONN_CREATE_EVENT);
   }

   // connect to VM using the appropriate app name
   if( VM_S_OK != VMDll_Interface::get().VmConnectApp( _appName, _errMsg, APP_MESSAGE_SIZE ) )
   {
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_PRIVCONN_CREATE_FAILED);
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
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_PRIVCONN_NOTIFY_FAILED);
   }

   // create the private connection for the given host
   strcpy( _vmPrivate.szHost, _hostId.c_str());
   _vmPrivate.usCommand = VM_PRIV_CREATE;
   VMDll_Interface::get().ViewMgr( (PVOID) &_vmPrivate );
   if( _vmPrivate.Vm.usRcPrimary != VM_P_OK )
   {
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_PRIVCONN_CREATE_FAILED);
   }

   // connect the private connection
   _vmPrivate.usCommand = VM_PRIV_CONNECT;
   VMDll_Interface::get().ViewMgr( (PVOID) &_vmPrivate );
   if( _vmPrivate.Vm.usRcPrimary != VM_P_OK )
   {
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("connect"), CND::ERR_PRIVCONN_CONNECT_FAILED);
   }

   _connected = true;
}

void
VmPrivateConnection::disconnect()
{

   // disconnect private connection
   _vmPrivate.usCommand = VM_PRIV_DISCONNECT;
   VMDll_Interface::get().ViewMgr( (PVOID) &_vmPrivate );

   // destroy private connection
   _vmPrivate.usCommand = VM_PRIV_DESTROY;
   VMDll_Interface::get().ViewMgr( (PVOID)&_vmPrivate );

   // close shared resources
   VMDll_Interface::get().VmDisconnectApp( _appName, _errMsg, APP_MESSAGE_SIZE );
   CloseHandle( _eventHandle );

   // free the response buffer
   freeResponse();
   _connected = false;
}

void
VmPrivateConnection::send( const DStringA &viewName, const DStringA &request )
{

   freeResponse();

   unsigned short rc = VMDll_Interface::get().VmAppRequestPriv( _appName,
                                                                _vmPrivate.usConnection,
                                                                const_cast<char *> (viewName.c_str()),
                                                                (PBYTE) request.c_str(),
                                                                (ULONG) request.size(),
                                                                0L,
                                                                0,
                                                                _errMsg,
                                                                APP_MESSAGE_SIZE );

   /*****************************/
   /**  Check the return code  **/
   /*****************************/

   if( rc != VM_P_OK )
   {
      // stale out this connection object
      if( _connected )
         disconnect();

      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("send"), CND::ERR_PRIVCONN_REQUEST_FAILED);
   }
}

void  
VmPrivateConnection::freeResponse()
{
   delete _response;
   _response = NULL;
}

const DStringA &
VmPrivateConnection::getHostId() const
{
   return(_hostId);
}

const DStringA &
VmPrivateConnection::getDescription() const
{
   return(_description);
}

bool 
VmPrivateConnection::isStale() const
{
   return(!_connected);
}

const DStringA &
VmPrivateConnection::getResponse()
{

   if( NULL == _response )
   {
      if( WAIT_OBJECT_0 != WaitForSingleObject( _eventHandle, INFINITE ) )
      {
         // stale out this connection object
         if( _connected )
            disconnect();

         THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("getResponse"), CND::ERR_PRIVCONN_WAITEVENT_FAILED);
      }
      /********************************/
      /**  Extract VIEW information  **/
      /********************************/
      PVMAPPRESP pVmResp = (PVMAPPRESP) VMDll_Interface::get().VmReadResponse( _appName );

      char *buff = new char[pVmResp->ulBuffSize+1];
      strncpy(buff, ( char *) pVmResp->pbBuff, pVmResp->ulBuffSize);
      buff[pVmResp->ulBuffSize] = '\0';

      _response = new DStringA( buff );

      VMDll_Interface::get().VmFree( (void *) pVmResp );
      delete[] buff;

   }

   return(*_response);
}


const DStringA &
VmPrivateConnection::getName() const
{
   return(_connectionName);
}
