#include "stdafx.h"
#include <registrykey.hpp>

namespace fake {
   const char * const DST = "SOFTWARE\\DST";
   const char * const DST_DEBUG = "SOFTWARE\\DST\\Debug";
   const char * const DICORE = "SOFTWARE\\DST\\DICORE";
   const char * const HLLAPI = "SOFTWARE\\DST\\HLLAPI";
   const char * const HLLAPI_TCS = "SOFTWARE\\DST\\HLLAPI\\TCS";
   const char * const MFDSTC = "SOFTWARE\\DST\\MFDSTC";
   const char * const MFDSTC_ADMIN = "SOFTWARE\\DST\\MFDSTC\\Admin";
   const char * const MFDSTC_AWDINTERFACE = "SOFTWARE\\DST\\MFDSTC\\AwdInterface";
   const char * const MFDSTC_CBO = "SOFTWARE\\DST\\MFDSTC\\CBO";
   const char * const MFDSTC_CONFIG = "SOFTWARE\\DST\\MFDSTC\\Config";
   const char * const MFDSTC_CONFIG_AWDTYPE = "SOFTWARE\\DST\\MFDSTC\\Config\\AwdType";
   const char * const MFDSTC_CONFIG_CSI = "SOFTWARE\\DST\\MFDSTC\\Config\\Csi";
   const char * const MFDSTC_CONFIG_DATAPATH = "SOFTWARE\\DST\\MFDSTC\\Config\\DataPath";
   const char * const MFDSTC_CONFIG_DISPLAYMASKS = "SOFTWARE\\DST\\MFDSTC\\Config\\DisplayMasks";
   const char * const MFDSTC_CONFIG_HOSTMASKS = "SOFTWARE\\DST\\MFDSTC\\Config\\HostMasks";
   const char * const MFDSTC_CONFIG_MARKET = "SOFTWARE\\DST\\MFDSTC\\Config\\Market";
   const char * const MFDSTC_CONFIG_RTSHOST = "SOFTWARE\\DST\\MFDSTC\\Config\\RTSHost";
   const char * const MFDSTC_CONFIG_SUPPORT = "SOFTWARE\\DST\\MFDSTC\\Config\\Support";
   const char * const MFDSTC_CONFIG_TOOLTIPS = "SOFTWARE\\DST\\MFDSTC\\Config\\Tooltips";
   const char * const MFDSTC_DATABROKER = "SOFTWARE\\DST\\MFDSTC\\DataBroker";
   const char * const MFDSTC_DEFAULTWORKSTATION = "SOFTWARE\\DST\\MFDSTC\\DefaultWorkstation";
   const char * const MFDSTC_DICORE = "SOFTWARE\\DST\\MFDSTC\\DICORE";
   const char * const MFDSTC_DICORE_DITRACER = "SOFTWARE\\DST\\MFDSTC\\DICORE\\DITracer";
   const char * const MFDSTC_JNIJVM = "SOFTWARE\\DST\\MFDSTC\\JNIJVM";
   const char * const MFDSTC_LOCALEFORMATS = "SOFTWARE\\DST\\MFDSTC\\LocaleFormats";
   const char * const MFDSTC_MFDSTC = "SOFTWARE\\DST\\MFDSTC\\MFDSTC";
   const char * const MFDSTC_SESSION = "SOFTWARE\\DST\\MFDSTC\\Session";
   const char * const MFDSTC_USER = "SOFTWARE\\DST\\MFDSTC\\User";
   const char * const MFDSTC_VMREQUEST = "SOFTWARE\\DST\\MFDSTC\\VMRequest";
   const char * const MFDSTC_WORKSTATION = "SOFTWARE\\DST\\MFDSTC\\Workstation";

   const char * const TESESSION = "SOFTWARE\\DST\\TESession";
   const char * const TESESSION_EXTRAEAL = "SOFTWARE\\DST\\TESession\\ExtraEal";
   const char * const TESESSION_KEA = "SOFTWARE\\DST\\TESession\\KEA!";
   const char * const TESESSION_REFLECTION = "SOFTWARE\\DST\\TESession\\Reflection";
   const char * const TESESSION_STUB = "SOFTWARE\\DST\\TESession\\Stub";
   

}


