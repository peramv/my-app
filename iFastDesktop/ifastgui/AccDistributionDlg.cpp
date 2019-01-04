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
// ^FILE   : AccDistributionDlg.cpp
// ^AUTHOR : Zijian Ying + Yingbao(INC 2)
// ^DATE   : 04/23/1999
//
// ^CLASS    : AccDistributionDlg
// ^SUBCLASS : BaseMainDlg
//
// ----------------------------------------------------------
//
// ^CLASS    : AccDistributionDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

   #include <bfproc\AbstractProcess.hpp>
   #include <ifastbp\AccountDistributionProcessIncludes.h>
   #include <uibase\ConditionMessageDialog.h>

#include "AccDistributionDlg.h"
#include <uibase\DSTComboBox.h>
#include <uibase\DstcFuncs.h>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <uibase\dstbutton.h>

   #include <uibase\DSTEdit.h>
   #include <uibase\dstlistctrl.h>
   #include <uibase\DSTOleDateTime.h>
   #include <ifastbp\MFCANInterProcParam.hpp>
   #include <ifastcbo\DSTCWorkSession.hpp>
   #include <ifastcbo\mgmtco.hpp>
   #include <ifastcbo\FundMasterList.hpp>
   #include <ifastcbo\FundMaster.hpp>
   #include <ifastbp\FundClassProcessIncludes.h>

//HllApi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstlistctrl.h>

#ifndef INCLUDED_MATH_H
#define INCLUDED_MATH_H
#include <math.h>
#endif


extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_DISTRIBUTION;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AccDistributionDlg > dlgCreator( CMD_GUI_DISTRIBUTION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AccDistributionDlg dialog
namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME               = I_( "AccDistributionDlg" );
   const I_CHAR * const LV_FROM                 = I_( "lvFrom" );
   const I_CHAR * const LV_TO                   = I_( "lvTo" ); 
   const I_CHAR * const CASH                    = I_( "CASH" ); 
   const I_CHAR * const E                       = I_( "E" );
   const I_CHAR * const YES                     = I_( "Y" );  
   const I_CHAR * const NO                      = I_( "N" );  
   const I_CHAR * const SEPARATOR               = I_( " " );
   const I_CHAR * const PERCENT_SIGN            = I_( " %" );
   const I_CHAR * const ACCOUNT_NUM             = I_( "AccountNum" );   
   const I_CHAR * const FUND_CODE               = I_( "FundCode" );
   const I_CHAR * const FUND_TO_CODE            = I_( "FundToCode" );
   const I_CHAR * const FUND_NUMBER             = I_( "Baycom" );
   const I_CHAR * const FUNDNUMBER              = I_( "FundNumber" );
   const I_CHAR * const CLASS_CODE              = I_( "ClassCode" );
   const I_CHAR * const CLASS_TO_CODE           = I_( "ClassToCode" );
   const I_CHAR * const TRANS_TYPE              = I_( "TransType" );
   const I_CHAR * const PAY_TYPE                = I_( "DistributionPayType" );
   const I_CHAR * const PERCENT                 = I_( "Percent" );
   const I_CHAR * const EFFECTIVE_DATE          = I_( "EffectDate" );
   const I_CHAR * const ALLOCPERCENT            = I_( "AllocPercent" );
   const I_CHAR * const pSHAREHOLDERID          = I_( "ShareholderNum" );
   const I_CHAR * const BANK_INSTRUCTION_TYPE   = I_( "BankInstrType" );
   const I_CHAR * const DISTRIBUTION            = I_( "Distribution" );
   const I_CHAR * const CLASS_CAPTION           = I_( "&Class:" );
   const I_CHAR * const CURRENCY_CAPTION        = I_( "&Currency:" );
   const I_CHAR * const ACCT_KEY                = I_( "ListKey" );
   const I_CHAR * const FUND_CLASS_KEY          = I_( "FundClassKey" );
   const I_CHAR * const SHR_NUM                 = I_( "ShrNum" );
   const I_CHAR * const ACCT_NUM                = I_( "AccountNum" );
   const I_CHAR * const CODE_BANKIDTYPE_ABA     = I_( "01" );
   const I_CHAR * const CODE_BANKIDTYPE_CANADA  = I_( "03" );
   const I_CHAR * const CODE_BANKIDTYPE_SWIFT   = I_( "04" );
   const I_CHAR * const CODE_BANKIDTYPE_JAPAN   = I_( "06" );
//DistributionPayType
   const I_CHAR * const EFT_TO_ACCOUNT             = I_( "E" ); 
   const I_CHAR * const INTERNATIONAL_WIRE         = I_( "I" );  
   const I_CHAR * const MANUAL_CHEQUE              = I_( "M" );  
   const I_CHAR * const SYSTEM_GENERATED_CHEQUE    = I_( "S" );  
   const I_CHAR * const VALIDATE_ADDR_CODE         = I_( "VALIDATE_ADDR_CODE" );
   const I_CHAR * const LOCK_TRANS_TYPE            = I_( "LOCK_TRANS_TYPE" );
   const I_CHAR * const WIRE                       = I_( "WIRE" );
   const I_CHAR * const CHQ                        = I_( "CHQ" );
   const I_CHAR * const CASH_ACCT_LEVEL            = I_("CS");//can't we be consistent? Why do we need CASH and CS in the same time?
   const I_CHAR * const REINVEST                   = I_("RI");
   const I_CHAR * const REDIRECT                   = I_("RD");
   const I_CHAR * const FUND_CURRENCY              = I_("01");
   const I_CHAR * const PREFERRED_CURRECNY         = I_("02");
   const I_CHAR * const EFT                        = I_( "E" );
   const I_CHAR * const DISTRIB_LEVEL              = I_("02");
   const I_CHAR * const DISTRIB_CATEGORY           = I_("2");
   const I_CHAR * const UNVERIFIED                 = I_("02");
   const I_CHAR * const CALLER                     = I_("Caller");
   const I_CHAR * const MONEY_MARKET			   = I_( "I" );
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//user access function codes
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId InqPerm;
   extern CLASS_IMPORT const BFTextFieldId ACHDividend;
   extern CLASS_IMPORT const BFTextFieldId AllFundsDistrib;
   extern CLASS_IMPORT const BFTextFieldId VerifyCategory;
   extern CLASS_IMPORT const BFTextFieldId DistributionHeadingVerifySet;
   extern CLASS_IMPORT const BFTextFieldId DistributionToHeadingVerifySet;
   extern CLASS_IMPORT const BFTextFieldId DistribInstrAsRatioOpt;
   extern CLASS_IMPORT const BFDecimalFieldId LastIDRate;
   extern CLASS_IMPORT const BFDecimalFieldId TotalDistribRate;
   extern CLASS_IMPORT const BFTextFieldId DistribInputMethod;
   extern CLASS_IMPORT const BFDecimalFieldId TotalAllocPercent;
}

namespace MFCAN_IP_PARAM
{
   extern CLASS_IMPORT const I_CHAR * const DISTRIB_GBCD;
   extern CLASS_IMPORT const I_CHAR * const VERIFY_STAT;
}

//******************************************************************************

AccDistributionDlg::AccDistributionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AccDistributionDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ) 
, m_hAccel( 0 )
, m_uiDialogItem( 0 )
, m_bScreenClose (false)
, m_bEsc (false)
{
   //{{AFX_DATA_INIT(AccDistributionDlg)
   m_rbInputMethod = -1;
   //}}AFX_DATA_INIT
}

//******************************************************************************

void AccDistributionDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AccDistributionDlg)
   DDX_Radio(pDX, IDC_RB_PERCENTAGE, m_rbInputMethod);
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(AccDistributionDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AccDistributionDlg)
ON_BN_CLICKED(IDC_BTN_BANK, OnBtnBank)
ON_BN_CLICKED(IDC_BTN_ADDRESS, OnBtnAddress)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADMINDATE, OnBtnAdmindate)
ON_COMMAND(ID_ACCEL_FROM, OnAccelFrom)
ON_COMMAND(ID_ACCEL_TO, OnAccelTo)
ON_BN_CLICKED(IDC_BTN_ADD_TO, OnBtnAddTo)
ON_BN_CLICKED(IDC_BTN_ADD_FROM, OnBtnAddFrom)
ON_BN_CLICKED(IDC_BTN_DELETE_FROM, OnBtnDeleteFrom)
ON_BN_CLICKED(IDC_BTN_DELETE_TO, OnBtnDeleteTo)
ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical)
ON_BN_CLICKED(IDC_BTN_MORE_FROM, OnBtnMoreFrom)
ON_BN_CLICKED(IDC_BTN_MORE_TO, OnBtnMoreTo)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_CBN_KILLFOCUS(IDC_CMB_TRANS_TYPE, OnKillfocusCmbTransType )
ON_EN_KILLFOCUS(IDC_EDT_ADDRESS_CODE, OnKillfocusEdtAddressCode )
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_CHECK_ACCOUNT_LEVEL, OnAllFundsMode)
ON_BN_CLICKED(IDC_RB_PERCENTAGE, OnRbPercentage)
ON_BN_CLICKED(IDC_RB_DISTRIBRATE, OnRbDistribRate)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AccDistributionDlg message handlers

//******************************************************************************

//******************************************************************

SEVERITY AccDistributionDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   getParameter(CALLER, m_dstrCaller);

   SEVERITY sevRtn = SEVERE_ERROR;
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************

