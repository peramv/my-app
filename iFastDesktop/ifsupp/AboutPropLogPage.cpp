// AboutPropRTSPage.cpp : implementation file
//

#include "stdafx.h"
#include "ifsupp.h"

//#include "cview.h"
#include "AboutPropLogPage.h"
#include <configmanager.hpp>
#include "ExceptionReport.hpp"
#include <bfdbrkr/bfviewtimelog.hpp>
#include <bf/log/log.hpp>
#include <bf/log/AbstractLogTarget.hpp>
#include <bfdbrkr/DbrkrLogger.hpp>
#include <../ifastgui/ifastlogfile.hpp>
#include <registryvalue.hpp>
#include <registrykey.hpp>
#include <ifsupp/ifsuppext.hpp>
#include ".\aboutproplogpage.h"
#include <ifastgui/MFDSTC.h>

static bool isLogTargetted()
{
   return( bf::log::theLog.hasTarget(I_("disk") ) );
}

static IFastLogFile* getLogTarget()
{
   if( isLogTargetted() ) {
      try {
         IFastLogFile* p = dynamic_cast<IFastLogFile*>(bf::log::theLog.getTarget(I_("disk")));
         return( p );
      } catch( std::bad_cast ) {}
   }
   return(NULL);
}

static bool getCurrentLogEnableState()
{
   bool bRc = false;
   const IFastLogFile* p = getLogTarget();
   if( NULL != p ) {
      bool b = p->isSuspended();
      bRc = !b;
   }
   return( bRc );
}

// AboutPropLogPage dialog

IMPLEMENT_DYNAMIC(AboutPropLogPage, CPropertyPage)
AboutPropLogPage::AboutPropLogPage()
    : CPropertyPage(AboutPropLogPage::IDD)
{
   const IFastLogFile* p = getLogTarget();
   if( NULL != p ) {
      m_strLogFile = p->getFileName().c_str();
      m_strLogPath = p->getPathName().c_str();
      m_bLogEnable = getCurrentLogEnableState();
      m_iLogLevel = bf::log::theLog.getReportingThreshold();
   }

   m_strViewLogPath = DbrkrLogger::getLogDir().c_str();
   m_bViewLogEnable = DbrkrLogger::isEnabled();
   m_bViewLogAppend = DbrkrLogger::isAppending();
   m_bViewLogComplete = DbrkrLogger::isCompleteLogging();
   m_bViewLogRequest = DbrkrLogger::logRequest();
   m_bViewLogResponse = DbrkrLogger::logResponse();

   BFViewTimeLog& viewTimeLog = BFViewTimeLog::getInstance();
   m_bViewTimingEnable = viewTimeLog.isEnabled();
   m_strViewTimingPath = viewTimeLog.getPath().c_str();

   m_strExceptionPath = ExceptionReport::getLogFileDir();
   m_bExceptionEnable = ExceptionReport::isEnabled();

   RegistryKey rkOption( "SOFTWARE\\DST\\Debug" );
   RegistryValue rvDisplay = rkOption.getValue( "DisplayBeforeThrowLevel" );
   m_bDisplayConditionName = GetConfigValueAsBool(I_("Support"), I_("DisplayConditionName") );
   m_bDisplayClientNamePane = GetConfigValueAsBool(I_("Support"), I_("ShowClientNamePane") );

   m_bDesktopWebURL = ConfigManager::GetSaveDesktopWebURL();
}

AboutPropLogPage::~AboutPropLogPage()
{
}

void AboutPropLogPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control( pDX, IDC_LOG_ENABLE, m_btnLogEnable );
   DDX_Control( pDX, IDC_LOG_PATH, m_wndLogPath );
   DDX_Control( pDX, IDC_LOG_FILE, m_wndLogFile );
   DDX_Control( pDX, IDC_LOG_LEVEL, m_wndLogLevel );
   DDX_Text( pDX, IDC_LOG_FILE, m_strLogFile );
   DDX_Text( pDX, IDC_LOG_PATH, m_strLogPath );
   DDX_Check( pDX, IDC_LOG_ENABLE, m_bLogEnable );
   DDX_CBIndex( pDX, IDC_LOG_LEVEL, m_iLogLevel );
   DDX_Text( pDX, IDC_LOG_VIEWLOG_PATH2, m_strViewLogPath );
   DDX_Check( pDX, IDC_LOG_VIEWLOG_ENABLE, m_bViewLogEnable );
   DDX_Check( pDX, IDC_LOG_VIEWLOG_APPEND, m_bViewLogAppend );
   DDX_Check( pDX, IDC_LOG_VIEWLOG_COMPLETE, m_bViewLogComplete );
   DDX_Check( pDX, IDC_LOG_VIEWLOG_REQUEST, m_bViewLogRequest );
   DDX_Check( pDX, IDC_LOG_VIEWLOG_RESPONSE, m_bViewLogResponse );
   DDX_Text( pDX, IDC_LOG_VIEWTIME_PATH, m_strViewTimingPath );
   DDX_Check( pDX, IDC_LOG_VIEWTIME_ENABLE, m_bViewTimingEnable );
   DDX_Text( pDX, IDC_LOG_EXCEPTION_PATH, m_strExceptionPath );
   DDX_Check( pDX, IDC_LOG_EXCEPTION_ENABLE, m_bExceptionEnable );
   DDX_Check( pDX, IDC_LOG_DISPLAY_CONDITION_NAME, m_bDisplayConditionName );
   DDX_Check( pDX, IDC_LOG_DISPLAY_CLIENT_NAME_PANE, m_bDisplayClientNamePane );
   DDX_Control( pDX, IDC_CHECK_DESKTOP_WEB_URL, m_checkBoxSaveDesktopWebURL );
}

void AboutPropLogPage::OnOK()
{
   CPropertyPage::OnOK();

   IFastLogFile* p = getLogTarget();
   if( NULL != p ) {
      bool bRestart = false;
      if( getCurrentLogEnableState() != ( TRUE == m_bLogEnable ) ) {
         if( m_bLogEnable ) {
            bRestart = true;
         }
         else {
            bf::log::theLog.suspendTarget( I_("disk") );
         }
      }
      if( m_iLogLevel != bf::log::theLog.getReportingThreshold() ) {
         bf::log::theLog.setReportingThreshold( (bf::log::LogStream::Level)m_iLogLevel );
      }
      if( m_strLogFile != p->getFileName().c_str() ||
          m_strLogPath != p->getPathName().c_str() ) {
         p->setFilePath( LPCTSTR(m_strLogPath), LPCTSTR(m_strLogFile) );
         bRestart = true;
      }
      if( bRestart ) {
         p->restart();
      }
   }

   DbrkrLogger::setAppending( TRUE == m_bViewLogAppend );
   DbrkrLogger::setCompleteLogging( TRUE == m_bViewLogComplete );
   DbrkrLogger::setLogDir( LPCTSTR(m_strViewLogPath) );
   DbrkrLogger::enable( TRUE == m_bViewLogEnable );
   DbrkrLogger::setLogRequest( TRUE == m_bViewLogRequest );
   DbrkrLogger::setLogResponse( TRUE == m_bViewLogResponse );

   BFViewTimeLog& viewTimeLog = BFViewTimeLog::getInstance();
   viewTimeLog.enable( TRUE == m_bViewTimingEnable );
   if( m_strViewTimingPath.GetLength() > 0 &&
       m_strViewTimingPath.Right(1) != "\\" ) {
      m_strViewTimingPath += "\\";
   }
   viewTimeLog.setPath( DString( m_strViewTimingPath ) );

   ExceptionReport::setLogFileDir( DString( m_strExceptionPath ) );
   ExceptionReport::enable( TRUE == m_bExceptionEnable );

/*
   ** These two statements will overwrite the user's registry with the currently cached contents
   ** This is a bad thing.  Need to rewrite configmanager to have a way of locally saving config
   ** values, but not persist them to disk - CP 16Feb2011

   WriteConfigValue( I_("MFDSTC"),
                     I_("Support"),
                     I_("DisplayConditionName"),
                     m_bDisplayConditionName ? I_("YES") : I_("NO") );

   WriteConfigValue( I_("MFDSTC"),
                     I_("Support"),
                     I_("ShowClientNamePane"),
                     m_bDisplayClientNamePane ? I_("YES") : I_("NO") );
*/
   // do post message to main window of application that
   // there is change registry which effect to status bar!
   POSITION posDocTemplate = (AfxGetApp())->GetFirstDocTemplatePosition();
   CDocTemplate* pDocTemplate = (AfxGetApp())->GetNextDocTemplate(posDocTemplate);
   POSITION posDoc = pDocTemplate->GetFirstDocPosition();
   CDocument* pDoc = pDocTemplate->GetNextDoc(posDoc);
   POSITION posView = pDoc->GetFirstViewPosition();
   CFormView* pView = (CFormView*)pDoc->GetNextView(posView);

   ifsupp::PFNKICKSTATUSBAR pfn = NULL;
   ifsupp::GetStatusBarKicker(pfn);
   if( NULL != pfn ) {
      (*pfn)();
   }
}

