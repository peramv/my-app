#pragma once

#include <list>
#include <bfutil\bfevent.hpp>
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfthread.hpp>

//Forward declarations
class BFJob;
class BFJobQueue;
class BFPooledThread;

namespace
{
   const int DEFAULT_JOBS_QUEUE_SIZE = 50;
   const int DEFAULT_THREAD_COUNT = 10;
}

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE BFThreadPool : public BFThread
{
   friend BFPooledThread;
public:   

   BFThreadPool( const DString &name,
                 int threadCount = DEFAULT_THREAD_COUNT, 
                 int jobQueueSize = DEFAULT_JOBS_QUEUE_SIZE,
                 bfutil::PTHRDNAMEFN pThreadNameFunc = NULL );

   BFThreadPool( const DString &name,
                 BFJobQueue *jobQ,
                 int threadCount = DEFAULT_THREAD_COUNT, 
                 bfutil::PTHRDNAMEFN pThreadNameFunc = NULL );

   virtual ~BFThreadPool();

   void startPool();

   void postJob( BFJob *job );

   // metrics for the purpose of monitoring 
   int getThreadsCount() const;
   int getWorkingThreadCount() const;

   int getMaxJobsQueued() const;
   int getCurrentJobsQueued() const;
   int getJobsProcessed() const;


   void addThreads( unsigned int cNewThreads, bfutil::PTHRDNAMEFN pThreadNameFunc = NULL );
   void removeThreads( unsigned int cDeadThreads );

protected:
   virtual void run();

private:

   // called by BFPooledThread friend class
   void runJobs();
   void incrementThreadCount();
   void decrementThreadCount();

   const DString name_;

   mutable BFCritSec csThreadCount_;
   int cThreads_;

   // the job queue
   BFJobQueue *jobQueue_;

   // the number of threads that are currently working,
   // and the number of jobs processed
   mutable BFCritSec csStats_;
   int cWorkingThreads_;
   int cJobsProcessed_;

   mutable BFEvent   evShutdown_;
   mutable BFCritSec csListThreads_;
   std::list< BFPooledThread* > listThreads_;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFThreadPool.hpp-arc  $
//
//   Rev 1.9   Mar 01 2005 18:21:48   smithdav
//Add additional logging.
//
//   Rev 1.8   Feb 01 2005 15:03:26   smithdav
//removed start pool event.
//
//   Rev 1.7   Jan 27 2005 10:37:46   smithdav
//Major thread pool rework. Esp. thread reaper.
//
//   Rev 1.6   Nov 17 2003 19:09:18   PURDYECH
//Added proper support to remove threads while the pool is still active.
//
//   Rev 1.5   May 01 2003 10:51:56   PURDYECH
//Added code to support thread naming.
//
//   Rev 1.4   Mar 11 2003 10:23:56   PURDYECH
//Support the ability to add and remove threads from the pool.
//
//   Rev 1.3   Oct 09 2002 17:41:22   PURDYECH
//New PVCS Database
//
//   Rev 1.2   22 Mar 2002 15:11:46   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   03 Oct 2001 15:10:02   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.0   Jun 28 2001 09:47:02   PURDYECH
//Initial revision.
//
//   Rev 1.0   Jun 26 2001 12:03:56   PURDYECH
//Initial revision.
 * 
 *    Rev 1.6   06 Dec 2000 16:24:16   SMITHDAV
 * Tweak monitors, and add thread pool monitor
 * 
 *    Rev 1.5   Jun 22 2000 17:24:48   POPESCUS
 * clean-up, comments
 * 
 *    Rev 1.4   Jun 16 2000 15:31:40   POPESCUS
 * fixed the mechanism that grows the pool
 * 
 *    Rev 1.3   Jun 06 2000 10:47:36   POPESCUS
 * cleaned up the code to support only one threading model
 * 
 *    Rev 1.2   Feb 16 2000 13:09:44   POPESCUS
 * Initial revision
 * 
 * 
 */