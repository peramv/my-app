#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#pragma message( "including "__FILE__ )

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef COMMONPORT_H
   #include "diport.h"
#endif

#ifndef TINSTANCEMANAGER_HPP
   #include "tinstancemanager.hpp"
#endif

#ifndef CONFIGURATION_HPP
   #include "configuration.hpp"
#endif

#ifndef DICORE_H
   #include "dicore.h"
#endif

#ifndef DICONFIGGLOBAL_H
   #include "diconfigglobal.h"
#endif

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef MUTEXSEMAPHORE_HPP
   #include "mutexsemaphore.hpp"
#endif

#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class ConfigBrokerObject;

/**
 * A ConfigManager object represents a single persistent source for
 * configuration data.
 *
 * To create an instance of this class, use the static method getManager().
 * Once instantiated, a ConfigManager object is used to retrieve Configuration
 * objects, to store them and to persist any changes that have been made.
 */
class DICORE_LINKAGE ConfigManager
{
   // Public methods
   public:
      /**
       * Returns a singleton for the named persistent source.
       *
       * If the first request for the named persistence, the
       * ConfigManager object is constructed.  The ConfigManager
       * constructor calls the method refresh() during construction.
       *
       * @param name - The name of the persistent source.
       *
       * @return pointer to the requested ConfigManager object.
       */
      static ConfigManager *getManager( const DString &name );

      /**
       * Creates a new instance of a named persistence source.
       *
       * @param name - The name of the persistent source.
       * @param type - The type of the persistent source. Types are:<br>
       *        1. CONTAINER - Container Manager with a set of reuseable
       *                       configurations.  Can be pointed to by multiple
       *                       managers.<br>
       *        2. REGISTRY - Type of Manager whose entire configuration is
       *                      in the registry.<br>
       *        3. INI      - Type of Manager whose configuration is in an
       *                      INI file.<br>
       *        4. GROUP    - A profile group.  It is implemented as a file is
       *                      can represent a group of INI and GROUP managers.<br>
       *        5. VIEW     - Not implemented
       * @param path - The path of persistence.  If creating a REGISTRY type
       *               manager, this parameter is used to identify the path in
       *               the NT registry where persistence resides.  If creating
       *               an INI type manager, this parameter is used to identify
       *               the path where the INI or GRP file resides.
       * @param fileName - Name of the INI or GRP file used.
       *
       * @return Pointer to ConfigManager object
       */
      static ConfigManager *createManager( const DString &name,
                                           const Config::Type &type,
                                           const DString &path,
                                           const DString &fileName,
                                           bool &created );

      /**
       * Permenently destroys a configuration manager
       *
       * @param name - The name of the manager to destroy
       *
       * @return bool - true indicates the destroy was successful.
       */
      static bool destroyManager( const DString &name );

      /**
       * Sets the current application.  This is used for finding the
       * ConfigManager objects when getManager() is called.
       *
       * @param name - the current application
       */
      static void setApplication( const DString &name );

      /**
       * Returns the current application that is being used to locate
       * ConfigManager objects when getManager() is called.
       *
       * @return The current application.
       */
      static const DString getApplication();

      /**
       * Sets the current company.  This defaults to DST.
       *
       * @param name - the current company
       */
      static void setCompany( const DString &name );

      /**
       * Refreshes the Configuration objects from the persistent source.
       *
       * @return true if successfully read
       *
       * @exception ConditionException - If this is undefined. See undefined()
       */
      bool refresh();

      /**
       * Saves the Configuration objects to the persistent source.
       *
       * @return true if successfully stored
       *
       * @exception ConditionException - If this is undefined.  See undefined()
       * @exception ConditionException - If cannot write to the persistent source.
       */
      bool persist();

      /**
       * Retrives the named Configuration object.
       *
       * @param configName - Nam of the Configuration object to be returned
       *
       * @return Configuration
       */
      Configuration retrieveConfig( const DString &configName );

      /**
       * Stores the Configuration object.  The collection of Configuration
       * objects are not saved to the persistent source until the method
       * persist() is called.
       *
       * @param config - the Configuration object to store.
       */
      void storeConfig( const Configuration &config );

      /**
       * Returns true if the peristent source is not defined.  That is, if the
       * ConfigManager object does not have a definition.  A definition is
       * required for each ConfigManager object that is intended for use.
       * On a Win32 platform, this definition exists in the system registry.
       *
       * @return true if the manager is NOT defined.
       */
      bool undefined();

