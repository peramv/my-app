// RESPTransactionsDlg.cpp : implementation file
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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RESPTransactionsDlg.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/21/2000
//
// ^CLASS    : RESPTransactionsDlg
// ^SUBCLASS : BaseMainDlg         
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include "stdafx.h"
#include "mfdstc.h"
#include <uibase\ifdslistctrl.h>


#include "resptransactionsdlg.h"

#include <uibase\ConditionMessageDialog.h>
#include <uibase\dstbutton.h>
#include <ifastbp\RESPTransactionsProcessIncludes.h>
#include <ifastbp\RESPTransactionsProcess.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_RESPTRANSACTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_BENEF_ALLOCATION_LIST;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_TRANSFER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PSE_EAP;
                                  
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RESPTransactionsDlg > dlgCreator( CMD_GUI_RESPTRANSACTIONS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // trace literals
   const I_CHAR *CLASSNAME				= I_( "RESPTransactionsDlg" );
   const I_CHAR *LV_RESPTRANSACTIONS	= I_( "RESPTransactionsList" ); 
   const I_CHAR *PENDPROCRECORD_TYPE	= I_( "PendProcRecordType" );
   const I_CHAR *TRANSID				= I_( "TransId" );
   const I_CHAR *CASH					= I_( "1" );
   const I_CHAR *PAC					= I_( "2" );
   const I_CHAR *ED						= I_("ED"); 
   const I_CHAR *TI						= I_("TI");
   const I_CHAR *TR						= I_("TR");
   const I_CHAR *INCOMPLETE				= I_("0");
   const I_CHAR *TRANS_HIST             = I_( "TransHist" );
   const I_CHAR *CALLER                 = I_( "Caller" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RESP_BENEFICIARY_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const RESP_TRANSFER;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFNumericFieldId HistNonTrustYear;
   extern CLASS_IMPORT const BFTextFieldId TotTransfINDC;
   extern CLASS_IMPORT const BFDecimalFieldId BCTESGGrant;
}

using namespace RESPTRANSACTIONSNAMES;

class LVRespTransactionsData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVRespTransactionsData() {}
   DString BeneName_;
   DString TransType_;
   DString DepositTypeDesc_;
   DString TransId_;
   DString EffectiveDate_;
   DString GrossAmt_;
   DString HistNonTrustYear_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BeneName, BeneName_);
      BeneName_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::TransType, TransType_);
      TransType_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::DepositTypeDesc, DepositTypeDesc_);
      DepositTypeDesc_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::TransId, TransId_);
      TransId_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::EffectiveDate, EffectiveDate_);
      EffectiveDate_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::GrossAmt, GrossAmt_);
      GrossAmt_.strip();

	  pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::HistNonTrustYear, HistNonTrustYear_);
      HistNonTrustYear_.strip();
   }
};

class LVRESPTransactionsAdapter : public IFDSListCtrlAdapter< LVRespTransactionsData >
{
public:
   // required overrides
   virtual int compare(IFDSListBase* pCtrl, int iSortColumn, bool bAscending, 
      RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2)
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField(iSortColumn - 1);
      if (1 == iSortColumn) 
      {
         // Condition indicator column.  Sort on image index
         result = (IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem(lParam2, iSortColumn - 1)->iImage);
      } 
      else if (NULL == pFieldId) 
      {
         return (0);
      } 
      else if (*pFieldId == ifds::BeneName) 
      {
         result = i_strcmp(pData1->BeneName_.c_str(), pData2->BeneName_.c_str());
      } 
      else if (*pFieldId == ifds::TransType) 
      {
         result = i_strcmp(pData1->TransType_.c_str(), pData2->TransType_.c_str());
      } 
      else if (*pFieldId == ifds::DepositTypeDesc) 
      {
         result = i_strcmp(pData1->DepositTypeDesc_.c_str(), pData2->DepositTypeDesc_.c_str());
      } 
      else if (*pFieldId == ifds::TransId) 
      {
         result = i_strcmp(pData1->TransId_.c_str(), pData2->TransId_.c_str());
      } 
      else if( *pFieldId == ifds::EffectiveDate ) 
	   {
			if ( DSTCommonFunctions::CompareDates( pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = -1;
			else if ( DSTCommonFunctions::CompareDates( pData2->EffectiveDate_.c_str(), pData1->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = 1;
	   }
      else if (*pFieldId == ifds::GrossAmt) 
      {
         result = i_strcmp(pData1->GrossAmt_.c_str(), pData2->GrossAmt_.c_str());
      } 
	  else if (*pFieldId == ifds::HistNonTrustYear) 
      {
         result = i_strcmp(pData1->HistNonTrustYear_.c_str(), pData2->HistNonTrustYear_.c_str());
      }
	  

      return (bAscending ? result : -result);
   }

   virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
   {
      if (pDispInfo->item.mask & LVIF_TEXT)
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);

         if (NULL == pFieldId) 
         {
            pDispInfo->item.pszText = I_("");
         } 
         else if (*pFieldId == ifds::BeneName) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BeneName_.c_str();
         } 
         else if (*pFieldId == ifds::TransType) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->TransType_.c_str();
         } 
         else if (*pFieldId == ifds::DepositTypeDesc) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DepositTypeDesc_.c_str();
         } 
         else if (*pFieldId == ifds::TransId)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->TransId_.c_str();
         } 
         else if( *pFieldId == ifds::EffectiveDate) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         }
         else if( *pFieldId == ifds::GrossAmt)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->GrossAmt_.c_str();
         }
         else if (*pFieldId == ifds::HistNonTrustYear) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->HistNonTrustYear_.c_str();
         }
         return 1;
      }
      return 0;
   }
};

//******************************************************************************
RESPTransactionsDlg::RESPTransactionsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RESPTransactionsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(RESPTransactionsDlg)
   _strHistoryPendingMode = HISTORY;
   //}}AFX_DATA_INIT
}


