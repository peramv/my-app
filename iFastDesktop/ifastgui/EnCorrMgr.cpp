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
// ^FILE   : EnCorrMgr.cpp
// ^AUTHOR : Michael James McGarry
// ^DATE   : 29 Jul 1998
//
// ----------------------------------------------------------
//
// ^CLASS    : EnCorrMgr
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "encorrmgr.hpp"
#include "awdcommon.hpp"
#include <uibase\conditionmessagedialog.h>
#include "roadencorr.h"

#include <bfawdi\bfawddata.hpp>
#include <bfsessn\bfawdsession.hpp>

#include <configmanager.hpp>
#include <bfsessn\bfcpsessiontags.h>
#include <bfproc\genericinterface.hpp>
#include <idistring.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastcbo\entityidslist.hpp>
#include <afxpriv.h>

namespace
{
   const I_CHAR *ENCORR_MGR = I_( "ENCORR_MGR" );
   const I_CHAR *ENCORR     = I_( "EnCorrDSTGui.Entry" ); // Not "EnCorrDSTGui.CSW"
   const I_CHAR *IDI_OLEMSG = I_( "%OLEMSG%" );
   I_CHAR *START            = I_( "Start" );
}

namespace SessionTags
{
   //extern const I_CHAR *NT_ENCORR_EVENT;
   //change when NT_ENCORR_EVENT is defined.
   extern const I_CHAR *SESSION;
   const I_CHAR *NT_ENCORR_EVENT  = I_( "NtEnCorrEvent" );

   const I_CHAR *LETTER_TYPE_CODE = I_( "LetterTypeCode" );
   const I_CHAR *LETTER_TYPE      = I_( "LetterType" );
   const I_CHAR *ENCORR           = I_( "EnCorr" );
   const I_CHAR *ENCORR_TABLE     = I_( "EnCorr Table" );
}

