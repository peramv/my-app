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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : datapath.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   :
//
//******************************************************************************

#define DICORE_DLL

#ifdef DST_UNICODE
   #define UNICODE
#endif

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef DATAPATH_H
   #include "datapath.h"
#endif

#ifdef _WIN32

   #include <tchar.h>
   #include "registrykey.hpp"
   #include "registryvalue.hpp"

#endif

namespace
{
   const I_CHAR *INIPATH1 = I_( "IniPath" );
   const I_CHAR *INIPATH2 = I_( "_INIPATH" );
   const I_CHAR *PATH1    = I_( "Path" );
   const I_CHAR *PATH2    = I_( "_DATAPATH" );
}

static DString s_dataPath;
static DString s_iniPath;
static DString s_dstrEmpty;

void SetGlobalDataPath( const DString& dataPath ) {
   s_dataPath = dataPath;
}

const DString& GetGlobalDataPath( const DString& dataPath ) {
   return( s_dataPath );
}

void SetGlobalIniPath( const DString& iniPath ) {
   s_iniPath = iniPath;
}

const DString& GetGlobalIniPath( const DString& iniPath ) {
   return( s_iniPath );
}

bool GetPath( DString &path,
              const DString &app,
              const DString &company,
              const DString &path1,
              const DString &path2 )
{
   // Clear out the path
   path = I_( "" );

#ifdef _WIN32

   DString registryPath = I_( "SOFTWARE\\" );
   registryPath += company;
   registryPath += I_( "\\" );
   registryPath += app;
   registryPath += I_( "\\Config\\DataPath" );

   RegistryKey rkDataPath( registryPath.asA() );
   RegistryValue rvDataPath = rkDataPath.getValue( path1.asA() );

   if( RegistryValue::STRING == rvDataPath.getType() )
   {
      path = rvDataPath.getAsString();
   }

#endif

   if( path.empty() )
   {
      DString env = app;
      env += path2;

      try
      {
         const I_CHAR* pszValue = i_getenv( env.c_str() );
         if( NULL == pszValue )
         {
            path = NULL_STRING;
         }
         else
         {
            path = pszValue;
         }
      }
      catch( ... )
      {
         path = NULL_STRING;
      }
   }

   return(! path.empty());
}

bool GetDataPath( DString &path, const DString &app )
{
   DString company = I_( "DST" );
   return(GetDataPath( path, app, company ));
}

bool GetDataPath( DString &path, const DString &app, const DString &company )
{
   if( s_dataPath != s_dstrEmpty ) {
      path = s_dataPath;
      return( true );
   }
   return(GetPath( path, app, company, PATH1, PATH2 ));
}

bool GetIniPath( DString &path, const DString &app )
{
   DString company = I_( "DST" );
   return(GetIniPath( path, app, company ));
}

bool GetIniPath( DString &path, const DString &app, const DString &company )
{
   if( s_iniPath != s_dstrEmpty ) {
      path = s_iniPath;
      return( true );
   }

   bool success = GetPath( path, app, company, INIPATH1, INIPATH2 );

   if( ! success )
   {
      success = GetPath( path, app, company, PATH1, PATH2 );
   }

   return(success);
}

const I_CHAR *GetPathDelemiter()
{
   I_CHAR *delimiter = NULL;

#if defined( _WIN32 ) || defined( __OS2__ )

   delimiter = I_( "\\" );

#elif defined( _UNIX )

   delimiter = I_( "/" );

#endif

   return(delimiter);
}

bool FindApplication( DString &strApp )
{
   bool success = false;

   DString strName;
   GetApplicationFile( strName );
   strName.lowerCase();

#ifdef _WIN32

   DStringA strCore = "SOFTWARE\\DST\\DICORE";
   RegistryKey rkCore( strCore );
   RegistryValue rvApp = rkCore.getValue( strName.asA() );

   if( RegistryValue::STRING == rvApp.getType() )
   {
      strApp = rvApp.getAsString();
      success = true;
   }

#endif

   return(success);
}

void GetApplicationPathAndFile( DString &strPath, DString &strFile )
{
#ifdef _WIN32

   I_CHAR mod_name[MAX_PATH + 1];
   I_CHAR drive[MAX_PATH + 1];
   I_CHAR dir[MAX_PATH + 1];
   I_CHAR fname[MAX_PATH + 1];
   I_CHAR ext[MAX_PATH + 1];

   HMODULE handle = GetModuleHandle( NULL );
   GetModuleFileName( handle, mod_name, numElements(mod_name) );
   _tsplitpath( mod_name, drive, dir, fname, ext );

   strPath = drive;
   strPath += DString( dir );
   strFile = fname;

#endif
}

void GetApplicationPath( DString &strPath )
{
   DString dummy;
   GetApplicationPathAndFile( strPath, dummy );
}

void GetApplicationFile( DString &strFile )
{
   DString dummy;
   GetApplicationPathAndFile( dummy, strFile );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/iFastAWD/dicore/datapath.cpp-arc  $
// 
//    Rev 1.1   Nov 02 2011 04:42:58   purdyech
// Registry Cleanup
//
//   Rev 1.3   Aug 27 2009 08:57:48   purdyech
//Allow global override of IniPath and DataPath.  Used by XML configuration logic.
// 
//    Rev 1.2   Oct 09 2002 17:41:54   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   Sep 09 2002 13:37:14   PURDYECH
// Removed access violation in GetPath
// 
//    Rev 1.0   Jul 05 2002 10:14:02   SMITHDAV
// Initial revision.
// 
//    Rev 1.12   Jun 12 2000 17:52:10   DMUM
// Replaced static DString with static I_CHAR *
//
//    Rev 1.11   Oct 12 1999 10:05:58   DMUM
// Made changes to support Unicode name-mangling of DLLs
//
//    Rev 1.10   Jul 15 1999 09:51:36   DT14177
// Fixed BoundsChecker-reported buffer overrun error.
//
//    Rev 1.9   Jun 09 1999 09:51:30   DMUM
// If the DataPath is not found, config now uses the application path
//
//    Rev 1.8   May 26 1999 12:10:38   DMUM
// Bug fix - finding the application's name
//
//    Rev 1.7   May 14 1999 13:19:50   DMUM
// Small fix
//
//    Rev 1.6   Apr 27 1999 17:54:10   DMUM
// Changes for finding an application when setApplication()
// has not yet been found
//
//    Rev 1.5   Apr 19 1999 08:19:20   DMUM
// Changes for Unicode
//
//    Rev 1.4   22 Feb 1999 13:57:26   DT14177
// more UNICODE stuff
//
//    Rev 1.3   18 Feb 1999 10:38:00   DT14177
// UNICODE
//
//    Rev 1.2   Jan 28 1999 14:02:40   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Jan 28 1999 13:43:18   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:02   DMUM
//
//

