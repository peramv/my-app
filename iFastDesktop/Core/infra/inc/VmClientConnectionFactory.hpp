#pragma message( "including "__FILE__ )

#ifndef VMCLIENTCONNECTIONFACTORY_HPP
   #define VMCLIENTCONNECTIONFACTORY_HPP

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
   #ifndef BASECONNECTIONFACTORY_HPP
      #include "baseconnectionfactory.hpp"
   #endif
   #ifndef VMNAMESERVER_HPP
      #include "vmnameserver.hpp"
   #endif

class BaseConnection;

// Import/Export resolution
   #undef DIVIEW_LINKAGE
   #ifdef DIVIEW_DLL
      #define DIVIEW_LINKAGE CLASS_EXPORT
   #else
      #define DIVIEW_LINKAGE CLASS_IMPORT
   #endif

/**
 * View Manager Connection Factory class
 *
 * Class is used to create and destroy View Manager connections.
 */
class DIVIEW_LINKAGE VmClientConnectionFactory : public BaseConnectionFactory
{
public:
   enum CONNECTION_TYPE
   {
      STANDARD,
      PRIVATE
   };

   /**
    * Construct a VmClientConnectionFactory.
    *
    * @param type     type of connections produced by the factory.
    *
    * @param maxConnectionCount maximum number of concurrent connections that
    *                 can be created by the factory.
    */
   VmClientConnectionFactory( CONNECTION_TYPE type, int maxConnectionCount );

   /**
    * Create a View Manager connection.
    *
    * @param hostId   host ID for the connection.
    *
    * @return         Returns the connection.
    */
   virtual BaseConnection * createConnection( const DString & hostId );

   /**
    * Destroy a View Manager connection.
    *
    * @param connection connection object to be destroyed.
    */
   virtual void destroyConnection( BaseConnection * connection );

   /**
    * Get the maximum number of concurrent connections that this factory can
    * create.
    *
    * @param connection connection object to be destroyed.
    */
   virtual int getMaxConnectionCount( );

private:
   VmClientConnectionFactory( );

   CONNECTION_TYPE m_type;
   int m_maxConnectionCount;
   VmNameServer m_nameServer;
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
// $Log:   Y:/VCS/iFastAWD/inc/VmClientConnectionFactory.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:20   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 08:24:08   DT11159
// 
//
//

#endif
