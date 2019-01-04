//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AMSAcctLvlDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : AMSAcctLvlDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the AMSAcctLvl dialog
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcfuncs.h>
#include <uibase\DSTComboBox.h>
#include <uibase\dstbutton.h>

///#include "dse_dstcglob_vw.hpp"
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include "AMSAcctLvldlg.h"
#include <ifastbp\amsmstprocessincludes.h>
#include <ifastbp\AMSAcctLvlprocessincludes.h>
#include <ifastbp\fundclassprocessincludes.h>
#include <bfproc\abstractprocess.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include <assert.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AMSACCTLVL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_GLOBAL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_ASSET_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_DELTA_ALLOC;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AMSAcctLvlDlg > dlgCreator( CMD_GUI_AMSACCTLVL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME          = I_( "AMSAcctLvlDlg" );
   const I_CHAR * const LV_AMSAcctLvl      = I_( "AMSAcctLvl" );
   const I_CHAR * const LV_AMSAcctLvlAlloc = I_( "AMSAcctLvlAlloc" );
   const I_CHAR * const YES                = I_( "Y" );
   const I_CHAR * const CALLER             = I_( "Caller" );
   const I_CHAR * const MarketValueWeight  = I_("M");
   const I_CHAR * const ACTIVE             = I_("1");
}

namespace PARAMETER
{
   const I_CHAR * const FUND_CODE     = I_( "FundCode" );    // Used for F4-Fund Search Dialog
   const I_CHAR * const FUND_NUMBER   = I_( "FundNumber" );  // Used for F4-Fund Search Dialog
   const I_CHAR * const CLASS_CODE    = I_( "ClassCode" );   // Used for F4-Fund Search Dialog
   const I_CHAR * const AMS_CODE      = I_( "AMSCode" );     // Used for passing AMSCode to AMSCodeSearch
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_DETAILS;
   extern CLASS_IMPORT I_CHAR * const AMS_ASSET;
   extern CLASS_IMPORT I_CHAR * const AMS_REBAL_REQ_ON_DEMAND;
   extern CLASS_IMPORT I_CHAR * const AMS_ACCT_LVL;   
}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId    AMSFundAllocHeading;  // Column Heading field
   extern CLASS_IMPORT const BFTextFieldId    ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId    FundCode;
   extern CLASS_IMPORT const BFTextFieldId    ClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId    Rebalance;
   extern CLASS_IMPORT const BFTextFieldId    UpdatePACSWP;
   extern CLASS_IMPORT const BFTextFieldId    Currency;
   extern CLASS_IMPORT const BFDecimalFieldId ThresholdPrcnt;
   extern CLASS_IMPORT const BFTextFieldId    AMSCodeBuffer;
//   extern CLASS_IMPORT const BFTextFieldId    AMSCurrency;
//   extern CLASS_IMPORT const BFDecimalFieldId RebalPrcnt;
   extern CLASS_IMPORT const BFTextFieldId RebalDateFormat;
   extern CLASS_IMPORT const BFTextFieldId AMSRebalPending;
   extern CLASS_IMPORT const BFDateFieldId ActualRebalanceDate;
   extern CLASS_IMPORT const BFTextFieldId AMSRebReqMode;
}


namespace AMS_DELTA_ALLOC_Para
{
	const I_CHAR * const AMS_CODE	    = I_("AMSCode");
	const I_CHAR * const AMS_TYPE	    = I_("AMSType");
	const I_CHAR * const AMS_EFFECTIVE_DATE = I_("EffectiveDate");
	const I_CHAR * const ACCOUNT_NUM    = I_("AccountNum");
	const I_CHAR * const AMS_REC_ID     = I_("AMSRecId");
	const I_CHAR * const AMS_SEARCH_DATE = I_("AMSSearchDate");
	const I_CHAR * const AMS_SEARCH_CODE = I_("AMSSearchCode");
}

