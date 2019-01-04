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
// ^FILE   : IdCallerDlg.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 1/10/99
//
// ----------------------------------------------------------
//
// ^CLASS    : IdCallerDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the IdCallerDlg dialog
//
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <bfdata\bfdata.hpp>
#include "idcallerdlg.h"
#include "awdcommon.hpp"
#include <bfawdi\bfawdinterface.hpp>
#include <bfsessn\bfawdsession.hpp>
#include <bfsessn\bfcpsession.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtco.hpp>

#include <bfproc\bpsessiontags.h>
#include <uibase\conditionmessagedialog.h>
#include <bfutil\bfdate.hpp>
#include <configmanager.hpp>
#include "mainfrm.h"
#include <uibase\dstcdoc.h>
#include "dstcview.h"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastawd\DSTCAWDSession.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_IDCALLER;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< IdCallerDlg > dlgCreator( CMD_GUI_IDCALLER );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace SessionTags
{
   const I_CHAR *ID_CALLER = I_( "ID Caller" );
}

namespace
{
   const I_CHAR *CLASSNAME = I_( "IdCallerDlg" );
   const I_CHAR *ID_FILLRELATIONSHIP = I_( "fillRelationship" );
   const I_CHAR *ID_LSTCALLERNAME = I_( "OnSelchangeLstCallername" );
   const I_CHAR *ID_SETCALLERINFO = I_( "setCallerInfo" );
   const I_CHAR *ID_SETCALLERNAME = I_( "setCallerName" );
   const I_CHAR *ID_SETNAME = I_( "setName" );
   const I_CHAR *ID_STOREDATA = I_( "storeData" );
   const I_CHAR *CALL_INQUIRY_INFO = I_("CALL INQUIRY INFO");
   const I_CHAR *MGMCO = I_("MGMCO");
   const I_CHAR *AWD_PTR = I_("_AwdInterface_Ptr_");
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_INVALID_FIELD_ENTRY;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
   extern CLASS_IMPORT const BFTextFieldId CallerName;
   extern CLASS_IMPORT const BFTextFieldId Operator_Extension;
   extern CLASS_IMPORT const BFTextFieldId RelationShip;
   extern CLASS_IMPORT const BFTextFieldId BusinessPhone;
   extern CLASS_IMPORT const BFTextFieldId BusinessExt;
   extern CLASS_IMPORT const BFTextFieldId HomePhone;
   extern CLASS_IMPORT const BFTextFieldId CallStartTime;
   extern CLASS_IMPORT const BFTextFieldId CallEndTime;
   extern CLASS_IMPORT const BFTextFieldId SegStartTime;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;

}


//******************************************************************************
// Public methods
//******************************************************************************

IdCallerDlg::IdCallerDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( IdCallerDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME),
m_pWorkstation( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(IdCallerDlg)
   //}}AFX_DATA_INIT

   FirstTimeOpen=TRUE;
}

//******************************************************************************

void IdCallerDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(IdCallerDlg)
   DDX_Control( pDX, IDC_EDT_EXTENSION2, m_ExtensionBusiness );
   DDX_Control( pDX, IDC_EDT_EXTENSION1, m_ExtensionOperator );
   DDX_Control( pDX, IDC_PHONE2, m_PhoneBusiness );
   DDX_Control( pDX, IDC_PHONE1, m_PhoneHome );
   DDX_Control( pDX, IDC_CMB_RELATIONSHIP, m_Relationship );
   DDX_Control( pDX, IDC_EDT_CALLER_NAME, m_callerName );
   DDX_Control( pDX, IDC_TXT_START_DATE, m_StartDateTime );
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(IdCallerDlg, BaseMainDlg)
//{{AFX_MSG_MAP(IdCallerDlg)
ON_BN_CLICKED( IDC_BTN_INQUIRY_COMPLETED, OnBtnInquiryCompleted )
/// ON_BN_CLICKED( IDC_BTN_INQUIRY_COMPLETED_END_CALL, OnBtnInquiryCompletedEndCall )
ON_BN_CLICKED( IDC_BTN_END_CALL, OnBtnEndCall )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/******************************************************************************
   Message handlers
   STTAG( CallerExtension );
   STTAG( CallerName );
   STTAG( CallerPhoneNumber );
   STTAG( CallerRelationship );
   STTAG( OperatorExtension );
   STTAG( SecondaryExt );
   STTAG( SecondaryPhone );
   STTAG( USERSESSIONID );
   STTAG( WORKSESSIONID );
   STTAG( CallTime );
   STTAG( PhoneAreaCode );
   STTAG( SecondaryAreaCode );
******************************************************************************/

