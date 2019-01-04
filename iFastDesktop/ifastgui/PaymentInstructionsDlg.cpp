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
// ^FILE   : PaymentInstructionsDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// ----------------------------------------------------------
//
// ^CLASS    : PaymentInstructionsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "paymentinstructionsdlg.h"
#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\paymentinstructionsprocessincludes.h>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\dstbutton.h>
#include <uibase\dstlistctrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_IDENT_ACC;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_PAYMENT_INSTRUCTIONS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<PaymentInstructionsDlg> dlgCreator(CMD_GUI_PAYMENT_INSTRUCTIONS);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("PaymentInstructionsDlg");
   const I_CHAR *LV_PAYMENT_INSTRUCTIONS_LIST = I_("PaymentInstructionsList");
   const I_CHAR *LV_BANK_INSTRUCTIONS_LIST = I_("BankInstructionsList");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   //extern const long GUI_NO_PAYMENTINSTRUCTION_IN_LIST;
}
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const PAYMENT_INSTRUCTIONS;
}

namespace PAY_TO
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
	extern CLASS_IMPORT I_CHAR * const CLIENT;
}


namespace PAYMENT_FOR
{
   extern CLASS_IMPORT const I_CHAR * TRAILER_FEE;
   extern CLASS_IMPORT const I_CHAR * COMMISSION;
}

namespace AcctUseCode
{
	extern CLASS_IMPORT const I_CHAR * const COMMISSION;
	extern CLASS_IMPORT const I_CHAR * const TRAILER_FEE;
}

namespace ifds
{
   //field ids used   
   extern CLASS_IMPORT const BFTextFieldId HasNegativeComm; 
	extern CLASS_IMPORT const BFTextFieldId ClientName;
}

class LVBankInstructionsData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVBankInstructionsData() {}
   DString BankIdValue_;
   DString InstName_;
   DString BankAcctNum_;
   DString BankIdType_;
   DString AcctUseCode_;
   DString BankAcctCurrency_;
   DString Status_;
	DString AccountNum_;
	DString VerifyStatus_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BankIdValue, BankIdValue_);
      BankIdValue_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::InstName, InstName_);
      InstName_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BankAcctNum, BankAcctNum_);
      BankAcctNum_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BankIdType, BankIdType_);
      BankIdType_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::AcctUseCode, AcctUseCode_);
      AcctUseCode_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BankAcctCurrency, BankAcctCurrency_);
      BankAcctCurrency_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::Status, Status_);
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::AccountNum, AccountNum_);
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::VerifyStat, VerifyStatus_);

   }
};

class LVBankInstructionsAdapter : public IFDSListCtrlAdapter< LVBankInstructionsData >
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
      else if (*pFieldId == ifds::BankIdValue) 
      {
         result = i_strcmp(pData1->BankIdValue_.c_str(), pData2->BankIdValue_.c_str());
      } 
      else if (*pFieldId == ifds::InstName) 
      {
         result = i_strcmp(pData1->InstName_.c_str(), pData2->InstName_.c_str());
      } 
      else if (*pFieldId == ifds::BankAcctNum) 
      {
         result = i_strcmp(pData1->BankAcctNum_.c_str(), pData2->BankAcctNum_.c_str());
      } 
      else if (*pFieldId == ifds::BankIdType) 
      {
         result = i_strcmp(pData1->BankIdType_.c_str(), pData2->BankIdType_.c_str());
      } 
      else if (*pFieldId == ifds::AcctUseCode) 
      {
         result = i_strcmp(pData1->AcctUseCode_.c_str(), pData2->AcctUseCode_.c_str());
      } 
      else if (*pFieldId == ifds::BankAcctCurrency) 
      {
         result = i_strcmp(pData1->BankAcctCurrency_.c_str(), pData2->BankAcctCurrency_.c_str());
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
         else if (*pFieldId == ifds::BankIdValue) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BankIdValue_.c_str();
         } 
         else if (*pFieldId == ifds::InstName) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->InstName_.c_str();
         } 
         else if (*pFieldId == ifds::BankAcctNum) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BankAcctNum_.c_str();
         } 
         else if (*pFieldId == ifds::BankIdType)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BankIdType_.c_str();
         } 
         else if (*pFieldId == ifds::AcctUseCode)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->AcctUseCode_.c_str();
         } 
         else if (*pFieldId == ifds::BankAcctCurrency)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BankAcctCurrency_.c_str();
         } 
         else if (*pFieldId == ifds::Status)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->Status_.c_str();
         } 
		 else if (*pFieldId == ifds::VerifyStat)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->VerifyStatus_.c_str();
         } 
         else if (*pFieldId == ifds::AccountNum)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->AccountNum_.c_str();
         } 
         return (1);
      }
      return (0);
   }
};

class LVPaymentInstructionsData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVPaymentInstructionsData() {}
   DString PaymentFor_;
   DString PayType_;
   DString PayMethod_;
   DString ACHProcessor_;
   DString BankChrgs_;
   DString CurrencyOption_;
   DString Currency_;
   DString UseEntityAddress_;
	DString ConsolType_;
	DString EffectiveDate_;
	DString StopDate_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::PaymentFor, PaymentFor_);
      PaymentFor_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::PayType, PayType_);
      PayType_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::PayMethod, PayMethod_);
      PayMethod_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::ACHProcessor, ACHProcessor_);
      ACHProcessor_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BankChrgs, BankChrgs_);
      BankChrgs_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::CurrencyOption, CurrencyOption_);
      CurrencyOption_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::Currency, Currency_);
      Currency_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::UseEntityAddress, UseEntityAddress_);
      UseEntityAddress_.strip();
		pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::ConsolType, ConsolType_);
      ConsolType_.strip();
		pDlg->getParent()->getField(pDlg, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::EffectiveDate, EffectiveDate_);
      EffectiveDate_.strip();
		pDlg->getParent()->getField(pDlg, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::StopDate, StopDate_);
      StopDate_.strip();
   }
};

