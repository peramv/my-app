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
// ^FILE   :  BFConnectionManager.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  March 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "bfconnectionmanager.hpp"
#include <base.h>
#include "bfconnection.hpp"
#include "bfconnectionfactory.hpp"
#include "bfconnectionmonitor.hpp"
#include <conditionmanager.hpp>
#include "pooledhostconnectionmanager.hpp"
#include "simplehostconnectionmanager.hpp"

namespace
{
   const I_CHAR *CLASSNAME = I_( "BFConnectionManager" );
   const I_CHAR *const GETINSTANCE = I_( "getInstance" );

   BFCritSec g_hostManagerMapLock;
}

namespace CND
{
   extern const I_CHAR *BFCONMGR_CONDITION;
   extern const long ERR_HOST_CONNECTION_MGR_NOT_FOUND;
}

//initialize the static members
BFConnectionManager *BFConnectionManager::_pInstance = NULL;

//******************************************************************************
BFConnectionManager *
BFConnectionManager::getInstance( void )
{
   TRACE_METHOD( CLASSNAME, GETINSTANCE );

   if( !BFConnectionManager::_pInstance )
   {
      BFConnectionManager::_pInstance = new BFConnectionManager();
      if( !BFConnectionManager::_pInstance )
      {
         THROWFROMBASE( CND::BFCONMGR_CONDITION, GETINSTANCE, BASE_ALLOC_FAIL );
         return(NULL);
      }
   }
   return(BFConnectionManager::_pInstance);
}

//******************************************************************************
void
BFConnectionManager::killInstance()
{
   if( BFConnectionManager::_pInstance )
   {
      delete BFConnectionManager::_pInstance;
      BFConnectionManager::_pInstance = NULL;
   }
}

//******************************************************************************
BFConnection *
BFConnectionManager::getConnection( const DStringA &hostId )
{
   BFHostConnectionManager *hostManager = getHostConnectionManager(hostId);

   if( NULL == hostManager )
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("getConnection"), CND::ERR_HOST_CONNECTION_MGR_NOT_FOUND );

   return(hostManager->getConnection());
}

//******************************************************************************
void
BFConnectionManager::freeConnection(BFConnection *connection)
{
   BFHostConnectionManager *hostManager = getHostConnectionManager( connection->getHostId() );

   if( NULL == hostManager )
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("freeConnection"), CND::ERR_HOST_CONNECTION_MGR_NOT_FOUND );

   hostManager->freeConnection(connection);
}

//******************************************************************************
void
BFConnectionManager::createHostConnectionManager(const DStringA &hostId, BFConnectionFactory *connectionFactory, int maxConnections, bool persistentConnections, int minConnections)
{
   BFHostConnectionManager *hostManager;

   // construct the appropriate host manager
   if( persistentConnections )
   {
      hostManager = new PooledHostConnectionManager(hostId, connectionFactory, minConnections, maxConnections);
   }
   else
   {
      hostManager = new SimpleHostConnectionManager(hostId, connectionFactory, maxConnections);
   }

   {
      BFGuard cs( g_hostManagerMapLock );

      // if there is already one destroy it...
      destroyHostConnectionManager( hostId );

      // notify monitor if there is one.
      if( NULL != _connectionMonitor )
      {
         _connectionMonitor->registerHostConnectionManager( hostManager );
      }

      // add new host manager to the map
      _hostManagerMap.insert( HOST_CONNECTION_MGR_MAP_VALUE_TYPE(hostId, hostManager) );
   }
}

//******************************************************************************
void
BFConnectionManager::destroyHostConnectionManager(const DStringA &hostId)
{
   BFHostConnectionManager *hostManager = NULL;
   {
      BFGuard cs( g_hostManagerMapLock );
      HOST_CONNECTION_MGR_MAP_ITER iterator = _hostManagerMap.find(hostId);

      if( _hostManagerMap.end() == iterator ) // nothing to do
      {
         return;
      }

      hostManager = (*iterator).second;

      // remove host manager from map
      _hostManagerMap.erase(iterator);

      // notify monitor if there is one.
      if( NULL != _connectionMonitor )
      {
         _connectionMonitor->unregisterHostConnectionManager( hostManager );
      }

   }

   // delete after freeing the map lock so we do not hold up
   // access for other threads
   delete hostManager;
}

