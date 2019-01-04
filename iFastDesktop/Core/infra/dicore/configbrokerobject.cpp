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
// ^FILE   : ConfigBrokerObject.cpp
// ^AUTHOR : Steve Doolittle
// ^DATE   : 10 Oct 97
//
// ----------------------------------------------------------
//
// ^CLASS    : ConfigBrokerObject
//
// ^MEMBER VARIABLES :
//
//
//    long                m_lastfilesize       - size of file when last read in.
//    bool                m_bStandAlone        - in stand alon mode *.INI files
//                                              only
//    Location            m_standAlonelocation - location of persistence
//    Location            m_location           - location of persistence
//    ConfigBrokerObject* m_pAppIni            - Pointer to configuration manager
//                                              app ini object.
//
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef CONFIGBROKEROBJECT_HPP
   #include "configbrokerobject.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DICORE_H
   #include "dicore.h"
#endif

#ifndef BASE_H
   #include "base.h"
#endif

#ifndef DATAPATH_H
   #include "datapath.h"
#endif

#ifndef IDISTRING_HPP
#include "idistring.hpp"
#endif

#ifndef _IO_INCLUDED
#define _IO_INCLUDED
   #include <io.h>
#endif
#ifndef _FSTREAM_INCLUDED
#define _FSTREAM_INCLUDED
   #include <fstream>
#endif

namespace
{
   const int FLAG_READ_ACCESS    = 0x04;
   const int FLAG_WRITE_ACCESS   = 0x02;
   const int FLAG_EXISTS         = 0x00;

   const int MAX_LINE_LEN        = 255;

   const I_CHAR *ENV_DATAPATH      = I_("_DATAPATH");

   const I_CHAR *INI               = I_(".ini");
   const I_CHAR *MGR               = I_(".mgr");
   const I_CHAR *GRP               = I_(".grp");

   const I_CHAR *KEY_TYPE          = I_("type");
   const I_CHAR *KEY_FILE          = I_("file");
   const I_CHAR *KEY_PATH          = I_("path");
   const I_CHAR *KEY_GETVIEW       = I_("getview");
   const I_CHAR *KEY_SETVIEW       = I_("setview");
   const I_CHAR *KEY_COMMENTS      = I_("comments");

   const I_CHAR *VALUE_CONTAINER   = I_("Container");
   const I_CHAR *VALUE_REGISTRY    = I_("Registry");
   const I_CHAR *VALUE_INI         = I_("Ini");
   const I_CHAR *VALUE_GROUP       = I_("Group");
   const I_CHAR *VALUE_APP_MANAGER = I_("AppManager");
   const I_CHAR *VALUE_VIEW        = I_("View");
   const I_CHAR *VALUE_UNDEFINED   = I_("Undefined");

   const I_CHAR *IDI_PATH          = I_("PATH");
   const I_CHAR *IDI_GENERIC       = I_("GENERIC");
}

namespace Config
{
   extern bool isElemental();
}

MsgPair en_usConfigBrokerObject[] =
{
   {
      BASE_ALLOC_FAIL,
      I_("Machine is out of memory. There is insufficient disc space."),
      I_("Contact a support representative and report this message.")
   },
   {
      DICORE_LOCATION_NOT_DEFINED,
      I_("There is an internal problem. Persistent location not defined!"),
      I_("Contact a support representative to verify install configuration.")
   },
   {
      DICORE_OPEN_INI_FILE_FAIL,
      I_("There is an internal problem. Cannot open file: %PATH%"),
      I_("Contact a support representative to verify this file or check ")
      I_("install configuration.")
   },
   {
      DICORE_DATAPATH_ENV_NOT_DEFINED,
      I_("There is an internal problem. This workstation has not been ")
      I_("properly setup with the required environmental variables!"),
      I_("Contact a support representative to verify install configuration.")
   }
};

Condition::mapCodePagesToLanguages languagesMapForConfigBrokerObject[] =
{
   {
      I_( "C" ), en_usConfigBrokerObject
   },

   // End slot marger
   {
      NULL, NULL
   }
};


//******************************************************************************
//              Protected Constructor
//******************************************************************************
ConfigBrokerObject::ConfigBrokerObject( manager_map &table )
   : m_location( Config::UNDEFINED ),
     m_table( table ),
     m_pAppIni( NULL ),
     m_pGroupMgr( NULL )
{
}


