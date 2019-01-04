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
// ^FILE   : ConfigManager.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 14 May 97
//
// ----------------------------------------------------------
//
// ^CLASS    : ConfigManager
//
// ^MEMBER VARIABLES :
//
//    manager_map   m_table     - map of configuration objects
//    string        m_appName   - application name plus manager's name
//    string        _path      - path to persistent source from definition
//    string        _fullPath  - complete path to persistent source
//
//    ConfigBrokerObject    *m_pBroker - manages configuration
//                                                  persistence
//
//    manager_map            m_table           - map of configuration objects
//    string                 m_appName         - application name plus manager's
//                                              name
//    static InstanceManager s_instanceManager - manages instances of
//                                              ConfigManager
//    static string          s_application     - application name
//    static string          s_company         - name of the company using the
//                                              manager
//
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef DIPORT_H
    #include "diport.h"
#endif
#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef CONFIGBROKEROBJECT_HPP
   #include "configbrokerobject.hpp"
#endif
#ifndef REGISTRYOBJECT_HPP
   #include "registryobject.hpp"
#endif
#ifndef DICORE_H
   #include "dicore.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif
#ifndef SYMBOLS_H
    #include "symbols.h"
#endif
#ifndef DATAPATH_H
   #include "datapath.h"
#endif
#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif

namespace
{
   const int UNKOWN_ERROR    = 3;
   const int SEMAPHORE_ERROR = 4;
}

MsgPair en_usConfigManager[] =
{
   {
      BASE_ALLOC_FAIL,
      I_("Machine is out of memory. There is insufficient disc space."),
      I_("Contact a support representative and report this message.")
   },
   {
      UNKOWN_ERROR,
      I_("Unkown Error."),
      I_("Contact a support representative and report this message.")
   },
   {
      SEMAPHORE_ERROR,
      I_("Semaphore Error."),
      I_("Contact a support representative and report this message.")
   }
};

Condition::mapCodePagesToLanguages languagesMapForConfigManager[] =
{
   {
      I_( "C" ), en_usConfigManager
   },

   // End slot marger
   {
      NULL, NULL
   }
};

//******************************************************************************
//              For ConfigManager use only
//******************************************************************************

class ElementalState
{
   public:
      ElementalState()
         : m_mutex( I_("elementalconfig"), true, 10000 )
      {
      }

      ~ElementalState()
      {
      }

      void setElemental()
      {
         CriticalSection crit( m_mutex );
         m_list.push_back( DSTGetCurrentThreadId() );
      }

      void resetElemental()
      {
         CriticalSection crit( m_mutex );

         const DWORD id = DSTGetCurrentThreadId();
         std::vector<DWORD>::iterator iter = m_list.begin();

         while ( iter != m_list.end() )
         {
            if ( id == *iter )
            {
               break;
            }

            ++iter;
         }

         if ( iter != m_list.end() )
         {
            m_list.erase( iter );
         }
      }

      bool isElemental()
      {
         CriticalSection crit( m_mutex );

         bool isElemental = false;

         const DWORD id = DSTGetCurrentThreadId();
         std::vector<DWORD>::iterator iter = m_list.begin();

         while ( iter != m_list.end() )
         {
            if ( id == *iter )
            {
               isElemental = true;
               break;
            }

            ++iter;
         }

         return isElemental;
      }

   private:
      std::vector<DWORD> m_list;
      MutexSemaphore m_mutex;
};

namespace Config
{
   ElementalState elemental;

   bool isElemental() { return elemental.isElemental(); }

   const I_CHAR *APP     = I_( "Default" );
   const I_CHAR *COMPANY = I_( "DST" );

   const I_CHAR MUTEX_STATIC[] = I_("_ConfigManager_Static_");
   const I_CHAR MUTEX[]        = I_("_ConfigManager_");
}

//******************************************************************************
//              Static member objects
//******************************************************************************

ConfigManager::InstanceManager  ConfigManager::s_instanceManager;

