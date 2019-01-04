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
//    Copyright 1996 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DataElementProperties.cpp
// ^AUTHOR : Tony Stryker
// ^DATE   : 10/31/96
//
// ----------------------------------------------------------
//
// ^CLASS    : DataElementProperties
//
// ^INHERITS FROM : DataComponentProperties
//
// ^MEMBER VARIABLES :
//    ^NAME :        _items
//    ^TYPE :        Items
//    ^DESCRIPTION : Describes the type, length, justification, etc. for this
//                   DataElementProperties object.
//
//    ^NAME :        _substitutionMap
//    ^TYPE :        map< string, string, less< string >, allocator >
//    ^DESCRIPTION : Contains the key & value pairs that are used to substitute
//                   values.
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef DATAELEMENTPROPERTIES_HPP
   #include "dataelementproperties.hpp"
#endif

#ifndef BASE_H
   #include "base.h"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#ifndef DCFMTSYM_H
   #include <dcfmtsym.h>
#endif

#ifndef DIDBRKR_H
   #include "didbrkr.h"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif

#ifndef JAVADECIMALFORMAT_HPP
   #include "javadecimalformat.hpp"
#endif

#ifndef JAVANUMBERFORMAT_HPP
   #include "javanumberformat.hpp"
#endif

#ifndef JAVASIMPLEDATEFORMAT_HPP
   #include "javasimpledateformat.hpp"
#endif

#ifndef PROPERTYREPOSITORY_HPP
   #include "propertyrepository.hpp"
#endif

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif

using namespace std;

namespace
{
   const I_CHAR SEPARATOR_CHAR = '=';
   const I_CHAR TERMINATOR_CHAR = ';';
   const I_CHAR EOL_CHAR = '\n';

   // use for cobol signed field conversion
   I_UCHAR pTable[] =
   {
      0x00, 0x01, 0x02, 0x03, 0x37, 0x2D, 0x2E, 0x2F,    //  0x00 - 0x07
      0x16, 0x05, 0x25, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,    //  0x08 - 0x0F
      0x10, 0x11, 0x12, 0x13, 0x3C, 0x3D, 0x32, 0x26,    //  0x10 - 0x17
      0x18, 0x19, 0x3F, 0x27, 0x22, 0x1D, 0x35, 0x1F,    //  0x18 - 0x1F
      0x40, 0x5A, 0x7F, 0x7B, 0x5B, 0x6C, 0x50, 0x7D,    //  0x20 - 0x27
      0x4D, 0x5D, 0x5C, 0x4E, 0x6B, 0x60, 0x4B, 0x61,    //  0x28 - 0x2F
      0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,    //  0x30 - 0x37
      0xF8, 0xF9, 0x7A, 0x5E, 0x4C, 0x7E, 0x6E, 0x6F,    //  0x38 - 0x3F
      0x7C, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,    //  0x40 - 0x47
      0xC8, 0xC9, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,    //  0x48 - 0x4F
      0xD7, 0xD8, 0xD9, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,    //  0x50 - 0x57
      0xE7, 0xE8, 0xE9, 0xAD, 0xE0, 0xBD, 0x5F, 0x6D,    //  0x58 - 0x5F
      0x79, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,    //  0x60 - 0x67
      0x88, 0x89, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,    //  0x68 - 0x6F
      0x97, 0x98, 0x99, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,    //  0x70 - 0x77
      0xA7, 0xA8, 0xA9, 0xC0, 0x6A, 0xD0, 0xA1, 0x07,    //  0x78 - 0x7F
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x80 - 0x87
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x88 - 0x8F
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x90 - 0x97
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x98 - 0x9F
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xA0 - 0xA7
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xA8 - 0xAF
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xB0 - 0xB7
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xB8 - 0xBF
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xC0 - 0xC7
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xC8 - 0xCF
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xD0 - 0xD7
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xD8 - 0xDF
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xE0 - 0xE7
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xE8 - 0xEF
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xF0 - 0xF7
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xF8 - 0xFF
   //};
   //unsigned char achEtoA[] =
   //{
      0x20, 0x01, 0x02, 0x03, 0xFF, 0x09, 0xFF, 0x7F,    //  0x00 - 0x07
      0xFF, 0xFF, 0xFF, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,    //  0x08 - 0x0F
      0x10, 0x11, 0x12, 0x13, 0xFF, 0xFF, 0x08, 0xFF,    //  0x10 - 0x17
      0x18, 0x19, 0xFF, 0xFF, 0xFF, 0x1D, 0xFF, 0x1F,    //  0x18 - 0x1F
      0xFF, 0xFF, 0x1C, 0xFF, 0xFF, 0x0A, 0x17, 0x1B,    //  0x20 - 0x27
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07,    //  0x28 - 0x2F
      0xFF, 0xFF, 0x16, 0xFF, 0xFF, 0x1E, 0xFF, 0x04,    //  0x30 - 0x37
      0xFF, 0xFF, 0xFF, 0xFF, 0x14, 0x15, 0xFF, 0x1A,    //  0x38 - 0x3F
      0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x40 - 0x47
      0xFF, 0xFF, 0xFF, 0x2E, 0x3C, 0x28, 0x2B, 0xFF,    //  0x48 - 0x4F
      0x26, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x50 - 0x57
      0xFF, 0xFF, 0x21, 0x24, 0x2A, 0x29, 0x3B, 0x5E,    //  0x58 - 0x5F
      0x2D, 0x2F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x60 - 0x67
      0xFF, 0xFF, 0x7C, 0x2C, 0x25, 0x5F, 0x3E, 0x3F,    //  0x68 - 0x6F
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x70 - 0x77
      0xFF, 0x60, 0x3A, 0x23, 0x40, 0x27, 0x3D, 0x22,    //  0x78 - 0x7F
      0xFF, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,    //  0x80 - 0x87
      0x68, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x88 - 0x8F
      0xFF, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,    //  0x90 - 0x97
      0x71, 0x72, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0x98 - 0x9F
      0xFF, 0x7E, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,    //  0xA0 - 0xA7
      0x79, 0x7A, 0xFF, 0xFF, 0xFF, 0x5B, 0xFF, 0xFF,    //  0xA8 - 0xAF
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xB0 - 0xB7
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5D, 0xFF, 0xFF,    //  0xB8 - 0xBF
      0x7B, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,    //  0xC0 - 0xC7
      0x48, 0x49, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xC8 - 0xCF
      0x7D, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,    //  0xD0 - 0xD7
      0x51, 0x52, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xD8 - 0xDF
      0x5C, 0xFF, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,    //  0xE0 - 0xE7
      0x59, 0x5A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    //  0xE8 - 0xEF
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,    //  0xF0 - 0xF7
      0x38, 0x39, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF     //  0xF8 - 0xFF
   };

   static const I_CHAR *CLASS_NAME = I_("DataElementProperties");
   const DString s_maskVals( I_("A9#XZ$%") );
}

const DString DataElementProperties::EMPTY_STRING = NULL_STRING;

typedef DataComponentProperties DCP;
typedef DataElementProperties DEP;

//******************************************************************************
//              Public Methods
//******************************************************************************

DataElementProperties::DataElementProperties( const DString &name,
                                              const ClientLocale &clientLocale,
                                              ELEMENTTYPE storedType,
                                              const DString &mask,
                                              const DString &hostMask,
                                              const DString &substitutionString,
                                              unsigned long maxLength,
                                              unsigned long decimalPlace,
                                              const DString &fieldLabel ) :
DCP( name, FALSE, DCP::eDEP ),
   _cfgDisplayMasks( NULL ), _cfgHostMasks( NULL ), pDateHostFormatter( 0 ),
   pNumberHostFormatter( 0 ),
   _ulongId( ULONG_MAX ), _name( name ),
   m_hasMasks( false ),
   m_hasSubstitutes( false )
{
   _items.rounding = true;
   _items.forceMatching = false;
   _items.decimalPlace = decimalPlace;
   _items.maxLength = maxLength;
   _items.storedType = storedType;
   _items.filterType = STRING;

   ClientLocale cloc( clientLocale );
   // All of the BaseAndMarketItems are locale independent, so we use
   // enUS for the locale
   cloc.setLocale( I_( "enUS" ) );
   BaseAndMarketItems *pBamItems = new BaseAndMarketItems();
   MultiKeyPointerMapElement< BaseAndMarketItems >
      mkpElement( pBamItems );
   m_mapBaseAndMarketItems[ cloc ] = mkpElement;
   m_mapBaseAndMarketItems[ cloc ].setDeleteElementOnDestruct( true );

   FieldAndOverrides *pFAOItems = new FieldAndOverrides();
   pFAOItems->fillCharacter = ' ';
   pFAOItems->justification = LEFT;
   pFAOItems->defaultValue = NULL_STRING;
   pFAOItems->fieldLabel = fieldLabel;
   pFAOItems->fDefaultValueIsNull = false;

   MaskAndOverrides *pMAOItems = new MaskAndOverrides();
   pMAOItems->mask = mask;

   SubsAndOverrides *pSAOItems = new SubsAndOverrides();

   if ( substitutionString.length() > 0 )
   {
      fillSubstitutionMapFromString( substitutionString,
                                     pSAOItems->substitutionMap,
                                     pSAOItems->substitutionVector );
      if ( pSAOItems->substitutionMap.size() == 1 )
      {
         SubstitutionMap::iterator iter = pSAOItems->substitutionMap.begin();
         DString key( ( *iter ).first );
         upperCase( key );
         if ( ( -1 != key.find( I_("MASK") )) && mask == NULL_STRING)
         {
            pMAOItems->mask = ( *iter ).second;
            stripTrailing( pMAOItems->mask );
            pSAOItems->substitutionMap.clear();
         }
      }
   }

   FieldAndOverridesMapType::iterator iterF =
      m_mapFieldItems.insert( std::pair< ClientLocale, FieldAndOverrides * >( clientLocale, pFAOItems ) );
   MaskAndOverridesMapType::iterator iterM =
      m_mapMaskItems.insert( std::pair< ClientLocale, MaskAndOverrides * >( clientLocale, pMAOItems ) );
   SubsAndOverridesMapType::iterator iterS =
      m_mapSubsItems.insert( std::pair< ClientLocale, SubsAndOverrides * >( clientLocale, pSAOItems ) );

   m_dstrHostMask = hostMask;
}


DataElementProperties::DataElementProperties(
                                const DString  &name,
                                const ClientLocale &clientLocale,
                                const DString  &defaultValue,
                                bool           repeatable,
                                unsigned long  fixedRepeatSize,
                                unsigned long  maxLength,
                                ELEMENTTYPE    storedType,
                                unsigned long  minLength,
                                unsigned long  decimalPlace,
                                I_CHAR         fillCharacter,
                                ELEMENTTYPE    filterType,
                                JUSTIFICATION  justification,
                                const DString  &mask,
                                const DString  &hostMask,
                                const DString  &substitutionString,
                                const DString  &fieldLabel,
                                bool fAllowNull,
                                bool fDefaultValueIsNull ) :
   DCP( name, repeatable, DCP::eDEP ),
   _cfgDisplayMasks( NULL ), _cfgHostMasks( NULL ),
   pDateHostFormatter( 0 ), pNumberHostFormatter( 0 ),
   _ulongId( ULONG_MAX ), _name( name ),
   m_hasMasks( false ),
   m_hasSubstitutes( false )
{

   _items.rounding = true;
   _items.forceMatching = false;
   _items.decimalPlace = decimalPlace;
   _items.maxLength = maxLength;
   _items.storedType = storedType;
   _items.filterType = filterType;

   ClientLocale cloc( clientLocale );
   // All of the BaseAndMarketItems are locale independent, so we use
   // enUS for the locale
   cloc.setLocale( I_( "enUS" ) );
   BaseAndMarketItems *pBamItems = new BaseAndMarketItems();
   pBamItems->minLength = minLength;
   pBamItems->fAllowNull = fAllowNull;
   MultiKeyPointerMapElement< BaseAndMarketItems >
      mkpElement( pBamItems );
   m_mapBaseAndMarketItems[ cloc ] = mkpElement;
   m_mapBaseAndMarketItems[ cloc ].setDeleteElementOnDestruct( true );

   m_dstrHostMask = hostMask;

   FieldAndOverrides *pFAOItems = new FieldAndOverrides();
   pFAOItems->fillCharacter = fillCharacter;
   pFAOItems->justification = justification;
   pFAOItems->defaultValue = defaultValue;
   pFAOItems->fieldLabel = fieldLabel;
   pFAOItems->fDefaultValueIsNull = fDefaultValueIsNull;

   MaskAndOverrides *pMAOItems = new MaskAndOverrides();
   pMAOItems->mask = mask;

   SubsAndOverrides *pSAOItems = new SubsAndOverrides();

   // Make sure the defaultValue is a valid value for the property
   // Cheap hack - later this should be made smarter.
   if ( defaultValue.length() > maxLength )
   {
      // Another hack due to the default values for signed numbers getting
      // a space at the front and a decimal point placed in them.
      // This points to a semantic difference between the default value in
      // the ddtools and the default value in the c++ code.
      // This should be resolved in the db memory size rewrite.
      if ( ( defaultValue.length() > ( maxLength + 2 ) ) ||
           storedType != DECIMAL )
      {
         // If the default value is too long, just lop off the end.
         pFAOItems->defaultValue = pFAOItems->defaultValue.substr( 0,
                                                                   maxLength );
      }

      // DTWK - Add / Throw a condition later, when the DDTools are fixed so
      // they do not constantly create this condition (by adding trailing
      // spaces)
   }

   if ( substitutionString.length() > 0 )
   {
      fillSubstitutionMapFromString( substitutionString,
                                     pSAOItems->substitutionMap,
                                     pSAOItems->substitutionVector );
      if ( pSAOItems->substitutionMap.size() == 1 )
      {
         SubstitutionMap::iterator iter = pSAOItems->substitutionMap.begin();
         DString key( (*iter).first );
         upperCase( key );
         if ( ( -1 != key.find( I_("MASK") )) && mask == NULL_STRING)
         {
            pMAOItems->mask = (*iter).second;
            stripTrailing( pMAOItems->mask );
            pSAOItems->substitutionMap.clear();
         }
      }
   }

   FieldAndOverridesMapType::iterator iterF =
      m_mapFieldItems.insert( std::pair< ClientLocale, FieldAndOverrides * >( clientLocale, pFAOItems ) );
   MaskAndOverridesMapType::iterator iterM =
      m_mapMaskItems.insert( std::pair< ClientLocale, MaskAndOverrides * >( clientLocale, pMAOItems ) );
   SubsAndOverridesMapType::iterator iterS =
      m_mapSubsItems.insert( std::pair< ClientLocale, SubsAndOverrides * >( clientLocale, pSAOItems ) );

   if ( storedType != DEP::STRING &&
        storedType != DEP::INTEGER &&
        storedType != DEP::DECIMAL &&
        storedType != DEP::BINARY )
   {
      // Initialize Configuration items
      ConfigManager *pMgr = ConfigManager::getManager( I_( "DICORE" ) );
      _cfgDisplayMasks = new Configuration();
      *_cfgDisplayMasks = pMgr->retrieveConfig( I_( "DisplayMasks" ) );
      _cfgHostMasks = new Configuration();
      *_cfgHostMasks = pMgr->retrieveConfig( I_( "HostMasks" ) );
   }
}


