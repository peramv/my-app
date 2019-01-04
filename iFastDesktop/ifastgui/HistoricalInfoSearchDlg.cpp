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
// ^FILE   : HistoricalInfoSearchDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ----------------------------------------------------------
//
// ^CLASS    : HistoricalInfoSearchDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include <bfproc\AbstractProcess.hpp>
#include "ifastbp\HistoricalInfoProcessIncludes.hpp"
#include <ifastbp\HistoricalInfoSearchProcessincludes.hpp>
#include "HistoricalInfoSearchDlg.hpp"
#include <uibase\DSTButton.h>
#include <uibase\DSTComboBox.h>
#include <uibase\DSTEdit.h>
#include <ifastbp\mfcaninterprocparam.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_HISTORICAL_INFO_SRCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< HistoricalInfoSearchDlg > dlgCreator( CMD_GUI_HISTORICAL_INFO_SRCH );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "HistoricalInfoSearchDlg" );
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId HistoricalSearchInfo;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const FDE;
   extern CLASS_IMPORT I_CHAR * const SLS;
   extern CLASS_IMPORT I_CHAR * const BRK;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
HistoricalInfoSearchDlg::HistoricalInfoSearchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( HistoricalInfoSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(HistoricalInfoSearchDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void HistoricalInfoSearchDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(HistoricalInfoSearchDlg)
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY HistoricalInfoSearchDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP( HistoricalInfoSearchDlg, BaseMainDlg )
//{{AFX_MSG_MAP(HistoricalInfoSearchDlg)
ON_MESSAGE(UM_OPENFUNDLISTDLG, OpenFundListDlg)
ON_MESSAGE(UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_MESSAGE(UM_OPENBRANCHLISTDLG, OpenBranchListDlg)
ON_MESSAGE(UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg)
ON_BN_CLICKED(ID_BTN_SRCH, OnBtnSrch)
ON_CBN_SELCHANGE(IDC_CMB_SEARCH_TYPE, OnSelchangeCmbSrch)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL HistoricalInfoSearchDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return(TRUE);
}

//*****************************************************************************
void HistoricalInfoSearchDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

   AddControl(CTRL_COMBO, IDC_CMB_SEARCH_TYPE, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::HistoricalSearchInfo, 
      CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_EDIT, IDC_EDT_BROKER_CODE, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::BrokerCode, CTRLFLAG_DEFAULT);
   AddControl(CTRL_STATIC, IDC_STC_BROKER_NAME, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::BrokerName, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_BRANCH_CODE, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::BranchCode, CTRLFLAG_DEFAULT);
   AddControl(CTRL_STATIC, IDC_STC_BRANCH_NAME, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::BranchName, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_SALES_REP, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::SalesRepCode, CTRLFLAG_DEFAULT);
   AddControl(CTRL_STATIC, IDC_STC_SALESREP_NAME, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::SalesRepName, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_FUND_GROUP, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::FundGroup, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_FUND_CODE, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::FundCode, CTRLFLAG_DEFAULT);
   AddControl(CTRL_STATIC, IDC_STC_FUND_NAME, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::FundName, CTRLFLAG_DEFAULT);
   AddControl(CTRL_EDIT, IDC_EDT_CLASS_CODE, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::ClassCode, CTRLFLAG_DEFAULT);
   doRefresh( this, NULL_STRING );
}

//******************************************************************************
void HistoricalInfoSearchDlg::OnSelchangeCmbSrch()
{
   TRACE_METHOD( CLASSNAME, I_("OnSelchangeCmbSrch"));
   CWaitCursor wait;
   DString tableId;

   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::HistoricalSearchInfo, tableId, false);

   if (tableId == AUDITTYPE::FDE)
   {
      EnableControl(IDC_EDT_BROKER_CODE, true);
      EnableControl(IDC_EDT_BRANCH_CODE, true);
      EnableControl(IDC_EDT_SALES_REP, true);
      EnableControl(IDC_EDT_FUND_GROUP, true);
      EnableControl(IDC_EDT_FUND_CODE, true);
      EnableControl(IDC_EDT_CLASS_CODE, true);
      GetDlgItem(ID_BTN_SRCH)->EnableWindow(true);
   } else if (tableId == AUDITTYPE::BRK)
   {
      EnableControl(IDC_EDT_BROKER_CODE, true);
      EnableControl(IDC_EDT_BRANCH_CODE, false);
      EnableControl(IDC_EDT_SALES_REP, false);
      EnableControl(IDC_EDT_FUND_GROUP, false);
      EnableControl(IDC_EDT_FUND_CODE, false);
      EnableControl(IDC_EDT_CLASS_CODE, false);
      GetDlgItem(ID_BTN_SRCH)->EnableWindow(true);
   } else if (tableId == AUDITTYPE::SLS)
   {
      EnableControl(IDC_EDT_BROKER_CODE, true);
      EnableControl(IDC_EDT_BRANCH_CODE, true);
      EnableControl(IDC_EDT_SALES_REP, true);
      EnableControl(IDC_EDT_FUND_GROUP, false);
      EnableControl(IDC_EDT_FUND_CODE, false);
      EnableControl(IDC_EDT_CLASS_CODE, false);
      GetDlgItem(ID_BTN_SRCH)->EnableWindow(true);
   } else
   {
      EnableControl(IDC_EDT_BROKER_CODE, false);
      EnableControl(IDC_EDT_BRANCH_CODE, false);
      EnableControl(IDC_EDT_SALES_REP, false);
      EnableControl(IDC_EDT_FUND_GROUP, false);
      EnableControl(IDC_EDT_FUND_CODE, false);
      EnableControl(IDC_EDT_CLASS_CODE, false);
      GetDlgItem(ID_BTN_SRCH)->EnableWindow(false);
   }
}

