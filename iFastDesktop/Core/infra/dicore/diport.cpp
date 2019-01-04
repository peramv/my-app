//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997-1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : diport.cpp
// ^AUTHOR : Larry Parnes
// ^DATE   :
//
// ----------------------------------------------------------
//
// ^CLASS : DebugMgr
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DICORE_H
   #include "dicore.h"
#endif

#ifndef BASE_H
   #include "base.h"
#endif

#ifndef DIPORT_H
   #include "diport.h"
#endif

#ifndef INCLUDED_TIME_H
#define INCLUDED_TIME_H
   #include <time.h>
#endif

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif


PVOID CreateBuffer(const DString &strFunc, DWORD dwSize)
throw (std::exception, ConditionException)
{
   PVOID pBuffer = (PVOID) new char[dwSize];

   if (!pBuffer)
      THROWFROMBASE( DICORE_CONDITION, strFunc, BASE_ALLOC_FAIL )

   return (pBuffer);
}


PCHAR DeleteBuffer(PCHAR pch)
{
   if (pch)
   {
      delete [] pch;
      pch = (PCHAR) NULL;
   }

   return (pch);
}


// put here instead of diport1.cpp since applies to all other platforms
#ifndef _WIN32
void GetSystemTime(SYSTEMTIME *pst)
{
   struct tm   *ptm;
   time_t      t;

   time(&t);
   ptm = localtime(&t);
   pst->wYear = ptm->tm_year + 1900;
   pst->wMonth = ptm->tm_mon + 1;
   pst->wDayOfWeek = ptm->tm_mday;
   pst->wDay = ptm->tm_mday;
   pst->wHour = ptm->tm_hour;
   pst->wMinute = ptm->tm_min;
   pst->wSecond = ptm->tm_sec;
   pst->wMilliseconds = 0;
}
#endif


DWORD DSTGetCurrentProcessId(VOID)
{
   return GetCurrentID(FALSE);
}


DWORD DSTGetCurrentThreadId(VOID)
{
   return GetCurrentID(TRUE);
}


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
// $Log:   Y:/VCS/iFastAWD/dicore/diport.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:38   kovacsro
// Initial revision.
// 
//    Rev 1.6   May 04 2000 16:34:52   DT14177
// removed TGenericMap and all dependent code
// 
//    Rev 1.5   26 Feb 1999 15:05:52   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.4   24 Feb 1999 10:44:06   DT14177
// sync up with tracer
// 
//    Rev 1.3   18 Feb 1999 10:38:06   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:02:50   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.1   Jan 28 1999 13:43:30   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:10   DMUM
//
//
