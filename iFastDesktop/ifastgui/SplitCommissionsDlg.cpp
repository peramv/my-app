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
// ^FILE   : SplitCommissionsDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : SplitCommissionsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the SplitCommissionsDlg dialog
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "splitcommissionsdlg.h"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastbp\splitcommissionsprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcfuncs.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_SPLITCOMMISSION;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SplitCommissionsDlg > dlgCreator(CMD_GUI_SPLITCOMMISSION);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("SplitCommissionsDlg");
   const I_CHAR * const LV_TRADE_ALLOCATIONS = I_("Trade Allocation Details");
   const I_CHAR * const LV_SPLIT_COMMISSIONS = I_("Split Commission Details");
   const I_CHAR * const YES = I_("Y");
   const I_CHAR * const NO = I_("N");
   const I_CHAR * const COMMISSION_TYPE_TWO = I_("2");
   const I_CHAR * const FLAT = I_("0");
   const I_CHAR * const RDR_ADVICE_PROVIDED   = I_ ("02");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransactionSplitCommHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId TradeAllocationDetailsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId SplitCommissionDetailsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId SplitCommissionFlatDetailsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFDecimalFieldId GrossAmt;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
}

//******************************************************************************
SplitCommissionsDlg::SplitCommissionsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand) : 
BaseMainDlg(SplitCommissionsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME)
, m_dstrCaller(NULL_STRING)
, m_dstrSplitComm(NO)
, m_dstrTransactionNumber(NULL_STRING)
, m_dstrTransactionTypeDesc(NULL_STRING)
, m_dstrAllocationListKey(NULL_STRING)
, m_dstrSplitCommListKey(NULL_STRING)
, m_bIsInquiry(false)
, m_bIsSplitByRate(false)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(SplitCommissionsDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
SplitCommissionsDlg::~SplitCommissionsDlg()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************

void SplitCommissionsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SplitCommissionsDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(SplitCommissionsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SplitCommissionsDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDCLOSE, OnBtnClose)
ON_MESSAGE(UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_MESSAGE(UM_OPENBRANCHLISTDLG, OpenBranchListDlg)
ON_MESSAGE(UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SplitCommissionsDlg message handlers

BOOL SplitCommissionsDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   CString cstrCaption = GetBaseCaption().c_str();
   cstrCaption += " ";
   CString cstrTransNumber;
   cstrTransNumber.LoadString(TXT_TRANS_TRANSNUM);
   cstrTransNumber += ": ";
   DString dstrAccountNumber(NULL_STRING);
   getGlobal(WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNumber);
   dstrAccountNumber.stripLeading(I_('0'));
   if(!dstrAccountNumber.empty())
   {
      cstrCaption += dstrAccountNumber.c_str();
   }

   if(!m_dstrTransactionNumber.empty())
   {
      cstrCaption += " ";
      cstrCaption += cstrTransNumber;
      cstrCaption += m_dstrTransactionNumber.c_str();
   }
   else if (!m_dstrTransactionTypeDesc.empty())
   {
      cstrCaption += " - ";
      cstrCaption += m_dstrTransactionTypeDesc.c_str();
   }
   SetWindowText(cstrCaption);
   return(TRUE);
}

//******************************************************************************
SEVERITY SplitCommissionsDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   DString dstrTemp, dstrCommissionType;
   
   getParameter(SPLITCOMM::CALLER, m_dstrCaller);
   m_bIsInquiry = m_dstrCaller == SPLITCOMM::TRANSACTION_HISTORY ||
      m_dstrCaller == SPLITCOMM::TRANSACTION_HISTORY_ALLOCATION ||
      m_dstrCaller == SPLITCOMM::TRANSACTION_PENDING ||
      m_dstrCaller == SPLITCOMM::TRANSACTION_PENDING_ALLOCATION;
   
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession*> (getBFWorkSession());
   
   pDSTCWorkSession->getOption(ifds::CommissionType, dstrCommissionType, getDataGroupId(), false);
   m_bIsSplitByRate = dstrCommissionType != COMMISSION_TYPE_TWO;
   
   getParameter (SPLITCOMM::TRANSACTION_NUMBER, m_dstrTransactionNumber);
   getParameter (SPLITCOMM::TRANSACTION_TYPE_DESC, m_dstrTransactionTypeDesc);
   getParameter (SPLITCOMM::ALLOCATION_LIST_KEY, m_dstrAllocationListKey);
   getParameter (SPLITCOMM::SPLIT_COMM_LIST_KEY, m_dstrSplitCommListKey);
   getParameter(I_("FeeType"), m_dstrFeeType);

   return(NO_CONDITION);
}


//******************************************************************************
void SplitCommissionsDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

   CWaitCursor wait;     



   //add and delete buttons
   GetDlgItem(IDC_BTN_ADD)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_BTN_DELETE)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_BTN_ADD)->EnableWindow(!m_bIsInquiry);
   GetDlgItem(IDC_BTN_DELETE)->EnableWindow(!m_bIsInquiry);

   //enable edit controls if not in inquiry
   GetDlgItem(IDC_COMBO_ENTITY_TYPE)->EnableWindow(!m_bIsInquiry);
   GetDlgItem(IDC_COMBO_PAY_TYPE)->EnableWindow(!m_bIsInquiry);
   GetDlgItem(IDC_EDIT_SPLIT_PERCENT)->EnableWindow(!m_bIsInquiry);
   GetDlgItem(IDC_COMBO_SETTLEMENT)->EnableWindow(!m_bIsInquiry);
   GetDlgItem(IDC_EDIT_BROKER)->EnableWindow(!m_bIsInquiry);
   GetDlgItem(IDC_EDIT_BRANCH)->EnableWindow(!m_bIsInquiry);
   GetDlgItem(IDC_EDIT_SALES_REP)->EnableWindow(!m_bIsInquiry);
   //show edit controls if not in inquiry
   GetDlgItem(IDC_COMBO_ENTITY_TYPE)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_COMBO_PAY_TYPE)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_EDIT_SPLIT_PERCENT)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_COMBO_SETTLEMENT)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_EDIT_BROKER)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_EDIT_BRANCH)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_EDIT_SALES_REP)->ShowWindow(!m_bIsInquiry);

   //enable the text controls if in inquiry
   GetDlgItem(IDC_TXT_ENTITY_TYPE)->EnableWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_PAY_TYPE)->EnableWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_SPLIT_PERCENT)->EnableWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_SETTLEMENT)->EnableWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_BROKER)->EnableWindow(true);
   GetDlgItem(IDC_TXT_BRANCH)->EnableWindow(true);
   GetDlgItem(IDC_TXT_SALES_REP)->EnableWindow(true);

   //show the text controls if in inquiry
   GetDlgItem(IDC_TXT_ENTITY_TYPE)->ShowWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_PAY_TYPE)->ShowWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_SPLIT_PERCENT)->ShowWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_SETTLEMENT)->ShowWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_BROKER)->ShowWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_BRANCH)->ShowWindow(m_bIsInquiry);
   GetDlgItem(IDC_TXT_SALES_REP)->ShowWindow(m_bIsInquiry);

   //show only close button in inquiry
   GetDlgItem(IDCLOSE)->EnableWindow(m_bIsInquiry);
   
   //show the buttoms if not in inquiry
   GetDlgItem(IDOK)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDCANCEL)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDC_BTN_RESET)->ShowWindow(!m_bIsInquiry);
   GetDlgItem(IDCLOSE)->ShowWindow(m_bIsInquiry);

   //the transaction history screen is the caller
   if (m_dstrCaller == SPLITCOMM::TRANSACTION_HISTORY)
   {
      AddListControl(CLASSNAME, IDC_LV_TRADE_ALLOC, LV_TRADE_ALLOCATIONS, 
         ifds::TransactionSplitCommHeadingSet, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, 0, true, LISTFLAG_NOT_UPDATABLE);
      AddControl(CTRL_STATIC, IDC_TXT_PERCENT_TOTAL, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, 
         TOTAL_PERCENT, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
      AddControl(CTRL_STATIC, IDC_TXT_AMOUNT_TOTAL, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, 
         ifds::GrossAmt, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
      AddControl(CTRL_STATIC, IDC_TXT_AMOUNT_TOTAL_CURRENCY, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, 
         ifds::SettleCurrency, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
   }
   //the systematic allocation screen is the caller
   else if (m_dstrCaller == SPLITCOMM::SYSTEMATIC_ALLOCATION)
   {
      AddListControl(CLASSNAME, IDC_LV_TRADE_ALLOC, LV_TRADE_ALLOCATIONS, 
         ifds::TradeAllocationDetailsHeadingSet, IFASTBP_PROC::SYS_ALLOCATION_LIST, 0, true, LISTFLAG_NOT_UPDATABLE); 
      AddControl(CTRL_STATIC, IDC_TXT_PERCENT_TOTAL, IFASTBP_PROC::SYS_ALLOCATION_LIST, 
         TOTAL_PERCENT, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
      AddControl(CTRL_STATIC, IDC_TXT_AMOUNT_TOTAL, IFASTBP_PROC::SYS_ALLOCATION_LIST, 
         TOTAL_AMOUNT, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
      AddControl(CTRL_STATIC, IDC_TXT_AMOUNT_TOTAL_CURRENCY, IFASTBP_PROC::SYS_ALLOCATION_LIST, 
         ifds::SettleCurrency, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);      
   }
   //the autotransfer systematic allocation screen is the caller
   else if (m_dstrCaller == SPLITCOMM::SYSTEMATIC_ATALLOCATION)
   {
      AddListControl(CLASSNAME, IDC_LV_TRADE_ALLOC, LV_TRADE_ALLOCATIONS, 
         ifds::TradeAllocationDetailsHeadingSet, IFASTBP_PROC::SYS_ATALLOCATION_LIST, 0, true, LISTFLAG_NOT_UPDATABLE); 
      AddControl(CTRL_STATIC, IDC_TXT_PERCENT_TOTAL, IFASTBP_PROC::SYS_ATALLOCATION_LIST, 
         TOTAL_PERCENT, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
      AddControl(CTRL_STATIC, IDC_TXT_AMOUNT_TOTAL, IFASTBP_PROC::SYS_ATALLOCATION_LIST, 
         TOTAL_AMOUNT, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
      AddControl(CTRL_STATIC, IDC_TXT_AMOUNT_TOTAL_CURRENCY, IFASTBP_PROC::SYS_ATALLOCATION_LIST, 
         ifds::SettleCurrency, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);      
   }
   else //any other caller
   {
      AddListControl(CLASSNAME, IDC_LV_TRADE_ALLOC, LV_TRADE_ALLOCATIONS, 
         ifds::TradeAllocationDetailsHeadingSet, IFASTBP_PROC::FUND_ALLOCATION_LIST, 0, true, LISTFLAG_NOT_UPDATABLE); 
      AddControl(CTRL_STATIC, IDC_TXT_PERCENT_TOTAL, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
         TOTAL_PERCENT, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
      AddControl(CTRL_STATIC, IDC_TXT_AMOUNT_TOTAL, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
         TOTAL_AMOUNT, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
      AddControl(CTRL_STATIC, IDC_TXT_AMOUNT_TOTAL_CURRENCY, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
         ifds::SettleCurrency, CTRLFLAG_NOT_UPDATABLE, FUND_ALLOCATION_GROUP);
   }

   //the split commission details list
   BFFieldId SplitCommissionDetailsHeading = ifds::SplitCommissionDetailsHeadingSet;
   if ((m_dstrCaller == SPLITCOMM::TRADE || m_dstrCaller == SPLITCOMM::TRANSACTION_PENDING || 
	   m_dstrCaller == SPLITCOMM::TRANSACTION_PENDING) && m_dstrFeeType == FLAT)
   {
		SplitCommissionDetailsHeading = ifds::SplitCommissionFlatDetailsHeadingSet;
   }

   AddListControl(CLASSNAME, IDC_LV_SPLIT_COMMISSIONS, LV_SPLIT_COMMISSIONS,
	   SplitCommissionDetailsHeading, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 0, true); 
   AddControl(CTRL_STATIC, IDC_SPLITCOMM_RATE_TOTAL, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
      SPLIT_RATE_TOTAL, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
   AddControl(CTRL_STATIC, IDC_SPLITCOMM_PERCENT_TOTAL, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
      SPLIT_PERCENT_TOTAL, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
   AddControl(CTRL_STATIC, IDC_SPLITCOMM_AMOUNT_TOTAL, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
      SPLIT_AMOUNT_TOTAL, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
   AddControl(CTRL_STATIC, IDC_SPLITCOMM_RENUNCIATION, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
      RENUNCIATION_AMOUNT, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);


   if (m_bIsSplitByRate) //commission type is not "2"
   {
      AddControl (CTRL_STATIC, IDC_SPLITCOMM_FIXED, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::Fixed, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
   }

   if (m_bIsInquiry)
   {
      //in inquriy we only display the values 
      AddControl(CTRL_STATIC, IDC_TXT_ENTITY_TYPE, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::CommEntTypeDesc, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_STATIC, IDC_TXT_PAY_TYPE, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::TradesPayType, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_STATIC, IDC_TXT_SPLIT_PERCENT, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         m_bIsSplitByRate ? ifds::CommRate : ifds::CommPrcnt, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_STATIC, IDC_TXT_SETTLEMENT, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::GrossOrNet, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_STATIC, IDC_TXT_BROKER, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::BrokerCode, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_STATIC, IDC_TXT_BRANCH, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::BranchCode, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_STATIC, IDC_TXT_SALES_REP, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::SlsrepCode, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
   }
   else
   {
      AddControl(CTRL_COMBO, IDC_COMBO_ENTITY_TYPE, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::CommEntType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_COMBO, IDC_COMBO_PAY_TYPE, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::TradesPayType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_COMBO, IDC_COMBO_SETTLEMENT, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::GrossOrNet, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_EDIT, IDC_EDIT_SPLIT_PERCENT, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         m_bIsSplitByRate ? ifds::CommRate : ifds::CommPrcnt, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_EDIT, IDC_EDIT_BROKER, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::BrokerCode, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_EDIT, IDC_EDIT_BRANCH, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::BranchCode, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_COMMISSIONS);
      AddControl(CTRL_EDIT, IDC_EDIT_SALES_REP, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
         ifds::SlsrepCode, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_COMMISSIONS);
	   DSTEdit *dstEditCommRate = 
         dynamic_cast<DSTEdit *> (GetDlgItem (IDC_EDIT_SPLIT_PERCENT));

      if (NULL != dstEditCommRate)
	   {
		   DString dstrPercentageMask = DSTCommonFunctions::getMask (m_bIsSplitByRate ? ifds::CommRate : ifds::CommPrcnt);
         int iDecimalPointPos = dstrPercentageMask.find (I_("."));

         dstEditCommRate->AllowNonnegativeDecimalNumbers(
            iDecimalPointPos, 
            dstrPercentageMask.length() - iDecimalPointPos - 2);
	   }
   }
   //in either case add the broker, bracnch and sales rep description
   AddControl(CTRL_STATIC, IDC_TXT_BROKER_DESC, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
      ifds::BrokerName, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
   AddControl(CTRL_STATIC, IDC_TXT_BRANCH_DESC, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
      ifds::BranchName, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);
   AddControl(CTRL_STATIC, IDC_TXT_SALES_REP_DESC, IFASTBP_PROC::SPLIT_COMMISSION_LIST, 
      ifds::SlsrepName, CTRLFLAG_NOT_UPDATABLE, IDC_LV_SPLIT_COMMISSIONS);

   showHideFlatPercentControls (m_dstrFeeType);

   //load and connect the controls to data
   //for the allocation list if there are two or more items in the list,
   //set the selection on the item highilted in the parent dialog
   LoadListControl( IDC_LV_TRADE_ALLOC, 
                    m_dstrAllocationListKey != NULL_STRING ? &m_dstrAllocationListKey : NULL);
   LoadListControl( IDC_LV_SPLIT_COMMISSIONS, 
                    m_dstrSplitCommListKey != NULL_STRING ? &m_dstrSplitCommListKey : NULL);
   
   ConnectControlsToData (FUND_ALLOCATION_GROUP);
   LoadControls (FUND_ALLOCATION_GROUP);
   if (!m_bIsSplitByRate) //set caption
   {   // Dialog initially "Split Rate:"
      CString cstrTemp;

      cstrTemp.LoadString(TXT_SPLIT_PERCENT);
      SetDlgItemText(IDC_SPLIT_PERCENT, cstrTemp);
   }

//incident 353558
   if( !m_bIsInquiry )
   {
      BFFieldId idField = m_bIsSplitByRate? ifds::CommRate : ifds::CommPrcnt;
      const BFProperties * pBFProp = getParent()->getFieldAttributes(this, IFASTBP_PROC::SPLIT_COMMISSION_LIST, idField );
      if( pBFProp )
      {
         int iMaxLen = pBFProp->getMaxLength();
         iMaxLen -=  iMaxLen / 3;  
         DSTEdit* pEdit = dynamic_cast<DSTEdit* > (GetControl( IDC_EDIT_SPLIT_PERCENT ) );
         if (pEdit )
         {
            pEdit->SetMaxCharNum(iMaxLen);      
         }
      }
   } 
   DString rdrAdvice;
   getParent()->getField( this, IFASTBP_PROC::SPLIT_COMMISSION_LIST, ifds::RDRAdvice, rdrAdvice, true );
   GetDlgItem(IDC_BTN_ADD)->EnableWindow(rdrAdvice != RDR_ADVICE_PROVIDED);
   GetDlgItem(IDC_BTN_DELETE)->EnableWindow(rdrAdvice != RDR_ADVICE_PROVIDED);
}

//******************************************************************************
void SplitCommissionsDlg::OnBtnAdd() 
{
   AddToListControl(IDC_LV_SPLIT_COMMISSIONS);
   DisplayByEntityType();
}

//******************************************************************************
void SplitCommissionsDlg::OnBtnDelete() 
{
   DeleteFromListControl(IDC_LV_SPLIT_COMMISSIONS);
}

//******************************************************************************
void SplitCommissionsDlg::OnBtnReset() 
{
   ResetListItem(IDC_LV_SPLIT_COMMISSIONS);
}

//******************************************************************************
void SplitCommissionsDlg::OnBtnClose()
{
   PostMessage( WM_CLOSE ); // IN2624129 - no validation should applied on viewing history trades
}

//******************************************************************************
BOOL SplitCommissionsDlg::PreTranslateMessage(MSG* pMsg) 
{
   if(pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 && 
         !IsSelectedCtrlUpdateable())
   {
      return(TRUE);
   }

   if(pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
      if(GetFocus()== GetDlgItem(IDC_EDIT_BROKER))
         PostMessage(UM_OPENBROKERLISTDLG);
      else if(GetFocus()== GetDlgItem(IDC_EDIT_BRANCH))
         PostMessage(UM_OPENBRANCHLISTDLG);
      else if(GetFocus() == GetDlgItem(IDC_EDIT_SALES_REP))
         PostMessage(UM_OPENSLSREPLISTDLG);
   }
   return(BaseMainDlg::PreTranslateMessage(pMsg));
}

//****************************************************************************** 
LRESULT SplitCommissionsDlg::OpenBrokerListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBrokerListDlg"));

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode;

      GetControlText(IDC_EDIT_BROKER, dstrBrokerCode);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode);
      //invoke the broker dialog and process
      eRtn = invokeCommand(getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString dstrBrokerCode;

               getParameter(MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode);
               if(!dstrBrokerCode.empty())
               {
                  bool bSuccess = SetControlText(IDC_EDIT_BROKER, dstrBrokerCode);
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem(IDC_EDIT_BROKER));
                  if(!bSuccess && pBC)
                     pBC->Load();
                  if(pBC && pBC->IsToolTipVisible())
                     pBC->ToggleToolTip();
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return(0);
}

//******************************************************************
LRESULT SplitCommissionsDlg::OpenBranchListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBranchListDlg"));
   //
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode;

      GetControlText(IDC_EDIT_BROKER, dstrBrokerCode);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode);
      //invoke the broker dialog and process
      eRtn = invokeCommand(getParent(), CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString dstrBranchCode;

               getParameter(MFCAN_IP_PARAM::BRANCH_CODE, dstrBranchCode);
               if(!dstrBrokerCode.empty())
               {
                  bool bSuccess = SetControlText(IDC_EDIT_BRANCH, dstrBranchCode);
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem(IDC_EDIT_BRANCH));
                  if(!bSuccess && pBC)
                     pBC->Load();
                  if(pBC && pBC->IsToolTipVisible())
                     pBC->ToggleToolTip();
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return(0);
}

//******************************************************************
LRESULT SplitCommissionsDlg::OpenSlsRepListDlg(WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg"));

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode, dstrBranchCode;

      GetControlText(IDC_EDIT_BROKER, dstrBrokerCode);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode);
      GetControlText(IDC_EDIT_BRANCH, dstrBranchCode);
      setParameter(MFCAN_IP_PARAM::BRANCH_CODE, dstrBranchCode);

      //invoke the broker dialog and process
      eRtn = invokeCommand(getParent(), CMD_BPROC_SLSREP, PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString dstrAgentCode;

               getParameter(MFCAN_IP_PARAM::SALES_REP_CODE, dstrAgentCode);
               if(!dstrBrokerCode.empty())
               {
                  bool bSuccess = SetControlText(IDC_EDIT_SALES_REP, dstrAgentCode);
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem(IDC_EDIT_SALES_REP));
                  if(!bSuccess && pBC)
                     pBC->Load();
                  if(pBC && pBC->IsToolTipVisible())
                     pBC->ToggleToolTip();
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return(0);
}

//****************************************************************************** 
void SplitCommissionsDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{  
   TRACE_METHOD(CLASSNAME, I_("DoListItemChanged"));      

   if (listControlID == IDC_LV_TRADE_ALLOC)
   {
      if (m_dstrCaller == SPLITCOMM::SYSTEMATIC_ALLOCATION)
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ALLOCATION_LIST, ifds::SplitComm, m_dstrSplitComm, false);         
      }
      else if ((m_dstrCaller == SPLITCOMM::TRANSACTION_PENDING_ALLOCATION) ||  
               (m_dstrCaller == SPLITCOMM::TRANSACTION_PENDING) ||
               (m_dstrCaller == SPLITCOMM::TRANSACTION_HISTORY_ALLOCATION) ||
               (m_dstrCaller == SPLITCOMM::TRADE_ALLOCATION) ||
               (m_dstrCaller == SPLITCOMM::TRADE))
      {
         getParent()->getField (this, IFASTBP_PROC::FUND_ALLOCATION_LIST, ifds::SplitComm, m_dstrSplitComm, false);
      }
      else if (m_dstrCaller == SPLITCOMM::SYSTEMATIC_ATALLOCATION)
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ATALLOCATION_LIST, ifds::SplitComm, m_dstrSplitComm, false);         
      }
      else if (m_dstrCaller == SPLITCOMM::TRANSACTION_HISTORY)
      {
         getParent()->getField (this, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, ifds::SplitComm, m_dstrSplitComm, false);
      }
      if (m_dstrSplitComm == YES)
      {
         EnableSplitCommission (true);
         LoadListControl (IDC_LV_SPLIT_COMMISSIONS);
      }
      else
      {
         EnableSplitCommission (false);      
         GetList(IDC_LV_SPLIT_COMMISSIONS)->DeleteAllItems();
         ClearControls (IFASTBP_PROC::SPLIT_COMMISSION_LIST);
      }

	  showHideFlatPercentControls (m_dstrFeeType);
   }
   else
   {
      if (m_bIsInquiry)
      {
         DisplayByEntityType();
      }
      else if (listControlID == IDC_LV_SPLIT_COMMISSIONS && !m_bIsSplitByRate)
      {
//INA Project - Commissions
         GetDlgItem (IDC_EDIT_SPLIT_PERCENT)->EnableWindow (false);
      }
   }
}

//****************************************************************************** 
void SplitCommissionsDlg::EnableSplitCommission(bool bEnable) 
{
   // Controls
   GetDlgItem(IDC_BTN_ADD)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_DELETE)->EnableWindow(bEnable);
   GetDlgItem(IDC_SPLITCOMM_RATE_TOTAL)->ShowWindow(bEnable);
   GetDlgItem(IDC_SPLITCOMM_PERCENT_TOTAL)->ShowWindow(bEnable);
   GetDlgItem(IDC_SPLITCOMM_AMOUNT_TOTAL)->ShowWindow(bEnable);
   GetDlgItem(IDC_SPLITCOMM_RENUNCIATION)->ShowWindow(bEnable);
   GetDlgItem(IDC_SPLITCOMM_FIXED)->ShowWindow(bEnable);

   if(!m_bIsInquiry)
   {
		ConnectControl(IDC_COMBO_ENTITY_TYPE, bEnable);
		ConnectControl(IDC_COMBO_PAY_TYPE, bEnable);
		ConnectControl(IDC_EDIT_SPLIT_PERCENT, bEnable);
		ConnectControl(IDC_COMBO_SETTLEMENT, bEnable);

		// Broker, Branch, Salesrep
		ConnectControl(IDC_EDIT_BROKER, bEnable);
		ConnectControl(IDC_EDIT_BRANCH, bEnable);
		ConnectControl(IDC_EDIT_SALES_REP, bEnable);
   }
}

//****************************************************************************** 
bool SplitCommissionsDlg::GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut)
{
   if(m_dstrCaller == SPLITCOMM::TRANSACTION_HISTORY)
   {
      if(dstrColumnKey == I_("Percent"))
      {
         getParent()->getField (this, IFASTBP_PROC::TRANSACTION_HISTORY_LIST, TOTAL_PERCENT, dstrOut);
         return(true);
      }
   }
   else if((m_dstrCaller == SPLITCOMM::TRANSACTION_PENDING) ||
            (m_dstrCaller == SPLITCOMM::TRANSACTION_PENDING_ALLOCATION) ||
            (m_dstrCaller == SPLITCOMM::TRANSACTION_HISTORY_ALLOCATION) ||
            (m_dstrCaller == SPLITCOMM::TRADE_ALLOCATION) ||
            (m_dstrCaller == SPLITCOMM::TRADE))
   {
      if(dstrColumnKey == I_("rxFundCode"))
      {
         getParent()->getField (this, IFASTBP_PROC::FUND_ALLOCATION_LIST, ifds::FundCode, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("rxClassCode"))
      {
         getParent()->getField (this, IFASTBP_PROC::FUND_ALLOCATION_LIST, ifds::ClassCode, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("Percent"))
      {
         getParent()->getField (this, IFASTBP_PROC::FUND_ALLOCATION_LIST, ifds::AllocPercentage, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("Amount"))
      {
         getParent()->getField (this, IFASTBP_PROC::FUND_ALLOCATION_LIST, ifds::AllocAmount, dstrOut);
         return(true);
      }

   }
   else if(m_dstrCaller == SPLITCOMM::SYSTEMATIC_ALLOCATION)
   {
      if(dstrColumnKey == I_("rxFundCode"))
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ALLOCATION_LIST, ifds::FundCode, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("rxClassCode"))
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ALLOCATION_LIST, ifds::ClassCode, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("Percent"))
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ALLOCATION_LIST, ifds::Percentage, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("Amount"))
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ALLOCATION_LIST, ifds::AllocAmount, dstrOut);
         return(true);
      }
   }
   else if(m_dstrCaller == SPLITCOMM::SYSTEMATIC_ATALLOCATION)
   {
      if(dstrColumnKey == I_("rxFundCode"))
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ATALLOCATION_LIST, ifds::FundCode, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("rxClassCode"))
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ATALLOCATION_LIST, ifds::ClassCode, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("Percent"))
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ATALLOCATION_LIST, ifds::Percentage, dstrOut);
         return(true);
      }
      else if(dstrColumnKey == I_("Amount"))
      {
         getParent()->getField (this, IFASTBP_PROC::SYS_ATALLOCATION_LIST, ifds::AllocAmount, dstrOut);
         return(true);
      }
   }
   if (dstrColumnKey == I_("SplitRate"))
   {
      getParent()->getField (this, IFASTBP_PROC::SPLIT_COMMISSION_LIST, ifds::CommRate, dstrOut);
      return(true);
   }
   return(false);
}