//******************************************************************************
//              Public Methods
//******************************************************************************
ConfigBrokerObject::ConfigBrokerObject( const DString &appName,
                                        manager_map &table )
   : m_location( Config::UNDEFINED ),
     m_table( table ),
     m_pAppIni( NULL ),
     m_pGroupMgr( NULL )
{
   setDefinition( appName );
   profileGroupManagement();
}

ConfigBrokerObject::ConfigBrokerObject( const Configuration &defined,
                                        manager_map &table )
   : m_location( Config::UNDEFINED ),
     m_table( table ),
     m_definition( defined ),
     m_pAppIni( NULL ),
     m_pGroupMgr( NULL )
{
   setLocation( m_definition.getValueAsString( getTypeKey() ) );
   profileGroupManagement();
}

ConfigBrokerObject::~ConfigBrokerObject()
{
   if ( m_pAppIni )
   {
      delete m_pAppIni;
   }

   if ( m_pGroupMgr )
   {
      delete m_pGroupMgr;
   }
}

ConfigBrokerObject::Origin ConfigBrokerObject::getOrigin()
{
   #ifdef _CONFIG_TEST_1

      return INI_FILE;

   #else
      #if defined( __OS2__ )

         return INI_FILE;

      #elif defined( _WIN32 )

         return  REGISTRY;

      #else

         #error Platform not supported.

      #endif
   #endif
}

const I_CHAR *ConfigBrokerObject::getDelimiter()
{
   return GetPathDelemiter();
}

bool ConfigBrokerObject::doesFileExist( const DString & fullFilePath )
{
   return -1 != i_access( fullFilePath.c_str(), getDoesExistFlag() );
}

bool ConfigBrokerObject::isFileReadable( const DString & fullFilePath )
{
   return -1 != i_access( fullFilePath.c_str(), getReadAccessFlag() );
}

bool ConfigBrokerObject::isFileWritable( const DString & fullFilePath )
{
   return -1 != i_access( fullFilePath.c_str(), getWriteAccessFlag() );
}

bool ConfigBrokerObject::affirmFile( const DString &fullFilePath )
{
   /* See if the requested file exists. */
   bool affirmed = doesFileExist( fullFilePath );

   if ( ! affirmed )
   {
      /* File does not exists create a new one. */
      std::ofstream file( fullFilePath.asA().c_str() );

      if ( file )
      {
         affirmed = true;
         file.close();
      }
   }

   return affirmed;
}

bool ConfigBrokerObject::deleteFile( const DString &fullFilePath )
{
   bool success = false;

   if ( doesFileExist( fullFilePath ) )
   {
      success = ( -1 != i_unlink( fullFilePath.c_str() ) );
   }

   return success;
}

bool ConfigBrokerObject::undefined()
{
   return Config::UNDEFINED == m_location;
}

const Configuration &ConfigBrokerObject::getDefinition()
{
   return m_definition;
}

bool ConfigBrokerObject::create( const Config::Type &type,
                                 const DString &path,
                                 const DString &fileName )
{
   TRACE_METHOD( I_( "ConfigBrokerObject" ),
      I_( "create( const Config::Type &, const DString &, const DString & )" ) )

   bool created = false;

   // If this is called on a derived class that does not implement this method,
   // then m_pAppIni will be NULL
   if ( m_pAppIni )
   {
      Config::Location location = getLocationFromType( type );

      if ( Config::UNDEFINED != location )
      {
         Configuration &config = m_pAppIni->m_definition;
         DString fullPath = config.getValueAsString( getPathKey() );

         if ( ! path.empty() )
         {
            if ( getDelimiter() != path.substr( 0, 1 ) )
            {
               fullPath += getDelimiter();
            }

            fullPath += path;
         }

         DString fullName = fileName;
         fullName += getExtension( location );

         DString strLocation = getValueForLocation( location );

         ConfigValue cvType( strLocation );
         ConfigValue cvPath( fullPath );
         ConfigValue cvFile( fullName );

         m_definition.set( getTypeKey(), cvType );
         m_definition.set( getPathKey(), cvPath );
         m_definition.set( getFileKey(), cvFile );

         m_table.insert( manager_type( m_definition.getName(), m_definition ) );

         try
         {
            m_location = location;
            persist();

            cvPath.set( path );
            cvFile.set( fileName );

            // Copy our definition and put in the correct values for
            // "path" and "file"
            Configuration definition( m_definition );
            definition.set( getPathKey(), cvPath );
            definition.set( getFileKey(), cvFile );

            // Add it to the applications table
            DString name = definition.getName();
            manager_iterator table_ptr = m_appTable.find( name );

            if ( table_ptr == m_appTable.end() )
            {
               m_appTable.insert( manager_type( name, definition ) );
            }
            else
            {
               Configuration &config = ( *table_ptr ).second;

               config.set( getTypeKey(), cvType );
               config.set( getPathKey(), cvPath );
               config.set( getFileKey(), cvFile );
            }

            m_pAppIni->persist();

            created = true;
         }
         catch ( ConditionException &ce )
         {
            MAKEFRAMENOTRACE( DICORE_CONDITION,
                              I_( "ConfigBrokerObject::create()" ) );

            SETCONDITIONFROMEXCEPTION( ce )

            m_location = Config::UNDEFINED;
            created = false;
         }
      }
   }

   return created;
}