// Version used by RepositoryFile - not sure above versions needed/used anymore
DataElementProperties::DataElementProperties(
                                unsigned long  fieldId,
                                const DString  &fieldName,
                                const DString  &fieldType,
                                const DString  &hostMask,
                                unsigned long  maxLength,
                                unsigned long  minLength,
                                unsigned long  decimalPlace,
                                bool           fAllowNull ) :
   DCP( fieldName, false, DCP::eDEP ),
   _cfgDisplayMasks( NULL ), _cfgHostMasks( NULL ),
   pDateHostFormatter( 0 ), pNumberHostFormatter( 0 ),
   _ulongId( fieldId ), _name( fieldName ),
   m_hasMasks( false ),
   m_hasSubstitutes( false )
{
   _items.rounding = true;
   _items.forceMatching = false;
   _items.decimalPlace = decimalPlace;
   _items.maxLength = maxLength;
   _items.storedType = getTypeFromString( fieldType );
   _items.filterType = _items.storedType;

   ClientLocale baseLocale( I_( "enUS" ),
                            BinFileHeader::s_ulNoMarket,
                            BinFileHeader::s_ulNoClient );

   // All of the BaseAndMarketItems are locale independent, so we use
   // enUS for the locale.
   BaseAndMarketItems *pBamItems = new BaseAndMarketItems();
   pBamItems->minLength = minLength;
   pBamItems->fAllowNull = fAllowNull;
   MultiKeyPointerMapElement< BaseAndMarketItems >
      mkpElement( pBamItems );
   m_mapBaseAndMarketItems[ baseLocale ] = mkpElement;
   m_mapBaseAndMarketItems[ baseLocale ].setDeleteElementOnDestruct( true );

   m_dstrHostMask = hostMask;

   if ( _items.storedType != DEP::STRING &&
        _items.storedType != DEP::INTEGER &&
        _items.storedType != DEP::DECIMAL &&
        _items.storedType != DEP::BINARY )
   {
      // Initialize Configuration items
      ConfigManager *pMgr = ConfigManager::getManager( I_( "DICORE" ) );
      _cfgDisplayMasks = new Configuration();
      *_cfgDisplayMasks = pMgr->retrieveConfig( I_( "DisplayMasks" ) );
      _cfgHostMasks = new Configuration();
      *_cfgHostMasks = pMgr->retrieveConfig( I_( "HostMasks" ) );
   }
}


DataElementProperties::ELEMENTTYPE DataElementProperties::getTypeFromString(
                                                      const DString &fieldType )
{
   if ( I_(" X") == fieldType )
   {
      return DataElementProperties::STRING;
   }
   else if ( I_(" 9") == fieldType )
   {
      return DataElementProperties::INTEGER;
   }
   else if ( I_(" S") == fieldType )
   {
      return DataElementProperties::DECIMAL;
   }
   else if ( I_(" B") == fieldType )
   {
      return DataElementProperties::BINARY;
   }
   else if ( I_(" F") == fieldType )
   {
      return DataElementProperties::BOOLEAN;
   }
   else if ( I_(" D") == fieldType )
   {
      return DataElementProperties::I18N_DATE;
   }
   else if ( I_(" T") == fieldType )
   {
      return DataElementProperties::I18N_TIME;
   }
   else if ( I_("DN") == fieldType )
   {
      return DataElementProperties::I18N_DECIMAL;
   }
   else if ( I_(" I") == fieldType )
   {
      return DataElementProperties::I18N_INTEGER;
   }
   else if ( I_(" %") == fieldType )
   {
      return DataElementProperties::I18N_PERCENT;
   }
   else if ( I_(" $") == fieldType )
   {
      return DataElementProperties::I18N_CURRENCY;
   }
   else if ( I_("  ") == fieldType || I_(" N") == fieldType )
   {
      return DataElementProperties::NO_TYPE;
   }
   return DataElementProperties::STRING;
}

DataElementProperties::JUSTIFICATION DataElementProperties::getJustificationFromChar( I_CHAR chJust )
{
   switch( chJust )
   {
      case 'R':
         return DEP::RIGHT;
         break;

      case 'C':
         return DEP::CENTER;
         break;

      case 'L':
         return DEP::LEFT;
         break;

      default:
         return DEP::NO_JUSTIFICATION;
         break;
   }

   return DEP::LEFT;
}

DataElementProperties::~DataElementProperties()
{
   delete _cfgDisplayMasks;
   _cfgDisplayMasks = 0;

   delete _cfgHostMasks;
   _cfgHostMasks = 0;

   delete pDateHostFormatter;
   pDateHostFormatter = 0;

   delete pNumberHostFormatter;
   pNumberHostFormatter = 0;

   // Delete mask items
   for ( MaskAndOverridesMapType::iterator iterM = m_mapMaskItems.begin();
      iterM != m_mapMaskItems.end(); ++iterM )
   {
      delete ( *iterM ).second;
   }
   // Delete substitute items
   for ( SubsAndOverridesMapType::iterator iterS = m_mapSubsItems.begin();
      iterS != m_mapSubsItems.end(); ++iterS )
   {
      delete ( *iterS ).second;
   }
   // Delete field items
   for ( FieldAndOverridesMapType::iterator iterF = m_mapFieldItems.begin();
      iterF != m_mapFieldItems.end(); ++iterF )
   {
      delete ( *iterF ).second;
   }
}


bool DataElementProperties::getAllSubstitutes(
   DString &subValues,
   bool separateWithEOLs,
   const ClientLocale *pClientLocale,
   bool usePropertiesOrder )
{
   if ( !hasSubstitutes( pClientLocale ) )
   {
      return false;
   }
   SubsAndOverrides *items;
   const ClientLocale *pLocLocale =
       pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   {
      SubsAndOverridesMapType::const_iterator iter = findSubs( *pLocLocale );
      if ( iter == m_mapSubsItems.end() )
      {
         DString msg( I_("locale=") );
         msg += pLocLocale->getLocale();
         msg += I_(";element=");
         msg += _name;
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("DataElementProperties::getAllSubstitutes"),
                           DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
      }
      items = ( *iter ).second;
   }

   subValues = NULL_STRING;
   if ( usePropertiesOrder )
   {
      SubstitutionMap::const_iterator mapIter;
      SubStringVectorType::const_iterator iter;
      for ( iter = items->substitutionVector.begin();
            iter != items->substitutionVector.end();
            ++iter )
      {
         mapIter = items->substitutionMap.find( (*iter) );
         subValues += (*mapIter).second;
         if ( separateWithEOLs )
         {
            subValues += '\n';
         }
         else
         {
            subValues += TERMINATOR_CHAR;
         }
      }
   }
   else
   {
      SubstitutionMap::const_iterator iter;
      SubstitutionMap::const_iterator iterEnd = items->substitutionMap.end();
      for ( iter = items->substitutionMap.begin();
            iter != iterEnd;
            ++iter )
      {
         subValues += (*iter).second;
         if ( separateWithEOLs )
         {
            subValues += '\n';
         }
         else
         {
            subValues += TERMINATOR_CHAR;
         }
      }
   }
   return true;
}


DString &DataElementProperties::formatUsingMask(
   DString &valueString,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat ) const
{
   const ClientLocale *rpLocClientLocale =
      rpClientLocale ? rpClientLocale : &ClientLocale::getDefaultClientLocale();
   MaskAndOverrides *items = NULL;
   bool bMaskToApply = false;
   ELEMENTTYPE eType = getStoredType();

   if ( eType != BINARY && eType != BOOLEAN && eType != NO_TYPE )
   {  // only other types can be formatted
      if ( !i18nFormat.length() )
      {
         MaskAndOverridesMapType::const_iterator iter = findMask( *rpLocClientLocale );
         if ( iter == m_mapMaskItems.end() )
         {
            DString msg( I_("locale=") );
            msg += rpLocClientLocale->getLocale();
            msg += I_(";element=");
            msg += _name;
            THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                              I_("DataElementProperties::formatUsingMask"),
                              DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
         }
         items = ( *iter ).second;
         if ( items->mask.length() > 0 )
         {  // We have a mask
            bMaskToApply = true;
         }
      }
      else
      {  // User passed in mask to apply for new format type
         bMaskToApply = true;
      }
   }

   if ( bMaskToApply )
   {
      switch( eType )
      {
         case I18N_DATE:
         case I18N_TIME:
            _formatDateTime( valueString, *rpLocClientLocale, items,
               i18nFormat );
            break;

         case I18N_DECIMAL:
         case I18N_INTEGER:
         case I18N_PERCENT:
         case I18N_CURRENCY:
            _formatNewNumber( valueString, *rpLocClientLocale, items,
               i18nFormat );
            break;

         case STRING:
            if ( items )
            {  // if user passed in i18nFormat with this type,
               //  formatting is ignored.  (Would not fall into this code.)
               _formatString( valueString, *rpLocClientLocale, items );
            }
            break;

         case INTEGER:
            if ( items )
            {  // if user passed in i18nFormat with this type,
               //  formatting is ignored.  (Would not fall into this code.)
               _formatInteger( valueString, *rpLocClientLocale, items );
            }
            break;

         case DECIMAL:
            if ( items )
            {  // if user passed in i18nFormat with this type,
               //  formatting is ignored.  (Would not fall into this code.)
               _formatDecimal( valueString, *rpLocClientLocale, items );
            }
            break;
      };
   }
   return valueString;
}


void DataElementProperties::_formatDateTime(
   DString &valueString,
   const ClientLocale &rpClientLocale,
   MaskAndOverrides *rpItems,
   const DString &i18nFormat
   ) const
{
   JavaSimpleDateFormat *pDisplayFormat = 0;
   try
   {  // Don't attempt to parse a string that's empty (you'll probably get
      // an exception)
      if ( !valueString.stringHasOnly( I_( " " ) ) )
      {
         JavaSimpleDateFormat *pHostFormat = getDateHostFormatter();

         if ( i18nFormat.length() )
         {
            pDisplayFormat = new JavaSimpleDateFormat( i18nFormat,
               rpClientLocale );
         }
         else
         {
            pDisplayFormat = _getDateDisplayFormatter( rpItems, rpClientLocale );
         }

         if ( pDisplayFormat && pHostFormat )
         {
            JavaDate *pDate = pHostFormat->parse( valueString );

            if ( pDate )
            {
               pDisplayFormat->format( *pDate, valueString );
               delete pDate;
            }
         }
         if ( i18nFormat.length() )
         {  // Delete if we created
            delete pDisplayFormat;
         }
      }
   }
   catch ( ConditionException & )
   {
      if ( i18nFormat.length() )
      {  // Delete if we created
         delete pDisplayFormat;
      }
      DString msg( I_( "VALUE=" ) );
      msg += valueString;
      msg += I_( ";HOSTMASK=" );
      msg += getHostMask();
      msg += I_( ";DISPMASK=" );
      if ( i18nFormat.length() )
      {
         msg += i18nFormat;
      }
      else
      {
         msg += rpItems->mask;
      }
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_( "DataElementProperties::_formatDateTime" ),
                        DIDBRKR_I18N_MASK_FORMAT_ERROR, msg.c_str() );
   }
}

void DataElementProperties::_formatDecimal(
   DString &valueString,
   const ClientLocale &rpClientLocale,
   const MaskAndOverrides *rpItems
   ) const
{
   long valDecimalPosition = 0;
   long maskDecimalPosition = 0;
   long srcOffset = 0;
   long targetOffset = 0;
   long maskOffset = 0;
   long valLen = 0;
   I_CHAR thisMaskChar;
   bool isNegative = false;
   long s_maskValsLen = s_maskVals.length();

   DString newValue( rpItems->mask.length(), ' ' );
   long maskLen = rpItems->mask.length();

   strip( valueString );
   if ( -1 == rpItems->mask.find_first_not_of( I_("%.") ) )
   {
      long newLen = valueString.length();
      long decPlace = valueString.find( I_(".") );
      long afterDecimal = newLen - ( decPlace - 1 );
      if ( afterDecimal < 2 )
      {
         padRight( valueString.getImp(), ( 2 - afterDecimal ), '0' );
      }
      valueString.insert( decPlace + 3, I_(".") );
      valueString.erase( decPlace, 1 );
   }
   if ( -1 != valueString.find( I_("-") ))
   {
      isNegative = true;
      valueString = valueString.substr( 1 );
   }

   long oldDecPlace = valueString.find( I_(".") );
   if ( -1 != oldDecPlace )
   {
      stripLeading( valueString, '0' );
      if ( valueString.find( I_(".") ) == 0 )
      {
         valueString = I_("0") + valueString;
      }
   }

   valLen = valueString.length();
   if ( -1 == ( maskOffset = rpItems->mask.find( I_(".") )))
   {
      maskOffset = maskLen - 1;
   }

   targetOffset = maskOffset;

   if ( -1 != ( srcOffset = valueString.find( I_(".") )))
   {
      valDecimalPosition = srcOffset--;
   }
   else
   {
      srcOffset = valDecimalPosition = valLen - 1;
   }

   maskDecimalPosition = maskOffset;

   while ( maskOffset >= 0 )
   {
      thisMaskChar = rpItems->mask[ maskOffset ];
      if ( -1 != s_maskVals.find( thisMaskChar ) )
      {
         if ( srcOffset >= 0 )
         {
            newValue[ targetOffset ] = valueString[ srcOffset-- ];
         }
         else
         {
            switch ( thisMaskChar )
            {
               case '$' :
                  newValue[ targetOffset ] = '$';
                  maskOffset = 0;
                  break;

               case '.' :
                  newValue[ targetOffset ] = '.';
                  break;

               case 'Z' :
                  newValue[ targetOffset ] = '0';
                  break;

               default:
                  newValue[ targetOffset ] = ' ';
                  break;
            } // switch
         } // if - else
      }
      else
      {
         if ( srcOffset >= 0 )
         {
            if ( '-' != valueString[ srcOffset ] )
            {
               newValue[ targetOffset ] = thisMaskChar;
            }
            else if ( '.' == thisMaskChar )
            {
               newValue[ targetOffset ] = thisMaskChar;
            }
            else if ( ',' == thisMaskChar )
            {
               switch ( rpItems->mask[ maskOffset + 1 ] )
               {
                  case '$' :
                     newValue[ targetOffset ] = '$';
                     maskOffset = 0;
                     break;

                  case 'Z' :
                     newValue[ targetOffset ] = thisMaskChar;
                     break;

                  default:
                     newValue[ targetOffset ] = ' ';
                     break;
               } // switch
            } // if-else
            else
            {
               newValue[ targetOffset ] = ' ';
            }
         } // if
         else
         {
            newValue[ targetOffset ] = ' ';
         }
      } // if-else
      --targetOffset;
      --maskOffset;
   }
   maskOffset = targetOffset = ( maskDecimalPosition + 1 );
   srcOffset = ( valDecimalPosition + 1 );

   while ( maskOffset < maskLen )
   {
      thisMaskChar = rpItems->mask[ maskOffset ];
      if ( -1 != s_maskVals.find( thisMaskChar ))
      {
         if ( srcOffset < valLen )
         {
            newValue[ targetOffset++ ] = valueString[ srcOffset++ ];
         }
         else
         {
            newValue[ targetOffset++ ] = '0';
         }
      }
      else
      {
         newValue[ targetOffset++ ] = thisMaskChar;
      }
      ++maskOffset;
   } // while

   if ( isNegative )
   {
      unsigned long firstNonSpace = newValue.find_first_not_of( ' ' );
      if ( 0 == firstNonSpace )
      {
         newValue = I_("-") + newValue;
      }
      else
      {
         newValue[ firstNonSpace - 1 ] = '-';
      }
   }
   valueString = newValue;
}


