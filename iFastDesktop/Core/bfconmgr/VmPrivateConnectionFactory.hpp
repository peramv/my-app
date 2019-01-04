#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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
// ^FILE   : BFConnection.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : BFConnectionFactory
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the specific connection 
//    factory classes.
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfconmgr\bfconnectionfactory.hpp>
#include <bfutil\bfsemaphore.hpp>
#include <mutexsemaphore.hpp>
#include <queue>

#define APP_MESSAGE_SIZE 128L

class BFConnection;

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE VmPrivateConnectionFactory : public BFConnectionFactory
{
public:
   VmPrivateConnectionFactory(const DStringA &namePrefix, int maxConnectionCount);
   virtual BFConnection *createConnection(const DStringA &hostId);
   virtual void destroyConnection(BFConnection *connection);

private:

   class NameServer
   {
   public:
      NameServer(const DStringA &namePrefix, int nameCount);

      DStringA &getName(DStringA &name);
      void freeName(const DStringA& name);

   private:
      void initNameQueue(const DStringA &namePrefix, int nameCount);


      typedef std::queue< DStringA >  NAME_QUEUE;
      typedef NAME_QUEUE::value_type NAME_QUEUE_VALUE_TYPE;

      NAME_QUEUE _nameQueue;
      MutexSemaphore _nameQueueLock;
      BFSemaphore _nameSemaphore;
   } _nameServer;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/VmPrivateConnectionFactory.hpp-arc  $
//
//   Rev 1.7   Oct 09 2002 17:40:24   PURDYECH
//New PVCS Database
//
//   Rev 1.6   22 Mar 2002 15:12:12   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.5   Jun 27 2001 20:07:48   PURDYECH
//Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
//
//   Rev 1.4   03 May 2001 14:03:30   SMITHDAV
//Session management restructuring.
//
//   Rev 1.3   23 Oct 2000 20:13:22   SMITHDAV
//Change linkage to support new library BFConMfg.
//
//   Rev 1.2   May 10 2000 18:09:42   SMITHDAV
//Change to allow user to specify connection name prefix.  Also bug fix on destroyConnection: name should not be freed until after connection is deleted.
//
//   Rev 1.1   May 02 2000 17:27:50   DT24433
//changed to use Infra CriticalSection
//
//   Rev 1.0   Apr 14 2000 14:10:04   SMITHDAV
//Initial revision.
*/