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
// ^FILE   : RegistryKey.cpp
// ^AUTHOR : Michael McGarry & Mike Ward
// ^DATE   : 19 May 97
//
// ----------------------------------------------------------
//
// ^CLASS    : RegistryKey
//
// ^MEMBER VARIABLES :
//    void           *_hKey         - handle to the registry key
//    void           *_hRemoteKey   - handle to root key on remote pc
//    string          _machineName  - name of remote pc
//    string          _path         - path of the key
//    string_vector   _keyList      - list of subkeys
//    value_map       _valueMap     - list of values and their names
//    value_map       _newValues    - list of values added by application
//    Hive            _hive         - enum representing a root key
//    bool            _isNull       - true if object does not point to a key
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DICORE_DLL
#include <srcprag.h>
#include <registrykey.hpp>
#include <dicore.h>
#include <symbols.h>

bool checkOverride( HKEY hKey, const char* path ) {
   return( false );
}

DWORD getOverrideCount( const char* path ) {
   return(0);
}

#define SET_OVERRIDE_STR( name, value ) \
   do { strcpy( ValueName, name );\
        *pdwcValueName = strlen( ValueName );\
        strcpy( (char*)ValueData, value );\
        *pdwcValueData = strlen( (char*)ValueData );\
        *pdwcValueType = REG_SZ; } while(false)

void enumOverrideValue( const char* path,
                        DWORD i,
                        char* ValueName,
                        LPDWORD pdwcValueName,
                        LPDWORD pdwcValueType,
                        unsigned char* ValueData,
                        LPDWORD pdwcValueData ) 
{
   *pdwcValueType = *pdwcValueData = *pdwcValueName = 0;
}

DWORD enumOverrideKey( const char* path, 
                       DWORD i, 
                       char* pszSubKeyName, 
                       DWORD buffSize ) 
{
   return( ERROR_NO_MORE_ITEMS );
}

void RegistryKey::SetOverrideFunctions( PFRCO pfnCO, PFRGOC pfnGOC, PFREOV pfnEOV, PFREOK pfnEOK ) {
   s_pfnCheckOverride = pfnCO;
   s_pfnGetOverrideCount = pfnGOC;
   s_pfnEnumOverrideValue = pfnEOV;
   s_pfnEnumOverrideKey = pfnEOK;
}

void __cdecl GetOverrideFunctions( PFRCO *pfnCO, PFRGOC *pfnGOC, PFREOV *pfnEOV, PFREOK *pfnEOK ) {
	*pfnCO = RegistryKey::s_pfnCheckOverride;
	*pfnGOC = RegistryKey::s_pfnGetOverrideCount;
	*pfnEOV = RegistryKey::s_pfnEnumOverrideValue;
	*pfnEOK = RegistryKey::s_pfnEnumOverrideKey;
}

PFRCO RegistryKey::getPfnCheckOverride() {
   if( NULL == s_pfnCheckOverride ) {
      s_pfnCheckOverride = checkOverride;
   }
   return( s_pfnCheckOverride );
}

PFRGOC RegistryKey::getPfnGetOverrideCount() {
   if( NULL == s_pfnGetOverrideCount ) {
      s_pfnGetOverrideCount = getOverrideCount;
   }
   return( s_pfnGetOverrideCount );
}

PFREOV RegistryKey::getPfnEnumOverrideValue() {
   if( NULL == s_pfnEnumOverrideValue ) {
      s_pfnEnumOverrideValue = enumOverrideValue;
   }
   return( s_pfnEnumOverrideValue );
}

PFREOK RegistryKey::getPfnEnumOverrideKey() {
   if( NULL == s_pfnEnumOverrideKey ) {
      s_pfnEnumOverrideKey = enumOverrideKey;
   }
   return( s_pfnEnumOverrideKey );
}

