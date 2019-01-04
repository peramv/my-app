// AllocationsDlg.cpp : implementation file
//

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
// ^FILE   : AllocationsDlg.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 09/17/99
//
//           Shaobo Huang        MSDW M3  March, 2000
//				 Yingbao					Automatic transfer Allocation
//											 		
// ----------------------------------------------------------
//
// ^CLASS    : AllocationsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the AllocationsDlg dialog
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <bfproc\abstractprocess.hpp>
#include "allocationsdlg.h"
#include <ifastbp\allocationsprocessincludes.h>
#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <uibase\dstedit.h>
#include <uibase\dstdatetime.h>
#include <uibase\dstoledatetime.h>
#include <uibase\dststatic.h>
#include <ifastbp\splitcommissionsprocessincludes.h>
#include <ifastbp\identaccprocessincludes.h>
#include <math.h>
#include <assert.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\allocationsprocess.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SPLITCOMMISSION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_SIMPLE_ALLOCATION;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AllocationsDlg > dlgCreator( CMD_GUI_SIMPLE_ALLOCATION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AllocationsDlg" );
   const I_CHAR * const LV_SHR_ALLOC = I_( "lvShrAlloc" );
   const I_CHAR * const LV_ACCT_ALLOC = I_( "lvAcctAlloc" );
   const I_CHAR * const LV_FUND_ALLOC = I_( "lvFundAlloc" );
   const I_CHAR * const LV_SYSTEMATIC = I_( "lvSystematic" );
   const I_CHAR * const LV_SYS_FUND_ALLOC = I_( "lvSysFundAlloc" );
   const I_CHAR * const LV_AT_FUND_ALLOC = I_( "lvAutoFundAlloc" );

   const I_CHAR * const LV_RRIF_LIF_ALLOC = I_( "lvRRIF_LIF_Alloc" );

   // Automatic Transfer
   const I_CHAR * const LV_AUTO_SYS_FUND_ALLOC = I_( "lvAutoSysFundAlloc" );
   const I_CHAR * const ONE_TIME = I_( "OneTime" );
   const I_CHAR * const DEFAULT = I_( "Default" );
   const I_CHAR * const SHR_LEVEL = I_( "1" );
   const I_CHAR * const ACCT_LEVEL = I_( "2" );
   const I_CHAR * const FUND_LEVEL = I_( "3" );
   const I_CHAR * const ONE_HUNDRED = I_( "100.0000" );
   const I_CHAR * const ONE_HUNDRED_PERCENT = I_( "100.0000%" );
   const I_CHAR * const FILLACCTAXCMB = I_( "fillAccTaxCMB" );
   const I_CHAR * const DISPLAYALLOCATIONS = I_( "displayAllocations" );
   const I_CHAR * const DISPLAYALLOCATIONGROUPS = I_( "displayAllocationGroups" );

   const I_CHAR * const BLANK = I_( " " );
   const I_CHAR * const DASH = I_( " - " );
   const I_CHAR * const ALLOCATIONTYPE = I_("AllocationType");

   const I_CHAR * const SHAREHOLDER_NBR = I_( " Shareholder Number: " );
   const I_CHAR * const TRANSACTION_NBR = I_( " Transaction Nbr: " );
   const I_CHAR * const ONRBDEFAULT = I_( "OnRbDefault" );
   const I_CHAR * const ONRBONETIME = I_( "OnRbOneTime" );
   const I_CHAR * const ONRBONETIMETRADE = I_( "OnRbOneTimeTrade" );

   const I_CHAR * const ONRBAUTOTRANSFER = I_( "OnRbAutoTransfer" );
   const I_CHAR * const TAX_TYPE = I_( "TaxType" );
   const I_CHAR * const TRANS_TYPE = I_( "TransType" );
   const I_CHAR * const FUND_CODE = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE = I_( "ClassCode" );
   const I_CHAR * const FUNDNUMBER = I_( "FundNumber" );
   const I_CHAR * const FUND_NUMBER = I_( "Baycom" );
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const BANK_ACCT_CURRENCY = I_( "BankAcctCurrency" );
   const I_CHAR * const SETTLE_CURRENCY = I_( "SettleCurrency" );
   const I_CHAR * const NEWPREFIX = I_( "999" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const EFFECTIVE_DATE = I_( "EffectiveDate" );

   const I_CHAR * const SHR_NUM        = I_( "ShrNum" );
   const I_CHAR * const ACCT_NUM       = I_( "AccountNum" );
   const I_CHAR * const FOREIGN_CONTENT_REBALANCING= I_( "XS" );
   const I_CHAR * const MANAGEMENT_FEE_CODE        = I_( "MF" );
   const I_CHAR * const REBALANCING_CODE           = I_( "RB" );
   const UINT TRADE_ALLOCATIONS_ONLY    = 25000;
   const UINT DEFAULT_ALLOCATIONS_ONLY  = 25001;
}

namespace CND
{//Conditionsused
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ModPerm;
   extern CLASS_IMPORT const BFTextFieldId AddPerm;
   extern CLASS_IMPORT const BFTextFieldId DelPerm;
   extern CLASS_IMPORT const BFTextFieldId AllocationsAllowed;
   extern CLASS_IMPORT const BFTextFieldId DefaultAllocOverride;
   extern CLASS_IMPORT const BFTextFieldId PACSWPOverride;
   extern CLASS_IMPORT const BFTextFieldId FELCommOnGrant;
   extern CLASS_IMPORT const BFTextFieldId LV_DefaultAllocFundHeading2;
   extern CLASS_IMPORT const BFDecimalFieldId FELComm;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const DEFAULT_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTOMATIC_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_INFO;// or RIF_LIF_LRIF_ALLOC_INFO ????
   extern CLASS_IMPORT I_CHAR * const TRADING_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const TRADING_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRADING_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const TRANSACTION_HISTORY;
   extern CLASS_IMPORT I_CHAR * const AMS_MIX_OVERRIDE;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
	extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
}

/////////////////////////////////////////////////////////////////////////////
// AllocationsDlg dialog

AllocationsDlg::AllocationsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AllocationsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( 0 )
, m_uiClassCodeDialogItem( 0 )
, bRRIF(false)
, _blNewShrItem(false)
{
   //{{AFX_DATA_INIT(AllocationsDlg)
   m_rbUsage = -1;
   m_bReplaceAsDefault = FALSE;
   //}}AFX_DATA_INIT

   m_lOneTimeList       = BF::AllContainerIds;
   m_lOneTimeAllocList  = BF::AllContainerIds;
}

//******************************************************************************

void AllocationsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AllocationsDlg)
   DDX_Radio(pDX, IDC_RB_DEFAULT, m_rbUsage);
   DDX_Check(pDX, IDC_CHK_REPLACE, m_bReplaceAsDefault);
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(AllocationsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AllocationsDlg)
ON_COMMAND(ID_ACCEL_ALLOC_TYPE, OnAccelAllocType)
ON_COMMAND(ID_ACCEL_FUND, OnAccelFund)
ON_BN_CLICKED(IDC_RB_DEFAULT, OnRbDefault)
ON_BN_CLICKED(IDC_RB_ONE_TIME, OnRbOneTime)
ON_BN_CLICKED(IDC_BTN_ADD_ACCT_ALLOC, OnBtnAddAcctAlloc)
ON_BN_CLICKED(IDC_BTN_ADD_FUND_ALLOC, OnBtnAddFundAlloc)
ON_BN_CLICKED(IDC_BTN_ADD_SHR_ALLOC, OnBtnAddShrAlloc)
ON_BN_CLICKED(IDC_BTN_DELETE_ACCT_ALLOC, OnBtnDeleteAcctAlloc)
ON_BN_CLICKED(IDC_BTN_DELETE_FUND_ALLOC, OnBtnDeleteFundAlloc)
ON_BN_CLICKED(IDC_BTN_DELETE_SHR_ALLOC, OnBtnDeleteShrAlloc)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_COMMAND(ID_ACCEL_ACCT, OnAccelAcct)
ON_BN_CLICKED(IDC_CHK_REPLACE, OnChkReplace)
ON_BN_CLICKED(IDC_RB_AUTO_TRANSFER, OnRbAutoTransfer)
ON_BN_CLICKED(IDC_BTN_AUTO_ADD_SHR_ALLOC, OnBtnAutoAddAcctAlloc)
ON_BN_CLICKED(IDC_BTN_AUTO_DELETE_SHR_ALLOC, OnBtnAutoDeleteAcctAlloc)
ON_BN_CLICKED(IDC_RB_ONE_TIME_TRADE, OnRbOneTimeTrade)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_MESSAGE( WM_LAUNCH_IDENT_ACC, OpenIdentifyAccountsDlg )  

ON_CBN_SELCHANGE(IDC_CMB_ACCT_TAX, OnSelchangeCmbAcctTax)
ON_BN_CLICKED(IDC_BTN_SPLIT_COM, OnBtnSplitCom)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AllocationsDlg message handlers

//******************************************************************************

SEVERITY AllocationsDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   getParameter(MFCAN_IP_PARAM::TRANS_NUM, 
      m_dstrTransNum);
   getParameter(MFCAN_IP_PARAM::TRANS_TYPE, 
      _strTransType);
   getParameter(MFCAN_IP_PARAM::LIST_KEY, 
      _strAllocationListKey);
   return NO_CONDITION;
}

//******************************************************************************

BOOL AllocationsDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   GetDlgItem( IDC_BTN_RESET )->ShowWindow( SW_SHOW );

   CString str;
   str.LoadString( TXT_BTN_CANCEL );
   GetDlgItem( IDCANCEL )->SetWindowText( str );

   if( !m_hAccel )
      m_hAccel = LoadAccelerators(NULL, MAKEINTRESOURCE(IDR_ACCEL_ALLOCATIONS));

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void AllocationsDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG ); 

   getParent()->getField( this, BF::NullContainerId, ifds::AllocationType, m_dstrAllocType, true );
   if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME )
      m_strTransType = _strTransType;
   else if( m_dstrAllocType == ALLOCATIONSPROC::TRADE_ONE_TIME )
      m_strTradeTransType = _strTransType;
   else if( m_dstrAllocType == ALLOCATIONSPROC::RRIF_LIF_LRIF_ONE_TIME )
      bRRIF = true;

   SetUserAccesFuncCode();

   if( m_dstrAllocType == ALLOCATIONSPROC::SHAREHOLDER_DEFAULT )
   {
      m_rbUsage = 0;
      GetDlgItem(IDC_RB_ONE_TIME)->EnableWindow(false);
      GetDlgItem(IDC_RB_AUTO_TRANSFER)->EnableWindow(false);
      GetDlgItem(IDC_RB_ONE_TIME_TRADE)->EnableWindow(false);

   }
   else if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME || 
            m_dstrAllocType == ALLOCATIONSPROC::TRADE_ONE_TIME ||
            m_dstrAllocType == ALLOCATIONSPROC::RRIF_LIF_LRIF_ONE_TIME )
   {

      if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME )
      {
         m_rbUsage = 1;
         m_lOneTimeList      = IFASTBP_PROC::SYSTEMATIC_LIST;
         m_lOneTimeAllocList = IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST;
         GetDlgItem(IDC_RB_ONE_TIME_TRADE)->EnableWindow(false);
         CString cTitle;
         cTitle.LoadString(IDS_ONE_TIME_SYSTEMATIC);
         dynamic_cast<CWnd* >( GetDlgItem(IDC_RB_ONE_TIME) )->SetWindowText( cTitle );
      }
      else if( m_dstrAllocType == ALLOCATIONSPROC::TRADE_ONE_TIME )
      {
         m_rbUsage = 3;//new usage for this screen - trade alloc. will not share any more systematic and RIF layout
         m_lOneTimeList      = IFASTBP_PROC::TRADES_LIST;
         m_lOneTimeAllocList = IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST;
         GetDlgItem(IDC_RB_ONE_TIME)->EnableWindow(false);
      }
      else if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA && isRRifAlloction() )
      {
         m_rbUsage = 1;
         //should be changed later, decided by the lauching screen ?????
         m_lOneTimeList      = IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST;
         m_lOneTimeAllocList = IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST;
         GetDlgItem(IDC_RB_ONE_TIME_TRADE)->EnableWindow(false);
         CString cTitle;
         cTitle.LoadString(IDS_ONE_TIME_RRIF);
         dynamic_cast<CWnd* >( GetDlgItem(IDC_RB_ONE_TIME) )->SetWindowText( cTitle );

      }
      GetDlgItem(IDC_RB_AUTO_TRANSFER)->EnableWindow(false);

   }
   else if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER )
   {
      GetDlgItem( IDC_RB_ONE_TIME )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_RB_ONE_TIME_TRADE )->ShowWindow( SW_HIDE );

      //    m_lOneTimeList      = ALLOCATIONSPROC::SYSTEMATIC_LIST;
      // should be AcctAtlist
      //    m_lOneTimeAllocList = ALLOCATIONSPROC::SYSTEMATIC_ALLOCATIONS_LIST;
      m_rbUsage = 2;
   }
   else
      assert( 0 );

   //permission check stuff
   addBtnAddForPermissionCheck(IDC_BTN_ADD_SHR_ALLOC, IDC_LV_SHR_ALLOC);
   addBtnAddForPermissionCheck(IDC_BTN_AUTO_ADD_SHR_ALLOC, IDC_LV_AUTO_SHR_ALLOC);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_ACCT_ALLOC, IDC_LV_SYSTEMATIC);
   if( (m_rbUsage == 0) || (m_rbUsage == 3) )
      addBtnAddForPermissionCheck(IDC_BTN_ADD_FUND_ALLOC, IDC_LV_FUND_ALLOC);
   else
      addBtnAddForPermissionCheck(IDC_BTN_ADD_FUND_ALLOC, IDC_LV_SYS_FUND_ALLOC);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_SHR_ALLOC, IDC_LV_SHR_ALLOC);
   addBtnDeleteForPermissionCheck(IDC_BTN_AUTO_DELETE_SHR_ALLOC, IDC_LV_AUTO_SHR_ALLOC);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_ACCT_ALLOC, IDC_LV_ACCT_ALLOC);
   if( (m_rbUsage == 0) || (m_rbUsage == 3) )
      addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_FUND_ALLOC, IDC_LV_FUND_ALLOC);
   else
      addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_FUND_ALLOC, IDC_LV_SYS_FUND_ALLOC);


   setupDefaultControls();
   setupOnetimeATControls();

   DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::Percentage );

   int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );

   DSTEdit *edtPercent = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_ACCT_PRC ) );

   edtPercent->SetMaxCharNum( dstrPercentageMask.length() );//probably redundant
   edtPercent->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
                                               dstrPercentageMask.length() - iDecimalPointPos - 1 );
   DSTEdit *edtPercentDet = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_FUND_PERCENT ) );

   edtPercentDet->SetMaxCharNum( dstrPercentageMask.length() );//probably redundant
   edtPercentDet->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
                                                  dstrPercentageMask.length() - iDecimalPointPos - 1 );

   showHideFrontEndLoadCommissionControls();
//Refresh the list 
   doRefresh(NULL, NULL);
}

//-----------------------------------------------------------------------------
// setup the controls for Default allocations
//
void AllocationsDlg::setupDefaultControls()
{
   //List controls
   AddListControl( CLASSNAME, IDC_LV_SHR_ALLOC, LV_SHR_ALLOC, ifds::LV_DefaultAllocShrHeading, 
                   IFASTBP_PROC::SHR_ALLOCATIONS_LIST, 0, true );
   AddListControl( CLASSNAME, IDC_LV_ACCT_ALLOC, LV_ACCT_ALLOC,ifds::LV_DefaultAllocAcctHeading, 
                   IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, IDC_LV_SHR_ALLOC, true);

   /* Check generic controls for Add correct DefaultAllocFundHeading and Controls */
   if( isFELCommApplicable() )
   {
      //show FEL Commission fields
	  AddListControl( CLASSNAME, IDC_LV_FUND_ALLOC, LV_FUND_ALLOC, ifds::LV_DefaultAllocFundHeading2,
                      IFASTBP_PROC::FUND_ALLOCATIONS_LIST, IDC_LV_ACCT_ALLOC, true);
	  	  
   }
   else
   {	  
      AddListControl( CLASSNAME, IDC_LV_FUND_ALLOC, LV_FUND_ALLOC, ifds::LV_DefaultAllocFundHeading,
                      IFASTBP_PROC::FUND_ALLOCATIONS_LIST, IDC_LV_ACCT_ALLOC, true);
   }
   
   AddControl( CTRL_COMBO, IDC_CMB_ALLOC_TYPE, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, 
               ifds::TransType,CTRLFLAG_INITCOMBO_BY_SUB_LIST, DEFAULT_ALLOCATIONS_ONLY );
   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE,IFASTBP_PROC::SHR_ALLOCATIONS_LIST, 
               ifds::EffectiveDate, 0, DEFAULT_ALLOCATIONS_ONLY);//IDC_LV_SHR_ALLOC
   ConnectControl( IDC_DTP_EFF_DATE, true );
   //EnableControl( IDC_DTP_EFF_DATE, false );

   AddControl( CTRL_COMBO, IDC_CMB_ACCT_TAX,IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, 
               ifds::AccountNum,CTRLFLAG_MANUAL_INIT, DEFAULT_ALLOCATIONS_ONLY );

   AddControl( CTRL_EDIT, IDC_EDT_ACCT_PRC,IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, 
               ifds::AllocPercentage, 0, IDC_LV_ACCT_ALLOC );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ACCT_PRC))->SetAllowedChars(I_("0123456789."));

   AddControl( CTRL_STATIC, IDC_TXT_ACCT_TOTAL_PRC_VAL, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD, IDC_LV_ACCT_ALLOC );
