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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RESPInfoDlg.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/05/2000
//
// ^CLASS    : RESPInfoDlg
// ^SUBCLASS : BaseMainDlg         
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
// RESPInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"

#ifndef RESPINFODLG_H
   #include "RESPInfoDlg.h"
#endif

#ifndef RESPINFOPROCESSINCLUDES_H
   #include <ifastbp\RESPInfoProcessIncludes.h>
#endif

//#ifndef DSTLISTCTRL_H
//   #include <uibase\dstlistctrl.h>
//#endif

#ifndef CONDITIONMESSAGEDIALOG_H
   #include <uibase\ConditionMessageDialog.h>
#endif

//HllApi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESPTRANSACTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_RESPINFO;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RESPInfoDlg > dlgCreator( CMD_GUI_RESPINFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RESPInfoDlg dialog

namespace
{
   // trace literals
   const I_CHAR *CLASSNAME = I_( "RESPInfoDlg" );
   const I_CHAR *LV_RESPINFO = I_( "RESPInfoBeneficiaryList" ); 

   // column keys for the Account Beneficiary Total table
   const I_CHAR *FIRST_COL = I_("BeneName");
   const I_CHAR *COL_LIFE_TIME = I_("LifeContr");
   const I_CHAR *COL_UNASSISTED = I_("UnAssisted");
   const I_CHAR *COL_ASSISTED = I_("Assisted");
   const I_CHAR *COL_NET_GRANT = I_("NetGrant");
   const I_CHAR *COL_EAP = I_("EAPayment");

   //  const I_CHAR *ROW_REDUCTION_TOTALS = I_("Reduction Totals:");
   //  const I_CHAR *ROW_ACCOUNT_TOTALS = I_("Account Totals:");

   const I_CHAR * const MODUSER               = I_( "ModUser" );
   const I_CHAR * const MODDATE               = I_( "ModDate" );
   const I_CHAR * const PROCESSUSER           = I_( "Username" );
   const I_CHAR * const PROCESSDATE           = I_( "ProcessDate" );

   const I_CHAR *SPACE_STRING = I_( " " ); 
   const I_CHAR *MFDSTC = I_( "MFDSTC" );   
   const I_CHAR *CANADA = I_("Canada");
   const I_CHAR *JAPAN = I_("Japan");
   const I_CHAR *MARKET = I_( "Market" );

//   const I_CHAR * const HISTORY_PENDING_FIELD = I_( "HistoryPending" );
//   const I_CHAR * const HISTORY = I_( "H" );
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

using namespace RESPINFONAMES;


//******************************************************************************
RESPInfoDlg::RESPInfoDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RESPInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(RESPInfoDlg)
   //}}AFX_DATA_INIT
}


//******************************************************************************
void RESPInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RESPInfoDlg)
   DDX_Control(pDX, IDC_LV_RESPINFO_TOTAL, m_RESPTotalList);
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(RESPInfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RESPInfoDlg)
ON_BN_CLICKED(IDC_BTN_CHANGE, OnBtnChange)
ON_BN_CLICKED(IDC_BTN_RESPTRANS, OnBtnResptrans)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RESPInfoDlg message handlers

