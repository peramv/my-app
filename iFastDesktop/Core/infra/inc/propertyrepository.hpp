#ifndef PROPERTYREPOSITORY_HPP
#define PROPERTYREPOSITORY_HPP

#  pragma message( "including "__FILE__ )

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

/** @pkg DIDBRKR */

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
   #include <fstream>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef DATAELEMENTPROPERTIES_HPP
   #include "dataelementproperties.hpp"
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#ifndef REPOSITORYFILE_HPP
   #include "repositoryfile.hpp"
#endif

#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
#endif

#ifndef CASEINSENSITIVECOMPARE_HPP
   #include "caseinsensitivecompare.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif


class ClientLocale;

class DIDBRKR_LINKAGE PropertyRepository
{
public:
   /**
    * Gets a pointer to an instance of PropertyRepository.
    * This function must be called before the
    * PropertyRepository can be used in any way.
    *
    * @return
    */
   static PropertyRepository * getInstance();

   /**
    * Returns a pointer to the DataPropertiesImpl object
    * for the given data set name.
    *
    * @param dataSetName
    * @param clientLocale
    * @return
    */
   DataPropertiesImpl *getDataSet( const DString & dataSetName,
                             const ClientLocale & clientLocale,
                             int repeat = 0 );

   /**
    * Returns a pointer to the DataPropertiesImpl object
    * for the given data set Id.
    *
    * @param dataSetId
    * @param clientLocale
    * @return
    */
   DataPropertiesImpl *getDataSet( unsigned long dataSetId,
                             const ClientLocale &clientLocale,
                             int repeat = 0 );

   /**
    * Returns a pointer to the DataElementProperties
    * object for the given field name.
    *
    * @param elementName
    * @param clientLocale
    * @return
    */
   DataElementProperties *getField( const DString &elementName,
                             const ClientLocale &clientLocale );

   /**
    * Returns a pointer to the DataElementProperties
    * object for the given field Id.
    *
    * @param elementId
    * @param clientLocale
    * @return
    */
   DataElementProperties *getField( unsigned long elementId,
                             const ClientLocale &clientLocale );

   /**
    * This method maps a name to an Id.
    *
    * @param fieldName
    * @return
    */
   unsigned long getFieldIdFromName( const DString &fieldName );

   /**
    * This method maps an Id to a name.
    *
    * @param id
    * @param fieldName
    * @return
    */
   const DString &getFieldNameFromId( unsigned long id, DString & fieldName );

   /**
    * Get the mask specified for a given ClientLocale (market/
    *  client/language).
    * If the entry does not exist, numLanguages is set to 0.
    *
    * @param maskID     - the id of the mask
    * @param maskString - this will be set with the mask
    * @param numLanguages
    *                   - this will be set to zero if the mask
    *                     was not found in the bin file
    * @param pClientLocale
    *                   - the requested ClientLocale
    * @param fExactMatch
    *                   - set to true to search for only the mask
    *                     for a given market/client/language.
    *                     If false, the nearest match for
    *                     a ClientLocale will be returned.  For
    *                     example, if a client is specified, but
    *                     there is no mask override for that
    *                     client, the mask override for the market
    *                     will be returned.
    */
   void getMask( unsigned long maskID, DString & maskString,
                 unsigned long & numLanguages,
                 const ClientLocale * pClientLocale = 0,
                 bool fExactMatch = false );

   /**
    * Get the substitution idi string specified for a given
    * ClientLocale (market/client/language).
    * If the entry does not exist, numLanguages is set to 0.
    *
    * @param maskID     - the id of the substitution set
    * @param maskString - this will be set with the substitutions
    * @param numLanguages
    *                   - this will be set to zero if the subset
    *                     was not found in the bin file
    * @param pClientLocale
    *                   - the requested ClientLocale
    * @param fExactMatch
    *                   - set to true to search for only the set
    *                     for a given market/client/language. If
    *                     false, the nearest match for a
    *                     ClientLocale will be returned.  For
    *                     example, if a client is specified, but
    *                     there is no subset override for that
    *                     client, the subset override for the
    *                     market will be returned.
    */
   void getSubstitutionSet( unsigned long setID,
                            DString & subSetString,
                            unsigned long & numLanguages,
                          const ClientLocale * pClientLocale = 0,
                            bool fExactMatch = false );

   /**
    * Getter for case sensitivity flag
    *
    * @return
    */
   static bool isCaseSensitive()
   {
      return s_fCaseSensitive;
   };

   /**
    * Getter for ignoring case on sub keys (substitutes) flag
    *
    * @return
    */
   static bool ignoreCaseOnSubstitutes()
   {
      return s_fIgnoreCaseOnSubKeys;
   };

   /**
    * Getter for version number
    *
    * @return
    */
   DString getVersionNumber();

   /**
    *
    * @param DString
    * @return
    */
   DataElementProperties::ELEMENTTYPE getStoredTypeFromString(
                                               const DString & );

