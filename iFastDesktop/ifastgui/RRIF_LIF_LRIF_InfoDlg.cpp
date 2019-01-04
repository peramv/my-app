// RRIF_LIF_LRIF_InfoDlg.cpp : implementation file
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
// ^FILE   : RRIF_LIF_LRIF_InfoDlg.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : Feb 09, 2000
//
// ----------------------------------------------------------
//
// ^CLASS    : RRIF_LIF_LRIF_InfoDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the RRIF dialog
//
//******************************************************************************

#include "stdafx.h"
#include <bfdata\bfdata.hpp>
#include <ifastbp\allocationsprocessincludes.h>
#include <ifastcsi\csisession.h>
#include <uibase\dstlistctrl.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstcombobox.h>
#include <uibase\dsttabctrl.h>
#include "mfdstc.h"
#include <bfproc\abstractprocess.hpp>
#include "rrif_lif_lrif_infodlg.h"
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\rrif_lif_lrif_infoprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <assert.h>
#include <ifastbp\minmaxinfoprocessincludes.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\financialinstitution.hpp>
#include <ifastdataimpl\dse_dstc0129_req.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MINMAXINFO;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_RRIF_LIF_LRIF_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FROM_TO_ALLOCATION;


#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RRIF_LIF_LRIF_InfoDlg > dlgCreator( CMD_GUI_RRIF_LIF_LRIF_INFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace RRIF_INFO_CONTROLS
{
   const int GENERAL_INFO_PAYMENT    = 1;
   const int MISC                    = 2;
}

namespace
{
   const I_CHAR * const CLASSNAME       = I_( "RRIF_LIF_LRIF_InfoDlg" );
   const I_CHAR * const LV_RRIF         = I_( "lvRRIF" );
   const I_CHAR * const LV_RRIF_ALLOC   = I_( "lvRRIF_Alloc" );
   const I_CHAR * const LV_TO_ALLOC     = I_( "lvTO_Alloc" );


   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const GOODBAD        = I_("GoodBad");
   const I_CHAR * const MOD_USER       = I_( "ModUser" );
   const I_CHAR * const MOD_DATE       = I_( "ModDate" );
   const I_CHAR * const USER_NAME      = I_( "Username" );
   const I_CHAR * const PROCESS_DATE   = I_( "ProcessDate" );
   const I_CHAR * const ACCOUNT_NUM    = I_( "AccountNum" );
   const I_CHAR * const LISTKEY        = I_( "ListKey" );
   const I_CHAR * const ADDRESS_CODE   = I_( "AddressCode" );
   const I_CHAR * const MAND_PAYMENT   = I_( "MandAmtPay" );
   const I_CHAR * const AMOUNT         = I_( "Amount" );
   const I_CHAR * const PERCENT        = I_( "P" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_FIELD_INFO;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_INFO;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_TAX_UPDATE;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const RRIF;
}
//P0186486_FN15_The Source of Funds
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId RRIFSrcOfFund; //remove later when done vew67,129
   extern CLASS_IMPORT const BFTextFieldId RRIFSrcOfAcct; //remove later when done vew67,129
}

/////////////////////////////////////////////////////////////////////////////
// RRIF_LIF_LRIF_InfoDlg dialog

BEGIN_MESSAGE_MAP(RRIF_LIF_LRIF_InfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RRIF_LIF_LRIF_InfoDlg)
ON_BN_CLICKED(IDC_BTN_ADDRESS, OnBtnAddress)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_ALLOCATION, OnBtnAllocation)
ON_BN_CLICKED(IDC_BTN_BANK, OnBtnBank)
ON_BN_CLICKED(IDC_BTN_MIN_MAX, OnBtnMinMax)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_ADD_COPY, OnBtnAddCopy)
ON_BN_CLICKED(IDC_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_CALCULATE, OnBtnCalculate)
ON_MESSAGE( WM_LAUNCH_IDENT_ACC,OpenIdentifyAccountsDlg )
ON_WM_DESTROY()
ON_BN_CLICKED (IDC_CHK_ONLY_ACTIVE_RRIF, OnChkActiveOnly) //added for CHG0041174
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
RRIF_LIF_LRIF_InfoDlg::RRIF_LIF_LRIF_InfoDlg( CWnd* pParent, 
   GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RRIF_LIF_LRIF_InfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( 0 )
, m_pFont( 0 )
, m_iCurrentPage( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(RRIF_LIF_LRIF_InfoDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_CHK_ONLY_ACTIVE_RRIF, m_ckbActiveOnly);//Added for CHG0041174

   //{{AFX_DATA_MAP(RRIF_LIF_LRIF_InfoDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_InfoDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   getParameter(RRIF_LIF_LRIF::ACCOUNT_NUMBER_FIELD, m_strAccountNumber);
   getParameter(RRIF_LIF_LRIF::SHAREHOLDER_FIELD, m_strShareholderNum);
   getParameter(RRIF_LIF_LRIF::FIRST_NAME_FIELD, m_strFirstName);

   return NO_CONDITION;
}

//******************************************************************************
BOOL RRIF_LIF_LRIF_InfoDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));

   BaseMainDlg::OnInitDialog();

   DString strTaxType;

   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, 
      ifds::TaxType, strTaxType );
   strTaxType.strip();

   DString str;
   
   CString cstrShrhldInfo, cstrAcctNbr;
   cstrShrhldInfo.LoadString(TXT_SHRHLDR_INFO);
   str = strTaxType + DString(cstrShrhldInfo) + m_strShareholderNum;
   cstrAcctNbr.LoadString(TXT_RESP_ACCOUNT);
   str += DString(cstrAcctNbr) + m_strAccountNumber  + I_("; ") + m_strFirstName;

   SetWindowText( str.c_str() );

   //DString strGrpPaymentCaption = strTaxType + I_( " Pa&yment" );

   //GetDlgItem( IDC_GRP_PAYMENT )->SetWindowText(strGrpPaymentCaption.c_str());

   //Alignment of the monthly indicator
   m_pFont = new CFont;
   if (m_pFont)
   {
      CString strFaceName("Courier");

      m_pFont->CreatePointFont(10, strFaceName);
      GetDlgItem(IDC_LBL_UP_MONTHLY)->SetFont(m_pFont);
      GetDlgItem(IDC_EDT_MONTHLY)->SetFont(m_pFont);
   }

   //enable all buttons
   GetDlgItem( IDC_BTN_ADD )->EnableWindow( true );
   GetDlgItem( IDC_BTN_DELETE )->EnableWindow( true );
   //GetDlgItem( IDC_BTN_MORE )->EnableWindow( true );
   GetDlgItem( IDOK )->EnableWindow( true );
   GetDlgItem( IDC_BTN_ADD_COPY )->EnableWindow( true );
   GetDlgItem( IDC_RESET )->EnableWindow( true );

   return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );


   //add the list controls
   AddListControl( CLASSNAME, IDC_LV_RRIF,LV_RRIF, ifds::LV_RRIF_Heading, 
      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 0, true, LISTFLAG_TIMER);
   AddListControl( CLASSNAME, IDC_LV_RRIF_ALLOC, LV_RRIF_ALLOC, ifds::LV_RRIF_AllocHeading, 
      IFASTBP_PROC::RRIF_FROM_ALLOC_LIST, IDC_LV_RRIF, true, LISTFLAG_NOT_AUTO_ADD);

   AddListControl( CLASSNAME, IDC_LV_TO_ALLOC, LV_TO_ALLOC, ifds::LV_RRIF_AllocHeading, 
      IFASTBP_PROC::RRIF_TO_ALLOC_LIST, IDC_LV_RRIF, true, LISTFLAG_NOT_AUTO_ADD);

   //add the controls
   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::EffectiveFrom, 0, IDC_LV_RRIF );
   AddControl( CTRL_DATE, IDC_DTP_STOP_DATE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::StopDate, 0, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_QUALIFIED, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::Qualified, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_DATE, IDC_DTP_SPOUSE_BIRTH, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::SpouseBirth, 0, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_SRC_OF_FUND, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RIFSrcOfFund, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_NOW_PLAN_VALUE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::NowPlanValue, 0, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_PYE_PLAN_VALUE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::PYEPlanValue, 0, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_CALC_MAND_YR, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::CalcMandYr, 0, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_BATCH_NAME, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::BatchName, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_MONTHLY, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::MonthIndicator, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_MIN_WITH_AGE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::MinWithAge, 0, IDC_LV_RRIF );  
   AddControl( CTRL_STATIC, IDC_TXT_PAY_TERM, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::PayTerm, 0, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_FACTOR, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::Factor, 0, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_CALC_MAX_YR, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::CalcMaxYr, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_BATCH_TRACE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RRIFBatchTrace, 0, IDC_LV_RRIF ); //BatchTrace
   AddControl( CTRL_STATIC, IDC_TXT_PENSION_JURIS, 
      CTRLFLAG_MANUAL_LOAD | CTRLFLAG_GUI_FIELD, 0 );
   AddControl( CTRL_STATIC, IDC_EDT_PENSION_JURIS, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::PensionJuris, 0, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_PAY_OPTION, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::PayOption, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_PAY_TYPE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RIFPayType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_TAX_ON_MIN, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::TaxOnMin, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_ADDR_CODE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::AddrCode, 0, IDC_LV_RRIF );  
   AddControl( CTRL_COMBO, IDC_CMB_GROSS_OR_NET, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::GrossNetMethod, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_OVERRIDE_AMT_YR, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::OverrideAmtYr, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_SUPP_FED_TAX, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::SuppFedTax, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_SUPP_PROV_TAX, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::SuppProvTax, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_INDEX_AMOUNT, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::IndexRate, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_AMOUNT, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RRIFAmount, 0, IDC_LV_RRIF );
   DSTEdit *dstEditRRIFAmount = dynamic_cast<DSTEdit *> (GetDlgItem (IDC_EDT_AMOUNT));
   if (NULL != dstEditRRIFAmount )
   {
      dstEditRRIFAmount->SetAllowedChars( I_("-.0123456789" ) );

      DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::RRIFAmount );
      int iDecimalPointPos = dstrPercentageMask.find (I_("."));	

      dstEditRRIFAmount->setInputAllowedUnsignedDecimal();
      dstEditRRIFAmount->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos );
      dstEditRRIFAmount->setMaxNumDigitsAfterDecimalPoint( dstrPercentageMask.length() - iDecimalPointPos - 2 );		
   }

   AddControl( CTRL_EDIT, IDC_EDT_MAND_AMT_YR, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::MandAmtYr, 0, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_MAND_AMT_PAY, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::MandAmtPay, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_NET_AMT, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::NetAmt, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_MAX_AMT_YR, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::MaxAmtYr, 0, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_OVERR_UNUSED_MAX, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::OverrideUnusedMax, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_UNUSED_MAX, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::PYUnusedMax, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_FED_RATE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::FedRate, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_PROV_RATE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::ProvRate, 0, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_FED_RATE_PUD, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::FedRatePUD, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_PROV_RATE_PUD, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::ProvRatePUD, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_END_OF_MONTH, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::EndOfMonth, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_LAST_PROCESS_DATE, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::LastProcessDate, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::ShareholderAddress,CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_COMBO, IDC_CMB_FREQUENCY, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::Frequency, CTRLFLAG_INITCOMBO_BY_SUB_LIST /*| CTRLFLAG_GUI_FIELD*/, IDC_LV_RRIF );   
   AddControl( CTRL_EDIT, IDC_EDT_ACCOUNT_TO, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::AccountTo, 0, IDC_LV_RRIF );   
   AddControl( CTRL_EDIT, IDC_EDT_PREYR_PERCENT, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::PreYrPercent, 0, IDC_LV_RRIF );   

   AddControl( CTRL_COMBO, IDC_CMB_DAY_OF_WEEK, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::DayOfWeek, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_DAYS_OF_MONTH, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::DaysOfMonth, 0, IDC_LV_RRIF );

   AddControl( CTRL_STATIC, IDC_TXT_REF_TEMP_INCOME, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RefTempInc, 0, IDC_LV_RRIF );
   AddControl( CTRL_STATIC, IDC_TXT_ADJ_LIFE_INCOME, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::AdjLifeInc, 0, IDC_LV_RRIF );
   //P0186486_FN03 - RRIF Annuities
   AddControl( CTRL_EDIT, IDC_EDT_EXTERNAL_ASSETS, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::ExternalAssets, 0, IDC_LV_RRIF );  
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_EXTERNAL_ASSETS) )->SetAllowedChars(I_("0123456789.")); 

   //AddControl( CTRL_STATIC, IDC_TXT_REF_TEMP_INCOME, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
   //   ifds::FedRate, 0, IDC_LV_RRIF );
   //AddControl( CTRL_STATIC, IDC_TXT_ADJ_LIFE_INCOME, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
   //   ifds::ProvRate, 0, IDC_LV_RRIF );
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_ACCOUNT_TO) )->SetAllowedChars(I_("0123456789"));
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_PREYR_PERCENT) )->SetAllowedChars(I_("0123456789."));
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_PREYR_PERCENT) )->AllowNonnegativeDecimalNumbers (3,4);
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_UNUSED_MAX) )->SetAllowedChars(I_("0123456789.-"));
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_DAYS_OF_MONTH) )->SetAllowedChars(I_("0123456789,"));
   

   // electronic type, bank fields
   AddControl( CTRL_EDIT, IDC_TXT_INST_NAME_VAL, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::InstName, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_TXT_INST_CODE_VAL, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::InstCode, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_TXT_TRANSIT_NO_VAL, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::TransitNo, 0, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_TXT_BANK_ACCT_NUM_VAL, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::BankAcctNum, 0, IDC_LV_RRIF );
   // original plan deff
   AddControl( CTRL_DATE, IDC_DTP_ORG_PLAN_DEFF, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
   ifds::OrigPlanDeff, 0, IDC_LV_RRIF );

   //P0186486_FN15_The Source of Funds
   AddControl( CTRL_COMBO, IDC_CMB_RIFF_FUND_SRC, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RRIFSrcOfFund, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_WITH_BLANK, IDC_LV_RRIF );
   AddControl( CTRL_EDIT, IDC_EDT_RIFF_ACCT_SRC, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RRIFSrcOfAcct, 0, IDC_LV_RRIF );      
   //--
   
   //user permissions and other security checks
   SetUserAccesFunctionCode(UAF::RIF_LIF_LRIF_INFO);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_RRIF);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_COPY, IDC_LV_RRIF);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_RRIF);

   //load the controls with data
   CWaitCursor wait;

   addStaticControls ();
   registerTabControls (true);
   hideAllControlsOnMiscTab();

   DString strTaxType;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, strTaxType );
   strTaxType.strip();

   CString cstrPaymnt;
   cstrPaymnt.LoadString(TXT_PAYMENT);
   DString strGrpPaymentCaption = strTaxType + DString(cstrPaymnt);
   GetDlgItem( IDC_GRP_RIFF_PAYMENT )->SetWindowText( strGrpPaymentCaption.c_str() );

   SetMessageStatusBar( TXT_RRIF_INFO_RETRIEVING );
   doRefresh( this, NULL_STRING );
   SetMessageStatusBar( NULL_STRING );
   GetDlgItem( IDC_BTN_MORE )->EnableWindow(getParent()->doMoreRecordsExist(this, BF::NullContainerId));

   displayScheduleFields();

   CString cstrRRIFGeneralInfoPaymentPageName;
   cstrRRIFGeneralInfoPaymentPageName.LoadString ( TXT_TAB_RRIF_INFO_GENERAL_PAYMENT );
   DString strRRIFGeneralInfoPaymentPageName = cstrRRIFGeneralInfoPaymentPageName;

   ShowTabCtrl ( IDC_TAB_RRIF_INFO, true );
   LoadTabControl ( IDC_TAB_RRIF_INFO );
   tabSelectionChanged( IDC_TAB_RRIF_INFO , strRRIFGeneralInfoPaymentPageName );

}