BOOL AccDistributionDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
   bool bVerificationEnabled = false;
   pWorkSession->isVerificationEnabled ( idDataGroup, 
                                         DISTRIB_CATEGORY, 
                                         DISTRIB_LEVEL, 
                                         bVerificationEnabled);

   if ( bVerificationEnabled )
   {
      AddListControl( CLASSNAME, 
                      IDC_LV_FROM, 
                      LV_FROM, 
                      ifds::DistributionHeadingVerifySet, 
                      IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                      0, 
                      true/*, LISTFLAG_NOT_AUTO_ADD*/ );

      //AddListControl( CLASSNAME, 
      //                IDC_LV_TO, 
      //                LV_TO, 
      //                ifds::DistributionToHeadingVerifySet, 
      //                IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
      //                IDC_LV_FROM, true/*, LISTFLAG_NOT_AUTO_ADD*/ );
   }
   else
   {
      AddListControl( CLASSNAME, IDC_LV_FROM, LV_FROM, 
                      ifds::DistributionHeadingSet, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                      0, 
                      true/*, LISTFLAG_NOT_AUTO_ADD*/ );

      //AddListControl( CLASSNAME, IDC_LV_TO, LV_TO, 
      //                ifds::DistributionHeadingSet1, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
      //                IDC_LV_FROM, true/*, LISTFLAG_NOT_AUTO_ADD*/ );
   }
   
   AddListControl( CLASSNAME, IDC_LV_TO, LV_TO, 
                   ifds::DistributionHeadingSet1, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                   IDC_LV_FROM, true/*, LISTFLAG_NOT_AUTO_ADD*/ );

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
        AddControl( CTRL_EDIT, IDC_EDT_FROM_FUND_NUM, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                    ifds::FrFundNumber, CTRLFLAG_DEFAULT, IDC_LV_FROM );
        ConnectControl( IDC_EDT_FROM_FUND_NUM, true );
        EnableControl( IDC_EDT_FROM_FUND_NUM, true );

        AddControl( CTRL_EDIT, IDC_EDT_TO_FUND_NUM, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                    ifds::ToFundNumber, CTRLFLAG_DEFAULT, IDC_LV_TO );
        ConnectControl( IDC_EDT_TO_FUND_NUM, true );
        EnableControl( IDC_EDT_TO_FUND_NUM, true );
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      GetDlgItem( IDC_EDT_FROM_FUND_NUM )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_EDT_TO_FUND_NUM )->ShowWindow( SW_HIDE );
   }

   AddControl( CTRL_EDIT, IDC_EDT_FROM_FUND, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
               ifds::FundCode, CTRLFLAG_DEFAULT, IDC_LV_FROM );
   ConnectControl( IDC_EDT_FROM_FUND, true );
   EnableControl( IDC_EDT_FROM_FUND, true );

   AddControl( CTRL_EDIT, IDC_EDT_FROM_CLASS, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
               ifds::ClassCode, CTRLFLAG_DEFAULT, IDC_LV_FROM );
   ConnectControl( IDC_EDT_FROM_CLASS, true );
   EnableControl( IDC_EDT_FROM_CLASS, true );


   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
               ifds::EffectiveDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_FROM );
   ConnectControl( IDC_DTP_EFF_DATE, true );
   EnableControl( IDC_DTP_EFF_DATE, true );

   AddControl( CTRL_COMBO, IDC_CMB_TRANS_TYPE, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
               ifds::TransType, /*CTRLFLAG_MANUAL_INIT*/CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TO );
   ConnectControl( IDC_CMB_TRANS_TYPE, true );
   EnableControl( IDC_CMB_TRANS_TYPE, true );

   AddControl( CTRL_EDIT, IDC_EDT_TO_FUND, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::FundToCode, CTRLFLAG_DEFAULT, IDC_LV_TO );
   ConnectControl( IDC_EDT_TO_FUND, true );
   EnableControl( IDC_EDT_TO_FUND, true );

   AddControl( CTRL_EDIT, IDC_EDT_TO_CLASS, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::ClassToCode, CTRLFLAG_DEFAULT, IDC_LV_TO );
   ConnectControl( IDC_EDT_TO_CLASS, true );
   EnableControl( IDC_EDT_TO_CLASS, true );

   AddControl( CTRL_COMBO, IDC_CMB_TO_CURRENCY, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::Currency, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TO );
   ConnectControl( IDC_CMB_TO_CURRENCY, true );
   EnableControl( IDC_CMB_TO_CURRENCY, true );

   AddControl( CTRL_EDIT, IDC_EDT_PERCENTAGE, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::AllocPercent, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_TO );
   ConnectControl( IDC_EDT_PERCENTAGE, true );
   EnableControl( IDC_EDT_PERCENTAGE, true );

   DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::AllocPercent );
   int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );
   DSTEdit *edtPercent = dynamic_cast< DSTEdit * >(
                                                   GetDlgItem( IDC_EDT_PERCENTAGE ) );
   edtPercent->SetMaxCharNum( dstrPercentageMask.length() );//probably redundant
   edtPercent->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
                                             dstrPercentageMask.length() - iDecimalPointPos - 1 );

   AddControl( CTRL_STATIC, IDC_TXT_TOTAL_PERCENTAGE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD );
   ConnectControl( IDC_TXT_TOTAL_PERCENTAGE, true );

   AddControl( CTRL_COMBO, IDC_CMB_PAYMENT_TYPE, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::DistributionPayType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TO );
   ConnectControl( IDC_CMB_PAYMENT_TYPE, true );
   EnableControl( IDC_CMB_PAYMENT_TYPE, true );

   AddControl( CTRL_COMBO, IDC_CMB_PAYMETHOD, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::PayMethod, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TO );
   ConnectControl( IDC_CMB_PAYMETHOD, true );
   EnableControl( IDC_CMB_PAYMETHOD, true );

   AddControl( CTRL_COMBO, IDC_CMB_ACHPROCESSOR, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::ACHProcessor, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TO );
   ConnectControl( IDC_CMB_ACHPROCESSOR, true );
   EnableControl( IDC_CMB_ACHPROCESSOR, true );

   AddControl( CTRL_EDIT, IDC_EDT_BANK_NAME_VAL, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::InstName, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_TO );
   ConnectControl( IDC_EDT_BANK_NAME_VAL, true );
   EnableControl( IDC_EDT_BANK_NAME_VAL, true );

   AddControl( CTRL_EDIT, IDC_EDT_TRANS_NUM_VAL, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::TransitNo,  CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_TO );
   ConnectControl( IDC_EDT_TRANS_NUM_VAL, true );
   EnableControl( IDC_EDT_TRANS_NUM_VAL, true );

   AddControl( CTRL_EDIT, IDC_EDT_INST_CODE_VAL, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::BankIdValue,  CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_TO );
   ConnectControl( IDC_EDT_INST_CODE_VAL, true );
   EnableControl( IDC_EDT_INST_CODE_VAL, true );

   AddControl( CTRL_EDIT, IDC_EDT_BANK_ACCT_NUM_VAL, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::BankAcctNum,  CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_TO );
   ConnectControl( IDC_EDT_BANK_ACCT_NUM_VAL, true );
   EnableControl( IDC_EDT_BANK_ACCT_NUM_VAL, true );

   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS, IFASTBP_PROC::ACCOUNT_MAILING_LIST, 
               ifds::DivChqAddr, CTRLFLAG_NOT_UPDATABLE, IDC_LV_TO );
   ConnectControl( IDC_EDT_ADDRESS, true );
   EnableControl( IDC_EDT_ADDRESS, true );

   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS_CODE, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
               ifds::AddrCode, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_TO );
   ConnectControl( IDC_EDT_ADDRESS_CODE, true );
   EnableControl( IDC_EDT_ADDRESS_CODE, true );

   DSTEdit *pEdtAddress 
      = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_ADDRESS ) );
   pEdtAddress->SetMaxCharNum( 70 );

   AddControl(CTRL_CHECKBOX, IDC_CHECK_ACCOUNT_LEVEL, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
               ifds::AllFundsDistrib, CTRLFLAG_DEFAULT, (UINT)IDC_LV_FROM);
   ShowControl( IDC_CHECK_ACCOUNT_LEVEL, false );
   // account level distrib options
   AddControl( CTRL_COMBO,  IDC_CMB_DISTRIB_DFLT_OPTION, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
            ifds::AcctDistribOpt, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_FROM);   
   ShowControl( IDC_CMB_DISTRIB_DFLT_OPTION, false );   
   AddControl( CTRL_COMBO,  IDC_CMB_DISTRIB_CURRENCY_OPTION, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
            ifds::AcctDistribCurrencyOption, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_FROM);
   ShowControl( IDC_CMB_DISTRIB_CURRENCY_OPTION, false );
   GetDlgItem( IDC_STC_DISTRIB_DFLT_OPTION )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_STC_DISTRIB_CURRENCY_OPTION )->ShowWindow( SW_HIDE );

   AddControl( CTRL_COMBO, 
               IDC_CMB_VERIFY_STAT, 
               IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
               ifds::VerifyStat, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               IDC_LV_FROM );

   GetDlgItem (IDC_STATIC_VERIFY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_VERIFY_STAT)->ShowWindow (SW_SHOW);

   if ( bVerificationEnabled )
   {
      GetDlgItem( IDC_CMB_VERIFY_STAT )->EnableWindow( TRUE );
   }
   else
   {
      GetDlgItem( IDC_CMB_VERIFY_STAT )->EnableWindow( FALSE );
   }

   /*GetDlgItem( IDC_BTN_BANK )->EnableWindow( hasPermission( 
     UAF::BANKING_INSTRUCTION, DBR::InqPerm ) );*/

   // Distribution Rate Controls	
   GetDlgItem( IDC_STC_INPUT_METHOD )->ShowWindow( SW_HIDE );

   GetDlgItem( IDC_STC_RECENT_DISTRIBUTION )->ShowWindow( SW_HIDE );
   AddControl( CTRL_STATIC, IDC_TXT_RECENT_DISTRIBUTION, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::LastIDRate, CTRLFLAG_DEFAULT, IDC_LV_FROM );    
   ConnectControl( IDC_TXT_RECENT_DISTRIBUTION, true );
   GetDlgItem( IDC_TXT_RECENT_DISTRIBUTION )->ShowWindow( SW_HIDE );

   GetDlgItem( IDC_STC_DISTRIB_RATE )->ShowWindow( SW_HIDE );
   AddControl( CTRL_EDIT, IDC_EDT_DISTRIB_RATE, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
	   ifds::DistribRate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_TO );
   ConnectControl( IDC_EDT_DISTRIB_RATE, true );
   EnableControl( IDC_EDT_DISTRIB_RATE, true );

   DString dstrDistribRateMask = DSTCommonFunctions::getMask( ifds::DistribRate );
   int iDecimalPointRatePos = dstrDistribRateMask.find( I_( "." ) );
   DSTEdit *edtDRate = dynamic_cast< DSTEdit * >(
	   GetDlgItem( IDC_EDT_DISTRIB_RATE ) );
   edtDRate->SetMaxCharNum( dstrDistribRateMask.length() );
   edtDRate->AllowNonnegativeDecimalNumbers( iDecimalPointRatePos, 
	   dstrDistribRateMask.length() - iDecimalPointRatePos - 1 );

   AddControl( CTRL_STATIC, IDC_TXT_TOTAL_DISTRIB_RATE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD );
   ConnectControl( IDC_TXT_TOTAL_DISTRIB_RATE, true );
   GetDlgItem( IDC_TXT_TOTAL_DISTRIB_RATE )->ShowWindow( SW_HIDE );	
   //

   if( !m_hAccel )
   {
      m_hAccel = LoadAccelerators( NULL, 
                                    MAKEINTRESOURCE( IDR_ACCEL_DISTRIBUTIONS ) );
   }

   dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_INST_CODE_VAL ) )->SetReadOnly();
   dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_TRANS_NUM_VAL ) )->SetReadOnly();
   dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_BANK_ACCT_NUM_VAL ) )->SetReadOnly();
   dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_BANK_NAME_VAL ) )->SetReadOnly();

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void AccDistributionDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog"));

   CWaitCursor wait;
   SetUserAccesFunctionCode(UAF::DISTRIBUTION);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_FROM, IDC_LV_FROM);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_TO, IDC_LV_TO);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_FROM, IDC_LV_FROM);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_TO,IDC_LV_TO );

   doRefresh(NULL, NULL);  
   
   GetDlgItem (IDC_BTN_MORE_FROM)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST));
   GetDlgItem (IDC_BTN_MORE_TO)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST));

   DSTListCtrl *rpList = GetList( IDC_LV_FROM );	

   bool bIsDummy = getParentProcess()->isCurrentListItemDummy( this, rpList->getContainerId() );
   
   if (m_dstrCaller == I_("FromAWD") && !bIsDummy && hasCreatePermission( UAF::DISTRIBUTION ))
	   PostMessage (WM_COMMAND, IDC_BTN_ADD_FROM);

   showHideDistribRateControls ();

}

//******************************************************************************

bool AccDistributionDlg::GetDataForControl( UINT controlID, 
                                            DString &dstrValueOut, bool bFormatted, int iIndex ) const
{
   bool bRet = false;
   switch( controlID )
   {
//	   case IDC_CMB_TRANS_TYPE:
//		   dstrValueOut = I_("ID");
//		   break;
      case IDC_TXT_TOTAL_PERCENTAGE:
         CalcTotalPercent( dstrValueOut );
         break;
      case IDC_EDT_ADDRESS:
         GetMailingAddress(dstrValueOut);
         break;
      case IDC_EDT_ADDRESS_CODE:

         GetDivChqAddrCode(dstrValueOut);

//         getParent()->getField ( this, ACC_DISTRIBUTION_SUB_LIST, ifds::AddrCode, dstrValueOut, false );
         break;
	  case IDC_TXT_RECENT_DISTRIBUTION:
		  getLastIDRate( dstrValueOut );			 
		  break;
	  case IDC_TXT_TOTAL_DISTRIB_RATE:
		  CalcTotalDistribRate( dstrValueOut );		
		  break;
      default:
         return(false);
   }
   return(true);
}

//******************************************************************************

