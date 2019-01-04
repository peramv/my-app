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
// ^FILE   : TradePayInstructDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2006
//
// ----------------------------------------------------------
//
// ^CLASS    : TradePayInstructDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "tradepayinstructdlg.h"
#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\tradepayinstructprocessincludes.h>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRADE_PAYMENT_INSTRUCTIONS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<TradePayInstructDlg> dlgCreator(CMD_GUI_TRADE_PAYMENT_INSTRUCTIONS);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("TradePayInstructDlg");
   const I_CHAR *LV_TRADE_PAYMENT_INSTRUCTIONS_LIST = I_("TradePaymentInstructionsList");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADE_PI_CONTROLS
{
   const UINT BANK = 1;
   const UINT ADDRESS = 2;
}

class LVTradePayInstructData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVTradePayInstructData() {}
   DString PaymentFor_;
   DString PayType_;
   DString PayMethod_;
   DString ACHProcessor_;
   DString AllocPercent_;

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
         ifds::AllocPercent, AllocPercent_);
      AllocPercent_.strip();
   }
};

class LVTradePayInstructAdapter : public IFDSListCtrlAdapter< LVTradePayInstructData >
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
      else if (*pFieldId == ifds::AllocPercent) 
      {
			double ap1 = DSTCommonFunctions::convertToDouble ( pData1->AllocPercent_.c_str() );
			double ap2 = DSTCommonFunctions::convertToDouble ( pData2->AllocPercent_.c_str() );         			

         result = ap1 < ap2 ? -1 : ap1 > ap2 ? 1 : 0;
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
         else if (*pFieldId == ifds::AllocPercent)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->AllocPercent_.c_str();
         }
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
TradePayInstructDlg::TradePayInstructDlg (CWnd* pParent, 
                                          GenericInterfaceContainer* pGIC, 
                                          GenericInterface* pGIParent, 
                                          const Command& rCommand)
: BaseMainDlg(TradePayInstructDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_dstrTransNum (NULL_STRING),
m_dstrListKey (NULL_STRING),
m_dstrCaller (NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(TradePayInstructDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void TradePayInstructDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TradePayInstructDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY TradePayInstructDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter (MFCAN_IP_PARAM::CALLER, m_dstrCaller);
   getParameter (MFCAN_IP_PARAM::TRANS_NUM, m_dstrTransNum);
   getParameter (MFCAN_IP_PARAM::LIST_KEY, m_dstrListKey);
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(TradePayInstructDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TradePayInstructDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_BANK, OnBtnBank)
ON_BN_CLICKED(IDC_CHK_USE_ENTITY_ADDRESS, OnUseEntityAddressCheck)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL TradePayInstructDlg::OnInitDialog() 
{
   TRACE_METHOD (CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void TradePayInstructDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

   IFDSListCtrl* pPaymentInstructionsListCtrl = 
      new IFDSAdaptedListCtrl< LVTradePayInstructAdapter >( this, CLASSNAME, 
                                                            IDC_LV_TRADE_PAY_INSTRUCT, 
                                                            0, 0, true, true);  
   AddIFDSListControl( pPaymentInstructionsListCtrl, 
                       LV_TRADE_PAYMENT_INSTRUCTIONS_LIST, 
                       IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
                       ifds::TradePayInstructHeadSet);

   //payment instructions controls
   AddControl( CTRL_COMBO, IDC_CMB_PAYMENT_FOR, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::PaymentFor, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_TRADE_PAY_INSTRUCT);
   AddControl( CTRL_COMBO, IDC_CMB_PAYMENT_TYPE, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::PayType, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_TRADE_PAY_INSTRUCT);
   AddControl( CTRL_COMBO, IDC_CMB_PAYMENT_METHOD, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::PayMethod, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_TRADE_PAY_INSTRUCT);
   AddControl( CTRL_COMBO, IDC_CMB_FILE_PROCESSOR, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::ACHProcessor, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_TRADE_PAY_INSTRUCT);  
   AddControl( CTRL_COMBO, IDC_CMB_CURRENCIES, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::Currency, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_TRADE_PAY_INSTRUCT);  
   AddControl( CTRL_COMBO, IDC_CMB_CONSOLIDATION_TYPE, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::ConsolType, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_TRADE_PAY_INSTRUCT);  
   AddControl ( CTRL_STATIC, 
                IDC_STC_ADDRESS_DETAILS, 
                CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_STATIC, 
                IDC_STC_ADDRESS, 
                CTRLFLAG_GUI_FIELD);
   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::AddressLine, 
               CTRLFLAG_FIELDS_FROM_SUB_LIST, 
               TRADE_PI_CONTROLS::ADDRESS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_POSTAL_CODE, 
                CTRLFLAG_GUI_FIELD);
   AddControl( CTRL_EDIT, IDC_EDT_POSTAL_CODE, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::PostalCode, 
               CTRLFLAG_DEFAULT, 
               TRADE_PI_CONTROLS::ADDRESS);
   AddControl ( CTRL_STATIC, 
                IDC_STC_COUNTRY, 
                CTRLFLAG_GUI_FIELD);
   AddControl( CTRL_COMBO, IDC_CMB_COUNTRY, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::CountryCode, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               TRADE_PI_CONTROLS::ADDRESS);
   AddControl( CTRL_CHECKBOX, IDC_CHK_USE_ENTITY_ADDRESS, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
               ifds::UseEntityAddress, 
               CTRLFLAG_DEFAULT, 
               TRADE_PI_CONTROLS::ADDRESS);
   
//Group Box 'Bank details'   
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_DETAILS, 
                CTRLFLAG_GUI_FIELD);
//'Bank Name' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_NAME_LABEL, 
                CTRLFLAG_GUI_FIELD);
//bank name value
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_NAME, 
                BANK, 
                ifds::InstName, 
                CTRLFLAG_DEFAULT, 
                TRADE_PI_CONTROLS::BANK);
//'Bank Nbr.' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ID_LABEL, 
                CTRLFLAG_GUI_FIELD);
