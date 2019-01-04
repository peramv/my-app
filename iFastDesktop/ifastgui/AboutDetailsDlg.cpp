//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997-1998 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AboutDetailsDlg.cpp
// ^AUTHOR : Terry Erickson
// ^DATE   : 3/31/98
//
// ----------------------------------------------------------
//
// ^CLASS    : AboutDetailsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "aboutdetailsdlg.h"
#include <configmanager.hpp>
#include "configurationconstants.h"

#include <bfsessn\bfcpsession.hpp>
#include ".\aboutdetailsdlg.h"

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const unsigned long MAXBUFSIZE = 256;
   const short BUILDTYPE = 0;
   const short DATETIME  = 1;
   const short FORMAT_NUM = 6;

   //Used in list control
   const I_CHAR *COL_HEADER1 = I_( "Path" );
   const I_CHAR *COL_HEADER2 = I_( "Date / Time" );
   const I_CHAR *COL_HEADER3 = I_( "Build Type" );
//   const I_CHAR *AB_INFOLIST = I_( "ABOUTINFOLIST" );

   const I_CHAR *NUL_INSTANCE   = I_( "<<Not Loaded>>" );
   const I_CHAR *NOT_AVAILABLE  = I_( "" );
   const I_CHAR *LOC_BUILD_TYPE = I_( "Local Compile" );
   const I_CHAR *BSV_BUILD_TYPE = I_( "Build Server" );
   const I_CHAR *LGM_BUILD_TYPE = I_( "Library Mgmt" );

   //Used with ConfigManager
   const I_CHAR *AWD_INTERFACE = I_( "AwdInterface" );
   const I_CHAR *AWD_TYPE = I_( "AwdType" );
   const I_CHAR *INTERFACE_DLL = I_( "InterfaceDll" );
   const I_CHAR *YES = I_( "Yes" );
   const I_CHAR *NO = I_( "No" );

   const I_CHAR *DATE_STR = I_( "Date: " );
   const I_CHAR *TIME_STR = I_( "Time: " );

   //Constants used for writing file
   const I_CHAR *TXT_FILTER = I_( "Text Files (*.txt)|*.txt||" );
   const I_CHAR *MODULE_DETAILS = I_( "Module Details\n" );
   const I_CHAR *OTHER_INFO = I_( "Other Information\n" );
   const I_CHAR *VIEW_DATA_PATH = I_( "View Data Path: " );
   const I_CHAR *USING_AWD = I_( "Using Awd: " );
   const I_CHAR *FILE_SPACER = I_( "**************************************************\n" );
   const I_CHAR *ABOUT_DETAILS_DLG = I_( "AboutDetailsDlg" );
   const I_CHAR *CRLF = I_( "\n" );
   const I_CHAR *TAB = I_( "\t" );

   // Infrastructure libraries
   I_CHAR* CORE_NAMES[] =
   {
      I_( "bfawdi" ),
      I_( "bfcbo" ),
      I_( "bfconmgr" ),
      I_( "bfdata" ),
      I_( "bfdbrkr" ),
      I_( "bfproc" ),
      I_( "bfsessn" ),
      I_( "bfutil" ),
      I_( "dplatform" ),
      I_( "ifdscore" ),

      I_( "diawdiu" ),
      I_( "dicoreu" ),
      I_( "didbrkru" ),

   };

   // Application libraries
   I_CHAR* APP_NAMES[] =
   {
      I_( "ifast_dataimpl" ),
      I_( "ifastids" ),
      I_( "ifastdbrkr" ),
      I_( "ifastcbo" ),
      I_( "ifastbp" ),
      I_( "ifastcsi" ),
      I_( "ifastawd" ),
      I_( "uibase" ),
   };
}

namespace CND
{
}
//Macro used in ShowImports() function
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (addValue) )

//******************************************************************************
//              Public Methods
//******************************************************************************