// Pointer to Registry "CheckOverride" function
PFRCO RegistryKey::s_pfnCheckOverride = NULL;
// Pointer to Registry "GetOverrideCount" function
PFRGOC RegistryKey::s_pfnGetOverrideCount = NULL;
// Pointer to Registry "EnumOverrideValue" function
PFREOV RegistryKey::s_pfnEnumOverrideValue = NULL;
// Pointer to Registry "EnumOverrideKey" function
PFREOK RegistryKey::s_pfnEnumOverrideKey = NULL;


static const int BUFF_SIZE = 255;

//******************************************************************************
//              Public Methods
//******************************************************************************

RegistryKey::RegistryKey()
: _machineName( "" )
{
   // Initialize internals
   _bFake      = false;
   _hive       = LOCAL_MACHINE;
   _isNull     = true;
   _hKey       = NULL;
   _hRemoteKey = NULL;
}

RegistryKey::RegistryKey( const RegistryKey &copy )
{
   this->operator=( copy );
}

RegistryKey::RegistryKey( const DStringA &path, Hive hive )
: _machineName( "" )
, _path( path )
{
   // Initialize internals
   _bFake      = false;
   _hive       = hive;
   _hKey       = NULL;
   _hRemoteKey = NULL;

   openKey( KEY_READ );
}

RegistryKey::RegistryKey(  const DStringA &machineName,
                           const DStringA &path,
                           Hive hive )
: _machineName( machineName ), _path( path )
{
   // Initialize internals
   _bFake      = false;
   _hive       = hive;
   _hKey       = NULL;
   _hRemoteKey = NULL;

   openKey( KEY_READ );
}

RegistryKey::~RegistryKey()
{
   closeKeys();
}

const DStringA &RegistryKey::getMachineName()
{
   return(_machineName);
}

const DStringA &RegistryKey::getPath()
{
   return(_path);
}

RegistryKey::Hive RegistryKey::getHive()
{
   return(_hive);
}

void RegistryKey::setRemotePath(  const DStringA &machineName,
                                  const DStringA &path,
                                  Hive hive )
{
   _machineName = machineName;
   _path         = path;
   _hive         = hive;

   clearValuesAndKeys();
   openKey( KEY_READ );
}

void RegistryKey::setPath( const DStringA &path )
{
   setPath( path, _hive );
}

void RegistryKey::setPath( const DStringA &path, Hive hive )
{
   _path = path;
   _hive = hive;

   clearValuesAndKeys();
   openKey( KEY_READ );
}

void RegistryKey::setToSubKey( const DStringA &name )
{
   _path += '\\';
   _path += name;

   clearValuesAndKeys();
   openKey( KEY_READ );
}

RegistryKey RegistryKey::getSubKey( const DStringA &name )
{
   DStringA subKey( _path );
   subKey += '\\';
   subKey += name;

   return(RegistryKey( _machineName, subKey, _hive ));
}

RegistryValue RegistryKey::getValue( const DStringA &name )
{
   // If we have not yet read the values get them.
   if( _valueMap.empty() )
   {
      getValueList();
   }

   // Search for the value
   value_const_iterator iter = _valueMap.find( name );

   // If not found, return an empty value
   if( iter == _valueMap.end() )
   {
      return(RegistryValue());
   }
   else
   {
      return( *iter ).second;
   }
}

void RegistryKey::setValue( const RegistryValue &value )
{
   // See if the value has already been stored
   value_iterator iter = _newValues.find( value.getName() );

   // Insert the value if new, override if already present.
   if( iter == _newValues.end() )
   {
      _newValues.insert( value_type( value.getName(), value ) );
   }
   else
   {
      ( *iter ).second = value;
   }

}

bool RegistryKey::deleteSubKey( const DStringA &name )
{
   // Initialize deleted to a failed state
   bool deleted = false;

   // Only precede if this is not null
   if( ! _isNull )
   {
      // Change access from read only to all access
      closeKeys();
      openKey( KEY_ALL_ACCESS );

      // Make sure we've opened the key
      if( ! _isNull )
      {
         LONG retCode;

         // Delete the subkey
         retCode = RegDeleteKey( ( HKEY )_hKey, name.c_str() );

         // If successfull, indicate so.
         if( retCode == ERROR_SUCCESS )
         {
            deleted = true;
         }
      }

      // Reset access to read only
      closeKeys();
      openKey( KEY_READ );
   }

   return(deleted);
}

