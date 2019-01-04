// SonicPage.cpp : implementation file
//

#include "stdafx.h"
#include "MFDSTC_Config.h"
#include "SonicPage.h"
#include <atlrx.h>
#include "MFDSTC_ConfigDoc.h"
#include "SonicConnectionTest.h"
#include ".\sonicpage.h"
#include <map>

static CString strEmpty(_T(""));

typedef std::map<CString, CString> PARTNER_MAP;
typedef PARTNER_MAP::iterator PARTNER_MAP_ITER;
static PARTNER_MAP* initPartnerMap() {
   static PARTNER_MAP partnerMap;
   partnerMap[CString(_T("msgdevpri"))] = CString(_T("msgdevsec"));
   partnerMap[CString(_T("msgdevsec"))] = CString(_T("msgdevpri"));

   partnerMap[CString(_T("msgeuu1.ifdsgroup.ca"))] = CString(_T("msgeuu2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgeuu2.ifdsgroup.ca"))] = CString(_T("msgeuu1.ifdsgroup.ca"));
   partnerMap[CString(_T("msgeuu4.ifdsgroup.ca"))] = CString(_T("msgeuu5.ifdsgroup.ca"));
   partnerMap[CString(_T("msgeuu5.ifdsgroup.ca"))] = CString(_T("msgeuu4.ifdsgroup.ca"));
   partnerMap[CString(_T("msgdeu1.ifdsgroup.ca"))] = CString(_T("msgdeu2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgdeu2.ifdsgroup.ca"))] = CString(_T("msgdeu1.ifdsgroup.ca"));
   partnerMap[CString(_T("msgcau1.ifdsgroup.ca"))] = CString(_T("msgcau2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgcau2.ifdsgroup.ca"))] = CString(_T("msgcau1.ifdsgroup.ca"));
   partnerMap[CString(_T("msgmifu1.ifdsgroup.ca"))] = CString(_T("msgmifu2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgmifu2.ifdsgroup.ca"))] = CString(_T("msgmifu1.ifdsgroup.ca"));
   partnerMap[CString(_T("msgaimu1.ifdsgroup.ca"))] = CString(_T("msgaimu2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgaimu2.ifdsgroup.ca"))] = CString(_T("msgaimu1.ifdsgroup.ca"));
   partnerMap[CString(_T("msgiau1.ifdsgroup.ca"))] = CString(_T("msgiau2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgiau2.ifdsgroup.ca"))] = CString(_T("msgiau1.ifdsgroup.ca"));

   partnerMap[CString(_T("msgeup1.ifdsgroup.ca"))] = CString(_T("msgeup2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgeup2.ifdsgroup.ca"))] = CString(_T("msgeup1.ifdsgroup.ca"));
   partnerMap[CString(_T("msgeup4.ifdsgroup.ca"))] = CString(_T("msgeup5.ifdsgroup.ca"));
   partnerMap[CString(_T("msgeup5.ifdsgroup.ca"))] = CString(_T("msgeup4.ifdsgroup.ca"));
   partnerMap[CString(_T("msgdep1.ifdsgroup.ca"))] = CString(_T("msgdep2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgdep2.ifdsgroup.ca"))] = CString(_T("msgdep1.ifdsgroup.ca"));
   partnerMap[CString(_T("msgcap1.ifdsgroup.ca"))] = CString(_T("msgcap2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgcap2.ifdsgroup.ca"))] = CString(_T("msgcap1.ifdsgroup.ca"));
   partnerMap[CString(_T("msgmifp4.ifdsgroup.ca"))] = CString(_T("msgmifp5.ifdsgroup.ca"));
   partnerMap[CString(_T("msgmifp5.ifdsgroup.ca"))] = CString(_T("msgmifp4.ifdsgroup.ca"));
   partnerMap[CString(_T("msgaimp4.ifdsgroup.ca"))] = CString(_T("msgaimp5.ifdsgroup.ca"));
   partnerMap[CString(_T("msgaimp5.ifdsgroup.ca"))] = CString(_T("msgaimp4.ifdsgroup.ca"));
   partnerMap[CString(_T("msgiap1.ifdsgroup.ca"))] = CString(_T("msgiap2.ifdsgroup.ca"));
   partnerMap[CString(_T("msgiap2.ifdsgroup.ca"))] = CString(_T("msgiap1.ifdsgroup.ca"));
   return( &partnerMap );
}
static PARTNER_MAP* s_pPartnerMap = initPartnerMap();

static const CString& getPartnerHost( const CString& str ) {
   PARTNER_MAP_ITER it = s_pPartnerMap->find( str );
   if( it != s_pPartnerMap->end() ) {
      return( (*it).second );
   }
   return( strEmpty );
}

static const CString& getPartnerHost( CComboBox& ctl ) {
   CString strHost;
   ctl.GetWindowText(strHost);
   return( getPartnerHost( strHost ) );
}

// CSonicPage dialog

