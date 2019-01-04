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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : FileSearchDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/15/2005
//
// ^CLASS    : FileSearchDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef FILESEARCHDLG_H
   #include "FileSearchDlg.h"
#endif
#include <ifastbp\FileSearchProcessInclude.h>
#include <ifastbp\FileInquiryProcessInclude.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include "discardmsgdlg.h"
#include <bfproc\genericinterfacecontainer.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FILE_SEARCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FileSearchDlg > dlgCreator( CMD_GUI_FILE_SEARCH);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FILE_SEARCH;

namespace
{
	const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const CLASSNAME         = I_( "FileSearchDlg" );
	const I_CHAR * const LV_FILE_SEARCH    = I_( "File Search" );
  
   const I_CHAR *pINQUIRYONLY       = I_( "InquiryOnly" );
}

namespace CND
{//Conditionsused
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************

FileSearchDlg::FileSearchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FileSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	
   //{{AFX_DATA_INIT(FileSearchDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
FileSearchDlg::~FileSearchDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void FileSearchDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(FileSearchDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FileSearchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FileSearchDlg)

	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FileSearchDlg message handlers


//******************************************************************************
void FileSearchDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
  	addControls();
}

//******************************************************************************
SEVERITY FileSearchDlg::doInit()
{
   SEVERITY sevRtn = NO_CONDITION;

   return(sevRtn);
}

//******************************************************************************

BOOL FileSearchDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
//******************************************************************************
void FileSearchDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );    
	
	//controls
   
   AddControl( CTRL_COMBO, IDC_CMB_NETWORK_ORDER, IFASTBP_PROC::CRITERIA, ifds::NetworkID, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
  
	AddControl( CTRL_EDIT, IDC_EDT_FILE_NAME, IFASTBP_PROC::CRITERIA, ifds::FileName , 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );

	AddControl( CTRL_DATE, IDC_DATE_START, IFASTBP_PROC::CRITERIA, ifds::StartDate, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );

	AddControl( CTRL_DATE, IDC_DATE_END,  IFASTBP_PROC::CRITERIA, ifds::EndDate, 
		CTRLFLAG_AUTO_UPDATE_ON_CHANGE );

   ConnectControlsToData ();
   LoadControls();
}

//******************************************************************************

bool FileSearchDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

	ConnectControlsToData ();
   LoadControls();
   return(true);
}



//******************************************************************************

void FileSearchDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );

	GetDlgItem(IDC_BTN_SEARCH)->SetFocus();
	CWaitCursor wait;
   SetMessageStatusBar( IDS_LOADING_FILE_INQUIRY );

   SEVERITY sev = NO_SEVERITY;
   sev = getParent()->performSearch(this, IFASTBP_PROC::CRITERIA, SEARCH_START );
   
	if (sev>WARNING)
	{
		SetMessageStatusBar( NULL_STRING );
		ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
		return;
	}
	setUpdateFlag(false);// we don't want to see the disgard dialog is this screen

}

//******************************************************************************
bool FileSearchDlg::doSend ( GenericInterface *rpGICaller, const I_CHAR *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("doSend"));
   bool bRet = true;
	setUpdateFlag (false);
   DString Message( szMessage );
   if( Message == I_("CLOSE") )
   {
      BFWorkSession *bfWorkSession = getBFWorkSession();
      if( bfWorkSession)
      {
         bfWorkSession->cleanupWorkSession();  
      }
      // Close
      getGIContainer()->destroySelf( this );
      return( true );
   }
   return( false );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FileSearchDlg.cpp-arc  $
// 
//    Rev 1.3   Sep 15 2005 15:12:14   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.2   Mar 17 2005 12:02:22   ZHANGCEL
// Magic #267177 -- Bug fix for the NetworkID comb box empty problem
// 
//    Rev 1.1   Feb 28 2005 16:58:12   ZHANGCEL
// PET1117 - FN 66-68  -- Code clean up and deal with the close button issue
// 
//    Rev 1.0   Feb 24 2005 17:48:20   ZHANGCEL
// Initial revision.
//
*/