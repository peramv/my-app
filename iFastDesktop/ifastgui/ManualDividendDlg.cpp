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
//    Copyright 2003 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : ManualDividendDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : ManualDividendDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "manualdividenddlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <uibase\dstlistctrl.h>

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\tradesprocessincludes.h>
#include <ifastbp\addressprocessincludes.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>

// Test
//#include <ifastdataimpl\ifast_fieldids.hpp>


#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MANUAL_DIVIDEND;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DILUTION;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ManualDividendDlg > dlgCreator( CMD_GUI_MANUAL_DIVIDEND );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                  = I_( "ManualDividendDlg" );
   const I_CHAR * const FUNDNUMBER                 = I_( "FUNDNUMBER" );
   const I_CHAR * const REFRESH                    = I_( "REFRESH" );
   const I_CHAR * const FUND_CODE                  = I_( "FundCode" );     // Used for F4-Fund Search Dialog
   const I_CHAR * const FUND_NUMBER                = I_( "FundNumber" );   // Used for F4-Fund Search Dialog
   const I_CHAR * const CLASS_CODE                 = I_( "ClassCode" );    // Used for F4-Fund Search Dialog
   const I_CHAR * const PAYTYPE_CODE_SYSTEM_CHEQUE = I_( "S" );
   const I_CHAR * const PAYTYPE_CODE_SUPPRESS      = I_( "X" );
   const I_CHAR * const PAYTYPE_CODE_MANUAL_CHEQUE = I_( "M" );
   const I_CHAR * const PAYTYPE_CODE_EFT_TO_ACCOUNT= I_( "E" );
   const I_CHAR * const FUND_CODE_CASH             = I_( "CASH" );
   const I_CHAR * const MFR                        = I_( "MFR" );
   const I_CHAR * const FC_GAIN_ALLOC              = I_( "ID62" );
   const I_CHAR * const FC_GAIN_ALLOC_ADJUST       = I_( "ID63" );
   const I_CHAR * const YES                        = I_( "Y" );
   const I_CHAR * const NO                         = I_( "N" );
}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const MANUAL_DIVIDEND;
}

namespace MD_CONTROLS
{
//group of controls with fields part of a manual dividend object
   const UINT MANUAL_DIVIDEND = 1;
   const UINT SHAREHOLDER_ADDRESS = 2;
   const UINT BANK = 3;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const MANUAL_DIVIDEND_ADJ;
   extern CLASS_IMPORT I_CHAR * const CAPITAL_GAIN_INCOME_ADJ;
   extern CLASS_IMPORT I_CHAR * const SUPPLEMENTARY_INCOME_ADJ;
   extern CLASS_IMPORT I_CHAR * const FOREIGN_CAPGAIN_ALLOCATION_ADJ;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE_REBATE_ADJ;
   extern CLASS_IMPORT I_CHAR * const POST_ADJUSTMENT_LIST;
}

namespace ifds
{
//substitution sets
   extern CLASS_IMPORT const BFTextFieldId ManualDividendHeading;
   extern CLASS_IMPORT const BFTextFieldId ESGSettle;
   extern CLASS_IMPORT const BFDecimalFieldId FCFundRate;
   extern CLASS_IMPORT const BFDecimalFieldId FCFundToRate;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
   extern CLASS_IMPORT const BFDataFieldProperties s_FldProp_USDollar;
   extern CLASS_IMPORT const BFTextFieldId UseSpecialDividend;
   extern CLASS_IMPORT const BFTextFieldId NegMoneyMktInt;
   extern CLASS_IMPORT const BFTextFieldId RoundCalcToCents;
   extern CLASS_IMPORT const BFTextFieldId PrcsSpDiv;
   extern CLASS_IMPORT const BFDecimalFieldId NumUnitEligDividends;
   extern CLASS_IMPORT const BFDecimalFieldId NumUnitDividends;
   extern CLASS_IMPORT const BFDecimalFieldId ReinvestmentRate;
   extern CLASS_IMPORT const BFDecimalFieldId DivRate;
   extern CLASS_IMPORT const BFTextFieldId AcctCIDElig;
}


//*****************************************************************************
// Public methods
//*****************************************************************************

ManualDividendDlg::ManualDividendDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ManualDividendDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ManualDividendDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void ManualDividendDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ManualDividendDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(ManualDividendDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ManualDividendDlg)
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DELETE, OnBtnDel )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_BANK_MANUAL_DIV, OnBtnBank )
ON_BN_CLICKED( IDC_BTN_DILUTIONS, OnBtnDilutions)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_MESSAGE( UM_OPENSELECTADDRESSDLG, OpenSelectAddressDlg )
ON_MESSAGE( WM_LAUNCH_IDENT_ACC, OpenIdnAccountsDlg )

//}}AFX_MSG_MAP
ON_EN_KILLFOCUS(IDC_EDT_ACCOUNT, OnEnKillfocusEdtAccount)
ON_EN_KILLFOCUS(IDC_EDT_UNITS_ELIGIBLE_DIV, OnEnKillfocusEdtNumUnitEligDividends)
ON_EN_KILLFOCUS(IDC_EDT_NUMBER_OF_UNITS_DIV, OnEnKillfocusEdtNumUnitDividends)
ON_EN_KILLFOCUS(IDC_EDT_AMOUNT, OnEnKillfocusEdtAmount)
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL ManualDividendDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   DString dstrMarket = DSTCommonFunctions::getMarket();
   m_bFundNumberSupported = dstrMarket == MARKET_IDS::CANADA;

   if (!m_bFundNumberSupported )
   {
      GetDlgItem( IDC_EDT_FUND_NUMBER )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_EDT_FUND_NUM )->ShowWindow( SW_HIDE );
   }
   BaseMainDlg::OnInitDialog();
   return TRUE;
}

//******************************************************************************

