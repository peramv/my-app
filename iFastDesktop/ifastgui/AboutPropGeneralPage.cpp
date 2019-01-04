// AboutPropGeneralPage.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include <configmanager.hpp>
#include "configurationconstants.h"
#include "AboutPropGeneralPage.h"
#include <bfsessn\bfcpsession.hpp>
#include <ifastcbo\version_app.hpp>
#include <condition.hpp>
#include <bfdbrkr/bfviewtimelog.hpp>
#include <iomanip>

namespace {
   const unsigned long MAXBUFSIZE = 256;
   const short BUILDTYPE = 0;
   const short DATETIME = 1;
   const I_CHAR *BSV_BUILD_TYPE = I_( "Build Server" );
   const I_CHAR *LGM_BUILD_TYPE = I_( "Library Mgmt" );
   const I_CHAR *LOC_BUILD_TYPE = I_( "Local Compile" );
   const I_CHAR *NUL_INSTANCE   = I_( "<<Not Loaded>>" );
   const I_CHAR *NOT_AVAILABLE  = I_( "" );

   //Used with ConfigManager
   const I_CHAR *AWD_INTERFACE = I_( "AwdInterface" );
   const I_CHAR *AWD_TYPE = I_( "AwdType" );
   const I_CHAR *INTERFACE_DLL = I_( "InterfaceDll" );
   const I_CHAR *YES = I_( "Yes" );
   const I_CHAR *NO = I_( "No" );
}

// AboutPropGeneralPage dialog

IMPLEMENT_DYNAMIC(AboutPropGeneralPage, CPropertyPage)
AboutPropGeneralPage::AboutPropGeneralPage()
    : CPropertyPage(AboutPropGeneralPage::IDD)
{
   HINSTANCE instance = AfxGetInstanceHandle();
   m_strBuildTime = GetModuleBuildInfo( instance, DATETIME );
   m_strBuildLabel = ifds::getAppVersion().c_str();
   //Are we using AWD??
   m_strUsingAWD = BFCPSession::usingAwd() ? YES : NO;

   m_PID = GetCurrentProcessId();
   TCHAR szDir[MAX_PATH];
   GetCurrentDirectory( sizeof(szDir)/sizeof(szDir[0]), szDir );
   m_strCWD = szDir;

   m_strMarket = GetConfigValueAsString( I_("Market"), I_("Market") ).c_str();

   m_strVaalMode = GetConfigValueAsBool( I_("Support"), I_("AllPowerfulVaalMode") ) ?
      _T("Vaal Mode") : _T("");
}

AboutPropGeneralPage::~AboutPropGeneralPage()
{
}

BOOL AboutPropGeneralPage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   return( TRUE );
}

void AboutPropGeneralPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
   DDX_Text( pDX, IDC_BUILD_TIME, m_strBuildTime );
   DDX_Text( pDX, IDC_BUILD_LABEL, m_strBuildLabel );
   DDX_Text( pDX, IDC_USING_AWD, m_strUsingAWD );
   DDX_Text( pDX, IDC_GENERAL_PID, m_PID );
   DDX_Text( pDX, IDC_GENERAL_CWD, m_strCWD );
   DDX_Text( pDX, IDC_GENERAL_MARKET, m_strMarket );
   DDX_Text( pDX, IDC_GENERAL_VAAL_MODE, m_strVaalMode );
}

static const I_CHAR* apszSeverity[] = {
   I_("0"),
   I_("NO_CONDITION"),
   I_("TRACE_ONLY"),
   I_("NO_SEVERITY"),
   I_("INFORMATIONAL"),
   I_("WARNING"), 
   I_("SEVERE_ERROR"), 
   I_("CRITICAL_ERROR") };

