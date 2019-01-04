//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial.
//
//******************************************************************************
//
// ^FILE   : ReportDlg.cpp
// ^AUTHOR : 
// ^DATE   : Nov 21, 2002
//
// ^CLASS    : ReportDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef ReportDlg_H
   #include "ReportDlg.h"
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#ifndef DSTCCSI_H
   #include <ifastcsi\ifastcsi.h>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#include <ifastbp\reportprocessincludes.h>
#include <ifastbp\amsmstprocessincludes.h>
#include <ifastbp\AMSHypoAllocProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\mgmtcooptions.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_REPORT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_GLOBAL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_HYPO_ALLOC;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ReportDlg > dlgCreator( CMD_GUI_REPORT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ReportDlg" );
   const I_CHAR * const LV_REPORT_LIST          = I_( "ReportList" );   
   const I_CHAR * const BROKER_CODE_PARAM       = I_( "BrokerCode" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const REPEAT                  = I_( "R" );
   const I_CHAR * const REBALANCE               = I_( "RB" );
   const I_CHAR * const TARGET_ASSET_MIX        = I_( "RO" );
   const I_CHAR * const AMS_REBALANCE			= I_("IFAST.AMSREBAL");
   const I_CHAR * const AMS_HYPOCALC_REBALANCE  = I_("IFAST.AMSHYPOCALCREBAL");
   const UINT REPORT_CRITERIA = 1;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFTextFieldId IsEnabledBtnAlloc;
}

