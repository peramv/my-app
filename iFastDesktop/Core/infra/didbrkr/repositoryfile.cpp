// *****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, databases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
// *****************************************************************************
//
// ^FILE   : repositoryfile.cpp
// ^AUTHOR : Chris Kennedy
// ^DATE   : 06/01/1999
//
// ----------------------------------------------------------
//
// ^CLASS : RepositoryFile
//
// ^INHERITS FROM : RepositoryDataSource
//
// ^MEMBER VARIABLES :
//    ^NAME :        m_infile;
//    ^TYPE :        FILE *
//    ^DESCRIPTION : File pointer to input "bin" file.
//
//    ^NAME :        m_fileName
//    ^TYPE :        std::string
//    ^DESCRIPTION : Full path to input "bin" file.
//
//    ^NAME :        m_versionNumber
//    ^TYPE :        std::wstring
//    ^DESCRIPTION : Wide string for "bin" file version number.
//
//    ^NAME :        m_crcNumber
//    ^TYPE :        std::wstring
//    ^DESCRIPTION : Wide string for "bin" file CRC number.
//
//    ^NAME :        m_subSectionLength
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Length of the substitute section in the "bin" file.
//
//    ^NAME :        m_maskSectionLength
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Length of the mask section in the "bin" file.
//
//    ^NAME :        m_fieldSectionLength
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Length of the field section in the "bin" file.
//
//    ^NAME :        m_dataSetSectionLength
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Length of the data set section in the "bin" file.
//
//    ^NAME :        m_subSectionOffset
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Offset of the substitute section in the "bin" file.
//
//    ^NAME :        m_maskSectionOffset
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Offset of the mask section in the "bin" file.
//
//    ^NAME :        m_fieldSectionOffset
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Offset of the field section in the "bin" file.
//
//    ^NAME :        m_dataSetSectionOffset
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Offset of the data set section in the "bin" file.
//
//    ^NAME :        m_numSubSets
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Number of substitution sets in the "bin" file.
//
//    ^NAME :        m_numMasks
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Number of masks in the "bin" file.
//
//    ^NAME :        m_numFields
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Number of fields in the "bin" file.
//
//    ^NAME :        m_numDataSets
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Number of data sets in the "bin" file.
//
//    ^NAME :        m_maskOffsetMap
//    ^TYPE :        std::map< long, long, std::less< long > >
//    ^DESCRIPTION : Map of the offsets to masks based on the mask id.
//
//    ^NAME :        m_subOffsetMap
//    ^TYPE :        std::map< long, long, std::less< long > >
//    ^DESCRIPTION : Map of the offsets to substitution sets based on the
//                   substitution set id.
//
//    ^NAME :        m_fieldOffsetMap
//    ^TYPE :        std::map< long, long, std::less< long > >
//    ^DESCRIPTION : Map of the offsets to fields based on the field id.
//
//    ^NAME :        m_dataSetOffsetMap
//    ^TYPE :        std::map< long, long, std::less< long > >
//    ^DESCRIPTION : Map of the offsets to data sets based on the data set id.
//
//    ^NAME :        m_dataSetNameToIdMap
//    ^TYPE :        std::map< DString, long, std::less< DString > >
//    ^DESCRIPTION : Map of data set id's based on data set names.
//
//    ^NAME :        m_fieldNameToIdMap
//    ^TYPE :        std::map< DString, long, std::less< DString > >
//    ^DESCRIPTION : Map of field id's based on field names.
//
// ^CODING COMMENTS  :
//
// *****************************************************************************

/* Bin File format

1  byte order

6  version number

6  crc

1  read only

5  num markets

10  market id                           ----|
                                            |
5  market name length                       |
                                            |
0+ market name                          ----|

10 default market id

5  num clients

10 client id                            ----|
                                            |
10 market id                                |
                                            |
5  client name length                       |
                                            |
0+ client name                          ----|

10 default client id

10 total mask section length (includes
   masks, market overrides, client
   overides, language market overrides,
   and language client overides)

10 mask section length (no overrides)

5  num masks

10 mask id                              ---------|
                                                 |
5  num languages                                 |
                                                 |
6  mask language code                   ----|    |
                                            |    |
5  mask length                              |    |
                                            |    |
0+ mask                                 ----+----|

10 language mask market overrides
   section length

5  num language mask overrides

10 market id                            ---------|
                                                 |
10 mask id                                       |
                                                 |
5  num languages overridden                      |
                                                 |
6  language code                        ----|    |
                                            |    |
5  mask length                              |    |
                                            |    |
0+ mask                                 ----+----|

10 language mask client overrides
   section length

5  num language mask overrides

10 market id                            ---------|
                                                 |
10 client id                                     |
                                                 |
10 mask id                                       |
                                                 |
5  num languages overridden                      |
                                                 |
6  language code                        ----|    |
                                            |    |
5  mask length                              |    |
                                            |    |
0+ mask                                 ----+----|

10 total substitution set section
   length (includes substitution set,
   market overrides, and client
   overides)

10 substitution set section length (base)

5  num substitution sets

10 substitution set id                  ---------|
                                                 |
5  num languages                                 |
                                                 |
6  substitution set language code       ----|    |
                                            |    |
5  substitution set length                  |    |
                                            |    |
0+ substitution set                     ----+----|

10 market substitution set section
   length

5  num substitution sets

10 market id                            ---------|
                                                 |
10 substitution set id                           |
                                                 |
5  num languages overridden             ----|    |
                                            |    |
6  substitution set language code           |    |
                                            |    |
5  substitution set length                  |    |
                                            |    |
0+ substitution set                     ----+----|

10 client substitution set section
   length

5  num substitution sets

10 market id                            ---------|
                                                 |
10 client id                                     |
                                                 |
10 substitution set id                           |
                                                 |
5  num languages overridden             ----|    |
                                            |    |
6  substitution set language code           |    |
                                            |    |
5  substitution set length                  |    |
                                            |    |
0+ substitution set                     ----+----|

10 total field section length (base,
   language, client, market)

10 field section length (base and
   language)

5  num fields

10 field id                             ---------|
                                                 |
5  field name length                             |
                                                 |
0+ field name                                    |
                                                 |
2  field type                                    |
                                                 |
5  field max length                              |
                                                 |
5  field min length                              |
                                                 |
5  field length after decimal                    |
                                                 |
10 field mask id                                 |
                                                 |
10 field host mask id                            |
                                                 |
10 field substitution set id                     |
                                                 |
1  field allow null                              |
                                                 |
5  num languages                                 |
                                                 |
6  field language code                  ----|    |
                                            |    |
5  field label length                       |    |
                                            |    |
0+ field label                              |    |
                                            |    |
5  field default value length               |    |
                                            |    |
0+ field default value                      |    |
                                            |    |
1  field default value is null              |    |
                                            |    |
1  field justification                      |    |
                                            |    |
1  field fill character                 ----+----|

10 market field section length
   (market and language market)

5  num fields

10 market id                            ---------|
                                                 |
10 field id                                      |
                                                 |
5  field min length                              |
                                                 |
10 field mask id                                 |
                                                 |
10 field substitution set id                     |
                                                 |
1  field allow null                              |
                                                 |
5  num languages overridden                      |
                                                 |
6  field language code                  ----|    |
                                            |    |
5  field label length                       |    |
                                            |    |
0+ field label                              |    |
                                            |    |
5  field default value length               |    |
                                            |    |
0+ field default value                      |    |
                                            |    |
1  field default value is null              |    |
                                            |    |
1  field justification                      |    |
                                            |    |
1  field fill character                 ----+----|

10 client field section length
   (client and language client)

5  num fields

10 market id                            ---------|
                                                 |
10 client id                                     |
                                                 |
10 field id                                      |
                                                 |
5  field min length                              |
                                                 |
10 field mask id                                 |
                                                 |
10 field substitution set id                     |
                                                 |
1  field allow null                              |
                                                 |
5  num languages overridden                      |
                                                 |
6  field language code                  ----|    |
                                            |    |
5  field label length                       |    |
                                            |    |
0+ field label                              |    |
                                            |    |
5  field default value length               |    |
                                            |    |
0+ field default value                      |    |
                                            |    |
1  field default value is null              |    |
                                            |    |
1  field justification                      |    |
                                            |    |
1  field fill character                 ----+----|

10 data set section length

5  num data sets

10 data set length                      ---------|
                                                 |
10 data set id                                   |
                                                 |
5  data set name length                          |
                                                 |
0+ data set name                                 |
                                                 |
5  field count                                   |
                                                 |
10 field id                             ----|    |
                                            |    |
5  field repeat count                       |    |
                                            |    |
10 field repeat count id                    |    |
                                            |    |
5  field flags                          ----+----|

*/

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef REPOSITORYFILE_HPP
   #include "repositoryfile.hpp"
