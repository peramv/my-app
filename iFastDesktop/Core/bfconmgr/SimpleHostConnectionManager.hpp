#pragma once
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
// ^FILE   : SimpleHostConnectionManager.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : SimpleHostConnectionManager
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class is registrered with BFConnectionManager to manage 
//    simple connections for a single host.
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfconmgr\bfhostconnectionmanager.hpp>
#include <bfutil\bfsemaphore.hpp>

class BFConnectionFactory;
class BFConnection;

class SimpleHostConnectionManager : public BFHostConnectionManager
{
public:
   SimpleHostConnectionManager(const DStringA &hostId, BFConnectionFactory *connectionFactory, int maxConnections);
   virtual ~SimpleHostConnectionManager();

   virtual BFConnection *getConnection( void );
   virtual void freeConnection(BFConnection *connection);

   virtual const DStringA &getHostId() const;
   virtual int getMaxConnections() const;
   virtual int getMinConnections() const;
   virtual int getConnectionCount() const;
   virtual int getConnectionsInUse() const;
   virtual int getConnectionFailures() const;

private:
   SimpleHostConnectionManager();

   const DStringA _hostId;
//CP   BFConnectionFactory *_connectionFactory;

   int _connectionFailures;
   int _connectionCount;
   const int _maxConnections;
   BFSemaphore _connectionSemaphore;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/SimpleHostConnectionManager.hpp-arc  $
//
//   Rev 1.6   Oct 09 2002 17:40:20   PURDYECH
//New PVCS Database
//
//   Rev 1.5   22 Mar 2002 15:14:20   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.4   Jun 27 2001 20:07:22   PURDYECH
//Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
//
//   Rev 1.3   Jun 26 2001 12:54:34   PURDYECH
//Infrastructure Release 1.9 Integration.
//
//   Rev 1.2   03 May 2001 14:03:04   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   04 Dec 2000 11:38:18   SMITHDAV
//Add console connection monitoring support.
//
//   Rev 1.0   23 Oct 2000 20:10:48   SMITHDAV
//Initial revision.
// 
//    Rev 1.0   Apr 28 2000 18:59:34   SMITHDAV
// Initial revision.
*/