static const char szAWDSERV_ModuleID[] = "***Ver $Header:   Y:/VCS/BF iFAST/awdsrv/KEInterface.cpp-arc   1.2   Nov 14 2005 11:04:58   yingbaol  $ ***";

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
// ^FILE   : KEInterface.cpp
// ^AUTHOR : Yingbao Li & Paul Ives
// ^DATE   : Oct. 23, 2005
//
// ^CLASS    : KEInterface
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <string>
#include "awdstrct.h"
#include "AwdServiceManager.hpp"
#include "BPResult.hpp"
#include "AwdLobData.hpp"
#include "logging.h"

/**
 * Typedefs
*/

#define APIEXPORT __declspec( dllexport ) __stdcall

extern "C"
{
   typedef BOOL (__stdcall *PFNAWDENTRYPOINT)( HWND           hwndCSD,
                                               ULONG          ulMsgId,
                                               CHAR          *pAwdObjKey,
                                               PAWDLOBARRAY   pAwdLobArray,
                                               CHAR          *pszIdentity,
                                               PVOID          pvImageWindow,
                                               CHAR          *pucHost,
                                               CHAR          *pucParm,
                                               CHAR          *pucCustom );

   typedef int (__stdcall *PFN_DO_ADD_COMMENTS)( HWND   hwnd,
                                                 ULONG  iRetMsg,
                                                 CHAR  *pszAWDObjKey,
                                                 CHAR  *pszJobName,
                                                 CHAR  *pszTaskName,
                                                 ULONG  cbBusVars,
                                                 PAWDLOBARRAY pLOBData,
                                                 CHAR  *pszHost,
                                                 CHAR  *pszParams,
                                                 const BOOL bUseSendMessage );
}

/**
 * DTM return codes
*/

#define DTM_OK    0
#define DTM_ERROR 1

#define  LOB_CANCEL            0
#define  LOB_FUN_COMPLETE      1
#define  LOB_UPDATE            2
#define  LOB_PASS              3
#define  LOB_FAIL              4
#define  FUN_COMPELTE_FORWARD  5
//extern  HMODULE hModule;

/**
 * Prototypes - StartExternalSystem, this is the function that DTM/KE will call for you...
*/
extern BOOL APIEXPORT StartExternalSystem( HWND           hwndCSD,
                                           ULONG          ulMsgId,
                                           CHAR          *pAwdObjKey,
                                           PAWDLOBARRAY   pAwdLobArray,
                                           CHAR          *pszIdentity,
                                           PVOID          pvImageWindow,
                                           CHAR          *pucHost,
                                           CHAR          *pucParm,
                                           CHAR          *pucCustom );



/**
 * includes, defs for custom function calling
*/
#include "keinterface.h"

#define ERROR_MESSAGE_BOX_TITLE     "Error: AWDSRV.DLL"
#define ERROR_MESSAGE_SIZE          256
#define FUNC_ARRAY_SIZE             2


//******************************************************************
BOOL (__stdcall *aCustomFunctions[FUNC_ARRAY_SIZE])( HWND,
                                                     ULONG,
                                                     CHAR*,
                                                     PAWDLOBARRAY,
                                                     CHAR*,
                                                     PVOID,
                                                     CHAR*,
                                                     CHAR*,
                                                     CHAR* ) =
{
   //fnSendLOBtoMappingLayer,
   mailingService,
   addComments,  
} ;


// These are the names of the functions (char*'s) and must have a corresponding
// entry in the aCustomFunctions array
const char *aCustomFuncNames[FUNC_ARRAY_SIZE] =
{
   //"fnSendLOBtoMappingLayer",
   "mailingService",
   "addComments"
};

