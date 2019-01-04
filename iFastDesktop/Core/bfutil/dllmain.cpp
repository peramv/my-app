#pragma warning(disable: 4001)      /* Single-line comment */

#include "stdafx.h"
#include "BFExecutionContext.hpp"
#include <objbase.h>
#include <bf/log/log.hpp>
#include <bfutil/verify.hpp>
#include "seh_exception.hpp"

#include <exechist.hpp>

#define VERIFIER_VERSION I_("Dev")

namespace CND
{
   extern const long BFUTIL_CND_VERSION;
}

_se_translator_function s_pGlobalSeTranslatorFunc = NULL;
int oleInitialized = 0;
void setGlobalSeTranslator( _se_translator_function pFunc )
{
   s_pGlobalSeTranslatorFunc = pFunc;
}

extern BFUTIL_LINKAGE void setOleInitialized( int _oleInitialized)
{
	oleInitialized = _oleInitialized;
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
         ExecutionHistory::init();
         bfutil::getLibraryVerifier().registerLibrary( bfutil::LibraryVerifier::Category::core, I_( "BFUTIL" ), VERIFIER_VERSION );
         bfutil::getLibraryVerifier().addConditionFile( bfutil::LibraryVerifier::Category::core, I_( "BFUTIL" ), I_( "bfutil" ), CND::BFUTIL_CND_VERSION );
         bfutil::getLibraryVerifier().addConditionFile( bfutil::LibraryVerifier::Category::core, I_( "BFUTIL" ), I_( "dicore" ), 0 );
         break;

         //  the attached process creates a new thread.
      case DLL_THREAD_ATTACH:
         ExecutionHistory::init();
         _set_se_translator( s_pGlobalSeTranslatorFunc );
         CoInitializeEx( NULL, bfutil::isServerContext() ? COINIT_MULTITHREADED : COINIT_APARTMENTTHREADED );
         bf::log::Log::attachThreads();
         break;

         //  the thread of the attached process terminates.
      case DLL_THREAD_DETACH:
         bf::log::Log::detachThreads();
         BFExecutionContext::detach();
         ExecutionHistory::finalize();
         CoUninitialize();
         break;

         //  the DLL is detaching from a process due to
         //  process termination or a call to FreeLibrary
      case DLL_PROCESS_DETACH:
         ExecutionHistory::finalize();
         break;

      default:
         break;
   }

   return(TRUE);
}