void DataElementProperties::_formatInteger(
   DString &valueString,
   const ClientLocale &rpClientLocale,
   const MaskAndOverrides *rpItems
   ) const
{
   stripLeading( valueString, '0' );
   if ( valueString.empty() )
   {
      valueString.assign( rpItems->mask.length() - 1, ' ' );
      valueString.append( 1, '0' );
   }
   else
   {
      I_CHAR thisMaskChar;
      long srcOffset = valueString.length() - 1;
      long maskOffset = rpItems->mask.length() - 1;
      long targetOffset = maskOffset;
      DString newValue( rpItems->mask.length(), ' ' );
      bool done = false;
      for ( unsigned long lc = maskOffset; lc >= 0 && !done; --lc )
      {
         thisMaskChar = rpItems->mask[ maskOffset-- ];
         if ( srcOffset >= 0 )
         {
            if ( -1 != s_maskVals.find( thisMaskChar ))
            {
               newValue[ targetOffset-- ] = valueString[ srcOffset-- ];
            }
            else
            {
               newValue[ targetOffset-- ] = thisMaskChar;
            }
         }
         else
         {
            if ( thisMaskChar == '$' || thisMaskChar == '-' )
            {
               newValue.insert( DString::size_type( 0 ), 1, thisMaskChar );
            }
            done = true;
         }
      }
      valueString = newValue;
   }
}


void DataElementProperties::_formatNewNumber(
   DString &valueString,
   const ClientLocale &clientLocale,
   MaskAndOverrides *rpItems,
   const DString &i18nFormat
   ) const
{
   JavaDecimalFormat *pDisplayFormat = 0;
   try
   {  // Don't attempt to parse a string that's empty (you'll probably get
      // an exception)
      if ( !valueString.stringHasOnly( I_( " " ) ) )
      {
         JavaDecimalFormat *pHostFormat = getNumberHostFormatter();

         if ( i18nFormat.length() )
         {
            pDisplayFormat = JavaNumberFormat::getNumberInstance(
               &clientLocale );
            pDisplayFormat->applyPattern( i18nFormat );
            _setDecimalFormatSymbols( *pDisplayFormat,
               clientLocale.getLocale() );
         }
         else
         {
            pDisplayFormat = _getNumberDisplayFormatter( rpItems,
               clientLocale );
         }

         if ( pDisplayFormat && pHostFormat )
         {
            double dNum;
            int iDecimal;

            if ( -1 != valueString.find( I_('+') ) &&
                 -1 == m_dstrHostMask.find( I_('+') ) )
            {
               strip( valueString, I_('+') );
            }
            // Note that we can only check for "." as a decimal place
            //  because the host format is enUs. If that changes this code
            // will break!
            if ( ( iDecimal = getDecimalPlace() ) &&
                 ( -1 == valueString.pos( I_( '.' ) ) ) )
            {
               // There's a decimal place, but TA2000 host doesn't send it
               // in the data stream.  So, we have to "preformat" the
               // value string and add in the decimal place before we give
               // it to the JavaDecimalFormat object.  Silly, no?

               // Pad the number to the correct length
               DString tempValueString( valueString.c_str() );
               if ( tempValueString.length() < getMaxLength() )
               {
                  tempValueString.padLeft( getMaxLength(), I_( '0' ) );
               }

               // Insert the decimal place
               tempValueString.insert( tempValueString.length() -
                                          iDecimal,
                                       I_( "." ) ) ;
               dNum = pHostFormat->parse( tempValueString );
            }
            else
            {
               dNum = pHostFormat->parse( valueString );
            }
            valueString = pDisplayFormat->format( dNum );
         }
         if ( i18nFormat.length() )
         {  // delete if we created
            delete pDisplayFormat;
         }
      }
   }
   catch ( ConditionException & )
   {
      if ( i18nFormat.length() )
      {  // delete if we created
         delete pDisplayFormat;
      }
      DString msg( I_( "VALUE=" ) );
      msg += valueString;
      msg += I_( ";HOSTMASK=" );
      msg += getHostMask();
      msg += I_( ";DISPMASK=" );
      if ( i18nFormat.length() )
      {
         msg += i18nFormat;
      }
      else
      {
         msg += rpItems->mask;
      }
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_( "DataElementProperties::formatNewNumber" ),
                        DIDBRKR_I18N_MASK_FORMAT_ERROR, msg.c_str() );
   }
}


void DataElementProperties::_formatString(
   DString &valueString,
   const ClientLocale &rpClientLocale,
   const MaskAndOverrides *rpItems
   ) const
{
   I_CHAR maskChar;
   long maskOffset = 0;
   long srcOffset = 0;
   long targetOffset = 0;
   long valLen = valueString.length();
   long maskLen = rpItems->mask.length();
   DString newValue( maskLen, ' ' );

   while ( maskOffset < maskLen )
   {
      maskChar = rpItems->mask[ maskOffset ];
      if ( -1 != s_maskVals.find( maskChar ) )
      {
         if ( srcOffset < valLen )
         {
            newValue[ targetOffset++ ] = valueString[ srcOffset++ ];
         }
         else
         {
            newValue[ targetOffset++ ] = ' ';
         }
      }
      else
      {
         newValue[ targetOffset++ ] = maskChar;
      }
      ++maskOffset;
   }
   valueString = newValue;
}


void DataElementProperties::_unformatDateTime(
   DString &valueString,
   const ClientLocale &clientLocale,
   MaskAndOverrides *rpItems,
   const DString &i18nFormat
   ) const
{
   JavaSimpleDateFormat *pDisplayFormat = NULL;
   try
   {  // Don't attempt to parse a string that's empty (you'll probably get
      // an exception)
      if ( !valueString.stringHasOnly( I_( " " ) ) )
      {
         JavaSimpleDateFormat *pHostFormat = getDateHostFormatter();

         if ( i18nFormat.length() )
         {
            pDisplayFormat = new JavaSimpleDateFormat( i18nFormat,
               *( clientLocale.getJavaLocale() ) );
            pDisplayFormat->setLenient( false );
         }
         else
         {
            pDisplayFormat = _getDateDisplayFormatter( rpItems, clientLocale );
         }

         if ( pHostFormat && pDisplayFormat )
         {
            JavaDate *pDate = pDisplayFormat->parse( valueString );
            if ( pDate )
            {
               pHostFormat->format( *pDate, valueString );
               delete pDate;
            }
         }
         if ( i18nFormat.length() )
         {  // delete if we created
            delete pDisplayFormat;
         }
      }
   }
// should we be catching ... ?
   catch ( ConditionException & )
   {
      if ( i18nFormat.length() )
      {  // delete if we created
         delete pDisplayFormat;
      }
      DString msg( I_( "VALUE=" ) );
      msg += valueString;
      msg += I_( ";HOSTMASK=" );
      msg += getHostMask();
      msg += I_( ";DISPMASK=" );
      if ( i18nFormat.length() )
      {
         msg += i18nFormat;
      }
      else
      {
         msg += rpItems->mask;
      }
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_( "DataElementProperties::_unformatDateTime" ),
                        DIDBRKR_I18N_MASK_FORMAT_ERROR, msg.c_str() );
   }
}


void DataElementProperties::_unformatNewNumber(
   DString &valueString,
   const ClientLocale &clientLocale,
   MaskAndOverrides *rpItems,
   const DString &i18nFormat
   ) const
{
   JavaDecimalFormat *pDisplayFormat = NULL;
   try
   {  // Don't attempt to parse a string that's empty (you'll probably get
      // an exception)
      if ( !valueString.stringHasOnly( I_( " " ) ) )
      {
         JavaDecimalFormat *pHostFormat = getNumberHostFormatter();

         // DT17817 This may not be locale independent.
         // If the value has a '+' and the mask does not have a '+', remove it
         // from the value (the DecimalFormat class has no support for '+')
         if ( valueString.find( '+' ) != -1 )
         {
            bool fStripPlus = false;
            if ( i18nFormat.length() )
            {
               if ( i18nFormat.find( I_( '+' ) ) == -1 )
               {  // Mask doesn't have +
                  fStripPlus = true;
               }
            }
            else
            {
               if ( rpItems->mask.length() )
               {
                  if ( rpItems->mask.find( I_( '+' ) ) == -1 )
                  {  // Mask doesn't have +
                     fStripPlus = true;
                  }
               }
            }

            if ( fStripPlus )
            {
               valueString.stripAll( I_( '+' ) );
            }
         }

         if ( i18nFormat.length() )
         {
            pDisplayFormat = JavaNumberFormat::getNumberInstance(
               &clientLocale );
            pDisplayFormat->applyPattern( i18nFormat );
            _setDecimalFormatSymbols( *pDisplayFormat,
               clientLocale.getLocale() );
         }
         else
         {
            pDisplayFormat = _getNumberDisplayFormatter( rpItems, clientLocale );
         }

         if ( pHostFormat && pDisplayFormat )
         {
            double dNum = pDisplayFormat->parse( valueString );
            valueString = pHostFormat->format( dNum );

            // Note that we can only check for "." as a decimal place because
            // the host format is enUs. If that changes this code will break!
            if ( ( getDecimalPlace() ) )
            {
               // There's a decimal place, but TA2000 host doesn't send it in
               // the data stream.  So, we have to "preformat" the value string
               // and remove the decimal place before we set the "raw" data
               // format.
               valueString.stripAll( I_( '.' ) );
            }
         }

         if ( i18nFormat.length() )
         {
            delete pDisplayFormat;
         }
      }
   }
// Should catch ... ??
   catch ( ConditionException & )
   {
      if ( i18nFormat.length() )
      {
         delete pDisplayFormat;
      }
      DString msg( I_( "VALUE=" ) );
      msg += valueString;
      msg += I_( ";HOSTMASK=" );
      msg += getHostMask();
      msg += I_( ";DISPMASK=" );
      if ( i18nFormat.length() )
      {
         msg += i18nFormat;
      }
      else
      {
         msg += rpItems->mask;
      }
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_( "DataElementProperties::removeMaskFromValue" ),
                        DIDBRKR_I18N_MASK_FORMAT_ERROR, msg.c_str() );
   }
}


void DataElementProperties::_unformatOldTypes(
   DString &valueString,
   const ClientLocale &rpClientLocale,
   const MaskAndOverrides *rpItems
   ) const
{
   long valLength = valueString.length();
   long maskLength = rpItems->mask.length();
   DString::size_type decPos;
// Why + 1 ??  Why filling with anything?
   DString targetValue( maskLength + 1, ' ' );

   if ( getStoredType() == DEP::DECIMAL &&
        ( -1 != rpItems->mask.find( I_( "." ) ) ) )
   {
      DString thisMask( rpItems->mask );
      if ( -1 != thisMask.find_first_not_of( I_("%.") ))
      {
         if ( -1 == thisMask.find( I_(".") ))
         {
            stripTrailing( thisMask );
            thisMask += I_(".");
            maskLength = thisMask.length();
            targetValue += I_(" ");
         }
         if ( -1 == valueString.find( I_(".") ))
         {
            stripTrailing( valueString );
            valueString += I_(".");
            valLength = valueString.length();
         }
         long srcDecPos = valueString.find( I_(".") );
         long maskDecPos = thisMask.find( I_(".") );
         long srcOffset = srcDecPos;
         long maskOffset = maskDecPos;
         bool hasDec = ( srcOffset >= 0 || maskOffset >= 0 );
         long targetOffset = maskOffset;

         if ( hasDec )
         {
            while ( srcOffset >= 0 && maskOffset >= 0 )
            {
               I_CHAR maskedAtOffset = valueString[ srcOffset ];
               if ( isdigit( maskedAtOffset ))
               {
                  targetValue[ targetOffset-- ] = maskedAtOffset;
               }
               else
               {
                  if ( maskedAtOffset != thisMask[ maskOffset ] )
                  {
                     if ( maskedAtOffset != '$' ||
                          maskOffset == 0 ||
                          thisMask[ maskOffset - 1 ] != '$' )
                     {
                        targetValue[ targetOffset-- ] = maskedAtOffset;
                     }
                  }
               }
               --srcOffset;
               --maskOffset;
            }
         }
         srcOffset = srcDecPos + 1;
         maskOffset = targetOffset = ( maskDecPos + 1 );
         if ( hasDec )
         {
            targetValue[ targetOffset++ ] = '.';
         }
         while ( srcOffset < valLength && maskOffset < maskLength
                 && targetOffset < ( maskLength + 1 ))
         {
            I_CHAR maskedAtOffset = valueString[ srcOffset ];
            if ( isdigit( maskedAtOffset ) ||
                 ( maskedAtOffset != thisMask[ maskOffset ] ))
            {
               targetValue[ targetOffset++ ] = maskedAtOffset;
            }
            ++srcOffset;
            ++maskOffset;
         }
      }
      else
      {
         if ( -1 != valueString.find( I_("%") ))
         {
            stripAll( valueString, '%' );
            stripLeading( valueString, ' ' );
            stripLeading( valueString, '0' );
            decPos = valueString.find( I_( "." ) );
            if ( -1 == decPos )
            {
               decPos = valueString.length();
               valueString = valueString + I_(".0");
            }
            if ( decPos < 2 )
            {
               padLeft( valueString,
                        valueString.length() + ( 2 - decPos ), '0' );
            }
            decPos = valueString.find( I_(".") );
            valueString.erase( decPos, 1 );
            valueString.insert( decPos - 2, I_(".") );
            targetValue = valueString;
         }
         else
         {
            targetValue = valueString;
         }
      }
      strip( targetValue );
   }
   else
   {
      long srcOffset = 0;
      long maskOffset = 0;
      long targetOffset = 0;
      while ( srcOffset < valLength && maskOffset < maskLength )
      {
         I_CHAR maskedAtOffset = valueString[ srcOffset ];
         I_CHAR maskChar = rpItems->mask[ maskOffset ];
         if ( ( maskChar == '9' && isdigit( maskedAtOffset ) ) ||
              (( maskChar == 'X' || maskChar == 'A' ||
                 maskChar == 'Z' ) &&
               !isdigit( maskedAtOffset )) ||
              maskedAtOffset != maskChar )
         {
            targetValue[ targetOffset++ ] = maskedAtOffset;
         }
         ++srcOffset;
         ++maskOffset;
      }
      stripLeading( targetValue );
      stripTrailing( targetValue );
   }
   valueString = targetValue;
}