class LVPaymentInstructionsAdapter : public IFDSListCtrlAdapter< LVPaymentInstructionsData >
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
      else if (*pFieldId == ifds::PaymentFor) 
      {
         result = i_strcmp(pData1->PaymentFor_.c_str(), pData2->PaymentFor_.c_str());
      } 
      else if (*pFieldId == ifds::PayMethod) 
      {
         result = i_strcmp(pData1->PayMethod_.c_str(), pData2->PayMethod_.c_str());
      } 
      else if (*pFieldId == ifds::ACHProcessor) 
      {
         result = i_strcmp(pData1->ACHProcessor_.c_str(), pData2->ACHProcessor_.c_str());
      } 
      else if (*pFieldId == ifds::BankChrgs) 
      {
         result = i_strcmp(pData1->BankChrgs_.c_str(), pData2->BankChrgs_.c_str());
      } 
      else if (*pFieldId == ifds::Currency) 
      {
         result = i_strcmp(pData1->Currency_.c_str(), pData2->Currency_.c_str());
      } 
      else if (*pFieldId == ifds::CurrencyOption) 
      {
         result = i_strcmp(pData1->CurrencyOption_.c_str(), pData2->CurrencyOption_.c_str());
      } 
      else if (*pFieldId == ifds::UseEntityAddress) 
      {
         result = i_strcmp(pData1->UseEntityAddress_.c_str(), pData2->UseEntityAddress_.c_str());
      } 
		else if (*pFieldId == ifds::ConsolType) 
      {
         result = i_strcmp(pData1->ConsolType_.c_str(), pData2->ConsolType_.c_str());
      }
		 else if( *pFieldId == ifds::EffectiveDate ) 
		{
			if ( DSTCommonFunctions::CompareDates( pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = -1;
			else if ( DSTCommonFunctions::CompareDates( pData2->EffectiveDate_.c_str(), pData1->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = 1;
		}
		else if( *pFieldId == ifds::StopDate ) 
		{
			if ( DSTCommonFunctions::CompareDates( pData1->StopDate_.c_str(), pData2->StopDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = -1;
			else if ( DSTCommonFunctions::CompareDates( pData2->StopDate_.c_str(), pData1->StopDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = 1;
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
         else if (*pFieldId == ifds::PaymentFor) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->PaymentFor_.c_str();
         } 
         else if (*pFieldId == ifds::PayType) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->PayType_.c_str();
         } 
         else if (*pFieldId == ifds::PayMethod) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->PayMethod_.c_str();
         } 
         else if (*pFieldId == ifds::ACHProcessor)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ACHProcessor_.c_str();
         } 
         else if (*pFieldId == ifds::BankChrgs)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BankChrgs_.c_str();
         } 
         else if (*pFieldId == ifds::CurrencyOption)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->CurrencyOption_.c_str();
         } 
         else if (*pFieldId == ifds::Currency)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->Currency_.c_str();
         } 
         else if (*pFieldId == ifds::UseEntityAddress)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->UseEntityAddress_.c_str();
         } 
			else if (*pFieldId == ifds::ConsolType)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ConsolType_.c_str();
         }
			else if( *pFieldId == ifds::EffectiveDate ) 
			{
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         }
			else if( *pFieldId == ifds::StopDate )
			{
            pDispInfo->item.pszText = (I_CHAR*)pData->StopDate_.c_str();
			}
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
PaymentInstructionsDlg::PaymentInstructionsDlg(CWnd* pParent, 
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(PaymentInstructionsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL),
m_dstrBrokerCode(NULL_STRING), 
m_dstrBranchCode(NULL_STRING), 
m_dstrSalesRepCode(NULL_STRING),
m_dstrSearchTypeMgmt(NULL_STRING),
m_dstrPaymentFor(NULL_STRING),
m_dstrPayToEntity(NULL_STRING),
m_dstrCurrentBankInstructionsListKey(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(PaymentInstructionsDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void PaymentInstructionsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(PaymentInstructionsDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY PaymentInstructionsDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter (MFCAN_IP_PARAM::BROKER_CODE, m_dstrBrokerCode);
   getParameter (MFCAN_IP_PARAM::BRANCH_CODE, m_dstrBranchCode);
   getParameter (MFCAN_IP_PARAM::SALES_REP_CODE, m_dstrSalesRepCode);
	getParameter (MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, m_dstrSearchTypeMgmt);
   getParameter (I_("PaymentFor"), m_dstrPaymentFor);
   getParameter (I_("PayToEntity"), m_dstrPayToEntity);
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(PaymentInstructionsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(PaymentInstructionsDlg)
ON_MESSAGE(UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_MESSAGE(UM_OPENBRANCHLISTDLG, OpenBranchListDlg)
ON_MESSAGE(UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg)
ON_MESSAGE (WM_LAUNCH_IDENT_ACC, OpenAccountSearchDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_BANK, OnBtnBank)
ON_BN_CLICKED(IDC_CHK_USE_ENTITY_ADDRESS, OnUseEntityAddressCheck)
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical)
ON_NOTIFY(NM_DBLCLK, IDC_LV_BANK_INSTRUCTIONS_LIST, OnDblclkBankList)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL PaymentInstructionsDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void PaymentInstructionsDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

	SetUserAccesFunctionCode(UAF::PAYMENT_INSTRUCTIONS);

   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_PAYMENT_INSTRUCTIONS);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_PAYMENT_INSTRUCTIONS);

   /*AddListControl(CLASSNAME, IDC_LV_PAYMENT_INSTRUCTIONS, LV_PAYMENT_INSTRUCTIONS_LIST, 
      ifds::PaymentInstructionsListHeading, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      0, true, LISTFLAG_NOT_AUTO_ADD);*/

   IFDSListCtrl* pPaymentInstructionsListCtrl = 
      new IFDSAdaptedListCtrl< LVPaymentInstructionsAdapter >(this, CLASSNAME, 
      IDC_LV_PAYMENT_INSTRUCTIONS, 0, 0, true, true);
   
   AddIFDSListControl ( pPaymentInstructionsListCtrl, 
                        LV_PAYMENT_INSTRUCTIONS_LIST, 
                        IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                        ifds::PaymentInstructionsListHeading);

   AddListControl ( CLASSNAME, 
                    IDC_LV_BANK_INSTRUCTIONS_LIST, 
                    LV_BANK_INSTRUCTIONS_LIST, 
                    ifds::BankInstrHeadingSet, 
                    IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                    (UINT)IDC_LV_PAYMENT_INSTRUCTIONS, 
                    true, 
                    LISTFLAG_NOT_AUTO_ADD);

   /*IFDSListCtrl* pBankInstructionsListCtrl = 
      new IFDSAdaptedListCtrl< LVBankInstructionsAdapter >(this, CLASSNAME, 
      IDC_LV_BANK_INSTRUCTIONS_LIST, IDC_LV_PAYMENT_INSTRUCTIONS, LISTFLAG_NOT_AUTO_ADD, 
      true, true);

   AddIFDSListControl(pBankInstructionsListCtrl, 
      LV_BANK_INSTRUCTIONS_LIST, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
      ifds::BankInstrHeadingSet);*/
   AddControl(CTRL_COMBO, IDC_CMB_SETUP_FOR, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::PayToEntity, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   //payment instructions controls
   AddControl(CTRL_EDIT, IDC_EDT_BROKER_CODE, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::BrokerCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_STATIC, IDC_STC_BROKER_NAME, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::BrokerName, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_EDIT, IDC_EDT_BRANCH_CODE, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::BranchCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_STATIC, IDC_STC_BRANCH_NAME, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::BranchName, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_EDIT, IDC_EDT_SLS_REP_CODE, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::SalesRepCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_STATIC, IDC_STC_SLSREP_NAME, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::SalesRepName, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_PAYMENT_TYPE, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::PayType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_DIRECT_TO , IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::DirectTo, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_SHR_GROUP , IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::DirectToShrGrp, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_PAYMENT_METHOD, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::PayMethod, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_EDIT, IDC_EDT_ACCOUNT, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::AccountNum, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
		(UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_PAYMENT_FOR, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::PaymentFor, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_CURRENCY_OPTION, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::CurrencyOption, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_PAY_CURRENCY, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::Currency, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_FILE_PROCESSOR, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::ACHProcessor, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_BANK_CHARGE, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::BankChrgs, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_EDIT, IDC_EDT_ADDRESS, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::AddressLine, CTRLFLAG_FIELDS_FROM_SUB_LIST, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_EDIT, IDC_EDT_POSTAL_CODE, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::PostalCode, CTRLFLAG_DEFAULT, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_COMBO, IDC_CMB_COUNTRY, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::CountryCode, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   AddControl(CTRL_CHECKBOX, IDC_CHK_USE_ENTITY_ADDRESS, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::UseEntityAddress, CTRLFLAG_DEFAULT, 
      (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);

	// Mgmt Company related changes
	AddControl(CTRL_EDIT, IDC_EDT_CODE, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::CompanyCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
	AddControl(CTRL_STATIC, IDC_STC_COMPANY_NAME, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::ClientName, CTRLFLAG_DEFAULT, (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);

	AddControl (CTRL_STATIC, IDC_STATIC_BROKER,	  CTRLFLAG_GUI_FIELD );
	AddControl (CTRL_STATIC, IDC_STATIC_BRANCH,	  CTRLFLAG_GUI_FIELD );
	AddControl (CTRL_STATIC, IDC_STATIC_SALES_REP,  CTRLFLAG_GUI_FIELD );
	AddControl (CTRL_STATIC, IDC_STATIC_CODE,       CTRLFLAG_GUI_FIELD );

	// Netting Bulking Redemtion and Distribution enhancement PET2212 FN10
	//Effective Date
   AddControl ( CTRL_DATE,  
                IDC_DTP_EFFECTIVE_DATE, 
                IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST,
		          ifds::EffectiveDate, 
                CTRLFLAG_DEFAULT, 
                (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
   //Stop Date
   AddControl ( CTRL_DATE,  
                IDC_DTP_STOP_DATE, 
                IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
		          ifds::StopDate, 
                CTRLFLAG_DEFAULT, 
                (UINT)IDC_LV_PAYMENT_INSTRUCTIONS);
	//ConsolType
	 AddControl ( CTRL_COMBO, 
                 IDC_CMB_CONSOL_TYPE, 
                 IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                 ifds::ConsolType, 
                 CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                 (UINT)IDC_LV_PAYMENT_INSTRUCTIONS); 	

	 //Payment Id
	 AddControl ( CTRL_COMBO, 
                 IDC_CMB_PAYMENT_ID, 
                 IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                 ifds::PaymentIdMethod, 
                 CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                 (UINT)IDC_LV_PAYMENT_INSTRUCTIONS); 
	 AddControl ( CTRL_COMBO, 
                 IDC_CMB_SUPPRESSION_CODE, 
                 IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                 ifds::SuppressionReasonCode, 
                 CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                 (UINT)IDC_LV_PAYMENT_INSTRUCTIONS); 

   doRefresh (this, NULL);
}


//******************************************************************************
bool PaymentInstructionsDlg::doRefresh ( GenericInterface *rpGICaller, 
                                         const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
      getParameter(MFCAN_IP_PARAM::BROKER_CODE, m_dstrBrokerCode);
      getParameter(MFCAN_IP_PARAM::BRANCH_CODE, m_dstrBranchCode);
      getParameter(MFCAN_IP_PARAM::SALES_REP_CODE, m_dstrSalesRepCode);
      getParameter(I_("PaymentFor"), m_dstrPaymentFor);
      getParameter(I_("PayToEntity"), m_dstrPayToEntity);
		getParameter(MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, m_dstrSearchTypeMgmt);
   }
	ShowAndEnableMgmtOrBroker ();

	if  (m_dstrSearchTypeMgmt != I_("MGMTCO"))
	{
		CWnd *pWnd = GetDlgItem(IDC_BTN_HISTORICAL);
	   
		if (pWnd)
		{
			pWnd->EnableWindow(
				getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST) > 0 );
		}
	}
	//this will load the connected controls
	LoadListControl(IDC_LV_PAYMENT_INSTRUCTIONS); 
	GetDlgItem (IDC_BTN_MORE)->EnableWindow ( getParent()->doMoreRecordsExist(this, 
		                                       IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST));

	DSTListCtrl *pPIDSTListCtrl = GetList(IDC_LV_PAYMENT_INSTRUCTIONS);

	if (pPIDSTListCtrl)
	{
		if (pPIDSTListCtrl->GetItemCount() <= 0)
		{
			ShowAndEnableBankRelatedControls(true);
			ShowAndEnableAddressRelatedControls(false);
			//add a new row if list is empty, to simulate
			//the normal behaviour
			AddToListControl(IDC_LV_PAYMENT_INSTRUCTIONS);
		}
	}
	
   SetDlgCaption();
   return true;
}

//**********************************************************************************
void PaymentInstructionsDlg::ShowAndEnableMgmtOrBroker()
{
	bool isMgmtCo = m_dstrSearchTypeMgmt == I_("MGMTCO") ?  true : false;
	
	GetDlgItem(IDC_BTN_MORE)->EnableWindow( !isMgmtCo );
	GetDlgItem(IDC_BTN_ADD)->EnableWindow( !isMgmtCo );
	GetDlgItem(IDC_BTN_DELETE)->EnableWindow( !isMgmtCo );
	GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( !isMgmtCo );


	if (  m_dstrSearchTypeMgmt == I_("MGMTCO") )
	{
		GetDlgItem( IDC_STATIC_BROKER )->ShowWindow( SW_HIDE );
		GetDlgItem( IDC_STATIC_BRANCH )->ShowWindow( SW_HIDE );
		GetDlgItem( IDC_STATIC_SALES_REP )->ShowWindow( SW_HIDE );
		
		
		ConnectControl( IDC_EDT_BROKER_CODE, false );
		GetDlgItem( IDC_EDT_BROKER_CODE )->ShowWindow( SW_HIDE );
		
		ConnectControl( IDC_STC_BROKER_NAME, false );
		GetDlgItem( IDC_STC_BROKER_NAME )->ShowWindow( SW_HIDE );

		ConnectControl( IDC_EDT_BRANCH_CODE, false );
		GetDlgItem( IDC_EDT_BRANCH_CODE )->ShowWindow( SW_HIDE );

		ConnectControl( IDC_STC_BRANCH_NAME, false );
		GetDlgItem( IDC_STC_BRANCH_NAME )->ShowWindow( SW_HIDE );

		ConnectControl( IDC_EDT_SLS_REP_CODE, false );
		GetDlgItem( IDC_EDT_SLS_REP_CODE )->ShowWindow( SW_HIDE );
				
		ConnectControl( IDC_STC_SLSREP_NAME, false );
		GetDlgItem( IDC_STC_SLSREP_NAME )->ShowWindow( SW_HIDE );

		GetDlgItem( IDC_STATIC_CODE )->ShowWindow( SW_SHOW );
			
		GetDlgItem( IDC_EDT_CODE )->ShowWindow( SW_SHOW );
		
		GetDlgItem( IDC_STC_COMPANY_NAME )->ShowWindow( SW_SHOW );
	
	}

	else
	{
		GetDlgItem( IDC_STATIC_BROKER )->ShowWindow( SW_SHOW );
		GetDlgItem( IDC_STATIC_BRANCH )->ShowWindow( SW_SHOW );
		GetDlgItem( IDC_STATIC_SALES_REP )->ShowWindow( SW_SHOW );

		GetDlgItem( IDC_EDT_BROKER_CODE )->ShowWindow( SW_SHOW );
		
		GetDlgItem( IDC_STC_BROKER_NAME )->ShowWindow( SW_SHOW );
		
		GetDlgItem( IDC_EDT_BRANCH_CODE )->ShowWindow( SW_SHOW );
		
		GetDlgItem( IDC_STC_BRANCH_NAME )->ShowWindow( SW_SHOW );
		
		GetDlgItem( IDC_EDT_SLS_REP_CODE )->ShowWindow( SW_SHOW );
		
		GetDlgItem( IDC_STC_SLSREP_NAME )->ShowWindow( SW_SHOW );
		
		
		GetDlgItem( IDC_STATIC_CODE )->ShowWindow( SW_HIDE );
		
		ConnectControl( IDC_EDT_CODE, false );
		GetDlgItem( IDC_EDT_CODE )->ShowWindow( SW_HIDE );

		ConnectControl( IDC_STC_COMPANY_NAME, false );
		GetDlgItem( IDC_STC_COMPANY_NAME )->ShowWindow( SW_HIDE );
	}

}

//*************************************************************************
void PaymentInstructionsDlg::SetDlgCaption()
{
   DString caption;

	if ( m_dstrSearchTypeMgmt == I_("MGMTCO") )
	{
		DString dstrClientName;
		DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
		if( dstWorkSession->getOption( ifds::ClientName, dstrClientName, getParent()->getDataGroupId(), false ) <= WARNING )
		{
			CString cstrMgmtCo;
			cstrMgmtCo.LoadString(TXT_MANAGEMENT_COMPANY);
			caption = DString(cstrMgmtCo) + dstrClientName;
			SetCaption(caption);
		}
	}
	else
	{

		if (m_dstrBrokerCode == NULL_STRING && 
			m_dstrBranchCode == NULL_STRING && 
			m_dstrSalesRepCode == NULL_STRING)
		{
			CString all;

			all.LoadString(TXT_ALL);
			caption = all.GetBuffer(0);
			caption = I_(": ") + caption;
		}
		else
		{
			DString brokerName,
				branchName,
				salesRepName;

			getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
				ifds::BrokerName, brokerName);
			getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
				ifds::BranchName, branchName);
			getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
				ifds::SalesRepName, salesRepName);
			CString cstrBroker;
			cstrBroker.LoadString(TXT_BROKER_TXT);
			if (m_dstrPayToEntity == PAY_TO::BROKER)
			{
				caption = DString(cstrBroker) + brokerName;
			}
			else if (m_dstrPayToEntity == PAY_TO::BRANCH)
			{
				CString cstrBranch;
			    cstrBranch.LoadString(TXT_BRANCH_TXT);
				caption = DString(cstrBroker) + brokerName + 
					DString(cstrBranch) + branchName;
			}
			else if (m_dstrPayToEntity == PAY_TO::SALESREP)
			{
				CString cstrBranch, cstrSalesRep;
			    cstrBranch.LoadString(TXT_BRANCH_TXT);
				cstrSalesRep.LoadString(TXT_SALES_REP);
				caption = DString(cstrBroker) + brokerName + 
					DString(cstrBranch) + branchName + 
					DString(cstrSalesRep) + salesRepName;
			}
		}
		SetCaption(caption);
	}
}

//*************************************************************************
bool PaymentInstructionsDlg::PreCancel()
{
   DString onlyBankListIsUpdated;

   getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      OnlyBankListIsUpdated, onlyBankListIsUpdated);

   return onlyBankListIsUpdated != I_("Y") ||
      AfxMessageBox(TXT_PAY_INSTRUCT_BANKS_CANCEL, MB_YESNO) == IDYES;
}

//*************************************************************************
void PaymentInstructionsDlg::ControlUpdated(UINT controlID, 
   const DString &strValue)
{
   DString dstrEnableBanking,
      dstrPayToEntity,
      dstrRemoveBanks;

   getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      EnableBanking, dstrEnableBanking);
   getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      RemoveBanks, dstrRemoveBanks);
   getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      ifds::PayToEntity, dstrPayToEntity, false);

   bool bShouldBank = dstrEnableBanking == I_("Y");
   bool bRemoveBanks = dstrRemoveBanks == I_("Y");
   
   if (IDC_CMB_PAYMENT_TYPE == controlID && !bShouldBank && bRemoveBanks)
   {
      //get the bank list ctrl
      DSTListCtrl *pBanksDSTListCtrl = 
         GetList(IDC_LV_BANK_INSTRUCTIONS_LIST);

      if (pBanksDSTListCtrl)
      {
         pBanksDSTListCtrl->DeleteAllItems();
      }
      GetDlgItem(IDC_BTN_BANK)->EnableWindow(false);
      ShowAndEnableBankRelatedControls(true);
      ShowAndEnableAddressRelatedControls(false);
   }
   else if ((IDC_CMB_PAYMENT_METHOD == controlID ||
	   IDC_CMB_PAYMENT_TYPE == controlID || IDC_CMB_PAYMENT_FOR == controlID) && !bRemoveBanks)
   {
      GetDlgItem(IDC_BTN_BANK)->EnableWindow(bShouldBank);
      ShowAndEnableBankRelatedControls(bShouldBank);
      ShowAndEnableAddressRelatedControls(!bShouldBank);
      /*if (IDC_CMB_PAYMENT_METHOD == controlID)
      {*/
         if (bShouldBank)
         {
            DString dstrBrokerCode,
               dstrBranchCode,
               dstrSalesRepCode;

            getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
               ifds::BrokerCode, dstrBrokerCode, false);
            getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
               ifds::BranchCode, dstrBranchCode, false);
            getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
               ifds::SalesRepCode, dstrSalesRepCode, false);

            bool bReloadBankList = 
               (GetControl(IDC_EDT_BROKER_CODE)->GetErrorState() <= WARNING &&
                  dstrBrokerCode != NULL_STRING && dstrPayToEntity == PAY_TO::BROKER) ||
               (GetControl(IDC_EDT_BRANCH_CODE)->GetErrorState() <= WARNING &&
                  dstrBrokerCode != NULL_STRING && dstrBranchCode != NULL_STRING && 
                  dstrPayToEntity == PAY_TO::BRANCH) ||
               (GetControl(IDC_EDT_SLS_REP_CODE)->GetErrorState() <= WARNING &&
                  dstrBrokerCode != NULL_STRING && dstrBranchCode != NULL_STRING && 
                  dstrSalesRepCode != NULL_STRING && dstrPayToEntity == PAY_TO::SALESREP) ||
					(GetControl(IDC_EDT_CODE)->GetErrorState() <= WARNING &&
                  dstrBrokerCode == NULL_STRING && dstrBranchCode == NULL_STRING && 
                  dstrSalesRepCode == NULL_STRING && dstrPayToEntity == I_("CLIENT") );

            if (bReloadBankList)
            {
               //to reset the bank list, so new items can be picked-up
               getParent()->setField(this, ReloadBankList, 0, false);
               LoadListControl(IDC_LV_BANK_INSTRUCTIONS_LIST);
            }
            else
            {//remove all items from the list control ?
            }
         /*}
         else
         {
            //reset the bank list
            getParent()->setField(this, ReloadBankList, 0, false);
            LoadListControl(IDC_LV_BANK_INSTRUCTIONS_LIST);
         }*/
      }
   } 
   else if (IDC_EDT_BROKER_CODE == controlID || 
      IDC_EDT_BRANCH_CODE == controlID ||
      IDC_EDT_SLS_REP_CODE == controlID)
   {
      bool bReloadBankList = bShouldBank && 
         (( IDC_EDT_BROKER_CODE == controlID && 
            GetControl(IDC_EDT_BROKER_CODE)->GetErrorState() <= WARNING &&
            strValue != NULL_STRING && dstrPayToEntity == PAY_TO::BROKER) ||
          (IDC_EDT_BRANCH_CODE == controlID && 
            GetControl(IDC_EDT_BRANCH_CODE)->GetErrorState() <= WARNING &&
            strValue != NULL_STRING && dstrPayToEntity == PAY_TO::BRANCH) ||
          (IDC_EDT_SLS_REP_CODE == controlID && 
            GetControl(IDC_EDT_SLS_REP_CODE)->GetErrorState() <= WARNING &&
            strValue != NULL_STRING && dstrPayToEntity == PAY_TO::SALESREP));

      if (bReloadBankList)
      {
         //to reset the bank list, so new items can be picked-up
         getParent()->setField(this, ReloadBankList, 0, false);
         LoadListControl(IDC_LV_BANK_INSTRUCTIONS_LIST);
      }
      else
      {//remove all items from the list control?
      }
   }
   else if (IDC_CMB_SETUP_FOR == controlID)
   {
		ShowAndEnableMgmtOrBroker ( );
      if (bShouldBank)
      {
         //to reset the bank list, so new items can be picked-up
         getParent()->setField(this, ReloadBankList, 0, false);
      }
      else
      { //remove all items from the list control
      }
   }
   else if (IDC_CHK_USE_ENTITY_ADDRESS == controlID)
   {
      DSTButton* ueaCheck = 
         dynamic_cast<DSTButton*>(GetControl(controlID));

      if (ueaCheck != NULL)
      {
         ueaCheck->SetCheck(strValue == I_("Y"));
      }
   }
   else if ( IDC_CMB_DIRECT_TO == controlID )
   {
		LoadControl( IDC_CMB_PAYMENT_TYPE );

		DString dstrDirectTo;
		getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, ifds::DirectTo, dstrDirectTo, false);
		if ( I_( "SH" ) == dstrDirectTo )       // Shareholder Group
		{
			// Show Shareholder Group
			CString cstrShrHldr;
			cstrShrHldr.LoadString(TXT_SHRHLDR_GROUP);
			GetDlgItem(IDC_TXT_DIRECT_TO_KEY)->SetWindowText( cstrShrHldr );
			GetDlgItem(IDC_CMB_SHR_GROUP)->ShowWindow( true );
			LoadControl( IDC_CMB_SHR_GROUP );
			ConnectControlToData( IDC_CMB_SHR_GROUP, true );
			
			// Hide Account
			GetDlgItem(IDC_EDT_ACCOUNT)->ShowWindow( false );
			ConnectControlToData( IDC_EDT_ACCOUNT, false );			
		}
		else         // Account or Pay Entity
		{
			// Show Account
			CString cstrAcctNum;
			cstrAcctNum.LoadString(TXT_ACCT_NUM);
			GetDlgItem(IDC_TXT_DIRECT_TO_KEY)->SetWindowText( cstrAcctNum );
			GetDlgItem(IDC_EDT_ACCOUNT)->ShowWindow( true );
			LoadControl( IDC_EDT_ACCOUNT );
			ConnectControlToData( IDC_EDT_ACCOUNT, true );

			// Hide Shareholder
			GetDlgItem(IDC_CMB_SHR_GROUP)->ShowWindow( false );
			ConnectControlToData( IDC_CMB_SHR_GROUP, false );	
		}
   }
   else if( IDC_CMB_PAYMENT_FOR == controlID )
   {
	   /* bool bShowPaymentFor = false;
		DString dstrPaymentFor;
		getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, ifds::PaymentFor, dstrPaymentFor, false);		
		dstrPaymentFor.stripAll().upperCase();
		if ( I_( "PW" ) == dstrPaymentFor || 
			 I_( "ID" ) == dstrPaymentFor )
		{
			bShowPaymentFor = true;
		}

		GetDlgItem( IDC_TXT_CONSOL_TYPE )->ShowWindow( bShowPaymentFor );	
		GetDlgItem( IDC_CMB_CONSOL_TYPE )->ShowWindow( bShowPaymentFor );	*/		
   }
}