void AccDistributionDlg::ControlUpdated( UINT ControlID, 
                                         const DString &dstrValue )
{
   DString dstrtmpValue;
   DString dstr;
   DString dstrACHDivident = NO;
   DString strMarket = DSTCommonFunctions::getMarket();

   switch( ControlID )
   {
/* case IDC_EDT_FROM_FUND_NUM:  // Added for C2 -- xyz 10/07/00
    LoadControl( IDC_EDT_FROM_FUND );
    LoadControl( IDC_EDT_FROM_CLASS );
      break;

  case IDC_EDT_FROM_FUND:	
      LoadControl( IDC_EDT_FROM_FUND_NUM );
    break;

   case IDC_EDT_FROM_CLASS:
      LoadControl( IDC_EDT_FROM_FUND_NUM );
      break;
*/
      case IDC_EDT_TO_FUND:
   {  dstrtmpValue = DString (dstrValue);
         dstrtmpValue.strip().upperCase();
         if( dstrtmpValue == CASH )//To Cash
         {
            DString strMarket = DSTCommonFunctions::getMarket();
            if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
            {
               //SetDlgItemText( IDC_EDT_TO_FUND_NUM, I_("N/A") );
            }
            //SetDlgItemText( IDC_TXT_CLASS_CURRENCY, CURRENCY_CAPTION );

            DString strAcctDistribCurrencyOption;
            getParent()->getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST,
               ifds::AcctDistribCurrencyOption, strAcctDistribCurrencyOption, false );

            if( strAcctDistribCurrencyOption.strip() == PREFERRED_CURRECNY )
            {
               CString strCurrencyCaption;
               strCurrencyCaption.LoadString( TXT_DISTRIBUTION_SETTLE_CURRENCY );
               SetDlgItemText( IDC_TXT_CLASS_CURRENCY, strCurrencyCaption );
            }
            else
            {
               CString strCurrencyCaption;
               strCurrencyCaption.LoadString( TXT_DISTRIBUTION_CURRENCY );
               SetDlgItemText( IDC_TXT_CLASS_CURRENCY, strCurrencyCaption );
            }

            ShowControl( IDC_EDT_TO_CLASS, false );
            ConnectControlToData( IDC_EDT_TO_CLASS, false );
            ShowControl( IDC_CMB_TO_CURRENCY, true );
            ConnectControlToData( IDC_CMB_TO_CURRENCY, true );
            LoadControl( IDC_CMB_TO_CURRENCY );

            GetDlgItem( IDC_TXT_PAYMENT_TYPE )->ShowWindow( SW_SHOW );
            ClearControl ( IDC_CMB_PAYMENT_TYPE );
            ReInitControl ( IDC_CMB_PAYMENT_TYPE, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::DistributionPayType );
            ShowControl( IDC_CMB_PAYMENT_TYPE, true );
            ConnectControlToData( IDC_CMB_PAYMENT_TYPE, true );
            LoadControl( IDC_CMB_PAYMENT_TYPE );

            getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                   ifds::DistributionPayType, dstr, false );
            dstr.strip().upperCase();
            AdjustControlsToPaymentType( dstr );

            LoadControl( IDC_CMB_TO_CURRENCY );
            GetDlgItem (IDC_CMB_TO_CURRENCY)->SetFocus();
         }
         else//To Fund
         {

            //SetDlgItemText( IDC_TXT_CLASS_CURRENCY, CLASS_CAPTION );

            CString strClassCaption;
            strClassCaption.LoadString( TXT_DISTRIBUTION_CLASS );
            SetDlgItemText( IDC_TXT_CLASS_CURRENCY, strClassCaption );

            ShowControl( IDC_CMB_TO_CURRENCY, false );
            ConnectControlToData( IDC_CMB_TO_CURRENCY, false );     
            ShowControl( IDC_EDT_TO_CLASS, true );
            ConnectControlToData( IDC_EDT_TO_CLASS, true );
            LoadControl( IDC_EDT_TO_CLASS );

            GetDlgItem( IDC_TXT_PAYMENT_TYPE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_PAYMENT_TYPE, false );
            ConnectControlToData( IDC_CMB_PAYMENT_TYPE, false );

            GetDlgItem( IDC_TXT_PAYMETHOD )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_PAYMETHOD, false );
            ConnectControlToData( IDC_CMB_PAYMETHOD, false );

            GetDlgItem( IDC_TXT_ACHPROCESSOR )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_ACHPROCESSOR, false );
            ConnectControlToData( IDC_CMB_ACHPROCESSOR, false );

            GetDlgItem( IDC_GRP_DESTINATION )->ShowWindow( SW_HIDE );


            GetDlgItem( IDC_BTN_ADDRESS )->ShowWindow( SW_HIDE );
            GetDlgItem(IDC_BTN_ADDRESS)->EnableWindow(SW_HIDE);
            GetDlgItem( IDC_LBL_ADDR_CODE )->ShowWindow ( SW_HIDE );
            ShowControl( IDC_EDT_ADDRESS, false );

            ShowBankRelated( false );
//         LoadControl( IDC_EDT_TO_FUND_NUM );
         }
   }
         break;
/*
   case IDC_EDT_TO_FUND_NUM:
      LoadControl( IDC_EDT_TO_FUND );
    LoadControl( IDC_EDT_TO_CLASS );
      break;
   
   case IDC_EDT_TO_CLASS:
      LoadControl( IDC_EDT_TO_FUND_NUM );
      break;
*/
      case IDC_CMB_PAYMENT_TYPE:
      {
         AdjustControlsToPaymentType( dstrValue );
         LoadControl( IDC_CMB_TO_CURRENCY );

         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(  ifds::ACHDividend , dstrACHDivident, BF::HOST, false );
         if(dstrValue == EFT_TO_ACCOUNT && dstrACHDivident == YES)
         {
            GetDlgItem( IDC_TXT_PAYMETHOD )->ShowWindow( SW_SHOW );
            ClearControl ( IDC_CMB_PAYMETHOD );
            ReInitControl ( IDC_CMB_PAYMETHOD, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::PayMethod );
            ShowControl( IDC_CMB_PAYMETHOD, true );
            ConnectControlToData( IDC_CMB_PAYMETHOD, true );
            LoadControl( IDC_CMB_PAYMETHOD );

            GetDlgItem( IDC_TXT_ACHPROCESSOR )->ShowWindow( SW_SHOW );
            ClearControl ( IDC_CMB_ACHPROCESSOR );
            ReInitControl ( IDC_CMB_ACHPROCESSOR, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::ACHProcessor );
            ShowControl( IDC_CMB_ACHPROCESSOR, true );
            ConnectControlToData( IDC_CMB_ACHPROCESSOR, true );
            LoadControl( IDC_CMB_ACHPROCESSOR );
         }
         else
         {
            GetDlgItem( IDC_TXT_PAYMETHOD )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_PAYMETHOD, false );
            ConnectControlToData( IDC_CMB_PAYMETHOD, false );

            GetDlgItem( IDC_TXT_ACHPROCESSOR )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_ACHPROCESSOR, false );
            ConnectControlToData( IDC_CMB_ACHPROCESSOR, false );
         }
      }
         break;
      case IDC_CMB_PAYMETHOD:
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                               ifds::DistributionPayType, dstr, false );
         dstr.strip().upperCase();
         AdjustControlsToPaymentType( dstr );
      }
         break;
      case IDC_EDT_PERCENTAGE:
      {
         LoadControl( IDC_TXT_TOTAL_PERCENTAGE );
      }
         break;
      case IDC_CMB_TRANS_TYPE:
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                                 ifds::TransType, dstr, false );
         if((dstr.strip() == I_( "ID" ) || dstr.strip() == I_( "MR" )) && strMarket == MARKET_IDS::LUXEMBOURG )
         {
            ShowControl( IDC_CHECK_ACCOUNT_LEVEL, true );
         }
         else
         {
            ShowControl( IDC_CHECK_ACCOUNT_LEVEL, false );
         }

         if( GetDlgItem( IDC_CHECK_ACCOUNT_LEVEL ) != NULL )
         {
            DSTButton* fullTrsfCheck = 
               dynamic_cast<DSTButton*>(GetControl(IDC_CHECK_ACCOUNT_LEVEL));
            if (fullTrsfCheck != NULL)
            {
               bool bCheck = fullTrsfCheck->GetCheck() == 1;
               if( bCheck )
               {
                  ShowControl( IDC_CMB_DISTRIB_DFLT_OPTION, true );   
                  ShowControl( IDC_CMB_DISTRIB_CURRENCY_OPTION, true );
                  GetDlgItem( IDC_STC_DISTRIB_DFLT_OPTION )->ShowWindow( SW_SHOW );
                  GetDlgItem( IDC_STC_DISTRIB_CURRENCY_OPTION )->ShowWindow( SW_SHOW );

               }
               else
               {
                  ShowControl( IDC_CMB_DISTRIB_DFLT_OPTION, false );   
                  ShowControl( IDC_CMB_DISTRIB_CURRENCY_OPTION, false );
                  GetDlgItem( IDC_STC_DISTRIB_DFLT_OPTION )->ShowWindow( SW_HIDE );
                  GetDlgItem( IDC_STC_DISTRIB_CURRENCY_OPTION )->ShowWindow( SW_HIDE );

               }
            }
         }

		 DString dstrDistribRateOpt;	
		 dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(  ifds::DistribInstrAsRatioOpt , dstrDistribRateOpt, BF::HOST, false );	
		 bool bShow = ((dstr.strip() == I_( "ID" )) && (dstrDistribRateOpt == YES)) ? true : false;
		 if (bShow) {
			 switchInputMethod(false);
		 } else {
			 hideDistribRateControls();
		 }
      }
         break;
      case IDC_CMB_DISTRIB_CURRENCY_OPTION:
      {
         DString strAcctDistribCurrencyOption;
         getParent()->getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST,
            ifds::AcctDistribCurrencyOption, strAcctDistribCurrencyOption, false );

         if( strAcctDistribCurrencyOption.strip() == FUND_CURRENCY )
         {
            //disable Bank button
            GetDlgItem( IDC_BTN_BANK )->EnableWindow( FALSE );
            //change the Currency description to 'Currency'
            CString strCurrencyCaption;
            strCurrencyCaption.LoadString( TXT_DISTRIBUTION_CURRENCY );
            SetDlgItemText( IDC_TXT_CLASS_CURRENCY, strCurrencyCaption );
         }
         else if( strAcctDistribCurrencyOption.strip() == PREFERRED_CURRECNY )
         {
            DString strPayType;
            getParent()->getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST,
               ifds::DistributionPayType, strPayType, false );
            if( strPayType.strip().upperCase() == EFT )
            {
               //enable Bank button
               GetDlgItem( IDC_BTN_BANK )->EnableWindow( TRUE );
            }
            //change the Currency description to 'Settle Currency'
            CString strCurrencyCaption;
            strCurrencyCaption.LoadString( TXT_DISTRIBUTION_SETTLE_CURRENCY );
            SetDlgItemText( IDC_TXT_CLASS_CURRENCY, strCurrencyCaption );
         }
         else
         {
               /*must be blank; change the description to Class
               CString strClassCaption;
                  strClassCaption.LoadString( TXT_DISTRIBUTION_CLASS );
                  SetDlgItemText( IDC_TXT_CLASS_CURRENCY, strClassCaption );*/
         }
      }
         break;
      case IDC_CHECK_ACCOUNT_LEVEL:
      {
        DSTButton *ftCheck = dynamic_cast<DSTButton*>(GetControl(ControlID));
        if (ftCheck != NULL)
         {
           ftCheck->SetCheck(dstrValue == I_("Y"));
         }
      }
         break;
      case IDC_CMB_DISTRIB_DFLT_OPTION:
      {
         DString strAcctDistribOption;
         getParent()->getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST,
            ifds::AcctDistribOpt, strAcctDistribOption, false );
         if( strAcctDistribOption.strip() == REINVEST )
         {
            ShowControl( IDC_EDT_PERCENTAGE, false );  
            GetDlgItem( IDC_STC_PERCENTAGE )->ShowWindow( false );
            GetDlgItem( IDC_STC_TOTAL_PERCENTAGE )->ShowWindow( false );
            GetDlgItem( IDC_TXT_TOTAL_PERCENTAGE )->ShowWindow( false );
         }
         else
         {
            ShowControl( IDC_EDT_PERCENTAGE, true );   
            GetDlgItem( IDC_STC_PERCENTAGE )->ShowWindow( true );
            GetDlgItem( IDC_STC_TOTAL_PERCENTAGE )->ShowWindow( true );
            GetDlgItem( IDC_TXT_TOTAL_PERCENTAGE )->ShowWindow( true );
         }
         LoadListControl(IDC_LV_TO);
      }
         break;
	  case IDC_EDT_DISTRIB_RATE:
		  {
			  LoadControl( IDC_TXT_TOTAL_DISTRIB_RATE );
		  }
		  break;	
	  case IDC_EDT_FROM_CLASS:  
		  {
			  LoadControl( IDC_TXT_RECENT_DISTRIBUTION );
		  }
		  break;
	  case IDC_TXT_TOTAL_DISTRIB_RATE:  
		  {
			  RefreshListItem( IDC_LV_TO );
			  GetList(IDC_LV_TO)->RefreshAllItems();
		  }
		  break;
   }
}

//******************************************************************************

