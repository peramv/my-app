#ifndef DIPORT1_H
#define DIPORT1_H

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

// DESCRIPTION : to declare prototypes for operating system-
//               specific functions for Win32

#ifndef DIPORT_H
   #include "diport.h"
#endif

#define FILE_READWRITE_ACCESS  (GENERIC_READ | GENERIC_WRITE)
#define FILE_READ_SHARE        FILE_SHARE_READ
#define FILE_WRITE_SHARE       FILE_SHARE_WRITE
#define FILE_READWRITE_SHARE   (FILE_SHARE_READ | FILE_SHARE_WRITE)
#define FILE_NO_SHARE          0
#define FILE_OPEN_EXISTING     OPEN_EXISTING
#define FILE_DEFAULT_ATTRIBUTE 0

#define NAMED_PIPE_WAIT               PIPE_WAIT
#define NAMED_PIPE_READMODE_MESSAGE   PIPE_READMODE_MESSAGE
#define NAMED_PIPE_NOINHERIT          0
#define NAMED_PIPE_ACCESS_DUPLEX      PIPE_ACCESS_DUPLEX
#define NAMED_PIPE_WAIT               PIPE_WAIT
#define NAMED_PIPE_TYPE_MESSAGE       PIPE_TYPE_MESSAGE

typedef STARTUPINFO      STARTUPDATA;
typedef STARTUPDATA      *PSTARTUPDATA;

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
// $Log:   Y:/VCS/iFastAWD/inc/diport1.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:14   kovacsro
//Initial revision.
// 
//    Rev 1.5   21 Mar 2002 14:49:08   dt14177
// removed FILE ACCESS macros that
// conflicted with the definitions in
// Microsoft's WinIoCtl.H file.
// 
//    Rev 1.4   30 Nov 2000 10:38:56   dt14177
// cleanup
// 
//    Rev 1.3   18 Feb 1999 10:40:26   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:07:34   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 14 1998 15:10:50   DMUM
// Change for DICORE
//

#endif   // DIPORT1_H
