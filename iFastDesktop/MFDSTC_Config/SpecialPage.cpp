// SpecialPage.cpp : implementation file
//

#include "stdafx.h"
#include "MFDSTC_Config.h"
#include "SpecialPage.h"
#include "MFDSTC_ConfigDoc.h"
#include ".\specialpage.h"

// CSpecialPage dialog

IMPLEMENT_DYNAMIC(CSpecialPage, CPropertyPage)
CSpecialPage::CSpecialPage()
   : CPropertyPage(CSpecialPage::IDD)
   , vMMFPassword_(FALSE)
{
}

CSpecialPage::~CSpecialPage()
{
}

void CSpecialPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_SPEC_MMF, vMMFPassword_);
	DDX_Control(pDX, IDC_SPEC_MMF, ctlMMFPassword_);
}


BEGIN_MESSAGE_MAP(CSpecialPage, CPropertyPage)
	ON_BN_CLICKED(IDC_SPEC_MMF, OnBnClickedSpecMmf)
END_MESSAGE_MAP()


// CSpecialPage message handlers

BOOL CSpecialPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();
   UpdateFromDoc();

   return TRUE;  // return TRUE unless you set the focus to a control
}

void CSpecialPage::UpdateFromDoc(LPARAM lHint)
{
   setChanged( lHint ? TRUE : FALSE);
   site::SiteConfig* pSiteConfig = getSiteConfig();

   if( !pSiteConfig ) {
      return;
   }
   std::wstring wstr;
   pSiteConfig->getTextForPath(I_("Support/SpecialPasswordRules"), wstr);
   vMMFPassword_ = isTrue(wstr);


   if( GetSafeHwnd() ) {
      UpdateData(FALSE);
   }
}

site::SiteConfig* CSpecialPage::getSiteConfig(void)
{
   CMFDSTC_ConfigDoc* pDoc = CMFDSTC_ConfigDoc::getDoc();
   if( NULL != pDoc ) {
      return( pDoc->pSiteConfig_ );
   }
   return NULL;
}

void CSpecialPage::OnUpdate(CView* pView, LPARAM lHint, CObject* pHint)
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

BOOL CSpecialPage::SaveToDoc(void)
{
   site::SiteConfig* pSiteConfig = getSiteConfig();

   if( !pSiteConfig  || !GetSafeHwnd()) {
      return FALSE;
   }
   UpdateData(TRUE);
   pSiteConfig->setTextForPath( I_("Support/SpecialPasswordRules"), vMMFPassword_ ? I_("1") : I_("0") );

   return( TRUE );
}




void CSpecialPage::OnBnClickedSpecMmf()
{
   setChanged(TRUE);
}
