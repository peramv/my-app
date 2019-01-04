#ifndef LOCK_HPP
#define LOCK_HPP

#pragma message( "including "__FILE__ )

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

#ifndef DIPORT_H
   #include "diport.h"
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * Class: Lock
 *
 * Description: Pure base class representing interface for lock types used by
 *  Guard
 */

class DICORE_LINKAGE Lock
{
public:
   /**
    * Constructor
    *
    */
   Lock()
   {}

   /**
    * Destructor
    */
   virtual ~Lock()
   {}

   /**
    * Method called to acquire lock
    */
   virtual void lock() = 0;
   /**
    * Method called to release lock
    */
   virtual void unlock() = 0;
private:
   Lock( const Lock & );
   Lock & operator=( const Lock & );
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
// $Log:   Y:/VCS/iFastAWD/inc/lock.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:14   kovacsro
//Initial revision.
//
//   Rev 1.2   May 18 2001 15:44:04   dt24433
// 
//
//   Rev 1.0   May 18 2001 14:38:38   DT21858
// 
//
//

#endif