//******************************************************************************
void PaymentInstructionsDlg::OnBtnAdd()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnAdd"));

   CWaitCursor wait;

   AddToListControl(IDC_LV_PAYMENT_INSTRUCTIONS);
}

//******************************************************************************
void PaymentInstructionsDlg::OnBtnDelete()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnDelete"));

   CWaitCursor wait;

   DString dstrHasNegativeCommission;
   getParent()->getField( this, 
	                      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                          ifds::HasNegativeComm, 
						  dstrHasNegativeCommission, 
						  false );

   if ( I_( "Y" ) == dstrHasNegativeCommission.stripAll().upperCase() )
   {
		CString cstrMessage;
		cstrMessage.LoadString(TXT_NEG_COMM_MESSAGE);		
		AfxMessageBox( cstrMessage, MB_OK | MB_ICONSTOP);
   }
   else
   {
		DeleteFromListControl(IDC_LV_PAYMENT_INSTRUCTIONS);
		   
		DSTListCtrl *pPIDSTListCtrl = 
			GetList(IDC_LV_PAYMENT_INSTRUCTIONS);

		//if no items in the payment instructions list ctrl
		//delete all list items of the bank list ctrl
		if (pPIDSTListCtrl && pPIDSTListCtrl->GetItemCount() <= 0)
		{
			//get the bank list ctrl
			DSTListCtrl *pBanksDSTListCtrl = 
				GetList(IDC_LV_BANK_INSTRUCTIONS_LIST);

			if (pBanksDSTListCtrl)
			{
				pBanksDSTListCtrl->DeleteAllItems();
			}
		}
   }
}

