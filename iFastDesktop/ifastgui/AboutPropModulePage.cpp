// AboutPropModulePage.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "AboutPropModulePage.h"

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

   // Required support DLLs
   I_CHAR* SUPPORT_NAMES[] =
   {
      I_("ieframe"),
   };
}

//Macro used in ShowImports() function
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (addValue) )


// AboutPropModulePage dialog

IMPLEMENT_DYNAMIC(AboutPropModulePage, CPropertyPage)
AboutPropModulePage::AboutPropModulePage()
: CPropertyPage(AboutPropModulePage::IDD)
, m_itemCount(0)
{
}

AboutPropModulePage::~AboutPropModulePage()
{
}

void AboutPropModulePage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AboutDetailsDlg)
   DDX_Control(pDX, IDC_LB_COMPONENT_INFO, m_infoList);
   //}}AFX_DATA_MAP
}

void AboutPropModulePage::generateReport( std::wstringstream& ss )
{
   ss << I_("=====================================================") << std::endl;
   ss << I_("=== Module Information ==============================") << std::endl;
   ss << I_("Not implemented") << std::endl;
   ss << std::endl;
}

BEGIN_MESSAGE_MAP(AboutPropModulePage, CPropertyPage)
//{{AFX_MSG_MAP(AboutPropModulePage)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL AboutPropModulePage::OnInitDialog()
{
   CPropertyPage::OnInitDialog();

   CWaitCursor waiter;

   m_infoList.InsertColumn( 0, COL_HEADER1, LVCFMT_LEFT, 292 );
   m_infoList.InsertColumn( 1, COL_HEADER2, LVCFMT_LEFT, 270 );
   m_infoList.InsertColumn( 2, COL_HEADER3, LVCFMT_LEFT, 140 );

   HINSTANCE instance = AfxGetInstanceHandle();
   I_CHAR buffer[MAXBUFSIZE];
   ::GetModuleFileName( instance, buffer, MAXBUFSIZE );
   LoadModuleInfo( buffer );

   CString extension = I_( ".DLL" );
#ifdef _DEBUG
   extension = I_( "_D.DLL" );
#endif

   CString latestDate, currentDate;
   //Load Infrastructure information
   int count = sizeof( CORE_NAMES ) / sizeof( CORE_NAMES[0] );
   for( int i = 0; i < count; i++ )
   {
      currentDate = LoadModuleInfo( CORE_NAMES[i] + extension );
      GetLatestBuildDate( latestDate, currentDate );
   }

//   SetDlgItemText( IDC_TXT_INFRASTRUCTURE, latestDate );

   latestDate.Empty();
   //Load CBO information
   count = sizeof( APP_NAMES ) / sizeof( APP_NAMES[0] );
   for( i = 0; i < count; i++ )
   {
      currentDate = LoadModuleInfo( APP_NAMES[i] + extension );
      GetLatestBuildDate( latestDate, currentDate );
   }

   count = sizeof( SUPPORT_NAMES ) / sizeof( SUPPORT_NAMES[0] );
   static CString supportExtension = I_(".dll");
   for( i = 0; i < count; i++ )
   {
      currentDate = LoadModuleInfo( SUPPORT_NAMES[i] + supportExtension );
   }


   //Now walk all the loaded modules and recursively check
   //for dependencies on each one
   CString moduleName;
   for( i = 0; i < m_itemCount; i++ )
   {
      moduleName = m_infoList.GetItemText( i, 0 );
      WalkTheProcess( moduleName );
   }

   return( TRUE );
}

CString AboutPropModulePage::LoadModuleInfo( CString moduleName )
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

void AboutPropModulePage::LoadDependentInfo( CString dependentName )
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
CString AboutPropModulePage::GetModuleBuildInfo( HINSTANCE inst, const short infoType )
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

void AboutPropModulePage::GetLatestBuildDate( CString &latestDate, const CString &compareDate )
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

BOOL AboutPropModulePage::WalkTheProcess( CString fileName )
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

BOOL AboutPropModulePage::ShowImports( PIMAGE_DOS_HEADER dosHeader )
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

PIMAGE_SECTION_HEADER AboutPropModulePage::GetSectionHeader( PSTR name, PIMAGE_NT_HEADERS pNTHeader )
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


// AboutPropModulePage message handlers
