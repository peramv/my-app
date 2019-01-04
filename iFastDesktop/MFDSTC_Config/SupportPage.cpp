// SupportPage.cpp : implementation file
//

#include "stdafx.h"
#include "MFDSTC_Config.h"
#include "SupportPage.h"
#include "MFDSTC_ConfigDoc.h"
#include ".\supportpage.h"

// CSupportPage dialog

IMPLEMENT_DYNAMIC(CSupportPage, CPropertyPage)
CSupportPage::CSupportPage()
	: CPropertyPage(CSupportPage::IDD)
   , vLogEnable_(0)
   , vLogLevel_(0)
   , vLogPath_(_T(""))
   , vLogFile_(_T(""))
   , vViewLogEnable_(0)
   , vViewLogAppend_(FALSE)
   , vViewLogComplete_(FALSE)
   , vViewLogRawRequest_(FALSE)
   , vViewLogRawResponse_(FALSE)
   , vViewLogPath_(_T(""))
   , vViewTimeEnable_(0)
   , vViewTimePath_(_T(""))
   , vViewTimeSize_(_T(""))
   , vDisplayConnectionIcon_(FALSE)
   , vShowClientNamePane_(FALSE)
   , vDisplayConditionName_(FALSE)
   , vViewBatch_(_T(""))
   , vExceptionReportEnable_(0)
   , vExceptionReportPath_(_T(""))
{
}

CSupportPage::~CSupportPage()
{
}

void CSupportPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_SP_LOG_ENABLE, ctlLogEnable_);
   DDX_Check(pDX, IDC_SP_LOG_ENABLE, vLogEnable_);
   DDX_CBIndex(pDX, IDC_SP_LOG_LEVEL, vLogLevel_);
   DDX_Text(pDX, IDC_SP_LOG_PATH, vLogPath_);
   DDX_Text(pDX, IDC_SP_LOG_FILE, vLogFile_);
   DDX_Control(pDX, IDC_SP_VIEWLOG_ENABLE, ctlViewLogEnable_);
   DDX_Check(pDX, IDC_SP_VIEWLOG_ENABLE, vViewLogEnable_);
   DDX_Check(pDX, IDC_SP_VIEWLOG_APPEND, vViewLogAppend_);
   DDX_Check(pDX, IDC_SP_VIEWLOG_COMPLETE, vViewLogComplete_);
   DDX_Check(pDX, IDC_SP_VIEWLOG_RAWREQ, vViewLogRawRequest_);
   DDX_Check(pDX, IDC_SP_VIEWLOG_RAWREQ, vViewLogRawResponse_);
   DDX_Check(pDX, IDC_SP_VIEWTIME_ENABLE, vViewTimeEnable_);
   DDX_Text(pDX, IDC_SP_VIEWLOG_PATH, vViewLogPath_);
   DDX_Control(pDX, IDC_SP_VIEWTIME_ENABLE, ctlViewTimeEnable_);
   DDX_Text(pDX, IDC_SP_VIEWTIME_PATH, vViewTimePath_);
   DDX_Text(pDX, IDC_SP_VIEWTIME_SIZE, vViewTimeSize_);
   DDX_Check(pDX, IDC_SP_DISPLAYCONNECTIONICON, vDisplayConnectionIcon_);
   DDX_Control(pDX, IDC_SP_LOG_PATH, ctlLogPath_);
   DDX_Control(pDX, IDC_SP_LOG_LEVEL, ctlLogLevel_);
   DDX_Control(pDX, IDC_SP_LOG_FILE, ctlLogFile_);
   DDX_Control(pDX, IDC_SP_VIEWLOG_PATH, ctlViewLogPath_);
   DDX_Control(pDX, IDC_SP_VIEWLOG_APPEND, ctlViewLogAppend_);
   DDX_Control(pDX, IDC_SP_VIEWLOG_COMPLETE, ctlViewLogComplete_);
   DDX_Control(pDX, IDC_SP_VIEWLOG_RAWREQ, ctlViewLogRawRequest_);
   DDX_Control(pDX, IDC_SP_VIEWLOG_RAWRESP, ctlViewLogRawResponse_);
   DDX_Control(pDX, IDC_SP_VIEWTIME_PATH, ctlViewTimePath_);
   DDX_Control(pDX, IDC_SP_VIEWTIME_SIZE, ctlViewTimeSize_);
   OnBnClickedSpViewtimeEnable();
   OnBnClickedSpViewlogEnable();
   OnBnClickedSpLogEnable();
   DDX_Check(pDX, IDC_SP_SHOW_CLIENT_NAME_PANE, vShowClientNamePane_);
   DDX_Check(pDX, IDC_SP_DISPLAY_CONDITION_NAME, vDisplayConditionName_);

   DDX_Text(pDX, IDC_SP_VIEWBATCH, vViewBatch_);

   DDX_Control(pDX, IDC_SP_EXCEPTION_REPORT_PATH, ctlExceptionReportPath_);
   DDX_Check(pDX, IDC_SP_EXCEPTION_REPORT_ENABLE, vExceptionReportEnable_);
   DDX_Text(pDX, IDC_SP_EXCEPTION_REPORT_PATH, vExceptionReportPath_);
   DDX_Control(pDX, IDC_SP_EXCEPTION_REPORT_ENABLE, ctlExceptionReportEnable_);
   OnBnClickedSpExceptionReportEnable();
}


