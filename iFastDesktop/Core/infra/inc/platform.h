#ifndef PLATFORM_H
#define PLATFORM_H

#  pragma message( "including "__FILE__ )

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

// DESCRIPTION : This file will exist for each platform and contain
//               platform specific typedefs and includes.  This is
//               the Windows specific one.

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#include <windows.h>

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
// $Log:   Y:/VCS/iFastAWD/inc/platform.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:28   kovacsro
//Initial revision.
// 
//    Rev 1.4   30 Nov 2000 11:23:06   dt14177
// cleanup
// 
//    Rev 1.3   18 Feb 1999 10:40:28   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:07:36   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 14 1998 15:11:40   DMUM
//
//

#endif // platform_h