/*
  AddControl( CTRL_COMBO, IDC_CMB_FUND, ALLOCATIONSPROC::FUND_ALLOCATIONS_LIST, DBR::FundCode, 
          CTRLFLAG_MANUAL_INIT, IDC_LV_FUND_ALLOC );
  AddControl( CTRL_COMBO, IDC_CMB_CLASS, ALLOCATIONSPROC::FUND_ALLOCATIONS_LIST, DBR::ClassCode, 
          CTRLFLAG_MANUAL_INIT, IDC_LV_FUND_ALLOC );
*/

   AddControl( CTRL_EDIT, IDC_EDT_FUND_NUMBER, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::ToFundNumber, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_FUND_ALLOC );
   AddControl( CTRL_EDIT, IDC_EDT_FUND, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::FundCode, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_FUND_ALLOC );
   AddControl( CTRL_EDIT, IDC_EDT_CLASS, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::ClassCode, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_FUND_ALLOC );

   AddControl( CTRL_EDIT, IDC_EDT_FUND_PERCENT,IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::AllocPercentage,0,IDC_LV_FUND_ALLOC );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FUND_PERCENT))->SetAllowedChars(I_("0123456789."));

   AddControl( CTRL_STATIC, IDC_TXT_FUND_TOTAL_PRC_VAL, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_COMBO, IDC_CMB_FUND_GROUP,IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, 
               ifds::FundGroup,CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_ALLOC );
}

//------------------------------------------------------------------------------
//	One Time Allocation(Systematic, RRIF(Canadian), Trade ... ) and AT 
//
void AllocationsDlg::setupOnetimeATControls()
{
   //Common for both OneTime and AT

   if( m_rbUsage == 2 ) //AT
   {      
      AddListControl( CLASSNAME, IDC_LV_SYS_FUND_ALLOC, LV_SYS_FUND_ALLOC, ifds::NullFieldId, BF::NullContainerId, IDC_LV_AUTO_SHR_ALLOC, true );
   }
   else
   {
      AddListControl( CLASSNAME, IDC_LV_SYS_FUND_ALLOC, LV_SYS_FUND_ALLOC, ifds::NullFieldId, BF::NullContainerId, IDC_LV_SYSTEMATIC, true);
   }

   AddControl( CTRL_EDIT, IDC_EDT_SYS_FUND_NUMBER, IFASTBP_PROC::AT_FUND_TRANS_LIST,
               ifds::ToFundNumber, 0, IDC_LV_SYS_FUND_ALLOC );
   AddControl( CTRL_EDIT, IDC_EDT_SYS_FUND, IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::FundCode, 0, IDC_LV_SYS_FUND_ALLOC );
   AddControl( CTRL_EDIT, IDC_EDT_SYS_CLASS,IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::ClassCode, 0, IDC_LV_SYS_FUND_ALLOC );

   AddControl( CTRL_EDIT, IDC_EDT_SYS_FUND_PERCENT,IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::Percentage,0, IDC_LV_SYS_FUND_ALLOC );
   DString dstrPercentageMask = DSTCommonFunctions::getRawMask( ifds::Percentage );
   int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );
   DSTEdit *edtPercent = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_SYS_FUND_PERCENT ) );
   edtPercent->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
                                               dstrPercentageMask.length() - iDecimalPointPos - 1 );

   AddControl( CTRL_EDIT, IDC_EDT_TRADE_FUND_AMT,IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST,ifds::AllocAmount, 0, TRADE_ALLOCATIONS_ONLY );//used only for trade one time alloc
   AddControl( CTRL_EDIT, IDC_EDT_FUND_AMT,IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::AllocAmount,0, IDC_LV_SYS_FUND_ALLOC );
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FUND_AMT))->SetAllowedChars(I_("0123456789."));

   AddControl( CTRL_STATIC, IDC_TXT_FUND_TOTAL_AMT_VAL, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD );

   AddControl( CTRL_STATIC, IDC_TXT_FUND_TOTAL_SYS_PRC_VAL, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD );

   //One Time Allocation Specific
   AddListControl( CLASSNAME, IDC_LV_SYSTEMATIC, LV_SYSTEMATIC, ifds::NullFieldId, BF::NullContainerId, 0, true, LISTFLAG_NOT_AUTO_ADD );

   //Automatic Transfer Specific
   AddListControl( CLASSNAME, IDC_LV_AUTO_SHR_ALLOC, LV_AUTO_SYS_FUND_ALLOC, ifds::AutoTransferAllocHeadingSet, 
                   IFASTBP_PROC::AT_ACCT_TRANS_LIST, 0, true );


   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_EDIT, IDC_EDT_AUTO_ACCT_TAX, IFASTBP_PROC::AT_ACCT_TRANS_LIST,ifds::AllocAccountNum,
                  0,IDC_LV_AUTO_SHR_ALLOC );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      AddControl( CTRL_COMBO, IDC_CMB_AUTO_ACCT_TAX, IFASTBP_PROC::AT_ACCT_TRANS_LIST,ifds::AllocAccountNum,
                  CTRLFLAG_MANUAL_INIT,IDC_LV_AUTO_SHR_ALLOC );
   }
   AddControl( CTRL_EDIT, IDC_EDT_AUTO_ACCT_PRC,IFASTBP_PROC::AT_ACCT_TRANS_LIST, 
               ifds::Percentage,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_AUTO_SHR_ALLOC );

   AddControl( CTRL_EDIT, IDC_EDT_AUTO_FUND_AMT,IFASTBP_PROC::AT_ACCT_TRANS_LIST, 
               ifds::AllocAmount,CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_LV_AUTO_SHR_ALLOC );

   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_AUTO_ACCT_PRC))->SetAllowedChars(I_("0123456789."));
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_AUTO_FUND_AMT))->SetAllowedChars(I_("0123456789."));


   AddControl( CTRL_STATIC, IDC_TXT_AUTO_FUND_TOTAL_AMT_VAL,BF::NullContainerId, 
               ifds::NullFieldId,CTRLFLAG_GUI_FIELD,IDC_LV_AUTO_SHR_ALLOC );

   AddControl( CTRL_STATIC, IDC_TXT_AUTO_ACCT_TOTAL_PRC_VAL,BF::NullContainerId, 
               ifds::NullFieldId,CTRLFLAG_GUI_FIELD,IDC_LV_AUTO_SHR_ALLOC );
   AddControl( CTRL_EDIT, IDC_EDIT_ACC_NUM, 0, TRADE_ALLOCATIONS_ONLY );

   CString cstrLabel1,cstrLabel2,cstrLabel3;
   cstrLabel1.LoadString(TXT_ACCOUNT_NBR);
   cstrLabel3.LoadString(IDS_LBL_SEMICOL);
   if( strMarket == MARKET_IDS::JAPAN )
   {
      cstrLabel2.LoadString( TXT_SLASH );
      cstrLabel1 += cstrLabel2;
      cstrLabel2.LoadString( COL_DETAILS_TAXTYPE );   
      cstrLabel1 += cstrLabel2;

   }
   cstrLabel1 += cstrLabel3;
   GetDlgItem(IDC_TXT_AUTO_ACCT_TAX)->SetWindowText(cstrLabel1);


   // AddControl( CTRL_STATIC, IDC_TXT_ACCT_NUM,BF::NullContainerId, 0,CTRLFLAG_GUI_FIELD,IDC_LV_ACCT_ALLOC );

}

//***************************************************************************

void AllocationsDlg::showControls()
{

   /**
       *   Controls for Default Allocations and Trade Allocation
       */ 
   bool bShow = ( (m_rbUsage == 0) || (m_rbUsage == 3) );
   int iShowWindow = (bShow ? SW_SHOW : SW_HIDE);

   GetList( IDC_LV_SHR_ALLOC )->ShowWindow( iShowWindow ); 
   GetList( IDC_LV_ACCT_ALLOC )->ShowWindow( iShowWindow ); 
   GetList( IDC_LV_FUND_ALLOC )->ShowWindow( iShowWindow ); 

   ShowControl( IDC_EDT_ACCT_PRC, bShow );
   ShowControl( IDC_TXT_ACCT_TOTAL_PRC_VAL,  bShow);
   ShowControl( IDC_EDT_FUND,                bShow );

   GetDlgItem( IDC_TXT_ACCT_PRC )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_ACCT_TOTAL_PRC )->ShowWindow( iShowWindow );
   //GetDlgItem( IDC_BTN_ADD_ACCT_ALLOC )->ShowWindow( iShowWindow );//will be; don't delete it
   //GetDlgItem( IDC_BTN_DELETE_ACCT_ALLOC )->ShowWindow( iShowWindow );//will be; don't delete it

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      ShowControl( IDC_EDT_FUND_NUMBER,         bShow );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      ShowControl( IDC_EDT_FUND_NUMBER,         false );
   }
   ShowControl( IDC_EDT_CLASS,               bShow );
   ShowControl( IDC_EDT_FUND_PERCENT,        bShow );
   ShowControl( IDC_TXT_FUND_TOTAL_PRC_VAL,  bShow );

   /**
     *   Controls for the Default Allocations
     */ 
   bShow = (m_rbUsage == 0);
   iShowWindow = (bShow ? SW_SHOW : SW_HIDE);

   ShowControl( IDC_CMB_ACCT_TAX, bShow );
   ShowControl( IDC_CMB_ALLOC_TYPE,          bShow );
   ShowControl( IDC_DTP_EFF_DATE,            bShow );
   ShowControl( IDC_CMB_FUND_GROUP, bShow && isFundGroupApplicable() );

   if( isFELCommApplicable() )
   {
      GetDlgItem( IDC_TXT_FE_COMM )->ShowWindow( bShow );
	  GetDlgItem( IDC_EDT_FE_COMM )->ShowWindow( bShow );
   }
   else
   {
	  GetDlgItem( IDC_TXT_FE_COMM )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_EDT_FE_COMM )->ShowWindow( SW_HIDE );
   }

   GetDlgItem( IDC_TXT_ACCT_TAX )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_BTN_ADD_ACCT_ALLOC )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_BTN_DELETE_ACCT_ALLOC )->ShowWindow( iShowWindow );
   /*if( DSTCommonFunctions::getMarket() == CFDS_CAN ) 
   {
     ShowControl( IDC_EDT_FUND_NUMBER,         bShow );
   }
   else if( DSTCommonFunctions::getMarket() == JAPAN )
   {
     ShowControl( IDC_EDT_FUND_NUMBER,         false );
   }
  ShowControl( IDC_EDT_CLASS,               bShow );
  ShowControl( IDC_EDT_FUND_PERCENT,        bShow );
  ShowControl( IDC_TXT_FUND_TOTAL_PRC_VAL,  bShow );*/

   GetDlgItem( IDC_BTN_ADD_SHR_ALLOC )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_BTN_DELETE_SHR_ALLOC )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_ALLOC_TYPE )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_EFF_DATE )->ShowWindow( iShowWindow );
   isFundGroupApplicable() ? GetDlgItem( IDC_TXT_FUND_GROUP )->ShowWindow( SW_SHOW ) :
                             GetDlgItem( IDC_TXT_FUND_GROUP )->ShowWindow( SW_HIDE );
   /**
     * Common controls for Systematic One Time Allocation and the Automatic Transfer
     */
   bShow = ( (m_rbUsage == 1) || (m_rbUsage == 2) );
   iShowWindow = (bShow ? SW_SHOW : SW_HIDE);

   ShowControl( IDC_EDT_SYS_FUND,               bShow );
   ShowControl( IDC_EDT_SYS_CLASS,              bShow );
   ShowControl( IDC_EDT_SYS_FUND_PERCENT,       bShow );
   ShowControl( IDC_TXT_FUND_TOTAL_SYS_PRC_VAL, bShow );
   ShowControl( IDC_EDT_FUND_AMT,               bShow );

   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      ShowControl( IDC_EDT_SYS_FUND_NUMBER,     bShow );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      ShowControl( IDC_EDT_SYS_FUND_NUMBER,     false );
   }
   //GetDlgItem( IDC_TXT_AMT )->ShowWindow( iShowWindow );
   //GetDlgItem( IDC_TXT_FUND_TOTAL_AMT )->ShowWindow( iShowWindow );

/**
     * Common controls for Systematic and Trade One Time Allocation and the Automatic Transfer
     */
   bShow = ( (m_rbUsage == 1) || (m_rbUsage == 2) || (m_rbUsage == 3) );
   iShowWindow = (bShow ? SW_SHOW : SW_HIDE);
   GetDlgItem( IDC_CHK_REPLACE )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_AMT )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_FUND_TOTAL_AMT )->ShowWindow( iShowWindow );
   ShowControl( IDC_TXT_FUND_TOTAL_AMT_VAL,     bShow);

/**
     * Common controls for Systematic One Time Allocation and the Automatic Transfer
     */
   bShow = ( (m_rbUsage == 1) || (m_rbUsage == 2) );
   iShowWindow = (bShow ? SW_SHOW : SW_HIDE);
   GetList( IDC_LV_SYS_FUND_ALLOC )->ShowWindow( iShowWindow ); 



   /**
     *  One Time Allocations Specific
     */
   bShow = (m_rbUsage == 1);
   iShowWindow = (bShow ? SW_SHOW : SW_HIDE);

   GetList( IDC_LV_SYSTEMATIC )->ShowWindow( iShowWindow ); 

   /**
     *   Automatic Transfers Specific
     */
   bShow = (m_rbUsage == 2);
   iShowWindow = (bShow ? SW_SHOW : SW_HIDE);

   GetList( IDC_LV_AUTO_SHR_ALLOC )->ShowWindow( iShowWindow); 
   GetDlgItem( IDC_BTN_AUTO_ADD_SHR_ALLOC )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_BTN_AUTO_DELETE_SHR_ALLOC )->ShowWindow( iShowWindow );

   GetDlgItem( IDC_TXT_AUTO_ACCT_TAX )->ShowWindow( iShowWindow );

   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      GetDlgItem( IDC_EDT_AUTO_ACCT_TAX )->ShowWindow( iShowWindow );
      GetDlgItem( IDC_CMB_AUTO_ACCT_TAX )->ShowWindow( SW_HIDE );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      GetDlgItem( IDC_CMB_AUTO_ACCT_TAX )->ShowWindow( iShowWindow );
      GetDlgItem( IDC_EDT_AUTO_ACCT_TAX )->ShowWindow( SW_HIDE );
   }

   GetDlgItem( IDC_TXT_AUTO_ACCT_PRC )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_EDT_AUTO_ACCT_PRC )->ShowWindow( iShowWindow );

   GetDlgItem( IDC_TXT_AUTO_ACCT_TOTAL_PRC )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_AUTO_ACCT_TOTAL_PRC_VAL )->ShowWindow( iShowWindow );

   GetDlgItem( IDC_TXT_AUTO_AMT )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_EDT_AUTO_FUND_AMT )->ShowWindow( iShowWindow );

   GetDlgItem( IDC_TXT_AUTO_FUND_TOTAL_AMT )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_AUTO_FUND_TOTAL_AMT_VAL )->ShowWindow( iShowWindow );

   // Trade Allocation specific
   bShow = (m_rbUsage == 3);
   iShowWindow = (bShow ? SW_SHOW : SW_HIDE);

   ShowControl( IDC_EDIT_ACC_NUM, bShow );
   ShowControl( IDC_EDT_TRADE_FUND_AMT, bShow );
   GetDlgItem( IDC_TXT_ACCT_NUM )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_TAX_TYPE )->ShowWindow( iShowWindow );
   GetDlgItem( IDC_TXT_TAX_TYPE_VAL )->ShowWindow( iShowWindow );


}