AboutDetailsDlg::AboutDetailsDlg(CWnd* pParent /*=NULL*/)
: CDialog(AboutDetailsDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(AboutDetailsDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
   m_itemCount = 0;
   m_registryCount = 0;
}

void AboutDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AboutDetailsDlg)
   DDX_Control(pDX, IDC_LB_COMPONENT_INFO, m_infoList);
   DDX_Control(pDX, IDC_LB_REVISION_INFO, m_registryList);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(AboutDetailsDlg, CDialog)
//{{AFX_MSG_MAP(AboutDetailsDlg)
ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
//}}AFX_MSG_MAP
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LB_REVISION_INFO, OnLvnItemchangedLbRegistryInfo)
END_MESSAGE_MAP()

//******************************************************************************
//              Protected Methods
//******************************************************************************

BOOL AboutDetailsDlg::OnInitDialog()
{
   CDialog::OnInitDialog();
   CWaitCursor waiter;

   m_infoList.InsertColumn( 0, COL_HEADER1, LVCFMT_LEFT, 292 );
   m_infoList.InsertColumn( 1, COL_HEADER2, LVCFMT_LEFT, 270 );
   m_infoList.InsertColumn( 2, COL_HEADER3, LVCFMT_LEFT, 140 );
//   m_infoList.LoadSettings( ABOUT_DETAILS_DLG, AB_INFOLIST );

   m_registryList.InsertColumn( 0, I_("Config"), LVCFMT_LEFT, 100 );
   m_registryList.InsertColumn( 1, I_("Key"), LVCFMT_LEFT, 100 );
   m_registryList.InsertColumn( 2, I_("Name"), LVCFMT_LEFT, 100 );
   m_registryList.InsertColumn( 3, I_("Value"), LVCFMT_LEFT, 600 );

   //Load application information
   HINSTANCE instance = AfxGetInstanceHandle();
   SetDlgItemText( IDC_TXT_APPLICATION, GetModuleBuildInfo( instance, DATETIME ) );
   I_CHAR buffer[MAXBUFSIZE];
   ::GetModuleFileName( instance, buffer, MAXBUFSIZE );
   LoadModuleInfo( buffer );

   CString extension = I_( ".DLL" );

#ifdef _DEBUG
   extension = I_( "_D.DLL" );
#endif

   //Load Awd information
   DString tempString = GetConfigValueAsString( AWD_INTERFACE, AWD_TYPE, INTERFACE_DLL );
#ifdef DST_UNICODE
   tempString += I_("U");
#endif
   LoadModuleInfo( tempString.c_str() + extension );

   tempString = ConfigManager::getApplication();

#if 0
   //Find Data Path
   tempString = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, 
                                        CONFIGURATION_CONSTANTS::DataPath, 
                                        CONFIGURATION_CONSTANTS::Path );
#endif
   SetDlgItemText( IDC_TXT_DATAPATH, tempString.c_str() );

#if 0
   //Find Sysload Path
   tempString = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, 
                                        CONFIGURATION_CONSTANTS::DataPath, 
                                        CONFIGURATION_CONSTANTS::SysloadPath );
#endif
   tempString = GetConfigValueAsString( I_("MFDSTC"), I_("SiteXML"), I_("file") );
   SetDlgItemText( IDC_TXT_SYSLOADPATH, tempString.c_str() );

   //Are we using AWD??
   SetDlgItemText( IDC__TXT_USINGAWD, BFCPSession::usingAwd() ? YES : NO );

   CString latestDate, currentDate;

   //Load Infrastructure information
   int count = sizeof( CORE_NAMES ) / sizeof( CORE_NAMES[0] );
   for( int i = 0; i < count; i++ )
   {
      currentDate = LoadModuleInfo( CORE_NAMES[i] + extension );
      GetLatestBuildDate( latestDate, currentDate );
   }

   SetDlgItemText( IDC_TXT_INFRASTRUCTURE, latestDate );

   latestDate.Empty();

   //Load CBO information
   count = sizeof( APP_NAMES ) / sizeof( APP_NAMES[0] );
   for( i = 0; i < count; i++ )
   {
      currentDate = LoadModuleInfo( APP_NAMES[i] + extension );
      GetLatestBuildDate( latestDate, currentDate );
   }

   SetDlgItemText( IDC_TXT_CBOS, latestDate );

