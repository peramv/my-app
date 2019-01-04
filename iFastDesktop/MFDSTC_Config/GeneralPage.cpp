// GeneralPage.cpp : implementation file
//

#include "stdafx.h"
#include "MFDSTC_Config.h"
#include "MFDSTC_ConfigDoc.h"
#include "GeneralPage.h"
#include <ifastgui/SiteConfig.h>
#include ".\generalpage.h"


// CGeneralPage dialog

IMPLEMENT_DYNAMIC(CGeneralPage, CPropertyPage)
CGeneralPage::CGeneralPage()
	: CPropertyPage(CGeneralPage::IDD)
   , vMarket_(_T(""))
   , vAwdInterfaceDll_(_T(""))
   , vAwdAutoLogon_(FALSE)
   , vPath_(_T(""))
   , vFYIFile_(_T(""))
   , vRepository_(_T(""))
   , vDescription_(_T(""))
   , vLastChangedUser_(_T(""))
   , vLastChangedDate_(_T(""))
   , vCSIHost_(_T(""))
   , vCSIParam_(_T(""))
   , vCSIType_(_T(""))
{
}

CGeneralPage::~CGeneralPage()
{
}

void CGeneralPage::DoDataExchange(CDataExchange* pDX)
{
   CPropertyPage::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_MARKET, ctlMarket_);
   DDX_Control(pDX, IDC_AWD_INTERFACE_DLL, ctlAwdInterfaceDll_);
   DDX_CBString(pDX, IDC_MARKET, vMarket_);
   DDX_Text(pDX, IDC_AWD_INTERFACE_DLL, vAwdInterfaceDll_);
   DDX_Check(pDX, IDC_AWD_AUTOLOGON, vAwdAutoLogon_);
   DDX_Text(pDX, IDC_DATAPATH_PATH, vPath_);
   DDX_Text(pDX, IDC_DATAPATH_FYI, vFYIFile_);
   DDX_Text(pDX, IDC_DATAPATH_REPOSITORY, vRepository_);
   DDX_Text(pDX, IDC_XML_DESCRIPTION, vDescription_);
   DDX_Control(pDX, IDC_DATAPATH_PATH, ctlPath_);
   DDX_Control(pDX, IDC_DATAPATH_FYI, ctlFYIFile_);
   DDX_Control(pDX, IDC_DATAPATH_REPOSITORY, ctlRepository_);
   DDX_Text(pDX, IDC_LAST_CHANGED_BY, vLastChangedUser_);
   DDX_Text(pDX, IDC_LAST_CHANGED_DATE, vLastChangedDate_);
   DDX_Text(pDX, IDC_CSI_HOST, vCSIHost_);
   DDX_Text(pDX, IDC_CSI_TYPE, vCSIType_);
   DDX_Text(pDX, IDC_CSI_PARAM, vCSIParam_);
}


BEGIN_MESSAGE_MAP(CGeneralPage, CPropertyPage)
   ON_CBN_SELCHANGE(IDC_MARKET, OnCbnSelchangeMarket)
   ON_EN_CHANGE(IDC_XML_DESCRIPTION, OnEnChangeXmlDescription)
   ON_EN_CHANGE(IDC_AWD_INTERFACE_DLL, OnEnChangeAwdInterfaceDll)
   ON_BN_CLICKED(IDC_AWD_AUTOLOGON, OnBnClickedAwdAutologon)
   ON_EN_CHANGE(IDC_DATAPATH_PATH, OnEnChangeDatapathPath)
   ON_EN_CHANGE(IDC_DATAPATH_FYI, OnEnChangeDatapathFyi)
   ON_EN_CHANGE(IDC_DATAPATH_REPOSITORY, OnEnChangeDatapathRepository)
   ON_EN_KILLFOCUS(IDC_DATAPATH_PATH, OnEnKillfocusDatapathPath)
   ON_EN_CHANGE(IDC_LAST_CHANGED_BY, OnEnChangeLastChangedBy)
   ON_EN_CHANGE(IDC_CSI_HOST, OnEnChangeCsiHost)
   ON_EN_CHANGE(IDC_CSI_PARAM, OnEnChangeCsiParam)
   ON_EN_CHANGE(IDC_CSI_TYPE, OnEnChangeCsiType)
