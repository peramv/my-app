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

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef INFRATHREADPOOL_HPP
   #include "infrathreadpool.hpp"
#endif
#ifndef INFRAJOB_HPP
   #include "infrajob.hpp"
#endif
#ifndef INFRAEXCEPTION_HPP
   #include "infraexception.hpp"
#endif
#ifndef INFRAWAITABLESET_HPP
   #include "infrawaitableset.hpp"
#endif

//initialize static variables
bool InfraThreadPool::_bAlive = false;
//bool InfraThreadPool.GrowsPool::_bAlive = false;

InfraThreadPool::InfraThreadPool( long lMinThreads, long lMaxThreads,
                        long lThreadTimeout, char *threadName /*=NULL*/ ) :
   InfraThread( threadName ),
   _lMinThreads( lMinThreads ), //minimum number of threads
   _lMaxThreads( lMaxThreads ), //maximum number of threads
   _lThreadTimeout( lThreadTimeout ), //thread life span
   _crtWorkingThreads( 0 ), //the number of threads that are working
   _crtThreads( 0 ), //the number of the threads in the pool
   _exitEvent( true ), //manual reset event, initially non-signaled
   _poolCS( false ), //manually enter and leave the critical section
   _jobTrigger( false, true ) //manual reset event, initially signaled
{
}

InfraThreadPool::~InfraThreadPool()
{
   std::vector< InfraThread* > liveThreads;
   bool allDone = false;

   //make sure we will not process process any other jobs
   _jobTrigger.reset();
   //first make a copy of all live threads
   //this should be locked because,
   //we might concure with the auto-destruction of a thread
   //due to timeout
#ifdef MT_DEBUG
   cout << "Capture all the live threads." << endl;
   cout.flush();
#endif
   _poolCS.enter();
   //stop the thread pool
   InfraThreadPool::_bAlive = false;
   THREAD_POOL_ITER iter;
   for(iter = _threadpool.begin(); iter != _threadpool.end(); iter++)
   {
      InfraThread *pThread = (*iter).second;

      if( pThread->isAlive() )
      {
         liveThreads.push_back( pThread );
      }
   }
   //signal all threads to exit,
   //so they can clean-up themselves
   _exitEvent.set();
   _poolCS.leave();
#ifdef MT_DEBUG
   cout << "Wait for "<< liveThreads.size() << " live threads to end." << endl;
   cout.flush();
#endif
   //now we have to wait for all threads to exit
   //walk the vector of alive threads and wait for everyone to stop;
   std::vector<InfraThread*>::iterator ltiter; 
   for(ltiter = liveThreads.begin(); ltiter != liveThreads.end(); ++ltiter )
   {
      //wait on the current thread to exit
      DWORD dwWaitResult = (*ltiter)->wait( INFINITE );

#ifdef MT_DEBUG
   cout << "Wait on: " << (*ltiter)->getThreadDebugName() << " to end." << endl;
   cout.flush();
#endif
      if( dwWaitResult == WAIT_FAILED || dwWaitResult == WAIT_TIMEOUT )
      {
#ifdef MT_DEBUG
   cout << "The wait on: " << (*ltiter)->getThreadDebugName() << " failed." << endl;
   cout.flush();
#endif
         //wait on this thread to stop
         wait( INFINITE );
         throw InfraException();
      }
   }
   //erase the threadPool map
   for( iter = _threadpool.begin(); iter != _threadpool.end(); )
   {
      delete (*iter).second;
      iter = _threadpool.erase( iter );
   }
   //delete the livethreads vector
   for( ltiter = liveThreads.begin(); ltiter != liveThreads.end(); )
   {
      //we've already deleted the actual thread pointer;
      ltiter = liveThreads.erase( ltiter );
   }
   //wait for the current thread (thread pool) to stop
   wait( INFINITE );
#ifdef MT_DEBUG
   cout << "The thread pool has died." << endl;
   cout.flush();
#endif
}