   /**
    * @param DataElementProperties::ELEMENTTYPE
    * @param DString
    * @return true, if the stored type has a string
    *         representation
    */
   bool getStringFromStoredType(
                              DataElementProperties::ELEMENTTYPE,
                              DString & ) const;

   virtual bool formatValue( const DString & elementName,
                             DString & valueString,
                             bool checkValidity = true,
                             const ClientLocale * pClientLocale = 0,
                             const DString & i18nFormat = NULL_STRING,
                             unsigned long lStripFlags = 0
                             // These possible values are
                             // DEP::STRIP_TRAILING and DEP::STRIP_LEADING
                             );

   /**
    * Format the value, using substitutes and masks,
    * and strip leading and trailing spaces or zeroes
    * as indicated by the flags.
    *
    * @param fieldId
    * @param valueString
    * @param checkValidity
    *                   - do a validation?
    * @param pClientLocale
    * @param i18nFormat
    * @param ulStripFlags
    *                   - leading or trailing spaces or zeroes
    * @return
    */
   virtual bool formatValue( unsigned long fieldId,
                             DString & valueString,
                             bool checkValidity = true,
                             const ClientLocale * pClientLocale = 0,
                             const DString & i18nFormat = NULL_STRING,
                             unsigned long ulStripFlags = 0
                             // These possible values are
                             // DEP::STRIP_TRAILING and DEP::STRIP_LEADING
                             );
   /**
    * Perform validation
    *
    * @param fieldId
    * @param valueString
    * @param pClientLocale
    * @return
    */
   virtual bool isValid( unsigned long fieldId,
                         const DString & valueString,
                         const ClientLocale * pClientLocale = 0 );

   /**
    * Perform validation
    *
    * @param fieldId
    * @param valueString
    * @param pClientLocale
    * @return
    */
   virtual bool isValid( const DString & elementName,
                         const DString & valueString,
                         const ClientLocale * pClientLocale = 0 );

   /**
    * Perform validation
    *
    * @param fieldId
    * @param valueString
    * @return
    */
   virtual bool isValidForHost( unsigned long fieldId,
                                const DString & valueString );

   /**
    * Perform validation
    *
    * @param fieldId
    * @param valueString
    * @return
    */
   virtual bool isValidForHost( const DString & elementName,
                                const DString & valueString );

   /**
    * Is the DataSet/field in the redefine map?
    *
    * @param dstrField
    * @param dstrDataSet
    * @return
    */
   bool isValidRedefine( const DString & dstrField,
                         const DString & dstrDataSet );

   /**
    * Unformat the value, using substitutes and masks,
    * and strip leading and trailing spaces or zeroes
    * as indicated by the flags.
    *
    * If checkValidity is true and the field has substitutes, the
    * method will return false if valueString is not one of the
    * valid substitutions.  If the field has no substitutes,
    * checkValidity is not used.
    *
    * @param elementName
    * @param valueString
    * @param pClientLocale
    * @param i18nFormat
    * @param checkValidity
    *                   - do a substitution validation?
    * @return
    */
   virtual bool unformatValue( const DString & elementName,
                               DString & valueString,
                               const ClientLocale * pClientLocale = 0,
                               const DString & i18nFormat = NULL_STRING,
                               bool checkValidity = true );

   /**
    * Unformat the value, using substitutes and masks,
    * and strip leading and trailing spaces or zeroes
    * as indicated by the flags.
    *
    * If checkValidity is true and the field has substitutes, the
    * method will return false if valueString is not one of the
    * valid substitutions.  If the field has no substitutes,
    * checkValidity is not used.
    *
    * @param fieldId
    * @param valueString
    * @param pClientLocale
    * @param i18nFormat
    * @param checkValidity
    *                   - do a substitution validation?
    * @return
    */
   virtual bool unformatValue( unsigned long fieldId,
                               DString & valueString,
                               const ClientLocale * pClientLocale = 0,
                               const DString & i18nFormat = NULL_STRING,
                               bool checkValidity = true );

   /**
    * Returns a pointer to the component property after
    * searching the property map
    *
    * @param fieldName
    * @param pClientLocale
    * @return
    */
   DataComponentProperties * getPropsPtr(
      const DString & fieldName,
      const ClientLocale * pClientLocale = 0 );

   /**
    * Getter for the DataSource client
    *
    * @return
    */
   DString getClient();

private: // declarations
   static const DString EMPTY_STRING;  // Used for returns
   typedef std::map< unsigned long, DataPropertiesImpl *,
                     std::less< unsigned long > > DPIMapType;
   typedef std::map< unsigned long, DataElementProperties *,
                     std::less< unsigned long > > DEMapType;
   typedef std::map< DString, int, CaseInsensitiveCompare >
      NameMapType;
   typedef std::map< DString, string_vector, std::less< DString > >
      RedefineMapType;

private: // methods
   PropertyRepository();
   ~PropertyRepository();
   void _initInstance();
   static void _killInstance();

