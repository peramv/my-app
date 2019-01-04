#pragma message( "including "__FILE__ )

#ifndef BASECONNECTION_HPP
   #define BASECONNECTION_HPP

/**
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

// Import/Export resolution
   #undef DIVIEW_LINKAGE
   #ifdef DIVIEW_DLL
      #define DIVIEW_LINKAGE CLASS_EXPORT
   #else
      #define DIVIEW_LINKAGE CLASS_IMPORT
   #endif

class DString;

/**
 * This class provides a pure virtual interface for the specific connection
 * classes.
 */
class DIVIEW_LINKAGE BaseConnection
{
public:
   /**
    * Destructor
    */
   virtual ~BaseConnection( )
   {
   }

   /**
    * Used to send request data to the target of this connection.
    *
    * @param name     The name of the request.
    * @param request  The request data.
    * @param timeout  The maximum number of seconds to wait for a response.
    *                 Zero means wait indefinitely.
    */
   virtual void send( const DString & name,
                      const DString & request,
                      unsigned long timeout ) = 0;

   /**
    * Used to get the response data.
    *
    * @return Pointer to the response data.
    */
   virtual const void * getResponse( ) = 0;

   /**
    * Used to wait on the response data
    *
    */
   virtual void waitResponse( ) = 0;

   /**
    * Used to free the response data.
    */
   virtual void freeResponse( ) = 0;

   /**
    * Used to get the host ID.
    *
    * @return Name of the target host for this connection.
    */
   virtual const DString & getHostId( ) const = 0;

   /**
    * Used to set the host ID.  If the connection is not to a single host, but
    * is instead a connection to middleware, this method allows the host to be
    * changed prior to sending data to the connection.
    *
    * @param hostId Name of the target host for this connection.
    */
   virtual void setHostId( const DString & hostId ) = 0;

   /**
    * Used to get the name of this connection. The name of the connection is
    * passed in on the constructor.
    */
   virtual const DString & getName( DString & connectionName ) const = 0;

   virtual const DString & getErrorMessage( DString & message ) const = 0;

   /**
    * Used to find out if the connection is stale (unusable).
    *
    * @return true - if, and only if, connected is unusable.
    */
   virtual bool isStale( ) const = 0;

   /**
    * Used to find out if the connection is reserved.
    *
    * @return true - if, and only if, connected is reserved.
    */
   virtual bool isReserved( ) const = 0;

   /**
    * Used to set reserved status.
    *
    * @param reserved  New reserved state.
    */
   virtual void setReserved( bool reserved ) = 0;

   /**
    * Used to get the ID of the connection manager that manages this connection.
    *
    * @return ID of host connection manager.
    */
   virtual const DString & getHostConnectionManagerId( ) const = 0;

   /**
    * Used to set the ID of the connection manager that manages this connection.
    *
    * @param managerId  ID of the manager for this connection.
    */
   virtual void setHostConnectionManagerId( const DString & managerId ) = 0;

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
                               unsigned long ulMsg ) = 0;
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
// $Log:   Y:/VCS/iFastAWD/inc/BaseConnection.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:58   kovacsro
//Initial revision.
//
//   Rev 1.2   Jun 08 2001 19:12:42   DT11159
//Added View Manager error information in conditions.
//
//   Rev 1.1   May 20 2001 16:56:22   DT11159
//Added the setHostId method to allow applications
//to change the target host  of a connection when using
//View Manager.
//
//   Rev 1.0   May 18 2001 15:51:58   DT11159
//
//
//

#endif