bool ConfigBrokerObject::destroy()
{
   TRACE_METHOD( I_( "ConfigBrokerObject" ), I_( "destroy()" ) )

   bool destroyed = false;

   if ( undefined() )
   {
      // No definition for the persistence, let someone know.
      MAKEFRAMENOTRACE( DICORE_CONDITION,
                        I_( "ConfigBrokerObject::destroy()" ) );
      ADDCONDITIONFROMFILE( DICORE_LOCATION_NOT_DEFINED );
   }
   else
   {
      // Clear the definition
      if ( m_pAppIni )
      {
         clearDefinition();

         manager_iterator table_ptr = m_appTable.find( m_definition.getName() );

         if ( table_ptr != m_table.end() )
         {
            m_appTable.erase( table_ptr );
         }

         destroyed = m_pAppIni->persist();
      }
   }

   return destroyed;
}

bool ConfigBrokerObject::refresh()
{
   if ( ! Config::isElemental() )
   {
      TRACE_METHOD( I_( "ConfigBrokerObject" ), I_( "refresh()" ) )
   }

   clearTable();

   if ( Config::VIEW == m_location )
   {
      return refreshFromView();
   }

   bool success = false;
   DString currentSection;

   DString fullFilePath = makeFullFilePath();

   if ( Config::APP_MANAGER == m_location )
   {
      affirmFile( fullFilePath );
   }

   if ( isFileReadable( fullFilePath ) && ( Config::UNDEFINED != m_location ) )
   {
      std::ifstream collection( fullFilePath.asA().c_str() );
      char * pLine = new char[MAX_LINE_LEN + 1];
      success = true;

      while ( ! collection.eof() )
      {
         // Grab a line
         collection.getline( pLine, MAX_LINE_LEN );
         DStringA line( pLine );
         strip( line );

         // Make sure the line is not a comment
         if ( ! ( line.empty() || isCommentLine( line ) ) )
         {
            // See if we are in a new section
            if ( isSection( line ) )
            {
               currentSection = line;
            }
            else
            {
               // We have a pair, potentially, make sure we have a section
               if ( ! currentSection.empty() )
               {
                  // Find the section in the table
                  manager_iterator table_ptr = m_table.find( currentSection );

                  if ( table_ptr == m_table.end() )
                  {
                     // Section Not found, so add it.
                     Configuration config( currentSection );
                     config.set( line );

                     m_table.insert( manager_type( currentSection, config ) );
                  }
                  else
                  {
                     // Just add to the config object
                     Configuration &config = (* table_ptr).second;
                     config.set( line );
                  }
               }
            }
         }
      }

      delete[] pLine;
   }

   return success;
}