void IdCallerDlg::setCallerInfo( void )
{
   TRACE_METHOD( CLASSNAME, ID_SETCALLERINFO );
	
   DSTCAWDSession* pAwdSession = dynamic_cast< DSTCAWDSession* >(getSession() );			
   if( pAwdSession )
   {
	DString dstrValue;
	pAwdSession->getAwdField(ifds::CallerName,dstrValue );
	m_callerName.SetWindowText( dstrValue.strip().c_str() );
	pAwdSession->getAwdField(ifds::HomePhone,dstrValue );
	m_PhoneHome.SetWindowText( dstrValue.strip().c_str() );
	pAwdSession->getAwdField(ifds::BusinessPhone,dstrValue );
	m_PhoneBusiness.SetWindowText( dstrValue.strip().c_str() );

	pAwdSession->getAwdField(ifds::BusinessExt,dstrValue );
	m_ExtensionBusiness.SetWindowText( dstrValue.strip().c_str() );
	
	pAwdSession->getAwdField(ifds::RelationShip,dstrValue );
	m_Relationship.SelectString( -1, dstrValue.strip().c_str() );
	pAwdSession->getAwdField(ifds::CallStartTime, dstrValue );
	DString time = dstrValue;
	if( time.stripAll() == NULL_STRING )
	{
		dstrValue = pAwdSession->getTimeStamp();	
		pAwdSession->setAwdField(ifds::CallStartTime,dstrValue );
		pAwdSession->setAwdField(ifds::SegStartTime, dstrValue);     
	}
	m_StartDateTime.SetWindowText( dstrValue.strip().c_str() );

	pAwdSession->getAwdField(ifds::Operator_Extension,dstrValue );
	m_ExtensionOperator.SetWindowText( dstrValue.strip().c_str() );


    UpdateData( FALSE );
	m_callerName.SetFocus();
   }
   
   /*
   CString cstrHold;

   // Caller Full Name
   cstrHold = ( getSession()->getSessionData( I_("CallerFullName") ) ).c_str();
   m_callerName.SetWindowText( cstrHold );

   // Caller Home Number
   cstrHold = ( getSession()->getSessionData( I_("CallerHomeNumber") )).c_str();
   m_PhoneHome.SetWindowText( cstrHold );

   // Caller Business Number
   cstrHold = ( getSession()->getSessionData( I_("CallerBusinessNumber") )).c_str();
   m_PhoneBusiness.SetWindowText( cstrHold );

   // Caller Business Extension
   cstrHold = ( getSession()->getSessionData( I_("CallerBusinessExtension") )).c_str();
   m_ExtensionBusiness.SetWindowText( cstrHold );

   // Operator Extension
   m_pWorkstation = ConfigManager::getManager( I_("Workstation") );
   m_workstation = m_pWorkstation->retrieveConfig( I_( "Settings" ) );
   cstrHold = ( getSession()->getSessionData( SessionTags::OperatorExtension )).c_str();
   if( cstrHold.IsEmpty() == FALSE )
   {
      m_ExtensionOperator.SetWindowText( cstrHold );
   }
   else
   {
      DString dstrExt = m_workstation.getValueAsString( SessionTags::OperatorExtension );
      m_ExtensionOperator.SetWindowText( dstrExt.c_str() );
   }
     
   // Set the Start Time and Date of Call (if not already started) and store.
   cstrHold = ( getSession()->getSessionData( I_("CallStartDateTime") )).c_str();
   if( cstrHold.IsEmpty() == TRUE )
   {
      DString dstrCallStartDateTime = getSession()->getTimeStamp();
      getSession()->setGlobalSessionData( I_("CallStartDateTime"), dstrCallStartDateTime );
      m_StartDateTime.SetWindowText( dstrCallStartDateTime.c_str() );

      // Set the Start Time and Date of Object to the same value and store.
      getSession()->setGlobalSessionData( I_("ObjectStartDateTime"), dstrCallStartDateTime );
   }
   else
   {
      // Display existing values
      m_StartDateTime.SetWindowText( cstrHold );
   }

   // Set Relationship
   cstrHold = ( getSession()->getSessionData( SessionTags::CallerRelationship )).c_str();
   m_Relationship.SelectString( -1, cstrHold );

   UpdateData( FALSE );
   CWnd *pCtrl = GetDlgItem( IDC_EDT_CALLER_NAME );
   pCtrl->SetFocus();
   */
}