DString *ConfigManager::s_pApplication = NULL;
DString *ConfigManager::s_pCompany     = new DString( Config::COMPANY );

SingletonRegister *ConfigManager::s_pStaticsRegister =
              new SingletonRegister( ConfigManager::deregisterStatics, NULL );

//******************************************************************************
//              Public Methods
//******************************************************************************

ConfigManager *ConfigManager::getManager( const DString &name )
{
   MutexSemaphore mutex( Config::MUTEX_STATIC );
   CriticalSection crit( mutex );

   // Concatenate the application and name into appName
   DString appName = makeAppName( name );
   ConfigManager *pMgr = s_instanceManager.getInstance( appName );

   return pMgr;
}

ConfigManager *ConfigManager::createManager( const DString &name,
                                             const Config::Type &type,
                                             const DString &path,
                                             const DString &filename,
                                             bool &created )
{
   MutexSemaphore mutex( Config::MUTEX_STATIC );
   CriticalSection crit( mutex );

   ConfigManager *pMgr = NULL;
   created = false;

   if ( ! Config::isElemental() )
   {
      TRACE_METHOD( I_( "ConfigManager" ), I_( "getManager( const DString & )" ) )
      pMgr = getManager( name );

      if ( pMgr && pMgr->undefined() )
      {
         created = pMgr->create( type, path, filename );
      }
   }

   return pMgr;
}

bool ConfigManager::destroyManager( const DString &name )
{
   MutexSemaphore mutex( Config::MUTEX_STATIC );
   CriticalSection crit( mutex );

   bool destroyed = false;

   if ( ! Config::isElemental() )
   {
      TRACE_METHOD( I_( "ConfigManager" ), I_( "destroyManager( const DString & )" ) )

      // Concatenate the application and name into appName
      DString appName = makeAppName( name );
      ConfigManager *pMgr = s_instanceManager.removeInstance( appName );

      if ( pMgr )
      {
         if ( ! pMgr->undefined() )
         {
            destroyed = pMgr->destroy();
         }

         delete pMgr;
      }
   }

   return destroyed;
}

void ConfigManager::setCompany( const DString &name )
{
   MutexSemaphore mutex( Config::MUTEX_STATIC );
   CriticalSection crit( mutex );

   *s_pCompany = name.c_str();
}

void ConfigManager::setApplication( const DString &name )
{
   MutexSemaphore mutex( Config::MUTEX_STATIC );
   CriticalSection crit( mutex );

   if ( NULL == s_pApplication )
   {
      // Set the application here
      s_pApplication = new DString( name.c_str() );
   }
   else
   {
      // Set the application here
      *s_pApplication = name.c_str();
   }

   // Let the Condition Manager know the application too.
   g_conditionManager.setApplicationName( name.c_str() );
}

const DString ConfigManager::getApplication()
{
   MutexSemaphore mutex( Config::MUTEX_STATIC );
   CriticalSection crit( mutex );

   if ( NULL == s_pApplication )
   {
      findApplication();
   }

   DString str = s_pApplication->c_str();

   return str;
}

bool ConfigManager::refresh()
{
   CriticalSection crit( *m_mutex );

   if ( ! Config::isElemental() )
   {
      TRACE_METHOD( I_( "ConfigManager" ), I_( "refresh()" ) )
   }

   return m_pBroker->refresh();
}

bool ConfigManager::undefined()
{
   CriticalSection crit( *m_mutex );

   return m_pBroker->undefined();
}

bool ConfigManager::persist()
{
   CriticalSection crit( *m_mutex );

   if ( ! Config::isElemental() )
   {
      TRACE_METHOD( I_( "ConfigManager" ), I_( "persist()" ) )
   }

   return m_pBroker->persist();
}

Configuration ConfigManager::retrieveConfig( const DString &configName )
{
   CriticalSection crit( *m_mutex );

   // Find the Configuration object
   manager_const_iterator table_ptr = m_table.find( configName );

   if ( table_ptr == m_table.end() )
   {
      // if not found, return an empty Configuration object
      return Configuration( configName );
   }
   else
   {
      // found, return the Configuration object
      return ( *table_ptr ).second;
   }
}

