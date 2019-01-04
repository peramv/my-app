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
#include <srcprag.h>
#include "pooledhostconnectionmanager.hpp"
#include <base.h>
#include "bfconnection.hpp"
#include "bfconnectionfactory.hpp"
#include <conditionmanager.hpp>
#include <bf/log/log.hpp>

namespace
{
   const I_CHAR *CLASSNAME = I_( "PooledHostConnectionManager" );
}


PooledHostConnectionManager::PooledHostConnectionManager(const DStringA &hostId, BFConnectionFactory *connectionFactory, int minConnections, int maxConnections)
: BFHostConnectionManager( connectionFactory )
, BFThread()
, _connectionQueueLock()
, _hostId(hostId)
, _minConnections(minConnections)
, _maxConnections(maxConnections)
, _connectionCount(0)
, _connectionsInUse(0)
, _connectionFailures(0)
, _intervalMaxConnectionsInUse(0)
, _connectionSemaphore(maxConnections, maxConnections)
, _connectionQueue()
, _shutdownEvent(true)
{
   start(); // start the reaper

   // Attempt to initialize min connections.
   // Do not throw if unsuccessful - perhaps server is down - no need to give-up yet
   BFGuard cs( _connectionQueueLock );

   BFConnection *connection;
   for( int i=0; i< _minConnections; i++ )
   {
      try
      {
         connection = _connectionFactory->createConnection(_hostId);
      }
      catch( ... )
      {
         return;
      }

      _connectionQueue.push(connection);
      _connectionCount++;
   }
}

PooledHostConnectionManager::PooledHostConnectionManager()
: BFHostConnectionManager( NULL )
, BFThread()
, _connectionQueueLock()
, _hostId("")
, _minConnections(0)
, _maxConnections(0)
, _connectionCount(0)
, _connectionsInUse(0)
, _connectionFailures(0)
, _intervalMaxConnectionsInUse(0)
, _connectionSemaphore(0, 0)
, _connectionQueue()
, _shutdownEvent(true)
{
}

PooledHostConnectionManager::~PooledHostConnectionManager()
{
   _shutdownEvent.set(); // signal the reaper to shutdown
   wait(INFINITE); // wait for the reaper to shutdown

   // wait for all connections to be freed and block subsequent gets
   for( int i=0; i<_maxConnections; i++ )
      _connectionSemaphore.wait( 20000 );

   // destroy queued connections
   while( !_connectionQueue.empty() )
   {
      BFConnection *connection = _connectionQueue.front();
      _connectionQueue.pop();

      try
      {
         _connectionFactory->destroyConnection( connection );
      }
      catch( ... ) //ignore exceptions
      {
      }

      _connectionCount--;
   }
}

BFConnection *
PooledHostConnectionManager::getConnection( void )
{
   // prevent more that _maxConnections concurrent
   _connectionSemaphore.wait( INFINITE );

   // get exclusive lock on the queue and pop a connection off
   // if the queue is empty, create a new one
   BFGuard cs( _connectionQueueLock );
   BFConnection *connection;

   if( _connectionQueue.empty() )
   {
      bf::log::LogStream ls( bf::log::databroker );
      ls << bf::log::information;
      ls << I_("No free connections.  Count: ") << _connectionCount << I_(", InUse: ") << _connectionsInUse << bf::log::endlf;


      try
      {
         connection = _connectionFactory->createConnection(_hostId);
      }
      catch( ConditionException &ce )
      {
         _connectionSemaphore.release( 1 );
         throw ce;
      }
      catch( ... )
      {
         _connectionSemaphore.release( 1 );
         throw;
      }

      _connectionCount++;
   }
   else
   {
      connection = _connectionQueue.front();
      _connectionQueue.pop();
   }

   _connectionsInUse++;

   if( _intervalMaxConnectionsInUse < _connectionsInUse )
      _intervalMaxConnectionsInUse = _connectionsInUse;

   _setInUse.insert( connection );
   return(connection);
}

void
PooledHostConnectionManager::freeConnection(BFConnection *connection)
{
   if( connection->isStale() ) // don't put stale connections back on the queue
   {

      try
      {
         _connectionFactory->destroyConnection( connection );
      }
      catch( ... ) //ignore exceptions
      {
      }

      BFGuard cs( _connectionQueueLock );

      _connectionFailures++;
      _connectionsInUse--;
      _connectionCount--;

      // remove from the inUse set
      std::set< BFConnection* >::iterator itInUse = _setInUse.find( connection );
      if( _setInUse.end() != itInUse )
      {
         _setInUse.erase( itInUse );
      }
   }
   else
   {
      BFGuard cs( _connectionQueueLock );

      if( connection->isRecycleRequired() )
      {
         connection->recycle();
      }
      // remove from the inUse set
      std::set< BFConnection* >::iterator itInUse = _setInUse.find( connection );
      if( _setInUse.end() != itInUse )
      {
         _setInUse.erase( itInUse );
      }

      // get exclusive lock on the queue and push the connection on
      _connectionQueue.push(connection);
      _connectionsInUse--;
   }

   // release the semaphore
   _connectionSemaphore.release( 1 );
}