#endif

#ifndef BINFILEHEADER_HPP
   #include "binfileheader.hpp"
#endif

#ifndef CONDITIONMANANGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DIDBRKR_H
   #include "didbrkr.h"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

#include <iostream>

#ifndef INCLUDE_IOSTREAM
#define INCLUDE_IOSTREAM
   #include <iostream>
#endif

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
   #include <fstream>
#endif

#ifndef INCLUDED_MEMORY
#define INCLUDED_MEMORY
   #include <memory>
#endif

using namespace std;

namespace
{
   const I_CHAR *const CLASS_NAME = I_( "RepositoryFile" );

   const unsigned long VERSION_NUM_LENGTH = 6;
   const unsigned long CLIENT_LENGTH = 5;
   const unsigned long CRC_LENGTH = 6;
   const unsigned long SECTION_LENGTH = 10;
   const unsigned long LANGUAGE_COUNT_LENGTH = 5;
   const unsigned long LANGUAGE_CODE_LENGTH = 6;
   const unsigned long MASK_ID_LENGTH = 10;
   const unsigned long MASK_LENGTH_LENGTH = 5;
   const unsigned long MASK_COUNT_LENGTH = 5;
   const unsigned long SET_ID_LENGTH = 10;
   const unsigned long SET_LENGTH_LENGTH = 5;
   const unsigned long SET_COUNT_LENGTH = 5;
   const unsigned long FIELD_ID_LENGTH = 10;
   const unsigned long FIELD_ACTUAL_LENGTH = 5;
   const unsigned long FIELD_MIN_LENGTH = 5;
   const unsigned long FIELD_COUNT_LENGTH = 5;
   const unsigned long FIELD_TYPE_LENGTH = 2;
   const unsigned long FIELD_LENGTH = 10;
   const unsigned long FIELD_NAME_LENGTH_LENGTH = 5;
   const unsigned long FIELD_LANGUAGE_COUNT_LENGTH = 5;
   const unsigned long FIELD_LABEL_LENGTH_LENGTH = 5;
   const unsigned long FIELD_DEFAULT_VALUE_LENGTH_LENGTH = 5;
   const unsigned long FIELD_JUSTIFICATION_LENGTH = 1;
   const unsigned long FIELD_AFTER_DECIMAL_LENGTH = 5;
   const unsigned long FIELD_MASK_ID_LENGTH = 10;
   const unsigned long FIELD_HOSTMASK_ID_LENGTH = 10;
   const unsigned long FIELD_SET_ID_LENGTH = 10;
   const unsigned long FIELD_NUM_LANGUAGES_LENGTH = 5;
   const unsigned long DATASET_ID_LENGTH = 10;
   const unsigned long DATASET_NAME_LENGTH_LENGTH = 5;
   const unsigned long DATASET_NUM_ELEMENTS_LENGTH = 5;
   const unsigned long DATASET_FIELD_ID_LENGTH = 10;
   const unsigned long DATASET_FIELD_REPEAT_COUNT_LENGTH = 5;
   const unsigned long DATASET_FIELD_FLAGS_LENGTH = 5;
   const unsigned long DATASET_COUNT_LENGTH = 5;
   const unsigned long DATASET_LENGTH_LENGTH = 10;

   const short CHAR_SIZE = sizeof( wchar_t );
}

namespace DBSUBS
{
   extern CLASS_IMPORT const long No_Substitutions;
}

unsigned long wcToULong( wchar_t *inBuff, int charCount )
{
   char charBuff[ 11 ], *inChar;
   memset( charBuff, 0, 11 );
   inChar = ( char * ) inBuff;
   for ( int i = 0; i < charCount; i++ )
   {
      charBuff[ i ] = inChar[ i * 2 ];
   }
   return strtoul( charBuff, (char **)NULL, 10 );
}

// DTWK change calls to this to use _readNum!
unsigned long getULongFromFile( FILE *infile , int fieldLength )
{
   wchar_t readBuff[ 20 ];
   wmemset( readBuff, 0, 20 );
   fread( (char *)readBuff, CHAR_SIZE, fieldLength, infile );
   return wcToULong( readBuff, fieldLength );
}


RepositoryFile::RepositoryFile( const std::string &_fileName ) :
   RepositoryDataSource()
{
   unsigned long fileOffset = 0;
   unsigned long ulTempValue;
   BinFileHeader *pBinFileHeader = BinFileHeader::getInstance();
   m_fileName = _fileName;
   Guard crit( &m_fileLock );

   m_infile = fopen( m_fileName.c_str(), "rb" );

   if ( m_infile )
   {
      pBinFileHeader->getClientName(
         pBinFileHeader->getDefaultMarket(),
         pBinFileHeader->getDefaultClient(),
         m_client );

      fileOffset = pBinFileHeader->getHeaderSize();

      // Masks
      fseek( m_infile, fileOffset, SEEK_SET );
      m_maskSectionOffset = ftell( m_infile );
      m_maskSectionLength = _readNum( m_infile, 10 );
      ulTempValue = _readNum( m_infile, 10 ); // Mask section length (no overrides)
      m_numMasks = _readNum( m_infile, 5 );
      fseek( m_infile,
             fileOffset + ( ( m_maskSectionLength + 10  ) * CHAR_SIZE ),
             SEEK_SET );

      // Substitutions
      m_subSectionOffset = ftell( m_infile );
      m_subSectionLength = _readNum( m_infile, 10 );
      ulTempValue = _readNum( m_infile, 10 ); // Sub section length (no overrides)
      m_numSubSets = _readNum( m_infile, 5 );
      fseek( m_infile,
                m_subSectionOffset + ( ( m_subSectionLength + 10 ) * CHAR_SIZE ),
             SEEK_SET );

      // Fields
      m_fieldSectionOffset = ftell( m_infile );
      m_fieldSectionLength = _readNum( m_infile, 10 );
      ulTempValue = _readNum( m_infile, 10 ); // Field section length (no overrides)
      m_numFields = _readNum( m_infile, 5 );
      fseek( m_infile,
             m_fieldSectionOffset +
                ( ( m_fieldSectionLength + 10 ) * CHAR_SIZE  ),
             SEEK_SET );

      // Data Sets
      m_dataSetSectionOffset = ftell( m_infile );
      m_dataSetSectionLength = _readNum( m_infile, 10 );
      m_numDataSets = _readNum( m_infile, 5 );

      // Market offsets
      fileOffset = m_maskSectionOffset + ( 10 * CHAR_SIZE );
      fseek( m_infile, fileOffset, SEEK_SET );

      unsigned long ulMaskBaseSectionLength = _readNum( m_infile, 10 );
      m_maskMarketSectionOffset =
         fileOffset + ( 10 + ulMaskBaseSectionLength ) * CHAR_SIZE;

      fseek( m_infile, m_maskMarketSectionOffset, SEEK_SET );
      unsigned long ulMaskMarketSectionLength = _readNum( m_infile, 10 );
      m_maskClientSectionOffset =
         m_maskMarketSectionOffset +
            ( 10 + ulMaskMarketSectionLength ) * CHAR_SIZE;

      // Substitution offsets
      fileOffset = m_subSectionOffset + ( 10 * CHAR_SIZE );
      fseek( m_infile, fileOffset, SEEK_SET );

      unsigned long ulSubBaseSectionLength = _readNum( m_infile, 10 );
      m_subMarketSectionOffset =
         fileOffset + ( 10 + ulSubBaseSectionLength ) * CHAR_SIZE;

      fseek( m_infile, m_subMarketSectionOffset, SEEK_SET );
      unsigned long ulSubMarketSectionLength = _readNum( m_infile, 10 );
      m_subClientSectionOffset =
         m_subMarketSectionOffset +
            ( 10 + ulSubMarketSectionLength ) * CHAR_SIZE;

      // Field offsets
      fileOffset = m_fieldSectionOffset + ( 10 * CHAR_SIZE );
      fseek( m_infile, fileOffset, SEEK_SET );

      unsigned long ulFieldBaseSectionLength = _readNum( m_infile, 10 );
      m_fieldMarketSectionOffset =
         fileOffset + ( 10 + ulFieldBaseSectionLength ) * CHAR_SIZE;

      fseek( m_infile, m_fieldMarketSectionOffset, SEEK_SET );
      unsigned long ulFieldMarketSectionLength = _readNum( m_infile, 10 );
      m_fieldClientSectionOffset =
         m_fieldMarketSectionOffset +
            ( 10 + ulFieldMarketSectionLength ) * CHAR_SIZE;
   }
}