      /**
       * Returns a list of names of all the configuration objects within this
       * manager.
       *
       * @return List of Configuration object names
       */
      string_vector configList();

      /**
       * This method is used to determine if the manager is a <i>profile group</i>.
       *
       * A <i>profile group</i> adds one more level of indirection for retrieving
       * configurable data.  This gives an application greater flexibility.
       * When a ConfigManager object is a profile group, it is actually a
       * collection of ConfigManager objects.  By changing profiles, a user
       * is really changing which manager this object represents.  Underlying
       * components using the same manager still see it as a collection of
       * Configuration objects.  The only impact is that when the underlying
       * component interacts with the manager to retreive the same configurable
       * data, the values returned may be different if the application switched
       * the profile.<p>
       *
       * Profile groups should only be manipulated at the application level.
       * Lower level compnents should only deal with getting and possibly
       * storing the configurable data itself.<p>
       *
       * In the following code sample, the <i>value</i> may be different after
       * the second call to fnGetValue().
       *
       * <pre>
       *  bool fnGetValue( DString &value )
       *  {
       *     bool success = false;
       *
       *     value = GetConfigValueAsSring( I_("Session"), I_("Use Awd"), I_("Use Awd") );
       *     success = ! value.empty();
       *
       *     return success;
       *  }
       *
       *  void main (int argc, char *argv[])
       *  {
       *     ConfigManager::setApplication( I_("TA2000") );
       *     ConfigManager *pManager = ConfigManager::getManager( "Session" );
       *
       *     // Make sure this is a profile group.
       *     if ( pManager->isProfileGroup() )
       *     {
       *        DString value;
       *
       *        std::cout << std::endl << "The value is ";
       *        std::cout << ( fnGetValue( value ) ? value : "<empty>" );
       *
       *        pManager->selectProfile( I_("DMUM Profile A") );
       *
       *        std::cout << std::endl << "The value is ";
       *        std::cout << ( fnGetValue( value ) ? value : "<empty>" );
       *     }
       *  }
       *</pre>
       *
       * @return True if the manager is a Profile Group
       */
      bool isProfileGroup();

      /**
       * If the manager is a profile group, this will return the list of the
       * profile names for this ConfigManager object.  See isProfileGroup()
       *
       * @return list of profile names
       */
      string_vector getProfileList();

      /**
       * If the manager is a profile group, this will return the name of the
       * profile that the manager currently represents.  See isProfileGroup()
       *
       * @return DString - The name of the current profile
       */
      DString getCurrentProfileName();

      /**
       * If the manager is a profile group, this will change the name of the
       * current profile and persist the new name.  See isProfileGroup()
       *
       * @param name - The new name for the current profile
       *
       * @return True if successfull
       */
      bool renameCurrentProfile( const DString &name );

      /**
       * This will return the filename (with extension) of the profile
       * identified by the name passed in. See isProfileGroup()
       *
       * @param name - Name of a profile to check
       *
       * @return File name - with extension
       */
      DString getFileNameForProfile( const DString &name );

      /**
       * If the manager is a profile group, this will change which profile the
       * manager represents and refresh itself. See isProfileGroup()
       *
       * @param name - Name of the profile to represent
       *
       * @return True if successfull
       */
      bool selectProfile( const DString &name );

      /**
       * If the manager is a profile group, this will create and add
       * a new profile to the group. See isProfileGroup()
       *
       * @param name - New profile name
       * @param file - New profile file name - without extension
       * @param type - Defaults to Config::INI_TYPE.
       *
       * @return bool True if successfull
       *
       * @exception ConditionException
       */
      bool createNewProfile( const DString &name,
                             const DString &file,
                             const Config::Type &type = Config::INI_TYPE );

      /**
       * If the manager is a profile group, this will create and add a new
       * profile; and copy the collection of configuration objects to the
       * new profile.
       *
       * @param newName - New profile name
       * @param newFile - New profile file name - without extension
       *
       * @return bool - True if successfull
       */
      bool createCopyProfile( const DString &newName,
                              const DString &newFile );

      /**
       * If the manager is a profile group, this will remove the named profile
       * from the group and perminently delete it. See isProfileGroup()
       *
       * @param name - Name of profile to delete
       *
       * @return True if successfull
       */
      bool deleteProfile( const DString &name );

