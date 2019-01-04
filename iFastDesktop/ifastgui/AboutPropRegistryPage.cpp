// AboutPropRegistryPage.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "AboutPropRegistryPage.h"
#include <ConfigManager.hpp>

namespace {
   const unsigned long MAXBUFSIZE = 256;
   const short BUILDTYPE = 0;
   const short DATETIME  = 1;
   const short FORMAT_NUM = 6;

   const I_CHAR *NUL_INSTANCE   = I_( "<<Not Loaded>>" );
   const I_CHAR *NOT_AVAILABLE  = I_( "" );
   const I_CHAR *LOC_BUILD_TYPE = I_( "Local Compile" );
   const I_CHAR *BSV_BUILD_TYPE = I_( "Build Server" );
   const I_CHAR *LGM_BUILD_TYPE = I_( "Library Mgmt" );

   //Used in list control
   const I_CHAR *COL_HEADER1 = I_( "Path" );
   const I_CHAR *COL_HEADER2 = I_( "Date / Time" );
   const I_CHAR *COL_HEADER3 = I_( "Build Type" );

   const I_CHAR *DATE_STR = I_( "Date: " );
   const I_CHAR *TIME_STR = I_( "Time: " );
}

//Macro used in ShowImports() function
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (addValue) )


// AboutPropRegistryPage dialog

IMPLEMENT_DYNAMIC(AboutPropRegistryPage, CPropertyPage)
AboutPropRegistryPage::AboutPropRegistryPage()
: CPropertyPage(AboutPropRegistryPage::IDD)
, m_registryCount(0)
{
}

AboutPropRegistryPage::~AboutPropRegistryPage()
{
}

void AboutPropRegistryPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AboutDetailsDlg)
   DDX_Control(pDX, IDC_LB_REVISION_INFO, m_registryList);
   //}}AFX_DATA_MAP
}


void AboutPropRegistryPage::generateReport( std::wstringstream& ss )
{
   DString tempString = ConfigManager::getApplication();
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== Registry Information ============================") << std::endl;
   ss << I_("Registry Key: ") << tempString.c_str() << std::endl;

   addReportItem( ss, I_("MFDSTC"), I_("SiteXML"), I_("file") );
   addReportItem( ss, I_("MFDSTC"), I_("SiteXML"), I_("override") );

   addReportItem( ss, I_("MFDSTC"), I_("Market"), I_("Market") );

   addReportItem( ss, I_("AwdInterface"), I_("AwdType"), I_("InterfaceDll") );
   addReportItem( ss, I_("AwdInterface"), I_("AwdType"), I_("AutoLogon") );

   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("RTSHostIP") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("RTSHostPort") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("PersistentConnections") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("RecycleInterval") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("SMQBrokerURLs") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("SMQSingleQueue") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("SMQMultiQueue") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("SMQLDAPQueue") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("SMQUser") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("SMQPassword") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("SMQWaitTimeout") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("cswacl") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("UseSonicMQ") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("LDAPUserNS") );
   addReportItem( ss, I_("MFDSTC"), I_("RTSHost"), I_("UseSingleSonicConnection") );

   addReportItem( ss, I_("MFDSTC"), I_("DataPath"), I_("FYIfile") );
   addReportItem( ss, I_("MFDSTC"), I_("DataPath"), I_("Path") );
   addReportItem( ss, I_("MFDSTC"), I_("DataPath"), I_("SysLoadPath") );
   addReportItem( ss, I_("MFDSTC"), I_("DataPath"), I_("RepositorySource") );

   addReportItem( ss, I_("MFDSTC"), I_("Csi"), I_("Host") );
   addReportItem( ss, I_("MFDSTC"), I_("Csi"), I_("Param") );
   addReportItem( ss, I_("MFDSTC"), I_("Csi"), I_("Type") );

   addReportItem( ss, I_("MFDSTC"), I_("DemoMode"), I_("ProtoDataPath") );

   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("Log_File") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("Log_Path") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("Log_Enable") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewLog_Append") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewLog_Complete") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewLog_Enable") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewLog_Path") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewLog_RawResponse") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewLog_RawRequest") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Enable") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Path") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Size") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("DisplayConnectionIcon") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("DisplayConditionName") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ShowClientNamePane") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ExceptionReport_Enable") );
   addReportItem( ss, I_("MFDSTC"), I_("Support"), I_("ExceptionReport_Path") );
   ss << std::endl;
}

BEGIN_MESSAGE_MAP(AboutPropRegistryPage, CPropertyPage)
END_MESSAGE_MAP()


