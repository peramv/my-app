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
// ^FILE   : EStatementDlg.cpp
// ^AUTHOR : Shaobo Huang
// ^DATE   : July, 2002
//
// ----------------------------------------------------------
//
// ^CLASS    : EStatementDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#include "stdafx.h"
#include "MFDSTC.h"

#include "EStatementDlg.h"
#include <ifastbp\EStatementProcessIncludes.h>
#include <ConfigManager.hpp>
#include "ConfigurationConstants.h"


extern CLASS_IMPORT const I_CHAR* CMD_GUI_ESTATEMENT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< EStatementDlg > dlgCreator( CMD_GUI_ESTATEMENT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME = I_( "EStatementDlg" );
   const I_CHAR *BI_COMPLETE = I_( "OnDownloadCompleteBushtml" );
   const I_CHAR *BI_DOWNLOAD = I_( "OnDownloadBeginBushtml" );
   const I_CHAR *BI_ONWEBBACK = I_( "OnWebback" );
   const I_CHAR *BI_ONWEBFWD = I_( "OnWebfwd" );
   const I_CHAR *BI_ONWEBHOME = I_( "OnWebhome" );
   const I_CHAR *BI_ONWEBSTOP = I_( "OnWebstop" );
   const I_CHAR *BI_SETHOMEFOCUS = I_( "SetHomeFocus" );
   const I_CHAR *BI_STATECHANGE = I_( "OnCommandStateChangebushtml" );
   const I_CHAR *URL_FILE = I_( "file:///" );
   const I_CHAR *SEARCH_AVI = I_( "\\search.avi" );
}

//******************************************************************************
// Public methods
//******************************************************************************

EStatementDlg::EStatementDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( EStatementDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   //{{AFX_DATA_INIT(EStatementDlg)
   //}}AFX_DATA_INIT

   m_csFileDir = "";
}

//******************************************************************************

EStatementDlg::~EStatementDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   for( int i = 0; i < m_stCount; i++ )
   {
      delete m_stCtrlSize[i];
   }
}

//******************************************************************************

void EStatementDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(EStatementDlg)
   DDX_Control(pDX, IDC_WEBSTOP, m_btnStop);
   DDX_Control(pDX, IDC_WEBHOME, m_btnHome);
   DDX_Control(pDX, IDC_WEBFWD, m_btnForward);
   DDX_Control(pDX, IDC_WEBBACK, m_btnBack);
   DDX_Control(pDX, IDC_BUSHTML, m_browserCtrl);
   DDX_Control(pDX, IDC_ANIMATION2, m_Animate);
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(EStatementDlg, BaseMainDlg)
//{{AFX_MSG_MAP(EStatementDlg)
ON_BN_CLICKED(IDC_WEBBACK, OnWebback)
ON_BN_CLICKED(IDC_WEBFWD, OnWebfwd)
ON_BN_CLICKED(IDC_WEBHOME, OnWebhome)
ON_BN_CLICKED(IDC_WEBSTOP, OnWebstop)
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************

BOOL EStatementDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   m_csFileDir = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, 
                                         CONFIGURATION_CONSTANTS::DataPath,
                                         CONFIGURATION_CONSTANTS::Path ).c_str();
   m_csFileDir.TrimRight();

   DString requestURL = BuildRequestURL();

   // Display HTML doc associated with selected item
   m_browserCtrl.Navigate( requestURL.c_str(), NULL, NULL, NULL, NULL );

   MoveDialog( GUIPOS_BOTTOM, 0 );             // Place me under my parent window

   //remember the intial size of the window
   m_stCount = 0;

   WINDOWPLACEMENT tmp;
   GetWindowPlacement( &tmp );
   m_stCtrlSize[m_stCount] = new ST_CTRL_SIZE;
   m_stCtrlSize[m_stCount]->ctrlID = GetDlgCtrlID();
   m_stCtrlSize[m_stCount]->ctrlRect = tmp.rcNormalPosition;

   CWnd* pwndChild = GetWindow(GW_CHILD);
   while( pwndChild )
   {
      pwndChild->GetWindowPlacement( &tmp );

      if( m_stCount < 15 )
      {
         m_stCount++;
         m_stCtrlSize[m_stCount] = new ST_CTRL_SIZE;
         m_stCtrlSize[m_stCount]->ctrlID = pwndChild->GetDlgCtrlID();
         m_stCtrlSize[m_stCount]->ctrlRect = tmp.rcNormalPosition;
      }
      pwndChild = pwndChild->GetNextWindow();
   }

   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

