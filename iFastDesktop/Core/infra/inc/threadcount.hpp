#ifndef THREADCOUNT_HPP
#define THREADCOUNT_HPP

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
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DITEST */    

#ifndef MUTEXSEMAPHORE_HPP
   #include "mutexsemaphore.hpp"
#endif

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

/**
 * Class used for thread testing.  Use the static methods of ThreadCount
 * for testing components on multiple threads.
 *
 * <b>Example:</b>
 * <pre>
 * void worker( void *pData )
 * {
 *    // Do Testing Here
 *    DString strMsg = I_("Working...");
 *    ThreadCount::std_out( strMsg );
 * }
 *
 * void main( int argc, char *argv[] )
 * {
 *    // Spin off 100 threads, giving each distinct data.  Hold the first
 *    // 60 threads and let the remaining begin immediately.
 *
 *    for ( int count = 0; count < 100; ++count )
 *    {
 *       void *pParam = (void *)count;
 *       ThreadCount::beginThread( worker, 0, pParam, count < 60 );
 *    }
 *
 *    ThreadCount::releaseThreads();
 *    ThreadCount::waitForThreads();
 *
 *    // Spin off 100 threads giving all the threads the same data.  Have
 *    // 60 of the threads held and have 40 of them begin immediately.
 *
 *    ThreadCount::runThreads( worker, 20, &threadedAddition, 60, 40 );
 *    ThreadCount::waitForThreads();
 * }
 *</pre>
 */
class DITEST_LINKAGE ThreadCount
{
public:
   typedef void ( __cdecl * THREAD_PROC )( void * );

   enum CoutLevel
   {
      CL_NONE = 0,
      CL_LOW,
      CL_MEDIUM,
      CL_HIGH,
      CL_ALL
   };

public:

   /**
    * Sets the filter used by std_cout().  Call this method to affect how many
    * messages are output for a thread.
    */
   static void setCoutLevel( CoutLevel cl );

   /**
    * This method replaces the _beginthread() method provided in the
    * C++ compiler.  It has one additional perameter to indicate whether
    * the thread should be held (wait) until the releaseThreads()
    * method is called.
    *
    * @param start_address - Start address of routine that begins execution of
    *                        new thread.
    *
    * @param stack_size - Stack size for new thread or 0
    *
    * @param arglist - Argument list to be passed to new thread or NULL.
    *
    * @param wait - If true, waits for releaseThreads() else begins immediately.
    */
   static void beginThread( THREAD_PROC start_address,
                            unsigned stack_size,
                            void *arglist,
                            bool wait = false );

   /**
    * Method to release threads.  Call this method to release those threads
    * that were held by passing a true as the wait paramenter for
    * beginThread().
    */
   static void releaseThreads();

   /**
    * Waits for all the threads to terminate.  Call this method to wait for all
    * the threads to end.
    */
   static void waitForThreads();

   /**
    * Method to start a number of threads.  If you want the same data to be
    * passed to all the threads, use this method.  Otherwise, if you want
    * different data to be used for different threads, use beginThread().
    *
    * @param start_address - Start address of routine that begins execution of
    *                        new thread.
    *
    * @param stack_size - Stack size for new thread or 0
    *
    * @param arglist - Argument list to be passed to new thread or NULL.
    *
    * @param holdAndReleaseCount - The number of threads to be held and
    *                              released all at once.
    *
    * @param startImmediatelyCount - The number of threads to begin immediate
    *                              execution.
    */
   static void runThreads( THREAD_PROC start_address,
                           unsigned stack_size,
                           void *arglist,
                           unsigned holdAndReleaseCount,
                           unsigned startImmediatelyCount );

   /**
    * Method to start a number of threads and pass each thread a TestData
    * object.  This method will return true if any of the tests failed.  If you
    * want the same custom data to be passed to all the threads, use this
    * method.  Otherwise, if you want different custom data to be used for
    * different threads, use beginThread().
    *
    * @param start_address
    *                   - Start address of routine that begins execution of
    *                   new thread.
    *
    * @param stack_size - Stack size for new thread or 0
    *
    * @param arglist - Argument list to be passed to new thread or NULL.
    *
    * @param holdAndReleaseCount - The number of threads to be held and
    *                              released all at once.
    *
    * @param startImmediatelyCount - The number of threads to begin immediate
    *                                execution.
    *
    * @return True if any test failed.
    */
   static bool runThreadsWithTestData( THREAD_PROC start_address,
                                       unsigned stack_size,
                                       void *arglist,
                                       unsigned holdAndReleaseCount,
                                       unsigned startImmediatelyCount );

   /**
    * Thread safe method to be used by the thread function for standard output.
    *
    * @param strOut - Output string.
    */
   static void std_out( const DString &strOut, CoutLevel cl = CL_HIGH );

   /**
    * Thread safe method to be used by the thread function for error output.
    *
    * @param strOut - Output string.
    */
   static void std_err( const DString &strErr );

private:
   static void threadProc( void *pParams );

   static int s_count;
   static int s_hold;
   static int s_waiting;
   static CoutLevel s_level;
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
// $Log:   Y:/VCS/iFastAWD/inc/threadcount.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:06   kovacsro
//Initial revision.
//
//   Rev 1.5   28 Nov 2000 14:32:18   dt14177
//cleanup
//
//   Rev 1.4   Mar 09 2000 14:37:50   DMUM
//Moved TestSection into seperate source files
//
//   Rev 1.3   Mar 08 2000 14:39:44   DMUM
//TestCount more robust.  Ported TestData from 1.7
//
#endif // THREADCOUNT_HPP
