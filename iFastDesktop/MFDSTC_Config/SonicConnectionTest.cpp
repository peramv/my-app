// SonicConnectionTest.cpp : implementation file
//

#include "stdafx.h"
#include "MFDSTC_Config.h"
#include "SonicConnectionTest.h"
#include ".\sonicconnectiontest.h"

static CString s_Testing = _T("Testing");
static CString s_Failed = _T("Failed");
static CString s_Passed = _T("Passed");

// CSonicConnectionTest dialog

IMPLEMENT_DYNAMIC(CSonicConnectionTest, CDialog)
CSonicConnectionTest::CSonicConnectionTest(SMQTest& smqTest, CWnd* pParent /*=NULL*/)
: CDialog(CSonicConnectionTest::IDD, pParent)
, smqTest_( smqTest )
{
}

CSonicConnectionTest::~CSonicConnectionTest()
{
}

void CSonicConnectionTest::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_STATUS_TELNET, ctlStatusTelnet_);
   DDX_Control(pDX, IDC_STATUS_CONNECT, ctlStatusConnect_);
   DDX_Control(pDX, IDC_STATUS_SINGLEQ, ctlStatusSingleQ_);
   DDX_Control(pDX, IDC_STATUS_MULTIQ, ctlStatusMultiQ_);
   DDX_Control(pDX, IDC_STATUS_AUTHQ, ctlStatusAuthQ_);
   DDX_Control(pDX, IDC_STATUS_AWDQ, ctlStatusAwdQ_);

   DDX_Control(pDX, IDC_ST_PRIMARY, ctlStPrimary_);
   DDX_Control(pDX, IDC_ST_CONNECT, ctlStConnect_);
   DDX_Control(pDX, IDC_ST_SINGLEQ, ctlStSingleQ_);
   DDX_Control(pDX, IDC_ST_MULTIQ, ctlStMultiQ_);
   DDX_Control(pDX, IDC_ST_AUTHQ, ctlStAuthQ_);
   DDX_Control(pDX, IDC_ST_AWDQ, ctlStAwdQ_);
   DDX_Control(pDX, IDC_PB_PRIMARY_TELNET, ctlPbPrimary_);
   DDX_Control(pDX, IDC_PB_CONNECT, ctlPbConnect_);
   DDX_Control(pDX, IDC_PB_SINGLEQ, ctlPbSingleQ_);
   DDX_Control(pDX, IDC_PB_MULTIQ, ctlPbMultiQ_);
   DDX_Control(pDX, IDC_PB_AUTHQ, ctlPbAuthQ_);
   DDX_Control(pDX, IDC_PB_AWDQ, ctlPbAwdQ_);
   DDX_Control(pDX, IDC_CONNECT_MESSAGE, ctlMessage_);
}


BEGIN_MESSAGE_MAP(CSonicConnectionTest, CDialog)
   ON_BN_CLICKED(IDC_PB_PRIMARY_TELNET, OnBnClickedPbTelnet)
   ON_BN_CLICKED(IDC_PB_CONNECT, OnBnClickedPbConnect)
   ON_BN_CLICKED(IDC_PB_SINGLEQ, OnBnClickedPbSingleq)
   ON_BN_CLICKED(IDC_PB_MULTIQ, OnBnClickedPbMultiq)
   ON_BN_CLICKED(IDC_PB_AUTHQ, OnBnClickedPbAuthq)
   ON_BN_CLICKED(IDC_PB_AWDQ, OnBnClickedPbAwdq)
   ON_STN_CLICKED(IDC_ST_PRIMARY, OnStnClickedStPrimary)
END_MESSAGE_MAP()


// CSonicConnectionTest message handlers

void CSonicConnectionTest::OnBnClickedPbTelnet()
{
   CString str;
   DString message;
   ctlPbPrimary_.SetWindowText( s_Testing );
   if( smqTest_.doTelnetTest( message ) ) {
      str.Format( _T("Connected in %s\r\n"), message.c_str() );
      ctlPbPrimary_.ShowWindow(FALSE);
      ctlStatusTelnet_.ShowWindow(TRUE);
      ctlStatusTelnet_.SetWindowText(s_Passed);
      ctlPbConnect_.EnableWindow(TRUE);
   }
   else {
      str.Format(_T("%s\r\n"), message.c_str() );
      ctlPbPrimary_.ShowWindow(FALSE);
      ctlStatusTelnet_.ShowWindow(TRUE);
      ctlStatusTelnet_.SetWindowText(s_Failed);
      ctlPbConnect_.EnableWindow(FALSE);
   }
   ctlMessage_.SetWindowText( str );
}

void CSonicConnectionTest::OnBnClickedPbConnect()
{
   DString message;
   CString str;
   ctlPbConnect_.SetWindowText( s_Testing );
   if( smqTest_.doConnectionTest( message ) ) {
      str.Format( _T("Connected to %s\r\n"), smqTest_.getBrokerURL().c_str() ); 
      ctlPbConnect_.ShowWindow(FALSE);
      ctlStatusConnect_.SetWindowText(s_Passed);
      ctlStatusConnect_.ShowWindow(TRUE);
      ctlPbConnect_.EnableWindow(FALSE);
      ctlPbSingleQ_.EnableWindow(TRUE);
      ctlPbMultiQ_.EnableWindow(TRUE);
      ctlPbAuthQ_.EnableWindow(TRUE);
      ctlPbAwdQ_.EnableWindow(TRUE);
   }
   else {
      str.Format( _T("%s\r\n"), message.c_str() );
      ctlPbConnect_.ShowWindow(FALSE);
      ctlStatusConnect_.SetWindowText(s_Failed);
      ctlStatusConnect_.ShowWindow(TRUE);
      ctlPbSingleQ_.EnableWindow(FALSE);
      ctlPbMultiQ_.EnableWindow(FALSE);
      ctlPbAuthQ_.EnableWindow(FALSE);
      ctlPbAwdQ_.EnableWindow(FALSE);
   }
   CString strMessage;
   ctlMessage_.GetWindowText( strMessage );
   strMessage += str;
   ctlMessage_.SetWindowText( strMessage );
}

