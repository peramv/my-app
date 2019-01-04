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
// ^FILE   : FormsMgr.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 1 Jul 1998
//
// ----------------------------------------------------------
//
// ^CLASS    : FormsMgr
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <bfdata\bfdata.hpp>
#include "formsmgr.hpp"
#include <uibase\editor.h>

#include <bfawdi\bfawdinterface.hpp>
#include <bfsessn\bfawdsession.hpp>
#include <bfawdi\bfawdkey.hpp>

#include <stringfunctions.hpp>
#include <uibase\conditionmessagedialog.h>
#include <uibase\oleglobal.hpp>
#include <configmanager.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <string>
#include <afxpriv.h>
#include <sessiontags.h>
#include <bfproc\genericinterface.hpp>
#include <idistring.hpp>
#include "awdcommon.hpp"

namespace
{
   const I_CHAR *FORMS_MGR      = I_( "FORMS_MGR" );
   const I_CHAR *FORMS          = I_( "Form.Document" );
   const I_CHAR *WINDOW_HANDLE  = I_( "HWND" );
   const I_CHAR *CASE_CRDA      = I_( "CASE_CRDA" );
   const I_CHAR *CASE_RECO      = I_( "CASE_RECO" );
   const I_CHAR *CASE_CRNO      = I_( "CASE_CRNO" );
   const I_CHAR *WORK_CASE      = I_( "WORK_CASE" );
   const I_CHAR *IDI_OLEMSG     = I_( "%OLEMSG%" );

}


namespace SessionTags
{
//   extern const I_CHAR *NT_EVENT_FORM;
//Temp.. remove
   const I_CHAR *NT_EVENT_FORM = I_( "NT Event Form" );
   const I_CHAR *SESSION = I_( "Session" );
}


namespace CND
{  // Conditions used
   extern const long GUI_FORMS_ALREADY_ACTIVE;
   extern const long GUI_FORMS_OLE_ERROR;
   extern const long GUI_FORMS_ERROR_MALLOC;
   extern const long GUI_SEARCH_FORMS_ID;
   extern const long GUI_SEARCH_FORMS_FACTORY;
   extern const long GUI_SEARCH_FORMS_CLASS;
}

namespace VF
{
   const I_CHAR * Registration_Name_1 = I_( "Registration_Name_1" );
   const I_CHAR * Registration_Name_2 = I_( "Registration_Name_2" );
   const I_CHAR * Registration_Name_3 = I_( "Registration_Name_3" );
   const I_CHAR * Registration_Name_4 = I_( "Registration_Name_4" );
   const I_CHAR * Registration_Name_5 = I_( "Registration_Name_5" );
   const I_CHAR * Registration_Name_6 = I_( "Registration_Name_6" );
   const I_CHAR * Registration_Name_7 = I_( "Registration_Name_7" );
   const I_CHAR * Registration_Name[] = 
   {  
      I_(""),
      Registration_Name_1,
      Registration_Name_2,
      Registration_Name_3,
      Registration_Name_4,
      Registration_Name_5,
      Registration_Name_6,
      Registration_Name_7,
   };
}

//******************************************************************************
//              Function prototypes
//******************************************************************************

DString longToHex( long value );
long hexToLong( DString value );

//******************************************************************************
//              Public Methods
//******************************************************************************

FormsMgr *FormsMgr::getInstance()
{
   FormsMgr *pInstance = m_instanceManager.getInstance( FORMS_MGR );

   return(pInstance);
}