void AboutPropGeneralPage::generateReport( std::wstringstream& ss )
{
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== General Information =============================") << std::endl;
   ss << I_("Build Time: ") << LPCTSTR(m_strBuildTime) << std::endl;
   ss << I_("Build Label: ") << LPCTSTR(m_strBuildLabel) << std::endl;
   ss << I_("Using AWD? ") << LPCTSTR(m_strUsingAWD) << std::endl;
   ss << I_("PID: ") << m_PID << std::endl;
   ss << I_("CWD: ") << LPCTSTR(m_strCWD) << std::endl;
   ss << I_("Market: ") << LPCTSTR(m_strMarket) << std::endl;
   ss << std::endl;
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== Conditions ======================================") << std::endl;
   const Condition* pCondition = Condition::getRecordedCondition(NULL);
   for( ; NULL != pCondition; pCondition = Condition::getRecordedCondition(pCondition) ) {
      ss << I_("Condition: ") << pCondition->getCode() << I_("{") << pCondition->getCodeString() << I_(")") << std::endl;
      {
         char szDate[512];
         SYSTEMTIME st;
         pCondition->getCreatedTimestamp( st );
         sprintf( szDate,
                  "   %04d-%02d-%02d %02d:%02d:%02d UTC",
                  st.wYear,
                  st.wMonth,
                  st.wDay,
                  st.wHour,
                  st.wMinute,
                  st.wSecond );
         ss << DString(DStringA(szDate)) << std::endl;
      }
      DString dstr(DStringA(pCondition->getFileName()));
      ss << I_("   ") << dstr.c_str() << I_("[") << pCondition->getLineNumber() << I_("]") << std::endl;
      ss << I_("   ") << pCondition->getMethodName() << std::endl;
      int sev = pCondition->getSeverity();
      if( sev > 0 && sev < (sizeof(apszSeverity)/sizeof(apszSeverity[0])) ) {
         ss << I_("   Severity: ") << apszSeverity[sev] << std::endl;
      }
      else {
         ss << I_("   Severity: ") << sev << std::endl;
      }
   }
   ss << std::endl;

   ss << I_("=====================================================") << std::endl;
   ss << I_("=== DataBroker ======================================") << std::endl;
   I_CHAR szBuf[1024];
   i_sprintf(szBuf,I_("%-12s %-16s %-36s %6s %6s %6s| %6s| %6s %6s| %6s %6s %6s %6s\n"),
                   I_("Time (UTC)"), I_("View"), I_("Tracking ID"),
                   I_("Send"),
                   I_("Rcv"),
                   I_("UoW"),
                   I_("Net"),
                   I_("ESB"),
                   I_("OEAdap"),
                   I_("ABL"),
                   I_("Pre"),
                   I_("Logic"),
                   I_("Post") );
   ss << szBuf;
/*
   ss << std::left << std::setw(13) << I_("Time (UTC)") << std::left << std::setw(16) << I_("View") << I_(" ")
      << std::left << std::setw(36) << I_("Tracking ID") << I_(" ")
      << I_("Send   ")
      << I_("Rcv    ")
      << I_("UoW    |")
      << I_("Net    |")
      << I_("ESB    ")
      << I_("OEAdap |")
      << I_("ABL    ")
      << I_("Pre    ")
      << I_("Logic  ")
      << I_("Post   ")
      << std::endl;
*/
   for( const ViewTimeEntry* pVTE = ViewTimeEntry::getViewTimeEntry(NULL); pVTE != NULL; pVTE = ViewTimeEntry::getViewTimeEntry(pVTE) ) {
      const SYSTEMTIME& st = pVTE->getTimeStamp();
      I_CHAR szBuf[1024];
      int viewTime = pVTE->getPreViewTime() +
                     pVTE->getViewTime() +
                     pVTE->getPostViewTime();
      int networkTime = pVTE->getSendTime() + pVTE->getReceiveTime() - pVTE->getNetworkTime();
      int esbTime = pVTE->getNetworkTime() - pVTE->getOEInvocationTime();
      int oeAdapTime = pVTE->getOEInvocationTime() - viewTime;
      i_sprintf(szBuf, I_("%02d:%02d:%02d.%03d %-16s %-36s %6d %6d %6d| %6d| %6d %6d| %6d %6d %6d %6d\n"),
                       st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
                       DString(pVTE->getViewName()).c_str(),
                       DString(pVTE->getMsgId()).c_str(),
                       pVTE->getSendTime(), 
                       pVTE->getReceiveTime(), 
                       pVTE->getUnitOfWorkTime(),
                       networkTime,
                       esbTime,
                       oeAdapTime,
                       viewTime,
                       pVTE->getPreViewTime(),
                       pVTE->getViewTime(),
                       pVTE->getPostViewTime());
/*
      ss << std::setfill(I_('0'));
      ss << std::right << std::setw(2) << (int)st.wHour << I_(":") << std::right << std::setw(2) << (int)st.wMinute << I_(":") << std::right << std::setw(2) << (int)st.wSecond << I_(".") << std::right << std::setw(3) << (int)st.wMilliseconds;
      ss << std::left << I_(" ");
      ss << std::setfill(I_(' '));
      int viewTime = pVTE->getPreViewTime() +
                     pVTE->getViewTime() +
                     pVTE->getPostViewTime();
      int networkTime = pVTE->getSendTime() + pVTE->getReceiveTime() - pVTE->getNetworkTime();
      int esbTime = pVTE->getNetworkTime() - pVTE->getOEInvocationTime();
      int oeAdapTime = pVTE->getOEInvocationTime() - viewTime;
      ss << std::left << std::setw(16) << pVTE->getViewName().c_str() << I_(" ")
         << std::left << std::setw(36) << pVTE->getMsgId().c_str() << I_(" ") 
         << std::left << std::setw(6) << pVTE->getSendTime() << I_(" ") 
         << std::left << std::setw(6) << pVTE->getReceiveTime() << I_(" ") 
         << std::left << std::setw(6) << pVTE->getUnitOfWorkTime() << I_(" |");
      ss << std::left << std::setw(6) << (int)(networkTime) << I_(" |")
         << std::left << std::setw(6) << (int)(esbTime) << I_(" ")
         << std::left << std::setw(6) << (int)(oeAdapTime)<< I_(" |");
      ss << std::left << std::setw(6) << (int)viewTime << I_(" ")
         << std::left << std::setw(6) << pVTE->getPreViewTime() << I_(" ")
         << std::left << std::setw(6) << pVTE->getViewTime() << I_(" ")
         << std::left << std::setw(6) << pVTE->getPostViewTime() << I_(" ")
         << std::endl;
*/
      ss << szBuf;
   }
   ss << std::endl;

}


