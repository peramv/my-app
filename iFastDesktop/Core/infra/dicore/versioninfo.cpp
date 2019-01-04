/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 */

#define DICORE_DLL

#ifndef VERSIONINFO_HPP
#include "versioninfo.hpp"
#endif

// forward declarations

static void makeValueString( int codepage, 
                             std::string & prodVerString );

static int getCodePage( char * localeString );

static bool getProductVersionInfo( const char * const dllName,
                                   char ** versionNumber,
                                   unsigned int * puVersionLen,
                                   HANDLE * hmem );

static bool getFileVersionInfo( const char * const dllName,
                                char ** versionNumber,
                                unsigned int * puVersionLen,
                                HANDLE * hmem );

static bool getVersionInfo( const char * const dllName,
                            const char * const versionString,
                            char ** versionNumber,
                            unsigned int * puVersionLen,
                            HANDLE * hmem );

// public methods

DString & VersionInfo::getVersionString( DString & inFileName,
                                         DString & msgOut )
{
   VersionInfo vi( inFileName );
   msgOut = I_( "File: " );
   msgOut += DString( DStringA( inFileName ) );
   msgOut += DString( I_( "; Product Version: " ) );
   DString ver = vi.getProductVersion();
   if ( ver.empty() )
      ver = I_( "missing from file" );
   msgOut += ver;
   msgOut += I_( "; File Version: " );
   ver = vi. getFileVersion();
   if ( ver.empty() )
      ver = I_( "missing from file" );
   msgOut += ver;
   return msgOut;
}


// Class methods

VersionInfo::VersionInfo( DString & filename ) :
   productVersionInfo( NULL ),
   fileVersionInfo( NULL )
{
   unsigned int versionLength;
   char * tmpVersionInfo;
   DStringA tmp( filename );
   const char * inFilename = tmp.c_str();
   HANDLE hMem;

   int itmp = getProductVersionInfo( inFilename,
                                     &tmpVersionInfo,
                                     &versionLength,
                                     &hMem );
   int errCode;
   if ( 0 == itmp )
   {
      errCode = GetLastError();
      return;
   }

   char * tmpProdVersionInfo = new char[ versionLength + 1 ];
   memcpy( tmpProdVersionInfo, 
           tmpVersionInfo, 
           versionLength );
   GlobalUnlock( hMem );
   GlobalFree( hMem );
   tmpProdVersionInfo[ versionLength ] = '\0';
   productVersionInfo = DString( DStringA( tmpProdVersionInfo ) );
   delete tmpProdVersionInfo;
   
   itmp = getFileVersionInfo( inFilename,
                              &tmpVersionInfo,
                              &versionLength,
                              &hMem );
   if ( 0 == itmp )
   {
      errCode = GetLastError();
      return;
   }
   char * tmpfileVersionInfo = new char[ versionLength + 1 ];
   memcpy( tmpfileVersionInfo, 
           tmpVersionInfo, 
           versionLength );
   GlobalUnlock( hMem );
   GlobalFree( hMem );
   tmpfileVersionInfo[ versionLength ] = '\0';
   fileVersionInfo = DString( DStringA( tmpfileVersionInfo ) );
   delete tmpfileVersionInfo;
}


VersionInfo::~VersionInfo()
{
}

/////////////////////////////////////////////////////////////////
//                                                             //
//                       LOCAL METHODS                         //
//                                                             //
/////////////////////////////////////////////////////////////////

static void makeValueString( int codepage, 
                             std::string & prodVerString )
{
   char tmp[ 20 ];
   std::string tmpString = prodVerString;
   sprintf( tmp, "%04X%04X", GetUserDefaultLangID(), codepage );
   prodVerString = "\\\\StringFileInfo\\\\";
   prodVerString += tmp;
   prodVerString += "\\\\";
   prodVerString += tmpString;
}


static int getCodePage( char * localeString )
{
   char * tp = setlocale( LC_ALL, localeString );
   std::string tmpString( tp );
   int index = tmpString.find_first_of( "." );
   DString tmpDString( tmpString.substr( ++index ) );
   int cp = tmpDString.asInteger();
   return cp;
}