//******************************************************************************
bool RRIF_LIF_LRIF_InfoDlg::doRefresh(GenericInterface * rpGICaller, 
                                      const I_CHAR * szOriginalCommand)
{
   LoadListControl(IDC_LV_RRIF);

   DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_RRIF_INFO);
   if (pTabCtrl != NULL)
   {
      CString cstrCheckPageName, cstrPageName;
      TCITEM tcItem;
      wchar_t buffer[256] = {0};
      tcItem.pszText = buffer;
      tcItem.cchTextMax = 256;
      tcItem.mask = TCIF_TEXT;

      int iPagePos = pTabCtrl->GetCurSel();
      pTabCtrl->GetItem(iPagePos, &tcItem);

      cstrPageName = tcItem.pszText;
      cstrCheckPageName.LoadString( TXT_TAB_RRIF_INFO_GENERAL_PAYMENT );

      if( cstrCheckPageName == cstrPageName )
      {
         hideControlsForGeneralInfoPaymentTab( false );
         hideControlsForMiscInfoTab( true );
      }
   }

   return true;
}

//******************************************************************************
bool RRIF_LIF_LRIF_InfoDlg::GetDataForControl(UINT controlID,  
   DString &strValueOut, bool bFormatted, int index) const
{
   DString  str;

   bool bReturn = false;
   switch( controlID )
   {
      case IDC_TXT_PAY_TERM:
      {
         DString dstrPayTerm, dstrPayTermDesc;
      
         getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::PayTerm, 
            dstrPayTerm, false);
         dstrPayTerm.strip();
         getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::PayTermDesc, 
            dstrPayTermDesc,false);
         dstrPayTermDesc.strip();
         if (dstrPayTermDesc.empty())
         {
            CString cstrTemp;
            
            cstrTemp.LoadString(TXT_YEARS);
            dstrPayTermDesc = cstrTemp;
         }
         strValueOut = dstrPayTerm + I_(" ") + dstrPayTermDesc;
         bReturn = true;

         break;
      }

     case IDC_TXT_TRANSIT_NO_VAL:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
                                     ifds::BankType, 
                                     dstrBankIDType, 
                                     false
                                   );
            if ( FinancialInstitution::getBankTransitNumInfo ( dstrBankIDType, 
                                                               nMaxLength, 
                                                               bIsAllDigits, 
                                                               nAllMaxLength
                                                             )
               )
            {
               if (bIsAllDigits)
               {
                  getParent ()->getField ( this, 
                                           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
                                           ifds::TransitNo, 
                                           strValueOut, 
                                           false
                                         );
                  strValueOut.padLeft (nMaxLength, I_('0'));
                  bReturn = true;
               }
            }
            break;
         }
 
      case IDC_TXT_INST_CODE_VAL:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
                                     ifds::BankType, 
                                     dstrBankIDType, 
                                     false
                                   );

            if (FinancialInstitution::getBankIdNumInfo ( dstrBankIDType, 
                                                         nMaxLength, 
                                                         bIsAllDigits, 
                                                         nAllMaxLength
                                                        )
               )
            {
               if (bIsAllDigits)
               {
                  getParent ()->getField ( this, 
                                           IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
                                           ifds::InstCode, 
                                           strValueOut, 
                                           false
                                         );
                  strValueOut.padLeft (nMaxLength, I_('0'));
                  bReturn = true;
               }
            }
            break;
         }

      default:
         break;
   }
   return bReturn;
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnAddress() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAddress" ) );

   CWaitCursor wait;
   E_COMMANDRETURN eRtn;
   bool bModal = true;   // Default to model
   try
   {
      DString dstr;

      getParent()->getField(this, ifds::AccountNum, dstr);
      dstr.strip().stripLeading(I_CHAR( '0' ));
      setParameter( ACCOUNT_NUM, dstr );
      getParent()->getField( this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::AddrCode, 
                             dstr, false );
      dstr.strip();
      setParameter(ADDRESS_CODE, dstr);
      eRtn = getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_ADDRESSES, 
                                                         PROC_SUPPORT);
      if( eRtn == CMD_OK )
      {
         getParameter(ADDRESS_CODE, dstr);
         getParent()->setField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
            ifds::AddrCode, I_(""), true);
         getParent()->setField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
            ifds::AddrCode, dstr, true);
         LoadControl(IDC_EDT_ADDR_CODE);
         LoadControl( IDC_EDT_ADDRESS );
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

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnAllocation() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAllocation" ) );

   CWaitCursor wait;
   E_COMMANDRETURN eRtn;
   try
   {
      DString dstr;
      getParent()->getField( this, ifds::AccountNum, dstr );
      dstr.strip().stripLeading( I_CHAR( '0' ) );
      setParameter( ACCOUNT_NUM, dstr );
      setParameter( ALLOCATIONSPROC::ALLOCATION_TYPE, ALLOCATIONSPROC::RRIF_LIF_LRIF_ONE_TIME );

      const DString* dstrCurrKey = &(getParent()->getCurrentListItemKey( this, 
                                                                         IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST ) );

      setParameter( I_( "CurrentKey" ), *dstrCurrKey);

      eRtn = getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_FROM_TO_ALLOCATION,
                        PROC_SUPPORT);
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               LoadListControl( IDC_LV_RRIF_ALLOC );
               DString dstrPayType;
               getParent()->getField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,ifds::RIFPayType,dstrPayType,false);
               dstrPayType.strip().upperCase();
               if( dstrPayType ==  I_("T") )
               {
                  LoadListControl( IDC_LV_TO_ALLOC );
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
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnBank() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBank" ) );

   CWaitCursor wait;
   E_COMMANDRETURN eRtn;

   try
   {
      DString dstrAccountNum;

      getParent()->getField(this, ifds::AccountNum, dstrAccountNum);
      dstrAccountNum.strip().stripLeading(I_CHAR( '0' ));
      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);

      const DString& rKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST);

      setParameter(MFCAN_IP_PARAM::LIST_KEY, rKey);
      setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::RRIF);
      eRtn = invokeCommand(getParent(), CMD_BPROC_BANK_INSTRUCTIONS, 
         PROC_SUPPORT, true, NULL);

      if (eRtn == IDOK)
      {
         LoadControl(IDC_TXT_INST_NAME_VAL);
         LoadControl(IDC_TXT_INST_CODE_VAL);
         LoadControl(IDC_TXT_TRANSIT_NO_VAL);
         LoadControl(IDC_TXT_BANK_ACCT_NUM_VAL);
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

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnMinMax() 
{
   // TODO: Add your control notification handler code here
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBank" ) );

   CWaitCursor wait;
   E_COMMANDRETURN eRtn;
   bool bModal = true;   // should be model
   try
   {
      DString dstrAccountNum, dstrTaxType;
      getParent()->getField( this,IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum );
      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
      setParameter( MINMAX::ACCOUNT_NUMBER, dstrAccountNum );

      getParent()->getField( this,IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, dstrTaxType );
      dstrTaxType.strip();
      setParameter( MINMAX::TAX_TYPE, dstrTaxType);

      eRtn = invokeCommand( this, CMD_BPROC_MINMAXINFO, PROC_NO_TYPE, bModal, NULL );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }

}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnAdd() 
{
   AddToListControl( IDC_LV_RRIF );
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnDelete() 
{
   DeleteFromListControl( IDC_LV_RRIF );
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnReset() 
{
   ResetListItem(IDC_LV_RRIF);
   m_ckbActiveOnly.SetCheck (0);//added for CHG0041174
   OnChkActiveOnly ();//added for CHG0041174
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnAddCopy() 
{
   DString dstrOrgKey = GetList(IDC_LV_RRIF)->GetCurrentKey();

   AddToListControl( IDC_LV_RRIF );

   DString dstrDestKey = GetList(IDC_LV_RRIF)->GetCurrentKey();
   
   getParent()->setField(this, BF::NullContainerId, 
      RRIF_LIF_LRIF::ORG_KEY, dstrOrgKey);
   getParent()->setField(this, BF::NullContainerId, 
      RRIF_LIF_LRIF::DEST_KEY, dstrDestKey);
   RefreshListItem( IDC_LV_RRIF );
   LoadListControl( IDC_LV_RRIF_ALLOC );
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, ONBTNMORE );

   CWaitCursor wait;

   SetMessageStatusBar(TXT_RRIF_INFO_RETRIEVING);
   const DString *pCurKey =  &(getParent()->getCurrentListItemKey(this, 
      IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST) );
   if( getParent()->performSearch( this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
         SEARCH_NEXT_BLOCK ) <= WARNING	)
   {
      LoadListControl( IDC_LV_RRIF );
      if( *pCurKey != NULL_STRING )
      {
         GetList( IDC_LV_RRIF )->SetSelection( pCurKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow(getParent()->doMoreRecordsExist(this, 
      BF::NullContainerId));
   getParent()->setCurrentListItem(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      *pCurKey);
   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnBtnCalculate() 
{
   getParent()->send( this,I_( "CallView130" ) );
   LoadListControl( IDC_LV_RRIF_ALLOC );
}

//******************************************************************************
BOOL RRIF_LIF_LRIF_InfoDlg::PreTranslateMessage( MSG *pMsg ) 
{
  
   if (pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && 
         !IsSelectedCtrlUpdateable())
      return(TRUE);
   if (pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4)
   {
      if (GetFocus() == GetDlgItem( IDC_EDT_ACCOUNT_TO ))
      {
         PostMessage( WM_LAUNCH_IDENT_ACC );
      }
   }
   
   BOOL isTranslated = FALSE;

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
// show or hide address bank part
// show address if bAddressBank = true
// otherwise show Bank
//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::ShowAddressBank(bool bAddressBank)
{
   DString dstrPayType;
   getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RIFPayType, dstrPayType,false );

   int iShowBank = dstrPayType == I_("E") ? SW_SHOW : SW_HIDE;
   int iShowAddress = ( dstrPayType != I_("E") &&  dstrPayType != I_("T") ) ? SW_SHOW : SW_HIDE;
   int iShowAccountTo = dstrPayType == I_("T") ? SW_SHOW : SW_HIDE;


   GetDlgItem (IDC_TXT_INST_NAME)->ShowWindow (iShowBank);
   GetDlgItem (IDC_TXT_INST_NAME_VAL)->ShowWindow (iShowBank);
   GetDlgItem (IDC_BTN_BANK)->ShowWindow (iShowBank);
   GetDlgItem (IDC_TXT_INST_CODE)->ShowWindow (iShowBank);
   GetDlgItem (IDC_TXT_INST_CODE_VAL)->ShowWindow (iShowBank);
   GetDlgItem (IDC_TXT_TRANSIT_NO)->ShowWindow (iShowBank);
   GetDlgItem (IDC_TXT_TRANSIT_NO_VAL)->ShowWindow (iShowBank);
   GetDlgItem (IDC_TXT_BANK_ACCT_NUM)->ShowWindow (iShowBank);
   GetDlgItem (IDC_TXT_BANK_ACCT_NUM_VAL)->ShowWindow (iShowBank);
   dynamic_cast<CEdit *>(GetDlgItem(IDC_TXT_INST_NAME_VAL))->SetReadOnly(true);
   dynamic_cast<CEdit *>(GetDlgItem(IDC_TXT_INST_CODE_VAL))->SetReadOnly(true);
   dynamic_cast<CEdit *>(GetDlgItem(IDC_TXT_TRANSIT_NO_VAL))->SetReadOnly(true);
   dynamic_cast<CEdit *>(GetDlgItem(IDC_TXT_BANK_ACCT_NUM_VAL))->SetReadOnly(true);
   GetDlgItem (IDC_TXT_ADDR_CODE)->ShowWindow (iShowAddress);
   GetDlgItem (IDC_EDT_ADDR_CODE)->ShowWindow (iShowAddress);
   GetDlgItem (IDC_EDT_ADDRESS)->ShowWindow (iShowAddress);
   GetDlgItem (IDC_EDT_ADDRESS)->EnableWindow(false);  
   GetDlgItem (IDC_BTN_ADDRESS)->ShowWindow (iShowAddress);
   ConnectControlToData(IDC_EDT_ACCOUNT_TO, dstrPayType == I_("T"));
   GetDlgItem (IDC_TXT_ACCOUNT_TO)->ShowWindow (iShowAccountTo);
   GetDlgItem (IDC_EDT_ACCOUNT_TO)->ShowWindow (iShowAccountTo);
   GetDlgItem (IDC_LV_TO_ALLOC)->ShowWindow (iShowAccountTo);
}
//******************************************************************************
// yingbao
void  RRIF_LIF_LRIF_InfoDlg::ControlUpdated(
   UINT controlID, const DString &strValue )
{
   switch( controlID )
   {
      case IDC_CMB_PAY_TYPE:
         {
            bool _bAddress = strValue != I_( "E" );
            if ( m_iCurrentPage == RRIF_INFO_CONTROLS::MISC )
            {
               ShowAddressBank(_bAddress);
               if( strValue == I_( "T" ) )
               {
                  (CWnd* )( GetDlgItem(IDC_EDT_ACCOUNT_TO ) )->SetFocus();
               }
            }

            bool bConnect = strValue == I_("T")? true:false;
            //ConnectListToData( IDC_LV_TO_ALLOC,bConnect,true );
            ConnectListToData( IDC_LV_TO_ALLOC,bConnect, false );
            if(bConnect )
            {
               LoadListControl( IDC_LV_TO_ALLOC );
            }
         }
         break;

      case IDC_EDT_AMOUNT:
         {
            LoadListControl( IDC_LV_RRIF_ALLOC );
            DString dstrPayType;
            getParent()->getField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::RIFPayType, dstrPayType, false);
            dstrPayType.strip().upperCase();
            if( dstrPayType == I_( "T" ) )
            {
               LoadListControl( IDC_LV_TO_ALLOC );
            }

            break;
         }
      case IDC_CMB_PAY_OPTION:
         {
            if ( m_iCurrentPage == RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT )
            {
               DisplayPayOptionRelate();
            }
            break;
         }
      case IDC_CMB_OVERR_UNUSED_MAX:
         {
            LoadControl( IDC_EDT_UNUSED_MAX );
            LoadControl( IDC_EDT_MAX_AMT_YR );
            break;
         }
      case IDC_EDT_UNUSED_MAX:
         {
            LoadControl( IDC_EDT_MAX_AMT_YR );
            break;
         }
      case IDC_EDT_MAX_AMT_YR:
         {
            LoadControl( IDC_EDT_MAX_AMT_YR );
            break;
         }
      case IDC_CMB_FREQUENCY:
      {
         if ( m_iCurrentPage == RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT )
         {
            displayScheduleFields();
         }
         break;
      }
      case IDC_CMB_TAX_ON_MIN :
      case IDC_CMB_SUPP_FED_TAX :
      case IDC_CMB_SUPP_PROV_TAX :
      {
         bool bEnable = hasUpdatePermission(UAF::RIF_LIF_LRIF_TAX_UPDATE) &&
                        hasUpdatePermission(UAF::RIF_LIF_LRIF_FIELD_INFO);
         GetControl(IDC_CMB_FED_RATE_PUD)->Enable(bEnable);
         GetControl(IDC_CMB_PROV_RATE_PUD)->Enable(bEnable);
         GetControl(IDC_EDT_FED_RATE)->Enable(bEnable);
         GetControl(IDC_EDT_PROV_RATE)->Enable(bEnable);
        
         break;
      }
      case IDC_DTP_STOP_DATE:
      case IDC_DTP_EFF_DATE :
      {
         if ( m_iCurrentPage == RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT )
         {
            hideControlsForGeneralInfoPaymentTab( false );
            hideControlsForMiscInfoTab( true );
         }
         else
         {
            hideControlsForGeneralInfoPaymentTab( true );
            hideControlsForMiscInfoTab( false );
         }
         break;
      }
      default:
         break;
   }
}

//***************************************************************************
//yingbao
void  RRIF_LIF_LRIF_InfoDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   DString str;
   if( listControlID == IDC_LV_RRIF )
   {
      getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::GoodBad, str, false);
      str.strip();

      enableDateControl((str == YES));

      getParent()->getField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::RIFPayType, str, false);
      bool bConnect = str.strip().upperCase() == I_("T")? true:false;
      //ConnectListToData( IDC_LV_TO_ALLOC,bConnect,true );
      ConnectListToData( IDC_LV_TO_ALLOC,bConnect,false );

      double dFedRate = 0, dProvRate = 0;
      double dRefTempInc = 0, dAdjLifeInc = 0;
      DString strFedRate, strProvRate;
      DString strRefTempInc, strAdjLifeInc;

      getParent()->getField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::RefTempInc,strRefTempInc, false);
      getParent()->getField(this,IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::AdjLifeInc,strAdjLifeInc, false);

      dRefTempInc = DSTCommonFunctions::convertToDouble(strRefTempInc);		
      dAdjLifeInc = DSTCommonFunctions::convertToDouble(strAdjLifeInc);

      // show window if the value is not zero, hide it otherwise

      bool bShow = (fabs(dRefTempInc - 0.0)>0.00000001 || fabs(dAdjLifeInc - 0.0)>0.00000001) && 
                   ( m_iCurrentPage == RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );

      GetDlgItem(IDC_TXT_REF_TEMP_INCOME)->ShowWindow(bShow);  
      GetDlgItem(IDC_TXT_REF_TEMP_INCOME_LBL)->ShowWindow(bShow);  
      GetDlgItem(IDC_TXT_ADJ_LIFE_INCOME)->ShowWindow(bShow);
      GetDlgItem(IDC_TXT_ADJ_LIFE_INCOME_LBL)->ShowWindow(bShow);
      //P0186486_FN03 - RRIF Annuities
      GetDlgItem(IDC_EDT_EXTERNAL_ASSETS)->ShowWindow(bShow);
      GetDlgItem(IDC_TXT_EXTERNAL_ASSETS_LBL)->ShowWindow(bShow);

      if( m_iCurrentPage == RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT )
      {
         hideControlsForMiscInfoTab( true );
         hideControlsForGeneralInfoPaymentTab( false );
      }
      else
      {
         hideControlsForGeneralInfoPaymentTab( true );
         hideControlsForMiscInfoTab( false );
      }
   }

}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::displayScheduleFields() 
{
   GetDlgItem( IDC_LBL_UP_MONTHLY )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_LBL_MONTH_IND )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_EDT_MONTHLY)->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_LBL_END_OF_MONTH )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_CMB_END_OF_MONTH )->ShowWindow( SW_HIDE );

   GetDlgItem( IDC_LBL_DAY_OF_WEEK )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_CMB_DAY_OF_WEEK )->ShowWindow( SW_HIDE );

   GetDlgItem( IDC_LBL_DAYS_OF_MONTH )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_EDT_DAYS_OF_MONTH )->ShowWindow( SW_HIDE );

   DString str;
   getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::Frequency, str, false);
   str.strip();

   if ( str == I_("1") || str == I_("2") ) 
   {
      GetDlgItem( IDC_LBL_DAY_OF_WEEK )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_CMB_DAY_OF_WEEK )->ShowWindow( SW_SHOW );
   } 
   else if ( str == I_("4") ) 
   {
      GetDlgItem( IDC_LBL_DAYS_OF_MONTH )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_EDT_DAYS_OF_MONTH )->ShowWindow( SW_SHOW );
   } 
   else if ( str == I_("3")  || 
             str == I_("5")  || 
             str == I_("6")  || 
             str == I_("7")  || 
             str == I_("8") ) 
   {
      GetDlgItem( IDC_LBL_UP_MONTHLY )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_LBL_MONTH_IND )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_EDT_MONTHLY)->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_LBL_END_OF_MONTH )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_CMB_END_OF_MONTH )->ShowWindow( SW_SHOW );
   }
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnDestroy() 
{
   BaseMainDlg::OnDestroy();

   if( m_pFont )
   {
      m_pFont->DeleteObject();
      delete m_pFont;
   }
}

