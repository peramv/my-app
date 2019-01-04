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
// ^FILE   : BusInfoDlg.cpp
// ^AUTHOR : Paul Lyons
// ^DATE   : 5-97
//
// ----------------------------------------------------------
//
// ^CLASS    : BusInfoDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the FYI dialog which contains a 
//           webbrowser control that displays HTML documents.  It requires 
//           Internet Explorer 3.02 to work properly.
//******************************************************************************

#include "stdafx.h"
#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef BUSINFODLG_H
   #include "BusInfoDlg.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif

#ifndef CONFIGURATIONCONSTANTS_H
   #include "ConfigurationConstants.h"
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_BUSINFO;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< BusInfoDlg > dlgCreator( CMD_GUI_BUSINFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace DD
{
   const I_CHAR *config_FYI = I_( "\\config\\FYI.htm" ); 
   const I_CHAR *file_ = I_( "file:///" );
   const I_CHAR *search_avi = I_( "\\search.avi" );
}

namespace
{
   const I_CHAR *BI_COMPLETE = I_( "OnDownloadCompleteBushtml" );
   const I_CHAR *BI_DOWNLOAD = I_( "OnDownloadBeginBushtml" );
   const I_CHAR *BI_ONWEBBACK = I_( "OnWebback" );
   const I_CHAR *BI_ONWEBFWD = I_( "OnWebfwd" );
   const I_CHAR *BI_ONWEBHOME = I_( "OnWebhome" );
   const I_CHAR *BI_ONWEBSTOP = I_( "OnWebstop" );
   const I_CHAR *BI_SETHOMEFOCUS = I_( "SetHomeFocus" );
   const I_CHAR *BI_STATECHANGE = I_( "OnCommandStateChangebushtml" );
   const I_CHAR *CLASSNAME = I_( "BusInfoDlg" );
}

//******************************************************************************
// Public methods
//******************************************************************************

BusInfoDlg::BusInfoDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( BusInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   //{{AFX_DATA_INIT(BusInfoDlg)
   //}}AFX_DATA_INIT

   m_csFileDir = "";
}

//******************************************************************************

BusInfoDlg::~BusInfoDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

void BusInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(BusInfoDlg)
   DDX_Control(pDX, IDC_WEBSTOP, m_BtnStop);
   DDX_Control(pDX, IDC_WEBHOME, m_BtnHome);
   DDX_Control(pDX, IDC_WEBFWD, m_BtnForward);
   DDX_Control(pDX, IDC_WEBBACK, m_BtnBack);
   DDX_Control(pDX, IDC_BUSHTML, m_BusHTML);
   DDX_Control(pDX, IDC_ANIMATION1, m_Animate);
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(BusInfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(BusInfoDlg)
ON_BN_CLICKED(IDC_WEBBACK, OnWebback)
ON_BN_CLICKED(IDC_WEBFWD, OnWebfwd)
ON_BN_CLICKED(IDC_WEBHOME, OnWebhome)
ON_BN_CLICKED(IDC_WEBSTOP, OnWebstop)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************

BOOL BusInfoDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   // Get registry datapath directory to look for files
   m_csFileDir = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, 
                                         CONFIGURATION_CONSTANTS::DataPath,
                                         CONFIGURATION_CONSTANTS::Path ).c_str();
   m_csFileDir.TrimRight();

   CString strHomeName;
   GetHomeNameFromRegistry(strHomeName);

   // Display HTML doc associated with selected item
   m_BusHTML.Navigate( strHomeName, NULL, NULL, NULL, NULL );

   MoveDialog( GUIPOS_BOTTOM, 0 );             // Place me under my parent window

   return(TRUE);    // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void BusInfoDlg::OnWebback() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBBACK );
   m_BusHTML.GoBack();
}

//******************************************************************************

void BusInfoDlg::OnWebfwd() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBFWD );
   m_BusHTML.GoForward();
}

//******************************************************************************