//******************************************************************************

void AllocationsDlg::enableDisableOneTimeAllocation(bool bEnable)
{
   GetList(IDC_LV_SYS_FUND_ALLOC )->EnableWindow(bEnable); 
   EnableControl( IDC_EDT_SYS_FUND,               bEnable );
   EnableControl( IDC_EDT_SYS_CLASS,              bEnable );
   EnableControl( IDC_EDT_SYS_FUND_PERCENT,       bEnable );
   EnableControl( IDC_EDT_FUND_AMT,               bEnable );
   EnableControl( IDC_TXT_FUND_TOTAL_AMT_VAL,     bEnable);
   EnableControl( IDC_TXT_FUND_TOTAL_SYS_PRC_VAL, bEnable );

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      EnableControl( IDC_EDT_SYS_FUND_NUMBER,     bEnable );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      EnableControl( IDC_EDT_SYS_FUND_NUMBER,     false );
   }

   GetDlgItem( IDC_CHK_REPLACE )->EnableWindow( bEnable );
   GetDlgItem( IDC_TXT_AMT )->EnableWindow( bEnable );
   GetDlgItem( IDC_TXT_FUND_TOTAL_AMT )->EnableWindow( bEnable );
}

//******************************************************************************

bool AllocationsDlg::doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand)
{
   TRACE_METHOD( CLASSNAME, DOREFRESH )

   SetShareholderCaption();

   ConnectControlsToData();

   /**
    * The Allocation Type should decided by the lauching screen
    */
   switchAllocationType();

   focusOnSelectedItem(); 

   UpdateData( false );
   return(true);
}

//******************************************************************************
//put the focus on the selected item when lauched from Systematic, Trade...
//
void AllocationsDlg::focusOnSelectedItem()
{
   DString dstrKey;
   getParent()->getField(this, BF::NullContainerId, ifds::SystematicKey, dstrKey);
   dstrKey.strip();
   if( m_rbUsage == 1 )
   {
      DSTListCtrl *pListCtrl = GetList(IDC_LV_SYSTEMATIC );
      pListCtrl->SetSelection(&dstrKey);
   }
   else if( m_rbUsage == 2 )
   {
      getParent()->setCurrentListItem(this, IFASTBP_PROC::SYSTEMATIC_LIST, dstrKey);

      DString dstrTotalAmount;
      getParent()->getField( this,  IFASTBP_PROC::SYSTEMATIC_LIST, ifds::Amount, dstrTotalAmount, false);
      I_CHAR *stopstring;
      double dTotalAmount = wcstod(dstrTotalAmount.c_str(), &stopstring );
      EnableControl( IDC_EDT_AUTO_FUND_AMT, dTotalAmount > 0 );
      EnableControl( IDC_EDT_FUND_AMT, dTotalAmount > 0 );
   }
   else if (m_rbUsage == 3)
   {
      DSTListCtrl *pListCtrl = GetList(IDC_LV_SHR_ALLOC);
      DSTListCtrl *pAllocListCtrl = GetList(IDC_LV_FUND_ALLOC);

      if (pListCtrl)
      {
         pListCtrl->SetSelection(&dstrKey);
      }
      if (pAllocListCtrl && _strAllocationListKey != NULL_STRING)
      {
         pAllocListCtrl->SetSelection(&_strAllocationListKey);
      }
   }
}

//******************************************************************************

void AllocationsDlg::OnRbDefault() 
{
   TRACE_METHOD( CLASSNAME, ONRBDEFAULT );

   CWaitCursor wait;

   if( m_rbUsage != 0 )
   {
      m_rbUsage = 0;
      switchAllocationType();
   }
   SetUserAccesFuncCode();
   CheckPermission();
}

//******************************************************************************

void AllocationsDlg::OnRbOneTime() 
{
   TRACE_METHOD( CLASSNAME, ONRBONETIME );

   CWaitCursor wait;

   if( m_rbUsage != 1 )
   {
      m_rbUsage = 1;
      switchAllocationType();
   }
   SetUserAccesFuncCode();
   CheckPermission();
}
//******************************************************************************

void AllocationsDlg::OnRbOneTimeTrade() 
{
   TRACE_METHOD( CLASSNAME, ONRBONETIMETRADE );

   CWaitCursor wait;

   if( m_rbUsage != 3 )
   {
      m_rbUsage = 3;
      switchAllocationType();
   }
   SetUserAccesFuncCode();
   CheckPermission();
}
//******************************************************************************

void AllocationsDlg::OnRbAutoTransfer() 
{ 
   TRACE_METHOD( CLASSNAME, ONRBAUTOTRANSFER );

   CWaitCursor wait;

   if( m_rbUsage != 2 )
   {
      m_rbUsage = 2;
      switchAllocationType();
   }
   SetUserAccesFuncCode();
   CheckPermission();
}

//------------------------------------------------------------------------------
void  AllocationsDlg::setRadioButton()
{
   ((CButton* )GetDlgItem(IDC_RB_ONE_TIME))->SetCheck(m_rbUsage == 1);
   ((CButton* )GetDlgItem(IDC_RB_DEFAULT))->SetCheck(m_rbUsage == 0);
   ((CButton* )GetDlgItem(IDC_RB_AUTO_TRANSFER))->SetCheck(m_rbUsage == 2);
   ((CButton* )GetDlgItem(IDC_RB_ONE_TIME_TRADE))->SetCheck(m_rbUsage == 3);

   /* if( DSTCommonFunctions::getMarket() == CFDS_CAN) 
       GetDlgItem(IDC_RB_AUTO_TRANSFER )->EnableWindow( true );
    else if( DSTCommonFunctions::getMarket() == MSDW_JAP ) 
       GetDlgItem( IDC_RB_AUTO_TRANSFER )->EnableWindow( false );
 */
}

//------------------------------------------------------------------------------
void  AllocationsDlg::switchAllocationType()
{
   setRadioButton();                            //this should be already set when click the Radio button
   showControls();

   if( m_rbUsage == 1 )        //One Time Systematic Allocations or Automatic Transfer
   {
      if( isRRifAlloction() )
      {
         GetDlgItem( IDC_BTN_SPLIT_COM )->EnableWindow( false );
         m_dstrAllocType = ALLOCATIONSPROC::RRIF_LIF_LRIF_ONE_TIME;
      }
      else
         m_dstrAllocType = ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME;
      getParent()->setField(this, ifds::AllocationType, m_dstrAllocType, true);

      loadOneTimeAllocation();
      //GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow(GetList(IDC_LV_SYS_FUND_ALLOC)->GetItemCount());
   }
   else if( m_rbUsage == 2 )
   {
      m_dstrAllocType = ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER;
      getParent()->setField(this, ifds::AllocationType, m_dstrAllocType, true);

      LoadATAllocation();
   }
   else if( m_rbUsage == 0 )                                     //default allocation
   {
      m_dstrAllocType = ALLOCATIONSPROC::SHAREHOLDER_DEFAULT;
      getParent()->setField(this, ifds::AllocationType, m_dstrAllocType, true);

      loadDefaultAllocation();
      //GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow(GetList(IDC_LV_FUND_ALLOC )->GetItemCount());
      //temporary disable split commission for default allocations
      GetDlgItem( IDC_BTN_SPLIT_COM )->EnableWindow( false );
   }
   else if( m_rbUsage == 3 )     //trade allocation
   {
      m_dstrAllocType = ALLOCATIONSPROC::TRADE_ONE_TIME;
      getParent()->setField(this, ifds::AllocationType, m_dstrAllocType, true);

      loadTradeOneTimeAllocation();
      //GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow(GetList(IDC_LV_FUND_ALLOC)->GetItemCount());
   }
   //permission check stuff
   if( m_rbUsage == 2 )
   {
      changeBtnToListCtrlAssociation(IDC_BTN_ADD_FUND_ALLOC, IDC_LV_SYS_FUND_ALLOC, true);
      changeBtnToListCtrlAssociation(IDC_BTN_DELETE_FUND_ALLOC, IDC_LV_SYS_FUND_ALLOC, true);
   }
   else
   {
      changeBtnToListCtrlAssociation(IDC_BTN_ADD_FUND_ALLOC, IDC_LV_FUND_ALLOC, true);
      changeBtnToListCtrlAssociation(IDC_BTN_DELETE_FUND_ALLOC, IDC_LV_FUND_ALLOC, true);
   }
   CheckPermission();
   if( m_rbUsage == 0 )
      LoadListControl(IDC_LV_SHR_ALLOC);
   else if( m_rbUsage == 1 )
   {
      LoadListControl(IDC_LV_SYSTEMATIC);
      LoadListControl(IDC_LV_SYS_FUND_ALLOC);
   }
   else if( m_rbUsage == 2 )
   {
      LoadListControl(IDC_LV_AUTO_SHR_ALLOC);
      LoadListControl(IDC_LV_SYS_FUND_ALLOC);
      DString dstrTotalAmount;
      getParent()->getField( this,  IFASTBP_PROC::SYSTEMATIC_LIST, ifds::Amount, dstrTotalAmount, false);
      I_CHAR *stopstring;
      double dTotalAmount = wcstod(dstrTotalAmount.c_str(), &stopstring );
      EnableControl( IDC_EDT_AUTO_FUND_AMT, dTotalAmount > 0 );
      EnableControl( IDC_EDT_FUND_AMT, dTotalAmount > 0 );
   }
   else if( m_rbUsage == 3 )
      LoadListControl(IDC_LV_SHR_ALLOC);   

   LoadControls();//??

   //checkAllocType();
}
//--------------------------------------------------------------------------

void  AllocationsDlg::loadDefaultAllocation()
{
   ReInitControl(IDC_EDIT_ACC_NUM, BF::NullContainerId, ifds::NullFieldId, -1, TRADE_ALLOCATIONS_ONLY);
   ReInitControl(IDC_EDT_TRADE_FUND_AMT, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::AllocAmount, -1, TRADE_ALLOCATIONS_ONLY);
   ReInitControl(IDC_CMB_ACCT_TAX, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::AccountNum, -1, IDC_LV_ACCT_ALLOC);//flags unchanged
   ReInitControl(IDC_DTP_EFF_DATE, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::EffectiveDate, -1, IDC_LV_SHR_ALLOC);//flags unchanged
   ReInitControl(IDC_CMB_FUND_GROUP, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::FundGroup, -1, IDC_LV_ACCT_ALLOC);//flags unchanged


   ReInitListControl(IDC_LV_SHR_ALLOC,  ifds::LV_DefaultAllocShrHeading, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, LV_SHR_ALLOC);
   ReInitListControl(IDC_LV_ACCT_ALLOC,  ifds::LV_DefaultAllocAcctHeading, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, LV_ACCT_ALLOC);

   if( isFELCommApplicable() )
   {
	  ReInitListControl(IDC_LV_FUND_ALLOC, ifds::LV_DefaultAllocFundHeading2, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, LV_FUND_ALLOC);	  
   }
   else
   {
      ReInitListControl(IDC_LV_FUND_ALLOC, ifds::LV_DefaultAllocFundHeading, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, LV_FUND_ALLOC);   
   }

   ReInitControl(IDC_EDT_FUND_NUMBER,    IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::ToFundNumber);
   ReInitControl(IDC_EDT_FUND,           IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::FundCode);
   ReInitControl(IDC_EDT_CLASS,          IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::ClassCode);
   ReInitControl(IDC_EDT_FUND_PERCENT,   IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::AllocPercentage);
   ReInitControl(IDC_EDT_FUND_AMT,       BF::NullContainerId, ifds::NullFieldId);
   ReInitControl(IDC_EDT_ACCT_PRC,       IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::AllocPercentage);

   ReInitControl(IDC_CMB_ALLOC_TYPE,     IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, -1, IDC_LV_SHR_ALLOC);//flags unchanged
}

//--------------------------------------------------------------------------


