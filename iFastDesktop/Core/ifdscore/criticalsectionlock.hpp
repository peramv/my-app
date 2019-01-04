#pragma once

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
   #include <Lock.hpp>
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

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/criticalsectionlock.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:52   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:44   SMITHDAV
//Initial revision.
//
//   Rev 1.1   May 18 2001 15:35:40   dt24433
//Initial check ins.
// 
//

