#ifndef THREADTEST_HPP
#define THREADTEST_HPP

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
 *    Copyright 1999, 2000 by DST Systems, Inc.
 */

/**@pkg DITEST */

/* FILE: threadtest.hpp */

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif


#include "eventsemaphore.hpp"
#include <process.h>    /* _beginthread, _endthread */

class ThreadTest;

class TestData;

typedef void ( _cdecl * P_FN )( void * );

typedef void ( _cdecl * PFN_I_CHAR )( I_CHAR * );

typedef void ( _cdecl * PFN_PVOID )( void * );

typedef void ( _cdecl * PFN_VOID )();

/**
*      used to test thread-awareness of external methods.
*
* DESCRIPTION:
*
*      The ThreadTest constructor is designed to have an interface like
*      _beginthread().  It can also be used as a base class if
*      inheritance is required to complete the test.  A variable number
*      of threads can be executed; they can be sequenced or let loose
*      all at once.  Facility is provided for pre- and post- test
*      processing.  std::out is wrapped in order to guarantee coherence
*      of the output.
*
*/

class DITEST_LINKAGE ThreadTest
{
////////////////////////
// Interface
   public:

      /**
      * This constructor is for those who prefer to use
      *    callback construction.
      *
      * @param     I_CHAR * - name of semaphore (method name)
      * @param     PVN_PVOID - the test function
      * @param     int - stack size for the thread
      * @param     void * - a pointer to the data block for
      *            the test function
      * @param     int numStartTogetherThreads - these are only
      *            released after they have all been started
      * @param     int numStartSeparatelyThreads - these are
      *            released individually at the beginning
      * @param     PVN_VOID - an optional function to call when
      *            preparation for the test needs to be done
      * @param     PVN_VOID - the cleanup function
      * @param     PFN_I_CHAR - the exception-handling function
      * @returns   this
      * @exception none
      */
      ThreadTest( PFN_PVOID testFunction,
                  int stackSize = 0,
                  void * data = NULL,
                  int numStartTogetherThreads = 100,
                  int numStartSeparatelyThreads = 0,
                  PFN_VOID prepareFunction = NULL,
                  PFN_VOID cleanupFunction = NULL,
                  PFN_I_CHAR logFn = ( PFN_I_CHAR ) logStdOut );

      /**
      * This constructor is for those who prefer to use
      * inheritance.  Note that the doTest() method must
      * be implemented in the child class
      *
      * @param     int numStartTogetherThreads - these are only
      *            released after they have all been started
      * @param     int numStartSeparatelyThreads - these are
      *            released individually at the beginning
      * @param     int - stack size for the thread
      * @param     void * - a pointer to the data block for
      *            the test function
      * @param     PFN_I_CHAR - the exception-handling function
      * @returns   this
      * @exception none
      */
      ThreadTest( int numStartTogetherThreads = 100,
                  int numStartSeparatelyThreads = 0,
                  int stackSize = 0,
                  void * data = NULL,
                  PFN_I_CHAR logFn = ( PFN_I_CHAR ) logStdOut );
      
      
      /**
      * Virtual Destructor
      *
      * @returns   none
      * @exception none
      */
      virtual ~ThreadTest() {}
   
      /**
      * This method kicks off threads and waits for them to return.
      *
      * @returns   void
      * @exception none
      */
      virtual void doThreadTest();


      /**
      * This method is used to set the exeption handler
      *
      * @param     I_CHAR * - the message to be logged
      * @returns   void
      * @exception none
      */
      void setExceptionHandler( PFN_I_CHAR handler )
      {
         m_exceptionHandler = handler;
      }


      void * getData()
      {
         return m_data;
      }

      /**
      * This method uses cout and is protected by a CriticalSection
      *
      * @param     I_CHAR * - the message to be logged
      * @returns   void
      * @exception none
      */
      static void logStdOut( const I_CHAR * message );
   

////////////////////////
// Protected Methods
   protected:
      /**
      * this is run before the function to be tested
      *
      * @returns   void
      * @exception none
      */
      virtual void prepareTest()
      {
         if ( m_prepareFunction )
            m_prepareFunction();
      }

      /**
      * You can override the following method with a method
      * containing your thread testing code
      *
      * @param     void * - pointer to the data blob to be passed to the
      *            testing function
      * @returns   void
      * @exception none
      */
      virtual void doTest( void * data )
      {
         if ( m_testFunction )
            m_testFunction( data );
      }

      /**
      * this is run after the function to be tested
      *
      * @returns   void
      * @exception none
      */
      virtual void doCleanup()
      {
         if ( m_cleanupFunction )
            m_cleanupFunction();
      }
  
 
////////////////////////
// Private Methods
   private:
        // Copy constructor, not implemented:
      ThreadTest( const ThreadTest & );

        // Assignment operator, not implemented:
      const ThreadTest & operator=( const ThreadTest & );

      /**
      * This method returns the complete sema4
      *
      * @returns   EventSemaphore &
      * @exception none
      */
      EventSemaphore & getCompleteSema4( void )
      {
         return m_completeSema4;
      }

      void static _cdecl testThreadSeparately( TestData * ttest );
      
      void static _cdecl testThread( TestData * ttest );
      

////////////////////////
// Private Data Members
   private:
      PFN_VOID         m_cleanupFunction;
      EventSemaphore   m_completeSema4;
      void *           m_data;
      PFN_I_CHAR       m_exceptionHandler;
//      I_CHAR *         m_name;

      int              m_numStartTogetherThreads;
      int              m_numStartSeparatelyThreads;
      PFN_VOID         m_prepareFunction;
      int              m_refCount;

      MutexSemaphore   m_refCountSema4;
      EventSemaphore   m_sema4;  // used to block threads until all are
                                 // ready to go
      int              m_stackSize;
      PFN_PVOID        m_testFunction;

      int              m_numStartTogetherThreadsCountDown;
      MutexSemaphore   m_numStartTogetherThreadsCountDownSema4;
      int              m_numStartSeparatelyThreadsCountDown;
      MutexSemaphore   m_numStartSeparatelyThreadsCountDownSema4;



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
// $Log:   Y:/VCS/iFastAWD/inc/threadtest.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:08   kovacsro
//Initial revision.
//
//   Rev 1.6   May 18 2000 12:17:40   DT14177
//fixed a pointer bug that was causing semaphore.post() to crash after 200 runs
//
//   Rev 1.5   Apr 11 2000 17:50:06   DT14177
//removed java stuff
//
//   Rev 1.4   Mar 14 2000 14:32:54   DT20842
//Add testData
//
//   Rev 1.3   Mar 03 2000 16:04:30   DT20842
//Fixed so threads started separately will single main program when all done
//
//
//   Rev 1.2   Jan 31 2000 09:57:54   DT14177
//to catch a JVM trap and throw a message we can read; fixed a threading problem with logStdOut
//
//   Rev 1.1   Jan 03 2000 19:44:50   DT14177
//added JavaDoc comments
//
//   Rev 1.0   Nov 19 1999 17:00:58   dtwk
// 
//

#endif // THREADTEST_HPP

