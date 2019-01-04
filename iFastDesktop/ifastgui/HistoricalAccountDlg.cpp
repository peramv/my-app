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
// ^FILE   : HistoricalAccountDlg.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : 10/28/99
//
// ----------------------------------------------------------
//
// ^CLASS    : HistoricalAccountDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Historical Account dialog
//
//******************************************************************************

#include "stdafx.h"
#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif
#ifndef HISTORICALACCOUNTDLG_H
   #include "HistoricalAccountDlg.h"
#endif

#ifndef HISTORICALACCOUNTPROCESSINCLUDES_H
   #include <ifastbp\HistoricalAccountProcessIncludes.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_HISTORICAL_ACCOUNT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< HistoricalAccountDlg > dlgCreator( CMD_GUI_HISTORICAL_ACCOUNT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "HistoricalAccountDlg" );
   const I_CHAR * const LV_HISTORICAL_ACCOUNT = I_( "HistoricalAccount" );
   const I_CHAR* const ACCNUM = I_( "AccountNum" );
   const I_CHAR* const SHRNUM = I_( "ShareholderNum");
   const I_CHAR* const ACCTTYPE = I_( "AcctType" );
   const I_CHAR* const TAXTYPE = I_( "TaxType" );
   const I_CHAR* const RECIPIENTTYPE = I_( "RecipientType" );
   const I_CHAR* const CURRENCYCODE = I_( "Currency" );
   const I_CHAR* const INTERCODE = I_( "InterCode" );
   const I_CHAR* const ACCTSTATUS = I_( "AcctStatus" );
   const I_CHAR* const PENSIONJURIS = I_( "PensionJuris" );
   const I_CHAR* const NAME = I_( "Name" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId RecipientType;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId AcctStatus;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
}

//******************************************************************************
// Public methods
//******************************************************************************
HistoricalAccountDlg::HistoricalAccountDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( HistoricalAccountDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(HistoricalAccountDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
HistoricalAccountDlg::~HistoricalAccountDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
void HistoricalAccountDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(HistoricalAccountDlg)
   DDX_Control(pDX, IDMORE, m_btnMore);
   DDX_Control(pDX, IDC_LV_HISTORICAL_ACCOUNT, m_lvHistoricalAccount);
   //}}AFX_DATA_MAP
}

//*******************************************************************************
// Message handlers
//*******************************************************************************
BEGIN_MESSAGE_MAP(HistoricalAccountDlg, BaseMainDlg)
//{{AFX_MSG_MAP(HistoricalAccountDlg)
ON_BN_CLICKED(IDMORE, OnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
bool HistoricalAccountDlg::doRefresh( GenericInterface * rpGICaller,
                                      const I_CHAR * szOriginalCommand )
{
   if( DString (szOriginalCommand) == I_( "FullRefresh" ) )
   {
      m_lvHistoricalAccount.DeleteAllItems();
      getParameter( ACCNUM, AccountNum );
      AccountNum.stripAll();
      DString s_Caption;
      getParameter ( NAME, s_Caption );
      s_Name = I_(": ") + AccountNum + I_(" ") + s_Caption;
      OnPostInitDialog();
   }
   return(true);
}

//*****************************************************************************
BOOL HistoricalAccountDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************
void HistoricalAccountDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   SetCaption(s_Name);
   m_lvHistoricalAccount.Init(this,ifds::HistoricalAccountHeadingSet,IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST,CLASSNAME,LV_HISTORICAL_ACCOUNT);
   m_lvHistoricalAccount.PopulateList();
   m_btnMore.EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   ShowWindow( SW_SHOW );
}

//*****************************************************************************
SEVERITY HistoricalAccountDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;
   getParameter( ACCNUM, AccountNum );
   AccountNum.stripAll();
   DString s_Caption;
   getParameter ( NAME, s_Caption );
   s_Name = I_(": ") + AccountNum + I_(" ") + s_Caption;
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//*****************************************************************************
void HistoricalAccountDlg::OnMore() 
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore") );
   SetMessageStatusBar( TXT_LOAD_HISTORICAL_ACCOUNT );
   getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK );
   m_lvHistoricalAccount.PopulateList();
   m_btnMore.EnableWindow(getParent()->doMoreRecordsExist( this, BF::AllContainerIds ));
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalAccountDlg.cpp-arc  $
 * 
 *    Rev 1.6   Sep 15 2005 15:13:16   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.5   Mar 21 2003 18:37:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:55:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 19:16:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   27 Mar 2002 20:01:12   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.1   Mar 15 2000 15:27:22   DT24433
 * moved getting field display logic to historicalaccountprocess
 * 
 */