//******************************************************************************
SEVERITY RESPInfoDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   SEVERITY sevRtn = SEVERE_ERROR;
   getParameter( ACCOUNT_NUMBER_FIELD, _strAccountNumber );
   getParameter( SHAREHOLDER_FIELD, _strShareholderNum );
   getParameter( LAST_NAME_FIELD, _strLastName );
   getParameter( FIRST_NAME_FIELD, _strFirstName );
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
BOOL RESPInfoDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));

   int col=0;
   CString colTitle;

   DisplayTitle();
   FillTotalList();

   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void RESPInfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 

   AddListControl( CLASSNAME, IDC_LV_RESPINFO_BENEFICIARY, LV_RESPINFO, ifds::RESPInfoHeadingSet,      IFASTBP_PROC::RESPINFOBENEFICIARY_LIST );
   AddControl( CTRL_DATE,  IDC_CMB_PLANTERMINATEDATE, IFASTBP_PROC::RESPINFO_LIST, ifds::MaturityDate,  CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_COMBO, IDC_CMB_CESGELIGIBLE,      IFASTBP_PROC::RESPINFO_LIST, ifds::CESGEligible,  CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_COMBO, IDC_CMB_GFATHERED,         IFASTBP_PROC::RESPINFO_LIST, ifds::GFathered,     CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_COMBO, IDC_CMB_RESPSTATUS,        IFASTBP_PROC::RESPINFO_LIST, ifds::RESPStatus,    CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_EDIT,  IDC_EDT_CONTRTERMINATEDATE,IFASTBP_PROC::RESPINFO_LIST, ifds::TerminateDate, CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_EDIT,  IDC_EDT_TODATECONTR,       IFASTBP_PROC::RESPINFO_LIST, ifds::ToDateContr,   CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_EDIT,  IDC_EDT_GRANTREPAYABLE,    IFASTBP_PROC::RESPINFO_LIST, ifds::GrantRepayable,CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_EDIT,  IDC_EDT_TDREDEARNING,      IFASTBP_PROC::RESPINFO_LIST, ifds::TDRedEarning,  CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_EDIT,  IDC_EDT_CURREARNING,       IFASTBP_PROC::RESPINFO_LIST, ifds::CurrEarning,   CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   AddControl( CTRL_EDIT,  IDC_EDT_PLANNUM,           IFASTBP_PROC::RESPINFO_LIST, ifds::PlanNum,       CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_RESPINFO_BENEFICIARY );
   doRefresh( this, NULL_STRING );
}

//******************************************************************************
bool RESPInfoDlg::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{  
   //ConnectControlsToData();
   LoadListControl( IDC_LV_RESPINFO_BENEFICIARY );
   //LoadControls();

   return(true);
}

//******************************************************************************
void RESPInfoDlg::OnBtnChange() 
{
   setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(_strAccountNumber) );
   executeCsiProcess( DcCsiProcesses::RESP_INFORMATION );    
}

