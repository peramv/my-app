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
// ^FILE   : RegistryObject.cpp
// ^AUTHOR : Steve Doolittle
// ^DATE   : 10 Oct 97
//
// ----------------------------------------------------------
//
// ^CLASS    : RegistryObject
//
// ^MEMBER VARIABLES :
//
//
//    unsigned long      m_hive        - Current registry hive
//    string             m_fullIniPath - Full Ini path for m_pGlobalIni
//    string             m_path        - Same as m_fullPath
//    string             m_file        - file set in the "file"
//    string             m_fullPath    - Registry full path
//    ConfigBrokerObject *_pGlobalIni - Ini file pointed to by the registry
//
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef STDINCLUDE_H
   #include "stdinclude.h"
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

#ifndef REGISTRYOBJECT_HPP
   #include "registryobject.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DATAPATH_H
   #include "datapath.h"
#endif

#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif

#ifndef _WIN32

   #ifndef INCLUDED_STDLIB_H
      #define INCLUDED_STDLIB_H
      #include <stdlib.h>
   #endif

#endif

namespace
{
   const I_CHAR * const SOFTWARE = I_( "SOFTWARE\\" );
   const char * const HIVE = "hive";
   const I_CHAR * const KEY_APP = I_( "App" );
   const I_CHAR * const IDI_GENERIC = I_( "GENERIC" );
}

namespace Config
{
   extern bool isElemental();
}

MsgPair en_usRegistryObject[] =
{
   {
      DICORE_DATAPATH_REG_NOT_DEFINED,
      I_("There is an internal problem. This workstation has not been ")
      I_("properly setup with the required registry entries!"),
      I_("Contact a support representative to verify install configuration.")
   },
   {
      DICORE_CANNOT_PERSIST_UNDEFINED_MGR,
      I_("There is an internal problem. Cannot persist an undefined ")
      I_("persistence."),
      I_("Contact a support representative to verify install configuration.")
   },
   {
      DICORE_READ_REGISTRY_FAIL,
      I_("There is an internal problem. Cannot read registry."),
      I_("Contact a support representative to verify install configuration.")
   },
   {
      DICORE_PERSIST_REGISTRY_FAIL,
      I_("There is an internal problem. Cannot persist registry.  %GENERIC%"),
      I_("Contact a support representative to verify install configuration ")
      I_("and operator registry privileges.")
   },
   {
      DICORE_LOCATION_NOT_DEFINED,
      I_("There is an internal problem. Persistent location not defined!"),
      I_("Contact a support representative to verify install configuration.")
   }
};

Condition::mapCodePagesToLanguages languagesMapForRegistryObject[] =
{
   {
      I_( "C" ), en_usRegistryObject
   },

   // End slot marger
   {
      NULL, NULL
   }
};


#ifdef _WIN32

   #include "registrykey.hpp"
   #include "registryvalue.hpp"

#endif

//******************************************************************************
//              Public Methods
//******************************************************************************

#ifdef _WIN32

RegistryObject::RegistryObject(  const DString &appName,
                                 const DString &company,
                                 manager_map &table )
: ConfigBrokerObject( table ),
m_pGlobalIni( NULL ),
m_company( company ),
m_hive( RegistryKey::LOCAL_MACHINE )
{
   setDefinition( appName );
}

#else

RegistryObject::RegistryObject(  const DString &appName,
                                 const DString &company,
                                 manager_map &table )
: ConfigBrokerObject( appName, table ),
m_pGlobalIni( NULL ),
m_company( company )
{
}

#endif

RegistryObject::~RegistryObject()
{
   if( m_pGlobalIni )
   {
      delete( m_pGlobalIni );
      m_pGlobalIni = NULL;
   }
}

#ifdef _WIN32

const Configuration &RegistryObject::getDefinition()
{
   if( m_pGlobalIni )
   {
      return(m_pGlobalIni->getDefinition());
   }
   else
   {
      return(m_definition);
   }
}

DString RegistryObject::getDataPath( const DString &application )
{
   DString dataPath;

   if( ! GetIniPath( dataPath, application, m_company ) )
   {
      GetApplicationPath( dataPath );
   }

   int pos = dataPath.length();

   if( 0 < --pos )
   {
      if( getDelimiter() == dataPath.substr( pos, 1 ) )
      {
         dataPath.erase( pos );
      }
   }

   return(dataPath);
}

