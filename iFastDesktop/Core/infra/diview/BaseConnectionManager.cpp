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
 *   Class:   BaseConnectionManager.cpp
 *
 *   @@@Description
 *
 */
#define DIVIEW_DLL

#ifndef SRCPRAG_h
   #include "SrcPrag.h"
#endif
#ifndef BASECONNECTIONMANAGER_HPP
   #include "BaseConnectionManager.hpp"
#endif
#ifndef BASE_H //for the conditons
   #include "base.h"
#endif
#ifndef DIVIEW_H //for the conditons
   #include "diview.h"
#endif

#ifndef BASECONNECTION_HPP
   #include "BaseConnection.hpp"
#endif
#ifndef BASECONNECTIONFACTORY_HPP
   #include "BaseConnectionFactory.hpp"
#endif
#ifndef BASECONNECTIONMONITOR_HPP
   #include "BaseConnectionMonitor.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef CRITICALSECTION_HPP
   #include "CriticalSection.hpp"
#endif
#ifndef POOLEDHOSTCONNECTIONMANAGER_HPP
   #include "PooledHostConnectionManager.hpp"
#endif
#ifndef SIMPLEHOSTCONNECTIONMANAGER_HPP
   #include "SimpleHostConnectionManager.hpp"
#endif
#ifndef RESERVEDHOSTCONNECTIONMANAGER_HPP
   #include "ReservedHostConnectionManager.hpp"
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "BaseConnectionManager" );
   const I_CHAR * const GETINSTANCE = I_( "getInstance" );

   MutexSemaphore g_hostManagerMapLock;
}

//initialize the static members
BaseConnectionManager *BaseConnectionManager::_pInstance = NULL;

//******************************************************************************
BaseConnectionManager *
BaseConnectionManager::getInstance( void )
{
   TRACE_METHOD( CLASSNAME, GETINSTANCE );

   if ( !BaseConnectionManager::_pInstance )
   {
      BaseConnectionManager::_pInstance = new BaseConnectionManager( );
      if ( !BaseConnectionManager::_pInstance )
      {
         THROWFROMBASE( DIVIEW_CONDITION, GETINSTANCE, BASE_ALLOC_FAIL );
         return NULL;
      }
   }
   return BaseConnectionManager::_pInstance;
}

//******************************************************************************
DString
BaseConnectionManager::getReservation( const DString & hostConnectionManagerId )
{
   DString connectionName;

   BaseHostConnectionManager *hostManager = getHostConnectionManager( hostConnectionManagerId );

   if ( NULL == hostManager )
   {
      THROWFROMFILE2( DIVIEW_CONDITION, CLASSNAME, I_( "getReservation" ), ERR_HOST_CONNECTION_MGR_NOT_FOUND );
   }

   connectionName = hostManager->getReservation( );

   return( connectionName );
}

//******************************************************************************
void
BaseConnectionManager::freeReservation( const DString & hostConnectionManagerId,
                                        const DString & connectionName )
{
   if ( connectionName.size( ) )
   {
      BaseHostConnectionManager *hostManager = getHostConnectionManager( hostConnectionManagerId );

      if ( NULL == hostManager )
      {
         THROWFROMFILE2( DIVIEW_CONDITION, CLASSNAME, I_( "freeReservation" ), ERR_HOST_CONNECTION_MGR_NOT_FOUND );
      }

      hostManager->freeReservation( connectionName );
   }

   return;
}

//******************************************************************************
BaseConnection *
BaseConnectionManager::getConnection( const DString & hostConnectionManagerId )
{
   BaseHostConnectionManager *hostManager = getHostConnectionManager( hostConnectionManagerId );

   if ( NULL == hostManager )
   {
      THROWFROMFILE2( DIVIEW_CONDITION, CLASSNAME, I_( "getConnection" ), ERR_HOST_CONNECTION_MGR_NOT_FOUND );
   }

   return hostManager->getConnection( );
}

//******************************************************************************
BaseConnection *
BaseConnectionManager::getConnection( const DString & hostConnectionManagerId,
                                      const DString & connectionName )
{
   BaseConnection * connection;

   if ( connectionName.empty( ) )
   {
      connection = getConnection( hostConnectionManagerId );
   }
   else
   {
      BaseHostConnectionManager * hostManager;

      hostManager = getHostConnectionManager( hostConnectionManagerId );

      if ( NULL == hostManager )
      {
         THROWFROMFILE2( DIVIEW_CONDITION, CLASSNAME, I_( "getConnection" ), ERR_HOST_CONNECTION_MGR_NOT_FOUND );
      }

      connection = hostManager->getConnection( connectionName );
   }

   return connection;
}

//******************************************************************************
void
BaseConnectionManager::freeConnection( BaseConnection *connection )
{
   BaseHostConnectionManager * hostManager;

   hostManager = getHostConnectionManager( connection->getHostConnectionManagerId( ) );

   if ( NULL == hostManager )
   {
      THROWFROMFILE2( DIVIEW_CONDITION, CLASSNAME, I_( "freeConnection" ), ERR_HOST_CONNECTION_MGR_NOT_FOUND );
   }

   hostManager->freeConnection( connection );
}