bool DataElementProperties::getAllKeys( DString &keyValues,
                                        bool separateWithEOLs,
                                        const ClientLocale *pClientLocale,
                                        bool usePropertiesOrder )
{
   if ( !hasSubstitutes( pClientLocale ) )
   {
      return false;
   }
   SubsAndOverrides *items;

   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   const DString& locLocale = pLocClientLocale->getLocale();

   {
      SubsAndOverridesMapType::const_iterator iter = findSubs( *pLocClientLocale );

      if ( iter == m_mapSubsItems.end() )
      {
         DString msg( I_("locale=") );
         msg += locLocale;
         msg += I_(";element=");
         msg += _name;
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("DataElementProperties::getAllKeys"),
                           DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
      }
      items = ( *iter ).second;
   }

   keyValues = NULL_STRING;
   if ( usePropertiesOrder )
   {
      SubStringVectorType::const_iterator iter;
      for ( iter = items->substitutionVector.begin();
            iter != items->substitutionVector.end();
            ++iter )
      {
         keyValues += (*iter);
         if ( separateWithEOLs )
         {
            keyValues += '\n';
         }
         else
         {
            keyValues += TERMINATOR_CHAR;
         }
      }
   }
   else
   {
      SubstitutionMap::const_iterator iter;
      SubstitutionMap::const_iterator iterEnd = items->substitutionMap.end();
      for ( iter = items->substitutionMap.begin();
            iter != iterEnd;
            ++iter )
      {
         keyValues += (*iter).first;
         if ( separateWithEOLs )
         {
            keyValues += '\n';
         }
         else
         {
            keyValues += TERMINATOR_CHAR;
         }
      }
   }
   return true;
}


bool DataElementProperties::formatValue( DString &valueString,
                                         bool checkValidity ) const
{
   DString adjustedValue( valueString );
   if ( _formatValue( adjustedValue, checkValidity ) )
   {  // Success
      valueString = adjustedValue;
      return true;
   }
   return false;
}

// Will potentially change valueString even if fail - not sure if we need public
//  exposure here.
bool DataElementProperties::_formatValue( DString &valueString,
                                         bool checkValidity ) const
{
   unsigned long valueLength = valueString.length();
   unsigned long maxLength = getMaxLength();
   switch( getStoredType() )
   {
      case DEP::STRING:
      {
         if ( checkValidity && ( valueLength > maxLength ))
         {
            return false;
         }
         if ( valueLength < maxLength )
         {
            padRight( valueString.getImp(), maxLength, ' ' );
         }
      }
      break;

      case DEP::DECIMAL:
      {
         strip( valueString );
         if ( checkValidity && !isValid( valueString ))
         {
            return false;
         }
         unsigned long actualBeforeDecimal, actualAfterDecimal;
         DString beforeDecimalString, afterDecimalString, finalString;
         bool isNegative = ( -1 != valueString.find( '-' ));
         // Skip any leading spaces
         unsigned long numberStart =
                               valueString.find_first_of( I_("0123456789.") );
         if ( -1 == numberStart )
         {
            numberStart = 0;
         }
         DString actualValue( valueString.substr( numberStart ));
         stripLeading( actualValue, '0' );
         unsigned long actValueLength = actualValue.length();
         unsigned long decimalPosition = actualValue.find( '.' );
         if ( -1 == decimalPosition )
         {
            decimalPosition = 0;
            actualAfterDecimal = 0;
            actualBeforeDecimal = actValueLength;
         }
         else
         {
            actualAfterDecimal = actValueLength - decimalPosition - 1;
            actualBeforeDecimal = actValueLength - actualAfterDecimal - 1;
         }
         unsigned long shouldBeAfterDecimal = getDecimalPlace();
         unsigned long shouldBeBeforeDecimal = maxLength - shouldBeAfterDecimal;
         if ( actualBeforeDecimal > shouldBeBeforeDecimal )
         {
            // Probably don't want to truncate like this...
            beforeDecimalString = actualValue.substr(
                                ( actualBeforeDecimal - shouldBeBeforeDecimal ),
                                shouldBeBeforeDecimal );
         }
         else if ( actualBeforeDecimal < shouldBeBeforeDecimal )
         {
            // Fewer digits before the decimal than max, so pad to the left
            // with 0's.
            beforeDecimalString = actualValue.substr(0, actualBeforeDecimal);
            padLeft( beforeDecimalString, shouldBeBeforeDecimal, '0' );
         }
         else
         {
            // We have exactly the same number of digits before the decimal
            // as we should...
            beforeDecimalString = actualValue.substr(0, actualBeforeDecimal);
         }

         if ( actualAfterDecimal > shouldBeAfterDecimal )
         {
            // We have more digits after the decimal than we should,
            // so we'll either have to round them, or truncate them.
            DString actualAfterDecimalString( valueString.substr(
                                 valueString.length() - actualAfterDecimal ));
            DString shouldBeAfterDecimalString(
                    actualAfterDecimalString.substr( 0, shouldBeAfterDecimal ));
            if ( getRounding() ) // Is rounding enabled for the object?
            {
               int thisValue = 0, carryValue = 0;
               I_CHAR abuff;
               // Get the digits that need to be rounded.
               DString leftOverString(
                       actualAfterDecimalString.substr( shouldBeAfterDecimal ));
               long leftOverLength = leftOverString.length();
               for ( long counter = leftOverLength - 1; counter >= 0;counter-- )
               {
                  // Convert each digit to a number, and add whatever carry
                  // value comes from the previous ( to the right ) digit.
                  abuff = leftOverString[ counter ];
                  thisValue = ( abuff - '0' ) + carryValue;
                  // Set the carry value is this value is > 4
                  if ( thisValue > 4 )
                  {
                     carryValue = 1;
                  }
                  else
                  {
                     carryValue = 0;
                  }
               }
               if ( thisValue > 4 )
               {
                  // The extra digits rounded up, so we need to add 1 to the
                  // digits that should be there.
                  DString newAfterString(
                          addTwoStrings( shouldBeAfterDecimalString, I_("1") ));
                  if ( newAfterString.length() >
                                           shouldBeAfterDecimalString.length() )
                  {
                     // If the length of the newAfterString is more than that of
                     // the shouldBeAfterDecimalString, that means the digits
                     // after the decimal rounded up to more than 1.  So, we
                     // need to add 1 to the digits before the decimal.
                     DString newBDS( addTwoStrings( beforeDecimalString,
                                                    I_("1") ));
                     if ( newBDS.length() <= beforeDecimalString.length() )
                     {
                        beforeDecimalString = newBDS;
                        afterDecimalString = newAfterString.substr( 1 );
                     }
                     else
                     {
                        // If rounding would make the string before the
                        // decimal longer than it should be, don't round.
                        afterDecimalString = shouldBeAfterDecimalString;
                     }
                  }
                  else
                  {
                     // String resulting from the add is the same length as the
                     // original.
                     afterDecimalString = newAfterString;
                  }
               }
               else
               {
                  // The extra digits didn't round up, so just truncate the
                  // string at it's proper length.
                  afterDecimalString = shouldBeAfterDecimalString;
               }
            }
            else
            {
               // We're not rounding, so just truncate the string at it's proper
               // length.
               afterDecimalString = shouldBeAfterDecimalString;
            }
         }
         else if ( 0 == actualAfterDecimal )
         {
            afterDecimalString = DString( shouldBeAfterDecimal, '0');
         }
         else if ( actualAfterDecimal < shouldBeAfterDecimal )
         {
            // There are fewer digits after the decimal than what we're allowed,
            // so pad on the right side with 0's
            afterDecimalString = padRight(
                                      actualValue.substr( decimalPosition + 1 ).getImp(),
                                      shouldBeAfterDecimal, '0' );
         }
         else
         {
            // There are just as many digits after the decimal as there should
            // be, so just grab all digits after the decimalPosition.
            afterDecimalString = actualValue.substr( decimalPosition + 1,
                                                     actualAfterDecimal );
         }
         if ( isNegative )
         {
            finalString = I_("-");
         }
         else
         {
            finalString = I_(" ");
         }
         finalString += beforeDecimalString;
         if ( afterDecimalString.length() != 0L )
         {
            finalString += I_(".");
            finalString += afterDecimalString;
         }
         valueString = finalString;
      }
      break;

      case DEP::INTEGER:
      {
         strip( valueString );
         stripLeading( valueString, '0');
         unsigned long adjLength = valueString.length();
         if ( checkValidity &&
                      ( adjLength > maxLength || !isAllDigits( valueString )))
         {
            return false;
         }
         if ( adjLength < maxLength )
         {
            padLeft( valueString, maxLength, '0');
         }
      }
      break;

      default:
         break;
   } // switch
   return true;
}


const DString &DataElementProperties::getDefaultValue(
   const ClientLocale *pClientLocale
   ) const
{
   FieldAndOverrides *items;
   const ClientLocale *pLocLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   {
      FieldAndOverridesMapType::const_iterator iter;
      iter = findField( *pLocLocale );

      if ( iter == m_mapFieldItems.end() )
      {
         DString msg( I_("locale=") );
         msg += pLocLocale->getLocale();
         msg += I_(";element=");
         msg += _name;
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("DataElementProperties::getDefaultValue"),
                           DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
      }
      items = ( *iter ).second;
   }

   unsigned long maxLength = getMaxLength();
   unsigned long defaultSize = items->defaultValue.size();
   if ( 0 == defaultSize )
   {
      switch( getStoredType() )
      {
         case DEP::STRING:
            // fill with blanks
            items->defaultValue.assign( maxLength, I_(' ') );
            break;

         case DEP::INTEGER:
            items->defaultValue = I_("0");
            formatValue( items->defaultValue, false );
            break;

         case DEP::DECIMAL:
            items->defaultValue = I_(" .0");
            formatValue( items->defaultValue, false );
            break;

         case DEP::I18N_DATE:
         case DEP::I18N_TIME:
         {
            items->defaultValue = I_( " " );
         }
            break;

         case DEP::I18N_INTEGER:
         {
            JavaDecimalFormat *pHostFormat = getNumberHostFormatter();

            if ( pHostFormat )
            {
               items->defaultValue = pHostFormat->format( 0 );
            }
            else
            {
               items->defaultValue = I_( "0" );
            }
         }
            break;

         case DEP::I18N_DECIMAL:
         case DEP::I18N_PERCENT:
         case DEP::I18N_CURRENCY:
         {
            JavaDecimalFormat *pHostFormat = getNumberHostFormatter();

            if ( pHostFormat )
            {
               items->defaultValue = pHostFormat->format( 0.0 );
            }
            else
            {
               items->defaultValue = I_( "0.0" );
            }
         }
            break;

         default:
               break;
      }
   }
   else if ( defaultSize > maxLength )
   {
// This code is compensating for bin/mdb files containing default values longer than max value.
// Should be corrected in database.
      if ( maxLength > 0 )
      {
         items->defaultValue.erase( maxLength, defaultSize - maxLength );
      }
      else
      {  // temp to catch
         items->defaultValue = NULL_STRING;
      }
   }
   return items->defaultValue;
}



bool DataElementProperties::getAllSubstituteValues(
   DString &subValues,
   const ClientLocale *pClientLocale,
   bool usePropertiesOrder )
{
   if ( !hasSubstitutes( pClientLocale ) )
   {
      return false;
   }

   SubsAndOverrides *items;
   const ClientLocale *pLocLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   {
      SubsAndOverridesMapType::const_iterator iter = findSubs( *pLocLocale );
      if ( iter == m_mapSubsItems.end() )
      {
         DString msg( I_("locale=") );
         msg += pLocLocale->getLocale();
         msg += I_(";element=");
         msg += _name;
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("DataElementProperties::getAllSubstituteValues"),
                           DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
      }
      items = ( *iter ).second;
   }

   subValues = NULL_STRING;
   if ( usePropertiesOrder )
   {
      SubstitutionMap::const_iterator mapIter;
      SubStringVectorType::const_iterator iter;
      for ( iter = items->substitutionVector.begin();
            iter != items->substitutionVector.end();
            ++iter )
      {
         mapIter = items->substitutionMap.find( (*iter) );
         subValues += (*mapIter).first;
         subValues += SEPARATOR_CHAR;
         subValues += (*mapIter).second;
         subValues += TERMINATOR_CHAR;
      }
   }
   else
   {
      SubstitutionMap::const_iterator iter;
      SubstitutionMap::const_iterator iterEnd = items->substitutionMap.end();
      for ( iter = items->substitutionMap.begin();
            iter != iterEnd;
            ++iter )
      {
         subValues += (*iter).first;
         subValues += SEPARATOR_CHAR;
         subValues += (*iter).second;
         subValues += TERMINATOR_CHAR;
      }
   }
   return true;
}


DString DataElementProperties::getKeyFromValue(
   const DString &value,
   const ClientLocale *pClientLocale ) const
{
   SubsAndOverrides *items;
   const ClientLocale* pLocLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   {
      SubsAndOverridesMapType::const_iterator itemsIter = findSubs( *pLocLocale );

      if ( itemsIter == m_mapSubsItems.end() )
      {
         DString msg( I_("locale=") );
         msg += pLocLocale->getLocale();
         msg += I_(";element=");
         msg += _name;
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("DataElementProperties::getKeyFromValue"),
                           DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
      }
      items = ( *itemsIter ).second;
   }

   SubstitutionMap::const_iterator iter, iterEnd = items->substitutionMap.end();
   for ( iter = items->substitutionMap.begin();
         iter != iterEnd;
         ++iter )
   {
      if ( PropertyRepository::getInstance()->ignoreCaseOnSubstitutes() )
      {
         if ( 0 == (*iter).second.stricmp( value ) )
         {
            return (*iter).first.c_str();
         }
      }
      else
      {
         if ( (*iter).second == value )
         {
            return (*iter).first.c_str();
         }
      }
   }
   return value.c_str();
}


JavaSimpleDateFormat * DataElementProperties::getDateHostFormatter() const
{
   if ( pDateHostFormatter )
   {
      return pDateHostFormatter;
   }

   switch ( getStoredType() )
   {
      case DEP::I18N_DATE:
      case DEP::I18N_TIME:
      {
         Guard crit( &m_itemsLock );

         if ( pDateHostFormatter )
         {
            return pDateHostFormatter;
         }

         DString dstrMask( getHostMask() );

         if ( dstrMask.length() > 0 )
         {
            JavaLocale *pLocaleUS = JavaLocale::getUSInstance();
            JavaSimpleDateFormat *pTemp = new JavaSimpleDateFormat( dstrMask,
                                                                    *pLocaleUS,
                                                                    true );
            pTemp->setLenient( false );
            pDateHostFormatter = pTemp;
         }
      }
      break;
   }

   return pDateHostFormatter;
}


JavaSimpleDateFormat * DataElementProperties::getDateDisplayFormatter(
   const ClientLocale &clientLocale
   ) const
{
   if ( getStoredType() != I18N_DATE && getStoredType() != I18N_TIME )
   {  // not valid for this type
      return NULL;
   }

   MaskAndOverrides *rpItems = getMaskItems( clientLocale );
   if ( !rpItems )
   {
      return NULL;
   }

   return _getDateDisplayFormatter( rpItems, clientLocale );
}