//******************************************************************************
// Constructor
//******************************************************************************
ReportDlg::ReportDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ReportDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT( ReportDlg )
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************
ReportDlg::~ReportDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void ReportDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( ReportDlg )
   DDX_Control(pDX, IDC_RB_RUN_NOW, m_rb_run_now);
   DDX_Control(pDX, IDC_RB_SCHEDULE, m_rb_schedule);
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( ReportDlg, BaseMainDlg )
//{{AFX_MSG_MAP( ReportDlg )
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DELETE, OnBtnDel )
ON_BN_CLICKED( IDC_RB_RUN_NOW, OnRbRunNow )
ON_BN_CLICKED( IDC_RB_SCHEDULE, OnRbSchedule )
ON_BN_CLICKED( IDC_BTN_ALLOC, OnBtnAlloc )
ON_CBN_SELCHANGE ( IDC_CMB_REPORT_NAME, OnSelchangeRptName )
ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
ON_MESSAGE( UM_OPENAMSCODESEARCH, OpenAMSMstrListDlg )
ON_MESSAGE( WM_LAUNCH_IDENT_ACC,OpenIdentifyAccountsDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL ReportDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void ReportDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   addControls( );
   OnRbRunNow();  
   activeAllocation( false );
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY ReportDlg::doInit()
{
   return ( NO_CONDITION );
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void ReportDlg::addControls( )
{

   AddControl( CTRL_COMBO,  IDC_CMB_REPORT_NAME, IFASTBP_PROC::REPORT_COMMON_INFO, ifds::ReportName, CTRLFLAG_INITCOMBO_BY_SUB_LIST, REPORT_CRITERIA );
   AddControl( CTRL_COMBO,  IDC_CMB_REPORT_MODE, IFASTBP_PROC::REPORT_COMMON_INFO, ifds::ReportMode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, REPORT_CRITERIA );
   AddControl( CTRL_COMBO,  IDC_CMB_REPORT_TYPE, IFASTBP_PROC::REPORT_COMMON_INFO, ifds::ReportType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, REPORT_CRITERIA );
   AddControl( CTRL_DATE,  IDC_DTP_RUN_DATE, IFASTBP_PROC::REPORT_COMMON_INFO, ifds::RunOnDate, CTRLFLAG_DEFAULT, REPORT_CRITERIA );
   AddControl( CTRL_EDIT,  IDC_EDT_RUN_TIME, IFASTBP_PROC::REPORT_COMMON_INFO, ifds::RunOnTime, CTRLFLAG_DEFAULT, REPORT_CRITERIA );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_RUN_TIME ) )->SetAllowedChars( I_("0123456789:") );
   AddControl( CTRL_STATIC,  IDC_STC_TIMEZONE, IFASTBP_PROC::REPORT_COMMON_INFO, ifds::TimeZone, CTRLFLAG_DEFAULT, REPORT_CRITERIA );

   AddListControl( CLASSNAME, IDC_LV_CRITERIA, LV_REPORT_LIST, ifds::ReportCriteriaHeadingSet, 
                   IFASTBP_PROC::REPORT_CRITERIA_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD);
   
   AddControl( CTRL_COMBO,  IDC_CMB_CRITERIA_TYPE, IFASTBP_PROC::REPORT_CRITERIA_LIST, ifds::CriteriaType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CRITERIA );
   AddControl( CTRL_COMBO,  IDC_CMB_INCLUDE, IFASTBP_PROC::REPORT_CRITERIA_LIST, ifds::IncludeExclude, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_CRITERIA );
   AddControl( CTRL_STATIC,  IDC_STC_DESCRIPTION, IFASTBP_PROC::REPORT_CRITERIA_LIST, ifds::Description, CTRLFLAG_DEFAULT, IDC_LV_CRITERIA );
   
   AddControl( CTRL_EDIT,  IDC_EDT_CRITERIA_VALUE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   AddControl( CTRL_COMBO,  IDC_CMB_CRITERIA_VALUE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_INITCOMBO_BY_SUB_LIST, 0 );
   AddControl( CTRL_DATE,  IDC_DTP_CRITERIA_VALUE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   showCriteriaValue ( IDC_EDT_CRITERIA_VALUE );   
   _lastCriteriaValueControl = IDC_EDT_CRITERIA_VALUE;

   ConnectControlToData(IDC_CMB_REPORT_NAME, true);
   LoadControl(IDC_CMB_REPORT_NAME);
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool ReportDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand )
{
    DString dstrCommand(szOriginalCommand);
	if( dstrCommand == I_("AllocBtn") )
	{
		DString dstrIsEnabledBtnAlloc;
		getParent()->getField(this,IFASTBP_PROC::REPORT_CRITERIA_LIST, ifds::IsEnabledBtnAlloc, dstrIsEnabledBtnAlloc);
		activeAllocation((dstrIsEnabledBtnAlloc == I_("Y") ? true : false));
	}
   return(true);
}

//******************************************************************************
// Adds new critera to list
//******************************************************************************
void ReportDlg::OnBtnAdd ( )
{
   AddToListControl( IDC_LV_CRITERIA );
}

//******************************************************************************
// Deletes criteria from list.
//******************************************************************************
void ReportDlg::OnBtnDel  ( )
{
   DeleteFromListControl( IDC_LV_CRITERIA );
}

//******************************************************************************
// Open dialog for override allocation.
//******************************************************************************
void ReportDlg::OnBtnAlloc ( )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAlloc" ) );
	CWaitCursor wait;
	E_COMMANDRETURN eRtn;
	bool bModal = true;  

	try
	{
		DString dstrAmsCode, dstrAccountNum, dstrEffectiveDate;

	
		getParent()->getField(this,IFASTBP_PROC::REPORT_CRITERIA_LIST,CRITERIA_VAL::AMSCode, dstrAmsCode,false );
		getParent()->getField(this,IFASTBP_PROC::REPORT_CRITERIA_LIST,CRITERIA_VAL::AccountNum, dstrAccountNum,false );
		getParent()->getField(this,IFASTBP_PROC::REPORT_CRITERIA_LIST,CRITERIA_VAL::EffectiveDate, dstrEffectiveDate,false );
		
		setParameter( AMS_HYPO_ALLOC_Para::AMS_CODE, dstrAmsCode.strip().upperCase() );
		setParameter( AMS_HYPO_ALLOC_Para::AMS_TYPE, I_("RB") );
		setParameter( AMS_HYPO_ALLOC_Para::EFFECTIVE_DATE, dstrEffectiveDate );
		setParameter( AMS_HYPO_ALLOC_Para::ACCOUNT_NUM, dstrAccountNum );

		eRtn = invokeCommand(getParent(), CMD_BPROC_AMS_HYPO_ALLOC, PROC_SUPPORT, true, NULL);
		if( eRtn != CMD_CANCEL )
		{
		
		}
	}
	catch( ConditionException &ce )
	{
		ConditionMessageBox( ce );
	}
	catch( ... )
	{
		DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
	}
}

void ReportDlg::OnSelchangeRptName()
{
   LoadListControl ( IDC_LV_CRITERIA );
   ConnectControlsToData (REPORT_CRITERIA);
   LoadControls(REPORT_CRITERIA);
}

//******************************************************************************

BOOL ReportDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus()== GetDlgItem( IDC_EDT_CRITERIA_VALUE) ) {
         DString dstrCriteriaType;
         getParent()->getField ( this, IFASTBP_PROC::REPORT_CRITERIA_LIST, ifds::CriteriaType, dstrCriteriaType, false );
         const BFFieldId& fieldId = BFFieldId::getId( dstrCriteriaType );
         if ( fieldId == ifds::BrokerCode ) {
            PostMessage( UM_OPENBROKERLISTDLG );
         } else if ( fieldId == ifds::AMSCode ) {
            PostMessage ( UM_OPENAMSCODESEARCH );
         }  else if ( fieldId == ifds::AccountNum ) {
            PostMessage ( WM_LAUNCH_IDENT_ACC );
         }

      } else if( GetFocus()== GetDlgItem( IDC_EDT_CRITERIA_VALUE) ) {
            PostMessage( UM_OPENBROKERLISTDLG );
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}