RepositoryFile::~RepositoryFile()
{
   if ( m_infile )
   {
      Guard crit( &m_fileLock );
      fclose( m_infile );
   }
}


void RepositoryFile::initInstance()
{
   Guard crit( &m_fileLock );
   buildOffsetMaps();
}


void RepositoryFile::buildMaskOrSetMap(
   unsigned long idLength,
   unsigned long lengthLength,
   unsigned long sectionOffset,
   unsigned long countLength,
   unsigned long numItems,
   OffsetMapType &theMap
   )
{
   unsigned long counter, tempId, numLanguages,
                 tempLength;

   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildMaskOrSetMap"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   fseek( m_infile, sectionOffset, 0 );
   if ( ferror( m_infile ) )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildMaskOrSetMap"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   for ( counter = 0; counter < numItems; counter++ )
   {
      tempId = getULongFromFile( m_infile, idLength );
      theMap[ tempId ] = sectionOffset;
      sectionOffset += idLength * CHAR_SIZE;
      numLanguages = _readNum( m_infile, LANGUAGE_COUNT_LENGTH );
      sectionOffset += LANGUAGE_COUNT_LENGTH * CHAR_SIZE;

      for ( unsigned long langCount = 0; langCount < numLanguages; langCount++ )
      {
         sectionOffset += LANGUAGE_CODE_LENGTH * CHAR_SIZE;
         fseek( m_infile, sectionOffset, 0 );
         if ( ferror( m_infile ) )
         {
            THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildMaskOrSetMap"),
                           DIDBRKR_FILE_SEEK_FAILED );
         }
         sectionOffset += lengthLength * CHAR_SIZE;
         tempLength = getULongFromFile( m_infile, lengthLength );
         sectionOffset += tempLength * CHAR_SIZE;
         fseek( m_infile, sectionOffset, 0 );
         if ( ferror( m_infile ) )
         {
            THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildMaskOrSetMap"),
                           DIDBRKR_FILE_SEEK_FAILED );
         }
      }
   }
}


void RepositoryFile::buildMaskOrSetMarketOrClientMap(
   unsigned long sectionOffset,
   ClientOrMarketOffsetMapType &theMap,
   bool fClientMap )
{
   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME,
                     I_( "buildMaskOrSetMarketOrClientMap" ),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   fseek( m_infile, sectionOffset, 0 );
// DTWK these ferror calls don't even work (according to docs - test them)!
   if ( ferror( m_infile ) )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME,
                     I_( "buildMaskOrSetMap" ),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   unsigned long ulSectionLength = _readNum( m_infile, 10 );

   if ( 0 == ulSectionLength )
   {
      return;
   }

   unsigned long ulNumElements = _readNum( m_infile, 5 );

   ClientOrMarketIndex clomIndex;

   // We are loading market overrides, so set the client to "No Client"
   if ( !fClientMap )
   {
      clomIndex.ulClientId = BinFileHeader::s_ulNoClient;
   }

   for ( unsigned long ulIndex = 0; ulIndex < ulNumElements; ++ulIndex )
   {
      clomIndex.ulMarketId = _readNum( m_infile, 10 );

      if ( fClientMap )
      {
         clomIndex.ulClientId = _readNum( m_infile, 10 );
      }

      clomIndex.ulMaskOrSubId = _readNum( m_infile, 10 );

      unsigned long ulNumLanguages = _readNum( m_infile, 5 );

      for ( unsigned long ulLangIndex = 0; ulLangIndex < ulNumLanguages;
            ++ulLangIndex )
      {
         _readString( m_infile, 6, clomIndex.dstrLanguageCode );
         clomIndex.dstrLanguageCode.stripTrailing();
         theMap[ clomIndex ] = ftell( m_infile );

         unsigned long ulLength = _readNum( m_infile, 5 );
         unsigned long ulOffset = ftell( m_infile ) + ( ulLength * CHAR_SIZE );

         fseek( m_infile, ulOffset, SEEK_SET );
      }
   }
}


void RepositoryFile::buildFieldMarketOrClientMap(
   unsigned long sectionOffset,
   ClientOrMarketOffsetMapType &theMap,
   bool fClientMap )
{
   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME,
                     I_( "buildFieldMarketOrClientMap" ),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   fseek( m_infile, sectionOffset, 0 );
// DTWK these ferror calls don't even work (according to docs - test them)!
   if ( ferror( m_infile ) )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME,
                     I_( "buildMaskOrSetMap" ),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   unsigned long ulSectionLength = _readNum( m_infile, 10 );

   if ( 0 == ulSectionLength )
   {
      return;
   }

   unsigned long ulNumElements = _readNum( m_infile, 5 );

   ClientOrMarketIndex clomIndex;

   // We are loading market overrides, so set the client to "No Client"
   if ( !fClientMap )
   {
      clomIndex.ulClientId = BinFileHeader::s_ulNoClient;
   }

   for ( unsigned long ulIndex = 0; ulIndex < ulNumElements; ++ulIndex )
   {
      clomIndex.ulMarketId = _readNum( m_infile, 10 );

      if ( fClientMap )
      {
         clomIndex.ulClientId = _readNum( m_infile, 10 );
      }

      clomIndex.ulMaskOrSubId = _readNum( m_infile, 10 );
      clomIndex.dstrLanguageCode = I_( "" );

      unsigned long ulOffset = ftell( m_infile );

      // The non-language-specifiec parts of the client and market field
      // overrides are placed under the key with "" as the language string.
      theMap[ clomIndex ] = ulOffset;

      ulOffset += ( 5 + 10 + 10 + 1 ) * CHAR_SIZE;
      fseek( m_infile, ulOffset, SEEK_SET );

      unsigned long ulNumLanguages = _readNum( m_infile, 5 );

      for ( unsigned long ulLangIndex = 0; ulLangIndex < ulNumLanguages;
            ++ulLangIndex )
      {
         _readString( m_infile, 6, clomIndex.dstrLanguageCode );
         clomIndex.dstrLanguageCode.stripTrailing();
         theMap[ clomIndex ] = ftell( m_infile );

         // Label
         unsigned long ulLength = _readNum( m_infile, 5 );
         unsigned long ulOffset = ftell( m_infile ) + ( ulLength * CHAR_SIZE );
         fseek( m_infile, ulOffset, SEEK_SET );

         // Default value
         ulLength = _readNum( m_infile, 5 );
         ulOffset = ftell( m_infile ) + ( ulLength * CHAR_SIZE );

         ulOffset += ( 2 + 1 + 1 ) * CHAR_SIZE;
         fseek( m_infile, ulOffset, SEEK_SET );
      }
   }
}


