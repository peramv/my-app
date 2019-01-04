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
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MFDSTC.cpp
// ^AUTHOR :
// ^DATE   :
//
// ^CLASS    :
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "MFDSTC.h"
#include "AboutDlg.h"
#include <clientlocale.hpp>
#include <ConfigManager.hpp>
#include "ConfigurationConstants.h"
#include <ifastcsi\CsiSession.h>
#include <DebugMgr.hpp>
#include <ifastcsi\ifastcsi.h>
#include <uibase\DSTCDoc.h>
#include "DSTCCommandLineInfo.h"
#include "DSTCView.h"
//#include <gxall.h>
#include <locale.h>
#include "MainFrm.h"
#include "MFDSTCSetup.hpp"
#include <SingletonRegister.hpp>
#include <bfutil\clientlocalecontext.hpp>
#include <bfcbo\bfcbo.hpp>
#include <bfutil/bfguard.hpp>
#include "GuiConfig.h"
#include "SiteConfig.h"
#include <xercesc\util\PlatformUtils.hpp>
#include <xercesc\dom\DOMException.hpp>
#include <bfproc\commandtraits.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <xercesc\sax\saxparseexception.hpp>
#include <datapath.h>
#include <registryvalue.hpp>
#include <registrykey.hpp>

#include <ifsupp/ExceptionReport.hpp>
#include <ifsupp/ifsuppext.hpp>
#include "ConfigSelectionDlg.h"

#include <ifastdbrkr/ifastdbrkr.hpp>

#include <bf/log/log.hpp>
#include <bf/log/logtargetdisk.hpp>

static DString s_appName( I_("MFDSTC") );
static DString s_appDesc( I_("iFAST/Desktop") );

#include <uibase\win32uibase_global.hpp>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <ifsupp/AboutPropSheet.h>

namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME      = I_( "MFDSTCApp" );
   const I_CHAR * const INITINSTANCE   = I_( "InitInstance" );
   const I_CHAR * const DEFAULT_LOCALE = I_( "English" );

   gui::DStringProperty g_webPageUrl   ( 'C',            L"WebPages/WebPageURL", I_("") );
   gui::DStringProperty g_webCMD       ( 'C',            L"WebPages/WebPageCmd", I_("") );
   gui::DStringProperty g_userId       ( 'C',            L"WebPages/UserId",     I_("") );
   gui::DStringProperty g_passWord     ( 'C',            L"WebPages/PassWord",   I_("") );
   gui::DStringProperty g_webPageName  ( L"PageName",    I_("") );
   gui::DStringProperty g_dialogCMDName( L"CmdName",     I_("") );
   gui::DStringProperty g_overrideCMD  ( L"OverrideCMD", I_("") );
   gui::DStringProperty g_parameter    ( L"Parameter",   I_("") );

   gui::DStringProperty g_currHost     ( L"HostAddress", I_("") );
   gui::DStringProperty g_currPort     ( L"HostPort",    I_("") );
   gui::DStringProperty g_currCompany  ( L"CompanyCode", I_("") );
   gui::DStringProperty g_currEnv      ( L"envName",     I_("") );
}

#include <ifastlogfile.hpp>
extern _declspec( dllimport ) void setOleInitialized( int _oleInitialized);

/////////////////////////////////////////////////////////////////////////////
// MFDSTCApp

//Register the message to kill splash screen
UINT WM_KILLSPLASH = RegisterWindowMessage( I_( "WM_KILLSPLASH" ) );

/////////////////////////////////////////////////////////////////////////////
// The one and only DSTCApp object
MFDSTCApp theApp;

BEGIN_MESSAGE_MAP(MFDSTCApp, CWinApp)
//{{AFX_MSG_MAP(MFDSTCApp)
ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
// Standard file based document commands
ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

//******************************************************************************

MFDSTCApp::MFDSTCApp() :
m_hResInstance( NULL ),
m_hDefaultRes(NULL),
m_dstrCurrentLang( NULL_STRING ),
m_dstrCurrentCompId( NULL_STRING ),
m_dstrCurrentResourceDllName( NULL_STRING ),
m_pNewFont(NULL),
m_pFixedFont(NULL) {
   // TODO: add construction code here,
   // Place all significant initialization in InitInstance
}

//******************************************************************************

MFDSTCApp::~MFDSTCApp() {
   if ( m_hResInstance && m_hResInstance != m_hDefaultRes )
      FreeLibrary( m_hResInstance );

//   if (m_pFixedFont)
//      delete m_pFixedFont;
}

//******************************************************************************
// MFDSTCApp initialization

