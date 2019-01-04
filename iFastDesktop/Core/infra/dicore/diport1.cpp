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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : heap.cpp
// ^AUTHOR : Larry Parnes
// ^DATE   : 06/19/98
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef DIPORT2_H
#include "diport2.h"
#endif

#ifndef INCLUDED_DSTRINGA
#define INCLUDED_DSTRINGA
   #include "dstringa.hpp"
#endif

#ifndef INCLUDED_PROCESS_H
#define INCLUDED_PROCESS_H
   #include <process.h>
#endif


DWORD CreateAFile (PCCH pcchFile, DWORD dwDesiredAccess, DWORD dwShareMode,
               DWORD dwCreationDistribution, DWORD dwFlagsAndAttributes,
               DWORD dwSize, HANDLE *pHandle, DWORD *pdwAction)
{
   DWORD dwResult = 0;

// pdwAction and dwSize ignored on this platform
   if ((*pHandle = CreateFile(pcchFile, dwDesiredAccess, dwShareMode, NULL,
                        dwCreationDistribution, dwFlagsAndAttributes,
                        NULL)) == INVALID_HANDLE_VALUE)
      *pHandle = (HANDLE) NULL;

   dwResult = GetLastError(); // will indicate stuff like file already existed even if handle returned

   return (dwResult);
}


DWORD WriteToFile (HANDLE handle, PVOID pvData, DWORD dwBytesToWrite, DWORD *pdwBytesWritten)
{
   DWORD dwResult = 0;

   if (!WriteFile(handle, pvData, dwBytesToWrite, pdwBytesWritten, NULL))
      dwResult = GetLastError();

   return (dwResult);
}


DWORD ReadFromFile (HANDLE handle, PVOID pvData, DWORD dwMaxBytesToRead, DWORD *pdwBytesRead)
{
   DWORD dwResult = 0;

   if (!ReadFile(handle, pvData, dwMaxBytesToRead, pdwBytesRead, NULL))
      dwResult = GetLastError();

   return (dwResult);
}


typedef unsigned (__stdcall *PBEGINTHREAD_START_ROUTINE) (PVOID);


DWORD CreateAnotherThread (PVOID pfn, PVOID pvArgList, HANDLE *pHandle, DWORD *pdwID)
{
   DWORD dw = 0, dwTemp;

   if (pHandle)
      *pHandle = (HANDLE) dw;

   if ((dw = _beginthreadex(NULL, 0, (PBEGINTHREAD_START_ROUTINE) pfn, pvArgList, 0,
                      (unsigned *) (pdwID ? pdwID : &dwTemp))) == 0)
      dw = errno;
   else if (pHandle)
      *pHandle = (HANDLE) dw;

   return (dw);
}


DWORD EndAnotherThread (DWORD dwRetval, bool bClose, HANDLE handle)
{
   DWORD dw = 0;

   _endthreadex(dwRetval);

   if (bClose && handle)
      dw = CloseAHandle(handle);

   return (dw);
}


DWORD CloseAHandle (HANDLE &handle)
{
   DWORD dwResult = 0;

   if (handle)
   {
      if (!CloseHandle(handle))
         dwResult = GetLastError();

      handle = (HANDLE) NULL;
   }

   return (dwResult);
}


DWORD LoadALibrary (PCHAR pchName, DWORD ulBytes, const DStringA &_strModule, HINSTANCE *phInstance)
{
   DWORD dw = 0;

   if ((*phInstance = LoadLibrary(_strModule.c_str())) == (HINSTANCE) NULL)
      dw = GetLastError();

   return (dw);
}


DWORD FindAFunction (HINSTANCE hInstance, const DStringA &strFunc, FARPROC *pfarproc)
{
   DWORD dw = 0;

   if ((*pfarproc = GetProcAddress(hInstance, strFunc.c_str())) == (FARPROC) NULL)
      dw = GetLastError();

   return (dw);
}


DWORD FreeALibrary (HINSTANCE hInstance)
{
   DWORD dw = 0;

   if (!FreeLibrary(hInstance))
      dw = GetLastError();

   return (dw);
}


DWORD CreateEventSemaphore (PCCH pcchName, HANDLE *phandle, BOOL bInitialState)
{
   DWORD dw = 0;

   if ((*phandle = CreateEvent(NULL, TRUE, bInitialState, pcchName)) == (HANDLE) NULL)
      dw = GetLastError();

   return (dw);
}


DWORD OpenEventSemaphore (PCCH pcchName, HANDLE *phandle, BOOL bInitialState)
{
   DWORD dw = 0;

   if ((*phandle = OpenEvent(EVENT_ALL_ACCESS, bInitialState, pcchName)) == (HANDLE) NULL)
      dw = GetLastError();

   return (dw);
}


DWORD CloseEventSemaphore (HANDLE &handle)
{
   return (CloseAHandle(handle));
}


DWORD PostEventSemaphore (HANDLE handle)
{
   DWORD dwResult = 0;

   if (!SetEvent(handle))
      dwResult = GetLastError();

   return (dwResult);
}


static DWORD WaitForObject (HANDLE handle, DWORD dwTimeout)
{
   DWORD dwResult = WaitForSingleObject(handle, dwTimeout);

   if (dwResult == WAIT_OBJECT_0 || dwResult == WAIT_ABANDONED)
      dwResult = 0;

   return (dwResult);
}


