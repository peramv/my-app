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
// ^FILE   :  ReservedHostConnectionManager.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  March 2000
//
// ----------------------------------------------------------
#define DIVIEW_DLL

#ifndef SRCPRAG_h
   #include "srcprag.h"
#endif
#include <ctime>
#ifndef RESERVEDHOSTCONNECTIONMANAGER_HPP
   #include "reservedhostconnectionmanager.hpp"
#endif
#ifndef BASE_H //for the conditons
   #include "base.h"
#endif
#ifndef DIVIEW_H
   #include "diview.h"
#endif
#ifndef BASECONNECTION_HPP
   #include "baseconnection.hpp"
#endif
#ifndef BASECONNECTIONFACTORY_HPP
   #include "baseconnectionfactory.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif

namespace
{
   const I_CHAR *CLASSNAME = I_( "ReservedHostConnectionManager" );
}

ReservedHostConnectionManager::ReservedHostConnectionManager( const DString & hostConnectionManagerId,
                                                              const DString & hostId,
                                                              BaseConnectionFactory * connectionFactory,
                                                              int maxConnections,
                                                              unsigned long timeout ) :
_hostConnectionManagerId( hostConnectionManagerId ),
_hostId( hostId ),
_connectionFactory( connectionFactory ),
_maxConnections( maxConnections ),
_timeout( ( timeout == 0 || timeout > ( INFINITE / 1000 ) ) ? INFINITE : timeout * 1000 ),
_connectionCount( 0 ),
_connectionsInUse( 0 ),
_connectionFailures( 0 ),
_connectionMutex( ),
_connectionSemaphore( 0, maxConnections ),
_reservedEvent( true ),
_connectionEvent( true ),
_connectionQueue( ),
_reservedQueue( )
{
   // Attempt to initialize max connections.
   CriticalSection cs( _connectionMutex );

   BaseConnection * connection;

   for ( int i = 0; i < _maxConnections; i++ )
   {
      connection = _connectionFactory->createConnection( _hostId );
      connection->setHostConnectionManagerId( _hostConnectionManagerId );

      _connectionQueue.push( connection );
      _connectionCount++;
      _connectionSemaphore.release( 1 );
   }
}

ReservedHostConnectionManager::ReservedHostConnectionManager( ) :
_hostId( NULL_STRING ),
_connectionFactory( NULL ),
_maxConnections( 0 ),
_timeout( INFINITE ),
_connectionCount( 0 ),
_connectionsInUse( 0 ),
_connectionFailures( 0 ),
_connectionMutex( ),
_connectionSemaphore( 0, 0 ),
_reservedEvent( true ),
_connectionQueue( ),
_reservedQueue( )
{
}

ReservedHostConnectionManager::~ReservedHostConnectionManager( )
{
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

DString
ReservedHostConnectionManager::getReservation( )
{
   DString connectionName;
   time_t tmStart;
   time_t tmEnd;
   unsigned long elapsed;
   BaseConnection * connection;

   tmStart = 0;
   elapsed = 0;

   if ( _timeout != INFINITE )
   {
      time( &tmStart );
   }

   while ( true )
   {
      connection = getNonReservedConnection( _timeout - elapsed );

      if ( connection )
      {
         //
         // Mark connection as reserved.
         // Get the name of the connection.
         // Free the connection into the reserved queue.
         //

         connection->setReserved( true );
         connection->getName( connectionName );
         freeConnection( connection );

         break;
      }

      if ( _timeout == INFINITE )
      {
         if ( _connectionEvent.wait( _timeout ) != WAIT_OBJECT_0 )
         {
            THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                     I_( "ReservedHostConnectionManager::getReservation" ),
                                     ERR_RESERVATION_TIMEOUT, NULL_STRING, NULL );
         }
      }
      else
      {
         time( &tmEnd );
         elapsed = ( unsigned long ) ( 1000.0 * difftime( tmEnd, tmStart ) );

         // This will let it have one more try at 0 if there is still not a
         // free connection it will timeout immediately.
         if ( elapsed >= _timeout )
         {
            elapsed = _timeout;
         }

         if ( _connectionEvent.wait( _timeout - elapsed ) != WAIT_OBJECT_0 )
         {
            THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                     I_( "ReservedHostConnectionManager::getReservation" ),
                                     ERR_RESERVATION_TIMEOUT, NULL_STRING, NULL );
         }

         time( &tmEnd );
         elapsed = ( unsigned long ) ( 1000.0 * difftime( tmEnd, tmStart ) );

         if ( elapsed >= _timeout )
         {
            elapsed = _timeout;
         }
      }
   }

   return( connectionName );
}

void
ReservedHostConnectionManager::freeReservation( const DString & connectionName )
{
   if ( connectionName.size( ) )
   {
      BaseConnection * connection;

      // Get the reserved connection.
      connection = getConnection( connectionName );

      // Mark connection as non-reserved.
      connection->setReserved( false );

      freeConnection( connection );
   }

   return;
}

