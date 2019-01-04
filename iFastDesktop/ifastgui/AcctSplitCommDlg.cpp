//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : AcctSplitCommDlg.cpp
// ^AUTHOR : 
// ^DATE   : Aug 23, 2001
//
// ^CLASS    : AcctSplitCommDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "AcctSplitCommDlg.h"
#include <ifastbp\AcctSplitCommProcessIncludes.h>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <uibase\DSTListCtrl.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\DSTEdit.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastbp\NASUProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCT_SPLITCOMM;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AcctSplitCommDlg > dlgCreator( CMD_GUI_ACCT_SPLITCOMM );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                     = I_( "AcctSplitCommDlg" );
   const I_CHAR * const LV_ACCT_SPLITCOMM_DATE_LIST   = I_( "AcctSplitCommDateList" );
   const I_CHAR * const LV_ACCT_SPLITCOMM_REP_LIST    = I_( "AcctSplitCommRepList" );   
   const I_CHAR * const YES                  = I_( "Y" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AddPerm;
   extern CLASS_IMPORT const BFTextFieldId DelPerm;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCT_SPLIT_COMM;
}

//******************************************************************************
// Constructor
//******************************************************************************
AcctSplitCommDlg::AcctSplitCommDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( AcctSplitCommDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, _bDisableAdd (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT( AcctSplitCommDlg )
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************
AcctSplitCommDlg::~AcctSplitCommDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void AcctSplitCommDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( AcctSplitCommDlg )
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( AcctSplitCommDlg, BaseMainDlg )
//{{AFX_MSG_MAP( AcctSplitCommDlg )
ON_BN_CLICKED( IDC_BTN_ADD_DATE, OnBtnAddDate )
ON_BN_CLICKED( IDC_BTN_DEL_DATE, OnBtnDelDate )
ON_BN_CLICKED( IDC_BTN_ADD_REP, OnBtnAddRep )
ON_BN_CLICKED( IDC_BTN_DELETE, OnBtnDelRep )  
ON_BN_CLICKED( IDRESET, OnBtnReset )
ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
ON_MESSAGE( UM_OPENBRANCHLISTDLG, OpenBranchListDlg )
ON_MESSAGE( UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL AcctSplitCommDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   SetShrAcctCaption(_dstrShrNum, _dstrAccountNum, _dstrEntityName);
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void AcctSplitCommDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   SetUserAccesFunctionCode(UAF::ACCT_SPLIT_COMM);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_DATE, IDC_LV_SPLIT_DATE);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_REP, IDC_LV_SPLIT_REP);
   addBtnDeleteForPermissionCheck(IDC_BTN_DEL_DATE, IDC_LV_SPLIT_DATE);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_SPLIT_REP);
   addControls( );
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY AcctSplitCommDlg::doInit()
{
   getParameter( ACCTSPLIT::ACCOUNT_NUM, _dstrAccountNum );
   getParameter( ACCTSPLIT::SHR_NUM, _dstrShrNum );      
   getParameter( NASULIT::CREATING_ACCOUNT, _dstrCreateAcct );
   getParameter( NASULIT::CREATING_SHAREHOLDER, _dstrCreateShr );
   SetAccount( _dstrAccountNum );
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), _dstrAccountNum, _dstrEntityName );   
   return(NO_CONDITION);
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void AcctSplitCommDlg::addControls( )
{
   DString dstrAccountType;
   // Initializes the Account Level Split Commission Date List.
   AddListControl( CLASSNAME, IDC_LV_SPLIT_DATE, LV_ACCT_SPLITCOMM_DATE_LIST, ifds::AcctSplitCommDateHeadingSet, 
                   IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, 0, true);

   // Initializes the Account Level Split Commission Rep List as the child of the Split Commission Date List
   AddListControl( CLASSNAME, IDC_LV_SPLIT_REP, LV_ACCT_SPLITCOMM_REP_LIST, ifds::AcctSplitCommRepHeadingSet, 
                   IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST, IDC_LV_SPLIT_DATE, true);

   AddControl( CTRL_DATE,  IDC_DTP_EFFECTIVE,        IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, ifds::EffectiveDate, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_DATE );
   AddControl( CTRL_DATE,  IDC_DTP_STOP,        IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, ifds::StopDate, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_DATE );
   AddControl( CTRL_STATIC,   IDC_STATIC_RENAMT,  IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, ACCTSPLIT::TOTAL_RENUNCIATION, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_REP );
   AddControl( CTRL_COMBO,   IDC_CMB_ENTITY,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST,    ifds::CommEntType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SPLIT_REP );

   AddControl( CTRL_EDIT,   IDC_EDT_BROKER,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST,    ifds::AgencyCode, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_REP );
   AddControl( CTRL_STATIC,   IDC_STATIC_BROKER,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST, ifds::BrokerName, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_REP );
   AddControl( CTRL_EDIT,   IDC_EDT_BRANCH,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST,    ifds::BranchCode, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_REP );
   AddControl( CTRL_STATIC,   IDC_STATIC_BRANCH,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST, ifds::BranchName, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_REP );
   AddControl( CTRL_EDIT,   IDC_EDT_SALESREP,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST,    ifds::AgentCode, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_REP );
   AddControl( CTRL_STATIC,   IDC_STATIC_SALESREP,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST, ifds::SlsrepName, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_REP );
   AddControl( CTRL_EDIT,   IDC_EDT_PERCENT,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST,    ifds::CommPrcnt, CTRLFLAG_DEFAULT, IDC_LV_SPLIT_REP );
   AddControl( CTRL_COMBO,   IDC_CMB_PAYTYPE,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST,    ifds::TradesPayType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SPLIT_REP );
   AddControl( CTRL_COMBO,   IDC_CMB_SETTLEMENT,     IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST,    ifds::GrossOrNet, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SPLIT_REP);   
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_PERCENT ) )->SetAllowedChars( I_("0123456789.") );
   LoadListControl ( IDC_LV_SPLIT_DATE );  
   ConnectControlsToData ();
   LoadControls();
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool AcctSplitCommDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   DString  dstrAccountNum, dstrShrNum, dstrEntityName( NULL_STRING );
   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
   if( !dstrAccountNum.empty() )
   {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);
   }
   SetShrAcctCaption( dstrShrNum, dstrAccountNum, dstrEntityName);
   //reload list control
   LoadListControl( IDC_LV_SPLIT_DATE );

   return(true);
}