//*****************************************************************************
void ManualDividendDlg::OnPostInitDialog()
{
   TRACE_METHOD (CLASSNAME, ONPOSTINITDIALOG);

   SetUserAccesFunctionCode (UAF::MANUAL_DIVIDEND);
   addBtnAddForPermissionCheck (IDC_BTN_ADD, IDC_LV_TRANSACTIONS);
   addBtnDeleteForPermissionCheck (IDC_BTN_DELETE, IDC_LV_TRANSACTIONS);

   // Transaction List
   AddListControl ( CLASSNAME, 
                    IDC_LV_TRANSACTIONS, 
                    I_("MANUALDIVIDENDS"), 
                    ifds::ManualDividendHeading, 
                    IFASTBP_PROC::TRADES_LIST);
//transaction type
   AddControl ( CTRL_COMBO, 
                IDC_CMB_TRANSACTION_TYPE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::TradesTransType, 
                CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                IDC_LV_TRANSACTIONS
   );
   // Account
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ACCOUNT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::AccountNum, 
                CTRLFLAG_DEFAULT, 
                IDC_LV_TRANSACTIONS);
   dynamic_cast<DSTEdit *>(GetControl( IDC_EDT_ACCOUNT ))->SetAllowedChars (I_("0123456789"));
   // Fund Number, Fund Code, Fund Class
   if (m_bFundNumberSupported)
   {
      AddControl ( CTRL_EDIT, 
                   IDC_EDT_FUND_NUMBER, 
                   IFASTBP_PROC::TRADES_LIST, 
                   ifds::FromFundNumber, 
                   CTRLFLAG_DEFAULT, 
                   MD_CONTROLS::MANUAL_DIVIDEND);
   }
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FUND, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::FromFund, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_CLASS, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::FromClass, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // To Fund Number, To Fund Code, To Fund Class
   if (m_bFundNumberSupported)
   {
      AddControl( CTRL_EDIT, 
                  IDC_EDT_FUND_NUM, 
                  IFASTBP_PROC::TRADES_LIST, 
                  ifds::ToFundNumber, 
                  CTRLFLAG_DEFAULT, 
                  MD_CONTROLS::MANUAL_DIVIDEND);
   }
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FUND_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::ToFund, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_CLASS_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::ToClass, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Amount Type
   AddControl ( CTRL_COMBO, 
                IDC_CMB_AMOUNT_TYPE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::AmtType, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Amount
   AddControl ( CTRL_EDIT, 
                IDC_EDT_AMOUNT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::Amount, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   dynamic_cast<DSTEdit *>(GetControl( IDC_EDT_AMOUNT ))->SetAllowedChars( I_("-,.0123456789") );
   // Trans Type
   AddControl ( CTRL_COMBO, 
                IDC_CMB_PAY_TYPE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::TradesPayType, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // MFR Payment
   AddControl ( CTRL_COMBO, 
                IDC_CMB_MFR_PAYMENT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::MFPayment, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Supress Code (Combo) or Address Code (Edit)
   AddControl ( CTRL_COMBO, 
                IDC_CMB_SUPPRESS_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::SuppressCode, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ADDR_CODE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::AddrCode, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Trade Date
   AddControl ( CTRL_DATE, 
                IDC_DTP_TRADE_DATE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::EffectiveDate, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Settlement Date
   AddControl ( CTRL_DATE, 
                IDC_DTP_SETTLE_DATE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::SettleDate, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Transaction Number
   AddControl ( CTRL_STATIC, 
                IDC_TXT_TRANS_NBR, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::TransNum, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Batch Name
   AddControl ( CTRL_STATIC, 
                IDC_TXT_BATCH_NAME, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::BatchName, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Settle Currency
   AddControl ( CTRL_COMBO, 
                IDC_CMB_SETTLE_CURENCY, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::SettleCurrency, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Accountability
   AddControl ( CTRL_COMBO, 
                IDC_CMB_ACCOUNTABILITY, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::Accountable, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);
   // Backdated Reason
   AddControl ( CTRL_COMBO, 
                IDC_CMB_REASON, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::BackDatedReason, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);

   //Dividend Rate
   AddControl ( CTRL_STATIC, 
                IDC_DIV_RATE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::DivRate,
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);

   // Reinvestment Rate
   AddControl ( CTRL_STATIC, 
                IDC_REINVEST_RATE, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::ReinvestmentRate, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);

   //Negative Money Mkt Int
   AddControl ( CTRL_COMBO, 
                IDC_CMB_NEG_MONEY_MKT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::NegMoneyMktInt, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);

   //Round Calc to Cents
   AddControl ( CTRL_COMBO, 
                IDC_CMB_RND_CAL_TO_CENTS, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::RoundCalcToCents, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);

   //Number of Units of Deiv
   AddControl ( CTRL_EDIT, 
                IDC_EDT_NUMBER_OF_UNITS_DIV, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::NumUnitDividends, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);

   //Units Eligible for Div
   AddControl ( CTRL_EDIT, 
                IDC_EDT_UNITS_ELIGIBLE_DIV, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::NumUnitEligDividends, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::MANUAL_DIVIDEND);

   //Special Dividend
   /*AddControl ( CTRL_COMBO, 
                IDC_CMB_SPECIAL_DIV, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::PrcsSpDiv, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                MD_CONTROLS::MANUAL_DIVIDEND);*/

   // Address
   AddControl ( CTRL_EDIT, 
                IDC_SHAREHOLDER_ADDRESS, 
                SHAREHOLDER_ADDRESS, 
                ifds::TradeAddress, 
                CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_LINE_PACK, 
                MD_CONTROLS::SHAREHOLDER_ADDRESS);

   DSTEdit* pEditAddr = dynamic_cast<DSTEdit*> (GetControl (IDC_SHAREHOLDER_ADDRESS));

   pEditAddr->SetMaxCharNum( 40 );
   // Remarks
   AddControl( CTRL_EDIT, 
               IDC_EDT_REMARKS, 
               IFASTBP_PROC::TRADES_LIST, 
               ifds::RemarksLine, 
               CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_WORD_WRAP, 
               MD_CONTROLS::MANUAL_DIVIDEND);
  
   DSTEdit* pEditRemarks = dynamic_cast<DSTEdit*> (GetControl (IDC_EDT_REMARKS));
   pEditRemarks->SetMaxCharNum(50);

   // ESGSettle
   AddControl( CTRL_COMBO, 
               IDC_CMB_ESG_SETTLE, 
               IFASTBP_PROC::TRADES_LIST, 
               ifds::ESGSettle,
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               MD_CONTROLS::MANUAL_DIVIDEND);

   //Bank Name - Bank Group
   AddControl ( CTRL_STATIC, 
                IDC_STATIC_BANK_NAME_TXT, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::InstName, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::BANK);

   //Bank Nbr - Bank Group
   AddControl ( CTRL_STATIC, 
                IDC_STATIC_BANK_NBR, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::BankIdValue, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::BANK);

   //Bank Account Name - Bank Group
   AddControl ( CTRL_STATIC, 
                IDC_STATIC_ACCT_NAME, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::BankAcctName, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::BANK);

   //Bank Account Nbr - Bank Group
   AddControl ( CTRL_STATIC, 
                IDC_STATIC_ACCT_NBR, 
                IFASTBP_PROC::TRADES_LIST, 
                ifds::BankAcctNum, 
                CTRLFLAG_DEFAULT, 
                MD_CONTROLS::BANK);


   // Format Columns
   CListCtrl *pDSTListCtrl = GetList( IDC_LV_TRANSACTIONS );
   if (pDSTListCtrl)
   {
      LVCOLUMN lvcolumn;
      lvcolumn.mask = LVCF_FMT;
      lvcolumn.fmt = LVCFMT_RIGHT;
      BOOL bReturn = pDSTListCtrl->SetColumn( 7, &lvcolumn ); // Amount field - Right Justified
   }
   doRefresh (this, NULL);
}

//************************************************************************
bool ManualDividendDlg::doRefresh ( GenericInterface *rpGICaller, 
                                    const I_CHAR* szOriginalCommand)
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   LoadListControl (IDC_LV_TRANSACTIONS);
   ConnectControlsToData (MD_CONTROLS::MANUAL_DIVIDEND, false);
   ConnectControlsToData (MD_CONTROLS::SHAREHOLDER_ADDRESS, false);
   ConnectControlsToData (MD_CONTROLS::BANK, false);
   return true;
}

//******************************************************************************
bool ManualDividendDlg::doSend ( GenericInterface *rpGICaller,
                                 const I_CHAR *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("doSend"));
   bool bRet = true;

   if (DString (szMessage) == I_("RefreshTradesList"))
   {
      DString selectionKey;

      getParameter (MFCAN_IP_PARAM::LIST_KEY, selectionKey); 
      LoadListControl (IDC_LV_TRANSACTIONS, &selectionKey);
      if (GETHIGHESTSEVERITY () > WARNING)
      {
         // Display error
         ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
         bRet = false;
      }
   }
   else
   {
      bRet = BaseMainDlg::doSend (rpGICaller, szMessage);
   }
   return bRet;
}

//*****************************************************************************
void ManualDividendDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   CWaitCursor wait;
   
   DSTListCtrl *pTransactionsListCtrl = GetList (IDC_LV_TRANSACTIONS);

   if (pTransactionsListCtrl)
   {
      ResetListItem (IDC_LV_TRANSACTIONS);
      pTransactionsListCtrl->setAutoAddFlag (true); //this will set the list NOT to be an auto add list
//setting the flag will actually signal the process to delete the current item 
//and create a new 'light' trade.
      getParent()->setField ( this, 
                              Reset,
                              I_("Y"));
      pTransactionsListCtrl->setAutoAddFlag (false);

      ClearControlValues();
   }
}

//*********************************************************************
void ManualDividendDlg::OnBtnAdd()
{
   TRACE_METHOD (CLASSNAME, I_("OnBtnAdd"));
   
   CWaitCursor wait;
   
   AddToListControl (IDC_LV_TRANSACTIONS);
}

//**********************************************************************
void ManualDividendDlg::OnBtnDel()
{
   TRACE_METHOD (CLASSNAME, I_("OnBtnDel"));
   
   CWaitCursor wait;

   DeleteFromListControl (IDC_LV_TRANSACTIONS);
}

//**********************************************************************
void ManualDividendDlg::ClearControlValues()
{
    GetDlgItem(IDC_EDT_NUMBER_OF_UNITS_DIV)->SetWindowText(NULL_STRING);
    GetDlgItem(IDC_EDT_UNITS_ELIGIBLE_DIV)->SetWindowText(NULL_STRING);
    GetDlgItem(IDC_EDT_FUND_CODE)->SetWindowText(NULL_STRING);
    GetDlgItem(IDC_EDT_CLASS_CODE)->SetWindowText(NULL_STRING);
    GetDlgItem(IDC_EDT_FUND_NUM)->SetWindowText(NULL_STRING);
}

//****************************************************************************** 
void ManualDividendDlg::DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   TRACE_METHOD(CLASSNAME, I_("DoListItemChanged"));

   if (listControlID == IDC_LV_TRANSACTIONS)
   {
       DString isAccountSetAndValid;
       getParent ()->getField(this,
                              ACCOUNT,
                              IsAccountSetAndValid,
                              isAccountSetAndValid,
                              false);

       if (isAccountSetAndValid == I_("N"))
       {
           ClearControlValues();
       }
   }
}

//**********************************************************************
BOOL ManualDividendDlg::PreTranslateMessage(MSG* pMsg) 
{

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
   {
      return( TRUE );
   }
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if ( GetFocus() == GetDlgItem( IDC_EDT_FUND ) || 
           GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) || 
           GetFocus() == GetDlgItem( IDC_EDT_CLASS ) || 
           GetFocus() == GetDlgItem( IDC_EDT_FUND_NUM ) || 
           GetFocus() == GetDlgItem( IDC_EDT_FUND_CODE ) || 
           GetFocus() == GetDlgItem( IDC_EDT_CLASS_CODE ))
      {
         PostMessage (UM_OPENFUNDCLASSLISTDLG);
      }
      else if (GetFocus() == GetDlgItem (IDC_EDT_ADDR_CODE))
      {
         PostMessage(UM_OPENSELECTADDRESSDLG);
      }
      else if (GetFocus() == GetDlgItem (IDC_EDT_ACCOUNT))
      {
         PostMessage (WM_LAUNCH_IDENT_ACC);
      }
      return TRUE;
   }
   return BaseMainDlg::PreTranslateMessage (pMsg);
}  

//**********************************************************************
LRESULT ManualDividendDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      setParameter( FUND_CODE, NULL_STRING );
      setParameter( FUND_NUMBER, NULL_STRING );
      setParameter( CLASS_CODE, NULL_STRING );
      GetFocus()->GetWindowText( cstrValue );
      DString dstrValue( cstrValue );
      switch( GetFocus()->GetDlgCtrlID() )
      {
         case IDC_EDT_FUND:
         case IDC_EDT_FUND_CODE:
            setParameter( FUND_CODE, dstrValue );
            break;    
         case IDC_EDT_FUND_NUMBER:
         case IDC_EDT_FUND_NUM:
            setParameter( FUND_NUMBER, dstrValue );
            break;    
         case IDC_EDT_CLASS:
         case IDC_EDT_CLASS_CODE:
            setParameter( CLASS_CODE, dstrValue );
            break;    
      }

      // Set Account Number
      DString dstrAccountNum;
      getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, dstrAccountNum, false);      
      setParameter( I_("AccountNum"), dstrAccountNum );

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( FUND_CODE, dstrFundCode );
               getParameter ( CLASS_CODE, dstrClassCode );
               getParameter ( FUND_NUMBER, dstrFundNumber );

               if( GetFocus()->GetDlgCtrlID() == IDC_EDT_FUND || GetFocus()->GetDlgCtrlID() == IDC_EDT_FUND_NUMBER || GetFocus()->GetDlgCtrlID() == IDC_EDT_CLASS )
               {
                  getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::FromFund, dstrFundCode );
                  getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::FromClass, dstrClassCode );
                  if( m_bFundNumberSupported ) 
                  {
                     getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::FromFundNumber, dstrFundNumber );
                     LoadControl( IDC_EDT_FUND_NUMBER );
                  }
                  LoadControl( IDC_EDT_FUND );
                  LoadControl( IDC_EDT_CLASS );
               }
               else
               {
                  getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::ToFund, dstrFundCode );
                  getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::ToClass, dstrClassCode );
                  if( m_bFundNumberSupported ) 
                  {
                     getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::ToFundNumber, dstrFundNumber );
                     LoadControl( IDC_EDT_FUND_NUM );
                  }
                  LoadControl( IDC_EDT_FUND_CODE );
                  LoadControl( IDC_EDT_CLASS_CODE );
               }
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