//load Automatic Transfer Allocation
//
void AllocationsDlg::LoadATAllocation()
{
   ReInitControl(IDC_EDIT_ACC_NUM, BF::NullContainerId, ifds::NullFieldId, -1, TRADE_ALLOCATIONS_ONLY);
   ReInitControl(IDC_EDT_TRADE_FUND_AMT, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::AllocAmount, -1, TRADE_ALLOCATIONS_ONLY);
   ReInitControl(IDC_DTP_EFF_DATE, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::EffectiveDate, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
   ReInitControl(IDC_CMB_FUND_GROUP, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::FundGroup, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged

   ReInitListControl(IDC_LV_SYS_FUND_ALLOC,  ifds::LV_OneTimeAllocFundHeading, IFASTBP_PROC::AT_FUND_TRANS_LIST, LV_AT_FUND_ALLOC);
   ReInitControl( IDC_EDT_SYS_FUND_NUMBER,IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::ToFundNumber);
   ReInitControl( IDC_EDT_SYS_FUND,IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::FundCode);
   ReInitControl( IDC_EDT_SYS_CLASS,IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::ClassCode);
   ReInitControl( IDC_EDT_SYS_FUND_PERCENT,IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::Percentage);
   ReInitControl( IDC_EDT_FUND_AMT,IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::AllocAmount);
   ReInitControl(IDC_CMB_ALLOC_TYPE, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
   ReInitControl(IDC_CMB_ACCT_TAX, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::AccountNum, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
}

//-----------------------------------------------------------------------------
// This routine for Systematic OneTime Allocation 
//
void AllocationsDlg::loadOneTimeAllocation()
{
   ReInitControl(IDC_EDIT_ACC_NUM, BF::NullContainerId, ifds::NullFieldId, -1, TRADE_ALLOCATIONS_ONLY);
   ReInitControl(IDC_EDT_TRADE_FUND_AMT, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::AllocAmount, -1, TRADE_ALLOCATIONS_ONLY);
   ReInitControl(IDC_CMB_ALLOC_TYPE, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
   ReInitControl(IDC_CMB_ACCT_TAX, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::AccountNum, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
   ReInitControl(IDC_DTP_EFF_DATE, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::EffectiveDate, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
   ReInitControl(IDC_CMB_FUND_GROUP, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::FundGroup, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged

   if( m_lOneTimeList == IFASTBP_PROC::SYSTEMATIC_LIST )
   {
      ReInitListControl(IDC_LV_SYSTEMATIC,  ifds::LV_OneTimeAllocSystematicHeading, m_lOneTimeList, LV_SYSTEMATIC);
      ReInitListControl(IDC_LV_SYS_FUND_ALLOC, ifds::LV_OneTimeAllocFundHeading, m_lOneTimeAllocList, LV_SYS_FUND_ALLOC);

      ReInitControl(IDC_EDT_SYS_FUND,          m_lOneTimeAllocList, ifds::FundCode);
      ReInitControl(IDC_EDT_SYS_FUND_NUMBER,    m_lOneTimeAllocList, ifds::ToFundNumber);
      ReInitControl(IDC_EDT_SYS_CLASS,           m_lOneTimeAllocList, ifds::ClassCode);
      ReInitControl(IDC_EDT_SYS_FUND_PERCENT,   m_lOneTimeAllocList, ifds::Percentage);
      ReInitControl(IDC_EDT_FUND_AMT,          m_lOneTimeAllocList, ifds::AllocAmount);

   }
   else if( m_lOneTimeList == IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST )   // lif rif allocation - need to check how to be lauched ?????
   {
      ReInitListControl(IDC_LV_SYSTEMATIC,ifds::LV_OneTimeRRIFAllocHeading, m_lOneTimeList, LV_SYSTEMATIC); 
      ReInitListControl(IDC_LV_SYS_FUND_ALLOC,ifds::LV_OneTimeTradeAllocHeadingSet,//all allocations except systematic can use TradeAllocHeadingSet
                        m_lOneTimeAllocList,LV_SYS_FUND_ALLOC);

      ReInitControl(IDC_EDT_SYS_FUND, m_lOneTimeAllocList, ifds::FundCode);
      ReInitControl(IDC_EDT_SYS_FUND_NUMBER,  m_lOneTimeAllocList, ifds::ToFundNumber);
      ReInitControl(IDC_EDT_SYS_CLASS,  m_lOneTimeAllocList, ifds::ClassCode);
      ReInitControl(IDC_EDT_SYS_FUND_PERCENT, m_lOneTimeAllocList, ifds::AllocPercentage);
      ReInitControl(IDC_EDT_FUND_AMT, m_lOneTimeAllocList, ifds::AllocAmount);
   }
}
//-----------------------------------------------------------------------------

void AllocationsDlg::loadTradeOneTimeAllocation()
{
   if( m_lOneTimeList == IFASTBP_PROC::TRADES_LIST )
   {
      ReInitListControl(IDC_LV_SHR_ALLOC,  ifds::LV_OneTimeTradeHeadingSet, m_lOneTimeList, LV_SHR_ALLOC);
      ReInitListControl(IDC_LV_ACCT_ALLOC,  ifds::LV_TradeAllocAcctHeadingSet, IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, LV_ACCT_ALLOC);
      ReInitListControl(IDC_LV_FUND_ALLOC, ifds::LV_OneTimeTradeAllocHeadingSet, m_lOneTimeAllocList, LV_FUND_ALLOC);
      ReInitControl(IDC_DTP_EFF_DATE, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::EffectiveDate, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
      ReInitControl(IDC_CMB_FUND_GROUP, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::FundGroup, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged

      ReInitControl(IDC_EDT_FUND_NUMBER,    m_lOneTimeAllocList, ifds::ToFundNumber);
      ReInitControl(IDC_EDT_FUND,         m_lOneTimeAllocList, ifds::FundCode);
      ReInitControl(IDC_EDT_CLASS,          m_lOneTimeAllocList, ifds::ClassCode);
      ReInitControl(IDC_EDT_FUND_PERCENT,   m_lOneTimeAllocList, ifds::AllocPercentage);
      ReInitControl(IDC_EDT_ACCT_PRC,       IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, ifds::AllocPercentage);
      ReInitControl(IDC_EDIT_ACC_NUM,       IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, 
                    ifds::AccountNum, -1, IDC_LV_ACCT_ALLOC);
      ReInitControl(IDC_EDT_TRADE_FUND_AMT, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::AllocAmount, -1, IDC_LV_FUND_ALLOC);

      ReInitControl(IDC_CMB_ALLOC_TYPE, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
      ReInitControl(IDC_CMB_ACCT_TAX, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::AccountNum, -1, DEFAULT_ALLOCATIONS_ONLY);//flags unchanged
   }
   else
      assert(0);
}

//-----------------------------------------------------------------------------
bool  AllocationsDlg::isRRifAlloction()  const
{
   return(bRRIF);
}

//******************************************************************************

void AllocationsDlg::OnAccelAllocType() 
{
   if( GetList( IDC_LV_SHR_ALLOC )->IsWindowVisible() )
      GetList( IDC_LV_SHR_ALLOC )->SetFocus();
   else
      GetList( IDC_LV_SYSTEMATIC )->SetFocus();
}

//******************************************************************************

void AllocationsDlg::OnAccelAcct() 
{
   if( GetList( IDC_LV_AUTO_SHR_ALLOC )->IsWindowVisible() )
      GetList( IDC_LV_AUTO_SHR_ALLOC )->SetFocus();
   else
      GetList( IDC_LV_ACCT_ALLOC )->SetFocus(); 
}

//******************************************************************************

void AllocationsDlg::OnAccelFund() 
{
   if( GetList( IDC_LV_FUND_ALLOC )->IsWindowVisible() )
      GetList( IDC_LV_FUND_ALLOC )->SetFocus();
   else
      GetList( IDC_LV_SYS_FUND_ALLOC )->SetFocus();
}

//******************************************************************************

BOOL AllocationsDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

//   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable())
//      return TRUE;

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_NUMBER;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_SYS_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiClassCodeDialogItem = IDC_EDT_SYS_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_SYS_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_SYS_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_SYS_FUND_NUMBER ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );  
         m_uiClassCodeDialogItem = IDC_EDT_SYS_FUND_NUMBER;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_AUTO_ACCT_TAX ) )
      {
         DString strMarket = DSTCommonFunctions::getMarket();
         if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
         {
            PostMessage( WM_LAUNCH_IDENT_ACC );      
            m_uiAccItem = IDC_EDT_AUTO_ACCT_TAX;
         }
      }
   }

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );

   if( !isTranslated )
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );

   return(isTranslated);
}

//******************************************************************************

void AllocationsDlg::ControlUpdated( UINT ControlID, const DString &dstrValue )
{
   switch( ControlID )
   {
      
      case IDC_CMB_ALLOC_TYPE:
         /*if( m_rbUsage == 0 )
         {
            EnableControl( IDC_CMB_ALLOC_TYPE, false );
         }*/
         //LoadControl( IDC_TXT_ACCT_TOTAL_PRC_VAL );
         ShowControl( IDC_CMB_FUND_GROUP, isFundGroupApplicable() );
         isFundGroupApplicable() ? GetDlgItem( IDC_TXT_FUND_GROUP )->ShowWindow( SW_SHOW ) :
                             GetDlgItem( IDC_TXT_FUND_GROUP )->ShowWindow( SW_HIDE );

         //GetDlgItem( IDC_BTN_ADD_ACCT_ALLOC )->EnableWindow( dstrValue != MANAGEMENT_FEE_CODE && dstrValue != FOREIGN_CONTENT_REBALANCING );
		 GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( dstrValue != MANAGEMENT_FEE_CODE && dstrValue != REBALANCING_CODE);	
		 GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( dstrValue != REBALANCING_CODE);
         break;

      case IDC_CMB_ACCT_TAX:          
      case IDC_EDT_ACCT_PRC:
         LoadControl( IDC_TXT_ACCT_TOTAL_PRC_VAL );
         break;

      case IDC_EDT_FUND_PERCENT:
         LoadControl( IDC_TXT_FUND_TOTAL_PRC_VAL );
         LoadControl( IDC_EDT_TRADE_FUND_AMT );
         break;

      case IDC_EDT_SYS_FUND_PERCENT:
         LoadControl( IDC_TXT_FUND_TOTAL_SYS_PRC_VAL );
         LoadControl( IDC_TXT_FUND_TOTAL_AMT_VAL );
         break;

      case IDC_EDT_FUND_AMT:
         LoadControl( IDC_TXT_FUND_TOTAL_SYS_PRC_VAL );
         LoadControl( IDC_TXT_FUND_TOTAL_AMT_VAL );
         break;

      case IDC_EDT_TRADE_FUND_AMT:
         //LoadControl( IDC_TXT_FUND_TOTAL_SYS_PRC_VAL );
         LoadControl( IDC_TXT_FUND_TOTAL_AMT_VAL );
         break;

      case IDC_EDIT_ACC_NUM:
         {
            if( m_rbUsage == 3 ) //trade one time
            {
               DString strTaxType;
               getParent()->getField(this, IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, ifds::TaxType, strTaxType);
               CStatic * pStatic = static_cast<CStatic*>(GetDlgItem(IDC_TXT_TAX_TYPE_VAL));
               if( pStatic )
                  pStatic->SetWindowText(strTaxType.c_str());
            }
            LoadControl( IDC_EDIT_ACC_NUM );
         }
         break;
      case IDC_EDT_FUND_NUMBER:
         {
            if( m_rbUsage != 0 )
            {
               DString dstr;         
               if( m_dstrAllocType == ALLOCATIONSPROC::TRADE_ONE_TIME )
               {
                  getParent()->getField(this, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::SplitComm, dstr, false );
                  GetDlgItem( IDC_BTN_SPLIT_COM )->EnableWindow( dstr == I_("Y") );            
               }
               else if( m_dstrAllocType == ALLOCATIONSPROC::SHAREHOLDER_DEFAULT )
               {
                  getParent()->getField(this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::SplitComm, dstr, false );
                  GetDlgItem( IDC_BTN_SPLIT_COM )->EnableWindow( dstr == I_("Y") );            
               }
            }
         }
         break;
      case IDC_EDT_SYS_FUND_NUMBER:
         {
            if( m_rbUsage != 0 )
            {
               DString dstr;
               if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME )
               {
                  getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST, ifds::SplitComm, dstr, false );
                  GetDlgItem( IDC_BTN_SPLIT_COM )->EnableWindow( dstr == I_("Y") );
               }
               else if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER )
               {
                  getParent()->getField(this, IFASTBP_PROC::AT_FUND_TRANS_LIST, ifds::SplitComm, dstr, false );
                  GetDlgItem( IDC_BTN_SPLIT_COM )->EnableWindow( dstr == I_("Y") );
               }
            }
         }
         break;      
      case IDC_EDT_FUND:
      case IDC_EDT_CLASS:
         showHideFrontEndLoadCommissionControls();
         break;
      default:
         break;
   }
}

//******************************************************************************

void AllocationsDlg::calcTotalPercent( const BFContainerId& idList, DString &dstrOutTotalPercent) const
{
   if( m_rbUsage == 0 || m_rbUsage == 3 || (m_rbUsage == 1 && isRRifAlloction()) )//have to implement it properly
   {
      //at least for Trading, Default and RRIF alloc. we don't want this destructive code to be executed
      assert(0);
   }

   if( idList == BF::AllContainerIds || !getParent()->getNumberOfItemsInList(this, idList) )
   {
      dstrOutTotalPercent = NULL_STRING;
      return;
   }

   BFFieldId idPercentage = ifds::Percentage;

   // 1. save the current position in the list, to restore it later
   const DString *pCurrKey = &(getParent()->getCurrentListItemKey(this, idList));

   // 2. calculate total percent
   double dTotalPercent = 0;
   const DString *pKey = &( getParent()->getFirstListItemKey(this, idList));
   while( *pKey != NULL_STRING )
   {
      DString dstrPercentage;
      getParent()->getField(this, idList, idPercentage, dstrPercentage);

      dTotalPercent += DSTCommonFunctions::convertToDouble(dstrPercentage);

      pKey = &(getParent()->getNextListItemKey(this, idList));
   }
   dstrOutTotalPercent = DSTCommonFunctions::doubleToDString(idPercentage, dTotalPercent);
   dstrOutTotalPercent += I_CHAR( '%' );

   // 4. restore the initial iterator position in the list
   if( *pCurrKey != NULL_STRING )
      getParent()->setCurrentListItem( this, idList, *pCurrKey );
}

//******************************************************************************
// This routine is currently called only for One Time Allocation or AT
//
void AllocationsDlg::calcTotalAmount( DString &dstrOutTotalAmount, const BFContainerId& idList ) const
{

   DString dstrTransType;
   if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME )
   {
      getParent()->getField( this, IFASTBP_PROC::SYSTEMATIC_LIST, 
                             ifds::TransType, dstrTransType, false );
      dstrTransType.strip().upperCase();
   }

   if( m_rbUsage == 3 || (m_rbUsage == 1 && isRRifAlloction()) )//have to implement it properly
   {
      //at least for Trading and RRIF we don't want this distructive code to be executed
      assert(0);
      return;
   }

   BFContainerId idContainer;
   if( BF::NullContainerId == idList )
   {
      idContainer = m_lOneTimeAllocList;
      if( (m_rbUsage == 2) && ( dstrTransType == I_("AT") ) )
         idContainer = IFASTBP_PROC::AT_FUND_TRANS_LIST;
      else if( dstrTransType == I_("AT") ) return;
   }
   else
   {
      idContainer = idList;
   }
   if( idContainer == BF::AllContainerIds || !getParent()->getNumberOfItemsInList(this, idContainer) )
   {
      dstrOutTotalAmount = NULL_STRING;
      return;
   }

   // 1. remember the current positions in the list, to restore it later
   const DString *pCurrKey;
   pCurrKey = &( getParent()->getCurrentListItemKey( this, idContainer) );

   // 2. calculate total amount
   double dTotalAmount = 0;  
   const DString *pKey;
   pKey = &( getParent()->getFirstListItemKey( this, idContainer ));
   while( *pKey != NULL_STRING )
   {
      DString dstr;
      getParent()->getField(this, idContainer, ifds::AllocAmount, dstr, true);

      dTotalAmount += DSTCommonFunctions::convertToDouble(dstr);

      pKey = &(getParent()->getNextListItemKey(this, idContainer));
   }

   // 3. restore the initial iterator position in the list
   getParent()->setCurrentListItem(this, idContainer, *pCurrKey);

   dstrOutTotalAmount = DSTCommonFunctions::doubleToDString(ifds::AllocAmount, dTotalAmount);
}

//******************************************************************************

void AllocationsDlg::InitControl( UINT controlID )
{
   switch( controlID )
   {
      case IDC_CMB_ACCT_TAX:
         initAcctTaxCombo(controlID);
         break;
      case IDC_CMB_AUTO_ACCT_TAX:
         initAcctTaxCombo(controlID);
         break;
   }
}

//******************************************************************************

void AllocationsDlg::initAcctTaxCombo(UINT iControlID)
{
   DSTComboBox *pCmbAcctTax = dynamic_cast< DSTComboBox * >( GetDlgItem( iControlID ) );

   const DString *pKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::MFACCOUNT_LIST));
   while( *pKey != NULL_STRING )
   {
      DString dstrAccountNum, dstr;
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_LIST, ifds::AccountNum, dstrAccountNum,false );

      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_LIST, ifds::TaxType, dstr );
      dstr.strip();
      dstr = dstrAccountNum + DASH + dstr;
      if( pCmbAcctTax->FindString( -1, dstr.c_str() ) == CB_ERR )
         int iIdx = pCmbAcctTax->AddString( dstr.c_str() );

      pKey = &(getParent()->getNextListItemKey(this, IFASTBP_PROC::MFACCOUNT_LIST));
   }
}

//-----------------------------------------------------------------------------
void  AllocationsDlg::getAcctTaxValue(const BFContainerId& idContainer,DString& dstrOutValue) const
{
   dstrOutValue = NULL_STRING;

   const DString &dstrAcctKey = getParent()->getCurrentListItemKey(this, idContainer ); 
   if( dstrAcctKey ==NULL_STRING ) return;

   DString dstrAccountNum;
   getParent()->getField( this, idContainer, ifds::AllocAccountNum, dstrAccountNum,false );
   dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
   dstrAccountNum.stripLeading(I_CHAR('+'));
   const DString &dstrMFAccountListKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::MFACCOUNT_LIST);

   const DString *pKey = &( getParent()->getFirstListItemKey( this, IFASTBP_PROC::MFACCOUNT_LIST ) );
   while( *pKey != NULL_STRING )
   {
      DString dstr;
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_LIST, ifds::AccountNum, dstr,false );
      if( dstr.strip().stripLeading(I_CHAR('0')) == dstrAccountNum )
      {
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_LIST, ifds::TaxType, dstr );
         dstrOutValue = dstrAccountNum + DASH + dstr.strip();
         break;
      }
      pKey = &(getParent()->getNextListItemKey(this, IFASTBP_PROC::MFACCOUNT_LIST));
   }
   if( dstrMFAccountListKey != NULL_STRING )
      getParent()->setCurrentListItem( this, IFASTBP_PROC::MFACCOUNT_LIST, dstrMFAccountListKey );
}


//******************************************************************************

bool AllocationsDlg::GetDataForControl( UINT controlId, DString &dstrValueOut,
                                        bool bFormatted, int iIndex ) const
{
   dstrValueOut = NULL_STRING;

   switch( controlId )
   {
      
      case IDC_TXT_AUTO_ACCT_TOTAL_PRC_VAL:
         if( m_rbUsage == 2 )
            calcTotalPercent( IFASTBP_PROC::AT_ACCT_TRANS_LIST, dstrValueOut );
         break;

      case IDC_TXT_AUTO_FUND_TOTAL_AMT_VAL:
         {
            DString dstrTransType;
            getParent()->getField( this, IFASTBP_PROC::SYSTEMATIC_LIST, 
                                   ifds::TransType, dstrTransType, false );

            dstrTransType.strip().upperCase();

            if( m_rbUsage == 2 && dstrTransType == I_("AT" ) )
               calcTotalAmount( dstrValueOut,IFASTBP_PROC::AT_ACCT_TRANS_LIST );
         }
         break;

      case IDC_CMB_AUTO_ACCT_TAX:
         if( m_rbUsage == 2 )
            getAcctTaxValue(IFASTBP_PROC::AT_ACCT_TRANS_LIST,dstrValueOut);
         break;

      case IDC_TXT_ACCT_TOTAL_PRC_VAL:
         {
            if( m_rbUsage == 0 )
               getParent()->getField(this, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::TotPercentage, dstrValueOut);
            else if( m_rbUsage == 3 )
               getParent()->getField(this, IFASTBP_PROC::TRADE_ACCOUNT_ALLOCATION_LIST, ifds::TotPercentage, dstrValueOut);
         }
         break;

      case IDC_TXT_FUND_TOTAL_PRC_VAL:
         if( m_rbUsage == 0 )
            getParent()->getField(this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::TotPercentage, dstrValueOut);
         else if( m_rbUsage == 2 )
            calcTotalPercent( IFASTBP_PROC::AT_FUND_TRANS_LIST, dstrValueOut );
         else if( m_rbUsage == 3 )
            getParent()->getField(this, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::TotPercentage, dstrValueOut);
         break;

      case IDC_CMB_ACCT_TAX:                                      //Default Allocation
         {
            dstrValueOut = NULL_STRING;
            const DString &dstrAcctLvKey = GetList( IDC_LV_ACCT_ALLOC )->GetCurrentKey();
            if( dstrAcctLvKey == NULL_STRING )                    //LVN_UNSELECTED
               return(true);

            /*#ifdef _DEBUG
            else
            {
              const DString &dstrAcctKey = getParent()->getCurrentListItemKey(this, ALLOCATIONSPROC::ACCT_ALLOCATIONS_LIST ); 
              assert( dstrAcctLvKey == dstrAcctKey );
            }
            #endif*/

            DString dstrAccountNum;
            getParent()->getField( this, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::AccountNum, dstrAccountNum );
            dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
            const DString &dstrMFAccountListKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::MFACCOUNT_LIST);

            const DString *pKey = &( getParent()->getFirstListItemKey( this, IFASTBP_PROC::MFACCOUNT_LIST ) );
            while( *pKey != NULL_STRING )
            {
               DString dstr;
               getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_LIST, ifds::AccountNum, dstr );
               if( dstr.strip().stripLeading(I_CHAR('0')) == dstrAccountNum )
               {
                  getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_LIST, ifds::TaxType, dstr );
                  dstrValueOut = dstrAccountNum + DASH + dstr.strip();
                  break;
               }
               pKey = &(getParent()->getNextListItemKey(this, IFASTBP_PROC::MFACCOUNT_LIST));
            }
            if( dstrMFAccountListKey != NULL_STRING )
               getParent()->setCurrentListItem( this, IFASTBP_PROC::MFACCOUNT_LIST, dstrMFAccountListKey );
         }
         break;

      case IDC_TXT_FUND_TOTAL_SYS_PRC_VAL:

//      if (m_lOneTimeAllocList == ALLOCATIONSPROC::RRIF_LIF_LRIF_ALLOC_LIST)
//   		dstrValueOut = I_("RRIF_100");
//      else 
         {
            if( m_rbUsage == 0 || m_rbUsage == 3 )
               break;
            else if( m_rbUsage == 1 && isRRifAlloction() )
               getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST, ifds::TotPercentage, dstrValueOut);
            else
               calcTotalPercent(m_lOneTimeAllocList, dstrValueOut);  //Other OneTime Allocations Or AT
         }
         break;

      case IDC_EDT_FUND_NUMBER:
         {
            DString dstrFundCode, dstrClassCode;

            if( m_rbUsage == 0 )//default 
               getParent()->getField( this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::ToFundNumber, dstrValueOut );
            else if( m_rbUsage == 3 )// trade
               getParent()->getField( this, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::ToFundNumber, dstrValueOut );
            else
            {
               getParent()->getField( this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::FundCode, dstrFundCode ); 
               getParent()->getField( this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::ClassCode, dstrClassCode ); 

               dstrFundCode.strip().upperCase();
               dstrClassCode.strip().upperCase();

               DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
               dstcWorkSession->GetFundNumber ( dstrFundCode, dstrClassCode, dstrValueOut );
            }
            dstrValueOut.strip().upperCase();
         }
         break;

      case IDC_EDT_SYS_FUND_NUMBER:
         {
            if( m_rbUsage == 2 )           //AT
            {
               getParent()->getField( this, IFASTBP_PROC::AT_FUND_TRANS_LIST,ifds::ToFundNumber, dstrValueOut );
               dstrValueOut.strip().upperCase();
            }
            else
            {
               BFFieldId idField = ifds::ToFundNumber;
               if( m_lOneTimeAllocList == IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST )
                  idField = ifds::ToFundNumber;

               getParent()->getField( this, m_lOneTimeAllocList,idField, dstrValueOut );
               dstrValueOut.strip().upperCase();
            }
         }
         break;

      case IDC_TXT_FUND_TOTAL_AMT_VAL:             //OneTime or AT
         if( m_rbUsage == 3 )
            getParent()->getField(this, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::TotAmount, dstrValueOut);
         else if( m_rbUsage == 1 && isRRifAlloction() )
            getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST, ifds::TotAmount, dstrValueOut);
         else
            calcTotalAmount( dstrValueOut );
         break;

         /*case IDC_EDT_TRADE_FUND_AMT:             //OneTime Trade
            {
               dstrValueOut = NULL_STRING;
               if (m_rbUsage == 3)
               {
                  if (getParent()->getNumberOfItemsInList(this,ALLOCATIONSPROC::TRADE_FUND_ALLOCATION_LIST) > 0)
                  {
                     getParent()->getField( this, m_lOneTimeAllocList,DBR::AllocAmount, dstrValueOut );
                 dstrValueOut.strip().upperCase();
                  }
               }
            }
          break;*/

      default:
         return(false);
   }
   dstrValueOut.strip();
   return(true);
}
//******************************************************************************
void AllocationsDlg::AccountLevelAllocationForATChanged(SEVERITY &sevRtn,const BFFieldId &idFiled,const DString& strNewValue )
{
   DString oldValue;
   if( m_rbUsage == 2 )
   {
      getParent()->getField(this,IFASTBP_PROC::AT_ACCT_TRANS_LIST,idFiled,oldValue,false);
      oldValue.strip();
      if( oldValue == strNewValue )
         return;
      sevRtn = getParent()->setField(this,IFASTBP_PROC::AT_ACCT_TRANS_LIST, idFiled,strNewValue,false);

      while( getParent()->getNumberOfItemsInList(this,IFASTBP_PROC::AT_FUND_TRANS_LIST) > 0 )
      {
         DeleteFromListControl( IDC_LV_SYS_FUND_ALLOC );   
      }
      //AddToListControl( IDC_LV_SYS_FUND_ALLOC );
   }

}

//******************************************************************************

bool AllocationsDlg::SetDataFromControl( UINT controlID, 
                                         const DString &dstrValue, bool bFormatted,
                                         SEVERITY &sevRtn, int iIndex )
{
   sevRtn = NO_CONDITION;
   switch( controlID )
   {
      case IDC_EDT_AUTO_ACCT_PRC:
         sevRtn = getParent()->setField( this, IFASTBP_PROC::AT_ACCT_TRANS_LIST, 
                                         ifds::Percentage, dstrValue, false );
         if( m_rbUsage == 2 )
            LoadListControl( IDC_LV_SYS_FUND_ALLOC );
         break;

      case IDC_EDT_AUTO_FUND_AMT:
         sevRtn = getParent()->setField( this, IFASTBP_PROC::AT_ACCT_TRANS_LIST, 
                                         ifds::AllocAmount, dstrValue, false );
         if( m_rbUsage == 2 )
            LoadListControl( IDC_LV_SYS_FUND_ALLOC );
         break;

      case IDC_CMB_ACCT_TAX:
         {
            // 1. set field in the currently selected AcctLevel allocation
            if( dstrValue != NULL_STRING )
            {
               DString dstr( dstrValue );
               int iPos = dstr.pos( DASH );
               assert( iPos != -1 );
               DString dstrAccountNum = dstr.left( iPos );
               sevRtn = getParent()->setField( this, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, 
                                               ifds::AccountNum, dstrAccountNum, false );
            }
         }
         break;

      case IDC_CMB_AUTO_ACCT_TAX:
      case IDC_EDT_AUTO_ACCT_TAX:
         if( m_rbUsage == 2 )
         {
            if( dstrValue != NULL_STRING )
            {
               DString strMarket = DSTCommonFunctions::getMarket();
               DString dstrAccountNum(dstrValue);
               DString strOld;
               DString dstr( dstrValue );
               if( strMarket == MARKET_IDS::JAPAN )
               {
                  int iPos = dstr.pos( DASH );
                  assert( iPos != -1 );
                  dstrAccountNum = dstr.left( iPos );         
               }
               getParent()->getField(this,IFASTBP_PROC::AT_ACCT_TRANS_LIST,ifds::AllocAccountNum,
                                     strOld,false);
               strOld.strip().stripLeading(I_CHAR('0')).stripLeading(I_('+') );
               if( strOld !=dstrAccountNum )
               {
                  sevRtn = getParent()->setField( this, IFASTBP_PROC::AT_ACCT_TRANS_LIST, 
                                                  ifds::AllocAccountNum, dstrAccountNum, false );
               }
            }


         }
         break;

      case IDC_TXT_ACCT_TOTAL_PRC_VAL://no need to do anything
         break;
      case IDC_TXT_FUND_TOTAL_PRC_VAL://no need to do anything
         break;
      case IDC_TXT_FUND_TOTAL_SYS_PRC_VAL://no need to do anything
         break;
         /*case IDC_EDT_TRADE_FUND_AMT:             //OneTime Trade
            {
               if (m_rbUsage == 3)
               {
                  getParent()->setField( this, m_lOneTimeAllocList,DBR::AllocAmount, dstrValue );
               }
            }
          break;*/
      default :
         return(false);
   }

   return(true);
}

//******************************************************************************

void AllocationsDlg::SetShareholderCaption()
{
   DString dstrCaption = SHAREHOLDER_NBR, dstr;
   getParent()->getField( this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::ShrNum, dstr );
   dstr.strip().stripLeading( I_CHAR( '0' ) );
   dstrCaption += dstr;
   dstrCaption += BLANK;
   getParent()->getField( this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::Name1, dstr );
   dstr.strip();
   dstrCaption += dstr;
   SetCaption( dstrCaption );
}

//******************************************************************************

void AllocationsDlg::SetTransactionCaption()
{
   DString dstrCaption = TRANSACTION_NBR, dstr;
   getParent()->getField( this, BF::NullContainerId, ifds::TransNum, dstr );
   dstr.strip().stripLeading( I_CHAR( '0' ) );
   dstrCaption += dstr;
   SetCaption( dstrCaption );
}

//******************************************************************************

bool AllocationsDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   if( lSubstituteId == ifds::LV_OneTimeAllocSystematicHeading.getId() )
   {
      /*	DString dstrAmountType;
        getParent()->getField( this, ALLOCATIONSPROC::SYSTEMATIC_LIST, DBR::AmountType, dstrAmountType, false );
    
          dstrAmountType.strip().upperCase();
          if( dstrAmountType == I_( "U" ) )
          return false;
    */
      // for Automatic Transfer we should filter it out in the one time allocation
      DString dstrTransType;
      getParent()->getField( this, IFASTBP_PROC::SYSTEMATIC_LIST, 
                             ifds::TransType, dstrTransType, false );

      dstrTransType.strip().upperCase();
      if( dstrTransType == I_("AT") ) return(false);
   }
   else if( lSubstituteId == ifds::LV_OneTimeTradeHeadingSet.getId() )
   {
      if( m_lOneTimeList == IFASTBP_PROC::TRADES_LIST )   //not really necessary to check, just in case
      {
         // Filter the Trade Record with the different account number from the lauching account number
         DString dstrTradeAccountNum, dstrTransType, dstrAmountType, dstrTradeTransNum;
         getParent()->getField( this, m_lOneTimeList, ifds::AccountNum, dstrTradeAccountNum, false);
         DString dstrAccountNum;
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum, false);

         getParent()->getField( this, m_lOneTimeList, ifds::TradesTransType, dstrTransType, false );
         dstrTransType.strip().upperCase();

         dstrAccountNum.strip().stripLeading(I_('0'));
         dstrTradeAccountNum.strip().stripLeading(I_('0'));
         if( dstrTransType != TRADETYPE::TRANSFER )
            if( dstrAccountNum != dstrTradeAccountNum )
               return(false);

         getParent()->getField( this, m_lOneTimeList, ifds::TransNum, dstrTradeTransNum, false);
         if( dstrTradeTransNum.strip().stripLeading('0') != m_dstrTransNum )//only show the selected trade on the trading screen
            return(false);

         getParent()->getField( this, m_lOneTimeList, ifds::AmtType, dstrAmountType, false );
         dstrAmountType.strip().upperCase();
         if( dstrTransType == TRADETYPE::PURCHASE || dstrTransType == TRADETYPE::REDEMPTION || dstrTransType == TRADETYPE::MGMT_FEE )
         {
            if( dstrAmountType == I_( "U" ) )
               return(false);
         }

         //don't show trades types for which allocations are not allowed
         DString dstrAllocationsAllowed;
         getParent()->getField( this, m_lOneTimeList, ifds::AllocationsAllowed, dstrAllocationsAllowed, false );
         if( dstrAllocationsAllowed.strip() != YES )
            return(false);
      }
   }
   return(true);
}

//******************************************************************************

bool AllocationsDlg::GetOverrideItemString( long lSubstituteId, 
                                            const DString &dstrColumnKey, DString &dstrOut )
{
   bool bReturn = false;
   dstrOut = NULL_STRING;

   CString str;
   if( lSubstituteId == ifds::LV_DefaultAllocAcctHeading.getId() )
   {
      if( dstrColumnKey == TAX_TYPE )
      {
         DString dstrAccountNum;
         getParent()->getField(this, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST, ifds::AccountNum, dstrAccountNum);
         dstrAccountNum.strip().stripLeading(I_CHAR( '0' ));

         if( dstrAccountNum != NULL_STRING )
         {
            const DString *pKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::MFACCOUNT_LIST));
            while( *pKey != NULL_STRING )
            {
               DString dstr;
               getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_LIST,   ifds::AccountNum, dstr, false);
               dstr.strip().stripLeading(I_CHAR('0'));
               if( dstr == dstrAccountNum )
               {
                  getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_LIST, ifds::TaxType, dstrOut);
                  dstrOut.strip();
                  break;
               }
               pKey = &( getParent()->getNextListItemKey(this, IFASTBP_PROC::MFACCOUNT_LIST));
            }
         }
         bReturn = true;
      }
   }
   else if( lSubstituteId == ifds::LV_DefaultAllocFundHeading.getId() )
   {
   }
   else if( lSubstituteId == ifds::LV_OneTimeAllocSystematicHeading.getId() )
   {
      if( dstrColumnKey == ACCOUNT_NUM )
      {
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrOut, true);
         bReturn = true;
      }
      else if( dstrColumnKey == TAX_TYPE )
      {
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, dstrOut );
         bReturn = true;
      }
      else if( dstrColumnKey == BANK_ACCT_CURRENCY )
      {
         if( m_dstrAllocType == ALLOCATIONSPROC::TRANSACTION_ONE_TIME )
         {
            getParent()->getField( this, BF::NullContainerId, ifds::SettleCurrency, dstrOut );
            bReturn = true;
         }
      }
      else if( dstrColumnKey == TRANS_TYPE )
      {
         if( m_dstrAllocType == ALLOCATIONSPROC::TRANSACTION_ONE_TIME )
         {
            getParent()->getField( this, BF::NullContainerId, ifds::TransCode, dstrOut );
            bReturn = true;
         }
      }
   }
   else if( lSubstituteId == ifds::LV_OneTimeAllocFundHeading.getId() )
   {
      if( m_rbUsage == 2 )
         m_lOneTimeAllocList = IFASTBP_PROC::AT_FUND_TRANS_LIST;
#ifdef _DEBUG
      const DString *pCurrKey = &( getParent()->getCurrentListItemKey(this, m_lOneTimeAllocList));
#endif
      if( dstrColumnKey == FUND_CODE )
      {
         getParent()->getField(this, m_lOneTimeAllocList, ifds::FundCode, dstrOut ); 
         dstrOut.strip().upperCase();
         bReturn = true;
      }
      else if( dstrColumnKey == CLASS_CODE )
      {
         getParent()->getField( this, m_lOneTimeAllocList, ifds::ClassCode, dstrOut );
         dstrOut.strip().upperCase();
         bReturn = true;
      }
      else if( dstrColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode, dstrFundNumber;
         getParent()->getField( this, m_lOneTimeAllocList, ifds::FundCode, dstrFundCode ); 
         getParent()->getField( this, m_lOneTimeAllocList, ifds::ClassCode, dstrClassCode ); 
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         dstcWorkSession->GetFundNumber ( dstrFundCode, dstrClassCode, dstrFundNumber );
         dstrOut = dstrFundNumber.strip();
         bReturn = true;
      }

   }
   else if( lSubstituteId == ifds::LV_OneTimeRRIFAllocHeading.getId() )
   {
      bReturn = true;
      if( dstrColumnKey == ALLOCATIONTYPE )
         dstrOut = I_("RIF");
      else if( dstrColumnKey == TAX_TYPE )
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType,dstrOut,true );
      else if( dstrColumnKey == ACCOUNT_NUM )
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum,dstrOut,true );
      else if( dstrColumnKey == SETTLE_CURRENCY )
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::Currency,dstrOut,true );
      else
         bReturn = false;
   }
   else if( lSubstituteId == ifds::LV_OneTimeRRIFFundHeading.getId() )
   {
      if( dstrColumnKey == FUND_NUMBER )
      {
         /*DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, ALLOCATIONSPROC::RRIF_LIF_LRIF_ALLOC_LIST , ifds::FundCode, dstrFundCode );
         getParent()->getField( this, ALLOCATIONSPROC::RRIF_LIF_LRIF_ALLOC_LIST , ifds::ClassCode, dstrClassCode );
      dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         dstcWorkSession->GetFundNumber ( dstrFundCode, dstrClassCode, dstrOut );*/

         getParent()->getField( this, IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST , ifds::ToFundNumber, dstrOut );

         bReturn = true;
      }
   }
   else if( lSubstituteId == ifds::LV_OneTimeTradeHeadingSet.getId() )
   {
      if( dstrColumnKey == TAX_TYPE )
      {
         getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, dstrOut, true );
         bReturn = true;
      }
   }
   else if( lSubstituteId == ifds::LV_OneTimeTradeAllocHeadingSet.getId() )
   {
   }
   else if( lSubstituteId == ifds::AutoTransferAllocHeadingSet.getId() )
   {
      if( dstrColumnKey == EFFECTIVE_DATE )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_SYSTEMATIC_CBO, ifds::EffectiveDate, dstrOut, true );
         bReturn = true;    

      }
      else if( dstrColumnKey == TAX_TYPE )
      {
         getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, dstrOut, true );
         bReturn = true;
      }
      else if( dstrColumnKey == I_("AccountNum") )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_ACCT_TRANS_LIST, ifds::AllocAccountNum, dstrOut, true );
         bReturn = true;    


      }
      else if( dstrColumnKey == I_("Amount") )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_ACCT_TRANS_LIST, ifds::AllocAmount, dstrOut, true );
         bReturn = true;    


      }


   }
   dstrOut.strip();
   return(bReturn);
}

