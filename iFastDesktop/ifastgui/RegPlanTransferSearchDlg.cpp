//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : RegPlanTransferSearchDlg.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS    : 
// ^SUBCLASS :    
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
// RegPlanTransferSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include <algorithm>

#include "mfdstc.h"
#include "RegPlanTransferSearchDlg.h"
#include <ifastbp\regplantransfersearchprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastbp\EntityProcessIncludes.h>
#include <configmanager.hpp>

using std::vector;

extern CLASS_IMPORT const I_CHAR* CMD_GUI_REG_PLAN_TRANSFER_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_USERDEFMAT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_VERSION_FEATURE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_PLAN_TRANSFER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH;


#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RegPlanTransferSearchDlg > dlgCreator( CMD_GUI_REG_PLAN_TRANSFER_SEARCH );

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//******************************************************************************
// RegPlanTransferSearchDlg dialog

namespace
{   
   const I_CHAR * const CLASSNAME               = I_( "RegPlanTransferSearchDlg" );
   const I_CHAR * const LV_REG_PLAN_TRANSFER    = I_( "RegPlanTransferList" );
   const I_CHAR * const LV_REG_PLAN_TRANSF_ALLOC = I_( "RegPlanTransfAllocList" );
   const I_CHAR * const SPACE_STRING            = I_( " " ); 
   const I_CHAR * const N                       = I_( "N" ); 
}

namespace CND
{  
   // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_INVALID_CONTRACT_TYPE;
   extern const long GUI_INVALID_POLICY;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForDofBirth;

   // Take these out as soon as we have them in the view
   extern CLASS_IMPORT const BFTextFieldId RegPlanTransferSrchHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId RegPlanTransferHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId RegPlanTransfAllocHeadingSet;
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId RegTransferSearchCriteria;
}

namespace CONTROL_GROUP
{   
   const UINT ACCOUNT_INFORMATION_GROUP   = 1;   
}


//******************************************************************************
RegPlanTransferSearchDlg::RegPlanTransferSearchDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
   : BaseMainDlg( RegPlanTransferSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(RegPlanTransferSearchDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
void RegPlanTransferSearchDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RegPlanTransferSearchDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(RegPlanTransferSearchDlg, BaseMainDlg)
   //{{AFX_MSG_MAP(RegPlanTransferSearchDlg)
   ON_BN_CLICKED( IDC_BTN_SEARCH, OnBtnSearch)
   ON_BN_CLICKED( IDC_BTN_REFRESH, OnBtnRefresh)
   ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore)
   ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
   ON_NOTIFY(NM_DBLCLK, IDC_LV_REG_PLAN_TRANSFERS, OnDblclkLvResults)
   ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
   ON_MESSAGE( UM_OPENBRANCHLISTDLG, OpenBranchListDlg )
   ON_MESSAGE( UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg )
   ON_MESSAGE (UM_OPENEXTERNALINSTITUTION, OpenExternalInstitutionSearchDlg)

   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
SEVERITY RegPlanTransferSearchDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
BOOL RegPlanTransferSearchDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   return(TRUE);  // return TRUE unless you set the focus to 
}