bool EStatementDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{
   DString requestURL = BuildRequestURL();
   // Display HTML doc associated with selected item
   m_browserCtrl.Navigate( requestURL.c_str(), NULL, NULL, NULL, NULL );
   return(TRUE);
}

//******************************************************************************

void EStatementDlg::OnWebback() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBBACK );
   m_browserCtrl.GoBack();
}

//******************************************************************************

void EStatementDlg::OnWebfwd() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBFWD );
   m_browserCtrl.GoForward();
}

//******************************************************************************

void EStatementDlg::OnWebhome() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBHOME );

   DString requestURL = BuildRequestURL();
   m_browserCtrl.Navigate(requestURL.c_str(), NULL, NULL, NULL, NULL); // Display HTML doc associated with selected item
}

//******************************************************************************

void EStatementDlg::OnWebstop() 
{
   TRACE_METHOD( CLASSNAME, BI_ONWEBSTOP );
   m_browserCtrl.Stop();
}

//******************************************************************************

BEGIN_EVENTSINK_MAP(EStatementDlg, BaseMainDlg)
//{{AFX_EVENTSINK_MAP(EStatementDlg)
ON_EVENT(EStatementDlg, IDC_BUSHTML, 105 /* CommandStateChange */, OnCommandStateChangeBushtml, VTS_I4 VTS_BOOL)
ON_EVENT(EStatementDlg, IDC_BUSHTML, 106 /* DownloadBegin */, OnDownloadBeginBushtml, VTS_NONE)
ON_EVENT(EStatementDlg, IDC_BUSHTML, 104 /* DownloadComplete */, OnDownloadCompleteBushtml, VTS_NONE)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void EStatementDlg::OnCommandStateChangeBushtml(long Command, BOOL Enable) 
{
   TRACE_METHOD( CLASSNAME, BI_STATECHANGE );
   switch( Command )
   {
      case CSC_NAVIGATEFORWARD:
         m_btnForward.EnableWindow( Enable );  
         break;
      case CSC_NAVIGATEBACK:
         m_btnBack.EnableWindow( Enable );
         break;
   }
}

//******************************************************************************

void EStatementDlg::OnDownloadBeginBushtml() 
{
   TRACE_METHOD( CLASSNAME, BI_DOWNLOAD );
   CString     szFileName( SEARCH_AVI);

   szFileName = m_csFileDir + szFileName;
   m_Animate.Open(szFileName);
   m_btnStop.EnableWindow( TRUE );
// Need to move to message file
   SetMessageStatusBar( TXT_LOAD_ESTATEMENT );
}

//******************************************************************************

void EStatementDlg::OnDownloadCompleteBushtml() 
{
   TRACE_METHOD( CLASSNAME, BI_COMPLETE );
   m_btnStop.EnableWindow( FALSE );
   SetMessageStatusBar( NULL_STRING );
   m_Animate.Close( );   // Same as close
}

//******************************************************************************

void EStatementDlg::SetHomeFocus() 
{
   TRACE_METHOD( CLASSNAME, BI_SETHOMEFOCUS );
   m_btnHome.SetFocus();   // Set focus on home key
}

//******************************************************************************