void FormsMgr::start( HWND hWnd, GenericInterface *rpGIUserSession)
{
   TRACE_METHOD( FORMS_MGR, I_( "start" ))

   CWaitCursor wait;
   BFData params;
   BFData data;
   BFCPSession *pSubSession = NULL;
   BFAwdSession *pAwdSession = NULL;
//   GenericInterface* rpGIUserSession = pGIC->findGI( 0, CMD_BPROC_USER_SESSION );

   //fillInBlankAddressLines( data );

   // Set the parameters
   DString strWnd = longToHex( (long) hWnd );
   params.setElementValue( WINDOW_HANDLE, strWnd, true );

   if( rpGIUserSession )
   {
      pSubSession = rpGIUserSession->getSession();
   }

   if( pSubSession )
   {
      AWDCommon::getExportAwdConvertedData( data, *rpGIUserSession );
      DString strForm = pSubSession->getSessionData( SessionTags::NT_EVENT_FORM );

      if( !strForm.empty() )
      {
         // Set the form as a parameter then clear it out of session
         params.setElementValue( SessionTags::NT_EVENT_FORM, strForm, true );
         pSubSession->setSessionData( SessionTags::NT_EVENT_FORM, NULL_STRING );
      }

      pAwdSession = pSubSession->getAwdSession();

      if( pAwdSession )
      {
         // See if we have a case, if so, pass the key
         const BFAwdKey *pAwdKey = pAwdSession->getAwdCase();

         // If we are get work and do not have a case, there still might be one.
//         if ( ! ( pGlobal->isTelTranMode() || pAwdKey ) )
         if( ! ( pAwdKey == NULL) )
         {
            BFAwdInterface awd;

            const BFAwdData *pWork = pAwdSession->getProcessWork();
            const BFAwdKey *pWorkKey = pWork->getKey();

            try
            {
               BFAwdKey *pWorkCase;
               awd.hasCaseForParent( pWorkKey, &pWorkCase );
               pAwdKey = pWorkCase;

               if( pWorkCase )
               {
                  DString strCase = longToHex( (long) pWorkCase );
                  params.setElementValue( WORK_CASE, strCase, true );
               }
            }
            catch( ConditionException &ce )
            {
               ConditionMessageBox( ce );
               return;
            }
         }

         if( pAwdKey )
         {
            params.setElementValue( CASE_CRDA, pAwdKey->getCreateDateTime(), true );
            params.setElementValue( CASE_CRNO, pAwdKey->getCreateNode(), true );
            params.setElementValue( CASE_RECO, pAwdKey->getRecordCode(), true );
         }
      }

      m_exitForms = FALSE;

      spool( ERROR_ON_PRIOR_THREAD, data, params, CND::GUI_FORMS_ALREADY_ACTIVE );
   }
}

void FormsMgr::end()
{
   m_exitForms = TRUE;
}

//******************************************************************************
//              Static member objects
//******************************************************************************

FormsMgr::InstanceManager FormsMgr::m_instanceManager;


//******************************************************************************
//              Protected Methods
//******************************************************************************

BOOL FormsMgr::performTask( COleDispatchDriver *pOleDispatch )
{
   TRACE_METHOD( I_( "FormsMgr" ), I_( "performTask" ) );

   DString strIDI;

   IEditor *pEditor = static_cast<IEditor *>( pOleDispatch );
   UINT formsComplete = RegisterWindowMessage( FORMS );
   getThreadData()->getAllValues( strIDI );

   // make sure we were passed the HWND
   if( ! getThreadParams()->exists( WINDOW_HANDLE ) )
   {
      // Bad JuJu
      return(FALSE);
   }

   // extract the HWND
   DString strWnd = getThreadParams()->getElementValue( WINDOW_HANDLE );
   HWND hWnd = (HWND) hexToLong( strWnd.c_str() );

   // We will create an invisible window using the desktop as its parent.
   // This is so that we will see the message when the Form is done. - DMUM
   CWnd *pParent = CWnd::GetDesktopWindow();
   RECT rect = { 0, 0, 1, 1};
   CWnd invisible;
   invisible.Create( NULL, NULL, 0L , rect, pParent, 0 );
   long lWnd = (long) invisible.m_hWnd;

   // See if we have a case to pass
   DString createDateTime;
   DString recordCode;
   DString createNode;

   if( getThreadParams()->exists( CASE_CRDA ) )
   {
      createDateTime = getThreadParams()->getElementValue( CASE_CRDA );
   }

   if( getThreadParams()->exists( CASE_RECO ) )
   {
      recordCode = getThreadParams()->getElementValue( CASE_RECO );
   }

   if( getThreadParams()->exists( CASE_CRNO ) )
   {
      createNode = getThreadParams()->getElementValue( CASE_CRNO );
   }

   strip( createDateTime );
   strip( recordCode );
   strip( createNode );

   BOOL haveCase = ( ! ( createDateTime.empty() ||
                         recordCode.empty() ||
                         createNode.empty() ) );

   DString strForm;
   CString cstrForm;

   if( getThreadParams()->exists( SessionTags::NT_EVENT_FORM ) )
   {
      strForm = getThreadParams()->getElementValue( SessionTags::NT_EVENT_FORM );
   }

   try
   {
      pEditor->RunAsForms( lWnd, NULL_STRING );
      pEditor->SetVisible( TRUE );
      pEditor->RunAsForms( lWnd, I_( "Return to TA2000 NT" ) );

      if( ! strForm.empty() )
      {
         cstrForm = strForm.c_str();
      }
      else
      {
         cstrForm = pEditor->FileOpenDialog();
      }

      // If they cancelled, leave
      if( cstrForm.IsEmpty() )
      {
         // Tell the invisible window to go away
         invisible.DestroyWindow();
         // Set focus back on ourself and return
         safeSetForeground( hWnd );
         return(FALSE);
      }

      // Open the file
      if( pEditor->FileOpen( cstrForm, 0 ) )
      {
         // Tell the invisible window to go away
         invisible.DestroyWindow();
         // Open failed - Set focus back on ourself and return
         safeSetForeground( hWnd );
         return(FALSE);
      }

      // Pass the data to forms
      pEditor->ReplaceVariablesWith( strIDI.c_str() );

      // Pass the case if we have one
      if( haveCase )
      {
         pEditor->UseCaseObjectValues( createDateTime.c_str(),
                                       recordCode.c_str(),
                                       createNode.c_str() );
      }
   }
   catch( COleException * oleException )
   {
      I_CHAR oleMsg[128];
      oleException->GetErrorMessage( oleMsg, 128 );
      MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "FormsMgr::createDispatch" ) );
      DString strTemp;
      addIDITagValue( strTemp, IDI_OLEMSG, oleMsg );
      DISPLAYCONDITIONFROMFILEIDI( CND::GUI_FORMS_OLE_ERROR, oleMsg);
      oleException->Delete();

      m_exitForms = true;
   }

   // Process the queue for a while - until they exit the form.
   BOOL wait = true;
   MSG msg;

   while( wait && ! m_exitForms )
   {
      while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
      {
         if( ( formsComplete == msg.message ) || m_exitForms )
         {
            wait = FALSE;
            break;
         }

         TranslateMessage( &msg);
         DispatchMessage( &msg );
      }

      Sleep( 50 );
   }

   // Tell the invisible window to go away
   invisible.DestroyWindow();

   // Give the search screen focus
   safeSetForeground( hWnd );

   // If we were not told to shut down
   if( ! m_exitForms )
   {
      long lParam = 0L;

      if( getThreadParams()->exists( WORK_CASE ) )
      {
         DString strCase = getThreadParams()->getElementValue( WORK_CASE );
         lParam = hexToLong( strCase.c_str() );
      }

      OleGlobal *pOleGlobal = OleGlobal::getInstance();
      pOleGlobal->postMessageToSearchScreen( UM_EXPANDCASE, 0L, lParam );
   }

   return(TRUE);

}


