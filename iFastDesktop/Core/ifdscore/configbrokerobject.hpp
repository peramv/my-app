#ifndef CONFIGBROKEROBJECT_HPP
#define CONFIGBROKEROBJECT_HPP

#pragma message( "including "__FILE__ )

/*
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

/** This a base class for configuration persistence.  The
 *  default for persistence are *.INI files.
 */

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif
#ifndef DICORE_H
   #include <dicore.h>
#endif
#ifndef DICONFIGGLOBAL_H
   #include <diconfigglobal.h>
#endif
#ifndef COMMONTEMPLATES_H
   #include <commontemplates.h>
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif

// Persistence locations

// NOTE: The decimal settings are the ASCII equivalent to the
// first letter in each enumeration.  This is used later in the
// code to cast from a string to the enum.

// UNDEFINED      - means the persistent location is not known.
// CONTAINER      - means the persistent location contains configurations
//                  only.  There is no pointer to other configurations.
// REGISTRY       - means this configuration points to another
//                  'commonly used' configuration.  A LOCAL location
//                  can point to itself if 'it' is the common
//                  configuration.
// INI            - means this configuration points to a *.INI file
//                  located on some server.
// VIEW           - means this configuration is located on a mainframe
//                  and is accessed through views.
// MACHINE_REMOTE - means this configuration points to a configuration
//                  on another machine.

namespace Config
{
   enum Location
   {
      UNDEFINED      = 0,
      CONTAINER      = 67,  // 67 - Decimal value of 'C' used for casting
      REGISTRY       = 82,  // 82 - Decimal value of 'R' used for casting
      INI            = 73,  // 73 - Decimal value of 'I' used for casting
      GROUP          = 71,  // 71 - Decimal value of 'G' used for casting
      APP_MANAGER    = 65,  // 65 - Decimal value of 'A' used for casting
      VIEW           = 86,  // 86 - Decimal value of 'V' used for casting
      MACHINE_REMOTE = 77   // 77 - Decimal value of 'M' used for casting
   };
}

class ConfigBrokerObject
{
   // Public Enumerations
public:
   enum Origin
   {
      REGISTRY, INI_FILE
   };

   // Constructors and destructor
protected:
   /**
    * Constructor
    * 
    * @param table
    */
   ConfigBrokerObject( manager_map & table );

public:
   /**
    * Constructor
    * 
    * @param appName
    * @param table
    */
   ConfigBrokerObject( const DString & appName, 
                       manager_map & table );

   /**
    * Constructor
    * 
    * @param defined
    * @param table
    */
   ConfigBrokerObject( const Configuration & defined,
                       manager_map & table );

   /**
    * Destructor
    */
   virtual ~ConfigBrokerObject();

   // Public methods
public:
   /**
    * Returns the origin of the config object
    * 
    * @return INIFILE or REGISTRY, depending on the O/S
    */
   static Origin getOrigin();

   /**
    * Returns the path delimiter
    * 
    * @return 
    */
   static const I_CHAR * getDelimiter();

   /**
    * Tests whether the file exists
    * 
    * @param fullFilePath
    * @return 
    */
   static bool doesFileExist( const DString &fullFilePath );

   /**
    * Test the file's read attribute
    * 
    * @param fullFilePath
    * @return 
    */
   static bool isFileReadable( const DString &fullFilePath );

   /**
    * Tests the file's write attribute
    * 
    * @param fullFilePath
    * @return 
    */
   static bool isFileWritable( const DString &fullFilePath );

   /**
    * Tests whether the file exists; if it doesn't exist,
    *   the method will attempt to create it
    * 
    * @param fullFilePath
    * @return 
    */
   static bool affirmFile( const DString &fullFilePath );

   /**
    * Deletes a file if it exists
    * 
    * @param fullFilePath
    * @return 
    */
   static bool deleteFile( const DString &fullFilePath );

   /**
    * Returns whether a location is undefined
    * 
    * @return 
    */
   bool undefined();

   // Public virtual methods
public:
   /**
    * Getter for the definition
    * 
    * @return 
    */
   virtual const Configuration & getDefinition();

   /**
    * Creates a persistent ConfigBroker object
    * 
    * @param type     - the object type
    * @param path     - the path to the object
    * @param fileName
    * @return 
    */
   virtual bool create( const Config::Type & type,
                        const DString & path,
                        const DString & fileName );

   /**
    * Destroys a persistent ConfigBroker object
    * 
    * @return 
    */
   virtual bool destroy();

   /**
    * Refreshes a persistent ConfigBroker object
    * 
    * @return 
    */
   virtual bool refresh();

   /**
    * Causes a ConfigBroker object to persist
    * 
    * @return 
    */
   virtual bool persist();

   /**
    * Returns whether the ConfigBroker object has
    * a profile manager
    * 
    * @return 
    */
   virtual bool isProfileGroup();

   /**
    * creates a string vector of ConfigBroker object
    * names from the group table
    * 
    * @return 
    */
   virtual string_vector getProfileList();

   /**
    * If the object is part of a profile group,
    * the definition name is returned.
    * 
    * @return 
    */
   virtual DString getCurrentProfileName();

   /**
    * Gives the object a new name
    * 
    * @param name   - the new name
    * @return 
    */
   virtual bool renameCurrentProfile( const DString & name );

   /**
    * Returns the file name associated with a
    * profile
    * 
    * @param name
    * @return 
    */
   virtual DString getFileNameForProfile(
                                        const DString & profileName );

