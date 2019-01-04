#include "stdafx.h"

#include "bfjobqueue.hpp"
#include "bfjob.hpp"
#include "bfexception.hpp"
#include "bfwaitableset.hpp"
#include "bfguard.hpp"
#include "txnstats.hpp"

//***********************************************************************
BFInternalJobQueue::BFInternalJobQueue( int maxJobsQueued ):
_maxJobsQueued( maxJobsQueued ),
_currentJobsQueued( 0 ),
_jobQueueCritSec(),
_jobPushSemaphore( maxJobsQueued, maxJobsQueued ),
_jobPopSemaphore( 0, maxJobsQueued ),
_closedEvent( true )           //manual reset event, initially non-signaled
{
   // push wait object set
   _pushWaitObjects[0] = &_jobPushSemaphore;
   _pushWaitObjects[1] = &_closedEvent;

   // pop wait object set
   _popWaitObjects[0]  = &_jobPopSemaphore;
   _popWaitObjects[1]  = &_closedEvent;
}

//***********************************************************************
BFInternalJobQueue::~BFInternalJobQueue() {
   close();
}

//***********************************************************************
void BFInternalJobQueue::close() {
   BFGuard closeGuard( _closeCritSec ); // one closer at a time

   if( _closedEvent.wait(0) )
      return; // already closed

   // starve push semaphore to prevent subsquent pushes
   for( int i=0; i<_maxJobsQueued; i++ )
      _jobPushSemaphore.wait( INFINITE );

   _closedEvent.set();

}

//***********************************************************************
bool BFInternalJobQueue::isClosed() {
   return(_closedEvent.wait(0));
}

//***********************************************************************
int BFInternalJobQueue::getMaxJobsQueued() const {
   return(_maxJobsQueued); 
}

//***********************************************************************
int BFInternalJobQueue::getCurrentJobsQueued() const { 
   return(_currentJobsQueued); 
}

//***********************************************************************
bool BFInternalJobQueue::pushJob( BFJob *job, DWORD timeout /*= INFINITE*/ ) {

   // wait (forever) for push semaphore or closed event
   BFKernel *waitResult = NULL;
   if( !BFWaitableSet( _pushWaitObjects, 2).wait( waitResult, timeout ) )
      return(false);

   if( *waitResult == _closedEvent )
      throw BFException("BFJobQueue: queue closed - push failed.");
   {
      BFGuard jobQueueGuard( _jobQueueCritSec );

      _jobQueue.push(job);
      _currentJobsQueued++;
   }

   _jobPopSemaphore.release( 1 );

   return(true);

}

//***********************************************************************
bool BFInternalJobQueue::popJob( BFJob *&job, DWORD timeout /*= INFINITE*/ ) {

   // wait for pop semaphore or closed event
   BFKernel *waitResult = NULL;
   if( !BFWaitableSet( _popWaitObjects, 2).wait( waitResult, timeout ) ||  *waitResult == _closedEvent )
   {
      job = NULL;
      return(false);
   }

   {
      BFGuard guard( _jobQueueCritSec );

      job = _jobQueue.front();
      _jobQueue.pop();
      _currentJobsQueued--;
   }

   _jobPushSemaphore.release( 1 );

   return(true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFJobQueue.cpp-arc  $
//
//   Rev 1.6   Jan 27 2005 10:33:22   smithdav
//Refactor BFJobQueue to extract a sub-class BFInternalJobQueue. BFJobQueue becomes a pure virtual interface.
//
//   Rev 1.5   Nov 17 2003 19:07:34   PURDYECH
//Allow NULL jobs to be added to Queue.
//
//   Rev 1.4   Apr 30 2003 13:39:08   PURDYECH
//Fixed bad fix for incorrect guard mechanism on BFJobQueue::close
//
//   Rev 1.3   Apr 28 2003 13:35:38   PURDYECH
//Incorrect guard mechanism on BFJobQueue::close
// 
//    Rev 1.2   Oct 09 2002 17:41:16   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   22 May 2002 17:56:44   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   03 Oct 2001 15:15:42   SMITHDAV
// Initial revision.
 */