void RepositoryFile::buildOffsetMaps()
{
   DString tempFieldName;
   bool found = false;
   unsigned long fileOffset = 0, fieldLength,
                 counter,
                 tempFieldId,
                 tempDataSetId, fieldNameLength,
                 fieldLabelLength;

   DString dstrFieldName;
   DString dstrTemp;

   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildOffsetMaps"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

// DTWK no longer true?
   // This function is only called from the constructor.  Since the constructor
   // has control of the mutex, no need to wait & post it here ( I hope ).

   buildMaskOrSetMap( MASK_ID_LENGTH, MASK_LENGTH_LENGTH,
                      m_maskSectionOffset + ( ( 10 + 10 + 5 ) * CHAR_SIZE ),
                      MASK_COUNT_LENGTH, m_numMasks, m_maskOffsetMap );
   buildMaskOrSetMap( SET_ID_LENGTH, SET_LENGTH_LENGTH,
                      m_subSectionOffset + ( ( 10 + 10 + 5 ) * CHAR_SIZE ),
                      SET_COUNT_LENGTH, m_numSubSets, m_subOffsetMap );

   buildMaskOrSetMarketOrClientMap( m_maskMarketSectionOffset,
                                    m_maskMarketOffsetMap,
                                    false );

   buildMaskOrSetMarketOrClientMap( m_maskClientSectionOffset,
                                    m_maskClientOffsetMap,
                                    true );

   buildMaskOrSetMarketOrClientMap( m_subMarketSectionOffset,
                                    m_subMarketOffsetMap,
                                    false );

   buildMaskOrSetMarketOrClientMap( m_subClientSectionOffset,
                                    m_subClientOffsetMap,
                                    true );

   buildFieldMarketOrClientMap( m_fieldMarketSectionOffset,
                                m_fieldMarketOffsetMap,
                                false );

   buildFieldMarketOrClientMap( m_fieldClientSectionOffset,
                                m_fieldClientOffsetMap,
                                true );

   fileOffset = m_fieldSectionOffset + ( 10 + 10 + 5 ) * CHAR_SIZE;
   fseek( m_infile, fileOffset, 0 );
   if ( ferror( m_infile ) )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildOffsetMaps"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   for ( counter = 0; counter < m_numFields; counter++ )
   {
      tempFieldId = getULongFromFile( m_infile, FIELD_ID_LENGTH );
      m_fieldOffsetMap[ tempFieldId ] = fileOffset;
      fileOffset += FIELD_ID_LENGTH * CHAR_SIZE;

      fieldNameLength = getULongFromFile( m_infile, FIELD_NAME_LENGTH_LENGTH );
      _readString( m_infile, fieldNameLength, dstrFieldName );

      m_fieldNameToIdMap[ dstrFieldName ] = tempFieldId;
      fileOffset += ( fieldNameLength + FIELD_NAME_LENGTH_LENGTH ) * CHAR_SIZE;

      fileOffset += ( 2 + 5 + 5 + 5 + 10 + 10 + 10 + 1 ) * CHAR_SIZE;
      fseek( m_infile, fileOffset, 0 );
      if ( ferror( m_infile ) )
      {
         THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildOffsetMaps"),
                        DIDBRKR_FILE_SEEK_FAILED );
      }

      unsigned long ulNumLanguages = _readNum( m_infile, LANGUAGE_COUNT_LENGTH );
      fileOffset += LANGUAGE_COUNT_LENGTH * CHAR_SIZE;

      for ( unsigned int iLang = 0; iLang < ulNumLanguages; ++iLang )
      {
         _readString( m_infile, LANGUAGE_CODE_LENGTH, dstrTemp );

         fieldLabelLength = _readNum( m_infile, 5 );
         fileOffset +=
            ( LANGUAGE_CODE_LENGTH + 5 + fieldLabelLength ) * CHAR_SIZE;

         fseek( m_infile, fileOffset, 0 );
         if ( ferror( m_infile ) )
         {
            THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildOffsetMaps"),
                           DIDBRKR_FILE_SEEK_FAILED );
         }

         unsigned long ulDefaultValueLen = _readNum( m_infile, 5 );
         fileOffset += ( 5 + ulDefaultValueLen ) * CHAR_SIZE;

         fseek( m_infile, fileOffset, 0 );
         if ( ferror( m_infile ) )
         {
            THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildOffsetMaps"),
                           DIDBRKR_FILE_SEEK_FAILED );
         }

         fileOffset += ( 1 + 1 + 1 ) * CHAR_SIZE;
         fseek( m_infile, fileOffset, 0 );
         if ( ferror( m_infile ) )
         {
            THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildOffsetMaps"),
                           DIDBRKR_FILE_SEEK_FAILED );
         }
      }
   }

   fileOffset = m_dataSetSectionOffset + ( DATASET_COUNT_LENGTH + 10 ) * CHAR_SIZE;
   fseek( m_infile, fileOffset, 0 );
   if ( ferror( m_infile ) )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildOffsetMaps"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   for ( counter = 0; counter < m_numDataSets; ++counter )
   {
      fieldLength = _readNum( m_infile, DATASET_LENGTH_LENGTH );
      tempDataSetId = _readNum( m_infile, DATASET_ID_LENGTH );
      m_dataSetOffsetMap[ tempDataSetId ] = fileOffset;

      fieldNameLength = getULongFromFile( m_infile, DATASET_NAME_LENGTH_LENGTH );
      _readString( m_infile, fieldNameLength, tempFieldName );

      m_dataSetNameToIdMap[ tempFieldName ] = tempDataSetId;

      fileOffset += ( DATASET_LENGTH_LENGTH + fieldLength ) * CHAR_SIZE;
      fseek( m_infile, fileOffset, 0 );
      if ( ferror( m_infile ) )
      {
         THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("buildOffsetMaps"),
                        DIDBRKR_FILE_SEEK_FAILED );
      }
   }
}


unsigned long RepositoryFile::getFieldIdFromName( const DString &fieldName )
{
   unsigned long returnFieldId = ULONG_MAX;

   NameToIdMapType::iterator iter = m_fieldNameToIdMap.find( fieldName );
   if ( iter != m_fieldNameToIdMap.end() )
   {
      return (*iter).second;
   }
   return returnFieldId;
}


unsigned long RepositoryFile::getIdFromDataSetName( const DString &dataSetName )
{
   unsigned long returnDataSetId = ULONG_MAX;

   NameToIdMapType::iterator iter = m_dataSetNameToIdMap.find( dataSetName );
   if ( iter != m_dataSetNameToIdMap.end() )
   {
      return (*iter).second;
   }
   return returnDataSetId;
}


