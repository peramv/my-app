#include "stdafx.h"

#include "bfthreadpool.hpp"
#include "bfjob.hpp"
#include "bfjobqueue.hpp"
#include "bfexception.hpp"
#include "bfguard.hpp"
#include "bfpooledthread.hpp"
#include <bf\log\log.hpp>

namespace
{
   const int REAPER_SLEEP_TIME = 5000;
}

//***********************************************************************
BFThreadPool::BFThreadPool( const DString &name,
                            int threadCount /*= DEFAULT_THREAD_COUNT*/, 
                            int jobQueueSize /*= DEFAULT_JOBS_QUEUE_SIZE*/,
                            bfutil::PTHRDNAMEFN pThreadNameFunc /*= NULL*/ )
: BFThread()
, name_(name)
, cThreads_( 0 )
, jobQueue_( new BFInternalJobQueue( std::max( jobQueueSize, 1 ) ) )
, cWorkingThreads_( 0 )
, evShutdown_( true, false )
{
   addThreads( std::max(threadCount, 1), pThreadNameFunc );
   start();
}

//***********************************************************************
BFThreadPool::BFThreadPool( const DString &name,
                            BFJobQueue *jobQ,
                            int threadCount /*= DEFAULT_THREAD_COUNT*/, 
                            bfutil::PTHRDNAMEFN pThreadNameFunc /*= NULL*/ )
: BFThread()
, name_(name)
, cThreads_( 0 )
, jobQueue_(jobQ)
, cWorkingThreads_( 0 )
, cJobsProcessed_( 0 )
, evShutdown_( true, false )
{
   addThreads( std::max(threadCount, 1), pThreadNameFunc );
   start();
   bf::log::theLog << bf::log::information << name_ << I_( " thread pool created..." ) << bf::log::endlf;
}

//***********************************************************************
BFThreadPool::~BFThreadPool()
{
   // close the job queue
   jobQueue_->close();

   // signal the reaper to die and wait
   evShutdown_.set();
   wait();
   delete jobQueue_;
   bf::log::theLog << bf::log::information << name_ << I_( " thread pool closed..." ) << bf::log::endlf;
}

// Reaper
void BFThreadPool::run() 
{

   while( !evShutdown_.wait( REAPER_SLEEP_TIME ) ) {
      //clean-up thread pool
      int cDeadThreads=0;
      BFGuard g( csListThreads_ );
      std::list< BFPooledThread* >::iterator iter = listThreads_.begin();
      while( iter != listThreads_.end() ) {
         if ( (*iter)->wait(0) ) {
            delete  (*iter);
            iter = listThreads_.erase(iter);
            ++cDeadThreads;
         } else {
            ++iter;
         }
      }
      if ( cDeadThreads > 0 ) {
         bf::log::theLog << bf::log::information << cDeadThreads << I_( " dead threads reaped in thread pool " ) << name_ << bf::log::endlf;
      }
   }

   {
      //clean-up thread pool
      bf::log::theLog << bf::log::information << name_  << I_( " thread pool reaper waiting to exit" ) << bf::log::endlf;
      int cDeadThreads=0;
      BFGuard g( csListThreads_ );
      std::list< BFPooledThread* >::iterator iter = listThreads_.begin();
      while( iter != listThreads_.end() ) {
         (*iter)->wait();
         delete  (*iter);
         iter = listThreads_.erase(iter);
         ++cDeadThreads;
      }
      bf::log::theLog << bf::log::information << cDeadThreads << I_( " dead threads reaped in thread pool " ) << name_ << bf::log::endlf;
      bf::log::theLog << bf::log::information << name_  << I_( " thread pool reaper has exited" ) << bf::log::endlf;
   }

}

//***********************************************************************
int BFThreadPool::getThreadsCount() const 
{
   BFGuard g( csThreadCount_ );
   return( cThreads_ );
}

//***********************************************************************
int BFThreadPool::getWorkingThreadCount() const 
{ 
   BFGuard g( csStats_ );
   return( cWorkingThreads_ ); 
}

//***********************************************************************
int BFThreadPool::getMaxJobsQueued() const 
{ 
   return(jobQueue_->getMaxJobsQueued()); 
}

//***********************************************************************
int BFThreadPool::getJobsProcessed() const {
   BFGuard g( csStats_ );
   return(cJobsProcessed_); 
}

//***********************************************************************
int BFThreadPool::getCurrentJobsQueued() const 
{ 
   return(jobQueue_->getCurrentJobsQueued()); 
}

