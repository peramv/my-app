//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by International Financial Data Servicesaguila
//
//******************************************************************************
//
// ^FILE   : MsgSearchDlg.cpp
// ^CLASS  : MsgSearchDlg
//******************************************************************************
#include "stdafx.h"
#include "MFDSTC.h"
#include "MsgSearchDlg.h"
#include <ifastbp\MsgSearchProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include "discardmsgdlg.h"

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MSG_SEARCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MsgSearchDlg > dlgCreator(CMD_GUI_MSG_SEARCH);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("MsgSearchDlg");
   const I_CHAR * const SEARCH_TYPE_PROCESSTYPE = I_("ProcessType");
   const I_CHAR * const SEARCH_TYPE_NETWORKID = I_("NetworkID");
   const I_CHAR * const SEARCH_TYPE_SEND_REF_NUM = I_("SendersRefNum");
   const I_CHAR * const SEARCH_TYPE_TRANS_NUM = I_("TransNum");
   const I_CHAR * const SEARCH_TYPE_AGGR_ORD_NUM = I_("AggrOrdRefNum");
}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
MsgSearchDlg::MsgSearchDlg(CWnd* pParent, 
   GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, 
   const Command& rCommand)
: BaseMainDlg(MsgSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL),
m_dstrBackgroundSearch(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(MsgSearchDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void MsgSearchDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MsgSearchDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY MsgSearchDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);
   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(MsgSearchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MsgSearchDlg)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_CBN_SELCHANGE(IDC_CMB_USING, OnSelchangeCmbUsing)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL MsgSearchDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);
   BaseMainDlg::OnInitDialog();
   return TRUE;
}