SEVERITY RepositoryFile::getDataSet( const DString &dataSetName,
                                     const ClientLocale& clientLocale,
                                     unsigned long &dataSetId,
                                     string_vector &fieldList,
                                     DString & dstrType )
{
   MAKEFRAMEAUTOPROMOTE( DIDBRKR_COMPONENT_NAME,
                         I_("RepositoryFile::getDataSet") );
   DString tempDataSetName;
   dataSetId = getIdFromDataSetName( dataSetName );
   if ( dataSetId == ULONG_MAX )
   {
      DString msg( I_("dataset=") );
      msg += dataSetName;
      ADDCONDITIONFROMFILEIDI( DIDBRKR_DATASET_NOT_FOUND, msg.c_str() );
   }
   else
   {
      if ( getDataSet( dataSetId,
                       clientLocale,
                       tempDataSetName,
                       fieldList,
                       dstrType ) > NO_SEVERITY )
      {
          DString msg( I_("dataset=") );
          msg += dataSetName;
          ADDCONDITIONFROMFILEIDI( DIDBRKR_DATASET_NOT_FOUND, msg.c_str() );
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


SEVERITY RepositoryFile::getDataSet( unsigned long dataSetId,
                                     const ClientLocale& clientLocale,
                                     DString &dataSetName,
                                     string_vector &fieldList,
                                     DString & dstrType )
{
   MAKEFRAMEAUTOPROMOTE( DIDBRKR_COMPONENT_NAME,
                         I_("RepositoryFile::getDataSet") );
   bool found = false;

   DString tempFieldType;

   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getDataSet"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   Guard crit( &m_fileLock );
   OffsetMapType::iterator iter = m_dataSetOffsetMap.find( dataSetId );
   if ( m_dataSetOffsetMap.end() != iter )
   {
      unsigned long fileOffset = (*iter).second;
      fileOffset += DATASET_LENGTH_LENGTH * CHAR_SIZE;
      fileOffset += DATASET_ID_LENGTH * CHAR_SIZE;
      fseek( m_infile, fileOffset, 0 );
      if ( ferror( m_infile ) )
      {
         THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getDataSet"),
                        DIDBRKR_FILE_SEEK_FAILED );
      }
      found = true;
   }
   if ( found )
   {
      unsigned long dataSetNameLength =
         _readNum( m_infile, DATASET_NAME_LENGTH_LENGTH );
      _readString( m_infile, dataSetNameLength, dataSetName );

      unsigned long fieldCount = getULongFromFile( m_infile,
                                                   DATASET_NUM_ELEMENTS_LENGTH);
      DString temp;

      for ( unsigned long fieldCounter = 0;
            fieldCounter < fieldCount;
            ++fieldCounter )
      {
         _readString( m_infile, DATASET_FIELD_ID_LENGTH, temp );
         fieldList.push_back( temp );

         _readString( m_infile, DATASET_FIELD_ID_LENGTH, temp );
         // fieldList.push_back( temp ); // ID of the repeat count field.

         _readString( m_infile, DATASET_FIELD_REPEAT_COUNT_LENGTH, temp );
         fieldList.push_back( temp );

         _readString( m_infile, DATASET_FIELD_FLAGS_LENGTH, temp );
         fieldList.push_back( temp );
      }

      dstrType = I_( " V" );
   }
   return GETCURRENTHIGHESTSEVERITY();
}


DataElementProperties * RepositoryFile::getField(
                                unsigned long fieldId,
                                const ClientLocale& clientLocale,
                                bool fExactMatch )
{
   const I_CHAR * METHOD = I_( "RepositoryFile::getField( unsigned long, const ClientLocale &, bool )" );
   MAKEFRAMEAUTOPROMOTE( DIDBRKR_COMPONENT_NAME, METHOD );

   DataElementProperties *pDEP = NULL;
   unsigned long fileOffset;
   DString fieldName;
   unsigned long fieldLength;
   DString fieldType;
   unsigned long maxLength;
   unsigned long minLength;
   unsigned long decimalPlace;
   unsigned long maskId;
   DString mask;
   unsigned long hostMaskId;
   DString hostMask;
   unsigned long subSetId;
   DString subSet;
   unsigned long numLanguages;
   DString fieldLabel;
   DString defaultValue;
   I_CHAR justification;
   I_CHAR fillChar;
   bool fAllowNull;
   bool fDefaultValueIsNull;
   bool found;
   unsigned long fieldNameLength;
   DString dstrTemp;
   OffsetMapType::iterator iter;
   ul_vector vecSubSetIds;
   ul_vector vecMaskIds;
   string_vector vecLangCodes;

   Guard crit( &m_fileLock );

   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getField"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   found = false;
   fileOffset = 0;

   const DString& locCountryCode = clientLocale.getLocale();
   ClientLocale cloc( I_( "enUS" ),
                      BinFileHeader::s_ulNoMarket,
                      BinFileHeader::s_ulNoClient );

   iter = m_fieldOffsetMap.find( fieldId );
   if ( m_fieldOffsetMap.end() != iter )
   {
      fileOffset = (*iter).second;
      fileOffset += FIELD_ID_LENGTH * CHAR_SIZE;
      // Skip field ID.
      fseek( m_infile, fileOffset, SEEK_SET );
      if ( ferror( m_infile ) )
      {
         THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getField"),
                        DIDBRKR_FILE_SEEK_FAILED );
      }
      found = true;
   }

   if ( found )
   {
      // Get the field name length and field name.
      fieldNameLength = getULongFromFile( m_infile, FIELD_NAME_LENGTH_LENGTH );
      _readString( m_infile, fieldNameLength, fieldName );

      // Get the field type
      _readString( m_infile, FIELD_TYPE_LENGTH, fieldType );

      // get the field length
      maxLength = getULongFromFile( m_infile, FIELD_ACTUAL_LENGTH );
      minLength = getULongFromFile( m_infile, FIELD_MIN_LENGTH );
      decimalPlace = getULongFromFile( m_infile, FIELD_AFTER_DECIMAL_LENGTH );
      maskId = getULongFromFile( m_infile, FIELD_MASK_ID_LENGTH );
      hostMaskId = getULongFromFile( m_infile, FIELD_HOSTMASK_ID_LENGTH );
      subSetId = getULongFromFile( m_infile, FIELD_SET_ID_LENGTH );
      fAllowNull = ( _readNum( m_infile, 1 ) != 0 );
      numLanguages = _readNum( m_infile, 5 );

      found = false;

      if ( numLanguages )
      {
         unsigned long numLanguagesTemp;

         fileOffset = ftell( m_infile ); // Save current position.

         numLanguagesTemp = 0;
         getMask( hostMaskId, hostMask, numLanguagesTemp, &cloc, fExactMatch );
         if ( 0 == numLanguagesTemp )
         {
            hostMask = I_( "" );
         }

         fseek( m_infile, fileOffset, SEEK_SET ); // Restore current position.

         pDEP = new DataElementProperties( fieldId,
                                           fieldName,
                                           fieldType,
                                           hostMask,
                                           maxLength,
                                           minLength,
                                           decimalPlace,
                                           fAllowNull );


         DString langCode;
         unsigned long counter;

         for ( counter = 0; counter < numLanguages; counter++ )
         {
            _readString( m_infile, LANGUAGE_CODE_LENGTH, langCode );
            langCode.stripTrailing();

            if ( locCountryCode == langCode )
            {
               found = true;
            }

            cloc.setLocale( langCode );
            vecLangCodes.push_back( langCode );

            fieldLength = getULongFromFile( m_infile, FIELD_LABEL_LENGTH_LENGTH );
            _readString( m_infile, fieldLength, fieldLabel );

            fieldLength = getULongFromFile( m_infile,
                                            FIELD_DEFAULT_VALUE_LENGTH_LENGTH );
            _readString( m_infile, fieldLength, defaultValue );

            fDefaultValueIsNull = ( _readNum( m_infile, 1 ) != 0 );

            // get justification
            _readString( m_infile, 1, dstrTemp );
            justification = dstrTemp.c_str()[ 0 ];

            // get fill char
            _readString( m_infile, 1, dstrTemp );
            fillChar = dstrTemp.c_str()[ 0 ];

            fileOffset = ftell( m_infile ); // Save current position.

            pDEP->addFieldLocale( cloc,
                                  fillChar,
                                  justification,
                                  defaultValue,
                                  fieldLabel,
                                  fDefaultValueIsNull );

            // Add to the list of masks.  Add the maskId even if it is
            // DBSUBS::No_Substitutions because there may be a default mask
            // in the registry.
            addId( vecMaskIds, maskId );

            // Add to the list of substitution sets.
            if ( subSetId != DBSUBS::No_Substitutions )
            {
               addId( vecSubSetIds, subSetId );
            }

            fseek( m_infile, fileOffset, SEEK_SET ); // Restore current position.
         }
      }
   }
   else
   {
      DString msg( I_("element=") );
      msg += asString( fieldId );
      ADDCONDITIONFROMFILEIDI( DIDBRKR_ELEMENT_NOT_FOUND, msg.c_str() );

      if ( pDEP )
      {
         delete pDEP;
         pDEP = NULL;
      }
   }

   if ( pDEP )
   {
      getClientOrMarketField( fieldId, m_fieldClientOffsetMap, true,
                              vecLangCodes, vecMaskIds, vecSubSetIds, *pDEP );
   }

   return( pDEP );
}


SEVERITY RepositoryFile::getClientOrMarketField( unsigned long fieldId,
                                                 ClientOrMarketOffsetMapType & mapOffsets,
                                                 bool fAllClients,
                                                 string_vector & vecLangCodes,
                                                 ul_vector & vecMaskIds,
                                                 ul_vector & vecSubSetIds,
                                                 DataElementProperties & dep )
{
   const I_CHAR * METHOD = I_( "RepositoryFile::getClientOrMarketField( unsigned long, ClientOrMarketOffsetMapType &, bool, DataElementProperties & )" );
   MAKEFRAMEAUTOPROMOTE( DIDBRKR_COMPONENT_NAME, METHOD );

   unsigned long fileOffset;
   DString fieldName;
   unsigned long fieldLength;
   DString fieldType;
   unsigned long minLength;
   unsigned long maskId;
   DString mask;
   DString hostMask;
   unsigned long subSetId;
   DString subSet;
   unsigned long numLanguages;
   DString fieldLabel;
   DString defaultValue;
   I_CHAR justification;
   I_CHAR fillChar;
   bool fAllowNull;
   bool fDefaultValueIsNull;
   bool found;
   DString dstrTemp;
   unsigned long ulClientId;
   unsigned long ulMarketId;
   BinFileHeader * pBinFileHeader;

   pBinFileHeader = BinFileHeader::getInstance();

   ClientLocale cloc( I_( "enUS" ),
                      BinFileHeader::s_ulNoMarket,
                      BinFileHeader::s_ulNoClient );

   BinFileHeader::cmi_vector vecClientMarkets;
   BinFileHeader::cmi_vector::iterator iterClientMarket;
   BinFileHeader::cmi_vector::iterator iterClientMarketEnd;

   if ( fAllClients )
   {
      pBinFileHeader->getClients( vecClientMarkets );
   }
   else
   {
      ul_vector vecMarkets;
      ul_vector_iterator iterMarket;
      ul_vector_iterator iterMarketEnd;
      BinFileHeader::ClientMarketIndex cmIndex;

      pBinFileHeader->getMarkets( vecMarkets );

      iterMarketEnd = vecMarkets.end();

      for ( iterMarket = vecMarkets.begin(); iterMarket != iterMarketEnd; iterMarket++ )
      {
         cmIndex.ulMarketId = *iterMarket;
         cmIndex.ulClientId = BinFileHeader::s_ulNoClient;

         vecClientMarkets.push_back( cmIndex );
      }
   }

   iterClientMarketEnd = vecClientMarkets.end();

   for ( iterClientMarket = vecClientMarkets.begin();
         iterClientMarket != iterClientMarketEnd;
         iterClientMarket++ )
   {
      ulMarketId = (*iterClientMarket).ulMarketId;
      cloc.setMarket( ulMarketId );
      ulClientId = (*iterClientMarket).ulClientId;
      cloc.setClient( ulClientId );

      // The index of the non-language-specific overrides

      ClientOrMarketIndex clomIndex( ulClientId, ulMarketId, fieldId, NULL_STRING );

      ClientOrMarketOffsetMapType::iterator iter = mapOffsets.find( clomIndex );

      if ( mapOffsets.end() != iter )
      {
         fileOffset = (*iter).second;
         fseek( m_infile, fileOffset, 0 );
         found = true;

         minLength = _readNum( m_infile, 5 );
         maskId = _readNum( m_infile, 10 );
         subSetId = _readNum( m_infile, 10 );
         fAllowNull = ( _readNum( m_infile, 1 ) != 0 );
         numLanguages = _readNum( m_infile, 5 );

         dep.addBaseLocale( cloc, minLength, fAllowNull );

         if ( numLanguages )
         {
            DString langCode;
            unsigned long counter;

            for ( counter = 0; counter < numLanguages; counter++ )
            {
               _readString( m_infile, LANGUAGE_CODE_LENGTH, langCode );
               cloc.setLocale( langCode );

               fieldLength = getULongFromFile( m_infile, FIELD_LABEL_LENGTH_LENGTH );
               _readString( m_infile, fieldLength, fieldLabel );

               fieldLength = getULongFromFile( m_infile,
                                               FIELD_DEFAULT_VALUE_LENGTH_LENGTH );
               _readString( m_infile, fieldLength, defaultValue );

               fDefaultValueIsNull = ( _readNum( m_infile, 1 ) != 0 );

               // get justification
               _readString( m_infile, 1, dstrTemp );
               justification = dstrTemp.c_str()[ 0 ];

               // get fill char
               _readString( m_infile, 1, dstrTemp );
               fillChar = dstrTemp.c_str()[ 0 ];

               fileOffset = ftell( m_infile ); // Save current position.

               dep.addFieldLocale( cloc,
                                   fillChar,
                                   justification,
                                   defaultValue,
                                   fieldLabel,
                                   fDefaultValueIsNull );

               // Add to the list of masks.
               if ( maskId != DBSUBS::No_Substitutions )
               {
                  addId( vecMaskIds, maskId );
               }

               // Add to the list of substitution sets.
               if ( subSetId != DBSUBS::No_Substitutions )
               {
                  addId( vecSubSetIds, subSetId );
               }

               fseek( m_infile, fileOffset, SEEK_SET ); // Restore current position.
            }
         }
      }
   }

   //
   // For the current field, load all masks and substitution sets for all
   // combinations of market and client.
   //

   fileOffset = ftell( m_infile ); // Save current position.

   string_vector_const_iterator iterLangCodes;
   string_vector_const_iterator iterLangCodesEnd;

   iterLangCodesEnd = vecLangCodes.end();
   iterClientMarketEnd = vecClientMarkets.end();
   unsigned long numLanguagesTemp;

   for ( iterLangCodes = vecLangCodes.begin();
         iterLangCodes != iterLangCodesEnd;
         iterLangCodes++ )
   {
      for ( iterClientMarket = vecClientMarkets.begin();
            iterClientMarket != iterClientMarketEnd;
            iterClientMarket++ )
      {
         cloc.setLocale( *iterLangCodes );
         ulMarketId = (*iterClientMarket).ulMarketId;
         cloc.setMarket( ulMarketId );
         ulClientId = (*iterClientMarket).ulClientId;
         cloc.setClient( ulClientId );

         ul_vector_const_iterator iter;

         for ( iter = vecMaskIds.begin(); iter != vecMaskIds.end(); ++iter )
         {
            numLanguagesTemp = 0;
            getMask( *iter, mask, numLanguagesTemp, &cloc, false );
            if ( 0 == numLanguagesTemp )
            {
               mask = I_( "" );
            }

            dep.addMaskLocale( cloc, mask );
         }

         for ( iter = vecSubSetIds.begin(); iter != vecSubSetIds.end(); ++iter )
         {
            numLanguagesTemp = 0;
            getSubstitutionSet( *iter, subSet, numLanguagesTemp, &cloc, false );
            if ( 0 == numLanguagesTemp )
            {
              subSet = I_( "" );
            }

            dep.addSubsLocale( cloc, subSet );
         }
      }
   }

   fseek( m_infile, fileOffset, SEEK_SET ); // Restore current position.

   return GETCURRENTHIGHESTSEVERITY();
}


void RepositoryFile::getFieldType( unsigned long fieldId, DString & fieldType )
{
   unsigned long fileOffset;
   bool found;
   unsigned long fieldNameLength;

   Guard crit( &m_fileLock );

   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getField"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   found = false;
   fileOffset = 0;

   OffsetMapType::iterator iter = m_fieldOffsetMap.find( fieldId );
   if ( m_fieldOffsetMap.end() != iter )
   {
      fileOffset = (*iter).second;
      fileOffset += FIELD_ID_LENGTH * CHAR_SIZE;
      // Skip field ID.
      fseek( m_infile, fileOffset, SEEK_SET );
      if ( ferror( m_infile ))
      {
         THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getField"),
                        DIDBRKR_FILE_SEEK_FAILED );
      }
      found = true;
   }

   if ( found )
   {
      // Skip the field name length and field name.
      fieldNameLength = getULongFromFile( m_infile, FIELD_NAME_LENGTH_LENGTH );
      fseek( m_infile, fieldNameLength * CHAR_SIZE, SEEK_CUR );

      // Get the field type
      _readString( m_infile, FIELD_TYPE_LENGTH, fieldType );
   }
   else
   {
      fieldType = NULL_STRING;
   }

   return;
}


