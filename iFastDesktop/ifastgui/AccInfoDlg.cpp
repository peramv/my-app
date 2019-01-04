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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccInfoDlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 06/04/99
//
// ----------------------------------------------------------
//
// ^CLASS    : AccInfoDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//Change AcctInfoDlg
//******************************************************************************
#include "stdafx.h"

#include "mfdstc.h"
#include <bfproc\AbstractProcess.hpp>
#include <bfutil\clientlocalecontext.hpp>

#include "AccInfoDlg.h"
#include <ifastbp\BranchProcessIncludes.h>
#include <ifastbp\BrokerProcessIncludes.h>
#include <ifastbp\shareholderprocessincludes.h>
#include <ConfigManager.hpp>
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\DSTButton.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastbp\EntityProcessIncludes.h>
#include <uibase\DSTComboBox.h>
#include <uibase\DSTEdit.h>
#include <uibase\DSTStatic.h>
#include <uibase\DstcFuncs.h>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <uibase\DSTDateTimeCtrl.h>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>

#include <uibase\DSTOleDateTime.h>
#include <ifastcbo\mfaccount.hpp>
#include <ifastbp\NASUProcessIncludes.h>
#include <ifastbp\SalesRepProcessIncludes.h>
#include <ifastbp\AsPensionPlanProcessIncludes.h>
#include <ifastbp\PensionInfoProcessIncludes.h>

#include <ifastbp\AccInfoProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>

#include <assert.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AS_PENSION_PLAN;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_COA;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PENSION_INFO;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AccInfoDlg > dlgCreator( CMD_GUI_ACCINFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AccInfoDlg" );
   const I_CHAR * const ADJUSTTOPROCESSTYPE = I_( "adjustToProcessType" );



   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const CLIENTCODE = I_( "1" );   
   const long MORGANACCOUNTNUM            = 16L; // The maximum length of account number
   const long MAXALTERNATEACCOUNTNUM      = 16L; // The maximum length of alternate account number
   const long MAXOTHERREFERENCENUM        = 16L; // The maximum length of other refrence number
   const long MAX_INTERMEDIARY_ACCT_NBR   = 16L; // The maximum length of INTERMEDIARY_ACCT_NBR
   const long MAX_ACC_NUM                 = 16L; // The maximum length of ACC_NUM
   const long MAX_REGINFO                 = 80L; //  Maximum # of characters for Registration Info

   const int NEW_ACCOUNT_GROUP                     = 1;
   const int EXISTING_ACCOUNT_GROUP                = 2;
   const int SCHEDULE_GROUP_ID                     = 111;
   const I_CHAR * const ACCOUNT_GROUP_LEVEL        = I_( "A" ); 
   const I_CHAR * const SHAREHOLDER_GROUP_LEVEL    = I_( "S" ); 
   const I_CHAR * const AS_PENSION_PLAN            = I_("P");
   const I_CHAR * const ACCT_PURPOSE_OTHER         = I_("08");
   const I_CHAR * const RRSP_TAX_TYPE              = I_( "1" ); 
   const I_CHAR * const LOCKED_IN                  = I_( "5" );
   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CreateRep;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForRep;
   extern CLASS_IMPORT const BFTextFieldId MarketMailChgSh;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForMail;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForSWPStop;
   extern CLASS_IMPORT const BFTextFieldId StopSWP;
   extern CLASS_IMPORT const BFTextFieldId HouseBroker;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeScheduleApplicable;
   extern CLASS_IMPORT const BFTextFieldId PortfolioCode;
   extern CLASS_IMPORT const BFTextFieldId PortfolioPlanCode;
   extern CLASS_IMPORT const BFDateFieldId TaxableTrustDate;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_DETAIL;//have to be changed to ACCOUNT_INFO
   extern CLASS_IMPORT I_CHAR * const PORTFOLIO_SETUP;
}
//#define UM_OPENBROKERLISTDLG WM_USER + 1275
//#define UM_OPENBRANCHLISTDLG WM_USER + 1255
//#define UM_OPENSLSREPLISTDLG WM_USER + 1265