BEGIN_MESSAGE_MAP(AboutPropGeneralPage, CPropertyPage)
END_MESSAGE_MAP()


// AboutPropGeneralPage message handlers

// Create a new pointer type to reference the fnGetModuleInfo functions in our DLLs
typedef long ( __cdecl * GET_MODULE_INFO)( char *buffer, unsigned long bufSize );
// We need a local prototype for the fnGetModuleInfo in the .exe file
extern "C" long fnGetModuleInfo( char* buffer, unsigned long bufSize );
CString AboutPropGeneralPage::GetModuleBuildInfo( HINSTANCE inst, const short infoType )
{
   if( inst == NULL )
   {
      return(NUL_INSTANCE);
   }

   CString retValue = NOT_AVAILABLE;

   char buffer[MAXBUFSIZE];

   //Cast the FARPROC to the fnGetModuleInfo prototype, then call it
   GET_MODULE_INFO pfnInfo = NULL;
   if( AfxGetInstanceHandle() == inst ) {
      pfnInfo = fnGetModuleInfo;
   }
   else {
      pfnInfo = (GET_MODULE_INFO)GetProcAddress( inst, "fnGetModuleInfo" );
   }
   if( NULL != pfnInfo ) {
      long buildType = pfnInfo( buffer, MAXBUFSIZE );

      if( buildType  > -1 )
      {
         if( BUILDTYPE == infoType )
         {
            retValue = ( 0 == buildType ) ? LOC_BUILD_TYPE :
                       ( 1 == buildType ) ? BSV_BUILD_TYPE : LGM_BUILD_TYPE;
         }
         else if( DATETIME == infoType )
         {
            retValue = buffer;
         }
      }
   }
   return(retValue);
}