//****************************************************************************** 
void SplitCommissionsDlg::DisplayByEntityType() 
{
   bool  bBroker, bBranch, bSalesRep;
   DString dstrTemp(NULL_STRING);

   // Set flags based on entity type
   if(m_dstrSplitComm == YES)
   {
      getParent()->getField(this, IFASTBP_PROC::SPLIT_COMMISSION_LIST, ifds::CommEntType, dstrTemp, false);
   }
   if(dstrTemp == I_("BROK"))
   {
      bBroker = true;
      bBranch = false;
      bSalesRep = false;
   }
   else if(dstrTemp == I_("BRNH"))
   {
      bBroker = true;
      bBranch = true;
      bSalesRep = false;
   }
   else if(dstrTemp == I_("CNTX"))
   {
      bBroker = false;
      bBranch = false;
      bSalesRep = false;
   }
   else if(dstrTemp == I_("SREP"))
   {
      bBroker = true;
      bBranch = true;
      bSalesRep = true;
   }
   else
   {
      bBroker = false;
      bBranch = false;
      bSalesRep = false;
   }

   // Static Text
   GetDlgItem(IDC_STATIC_BROKER)->ShowWindow(bBroker);
   GetDlgItem(IDC_STATIC_BRANCH)->ShowWindow(bBranch);
   GetDlgItem(IDC_STATIC_SALESREP)->ShowWindow(bSalesRep);
   GetDlgItem(IDC_TXT_BROKER_DESC)->ShowWindow(bBroker);
   GetDlgItem(IDC_TXT_BRANCH_DESC)->ShowWindow(bBranch);
   GetDlgItem(IDC_TXT_SALES_REP_DESC)->ShowWindow(bSalesRep);

   // Controls
   if(m_bIsInquiry)
   {
      ShowControl(IDC_TXT_BROKER, bBroker);      
      ShowControl(IDC_TXT_BRANCH, bBranch);
      ShowControl(IDC_TXT_SALES_REP, bSalesRep);
   }
   else
   {
      ShowControl(IDC_EDIT_BROKER, bBroker);
      ShowControl(IDC_EDIT_BRANCH, bBranch);
      ShowControl(IDC_EDIT_SALES_REP, bSalesRep);
   }
}