IMPLEMENT_DYNAMIC(CSonicPage, CPropertyPage)
CSonicPage::CSonicPage()
	: CPropertyPage(CSonicPage::IDD)
   , BaseConfigPage(this)
   , vUseSonic_(_T(""))
   , vRecycleInterval_(_T(""))
   , vRTSHost_(_T(""))
   , vRTSPort_(_T(""))
   , vPrimaryProtocol_(_T(" "))
   , vPrimaryHost_(_T(""))
   , vPrimaryPort_(_T(""))
   , vBackupProtocol_(_T(" "))
   , vBackupHost_(_T(""))
   , vBackupPort_(_T(""))
   , vSingleQ_(_T(""))
   , vMultiQ_(_T(""))
   , vAuthQ_(_T(""))
   , vAwdQ_(_T(""))
   , vUserNS_(_T(""))
   , vSMQUser_(_T(""))
   , vSMQPassword_(_T(""))
   , vSMQTimeout_(_T(""))
   , vPersistentConnections_(FALSE)
   , vUseSingleConnection_(FALSE)
{
}

CSonicPage::~CSonicPage()
{
}

bool CSonicPage::isLocal() const {
   I_CHAR* pszEnv = NULL;
   pszEnv = i_getenv(I_("USERDOMAIN"));
   if( NULL != pszEnv &&
      !i_strcmp(pszEnv,I_("DSTCORFAX")) ) {
      return( true );
   }
   return( false );
}

void CSonicPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_CBString(pDX, IDC_TL_USE_SONIC, vUseSonic_);
   DDX_Text(pDX, IDC_TL_RECYCLE_INTERVAL, vRecycleInterval_);
   DDX_Text(pDX, IDC_TL_RTS_HOST, vRTSHost_);
   DDX_Text(pDX, IDC_TL_RTS_PORT, vRTSPort_);
   DDX_CBString(pDX, IDC_TL_ZTS_PRIMARY_PROTOCOL, vPrimaryProtocol_);
   DDX_CBString(pDX, IDC_TL_ZTS_PRIMARY_HOST, vPrimaryHost_);
   DDX_Text(pDX, IDC_TL_ZTS_PRIMARY_PORT, vPrimaryPort_);
   DDX_CBString(pDX, IDC_TL_ZTS_BACKUP_PROTOCOL, vBackupProtocol_);
   DDX_CBString(pDX, IDC_TL_ZTS_BACKUP_HOST, vBackupHost_);
   DDX_Text(pDX, IDC_TL_ZTS_BACKUP_PORT2, vBackupPort_);
   DDX_CBString(pDX, IDC_TL_SINGLEQIDC_TL_SINGLEQ, vSingleQ_);
   DDX_CBString(pDX, IDC_TL_MULTIQ, vMultiQ_);
   DDX_CBString(pDX, IDC_TL_AUTHQ, vAuthQ_);
   DDX_CBString(pDX, IDC_TL_AWDQ, vAwdQ_);
   DDX_CBString(pDX, IDC_TL_USERNS, vUserNS_);
   DDX_Text(pDX, IDC_TL_SMQUSER, vSMQUser_);
   DDX_Text(pDX, IDC_TL_SMQPASSWORD, vSMQPassword_);
   DDX_Text(pDX, IDC_TL_WAIT_TIMEOUT, vSMQTimeout_);
   DDX_Check(pDX, IDC_CHECK2, vPersistentConnections_);
   DDX_Check(pDX, IDC_TL_SINGLE_CONNECTION, vUseSingleConnection_);
   DDX_Control(pDX, IDC_TL_ZTS_PRIMARY_HOST, ctlPrimaryHost_);
   DDX_Control(pDX, IDC_TL_ZTS_BACKUP_HOST, ctlBackupHost_);
   DDX_Control(pDX, IDC_TL_SINGLEQ, ctlSingleQ_);
   DDX_Control(pDX, IDC_TL_MULTIQ, ctlMultiQ_);
   DDX_Control(pDX, IDC_TL_AUTHQ, ctlAuthQ_);
   DDX_Control(pDX, IDC_TL_AWDQ, ctlAwdQ_);
   DDX_Control(pDX, IDC_TL_USERNS, ctlUserNS_);
   DDX_Control(pDX, IDC_TL_RECYCLE_INTERVAL_SPIN, ctlRecycleSpin_);
   DDX_Control(pDX, IDC_TL_WAIT_TIMEOUT_SPIN, ctlWaitTimeoutSpin_);
   DDX_Control(pDX, IDC_TL_ZTS_PRIMARY_PORT, ctlPrimaryPort_);
   DDX_Control(pDX, IDC_TL_ZTS_BACKUP_PORT2, ctlBackupPort_);
   DDX_Control(pDX, IDC_TL_WAIT_TIMEOUT, ctlTimeout_);
   DDX_Control(pDX, IDC_TL_RECYCLE_INTERVAL, ctlRecycleInterval_);
   DDX_Control(pDX, IDC_TL_RTS_PORT, ctlRTSPort_);
   DDX_Control(pDX, IDC_TL_USE_SONIC, ctlUseSonic_);
   DDX_Control(pDX, IDC_SONIC_TEST, ctlSonicTest_);
   DDX_Control(pDX, IDC_RTS_TEST, ctlRTSTest_);
   DDX_Control(pDX, IDC_TL_ZTS_PRIMARY_PROTOCOL, ctlPrimaryProtocol_);
   DDX_Control(pDX, IDC_TL_ZTS_BACKUP_PROTOCOL, ctlBackupProtocol_);
}