COleDispatchDriver *FormsMgr::createDispatch()
{
   TRACE_METHOD( I_( "FormsMgr" ), I_( "createDispatch()" ))

   HRESULT         hr;
   CLSID           clsid;
   LPUNKNOWN       lpUnknown = NULL;
   LPCLASSFACTORY  lpClassFactory = NULL;
   LPDISPATCH      lpDispatch;
   I_CHAR           szID[ 20 ];

   IEditor *pEditor = new IEditor();

   if( ! pEditor )
   {
      THROWFROMFILE( CND::IFASTGUI_CONDITION, I_( "FormsMgr::performTask()"), CND::GUI_FORMS_ERROR_MALLOC );
   }

   try
   {
      USES_CONVERSION;        // Macro used to convert LPCTSTR types to wchar_t types

      i_strcpy( szID, FORMS );
      hr = CLSIDFromProgID( T2OLE( szID ), &clsid );

      if( FAILED( hr ) )
      {
         MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "FormsMgr::createDispatch()" ));
         DISPLAYCONDITIONFROMFILE( CND::GUI_SEARCH_FORMS_ID);
         delete pEditor;
         return(NULL);
      }

      hr = CoGetClassObject( clsid, CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER, NULL,
                             IID_IClassFactory, ( LPVOID * )&lpClassFactory );

      if( FAILED( hr ) )
      {
         MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "FormsMgr::createDispatch()" ));
         DISPLAYCONDITIONFROMFILE( CND::GUI_SEARCH_FORMS_CLASS);
         delete pEditor;
         return(NULL);
      }

      hr = lpClassFactory->CreateInstance( NULL, IID_IDispatch, ( LPVOID * )&lpDispatch );
      lpClassFactory->Release();

      if( FAILED( hr ) )
      {
         MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "FormsMgr::createDispatch()" ));
         DISPLAYCONDITIONFROMFILE( CND::GUI_SEARCH_FORMS_FACTORY);
         delete pEditor;
         return(NULL);
      }

      pEditor->AttachDispatch( lpDispatch );

      //
      // This code below should work, but it doesn't - so use the code above
      //
      // if ( ! pEditor->CreateDispatch( FORMS ) )
      // {
      //    delete pEditor;
      //    pEditor = NULL;
      // }
      // else
      // {
      //    string msg = "Dispatch to CallTracker established.";
      //    TRACE_MSG( msg.c_str() )
      // }
   }
   catch( COleException * oleException )
   {
      I_CHAR oleMsg[128];
      oleException->GetErrorMessage( oleMsg, 128 );
      MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "FormsMgr::createDispatch()" ));
      DISPLAYCONDITIONFROMFILEIDI( CND::GUI_FORMS_OLE_ERROR, oleMsg);
      oleException->Delete();

      delete pEditor;
      pEditor = NULL;
   }

   return(pEditor);

