// MFDSTC_Config.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "MFDSTC_Config.h"
#include "MainFrm.h"
#include <xercesc\util\PlatformUtils.hpp>
#include <ifastcbo\version_app.hpp>

#include "MFDSTC_ConfigDoc.h"
#include "MFDSTC_ConfigView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool isTrue( const std::wstring& wstr ) {
   if( wstr == I_("1") ||
       wstr == I_("Y") ||
       wstr == I_("T") ) {
      return( true );
   }
   return( false );
}

const std::wstring& asBoolString( BOOL b ) {
   static const std::wstring& s_True( L"1" );
   static const std::wstring& s_False( L"0" );
   return( b ? s_True : s_False );
}




// CMFDSTC_ConfigApp

BEGIN_MESSAGE_MAP(CMFDSTC_ConfigApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CMFDSTC_ConfigApp construction

CMFDSTC_ConfigApp::CMFDSTC_ConfigApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFDSTC_ConfigApp object

CMFDSTC_ConfigApp theApp;

// CMFDSTC_ConfigApp initialization

BOOL CMFDSTC_ConfigApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
   xercesc::XMLPlatformUtils::Initialize();

   InitCommonControls();

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFDSTC_ConfigDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMFDSTC_ConfigView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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
public:
   CString vVersion_;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, vVersion_(_T(""))
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_VERSION_NUMBER, vVersion_);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CMFDSTC_ConfigApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
   aboutDlg.vVersion_ = ifds::getAppVersion().c_str();
	aboutDlg.DoModal();
}


// CMFDSTC_ConfigApp message handlers