//******************************************************************************
AMSAcctLvlDlg::AMSAcctLvlDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AMSAcctLvlDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( 0 )
, m_bAMSTypeReadOnly( false )
, m_bAMSAcctLvlListSelectionInProgress (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(AMSAcctLvlDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
AMSAcctLvlDlg::~AMSAcctLvlDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
void AMSAcctLvlDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AMSAcctLvlDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(AMSAcctLvlDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AMSAcctLvlDlg)
ON_BN_CLICKED( IDC_BTN_AMS_ADD, OnBtnAddAms )
ON_BN_CLICKED( IDC_BTN_AMS_DEL, OnBtnDelAms )
ON_BN_CLICKED( IDC_BTN_ADD_FUND_ALLOC, OnBtnAddAlloc )
ON_BN_CLICKED( IDC_BTN_DELETE_FUND_ALLOC, OnBtnDelAlloc )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED( IDC_BTN_HISTORICAL,  OnBtnHistorical )
ON_BN_CLICKED( IDC_BTN_ADM_DATES,  OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_AMS_ASSET_INFO,  OnBtnAmsAssetInfo )
ON_BN_CLICKED(IDC_CHECK_FREQUENCY_OVERRIDE, OnFreqOverrideCheck)
ON_BN_CLICKED( IDC_BTN_DELTA, OnBtnDeltaAlloc)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_MESSAGE( UM_OPENAMSCODESEARCH, OpenAMSMstrListDlg )
ON_CBN_KILLFOCUS( IDC_CMB_AMSTYPE, OnKillfocusCmbAMSType )
ON_EN_KILLFOCUS( IDC_EDT_AMS_CODE, OnKillfocusEdtAMSCode )
ON_CBN_SELCHANGE(IDC_CMB_TARGET_MIX_OPT, OnSelchangeTargetMixOpt)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AMSAcctLvlDlg message handlers

BOOL AMSAcctLvlDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   DisplayCaption();

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void AMSAcctLvlDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );


   SetUserAccesFunctionCode(UAF::AMS_ACCT_LVL);
   
   addBtnAddForPermissionCheck(IDC_BTN_AMS_ADD, IDC_LST_AMSACCTLVL);
   addBtnDeleteForPermissionCheck(IDC_BTN_AMS_DEL, IDC_LST_AMSACCTLVL);
   // AMS Account Level List
   AddListControl( CLASSNAME, 
                   IDC_LST_AMSACCTLVL, 
                   LV_AMSAcctLvl, 
                   ifds::AMSAcctLevelHeading, 
                   IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
                   0, true );

   // AMS Type
   AddControl( CTRL_COMBO, 
               IDC_CMB_AMSTYPE, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::AMSType, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST,
               IDC_LST_AMSACCTLVL);

   // AMS Code
   AddControl( CTRL_EDIT, 
               IDC_EDT_AMS_CODE, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::AMSCode, 
               CTRLFLAG_DEFAULT,
               IDC_LST_AMSACCTLVL );

   DSTEdit* editAMSCode = dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_AMS_CODE ) );
   if( editAMSCode != NULL )
   {
      editAMSCode->SetMaxCharNum( 4 );
   }

   // Frequency Override
   AddControl( CTRL_CHECKBOX, 
               IDC_CHECK_FREQUENCY_OVERRIDE, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::FreqOverride, 
               CTRLFLAG_DEFAULT,
               IDC_LST_AMSACCTLVL );

   // Frequency
   AddControl( CTRL_COMBO, 
               IDC_CMB_FREQUENCY, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::SchedSetupFreqID, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST,
               IDC_LST_AMSACCTLVL );
   
   // Effective Date
   AddControl ( CTRL_DATE, 
                IDC_DTP_EFFECTIVE_DATE, 
                IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
                ifds::Deff, 
                CTRLFLAG_DEFAULT,
                IDC_LST_AMSACCTLVL );

   // Stop Date
   AddControl ( CTRL_DATE, 
                IDC_DTP_STOP_DATE, 
                IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
                ifds::StopDate, 
                CTRLFLAG_DEFAULT,
                IDC_LST_AMSACCTLVL );

   // Last Process Date
   AddControl ( CTRL_DATE, 
                IDC_DTP_LAST_PROCESS_DATE, 
                IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
                ifds::LastProcessDate, 
                CTRLFLAG_DEFAULT,
                IDC_LST_AMSACCTLVL );

   // Next Process Date
   AddControl ( CTRL_DATE, 
                IDC_DTP_NEXT_PROCESS_DATE, 
                IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
                ifds::NextProcessDate, 
                CTRLFLAG_DEFAULT,
                IDC_LST_AMSACCTLVL );

   // Activation Date
   AddControl ( CTRL_DATE, 
                IDC_DTP_ACTIVATION_DATE, 
                IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
                ifds::ActivationDate, 
                CTRLFLAG_DEFAULT,
                IDC_LST_AMSACCTLVL );

   // Status
   AddControl( CTRL_COMBO, 
               IDC_CMB_AMS_STATUS, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::AMSStat, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST,
               IDC_LST_AMSACCTLVL );

   // Flag - Should this account be rebalanced?
   AddControl( CTRL_COMBO, 
               IDC_CMB_REBALANCE, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::Rebalance, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST,
               IDC_LST_AMSACCTLVL  );

   // Flag - Do you want to change PAC/SWP allocations?
   AddControl( CTRL_COMBO, 
               IDC_CMB_CHANGE_PACSWP, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::UpdatePACSWP, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST,
               IDC_LST_AMSACCTLVL  );

   // Threshold and Currency fields
   AddControl( CTRL_EDIT, 
               IDC_EDT_THRESHOLD, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::ThresholdPrcnt, 
               CTRLFLAG_DEFAULT,
               IDC_LST_AMSACCTLVL );

   //Target Mix Option
   AddControl( CTRL_COMBO,
			   IDC_CMB_TARGET_MIX_OPT,
			   IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST,
			   ifds::TargetMixOption,
			   CTRLFLAG_INITCOMBO_BY_SUB_LIST,
			   IDC_LST_AMSACCTLVL );


   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_THRESHOLD))->SetAllowedChars(I_("0123456789."));

   AddControl( CTRL_COMBO, 
               IDC_CMB_CURRENCY, 
               IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
               ifds::Currency, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST,
               IDC_LST_AMSACCTLVL );

   // Fund Allocations List
   AddListControl( CLASSNAME, IDC_LV_ALLOCATION, LV_AMSAcctLvlAlloc, ifds::AMSFundAllocHeading, BF::NullContainerId, 0, true );

   // Fund Details
   AddControl( CTRL_EDIT, IDC_EDT_FUND_NUMBER, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
   AddControl( CTRL_EDIT, IDC_EDT_FUND, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
   AddControl( CTRL_EDIT, IDC_EDT_CLASS, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
   AddControl( CTRL_EDIT, IDC_EDT_FUND_PERCENT, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );

   AddControl( CTRL_STATIC, IDC_TXT_FUND_TOTAL_PRC_VAL, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT );
   AddControl( CTRL_STATIC, IDC_STC_DESCRIPTION, IFASTBP_PROC::AMS_MASTER_LIST, ifds::EnglishName, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
//   AddControl( CTRL_STATIC, IDC_STC_DESCRIPTION, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_NOT_UPDATABLE );

   CWaitCursor wait;

//   ConnectControlToData( IDC_STC_DESCRIPTION, true, false );
//   LoadControl( IDC_STC_DESCRIPTION );

   LoadListControl (IDC_LST_AMSACCTLVL);


    // Status field should be available for all users. It is used to stop rebalancing only
 /*  GetDlgItem( IDC_CMB_AMS_STATUS )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_TXT_STATUS) ->ShowWindow( SW_HIDE );
   DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   if ( NULL != pDSTWorkSession ) {
      DString companyCode;
      pDSTWorkSession->getOption( ifds::CompanyCode, companyCode, getDataGroupId(), false );
      companyCode = companyCode.upperCase();
      if ( companyCode == I_("AIM") || companyCode == I_("ATS") )
      {
         GetDlgItem( IDC_CMB_AMS_STATUS )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_TXT_STATUS) ->ShowWindow( SW_SHOW );
      }
   }*/



   DisplayAMSCodeRelatedControls();
   DisplayAMSTypeRelatedControls();
   RefreshFreq();

   DString dstrAcctStatus;
   getParent()->getField(this,IFASTBP_PROC::MFACCOUNT_CBO,ifds::AcctStatus,dstrAcctStatus);
   if(dstrAcctStatus != I_("Active"))
   {
      GetDlgItem( IDC_BTN_AMS_ADD )->EnableWindow( FALSE );
   }

   DSTListCtrl *rpList = GetList( IDC_LST_AMSACCTLVL );	
   bool bIsDummy = getParentProcess()->isCurrentListItemDummy( this, rpList->getContainerId() );
   
   if (m_Caller == I_("FromAWD") && !bIsDummy)
   	   PostMessage (WM_COMMAND, IDC_BTN_AMS_ADD);  	

   //IN2818924 - DSK_AMS Validation for CDIC
   bool bSet = getFundLimitedByBankuptcy();
   if(bSet)
   {
      doDisableBankruptcyRelatedControls(!bSet);
   }

}

//******************************************************************************
bool AMSAcctLvlDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand )
{
   DisplayCaption();

   DString dstrCode;
   GetControlText( IDC_EDT_AMS_CODE, dstrCode );
   DisplayAmsTypeSensitiveControls( dstrCode );
   RefreshFreq();
   //IN2818924 - DSK_AMS Validation for CDIC
   bool bSet = getFundLimitedByBankuptcy();
   if(bSet)
   {
      doDisableBankruptcyRelatedControls(!bSet);
   }
 
   return( true );
}

//******************************************************************************
void AMSAcctLvlDlg::DoPreListItemChanged ( UINT listControlID,
                                           const DString &strKey,
                                           bool bIsNewItem,
                                           bool bIsDummyItem)
{
   switch (listControlID)
   {
      case IDC_LST_AMSACCTLVL:
         {
            m_bAMSAcctLvlListSelectionInProgress = true;
            break;
         }
      default:
         break;
   }
}

//************************************************************************************
void AMSAcctLvlDlg::DoListItemChanged( UINT listControlID,
                                       const DString &strKey,
                                       bool bIsNewItem ,
                                       bool bIsDummyItem)
{

   if (listControlID == IDC_LST_AMSACCTLVL)
   {
      GetDlgItem (IDC_BTN_HISTORICAL)->EnableWindow( (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );

	  //IN2818924 - DSK_AMS Validation for CDIC
	  bool reset((bIsNewItem || bIsDummyItem) || !getFundLimitedByBankuptcy());

	  doDisableBankruptcyRelatedControls(reset);


      DString lastProcessDate,
         endOfTime;

      //asking this with false should retrieve the date in host format - unformatted
      getParent()->getField (this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::LastProcessDate, lastProcessDate, false);
      
      DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      
      pDSTWorkSession->getDateInHostFormat (endOfTime, DSTCWorkSession::DATE_TYPE::DAY12319999, BF::HOST);
      GetDlgItem (IDC_BTN_AMS_DEL)->EnableWindow  (lastProcessDate.empty() || lastProcessDate == endOfTime);
      RefreshFreq();
      m_bAMSAcctLvlListSelectionInProgress = false;
	    EnableDeltaAllocation();
   }	
}

//*********************************************************************
void AMSAcctLvlDlg::OnBtnAddAms()
{
	AddToListControl( IDC_LST_AMSACCTLVL );
}

//**********************************************************************
void AMSAcctLvlDlg::OnBtnDelAms()
{
  DeleteFromListControl( IDC_LST_AMSACCTLVL ); 
}

//******************************************************************
void AMSAcctLvlDlg::OnFreqOverrideCheck()
{
   RefreshFreq();
}

void AMSAcctLvlDlg::RefreshFreq() 
{
   if (IsCancelInProgress())
      return;

   DSTButton* ueaCheck = 
      dynamic_cast<DSTButton*>(GetControl(IDC_CHECK_FREQUENCY_OVERRIDE));

   if (ueaCheck != NULL)
   {
      getParent()->setField( this, 
                             IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
                             ifds::FreqOverride, 
                             ueaCheck->GetCheck() ? I_("1") : I_("0"), 
                             false );

      LoadControl( IDC_CMB_FREQUENCY );
      //IN2818924 - DSK_AMS Validation for CDIC
      GetDlgItem (IDC_CMB_FREQUENCY)->EnableWindow( ueaCheck->GetCheck() && !getFundLimitedByBankuptcy() );

   }
}

//**********************************************************************************
void AMSAcctLvlDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
}

//**********************************************************************************
void AMSAcctLvlDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, I_("MULTI") );
}