//************************************************************************
LRESULT ManualDividendDlg::OpenSelectAddressDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenSelectAddressDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      DString dstrShrNum;
      

      getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER, ifds::ShrNum, dstrShrNum, false);      
      setParameter( ADDRLIT::SETTLEMENT, I_("YES") );
      dstrShrNum.strip();
      setParameter( ADDRLIT::SHAREHOLDER_NUM, dstrShrNum );

      eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrAddressCode;
               
               getParameter (ADDRLIT::ADDRESS_CODE, dstrAddressCode);
               if( !dstrAddressCode.empty() )
               {
                  getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::AddrCode, dstrAddressCode );
                  LoadControl( IDC_EDT_ADDR_CODE );
               }
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

//************************************************************************
LRESULT ManualDividendDlg::OpenIdnAccountsDlg( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,CLASSNAME,I_( "OpenIdnAccountsDlg" ) );
   try
   {
      switch( getParentProcess( )->invokeProcessFromChild( this, CMD_BPROC_IDENT_ACC, PROC_SUPPORT ) )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstAcctNum( NULL_STRING );
               getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstAcctNum );
               dstAcctNum.strip();
               bool bRetVal = SetControlText( IDC_EDT_ACCOUNT, dstAcctNum );
               BaseControl* pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_ACCOUNT ));
               if( pBC && pBC->IsToolTipVisible() )
               {
                  pBC->ToggleToolTip();
               }
               if( !bRetVal )
               {
                  if( pBC )
                  {
                     if( pBC->IsToolTipVisible() )
                     {
                        pBC->ToggleToolTip();
                     }
                     pBC->Load();
                  }
               }
               clearParameters( );
            }
            break;
         case CMD_CANCEL:
            break;
         default:
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

