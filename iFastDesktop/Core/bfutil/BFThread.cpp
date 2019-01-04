#include "stdafx.h"

#include "BFThread.hpp"
#include "bfexception.hpp"

#include "txnstats.hpp"

namespace bfutil
{
   // This whole mess of code is just a hack to give a thread a 'name' when it is running
   // under the Microsoft Visual Studio Debugger.  The following struct is defined by M$
   // and interpreted by the Debugger to provide a name for a thread

   typedef struct tagTHREADNAME_INFO
   {
       DWORD dwType;        // must be 0x1000
       const char* pszName; // pointer to name (in same addr space)
       DWORD dwThreadID;    // thread ID (-1 caller thread)
       DWORD dwFlags;       // reserved for future use, most be zero
   } THREADNAME_INFO;

   static const DWORD MS_VC_EXCEPTION = 0x406d1388;   // defined by M$.  Trapped by VC Debugger to name a thread

   void setThreadName(DWORD dwThreadID, const char* pszThreadName)
   {
       THREADNAME_INFO info;
       info.dwType = 0x1000;
       info.pszName = pszThreadName;
       info.dwThreadID = dwThreadID;
       info.dwFlags = 0;
   
       __try
       {
           ::RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(DWORD), (DWORD *)&info);
       }
       __except (EXCEPTION_CONTINUE_EXECUTION)
       {
       }
   }
}



//***********************************************************************
void BFThread::sleep( DWORD dwMilliseconds /*=1000*/ )
{
   ::Sleep( dwMilliseconds );
}

//***********************************************************************
BFThread::BFThread( bfutil::PTHRDNAMEFN pThreadNameFunc ) 
: tid_( -1 )
, pThreadNameFunc_( pThreadNameFunc )
{
}

//***********************************************************************
BFThread::~BFThread()
{
}

//***********************************************************************
DWORD BFThread::getThreadID() const
{
   return( tid_ );
}

//***********************************************************************
int BFThread::getPriority() const
{
   int iThreadPriorityResult = ::GetThreadPriority( _handle );

   if( iThreadPriorityResult == THREAD_PRIORITY_ERROR_RETURN )
      throw BFException();

   return(iThreadPriorityResult);

}

//***********************************************************************
void BFThread::setPriority( int nPriority )
{
   if( !::SetThreadPriority( _handle, nPriority ) )
      throw BFException();
}

//***********************************************************************
void BFThread::suspend()
{
   DWORD dwSuspendResult = ::SuspendThread( _handle );

   if( dwSuspendResult == 0xFFFFFFFF )
      throw BFException();
}

//***********************************************************************
bool BFThread::resume()
{
   DWORD dwResumeResult = ::ResumeThread( _handle );

   if( dwResumeResult == 0xFFFFFFFF )
      throw BFException();

   return( dwResumeResult == 0 );
}

//***********************************************************************
void BFThread::start( unsigned uStackSize /*= 0*/ )
{
   if( _handle != NULL )
      return;

   _handle = (HANDLE)_beginthreadex( NULL, uStackSize, ThreadKicker, this, 0, reinterpret_cast< unsigned int*>( &tid_ ) );

   //check if handle is valid
   if( _handle == NULL )
      throw BFException();
}

//***********************************************************************
void BFThread::startSuspended( unsigned uStackSize /*= 0*/ )
{
   if( _handle != NULL )
      return;

   _handle = (HANDLE)_beginthreadex( NULL, uStackSize, ThreadKicker, this, CREATE_SUSPENDED, reinterpret_cast< unsigned int*>( &tid_ ) );

   //check if handle is valid
   if( _handle == NULL )
      throw BFException();
}

//***********************************************************************
unsigned _stdcall BFThread::ThreadKicker( void* lpThreadParameter )
{
   BFThread* pThread = static_cast<BFThread*>( lpThreadParameter );
   if( NULL != pThread->pThreadNameFunc_ )
   {
      std::string str = (pThread->pThreadNameFunc_)( pThread->tid_ );
      bfutil::setThreadName( pThread->tid_, str.c_str() );
   }

   pThread->run();
   return(0);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFThread.cpp-arc  $
//
//   Rev 1.6   May 01 2003 10:51:42   PURDYECH
//Added code to support thread naming.
//
//   Rev 1.5   Apr 28 2003 14:48:28   PURDYECH
//Added setThreadName 
// 
//    Rev 1.4   Oct 09 2002 17:41:20   PURDYECH
// New PVCS Database
// 
//    Rev 1.3   May 28 2002 12:15:58   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.2   03 Oct 2001 15:09:56   SMITHDAV
// Syncronization changes and Job Queue changes
// 
//    Rev 1.1   24 Jul 2001 19:49:44   PURDYECH
// Removed Debug console messages.
// 
//    Rev 1.0   Jun 28 2001 09:48:04   PURDYECH
// Initial revision.
// 
//    Rev 1.0   Jun 26 2001 12:01:06   PURDYECH
// Initial revision.
 * 
 *    Rev 1.5   Nov 14 2000 10:19:16   VASILEAD
 * Memory leak ?
 * 
 *    Rev 1.4   Aug 23 2000 11:08:42   DT24433
 * Use Job::run method during run method
 * 
 *    Rev 1.3   Apr 04 2000 10:22:34   POPESCUS
 * fixes for the server sync-up
 * 
 *    Rev 1.2   Feb 16 2000 13:09:48   POPESCUS
 * Initial revision
 * 
 * 
 */