//******************************************************************************
void AMSAcctLvlDlg::OnBtnAmsAssetInfo ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAmsAssetInfo"));
   CWaitCursor wait;   
   DString accountNum;
   
   getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, accountNum);
   DString urlParamsIDI;

   addIDITagValue(urlParamsIDI, I_("AccountNum"), accountNum);
   addIDITagValue(urlParamsIDI, I_("searchType"), I_("fund"));
   addIDITagValue (urlParamsIDI, I_("screen"), I_("AMSAssetInfo")); //DesktopWeb conversion
   
   setParameter( I_("from_screen"), I_("AMSAcctLvlDlg"));
   setParameter( I_("UrlParams"), urlParamsIDI);
   CString cstrAMSAssetInfo;
   cstrAMSAssetInfo.LoadString(TXT_AMS_ASSET_INFO_ACCOUNT_NUMBER);
   setParameter( I_("BrowserTitle"), DString(cstrAMSAssetInfo) + accountNum);

   invokeCommand (getParent(), CMD_BPROC_AMS_ASSET_INFO, PROC_NO_TYPE, true, NULL);
   if (GETHIGHESTSEVERITY () > WARNING)
   {
      // Display error
      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
   }   
}

//******************************************************************************
void AMSAcctLvlDlg::OnBtnAddAlloc () 
{
   AddToListControl( IDC_LV_ALLOCATION );
}

//******************************************************************************
void AMSAcctLvlDlg::OnBtnDelAlloc () 
{
   DeleteFromListControl( IDC_LV_ALLOCATION );
}

//******************************************************************************
void AMSAcctLvlDlg::OnBtnReset() 
{
   ResetListItem( IDC_LST_AMSACCTLVL );

   getParent()->setField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::SchedSetupFreqID, I_(""), false );

   LoadControl( IDC_CMB_FREQUENCY );
//   getParent()->resetCurrentItem( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST);
//   if (m_bUserDefinedAMS)
//      getParent()->reset( this, IFASTBP_PROC::USER_DEFINED_AMS );
//   getParent()->send( this, I_("CLEAR GLOBAL AMS CONTAINER") );
//   getParent()->send( this, I_("CLEAR DEFAULT CONTAINER") );        
   
//   doRefresh( this, NULL_STRING );
}

//******************************************************************************
BOOL AMSAcctLvlDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
   {
      return(TRUE);
   }

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if(   GetFocus() == GetDlgItem( IDC_EDT_FUND ) 
            || GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) 
            || GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
      } else if( GetFocus() == GetDlgItem( IDC_EDT_AMS_CODE ) )
      {
         PostMessage( UM_OPENAMSCODESEARCH );
      }
      return( TRUE );
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************
void AMSAcctLvlDlg::DisplayCaption() 
{
   DString dstrShrNum, dstrAccountNum, dstrEntityName;

   // Get Shareholder Number
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Account Number
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Entity Name
   if ( !dstrAccountNum.empty() ) {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), dstrAccountNum, dstrEntityName);
   }
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
}