//*******************************************************************************
bool RRIF_LIF_LRIF_InfoDlg::GetOverrideItemString(long lSubstituteId, 
   const DString &ColumnKey, DString &strOut)
{
   DString str;  
   bool bOverride = false;

   if( lSubstituteId == ifds::LV_RRIF_Heading.getId() )
   {
      if (ColumnKey == GOODBAD)
      {
         getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::GoodBad, str, false);
         str.strip();
         if( str == I_("Y") ) 
         {
            strOut = I_("Good");
         }
         else 
         {
            strOut = I_("Bad");
         }
         bOverride = true;
      }
      else if (ColumnKey == AMOUNT)
      {
         getParent()->getField( this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::RRIFAmount, strOut,true );
         strOut.strip();
         bOverride = true;
      }
      else if( ColumnKey == MAND_PAYMENT )
      {
      }
   }
   return bOverride;
}

//*******************************************************************************
void  RRIF_LIF_LRIF_InfoDlg::enableDateControl(bool bEnable)
{
   if ( m_iCurrentPage == RRIF_INFO_CONTROLS::MISC )
   {
      dynamic_cast<CWnd*>(GetDlgItem( IDC_BTN_ADDRESS) )->EnableWindow(bEnable);
      dynamic_cast<CWnd*>(GetDlgItem( IDC_BTN_BANK) )->EnableWindow(bEnable);
   }
   else
   {
      GetControl(IDC_DTP_EFF_DATE)->Enable(bEnable);
      GetControl(IDC_DTP_STOP_DATE)->Enable(bEnable);
      GetControl(IDC_DTP_SPOUSE_BIRTH)->Enable(bEnable);
   }

   dynamic_cast<CWnd*>(GetDlgItem( IDC_BTN_CALCULATE) )->EnableWindow(bEnable);
}

