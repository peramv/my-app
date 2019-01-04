//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//******************************************************************************
//
// ^FILE   : dllmain.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 27, 2005
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************
#pragma warning(disable: 4001)      /* Single-line comment */

#include "stdafx.h"
#include "AwdServiceManager.hpp"
#include "AWDLog.hpp"

BOOL WINAPI DllMain( HINSTANCE hinstDLL,    // DLL module handle
                     DWORD fdwReason,       // reason called
                     LPVOID lpvReserved )   // reserved
{
   switch( fdwReason )
   {
      //  the DLL is attaching to a process due to process
      //  initialization or a call to LoadLibrary.
      case DLL_PROCESS_ATTACH:
         AwdServiceManager::getInstance(); 
         AWDLog::getInstance();
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
         AwdServiceManager::killInstance();
         AWDLog::killInstance();         
         break;

      default:
         break;
   }

   return(TRUE);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/dllmain.cpp-arc  $
// 
//    Rev 1.1   Nov 15 2005 15:35:38   yingbaol
// PET1332,FN09: clean up AWDLOG
// 
//    Rev 1.0   Oct 31 2005 14:57:16   yingbaol
// Initial revision.
 * 
 *

 */