void AccDistributionDlg::AdjustControlsToPaymentType(
                                                    const DString &dstrPaymentType ) 
{
   DString dstrPayMethod;
   getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                      ifds::PayMethod, dstrPayMethod, false );
    dstrPayMethod.strip().upperCase();

   if ( (dstrPaymentType == EFT_TO_ACCOUNT && dstrPayMethod != CHQ) ||
	   (dstrPaymentType == INTERNATIONAL_WIRE && ( dstrPayMethod == WIRE || dstrPayMethod == NULL_STRING ))) 
   {
      GetDlgItem( IDC_GRP_DESTINATION )->ShowWindow( SW_SHOW );

      GetDlgItem( IDC_BTN_ADDRESS )->ShowWindow( SW_HIDE );
      GetDlgItem(IDC_BTN_ADDRESS)->EnableWindow(SW_HIDE);
      GetDlgItem( IDC_LBL_ADDR_CODE )->ShowWindow ( SW_HIDE );
      GetDlgItem( IDC_EDT_ADDRESS_CODE )->ShowWindow ( SW_HIDE );
      ShowControl( IDC_EDT_ADDRESS, false );      
      ShowBankRelated( true );
      LoadControl( IDC_EDT_BANK_NAME_VAL );
      LoadControl( IDC_EDT_TRANS_NUM_VAL );
      LoadControl( IDC_EDT_INST_CODE_VAL );
      LoadControl( IDC_EDT_BANK_ACCT_NUM_VAL );  
     /*dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_INST_CODE_VAL ) )->SetReadOnly();
      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_TRANS_NUM_VAL ) )->SetReadOnly();
      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_BANK_ACCT_NUM_VAL ) )->SetReadOnly();
      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_BANK_NAME_VAL ) )->SetReadOnly();*/

   }
   else if( dstrPaymentType == SYSTEM_GENERATED_CHEQUE || (dstrPaymentType == EFT_TO_ACCOUNT && (dstrPayMethod  != WIRE || dstrPayMethod != I_("EFT"))) )
   {
      GetDlgItem( IDC_GRP_DESTINATION )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_BTN_ADDRESS )->ShowWindow( SW_SHOW );
      GetDlgItem(IDC_BTN_ADDRESS)->EnableWindow(SW_HIDE);
      GetDlgItem( IDC_LBL_ADDR_CODE )->ShowWindow ( SW_SHOW );
      DString dstrTransType;
      getParent()->getField ( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST ,ifds::TransType, dstrTransType, false );
      EnableControl ( IDC_EDT_ADDRESS_CODE, dstrTransType == I_("MR") );
      GetDlgItem( IDC_EDT_ADDRESS_CODE )->ShowWindow ( SW_SHOW );

      LoadControl( IDC_EDT_ADDRESS_CODE );
      ShowControl( IDC_EDT_ADDRESS, true );
      ShowBankRelated( false );
      LoadControl( IDC_EDT_ADDRESS );
   }
   else
   {
      GetDlgItem( IDC_GRP_DESTINATION )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_BTN_ADDRESS )->ShowWindow( SW_HIDE );
      GetDlgItem(IDC_BTN_ADDRESS)->EnableWindow(SW_HIDE);
      GetDlgItem( IDC_EDT_ADDRESS_CODE )->ShowWindow ( SW_HIDE );
      GetDlgItem( IDC_LBL_ADDR_CODE )->ShowWindow ( SW_HIDE );     
      ShowControl( IDC_EDT_ADDRESS, false );
      ShowBankRelated( false );
   }
}

//******************************************************************************

void AccDistributionDlg::CalcTotalPercent( DString &dstrOutTotalPercent ) const
{
   if( !getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ) )
   {
      dstrOutTotalPercent = NULL_STRING;
      return;
   }

   DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();

   bool bVerificationEnabled = false;
   pWorkSession->isVerificationEnabled ( idDataGroup, 
                                         DISTRIB_CATEGORY, 
                                         DISTRIB_LEVEL, 
                                         bVerificationEnabled );

   // 1. remember the current positions in the list, to restore it later
   const DString *pCurrKey = &( getParent()->getCurrentListItemKey( this, 
                                                                    IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ) );
   // 2. calculate total percent
   const DString *pKey = &( getParent()->getFirstListItemKey( this, 
                                                              IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ) );
   double dTotalPercent = 0;
   if( *pKey != NULL_STRING )
   {
      DString dstr,dstrGoodBad;
      do
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                ifds::AllocPercent, dstr );
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                ifds::DistribGBCD, dstrGoodBad, false );
         dstrGoodBad.strip().upperCase();
         dstr.strip().stripAll( I_CHAR( ',' ) );
         I_CHAR *stopstring;

         // if system has verification enable only sum with good record
         // otherwise sum all records
         if ( bVerificationEnabled )
         {
            if ( dstrGoodBad != I_("N") )
            {
               dTotalPercent += wcstod( dstr.c_str(), &stopstring );
            }
            else
            {
               continue;
            }
         }
         else
         {
            dTotalPercent += wcstod( dstr.c_str(), &stopstring );
         }
      }
      while( *( pKey = &( getParent()->getNextListItemKey( this, 
                                                           IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ) ) ) != NULL_STRING );
   }
   // 3. restore the initial iterator position in the list
   getParent()->setCurrentListItem( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                    *pCurrKey );
   // 4. format string
   DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::AllocPercent );
   dstrPercentageMask.strip();
   int iMaskNumDigitsAfterDecimalPoint = dstrPercentageMask.length() 
                                         - dstrPercentageMask.find( I_( "." ) ) - 1;
   double dFactor = pow( 10, iMaskNumDigitsAfterDecimalPoint );
   //rounding dTotalPercent:
   assert( dTotalPercent >= 0 );
   dTotalPercent *= dFactor;
   dTotalPercent += .5;
   dTotalPercent = floor( dTotalPercent );
   dTotalPercent /= dFactor;

   char buffer[ 50 ];
   dstrOutTotalPercent = DStringA( _gcvt( dTotalPercent, 30, buffer ) );
   int iCurrNumDigitsAfterDecimalPoint = dstrOutTotalPercent.length() 
                                         - dstrOutTotalPercent.find( I_( "." ) ) - 1;
   int NumOfZerosToPad = iMaskNumDigitsAfterDecimalPoint 
                         - iCurrNumDigitsAfterDecimalPoint;
   if( NumOfZerosToPad > 0 )
      dstrOutTotalPercent.padRight( dstrOutTotalPercent.length() 
                                    + NumOfZerosToPad, I_CHAR( '0' ) );
   else if( NumOfZerosToPad < 0 )
      dstrOutTotalPercent = dstrOutTotalPercent.left(
                                                    dstrOutTotalPercent.length() + NumOfZerosToPad );   

   dstrOutTotalPercent += I_CHAR( '%' ); 

   DString dstrTotalAllocPercent = DSTCommonFunctions::doubleToDString( ifds::TotalAllocPercent, dTotalPercent );	
   getParent()->setField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::TotalAllocPercent, dstrTotalAllocPercent, false );	

}

//******************************************************************************

void AccDistributionDlg::OnBtnBank() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBank" ) );

   CWaitCursor wait;

   try
   {
      SetMessageStatusBar( TXT_LOAD_BANKING );

      DString dstrAccountNum;

      getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, 
         ifds::AccountNum, dstrAccountNum );
      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );

      const DString *pAcctKey = &(getParent()->getCurrentListItemKey( this, 
         IFASTBP_PROC::ACC_DISTRIBUTION_LIST));
      const DString *pFundClassKey = &(getParent()->getCurrentListItemKey( this,
         IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST));

#ifdef _DEBUG
      const DString &dstrAcctKeyDEBUG = GetList( IDC_LV_FROM )->GetCurrentKey();
      const DString &dstrFundClassKeyDEBUG = GetList( IDC_LV_TO )->GetCurrentKey();
      assert( *pAcctKey == dstrAcctKeyDEBUG &&
              *pFundClassKey == dstrFundClassKeyDEBUG );
#endif

      DString strVerifyStat, strDistribGBCD;

      getParent()->getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST,
                            ifds::VerifyStat, strVerifyStat, false );
      getParent()->getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST,
                            ifds::DistribGBCD, strDistribGBCD, false );

      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);
      setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::DISTRIBUTION);
      setParameter(MFCAN_IP_PARAM::LIST_KEY, *pAcctKey);
      setParameter(MFCAN_IP_PARAM::SUB_LIST_KEY, *pFundClassKey);

      setParameter(MFCAN_IP_PARAM::DISTRIB_GBCD, strDistribGBCD);
      setParameter(MFCAN_IP_PARAM::VERIFY_STAT, strVerifyStat);

      E_COMMANDRETURN eRtn = getParentProcess()->invokeProcessFromChild(this, 
         CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT);

      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            LoadControl( IDC_EDT_BANK_NAME_VAL );
            LoadControl( IDC_EDT_TRANS_NUM_VAL );
            LoadControl( IDC_EDT_INST_CODE_VAL );
            LoadControl( IDC_EDT_BANK_ACCT_NUM_VAL );
            LoadControl( IDC_CMB_TO_CURRENCY );

            RefreshListItem( IDC_LV_TO );

            {
               DString dstrPayType;
               getParent()->getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                  ifds::DistributionPayType, dstrPayType, false);
               dstrPayType.strip().upperCase();
               AdjustControlsToPaymentType(dstrPayType);
            }
            break;
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
      SetMessageStatusBar( NULL_STRING );
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

//******************************************************************************

bool AccDistributionDlg::doRefresh( GenericInterface *rpGICaller,
                                    const I_CHAR * szOriginalCommand)
{  
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetMessageStatusBar( TXT_LOAD_DISTRIBUTION );

   // display caption
   DString ShrNum, AcctNum, EntityName;
   getParent()->getField( this, SHAREHOLDER_NUMBER, ShrNum );
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, AcctNum ); 
   getParent()->getField( this, PRIMARY_ACCOUNT_OWNER, EntityName );


   SetShrAcctCaption(ShrNum, AcctNum, EntityName);

   ConnectControlsToData();

   DString selectionKey;
   getParent()->getField( this, LISTKEY, selectionKey );

   DString strVerifyCategoryList;
   DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   pWorkSession->getVerificationCategoryList(strVerifyCategoryList);

   LoadListControl( IDC_LV_FROM, &selectionKey );
   LoadListControl( IDC_LV_TO );
   LoadControls();

   if( !selectionKey.empty() )
   {
      getParent()->getField( this, TO_LISTKEY, selectionKey );
      GetList( IDC_LV_TO )->SetSelection( &selectionKey );
      selectionKey = NULL_STRING; // one time use
   }

   SetMessageStatusBar( NULL_STRING );
   GetDlgItem ( IDC_CMB_TRANS_TYPE )->SetFocus();
   return(true);
}

//******************************************************************************

void AccDistributionDlg::OnBtnAddFrom() 
{ 
   AddToListControl( IDC_LV_FROM );
   GetDlgItem ( IDC_CMB_TRANS_TYPE )->SetFocus();
}

//******************************************************************************

void AccDistributionDlg::OnBtnDeleteFrom() 
{
   DeleteFromListControl( IDC_LV_FROM );
   GetDlgItem ( IDC_CMB_TRANS_TYPE )->SetFocus();   
}

//******************************************************************************

void AccDistributionDlg::OnBtnMoreFrom()
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMoreFrom" ) );
    CWaitCursor wait;

    SetMessageStatusBar(TXT_LOAD_DISTRIBUTION_OPTIONS_INFORMATION);

    static int cursel = GetList (IDC_LV_FROM)->GetNextItem (-1, LVIS_SELECTED | LVNI_FOCUSED);  
    const DString *crtKey = &getParent()->getCurrentListItemKey (this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST);
    if ( getParent()->performSearch (this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, SEARCH_NEXT_BLOCK) <= WARNING )
    {
        LoadListControl (IDC_LV_FROM);
        if (*crtKey != NULL_STRING)
        {
            GetList (IDC_LV_FROM)->SetSelection (crtKey);
        }
    }
    else
    {
        ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
    }

    GetDlgItem (IDC_BTN_MORE_FROM)->
            EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST));
    GetList( IDC_LV_FROM )->SetSelection(cursel, true, true);

    SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************