BOOL MFDSTCApp::InitInstance() {
   // Parse command line for standard shell commands, DDE, file open.
   // Do this before *anything* else so that we can set a different DST Registry tree to use with the -m option.
   DSTCCommandLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);

   xercesc::XMLPlatformUtils::Initialize();
   // Load configuration value overrides
   // IMPORTANT: This must be done as soon as possible once we know the Configuration Application Name.
   // Some of the code in the core classes will read values from the Configuration and cache them.  We need
   // to update the Configuration values before this happens.
   if ( cmdInfo.getSiteXml() != I_("") ) {
      if( FALSE == SiteConfigInit( cmdInfo.getSiteXml(), cmdInfo.doesSiteXmlOverride() ) ) {
         return( FALSE );
      }
   }

   if (GetConfigValueAsBool(I_("RTSHost"), I_("UseSonicMQ")))
   {
     ifastdbrkr::setMessageService(ifastdbrkr::MessageService::SonicMQ);
   }
   else
   {
     ifastdbrkr::setMessageService(ifastdbrkr::MessageService::ActiveMQ);
   }

   TRACE_METHOD( CLASSNAME, INITINSTANCE );
   {
      bool bLogEnabled = GetConfigValueAsBool( I_("Support"), I_("Log_Enable") );
      // Start logging
      DString dstrLogFile = GetConfigValueAsString( I_("Support"), I_("Log_File") );
      DString dstrLogPath = GetConfigValueAsString( I_("Support"), I_("Log_Path") );
      if ( dstrLogPath.length() == 0 ) {
         dstrLogPath = I_(".");
      }
      bf::log::theLog.addTarget( I_( "disk" ), new IFastLogFile( dstrLogPath, dstrLogFile, bLogEnabled ) );

      int iLogLevel = GetConfigValueAsInteger( I_("Support"), I_("Log_Level") );
      if( 0 != iLogLevel &&
          iLogLevel != bf::log::theLog.getReportingThreshold() ) {
         bf::log::theLog.setReportingThreshold( (bf::log::LogStream::Level)iLogLevel );
      }
   }

   bf::log::theLog << bf::log::endl;
   bf::log::theLog << I_( "App Name:     " ) << s_appName << I_( " - " ) << s_appDesc << bf::log::endl;
   bf::log::theLog << I_( "----------------------------------------------------------------------------" ) << bf::log::endl;
   bf::log::theLog << bf::log::endlf;

   AfxInitRichEdit();
   GXInit();
   // CG: This line was added by the OLE Control Containment component
   AfxEnableControlContainer();

   INITCOMMONCONTROLSEX iccex;
   iccex.dwSize = sizeof( INITCOMMONCONTROLSEX );
   iccex.dwICC = ICC_WIN95_CLASSES;
   InitCommonControlsEx( &iccex );

   // Initialize OLE libraries
   if ( !AfxOleInit() ) {
      // Put up error message and exit
      return(FALSE);
   }
   setOleInitialized(1);	
   // Standard initialization
   // If you are not using these features and wish to reduce the size
   //  of your final executable, you should remove from the following
   //  the specific initialization routines you do not need.

   // Register all OLE server (factories) as running.  This enables the
   //  OLE libraries to create objects from other applications.
   COleTemplateServer::RegisterAll();

   // When a server application is launched stand-alone, it is a good idea
   //  to update the system registry in case it has been damaged.
   COleObjectFactory::UpdateRegistryAll();

   CString strCmd = m_lpCmdLine;
   strCmd.MakeUpper();

   if ( strCmd.CompareNoCase( I_( "/REGSERVER" ) ) == 0 ) {
      return(FALSE);
   }

   LoadStdProfileSettings();  // Load standard INI file options (including MRU)

   TCHAR szLanguage[128];
   GetLocaleInfo( LOCALE_SYSTEM_DEFAULT, LOCALE_SENGLANGUAGE, szLanguage, 127);
   m_dstrSysLang = DString( szLanguage );
   m_dstrSysLang.strip().upperCase();

   SetLocale();

   m_pFixedFont = new CFont();
   CString strFaceName;
   if ( m_dstrSysLang == I_("JAPANESE") || m_dstrSysLang == I_("JPN") )
      strFaceName = "‚l‚r ƒSƒVƒbƒN";
   else
      strFaceName = "Courier";
   if ( m_pFixedFont ) {
      m_pFixedFont->CreatePointFont(100, strFaceName);
//      m_pNewFont = m_pFixedFont;
   }
   m_hDefaultRes = AfxGetResourceHandle( );

   // Register the application's document templates.  Document templates
   //  serve as the connection between documents, frame windows and views.
   CSingleDocTemplate *pDocTemplate;
   pDocTemplate = new CSingleDocTemplate( IDR_MAINFRAME,
                                          RUNTIME_CLASS(DSTCDoc),
                                          RUNTIME_CLASS(CMainFrame),       // main SDI frame window
                                          RUNTIME_CLASS(CDSTCView));
   AddDocTemplate(pDocTemplate);
   
   ifastdbrkr::initialize();

   DString errorMessage;
   bool performTesting = !cmdInfo.getSiteXml().empty();

   if (MFDSTCSetup::init(cmdInfo.directConnect(), performTesting, errorMessage) == false) {
     MessageBox(HWND_DESKTOP, errorMessage.c_str(), I_("Connection Error:"), MB_OK);  //)
     return (FALSE);
   }

   //Hide splash screen
   ::PostMessage( HWND_BROADCAST, WM_KILLSPLASH, 0, 0 );

   // Make sure the sysload path is defined.
   ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
   Configuration cfgPath = pDSTCMgr->retrieveConfig( CONFIGURATION_CONSTANTS::DataPath );
   DString sysloadPath = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::SysloadPath );

   // If not, default it to the data path
   if ( sysloadPath.empty() ) {
      sysloadPath = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::Path );
      ConfigValue cvSysloadPath( sysloadPath );
      cfgPath.set( CONFIGURATION_CONSTANTS::SysloadPath, cvSysloadPath );
      pDSTCMgr->storeConfig( cfgPath );

      ConfigManager *pCboMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::CBO );
      pCboMgr->storeConfig( cfgPath );
   }

   // Dispatch commands specified on the command line
   if ( !ProcessShellCommand(cmdInfo) ) {
      return(FALSE);
   }
   return(TRUE);
}

