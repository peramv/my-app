// DThread.cpp: implementation of the DThread class.
//
//////////////////////////////////////////////////////////////////////

#include "DThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DThread::DThread()
:hThread((HANDLE)-1)
{
}

DThread::~DThread()
{
   join();
}

void 
DThread::start()
{
   hThread = (HANDLE)_beginthread(startThread, 0, this);
   if( (HANDLE)-1 == hThread )
      throw DThreadInitFailed();

}

bool 
DThread::join(long ms)
{
   if( (HANDLE)-1 != hThread )
   {
      DWORD retValue = WaitForSingleObject(hThread, ms==-1?INFINITE:ms);
      if( WAIT_TIMEOUT == retValue )
         return(false);

      if( WAIT_FAILED == retValue )
         return(true);
//         throw DThreadJoinFailed();
   }
   return(true);
}

void __cdecl 
DThread::startThread(void *threadObj)
{
   try { ((DThread *)threadObj)->run(); } catch(...) {}
   _endthread();
   ((DThread *)threadObj)->hThread = (HANDLE)-1;
}