bool AccDistributionDlg::GetOverrideItemString( long lSubstituteId, 
                                                const DString &dstrColumnKey, DString &dstrOut )
{
   if( lSubstituteId == ifds::DistributionHeadingSet.getId() || 
       lSubstituteId == ifds::DistributionHeadingVerifySet.getId() )
   {
      if( dstrColumnKey == TRANS_TYPE )
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::TransType, 
                                dstrOut );
         dstrOut.strip();
/*			CString tmp;
      tmp.LoadString( TXT_DISTRIBUTION_INCOME_DIS );
      dstrOut = tmp.GetBuffer( 0 );//INCOME_DIS;
      tmp.ReleaseBuffer( -1 );*/
         return(true);
      }

      if( dstrColumnKey == FUND_CODE )
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::FundCode, 
                                dstrOut );
         dstrOut.strip().upperCase();
         return(true);
      }

      if( dstrColumnKey == CLASS_CODE )
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::ClassCode, 
                                dstrOut );
         dstrOut.strip().upperCase();
         return(true);
      }

      if( dstrColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::FundCode, dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::ClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();

         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, dstrOut );

         return(true);
      }

      if( dstrColumnKey == EFFECTIVE_DATE )
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::EffectiveDate, 
                                dstrOut );
         dstrOut.strip();
         return(true);
      }

      if( dstrColumnKey == I_("DistribGBCD") )
      {
         getParent()->getField( this, 
                                IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                                ifds::DistribGBCD, 
                                dstrOut,
                                false );
         dstrOut.strip().upperCase();
         
         if ( dstrOut == I_("Y"))
         {
            dstrOut = I_("Good");
         }
         else
         {
            dstrOut = I_("Bad");
         }
         return(true);
      }
   }
   //else if( lSubstituteId == ifds::DistributionToHeadingVerifySet.getId() )
   else if( lSubstituteId == ifds::DistributionHeadingSet1.getId() )
   {
      if( dstrColumnKey == CLASS_TO_CODE )
      {
         DString dstrFundToCode;
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                ifds::FundToCode, dstrFundToCode );
         dstrFundToCode.strip().upperCase();

         if( dstrFundToCode == CASH )
         {
            getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                   ifds::Currency, dstrOut );
            dstrOut.strip();
         }
         else
         {
            getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                   ifds::ClassToCode, dstrOut );
            dstrOut.stripAll().upperCase();
         }
         return(true);
      }

      if( dstrColumnKey == FUND_TO_CODE )
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                ifds::FundToCode, dstrOut );
         dstrOut.strip().upperCase();
         return(true);
      }

      if( dstrColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::FundToCode, dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::ClassToCode, dstrClassCode );
         dstrFundCode.strip().upperCase();         
         dstrClassCode.strip().upperCase();
         if( dstrFundCode == I_( "CASH" ) )
            dstrOut = I_( "N/A" );
         else
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, dstrOut );
         return(true);
      }

      if( dstrColumnKey == PERCENT )
      {
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                ifds::AllocPercent, dstrOut );
         dstrOut.strip();
         dstrOut += PERCENT_SIGN;
         return(true);
      }

      if( dstrColumnKey == PAY_TYPE )
      {
         DString dstrFundToCode;
         getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                ifds::FundToCode, dstrFundToCode );
         dstrFundToCode.strip().upperCase();

         if( dstrFundToCode == CASH )
         {
            getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                   ifds::DistributionPayType, dstrOut );
            dstrOut.strip();
         }
         else
            dstrOut = NULL_STRING;
         return(true);
      }
      
      //if( dstrColumnKey == I_("DistribGBCD") )
      //{
      //   getParent()->getField( this, 
      //                          IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
      //                          ifds::DistribGBCD, 
      //                          dstrOut,
      //                          false );
      //   dstrOut.strip().upperCase();
      //   
      //   if ( dstrOut == I_("Y"))
      //   {
      //      dstrOut = I_("Good");
      //   }
      //   else
      //   {
      //      dstrOut = I_("Bad");
      //   }
      //   return(true);
      //}
   }
   return(false);
}

//******************************************************************************

bool AccDistributionDlg::SetDataFromControl( UINT controlID, 
                                             const DString &dstrValue, bool bFormatted,
                                             SEVERITY &sevRtn, int iIndex )
{
   sevRtn = NO_CONDITION;
   switch( controlID )
   {
      case IDC_EDT_TO_FUND:
         {
            DString dstr( dstrValue );
            dstr.strip().upperCase();
            sevRtn = getParent()->setField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                            ifds::FundToCode, dstr, false );
            if( dstr == I_( "CASH" ) )
            {
               getParent()->setField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                      ifds::ClassToCode, I_( "A" ), false );
               getParent()->setField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
                                      ifds::ToFundNumber, I_( "N/A" ), false );
            }
            LoadControl ( IDC_EDT_TO_CLASS );
            DString strMarket = DSTCommonFunctions::getMarket();
            if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
            {
               LoadControl ( IDC_EDT_TO_FUND_NUM );
            }
            break;
         }
      case IDC_EDT_ADDRESS:
         if( dstrValue.empty() )
            sevRtn = SEVERE_ERROR;
         break;   
      default :
         return(false);
   }
   return(true);
}

//******************************************************************************

void AccDistributionDlg::OnBtnAddress() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAddress" ) );

   assert( hasReadPermission( UAF::ADDRESS_BOOK ) ); //, DBR::InqPerm ) );  // ??? why ???

   try
   {
      SetMessageStatusBar( TXT_BROWSE_ADDRESS_BOOK );
      CWaitCursor wait;
      DString dstrAccountNum;
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, 
                             dstrAccountNum );
      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
      setParameter( ACCOUNT_NUM, dstrAccountNum );

      E_COMMANDRETURN eRtn = getParentProcess()->invokeProcessFromChild( this, 
                                                                         CMD_BPROC_ADDRESSES, PROC_SUPPORT );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            LoadControl( IDC_EDT_ADDRESS );
            getParent()->setField ( this,IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ,ifds::TransTypeDesc, VALIDATE_ADDR_CODE, false );
            break;
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }

      SetMessageStatusBar( NULL_STRING );
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

//******************************************************************************

void AccDistributionDlg::OnBtnReset() 
{
   ResetListItem(IDC_LV_FROM );
   GetDlgItem ( IDC_CMB_TRANS_TYPE )->SetFocus();
}

//******************************************************************************

void AccDistributionDlg::OnBtnAddTo() 
{
   AddToListControl( IDC_LV_TO );
   GetList(IDC_LV_TO)->RefreshAllItems();
   GetList( IDC_LV_TO )->SetFocus();
}

//******************************************************************************

void AccDistributionDlg::OnBtnDeleteTo() 
{
   DeleteFromListControl( IDC_LV_TO );
   GetList(IDC_LV_TO)->RefreshAllItems();
   GetList( IDC_LV_TO )->SetFocus();
}

//******************************************************************************

void AccDistributionDlg::OnBtnMoreTo()
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMoreTo" ) );
    CWaitCursor wait;

    SetMessageStatusBar(TXT_LOAD_DISTRIBUTION_OPTIONS_INFORMATION);

    static int cursel = GetList (IDC_LV_TO)->GetNextItem (-1, LVIS_SELECTED | LVNI_FOCUSED);  
    const DString *crtKey = &getParent()->getCurrentListItemKey (this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST);
    if (getParent()->performSearch (this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, SEARCH_NEXT_BLOCK) <= WARNING)
    {
        LoadListControl (IDC_LV_TO);
        if (*crtKey != NULL_STRING)
        {
            GetList (IDC_LV_TO)->SetSelection (crtKey);
        }
    }
    else
    {
        ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
    }

    GetDlgItem (IDC_BTN_MORE_TO)->
            EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST));
    GetList( IDC_LV_TO )->SetSelection(cursel, true, true);

    SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************

void AccDistributionDlg::OnBtnAdmindate() 
{
    // move to current item of the list
    DString strKey = GetList( IDC_LV_FROM )->GetCurrentKey();
    if( !strKey.empty() )
    {
        getParent()->setCurrentListItem( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, strKey );

        ShowAdminDates( IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
    }
}

//******************************************************************************

BOOL AccDistributionDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   m_bEsc = false;
   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_ESCAPE )
   {
      m_bEsc = true;
   }
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      DString dstrTransType;
      getParent()->getField ( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST ,ifds::TransType, dstrTransType, false );
      setParameter ( FUNDCLASSLIST::MANAGEMENTFEE_REBATE, dstrTransType == I_("MR")?YES:NO);
      if( GetFocus() == GetDlgItem( IDC_EDT_TO_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_TO_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_TO_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG ); 
         m_uiDialogItem = IDC_EDT_TO_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_TO_FUND_NUM ) )
      {  // Added for C2 -- xyz 10/07/00     
         PostMessage( UM_OPENFUNDCLASSLISTDLG ); 
         m_uiDialogItem = IDC_EDT_TO_FUND_NUM;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FROM_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FROM_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiDialogItem = IDC_EDT_FROM_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND_NUM ) )
      { // Added for C2 -- xyz 10/07/00
         PostMessage( UM_OPENFUNDCLASSLISTDLG );  
         m_uiDialogItem = IDC_EDT_FROM_FUND_NUM;
      }
   }

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }

   if( !isTranslated )
   {
      // pass message down the chain
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }

   return(isTranslated);
}

//******************************************************************************

void AccDistributionDlg::OnAccelFrom() 
{
   GetList( IDC_LV_FROM )->SetFocus();
}

//******************************************************************************

void AccDistributionDlg::OnAccelTo() 
{
   GetList( IDC_LV_TO )->SetFocus();
}

//******************************************************************************

bool AccDistributionDlg::PreOk()
{
   return(true);
}

//******************************************************************************

void AccDistributionDlg::DoListItemChanged(
                                          UINT listControlID,
                                          const DString &strKey,
                                          bool bIsNewItem, 
                                          bool bIsDummyItem
                                          )
{
   bool bVerificationEnabled = false;
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
   DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   DString strVerifyStat,strDistribGBCD;

   pWorkSession->isVerificationEnabled ( idDataGroup, 
                                         DISTRIB_CATEGORY, 
                                         DISTRIB_LEVEL, 
                                         bVerificationEnabled);

   if( listControlID == IDC_LV_TO )
   {
      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_INST_CODE_VAL ) )->SetReadOnly();
      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_TRANS_NUM_VAL ) )->SetReadOnly();
      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_BANK_ACCT_NUM_VAL ) )->SetReadOnly();
      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_BANK_NAME_VAL ) )->SetReadOnly();

      if ( bVerificationEnabled )
      {
         getParent ()->getField( this, 
                                 IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                                 ifds::VerifyStat, 
                                 strVerifyStat, false );
         getParent ()->getField( this, 
                                 IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                                 ifds::DistribGBCD, 
                                 strDistribGBCD, false );

         strVerifyStat.strip().upperCase();
         strDistribGBCD.strip().upperCase();

         // all of control should be set readonly or not updatable, 
         // if record was deleted and waiting for verification
         if ( strVerifyStat == UNVERIFIED && strDistribGBCD == I_("N"))
         {
            GetDlgItem(IDC_BTN_DELETE_TO)->EnableWindow( 
               (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );
         }
      }

	  showHideDistribRateControls();
   }
   else if( listControlID == IDC_LV_FROM )
   {
      // Historical Button
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );

      if ( bVerificationEnabled )
      {
         getParent ()->getField( this, 
                                 IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                                 ifds::VerifyStat, 
                                 strVerifyStat, false );
         getParent ()->getField( this, 
                                 IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
                                 ifds::DistribGBCD, 
                                 strDistribGBCD, false );

         strVerifyStat.strip().upperCase();
         strDistribGBCD.strip().upperCase();

         // all of control should be set read only or not updatable, 
         // if record was deleted and waiting for verification
         if ( strVerifyStat == UNVERIFIED && strDistribGBCD == I_("N"))
         {
            GetDlgItem(IDC_BTN_DELETE_FROM)->EnableWindow( 
               (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );
         }
      }
		  
	  showHideDistribRateControls();
   }
}

//***********************************************************************
void AccDistributionDlg::GetDivChqAddrCode(DString& dstrAddrCode) const
{

   DString dstrAccountNum;
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, 
                          dstrAccountNum );
   dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );

   const DString *pKey = &( getParent()->getFirstListItemKey( this, 
         IFASTBP_PROC::ACCOUNT_MAILING_LIST ) );
   if( *pKey != NULL_STRING )
   {
      DString dstrTransType;
      getParent()->getField ( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::TransType, dstrTransType, false );
      if( dstrTransType != I_("MR") )
      {
         do
         {
            DString dstrCurrAccountNum;
            getParent()->getField( this, IFASTBP_PROC::ACCOUNT_MAILING_LIST, 
                                   ifds::AccountNum, dstrCurrAccountNum );
            dstrCurrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
            if( dstrCurrAccountNum == dstrAccountNum )
            {
               getParent()->getField( this, IFASTBP_PROC::ACCOUNT_MAILING_LIST, ifds::DivChqAddr, dstrAddrCode,false );
               break;
            }
         }
         while( *( pKey = &( getParent()->getNextListItemKey( this, 
                                                              IFASTBP_PROC::ACCOUNT_MAILING_LIST ) ) ) != NULL_STRING );
      }
      else
      {
         getParent()->getField ( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::AddrCode, dstrAddrCode, false );

      }
   }
   dstrAddrCode.strip();
}
//******************************************************************************