//****************************************************************************** 

LRESULT ReportDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode;

      GetControlText( IDC_EDT_CRITERIA_VALUE, dstrBrokerCode );
      setParameter( BROKER_CODE_PARAM, dstrBrokerCode );
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString dstrBrokerCode;

               getParameter( BROKER_CODE_PARAM, dstrBrokerCode );
               if( !dstrBrokerCode.empty() )
               {
                  bool bSuccess = SetControlText( IDC_EDT_CRITERIA_VALUE, dstrBrokerCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BROKER ));
                  if( !bSuccess && pBC )
                     pBC->Load();
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(0);
}

//****************************************************************************** 

void ReportDlg::ControlUpdated(UINT controlID, const DString &dstrValue)
{
   switch( controlID )
   {
      case IDC_CMB_CRITERIA_TYPE:
         {
            ClearControl ( _lastCriteriaValueControl );
            ConnectControlToData ( _lastCriteriaValueControl, false );
            setupCriteriaValueControl( dstrValue );
         }
         break;
      case IDC_CMB_REPORT_TYPE :
         {
            if ( dstrValue == NO )
               activateScheduleRadio ( false );
            else 
               activateScheduleRadio ( true );
            static int cursel;
            cursel = GetList( IDC_LV_CRITERIA )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );
            LoadListControl ( IDC_LV_CRITERIA );
            GetList( IDC_LV_CRITERIA )->SetSelection(cursel, true, true);
         }
         break;
	  case IDC_CMB_CRITERIA_VALUE:
	  case IDC_EDT_CRITERIA_VALUE:
		  {
			DString dstrRptName;
			getParent()->getField(this,IFASTBP_PROC::REPORT_COMMON_INFO, ifds::ReportName, dstrRptName, false);
			if ( dstrRptName == AMS_HYPOCALC_REBALANCE )
				getParent()->send(this, I_("CriteriaValidate"));
		  }
		  break;
   }
}

//****************************************************************************** 

void ReportDlg::activeAllocation ( bool bActive )
{
	GetDlgItem( IDC_BTN_ALLOC )->EnableWindow( bActive );
}

//******************************************************************************
void ReportDlg::setupCriteriaValueControl( const DString &dstrValue )
{
   DString dstrCriteriaType;
   if ( dstrValue == NULL_STRING ) {
      showCriteriaValue ( IDC_EDT_CRITERIA_VALUE );
      EnableControl ( IDC_EDT_CRITERIA_VALUE, false );
      return;
   }
   const BFFieldId& fieldId = BFFieldId::getId( dstrValue );
   const BFDataFieldProperties* pProps = BFDataFieldProperties::get ( fieldId );   
   switch ( pProps->getType() ) {
      case BFDataFieldProperties::Type::text :
         {
            const BFProperties* ppBFProp = getParent()->getFieldAttributes(this, IFASTBP_PROC::REPORT_CRITERIA_LIST, fieldId );
            DString dstrSub;
            ppBFProp->getSubstituteValues ( dstrSub );
            if ( dstrSub != NULL_STRING ) {
               //load combo
               loadCriteriaValue ( IDC_CMB_CRITERIA_VALUE );
            } else { 
               //Allow all characters to be entered.
               dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_CRITERIA_VALUE ) )->SetAllowedChars( I_("") );
               loadCriteriaValue ( IDC_EDT_CRITERIA_VALUE );
            }
         }
         break;
      case BFDataFieldProperties::Type::time :
         {
            //load text with input of 0-9 and :
            loadCriteriaValue ( IDC_EDT_CRITERIA_VALUE );
            dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_CRITERIA_VALUE ) )->SetAllowedChars( I_("0123456789:") );
         }
         break;
      case BFDataFieldProperties::Type::date :
         {
            // load dtp
            loadCriteriaValue ( IDC_DTP_CRITERIA_VALUE );
         }
         break;
      case BFDataFieldProperties::Type::decimal :
      case BFDataFieldProperties::Type::bigdecimal :
         {
            // load edit control with input of 0-9 and .
            loadCriteriaValue ( IDC_EDT_CRITERIA_VALUE );
            dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_CRITERIA_VALUE ) )->SetAllowedChars( I_("0123456789.") );
         }
         break;
      case BFDataFieldProperties::Type::integer :         
      case BFDataFieldProperties::Type::numeric :
         {
            // load edit control with input of 0-9
            loadCriteriaValue ( IDC_EDT_CRITERIA_VALUE );
            dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_CRITERIA_VALUE ) )->SetAllowedChars( I_("0123456789") );
         }
         break;
   }   
}