//******************************************************************************
LRESULT AMSAcctLvlDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      // Set Account Number
      DString dstrAccountNum;
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum );
      setParameter( FUNDCLASSLIST::ACCT_NUM, dstrAccountNum );

      setParameter( PARAMETER::FUND_CODE, NULL_STRING );
      setParameter( PARAMETER::FUND_NUMBER, NULL_STRING );
      setParameter( PARAMETER::CLASS_CODE, NULL_STRING );
      GetFocus()->GetWindowText( cstrValue );
      DString dstrValue( cstrValue );
      switch( GetFocus()->GetDlgCtrlID() )
      {
         case IDC_EDT_FUND:
            setParameter( PARAMETER::FUND_CODE, dstrValue );
            break;    
         case IDC_EDT_FUND_NUMBER:
            setParameter( PARAMETER::FUND_NUMBER, dstrValue );
            break;    
         case IDC_EDT_CLASS:
            setParameter( PARAMETER::CLASS_CODE, dstrValue );
            break;    
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( PARAMETER::FUND_CODE, dstrFundCode );
               getParameter ( PARAMETER::CLASS_CODE, dstrClassCode );
               getParameter ( PARAMETER::FUND_NUMBER, dstrFundNumber );

               getParent()->setField( this, IFASTBP_PROC::USER_DEFINED_AMS, ifds::FundCode, dstrFundCode );
               getParent()->setField( this, IFASTBP_PROC::USER_DEFINED_AMS, ifds::ClassCode, dstrClassCode );
               getParent()->setField( this, IFASTBP_PROC::USER_DEFINED_AMS, ifds::ToFundNumber, dstrFundNumber );

               LoadControl( IDC_EDT_FUND );
               LoadControl( IDC_EDT_CLASS );
               LoadControl( IDC_EDT_FUND_NUMBER );
               break;
            }
         case CMD_CANCEL:
            break;
         default:
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
LRESULT AMSAcctLvlDlg::OpenAMSMstrListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenAMSCodeListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      GetFocus()->GetWindowText( cstrValue );
      DString dstrAMSCode( cstrValue );

      // Get AMS Type (will come from AMSType list will have RO or RB
      DString dstrAMSType;
      getParent()->getField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSType, dstrAMSType, false );

      // Pass transaction type (ie. RO, RB) to handle F4
      setParameter( AMS_Para::FROM_SCR, AMS_Para::AMS_DETAIL );
      setParameter( AMS_Para::AMS_CODE, dstrAMSCode );
      setParameter( AMS_Para::AMS_TYPE, dstrAMSType );

      eRtn = invokeCommand( getParent(), CMD_BPROC_AMS_GLOBAL, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {

               getParent()->send( this, I_("CLEAR GLOBAL AMS CONTAINER") );
               getParent()->send( this, I_("CLEAR DEFAULT CONTAINER") );


               getParameter ( AMS_Para::AMS_CODE, dstrAMSCode );
               //if( dstrAMSType == I_("RB") )
               //{
                  getParent()->setField( this,IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSCode, dstrAMSCode, false );
               //}
               //else if( dstrAMSType == I_("RO") )
               //{
               //   getParent()->setField( this,IFASTBP_PROC::MFACCOUNT_CBO, ifds::AMSROCode, dstrAMSCode, false );
               //}
               SetControlText( IDC_EDT_AMS_CODE, dstrAMSCode );
//               LoadControl( IDC_EDT_AMS_CODE );
               break;
            }
         case CMD_CANCEL:
            break;
         default:
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
void AMSAcctLvlDlg::ControlUpdated (UINT controlID, 
                                    const DString &strValue)
{
   if (controlID == IDC_CMB_AMSTYPE)
   {

      getParent()->send (this, I_("CLEAR GLOBAL AMS CONTAINER"));
      getParent()->send (this, I_("CLEAR DEFAULT CONTAINER"));
      DString dstrAMSCode;

      getParent()->getField (this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSCode, dstrAMSCode);
      DisplayAMSTypeRelatedControls ();
      ConnectControlToData (IDC_STC_DESCRIPTION, true);
      LoadControl (IDC_STC_DESCRIPTION);
   }
   else if (controlID == IDC_EDT_AMS_CODE)
   {
      DString dstrAMSCode (strValue );
      dstrAMSCode.strip().upperCase();
      DisplayAMSCodeRelatedControls();
      
      //getParent()->setField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSCodeBuffer, dstrAMSCode );

      //IN2818924 - DSK_AMS Validation for CDIC
      bool bSet = getFundLimitedByBankuptcy();
      if(bSet)
      {
         doDisableBankruptcyRelatedControls(!bSet);
      }
   }	
   else if (controlID == IDC_EDT_FUND_PERCENT) 
   {
      LoadControl (IDC_TXT_FUND_TOTAL_PRC_VAL);
   }
   else if (controlID == IDC_DTP_EFFECTIVE_DATE)
   {
//clear the allocations list if user modifies the effective date.
//only do this if the AMS list selection is not in progress - 
      if (!m_bAMSAcctLvlListSelectionInProgress)
      {
         getParent()->send( this, I_("CLEAR DEFAULT CONTAINER") );
         LoadListControl (IDC_LV_ALLOCATION);
      }
   }
   else if (controlID == IDC_CMB_FREQUENCY)
   {
      DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      if ( NULL != pDSTWorkSession ) {
         DString dstrRebalDateFormat;
         pDSTWorkSession->getOption( ifds::RebalDateFormat, dstrRebalDateFormat, getDataGroupId(), false );
         dstrRebalDateFormat.strip().upperCase();
         if (dstrRebalDateFormat == I_("1")){
            ReInitControl( IDC_DTP_NEXT_PROCESS_DATE, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::ActualRebalanceDate, -1);
         }
         else
         {
            ReInitControl( IDC_DTP_NEXT_PROCESS_DATE, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::NextProcessDate, -1);
         }
      }
      LoadControl(IDC_DTP_NEXT_PROCESS_DATE);
   }
}

//******************************************************************************
// EnableAMSControls
void AMSAcctLvlDlg::DisplayAmsTypeSensitiveControls( const DString &dstrValue )
{
   DString dstrAMSType;
   DString dstrCommonCurrency, dstrDispRBLSysThrshld;

   m_bUserDefinedAMS = false;

   getParent()->getField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSType, dstrAMSType, false );
   getParent()->getField(this, ifds::CommonCurrency, dstrCommonCurrency, false);
   dstrCommonCurrency.strip().upperCase();
   getParent()->getField( this, ifds::DispRBLSysThrshld, dstrDispRBLSysThrshld, false);
   dstrDispRBLSysThrshld.strip().upperCase();


   DString dstrDefaultAlloc = NULL_STRING;
   DString dstrGlobalAlloc = NULL_STRING;
   try 
   {

      DString dstrGbAMSCode,dstrEffectiveDate;
      getParent()->getField(this,IFASTBP_PROC::AMS_MASTER_LIST,ifds::AMSCode,dstrGbAMSCode,false);
      getParent()->getField(this,IFASTBP_PROC::AMS_MASTER_LIST,ifds::EffectiveDate,dstrEffectiveDate,false);
      dstrGbAMSCode.strip().upperCase();
      DString 	strKey = dstrGbAMSCode + dstrEffectiveDate ;	
      if ( !dstrValue.empty() )
      {
         getParent()->getField(this, IFASTBP_PROC::AMS_MASTER_LIST, ifds::DefaultAlloc, dstrDefaultAlloc, false);
         getParent()->getField(this, IFASTBP_PROC::AMS_MASTER_LIST, ifds::FundAlloc, dstrGlobalAlloc, false);
      }
   }
   catch(...)
   {
   }

   // Reinitialize Controls
   if( !dstrValue.empty() && dstrDefaultAlloc == I_("Y") )
   {
      m_bUserDefinedAMS = true;
      EnableList( IDC_LV_ALLOCATION, true );
      ReInitListControl( IDC_LV_ALLOCATION, ifds::AMSFundAllocHeading, IFASTBP_PROC::USER_DEFINED_AMS, LV_AMSAcctLvlAlloc );

      //
      // ReInit Detail Controls
      ReInitControl( IDC_EDT_FUND_NUMBER, IFASTBP_PROC::USER_DEFINED_AMS, ifds::ToFundNumber, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_FUND, IFASTBP_PROC::USER_DEFINED_AMS, ifds::FundCode, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_CLASS, IFASTBP_PROC::USER_DEFINED_AMS, ifds::ClassCode, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_FUND_PERCENT, IFASTBP_PROC::USER_DEFINED_AMS, ifds::AllocPercentage, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
      ReInitControl( IDC_TXT_FUND_TOTAL_PRC_VAL, BF::NullContainerId, TOTAL_PERCENTAGE, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );

      ConnectListToData( IDC_LV_ALLOCATION, true );
      ConnectControl( IDC_EDT_FUND_NUMBER, true );
      ConnectControl( IDC_EDT_FUND, true );
      ConnectControl( IDC_EDT_CLASS, true );
      ConnectControl( IDC_EDT_FUND_PERCENT, true );
      ConnectControl( IDC_TXT_FUND_TOTAL_PRC_VAL, true );

      LoadListControl( IDC_LV_ALLOCATION );
      LoadControl( IDC_TXT_FUND_TOTAL_PRC_VAL );

      // Display
      GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( TRUE );
      GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( TRUE );
      EnableControl( IDC_EDT_FUND, true );
      EnableControl( IDC_EDT_CLASS, true );
      EnableControl( IDC_EDT_FUND_NUMBER, true );
      EnableControl( IDC_EDT_FUND_PERCENT, true );

   }
   else if(!dstrValue.empty() && dstrGlobalAlloc == I_("Y") )
   {
      EnableList( IDC_LV_ALLOCATION, true );
      ReInitListControl( IDC_LV_ALLOCATION, ifds::AMSFundAllocHeading, IFASTBP_PROC::GLOBAL_DEFINED_AMS, LV_AMSAcctLvlAlloc );

      // ReInit Detail Controls
      ReInitControl( IDC_EDT_FUND_NUMBER, IFASTBP_PROC::GLOBAL_DEFINED_AMS, ifds::ToFundNumber, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_FUND, IFASTBP_PROC::GLOBAL_DEFINED_AMS, ifds::FundCode, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_CLASS, IFASTBP_PROC::GLOBAL_DEFINED_AMS, ifds::ClassCode, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_FUND_PERCENT, IFASTBP_PROC::GLOBAL_DEFINED_AMS, ifds::AllocPercentage, CTRLFLAG_NOT_UPDATABLE, IDC_LV_ALLOCATION );
      ReInitControl( IDC_TXT_FUND_TOTAL_PRC_VAL, BF::NullContainerId, TOTAL_PERCENTAGE, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );

      ConnectListToData( IDC_LV_ALLOCATION, true );
      ConnectControl( IDC_EDT_FUND_NUMBER, true );
      ConnectControl( IDC_EDT_FUND, true );
      ConnectControl( IDC_EDT_CLASS, true );
      ConnectControl( IDC_EDT_FUND_PERCENT, true );
      ConnectControl( IDC_TXT_FUND_TOTAL_PRC_VAL, true );

      LoadListControl( IDC_LV_ALLOCATION );
      LoadControl( IDC_TXT_FUND_TOTAL_PRC_VAL );

      // Display
      GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( FALSE );
      GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( FALSE );
      EnableControl( IDC_EDT_FUND, false );
      EnableControl( IDC_EDT_CLASS, false );
      EnableControl( IDC_EDT_FUND_NUMBER, false );
      EnableControl( IDC_EDT_FUND_PERCENT, false );
   }
   else {
      // Empty AMS Code
      // ReInit Detail Controls
      ReInitListControl( IDC_LV_ALLOCATION, ifds::AMSFundAllocHeading, BF::NullContainerId, LV_AMSAcctLvlAlloc );
      ReInitControl( IDC_EDT_FUND_NUMBER, BF::NullContainerId, ifds::NullFieldId, -1, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_FUND, BF::NullContainerId, ifds::NullFieldId, -1, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_CLASS, BF::NullContainerId, ifds::NullFieldId, -1, IDC_LV_ALLOCATION );
      ReInitControl( IDC_EDT_FUND_PERCENT, BF::NullContainerId, ifds::NullFieldId, -1, IDC_LV_ALLOCATION );
      ReInitControl( IDC_TXT_FUND_TOTAL_PRC_VAL, BF::NullContainerId, ifds::NullFieldId, -1, IDC_LV_ALLOCATION );

      //
      ConnectListToData( IDC_LV_ALLOCATION, false );
      ConnectControl( IDC_EDT_FUND_NUMBER, false );
      ConnectControl( IDC_EDT_FUND, false );
      ConnectControl( IDC_EDT_CLASS, false );
      ConnectControl( IDC_EDT_FUND_PERCENT, false );
      ConnectControl( IDC_TXT_FUND_TOTAL_PRC_VAL, false );

      // Disable Controls for Empty AMS Code
      GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( FALSE );
      GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( FALSE );
      EnableControl( IDC_EDT_FUND, false );
      EnableControl( IDC_EDT_CLASS, false );
      EnableControl( IDC_EDT_FUND_NUMBER, false );
      EnableControl( IDC_EDT_FUND_PERCENT, false );
   }

   // Flags -- if RB and dstrGlobal || dstrDefault --- only if changed.
   if( dstrAMSType == I_("RB") )
   {
      // Flag - Should this account be rebalanced?
//      ReInitControl( IDC_CMB_REBALANCE, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::Rebalance, -1 );
      // Flag - Do you want to change PAC/SWP allocations?
//      ReInitControl( IDC_CMB_CHANGE_PACSWP, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::UpdatePACSWP, -1 );

//      ConnectControlToData( IDC_CMB_REBALANCE, true, false );
//      ConnectControlToData( IDC_CMB_CHANGE_PACSWP, true, false );
//      LoadControl( IDC_CMB_REBALANCE );
//      LoadControl( IDC_CMB_CHANGE_PACSWP );

      DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      if ( NULL != pDSTWorkSession ) {
         DString dstrRebalDateFormat;
         pDSTWorkSession->getOption( ifds::RebalDateFormat, dstrRebalDateFormat, getDataGroupId(), false );
         dstrRebalDateFormat.strip().upperCase();
         if (dstrRebalDateFormat == I_("1")){
            ReInitControl( IDC_DTP_NEXT_PROCESS_DATE, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::ActualRebalanceDate, -1);
         }
         else
         {
            ReInitControl( IDC_DTP_NEXT_PROCESS_DATE, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::NextProcessDate, -1);
         }
         LoadControl(IDC_DTP_NEXT_PROCESS_DATE);

         //bool bAbletoReqRebOndemand =  pDSTWorkSession->hasReadPermission( UAF::AMS_REBAL_REQ_ON_DEMAND );
         //EnableControl( IDC_CMB_REBALANCE , bAbletoReqRebOndemand );
      }

      EnableControl( IDC_CMB_REBALANCE , !dstrValue.empty() );
      EnableControl( IDC_CMB_CHANGE_PACSWP , !dstrValue.empty() );
   }

   // AMS Type
   if ( dstrAMSType == I_("RO") ) 
   {
      GetDlgItem( IDC_TXT_CURRENCY )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_CURRENCY )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_THRESHOLD )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_EDT_THRESHOLD )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_REBALANCE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_REBALANCE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_CHANGE_PACSWP )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_CHANGE_PACSWP )->ShowWindow( SW_HIDE );
   }
   else 
   {
      int iDisp;
      iDisp = (dstrCommonCurrency == I_("Y")) ? SW_SHOW : SW_HIDE;
      GetDlgItem( IDC_TXT_CURRENCY )->ShowWindow( iDisp );
      GetDlgItem( IDC_CMB_CURRENCY )->ShowWindow( iDisp );

      iDisp = (dstrDispRBLSysThrshld == I_("Y")) ? SW_SHOW : SW_HIDE;
      GetDlgItem( IDC_TXT_THRESHOLD )->ShowWindow( iDisp );
      GetDlgItem( IDC_EDT_THRESHOLD )->ShowWindow( iDisp );

      GetDlgItem( IDC_CMB_REBALANCE )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_TXT_REBALANCE )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_CMB_CHANGE_PACSWP )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_TXT_CHANGE_PACSWP )->ShowWindow( SW_SHOW );
   }

   // Format Columns
   CListCtrl *pDSTListCtrl = GetList( IDC_LV_ALLOCATION );
   if( pDSTListCtrl )
   {
      LVCOLUMN lvcolumn;
      lvcolumn.mask = LVCF_FMT;
      lvcolumn.fmt = LVCFMT_RIGHT;
      BOOL bReturn = pDSTListCtrl->SetColumn( 4, &lvcolumn ); // Percentage field
   }
}