bool ConfigBrokerObject::persist()
{
   if ( ! Config::isElemental() )
   {
      TRACE_METHOD( I_( "ConfigBrokerObject" ), I_( "persist()" ) )
   }

   bool success = false;

   if ( Config::UNDEFINED == m_location )
   {
      if ( Config::isElemental() )
      {
         THROWELEMENTAL( DICORE_CONDITION,
                         I_( "ConfigBrokerObject::persist()" ),
                         DICORE_LOCATION_NOT_DEFINED,
                         languagesMapForConfigBrokerObject );
      }
      else
      {
         // The location is not defined!
         THROWFROMFILE( DICORE_CONDITION,
                        I_( "ConfigBrokerObject::persist()" ),
                        DICORE_LOCATION_NOT_DEFINED );
      }
   }

   if ( Config::VIEW == m_location )
   {
      return persistToView();
   }

   DString fullFilePath = makeFullFilePath();
   DString idiMsg;
   addIDITagValue( idiMsg, IDI_PATH, fullFilePath );

   // Affirm the file exists
   if ( ! affirmFile( fullFilePath ) )
   {
      if ( Config::isElemental() )
      {
         THROWELEMENTALIDI( DICORE_CONDITION,
                            I_( "ConfigBrokerObject::persist()" ),
                            DICORE_OPEN_INI_FILE_FAIL,
                            languagesMapForConfigBrokerObject,
                            idiMsg );
      }
      else
      {
         // Cannot open the file for writing
         THROWFROMFILEIDI( DICORE_CONDITION,
                           I_( "ConfigBrokerObject::persist()" ),
                           DICORE_OPEN_INI_FILE_FAIL,
                           idiMsg );
      }
   }

   // See if the file can be written to
   if ( ! isFileWritable( fullFilePath ) )
   {
      if ( Config::isElemental() )
      {
         THROWELEMENTALIDI( DICORE_CONDITION,
                            I_( "ConfigBrokerObject::persist()" ),
                            DICORE_OPEN_INI_FILE_FAIL,
                            languagesMapForConfigBrokerObject,
                            idiMsg );
      }
      else
      {
         // Cannot open the file for writing
         THROWFROMFILEIDI( DICORE_CONDITION,
                           I_( "ConfigBrokerObject::persist()" ),
                           DICORE_OPEN_INI_FILE_FAIL,
                           idiMsg );
      }
   }

   // open the file
   std::ofstream inifile( DStringA( fullFilePath ).c_str(), std::ios::out );

   // Failed to open the file
   if ( ! inifile )
   {
      if ( Config::isElemental() )
      {
         THROWELEMENTALIDI( DICORE_CONDITION,
                            I_( "ConfigBrokerObject::persist()" ),
                            DICORE_OPEN_INI_FILE_FAIL,
                            languagesMapForConfigBrokerObject,
                            idiMsg );
      }
      else
      {
         // Cannot open the file for writing
         THROWFROMFILEIDI( DICORE_CONDITION,
                           I_( "ConfigBrokerObject::persist()" ),
                           DICORE_OPEN_INI_FILE_FAIL,
                           idiMsg );
      }
   }

   success = true;

   // Iterate through the Configuration Objects
   manager_iterator iter = m_table.begin();
   DString outputbuffer = NULL_STRING;

   for ( ; iter != m_table.end(); ++iter )
   {
      // Grab the Configuration object
      Configuration &config = ( *iter ).second;

      outputbuffer += I_( "[" );
      outputbuffer += config.getName();
      outputbuffer += I_( "]" );
      outputbuffer += '\n';

      // Iterate through the configuration pairs
      Configuration::iterator c_iter = config.begin();

      for ( ; c_iter != config.end(); ++c_iter )
      {
         outputbuffer += I_( "   " );
         outputbuffer += ( *c_iter ).getKey();
         outputbuffer += I_( " = " );
         outputbuffer += ( *c_iter ).getValueAsString();
         outputbuffer += '\n';
      }

      // Add an extra line between configuration objects
      outputbuffer += '\n';
   }

   // not set up for UNICODE .INI files
   inifile << outputbuffer.asA();
   inifile.close();

   return success;
}


bool ConfigBrokerObject::isProfileGroup()
{
   // We are a profile group if we have a group manager
   return  NULL != m_pGroupMgr;
}

string_vector ConfigBrokerObject::getProfileList()
{
   string_vector list;

   if ( m_pGroupMgr )
   {
      manager_const_iterator iter = m_groupTable.begin();

      // Iterate through the map of Configuration objects
      for ( ; iter != m_groupTable.end(); ++iter )
      {
         // Add the Configuration object's name to the list
         list.push_back( ( *iter ).first );
      }
   }

   return list;
}