//****************************************************************************** 
void SplitCommissionsDlg::ControlUpdated(UINT controlID, const DString &dstrValue)
{
   switch(controlID)
   {
      case IDC_EDIT_BROKER:
         {
            LoadControl(IDC_TXT_BROKER_DESC);
         }
         break;
      case IDC_EDIT_BRANCH:
         {
            LoadControl(IDC_TXT_BRANCH_DESC);
         }
         break;
      case IDC_EDIT_SALES_REP:
         {
            LoadControl(IDC_TXT_SALES_REP_DESC);
         }
         break;
      case IDC_COMBO_ENTITY_TYPE:
         {
            DisplayByEntityType();
         }
      case IDC_EDIT_SPLIT_PERCENT:
         {
            //get a pointer to the split commission list control
         	DSTListCtrl *pDSTListCtrlSplitComm = GetList(IDC_LV_SPLIT_COMMISSIONS);
            //kludge to get refreshed all items in this list, 
            //in order to get an update from the calculated fields
            pDSTListCtrlSplitComm->RefreshAllItems();
            LoadControl(IDC_SPLITCOMM_RATE_TOTAL);
            LoadControl(IDC_SPLITCOMM_PERCENT_TOTAL);
            LoadControl(IDC_SPLITCOMM_AMOUNT_TOTAL);
            LoadControl(IDC_SPLITCOMM_RENUNCIATION);
         }
         break;
   }
}
//******************************************************************************

