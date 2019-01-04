#pragma message( "including "__FILE__ )

#ifndef SIMPLEHOSTCONNECTIONMANAGER_HPP
#define SIMPLEHOSTCONNECTIONMANAGER_HPP

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
   #include "infrasemaphore.hpp"
#endif

class BaseConnectionFactory;
class BaseConnection;

class SimpleHostConnectionManager : public BaseHostConnectionManager
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
    * @param maxConnections
    *                 Maximum number of connections.  This parameter is used
    *                 to limit the number of simultaneous connections to the
    *                 host.
    */
   SimpleHostConnectionManager( const DString & hostConnectionManagerId,
                                const DString & hostId,
                                BaseConnectionFactory * connectionFactory,
                                int maxConnections,
                                unsigned long timeout );
   virtual ~SimpleHostConnectionManager( );

   /**
    * Get a connection.  If maxConnections has been reached, wait for a
    * connection to become free, otherwise a new connection will be created and
    * returned.
    *
    * @return A connection.
    */
   virtual BaseConnection * getConnection( void );

   /**
    * Free a connection.  This will destroy the connection.
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

private:
   SimpleHostConnectionManager( );

   const DString _hostConnectionManagerId;
   const DString _hostId;
   BaseConnectionFactory * _connectionFactory;

   int _connectionFailures;
   int _connectionCount;
   const int _maxConnections;
   const unsigned long _timeout;
   InfraSemaphore _connectionSemaphore;
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
// $Log:   Y:/VCS/iFastAWD/diview/SimpleHostConnectionManager.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:24:04   kovacsro
//Initial revision.
//
//   Rev 1.1   Jun 28 2001 16:49:38   DT11159
//Renamed some classes.
//
//   Rev 1.0   May 18 2001 11:40:46   DT11159
// 
//
//   Rev 1.1   04 Dec 2000 11:38:18   SMITHDAV
//Add console connection monitoring support.
//
//   Rev 1.0   23 Oct 2000 20:10:48   SMITHDAV
//Initial revision.
//
//    Rev 1.0   Apr 28 2000 18:59:34   SMITHDAV
// Initial revision.
