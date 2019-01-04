#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 */

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef PLATFORM_H
   #include "platform.h"
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
   #include <vector>
#endif

#ifndef INFRAEVENT_HPP
   #include "InfraEvent.hpp"
#endif
#ifndef INFRACRITSEC_HPP
   #include "InfraCritSec.hpp"
#endif
#ifndef INFRAMUTEX_HPP
   #include "InfraMutex.hpp"
#endif
#ifndef INFRASEMAPHORE_HPP
   #include "InfraSemaphore.hpp"
#endif

#ifndef INFRATHREAD_HPP
/**@#-*/  // forward declarations
class InfraThreadPool;
/**@#+*/
   #include "infrathread.hpp"
#endif

#ifndef INFRAJOB_HPP
/**@#-*/  // forward declarations
class InfraJob;
/**@#+*/
#endif

// Import/Export resolution
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

//this class represents an implementation of
//a growable pool of threads; the pool starts with a
//minimum number of idle threads and if needed this
//number of threads can be grown until reaches
//a maximum; if a thread idles for a certain
//period of time then it will terminate itself.
//(it means that the thread timed-out);
//this is allowed only if there are enough threads
//in the pool because the number of threads in the pool
//cannot go beyond the minimum;
//  class BPSRVMT_LINKAGE InfraThreadPool : public InfraThread
class DICORE_LINKAGE InfraThreadPool : public InfraThread
{
public:
   enum ThreadPoolConstants
   {
      THREAD_TIMEOUT = 10000,  //10 seconds
      MIN_THREADS = 100,       //100 threads
      MAX_THREADS = 250,       //250 threads
      TPSLEEPTIME = 10000       //10 seconds
   };

private:
   friend InfraThread;

public:
   //this method will dispatch a job to a thread that is idle
   //if there is no such thread it will create one on the fly, if this is
   //possible;
   //bool dispatchThread( InfraJob* infrajob );

   // metrics for the purpose of monitoring
   // cast to int to avoid syncronization - assume atomic assign on all reasonable platforms
   int getThreadsCount() const { return (int)_crtThreads; }
   int getWorkingThreadCount() const { return (int)_crtWorkingThreads; }

   int getMinThreadCount() const { return (int)_lMinThreads; }
   int getMaxThreadCount() const { return (int)_lMaxThreads; }
protected:
   //the constructor will create the minimum number of threads to populate the pool
   InfraThreadPool( long lMinConnections = MIN_THREADS,
      long lMaxConnections = MAX_THREADS, long lTimeout = THREAD_TIMEOUT, char *threaName = NULL );
   //the destructor will signal all threads to exit and terminate their jobs
   //and then will clean-up the pool
   virtual ~InfraThreadPool();
   //the method will initialize the pool with the minimum required threads
   void initPool();
   //the thread pool is itself a thread; this is the body of it;
   //the pool will ckeck once in a while if there are any died threads;
   //if there are, it will delete the instance of these threads
   virtual void run();
   void runThread();
   //must be implemented in the derived classes,
   //to define the type of threads kept in the pool
   virtual InfraThread *doAddThread() = 0;
   //allows derived classes to query whether the pool is full or not
   bool isPoolFull();
   //resources used to implement per-thread dispatching;
   virtual InfraJob *doGetJob(); //base class does nothing

private:
   //adds a thread to the pool
   bool addThread();
   //removes a thread from the pool
   void removeThread( long currentThreadID );
   //this will grow the pool if we need it
   //returns true if it succeded,
   bool growPool();
   //once a thread timed out it should be added to this
   //vector, so the pool object can delete them
   typedef std::vector< InfraThread* > DIED_THREADS;
   typedef DIED_THREADS::iterator DIED_THREADS_ITER;
   //this is how the threads are stored in the pool
   typedef std::map< long, InfraThread*, std::less<long> > THREAD_POOL;
   typedef THREAD_POOL::iterator THREAD_POOL_ITER;
   //the pool of threads
   THREAD_POOL _threadpool;
   //the died threads vector
   DIED_THREADS _diedthreads;
   //the number of threads that are currently working
   long _crtWorkingThreads;
   //the curent number of threads in the pool
   long _crtThreads;
   //the minimum number of threads allowed to live in the pool
   long _lMinThreads;
   //the maximum number of threads allowed to live in the pool
   long _lMaxThreads;
   //the thread's life span
   long _lThreadTimeout;
   //the event signals all threads to terminate, because the pool is
   //going to be cleared-up
   InfraEvent _exitEvent;
   //the critical section that will synchronize the access to the pool's data
   InfraCritSec _poolCS;
   //we should use this to stop the thread pool
   static bool _bAlive;

   //resources used to implement per-thread dispatching;
   //the idea behind this approach is for each thread from the pool to create
   //a job for itself and do not wait for someone else to dispatch a job;
   //the event is used to guard the resource which will trigger the job creation
   InfraEvent _jobTrigger;
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
// $Log:   Y:/VCS/iFastAWD/inc/InfraThreadPool.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:54   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:31:42   DT11159
// 
//
//

#endif
