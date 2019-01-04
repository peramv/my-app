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
// ^FILE   : MultiFundAllocationDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2003
//
// ----------------------------------------------------------
//
// ^CLASS    : MultiFundAllocationDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  Handles the multi fund transfer/exchange dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include "multifundallocationdlg.h"
#include <ifastbp\multifundallocationprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstbutton.h>
#include <uibase\dstlistctrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_MULTI_FUND_ALLOCATION;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<MultiFundAllocationDlg> dlgCreator(CMD_GUI_MULTI_FUND_ALLOCATION);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("MultiFundAllocationDlg");
   const I_CHAR * const LV_ALLOC_FROM = I_("LvAllocFrom");
   const I_CHAR * const LV_ALLOC_TO = I_("LvAllocTo");
   const UINT FROM = 1;
   const UINT TO = 2;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
}


class LVFromAllocData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFromAllocData() {}
   DString FundCode_;
   DString ClassCode_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::FundCode, FundCode_);
      FundCode_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::ClassCode, ClassCode_);
      ClassCode_.strip();
   }
};

class LVFromAllocAdapter : public IFDSListCtrlAdapter< LVFromAllocData >
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
      else if (*pFieldId == ifds::FundCode) 
      {
         result = i_strcmp(pData1->FundCode_.c_str(), pData2->FundCode_.c_str());
      } 
      else if (*pFieldId == ifds::ClassCode) 
      {
         result = i_strcmp(pData1->ClassCode_.c_str(), pData2->ClassCode_.c_str());
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
         else if (*pFieldId == ifds::ClassCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ClassCode_.c_str();
         } 
         else if (*pFieldId == ifds::FundCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundCode_.c_str();
         } 
         return (1);
      }
      return (0);
   }
};

class LVToAllocData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVToAllocData() {}
   DString FundCode_;
   DString ClassCode_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::FundCode, FundCode_);
      FundCode_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::ClassCode, ClassCode_);
      ClassCode_.strip();
   }
};

