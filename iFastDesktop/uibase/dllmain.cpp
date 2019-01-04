#pragma warning(disable: 4001)      /* Single-line comment */

#include "stdafx.h"
#include <afxdllx.h>

#include <bf/log/log.hpp>

#define VERIFIER_VERSION I_("Dev")

namespace CND
{
   extern const long GUI_CND_VERSION;
}
HINSTANCE g_hinstDLL = 0;
static AFX_EXTENSION_MODULE ExtdllDLL = { NULL, NULL };


BOOL WINAPI DllMain( HINSTANCE hinstDLL,    // DLL module handle
                     DWORD fdwReason,       // reason called
                     LPVOID lpvReserved )   // reserved
{
   switch( fdwReason )
   {
      //  the DLL is attaching to a process due to process
      //  initialization or a call to LoadLibrary.
      case DLL_PROCESS_ATTACH:
         g_hinstDLL = hinstDLL;
         // Extension DLL one-time initialization
         if (!AfxInitExtensionModule(ExtdllDLL, hinstDLL))
            return( FALSE );
         new CDynLinkLibrary(ExtdllDLL);

         break;

         //  the attached process creates a new thread.
      case DLL_THREAD_ATTACH:
         break;

         //  the thread of the attached process terminates.
      case DLL_THREAD_DETACH:
         break;

         //  the DLL is detaching from a process due to
         //  process termination or a call to FreeLibrary
      case DLL_PROCESS_DETACH:
         AfxTermExtensionModule(ExtdllDLL);
         break;

      default:
         break;
   }

   return(TRUE);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/uibase/dllmain.cpp-arc  $
// 
//    Rev 1.11   Dec 05 2011 09:01:24   purdyech
// ControlTextRewriter Logic
//
//    Rev 1.10   Sep 20 2011 16:37:24   dchatcha
// Usability Improvement on iFAST/Desktop, redirect 'keyfile' to 'temp' directory.
//
//    Rev 1.9   Sep 19 2011 14:37:34   dchatcha
// Usability Improvement on iFAST/Desktop, allow using keyborad hook only for specific build(via complie guard)
//