//**********************************************************************************
void ManualDividendDlg::ControlUpdated ( UINT controlID, 
                                         const DString &dstrValue)
{
   if (controlID == IDC_CMB_PAY_TYPE)
   {
      DisplayPayTypeRelated (dstrValue); // Display Address Code/Suppress Code Controls as user changes Pay Type
   }
   else if (controlID == IDC_CMB_TRANSACTION_TYPE)
   {
      DString transType;

      getParent ()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType,
                             transType, false);

      UpdateControlsByTranstype(transType);
   }
   else if (controlID == IDC_EDT_ACCOUNT)
   {
      DString accountNum,
         isAccountSetAndValid, transType;

      GetControl (IDC_EDT_ACCOUNT)->GetText (accountNum);
      getParent ()->getField ( this,
                               ACCOUNT,
                               IsAccountSetAndValid,
                               isAccountSetAndValid,
                               false);

       getParent ()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType, transType, false);

      //load the account related controls only if the account num is valid
      if ( isAccountSetAndValid == I_("Y") && 
           !accountNum.empty())
      {
         if (GetControl (IDC_EDT_ACCOUNT)->IsEnabled ())
         {
//and load the md controls 
            ConnectControlsToData (MD_CONTROLS::MANUAL_DIVIDEND, true);
            LoadControls (MD_CONTROLS::MANUAL_DIVIDEND);
            ConnectControlsToData (MD_CONTROLS::SHAREHOLDER_ADDRESS, true);
            LoadControls (MD_CONTROLS::SHAREHOLDER_ADDRESS);
            ConnectControlsToData (MD_CONTROLS::BANK, true);
            LoadControls (MD_CONTROLS::BANK);

            UpdateControlsByTranstype(transType);
         }
      }
      else
      {
         ConnectControlsToData (MD_CONTROLS::MANUAL_DIVIDEND, false);
         ConnectControlsToData (MD_CONTROLS::SHAREHOLDER_ADDRESS, false);
         ConnectControlsToData (MD_CONTROLS::BANK, false);
         GetControl (IDC_EDT_ACCOUNT)->LoadErrorState ();
      }
   }
   else if (controlID == IDC_EDT_ADDR_CODE)
   {
      LoadControls (MD_CONTROLS::SHAREHOLDER_ADDRESS); // Refresh address display after changing Address Code
   }
   else if ( controlID == IDC_EDT_FUND_NUMBER   || 
             controlID == IDC_EDT_FUND_NUM      ||
             controlID == IDC_EDT_FUND          || 
             controlID == IDC_EDT_CLASS         ||
             controlID == IDC_EDT_FUND_CODE     || 
             controlID == IDC_EDT_CLASS_CODE )
   {
      GetControl (controlID)->LoadErrorState ();
      if (controlID == IDC_EDT_FUND_CODE)
      {
         DisplayToFundCodeRelated (dstrValue);
      }
   }
   else if( controlID == IDC_CMB_AMOUNT_TYPE ) // changing occur on amount type, 
                                               // but value is not change
   {
      LoadControl ( IDC_EDT_AMOUNT );
   }
   else if( controlID == IDC_EDT_AMOUNT )
   {
      DString dstrTradesTransType,
              dstrAmtType;
      getParent()->getField( this, 
                           IFASTBP_PROC::TRADES_LIST, 
                           ifds::TradesTransType, 
                           dstrTradesTransType, 
                           false);
      getParent()->getField( this, 
                           IFASTBP_PROC::TRADES_LIST, 
                           ifds::AmtType, 
                           dstrAmtType, 
                           false);

      dstrTradesTransType.strip().upperCase();
      if( dstrTradesTransType == FC_GAIN_ALLOC_ADJUST )
      {
         if ( dstrAmtType == I_("D") )
         {
            UpdateAmountTypeDollar();
         }
         else if ( dstrAmtType == I_("U") )
         {
            UpdateAmountTypeUnit();
         }
      }
   }
   else if (controlID == IDC_DTP_TRADE_DATE)
   {
       DString dstrIsDilutionAllowed;
       getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, IsDilutionAllowed, dstrIsDilutionAllowed, false);

       GetDlgItem(IDC_BTN_DILUTIONS)->EnableWindow(dstrIsDilutionAllowed == YES);
   }
}