//********************************************************************************
bool RRIF_LIF_LRIF_InfoDlg::doDisablePermCheckButton(UINT nID)
{
   if(nID == IDC_BTN_ADD_COPY)
   {
      DString str;

      getParent()->getField( this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
         ifds::GoodBad, str, false );
      return str.strip() != I_("Y");
   }
   return false;
}

//********************************************************************************
void RRIF_LIF_LRIF_InfoDlg::doDisableNonPermButtons()
{
   DString str;
 
   getParent()->getField( this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::GoodBad, str,false );
   str.strip();
   dynamic_cast<CWnd*>(GetDlgItem(IDC_RESET) )->EnableWindow(str == I_("Y"));
}

//*********************************************************************************
void RRIF_LIF_LRIF_InfoDlg::DisplayPayOptionRelate()
{
   DString dstrPayOption;
   getParent()->getField( this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::PayOption, dstrPayOption,false );
   dstrPayOption.strip().upperCase();
   int iShowPercent = dstrPayOption == PERCENT? SW_SHOW:SW_HIDE;
   int iShowIndex = dstrPayOption == PERCENT? SW_HIDE:SW_SHOW;
   GetDlgItem(IDC_TXT_PREYR_PERCENT)->ShowWindow(iShowPercent);
   GetDlgItem(IDC_EDT_PREYR_PERCENT)->ShowWindow(iShowPercent);
   GetDlgItem(IDC_EDT_INDEX_AMOUNT)->ShowWindow(iShowIndex);
   GetDlgItem(IDC_TXT_INDEX_AMOUNT)->ShowWindow(iShowIndex);
}

