// AboutPropMgmtPage.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "AboutPropMgmtPage.h"
#include <ConfigManager.hpp>
#include <ifastgui/dstcview.h>
#include <ifastcbo/dstcusersession.hpp>
#include <ifastcbo/dstcglobalsession.hpp>
#include <ifastcbo/MgmtCo.hpp>
#include <ifastcbo/MgmtCoOptions.hpp>
#include <ifastbp/UserSessionProcessIncludes.h>
#include <dataimpl\dse_dstc0083_vw.hpp>
#include <dataimpl\dse_dstc0149_vw.hpp>
#include <dataimpl\dse_dstc0263_vw.hpp>
#include <dataimpl\dse_dstc0344_vw.hpp>


namespace {
   const unsigned long MAXBUFSIZE = 256;

   //Used in list control
   const I_CHAR *COL_HEADER1 = I_( "Option" );
   const I_CHAR *COL_HEADER2 = I_( "Value" );
}

//Macro used in ShowImports() function
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (addValue) )


// AboutPropMgmtPage dialog

IMPLEMENT_DYNAMIC(AboutPropMgmtPage, CPropertyPage)
AboutPropMgmtPage::AboutPropMgmtPage()
: CPropertyPage(AboutPropMgmtPage::IDD)
, pMgmtCo_(NULL)
{
   CDSTCView* pView = CDSTCView::GetView();
   if( NULL != pView ) {
      // get the UserSession
      try {
         GenericInterface* pGI = const_cast<GenericInterface*>(pView->getUserSession());
         if( NULL != pGI ) {
            DString dstrMgmtCo;
            pGI->getField( NULL, SYSTMGMTS, dstrMgmtCo );
            DSTCUserSession* pUserSession = dynamic_cast<DSTCUserSession *>(pGI->getBFSession());
            if( NULL != pUserSession ) {
               DSTCGlobalSession& gs = dynamic_cast<DSTCGlobalSession&>(pUserSession->getGlobalSession());
               gs.findMgmtCo( dstrMgmtCo, pMgmtCo_ );
               DString dstrCompanyId, dstrClientId, dstrCompanyName, dstrURL;
               pMgmtCo_->getField( ifds::CompanyId, dstrCompanyId, BF::HOST );
               m_strCompanyID = dstrCompanyId.c_str();
               pMgmtCo_->getField( ifds::ClientID, dstrClientId, BF::HOST );
               m_strClientID = dstrClientId.c_str();
               pMgmtCo_->getField( ifds::CompanyName, dstrCompanyName, BF::HOST );
               m_strName = dstrCompanyName.c_str();

               MgmtCoOptions* pOptions = NULL;
               pMgmtCo_->getMgmtCoOptions( pOptions );
               if( NULL != pOptions ) {
                  pOptions->getField( ifds::CompanyUrl, dstrURL, BF::HOST );
                  m_strURL = dstrURL.c_str();
               }
            }
         }
      } catch ( bad_cast ) {
      }
   }

}

AboutPropMgmtPage::~AboutPropMgmtPage()
{
}

void AboutPropMgmtPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text( pDX, IDC_ABOUT_MGMT_COMPANY_ID, m_strCompanyID);
    DDX_Text( pDX, IDC_ABOUT_MGMT_CLIENT_ID, m_strClientID );
    DDX_Text( pDX, IDC_ABOUT_MGMT_NAME, m_strName );
    DDX_Text( pDX, IDC_ABOUT_MGMT_URL, m_strURL );

   //{{AFX_DATA_MAP(AboutDetailsDlg)
   //}}AFX_DATA_MAP
}


bool AboutPropMgmtPage::hasMgmtCo() const {
   return( pMgmtCo_ != NULL );
}

void AboutPropMgmtPage::generateReport( std::wstringstream& ss )
{
   DString tempString = ConfigManager::getApplication();
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== Management Company ==============================") << std::endl;
   ss << I_("CompanyID  : ") << LPCTSTR(m_strCompanyID) << std::endl;
   ss << I_("ClientID   : ") << LPCTSTR(m_strClientID) << std::endl;
   ss << I_("CompanyName: ") << LPCTSTR(m_strName) << std::endl;
   ss << I_("WebURL     : ") << LPCTSTR(m_strURL) << std::endl;
   ss << std::endl;
}

BEGIN_MESSAGE_MAP(AboutPropMgmtPage, CPropertyPage)
END_MESSAGE_MAP()


// AboutPropMgmtPage message handlers
BOOL AboutPropMgmtPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

//   CWaitCursor waiter;

   return( TRUE );
}