//******************************************************************************
void PaymentInstructionsDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList(IDC_LV_PAYMENT_INSTRUCTIONS)->GetNextItem(-1, 
      LVIS_SELECTED | LVNI_FOCUSED);
   const DString *crtKey = &getParent()->getCurrentListItemKey(this, 
      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);

   if (getParent()->performSearch(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
      SEARCH_NEXT_BLOCK ) <= WARNING)
   {
      LoadListControl(IDC_LV_PAYMENT_INSTRUCTIONS);
      if (*crtKey != NULL_STRING)
      {
         GetList(IDC_LV_PAYMENT_INSTRUCTIONS)->SetSelection(crtKey);
      }
   }
   GetDlgItem(IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist(this, 
      IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST));
   GetList(IDC_LV_PAYMENT_INSTRUCTIONS)->SetSelection(cursel, true, true);
}

//****************************************************************
void PaymentInstructionsDlg::OnBtnReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;

   ResetListItem(IDC_LV_PAYMENT_INSTRUCTIONS);
	ClearControl ( IDC_CMB_PAYMENT_TYPE );
    ReInitControl ( IDC_CMB_PAYMENT_TYPE, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, ifds::PayType );    
    ConnectControlToData( IDC_CMB_PAYMENT_TYPE, true );
    LoadControl( IDC_CMB_PAYMENT_TYPE );
}

