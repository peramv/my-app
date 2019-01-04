// AboutPropMgmtPage.cpp : implementation file
//

#include "stdafx.h"
#include "ifsupp.h"
#include "ifsuppext.hpp"

#include "AboutPropMgmtPage.h"
#include <ConfigManager.hpp>
////#include <ifastgui/dstcview.h>
#include <ifastcbo/dstcusersession.hpp>
#include <ifastcbo/dstcglobalsession.hpp>
#include <ifastcbo/MgmtCo.hpp>
#include <ifastcbo/MgmtCoOptions.hpp>
////#include <ifastbp/UserSessionProcessIncludes.h>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0263_vw.hpp>
#include <ifastdataimpl\dse_dstc0344_vw.hpp>


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
   ifsupp::PFNMGMTCOINFO pfnMgmtCoInfo;
   ifsupp::GetMgmtCoInfoCallback(pfnMgmtCoInfo);
   if( NULL != pfnMgmtCoInfo ) {
      DSTCUserSession* p;
      (*pfnMgmtCoInfo)(p, pMgmtCo_, m_strClientID, m_strCompanyID, m_strName, m_strURL);
   }
   // need to find:
   //    pMgmtCo_
   //    m_strClientID, m_strCompanyID, m_strName, m_strURL
   //    TODO: write a callback function into MFDSTC to do this
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