//**********************************************************************************
void ManualDividendDlg::DisplayPayTypeRelated (const DString& dstrPayType)
{
   DString dstrToFundCode;
   getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::ToFund, dstrToFundCode, false);

   if (dstrToFundCode.stripAll().upperCase() == FUND_CODE_CASH)
   {
      if (dstrPayType == PAYTYPE_CODE_SUPPRESS) // EFT to Account
      {
         LoadControl( IDC_EDT_ADDR_CODE );
         GetDlgItem( IDC_CMB_SUPPRESS_CODE )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_TXT_SUPPRESS_CODE )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_EDT_ADDR_CODE )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STATIC_ADDRESS_CODE )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STATIC_ADDRESS )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_SHAREHOLDER_ADDRESS )->ShowWindow( SW_HIDE );
         GetDlgItem (IDC_TXT_ESG_SETTLE)->ShowWindow (SW_HIDE);
         GetDlgItem (IDC_CMB_ESG_SETTLE) ->ShowWindow (SW_HIDE);

         DisplayBankControls(SW_HIDE);
      }
      else if (dstrPayType == PAYTYPE_CODE_EFT_TO_ACCOUNT)
      {
          GetDlgItem( IDC_CMB_SUPPRESS_CODE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_TXT_SUPPRESS_CODE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_EDT_ADDR_CODE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_STATIC_ADDRESS_CODE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_STATIC_ADDRESS )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_SHAREHOLDER_ADDRESS )->ShowWindow( SW_HIDE );
          GetDlgItem (IDC_TXT_ESG_SETTLE)->ShowWindow (SW_HIDE);
          GetDlgItem (IDC_CMB_ESG_SETTLE) ->ShowWindow (SW_HIDE);

          DisplayBankControls(SW_SHOW);
      }
      else if (dstrPayType == PAYTYPE_CODE_SYSTEM_CHEQUE || dstrPayType == PAYTYPE_CODE_MANUAL_CHEQUE)  // System Generated Cheque
      {
         LoadControl (IDC_CMB_SUPPRESS_CODE);
         GetDlgItem (IDC_CMB_SUPPRESS_CODE)->ShowWindow (SW_HIDE);
         GetDlgItem (IDC_TXT_SUPPRESS_CODE)->ShowWindow (SW_HIDE);
         GetDlgItem (IDC_EDT_ADDR_CODE) ->ShowWindow (SW_SHOW);
         GetDlgItem (IDC_STATIC_ADDRESS_CODE)->ShowWindow (SW_SHOW);
         GetDlgItem (IDC_STATIC_ADDRESS)->ShowWindow (SW_SHOW );
         GetDlgItem (IDC_SHAREHOLDER_ADDRESS)->ShowWindow (SW_SHOW);
         bool bEnableESGSettle = false;
         if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA  ) 
         {
            bEnableESGSettle = true;
         }
         GetDlgItem (IDC_TXT_ESG_SETTLE)->ShowWindow (bEnableESGSettle);
         GetDlgItem (IDC_CMB_ESG_SETTLE) ->ShowWindow (bEnableESGSettle);

         if (dstrPayType == PAYTYPE_CODE_SYSTEM_CHEQUE)
         {
             DString dstrisCASHSettleESGElig;

             getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, isCASHSettleESGElig, dstrisCASHSettleESGElig, false);
             GetDlgItem (IDC_CMB_ESG_SETTLE)->EnableWindow(dstrisCASHSettleESGElig == YES);
         }

         DisplayBankControls(SW_HIDE);
      }
      else if (dstrPayType.empty())
      {
          GetDlgItem( IDC_CMB_SUPPRESS_CODE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_TXT_SUPPRESS_CODE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_EDT_ADDR_CODE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_STATIC_ADDRESS_CODE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_STATIC_ADDRESS )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_SHAREHOLDER_ADDRESS )->ShowWindow( SW_HIDE );
          GetDlgItem (IDC_TXT_ESG_SETTLE)->ShowWindow (SW_HIDE);
          GetDlgItem (IDC_CMB_ESG_SETTLE) ->ShowWindow (SW_HIDE);
          DisplayBankControls(SW_HIDE);
      }
   }
}