class LVToAllocAdapter : public IFDSListCtrlAdapter< LVToAllocData >
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
      else if (*pFieldId == ifds::FundCode) 
      {
         result = i_strcmp(pData1->FundCode_.c_str(), pData2->FundCode_.c_str());
      } 
      else if (*pFieldId == ifds::ClassCode) 
      {
         result = i_strcmp(pData1->ClassCode_.c_str(), pData2->ClassCode_.c_str());
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
         else if (*pFieldId == ifds::ClassCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ClassCode_.c_str();
         } 
         else if (*pFieldId == ifds::FundCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundCode_.c_str();
         } 
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
MultiFundAllocationDlg::MultiFundAllocationDlg(CWnd* pParent, 
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(MultiFundAllocationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL),
m_dstrCaller(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(MultiFundAllocationDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void MultiFundAllocationDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MultiFundAllocationDlg)
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY MultiFundAllocationDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter(MFCAN_IP_PARAM::CALLER, m_dstrCaller);  
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(MultiFundAllocationDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MultiFundAllocationDlg)
ON_MESSAGE(UM_OPENFUNDLISTDLG, OpenFundListDlg)
ON_BN_CLICKED(IDC_BTN_ADD_FROM, OnBtnAddFrom)
ON_BN_CLICKED(IDC_BTN_DEL_FROM, OnBtnDeleteFrom)
ON_BN_CLICKED(IDC_BTN_RESET_FROM, OnBtnResetFrom)
ON_BN_CLICKED(IDC_BTN_ADD_TO, OnBtnAddTo)
ON_BN_CLICKED(IDC_BTN_DEL_TO, OnBtnDeleteTo)
ON_BN_CLICKED(IDC_BTN_RESET_TO, OnBtnResetTo)
ON_BN_CLICKED(IDC_FULL_TRANSFER, OnFullTransfer)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL MultiFundAllocationDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();
   return TRUE;
}

//*****************************************************************************
void MultiFundAllocationDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

//the 'FROM' side
   /*IFDSListCtrl* pFromAllocListCtrl = 
      new IFDSAdaptedListCtrl< LVFromAllocAdapter >(this, CLASSNAME, 
      IDC_LV_ALLOC_FROM, 0, 0, true, true);

   AddIFDSListControl(pFromAllocListCtrl, 
      LV_ALLOC_FROM, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
      ifds::FromAllocListHeading);*/

   AddListControl(CLASSNAME, IDC_LV_ALLOC_FROM, LV_ALLOC_FROM, 
      ifds::FromAllocListHeading, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
      0, true, 0);
   AddControl(CTRL_EDIT, IDC_EDT_FUND_NUM_FROM, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
      ifds::ToFundNumber, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_FROM);
   AddControl(CTRL_EDIT, IDC_EDT_FUND_FROM, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
      ifds::FundCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_FROM);
   AddControl(CTRL_EDIT, IDC_EDT_CLASS_FROM, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
      ifds::ClassCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_FROM);
   AddControl(CTRL_EDIT, IDC_EDT_AMT_FROM, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
      ifds::AllocAmount, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_FROM);
   AddControl(CTRL_EDIT, IDC_EDT_PERCENT_FROM, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
      ifds::AllocPercentage, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_FROM);
   AddControl(CTRL_COMBO, IDC_CMB_AMT_TYPE, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST,
      ifds::AllocAmtType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
      (UINT)IDC_LV_ALLOC_FROM);
   AddControl(CTRL_CHECKBOX, IDC_FULL_TRANSFER, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
      ifds::FullTransfer, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_FROM);
   AddControl(CTRL_STATIC, IDC_TXT_PERCET_TOTAL_FROM, 
      IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST,
      TotalPercent, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_FROM);
   AddControl(CTRL_STATIC, IDC_TXT_AMT_TOTAL_FROM, 
      IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST,
      TotalAmount, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_FROM);
//the 'from account'   
   AddControl(CTRL_STATIC, IDC_TXT_ACCT_FROM, ACCOUNT_FROM, 
      ifds::AccountNum, CTRLFLAG_DEFAULT, FROM);
   AddControl(CTRL_STATIC, IDC_TXT_ACCT_TYPE_FROM, ACCOUNT_FROM, 
      ifds::AcctType, CTRLFLAG_DEFAULT, FROM);
   AddControl(CTRL_STATIC, IDC_TXT_TAX_TYPE_FROM, ACCOUNT_FROM, 
      ifds::TaxType, CTRLFLAG_DEFAULT, FROM);
//the 'TO' side
   /*IFDSListCtrl* pToAllocListCtrl = 
      new IFDSAdaptedListCtrl< LVToAllocAdapter >(this, CLASSNAME, 
      IDC_LV_ALLOC_TO, 0, 0, true, true);

   AddIFDSListControl(pToAllocListCtrl, 
      LV_ALLOC_TO, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
      ifds::ToAllocListHeading);*/
   AddListControl(CLASSNAME, IDC_LV_ALLOC_TO, LV_ALLOC_TO, 
      ifds::ToAllocListHeading, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
      0, true, 0);
   AddControl(CTRL_EDIT, IDC_EDT_FUND_NUM_TO, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
      ifds::ToFundNumber, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_TO);
   AddControl(CTRL_EDIT, IDC_EDT_FUND_TO, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
      ifds::FundCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_TO);
   AddControl(CTRL_EDIT, IDC_EDT_CLASS_TO, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
      ifds::ClassCode, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_TO);
   AddControl(CTRL_EDIT, IDC_EDT_AMT_TO, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
      ifds::AllocAmount, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_TO);
   AddControl(CTRL_EDIT, IDC_EDT_PERCENT_TO, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
      ifds::AllocPercentage, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_TO);
   AddControl(CTRL_STATIC, IDC_TXT_PERCENT_TOTAL_TO, 
      IFASTBP_PROC::FUND_ALLOCATION_LIST,
      TotalPercent, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_TO);
   AddControl(CTRL_STATIC, IDC_TXT_AMT_TOTAL_TO, 
      IFASTBP_PROC::FUND_ALLOCATION_LIST,
      TotalAmount, CTRLFLAG_DEFAULT, (UINT)IDC_LV_ALLOC_TO);
//the 'to account'   
   AddControl(CTRL_STATIC, IDC_TXT_ACCT_TO, ACCOUNT_TO, 
      ifds::AccountNum, CTRLFLAG_DEFAULT, TO);
   AddControl(CTRL_STATIC, IDC_TXT_ACCT_TYPE_TO, ACCOUNT_TO, 
      ifds::AcctType, CTRLFLAG_DEFAULT, TO);
   AddControl(CTRL_STATIC, IDC_TXT_TAX_TYPE_TO, ACCOUNT_TO, 
      ifds::TaxType, CTRLFLAG_DEFAULT, TO);
   doRefresh(this, NULL);
}


//******************************************************************************
bool MultiFundAllocationDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //this will load the controls
   LoadListControl (IDC_LV_ALLOC_FROM); 
   LoadListControl (IDC_LV_ALLOC_TO);
   ConnectControlsToData (FROM); 
   LoadControls (FROM);
   ConnectControlsToData (TO);
   LoadControls (TO);
   // display caption
   SetDlgCaption();
   //disable/enable controls based on the caller
   callerDependentChanges();
   return true;
}

