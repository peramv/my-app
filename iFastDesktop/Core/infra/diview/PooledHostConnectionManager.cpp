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
// ^FILE   :  PooledHostConnectionManager.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  March 2000
//
// ----------------------------------------------------------
#define DIVIEW_DLL

#ifndef SRCPRAG_h
   #include "SrcPrag.h"
#endif
#ifndef POOLEDHOSTCONNECTIONMANAGER_HPP
   #include "pooledhostconnectionmanager.hpp"
#endif
#ifndef BASE_H //for the conditons
   #include "base.h"
#endif
#ifndef BASECONNECTION_HPP
   #include "BaseConnection.hpp"
#endif
#ifndef BASECONNECTIONFACTORY_HPP
   #include "baseconnectionfactory.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef CRITICALSECTION_HPP
   #include "CriticalSection.hpp"
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "PooledHostConnectionManager" );
}

PooledHostConnectionManager::PooledHostConnectionManager( const DString & hostConnectionManagerId,
                                                          const DString & hostId,
                                                          BaseConnectionFactory * connectionFactory,
                                                          int minConnections,
                                                          int maxConnections,
                                                          unsigned long timeout,
                                                          int reaperInterval,
                                                          int reaperCount ) :
InfraThread( ),
_hostConnectionManagerId( hostConnectionManagerId ),
_hostId( hostId ),
_connectionFactory( connectionFactory ),
_minConnections( minConnections ),
_maxConnections( maxConnections ),
_timeout( ( timeout == 0 || timeout > ( INFINITE / 1000 ) ) ? INFINITE : timeout * 1000 ),
_reaperInterval( ( reaperInterval == 0 || reaperInterval > ( INFINITE / 1000 ) ) ?
                 INFINITE : reaperInterval * 1000 ),
_reaperCount( reaperCount ),
_connectionCount( 0 ),
_connectionsInUse( 0 ),
_connectionFailures( 0 ),
_intervalMaxConnectionsInUse( 0 ),
_connectionSemaphore( maxConnections, maxConnections ),
_connectionQueue( ),
_shutdownEvent( true )
{
   if ( _reaperInterval != INFINITE && _reaperCount > 0 && _minConnections < _maxConnections )
   {
      start( ); // start the reaper
   }

   // Attempt to initialize min connections.
   // Do not throw if unsuccessful - perhaps server is down - no need to give-up yet
   CriticalSection cs( _connectionMutex );

   BaseConnection * connection;

   for ( int i = 0; i < _minConnections; i++ )
   {
      try
      {
         connection = _connectionFactory->createConnection( _hostId );
         connection->setHostConnectionManagerId( _hostConnectionManagerId );
      }
      catch ( ... )
      {
         break;
      }

      _connectionQueue.push( connection );
      _connectionCount++;
   }
}

PooledHostConnectionManager::PooledHostConnectionManager( )
:  InfraThread( ),
_hostId( NULL_STRING ),
_connectionFactory( NULL ),
_minConnections( 0 ),
_maxConnections( 0 ),
_timeout( INFINITE ),
_reaperInterval( INFINITE ),
_reaperCount( 0 ),
_connectionCount( 0 ),
_connectionsInUse( 0 ),
_connectionFailures( 0 ),
_intervalMaxConnectionsInUse( 0 ),
_connectionSemaphore( 0, 0 ),
_connectionQueue( ),
_shutdownEvent( true )
{
}

PooledHostConnectionManager::~PooledHostConnectionManager( )
{
   _shutdownEvent.set( ); // signal the reaper to shutdown
   wait( INFINITE ); // wait for the reaper to shutdown

   // wait for all connections to be freed and block subsequent gets
   for ( int i = 0; i < _maxConnections; i++ )
   {
      _connectionSemaphore.wait( INFINITE );
   }

   BaseConnection * connection;

   // destroy queued connections
   while ( !_connectionQueue.empty( ) )
   {
      connection = _connectionQueue.front( );
      _connectionQueue.pop( );

      try
      {
         _connectionFactory->destroyConnection( connection );
      }
      catch ( ... ) //ignore exceptions
      {
      }

      _connectionCount--;
   }

   delete _connectionFactory;
}