//**********************************************************************
void ManualDividendDlg::DisplayToFundCodeRelated( const DString& dstrToFundCode )
{
   DString dstrToFund( dstrToFundCode ), dstrTradesTransType;
   dstrToFund.stripAll().upperCase();

   getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::TradesTransType, dstrTradesTransType, false);

   if( dstrToFund == FUND_CODE_CASH )
   {
      GetDlgItem( IDC_TXT_PAY_TYPE )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_CMB_PAY_TYPE )->ShowWindow( SW_SHOW );

      DString dstrPayType;
      getParent()->getField (this, IFASTBP_PROC::TRADES_LIST, ifds::TradesPayType, dstrPayType, false);
      DisplayPayTypeRelated( dstrPayType );
      
      if (DSTCommonFunctions::codeInList(dstrTradesTransType, TRADETYPE::POST_ADJUSTMENT_LIST))
      {
          GetDlgItem(IDC_REINVEST_RATE)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_EDT_NUMBER_OF_UNITS_DIV)->EnableWindow(FALSE);
      }
   }
   else
   {
      GetDlgItem( IDC_TXT_PAY_TYPE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_PAY_TYPE )->ShowWindow( SW_HIDE );
      GetDlgItem(IDC_TXT_ESG_SETTLE)->ShowWindow( SW_HIDE );
      GetDlgItem(IDC_CMB_ESG_SETTLE)->ShowWindow( SW_HIDE );

      GetDlgItem( IDC_EDT_ADDR_CODE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_STATIC_ADDRESS_CODE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_STATIC_ADDRESS )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_SHAREHOLDER_ADDRESS )->ShowWindow( SW_HIDE );

      GetDlgItem( IDC_CMB_SUPPRESS_CODE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_SUPPRESS_CODE )->ShowWindow( SW_HIDE );

      DisplayBankControls(SW_HIDE);

      if (DSTCommonFunctions::codeInList(dstrTradesTransType, TRADETYPE::POST_ADJUSTMENT_LIST))
      {
          GetDlgItem(IDC_REINVEST_RATE)->ShowWindow(SW_SHOW);
          GetDlgItem(IDC_EDT_NUMBER_OF_UNITS_DIV)->EnableWindow(dstrTradesTransType != TRADETYPE::FOREIGN_CAPGAIN_ALLOCATION_ADJ ? TRUE:FALSE);
      }
   }

}

//**********************************************************************
bool ManualDividendDlg::PreOk()
{
   return AfxMessageBox (TXT_MANUAL_DIV_CONFIRMATION, MB_YESNO) == IDYES;
}

//******************************************************************************
void ManualDividendDlg::OnEnKillfocusEdtAccount()
{
   if (GetControl (IDC_EDT_FUND)-> IsEnabled ())
   {
      if( !m_bFundNumberSupported )
      {
         FocusOnControl (IDC_EDT_FUND);
         GetDlgItem (IDC_EDT_FUND) ->ShowCaret ();
      }
      else
      {
         FocusOnControl (IDC_EDT_FUND_NUMBER);
         GetDlgItem (IDC_EDT_FUND_NUMBER) ->ShowCaret ();
      }
   }
}

//******************************************************************************
void ManualDividendDlg::OnEnKillfocusEdtNumUnitEligDividends()
{
    DString dstrNumUnitEligDividends;
    getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::NumUnitEligDividends, dstrNumUnitEligDividends, false);

    GetControl(IDC_EDT_UNITS_ELIGIBLE_DIV)->SetText(dstrNumUnitEligDividends);
}

//******************************************************************************
void ManualDividendDlg::OnEnKillfocusEdtNumUnitDividends()
{
    DString dstrNumUnitDividends;
    getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::NumUnitDividends, dstrNumUnitDividends, false);

    GetControl(IDC_EDT_NUMBER_OF_UNITS_DIV)->SetText(dstrNumUnitDividends);
}

//******************************************************************************
void ManualDividendDlg::OnEnKillfocusEdtAmount()
{
    DString dstrAmount;
    getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::Amount, dstrAmount, false);

    GetControl(IDC_EDT_AMOUNT)->SetText(dstrAmount);
}


//******************************************************************************
void ManualDividendDlg::RoundByNumDigit(const DString& inValue, DString& roundedValue, int& iNumDigit)
{
   DString dstrMask = NULL_STRING;
   MakeMaskWithNumDigit(dstrMask,iNumDigit);
   
   BFDecimalField df( ifds::USDollar , &ifds::s_FldProp_USDollar );

   DString strValue(inValue);
   const ClientLocale &clientLocale = ClientLocaleContext::get();
   df.set( strValue, false, clientLocale );
   strValue = df.get( strValue, true, clientLocale, &BFMask( dstrMask ) );
   
   roundedValue = strValue;
}

//******************************************************************************
void ManualDividendDlg::ConvertToStringWithNumDigit(const double& dInValue, DString& roundedValue, int& iNumDigit)
{
   char szFormatBuffer[40];
   char szOutputBuffer[40];

   sprintf( szFormatBuffer, "%%.%df",iNumDigit);
   sprintf( szOutputBuffer, szFormatBuffer, dInValue );
   roundedValue = szOutputBuffer;
}

//******************************************************************************
void ManualDividendDlg::UpdateAmountTypeDollar(void)
{
   DString dstrAmountDecimalDigit, 
            dstrAmount,
            dstrTempAmount,
            dstrPUD;

   getParent()->getField( this, 
                          IFASTBP_PROC::TRADES_LIST, 
                          AmountDecimalDigit, 
                          dstrAmountDecimalDigit, 
                          false);
                           
   getParent()->getField( this, 
                          IFASTBP_PROC::TRADES_LIST, 
                          ifds::Amount, 
                          dstrTempAmount, 
                          false);

   int iAmountDecimalDigit = 2;
   RoundByNumDigit(dstrTempAmount,dstrAmount,iAmountDecimalDigit);
   getParent ()->setField( this, 
                           IFASTBP_PROC::TRADES_LIST, 
                           ifds::Amount, 
                           dstrAmount, 
                           false);
}

//******************************************************************************
void ManualDividendDlg::UpdateAmountTypeUnit(void)
{
   DString dstrAmountDecimalDigit, 
            dstrAmount,
            dstrTempAmount,
            dstrPUD;

   getParent()->getField( this, 
                          IFASTBP_PROC::TRADES_LIST, 
                          AmountDecimalDigit, 
                          dstrAmountDecimalDigit, 
                          false);
                           
   getParent()->getField( this, 
                          IFASTBP_PROC::TRADES_LIST, 
                          ifds::Amount, 
                          dstrTempAmount, 
                          false);

   // round to number of digit specified by
   // UnitPrecision-56
   DString strFCFundRate;
   int iAmountDecimalDigit = dstrAmountDecimalDigit.asInteger();
   RoundByNumDigit(dstrTempAmount,dstrAmount,iAmountDecimalDigit);
   double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);

   getParent()->getField( this, 
                        IFASTBP_PROC::TRADES_LIST, 
                        ifds::FCFundRate, 
                        strFCFundRate, 
                        false);
   double dFCFundRate = DSTCommonFunctions::convertToDouble(strFCFundRate);
   iAmountDecimalDigit = dstrAmountDecimalDigit.asInteger();
   ConvertToStringWithNumDigit(dFCFundRate,strFCFundRate,iAmountDecimalDigit);
   dFCFundRate = DSTCommonFunctions::convertToDouble(strFCFundRate);
   dAmount*=dFCFundRate;
   iAmountDecimalDigit = 2;
   ConvertToStringWithNumDigit(dAmount,dstrAmount,iAmountDecimalDigit);
   dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
   dAmount/=dFCFundRate;
   ConvertToStringWithNumDigit(dAmount,dstrAmount,iAmountDecimalDigit);

   getParent ()->setField( this, 
                           IFASTBP_PROC::TRADES_LIST, 
                           ifds::Amount, 
                           dstrAmount, 
                           false);
}