//******************************************************************************
void
BFConnectionManager::setConnectionMonitor(BFConnectionMonitor *connectionMonitor)
{
   HOST_CONNECTION_MGR_MAP_ITER iterator;

   BFConnectionMonitor *oldConnectionMonitor = _connectionMonitor;
   _connectionMonitor  = connectionMonitor;

   { // critical section
      BFGuard cs( g_hostManagerMapLock );
      // let old monitor remove host managers
      if( NULL != oldConnectionMonitor )
         for( iterator = _hostManagerMap.begin(); _hostManagerMap.end() != iterator; iterator++ )
            oldConnectionMonitor->unregisterHostConnectionManager( (*iterator).second );

      // let new monitor add host managers
      if( NULL != _connectionMonitor )
      {
         for( iterator = _hostManagerMap.begin(); _hostManagerMap.end() != iterator; iterator++ )
         {
            _connectionMonitor->registerHostConnectionManager( (*iterator).second );
         }
      }
   }

   delete oldConnectionMonitor;
}

//******************************************************************************
const BFConnectionMonitor *
BFConnectionManager::getConnectionMonitor() const
{
   return(_connectionMonitor);
}

//******************************************************************************
BFHostConnectionManager *
BFConnectionManager::getHostConnectionManager(const DStringA &hostId)
{
   BFGuard cs( g_hostManagerMapLock );
   HOST_CONNECTION_MGR_MAP_ITER iterator = _hostManagerMap.find(hostId);

   if( _hostManagerMap.end() == iterator )
   {
      return(NULL);
   }
   else
   {
      return(*iterator).second;
   }
}

//******************************************************************************
BFConnectionManager::BFConnectionManager()
:  _hostManagerMap()
, _connectionMonitor(NULL)
{
}

//******************************************************************************
BFConnectionManager::~BFConnectionManager()
{

   delete _connectionMonitor;

   // free all Host managers
   HOST_CONNECTION_MGR_MAP_ITER iterator = _hostManagerMap.begin();

   while( _hostManagerMap.end() != iterator )
   {
      delete (*iterator).second;
      iterator = _hostManagerMap.erase(iterator);
   }

}

//******************************************************************************
bool BFConnectionManager::recycle(const DStringA &hostId)
{
   BFHostConnectionManager *hostManager = getHostConnectionManager(hostId);

   if( NULL == hostManager )
   {
      THROWFROMFILE2( CND::BFCONMGR_CONDITION, CLASSNAME, I_("recycle"), CND::ERR_HOST_CONNECTION_MGR_NOT_FOUND );
   }

   return(hostManager->recycle());
}

//******************************************************************************
unsigned int BFConnectionManager::hostCount( void )
{
   BFGuard cs( g_hostManagerMapLock );
   return( _hostManagerMap.size() );
}

//******************************************************************************
bool BFConnectionManager::ok( const DStringA &hostId )
{
   BFGuard cs( g_hostManagerMapLock );
   HOST_CONNECTION_MGR_MAP_ITER iterator = _hostManagerMap.find( hostId );

   if( _hostManagerMap.end() == iterator )
   {
      return( false );
   }
   else
   {
      BFHostConnectionManager* pHostManager = (*iterator).second;
      return( true ); //pHostManager->ok() );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfconmgr/BFConnectionManager.cpp-arc  $
//
//   Rev 1.10   Feb 27 2004 14:14:20   PURDYECH
//Some functions didn't have guards on the std::map
// 
//    Rev 1.9   Oct 09 2002 17:40:18   PURDYECH
// New PVCS Database
// 
//    Rev 1.8   Sep 04 2002 16:32:16   SMITHDAV
// Fix deadlock on shutdown.
// 
//    Rev 1.7   22 May 2002 17:54:54   PURDYECH
// BFData Implementation
// 
//    Rev 1.6   Mar 04 2002 12:30:04   IVESPAUL
// Handle dead AS/400 listeners for both ChangeHostMode and initial startup + 
// Logging changes.
//
//    Rev 1.5   Oct 22 2001 17:17:26   HUDAVID
// Connection Recycle code.
//
//    Rev 1.4   May 22 2001 13:49:26   MCNABBGL
// server monitoring functionality, explicit server registration with connection manager, fastrequestor modifications
//
//    Rev 1.3   03 May 2001 14:03:02   SMITHDAV
// Session management restructuring.
//
//    Rev 1.2   06 Dec 2000 11:47:42   SMITHDAV
// Update monitoring console; Added DataBroker monitor.
//
//    Rev 1.1   04 Dec 2000 11:38:16   SMITHDAV
// Add console connection monitoring support.
//
//    Rev 1.0   23 Oct 2000 20:10:46   SMITHDAV
// Initial revision.
 //
 //    Rev 1.3   May 03 2000 14:52:48   SMITHDAV
 // Move hostManager delete outside of critical section in destroyHostManager.
 //
 //    Rev 1.2   May 02 2000 17:23:26   DT24433
 // changed to use Infra CriticalSection
//
*/