   static void _deregister( void * pObj )
   {
      PropertyRepository * pPR = ( PropertyRepository * ) pObj;
      pPR->_killInstance();
   }

   DataComponentProperties * _getPropsPtr( unsigned long fieldId,
                            const ClientLocale * pClientLocale,
                            int repeat );

   DataElementProperties::JUSTIFICATION _getJustificationFromChar(
                                                  I_CHAR fJust );

   void _addRedefinableField( const DString & dstrFieldName );

   void _addRedefine( const DString & dstrFieldName,
                      const DString & dstrDataSet );

   DataPropertiesImpl * _findLoadedDataSet(
                                      const DString & dstrName );

   DataElementProperties * _getField( unsigned long elementId,
                               const ClientLocale & clientLocale,
                                     unsigned long & maskId,
                                     unsigned long & hostMaskId,
                                     unsigned long & subSetId,
                                     bool & fCreatedNew );

private: // attributes

   DPIMapType m_dpiMap;
   DEMapType m_deMap;

   NameMapType m_dataSetToIdMap;

   RedefineMapType m_redefineMap;

   RepositoryFile * m_dataSource;

   SingletonRegister m_register;

   static PropertyRepository * _pInstance;

   static bool s_fCaseSensitive;
   static bool s_fIgnoreCaseOnSubKeys;
};

#endif

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
// $Log:   Y:/VCS/iFastAWD/inc/propertyrepository.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:30   kovacsro
//Initial revision.
// 
//    Rev 1.30   Sep 21 2001 16:20:12   DT11159
// Made changes to support the new bin file format.
//
//    Rev 1.29   May 18 2001 15:32:00   dt24433
// Added support for cacheing ignoreCaseOnSubstitutes.
//
//    Rev 1.28   Mar 02 2001 14:51:12   dt24433
// Changed implementation for getting case sensitivity flag.
// Removed unused methods.
// Changed to use mutex instead of SWMR lock.
// getFiledNameFromId changed to do more efficient lookup instead of always going back to the file.
//
//    Rev 1.27   30 Oct 2000 16:03:32   dt14177
// cleanup
//
//    Rev 1.26   Sep 30 2000 14:25:22   dt17817
// Added flag to check validity of substitutions to PropertyRepository::unformatValue()
//
//    Rev 1.25   Aug 24 2000 11:53:36   dtwk
// Update comments
//
//    Rev 1.24   Aug 24 2000 07:24:46   dtwk
// Add in more support for clients and markets
//
//
//    Rev 1.23   Aug 09 2000 08:35:28   dtwk
// Add in support for clients and markets
//
//    Rev 1.22   Jun 08 2000 11:50:54   dtwk
// Add support for case-insensitivity
//
//    Rev 1.21   May 31 2000 09:31:40   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.20   Apr 10 2000 11:48:22   dtwk
// Updates for thread-safety
//
//    Rev 1.19   Apr 04 2000 10:01:16   dtwk
// Updates for thread safety
//
//    Rev 1.18   Dec 12 1999 13:04:50   dtwk
// Fix for problem with instantiating a repeatable data set
// before instantiating a data set that contains the repeat data
// set as one of it's fields
//
//    Rev 1.17   Nov 29 1999 07:29:36   dtwk
// Add support for redefines
//
//    Rev 1.16   Nov 09 1999 07:14:04   dtwk
// Add parameter to formatValue for STRIP_TRAILING and STRIP_LEADING
//
//    Rev 1.15   Oct 07 1999 14:06:22   DCYK
// Add support for CLIENT field in bin file.
//
//
//    Rev 1.14   Oct 06 1999 11:33:28   DCYK
// Add support for redefines.
//
//
//    Rev 1.13   Sep 03 1999 12:54:08   dtwk
// Add isValidForHost
// Tweak method signature for unformatValue
//
//
//    Rev 1.12   Aug 26 1999 13:51:56   dtwk
// Remove parameter from formatValue for Jerry
//
//    Rev 1.11   Aug 20 1999 15:37:02   DCYK
// Added locale parameter to isValid, added isI18NValid function.
//
//
//    Rev 1.10   Aug 16 1999 14:46:44   DCYK
// Added "unformatValue".  Added more parameters to "formatValue".  Re-ordered parameters.
//
//
//    Rev 1.9   Aug 06 1999 14:22:42   DCYK
// Performance improvements.
//
//
//    Rev 1.7   Aug 05 1999 16:38:36   DCYK
// Performance improvements from Tom H. & Michael M.
//
//
//    Rev 1.6   Aug 04 1999 09:50:38   DCYK
// Fix bug returning severity from from getField.
// Add isValid and formatValue methods.
//
//
//    Rev 1.5   Jul 28 1999 14:20:14   DCYK
// Performance improvements.
//
//
//    Rev 1.4   Jun 14 1999 16:16:24   DCYK
// Clean up.
//
//