void PooledHostConnectionManager::run()
{
#ifdef _DEBUG
   bfutil::setThreadName( -1, "HostConn" );
#endif

   int targetConnectionCount_save = 0;
   int connectionCount_save = 0;
   int connectionQueueSize_save = 0;
   int connectionsInUse_save = 0;

   while( !_shutdownEvent.wait(5000) )
   {
      BFGuard cs( _connectionQueueLock );

      bf::log::LogStream ls( bf::log::databroker );
      ls << bf::log::information;

      // calculate target connection count
      int targetConnectionCount = _intervalMaxConnectionsInUse;

      if( targetConnectionCount < _minConnections )
         targetConnectionCount = _minConnections;

      if( targetConnectionCount != targetConnectionCount_save ||
         _connectionCount != connectionCount_save ||
         _connectionQueue.size() != connectionQueueSize_save ||
         _connectionsInUse != connectionsInUse_save ) {
         ls << I_("Connection Reaper.  Target: ") << targetConnectionCount 
            << I_(", Current: ") << _connectionCount 
            << I_(", Queue: ") << _connectionQueue.size() 
            << I_(", InUse: ") << _connectionsInUse
            << bf::log::endlf;
      }
      targetConnectionCount_save = targetConnectionCount;
      connectionCount_save = _connectionCount;
      connectionQueueSize_save = _connectionQueue.size();
      connectionsInUse_save = _connectionsInUse;

      // remove connections from the queue until we have reached the target to a maimum of 5
      // _connectionQueue.empty() should, in theory never occur - but check it anyways...
      for( int i=0; _connectionCount>targetConnectionCount && i<5 && !_connectionQueue.empty(); i++ )
      {
         // pop the top and destroy
         BFConnection *connection = _connectionQueue.front();
         _connectionQueue.pop();

         try
         {
            _connectionFactory->destroyConnection( connection );
         }
         catch( ... ) //ignore exceptions
         {
         }

         _connectionCount--;
      }

      // reset the interval max.
      _intervalMaxConnectionsInUse = 0;

   }
}

const DStringA &
PooledHostConnectionManager::getHostId() const
{
   return(_hostId);
}

int
PooledHostConnectionManager::getMaxConnections() const
{
   return(_maxConnections);
}

int
PooledHostConnectionManager::getMinConnections() const
{
   return(_minConnections);
}

int
PooledHostConnectionManager::getConnectionCount() const
{
   return(_connectionCount);
}

int
PooledHostConnectionManager::getConnectionsInUse() const
{
   return(_connectionsInUse);
}

int
PooledHostConnectionManager::getConnectionFailures() const
{
   return(_connectionFailures);
}

bool PooledHostConnectionManager::recycle()
{
   BFGuard cs( _connectionQueueLock );

   // go through the connection queue (not inUse) and recycle each one
   CONNECTION_QUEUE::size_type cConnections = _connectionQueue.size();
   CONNECTION_QUEUE::size_type iConnection = 0;
   for( iConnection = 0; iConnection < cConnections; ++iConnection )
   {
      BFConnection *pConnection = _connectionQueue.front();
      pConnection->recycle();
      _connectionQueue.pop();
      _connectionQueue.push( pConnection );
   }

   // mark the in-use ones as requiring recycling the next time they are freed to the pool
   std::set< BFConnection* >::iterator itInUse = _setInUse.begin();

   for( ; itInUse != _setInUse.end(); ++itInUse )
   {
      BFConnection *pConnection = (*itInUse);
      pConnection->setRecycleRequired();
   }

   return(true);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfconmgr/PooledHostConnectionManager.cpp-arc  $
//
//   Rev 1.14   Mar 14 2007 10:21:16   purdyech
//Added logging for Reaper thread
//
//   Rev 1.13   Mar 13 2007 13:54:40   purdyech
//Added logging
//
//   Rev 1.12   Dec 10 2004 10:44:50   purdyech
//PET910 - Fixed shoddy recycle logic
//
//   Rev 1.11   May 02 2003 15:46:32   PURDYECH
//Changed some thread naming logic for debugging.
// 
//    Rev 1.10   Oct 09 2002 17:40:20   PURDYECH
// New PVCS Database
// 
//    Rev 1.9   22 May 2002 17:54:54   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   Mar 04 2002 12:30:04   IVESPAUL
// Handle dead AS/400 listeners for both ChangeHostMode and initial startup + 
// Logging changes.
//
//    Rev 1.7   Oct 22 2001 17:17:26   HUDAVID
// Connection Recycle code.
//
//    Rev 1.6   03 Oct 2001 15:09:54   SMITHDAV
// Syncronization changes and Job Queue changes
//
//    Rev 1.5   Jun 27 2001 20:07:22   PURDYECH
// Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
//
//    Rev 1.4   Jun 26 2001 12:54:32   PURDYECH
// Infrastructure Release 1.9 Integration.
//
//    Rev 1.3   03 May 2001 14:03:02   SMITHDAV
// Session management restructuring.
//
//    Rev 1.2   04 Dec 2000 11:38:18   SMITHDAV
// Add console connection monitoring support.
//
//    Rev 1.1   29 Nov 2000 11:19:20   SMITHDAV
// Update to stale-out failed connection so they are not reused.
//
//    Rev 1.0   23 Oct 2000 20:10:48   SMITHDAV
// Initial revision.
//
//    Rev 1.4   May 05 2000 11:32:56   SMITHDAV
// Additional exception handling.  This should fix any deadlocks that occur on BFConnectionManager::killInstance()
//
//    Rev 1.3   May 04 2000 13:03:36   SMITHDAV
// Catch exceptions from createConnection() so that we can release a connection semaphore in the case of a failure.
//
//    Rev 1.2   May 03 2000 14:54:18   SMITHDAV
// Reset the intervalMaxConnectionsInUse to 0 after reaper finishes a cycle.
//
//    Rev 1.1   May 02 2000 17:27:50   DT24433
// changed to use Infra CriticalSection
//
*/