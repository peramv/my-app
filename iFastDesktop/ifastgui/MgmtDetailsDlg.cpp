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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MgmtDetailsDlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ----------------------------------------------------------
//
// ^CLASS    : MgmtDetailsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif
#ifndef MGMTDETAILSDLG_H
   #include "MgmtDetailsDlg.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif
#ifndef CONFIGURATIONCONSTANTS_H
   #include "ConfigurationConstants.h"
#endif
#ifndef MGMTDETAILSPROCESSINCLUDES_H
   #include <ifastbp\MgmtDetailsProcessIncludes.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MGMTDETAILS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MgmtDetailsDlg > dlgCreator( CMD_GUI_MGMTDETAILS );

namespace
{
   const I_CHAR *BI_COMPLETE    = I_( "OnDownloadCompleteBushtml" );
   const I_CHAR *BI_DOWNLOAD    = I_( "OnDownloadBeginBushtml" );
   const I_CHAR *BI_ONWEBBACK   = I_( "OnWebback" );
   const I_CHAR *BI_ONWEBFWD    = I_( "OnWebfwd" );
   const I_CHAR *BI_ONWEBHOME   = I_( "OnWebhome" );
   const I_CHAR *BI_ONWEBSTOP   = I_( "OnWebstop" );
   const I_CHAR *BI_SETHOMEFOCUS = I_( "SetHomeFocus" );
   const I_CHAR *BI_STATECHANGE = I_( "OnCommandStateChangebushtml" );
   const I_CHAR *CLASSNAME      = I_( "MgmtDetailsDlg" );
}

namespace DD
{
   const I_CHAR *fund_1     = I_( "\\config\\fyi.htm" ); 
   const I_CHAR *FNamePrefix  = I_( "\\config\\fnd" ); 
   const I_CHAR *FNamePostfix = I_( ".htm" ); 
   const I_CHAR *search_anim = I_( "\\search.avi" );
   extern const I_CHAR *file_;
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

MgmtDetailsDlg::MgmtDetailsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MgmtDetailsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(MgmtDetailsDlg)
   m_txtFundCode = _T("");
   //}}AFX_DATA_INIT
   //m_rbFixed = 1;
}

//*****************************************************************************
void MgmtDetailsDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MgmtDetailsDlg)
   DDX_Control(pDX, IDC_WEBSTOP, m_btnWebStop);
   DDX_Control(pDX, IDC_WEBHOME, m_btnWebHome);
   DDX_Control(pDX, IDC_WEBFWD, m_btnWebFwd);
   DDX_Control(pDX, IDC_WEBBACK, m_btnWebBack);
   DDX_Text(pDX, IDC_TXT_FUND, m_txtFundCode);
   DDX_Control(pDX, IDC_MGMT_DETAILS_HTML, m_wbrowMgmtDetail);
   DDX_Control(pDX, IDC_ANIMATION1, m_Animate);
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY MgmtDetailsDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(MgmtDetailsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MgmtDetailsDlg)
ON_BN_CLICKED(IDC_WEBHOME, OnWebhome)
ON_BN_CLICKED(IDC_WEBSTOP, OnWebstop)
ON_BN_CLICKED(IDC_WEBBACK, OnWebback)
ON_BN_CLICKED(IDC_WEBFWD, OnWebfwd)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL MgmtDetailsDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   m_csFileDir = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, 
                                         CONFIGURATION_CONSTANTS::DataPath,
                                         CONFIGURATION_CONSTANTS::Path ).c_str();
   m_csFileDir.TrimRight();


   return(TRUE);   // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************************************************
void MgmtDetailsDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   fillInitialValues();
   UpdateData(FALSE);
}

//******************************************************************************
bool MgmtDetailsDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand )
{
   fillInitialValues();
   UpdateData(FALSE);
   return(true);
}

//******************************************************************************
void MgmtDetailsDlg::fillInitialValues() 
{
   GenericInterface * Parent = getParent();
   DString lFundCode;
   Parent->getField( this,  ifds::FundCode, lFundCode );
   m_txtFundCode = lFundCode.strip().upperCase().c_str();

   CFileFind finder;
   m_FileName = m_csFileDir + DD::FNamePrefix  + m_txtFundCode + DD::FNamePostfix;
   if( BOOL bWorking = finder.FindFile( m_FileName ) )
   {
      m_FileName = CString( DD::file_) +  m_FileName;
   }
   else
   {
      m_FileName = CString( DD::file_) + m_csFileDir + DD::fund_1;
   }

   // Display HTML doc associated with selected item
   m_wbrowMgmtDetail.Navigate( m_FileName, NULL, NULL, NULL, NULL );

}