void RepositoryFile::getMask( unsigned long maskID, DString &maskString,
                              unsigned long &numLanguages,
                              const ClientLocale *pClientLocale,
                              bool fExactMatch )
{
   if ( 0 == pClientLocale )
   {
      pClientLocale = &( ClientLocale::getDefaultClientLocale() );
   }

   numLanguages = 0;

   Guard crit( &m_fileLock );
   if ( BinFileHeader::s_ulNoClient != pClientLocale->getClientIndex() )
   {
      if ( getClientOrMarketMaskOrSet(
              maskID, pClientLocale->getClientIndex(), pClientLocale->getMarketIndex(),
              pClientLocale->getLocale(), m_maskClientOffsetMap, maskString ) )
      {
         numLanguages = 1;
      }

      if ( fExactMatch || numLanguages )
      {
         return;
      }
   }

   if ( BinFileHeader::s_ulNoMarket != pClientLocale->getMarketIndex() )
   {
      if ( getClientOrMarketMaskOrSet(
              maskID, BinFileHeader::s_ulNoClient,
              pClientLocale->getMarketIndex(),
              pClientLocale->getLocale(), m_maskMarketOffsetMap, maskString ) )
      {
         numLanguages = 1;
      }

      if ( fExactMatch || numLanguages )
      {
         return;
      }
   }

   getBaseMaskOrSet( maskID, MASK_LENGTH_LENGTH,
                     MASK_ID_LENGTH, MASK_COUNT_LENGTH, maskString,
                     m_maskOffsetMap, numLanguages, pClientLocale );

   return;
}