//*****************************************************************************
void MsgSearchDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

   AddControl(CTRL_COMBO, IDC_CMB_USING, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::MsgSearchType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   // Using
   AddControl(CTRL_EDIT, IDC_EDT_SEARCH_VALUE, BF::NullContainerId, 
      ifds::SearchUsing, CTRLFLAG_DEFAULT);

   // Process Type (Combo)
   AddControl(CTRL_COMBO, IDC_CMB_TYPE, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::MsgProcessType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   // Process Category (Combo)
   AddControl(CTRL_COMBO, IDC_CMB_CATEGORY, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::MsgProcessCategory, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   // Network ID
   AddControl(CTRL_COMBO, IDC_CMB_NETWORK_ID, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::NetworkID, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);			

   // Process Status / Process Category
   AddControl(CTRL_COMBO, IDC_CMB_PROCESS_STATUS, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::MsgProcessStatus, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);			

   // Start Date
	AddControl(CTRL_DATE, IDC_DATE_START, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::StartDate, CTRLFLAG_DEFAULT);

   // End Date
	AddControl(CTRL_DATE, IDC_DATE_END, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::EndDate, CTRLFLAG_DEFAULT);

   doRefresh (this, NULL_STRING);
   OnSelchangeCmbUsing();
}

//******************************************************************************
bool MsgSearchDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   ConnectControlsToData();
   LoadControls(IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
//   SetDlgCaption();
   return true;
}

//*************************************************************************
bool MsgSearchDlg::PreCancel()
{
   return discardUpdates();
}

//*************************************************************************

void MsgSearchDlg::ControlUpdated (
   UINT controlID, 
   const DString &strValue)
{
   switch (controlID)
   {
      case IDC_CMB_USING:
      {
         // Clear Edit Control
         CString cstrTemp("");
         GetDlgItem( IDC_EDT_SEARCH_VALUE )->SetWindowText( cstrTemp );
         if( strValue == SEARCH_TYPE_PROCESSTYPE )
         {
            // Edit Ctrl
            ReInitControl(IDC_EDT_SEARCH_VALUE, BF::NullContainerId, ifds::SearchUsing, CTRLFLAG_DEFAULT);

            GetDlgItem( IDC_TXT_USING )->ShowWindow( SW_SHOW );
            ConnectControl( IDC_EDT_SEARCH_VALUE, false );
            GetControl( IDC_EDT_SEARCH_VALUE )->ConnectToData( false );
            ShowControl( IDC_EDT_SEARCH_VALUE, false );

            // Connect to Combo box for Process Type
            GetDlgItem( IDC_CMB_TYPE )->ShowWindow( SW_SHOW );
            ConnectControl( IDC_CMB_TYPE, true );
            GetControl( IDC_CMB_TYPE )->ConnectToData( true );
            ShowControl( IDC_CMB_TYPE, true );
            LoadControl( IDC_CMB_TYPE );

            // Change Process Category
            GetDlgItem( IDC_CMB_CATEGORY )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_CATEGORY, false );
            GetControl( IDC_CMB_CATEGORY )->ConnectToData( false );
            ShowControl( IDC_CMB_CATEGORY, false );

            GetDlgItem( IDC_TXT_NETWORK_ID )->ShowWindow( SW_SHOW );
            ShowControl( IDC_CMB_NETWORK_ID, true );
            GetDlgItem( IDC_TXT_PROCESS_STATUS )->ShowWindow( SW_SHOW );
            ShowControl( IDC_CMB_PROCESS_STATUS, true );
            GetDlgItem( IDC_TXT_START_DATE )->ShowWindow( SW_SHOW );
            ShowControl( IDC_DATE_START, true );
            GetDlgItem( IDC_TXT_END_DATE )->ShowWindow( SW_SHOW );
            ShowControl( IDC_DATE_END, true );
         }
         else if( strValue == SEARCH_TYPE_NETWORKID )
         {
            // Edit Ctrl
            ReInitControl(IDC_EDT_SEARCH_VALUE, BF::NullContainerId, ifds::SearchUsing, CTRLFLAG_DEFAULT);

            GetDlgItem( IDC_TXT_USING )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_EDT_SEARCH_VALUE, false );
            GetControl( IDC_EDT_SEARCH_VALUE )->ConnectToData( false );
            ShowControl( IDC_EDT_SEARCH_VALUE, false );

            // Change to Combo box, and Show Control
            GetDlgItem( IDC_CMB_TYPE )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_TYPE, false );
            GetControl( IDC_CMB_TYPE )->ConnectToData( false );
            ShowControl( IDC_CMB_TYPE, false );

            // Change Process Category
            GetDlgItem( IDC_CMB_CATEGORY )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_CATEGORY, false );
            GetControl( IDC_CMB_CATEGORY )->ConnectToData( false );
            ShowControl( IDC_CMB_CATEGORY, false );

            GetDlgItem( IDC_TXT_NETWORK_ID )->ShowWindow( SW_SHOW );
            ShowControl( IDC_CMB_NETWORK_ID, true );
            GetDlgItem( IDC_TXT_PROCESS_STATUS )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_PROCESS_STATUS, false );
            GetDlgItem( IDC_TXT_START_DATE )->ShowWindow( SW_SHOW );
            ShowControl( IDC_DATE_START, true );
            GetDlgItem( IDC_TXT_END_DATE )->ShowWindow( SW_SHOW );
            ShowControl( IDC_DATE_END, true );
         }
         else if( strValue == SEARCH_TYPE_SEND_REF_NUM )
         {
            // Edit Ctrl - SendRefNum
            ReInitControl(IDC_EDT_SEARCH_VALUE, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::SendRefNum, CTRLFLAG_DEFAULT);

            GetDlgItem( IDC_TXT_USING )->ShowWindow( SW_SHOW );
            ConnectControl( IDC_EDT_SEARCH_VALUE, true );
            GetControl( IDC_EDT_SEARCH_VALUE )->ConnectToData( true );
            LoadControl( IDC_EDT_SEARCH_VALUE );
            ShowControl( IDC_EDT_SEARCH_VALUE, true );

            // Change to Combo box, and Show Control
            GetDlgItem( IDC_CMB_TYPE )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_TYPE, false );
            GetControl( IDC_CMB_TYPE )->ConnectToData( false );
            ShowControl( IDC_CMB_TYPE, false );

            // Change Process Category
            GetDlgItem( IDC_CMB_CATEGORY )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_CATEGORY, false );
            GetControl( IDC_CMB_CATEGORY )->ConnectToData( false );
            ShowControl( IDC_CMB_CATEGORY, false );

            GetDlgItem( IDC_TXT_NETWORK_ID )->ShowWindow( SW_SHOW );
            ShowControl( IDC_CMB_NETWORK_ID, true );
            GetDlgItem( IDC_TXT_PROCESS_STATUS )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_PROCESS_STATUS, false );
            GetDlgItem( IDC_TXT_START_DATE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_DATE_START, false );
            GetDlgItem( IDC_TXT_END_DATE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_DATE_END, false );
         }
         else if( strValue == SEARCH_TYPE_TRANS_NUM )
         {
            // Edit Ctrl - Trans Num
            ReInitControl(IDC_EDT_SEARCH_VALUE, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::TransNum, CTRLFLAG_DEFAULT);

            GetDlgItem( IDC_TXT_USING )->ShowWindow( SW_SHOW );
            ConnectControl( IDC_EDT_SEARCH_VALUE, true );
            GetControl( IDC_EDT_SEARCH_VALUE )->ConnectToData( true );
            LoadControl( IDC_EDT_SEARCH_VALUE );
            ShowControl( IDC_EDT_SEARCH_VALUE, true );

            // Change to Combo box, and Show Control
            GetDlgItem( IDC_CMB_TYPE )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_TYPE, false );
            GetControl( IDC_CMB_TYPE )->ConnectToData( false );
            ShowControl( IDC_CMB_TYPE, false );

            // Change Process Category
            GetDlgItem( IDC_CMB_CATEGORY )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_CATEGORY, false );
            GetControl( IDC_CMB_CATEGORY )->ConnectToData( false );
            ShowControl( IDC_CMB_CATEGORY, false );

            GetDlgItem( IDC_TXT_NETWORK_ID )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_NETWORK_ID, false );
            GetDlgItem( IDC_TXT_PROCESS_STATUS )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_PROCESS_STATUS, false );
            GetDlgItem( IDC_TXT_START_DATE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_DATE_START, false );
            GetDlgItem( IDC_TXT_END_DATE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_DATE_END, false );
         }
         else if( strValue == SEARCH_TYPE_AGGR_ORD_NUM )
         {
            // Edit Ctrl - OmnibusID
            ReInitControl(IDC_EDT_SEARCH_VALUE, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::OmnibusID, CTRLFLAG_DEFAULT);

            GetDlgItem( IDC_TXT_USING )->ShowWindow( SW_SHOW );
            ConnectControl( IDC_EDT_SEARCH_VALUE, true );
            GetControl( IDC_EDT_SEARCH_VALUE )->ConnectToData( true );
            LoadControl( IDC_EDT_SEARCH_VALUE );
            ShowControl( IDC_EDT_SEARCH_VALUE, true );

            // Change to Combo box, and Show Control
            GetDlgItem( IDC_CMB_TYPE )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_TYPE, false );
            GetControl( IDC_CMB_TYPE )->ConnectToData( false );
            ShowControl( IDC_CMB_TYPE, false );

            // Change Process Category
            GetDlgItem( IDC_CMB_CATEGORY )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_CATEGORY, false );
            GetControl( IDC_CMB_CATEGORY )->ConnectToData( false );
            ShowControl( IDC_CMB_CATEGORY, false );

            GetDlgItem( IDC_TXT_NETWORK_ID )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_NETWORK_ID, false );
            GetDlgItem( IDC_TXT_PROCESS_STATUS )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_PROCESS_STATUS, false );
            GetDlgItem( IDC_TXT_START_DATE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_DATE_START, false );
            GetDlgItem( IDC_TXT_END_DATE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_DATE_END, false );
         }
         else if( strValue == I_("ActivityID") )
         {
            // Edit Ctrl - ActivityID
            ReInitControl(IDC_EDT_SEARCH_VALUE, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, ifds::ActivityID, CTRLFLAG_DEFAULT);

            GetDlgItem( IDC_TXT_USING )->ShowWindow( SW_SHOW );
            ConnectControl( IDC_EDT_SEARCH_VALUE, true );
            GetControl( IDC_EDT_SEARCH_VALUE )->ConnectToData( true );
            LoadControl( IDC_EDT_SEARCH_VALUE );
            ShowControl( IDC_EDT_SEARCH_VALUE, true );

            // Change to Combo box, and Show Control
            GetDlgItem( IDC_CMB_TYPE )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_TYPE, false );
            GetControl( IDC_CMB_TYPE )->ConnectToData( false );
            ShowControl( IDC_CMB_TYPE, false );

            // Change Process Category
            GetDlgItem( IDC_CMB_CATEGORY )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_CATEGORY, false );
            GetControl( IDC_CMB_CATEGORY )->ConnectToData( false );
            ShowControl( IDC_CMB_CATEGORY, false );

            GetDlgItem( IDC_TXT_NETWORK_ID )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_NETWORK_ID, false );
            GetDlgItem( IDC_TXT_PROCESS_STATUS )->ShowWindow( SW_HIDE );
            ShowControl( IDC_CMB_PROCESS_STATUS, false );
            GetDlgItem( IDC_TXT_START_DATE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_DATE_START, false );
            GetDlgItem( IDC_TXT_END_DATE )->ShowWindow( SW_HIDE );
            ShowControl( IDC_DATE_END, false );
         }
         else if( strValue == I_("ProcessCategory") )
         {
            // Edit Ctrl
            ReInitControl(IDC_EDT_SEARCH_VALUE, BF::NullContainerId, ifds::SearchUsing, CTRLFLAG_DEFAULT);

            GetDlgItem( IDC_TXT_USING )->ShowWindow( SW_SHOW );
            ConnectControl( IDC_EDT_SEARCH_VALUE, false );
            GetControl( IDC_EDT_SEARCH_VALUE )->ConnectToData( false );
            ShowControl( IDC_EDT_SEARCH_VALUE, false );

            // Change to Combo box, and Show Control
            GetDlgItem( IDC_CMB_TYPE )->ShowWindow( SW_HIDE );
            ConnectControl( IDC_CMB_TYPE, false );
            GetControl( IDC_CMB_TYPE )->ConnectToData( false );
            ShowControl( IDC_CMB_TYPE, false );

            // Connect to Combo box for Process Category
            GetDlgItem( IDC_CMB_CATEGORY )->ShowWindow( SW_SHOW );
            ConnectControl( IDC_CMB_CATEGORY, true );
            GetControl( IDC_CMB_CATEGORY )->ConnectToData( true );
            ShowControl( IDC_CMB_CATEGORY, true );
            LoadControl( IDC_CMB_CATEGORY );

            GetDlgItem( IDC_TXT_NETWORK_ID )->ShowWindow( SW_SHOW );
            ShowControl( IDC_CMB_NETWORK_ID, true );
            GetDlgItem( IDC_TXT_PROCESS_STATUS )->ShowWindow( SW_SHOW );
            ShowControl( IDC_CMB_PROCESS_STATUS, true );
            GetDlgItem( IDC_TXT_START_DATE )->ShowWindow( SW_SHOW );
            ShowControl( IDC_DATE_START, true );
            GetDlgItem( IDC_TXT_END_DATE )->ShowWindow( SW_SHOW );
            ShowControl( IDC_DATE_END, true );
         }
   		break;
	   }
      default:
			break;
   }
	setUpdateFlag (false);
}