BEGIN_MESSAGE_MAP(CSonicPage, CPropertyPage)
   ON_CBN_SELCHANGE(IDC_TL_USE_SONIC, OnCbnSelchangeTlUseSonic)
   ON_WM_VSCROLL()
   ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
   ON_EN_CHANGE(IDC_TL_RECYCLE_INTERVAL, OnEnChangeTlRecycleInterval)
   ON_EN_CHANGE(IDC_TL_RTS_HOST, OnEnChangeTlRtsHost)
   ON_EN_CHANGE(IDC_TL_RTS_PORT, OnEnChangeTlRtsPort)
   ON_CBN_SELCHANGE(IDC_TL_ZTS_PRIMARY_PROTOCOL, OnCbnSelchangeTlZtsPrimaryProtocol)
   ON_CBN_SELCHANGE(IDC_TL_ZTS_PRIMARY_HOST, OnCbnSelchangeTlZtsPrimaryHost)
   ON_EN_CHANGE(IDC_TL_ZTS_PRIMARY_PORT, OnEnChangeTlZtsPrimaryPort)
   ON_CBN_SELCHANGE(IDC_TL_ZTS_BACKUP_PROTOCOL, OnCbnSelchangeTlZtsBackupProtocol)
   ON_CBN_SELCHANGE(IDC_TL_ZTS_BACKUP_HOST, OnCbnSelchangeTlZtsBackupHost)
   ON_EN_CHANGE(IDC_TL_ZTS_BACKUP_PORT2, OnEnChangeTlZtsBackupPort2)
   ON_CBN_SELCHANGE(IDC_TL_SINGLEQ, OnCbnSelchangeTlSingleq)
   ON_CBN_SELCHANGE(IDC_TL_MULTIQ, OnCbnSelchangeTlMultiq)
   ON_CBN_SELCHANGE(IDC_TL_AUTHQ, OnCbnSelchangeTlAuthq)
   ON_CBN_SELCHANGE(IDC_TL_AWDQ, OnCbnSelchangeTlAwdq)
   ON_CBN_SELCHANGE(IDC_TL_USERNS, OnCbnSelchangeTlUserns)
   ON_EN_CHANGE(IDC_TL_SMQUSER, OnEnChangeTlSmquser)
   ON_EN_CHANGE(IDC_TL_SMQPASSWORD, OnEnChangeTlSmqpassword)
   ON_EN_CHANGE(IDC_TL_WAIT_TIMEOUT, OnEnChangeTlWaitTimeout)
   ON_CBN_EDITCHANGE(IDC_TL_SINGLEQ, OnCbnEditchangeTlSingleq)
   ON_CBN_EDITCHANGE(IDC_TL_MULTIQ, OnCbnEditchangeTlMultiq)
   ON_CBN_EDITCHANGE(IDC_TL_AUTHQ, OnCbnEditchangeTlAuthq)
   ON_CBN_EDITCHANGE(IDC_TL_AWDQ, OnCbnEditchangeTlAwdq)
   ON_CBN_EDITCHANGE(IDC_TL_ZTS_PRIMARY_HOST, OnCbnEditchangeTlZtsPrimaryHost)
   ON_CBN_EDITCHANGE(IDC_TL_ZTS_BACKUP_HOST, OnCbnEditchangeTlZtsBackupHost)
   ON_EN_KILLFOCUS(IDC_TL_ZTS_PRIMARY_PORT, OnEnKillfocusTlZtsPrimaryPort)
   ON_EN_KILLFOCUS(IDC_TL_ZTS_BACKUP_PORT2, OnEnKillfocusTlZtsBackupPort2)
   ON_EN_KILLFOCUS(IDC_TL_RECYCLE_INTERVAL, OnEnKillfocusTlRecycleInterval)
   ON_EN_KILLFOCUS(IDC_TL_WAIT_TIMEOUT, OnEnKillfocusTlWaitTimeout)
   ON_EN_KILLFOCUS(IDC_TL_RTS_PORT, OnEnKillfocusTlRtsPort)
   ON_CBN_KILLFOCUS(IDC_TL_ZTS_PRIMARY_HOST, OnCbnKillfocusTlZtsPrimaryHost)
   ON_BN_CLICKED(IDC_SONIC_TEST, OnBnClickedSonicTest)
   ON_BN_CLICKED(IDC_RTS_TEST, OnBnClickedRTSTest)
   ON_EN_SETFOCUS(IDC_TL_ZTS_BACKUP_PORT2, OnEnSetfocusTlZtsBackupPort2)
   ON_CBN_SETFOCUS(IDC_TL_ZTS_BACKUP_PROTOCOL, OnCbnSetfocusTlZtsBackupProtocol)
   ON_CBN_SETFOCUS(IDC_TL_ZTS_BACKUP_HOST, OnCbnSetfocusTlZtsBackupHost)
END_MESSAGE_MAP()


// CSonicPage message handlers

