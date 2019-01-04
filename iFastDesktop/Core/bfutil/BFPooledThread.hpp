#pragma once

#include <bfutil\bfthread.hpp>

class BFThreadPool;

class BFPooledThread : public BFThread
{
public:   

   BFPooledThread( BFThreadPool *threadPool, bfutil::PTHRDNAMEFN pThreadNameFunc = NULL );
   virtual ~BFPooledThread();

protected:
   void run();

private:
   BFThreadPool *threadPool_;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFPooledThread.hpp-arc  $
//
//   Rev 1.3   May 02 2003 15:46:08   PURDYECH
//Cosmetic changes.
//
//   Rev 1.2   May 01 2003 10:51:38   PURDYECH
//Added code to support thread naming.
//
//   Rev 1.1   Oct 09 2002 17:41:18   PURDYECH
//New PVCS Database
//
//   Rev 1.0   03 Oct 2001 16:37:16   SMITHDAV
//Initial revision.
 */