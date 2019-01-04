// AboutPropBandsPage.cpp : implementation file
//

#include "stdafx.h"
#include "ifsupp.h"
#include "AboutPropBandsPage.h"
#include <ConfigManager.hpp>
#include <ifastcbo/DSTCUserSession.hpp>
#include <ifastcbo/UserAccessList.hpp>
//#include <ifastbp/UserSessionProcessIncludes.h>
#include "ifsuppext.hpp"

namespace UAF { extern CLASS_IMPORT bool getUAFValue( unsigned int, std::wstring&, std::wstring& );}



namespace {
   const unsigned long MAXBUFSIZE = 256;

   //Used in list control
   const I_CHAR *COL_HEADER1 = I_( "Function" );
   const I_CHAR *COL_HEADER2 = I_( "Code" );
   const I_CHAR *COL_HEADER3 = I_( "Read" );
   const I_CHAR *COL_HEADER4 = I_( "C/U/D" );
}

//Macro used in ShowImports() function
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (addValue) )




// AboutPropBandsPage dialog

IMPLEMENT_DYNAMIC(AboutPropBandsPage, CPropertyPage)


AboutPropBandsPage::AboutPropBandsPage()
: CPropertyPage(AboutPropBandsPage::IDD)
, m_bandCount(0)
, pUserSession_(NULL)
, dstrMgmtCo_(I_(""))
{
   ifsupp::PFNMGMTCOINFO pfnMgmtCoInfo;
   ifsupp::GetMgmtCoInfoCallback(pfnMgmtCoInfo);
   if( NULL != pfnMgmtCoInfo ) {
      MgmtCo* pMgmtCo;
      CString str1,str2,str3,strClientID;
      (*pfnMgmtCoInfo)(pUserSession_, pMgmtCo, strClientID, str1, str2, str3);

      bool bBandInfoByCompanyId = GetConfigValueAsBool( I_("MFDSTC"), 
                                                        I_("Support"), 
                                                        I_("BandInfoByCompanyId") );
      if(bBandInfoByCompanyId)
      {
         dstrMgmtCo_ = LPCTSTR(str1);
      }
      else
      {
         dstrMgmtCo_ = LPCTSTR(strClientID);
      }
   }
}

AboutPropBandsPage::~AboutPropBandsPage()
{
}

void AboutPropBandsPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AboutDetailsDlg)
   DDX_Control(pDX, IDC_LB_BANDS, m_bandList);
   //}}AFX_DATA_MAP
}


bool AboutPropBandsPage::hasBands() const {
   return( pUserSession_ != NULL );
}

void AboutPropBandsPage::generateReport( std::wstringstream& ss )
{
   DString tempString = ConfigManager::getApplication();
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== User Access Bands ===============================") << std::endl;
   bool bHasUserAccessList = pUserSession_->hasUserAccessList( dstrMgmtCo_ );

   unsigned int iBand = 0;
   std::wstring dstrBand, dstrCode;
   while( UAF::getUAFValue( iBand++, dstrBand, dstrCode ) ) {
      ReportBand( ss, dstrBand, dstrCode, bHasUserAccessList );
   }
   ss << std::endl;

}

BEGIN_MESSAGE_MAP(AboutPropBandsPage, CPropertyPage)
END_MESSAGE_MAP()

void AboutPropBandsPage::AddBand( const std::wstring& dstrName, const std::wstring& dstrBand, bool bHasAccessList ) {
   int idx = m_bandList.InsertItem( m_bandCount++, I_( "" ) );

   m_bandList.SetItemText( idx, 0, dstrName.c_str() );
   m_bandList.SetItemText( idx, 1, dstrBand.c_str() );
   if( bHasAccessList ) { 
      if( pUserSession_->hasReadPermission(dstrMgmtCo_, dstrBand.c_str() ) ) {
         m_bandList.SetItemText( idx, 2, I_("Y") );
      }
      else {
         m_bandList.SetItemText( idx, 2, I_("N") );
      }
      if( pUserSession_->hasCreatePermission(dstrMgmtCo_, dstrBand.c_str() ) ) {
         m_bandList.SetItemText( idx, 3, I_("Y") );
      }
      else {
         m_bandList.SetItemText( idx, 3, I_("N") );
      }
   }
   else {
      m_bandList.SetItemText( idx, 2, I_("?") );
      m_bandList.SetItemText( idx, 3, I_("?") );
   }
}

void AboutPropBandsPage::ReportBand( std::wstringstream& ss,
                                     const std::wstring& dstrName, 
                                     const std::wstring& dstrBand, 
                                     bool bHasAccessList ) {
   ss.width(40);
   ss.setf( std::ios::left );
   ss << dstrName.c_str();
   ss << I_(": ");
   if( bHasAccessList ) { 
      if( pUserSession_->hasReadPermission(dstrMgmtCo_, dstrBand.c_str() ) ) {
         ss << I_("Y ");
      }
      else {
         ss << I_("N ");
      }
      if( pUserSession_->hasCreatePermission(dstrMgmtCo_, dstrBand.c_str() ) ) {
         ss << I_("Y ");
      }
      else {
         ss << I_("N ");
      }
   }
   else {
      ss << I_("? ? ");
   }
   ss << std::endl;
}

// AboutPropBandsPage message handlers
BOOL AboutPropBandsPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   CWaitCursor waiter;

   m_bandList.InsertColumn( 0, COL_HEADER1, LVCFMT_LEFT, 150 );
   m_bandList.InsertColumn( 1, COL_HEADER2, LVCFMT_LEFT, 50 );
   m_bandList.InsertColumn( 2, COL_HEADER3, LVCFMT_LEFT, 60 );
   m_bandList.InsertColumn( 3, COL_HEADER4, LVCFMT_LEFT, 60 );

   bool bHasUserAccessList = pUserSession_->hasUserAccessList( dstrMgmtCo_ );

   unsigned int iBand = 0;
   std::wstring dstrBand, dstrCode;
   while( UAF::getUAFValue( iBand++, dstrBand, dstrCode ) ) {
      AddBand( dstrBand, dstrCode, bHasUserAccessList );
   }

   return( TRUE );
}