//******************************************************************************
void RESPTransactionsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RESPTransactionsDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(RESPTransactionsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RESPTransactionsDlg)
ON_BN_CLICKED(IDC_BTN_RESP_TRANSACTIONS, OnBtnRESPTransactions)
ON_BN_CLICKED(IDC_BTN_ALLOCS, OnBtnAllocations)
ON_BN_CLICKED(IDC_BTN_TRANSFER, OnBtnTransfer)
ON_BN_CLICKED(IDC_BTN_PSEEAP, OnBtnPSEEAP)
ON_BN_CLICKED(IDC_RB_RESP_HISTORY, OnRbRESPHistory)
ON_BN_CLICKED(IDC_RB_RESP_PENDING, OnRbRESPPending)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RESPTransactionsDlg message handlers

//******************************************************************************
SEVERITY RESPTransactionsDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   getParameter (ACCOUNT_NUMBER_FIELD, _strAccountNumber);
   getParameter (HISTORY_PENDING_FIELD, _strHistoryPendingMode);
   getParameter (CALLER, _strCaller );

   return NO_CONDITION;
}

//******************************************************************************
BOOL RESPTransactionsDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();

	IFDSListCtrl* pRespTransactionList = 
      new IFDSAdaptedListCtrl< LVRESPTransactionsAdapter >(this, CLASSNAME, IDC_LV_RESP_TRANSACTIONS, 0, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE, true, true);
   
   AddIFDSListControl (pRespTransactionList, LV_RESPTRANSACTIONS, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::RESPTransactionHeadingSet);

   	addControlsForSearchCriteria();

   AddControl ( CTRL_STATIC, 
                IDC_STC_HRDCTRANSID, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::HRDCTransId, 
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_ACAMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::ACAmt, 
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_UCAMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::UCAmt, 
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_GRANTTRANSID, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::GrantTransId,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_REJCODE, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::CESGInDetlErrorDesc,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SETTLEDATE, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SettleDate,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_UCREASON, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::UCReasonDesc,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);   
   AddControl ( CTRL_STATIC, 
                IDC_STC_NET_AMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::GrossAmt,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STCREPORTEDHRDC, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::HRDCReported,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TRANSSTATUS, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RESPTransStat,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

   // SAGES
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESUCREASON, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESUCREASON, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESUCDesc,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESREJREASON, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESREJREASON, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESRejDesc,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESREPORTED, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESREPORTED, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESReported,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESTRANSID, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESTRANSID, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESTransID,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESTRANSORIGCODE, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESTRANSORIGCODE, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESTransOrigCode,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

// Purchase
   AddControl ( CTRL_STATIC, 
                IDC_STC_PURCH, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_DEPOSIT_TYPE, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_DEPOSIT_TYPE, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::DepositType,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_CESG_AMOUNT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_CESGCALC, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::GrantAmount,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_CLB_AMOUNT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_CLB_AMOUNT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::PurCLB,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_PUR_ADD, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_ADDTL_CESG_AMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::PurAdd,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_ALBERTA_PGRANT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_ALBERTA_PGRANT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::PurPGrant,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_PUR_QESI, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_QESI_BASIC, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::PurQESI,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_ADDTL_QESI, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_ADDTL_QESI, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::AddtlQESI,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_GR_REPAY_REASON, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_GR_PAYMENT_REASON, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                //ifds::AddlCESGRsnDesc,
                ifds::AddlCESGRsnCode,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_TAX_YEAR, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RESPContrDetlTaxYear,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_PURCH_GRANT_REPAY, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_PURHC_GRANT_REPAYMENT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::GrantRepayablePurch,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

   AddControl ( CTRL_STATIC, 
                IDC_STC_RES_CESG, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::IsResidualCESG,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);   

   // SAGES
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESPURAMT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESPURAMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESPurAmt,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

//Redemption
   AddControl ( CTRL_STATIC, 
                IDC_STC_REDEEM, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_RED_CODE, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_AIP, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_RED_CODE, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RedCode,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_GRANT_REPAYABLE, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_GRANTREPAYABLE, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::GrantRepayable,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_GRANT_REPAY_REASON, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_GRREPAYREASON, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::GratRepayReasonAll,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_RED_INCOME, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_RED_INCOME, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RedIncome,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_RED_CLB, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_RED_CLB, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RedCLB,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_RED_CESG, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_RED_CESG, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RedCESG,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_RED_ALBERTA_PGRANT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_RED_ALBERTA_PGRANT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RedPGrant,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_RED_QESI, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_RED_QESI, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RedQESI,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_NEEDREPHRDC, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_NEEDREPHRDC, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::NeedRepHRDC,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_OCRDMYEAR, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_OCRDMYEAR, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::OCRdmYear,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_RESPLETTER, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_RESPLETTER, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::RESPLetter,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);
   AddControl ( CTRL_STATIC,
                IDC_STC_LBL_CALCULATED_CESG, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_CALCULATED_CESG, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::CESGAmount,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

   AddControl ( CTRL_STATIC, 
                IDC_STC_ACCTH_NAME, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::AIPAcctName,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

   // SAGES
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESREDAMT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESREDAMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESRedAmt,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESUCAMT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESUCAMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESUCAmt,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_SAGESACAMT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_SAGESACAMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::SAGESACAmt,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

   AddControl( CTRL_CHECKBOX, 
               IDC_RB_RESP_HISTORY, 
               CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, 
               IDC_RB_RESP_PENDING, 
               CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );

   //BCTESG
   AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_BCTESGPURAMT, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_BCTESGPURAMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::BCTESGGrant,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

    AddControl ( CTRL_STATIC, 
                IDC_STC_LBL_BCTESGREDAMT, 
                CTRLFLAG_GUI_FIELD);
    AddControl ( CTRL_STATIC, 
                IDC_STC_BCTESGREDAMT, 
                IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                ifds::BCTESGGrant,
                CTRLFLAG_DEFAULT,  
                IDC_LV_RESP_TRANSACTIONS);

   ConnectListToData (IDC_LV_RESP_TRANSACTIONS, true);
   showControlsForTransType ();
   doRefresh (this, NULL);
   
   return TRUE;
}
//******************************************************************************

void RESPTransactionsDlg::addControlsForSearchCriteria( )
{ 
   TRACE_METHOD( CLASSNAME, I_("addControlsForSearchCriteria") );

   AddControl (CTRL_COMBO, IDC_CMB_BEN_NAME, IFASTBP_PROC::RESP_CRITERIA, 
               ifds::RESPBenefId, CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   AddControl (CTRL_DATE, IDC_DTP_FROM_TRADEDATE, IFASTBP_PROC::RESP_CRITERIA, 
              ifds::FromDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE);

   AddControl (CTRL_DATE, IDC_DTP_TO_TRADEDATE, IFASTBP_PROC::RESP_CRITERIA, 
               ifds::ToDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE);

   AddControl (CTRL_COMBO, IDC_CMB_DESCRIPTION, IFASTBP_PROC::RESP_CRITERIA, 
               ifds::TransTypeDesc, CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   AddControl (CTRL_COMBO, IDC_CMB_TRANSFER_STATUS, IFASTBP_PROC::RESP_CRITERIA, 
               ifds::TfrStat, CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   AddControl (CTRL_COMBO, IDC_CMB_TRFER_TYPE, IFASTBP_PROC::RESP_CRITERIA, 
               ifds::RepHRDC, CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   ConnectControlsToData();
   LoadControls ();
}

//******************************************************************************

void RESPTransactionsDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, CLASSNAME, I_("ControlUpdated"));
	
	switch (controlID)
	{
		case IDC_DTP_FROM_TRADEDATE:
		case IDC_DTP_TO_TRADEDATE:
        {
			bool bValid = GetControl (controlID)->IsValid ();
            
			GetDlgItem (IDC_BTN_SEARCH)->EnableWindow (bValid);
			break;
        }
		
		default:
			break;
   }
   setUpdateFlag (false);
}

//******************************************************************************
bool RESPTransactionsDlg::doRefresh ( GenericInterface * rpGICaller, 
                                      const I_CHAR * szOriginalCommand)
{  
  	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "doRefresh" ) ); 

   bool bReturn = true;
   
   DisplayTitle();

   DString resp_TransListKey;

   getParameter (I_("RESP_TransListKey"), resp_TransListKey);
   
   if (resp_TransListKey.empty())
   {
      if (_strHistoryPendingMode == HISTORY)
      {
         DSTButton *checkHistBtn = 
            dynamic_cast<DSTButton*>( GetControl( IDC_RB_RESP_HISTORY ) );

         if (checkHistBtn)
         {
            checkHistBtn->SetCheck (1);
         }
         OnRbRESPHistory ();
      }
      else if (_strHistoryPendingMode == PENDING)
      {
         DSTButton *checkPendBtn = 
            dynamic_cast<DSTButton*>( GetControl( IDC_RB_RESP_PENDING ) );

         if (checkPendBtn)
         {
            checkPendBtn->SetCheck (1);
         }
         OnRbRESPPending ();
      }
   }
   else
   {
      if (dynamic_cast <IFDSListCtrl*> (GetList (IDC_LV_RESP_TRANSACTIONS))->SetSelectionWithSearch (&resp_TransListKey) > WARNING)
      {
// Display error
         ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
         bReturn = false;
      }
   }

   if (_strCaller == TRANS_HIST)
   {
      showCriteria (false);
      GetDlgItem (IDC_BTN_RESET)->EnableWindow (false);
   }

   return bReturn;
}

//******************************************************************************
void RESPTransactionsDlg::DisplayTitle()
{
   TRACE_METHOD( CLASSNAME, I_("DisplayTitle"));

   DString dstrShrNum, 
      dstrEntityName;

   // Get Entity Name
   if ( !_strAccountNumber.empty() ) 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
      getDataGroupId(), _strAccountNumber, dstrEntityName);

   SetShrAcctCaption (dstrShrNum, _strAccountNumber, dstrEntityName);
}

//******************************************************************************
void RESPTransactionsDlg::DoListItemChanged ( UINT listControlID,
                                              const DString &strKey, 
                                              bool isNewItem,
                                              bool bIsDummyItem)
{  
   switch (listControlID)
   {
      case IDC_LV_RESP_TRANSACTIONS:
         {
            enableBeneficiaryAllocation (IFASTBP_PROC::RESPTRANSACTIONS_LIST);
            enableTransfer (IFASTBP_PROC::RESPTRANSACTIONS_LIST);
            enablePSE (IFASTBP_PROC::RESPTRANSACTIONS_LIST);

            DString transType;

            getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::TransType, transType, false);
            showControlsForTransType (transType);
            break;
         }
      default:
         break;
   }
}

//******************************************************************************
void RESPTransactionsDlg::OnBtnAllocations () 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAllocations" ) ); 

   try
   {
	   DString dstrTransId, disableBeneAllocScreen, dstrHRDCRespPending;         
	   DString resp_TransListKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST);
	   getParent()->getField( this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::HRDCPending, dstrHRDCRespPending, false );
      
		if (_strHistoryPendingMode == PENDING)
      {
         disableBeneAllocScreen = I_("Y");
      }
      else
      {
         disableBeneAllocScreen = disableBeneAlloc (IFASTBP_PROC::RESPTRANSACTIONS_LIST) ? I_("Y") : I_("N");
      }

      getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::TransId, dstrTransId, false);					
      setParameter (TRANSID, dstrTransId);
      setParameter (HISTORY_PENDING_FIELD, _strHistoryPendingMode);
      setParameter (I_("AccountNum"), _strAccountNumber);
      setParameter (I_("Caller"), CLASSNAME);
      setParameter (I_("RESP_TransListKey"), resp_TransListKey);
      setParameter (I_("DisableScreen"), disableBeneAllocScreen);
	  setParameter (I_("HRDCPending"), dstrHRDCRespPending);

      switch (invokeCommand (getParent(), CMD_BPROC_RESP_BENEF_ALLOCATION_LIST, PROC_NO_TYPE , true, NULL))
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
               break;
            default:
               // Display error
               ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
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
void RESPTransactionsDlg::OnBtnTransfer () 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnTransfer" ) ); 

   try
   {
      DString dstrTransId, dstrTransType, dstrDepositType, dstrRedCode;
      DString resp_TransListKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST);

	  getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::TransId, dstrTransId, false);	
	  getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::TransType, dstrTransType, false);
	  getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::DepositType, dstrDepositType, false);
	  getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::RedCode, dstrRedCode, false);

	  setParameter (TRANSID, dstrTransId);
	  setParameter (HISTORY_PENDING_FIELD, _strHistoryPendingMode);
	  setParameter (I_("AccountNum"), _strAccountNumber);
	  setParameter (I_("Caller"), CLASSNAME);
	  setParameter (I_("RESP_TransListKey"), resp_TransListKey);
	  setParameter (I_("TransType"), dstrTransType);
	  setParameter (I_("DepositType"), dstrDepositType);
	  setParameter (I_("RedCode"), dstrRedCode);

      switch (invokeCommand (getParent(), CMD_BPROC_RESP_TRANSFER, PROC_NO_TYPE , true, NULL))
      {
      case CMD_OK:
      case CMD_CANCEL:
      case CMD_MODELESS_INPROCESS:
         break;
      default:
         // Display error
         ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
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
void RESPTransactionsDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));

   CWaitCursor wait;
   SetMessageStatusBar (TXT_LOAD_RESPTRANSACTIONS);

   const DString *crtKey = &getParent()->getCurrentListItemKey (this, 
      IFASTBP_PROC::RESPTRANSACTIONS_LIST);

   if (getParent()->performSearch(this, 
                                  IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
                                  SEARCH_NEXT_BLOCK) <= WARNING)
   {
      LoadListControl (IDC_LV_RESP_TRANSACTIONS);
      if (*crtKey != NULL_STRING)
      {
         GetList (IDC_LV_RESP_TRANSACTIONS)->SetSelection (crtKey);
      }
   }
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST));
   SetMessageStatusBar (NULL_STRING); 
}