//*******************************************************************************************
LRESULT RRIF_LIF_LRIF_InfoDlg::OpenIdentifyAccountsDlg( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,CLASSNAME,I_( "OpenIdentifyAccountsDlg" ) );
   //don't allow user to open identify account unless they cleared the account number
   CString strAccNum;
   CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(IDC_EDT_ACCOUNT_TO));
   pEdit->GetWindowText(strAccNum);
   DString dstAcctNum = NULL_STRING;
   dstAcctNum = (LPCTSTR) strAccNum;
   dstAcctNum.strip().stripLeading('0');
   if( dstAcctNum != NULL_STRING  )
      return(0);

   bool bRetVal = false;
   BaseControl *pBC = NULL;
   try
   {
      switch( getParentProcess( )->invokeProcessFromChild( this,CMD_BPROC_IDENT_ACC,PROC_SUPPORT ) )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstAcctNum = NULL_STRING;
               getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstAcctNum );
               dstAcctNum.strip();
               bool success = SetControlText( IDC_EDT_ACCOUNT_TO, dstAcctNum );
               BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_ACCOUNT_TO ));
               if( !success && pBC )
                  pBC->Load();
               if( pBC && pBC->IsToolTipVisible() )
                  pBC->ToggleToolTip();
               clearParameters( );
            }
            break;
         case CMD_CANCEL:
            break;
         default:
            //Displayerror
            ConditionMessageBox(FRAMEBELOW( ), GETHIGHESTSEVERITY( ));
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
void RRIF_LIF_LRIF_InfoDlg::addStaticControls ( void )
{
   AddControl (CTRL_STATIC, IDC_GRP_RIFF_PAYMENT            ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_GRP_RIFF_SCHEDULE           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );

   AddControl (CTRL_STATIC, IDC_STC_RIFF_EFF_DATE           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_MKT_VAL            ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_PAYOUT             ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_STOP_DATE          ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_PYE_VAL            ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_FCT_YRS            ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_QUALIFIED          ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_CALC_MAND_YRS      ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_CALC_MAX_YRS       ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_SPOUSE_BIRTH       ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_BATCH_TRACE_NUMB   ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_TRACE_NUMB         ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_SRC_OF_FUND        ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_PAY_OPTION         ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_TAX_ON_MIN         ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_GROSS_NET_PRE_TAX  ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_GROSS_PAYMENT      ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_NET_Of_TAX         ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_OVERRIDE_AMT_YR    ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_MAND_AMT_YR        ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_OVERR_UNUSED_MAX   ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_UNUSED_MAX_AMT     ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_SUPP_FED_TAX       ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_FED_NR_RATE        ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_FED_TYPE           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_SUPP_PROV_TAX      ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_PROV_RATE          ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_PROV_TYPE          ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_MAND_AMT_PAY       ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_FREQUENCY          ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_LAST_PROCESS_DATE  ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );

   AddControl (CTRL_STATIC, IDC_TXT_MIN_WITH_AGE            ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_TXT_REF_TEMP_INCOME_LBL     ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_TXT_ADJ_LIFE_INCOME_LBL     ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_TXT_INDEX_AMOUNT            ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_TXT_PREYR_PERCENT           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_TXT_MAX_AMT_YR              ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_LBL_END_OF_MONTH            ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_LBL_MONTH_IND               ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_LBL_UP_MONTHLY              ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_LBL_DAYS_OF_MONTH           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   AddControl (CTRL_STATIC, IDC_LBL_DAY_OF_WEEK             ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   //P0186486_FN03 - RRIF Annuities
   AddControl (CTRL_STATIC, IDC_TXT_EXTERNAL_ASSETS_LBL     ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT );
   //--
   AddControl (CTRL_STATIC, IDC_STC_RIFF_DEST               ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_PAY_TYPE           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_TXT_ACCOUNT_TO              ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_TXT_ADDR_CODE               ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_TXT_INST_CODE               ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_TXT_INST_NAME               ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_TXT_BANK_ACCT_NUM           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_TXT_TRANSIT_NO              ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_GRP_RIFF_FRM_ALLOC          ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_BTN_ADDRESS                 ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_BTN_BANK                    ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_STC_ORG_PLAN_DEFF           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
    //P0186486_FN15_The Source of Funds
   AddControl (CTRL_STATIC, IDC_GRP_RIFF_FUND_SRC           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_FUND_SRC           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
   AddControl (CTRL_STATIC, IDC_STC_RIFF_ACCT_SRC           ,CTRLFLAG_GUI_FIELD, RRIF_INFO_CONTROLS::MISC );
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::hideControlsForGeneralInfoPaymentTab( bool bShow )
{
   GetControl ( IDC_STC_RIFF_EFF_DATE           )->Show ( !bShow );
   GetControl ( IDC_DTP_EFF_DATE                )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_MKT_VAL            )->Show ( !bShow );
   GetControl ( IDC_TXT_NOW_PLAN_VALUE          )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_PAYOUT             )->Show ( !bShow );
   GetControl ( IDC_TXT_PAY_TERM                )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_STOP_DATE          )->Show ( !bShow );
   GetControl ( IDC_DTP_STOP_DATE               )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_PYE_VAL            )->Show ( !bShow );
   GetControl ( IDC_TXT_PYE_PLAN_VALUE          )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_FCT_YRS            )->Show ( !bShow );
   GetControl ( IDC_TXT_FACTOR                  )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_QUALIFIED          )->Show ( !bShow );
   GetControl ( IDC_CMB_QUALIFIED               )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_CALC_MAND_YRS      )->Show ( !bShow );
   GetControl ( IDC_TXT_CALC_MAND_YR            )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_CALC_MAX_YRS       )->Show ( !bShow );
   GetControl ( IDC_TXT_CALC_MAX_YR             )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_SPOUSE_BIRTH       )->Show ( !bShow );
   GetControl ( IDC_DTP_SPOUSE_BIRTH            )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_BATCH_TRACE_NUMB   )->Show ( !bShow );
   GetControl ( IDC_TXT_BATCH_NAME              )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_TRACE_NUMB         )->Show ( !bShow );
   GetControl ( IDC_EDT_BATCH_TRACE             )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_SRC_OF_FUND        )->Show ( !bShow );
   GetControl ( IDC_CMB_SRC_OF_FUND             )->Show ( !bShow );
   GetControl ( IDC_TXT_MIN_WITH_AGE            )->Show ( !bShow );
   GetControl ( IDC_EDT_MIN_WITH_AGE            )->Show ( !bShow );
   GetControl ( IDC_TXT_PENSION_JURIS           )->Show ( !bShow );
   GetControl ( IDC_EDT_PENSION_JURIS           )->Show ( !bShow );
   GetControl ( IDC_TXT_REF_TEMP_INCOME_LBL     )->Show ( !bShow );
   GetControl ( IDC_TXT_ADJ_LIFE_INCOME_LBL     )->Show ( !bShow );
   GetControl ( IDC_TXT_REF_TEMP_INCOME         )->Show ( !bShow );
   GetControl ( IDC_TXT_ADJ_LIFE_INCOME         )->Show ( !bShow );
   GetControl ( IDC_GRP_RIFF_PAYMENT            )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_PAY_OPTION         )->Show ( !bShow );
   GetControl ( IDC_CMB_PAY_OPTION              )->Show ( !bShow );
   GetControl ( IDC_TXT_INDEX_AMOUNT            )->Show ( !bShow );
   GetControl ( IDC_TXT_PREYR_PERCENT           )->Show ( !bShow );
   GetControl ( IDC_EDT_PREYR_PERCENT           )->Show ( !bShow );
   GetControl ( IDC_EDT_INDEX_AMOUNT            )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_TAX_ON_MIN         )->Show ( !bShow );
   GetControl ( IDC_CMB_TAX_ON_MIN              )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_GROSS_NET_PRE_TAX  )->Show ( !bShow );
   GetControl ( IDC_CMB_GROSS_OR_NET            )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_GROSS_PAYMENT      )->Show ( !bShow );
   GetControl ( IDC_EDT_AMOUNT                  )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_NET_Of_TAX         )->Show ( !bShow );
   GetControl ( IDC_EDT_NET_AMT                 )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_OVERRIDE_AMT_YR    )->Show ( !bShow );
   GetControl ( IDC_CMB_OVERRIDE_AMT_YR         )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_MAND_AMT_YR        )->Show ( !bShow );
   GetControl ( IDC_EDT_MAND_AMT_YR             )->Show ( !bShow );
   GetControl ( IDC_TXT_MAX_AMT_YR              )->Show ( !bShow );
   GetControl ( IDC_EDT_MAX_AMT_YR              )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_OVERR_UNUSED_MAX   )->Show ( !bShow );
   GetControl ( IDC_CMB_OVERR_UNUSED_MAX        )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_UNUSED_MAX_AMT     )->Show ( !bShow );
   GetControl ( IDC_EDT_UNUSED_MAX              )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_SUPP_FED_TAX       )->Show ( !bShow );
   GetControl ( IDC_CMB_SUPP_FED_TAX            )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_FED_NR_RATE        )->Show ( !bShow );
   GetControl ( IDC_EDT_FED_RATE                )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_FED_TYPE           )->Show ( !bShow );
   GetControl ( IDC_CMB_FED_RATE_PUD            )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_SUPP_PROV_TAX      )->Show ( !bShow );
   GetControl ( IDC_CMB_SUPP_PROV_TAX           )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_PROV_RATE          )->Show ( !bShow );
   GetControl ( IDC_EDT_PROV_RATE               )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_PROV_TYPE          )->Show ( !bShow );
   GetControl ( IDC_CMB_PROV_RATE_PUD           )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_MAND_AMT_PAY       )->Show ( !bShow );
   GetControl ( IDC_TXT_MAND_AMT_PAY            )->Show ( !bShow );
   GetControl ( IDC_GRP_RIFF_SCHEDULE           )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_FREQUENCY          )->Show ( !bShow );
   GetControl ( IDC_CMB_FREQUENCY               )->Show ( !bShow );
   GetControl ( IDC_LBL_END_OF_MONTH            )->Show ( !bShow );
   GetControl ( IDC_CMB_END_OF_MONTH            )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_LAST_PROCESS_DATE  )->Show ( !bShow );
   GetControl ( IDC_TXT_LAST_PROCESS_DATE       )->Show ( !bShow );
   GetControl ( IDC_LBL_MONTH_IND               )->Show ( !bShow );
   GetControl ( IDC_LBL_UP_MONTHLY              )->Show ( !bShow );
   GetControl ( IDC_EDT_MONTHLY                 )->Show ( !bShow );
   GetControl ( IDC_EDT_DAYS_OF_MONTH           )->Show ( !bShow );
   GetControl ( IDC_LBL_DAYS_OF_MONTH           )->Show ( !bShow );
   GetControl ( IDC_LBL_DAY_OF_WEEK             )->Show ( !bShow );
   GetControl ( IDC_CMB_DAY_OF_WEEK             )->Show ( !bShow );
   //P0186486_FN03 - RRIF Annuities
   GetControl ( IDC_TXT_EXTERNAL_ASSETS_LBL     )->Show ( !bShow );
   GetControl ( IDC_EDT_EXTERNAL_ASSETS         )->Show ( !bShow );

   // check payoption related
   DString dstrPayOption;
   getParent()->getField( this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::PayOption, dstrPayOption,false );
   dstrPayOption.strip().upperCase();

   GetControl ( IDC_TXT_PREYR_PERCENT          )->Show( false );
   GetControl ( IDC_EDT_PREYR_PERCENT          )->Show( false );
   GetControl ( IDC_EDT_INDEX_AMOUNT           )->Show( false );
   GetControl ( IDC_TXT_INDEX_AMOUNT           )->Show( false );

   if ( dstrPayOption == PERCENT )
   {
      GetControl(IDC_TXT_PREYR_PERCENT)->Show(!bShow);
      GetControl(IDC_EDT_PREYR_PERCENT)->Show(!bShow);
   }
   else
   {
      GetControl(IDC_EDT_INDEX_AMOUNT)->Show(!bShow);
      GetControl(IDC_TXT_INDEX_AMOUNT)->Show(!bShow);
   }
   
   // schedule related
   GetControl ( IDC_LBL_UP_MONTHLY              )->Show( false );
   GetControl ( IDC_LBL_MONTH_IND               )->Show( false );
   GetControl ( IDC_EDT_MONTHLY                 )->Show( false );
   GetControl ( IDC_LBL_END_OF_MONTH            )->Show( false );
   GetControl ( IDC_CMB_END_OF_MONTH            )->Show( false );

   GetControl ( IDC_LBL_DAY_OF_WEEK             )->Show( false );
   GetControl ( IDC_CMB_DAY_OF_WEEK             )->Show( false );

   GetControl ( IDC_LBL_DAYS_OF_MONTH           )->Show( false );
   GetControl ( IDC_EDT_DAYS_OF_MONTH           )->Show( false );

   DString str;
   getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::Frequency, str, false);
   str.strip();

   if ( str == I_("1") || str == I_("2") ) 
   {
      GetControl( IDC_LBL_DAY_OF_WEEK )->Show( !bShow );
      GetControl( IDC_CMB_DAY_OF_WEEK )->Show( !bShow );
   } 
   else if ( str == I_("4") ) 
   {
      GetControl( IDC_LBL_DAYS_OF_MONTH )->Show( !bShow );
      GetControl( IDC_EDT_DAYS_OF_MONTH )->Show( !bShow );
   } 
   else if ( str == I_("3")  || 
             str == I_("5")  || 
             str == I_("6")  || 
             str == I_("7")  || 
             str == I_("8") ) 
   {
      GetControl( IDC_LBL_UP_MONTHLY   )->Show( !bShow );
      GetControl( IDC_LBL_MONTH_IND    )->Show( !bShow );
      GetControl( IDC_EDT_MONTHLY      )->Show( !bShow );
      GetControl( IDC_LBL_END_OF_MONTH )->Show( !bShow );
      GetControl( IDC_CMB_END_OF_MONTH )->Show( !bShow );
   }

   DString dstrOrigPlanDeffApplied;
   
   getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, ifds::OrigPlanDeffApplied, dstrOrigPlanDeffApplied, false );
   dstrOrigPlanDeffApplied.strip().upperCase();
   bool bShowOrgPlanDeff = !bShow && m_iCurrentPage && dstrOrigPlanDeffApplied == I_("Y");

   GetControl( IDC_STC_ORG_PLAN_DEFF )->Show( bShowOrgPlanDeff );
   GetControl( IDC_DTP_ORG_PLAN_DEFF )->Show( bShowOrgPlanDeff );
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::hideControlsForMiscInfoTab( bool bShow )
{
   hideAllControlsOnMiscTab();

   GetControl ( IDC_STC_RIFF_DEST          )->Show ( !bShow );
   GetControl ( IDC_GRP_RIFF_FRM_ALLOC     )->Show ( !bShow );
   GetList    ( IDC_LV_RRIF_ALLOC          )->Show ( !bShow );
   
   GetControl ( IDC_STC_RIFF_PAY_TYPE      )->Show ( !bShow );
   GetControl ( IDC_CMB_PAY_TYPE           )->Show ( !bShow );
   //P0186486_FN15_The Source of Funds
   GetControl ( IDC_GRP_RIFF_FUND_SRC      )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_FUND_SRC      )->Show ( !bShow );
   GetControl ( IDC_CMB_RIFF_FUND_SRC      )->Show ( !bShow );
   GetControl ( IDC_STC_RIFF_ACCT_SRC      )->Show ( !bShow );
   GetControl ( IDC_EDT_RIFF_ACCT_SRC      )->Show ( !bShow );

   // address-bank related
   DString dstrPayType;
   getParent()->getField(this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, 
      ifds::RIFPayType, dstrPayType,false );

   if ( dstrPayType == I_("E") ) // bank
   {
      GetControl ( IDC_TXT_INST_NAME         )->Show ( !bShow );
      GetControl ( IDC_TXT_INST_NAME_VAL     )->Show ( !bShow );
      GetControl ( IDC_BTN_BANK              )->Show ( !bShow );
      GetControl ( IDC_TXT_INST_CODE         )->Show ( !bShow );
      GetControl ( IDC_TXT_INST_CODE_VAL     )->Show ( !bShow );
      GetControl ( IDC_TXT_TRANSIT_NO        )->Show ( !bShow );
      GetControl ( IDC_TXT_TRANSIT_NO_VAL    )->Show ( !bShow );
      GetControl ( IDC_TXT_BANK_ACCT_NUM     )->Show ( !bShow );
      GetControl ( IDC_TXT_BANK_ACCT_NUM_VAL )->Show ( !bShow );
   }
   else if ( dstrPayType == I_("T") ) // account to
   {
      GetControl ( IDC_TXT_ACCOUNT_TO        )->Show ( !bShow );
      GetControl ( IDC_EDT_ACCOUNT_TO        )->Show ( !bShow );
      GetList    ( IDC_LV_TO_ALLOC           )->Show ( !bShow );
   }
   else if ( ( dstrPayType != I_("E") ) &&
             ( dstrPayType != I_("T") ) ) // address
   {
      GetControl ( IDC_TXT_ADDR_CODE         )->Show ( !bShow );
      GetControl ( IDC_EDT_ADDR_CODE         )->Show ( !bShow );
      GetControl ( IDC_EDT_ADDRESS           )->Show ( !bShow );
      GetControl ( IDC_BTN_ADDRESS           )->Show ( !bShow );
   }
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::tabSelectionChanged( UINT tabControlID, const DString& strPageName )
{
   if ( tabControlID == IDC_TAB_RRIF_INFO )
   {
      CString cstrRRIFGeneralInfoPaymentPageName;
      CString cstrRRIFMiscInfoPageName;
      
      cstrRRIFGeneralInfoPaymentPageName.LoadString ( TXT_TAB_RRIF_INFO_GENERAL_PAYMENT );
      cstrRRIFMiscInfoPageName.LoadString ( TXT_TAB_RRIF_INFO_MISC );
      
      if ( strPageName.c_str() == cstrRRIFGeneralInfoPaymentPageName )
      {
         m_iCurrentPage = RRIF_INFO_CONTROLS::GENERAL_INFO_PAYMENT;
         hideControlsForMiscInfoTab( true );
         hideControlsForGeneralInfoPaymentTab( false );
      }
      else if ( strPageName.c_str() == cstrRRIFMiscInfoPageName )
      {
         m_iCurrentPage = RRIF_INFO_CONTROLS::MISC;
         hideControlsForGeneralInfoPaymentTab( true );
         hideControlsForMiscInfoTab( false );
      }
      else
      {
         assert(0);
      }
   }
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::registerTabControls (bool bShow)
{
   DSTTabCtrl* pTabCtrl = AddTabControl(CLASSNAME, IDC_TAB_RRIF_INFO, I_("RRIFTab"));

   if (pTabCtrl)
   {
      // general information , payment and schedule
      pTabCtrl->AddTab ( TXT_TAB_RRIF_INFO_GENERAL_PAYMENT );
            
      pTabCtrl->registerControl ( IDC_STC_RIFF_EFF_DATE           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_DTP_EFF_DATE                ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_MKT_VAL            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_NOW_PLAN_VALUE          ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_PAYOUT             ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_PAY_TERM                ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_STOP_DATE          ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_DTP_STOP_DATE               ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_PYE_VAL            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_PYE_PLAN_VALUE          ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_FCT_YRS            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_FACTOR                  ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_QUALIFIED          ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_QUALIFIED               ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_CALC_MAND_YRS      ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_CALC_MAND_YR            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_CALC_MAX_YRS       ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_CALC_MAX_YR             ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_SPOUSE_BIRTH       ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_DTP_SPOUSE_BIRTH            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_BATCH_TRACE_NUMB   ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_BATCH_NAME              ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_TRACE_NUMB         ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_BATCH_TRACE             ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_SRC_OF_FUND        ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_SRC_OF_FUND             ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_MIN_WITH_AGE            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_MIN_WITH_AGE            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_PENSION_JURIS           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_PENSION_JURIS           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_REF_TEMP_INCOME_LBL     ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_ADJ_LIFE_INCOME_LBL     ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_REF_TEMP_INCOME         ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_ADJ_LIFE_INCOME         ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_GRP_RIFF_PAYMENT            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_PAY_OPTION         ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_PAY_OPTION              ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_INDEX_AMOUNT            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_PREYR_PERCENT           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_PREYR_PERCENT           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_INDEX_AMOUNT            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_TAX_ON_MIN         ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_TAX_ON_MIN              ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_GROSS_NET_PRE_TAX  ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_GROSS_OR_NET            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_GROSS_PAYMENT      ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_AMOUNT                  ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_NET_Of_TAX         ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_NET_AMT                 ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_OVERRIDE_AMT_YR    ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_OVERRIDE_AMT_YR         ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_MAND_AMT_YR        ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_MAND_AMT_YR             ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_MAX_AMT_YR              ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_MAX_AMT_YR              ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_OVERR_UNUSED_MAX   ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_OVERR_UNUSED_MAX        ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_UNUSED_MAX_AMT     ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_UNUSED_MAX              ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_SUPP_FED_TAX       ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_SUPP_FED_TAX            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_FED_NR_RATE        ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_FED_RATE                ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_FED_TYPE           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_FED_RATE_PUD            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_SUPP_PROV_TAX      ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_SUPP_PROV_TAX           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_PROV_RATE          ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_PROV_RATE               ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_PROV_TYPE          ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_PROV_RATE_PUD           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_MAND_AMT_PAY       ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_MAND_AMT_PAY            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_GRP_RIFF_SCHEDULE           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_FREQUENCY          ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_FREQUENCY               ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_LBL_END_OF_MONTH            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_END_OF_MONTH            ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_STC_RIFF_LAST_PROCESS_DATE  ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_TXT_LAST_PROCESS_DATE       ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_LBL_MONTH_IND               ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_LBL_UP_MONTHLY              ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_MONTHLY                 ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_EDT_DAYS_OF_MONTH           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_LBL_DAYS_OF_MONTH           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_LBL_DAY_OF_WEEK             ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
      pTabCtrl->registerControl ( IDC_CMB_DAY_OF_WEEK             ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT);
	  pTabCtrl->registerControl ( IDC_STC_ORG_PLAN_DEFF           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT );
      pTabCtrl->registerControl ( IDC_DTP_ORG_PLAN_DEFF           ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT );
      //P0186486_FN03 - RRIF Annuities
       pTabCtrl->registerControl ( IDC_TXT_EXTERNAL_ASSETS_LBL    ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT );
       pTabCtrl->registerControl ( IDC_EDT_EXTERNAL_ASSETS        ,TXT_TAB_RRIF_INFO_GENERAL_PAYMENT );

      // misc
      pTabCtrl->AddTab ( TXT_TAB_RRIF_INFO_MISC );

      pTabCtrl->registerControl (IDC_STC_RIFF_DEST ,        TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_STC_RIFF_PAY_TYPE,     TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_CMB_PAY_TYPE,          TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_ACCOUNT_TO,        TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_EDT_ACCOUNT_TO,        TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_ADDR_CODE,         TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_EDT_ADDR_CODE,         TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_EDT_ADDRESS,           TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_INST_NAME,         TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_INST_NAME_VAL,     TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_BTN_ADDRESS,           TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_INST_CODE,         TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_INST_CODE_VAL,     TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_TRANSIT_NO,        TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_TRANSIT_NO_VAL,    TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_BANK_ACCT_NUM,     TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_TXT_BANK_ACCT_NUM_VAL, TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_BTN_BANK,              TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_GRP_RIFF_FRM_ALLOC,    TXT_TAB_RRIF_INFO_MISC );

      pTabCtrl->registerListControl (IDC_LV_TO_ALLOC,       TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerListControl (IDC_LV_RRIF_ALLOC,     TXT_TAB_RRIF_INFO_MISC );
      
       //P0186486_FN15_The Source of Funds
      pTabCtrl->registerControl (IDC_GRP_RIFF_FUND_SRC,     TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_STC_RIFF_FUND_SRC,     TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_CMB_RIFF_FUND_SRC,     TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_STC_RIFF_ACCT_SRC,     TXT_TAB_RRIF_INFO_MISC );
      pTabCtrl->registerControl (IDC_EDT_RIFF_ACCT_SRC,     TXT_TAB_RRIF_INFO_MISC );
   }
}
//******************************************************************************
bool RRIF_LIF_LRIF_InfoDlg::doDisableControl(UINT nID, bool bIsNew)
{
   switch(nID)
   {
      // check for function 179
      case IDC_CMB_SUPP_PROV_TAX:
      case IDC_CMB_SUPP_FED_TAX:
         return !hasUpdatePermission(UAF::RIF_LIF_LRIF_TAX_UPDATE);
         break;

      //These 4 fields required to check both function 37 and 179 
      case IDC_CMB_FED_RATE_PUD:
      case IDC_CMB_PROV_RATE_PUD:
      case IDC_EDT_FED_RATE:
      case IDC_EDT_PROV_RATE:
         return !hasUpdatePermission(UAF::RIF_LIF_LRIF_TAX_UPDATE) || 
                !hasUpdatePermission(UAF::RIF_LIF_LRIF_FIELD_INFO) ;

      //function 37 only
      //Note : RRIF_LIF_LRIF_Info::setFieldsAsReadOnly also handles field's read-only property
      //if the field is set to read-only at the CBO level, this method will not be called and fields
      //will be read-only.
      case IDC_CMB_OVERRIDE_AMT_YR:
      case IDC_EDT_MAND_AMT_YR:
      case IDC_EDT_MAX_AMT_YR:
      case IDC_DTP_ORG_PLAN_DEFF:
         return !hasUpdatePermission (UAF::RIF_LIF_LRIF_FIELD_INFO);
      default:
         return false;
   }
}

//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::hideAllControlsOnMiscTab(void)
{
   GetDlgItem( IDC_STC_RIFF_DEST         )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_STC_RIFF_PAY_TYPE     )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_CMB_PAY_TYPE          )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_ACCOUNT_TO        )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_EDT_ACCOUNT_TO        )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_LV_TO_ALLOC           )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_ADDR_CODE         )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_EDT_ADDR_CODE         )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_EDT_ADDRESS           )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_INST_NAME         )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_INST_NAME_VAL     )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_BTN_ADDRESS           )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_INST_CODE         )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_INST_CODE_VAL     )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_TRANSIT_NO        )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_TRANSIT_NO_VAL    )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_BANK_ACCT_NUM     )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_TXT_BANK_ACCT_NUM_VAL )->ShowWindow(SW_HIDE);
   GetDlgItem( IDC_BTN_BANK              )->ShowWindow(SW_HIDE);
   //P0186486_FN15_The Source of Funds
   GetDlgItem ( IDC_GRP_RIFF_FUND_SRC )->ShowWindow(SW_HIDE);
   GetDlgItem ( IDC_STC_RIFF_FUND_SRC )->ShowWindow(SW_HIDE);
   GetDlgItem ( IDC_CMB_RIFF_FUND_SRC )->ShowWindow(SW_HIDE);
   GetDlgItem ( IDC_STC_RIFF_ACCT_SRC )->ShowWindow(SW_HIDE);
   GetDlgItem ( IDC_EDT_RIFF_ACCT_SRC )->ShowWindow(SW_HIDE);
}

