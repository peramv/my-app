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
 *   Class:   VmClientConnectionManager.cpp
 *
 *   Class Description
 *
 */
#define DIVIEW_DLL

#ifndef SRCPRAG_h
   #include "srcprag.h"
#endif
#ifndef VMCLIENTCONNECTIONFACTORY_HPP
   #include "vmclientconnectionfactory.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef CRITICALSECTION_HP
   #include "criticalsection.hpp"
#endif
#ifndef VMCLIENTSTANDARDCONNECTION_HPP
   #include "vmclientstandardconnection.hpp"
#endif
#ifndef VMCLIENTPRIVATECONNECTION_HPP
   #include "vmclientprivateconnection.hpp"
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "VmClientConnectionFactory" );
}

VmClientConnectionFactory::VmClientConnectionFactory( CONNECTION_TYPE type, int maxConnectionCount ) :
m_type( type ),
m_maxConnectionCount( maxConnectionCount ),
m_nameServer( maxConnectionCount )
{
}

BaseConnection *
VmClientConnectionFactory::createConnection( const DString & hostId )
{
   BaseConnection * connection;

   DString connectionName;

   m_nameServer.getName( connectionName );

   switch ( m_type )
   {
      case STANDARD:
         connection = new VmClientStandardConnection( hostId, connectionName );
         break;

      case PRIVATE:
         connection = new VmClientPrivateConnection( hostId, connectionName );
         break;

      default:
         connection = new VmClientStandardConnection( hostId, connectionName );
         break;
   }

   return ( connection );
}

void
VmClientConnectionFactory::destroyConnection( BaseConnection * connection )
{
   if ( connection )
   {
      VmClientConnection * vmClientConnection = dynamic_cast< VmClientConnection * > ( connection );

      // Make a copy of the connection name.
      DString connectionName;
      vmClientConnection->getName( connectionName );

      // Delete the object before freeing the name.
      delete vmClientConnection;

      // Free the name for reuse.
      m_nameServer.freeName( connectionName );
   }
}

int
VmClientConnectionFactory::getMaxConnectionCount( )
{
   return( m_maxConnectionCount );
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
// $Log:   Y:/VCS/iFastAWD/diview/VmClientConnectionFactory.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:08   kovacsro
// Initial revision.
//
//   Rev 1.1   Jun 29 2001 11:05:18   DT11159
//Rename some classes.
//
//   Rev 1.0   Jun 28 2001 08:25:04   DT11159
// 
//
//