//****************************************************************************** 

void ReportDlg::activateScheduleRadio ( bool bActivate )
{
   GetDlgItem ( IDC_RB_SCHEDULE )->EnableWindow ( bActivate );
   OnRbRunNow ();
}

//****************************************************************************** 

void ReportDlg::activateSchedule ( bool bActivate )
{
   EnableControl ( IDC_DTP_RUN_DATE, bActivate );
   EnableControl ( IDC_EDT_RUN_TIME, bActivate );
}

//****************************************************************************** 

void ReportDlg::showCriteriaValue ( UINT controlID )
{
   GetDlgItem ( IDC_EDT_CRITERIA_VALUE )->ShowWindow( controlID == IDC_EDT_CRITERIA_VALUE ? SW_SHOW : SW_HIDE );
   EnableControl ( IDC_EDT_CRITERIA_VALUE, controlID == IDC_EDT_CRITERIA_VALUE );
   GetDlgItem ( IDC_DTP_CRITERIA_VALUE )->ShowWindow( controlID == IDC_DTP_CRITERIA_VALUE ? SW_SHOW : SW_HIDE );   
   GetDlgItem ( IDC_CMB_CRITERIA_VALUE )->ShowWindow( controlID == IDC_CMB_CRITERIA_VALUE ? SW_SHOW : SW_HIDE );   
}

//****************************************************************************** 

void ReportDlg::loadCriteriaValue ( UINT controlID )
{
   showCriteriaValue ( controlID );
   DString dstrCriteriaType;
   getParent()->getField(this, IFASTBP_PROC::REPORT_CRITERIA_LIST, ifds::CriteriaType, dstrCriteriaType, false);   
   const BFFieldId& fieldId = BFFieldId::getId( dstrCriteriaType );         
   ReInitControl ( controlID, IFASTBP_PROC::REPORT_CRITERIA_LIST, fieldId );   
   ConnectControlToData ( controlID, true );   
   LoadControl ( controlID );
   _lastCriteriaValueControl = controlID;
}

//****************************************************************************** 

void ReportDlg::OnRbRunNow ( )
{
   m_rb_run_now.SetCheck(1);
   m_rb_schedule.SetCheck(0);
   activateSchedule ( false );
   getParent()->setField( this, IFASTBP_PROC::REPORT_COMMON_INFO, ifds::ScheduleJob, NO );   
   LoadControl ( IDC_EDT_RUN_TIME );
}

//****************************************************************************** 

void ReportDlg::OnRbSchedule ( )
{
   m_rb_run_now.SetCheck(0);
   m_rb_schedule.SetCheck(1);
   activateSchedule ( true );
   getParent()->setField( this, IFASTBP_PROC::REPORT_COMMON_INFO, ifds::ScheduleJob, YES );   
}

//************************************************************************************
void ReportDlg::DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem )
{
   if ( listControlID == IDC_LV_CRITERIA ) {
      DString dstrRecordType;
      getParent()->getField(this, IFASTBP_PROC::REPORT_CRITERIA_LIST, ifds::RecordType, dstrRecordType, false);
	  GetDlgItem ( IDC_BTN_DELETE )->EnableWindow( dstrRecordType == REPEAT );

	  DString dstrRptName;
	  getParent()->getField(this,IFASTBP_PROC::REPORT_COMMON_INFO, ifds::ReportName, dstrRptName, false);
	  if ( dstrRptName == AMS_HYPOCALC_REBALANCE )
		  getParent()->send(this, I_("CriteriaValidate"));
   }
}

