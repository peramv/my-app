#ifndef SRCPRAG_H
#define SRCPRAG_H


/*
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


// This header file contains compiler-specific pragmas that
// should be included in source files.


// Microsoft Visual C++ pragmas
#ifdef _MSC_VER
// Disable the following compiler warnings
// 4237 nonstandard extension used : 'bool' reserved for future use
// 4251 needs to have dll-interface to be used by clients of class
// 4786 identifier truncated to 255 characters
   #pragma warning( disable : 4237 4251 4786 4503 4275 )

   #ifdef DISABLE_MACRO_REDEFINITION_WARNINGS
// 4005 macro redifinition
      #pragma warning( disable : 4005 )
   #endif
#endif

// exception specs are no longer really supported with VC7.1
// to stop warnings we will just turn off the warning altogether
//   C++ is stupid.
#pragma warning( disable: 4290 )

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/srcprag.h-arc  $
//
//   Rev 1.3   Oct 22 2004 09:04:26   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.2   May 14 2004 13:10:04   SMITHDAV
//Add 4275 to the warning disable list.
//
//   Rev 1.1   Oct 09 2002 17:42:16   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:12   SMITHDAV
//Initial revision.
// 
//    Rev 1.5   28 Nov 2000 09:45:22   dt14177
// cleanup
// 
//    Rev 1.4   May 05 2000 11:36:20   DT29758
// added 4503 to disable list
// 
//    Rev 1.3   18 Feb 1999 10:40:08   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:06:54   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:43:22   DMUM
// Check in for DICORE
//
//    Rev 1.3   Nov 09 1997 15:34:48   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.2   Feb 07 1997 15:14:54   DPQD
// Added support for conditional disabling of macro redefinition warnings.
//
//    Rev 1.1   Jan 27 1997 15:02:30   DPQD
// Moved EOF marker past last comment line.
//
//    Rev 1.0   Jan 27 1997 14:57:10   DPQD
//
//
//

#endif

