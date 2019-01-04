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
// ^FILE   : PooledHostConnectionManager.hpp
// ^AUTHOR : David B. Smith
// ^DATE   : January 2000
//
// ^CLASS    : PooledHostConnectionManager
// ^INHERITS FROM :
//
// ^CLASS DESCRIPTION :
//    This class is registrered with BFConnectionManager to manage
//    pooled connections for a single host.
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfconmgr\bfhostconnectionmanager.hpp>
#include <bfutil\bfsemaphore.hpp>
#include <bfutil\bfevent.hpp>
#include <bfutil\bfguard.hpp>
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfthread.hpp>

#include <queue>
#include <set>

class BFConnectionFactory;
class BFConnection;

class PooledHostConnectionManager : public BFHostConnectionManager, public BFThread
{
public:
   PooledHostConnectionManager(const DStringA &poolId, BFConnectionFactory *connectionFactory, int minConnections, int maxConnections);
   virtual ~PooledHostConnectionManager();

   virtual BFConnection *getConnection( void );
   virtual void freeConnection(BFConnection *connection);

   virtual const DStringA &getHostId() const;
   virtual int getMaxConnections() const;
   virtual int getMinConnections() const;
   virtual int getConnectionCount() const;
   virtual int getConnectionsInUse() const;
   virtual int getConnectionFailures() const;

   virtual bool recycle();

protected:
   PooledHostConnectionManager();
   void run();

private:

   typedef std::queue< BFConnection* >  CONNECTION_QUEUE;
   typedef CONNECTION_QUEUE::value_type CONNECTION_QUEUE_VALUE_TYPE;

   CONNECTION_QUEUE _connectionQueue;
   BFCritSec _connectionQueueLock;


   std::set< BFConnection* > _setInUse;

   const DStringA _hostId;

   const int _minConnections;
   const int _maxConnections;

   int _connectionFailures;
   int _connectionCount;
   int _connectionsInUse;

   int _intervalMaxConnectionsInUse;

   BFSemaphore _connectionSemaphore;
   BFEvent _shutdownEvent;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/PooledHostConnectionManager.hpp-arc  $
//
//   Rev 1.8   Oct 09 2002 17:40:20   PURDYECH
//New PVCS Database
//
//   Rev 1.7   22 May 2002 17:54:54   PURDYECH
//BFData Implementation
//
//   Rev 1.6   22 Mar 2002 15:14:18   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.5   Oct 22 2001 17:17:28   HUDAVID
//Connection Recycle code.
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
//    Rev 1.1   May 02 2000 17:29:26   DT24433
// changed to use Infra CriticalSection
//
//    Rev 1.0   Apr 28 2000 18:59:34   SMITHDAV
// Initial revision.
*/