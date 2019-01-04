#pragma message( "including "__FILE__ )

#ifndef VMCLIENTCONNECTION_HPP
#define VMCLIENTCONNECTION_HPP

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

#ifndef PLATFORM_H
   #include "platform.h"
#endif
#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif
#ifndef BASECONNECTION_HPP
   #include "baseconnection.hpp"
#endif

extern "C"
{
#include <vm.h>
#include <vmdll.h>
#include <vmdst.h>
}

namespace
{
   const int APP_MESSAGE_SIZE = 128;
}

/**
 * This class provides common functionality for the more specific View Manager
 * connection classes.
 */
class DIVIEW_LINKAGE VmClientConnection : public BaseConnection
{
public:
   /**
    * Constructor
    *
    * @param hostId          The name of target host.  The default host
    *                        configured in View Manager will be used if this
    *                        hostId is an empty string.
    * @param connectionName  The name of the connection to View Manager client.
    */
   VmClientConnection( const DString & hostId, const DString & connectionName );

   /**
    * Destructor
    */
   virtual ~VmClientConnection( );

   /**
    * Used to find out if the connection is stale (unusable).
    *
    * @return true - if, and only if, connected is unusable.
    */
   virtual bool isStale( ) const;

   /**
    * Used to wait on the response data.
    *
    */
   virtual void waitResponse();

   /**
    * Used to get the response data.
    *
    * @return Pointer to the response data. The pointer returned will point to
    *         a VMAPPRESP structure.
    */
   virtual const void * getResponse( );

   /**
    * Used to get the ID of the connection manager that manages this connection.
    *
    * @return ID of host connection manager.
    */
   virtual const DString & getHostConnectionManagerId( ) const;

   /**
    * Used to set the ID of the connection manager that manages this connection.
    *
    * @param managerId  ID of the manager for this connection.
    */
   virtual void setHostConnectionManagerId( const DString & hostConnectionManagerId );

   /**
    * Used to get the host ID.
    *
    * @return Name of the target host for this connection.
    */
   virtual const DString & getHostId( ) const;

   /**
    * Used to set the host ID.  This method allows the host to be changed
    * prior to sending data to the connection.
    *
    * @param hostId Name of the target host for this connection.
    */
   virtual void setHostId( const DString & hostId )
   {
      _hostId = hostId;
   }

   /**
    * Used to get the name of this connection. The name of the connection is
    * passed in on the constructor.
    */
   virtual const DString & getName( DString & connectionName ) const;

   /**
    * Used to get the error message if a View Manager error occurs.
    *
    * @param message error message returned from View Manager.
    * @return error message returned from View Manager.
    */
   virtual const DString & getErrorMessage( DString & message ) const
   {
      message = _errMsg;

      return ( message );
   }

   /**
    * Sets the window information needed for notification via PostMessage
    *
    * The calling application can use messaging to be notified of data returned
    * from the backend.
    *
    * The application must use the unique combinations of the two values.  The values
    * provides in the set are only used once and a different combination
    * must be provided for the next messaging notfication.  If the unique combination is
    * not provided, the normal notification process will be used via semaphores.
    *
    * @param hwndRecipient - Window identifier
    * @param ulMsg - Message identifier
    *
    */
   virtual void setWindowInfo( DSTWINDOWHANDLE hwndRecipient,
                               unsigned long ulMsg );

   /**
    * Used to set reserved status.
    *
    * @param reserved  New reserved state.
    */
   virtual void setReserved( bool reserved )
   {
      _reserved = reserved;
   }

   /**
    * Used to find out if the connection is reserved.
    *
    * @return true - if, and only if, connected is reserved.
    */
   virtual bool isReserved( ) const
   {
      return( _reserved );
   }

protected:
   /**
    * View Manager "application name".
    */
   char _appName[9];

   /**
    * Name of semaphore to be posted by View Manager when a response
    * is available.
    */
   char _semName[12];

   /**
    * Boolean that indicates whether or not a connection to View Manager exists.
    * Initialized to false. Set to true when connect() completes successfully.
    * Set to false when disconnect() is called.
    */
   bool _connected;

   /**
    * Handle of event semaphore that will be posted by View Manager when a
    * response is available.
    */
   HANDLE _eventHandle;

   /**
    * Area for error message returned by View Manager.
    */
   char _errMsg[APP_MESSAGE_SIZE];

   /**
    * Pointer to View Manager Application Response structure. See the View
    * Manager documentation for more information.
    */
   PVMAPPRESP _response;

   DSTWINDOWHANDLE _hwndRecipient;
   unsigned long _ulMsg;

   /**
    * Not implemented.
    */
   VmClientConnection( )
   {
   }

   /**
    * Used to start a connection via View Manager client.
    */
   virtual void connect( ) = 0;

   /**
    * Used to end a connection via View Manager client.
    */
   virtual void disconnect( ) = 0;

   /**
    * Used to free a View Manager response buffer.
    */
   virtual void freeResponse( );

   /**
    * Used to set up the notification method being used
    *    for the next data request to the backend
    */
   virtual void setNotificationMethod();

private:
   /**
    * ID of the host connection manager that manages this connection.  This
    * field is needed so that this connection can be freed back into the host
    * connection manager from which it came.
    */
   DString _hostConnectionManagerId;

   /**
    * ID of target host. If this field is an empty string, the default host
    * configured for View Manager will be used.
    */
   DString _hostId;

   /**
    * This is the name of the connection to View Manager client.
    */
   const DString _connectionName;

   /**
    * This flag indicates whether this connection is reserved.
    */
   bool _reserved;
};

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
// $Log:   Y:/VCS/iFastAWD/diview/VmClientConnection.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:24:06   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:27:32   DT11159
// 
//
//

#endif
