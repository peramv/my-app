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

#define DICORE_DLL

#include <windows.h>
#include <commonport.h>
#include <ConditionManager.hpp>

#define VERIFIER_VERSION I_("Dev");

// Not included in any header.
// This function is used for thread cleanup.
void deleteFrames();    // Cleans up frames for current thread

BOOL WINAPI DllMain( HINSTANCE hinstDLL,    // DLL module handle
                     DWORD fdwReason,       // reason called
                     LPVOID lpvReserved )   // reserved
{
   switch( fdwReason )
   {
      //  the DLL is attaching to a process due to process
      //  initialization or a call to LoadLibrary.
      case DLL_PROCESS_ATTACH:
//       ExecutionHistory::init();
         break;

         //  the attached process creates a new thread.
      case DLL_THREAD_ATTACH:
//         ExecutionHistory::init();
         break;

         //  the thread of the attached process terminates.
      case DLL_THREAD_DETACH:
//         ExecutionHistory::finalize();
         deleteFrames();
         break;

         //  the DLL is detaching from a process due to
         //  process termination or a call to FreeLibrary
      case DLL_PROCESS_DETACH:
//         ExecutionHistory::finalize();
         break;

      default:
         break;
   }

   return(TRUE);
}

//************************************************************************
//              Revision Control Entries
//**********************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/win32/dllmain.cpp-arc  $
//
//   Rev 1.4   May 09 2007 10:26:12   purdyech
//Introduce EXECHIST Logging for AWD
//
//   Rev 1.3   Feb 18 2004 15:13:20   PURDYECH
//Added calls to ExecutionHistory::init() and ExecutionHistory::finalize() to to execution history tracking.
//
//   Rev 1.2   Jan 13 2004 09:44:20   PURDYECH
//Add version checking code
// 
//    Rev 1.1   Oct 09 2002 17:42:22   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Sep 07 2002 12:17:16   PURDYECH
// Initial revision.
// 
//    Rev 1.4   May 18 2001 14:30:22   dt24433
// Changes for ConditionManager thread management changes.
// 
// 

