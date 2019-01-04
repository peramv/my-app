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
// ^FILE   : CloneAccountDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2006
//
// ----------------------------------------------------------
//
// ^CLASS    : CloneAccountDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"
#include <assert.h>
#include "mfdstc.h"

#include "cloneaccountdlg.h"

#include <ifastbp\cloneaccountprocessincludes.h>
#include <ifastbp\cloneaccountprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

extern CLASS_IMPORT const I_CHAR *CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_CLONE_ACCOUNT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<CloneAccountDlg> dlgCreator(CMD_GUI_CLONE_ACCOUNT);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("CloneAccountDlg");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
CloneAccountDlg::CloneAccountDlg (CWnd* pParent, 
                                  GenericInterfaceContainer* pGIC, 
                                  GenericInterface* pGIParent, 
                                  const Command& rCommand)
: BaseMainDlg(CloneAccountDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_dstrCaller (NULL_STRING),
m_accountNum (NULL_STRING),
m_pCWndF4Focus (NULL),
m_popSalesRepCreateQuestion (false)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(CloneAccountDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void CloneAccountDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CloneAccountDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY CloneAccountDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter (MFCAN_IP_PARAM::CALLER, m_dstrCaller);
   getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, m_accountNum);
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(CloneAccountDlg, BaseMainDlg)
//{{AFX_MSG_MAP(CloneAccountDlg)
ON_MESSAGE (UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_MESSAGE (UM_OPENBRANCHLISTDLG, OpenBranchListDlg)
ON_MESSAGE (UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL CloneAccountDlg::OnInitDialog() 
{
   TRACE_METHOD (CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void CloneAccountDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

   AddControl( CTRL_COMBO, IDC_CMB_ACCT_DESIGNATION, CLONE_ACCOUNT, 
               ifds::AcctDesignation, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_TAX_TYPE, CLONE_ACCOUNT, 
               ifds::TaxType, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl ( CTRL_DATE, IDC_DTP_EFF_DATE, CLONE_ACCOUNT, 
                ifds::EffectiveDate, 
                CTRLFLAG_DEFAULT);
   AddControl( CTRL_EDIT, IDC_EDT_BROKER, CLONE_ACCOUNT, 
               ifds::BrokerCode, 
               CTRLFLAG_DEFAULT);
   AddControl( CTRL_COMBO, IDC_CMB_INTERMEDIARY_CODE, CLONE_ACCOUNT, 
               ifds::InterCode, 
               CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl( CTRL_EDIT, IDC_EDT_INTERMEDIARY_ACCT_NBR, CLONE_ACCOUNT, 
               ifds::InterAccount, 
               CTRLFLAG_DEFAULT);
   AddControl( CTRL_EDIT, IDC_EDT_ALT_ACC_NUM, CLONE_ACCOUNT, 
               ifds::AltAccount, 
               CTRLFLAG_DEFAULT);
   AddControl ( CTRL_STATIC, IDC_STC_BROKER_NAME, CLONE_ACCOUNT, 
                ifds::BrokerName, 
                CTRLFLAG_DEFAULT);
   AddControl( CTRL_EDIT, IDC_EDT_BRANCH, CLONE_ACCOUNT, 
               ifds::BranchCode, 
               CTRLFLAG_DEFAULT);
   AddControl ( CTRL_STATIC, IDC_STC_BRANCH_NAME, CLONE_ACCOUNT, 
                ifds::BranchName, 
                CTRLFLAG_DEFAULT);
   AddControl( CTRL_EDIT, IDC_EDT_SALES_REP, CLONE_ACCOUNT, 
               ifds::SlsrepCode, 
               CTRLFLAG_DEFAULT);  
   AddControl ( CTRL_STATIC, IDC_STC_SALES_REP_NAME, CLONE_ACCOUNT, 
                ifds::SlsrepName, 
                CTRLFLAG_DEFAULT);
   doRefresh (this, NULL);
}


//******************************************************************************
bool CloneAccountDlg::doRefresh( GenericInterface *rpGICaller, 
                                 const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);
   ConnectControlsToData ();
   LoadControls ();
   //when called by the process from doRefresh, 
   SetDlgCaption ();
   return true;
}

//*************************************************************************
void CloneAccountDlg::SetDlgCaption ()
{
   DString caption (m_accountNum),
      name;

	DSTCWorkSession *pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	pDSTCWorkSession ->
         getFirstSequenced01AccountholderEntityName (getDataGroupId(), m_accountNum, name);
	CString cstrAcctOwner;
	cstrAcctOwner.LoadString(TXT_ACCOUNT_OWNER);
   caption += DString(cstrAcctOwner) + name + I_(";");
   SetCaption (caption);
}


//*************************************************************************
void CloneAccountDlg::ControlUpdated( UINT controlID, 
                                      const DString &strValue)
{
   switch (controlID)
   {
      case IDC_EDT_SALES_REP:
      {

         DString shouldAskForRep;

         getParent ()->getField ( this,
                                 CLONE_ACCOUNT,
                                 ShouldAskForRep,
                                 shouldAskForRep,
                                 false);
         if (shouldAskForRep == I_("Y"))
         {
	         if (m_popSalesRepCreateQuestion) //only if a change in salesrep value
	         {
               CString noSlsrep;

               noSlsrep.LoadString (TXT_NO_SLSREP);

               int choice = AfxMessageBox (noSlsrep, MB_YESNO | MB_ICONQUESTION);

               if (choice == IDYES) //should turn the create rep flag on
               {
                  getParent ()->setField (this, CLONE_ACCOUNT, ifds::CreateRep, I_("Y"));
               }
               else
               {
                  //turn the create rep flag off
                  getParent ()->setField (this, CLONE_ACCOUNT, ifds::CreateRep, I_("N"));
               }
               GetControl (IDC_EDT_SALES_REP)->LoadErrorState ();
            }
         }
         else
         {
            //turn the create rep flag off
            getParent ()->setField (this, CLONE_ACCOUNT, ifds::CreateRep, I_("N"));
         }
      }
      default:
         break;
   }
}

//******************************************************************************
bool CloneAccountDlg::SetDataFromControl( UINT controlID,
                                          const DString &strValue,
                                          bool bFormatted,
                                          SEVERITY &sevRtn,
                                          int index /*= 0*/)
{
	if (controlID == IDC_EDT_SALES_REP)
   {
      DString slsrepCode;
      
      getParent()->getField ( this, 
                              CLONE_ACCOUNT, 
                              ifds::SlsrepCode, 
                              slsrepCode, 
                              false);
      m_popSalesRepCreateQuestion = strValue != slsrepCode;
      if (m_popSalesRepCreateQuestion) //turn the create rep flag off
      {
         getParent ()->setField (this, CLONE_ACCOUNT, ifds::CreateRep, I_("N"));
      }
   }
   return false;
}

//******************************************************************
BOOL CloneAccountDlg::PreTranslateMessage(MSG* pMsg) 
{
   if ( pMsg->message == WM_KEYDOWN && 
       (int) (pMsg->wParam) == VK_F4 && 
       !IsSelectedCtrlUpdateable ())
   {
      return TRUE;
   }
   if ( pMsg->message == WM_KEYDOWN && 
        (int) (pMsg->wParam) == VK_F4)
   {
      m_pCWndF4Focus = GetFocus ();
      if (m_pCWndF4Focus == GetDlgItem (IDC_EDT_BROKER))
      {
         PostMessage (UM_OPENBROKERLISTDLG);
      }
      else if (m_pCWndF4Focus == GetDlgItem (IDC_EDT_BRANCH)) 
      {
         PostMessage (UM_OPENBRANCHLISTDLG);
      } 
      else if (m_pCWndF4Focus == GetDlgItem (IDC_EDT_SALES_REP)) 
      {
         PostMessage (UM_OPENSLSREPLISTDLG);
      }
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//F4 helper dialogs
//******************************************************************
LRESULT CloneAccountDlg::OpenBrokerListDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenBrokerListDlg"));
   CWaitCursor wait;

   try
   {
      DString brokerCode;

      GetControlText (IDC_EDT_BROKER, brokerCode);
      setParameter (I_("BrokerCode"), brokerCode);

//invoke the broker dialog helper dialog
      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_BROKER, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter (I_("BrokerCode"), brokerCode);
               if (!brokerCode.empty ())
               {
		            getParent()->setField ( this, 
                                          CLONE_ACCOUNT, 
                                          ifds::BrokerCode, 
                                          brokerCode, 
                                          false);
                  LoadControl (IDC_EDT_BROKER);
                  LoadControl (IDC_STC_BROKER_NAME);
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
   return 0;
}

//******************************************************************
LRESULT CloneAccountDlg::OpenBranchListDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenBranchListDlg"));
   CWaitCursor wait;

   try
   {
      DString brokerCode;

      GetControlText (IDC_EDT_BROKER, brokerCode);
      setParameter (I_("BrokerCode"), brokerCode);
//invoke the branch dialog helper dialog
      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_BRANCH, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString branchCode;

               getParameter (I_("BranchCode"), branchCode);
               if (!branchCode.empty ())
               {
		            getParent()->setField ( this, 
                                          CLONE_ACCOUNT, 
                                          ifds::BranchCode, 
                                          branchCode, 
                                          false);
                  LoadControl (IDC_EDT_BRANCH);
                  LoadControl (IDC_STC_BRANCH_NAME);
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
   return 0;
}

//******************************************************************
LRESULT CloneAccountDlg::OpenSlsRepListDlg (WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OpenSlsRepListDlg"));
   CWaitCursor wait;

   try
   {
      DString brokerCode,
         branchCode;

      GetControlText (IDC_EDT_BROKER, brokerCode);
      setParameter (I_("BrokerCode"), brokerCode);
      GetControlText (IDC_EDT_BRANCH, branchCode);
      setParameter (I_("BranchCode"), branchCode);
//invoke the sales rep dialog helper dialog
      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_SLSREP, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString slsrepCode;

               getParameter (I_("AgentCode"), slsrepCode);
               if (!slsrepCode.empty ())
               {
		            getParent()->setField ( this, 
                                          CLONE_ACCOUNT, 
                                          ifds::SlsrepCode, 
                                          slsrepCode, 
                                          false);
                  LoadControl (IDC_EDT_SALES_REP);
                  LoadControl (IDC_STC_SALES_REP_NAME);
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
   return 0;
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CloneAccountDlg.cpp-arc  $
// 
//    Rev 1.2   Nov 24 2011 15:48:42   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.1   Nov 10 2006 18:07:46   popescu
// PET 2281/FN 01
// 
//    Rev 1.0   Nov 08 2006 17:33:52   popescu
// Initial revision.
// 
// 
*/