JavaSimpleDateFormat *DataElementProperties::_getDateDisplayFormatter(
   MaskAndOverrides *rpItems,
   const ClientLocale &clientLocale
   ) const
{
   if ( rpItems->pDateDisplayFormatter )
   {
      return rpItems->pDateDisplayFormatter;
   }

   Guard crit( &m_itemsLock );

   if ( rpItems->pDateDisplayFormatter )
   {
      return rpItems->pDateDisplayFormatter;
   }

   if ( rpItems->mask.length() > 0 )
   {
      JavaSimpleDateFormat *pTemp = new JavaSimpleDateFormat(
         rpItems->mask, clientLocale, true );
      pTemp->setLenient( false );
      rpItems->pDateDisplayFormatter = pTemp;
   }

   return rpItems->pDateDisplayFormatter;
}


JavaDecimalFormat * DataElementProperties::getNumberHostFormatter() const
{
   if ( pNumberHostFormatter )
   {
      return pNumberHostFormatter;
   }

   switch ( getStoredType() )
   {
      case DEP::I18N_DECIMAL:
      case DEP::I18N_INTEGER:
      case DEP::I18N_PERCENT:
      case DEP::I18N_CURRENCY:
      {
         Guard crit( &m_itemsLock );

         if ( pNumberHostFormatter )
         {
            return pNumberHostFormatter;
         }

         DString dstrMask( getHostMask() );

         if ( dstrMask.length() > 0 )
         {
            JavaLocale *pLocaleUS = JavaLocale::getUSInstance();

            JavaDecimalFormat *pTempHostFormatter =
               JavaNumberFormat::getNumberInstance( pLocaleUS, true );

            if ( pTempHostFormatter )
            {
               pTempHostFormatter->applyPattern( dstrMask );
               _setDecimalFormatSymbols( *pTempHostFormatter, pLocaleUS->getLCV() );
               pNumberHostFormatter = pTempHostFormatter;
            }
         }
      }
      break;
   }

   return pNumberHostFormatter;
}


JavaDecimalFormat * DataElementProperties::getNumberDisplayFormatter(
   const ClientLocale &clientLocale
   ) const
{
   if ( getStoredType() != I18N_DECIMAL && getStoredType() != I18N_INTEGER &&
      getStoredType() != I18N_PERCENT && getStoredType() != I18N_CURRENCY )
   {  // Not valid for this type
      return NULL;
   }

   MaskAndOverrides *rpItems = getMaskItems( clientLocale );
   if ( !rpItems )
   {
      return NULL;
   }

   return _getNumberDisplayFormatter( rpItems, clientLocale );
}


JavaDecimalFormat *DataElementProperties::_getNumberDisplayFormatter(
   MaskAndOverrides *rpItems,
   const ClientLocale &clientLocale
   ) const
{
   if ( rpItems->pNumberDisplayFormatter )
   {
      return rpItems->pNumberDisplayFormatter;
   }

   Guard crit( &m_itemsLock );

   if ( rpItems->pNumberDisplayFormatter )
   {
      return rpItems->pNumberDisplayFormatter;
   }

   if ( rpItems->mask.length() > 0 )
   {
      JavaDecimalFormat *pTempDisplayFormatter =
         JavaNumberFormat::getNumberInstance( &clientLocale, true );

      if ( pTempDisplayFormatter )
      {
         pTempDisplayFormatter->applyPattern( rpItems->mask );
         _setDecimalFormatSymbols( *pTempDisplayFormatter,
                                   clientLocale.getLocale() );
         rpItems->pNumberDisplayFormatter = pTempDisplayFormatter;
      }
   }

   return rpItems->pNumberDisplayFormatter;
}


bool DataElementProperties::getDefaultValueIsNull(
   const ClientLocale *pClientLocale
   ) const
{
   FieldAndOverrides *items = getFieldItems( pClientLocale );
   return items->fDefaultValueIsNull;
}


const DString &DataElementProperties::getFieldLabel(
   const ClientLocale *rpClientLocale
   ) const
{
   FieldAndOverrides *items = getFieldItems( rpClientLocale );
   return items->fieldLabel;
}


I_CHAR DataElementProperties::getFillCharacter(
   const ClientLocale *pClientLocale
   ) const
{
   FieldAndOverrides *items = getFieldItems( pClientLocale );
   return items->fillCharacter;
}


DString &DataElementProperties::getFormattedValue(
   DString &strOut,
   unsigned long formatFlags,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   ) const
{
   if ( formatFlags == 0L )
   {
      if ( getStoredType() == DEP::DECIMAL )
      {
         stripLeading( strOut );
      }
   }
   else
   {
      if ( ( formatFlags & USE_SUBSTITUTES ) &&
           hasSubstitutes( rpClientLocale ) )
      {
         strOut = getSubstituteValue( strOut, rpClientLocale );
      }
      else if ( ( formatFlags & USE_MASK ) &&
                ( hasMask( rpClientLocale ) || i18nFormat.length()  ) )
      {
         formatUsingMask( strOut, rpClientLocale, i18nFormat );
      }

      if ( getStoredType() == DEP::STRING )
      {
         if ( formatFlags & STRIP_LEADING )
         {
            stripLeading( strOut );
         }
         if ( formatFlags & STRIP_TRAILING )
         {
            stripTrailing( strOut );
         }
      }
   }
   return strOut;
}


DataElementProperties::JUSTIFICATION DataElementProperties::getJustification(
   const ClientLocale *pClientLocale
   ) const
{
   FieldAndOverrides *items = getFieldItems( pClientLocale );
   return items->justification;
}


DString DataElementProperties::getMask( const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   MaskAndOverrides *pItems = getMaskItems( *pLocClientLocale );

   if ( pItems == NULL )
   {  // no mask available
      return EMPTY_STRING;
   }

   return pItems->mask;
}


DString DataElementProperties::getHostMask() const
{
   {
      Guard crit( &m_itemsLock );
      if ( m_dstrHostMask.length() )
      {
         return m_dstrHostMask;
      }
   }

   Guard crit( &m_itemsLock );
   if ( m_dstrHostMask.length() )
   {
      return m_dstrHostMask;
   }

   getCfgHostMask( getStoredType(), m_dstrHostMask );

   return m_dstrHostMask;
}


DString DataElementProperties::getSubstituteValue(
   const DString &subValue,
   const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pLocLocale =
       pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   const DString &locLocale = pLocLocale->getLocale();

   SubsAndOverrides *items = getSubsItems( pLocLocale );
   if ( items == NULL )
   {
      return EMPTY_STRING;
   }

   DString locSubValue( subValue );

   stripTrailing( locSubValue );

   SubstitutionMap::const_iterator iter =
                                     items->substitutionMap.find( locSubValue );
   if ( iter != items->substitutionMap.end() )
   {
      return (*iter).second.c_str();
   }
   else if ( GetConfigValueAsString( I_( "DataBroker" ),
                                     I_( "DBOptions" ),
                                     I_( "IgnoreCaseOnSubKeys" ) ).length() > 0 )
   {
      // Case insensitive searching
      SubstitutionMap::const_iterator iter = items->substitutionMap.begin();

      while ( items->substitutionMap.end() != iter )
      {
         if ( 0 == locSubValue.stricmp( ( *iter ).first ) )
         {
            return ( *iter ).second.c_str();
         }

         ++iter;
      }

      return subValue.c_str();
   }
   else
   {
      return subValue.c_str();
   }
}


DString &DataElementProperties::getValueFromBuffer(
   DString &strOut,
   const unsigned char *rpDataBuffer,
   unsigned long formatFlags,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   ) const
{
   strOut.assign( (I_CHAR *)rpDataBuffer, getMaxLength() );
   mapToFormattedValue( strOut );

   return getFormattedValue( strOut, formatFlags, rpClientLocale, i18nFormat );
}


void DataElementProperties::getValueFromBuffer(
   unsigned char *binBuff,
   const unsigned char *rpDataBuffer,
   unsigned long buffLength,
   unsigned long &returnedLength
   ) const
{
   unsigned long copyLength = min( buffLength, getMaxLength() );
   memcpy( binBuff, rpDataBuffer, copyLength );
   returnedLength = copyLength;
}


bool DataElementProperties::setValueInBuffer(
   const DString &valueIn,
   unsigned char *rpDataBuffer,
   const ClientLocale *rpClientLocale,
   bool displayFormat,
   const DString &i18nFormat
   ) const
{
// NOTE:  When going direct to buffer, we always check validity
   DString strOut( valueIn );

   if ( hasSubstitutes( rpClientLocale ) )
   {
      if ( !getForceMatching() ||
           ( getForceMatching() &&
             ( isValidKey( strOut, rpClientLocale ) ||
               isValidValue( strOut, rpClientLocale ))))
      {
         const DString &key = getKeyFromValue( strOut, rpClientLocale );
         if ( key != strOut )
         {
            strOut = key;
         }
         else
         {
            if ( !_formatValue( strOut, true ) )
            {
               return false;
            }
         }
      }
      else
      {
         return false;
      }
   }
   else
   {
      if ( hasMask( rpClientLocale ) || i18nFormat.length() )
      {
         DString unMaskedValue( strOut );

         if ( displayFormat || i18nFormat.length() )
         {
            try
            {
               removeMaskFromValue( unMaskedValue, rpClientLocale, i18nFormat );
            }
            catch ( ConditionException &ce )
            {
               // Allow locale errors to pass (do this so we don't change
               // the behavior of the existing interface).
               if ( DIDBRKR_LOCALE_NOT_FOUND == ce.getCode() &&
                    DIDBRKR_COMPONENT_NAME == ce.getComponentName() )
               {
                  throw;
               }
               else
               {
                  return false;
               }
            }
         }
         else if ( !displayFormat )
         {
            // Make sure it's parseable by the host formatter
            try
            {
               formatUsingMask( strOut,
                  &ClientLocale::getDefaultInfraClientLocale(),
                  NULL_STRING );
            }
            catch ( ConditionException &ce )
            {
               // Allow locale errors to pass (do this so we don't change
               // the behavior of the existing interface).
               if ( DIDBRKR_LOCALE_NOT_FOUND == ce.getCode() &&
                    DIDBRKR_COMPONENT_NAME == ce.getComponentName() )
               {
                  throw;
               }
               else
               {
                  return false;
               }
            }
         }

         if ( _formatValue( unMaskedValue, true ))
         {
            strOut = unMaskedValue;
         }
         else
         {
            return false;
         }
      }
      else
      {
         if ( !_formatValue( strOut, true ) )
         {
            return false;
         }
      }
   }
   // Get back in host format and copy into buffer
   mapToNativeValue( strOut );
   int copyLength = strOut.size();
   if ( copyLength != getMaxLength() )
   {  // double check size
// Should log this somehow.
      int i = getMaxLength();
      if ( copyLength > i )
      {  // Use shorter length - but we have a problem
         copyLength = i;
      }
   }
   memcpy( rpDataBuffer, strOut.c_str(), copyLength * sizeof( I_CHAR ) );
   return true;
}


bool DataElementProperties::setValueInBuffer(
   unsigned char *binBuff,
   unsigned char *rpDataBuffer,
   unsigned long buffLength,
   unsigned long &returnedLength
   ) const
{
   unsigned long copyLength = min( buffLength, getMaxLength() );
   memcpy( rpDataBuffer, binBuff, copyLength );
   returnedLength = copyLength;
   return true;
}


bool DataElementProperties::setValueInBufferFromHost(
   DString &valueIn,
   unsigned char *rpDataBuffer
   ) const
{
   if ( !_formatValue( valueIn, false ) )
   {
      return false;
   }
   // Get back in host format and copy into buffer
   mapToNativeValue( valueIn );
   int copyLength = valueIn.size();
   if ( copyLength != getMaxLength() )
   {  // double check size
// Should log this somehow.
      int i = getMaxLength();
      if ( copyLength > i )
      {  // Use shorter length - but we have a problem
         copyLength = i;
      }
   }
   memcpy( rpDataBuffer, valueIn.c_str(), copyLength * sizeof( I_CHAR ) );
   return true;
}


void DataElementProperties::unauthorizedSetValueInBuffer(
   const DString &valueIn,
   unsigned char *rpDataBuffer
   ) const
{
// NOTE:  This method stuffs directly into buffer without any checking
   unsigned long copyLength = min( valueIn.size(), getMaxLength() );
   memcpy( rpDataBuffer, valueIn.c_str(), copyLength * sizeof( I_CHAR ) );
}


bool DataElementProperties::hasFieldLocale( const ClientLocale &clientLocale,
                                            bool checkRepository )
{
   FieldAndOverridesMapType::const_iterator itemsIter = findField( clientLocale );

   if ( itemsIter == m_mapFieldItems.end() )
   {
      return false;
   }
   return true;
}


bool DataElementProperties::addBaseLocale( const ClientLocale &clientLocale,
                                           unsigned long locFieldMinLength,
                                           bool fAllowNull )
{
   ClientLocale cloc( clientLocale );
   // All of the BaseAndMarketItems are locale independent, so we use
   // enUS for the locale
   cloc.setLocale( I_( "enUS" ) );

   BaseAndMarketItems *pBamItems = new BaseAndMarketItems();
   pBamItems->minLength = locFieldMinLength;
   pBamItems->fAllowNull = fAllowNull;
   MultiKeyPointerMapElement< BaseAndMarketItems >
      mkpElement( pBamItems );
   m_mapBaseAndMarketItems[ cloc ] = mkpElement;
   m_mapBaseAndMarketItems[ cloc ].setDeleteElementOnDestruct( true );

   return true;
}


bool DataElementProperties::addFieldLocale( const ClientLocale &clientLocale,
                                            I_CHAR locFillChar,
                                            enum JUSTIFICATION locJust,
                                            const DString &locDefaultValue,
                                            const DString &locFieldLabel,
                                            bool fDefaultValueIsNull )
{

   FieldAndOverrides *pFieldItems = new FieldAndOverrides();
   pFieldItems->defaultValue = locDefaultValue;
   pFieldItems->fieldLabel = locFieldLabel;
   pFieldItems->fillCharacter = locFillChar;
   pFieldItems->justification = locJust;
   pFieldItems->fDefaultValueIsNull = fDefaultValueIsNull;
   FieldAndOverridesMapType::iterator iterF =
      m_mapFieldItems.insert( std::pair< ClientLocale, FieldAndOverrides * >( clientLocale, pFieldItems ) );

   return true;
}


bool DataElementProperties::addFieldLocale( const ClientLocale &clientLocale,
                                            I_CHAR locFillChar,
                                            I_CHAR locJustChar,
                                            const DString &locDefaultValue,
                                            const DString &locFieldLabel,
                                            bool fDefaultValueIsNull )
{
   return ( addFieldLocale( clientLocale,
                            locFillChar,
                            getJustificationFromChar( locJustChar ),
                            locDefaultValue,
                            locFieldLabel,
                            fDefaultValueIsNull ) );
}