//******************************************************************************

void AllocationsDlg::DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem )
{
   DString dstrReplaceAsDefault, dstrStatus;

   if( listControlID == IDC_LV_SHR_ALLOC )
   {
	   _blNewShrItem = bIsNewItem;
      //EnableControl( IDC_CMB_ALLOC_TYPE, bIsNewItem );
      //EnableControl( IDC_DTP_EFF_DATE, bIsNewItem );
   }
   else if( listControlID == IDC_LV_AUTO_SHR_ALLOC )
   {
      if( m_rbUsage == 2 )
      {
         getParent()->getField( this, IFASTBP_PROC::AT_ACCT_TRANS_LIST_AS_CBO, 
                                ifds::ReplaceAsDefault, dstrReplaceAsDefault, false );
         dstrReplaceAsDefault.strip();
         if( dstrReplaceAsDefault == YES )
            m_bReplaceAsDefault = true;
         else
            m_bReplaceAsDefault = false;  
         LoadListControl( IDC_LV_SYS_FUND_ALLOC );
      }
      SetUserAccesFuncCode();
   }
   else if( listControlID == IDC_LV_SYSTEMATIC )      //one time allocation
   {
      if( m_lOneTimeList == IFASTBP_PROC::TRADES_LIST )
      {
         getParent()->getField( this, m_lOneTimeList, ifds::SetAsDefault, dstrReplaceAsDefault, false );
      }
      else if( m_lOneTimeList == IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST_AS_CBO )
      {
         getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST_AS_CBO,
                               ifds::ReplaceAsDefault, dstrReplaceAsDefault, false );
      }
      else if( m_lOneTimeList == IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST )
      {
         getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,
                               ifds::SetAsDefault, dstrReplaceAsDefault, false );
      }

      dstrReplaceAsDefault.strip();
      if( dstrReplaceAsDefault == YES )
         m_bReplaceAsDefault = true;
      else
         m_bReplaceAsDefault = false;

      if( m_rbUsage == 1 )
      {
         //Disable the bad status systematic input controls
         DString dstrStatus;
         if( m_lOneTimeList == IFASTBP_PROC::SYSTEMATIC_LIST )
         {
            getParent()->getField( this, m_lOneTimeList, ifds::StatusCode, dstrStatus, false);
            enableDisableOneTimeAllocation(dstrStatus.strip() == YES);
         }
         else if( m_lOneTimeList == IFASTBP_PROC::TRADES_LIST )
         {
            getParent()->getField( this, m_lOneTimeList, ifds::GoodBad, dstrStatus, false);
            enableDisableOneTimeAllocation(dstrStatus.strip() == YES);
         }

         //Disable Amount input if TotalAmount is zero
         DString dstrTotalAmount;
         if( m_lOneTimeList != IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST )
            getParent()->getField( this, m_lOneTimeList, ifds::Amount, dstrTotalAmount, false);
         else
            getParent()->getField( this, m_lOneTimeList, ifds::RRIFAmount, dstrTotalAmount, false);

         I_CHAR *stopstring;
         double dTotalAmount = wcstod(dstrTotalAmount.c_str(), &stopstring );
         EnableControl( IDC_EDT_FUND_AMT, dTotalAmount > 0 );         
      }
      UpdateData( false );
      if( m_dstrAllocType == ALLOCATIONSPROC::TRADE_ONE_TIME )
         getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType, m_strTradeTransType, false);
      else if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME )
         getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::TransType, m_strTransType, false);
      SetUserAccesFuncCode();
   }
   else if( listControlID == IDC_LV_ACCT_ALLOC )
   {
      if ( m_rbUsage == 1 )
         LoadControl(IDC_CMB_FUND_GROUP);
      if( m_rbUsage == 3 )//this is temporary; we do not allow multiple account allocations yet
      {
         CEdit* pEdit = NULL;//this is temporary; it will be removed as soon as we'll allow multiple account allocations
         pEdit = (CEdit*) GetDlgItem( IDC_EDIT_ACC_NUM );//this is temporary; it will be removed as soon as we'll allow multiple account allocations
         pEdit->SetReadOnly();//this is temporary; it will be removed as soon as we'll allow multiple account allocations
         pEdit = (CEdit*) GetDlgItem( IDC_EDT_ACCT_PRC );//this is temporary; it will be removed as soon as we'll allow multiple account allocations
         pEdit->SetReadOnly();//this is temporary; it will be removed as soon as we'll allow multiple account allocations
      }
   }
   else if( listControlID == IDC_LV_FUND_ALLOC )
   {
      if( isFELCommApplicable() )
      {				  	  
         DSTEdit *edtPercentOrFlat = dynamic_cast<DSTEdit *>(GetDlgItem(IDC_EDT_FE_COMM));
         if( !edtPercentOrFlat )
         {
            //EDT_FE_COMM hasn't been added, so make sure to AddControl first
            AddControl(CTRL_EDIT, IDC_EDT_FE_COMM, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::FELComm, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_FUND_ALLOC);
            edtPercentOrFlat = dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FE_COMM));
            edtPercentOrFlat->SetAllowedChars(I_("0123456789."));				
         }

         ConnectControlToData( IDC_EDT_FE_COMM, true);
         DString dstrFELCommType;
         getParent()->getField( this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, ifds::FELCommType, dstrFELCommType, false );

         if( dstrFELCommType == NO) // Percent
         {
            edtPercentOrFlat->AllowNonnegativeDecimalNumbers( 2, 4 );   // format 99.9999
         }
         else   // Flat
         {
            edtPercentOrFlat->AllowNonnegativeDecimalNumbers( 2, 2 );   // format 99.99
         }	
         LoadControl( IDC_EDT_FE_COMM );
      }
      else
      {
         DSTEdit *edtPercentOrFlat = dynamic_cast<DSTEdit *>(GetDlgItem(IDC_EDT_FE_COMM));
         if( edtPercentOrFlat )
         {
            ConnectControlToData( IDC_EDT_FE_COMM, false);		   
         }
      }

      showHideFrontEndLoadCommissionControls();
   }
   else if( listControlID == IDC_LV_SYS_FUND_ALLOC )
   {

   }
}

//******************************************************************************
void AllocationsDlg::showHideFrontEndLoadCommissionControls() 
{
   if(m_rbUsage == 3 && hasFrontEndLoadCommission())
   {
      DSTEdit *edtFelCommission = dynamic_cast<DSTEdit *>(GetDlgItem(IDC_EDT_FEL_COMMISSION));
      if(!edtFelCommission)
      {
         AddControl(CTRL_COMBO, IDC_CMB_FEL_FEE_TYPE,  IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::FeeType,  CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_FUND_ALLOC);
         AddControl(CTRL_EDIT, IDC_EDT_FEL_COMMISSION, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST, ifds::FeeRate,  CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_FUND_ALLOC);
      }

      GetDlgItem(IDC_TXT_FEL_FEE_TYPE)  ->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_TXT_FEL_COMISSION) ->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_CMB_FEL_FEE_TYPE)  ->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_EDT_FEL_COMMISSION)->ShowWindow(SW_SHOW);

      ConnectControlToData(IDC_CMB_FEL_FEE_TYPE,   true);
      ConnectControlToData(IDC_EDT_FEL_COMMISSION, true);

      LoadControl(IDC_CMB_FEL_FEE_TYPE);
      LoadControl(IDC_EDT_FEL_COMMISSION);
   }
   else
   {
      GetDlgItem(IDC_TXT_FEL_FEE_TYPE)  ->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TXT_FEL_COMISSION) ->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_CMB_FEL_FEE_TYPE)  ->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_EDT_FEL_COMMISSION)->ShowWindow(SW_HIDE);

      DSTEdit *edtFelCommission = dynamic_cast<DSTEdit *>(GetDlgItem(IDC_EDT_FEL_COMMISSION));
      if(edtFelCommission)
      {
         ConnectControlToData(IDC_CMB_FEL_FEE_TYPE,   false);
         ConnectControlToData(IDC_EDT_FEL_COMMISSION, false);
      }
   }
}
//******************************************************************************
void AllocationsDlg::OnBtnAddShrAlloc() 
{
   AddToListControl( IDC_LV_SHR_ALLOC );

   //EnableControl( IDC_CMB_ALLOC_TYPE, true );
   //EnableControl( IDC_DTP_EFF_DATE, true );
   GetDlgItem( IDC_BTN_DELETE_SHR_ALLOC )->EnableWindow( true );
   GetDlgItem( IDC_BTN_ADD_ACCT_ALLOC )->EnableWindow( true );
   CheckPermission();
}

//******************************************************************************

void AllocationsDlg::OnBtnAddAcctAlloc() 
{
   AddToListControl( IDC_LV_ACCT_ALLOC );

   /*#ifdef _DEBUG
   const DString &dstrShrLvKey = GetList( IDC_LV_SHR_ALLOC )->GetCurrentKey();
   const DString &dstrShrKey = getParent()->getCurrentListItemKey(this, ALLOCATIONSPROC::SHR_ALLOCATIONS_LIST);
   assert( dstrShrLvKey == dstrShrKey );
   #endif*/

   GetDlgItem( IDC_BTN_DELETE_ACCT_ALLOC )->EnableWindow( true );
   GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( true );
   CheckPermission();
}

//******************************************************************************

void AllocationsDlg::OnBtnAddFundAlloc() 
{
   if( (m_rbUsage == 0) || (m_rbUsage == 3) )                                 //default or trade allocations 
      AddToListControl( IDC_LV_FUND_ALLOC );
   else  //systematic allocations
      AddToListControl( IDC_LV_SYS_FUND_ALLOC );

   GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( true );
   CheckPermission();
}

//******************************************************************************

void AllocationsDlg::OnBtnDeleteShrAlloc() 
{
   DeleteFromListControl( IDC_LV_SHR_ALLOC );
   if( !GetList( IDC_LV_SHR_ALLOC )->GetItemCount() )
   {
      assert( !GetList( IDC_LV_ACCT_ALLOC )->GetItemCount() );
      assert( !GetList( IDC_LV_FUND_ALLOC )->GetItemCount() );
      GetDlgItem( IDC_BTN_DELETE_SHR_ALLOC )->EnableWindow( false );
      GetDlgItem( IDC_BTN_DELETE_ACCT_ALLOC )->EnableWindow( false ); 
      GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( false );
      GetDlgItem( IDC_BTN_ADD_ACCT_ALLOC )->EnableWindow( false );  
      GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( false );
   }
}

//******************************************************************************