//**********************************************************************************
void AMSAcctLvlDlg::DisplayAMSCodeRelatedControls()
{
   DString dstrDefaultAlloc = NULL_STRING;
   DString dstrGlobalAlloc = NULL_STRING;
   DString dstrAMSCode;
   getParent()->getField(this, IFASTBP_PROC::AMS_MASTER_LIST, ifds::DefaultAlloc, dstrDefaultAlloc, false);
   getParent()->getField(this, IFASTBP_PROC::AMS_MASTER_LIST, ifds::FundAlloc, dstrGlobalAlloc, false);
   getParent()->getField(this, IFASTBP_PROC::AMS_MASTER_LIST, ifds::AMSCode, dstrAMSCode, false);
   dstrAMSCode.strip().upperCase();
   dstrGlobalAlloc.strip().upperCase();
   dstrDefaultAlloc.strip().upperCase();
   if( dstrAMSCode != NULL_STRING )
      //AMSCode is not empty 
   {	
      bool bConnect = false;

      BFContainerId lContainerId,lCurContainerId;
      bool bEnableControl;
      if( dstrDefaultAlloc == YES )
      {
         lCurContainerId = lContainerId = IFASTBP_PROC::USER_DEFINED_AMS;		
         m_bUserDefinedAMS = true;
         bEnableControl = true; 
         bConnect = true;
      }
      else if( dstrGlobalAlloc == YES )
      {		
         lContainerId = IFASTBP_PROC::GLOBAL_DEFINED_AMS;	

         lCurContainerId = IFASTBP_PROC::AMS_MASTER_LIST;

         bEnableControl = false; // user can not change global AMS
         DString dstrDispRBLSysThrshld,dstrCommonCurrency;
         getParent()->getField( this, ifds::DispRBLSysThrshld, dstrDispRBLSysThrshld, false);
         dstrDispRBLSysThrshld.strip().upperCase();
         getParent()->getField(this, ifds::CommonCurrency, dstrCommonCurrency, false);
         dstrCommonCurrency.strip().upperCase();
         LoadControl( IDC_CMB_FREQUENCY );
         bConnect = true;
      }
      if( bConnect )
      {
         EnableList( IDC_LV_ALLOCATION, true );
         ReInitListControl( IDC_LV_ALLOCATION, ifds::AMSFundAllocHeading, lContainerId, LV_AMSAcctLvlAlloc );


         ReInitControl( IDC_EDT_FUND_NUMBER, lContainerId, ifds::ToFundNumber, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
         ReInitControl( IDC_EDT_FUND, lContainerId, ifds::FundCode, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
         ReInitControl( IDC_EDT_CLASS, lContainerId, ifds::ClassCode, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
         ReInitControl( IDC_EDT_FUND_PERCENT, lContainerId, ifds::AllocPercentage, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
         ReInitControl( IDC_TXT_FUND_TOTAL_PRC_VAL, BF::NullContainerId, TOTAL_PERCENTAGE, CTRLFLAG_DEFAULT, IDC_LV_ALLOCATION );
         ConnectListToData( IDC_LV_ALLOCATION, true );
         ConnectControl( IDC_EDT_FUND_NUMBER, true );
         ConnectControl( IDC_EDT_FUND, true );
         ConnectControl( IDC_EDT_CLASS, true );
         ConnectControl( IDC_EDT_FUND_PERCENT, true );
         ConnectControl( IDC_TXT_FUND_TOTAL_PRC_VAL, true );
         LoadListControl( IDC_LV_ALLOCATION );
         LoadControl( IDC_TXT_FUND_TOTAL_PRC_VAL );

         EnableControl( IDC_EDT_FUND, bEnableControl );
         EnableControl( IDC_EDT_CLASS, bEnableControl );
         EnableControl( IDC_EDT_FUND_NUMBER, bEnableControl );
         EnableControl( IDC_EDT_FUND_PERCENT, bEnableControl );
         GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( bEnableControl );
         GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( bEnableControl );

         return;		
      }
   }

   //disconect all controls
   ConnectListToData( IDC_LV_ALLOCATION, false );
   ConnectControl( IDC_EDT_FUND_NUMBER, false );
   ConnectControl( IDC_EDT_FUND, false );
   ConnectControl( IDC_EDT_CLASS, false );
   ConnectControl( IDC_EDT_FUND_PERCENT, false );
   ConnectControl( IDC_TXT_FUND_TOTAL_PRC_VAL, false );
   GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( FALSE );
   GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( FALSE );
   EnableControl( IDC_EDT_FUND, false );
   EnableControl( IDC_EDT_CLASS, false );
   EnableControl( IDC_EDT_FUND_NUMBER, false );
   EnableControl( IDC_EDT_FUND_PERCENT, false );
   CString cstr = _T("");	
   GetDlgItem(IDC_EDT_FUND_NUMBER)->SetWindowText(cstr);
   GetDlgItem(IDC_EDT_FUND			)->SetWindowText(cstr);
   GetDlgItem(IDC_EDT_CLASS		)->SetWindowText(cstr);
   GetDlgItem(IDC_EDT_FUND_PERCENT)->SetWindowText(cstr);
   GetDlgItem(IDC_EDT_THRESHOLD	)->SetWindowText(cstr);
}

//**********************************************************************************
void AMSAcctLvlDlg::DisplayAMSTypeRelatedControls()
{
   DString	dstrAMSType,dstrCommonCurrency,dstrDispRBLSysThrshld;
   getParent()->getField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSType, dstrAMSType, false );
   dstrAMSType.strip().upperCase();

   getParent()->getField( this, ifds::DispRBLSysThrshld, dstrDispRBLSysThrshld, false);
   dstrDispRBLSysThrshld.strip().upperCase();

   getParent()->getField(this, ifds::CommonCurrency, dstrCommonCurrency, false);
   dstrCommonCurrency.strip().upperCase();

   // AMS Type
   if ( dstrAMSType == I_("RO") ) 
   {
      GetDlgItem( IDC_TXT_CURRENCY )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_CURRENCY )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_THRESHOLD )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_EDT_THRESHOLD )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_REBALANCE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_REBALANCE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_CHANGE_PACSWP )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_CHANGE_PACSWP )->ShowWindow( SW_HIDE );

      GetDlgItem( IDC_CHECK_FREQUENCY_OVERRIDE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_FREQUENCY )->ShowWindow( SW_HIDE );
   }
   else 
   {
      int iDisp;
      iDisp = (dstrCommonCurrency == I_("Y")) ? SW_SHOW : SW_HIDE;
      GetDlgItem( IDC_TXT_CURRENCY )->ShowWindow( iDisp );
      GetDlgItem( IDC_CMB_CURRENCY )->ShowWindow( iDisp );

      iDisp = (dstrDispRBLSysThrshld == I_("Y")) ? SW_SHOW : SW_HIDE;
      GetDlgItem( IDC_TXT_THRESHOLD )->ShowWindow( iDisp );
      GetDlgItem( IDC_EDT_THRESHOLD )->ShowWindow( iDisp );

      GetDlgItem( IDC_CMB_REBALANCE )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_TXT_REBALANCE )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_CMB_CHANGE_PACSWP )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_TXT_CHANGE_PACSWP )->ShowWindow( SW_SHOW );


      DString dstrAMSFreqOvrd;
      DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      if ( NULL != pDSTWorkSession )
         pDSTWorkSession->getOption( ifds::AMSFreqOvrd, dstrAMSFreqOvrd, getDataGroupId(), false );

      iDisp = (dstrAMSFreqOvrd == I_("Y")) ? SW_SHOW : SW_HIDE;

      GetDlgItem( IDC_CHECK_FREQUENCY_OVERRIDE )->ShowWindow( iDisp );
      GetDlgItem( IDC_CMB_FREQUENCY )->ShowWindow( iDisp  );

      CButton* ueaCheck = dynamic_cast<CButton*>(GetControl(IDC_CHECK_FREQUENCY_OVERRIDE));
      if (ueaCheck != NULL)
      {
         DString dstrFreqOverride;
         getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::FreqOverride, dstrFreqOverride);
         if ( dstrFreqOverride == I_("1") ) {
            ueaCheck->SetCheck(BST_CHECKED);
         } else {
            ueaCheck->SetCheck(BST_UNCHECKED);
         }
      }

      if ( NULL != pDSTWorkSession ) {
         DString dstrRebalDateFormat;
         pDSTWorkSession->getOption( ifds::RebalDateFormat, dstrRebalDateFormat, getDataGroupId(), false );
         dstrRebalDateFormat.strip().upperCase();
         if (dstrRebalDateFormat == I_("1")){
            ReInitControl( IDC_DTP_NEXT_PROCESS_DATE, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::ActualRebalanceDate, -1);
         }
         else
         {
            ReInitControl( IDC_DTP_NEXT_PROCESS_DATE, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::NextProcessDate, -1);
         }
         LoadControl(IDC_DTP_NEXT_PROCESS_DATE);

         //bool bAbletoReqRebOndemand =  pDSTWorkSession->hasReadPermission( UAF::AMS_REBAL_REQ_ON_DEMAND );
         //EnableControl( IDC_CMB_REBALANCE , bAbletoReqRebOndemand );
      }
   }
}