bool RegistryKey::deleteValue( const DStringA &name )
{
   // Initialize deleted to a failed state
   bool deleted = false;

   // If we don't have a valu list yet, get it
   if( _valueMap.empty() )
   {
      getValueList();
   }

   // Search for the value
   value_iterator iter = _valueMap.find( name );

   // Only delete the value if it exists
   if( iter != _valueMap.end() )
   {
      // Change access from read only to all access
      closeKeys();
      openKey( KEY_ALL_ACCESS );

      // Make sure we've opened the key
      if( ! _isNull )
      {
         LONG retCode;

         // Delete the value
         retCode = RegDeleteValue( ( HKEY )_hKey, name.c_str() );

         // If successfull, indicate so and remove the value from the map
         if( retCode == ERROR_SUCCESS )
         {
            _valueMap.erase( iter );

            deleted = true;
         }
      }

      // Reset access to read only
      closeKeys();
      openKey( KEY_READ );
   }

   return(deleted);
}

bool RegistryKey::saveKey()
{
   LONG retCode;
   DWORD dwcDisp;

   // Close the keys if already open
   closeKeys();

   // Open the key with the create api
   if( _machineName.empty() )
   {
      // open local registry
      retCode = RegCreateKeyEx( (HKEY)hKeyFromHive(),
                                _path.c_str(),
                                0,
                                NULL,
                                REG_OPTION_NON_VOLATILE,
                                KEY_ALL_ACCESS,
                                NULL,
                                ( HKEY * )&_hKey,
                                &dwcDisp );
   }
   else
   {
      switch( _hive )
      {
         case USERS:
         case LOCAL_MACHINE:
            {
               // open remote registry
               char szName[64];

               strcpy( szName, _machineName.c_str() );

               retCode = RegConnectRegistry( szName,
                                             (HKEY)hKeyFromHive(),
                                             ( HKEY * )&_hRemoteKey );
            }

            // check open
            if( retCode == ERROR_SUCCESS )
            {
               retCode = RegCreateKeyEx( ( HKEY )_hRemoteKey,
                                         _path.c_str(),
                                         0,
                                         NULL,
                                         REG_OPTION_NON_VOLATILE,
                                         KEY_ALL_ACCESS,
                                         NULL,
                                         ( HKEY * )&_hKey,
                                         &dwcDisp );
            }
            break;

         default:
            retCode = ERROR_FILE_NOT_FOUND;
            break;
      }
   }

   if( retCode != ERROR_SUCCESS )
   {
      return(false);
   }


   // save the new values to the registry
   value_const_iterator iter = _newValues.begin();

   for( ; iter != _newValues.end(); ++iter )
   {
      RegistryValue value = ( *iter ).second;

      // Check value type
      switch( value.getType() )
      {
         case RegistryValue::STRING:
            {
               // Save as string
               DStringA strValue = value.getAsString();

               retCode = RegSetValueEx( ( HKEY )_hKey,
                                        value.getName().c_str(),
                                        0,
                                        REG_SZ,
                                        (const BYTE *)strValue.c_str(),
                                        strValue.length() );
            }
            break;

         case RegistryValue::DWORD:
            {
               // Save as DWORD
               unsigned long ulValue = value.getAsDWORD();

               retCode = RegSetValueEx( ( HKEY )_hKey,
                                        value.getName().c_str(),
                                        0,
                                        REG_DWORD,
                                        (const BYTE *)&ulValue,
                                        sizeof( ulValue ) );
            }
            break;
      }

      if( retCode != ERROR_SUCCESS )
      {
         return(false);
      }
   }

   refresh();

   return(true);
}

void RegistryKey::refresh()
{
   closeKeys();
   clearValuesAndKeys();
   openKey( KEY_READ );
}