BEGIN_MESSAGE_MAP(CSupportPage, CPropertyPage)
   ON_BN_CLICKED(IDC_SP_VIEWTIME_ENABLE, OnBnClickedSpViewtimeEnable)
   ON_BN_CLICKED(IDC_SP_VIEWLOG_ENABLE, OnBnClickedSpViewlogEnable)
   ON_BN_CLICKED(IDC_SP_LOG_ENABLE, OnBnClickedSpLogEnable)
   ON_EN_CHANGE(IDC_SP_LOG_PATH, OnEnChangeSpLogPath)
   ON_CBN_SELCHANGE(IDC_SP_LOG_LEVEL, OnCbnSelchangeSpLogLevel)
   ON_EN_CHANGE(IDC_SP_LOG_FILE, OnEnChangeSpLogFile)
   ON_EN_CHANGE(IDC_SP_VIEWLOG_PATH, OnEnChangeSpViewlogPath)
   ON_BN_CLICKED(IDC_SP_VIEWLOG_APPEND, OnBnClickedSpViewlogAppend)
   ON_BN_CLICKED(IDC_SP_VIEWLOG_COMPLETE, OnBnClickedSpViewlogComplete)
   ON_BN_CLICKED(IDC_SP_VIEWLOG_RAWREQ, OnBnClickedSpViewlogRawreq)
   ON_BN_CLICKED(IDC_SP_VIEWLOG_RAWRESP, OnBnClickedSpViewlogRawresp)
   ON_EN_CHANGE(IDC_SP_VIEWTIME_PATH, OnEnChangeSpViewtimePath)
   ON_EN_CHANGE(IDC_SP_VIEWTIME_SIZE, OnEnChangeSpViewtimeSize)
   ON_BN_CLICKED(IDC_SP_DISPLAYCONNECTIONICON, OnBnClickedSpDisplayconnectionicon)
   ON_EN_KILLFOCUS(IDC_SP_VIEWTIME_SIZE, OnEnKillfocusSpViewtimeSize)
   ON_BN_CLICKED(IDC_SP_SHOW_CLIENT_NAME_PANE, OnBnClickedSpShowClientNamePane)
   ON_BN_CLICKED(IDC_SP_DISPLAY_CONDITION_NAME, OnBnClickedSpDisplayConditionName)
   ON_EN_CHANGE(IDC_SP_VIEWBATCH, OnEnChangeSpViewbatch)
   ON_BN_CLICKED(IDC_SP_EXCEPTION_REPORT_ENABLE, OnBnClickedSpExceptionReportEnable)
   ON_EN_CHANGE(IDC_SP_EXCEPTION_REPORT_PATH, OnEnChangeSpExceptionReportPath)
END_MESSAGE_MAP()


// CSupportPage message handlers

