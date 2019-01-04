#ifndef MUTEX_H
#define MUTEX_H

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __unix__
#include <pthread.h>
#endif


#include "Messaging.h"

namespace MessagingFramework
{

/**
 * The Mutex class is used to "lock" and "unlock" sections of code
 * for thread synchronization in a multi-threaded environment.  This
 * code is written for use on both Win32 and Unix operating systems.
 */
class DIMESSAGE_LINKAGE Mutex
{
   public:
      /**
       * Constructor. The Mutex will initially be in an "unlocked" state.
       */
      Mutex();

      /**
       * Destructor
       */
      ~Mutex();

      /**
       * Unlocks the Mutex lock.
       */
      void unlock();

      /**
       * Locks the Mutex lock.
       */
      void lock();

   private:
      Mutex( const Mutex& copy );
      Mutex& operator=( const Mutex& copy );

   private:
#ifdef _WIN32
      HANDLE  m_hsem;
#endif

#ifdef __unix__
      pthread_mutex_t  m_mutex;
#endif

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