//******************************************************************************

void RESPTransactionsDlg::OnBtnSearch() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnSearch"));

   GetDlgItem(IDC_BTN_SEARCH)->SetFocus();

   CWaitCursor wait;

   if (getParent()->performSearch(this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, 
      SEARCH_START) <= WARNING) // ivanka
   {
      LoadListControl (IDC_LV_RESP_TRANSACTIONS);

      const DString *crtKey = &getParent()->getCurrentListItemKey (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST);

      if (*crtKey != NULL_STRING)
      {
         GetList (IDC_LV_RESP_TRANSACTIONS)->SetSelection (crtKey);
      }
   }

   showCriteria (false);

   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST));

   
   int itemCount = GetList (IDC_LV_RESP_TRANSACTIONS)->GetItemCount ();
   GetDlgItem (IDC_BTN_RESP_TRANSACTIONS)->EnableWindow (itemCount > 0);
}

//******************************************************************************

void RESPTransactionsDlg::OnBtnReset () 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));

   GetDlgItem(IDC_BTN_RESET)->SetFocus();

   CWaitCursor wait;

   showCriteria (true);

   getParent()->reset(this, IFASTBP_PROC::RESP_CRITERIA);
   getParent()->reset(this, IFASTBP_PROC::RESPTRANSACTIONS_LIST);

   DString transType = NULL_STRING;
   showControlsForTransType (transType);

   GetDlgItem (IDC_BTN_MORE)->EnableWindow (false);	

   DSTListCtrl *pRESPTransListCtrl = GetList(IDC_LV_RESP_TRANSACTIONS);

   if (pRESPTransListCtrl)
   {
      pRESPTransListCtrl->DeleteAllItems();
   }

   ReregisterObservers();

   ConnectControlsToData();
   LoadControls(IFASTBP_PROC::RESP_CRITERIA);

   GetDlgItem (IDC_BTN_RESP_TRANSACTIONS)->EnableWindow(false);
   GetDlgItem (IDC_BTN_ALLOCS)->EnableWindow(false);
   GetDlgItem (IDC_BTN_TRANSFER)->EnableWindow(false);
   GetDlgItem (IDC_BTN_PSEEAP)->EnableWindow(false);

}