END_MESSAGE_MAP()


// CGeneralPage message handlers

void CGeneralPage::OnCbnSelchangeMarket()
{
   setChanged(TRUE);
}

BOOL CGeneralPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();
   UpdateFromDoc();

   return TRUE;  // return TRUE unless you set the focus to a control
}

void CGeneralPage::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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

void CGeneralPage::OnEnChangeXmlDescription()
{
   setChanged(TRUE);
}

void CGeneralPage::UpdateFromDoc(LPARAM lHint)
{
   setChanged( lHint ? TRUE : FALSE);
   site::SiteConfig* pSiteConfig = getSiteConfig();

   if( !pSiteConfig ) {
      return;
   }
   std::wstring wstr;
   pSiteConfig->getTextForPath(I_("Market/Market"), wstr);
   vMarket_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("Description"), wstr);
   vDescription_ = wstr.c_str();
   if( pSiteConfig->getElementForPath(I_("LastChanged/User") ) ) {
      pSiteConfig->getTextForPath(I_("LastChanged/User"), wstr);
      vLastChangedUser_ = wstr.c_str();
   }
   else {
      vLastChangedUser_ = _T("");
   }
   if( pSiteConfig->getElementForPath(I_("LastChanged/Date") ) ) {
      pSiteConfig->getTextForPath(I_("LastChanged/Date"), wstr);
      vLastChangedDate_ = wstr.c_str();
   }
   else {
      vLastChangedDate_ = _T("");
   }
   if( !pSiteConfig->getElementForPath( I_("AwdType/InterfaceDll") ) ) {
      vAwdInterfaceDll_ = I_("DIAWD23");
   }
   else {
      pSiteConfig->getTextForPath(I_("AwdType/InterfaceDll"), wstr);
      vAwdInterfaceDll_ = wstr.c_str();
   }
   if( !pSiteConfig->getElementForPath(I_("AwdType/AutoLogon") ) ) {
      vAwdAutoLogon_ = TRUE;
   }
   else {
      pSiteConfig->getTextForPath(I_("AwdType/AutoLogon"), wstr);
      vAwdAutoLogon_ = isTrue(wstr);
   }
   pSiteConfig->getTextForPath(I_("DataPath/Path"), wstr);
   vPath_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("DataPath/FYIfile"), wstr);
   vFYIFile_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("DataPath/RepositorySource"), wstr);
   vRepository_ = wstr.c_str();

   pSiteConfig->getTextForPath(I_("Csi/Host"), wstr);
   vCSIHost_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("Csi/Param"), wstr);
   vCSIParam_ = wstr.c_str();
   pSiteConfig->getTextForPath(I_("Csi/Type"), wstr);
   vCSIType_ = wstr.c_str();

   if( GetSafeHwnd() ) {
      UpdateData(FALSE);
   }
}

site::SiteConfig* CGeneralPage::getSiteConfig(void)
{
   CMFDSTC_ConfigDoc* pDoc = CMFDSTC_ConfigDoc::getDoc();
   if( NULL != pDoc ) {
      return( pDoc->pSiteConfig_ );
   }
   return NULL;
}

void CGeneralPage::OnEnChangeAwdInterfaceDll()
{
   setChanged(TRUE);
}

void CGeneralPage::OnBnClickedAwdAutologon()
{
   setChanged(TRUE);
}

void CGeneralPage::OnEnChangeDatapathPath()
{
   setChanged(TRUE);
}

void CGeneralPage::OnEnChangeDatapathFyi()
{
   setChanged(TRUE);
}