//remove later
   return(NULL);
}

void FormsMgr::releaseDispatch( COleDispatchDriver *pOleDispatch )
{
   TRACE_METHOD( I_( "FormsMgr" ), I_( "releaseDispatch( COleDispatchDriver * )" ))

   if( pOleDispatch )
   {
      IEditor *pEditor = static_cast<IEditor *>( pOleDispatch );

      pEditor->ReleaseDispatch();
      delete pEditor;
   }
   else
   {
      m_exitForms = TRUE;
      Sleep( 100 );
   }

}


//******************************************************************************
//              Private Methods
//******************************************************************************
FormsMgr::FormsMgr( const DString &id )
: m_id( id ), m_exitForms( FALSE )
{
   TRACE_CONSTRUCTOR( I_( "FormsMgr" ), I_( "FormsMgr( const DString & )" ))
}

FormsMgr::~FormsMgr()
{
   TRACE_DESTRUCTOR( I_( "FormsMgr" ))
   releaseDispatch();
}

void FormsMgr::safeSetForeground( HWND hWnd )
{
   CWnd *pWnd = ::IsWindow( hWnd ) ? CWnd::FromHandle( hWnd ) : NULL;

   if( pWnd )
   {
      pWnd->SetForegroundWindow();
   }
}


//******************************************************************************
//
// ^PRIVATE METHOD      : FormsMgr::fillInBlankAddressLines
//
// ^DESCRIPTION : This will make sure that all the Registration lines have at
//                least a space.
//
// ^PARAMETERS  :
//   ^^ Data &data -
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************

void FormsMgr::fillInBlankAddressLines( BFData &data )
{
   DString strRegLine;
   DString strAwdRegLine;
   ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
   Configuration cfgTable = pMgr->retrieveConfig( SessionTags::WORK_TABLE );
   for( int index = 1; index <= 7; ++index )
   {
      strRegLine = VF::Registration_Name[ index ];
      strAwdRegLine = cfgTable.getValueAsString( strRegLine );

      if( strAwdRegLine.empty() )
      {
         strAwdRegLine = strRegLine;
      }

      if( ! data.exists( strAwdRegLine ) )
      {
         data.setElementValue( strAwdRegLine, I_(" "));
      }

   }
}

//******************************************************************************
//              Functions
//******************************************************************************

DString longToHex( long value )
{
   char buffer[10];
   _ltoa( value, buffer, 16 );
   DString strValue( I_( "0x" ));
   strValue += DString(DStringA(buffer));
   return(strValue);
}

long hexToLong( DString value )
{
   return(strtol( DStringA(value).c_str(), (char **)NULL, 16 ));
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FormsMgr.cpp-arc  $
 * 
 *    Rev 1.7   Mar 21 2003 18:36:34   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:55:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   May 28 2002 12:19:50   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.4   22 May 2002 19:16:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   Jun 19 2001 18:43:32   HERNANDO
 * Changed Parameter passed to Start() - GI instead of GIC
 * 
 *    Rev 1.2   03 May 2001 14:07:34   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Apr 05 2000 12:43:02   DT24433
 * changed usage of GIContainer
 * 
 *    Rev 1.0   Feb 15 2000 11:01:14   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Jul 20 1999 11:18:54   VASILEAD
 * New conditions update
 * 
 *    Rev 1.5   Jul 12 1999 18:26:00   HSUCHIN
 * removed getExportAwdConvertedData
 * 
 *    Rev 1.4   Jul 09 1999 07:14:20   HUANGSHA
 * Change the comment 
 * 
 *    Rev 1.2   Jul 08 1999 16:34:12   HSUCHIN
 * Modified getExportAwdConvertedData to pass more data 
 *
 */
