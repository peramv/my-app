#ifndef CRITICALSECTION_HPP
#define CRITICALSECTION_HPP

#  pragma message( "including "__FILE__ )

/** 
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

/**@pkg DICORE */    

#ifndef MUTEXSEMAPHORE_HPP
#include "mutexsemaphore.hpp"
#endif

#ifndef SWMRRESOURCELOCK_HPP
#include "swmrresourcelock.hpp"
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * Class: CriticalSection
 *
 * Description: A wrapper for MutexSemaphores to implement
 *              critical sections.
 */

class DICORE_LINKAGE CriticalSection
{
// enums
public:

   enum SWMR_MODE
   {
      SWMR_READ,
      SWMR_WRITE
   };


// functions
public:

   /**
    * Default Constructor - used for "delayed"
    * waiting
    */
   CriticalSection();

   /**
    * Constructor
    * 
    * @param mutex
    */
   CriticalSection( MutexSemaphore &mutex );

   /**
    * Constructor
    * 
    * @param pMutex - Pass in 0 for "delayed" waiting
    */
   CriticalSection( MutexSemaphore *pMutex );

   /**
    * Constructor
    * 
    * @param swmr
    * @param swmrMode - SWMR_READ or
    *                   SWMR_WRITE
    */
   CriticalSection( SWMRResourceLock &swmr,
                    SWMR_MODE swmrMode );

   /**
    * Destructor
    */
   virtual ~CriticalSection();

   
   /**
    * Only call this one time, and only if you have used 
    * the default constructor, or passed in 0 for pMutex
    * 
    * @param mutex
    */
   void startCritcalSection( MutexSemaphore &mutex )
   {
      mutex.wait();
      m_pmsem = &mutex;
   };

private:
   CriticalSection( const CriticalSection & );
   CriticalSection& operator=( const CriticalSection & );


// data
private:
   MutexSemaphore *m_pmsem;
   SWMRResourceLock *m_pswmr;
   SWMR_MODE m_swmrMode;
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
// $Log:   Y:/VCS/iFastAWD/inc/criticalsection.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:48   kovacsro
//Initial revision.
// 
//    Rev 1.5   23 Oct 2000 16:58:08   dt14177
// cleanup
// 
//    Rev 1.4   23 Oct 2000 16:47:32   dt14177
// cleanup
// 
//    Rev 1.3   Jun 05 2000 07:53:54   dtwk
// Add support for "delayed" waiting
// 
//    Rev 1.2   Apr 03 2000 15:58:20   dtwk
// Add in SWMRResourceLock support
// 
//    Rev 1.1   Jun 28 1999 11:31:28   DTWK
// Make useable for code outside of DICORE
//
//    Rev 1.0   May 24 1999 10:26:20   DTWK
//
//
//
//

#endif


