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
// ^FILE   : VmConnectionFactory.hpp
// ^AUTHOR : David B. Smith / Glen McNabb
// ^DATE   : March 2000
//
// ^CLASS    : VmConnectionFactory
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

class BFCONMGR_LINKAGE VmConnectionFactory : public BFConnectionFactory
{
public:
   VmConnectionFactory( const DStringA &namePrefix, int maxConnectionCount );
   virtual BFConnection *createConnection( const DStringA &hostId );
   virtual void destroyConnection( BFConnection *connection );

private:

   class NameServer
   {
   public:
      NameServer( const DStringA &namePrefix, int nameCount );

      DStringA &getName( DStringA &name );
      void freeName( const DStringA& name );

   private:
      void initNameQueue( const DStringA &namePrefix, int nameCount );


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
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/VmConnectionFactory.hpp-arc  $
//
//   Rev 1.4   Oct 09 2002 17:40:22   PURDYECH
//New PVCS Database
//
//   Rev 1.3   Aug 29 2002 12:59:26   PURDYECH
//VMInterface fixes
//
//   Rev 1.2   22 Mar 2002 15:14:20   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   Jun 27 2001 20:07:24   PURDYECH
//Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
//
//   Rev 1.0   May 16 2001 11:22:32   MCNABBGL
//Initial revision.
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