DString ConfigBrokerObject::getCurrentProfileName()
{
   DString name;

   if ( m_pGroupMgr )
   {
      name = m_definition.getName();
   }

   return name;
}

bool ConfigBrokerObject::renameCurrentProfile( const DString &name )
{
   bool success = false;

   if ( m_pGroupMgr )
   {
      manager_iterator table_ptr = m_groupTable.find( m_definition.getName() );

      if ( table_ptr != m_groupTable.end() )
      {
         // Copy the definition
         Configuration definition( ( *table_ptr ).second );

         // Change the name
         definition.setName( name );
         m_definition.setName( name );

         // Remoev the old definition and add the new one
         m_groupTable.erase( table_ptr );
         m_groupTable.insert( manager_type( name, definition ) );

         success = m_pGroupMgr->persist();
      }
   }

   return success;
}

DString ConfigBrokerObject::getFileNameForProfile( const DString &name )
{
   DString file;

   if ( m_pGroupMgr )
   {
      manager_iterator table_ptr = m_groupTable.find( name );

      if ( table_ptr != m_groupTable.end() )
      {
         Config::Location location;
         Configuration &config = ( *table_ptr ).second;
         location = getLocation( config.getValueAsString( getTypeKey() ) );
         file = config.getValueAsString( getFileKey() );
         file += getExtension( location );
      }
   }

   return file;
}

bool ConfigBrokerObject::selectProfile( const DString &name )
{
   bool selected = false;

   if ( m_pGroupMgr )
   {
      manager_iterator table_ptr = m_groupTable.find( name );

      if ( table_ptr != m_groupTable.end() )
      {
         selected = true;

         clearTable();

         // change our definition
         m_definition = ( *table_ptr ).second;

         // set our new location
         setLocation( m_definition.getValueAsString( getTypeKey() ) );

         // get the path
         DString path = m_pGroupMgr->m_definition.getValueAsString( getPathKey() );
         // make our file name
         DString fullName = m_definition.getValueAsString( getFileKey() );
         fullName += getExtension( m_location );

         ConfigValue cvPath( path );
         ConfigValue cvFile( fullName );

         // store the path and file name
         m_definition.set( getPathKey(), cvPath );
         m_definition.set( getFileKey(), cvFile );
      }
   }

   return selected;
}

bool ConfigBrokerObject::createNewProfile( const DString &name,
                                           const DString &file,
                                           const Config::Type &type )
{
   bool success = false;

   if ( m_pGroupMgr )
   {
      clearTable();
      clearDefinition();
      selectProfile( name );

      // Make sure we are undefined at this point before proceeding.
      // If we are defined, then this profile already exists
      if ( Config::UNDEFINED == m_location )
      {
         Configuration definition( name );
         Config::Location location = getLocationFromType( type );

         ConfigValue cvFile( file );
         ConfigValue cvType( getValueForLocation( location ) );

         definition.set( getFileKey(), cvFile );
         definition.set( getTypeKey(), cvType );

         m_groupTable.insert( manager_type( name, definition ) );

         success = m_pGroupMgr->persist();

         if ( success )
         {
            // Select the profile again
            success = selectProfile( name );
         }
      }
      else
      {
         MAKEFRAMENOTRACE( DICORE_CONDITION,
                           I_( "ConfigBrokerObject::createNewProfile()" ) );

         DString idiMsg;
         addIDITagValue( idiMsg, IDI_GENERIC, name );
         ADDCONDITIONFROMFILEIDI( DICORE_PROFILE_ALREAD_EXISTS, idiMsg );
      }
   }

   return success;
}

bool ConfigBrokerObject::deleteProfile( const DString &name )
{
   bool success = false;

   if ( m_pGroupMgr )
   {
      manager_iterator table_ptr = m_groupTable.find( name );

      if ( table_ptr != m_groupTable.end() )
      {
         Config::Location location;
         Configuration &config = ( *table_ptr ).second;
         location = getLocation( config.getValueAsString( getTypeKey() ) );

         // make the full file path
         DString path = m_pGroupMgr->m_definition.getValueAsString( getPathKey() );
         path += getDelimiter();
         path += config.getValueAsString( getFileKey() );
         path += getExtension( location );

         success = deleteFile( path );

         if ( success )
         {
            if ( m_definition.getName() == name )
            {
               clearTable();
               clearDefinition();
            }

            m_groupTable.erase( table_ptr );
            success = m_pGroupMgr->persist();
         }
      }
   }

   return success;
}