//******************************************************************************
void RESPTransactionsDlg::showCriteria (bool bEnable)
{
   TRACE_METHOD( CLASSNAME, I_( "showCriteria" ) );

   GetDlgItem (IDC_BTN_SEARCH)->EnableWindow (bEnable);
   GetDlgItem (IDC_CMB_BEN_NAME)->EnableWindow (bEnable);
   GetDlgItem (IDC_DTP_FROM_TRADEDATE)->EnableWindow (bEnable);
   GetDlgItem (IDC_DTP_TO_TRADEDATE)->EnableWindow (bEnable);
   GetDlgItem (IDC_CMB_DESCRIPTION)->EnableWindow (bEnable);
   GetDlgItem (IDC_CMB_TRANSFER_STATUS)->EnableWindow (bEnable);
   GetDlgItem (IDC_CMB_TRFER_TYPE)->EnableWindow (bEnable);

   //radio buttons
   GetDlgItem(IDC_RB_RESP_HISTORY)->EnableWindow (bEnable);
   GetDlgItem(IDC_RB_RESP_PENDING)->EnableWindow (bEnable);

   if (bEnable)
   {
      CButton* pRB = (CButton*) GetDlgItem(IDC_RB_RESP_HISTORY);
      pRB->SetCheck(1);
      pRB = (CButton*) GetDlgItem(IDC_RB_RESP_PENDING);
      pRB->SetCheck(0);

      OnRbRESPHistory ();
   }

   GetDlgItem(IDC_CMB_BEN_NAME)->SetFocus();
}