//******************************************************************************

void MsgSearchDlg::OnBtnSearch()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch"));
   CWaitCursor wait;

   GetDlgItem(IDC_BTN_SEARCH)->SetFocus();
   if (discardUpdates())
   {
      if (getParent()->performSearch(this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
         SEARCH_START) > WARNING)
      {
         // Display error
         ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
      }
   }
}

//******************************************************************
BOOL MsgSearchDlg::PreTranslateMessage(MSG* pMsg) 
{
   //do not allow F4 on the edit controls that are not updateable
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//*************************************************************************
bool MsgSearchDlg::discardUpdates()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("discardUpdates"));
   bool bCanSearch = true;
   
   BFWorkSession *bfWorkSession = getBFWorkSession();

   if (bfWorkSession && bfWorkSession->hasNonHostUpdates())
   {
      DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, 
         TXT_DISCARD_MSGB, TXT_DISCARD);
      
      if (discardDlg.DoModal() == IDCANCEL)
      {
         bCanSearch = false;
      }
      else 
      {
         //discard everything and close the dialogs
         getGIContainer()->destroyGUIChildren(this);
      }
   }
//clean-up the work session before each search, even if there are no updates
   if (bCanSearch && bfWorkSession)
   {
      bfWorkSession->cleanupWorkSession();
   }
   return bCanSearch;
}