bool checkOverride( HKEY hKey, const char* path ) {
   if( HKEY_LOCAL_MACHINE != hKey ) {
      return( false );
   }
   if( !stricmp( fake::MFDSTC, path ) ||
       !stricmp( fake::MFDSTC_ADMIN, path ) ||
       !stricmp( fake::MFDSTC_AWDINTERFACE, path ) ||
       !stricmp( fake::MFDSTC_CBO, path ) ||
       !stricmp( fake::MFDSTC_CONFIG, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_AWDTYPE, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_CSI, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_DATAPATH, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_DISPLAYMASKS, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_HOSTMASKS, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_MARKET, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_RTSHOST, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_SUPPORT, path ) ||
       !stricmp( fake::MFDSTC_CONFIG_TOOLTIPS, path ) ||
       !stricmp( fake::MFDSTC_DATABROKER, path ) ||
       !stricmp( fake::MFDSTC_DEFAULTWORKSTATION, path ) ||
       !stricmp( fake::MFDSTC_DICORE, path ) ||
       !stricmp( fake::MFDSTC_DICORE_DITRACER, path ) ||
       !stricmp( fake::MFDSTC_JNIJVM, path ) ||
       !stricmp( fake::MFDSTC_LOCALEFORMATS, path ) ||
       !stricmp( fake::MFDSTC_MFDSTC, path ) ||
       !stricmp( fake::MFDSTC_SESSION, path ) ||
       !stricmp( fake::MFDSTC_USER, path ) ||
       !stricmp( fake::MFDSTC_VMREQUEST, path ) ||
       !stricmp( fake::MFDSTC_WORKSTATION, path ) ||
       !stricmp( fake::DICORE, path ) ||
       !stricmp( fake::TESESSION, path ) ||
       !stricmp( fake::TESESSION_EXTRAEAL, path ) ||
       !stricmp( fake::TESESSION_KEA, path ) ||
       !stricmp( fake::TESESSION_REFLECTION, path ) ||
       !stricmp( fake::TESESSION_STUB, path ) ||
       !stricmp( fake::HLLAPI, path ) ||
       !stricmp( fake::HLLAPI_TCS, path ) ||
       !stricmp( fake::DST_DEBUG, path ) ||
       !stricmp( fake::DST, path ) 
       ) {
      return( true );
   }
   return( false );
}

DWORD getOverrideCount( const char* path ) {
   if( !stricmp( fake::MFDSTC_SESSION, path ) ) {
      return( 3 );
   }
   else if( !stricmp( path, fake::MFDSTC_ADMIN ) ) {
      return( 3 );
   }
   else if( !stricmp( path, fake::MFDSTC_CONFIG ) ) {
      return( 1 );
   }
   else if( !stricmp( path, fake::MFDSTC_USER ) || 
            !stricmp( path, fake::MFDSTC_WORKSTATION ) ) {
      return( 3 );
   }
   else if( !stricmp( path, fake::MFDSTC_AWDINTERFACE ) ||
            !stricmp( path, fake::MFDSTC_CBO ) ||
            !stricmp( path, fake::MFDSTC_DATABROKER ) ||
            !stricmp( path, fake::MFDSTC_DEFAULTWORKSTATION ) ||
            !stricmp( path, fake::MFDSTC_DICORE ) ||
            !stricmp( path, fake::MFDSTC_JNIJVM ) ||
            !stricmp( path, fake::MFDSTC_LOCALEFORMATS ) ||
            !stricmp( path, fake::MFDSTC_MFDSTC ) ||
            !stricmp( path, fake::MFDSTC_VMREQUEST ) ) {
      return( 3 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_AWDTYPE ) ) {
      return( 2 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_CSI ) ) {
      return( 3 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_DATAPATH ) ) {
      return( 5 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_DISPLAYMASKS ) ) {
      return( 3 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_HOSTMASKS ) ) {
      return( 3 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_MARKET ) ) {
      return( 1 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_RTSHOST ) ) {
      return( 2 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_SUPPORT ) ) {
      return( 19 );
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_TOOLTIPS ) ) {
      return( 1 );
   }
   else if ( !stricmp( path, fake::MFDSTC_DICORE_DITRACER ) ) {
      return( 5 );
   }
   else if ( !stricmp( path, fake::DICORE ) ) {
      return( 2 );
   }
   else if ( !stricmp( path, fake::TESESSION ) ) {
      return( 0 );
   }
   else if ( !stricmp( path, fake::TESESSION_EXTRAEAL ) ) {
      return( 4 );
   }
   else if ( !stricmp( path, fake::TESESSION_KEA ) ) {
      return( 4 );
   }
   else if ( !stricmp( path, fake::TESESSION_REFLECTION ) ) {
      return( 4 );
   }
   else if ( !stricmp( path, fake::TESESSION_STUB ) ) {
      return( 4 );
   }
   else if ( !stricmp( path, fake::HLLAPI ) ) {
      return( 0 );
   }
   else if ( !stricmp( path, fake::HLLAPI_TCS ) ) {
      return( 4 );
   }
   else if ( !stricmp( path, fake::DST_DEBUG ) ) {
      return( 2 );
   }
   return(0);
}

