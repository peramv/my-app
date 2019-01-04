#pragma message( "including "__FILE__ )

#ifndef POOLEDHOSTCONNECTIONMANAGER_HPP
#define POOLEDHOSTCONNECTIONMANAGER_HPP

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
   #include "InfraSemaphore.hpp"
#endif
#ifndef INFRAEVENT_HPP
   #include "InfraEvent.hpp"
#endif
#ifndef MUTEXSEMAPHORE_HPP
   #include "MutexSemaphore.hpp"
#endif
#ifndef INFRATHREAD_HPP
   #include "InfraThread.hpp"
#endif

#include <queue>

class BaseConnectionFactory;
class BaseConnection;

/**
 * Pooled Host Connection Manager
 *
 * Class manages a pool of connections which can grow and shrink according to
 * recent load.
 */
class PooledHostConnectionManager : public BaseHostConnectionManager, public InfraThread
{
public:
   /**
    * Constructor
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
    * @param minConnections
    *                 Minimum number of connections.  During construction,
    *                 this number of connections will be created.
    *
    * @param maxConnections
    *                 Maximum number of connections.  If maxConnections equals
    *                 minConnections, the number of connections will not grow
    *                 or shrink according to load.  The maxConnections should
    *                 never be less than minConnections.
    *
    * @param reaperInterval
    *                 Interval, seconds, for thread to remove unneeded
    *                 connections.
    *
    * @param reaperCount
    *                 Max number of connections removed per interval.
    */
   PooledHostConnectionManager( const DString & hostConnectionManagerId,
                                const DString & hostId,
                                BaseConnectionFactory * connectionFactory,
                                int minConnections,
                                int maxConnections,
                                unsigned long timeout,
                                int reaperInterval,
                                int reaperCount );
   virtual ~PooledHostConnectionManager( );

   /**
    * Get a connection.  If there is an unused connection already in the pool,
    * it will be returned.  If maxConnections has been reached, wait for a
    * connection to become free, otherwise a new connection will be created and
    * returned.
    *
    * @return A connection.
    */
   virtual BaseConnection * getConnection( void );

   /**
    * Free a connection.  This will return the connection to the pool.
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
   PooledHostConnectionManager( );
   void run( );

private:
   typedef std::queue< BaseConnection* >  CONNECTION_QUEUE;
   typedef CONNECTION_QUEUE::value_type CONNECTION_QUEUE_VALUE_TYPE;

   CONNECTION_QUEUE _connectionQueue;
   MutexSemaphore _connectionMutex;

   const DString _hostConnectionManagerId;
   const DString _hostId;
   BaseConnectionFactory * _connectionFactory;

   const int _minConnections;
   const int _maxConnections;
   const unsigned long _timeout;
   const int _reaperInterval;
   const int _reaperCount;

   int _connectionFailures;
   int _connectionCount;
   int _connectionsInUse;

   int _intervalMaxConnectionsInUse;

   InfraSemaphore _connectionSemaphore;
   InfraEvent _shutdownEvent;
};

#endif


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
/* $Log:   Y:/VCS/iFastAWD/diview/PooledHostConnectionManager.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:24:00   kovacsro
//Initial revision.
//
//   Rev 1.1   Jun 28 2001 16:49:32   DT11159
//Renamed some classes.
//
//   Rev 1.0   May 18 2001 11:40:22   DT11159
// 
//
//   Rev 1.1   04 Dec 2000 11:38:18   SMITHDAV
//Add console connection monitoring support.
//
//   Rev 1.0   23 Oct 2000 20:10:48   SMITHDAV
//Initial revision.
//
//    Rev 1.1   May 02 2000 17:29:26   DT24433
// changed to use Infra CriticalSection
//
//    Rev 1.0   Apr 28 2000 18:59:34   SMITHDAV
// Initial revision.
*/