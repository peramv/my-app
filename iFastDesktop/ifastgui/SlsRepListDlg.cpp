// SlsRepListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "slsreplistdlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\salesrepprocessincludes.h>
#include <uibase\DSTListCtrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SLSREP;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SlsRepListDlg > dlgCreator(CMD_GUI_SLSREP);

namespace
{
   const I_CHAR * const CLASSNAME = I_("SlsRepListDlg");
   const I_CHAR * const LV_SALESREP = I_("SalesRepList");
}


//**********************************************************
SlsRepListDlg::SlsRepListDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(SlsRepListDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME),
m_dstrBrokerCode(NULL_STRING),
m_dstrBranchCode(NULL_STRING),
m_dstrCaller(NULL_STRING)
{
   //{{AFX_DATA_INIT(SlsRepListDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//**********************************************************
void SlsRepListDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SlsRepListDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   DDX_Control(pDX, IDC_BTN_MORE, m_BtnMore);
   //}}AFX_DATA_MAP
}

//*******************************************************
BEGIN_MESSAGE_MAP(SlsRepListDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SlsRepListDlg)
ON_NOTIFY(NM_DBLCLK, IDC_SLSREP_LIST, OnDblclkSlsrepList)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

class LVSlsRepData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVSlsRepData() {}
   DString SlsrepName_;
   DString Slsrep_;
   DString Commission_;
   DString TrailerFee_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::SlsrepName, SlsrepName_);
      SlsrepName_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::Slsrep, Slsrep_);
      Slsrep_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::PayInstrComm, Commission_);
      Commission_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::PayInstrTrailer, TrailerFee_);
      TrailerFee_.strip();
   }
};

class LVSlsRepAdapter : public IFDSListCtrlAdapter< LVSlsRepData >
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
      else if (*pFieldId == ifds::SlsrepName) 
      {
         result = i_strcmp(pData1->SlsrepName_.c_str(), pData2->SlsrepName_.c_str());
      } 
      else if (*pFieldId == ifds::Slsrep) 
      {
         result = i_strcmp(pData1->Slsrep_.c_str(), pData2->Slsrep_.c_str());
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
         else if (*pFieldId == ifds::SlsrepName) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->SlsrepName_.c_str();
         } 
         else if (*pFieldId == ifds::Slsrep) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->Slsrep_.c_str();
         } 
         else if (*pFieldId == ifds::PayInstrComm) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->Commission_.c_str();
         } 
         else if (*pFieldId == ifds::PayInstrTrailer) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->TrailerFee_.c_str();
         } 
         return (1);
      }
      return (0);
   }
};

/*************************************************************************/
SEVERITY SlsRepListDlg::doInit()
{
   getParameter(MFCAN_IP_PARAM::BROKER_CODE, m_dstrBrokerCode); 
   getParameter(MFCAN_IP_PARAM::BRANCH_CODE, m_dstrBranchCode);
   getParameter(MFCAN_IP_PARAM::CALLER, m_dstrCaller);
   return NO_CONDITION;
}

//****************************************************************/
void SlsRepListDlg::OnPostInitDialog()
{
   DString dstrCaption;
   CString cstrText;

   cstrText.LoadString(TXT_TRANS_BROKERCODE);
   dstrCaption = I_(" ") + DString(cstrText) + I_(" ") + m_dstrBrokerCode;
   if (!m_dstrBranchCode.empty())
   {
      dstrCaption += I_("; ");
      cstrText.LoadString(TXT_TRANS_BRANCHCODE);
      dstrCaption += DString(cstrText) + I_(" ") + m_dstrBranchCode;
   }
   SetCaption(dstrCaption);

   IFDSListCtrl* pCtrl = new IFDSAdaptedListCtrl< LVSlsRepAdapter >(this, 
      CLASSNAME, IDC_SLSREP_LIST, 0, LISTFLAG_NOT_UPDATABLE, true, true);

   DString strMarket = DSTCommonFunctions::getMarket();

   if (strMarket == MARKET_IDS::JAPAN)
   {
      AddListControl(CLASSNAME, IDC_SLSREP_LIST, LV_SALESREP, 
         ifds::SlsRepListHeading, IFASTBP_PROC::AGENT_LIST);
   }
   else
   {
      if (m_dstrCaller == I_("PaymentInstructions"))
      {
         AddIFDSListControl(pCtrl, LV_SALESREP, 
            IFASTBP_PROC::AGENT_LIST, ifds::SlsrepListHeadingPayments);
      }
      else
      {
         AddIFDSListControl(pCtrl, LV_SALESREP, 
            IFASTBP_PROC::AGENT_LIST, ifds::SlsRepListHeading1);
      }
   }
   doRefresh(this, NULL);
}

//**********************************************************************
bool SlsRepListDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR * szOriginalCommand)
{
   LoadListControl(IDC_SLSREP_LIST);
   m_BtnMore.EnableWindow(getParent()->doMoreRecordsExist(this, 
      BF::AllContainerIds));
   GetList(IDC_SLSREP_LIST)->SetFocus();
   return true;
}

//**********************************************************************
void SlsRepListDlg::OnDblclkSlsrepList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   PostMessage(WM_COMMAND, IDOK);
   *pResult = 0;
}

//******************************************************************************
void SlsRepListDlg::OnBtnMore() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD(CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel;

   cursel = GetList(IDC_SLSREP_LIST)->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);

   const DString *crtKey = &getParent()->getCurrentListItemKey(this, IFASTBP_PROC::AGENT_LIST);

   SetMessageStatusBar(TXT_LOAD_SLSREP);
   if (getParent()->performSearch(this, BF::AllContainerIds, SEARCH_NEXT_BLOCK) <= WARNING)
   {
      LoadListControl(IDC_SLSREP_LIST);
      if (*crtKey != NULL_STRING)
      {
         GetList(IDC_SLSREP_LIST)->SetSelection(crtKey);
      }
   }
   m_BtnMore.EnableWindow(getParent()->doMoreRecordsExist(this, BF::AllContainerIds));
   GetList(IDC_SLSREP_LIST)->SetSelection(cursel, true, true);                 
   SetMessageStatusBar(NULL_STRING); 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SlsRepListDlg.cpp-arc  $
 * 
 *    Rev 1.11   Sep 15 2005 15:15:18   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.10   Jul 23 2003 18:22:58   popescu
 * erased duplicate include
 * 
 *    Rev 1.9   Jul 10 2003 22:21:54   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.8   Jul 07 2003 12:56:54   HERNANDO
 * Replaced AddListControl with AddIFDSListControl.  Fixed Caption display; removed embedded English text.
 * 
 *    Rev 1.7   Mar 21 2003 18:41:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:56:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   22 May 2002 19:16:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   27 Mar 2002 20:01:22   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.3   16 Oct 2001 11:20:24   HSUCHIN
 * Implemented GetMore functionality
 * 
 *    Rev 1.2   Aug 02 2001 22:10:10   YINGBAOL
 * fix list title
 * 
 *    Rev 1.1   Nov 03 2000 16:03:52   DINACORN
 * Set Focus on the SlsRepList
 * 
 *    Rev 1.0   Feb 15 2000 11:01:24   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Jan 14 2000 08:51:30   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.5   Jan 07 2000 15:55:52   POPESCUS
// just checking in...
// 
//    Rev 1.4   Dec 24 1999 14:18:10   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.3   Dec 22 1999 12:24:12   ZHANGCEL
// Revision bug fixed
// 
//    Rev 1.2   Dec 22 1999 11:39:50   ZHANGCEL
// for release
*/