bool DataElementProperties::addMaskLocale( const ClientLocale &clientLocale,
                                           const DString &locMask )
{
   MaskAndOverrides *pMaskItems = new MaskAndOverrides();
   pMaskItems->mask = locMask;
   MaskAndOverridesMapType::iterator iterM =
      m_mapMaskItems.insert( std::pair< ClientLocale, MaskAndOverrides * >( clientLocale, pMaskItems ) );

   if ( pMaskItems->mask.length() == 0 )
   {
      DString dstrMask;
      if ( getCfgDisplayMask( getStoredType(), clientLocale, dstrMask ) )
      {
         pMaskItems->mask = dstrMask;
      }
   }

   if ( pMaskItems->mask.length() != 0 )
   {
      m_hasMasks = true;
   }
   return true;
}


bool DataElementProperties::addSubsLocale( const ClientLocale &clientLocale,
                                           const DString &locSubString )
{
   if ( locSubString != NULL_STRING )
   {
      m_hasSubstitutes = true;
   }

   SubsAndOverrides *pSubsItems = new SubsAndOverrides();

   fillSubstitutionMapFromString( locSubString, pSubsItems->substitutionMap,
                                  pSubsItems->substitutionVector );

   SubsAndOverridesMapType::iterator iterS =
      m_mapSubsItems.insert( std::pair< ClientLocale, SubsAndOverrides * >( clientLocale, pSubsItems ) );

   return true;
}


unsigned long DataElementProperties::getMinLength( const ClientLocale& cloc ) const
{
   const BaseAndMarketItems *pBAM = _getBAMItems( cloc );
   return pBAM->minLength;
}


bool DataElementProperties::getAllowNull( const ClientLocale& cloc ) const
{
   const BaseAndMarketItems *pBAM = _getBAMItems( cloc );
   return pBAM->fAllowNull;
}


bool DataElementProperties::hasMask( const ClientLocale *pClientLocale ) const
{
   if ( !m_hasMasks )
   {  // No locale, client, market combination has a mask
      return false;
   }
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   MaskAndOverrides *pItems = getMaskItems( *pLocClientLocale );

   if ( pItems == NULL )
   {
      return false;
   }

   return ( pItems->mask.length() > 0 );
}


bool DataElementProperties::hasHostMask()
{
   DString mask;
   try
   {
      mask = getHostMask();
   }
   catch( ConditionException &ce )
   {
      if ( ce.getCode() == DIDBRKR_LOCALE_NOT_FOUND )
      {
         return false;
      }
      else
      {
         throw;
      }
   }
   if ( mask.length() > 0 )
   {
      return true;
   }
   return false;
}


bool DataElementProperties::hasSubstitutes( const ClientLocale *pClientLocale ) const
{
   if ( !m_hasSubstitutes )
   {  // no locale, client, market combination has substitutes
      return false;
   }
   SubsAndOverrides *items;
   items = getSubsItems( pClientLocale );
   if ( items && items->substitutionMap.size() > 0 )
   {
      return true;
   }
   return false;
}


bool DataElementProperties::isValidKey( const DString &key,
                                        const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pLocLocale =
       pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();
   const DString &locLocale = pLocLocale->getLocale();

   SubsAndOverrides *items = getSubsItems( pLocLocale );
   if ( items == NULL )
   {
      return false;
   }

   if ( items->substitutionMap.end() != items->substitutionMap.find( key ) )
   {
      return true;
   }
   else if ( GetConfigValueAsString( I_( "DataBroker" ),
                                     I_( "DBOptions" ),
                                     I_( "IgnoreCaseOnSubKeys" ) ).length() > 0 )
   {
      // Case insensitive searching
      SubstitutionMap::const_iterator iter = items->substitutionMap.begin();

      while ( items->substitutionMap.end() != iter )
      {
         if ( 0 == key.stricmp( ( *iter ).first ) )
         {
            return true;
         }

         ++iter;
      }

      return false;
   }
   else
   {
      return false;
   }
}


bool DataElementProperties::isValidValue( const DString &value,
                                          const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pLocLocale =
       pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   const DString &locLocale = pLocLocale->getLocale();

   SubsAndOverrides *items = getSubsItems( pLocLocale );
   if ( items == NULL )
   {
      return false;
   }

   SubstitutionMap::const_iterator iter, iterEnd = items->substitutionMap.end();
   for ( iter = items->substitutionMap.begin();
         iter != iterEnd;
         ++iter )
   {
      if ( (*iter).second == value )
      {
         return true;
      }
   }
   return false;
}


bool DataElementProperties::isValid( const DString &valueString,
                                     const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   // Check for length compliance...
   const BaseAndMarketItems *pBamItems = _getBAMItems( *pLocClientLocale );
   if ( !pBamItems ||
        valueString.length() < pBamItems->minLength )
   {
      return false;
   }

   // Check for type-specific compliance...
   switch ( _items.storedType )
   {
      case DECIMAL:
         {
            if ( ( valueString.length() > _items.maxLength + 2 ) &&
                                                                 !getRounding())
            {
               return false;
            }

            if ( ( getDecimalPlace() > 0L ) && !isDecimal( valueString ) )
            {
               return false;
            }

            // Check that the decimal place is in the proper position...
            DString::size_type leadingSpaces =
                                   valueString.find_first_of(I_("0123456789."));
            if ( -1 == leadingSpaces )
            {
               leadingSpaces = 0;
            }
            DString actualValueString( valueString.substr( leadingSpaces ));
            stripLeading( actualValueString, '0' );
            DString::size_type vsBeforeDecimal =
               actualValueString.find( '.' );
            DString::size_type actualLength;
            if ( -1 == vsBeforeDecimal )
            {
               actualLength = actualValueString.length();
               vsBeforeDecimal = actualLength;
            }
            else
            {
               actualLength = actualValueString.length() - 1;
            }
            DString::size_type vsAfterDecimal = actualLength - vsBeforeDecimal;
            DString::size_type fmtAfterDecimal = _items.decimalPlace;
            DString::size_type fmtBeforeDecimal =
                                             _items.maxLength - fmtAfterDecimal;
            if ( vsBeforeDecimal > fmtBeforeDecimal ||
                         ( ( vsAfterDecimal > fmtAfterDecimal ) &&
                           !getRounding() ))
            {
               return false;
            }
            return true;
         }

      case INTEGER:
         {
            DString newValueString( valueString );
            stripLeading( newValueString, '0' );
            if ( newValueString.length() > _items.maxLength )
            {
               return false;
            }
            return isAllDigits( newValueString );
         }

      case STRING:
         if ( valueString.length() > _items.maxLength )
         {
            return false;
         }
         break;

      case I18N_DATE:
      case I18N_TIME:
      case I18N_DECIMAL:
      case I18N_INTEGER:
      case I18N_PERCENT:
      case I18N_CURRENCY:
         return _isI18NValid( valueString, *pLocClientLocale );

      default:
         break;
   }

   return true;
}


bool DataElementProperties::isValidForHost( const DString &valueString ) const
{
   // Check for type-specific compliance...
   switch ( _items.storedType )
   {
   case DECIMAL:
   case INTEGER:
   case STRING:
      return isValid( valueString );

   case I18N_DATE:
   case I18N_TIME:
   case I18N_DECIMAL:
   case I18N_INTEGER:
   case I18N_PERCENT:
   case I18N_CURRENCY:
      return _isI18NValidForHost( valueString );

   default:
      break;
   }

   return true;
}

DString &DataElementProperties::removeMaskFromValue(
   DString &maskedValue,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   ) const
{
   const ClientLocale *rpLocClientLocale =
      rpClientLocale ? rpClientLocale : &ClientLocale::getDefaultClientLocale();
   MaskAndOverrides *items = NULL;
   ELEMENTTYPE eType = getStoredType();
   bool bMaskToRemove = false;

   if ( maskedValue == NULL_STRING || eType == BOOLEAN || eType == NO_TYPE ||
      eType == BINARY )
   {  // No mask to remove
      return maskedValue;
   }

   if ( !i18nFormat.length() )
   {
      MaskAndOverridesMapType::const_iterator iter = findMask( *rpLocClientLocale );
      if ( iter == m_mapMaskItems.end() )
      {
         DString msg( I_("locale=") );
         msg += rpLocClientLocale->getLocale();
         msg += I_(";element=");
         msg += _name;
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("DataElementProperties::removeMaskFromValue"),
                           DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
      }
      items = ( *iter ).second;
      if ( items->mask.length() > 0 )
      {  // We have mask to remove
         bMaskToRemove = true;
      }
   }
   else
   {  // User passed in mask to remove for new type
      bMaskToRemove = true;
   }

   if ( bMaskToRemove )
   {
      switch( eType )
      {
         case I18N_DATE:
         case I18N_TIME:
            _unformatDateTime( maskedValue, *rpLocClientLocale, items,
               i18nFormat );
            break;

         case I18N_DECIMAL:
         case I18N_INTEGER:
         case I18N_PERCENT:
         case I18N_CURRENCY:
            _unformatNewNumber( maskedValue, *rpLocClientLocale, items,
               i18nFormat );
            break;

         case STRING:
         case DECIMAL:
         case INTEGER:
            if ( items )
            {  // if user passed in i18nFormat with this type,
               //  formatting is ignored.  (Would not fall into this code.)
               _unformatOldTypes( maskedValue, *rpLocClientLocale, items );
            }
            break;

         default:
            // Types BINARY, BOOLEAN, and NO_TYPE, do not use masks.
            break;
      };
   }
   return maskedValue;
}


void DataElementProperties::setForceMatching( bool forceMatching )
{
   _items.forceMatching = forceMatching;
}


// Note: this method assumes the nativeValue is correct, and doesn't need a
// validity check...
void DataElementProperties::mapToFormattedValue( DString &nativeValue ) const
{
   switch ( getStoredType() )
   {
      case DEP::DECIMAL:
      {
         // Attempt to fix any problems with the native value
         strip( nativeValue );
         long maxLen = getMaxLength();
         if ( nativeValue.length() < (unsigned long)maxLen )
         {
            padLeft( nativeValue, maxLen, '0' );
         }
         // Detect the decimal sign...
         long lastPos = nativeValue.length() - 1;
         I_UCHAR endChar = nativeValue[ lastPos ];
         I_UCHAR signChar = pTable[ endChar ];
         signChar &=  0xf0;
         bool fIsNegative = ((signChar == 0xd0 ) || ( signChar == 0xe0 ));

         // Convert the last character to ASCII...
         nativeValue[ lastPos ] = ( pTable[ endChar ] & 0x0f ) + '0';

         // Insert the decimal sign...
         if ( fIsNegative )
         {
            nativeValue.getImp().insert( nativeValue.getImp().begin(), '-' );
         }
         else
         {
            nativeValue.getImp().insert( nativeValue.getImp().begin(), ' ' );
         }

         // Insert the decimal point...
         if ( getDecimalPlace() > 0L )
         {
            nativeValue.getImp().insert(nativeValue.getImp().end() - getDecimalPlace(), '.' );
         }
      }
      break;

      case DEP::INTEGER:
      {
         // Attempt to fix any problems with the native value
         strip( nativeValue );
         long maxLen = getMaxLength();
         if ( nativeValue.length() < (unsigned long)maxLen )
         {
            padLeft( nativeValue, maxLen, '0' );
         }
      }
      break;

      case I18N_DATE:
      case I18N_TIME:
      case I18N_DECIMAL:
      case I18N_INTEGER:
      case I18N_PERCENT:
      case I18N_CURRENCY:
         nativeValue.stripTrailing();
         break;

      case DEP::STRING:
      default:
         break;
   }
}


// Note: this method currently assumes the formattedValue is correct, and
// doesn't need a validity check.  In addition, a decimal point and sign is
// assumed to exist...
void DataElementProperties::mapToNativeValue( DString &formattedValue ) const
{
   switch ( getStoredType() )
   {
      case DEP::DECIMAL:
      {
         // Remove the decimal point...
         if ( getDecimalPlace() > 0L )
         {
            formattedValue.getImp().erase( formattedValue.getImp().end() - getDecimalPlace() - 1);
         }

         // Detect the decimal sign and remove it...
         if ( '-' == formattedValue[0] )
         {
            unsigned long theEnd = formattedValue.length() - 1;
            I_UCHAR endChar = formattedValue[ theEnd ];
            I_UCHAR theChar = pTable[ endChar ] - 0x20;
            formattedValue[ theEnd ] = pTable[ theChar + 256 ];
         }
         formattedValue.getImp().erase( formattedValue.getImp().begin() );
      }
      break;

      case I18N_DATE:
      case I18N_TIME:
      case I18N_DECIMAL:
      case I18N_INTEGER:
      case I18N_PERCENT:
      case I18N_CURRENCY:
         formattedValue.padRight( getMaxLength(), ' ');
         break;

      case DEP::INTEGER:
      case DEP::STRING:
      default:
         break;
   }
}


//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
//              Private Methods
//******************************************************************************

bool DataElementProperties::_isI18NValid(
   const DString &valueString,
   const ClientLocale &rpClientLocale
   ) const
{
   // Check for type-specific compliance...
   switch ( _items.storedType )
   {
   case I18N_DATE:
   case I18N_TIME:
      {
         try
         {
            JavaSimpleDateFormat *pDisplayFormat =
               getDateDisplayFormatter( rpClientLocale );
            if ( pDisplayFormat )
            {
               JavaDate *pDate = pDisplayFormat->parse( valueString );
               if ( pDate )
               {
                  delete pDate;
                  return true;
               }
            }
            return false;
         }
         catch( ... )
         {
            return false;
         }
      }
      break;

   case DEP::I18N_DECIMAL:
   case DEP::I18N_INTEGER:
   case DEP::I18N_PERCENT:
   case DEP::I18N_CURRENCY:
      {
         try
         {
            JavaDecimalFormat *pDisplayFormat =
                getNumberDisplayFormatter( rpClientLocale );

            if ( pDisplayFormat )
            {
               pDisplayFormat->parse( valueString );
               return true;
            }
            // If no formatter, it is considered invalid??
            return false;
         }
         catch ( ... )
         {
            return false;
         }
      }
      break;

   default:
      break;
   }
   return false;
}


bool DataElementProperties::_isI18NValidForHost(
   const DString &valueString
   ) const
{
   // Check for length compliance...
   const BaseAndMarketItems *pBamItems =
      _getBAMItems( ClientLocale::getDefaultClientLocale() );
   if ( valueString.length() < pBamItems->minLength )
   {
      return false;
   }

   // Check for type-specific compliance...
   switch ( _items.storedType )
   {
   case I18N_DATE:
   case I18N_TIME:
      {
         try
         {
            JavaSimpleDateFormat *pHostFormat = getDateHostFormatter();
            if ( pHostFormat )
            {
               JavaDate *pDate = pHostFormat->parse( valueString );
               if ( pDate )
               {
                  delete pDate;
                  return true;
               }
            }
            return false;
         }
         catch( ... )
         {
            return false;
         }
      }
      break;

   case DEP::I18N_DECIMAL:
   case DEP::I18N_INTEGER:
   case DEP::I18N_PERCENT:
   case DEP::I18N_CURRENCY:
      {
         try
         {
            JavaDecimalFormat *pHostFormat = getNumberHostFormatter();

            if ( pHostFormat )
            {
               pHostFormat->parse( valueString );
               return true;
            }
            return false;
         }
         catch ( ... )
         {
            return false;
         }
      }
      break;

   default:
      break;
   }
   return false;
}


