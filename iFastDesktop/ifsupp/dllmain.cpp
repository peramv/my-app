#pragma warning(disable: 4001)      /* Single-line comment */

#include "stdafx.h"
#include <afxdllx.h>
//#include <map>
//#include <DString.hpp>
//#include <typeinfo>
#include "ControlTextRewriter.h"
#include "UserActivity.h"
#include "KeyTrapper.h"

//#include <bf/log/log.hpp>

#define VERIFIER_VERSION I_("Dev")

namespace CND
{
   extern const long GUI_CND_VERSION;
}
HINSTANCE g_hInstDll = 0;

static AFX_EXTENSION_MODULE ExtdllDLL = { NULL, NULL };





BOOL WINAPI DllMain( HINSTANCE hInstDll,    // DLL module handle
                     DWORD fdwReason,       // reason called
                     LPVOID lpvReserved )   // reserved
{
   switch( fdwReason )
   {
      //  the DLL is attaching to a process due to process
      //  initialization or a call to LoadLibrary.
      case DLL_PROCESS_ATTACH:
         g_hInstDll = hInstDll;
         // Extension DLL one-time initialization
         if (!AfxInitExtensionModule(ExtdllDLL, hInstDll))
            return( FALSE );
         new CDynLinkLibrary(ExtdllDLL);

         RegisterUserActivityHooks( g_hInstDll );
         RegisterKeyTrapperHooks( g_hInstDll );
         RegisterControlTextRewriterHooks(g_hInstDll);
                            
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