bool IdCallerDlg::PreOk()
{
   storeData();
   return(true);
}

//*****************************************************************************
//
// ^METHOD : IdCallerDlg::OnInitDialog()
//
// ^DESCRIPTION : Load the Relationships and put use where we need to be
//
// ^PARAMETERS  :
//      void
//
// ^RETURNS     :
//      normal
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************

BOOL IdCallerDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   CWaitCursor cursor;
   BaseMainDlg::OnInitDialog();

   m_hwndParent = GetMyParent()->m_hWnd;

   // Populate Combo Box
   CString tmp;
   m_Relationship.AddString( tmp );
   tmp.LoadString( TXT_IDCALLER_ACCHOLDER );
   m_Relationship.AddString( tmp );
   tmp.LoadString( TXT_IDCALLER_DEALER );
   m_Relationship.AddString( tmp );
   tmp.LoadString( TXT_IDCALLER_REP );
   m_Relationship.AddString( tmp );
   tmp.LoadString( TXT_IDCALLER_OTHER );
   m_Relationship.AddString( tmp );

   m_Relationship.SetCurSel( 0 );   // Select the first item

   // Load the Name Listbox if there is appropriate data, and display existing data
   setCallerInfo();

   CWnd *y=GetDlgItem( IDC_EDT_CALLER_NAME );
   y->SetFocus();

   // Send message to Search Dialog to get it to retrieve the data
   ((CDSTCView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()))->SendMessage( UM_IDDATA );

   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************************************************
//
// ^PRIVATE METHOD : IdCallerDlg::storeData()
//
// ^DESCRIPTION : Sets the Data so it can be displayed in RoadRunner
//
// ^PARAMETERS  :
//      none
//
// ^RETURNS     :
//      void
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************

void IdCallerDlg::storeData( void )
{
   TRACE_METHOD( CLASSNAME, ID_STOREDATA );
  

    UpdateData();

   DString dstrAccountNum;

   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );

   CDSTCView* dstcview = ((CDSTCView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()));

   DSTCAWDSession* pAwdSession = dynamic_cast< DSTCAWDSession* >(getSession() );			
   CString cstr;
   m_callerName.GetWindowText( cstr);
	m_awdData.setElementValue(ifds::CallerName, LPCTSTR( cstr ), true );
   if( pAwdSession )
	   pAwdSession->setAwdField(ifds::CallerName,LPCTSTR( cstr ) );

   m_PhoneHome.GetWindowText( cstr);
	m_awdData.setElementValue(ifds::HomePhone,LPCTSTR( cstr ), true );
   if( pAwdSession )
	   pAwdSession->setAwdField(ifds::HomePhone,LPCTSTR( cstr ) );

   m_PhoneBusiness.GetWindowText( cstr);
	m_awdData.setElementValue(ifds::BusinessPhone,LPCTSTR( cstr ), true );
   if( pAwdSession )
	   pAwdSession->setAwdField(ifds::BusinessPhone,LPCTSTR( cstr ) );

   m_ExtensionBusiness.GetWindowText( cstr);
	m_awdData.setElementValue(ifds::BusinessExt,LPCTSTR( cstr ), true );
   if( pAwdSession )
	   pAwdSession->setAwdField(ifds::BusinessExt,LPCTSTR( cstr ) );

   m_ExtensionOperator.GetWindowText( cstr);
	m_awdData.setElementValue(ifds::Operator_Extension, LPCTSTR( cstr ), true );
   if( pAwdSession )
	   pAwdSession->setAwdField(ifds::Operator_Extension,LPCTSTR( cstr ) );

   m_Relationship.GetWindowText( cstr);
	m_awdData.setElementValue(ifds::RelationShip, LPCTSTR( cstr ), true );
   if( pAwdSession )
	   pAwdSession->setAwdField(ifds::RelationShip,LPCTSTR( cstr ) );

	m_awdData.setElementValue(ifds::AccountNum, dstrAccountNum, true );
   if( pAwdSession )
	   pAwdSession->setAwdField(ifds::AccountNum,dstrAccountNum );
	
   dstcview->SetWorkData(CMD_GUI_IDCALLER, m_awdData);

   // Send message to Search Dialog to get it to retrieve the data
   dstcview->SendMessage( UM_IDDATA );
}