i_istream &operator>> ( i_istream &stream, DEP &properties )
{
   return stream;
}


i_ostream &operator<< ( i_ostream &stream, const DEP &properties )
{
   return stream;
}


bool DataElementProperties::getCfgHostMask( ELEMENTTYPE type, DString &mask ) const
{
   mask = NULL_STRING;

   if ( _cfgHostMasks )
   {
      DString dstrType;

      PropertyRepository *pPropRep = PropertyRepository::getInstance();
      pPropRep->getStringFromStoredType( type, dstrType );

      mask = _cfgHostMasks->getValueAsString( dstrType.strip() );
   }

   return mask.length() != 0;
}


bool DataElementProperties::getCfgDisplayMask( ELEMENTTYPE type,
                                               const ClientLocale &clientLocale,
                                               DString &mask )
{
   mask = NULL_STRING;

   if ( _cfgDisplayMasks )
   {
      DString strType;
      DString dstrKey = clientLocale.getLocale();

      PropertyRepository *pPropRep = PropertyRepository::getInstance();
      // Get data type string
      pPropRep->getStringFromStoredType( type, strType );

      dstrKey.append( I_( "-" ) )
             .append( strType.stripLeading() );

      mask = _cfgDisplayMasks->getValueAsString( dstrKey );
   }

   return mask.length() != 0;
}


DataElementProperties::FieldAndOverrides *DataElementProperties::getFieldItems(
   const ClientLocale *pClientLocale
   ) const
{
   const ClientLocale *pCloc =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   FieldAndOverridesMapType::const_iterator itemsIter = findField( *pCloc );

   if ( itemsIter == m_mapFieldItems.end() )
   {
      DString msg( I_("locale=") );
      msg += pCloc->getLocale();
      msg += I_(";element=");
      msg += _name;
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_("DataElementProperties::getFieldItems"),
                        DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
   }
   return ( *itemsIter ).second;
}


bool DataElementProperties::getLocale( const ClientLocale& clientLocale )
{
   if ( _cameFromRepository )
   {
      PropertyRepository *pPropRep = PropertyRepository::getInstance();
      if ( pPropRep )
      {
         if ( pPropRep->getField( _name, clientLocale ) )
         {
            return true;
         }
      }
   }
   return false;
}


DataElementProperties::SubsAndOverrides *DataElementProperties::getSubsItems(
   const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pCloc =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   SubsAndOverridesMapType::const_iterator itemsIter = findSubs( *pCloc );

   if ( itemsIter == m_mapSubsItems.end() )
   {
      return NULL;
   }
   return ( *itemsIter ).second;
}


DataElementProperties::MaskAndOverrides *DataElementProperties::getMaskItems(
   const ClientLocale &clientLocale ) const
{
   MaskAndOverridesMapType::const_iterator itemsIter;
   itemsIter = findMask( clientLocale );

   if ( itemsIter == m_mapMaskItems.end() )
   {
      return NULL;
   }
   return ( *itemsIter ).second;
}


void DataElementProperties::fillSubstitutionMapFromString(
                                                const DString &subString,
                                                SubstitutionMap &subMap,
                                                SubStringVectorType &subVector )
{
   if ( subString.length() > 0 )
   {
      bool done = false, allOK = true, doesExist = false;
      DString::size_type start = 0L, separatorPosition, terminatorPosition;
      DString::size_type length = subString.length();
      DString key;

      while( !done && allOK )
      {
         // Look for the next separator
         separatorPosition = subString.find( SEPARATOR_CHAR, start );

         if ( -1 == separatorPosition )
         {
            // Stop if a separator was not found
            done = true;
         }
         else
         {
            // Extract the key & look for the next terminator
            key = subString.substr( start, separatorPosition - start );

            stripTrailing( key );

            // Check if the key indicates a replacement but doesn't exist
            if ( subMap.end() != subMap.find( key ))
            {
               allOK = false;
            }

            terminatorPosition = subString.find( TERMINATOR_CHAR,
                                                        separatorPosition + 1 );

            if ( -1 == terminatorPosition )
            {
               // Stop if a terminator was not found, but
               terminatorPosition = length;
               done = true;
            }

            // Extract the value & add it to the object
            subMap[ key ] = subString.substr( separatorPosition + 1,
                                   terminatorPosition - separatorPosition - 1 );
            subVector.push_back( key );

            start = terminatorPosition + 1;
         }
      }
   }
}


const DataElementProperties::BaseAndMarketItems *
   DataElementProperties::_getBAMItems( const ClientLocale& cloc ) const
{
   ClientLocale *pLoc = const_cast<ClientLocale *>(&cloc);
   bool bDeleteLocale = false;

   if ( cloc.getLocale() != I_( "enUS" ) )
   {  // Only create locale if not aleady enUS.  Could also change BAMItems
      //  to be keyed on Market/Client string instead of locale object.
      pLoc = new ClientLocale( cloc );
      pLoc->setLocale( I_( "enUS" ) );
      bDeleteLocale = true;
   }

   BAMItemsMapType::const_iterator iter = findBaseAndMarket( *pLoc );

   if ( m_mapBaseAndMarketItems.end() == iter )
   {
      // This is kindof cheap. Later on, we will change the appropriate
      // members to mutable so we don't need this.
      ( const_cast< DataElementProperties *>( this ) )->getLocale( cloc );
      iter = findBaseAndMarket( *pLoc );
   }
   if ( bDeleteLocale )
   {  // We created, so delete
      delete pLoc;
   }

   if ( m_mapBaseAndMarketItems.end() == iter )
   {
      DString msg( I_("locale=enUS") );
      msg += I_(";element=");
      msg += _name;

      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_("DataElementProperties::_getBAMItems"),
                        DIDBRKR_LOCALE_NOT_FOUND, msg.c_str() );
   }

   return ( *iter ).second.getElement();
}


void DataElementProperties::_setDecimalFormatSymbols(
   JavaDecimalFormat& formatter,
   const DString& dstrLocale ) const
{
   MAKEFRAME( DIDBRKR_COMPONENT_NAME,
              I_( "DataElementProperties::_setDecimalFormatSymbols()" ) );

   DString dstrKey( dstrLocale );
   dstrKey.strip();
   dstrKey += I_( "-DN" );

   DString dstrFormatOverrideIDI =
      GetConfigValueAsString( I_( "DICORE" ),
                              I_( "FormattingOverrides" ),
                              dstrKey );

   if ( 0 == dstrFormatOverrideIDI.length() )
   {
      return;
   }

   UErrorCode status;
   DecimalFormatSymbols symbols( status );

   formatter.getDecimalFormatSymbols( symbols );

   DString dstrValue;

   if ( getIdiValue( dstrFormatOverrideIDI, I_( "0" ), dstrValue ) )
   {
      symbols.setSymbol(DecimalFormatSymbols::ENumberFormatSymbol::kZeroDigitSymbol, dstrValue[ 0 ] );
   }

   if ( getIdiValue( dstrFormatOverrideIDI, I_( "." ), dstrValue ) )
   {
      symbols.setSymbol(DecimalFormatSymbols::ENumberFormatSymbol::kDecimalSeparatorSymbol, dstrValue[ 0 ] );
   }

   if ( getIdiValue( dstrFormatOverrideIDI, I_( "-" ), dstrValue ) )
   {
      symbols.setSymbol(DecimalFormatSymbols::ENumberFormatSymbol::kMinusSignSymbol, dstrValue[ 0 ] );
   }

   if ( getIdiValue( dstrFormatOverrideIDI, I_( "," ), dstrValue ) )
   {
      symbols.setSymbol(DecimalFormatSymbols::ENumberFormatSymbol::kGroupingSeparatorSymbol, dstrValue[ 0 ] );
   }

   formatter.setDecimalFormatSybols( symbols );
}

DataElementProperties::FieldAndOverridesMapType::const_iterator DataElementProperties::findField( const ClientLocale & clientLocale ) const
{
   FieldAndOverridesMapType::const_iterator iter;
   FieldAndOverridesMapType::const_iterator returnIter = m_mapFieldItems.end();

   std::pair< FieldAndOverridesMapType::const_iterator,
              FieldAndOverridesMapType::const_iterator > p = m_mapFieldItems.equal_range( clientLocale );

   iter = p.first;
   if ( p.first == m_mapFieldItems.end() || std::distance( p.first, p.second ) == 1 )
   {  // 0 or 1 element exists for this ClientLocale in the map, so just return the iterator
      returnIter = p.first;    // end or one we want
   }
   else
   {
      bool bMarketOnly = false;
      while ( iter != p.second )
      {
         const ClientLocale& r = (*iter).first;
         if ( r.getMarketIndex() == clientLocale.getMarketIndex() )
         {  // We have market match
            if ( r.getClientIndex() == clientLocale.getClientIndex() )
            {  // Market/Client - always use exact match
               returnIter = iter;
               break;
            }
            else if ( r.getClientIndex() == BinFileHeader::s_ulNoClient )
            {  // We have market only override, use this over no market/client default
               returnIter = iter;
               bMarketOnly = true;
            }
            // otherwise, default for a different client - ignore and get next one
         }
         else if ( !bMarketOnly && r.getClientIndex() == BinFileHeader::s_ulNoClient &&
              r.getMarketIndex() == BinFileHeader::s_ulNoMarket )
         {  // Default to use if no market and/or client overrides
            returnIter = iter;
         }
         ++iter;
      }
   }
   if ( returnIter == m_mapFieldItems.end() )
   {
      std::pair< FieldAndOverridesMapType::const_iterator,
                 FieldAndOverridesMapType::const_iterator > p = m_mapFieldItems.equal_range( ClientLocale( I_( "" ) ) );
      returnIter = p.first;
   }
   return returnIter;
}


DataElementProperties::MaskAndOverridesMapType::const_iterator DataElementProperties::findMask( const ClientLocale & clientLocale ) const
{
   MaskAndOverridesMapType::const_iterator iter;
   MaskAndOverridesMapType::const_iterator returnIter = m_mapMaskItems.end();

   std::pair< MaskAndOverridesMapType::const_iterator,
              MaskAndOverridesMapType::const_iterator > p = m_mapMaskItems.equal_range( clientLocale );

   iter = p.first;
   if ( p.first == m_mapMaskItems.end() || std::distance( p.first, p.second ) == 1 )
   {  // 0 or 1 element exists for this ClientLocale in the map, so just return the iterator
      returnIter = p.first;    // end or one we want
   }
   else
   {
      bool bMarketOnly = false;
      while ( iter != p.second )
      {
         const ClientLocale& r = (*iter).first;
         if ( r.getMarketIndex() == clientLocale.getMarketIndex() )
         {  // We have market match
            if ( r.getClientIndex() == clientLocale.getClientIndex() )
            {  // Market/Client - always use exact match
               returnIter = iter;
               break;
            }
            else if ( r.getClientIndex() == BinFileHeader::s_ulNoClient )
            {  // We have market only override, use this over no market/client default
               returnIter = iter;
               bMarketOnly = true;
            }
            // otherwise, default for a different client - ignore and get next one
         }
         else if ( !bMarketOnly && r.getClientIndex() == BinFileHeader::s_ulNoClient &&
              r.getMarketIndex() == BinFileHeader::s_ulNoMarket )
         {  // Default to use if no market and/or client overrides
            returnIter = iter;
         }
         ++iter;
      }
   }
   if ( returnIter == m_mapMaskItems.end() )
   {
      std::pair< MaskAndOverridesMapType::const_iterator,
                 MaskAndOverridesMapType::const_iterator > p = m_mapMaskItems.equal_range( ClientLocale( I_( "" ) ) );
      returnIter = p.first;
   }
   return returnIter;
}


DataElementProperties::SubsAndOverridesMapType::const_iterator DataElementProperties::findSubs( const ClientLocale & clientLocale ) const
{
   SubsAndOverridesMapType::const_iterator iter;
   SubsAndOverridesMapType::const_iterator returnIter = m_mapSubsItems.end();

   std::pair< SubsAndOverridesMapType::const_iterator,
              SubsAndOverridesMapType::const_iterator > p = m_mapSubsItems.equal_range( clientLocale );

   iter = p.first;
   if ( p.first == m_mapSubsItems.end() || std::distance( p.first, p.second ) == 1 )
   {  // 0 or 1 element exists for this ClientLocale in the map, so just return the iterator
      returnIter = p.first;    // end or one we want
   }
   else
   {
      bool bMarketOnly = false;
      while ( iter != p.second )
      {
         const ClientLocale& r = (*iter).first;
         if ( r.getMarketIndex() == clientLocale.getMarketIndex() )
         {  // We have market match
            if ( r.getClientIndex() == clientLocale.getClientIndex() )
            {  // Market/Client - always use exact match
               returnIter = iter;
               break;
            }
            else if ( r.getClientIndex() == BinFileHeader::s_ulNoClient )
            {  // We have market only override, use this over no market/client default
               returnIter = iter;
               bMarketOnly = true;
            }
            // otherwise, default for a different client - ignore and get next one
         }
         else if ( !bMarketOnly && r.getClientIndex() == BinFileHeader::s_ulNoClient &&
              r.getMarketIndex() == BinFileHeader::s_ulNoMarket )
         {  // Default to use if no market and/or client overrides
            returnIter = iter;
         }
         ++iter;
      }
   }
   if ( returnIter == m_mapSubsItems.end() )
   {
      std::pair< SubsAndOverridesMapType::const_iterator,
                 SubsAndOverridesMapType::const_iterator > p = m_mapSubsItems.equal_range( ClientLocale( I_( "" ) ) );
      returnIter = p.first;
   }
   return returnIter;
}

DataElementProperties::BAMItemsMapType::const_iterator DataElementProperties::findBaseAndMarket( const ClientLocale & clientLocale ) const
{
   BAMItemsMapType::const_iterator iter;

   iter = m_mapBaseAndMarketItems.find( clientLocale );

   if ( m_mapBaseAndMarketItems.end() == iter )
   {
      if ( ( clientLocale.getMarketIndex() != BinFileHeader::s_ulNoMarket ) ||
           ( clientLocale.getClientIndex() != BinFileHeader::s_ulNoClient ) )
      {
         ClientLocale cloc( clientLocale );

         if ( clientLocale.getClientIndex() != BinFileHeader::s_ulNoClient )
         {
            cloc.setClient( BinFileHeader::s_ulNoClient );

            iter = m_mapBaseAndMarketItems.find( cloc );
         }

         if ( m_mapBaseAndMarketItems.end() == iter )
         {
            if ( clientLocale.getMarketIndex() != BinFileHeader::s_ulNoMarket )
            {
               cloc.setMarket( BinFileHeader::s_ulNoMarket );

               iter = m_mapBaseAndMarketItems.find( cloc );
            }
         }
      }
   }

   return ( iter );
}