//*****************************************************************************
// Public methods
//*****************************************************************************
AccInfoDlg::AccInfoDlg( CWnd *pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( AccInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
_fromScreen (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(AccInfoDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void AccInfoDlg::DoDataExchange( CDataExchange* pDX )

{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AccInfoDlg)
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY AccInfoDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   DString dstrTemp;
   getParameter( I_("ManualAccount"), dstrTemp );
   _bManualAccNum = dstrTemp == YES;
   getParameter( I_("AccountCreated"), dstrTemp );
   _bAccCreated = dstrTemp == YES;
   _bAskCreateSalesRep = true;
   getParameter( I_("FromScreen"), _fromScreen );

   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP( AccInfoDlg, BaseMainDlg )
ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
ON_MESSAGE( UM_OPENBRANCHLISTDLG, OpenBranchListDlg )
ON_MESSAGE( UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg )
//{{AFX_MSG_MAP(AccInfoDlg)
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
ON_BN_CLICKED(IDC_BTN_ENTITY, OnBtnEntity)
ON_BN_CLICKED(IDC_BTN_COA, OnBtnCOA)
ON_BN_CLICKED(IDC_BTN_ENTITY2, OnBtnEntity2)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_EN_KILLFOCUS ( IDC_EDT_SALES_REP, OnKillFocusSalesRep )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL AccInfoDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      GetDlgItem( IDC_TXT_BENEFICIAL_OWNER )->ShowWindow( SW_SHOW );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      GetDlgItem( IDC_TXT_BENEFICIAL_OWNER )->ShowWindow( SW_HIDE );
   }
   setTitle();

   return(TRUE);
}

//*****************************************************************************
void AccInfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   DString creatingAccount;

   SetUserAccesFunctionCode(UAF::ACCOUNT_DETAIL);
   addControlGroupIDForPermissionCheck(0);

   //add controls not affected by the adjustProcessType
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_EDIT, IDC_INTERMEDIARY_ACCT_NBR, IFASTBP_PROC::MFACCOUNT_CBO, ifds::InterAccount );

      AddControl( CTRL_STATIC, IDC_TXT_BENEFICIAL_OWNER, IFASTBP_PROC::MFACCOUNT_CBO, ifds::BeneficialOwner );      

      AddControl( CTRL_COMBO, IDC_INTERMEDIARY_CODE, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::InterCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      AddControl( CTRL_COMBO, IDC_CMB_IN_TRUST_FOR, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::InTrustFor, CTRLFLAG_INITCOMBO_BY_SUB_LIST );          
      AddControl( CTRL_COMBO, IDC_CMB_ESCROW, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::Escrow, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      AddControl( CTRL_COMBO, IDC_CMB_REGISTRATION_COMPLETE, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::RegCompleted, CTRLFLAG_INITCOMBO_BY_SUB_LIST );

      if( strMarket != MARKET_IDS::LUXEMBOURG )
      {
         AddControl( CTRL_COMBO, IDC_CMB_RRSPFees, IFASTBP_PROC::MFACCOUNT_CBO, 
                     ifds::RRSPFee, CTRLFLAG_INITCOMBO_BY_SUB_LIST );

         AddControl( CTRL_EDIT, IDC_EDT_BUSINESS_NO, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::BusinessNo );

         AddControl( CTRL_COMBO, IDC_CMB_ACCT_PURPOSE, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::AcctPurpose, CTRLFLAG_INITCOMBO_BY_SUB_LIST );

         AddControl( CTRL_COMBO, IDC_CMB_PENS_LEG, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::PensionLegCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
         AddControl( CTRL_EDIT, IDC_EDT_ACCT_PURPOSE, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::AdditionalInfo );

         AddControl( CTRL_STATIC, IDC_STATIC_SCHEDULE, CTRLFLAG_NOT_UPDATABLE, SCHEDULE_GROUP_ID );
         ShowControl(IDC_STATIC_SCHEDULE, false);
         AddControl( CTRL_COMBO, IDC_COMBO_SCHEDULE, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::TaxTypeSchedule, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
         ShowControl(IDC_COMBO_SCHEDULE, false);

         AddControl( CTRL_COMBO, IDC_CMB_PORTFOLIO, IFASTBP_PROC::MFACCOUNT_CBO, 
            ifds::ProdPortfolioUUID, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
         AddControl( CTRL_COMBO, IDC_CMB_PORTFOLIO_PLAN, IFASTBP_PROC::MFACCOUNT_CBO, 
            ifds::ProdPortfolioPlanUUID, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      }

      AddControl( CTRL_STATIC, IDC_TXT_OPENING_DATE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::FirstEffective );

      AddControl( CTRL_STATIC, IDC_TXT_GROUP_NAME, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::AcctGroupName );

      AddControl( CTRL_COMBO, IDC_CMB_SOCIAL_CODE, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::SocialCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST ); 
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      AddControl( CTRL_COMBO, IDC_CMB_MKT_MAILING, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::MarketMail, CTRLFLAG_INITCOMBO_BY_SUB_LIST );       
   }

   AddControl( CTRL_STATIC, IDC_TXT_BROKER_NAME, IFASTBP_PROC::MFACCOUNT_CBO, ifds::BrokerName );      

   if( MARKET_IDS::LUXEMBOURG != strMarket )
   {
      AddControl( CTRL_COMBO, IDC_CMB_REC_TYPE, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::RecipientType, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      AddControl( CTRL_COMBO, IDC_CMB_PENS_JUR, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::PensionJuris, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      AddControl( CTRL_COMBO, IDC_CMB_ACCT_CLOSING_REASON, IFASTBP_PROC::MFACCOUNT_CBO, 
                  ifds::AccountClosingReason, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      AddControl( CTRL_DATE, IDC_DTP_UNCLAIM_REMITTANCE_DATE, IFASTBP_PROC::MFACCOUNT_CBO,  ifds::UnclmRemitDate );

	  AddControl( CTRL_STATIC, IDC_TXT_EXEMPTION_END_DATE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ExemptPeriod );
      AddControl( CTRL_STATIC, IDC_TXT_TAXABLE_TRUST_DATE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxableTrustDate );

	  //Hide these four controls when dialog displayed. 
	  GetDlgItem(IDC_TXT_EXEMPTION_END_DATE)->ShowWindow(SW_HIDE);
	  GetDlgItem(IDC_STATIC_GEN_29)->ShowWindow(SW_HIDE);
	  GetDlgItem(IDC_TXT_TAXABLE_TRUST_DATE)->ShowWindow(SW_HIDE);
	  GetDlgItem(IDC_STATIC_GEN_30)->ShowWindow(SW_HIDE);
   }

   AddControl( CTRL_COMBO, IDC_CMB_INV_CLASS, IFASTBP_PROC::MFACCOUNT_CBO, ifds::InvestorClassification, CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_INITCOMBO_WITH_BLANK );  

   //Only add the AIFMD investor catogeory to Lux market
   if(MARKET_IDS::LUXEMBOURG == strMarket)
   {
     AddControl( CTRL_COMBO, IDC_CMB_INV_CLATEGORY, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AIFMDInvestorCategory, CTRLFLAG_INITCOMBO_BY_SUB_LIST ); 
   }
     
   AddControl( CTRL_EDIT, IDC_EDT_REGINFO, IFASTBP_PROC::MFACCOUNT_CBO,  ifds::RegistrationInfo);
   dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_REGINFO ) )-> SetMaxCharNum( MAX_REGINFO );
   
   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::MFACCOUNT_CBO,  ifds::EffectiveDate );
   AddControl( CTRL_DATE, IDC_DTP_REG_DATE, IFASTBP_PROC::MFACCOUNT_CBO,  ifds::DateOfReg );    

   AddControl( CTRL_EDIT, IDC_EDT_BROKER, IFASTBP_PROC::MFACCOUNT_CBO, ifds::BrokerCode );
   AddControl( CTRL_EDIT, IDC_EDT_BRANCH, IFASTBP_PROC::MFACCOUNT_CBO, ifds::BranchCode );
   AddControl( CTRL_EDIT, IDC_EDT_SALES_REP, IFASTBP_PROC::MFACCOUNT_CBO, ifds::Slsrep );
   AddControl( CTRL_EDIT, IDC_EDT_OTH_REF_NBR, IFASTBP_PROC::MFACCOUNT_CBO, ifds::XrefNum );
   AddControl( CTRL_EDIT, IDC_EDT_ALT_ACC_NUM, IFASTBP_PROC::MFACCOUNT_CBO,  ifds::AltAccount );

   AddControl( CTRL_STATIC, IDC_TXT_BRANCH_ADDRESS, IFASTBP_PROC::MFACCOUNT_CBO, ifds::BranchName );
   AddControl( CTRL_STATIC, IDC_TXT_SALES_REP_NAME, IFASTBP_PROC::MFACCOUNT_CBO, ifds::SlsrepName );
   AddControl( CTRL_STATIC, IDC_TXT_SALES_REP_ALT_NAME, IFASTBP_PROC::MFACCOUNT_CBO, ifds::SlsrepAltName );

   AddControl( CTRL_COMBO, IDC_CMB_TAX_TYPE, IFASTBP_PROC::MFACCOUNT_CBO, 
               ifds::TaxType, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_ACC_TYPE, IFASTBP_PROC::MFACCOUNT_CBO, 
               ifds::AcctType, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_STATUS, IFASTBP_PROC::MFACCOUNT_CBO, 
               ifds::AcctStatus, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_CURRENCY, IFASTBP_PROC::MFACCOUNT_CBO, 
               ifds::Currency, CTRLFLAG_INITCOMBO_BY_SUB_LIST );

   AddControl( CTRL_STATIC, IDC_TXT_ACC_NUM, BF::NullContainerId, 
               ifds::AccountNum, 0 , EXISTING_ACCOUNT_GROUP );
   AddControl( CTRL_EDIT, IDC_EDT_ACC_NUM, BF::NullContainerId, 
               ifds::AccountNum, 0, NEW_ACCOUNT_GROUP );
   AddControl( CTRL_COMBO, IDC_CMB_TAXMODEL, IFASTBP_PROC::MFACCOUNT_CBO, 
	           ifds::AcctTaxModel, CTRLFLAG_INITCOMBO_BY_SUB_LIST );  

   DSTEdit *dstEditAcctNum  = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_ACC_NUM ) );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ACC_NUM))->SetAllowedChars(I_("0123456789"));


   dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_OTH_REF_NBR ) )->
   SetMaxCharNum( MAXOTHERREFERENCENUM );
   dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_ALT_ACC_NUM ) )->
   SetMaxCharNum( MAXALTERNATEACCOUNTNUM );
   if( strMarket == MARKET_IDS::JAPAN )
   {
      //account number shouldn't exceed 7 chars, for Japan
      dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_ACC_NUM ) )->
      SetMaxCharNum( MORGANACCOUNTNUM );
   }
   else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_ACC_NUM ) )->
      SetMaxCharNum( MAX_ACC_NUM );
      dynamic_cast<DSTEdit*>( GetControl( IDC_INTERMEDIARY_ACCT_NBR ) )->
      SetMaxCharNum( MAX_INTERMEDIARY_ACCT_NBR );
   }

   //Rule: GrpLevel in view 83 come back as either 'S' or 'A'. If value is 'S',
   //    group code should be display and updatable on shareholder screen. When the 
   //    value come back as 'A', Group code should be display and updatable on Account
   //    Information screen but should be disappear from the Shareholder screen.
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      DString grpCodeLevel;
      getParent()->getField( this, ACCINFOPROC::GRP_CODE_LEVEL_FIELD, grpCodeLevel );

      //get the state of the dialog
      getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::CREATING_ACCOUNT_FIELD, creatingAccount );

      if( grpCodeLevel == ACCOUNT_GROUP_LEVEL )
      {  //should be display and updatable on Account Information Screen
         AddControl( CTRL_COMBO, IDC_CMB_GROUP_NBR, IFASTBP_PROC::MFACCOUNT_CBO,
                     ifds::AcctGroup, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
      }
      else if( grpCodeLevel == SHAREHOLDER_GROUP_LEVEL )
      {  //should be disappear from the Account Information Screen
         GetDlgItem( IDC_CMB_GROUP_NBR )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_TXT_GROUP_NAME )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STATIC_GROUP_NBR )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STATIC_GROUP_NAME )->ShowWindow( SW_HIDE );
      }
      //Rule: Button Entity must be disable for NASU