void AccDistributionDlg::GetMailingAddress(DString& strAddress) const
{

   DString dstrAddrCode;
   GetDivChqAddrCode( dstrAddrCode );  
   if( dstrAddrCode == NULL_STRING )//no mailing info found
      strAddress = NULL_STRING;
   else
   {
      const DString *pKey = &( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ADDRESS_LIST ) );
      const DString *pAddrKey = 0;
      if( *pKey != NULL_STRING )
      {
         DSTOleDateTime dtDate( 100, 1, 1, 0, 0, 0 );//the earliest 
         //supported date
         CString strDate;
         dtDate.DSTHostFormat( strDate );
         DString dstrEffectiveDate( strDate );
         DString dstrCurrAddrCode, dstrCurrEffectiveDate;
         do
         {
            getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode, 
                                   dstrCurrAddrCode, false );
            dstrCurrAddrCode.strip();
            if( dstrCurrAddrCode == dstrAddrCode )
            {
               getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, 
                                      ifds::EffectiveDate, dstrCurrEffectiveDate, false );
               dstrCurrEffectiveDate.strip();
               if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, 
                                                     dstrCurrEffectiveDate ) 
                   == DSTCommonFunctions::FIRST_EARLIER )
               {
                  dstrEffectiveDate = dstrCurrEffectiveDate;
                  pAddrKey = pKey;
               }
            }
         }
         while( *( pKey = &( getParent()->getNextListItemKey( this, 
                                                              IFASTBP_PROC::ADDRESS_LIST ) ) ) != NULL_STRING );
      }
      if( pAddrKey )
      {
         getParent()->setCurrentListItem( this, IFASTBP_PROC::ADDRESS_LIST, *pAddrKey );

         DString dstrAddr;
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine1, 
                                dstrAddr );
         strAddress = dstrAddr.strip();
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine2, 
                                dstrAddr );
         strAddress += I_( "\r\n" ) + dstrAddr.strip();
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine3, 
                                dstrAddr );
         strAddress += I_( "\r\n" ) + dstrAddr.strip();
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine4, 
                                dstrAddr );
         strAddress += I_( "\r\n" ) + dstrAddr.strip();
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine5, 
                                dstrAddr );
         strAddress += I_( "\r\n" ) + dstrAddr.strip();
         getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::PostalCode, 
                                dstrAddr );
         strAddress += I_( "\r\n" ) + dstrAddr.strip();
      }
   }
}

//******************************************************************************

LRESULT AccDistributionDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      DString dstrShareholder, dstrAcctNum;
      getParent()->getField( this, ifds::ShrNum, dstrShareholder );
      dstrShareholder.strip().stripLeading( I_CHAR( '0' ) );
      setParameter ( SHR_NUM , dstrShareholder );

      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAcctNum );
      dstrAcctNum.strip().stripLeading( I_CHAR( '0' ) );
      setParameter ( ACCT_NUM , dstrAcctNum );


      // Set Search Parameters for Fund Class Dialog
      switch( m_uiDialogItem )
      {
         case IDC_EDT_TO_FUND:
         case IDC_EDT_FROM_FUND:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUND_CODE, dstrFundCode );
               setParameter( CLASS_CODE, NULL_STRING );
               setParameter( FUNDNUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_TO_CLASS:
         case IDC_EDT_FROM_CLASS:
            {
               CString cstrFundClass;
               GetDlgItem( m_uiDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUND_CODE, NULL_STRING );
               setParameter( CLASS_CODE, dstrFundClass );
               setParameter( FUNDNUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_TO_FUND_NUM:
         case IDC_EDT_FROM_FUND_NUM:
            {
               CString cstrFundNumber;
               GetDlgItem( m_uiDialogItem )->GetWindowText( cstrFundNumber );
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
               if( ( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND_NUM ) ) || 
                   ( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND ) )   || 
                   ( GetFocus() == GetDlgItem( IDC_EDT_FROM_CLASS ) ) )
               {
                  if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                  {
                     getParent()->setField (this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST , ifds::FrFundNumber, dstrFundNumber );
                     LoadControl ( IDC_EDT_FROM_FUND_NUM );
                  }
                  getParent()->setField (this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST , ifds::FundCode, dstrFundCode );  //??
                  getParent()->setField (this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST , ifds::ClassCode, dstrClassCode );
                  LoadControl ( IDC_EDT_FROM_FUND );
                  LoadControl ( IDC_EDT_FROM_CLASS );				 
               }
               else if( ( GetFocus() == GetDlgItem( IDC_EDT_TO_FUND_NUM ) ) ||
                        ( GetFocus() == GetDlgItem( IDC_EDT_TO_FUND ) )     || 
                        ( GetFocus() == GetDlgItem( IDC_EDT_TO_CLASS ) ) )
               {
                  if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                  {
                     getParent()->setField (this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST , ifds::ToFundNumber, dstrFundNumber );
                     LoadControl ( IDC_EDT_TO_FUND_NUM );
                  }
                  getParent()->setField (this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST , ifds::FundToCode, dstrFundCode );
                  getParent()->setField (this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST , ifds::ClassToCode, dstrClassCode );
                  LoadControl ( IDC_EDT_TO_FUND );
                  LoadControl ( IDC_EDT_TO_CLASS );
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

void AccDistributionDlg::ShowBankRelated( bool bShow )
{
   DString  dstrBankIdType, strAllFundMode, strCurrencyOption;
   int   nCmdShow = bShow ? SW_SHOW : SW_HIDE;

   getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::BankIdType, dstrBankIdType, false );
   dstrBankIdType.strip();
   getParent ()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::AllFundsDistrib, strAllFundMode, false );
   strAllFundMode.strip();
   getParent ()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::AcctDistribCurrencyOption, strCurrencyOption, false );
   strCurrencyOption.strip();

   GetDlgItem( IDC_TXT_BANK_NAME )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_TRANS_NUM )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_TXT_INST_CODE )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_BANK_ACCT_NUM )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_BTN_BANK )->ShowWindow( nCmdShow );
   GetDlgItem(IDC_BTN_BANK)->EnableWindow(nCmdShow);
   if( strAllFundMode.strip() == I_( "Y" ) &&
      strCurrencyOption == FUND_CURRENCY )
   {
      GetDlgItem( IDC_BTN_BANK )->EnableWindow( FALSE );
   }
   ShowControl( IDC_EDT_BANK_NAME_VAL, bShow );
   ConnectControlToData( IDC_EDT_BANK_NAME_VAL, bShow );
   ShowControl( IDC_EDT_TRANS_NUM_VAL, false );
   ConnectControlToData( IDC_EDT_TRANS_NUM_VAL, false );
   ShowControl( IDC_EDT_INST_CODE_VAL, bShow );
   ConnectControlToData( IDC_EDT_INST_CODE_VAL, bShow );
   ShowControl( IDC_EDT_BANK_ACCT_NUM_VAL, bShow );
   ConnectControlToData( IDC_EDT_BANK_ACCT_NUM_VAL, bShow );

   if( bShow )
   {
      if( dstrBankIdType == CODE_BANKIDTYPE_CANADA || dstrBankIdType == CODE_BANKIDTYPE_JAPAN )
      {
         GetDlgItem( IDC_TXT_TRANS_NUM )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_EDT_TRANS_NUM_VAL )->ShowWindow( SW_SHOW );
         ShowControl( IDC_EDT_TRANS_NUM_VAL, true );
         ConnectControlToData( IDC_EDT_TRANS_NUM_VAL, true );

         CString str;
         str.LoadString( IDS_LBL_INSTCODE );
         SetDlgItemText( IDC_TXT_INST_CODE, str );
      }
      else if( dstrBankIdType == CODE_BANKIDTYPE_ABA )
      {
         CString str;
         str.LoadString( IDS_LBL_ABA_NBR );
         SetDlgItemText( IDC_TXT_INST_CODE, str );
      }
      else if( dstrBankIdType == CODE_BANKIDTYPE_SWIFT )
      {
         CString str;
         str.LoadString( IDS_LBL_SWIFT_CODE );
         SetDlgItemText( IDC_TXT_INST_CODE, str );
      }
      else
      {
         CString str;
         str.LoadString( IDS_LBL_NBR );
         SetDlgItemText( IDC_TXT_INST_CODE, str );
      }
   }
}

//******************************************************************
void AccDistributionDlg::OnKillfocusCmbTransType() 
{
   if( m_bScreenClose ) return;
   if( !m_bEsc )
      if( getParent() )
         getParent()->setField(this,IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::TransTypeDesc, LOCK_TRANS_TYPE,true);
}

//******************************************************************
void AccDistributionDlg::PostCancel()
{
   m_bScreenClose = true;
}

//******************************************************************
void AccDistributionDlg::OnClose() 
{
   // TODO: Add your message handler code here and/or call default
   m_bScreenClose = true; 
   BaseMainDlg::OnClose();
}

//******************************************************************
void AccDistributionDlg::OnKillfocusEdtAddressCode ()
{
   LoadControl ( IDC_EDT_ADDRESS );
}

//******************************************************************
void AccDistributionDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, I_("MULTI") );
}

//******************************************************************
void AccDistributionDlg::OnAllFundsMode()
{
   DSTButton* fullTrsfCheck = 
      dynamic_cast<DSTButton*>(GetControl(IDC_CHECK_ACCOUNT_LEVEL));

   if (fullTrsfCheck != NULL)
   {
      bool bCheck = fullTrsfCheck->GetCheck() == 1;

      getParent()->setField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, 
         ifds::AllFundsDistrib, bCheck ? I_("Y") : I_("N"), false);

      if( bCheck )
      {
         ShowControl( IDC_CMB_DISTRIB_DFLT_OPTION, true );   
         ShowControl( IDC_CMB_DISTRIB_CURRENCY_OPTION, true );
         GetDlgItem( IDC_STC_DISTRIB_DFLT_OPTION )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_STC_DISTRIB_CURRENCY_OPTION )->ShowWindow( SW_SHOW );

      }
      else
      {
         ShowControl( IDC_CMB_DISTRIB_DFLT_OPTION, false );   
         ShowControl( IDC_CMB_DISTRIB_CURRENCY_OPTION, false );
         GetDlgItem( IDC_STC_DISTRIB_DFLT_OPTION )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STC_DISTRIB_CURRENCY_OPTION )->ShowWindow( SW_HIDE );

      }
   }

   LoadListControl(IDC_LV_TO);
   CheckPermission();
}

//******************************************************************************
void AccDistributionDlg::doDisableNonPermButtons ()
{

}

//******************************************************************************
bool AccDistributionDlg::doDisablePermCheckButton (UINT nID)
{
   bool bReturn = false;

   DString AllFundMode;

   getParent ()->getField ( this, 
                            IFASTBP_PROC::ACC_DISTRIBUTION_LIST,
                            ifds::AllFundsDistrib, 
                            AllFundMode );
   AllFundMode.strip().upperCase();

   bool bVerificationEnabled = false;
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
   DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   pWorkSession->isVerificationEnabled ( idDataGroup, 
                                         DISTRIB_CATEGORY, 
                                         DISTRIB_LEVEL, 
                                         bVerificationEnabled);

   DString strVerifyStat, strDistribGBCD, strSubDistribGBCD;
   getParent()->getField( this, 
                          IFASTBP_PROC::ACC_DISTRIBUTION_LIST , 
                          ifds::VerifyStat, 
                          strVerifyStat,
                          false );
   getParent()->getField( this, 
                          IFASTBP_PROC::ACC_DISTRIBUTION_LIST , 
                          ifds::DistribGBCD, 
                          strDistribGBCD,
                          false );
   getParent()->getField( this, 
                          IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST , 
                          ifds::DistribGBCD, 
                          strSubDistribGBCD,
                          false );

   strVerifyStat.strip().upperCase();
   strDistribGBCD.strip().upperCase();
   strSubDistribGBCD.strip().upperCase();

   if ( AllFundMode == I_( "Y" ) )
   {
      if (nID == IDC_BTN_ADD_TO || nID == IDC_BTN_DELETE_TO)
      {
         bReturn = true;
      }
      else if ( nID == IDC_BTN_DELETE_FROM )
      {
         if ( bVerificationEnabled && strVerifyStat == UNVERIFIED && strDistribGBCD == I_("N"))
         {
            bReturn = true;
         }
      }
   }
   else
   {
      if ( bVerificationEnabled )
      {
         if ( nID == IDC_BTN_DELETE_FROM )
         {
            // deleted and waiting for verification on from side
            if ( strVerifyStat == UNVERIFIED && strDistribGBCD == I_("N"))
            {
               bReturn = true;
            }
         }
         else if (nID == IDC_BTN_ADD_TO || nID == IDC_BTN_DELETE_TO)
         {
            // deleted and waiting for verification on to side
            if ( strVerifyStat == UNVERIFIED && strSubDistribGBCD == I_("N"))
            {
               bReturn = true;
            }
         }
      }
   }
   return bReturn;
}