//******************************************************************************
void MgmtDetailsDlg::OnWebhome() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBHOME );
   m_wbrowMgmtDetail.Navigate(m_FileName, NULL, NULL, NULL, NULL); // Display HTML doc associated with selected item
}

//******************************************************************************
void MgmtDetailsDlg::OnWebstop() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBSTOP );
   m_wbrowMgmtDetail.Stop();
}

//******************************************************************************
void MgmtDetailsDlg::OnWebback() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBBACK );
   m_wbrowMgmtDetail.GoBack();
}

//******************************************************************************
void MgmtDetailsDlg::OnWebfwd() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBFWD );
   m_wbrowMgmtDetail.GoForward();
}

//******************************************************************************
BEGIN_EVENTSINK_MAP(MgmtDetailsDlg, BaseMainDlg)
//{{AFX_EVENTSINK_MAP(MgmtDetailsDlg)
ON_EVENT(MgmtDetailsDlg, IDC_MGMT_DETAILS_HTML, 105 /* CommandStateChange */, OnCommandStateChangeMgmtDetailsHtml, VTS_I4 VTS_BOOL)
ON_EVENT(MgmtDetailsDlg, IDC_MGMT_DETAILS_HTML, 106 /* DownloadBegin */, OnDownloadBeginMgmtDetailsHtml, VTS_NONE)
ON_EVENT(MgmtDetailsDlg, IDC_MGMT_DETAILS_HTML, 104 /* DownloadComplete */, OnDownloadCompleteMgmtDetailsHtml, VTS_NONE)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//******************************************************************************
void MgmtDetailsDlg::OnCommandStateChangeMgmtDetailsHtml(long Command, BOOL Enable) 
{
   TRACE_METHOD( CLASSNAME, BI_STATECHANGE );
   switch( Command )
   {
      case CSC_NAVIGATEFORWARD:
         m_btnWebFwd.EnableWindow( Enable );  
         break;
      case CSC_NAVIGATEBACK:
         m_btnWebBack.EnableWindow( Enable );
         break;
   }
}

//******************************************************************************
void MgmtDetailsDlg::OnDownloadBeginMgmtDetailsHtml() 
{
   TRACE_METHOD( CLASSNAME, BI_DOWNLOAD );
   CString     szFileName( DD::search_anim );

   szFileName = m_csFileDir + szFileName;
   m_Animate.Open(szFileName);
   m_btnWebStop.EnableWindow( TRUE );
// Need to move to message file
   SetMessageStatusBar( TXT_LOAD_HTML );
}

//******************************************************************************
void MgmtDetailsDlg::OnDownloadCompleteMgmtDetailsHtml() 
{
   TRACE_METHOD( CLASSNAME, BI_COMPLETE );
   m_btnWebStop.EnableWindow( FALSE );
   SetMessageStatusBar( NULL_STRING );
   m_Animate.Open(NULL);   // Same as close
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MgmtDetailsDlg.cpp-arc  $
 * 
 *    Rev 1.7   Sep 15 2005 15:13:58   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.6   Jun 08 2005 18:23:44   popescu
 * Incident# 310950 - upgraded the animation control to Microsoft Animation Control v 6.0 - SP4
 * 
 *    Rev 1.5   Nov 15 2004 18:28:00   popescu
 * PTS 10035790, fixed html page with broken links for mgmt com details button
 * 
 *    Rev 1.4   Mar 21 2003 18:39:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:55:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   22 May 2002 19:16:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.1   27 Mar 2002 20:01:18   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.0   Feb 15 2000 11:01:20   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Feb 02 2000 14:53:22   DT24433
 * removed ok/cancel
 * 
 *    Rev 1.5   Jul 20 1999 16:58:50   BUZILA
 * Added animation control to Mgmt details
 * 
 *    Rev 1.4   Jul 20 1999 11:19:14   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 15 1999 16:39:30   BUZILA
 * Fixing Mgmt Detail
 * 
 *    Rev 1.2   Jul 12 1999 17:31:02   PRAGERYA
 * 
 *    Rev 1.1   Jul 08 1999 10:05:38   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

