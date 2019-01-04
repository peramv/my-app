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
// ^FILE   : HistoricalSystematicIndexDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : HistoricalSystematicIndexDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Historical Systematic Index Dlg
//
//******************************************************************************

#include "stdafx.h"
#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef HistoricalSystematicIndexDlg_H
   #include "HistoricalSystematicIndexDlg.h"
#endif

#ifndef HISTORICALSYSTEMATICINDEXPROCESSINCLUDES_H
   #include <ifastbp\HistoricalSystematicIndexProcessIncludes.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_HISTORICAL_SYS_INDEX;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< HistoricalSystematicIndexDlg > dlgCreator( CMD_GUI_HISTORICAL_SYS_INDEX );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR* const CLASSNAME                = I_( "HistoricalSystematicIndexDlg" );
   const I_CHAR* const LV_HISTORICAL_SYSTEMATIC_INDEX = I_( "HistoricalSystematicIndex" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveShrNum;
}

//******************************************************************************
// Public methods
//******************************************************************************
HistoricalSystematicIndexDlg::HistoricalSystematicIndexDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( HistoricalSystematicIndexDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(HistoricalSystematicIndexDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

HistoricalSystematicIndexDlg::~HistoricalSystematicIndexDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************

void HistoricalSystematicIndexDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(HistoricalSystematicIndexDlg)
   DDX_Control(pDX, IDMORE, m_btnMore);
   DDX_Control(pDX, IDC_LV_HISTORICAL_ACCOUNT, m_lvHistoricalSystematicIndex);
   //}}AFX_DATA_MAP
}

//*******************************************************************************
// Message handlers
//*******************************************************************************
BEGIN_MESSAGE_MAP(HistoricalSystematicIndexDlg, BaseMainDlg)
//{{AFX_MSG_MAP(HistoricalSystematicIndexDlg)
ON_BN_CLICKED(IDMORE, OnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************

bool HistoricalSystematicIndexDlg::doRefresh( GenericInterface * rpGICaller,
                                              const I_CHAR * szOriginalCommand )
{
   if( DString (szOriginalCommand) == I_( "FullRefresh" ) )
   {
      m_lvHistoricalSystematicIndex.DeleteAllItems();
      OnPostInitDialog();
   }
   return(true);
}

//***************************************************************************** 

BOOL HistoricalSystematicIndexDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************

void HistoricalSystematicIndexDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   CString cstrBaseCaption;
   cstrBaseCaption.LoadString( TXT_INDEX_HISTORY );
   SetBaseCaption( cstrBaseCaption );

   DString dstrAccountNum( NULL_STRING ), 
   dstrShrNum( NULL_STRING), 
   dstrEntityName( NULL_STRING );
   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
   if( !dstrAccountNum.empty() )
   {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);
   }
   SetShrAcctCaption( dstrShrNum, dstrAccountNum, dstrEntityName);

   m_lvHistoricalSystematicIndex.Init(  this, 
                                        ifds::HistoricalSysIndexHeadingSet,
                                        IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST, 
                                        CLASSNAME, 
                                        LV_HISTORICAL_SYSTEMATIC_INDEX );
   m_lvHistoricalSystematicIndex.PopulateList();
   m_btnMore.EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   ShowWindow( SW_SHOW );
}

//*****************************************************************************

SEVERITY HistoricalSystematicIndexDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT);
   return(NO_CONDITION);
}

//*****************************************************************************

void HistoricalSystematicIndexDlg::OnMore() 
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore") );
   SetMessageStatusBar( TXT_LOAD_HIST_SYS_INDEX );
   getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK );
   m_lvHistoricalSystematicIndex.PopulateList();
   m_btnMore.EnableWindow(getParent()->doMoreRecordsExist( this, BF::AllContainerIds ));
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalSystematicIndexDlg.cpp-arc  $
// 
//    Rev 1.9   Sep 15 2005 15:13:22   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.8   Apr 17 2003 16:46:32   linmay
// Ticket PTS 10016118 sync up version 1.6.1.0
// 
//    Rev 1.7   Mar 21 2003 18:37:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Oct 09 2002 23:55:44   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   22 May 2002 19:16:10   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   Jun 01 2001 15:19:06   HERNANDO
// Removed parameters.
// 
//    Rev 1.3   Jun 01 2001 13:44:20   HERNANDO
// Added caption.
// 
//    Rev 1.2   May 30 2001 16:31:02   HERNANDO
// Bug fix - changed define (HISTORICALSYSTEMATICINDEXPROCESSINCLUDES_H)
// 
//    Rev 1.1   May 11 2001 13:00:18   HERNANDO
// _
// 
//    Rev 1.0   May 10 2001 14:11:06   HERNANDO
// Initial revision.
 * 
 * 
 */
