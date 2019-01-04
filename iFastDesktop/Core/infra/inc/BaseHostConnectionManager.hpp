#pragma message( "including "__FILE__ )

#ifndef BASEHOSTCONNECTIONMANAGER_HPP
#define BASEHOSTCONNECTIONMANAGER_HPP

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

#ifndef DICORE_H
   #include "dicore.h"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

class BaseConnection;
class DString;

// Import/Export resolution
#undef DIVIEW_LINKAGE
#ifdef DIVIEW_DLL
   #define DIVIEW_LINKAGE CLASS_EXPORT
#else
   #define DIVIEW_LINKAGE CLASS_IMPORT
#endif


/**
 * Base Host Connection Manager class
 *
 * Class is parent for all host connection manager classes.
 */
class DIVIEW_LINKAGE BaseHostConnectionManager
{
public:
   virtual ~BaseHostConnectionManager( )
   {
   }

   /**
    * Get a connection for a specific host.
    *
    * @returns A connection to a specific host.
    */
   virtual BaseConnection * getConnection( void ) = 0;

   /**
    * Free a connection to a specific host.
    *
    * @param connection connection to be freed.
    */
   virtual void freeConnection( BaseConnection * connection ) = 0;

   /**
    * Get the host ID.
    *
    * @returns The host ID.
    */
   virtual const DString & getHostId( ) const = 0;

   /**
    * Get the maximum number of connections.
    *
    * @returns The maximum number of connections.
    */
   virtual int getMaxConnections( ) const = 0;

   /**
    * Get the minimum number of connections.
    *
    * @returns The minimum number of connections.
    */
   virtual int getMinConnections( ) const = 0;

   /**
    * Get the current number of connections managed by this manager.
    *
    * @returns The connection coune.
    */
   virtual int getConnectionCount( ) const = 0;

   /**
    * Get the current number of connections in use.
    *
    * @returns The number of connections in use.
    */
   virtual int getConnectionsInUse( ) const = 0;

   /**
    * Get the number of connection failures.
    *
    * @returns The number of connection failures.
    */
   virtual int getConnectionFailures( ) const = 0;

   /**
    * Get a reservation.
    *
    * The getReservation, freeReservation, and
    * getConnection( const DString &, unsigned long ) methods make up the
    * "reservable interface".  If one of them is overridden, they all should be.
    *
    * @returns The connection name that was reserved.
    */
   virtual DString getReservation( )
   {
      THROWEXCEPTIONCONDITION( DICORE_CONDITION,
                               I_( "BaseHostConnectionManager::getReservation( unsigned long )" ),
                               VIRTUAL_BASE_METHOD_NOT_SUPPORTED,
                               NULL_STRING, NULL );

      return( NULL_STRING );
   }

   /**
    * Free a reservation.
    *
    * The getReservation, freeReservation, and
    * getConnection( const DString &, unsigned long ) methods make up the
    * "reservable interface".  If one of them is overridden, they all should be.
    *
    * @param connectionName name of the reserved connection to free.
    */
   virtual void freeReservation( const DString & connectionName )
   {
      THROWEXCEPTIONCONDITION( DICORE_CONDITION,
                               I_( "BaseHostConnectionManager::freeReservation( const DString & )" ),
                               VIRTUAL_BASE_METHOD_NOT_SUPPORTED,
                               NULL_STRING, NULL );
   }

   /**
    * Get a specific connection.
    *
    * The getReservation, freeReservation, and
    * getConnection( const DString &, unsigned long ) methods make up the
    * "reservable interface".  If one of them is overridden, they all should be.
    *
    * @param connectionName name of the connection to get.
    *
    * @returns The connection name that was reserved.
    */
   virtual BaseConnection * getConnection( const DString & connectionName )
   {
      THROWEXCEPTIONCONDITION( DICORE_CONDITION,
                               I_( "BaseHostConnectionManager::getConnection( const DString &, unsigned long )" ),
                               VIRTUAL_BASE_METHOD_NOT_SUPPORTED,
                               NULL_STRING, NULL );

      return( NULL );
   }
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
// $Log:   Y:/VCS/iFastAWD/inc/BaseHostConnectionManager.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:02   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:52:20   DT11159
// 
//
//

#endif