//*****************************************************************************

void IdCallerDlg::OnBtnInquiryCompleted()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnInquiryCompleted") );

   // Check for Extension Value
   CString cstrHold;
   m_ExtensionOperator.GetWindowText( cstrHold );
   if( cstrHold.IsEmpty() == TRUE )
   {
      // Report message
      AfxMessageBox( TXT_ENTER_EXTENSION, MB_OK | MB_ICONSTOP );
      // Set Focus
      CWnd *pCtrl = GetDlgItem( IDC_EDT_EXTENSION1 );
      pCtrl->SetFocus();
      return;
   }

   // Store the values in case the user has added values just before 'Inquiry Completed'.
   storeData();

   DSTCAWDSession* pAwdSession = dynamic_cast< DSTCAWDSession* >(getSession() );			
   if( pAwdSession )
   {

      if( WARNING < pAwdSession->CallInquiry() )
	  {
		 ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );	  
	  }   
   }

   ((CDSTCView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()))->createWork(CMD_GUI_IDCALLER);
   
  /* 
   // Establish the Object End Time and retain for the next Object Start Time.
   DString dstrObjectEndDateTime = getSession()->getTimeStamp();
   getSession()->setGlobalSessionData( I_("ObjectEndDateTime"), dstrObjectEndDateTime );

   // Create AWD object
      BFAwdSession  *pAwdSession = NULL;
      if( getSession() != NULL )
      {
         pAwdSession = getSession()->getAwdSession();
      }

      if( pAwdSession )
      {
         BFData data;
         BFDataPtrMap dummy;

         // Set Business Area, Status, and Type -- use getCreateDefault settings.
         DString dstrBusinessArea, dstrProcessStatus, dstrWorkType;
         if( pAwdSession->isAwdDefined( CALL_INQUIRY_INFO ) )
         {
            pAwdSession->getCreateDefaults( CALL_INQUIRY_INFO, dstrBusinessArea, dstrWorkType, dstrProcessStatus, true ); // Process Status = true *);
         }

         // Set Business Area
         if( dstrBusinessArea.empty() )
         {
            // Get Company ID
            DString dstrCompanyId;
            DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
            dstWorkSession->getMgmtCo().getField(ifds::CompanyId, dstrCompanyId, BF::HOST );
            GetBusinessArea( dstrCompanyId, dstrBusinessArea );
         }

         // Set Values
         getSession()->setSessionData( SessionTags::BUSINESS_AREA, dstrBusinessArea );
         getSession()->setSessionData( SessionTags::WORK_TYPE, dstrWorkType );
         getSession()->setSessionData( SessionTags::STATUS, dstrProcessStatus );
         getSession()->setSessionData( SessionTags::AWD_EVENT, SessionTags::CREATE_WORK );

         AWDCommon::getExportAwdConvertedData(data, *this );   // Replace this with AWD CALL POPULATION
         dummy.insert( BFDataPtrMap::value_type( I_("DEFAULT"), &data));
         if( WARNING < getSession()->setSessionEvent( SessionTags::CREATE_WORK, dummy) )
         {
            // Report err if failed
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         }
      }

   // Set the next Object Start Time
   getSession()->setGlobalSessionData( I_("ObjectStartDateTime"), dstrObjectEndDateTime );
   getSession()->setGlobalSessionData( I_("ObjectEndDateTime"), NULL_STRING );
*/

}