void SplitCommissionsDlg::showHideFlatPercentControls (const DString &dstrFlatPercent)
{
	bool bShow = dstrFlatPercent == FLAT ? false : true;

	if (bShow)
		return;
	
	GetDlgItem (IDC_STC_SPLIT_PRCNT_TOTAL)->ShowWindow (bShow);       
	GetDlgItem (IDC_STC_SPLIT_AMOUNT_TOTAL)->ShowWindow (bShow);      
	GetDlgItem (IDC_STC_REN_AMOUNT)->ShowWindow (bShow);              
	GetDlgItem (IDC_STC_FIXED)->ShowWindow (bShow);   

	GetDlgItem (IDC_SPLITCOMM_PERCENT_TOTAL)->ShowWindow (bShow);   
	GetDlgItem (IDC_SPLITCOMM_AMOUNT_TOTAL)->ShowWindow (bShow);   
	GetDlgItem (IDC_SPLITCOMM_RENUNCIATION)->ShowWindow (bShow);   
	GetDlgItem (IDC_SPLITCOMM_FIXED)->ShowWindow (bShow);   
	
	CString cstrAmount;
	CString cstrAmountTotatl;

	cstrAmountTotatl.LoadString (TXT_SPLIT_AMOUNT_TOTAL);
	cstrAmount.LoadString (IDS_SPLIT_AMOUNT);

	SetDlgItemText(IDC_SPLIT, cstrAmount);
	SetDlgItemText(IDC_STC_SPLIT_RATE_TOTAL, cstrAmountTotatl);
}