//******************************************************************************
void RESPTransactionsDlg::OnBtnRESPTransactions() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnRESPTransactions" ) ); 

   DString dstrTransId;

   setParameter (ACCOUNT_NUMBER_FIELD, _strAccountNumber);
   setParameter (I_("Pending"), ( _strHistoryPendingMode == RESPTRANSACTIONSNAMES::HISTORY) ? I_("N") : I_("Y"));
   getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::TransId, dstrTransId, false);
   setParameter (I_("TransId"), dstrTransId);
   setParameter (I_( "ReqTransid" ), dstrTransId);
   SetMessageStatusBar( TXT_LOAD_TRANSACTION_PENDING );
   switch (invokeCommand (getParent(), CMD_BPROC_TRANS_HISTORY, PROC_NO_TYPE, false, NULL)) //modeless
   {
      case CMD_OK:
      case CMD_CANCEL:
      case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
   }
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void RESPTransactionsDlg::OnBtnPSEEAP () 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnPSEEAP")); 

   CWaitCursor wait;

   DString transId;

   getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::TransId, transId, false);

   setParameter (I_("Caller"), CLASSNAME);
   setParameter (I_("AccountNum"), _strAccountNumber);
   setParameter (I_("TransId"), transId);
   switch (invokeCommand (getParent(), CMD_BPROC_PSE_EAP, PROC_NO_TYPE, true, NULL)) //modal
   {
      case CMD_OK:
      case CMD_CANCEL:
      case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
   }
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void RESPTransactionsDlg::OnRbRESPHistory () 
{
   TRACE_METHOD( CLASSNAME, I_("OnRbRESPHistory"));
   
   CWaitCursor wait;
   DSTButton *checkHistBtn = 
      dynamic_cast<DSTButton*> (GetControl (IDC_RB_RESP_HISTORY));

   if (checkHistBtn && checkHistBtn->GetCheck ())
   {
      DSTButton *checkPendBtn = 
         dynamic_cast<DSTButton*> (GetControl (IDC_RB_RESP_PENDING));

      checkPendBtn->SetCheck (0);
      _strHistoryPendingMode = HISTORY;

      getParent()->setField(this, IFASTBP_PROC::RESP_CRITERIA, ifds::HistoryPending, _strHistoryPendingMode, false);

      setParameter (HISTORY_PENDING_FIELD, _strHistoryPendingMode);

      if (_strCaller == TRANS_HIST)
      {
         // if screen is called from transaction history display data
         getParent()->performSearch (NULL, BF::NullContainerId, SEARCH_START); //reloading the list with transactions history.
         LoadListControl (IDC_LV_RESP_TRANSACTIONS);
         GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST));
      }

      int itemCount = GetList (IDC_LV_RESP_TRANSACTIONS)->GetItemCount ();

      if (itemCount <= 0)
      {
         GetDlgItem (IDC_BTN_ALLOCS)->EnableWindow (false);
         GetDlgItem (IDC_BTN_TRANSFER)->EnableWindow (false);
         GetDlgItem (IDC_BTN_PSEEAP)->EnableWindow (false);
      }
      GetDlgItem (IDC_BTN_RESP_TRANSACTIONS)->EnableWindow (itemCount > 0);
   }
}

//******************************************************************************
void RESPTransactionsDlg::OnRbRESPPending() 
{
   TRACE_METHOD( CLASSNAME, I_("OnRbRESPPending"));
   
   CWaitCursor wait;
   DSTButton *checkPendBtn = 
      dynamic_cast<DSTButton*> (GetControl (IDC_RB_RESP_PENDING));

   if (checkPendBtn && checkPendBtn->GetCheck ())
   {
      DSTButton *checkHistBtn = 
         dynamic_cast<DSTButton*> (GetControl (IDC_RB_RESP_HISTORY));

      checkHistBtn->SetCheck (0);
      _strHistoryPendingMode = RESPTRANSACTIONSNAMES::PENDING;

      getParent()->setField(this, IFASTBP_PROC::RESP_CRITERIA, ifds::HistoryPending, _strHistoryPendingMode, false);

      setParameter( HISTORY_PENDING_FIELD, _strHistoryPendingMode );

      if (_strCaller == TRANS_HIST)
      {
         // if screen is called from transaction history display data
         getParent()->performSearch (NULL, BF::NullContainerId, SEARCH_START); //reloading the list with pending transactions.
         LoadListControl (IDC_LV_RESP_TRANSACTIONS);
         GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST));
      }

      int itemCount = GetList (IDC_LV_RESP_TRANSACTIONS)->GetItemCount ();

      if (itemCount <= 0)
      {
         GetDlgItem (IDC_BTN_ALLOCS)->EnableWindow (false);
         GetDlgItem (IDC_BTN_TRANSFER)->EnableWindow (false);
         GetDlgItem (IDC_BTN_PSEEAP)->EnableWindow (false);
      }
      GetDlgItem (IDC_BTN_RESP_TRANSACTIONS)->EnableWindow (itemCount > 0);
   }
}

//******************************************************************************
bool RESPTransactionsDlg::GetOverrideItemString( long lSubstituteId, const DString& ColumnKey, DString& strOut )
{
   if( lSubstituteId == ifds::RESPTransactionHeadingSet.getId() )
   {
   }
   return(false);
}

//******************************************************************************
void RESPTransactionsDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 
    
    GetDlgItem (IDC_BTN_MORE)->EnableWindow (false);
}