//*****************************************************************************

void IdCallerDlg::OnBtnInquiryCompletedEndCall()
{
   OnBtnInquiryCompleted();
   OnBtnEndCall();
}

//*****************************************************************************

void IdCallerDlg::OnBtnEndCall()
{
   // Clear Global values from Session Data
  
   DSTCAWDSession* pAwdSession = dynamic_cast< DSTCAWDSession* >(getSession() );			
   if( pAwdSession )
   {
   
		pAwdSession->EndCall();
   }
   
   /* getSession()->setGlobalSessionData( I_("CallerFullName"), NULL_STRING );            // Caller Name
   getSession()->setGlobalSessionData( I_("CallerHomeNumber"), NULL_STRING );          // Home Phone Number
   getSession()->setGlobalSessionData( I_("CallerBusinessNumber"), NULL_STRING );      // Business Phone Number
   getSession()->setGlobalSessionData( I_("CallerBusinessExtension"), NULL_STRING );   // Business Extension
   getSession()->setGlobalSessionData( I_("CallStartDateTime"), NULL_STRING );         // Start Date & Time
   getSession()->setGlobalSessionData( SessionTags::CallerRelationship, NULL_STRING ); // Relationship
   getSession()->setGlobalSessionData( I_("ObjectStartDateTime"), NULL_STRING );       // Object Start Date & Time
   getSession()->setGlobalSessionData( I_("ObjectEndDateTime"), NULL_STRING );         // Object End Date & Time
*/
   // Clear controls
   m_callerName.SetWindowText( NULL_STRING );
   m_PhoneHome.SetWindowText( NULL_STRING );
   m_PhoneBusiness.SetWindowText( NULL_STRING );
   m_ExtensionBusiness.SetWindowText( NULL_STRING );
   m_Relationship.SetCurSel( -1 );   // Select the first item
   m_StartDateTime.SetWindowText( NULL_STRING );

   // Send message to Search Dialog to get it to retrieve the data
   ((CDSTCView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()))->SendMessage( UM_IDDATA );

   GetDlgItem( IDC_BTN_INQUIRY_COMPLETED )->EnableWindow( FALSE );
   GetDlgItem( IDC_BTN_INQUIRY_COMPLETED_END_CALL )->EnableWindow( FALSE );
   GetDlgItem( IDC_BTN_END_CALL )->EnableWindow( FALSE );
   PostMessage( WM_COMMAND, IDOK );
}

//*****************************************************************************

void IdCallerDlg::GetBusinessArea( const DString &dstrCompanyId, DString &dstrBusinessArea )
{
   dstrBusinessArea = NULL_STRING;
   string_vector  listTemp;
   string_vector_const_iterator  iter;

   // Get AWD Interface Ptr
   DString dstrSourcePtr = getSession()->getSessionData( AWD_PTR );
   BFAwdInterface *pAwdInterface = (BFAwdInterface *) dstrSourcePtr.asInteger();

   // Iterate AWD Business Area list in MGMCO to find matching ID
   bool  bFound = false;
   if( !dstrCompanyId.empty() )
   {
      ConfigManager *pConfigManager = ConfigManager::getManager( SessionTags::Session );
      Configuration sysTable = pConfigManager->retrieveConfig( MGMCO);

      DString  dstrTempBusinessArea = NULL_STRING;
      listTemp = pAwdInterface->getBusinessAreaList();
      iter = listTemp.begin();

      while( (iter != listTemp.end()) && !bFound )
      {
         dstrTempBusinessArea = *iter;
         dstrTempBusinessArea.strip();
         if( bFound = (dstrCompanyId == sysTable.getValueAsString( dstrTempBusinessArea ).stripAll( I_CHAR('\t') )) )
         {
            dstrBusinessArea = dstrTempBusinessArea;
            break;
         }
         iter++;
      }
   }
}