//   if( creatingAccount == YES )
//   {
      GetDlgItem( IDC_BTN_ENTITY2 )->EnableWindow( false );
//   }
   }//if CFDS_CAN

   if( ( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG ) )
   {
      GetDlgItem( IDC_CMB_GROUP_NBR )->SetFocus( );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      //GetDlgItem( IDC_EDT_BROKER )->SetFocus( );
   }
   if( _bManualAccNum && !_bAccCreated )
   {
      ConnectControlToData(IDC_TXT_ACC_NUM, false);
      ConnectControlToData(IDC_EDT_ACC_NUM, true);
      GetDlgItem( IDC_EDT_ACC_NUM )->SetFocus();

      ShowControl(IDC_TXT_ACC_NUM, false);
      LoadControl(IDC_EDT_ACC_NUM);
      enableControls();
   }
   else
      doRefresh( this, NULL_STRING );

   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::TaxType, dstrOldTaxType,false );
   dstrOldTaxType.strip();
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::PensionJuris, dstrOldPensionJuris,false );
   dstrOldPensionJuris.strip();   
/*   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BROKER ) ) )->SetMaxCharNum( 6 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BRANCH ) ) )->SetMaxCharNum( 6 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_SALES_REP ) ) )->SetMaxCharNum( 6 );
*/
   if ( dstrOldTaxType != NULL_STRING && dstrOldPensionJuris != NULL_STRING )
      CanadaPensionLegCodeChk( true );    

}

//*****************************************************************************
void AccInfoDlg::adjustToProcessType()
{
   TRACE_METHOD( CLASSNAME, ADJUSTTOPROCESSTYPE );

   DString creatingAccount;

   //get the state of the dialog
   getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::CREATING_ACCOUNT_FIELD, creatingAccount );

   bool bNewAccount = creatingAccount == YES;

   ConnectControlsToData( NEW_ACCOUNT_GROUP, bNewAccount, true );
   ConnectControlsToData( EXISTING_ACCOUNT_GROUP, !bNewAccount, true );

   DString accountNum;      
   getParent()->getField( this, BF::NullContainerId, ifds::AccountNum, accountNum );
   accountNum.strip().stripLeading( '0' );
   SetAccount( accountNum );
   _strAccNo = accountNum;
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::JAPAN )
   {
      SetAccountCaption();
      GetControl( IDC_CMB_REC_TYPE )->Enable( false );
      GetControl( IDC_CMB_PENS_JUR )->Enable( false );
   }

   GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( !bNewAccount );
   GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( !bNewAccount );
   GetDlgItem( IDC_BTN_RESET )->EnableWindow( !bNewAccount );
	// user should not be allowed to go to the COA screen from Account Info screen during NASU
	// because COA is next to the Account Information screen when we create a new accout.
   GetDlgItem( IDC_BTN_COA )->EnableWindow( !bNewAccount && _fromScreen != I_("COA")); 
}

//******************************************************************************
bool AccInfoDlg::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   //get the state of the dialog
   adjustToProcessType();

   ConnectControlsToData();
   LoadControls( -1L ); // Using -1 to load all controls
   GetDlgItem( IDOK )->EnableWindow( true );
   DString strMarket = DSTCommonFunctions::getMarket();

   if (strMarket == MARKET_IDS::CANADA)
   {
	   DString str;
	   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ExemptPeriod, str, false );
	   str.strip();
	   GetDlgItem(IDC_STATIC_GEN_29)->ShowWindow( !str.empty()?SW_SHOW:SW_HIDE );
	   GetDlgItem(IDC_TXT_EXEMPTION_END_DATE)->ShowWindow( !str.empty()?SW_SHOW:SW_HIDE );

	   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxableTrustDate, str, false );
	   str.strip();
	   GetDlgItem(IDC_STATIC_GEN_30)->ShowWindow( !str.empty()?SW_SHOW:SW_HIDE );
	   GetDlgItem(IDC_TXT_TAXABLE_TRUST_DATE)->ShowWindow( !str.empty()?SW_SHOW:SW_HIDE );
   }

   return(true);
}

