#ifndef REGISTRYOBJECT_HPP
#define REGISTRYOBJECT_HPP

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

/** This class is responsible for registry configuration
 *                    persistence. */

#ifndef CONFIGBROKEROBJECT_HPP
   #include "configbrokerobject.hpp"
#endif

#ifdef _WIN32

#ifndef REGISTRYKEY_HPP
   #include "registrykey.hpp"
#endif

#endif

class RegistryObject: public ConfigBrokerObject
{
   // Constructors and destructors
   public:
      /**
       * Constructor
       * 
       * @param appName
       * @param company
       * @param table
       */
      RegistryObject( const DString &appName,
                      const DString &company,
                      manager_map &table );

      /**
       * Destructor
       */
      virtual ~RegistryObject();

   #ifdef _WIN32

   // Public virtual methods
   public:
      /**
       * Get the profile definition either from
       * the object or from the global
       * Configuration object
       * 
       * @return 
       */
      virtual const Configuration & getDefinition();

      /**
       * Creates a registry object
       * 
       * @param type     - the object type
       * @param path
       * @param fileName
       * @return 
       */
      virtual bool create( const Config::Type &type,
                           const DString &path,
                           const DString &fileName );

      /**
       * Destroys the object
       * 
       * @return 
       */
      virtual bool destroy();

      /**
       * Refreshes the object's attributes
       * 
       * @return 
       */
      virtual bool refresh();

      /**
       * Causes an object to persist
       * 
       * @return 
       */
      virtual bool persist();

      /**
       * Indicates whether the object is a member
       * of a profile group
       * 
       * @return 
       */
      virtual bool isProfileGroup();

      /**
       * Returns a list of all profile names
       * 
       * @return 
       */
      virtual string_vector getProfileList();

      /**
       * Returns the name of the current profile
       * 
       * @return 
       */
      virtual DString getCurrentProfileName();

      /**
       * Renames the current profile
       * 
       * @param name - new name
       * @return 
       */
      virtual bool renameCurrentProfile( const DString &name );

      /**
       * Returns the file name associated with
       * the profile name
       * 
       * @param name   - the profile name
       * @return 
       */
      virtual DString getFileNameForProfile( const DString &name );

      /**
       * Copies the Configuration profile to this
       * object
       * 
       * @param name   - name of profile to copy
       * @return 
       */
      virtual bool selectProfile( const DString &name );

      /**
       * Creates a new profile
       * 
       * @param name   - name of the new profile
       * @param file   - file name of the new profile
       * @param type   - new profile type
       * @return 
       */
      virtual bool createNewProfile( const DString &name,
                                     const DString &file,
                                     const Config::Type &type );

      /**
       * Deletes a profile
       * 
       * @param name   - name of profile to delete
       * @return 
       */
      virtual bool deleteProfile( const DString &name );

      /**
       * Determines whether the current profile
       * is a member of a subgroup
       * 
       * @return 
       */
      virtual bool isCurrentProfileSubGroup();

      /**
       * Determines whether a profile is a member
       * of a subgroup
       * 
       * @param name   - name of profile to test
       * @return 
       */
      virtual bool isSubGroup( const DString &name );

   // Protected methods
   protected:
      /**
       * Sets the definition in the parent object
       * 
       * @param appName
       */
      void setDefinition( const DString &appName );

      /**
       * Returns the datapath
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

   // Private Methods
   private:
      DString buildApplicationPath( const DString &app );
      bool refreshFromRegistry();
      bool refreshFromIniFile();
      bool persistToRegistry();
      bool persistToIniFile();
      bool deleteRegistry( RegistryKey::Hive hive );
      bool deleteIni();
      bool deleteContainer();

   // Private Members
   private:
      RegistryKey::Hive m_hive;

   #endif
      
   private:
      ConfigBrokerObject *m_pGlobalIni;
      DString m_company;

};

#endif//REGISTRYOBJECT_HPP

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
// $Log:   Y:/VCS/iFastAWD/dicore/registryobject.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:20:24   kovacsro
//Initial revision.
// 
//    Rev 1.5   12 Dec 2000 14:54:50   dt14177
// cleanup and documentation
// 
//    Rev 1.4   Apr 15 1999 11:46:34   DMUM
// String development/enhancement
//
//    Rev 1.3   22 Feb 1999 13:57:42   DT14177
// more UNICODE stuff
//
//    Rev 1.2   18 Feb 1999 10:38:28   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:03:18   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:32   DMUM
//
//
//    Rev 1.1   Aug 13 1998 11:36:38   DMUM
// added renameCurrentProfile()
//
//    Rev 1.6   Jul 14 1998 08:03:58   dmum
// Added getFileNameForProfile()
//
//    Rev 1.5   Jul 13 1998 17:01:42   dmum
// More development
//
//    Rev 1.4   Jul 13 1998 12:22:06   dmum
// More development
//
//    Rev 1.3   Jul 11 1998 16:11:10   dmum
// Development - too many changes to describe
//
//    Rev 1.2   Jul 02 1998 12:02:36   dmum
// cleanup
//
//    Rev 1.1   Nov 19 1997 16:11:38   dmum
// Portability Issues
//
//    Rev 1.0   Nov 10 1997 12:23:44   DSZD
// Configuration extensions.
//