BEGIN_EVENTSINK_MAP(IdCallerDlg, BaseMainDlg)
//{{AFX_EVENTSINK_MAP(IdCallerDlg)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/IdCallerDlg.cpp-arc  $
 * 
 *    Rev 1.16   Sep 15 2005 15:13:26   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.15   Jan 17 2005 18:33:02   hernando
 * PTS10037736 - Removed reference to AWDEVENT. (Sync up from 1.13.1.0)
 * 
 *    Rev 1.14   Jan 10 2005 11:11:44   hernando
 * PET1189 FN1 - Dual-Monitor changes.
 * 
 *    Rev 1.13   Feb 23 2004 17:07:34   popescu
 * PTS 10027470, revert to old logic of saving the settings into the current user registry location instead of local machine
 * 
 *    Rev 1.12   Jan 21 2004 10:22:56   YINGBAOL
 * PET987: strip space for phone number 
 * 
 *    Rev 1.11   Jan 15 2004 11:28:12   YINGBAOL
 * PET897:: change SegStartTime logic
 * 
 *    Rev 1.10   Jan 13 2004 16:35:56   YINGBAOL
 * PET987:Add empty choice for relationship
 * 
 *    Rev 1.9   Jan 12 2004 14:56:24   YINGBAOL
 * PET987: Convert to DSTCAwdSession interface
 * 
 *    Rev 1.8   Dec 31 2003 13:57:36   HERNANDO
 * PET910 - AWD Voice integration enhancement.
 * 
 *    Rev 1.7   Mar 21 2003 18:37:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:55:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Jul 05 2002 11:49:42   PURDYECH
 * Infrastructure Fixup ... no more ICU!
 * 
 *    Rev 1.4   May 28 2002 12:19:52   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.3   22 May 2002 19:16:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   27 Mar 2002 20:01:12   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.1   Oct 06 2000 13:38:58   HERNANDO
 * Preventive measure; make sure session exists before getAWDSession
 * 
 *    Rev 1.0   Feb 15 2000 11:01:16   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.13   Dec 08 1999 11:45:46   YINGZ
 * change ok to preok to make it work
 * 
 *    Rev 1.12   Nov 10 1999 13:46:28   VASILEAD
 * Changed USER_GLOBALS to WORK_GLOBALS
 * 
 *    Rev 1.11   Oct 15 1999 11:08:04   POPESCUS
 * Fixed compiling issues related to the new infra-1900
 * 
 *    Rev 1.10   Oct 01 1999 14:33:12   YINGZ
 * fix data not display probelm
 * 
 *    Rev 1.9   Sep 01 1999 15:25:32   BUZILA
 * Fix Positioning
 * 
 *    Rev 1.8   Jul 28 1999 10:16:22   VASILEAD
 * Constrain CallerName text filed to 60 characters
 * 
 *    Rev 1.7   Jul 21 1999 12:10:34   YINGZ
 * ?
 * 
 *    Rev 1.6   Jul 20 1999 13:52:30   YINGZ
 * use new feature in CTelEdit (about ime)
 * 
 *    Rev 1.5   Jul 20 1999 11:19:00   VASILEAD
 * New conditions update
 * 
 *    Rev 1.4   Jul 16 1999 09:20:56   YINGZ
 * change ext
 * 
 *    Rev 1.3   Jul 15 1999 16:51:18   YINGZ
 * prevent show non numeric in tel and ext when first opened
 * 
 *    Rev 1.2   Jul 14 1999 17:22:06   HSUCHIN
 * stored caller name and phone into global
 * 
 *    Rev 1.1   Jul 08 1999 10:05:20   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
