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

//base class for the MT objects in this DLL
class DICORE_LINKAGE Kernel
{
protected:
   //Constructor
   Kernel();
public:
   //makes this an abstract class
   virtual ~Kernel() = 0;
   //Reads the internal status of the object
   DWORD status();
   //Gets the internal handle
   HANDLE getHandle() const;
   //Waits on the current kernel object
   DWORD wait( DWORD dwMilliSeconds );
   //checks if the current handle is valid
   bool hasValidHandle();
   //another way to get the internal handle
   operator HANDLE() const;
protected:
   HANDLE   _handle;
   DWORD    _dwStatus;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/kernel.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:08   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:00   SMITHDAV
//Initial revision.
//
//   Rev 1.0   May 20 2001 10:04:24   DT11159
// 
//