void ConfigManager::storeConfig( const Configuration &config )
{
   CriticalSection crit( *m_mutex );

   // See if the Configuration object is already here
   manager_iterator table_ptr = m_table.find( config.getName() );

   if ( table_ptr == m_table.end() )
   {
      // Not found, insert it
      m_table.insert( manager_type( config.getName(), config ) );
   }
   else
   {
      // Found, repalce the existing object
      ( *table_ptr ).second = config;
   }
}

string_vector ConfigManager::configList()
{
   CriticalSection crit( *m_mutex );

   string_vector list;

   manager_const_iterator iter = m_table.begin();

   // Iterate through the map of Configuration objects
   for ( ; iter != m_table.end(); ++iter )
   {
      // Add the Configuration object's name to the list
      list.push_back( ( *iter ).first );
   }

   return list;
}

bool ConfigManager::isProfileGroup()
{
   CriticalSection crit( *m_mutex );

   return m_pBroker->isProfileGroup();
}

string_vector ConfigManager::getProfileList()
{
   CriticalSection crit( *m_mutex );

   return m_pBroker->getProfileList();
}

DString ConfigManager::getCurrentProfileName()
{
   CriticalSection crit( *m_mutex );

   return m_pBroker->getCurrentProfileName();
}

bool ConfigManager::renameCurrentProfile( const DString &name )
{
   CriticalSection crit( *m_mutex );

   bool success = false;

   if ( ! Config::isElemental() )
   {
      success = m_pBroker->renameCurrentProfile( name );
   }

   return success;
}

DString ConfigManager::getFileNameForProfile( const DString &name )
{
   CriticalSection crit( *m_mutex );

   return m_pBroker->getFileNameForProfile( name );
}

bool ConfigManager::selectProfile( const DString &group )
{
   CriticalSection crit( *m_mutex );

   bool success = false;

   success = m_pBroker->selectProfile( group );

   if ( success )
   {
      success = m_pBroker->refresh();
   }

   return success;
}

bool ConfigManager::createNewProfile( const DString &name,
                                      const DString &file,
                                      const Config::Type &type )
{
   CriticalSection crit( *m_mutex );

   bool success = false;

   if ( ! Config::isElemental() )
   {
      success = m_pBroker->createNewProfile( name, file, type );
   }

   return success;
}

bool ConfigManager::createCopyProfile( const DString &newName,
                                       const DString &newFile )
{
   CriticalSection crit( *m_mutex );

   bool success = false;

   if ( ! Config::isElemental() )
   {
      // Make sure we are a profile group and not a subgroup
      if ( m_pBroker->isProfileGroup() && ! m_pBroker->isCurrentProfileSubGroup() )
      {
         Config::Type type = Config::INI_TYPE;
         manager_map table = m_table;

         success = m_pBroker->createNewProfile( newName, newFile, type );

         if ( success )
         {
            m_table = table;

            success = m_pBroker->persist();
         }
      }
   }

   return success;
}

bool ConfigManager::deleteProfile( const DString &name )
{
   CriticalSection crit( *m_mutex );

   bool success = false;

   if ( ! Config::isElemental() )
   {
      success = m_pBroker->deleteProfile( name );
   }

   return success;
}

bool ConfigManager::isCurrentProfileSubGroup()
{
   CriticalSection crit( *m_mutex );

   return m_pBroker->isCurrentProfileSubGroup();
}

bool ConfigManager::isSubGroup( const DString &name )
{
   CriticalSection crit( *m_mutex );

   return m_pBroker->isSubGroup( name );
}