//******************************************************************************
void HistoricalInfoSearchDlg::OnBtnSrch()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSrch") );
   GetDlgItem(ID_BTN_SRCH)->SetFocus();
   CWaitCursor wait;
   DString tableId, keyStringIDI;
   DString brokerCode, branchCode, salesRepCode, fundGroup, fundCode, classCode;
   
   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::HistoricalSearchInfo, tableId, false);
   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::BrokerCode, brokerCode);
   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::BranchCode, branchCode);
   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::SalesRepCode, salesRepCode);
   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::FundGroup, fundGroup);
   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::FundCode, fundCode);
   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
      ifds::ClassCode, classCode);
   if (tableId == AUDITTYPE::FDE)
   {
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::SALES_REP_CODE, salesRepCode);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::FUND_GROUP, fundGroup);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::FUND_CODE, fundCode);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::CLASS_CODE, classCode);
   } 
   else if (tableId == AUDITTYPE::BRK)
   {
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
   } 
   else if (tableId == AUDITTYPE::SLS)
   {
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::SALES_REP_CODE, salesRepCode);
   }
   setParameter( I_("TYPE"), I_("SINGLE") );
   setParameter(MFCAN_IP_PARAM::KEYS, keyStringIDI);
   setParameter(MFCAN_IP_PARAM::RECID, NULL_STRING);
   setParameter(MFCAN_IP_PARAM::TABLEID, tableId);
   //call the historical process
   try
   {
      E_COMMANDRETURN eRtn;
      SetMessageStatusBar(TXT_LOAD_HISTORICAL_INFO);
      eRtn = invokeCommand( this, CMD_BPROC_HISTORICAL_INFO, PROC_NO_TYPE,
                            true /*modal*/, NULL );
      SetMessageStatusBar( NULL_STRING );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
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
}

//******************************************************************
BOOL HistoricalInfoSearchDlg::PreTranslateMessage( MSG* pMsg ) 
{
   BOOL isTranslated = FALSE;

   if( pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 )
   {
      m_pWndItemInFocus = GetFocus();
      if( m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_CODE) ||
         m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_CODE))
      {
         PostMessage(UM_OPENFUNDLISTDLG);
      } else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_BROKER_CODE))
      {
         PostMessage(UM_OPENBROKERLISTDLG);
      } else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_BRANCH_CODE))
      {
         PostMessage(UM_OPENBRANCHLISTDLG);
      }
      else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_SALES_REP))
      {
         PostMessage(UM_OPENSLSREPLISTDLG);
      }
   }
   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}


//******************************************************************
LRESULT HistoricalInfoSearchDlg::OpenBranchListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBranchListDlg" ) );
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;
   DString brokerCode, branchCode;

   try
   {
      getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
         ifds::BrokerCode, brokerCode);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      eRtn = invokeCommand( getParent(), 
         CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode);
               if(branchCode != NULL_STRING)
               {
                  getParent()->setField( this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
                     ifds::BranchCode, branchCode);
               }
               LoadControl(IDC_EDT_BRANCH_CODE);
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
   return(eRtn);
}

