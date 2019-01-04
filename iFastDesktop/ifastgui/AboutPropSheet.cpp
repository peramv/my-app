// AboutPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include <win32\platform.h>
#include "mfdstc.h"
#include "AboutPropSheet.h"
#include <ConfigManager.hpp>

#include "AboutPropGeneralPage.h"
#include "AboutPropModulePage.h"
#include "AboutPropRegistryPage.h"
#include "AboutPropSonicPage.h"
#include "AboutPropRTSPage.h"
#include "AboutPropLogPage.h"
#include "AboutPropMgmtPage.h"
#include "AboutPropMgmtOptionsPage.h"
#include "AboutPropBandsPage.h"
#include <sstream>
#include <memory>
#include <winsock2.h>

const char* const REGKEY_PRODUCT_OPTIONS = "SYSTEM\\CurrentControlSet\\Control\\ProductOptions";

typedef enum {
   typeDefault = 0, typeAdvancedServer = 1, typeWorkstation = 2, typeServer = 3
} NTTYPE;

static NTTYPE getNTVersion( void )
{
   char szValue[256];
   DWORD dwType = 0;
   DWORD dwSize = sizeof (szValue);
   HKEY hKey   = NULL;
   LONG lStatus;

   lStatus = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                           REGKEY_PRODUCT_OPTIONS,
                           0,
                           KEY_QUERY_VALUE,
                           &hKey);
   if( ERROR_SUCCESS != lStatus ) {
      // Windows NT
      return(typeDefault);
   }

   lStatus = RegQueryValueEx(hKey, TEXT("ProductType"),
                             NULL, &dwType, (LPBYTE)szValue, &dwSize);
   RegCloseKey(hKey) ;
   if( ERROR_SUCCESS != lStatus ) {
      // Windows NT
      return(typeDefault);
   }

   if( stricmp("WINNT", szValue) == 0 ) {
      return(typeWorkstation);         // Windows NT Workstation
   }
   else if( 0 == stricmp("SERVERNT", szValue) ) {
      return(typeServer);             // Windows NT Server
   }
   else if( 0 == stricmp("LANMANNT", szValue) ) {
      return(typeAdvancedServer);     // Windows NT Advanced Server (3.1)
   }

   return(typeDefault);               // Windows NT
}// GetNTVersion()


static void logOS( std::wstringstream& ss)
{
   OSVERSIONINFO osvi;

   osvi.dwOSVersionInfoSize = sizeof(osvi);
   GetVersionEx(&osvi);

   // Dump out windows version and processor information
   switch( osvi.dwPlatformId ) {
      case VER_PLATFORM_WIN32_NT:
         switch( getNTVersion() ) {
            case typeWorkstation:
               ss << I_("Microsoft Windows NT Workstation ") 
                  << osvi.dwMajorVersion << I_(".") << osvi.dwMinorVersion
                  << I_(" (Build ") << osvi.dwBuildNumber << I_(") ")
                  << osvi.szCSDVersion
                  << std::endl;
               break;
            case typeServer:
               ss << I_("Microsoft Windows NT Server ") 
                  << osvi.dwMajorVersion << I_(".") << osvi.dwMinorVersion
                  << I_(" (Build ") << osvi.dwBuildNumber << I_(") ")
                  << osvi.szCSDVersion
                  << std::endl;
               break;
            case typeAdvancedServer:
               ss << I_("Microsoft Windows NT Advanced Server ") 
                  << osvi.dwMajorVersion << I_(".") << osvi.dwMinorVersion
                  << I_(" (Build ") << osvi.dwBuildNumber << I_(") ")
                  << osvi.szCSDVersion
                  << std::endl;
               break;
            default:
               ss << I_("Microsoft Windows NT ") 
                  << osvi.dwMajorVersion << I_(".") << osvi.dwMinorVersion
                  << I_(" (Build ") << osvi.dwBuildNumber << I_(") ")
                  << osvi.szCSDVersion
                  << std::endl;
               break;
         }
         break;
      case VER_PLATFORM_WIN32_WINDOWS:  // i.e. Win95
         ss << I_("Microsoft Windows 95 ") 
            << osvi.dwMajorVersion << I_(".") << osvi.dwMinorVersion
            << I_(" (Build ") << osvi.dwBuildNumber << I_(") ")
            << osvi.szCSDVersion
            << std::endl;
         break;
      default:
         // Unknown OS
         ss << I_("Unknown Win32 platform ") 
            << osvi.dwMajorVersion << I_(".") << osvi.dwMinorVersion
            << I_(" (Build ") << osvi.dwBuildNumber << I_(") ")
            << osvi.szCSDVersion
            << std::endl;
         break;
   }
   return;
}