bool RegistryKey::waitForChange( EventSemaphore &stopWaiting )
{
   const int EVENT_CHANGE = 0;
   const int EVENT_STOP   = 1;
   const int NUM_EVENTS   = 2;

   bool changed = false;

   if( ! _isNull )
   {
      // Create the array to pass the the api
      HANDLE hEvents[NUM_EVENTS];

      hEvents[EVENT_CHANGE] = CreateEvent( NULL, TRUE, FALSE, NULL );
      hEvents[EVENT_STOP] = stopWaiting.getHandle();

      if( hEvents[EVENT_CHANGE] && hEvents[EVENT_STOP] )
      {
         // Now wait
         RegNotifyChangeKeyValue( ( HKEY )_hKey,
                                  TRUE,
                                  REG_NOTIFY_CHANGE_LAST_SET,
                                  hEvents[EVENT_CHANGE],
                                  TRUE );

         // Why the the wait end
         switch( WaitForMultipleObjects( NUM_EVENTS,
                                         hEvents,
                                         FALSE,
                                         INFINITE ) )
         {
            // registry changed
            case EVENT_CHANGE:
               {
                  ResetEvent( hEvents[EVENT_CHANGE] );
                  changed = true;
               }
               break;

               // end signaled
            case EVENT_STOP:
               {
                  changed = false;
               }
               break;
         }
      }
   }

   return(changed);
}


RegistryKey::value_const_iterator RegistryKey::getValueListBegin()
{
   // If the value have not yet been read, get them
   if( _valueMap.empty() )
   {
      getValueList();
   }

   return(_valueMap.begin());
}

RegistryKey::value_const_iterator RegistryKey::getValueListEnd()
{
   // If the value have not yet been read, get them
   if( _valueMap.empty() )
   {
      getValueList();
   }

   return(_valueMap.end());
}

string_vector_const_iterator RegistryKey::getKeyListBegin()
{
   // If the key list has not yet been read, get it
   if( _keyList.empty() )
   {
      getKeyList();
   }

   return(_keyList.begin());
}

string_vector_const_iterator RegistryKey::getKeyListEnd()
{
   // If the key list has not yet been read, get it
   if( _keyList.empty() )
   {
      getKeyList();
   }

   return(_keyList.end());
}

RegistryKey &RegistryKey::operator=( const RegistryKey &copy )
{
   if( this != &copy )
   {
      this->_bFake       = copy._bFake;
      this->_machineName = copy._machineName;
      this->_path        = copy._path;
      this->_keyList     = copy._keyList;
      this->_valueMap    = copy._valueMap;
      this->_newValues   = copy._newValues;
      this->_hive        = copy._hive;
      this->_isNull      = copy._isNull;
      this->_hRemoteKey  = copy._hRemoteKey;
      this->_hKey        = copy._hKey;
   }

   return(*this);
}