//******************************************************************************
void
BaseConnectionManager::createHostConnectionManager( const DString & hostConnectionManagerId,
                                                    const DString & hostId,
                                                    BaseConnectionFactory * connectionFactory,
                                                    MANAGER_TYPE type,
                                                    unsigned long timeout,
                                                    int minConnections, // Only used for POOLED manager.
                                                    int reaperInterval, // Only used for POOLED manager.
                                                    int reaperCount )   // Only used for POOLED manager.
{
   BaseHostConnectionManager * hostManager;

   int maxConnections = connectionFactory->getMaxConnectionCount( );
   if ( minConnections > maxConnections )
   {
      minConnections = maxConnections;
   }

   // Construct the appropriate host manager.
   switch ( type )
   {
      case SIMPLE:
         hostManager = new SimpleHostConnectionManager( hostConnectionManagerId, hostId, connectionFactory, maxConnections, timeout );
         break;

      case POOLED:
         hostManager = new PooledHostConnectionManager( hostConnectionManagerId, hostId, connectionFactory, minConnections, maxConnections, timeout, reaperInterval, reaperCount );
         break;

      case RESERVED:
         hostManager = new ReservedHostConnectionManager( hostConnectionManagerId, hostId, connectionFactory, maxConnections, timeout );
         break;

      default:
         hostManager = new SimpleHostConnectionManager( hostConnectionManagerId, hostId, connectionFactory, maxConnections, timeout );
   }

   {
      CriticalSection cs( g_hostManagerMapLock );

      // if there is already one destroy it...
      destroyHostConnectionManager( hostConnectionManagerId );

      // notify monitor if there is one.
      if ( NULL != _connectionMonitor )
      {
         _connectionMonitor->registerHostConnectionManager( hostManager );
      }

      // add new host manager to the map
      _hostManagerMap.insert( HOST_CONNECTION_MGR_MAP::value_type( hostConnectionManagerId, hostManager ) );
   }
}

//******************************************************************************
void
BaseConnectionManager::destroyHostConnectionManager( const DString & hostConnectionManagerId )
{
   BaseHostConnectionManager *hostManager;
   {
      CriticalSection cs( g_hostManagerMapLock );
      HOST_CONNECTION_MGR_MAP::iterator iterator = _hostManagerMap.find( hostConnectionManagerId );

      if ( _hostManagerMap.end( ) == iterator ) // nothing to do
      {
         return;
      }

      hostManager = ( *iterator ).second;

      // remove host manager from map
      _hostManagerMap.erase( iterator );

      // notify monitor if there is one.
      if ( NULL != _connectionMonitor )
         _connectionMonitor->unregisterHostConnectionManager( hostManager );

   }

   // delete after freeing the map lock so we do not hold up
   // access for other threads
   delete hostManager;
}

//******************************************************************************
void
BaseConnectionManager::setConnectionMonitor( BaseConnectionMonitor *connectionMonitor )
{
   HOST_CONNECTION_MGR_MAP::iterator iterator;

   BaseConnectionMonitor *oldConnectionMonitor = _connectionMonitor;
   _connectionMonitor  = connectionMonitor;

   {
      CriticalSection cs( g_hostManagerMapLock );
      // let old monitor remove host managers
      if ( NULL != oldConnectionMonitor )
         for ( iterator = _hostManagerMap.begin( ); _hostManagerMap.end( ) != iterator; iterator++ )
            oldConnectionMonitor->unregisterHostConnectionManager( ( *iterator ).second );

      // let new monitor add host managers
      if ( NULL != _connectionMonitor )
         for ( iterator = _hostManagerMap.begin( ); _hostManagerMap.end( ) != iterator; iterator++ )
            _connectionMonitor->registerHostConnectionManager( ( *iterator ).second );
   }

   delete oldConnectionMonitor;
}

//******************************************************************************
const BaseConnectionMonitor *
BaseConnectionManager::getConnectionMonitor( ) const
{
   return _connectionMonitor;
}

//******************************************************************************
BaseHostConnectionManager *
BaseConnectionManager::getHostConnectionManager( const DString & hostConnectionManagerId )
{
   CriticalSection cs( g_hostManagerMapLock );
   HOST_CONNECTION_MGR_MAP::iterator iterator = _hostManagerMap.find( hostConnectionManagerId );

   if ( _hostManagerMap.end( ) == iterator )
      return NULL;
   else
      return( *iterator ).second;
}

//******************************************************************************
BaseConnectionManager::BaseConnectionManager( )
:  _hostManagerMap( ),
_connectionMonitor( NULL )
{
   m_register.registerSingleton( deregister, this );
}

//******************************************************************************
BaseConnectionManager::~BaseConnectionManager( )
{

   if ( NULL != _connectionMonitor )
      delete _connectionMonitor;

   // free all Host managers
   CriticalSection cs( g_hostManagerMapLock );
   HOST_CONNECTION_MGR_MAP::iterator iterator = _hostManagerMap.begin( );

   while ( _hostManagerMap.end( ) != iterator )
   {
      delete ( *iterator ).second;
      iterator = _hostManagerMap.erase( iterator );
   }

}

void BaseConnectionManager::deregister( void * pObj )
{
   //
   // BaseConnectionManager * p = ( BaseConnectionManager * ) pObj;
   //

   killInstance( );
}

void BaseConnectionManager::killInstance( void )
{
   if ( _pInstance )
   {
      delete _pInstance;
      _pInstance = NULL;
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
// $Log:   Y:/VCS/iFastAWD/diview/BaseConnectionManager.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:23:52   kovacsro
// Initial revision.
//
//   Rev 1.0   May 18 2001 11:39:58   DT11159
// 
//
//