//******************************************************************************
void RegPlanTransferSearchDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   //SetUserAccesFunctionCode(UAF::SEG_FUND_MULTI_CONTRACT);   

   // Populate dialog    
   //bEffDateChanged = false;

   AddListControl( CLASSNAME, IDC_LV_REG_PLAN_TRANSFERS,       LV_REG_PLAN_TRANSFER,     ifds::RegPlanTransferSrchHeadingSet,    IFASTBP_PROC::REG_PLAN_TRANSFER_LIST,0, true, LISTFLAG_NOT_AUTO_ADD);

   AddControl( CTRL_EDIT, IDC_EDT_ACCOUNT_NUMBER,   IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SrchAccountNum,     CTRLFLAG_DEFAULT, 1);
   AddControl( CTRL_EDIT, IDC_EDT_INST_CODE,        IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SrchExtInst,        CTRLFLAG_DEFAULT, 1);
   AddControl( CTRL_EDIT, IDC_EDT_INSTITUTION_NAME, IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SrchExtInstName,    CTRLFLAG_DEFAULT, 1);
   AddControl( CTRL_EDIT, IDC_EDT_RELINQ_ACCT_NUM,  IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SrchExtInstAcct,    CTRLFLAG_DEFAULT, 1);
   AddControl( CTRL_EDIT, IDC_EDT_BROKER,           IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SrchBroker,         CTRLFLAG_DEFAULT, 1);
   AddControl( CTRL_EDIT, IDC_EDT_BRANCH,           IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SrchBranch,         CTRLFLAG_DEFAULT, 1);
   AddControl( CTRL_EDIT, IDC_EDT_SALESREP,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SrchSlsrep,         CTRLFLAG_DEFAULT, 1);

   AddControl( CTRL_STATIC, IDC_TXT_BROKER_NAME,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::BrokerName,    CTRLFLAG_DEFAULT, 1);      
   AddControl( CTRL_STATIC, IDC_TXT_BRANCH_NAME,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::BranchName,    CTRLFLAG_DEFAULT, 1);
   AddControl( CTRL_STATIC, IDC_TXT_SALES_REP_NAME,      IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SlsrepName,    CTRLFLAG_DEFAULT, 1);
   AddControl( CTRL_STATIC, IDC_TXT_SALES_REP_ALT_NAME,  IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SlsrepAltName, CTRLFLAG_DEFAULT, 1);




   AddControl( CTRL_COMBO,IDC_CMB_SEARCH,           IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::RegTransferSearchCriteria,  CTRLFLAG_INITCOMBO_BY_SUB_LIST, 1);



   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);
   ConnectControlsToData(1);
   LoadControl( IDC_CMB_SEARCH);
   //   LoadControls(IDC_LV_REG_PLAN_TRANSFERS);

   GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(false);

   doRefresh(this, NULL_STRING);

   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   //GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::CONTRACTINFO_LIST ) );

   ShowSearchControls(I_("AccountNum"));
}





//******************************************************************************
void RegPlanTransferSearchDlg::OnBtnRefresh() 
{
   //ResetListItem(IDC_LV_REG_PLAN_TRANSFERS);
   TRACE_METHOD( CLASSNAME, I_( "OnBtnRefresh" ) );

   //GetDlgItem(IDC_BTN_BROWSE)->SetFocus();
   CWaitCursor wait;

   //getParent()->refresh(

   //getParent()->reset(this, IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   //getParent()->reset(this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);

   //ReregisterObservers();
   //CheckPermission();
   GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(false);

   getParent()->send( this, I_("RESET"));

   //ConnectControlsToData(1, false);
   //ConnectControlsToData(1, true);
   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);
   LoadControls(1);
}





//******************************************************************************
bool RegPlanTransferSearchDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{
   TRACE_METHOD( CLASSNAME, I_("doRefresh"));

   DString strOrgCommand(szOriginalCommand);

   int iItemNumber = 0;
   iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   if( iItemNumber != 0 )
   {
      ConnectControlToData(IDC_LV_REG_PLAN_TRANSFERS, true);
      LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);
      LoadControls(IDC_LV_REG_PLAN_TRANSFERS);
   }
   else
   {
      //AddToListControl (IDC_LV_REG_PLAN_TRANSFERS);
   }   

   return(true);
}

//*******************************************************************************************
void RegPlanTransferSearchDlg::DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(true);
}


//****************************************************************************
void RegPlanTransferSearchDlg::OnBtnSearch() 
{
   CWaitCursor wait;
   SetMessageStatusBar( TXT_SEARCHING );
   SEVERITY sev = NO_SEVERITY;

   DString strValidCriteria, strPending;
   getParent()->getField(this, REG_PLAN_TRANSFER_SEARCH::Validation_OK, strValidCriteria, false);

   if(N==strValidCriteria)
   {
      CString strValidCriteria;
      strValidCriteria.LoadString(TXT_VALID_CRITERIA);
      AfxMessageBox(strValidCriteria, MB_OK | MB_ICONSTOP);
      return;
   }

   GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(false);
   sev = getParent()->performSearch(this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, SEARCH_START );

   LoadListControl(IDC_LV_REG_PLAN_TRANSFERS);

   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

////****************************************************************************
//void RegPlanTransferSearchDlg::OnBtnMore() 
//{
//   	CWaitCursor wait;
//    SetMessageStatusBar( TXT_SEARCHING );
//    SEVERITY sev = NO_SEVERITY;
//    sev = getParent()->performSearch(this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, SEARCH_NEXT_BLOCK);
//}

//*****************************************************************************
void RegPlanTransferSearchDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   if( controlID == IDC_CMB_SEARCH )
   {
      DString dstrSearchType;
      getParent()->getField(this, ifds::RegTransferSearchCriteria, dstrSearchType, false);
      ShowSearchControls(dstrSearchType);
   }
   setUpdateFlag( false );      // Clears Update for Dialog
}