ConfigManager *ConfigManager::getSubGroupManager()
{
   CriticalSection crit( *m_mutex );

   ConfigManager *pMgr = NULL;

   // Make sure the current profile is a sub group
   if ( isCurrentProfileSubGroup() )
   {
      DString name = m_appName;
      name += ConfigBrokerObject::getDelimiter();
      name += getCurrentProfileName();

      // See if we already have one
      pMgr = getManager( name );

      if ( NULL == pMgr )
      {
         // Not found, create and add it.
         const Configuration &config = m_pBroker->getDefinition();

         pMgr = new ConfigManager( name, config );

         if ( ! pMgr )
         {
            if ( Config::isElemental() )
            {
               THROWELEMENTAL( DICORE_CONDITION,
                               I_( "ConfigManager::getSubGroupManager()" ),
                               BASE_ALLOC_FAIL,
                               languagesMapForConfigManager );
            }
            else
            {
               THROWFROMBASE( DICORE_CONDITION,
                              I_( "ConfigManager::getSubGroupManager()" ),
                              BASE_ALLOC_FAIL );
            }
         }

         s_instanceManager.addInstance( name, pMgr );
      }
   }

   return pMgr;
}


//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : ConfigManager::ConfigManager
//
// ^DESCRIPTION : Constuctor.  This is only called by InstanceManager
//
// ^PARAMETERS  :
//   ^^ const string &name - The applicatoin and name of the persistent source
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************
ConfigManager::ConfigManager( const DString &name )
   : m_register(),
     m_pBroker( NULL ),
     m_appName( name ),
     m_mutex( NULL )
{
   m_register.registerSingleton( deregister, this );
   initMutex( name );

   if ( ! Config::isElemental() )
   {
      TRACE_CONSTRUCTOR( I_( "ConfigManager" ),
                         I_( "ConfigManager( const DString & )" ) )
   }

   newBrokerObject();
   m_pBroker->refresh();
}

ConfigManager::ConfigManager( const DString &name,
                              const Configuration &definition  )
   : m_register(),
     m_pBroker( NULL ),
     m_appName( name ),
     m_mutex( NULL )
{
   m_register.registerSingleton( deregister, this );
   initMutex( name );

   m_pBroker = new ConfigBrokerObject( definition, m_table );
   m_pBroker->refresh();
}