void CSonicPage::OnCbnSelchangeTlUseSonic()
{
   CString s;
   ctlUseSonic_.GetWindowText(s);
   if( s == _T("ZTS") ) {
      ctlSonicTest_.EnableWindow(TRUE);
      ctlRTSTest_.EnableWindow(FALSE);
   }
   else {
      ctlSonicTest_.EnableWindow(FALSE);
      ctlRTSTest_.EnableWindow(TRUE);
   }
}

void CSonicPage::UpdateFromDoc(LPARAM lHint)
{
   setChanged( lHint ? TRUE : FALSE);
   site::SiteConfig* pSiteConfig = getSiteConfig();
   if( !pSiteConfig ) {
      return;
   }
   std::wstring wstr;
   pSiteConfig->getTextForPath(I_("RTSHost/UseSonicMQ"), wstr);
   vUseSonic_ = isTrue(wstr) ? I_("ZTS") : I_("RTS");
   pSiteConfig->getTextForPath(I_("RTSHost/RTSHostIP"), wstr);
   vRTSHost_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/RTSHostPort"), wstr);
   vRTSPort_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/PersistentConnections"), wstr);
   vPersistentConnections_ = isTrue(wstr);
   wstr=I_("");
   pSiteConfig->getTextForPath(I_("RTSHost/UseSingleSonicConnection"), wstr);
   vUseSingleConnection_ = isTrue(wstr);
   wstr=I_("");
   pSiteConfig->getTextForPath(I_("RTSHost/RecycleInterval"), wstr);
   vRecycleInterval_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/SMQBrokerURLs"), wstr);
   CAtlRegExp<> reSingleUrl;
   CAtlRegExp<> reDoubleUrl;

   // three match groups: scheme, host, port
   REParseError status1 = reSingleUrl.Parse(_T("{[a-z]+}://{[A-Za-z0-9_\\.\\-]+}:{[0-9]+}") );
   REParseError status2 = reDoubleUrl.Parse(_T("{[a-z]+}://{[A-Za-z0-9_\\.\\-]+}:{[0-9]+},{[a-z]+}://{[A-Za-z0-9_\\.\\-]+}:{[0-9]+}") );
   if (REPARSE_ERROR_OK == status1 &&
       REPARSE_ERROR_OK == status2 ) {
      CAtlREMatchContext<> mcUrl;
      BOOL b = reDoubleUrl.Match(wstr.c_str(), &mcUrl);
      if( !b ) {
         b = reSingleUrl.Match(wstr.c_str(), &mcUrl);
      }
      if( b ) {
         std::wstring p;
         for (UINT nGroupIndex = 0; nGroupIndex < mcUrl.m_uNumGroups; ++nGroupIndex) {
            const CAtlREMatchContext<>::RECHAR* szStart = 0;
            const CAtlREMatchContext<>::RECHAR* szEnd = 0;
            mcUrl.GetMatch(nGroupIndex, &szStart, &szEnd);
            ptrdiff_t nLength = szEnd - szStart;
            p.assign( szStart, nLength);
            switch( nGroupIndex ) {
               case 0: vPrimaryProtocol_ = p.c_str(); break;
               case 1: vPrimaryHost_ = p.c_str(); break;
               case 2: vPrimaryPort_ = p.c_str(); break;
               case 3: vBackupProtocol_ = p.c_str(); break;
               case 4: vBackupHost_ = p.c_str(); break;
               case 5: vBackupPort_ = p.c_str(); break;
            }
         }
      }
      else {
         vPrimaryProtocol_ = _T(" ");
         vPrimaryHost_ = _T("");
         vPrimaryPort_ = _T("");
         vBackupProtocol_ = _T(" ");
         vBackupHost_ = _T("");
         vBackupPort_ = _T("");
      }
   }

   pSiteConfig->getTextForPath(I_("RTSHost/SMQSingleQueue"), wstr);
   if( wstr == I_("") ) {
      pSiteConfig->getTextForPath(I_("RTSHost/SMQInqQueue"), wstr);
   }
   vSingleQ_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/SMQMultiQueue"), wstr);
   if( wstr == I_("") ) {
      pSiteConfig->getTextForPath(I_("RTSHost/SMQUpdQueue"), wstr);
   }
   vMultiQ_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/SMQLDAPQueue"), wstr);
   vAuthQ_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/SMQAWDQueue"), wstr);
   vAwdQ_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/LDAPUserNS"), wstr);
   if( wstr == I_("") ) {
      pSiteConfig->getTextForPath(I_("RTSHost/UserNS"), wstr);
   }
   vUserNS_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/SMQUser"), wstr);
   vSMQUser_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/SMQPassword"), wstr);
   vSMQPassword_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("RTSHost/SMQWaitTimeout"), wstr);
   vSMQTimeout_ = wstr.c_str();
   if( GetSafeHwnd() != NULL ) {
      clearQueueLists();
      UpdateData(FALSE);
   }
}

void CSonicPage::OnUpdate(CView* pView, LPARAM lHint, CObject* pHint)
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

