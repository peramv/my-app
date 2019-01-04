#ifndef DIPORT_H
#define DIPORT_H

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

#ifndef PLATFORM_H
   #include "platform.h"
#endif

#ifndef INCLUDED_DSTRINGA
#define INCLUDED_DSTRINGA
   #include "dstringa.hpp"
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

DICORE_LINKAGE PVOID CreateBuffer(const DString &strFunc, DWORD dwSize);

DICORE_LINKAGE PCHAR DeleteBuffer(PCHAR pch);

DICORE_LINKAGE DWORD GetCurrentID(bool bThread);

DICORE_LINKAGE DWORD DSTGetCurrentProcessId(void);

DICORE_LINKAGE DWORD DSTGetCurrentThreadId(void);

// just put passed thread in map without creating one
DICORE_LINKAGE bool RegisterChildThread(DWORD dwThread);

// just remove passed thread from map without ending it,
// 0 == unregister current one
DICORE_LINKAGE bool UnregisterChildThread(DWORD dwThread = 0);

DICORE_LINKAGE DWORD CreateAnotherThread(
      PVOID pfn,        // address of function to execute in new thread
      PVOID pvArgList,  // argument or address of argument to new thread
      HANDLE *pHandle,  // to contain new thread handle
      DWORD *pdwID      // to contain new thread ID
      );

DICORE_LINKAGE DWORD EndAnotherThread(
      DWORD dwRetval = 0,             // exit code for thread
      bool bClose = true,             // close thread only applicable on WIN32
      HANDLE handle = (HANDLE) NULL   // non null only has significance on
      );                              //    WIN32 when bClose == TRUE

DICORE_LINKAGE DWORD GetConnectionId(DWORD dwThreadId = 0);

DICORE_LINKAGE DWORD SetConnection(DWORD dwConnection);

DICORE_LINKAGE DWORD RemoveConnection(DWORD dwConnection);

#endif // DIPORT_H


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
// $Log:   Y:/VCS/iFastAWD/inc/diport.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:12   kovacsro
//Initial revision.
// 
//    Rev 1.6   23 Oct 2000 17:19:10   dt14177
// cleanup
// 
//    Rev 1.5   May 08 2000 08:13:52   dtwk
// Make some thread functions public due to removal of "Larry code"
// 
//    Rev 1.4   24 Feb 1999 10:44:50   DT14177
// sync up with tracer
// 
//    Rev 1.3   18 Feb 1999 10:39:42   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:06:18   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:41:48   DMUM
// Check in for DICORE
//