//******************************************************************************
BOOL MFDSTCApp::SiteConfigInit( const DString& t, bool bOverrideRegistry ) {
   // bOverrideRegistry - values from Site.xml file will override the ones in the user's registry
   DString dstrSiteXml = t;
   dstrSiteXml.stripLeading(I_(' '));
   dstrSiteXml.stripTrailing(I_(' '));
   if ( dstrSiteXml == NULL_STRING ) {
      return(TRUE);
   }
   ClientLocale clientLocale;
   LCID lcid = clientLocale.getLCID();
   DString dstrLang;

   //if client locale is french load the french resources 
   //will be used for configuration slection and logon dialogs
   if(LANG_FRENCH == PRIMARYLANGID(LANGIDFROMLCID(lcid)))
   {
		dstrLang = I_("FR");
   }
   else
   {
		dstrLang = I_("ENG");
   }

   ((MFDSTCApp*)AfxGetApp())->LoadResourceDllByLanguageAndMarket( I_(""), I_("Canada"), dstrLang);

   site::SiteConfig* pSC = site::SiteConfig::getInstance();

   ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
   CT2CA pszConvertedAnsiString( dstrSiteXml.c_str());
   std::string SiteConfigFileName( pszConvertedAnsiString );

   DString q = GetConfigValueAsString( I_("RTSHost"), I_("SMQInqQueue") );

   bool bSelectedFromDlg = false;
   if ( SiteConfigFileName != "" ) {
      try {
         ConfigSelectionDlg dlgSelect(SiteConfigFileName );
         switch( dlgSelect.getFileCount() ) {
            case 0:
               {
                  char szBuf[4096];
                  sprintf(szBuf, "No valid configuration file found based on %s.\nExiting application\n", SiteConfigFileName.c_str());
                  MessageBoxA( HWND_DESKTOP, szBuf, "Error reading configuration", MB_OK );
                  return(FALSE);
               }
            case 1:
               SiteConfigFileName = DStringA(dlgSelect.getFileName()).c_str();
               break;
            default:
               {
                  if( IDCANCEL == dlgSelect.DoModal() ) {
                     return(FALSE);
                  }
                  SiteConfigFileName = DStringA(dlgSelect.getFileName()).c_str();
                  bSelectedFromDlg = true;
               }
         }

         pSC->init( SiteConfigFileName, pDSTCMgr );
         DString dstrDescription = pSC->getDescription();
         Configuration cfg( I_("SiteXML") );
         if(bSelectedFromDlg)
         {
            DString dstrSiteConfigFileName = SiteConfigFileName;
            cfg.set( DString(I_("file")), dstrSiteConfigFileName );
         }
         else
         {
            cfg.set( DString(I_("file")), dstrSiteXml );
         }
         cfg.set( DString(I_("Description")),dstrDescription);

         cfg.set( DString(I_("override")), bOverrideRegistry ? DString(I_("True")) : DString(I_("False")) );
         pDSTCMgr->storeConfig( cfg );
         pSC->setParm( I_("AwdType"),I_("InterfaceDll"), I_("AwdType"), site::DStringProperty( L"InterfaceDll"), bOverrideRegistry );
         pSC->setParm( I_("AwdType"),I_("AutoLogon"), I_("AwdType"), site::DStringProperty( L"AutoLogon" ), bOverrideRegistry );
         pSC->setParm( I_("DataPath"), I_("FYIfile"), I_("DataPath"), site::DStringProperty( L"FYIfile" ), bOverrideRegistry );
         pSC->setParm( I_("DataPath"), I_("Path"), I_("DataPath"), site::DStringProperty( L"Path" ), bOverrideRegistry );
         ConditionManager::getInstance()->setPath( GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, I_("DataPath"), I_("Path") ) );
         SetGlobalDataPath( GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, I_("DataPath"), I_("Path") ) );
         SetGlobalIniPath( GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, I_("DataPath"), I_("Path") ) );
         pSC->setParm( I_("DataPath"), I_("SysLoadPath"), I_("DataPath"), site::DStringProperty( L"SysLoadPath" ), bOverrideRegistry );
         pSC->setParm( I_("DataPath"), I_("RepositorySource"), I_("DataPath"), site::DStringProperty( L"RepositorySource" ), bOverrideRegistry );
         pSC->setParm( I_("DemoMode"), I_("ProtoDataPath"), I_("DemoMode"), site::DStringProperty( L"ProtoDataPath" ), bOverrideRegistry );

       pSC->setParm( I_("Support"), I_("SpecialPasswordRules"), I_("Support"),
                  site::DStringProperty( L"SpecialPasswordRules" ), bOverrideRegistry );

         pSC->setParm( I_("Support"),I_("ViewTimeLog_Enable"), I_("ViewTimeLog"), site::DStringProperty( L"Active"), bOverrideRegistry );
         pSC->setParm( I_("Support"),I_("ViewTimeLog_Path"), I_("ViewTimeLog"), site::DStringProperty( L"Path"), bOverrideRegistry );
         pSC->setParm( I_("Support"),I_("ViewTimeLog_Size"), I_("ViewTimeLog"), site::DStringProperty( L"Size"), bOverrideRegistry );
         pSC->setParm( I_("Support"),I_("ViewTimeLog_Enable"), I_("Support"), site::DStringProperty( L"ViewTimeLog_Enable"), bOverrideRegistry );
         pSC->setParm( I_("Support"),I_("ViewTimeLog_Path"), I_("Support"), site::DStringProperty( L"ViewTimeLog_Path"), bOverrideRegistry );
         pSC->setParm( I_("Support"),I_("ViewTimeLog_Size"), I_("Support"), site::DStringProperty( L"ViewTimeLog_Size"), bOverrideRegistry );

         pSC->setParm( I_("Support"), I_("Log_File"), I_("LoggingOptions"), site::DStringProperty( L"LogFile" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("Log_Path"), I_("LoggingOptions"), site::DStringProperty( L"LogPath" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("Log_File"), I_("Support"), site::DStringProperty( L"Log_File" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("Log_Path"), I_("Support"), site::DStringProperty( L"Log_Path" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("Log_Enable"), I_("Support"), site::DStringProperty( L"Log_Enable" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("Log_Level"), I_("Support"), site::DStringProperty( L"Log_Level" ), bOverrideRegistry );

         pSC->setParm( I_("Support"), I_("ViewLog_Append"), I_("DebugOptions"), site::DStringProperty( L"AppendFile" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_Enable"), I_("DebugOptions"), site::DStringProperty( L"Debug" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_Path"), I_("DebugOptions"), site::DStringProperty( L"DebugPath" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_Complete"), I_("DebugOptions"), site::DStringProperty( L"CompleteLog" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_Append"), I_("Support"), site::DStringProperty( L"ViewLog_Append" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_Enable"), I_("Support"), site::DStringProperty( L"ViewLog_Enable" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_Path"), I_("Support"), site::DStringProperty( L"ViewLog_Path" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_Complete"), I_("Support"), site::DStringProperty( L"ViewLog_Complete" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_InsertDateTime"), I_("Support"), site::DStringProperty( L"ViewLog_InsertDateTime" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_RawRequest"), I_("Support"), site::DStringProperty( L"ViewLog_RawRequest" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ViewLog_RawResponse"), I_("Support"), site::DStringProperty( L"ViewLog_RawResponse" ), bOverrideRegistry );

         pSC->setParm( I_("Support"), I_("ExceptionReport_Enable"), I_("Support"), site::DStringProperty( L"ExceptionReport_Enable" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ExceptionReport_Path"), I_("Support"), site::DStringProperty( L"ExceptionReport_Path" ), bOverrideRegistry );


         pSC->setParm( I_("Support"), I_("DisplayConnectionIcon"), I_("Support"), site::DStringProperty( L"DisplayConnectionIcon" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("DisplayConditionName"), I_("Support"), site::DStringProperty( L"DisplayConditionName" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("AllPowerfulVaalMode"), I_("Support"), site::DStringProperty( L"AllPowerfulVaalMode" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ShowClientNamePane"), I_("Support"), site::DStringProperty( L"ShowClientNamePane" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ExceptionReport_Enable"), I_("Support"), site::DStringProperty( L"ExceptionReport_Enable" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ExceptionReport_Path"), I_("Support"), site::DStringProperty( L"ExceptionReport_Path" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("BandInfoByCompanyId"), I_("Support"), site::DStringProperty( L"BandInfoByCompanyId" ), bOverrideRegistry );

#ifdef _DEBUG
         pSC->setParm( I_("Debug"), I_("OverridenDSKURLEnable"), I_("Debug"), site::DStringProperty( L"OverridenDSKURLEnable" ), bOverrideRegistry );
         pSC->setParm( I_("Debug"), I_("OverridenDSKURL"), I_("Debug"), site::DStringProperty( L"OverridenDSKURL" ), bOverrideRegistry );
         pSC->setParm( I_("Debug"), I_("DebugEXT"), I_("Debug"), site::DStringProperty( L"DebugEXT" ), bOverrideRegistry );
         pSC->setParm( I_("Debug"), I_("StubModeOnBrowserScreen"), I_("Debug"), site::DStringProperty( L"StubModeOnBrowserScreen" ), bOverrideRegistry );
         pSC->setParm( I_("Debug"), I_("ShowMGMTOptionsSeparator"), I_("Debug"), site::DStringProperty( L"ShowMGMTOptionsSeparator" ), bOverrideRegistry );
#endif

         pSC->setParm( I_("Support"), I_("ReportEMailAddress"), I_("Support"), site::DStringProperty( L"ReportEMailAddress" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("ControlTextRewriter_Path"),
            I_("Support"), site::DStringProperty( L"ControlTextRewriter_Path" ), bOverrideRegistry );
         pSC->setParm( I_("Support"), I_("KeyPeek_Path"), I_("Support"), site::DStringProperty( L"KeyPeek_Path" ), bOverrideRegistry );

         pSC->setParm( I_("Market"), I_("Market"), I_("Market"), site::DStringProperty( L"Market" ), bOverrideRegistry );

         pSC->setParm( I_("Market"), I_("ValidCompanies"), I_("Market"), site::DStringProperty( L"ValidCompanies" ), bOverrideRegistry );

         pSC->setParm( I_("Csi"), I_("Host"), I_("Csi"), site::DStringProperty( L"Host" ), bOverrideRegistry );
         pSC->setParm( I_("Csi"), I_("Param"), I_("Csi"), site::DStringProperty( L"Param" ), bOverrideRegistry );
         pSC->setParm( I_("Csi"), I_("Type"), I_("Csi"), site::DStringProperty( L"Type" ), bOverrideRegistry );

/* OBSOLETE 03Dec2011 - CP
 * RTS Support has been removed from iFAST/Desktop
         pSC->setParm( I_("RTSHost"), I_("RTSHostPort"), I_("RTSHost"), site::DStringProperty( L"RTSHostPort" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("UseSonicMQ"), I_("RTSHost"), site::DStringProperty( L"UseSonicMQ" ), bOverrideRegistry );
 */
         // RTSHostIP is still used by Character Screen Integration.  We should flag that as a deprecated use, but that's a task for another day
         //  - 03Dec2011 CP
         pSC->setParm( I_("RTSHost"), I_("RTSHostIP"), I_("RTSHost"), site::DStringProperty( L"RTSHostIP" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("PersistentConnections"), I_("RTSHost"), site::DStringProperty( L"PersistentConnections" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("RecycleInterval"), I_("RTSHost"), site::DStringProperty( L"RecycleInterval" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQBrokerURLs"), I_("RTSHost"), site::DStringProperty( L"SMQBrokerURLs" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQUser"), I_("RTSHost"), site::DStringProperty( L"SMQUser" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQPassword"), I_("RTSHost"), site::DStringProperty( L"SMQPassword" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQMultiQueue"), I_("RTSHost"), site::DStringProperty( L"SMQUpdQueue" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQMultiQueue"), I_("RTSHost"), site::DStringProperty( L"SMQMultiQueue" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQSingleQueue"), I_("RTSHost"), site::DStringProperty( L"SMQInqQueue" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQSingleQueue"), I_("RTSHost"), site::DStringProperty( L"SMQSingleQueue" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("cswacl"), I_("RTSHost"), site::DStringProperty( L"cswacl" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQWaitTimeout"), I_("RTSHost"), site::DStringProperty( L"SMQWaitTimeout" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQMaxConnections"), I_("RTSHost"), site::DStringProperty( L"SMQMaxConnections" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQRTSDataFormat"), I_("RTSHost"), site::DStringProperty( L"SMQRTSDataFormat" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("UseSonicMQ"), I_("RTSHost"), site::DStringProperty( L"UseSonicMQ" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("UseSCC"), I_("RTSHost"), site::DStringProperty( L"UseSCC" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("LDAPUserNS"), I_("RTSHost"), site::DStringProperty( L"UserNS" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("LDAPUserNS"), I_("RTSHost"), site::DStringProperty( L"LDAPUserNS" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQLDAPQueue"), I_("RTSHost"), site::DStringProperty( L"SMQLDAPQueue" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQAWDQueue"), I_("RTSHost"), site::DStringProperty( L"SMQAWDQueue" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("UseSingleSonicConnection"), I_("RTSHost"), site::DStringProperty( L"UseSingleSonicConnection" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("ViewBatch"), I_("RTSHost"), site::DStringProperty( L"ViewBatch"), bOverrideRegistry );

		 pSC->setParm( I_("RTSHost"), I_("UseActiveMQ"), I_("RTSHost"), site::DStringProperty( L"UseActiveMQ" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQBrokerURLs"), I_("RTSHost"), site::DStringProperty( L"AMQBrokerURLs" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQInqQueue"), I_("RTSHost"), site::DStringProperty( L"AMQInqQueue" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQSingleQueue"), I_("RTSHost"), site::DStringProperty( L"AMQSingleQueue" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQMultiQueue"), I_("RTSHost"), site::DStringProperty( L"AMQMultiQueue" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQLDAPQueue"), I_("RTSHost"), site::DStringProperty( L"AMQLDAPQueue" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQUser"), I_("RTSHost"), site::DStringProperty( L"AMQUser" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQPassword"), I_("RTSHost"), site::DStringProperty( L"AMQPassword" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQWaitTimeout"), I_("RTSHost"), site::DStringProperty( L"AMQWaitTimeout" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQTimeToLive"), I_("RTSHost"), site::DStringProperty( L"AMQTimeToLive" ), bOverrideRegistry );
		 pSC->setParm( I_("RTSHost"), I_("AMQMaxConnections"), I_("RTSHost"), site::DStringProperty( L"AMQMaxConnections" ), bOverrideRegistry );

         pSC->setParm( I_("Session"), I_("NotUse_AWD"), I_("Session"), site::DStringProperty( L"NotUse_AWD" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("NotUse_AWD_File"), I_("Session"), site::DStringProperty( L"NotUse_AWD_File" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("NotUse_AWD_Type"), I_("Session"), site::DStringProperty( L"NotUse_AWD_Type" ), bOverrideRegistry );

         pSC->setParm( I_("Session"), I_("UseIntegration_AWD"), I_("Session"), site::DStringProperty( L"UseIntegration_AWD" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("UseIntegration_AWD_File"), I_("Session"), site::DStringProperty( L"UseIntegration_AWD_File" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("UseIntegration_AWD_Type"), I_("Session"), site::DStringProperty( L"UseIntegration_AWD_Type" ), bOverrideRegistry );

         pSC->setParm( I_("Session"), I_("UsePortalIntegration_AWD"), I_("Session"), site::DStringProperty( L"UsePortalIntegration_AWD" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("UsePortalIntegration_AWD_File"), I_("Session"), site::DStringProperty( L"UsePortalIntegration_AWD_File" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("UsePortalIntegration_AWD_Type"), I_("Session"), site::DStringProperty( L"UsePortalIntegration_AWD_Type" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("UsePortalIntegration_AWD_Topic"), I_("Session"), site::DStringProperty( L"UsePortalIntegration_AWD_Topic" ), bOverrideRegistry );

         pSC->setParm( I_("Session"), I_("CallCentreIntegration"), I_("Session"), site::DStringProperty( L"CallCentreIntegration" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("CallCentreIntegration_File"), I_("Session"), site::DStringProperty( L"CallCentreIntegration_File" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("CallCentreIntegration_Type"), I_("Session"), site::DStringProperty( L"CallCentreIntegration_Type" ), bOverrideRegistry );
         pSC->setParm( I_("Session"), I_("CallCentreIntegration_Topic"), I_("Session"), site::DStringProperty( L"CallCentreIntegration_Topic" ), bOverrideRegistry );
      } catch( const xercesc::SAXParseException& exc ) {
         I_CHAR szBuf[4096];
         i_sprintf(szBuf, I_("Error parsing configuration file %s\n\n%s\nLine %d, column %d\nSystemID=%s\nPublicID=%s\n"),
            dstrSiteXml.c_str(),
            exc.getMessage(),
            exc.getLineNumber(),
            exc.getColumnNumber(),
            exc.getSystemId(),
            exc.getPublicId() );
         // Error parsing the XML file
         // How do we signal this?  Simplest approach is a message box!
         // Format an error
         if( IDCANCEL == MessageBox( HWND_DESKTOP, szBuf, I_("Error reading configuration"), MB_OKCANCEL ) ) {
            return(FALSE);
         }
      }
   }

   if( GetConfigValueAsBool(I_("Support"), I_("ExceptionReport_Enable") ) ) {
      ExceptionReport::setLogFileDir(GetConfigValueAsString(I_("Support"), I_("ExceptionReport_Path") ) );
      ExceptionReport::enable(true);
   }

   ifsupp::EnableControlTextRewriter( GetConfigValueAsString( I_("Support"), I_("ControlTextRewriter_Path") ) );

   return(TRUE);
}

//******************************************************************************
/*void MFDSTCApp::GuiConfigInit() {

   return;
   ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
   Configuration cfgPath = pDSTCMgr->retrieveConfig( CONFIGURATION_CONSTANTS::DataPath );
   DString configfile = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::Configfile );
   if ( configfile.stripAll() == NULL_STRING ) {
      configfile = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::Path );
      configfile = configfile + I_("\\config\\iFastGuiConfig.xml");
   }

   CT2CA pszConvertedAnsiString (configfile.c_str());
   std::string GuiConfigFileName (pszConvertedAnsiString);
   if ( GuiConfigFileName != "" ) {
      try {
         gui::GuiConfig * cp = gui::GuiConfig::getInstance();
         cp->init( GuiConfigFileName );

         gui::ConfigIterator citer0 = cp->iterator( L"Hosts", L"Host" );
         while ( cp->next(citer0) ) {
            DString s_currHost, s_currport, s_currenv, s_currCompanyCode;
            s_currHost = cp->getPropertyValue(citer0, g_currHost);
            s_currport = cp->getPropertyValue(citer0, g_currPort);
            s_currCompanyCode =  cp->getPropertyValue(citer0, g_currCompany);
            s_currenv = cp->getPropertyValue(citer0, g_currEnv);
            cp->addConnection(s_currHost, s_currport, s_currCompanyCode, s_currenv);
         }

         DString s_webpageurl, s_webCMD, s_overridecmd, s_parameter;
         DString s_pagename, s_dialogcmdname, s_userid, s_password;

         s_webpageurl = cp->getPropertyValue(g_webPageUrl);
         s_webCMD = cp->getPropertyValue(g_webCMD);
         s_userid = cp->getPropertyValue(g_userId);
         s_password = cp->getPropertyValue(g_passWord);

         webpageMap::getInstance().setwebCMD(s_webCMD);
         webpageMap::getInstance().setwebUrl(s_webpageurl);
         webpageMap::getInstance().setwebUserId(s_userid);
         webpageMap::getInstance().setwebPW(s_password);

         gui::ConfigIterator citer = cp->iterator( L"WebPages", L"Page" );
         while ( cp->next(citer) ) {
            s_pagename = cp->getPropertyValue( citer, g_webPageName );
            s_dialogcmdname = cp->getPropertyValue( citer, g_dialogCMDName );
            s_overridecmd = cp->getPropertyValue( citer, g_overrideCMD );
            webguimaping * _pWebmapp = new webguimaping(s_dialogcmdname, s_pagename, s_overridecmd);

            gui::ConfigIterator citer1 = cp->iteratorchildren( citer, L"Parameter" );
            while ( cp->next(citer1) ) {
               s_parameter = cp->getCurrentValue( citer1, g_parameter );
               _pWebmapp->AddParameter(s_parameter);
            }
         }
      } catch (...) {
         //XML file error
      }
   }
}
*/

//******************************************************************************
int MFDSTCApp::Run() {
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,
                          CLASSNAME,
                          I_( "Run(  )" ) );
   return( CWinApp::Run() );
}

//******************************************************************************

CFont* MFDSTCApp::GetNewFont() {
   return(m_pNewFont);
}

#ifdef _DEBUG
// silly functions to stop the default Afx code from spitting out endless reports of memory leaks
void dumpDebugToNul( void*, size_t ) {
   return;
}
int dbgReportHook( int, char*, int* ) {
   return( 1 );
}     // don't report anything!
#endif

//******************************************************************************

int MFDSTCApp::ExitInstance() {
   SingletonRegister::releaseSingletons();

   // turn off annoying debug memory messages
#ifdef _DEBUG
   // turn off debug memory dumping at program exit
   _CrtSetDumpClient( dumpDebugToNul );
   _CrtSetReportHook( dbgReportHook );
#endif

   return(CWinApp::ExitInstance());
}

//******************************************************************************

BOOL MFDSTCApp::PreTranslateMessage(MSG* pMsg) {
   if ( WM_SYSKEYDOWN == pMsg->message ) {
      switch ( pMsg->wParam ) {
      case VK_F12: // Turn on/off tracing
         if ( DebugMgr::getInstance()->isTracing() ) {
            DebugMgr::getInstance()->setTracing( false );
         } else {
            DebugMgr::getInstance()->setTracing( true );
         }
         break;
      }
   }
   return(CWinApp::PreTranslateMessage(pMsg));
}

//******************************************************************************

void MFDSTCApp::OnAppAbout() {
   AboutDlg aboutDlg;
   aboutDlg.DoModal();
}

//******************************************************************************

void MFDSTCApp::LoadResourceDll( const DString &dstrCompId, const DString &dstrLang ) {
   assert( dstrCompId != NULL_STRING );

   DString newDllLanguage;
   DString userLanguageCountry = ClientLocaleContext::get().getLocale();
   if(userLanguageCountry.left(2) == I_( "fr" ))
   {
      newDllLanguage = I_( "FR" );
   }
   else
   {
      newDllLanguage = I_("ENG");
   }

   if ( m_dstrCurrentCompId == dstrCompId && m_dstrCurrentLang.upperCase() == newDllLanguage)
      return;

   m_dstrCurrentCompId = dstrCompId;

	DString dstrMarket = ClientLocaleContext::get().getMarket();
   LoadResourceDllByLanguageAndMarket(dstrCompId, dstrMarket, newDllLanguage);


/*
   DString strNewLanguage;
   if ( dstrLang != NULL_STRING )
   {
      strNewLanguage = dstrLang;
   }
*/
/*  
   DString dstrResourceDllName, dstrResourceDllAltName, dstrResourceDllEngName;

   HINSTANCE tmp = NULL;

   //If the currently language is undefined, we will default to English.
   if (m_dstrCurrentLang == NULL_STRING)
   {
      DString strLanguage = GetConfigValueAsString( I_("Language"), I_("Language"));
      DString strFrLanguage = I_("FRENCH");

      if( strLanguage.upperCase() == strFrLanguage)
      {
         m_dstrCurrentLang = I_("FR");
      }
      else
      {
         m_dstrCurrentLang = I_("ENG");
      }
   }
   else
   {
      DString strLanguage = GetConfigValueAsString( I_("Language"), I_("Language"));
      DString strFrLanguage = I_("FRENCH");
      DString strEnLanguage = I_("ENGLISH");

//      if( GetConfigValueAsBool( I_("Language"), I_("AllowSwitchLanguage") ) )
      {
         if( strLanguage.upperCase() == strFrLanguage )
         {
            m_dstrCurrentLang = I_("FR");
         }
         else if( strLanguage.upperCase() == strEnLanguage )
         {
            m_dstrCurrentLang = I_("ENG");
         }
         else
         {
            m_dstrCurrentLang = I_("ENG");
         }
      }
//      else
//      {
//         m_dstrCurrentLang = I_("ENG");
//      }
   }
   // Until we get the Client Locale working properly.  We will use the default market of the
   // the datadictionary for market information.  Thus resource will not change without changing
   // to a different datadictionary with a different default market.

   dstrResourceDllName = ClientLocaleContext::get().getMarket() + I_("_") + m_dstrCurrentLang;
   dstrResourceDllEngName = ClientLocaleContext::get().getMarket() + I_("_ENG");
   dstrResourceDllAltName = dstrResourceDllName + I_("_") + dstrCompId;

   // We will search for the resource Dll twice.
   // The first search will be for (Market)_(Lang)_(CompanyId).dll eg. Canada_ENG_manuseg.dll.
   // the second search (Market)_(Lang).dll eg. Canada_ENG.dll.

   if (dstrResourceDllName != NULL_STRING) {
      tmp = LoadLibrary (dstrResourceDllAltName.c_str());
      if (!tmp) {
         tmp = LoadLibrary (dstrResourceDllName.c_str());
         if (!tmp) {
//SP Incident 374782, Aug 8, 2005
            //a proper fix would be to create a new Resource project (i.e ResGermany),and
            //change the Install Shield script and build scripts;
            tmp = LoadLibrary (dstrResourceDllEngName.c_str()); //load the default/english one
            if (tmp) {
               dstrResourceDllName = dstrResourceDllEngName;
            }
         }
      } else {
         dstrResourceDllName = dstrResourceDllAltName;
      }
   }
   if (tmp) {
      m_dstrCurrentResourceDllName = dstrResourceDllName;

      // free res if new resource is load ok
      if ( m_hResInstance && m_hResInstance != m_hDefaultRes )
         FreeLibrary( m_hResInstance );

      AfxSetResourceHandle( m_hResInstance = tmp );

      SetLocale();
   }

   //For release builds only.  If the resource dlls are not found, prompt the user that
   //resource loading failed.  The application continue to working, but potentially unstable
   //depending on which resource was last build.  Eg. If the Canadian resource was last built and
   //the application is used in a canadian market all will be fine, however it will crash
   //in the European market.
#ifndef _DEBUG
   else {
      CString cstr = NULL_STRING;
      CString cstrTemp = NULL_STRING;
      cstr.LoadString ( TXT_ERROR_LOADING );
      cstrTemp += cstr;
      cstrTemp += dstrResourceDllName.c_str();
      cstr.LoadString ( TXT_RESOURCES );
      cstrTemp += cstr;
      AfxMessageBox( cstrTemp );
   }
#endif

*/
   /* if we want to notify the user
   if( !tmp )
     AfxMessageBox(I_("Error in loading the localized resource dll.\nLast used resource will be used."));
     */
}

void MFDSTCApp::LoadResourceDllByLanguageAndMarket(const DString &dstrCompId, const DString &dstrMarket, const DString &dstrLang)
{
   HINSTANCE dllHInstance = NULL;

   DString dstrResourceDllName = I_("") + dstrMarket + I_("_") + dstrLang;
   DString dstrResourceDllEngName = I_("") + dstrMarket + I_("_ENG");
   DString dstrResourceDllAltName;
   if(dstrCompId != I_(""))
      dstrResourceDllAltName = I_("")+ dstrResourceDllName + I_("_") + dstrCompId;

   if (dstrResourceDllName != NULL_STRING) 
   {
      if (dstrCompId != I_("") && (dllHInstance = LoadLibrary (dstrResourceDllAltName.c_str()))) 
      {
         m_dstrCurrentResourceDllName = dstrResourceDllAltName;
      }
      else if (dllHInstance = LoadLibrary (dstrResourceDllName.c_str())) 
      {
         m_dstrCurrentResourceDllName = dstrResourceDllName;
      }
      else if (dllHInstance = LoadLibrary (dstrResourceDllEngName.c_str())) //load the default/english one
      {
         //SP Incident 374782, Aug 8, 2005
         //a proper fix would be to create a new Resource project (i.e ResGermany),and
         //change the Install Shield script and build scripts;
         m_dstrCurrentResourceDllName = dstrResourceDllEngName;
      }
   }

   if (dllHInstance) 
   {
//      m_dstrCurrentResourceDllName = dstrResourceDllName;

      HINSTANCE hCurDLLResource = AfxGetResourceHandle();

	   // free res if new resource is load ok
      if ( m_hResInstance && m_hResInstance == hCurDLLResource )
         FreeLibrary( m_hResInstance );

      AfxSetResourceHandle(m_hResInstance = dllHInstance);

      SetLocale();

		m_dstrCurrentLang = dstrLang;
    }
   //For release builds only.  If the resource dlls are not found, prompt the user that
   //resource loading failed.  The application continue to working, but potentially unstable
   //depending on which resource was last build.  Eg. If the Canadian resource was last built and
   //the application is used in a canadian market all will be fine, however it will crash
   //in the European market.
#ifndef _DEBUG
   else {
      CString cstr = NULL_STRING;
      CString cstrTemp = NULL_STRING;
      cstr.LoadString ( TXT_ERROR_LOADING );
      cstrTemp += cstr;
      cstrTemp += dstrResourceDllName.c_str();
      cstr.LoadString ( TXT_RESOURCES );
      cstrTemp += cstr;
      AfxMessageBox( cstrTemp );
   }
#endif
   /* if we want to notify the user
   if( !dllHInstance )
     AfxMessageBox(I_("Error in loading the localized resource dll.\nLast used resource will be used."));
     */

}

//******************************************************************************
void MFDSTCApp::LoadResourceDllByLanguage( const DString &dstrCompId, const DString &dstrLang )
{
   //if ( m_dstrCurrentCompId == dstrCompId )return;

   m_dstrCurrentCompId = dstrCompId;

   DString strNewLanguage;
   if ( dstrLang != NULL_STRING )
   {
      strNewLanguage = dstrLang;
   }



   //If the currently language is undefined, we will default to English.
   if (m_dstrCurrentLang == NULL_STRING)
   {
      DString strLanguage = GetConfigValueAsString( I_("Language"), I_("Language"));
      DString strFrLanguage = I_("FRENCH");

      if( strLanguage.upperCase() == strFrLanguage)
      {
         m_dstrCurrentLang = I_("FR");
      }
      else
      {
         m_dstrCurrentLang = I_("ENG");
      }
   }
   else
   {
      HINSTANCE hCurDLLResource = AfxGetResourceHandle();
      //char* szNameBuffer = new char[1024];
      //DWORD dwRetVal = GetModuleFileName(hCurDLLResource, (LPTSTR)szNameBuffer, 512 );

      if(hCurDLLResource)
      {
         if ( m_dstrCurrentLang != strNewLanguage)
         {
			   DString dstrMarket = ClientLocaleContext::get().getMarket();
            LoadResourceDllByLanguageAndMarket(dstrCompId, dstrMarket, strNewLanguage);
         }
      }
   }
}

//******************************************************************************

void MFDSTCApp::SetLocale() {
   DString dstrLocale;
   // need the further investigation to see how the system locale affected
   // the dst excellent infrastructure
   if ( m_dstrSysLang == I_("JAPANESE") || m_dstrSysLang == I_("JPN") )
      dstrLocale  = I_( "jpn_jpn.932" );
   else                                                        //more locales will be added later
      dstrLocale  = DEFAULT_LOCALE;
   i_setlocale( LC_ALL, dstrLocale.c_str() );

}

//******************************************************************************
HICON getUserIcon() {
   static HICON s_hUserIcon = NULL;
   static BFCritSec s_csUserIcon;
   if ( NULL != s_hUserIcon ) {
      return( s_hUserIcon );
   }

   DString strMarket = DSTCommonFunctions::getMarket();
   BFGuard g( s_csUserIcon );
   if ( NULL == s_hUserIcon ) {
      if ( strMarket == MARKET_IDS::LUXEMBOURG ) {
         s_hUserIcon = (HICON)AfxGetApp()->LoadIcon (IDR_MAINFRAME1);
      } else {
         // use 'Canada' Icon if we are not in Lux
         s_hUserIcon = (HICON)AfxGetApp()->LoadIcon (IDR_ROADTYPE);
      }
   }
   return s_hUserIcon;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MFDSTC.cpp-arc  $
 * 
 *    Rev 1.83   Jun 01 2012 15:53:06   dchatcha
 * IN#2952786 - Err Msg when keying Purchase Before Guarantee Adjustment- Trade Entry Screen, found during working on this issue that when client id and company id are difference user won't be able to see permission detail.
 * 
 *    Rev 1.82   May 11 2012 19:24:18   dchatcha
 * P0186479 FN10 - Gap 14G - Block Service Unit Transfers.
 * 
 *    Rev 1.81   Dec 22 2011 14:56:08   if991250
 * IA French resources/substitutions
 * 
 *    Rev 1.80   Dec 05 2011 09:00:52   purdyech
 * ControlTextRewriter Logic
 *
 *    Rev 1.79   Oct 27 2011 14:18:06   dchatcha
 * P0188150 FN01 & FN02 - IWT Enhancement, redirect environment default DSKURL to developer server in debug mode
 *
 *    Rev 1.78   Oct 11 2011 11:44:26   dchatcha
 * P0186484 FN01 - INA - Desktop Seg and Desktop French Enhancements, add language DLL switching support for domestic client.
 *
 *    Rev 1.77   Oct 06 2011 14:24:06   purdyech
 * IN2647659 Sync Up
 *
 *    Rev 1.76   Sep 16 2011 17:13:58   dchatcha
 * Usability Improvement on iFAST/Desktop
 *
 *    Rev 1.75   Jul 29 2011 11:28:02   dchatcha
 * Client name pane doens't show correctly. Found during working for GIA project.
 *
 *    Rev 1.74   Mar 15 2011 17:43:04   purdyech
 * RFC34278 - TA Exclusion List of Companies
 *
 *    Rev 1.73   Mar 15 2011 12:08:12   popescu
 * Incident 2463008 - removed the keyboard hook
 *
 *    Rev 1.72   Feb 16 2011 07:46:50   purdyech
 * IN2429143
 *
 * Fixed a problem where embedded spaces would break configuration file specification
 * Make command line arguments -s and -S act the same way (i.e. they both override the values found in the registry).
 *
 *    Rev 1.71   Dec 17 2010 06:03:02   purdyech
 * Improved logging for SSBG Performance analysis
 *
 *    Rev 1.70   Dec 02 2010 07:15:40   purdyech
 * Changes to implement view performance and crash-handling
 *
 *    Rev 1.69   Sep 13 2010 12:43:06   purdyech
 * Fixed bug in registry/config file interaction.
 *
 *    Rev 1.68   Jun 28 2010 10:55:28   purdyech
 * Improved Remote Support for AFT ZTS Migration
 *
 *    Rev 1.67   May 03 2010 04:46:58   purdyech
 * IN2107238 - Remove contention on usingSonicMQ().  Add support for IFAST_NUM_BATCH logic in Views
 *
 *    Rev 1.66   Feb 22 2010 08:53:18   purdyech
 * Added UseSCC (precautionary checkin for future development).  Will have no effect upon existing code.
 *
 *    Rev 1.65   Dec 22 2009 06:27:32   dchatcha
 * IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 *
 *    Rev 1.64   Oct 19 2009 08:27:24   purdyech
 * Single Connection registry code
 *
 *    Rev 1.63   Oct 06 2009 12:56:08   purdyech
 * Set GlobalIniPath as well as GlobalDataPath
 *
 *    Rev 1.62   Sep 23 2009 01:36:18   purdyech
 * Added support to override Support/DisplayConditionName.
 * This is a Rel96 feature, but adding it for Rel95 won't have any effect except to prevent us branching code, so I added it for Rel95.
 *
 *    Rev 1.61   Sep 23 2009 00:27:32   purdyech
 * Set GlobalDataPath based on the DataPath configured in the XML configuration file.  This is a work-around for the complicated way that we have implemented Registry objects here at IFDS.
 *
 *    Rev 1.60   Aug 27 2009 04:59:26   purdyech
 * Allow LDAPUserNS in ConfigFile
 *
 *    Rev 1.59   Aug 25 2009 07:58:12   purdyech
 * Added support for ConfigurationSelection dialog
 *
 *    Rev 1.58   Aug 23 2009 10:46:36   purdyech
 * Handle XML Parse errors
 *
 *    Rev 1.57   Aug 12 2009 07:14:56   purdyech
 * IN1794556 - Csi/Host, Csi/Type, and Csi/Param registry values are not overridable from Config.xml file
 *
 *    Rev 1.56   Aug 03 2009 23:17:54   purdyech
 * LDAP Integration Pieces
 *
 *    Rev 1.55   Aug 02 2009 22:05:22   yingz
 * new fields added for ldap
 *
 *    Rev 1.54   Jul 28 2009 09:15:48   purdyech
 * CR24095 - Performance Update to work around OpenEdge problem.
 *
 *    Rev 1.53   Jun 09 2009 11:41:24   purdyech
 * Removed overlay of InqQueue and UpdQueue to SingleQueue and MultiQueue due to problem with registry wipeout.
 *
 *    Rev 1.52   Jun 05 2009 08:49:30   purdyech
 * Fixed names of SonicSingle and SonicMulti queues in configuration.
 * SonicErrorMessages are now handled appropriately.
 *
 *    Rev 1.51   May 01 2009 09:28:20   purdyech
 * Added support for RTSHost/cswacl parameter
 *
 *    Rev 1.50   Mar 26 2009 09:26:26   purdyech
 * Sundry tweaks for ZTS - Rel 10
 *
 *    Rev 1.49   Mar 25 2009 07:28:34   purdyech
 * Added Support/DisplayConnectionIcon override
 *
 *    Rev 1.48   Mar 24 2009 10:29:18   purdyech
 * Changes for ZTS.  Release 9 for Phase II of POC
 *
 *    Rev 1.47   Feb 27 2009 08:50:38   purdyech
 * ZTS Fixes prior to User Experience Test
 *
 *    Rev 1.46   Feb 20 2009 14:57:42   purdyech
 * ZTS Revision 6
 *
 *    Rev 1.45   Feb 06 2009 14:55:54   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 *
 *    Rev 1.44   06 Dec 2007 15:20:28   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 *
 *    Rev 1.43   Nov 21 2007 07:37:32   purdyech
 * Added conditional support for exception processing.
 *
 *    Rev 1.42   Jun 24 2007 09:05:26   purdyech
 * Added AWD AutoLogon feature to desktop
 *
 *    Rev 1.41   May 14 2007 15:06:48   purdyech
 * PTS820423 - Added code to read Site.xml to override registry settings
 *
 *    Rev 1.40   Mar 14 2007 09:58:22   purdyech
 * Make the -m option work to load different registry options
 *
 *    Rev 1.39   Mar 06 2007 11:28:22   PURDYECH
 * Debug code control added for AFT performance tuning.
 *
 *    Rev 1.38   Nov 27 2006 11:23:04   fengyong
 * Incident #735041 - Add company code to configuration file
 *
 *    Rev 1.37   Oct 13 2006 14:40:34   fengyong
 * Sync up with web infra change
 *
 *    Rev 1.36   Sep 06 2006 14:13:14   fengyong
 * Give second option for reading configurastion file - read from path directory. file name hard code as "iFastGuiConfig.xml"
 *
 *    Rev 1.35   Aug 31 2006 10:47:22   fengyong
 * Add children iterator
 *
 *    Rev 1.34   Jun 08 2006 14:23:24   fengyong
 * Initialize webmapping by gui configuration
 *
 *    Rev 1.33   May 17 2006 13:36:10   fengyong
 * Add Gui XML configuration file
 *
 *    Rev 1.32   Oct 18 2005 19:10:08   popescu
 * Revert the previous changes
 *
 *    Rev 1.31   Sep 19 2005 14:28:12   ZHANGCEL
 * Correct the Icon for Canada market and Lux market
 *
 *    Rev 1.30   Aug 08 2005 11:30:52   popescu
 * Incident #374782 - if resources based on language cannot be found, load the English one, do not force it from the beginning.
 *
 *    Rev 1.29   Aug 08 2005 10:47:36   popescu
 * Incident #374782 - load only the 'ENG' resources, ignore the back-end language code
 *
 *    Rev 1.28   Dec 24 2004 11:59:16   purdyech
 * PTS1031333 - getUserIcon() function is now a global function which happens to reside in MFDSTC.cpp, instead of a member of MFDSTCApp
 *
 *    Rev 1.27   Dec 22 2004 16:55:32   zhangcel
 * PTS 10031333 -- Added a new function getUserIcon()
 *
 *    Rev 1.26   Nov 14 2004 15:00:46   purdyech
 * PET910 - .NET Conversion
 *
 *    Rev 1.25   Oct 21 2003 15:49:52   HSUCHIN
 * PTS 10023153 - added a message box warning when resources are not found.   Resources are defaulted to english language when language is not set by view.
 *
 *    Rev 1.24   Aug 21 2003 10:59:16   PURDYECH
 * Removed support for logger.hpp.
 *
 *    Rev 1.23   Jun 17 2003 16:06:36   SMITHDAV
 * Move CSI shutdown to dstcview.
 *
 *    Rev 1.22   Jun 09 2003 15:58:02   SMITHDAV
 * Changes related to Attachmate EXTRA integration
 *
 *    Rev 1.21   May 27 2003 14:58:44   PURDYECH
 * Disable server-style logging.
 *
 *    Rev 1.20   Dec 08 2002 21:58:28   HSUCHIN
 * added AfxInitRichEdit to enable rich edit control
 *
 *    Rev 1.19   Oct 09 2002 23:55:48   PURDYECH
 * PVCS Database Conversion
 *
 *    Rev 1.18   Sep 11 2002 08:50:44   PURDYECH
 * Reenable threads because the MT bug was found!
 *
 *    Rev 1.17   Sep 07 2002 13:30:14   PURDYECH
 * Disabled threading in release mode to remove a difficult-to-find bug which only manifests itself in release mode when threading is enabled.
 *
 *    Rev 1.16   Aug 29 2002 12:57:24   SMITHDAV
 * ClientLocale and typed field changes.
 *
 *    Rev 1.15   Jul 07 2002 12:05:52   PURDYECH
 * Allow threading again as the crash in the formatting has been resolved.
 *
 *    Rev 1.14   Jul 05 2002 11:49:42   PURDYECH
 * Infrastructure Fixup ... no more ICU!
 *
 *    Rev 1.13   Jul 05 2002 08:58:38   PURDYECH
 * Need a condition frame in CWinApp::Run to prevent a crash in infra code.  Overrode CMFDSTCApp::Run to put this in.
 *
 *    Rev 1.12   Jun 25 2002 09:38:08   PURDYECH
 * Default ClientLocale is now set at application level through the Market Registry setting
 *
 *    Rev 1.11   Dec 05 2001 14:29:08   ZHANGCEL
 * Deal with font problem
 *
 *    Rev 1.10   30 Nov 2001 10:43:54   HSUCHIN
 * more clean up and bug fix
 *
 *    Rev 1.9   29 Nov 2001 14:34:32   HSUCHIN
 * minor cleanup and removed getResourceDllName.  Changed the way the resource is loaded.
 *
 *    Rev 1.8   Sep 21 2001 16:13:58   YINGBAOL
 * fix memory leak
 *
 *    Rev 1.7   Aug 24 2001 14:01:04   HUANGSHA
 * Temp fix locale
 *
 *    Rev 1.6   30 Jul 2001 15:49:54   YINGZ
 * auto change of resources
 *
 *    Rev 1.5   Jul 27 2001 15:10:04   HUANGSHA
 * change
 *
 *    Rev 1.4   May 29 2001 11:44:36   HUANGSHA
 * Code Cleanup
 *
 *    Rev 1.3   Feb 12 2001 15:56:48   HSUCHIN
 * changed to call MFDSTCSetup::init on startup
 *
 *    Rev 1.2   Jan 29 2001 16:24:56   HUANGSHA
 * Create a Fixed font for edit box
 *
 *    Rev 1.1   Apr 13 2000 13:38:30   DT24433
 * added SingletonRegister::releaseSingletons
 *
 *    Rev 1.0   Feb 15 2000 11:01:20   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.5   04 Aug 1999 11:16:10   HUANGSHA
 * Same as MFDSTC.h
 *
 *    Rev 1.4   Jul 28 1999 12:03:38   BUZILA
 * moved gxall.h include at dialog level
 *
 *    Rev 1.3   Jul 27 1999 16:06:22   BUZILA
 * Increment M2
 *
 *    Rev 1.2   Jul 12 1999 17:31:02   PRAGERYA
 *
 *    Rev 1.1   Jul 08 1999 10:05:30   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