#define SET_OVERRIDE_STR( name, value ) \
   do { strcpy( ValueName, name );\
        *pdwcValueName = strlen( ValueName );\
        strcpy( (char*)ValueData, value );\
        *pdwcValueData = strlen( (char*)ValueData );\
        *pdwcValueType = REG_SZ; } while(false)

#define SET_OVERRIDE_DWORD( name, value ) \
   do { strcpy( ValueName, name );\
        *pdwcValueName = strlen( ValueName );\
        *((DWORD*)ValueData) = value;\
        *pdwcValueData = 4;\
        *pdwcValueType = REG_DWORD; } while(false)

void enumOverrideValue( const char* path,
                        DWORD i,
                        char* ValueName,
                        LPDWORD pdwcValueName,
                        LPDWORD pdwcValueType,
                        unsigned char* ValueData,
                        LPDWORD pdwcValueData ) 
{
   *pdwcValueType = *pdwcValueData = *pdwcValueName = 0;

   if( !stricmp( path, fake::MFDSTC_ADMIN ) ) {
      switch( i ) {
         case 0: SET_OVERRIDE_STR( "file", "Admin" ); break;
         case 1: SET_OVERRIDE_STR( "path", "\\config" ); break;
         case 2: SET_OVERRIDE_STR( "type", "Ini" ); break;
      }
   }
   else if( !stricmp( path, fake::MFDSTC_AWDINTERFACE ) ||
            !stricmp( path, fake::MFDSTC_CBO ) ||
            !stricmp( path, fake::MFDSTC_DATABROKER ) ||
            !stricmp( path, fake::MFDSTC_DEFAULTWORKSTATION ) ||
            !stricmp( path, fake::MFDSTC_DICORE ) ||
            !stricmp( path, fake::MFDSTC_JNIJVM ) ||
            !stricmp( path, fake::MFDSTC_LOCALEFORMATS ) ||
            !stricmp( path, fake::MFDSTC_MFDSTC ) ||
            !stricmp( path, fake::MFDSTC_VMREQUEST ) ) {
      switch( i ) {
         case 0: SET_OVERRIDE_DWORD( "hive", 2 ); break;
         case 1: SET_OVERRIDE_STR( "path", "SOFTWARE\\DST\\MFDSTC\\Config" ); break;
         case 2: SET_OVERRIDE_STR( "type", "Registry" ); break;
      }
   }
   else if( !stricmp( path, fake::MFDSTC_CONFIG ) ) {
      switch( i ) {
         case 0: SET_OVERRIDE_STR( "type", "Container" ); break;
      }
   }
   else if( !stricmp( path, fake::MFDSTC_USER ) || 
            !stricmp( path, fake::MFDSTC_WORKSTATION ) ) {
      switch( i ) {
         case 0: SET_OVERRIDE_DWORD( "hive", 1 ); break;
         case 1: SET_OVERRIDE_STR( "path", "SOFTWARE\\DST\\MFDSTC\\Config" ); break;
         case 2: SET_OVERRIDE_STR( "type", "Registry" ); break;
      }
   }
   else if( !stricmp( path, fake::MFDSTC_SESSION ) ) {
      switch( i ) {
         case 0: SET_OVERRIDE_STR( "file", "session" ); break;
         case 1: SET_OVERRIDE_STR( "path", "\\config" ); break;
         case 2: SET_OVERRIDE_STR( "type", "Group" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_AWDTYPE ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "InterfaceDll", "DIAWD23" ); break;
         case 1: SET_OVERRIDE_STR( "AutoLogon", "0" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_CSI ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "Host", "" ); break;
         case 1: SET_OVERRIDE_STR( "Param", "" ); break;
         case 2: SET_OVERRIDE_STR( "Type", "" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_DATAPATH ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "Path", "" ); break;
         case 1: SET_OVERRIDE_STR( "RepositorySource", "" ); break;
         case 2: SET_OVERRIDE_STR( "FYIFile", "" ); break;
         case 3: SET_OVERRIDE_STR( "InstallPath", "" ); break;
         case 4: SET_OVERRIDE_STR( "SysLoadPath", "" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_DISPLAYMASKS ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "enUS-D", "dd/MM/yyyy" ); break;
         case 1: SET_OVERRIDE_STR( "enUS-T", "HH:mm" ); break;
         case 2: SET_OVERRIDE_STR( "frCA-D", "dd/MM/yyyy" ); break;
         case 3: SET_OVERRIDE_STR( "deDE-D", "dd/MM/yyyy" ); break;
         case 4: SET_OVERRIDE_STR( "jaJP-T", "" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_HOSTMASKS ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "D", "MMddyyyy" ); break;
         case 1: SET_OVERRIDE_STR( "DN", "###################.##########" ); break;
         case 2: SET_OVERRIDE_STR( "T", "HH:mm" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_MARKET ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "Market", "" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_RTSHOST ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "DisplayConnectionIcon", "1" ); break;
         case 1: SET_OVERRIDE_STR( "VMHostName", "RTSCAN" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_SUPPORT ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "Log_Enable", "0" ); break;
         case 1: SET_OVERRIDE_STR( "Log_File", "" ); break;
         case 2: SET_OVERRIDE_STR( "LogPath", "." ); break;
         case 3: SET_OVERRIDE_STR( "ViewLog_Enable", "0" ); break;
         case 4: SET_OVERRIDE_STR( "ViewLog_Append", "1" ); break;
         case 5: SET_OVERRIDE_STR( "ViewLog_Complete", "1" ); break;
         case 6: SET_OVERRIDE_STR( "ViewLog_Path", "" ); break;
         case 7: SET_OVERRIDE_STR( "ViewLog_RawRequest", "0" ); break;
         case 8: SET_OVERRIDE_STR( "ViewLog_RawResponse", "0" ); break;
         case 9: SET_OVERRIDE_STR( "ViewTimeLog_Enable", "0" ); break;
         case 10: SET_OVERRIDE_STR( "ViewTimeLog_Path", ".\\" ); break;
         case 11: SET_OVERRIDE_STR( "ViewTimeLog_Size", "200000" ); break;
         case 12: SET_OVERRIDE_STR( "DisplayConnectionIcon", "1" ); break;
         case 13: SET_OVERRIDE_STR( "DisplayConditionName", "0" ); break;
         case 14: SET_OVERRIDE_STR( "ShowClientNamePane", "0" ); break;
         case 15: SET_OVERRIDE_STR( "ExceptionReport_Enable", "0" ); break;
         case 16: SET_OVERRIDE_STR( "ExceptionReport_Path", "" ); break;
         case 17: SET_OVERRIDE_STR( "ReportEmailAddress", "" ); break;
         case 18: SET_OVERRIDE_STR( "SpecialPasswordRules", "0" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_CONFIG_TOOLTIPS ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "Position", "Below" ); break;
      }
   }
   else if ( !stricmp( path, fake::MFDSTC_DICORE_DITRACER ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "File path", "" ); break;
         case 1: SET_OVERRIDE_STR( "Initial Value", "off" ); break;
         case 2: SET_OVERRIDE_STR( "IP Address", "127.0.0.1" ); break;
         case 3: SET_OVERRIDE_STR( "Output Device", "socket" ); break;
         case 4: SET_OVERRIDE_STR( "Port Number", "1552" ); break;
      }
   }
   else if ( !stricmp( path, fake::HLLAPI_TCS ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "HLLAPI_FUNCTION_CANCEL", "@d" ); break;
         case 1: SET_OVERRIDE_STR( "HLLAPI_FUNCTION_ESCAPE", "@e" ); break;
         case 2: SET_OVERRIDE_STR( "HLLAPI_HOTKEY_TEXT", "Attention" ); break;
         case 3: SET_OVERRIDE_STR( "HLLAPI_VENDOR", "EXTRA" ); break;
      }
   }
   else if ( !stricmp( path, fake::DICORE ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_STR( "mfdstc", "MFDSTC" ); break;
         case 1: SET_OVERRIDE_STR( "mfdstc_d", "MFDSTC" ); break;
      }
   }
   else if ( !stricmp( path, fake::TESESSION_EXTRAEAL ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_DWORD( "Capabilities", 0xffffffff ); break;
         case 1: SET_OVERRIDE_STR( "CreationImport", "CreateExtraEalSession" ); break;
         case 2: SET_OVERRIDE_STR( "ModuleName", "ExtraEalSession.dll" ); break;
         case 3: SET_OVERRIDE_STR( "ReleaseImport", "ReleaseExtraEalSession" ); break;
      }
   }
   else if ( !stricmp( path, fake::TESESSION_KEA ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_DWORD( "Capabilities", 0xffffffff ); break;
         case 1: SET_OVERRIDE_STR( "CreationImport", "CreateKEASession" ); break;
         case 2: SET_OVERRIDE_STR( "ModuleName", "KEASession.dll" ); break;
         case 3: SET_OVERRIDE_STR( "ReleaseImport", "ReleaseKEASession" ); break;
      }
   }
   else if ( !stricmp( path, fake::TESESSION_REFLECTION ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_DWORD( "Capabilities", 0xffffffff ); break;
         case 1: SET_OVERRIDE_STR( "CreationImport", "CreateReflectionSession" ); break;
         case 2: SET_OVERRIDE_STR( "ModuleName", "ReflectionSession.dll" ); break;
         case 3: SET_OVERRIDE_STR( "ReleaseImport", "ReleaseReflectionSession" ); break;
      }
   }
   else if ( !stricmp( path, fake::TESESSION_STUB ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_DWORD( "Capabilities", 0xffffffff ); break;
         case 1: SET_OVERRIDE_STR( "CreationImport", "CreateStubSession" ); break;
         case 2: SET_OVERRIDE_STR( "ModuleName", "StubSession.dll" ); break;
         case 3: SET_OVERRIDE_STR( "ReleaseImport", "ReleaseStubSession" ); break;
      }
   }
   else if ( !stricmp( path, fake::DST_DEBUG ) ) {
      switch(i) {
         case 0: SET_OVERRIDE_DWORD( "DisplayBeforeThrowLevel", 99 ); break;
         case 1: SET_OVERRIDE_DWORD( "AssertLevel", 99 ); break;
      }
   }
}