      /**
       * If the manager is a profile group, this will return true if the
       * current profile represented by the manager is also a profile group.
       * The current profile would then be a sub group.  See isProfileGroup()
       *
       * @return bool - True if sub group
       */
      bool isCurrentProfileSubGroup() ;

      /**
       * If the manager is a profile group, this will determine if the named
       * profile is also a profile group.
       *
       * @param name - Name of profile to check
       *
       * @return True if sub group
       */
      bool isSubGroup( const DString &name );

      /**
       * If the manager is a profile group, and the current profile is also a
       * profile group, this will return a new <i>child</i> ConfigManager to
       * manage the sub group.  The new manager is then able to represent
       * any if its profiles.
       *
       * @return A ConfigManager pointer to the sub group
       */
      ConfigManager *getSubGroupManager();

   // Constructor and destructor
   private:
      ConfigManager( const DString &name );
      ConfigManager( const DString &name, const Configuration &definition );
      virtual ~ConfigManager();

   // Private methods
   private:
      static const DString &getCompany();
      static DString makeAppName( const DString &name );
      void newBrokerObject();
      void initMutex( const DString &name );
      bool create( const Config::Type &type,
                   const DString &path,
                   const DString &fileName );
      bool destroy();

      static void findApplication();
      static void deregister( void *pObj );
      static void deregisterStatics( void *pObj );

   // Private Members
   private:
      typedef TInstanceManager<DString, ConfigManager> InstanceManager;
      friend InstanceManager;

      SingletonRegister   m_register;
      ConfigBrokerObject *m_pBroker;
      manager_map         m_table;
      DString             m_appName;
      MutexSemaphore     *m_mutex;

      static InstanceManager    s_instanceManager;
      static DString           *s_pApplication;
      static DString           *s_pCompany;
      static SingletonRegister *s_pStaticsRegister;
};

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to retrieve
 * @param key           - Name of the key whose value you wish
 *                        to retrieve.
 *
 * @return The value as a string.
 */
DICORE_LINKAGE DString GetConfigValueAsString( const DString & configManager,
                                               const DString & configuration,
                                               const DString & key );

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to retrieve
 * @param key           - Name of the key whose value you wish
 *                        to retrieve.
 *
 * @return The value as an int.
 */
DICORE_LINKAGE int GetConfigValueAsInteger( const DString & configManager,
                                            const DString & configuration,
                                            const DString & key );

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to retrieve
 * @param key           - Name of the key whose value you wish
 *                        to retrieve.
 *
 * @return The value as a long.
 */
DICORE_LINKAGE long GetConfigValueAsLong( const DString & configManager,
                                          const DString & configuration,
                                          const DString & key );

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to retrieve
 * @param key           - Name of the key whose value you wish
 *                        to retrieve.
 *
 * @return The value as a double.
 */
DICORE_LINKAGE double GetConfigValueAsDouble( const DString & configManager,
                                              const DString & configuration,
                                              const DString & key );

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to update
 * @param key - Name of the key whose value you wish to update.
 * @param value - The data you wish to store.
 *
 * @return True if successfull
 */
DICORE_LINKAGE bool WriteConfigValue( const DString & configManager,
                                      const DString & configuration,
                                      const DString & key,
                                      const ConfigValue & value );

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to update
 * @param key - Name of the key whose value you wish to update.
 * @param value - The data you wish to store.
 *
 * @return True if successfull
 */
DICORE_LINKAGE bool WriteConfigValue( const DString & configManager,
                                      const DString & configuration,
                                      const DString & key,
                                      const DString & value );

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to update
 * @param key - Name of the key whose value you wish to update.
 * @param value - The data you wish to store.
 *
 * @return True if successfull
 */
DICORE_LINKAGE bool WriteConfigValue( const DString & configManager,
                                      const DString & configuration,
                                      const DString & key,
                                      const int    & value );

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to update
 * @param key - Name of the key whose value you wish to update.
 * @param value - The data you wish to store.
 *
 * @return True if successfull
 */
DICORE_LINKAGE bool WriteConfigValue( const DString & configManager,
                                      const DString & configuration,
                                      const DString & key,
                                      const long   & value );

