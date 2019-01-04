#pragma warning(disable: 4001)      /* Single-line comment */

#include "stdafx.h"
#include <bfutil/verify.hpp>

#define VERIFIER_VERSION I_("Dev")

namespace CND
{
   extern const long BFDATA_CND_VERSION;
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL,    // DLL module handle
                     DWORD fdwReason,       // reason called
                     LPVOID lpvReserved )   // reserved
{
   switch( fdwReason )
   {
      //  the DLL is attaching to a process due to process
      //  initialization or a call to LoadLibrary.
      case DLL_PROCESS_ATTACH:
         bfutil::getLibraryVerifier().registerLibrary( bfutil::LibraryVerifier::Category::core, I_( "BFDATA" ), VERIFIER_VERSION );
         bfutil::getLibraryVerifier().addConditionFile( bfutil::LibraryVerifier::Category::core, I_( "BFDATA" ), I_( "bfdata" ), CND::BFDATA_CND_VERSION );
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
         break;

      default:
         break;
   }

   return(TRUE);
}