DWORD enumOverrideKey( const char* path, 
                       DWORD i, 
                       char* pszSubKeyName, 
                       DWORD buffSize ) 
{
   if( !stricmp( path, fake::MFDSTC ) ) {
      switch( i ) {
         case 0: strcpy( pszSubKeyName, "Admin" ); break;
         case 1: strcpy( pszSubKeyName, "AwdInterface" ); break;
         case 2: strcpy( pszSubKeyName, "CBO" ); break;
         case 3: strcpy( pszSubKeyName, "Config" ); break;
         case 4: strcpy( pszSubKeyName, "DataBroker" ); break;
         case 5: strcpy( pszSubKeyName, "DefaultWorkstation" ); break;
         case 6: strcpy( pszSubKeyName, "DICore" ); break;
         case 7: strcpy( pszSubKeyName, "LocaleFormats" ); break;
         case 8: strcpy( pszSubKeyName, "MFDSTC" ); break;
         case 9: strcpy( pszSubKeyName, "Session" ); break;
         case 10: strcpy( pszSubKeyName, "User" ); break;
         case 11: strcpy( pszSubKeyName, "VMRequest" ); break;
         case 12: strcpy( pszSubKeyName, "Workstation" ); break;
         case 13: strcpy( pszSubKeyName, "JNIJVM" ); break;
         default: return( ERROR_NO_MORE_ITEMS );
      }
   }
   else if( !stricmp( path, fake::DST ) ) {
      switch( i ) {
         case 0: strcpy( pszSubKeyName, "MFDSTC" ); break;
         case 1: strcpy( pszSubKeyName, "HLLAPI" ); break;
         case 2: strcpy( pszSubKeyName, "Debug" ); break;
         case 3: strcpy( pszSubKeyName, "TESESSION" ); break;
         default: return( ERROR_NO_MORE_ITEMS );
      }
   }
   else if( !stricmp( path, fake::MFDSTC_CONFIG ) ) {
      switch( i ) {
         case 0: strcpy( pszSubKeyName, "AwdType" ); break;
         case 1: strcpy( pszSubKeyName, "Csi" ); break;
         case 2: strcpy( pszSubKeyName, "DataPath" ); break;
         case 3: strcpy( pszSubKeyName, "DisplayMasks" ); break;
         case 4: strcpy( pszSubKeyName, "HostMasks" ); break;
         case 5: strcpy( pszSubKeyName, "Market" ); break;
         case 6: strcpy( pszSubKeyName, "RTSHost" ); break;
         case 7: strcpy( pszSubKeyName, "Support" ); break;
         case 8: strcpy( pszSubKeyName, "Tooltips" ); break;
         default: return( ERROR_NO_MORE_ITEMS );
      }
   }
   else if( !stricmp( path, fake::MFDSTC_DICORE ) ) {
      switch( i ) {
         case 0: strcpy( pszSubKeyName, "DITracer" ); break;
         default: return( ERROR_NO_MORE_ITEMS );
      }
   }
   else if( !stricmp( path, fake::HLLAPI ) ) {
      switch( i ) {
         case 0: strcpy( pszSubKeyName, "TCS" ); break;
         default: return( ERROR_NO_MORE_ITEMS );
      }
   }
   else if( !stricmp( path, fake::TESESSION ) ) {
      switch( i ) {
         case 0: strcpy( pszSubKeyName, "ExtraEal" ); break;
         case 1: strcpy( pszSubKeyName, "KEA" ); break;
         case 2: strcpy( pszSubKeyName, "Reflection" ); break;
         case 3: strcpy( pszSubKeyName, "Stub" ); break;
         default: return( ERROR_NO_MORE_ITEMS );
      }
   }
   else {
      return( ERROR_NO_MORE_ITEMS );
   }

   return( ERROR_SUCCESS );
}

int forceOnload()  
{
   RegistryKey::SetOverrideFunctions( checkOverride, getOverrideCount, enumOverrideValue, enumOverrideKey );
   return(0);
}

static int i = forceOnload();

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RegistryOverrides.cpp-arc  $
// 
//    Rev 1.4   Sep 27 2011 14:37:52   purdyech
// IN2647659.  Minimum length of password
// 
//    Rev 1.3   Dec 02 2010 07:15:56   purdyech
// Changes to implement view performance and crash-handling
// 
//    Rev 1.2   Nov 02 2010 16:06:18   purdyech
// Fixed some default issues for ZTS Migration.
// 
//    Rev 1.1   Dec 22 2009 06:25:40   dchatcha
// IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 * 
 */