bool RegistryObject::create( const Config::Type &type,
                             const DString &path,
                             const DString &fileName )
{
   TRACE_METHOD( I_( "RegistryObject" ),
                 I_( "create( const Config::Type &, " )
                 I_( "const DString &, const DString & )" ) )

   bool created = false;

   Config::Location location = getLocationFromType( type );
   DString strLocation = getValueForLocation( location );

   if( Config::UNDEFINED != location )
   {
      DString name = m_definition.getName();
      DString app  = m_definition.getValueAsString( KEY_APP );

      DString registryPath = buildApplicationPath( app );
      registryPath += getDelimiter();
      registryPath += name;

      // Add the definition to the registry
      RegistryKey definition( registryPath.asA(), RegistryKey::LOCAL_MACHINE );

      if( ! definition.saveKey() )
      {
         MAKEFRAMENOTRACE( DICORE_CONDITION, I_( "RegistryObject::create()" ) )

         // Could not open the registry
         DString idiMsg;
         addIDITagValue( idiMsg, IDI_GENERIC, registryPath );
         ADDCONDITIONFROMFILEIDI( DICORE_PERSIST_REGISTRY_FAIL, idiMsg );
      }
      else
      {
         DString registryPath = buildApplicationPath( app );
         registryPath += getDelimiter();

         if( ! path.empty() )
         {
            registryPath += path;
         }
         else
         {
            registryPath += name;
         }

         created = true;
         ConfigValue cvType( strLocation );
         ConfigValue cvPath( registryPath );
         ConfigValue cvFile( fileName );

         RegistryValue rvType( getTypeKey(), strLocation.asA() );
         definition.setValue( rvType );

         // if we are a container, we are done! If we are not a container,
         // then we need to continue
         if( Config::CONTAINER != location )
         {
            RegistryValue rvPath( getPathKey(), registryPath.asA() );

            if( Config::INI == location || Config::GROUP == location )
            {
               // We are a global persistence, remember the file
               RegistryValue rvFile( getFileKey(), fileName.asA() );
               definition.setValue( rvFile );

               // Change the stored value for the path
               rvPath.set( path );
               cvPath.set( path );

               // Build a full path to the file
               DString fullPath = getDataPath( app );

               if( ! path.empty() )
               {
                  if( getDelimiter() != path.substr( 0, 1 ) )
                  {
                     fullPath += getDelimiter();
                  }

                  fullPath += path;
               }

               // Build the full file name
               DString fullName = fileName;
               fullName += getExtension( location );

               ConfigValue cvPath( fullPath );
               ConfigValue cvFile( fullName );

               // Create the definition for the INI file
               Configuration config( name );
               config.set( getTypeKey(), cvType );
               config.set( getPathKey(), cvPath );
               config.set( getFileKey(), cvFile );

               m_table.insert( manager_type( name, config ) );

               m_pGlobalIni = new ConfigBrokerObject( config, m_table );

               try
               {
                  created = m_pGlobalIni->persist();
               }
               catch( ConditionException &ce )
               {
                  MAKEFRAMENOTRACE( DICORE_CONDITION,
                                    I_( "ConfigBrokerObject::create()" ) )

                  SETCONDITIONFROMEXCEPTION( ce )
                  created = false;
               }
            }
            else
            {
               // We are a registry entry, remember the hive
               RegistryValue rvHive( HIVE, RegistryKey::LOCAL_MACHINE );
               definition.setValue( rvHive );
            }

            definition.setValue( rvPath );

         } // not a container

         if( created )
         {
            created = definition.saveKey();

            if( created )
            {
               m_location = location;
               m_definition.set( getTypeKey(), cvType );
               m_definition.set( getPathKey(), cvPath );
               m_definition.set( getFileKey(), cvFile );
            }
            else
            {
               MAKEFRAMENOTRACE( DICORE_CONDITION,
                                 I_( "RegistryObject::create()" ) )
               // Could not open the registry
               DString idiMsg;
               addIDITagValue( idiMsg, IDI_GENERIC, registryPath );
               ADDCONDITIONFROMFILEIDI( DICORE_PERSIST_REGISTRY_FAIL, idiMsg )
            }
         }

      } // save the initial key

   } // not undefined

   return(created);
}