void BusInfoDlg::OnWebhome() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBHOME );

   //CString szFileName( DD::config_FYI );
   //szFileName = CString( DD::file_ ) + m_csFileDir + szFileName;

   CString strHomeName;
   GetHomeNameFromRegistry(strHomeName);

   m_BusHTML.Navigate(strHomeName, NULL, NULL, NULL, NULL); // Display HTML doc associated with selected item
}

//******************************************************************************

void BusInfoDlg::OnWebstop() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBSTOP );
   m_BusHTML.Stop();
}

//******************************************************************************

BEGIN_EVENTSINK_MAP(BusInfoDlg, BaseMainDlg)
//{{AFX_EVENTSINK_MAP(BusInfoDlg)
ON_EVENT(BusInfoDlg, IDC_BUSHTML, 105 /* CommandStateChange */, OnCommandStateChangeBushtml, VTS_I4 VTS_BOOL)
ON_EVENT(BusInfoDlg, IDC_BUSHTML, 106 /* DownloadBegin */, OnDownloadBeginBushtml, VTS_NONE)
ON_EVENT(BusInfoDlg, IDC_BUSHTML, 104 /* DownloadComplete */, OnDownloadCompleteBushtml, VTS_NONE)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void BusInfoDlg::OnCommandStateChangeBushtml(long Command, BOOL Enable) 
{
   TRACE_METHOD( CLASSNAME, BI_STATECHANGE );
   switch( Command )
   {
      case CSC_NAVIGATEFORWARD:
         m_BtnForward.EnableWindow( Enable );  
         break;
      case CSC_NAVIGATEBACK:
         m_BtnBack.EnableWindow( Enable );
         break;
   }
}

//******************************************************************************

void BusInfoDlg::OnDownloadBeginBushtml() 
{
   TRACE_METHOD( CLASSNAME, BI_DOWNLOAD );
   CString     szFileName( DD::search_avi );

   szFileName = m_csFileDir + szFileName;
   m_Animate.Open(szFileName);
   m_BtnStop.EnableWindow( TRUE );
// Need to move to message file
   SetMessageStatusBar( TXT_LOAD_HTML );
}

//******************************************************************************

void BusInfoDlg::OnDownloadCompleteBushtml() 
{
   TRACE_METHOD( CLASSNAME, BI_COMPLETE );
   m_BtnStop.EnableWindow( FALSE );
   SetMessageStatusBar( NULL_STRING );
   m_Animate.Close( );   // Same as close
}

//******************************************************************************

void BusInfoDlg::SetHomeFocus() 
{
   TRACE_METHOD( CLASSNAME, BI_SETHOMEFOCUS );
   m_BtnHome.SetFocus();   // Set focus on home key
}

//******************************************************************************

void BusInfoDlg::GetHomeNameFromRegistry(CString& strHomeName)
{
   TRACE_METHOD( CLASSNAME, I_("GetHomeNameFromRegistry") );

   strHomeName = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, 
                                         CONFIGURATION_CONSTANTS::DataPath,
                                         CONFIGURATION_CONSTANTS::FYIfile ).c_str();
   strHomeName.TrimRight();
   if( strHomeName == "" )
      strHomeName = CString( DD::file_) + m_csFileDir + DD::config_FYI;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BusInfoDlg.cpp-arc  $
 * 
 *    Rev 1.6   Sep 15 2005 15:10:54   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.5   Mar 21 2003 18:33:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   27 Mar 2002 20:01:00   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.2   Oct 12 2000 15:10:20   HUANGSHA
 * Fix when go back to home page, it should reretrive the registry again
 * 
 *    Rev 1.1   May 03 2000 16:45:26   BUZILA
 * changed to call at DownloadComplete Close for the animator instead of Open(NULL)
 * 
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Aug 10 1999 11:19:38   BUZILA
 * added support for configuring FYI screen's start page
 * 
 *    Rev 1.2   Jul 12 1999 17:31:00   PRAGERYA
 * 
 *    Rev 1.1   Jul 08 1999 10:04:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