bool ConfigBrokerObject::isCurrentProfileSubGroup()
{
   bool subGroup = false;

   if ( m_pGroupMgr )
   {
      subGroup = ( Config::GROUP == m_location );
   }

   return subGroup;
}

bool ConfigBrokerObject::isSubGroup( const DString &name )
{
   bool subGroup = false;

   if ( m_pGroupMgr )
   {
      manager_iterator table_ptr = m_groupTable.find( name );

      if ( table_ptr != m_groupTable.end() )
      {
         const Configuration &config = ( *table_ptr ).second;

         Config::Location location;
         location = getLocation( config.getValueAsString( getTypeKey() ) );
         subGroup = ( Config::GROUP == location );
      }
   }

   return subGroup;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void ConfigBrokerObject::setDefinition( const DString &appName )
{
   int seperator = appName.find( getDelimiter() );
   DString app = appName.substr( 0, seperator );
   DString path = getDataPath( app );

   if ( NULL == m_pAppIni )
   {
      DString appFile = app + getExtension( Config::APP_MANAGER );
      DString location = getValueForLocation( Config::APP_MANAGER );

      ConfigValue cvFile( appFile );
      ConfigValue cvType( location );

      Configuration definition( app );
      definition.set( getPathKey(), path );
      definition.set( getFileKey(), cvFile );
      definition.set( getTypeKey(), cvType );

      m_pAppIni = new ConfigBrokerObject( definition, m_appTable );

      if ( ! m_pAppIni )
      {
         if ( Config::isElemental() )
         {
            THROWELEMENTAL( DICORE_CONDITION,
                            I_( "ConfigBrokerObject::setDefinition()" ),
                            BASE_ALLOC_FAIL,
                            languagesMapForConfigBrokerObject );
         }
         else
         {
            THROWFROMBASE( DICORE_CONDITION,
                           I_( "ConfigBrokerObject::setDefinition()" ),
                           BASE_ALLOC_FAIL );
         }
      }

      m_pAppIni->refresh();
   }

   DString name = appName.substr( seperator + 1 );
   manager_iterator table_ptr = m_appTable.find( name );

   if ( table_ptr == m_appTable.end() )
   {
      // The lookup failed
      DString location = getValueForLocation( Config::UNDEFINED );

      ConfigValue cvType( location );
      ConfigValue cvComments( I_( "none" ) );

      m_definition.setName( name );
      m_definition.set( getTypeKey(), cvType );
      m_definition.set( KEY_COMMENTS, cvComments );

      m_appTable.insert( manager_type( name, m_definition ) );
   }
   else
   {
      m_definition = ( *table_ptr ).second;

      // prepend the data path to the ini path
      DString iniPath = m_definition.getValueAsString( getPathKey() );

      if ( ! iniPath.empty() )
      {
         if ( getDelimiter() != iniPath.substr( 0, 1 ) )
         {
            path += getDelimiter();
         }

         path += iniPath;
      }

      m_definition.set( getPathKey(), path );
   }

   setLocation( m_definition.getValueAsString( getTypeKey() ) );
}

void ConfigBrokerObject::profileGroupManagement()
{
   static const DString strGROUP_MGR = I_( "GroupMgr" );

   // We only need to manage profile groups
   if ( Config::GROUP == m_location )
   {
      // Determine if we are the profile group manager object
      DString manager = m_definition.getValueAsString( strGROUP_MGR );

      if ( ( ! manager.empty() ) && ( 'Y' == manager[0] ) )
      {
         // We are the group manager - do nothing but return
         return;
      }

      // We are not the group manager, so create one
      Configuration definition( m_definition );
      ConfigValue cvYes( I_( "Y" ) );
      definition.set( strGROUP_MGR, cvYes );

      m_pGroupMgr = new ConfigBrokerObject( definition, m_groupTable );

      if ( ! m_pGroupMgr )
      {
         if ( Config::isElemental() )
         {
            THROWELEMENTAL( DICORE_CONDITION,
                            I_( "ConfigBrokerObject::profileGroupManagement()" ),
                            BASE_ALLOC_FAIL,
                            languagesMapForConfigBrokerObject );
         }
         else
         {
            THROWFROMBASE( DICORE_CONDITION,
                           I_( "ConfigBrokerObject::profileGroupManagement()" ),
                           BASE_ALLOC_FAIL );
         }
      }

      m_pGroupMgr->refresh();

      // Change ourself to one of the profiles
      manager_iterator table_ptr = m_groupTable.begin();

      if ( table_ptr != m_groupTable.end() )
      {
         selectProfile( ( *table_ptr ).first );
      }
      else
      {
         // We have no profiles, so we are undefined.
         clearDefinition();
      }
   }
}

void ConfigBrokerObject::clearDefinition()
{
   m_location = Config::UNDEFINED;

   ConfigValue nullConfig( NULL_STRING );

   m_definition.set( getTypeKey(), nullConfig );
   m_definition.set( getPathKey(), nullConfig );
   m_definition.set( getFileKey(), nullConfig );
}

Config::Location ConfigBrokerObject::getLocation( const DString &strLocation )
{
   Config::Location location = Config::UNDEFINED;

   if ( ! strLocation.empty() && ( VALUE_UNDEFINED != strLocation ) )
   {
      location = (Config::Location) strLocation[0];
   }

   return location;
}

void ConfigBrokerObject::setLocation( const DString &strLocation )
{
   m_location = getLocation( strLocation );
}

void ConfigBrokerObject::clearTable()
{
   if ( !m_table.empty() )
   {
      m_table.erase( m_table.begin(), m_table.end() );
   }
}

DString ConfigBrokerObject::getDataPath( const DString &application )
{
   DString dataPath;

   if ( ! GetIniPath( dataPath, application ) )
   {
      GetApplicationPath( dataPath );
   }

   int pos = dataPath.length();

   if ( 0 < --pos )
   {
      if ( getDelimiter() == dataPath.substr( pos, 1 ) )
      {
         dataPath.erase( pos );
      }
   }

   return dataPath;
}

bool ConfigBrokerObject::refreshFromView()
{
   bool success = false;

   /* FUTURE: At some point a view will be sent to the       */
   /*         mainframe to retrieve configuration.           */

   return false;
}

bool ConfigBrokerObject::persistToView()
{
   bool success = false;

   /* FUTURE: At some point a view will be sent to the       */
   /*         mainframe to update configuration.             */

   return success;
}

const I_CHAR *ConfigBrokerObject::getExtension( const Config::Location &location )
{
   const I_CHAR *pExt = NULL;

   switch ( location )
   {
      case Config::GROUP:
         pExt = GRP;
         break;

      case Config::APP_MANAGER:
         pExt = MGR;
         break;

      default:
         pExt = INI;
   }

   return pExt;
}

const I_CHAR *ConfigBrokerObject::getTypeKey()
{
   return KEY_TYPE;
}

const I_CHAR *ConfigBrokerObject::getFileKey()
{
   return KEY_FILE;
}

const I_CHAR *ConfigBrokerObject::getGetViewKey()
{
   return KEY_GETVIEW;
}

const I_CHAR *ConfigBrokerObject::getSetViewKey()
{
   return KEY_SETVIEW;
}

const I_CHAR *ConfigBrokerObject::getPathKey()
{
   return KEY_PATH;
}


const I_CHAR *ConfigBrokerObject::getValueForLocation( Config::Location location )
{
   const I_CHAR *pValue = NULL;

   switch ( location )
   {
      case Config::CONTAINER:
         pValue = VALUE_CONTAINER;
         break;

      case Config::REGISTRY:
         pValue = VALUE_REGISTRY;
         break;

      case Config::INI:
         pValue = VALUE_INI;
         break;

      case Config::GROUP:
         pValue = VALUE_GROUP;
         break;

      case Config::APP_MANAGER:
         pValue = VALUE_APP_MANAGER;
         break;

      case Config::VIEW:
         pValue = VALUE_VIEW;
         break;

      default:
         pValue = VALUE_UNDEFINED;
         break;
   }

   return pValue;
}

Config::Location ConfigBrokerObject::getLocationFromType( Config::Type type )
{
   Config::Location location;

   switch ( type )
   {
      case Config::CONTAINER_TYPE:
         location = Config::CONTAINER;
         break;

      case Config::REGISTRY_TYPE:
         location = Config::REGISTRY;
         break;

      case Config::INI_TYPE:
         location = Config::INI;
         break;

      case Config::GROUP_TYPE:
         location = Config::GROUP;
         break;

      case Config::VIEW_TYPE:
         location = Config::VIEW;
         break;

      default:
         location = Config::UNDEFINED;
         break;
   }

   return location;
}


//******************************************************************************
//              Private Methods
//******************************************************************************

DString ConfigBrokerObject::makeFullFilePath()
{
   DString fullFilePath = m_definition.getValueAsString( getPathKey() );
   fullFilePath += getDelimiter();
   fullFilePath += m_definition.getValueAsString( getFileKey() );

   return fullFilePath;
}

bool ConfigBrokerObject::isCommentLine( const DStringA &iniLine )
{
   bool comment = false;

   if ( ! iniLine.empty() )
   {
      comment = ( ';' == iniLine[0] );
   }

   return comment;
}

bool ConfigBrokerObject::isSection( DStringA &iniLine )
{
   bool section = false;

   DStringA::size_type rbracket;
   DStringA::size_type lbracket;


   if ( ( DStringA::npos != ( lbracket = iniLine.find( '[' ) ) ) &&
        ( DStringA::npos != ( rbracket = iniLine.rfind( ']' ) ) ) )
   {
      //This line is a section.
      iniLine  = iniLine.substr( lbracket + 1, rbracket - ( lbracket + 1 ) );
      section = true;
   }

   return section;
}

int ConfigBrokerObject::getReadAccessFlag()
{
   return FLAG_READ_ACCESS;
}

int ConfigBrokerObject::getWriteAccessFlag()
{
   return FLAG_WRITE_ACCESS;
}

int ConfigBrokerObject::getDoesExistFlag()
{
   return FLAG_EXISTS;
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
// $Log:   Y:/VCS/iFastAWD/dicore/configbrokerobject.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:24   kovacsro
// Initial revision.
// 
//    Rev 1.13   Sep 21 2000 13:26:16   DT21858
// Fixes small bug
//
//    Rev 1.12   Jul 06 2000 14:56:20   DMUM
// Removed unused statid DString
//
//    Rev 1.11   Jun 09 1999 09:51:26   DMUM
// If the DataPath is not found, config now uses the application path
//
//    Rev 1.10   May 14 1999 12:18:54   DMUM
// Made the "Elemental" mode thread/server safe
//
//    Rev 1.9   May 13 1999 09:16:24   DMUM
// Implementing "Elemental" mode of operation
//
//    Rev 1.8   Apr 15 1999 11:46:26   DMUM
// String development/enhancement
//
//    Rev 1.7   Apr 08 1999 14:17:00   DMUM
// Fixed problem with persist()
//
//    Rev 1.6   26 Feb 1999 15:05:48   DT14177
// Integrate DIBASE and DICONFIG into DICORE
//
//    Rev 1.5   25 Feb 1999 14:05:06   DT14177
// Changed IDI string substitution macros to end in IDI.
//
//    Rev 1.4   24 Feb 1999 10:44:02   DT14177
// sync up with tracer
//
//    Rev 1.3   22 Feb 1999 13:57:16   DT14177
// more UNICODE stuff
//
//    Rev 1.2   18 Feb 1999 10:34:00   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:02:30   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:50:54   DMUM
//
//
//    Rev 1.1   Aug 13 1998 11:36:30   DMUM
// added renameCurrentProfile()
//
//    Rev 1.5   Jul 14 1998 08:03:48   dmum
// Added getFileNameForProfile()
//
//    Rev 1.4   Jul 13 1998 17:01:32   dmum
// More development
//
//    Rev 1.3   Jul 13 1998 12:21:56   dmum
// More development
//
//    Rev 1.2   Jul 11 1998 16:07:34   dmum
// Development - too many changes to describe
//
//    Rev 1.1   Jul 02 1998 12:03:26   dmum
// Cleanup
//
//    Rev 1.0   Nov 19 1997 16:05:36   dmum
// Initial Check in (AGAIN)
//
//    Rev 1.0   Nov 10 1997 12:22:50   DSZD
// Configuration extensions.
//