bool RegistryObject::destroy()
{
   TRACE_METHOD( I_( "RegistryObject" ),
                 I_( "destroy()" ) )
   
   bool destroyed = true;

   if( undefined() )
   {
      // No definition for the persistence, let someone know.

//CP This code is removed.  Dave Smith informs me that it causes unspecified errors in the
//CP BPServer - Chris Purdye 26Jun2001
//CP      MAKEFRAMENOTRACE( DICORE_CONDITION,
//CP                        I_( "RegistryObject::destroy()" ) );
//CP      ADDCONDITIONFROMFILE( DICORE_LOCATION_NOT_DEFINED );
   }
   else
   {
      DString name = m_definition.getName();
      DString app  = m_definition.getValueAsString( KEY_APP );

      DString registryPath = buildApplicationPath( app );

      clearDefinition();

      // Remove the Definition from the registry
      RegistryKey local( registryPath.asA(), m_hive/*RegistryKey::LOCAL_MACHINE*/ );

      destroyed = local.deleteSubKey( name );
   }

   return(destroyed);
}

bool RegistryObject::refresh()
{
   bool success = false;

   clearTable();

   switch( m_location )
   {
      case Config::REGISTRY:
      case Config::CONTAINER:
         success = refreshFromRegistry();
         break;

      case Config::GROUP:
      case Config::INI:
         success = refreshFromIniFile();
         break;

      case Config::VIEW:
         success = refreshFromView();
         break;

      default:
         m_location = Config::UNDEFINED;

//CP This code is removed.  Dave Smith informs me that it causes unspecified errors in the
//CP BPServer - Chris Purdye 26Jun2001
//CP         if ( ! Config::isElemental() )
//CP         {
//CP            // No definition for the persistence, let someone know.
//CP            MAKEFRAMENOTRACE( DICORE_CONDITION,
//CP                              I_( "RegistryObject::refresh()" ) );
//CP            ADDCONDITIONFROMFILE( DICORE_LOCATION_NOT_DEFINED );
//CP         }
         break;
   }

   return(success);
}

bool RegistryObject::persist()
{
   bool success = false;

   switch( m_location )
   {
      case Config::REGISTRY:
      case Config::CONTAINER:
         success = persistToRegistry();
         break;

      case Config::GROUP:
      case Config::INI:
         success = persistToIniFile();
         break;

      case Config::VIEW:
         success = persistToView();
         break;

      default:
         if( Config::isElemental() )
         {
            THROWELEMENTAL( DICORE_CONDITION,
                            I_( "RegistryObject::persist()" ),
                            DICORE_CANNOT_PERSIST_UNDEFINED_MGR,
                            languagesMapForRegistryObject );
         }
         else
         {
            THROWFROMFILE( DICORE_CONDITION,
                           I_( "RegistryObject::persist()" ),
                           DICORE_CANNOT_PERSIST_UNDEFINED_MGR );
         }
         break;
   }

   return(success);
}

bool RegistryObject::isProfileGroup()
{
   bool group = false;

   if( m_pGlobalIni )
   {
      group = m_pGlobalIni->isProfileGroup();
   }

   return(group);
}

string_vector RegistryObject::getProfileList()
{
   string_vector list;

   if( m_pGlobalIni )
   {
      list = m_pGlobalIni->getProfileList();
   }

   return(list);
}

DString RegistryObject::getCurrentProfileName()
{
   DString name;

   if( m_pGlobalIni )
   {
      name = m_pGlobalIni->getCurrentProfileName();
   }

   return(name);
}

bool RegistryObject::renameCurrentProfile( const DString &name )
{
   bool success = false;

   if( m_pGlobalIni )
   {
      success = m_pGlobalIni->renameCurrentProfile( name );
   }

   return(success);
}


DString RegistryObject::getFileNameForProfile( const DString &name )
{
   DString file;

   if( m_pGlobalIni )
   {
      file = m_pGlobalIni->getFileNameForProfile( name );
   }

   return(file);
}

bool RegistryObject::selectProfile( const DString &name )
{
   bool success = false;

   if( m_pGlobalIni )
   {
      success = m_pGlobalIni->selectProfile( name );
   }

   return(success);
}

bool RegistryObject::createNewProfile( const DString &name,
                                       const DString &file,
                                       const Config::Type &type )
{
   bool success = false;

   if( m_pGlobalIni )
   {
      success = m_pGlobalIni->createNewProfile( name, file, type );
   }

   return(success);
}

bool RegistryObject::deleteProfile( const DString &name )
{
   bool success = false;

   if( m_pGlobalIni )
   {
      success = m_pGlobalIni->deleteProfile( name );
   }

   return(success);
}

