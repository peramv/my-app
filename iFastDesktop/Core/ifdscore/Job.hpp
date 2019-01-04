#pragma once

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 */

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef PLATFORM_H
   #include <win32\platform.h>
#endif

// Import/Export resolution
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

//interface used to define a Job
class DICORE_DLL Job
{
public:
   Job();

   //makes this abstract
   virtual ~Job() = 0;

   // Override to provide functionality when invoked to run
   virtual void run() = 0;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/Job.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:08   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:58   SMITHDAV
//Initial revision.
//
//   Rev 1.0   May 20 2001 10:04:18   DT11159
// 
//