void AccDistributionDlg::setRadioButton()
{
	((CButton* )GetDlgItem(IDC_RB_PERCENTAGE))->SetCheck(m_rbInputMethod == 0);
	((CButton* )GetDlgItem(IDC_RB_DISTRIBRATE))->SetCheck(m_rbInputMethod == 1);	
}

//**********************************************************************************
void AccDistributionDlg::OnRbPercentage()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbPercentage" ) );

	if( m_rbInputMethod != 0 )
	{
		m_rbInputMethod = 0;		
		getParent()->setField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::DistribInputMethod, I_("0"), false );
		switchInputMethod(true);
	}
}

//**********************************************************************************
void AccDistributionDlg::OnRbDistribRate()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbDistribRate" ) );

	if( m_rbInputMethod != 1 )
	{
		m_rbInputMethod = 1;
		getParent()->setField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::DistribInputMethod, I_("1"), false );
		switchInputMethod(true);
	}
}

void AccDistributionDlg::switchInputMethod (bool bOnRbInputMethod)
{
	setRadioButton();

	GetDlgItem (IDC_STC_INPUT_METHOD)->ShowWindow (SW_SHOW);
	GetDlgItem (IDC_RB_PERCENTAGE)->ShowWindow (SW_SHOW);
	GetDlgItem (IDC_RB_DISTRIBRATE)->ShowWindow (SW_SHOW);

	DString dstrFundCode;
	getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::FundCode, dstrFundCode, false );		
	dstrFundCode.strip();
	bool bMoneyMarket = isMoneyMarketFund (dstrFundCode);

	if (bOnRbInputMethod) 
	{
		int nItems = GetList( IDC_LV_TO )->GetItemCount();
		if (nItems > 0) 
		{
			bool bIsDummy = getParentProcess()->isCurrentListItemDummy( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
			if (!(bIsDummy && nItems == 1)) 
			{
				DString dstrTotalDistribRate, dstrTotalAllocPercent;
				getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::TotalDistribRate, dstrTotalDistribRate, false );
				getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::TotalAllocPercent, dstrTotalAllocPercent, false );

				if (!dstrTotalDistribRate.strip().empty()) 
				{
					int dDistribRate = (int) (DSTCommonFunctions::convertToDouble(dstrTotalDistribRate) * 1000000);
					int dTotalAllocPercent = (int) (DSTCommonFunctions::convertToDouble(dstrTotalAllocPercent) * 10000);

					if ( dDistribRate > 0 ) {
						GetDlgItem (IDC_RB_PERCENTAGE)->EnableWindow (false);
						GetDlgItem (IDC_RB_DISTRIBRATE)->EnableWindow (true);
					} else {
						if ( dTotalAllocPercent > 0 ) {
							GetDlgItem (IDC_RB_PERCENTAGE)->EnableWindow (true);
							GetDlgItem (IDC_RB_DISTRIBRATE)->EnableWindow (false);
						} else {
							GetDlgItem (IDC_RB_PERCENTAGE)->EnableWindow (true);
							GetDlgItem (IDC_RB_DISTRIBRATE)->EnableWindow (true);
						}
					}
				}
			} else {
				GetDlgItem (IDC_RB_PERCENTAGE)->EnableWindow (true);
				GetDlgItem (IDC_RB_DISTRIBRATE)->EnableWindow (!bMoneyMarket);
			}
		}
	} else if (bMoneyMarket) {
			GetDlgItem (IDC_RB_DISTRIBRATE)->EnableWindow (false);			
	}

	if (m_rbInputMethod == 1) 
	{
		GetDlgItem (IDC_STC_RECENT_DISTRIBUTION)->ShowWindow (SW_SHOW);
		LoadControl (IDC_TXT_RECENT_DISTRIBUTION);
		GetDlgItem (IDC_TXT_RECENT_DISTRIBUTION)->ShowWindow (SW_SHOW);
	} 
	else 
	{
		GetDlgItem (IDC_STC_RECENT_DISTRIBUTION)->ShowWindow (SW_HIDE);
		GetDlgItem (IDC_TXT_RECENT_DISTRIBUTION)->ShowWindow (SW_HIDE);	
	}

	CString cstrTotal;
	cstrTotal.LoadString (TXT_TOTAL_PERCENTAGE);		
	GetDlgItem (IDC_STC_TOTAL_PERCENTAGE)->SetWindowText (cstrTotal);		
	GetDlgItem (IDC_STC_TOTAL_PERCENTAGE)->ShowWindow (SW_SHOW);		

	if (m_rbInputMethod == 1) 
	{
		GetDlgItem (IDC_STC_DISTRIB_RATE)->ShowWindow (SW_SHOW);
		GetDlgItem (IDC_EDT_DISTRIB_RATE)->ShowWindow (SW_SHOW);			
		GetDlgItem (IDC_STC_TOTAL_DISTRIB_RATE)->ShowWindow (SW_SHOW);
		GetDlgItem (IDC_TXT_TOTAL_DISTRIB_RATE)->ShowWindow (SW_SHOW);
		dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_PERCENTAGE ) )->SetReadOnly();
	} 
	else 
	{
		GetDlgItem (IDC_STC_DISTRIB_RATE)->ShowWindow (SW_HIDE);
		GetDlgItem (IDC_EDT_DISTRIB_RATE)->ShowWindow (SW_HIDE);
		GetDlgItem (IDC_STC_TOTAL_DISTRIB_RATE)->ShowWindow (SW_HIDE);
		GetDlgItem (IDC_TXT_TOTAL_DISTRIB_RATE)->ShowWindow (SW_HIDE);
		dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_PERCENTAGE ) )->SetReadOnly(false);
	}
}

void AccDistributionDlg::showHideDistribRateControls ()
{
	DString dstrDistribRateOpt = NO, dstrTransType, dstrTotalDistribRate;
	getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::TransType, dstrTransType, false );			
	dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(  ifds::DistribInstrAsRatioOpt , dstrDistribRateOpt, BF::HOST, false );	

	bool bShow = ((dstrTransType.strip() == I_( "ID" )) && (dstrDistribRateOpt == YES)) ? true : false;

	if (bShow) 
	{
		m_rbInputMethod = -1;
		getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::TotalDistribRate, dstrTotalDistribRate, false );
		int dTotalDistribRate = (int) (DSTCommonFunctions::convertToDouble(dstrTotalDistribRate) * 1000000);
		if ( dTotalDistribRate > 0 ) {
			OnRbDistribRate();
		} else {
			OnRbPercentage();
		}
	} 
	else 
	{
		hideDistribRateControls();
	}

}

void AccDistributionDlg::hideDistribRateControls ()
{
	GetDlgItem (IDC_STC_INPUT_METHOD)->ShowWindow (SW_HIDE);	
	GetDlgItem (IDC_RB_PERCENTAGE)->ShowWindow (SW_HIDE);
	GetDlgItem (IDC_RB_DISTRIBRATE)->ShowWindow (SW_HIDE);
	GetDlgItem (IDC_STC_RECENT_DISTRIBUTION)->ShowWindow (SW_HIDE);
	GetDlgItem (IDC_TXT_RECENT_DISTRIBUTION)->ShowWindow (SW_HIDE);		

	CString cstrTotal;
	cstrTotal.LoadString (TXT_TOTAL);
	GetDlgItem (IDC_STC_TOTAL_PERCENTAGE)->SetWindowText (cstrTotal); 		
	GetDlgItem (IDC_STC_TOTAL_PERCENTAGE)->ShowWindow (SW_SHOW);		

	GetDlgItem (IDC_STC_DISTRIB_RATE)->ShowWindow (SW_HIDE);
	GetDlgItem (IDC_EDT_DISTRIB_RATE)->ShowWindow (SW_HIDE);
	GetDlgItem (IDC_STC_TOTAL_DISTRIB_RATE)->ShowWindow (SW_HIDE);
	GetDlgItem (IDC_TXT_TOTAL_DISTRIB_RATE)->ShowWindow (SW_HIDE);

}

void AccDistributionDlg::CalcTotalDistribRate( DString &dstrOutTotalDistribRate ) const
{
	if( !getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ) )
	{
		dstrOutTotalDistribRate = NULL_STRING;
		return;
	}

	DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();

	bool bVerificationEnabled = false;
	pWorkSession->isVerificationEnabled ( idDataGroup, 
		DISTRIB_CATEGORY, 
		DISTRIB_LEVEL, 
		bVerificationEnabled );

	// 1. remember the current positions in the list, to restore it later
	const DString *pCurrKey = &( getParent()->getCurrentListItemKey( this, 
		IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ) );

	// 2. calculate total distribution rate
	const DString *pKey = &( getParent()->getFirstListItemKey( this, 
		IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ) );
	double dDistribRate = 0.0;
	if( *pKey != NULL_STRING )
	{
		DString dstr,dstrGoodBad;
		do
		{
			getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
				ifds::DistribRate, dstr );
			getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
				ifds::DistribGBCD, dstrGoodBad, false );

			dstrGoodBad.strip().upperCase();
			dstr.strip().stripAll( I_CHAR( ',' ) );		

			// if system has verification enable only sum with good record
			// otherwise sum all records
			if ( bVerificationEnabled )
			{
				if ( dstrGoodBad != I_("N") )
				{					
					dDistribRate += DSTCommonFunctions::convertToDouble(dstr);
				}
				else
				{
					continue;
				}
			}
			else
			{
				dDistribRate += DSTCommonFunctions::convertToDouble(dstr);	
			}
		}
		while( *( pKey = &( getParent()->getNextListItemKey( this, 
			IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ) ) ) != NULL_STRING );
	}

	// 3. restore the initial iterator position in the list
	getParent()->setCurrentListItem( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, 
		*pCurrKey );

	// 4. format string
	DString dstrDMask = DSTCommonFunctions::getMask( ifds::DistribRate );
	dstrDMask.strip();
	int iMaskNumDigitsAfterDecimalPoint = dstrDMask.length() 
		- dstrDMask.find( I_( "." ) ) - 1;
	double dFactor = pow( 10, iMaskNumDigitsAfterDecimalPoint );
	//rounding dTotalPercent:
	assert( dDistribRate >= 0 );
	dDistribRate *= dFactor;
	dDistribRate += .5;
	dDistribRate = floor( dDistribRate );
	dDistribRate /= dFactor;
	
	dstrOutTotalDistribRate = DSTCommonFunctions::doubleToDString( ifds::TotalDistribRate, dDistribRate );	
	getParent()->setField( this, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, ifds::TotalDistribRate, dstrOutTotalDistribRate, false );	

}

void AccDistributionDlg::getLastIDRate( DString &dstrOutRecentDistribRate ) const
{
	getParent()->getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::LastIDRate, dstrOutRecentDistribRate );
	dstrOutRecentDistribRate = I_CHAR( '$' ) + dstrOutRecentDistribRate;   
}

