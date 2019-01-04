#pragma once

/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif
#ifndef COMMONTEMPLATES_H
   #include <commontemplates.h>
#endif
#ifndef REGISTRYVALUE_HPP
   #include <registryvalue.hpp>
#endif
#ifndef EVENTSEMAPHORE_HPP
   #include <eventsemaphore.hpp>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
#include <map>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif


// Pointer to Registry "CheckOverride" function
typedef bool (__cdecl *PFRCO)( HKEY hKey, const char* path );
// Pointer to Registry "GetOverrideCount" function
typedef DWORD (__cdecl *PFRGOC)( const char* path );
// Pointer to Registry "EnumOverrideValue" function
typedef void (__cdecl *PFREOV)( const char* path,
                                  DWORD i,
                                  char* ValueName,
                                  LPDWORD pdwcValueName,
                                  LPDWORD pdwcValueType,
                                  unsigned char* ValueData,
                                  LPDWORD pdwcValueData );
// Pointer to Registry "EnumOverrideKey" function
typedef DWORD (__cdecl *PFREOK) ( const char* path,
                                    DWORD i,
                                    char* pszSubKeyName,
                                    DWORD buffSize );


/**
 * This class represents a single key in the system registry.
 * A key may contain values and subkeys.  If a RegistyKey object
 * is created and there is no corresponding system registry key,
 * the object will have a null state.  This is allowed so that
 * new keys may be created in the system registry.  When the
 * saveKey() method is called, the key will be saved (created if
 * not already existing in the system registry).  In addition,
 * all values will be stored.  The only thing preventing a
 * successful save is the operator's ability to update the
 * system registry.
 */
class DICORE_LINKAGE RegistryKey
{

private:
   static PFRCO getPfnCheckOverride();
   static PFRGOC getPfnGetOverrideCount();
   static PFREOV getPfnEnumOverrideValue();
   static PFREOK getPfnEnumOverrideKey();

   // Pointer to Registry "CheckOverride" function
   static PFRCO s_pfnCheckOverride;
   // Pointer to Registry "GetOverrideCount" function
   static PFRGOC s_pfnGetOverrideCount;
   // Pointer to Registry "EnumOverrideValue" function
   static PFREOV s_pfnEnumOverrideValue;
   // Pointer to Registry "EnumOverrideKey" function
   static PFREOK s_pfnEnumOverrideKey;

   // public typedef's
public:
   static void LoadOverrideFunctions();
   static void SetOverrideFunctions( PFRCO pfnCO, PFRGOC pfnGOC, PFREOV pfnEOV, PFREOK pfnEOF );

   enum Hive
   {
      CLASSES_ROOT,
      CURRENT_USER,
      LOCAL_MACHINE,
      USERS,
      PERFORMANCE_DATA,
      CURRENT_CONFIG,
      DYN_DATA
   };

   typedef std::map<DStringA, RegistryValue, std::less<DStringA> >
   value_map;
   typedef value_map::value_type value_type;
   typedef value_map::const_iterator value_const_iterator;
   typedef value_map::iterator value_iterator;

   // Constructors & Destructor
public:
   /**
    * Constructor
    */
   RegistryKey();

   /**
    * Copy constructor
    *
    * @param copy
    */
   RegistryKey( const RegistryKey & copy );

   /**
    * Constructor
    *
    * @param path
    * @param hive
    */
   RegistryKey( const DStringA & path,
                Hive hive = LOCAL_MACHINE );

   /**
    * Constructor
    *
    * @param machineName
    * @param path
    * @param hive
    */
   RegistryKey( const DStringA & machineName,
                const DStringA & path,
                Hive hive = LOCAL_MACHINE );

   /**
    * Destructor
    */
   virtual ~RegistryKey();

   // Public methods
public:

   /**
    * Getter for the machine name
    *
    * @return
    */
   const DStringA & getMachineName();

   /**
    * Getter for the path
    *
    * @return
    */
   const DStringA & getPath();

   /**
    * Getter for the hive
    *
    * @return
    */
   Hive getHive();

   /**
    * Sets this to point at a registry key on a
    * remote machine.
    *
    * @param machineName
    * @param path
    * @param hive
    */
   void setRemotePath( const DStringA & machineName,
                       const DStringA & path,
                       Hive hive = LOCAL_MACHINE );

   /**
    * Setter for the path
    *
    * @param path
    */
   void setPath( const DStringA & path );