static DString getLocalHost()
{
   char szHostName[256];
   gethostname( szHostName, sizeof(szHostName)/sizeof(szHostName[0]) );
   return( DString( DStringA( szHostName ) ) );
}

static DString getLocalIP()
{
   WSADATA wsaData;
   struct hostent *pHostEnt; 
   struct sockaddr_in tmpSockAddr; //placeholder for the ip address

   // Not needed if it is already taken care by some other part of the application
   WSAStartup(MAKEWORD(2,0),&wsaData); 

   //This will retrieve the ip details and put it into pHostEnt structure
   char szHostName[256];
   gethostname(szHostName, sizeof(szHostName)/sizeof(szHostName[0]));
   pHostEnt = gethostbyname(szHostName);

   if( NULL == pHostEnt ) {
      return( DString(I_("")) );
   }

   memcpy(&tmpSockAddr.sin_addr,pHostEnt->h_addr,pHostEnt->h_length);

   char szIP[17];
   strcpy(szIP,inet_ntoa(tmpSockAddr.sin_addr));
   DString s = DStringA(szIP);
   return( s );
}


void AboutPropSheet::Display( const I_CHAR* pszCaption )
{
   AboutPropSheet sht( pszCaption );
   sht.m_psh.dwFlags |= PSH_NOAPPLYNOW;
   sht.m_psh.dwFlags = sht.m_psh.dwFlags &~(PSH_HASHELP);
   AboutPropGeneralPage* pPageGeneral = new AboutPropGeneralPage();
   pPageGeneral->m_psp.dwFlags &= ~PSP_HASHELP;
   AboutPropModulePage* pPageModule = new AboutPropModulePage();
   pPageModule->m_psp.dwFlags &= ~PSP_HASHELP;
   AboutPropRegistryPage* pPageRegistry = new AboutPropRegistryPage();
   pPageRegistry->m_psp.dwFlags &= ~PSP_HASHELP;
   AboutPropSonicPage* pPageSonic = NULL;
   AboutPropRTSPage* pPageRTS = NULL;
   AboutPropLogPage* pPageLog = new AboutPropLogPage();
   pPageLog->m_psp.dwFlags &= ~PSP_HASHELP;
   sht.AddPage( pPageGeneral );
   sht.AddPage( pPageModule );
   sht.AddPage( pPageRegistry );
   if( GetConfigValueAsBool(I_("RTSHost"), I_("UseSonicMQ")) ) {
      pPageSonic = new AboutPropSonicPage;
      pPageSonic->m_psp.dwFlags &= ~PSP_HASHELP;
      sht.AddPage( pPageSonic );
   } 
   else {
      pPageRTS = new AboutPropRTSPage;
      pPageRTS->m_psp.dwFlags &= ~PSP_HASHELP;
      sht.AddPage( pPageRTS );
   }
   sht.AddPage( pPageLog );
   AboutPropMgmtPage* pPageMgmt = new AboutPropMgmtPage();
   if( pPageMgmt->hasMgmtCo() ) {
      sht.AddPage( pPageMgmt );
   }
   AboutPropMgmtOptionsPage* pPageMgmtOptions = new AboutPropMgmtOptionsPage();
   if( pPageMgmtOptions->hasOptions() ) {
      sht.AddPage( pPageMgmtOptions );
   }
   AboutPropBandsPage* pPageBands = new AboutPropBandsPage();
   if( pPageBands->hasBands() ) {
      sht.AddPage( pPageBands );
   }
   sht.DoModal();
   delete pPageGeneral;
   delete pPageModule;
   delete pPageRegistry;
   delete pPageSonic;
   delete pPageRTS;
   delete pPageLog;
   delete pPageMgmt;
   delete pPageMgmtOptions;
}

// AboutPropSheet

IMPLEMENT_DYNAMIC(AboutPropSheet, CPropertySheet)
AboutPropSheet::AboutPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

AboutPropSheet::AboutPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

AboutPropSheet::~AboutPropSheet()
{
}

BOOL AboutPropSheet::OnInitDialog() {
   CPropertySheet::OnInitDialog();
   CRect rect, tabrect;
   int width;

   //Get button sizes and positions
   GetDlgItem(IDOK)->GetWindowRect(rect);
   GetTabControl()->GetWindowRect(tabrect);
   ScreenToClient(rect); ScreenToClient(tabrect);

   //New button -> width, height and Y-coordiate of IDOK
   // -> X-coordinate of tab control
   width = rect.Width();
   rect.left = tabrect.left; rect.right = tabrect.left + width;

   //Create new "Add" button and set standard font
   m_btnReport.Create(CString("Report"),
                      BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP, 
                      rect, 
                      this, 
                      IDC_GENERAL_REPORT);
   m_btnReport.SetFont(GetFont());
   return( TRUE );
}