DString EStatementDlg::BuildRequestURL()
{
   TRACE_METHOD( CLASSNAME, I_("BuildRequestURL") );

   DString accountNum;
   getParent()->getField( this, BF::NullContainerId, ESTATEMENT::ACCOUNT_NUM, accountNum );

   SetAccount( accountNum);
   SetAccountCaption();


   DString companyId;
   getParent()->getField( this, BF::NullContainerId, ESTATEMENT::MANAGEMENT_CO_ID, companyId );

   DString sessionId;
   getParent()->getField( this, BF::NullContainerId, ESTATEMENT::RTS_SESSION_ID, sessionId );

   DString userId;
   getParent()->getField( this, BF::NullContainerId, ESTATEMENT::USER_ID, userId );

   DString langId;
   getParent()->getField( this, BF::NullContainerId, ESTATEMENT::LANGUAGE_ID, langId );

   DString localeId;
   getParent()->getField( this, BF::NullContainerId, ESTATEMENT::LOCALE_ID, localeId );

   DString requestURL = GetConfigValueAsString(CONFIGURATION_CONSTANTS::MFDSTC,I_("eStatement"), I_("RequestURL"));
   requestURL += I_("&cz=") + CalculateCZValue(companyId);
   requestURL += I_("&userId=") + userId;
   requestURL += I_("&rtsSessionId=") + sessionId;
   requestURL += I_("&languageId=") + langId;
   requestURL += I_("&companyId=") + companyId;
//for testing only
//accountNum = GetConfigValueAsString(CONFIGURATION_CONSTANTS::MFDSTC,I_("eStatement"), I_("AccountNum"));
   requestURL += I_("&accountNum=") + accountNum;

   requestURL += I_("&locale=") + localeId.left(2);

   time_t ltime;
   time( &ltime );
   I_CHAR s[128];
   wsprintf( s, I_("%lx"), ltime );

   requestURL += I_("&si=");
   requestURL += s;

   return(requestURL);
}

//******************************************************************************

DString EStatementDlg::CalculateCZValue(DString& companyId)
{
   //get the environment string from registry setting
   DString env = GetConfigValueAsString(CONFIGURATION_CONSTANTS::MFDSTC,I_("eStatement"), I_("Environment"));
   DString compId = companyId.strip().upperCase() + env.strip().upperCase();

   DString cz;
   int count = compId.length();
   cz.appendInt(count);
   cz.stripLeading(I_CHAR('0'));
   for( int i = 0; i < count; i++ )
   {
      int ch = compId[i] - I_CHAR('A');
      DString tmp;
      tmp.appendInt(ch);
      if( tmp.length()==1 )
      {
         cz += I_("0") + tmp;
      }
      else
      {
         cz += tmp;
      }
   }
   return(cz);
}

//******************************************************************************

void EStatementDlg::OnSize(UINT nType, int cx, int cy) 
{
   BaseMainDlg::OnSize(nType, cx, cy);

   // TODO: Add your message handler code here
   WINDOWPLACEMENT tmp;
   GetWindowPlacement( &tmp );
   CRect newRect = tmp.rcNormalPosition;
   int wd = newRect.right - newRect.left;
   int ht = newRect.bottom - newRect.top;

   for( int i = 1; i <= m_stCount; i++ )
   {
      CRect r0 = m_stCtrlSize[0]->ctrlRect; 
      CRect r  = m_stCtrlSize[i]->ctrlRect;
      int w, h;
      switch( m_stCtrlSize[i]->ctrlID )
      {
         case IDC_BUSHTML:
            r.bottom = ht - (r0.bottom - r0.top - r.bottom);
            r.right  = wd - (r0.right - r0.left - r.right);
            break;

         case IDC_ANIMATION2:
            h = r.bottom - r.top;
            r.bottom = ht - (r0.bottom - r0.top - r.bottom);
            r.top = r.bottom - h;
            break;

         default:
            w = r.right - r.left;
            h = r.bottom - r.top;
            r.left = wd - ((r0.right-r0.left) - r.left);
            r.right = r.left + w;

            r.top = ht - (r0.bottom-r0.top - r.top);
            r.bottom = r.top + h;
            break;
      }
      GetDlgItem(m_stCtrlSize[i]->ctrlID)->MoveWindow(r);
   }

   RepositionBars( AFX_IDW_STATUS_BAR, AFX_IDW_STATUS_BAR, 0 );

   Invalidate();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EStatementDlg.cpp-arc  $
// 
//    Rev 1.4   Sep 15 2005 15:12:00   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Mar 21 2003 18:36:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Oct 09 2002 23:55:40   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.1   13 Aug 2002 14:14:00   HUANGSHA
// Modification for requesting parameters
// 
//    Rev 1.0   31 Jul 2002 09:44:12   HUANGSHA
// Initial revision.
 * 
 */