DataElementProperties::MaskAndOverrides::~MaskAndOverrides()
{
   delete pDateDisplayFormatter;
   pDateDisplayFormatter = 0;

   delete pNumberDisplayFormatter;
   pNumberDisplayFormatter = 0;
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/dataelementproperties.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:22   kovacsro
// Initial revision.
// 
//    Rev 1.77   Oct 23 2001 14:57:26   DT11159
// Fixed _formatInteger() so that it uses the entire mask.
// The code was ignoring the first character of the mask.
// 
//    Rev 1.76   Oct 23 2001 13:29:32   DT11159
// Fixed removeMaskFromValue() so that it works for INTEGER fields.
//
//    Rev 1.75   Sep 21 2001 16:19:36   DT11159
// Made changes to support the new bin file format.
//
//    Rev 1.74   Jun 29 2001 12:41:42   DT11159
// Simplified addSubsLocale.
//
//    Rev 1.73   May 18 2001 15:19:36   dt24433
// Changes to formatting.
// Switch to Guard\CriticalSectionLock from CriticalSection\MutexSemaphore.
//
//
//    Rev 1.72   Mar 29 2001 13:06:24   dt24433
// Made isi18NValid and isi18NValidForHost private.
// Removed duplicated length check from isi18NValid.
// Reordered some methods.
//
//    Rev 1.71   Mar 26 2001 16:11:30   dt24433
// Added getFormattedValue method (from getValueFromBuffer).
//
//    Rev 1.70   Mar 24 2001 13:55:04   dt24433
// Changed 3 maps to multi-maps to provide more efficient lookup for market/client information.
// Keyed by ClientLocale, but using locale only comparison with additional logic provided in find
// methods.
//
//    Rev 1.69   Mar 22 2001 16:32:00   dt24433
// Implemented unauthorizedSetElementValue.
// Fixed I18N_INTEGER default.
// Made isI18Valid and isI18ValidForHost const.
// Removed DataElementProperties copys in those 2 methods.
//
//    Rev 1.68   Mar 21 2001 11:49:28   dt24433
// Removed assert.
//
//    Rev 1.67   Mar 21 2001 11:39:38   dt24433
// Fixed so header file does not force inclusion of ICU libraries for users.
// Added safety check in getValueInBuffer for memcpy.
// Filling out new datatypes with spaces for buffer - needs more work.
//
//    Rev 1.66   Mar 06 2001 18:42:36   dt24433
// Work around for bin/mdb maxLength = 0 fields (shouldn't be allowed).
//
//    Rev 1.65   Mar 06 2001 16:17:20   dt24433
// Added work around for bin/mdb files having default values longer than maxLength.
//
//    Rev 1.64   Mar 02 2001 14:48:40   dt24433
// Added support for get/set of field values directly to/from the data object's buffer.
// Made several methods const.
// getFieldLabel and getDefaultValue now return const DString & instead of DString.
// getId has been split into getId and getName as appropriate.
// removed/consolidated code due to always loading all locales for an element up front.
// Implemented quick flags for hasMask and hasSubstitute for performance.
// Use mutex instead of SWMR lock.
//
//    Rev 1.63   Jan 20 2001 16:41:04   dt24433
// Changed getMask to pass in correct locale to getMaskItems.
//
//    Rev 1.62   Jan 19 2001 16:55:48   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.61   Jan 08 2001 15:17:44   dt24433
// Cleaned up code to use ClientLocales instead of pulling out various strings and JavaLocales.
//
//    Rev 1.60   Jan 04 2001 16:46:46   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.59   Nov 22 2000 07:04:54   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.58   Oct 13 2000 15:55:06   dt17817
// Add support for setting a field with a substitution value that is
// not the correct case
//
//    Rev 1.57   Oct 10 2000 08:53:32   dt17817
// Add ability to override default formatting for a locale based on registry input
//
//    Rev 1.56   Sep 30 2000 17:01:06   dt17817
// Add support for '+' to I18N_DECIMALS, since the ICU (Java) stuff
// doesn't know about them.
//
//    Rev 1.55   Sep 27 2000 13:37:22   dt17817
// Remove ClientLocale from DataCompoentProperties
//
//    Rev 1.54   Sep 22 2000 12:20:38   dt17817
// Another hack due to the default values for signed numbers getting
// a space at the front and a decimal point placed in them.
// This points to a semantic difference between the default value in
// the ddtools and the default value in the c++ code.
// This should be resolved in the db memory size rewrite.
//
//
//    Rev 1.53   Sep 11 2000 16:42:32   dt17817
// Remove some deadlocks
//
//    Rev 1.52   Sep 05 2000 06:19:58   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.51   Aug 28 2000 16:27:30   dtwk
// Fix _getBAMItems() to not cause an access violation if locale is not found
//
//    Rev 1.50   Aug 24 2000 08:34:40   dtwk
// Change THROWEXCEPTIONCONDITION to THROWFROMFILEIDI
//
//    Rev 1.49   Aug 24 2000 07:18:14   dtwk
// Add in more support for clients and markets
//
//    Rev 1.48   Aug 09 2000 08:43:14   dtwk
// Add in support for clients and markets
//
//    Rev 1.47   Jun 05 2000 07:43:38   dtwk
// Fix thread-safety of i18n types
//
//    Rev 1.46   May 31 2000 09:32:56   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.45   Apr 20 2000 11:35:00   dtwk
// Plug two memory leaks
//
//    Rev 1.44   Apr 11 2000 13:25:10   dtwk
// Synch up with ICU class changes
//
//    Rev 1.43   Apr 10 2000 11:46:54   dtwk
// Updates for thread-safety
//
//    Rev 1.42   Jan 18 2000 17:36:56   dtwk
// Fix DataElementProperties::getSubstituteValue()
// to strip spaces before doing comparison when doing
// case-insensitive searchve too.
//
//    Rev 1.41   Jan 16 2000 12:19:32   dtwk
// -Change registry key from IngoreCaseOnSubKeys to IgnoreCaseOnSubKeys.
// -Fix problem on substitutes where case insensitive checking would return invalid
//  data if the key was not found.
//
//
//    Rev 1.40   Jan 13 2000 12:49:30   dtwk
// - Use ConfigurationManager DICORE instead of DataBroker to
//   find the host and display masks in the registry
// - Set option for case insensitive substituion map keys (host data)
//
//
//    Rev 1.39   Dec 09 1999 09:15:42   dtwk
// Make sure default values in data dictionary are not longer than the
// max length of field
//
//    Rev 1.38   Nov 23 1999 14:03:12   dtwk
// Fix support for setting default values from .bin file
//
//    Rev 1.37   Oct 06 1999 13:55:04   DCYK
// Don't delete pointers returned by JavaLocale::getLocaleInstance
// and JavaLocale::getUSInstance.
// This is a temporary fix.
//
//
//    Rev 1.36   Oct 06 1999 11:35:28   DCYK
// Add support for redefines.
//
//
//    Rev 1.35   Oct 04 1999 15:26:26   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.34   Oct 04 1999 10:23:20   DCYK
// Threading fixes.
//
//
//    Rev 1.33   Sep 23 1999 16:17:54   DCYK
// Partial fix for locales in formatUsingMask.
//
//
//    Rev 1.32   Sep 21 1999 09:53:48   DCYK
// Strip trailing spaces from keys for substitution
// sets, both when creating sets and when
// searching through them.
//
//
//    Rev 1.31   Sep 14 1999 12:44:20   DCYK
// In removeMaskFromValue, if element has no
// mask, don't change the value.
//
//
//    Rev 1.30   Sep 09 1999 11:11:32   dtwk
// Remove calls to JavaDecimalFormat::setLenient()
//
//    Rev 1.29   Sep 03 1999 15:32:44   dtwk
// Add isValidForHost and isI18NValidForHost
// Plug minor mem leak
//
//    Rev 1.28   Aug 26 1999 13:37:10   dtwk
// Changes to fix return codes on PropertyRepository::formatValue
//
//    Rev 1.26   Aug 19 1999 15:03:22   DCYK
// More minor performance improvements.
//
//
//    Rev 1.25   Aug 12 1999 09:45:38   DCYK
// Add ability to get substitution values in properties order or alphabetical order.
//
//
//    Rev 1.24   Aug 06 1999 14:21:14   DCYK
// Performance improvements.
//
//
//    Rev 1.23   Aug 05 1999 16:37:56   DCYK
// Performance improvements from Tom H. & Michael M.
//
//
//    Rev 1.22   Aug 04 1999 12:18:22   DCYK
// Fixed problem in masking.
//
//
//    Rev 1.21   Jul 29 1999 10:33:06   DCYK
// Minor performance improvements.
//
//    Rev 1.20   Jul 28 1999 14:19:20   DCYK
// Performance improvements.
//
//
//    Rev 1.19   Jul 26 1999 09:50:20   DCYK
// Change "USen" to "enUS".
// Clean up code.
//
//
//    Rev 1.18   Jul 16 1999 09:19:32   DCYK
// Strip leading '+' from signed values.
//
//
//    Rev 1.17   Jul 14 1999 15:49:54   DCYK
// Jerry fixes.
//
//
//    Rev 1.16   Jul 13 1999 18:00:04   dtwk
// Change so that I18N_ registry entries do not have spaces:
// enUS- D becomes enUS-D
//
//    Rev 1.15   Jul 13 1999 15:30:04   DCYK
// Fixed problem with I18N_Date type, where an uninitialized date was coming back as "Jan 1, 1970".  It now comes back as a blank.
//
//
//    Rev 1.14   06 Jul 1999 13:34:38   DCYK
// Init pHostFormatter & pDisplayFormatter in addLocale.
//
//
//    Rev 1.13   Jun 29 1999 15:59:14   DTWK
// Change dateDefault from static to automatic because it was killng the JVM on init
//
//    Rev 1.12   Jun 29 1999 09:45:46   DCYK
// Added setLocale methods.
// Fixed minor bugs.
//
//
//    Rev 1.11   Jun 14 1999 09:55:06   DCYK
// Use javalocale object to get default locales.
//
//    Rev 1.10   Jun 06 1999 13:23:04   DTWK
// Cleanup I18N formatting
//
//    Rev 1.9   May 25 1999 09:39:26   DTWK
// Add I18N_INTEGER and I18N_TIME types
//
//    Rev 1.8   May 24 1999 10:41:34   DTWK
// Add internationalized formatting and new types (date, decimal, percent, currency)
//
//    Rev 1.7   May 06 1999 16:44:02   DCYK
//
//
//    Rev 1.6   Apr 20 1999 16:49:32   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.5   09 Mar 1999 12:51:26   DT14177
// Unicode-izing
//
//    Rev 1.4   Mar 05 1999 10:25:32   DCYK
// Changes for I18N.
//
//
//    Rev 1.3   Feb 11 1999 15:04:12   DCYK
// Add support for binary elements.
//
//
//    Rev 1.2   Jan 28 1999 14:03:52   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   29 Jul 1998 20:30:52   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.12   Jul 22 1998 10:12:44   dcyk
// Performance improvements
// from Paul D.
//
//
//    Rev 1.11   Jun 18 1998 11:11:32   dcyk
// Remove tracing.
//
//
//    Rev 1.10   May 20 1998 11:55:40   dt27994
// Changed TRACE_BEGIN_METHOD and TRACE_END_METHOD to TRACE_METHOD.
//
//    Rev 1.9   Apr 24 1998 10:26:36   dcyk
// Fix bug in masking routines, for signed
// values with masks that don't have decimals.
//
//
//    Rev 1.8   Nov 10 1997 14:47:00   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.7   08 Sep 1997 14:26:42   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.6   05 Sep 1997 07:56:40   dcyk
// Removed most calls to MAKEFRAME, use
// TRACE_METHOD & THROWFROMFILE
// instead.
//
//
//    Rev 1.5   07 Aug 1997 15:05:16   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.4   07 Aug 1997 11:31:06   dcyk
// Add some error correction to
// mapToFormattedValue.  For integers &
// signed numbers, it now will strip off leading
// & trailing spaces, and pad to the left with '0's.
//
//
//    Rev 1.3   05 Aug 1997 13:44:18   dcyk
// Add support for percentage masks.
// Doesn't behave like other masks.
// See .hpp file for details.
//
//
//    Rev 1.2   24 Jul 1997 09:33:54   dcyk
// Use new tracing stuff.
//
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.1   08 Jul 1997 09:05:42   dcyk
// Added STL casting operators and RTTI.
// Fixed handling of negative values in
// mapToNativeValue & mapToFormattedValue.
//
//
//    Rev 1.0   Jun 13 1997 16:31:38   DTWK
//
//
//    Rev 1.16   13 Jun 1997 16:20:08   dcyk
//
//
//    Rev 1.15   05 Jun 1997 18:03:10   dcyk
// Fixed bugs in removeMask function.
//
//
//    Rev 1.14   30 May 1997 10:05:08   dcyk
// Fixed bug when passing too-long value
// to element that has a mask.  Was crashing.
//
//
//    Rev 1.13   May 29 1997 09:50:46   dcyk
// Added support for substitute values
// and masking.
//
//
//    Rev 1.12   May 09 1997 16:42:24   dcyk
//
//
//    Rev 1.11   May 06 1997 10:14:00   dcyk
// Cleaned up documentation & comments.
//
//
//    Rev 1.10   May 01 1997 08:43:30   dcyk
// Removed repeat handling stuff.
//
// Added documentation.
//
//
//    Rev 1.9   Apr 11 1997 08:56:58   dcyk
//
//
//    Rev 1.8   Apr 04 1997 09:49:36   dcyk
//
//
//    Rev 1.7   Mar 25 1997 15:53:10   dcyk
// Removed friend declarations of DataProperties
// and DataElement.
//
// Made items struct private.
//
// Added mapToNativeValue & mapToFormattedValue.
//
// Added getDefaultValue that returns a string.
//
//
//    Rev 1.6   Feb 21 1997 12:15:38   dcyk
// Modified isValid to strip leading zeroes
// from decimal numbers.
// Modified formatValue to strip leading zeroes
// and to handle decimal numbers with no
// digits after the decimal point, or no decimal
// point at all.
//
//
//    Rev 1.5   Feb 11 1997 14:24:32   dcyk
// Added #include "srcprag.h" to suppress
// compiler warnings.
// Added formatValue member function.
// Added support for rounding.
//
//
//    Rev 1.4   Jan 19 1997 12:59:02   DRUS
// Implemented == and != operators.  Fixed copy constructor.
// Fixed isValid to handle proper lengths in decimals.
//
//    Rev 1.3   Jan 17 1997 18:45:18   dcyk
// Fixed bug in isValid, failed when the value
// string was shorter than the number of
// digits that were supposed to be after the
// decimal.  Now check number of digits before
// and after against what is valid.
//
//
//    Rev 1.2   Dec 31 1996 13:45:18   DRUS
// Implemented the isValid() method.
//
//    Rev 1.1   Nov 21 1996 14:38:12   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:16   DRUS
//
//

