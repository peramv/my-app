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

#ifndef DIPORT_H
   #include <diport.h>
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
   Lock& operator=( const Lock & );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/lock.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:08   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:00   SMITHDAV
//Initial revision.
//
//   Rev 1.2   May 18 2001 15:44:04   dt24433
// 
//
//   Rev 1.0   May 18 2001 14:38:38   DT21858
// 
//
//