//******************************************************************************
//******************************************************************************
void AcctSplitCommDlg::OnBtnAddDate ( )
{
   AddToListControl( IDC_LV_SPLIT_DATE );   
   _bDisableAdd = true;
   GetDlgItem(IDC_BTN_ADD_DATE)->EnableWindow ( !_bDisableAdd );
}

//******************************************************************************
//******************************************************************************
void AcctSplitCommDlg::OnBtnDelDate ( )
{
   DeleteFromListControl( IDC_LV_SPLIT_DATE );
   _bDisableAdd = false;
   GetDlgItem(IDC_BTN_ADD_DATE)->EnableWindow ( !_bDisableAdd );
   LoadListControl ( IDC_LV_SPLIT_DATE );
}

//******************************************************************************
//******************************************************************************
void AcctSplitCommDlg::OnBtnAddRep ( )
{
   AddToListControl( IDC_LV_SPLIT_REP );
}
//******************************************************************************
//******************************************************************************
void AcctSplitCommDlg::OnBtnDelRep ( )
{
   DeleteFromListControl( IDC_LV_SPLIT_REP );
}

//******************************************************************************
//******************************************************************************
void AcctSplitCommDlg::OnBtnReset ( )
{
   ResetListItem( IDC_LV_SPLIT_REP );
   ResetListItem( IDC_LV_SPLIT_DATE );
}

//******************************************************************************

BOOL AcctSplitCommDlg::PreTranslateMessage(MSG* pMsg) 
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
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//****************************************************************************** 

LRESULT AcctSplitCommDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode;

      GetControlText( IDC_EDT_BROKER, dstrBrokerCode );
      setParameter( MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode );
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

LRESULT AcctSplitCommDlg::OpenBranchListDlg( WPARAM, LPARAM )
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

LRESULT AcctSplitCommDlg::OpenSlsRepListDlg( WPARAM, LPARAM ) 
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

//****************************************************************************** 

void AcctSplitCommDlg::DisplayByEntityType() 
{
   bool  bBroker, bBranch, bSalesRep;
   DString dstrTemp( NULL_STRING );

   // Set flags based on entity type
   getParent()->getField( this, IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST, ifds::CommEntType, dstrTemp, false);

   if( dstrTemp == I_("BROK") )
   {
      bBroker = true;
      bBranch = false;
      bSalesRep = false;
   }
   else if( dstrTemp == I_("BRNH") )
   {
      bBroker = true;
      bBranch = true;
      bSalesRep = false;
   }
   else if( dstrTemp == I_("CNTX") )
   {
      bBroker = false;
      bBranch = false;
      bSalesRep = false;
   }
   else if( dstrTemp == I_("SREP") )
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
   GetDlgItem( IDC_LBL_BROKER )->ShowWindow( bBroker );
   GetDlgItem( IDC_LBL_BRANCH )->ShowWindow( bBranch );
   GetDlgItem( IDC_LBL_SLSREP )->ShowWindow( bSalesRep );
   GetDlgItem( IDC_STATIC_BROKER )->ShowWindow( bBroker );
   GetDlgItem( IDC_STATIC_BRANCH )->ShowWindow( bBranch );
   GetDlgItem( IDC_STATIC_SALESREP )->ShowWindow( bSalesRep );
   ShowControl( IDC_EDT_BROKER, bBroker );
   ShowControl( IDC_EDT_BRANCH, bBranch );
   ShowControl( IDC_EDT_SALESREP, bSalesRep );
}

