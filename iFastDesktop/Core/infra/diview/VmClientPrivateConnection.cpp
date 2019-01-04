/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2001 by DST Systems, Inc.
 */

/**
 *   Author:  David Sample
 *
 *   Class:   VmClientPrivateConnection.cpp
 *
 *   Class Description
 *
 */
#define DIVIEW_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef VMCLIENTPRIVATECONNECTION_HPP
   #include "vmclientprivateconnection.hpp"
#endif
#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DIVIEW_H
   #include "diview.h"
#endif

#ifndef DICORE_CONDITIONS_HPP
   #include "dicore_conditions.hpp"
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "VmClientPrivateConnection" );
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VmClientPrivateConnection::VmClientPrivateConnection( const DString & hostId,
                                                      const DString & connectionName ) :
VmClientConnection( hostId, connectionName )
{
   connect( );
}

VmClientPrivateConnection::~VmClientPrivateConnection( )
{
   if ( _connected )
   {
      try
      {
         disconnect( );
      }
      catch ( ... )
      {
      }
   }
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void
VmClientPrivateConnection::send( const DString & viewName,
                                 const DString & request,
                                 unsigned long timeout )
{
   freeResponse( );

   setNotificationMethod();

   unsigned short rc;

   rc = VmAppRequestPriv( _appName,
                          _vmConnection.usConnection,
                          const_cast<char *> ( viewName.asA( ).c_str( ) ),
                          ( unsigned char * ) request.asA( ).c_str( ),
                          request.size(),
                          0L,
                          timeout > USHRT_MAX ? 0 : timeout,
                          _errMsg,
                          APP_MESSAGE_SIZE );
   if ( rc != VM_P_OK )
   {
      // Build message before doing anything that would destroy the error info.
      DString msg;
      addIDITagValue( msg, I_( "RC" ), rc );
      addIDITagValue( msg, I_( "Message" ), DStringA( _errMsg ) );
      addIDITagValue( msg, I_( "View" ), viewName );
      addIDITagValue( msg, I_( "Timeout" ), (long) timeout );
      addIDITagValue( msg, I_( "Host" ), getHostId( ) );
      addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

      // stale out this connection object
      if ( _connected )
      {
         disconnect( );
      }

      THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                               I_( "VmClientPrivateConnection::send" ),
                               ERR_APP_REQUEST_PRIV_FAIL, msg, NULL );
   }
}

void
VmClientPrivateConnection::connect( )
{
   // initialize the private connection structure
   memset( & _vmConnection, 0, sizeof( _vmConnection ) );
   _vmConnection.Vm.usOpCode  = VM_OP_PRIVATE;
   _vmConnection.Vm.usVersion = VM_VERSION;
   strcpy( _vmConnection.Vm.szIdent, _appName );
   _vmConnection.Vm.ulMsgSize = APP_MESSAGE_SIZE;
   _vmConnection.Vm.pszErrMsg = _errMsg;

   try
   {
      // close shared resources, just in case they are still hanging around
      // ( if another app is using the same name, they are gonzo... )
      VmDisConnectApp( _appName, _errMsg, APP_MESSAGE_SIZE );
   }
   catch ( ... )
   {
   }

   // create the notification event
   _eventHandle = CreateEvent( NULL, FALSE, FALSE, _semName );
   if ( _eventHandle == NULL )
   {
      DString msg;
      addIDITagValue( msg, I_( "Semaphore" ), DStringA( _semName ) );
      addIDITagValue( msg, I_( "Host" ), getHostId( ) );
      addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

      THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                               I_( "VmClientPrivateConnection::connect" ),
                               ERR_CREATE_EVENT_FAIL, msg, NULL );
   }

   // connect to VM using the appropriate app name
   unsigned short rc = VmConnectApp( _appName, _errMsg, APP_MESSAGE_SIZE );
   if ( VM_S_OK != rc )
   {
      DString msg;
      addIDITagValue( msg, I_( "RC" ), rc );
      addIDITagValue( msg, I_( "Message" ), DStringA( _errMsg ) );
      addIDITagValue( msg, I_( "Host" ), getHostId( ) );
      addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

      THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                               I_( "VmClientPrivateConnection::connect" ),
                               ERR_CONNECT_APP_FAIL, msg, NULL );
   }

   // create the private connection for the given host
   strcpy( _vmConnection.szHost, getHostId( ).asA().c_str( ) );
   _vmConnection.usCommand = VM_PRIV_CREATE;
   ViewMgr( ( PVOID ) & _vmConnection );
   if ( _vmConnection.Vm.usRcPrimary != VM_P_OK )
   {
      DString msg;
      addIDITagValue( msg, I_( "Request" ), _vmConnection.usCommand );
      addIDITagValue( msg, I_( "Primary" ), _vmConnection.Vm.usRcPrimary );
      addIDITagValue( msg, I_( "Secondary" ), _vmConnection.Vm.usRcSecondary );
      addIDITagValue( msg, I_( "Message" ), DStringA( _vmConnection.Vm.pszErrMsg ) );
      addIDITagValue( msg, I_( "Host" ), getHostId( ) );
      addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

      THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                               I_( "VmClientPrivateConnection::connect" ),
                               ERR_VIEWMGR_REQUEST_FAIL, msg, NULL );
   }

   // connect the private connection
   _vmConnection.usCommand = VM_PRIV_CONNECT;
   ViewMgr( ( PVOID ) & _vmConnection );
   if ( _vmConnection.Vm.usRcPrimary != VM_P_OK )
   {
      DString msg;
      addIDITagValue( msg, I_( "Request" ), _vmConnection.usCommand );
      addIDITagValue( msg, I_( "Primary" ), _vmConnection.Vm.usRcPrimary );
      addIDITagValue( msg, I_( "Secondary" ), _vmConnection.Vm.usRcSecondary );
      addIDITagValue( msg, I_( "Message" ), DStringA( _vmConnection.Vm.pszErrMsg ) );
      addIDITagValue( msg, I_( "Host" ), getHostId( ) );
      addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

      THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                               I_( "VmClientPrivateConnection::connect" ),
                               ERR_VIEWMGR_REQUEST_FAIL, msg, NULL );
   }

   _connected = true;
}

void
VmClientPrivateConnection::disconnect( )
{
   // disconnect private connection
   _vmConnection.usCommand = VM_PRIV_DISCONNECT;
   ViewMgr( ( PVOID ) & _vmConnection );

   // destroy private connection
   _vmConnection.usCommand = VM_PRIV_DESTROY;
   ViewMgr( ( PVOID )& _vmConnection );

   // close shared resources
   VmDisConnectApp( _appName, _errMsg, APP_MESSAGE_SIZE );
   CloseHandle( _eventHandle );

   // free the response buffer
   freeResponse( );
   _connected = false;
}

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/diview/VmClientPrivateConnection.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:08   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:27:36   DT11159
// 
//
//
