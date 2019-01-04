
// TransactionsMonitor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "TransactionsMonitor.h"
#include "MainFrm.h"
#include "DSTCCommandLineInfo.h"
#include <xercesc\util\PlatformUtils.hpp>
#include <xercesc\dom\DOMException.hpp>
#include <xercesc\sax\saxparseexception.hpp>
#include <ifastdbrkr.hpp>
#include <clientlocale.hpp>
#include <ConfigManager.hpp>
#include "SiteConfig.h"
#include "ConfigurationConstants.h"
#include <datapath.h>
#include "MFDSTCSetup.hpp"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTransactionsMonitorApp

BEGIN_MESSAGE_MAP(CTransactionsMonitorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTransactionsMonitorApp::OnAppAbout)
END_MESSAGE_MAP()


// CTransactionsMonitorApp construction

CTransactionsMonitorApp::CTransactionsMonitorApp()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("TransactionsMonitor.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CTransactionsMonitorApp object

CTransactionsMonitorApp theApp;


// CTransactionsMonitorApp initialization

BOOL CTransactionsMonitorApp::InitInstance()
{
	//CWinApp::InitInstance();
	//EnableTaskbarInteraction(FALSE);

	DSTCCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

   DString dstSiteXML = cmdInfo.getSiteXml();

   strUserName = cmdInfo.getUserName();
	strPassword = cmdInfo.getPassword();
	strClient = cmdInfo.getClient();

   if(dstSiteXML == I_("") || strUserName == I_("") || strPassword == I_("") || strClient == I_("") )
   {
      std::cout << "Usage TransactionsMonitor -S <config file> -u <user>  -p <password> -e <mgmt co>";
      AfxMessageBox(_T("Usage TransactionsMonitor -S <config file> -u <user>  -p <password> -e <mgmt co>"));
      //CWnd* pMainWindow = AfxGetMainWnd( );
      //if(pMainWindow)
      //   pMainWindow->DestroyWindow();
      PostQuitMessage(1);
      return FALSE;
   }

	xercesc::XMLPlatformUtils::Initialize();
	// Load configuration value overrides
	// IMPORTANT: This must be done as soon as possible once we know the Configuration Application Name.
	// Some of the code in the core classes will read values from the Configuration and cache them.  We need
	// to update the Configuration values before this happens.
	if ( cmdInfo.getSiteXml() != I_("") ) 
	{
		if( FALSE == SiteConfigInit( cmdInfo.getSiteXml(), cmdInfo.doesSiteXmlOverride() ) ) 
		{
			return( FALSE );
		}
	}

 //OBSOLETE 03Dec2011 - CP
 //Removed RTS support as a valid choice for iFAST/Desktop
 //  ifastdbrkr::setUsingSonicMQ( GetConfigValueAsBool( I_("RTSHost"), I_("UseSonicMQ") ) );

	ifastdbrkr::setMessageService( ifastdbrkr::MessageService::SonicMQ );


	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);


	MFDSTCSetup::init ( cmdInfo.directConnect() );

	//Hide splash screen
	//::PostMessage( HWND_BROADCAST, WM_KILLSPLASH, 0, 0 );

	// Make sure the sysload path is defined.
	ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
	Configuration cfgPath = pDSTCMgr->retrieveConfig( CONFIGURATION_CONSTANTS::DataPath );
	DString sysloadPath = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::SysloadPath );

	// If not, default it to the data path
	if ( sysloadPath.empty() ) 
	{
		sysloadPath = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::Path );
		ConfigValue cvSysloadPath( sysloadPath );
		cfgPath.set( CONFIGURATION_CONSTANTS::SysloadPath, cvSysloadPath );
		pDSTCMgr->storeConfig( cfgPath );

		ConfigManager *pCboMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::CBO );
		pCboMgr->storeConfig( cfgPath );
	}

	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_HIDE/*SW_SHOW*/);
	pFrame->UpdateWindow();


	pFrame->InitConnection();


	return TRUE;
}

int CTransactionsMonitorApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	return CWinApp::ExitInstance();
}

// CTransactionsMonitorApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CTransactionsMonitorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTransactionsMonitorApp message handlers