/**
 *
 * FUNCTION:  StartExternalSystem
 *
 * PARAMETERS:
 *   None.
 *
 * ABSTRACT:
 *   Updates a LOB Array with the values contained in
 *   the tag buffer.
 *
 * RETURNS:
 *   Nothing.
 *
*/
BOOL APIEXPORT StartExternalSystem( HWND           hwndCSD,
                                    ULONG          ulMsgId,
                                    CHAR          *pAwdObjKey,
                                    PAWDLOBARRAY   pAwdLobArray,
                                    CHAR          *pszIdentity,
                                    PVOID          pvImageWindow,
                                    CHAR          *pucHost,
                                    CHAR          *pucParm,
                                    CHAR          *pucCustom )
{
   char szErrorMessage[ERROR_MESSAGE_SIZE];
   BOOL dtmRc = DTM_ERROR; // Return code
   BOOL blErrorCode = LOB_CANCEL; // message return code

   BOOL blFunctionFound = false;
   BOOL blReturnFlag = false;

   // Check name of custom procedure - pucCustom - to be invoked
   if ( pucCustom != NULL )
   {
      for ( int x=0; x < FUNC_ARRAY_SIZE; x++ )
      {
         // if the custom function matches a function name in the function
         // name array, then run the corresponding function from the function
         // array
         if ( (aCustomFuncNames[x] != NULL) &&
              (strcmp( pucCustom, aCustomFuncNames[x]) == 0) )
         {
            blFunctionFound = true;
            blReturnFlag = (*aCustomFunctions[x])(hwndCSD,
                                                  ulMsgId,
                                                  pAwdObjKey,
                                                  pAwdLobArray,
                                                  pszIdentity,
                                                  pvImageWindow,
                                                  pucHost,
                                                  pucParm,
                                                  0 );
            break;
         }

      }

      if ( blFunctionFound == false )
      {
         // unknown function has been called
         memset( szErrorMessage, '\0', ERROR_MESSAGE_SIZE);
         sprintf( szErrorMessage, "Unknown function, %s , called in AWDSERV.DLL", pucCustom);
         // MessageBox( hwndCSD, szErrorMessage, ERROR_MESSAGE_BOX_TITLE, MB_OK);
      }

      if ( blReturnFlag == false )
      {
         // custom funtion exited with value == false
         memset( szErrorMessage, '\0', ERROR_MESSAGE_SIZE);
         sprintf( szErrorMessage, "Function, %s , called in AWDSERV has returned false.", pucCustom);
         // MessageBox( hwndCSD, szErrorMessage, ERROR_MESSAGE_BOX_TITLE, MB_OK);
      }
   }

   /**
    * Process AWD/DTM window message return
   */
   if ( blReturnFlag == TRUE )
   {
      /**
       * If the all ok tell AWD the function completed
      */
      blErrorCode = LOB_FUN_COMPLETE;
      dtmRc = DTM_OK;
   }
   else
   {
      /**
       * If we had any problems then tell AWD the
       * function did not complete
      */
      blErrorCode = LOB_CANCEL;
      dtmRc = DTM_ERROR;
   }

   /**
    * Inform AWD we have finished
   */
   PostMessage( hwndCSD,
                ulMsgId,
                (WPARAM) blErrorCode,
                (LPARAM) 0 );

   /**
    * Return code to calling function (DTM)
   */
   return( dtmRc );
}

//******************************************************************************
BOOL __stdcall mailingService( HWND          hwndCSD,
                          ULONG         ulMsgId,
                          CHAR         *pAwdObjKey,
                          PAWDLOBARRAY  pAwdLobArray,
                          CHAR         *pszIdentity,
                          PVOID         pvImageWindow,
                          CHAR         *pucHost,
                          CHAR         *pucParm,
                          CHAR         *pucCustom )
{
   BOOL bRC =  FALSE; 

   BPResult result;
   AwdLobData lob( pAwdLobArray );
   LOGGING("\n\n   service  start.....\n");
   LOGGINGLOBDATA( lob );
   bool bService = AwdServiceManager::getInstance()->requestService(lob,result );
   if( bService )
   {
      LOGGINGLOBDATA( lob );  
	  std::string comments = "S|";
	  bRC =  TRUE;
      if( result.getHighestSeverity() < 4 )
      {         
		 comments += "update BP server successful!";
      }
      if( result.getHighestSeverity() != 0 )
      {        
         comments += result.getHighestSeverityMessage();
      }
	  LOGGING("add comments-------");
	  LOGGING(comments+"\n");
	  char* cPtr;
	  cPtr = const_cast<char*>( comments.c_str() );
	  cPtr[comments.length() ] = '\0';
	  BOOL bT =addComments( hwndCSD,
				ulMsgId,
				pAwdObjKey,
				pAwdLobArray,
				pszIdentity,
				pvImageWindow,
				pucHost,
				cPtr,  
				pucCustom );

   }
   LOGGING("    service complete .....");
   return( bRC );
}
//*****************************************************************************
BOOL __stdcall addComments( HWND          hwndCSD,
                            ULONG         ulMsgId,
                            CHAR         *pAwdObjKey,
                            PAWDLOBARRAY  pAwdLobArray,
                            CHAR         *pszIdentity,
                            PVOID         pvImageWindow,
                            CHAR         *pucHost,
                            CHAR         *pucParm,
                            CHAR         *pucCustom )
{
   int dtmRc = DTM_OK;

   PFN_DO_ADD_COMMENTS pfnProcAddress = (PFN_DO_ADD_COMMENTS ) AwdServiceManager::getInstance()->getFunctionAddress( "DoAddComments" );
 
   if ( pfnProcAddress != NULL )
   {
      if ( (*pfnProcAddress) != NULL )
      {
         dtmRc = (*pfnProcAddress)( hwndCSD, 
                                    ulMsgId, 
                                    pAwdObjKey,
                                    NULL, 
                                    NULL, 
                                    0, 
                                    pAwdLobArray, 
                                    pucHost, 
                                    pucParm, 
                                    FALSE /* FALSE = Don't Post Message */);
      }
   }
   else
   {
      MessageBox( HWND_DESKTOP, "failed to call DTMAWDX.DLL function=DoAddComments", ERROR_MESSAGE_BOX_TITLE, MB_OK );
   }

   return( dtmRc == DTM_OK );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/KEInterface.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2005 11:04:58   yingbaol
// PET1332,FN09:add more log information
// 
//    Rev 1.1   Nov 08 2005 14:17:50   yingbaol
// PET1332,FN09: Remove DString and Infra structure
// 
//    Rev 1.0   Oct 31 2005 14:58:34   yingbaol
// Initial revision.
 * 
 *

 */