void RepositoryFile::getSubstitutionSet( unsigned long setID,
                                         DString &subSetString,
                                         unsigned long &numLanguages,
                                         const ClientLocale *pClientLocale,
                                         bool fExactMatch )
{
   if ( 0 == pClientLocale )
   {
      pClientLocale = &( ClientLocale::getDefaultClientLocale() );
   }

   numLanguages = 0;

   Guard crit( &m_fileLock );

   if ( BinFileHeader::s_ulNoClient != pClientLocale->getClientIndex() )
   {
      if ( getClientOrMarketMaskOrSet(
              setID, pClientLocale->getClientIndex(),
              pClientLocale->getMarketIndex(),
              pClientLocale->getLocale(), m_subClientOffsetMap, subSetString ) )
      {
         numLanguages = 1;
      }

      if ( fExactMatch || numLanguages )
      {
         return;
      }
   }

   if ( BinFileHeader::s_ulNoMarket != pClientLocale->getMarketIndex() )
   {
      if ( getClientOrMarketMaskOrSet(
              setID, BinFileHeader::s_ulNoClient,
              pClientLocale->getMarketIndex(),
              pClientLocale->getLocale(), m_subMarketOffsetMap,
              subSetString ) )
      {
         numLanguages = 1;
      }

      if ( fExactMatch || numLanguages )
      {
         return;
      }
   }

   getBaseMaskOrSet( setID, SET_LENGTH_LENGTH,
                     SET_ID_LENGTH, SET_COUNT_LENGTH, subSetString,
                     m_subOffsetMap, numLanguages, pClientLocale );
   return;
}


void RepositoryFile::getBaseMaskOrSet( unsigned long getThisID,
                                       unsigned long lengthLength,
                                       unsigned long idLength,
                                       unsigned long countLength,
                                       DString &returnString,
                                       OffsetMapType &offsetMap,
                                       unsigned long &numLanguages,
                                       const ClientLocale *pClientLocale )
{
   DString tempString;
   bool found = FALSE;
   unsigned long tempLength, fileOffset = 0;
   numLanguages = 0;

   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getBaseMaskOrSet"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   OffsetMapType::iterator iter = offsetMap.find( getThisID );
   if ( offsetMap.end() != iter )
   {
      fileOffset = (*iter).second;
      fileOffset += idLength * CHAR_SIZE;
      fseek( m_infile, fileOffset, 0 );
      if ( ferror( m_infile ))
      {
         THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getBaseMaskOrSet"),
                        DIDBRKR_FILE_SEEK_FAILED );
      }
      found = true;
   }
   if ( found )
   {
      found = false;

      fseek( m_infile, fileOffset, 0 );
      if ( ferror( m_infile ) )
      {
         THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getBaseMaskOrSet"),
                        DIDBRKR_FILE_SEEK_FAILED );
      }

      const DString& countryCode =
         pClientLocale ? pClientLocale->getLocale() :
                         ClientLocale::getDefaultClientLocale().getLocale();

      numLanguages = _readNum( m_infile, 5 );
      fileOffset += 5 * CHAR_SIZE;

      // now, loop through all languages under this item id
      for ( unsigned long langCount = 0;
            langCount < numLanguages && !found;
            ++langCount )
      {
         _readString( m_infile, LANGUAGE_CODE_LENGTH, tempString );
         fileOffset += LANGUAGE_CODE_LENGTH * CHAR_SIZE;
         tempString.stripTrailing();
         if ( countryCode == tempString )
         {
            found = true;
         }
         else
         {
            tempLength = getULongFromFile( m_infile, lengthLength );
            fileOffset += lengthLength * CHAR_SIZE;
            fileOffset += tempLength * CHAR_SIZE;
            fseek( m_infile, fileOffset, 0 );
            if ( ferror( m_infile ) )
            {
               THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getBaseMaskOrSet"),
                              DIDBRKR_FILE_SEEK_FAILED );
            }
         }
      }
   }
   if ( found )
   {
      // ok, found both the id & language.  return the actual item
      tempLength = getULongFromFile( m_infile, lengthLength );
      fileOffset += lengthLength * CHAR_SIZE;
      fileOffset += tempLength * CHAR_SIZE;
      _readString( m_infile, tempLength, returnString );
   }
   return;
}


bool RepositoryFile::getClientOrMarketMaskOrSet(
   unsigned long ulMaskOrSubId,
   unsigned long ulClientId,
   unsigned long ulMarketId,
   const DString& dstrLanguage,
   ClientOrMarketOffsetMapType &offsetMap,
   DString &dstrReturn )
{
   unsigned long ulFileOffset;
   dstrReturn = I_( "" );

   if ( !m_infile )
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME, I_("getMaskOrSet"),
                     DIDBRKR_FILE_SEEK_FAILED );
   }

   ClientOrMarketIndex clomIndex(
      ulClientId, ulMarketId, ulMaskOrSubId, dstrLanguage );

   ClientOrMarketOffsetMapType::iterator iter = offsetMap.find( clomIndex );
   if ( offsetMap.end() == iter )
   {
      return false;
   }

   ulFileOffset = ( *iter ).second;

// DTWK validate offset with file size

   fseek( m_infile, ulFileOffset, SEEK_SET );

   unsigned long ulMaskLength = _readNum( m_infile, 5 );
   _readString( m_infile, ulMaskLength, dstrReturn );

   return true;
}


bool RepositoryFile::hasField( const DString &elementName )
{
   if ( m_fieldNameToIdMap.find( elementName ) != m_fieldNameToIdMap.end() )
   {
      return true;
   }
   return false;
}


bool RepositoryFile::readDataProperties( const I_CHAR *dataSetName,
                                         const ClientLocale *pClientLocale  )
{
   return FALSE;
}


bool RepositoryFile::readDataElementProperties( const I_CHAR *elementName,
                                const ClientLocale *pClientLocale  )
{
   return FALSE;
}


bool RepositoryFile::readDataProperties( unsigned long dataSetID,
                         const ClientLocale *pClientLocale  )
{
   return FALSE;
}


bool RepositoryFile::readDataElementProperties( unsigned long elementID,
                                const ClientLocale *pClientLocale  )
{
   return FALSE;
}