BOOL CTransactionsMonitorApp::SiteConfigInit( const DString& t, bool bOverrideRegistry ) 
{
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

   //((CTransactionsMonitorApp*)AfxGetApp())->LoadResourceDllByLanguageAndMarket( I_(""), I_("Canada"), dstrLang);

   site::SiteConfig* pSC = site::SiteConfig::getInstance();

   ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
   CT2CA pszConvertedAnsiString( dstrSiteXml.c_str());
   std::string SiteConfigFileName( pszConvertedAnsiString );

   DString q = GetConfigValueAsString( I_("RTSHost"), I_("SMQInqQueue") );

   bool bSelectedFromDlg = false;
   if ( SiteConfigFileName != "" ) {
      //try {
      //   ConfigSelectionDlg dlgSelect(SiteConfigFileName );
      //   switch( dlgSelect.getFileCount() ) {
      //      case 0:
      //         {
      //            char szBuf[4096];
      //            sprintf(szBuf, "No valid configuration file found based on %s.\nExiting application\n", SiteConfigFileName.c_str());
      //            MessageBoxA( HWND_DESKTOP, szBuf, "Error reading configuration", MB_OK );
      //            return(FALSE);
      //         }
      //      case 1:
      //         SiteConfigFileName = DStringA(dlgSelect.getFileName()).c_str();
      //         break;
      //      default:
      //         {
      //            if( IDCANCEL == dlgSelect.DoModal() ) {
      //               return(FALSE);
      //            }
      //            SiteConfigFileName = DStringA(dlgSelect.getFileName()).c_str();
      //            bSelectedFromDlg = true;
      //         }
      //   }

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

// OBSOLETE 03Dec2011 - CP
// RTS Support has been removed from iFAST/Desktop
//         pSC->setParm( I_("RTSHost"), I_("RTSHostPort"), I_("RTSHost"), site::DStringProperty( L"RTSHostPort" ), bOverrideRegistry );
//         pSC->setParm( I_("RTSHost"), I_("UseSonicMQ"), I_("RTSHost"), site::DStringProperty( L"UseSonicMQ" ), bOverrideRegistry );
//
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
         pSC->setParm( I_("RTSHost"), I_("SMQRTSDataFormat"), I_("RTSHost"), site::DStringProperty( L"SMQRTSDataFormat" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("UseSonicMQ"), I_("RTSHost"), site::DStringProperty( L"UseSonicMQ" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("UseSCC"), I_("RTSHost"), site::DStringProperty( L"UseSCC" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("LDAPUserNS"), I_("RTSHost"), site::DStringProperty( L"UserNS" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("LDAPUserNS"), I_("RTSHost"), site::DStringProperty( L"LDAPUserNS" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQLDAPQueue"), I_("RTSHost"), site::DStringProperty( L"SMQLDAPQueue" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("SMQAWDQueue"), I_("RTSHost"), site::DStringProperty( L"SMQAWDQueue" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("UseSingleSonicConnection"), I_("RTSHost"), site::DStringProperty( L"UseSingleSonicConnection" ), bOverrideRegistry );
         pSC->setParm( I_("RTSHost"), I_("ViewBatch"), I_("RTSHost"), site::DStringProperty( L"ViewBatch"), bOverrideRegistry );

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
      //} catch( const xercesc::SAXParseException& exc ) {
      //   I_CHAR szBuf[4096];
      //   i_sprintf(szBuf, I_("Error parsing configuration file %s\n\n%s\nLine %d, column %d\nSystemID=%s\nPublicID=%s\n"),
      //      dstrSiteXml.c_str(),
      //      exc.getMessage(),
      //      exc.getLineNumber(),
      //      exc.getColumnNumber(),
      //      exc.getSystemId(),
      //      exc.getPublicId() );
      //   // Error parsing the XML file
      //   // How do we signal this?  Simplest approach is a message box!
      //   // Format an error
      //   if( IDCANCEL == MessageBox( HWND_DESKTOP, szBuf, I_("Error reading configuration"), MB_OKCANCEL ) ) {
      //      return(FALSE);
      //   }
      //}
   }

   //if( GetConfigValueAsBool(I_("Support"), I_("ExceptionReport_Enable") ) ) {
   //   ExceptionReport::setLogFileDir(GetConfigValueAsString(I_("Support"), I_("ExceptionReport_Path") ) );
   //   ExceptionReport::enable(true);
   //}

   // We always use SonicMQ now.  RTS is no longer a valid value for iFAST/Desktop
   //ifastdbrkr::setMessageService( ifastdbrkr::MessageService::SonicMQ );

   //ifsupp::EnableControlTextRewriter( GetConfigValueAsString( I_("Support"), I_("ControlTextRewriter_Path") ) );

   return(TRUE);
}
