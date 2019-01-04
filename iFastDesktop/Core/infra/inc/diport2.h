#ifndef DIPORT2_H
#define DIPORT2_H

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

#ifndef DIPORT1_H
   #include "diport1.h"
#endif

#ifndef _WIN32

// the following functions will be redefined on non Win32 platforms
DWORD Beep(DWORD dwFreq, DWORD dwDuration);
VOID Sleep(DWORD dwMilliseconds);
DWORD GetLastError(VOID);
void GetSystemTime(SYSTEMTIME *pst);

typedef struct _processinfo
{
    HANDLE  hProcess;
    HANDLE  hThread;
    DWORD   dwProcessId;
    DWORD   dwThreadId;
} PROCESS_INFORMATION;

#endif

// The following multipurpose functions can be called for many of the
// same things on at least Win32 and OS2

EXPORTWIN DWORD CreateAFile(
                PCCH pcchFile,
                DWORD dwDesiredAccess,        // access (read-write) mode
                DWORD dwShareMode,            // share mode
                DWORD dwCreationDistribution, // how to create
                DWORD dwFlagsAndAttributes,   // file attributes
                DWORD dwSize,                 // size of file
                HANDLE *pHandle,              // handle to file if successful
                DWORD *pdwAction              // action returned if successful
                );

EXPORTWIN DWORD WriteToFile(
                HANDLE handle,         // handle of file to write to
                PVOID pvData,          // data to write
                DWORD dwBytesToWrite,  // # of bytes to write
                DWORD *pdwBytesWritten // pointer to # of bytes actually written
                );

EXPORTWIN DWORD ReadFromFile(
                HANDLE handle,          // handle of file to read from
                PVOID pvData,           // data buffer to read into
                DWORD dwMaxBytesToRead, // max # of bytes to read
                DWORD *pdwBytesRead     // pointer to # of bytes actually read
                );

EXPORTWIN DWORD CloseAHandle(HANDLE &handle);

EXPORTWIN DWORD LoadALibrary(PCHAR pchName,
                             DWORD ulBytes,
                             const DStringA &_strModule,
                             HINSTANCE *phInstance);

EXPORTWIN DWORD FindAFunction(HINSTANCE hInstance,
                              const DStringA &strFunc,
                              FARPROC *pfarproc);
EXPORTWIN DWORD FreeALibrary(HINSTANCE hInstance);

EXPORTWIN DWORD CreateEventSemaphore(PCCH pcchName,
                                     HANDLE *phandle,
                                     BOOL bInitialState);

EXPORTWIN DWORD OpenEventSemaphore(PCCH pcchName,
                                   HANDLE *phandle,
                                   BOOL bInitialState);

EXPORTWIN DWORD CloseEventSemaphore(HANDLE &handle);

EXPORTWIN DWORD PostEventSemaphore(HANDLE handle);

EXPORTWIN DWORD WaitForEventSemaphore(HANDLE handle, DWORD dwTimeout);

EXPORTWIN DWORD QueryEventSemaphore(HANDLE handle, DWORD &dwCount);

EXPORTWIN DWORD ResetEventSemaphore(HANDLE handle, DWORD &dwCount);

EXPORTWIN DWORD CreateMutexSemaphore(PCCH pcchName,
                                     HANDLE *phandle,
                                     BOOL bInitialState);

EXPORTWIN DWORD OpenMutexSemaphore(PCCH pcchName, HANDLE *phandle);

EXPORTWIN DWORD CloseMutexSemaphore(HANDLE &handle);

EXPORTWIN DWORD PostMutexSemaphore(HANDLE handle);

EXPORTWIN DWORD WaitForMutexSemaphore(HANDLE handle, DWORD dwTimeout);

EXPORTWIN DWORD QueryMutexSemaphore(HANDLE handle,
                                    PID *pPID,
                                    TID *pTID,
                                    DWORD &dwCount);

EXPORTWIN DWORD SetNamedPipeState(HANDLE handle, DWORD dwState);

EXPORTWIN DWORD CreateANamedPipe(PCCH pcchName,
                                 HANDLE *pHandle,
                                 DWORD dwOpenMode,
                                 DWORD dwPipeMode,
                                 DWORD dwInstances,
                                 DWORD dwOutSize,
                                 DWORD dwInSize,
                                 DWORD dwTimeout);

EXPORTWIN DWORD ConnectANamedPipe(HANDLE handle);

EXPORTWIN DWORD DisconnectANamedPipe(HANDLE handle);

EXPORTWIN DWORD CreateAProcess(const DStringA& strExeLine,
                               PROCESS_INFORMATION *pprocessInfo,
                               PSTARTUPDATA psd);

EXPORTWIN int InitSocket(VOID);

EXPORTWIN int CloseSocket(int nSocket);

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
// $Log:   Y:/VCS/iFastAWD/inc/diport2.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:14   kovacsro
//Initial revision.
// 
//    Rev 1.4   23 Oct 2000 17:22:52   dt14177
// cleanup
// 
//    Rev 1.3   18 Feb 1999 10:39:44   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:06:20   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:41:48   DMUM
// Check in for DICORE
//

#endif   // DIPORT2_H