bool RepositoryFile::readMask( unsigned long maskID,
                               const ClientLocale *pClientLocale  )
{
   return FALSE;
}


bool RepositoryFile::readSubstitutionMap( unsigned long maskID,
                          const ClientLocale *pClientLocale  )
{
   return FALSE;
}


DString RepositoryFile::getVersionNumber()
{
   BinFileHeader *pBinFileHeader = BinFileHeader::getInstance();
   return pBinFileHeader->getVersionNumber();;
}


long RepositoryFile::_readNum( FILE* infile, int iSize )
{
   if ( iSize > 30 )
   {
      // throw if size too large? - should never be necessary
      iSize = 30;
   }

   wchar_t readBuffer[ 31 ];
   char charBuffer[ 31 ];

   long lOffset = ftell( infile );
   memset( readBuffer, 0, ( iSize + 1 ) * CHAR_SIZE );
   size_t count = fread( readBuffer, CHAR_SIZE, iSize, infile );

   if ( count != iSize )
   {
      DString idiStr = I_( "FILE=" );
      idiStr += DString( m_fileName ).c_str();
      idiStr += I_( ";OFFSET=" );
      idiStr.appendLong( lOffset );
      idiStr += I_( ";EXPECTED=" );
      idiStr.appendLong( CHAR_SIZE * iSize );
      idiStr += I_( ";RECEIVED=" );
      idiStr.appendLong( CHAR_SIZE * count );

      THROWFROMFILEIDI(
         DIDBRKR_COMPONENT_NAME,
         I_( "RepositoryFile::_readNum( FILE* infile, int iSize )" ),
         DIDBRKR_READ_SIZE_FAILED,
         idiStr );
   }

   wcstombs( charBuffer, readBuffer, ( iSize + 1 ) );
   return atol( charBuffer );
}


DString& RepositoryFile::_readString( FILE* infile, int iSize,
                                      DString& dstr )
{
   wchar_t *readBuffer = new wchar_t[ iSize +1 ];
   auto_ptr< wchar_t > autoPtr( readBuffer );

   long lOffset = ftell( infile );

   memset( readBuffer, 0, ( iSize + 1 ) * CHAR_SIZE );
   size_t count = fread( readBuffer, CHAR_SIZE, iSize, infile );

   if ( count != iSize )
   {
      DString idiStr = I_( "FILE=" );
      idiStr += DString( m_fileName ).c_str();
      idiStr += I_( ";OFFSET=" );
      idiStr.appendLong( lOffset );
      idiStr += I_( ";EXPECTED=" );
      idiStr.appendLong( CHAR_SIZE * iSize );
      idiStr += I_( ";RECEIVED=" );
      idiStr.appendLong( CHAR_SIZE * count );

      THROWFROMFILEIDI(
         DIDBRKR_COMPONENT_NAME,
         I_( "RepositoryFile::_readString( FILE* infile, int iSize )" ),
         DIDBRKR_READ_SIZE_FAILED,
         idiStr );
   }

#ifdef DST_UNICODE
   dstr = readBuffer;
#else
   char *charBuffer = new char[ iSize + 1 ];
   auto_ptr< char > autoPtr2( charBuffer );
   wcstombs( charBuffer, readBuffer, ( iSize + 1 ) );
   dstr = charBuffer;
#endif
   return dstr;
}

void RepositoryFile::addId( ul_vector & vecIds, unsigned long id )
{
   bool found = false;
   ul_vector_const_iterator iter;

   for ( iter = vecIds.begin(); iter != vecIds.end(); ++iter )
   {
      if ( *iter == id )
      {
         found = true;
         break;
      }
   }

   if ( !found )
   {
      vecIds.push_back( id );
   }
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/repositoryfile.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:34   kovacsro
// Initial revision.
// 
//    Rev 1.39   Sep 21 2001 16:20:00   DT11159
// Made changes to support the new bin file format.
//
//    Rev 1.38   Jun 22 2001 19:37:14   DT11159
// Changed getField( ) so that a mask locale will be added even if there
// is no mask defined in the data element properties for the field.  This is
// needed because there may be a mask defined in the registry to use
// as a default.  This fixes a bug introduced in the previous revision.
//
//    Rev 1.37   Jun 22 2001 09:40:44   DT11159
// Fixed a bug in overrides.  If there were overrides for a mask
// or substitution set, but not for a field that used the mask/subtitution set,
// then the overrides were not loaded.  Now, they will be.
//
//    Rev 1.36   Jun 21 2001 08:34:26   DT11159
// Fixed a bug in buildFieldMarketOrClientMap( ).  The number of characters
// skipped was too large by one.  There are no "eye catchers" in the bin file
// to verify that it is being read correctly, so the method didn't complain.
//
//    Rev 1.35   May 18 2001 15:22:52   dt24433
// Switched to Guard\CriticalSectionLock from CriticalSection\MutexSemaphore.
//
//    Rev 1.34   Mar 06 2001 19:00:12   dt24433
// Fixed to always call addMaskLocale for cases where generic mask defined in registry.
//
//    Rev 1.33   Mar 02 2001 14:54:04   dt24433
// Removed unused methods.
// Consistent use of unsigned long for ids.
// Better getMask/getSubstitute processing.
//
//    Rev 1.32   Jan 19 2001 16:57:08   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.31   Nov 29 2000 16:27:20   DT11159
// Fixed getField method so that it returns the maskId and subSetId.  The
// method was incorrectly returning the base values when there were overrides.
//
//    Rev 1.30   Oct 05 2000 12:39:20   dt17817
// Fix for substitutions overrides not being found if more than one override
//
//    Rev 1.29   Sep 05 2000 06:20:06   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.28   Aug 24 2000 07:27:04   dtwk
// Add in more support for clients and markets
//
//
//    Rev 1.27   Aug 09 2000 08:42:16   dtwk
// Add in support for clients and markets
//
//    Rev 1.26   Jun 08 2000 11:49:58   dtwk
// Add support for case-insensitivity
//
//    Rev 1.25   May 31 2000 09:33:16   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.24   Dec 12 1999 13:05:58   dtwk
// Fix for problem with instantiating a repeatable data set
// before instantiating a data set that contains the repeat data
// set as one of it's fields
//
//    Rev 1.23   Oct 26 1999 17:07:18   dtwk
// Jerry's fix for reading the .bin file when there are
// clients defined (before it wasn't adjusting for the offsets).
//
//    Rev 1.22   Oct 07 1999 14:05:54   DCYK
// Add support for CLIENT field in bin file.
//
//
//    Rev 1.21   Aug 16 1999 14:45:54   DCYK
// getField was using wrong buffer to read in.
//
//
//    Rev 1.20   Aug 10 1999 11:15:04   DCYK
// Fix bug with allocating buffers.  Leave as static allocations for now.
//
//
//    Rev 1.19   Aug 06 1999 14:21:24   DCYK
// Performance improvements.
//
//
//    Rev 1.18   Aug 05 1999 16:38:02   DCYK
// Performance improvements from Tom H. & Michael M.
//
//
//    Rev 1.17   Aug 04 1999 09:50:04   DCYK
// Fix bug returning severity from from getField.
// Add isValid and formatValue methods.
//
//
//    Rev 1.16   Jul 30 1999 13:57:58   DCYK
// Don't check bin file in getIdFromDataSetName.
//
//
//    Rev 1.15   Jul 29 1999 15:11:52   DCYK
// Complete switch from USen to enUS.
//
//
//    Rev 1.14   Jul 28 1999 14:19:32   DCYK
// Performance improvements.
//
//
//    Rev 1.13   Jul 26 1999 09:50:50   DCYK
// Change "USen" to "enUS".
// Dynamically allocate buffers instead of declaring them as 200 chars.
//
//
//    Rev 1.12   Jul 21 1999 09:54:42   DCYK
// Get default locale from registry.
//
//
//    Rev 1.11   Jun 18 1999 10:55:48   DCYK
// Fixed bug in getField.
//
//
//    Rev 1.10   Jun 14 1999 09:55:10   DCYK
// Use javalocale object to get default locales.
//