bool RegistryKey::isNull()
{
   return(_isNull);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryKey::openKey
//
// ^DESCRIPTION : Opens the system registry and reads in the key.  If the
//                key does not exists in the system registry, or the operator
//                does not have the privileges for the access requested, then
//                _isNull will be set to true.
//
// ^PARAMETERS  :
//   ^^ unsigned long access - security access mask
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void RegistryKey::openKey( unsigned long access )
{
   //
   // Check to see if this key exists withing the registry
   //

   LONG retCode;
   _isNull = true;

   // if registry is already open, close it.
   closeKeys();

   if( _machineName.empty() )
   {
      // open local registry
      retCode = RegOpenKeyEx( (HKEY)hKeyFromHive(),// handle of open key
                              _path.c_str(),       // addr of name of subkey to open
                              NULL,                // reserved
                              access,              // security access mask
                              ( HKEY * )&_hKey );  // address of handle of open key
   }
   else
   {
      switch( _hive )
      {
         case USERS:
         case LOCAL_MACHINE:
            // open registry
            {
               char szName[64];

               strcpy( szName, _machineName.c_str() );

               retCode = RegConnectRegistry( szName,
                                             (HKEY)hKeyFromHive(),
                                             ( HKEY * )&_hRemoteKey );
            }
            // check open
            if( retCode == ERROR_SUCCESS )
               retCode = RegOpenKeyEx( ( HKEY )_hRemoteKey,
                                       _path.c_str(),
                                       NULL,
                                       access,
                                       ( HKEY * )&_hKey );
            break;

         default:
            retCode = ERROR_FILE_NOT_FOUND;
            break;
      }
   }

   // If successfull, set _isNull to false
   if( retCode == ERROR_SUCCESS ) {
      _isNull = false;
   } 
   else {
      // try to get it from our "Big List of Registry Key Values"
      if( (_bFake = (getPfnCheckOverride())((HKEY)hKeyFromHive(), _path.c_str()) ) ) {
         _isNull = false;
      }
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryKey::closeKeys
//
// ^DESCRIPTION : closes all open registry keys
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void RegistryKey::closeKeys()
{
   if( _hKey )
   {
      RegCloseKey( ( HKEY )_hKey );
      _hKey = NULL;
   }

   if( _hRemoteKey )
   {
      RegCloseKey( ( HKEY )_hRemoteKey );
      _hKey = NULL;
   }
   _bFake = false;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryKey::clearValuesAndKeys
//
// ^DESCRIPTION : Clears the three member objects:
//                   _newValues, _valueMap and _keyList
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void RegistryKey::clearValuesAndKeys()
{
   _newValues.erase( _newValues.begin(), _newValues.end() );
   _valueMap.erase( _valueMap.begin(), _valueMap.end() );
   _keyList.erase( _keyList.begin(), _keyList.end() );
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryKey::getValueList
//
// ^DESCRIPTION : Populates _valueMap with values from the registry key
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void RegistryKey::getValueList()
{
   if( _hKey || _bFake )
   {
      DWORD    i;
      DWORD    dwcValueType;
      DWORD    dwcValueName = BUFF_SIZE;
      DWORD    dwcValueData = BUFF_SIZE;
      DWORD    dwcValues;
      CHAR     ValueData[BUFF_SIZE];
      CHAR     ValueName[BUFF_SIZE];

      //
      // populate _valueMap
      //

      // Get Class name, Value count.
      if( _bFake ) {
         dwcValues = (getPfnGetOverrideCount())( getPath().c_str() );
      }
      else {
         RegQueryInfoKey( ( HKEY )_hKey,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           &dwcValues,
                           NULL,
                           NULL,
                           NULL,
                           NULL );
      }

      // Enumerate the Key Values
      for( i = 0; i < dwcValues; i++ )
      {

         // set length to default
         dwcValueName = dwcValueData = dwcValueType = BUFF_SIZE;

         // set data to NULL
         ValueName[0] = '\0';
         ValueData[0] = '\0';

         // get values
         if( _bFake ) {
            (getPfnEnumOverrideValue())( getPath().c_str(),
                       i,
                       ValueName,
                       &dwcValueName,
                       &dwcValueType,
                       ( unsigned char* ) ValueData,
                       &dwcValueData );
         }
         else {
            RegEnumValue( ( HKEY )_hKey,
                        i,
                        ValueName,
                        &dwcValueName,
                        NULL,
                        &dwcValueType,
                        ( unsigned char* ) ValueData,
                        &dwcValueData );
         }
         // create value
         RegistryValue value( ValueName );

         // check value type
         switch( dwcValueType )
         {
            case REG_SZ:
               {
                  DStringA strValue( (char *)ValueData );
                  value.set( strValue );
               }
               break;

            case REG_DWORD:
               {
                  unsigned long ulValue = *( unsigned long *) ValueData;
                  value.set( ulValue );
               }
               break;

            default:
               // not supported
               break;
         }

         // inset in value map
         _valueMap.insert( value_type( value.getName(), value ) );
      }
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryKey::getKeyList
//
// ^DESCRIPTION : Populates the vector _keyList with a list of subkeys
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void RegistryKey::getKeyList()
{
   if( _hKey || _bFake )
   {
      DWORD    retCode, i;
      char     szSubKeyName[BUFF_SIZE];

      //
      // populate _keyList
      //

      // Enumerate the Child Keys.
      bool bTriedFakes = _bFake;
      for( i = 0, retCode = ERROR_SUCCESS; retCode == ERROR_SUCCESS; i++ )
      {
         if( bTriedFakes ) {
            retCode = (getPfnEnumOverrideKey())( getPath().c_str(), i, szSubKeyName, BUFF_SIZE );
         }
         else {
            retCode = RegEnumKey( ( HKEY )_hKey, i, szSubKeyName, BUFF_SIZE );
         }

         // retCode will be ERROR_SUCCESS for each subkey enumerated
         if( retCode == ERROR_SUCCESS )
         {
            DStringA tmp( szSubKeyName );
            /*I_STRING subKey;
            asciistringToI_STRING( tmp, subKey );*/

            // Add the key name to the list (if it's not already in the list)
            bool bFound = false;
            for( string_vector_const_iterator it = _keyList.begin();
                 it != _keyList.end();
                 ++it ) {
               if( *it == DString(tmp) ) {
                  bFound = true;
                  break;
               }
            }
            if( !bFound ) {
               _keyList.push_back( tmp );
            }
         }
         else if( retCode == ERROR_NO_MORE_ITEMS && !bTriedFakes ) {
            i = -1;
            bTriedFakes = true;
            retCode = ERROR_SUCCESS;
         }
      }
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryKey::hKeyFromHive
//
// ^DESCRIPTION : This method converts the enumerated type Hive to a handle
//                representing the hive.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : unsigned long - HKEY for the hive
//
// ^THROWS      : none
//
//******************************************************************************
unsigned long RegistryKey::hKeyFromHive()
{
   HKEY hKey = HKEY_LOCAL_MACHINE;

   switch( _hive )
   {
      case USERS:
         hKey = HKEY_USERS;
         break;
      case CURRENT_CONFIG:
         hKey = HKEY_CURRENT_CONFIG;
         break;
      case CLASSES_ROOT:
         hKey = HKEY_CLASSES_ROOT;
         break;
      case CURRENT_USER:
         hKey = HKEY_CURRENT_USER;
         break;
      case LOCAL_MACHINE:
         hKey = HKEY_LOCAL_MACHINE;
         break;
      case DYN_DATA:
         hKey = HKEY_DYN_DATA;
         break;
      case PERFORMANCE_DATA:
         hKey = HKEY_PERFORMANCE_DATA;
         break;
   }

   return(unsigned long)hKey;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/ifdscore/win32/registrykey.cpp-arc  $
//
//   Rev 1.3   May 16 2011 07:49:26   purdyech
//Added GetOverrideFunctions for registry-less AWD support
//
//   Rev 1.2   Oct 06 2009 12:54:32   purdyech
//Provide freedom from the tyranny of the Registry.  Now has ability to override registry queries from calling application.
// 
//    Rev 1.1   Oct 09 2002 17:42:22   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Sep 07 2002 12:17:16   PURDYECH
// Initial revision.
// 
//    Rev 1.4   26 Feb 1999 15:06:20   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.3   22 Feb 1999 14:14:18   DT14177
// more UNICODE stuff
// 
//    Rev 1.2   18 Feb 1999 10:38:44   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:03:34   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.0   Dec 09 1998 13:52:32   DMUM
//  
//
//    Rev 1.8   10 Nov 1997 15:25:36   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.7   16 Sep 1997 07:59:00   dmum
// Added more detail to the condition when a key cannot be opened.
//
//    Rev 1.6   29 Aug 1997 13:37:54   dmum
// Changed DIREGCLS to DICORE
//
//    Rev 1.5   24 Jul 1997 09:57:16   dmum
// Added tracing
//
//    Rev 1.4   24 Jun 1997 13:48:20   dmum
// Added documentation
//
//    Rev 1.3   20 Jun 1997 07:35:26   dmum
// Documentation
//
//    Rev 1.2   13 Jun 1997 11:16:08   dmum
// Revised condition handling
//
//    Rev 1.1   13 Jun 1997 09:59:04   dmum
// Added condition
//
//    Rev 1.0   May 22 1997 15:33:38   dmum
//
//
//