//******************************************************************************
//
// ^PRIVATE METHOD      : ConfigManager::~ConfigManager
//
// ^DESCRIPTION : Destuctor.  This is only called by InstanceManager
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************
ConfigManager::~ConfigManager()
{
   if ( ! m_table.empty() )
   {
      m_table.erase( m_table.begin(), m_table.end() );
   }

   if ( m_pBroker )
   {
      delete m_pBroker;
      m_pBroker = NULL;
   }

   delete m_mutex;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : ConfigManager::getCompany
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : const string & -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
const DString &ConfigManager::getCompany()
{
   return *s_pCompany;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : ConfigManager::makeAppName
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ const string &name -
//
// ^RETURNS     : string -
//
// ^THROWS      : none
//
//******************************************************************************
DString ConfigManager::makeAppName( const DString &name )
{
   DString appName = getApplication().c_str();
   appName += ConfigBrokerObject::getDelimiter();
   appName += name;

   return appName;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : ConfigManager::newBrokerObject
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ bool isNew -
//
// ^RETURNS     : ConfigBrokerObject * -
//
// ^THROWS      : none
//
//******************************************************************************
void ConfigManager::newBrokerObject()
{
   switch ( ConfigBrokerObject::getOrigin() )
   {
      case ConfigBrokerObject::INI_FILE:
         m_pBroker = new ConfigBrokerObject( m_appName, m_table );
         break;

      case ConfigBrokerObject::REGISTRY:
      {
         const DString &str = getCompany();
         m_pBroker = new RegistryObject( m_appName, str, m_table );
         break;
      }
   }

   if ( ! m_pBroker )
   {
      if ( Config::isElemental() )
      {
         THROWELEMENTAL( DICORE_CONDITION,
                         I_( "ConfigManager::newBrokerObject()" ),
                         BASE_ALLOC_FAIL,
                         languagesMapForConfigManager );
      }
      else
      {
         THROWFROMBASE( DICORE_CONDITION,
                        I_( "ConfigManager::newBrokerObject()" ),
                        BASE_ALLOC_FAIL );
      }
   }
}

void ConfigManager::initMutex( const DString &name )
{
   DString strMutex( Config::MUTEX );
   strMutex += name;
   int size = strMutex.size();

   for ( int index = 0; index < size; ++index )
   {
      if ( '\\' == strMutex[index] )
      {
         strMutex[index] = '_';
      }
   }

   m_mutex = new MutexSemaphore( strMutex.c_str() );
}

//******************************************************************************
//
// ^PRIVATE METHOD      : ConfigManager::create
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ const string &name - The application and name of the persistent source
//   ^^ const int    &type - The type of persistence souce.  NOTE: only used
//                           when creating a new manager.
//   ^^ const string &filename - File name of persistence. Name of the *.INI
//                               file.
//                               NOTE: This parameter is used when creating a
//                                     VIEW type manager. It is used to specify
//                                     the 'retrieving' view.
//   ^^ const string &filepath - The path of persistence.  If creating a
//                               REGISTRY type manager, this parameter is used
//                               to identify the path in the NT registry where
//                               persistence resides.  If creating a INI
//                               type manager, this parameter is used to
//                               identify the path where it *.INI file resides.
//                               NOTE: This parameter is used when creating a
//                                     VIEW type manager. It is used to specify
//                                     the 'updating' view.
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************
bool ConfigManager::create( const Config::Type  &type,
                            const DString        &path,
                            const DString        &fileName  )
{
   bool success = false;

   if ( m_pBroker )
   {
      success = m_pBroker->create( type, path, fileName );
   }

   return success;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : ConfigManager::destroy
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : bool -
//
// ^THROWS      : none
//
//******************************************************************************
bool ConfigManager::destroy()
{
   bool destroyed = false;

   if ( m_pBroker )
   {
      destroyed = m_pBroker->destroy();
   }

   return destroyed;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : ConfigManager::findApplication
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void ConfigManager::findApplication()
{
   DString strApp = Config::APP;
   ::FindApplication( strApp );
   setApplication( strApp );
}

void ConfigManager::deregister( void *pObj )
{
   ConfigManager *pMgr = (ConfigManager *)pObj;
   pMgr = s_instanceManager.removeInstance( pMgr->m_appName );
   delete pMgr;
}

void ConfigManager::deregisterStatics( void *pObj )
{
   // Make sure there are no ConfigManager objects remaining.
   if ( 0 == s_instanceManager.size() )
   {
      delete s_pApplication;
      delete s_pCompany;
      delete s_pStaticsRegister;

      s_pApplication = NULL;
      s_pCompany = NULL;
      s_pStaticsRegister = NULL;
   }
   else
   {
      // de-register and then re-register
      delete s_pStaticsRegister;
      s_pStaticsRegister = new SingletonRegister( deregisterStatics, NULL );
   }
}

//******************************************************************************
//              Exported Functions
//******************************************************************************

DString GetConfigValueAsString( const DString &configManager,
                                const DString &configuration,
                                const DString &key )
{
   ConfigManager *pMgr = ConfigManager::getManager( configManager );

   if ( pMgr )
   {
      Configuration config = pMgr->retrieveConfig( configuration );
      return config.getValueAsString( key );
   }

   return NULL_STRING;
}

int GetConfigValueAsInteger( const DString &configManager,
                             const DString &configuration,
                             const DString &key )
{
   ConfigManager *pMgr = ConfigManager::getManager( configManager );

   if ( pMgr )
   {
      Configuration config = pMgr->retrieveConfig( configuration );
      return config.getValueAsInt( key );
   }

   return 0;
}

long GetConfigValueAsLong( const DString &configManager,
                           const DString &configuration,
                           const DString &key )
{
   ConfigManager *pMgr = ConfigManager::getManager( configManager );

   if ( pMgr )
   {
      Configuration config = pMgr->retrieveConfig( configuration );
      return config.getValueAsLong( key );
   }

   return 0;
}

double GetConfigValueAsDouble( const DString &configManager,
                               const DString &configuration,
                               const DString &key )
{
   ConfigManager *pMgr = ConfigManager::getManager( configManager );

   if ( pMgr )
   {
      Configuration config = pMgr->retrieveConfig( configuration );
      return config.getValueAsDouble( key );
   }

   return 0.0;
}

bool WriteConfigValue( const DString &configManager,
                       const DString &configuration,
                       const DString &key,
                       const ConfigValue &value )
{
   bool success = false;

   ConfigManager *pMgr = ConfigManager::getManager( configManager );
   Configuration config;

   if ( pMgr && ( ! pMgr->undefined() ) )
   {
      Configuration config = pMgr->retrieveConfig( configuration );
      config.set( key, value );
      pMgr->storeConfig( config );
      success = pMgr->persist();
   }

   return success;
}

bool WriteConfigValue( const DString &configManager,
                       const DString &configuration,
                       const DString &key,
                       const DString &value )
{
   ConfigValue configValue( value );
   return WriteConfigValue( configManager, configuration, key, configValue );
}

bool WriteConfigValue( const DString &configManager,
                       const DString &configuration,
                       const DString &key,
                       const int    &value )
{
   ConfigValue configValue( value );
   return WriteConfigValue( configManager, configuration, key, configValue );
}

bool WriteConfigValue( const DString &configManager,
                       const DString &configuration,
                       const DString &key,
                       const long   &value )
{
   ConfigValue configValue( (int)value );
   return WriteConfigValue( configManager, configuration, key, configValue );
}

bool WriteConfigValue( const DString &configManager,
                       const DString &configuration,
                       const DString &key,
                       const double &value )
{
    I_CHAR buffer[32];

    i_sprintf( buffer, I_( "%f" ), value );
    DString strValue( buffer );
    ConfigValue configValue( strValue );
    return WriteConfigValue( configManager, configuration, key, strValue );
}

//******************************************************************************
//              For DICORE use only
//******************************************************************************

DString GetElementalConfigValueAsString( const DString &configManager,
                                         const DString &configuration,
                                         const DString &key )
{
   DString strValue( I_( "" ) );
   Config::elemental.setElemental();

   try
   {
      ConfigManager *pMgr = ConfigManager::getManager( configManager );

      if ( pMgr )
      {
         Configuration config = pMgr->retrieveConfig( configuration );
         strValue = config.getValueAsString( key );
      }
   }
   catch ( ConditionException &ce )
   {
      Config::elemental.resetElemental();

      throw ce;
   }
   catch ( ... )
   {
      Config::elemental.resetElemental();

      THROWELEMENTAL( DICORE_CONDITION,
                      I_( "ConfigManager::getSubGroupManager()" ),
                      UNKOWN_ERROR,
                      languagesMapForConfigManager );
   }

   Config::elemental.resetElemental();

   return strValue;
}

long GetElementalConfigValueAsLong( const DString &configManager,
                                    const DString &configuration,
                                    const DString &key )
{
   long value = 0;
   Config::elemental.setElemental();

   try
   {
      ConfigManager *pMgr = ConfigManager::getManager( configManager );

      if ( pMgr )
      {
         Configuration config = pMgr->retrieveConfig( configuration );
         value = config.getValueAsLong( key );
      }
   }
   catch ( ConditionException &ce )
   {
      Config::elemental.resetElemental();

      throw ce;
   }
   catch ( ... )
   {
      Config::elemental.resetElemental();

      THROWELEMENTAL( DICORE_CONDITION,
                      I_( "ConfigManager::getSubGroupManager()" ),
                      UNKOWN_ERROR,
                      languagesMapForConfigManager );
   }

   Config::elemental.resetElemental();

   return value;
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
// $Log:   Y:/VCS/iFastAWD/dicore/configmanager.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:26   kovacsro
// Initial revision.
// 
//    Rev 1.14   Sep 15 2000 12:55:24   DT21858
// Fixed bug where an assignment was accidentally being
// used in place of a comparison.
//
//    Rev 1.13   Mar 29 2000 18:25:50   DMUM
// Removed Larry-code
//
//    Rev 1.12   Mar 24 2000 12:26:40   DMUM
// Now uses SingletonRegister
//
//    Rev 1.11   23 Feb 2000 16:09:54   dt20842
// Removed SET_APPNAME macro and replaced the equivalent
// line of code
//
//    Rev 1.10   Oct 05 1999 08:59:54   DMUM
// Fixed unicode build.
//
//    Rev 1.9   Sep 30 1999 08:47:46   DMUM
// Made changes to make ConfigManager thread-safe
//
//    Rev 1.8   May 14 1999 12:18:58   DMUM
// Made the "Elemental" mode thread/server safe
//
//    Rev 1.7   May 13 1999 09:16:28   DMUM
// Implementing "Elemental" mode of operation
//
//    Rev 1.6   Apr 27 1999 17:54:08   DMUM
// Changes for finding an application when setApplication()
// has not yet been found
//
//    Rev 1.5   26 Feb 1999 15:05:50   DT14177
// Integrate DIBASE and DICONFIG into DICORE
//
//    Rev 1.4   24 Feb 1999 10:44:04   DT14177
// sync up with tracer
//
//    Rev 1.3   22 Feb 1999 13:57:20   DT14177
// more UNICODE stuff
//
//    Rev 1.2   18 Feb 1999 10:34:40   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:02:34   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:50:58   DMUM
//
//
//    Rev 1.2   Aug 27 1998 09:54:36   DMUM
// Added function
//
//    Rev 1.1   Aug 13 1998 11:36:10   DMUM
// added renameCurrentProfile()
//
//    Rev 1.0   29 Jul 1998 20:30:08   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.17   Jul 14 1998 08:03:18   dmum
// Added getFileNameForProfile()
//
//    Rev 1.16   Jul 13 1998 17:01:02   dmum
// More development
//
//    Rev 1.15   Jul 13 1998 12:22:42   dmum
// More development
//
//    Rev 1.14   Jul 11 1998 16:08:00   dmum
// Development - too many changes to describe
//
//    Rev 1.13   Jul 02 1998 12:03:02   dmum
// Cleanup
//
//    Rev 1.12   Nov 10 1997 13:49:08   DSZD
// Support for incorrect include.
//
//    Rev 1.11   Nov 10 1997 13:02:54   DSZD
// Configuration extension. IMPORT/EXPORT.
// MACRO inclusion
//
//    Rev 1.10   08 Oct 1997 11:54:36   dmum
// Changed the registry location where "_global" is defined
//
//    Rev 1.9   10 Sep 1997 15:04:32   dmum
// Now calls Condition Manager to let it know the application name
//
//    Rev 1.8   28 Aug 1997 12:49:42   dmum
// Changed the default application name
//
//    Rev 1.7   27 Aug 1997 10:42:44   dmum
// Changed how the application is treated and added company name
//
//    Rev 1.6   24 Jul 1997 10:03:24   dmum
// Added Tracing
//
//    Rev 1.5   18 Jul 1997 08:11:28   dmum
// Handles the registry a little different now
//
//    Rev 1.4   10 Jul 1997 09:41:00   dmum
// Added new method - configList
//
//    Rev 1.3   24 Jun 1997 13:47:18   dmum
// Added documentation
//
//    Rev 1.2   13 Jun 1997 12:27:22   dmum
// Added condition
//
//    Rev 1.1   11 Jun 1997 13:50:12   dmum
// Added parameter 'app' to getManager() and the logic to support it.
//
//    Rev 1.0   02 Jun 1997 12:31:12   dmum
//
//
//