void AllocationsDlg::OnBtnDeleteAcctAlloc() 
{
   DeleteFromListControl( IDC_LV_ACCT_ALLOC );
   if( !GetList( IDC_LV_ACCT_ALLOC )->GetItemCount() )
   {
      LoadListControl( IDC_LV_FUND_ALLOC );
      assert( !GetList( IDC_LV_FUND_ALLOC )->GetItemCount() );
      GetDlgItem( IDC_BTN_DELETE_ACCT_ALLOC )->EnableWindow( false );
      GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( false );
      GetDlgItem( IDC_BTN_ADD_FUND_ALLOC )->EnableWindow( false );
   }
#ifdef _DEBUG
   const DString &dstrCurrShrAllocKey = getParent()->getCurrentListItemKey(
                                                                          this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
   const DString &dstrCurrAcctAllocKey = getParent()->getCurrentListItemKey(
                                                                           this, IFASTBP_PROC::ACCT_ALLOCATIONS_LIST );
   const DString &dstrCurrFundAllocKey = getParent()->getCurrentListItemKey(
                                                                           this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST );
#endif
}

//******************************************************************************

void AllocationsDlg::OnBtnDeleteFundAlloc() 
{
   int iListControlId;
   if( (m_rbUsage == 0) || (m_rbUsage == 3) )                      //default and trade allocations
      iListControlId = IDC_LV_FUND_ALLOC;
   else                                      //OneTime Allocations or Automatic Transfers
      iListControlId = IDC_LV_SYS_FUND_ALLOC;

   DeleteFromListControl( iListControlId );
   GetDlgItem( IDC_BTN_DELETE_FUND_ALLOC )->EnableWindow( GetList(iListControlId)->GetItemCount() );
   CheckPermission();
}

//******************************************************************************

void AllocationsDlg::OnBtnReset() 
{
   if( m_rbUsage == 0 )                         //default allocations active
   {
      ResetListItem( IDC_LV_SHR_ALLOC );
      //EnableControl( IDC_CMB_ALLOC_TYPE, true );
   }
   else if( m_rbUsage == 1 )                                       //systematic allocations active
      ResetListItem( IDC_LV_SYS_FUND_ALLOC );
   else if( m_rbUsage == 2 )
   {      
      //ResetListItem( IDC_LV_SYS_FUND_ALLOC );
	  ResetListItem(  IDC_LV_AUTO_SHR_ALLOC );
   }
   else if( m_rbUsage == 3 )
      ResetListItem( IDC_LV_SHR_ALLOC );

}

//******************************************************************************

void AllocationsDlg::OnChkReplace() 
{
   m_bReplaceAsDefault = !m_bReplaceAsDefault;
   DString dstrReplaceAsDefault = ( m_bReplaceAsDefault ) ? YES : NO;

   if( m_rbUsage == 2 )
   {
      getParent()->setField(this, IFASTBP_PROC::AT_ACCT_TRANS_LIST_AS_CBO, ifds::ReplaceAsDefault, 
                            dstrReplaceAsDefault, false);
   }
   else
   {
      if( m_lOneTimeList == IFASTBP_PROC::TRADES_LIST || m_lOneTimeList == IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST )
         getParent()->setField(this, m_lOneTimeList, ifds::SetAsDefault, dstrReplaceAsDefault, false);
      else
         getParent()->setField( this, IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST_AS_CBO, 
                                ifds::ReplaceAsDefault, dstrReplaceAsDefault, false );
   }
}

//-------------------------------------------------------------------------------------------------------
void AllocationsDlg::OnBtnAutoAddAcctAlloc() 
{
   if( m_rbUsage == 2 )
   {
      AddToListControl( IDC_LV_AUTO_SHR_ALLOC );
      LoadListControl( IDC_LV_SYS_FUND_ALLOC );
   }
}
//--------------------------------------------------------------------------------------------------------
void AllocationsDlg::OnBtnAutoDeleteAcctAlloc() 
{
   if( m_rbUsage == 2 )
   {
      DeleteFromListControl( IDC_LV_AUTO_SHR_ALLOC );
      LoadListControl( IDC_LV_SYS_FUND_ALLOC );
   }
}

//----------------------------------------------------------------------------------------------------------

LRESULT AllocationsDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );
   DString strMarket = DSTCommonFunctions::getMarket();

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;      
      DString dstrShareholder;  
      DString dstrAccountNum;
      getParent()->getField( this, ifds::ShrNum,    dstrShareholder );
      dstrShareholder.strip().stripLeading( I_CHAR( '0' ) );

      switch( m_rbUsage )
      {
         case 0:  // default allocation
//            getParent()->getField( this, ALLOCATIONSPROC::ACCT_ALLOCATIONS_LIST, DBR::AccountNum, dstrAccountNum );
            getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum );
            break;

         case 1:  // one time allocation
         case 3:
            if( m_lOneTimeAllocList ==  IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST )
               getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum,    dstrAccountNum );
            else
               getParent()->getField( this, m_lOneTimeList, ifds::AccountNum,    dstrAccountNum );
            break;

         case 2:  // automaticlly allocation
            getParent()->getField( this, IFASTBP_PROC::AT_ACCT_TRANS_LIST, ifds::AllocAccountNum, dstrAccountNum, false); 
            break;

            /* case 3: //one time trade allocation
                   getParent()->getField( this, m_lOneTimeList, DBR::AccountNum,    dstrAccountNum );*/

      }

      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
      setParameter ( SHR_NUM , dstrShareholder );
      setParameter ( ACCT_NUM , dstrAccountNum );

      // Set FUND Code for Fund Dialog
      switch( m_uiClassCodeDialogItem )
      {
         case IDC_EDT_FUND:
         case IDC_EDT_SYS_FUND:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUND_CODE, dstrFundCode );
               setParameter( CLASS_CODE, NULL_STRING );
               setParameter( FUNDNUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_CLASS:
         case IDC_EDT_SYS_CLASS:
            {
               CString cstrFundClass;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUND_CODE, NULL_STRING );
               setParameter( CLASS_CODE, dstrFundClass );
               setParameter( FUNDNUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_FUND_NUMBER:
         case IDC_EDT_SYS_FUND_NUMBER:
            {
               CString cstrFundNumber;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundNumber );
               DString dstrFundNumber = cstrFundNumber;
               setParameter( FUND_CODE, NULL_STRING );
               setParameter( CLASS_CODE, NULL_STRING );
               setParameter( FUNDNUMBER, dstrFundNumber );
            }
            break;
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( FUND_CODE, dstrFundCode );
               getParameter ( CLASS_CODE, dstrClassCode );

               DString strMarket = DSTCommonFunctions::getMarket();
               if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
               {
                  getParameter ( FUNDNUMBER, dstrFundNumber );
                  if( dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING )
                     dstrFundNumber = NULL_STRING;
               }

               switch( m_rbUsage )
               {
                  case 0:
                     getParent()->setField (this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST , ifds::FundCode, dstrFundCode );
                     getParent()->setField (this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST , ifds::ClassCode, dstrClassCode );
                     LoadControl ( IDC_EDT_FUND );
                     LoadControl ( IDC_EDT_CLASS );
                     if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                     {
                        getParent()->setField (this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST , ifds::ToFundNumber, dstrFundNumber );
                        LoadControl ( IDC_EDT_FUND_NUMBER );
                     }
                     break;
                  case 3:
                     getParent()->setField (this, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST , ifds::FundCode, dstrFundCode );
                     getParent()->setField (this, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST , ifds::ClassCode, dstrClassCode );
                     LoadControl ( IDC_EDT_FUND );
                     LoadControl ( IDC_EDT_CLASS );
                     if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                     {
                        getParent()->setField (this, IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST , ifds::ToFundNumber, dstrFundNumber );
                        LoadControl ( IDC_EDT_FUND_NUMBER );
                     }
                     break;
                  case 1:
                     if( m_lOneTimeAllocList == IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST ||
                         m_lOneTimeAllocList == IFASTBP_PROC::RRIF_LIF_LRIF_ALLOC_LIST )
                     {
                        getParent()->setField (this, m_lOneTimeAllocList , ifds::FundCode, dstrFundCode );
                        getParent()->setField (this, m_lOneTimeAllocList , ifds::ClassCode, dstrClassCode );
                     }

                     if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                     {
                        getParent()->setField (this, m_lOneTimeAllocList , ifds::ToFundNumber, dstrFundNumber );
                        LoadControl ( IDC_EDT_SYS_FUND_NUMBER );
                     }
                     if( m_rbUsage == 1 )
                     {
                        LoadControl ( IDC_EDT_SYS_FUND );
                        LoadControl ( IDC_EDT_SYS_CLASS );
                     }
                     break;

                  case 2:
                     getParent()->setField (this, IFASTBP_PROC::AT_FUND_TRANS_LIST , ifds::FundCode, dstrFundCode );
                     getParent()->setField (this, IFASTBP_PROC::AT_FUND_TRANS_LIST , ifds::ClassCode, dstrClassCode );
                     if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                     {
                        getParent()->setField (this, IFASTBP_PROC::AT_FUND_TRANS_LIST , ifds::ToFundNumber, dstrFundNumber );
                        LoadControl ( IDC_EDT_SYS_FUND_NUMBER );
                     }
                     LoadControl ( IDC_EDT_SYS_FUND );
                     LoadControl ( IDC_EDT_SYS_CLASS );
                     break;

               }
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

void AllocationsDlg::SetUserAccesFuncCode()
{
   TRACE_METHOD( CLASSNAME, I_("SetUserAccesFuncCode") );

   if( m_dstrAllocType == ALLOCATIONSPROC::SHAREHOLDER_DEFAULT )
      SetUserAccesFunctionCode(UAF::DEFAULT_ALLOCATION);
   else if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME )
   {
      if( m_strTransType == TRADETYPE::PAC )
         SetUserAccesFunctionCode(UAF::PAC);
      else if( m_strTransType == TRADETYPE::SWP )
         SetUserAccesFunctionCode(UAF::SWP);
      else
         SetUserAccesFunctionCode(NULL);
   }
   else if( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER )
      SetUserAccesFunctionCode(UAF::AUTOMATIC_TRANSFER);
   else if( m_dstrAllocType == ALLOCATIONSPROC::RRIF_LIF_LRIF_ONE_TIME )
      SetUserAccesFunctionCode(UAF::RIF_LIF_LRIF_INFO);
   else if( m_dstrAllocType == ALLOCATIONSPROC::TRADE_ONE_TIME )
   {      
      if( m_strTradeTransType == TRADETYPE::PURCHASE ) {
         SetUserAccesFunctionCode(UAF::TRADING_PURCHASE);                     
      }
      else if( ( m_strTradeTransType == TRADETYPE::EXCHANGE) || ( m_strTradeTransType == TRADETYPE::TRANSFER) )
         SetUserAccesFunctionCode(UAF::TRADING_EXCHANGE);
      else if( m_strTradeTransType == TRADETYPE::REDEMPTION || m_strTradeTransType == TRADETYPE::MGMT_FEE || TRADETYPE::ADMIN_FEE  )
         SetUserAccesFunctionCode(UAF::TRADING_REDEMPTION);
      else
         SetUserAccesFunctionCode(NULL);        
      DString dstrDefaultAllocOverride;
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
      if( pDSTCWorkSession ) {
         pDSTCWorkSession->getOption( ifds::DefaultAllocOverride, dstrDefaultAllocOverride, idDataGroup, false );
         if ( dstrDefaultAllocOverride == YES) {
            DString dstrAMSCode;
            getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AMSCode, dstrAMSCode,true );
            if ( hasUpdatePermission(GetUserAccesFunctionCode()) && dstrAMSCode.strip() != NULL_STRING) {
               SetUserAccesFunctionCode(UAF::AMS_MIX_OVERRIDE);
            }
         }
      } else {
         // Worksession is null for some reason.
         assert (0);
      }      
   }
   else if( m_dstrAllocType == ALLOCATIONSPROC::TRANSACTION_ONE_TIME )
      SetUserAccesFunctionCode(UAF::TRANSACTION_HISTORY);   
}

//******************************************************************************

void AllocationsDlg::CheckPermission()
{
   TRACE_METHOD( CLASSNAME, I_("CheckPermission") );
   if( GetUserAccesFunctionCode() == UAF::DEFAULT_ALLOCATION )
      BaseDlg::CheckPermission();
   else
   {
      bool bModiPerm = false;
      bool bAddPerm = false;
      DString dstrPACSWPOverride;
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
      if( pDSTCWorkSession )
         pDSTCWorkSession->getOption( ifds::PACSWPOverride, dstrPACSWPOverride, idDataGroup, false );
      DString dstrAMSCode;
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AMSCode, dstrAMSCode,true );
      if (( dstrPACSWPOverride == YES) && (( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME ) ||
         ( m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER )) && (dstrAMSCode != NULL_STRING) ){
         bModiPerm = false;
         bAddPerm = false;
      } else {
         bModiPerm = hasUpdatePermission(GetUserAccesFunctionCode());
         bAddPerm = hasCreatePermission(GetUserAccesFunctionCode());
      }
      //bool bDelPerm = hasPermission(GetUserAccesFunctionCode(), DBR::DelPerm);
      //if user has 'modify' or 'add' or a combination of them enable all buttons, otherwise disable them all
      if( bModiPerm || bAddPerm )
         EnableAllButtons(true);
      else
         EnableAllButtons(false);
   }
}

//******************************************************************************

void AllocationsDlg::EnableAllButtons(bool bEnable)
{
   TRACE_METHOD( CLASSNAME, I_("EnableAllButtons") );
   GetDlgItem(IDC_BTN_ADD_SHR_ALLOC)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_AUTO_ADD_SHR_ALLOC)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_ADD_ACCT_ALLOC)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_ADD_FUND_ALLOC)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_DELETE_SHR_ALLOC)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_AUTO_DELETE_SHR_ALLOC)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_DELETE_ACCT_ALLOC)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_DELETE_FUND_ALLOC)->EnableWindow(bEnable);
   GetDlgItem(IDOK)->EnableWindow(bEnable);
}
//******************************************************************************

void AllocationsDlg::checkAllocType()
{
   TRACE_METHOD( CLASSNAME, I_("checkAllocType") );
   //for default allocations if trading, hide combo box AcctNum/Type and show instead edit box AcctNum
   if( m_rbUsage != 0 )
      return;
   DString strTransType;
   getParent()->getField(this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, strTransType, false);
   if( (strTransType == TRADETYPE::PURCHASE) || (strTransType == TRADETYPE::REDEMPTION) || (strTransType == TRADETYPE::EXCHANGE) || (strTransType == TRADETYPE::TRANSFER) || (strTransType == I_("DD")) )
   {
      // trading
      ShowControl( IDC_CMB_ACCT_TAX, false );
      GetDlgItem( IDC_TXT_ACCT_TAX )->ShowWindow( false );
      ShowControl( IDC_EDIT_ACC_NUM, true );
      GetDlgItem( IDC_EDIT_ACC_NUM )->EnableWindow( strTransType == TRADETYPE::TRANSFER );
      GetDlgItem( IDC_TXT_ACCT_NUM )->ShowWindow( true );
   }
   else
   {
      ShowControl( IDC_CMB_ACCT_TAX, true );
      GetDlgItem( IDC_TXT_ACCT_TAX )->ShowWindow( true );
      ShowControl( IDC_EDIT_ACC_NUM, false );
      GetDlgItem( IDC_TXT_ACCT_NUM )->ShowWindow( false );
   }
}
//******************************************************************************

void AllocationsDlg::OnSelchangeCmbAcctTax() 
{
   TRACE_METHOD( CLASSNAME, I_("OnSelchangeCmbAcctTax") );
   //checkAllocType();
}

//******************************************************************************
void AllocationsDlg::OnBtnSplitCom() {

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSplitCom" ) );
   E_COMMANDRETURN eRtn;

   bool bModal = true;   // Default to modeless

   CWaitCursor wait;
   try
   {
      getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, m_dstrAccountNum, false);
      setParameter(SPLITCOMM::ACCOUNT_NUM, m_dstrAccountNum);
      if (m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME)
      {
         const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::SYSTEMATIC_LIST));
         const DString *pAllocCurKey = &(getParent()->getCurrentListItemKey(this, 
            IFASTBP_PROC::SYSTEMATIC_ALLOCATIONS_LIST));

         setParameter(SPLITCOMM::MAIN_LIST_KEY, *pCurKey);
         setParameter(SPLITCOMM::CALLER, SPLITCOMM::SYSTEMATIC_ALLOCATION);
         setParameter(SPLITCOMM::ALLOCATION_LIST_KEY, *pAllocCurKey);
      }
      else if (m_dstrAllocType == ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER)
      {
         const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::SYSTEMATIC_LIST));
         const DString *pAllocCurKey = &(getParent()->getCurrentListItemKey(this, 
            IFASTBP_PROC::AT_FUND_TRANS_LIST));

         setParameter(SPLITCOMM::MAIN_LIST_KEY, *pCurKey);
         setParameter(SPLITCOMM::CALLER, SPLITCOMM::SYSTEMATIC_ATALLOCATION);      
         setParameter(SPLITCOMM::ALLOCATION_LIST_KEY, *pAllocCurKey);
      }
      else if (m_dstrAllocType == ALLOCATIONSPROC::TRADE_ONE_TIME)
      {
         DString dstrKey, dstrAccountNum;
         DString dstrTransTypeDesc(NULL_STRING);
      
         const DString *pAllocCurKey = &(getParent()->getCurrentListItemKey(this, 
            IFASTBP_PROC::TRADE_FUND_ALLOCATION_LIST));
         getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType,  dstrTransTypeDesc, true);
         dstrTransTypeDesc.strip();
         getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, dstrAccountNum, false);
         getParent()->getField(this, BF::NullContainerId, ifds::SystematicKey, dstrKey);
         //set the parameters on the split commission process
         setParameter(SPLITCOMM::ACCOUNT_NUM, dstrAccountNum);
         setParameter(SPLITCOMM::CALLER, SPLITCOMM::TRADE_ALLOCATION);
         setParameter(SPLITCOMM::MAIN_LIST_KEY, dstrKey);
         setParameter(SPLITCOMM::TRANSACTION_TYPE_DESC, dstrTransTypeDesc);
         setParameter(SPLITCOMM::ALLOCATION_LIST_KEY, *pAllocCurKey);
      }
      eRtn = getParentProcess()->invokeProcessFromChild(this, CMD_BPROC_SPLITCOMMISSION, PROC_SUPPORT);
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

//********************************************************************
LRESULT AllocationsDlg::OpenIdentifyAccountsDlg( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,CLASSNAME,I_( "OpenIdentifyAccountsDlg" ) );   
   bool bRetVal = false;
   BaseControl *pBC = NULL;
   try
   {
      setParameter( IDENTACCPROC::FROM_SYSTEMATIC, I_("Y") );

      switch( getParentProcess( )->invokeProcessFromChild( this,CMD_BPROC_IDENT_ACC,PROC_SUPPORT ) )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstAcctNum = NULL_STRING;
               getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstAcctNum );
               dstAcctNum.strip();
               if( m_uiAccItem == IDC_EDT_AUTO_ACCT_TAX )
               {
                  bRetVal = SetControlText( IDC_EDT_AUTO_ACCT_TAX, dstAcctNum );
                  pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_AUTO_ACCT_TAX ));
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();

                  if( !bRetVal )
                  {
                     if( pBC )
                     {
                        if( pBC->IsToolTipVisible() )
                           pBC->ToggleToolTip();

                        pBC->Load();
                     }
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

bool AllocationsDlg::isFundGroupApplicable()
{
   TRACE_METHOD( CLASSNAME, I_("isFundGroupApplicable") );
   //fund group is applicable only if 
   //1. allocation screen is default allocation screen
   //2. XSFundsValidate  generic control is YES
   //3. allocation type is XS - foreign content rebalancing

   //1.
   if (m_rbUsage != 0)
      return false;

   //2.
   DString strFundGroupApplic = NO;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(  ifds::XSFundsValidate , strFundGroupApplic, BF::HOST, false );
   if (strFundGroupApplic.strip() != YES)
      return false;

   //3.
   DString strTransType;
   if ( getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST) )
      getParent()->getField( this,  IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, strTransType, false);
   if (strTransType.strip() != FOREIGN_CONTENT_REBALANCING)
      return false;

   return true;
}

//******************************************************************************