//*************************************************************************
void PaymentInstructionsDlg::OnBtnAdmDates()
{
   ShowAdminDates(IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
}

//*************************************************************************
void PaymentInstructionsDlg::OnDblclkBankList(NMHDR* pNMHDR, LRESULT* pResult)
{
   if (GetDlgItem(IDC_BTN_BANK)->IsWindowEnabled())
   {
      OnBtnBank();
   }
   *pResult = 0;
}

//*************************************************************************
void PaymentInstructionsDlg::OnBtnBank()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBrokerListDlg"));
   CWaitCursor wait;

   try
   {
      DString dstrSetupFor;

      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::PayToEntity, dstrSetupFor, false);
      dstrSetupFor.upperCase();
      if (dstrSetupFor != NULL_STRING)
      {
         DString brokerCode, branchCode, salesRepCode;

         getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
            ifds::BrokerCode, brokerCode);
         getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
            ifds::BranchCode, branchCode);
         getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
            ifds::SalesRepCode, salesRepCode);
         if (dstrSetupFor == PAY_TO::BROKER)
         {
            setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::BROKER);
            setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
         }
         else if (dstrSetupFor == PAY_TO::BRANCH)
         {
            setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::BRANCH);
            setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
            setParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
         }
         else if (dstrSetupFor == PAY_TO::SALESREP)
         {
            setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::SALESREP);
            setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
            setParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
            setParameter(MFCAN_IP_PARAM::SALES_REP_CODE, salesRepCode);
         }
			else if ( dstrSetupFor == I_("CLIENT") )
			{
				setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::CLIENT );
				setParameter ( I_("BankMgmtCo"), I_("CLIENT") );
			}
         setParameter(MFCAN_IP_PARAM::SELECTION_KEY, 
            m_dstrCurrentBankInstructionsListKey);

         E_COMMANDRETURN eRtn = invokeCommand(getParent(), 
            CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL);

         switch(eRtn)
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               //load the bank controls
               LoadListControl(IDC_LV_BANK_INSTRUCTIONS_LIST);
               break;
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
               break;
         }
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
}