//******************************************************************
LRESULT HistoricalInfoSearchDlg::OpenSlsRepListDlg( WPARAM, LPARAM ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenSlsRepListDlg" ) );
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;
   DString brokerCode, branchCode;

   try
   {
      getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
         ifds::BrokerCode, brokerCode);
      getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
         ifds::BranchCode, branchCode);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode );
      setParameter(MFCAN_IP_PARAM::BRANCH_CODE, branchCode );
      eRtn = invokeCommand( getParent(), 
            CMD_BPROC_SLSREP, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString slsrepCode;

               getParameter(MFCAN_IP_PARAM::SALES_REP_CODE, slsrepCode);
               if( slsrepCode != NULL_STRING )
               {
                  getParent()->setField( this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
                     ifds::SalesRepCode, slsrepCode);
               }
               LoadControl(IDC_EDT_SALES_REP);
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
   return(eRtn);
}

//******************************************************************
LRESULT HistoricalInfoSearchDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;
   DString brokerCode;

   try
   {
      getParent()->getField(this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
         ifds::BrokerCode, brokerCode);
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, 
            PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter(MFCAN_IP_PARAM::BROKER_CODE, brokerCode);
               if(brokerCode != NULL_STRING)
               {
                  getParent()->setField( this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
                     ifds::BrokerCode, brokerCode );
               }
               LoadControl(IDC_EDT_BROKER_CODE);
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
   return(eRtn);
}

//******************************************************************
LRESULT HistoricalInfoSearchDlg::OpenFundListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundListDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      //clear all params first
      setParameter(MFCAN_IP_PARAM::CLASS_CODE, NULL_STRING);
      setParameter(MFCAN_IP_PARAM::FUND_CODE, NULL_STRING);
      if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_CODE)) 
      {
         CString cstrClassCode;

         static_cast<CEdit*>(GetDlgItem(IDC_EDT_CLASS_CODE))->GetWindowText(cstrClassCode);
         setParameter(MFCAN_IP_PARAM::CLASS_CODE, (LPCTSTR)cstrClassCode);
      } 
      else if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_CODE))
      {
         CString cstrFundCode;

         static_cast<CEdit*>(GetDlgItem(IDC_EDT_FUND_CODE))->GetWindowText(cstrFundCode);
         setParameter(MFCAN_IP_PARAM::FUND_CODE, (LPCTSTR)cstrFundCode);
      }
      //invoke the fund class dialog and process
      SetMessageStatusBar(TXT_LOAD_FUND_INFO);
      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;

               if (m_pWndItemInFocus == GetDlgItem(IDC_EDT_CLASS_CODE) ||
                   m_pWndItemInFocus == GetDlgItem(IDC_EDT_FUND_CODE))
               {
                  getParameter(MFCAN_IP_PARAM::CLASS_CODE, dstrClassCode);
                  getParent()->setField( this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
                     ifds::ClassCode, dstrClassCode);
                  getParameter(MFCAN_IP_PARAM::FUND_CODE, dstrFundCode );
                  getParent()->setField( this, IFASTBP_PROC::HISTORICAL_INFO_SEARCH_CRITERIA, 
                     ifds::FundCode, dstrFundCode);
               }
               LoadControl(IDC_EDT_CLASS_CODE);
               LoadControl(IDC_EDT_FUND_CODE);
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            SetMessageStatusBar(NULL_STRING);
            break;
      }
      SetMessageStatusBar(NULL_STRING);
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
bool HistoricalInfoSearchDlg::doRefresh( GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   ConnectControlsToData();
   LoadControls( -1L ); // Using -1 to load all controls
   return(true);
}


//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalInfoSearchDlg.cpp-arc  $
// 
//    Rev 1.9   Sep 15 2005 15:13:18   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.8   Oct 28 2004 17:13:48   HERNANDO
// PTS10035240 - Display Historical Info for Dealer/Branch/Rep.
// 
//    Rev 1.7   Jul 10 2003 22:21:42   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.6   Jun 30 2003 16:58:42   popescu
// added historical info search to the Broker Features search;
// moved some param names to the mfcaniterprocparam namespace
// 
//    Rev 1.5   Mar 21 2003 18:37:30   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Mar 10 2003 16:39:08   popescu
// Fixed PTS# 100014623
// 
//    Rev 1.3   Feb 11 2003 15:22:30   popescu
// Bug fixes
// 
//    Rev 1.2   Feb 11 2003 14:42:04   popescu
// changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
// 
//    Rev 1.1   Feb 07 2003 11:25:46   popescu
// Added a cursor wait for the search button
// 
//    Rev 1.0   Feb 06 2003 11:54:56   popescu
// Initial revision.
 * 
 */