BOOL CSonicPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();
   ctlRecycleSpin_.SetRange(0,1000);
   ctlWaitTimeoutSpin_.SetRange(0,120);
   UINT nIndex = 0;
   if( isLocal() ) {
      ctlPrimaryHost_.InsertString(nIndex++, I_("msgdevpri"));
   }
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgcau1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgdeu1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgeuu4.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgeuu1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgiau1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgmifu1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgaimu1.ifdsgroup.ca"));

   ctlPrimaryHost_.InsertString(nIndex++, I_("msgcap1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgdep1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgeup4.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgeup1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgiap1.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgmifp4.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgaimp4.ifdsgroup.ca"));

   nIndex = 0;
   if( isLocal() ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgdevsec"));
   }
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgcau2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgdeu2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgeuu5.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgeuu2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgiau2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgmifu2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgaimu2.ifdsgroup.ca"));

   ctlPrimaryHost_.InsertString(nIndex++, I_("msgcap2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgdep2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgeup5.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgeup2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgiap2.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgmifp5.ifdsgroup.ca"));
   ctlPrimaryHost_.InsertString(nIndex++, I_("msgaimp5.ifdsgroup.ca"));

   nIndex = 0;
   ctlUserNS_.InsertString(nIndex++, I_("ifast.dev") );
   ctlUserNS_.InsertString(nIndex++, I_("ifast.qa") );
   ctlUserNS_.InsertString(nIndex++, I_("ifast.uat") );
   ctlUserNS_.InsertString(nIndex++, I_("ifast.prod") );
   UpdateFromDoc();

   return TRUE;  // return TRUE unless you set the focus to a control
}
site::SiteConfig* CSonicPage::getSiteConfig(void)
{
   CMFDSTC_ConfigDoc* pDoc = CMFDSTC_ConfigDoc::getDoc();
   if( NULL != pDoc ) {
      return( pDoc->pSiteConfig_ );
   }
   return NULL;
}


void CSonicPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (nSBCode == SB_ENDSCROLL)
		return;

	if (pScrollBar->GetDlgCtrlID() == IDC_TL_RECYCLE_INTERVAL_SPIN) {
		CString strValue;
		strValue.Format(_T("%4d"), (nPos * 5)); // or you required format
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strValue);
   }
	else if (pScrollBar->GetDlgCtrlID() == IDC_TL_WAIT_TIMEOUT_SPIN) {
		CString strValue;
		strValue.Format(_T("%3d"), (nPos * 5)); // or you required format
		((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowText(strValue);
   }
   CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CSonicPage::SaveToDoc(void)
{
   site::SiteConfig* pSiteConfig = getSiteConfig();

   if( !pSiteConfig  || !GetSafeHwnd()) {
      return FALSE;
   }

   // save screen variables to SiteConfig object
   UpdateData(TRUE);  // put into v*_ variables
   pSiteConfig->setTextForPath( I_("RTSHost/UseSonicMQ"), vUseSonic_ == I_("ZTS") ? I_("1") : I_("0") );
   vRTSHost_.Trim();
   pSiteConfig->setTextForPath( I_("RTSHost/RTSHostIP"), LPCTSTR(vRTSHost_) );
   vRTSPort_.Trim();
   pSiteConfig->setTextForPath( I_("RTSHost/RTSHostPort"), LPCTSTR(vRTSPort_) );
   CString strBrokerUrl = makeBrokerURL();
   strBrokerUrl.Trim();
   pSiteConfig->setTextForPath( I_("RTSHost/SMQBrokerURLs"), LPCTSTR(strBrokerUrl) );
   vSingleQ_.Trim();
   pSiteConfig->setTextForPath( I_("RTSHost/SMQSingleQueue"), LPCTSTR(vSingleQ_) );
   vMultiQ_.Trim();
   pSiteConfig->setTextForPath( I_("RTSHost/SMQMultiQueue"), LPCTSTR(vMultiQ_) );
   vAuthQ_.Trim();
   pSiteConfig->setTextForPath( I_("RTSHost/SMQLDAPQueue"), LPCTSTR(vAuthQ_) );
   vAwdQ_.Trim();
   pSiteConfig->setTextForPath( I_("RTSHost/SMQAWDQueue"), LPCTSTR(vAwdQ_) );
   vSMQUser_.Trim();
   pSiteConfig->setTextForPath( I_("RTSHost/SMQUser"), LPCTSTR(vSMQUser_) );
   pSiteConfig->setTextForPath( I_("RTSHost/SMQPassword"), LPCTSTR(vSMQPassword_) );
   pSiteConfig->setTextForPath( I_("RTSHost/LDAPUserNS"), LPCTSTR(vUserNS_) );
   pSiteConfig->setTextForPath( I_("RTSHost/SMQWaitTimeout"), LPCTSTR(vSMQTimeout_) );
   pSiteConfig->setTextForPath( I_("RTSHost/PersistentConnections"), asBoolString(vPersistentConnections_) );
   pSiteConfig->setTextForPath( I_("RTSHost/UseSingleSonicConnection"), asBoolString(vUseSingleConnection_) );
   pSiteConfig->setTextForPath( I_("RTSHost/RecycleInterval"), LPCTSTR(vRecycleInterval_) );

   return( TRUE );
}

CString CSonicPage::makeBrokerURL() {
   CString strBrokerUrl = _T("");
   CString strComma = _T("");
   if( vPrimaryHost_ != _T("") ) {
      strBrokerUrl += vPrimaryProtocol_;
      strBrokerUrl += _T("://");
      strBrokerUrl += vPrimaryHost_;
      strBrokerUrl += _T(":");
      strBrokerUrl += vPrimaryPort_;
      strComma = _T(",");
   }
   if( vBackupHost_ != _T("") ) {
      strBrokerUrl += strComma;
      strBrokerUrl += vBackupProtocol_;
      strBrokerUrl += _T("://");
      strBrokerUrl += vBackupHost_;
      strBrokerUrl += _T(":");
      strBrokerUrl += vBackupPort_;
   }
   return strBrokerUrl;
}

void CSonicPage::OnBnClickedCheck2()
{
   setChanged(TRUE);
}

void CSonicPage::OnEnChangeTlRecycleInterval()
{
   setChanged(TRUE);
}

void CSonicPage::OnEnChangeTlRtsHost()
{
   setChanged(TRUE);
}

void CSonicPage::OnEnChangeTlRtsPort()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlZtsPrimaryProtocol()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlZtsPrimaryHost()
{
   setChanged(TRUE);
   CString str;
	int iSel = ctlPrimaryHost_.GetCurSel();
   if( iSel != -1 ) {
      ctlPrimaryHost_.GetLBText(iSel,str);
   }
   setBackupHostList(str);
}

void CSonicPage::OnEnChangeTlZtsPrimaryPort()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlZtsBackupProtocol()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlZtsBackupHost()
{
   setChanged(TRUE);
}

void CSonicPage::OnEnChangeTlZtsBackupPort2()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlSingleq()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlMultiq()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlAuthq()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlAwdq()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnSelchangeTlUserns()
{
   setChanged(TRUE);
}

void CSonicPage::OnEnChangeTlSmquser()
{
   setChanged(TRUE);
}

void CSonicPage::OnEnChangeTlSmqpassword()
{
   setChanged(TRUE);
}

void CSonicPage::OnEnChangeTlWaitTimeout()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnEditchangeTlSingleq()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnEditchangeTlMultiq()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnEditchangeTlAuthq()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnEditchangeTlAwdq()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnEditchangeTlZtsPrimaryHost()
{
   setChanged(TRUE);
}

void CSonicPage::OnCbnEditchangeTlZtsBackupHost()
{
   setChanged(TRUE);
}

void ForceNumeric( CEdit& ctl ) {
   if( ctl.GetWindowTextLength() > 0 ) {
      CString str;
      ctl.GetWindowText(str);
      int v = _ttoi(str);
      str.Format(_T("%d"),v);
      ctl.SetWindowText(str);
   }
}

void CSonicPage::OnEnKillfocusTlZtsPrimaryPort()
{
   ForceNumeric( ctlPrimaryPort_ );
   setQueueNames();
}

void CSonicPage::OnEnKillfocusTlZtsBackupPort2()
{
   ForceNumeric( ctlBackupPort_ );
}

void CSonicPage::OnEnKillfocusTlRecycleInterval()
{
   ForceNumeric( ctlRecycleInterval_ );
}

void CSonicPage::OnEnKillfocusTlWaitTimeout()
{
   ForceNumeric( ctlTimeout_ );
}

void CSonicPage::OnEnKillfocusTlRtsPort()
{
   ForceNumeric( ctlRTSPort_ );
}

BOOL CSonicPage::ValidateData(void)
{
   UpdateData(TRUE);
   if( vUseSonic_ == _T("ZTS") ) {
      if( vPrimaryProtocol_ == _T(" ") ||
          vPrimaryHost_ == _T("") ||
          vPrimaryPort_ == _T("")  
      ) {
         AfxMessageBox( _T("Primary Broker URL needs protocol, host, and port."), MB_OK );
         return( FALSE );
      }
      if( !( vBackupProtocol_ == _T(" ") &&
            vBackupHost_ == _T("") &&
            vBackupPort_ == _T("") ) &&
         !( vBackupProtocol_ != _T(" ") &&
            vBackupHost_ != _T("") &&
            vBackupPort_ != _T("") ) 
      ) {
         AfxMessageBox( _T("Backup Broker URL needs protocol, host, and port."), MB_OK );
         return( FALSE );
      }
      if( vSingleQ_ == _T("") ) {
         AfxMessageBox( _T("Single Queue can't be blank"), MB_OK );
         return( FALSE );
      }
      if( vMultiQ_ == _T("") ) {
         AfxMessageBox( _T("Multi Queue can't be blank"), MB_OK );
         return( FALSE );
      }
      if( vAuthQ_ == _T("") ) {
         AfxMessageBox( _T("Auth Queue can't be blank"), MB_OK );
         return( FALSE );
      }
      if( vUserNS_ == _T("") ) {
         AfxMessageBox( _T("User Namespace can't be blank"), MB_OK );
         return( FALSE );
      }
      if( vSMQUser_ == _T("") ) {
         AfxMessageBox( _T("SMQ User can't be blank"), MB_OK );
         return( FALSE );
      }
      if( vSMQPassword_ == _T("") ) {
         AfxMessageBox( _T("SMQ Password can't be blank"), MB_OK );
         return( FALSE );
      }
   }
   else if( vUseSonic_ == _T("RTS") ) {
      if( vRTSHost_ == _T("") ) {
         AfxMessageBox( _T("RTS Host can't be blank"), MB_OK );
         return( FALSE );
      }
      if( vRTSPort_ == _T("") ) {
         AfxMessageBox( _T("RTS Port can't be blank"), MB_OK );
         return( FALSE );
      }
   }      
   return( TRUE );
}

void CSonicPage::OnCbnKillfocusTlZtsPrimaryHost()
{
   CString str;
   ctlPrimaryHost_.GetWindowText(str);
   setBackupHostList(str);
   setQueueNames();
}

void CSonicPage::setBackupHostList(const CString& str)
{
   // remove all hosts from 'Backup' Host list
   for( int i = ctlBackupHost_.GetCount()-1; i >= 0; --i ) {
      ctlBackupHost_.DeleteString( i );
   }
   UINT nIndex = 0;
   if( str == _T("msgdevpri") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgdevsec"));
   } else if( str == _T("msgcau1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgcau2.ifdsgroup.ca"));
   } else if( str == _T("msgdeu1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgdeu2.ifdsgroup.ca"));
   } else if( str == _T("msgeuu1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgeuu2.ifdsgroup.ca"));
   } else if( str == _T("msgeuu4.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgeuu5.ifdsgroup.ca"));
   } else if( str == _T("msgaimu1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgaimu2.ifdsgroup.ca"));
   } else if( str == _T("msgiau1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgiau2.ifdsgroup.ca"));
   } else if( str == _T("msgmifu1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgcmifu2.ifdsgroup.ca"));
   } else if( str == _T("msgcap1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgcap2.ifdsgroup.ca"));
   } else if( str == _T("msgdep1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgdep2.ifdsgroup.ca"));
   } else if( str == _T("msgeup1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgeup2.ifdsgroup.ca"));
   } else if( str == _T("msgeup4.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgeup5.ifdsgroup.ca"));
   } else if( str == _T("msgaimp4.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgaimp5.ifdsgroup.ca"));
   } else if( str == _T("msgiap1.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgiap2.ifdsgroup.ca"));
   } else if( str == _T("msgmifp4.ifdsgroup.ca") ) {
      ctlBackupHost_.InsertString(nIndex++, I_("msgmifp5.ifdsgroup.ca"));
   } else {
      if( isLocal() ) {
         ctlBackupHost_.InsertString(nIndex++, I_("msgdevsec"));
      }
      ctlBackupHost_.InsertString(nIndex++, I_("msgcau2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgdeu2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgeuu2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgeuu5.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgaimu2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgiau2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgmifu2.ifdsgroup.ca"));

      ctlBackupHost_.InsertString(nIndex++, I_("msgcap2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgdep2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgeup2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgeup5.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgaimp5.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgiap2.ifdsgroup.ca"));
      ctlBackupHost_.InsertString(nIndex++, I_("msgmifp5.ifdsgroup.ca"));
   }   
}
void CSonicPage::OnBnClickedSonicTest()
{
   UpdateData(TRUE);
   SMQTest smqTest;
   smqTest.setBrokerURL( LPCTSTR(makeBrokerURL()) );
   smqTest.setSMQUser( LPCTSTR(vSMQUser_) );
   smqTest.setSMQPassword( LPCTSTR(vSMQPassword_) );
   smqTest.setSingleQ( LPCTSTR(vSingleQ_) );
   smqTest.setMultiQ( LPCTSTR(vMultiQ_) );
   smqTest.setAuthQ( LPCTSTR(vAuthQ_) );
   smqTest.setAwdQ( LPCTSTR(vAwdQ_) );
   CSonicConnectionTest smqTestDlg( smqTest );
   smqTestDlg.DoModal();
}