void CSupportPage::OnBnClickedSpViewtimeEnable()
{
   int b = ((ctlViewTimeEnable_.GetState() & 0x03) == 1);
   ctlViewTimePath_.EnableWindow(b);
   ctlViewTimeSize_.EnableWindow(b);
   setChanged(TRUE);
}

void CSupportPage::OnBnClickedSpViewlogEnable()
{
   int b = ((ctlViewLogEnable_.GetState() & 0x03) == 1);
   ctlViewLogPath_.EnableWindow(b);
   ctlViewLogAppend_.EnableWindow(b);
   ctlViewLogComplete_.EnableWindow(b);
   ctlViewLogRawRequest_.EnableWindow(b);
   ctlViewLogRawResponse_.EnableWindow(b);
   setChanged(TRUE);
}

void CSupportPage::OnBnClickedSpLogEnable()
{
   BOOL b = ((ctlLogEnable_.GetState() & 0x03) == 1);
   ctlLogPath_.EnableWindow(b);
   ctlLogFile_.EnableWindow(b);
   ctlLogLevel_.EnableWindow(b);
   setChanged(TRUE);
}

BOOL CSupportPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();
   UpdateFromDoc();

   return TRUE;  // return TRUE unless you set the focus to a control
}

void CSupportPage::UpdateFromDoc(LPARAM lHint)
{
   setChanged( lHint ? TRUE : FALSE);
   site::SiteConfig* pSiteConfig = getSiteConfig();

   if( !pSiteConfig ) {
      return;
   }
   std::wstring wstr;

   if( pSiteConfig->getElementForPath(I_("Support/Log_Enable")) ) {
      pSiteConfig->getTextForPath(I_("Support/Log_Enable"), wstr);
      vLogEnable_ = isTrue(wstr);
   }
   else {
      vLogEnable_ = 2;
   }
   pSiteConfig->getTextForPath(I_("Support/Log_File"), wstr);
   vLogFile_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("Support/Log_Path"), wstr);
   vLogPath_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("Support/Log_Level"), wstr);
   vLogLevel_ = DString(wstr.c_str()).asInteger();
   if( pSiteConfig->getElementForPath(I_("Support/ViewLog_Enable")) ) {
      pSiteConfig->getTextForPath(I_("Support/ViewLog_Enable"), wstr);
      vViewLogEnable_ = isTrue(wstr);
   }
   else {
      vViewLogEnable_ = 2;
   }
   pSiteConfig->getTextForPath(I_("Support/ViewLog_Path"), wstr);
   vViewLogPath_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("Support/ViewLog_Append"), wstr);
   vViewLogAppend_ = isTrue(wstr);
   pSiteConfig->getTextForPath(I_("Support/ViewLog_Complete"), wstr);
   vViewLogComplete_ = isTrue(wstr);
   pSiteConfig->getTextForPath(I_("Support/ViewLog_RawRequest"), wstr);
   vViewLogRawRequest_ = isTrue(wstr);
   pSiteConfig->getTextForPath(I_("Support/ViewLog_RawResponse"), wstr);
   vViewLogRawResponse_ = isTrue(wstr);
   if( pSiteConfig->getElementForPath(I_("Support/ViewTimeLog_Enable")) ) {
      pSiteConfig->getTextForPath(I_("Support/ViewTimeLog_Enable"), wstr);
      vViewTimeEnable_ = isTrue(wstr);
   }
   else {
      vViewTimeEnable_ = 2;
   }
   pSiteConfig->getTextForPath(I_("Support/ViewTimeLog_Path"), wstr);
   vViewTimePath_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("Support/ViewTimeLog_Size"), wstr);
   vViewTimeSize_ = wstr.c_str();

   if( pSiteConfig->getElementForPath(I_("Support/ExceptionReport_Enable")) ) {
      pSiteConfig->getTextForPath(I_("Support/ExceptionReport_Enable"), wstr);
      vExceptionReportEnable_ = isTrue(wstr);
   }
   else {
      vExceptionReportEnable_ = 2;
   }
   pSiteConfig->getTextForPath(I_("Support/ExceptionReport_Path"), wstr);
   vExceptionReportPath_ = wstr.c_str();

   pSiteConfig->getTextForPath(I_("Support/DisplayConnectionIcon"), wstr );
   vDisplayConnectionIcon_ = isTrue(wstr);
   pSiteConfig->getTextForPath(I_("Support/ShowClientNamePane"), wstr );
   vShowClientNamePane_ = isTrue(wstr);
   pSiteConfig->getTextForPath(I_("Support/DisplayConditionName"), wstr );
   vDisplayConditionName_ = isTrue(wstr);

   pSiteConfig->getTextForPath(I_("RTSHost/ViewBatch"), wstr );
   vViewBatch_ = wstr.c_str();

   if( GetSafeHwnd() ) {
      UpdateData(FALSE);
   }
}

