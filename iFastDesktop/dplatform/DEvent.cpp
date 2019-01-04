// DEvent.cpp: implementation of the DEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "DEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DEvent::DEvent(bool manualReset)
{
   hEvent = CreateEvent(NULL, manualReset?TRUE:FALSE, FALSE, NULL);
   if( NULL == hEvent )
      throw DEventInitFailed();
}

DEvent::~DEvent()
{
   CloseHandle(hEvent);
}

bool 
DEvent::wait(long ms) const
{
   DWORD retValue = WaitForSingleObject(hEvent, ms==-1?INFINITE:ms);

   if( WAIT_TIMEOUT == retValue )
      return(false);

   if( WAIT_FAILED == retValue )
      throw DEventWaitFailed();

   return(true);

}

void 
DEvent::set() const
{
   if( FALSE == SetEvent(hEvent) )
      throw DEventSetFailed();
}