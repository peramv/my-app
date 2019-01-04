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
 *   Class:   VmClientConnection.cpp
 *
 *   Class Description
 *
 */
#define DIVIEW_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef INCLUDED_ASSERT_H
   #include <assert.h>
#endif
#ifndef VMCLIENTCONNECTION_HPP
   #include "vmclientconnection.hpp"
#endif
#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif
#define CONDITIONMIGRATE_HPP // Defined to prevent use of the deprecated macros.
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DIVIEW_H
   #include "diview.h"
#endif

#ifndef DICORE
   #include "dicore.h"
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "VmClientConnection" );
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VmClientConnection::VmClientConnection( const DString & hostId,
                                        const DString & connectionName ) :
_connectionName( connectionName ),
_hostId( hostId ),
_connected( false ),
_eventHandle( NULL ),
_response( NULL ),
_hwndRecipient( 0 ),
_ulMsg( 0 ),
_reserved( false )

{
   sprintf( _appName,"%8.8s", _connectionName.asA( ).c_str( ) );
   sprintf( _semName, "%sSEM", _appName );
}

VmClientConnection::~VmClientConnection( )
{
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

const DString &
VmClientConnection::getHostConnectionManagerId( ) const
{
   return _hostConnectionManagerId;
}

void
VmClientConnection::setHostConnectionManagerId( const DString & hostConnectionManagerId )
{
   _hostConnectionManagerId = hostConnectionManagerId;
}

const DString &
VmClientConnection::getHostId( ) const
{
   return _hostId;
}

bool
VmClientConnection::isStale( ) const
{
   return( !_connected );
}

void VmClientConnection::waitResponse()
{
   if ( NULL == _response )
   {
      if ( WAIT_OBJECT_0 != WaitForSingleObject( _eventHandle, INFINITE ) )
      {
         // stale out this connection object
         if ( _connected )
         {
            disconnect( );
         }

         I_CHAR handle[20];
         i_sprintf( handle, I_( "0x%08lX" ), _eventHandle );

         DString msg;
         addIDITagValue( msg, I_( "Handle" ), handle );
         addIDITagValue( msg, I_( "Semaphore" ), DStringA( _semName ) );
         addIDITagValue( msg, I_( "Host" ), _hostId );
         addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

         THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                  I_( "VmClientConnection::waitResponse" ),
                                  ERR_WAIT_EVENT_FAIL, msg, NULL );
      }
   }
}

const void *
VmClientConnection::getResponse( )
{
   if ( NULL == _response )
   {
      /********************************/
      /**  Extract VIEW information  **/
      /********************************/
      DString tempName;
      _response = VmReadResponse( const_cast<char *> ( getName( tempName ).asA().c_str( ) ) );
      if ( NULL == _response )
      {
         DString msg;
         addIDITagValue( msg, I_( "Host" ), _hostId );
         addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

         THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                  I_( "VmClientConnection::getResponse" ),
                                  ERR_READ_RESPONSE_FAIL, msg, NULL );
      }
   }

   return( ( const void * ) _response );
}

void
VmClientConnection::freeResponse( )
{
   VmFree( _response );
   _response = NULL;
}

const DString &
VmClientConnection::getName( DString & connectionName ) const
{
   connectionName = _connectionName;

   return( connectionName );
}

void VmClientConnection::setWindowInfo(
                   DSTWINDOWHANDLE hwndRecipient,
                   unsigned long ulMsg )
{
   _hwndRecipient = hwndRecipient;
   _ulMsg = ulMsg;
}

void VmClientConnection::setNotificationMethod()
{
   // Set up the notification based on the value of _hwndRecipient
   if ( ( 0 == _hwndRecipient ) &&
        ( 0 == _ulMsg ) )
   {
      // Semaphore notification
      unsigned short rc;

      // setup VM semaphore notification
      rc = VmNotifySem( _appName,
                        _semName,
                        VM_NOTIFY_RESPONSE|VM_BUFF_ALLOC,
                        NULL,
                        0L,
                        _errMsg,
                        APP_MESSAGE_SIZE );
      if ( rc != VM_P_OK )
      {
         DString msg;
         addIDITagValue( msg, I_( "RC" ), rc );
         addIDITagValue( msg, I_( "Message" ), DStringA( _errMsg ) );
         addIDITagValue( msg, I_( "Semaphore" ), DStringA( _semName ) );
         addIDITagValue( msg, I_( "Host" ), _hostId );
         addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

         THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                  I_( "VmClientConnection::setNotificationMethod" ),
                                  ERR_NOTIFY_SEM_FAIL, msg, NULL );
      }
   }
   else
   {
      // Window notification
      unsigned short rc;

      rc = VmNotifyWin( _appName,
                        ( HWND )_hwndRecipient,
                        _ulMsg,
                        VM_NOTIFY_RESPONSE | VM_BUFF_ALLOC,
                        NULL,
                        0L,
                        _errMsg,
                        APP_MESSAGE_SIZE );

      if ( rc != VM_P_OK )
      {
         I_CHAR hwnd[20];
         i_sprintf( hwnd, I_( "0x%08lX" ), _hwndRecipient );

         DString msg;
         addIDITagValue( msg, I_( "RC" ), rc );
         addIDITagValue( msg, I_( "Message" ), DStringA( _errMsg ) );
         addIDITagValue( msg, I_( "HWND" ), hwnd );
         addIDITagValue( msg, I_( "MessageID" ), (long) _ulMsg );
         addIDITagValue( msg, I_( "Host" ), _hostId );
         addIDITagValue( msg, I_( "Connection" ), DStringA( _appName ) );

         _hwndRecipient = 0;
         _ulMsg = 0;

         THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                  I_( "VmClientConnection::setNotificationMethod" ),
                                  ERR_NOTIFY_WIN_FAIL, msg, NULL );
      }

      _hwndRecipient = 0;
      _ulMsg = 0;
   }
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
// $Log:   Y:/VCS/iFastAWD/diview/VmClientConnection.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:06   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:27:28   DT11159
// 
//
//