//******************************************************************
void PaymentInstructionsDlg::OnUseEntityAddressCheck()
{
   DSTButton* ueaCheck = 
      dynamic_cast<DSTButton*>(GetControl(IDC_CHK_USE_ENTITY_ADDRESS));

   if (ueaCheck != NULL)
   {
      getParent()->setField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::UseEntityAddress, ueaCheck->GetCheck() ? 
         I_("Y") : I_("N"), false);
   }
}

//******************************************************************
BOOL PaymentInstructionsDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   //do not allow F4 on the edit controls that are not updateable
   if (pMsg->message == WM_KEYDOWN && 
      (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
      m_pWndItemInFocus = GetFocus();
      if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_BROKER_CODE))
      {
         PostMessage(UM_OPENBROKERLISTDLG);
      }
      else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_BRANCH_CODE))
      {
         PostMessage(UM_OPENBRANCHLISTDLG);
      }
      else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_SLS_REP_CODE))
      {
         PostMessage(UM_OPENSLSREPLISTDLG);
      }
		else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_ACCOUNT))
      {
         PostMessage(WM_LAUNCH_IDENT_ACC);
      }
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}


//******************************************************************
void PaymentInstructionsDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   if ( listControlID == IDC_LV_BANK_INSTRUCTIONS_LIST )
   {
      m_dstrCurrentBankInstructionsListKey = strKey;
   }
   else if( listControlID == IDC_LV_PAYMENT_INSTRUCTIONS )
   {
      // History
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( !(bIsNewItem || bIsDummyItem) );
   }
}