site::SiteConfig* CSupportPage::getSiteConfig(void)
{
   CMFDSTC_ConfigDoc* pDoc = CMFDSTC_ConfigDoc::getDoc();
   if( NULL != pDoc ) {
      return( pDoc->pSiteConfig_ );
   }
   return NULL;
}

void CSupportPage::OnUpdate(CView* pView, LPARAM lHint, CObject* pHint)
{
   if( 0 == lHint ) {
      UpdateFromDoc();
   }
   else if ( 1 == lHint ) {
      SaveToDoc();
   }
   else if ( 2 == lHint ) {
      UpdateFromDoc(lHint);
   }
}

BOOL CSupportPage::SaveToDoc(void)
{
   site::SiteConfig* pSiteConfig = getSiteConfig();

   if( !pSiteConfig  || !GetSafeHwnd()) {
      return FALSE;
   }
   UpdateData(TRUE);
   if( (vLogEnable_ & 0x03) == 2 ) {
      // button is 'dimmed'
      // delete all Log_ keys, including LogEnable!
      pSiteConfig->removeElementForPath( _T("Support/Log_Enable") );
      pSiteConfig->removeElementForPath( _T("Support/Log_File") );
      pSiteConfig->removeElementForPath( _T("Support/Log_Path") );
      pSiteConfig->removeElementForPath( _T("Support/Log_Level") );
   }
   else {
      pSiteConfig->setTextForPath( _T("Support/Log_Enable"), asBoolString( (vLogEnable_ & 0x03)));
      pSiteConfig->setTextForPath( _T("Support/Log_File"), LPCTSTR(vLogFile_));
      pSiteConfig->setTextForPath( _T("Support/Log_Path"), LPCTSTR(vLogPath_));
      CString str;
      str.Format(_T("%d"), vLogLevel_);
      pSiteConfig->setTextForPath( _T("Support/Log_Level"), LPCTSTR(str) );
   }
   if( (vViewLogEnable_ & 0x03) == 2 ) {
      pSiteConfig->removeElementForPath( _T("Support/ViewLog_Enable") );
      pSiteConfig->removeElementForPath( _T("Support/ViewLog_Path") );
      pSiteConfig->removeElementForPath( _T("Support/ViewLog_Append") );
      pSiteConfig->removeElementForPath( _T("Support/ViewLog_Complete") );
      pSiteConfig->removeElementForPath( _T("Support/ViewLog_RawRequest") );
      pSiteConfig->removeElementForPath( _T("Support/ViewLog_RawResponse") );
      // get rid of all ViewLog_* values
   } 
   else {
      pSiteConfig->setTextForPath( _T("Support/ViewLog_Enable"), asBoolString( (vViewLogEnable_ & 0x03)));
      pSiteConfig->setTextForPath( _T("Support/ViewLog_Path"), LPCTSTR(vViewLogPath_));
      pSiteConfig->setTextForPath( _T("Support/ViewLog_Complete"), asBoolString(vViewLogComplete_));
      pSiteConfig->setTextForPath( _T("Support/ViewLog_Append"), asBoolString(vViewLogAppend_));
      pSiteConfig->setTextForPath( _T("Support/ViewLog_RawRequest"), asBoolString(vViewLogRawRequest_));
      pSiteConfig->setTextForPath( _T("Support/ViewLog_RawResponse"), asBoolString(vViewLogRawResponse_));
   }
   if( (vViewTimeEnable_ & 0x03) == 2 ) {
      // get rid of all ViewTime_* values
      pSiteConfig->removeElementForPath( _T("Support/ViewTimeLog_Enable") );
      pSiteConfig->removeElementForPath( _T("Support/ViewTimeLog_Path") );
      pSiteConfig->removeElementForPath( _T("Support/ViewTimeLog_Size") );
   } 
   else {
      pSiteConfig->setTextForPath( _T("Support/ViewTimeLog_Enable"), asBoolString( (vViewTimeEnable_ & 0x03)));
      pSiteConfig->setTextForPath( _T("Support/ViewTimeLog_Path"), LPCTSTR(vViewTimePath_) );
      pSiteConfig->setTextForPath( _T("Support/ViewTimeLog_Size"), LPCTSTR(vViewTimeSize_) );
   }

   if( (vExceptionReportEnable_ & 0x03) == 2 ) {
      // get rid of all ExceptionReport_* values
      pSiteConfig->removeElementForPath( _T("Support/ExceptionReport_Enable") );
      pSiteConfig->removeElementForPath( _T("Support/ExceptionReport_Path") );
   } 
   else {
      pSiteConfig->setTextForPath( _T("Support/ExceptionReport_Enable"), 
                                   asBoolString( (vExceptionReportEnable_ & 0x03)));
      pSiteConfig->setTextForPath( _T("Support/ExceptionReport_Path"), LPCTSTR(vExceptionReportPath_) );
   }

   pSiteConfig->setTextForPath( _T("Support/DisplayConnectionIcon"), asBoolString( vDisplayConnectionIcon_ ) );
   pSiteConfig->setTextForPath( _T("Support/ShowClientNamePane"), asBoolString( vShowClientNamePane_ ) );
   pSiteConfig->setTextForPath( _T("Support/DisplayConditionName"), asBoolString( vDisplayConditionName_ ) );
   pSiteConfig->setTextForPath( _T("RTSHost/ViewBatch"), LPCTSTR(vViewBatch_) );

   return( TRUE );
}