//Change for CHG0041174 starts
//******************************************************************************
void RRIF_LIF_LRIF_InfoDlg::OnChkActiveOnly()
{
   if (m_ckbActiveOnly.GetCheck() == 1)
   {
      //if on the last RRIF inactive record we need to add a dummy one, since the inactive record(s) will be removed from display,
      //when the active only check box is checked

      DString areAllRRIFRecordsInactive (I_("N"));
      getParent()->getField (this,RRIF_LIF_LRIF::AreAllRRIFRecordsInactive, areAllRRIFRecordsInactive, false);
      if (areAllRRIFRecordsInactive == I_("Y"))
      {
         AddToListControl (IDC_LV_RRIF);
      }
   }
    LoadListControl(IDC_LV_RRIF);
}
//******************************************************************************
bool RRIF_LIF_LRIF_InfoDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
	if( lSubstituteId == ifds::LV_RRIF_Heading.getId() )
	{
      return m_ckbActiveOnly.GetCheck() == 1 ? !isCurrentRRIFRecordInactive () : true;
	}
	else if (lSubstituteId == ifds::LV_RRIF_Heading.getId())
	{
		DSTListCtrl *rpList = GetList (IDC_LV_RRIF);

		if (m_ckbActiveOnly.GetCheck() == 1 && rpList && rpList->GetItemCount () == 0)
		{
			return false;
   }
	}
	return true;
}