//******************************************************************************
bool PaymentInstructionsDlg::GetOverrideItemString(long lSubstituteId, 
   const DString &ColumnKey, DString &strOut)
{
   bool retVal = false;
   if (lSubstituteId == ifds::BankInstrHeadingSet.getId())
   {
      if (ColumnKey == I_("Status"))
      {
         DString dstEffectiveDate, 
            dstStopDate, 
            dstCurrBusDate;

         getParent()->getField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
            ifds::EffectiveDate, dstEffectiveDate, false);
         getParent()->getField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
            ifds::StopDate, dstStopDate, false);
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
         getDateInHostFormat(dstCurrBusDate, 
            DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, 
            getDataGroupId());
         DSTCommonFunctions::DATE_ORDER rtn = 
            DSTCommonFunctions::CompareDates(dstEffectiveDate, dstCurrBusDate);
         DSTCommonFunctions::DATE_ORDER rtn1 = 
            DSTCommonFunctions::CompareDates(dstCurrBusDate, dstStopDate);

         if (rtn < DSTCommonFunctions::SECOND_EARLIER && 
            rtn1 == DSTCommonFunctions::FIRST_EARLIER)
         {
            strOut = I_("Active");
         }
         else
         {
            strOut = I_("Inactive");
         }
         retVal = true;
      }
   }
   return retVal;
}
//*************************************************************************
LRESULT PaymentInstructionsDlg::OpenBrokerListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBrokerListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString brokerCode;
   
      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::BrokerCode, brokerCode);
      setParameter(MFCAN_IP_PARAM::CALLER, I_("PaymentInstructions"));
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      eRtn = invokeCommand(getParent(), CMD_BPROC_BROKER, 
         PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
               if(brokerCode != NULL_STRING)
               {
                  getParent()->setField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                     ifds::BrokerCode, brokerCode);
               }
               LoadControl(IDC_EDT_BROKER_CODE);
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
   return eRtn;
}

//******************************************************************
LRESULT PaymentInstructionsDlg::OpenBranchListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBranchListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString brokerCode, branchCode;
   
      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::BrokerCode, brokerCode);
      setParameter(MFCAN_IP_PARAM::CALLER, I_("PaymentInstructions"));
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      eRtn = invokeCommand(getParent(), 
         CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
               if(branchCode != NULL_STRING)
               {
                  getParent()->setField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                     ifds::BranchCode, branchCode);
               }
               LoadControl(IDC_EDT_BRANCH_CODE);
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
   return eRtn;
}

//******************************************************************
LRESULT PaymentInstructionsDlg::OpenSlsRepListDlg(WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString brokerCode, branchCode;
   
      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::BrokerCode, brokerCode);
      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::BranchCode, branchCode);
      setParameter(MFCAN_IP_PARAM::CALLER, I_("PaymentInstructions"));
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      setParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
      eRtn = invokeCommand(getParent(), 
            CMD_BPROC_SLSREP, PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString slsrepCode;

               getParameter(MFCAN_IP_PARAM::SALES_REP_CODE, slsrepCode);
               if(slsrepCode != NULL_STRING)
               {
                  getParent()->setField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
                     ifds::SalesRepCode, slsrepCode);
               }
               LoadControl(IDC_EDT_SLS_REP_CODE);
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
   return(eRtn);
}

//*************************************************************************
void PaymentInstructionsDlg::ShowAndEnableBankRelatedControls(bool bShow)
{
   GetDlgItem(IDC_STC_BANK_INSTRUCTIONS_LIST)->ShowWindow(bShow);
   GetDlgItem(IDC_LV_BANK_INSTRUCTIONS_LIST)->ShowWindow(bShow);
}

//*************************************************************************
void PaymentInstructionsDlg::ShowAndEnableAddressRelatedControls(bool bShow)
{
   GetDlgItem(IDC_STC_ADDRESS_DETAILS)->ShowWindow(bShow);
   GetDlgItem(IDC_CHK_USE_ENTITY_ADDRESS)->EnableWindow(bShow);
   GetDlgItem(IDC_CHK_USE_ENTITY_ADDRESS)->ShowWindow(bShow);
   GetDlgItem(IDC_STC_ADDRESS)->ShowWindow(bShow);
   GetDlgItem(IDC_EDT_ADDRESS)->ShowWindow(bShow);
   GetDlgItem(IDC_STC_POSTAL_CODE)->ShowWindow(bShow);
   GetDlgItem(IDC_EDT_POSTAL_CODE)->ShowWindow(bShow);
   GetDlgItem(IDC_STC_COUNTRY)->ShowWindow(bShow);
   GetDlgItem(IDC_CMB_COUNTRY)->ShowWindow(bShow);
}


//******************************************************************************
bool PaymentInstructionsDlg::ListViewControlFilter(long lSubstituteId, const DString *strKey)
{
   bool bShow = true;

   if (lSubstituteId == ifds::PaymentInstructionsListHeading.getId())
   {
      DString brokerCode, branchCode, salesRepCode, paymentFor;

      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::BrokerCode, brokerCode);
      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::BranchCode, branchCode);
      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::SalesRepCode, salesRepCode);
      getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::PaymentFor, paymentFor, false);
      //make all upper cases
      brokerCode.stripAll().upperCase();
      branchCode.stripAll().upperCase();
      salesRepCode.stripAll().upperCase();
      paymentFor.stripAll().upperCase();
      bShow = 
         (m_dstrBrokerCode == NULL_STRING || m_dstrBrokerCode == brokerCode) &&
         (m_dstrBranchCode == NULL_STRING || m_dstrBranchCode == branchCode) &&
         (m_dstrSalesRepCode == NULL_STRING || m_dstrSalesRepCode == salesRepCode) &&
         (m_dstrPaymentFor == NULL_STRING || m_dstrPaymentFor == paymentFor);
   }
   return bShow;
}

//******************************************************************

void PaymentInstructionsDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   // Set Parameters
   DString dstrBrokerCode, dstrBranchCode, dstrSalesRepCode;
   getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, ifds::BrokerCode, dstrBrokerCode);
   getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, ifds::BranchCode, dstrBranchCode);
   getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, ifds::SalesRepCode, dstrSalesRepCode);
   dstrBrokerCode.stripAll().upperCase();
   dstrBranchCode.stripAll().upperCase();
   dstrSalesRepCode.stripAll().upperCase();
   setParameter( I_("BROKER"), dstrBrokerCode );
   setParameter( I_("BRANCH"), dstrBranchCode );
   setParameter( I_("SALESREP"), dstrSalesRepCode );

   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST);
}