void CSonicPage::OnBnClickedRTSTest()
{
   SetDlgItemText( IDC_TX_RTS_TEST, I_("") );   
   UpdateData(TRUE);
   SMQTest smqTest;
   DString dstrResult;
   smqTest.checkPort( LPCTSTR(vRTSHost_), _wtoi(vRTSPort_), dstrResult );
   SetDlgItemText( IDC_TX_RTS_TEST, dstrResult.c_str() );   
}

void CSonicPage::setQueueNames(void)
{
   CString strHost;
   ctlPrimaryHost_.GetWindowText(strHost);
   CString strPort;
   ctlPrimaryPort_.GetWindowText(strPort);
   if( strHost != _T("") ) {
      if( strHost == _T("msgdevpri") ) {
         if( strPort == _T("26112") ) { clearQueueLists(); addQueueList( _T("Online_Dev.") ); }
         else if( strPort == _T("26113") ) { clearQueueLists(); addQueueList( _T("Online_Dev_QA.") ); }
         else if( strPort == _T("26114") ) { clearQueueLists(); addQueueList( _T("Online_UAT.") ); }
         else if( strPort == _T("26115") ) { clearQueueLists(); addQueueList( _T("Online_Prod.") ); }
         else if( strPort == _T("26116") ) { clearQueueLists(); addQueueList( _T("Online_QA.") ); }
         else if( strPort == _T("26117") ) { clearQueueLists(); addQueueList( _T("Online_QA_UAT.") ); }
         else if( strPort == _T("26118") ) { clearQueueLists(); addQueueList( _T("Online_QA_Prod.") ); }
      }
      else if( strHost == _T("msgeup1.ifdsgroup.ca") ||
               strHost == _T("msgeuu1.ifdsgroup.ca") ) {
         if( strPort == _T("26130") ) { clearQueueLists(); addQueueList( _T("DTop_SSII.") ); }
         if( strPort == _T("26140") ) { clearQueueLists(); addQueueList( _T("DTop_SSBL.") ); }
      }
      else if( strHost == _T("msgdep1.ifdsgroup.ca") ||
               strHost == _T("msgdeu1.ifdsgroup.ca") ) {
         if( strPort == _T("26150") ) { clearQueueLists(); addQueueList( _T("DTop_SSBG.") ); }
      }
      else if( strHost == _T("msgaimp4.ifdsgroup.ca") ||
               strHost == _T("msgaimu1.ifdsgroup.ca") ) {
         if( strPort == _T("26160") ) { clearQueueLists(); addQueueList( _T("DTop_AIM.") ); }
      }
      else if( strHost == _T("msgcap1.ifdsgroup.ca") ||
               strHost == _T("msgcau1.ifdsgroup.ca") ) {
         if( strPort == _T("26170") ) { clearQueueLists(); addQueueList( _T("DTop_DOM.") ); }
         if( strPort == _T("26180") ) { clearQueueLists(); addQueueList( _T("DTop_DYN.") ); }
      }
      else if( strHost == _T("msgmifp4.ifdsgroup.ca") ||
               strHost == _T("msgmifu1.ifdsgroup.ca") ) {
         if( strPort == _T("26190") ) { clearQueueLists(); addQueueList( _T("DTop_MIF.") ); }
      }
      else if( strHost == _T("msgmifp4.ifdsgroup.ca") ||
               strHost == _T("msgmifu4.ifdsgroup.ca") ) {
         if( strPort == _T("26120") ) { clearQueueLists(); addQueueList( _T("DTop_IUK.") ); }
      }
      else if( strHost == _T("msgiap1.ifdsgroup.ca") ||
               strHost == _T("msgiau1.ifdsgroup.ca") ) {
         if( strPort == _T("26110") ) { clearQueueLists(); addQueueList( _T("DTop_INA.") ); }
      }
   }
}