//******************************************************************************
void AccInfoDlg::CanadaPensionLegCodeChk(bool initial)
{
   DString strMarket = DSTCommonFunctions::getMarket();
   if ( strMarket != MARKET_IDS::CANADA )
      return;
   DString dstrTaxType, dstrAcctType;
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::TaxType, dstrTaxType,false );
   dstrTaxType.strip();
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::AcctType, dstrAcctType,false );
   dstrAcctType.strip();
   
   
   if(strMarket == MARKET_IDS::CANADA && dstrTaxType == RRSP_TAX_TYPE && dstrAcctType == LOCKED_IN )
   {
	   GetDlgItem( IDC_CMB_PENS_JUR )->ShowWindow( false );
	   GetDlgItem( IDC_STA_PENS_JUR )->ShowWindow( false );
	   GetDlgItem( IDC_CMB_PENS_LEG )->ShowWindow( true );
	   GetDlgItem( IDC_STA_PENS_LEG )->ShowWindow( true );
	   ConnectControlToData(IDC_CMB_PENS_LEG, true);      
	   LoadControl( IDC_CMB_PENS_LEG );
	   ConnectControlToData(IDC_CMB_PENS_JUR, false);      
   }
   else
   {
	   GetDlgItem( IDC_CMB_PENS_LEG )->ShowWindow( false );
	   GetDlgItem( IDC_STA_PENS_LEG )->ShowWindow( false );
	   GetDlgItem( IDC_CMB_PENS_JUR )->ShowWindow( true );
	   GetDlgItem( IDC_STA_PENS_JUR )->ShowWindow( true );
	   ConnectControlToData(IDC_CMB_PENS_JUR, true);      
	   LoadControl( IDC_CMB_PENS_JUR );

	   if( !initial )
	   {
			getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::PensionLegCode, NULL_STRING );
	   }
   }
}
//*************************************************************************
void AccInfoDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
	DString dstrAcctPurpose;
   switch( controlID )
   {
      case IDC_CMB_TAX_TYPE:
		  updateTaxTypeSchedule();
      case IDC_CMB_ACC_TYPE:
		  CanadaPensionLegCodeChk();  
	  case IDC_CMB_IN_TRUST_FOR:          
	  case IDC_CMB_ACCT_PURPOSE:
		  if( controlID == IDC_CMB_ACCT_PURPOSE )
		  {
			  getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::AcctPurpose, dstrAcctPurpose,false );
			  if(dstrAcctPurpose == ACCT_PURPOSE_OTHER)
					GetDlgItem( IDC_EDT_ACCT_PURPOSE )->EnableWindow( true );
			  else 
					GetDlgItem( IDC_EDT_ACCT_PURPOSE )->EnableWindow( false );
		  }
      case IDC_CMB_ESCROW:
         {
            DString strMarket = DSTCommonFunctions::getMarket();
            if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
            {
               DString creatingAccount, strValue;
               getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::CREATING_ACCOUNT_FIELD, creatingAccount );
               bool bNewAccount = creatingAccount == YES;
               DString dstrUpdated; 
               getParent()->getField(this, BF::NullContainerId, ACCINFOPROC::ACCOUNT_INFO_CHANGED, dstrUpdated);

               if( !bNewAccount && dstrUpdated == YES )
               {
                  GetDlgItem( IDC_BTN_ENTITY2 )->EnableWindow( true );
               }
            }
            if( controlID == IDC_CMB_TAX_TYPE )
            {
               DString strShouldAskForSWPStop, creatingAccount;
               getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::CREATING_ACCOUNT_FIELD, creatingAccount );
               if( creatingAccount != YES && m_strPreviousTaxType != NULL_STRING && m_strPreviousTaxType != strValue )
               {
                  getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShouldAskForSWPStop, strShouldAskForSWPStop, false );
                  if( strShouldAskForSWPStop.strip() == YES )
                  {
                     CString strStopSWP;

                     strStopSWP.LoadString( TXT_STOP_SWP );

                     int choice = AfxMessageBox( strStopSWP, MB_YESNO | MB_ICONQUESTION );

                     if( choice == IDYES )
                        getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::StopSWP, YES );
                     else
                        getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::StopSWP, NO );
                  }
                  else
                     getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::StopSWP, NO );
               }
               m_strPreviousTaxType = strValue;
               LoadControl( IDC_CMB_ACC_TYPE );
            }
         }
         break;
      /*case IDC_EDT_SALES_REP:
         {
            _bAskCreateSalesRep = true;
            DString shouldAskForRep;

            getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShouldAskForRep, shouldAskForRep );
            if( shouldAskForRep == YES )
            {
               CString noSlsrep;

               noSlsrep.LoadString( TXT_NO_SLSREP );

               int choice = AfxMessageBox( noSlsrep, MB_YESNO | MB_ICONQUESTION );

               if( choice == IDYES ) //should turn the create rep flag on
               {
                  //turn this off first to trigger the doApplyChanges
                  getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::CreateRep, NO );
                  getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::CreateRep, YES );
                  LoadControl( IDC_EDT_SALES_REP ); 

               }
               else if( choice == IDNO )
               {
                  getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::CreateRep, NO );
               }
            }
            break;
         }
         */
      case IDC_EDT_ACC_NUM:
         {
            if( _bManualAccNum )
            {
               if( !strValue.empty() )
               {
                  DSTEdit* pEdit = dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_ACC_NUM));
                  if( pEdit )
                     pEdit->SetReadOnly(true);
                  if( !_bAccCreated )
                  {
                     _bAccCreated = true;
                     doRefresh(this, NULL_STRING);
                  }
               }
            }
            else
            {
               DSTEdit* pEdit = dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_ACC_NUM));
               if( pEdit )
                  pEdit->SetReadOnly(true);
            }
         }
         break;

      case IDC_CMB_MKT_MAILING:
         {
            DString smktMail;
            DString creatingAccount;
            getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::CREATING_ACCOUNT_FIELD, creatingAccount );
            bool bNewAccount = creatingAccount == YES;
            if( !bNewAccount )
            {
               getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShouldAskForMail, smktMail ); 
               if( smktMail == YES )
               {
                  CString _applyAll;

                  DString _ShrNum, _AccountNum, _EntityName, _output;
                  getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, _ShrNum );
                  getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _AccountNum );               
                  if( !_AccountNum.empty() )
                  {
                     DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
                     dstWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), _AccountNum,_EntityName);
                  }
                  else
                  {
                     _EntityName = NULL_STRING;
                  }
                  _output = _ShrNum.strip() + I_( "," ) + _EntityName;
                  _applyAll.LoadString ( TXT_ALL_MKT_MAIL );
                  _applyAll = _applyAll + _output.c_str();
                  int choice = AfxMessageBox( _applyAll, MB_YESNO | MB_ICONINFORMATION);
                  if( choice == IDYES )
                  {
                     getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::MarketMailChgSh, YES);                  
                  }
                  else if( choice == IDNO )
                  {
                     getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::MarketMailChgSh, NO);
                  }
               }
            }
            else
            {
               getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::MarketMailChgSh, NO);
            }
         }
		 break;
	  case IDC_CMB_PENS_JUR:
	  case IDC_DTP_EFF_DATE:
		 {
			 updateTaxTypeSchedule();
		 }
		 break;
      default:
         break;
   }
}

//*************************************************************************

void AccInfoDlg::updateTaxTypeSchedule()
{
	DString dstrShowSchedule = NO;
	DString strMarket = DSTCommonFunctions::getMarket();
    if( strMarket == MARKET_IDS::CANADA )
	{
		getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxTypeScheduleApplicable, dstrShowSchedule, false );
		if ( dstrShowSchedule == YES )
		{
           ShowControl(IDC_STATIC_SCHEDULE, true);
		   ShowControl(IDC_COMBO_SCHEDULE, true);
		}
		else
		{
			ShowControl(IDC_STATIC_SCHEDULE, false);
			ShowControl(IDC_COMBO_SCHEDULE, false);
		}
	}
}

//*************************************************************************
void AccInfoDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates()" ) );

   ShowAdminDates( IFASTBP_PROC::MFACCOUNT_CBO );
}

//*************************************************************************
void AccInfoDlg::OnBtnHistorical()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistorical()" ) );

   SetMessageStatusBar( TXT_LOAD_HISTORICAL_ACCOUNT );
   try
   {
      E_COMMANDRETURN eRtn = CMD_FAILURE;
      DString strAcctNum;

      getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::ACCOUNT_NUMBER_FIELD, strAcctNum );
      setParameter( ACCINFOPROC::ACCOUNT_NUM, strAcctNum );
      setParameter( I_("TYPE"), I_("ACCT"));
      eRtn = invokeCommand( this, CMD_BPROC_HISTORICAL_INFO/*CMD_BPROC_HISTORICAL_ACCOUNT*/, PROC_NO_TYPE, true /*modal*/, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
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
   SetMessageStatusBar( NULL_STRING );
}