//****************************************************************************** 

void AcctSplitCommDlg::ControlUpdated(UINT controlID, const DString &dstrValue)
{
   switch( controlID )
   {
      case IDC_CMB_ENTITY:
         {
            DisplayByEntityType();
         }
         break;
      case IDC_EDT_PERCENT:
         {
            LoadControl ( IDC_STATIC_RENAMT );
         }
         break;
      case IDC_EDT_BROKER:
         {
            LoadControl ( IDC_STATIC_BROKER );
         }
         break;
      case IDC_EDT_BRANCH:
         {
            LoadControl ( IDC_STATIC_BRANCH );
         }
         break;
      case IDC_EDT_SALESREP:
         {
            LoadControl ( IDC_STATIC_BRANCH );
            LoadControl ( IDC_STATIC_SALESREP );
         }
         break;
   }
}

//****************************************************************************** 

bool AcctSplitCommDlg::doDisablePermCheckButton(UINT nID)
{
   DString dstrActive;
   getParent()->getField( this, IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, ifds::Active, dstrActive, false );

   if( nID == IDC_BTN_ADD_REP || nID == IDC_BTN_DELETE )
   {
      return(dstrActive.strip() != YES);
   }
   else if( nID == IDC_BTN_ADD_DATE )
   {
      if ( _dstrCreateAcct == YES || _dstrCreateShr == YES )
         return true;
      return( _bDisableAdd );
   }
   else if( nID == IDC_BTN_DEL_DATE )
   {
      if ( _dstrCreateAcct == YES || _dstrCreateShr == YES )
         return true;
      DString dstrNewItem;
      getParent()->getField ( this, IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, ACCTSPLIT::NEWITEM, dstrNewItem, false );
      //getParent()->getField ( this, ACCTSPLIT::ACCT_SPLITCOMM_DATE_LIST, ifds::Active, dstrNewItem, false );
      return(dstrNewItem.strip() != YES);
   }
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AcctSplitCommDlg.cpp-arc  $
// 
//    Rev 1.17   Sep 15 2005 15:10:14   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.16   Jul 10 2003 22:21:26   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.15   Mar 21 2003 18:30:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.14   Oct 17 2002 14:57:14   HSUCHIN
// sync up with release 49.  Disable Delete button during NASU
// 
//    Rev 1.13   Oct 09 2002 23:55:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Aug 08 2002 15:22:52   HSUCHIN
// fix refresh issue on delete
// 
//    Rev 1.11   22 May 2002 19:15:36   PURDYECH
// BFData Implementation
// 
//    Rev 1.10   27 Mar 2002 20:00:52   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.9   25 Nov 2001 15:37:30   HSUCHIN
// bug fix to sync up.
// 
//    Rev 1.8   25 Nov 2001 15:25:10   HSUCHIN
// syncup with 1.5.1.1
// 
//    Rev 1.7   23 Nov 2001 14:20:00   KOVACSRO
// perm check changes.
// 
//    Rev 1.6   05 Nov 2001 15:49:46   KOVACSRO
// hasPermission() changes
// 
//    Rev 1.5   01 Oct 2001 16:41:56   HSUCHIN
// renamed IDC_RSP_CONSTRIBUTION_LIST to IDC_LV_SPLIT_DATE
// 
//    Rev 1.4   24 Sep 2001 11:02:58   HSUCHIN
// fixed the way the title is displayed
// 
//    Rev 1.3   13 Sep 2001 17:54:04   HSUCHIN
// added user security permission check
// 
//    Rev 1.2   13 Sep 2001 10:24:24   HSUCHIN
// fix so that the renunciation amount is refreshed each time the percent field changes
// 
//    Rev 1.1   29 Aug 2001 16:12:50   HSUCHIN
// more dialog support added
// 
//    Rev 1.0   23 Aug 2001 14:52:08   HSUCHIN
// Initial revision.
 */