//************************************************************************************
void RESPTransactionsDlg::enableBeneficiaryAllocation (const BFContainerId& idContainer)
{
   DString dstrTransType,
      dstrDepositType;

   int iItemNumber = getParent()->getNumberOfItemsInList( this, idContainer);

   if (iItemNumber > 0)
   {
		getParent()->getField (this, idContainer, ifds::TransType,  dstrTransType, false);      	
		getParent()->getField( this, idContainer, ifds::DepositType, dstrDepositType, false);
   }

   bool bCanHaveAllocations = false;

   if (dstrTransType == ED)
   {
      bCanHaveAllocations = dstrDepositType == CASH || dstrDepositType == PAC ? true : false;
   }
   else if (dstrTransType == TI || dstrTransType == TR)
   {
      DString dstrRedemptionCode;
      getParent()->getField( this, idContainer, ifds::RedCode, dstrRedemptionCode, false);

      bool bRESPTransfer = (dstrRedemptionCode == I_("64") || dstrRedemptionCode == I_("65") || 
                            dstrRedemptionCode == I_("66") || dstrRedemptionCode == I_("67") ||
							dstrRedemptionCode == I_("79") || dstrRedemptionCode == I_("80")) ? true : false;

      bCanHaveAllocations = dstrDepositType == CASH && !bRESPTransfer ? true : false;
   }

   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

   assert (pDSTCWorkSession);
   GetDlgItem (IDC_BTN_ALLOCS)->EnableWindow (bCanHaveAllocations &&
      pDSTCWorkSession->hasReadPermission (UAF::RESP_BENEFICIARY_ALLOCATION));
}

//************************************************************************************
bool RESPTransactionsDlg::disableBeneAlloc (const BFContainerId& idContainer)
{
   bool bEnable = false;

   DString dstrCancelled,
      dstrReversed,
      dstrHRDCRespPending;

   getParent()->getField( this, idContainer, ifds::Reversal, dstrReversed, false );
   getParent()->getField( this, idContainer, ifds::Cancelled, dstrCancelled, false );
   getParent()->getField( this, idContainer, ifds::HRDCPending, dstrHRDCRespPending, false );

   dstrCancelled.strip().upperCase();
   dstrReversed.strip().upperCase();
   dstrHRDCRespPending.strip().upperCase();

   bEnable = dstrCancelled == NO && dstrReversed == NO && dstrHRDCRespPending == NO;

   return !bEnable;
}

//************************************************************************************
void RESPTransactionsDlg::enableTransfer (const BFContainerId& idContainer)
{
	bool bEnable = false;

	DString dstrDepositType;
	DString dstrRedemptionCode;
   
	int iItemNumber = getParent()->getNumberOfItemsInList( this, idContainer);

   if (iItemNumber > 0)
   {
		getParent()->getField( this, idContainer, ifds::DepositType, dstrDepositType, false);
		getParent()->getField( this, idContainer, ifds::RedCode, dstrRedemptionCode, false);
   }

	bEnable = dstrDepositType == I_("17") || (dstrRedemptionCode == I_("64") || dstrRedemptionCode == I_("65")) ? true : false;

   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

	GetDlgItem (IDC_BTN_TRANSFER)->EnableWindow ( bEnable &&
                                                 pDSTCWorkSession->hasReadPermission (UAF::RESP_TRANSFER));		
}

//******************************************************************************
void RESPTransactionsDlg::enablePSE (const BFContainerId& idContainer)
{
	bool bEnable = false;

	DString redCode;
   
	int iItemNumber = getParent()->getNumberOfItemsInList( this, idContainer);

    if (iItemNumber > 0)
    {
		getParent()->getField (this, idContainer, ifds::RedCode, redCode, false);
	}

	GetDlgItem (IDC_BTN_PSEEAP)->EnableWindow (DSTCommonFunctions::codeInList (redCode, I_("61,69,77,84,85")));		
}