//************************************************************************
bool AccInfoDlg::PreOk() 
{
   DString dstrTaxType, dstrPensionJuris;
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::TaxType, dstrTaxType,false );
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::PensionJuris, dstrPensionJuris,false );   
   dstrTaxType.strip();
   dstrPensionJuris.strip();
   DString creatingAccount;

   //get the state of the dialog
   getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::CREATING_ACCOUNT_FIELD,
                          creatingAccount );
   if( creatingAccount == YES ) return(true); // we do not pop up as pension plan in  NASU flow

	DString strMarket = DSTCommonFunctions::getMarket();
   if( dstrTaxType == AS_PENSION_PLAN && dstrOldTaxType != dstrTaxType && strMarket != MARKET_IDS::CANADA )
   {
      DString dstrAccountNum,dstrShrNum;
      getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::ACCOUNT_NUMBER_FIELD, dstrAccountNum );
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, dstrShrNum );

      setParameter( ASPENSIONPLANLIT::SHAREHOLDER_NUM, dstrShrNum);
      setParameter( ASPENSIONPLANLIT::ACCOUNT_NUM, dstrAccountNum );
      E_COMMANDRETURN ret = getParentProcess( )->invokeProcessFromChild( this,CMD_BPROC_AS_PENSION_PLAN,PROC_SUPPORT ); 
      if( ret != CMD_OK )
      { // we expect user create as pension plan here
         return(false);  
      }

   }

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

   if( ( dstWorkSession->isLIFLike (dstrTaxType) || dstrTaxType == I_( "R" ) ||
		 dstWorkSession->isLIRALike (dstrTaxType) || dstrTaxType == I_( "L" )) 
		 && ( dstrPensionJuris != NULL_STRING ) )
   {
      if( ( dstrOldTaxType != dstrTaxType ) || ( dstrOldPensionJuris != dstrPensionJuris ) )
      {
         DString dstrAccountNum;
         getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::ACCOUNT_NUMBER_FIELD, dstrAccountNum );
         setParameter( PENSION_INFO::ACCOUNT_NUM, dstrAccountNum );
         setParameter( PENSION_INFO::REFRESH, YES );
         E_COMMANDRETURN ret = getParentProcess( )->invokeProcessFromChild( this, CMD_BPROC_PENSION_INFO, PROC_SUPPORT ); 
         if( ret != CMD_OK )
         {
            return(false);  
         }
         //The user has click ok on the Pension Info.  We will set the old Pension Juris/TaxType to NULL_STRING
         //so that the Pension Info screen will always pop up now.  This is done to force the user
         //to verify the Pension information if he decides to cancel out on the confirmation screen.
         dstrOldPensionJuris = NULL_STRING;
         dstrOldTaxType = NULL_STRING;
      }
   }

   return(true);
   //AbstractBaseMainDlg::PostMessage( WM_COMMAND, IDOK );
}
//**********************************************************************
void AccInfoDlg::PostOk( bool /*bOkStatus*/ )
{
   DString accountNum;
   DString createAccount;

   getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::ACCOUNT_NUMBER_FIELD, accountNum );
   getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::CREATING_ACCOUNT_FIELD, createAccount );
   //set this params on the work session process
   setParameter( ACCINFOPROC::ACCOUNT_NUM, accountNum );
   setParameter( NASULIT::CREATING_ACCOUNT, createAccount );
}

//******************************************************************
BOOL AccInfoDlg::PreTranslateMessage( MSG* pMsg ) 
{
   BOOL isTranslated = FALSE;

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 )
   {
      if( GetFocus()== GetDlgItem( IDC_EDT_BROKER ) )
         PostMessage( UM_OPENBROKERLISTDLG );
      else if( GetFocus()== GetDlgItem( IDC_EDT_BRANCH ) )
      {
         //Rule: if repByBranch is Yes, F4 should work
         DString strRepByBranch, dstrHouseBroker;
         getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::REP_BY_BRANCH_FIELD, strRepByBranch );
         //getParent()->getField( this, BF::NullContainerId, ifds::HouseBroker, dstrHouseBroker );
         if( strRepByBranch == YES ) {
           // if ( dstrHouseBroker == NO )
               PostMessage( UM_OPENBRANCHLISTDLG );
         }
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_SALES_REP ) ) {         
         DString dstrHouseBroker;
         getParent()->getField( this, BF::NullContainerId, ifds::HouseBroker, dstrHouseBroker );
         if ( dstrHouseBroker == NO ) {
            _bAskCreateSalesRep = false;
            PostMessage( UM_OPENSLSREPLISTDLG );
         }
      }
   }

//   return isTranslated;
   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}


//******************************************************************
LRESULT AccInfoDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString brokerCode;

      GetControlText( IDC_EDT_BROKER, brokerCode );
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString brokerCode;

               getParameter( MFCAN_IP_PARAM::BROKER_CODE, brokerCode );
               if( brokerCode != NULL_STRING )
               {
//                  SetControlText( IDC_EDT_BROKER, brokerCode );
                  bool success = SetControlText( IDC_EDT_BROKER, brokerCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BROKER ));
                  if( !success && pBC )
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

/*************************************************************************************/
LRESULT AccInfoDlg::OpenBranchListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBranchListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString brokerCode;

      GetControlText(IDC_EDT_BROKER, brokerCode);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      //invoke the branch dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the branch code that the user selected from the branch list and 
               //set the field on the account object
               DString branchCode;

               getParameter( MFCAN_IP_PARAM::BRANCH_CODE, branchCode );
               if( !branchCode.empty() )
               {
//                  SetControlText( IDC_EDT_BRANCH, branchCode );
                  bool success = SetControlText( IDC_EDT_BRANCH, branchCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BRANCH ));
                  if ( !success && pBC )
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

//************************************************************************
LRESULT AccInfoDlg::OpenSlsRepListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg" ) );
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString brokerCode, branchCode;

      GetControlText( IDC_EDT_BROKER, brokerCode );
      setParameter( MFCAN_IP_PARAM::BROKER_CODE, brokerCode );
      GetControlText( IDC_EDT_BRANCH, branchCode );
      setParameter( MFCAN_IP_PARAM::BRANCH_CODE, branchCode );
      //invoke the agents dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_SLSREP, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the agent code that the user selected from the agents list and 
               //set the field on the account object
               DString slsrepCode, branchCode;

               getParameter(MFCAN_IP_PARAM::SALES_REP_CODE, slsrepCode);
               getParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);

               if( !slsrepCode.empty() )
               {
//                  SetControlText( IDC_EDT_SALES_REP, slsrepCode );
                  SetControlText( IDC_EDT_BRANCH, branchCode );
                  bool success = SetControlText( IDC_EDT_SALES_REP, slsrepCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_SALES_REP ));
                  if ( !success && pBC )
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
   _bAskCreateSalesRep = true;
   return(0);
}

//******************************************************************************
void AccInfoDlg::OnBtnEntity() 
{
   // TODO: Add your control notification handler code here
}

//******************************************************************************
void AccInfoDlg::OnBtnEntity2() 
{
   // TODO: Add your control notification handler code here
   E_COMMANDRETURN eRtn = CMD_OK;

   setParameter( ENTPROC::ACCOUNT_NUM, _strAccNo );
   eRtn = getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_ENTITY, PROC_SUPPORT );