void InfraThreadPool::initPool()
{
   //lock the creation of the lMinThreads
   _poolCS.enter();
   bool okay = true;

   while( okay && ( _crtThreads < _lMinThreads ) )
   {
      okay = addThread();
   }
   if( !okay )
   {
      _poolCS.leave();
      throw InfraException();
   }
   InfraThreadPool::_bAlive = true;
   _poolCS.leave();
}

//this method should be used by threads that require a Job,
//basically this method will represent the body of a thread
//from the pool and it also defines the way the pool
//manages the threads it contains
void InfraThreadPool::runThread()
{
   InfraWaitableSet waitSet;
   bool keepThreadAlive = true;
   enum { EXIT_NDX = 0, JOB_TRIGGER, NUM_HANDLE };

   waitSet.addHandle( (HANDLE)_exitEvent );
   waitSet.addHandle( (HANDLE)_jobTrigger );
   while( keepThreadAlive )
   {
      //wait for either an exit event, or job, or just timeout
      DWORD dwWaitResult = waitSet.wait( FALSE, _lThreadTimeout );

      if( ( dwWaitResult >= WAIT_OBJECT_0 ) &&
          ( dwWaitResult <= WAIT_OBJECT_0 + NUM_HANDLE - 1 ) )
      {
         switch( dwWaitResult - WAIT_OBJECT_0 )
         {
            case EXIT_NDX :
            {
#ifdef MT_DEBUG
   cout << "Thread with the id: " << GetCurrentThreadId() << " got the exit event." << endl;
   cout.flush();
#endif //MT_DEBUG
               //by this time the pool destructor registered that this thread
               //is alive so we should just exit;
               keepThreadAlive = false;
               break;
            }
            case JOB_TRIGGER : //if the job trigger has been signaled
            {
               //make sure we are the only ones getting the job;
               _jobTrigger.reset();
               //go and grab the job; ask the derived classes to build the job
               //for us; could be blocked until the job is created
               InfraJob *infrajob = doGetJob();

               //tell other threads that they can go for a Job
               _jobTrigger.set();
               if( infrajob != NULL ) //if we have a job
               {
                  _poolCS.enter();
                  _crtWorkingThreads++; //increase the number of currently working threads in the pool
                  _poolCS.leave();
                  if( isPoolFull() ) //the pool is full, meaning that all threads have work to do
                  {
                     //What should we do with the result of growing the pool?
                     bool grown = growPool();
                  }
                  //dispatch the current job to the current thread
                  _poolCS.enter();
                  THREAD_POOL_ITER tpiter = _threadpool.find( GetCurrentThreadId() );
                  THREAD_POOL_ITER tpiterend = _threadpool.end();
                  _poolCS.leave();

                  if( tpiter != tpiterend )
                  {
                     InfraThread *pThread = (*tpiter).second;
                     pThread->setJob( infrajob );
#ifdef MT_DEBUG
   cout << pThread->getThreadDebugName() << " does the job." << endl;
   cout.flush();
#endif //MT_DEBUG
                     //does the job
                     pThread->run();
                     //frees the job pointer
//                     pThread->takeJob();  - this is done in derived Job class to keep flexible
                     //release this thread
                     _poolCS.enter();
                     _crtWorkingThreads--; //decrease the number of working threads in the pool
                     _poolCS.leave();
                  }
               }
               else
               {
#ifdef MT_DEBUG
      cout << "We do not have a job for thread:" << GetCurrentThreadId() << endl;
      cout.flush();
#endif //MT_DEBUG
               }
               break;
            }
         }
      }
      else if( dwWaitResult == WAIT_TIMEOUT )
      {
         //the thread has been asleep for a long time and has timed out.
         //see if we are allowed to remove it from the pool
         _poolCS.enter();
         if( _crtThreads > _lMinThreads ) //the current thread count in the pool is above the minimum
         {
#ifdef MT_DEBUG
      cout << "A thread timed-out" << endl;
      cout.flush();
#endif //MT_DEBUG
            removeThread( GetCurrentThreadId() );
            keepThreadAlive = false;
         }
         else
         {
            //here the minimum number of threads has been reached so,
            //the thread should stay and wait for something to do
         }
         _poolCS.leave();
      }
      else  //other wait failure in general
      {
         _poolCS.enter();
         removeThread( GetCurrentThreadId() );
         keepThreadAlive = false;
         _poolCS.leave();
      }
   }
}