//********************************************************************************************************
bool PaymentInstructionsDlg::PreOk()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("PreOk" ) );

   bool rtn = true;
   DString hasNoRecords, paymentFor;

   getParent()->getField(this, IFASTBP_PROC::PAYMENT_INSTRUCTIONS_LIST, 
         ifds::PaymentFor, paymentFor, false);
   getParent()->getField( this, HAS_NON_RECORDS, hasNoRecords );

   if( hasNoRecords == I_("Y") && ( paymentFor == I_("NC") || paymentFor == I_("NT") ) )
   {
      //ADDCONDITIONFROMFILE( CND::GUI_NO_PAYMENTINSTRUCTION_IN_LIST );
      CString cstrMessage;
	  cstrMessage.LoadString(TXT_PAY_INSTR_SETUP_MESSAGE);
      AfxMessageBox( cstrMessage );      
   }

   return(rtn);
}

//******************************************************************
LRESULT PaymentInstructionsDlg::OpenAccountSearchDlg (WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenAccountSearchDlg"));
   CWaitCursor wait;

   DString accountNum;

	//don't allow user to open account search unless they cleared the account number, why (???)
   if (accountNum.empty())
   {
      try
      {
   //invoke the account search helper dialog
         switch (getParentProcess ()->
                    invokeProcessFromChild ( this, 
                                             CMD_BPROC_IDENT_ACC, 
                                             PROC_SUPPORT))
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
                  getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
                  if (!accountNum.empty ())
                  {
                     int iAccountNumCtrlId = m_pWndItemInFocus->GetDlgCtrlID ();
                  
                     SetControlText (iAccountNumCtrlId, accountNum);
                     LoadControl (iAccountNumCtrlId);
                  }
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
   return 0;
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/PaymentInstructionsDlg.cpp-arc  $
// 
//    Rev 1.40   Nov 24 2011 15:52:22   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.39   Nov 19 2011 01:35:52   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.38   Nov 25 2009 14:29:16   jankovii
// PET0166583 FN01 Static Data Changes Banking 
// 
//    Rev 1.37   Aug 09 2007 14:15:42   jankovii
// PET 2388 FN01 - Swift Payment Method Id.
// 
//    Rev 1.36   Jan 24 2007 16:53:24   ZHANGCEL
// PET2306 FN02 -- Add logic for the enhancement
// 
//    Rev 1.35   Sep 14 2006 11:35:46   porteanm
// STP 2192/12
// 
//    Rev 1.34   Sep 10 2006 18:00:48   popescu
// STP 2192/12
// 
//    Rev 1.33   Sep 07 2006 21:39:04   popescu
// STP 2192/02
// 
//    Rev 1.32   Aug 28 2006 15:41:26   ZHANGCEL
// PET2212 FN10 -- Added new logic for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.31   Jul 31 2006 11:02:46   ZHANGCEL
// PET2192 FN11 -- Set parament for the banking issue.
// 
//    Rev 1.30   Jul 27 2006 18:03:28   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.29   May 31 2006 17:58:34   porteanm
// PET2132 FN03 - Edit check for Negative Commission.
// 
//    Rev 1.28   Jan 25 2006 10:19:24   AGUILAAM
// PET2016_FN05: AXA Office Trailer Fee Indicator
// 
//    Rev 1.27   Nov 01 2005 09:17:42   AGUILAAM
// PET1243_FN00_ABN AMRO Trailer Fee Processing - additional enhancements
// 
//    Rev 1.26   Oct 19 2005 17:16:34   AGUILAAM
// PET1243_FN00: ABN AMRO Trailer Fee Processing
// 
//    Rev 1.25   Sep 15 2005 15:14:32   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.24   Aug 22 2005 10:53:10   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
// 
//    Rev 1.23   Dec 09 2004 11:51:06   Fengyong
// PET1034745 - Add info box when no payment instruction record was added
// 
//    Rev 1.22   Apr 08 2004 10:19:40   FENGYONG
// PET944 FN01 Release56.1 NSCC Broker
// 
//    Rev 1.21   Feb 27 2004 15:58:00   HERNANDO
// PET965 FN11 - Enable/Disable Historical Button based on list item in doListItemChanged.
// 
//    Rev 1.20   Feb 18 2004 18:01:24   popescu
// PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
// - clean-up the work session every time user hits 'Search' on the Features Search Dialog
// - do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
// - fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
// - use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
// 
//    Rev 1.19   Oct 31 2003 16:03:14   HERNANDO
// PTS 10022670 - Passing Broker Code, Branch Code, and Sales Rep Code.
// 
//    Rev 1.18   Sep 05 2003 09:58:54   popescu
// Reset the banking list when pay method is Cheque and do not trigger the Bank Instructions dialog if the pay to entity is empty string. 
// 
//    Rev 1.17   Sep 02 2003 17:58:32   popescu
// The list filtering should convert tho uppercase the fields of the Payment Instructions list
// 
//    Rev 1.16   Aug 18 2003 12:12:04   popescu
// PTS 10020555
// Changed the bak instructios process type to a PROC_SUPPORT
// 
//    Rev 1.15   Aug 17 2003 16:12:40   popescu
// fixed 52 crash in regards with the Historical button
// 
//    Rev 1.14   Aug 14 2003 13:49:54   HERNANDO
// Added OnBtnHistorical.
// 
//    Rev 1.13   Aug 07 2003 18:42:38   popescu
// set the bank instructions bank list selection on the bank selected in payment instructions dialog
// 
//    Rev 1.12   Jul 31 2003 21:59:08   popescu
// Added support for PayType 'X' and support for Historical Info at the process level
// 
//    Rev 1.11   Jul 29 2003 19:06:20   popescu
// refresh should read the pay to entity param as well to set the caption correctly
// 
//    Rev 1.10   Jul 29 2003 14:19:40   popescu
// Fixes regarding the Discard/Cancel dialog
// 
//    Rev 1.9   Jul 26 2003 21:20:30   popescu
// worked on setting the caption of the payment instructions dialog
// 
//    Rev 1.8   Jul 26 2003 19:39:02   popescu
// the refresh of the banking list didn't work properly in some cases, 
// 
//    Rev 1.7   Jul 25 2003 14:26:24   popescu
// Fix crash in payment instructions dialog, as result of filtering the payment instructions list, cleared the address fields when the checque option is selected for the payment method
// 
//    Rev 1.6   Jul 23 2003 18:19:44   popescu
// changed list controls to the new IFDSListCtrl
// 
//    Rev 1.5   Jul 11 2003 13:47:00   popescu
// fixes related to the confirmation screen showing up even if there are no changes for the payment instructions screen, added validation for the Currency if BAAF is selected as the file processor
// 
//    Rev 1.4   Jul 10 2003 22:59:12   popescu
// latest changes to pay instruct, filtered correctly the screen, based on the input
// 
//    Rev 1.3   Jul 10 2003 22:21:42   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.2   Jul 09 2003 21:57:42   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.1   Jul 02 2003 17:49:54   popescu
// work for payment instructions feature 
// 
//    Rev 1.0   Jul 01 2003 18:17:52   popescu
// Initial revision.
// 
*/

