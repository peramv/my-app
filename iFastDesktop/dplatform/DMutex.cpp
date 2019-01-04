// DMutex.cpp: implementation of the DMutex class.
//
//////////////////////////////////////////////////////////////////////

#include "DMutex.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DMutex::DMutex()
{
   hMutex = CreateMutex(NULL, FALSE, NULL);
   if( NULL == hMutex )
      throw DMutexInitFailed();
}

DMutex::~DMutex()
{
   CloseHandle(hMutex);
}

bool 
DMutex::wait(long ms) const
{
   DWORD retValue = WaitForSingleObject(hMutex, ms==-1?INFINITE:ms);

   if( WAIT_TIMEOUT == retValue )
      return(false);

   if( WAIT_FAILED == retValue )
      throw DMutexWaitFailed();

   return(true);

}

void 
DMutex::release() const
{
   if( FALSE == ReleaseMutex(hMutex) )
      throw DMutexReleaseFailed();
}