void InfraThreadPool::run()
{
   //loop until someone stops the thread
   while( _bAlive )
   {
      // Now wait for a while.
      // When it wakes up it'll check the list of died threads.
      this->sleep( TPSLEEPTIME );
      //Check through the list of died threads and delete them
      _poolCS.enter();
#ifdef MT_DEBUG
      cout << "Thread pool wakes up and checks if there is any thread that died." << endl;
      cout << "The no. of threads in the pool is: " << _crtThreads << endl;
      cout << "The no. of working threads in the pool is: " << _crtWorkingThreads << endl;
      cout.flush();
#endif //MT_DEBUG

      for( DIED_THREADS_ITER iter = _diedthreads.begin();
           iter != _diedthreads.end(); )
      {
#ifdef MT_DEBUG
      cout << "The pool removes the " << (*iter)->getThreadDebugName() << " because it died."<< endl;
      cout.flush();
#endif //MT_DEBUG
         delete *iter;
         iter = _diedthreads.erase( iter );
      }
      _poolCS.leave();
   }
}

//this method should be synchronized by the caller
bool InfraThreadPool::addThread()
{
   bool okayThread = false;
   //ask the derived pools to create the thread,
   //they will take care of.
   InfraThread* pThread = doAddThread();

   if( pThread )
   {
      //create the thread suspended, before inserting it in the pool
      pThread->start( CREATE_SUSPENDED );
      _threadpool.insert( std::make_pair( pThread->getThreadID(), pThread ) );
      //resume the thread so it can start waiting for a job or other events
      pThread->resume();
      //increase the number of current threads in the pool
      _crtThreads++;
      okayThread = true;
#ifdef MT_DEBUG
      cout << "Add a new thread to the pool." << endl;
      cout.flush();
#endif //MT_DEBUG
   }
   return okayThread;
}

//there is no guarantee from where this method will be called
//so we should pass the thread id we need to remove
//this method should be synchronized by the caller
void InfraThreadPool::removeThread( long currentThreadID )
{
   THREAD_POOL_ITER tpiter = _threadpool.find( currentThreadID );

   if( tpiter != _threadpool.end() )
   {
      //decrease the number of threads available in the pool
      _crtThreads--;
      //add the thread to the vector of died threads
      _diedthreads.push_back( (*tpiter).second );
      //erase the thread from the map
      _threadpool.erase( tpiter );
#ifdef MT_DEBUG
      cout << "Erase a thread from the pool." << endl;
      cout.flush();
#endif //MT_DEBUG
   }
}

//grows the pool when is needed
bool InfraThreadPool::growPool()
{
   bool growOk = false;
   //lock the creation of a new thread
   _poolCS.enter();

   if( _crtThreads < _lMaxThreads )
   {
#ifdef MT_DEBUG
   cout << "The pool is growing, more threads are necessary." << endl;
   cout.flush();
#endif //MT_DEBUG
      growOk = addThread();
   }
   else //dispatch hit the maximum number of threads
   {
#ifdef MT_DEBUG
   cout << "Couldn't dispatch a thread because the maximum number of threads was hit" << endl;
   cout.flush();
#endif //MT_DEBUG
   }
   _poolCS.leave();
   return growOk;
}

//tests whether the pool has free threads or not
bool InfraThreadPool::isPoolFull()
{
   return _crtThreads - _crtWorkingThreads <= 0;
}

InfraJob *InfraThreadPool::doGetJob() //base class does nothing
{
   return NULL;
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraThreadPool.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:08   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:22:40   DT11159
// 
//
//