//*****************************************************************************
SEVERITY AMSAcctLvlDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   getParameter( CALLER, m_Caller );

   return(NO_CONDITION);
}

//******************************************************************************
bool AMSAcctLvlDlg::SetDataFromControl(UINT controlID,
                                      const DString &dstrValue,
                                      bool bFormatted,
                                      SEVERITY &sevRtn,
                                      int index )
{
   bool bReturn = false;
   sevRtn = NO_CONDITION;
   if( controlID == IDC_EDT_AMS_CODE )
   {
      DString dstrAMSType;
      getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSType, dstrAMSType, false);
      //if( dstrAMSType == I_("RB") )
      //{
         sevRtn = getParent()->setField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSCodeBuffer, dstrValue );
      //}
      //else
      //{
         //sevRtn = getParent()->setField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSROCode, dstrValue );
      //}
      if( sevRtn <= WARNING )
      {
         DString dstrAMSCode( dstrValue );
         dstrAMSCode.upperCase().strip();
         getParent()->send( this, I_("CLEAR GLOBAL AMS CONTAINER") );
         getParent()->send( this, I_("CLEAR DEFAULT CONTAINER") );
         // Reinitialize controls
         DisplayAMSCodeRelatedControls();
         ConnectControlToData( IDC_STC_DESCRIPTION, !dstrAMSCode.empty() );

         LoadControl( IDC_STC_DESCRIPTION );
      }

      bReturn = true;
   }
   else if( controlID == IDC_STC_DESCRIPTION )
   {
      bReturn = true;
   }
   
   return( bReturn );
}

//******************************************************************************
void AMSAcctLvlDlg::OnKillfocusCmbAMSType()
{
	if (m_Caller == I_("FromAWD"))
		return;

	RefreshFreq();
}

//******************************************************************************
void AMSAcctLvlDlg::OnKillfocusEdtAMSCode() 
{
   RefreshFreq();
}

//******************************************************************************
bool AMSAcctLvlDlg::GetDataForControl( UINT controlID,
                                           DString &strValueOut,
                                           bool bFormatted,
                                       int index ) const
{
   bool bReturn = false;
   if( controlID == IDC_STC_DESCRIPTION )
   {
      getParent()->getField( this, IFASTBP_PROC::AMS_MASTER_LIST, ifds::EnglishName, strValueOut );
      bReturn = true;
   }

   return bReturn;
}

//******************************************************************************
void AMSAcctLvlDlg::doDisableNonPermButtons ()
{
   GetDlgItem (IDC_BTN_AMS_ASSET_INFO)->EnableWindow( hasReadPermission( UAF::AMS_ASSET ) );
   
   DString endOfTime,lastProcessDate;
   getParent()->getField (this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::LastProcessDate, lastProcessDate, false);
   DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pDSTWorkSession->getDateInHostFormat (endOfTime, DSTCWorkSession::DATE_TYPE::DAY12319999, BF::HOST);

   bool blEnable = false;

   //As soon as rebalancing has taken place (i.e. last schedule date has been stamped), maintaince of the Acct AMS allocation should not be allowed. Winnie, Feb 12, 2008)
   if( lastProcessDate.empty() || lastProcessDate == endOfTime.strip() )
   {
	   //if AMS code is empty disable controls
	   DString dstrAMSCode;
	   getParent()->getField(this, IFASTBP_PROC::AMS_MASTER_LIST, ifds::AMSCode, dstrAMSCode, false);
       if( !dstrAMSCode.strip().empty() )
	   {
		   //only allow modifications of default allocations (not global ones)
		   DString dstrDefaultAlloc;
		   getParent()->getField(this, IFASTBP_PROC::AMS_MASTER_LIST, ifds::DefaultAlloc, dstrDefaultAlloc, false);
		   if( dstrDefaultAlloc.strip().upperCase() == YES )
		   {
              blEnable = true;
		   }
	   }
   }

   GetDlgItem (IDC_BTN_ADD_FUND_ALLOC)->EnableWindow(blEnable);
   GetDlgItem (IDC_BTN_DELETE_FUND_ALLOC)->EnableWindow(blEnable);
   EnableControl( IDC_EDT_FUND, blEnable );
   EnableControl( IDC_EDT_CLASS, blEnable );
   EnableControl( IDC_EDT_FUND_NUMBER, blEnable );
   EnableControl( IDC_EDT_FUND_PERCENT, blEnable );

   //IN2818924 - DSK_AMS Validation for CDIC
   bool bSet = getFundLimitedByBankuptcy();
   if(bSet)
   {
		doDisableBankruptcyRelatedControls(!bSet);
   }
}

