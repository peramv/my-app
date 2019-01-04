#pragma once

#include <queue>
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfsemaphore.hpp>
#include <bfutil\bfevent.hpp>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class BFJob;
class BFKernel;

class BFUTIL_LINKAGE BFJobQueue
{
public:   
   virtual ~BFJobQueue() {}

   virtual int getMaxJobsQueued() const = 0;
   virtual int getCurrentJobsQueued() const = 0;
   virtual bool pushJob( BFJob *job, DWORD timeout = INFINITE ) = 0;
   virtual bool popJob( BFJob *&job, DWORD timeout = INFINITE ) = 0;
   virtual void close() = 0;
   virtual bool isClosed() = 0;

};

class BFUTIL_LINKAGE BFInternalJobQueue : public BFJobQueue
{
public:   

   BFInternalJobQueue( int lMaxJobQueued );
   virtual ~BFInternalJobQueue();

   virtual int getMaxJobsQueued() const;
   virtual int getCurrentJobsQueued() const;

   virtual bool pushJob( BFJob *job, DWORD timeout = INFINITE );
   virtual bool popJob( BFJob *&job, DWORD timeout = INFINITE );

   virtual void close();
   virtual bool isClosed();

private:
   // manage a job queue
   typedef std::queue< BFJob* >  JOB_QUEUE;
   typedef JOB_QUEUE::value_type JOB_QUEUE_VALUE_TYPE;
   JOB_QUEUE _jobQueue;

   // job sync objects
   BFCritSec _jobQueueCritSec; 
   BFSemaphore _jobPushSemaphore;
   BFSemaphore _jobPopSemaphore;

   BFKernel* _pushWaitObjects[2];
   BFKernel* _popWaitObjects[2];

   // close sync objects
   BFCritSec _closeCritSec; 
   BFEvent _closedEvent;

   const int _maxJobsQueued;
   int _currentJobsQueued;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFJobQueue.hpp-arc  $
//
//   Rev 1.4   Jan 27 2005 10:16:00   smithdav
//Refactor BFJobQueue to extract a sub-class BFInternalJobQueue. BFJobQueue becomes a pure virtual interface.
//
//   Rev 1.3   Oct 09 2002 17:41:16   PURDYECH
//New PVCS Database
//
//   Rev 1.2   22 Mar 2002 15:11:38   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   Oct 05 2001 14:02:32   PURDYECH
//Removed the virtual keyword from the destructor as this caused the VisualC++ compiler to try to look for that destructor during Link in other modules.
//
//   Rev 1.0   03 Oct 2001 15:18:50   SMITHDAV
//Initial revision.
 */