//***********************************************************************
void BFThreadPool::addThreads( unsigned int cNewThreads, bfutil::PTHRDNAMEFN pThreadNameFunc )
{
   for( int i=0; i < cNewThreads; ++i ) {
      BFPooledThread* pThread = new BFPooledThread(this, pThreadNameFunc);
      if( NULL != pThread ) {
            // add this thread object to the list of threads
            BFGuard g( csListThreads_ );
            listThreads_.push_back( pThread );
      }
   }
}

//***********************************************************************
void BFThreadPool::removeThreads( unsigned int cDeadThreads )
{
   // we will put a NULL pointer onto the Job Queue.  This will
   // signal the runJobs method to exit its loop.
   for( int i = 0; i < cDeadThreads; ++i )
   {
      postJob( NULL );
   }
}

//***********************************************************************
void BFThreadPool::incrementThreadCount()
{
   BFGuard g( csThreadCount_ );
   ++cThreads_;
}

//***********************************************************************
void BFThreadPool::decrementThreadCount()
{
   BFGuard g( csThreadCount_ );
   --cThreads_;
}

//***********************************************************************
void BFThreadPool::postJob( BFJob *pJob )
{
   jobQueue_->pushJob( pJob );
}

//***********************************************************************
void BFThreadPool::runJobs()
{

   bf::log::theLog << bf::log::information << I_( "thread starting for thread pool " )<< name_ << bf::log::endlf;
   BFJob *pJob;
   // A NULL pointer coming back from the queue is a signal to exit the processing
   // (i.e. terminate the thread)
   while( jobQueue_->popJob( pJob ) && NULL != pJob ) {
      {
         BFGuard g( csStats_ );
         ++cWorkingThreads_;
      }

      try { pJob->run(); } catch( ... ) {}
      delete pJob;

      {
         BFGuard g( csStats_ );
         --cWorkingThreads_;
         ++cJobsProcessed_;
      }
   }
   bf::log::theLog << bf::log::information << I_( "thread exiting from thread pool " )<< name_ << bf::log::endlf;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFThreadPool.cpp-arc  $
//
//   Rev 1.9   Mar 01 2005 18:21:50   smithdav
//Add additional logging.
//
//   Rev 1.8   Feb 01 2005 15:03:42   smithdav
//removed start pool event.
//
//   Rev 1.7   Jan 27 2005 10:37:56   smithdav
//Major thread pool rework. Esp. thread reaper.
//
//   Rev 1.6   Nov 17 2003 19:09:12   PURDYECH
//Added proper support to remove threads while the pool is still active.
//
//   Rev 1.5   May 01 2003 10:51:52   PURDYECH
//Added code to support thread naming.
// 
//    Rev 1.4   Mar 11 2003 10:23:50   PURDYECH
// Support the ability to add and remove threads from the pool.
// 
//    Rev 1.3   Oct 09 2002 17:41:22   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   03 Oct 2001 15:09:56   SMITHDAV
// Syncronization changes and Job Queue changes
// 
//    Rev 1.1   24 Jul 2001 19:49:46   PURDYECH
// Removed Debug console messages.
// 
//    Rev 1.0   Jun 28 2001 09:48:04   PURDYECH
// Initial revision.
// 
//    Rev 1.0   Jun 26 2001 12:01:06   PURDYECH
// Initial revision.
 * 
 *    Rev 1.12   Sep 01 2000 11:17:18   YINGZ
 * add sync in runThread
 * 
 *    Rev 1.11   Aug 23 2000 11:15:04   DT24433
 * changed to use BFThread::setJob instead of giveJob (name change) and removed call to takeJob (handled in BFThread class)
 * 
 *    Rev 1.10   Jun 22 2000 17:24:46   POPESCUS
 * clean-up, comments
 * 
 *    Rev 1.9   Jun 16 2000 15:31:36   POPESCUS
 * fixed the mechanism that grows the pool
 * 
 *    Rev 1.8   Jun 06 2000 10:47:34   POPESCUS
 * cleaned up the code to support only one threading model
 * 
 *    Rev 1.7   May 30 2000 15:12:48   POPESCUS
 * sync fix
 * 
 *    Rev 1.6   May 28 2000 13:38:08   POPESCUS
 * save work
 * 
 *    Rev 1.5   May 26 2000 16:07:16   POPESCUS
 * fixes related to growing the size of the socket queue 
 * 
 *    Rev 1.4   May 25 2000 13:16:46   POPESCUS
 * added some comments
 * 
 *    Rev 1.3   May 25 2000 11:55:02   VASILEAD
 * Fixed release problem
 * 
 *    Rev 1.2   Feb 16 2000 13:09:48   POPESCUS
 * Initial revision
 * 
 * 
 */