//******************************************************************************
void ManualDividendDlg::MakeMaskWithNumDigit(DString& strOutMask, int& iNumDigit)
{
   strOutMask = NULL_STRING;
   if( iNumDigit < 0 )
   {
      iNumDigit = 0;
   }

   // hopefully we should not use longer than 24 digit,
   // include digit after decimal point
   int iNumSharp = 24 - iNumDigit - 1;
   DString strTempOut = I_("0");
   
   for( int i = 0; i < iNumSharp; i++ )
   {
      strTempOut += I_("#");
      
      if( (i % 3) == 1 )
      {
         strTempOut += I_(",");
      }
   }
   strOutMask += strTempOut.reverse();

   if( iNumDigit != 0 )
   {
      strOutMask += I_(".");
      
      DString strDecimal = NULL_STRING;
      for(int i=0;i<iNumDigit;i++)
      {
         strDecimal += I_("0");
      }

      strOutMask += strDecimal;
   }
}


//******************************************************************************
void ManualDividendDlg::DisplayBankControls(BOOL bShow)
{
    GetDlgItem(IDC_BTN_BANK_MANUAL_DIV)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_GROUP_BANK)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_LABEL_BANK_NAME_TXT)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_LABEL_BANK_NBR)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_LABEL_ACCT_NAME)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_LABEL_ACCT_NBR)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_BANK_NAME_TXT)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_BANK_NBR)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_ACCT_NAME)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_ACCT_NBR)->ShowWindow(bShow);
}


//******************************************************************************
void ManualDividendDlg::OnBtnBank()
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBank"));

    try
    {
        DString dstrAccountNum, tradeKey;

        getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::AccountNum, dstrAccountNum, false);
        
        tradeKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::TRADES_LIST);

        setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);
        setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
        setParameter (MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::TRADE);

        switch (invokeCommand(getParent(), CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL))
        {
        case CMD_OK:
        case CMD_MODELESS_INPROCESS:
            {
                LoadControls(MD_CONTROLS::BANK);
                break;
            }
        case CMD_CANCEL:
            break;
        default:
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
            break;
        }
    }
    catch (ConditionException &ce)
    {
        ConditionMessageBox (ce);
    }
    catch (...)
    {
        DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
    }
}



//******************************************************************************
void ManualDividendDlg::UpdateControlsByTranstype(DString &transType)
{
    if (DSTCommonFunctions::codeInList(transType, TRADETYPE::POST_ADJUSTMENT_LIST))
    {
        DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
        DString dstrUseSpecialDividend, isAccountSetAndValid, dstrToFund;

        getParent()->getField(this, ACCOUNT, IsAccountSetAndValid, isAccountSetAndValid, false);
        getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, ifds::ToFund, dstrToFund, false);

        dstWorkSession->getOption(ifds::UseSpecialDividend, dstrUseSpecialDividend, BF::HOST, false);

        // ID
        GetDlgItem(IDC_STATIC_DIV_RATE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_DIV_RATE)->ShowWindow(transType != TRADETYPE::MGMT_FEE_REBATE_ADJ ? SW_SHOW:SW_HIDE);
        GetDlgItem(IDC_STATIC_UNITS_ELIGIBLE_DIV)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDT_UNITS_ELIGIBLE_DIV)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDT_UNITS_ELIGIBLE_DIV)->EnableWindow(transType != TRADETYPE::MGMT_FEE_REBATE_ADJ && isAccountSetAndValid == YES ? TRUE:FALSE);

        // AV
        GetDlgItem(IDC_STATIC_REINVEST_RATE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_REINVEST_RATE)->ShowWindow(dstrToFund != I_("CASH") ? SW_SHOW:SW_HIDE);
        GetDlgItem(IDC_STATIC_NUMBER_OF_UNITS_DIV)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDT_NUMBER_OF_UNITS_DIV)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDT_NUMBER_OF_UNITS_DIV)->EnableWindow(transType != TRADETYPE::FOREIGN_CAPGAIN_ALLOCATION_ADJ && dstrToFund != I_("CASH") && isAccountSetAndValid == YES ? TRUE:FALSE);
        
        GetDlgItem(IDC_STATIC_NEG_MONEY_MKT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CMB_NEG_MONEY_MKT)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_RND_CAL_TO_CENTS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CMB_RND_CAL_TO_CENTS)->ShowWindow(SW_SHOW);

        DString dstrIsDilutionAllowed;
        getParent()->getField(this, IFASTBP_PROC::TRADES_LIST, IsDilutionAllowed, dstrIsDilutionAllowed, false);

        GetDlgItem(IDC_BTN_DILUTIONS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BTN_DILUTIONS)->EnableWindow(dstrIsDilutionAllowed == YES);

        // Controls are not used for these transtype.
        GetDlgItem(IDC_STATIC_SETTLEMENT_DATE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_DTP_SETTLE_DATE)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_ORDER_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_DIRECT)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_SETTLE_CURRENCY)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_SETTLE_CURENCY)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_ACCOUNTABILITY)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_ACCOUNTABILITY)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_BACKDATED_REASON)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_REASON)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_AMOUNT_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_AMOUNT_TYPE)->ShowWindow(SW_HIDE);
    }
    else
    {
        // Disable
        GetDlgItem(IDC_STATIC_DIV_RATE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_DIV_RATE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_UNITS_ELIGIBLE_DIV)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDT_UNITS_ELIGIBLE_DIV)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDT_UNITS_ELIGIBLE_DIV)->EnableWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_REINVEST_RATE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_REINVEST_RATE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_NUMBER_OF_UNITS_DIV)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDT_NUMBER_OF_UNITS_DIV)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_STATIC_NEG_MONEY_MKT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_NEG_MONEY_MKT)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_RND_CAL_TO_CENTS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_RND_CAL_TO_CENTS)->ShowWindow(SW_HIDE);

        //GetDlgItem(IDC_STATIC_SPECIAL_DIV)->ShowWindow(SW_HIDE);
        //GetDlgItem(IDC_CMB_SPECIAL_DIV)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_BTN_DILUTIONS)->ShowWindow(SW_HIDE);

        // Enable.
        GetDlgItem(IDC_STATIC_SETTLEMENT_DATE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_DTP_SETTLE_DATE)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_ORDER_TYPE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DIRECT)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_SETTLE_CURRENCY)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CMB_SETTLE_CURENCY)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_ACCOUNTABILITY)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CMB_ACCOUNTABILITY)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_BACKDATED_REASON)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CMB_REASON)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_AMOUNT_TYPE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CMB_AMOUNT_TYPE)->ShowWindow(SW_SHOW);
    }

    GetDlgItem(IDC_CMB_MFR_PAYMENT)->ShowWindow(transType == MFR || transType == TRADETYPE::MGMT_FEE_REBATE_ADJ ? SW_SHOW : SW_HIDE);		
    GetDlgItem(IDC_STATIC_MFR_PAYMENT)->ShowWindow(transType == MFR || transType == TRADETYPE::MGMT_FEE_REBATE_ADJ ? SW_SHOW : SW_HIDE);

    DString isAccountSetAndValid;
    getParent ()->getField ( this,
        ACCOUNT,
        IsAccountSetAndValid,
        isAccountSetAndValid,
        false);

    if (isAccountSetAndValid == I_("N"))
    {
        GetDlgItem(IDC_TXT_PAY_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_PAY_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ADDRESS_CODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_TXT_SUPPRESS_CODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_TXT_ESG_SETTLE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDT_ADDR_CODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_SUPPRESS_CODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CMB_ESG_SETTLE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ADDRESS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_GROUP_BANK)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_SHAREHOLDER_ADDRESS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_LABEL_BANK_NAME_TXT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_LABEL_BANK_NBR)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_LABEL_ACCT_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_LABEL_ACCT_NBR)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_BANK_NAME_TXT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_BANK_NBR)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACCT_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACCT_NBR)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BTN_BANK_MANUAL_DIV)->ShowWindow(SW_HIDE);
    }
}


