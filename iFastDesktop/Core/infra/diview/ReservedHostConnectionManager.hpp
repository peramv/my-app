#pragma message( "including "__FILE__ )

#ifndef RESERVEDHOSTCONNECTIONMANAGER_HPP
#define RESERVEDHOSTCONNECTIONMANAGER_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

#ifndef PLATFORM_H
   #include "platform.h"
#endif
#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif
#ifndef BASEHOSTCONNECTIONMANAGER_HPP
   #include "basehostconnectionmanager.hpp"
#endif
#ifndef INFRASEMAPHORE_HPP
   #include "infrasemaphore.hpp"
#endif
#ifndef INFRAEVENT_HPP
   #include "infraevent.hpp"
#endif
#ifndef MUTEXSEMAPHORE_HPP
   #include "mutexsemaphore.hpp"
#endif

#include <queue>

class BaseConnectionFactory;
class BaseConnection;

class ReservedHostConnectionManager : public BaseHostConnectionManager
{
public:
   /**
    * Constructor.
    *
    * @param hostConnectionManagerId
    *                 Contains the name of the host connection manager
    *                 to use for security related requests.
    *
    * @param hostId   Name of the host.
    *
    * @param connectionFactory
    *                 Connection factory to use to create connections.
    *
    * @param maxConnections
    *                 Maximum number of connections.  The number of connections
    *                 will not grow or shrink according to load.
    *                 or shrink according to load.
    */
   ReservedHostConnectionManager( const DString & hostConnectionManagerId,
                                  const DString & hostId,
                                  BaseConnectionFactory * connectionFactory,
                                  int maxConnections,
                                  unsigned long timeout );
   virtual ~ReservedHostConnectionManager( );

   /**
    * Find a free non-reserved connection and mark it as "reserved".
    *
    * @return The name of the connection.
    */
   virtual DString getReservation( );

   /**
    * Find the specified reserved connection and mark it as "non-reserved".
    *
    * @param connectionName
    *                 Name of a connection that was reserved by a call to
    *                 getReservation.
    *
    * @return The name of the connection.
    */
   virtual void freeReservation( const DString & connectionName );

   /**
    * Get a non-reserved connection.  If a free non-reserved connection is
    * found, return it, otherwise wait for a non-reserved connection to become
    * free.
    *
    * @param timeout  The time to wait for a connection to be released
    * @return A non-reserved connection.
    */
   virtual BaseConnection * getNonReservedConnection( unsigned long timeout );

   /**
    * Get a specific connection that was reserved by a call to getReservation.
    * If the connection is unused, it will be returned, otherwise wait for the
    * connection to become free.
    *
    * @param connectionName
    *                 Name of a connection that was reserved by a call to
    *                 getReservation.
    *
    * @return The specified connection.
    */
   virtual BaseConnection * getConnection( const DString & connectionName );

   /**
    * Get a connection.  If a free non-reserved connection is found, return it,
    * otherwise look for a free reserved connection.  If a free reserved
    * connection is found, return it, otherwise wait for a connection to become
    * free.
    *
    * New connections are never created by calls to this method.  All
    * connections managed by this class are created during construction.
    *
    * @return A connection.
    */
   virtual BaseConnection * getConnection( void );

   /**
    * Free a connection.  This will return the connection to the pool.  Calling
    * this method does not change the reserved status of the connection.
    *
    * @param connection Connection to free.
    */
   virtual void freeConnection( BaseConnection * connection );

   virtual const DString & getHostConnectionManagerId( ) const;
   virtual const DString & getHostId( ) const;
   virtual int getMaxConnections( ) const;
   virtual int getMinConnections( ) const;
   virtual int getConnectionCount( ) const;
   virtual int getConnectionsInUse( ) const;
   virtual int getConnectionFailures( ) const;

protected:
   ReservedHostConnectionManager( );

private:
   typedef std::queue< BaseConnection * > CONNECTION_QUEUE;

   //
   // The connection queue contains all non-reserved connections.
   //

   CONNECTION_QUEUE _connectionQueue;

   //
   // The reserved queue contains all reserved connections.
   //

   CONNECTION_QUEUE _reservedQueue;

   const DString _hostConnectionManagerId;
   const DString _hostId;
   BaseConnectionFactory * _connectionFactory;

   const int _maxConnections;
   const unsigned long _timeout;

   int _connectionFailures;
   int _connectionCount;
   int _connectionsInUse;

   //
   // The connection mutex synchronizes all access to the connection and reserved
   // queues. Also, the connection mutex should be locked any time the connection
   // semaphore is released or the reserved event is set.
   //

   MutexSemaphore _connectionMutex;

   //
   // The connection semaphore is used to gain access to a connection (either
   // non-reserved or reserved). The connection semaphore should be released after
   // a connection is returned to the connection or reserved queue.
   //

   InfraSemaphore _connectionSemaphore;

   //
   // The connection event semaphore is used to signal that a connection was
   // just returned to the connection queue.
   //

   InfraEvent _connectionEvent;

   //
   // The reserved event semaphore is used to signal that a reserved connection was
   // just returned to the reserved queue.
   //

   InfraEvent _reservedEvent;
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
// $Log:   Y:/VCS/iFastAWD/diview/ReservedHostConnectionManager.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:24:02   kovacsro
//Initial revision.
//
//   Rev 1.2   Aug 03 2001 17:07:18   DT11159
//Added _connectionEvent and fixed a deadlock in getReservation( ).
//Added conditions ERR_CONNECTION_TIMEOUT,
//ERR_NON_RESERVED_CONNECTION_TIMEOUT,
//and ERR_RESERVATION_TIMEOUT.
//
//
//   Rev 1.1   Jun 28 2001 16:49:34   DT11159
//Renamed some classes.
//
//

#endif
