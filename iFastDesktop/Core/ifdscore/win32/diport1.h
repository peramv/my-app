#ifndef DIPORT1_H
#define DIPORT1_H


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

#if 0
#define FILE_READ_ACCESS       GENERIC_READ
#define FILE_WRITE_ACCESS      GENERIC_WRITE
#define FILE_READWRITE_ACCESS  (GENERIC_READ | GENERIC_WRITE)
#define FILE_READ_SHARE        FILE_SHARE_READ
#define FILE_WRITE_SHARE       FILE_SHARE_WRITE
#define FILE_READWRITE_SHARE   (FILE_SHARE_READ | FILE_SHARE_WRITE)
#define FILE_NO_SHARE          0
#define FILE_OPEN_EXISTING     OPEN_EXISTING
#define FILE_DEFAULT_ATTRIBUTE 0
#endif
#define NAMED_PIPE_WAIT               PIPE_WAIT
#define NAMED_PIPE_READMODE_MESSAGE   PIPE_READMODE_MESSAGE
#define NAMED_PIPE_NOINHERIT          0
#define NAMED_PIPE_ACCESS_DUPLEX      PIPE_ACCESS_DUPLEX
#define NAMED_PIPE_WAIT               PIPE_WAIT
#define NAMED_PIPE_TYPE_MESSAGE       PIPE_TYPE_MESSAGE

typedef STARTUPINFO      STARTUPDATA;
typedef STARTUPDATA      *PSTARTUPDATA;

/*******************************************************************************
//              Revision Control Entries
//******************************************************************************/
//
// $Log:   Y:/VCS/BF Core/ifdscore/win32/diport1.h-arc  $
//
//   Rev 1.1   Oct 22 2004 09:04:48   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.0   Jul 05 2002 10:15:22   SMITHDAV
//Initial revision.
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