void CSupportPage::OnEnChangeSpLogPath()
{
   setChanged(TRUE);
}

void CSupportPage::OnCbnSelchangeSpLogLevel()
{
   setChanged(TRUE);
}

void CSupportPage::OnEnChangeSpLogFile()
{
   setChanged(TRUE);
}

void CSupportPage::OnEnChangeSpViewlogPath()
{
   setChanged(TRUE);
}

void CSupportPage::OnBnClickedSpViewlogAppend()
{
   setChanged(TRUE);
}

void CSupportPage::OnBnClickedSpViewlogComplete()
{
   setChanged(TRUE);
}

void CSupportPage::OnBnClickedSpViewlogRawreq()
{
   setChanged(TRUE);
}

void CSupportPage::OnBnClickedSpViewlogRawresp()
{
   setChanged(TRUE);
}

void CSupportPage::OnEnChangeSpViewtimePath()
{
   setChanged(TRUE);
}

void CSupportPage::OnEnChangeSpViewtimeSize()
{
   setChanged(TRUE);
}

void CSupportPage::OnBnClickedSpDisplayconnectionicon()
{
   setChanged(TRUE);
}

void CSupportPage::OnEnKillfocusSpViewtimeSize()
{
}

void CSupportPage::OnBnClickedSpShowClientNamePane()
{
   setChanged(TRUE);
}
void CSupportPage::OnBnClickedSpDisplayConditionName()
{
   setChanged(TRUE);
}

void CSupportPage::OnEnChangeSpViewbatch()
{
   setChanged(TRUE);
}

void CSupportPage::OnBnClickedSpExceptionReportEnable()
{
   BOOL b = ((ctlExceptionReportEnable_.GetState() & 0x03) == 1);
   ctlExceptionReportPath_.EnableWindow(b);
   setChanged(TRUE);
}

void CSupportPage::OnEnChangeSpExceptionReportPath()
{
   setChanged(TRUE);
}