bool AllocationsDlg::doDisablePermCheckButton(UINT nID)
{
   if( nID == IDC_BTN_ADD_ACCT_ALLOC )
   {
      const DString *pDstrKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
      if( pDstrKey && !pDstrKey->empty() )
      {
         // Management Fee or Foreign Content Rebalancing
         DString dstrTransType;
         getParent()->getField( this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, dstrTransType, false);
			return true;
         //return( dstrTransType.strip() == MANAGEMENT_FEE_CODE || dstrTransType.strip() == FOREIGN_CONTENT_REBALANCING );
      }
   }
   else if( nID == IDC_BTN_ADD_FUND_ALLOC )
   {
      const DString *pDstrKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
      if( pDstrKey && !pDstrKey->empty() )
      {
         // disable for Management Fee && AMS Rebalancing
         DString dstrTransType;
         getParent()->getField( this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, dstrTransType, false);
         return( dstrTransType.strip() == MANAGEMENT_FEE_CODE || 
			     dstrTransType.strip() == REBALANCING_CODE );
      }
   }
   else if( nID == IDC_BTN_DELETE_ACCT_ALLOC )
   {
      return true;  // disable delete button
   }
   else if( nID == IDC_BTN_DELETE_SHR_ALLOC ||
	        nID == IDC_BTN_DELETE_FUND_ALLOC )
   {
      const DString *pDstrKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST );
      if( pDstrKey && !pDstrKey->empty() )
      {		  
         // AMS Rebalancing
         DString dstrTransType;
         getParent()->getField( this, IFASTBP_PROC::SHR_ALLOCATIONS_LIST, ifds::TransType, dstrTransType, false);
		 if( dstrTransType.strip() == REBALANCING_CODE )
		 {
			if( nID == IDC_BTN_DELETE_SHR_ALLOC && !_blNewShrItem )
			{
			   return true;// disable delete button for Shr level
			}
			else if ( nID == IDC_BTN_DELETE_FUND_ALLOC )
			{
			   return true;// disable delete button for Fund/Class level
			}
		 }
      }
   }

   return false;  // return true to disable
}

bool AllocationsDlg::isFELCommApplicable()
{
   bool bRetVal = false;
   DString strFELCommOnGrant;
   DSTCWorkSession *pDSTCWorkSession = NULL;
   pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   pDSTCWorkSession->getOption( ifds::FELCommOnGrant, strFELCommOnGrant, BF::HOST, false );
   if( strFELCommOnGrant == YES)
   {
	   bRetVal = m_rbUsage == 0;
   }

   return bRetVal;
}

bool AllocationsDlg::hasFrontEndLoadCommission()
{
   bool bRetVal = false;

   AllocationsProcess* pAllocationsProcess = dynamic_cast<AllocationsProcess*>(getParent());

   if(pAllocationsProcess)
   {
      bRetVal = pAllocationsProcess->hasFrontEndLoadCommission();
   }

   return bRetVal;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AllocationsDlg.cpp-arc  $
 * 
 *    Rev 1.115   Dec 19 2011 02:43:04   wichian
 * IN#2578362 - Prevent user from inputting negative value, chars and not allow more than 4 precisions.
 * 
 *    Rev 1.114   18 Feb 2009 15:53:50   kovacsro
 * IN#1591952 - Error mssg when processing Purchase with multi Fund Alloc (fixed the crash when user tries to open the allocation screen from trading)
 * 
 *    Rev 1.113   28 Jan 2009 10:48:20   kovacsro
 * IN#1555838 - Issues on the field FeeComm (fixed crash for new allocation setup)
 * 
 *    Rev 1.112   Jan 22 2009 00:47:22   sopitwek
 * PET22486 FN03 IN1555932 - Issues on the field FeeComm - Fixed FELComm format.
 * 
 *    Rev 1.111   Jan 20 2009 01:57:46   sopitwek
 * PET22486 FN03 IN1555932 - Issues on the field FeeComm
 * 
 *    Rev 1.110   16 Dec 2008 13:26:30   kovacsro
 * IN#1179969 - Error messages on allocated SMART (fixed the reset issue)
 * 
 *    Rev 1.109   16 Dec 2008 09:34:26   kovacsro
 * PET22486 - FN03 - RESP Grant Commission - code review
 * 
 *    Rev 1.108   Dec 11 2008 09:21:30   sopitwek
 * PET22486 - FN03 - RESP Grant Commission
 * 
 *    Rev 1.107   29 Feb 2008 10:03:54   kovacsro
 * IN#1038318 - new requirement: also disabled Add/Del buttons at fund level for RB
 * 
 *    Rev 1.106   19 Oct 2007 16:20:24   kovacsro
 * IN#1038318 - added rej erros / hard edit to prevent users from entering future dated Stop dates on AMS and modifying Effective Date for RB/RO default allocations on Allocation screen
 * 
 *    Rev 1.105   Oct 23 2006 11:01:40   fengyong
 * Incident #698369 - fix reset issue
 * 
 *    Rev 1.104   Sep 15 2005 15:10:22   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.103   Mar 08 2005 12:08:12   aguilaam
 * IN 243381 - allow only valid account numbers on allocation screen
 * 
 *    Rev 1.102   Nov 14 2004 15:00:32   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.101   Sep 17 2004 18:04:30   ZHANGCEL
 * PET1094 -- AdminFee user access function check is the same as Redemption
 * 
 *    Rev 1.100   Feb 12 2004 15:59:02   YINGBAOL
 * PTS 10021233: Multi allocation at account level is not been supported
 * 
 *    Rev 1.99   Sep 01 2003 21:23:38   popescu
 * PET 809 FN 02 CIBC Multi Fund Transfer
 * 
 *    Rev 1.98   Aug 17 2003 12:46:38   popescu
 * set the selection on the allocation list based on the alocation item selected in Trade dialog
 * 
 *    Rev 1.97   Aug 15 2003 15:19:30   HSUCHIN
 * sync up with 1.95.1.0
 * 
 *    Rev 1.96   Aug 15 2003 15:16:52   HSUCHIN
 * added AMS restirction security check
 * 
 *    Rev 1.95   May 14 2003 11:15:52   popescu
 * added extra param to the process layer, which is used to pass the key string of the current selected item in the allocations list, in order to set selection on it in split commission dialog
 * 
 *    Rev 1.94   May 13 2003 18:19:48   HERNANDO
 * Prudential Broker Level Fee - PET792.FN07.2. Mod.
 * 
 *    Rev 1.93   May 13 2003 10:07:24   popescu
 * Split commission re-work
 * 
 *    Rev 1.92   Apr 25 2003 14:32:14   HERNANDO
 * Prudential Broker Level Fee - PET792.FN07.2 -  Added doDisablePermCheckButton.
 * 
 *    Rev 1.91   Mar 21 2003 18:32:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.90   Jan 12 2003 18:57:28   KOVACSRO
 * Added FundGroup control
 * 
 *    Rev 1.89   Oct 09 2002 23:55:28   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.88   Sep 30 2002 11:01:32   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.87   Sep 04 2002 13:45:48   KOVACSRO
 * Fixed RRIFAmount display.
 * 
 *    Rev 1.86   Aug 29 2002 12:57:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.85   Aug 07 2002 16:29:06   KOVACSRO
 * 1. PTS 10009225 : radio buttons.
 * 2. rrif fixes
 * 
 *    Rev 1.84   Aug 06 2002 10:04:04   KOVACSRO
 * Release 48. Converted RRIF allocations.
 * 
 *    Rev 1.83   Jul 24 2002 17:09:32   KOVACSRO
 * bug fixed for delete acct level button.
 * 
 *    Rev 1.82   Jul 18 2002 17:20:10   KOVACSRO
 * getting TransType as a parameter.
 * 
 *    Rev 1.81   22 May 2002 19:15:38   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.80   21 May 2002 10:08:42   KOVACSRO
 * Bug fixed for SplitComm.
 * 
 *    Rev 1.79   08 May 2002 17:09:08   KOVACSRO
 * new allocation design fixes.
 * 
 *    Rev 1.78   29 Apr 2002 16:37:20   KOVACSRO
 * new trade allocations.
 * 
 *    Rev 1.77   22 Apr 2002 17:07:54   KOVACSRO
 * code cleanup. Some controls only belong to a specific alloc. type, so if we don't display them for the current type, we shouldn't populate the container (tunning)
 * 
 *    Rev 1.76   22 Apr 2002 10:06:54   KOVACSRO
 * Rel.47 : new design for Allocations.
 * 
 *    Rev 1.75   27 Mar 2002 20:00:52   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.74   05 Mar 2002 11:51:18   KOVACSRO
 * Filtering out those trades for which allocations are not allowed.
 * 
 *    Rev 1.73   Nov 17 2001 14:42:10   YINGBAOL
 * disable splitCommision button for RRIF Allocation
 * 
 *    Rev 1.72   05 Nov 2001 15:48:32   KOVACSRO
 * hasPermission() changes
 * 
 *    Rev 1.71   21 Oct 2001 14:15:24   HSUCHIN
 * bug fix for selecting the right trade in a multi trade transaction
 * 
 *    Rev 1.70   03 Oct 2001 14:18:10   WINNIE
 * fix crash for RRIF
 * 
 *    Rev 1.69   Sep 13 2001 10:56:08   YINGBAOL
 * sync. up version 1.67.1.1
 * 
 *    Rev 1.68   Sep 06 2001 14:04:14   ZHANGCEL
 * Added second parameter in ListViewControlFilter()
 * 
 *    Rev 1.67   Aug 27 2001 18:21:32   YINGBAOL
 * allow displaying sysallocation with amount type = unit
 * 
 *    Rev 1.66   Aug 10 2001 12:53:16   YINGBAOL
 * disable NASU if identAcctDlg lauched from systematic and allocation screen
 * 
 *    Rev 1.65   Aug 09 2001 11:03:58   YINGBAOL
 * minor change
 * 
 *    Rev 1.64   Aug 09 2001 10:25:18   YINGBAOL
 * account allocation enhancement
 * 
 *    Rev 1.63   Aug 05 2001 03:10:50   YINGBAOL
 * fix reset problem
 * 
 *    Rev 1.62   Aug 02 2001 22:07:22   YINGBAOL
 * dynamic load one_time_allocation title
 * 
 *    Rev 1.61   Jul 17 2001 19:49:56   ZHANGCEL
 * Disable AllocType combo box after user adds a new item and select a type. 
 * 
 *    Rev 1.60   09 Jul 2001 11:01:06   HSUCHIN
 * getField fix for DBR::SplitComm
 * 
 *    Rev 1.59   13 Jun 2001 09:51:54   KOVACSRO
 *  TradeAllocAmount no longer guifield (because it was not showing the error message)
 * 
 *    Rev 1.58   31 May 2001 15:21:52   KOVACSRO
 * Sync up SSB (1.56.11.6))
 * 
 *    Rev 1.57   03 May 2001 14:07:22   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.56   Apr 06 2001 15:16:54   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.55   06 Apr 2001 10:24:48   KOVACSRO
 * Added F4 key perm. check.
 * 
 *    Rev 1.54   04 Apr 2001 07:07:58   HSUCHIN
 * Disable Split Commission for Default Allocation temporary
 * 
 *    Rev 1.53   03 Apr 2001 20:25:04   HSUCHIN
 * split commissions hook up and bug fix
 * 
 *    Rev 1.52   01 Apr 2001 12:56:20   HSUCHIN
 * added splitcomm button
 * 
 *    Rev 1.51   27 Mar 2001 16:44:54   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.50   22 Mar 2001 16:54:00   KOVACSRO
 * Bug fixed regarding transfer allocations.
 * 
 *    Rev 1.49   18 Mar 2001 15:38:54   KOVACSRO
 * Disabled Add and Delete buttons until we'll allow multiple account allocations.
 * 
 *    Rev 1.48   16 Mar 2001 16:55:58   KOVACSRO
 * Field name changes (AccountAllocation)
 * 
 *    Rev 1.47   15 Mar 2001 11:03:12   KOVACSRO
 * Some bug fixes. Still not fully functional.
 * 
 *    Rev 1.46   10 Mar 2001 18:04:44   KOVACSRO
 * one bug already fixed for Trade Account Allocation.
 * 
 *    Rev 1.45   10 Mar 2001 17:13:50   KOVACSRO
 * Many, many changes...First try for Trade  Account Allocation. It's not fully functional, yet.
 * 
 *    Rev 1.44   01 Mar 2001 16:37:38   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.43   Feb 13 2001 09:11:36   JANKAREN
 * bug fix
 * 
 *    Rev 1.42   Feb 12 2001 16:21:24   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.41   Feb 07 2001 13:59:06   DINACORN
 * M3/C4 synchronization
 * 
 *    Rev 1.40   Jan 19 2001 17:57:30   DINACORN
 * Fix bug error "No fund found"
 * 
 *    Rev 1.39   Dec 14 2000 11:06:04   KOVACSRO
 * Changed permission logic for non DEFAULT Alloc.
 * 
 *    Rev 1.38   Dec 13 2000 15:04:58   KOVACSRO
 * 1. Modified DoListItemChanged.
 * 2.Added Dummy Item logic for perm. check.
 * 
 *    Rev 1.37   Dec 07 2000 16:15:20   KOVACSRO
 * Added new item permission logic.
 * 
 *    Rev 1.36   Dec 01 2000 15:24:26   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.35   Nov 24 2000 17:31:04   ZHANGCEL
 * Code clean up
 * 
 *    Rev 1.34   Nov 09 2000 16:25:32   ZHANGCEL
 * Fixed the bug regarding the fund searching 
 * 
 *    Rev 1.33   Nov 09 2000 14:48:34   ZHANGCEL
 * Fixed the bug regarding searching fund by name
 * 
 *    Rev 1.32   Oct 31 2000 09:39:26   DINACORN
 * Replace "Shareholder Nbr" with "Shareholder Number"
 * 
 *    Rev 1.31   Oct 23 2000 11:42:20   YINGBAOL
 * change Allocation type for RIF
 * 
 *    Rev 1.30   Sep 29 2000 13:29:16   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.29   Sep 27 2000 10:08:20   OLTEANCR
 * fixed fund/class selection - refresh issue 
 * 
 *    Rev 1.28   Sep 25 2000 11:25:28   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.27   Sep 22 2000 16:30:06   HUANGSHA
 * disable the amount field if TotalAmount for AT or OneTime allocation is zero
 * 
 *    Rev 1.26   Sep 13 2000 17:06:10   ZHANGCEL
 * Added code for RRIF_LIF_LRIF_Alloc stuffs
 * 
 *    Rev 1.25   Sep 06 2000 09:46:16   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.24   Sep 01 2000 16:38:36   HUANGSHA
 * Sync with M3
 * 
 *    Rev 1.23   Sep 01 2000 14:30:54   ZHANGCEL
 * RRIF_LIF_LRIF Allocation problem
 * 
 *    Rev 1.22   Aug 28 2000 10:01:38   ZHANGCEL
 * Fund number issues
 * 
 *    Rev 1.21   Aug 11 2000 14:14:14   PETOLESC
 * Added FundCodeNumber field.
 * 
 *    Rev 1.20   Jul 21 2000 14:31:48   HERNANDO
 * Fund/Class Parms are sent to Fund Process for Srch
 * 
 *    Rev 1.19   Jul 10 2000 13:16:04   HUANGSHA
 * remove the GetOverrideItemString() for Fund & Class (error disp)
 * 
 *    Rev 1.18   Jun 27 2000 11:04:04   HUANGSHA
 * bug fix
 * 
 *    Rev 1.17   May 29 2000 15:25:38   HSUCHIN
 * fixed minor bug for Fund/Class Search.  Using the wrong field definition for one time trade.
 * 
 *    Rev 1.16   May 19 2000 13:00:06   HSUCHIN
 * added Fund Search to Fund/Class Fields in dlg
 * 
 *    Rev 1.15   May 18 2000 16:24:46   HUANGSHA
 * Removed the Market condition for AT
 * 
 *    Rev 1.14   May 11 2000 11:48:24   HUANGSHA
 * Don't filter the Exchange Unit record for Trade Allocation
 * 
 *    Rev 1.13   May 10 2000 12:04:46   YINGBAOL
 * create a dummy record when load a list
 * 
 *    Rev 1.12   May 05 2000 17:10:00   HUANGSHA
 * Filter the One-time Trade list
 * 
 *    Rev 1.11   May 05 2000 16:22:18   YINGBAOL
 * fix
 * 
 *    Rev 1.10   May 05 2000 12:41:52   HUANGSHA
 * bug fix
 * 
 *    Rev 1.9   May 02 2000 14:04:00   HUANGSHA
 * release
 * 
 *    Rev 1.8   May 02 2000 10:04:02   HUANGSHA
 * fixed the bugs
 * 
 *    Rev 1.7   May 01 2000 09:37:56   YINGBAOL
 * Automatic transfer allocation added
 * 
 */





