#ifndef THREAD_HPP
#define THREAD_HPP

#pragma message( "including "__FILE__ )

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

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef PLATFORM_H
   #include "platform.h"
#endif

#ifndef INFRAKERNEL_HPP
   #include "infrakernel.hpp"
#endif

#ifndef THREADPOOL_HPP
/**@#-*/  // forward declarations
class InfraThreadPool;
/**@#+*/
#endif

#ifndef INFRAJOB_HPP
/**@#-*/  // forward declarations
class InfraJob;
/**@#+*/
#endif

// Import/Export resolution
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

#ifdef MT_DEBUG
   #define THREAD_DBG_NAME_LENGTH    1024
#endif

class DICORE_LINKAGE InfraThread : public InfraKernel
{
private:
   friend InfraThreadPool;
public:
   InfraThread( char *threadName = NULL );
   InfraThread( InfraThreadPool *threadPool, char *threadName = NULL );
   virtual ~InfraThread();

   //Read a thread's exit code
   void getExitCode( DWORD *pdwExitCode );
   //Get the thread's priority
   int getPriority();
   //Checks if the thread is still alive
   bool isAlive();
   //Get the thread ID
   DWORD getThreadID();
   //Resume the thread
   DWORD resume();
   // sets the thread's current job, existing job will be deleted if necessary
   void setJob( InfraJob *infrajob );
   //Set the thread's priority
   void setPriority( int nPriority );
   //Put the thread at rest for a while (default 1 second)
   void sleep( DWORD dwMilliseconds = 1000 );
   //Causes this thread to begin execution
   /**
     * uInitFlag  -- Initial state of new thread (0 for running or CREATE_SUSPEND
     *               for suspended)
     * lpSecurity -- Security descriptor for new thread
     * uStackSize -- number of bytes to allocate for the new thread's stack
     *               if this is 0 the stack size will be the same as the primary thread
     *               of the current process. The system sets an upper limit of 1 MB
     *               on stack size.
     */
   bool start( unsigned uInitFlag = 0, LPSECURITY_ATTRIBUTES lpSecurity = NULL,
               unsigned uStackSize = 0 );
   //Suspend the thread
   DWORD suspend();
   /**
     * Interrupt's the thread's execution
     * Terminate is a dangerous function that should
     * only be used in the most extreme cases. It calls ::TerminateThread, see help
     * for that.
     */
   void terminate( DWORD dwExitCode = 0 );
#ifdef MT_DEBUG
   const char *getThreadDebugName();
#endif
protected:
   InfraJob *getJob();
   //frees the thread's job
   void removeJob();
   // The default will kick off the associated job
   virtual void run();
private:
   static unsigned _stdcall ThreadKicker( void *lpThreadParameter );
private:
   InfraThreadPool  *_threadPool; //the thread can be part of a pool
   unsigned int     _uiThreadID; //the thread ID
   char             *_threadName; //the thread name
   InfraJob         *_infrajob; //the job to do if part of a pool
#ifdef MT_DEBUG
   char             *_threadDebugName;
#endif
};

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
// $Log:   Y:/VCS/iFastAWD/inc/InfraThread.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:54   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:31:38   DT11159
// 
//
//

#endif