//   eRtn = invokeCommand( getParent(), CMD_BPROC_ENTITY, PROC_NO_TYPE, true, NULL );
}

//******************************************************************************
void AccInfoDlg::OnBtnCOA() 
{
   // TODO: Add your control notification handler code here
   E_COMMANDRETURN eRtn = CMD_OK;

   setParameter( I_( "AccountNum" ), _strAccNo );
	setParameter( I_("LaunchCOA"), I_("LaunchFromAcctInfo") );
   eRtn = getParentProcess()->invokeProcessFromChild( getParent(), CMD_BPROC_COA, PROC_SUPPORT );
	//eRtn = invokeCommand( getParent(), CMD_BPROC_COA, PROC_NO_TYPE, true, NULL );

}
//******************************************************************************
void AccInfoDlg::OnBtnReset() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   getParent()->reset(this, IFASTBP_PROC::MFACCOUNT_CBO);
   doRefresh( this, NULL_STRING );
}

//******************************************************************************
void AccInfoDlg::setTitle()
{
   TRACE_METHOD( CLASSNAME, I_("setTitle"));

   DString strTitle;
   getParent()->getField( this, BF::NullContainerId, ACCINFOPROC::TITLE_FIELD, strTitle );
   SetCaption(strTitle);

}

//******************************************************************************
void AccInfoDlg::enableControls()
{
   DString strMarket = DSTCommonFunctions::getMarket();

   GetDlgItem( IDC_EDT_BROKER )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_EDT_BRANCH )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_EDT_SALES_REP )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_EDT_OTH_REF_NBR )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_EDT_ALT_ACC_NUM )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_INTERMEDIARY_ACCT_NBR )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_CMB_GROUP_NBR )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_INTERMEDIARY_CODE )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_CMB_TAX_TYPE )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_CMB_ACC_TYPE )->EnableWindow( _bAccCreated );

   if( strMarket != MARKET_IDS::LUXEMBOURG )
   {
      GetDlgItem( IDC_CMB_REC_TYPE )->EnableWindow( _bAccCreated );
      GetDlgItem( IDC_CMB_RRSPFees )->EnableWindow( _bAccCreated );
      GetDlgItem( IDC_CMB_PENS_JUR )->EnableWindow( _bAccCreated );
   }

   GetDlgItem( IDC_DTP_REG_DATE )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_CMB_STATUS )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_CMB_IN_TRUST_FOR )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_CMB_ESCROW )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_CMB_CURRENCY )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_CMB_REGISTRATION_COMPLETE )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_DTP_EFF_DATE )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( _bAccCreated );
   GetDlgItem( IDC_BTN_RESET )->EnableWindow( _bAccCreated );
   GetDlgItem( IDOK )->EnableWindow( _bAccCreated );
	GetDlgItem( IDC_BTN_COA )->EnableWindow( _bAccCreated ); 
   GetDlgItem( IDC_CMB_TAXMODEL )->EnableWindow( _bAccCreated );

   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      GetDlgItem( IDC_CMB_SOCIAL_CODE )->EnableWindow( _bAccCreated );
   }
}

//******************************************************************************
void AccInfoDlg::OnKillFocusSalesRep () {
   // 
   if ( !_bAskCreateSalesRep )
      return;
   //Lets not ask to create the sales rep if the sales rep is blank.
   DString dstrSalesRep;
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::Slsrep, dstrSalesRep );
   if ( dstrSalesRep.strip() == NULL_STRING )
      return;
   DString shouldAskForRep;

   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShouldAskForRep, shouldAskForRep );
   if( shouldAskForRep == YES )
   {
      CString noSlsrep;

      noSlsrep.LoadString( TXT_NO_SLSREP );

      int choice = AfxMessageBox( noSlsrep, MB_YESNO | MB_ICONQUESTION );

      if( choice == IDYES ) //should turn the create rep flag on
      {
         //turn this off first to trigger the doApplyChanges
         getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::CreateRep, NO );
         getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::CreateRep, YES );
         LoadControl( IDC_EDT_SALES_REP ); 

      }
      else if( choice == IDNO )
      {
         getParent()->setField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::CreateRep, NO );
      }
   }
}

//******************************************************************************
bool AccInfoDlg::GetDataForControl( UINT controlID,
                                    DString &strValueOut,
                                    bool bFormatted,
                                    int index ) const
{
   bool bReturn = false;
   
   DString str12319999;
   DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pDSTWorkSession->getDateInHostFormat (str12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, BF::HOST);

   if( controlID == IDC_TXT_EXEMPTION_END_DATE || 
       controlID == IDC_TXT_TAXABLE_TRUST_DATE ||
       controlID == IDC_TXT_OPENING_DATE )
   {
      DString fieldValue(NULL_STRING);
      strValueOut = NULL_STRING;
      const BFFieldId& bfFieldId = GetControl(controlID)->GetFieldID();

      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, bfFieldId, fieldValue, false );
      
      if(fieldValue.strip().upperCase().empty())
      {
         fieldValue = str12319999;
      }
      
      if(bFormatted)
      {
         BFDate date(fieldValue, BFDate::DATE_FORMAT::DF_MMDDCCYY );
         const ClientLocale& locale = ClientLocaleContext::get();
         const BFDate::DATE_FORMAT& fmt = getDateFormatFromClientLocale(locale);
         const DString dstrDateOut = date.get(fmt);
         if ( !dstrDateOut.empty() )
         {
            strValueOut += dstrDateOut;
         }
      }
      else
      {
         strValueOut += fieldValue;
      }

      bReturn = true;
   }

   return bReturn;
}

//*************************************************************************
BFDate::DATE_FORMAT AccInfoDlg::getDateFormatFromClientLocale(const ClientLocale& rLocale) const
{
   static const DString dstrConfiguration( I_( "DisplayMasks" ) );
   DString dstrKey = rLocale.getLocale() + I_( "-D" );

   DString mask = GetConfigValueAsString( ConfigManager::getApplication(), 
                                          dstrConfiguration,
                                          dstrKey );
   if( mask.size() == 0 )
   {
      static const DString dstrHostConfiguration( I_( "HostMasks" ) );
      static const DString dstrType( I_( "D" ) );
      DString dstrHostKey;
      dstrHostKey.append( dstrType );

      DString hostMask = GetConfigValueAsString( I_( "DICORE" ),
                                                 dstrHostConfiguration,
                                                 dstrHostKey );

      if( hostMask.size() == 0 )
      {
         return BFDate::DATE_FORMAT::DF_MMDDCCYY;
      }
      else
      {
         return inferMaskFormat( hostMask );
      }
   }
   else
   {
      return inferMaskFormat( mask );
   }
}