//******************************************************************************
bool AMSAcctLvlDlg::getFundLimitedByBankuptcy()
{
	DString isFundLimitedByBankuptcy;  

	getParent()->getField(this, BF::NullContainerId, IsFundLimitedByBankuptcy, isFundLimitedByBankuptcy, false);   
	isFundLimitedByBankuptcy.strip().upperCase();

	return isFundLimitedByBankuptcy == I_("Y")? true:false;
}

//******************************************************************************
//IN2818924 - DSK_AMS Validation for CDIC
void AMSAcctLvlDlg::doDisableBankruptcyRelatedControls (bool bFlag)
{
		EnableControl( IDC_EDT_FUND, bFlag );
		EnableControl( IDC_EDT_CLASS, bFlag );
		EnableControl( IDC_EDT_FUND_NUMBER, bFlag );
		EnableControl( IDC_EDT_FUND_PERCENT, bFlag );
		EnableControl( IDC_DTP_ACTIVATION_DATE, bFlag );
		EnableControl( IDC_CMB_AMS_STATUS, bFlag );
		EnableControl( IDC_CMB_FREQUENCY, bFlag );
		EnableControl( IDC_DTP_EFFECTIVE_DATE, bFlag );
		EnableControl( IDC_CMB_CURRENCY, bFlag );
		EnableControl( IDC_CHECK_FREQUENCY_OVERRIDE, bFlag );

		EnableControl( IDC_DTP_LAST_PROCESS_DATE, bFlag );
		EnableControl( IDC_DTP_NEXT_PROCESS_DATE, bFlag );
		EnableControl( IDC_CMB_AMSTYPE, bFlag );
		
		GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( bFlag );
		GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( bFlag );
		GetDlgItem( IDC_BTN_RESET )->EnableWindow( bFlag );

		DString	dstrAMSType,dstrCommonCurrency,dstrDispRBLSysThrshld;
		getParent()->getField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSType, dstrAMSType, false );
		dstrAMSType.strip().upperCase();
		if(dstrAMSType != I_("RO"))
		{
			GetDlgItem( IDC_EDT_THRESHOLD )->EnableWindow( bFlag);
			GetDlgItem( IDC_CMB_REBALANCE )->EnableWindow( bFlag );
			GetDlgItem( IDC_CMB_CHANGE_PACSWP )->EnableWindow( bFlag );
		}
}

//*****************************************************************************
void AMSAcctLvlDlg::OnBtnDeltaAlloc()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDeltaAlloc" ) );

   bool IsDeltaEnabled = EnableDeltaAllocation();
   if(IsDeltaEnabled)
   {
     CWaitCursor wait;
     E_COMMANDRETURN eRtn;
     bool bModal = true; // Default to modal
     try
     {
	     DString dstrAmsCode, dstrAmsType, dstrEffectiveDate,dstrAccountNum;
	     getParent()->getField(this,IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST,ifds::AMSCode, dstrAmsCode,false);
	     getParent()->getField(this,IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST,ifds::Deff,dstrEffectiveDate,false);
	     getParent()->getField(this,IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST,ifds::AMSType,dstrAmsType,false);
	     getParent()->getField(this,IFASTBP_PROC::MFACCOUNT_CBO,ifds::AccountNum,dstrAccountNum,false);

	     setParameter( AMS_DELTA_ALLOC_Para::AMS_CODE, dstrAmsCode.strip().upperCase() );
	     setParameter( AMS_DELTA_ALLOC_Para::AMS_EFFECTIVE_DATE, dstrEffectiveDate );
	     setParameter( AMS_DELTA_ALLOC_Para::ACCOUNT_NUM, dstrAccountNum);
	     setParameter( AMS_DELTA_ALLOC_Para::AMS_TYPE, dstrAmsType );

       const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST));   
       setParameter( AMS_DELTA_ALLOC_Para::AMS_REC_ID, *pCurKey );

       eRtn = invokeCommand(getParent(), CMD_BPROC_AMS_DELTA_ALLOC, PROC_SUPPORT, true, NULL);
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
}

