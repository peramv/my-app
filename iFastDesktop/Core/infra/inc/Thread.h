#ifndef THREAD_H
#define THREAD_H


#ifdef __unix__
// the following 2 lines may be required for compiling on AIX
#define _POSIX_SOURCE
#define _XOPEN_SOURCE  500
// end AIX specific options
#include <pthread.h>
#else
#include <windows.h>
#endif

#include "Messaging.h"
#include "Runnable.h"
#include "Mutex.h"


namespace MessagingFramework
{

class Thread;


/**
 * The IThreadDoneObserver class is an "interface" (or "callback") that is used
 * to notify when a thread has terminated.  This capability is useful if you want
 * to start a Thread and be notified when the thread execution has completed.
 */
class DIMESSAGE_LINKAGE IThreadDoneObserver
{
   public:
      /**
       * Destructor
       */
      virtual ~IThreadDoneObserver() {}


      /**
       * The method that's called (notified) when the thread has completed its
       * execution.
       *
       * @param pThread - pointer to the Thread object that has completed
       *
       * @see Thread
       */
      virtual void notifyOnThreadDone( Thread* pThread ) = 0;
};



/**
 * The Thread class is used to provide multi-threading capabilities.  The Thread
 * class is modeled after the Thread class in Java (as well as the "Runnable" interface).
 * This class has been written to run in both Win32 and Unix environments.
 */
class DIMESSAGE_LINKAGE Thread : public Runnable
{
   public:
#ifdef __unix__
      typedef pthread_t HTHREAD;
      typedef void* THREAD_RETURN_T;
      typedef THREAD_RETURN_T (*PFN_THREAD_ROUTINE)(void*);
#else
      typedef HANDLE HTHREAD;
      typedef unsigned long THREAD_RETURN_T;
      typedef THREAD_RETURN_T (__stdcall *PFN_THREAD_ROUTINE)(void*);
#endif


      /**
       * Constructor.  When this constructor is used, it must be in the context of a
       * derived class (subclass).  Otherwise, an exception will be thrown when the
       * thread is started.  The derived class <b>MUST OVERRIDE</b> the "run" method.
       *
       * @see run
       */
      Thread();


      /**
       * Constructor - accepts a Runnable interface to use for executing
       *
       * @param - pointer to a Runnable "interface" that will be executed on a separate thread
       *
       * @see Runnable
       */
      Thread( Runnable* pRunnable );


      /**
       * Destructor
       */
      virtual ~Thread();


      /**
       * Starts the thread by spawning a new thread and then calling "run" on the "Runnable"
       * object (either "this" or the Runnable that was used to construct the Thread object).
       *
       * @return boolean indicating success/failure
       *
       * @see Runnable
       */
      bool start();


      /**
       * Although not declared as a pure virtual, this method really only represents an
       * "interface" to be called when the Thread clas has been subclassed.  This "run" method
       * should never be called and will, in fact, throw an exception if it's ever called.
       * If you subclass Thread, your derived class <b>MUST</b> override this method.  It's
       * not marked as a pure virtual, so that it can maintain the same semantics as is
       * used in Java.
       *
       * If a Runnable object was passed into the Thread constructor, then that Runnable's
       * "run" method will be called when the thread is started.
       *
       * @see Runnable
       */
      virtual void run();


      /**
       * Determines if the thread is alive
       *
       * @return boolean indicating whether the thread is alive or not
       */
      bool isAlive() const;


      /**
       * Retrieves the exit code of the thread.  This method should only be
       * called <b>AFTER</b> the thread has exited.  A return value of 0L indicates
       * that the thread has exited normally.  A return value of 1L indicates that
       * either: (1) the thread has not completed yet, or (2) has ended in an error
       * (possibly an exception was thrown in the thread).
       *
       * @return exit code of the thread
       */
      unsigned long getExitCode() const;


      /**
       * Registers an "observer" (callback) that will be notified when the "run"
       * method (of the Runnable) has completed.  This functionality may be safely
       * used with the "autoDelete" capability since the observer will be notified
       * before the Thread object is deleted (if marked as "auto-delete").
       *
       * @param pObserver - pointer to the IThreadDoneObserver interface (a callback)

       * @see IThreadDoneObserver
       * @see clearThreadDoneObserver
       */
      void registerThreadDoneObserver( IThreadDoneObserver* pObserver );


      /**
       * Cancels (clears) the "observer" (callback) that may have been set using
       * the "registerThreadDoneObserver" method.  Once the observer is cleared,
       * it cannot be called (and you won't know when the thread's "run" method has
       * completed.
       *
       * @see IThreadDoneObserver
       * @see registerThreadDoneObserver
       */
      void clearThreadDoneObserver();


      /**
       * Marks the Thread object for "auto-deletion".  CAUTION: this method should
       * <b>ONLY</b> be used for Thread objects that were allocated on the heap and
       * that are no longer referenced after the "start" method is called!!!
       */
      void autoDelete();


      /**
       * Returns the Runnable "interface" that was used to construct the Thread object.
       * If the default constructor was used, the return value will be NULL.
       * If a Runnable pointer was passed in on the constructor, then that Runnable is
       * returned.
       *
       * @return pointer to Runnable object (interface)

       * @see Runnable
       */
      Runnable* getRunnable();


      /**
       * Retrieves the handle (platform-specific) for the thread
       *
       * @return the thread handle
       */
      HTHREAD& getHandle();



   private:
      Thread( const Thread& );
      Thread& operator=( const Thread& );

#ifdef _WIN32
      static unsigned long __stdcall runThread( void* pArgs );
#else
      static void* runThread( void* pArgs );
#endif


      HTHREAD               m_hThread;
      PFN_THREAD_ROUTINE    m_pfnThreadRoutine;
      void*                 m_pThreadArgs;
      Runnable*             m_pRunnable;
      unsigned long         m_ulExitCode;
      bool                  m_isAlive;
      bool                  m_isAutoDelete;
      Mutex                 m_mutexAlive;
      Mutex                 m_mutexExitCode;
      IThreadDoneObserver*  m_pThreadDoneObserver;
};

}

#endif


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


