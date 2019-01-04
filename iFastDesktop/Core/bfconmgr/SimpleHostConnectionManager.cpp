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
// ^FILE   :  SimpleHostConnectionManager.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  March 2000
//
// ----------------------------------------------------------
#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif
#ifndef SIMPLEHOSTCONNECTIONMANAGER_HPP
   #include "SimpleHostConnectionManager.hpp"
#endif
#ifndef BASE_H //for the conditons
   #include <base.h>
#endif
#ifndef CONDITIONMANAGER_HPP
   #include <conditionmanager.hpp>
#endif
#ifndef BFCONNECTIONFACTORY_HPP
   #include "BFConnectionFactory.hpp"
#endif
#ifndef BFCONNECTION_HPP
   #include "BFConnection.hpp"
#endif

namespace
{
   const I_CHAR *CLASSNAME = I_( "SimpleHostConnectionManager" );
}


SimpleHostConnectionManager::SimpleHostConnectionManager(const DStringA &hostId, BFConnectionFactory *connectionFactory, int maxConnections)
: BFHostConnectionManager( connectionFactory ) 
, _hostId(hostId)
, _maxConnections(maxConnections)
, _connectionCount(0)
, _connectionFailures(0)
, _connectionSemaphore(maxConnections, maxConnections)
{
}

SimpleHostConnectionManager::SimpleHostConnectionManager()
: BFHostConnectionManager( NULL ) 
, _hostId("")
, _maxConnections(0)
, _connectionCount(0)
, _connectionFailures(0)
, _connectionSemaphore(0, 0)
{
}

SimpleHostConnectionManager::~SimpleHostConnectionManager()
{
   // wait for all connections to be freed and block subsequent gets
   for( int i=0; i<_maxConnections; i++ )
      _connectionSemaphore.wait( 20000 );
}

BFConnection *
SimpleHostConnectionManager::getConnection( void )
{
   // prevent more that _maxConnections concurrent
   _connectionSemaphore.wait( INFINITE ); 

   BFConnection * connection;

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
   return(connection);
}

void 
SimpleHostConnectionManager::freeConnection(BFConnection *connection)
{
   if( connection->isStale() )
      _connectionFailures++;

   try
   {
      _connectionFactory->destroyConnection( connection );
   }
   catch( ... ) //ignore exceptions
   {
   }

   _connectionCount--;

   // release the semaphore 
   _connectionSemaphore.release( 1 ); 
}

const DStringA &
SimpleHostConnectionManager::getHostId() const
{
   return(_hostId);
}

int
SimpleHostConnectionManager::getMaxConnections() const
{
   return(_maxConnections);
}

int
SimpleHostConnectionManager::getMinConnections() const
{
   return(0);
}

int
SimpleHostConnectionManager::getConnectionCount() const
{
   return(_connectionCount);
}

int
SimpleHostConnectionManager::getConnectionsInUse() const
{
   return(_connectionCount);
}

int 
SimpleHostConnectionManager::getConnectionFailures() const
{
   return(_connectionFailures);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/SimpleHostConnectionManager.cpp-arc  $
// 
//    Rev 1.5   Oct 09 2002 17:40:20   PURDYECH
// New PVCS Database
// 
//    Rev 1.4   Jun 26 2001 12:54:34   PURDYECH
// Infrastructure Release 1.9 Integration.
//
