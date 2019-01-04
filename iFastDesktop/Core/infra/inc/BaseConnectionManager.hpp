#pragma message( "including "__FILE__ )

#ifndef BASECONNECTIONMANAGER_HPP
   #define BASECONNECTIONMANAGER_HPP

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
   #ifndef DSTRING_HPP
      #include "dstring.hpp"
   #endif

   #ifndef INCLUDED_MAP
      #include <map>
      #define INCLUDED_MAP
   #endif

   #ifndef SINGLETONREGISTER_HPP
      #include "singletonregister.hpp"
   #endif

// Import/Export resolution
   #undef DIVIEW_LINKAGE
   #ifdef DIVIEW_DLL
      #define DIVIEW_LINKAGE CLASS_EXPORT
   #else
      #define DIVIEW_LINKAGE CLASS_IMPORT
   #endif

class BaseHostConnectionManager;
class BaseConnectionFactory;
class BaseConnection;
class BaseConnectionMonitor;

/**
 * Base Connection Manager class
 *
 * Class is parent for all connection manager classes.
 */
class DIVIEW_LINKAGE BaseConnectionManager
{
public:
   enum MANAGER_TYPE
   {
      SIMPLE,
      POOLED,
      RESERVED
   };

   /**
    * Get instance of BaseConnectionManager
    *
    * @returns BaseConnectionManager - Singleton pointer
    */
   static BaseConnectionManager * getInstance( void );

   DString getReservation( const DString & hostConnectionManagerId );

   void freeReservation( const DString & hostConnectionManagerId,
                         const DString & connectionName );

   /**
    *
    * Gets a connection to the requested backend
    *
    * The host connection manager name determines which
    *    pool of connections will be selected from
    *
    * Example Usage:
    * <code>
    * <li>
    * getConnection( "AWD" )
    * </li>
    * </code>
    *
    * @param hostConnectionManagerId - Host Connection Manager Name
    *
    * @returns BaseConnection - Connection to the backend
    *
    * @exceptions (Place descriptions of any exceptions thrown here.)
    */
   BaseConnection * getConnection( const DString & hostConnectionManagerId );

   /**
    *
    * Gets a connection to the requested backend
    *
    * The host connection manager name determines which
    *    pool of connections will be selected from
    *
    * Example Usage:
    * <code>
    * <li>
    * getConnection( "AWD", "01234567" )
    * </li>
    * </code>
    *
    * @param hostConnectionManagerId - Host Connection Manager Name
    *
    * @returns BaseConnection - Connection to the backend
    *
    * @exceptions (Place descriptions of any exceptions thrown here.)
    */
   BaseConnection * getConnection( const DString & hostConnectionManagerId,
                                   const DString & connectionName );

   /**
    * Returns connection to other requestors can use it
    *
    * @param connection - Connection object that is no longer needed
    *
    */
   void freeConnection( BaseConnection * connection );

   /**
    * Create a host connection manager
    *
    * The host connection manager is tailored based on the passed in parameters.
    *
    * Example Usage:
    * <code>
    * <li>
    *   cf = new VmConnectionFactory( VmConnectionFactory::STANDARD, 5 );
    *   cm->createHostConnectionManager( I_( "POOLED_STANDARD" ),
    *                        DEFAULT_HOST, cf, BaseConnectionManager::POOLED );
    * </li>
    * </code>
    *
    * @param hostConnectionManagerId - Name used by application to identify this host manager
    * @param hostId - Name of the host
    * @param connectionFactory - Factory class for wanted connections
    * @param type - Determines the type of connection pool
    * @param timeout - Max number of seconds to wait for connections
    * @param minConnection - Minimum number of connections
    * @param reaperInterval - Max number of seconds for thread to remove unneeded connections
    * @param reaperCount - Max number of connections removed per reaper interval
    */
   void createHostConnectionManager( const DString & hostConnectionManagerId,
                                     const DString & hostId,
                                     BaseConnectionFactory * connectionFactory,
                                     MANAGER_TYPE type = SIMPLE,
                                     unsigned long timeout = INFINITE,
                                     int minConnections = 0,
                                     int reaperInterval = 5,
                                     int reaperCount = 1 );

   /**
    * Remove host manager associated with name
    *
    * @param hostConnectionManagerId - Name of host connection manager
    */
   void destroyHostConnectionManager( const DString & hostConnectionManagerId );

   void setConnectionMonitor( BaseConnectionMonitor * connectionMonitor );
   const BaseConnectionMonitor * getConnectionMonitor( ) const;

protected:
   BaseHostConnectionManager * getHostConnectionManager( const DString & hostConnectionManagerId );

private:
   BaseConnectionManager( );
   ~BaseConnectionManager( );

   static void deregister( void * pObj );
   static void killInstance( void );

   static BaseConnectionManager * _pInstance;

   typedef std::map< DString, BaseHostConnectionManager * >  HOST_CONNECTION_MGR_MAP;

   HOST_CONNECTION_MGR_MAP _hostManagerMap;

   BaseConnectionMonitor * _connectionMonitor;
   SingletonRegister m_register;
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
// $Log:   Y:/VCS/iFastAWD/inc/BaseConnectionManager.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:00   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:52:08   DT11159
// 
//
//

#endif