void CSonicConnectionTest::OnBnClickedPbSingleq()
{
   CString str;
   DString message;
   ctlPbSingleQ_.SetWindowText( s_Testing );
   if( smqTest_.doSingleQTest( message ) ) {
      str.Format( _T("Connected to %s\r\n"), smqTest_.getSingleQ().c_str() );
      ctlPbSingleQ_.ShowWindow(FALSE);
      ctlStatusSingleQ_.SetWindowText( s_Passed );
      ctlStatusSingleQ_.ShowWindow(TRUE);
   }
   else {
      str.Format( _T("%s\r\n"), message.c_str() );
      ctlPbSingleQ_.ShowWindow(FALSE);
      ctlStatusSingleQ_.SetWindowText( s_Failed );
      ctlStatusSingleQ_.ShowWindow(TRUE);
   }
   CString strMessage;
   ctlMessage_.GetWindowText( strMessage );
   strMessage += str;
   ctlMessage_.SetWindowText( strMessage );
}

void CSonicConnectionTest::OnBnClickedPbMultiq()
{
   CString str;
   DString message;
   ctlPbMultiQ_.SetWindowText( s_Testing );
   if( smqTest_.doMultiQTest( message ) ) {
      str.Format( _T("Connected to %s\r\n"), smqTest_.getMultiQ().c_str() );
      ctlPbMultiQ_.ShowWindow(FALSE);
      ctlStatusMultiQ_.SetWindowText( s_Passed );
      ctlStatusMultiQ_.ShowWindow(TRUE);
   }
   else {
      str.Format( _T("%s\r\n"), message.c_str() );
      ctlPbMultiQ_.ShowWindow(FALSE);
      ctlStatusMultiQ_.SetWindowText( s_Failed );
      ctlStatusMultiQ_.ShowWindow(TRUE);
   }
   CString strMessage;
   ctlMessage_.GetWindowText( strMessage );
   strMessage += str;
   ctlMessage_.SetWindowText( strMessage );
}

void CSonicConnectionTest::OnBnClickedPbAuthq()
{
   CString str;
   DString message;
   ctlPbAuthQ_.SetWindowText( s_Testing );
   if( smqTest_.doAuthQTest( message ) ) {
      str.Format( _T("Connected to %s\r\n"), smqTest_.getAuthQ().c_str() );
      ctlPbAuthQ_.ShowWindow(FALSE);
      ctlStatusAuthQ_.SetWindowText( s_Passed );
      ctlStatusAuthQ_.ShowWindow(TRUE);
   }
   else {
      str.Format( _T("%s\r\n"), message.c_str() );
      ctlPbAuthQ_.ShowWindow(FALSE);
      ctlStatusAuthQ_.SetWindowText( s_Failed );
      ctlStatusAuthQ_.ShowWindow(TRUE);
   }
   CString strMessage;
   ctlMessage_.GetWindowText( strMessage );
   strMessage += str;
   ctlMessage_.SetWindowText( strMessage );
}

void CSonicConnectionTest::OnBnClickedPbAwdq()
{
   CString str;
   DString message;
   ctlPbAwdQ_.SetWindowText( s_Testing );
   if( smqTest_.doAwdQTest( message ) ) {
      str.Format( _T("Connected to %s\r\n"), smqTest_.getAwdQ().c_str() );
      ctlPbAwdQ_.ShowWindow(FALSE);
      ctlStatusAwdQ_.SetWindowText( s_Passed );
      ctlStatusAwdQ_.ShowWindow(TRUE);
   }
   else {
      str.Format( _T("%s\r\n"), message.c_str() );
      ctlPbAwdQ_.ShowWindow(FALSE);
      ctlStatusAwdQ_.SetWindowText( s_Failed );
      ctlStatusAwdQ_.ShowWindow(TRUE);
   }
   CString strMessage;
   ctlMessage_.GetWindowText( strMessage );
   strMessage += str;
   ctlMessage_.SetWindowText( strMessage );
}

void CSonicConnectionTest::OnBnClickedPbHeartbeat()
{
}

void CSonicConnectionTest::OnStnClickedStPrimary()
{
}

BOOL CSonicConnectionTest::OnInitDialog()
{
   CDialog::OnInitDialog();
   CString s;
   DString t;
   t = smqTest_.getSingleQ();
   s.Format( _T("Connect to %s"), t.c_str() );
   ctlStSingleQ_.SetWindowText( s );  
   t = smqTest_.getMultiQ();
   s.Format( _T("Connect to %s"), t.c_str() );
   ctlStMultiQ_.SetWindowText( s );  

   t = smqTest_.getAuthQ();
   s.Format( _T("Connect to %s"), t.c_str() );
   ctlStAuthQ_.SetWindowText( s );  
   t = smqTest_.getAwdQ();
   s.Format( _T("Connect to %s"), t.c_str() );
   ctlStAwdQ_.SetWindowText( s );  

   ctlPbPrimary_.EnableWindow(TRUE);
   ctlPbConnect_.EnableWindow(FALSE);
   ctlPbSingleQ_.EnableWindow(FALSE);
   ctlPbMultiQ_.EnableWindow(FALSE);
   ctlPbAuthQ_.EnableWindow(FALSE);
   ctlPbAwdQ_.EnableWindow(FALSE);
   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