//******************************************************************************
void RESPTransactionsDlg::showControlsForTransType (const DString& transType /*=NULL_STRING*/)
{
   DString dstrRedemptionCode, dstrDepositType;

   if (!transType.empty ())
   {
		getParent()->getField( this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::RedCode, dstrRedemptionCode, false);
		getParent()->getField (this, IFASTBP_PROC::RESPTRANSACTIONS_LIST, ifds::DepositType, dstrDepositType, false);
   }

   bool bShowPur = transType == I_("ED") || transType == I_("TI");
   bool bShowRed = transType == I_("PW") || transType == I_("TO");
   bool bAIPRed = DSTCommonFunctions::codeInList (dstrRedemptionCode, I_("66,67,79,80"));
   bool bShowTansfer = DSTCommonFunctions::codeInList (dstrRedemptionCode, I_("66,67,79,80")) && transType == I_("TR");
  
   //purchase
   GetControl (IDC_STC_PURCH)->Show (bShowPur);
   GetControl (IDC_STC_LBL_DEPOSIT_TYPE)->Show (bShowPur);
   GetControl (IDC_STC_DEPOSIT_TYPE)->Show (bShowPur);
   GetControl (IDC_STC_LBL_CESG_AMOUNT)->Show (bShowPur);
   GetControl (IDC_STC_CESGCALC)->Show (bShowPur);
   GetControl (IDC_STC_LBL_CLB_AMOUNT)->Show (bShowPur);
   GetControl (IDC_STC_CLB_AMOUNT)->Show (bShowPur);
   GetControl (IDC_STC_LBL_PUR_ADD)->Show (bShowPur);
   GetControl (IDC_STC_ADDTL_CESG_AMT)->Show (bShowPur);
   GetControl (IDC_STC_LBL_ALBERTA_PGRANT)->Show (bShowPur);
   GetControl (IDC_STC_ALBERTA_PGRANT)->Show (bShowPur);
   GetControl (IDC_STC_LBL_PUR_QESI)->Show (bShowPur);
   GetControl (IDC_STC_QESI_BASIC)->Show (bShowPur);
   GetControl (IDC_STC_LBL_ADDTL_QESI)->Show (bShowPur);
   GetControl (IDC_STC_ADDTL_QESI)->Show (bShowPur);
   GetControl (IDC_STC_LBL_GR_REPAY_REASON)->Show (bShowPur);
   GetControl (IDC_STC_GR_PAYMENT_REASON)->Show (bShowPur);
   GetControl (IDC_STC_LBL_PURCH_GRANT_REPAY)->Show (bShowPur);
   GetControl (IDC_STC_PURHC_GRANT_REPAYMENT)->Show (bShowPur);
   GetControl (IDC_STC_RES_CESG)->Show (bShowPur);
   GetControl (IDC_STC_LBL_SAGESPURAMT)->Show (bShowPur);
   GetControl (IDC_STC_SAGESPURAMT)->Show (bShowPur);

//redemption
   GetControl (IDC_STC_REDEEM)->Show (bShowRed);
   GetControl (IDC_STC_LBL_RED_CODE)->Show (bShowRed);
   GetControl (IDC_STC_RED_CODE)->Show (bShowRed);

   GetControl (IDC_STC_LBL_GRANT_REPAYABLE)->Show (bShowRed);
   GetControl (IDC_STC_GRANTREPAYABLE)->Show (bShowRed);
   GetControl (IDC_STC_LBL_GRANT_REPAY_REASON)->Show (bShowRed);
   GetControl (IDC_STC_GRREPAYREASON)->Show (bShowRed);
   GetControl (IDC_STC_LBL_RED_INCOME)->Show (bShowRed);
   GetControl (IDC_STC_RED_INCOME)->Show (bShowRed);
   GetControl (IDC_STC_LBL_RED_CLB)->Show (bShowRed);
   GetControl (IDC_STC_RED_CLB)->Show (bShowRed);
   GetControl (IDC_STC_LBL_RED_CESG)->Show (bShowRed);
   GetControl (IDC_STC_RED_CESG)->Show (bShowRed);
   GetControl (IDC_STC_LBL_RED_ALBERTA_PGRANT)->Show (bShowRed);
   GetControl (IDC_STC_RED_ALBERTA_PGRANT)->Show (bShowRed);
   GetControl (IDC_STC_LBL_RED_QESI)->Show (bShowRed);
   GetControl (IDC_STC_RED_QESI)->Show (bShowRed);
   GetControl (IDC_STC_LBL_NEEDREPHRDC)->Show (bShowRed);
   GetControl (IDC_STC_NEEDREPHRDC)->Show (bShowRed);
   GetControl (IDC_STC_LBL_OCRDMYEAR)->Show (bShowRed);
   GetControl (IDC_STC_OCRDMYEAR)->Show (bShowRed);
   GetControl (IDC_STC_LBL_RESPLETTER)->Show (bShowRed);
   GetControl (IDC_STC_RESPLETTER)->Show (bShowRed);
   GetControl (IDC_STC_LBL_CALCULATED_CESG)->Show (bShowRed);
   GetControl (IDC_STC_CALCULATED_CESG)->Show (bShowRed);
   GetControl (IDC_STC_ACCTH_NAME)->Show (bShowRed && bAIPRed);
   GetControl (IDC_STC_AIP)->Show (bShowRed && bAIPRed);
   GetControl (IDC_STC_LBL_SAGESREDAMT)->Show (bShowRed);
   GetControl (IDC_STC_SAGESREDAMT)->Show (bShowRed);

   //BCTESG
   GetControl (IDC_STC_LBL_BCTESGPURAMT)->Show (bShowPur);
   GetControl (IDC_STC_BCTESGPURAMT)->Show (bShowPur);
   GetControl (IDC_STC_LBL_BCTESGREDAMT)->Show (bShowRed);
   GetControl (IDC_STC_BCTESGREDAMT)->Show (bShowRed);

   //transfer
   if (bShowTansfer)
   {
      GetControl (IDC_STC_REDEEM)->Show (bShowTansfer);
      GetControl (IDC_STC_LBL_RED_CODE)->Show (bShowTansfer);
      GetControl (IDC_STC_RED_CODE)->Show (bShowTansfer);
      GetControl (IDC_STC_ACCTH_NAME)->Show (bShowTansfer);
      GetControl (IDC_STC_AIP)->Show (bShowTansfer);
   }

   bool bShow = bShowPur || bShowRed ? true : false;
   
   GetControl (IDC_STC_SETTLEDATE)->Show (bShow);
   GetControl (IDC_STC_ACAMT)->Show (bShow);
   GetControl (IDC_STC_UCAMT)->Show (bShow);
   GetControl (IDC_STC_GRANTTRANSID)->Show (bShow);
   GetControl (IDC_STC_TRANSSTATUS)->Show (bShow);
   GetControl (IDC_STCREPORTEDHRDC)->Show (bShow);
   GetControl (IDC_STC_NET_AMT)->Show (bShow);
   GetControl (IDC_STC_UCREASON)->Show (bShow);
   GetControl (IDC_STC_TAX_YEAR)->Show (bShow);
   GetControl (IDC_STC_REJCODE)->Show (bShow);
   GetControl (IDC_STC_HRDCTRANSID)->Show (bShow);
 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RESPTransactionsDlg.cpp-arc  $
 * 
 *    Rev 1.60   Oct 18 2011 04:26:32   wutipong
 * IN2582912 - PSE, RESP Trfr, Bene Alloc and Transaction button enabled after resetting search.
 * 
 *    Rev 1.59   Jun 28 2011 10:06:54   panatcha
 * P0184541_FN01_InvescoQESItrans
 * 
 *    Rev 1.58   Jan 13 2011 12:35:32   jankovii
 * IN 2371165 - Field values are not displayed in RESP Trans Hist scr for AIP all fund transfer
 * 
 *    Rev 1.57   Nov 29 2010 16:09:30   jankovii
 * Sunc up: Display issue.
 * 
 *    Rev 1.56   Nov 19 2010 15:15:26   jankovii
 * IN 2323038 - FN03-RESP Notional Transfer Completed.
 * 
 *    Rev 1.55   Nov 10 2010 15:18:06   jankovii
 * Sync up: IN 2318372- FN03- RESP Transaction History Screen
 * 
 *    Rev 1.54   Nov 10 2010 04:12:38   dchatcha
 * PET0165541 FN03 - QESI Phase3 - Removed not necessary pieces of code.
 * 
 *    Rev 1.53   Nov 08 2010 16:01:52   popescu
 * IN 2297013 - FN03 -  fixed bene alloc should be disabled for pending
 * 
 *    Rev 1.52   Nov 05 2010 16:07:28   popescu
 * IN 2297013 - FN03 -  Fixed the discard dialog.
 * 
 *    Rev 1.51   Nov 04 2010 15:05:06   jankovii
 * Sync up: IN 2297013 - FN03 -  RESP Transaction History Trade date filters
 * 
 *    Rev 1.50   Nov 02 2010 14:27:34   jankovii
 * Sync up: IN 2311933 - FN03 -  RESP Transaction History Trade date filters
 * 
 *    Rev 1.49   Oct 29 2010 06:39:00   kitticha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.48   Oct 28 2010 11:11:34   jankovii
 * IN 2297013 - RESP AIP for Joint Account - trade entry issues
 * 
 *    Rev 1.47   Sep 29 2010 11:30:12   jankovii
 * PET0175377 FN01 - AIP for Joint RESP Account
 * 
 *    Rev 1.46   Sep 24 2010 14:29:04   jankovii
 * PET0175377 FN01 - AIP for Joint RESP Account
 * 
 *    Rev 1.45   Sep 15 2010 13:41:54   jankovii
 * PET165541 FN03 SOC14 & SOC6.
 * 
 *    Rev 1.44   Aug 20 2010 14:16:06   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.43   Aug 19 2010 10:44:32   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.42   Aug 11 2010 19:37:48   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.41   Aug 09 2010 16:14:00   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.40   Aug 06 2010 14:06:38   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.39   Jun 21 2010 17:20:30   popescu
 * Incident 2162449 - REL Pre99 Bene Alloc button grayed out on RESP Transaction History Screen
 * 
 *    Rev 1.38   Jun 09 2010 15:12:56   jankovii
 * IN 2131626 - PETP0165541 -  Mapping Issues on the RESP Trans History Screen.
 * 
 *    Rev 1.37   Jun 09 2010 03:23:58   dchatcha
 * IN# 2143974 - QESI - PET#165541 - reason code missing from grant payment field.
 * 
 *    Rev 1.36   May 13 2010 01:33:18   popescu
 * RESP-QESI fixes
 * 
 *    Rev 1.35   May 12 2010 06:10:48   popescu
 * RESP/QESI - fixed description of Grant Repayment Reason 
 * 
 *    Rev 1.34   May 11 2010 15:51:36   popescu
 * RESP - QESI - adding the calculated CESG amount field
 * 
 *    Rev 1.33   May 11 2010 12:31:52   popescu
 * RESP - fixed the CESG amount assignment 
 * 
 *    Rev 1.32   May 11 2010 12:17:36   popescu
 * QESI - RESP fixing permission
 * 
 *    Rev 1.31   May 11 2010 08:19:32   popescu
 * QESI - RESP Fixes
 * 
 *    Rev 1.30   May 03 2010 19:40:52   popescu
 * PET165541_FN01_QESI - RESP Gap - small fixes
 * 
 *    Rev 1.29   Apr 27 2010 16:27:54   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.28   Apr 23 2010 16:11:10   jankovii
 * PET0165541 FN01 QESI RESP Trading
 * 
 *    Rev 1.27   Apr 21 2010 17:21:18   popescu
 * RESP-QESI Resp transfer screen
 * 
 *    Rev 1.26   Apr 16 2010 18:28:08   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.25   Apr 15 2010 10:32:22   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.24   Apr 12 2010 10:17:16   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - Trading History Dialog button fixes...
 * 
 *    Rev 1.23   Apr 09 2010 14:44:34   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog - fixed refresh issue when updating allocations
 * 
 *    Rev 1.22   Apr 01 2010 16:23:44   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog
 * 
 *    Rev 1.21   Apr 01 2010 00:48:04   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog
 * 
 *    Rev 1.20   Mar 31 2010 16:02:10   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.18   Mar 30 2010 19:02:02   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.17   Mar 30 2010 16:38:18   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.16   Mar 29 2010 22:51:16   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.15   Mar 29 2010 10:49:40   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.14   25 Nov 2008 16:39:30   popescu
 * Incident  1496411 - fixed the more button in the RESP screen
 * 
 *    Rev 1.12   Jul 25 2008 18:37:50   daechach
 * in#1089944 - iFast/Desktop RESP Transaction History Screen
 * 
 *    Rev 1.11   Sep 15 2005 15:15:00   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.10   Aug 12 2005 10:47:08   Fengyong
 * Incident #378438 - field type fix
 * 
 *    Rev 1.9   Jun 24 2005 17:00:28   Fengyong
 * PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.8   Mar 21 2003 18:40:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:56:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Sep 30 2002 11:01:42   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.5   22 May 2002 19:16:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   27 Mar 2002 20:01:20   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.3   Jan 28 2002 11:28:12   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.2   Jun 07 2001 11:40:38   YINGBAOL
 * fix refresh issue
 * 
 *    Rev 1.1   Mar 22 2000 09:02:48   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.5   Mar 06 2000 10:55:14   PETOLESC
// Added the hllapi call.
// 
//    Rev 1.4   Mar 02 2000 12:00:08   PETOLESC
// Corrected qa issues.
// 
//    Rev 1.3   Feb 16 2000 10:06:46   PETOLESC
// Included the list in MFAccount.
// 
//    Rev 1.2   Feb 10 2000 17:11:20   PETOLESC
// Removed RESPAccInfo buton.
// 
//    Rev 1.1   Feb 07 2000 11:02:32   PETOLESC
// Minor corrections and code cleaning.
// 
//    Rev 1.0   Dec 29 1999 17:23:50   PETOLESC
// Initial revision.
 * 
 *
 */