BaseConnection *
PooledHostConnectionManager::getConnection( void )
{
   // prevent more than _maxConnections concurrent
   if ( _connectionSemaphore.wait( _timeout ) != WAIT_OBJECT_0 )
   {
      throw DString( I_( "Timed out waiting for a connection." ) );
   }

   // get exclusive lock on the queue and pop a connection off
   // if the queue is empty, create a new one
   CriticalSection cs( _connectionMutex );
   BaseConnection *connection;

   if ( _connectionQueue.empty( ) )
   {
      try
      {
         connection = _connectionFactory->createConnection( _hostId );
         connection->setHostConnectionManagerId( _hostConnectionManagerId );
      }
      catch ( ConditionException & ce )
      {
         _connectionSemaphore.release( 1 );
         throw ce;
      }
      catch ( ... )
      {
         _connectionSemaphore.release( 1 );
         throw;
      }

      _connectionCount++;
   }
   else
   {
      connection = _connectionQueue.front( );
      _connectionQueue.pop( );
   }

   _connectionsInUse++;

   if ( _intervalMaxConnectionsInUse < _connectionsInUse )
      _intervalMaxConnectionsInUse = _connectionsInUse;

   return connection;
}

void
PooledHostConnectionManager::freeConnection( BaseConnection *connection )
{
   if ( connection->isStale( ) ) // Don't put stale connections back on the queue.
   {
      try
      {
         _connectionFactory->destroyConnection( connection );
      }
      catch ( ... ) //ignore exceptions
      {
      }

      CriticalSection cs( _connectionMutex );

      _connectionFailures++;
      _connectionsInUse--;
      _connectionCount--;

      // The connection semaphore is not released.
   }
   else
   {
      // Get exclusive lock on the queue and push on the connection.
      CriticalSection cs( _connectionMutex );

      connection->freeResponse( );
      _connectionQueue.push( connection );
      _connectionsInUse--;
   }

   // Release the connection semaphore.
   _connectionSemaphore.release( 1 );
}

void PooledHostConnectionManager::run( )
{
   while ( WAIT_TIMEOUT == _shutdownEvent.wait( _reaperInterval ) )
   {
      CriticalSection cs( _connectionMutex );

      // calculate target connection count
      int targetConnectionCount = _intervalMaxConnectionsInUse;

      if ( targetConnectionCount < _minConnections )
         targetConnectionCount = _minConnections;

      // Remove connections from the queue until we have reached the target to a maximum of _reaperCount.
      // _connectionQueue.empty( ) should, in theory never occur - but check it anyway...
      for ( int i = 0; _connectionCount > targetConnectionCount && i < _reaperCount && !_connectionQueue.empty( ); i++ )
      {
         // pop the top and destroy
         BaseConnection *connection = _connectionQueue.front( );
         _connectionQueue.pop( );

         try
         {
            _connectionFactory->destroyConnection( connection );
         }
         catch ( ... ) //ignore exceptions
         {
         }

         _connectionCount--;
      }

      // reset the interval max.
      _intervalMaxConnectionsInUse = 0;

   }
}

const DString &
PooledHostConnectionManager::getHostConnectionManagerId( ) const
{
   return _hostConnectionManagerId;
}

const DString &
PooledHostConnectionManager::getHostId( ) const
{
   return _hostId;
}

int
PooledHostConnectionManager::getMaxConnections( ) const
{
   return _maxConnections;
}

int
PooledHostConnectionManager::getMinConnections( ) const
{
   return _minConnections;
}

int
PooledHostConnectionManager::getConnectionCount( ) const
{
   return _connectionCount;
}

int
PooledHostConnectionManager::getConnectionsInUse( ) const
{
   return _connectionsInUse;
}

int
PooledHostConnectionManager::getConnectionFailures( ) const
{
   return _connectionFailures;
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
// $Log:   Y:/VCS/iFastAWD/diview/PooledHostConnectionManager.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:00   kovacsro
// Initial revision.
//
//   Rev 1.1   Jun 28 2001 16:49:28   DT11159
//Renamed some classes.
//
//   Rev 1.0   May 18 2001 11:40:16   DT11159
// 
//
//