namespace CND
{
   extern const long GUI_ENCORR_ALREADY_ACTIVE;
   extern const long GUI_SEARCH_ENCORR_NAMES;
   extern const long GUI_ENCORR_OLE_ERROR;
   extern const long GUI_SEARCH_ENCORR_DISPATCH;
   extern const long GUI_ENCORR_ERROR_MALLOC;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
EnCorrMgr *EnCorrMgr::getInstance()
{
   EnCorrMgr *pInstance = m_instanceManager.getInstance( ENCORR_MGR );
   return(pInstance);
}


void EnCorrMgr::start( GenericInterface *rpGIUserSession )
{
   TRACE_METHOD( I_( "EnCorrMgr" ), I_( "start" ))

   CWaitCursor wait;
   BFData params;
   BFData data;

   m_exitEnCorr = FALSE;

//   GenericInterface* rpGIUserSession = pGIC->findGI( 0, CMD_BPROC_USER_SESSION );
   BFCPSession *pSubSession = NULL;
   if( rpGIUserSession )
   {
      pSubSession = rpGIUserSession->getSession();
   }

   if( pSubSession )
   {
#ifdef AWD_BFDATA
      AWDCommon::getExportAwdConvertedData( data, *rpGIUserSession );
#endif
      ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
      Configuration cfgEnCorr = pMgr->retrieveConfig( SessionTags::ENCORR_TABLE );
      DString strEvent = pSubSession->getSessionData( SessionTags::NT_ENCORR_EVENT );
      Configuration cfgEvent = pMgr->retrieveConfig( strEvent );

      if( ! ( cfgEnCorr.isEmpty() || cfgEvent.isEmpty() ) )
      {
         pSubSession->setSessionData( SessionTags::NT_ENCORR_EVENT, I_( "" ));
         DString tag = cfgEnCorr.getValueAsString( SessionTags::LETTER_TYPE_CODE );
         DString value = cfgEvent.getValueAsString( SessionTags::LETTER_TYPE );

         if( ! ( tag.empty() || value.empty() ) )
         {
            data.setElementValue( tag, value, true);
         }

         BFAwdSession *pAwdSession = pSubSession->getAwdSession();

         if( pAwdSession )
         {
            DString strAwdWork = cfgEvent.getValueAsString( SessionTags::AWD_WORK );
            Configuration cfgAwd = pMgr->retrieveConfig( strAwdWork );

            DString strBusArea = cfgAwd.getValueAsString( SessionTags::BUSINESS_AREA );
            DString strWorktype = cfgAwd.getValueAsString( SessionTags::WORK_TYPE );
            DString strIStatus = cfgAwd.getValueAsString( SessionTags::ISTATUS );
            DString strPStatus = cfgAwd.getValueAsString( SessionTags::PSTATUS );

            if( ! ( strBusArea.empty() || strWorktype.empty() ||
                    strIStatus.empty() || strPStatus.empty() ) )
            {
               BFData dataForAwd;
               BFAwdData awdData( strBusArea, strWorktype, strIStatus );

               //Set up Export Data for AWD

//               pGlobal->getExportData( dataForAwd );
#ifdef AWD_BFDATA
               if( pAwdSession->createAwdTransaction( dataForAwd, awdData ) )
               //            if ( pAwdSession->createAwdTransaction( data, awdData ) )
               {
                  const BFAwdKey *pAwdKey = awdData.getKey();

                  data.setElementValue( AwdTags::UNIT , strBusArea, true );
                  params.setElementValue( AwdTags::UNIT , strBusArea, true );
                  params.setElementValue( AwdTags::CRDA, pAwdKey->getCreateDateTime(), true );
                  params.setElementValue( AwdTags::CRNO, pAwdKey->getCreateNode(), true );
                  params.setElementValue( AwdTags::RECO, pAwdKey->getRecordCode(), true );
                  params.setElementValue( SessionTags::PSTATUS, strPStatus, true );
               }
#endif
            }
         }


      }
   }

   spool( ERROR_ON_PRIOR_THREAD, data, params, CND::GUI_ENCORR_ALREADY_ACTIVE );
}

void EnCorrMgr::end()
{
   m_exitEnCorr = TRUE;
}

//******************************************************************************
//              Static member objects
//******************************************************************************

EnCorrMgr::InstanceManager EnCorrMgr::m_instanceManager;


//******************************************************************************
//              Protected Methods
//******************************************************************************

BOOL EnCorrMgr::performTask( COleDispatchDriver *pEnCorr )
{
   IDispatch *pDispatch = NULL;
   DISPID  dispid;
   HRESULT hr;

   // Get the DISPID of the Start method
   USES_CONVERSION;
   LPOLESTR pszName = T2OLE( START );

   hr = pEnCorr->m_lpDispatch->GetIDsOfNames( IID_NULL, &pszName, 1,
                                              LOCALE_SYSTEM_DEFAULT, &dispid );

   if( FAILED( hr ) )
   {
      MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "EnCorrMgr::performTask" ));
      DISPLAYCONDITIONFROMFILE( CND::GUI_SEARCH_ENCORR_NAMES );
   }
   else
   {
      RoadEncorr *pRoadEnCorr = new RoadEncorr;

      if( !pRoadEnCorr )
      {
         THROWFROMFILE( CND::IFASTGUI_CONDITION, I_( "EnCorrMgr::EnCorrMgr" ), CND::GUI_ENCORR_ERROR_MALLOC );
      }

      pRoadEnCorr->setData( getThreadData() );
      pRoadEnCorr->setAwdData( getThreadParams() );
      pRoadEnCorr->setProcessing();

      try
      {
         pDispatch = pRoadEnCorr->GetIDispatch( TRUE );
      }
      catch( COleException * oleException )
      {
         I_CHAR oleMsg[128];
         DString strTemp;
         oleException->GetErrorMessage( oleMsg, 128 );      
         addIDITagValue( strTemp, IDI_OLEMSG, oleMsg );
         MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "EnCorrMgr::EnCorrMgr" ));
         DISPLAYCONDITIONFROMFILEIDI( CND::GUI_ENCORR_OLE_ERROR, oleMsg);
         oleException->Delete();
         pRoadEnCorr->end();
         return(FALSE);
      }

      try
      {
         int result;
         static BYTE parms[] =
         VTS_DISPATCH;
         pEnCorr->InvokeHelper( dispid, DISPATCH_METHOD, VT_I4, (void *)&result,
                                parms, pDispatch );
      }
      catch( COleException * oleException )
      {
         I_CHAR oleMsg[128];
         oleException->GetErrorMessage( oleMsg, 128 );
         MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "EnCorrMgr::performTask" ));
         DISPLAYCONDITIONFROMFILEIDI( CND::GUI_ENCORR_OLE_ERROR, oleMsg);
         oleException->Delete();
         pRoadEnCorr->setProcessing( FALSE );
      }

      // Process the queue for awhile
      MSG msg;

      while( pRoadEnCorr->isProcessing() && ! m_exitEnCorr )
      {
         while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
         {
            if( ! pRoadEnCorr->isProcessing() || m_exitEnCorr )
            {
               break;
            }

            TranslateMessage( &msg);
            DispatchMessage( &msg );
         }

         Sleep( 50 );
      }

      pRoadEnCorr->end();
   }

   return(TRUE);
}