static bool getProductVersionInfo( const char * const indllName,
                                   char ** versionNumber,
                                   unsigned int * puVersionLen,
                            HANDLE * hMem )
{
   return getVersionInfo( indllName,
                          "ProductVersion",
                          versionNumber,
                          puVersionLen,
                          hMem );
}


static bool getFileVersionInfo( const char * const indllName,
                                char ** versionNumber,
                                unsigned int * puVersionLen,
                            HANDLE * hMem )
{
   return getVersionInfo( indllName,
                          "FileVersion",
                          versionNumber,
                          puVersionLen,
                          hMem );
}


static bool getVersionInfo( const char * const indllName,
                            const char * const versionString,
                            char ** versionNumber,
                            unsigned int * puVersionLen,
                            HANDLE * hMem )
{
   DWORD   dwVerInfoSize;    // size of version information block
   DWORD   dwVerHnd = 0;     // ignored;
   bool    bRetCode = false;

   char * dllName = const_cast< char * >( indllName );

   dwVerInfoSize = GetFileVersionInfoSize( dllName, 
                                           &dwVerHnd );
   if ( dwVerInfoSize )
   {
      LPSTR   lpstrVffInfo;
      *hMem = GlobalAlloc( GMEM_MOVEABLE, dwVerInfoSize );
      if ( NULL == *hMem )
         return false;

      lpstrVffInfo  = ( char * ) GlobalLock( *hMem );
      bRetCode = GetFileVersionInfo( dllName,
                                     dwVerHnd,
                                     dwVerInfoSize,
                                     lpstrVffInfo);
      if ( !bRetCode )
      {
         return false;
      }

      char tmp[ 20 ];
      std::string prodVerString;

      // get the current locale
      char * saveLocale = setlocale( LC_ALL, NULL );
      saveLocale = strdup( saveLocale );

      // try the current locale
      int codepage = getCodePage( saveLocale );
      prodVerString = versionString;
      makeValueString( codepage, prodVerString );
      bRetCode = VerQueryValue( ( LPVOID ) lpstrVffInfo,
                                const_cast< char * >( prodVerString.c_str() ),
                                ( LPVOID * ) versionNumber,
                                puVersionLen );
      
      // try default next
      if ( !bRetCode )
      {
         codepage = getCodePage( "" );
         prodVerString = versionString;
         makeValueString( codepage, prodVerString );
         bRetCode = VerQueryValue( ( LPVOID ) lpstrVffInfo,
                                   const_cast< char * >( prodVerString.c_str() ),
                                   ( LPVOID * ) versionNumber,
                                   puVersionLen );
      }

      // try current ACP
      if ( !bRetCode )
      {
         codepage = getCodePage( ".ACP" );
         prodVerString = versionString;
         makeValueString( codepage, prodVerString );
         bRetCode = VerQueryValue( ( LPVOID ) lpstrVffInfo,
                                   const_cast< char * >( prodVerString.c_str() ),
                                   ( LPVOID * ) versionNumber,
                                   puVersionLen );
      }

      // try current OCP
      if ( !bRetCode )
      {
         codepage = getCodePage( ".OCP" );
         prodVerString = versionString;
         makeValueString( codepage, prodVerString );
         bRetCode = VerQueryValue( ( LPVOID ) lpstrVffInfo,
                                   const_cast< char * >( prodVerString.c_str() ),
                                   ( LPVOID * ) versionNumber,
                                   puVersionLen );
      }

      // if all else fails, use the 1200 locale
      if ( !bRetCode )
      {
         prodVerString = versionString;
         makeValueString( 1200, prodVerString );
         bRetCode = VerQueryValue( ( LPVOID ) lpstrVffInfo,
                                   const_cast< char * >( prodVerString.c_str() ),
                                   ( LPVOID * ) versionNumber,
                                   puVersionLen );
      }

      // reset the locale
      setlocale( LC_ALL, saveLocale );
      free( saveLocale );
   }

   return bRetCode;
}


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/dicore/versioninfo.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:34   kovacsro
// Initial revision.
//
//   Rev 1.2   23 Jan 2002 13:40:34   dt14177
//fixed memory leak and Unicode compile
//problem
//
//   Rev 1.1   22 Jan 2002 16:18:22   dt14177
//added getVersionString()
//
//   Rev 1.0   19 Mar 2001 15:14:02   DT14177
// 

