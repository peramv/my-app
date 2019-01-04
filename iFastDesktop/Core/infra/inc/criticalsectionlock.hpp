#ifndef CRITICALSECTIONLOCK_HPP
#define CRITICALSECTIONLOCK_HPP

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
 *    Copyright 1996-2001 by DST Systems, Inc.
 */

#ifndef LOCK_HPP
#include "Lock.hpp"
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * Class: CriticalSectionLock
 *
 * Description: Implementation of lock using Win32 critical section.
 */

class DICORE_LINKAGE CriticalSectionLock :public Lock
{
public:
   /**
    * Constructor
    * 
    */
   CriticalSectionLock();

   /**
    * Destructor
    */
   virtual ~CriticalSectionLock();

   /**
    * Method called to acquire CriticalSectionLock
    */
   virtual void lock();
   /**
    * Method called to release CriticalSectionLock
    */
   virtual void unlock();
private:
   CRITICAL_SECTION m_lock;

   CriticalSectionLock( const CriticalSectionLock & );
   CriticalSectionLock& operator=( const CriticalSectionLock & );
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
// $Log:   Y:/VCS/iFastAWD/inc/criticalsectionlock.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:48   kovacsro
//Initial revision.
//
//   Rev 1.1   May 18 2001 15:35:40   dt24433
//Initial check ins.
// 
//

#endif