bool AccDistributionDlg ::isMoneyMarketFund(const DString &fundCode)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "isMoneyMarketFund" ) );	

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	FundMasterList *pFundMasterList = NULL;
	bool blIsMoneyMarketFund = false;		

	if (dstWorkSession && dstWorkSession->getMgmtCo().getFundMasterList(pFundMasterList) <= WARNING && pFundMasterList)
	{			
		if(pFundMasterList->isMoneyMarketFund(fundCode))
		{			
			blIsMoneyMarketFund = true;	
		}
	}	

	return blIsMoneyMarketFund;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccDistributionDlg.cpp-arc  $
 * 
 *    Rev 1.82   Aug 16 2011 10:52:46   wutipong
 * IN2527545 iFast Desktop image popus up in 2 screens for QC user.
 * 
 *    Rev 1.81   Nov 25 2010 13:57:46   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.80   Feb 06 2010 17:35:30   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one. Remove display of 'DistribGBCD' from To-side.
 * 
 *    Rev 1.79   Feb 03 2010 18:55:50   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.78   Jan 22 2010 09:04:40   dchatcha
 * IN# 1982767 - Rel 97 - Static Data - Display of Verified status.
 * 
 *    Rev 1.77   Jan 13 2010 09:17:16   dchatcha
 * IN# 1971377 - R97_Static Data_File Processor&Bank are blank after deleting distribution option.
 * 
 *    Rev 1.76   Dec 14 2009 03:22:26   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2, Negative testing, 'Verify Status' field should not be displayed on non-support for verification environment.
 * 
 *    Rev 1.75   Dec 03 2009 03:59:22   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.74   26 Feb 2009 16:16:52   kovacsro
 * IN#1586761 - Issues regarding Account Level Distribution entry on Desktop
 * 
 *    Rev 1.73   23 Feb 2009 15:32:00   kovacsro
 * P0155543_FN01_ Account Level Distribution 
 * 
 *    Rev 1.66   Feb 26 2008 15:00:18   daechach
 * In# 1160207 - Desktop distribution - Added 'More' button to account distribution screen.
 * 
 *    Rev 1.65   21 Dec 2007 14:43:36   kovacsro
 * PET2400FN01 - account level distribution instruction
 * 
 *    Rev 1.64   Sep 15 2005 15:09:36   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.63   Mar 10 2004 13:12:16   HERNANDO
 * PET965 FN11 - Added parameter to iFastHistoricalInfo.
 * 
 *    Rev 1.62   Feb 28 2004 16:13:58   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.61   Nov 10 2003 11:04:32   FENGYONG
 * Fix all the ticket 10023881 relate bugs.
 * 
 *    Rev 1.60   Nov 07 2003 16:02:06   FENGYONG
 * PTS 10023881 Account distribution 
 * 
 *    Rev 1.59   Sep 17 2003 16:28:56   ZHANGCEL
 * PTS ticket 10021850 & 10021878: fix <Bank> botton missing when PayMethod is empty.
 * 
 *    Rev 1.58   Jun 19 2003 17:25:36   FENGYONG
 * Add PayMethod and ACHProcessor two combo boxes
 * 
 *    Rev 1.57   Jun 12 2003 15:48:36   popescu
 * Fix crash related to refresh the current list item during a set focus on the currency combo 
 * 
 *    Rev 1.56   Jun 01 2003 17:08:14   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.55   May 26 2003 11:27:56   popescu
 * OnBtnBank button clean-up
 * 
 *    Rev 1.54   May 23 2003 10:04:28   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.53   May 22 2003 14:13:40   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.52   Apr 22 2003 13:50:42   PURDYECH
 * PTS 10116189.  Added ON_WM_CLOSE to activate the close processing when the window is closed using the System Menu.
 * 
 *    Rev 1.51   Apr 15 2003 12:07:14   sanchez
 * Ticket 10015074 sync up with version 1.48.10
 * 
 *    Rev 1.50   Mar 21 2003 18:30:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.49   Feb 26 2003 10:35:50   PURDYECH
 * Style changes.
 * 
 *    Rev 1.48   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.47   Sep 30 2002 11:01:32   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.46   Aug 29 2002 12:57:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.45   Jul 25 2002 08:35:26   HSUCHIN
 * bug fix which locks the transaction type after lost focus
 * 
 *    Rev 1.44   Jul 12 2002 15:37:24   YINGBAOL
 * PTS10008890
 * 
 *    Rev 1.43   May 23 2002 10:39:30   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.42   18 Apr 2002 15:27:28   HSUCHIN
 * Added support for Management Fee Rebate Distribution
 * 
 *    Rev 1.41   27 Mar 2002 20:00:48   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.40   19 Nov 2001 16:28:22   KOVACSRO
 * Hour glass.
 * 
 *    Rev 1.39   Nov 07 2001 17:57:04   ZHANGCEL
 * Haspermission changes
 * 
 *    Rev 1.38   Jul 05 2001 13:50:18   HERNANDO
 * Clean up.
 * 
 *    Rev 1.37   14 Jun 2001 11:58:04   SMITHDAV
 * Removed references to UserAccessProcess.
 * 
 *    Rev 1.36   Jun 11 2001 15:10:34   OLTEANCR
 * code sync. - translation issues
 * 
 *    Rev 1.35   14 May 2001 14:50:32   YINGZ
 * code sync up
 * 
 *    Rev 1.34   26 Apr 2001 16:45:38   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.33   Apr 19 2001 11:24:54   DINACORN
 * Add "International Wire" pay type
 * 
 *    Rev 1.32   Apr 17 2001 17:15:26   HERNANDO
 * Quick fix/patch to call ShowBankRelated after Bank Btn
 * 
 *    Rev 1.31   Apr 17 2001 14:47:40   HERNANDO
 * Displays BankIdValue instead of InstCode.
 * 
 *    Rev 1.30   Apr 17 2001 14:31:54   HERNANDO
 * Chg'd ShowBankRelated; displays BankIdValue or InstCode
 * 
 *    Rev 1.29   Apr 16 2001 17:33:52   HERNANDO
 * Added ShowBankRelated fn.
 * 
 *    Rev 1.28   10 Apr 2001 16:08:56   BUZILAMI
 * launching the new BankInstr
 * 
 *    Rev 1.27   06 Apr 2001 09:24:52   KOVACSRO
 * Perm. check for F4 key.
 * 
 *    Rev 1.26   Mar 30 2001 16:38:44   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.25   27 Mar 2001 16:39:40   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.24   01 Mar 2001 16:36:44   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.23   Feb 12 2001 16:19:42   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.22   Feb 07 2001 17:02:36   DINACORN
 * Another fix for M3/C4 synchronization
 * 
 *    Rev 1.21   Feb 05 2001 10:47:46   DINACORN
 * Fix for M3 / C4 synchronization
 * 
 *    Rev 1.20   Feb 05 2001 10:08:54   DINACORN
 * Synchronization M3 / C4
 * 
 *    Rev 1.19   Dec 13 2000 14:32:44   KOVACSRO
 * 1. Modified DoListItemChanged.
 * 2.Added Dummy Item logic for perm. check.
 * 
 *    Rev 1.18   Dec 05 2000 17:16:46   KOVACSRO
 * 1.Added new item permission logic.
 * 2.Enabled Bank button.
 * 
 *    Rev 1.17   Dec 01 2000 14:38:16   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.16   Sep 29 2000 13:29:12   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.15   Sep 25 2000 11:25:14   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.14   Aug 28 2000 10:01:16   ZHANGCEL
 * Fine tune
 * 
 *    Rev 1.13   Aug 18 2000 11:03:12   ZHANGCEL
 * Fixed the bug of SetDataFromContrl()
 * 
 *    Rev 1.12   Aug 02 2000 10:03:06   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.11   Jul 28 2000 16:46:58   ZHANGCEL
 * Search Fund bug fixed
 * 
 *    Rev 1.10   Jul 25 2000 16:15:02   HERNANDO
 * Sets parameters for Search Fund
 * 
 *    Rev 1.9   Jul 25 2000 14:33:04   ZHANGCEL
 * Added code for fund number stuffs of C2
 * 
 *    Rev 1.8   Jun 06 2000 11:12:20   HSUCHIN
 * bug fix with to fix class code not picked up in validation
 * 
 *    Rev 1.7   Jun 05 2000 11:58:56   HSUCHIN
 * code clean up
 * 
 *    Rev 1.6   Jun 05 2000 10:24:54   HSUCHIN
 * fund search dlg implement.  fund/class combo boxes removed.
 * 
 *    Rev 1.5   Apr 05 2000 09:39:58   DT24433
 * changed to use hasPermission
 * 
 *    Rev 1.4   Mar 21 2000 10:21:36   HSUCHIN
 * removed fund number from fund combo box
 * 
 *    Rev 1.3   Mar 20 2000 13:30:08   HSUCHIN
 * changed GetFundNumber to use DSTCommonFunction's version
 * 
 *    Rev 1.2   Mar 07 2000 16:23:34   HSUCHIN
 * added Fund Number for C2
 * 
 *    Rev 1.1   Feb 15 2000 18:59:02   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.47   Feb 07 2000 13:46:32   PRAGERYA
 * Bug fixed (wrong calculation of the num of decimal places in edit boxes)
 * 
 *    Rev 1.46   Feb 03 2000 16:07:54   YINGZ
 * code clean up
 * 
 *    Rev 1.45   Jan 31 2000 13:25:58   YINGZ
 * fix currency problem
 * 
 *    Rev 1.44   Jan 30 2000 19:11:32   YINGZ
 * for release
 * 
 *    Rev 1.43   Jan 26 2000 17:53:40   YINGZ
 * refresh bottom list when back from bi
 * 
 *    Rev 1.42   Jan 26 2000 16:58:40   YINGZ
 * fix load currency problem
 * 
 *    Rev 1.41   Jan 25 2000 17:13:02   YINGZ
 * change instname display
 * 
 *    Rev 1.40   Jan 25 2000 16:42:04   YINGZ
 * add reset, refresh, admindate, focus etc
 * 
 *    Rev 1.39   Jan 22 2000 18:42:38   YINGZ
 * bug fix
 * 
 *    Rev 1.38   Jan 21 2000 16:18:38   PRAGERYA
 * For Zijian
 * 
 *    Rev 1.37   Jan 21 2000 13:05:14   PRAGERYA
 * Latest fixes
 * 
 *    Rev 1.36   Jan 20 2000 14:52:44   PRAGERYA
 * Bug fixed
 * 
 *    Rev 1.35   Jan 20 2000 10:32:48   PRAGERYA
 * For Zijian
 * 
 *    Rev 1.34   Jan 18 2000 18:11:34   PRAGERYA
 * For release
 * 
 *    Rev 1.33   Jan 14 2000 16:23:58   PRAGERYA
 * For Jerry
 * 
 *    Rev 1.32   Jan 13 2000 14:08:34   PRAGERYA
 * Bug fixes
 * 
 *    Rev 1.31   Jan 11 2000 18:02:58   PRAGERYA
 * Bugs fixed
 * 
 *    Rev 1.30   Jan 10 2000 17:00:22   PRAGERYA
 * For Zijian
 * 
 *    Rev 1.29   Jan 10 2000 09:46:14   PRAGERYA
 * Again...
 * 
 *    Rev 1.28   Jan 09 2000 16:42:44   PRAGERYA
 * Made compilable!
 * 
 *    Rev 1.27   Jan 07 2000 20:33:44   PRAGERYA
 * For Mihai
 * 
 *    Rev 1.26   Dec 30 1999 12:40:38   YINGBAOL
 * split list sync
 * 
 *    Rev 1.25   Dec 22 1999 11:27:26   YINGBAOL
 * hllapi change sync
 * 
 *    Rev 1.24   Dec 22 1999 10:16:20   YINGBAOL
 * check in for release
 * 
 *    Rev 1.23   Dec 13 1999 10:41:10   YINGBAOL
 * check in for release
 * 
 *    Rev 1.21   Dec 03 1999 11:38:04   YINGBAOL
 * sync base change
 * 
 *    Rev 1.20   Nov 30 1999 19:46:22   YINGBAOL
 * select all fund as default
 * 
 *    Rev 1.19   Nov 25 1999 12:04:30   YINGBAOL
 * check in for first M2 release
 * 
 *    Rev 1.18   Nov 16 1999 17:24:46   YINGBAOL
 * change PayType to DistributionPayType Sync 
 * 
 *    Rev 1.17   Nov 15 1999 16:37:24   YINGBAOL
 * 
 *    Rev 1.16   Nov 09 1999 12:10:22   YINGZ
 * add list filter
 * 
 *    Rev 1.15   Nov 02 1999 12:25:14   YINGZ
 * add info to open bank dlg
 * 
 *    Rev 1.14   Oct 28 1999 09:35:08   YINGZ
 * for a clean Get from PVCS!
 * 
 *    Rev 1.13   Oct 05 1999 11:12:42   YINGZ
 * fix hour glass problem
 * 
 *    Rev 1.12   Oct 01 1999 15:33:24   YINGZ
 * disable delete button when there is no distribution
 * 
 *    Rev 1.11   Sep 23 1999 13:04:52   YINGZ
 * make it wokr for c1
 * 
 *    Rev 1.10   13 Sep 1999 14:07:24   HUANGSHA
 * Synchronize with M1's changes
 * 
 *    Rev 1.9   Aug 19 1999 16:00:52   PRAGERYA
 * BankAccTypeDesc -> BankAcctTypeDesc 
 * 
 *    Rev 1.8   Aug 17 1999 12:45:40   DT24433
 * changed getFieldFromCurrentListItem to getField
 * 
 *    Rev 1.7   Aug 08 1999 17:08:08   VASILEAD
 * Refixed a refresh issue
 * 
 *    Rev 1.6   Aug 08 1999 13:56:36   POPESCUS
 * Fixed a refresh issue
 * 
 *    Rev 1.5   Jul 20 1999 14:24:26   YINGZ
 * ?
 * 
 *    Rev 1.4   Jul 20 1999 11:18:10   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 19 1999 12:52:38   POPESCUS
 * Added user access checks for the ban button
 * 
 *    Rev 1.2   Jul 09 1999 16:48:50   YINGZ
 * change listview support to use Jerry's fix
 * 
 *    Rev 1.1   Jul 08 1999 10:04:28   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */


