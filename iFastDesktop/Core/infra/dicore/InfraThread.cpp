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

#ifndef INFRATHREAD_HPP
   #include "infrathread.hpp"
#endif

#ifndef INFRAJOB_HPP
   #include "infrajob.hpp"
#endif
#ifndef INFRAEXCEPTION_HPP
   #include "infraexception.hpp"
#endif
#ifndef INFRATHREADPOOL_HPP
   #include "infrathreadpool.hpp"
#endif

#ifndef INCLUDED_PROCESS_H
#define INCLUDED_PROCESS_H
   #include <process.h>
#endif

InfraThread::InfraThread( char *threadName /*=NULL*/ ) :
   _threadPool( NULL ), _uiThreadID( 0 ), _threadName( threadName ), _infrajob( NULL )
{
#ifdef MT_DEBUG
   _threadDebugName = new char[ THREAD_DBG_NAME_LENGTH + 1 ];
   *_threadDebugName = 0;
#endif
}

InfraThread::InfraThread( InfraThreadPool *threadPool, char *threadName /*=NULL*/ ) :
    _threadPool( threadPool ), _uiThreadID( 0 ), _threadName( threadName ), _infrajob( NULL )
{
#ifdef MT_DEBUG
   _threadDebugName = new char[ THREAD_DBG_NAME_LENGTH + 1 ];
   *_threadDebugName = 0;
#endif
}

//it is not the thread responsibillity to remove
//itself from the pool, if the current thread is part
//of a pool
InfraThread::~InfraThread()
{
#ifdef MT_DEBUG
   cout << getThreadDebugName() << "died." << endl;
   cout.flush();
   delete [] _threadDebugName;
   _threadDebugName = NULL;
#endif
   delete _infrajob;
   _infrajob = NULL;
}

void InfraThread::getExitCode( DWORD* pdwExitCode )
{
   if( !::GetExitCodeThread( _handle, pdwExitCode ) )
      throw InfraException();
}

int InfraThread::getPriority()
{
   int iThreadPriorityResult = ::GetThreadPriority( _handle );

   if( iThreadPriorityResult == THREAD_PRIORITY_ERROR_RETURN )
      throw InfraException();
   return iThreadPriorityResult;
}

InfraJob *InfraThread::getJob()
{
   return _infrajob;
}

DWORD InfraThread::getThreadID()
{
   return static_cast<DWORD>( _uiThreadID );
}

bool InfraThread::isAlive()
{
   DWORD dwExitCode;

#ifdef MT_DEBUG
   cout << getThreadDebugName() << " is asked if it is alive." << endl;
   cout.flush();
#endif
   getExitCode( &dwExitCode );
   return hasValidHandle() && dwExitCode == STILL_ACTIVE;
}

void InfraThread::removeJob()
{
// NOTE: May add a permanent flag for jobs that should be reused with thread
   delete _infrajob;
   _infrajob = NULL;
}

DWORD InfraThread::resume()
{
   DWORD dwResumeResult = ::ResumeThread( _handle );

   if( dwResumeResult == 0xFFFFFFFF )
      throw InfraException();
   return dwResumeResult;
}

void InfraThread::run()
{
   if ( _infrajob != NULL )
   {
      try
      {
         _infrajob->run();
      }
      catch( ... )
      {
      }
      // Done so remove
      removeJob();
   }
}

void InfraThread::sleep( DWORD dwMilliseconds /*=1000*/ )
{
   ::Sleep( dwMilliseconds );
}

void InfraThread::setJob( InfraJob *infrajob )
{
   removeJob();  // Make sure none exist - should this be error condiiton?
   _infrajob = infrajob;
}

void InfraThread::setPriority( int nPriority )
{
   if( !::SetThreadPriority( _handle, nPriority ) )
      throw InfraException();
}

bool InfraThread::start( unsigned uInitFlag /*= 0*/,
                    LPSECURITY_ATTRIBUTES lpSecurity /*=NULL*/,
                    unsigned uStackSize /*= 0*/ )
{
   _handle = (HANDLE)_beginthreadex( lpSecurity, uStackSize, ThreadKicker, this,
                                     uInitFlag, &_uiThreadID );
   //check if handle is valid
   if( hasValidHandle() )
   {
#ifdef MT_DEBUG
      sprintf( _threadDebugName, "Thread: %s with id: %d ", _threadName, _uiThreadID );
#endif
      _dwStatus = NO_ERROR;
   }
   else
   {
      _dwStatus = GetLastError();
      throw InfraException();
   }
   return true;
}

DWORD InfraThread::suspend()
{
   DWORD dwSuspendResult = ::SuspendThread( _handle );

   if( dwSuspendResult == 0xFFFFFFFF )
      throw InfraException();
   return dwSuspendResult;
}

void InfraThread::terminate( DWORD dwExitCode /*=0*/ )
{
   if( !::TerminateThread( _handle, dwExitCode ) )
      throw InfraException();
}

#ifdef MT_DEBUG
const char *InfraThread::getThreadDebugName()
{
   return _threadDebugName;
}
#endif

unsigned _stdcall InfraThread::ThreadKicker( void* lpThreadParameter )
{
   //get the current thread
   InfraThread* _thread = static_cast<InfraThread*>( lpThreadParameter );
   //if the thread is part of a pool then the pool will know
   //how to manage the life of the thread
   if ( _thread->_threadPool != NULL )
   {
      _thread->_threadPool->runThread();
   }
   else
   {
      _thread->run();
   }
   return 0;
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraThread.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:06   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:22:36   DT11159
// 
//
//