void CGeneralPage::OnEnChangeDatapathRepository()
{
   setChanged(TRUE);
}

BOOL CGeneralPage::SaveToDoc(void)
{
   site::SiteConfig* pSiteConfig = getSiteConfig();

   if( !pSiteConfig || !GetSafeHwnd()) {
      return FALSE;
   }

   // save screen variables to SiteConfig object
   UpdateData(TRUE);  // put into v*_ variables
   LPCTSTR pszEnv = _tgetenv(_T("USERNAME"));
   vLastChangedUser_ = pszEnv;

   time_t rawtime;
   struct tm* timeinfo;
   time(&rawtime);
   timeinfo = localtime(&rawtime);
   TCHAR szBuf[128];
   _tcsftime(szBuf, sizeof(szBuf)/sizeof(szBuf[0]), _T("%a %b %d, %Y at %H:%M:%S"), timeinfo );
   vLastChangedDate_ = szBuf;

   pSiteConfig->setTextForPath( I_("Description"), LPCTSTR(vDescription_) );
   pSiteConfig->setTextForPath( I_("Market/Market"), LPCTSTR(vMarket_) );
   pSiteConfig->setTextForPath( I_("LastChanged/User"), LPCTSTR(vLastChangedUser_) );
   pSiteConfig->setTextForPath( I_("LastChanged/Date"), LPCTSTR(vLastChangedDate_) );
   vPath_.Trim();
   pSiteConfig->setTextForPath( I_("DataPath/Path"), LPCTSTR(vPath_) );
   vFYIFile_.Trim();
   pSiteConfig->setTextForPath( I_("DataPath/FYIfile"), LPCTSTR(vFYIFile_) );
   vRepository_.Trim();
   pSiteConfig->setTextForPath( I_("DataPath/RepositorySource"), LPCTSTR(vRepository_) );
   vAwdInterfaceDll_.Trim();
   pSiteConfig->setTextForPath( I_("AwdType/InterfaceDll"), LPCTSTR(vAwdInterfaceDll_) );
   pSiteConfig->setTextForPath( I_("AwdType/AutoLogon"), asBoolString(vAwdAutoLogon_) );
   vCSIHost_.Trim();
   pSiteConfig->setTextForPath( I_("Csi/Host"), LPCTSTR(vCSIHost_) );
   vCSIParam_.Trim();
   pSiteConfig->setTextForPath( I_("Csi/Param"), LPCTSTR(vCSIParam_) );
   vCSIType_.Trim();
   pSiteConfig->setTextForPath( I_("Csi/Type"), LPCTSTR(vCSIType_) );

   return TRUE;
}

void CGeneralPage::OnEnKillfocusDatapathPath()
{
   if( ctlPath_.GetWindowTextLength() != 0 ) {
      CString strPath;
      ctlPath_.GetWindowText(strPath);

      if( ctlFYIFile_.GetWindowTextLength() == 0 ) {
         CString strFYIFile = strPath + _T("\\config\\fyi.htm");
         ctlFYIFile_.SetWindowText(strFYIFile);
      }
      if( ctlRepository_.GetWindowTextLength() == 0 ) {
         CString strRepo = strPath + _T("\\databroker.bin");
         ctlRepository_.SetWindowText(strRepo);
      }
   }
}

BOOL CGeneralPage::ValidateData(void)
{
   UpdateData(TRUE);
   if( vDescription_ == _T("") ) {
      AfxMessageBox( _T("Description can't be blank"), MB_OK );
      return( FALSE );
   }
   return( TRUE );
}

void CGeneralPage::OnEnChangeLastChangedBy()
{
}

void CGeneralPage::OnEnChangeCsiHost()
{
   setChanged(TRUE);
}

void CGeneralPage::OnEnChangeCsiParam()
{
   setChanged(TRUE);
}

void CGeneralPage::OnEnChangeCsiType()
{
   setChanged(TRUE);
}
