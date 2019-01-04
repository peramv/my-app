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
#define DIVIEW_DLL

#ifndef SRCPRAG_h
   #include "SrcPrag.h"
#endif
#ifndef SIMPLEHOSTCONNECTIONMANAGER_HPP
   #include "SimpleHostConnectionManager.hpp"
#endif
#ifndef BASE_H //for the conditons
   #include "base.h"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef BASECONNECTIONFACTORY_HPP
   #include "BaseConnectionFactory.hpp"
#endif
#ifndef BASECONNECTION_HPP
   #include "BaseConnection.hpp"
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SimpleHostConnectionManager" );
}


SimpleHostConnectionManager::SimpleHostConnectionManager( const DString & hostConnectionManagerId,
                                                          const DString & hostId,
                                                          BaseConnectionFactory *connectionFactory,
                                                          int maxConnections,
                                                          unsigned long timeout ) :
_hostConnectionManagerId( hostConnectionManagerId ),
_hostId( hostId ),
_connectionFactory( connectionFactory ),
_maxConnections( maxConnections ),
_timeout( ( timeout == 0 || timeout > ( INFINITE / 1000 ) ) ? INFINITE : timeout * 1000 ),
_connectionCount( 0 ),
_connectionFailures( 0 ),
_connectionSemaphore( maxConnections, maxConnections )
{
}

SimpleHostConnectionManager::SimpleHostConnectionManager( ) :
_hostId( NULL_STRING ),
_connectionFactory( NULL ),
_maxConnections( 0 ),
_timeout( INFINITE ),
_connectionCount( 0 ),
_connectionFailures( 0 ),
_connectionSemaphore( 0, 0 )
{
}

SimpleHostConnectionManager::~SimpleHostConnectionManager( )
{
   // wait for all connections to be freed and block subsequent gets
   for ( int i = 0; i < _maxConnections; i++ )
   {
      _connectionSemaphore.wait( INFINITE );
   }

   delete _connectionFactory;

}

BaseConnection *
SimpleHostConnectionManager::getConnection( )
{
   // prevent more that _maxConnections concurrent
   if ( _connectionSemaphore.wait( _timeout ) != WAIT_OBJECT_0 )
   {
      throw DString( I_( "Timed out waiting for a connection." ) );
   }

   BaseConnection * connection;

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
   return connection;
}

void
SimpleHostConnectionManager::freeConnection( BaseConnection * connection )
{
   if ( connection->isStale( ) )
   {
      _connectionFailures++;
   }

   try
   {
      _connectionFactory->destroyConnection( connection );
   }
   catch ( ... ) //ignore exceptions
   {
   }

   _connectionCount--;

   // release the semaphore
   _connectionSemaphore.release( 1 );
}

const DString &
SimpleHostConnectionManager::getHostConnectionManagerId( ) const
{
   return _hostConnectionManagerId;
}

const DString &
SimpleHostConnectionManager::getHostId( ) const
{
   return _hostId;
}

int
SimpleHostConnectionManager::getMaxConnections( ) const
{
   return _maxConnections;
}

int
SimpleHostConnectionManager::getMinConnections( ) const
{
   return 0;
}

int
SimpleHostConnectionManager::getConnectionCount( ) const
{
   return _connectionCount;
}

int
SimpleHostConnectionManager::getConnectionsInUse( ) const
{
   return _connectionCount;
}

int
SimpleHostConnectionManager::getConnectionFailures( ) const
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
// $Log:   Y:/VCS/iFastAWD/diview/SimpleHostConnectionManager.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:04   kovacsro
// Initial revision.
//
//   Rev 1.0   May 18 2001 11:40:40   DT11159
// 
//
//