//*************************************************************************
BFDate::DATE_FORMAT AccInfoDlg::inferMaskFormat( const DString& dstrMask ) const
{
   // look for the dd|DD, the mm|MM, and the ccyy|CCYY|yyyy|YYYY
   int iDay = dstrMask.find( I_( "DD" ) );
   if( iDay == dstrMask.npos ) iDay = dstrMask.find( I_( "dd" ) );

   int iMonth = dstrMask.find( I_( "MM" ) );
   if( iMonth == dstrMask.npos ) iMonth = dstrMask.find( I_( "mm" ) );

   int iYear = dstrMask.find( I_( "CCYY" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "ccyy" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "YYYY" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "yyyy" ) );

   // if day, month, or year are not known then give up
   if( iDay == dstrMask.npos ||
       iMonth == dstrMask.npos ||
       iYear == dstrMask.npos )
   {
      return( BFDate::DATE_FORMAT::DF_NULL );
   }

   // what is the separator?
   bool bFS = false;
   bool bFD = false;
   if( dstrMask.find( I_( "/" ) ) != dstrMask.npos ) bFS = true;
   else if( dstrMask.find( I_( "-" ) ) != dstrMask.npos ) bFD = true;

   if( iYear < iMonth )
   {
      // it's ISO
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSISO );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDISO );
      return( BFDate::DATE_FORMAT::DF_ISO );
   }
   else if( iDay < iMonth )
   {
      // it's European format (dd/mm/yyyy)
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSEURO );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDEURO );
      return( BFDate::DATE_FORMAT::DF_EURO );
   }
   else if( iMonth < iDay && iDay < iYear )
   {
      // it's US format
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSUS );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDUS );
      return( BFDate::DATE_FORMAT::DF_US );
   }
   else
   {
      //unknown format! therefore forced it as mmddyyyy
      return( BFDate::DATE_FORMAT::DF_MMDDCCYY );
   }
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccInfoDlg.cpp-arc  $
 * 
 *    Rev 1.89   Jul 12 2012 11:12:08   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.88   Feb 17 2012 10:05:14   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.87   Feb 08 2012 20:49:56   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.86   Feb 07 2012 18:12:34   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.85   Nov 11 2011 15:47:56   jankovii
 * Fixed porfolio/plan stuff.
 * 
 *    Rev 1.84   Oct 07 2011 00:47:58   kitticha
 * PETP0183105 FN02 - Unclaimed Property Alberta.
 * 
 *    Rev 1.83   Oct 04 2011 18:25:42   dchatcha
 * P0186477 FN01 - GIA Enhancements, display validate portfolio fields based on environment functionality(UAF).
 * 
 *    Rev 1.82   Sep 30 2011 10:08:02   popescu
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.81   Sep 01 2011 18:52:36   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.80   Aug 04 2011 11:44:30   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.79   Nov 28 2008 13:49:58   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.78   Nov 25 2008 11:30:18   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.77   01 May 2008 13:58:24   kovacsro
 * PET2255 FN47 - New Ontario LIF - finalized
 * 
 *    Rev 1.76   15 Apr 2008 12:13:38   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.75   Oct 08 2007 12:17:38   smithdav
 * IN  1005517,1020252 - LRSP logic
 * 
 *    Rev 1.74   Jul 31 2007 11:30:56   kovacsro
 * PET 2372 FN02 - FDP-AIM KYC - added AccountClosingReason
 * 
 *    Rev 1.73   Jan 26 2006 12:04:38   popescu
 * Disable the COA button on the AccInfo screen if this is invoked from the  COA dialog
 * 
 *    Rev 1.72   Sep 15 2005 15:09:38   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.71   Jul 07 2005 16:15:24   ZHANGCEL
 * PET1141-FN05 -- Disable <COA> button when it is in NASU flow
 * 
 *    Rev 1.70   Jul 06 2005 11:00:44   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.69   Aug 11 2004 12:05:36   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.68   May 27 2004 17:22:28   YINGBAOL
 * PTS10027992:remove restrict for brokercode, branch code and salesrep to CBO.
 * 
 *    Rev 1.67   Mar 15 2004 17:52:00   HERNANDO
 * PET965 FN11 - Changed to use Historical Info instead of Historical Account.
 * 
 *    Rev 1.66   Mar 12 2004 11:46:40   YINGBAOL
 * PTS10027992: Limit BrokeCode, BranchCode and SalsRep to 6 characters.
 * 
 *    Rev 1.65   Nov 20 2003 10:03:28   HSUCHIN
 * PTS 10024105 - Enable Branch search for house brokers.
 * 
 *    Rev 1.64   Nov 10 2003 11:45:46   ZHANGCEL
 * PTS ticket 10023790 : Solve the title bar display issue
 * 
 *    Rev 1.63   Oct 27 2003 16:30:28   ZHANGCEL
 * PTS ticket 10023250:(1) Fix crash when ManualAccount is Yes; (2) Show ShareHolder number on the title bar
 * 
 *    Rev 1.62   Oct 22 2003 15:50:00   FENGYONG
 * PTS 10023236 - PensionlegCode not set to novalidate
 * 
 *    Rev 1.61   Sep 12 2003 15:20:30   HSUCHIN
 * PTS 10021247 - Fixed crash for Lux Market due to dialog loading controls not found on the Lux resources.
 * 
 *    Rev 1.60   Aug 22 2003 10:46:14   FENGYONG
 * enable entity button when younthpotfolio was choosed so client can set up other or ITF
 * 
 *    Rev 1.59   Aug 20 2003 17:58:12   HSUCHIN
 * bug fix for create sales rep
 * 
 *    Rev 1.58   Aug 19 2003 09:10:24   HSUCHIN
 * agent/branch searches are no longer allowed when a house broker is selected.
 * 
 *    Rev 1.57   Aug 11 2003 17:19:56   FENGYONG
 * remove some Addtional info setfield
 * 
 *    Rev 1.56   Jul 30 2003 11:27:16   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.55   Jul 21 2003 13:50:14   ZHANGCEL
 * PTS ticket 10013951: As pension plan no alowed for the Canada market
 * 
 *    Rev 1.54   Jul 10 2003 22:21:24   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.53   Apr 15 2003 12:08:32   sanchez
 * Ticket 10015035 sync up with version 1.49.11
 * 
 *    Rev 1.52   Mar 21 2003 18:30:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.51   Mar 05 2003 11:50:40   HSUCHIN
 * sync up with 1.49.1.0
 * 
 *    Rev 1.50   Feb 26 2003 10:35:56   PURDYECH
 * Style changes.
 * 
 *    Rev 1.49   Dec 06 2002 10:59:52   YINGBAOL
 * PRIF Enhancement
 * 
 *    Rev 1.48   Nov 05 2002 10:41:20   HERNANDO
 * Removed AMS Controls and function.
 * 
 *    Rev 1.47   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.46   Oct 04 2002 11:31:50   HSUCHIN
 * disable reset btn during NASU
 * 
 *    Rev 1.45   Aug 09 2002 16:15:14   HSUCHIN
 * launch Pension info dlg on PreOk when tax type changes and also when pension juris changes
 * 
 *    Rev 1.44   Aug 09 2002 09:47:06   HSUCHIN
 * enhancment to launch pension info when tax type is changed to LIRA etc..
 * 
 *    Rev 1.43   Jun 25 2002 15:15:58   ZHANGCEL
 * PTS 10008253: bug fix for nable to select taxation type fields correctly
 * 
 *    Rev 1.42   Jun 24 2002 16:16:58   HERNANDO
 * Display Account Opening Date for Lux.
 * 
 *    Rev 1.41   08 Jun 2002 15:24:46   HERNANDO
 * Added Account Opening Date.
 * 
 *    Rev 1.40   May 23 2002 10:39:34   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.39   Apr 25 2002 13:41:04   YINGBAOL
 * Fix SalesRep PTS 10007782
 * 
 *    Rev 1.38   18 Apr 2002 15:58:02   KOVACSRO
 * Removed StopSWP check from NASU.
 * 
 *    Rev 1.37   17 Apr 2002 17:00:58   KOVACSRO
 * Added StopSWP enhancement.
 * 
 *    Rev 1.36   27 Mar 2002 20:00:48   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.35   Jan 28 2002 11:27:20   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.34   Jan 09 2002 16:50:28   YINGBAOL
 * in NASU flow, AS pension plan should not pop up
 * 
 *    Rev 1.33   Jan 07 2002 09:50:18   YINGBAOL
 * User changes Taxtype from otherr  to As Pension Plan, 
 * when hit OK, launch As Pension Plan automatically
 * 
 *    Rev 1.32   Dec 20 2001 13:47:44   YINGBAOL
 * fix acountnumber AMS Code display issue
 * 
 *    Rev 1.31   Dec 04 2001 16:13:34   ZHANGCEL
 * Fixed the "ESC" button not working problem
 * 
 *    Rev 1.30   Nov 28 2001 12:28:26   JANKAREN
 * Added AMSCode
 * 
 *    Rev 1.29   Nov 14 2001 15:34:10   YINGBAOL
 * code clean up
 * 
 *    Rev 1.28   Nov 09 2001 12:07:00   YINGBAOL
 * fix GroupCode
 * 
 *    Rev 1.27   Oct 11 2001 15:35:22   YINGBAOL
 * fix focus
 * 
 *    Rev 1.26   Sep 13 2001 17:26:34   ZHANGCEL
 * Code clean
 * 
 *    Rev 1.25   Jul 04 2001 13:19:50   HERNANDO
 * Removed reference to IDC_CMB_REC_TYPE, IDC_CMB_RRSPFees, and IDC_CMB_PENS_JUR for Luxembourg.
 * 
 *    Rev 1.24   25 May 2001 16:09:58   HSUCHIN
 * Work session restructuring bug fix 
 * 
 *    Rev 1.23   25 May 2001 16:04:46   HSUCHIN
 * sync up with 1.21.1.3
 * 
 *    Rev 1.21.1.3   Apr 25 2001 14:30:30   OLTEANCR
 * create account in manual mode - fixed OK button issue
 * 
 *    Rev 1.21.1.2   Apr 25 2001 14:20:30   DINACORN
 * Fix bug for Japan market (IDC_CMB_SOCIAL_CODE)
 * 
 *    Rev 1.21.1.1   Apr 23 2001 14:50:22   OLTEANCR
 * for IDC_EDT_ACC_NUM call SetAllowedChars(...)
 * 
 *    Rev 1.21.1.0   Apr 18 2001 17:13:42   OLTEANCR
 * manual create account - changed logic; added new function enableControls( )
 * 
 *    Rev 1.21   06 Apr 2001 11:36:34   KOVACSRO
 * Added F4 perm. check.
 * 
 *    Rev 1.20   Mar 30 2001 16:39:46   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.19   29 Mar 2001 16:09:26   KOVACSRO
 * perm. check.
 * 
 *    Rev 1.18   27 Mar 2001 16:43:06   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.17   18 Mar 2001 14:28:06   JANKAREN
 * Add Social Code
 * 
 *    Rev 1.16   Feb 12 2001 14:52:14   YINGBAOL
 * retrieve market from databroker instead of registry
 * 
 *    Rev 1.15   Feb 01 2001 15:45:24   DINACORN
 * Synchronization M3 / C4
 * 
 *    Rev 1.14   Dec 01 2000 14:38:56   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.13   Nov 08 2000 16:53:18   ZHANGCEL
 * Reset the CreateRep
 * 
 *    Rev 1.12   Oct 18 2000 14:55:06   WINNIE
 * Take branch code
 * 
 *    Rev 1.11   Sep 29 2000 13:29:16   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.10   Sep 23 2000 15:54:32   DINACORN
 * Disabled the F4 Branch search if strRepByBranch == NO;  Modified the maximum number of digits for some fields; Added setTitle() method;
 * 
 *    Rev 1.9   Sep 01 2000 14:34:10   YINGBAOL
 * impleament logic for enable entity button
 * 
 *    Rev 1.8   Aug 23 2000 12:17:22   DINACORN
 * Fixed the bug at brokerCode at F4 search
 * 
 *    Rev 1.7   Aug 18 2000 11:58:44   PETOLESC
 * Fixed call to entity process.
 * 
 *    Rev 1.6   Aug 16 2000 10:41:12   DINACORN
 * Added Controls for Group; added OnBtnReset() method
 * 
 *    Rev 1.5   Jul 27 2000 17:18:58   DINACORN
 * Added function OnBtnEntity
 * 
 *    Rev 1.4   May 16 2000 15:20:24   HSUCHIN
 * removed user define messages. l
 * 
 *    Rev 1.3   Apr 05 2000 10:02:38   DT24433
 * removed unused GIC header
 * 
 *    Rev 1.2   Mar 30 2000 13:19:48   HSUCHIN
 * M2 sync up
 * 
 *    Rev 1.1   Mar 13 2000 16:43:22   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.0   Feb 15 2000 11:01:04   SMITHDAV
 * Initial revision.
