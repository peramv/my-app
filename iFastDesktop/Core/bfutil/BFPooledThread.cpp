#include "stdafx.h"

#include "BFPooledThread.hpp"
#include "BFThreadPool.hpp"

//***********************************************************************
BFPooledThread::BFPooledThread( BFThreadPool *threadPool, bfutil::PTHRDNAMEFN pThreadNameFunc ) 
: BFThread( pThreadNameFunc )
, threadPool_( threadPool )
{
   start();
}

//***********************************************************************
BFPooledThread::~BFPooledThread()
{
}

//***********************************************************************
void 
BFPooledThread::run()
{
   threadPool_->incrementThreadCount();
   try { threadPool_->runJobs(); } catch(...) {}
   threadPool_->decrementThreadCount();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFPooledThread.cpp-arc  $
//
//   Rev 1.5   Jan 27 2005 10:37:58   smithdav
//Major thread pool rework. Esp. thread reaper.
//
//   Rev 1.4   Nov 17 2003 19:08:32   PURDYECH
//Remove ourself from the threadpool once we are finished.
//
//   Rev 1.3   May 02 2003 15:45:50   PURDYECH
//Make sure that the thread name function gets passed through to BFThread.
//
//   Rev 1.2   May 01 2003 10:51:30   PURDYECH
//Added code to support thread naming.
// 
//    Rev 1.1   Oct 09 2002 17:41:18   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   03 Oct 2001 16:37:16   SMITHDAV
// Initial revision.
 */