//****************************************************************************** 
LRESULT ReportDlg::OpenAMSMstrListDlg( WPARAM, LPARAM )
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenAMSMstrListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrAMSCode;

      GetControlText( IDC_EDT_CRITERIA_VALUE, dstrAMSCode );
      // we'll cheat and use the AMS_DETAIL as the from screen
      setParameter( AMS_Para::FROM_SCR, AMS_Para::AMS_DETAIL );
      setParameter( AMS_Para::AMS_CODE, dstrAMSCode );
      DString dstrClientAMSType;
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      pDSTCWorkSession->getMgmtCoOptions()->getField(ifds::ClientAMSType, dstrClientAMSType, BF::HOST, false);
	   dstrClientAMSType.strip().upperCase();

      if( -1 != dstrClientAMSType.find(REBALANCE) ){	
		   setParameter( AMS_Para::AMS_TYPE, REBALANCE );
      } else if( -1 != dstrClientAMSType.find(TARGET_ASSET_MIX ) ){         
         setParameter( AMS_Para::AMS_TYPE, TARGET_ASSET_MIX );
      } else { // else default to Rebalance
         setParameter( AMS_Para::AMS_TYPE, REBALANCE );
      }
      
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_AMS_GLOBAL, PROC_SUPPORT, true, NULL );
      
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString dstrAMSCode;

               getParameter( AMS_Para::AMS_CODE, dstrAMSCode );
               if( !dstrAMSCode.empty() )
               {
                  bool bSuccess = SetControlText( IDC_EDT_CRITERIA_VALUE, dstrAMSCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_CRITERIA_VALUE ));
                  if( !bSuccess && pBC )
                     pBC->Load();
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(0);
}

LRESULT ReportDlg::OpenIdentifyAccountsDlg( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,CLASSNAME,I_( "OpenIdentifyAccountsDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   //don't allow user to open identify account unless they cleared the account number
   CString strAccNum;
  
   CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(IDC_EDT_CRITERIA_VALUE));
   pEdit->GetWindowText(strAccNum);

   DString dstAcctNum = NULL_STRING;
   dstAcctNum = (LPCTSTR) strAccNum;
   dstAcctNum.strip().stripLeading('0');
   if( dstAcctNum != NULL_STRING )
      return(0);

   bool bRetVal = false;
   BaseControl *pBC = NULL;
   try
   {
      eRtn = invokeCommand( getParent(), CMD_BPROC_IDENT_ACC, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrAccountNum = NULL_STRING;
               getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum );
               dstAcctNum.strip();
               bRetVal = SetControlText( IDC_EDT_CRITERIA_VALUE, dstrAccountNum );
               pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_CRITERIA_VALUE ));
               if( pBC && pBC->IsToolTipVisible() )
                  pBC->ToggleToolTip();

               if( !bRetVal )
               {

                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_CRITERIA_VALUE ));
                  if( pBC )
                  {
                     if( pBC->IsToolTipVisible() )
                        pBC->ToggleToolTip();

                     pBC->Load();
                  }
               }
               clearParameters( );
            }
            break;
         case CMD_CANCEL:
            break;
         default:
            //Displayerror
            ConditionMessageBox( FRAMEBELOW( ),GETHIGHESTSEVERITY( ) );
            break;
      }
   }
   catch( ConditionException&ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return(0);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ReportDlg.cpp-arc  $
// 
//    Rev 1.8   14 May 2010 18:01:46   smithdav
// Add BFBigDecimal field type as an improvement to the double backed BFDecimal.
// 
//    Rev 1.7   Sep 15 2005 15:14:48   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.6   Sep 12 2003 11:45:12   HSUCHIN
// PTS 10018530 - The AMS Type was default to RB which did not work for client who has only RO under AMS Type defined in the generic control ClientAMSType.
// 
//    Rev 1.5   Jun 24 2003 09:34:24   HSUCHIN
// PTS 10018530 - Bug fix to AMS Code not updating.
// 
//    Rev 1.4   Mar 21 2003 18:39:48   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Feb 02 2003 13:38:38   HSUCHIN
// bug fix for ams code where edit control do not allow characters
// 
//    Rev 1.2   Dec 08 2002 21:57:46   HSUCHIN
// changed so that report type changes will refresh criteria list
// 
//    Rev 1.1   Nov 29 2002 13:16:50   HSUCHIN
// added account/ams search and a bug fix for loading controls
// 
//    Rev 1.0   Nov 27 2002 11:56:48   HSUCHIN
// Initial Revision
 */


