// BranchListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "branchlistdlg.h"
#include <ifastbp\branchprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_BRANCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< BranchListDlg > dlgCreator(CMD_GUI_BRANCH);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("BranchListDlg");
   const I_CHAR * const LV_BRANCH = I_("BranchList");
}

namespace CND
{  // Conditions used
}

/////////////////////////////////////////////////////////////////////////////
// BranchListDlg dialog
//*******************************************************************
BranchListDlg::BranchListDlg(CWnd* pParent, 
   GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, 
   const Command& rCommand)
: BaseMainDlg(BranchListDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME),
m_dstrCaller(NULL_STRING),
m_dstrBrokerCode(NULL_STRING)
{
   //{{AFX_DATA_INIT(BranchListDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//*******************************************************************
void BranchListDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(BranchListDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   DDX_Control(pDX, IDC_BTN_MORE, m_BtnMore);
   //}}AFX_DATA_MAP
}


//*******************************************************************
BEGIN_MESSAGE_MAP(BranchListDlg, BaseMainDlg)
//{{AFX_MSG_MAP(BranchListDlg)
ON_NOTIFY(NM_DBLCLK, IDC_BRANCH_LIST, OnDblclkBranchList)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BranchListDlg message handlers

//*************************************************************************
SEVERITY BranchListDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter(MFCAN_IP_PARAM::BROKER_CODE, m_dstrBrokerCode);
   getParameter(MFCAN_IP_PARAM::CALLER, m_dstrCaller);
   return NO_CONDITION;
}

//****************************************************************/
void BranchListDlg::OnPostInitDialog()
{
   SetCaption(I_(" ") + m_dstrBrokerCode);
   if (m_dstrCaller == I_("PaymentInstructions"))
   {
      AddListControl(CLASSNAME, IDC_BRANCH_LIST, 
         LV_BRANCH, ifds::BranchListHeadingPayments, IFASTBP_PROC::BRANCH_LIST);
   }
   else
   {
      AddListControl(CLASSNAME, IDC_BRANCH_LIST, 
         LV_BRANCH, ifds::BranchListHeading, IFASTBP_PROC::BRANCH_LIST);
   }
   doRefresh(this, NULL);
}

//****************************************************************
void BranchListDlg::OnDblclkBranchList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   PostMessage(WM_COMMAND, IDOK);
   *pResult = 0;
}

//****************************************************************
bool BranchListDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{
   LoadListControl(IDC_BRANCH_LIST);
   m_BtnMore.EnableWindow(getParent()->doMoreRecordsExist(this, 
      BF::AllContainerIds));
   GetList(IDC_BRANCH_LIST)->SetFocus();
   return true;
}

//****************************************************************
void BranchListDlg::OnBtnMore() 
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnMore"));

   CWaitCursor wait;
   static int iCurrentSelection;
   iCurrentSelection = GetList(IDC_BRANCH_LIST)->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);

   const DString *crtKey = &getParent()->getCurrentListItemKey(this, IFASTBP_PROC::BRANCH_LIST);

   SetMessageStatusBar(TXT_LOAD_BRANCH);
   if(getParent()->performSearch(this, BF::AllContainerIds, SEARCH_NEXT_BLOCK) <= WARNING)
   {
      LoadListControl(IDC_BRANCH_LIST);
      if(*crtKey != NULL_STRING)
      {
         GetList(IDC_BRANCH_LIST)->SetSelection(crtKey);
      }
   }
   m_BtnMore.EnableWindow(getParent()->doMoreRecordsExist(this, BF::AllContainerIds));
   GetList(IDC_BRANCH_LIST)->SetSelection(iCurrentSelection, true, true);
   SetMessageStatusBar(NULL_STRING); 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BranchListDlg.cpp-arc  $
 * 
 *    Rev 1.9   Sep 15 2005 15:10:48   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.8   Jul 10 2003 22:21:28   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.7   Mar 21 2003 18:33:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 22 2002 15:16:56   HERNANDO
 * Added DDX_Control(pDX, IDC_BTN_MORE, m_BtnMore) to DoDataExchange.
 * 
 *    Rev 1.4   Jul 31 2002 16:15:56   HERNANDO
 * More button implementation.
 * 
 *    Rev 1.3   22 May 2002 19:15:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   27 Mar 2002 20:00:58   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.1   Nov 03 2000 16:03:04   DINACORN
 * Set Focus on the BranchList
 * 
 *    Rev 1.0   Feb 15 2000 11:01:08   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Jan 14 2000 08:51:26   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.5   Jan 11 2000 08:41:46   POPESCUS
// fixes and validation
// 
//    Rev 1.4   Dec 24 1999 14:18:08   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.3   Dec 22 1999 12:23:54   ZHANGCEL
// Revision bug fixed
// 
//    Rev 1.2   Dec 22 1999 11:38:50   ZHANGCEL
// for release
*/