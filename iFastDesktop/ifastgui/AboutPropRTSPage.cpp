// AboutPropRTSPage.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "AboutPropRTSPage.h"
#include <configmanager.hpp>
#include <bfconmgr/BFConnectionManager.hpp>
#include <bfconmgr/BFHostConnectionManager.hpp>
#include <ifastdbrkr/RTSSocketConnectionFactory.hpp>

#include "AboutPropSonicPage.h"  // for checkPort()


// AboutPropRTSPage dialog

IMPLEMENT_DYNAMIC(AboutPropRTSPage, CPropertyPage)
AboutPropRTSPage::AboutPropRTSPage()
: CPropertyPage(AboutPropRTSPage::IDD)
, m_strHost( I_("Error") )
, m_iTimeout( 0 )
, m_iPort( 0 )
{
   DString vmHostName = GetConfigValueAsString( ConfigManager::getApplication(), I_("RTSHost"), I_("VMHostName") );
   BFConnectionManager* pConMgr = BFConnectionManager::getInstance();
   try {
   if( NULL != pConMgr ) {
      BFHostConnectionManager* pHostConMgr = pConMgr->getHostConnectionManager( vmHostName );
      if( NULL != pHostConMgr ) {
            RTSSocketConnectionFactory* pFactory = dynamic_cast<RTSSocketConnectionFactory*>( pHostConMgr->getConnectionFactory() );

            if( NULL != pFactory ) {
               m_strHost = DString(pFactory->getHostAddress()).c_str();
               m_iTimeout = pFactory->getTimeout();
               m_iPort = pFactory->getPort();
            }
      }
   }
   }
   catch( bad_cast ) {
      // Not an RTSSocketConnectionFactory
      // We just won't do anything (it's only an about box!)
   }
}

AboutPropRTSPage::~AboutPropRTSPage()
{
}

void AboutPropRTSPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
   DDX_Text( pDX, IDC_RTS_HOST, m_strHost );
   DDX_Text( pDX, IDC_RTS_PORT, m_iPort );
   DDX_Text( pDX, IDC_RTS_TIMEOUT, m_iTimeout );
}

void AboutPropRTSPage::generateReport( std::wstringstream& ss )
{
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== RTS Information =================================") << std::endl;
   ss << I_("RTSHost: ") << LPCTSTR( m_strHost ) << std::endl;
   ss << I_("RTSPort: ") << m_iPort << std::endl;
   ss << I_("Timeout: ") << m_iTimeout << std::endl;
   ss << std::endl;
}

BEGIN_MESSAGE_MAP(AboutPropRTSPage, CPropertyPage)
   ON_BN_CLICKED( IDC_RTS_PING, OnPbPing )
   ON_BN_CLICKED( IDC_RTS_CHECK, OnPbCheck )
END_MESSAGE_MAP()


// AboutPropRTSPage message handlers

// AboutPropSonicPage message handlers
BOOL AboutPropRTSPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();
   SetDlgItemText( IDC_RTS_CHECK_STATUS, I_("") );
   SetDlgItemText( IDC_RTS_PING_STATUS, I_("") );


   return( TRUE );
}

void AboutPropRTSPage::OnPbPing() 
{
   SetDlgItemText(IDC_RTS_PING_STATUS, I_("") );
   // call View152
}

void AboutPropRTSPage::OnPbCheck()
{
   SetDlgItemText(IDC_RTS_CHECK_STATUS, I_("") );

   CString strResult(I_(""));
   long connectStatus = AboutPropSonicPage::checkPort( m_strHost, m_iPort, strResult );
   SetDlgItemText( IDC_RTS_CHECK_STATUS, strResult );

}
