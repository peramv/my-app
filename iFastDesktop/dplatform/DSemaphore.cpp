// DSemaphore.cpp: implementation of the DSemaphore class.
//
//////////////////////////////////////////////////////////////////////

#include "DSemaphore.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DSemaphore::DSemaphore(int maxCount)
{
   hSemaphore = CreateSemaphore(NULL, (long)maxCount, (long)maxCount, NULL);
   if( NULL == hSemaphore )
      throw DSemaphoreInitFailed();

}

DSemaphore::~DSemaphore()
{
   CloseHandle(hSemaphore);
}

bool 
DSemaphore::wait(long ms) const
{
   DWORD retValue = WaitForSingleObject(hSemaphore, ms==-1?INFINITE:ms);

   if( WAIT_TIMEOUT == retValue )
      return(false);

   if( WAIT_FAILED == retValue )
      throw DSemaphoreWaitFailed();
   return(true);

}

void 
DSemaphore::release(int releaseCount) const
{
   if( FALSE == ReleaseSemaphore(hSemaphore, releaseCount, NULL) )
      throw DSemaphoreReleaseFailed();
}