//bank nbr value
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ID, 
                BANK, 
                ifds::BankIdValue, 
                CTRLFLAG_DEFAULT, 
                TRADE_PI_CONTROLS::BANK);
//bank 'Acct Name' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ACCT_NAME_LABEL, 
                CTRLFLAG_GUI_FIELD);
//bank acct name value
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ACCT_NAME, 
                BANK, 
                ifds::BankAcctName, 
                CTRLFLAG_DEFAULT,
                TRADE_PI_CONTROLS::BANK);
//bank 'Acct Nbr.' label
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ACCT_NBR_LABEL, 
                CTRLFLAG_GUI_FIELD);
//bank account number value
   AddControl ( CTRL_STATIC, 
                IDC_STC_BANK_ACCT_NBR, 
                BANK, 
                ifds::BankAcctNum, 
                CTRLFLAG_DEFAULT,
                TRADE_PI_CONTROLS::BANK);
   doRefresh (this, NULL);
}


//******************************************************************************
bool TradePayInstructDlg::doRefresh( GenericInterface *rpGICaller, 
                                     const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
      getParameter (MFCAN_IP_PARAM::CALLER, m_dstrCaller);
      getParameter (MFCAN_IP_PARAM::TRANS_NUM, m_dstrTransNum);
      getParameter (MFCAN_IP_PARAM::LIST_KEY, m_dstrListKey);
   }
   DSTListCtrl *pTradePayInstructListCtrl = GetList (IDC_LV_TRADE_PAY_INSTRUCT);

   if ( pTradePayInstructListCtrl && 
        (m_dstrCaller == I_("Transaction") || m_dstrCaller == I_("PendingTransaction")))
   {
      pTradePayInstructListCtrl->setAutoAddFlag (true);
      GetDlgItem (IDC_BTN_BANK)->EnableWindow (false);
      GetDlgItem (IDC_BTN_ADM_DATES)->EnableWindow (false);
      ShowAndEnableBankRelatedControls (false);
      ShowAndEnableAddressRelatedControls (false);
   }
   ConnectControlsToData (TRADE_PI_CONTROLS::ADDRESS, false);
   ConnectControlsToData (TRADE_PI_CONTROLS::BANK, false);
   //this will load the connected controls
   LoadListControl (IDC_LV_TRADE_PAY_INSTRUCT);
   SetDlgCaption ();
   return true;
}

//*************************************************************************
void TradePayInstructDlg::SetDlgCaption ()
{
   DString caption (m_dstrTransNum);

   SetCaption (caption);
}


//*************************************************************************
void TradePayInstructDlg::ControlUpdated( UINT controlID, 
                                          const DString &strValue)
{
   DString dstrEnableBanking,
      dstrPayToEntity,
      dstrRemoveBanks;

   getParent()->getField ( this, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
                           EnableBanking, dstrEnableBanking);

   bool bShouldBank = dstrEnableBanking == I_("Y");
   
   if (IDC_CMB_PAYMENT_METHOD == controlID || IDC_CMB_PAYMENT_TYPE == controlID)
   {
      GetDlgItem (IDC_BTN_BANK)->EnableWindow (bShouldBank && m_dstrCaller == I_("TradeEntry"));
      ShowAndEnableBankRelatedControls (bShouldBank);
      ShowAndEnableAddressRelatedControls (!bShouldBank);
   }
   else if (IDC_CHK_USE_ENTITY_ADDRESS == controlID)
   {
      DSTButton* ueaCheck = dynamic_cast <DSTButton*>(GetControl(controlID));

      if (ueaCheck != NULL)
      {
         ueaCheck->SetCheck (strValue == I_("Y"));
      }
   }
}

//*************************************************************************
void TradePayInstructDlg::OnBtnAdmDates ()
{
   ShowAdminDates (IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);
}

