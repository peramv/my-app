//********************************************************************
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
//********************************************************************
//
// ^FILE   : dllmain.cpp
// ^AUTHOR : Tom Hogan
// ^DATE   : 09-10-99
//
//********************************************************************

#pragma warning(disable: 4001)      /* Single-line comment */

#ifndef INCLUDED_WINDOWS_H
#define INCLUDED_WINDOWS_H
   #include <windows.h>
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "ConditionManager.hpp"
#endif

#include "configmanager.hpp"
#include "binfileheader.hpp"
#include "RegistryKey.hpp"
#include "datapath.h"

typedef const DString& (__cdecl *PFNINIPATH)( const DString& );

static void SetDataPaths() {
   I_CHAR szModName[256] = I_("ifdscore.dll");
#ifdef _DEBUG
   i_strcpy( szModName, I_("ifdscore_d.dll") );
#endif
   HMODULE hModule;
   PFNINIPATH pfn = NULL;
   hModule = GetModuleHandleW((LPCWSTR)szModName);
   if( NULL != hModule ) {
      pfn = (PFNINIPATH)GetProcAddress(hModule, "GetGlobalIniPath");
      if( NULL != pfn ) {
         const DString null;
         const DString& path = pfn(null);
         ConditionManager::getInstance()->setPath( path );
         SetGlobalIniPath( path );
      }
      pfn = (PFNINIPATH)GetProcAddress(hModule, "GetGlobalDataPath");
      if( NULL != pfn ) {
         const DString null;
         const DString& path = pfn(null);
         SetGlobalDataPath( path );
         SetGlobalRepositorySourcePath( path + I_("\\databroker.bin") );
      }
   }
}


// Not included in any header.
// This function is used for thread cleanup.
void deleteFrames();          // Cleans up frames for current thread
void initializeFramesTls();   // Initialized thread local storage of frames
// used for process cleanup
void freeLocaleInstanceMap();
void freeFramesTlsIndex();

BOOL WINAPI DllMain( HINSTANCE hinstDLL,    // DLL module handle
                     DWORD fdwReason,       // reason called
                     LPVOID lpvReserved )   // reserved
{
  switch ( fdwReason )
  {
    //  the DLL is attaching to a process due to process
    //  initialization or a call to LoadLibrary.
    case DLL_PROCESS_ATTACH:
       initializeFramesTls();

       // do we need to load the registry overrides?
      // module name to search for...
      RegistryKey::LoadOverrideFunctions();
      SetDataPaths();

       break;

    //  the attached process creates a new thread.
    case DLL_THREAD_ATTACH:
       break;

    //  the thread of the attached process terminates.
    case DLL_THREAD_DETACH:
       deleteFrames();
       break;

    //  the DLL is detaching from a process due to
    //  process termination or a call to FreeLibrary
    case DLL_PROCESS_DETACH:
       freeLocaleInstanceMap();
       freeFramesTlsIndex();
       break;

    default:
       break;
  }

  return TRUE;
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
// $Log:   Y:/VCS/iFastAWD/dicore/dllmain.cpp-arc  $
// 
//    Rev 1.1   Nov 02 2011 04:43:02   purdyech
// Registry Cleanup
//
//    Rev 1.5   Aug 13 2001 13:43:08   DT21858
// Changed TLS in condition manager from static declaration to dynamic TLS
// utilizing TlsAlloc, TlsFree, TlsGetValue, and TlsSetValue.
//
//