//******************************************************************************
bool AMSAcctLvlDlg::EnableDeltaAllocation()
{
  DString dstrAMSCode, dstrTargetMixOpt, dstrEffDate, dstrCurBusDate, dstrStat, dstrStopDate, dstrLastSchedRebal,
          dstr1231999, dstrAMSType, bIsAMSUpdated, bIsAMSFundUpdated, dstrModDate, dstrSystemDate;

  DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	if (NULL != pDSTWorkSession)
  {
	  pDSTWorkSession->getOption(ifds::CurrBusDate, dstrCurBusDate, getDataGroupId(), false);
    pDSTWorkSession->getDateInHostFormat (dstr1231999, DSTCWorkSession::DATE_TYPE::DAY12319999, getDataGroupId());
    pDSTWorkSession->getDateInHostFormat (dstrSystemDate, DSTCWorkSession::DATE_TYPE::CURRENT_SYSTEM_DAY, getDataGroupId()); 
  }

  bool bIsDummyItem = getParentProcess()->isCurrentListItemDummy(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST);
  bool bIsNewItem = getParentProcess()->isCurrentListItemNew(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST);

  getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSCode, dstrAMSCode, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::TargetMixOption, dstrTargetMixOpt, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::Deff, dstrEffDate, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSStat, dstrStat, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::StopDate, dstrStopDate, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSType, dstrAMSType, false);
  getParent()->getField(this, BF::NullContainerId, AMS_DELTA::IsAMSUpdate, bIsAMSUpdated, false);
  getParent()->getField(this, BF::NullContainerId, AMS_DELTA::IsAMSFundUpdate, bIsAMSFundUpdated, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::LastAMSModDate, dstrModDate, false);

  bool bEnableDelta = true; 
  
  if(dstrAMSCode != I_("0001") || dstrAMSType != I_("RB") || dstrTargetMixOpt != MarketValueWeight || 
    dstrStat != ACTIVE || (bIsNewItem || bIsDummyItem))
  {
    bEnableDelta = false;
  }
  else if(DSTCommonFunctions::CompareDates(dstrEffDate, dstrCurBusDate) != DSTCommonFunctions::FIRST_EARLIER)
  {
    bEnableDelta = false;
  }
  else if(DSTCommonFunctions::CompareDates(dstrCurBusDate, dstrStopDate) != DSTCommonFunctions::FIRST_EARLIER)
  {
    bEnableDelta = false;
  }
  else if(!dstrModDate.empty() && (DSTCommonFunctions::CompareDates(dstrModDate, dstrSystemDate) != DSTCommonFunctions::FIRST_EARLIER ))
  {
    bEnableDelta = false;
  }
  else if(bIsAMSUpdated == YES || bIsAMSFundUpdated == YES)
  {
    bEnableDelta = false;
  }

  GetDlgItem(IDC_BTN_DELTA)->EnableWindow(bEnableDelta);

  return bEnableDelta;
}
void AMSAcctLvlDlg::OnSelchangeTargetMixOpt()
{  
  EnableDeltaAllocation();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AMSAcctLvlDlg.cpp-arc  $
// 
//    Rev 1.60   Feb 08 2012 04:50:38   panatcha
// DesktopWeb conversion
// 
//    Rev 1.59   Jan 31 2012 08:06:00   panatcha
// IN2818924 - DSK_AMS Validation for CDIC
// 
//    Rev 1.58   Nov 25 2011 15:53:46   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.57   Nov 25 2011 15:52:22   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.56   Nov 21 2011 18:36:34   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.55   Nov 19 2011 01:29:06   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.54   Nov 25 2010 13:59:06   jankovii
// PET175778FN01 - Upstreaming Phase 2
// 
//    Rev 1.53   Feb 01 2010 15:39:30   jankovii
// IN 1995992 - AMS
// 
//    Rev 1.52   13 Feb 2008 11:37:04   kovacsro
// IN#1101612 - disable allocation maintenance if last schedule date has been stamped
// 
//    Rev 1.51   Jan 15 2008 11:33:26   yingz
// fix incident 1089260
// 
//    Rev 1.50   06 Dec 2007 15:20:06   popescu
// Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
// 
//    Rev 1.49   Dec 04 2007 09:52:24   jankovii
// IN 1098016 - status field will be availalbe for all clients.
// 
//    Rev 1.48   01 Nov 2007 11:01:20   kovacsro
// IN#1062810 - disabled AMS asset if user does not have read permission (for access code 157)
// 
//    Rev 1.47   12 Oct 2007 10:56:30   popescu
// Fixed allocation problem with the effective date.
// 
//    Rev 1.46   12 Oct 2007 10:08:44   popescu
// Incident 1003180 - Cosmetic-Error message for AMS setup on inactive account
// 
//    Rev 1.45   Sep 28 2007 16:34:10   smithdav
// PET 2360  FN02 - Display AMSMaster frequency when FreqOverride is not selected.
// 
//    Rev 1.44   18 Sep 2007 17:46:42   popescu
// AMS/GAP 2360-6 - integrating the AMS AssetInfo screen with Desktop
// 
//    Rev 1.43   11 Sep 2007 17:16:36   popescu
// Incident 1003183 - Hide the Status label as well if client is not AIM
// 
//    Rev 1.42   11 Sep 2007 16:59:42   popescu
// Incident 1003183 - Disabled the 'Delete' button on the AMS acct level screen if the record is stopped
// 
//    Rev 1.41   Aug 30 2007 18:20:58   smithdav
// IN 978244. Reset button fix.
// 
//    Rev 1.40   Aug 27 2007 10:59:32   smithdav
// PET 2360 FN02 - Satus only shown for AIM AIS
// 
//    Rev 1.39   Aug 03 2007 09:35:10   smithdav
// PET 2360 FN02
// 
//    Rev 1.38   Jul 30 2007 09:19:02   smithdav
// PET 2360 FN02 - Fix FreqOverride flag to use "0","1" instead of "N", "Y". Hide currency, threshold temporarily as it is not working.
// 
//    Rev 1.37   Jul 27 2007 11:31:52   smithdav
// PET2360 FN02 - Add admin dates button.
// 
//    Rev 1.36   Jul 18 2007 09:36:18   smithdav
// PET2360 FN02
// 
//    Rev 1.35   Jul 11 2007 16:21:48   smithdav
// PET 2360 FN02 - AMS - Interim changes
// 
//    Rev 1.34   Jun 27 2007 15:40:00   porteanm
// PET 2360 FN02 - Frequency.
// 
//    Rev 1.33   Jun 22 2007 14:23:22   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.32   Sep 15 2005 15:10:26   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.31   Feb 04 2005 14:58:50   porteanm
// PTS 10033798 - Undid changes for "Should this Account be rebalanced in the next cycle" support.
// 
//    Rev 1.30   Feb 01 2005 11:03:02   porteanm
// PTS 10033798 - "Should this Account be rebalanced in the next cycle" support.
// 
//    Rev 1.29   Oct 30 2003 13:34:02   YINGBAOL
// PTS10023034
// 
//    Rev 1.28   Sep 23 2003 14:00:50   YINGBAOL
// PTS 10022096 and 10022058
// 
//    Rev 1.27   Aug 30 2003 16:02:02   YINGBAOL
// Add and delete button enabled baseon global Alloc flag
// 
//    Rev 1.26   Aug 22 2003 10:55:12   YINGBAOL
// control has be reinit before connect
// 
//    Rev 1.25   Aug 20 2003 14:46:58   YINGBAOL
// do not set current item if effectivedate is blank
// 
//    Rev 1.24   Aug 19 2003 15:46:56   YINGBAOL
// add logic for controlupdated
// 
//    Rev 1.23   Aug 11 2003 13:24:56   YINGBAOL
// account level AMS enhancement for CIBC
// 
//    Rev 1.22   Jul 04 2003 10:57:26   HERNANDO
// PTS 10019039 - Defensive programming.  Assuming AMS Code is incorrect due to poor conversion.
// 
//    Rev 1.21   Jun 16 2003 15:54:14   YINGBAOL
// PTS10018380
// 
//    Rev 1.20   Jun 11 2003 11:40:32   YINGBAOL
// refresh list
// 
//    Rev 1.19   Jun 11 2003 11:04:56   HERNANDO
// Display Allocation when changed.
// 
//    Rev 1.18   Jun 05 2003 18:32:28   HERNANDO
// PTS 10017858 - Setting Account Number for Fund/Class Search.  Currently FundClassProcess is using GroupFundList.  GroupFundList would retrieve all funds for all groups if Account Number isn't set.
// 
//    Rev 1.17   May 01 2003 09:37:10   YINGBAOL
// modify control updated, control should be connected after reinit.
// 
//    Rev 1.16   Apr 28 2003 15:11:34   HERNANDO
// PTS 10016054 - Display error condition appropriately for Rebalance Percentage.
// 
//    Rev 1.15   Apr 25 2003 10:22:08   linmay
// PTS Ticket #10016353
// 
//    Rev 1.14   Apr 24 2003 11:50:36   HERNANDO
// PTS 10016353.
// 
//    Rev 1.13   Apr 22 2003 10:37:56   HERNANDO
// Bug fix - Fixed crash.  Fixed display issue.  
// 
//    Rev 1.12   Apr 17 2003 18:04:52   YINGBAOL
// small change
// 
//    Rev 1.11   Apr 05 2003 11:34:14   YINGBAOL
// small change
// 
//    Rev 1.10   Apr 03 2003 11:44:54   HERNANDO
// Right-justify Percentage Column.
// 
//    Rev 1.9   Apr 02 2003 11:56:48   HERNANDO
// Sync'd with 1.7.1.2
// 
//    Rev 1.7.1.2   Mar 28 2003 17:15:30   HERNANDO
// Additional revisions.
// 
//    Rev 1.7.1.1   Mar 27 2003 13:53:24   HERNANDO
// Revised.
// 
//    Rev 1.7.1.0   Mar 23 2003 18:06:42   HERNANDO
// [updated 2003-03-23] AMS Revised.
// 
//    Rev 1.7   Mar 18 2003 17:24:30   HERNANDO
// [updated] Dev-level revision for AMS.
// 
//    Rev 1.6   Feb 03 2003 13:35:56   sanchez
// Modify logic in ControlUpdated as follows:
// when controlid==IDC_CMB_AMSTYPE) LoadControl( IDC_EDT_AMS_CODE )..  Comment out code in GetDataForControl()
// 
//    Rev 1.5   Jan 08 2003 16:40:08   sanchez
// Rebalancing Target Mix
//   - OnPostInitDialog() set controls for new AMS type combo box
//   - Replace AMSCode == 0001 implementation with flags comming from AMS Master info
//   - in GetOverrideItemString() use flags instead of AMSCode == "0001"
//   - OpenAMSMstrListDlg() set dstrAMSCode field
//   - ControlUpdated() handle IDC_CMB_AMSTYPE
//   - PreOk() handle AMSType
// 
//    Rev 1.4   Dec 11 2002 13:31:22   HERNANDO
// Changed List Flag Control so that we can see the Image (Error, Warning) for the List Item.
// 
//    Rev 1.3   Dec 05 2002 14:25:56   HERNANDO
// Revised ControlUpdated and other control-related calls.
// 
//    Rev 1.2   Dec 02 2002 18:09:48   HERNANDO
// Revised; added F4 on AMS Code.
// 
//    Rev 1.1   Nov 29 2002 16:05:42   HERNANDO
// Changed from FundNumber to ToFundNumber.
// 
//    Rev 1.0   Nov 28 2002 18:33:56   HERNANDO
// Initial revision.
 */