#if 0
   //Load OCX information
   count = sizeof( OCX_NAMES ) / sizeof( OCX_NAMES[0] );
   for( i = 0; i < count; i++ )
   {
      LoadDependentInfo( OCX_NAMES[i] );
   }
#endif

   //Now walk all the loaded modules and recursively check
   //for dependencies on each one
   CString moduleName;
   for( i = 0; i < m_itemCount; i++ )
   {
      moduleName = m_infoList.GetItemText( i, 0 );
      WalkTheProcess( moduleName );
   }

   // Insert registry info into 'Revision List'
   addRegistryEntry( I_("MFDSTC"), I_("SiteXML"), I_("file") );
   addRegistryEntry( I_("MFDSTC"), I_("SiteXML"), I_("override") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("RTSHostIP") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("RTSHostPort") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("PersistentConnections") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("RecycleInterval") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQBrokerURLs") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQReqQueue") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQUser") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("SMQPassword") );
   addRegistryEntry( I_("MFDSTC"), I_("RTSHost"), I_("UseSonicMQ") );
   addRegistryEntry( I_("MFDSTC"), I_("DataPath"), I_("FYIfile") );
   addRegistryEntry( I_("MFDSTC"), I_("DataPath"), I_("Path") );
   addRegistryEntry( I_("MFDSTC"), I_("DataPath"), I_("SysLoadPath") );
   addRegistryEntry( I_("MFDSTC"), I_("DataPath"), I_("RepositorySource") );
   addRegistryEntry( I_("MFDSTC"), I_("DemoMode"), I_("ProtoDataPath") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("Log_File") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("Log_Path") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_Append") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_Complete") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_Enable") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_Path") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_RawResponse") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewLog_RawRequest") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Enable") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Path") );
   addRegistryEntry( I_("MFDSTC"), I_("Support"), I_("ViewTimeLog_Size") );
   addRegistryEntry( I_("MFDSTC"), I_("Exceptions"), I_("DumpLogFile") );
   addRegistryEntry( I_("MFDSTC"), I_("Exceptions"), I_("DumpLogStack") );
   addRegistryEntry( I_("MFDSTC"), I_("Exceptions"), I_("DumpPath") );
   addRegistryEntry( I_("MFDSTC"), I_("Exceptions"), I_("ShowAsserts") );
   addRegistryEntry( I_("MFDSTC"), I_("Market"), I_("Market") );
   addRegistryEntry( I_("AwdInterface"), I_("AwdType"), I_("InterfaceDll") );
   addRegistryEntry( I_("AwdInterface"), I_("AwdType"), I_("AutoLogon") );

   return(TRUE);  // Success
}


void AboutDetailsDlg::addRegistryEntry( const I_CHAR* lpcszConfig,
                                        const I_CHAR* lpcszKey,
                                        const I_CHAR* lpcszValue ) {
   DString v = GetConfigValueAsString( lpcszConfig, lpcszKey, lpcszValue );

   int idx = m_registryList.InsertItem( m_registryCount++, I_( "" ) );

   m_registryList.SetItemText( idx, 0, lpcszConfig );
   m_registryList.SetItemText( idx, 1, lpcszKey );
   m_registryList.SetItemText( idx, 2, lpcszValue );
   m_registryList.SetItemText( idx, 3, v.c_str() );
}

