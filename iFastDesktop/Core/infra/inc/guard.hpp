#ifndef GUARD_HPP
#define GUARD_HPP

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

// forward reference
class Lock;

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * Class: Guard
 *
 * Description: A helper class used to implement locking and provide automatic
 *  cleanup in a specific scope.
 *  An instance of this class should be created on the stack in any method 
 *  requiring synchronization passing in the appropriate Lock object to 
 *  use ( like CriticalSectionLock ).  If lock object 
 *  has a global timeout set, the timeout will be ignored.
 */

class DICORE_LINKAGE Guard
{
public:
   /**
    * Constructor
    * 
    * @param lock - pointer to object to use for locking.  A lock is obtained
	 *  during construction.  (Lock must not be pre-locked when passed in.)
    *  If lock is set to NULL no locking/unlocking is performed.
    */
   Guard(
      Lock *lock
	  );

   /**
    * Destructor - will unlock if necessary
    */
   virtual ~Guard();
   
private:
   Lock *m_lock;				// reference to lock used

   Guard( const Guard & );
   Guard& operator=( const Guard & );
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
// $Log:   Y:/VCS/iFastAWD/inc/guard.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:32   kovacsro
//Initial revision.
//
//   Rev 1.1   May 18 2001 15:36:18   dt24433
// 
// 
//

#endif