// 
//    Rev 1.62   Feb 01 2000 14:22:12   POPESCUS
// set the length to some gui fields
// 
//    Rev 1.61   Jan 28 2000 10:38:24   POPESCUS
// fixed tabbing
// 
//    Rev 1.60   Jan 28 2000 09:55:00   VASILEAD
// took out m_hAccel
// 
//    Rev 1.59   Jan 25 2000 17:14:42   POPESCUS
// fixes for validation of a new account
// 
//    Rev 1.58   Jan 23 2000 18:48:48   POPESCUS
// changes related to creating a slsrep on the fly
// 
//    Rev 1.57   Jan 21 2000 11:11:54   POPESCUS
// the user can change the account number and the shareholder number
// 
//    Rev 1.56   Jan 19 2000 11:06:30   WINNIE
// add broker screen
// 
//    Rev 1.55   Jan 14 2000 09:10:58   POPESCUS
// fixed some validation issues and cloning of a new account
// 
//    Rev 1.54   Jan 11 2000 14:10:12   POPESCUS
// for relealse
// 
//    Rev 1.53   Jan 11 2000 08:41:44   POPESCUS
// fixes and validation
// 
//    Rev 1.52   Jan 09 2000 19:11:24   POPESCUS
// bug fixes?
// 
//    Rev 1.51   Jan 07 2000 18:20:36   POPESCUS
// fixes in trxns
// 
//    Rev 1.50   Jan 07 2000 15:55:50   POPESCUS
// just checking in...
// 
//    Rev 1.49   Jan 06 2000 12:52:16   POPESCUS
// fixes for validation
// 
//    Rev 1.48   Jan 06 2000 09:58:38   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.47   Dec 31 1999 13:16:08   POPESCUS
// validations, fixes and misc
// 
//    Rev 1.46   Dec 24 1999 14:18:06   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.45   Dec 23 1999 14:43:22   POPESCUS
// invoke the process that deal with the F4 mechanism as support processes
// 
//    Rev 1.44   Dec 23 1999 12:59:34   POPESCUS
// added logic for supporting the F4 mechanism
// 
//    Rev 1.43   Dec 22 1999 12:29:08   POPESCUS
// validations and misc
// 
//    Rev 1.42   Dec 21 1999 14:15:02   POPESCUS
// cleanup the code, validations and misc
*/