//******************************************************************************
void MultiFundAllocationDlg::SetDlgCaption()
{
   DString dstrCaption, dstrTransType;
   
   if (m_dstrCaller == I_("Trade"))
   {
      getParent()->getField(this, TRADE, 
         ifds::TradesTransType, dstrTransType, false);
      
      CString caption;
      DString dstrAcctFrom;

      getParent()->getField(this, ACCOUNT_FROM, 
         ifds::AccountNum, dstrAcctFrom, false);
      if (dstrTransType == TRADETYPE::TRANSFER)
      {
         DString dstrAcctTo;

         getParent()->getField(this, ACCOUNT_TO, 
            ifds::AccountNum, dstrAcctTo, false);
         AfxFormatString2(caption, TXT_MULTI_FUND_TRANSFER_CAPTION,
            dstrAcctFrom.c_str(), dstrAcctTo.c_str());
      }
      else if (dstrTransType == TRADETYPE::EXCHANGE)
      {
         AfxFormatString1(caption, TXT_MULTI_FUND_EXCHANGE_CAPTION,
            dstrAcctFrom.c_str());
      }
      dstrCaption = caption.GetBuffer(0);
   }
   else if (m_dstrCaller == I_("Pending"))
   {
   }
   else if (m_dstrCaller == I_("Transaction_History"))
   {
   }
   SetCaption (dstrCaption);
}

//*************************************************************************
void MultiFundAllocationDlg::ControlUpdated(UINT controlID, 
   const DString &strValue)
{
   if (IDC_FULL_TRANSFER == controlID)
   {
      DSTButton *ftCheck = 
         dynamic_cast<DSTButton*>(GetControl(controlID));

      if (ftCheck != NULL)
      {
         ftCheck->SetCheck(strValue == I_("Y"));
      }
   }
}

//******************************************************************************
void MultiFundAllocationDlg::OnBtnAddFrom()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnAddFrom"));

   CWaitCursor wait;

   AddToListControl(IDC_LV_ALLOC_FROM);
}

//******************************************************************************
void MultiFundAllocationDlg::OnBtnDeleteFrom()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnDeleteFrom"));

   CWaitCursor wait;

   DeleteFromListControl (IDC_LV_ALLOC_FROM);
}

//****************************************************************
void MultiFundAllocationDlg::OnBtnResetFrom()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnResetFrom"));

   CWaitCursor wait;

   ResetListItem (IDC_LV_ALLOC_FROM);
}

//******************************************************************************
void MultiFundAllocationDlg::OnBtnAddTo()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnAddTo"));

   CWaitCursor wait;

   AddToListControl(IDC_LV_ALLOC_TO);
}

//******************************************************************************
void MultiFundAllocationDlg::OnBtnDeleteTo()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnDeleteTo"));

   CWaitCursor wait;

   DeleteFromListControl (IDC_LV_ALLOC_TO);
}

//****************************************************************
void MultiFundAllocationDlg::OnBtnResetTo()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnResetTo"));

   CWaitCursor wait;

   ResetListItem(IDC_LV_ALLOC_TO);
}

//******************************************************************
BOOL MultiFundAllocationDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   //do not allow F4 on the edit controls that are not updateable
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
      m_pWndItemInFocus = GetFocus();
      if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_FROM) ||
          m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_FROM) ||
          m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUM_FROM) ||
          m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_TO) ||
          m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_TO) ||
          m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUM_TO)) 
      {
         PostMessage (UM_OPENFUNDLISTDLG);
      }
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}


//******************************************************************
void MultiFundAllocationDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   if (listControlID == IDC_LV_ALLOC_FROM)
   {
      DString allowFullTransfer;

      getParent()->getField(this, ifds::AllowFullTransfer, 
         allowFullTransfer, false);
      GetDlgItem(IDC_FULL_TRANSFER)->EnableWindow(allowFullTransfer == I_("Y"));
      changeAmountLabel(allowFullTransfer == I_("Y"));
   }
}

