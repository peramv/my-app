#ifndef REPOSITORYFILE_HPP
#define REPOSITORYFILE_HPP

#  pragma message( "including "__FILE__ )

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

/**@pkg DIDBRKR */

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CASEINSENSITIVECOMPARE_HPP
   #include "caseinsensitivecompare.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#ifndef CLIENTORMARKETINDEX_HPP
   #include "clientormarketindex.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef REPOSITORYDATASOURCE_HPP
   #include "repositorydatasource.hpp"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
   #include <fstream>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

// Forward references
class DataElementProperties;

class DIDBRKR_LINKAGE RepositoryFile  : public RepositoryDataSource
{
public:
   /**
    * constructor
    *
    * @param fileName (in) full path to the input file.
    */
   RepositoryFile( const std::string &fileName );
   /**
    * destructor
    */
   ~RepositoryFile();

   /**
    * Returns a list of field id's that make up a data set.
    *
    * @param dataSetName
    *                  - (in) name of the data set
    * @param clientLocale
    *                  - the client/locale name
    * @param dataSetId - (out) numerical id of the requested data
    *                    set
    * @param fieldList - (out) a vector containing the field names
    * @param dstrType  - (out) the data type of the dataset
    * @return
    */
   virtual SEVERITY getDataSet( const DString &dataSetName,
                                const ClientLocale& clientLocale,
                                unsigned long &dataSetId,
                                string_vector &fieldList,
                                DString &dstrType );

   /**
    * Returns a list of field id's that make up a data set.
    *
    * @param dataSetId - (in) numerical id of the requested data
    *                    set
    * @param clientLocale
    *                  - the client/locale name
    * @param dataSetName
    *                  - (out) name of the data set
    * @param fieldList - (out) a vector containing the field names
    * @param dstrType  - (out) the data type of the dataset
    * @return
    */
   virtual SEVERITY getDataSet( unsigned long dataSetId,
                                const ClientLocale& clientLocale,
                                DString &dataSetName,
                                string_vector &fieldList,
                                DString &dstrType );


   virtual void getFieldType( unsigned long fieldId, DString & fieldType );

   virtual DataElementProperties *getField( unsigned long fieldId,
                                             const ClientLocale& clientLocale,
                                             bool fExactMatch );
   /**
    * gets the mask string for the field
    *
    * @param maskID     - the mask's id
    * @param maskString - (out) the string to return
    * @param numLanguages
    *                   - (out )the number of languages associated
    *                     with the mask
    * @param pClientLocale
    *                   - (out) the client/locale string
    * @param fExactMatch
    *                   - is an exact match required?
    */
   virtual void getMask( unsigned long maskID,
                         DString & maskString,
                         unsigned long & numLanguages,
                         const ClientLocale * pClientLocale = 0,
                         bool fExactMatch = false );

   /**
    * gets the substitution set for the field
    *
    * @param setID      - the mask's id
    * @param subSetString - (out) the string to return
    * @param numLanguages
    *                   - (out )the number of languages associated
    *                     with the substitution set
    * @param pClientLocale
    *                   - (out) the client/locale string
    * @param fExactMatch
    *                   - is an exact match required?
    */
   virtual void getSubstitutionSet( unsigned long setID,
                                    DString & subSetString,
                                    unsigned long & numLanguages,
                                    const ClientLocale * pClientLocale = 0,
                                    bool fExactMatch = false );

   /**
    * returns the binfile version number
    *
    * @return
    */
   DString getVersionNumber();

   /**
    * a lookup to get the field id
    *
    * @param fieldName
    * @return
    */
   unsigned long getFieldIdFromName( const DString &fieldName );
   /**
    * a lookup to get the dataset id from the name
    *
    * @param dataSetName
    * @return
    */
   unsigned long getIdFromDataSetName( const DString &dataSetName );

   /**
    * Check to see if a DEP has a locale for the "field" items -
    * those fields that are overrideable by clients and markets
    * and are language specific (excluding masks and substitution
    * sets)
    *
    * @param elementName
    * @param clientLocale
    *                   - the desired locale/market/client for the
    *                   data
    * @param fExactMatch
    *                   - set to true to search for only the set
    *                     for a given market/client/language. If
    *                     false, the nearest match for a
    *                     ClientLocale will be returned.  For
    *                     example, if a client is specified, but
    *                     there is no subset override for that
    *                     client, the subset override for the
    *                     market will be returned.
    * @return true if found, false otherwise
    */
   bool fieldFieldHasLocale( const DString &elementName,
                             const ClientLocale &clientLocale,
                             bool fExactMath = false );

   /**
    * Returns whether the dataset has any fields
    *
    * @param elementName
    * @return
    */
   bool hasField( const DString &elementName );

   /**
    * initializer
    */
   void initInstance();

private:
   CriticalSectionLock m_fileLock;
   FILE *m_infile;
   std::string m_fileName;
   unsigned long m_subSectionLength,
                 m_maskSectionLength,
                 m_fieldSectionLength,
                 m_dataSetSectionLength;
   unsigned long m_subSectionOffset,
                 m_maskSectionOffset,
                 m_fieldSectionOffset,
                 m_dataSetSectionOffset;
   unsigned long m_numSubSets,
                 m_numMasks,
                 m_numFields,
                 m_numDataSets;
   unsigned long m_subMarketSectionOffset,
                 m_maskMarketSectionOffset,
                 m_fieldMarketSectionOffset,
                 m_dataMarketSetSectionOffset;
   unsigned long m_subClientSectionOffset,
                 m_maskClientSectionOffset,
                 m_fieldClientSectionOffset,
                 m_dataClientSetSectionOffset;