//******************************************************************************
//              Revision Control Entries
//****************************************************************************** 
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SplitCommissionsDlg.cpp-arc  $
// 
//    Rev 1.49   Jul 30 2012 09:10:08   wp040027
// P0198518 - RDR Functionality - Review Comment incorporated
// 
//    Rev 1.48   Jul 26 2012 10:29:06   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.47   Feb 09 2012 19:34:34   popescu
// 2821238 - Base Commission should be calculated on Overriding the default Acquisition Fee
// 
//    Rev 1.46   Aug 23 2011 04:47:04   panatcha
// IN2624129 - Split Commission Inquiry error message
// 
//    Rev 1.45   Mar 25 2011 16:22:34   jankovii
// IN 2475801 - Invalid split commission calculation
// 
//    Rev 1.44   Mar 03 2011 16:06:32   jankovii
// PET181943 FN01 - XMLPhase 2
// 
//    Rev 1.43   Sep 15 2005 15:15:20   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.42   Aug 05 2005 09:59:52   Yingbaol
// fix crash in inquiry mode
// 
//    Rev 1.41   Jul 12 2005 09:44:34   Yingbaol
// Incident 353558: splitcommission internal problem by limit the maximum character allowed.
// 
//    Rev 1.40   Nov 27 2004 21:22:12   popescu
// PET 1117/06, trade processing
// 
//    Rev 1.39   Nov 09 2004 16:38:18   popescu
// PTS 10034369, allow only 4 decimals for the comm rate field 
// 
//    Rev 1.38   Jul 10 2003 22:22:14   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.37   May 14 2003 11:16:14   popescu
// added extra param to the process layer, which is used to pass the key string of the current selected item in the allocations list, in order to set selection on it in split commission dialog
// 
//    Rev 1.36   May 13 2003 10:07:32   popescu
// Split commission re-work
// 
//    Rev 1.35   Mar 21 2003 18:41:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.34   Jan 08 2003 19:03:56   WINNIE
// Sync up Rel 49 :  Rev 1.33   Oct 18 2002 11:56:10  bug fix for controls clearing up and not restoring properly. 
// 
//    Rev 1.33   Oct 09 2002 23:56:14   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.32   Jun 03 2002 11:22:14   HSUCHIN
// sync up with 1.29.1.0
// 
//    Rev 1.31   22 May 2002 19:16:28   PURDYECH
// BFData Implementation
// 
//    Rev 1.30   29 Apr 2002 16:38:56   KOVACSRO
// new trade allocations.
// 
//    Rev 1.29   27 Mar 2002 20:01:22   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.28   Mar 08 2002 08:35:46   JANKAREN
// removed fixed field only when commissiontype is '2'
// 
//    Rev 1.27   13 Feb 2002 11:24:52   HSUCHIN
// PTS 10007094 - removed the fixed field from dialog
// 
//    Rev 1.26   01 Oct 2001 16:39:40   HSUCHIN
// bug fix to clear split commission list
// 
//    Rev 1.25   09 Jul 2001 11:01:06   HSUCHIN
// getField fix for DBR::SplitComm
// 
//    Rev 1.24   14 Jun 2001 11:58:28   SMITHDAV
// Removed references to UserAccessProcess.
// 
//    Rev 1.23   24 May 2001 14:09:12   KOVACSRO
// Changed subst. set for Transaction History.
// 
//    Rev 1.22   07 May 2001 13:51:12   HSUCHIN
// bug fix for transaction history
// 
//    Rev 1.21   May 03 2001 15:48:28   HERNANDO
// Display Caption parameters.
// 
//    Rev 1.20   28 Apr 2001 15:11:14   HSUCHIN
// bug fix and clean up
// 
//    Rev 1.19   28 Apr 2001 13:13:48   HSUCHIN
// fix clearing of Split Commissions List
// 
//    Rev 1.18   Apr 27 2001 18:28:42   HERNANDO
// Revised clearing Split Commisions List.
// 
//    Rev 1.17   Apr 27 2001 17:52:44   HERNANDO
// Clear Split Commissions List when no Split Comm.
// 
//    Rev 1.16   26 Apr 2001 11:21:34   HSUCHIN
// removed refreshlistitem from control update
// 
//    Rev 1.15   Apr 19 2001 18:30:54   HERNANDO
// Display labels for Inquiries fix.
// 
//    Rev 1.14   14 Apr 2001 16:04:16   HSUCHIN
// trade hook up and additional code enhancement
// 
//    Rev 1.13   06 Apr 2001 11:37:08   KOVACSRO
// Added F4 perm. check.
// 
//    Rev 1.12   03 Apr 2001 20:25:46   HSUCHIN
// added auto transfers splitcommissions hook up
// 
//    Rev 1.11   Mar 23 2001 15:09:20   HERNANDO
// Fixed SalesRep Desc.; removed fns.
// 
//    Rev 1.10   Mar 22 2001 18:32:54   HERNANDO
// Dialog changed to either split by Rate or Percent. 
// 
//    Rev 1.9   Mar 22 2001 16:28:54   HERNANDO
// Check in for Winnie.
// 
//    Rev 1.8   Mar 22 2001 14:12:12   HSUCHIN
// logic added for transaction allocation hook up
// 
//    Rev 1.7   Mar 21 2001 18:37:46   HERNANDO
// Check in for Chin
// 
//    Rev 1.6   Mar 21 2001 13:30:14   HSUCHIN
// more improvements and bug fix
// 
//    Rev 1.5   Mar 20 2001 15:44:58   HSUCHIN
// implemented reset button, ensures split commission exists before being loaded.
// 
//    Rev 1.4   Mar 19 2001 16:40:38   HSUCHIN
// bug fix
// 
//    Rev 1.3   Mar 19 2001 15:03:18   HSUCHIN
// more Dialog processing
// 
//    Rev 1.2   Mar 18 2001 17:55:42   HERNANDO
// Development changes.
// 
//    Rev 1.0   Mar 13 2001 09:09:10   HSUCHIN
// Initial revision.
 * 
 *
 */
