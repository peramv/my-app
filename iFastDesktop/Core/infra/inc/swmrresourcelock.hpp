#ifndef RESOURCELOCK_HPP
#define RESOURCELOCK_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 */

/**@pkg DICORE */ 

#pragma message( "including "__FILE__ )


#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif 

#ifndef MUTEXSEMAPHORE_HPP
   #include "mutexsemaphore.hpp"
#endif 

#ifndef EVENTSEMAPHORE_HPP
   #include "eventsemaphore.hpp"
#endif 


#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif


/**
 * This class implements a single-write-multi-read critical section for
 * multithreaded applications.   Used properly it creates the following
 * rules:
 *    - Only one thread may access the critical section when the 
 *      resource is being accessed for a "write".
 *    - An unlimited number of threads may concurrently access the
 *      critical section for "reads".
 *    - Recursive calls to lock the resource are supported. For example, a 
 *      thread that has acquired the resource for a write, may attempt to 
 *      acquire the resource for writing without blocking.
 *    - If a thread has acquired the resource for writing, it may also acquire
 *      the resource for reading without blocking.
 *    - If a thread has acquired the resource for reading and is the only thread
 *      reading, it may also acquire the resource for writing without blocking.
 *      
 * This class is designed to be used with CriticalSection (see 
 * CriticalSection.hpp).
 * If this class is used without CriticalSection, then the acquire-release 
 * method pairs must be called in the correct sequence.
 * If an "acquire" method is called, then the matching "release" MUST be called
 * by the thread that called "acquire".
 *
 * This class also supports reqursive calls to these methods. For example, if a
 * thread calls acquireForWrite(), it make multiple calls to acquireForRead()
 * and acquireForWrite() without blocking.  However, the thread must be sure to
 * call releaseFrom* for each acquireFor* method called.
 *
 * DEADLOCK warning - one easy way to deadlock threads using these classes is to
 * acquire the resource for reading and then attempt to recursively acquire the
 * resource for writing. Example:
 * Thread1 and thread2 both acquire for reading (which is valid).  Thread1 
 * attempts to acquire for writing, but is blocked until it is the only thread
 * accessing the resource (it must wait until thread2 releases its read lock).
 * However, instead of releasing the read lock, thread2 attempts to acquire a
 * write lock.  Thread2 will block until thread1 releases its read and write 
 * locks, but this will never happen because thread1 is waiting on thread2.
 *
 * A good rule of thumb for recursive calls is:
 *       Write then read; never read then write.
 * 
 * @author DST Systems Inc
 * @see CriticalSection.hpp
 */
class DICORE_LINKAGE SWMRResourceLock
{
public:

   /**
    * Create a SWMR critical section for a given shared resource.
    */
   SWMRResourceLock();

   /**
    * Attempt to gain access to the resource for reading.  This method will
    * block if another thread has access to the resource for writing.
    *
    * If this method is called, the calling thread MUST also call
    * releaseFromRead().
    */
   void acquireForRead();

   /**
    * Attempt to gain access to the resource for writing.  This method will
    * block if another thread has access to the resource for either writing or
    * reading.
    *
    * If this method is called, the calling thread MUST also call
    * releaseFromWrite().
    */
   void acquireForWrite();

   /**
    * Release one level of read locking on a shared resource.  This method
    * should only be called by threads that have called acquireForRead().
    *
    * If the calling thread is the only thread that has a read lock on the
    * resource, one thread that is waiting to acqure a write lock on the 
    * resource will gain control of the resource.
    */
   void releaseFromRead();

   /**
    * Release one level of read locking on a shared resource.  This method
    * should only be called by threads that have called acquireForWrite().
    *
    * If there are any threads waiting to acquire the resource, either
    * one thread will acquire it for writing, or all threads waiting to acquire
    * the resource for reading will resume processing.
    */
   void releaseFromWrite();

private:

   enum RESOURCE_STATUS
   {
      SWMR_NONE,
      SWMR_READING,
      SWMR_WRITING
   };

   void _incrementThreadReadCount( DWORD dwCurrentThread );
   void _decrementThreadReadCount( DWORD dwCurrentThread );
   bool _onlyThreadReading( DWORD dwCurrentThread );

   MutexSemaphore m_mutexStatus;
   EventSemaphore m_eventStatusChanged;
   RESOURCE_STATUS m_enumStatus;
   DWORD m_dwCurrentWritingThread;

   typedef std::map< DWORD, int, std::less< DWORD > >READER_COUNT_MAP;
   READER_COUNT_MAP m_mapReadingThreads;
   int m_iNumWritingLocks;
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
// $Log:   Y:/VCS/iFastAWD/inc/swmrresourcelock.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:52   kovacsro
//Initial revision.
//
//   Rev 1.3   28 Nov 2000 10:48:42   dt14177
//cleanup
//
//   Rev 1.2   Apr 10 2000 11:49:22   dtwk
//Add JavaDoc comments
//Add support for recursive calls
//
//   Rev 1.1   Apr 04 2000 07:11:38   dtwk
//Change enum values due to conflict with DIAWD23
//
//   Rev 1.0   Apr 03 2000 15:58:50   dtwk
// 
// 

#endif // SWMRRESOURCELOCK_HPP