void RegPlanTransferSearchDlg::ShowSearchControls(DString dstrSearchType)
{
   bool bShowAcctSearch       = dstrSearchType == I_("AccountNum");
   bool bShowSlsrepSearch     = dstrSearchType == I_("BranchBrokerSlsrep");
   bool bShowInstSearch       = dstrSearchType == I_("ExternalInstitution");
   bool bShowInstAcctSearch   = dstrSearchType == I_("ExternalInstitutionAcct");

   GetDlgItem(IDC_EDT_ACCOUNT_NUMBER)->ShowWindow(bShowAcctSearch);
   GetDlgItem(IDC_LBL_ACC_NBR)->ShowWindow(bShowAcctSearch);

   GetDlgItem(IDC_STATIC_RELINQ_INST_NAME)->ShowWindow(bShowInstSearch);
   GetDlgItem(IDC_EDT_INST_CODE)->ShowWindow(bShowInstSearch);
   GetDlgItem(IDC_EDT_INSTITUTION_NAME)->ShowWindow(bShowInstSearch);

   GetDlgItem(IDC_STATIC_RELINQ_ACCT)->ShowWindow(bShowInstAcctSearch);
   GetDlgItem(IDC_EDT_RELINQ_ACCT_NUM)->ShowWindow(bShowInstAcctSearch);

   GetDlgItem(IDC_LBL_BROKER)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_EDT_BROKER)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_LBL_BRANCH)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_EDT_BRANCH)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_LBL_SLSREP)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_EDT_SALESREP)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_TXT_BROKER_NAME)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_TXT_BRANCH_NAME)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_TXT_SALES_REP_NAME)->ShowWindow(bShowSlsrepSearch);
   GetDlgItem(IDC_TXT_SALES_REP_ALT_NAME)->ShowWindow(bShowSlsrepSearch);
}

void RegPlanTransferSearchDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore") );

   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   if( getParent()->performSearch( this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_REG_PLAN_TRANSFERS );   
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_REG_PLAN_TRANSFERS )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//******************************************************************************
void RegPlanTransferSearchDlg::OnBtnBrowse() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBrowse" ) );

   GetDlgItem(IDC_BTN_BROWSE)->SetFocus();
   CWaitCursor wait;

   DString strAccNum, strFund, strClass, strAllFundMode(I_("N")), strTransId,
      strTransNum, strTradeDate, strTransType;

   getParent()->getField(this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::AccountNum, strAccNum, true);

   getParent()->setParameter (I_("AccountNum"), strAccNum);


   try
   {
      bool bModal = true;
      E_COMMANDRETURN eRtn = CMD_OK;
      SetMessageStatusBar( TXT_LOAD_TRANSACTION_PENDING );
      eRtn = invokeCommand( getParent(), CMD_BPROC_REG_PLAN_TRANSFER, PROC_NO_TYPE, false, NULL );
      switch( eRtn )
      {
      case CMD_OK:
      case CMD_CANCEL:
      case CMD_MODELESS_INPROCESS:
         break;
      default:
         // Display error
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
   SetMessageStatusBar( NULL_STRING );
}

void RegPlanTransferSearchDlg::OnDblclkLvResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvResults" ) );
   if (GetList(IDC_LV_REG_PLAN_TRANSFERS)->GetNextSelection()>=0)
      OnBtnBrowse();
   *pResult = 0;
}


BOOL RegPlanTransferSearchDlg::PreTranslateMessage( MSG* pMsg ) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus()== GetDlgItem( IDC_EDT_BROKER ) )
         PostMessage( UM_OPENBROKERLISTDLG );
      else if( GetFocus()== GetDlgItem( IDC_EDT_BRANCH ) )
         PostMessage( UM_OPENBRANCHLISTDLG );
      else if( GetFocus() == GetDlgItem( IDC_EDT_SALESREP ) )
         PostMessage( UM_OPENSLSREPLISTDLG );
      else if( GetFocus()== GetDlgItem( IDC_EDT_INST_CODE ) )
         PostMessage( UM_OPENEXTERNALINSTITUTION );
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}