void CSonicPage::clearQueueLists(void)
{
   for( int i = ctlSingleQ_.GetCount()-1; i >= 0; --i ) {
      ctlSingleQ_.DeleteString( i );
   }
   for( int i = ctlMultiQ_.GetCount()-1; i >= 0; --i ) {
      ctlMultiQ_.DeleteString( i );
   }
   for( int i = ctlAuthQ_.GetCount()-1; i >= 0; --i ) {
      ctlAuthQ_.DeleteString( i );
   }
   for( int i = ctlAwdQ_.GetCount()-1; i >= 0; --i ) {
      ctlAwdQ_.DeleteString( i );
   }
}

void CSonicPage::addQueueList(CString strPrefix)
{
   ctlSingleQ_.AddString( strPrefix + _T("ZTS.SingleRequest") );
   ctlMultiQ_.AddString( strPrefix + _T("ZTS.MultiRequest") );
   ctlAuthQ_.AddString( strPrefix + _T("ZTS.AuthRequest") );
   ctlAwdQ_.AddString( strPrefix + _T("ZTS.AwdIntRequest") );
}

void CSonicPage::OnEnSetfocusTlZtsBackupPort2()
{
   CString strProtocol;
   ctlBackupProtocol_.GetWindowText(strProtocol);
   CString strHost;
   ctlBackupHost_.GetWindowText(strHost);
   CString strPort;
   ctlBackupPort_.GetWindowText(strPort);
   strPort.Trim();
   if( strProtocol != _T("") && strHost != _T("") && strPort == _T("") ) {
      ctlPrimaryPort_.GetWindowText(strPort);
      ctlBackupPort_.SetWindowText(strPort);
   }
}

void CSonicPage::OnCbnSetfocusTlZtsBackupProtocol()
{
   CString strProtocol;
   ctlPrimaryProtocol_.GetWindowText(strProtocol);
   if( strProtocol != _T("") ) {
      CString strHost;
      ctlPrimaryHost_.GetWindowText(strHost);
      if( strHost != _T("ifmsg.ifdsgroup.ca") ) {
         ctlBackupProtocol_.SelectString(-1, strProtocol );
      }
   }
}

void CSonicPage::OnCbnSetfocusTlZtsBackupHost()
{
   CString strHost;
   ctlBackupHost_.GetWindowText(strHost);
   strHost.Trim();
   if( strHost == _T("") ) {
      strHost = getPartnerHost(ctlPrimaryHost_);
      ctlBackupHost_.SetWindowText(strHost);
   }
}