bool RegistryObject::isCurrentProfileSubGroup()
{
   bool subGroup = false;

   if( m_pGlobalIni )
   {
      subGroup = m_pGlobalIni->isCurrentProfileSubGroup();
   }

   return(subGroup);
}

bool RegistryObject::isSubGroup( const DString &name )
{
   bool subGroup = false;

   if( m_pGlobalIni )
   {
      subGroup = m_pGlobalIni->isSubGroup( name );
   }

   return(subGroup);
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void RegistryObject::setDefinition( const DString &appName )
{
   DString strType;
   DString strPath;
   DString strFile;

   int seperator = appName.find( getDelimiter() );
   DString app = appName.substr( 0, seperator );
   DString name = appName.substr( seperator + 1 );

   m_definition.setName( name );

   // Store the application
   ConfigValue cvApp( app );
   m_definition.set( KEY_APP, cvApp );

   DString registryPath = buildApplicationPath( app );
   RegistryKey diconfig( registryPath.asA() );

   // If the registry key for diconfig is null, then return.
   if( diconfig.isNull() )
   {
      if( ! Config::isElemental() )
      {
         MAKEFRAMENOTRACE( DICORE_CONDITION,
                           I_( "RegistryObject::" )
                           I_( "buildLocationInformation()" ) );
         ADDCONDITIONFROMFILE( DICORE_CANNOT_READ_DEFINITION );
      }
   }
   else
   {
      // Read the definition for the persistence
      registryPath += getDelimiter();
      registryPath += name;

      RegistryKey definition( registryPath.asA() );
      RegistryValue rvType = definition.getValue( getTypeKey() );
      RegistryValue rvPath = definition.getValue( getPathKey() );
      RegistryValue rvFile = definition.getValue( getFileKey() );
      RegistryValue rvHive = definition.getValue( HIVE );

      if( RegistryValue::STRING == rvType.getType() )
      {
         // Extract the type
         strType = rvType.getAsString();
      }

      if( RegistryValue::STRING == rvPath.getType() )
      {
         // Extract the path
         strPath = rvPath.getAsString();
      }

      if( RegistryValue::STRING == rvFile.getType() )
      {
         // Extract the file
         strFile = rvFile.getAsString();
      }
      else
      {
         // Default the file to the name if it is not defined
         strFile = name;
      }

      if( RegistryValue::DWORD == rvHive.getType() )
      {
         // Extract the hive, this is only used if the persistence is local
         m_hive = (RegistryKey::Hive) rvHive.getAsDWORD();
      }

      setLocation( strType );

      ConfigValue cvType( strType );
      ConfigValue cvPath( strPath );
      ConfigValue cvFile( strFile );

      m_definition.set( getTypeKey(), cvType );
      m_definition.set( getPathKey(), cvPath );
      m_definition.set( getFileKey(), cvFile );

      // See if we have a global persistance
      if( Config::INI == m_location || Config::GROUP == m_location )
      {
         DString iniPath = getDataPath( app );

         if( ! strPath.empty() )
         {
            if( getDelimiter() != strPath.substr( 0, 1 ) )
            {
               iniPath += getDelimiter();
            }

            iniPath += strPath;
         }

         strFile += getExtension( m_location );

         cvPath.set( iniPath );
         cvFile.set( strFile );

         Configuration definition( name );
         definition.set( getTypeKey(), cvType );
         definition.set( getPathKey(), cvPath );
         definition.set( getFileKey(), cvFile );

         // do something if this fails
         m_pGlobalIni = new ConfigBrokerObject( definition, m_table );
      }
   }
}

bool RegistryObject::refreshFromView()
{
   bool success = false;

   /* FUTURE: At some point a view will be sent to the       */
   /*         mainframe to retrieve configuration.           */

   return(success);
}

bool RegistryObject::persistToView()
{
   bool success = false;

   /* FUTURE: At some point a view will be sent to the       */
   /*         mainframe to update configuration.             */

   return(success);
}


//******************************************************************************
//              Private Methods
//******************************************************************************
//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryObject::buildApplicationPath
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ const DString &app -
//
// ^RETURNS     : DString -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
DString RegistryObject::buildApplicationPath( const DString &app )
{
   DString applicationPath = SOFTWARE;
   applicationPath += m_company;
   applicationPath += getDelimiter();
   applicationPath += app;

   return(applicationPath);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryObject::refreshFromRegistry
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : bool -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
bool RegistryObject::refreshFromRegistry()
{
   if( ! Config::isElemental() )
   {
      TRACE_METHOD( I_( "RegistryObject" ), I_( "refreshFromRegistry()" ) )
   }

   bool success = false;
   DString path = m_definition.getValueAsString( getPathKey() );

   // Open the registry
   RegistryKey local( path.asA(), m_hive );

   if( ! local.isNull() )
   {
      success = true;

      // Each sub key is a Configuration object
      string_vector_const_iterator iter = local.getKeyListBegin();

      for( ; iter != local.getKeyListEnd(); ++iter )
      {
         DString name = *iter;

         Configuration config( name );
         RegistryKey key = local.getSubKey( name.asA() );

         // Each value in the subkey is a configuration pair
         RegistryKey::value_const_iterator v_iter = key.getValueListBegin();

         for( ; v_iter != key.getValueListEnd(); ++v_iter )
         {
            // Grab the value
            RegistryValue value = ( *v_iter ).second;

            if( value.getType() == RegistryValue::STRING )
            {
               // Configuration only cares about string values
               config.set( value.getName(), ConfigValue( value.getAsString() ) );
            }
         }

         // insert the Configuration object into the map (keyed off its name)
         m_table.insert( manager_type( name, config ) );
      }
   }
   else
   {
      if( Config::isElemental() )
      {
         THROWELEMENTAL( DICORE_CONDITION,
                         I_( "RegistryObject::refreshFromRegistry()" ),
                         DICORE_READ_REGISTRY_FAIL,
                         languagesMapForRegistryObject );
      }
      else
      {
         // Cannot read the persistent source
         MAKEFRAMENOTRACE( DICORE_CONDITION,
                           I_( "RegistryObject::refreshFromRegistry()" ) );

         DString idiMsg;
         addIDITagValue( idiMsg, IDI_GENERIC, path );
         ADDCONDITIONFROMFILEIDI( DICORE_READ_REGISTRY_FAIL, idiMsg );
      }
   }

   return(success);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryObject::refreshFromIniFile
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : bool -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
bool RegistryObject::refreshFromIniFile()
{
   bool refresh = false;

   if( m_pGlobalIni )
   {
      refresh = m_pGlobalIni->refresh();
   }

   return(refresh);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryObject::persistToRegistry
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : bool -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
bool RegistryObject::persistToRegistry()
{
   if( ! Config::isElemental() )
   {
      TRACE_METHOD( I_( "RegistryObject" ), I_( "persistToRegistry()" ) )
   }

   bool success = true;
   DString path = m_definition.getValueAsString( getPathKey() );

   // Open the registry
   RegistryKey local( path.asA(), m_hive );

   if( ! local.saveKey() )
   {
      DString idiMsg;
      addIDITagValue( idiMsg, IDI_GENERIC, path );

      if( Config::isElemental() )
      {
         THROWELEMENTALIDI( DICORE_CONDITION,
                            I_( "RegistryObject::persistToRegistry()" ),
                            DICORE_PERSIST_REGISTRY_FAIL,
                            languagesMapForRegistryObject,
                            idiMsg );
      }
      else
      {
         THROWFROMFILEIDI( DICORE_CONDITION,
                           I_( "RegistryObject::persistToRegistry()" ),
                           DICORE_PERSIST_REGISTRY_FAIL,
                           idiMsg );
      }
   }

   // Iterate through the Configuratio Objects
   manager_const_iterator iter = m_table.begin();

   for( ; iter != m_table.end(); ++iter )
   {
      // Grab the Configuration Object
      Configuration config = ( *iter ).second;
      // Grab a subkey to represent the Configuration object
      RegistryKey key = local.getSubKey( config.getName() );

      // Iterate through the configuration pairs and store them as values
      Configuration::iterator c_iter = config.begin();

      for( ; c_iter != config.end(); ++c_iter )
      {
         RegistryValue value( ( *c_iter ).getKey().asA(),
                              ( *c_iter ).getValueAsString().asA() );
         key.setValue( value );
      }

      // Save the changes
      if( ! key.saveKey() )
      {
         // Could not persist
         if( Config::isElemental() )
         {
            THROWELEMENTAL( DICORE_CONDITION,
                            I_( "RegistryObject::persistToRegistry()" ),
                            DICORE_PERSIST_REGISTRY_FAIL,
                            languagesMapForRegistryObject );
         }
         else
         {
            THROWFROMFILE( DICORE_CONDITION,
                           I_( "RegistryObject::persistToRegistry()" ),
                           DICORE_PERSIST_REGISTRY_FAIL );
         }
      }
   }

   return(success);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RegistryObject::persistToIniFile
//
// ^DESCRIPTION :
//
// ^PARAMETERS  : none
//
// ^RETURNS     : bool -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
bool RegistryObject::persistToIniFile()
{
   bool success = false;

   if( m_pGlobalIni )
   {
      success = m_pGlobalIni->persist();
   }

   return(success);
}

bool RegistryObject::removeFromRegistry(const DString & subkey )
{
   TRACE_METHOD( I_( "RegistryObject" ), I_( "removeFromRegistry()" ) )

   bool destroyed = false;

   if (undefined())
   {
// No definition for the persistence, let someone know.
      MAKEFRAMENOTRACE( DICORE_CONDITION,
                        I_( "ConfigBrokerObject::destroy()" ) );
      ADDCONDITIONFROMFILE( DICORE_LOCATION_NOT_DEFINED );
   }
   else
   {
      DString name = m_definition.getName();
      DString app  = m_definition.getValueAsString( KEY_APP );
      DString registryPath = buildApplicationPath( app );	
      registryPath += getDelimiter();
      registryPath += name;
		   
	   RegistryKey local (registryPath.asA(), m_hive);
	   destroyed = local.deleteSubKey( subkey );

      manager_iterator table_ptr = m_table.find( subkey );
      if (table_ptr != m_table.end())
	   {
         m_table.erase (table_ptr);
      }
//       destroyed = persist();
   }
   return destroyed;
}

#endif // _WIN32

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/registryobject.cpp-arc  $
//
//   Rev 1.4   Oct 03 2005 09:59:56   popescu
//Incident 403519 - bug fix when removing registry entries
//
//   Rev 1.3   Sep 22 2005 16:46:42   fengyong
//Add feature - remove config within an config manager
//
//   Rev 1.2   Oct 22 2004 09:04:08   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:42:12   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:24   SMITHDAV
// Initial revision.
// 
//    Rev 1.13   May 24 2001 17:19:02   dt24433
// Changed static DString objects to const character strings.
// One (strSOFTWARE) was actually not initialized in time for use
// by another static object (TracerClient in InfraDateHelper).
// 
//    Rev 1.12   Apr 05 2000 15:23:32   DMUM
// Fixes problem with app loading
//
//    Rev 1.11   Jun 09 1999 09:51:42   DMUM
// If the DataPath is not found, config now uses the application path
//
//    Rev 1.10   May 14 1999 12:19:02   DMUM
// Made the "Elemental" mode thread/server safe
//
//    Rev 1.9   May 13 1999 09:16:38   DMUM
// Implementing "Elemental" mode of operation
//
//    Rev 1.8   Apr 15 1999 11:46:32   DMUM
// String development/enhancement
//
//    Rev 1.7   05 Mar 1999 15:40:50   DT14177
// Fixed DString invalid format problem
//
//    Rev 1.6   26 Feb 1999 15:06:10   DT14177
// Integrate DIBASE and DICONFIG into DICORE
//
//    Rev 1.5   25 Feb 1999 14:05:14   DT14177
// Changed IDI string substitution macros to end in IDI.
//
//    Rev 1.4   24 Feb 1999 10:44:30   DT14177
// sync up with tracer
//
//    Rev 1.3   22 Feb 1999 13:57:40   DT14177
// more UNICODE stuff
//
//    Rev 1.2   18 Feb 1999 10:38:26   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:03:16   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:32   DMUM
//
//
//    Rev 1.1   Aug 13 1998 11:36:46   DMUM
// added renameCurrentProfile()
//
//    Rev 1.6   Jul 14 1998 08:04:08   dmum
// Added getFileNameForProfile()
//
//    Rev 1.5   Jul 13 1998 17:01:54   dmum
// More development
//
//    Rev 1.4   Jul 13 1998 12:22:16   dmum
// More development
//
//    Rev 1.3   Jul 11 1998 16:10:52   dmum
// Development - too many changes to describe
//
//    Rev 1.2   Jul 02 1998 12:02:46   dmum
// Cleanup
//
//    Rev 1.1   Nov 19 1997 16:11:34   dmum
// Portability Issues
//
//    Rev 1.0   Nov 10 1997 12:22:36   DSZD
// Configuration extensions.
//