LRESULT RegPlanTransferSearchDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode;

      GetControlText( IDC_EDT_BROKER, dstrBrokerCode );
      setParameter( MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode );
      setParameter( MFCAN_IP_PARAM::CALLER, I_("RegPlanTransferSearch") );
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
      case CMD_OK:
      case CMD_MODELESS_INPROCESS:
         {
            //get the broker code that the user selected from the branch list and 
            //set the field on the account object
            DString dstrBrokerCode;

            getParameter( MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode );
            if( !dstrBrokerCode.empty() )
            {
               bool bSuccess = SetControlText( IDC_EDT_BROKER, dstrBrokerCode );
               BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BROKER ));
               if( !bSuccess && pBC )
                  pBC->Load();
               if( pBC && pBC->IsToolTipVisible() )
                  pBC->ToggleToolTip();
            }
            break;
         }
      case CMD_CANCEL:
         break;
      default:
         // Display error
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

//******************************************************************

LRESULT RegPlanTransferSearchDlg::OpenBranchListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBranchListDlg" ) );
   //
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode;

      GetControlText( IDC_EDT_BROKER, dstrBrokerCode );
      setParameter( MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode );
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
      case CMD_OK:
      case CMD_MODELESS_INPROCESS:
         {
            //get the broker code that the user selected from the branch list and 
            //set the field on the account object
            DString dstrBranchCode;

            getParameter( MFCAN_IP_PARAM::BRANCH_CODE, dstrBranchCode );
            if( !dstrBrokerCode.empty() )
            {
               bool bSuccess = SetControlText( IDC_EDT_BRANCH, dstrBranchCode );
               BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BRANCH ));
               if( !bSuccess && pBC )
                  pBC->Load();
               if( pBC && pBC->IsToolTipVisible() )
                  pBC->ToggleToolTip();
            }
            break;
         }
      case CMD_CANCEL:
         break;
      default:
         // Display error
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

//******************************************************************

LRESULT RegPlanTransferSearchDlg::OpenSlsRepListDlg( WPARAM, LPARAM ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenSlsRepListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode, dstrBranchCode;

      GetControlText( IDC_EDT_BROKER, dstrBrokerCode );
      setParameter( MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode );
      GetControlText( IDC_EDT_BRANCH, dstrBranchCode );
      setParameter( MFCAN_IP_PARAM::BRANCH_CODE, dstrBranchCode );

      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_SLSREP, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
      case CMD_OK:
      case CMD_MODELESS_INPROCESS:
         {
            //get the broker code that the user selected from the branch list and 
            //set the field on the account object
            DString dstrAgentCode;

            getParameter( MFCAN_IP_PARAM::SALES_REP_CODE, dstrAgentCode );
            if( !dstrBrokerCode.empty() )
            {
               bool bSuccess = SetControlText( IDC_EDT_SALESREP, dstrAgentCode );
               BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_SALESREP ));
               if( !bSuccess && pBC )
                  pBC->Load();
               if( pBC && pBC->IsToolTipVisible() )
                  pBC->ToggleToolTip();
            }
            break;
         }
      case CMD_CANCEL:
         break;
      default:
         // Display error
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

LRESULT RegPlanTransferSearchDlg::OpenExternalInstitutionSearchDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OpenExternalInstitutionSearchDlg"));
   try
   {
      DString tradeKey;

      setParameter (MFCAN_IP_PARAM::LIST_KEY, tradeKey);
      setParameter (MFCAN_IP_PARAM::CALLER,   I_("RegPlanTransfer"));

      E_COMMANDRETURN eRtn = CMD_CANCEL;
      eRtn = invokeCommand( getParent(), CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH, PROC_SUPPORT, true, NULL );
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString extInstitutionCode;

               getParameter (I_("ExternalInstitution"), extInstitutionCode);
               if (!extInstitutionCode.empty ())
               {
                  getParent()->setField ( this, IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, ifds::SrchExtInst, extInstitutionCode, false);
                  LoadControl(IDC_EDT_INST_CODE);
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox ( FRAMEBELOW (), GETHIGHESTSEVERITY ());
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
   return 0;
}