void MsgSearchDlg::OnSelchangeCmbUsing()
{
   CString cstrComboBoxText;
   GetDlgItem( IDC_CMB_USING )->GetWindowText( cstrComboBoxText );
   cstrComboBoxText += I_(":");
   GetDlgItem( IDC_TXT_USING )->SetWindowText( cstrComboBoxText );
}

bool MsgSearchDlg::doSend ( GenericInterface *rpGICaller, const I_CHAR *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("doSend"));
   bool bRet = true;
   DString Message( szMessage );
   if( Message == I_("CLOSE") )
   {
      BFWorkSession *bfWorkSession = getBFWorkSession();
      if( bfWorkSession)
      {
         bfWorkSession->cleanupWorkSession();   // A Beaut
      }
      // Close
      getGIContainer()->destroySelf( this );
      return( true );
   }
   return( false );
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/MsgSearchDlg.cpp-arc  $
// 
//    Rev 1.4   Sep 15 2005 15:14:14   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Apr 04 2005 16:04:42   hernando
// Incident #279858 - Displays the correct 'Using' label.
// 
//    Rev 1.2   Feb 24 2005 16:29:36   hernando
// PET1117 FN66-68 - Handle the Close button.
// 
//    Rev 1.1   Feb 22 2005 16:36:22   hernando
// PET1117 FN66-68 - Changed MsgProcessCategory control to populate based on the associated sub set.
// 
//    Rev 1.0   Feb 21 2005 09:59:50   hernando
// Initial revision.