void AboutPropLogPage::generateReport( std::wstringstream& ss )
{
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== Logging Information =============================") << std::endl;
   ss << I_("Logging enabled: ") << ( m_bLogEnable ? I_("Yes") : I_("No") ) << std::endl;
   if( m_bLogEnable ) {
      ss << I_("Log Path: ") << LPCTSTR(m_strLogPath) << std::endl;
      ss << I_("Log File: ") << LPCTSTR(m_strLogFile) << std::endl;
   }
   if( m_bViewLogEnable ) {
      ss << I_("View Log Path: ") << LPCTSTR(m_strViewLogPath) << std::endl;
      ss << I_("View Log Append:   ") << ( m_bViewLogAppend ? "Yes" : "No" ) << std::endl;
      ss << I_("View Log Complete: ") << ( m_bViewLogComplete ? "Yes" : "No" ) << std::endl;
      ss << I_("View Log Request:  ") << ( m_bViewLogRequest ? "Yes" : "No" ) << std::endl;
      ss << I_("View Log Response: ") << ( m_bViewLogResponse ? "Yes" : "No" ) << std::endl;
   }
   if( m_bViewTimingEnable ) {
      ss << I_("View Timing Log Path: ") << LPCTSTR(m_strViewTimingPath) << std::endl;
   }
   if( m_bExceptionEnable ) {
      ss << I_("Exception Log: ") << LPCTSTR(m_strExceptionPath) << std::endl;
   }
   ss << std::endl;

}

BEGIN_MESSAGE_MAP(AboutPropLogPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_DESKTOP_WEB_URL, OnBnClickedCheckDesktopWebUrl)
END_MESSAGE_MAP()


// AboutPropLogPage message handlers

// AboutPropSonicPage message handlers
BOOL AboutPropLogPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   // If there is no Disk log target then don't even enable the button
   if( getLogTarget() == NULL ) {
      m_btnLogEnable.EnableWindow( FALSE );
      m_wndLogFile.SetReadOnly(TRUE);
      m_wndLogPath.SetReadOnly(TRUE);
      m_wndLogLevel.EnableWindow( FALSE );
   }
   else {
      m_btnLogEnable.EnableWindow( TRUE );
      m_wndLogFile.SetReadOnly(FALSE);
      m_wndLogPath.SetReadOnly(FALSE);
      m_wndLogLevel.EnableWindow( TRUE );
   }

   m_checkBoxSaveDesktopWebURL.SetCheck(m_bDesktopWebURL);

   return( TRUE );
}

void AboutPropLogPage::OnBnClickedCheckDesktopWebUrl()
{
	if (BST_CHECKED == m_checkBoxSaveDesktopWebURL.GetCheck())
	{
		ConfigManager::SetSaveDesktopWebURL(TRUE);
	}
	else
	{
		ConfigManager::SetSaveDesktopWebURL(FALSE);
	}
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifsupp/AboutPropLogPage.cpp-arc  $
// 
//    Rev 1.0   Dec 05 2011 09:03:40   purdyech
// Initial revision.
//
//    Rev 1.8   Feb 16 2011 07:58:58   purdyech
// IN2429143
//
// Diagnostic page can mess with Registry.
//
//    Rev 1.7   Dec 03 2010 07:54:34   purdyech
// Changes to implement view performance tracking and crash handling
//
//    Rev 1.6   Dec 02 2010 07:15:08   purdyech
// Changes to implement view performance and crash-handling
//
//    Rev 1.5   Dec 22 2009 06:36:08   dchatcha
// IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 *
 */