//******************************************************************
LRESULT MultiFundAllocationDlg::OpenFundListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenFundListDlg"));

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      //clear all params first
      setParameter(MFCAN_IP_PARAM::CLASS_CODE, NULL_STRING);
      setParameter(MFCAN_IP_PARAM::FUND_CODE, NULL_STRING);
      setParameter(MFCAN_IP_PARAM::FUND_NUMBER, NULL_STRING);
      if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_FROM) ||
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_TO)) 
      {
         CString cstrClassCode;

         static_cast<CEdit*>(m_pWndItemInFocus)->GetWindowText(cstrClassCode);
         setParameter(MFCAN_IP_PARAM::CLASS_CODE, (LPCTSTR)cstrClassCode);
      } 
      else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_FROM) || 
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_TO))
      {
         CString cstrFundCode;

         static_cast<CEdit*>(m_pWndItemInFocus)->GetWindowText(cstrFundCode);
         setParameter(MFCAN_IP_PARAM::FUND_CODE, (LPCTSTR)cstrFundCode);
      } 
      else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUM_FROM) ||
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUM_TO))
      {
         CString cstrFundNumber;

         static_cast<CEdit*>(m_pWndItemInFocus)->GetWindowText(cstrFundNumber);
         setParameter(MFCAN_IP_PARAM::FUND_NUMBER, (LPCTSTR)cstrFundNumber);
      }
      //invoke the fund class dialog and process
      SetMessageStatusBar(TXT_LOAD_FUND_INFO);
      eRtn = invokeCommand(getParent(), CMD_BPROC_FUNDCLASS, 
         PROC_SUPPORT, true, NULL);
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               bool bFrom = false;

               if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_FROM) ||
                   m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_TO) ||
                   m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_FROM) ||
                   m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_TO))
               {
                  DString dstrClassCode, dstrFundCode;

                  getParameter(MFCAN_IP_PARAM::CLASS_CODE, dstrClassCode);
                  getParameter(MFCAN_IP_PARAM::FUND_CODE, dstrFundCode);
                  if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_FROM) ||
                     m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_FROM))
                  {
                     getParent()->setField(this, 
                        IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
                        ifds::ClassCode, dstrClassCode);
                     getParent()->setField(this, 
                        IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
                        ifds::FundCode, dstrFundCode);
                     bFrom = true;
                  }
                  else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_TO) ||
                     m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_TO))
                  {
                     getParent()->setField(this, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
                        ifds::ClassCode, dstrClassCode);
                     getParent()->setField(this, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
                        ifds::FundCode, dstrFundCode);
                  }
               }
               else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUM_FROM) ||
                  m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUM_TO))
               {
                  DString dstrFundNumber;

                  getParameter(MFCAN_IP_PARAM::FUND_NUMBER, dstrFundNumber);
                  if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUM_FROM))
                  {
                     getParent()->setField(this, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
                        ifds::ToFundNumber, dstrFundNumber);
                     bFrom = true;
                  }
                  else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_NUM_TO))
                  {
                     getParent()->setField(this, IFASTBP_PROC::FUND_ALLOCATION_LIST, 
                        ifds::ToFundNumber, dstrFundNumber);
                  }
               }
               if (bFrom)
               {
                  LoadControl (IDC_EDT_CLASS_FROM);
                  LoadControl (IDC_EDT_FUND_FROM);
                  LoadControl (IDC_EDT_FUND_NUM_FROM);
               }
               else 
               {
                  LoadControl (IDC_EDT_CLASS_TO);
                  LoadControl (IDC_EDT_FUND_TO);
                  LoadControl (IDC_EDT_FUND_NUM_TO);
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
      SetMessageStatusBar(NULL_STRING);
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return(0);
}

//******************************************************************
void MultiFundAllocationDlg::OnFullTransfer()
{
   DSTButton* fullTrsfCheck = 
      dynamic_cast<DSTButton*>(GetControl(IDC_FULL_TRANSFER));

   if (fullTrsfCheck != NULL)
   {
      bool bCheck = fullTrsfCheck->GetCheck() == 1;

      getParent()->setField(this, IFASTBP_PROC::TRADE_FROM_FUND_ALLOCATION_LIST, 
         ifds::FullTransfer, bCheck ? I_("Y") : I_("N"), false);
   }
}

//*************************************************************************
void MultiFundAllocationDlg::changeAmountLabel(bool bWhatLabel)
{
   CString s;
   
   if (bWhatLabel)
   {
      s.LoadString(TXT_ESTIMATED_TOTAL);
   }
   else
   {
      s.LoadString(TXT_TOTAL);
   }
   GetDlgItem(IDC_STC_FROM_TOTAL)->SetWindowText(s.GetBuffer(0));
}

//*************************************************************************
void MultiFundAllocationDlg::callerDependentChanges()
{
   bool bEnable = m_dstrCaller == I_("Trade");

   GetDlgItem(IDC_BTN_ADD_FROM)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_DEL_FROM)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_RESET_FROM)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_ADD_TO)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_DEL_TO)->EnableWindow(bEnable);
   GetDlgItem(IDC_BTN_RESET_TO)->EnableWindow(bEnable);
   GetDlgItem(IDOK)->EnableWindow(bEnable);
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MultiFundAllocationDlg.cpp-arc  $
// 
//    Rev 1.3   Sep 15 2005 15:14:16   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.2   Sep 05 2003 18:29:40   popescu
// PET809_FN02, fixex
// 
//    Rev 1.1   Sep 01 2003 21:23:48   popescu
// PET 809 FN 02 CIBC Multi Fund Transfer
// 
//    Rev 1.0   Aug 14 2003 15:52:36   popescu
// Initial revision.
// 
*/