/**
 * A common interface to get configuration data.  Performs the three
 * steps for getting the value
 *
 * @param configManager - Name of the configuration manager
 * @param configuration - Name of the configuration to update
 * @param key - Name of the key whose value you wish to update.
 * @param value - The data you wish to store.
 *
 * @return True if successfull
 */
DICORE_LINKAGE bool WriteConfigValue( const DString & configManager,
                                      const DString & configuration,
                                      const DString & key,
                                      const double & value );

//******************************************************************************
//              For DICORE use only
//******************************************************************************

/**
 * For DICORE use only
 */
DString GetElementalConfigValueAsString( const DString & configManager,
                                         const DString & configuration,
                                         const DString & key );

/**
 * For DICORE use only
 */
long GetElementalConfigValueAsLong( const DString & configManager,
                                    const DString & configuration,
                                    const DString & key );

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
// $Log:   Y:/VCS/iFastAWD/inc/configmanager.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:40   kovacsro
//Initial revision.
// 
//    Rev 1.17   23 Oct 2000 10:14:10   dt14177
// cleanup
// 
//    Rev 1.16   May 04 2000 16:15:18   DMUM
// Removed tdeletemap
//
//    Rev 1.15   Mar 29 2000 18:25:52   DMUM
// Removed Larry-code
//
//    Rev 1.14   Mar 24 2000 12:39:52   DMUM
// Sync up with 1.7 changes for thread safety and usage
// of SingletonRegister
//
//    Rev 1.13   Feb 23 2000 17:44:22   DMUM
// Updated comments
//
//    Rev 1.12   Jan 14 2000 17:51:14   DMUM
// Changing comments to javadoc format
//
//    Rev 1.11   Sep 30 1999 08:47:48   DMUM
// Made changes to make ConfigManager thread-safe
//
//    Rev 1.10   May 13 1999 09:16:46   DMUM
// Implementing "Elemental" mode of operation
//
//    Rev 1.9   Apr 27 1999 17:53:48   DMUM
// Changes for finding an application when setApplication()
// has not yet been found
//
//    Rev 1.8   04 Mar 1999 10:53:18   DT14177
// Fixed leftover diconfig.h file problem
//
//    Rev 1.7   22 Feb 1999 11:46:48   DT14177
// fixed DString and const I_CHAR stuff
//
//    Rev 1.6   18 Feb 1999 10:35:00   DT14177
// UNICODE
//
//    Rev 1.5   Jan 28 1999 14:05:44   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.4   Dec 09 1998 13:40:12   DMUM
// Check in for DICORE
//
//    Rev 1.3   Oct 01 1998 11:46:04   DMUM
// Added getApplication()
//
//    Rev 1.2   Aug 27 1998 09:54:14   DMUM
// Added a function and documented ProfileGroup methods
//
//    Rev 1.1   Aug 13 1998 09:05:04   DMUM
// added renameCurrentProfile()
//
//    Rev 1.0   29 Jul 1998 20:36:36   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.12   Jul 14 1998 08:03:06   dmum
// Added getFileNameForProfile()
//
//    Rev 1.11   Jul 13 1998 17:00:32   dmum
// More development
//
//    Rev 1.10   Jul 13 1998 12:22:32   dmum
// More development
//
//    Rev 1.9   Jul 11 1998 16:11:28   dmum
// Development - too many changes to describe
//
//    Rev 1.8   Jul 02 1998 12:02:18   dmum
// Cleanup
//
//    Rev 1.7   Nov 10 1997 13:48:04   DSZD
// removed incorrect include
//
//    Rev 1.6   Nov 10 1997 12:58:42   DSZD
// Configuration extension. IMPORT/EXPORT.
// MACRO inclusion
//
//    Rev 1.5   27 Aug 1997 10:41:24   dmum
// Changed how the application is treated and added company name
//
//    Rev 1.4   10 Jul 1997 09:41:48   dmum
// Added new method - configList
//
//    Rev 1.3   24 Jun 1997 13:46:34   dmum
// Added documentation
//
//    Rev 1.2   13 Jun 1997 12:26:18   dmum
// Added condition
//
//    Rev 1.1   11 Jun 1997 13:49:10   dmum
// Added parameter 'app' to getManager.  Also documented methods.
//
//    Rev 1.0   02 Jun 1997 12:26:14   dmum
//
//
//


#endif // CONFIGMANAGER_HPP