COleDispatchDriver *EnCorrMgr::createDispatch()
{
   TRACE_METHOD( I_( "EnCorrMgr" ), I_( "createDispatch" ))

   COleDispatchDriver *pEnCorr = new COleDispatchDriver;
   if( ! pEnCorr )
   {
      THROWFROMFILE( CND::IFASTGUI_CONDITION, I_( "EnCorrMgr::createDispatch" ), CND::GUI_ENCORR_ERROR_MALLOC );
   }

   if( ! pEnCorr->CreateDispatch( ENCORR ) )
   {
      MAKEFRAMENOTRACE( CND::IFASTGUI_CONDITION, I_( "EnCorrMgr::createDispatch" ))
      DISPLAYCONDITIONFROMFILE( CND::GUI_SEARCH_ENCORR_DISPATCH);
      delete pEnCorr;
      pEnCorr = NULL;
   }

   return(pEnCorr);
}

void EnCorrMgr::releaseDispatch( COleDispatchDriver *pOleDispatch )
{
   if( pOleDispatch )
   {
      pOleDispatch->ReleaseDispatch();
      delete pOleDispatch;
   }
   else
   {
      m_exitEnCorr = TRUE;
      Sleep( 100 );
   }
}


//******************************************************************************
//              Private Methods
//******************************************************************************

EnCorrMgr::EnCorrMgr( const DString &id )
: m_id( id ), m_exitEnCorr( FALSE )
{
   TRACE_CONSTRUCTOR( I_( "EnCorrMgr" ), I_( "EnCorrMgr( const DString & )" ))
}

EnCorrMgr::~EnCorrMgr()
{
   TRACE_DESTRUCTOR( I_( "EnCorrMgr" ))
   releaseDispatch();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EnCorrMgr.cpp-arc  $
 * 
 *    Rev 1.7   Mar 21 2003 18:35:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:55:38   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   May 28 2002 12:19:50   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.4   22 May 2002 19:15:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   Jun 19 2001 18:43:30   HERNANDO
 * Changed Parameter passed to Start() - GI instead of GIC
 * 
 *    Rev 1.2   03 May 2001 14:07:32   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Apr 05 2000 12:31:26   DT24433
 * changed GIContainer usage
 * 
 *    Rev 1.0   Feb 15 2000 11:01:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.5   Sep 14 1999 14:14:44   BUZILA
 * BFBase changes
 * 
 *    Rev 1.4   Jul 20 1999 11:18:46   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 12 1999 18:26:18   HSUCHIN
 * removed getExportAwdConvertedData
 * 
 *    Rev 1.2   Jul 08 1999 16:34:12   HSUCHIN
 * Modified getExportAwdConvertedData to pass more data 
 * 
 *    Rev 1.1   Jul 08 1999 10:05:04   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