   /**
    * Setter for the path
    *
    * @param path
    */
   void setPath( const DStringA & path, Hive hive );

   /**
    * Sets the key to point at the subkey passed in.
    *
    * @param subKeyName
    */
   void setToSubKey( const DStringA & subKeyName );

   /**
    * Returns a RegistryKey object constructed as a subkey
    *
    * @param subKeyName
    *
    * @return
    */
   RegistryKey getSubKey( const DStringA & subKeyName );

   /**
    * Returns a RegistryKey object corresponding
    * to the name passed in.
    *
    * @param subKeyName
    *
    * @return
    */
   RegistryValue getValue( const DStringA & subKeyName );

   /**
    * Stores a RegistryValue object in this.
    * The system registry will be updated when
    * the method saveKey() is called.
    *
    * @param value
    */
   void setValue( const RegistryValue & value );

   /**
    * Deletes the subkey named from the system registry
    *
    * @param name
    * @return
    */
   bool deleteSubKey( const DStringA & name );

   /**
    * Deletes the named value from the system registry
    *
    * @param name
    * @return
    */
   bool deleteValue( const DStringA & name );

   /**
    * Updates the registry
    *
    * @return
    */
   bool saveKey();

   /**
    * Refreshes this object from the registry
    */
   void refresh();

   /**
    * Returns when either the event semaphore passed
    * in is posted or when the the system registry
    * key this represents changes.
    *
    * @param stopWaiting
    * @return
    */
   bool waitForChange( EventSemaphore & stopWaiting );

   /**
    *
    * @return an iterator which points at the beginning of the
    *         value list.  When de-referenced, the iterator
    *         returns a 'pair', where the member 'first' will be
    *         the RegistryValue's name and the member 'second'
    *         will be the RegistryValue object.
    */
   value_const_iterator getValueListBegin();

   /**
    *
    * @return an iterator which points at the end of the
    *         value list
    */
   value_const_iterator getValueListEnd();

   /**
    *
    * @return an iterator which points at the beginning of the
    *         key list
    */
   string_vector_const_iterator getKeyListBegin();

   /**
    *
    * @return an iterator which points at the end of the
    *         key list
    */
   string_vector_const_iterator getKeyListEnd();

   /**
    * Assignment operator
    *
    * @param copy
    * @return
    */
   RegistryKey & operator=( const RegistryKey & copy );

   /**
    * Getter for the isNull flag
    *
    * @return
    */
   bool isNull();

   // methods
private:
   void closeKeys();
   void openKey( unsigned long access );
   void clearValuesAndKeys();
   void getValueList();
   void getKeyList();
   unsigned long hKeyFromHive();

   // attributes
private:
   bool             _bFake;
   void           * _hKey;
   void           * _hRemoteKey;
   DStringA         _machineName;
   DStringA         _path;
   string_vector    _keyList;
   value_map        _valueMap;
   value_map        _newValues;
   Hive             _hive;
   bool             _isNull;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/iFastAWD/inc/registrykey.hpp-arc  $
//
//   Rev 1.1   Nov 02 2011 04:44:24   purdyech
//Registry Cleanup
//
//   Rev 1.2   Oct 06 2009 12:52:00   purdyech
//Provide freedom from the tyranny of the Registry.  Now has ability to override registry queries from calling application.
//
//   Rev 1.1   Oct 09 2002 17:42:12   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:02   SMITHDAV
//Initial revision.
//
//    Rev 1.7   30 Oct 2000 16:37:14   dt14177
// cleanup
//
//    Rev 1.6   Feb 22 1999 13:20:14   DMUM
// Move back to TIP
//
//    Rev 1.4   Feb 22 1999 07:34:34   DMUM
// Re-added Linkage macros
//
//    Rev 1.3   Feb 22 1999 07:22:04   DMUM
// making Registry Classes public again for 1700
//
//    Rev 1.2   18 Feb 1999 10:38:48   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:03:36   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:53:02   DMUM
//
//
//    Rev 1.4   10 Nov 1997 15:01:32   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.3   20 Jun 1997 07:34:48   dmum
// Further documentation
//
//    Rev 1.2   11 Jun 1997 08:39:12   dmum
// Documented methods
//
//    Rev 1.1   May 29 1997 09:08:20   dmum
// Changed order of enumeration to match windows definition
//
//    Rev 1.0   May 22 1997 15:35:30   dmum
//
//
//