BaseConnection *
ReservedHostConnectionManager::getConnection( const DString & connectionName )
{
   BaseConnection * connection;
   time_t tmStart;
   time_t tmEnd;
   unsigned long elapsed;
   DString tempName;

   connection = NULL;
   tmStart = 0;
   elapsed = 0;

   if ( _timeout != INFINITE )
   {
      time( &tmStart );
   }

   while ( true )
   {
      if ( _connectionSemaphore.wait( _timeout - elapsed ) != WAIT_OBJECT_0 )
      {
         THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                  I_( "ReservedHostConnectionManager::getReservation" ),
                                  ERR_CONNECTION_TIMEOUT, NULL_STRING, NULL );
      }

      if ( connectionName.size( ) )
      {
         {
            CriticalSection cs( _connectionMutex );

            //
            // Search for the reserved connection with matching connection name.
            //

            int n;
            BaseConnection * tempConnection;

            n = _reservedQueue.size( );

            while ( n-- )
            {
               tempConnection = _reservedQueue.front( );
               _reservedQueue.pop( );

               if ( connectionName == tempConnection->getName( tempName ) )
               {
                  connection = tempConnection;
                  break;
               }

               _reservedQueue.push( tempConnection );
            }

            //
            // If not found, release the connection semaphore and reset the
            // event semaphore.
            //

            if ( connection )
            {
               _connectionsInUse++;
            }
            else
            {
               // We didn't find the connection so release the semaphore.
               _connectionSemaphore.release( 1 );

               // Reset the event semaphore.
               _reservedEvent.reset( );
            }
         }

         if ( connection )
         {
            break;
         }
         else
         {
            // Wait for a reserved connection to be released.
            if ( _reservedEvent.wait( _timeout - elapsed ) != WAIT_OBJECT_0 )
            {
               THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                        I_( "ReservedHostConnectionManager::getReservation" ),
                                        ERR_CONNECTION_TIMEOUT, NULL_STRING, NULL );
            }
         }
      }
      else
      {
         CriticalSection cs( _connectionMutex );

         if ( _connectionQueue.size( ) )
         {
            connection = _connectionQueue.front( );
            _connectionQueue.pop( );
            break;
         }
         else if ( _reservedQueue.size( ) )
         {
            connection = _reservedQueue.front( );
            _reservedQueue.pop( );
            break;
         }
         else
         {
            //
            // Shouldn't get here.  The connection semaphore should only allow
            // us to get here if there is a free connection.
            //

            THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                     I_( "ReservedHostConnectionManager::getReservation" ),
                                     ERR_CONNECTION_TIMEOUT, NULL_STRING, NULL );
         }

         _connectionsInUse++;
      }

      if ( _timeout != INFINITE )
      {
         time( &tmEnd );
         elapsed = ( unsigned long ) ( 1000.0 * difftime( tmEnd, tmStart ) );

         if ( elapsed >= _timeout )
         {
            THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                                     I_( "ReservedHostConnectionManager::getReservation" ),
                                     ERR_CONNECTION_TIMEOUT, NULL_STRING, NULL );
         }
      }
   }

   return( connection );
}

BaseConnection *
ReservedHostConnectionManager::getConnection( )
{
   return( getConnection( NULL_STRING ) );
}

BaseConnection *
ReservedHostConnectionManager::getNonReservedConnection(  unsigned long timeout )
{
   BaseConnection * connection;

   connection = NULL;

   if ( _connectionSemaphore.wait( timeout ) != WAIT_OBJECT_0 )
   {
      THROWEXCEPTIONCONDITION( DIVIEW_CONDITION,
                               I_( "ReservedHostConnectionManager::getReservation" ),
                               ERR_NON_RESERVED_CONNECTION_TIMEOUT, NULL_STRING, NULL );
   }

   CriticalSection cs( _connectionMutex );

   if ( _connectionQueue.size( ) )
   {
      connection = _connectionQueue.front( );
      _connectionQueue.pop( );
      _connectionsInUse++;
   }
   else
   {
      _connectionSemaphore.release( 1 );
      _connectionEvent.reset( );
   }

   return( connection );
}

void
ReservedHostConnectionManager::freeConnection( BaseConnection * connection )
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

      if ( connection->isReserved( ) )
      {
         _reservedQueue.push( connection );
         _reservedEvent.set( );
      }
      else
      {
         _connectionQueue.push( connection );
         _connectionEvent.set( );
      }

      _connectionsInUse--;
   }

   // Release the connection semaphore.
   _connectionSemaphore.release( 1 );
}

const DString &
ReservedHostConnectionManager::getHostConnectionManagerId( ) const
{
   return _hostConnectionManagerId;
}

const DString &
ReservedHostConnectionManager::getHostId( ) const
{
   return _hostId;
}

int
ReservedHostConnectionManager::getMaxConnections( ) const
{
   return _maxConnections;
}

int
ReservedHostConnectionManager::getMinConnections( ) const
{
   //
   // For reserved host connection managers, the minimum number of connections
   // is equal to the maximum number of connections.
   //

   return _maxConnections;
}

int
ReservedHostConnectionManager::getConnectionCount( ) const
{
   return _connectionCount;
}

int
ReservedHostConnectionManager::getConnectionsInUse( ) const
{
   return _connectionsInUse;
}

int
ReservedHostConnectionManager::getConnectionFailures( ) const
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
// $Log:   Y:/VCS/iFastAWD/diview/ReservedHostConnectionManager.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:00   kovacsro
// Initial revision.
//
//   Rev 1.3   Aug 14 2001 15:20:06   DT11159
//The "connections in use" counter should not be modified
//outside the critical section.
//
//   Rev 1.2   Aug 14 2001 15:01:24   DT11159
//Fixed bug in getConnection( const DString & ). The wrong variable was
//pushed onto the reserved queue.
//
//   Rev 1.1   Aug 03 2001 17:07:16   DT11159
//Added _connectionEvent and fixed a deadlock in getReservation( ).
//Added conditions ERR_CONNECTION_TIMEOUT,
//ERR_NON_RESERVED_CONNECTION_TIMEOUT,
//and ERR_RESERVATION_TIMEOUT.
//
//
//   Rev 1.0   May 18 2001 11:40:28   DT11159
//
//
//