   typedef std::map< unsigned long,
                     unsigned long,
                     std::less< unsigned long > > OffsetMapType;
   OffsetMapType m_maskOffsetMap,
                 m_subOffsetMap,
                 m_fieldOffsetMap,
                 m_dataSetOffsetMap;
   void buildOffsetMaps();
   void buildMaskOrSetMap( unsigned long idLength, unsigned long lengthLength,
                           unsigned long sectionOffset, unsigned long countLength,
                           unsigned long numItems, OffsetMapType &theMap );

   typedef std::map< DString,
                     unsigned long,
                     CaseInsensitiveCompare > NameToIdMapType;
   NameToIdMapType m_dataSetNameToIdMap, m_fieldNameToIdMap;

   virtual bool readDataProperties( const I_CHAR * dataSetName,
                        const ClientLocale * pClientLocale = 0 );
   virtual bool readDataElementProperties( const I_CHAR *
                                               elementName,
                         const ClientLocale *pClientLocale = 0 );

   virtual bool readDataProperties( unsigned long dataSetID,
                         const ClientLocale *pClientLocale = 0 );
   virtual bool readDataElementProperties( unsigned long elementID,
                         const ClientLocale *pClientLocale = 0 );

   virtual bool readMask( unsigned long maskID,
                         const ClientLocale *pClientLocale = 0 );
   virtual bool readSubstitutionMap( unsigned long maskID,
                         const ClientLocale *pClientLocale = 0 );
   void getBaseMaskOrSet( unsigned long getThisID,
                          unsigned long lengthLength,
                          unsigned long idLength,
                          unsigned long countLength,
                          DString &returnString,
                          OffsetMapType &offsetMap,
                          unsigned long &numLanguages,
                          const ClientLocale *pClientLocale = 0 );
   void _getFieldType( unsigned long ulId, DString & dstrType );
   long _readNum( FILE* infile, int iSize );
   DString& _readString( FILE * infile,
                         int iSize,
                         DString & dstr );

   typedef std::map< ClientOrMarketIndex,
                     unsigned long,
                     std::less< ClientOrMarketIndex > >
         ClientOrMarketOffsetMapType;
   ClientOrMarketOffsetMapType m_maskMarketOffsetMap,
      m_subMarketOffsetMap,
      m_fieldMarketOffsetMap;
   ClientOrMarketOffsetMapType m_maskClientOffsetMap,
      m_subClientOffsetMap,
      m_fieldClientOffsetMap;

   void buildMaskOrSetMarketOrClientMap( unsigned long sectionOffset,
                            ClientOrMarketOffsetMapType & theMap,
                                         bool fClientMap );

   // The non-language-specific parts of the client and market
   // field overrides are placed under the key with "" as the
   // language string.
   void buildFieldMarketOrClientMap( unsigned long sectionOffset,
                            ClientOrMarketOffsetMapType &theMap,
                                     bool fClientMap );

   bool getClientOrMarketMaskOrSet(
      unsigned long ulMaskOrSubId,
      unsigned long ulClientId,
      unsigned long ulMarketId,
      const DString& dstrLanguage,
      ClientOrMarketOffsetMapType &offsetMap,
      DString &dstrReturn );

   SEVERITY getClientOrMarketField( unsigned long fieldId,
                                    ClientOrMarketOffsetMapType &mapOffsets,
                                    bool fAllClients,
                                    string_vector & vecLangCodes,
                                    ul_vector & vecMaskIds,
                                    ul_vector & vecSubSetIds,
                                    DataElementProperties &dep );
   void addId( ul_vector & vector, unsigned long id );
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
// $Log:   Y:/VCS/iFastAWD/inc/repositoryfile.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:34   kovacsro
//Initial revision.
// 
//    Rev 1.21   Jun 22 2001 09:40:50   DT11159
// Fixed a bug in overrides.  If there were overrides for a mask
// or substitution set, but not for a field that used the mask/subtitution set,
// then the overrides were not loaded.  Now, they will be.
//
//    Rev 1.20   May 18 2001 15:33:08   dt24433
// Support for change to Guard\CriticalSectionLock.
//
//    Rev 1.19   Mar 02 2001 14:53:24   dt24433
// Removed unused methods.
// Consistent use of unsigned long for ids.
// Better getMask/getSubstitute processing.
//
//    Rev 1.18   Jan 19 2001 16:58:02   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.17   27 Nov 2000 13:23:28   dt14177
// cleanup
//
//    Rev 1.16   Sep 05 2000 06:05:56   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.15   Aug 24 2000 11:53:38   dtwk
// Update comments
//
//    Rev 1.14   Aug 24 2000 07:24:52   dtwk
// Add in more support for clients and markets
//
//
//    Rev 1.13   Aug 09 2000 08:35:32   dtwk
// Add in support for clients and markets
//
//    Rev 1.12   Jun 08 2000 11:50:56   dtwk
// Add support for case-insensitivity
//
//    Rev 1.11   May 31 2000 09:31:46   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.10   Dec 12 1999 13:04:56   dtwk
// Fix for problem with instantiating a repeatable data set
// before instantiating a data set that contains the repeat data
// set as one of it's fields
//
//    Rev 1.9   Aug 06 1999 14:22:46   DCYK
// Performance improvements.
//
//
//    Rev 1.8   Jul 28 1999 14:20:18   DCYK
// Performance improvements.
//
//
//    Rev 1.7   Jun 14 1999 09:56:02   DCYK
// Use javalocale object for default locales.
//
//