//******************************************************************************
void ManualDividendDlg::OnBtnDilutions()
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnDilutions"));

    try
    {
        DString tradeKey;

        tradeKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::TRADES_LIST);

        setParameter(I_("FromScr"), I_("TradeEntry"));
        setParameter(MFCAN_IP_PARAM::LIST_KEY, tradeKey);

        switch (getParentProcess()->invokeProcessFromChild(this, CMD_BPROC_DILUTION, PROC_SUPPORT))
        {
        case CMD_OK:
        case CMD_MODELESS_INPROCESS:
            {               
                DString accountable,
                    backDatedReason;

                getParameter (I_("Accountable"), accountable);
                getParameter (I_("BackDatedReason"), backDatedReason);
                getParent()->setField ( this, 
                    IFASTBP_PROC::TRADES_LIST, 
                    ifds::Accountable, 
                    accountable, 
                    false);
                getParent()->setField ( this, 
                    IFASTBP_PROC::TRADES_LIST, 
                    ifds::BackDatedReason, 
                    backDatedReason, 
                    false);
                break;
            }
        case CMD_CANCEL:
            break;
        default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), 
                GETHIGHESTSEVERITY ());
            break;      
        }
    }
    catch (ConditionException &ce)
    {
        ConditionMessageBox (ce);
    }
    catch (...)
    {
        DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
    }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ManualDividendDlg.cpp-arc  $
// 
//    Rev 1.15   Aug 17 2009 08:23:52   dchatcha
// IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop.
// 
//    Rev 1.14   Sep 16 2007 15:42:42   jankovii
// IN #990336 - User is unable to process manual/adhoc MFR trades.
// 
//    Rev 1.13   Sep 06 2007 17:21:14   popescu
// GAP 18 - added manual management fee rebate to manual dividend screen
// 
//    Rev 1.12   Mar 01 2006 13:57:18   ZHANGCEL
// PET1334 - FN01 -- Added logic for ESGSettle enhancement
// 
//    Rev 1.11   Dec 13 2005 16:55:42   zhengcon
// Incident #491607 -- fixed the tab sequence problem after input account number
// 
//    Rev 1.10   Nov 22 2005 09:38:28   zhengcon
// Incident #458410 -- fixed the cursor flashing problem
// 
//    Rev 1.9   Sep 15 2005 15:13:54   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.8   Sep 13 2005 17:37:22   AGUILAAM
// IN 399479 - get fund number for manual dividend
// 
//    Rev 1.7   May 27 2005 10:10:42   popescu
// Incident # 319459 - fixed the Manual Dividend reset issue - also used WorkSessionTradesList for manual dividends; use the TradesProcess instead of ManualDividendProcess
// 
//    Rev 1.6   Jan 19 2004 09:32:32   HERNANDO
// PTS10025436 - Added PreOk to display a message before validation/Confirmation as requested.
// 
//    Rev 1.5   Jan 12 2004 09:44:40   HERNANDO
// PTS 10025436 - Fund Number is no longer displayed for the Luxembourg market.  Discovered during this ticket.
// 
//    Rev 1.4   Jul 21 2003 16:35:20   HERNANDO
// Added filtering for Amount field.  Refresh Suppress Code and Address Code when switching Pay Types.
// 
//    Rev 1.3   Jul 08 2003 16:28:28   HERNANDO
// Sped up Fund Search Dialog by passing in the Account Number.
// 
//    Rev 1.2   Jun 26 2003 16:22:30   HERNANDO
// PTS 10018774 - Added DisplayToFundCodeRelated.
// 
//    Rev 1.1   May 30 2003 17:38:54   HERNANDO
// Changed the Control ID for the Address.  This is due to the change in Control IDs used for Address Edit, Address Static, and Address controls.
// 
//    Rev 1.0   May 22 2003 17:03:46   HERNANDO
// Initial revision.
 * 
 */