//******************************************************************************
void RESPInfoDlg::OnBtnResptrans() 
{
   setParameter( ACCOUNT_NUMBER_FIELD, _strAccountNumber );
   setParameter( HISTORY_PENDING_FIELD, HISTORY );
   SetMessageStatusBar( TXT_LOAD_RESPTRANSACTIONS );
   invokeCommand( getParent(), CMD_BPROC_RESPTRANSACTIONS, PROC_NO_TYPE, false, NULL ); //call modeless
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void RESPInfoDlg::DisplayTitle()
{
   TRACE_METHOD( CLASSNAME, I_("DisplayTitle"));

   DString str;
   CString text;

   text.LoadString( TXT_RESPINFO_TITLE );
   str = ( LPCTSTR )text + _strShareholderNum;

   text.LoadString( TXT_RESP_ACCOUNT );
   str = str + ( LPCTSTR )text + _strAccountNumber + I_("; ") + _strLastName + I_("; ") + _strFirstName; 

   SetWindowText( str.c_str() );
}

//******************************************************************************
void RESPInfoDlg::FillTotalList()
{
   DString str;
   CString strColumnName;
   int column = 0;

   strColumnName.LoadString( COL_RESP_LIFE );
   m_RESPTotalList.InsertColumn( column, ( LPCTSTR )strColumnName, LVCFMT_RIGHT, 130 );

   column++;
   strColumnName.LoadString( COL_RESP_UNASSISTED );
   m_RESPTotalList.InsertColumn( column, ( LPCTSTR )strColumnName, LVCFMT_RIGHT, 140 );

   column++;
   strColumnName.LoadString( COL_RESP_ASSISTED );
   m_RESPTotalList.InsertColumn( column, ( LPCTSTR )strColumnName, LVCFMT_RIGHT, 130  );

   column++;
   strColumnName.LoadString( COL_RESP_NET_GRANT );
   m_RESPTotalList.InsertColumn( column, ( LPCTSTR )strColumnName, LVCFMT_RIGHT, 90  );

   column++;
   strColumnName.LoadString( COL_RESP_EAP );
   m_RESPTotalList.InsertColumn( column, ( LPCTSTR )strColumnName, LVCFMT_RIGHT, 90  );

   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::RedLifeContr, str );
   m_RESPTotalList.InsertItem( 0, str.stripAll().c_str() );
   m_RESPTotalList.doSetItemText( 0, 0, str.stripAll().c_str(), ifds::RedLifeContr );
   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::RedUCAmt, str );
   m_RESPTotalList.doSetItemText( 0, 1, str.stripAll().c_str(), ifds::RedUCAmt );
   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::RedACAmt, str );
   m_RESPTotalList.doSetItemText( 0, 2, str.stripAll().c_str(), ifds::RedACAmt );
   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::RedNetGrant, str );
   m_RESPTotalList.doSetItemText( 0, 3, str.stripAll().c_str(), ifds::RedNetGrant );

   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::AcctLifeContr, str );
   m_RESPTotalList.InsertItem( 1, str.stripAll().c_str() );
   m_RESPTotalList.doSetItemText( 1, 0, str.stripAll().c_str(), ifds::AcctLifeContr );
   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::AcctUCAmt, str );
   m_RESPTotalList.doSetItemText( 1, 1, str.stripAll().c_str(), ifds::AcctUCAmt );
   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::AcctACAmt, str );
   m_RESPTotalList.doSetItemText( 1, 2, str.stripAll().c_str(), ifds::AcctACAmt );
   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::AcctNetGrant, str );
   m_RESPTotalList.doSetItemText( 1, 3, str.stripAll().c_str(), ifds::AcctNetGrant );
   getParent()->getField( this, IFASTBP_PROC::RESPINFO_LIST, ifds::AcctEAP, str );
   m_RESPTotalList.doSetItemText( 1, 4, str.stripAll().c_str(), ifds::AcctEAP );

}

/* $Log:   Y:/VCS/BF iFAST/ifastgui/RESPInfoDlg.cpp-arc  $
 * 
 *    Rev 1.11   Sep 15 2005 15:14:58   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.10   Jun 24 2005 17:00:38   Fengyong
 * PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.9   Mar 21 2003 18:40:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:56:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   22 May 2002 19:16:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   27 Mar 2002 20:01:20   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.5   Jan 28 2002 11:28:12   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.4   28 May 2001 14:36:58   KOVACSRO
 * Made controls read-only. Fixed crash. Uncommented HILLAPI.
 * 
 *    Rev 1.3   Mar 24 2000 12:19:12   PETOLESC
 * Modified fields width for RESPTotal table.
 * 
 *    Rev 1.2   Mar 23 2000 14:03:48   PETOLESC
 * Added RESPTotal table.
 * 
 *    Rev 1.1   Mar 22 2000 09:02:48   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.5   Mar 08 2000 10:50:32   PETOLESC
// Modified the title bar as requested by qa.
// 
//    Rev 1.4   Mar 06 2000 10:55:16   PETOLESC
// Added the hllapi call.
// 
//    Rev 1.3   Mar 02 2000 11:59:26   PETOLESC
// Enabled the Change button code.
// 
//    Rev 1.2   Feb 16 2000 10:22:44   PETOLESC
// Added the list to MFAccount.
// 
//    Rev 1.1   Feb 07 2000 11:01:18   PETOLESC
// Added link to RESPTransactionsHistory dialog.
// 
//    Rev 1.0   Jan 17 2000 14:50:10   PETOLESC
// Initial revision.
 * 
 *
 */