//******************************************************************************
bool RRIF_LIF_LRIF_InfoDlg::isCurrentRRIFRecordInactive ()
{
	DString str;
	 getParent()->getField( this, IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST,ifds::GoodBad, str, false );
      if( str.strip() == I_("Y"))
		return false;
	  else	
		return true;
}
//Change for CHG0041174 ends
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RRIF_LIF_LRIF_InfoDlg.cpp-arc  $
 * 
 *    Rev 1.91   Apr 27 2012 07:32:08   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.90   Feb 15 2012 04:51:06   panatcha
 * P0186486_FN03 - RRIF Annuities (change to editable field) 
 * 
 *    Rev 1.89   Feb 13 2012 04:30:44   panatcha
 * P0186486_FN03 - RRIF Annuities
 * 
 *    Rev 1.88   Nov 19 2011 01:38:00   wp040143
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.87   Oct 04 2010 16:49:10   popescu
 * PET0168176 FN01 Locked In Product Changes - fixed compile issue.
 * 
 *    Rev 1.86   Oct 04 2010 06:19:16   kitticha
 * PET0168176 FN01 Locked In Product Changes.
 * 
 *    Rev 1.85   Jul 21 2010 08:30:44   kitticha
 * PET0168176 FN01 - Locked In Product.
 * 
 *    Rev 1.84   Apr 26 2010 10:59:34   dchatcha
 * IN# 1941146 - R95/96 - RRIF Payment screen view is incorrect, overlapping with second tab.
 * 
 *    Rev 1.83   Feb 11 2010 17:05:46   dchatcha
 * IN# 1941146 - R95/96 - RRIF Payment screen view is incorrect, overlapping with second tab.
 * 
 *    Rev 1.82   Jul 30 2009 18:45:34   dchatcha
 * IN#1773489 - Possible to override Fed/NR and Prov rate fields using "RIFOverride2".
 * 
 *    Rev 1.81   Apr 23 2009 11:31:24   wutipong
 * PET157825 FN03 MISC RRIF GAPS
 * 
 *    Rev 1.80   20 Jan 2009 15:01:44   kovacsro
 * IN#1554898 - W20090114001 - RRIF - Schedule Set Up problem (restored the LISTFLAG_NOT_AUTO_ADD for allocations)
 * 
 *    Rev 1.79   Nov 24 2008 06:42:40   daechach
 * IN# 1212736 - DESKTOP issues with RRIF/LIF Screen Display - resolution, Introduced Tab control to RRIF screen.
 * 
 *    Rev 1.78   May 07 2008 10:21:00   daechach
 * in#1121661 - Error msg Amount exceed LIF maximum incorrectly.
 * 
 *    Rev 1.77   05 May 2008 14:51:36   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.76   01 May 2008 13:58:28   kovacsro
 * PET2255 FN47 - New Ontario LIF - finalized
 * 
 *    Rev 1.75   24 Apr 2008 13:35:18   kovacsro
 * PET2255 FN47 - New Ontario LIF - added EligExtTrfGainLoss
 * 
 *    Rev 1.74   22 Apr 2008 15:24:20   kovacsro
 * PET2255 FN47 - New Ontario LIF (LIF_GAIN_LOSS UAF)
 * 
 *    Rev 1.73   15 Apr 2008 12:13:40   kovacsro
 * PET2255 FN47 - New Ontario LIF
 *
 *    Rev 1.72   Jan 22 2008 15:38:18   yingz
 * fix incident 1110884 - bank infor display problem
 * 
 *    Rev 1.71   Nov 30 2007 18:44:14   daechach
 * PET5517 FN 92,97 - RRIF Net of Fees,
 * 
 *    Rev 1.70   Aug 10 2007 17:07:20   smithdav
 * PET2360 FN76,91
 * 
 *    Rev 1.69   Dec 06 2006 14:09:22   ZHANGCEL
 * Incident #770827 -- Load control to refresh MaxAnnalAmt
 * 
 *    Rev 1.68   Sep 11 2006 10:18:22   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
 * 
 *    Rev 1.67   Sep 07 2006 17:44:02   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
 * 
 *    Rev 1.66   Sep 06 2006 14:30:46   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
 * 
 *    Rev 1.65   Aug 01 2006 17:43:36   porteanm
 * Incident 666232 - Do not allow more than 2 decimals for RRIFAmount, i.e. rrif-detail.pay-amount.
 * 
 *    Rev 1.64   Sep 15 2005 15:15:02   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.63   Nov 25 2003 10:54:42   YINGBAOL
 * PTS10022269---fix more button issue.
 * 
 *    Rev 1.62   Sep 15 2003 14:15:44   YINGBAOL
 * fix ToAccount empty issue if there is an error
 * 
 *    Rev 1.61   Sep 03 2003 17:16:10   popescu
 * fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
 * 
 *    Rev 1.60   Jun 27 2003 10:16:56   YINGBAOL
 * load to allocation list control when pay type changed to "to account"
 * 
 *    Rev 1.59   Jun 24 2003 09:42:34   YINGBAOL
 * Add logic to load ToAllocation list when user changes amount
 * 
 *    Rev 1.58   Jun 09 2003 11:24:26   YINGBAOL
 * RRIF Allocation enhancement
 * 
 *    Rev 1.57   May 30 2003 09:31:20   popescu
 * rrrif work
 * 
 *    Rev 1.56   May 27 2003 13:14:10   popescu
 * RRIF Banking work
 * 
 *    Rev 1.55   May 23 2003 10:04:36   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.54   Apr 15 2003 12:30:08   sanchez
 * Tickets 10015881/10015338/10015839 sync up with version 1.52.1.0
 * 
 *    Rev 1.53   Mar 21 2003 18:40:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.52   Jan 12 2003 16:36:02   YINGBAOL
 * RRIF Enhancement
 * 
 *    Rev 1.51   Oct 09 2002 23:56:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.50   Oct 08 2002 14:07:36   PURDYECH
 * change back to ifastcsi.hpp
 * 
 *    Rev 1.49   Sep 30 2002 11:01:42   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.48   Sep 05 2002 14:33:56   HERNANDO
 * Cosmetic - Added a space in the title.
 * 
 *    Rev 1.47   Sep 04 2002 15:14:18   KOVACSRO
 * Refresh allocations after calculation is done.
 * 
 *    Rev 1.46   Aug 29 2002 12:57:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.45   Aug 20 2002 09:45:14   KOVACSRO
 * RRIF list control using timer
 * 
 *    Rev 1.44   Aug 06 2002 10:04:48   KOVACSRO
 * Release 48.
 * 
 *    Rev 1.43   Jul 31 2002 10:12:04   YINGBAOL
 * remove permission check for it's already done in CBO
 * 
 *    Rev 1.42   Jul 24 2002 11:44:20   YINGBAOL
 * fix permission check
 * 
 *    Rev 1.41   Jul 08 2002 17:23:36   HERNANDO
 * PTS 10008161 - Added IDC_TXT_PAY_TERM to getDataForControl.  To display 'yrs' using PayTermDesc or Resource string.
 * 
 *    Rev 1.40   22 May 2002 19:16:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.39   27 Mar 2002 20:01:22   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.38   Mar 21 2002 16:27:36   HERNANDO
 * Prevent build warning message.
 * 
 *    Rev 1.37   23 Nov 2001 14:24:46   KOVACSRO
 * perm check changes.
 * 
 *    Rev 1.36   Nov 07 2001 17:58:32   ZHANGCEL
 * Haspermission changes
 * 
 *    Rev 1.35   Nov 07 2001 11:31:28   YINGBAOL
 * change PesionJuris  to static control 
 * 
 *    Rev 1.34   Nov 01 2001 10:06:48   YINGBAOL
 * Change amount to RRIFAmount, capitalize payoption.
 * 
 *    Rev 1.33   Oct 16 2001 11:40:52   YINGBAOL
 * fix title
 * 
 *    Rev 1.32   Oct 01 2001 14:27:08   YINGBAOL
 * set IDC_CMB_SUPP_PROV_TAX as read only from CBO
 * 
 *    Rev 1.31   Sep 28 2001 11:33:46   YINGBAOL
 * small  fix
 * 
 *    Rev 1.30   Sep 27 2001 11:25:22   YINGBAOL
 * Upercase g for good
 * 
 *    Rev 1.29   Jul 24 2001 15:35:42   ZHANGCEL
 * Added new control:  IDC_TXT_MAND_AMT_PAY
 * 
 *    Rev 1.28   Jun 07 2001 11:40:42   YINGBAOL
 * fix refresh issue
 * 
 *    Rev 1.27   19 Apr 2001 17:14:22   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.26   Apr 16 2001 10:52:24   YINGBAOL
 * fix crash and some bugs due to permission check changes
 * 
 *    Rev 1.25   27 Mar 2001 16:54:20   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.24   01 Mar 2001 16:43:40   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.23   Feb 12 2001 15:54:26   JANKAREN
 * Bug fix
 * 
 *    Rev 1.22   Dec 13 2000 14:52:58   KOVACSRO
 * 1. Modified DoListItemChanged.
 * 2.Added Dummy Item logic for perm. check.
 * 
 *    Rev 1.21   Dec 05 2000 17:21:36   KOVACSRO
 * Added new item permission logic.
 * 
 *    Rev 1.20   Dec 01 2000 14:50:38   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.19   Nov 17 2000 10:46:38   YINGBAOL
 * fix some value inconsistent issues
 * 
 *    Rev 1.18   Nov 16 2000 13:58:28   YINGBAOL
 * override mand payment
 * 
 *    Rev 1.17   Oct 20 2000 14:22:26   YINGBAOL
 * Refresh allocation, when amount changed 
 * 
 *    Rev 1.16   Oct 19 2000 15:34:12   YINGBAOL
 * modify lauch minmax dialog
 * 
 *    Rev 1.15   Oct 18 2000 10:22:08   YINGBAOL
 * implement function for more button
 * 
 *    Rev 1.14   Oct 18 2000 10:01:10   YINGBAOL
 * add minmax--- temp
 * 
 *    Rev 1.13   Oct 17 2000 15:12:42   YINGBAOL
 * modify layout issues between RRIF_LIF_LRIF, BankInstruction, address and Allocation screen
 * 
 *    Rev 1.12   Oct 03 2000 17:31:10   YINGBAOL
 * fix launch address and bank screen issue
 * 
 *    Rev 1.11   Oct 03 2000 13:22:06   YINGBAOL
 * syscrosynize RRIF_LIF info and allocation screen
 * 
 *    Rev 1.10   Sep 28 2000 15:05:48   YINGBAOL
 * greate change in order to make it work
 * 
 *    Rev 1.9   Sep 01 2000 14:31:32   ZHANGCEL
 * Added code for Alloction stuffs
 * 
 *    Rev 1.8   Jul 18 2000 13:48:20   PETOLESC
 * Modified title bar for the RRIF dialog.
 * 
 *    Rev 1.7   Jun 28 2000 15:01:04   PETOLESC
 * Added Frequency field, changed logic for view 130 call sequence and a BIG bunch of other changes.
 * 
 *    Rev 1.6   May 19 2000 17:30:14   PETOLESC
 * save work
 * 
 *    Rev 1.5   Mar 30 2000 10:51:08   YINGBAOL
 * change
 * 
 *    Rev 1.4   Mar 21 2000 14:26:08   ZHANGCEL
 * Modify OnBtnMinMax()
 * 
 *    Rev 1.3   Mar 20 2000 17:05:20   YINGBAOL
 * great change
 * 
 *    Rev 1.2   Mar 16 2000 09:45:56   YINGBAOL
 * first version for C2
 * 
 *    Rev 1.0   Feb 15 2000 11:01:20   SMITHDAV
 * Initial revision.
 *
 */