void AboutPropSheet::OnReport() {
   std::wstringstream ss;

   CString defaultFileName, strTime;

   ss << I_("iFAST/Desktop Diagnostic Report") << std::endl;
   {
      char szDate[512];
      SYSTEMTIME st;
      GetSystemTime( &st );
      sprintf( szDate,
               "%04d-%02d-%02d %02d:%02d:%02d UTC",
               st.wYear,
               st.wMonth,
               st.wDay,
               st.wHour,
               st.wMinute,
               st.wSecond );
      ss << DString(DStringA(szDate)) << std::endl;

      strTime.Format(I_("%04d-%02d-%02d_%02d_%02d_%02d.txt"),
                        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );

   }
   I_CHAR* pszUserName = i_getenv( I_("USERNAME") );
   ss << I_("User: ") << pszUserName << std::endl;
   ss << I_("Computer: ") << getLocalHost() << std::endl;
   defaultFileName.Format(I_("%s_%s_%s"), getLocalHost().c_str(), pszUserName, LPCTSTR(strTime) );
   ss << I_("Local IP: ") << getLocalIP() << std::endl;
   logOS( ss );
   ss << std::endl;

   for( int iPage = 0; iPage < GetPageCount(); ++iPage ) {
      AboutPropPage* pPage = dynamic_cast<AboutPropPage*>(GetPage(iPage));
      if( NULL != pPage ) {
         pPage->generateReport( ss );
      }
   }

   std::wstring str = ss.str();

#if 0
   HGLOBAL clipbuffer;
   static TCHAR * buffer;

   OpenClipboard();
   EmptyClipboard();
   DWORD dw = str.length() + 1;
   clipbuffer = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, dw * sizeof(TCHAR));
   buffer = (TCHAR *)GlobalLock(clipbuffer);
   lstrcpy(buffer, str.c_str());
   GlobalUnlock(clipbuffer);
   SetClipboardData(CF_UNICODETEXT,clipbuffer);
   CloseClipboard();
   AfxMessageBox(I_("Report is now in clipboard. You may paste it into a document or e-mail."), MB_OK );
#else
   CFileDialog dlg( FALSE, I_("txt"), defaultFileName, OFN_OVERWRITEPROMPT );
   if( dlg.DoModal() ) {
      CStdioFile reportFile;
      if( reportFile.Open( dlg.GetFileName(), CFile::modeCreate|CFile::modeWrite ) ) {
         CString strText = str.c_str();
         reportFile.WriteString(strText );
         CString strMessage;
         strMessage.Format(I_("Report file %s generated."),dlg.GetPathName());

         HGLOBAL clipbuffer;
         static TCHAR * buffer;

         OpenClipboard();
         EmptyClipboard();
         CString strPath = dlg.GetPathName();
         DWORD dw = strPath.GetLength() + 1;
         clipbuffer = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, dw * sizeof(TCHAR));
         buffer = (TCHAR *)GlobalLock(clipbuffer);
         lstrcpy(buffer, LPCTSTR(strPath));
         GlobalUnlock(clipbuffer);
         SetClipboardData(CF_UNICODETEXT,clipbuffer);
         CloseClipboard();

         DString dstrEMail = GetConfigValueAsString( I_("Support"), I_("ReportEMailAddress") );
         dstrEMail.stripTrailing();
         if( dstrEMail != I_("") ) {
            CString strCommand("open");
            CString strMailTo;
            strMailTo.Format(I_("mailto:%s?subject=Error Report for iFAST/Desktop&body=The report file is %s%%0A%%0APlease attach the file to this e-mail before sending it."),
                           dstrEMail.c_str(), LPCTSTR(strPath));
            HINSTANCE h = ShellExecute(NULL, strCommand, strMailTo, NULL , NULL, SW_SHOWNORMAL);

         }
         else {
            AfxMessageBox(strMessage,MB_OK);
         }
      }
   }


#endif
}


BEGIN_MESSAGE_MAP(AboutPropSheet, CPropertySheet)
ON_BN_CLICKED(IDC_GENERAL_REPORT, OnReport)
END_MESSAGE_MAP()


// AboutPropSheet message handlers