//*************************************************************************
void TradePayInstructDlg::OnBtnBank ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBank"));
   CWaitCursor wait;

   try
   {
      DString accountNum,
         tradePayInstructListKey;

      getParent ()->getField (this, IFASTBP_PROC::TRADE, ifds::AccountNum, accountNum, false);
      tradePayInstructListKey = getParent ()->getCurrentListItemKey ( this, 
                                                                      IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST);

      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
      setParameter (MFCAN_IP_PARAM::LIST_KEY, m_dstrListKey); //trade list key...
      setParameter (MFCAN_IP_PARAM::SUB_LIST_KEY, tradePayInstructListKey); //trade pay instruct list key...
      setParameter (MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::TRADE);

      E_COMMANDRETURN eRtn = invokeCommand( getParent(), 
                                            CMD_BPROC_BANK_INSTRUCTIONS, 
                                            PROC_SUPPORT, 
                                            true, 
                                            NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            //load the bank controls
            LoadControl (IDC_STC_BANK_NAME);
            LoadControl (IDC_STC_BANK_ID);
            LoadControl (IDC_STC_BANK_ACCT_NAME);
            LoadControl (IDC_STC_BANK_ACCT_NBR);
            break;
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
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
void TradePayInstructDlg::OnUseEntityAddressCheck()
{
   DSTButton* ueaCheck = dynamic_cast<DSTButton*>(GetControl(IDC_CHK_USE_ENTITY_ADDRESS));

   if (ueaCheck != NULL)
   {
      getParent()->setField ( this, IFASTBP_PROC::TRADE_PAYMENT_INSTRUCTIONS_LIST, 
                              ifds::UseEntityAddress, 
                              ueaCheck->GetCheck() ? I_("Y") : I_("N"), false);
   }
}

//******************************************************************
BOOL TradePayInstructDlg::PreTranslateMessage(MSG* pMsg) 
{
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//*************************************************************************
void TradePayInstructDlg::ShowAndEnableBankRelatedControls (bool bShow)
{
   ConnectControlsToData (TRADE_PI_CONTROLS::BANK, bShow);
   if (bShow)
   {
      LoadControls (TRADE_PI_CONTROLS::BANK);
   }
   GetControl (IDC_STC_BANK_DETAILS)->Show (bShow);
   GetControl (IDC_STC_BANK_NAME_LABEL)->Show (bShow);
   GetControl (IDC_STC_BANK_NAME)->Show (bShow);
   GetControl (IDC_STC_BANK_ID_LABEL)->Show (bShow);
   GetControl (IDC_STC_BANK_ID)->Show (bShow);
   GetControl (IDC_STC_BANK_ACCT_NAME_LABEL)->Show (bShow);
   GetControl (IDC_STC_BANK_ACCT_NAME)->Show (bShow);
   GetControl (IDC_STC_BANK_ACCT_NBR_LABEL)->Show (bShow);
   GetControl (IDC_STC_BANK_ACCT_NBR)->Show (bShow);
}

//*************************************************************************
void TradePayInstructDlg::ShowAndEnableAddressRelatedControls (bool bShow)
{
   ConnectControlsToData (TRADE_PI_CONTROLS::ADDRESS, bShow);
   if (bShow)
   {
      LoadControls (TRADE_PI_CONTROLS::ADDRESS);
   }
   GetDlgItem (IDC_STC_ADDRESS_DETAILS)->ShowWindow (bShow);
   GetControl (IDC_CHK_USE_ENTITY_ADDRESS)->Show (bShow);
   GetDlgItem (IDC_STC_ADDRESS)->ShowWindow (bShow);
   GetControl (IDC_EDT_ADDRESS)->Show (bShow);
   GetDlgItem (IDC_STC_POSTAL_CODE)->ShowWindow (bShow);
   GetControl (IDC_EDT_POSTAL_CODE)->Show (bShow);
   GetDlgItem (IDC_STC_COUNTRY)->ShowWindow (bShow);
   GetControl (IDC_CMB_COUNTRY)->Show (bShow);
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TradePayInstructDlg.cpp-arc  $
// 
//    Rev 1.6   Dec 12 2006 12:22:54   popescu
// Incident# 777131 - fixed the access violation error on trade pay instruct dialog when user switches from system check to eft and clicks on bank btn
// 
//    Rev 1.5   Sep 27 2006 00:59:56   popescu
// STP 2217/13 Fixes related to PayInstruct btn on TrxnHist/Pend
// 
//    Rev 1.4   Sep 22 2006 00:47:04   popescu
// STP 2217/13
// 
//    Rev 1.3   Sep 21 2006 01:50:46   popescu
// STP PET 2217/13
// 
//    Rev 1.2   Sep 10 2006 18:01:14   popescu
// STP 2192/12
// 
//    Rev 1.1   Sep 07 2006 21:39:20   popescu
// STP 2192/02
// 
//    Rev 1.0   Aug 29 2006 18:27:32   popescu
// Initial revision.
// 
*/