// AboutPropRegistryPage message handlers
BOOL AboutPropRegistryPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   CWaitCursor waiter;

   DString tempString = GetConfigValueAsString( I_("MFDSTC"), I_("SiteXML"), I_("file") );
   SetDlgItemText( IDC_SITE_CONFIG, tempString.c_str() );
   tempString = ConfigManager::getApplication();
   SetDlgItemText( IDC_REGISTRY_KEY, tempString.c_str() );

   m_registryList.InsertColumn( 0, I_("Config"), LVCFMT_LEFT, 100 );
   m_registryList.InsertColumn( 1, I_("Key"), LVCFMT_LEFT, 100 );
   m_registryList.InsertColumn( 2, I_("Name"), LVCFMT_LEFT, 100 );
   m_registryList.InsertColumn( 3, I_("Value"), LVCFMT_LEFT, 600 );

   // Insert registry info into 'Revision List'
   addConfigEntry( I_("MFDSTC"), I_("SiteXML"), I_("file") );
   addConfigEntry( I_("MFDSTC"), I_("SiteXML"), I_("override") );

   addConfigEntry( I_("MFDSTC"), I_("Market"), I_("Market") );

   addConfigEntry( I_("AwdInterface"), I_("AwdType"), I_("InterfaceDll") );
   addConfigEntry( I_("AwdInterface"), I_("AwdType"), I_("AutoLogon") );

   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("RTSHostIP") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("RTSHostPort") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("PersistentConnections") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("RecycleInterval") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQBrokerURLs") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQSingleQueue") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQMultiQueue") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQLDAPQueue") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQUser") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQPassword") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQWaitTimeout") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("cswacl") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("UseSonicMQ") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("LDAPUserNS") );
   addConfigEntry( I_("MFDSTC"), I_("RTSHost"), I_("UseSingleSonicConnection") );

   addConfigEntry( I_("MFDSTC"), I_("DataPath"), I_("FYIfile") );
   addConfigEntry( I_("MFDSTC"), I_("DataPath"), I_("Path") );
   addConfigEntry( I_("MFDSTC"), I_("DataPath"), I_("SysLoadPath") );
   addConfigEntry( I_("MFDSTC"), I_("DataPath"), I_("RepositorySource") );

   addConfigEntry( I_("MFDSTC"), I_("Csi"), I_("Host") );
   addConfigEntry( I_("MFDSTC"), I_("Csi"), I_("Param") );
   addConfigEntry( I_("MFDSTC"), I_("Csi"), I_("Type") );

   addConfigEntry( I_("MFDSTC"), I_("DemoMode"), I_("ProtoDataPath") );

   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("Log_File") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("Log_Path") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("Log_Enable") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_Append") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_Complete") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_Enable") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_Path") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_RawResponse") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_RawRequest") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Enable") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Path") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Size") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("DisplayConnectionIcon") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("DisplayConditionName") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ShowClientNamePane") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ExceptionReport_Enable") );
   addConfigEntry( I_("MFDSTC"), I_("Support"), I_("ExceptionReport_Path") );

   return( TRUE );
}

void AboutPropRegistryPage::addConfigEntry( const I_CHAR* lpcszConfig,
                                            const I_CHAR* lpcszKey,
                                            const I_CHAR* lpcszValue ) {
   DString v = GetConfigValueAsString( lpcszConfig, lpcszKey, lpcszValue );

   int idx = m_registryList.InsertItem( m_registryCount++, I_( "" ) );

   m_registryList.SetItemText( idx, 0, lpcszConfig );
   m_registryList.SetItemText( idx, 1, lpcszKey );
   m_registryList.SetItemText( idx, 2, lpcszValue );
   m_registryList.SetItemText( idx, 3, v.c_str() );
}

void AboutPropRegistryPage::addReportItem( std::wstringstream& ss,
                                           const I_CHAR* lpcszConfig,
                                           const I_CHAR* lpcszKey,
                                           const I_CHAR* lpcszValue ) {
   DString v = GetConfigValueAsString( lpcszConfig, lpcszKey, lpcszValue );
   ss << lpcszConfig << I_("\\") << lpcszKey << I_("\\") << lpcszValue << I_("=") << v.c_str() << std::endl;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/AboutPropRegistryPage.cpp-arc  $
// 
//    Rev 1.11   Sep 16 2011 17:19:04   dchatcha
// Usability Improvement on iFAST/Desktop
// 
//    Rev 1.10   Jan 08 2010 08:35:36   dchatcha
// IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
//