   /**
    * Copies a profile from another ConfigBroker
    * object onto this object
    * 
    * @param name
    * @return 
    */
   virtual bool selectProfile( const DString & name );

   /**
    * Creates a new, persistent profile
    * 
    * @param name
    * @param file
    * @param type
    * @return 
    */
   virtual bool createNewProfile( const DString & name,
                                  const DString & file,
                                  const Config::Type & type );

   /**
    * Deletes a profile
    * 
    * @param name
    * @return 
    */
   virtual bool deleteProfile( const DString &name );

   /**
    * Returns whether the object is part of a
    * profile group
    * 
    * @return 
    */
   virtual bool isCurrentProfileSubGroup();

   /**
    * Returns whether the named object is part of a
    * profile group
    * 
    * @param name
    * @return 
    */
   virtual bool isSubGroup( const DString & name );
   virtual bool removeFromRegistry( const DString &configuration );

   // Protected Methods
protected:
   /**
    * Gets a persistent config object and sets
    * its attributes into this object
    * 
    * @param appName
    */
   void setDefinition( const DString &appName );

   /**
    * Creates a profile group manager if one
    * doesn't already exist for the Configuration
    * object
    */
   void profileGroupManagement();

   /**
    * Clears the profile definition from the
    * Configuration object
    */
   void clearDefinition();

   /**
    * Returns the location code
    * 
    * @param strLocation
    * @return 
    */
   Config::Location getLocation( const DString &strLocation );

   /**
    * Sets the location code
    * 
    * @param strLocation
    */
   void setLocation( const DString &strLocation );

   /**
    * Clears the ConfigManager table
    */
   void clearTable();

   /**
    * Gets the data path to the persistent
    * Configuration object named by the input
    * parameter
    * 
    * @param application
    * @return 
    */
   virtual DString getDataPath( const DString &application );

   /**
    * Stubbed out
    * 
    * @return 
    */
   virtual bool refreshFromView();

   /**
    * Stubbed out
    * 
    * @return 
    */
   virtual bool persistToView();

   // protected static methods
protected:
   /**
    * Returns the file extension based on
    * Configuration type (location)
    * 
    * @param location
    * @return 
    */
   static const I_CHAR * getExtension(
                                     const Config::Location & location );

   /**
    * Returns the type string
    * 
    * @return 
    */
   static const I_CHAR * getTypeKey();

   /**
    * Returns the file string
    * 
    * @return 
    */
   static const I_CHAR * getFileKey();

   /**
    * Returns the getview string
    * 
    * @return 
    */
   static const I_CHAR * getGetViewKey();

   /**
    * Returns the setview string
    * 
    * @return 
    */
   static const I_CHAR * getSetViewKey();

   /**
    * Returns the path string
    * 
    * @return 
    */
   static const I_CHAR * getPathKey();

   /**
    * Returns a pointer to a string constant
    * based on location
    * 
    * @param location
    * @return 
    */
   static const I_CHAR * getValueForLocation(
                                            Config::Location location );
   /**
    * Returns a location based on the type
    * 
    * @param type
    * @return 
    */
   static Config::Location getLocationFromType(
                                              Config::Type type );

   // Protected Members
protected:
   Config::Location  m_location;
   manager_map &m_table;
   Configuration m_definition;

   // Private Methods
private:
   DString makeFullFilePath();
   bool isCommentLine( const DStringA &iniLine );
   bool isSection( DStringA &iniLine );
   bool selectProfileFromSessionNodeXML( const DString &name );

   static int getReadAccessFlag();
   static int getWriteAccessFlag();
   static int getDoesExistFlag();

   // Private Members
private:
   ConfigBrokerObject *m_pAppIni;
   ConfigBrokerObject *m_pGroupMgr;
   manager_map m_appTable;
   manager_map m_groupTable;
};

#endif//CONFIGBROKEROBJECT_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/configbrokerobject.hpp-arc  $
//
//   Rev 1.2   Sep 22 2005 16:46:24   fengyong
//Add feature - remove config within an config manager
//
//   Rev 1.1   Oct 09 2002 17:41:48   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:12:46   SMITHDAV
//Initial revision.
// 
//    Rev 1.6   12 Dec 2000 11:30:54   dt14177
// cleanup and documentation
// 
//    Rev 1.5   Apr 15 1999 11:46:28   DMUM
// String development/enhancement
//
//    Rev 1.4   04 Mar 1999 10:53:16   DT14177
// Fixed leftover diconfig.h file problem
//
//    Rev 1.3   22 Feb 1999 13:57:18   DT14177
// more UNICODE stuff
//
//    Rev 1.2   18 Feb 1999 10:34:22   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:02:32   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:50:56   DMUM
//
//
//    Rev 1.1   Aug 13 1998 11:36:22   DMUM
// added renameCurrentProfile()
//
//    Rev 1.6   Jul 14 1998 08:03:36   dmum
// Added getFileNameForProfile()
//
//    Rev 1.5   Jul 13 1998 17:01:16   dmum
// More development
//
//    Rev 1.4   Jul 13 1998 12:21:42   dmum
// More development
//
//    Rev 1.3   Jul 11 1998 16:07:44   dmum
// Development - too many changes to describe
//
//    Rev 1.2   Jul 02 1998 12:03:12   dmum
// Cleanup
//
//    Rev 1.1   Mar 16 1998 15:53:56   dmum
// Made the destructor virtual
//
//    Rev 1.0   Nov 19 1997 16:05:38   dmum
// Initial Check in (AGAIN)
//
//    Rev 1.0   Nov 10 1997 12:23:58   DSZD
// Configuration extensions.
//