DWORD WaitForEventSemaphore (HANDLE handle, DWORD dwTimeout)
{
   DWORD dwResult = WaitForObject(handle, dwTimeout);

   if (dwResult != 0 && dwResult == WAIT_FAILED)
      dwResult = GetLastError();

   return (dwResult);
}


DWORD QueryEventSemaphore (HANDLE handle, DWORD &dwCount)
{
   DWORD dwResult = WaitForObject(handle, 0);

   if (dwResult == 0)
      PostEventSemaphore(handle);   // We just got ownership of the semaphore.  We should release it.
   else if (WAIT_TIMEOUT == dwResult)
   {
      dwResult = 0;        // also consider this wait successful
      dwCount = 1;         // at least one other thread is waiting on the semaphore
   }
   else if (WAIT_FAILED == dwResult)
      dwResult = GetLastError();
   else
      dwResult = 0;

   return (dwResult);
}


DWORD ResetEventSemaphore (HANDLE handle, DWORD &dwCount)
{
   DWORD dwResult = 0;

   if (!ResetEvent(handle))
      dwResult = GetLastError();

   return (dwResult);
}


DWORD CreateMutexSemaphore (PCCH pcchName, HANDLE *phandle, BOOL bInitialState)
{
   DWORD dwResult = 0;

   if ((*phandle = CreateMutex(NULL, bInitialState, pcchName)) == (HANDLE) NULL)
      dwResult = GetLastError();

   return (dwResult);
}


DWORD OpenMutexSemaphore (PCCH pcchName, HANDLE *phandle)
{
   DWORD dwResult = 0;

   if ((*phandle = OpenMutex(MUTEX_ALL_ACCESS, TRUE, pcchName)) == (HANDLE) NULL)
      dwResult = GetLastError();

   return (dwResult);
}


DWORD CloseMutexSemaphore (HANDLE &handle)
{
   return (CloseAHandle(handle));
}


DWORD PostMutexSemaphore (HANDLE handle)
{
   DWORD dwResult = 0;

   if (!ReleaseMutex(handle))
      dwResult = GetLastError();

   return (dwResult);
}


DWORD WaitForMutexSemaphore (HANDLE handle, DWORD dwTimeout)
{
   return (WaitForEventSemaphore(handle, dwTimeout));    // these 2 functions same on this platform
}


DWORD QueryMutexSemaphore (HANDLE handle, PID *pPID, TID *pTID, DWORD &dwCount)
{
   if (pPID)
      *pPID = DSTGetCurrentProcessId();

   if (pTID)
      *pTID = DSTGetCurrentThreadId();

   return (QueryEventSemaphore(handle, dwCount));     // these 2 functions same on this platform
}


DWORD SetNamedPipeState (HANDLE handle, DWORD dwState)
{
   DWORD dwResult = 0;

   if (!SetNamedPipeHandleState(handle, &dwState, NULL, NULL))
      dwResult = GetLastError();

   return (dwResult);
}


DWORD CreateANamedPipe (PCCH pcchName, HANDLE *pHandle, DWORD dwOpenMode, DWORD dwPipeMode,
                  DWORD dwInstances, DWORD dwOutSize, DWORD dwInSize, DWORD dwTimeout)
{
   DWORD dwResult = 0;

   if ((*pHandle = CreateNamedPipe(pcchName, dwOpenMode, dwPipeMode, dwInstances, dwOutSize,
                            dwInSize, dwTimeout, NULL)) == INVALID_HANDLE_VALUE)
   {
      *pHandle = (HANDLE) NULL;
      dwResult = GetLastError();
   }

   return (dwResult);
}


DWORD ConnectANamedPipe (HANDLE handle)
{
   DWORD dwResult = 0;

   if (!ConnectNamedPipe(handle, NULL))
      dwResult = GetLastError();

   return (dwResult);
}


DWORD DisconnectANamedPipe (HANDLE handle)
{
   DWORD dwResult = 0;

   if (!DisconnectNamedPipe(handle))
      dwResult = GetLastError();

   return (dwResult);
}


DWORD CreateAProcess (const DStringA& strExeLine, PROCESS_INFORMATION *pprocessInfo,
                 PSTARTUPDATA psd)
{
   DWORD dwResult = 0;

   if (CreateProcess(NULL, ( char * )strExeLine.c_str(), NULL, NULL, FALSE,
                      0, NULL, NULL, psd, pprocessInfo))
   {
      CloseAHandle(pprocessInfo->hThread);
      CloseAHandle(pprocessInfo->hProcess);
   }
   else
      dwResult = GetLastError();

   return (dwResult);
}


DWORD GetCurrentID (bool bThread)
{
    return (bThread ? GetCurrentThreadId() : GetCurrentProcessId());
}


int InitSocket (VOID)
{
    WORD wVersionRequested = MAKEWORD( 2, 0 );
    WSADATA wsaData;
    return (WSAStartup(wVersionRequested, &wsaData));
}


int CloseSocket (int nSocket)
{
    return (closesocket(nSocket));
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
// $Log:   Y:/VCS/iFastAWD/dicore/diport1.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:40   kovacsro
// Initial revision.
// 
//    Rev 1.3   18 Feb 1999 10:38:42   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:03:32   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.1   Jan 28 1999 13:44:14   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:52:30   DMUM
//
//