void AboutDetailsDlg::OnBtnSave()
{
   CFileDialog fileDlg( FALSE, I_( "txt" ), I_( "Details.txt" ),
                        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
                        OFN_LONGNAMES | OFN_PATHMUSTEXIST,
                        TXT_FILTER, this );

   if( fileDlg.DoModal() == IDOK )
   {
      if( fileDlg.GetFileExt().CompareNoCase( I_( "TXT" ) ) == 0 )
      {
         CString fileName = fileDlg.GetPathName();
         FILE* pFile = i_fopen( LPCTSTR(fileName), I_("w") );
         if( NULL != pFile ) {
            DString details = GetInfoAsString();

            i_fputs( details.c_str(), pFile );
            fclose( pFile );
         }
      }
   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::LoadModuleInfo
//
// ^DESCRIPTION :
//      This method loads module information into the list control
//
// ^PARAMETERS  :
//    ^^CString moduleName - The name of the module to parse
//
// ^RETURNS     :
//    ^^CString - Returns the datetime for this module
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************
CString AboutDetailsDlg::LoadModuleInfo( CString moduleName )
{
   HINSTANCE instance;
   if( ( instance = ::GetModuleHandle( moduleName ) ) ) {
      I_CHAR buffer[MAXBUFSIZE];
      ::GetModuleFileName( instance, buffer, MAXBUFSIZE );
      moduleName = buffer;
   }

   moduleName.MakeLower();

   CString dateTime = GetModuleBuildInfo( instance, DATETIME );

   int idx = m_infoList.InsertItem( m_itemCount++, I_( "" ) );

   m_infoList.SetItemText( idx, 0, moduleName );
   m_infoList.SetItemText( idx, 1, dateTime );
   m_infoList.SetItemText( idx, 2, GetModuleBuildInfo( instance, BUILDTYPE ) );

   return(dateTime);
}

//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::LoadDependentInfo
//
// ^DESCRIPTION :
//      This method searches for dependent information
//
// ^PARAMETERS  :
//    ^^CString dependentName - The name of the dependent to search for
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************
void AboutDetailsDlg::LoadDependentInfo( CString dependentName )
{
   dependentName.MakeLower();
   dependentName.TrimRight();

   //Make sure we have the corrent type of module
   CString right = dependentName.Right(3);
   if( right != I_( "exe" )  && right != I_( "dll" )  && 
       right != I_( "ocx" ) )
   {
      return;
   }

   //Make sure item is not already in the list
   CString listName;
   for( int i = 0; i < m_itemCount; i++ )
   {
      listName = m_infoList.GetItemText( i, 0 );

      if( -1 != listName.Find( dependentName ) )
      {
         return;
      }
   }

   HINSTANCE instance = ::GetModuleHandle( dependentName );
   CString dateTime = NUL_INSTANCE;

   if( NULL != instance )
   {
      I_CHAR buffer[MAXBUFSIZE];
      ::GetModuleFileName( instance, buffer, MAXBUFSIZE );
      dependentName = buffer;
      dependentName.MakeLower();

      HANDLE hFile = ::CreateFile( buffer, GENERIC_READ, FILE_SHARE_READ, NULL,
                                   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );

      if( hFile != INVALID_HANDLE_VALUE )
      {
         FILETIME fileTime;
         ::GetFileTime( hFile, NULL, NULL, &fileTime );
         COleDateTime odt( fileTime );
         dateTime = odt.Format( I_( "Date: %b %d %Y Time: %H:%M:%S" ) );
         ::CloseHandle(hFile);
      }
   }

   int idx = m_infoList.InsertItem( m_itemCount++, I_( "" ) );

   m_infoList.SetItemText( idx, 0, dependentName );
   m_infoList.SetItemText( idx, 1, dateTime );
   m_infoList.SetItemText( idx, 2, NOT_AVAILABLE );

}

// Create a new pointer type to reference the fnGetModuleInfo functions in our DLLs
typedef long ( __cdecl * GET_MODULE_INFO)( char *buffer, unsigned long bufSize );
// We need a local prototype for the fnGetModuleInfo in the .exe file
extern "C" long fnGetModuleInfo( char* buffer, unsigned long bufSize );
//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::GetModuleBuildInfo
//
// ^DESCRIPTION : Gets the build information for a particular module
//
// ^PARAMETERS  :
//    ^^ HINSTANCE inst - Module instance
//    ^^ const short infoType - Type of information to retrieve
//
// ^RETURNS     :
//    ^^ CString - The build information string
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************
CString AboutDetailsDlg::GetModuleBuildInfo( HINSTANCE inst, const short infoType )
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

//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::GetLatestBuildDate
//
// ^DESCRIPTION :
//      This method reveals the module with the latest build date
//
// ^PARAMETERS  :
//    ^^CString latestDate - The current latest date
//    ^^CString compareDate - The date to compare to latest date
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************
void AboutDetailsDlg::GetLatestBuildDate( CString &latestDate, const CString &compareDate )
{
   int dateIndex = latestDate.Find( DATE_STR );
   int timeIndex = latestDate.Find( TIME_STR );

   COleDateTime latestDT, compareDT;

   //Check for valid latestDate
   if( dateIndex != -1 && timeIndex != -1 )
   {
      latestDT.ParseDateTime( latestDate.Mid( FORMAT_NUM, timeIndex - FORMAT_NUM ) +
                              latestDate.Mid( timeIndex + FORMAT_NUM ) );
   }

   dateIndex = compareDate.Find( DATE_STR );
   timeIndex = compareDate.Find( TIME_STR );

   //Check for valid compareDate
   if( dateIndex != -1 && timeIndex != -1 )
   {
      compareDT.ParseDateTime( compareDate.Mid( FORMAT_NUM, timeIndex - FORMAT_NUM ) +
                               compareDate.Mid( timeIndex + FORMAT_NUM ) );

      //Compare and change latestDate if necessary
      if( latestDate.IsEmpty() || compareDT > latestDT )
      {
         latestDate = compareDate;
      }
   }
}

//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::GetInfoAsString
//
// ^DESCRIPTION :
//      This method parses the details information and
//      returns a block of text for writing to a file.
//
// ^PARAMETERS  : none
//
// ^RETURNS     :
//    ^^CString - The details in a CString object
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************
DString AboutDetailsDlg::GetInfoAsString() const
{
   DString retValue;

   //Module Details Header
   retValue += FILE_SPACER;
   retValue += MODULE_DETAILS;
   retValue += FILE_SPACER;
   retValue += CRLF;

   int longestPath = 0, longestDate = 0, tempNum;

   //Find the longest path and date string to determine space sizes
   for( int i = 0; i < m_infoList.GetItemCount(); i++ ) {
      tempNum = m_infoList.GetItemText( i, 0 ).GetLength();
      if( tempNum > longestPath ) {
         longestPath = tempNum;
      }
      tempNum = m_infoList.GetItemText( i, 1 ).GetLength();
      if( tempNum > longestDate ) {
         longestDate = tempNum;
      }
   }

   //Module Details
   DString path, date, type;
   for( i = 0; i < m_infoList.GetItemCount(); i++ ) {
      path = m_infoList.GetItemText( i, 0 );
      date = m_infoList.GetItemText( i, 1 );
      type = m_infoList.GetItemText( i, 2 );

      //Add some padding
      path = path.padLeft( longestPath );
      date = date.padLeft( longestDate );
      retValue += path + TAB + date + TAB + type + CRLF;
   }

   // Registry Details
   retValue += CRLF;
   retValue += FILE_SPACER;
   retValue += I_("Registry Details\n");
   retValue += FILE_SPACER;
   retValue += CRLF;
   int aMaxLen[4] = {0};
   for( i = 0; i < m_registryList.GetItemCount(); ++i ) {
      for( int j = 0; j < (sizeof(aMaxLen)/sizeof(aMaxLen[0])); ++j ) {
         int l = m_registryList.GetItemText( i, j ).GetLength();
         aMaxLen[j] = ( l > aMaxLen[j] ) ? l : aMaxLen[j];
      }
   }

   DString v;
   for( i = 0; i < m_registryList.GetItemCount(); ++i ) {
      DString vTab = I_("");
      for( int j = 0; j < (sizeof(aMaxLen)/sizeof(aMaxLen[0])); ++j ) {
         v = m_registryList.GetItemText(i,j);
         v.padLeft( aMaxLen[j] );
         retValue += vTab + v;
         vTab = TAB;
      }
      retValue += CRLF;
   }

   //Other Information Header
   retValue += CRLF;
   retValue += FILE_SPACER;
   retValue += OTHER_INFO;
   retValue += FILE_SPACER;
   retValue += CRLF;

   CString tempStr;

   //Data Path
   GetDlgItemText( IDC_TXT_DATAPATH, tempStr );
   retValue += I_("Application Name (Registry): ");
   retValue += tempStr + CRLF;

   GetDlgItemText( IDC_TXT_SYSLOADPATH, tempStr );
   retValue += I_("Site Configuration File: ");
   retValue += tempStr + CRLF;

   //Using AWD
   GetDlgItemText( IDC__TXT_USINGAWD, tempStr );
   retValue += USING_AWD;
   retValue += tempStr + CRLF;

   return(retValue);
}

//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::WalkTheProcess
//
// ^DESCRIPTION :
//      This method finds dependents for module
//
// ^PARAMETERS  :
//    ^^CString fileName - name of file to walk
//
// ^RETURNS     :
//    ^^BOOL - If successful
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************
BOOL AboutDetailsDlg::WalkTheProcess( CString fileName )
{
   BOOL lReturn = FALSE;

   //Create the file handle
   HANDLE hFile = ::CreateFile( fileName, GENERIC_READ, FILE_SHARE_READ, NULL,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );

   if( INVALID_HANDLE_VALUE != hFile )
   {
      //Map the file
      HANDLE hFileMapping = ::CreateFileMapping( hFile, NULL, PAGE_READONLY,
                                                 0, 0, NULL );
      if( 0 != hFileMapping )
      {
         //Make a mapped view of the file
         LPVOID lpFileBase = ::MapViewOfFile( hFileMapping, FILE_MAP_READ,
                                              0, 0, 0 );
         if( 0 != lpFileBase )
         {
            PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER) lpFileBase;

            if( IMAGE_DOS_SIGNATURE == dosHeader->e_magic )
            {
               //Walk the import information
               if( ShowImports( dosHeader ) )
               {
                  lReturn = TRUE;
               }
            }
            ::UnmapViewOfFile( lpFileBase );
         }
         ::CloseHandle( hFileMapping );
      }
      ::CloseHandle( hFile );
   }

   return(lReturn);
}

//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::ShowImports
//
// ^DESCRIPTION :
//      This method finds imports for the mapped file dosHeader
//
// ^PARAMETERS  :
//    ^^PIMAGE_DOS_HEADER dosHeader - The dosHeader of the file
//
// ^RETURNS     :
//    ^^BOOL - If successful
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************
BOOL AboutDetailsDlg::ShowImports( PIMAGE_DOS_HEADER dosHeader )
{
   try
   {
      PIMAGE_NT_HEADERS pNTHeader =
      MakePtr( PIMAGE_NT_HEADERS, dosHeader, dosHeader->e_lfanew );

      // First, verify that the e_lfanew field gave us a reasonable
      // pointer, then verify the PE signature.
      if( ::IsBadReadPtr( pNTHeader, sizeof( IMAGE_NT_HEADERS ) )
          || ( pNTHeader->Signature != IMAGE_NT_SIGNATURE ) )
      {
         return(FALSE);
      }

      //We show both the bound dll and any forward references.
      PIMAGE_DATA_DIRECTORY pidd =
      ((PIMAGE_OPTIONAL_HEADER) &pNTHeader->OptionalHeader)->DataDirectory;

      // Look for an idata section.
      PIMAGE_SECTION_HEADER header = GetSectionHeader( ".idata", pNTHeader );
      if( 0 == header )
      {
         return(FALSE);
      }

      // This section handles unbound dlls and the old style binding
      DWORD base = (DWORD) dosHeader;

      PIMAGE_IMPORT_DESCRIPTOR importDesc =
      MakePtr( PIMAGE_IMPORT_DESCRIPTOR, base, header->PointerToRawData );

      int delta = (int) ( header->VirtualAddress - header->PointerToRawData );
      char dependFile[100];

      while( TRUE )
      {
         // The array of image descriptors is null terminated
         if( 0 == importDesc->Characteristics )
         {
            break;
         }

         sprintf( dependFile, "%s", (PBYTE) (importDesc->Name) - delta + base );

         //Load list with information
         LoadDependentInfo( dependFile );

         importDesc++;  // advance to next IMAGE_IMPORT_DESCRIPTOR
      }

      return(TRUE);
   }
   catch( ... )
   {
      return(FALSE);
   }
}

//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::GetSectionHeader
//
// ^DESCRIPTION :
//      This method returns the section header
//
// ^PARAMETERS  :
//    ^^PSTR name - Pointer to the section name
//    ^^PIMAGE_NT_HEADERS pNTHeader - NT header
//
// ^RETURNS     :
//    ^^PIMAGE_SECTION_HEADER - Section header
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************
PIMAGE_SECTION_HEADER AboutDetailsDlg::GetSectionHeader( PSTR name, PIMAGE_NT_HEADERS pNTHeader )
{
   PIMAGE_SECTION_HEADER section = (PIMAGE_SECTION_HEADER) ( pNTHeader + 1 );

   for( int i = 0; i < pNTHeader->FileHeader.NumberOfSections; i++, section++ )
   {
      if( 0 == strnicmp( (LPCSTR) section->Name, name, IMAGE_SIZEOF_SHORT_NAME ) )
      {
         return(section);
      }
   }

   return(0);
}



//*****************************************************************************
//
// ^PRIVATE METHOD : AboutDetailsDlg::OnOK()
//
// ^DESCRIPTION :
//      Save the Listbox settings
//
// ^PARAMETERS  :
//    ^^void
//
// ^RETURNS     :
//    ^^void
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************

void AboutDetailsDlg::OnOK() 
{
//   m_infoList.SaveSettings( ABOUT_DETAILS_DLG, AB_INFOLIST );
   CDialog::OnOK();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AboutDetailsDlg.cpp-arc  $
 * 
 *    Rev 1.11   Feb 06 2009 14:56:00   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 * 
 *    Rev 1.10   Nov 21 2007 07:37:44   purdyech
 * Added conditional support for exception processing.
 * 
 *    Rev 1.9   Jun 24 2007 09:05:16   purdyech
 * Added AWD AutoLogon feature to desktop
 * 
 *    Rev 1.8   May 14 2007 15:12:46   purdyech
 * PTS 820423 - Extensive changes to Component Dialog
 * 
 *    Rev 1.7   Nov 14 2004 15:00:24   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   May 26 2003 15:32:28   PURDYECH
 * fnGetModuleInfo is no longer exported so we will explicitly reference it 
 * 
 *    Rev 1.5   Mar 21 2003 18:29:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:55:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   May 28 2002 12:19:44   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.2   22 May 2002 19:15:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.1   03 Jul 2001 15:55:04   SMITHDAV
 * Add revision list.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Jul 12 1999 17:30:56   PRAGERYA
 * DataDictionary constants replaced by ConfigurationConstants
 * 
 *    Rev 1.1   Jul 08 1999 10:04:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */


void AboutDetailsDlg::OnLvnItemchangedLbRegistryInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
   // TODO: Add your control notification handler code here
   *pResult = 0;
}
