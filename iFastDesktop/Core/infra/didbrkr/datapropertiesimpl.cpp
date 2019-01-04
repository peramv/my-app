//
// COPYRIGHT:
//
//    The computer systems, procedures, databases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DataPropertiesImpl.cpp
// ^AUTHOR : Chris Kennedy
// ^DATE   : 03/12/97
//
// ----------------------------------------------------------
//
// ^CLASS : DataPropertiesImpl
//
// ^INHERITS FROM : None
//
// ^MEMBER VARIABLES :
//    ^NAME :        _fileName
//    ^TYPE :        string
//    ^DESCRIPTION : Name of the file containing the details of the object.
//
//    ^NAME :        _id
//    ^TYPE :        string
//    ^DESCRIPTION : ID of this DataPropertiesImpl object.  Not always the same
//                   as the _fileName.
//
//    ^NAME :        _maxLength
//    ^TYPE :        unsigned long
//    ^DESCRIPTION : Maximum string length of any of the DataElementProperties
//                   or DataProperties objects in this object.
//
//    ^NAME :        _propertyMap
//    ^TYPE :        map< string, DataComponentProperties *, less< string >,
//                                                          allocator >
//    ^DESCRIPTION : Map of properties, sorted by their name.
//
//    ^NAME :        _propertyOrder
//    ^TYPE :        vector< DataComponentProperties *, allocator >
//    ^DESCRIPTION : Vector of properties, stored in the order they were read
//                   in from the file.
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
#include <srcprag.h>
#endif

#ifndef DATAPROPERTIESIMPL_HPP
   #include "datapropertiesimpl.hpp"
#endif

#ifndef INCLUDED_IO_H
#define INCLUDED_IO_H
   #include <io.h>
#endif

#ifndef INCLUDED_TYPEINFO
#define INCLUDED_TYPEINFO
#include <typeinfo>
#endif
#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
#include <fstream>
#endif
#ifndef INCLUDED_IOMANIP
#define INCLUDED_IOMANIP
#include <iomanip>
#endif

#ifndef INCLUDED_STDIO_H
#define INCLUDED_STDIO_H
#include <stdio.h>
#endif

#ifndef BASE_H
   #include "base.h"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef DATACOMPONENTPROPERTIES_HPP
   #include "datacomponentproperties.hpp"
#endif

#ifndef DATAELEMENTPROPERTIES_HPP
   #include "dataelementproperties.hpp"
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#ifndef DIDBRKR_H
   #include "didbrkr.h"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef PROPERTYREPOSITORY_HPP
   #include "propertyrepository.hpp"
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif

namespace
{
   const short BUFFER_SIZE = 1024;
   const short VIEWNAME_POS     =  0;
   const short VIEWNAME_SIZE    =  8;
   const short ELEMENTNAME_POS  =  8;
   const short ELEMENTNAME_SIZE = 30;
   const short TYPECODE_POS     = 38;
   const short LENGTH_POS       = 39;
   const short LENGTH_SIZE      =  4;
   const short DECIMAL_POS      = 43;
   const short DECIMAL_SIZE     =  4;
   const short LINENUMBER_POS   = 47;
   const short LINENUMBER_SIZE  =  4;
   const short MIN_LINE_SIZE    = 51;

   const I_CHAR * const CLASS_NAME = I_( "DataPropertiesImpl" );
   static const DString strEmpty = NULL_STRING;

   const I_CHAR SEPARATOR_CHAR = '=';
   const I_CHAR TERMINATOR_CHAR = ';';
   const I_CHAR EOL_CHAR = '\n';

   CriticalSectionLock s_mutex;
}

typedef DataProperties DP;
typedef DataPropertiesImpl DPI;
typedef DataComponentProperties DCP;
typedef DataElementProperties DEP;


//******************************************************************************
//              Public Methods
//******************************************************************************

DataPropertiesImpl::DataPropertiesImpl() :
   _maxLength( 0L ), _propertyCount( 0L ),
   _isRepeatable( false ),
   _ulongId( ULONG_MAX ),
   _ulCalcFixedByteLength( 0 ),
   _ulCalcFixedLength( 0 )
{
}


DataPropertiesImpl::DataPropertiesImpl( const DString &id,
                                        bool isRepeatable ) :
   _maxLength( 0L ), _propertyCount( 0L ),
   _isRepeatable( isRepeatable ),
   _ulongId( ULONG_MAX ), _id( id ),
   _fileName( id ),
   _ulCalcFixedByteLength( 0 ),
   _ulCalcFixedLength( 0 )
{
   bool foundFirst = false;
   DStringA locIDA( id );
   DString msg( I_("file=") );
   msg += _fileName;
   if ( !isRepeatable &&
        ( -1 == _fileName.find( DEFAULT_REPEAT_RECORD )))
   {
      i_ifstream inViewFile;
      if ( access( locIDA.c_str(), 00 )) // check if file exists
      {
         // Apparently, once you do an unsuccessful open on an ifstream,
         // you can't just do another open.
         i_ifstream inViewFile2;
         ConfigManager *theMgr = ConfigManager::getManager( I_("DataBroker") );
         Configuration theConfig = theMgr->retrieveConfig( I_("DataPath") );
         DStringA envPath( theConfig.getValueAsString( I_("Path") ));
         if ( envPath.length() )
         {
            DStringA locFileName;
            DStringA pathString( envPath );
            DStringA dirSepString( I_("\\") );
            DStringA::size_type
                           lastDirSep = pathString.find_last_of( dirSepString );
            if ( -1 == lastDirSep )
            {
               lastDirSep = 0;
            }
            DStringA::size_type
                         lastChar = pathString.find_last_not_of( dirSepString );
            if ( -1 == lastChar )
            {
               lastChar = 0;
            }
            if ( lastDirSep <= lastChar )
            {
               pathString += dirSepString;
            }
            locFileName = pathString + DStringA(_fileName);
            if ( !access( locFileName.c_str(), 00 )) // check if file exists
            {
               inViewFile2.open( locFileName.c_str() );
               if ( !inViewFile2 )
               {
                  THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                                  I_("DataPropertiesImpl::DataPropertiesImpl(")
                                  I_(" const DString & )"),
                                  DIDBRKR_CANT_OPEN_PROPERTIES_FILE,
                                  msg.c_str() );
               }
               else
               {
                  inViewFile2 >> *this;
                  inViewFile2.close();
               }
            }
            else
            {
               THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                                 I_("DataPropertiesImpl::DataPropertiesImpl( ")
                                 I_("const DString & )"),
                                 DIDBRKR_CANT_OPEN_PROPERTIES_FILE,
                                 msg.c_str() );
            }
         }
         else
         {
            THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                              I_("DataPropertiesImpl::DataPropertiesImpl( ")
                              I_("const DString & )"),
                              DIDBRKR_NO_PATH_TO_PROPERTIES_FILE, msg.c_str() );
         }
      }
      else
      {
         inViewFile.open( locIDA.c_str() );
         inViewFile >> *this;

         inViewFile.close();
      }
   }

   _calculateOffsets();
}


DataPropertiesImpl::DataPropertiesImpl( const DataPropertiesImpl& copy ) :
   _fileName( copy._fileName ), _id( copy._id ),
   _propertyOrder( copy._propertyOrder ),
   _propertyIndex( copy._propertyIndex ),
   _maxLength( 0L ), _propertyCount( copy._propertyCount ),
   _isRepeatable( copy._isRepeatable ),
   m_redefineMap( copy.m_redefineMap ),
   _ulongId( ULONG_MAX ),
   _ulCalcFixedByteLength( 0 ),
   _ulCalcFixedLength( 0 )
{
   DCPPtrMapType::const_iterator iter = copy._propertyMap.begin();

   while ( copy._propertyMap.end() != iter )
   {
      PropertyInfo *pPICopy = new PropertyInfo( *( iter->second ) );
      _propertyMap[ iter->first ] = pPICopy;
      ++iter;
   }
}


DataPropertiesImpl::DataPropertiesImpl( const DString &propsId,
                                        bool isRepeatable,
                                        const DCPPtrVectorType &propsVector ) :
   _maxLength( 0L ), _propertyCount( 0L ),
   _isRepeatable( isRepeatable ),
   _ulongId( ULONG_MAX ), _id( propsId ),
   _ulCalcFixedByteLength( 0 ),
   _ulCalcFixedLength( 0 )
{
   PROPERTY_INFO * pPropertyInfo = NULL;
   int nIndex = 0;
   _fileName = propsId;
   DString name, tempName;
   unsigned long fieldId;
   PropertyRepository *pProp = PropertyRepository::getInstance();

   for ( DCPPtrVectorType::const_iterator iter = propsVector.begin();
         iter != propsVector.end(); ++iter )
   {
      _propertyCount++;
      if ( _propertyMap.end() != _propertyMap.find( (*iter)->getName() ))
      {
         DString msg( I_("ele=") );
         msg += _id;
         msg += I_(";file=");
         msg += getName();

         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("DataPropertiesImpl::DataPropertiesImpl"),
                           DIDBRKR_DUPLICATE_PROPERTIES,
                           msg.c_str() );
      }
      pPropertyInfo = new PROPERTY_INFO( (*iter), nIndex++ );
      if ( !pPropertyInfo )
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME,
                        I_("DataPropertiesImpl::DataPropertiesImpl"),
                        BASE_ALLOC_FAIL );
      }
      name = (*iter)->getName();
      tempName = _id + DEFAULT_REPEAT_RECORD;

      if ( pProp->isCaseSensitive() )
      {
         if ( name == tempName )
         {
            name = DEFAULT_REPEAT_RECORD;
         }
      }
      else
      {
         if ( 0 == i_stricmp( name.c_str(), tempName.c_str() ) )
         {
            name = DEFAULT_REPEAT_RECORD;
         }
      }

      _propertyMap[ name ] = pPropertyInfo;
      _propertyOrder.push_back( (*iter) );

      fieldId = (*iter)->getId();

      if ( ULONG_MAX != fieldId )
      {
         _propertyIndex[ fieldId ] = pPropertyInfo;
      }

      assignVectorIndexes( *(*iter) );
   }

   _calculateOffsets();
}

DataPropertiesImpl::~DataPropertiesImpl()
{
   DCPPtrMapType::iterator iter;
   for ( iter = _propertyMap.begin();
         iter != _propertyMap.end();
         ++iter )
   {
      delete (*iter).second;
   }
}

i_istream &operator>> ( i_istream &stream, DataPropertiesImpl &propertiesImpl )
{
   MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME,
                     I_("DataPropertiesImpl::operator>>") );
   char bufferC[BUFFER_SIZE];
   I_CHAR *buffer = ( I_CHAR * )bufferC;
   DString lineBuf;
   unsigned long numLines = 0L, repeatOffset = 0L, lineNumber = 0L;
   DString tempStr;
   DString msg( I_("Data Set=") );
   msg += propertiesImpl.getName();

   DCP *propertyPtr = NULL;
   DP *repeatPtr = NULL;
   DataPropertiesImpl::PROPERTY_INFO * pPropertyInfo = NULL;

   DString name;
   DEP::ELEMENTTYPE propType = DEP::NO_TYPE;
   unsigned long length = 0L, count = 0L;
   unsigned long decimalPlace = 0;

   bool repeatFlag = false;

   DataPropertiesImpl::DCPPtrMapType::iterator iter;


   // Clear all items in the lists...
   for ( iter = propertiesImpl._propertyMap.begin();
         iter != propertiesImpl._propertyMap.end();
         ++iter )
   {
      delete (*iter).second;
   }
   propertiesImpl._propertyMap.erase( propertiesImpl._propertyMap.begin(),
                                      propertiesImpl._propertyMap.end() );
   propertiesImpl._propertyOrder.erase( propertiesImpl._propertyOrder.begin(),
                                        propertiesImpl._propertyOrder.end() );
   propertiesImpl._propertyIndex.erase( propertiesImpl._propertyIndex.begin(),
                                        propertiesImpl._propertyIndex.end() );

   // Read the initial line containing the line count...
   stream.getline( buffer, BUFFER_SIZE );
   lineBuf = buffer;

   if ( stream.eof()  ||  stream.gcount() < MIN_LINE_SIZE )
   {
      throw EXCEPTIONFROMFILEIDI( DIDBRKR_BAD_FORMAT_IN_STREAM_FILE,
                                msg.c_str() );
   }

   if ( stream.fail() )
   {
      throw EXCEPTIONFROMFILEIDI( DIDBRKR_ERROR_READING_STREAM_FILE,
                                msg.c_str() );
   }

   // Find the intended number of lines in the stream...
   tempStr.assign( lineBuf.substr( LENGTH_POS, LENGTH_SIZE ));
   numLines = convertToULong( tempStr );

   // Prepare the lists to contain the proper number of properties...
   propertiesImpl._propertyOrder.reserve( numLines );
   unsigned long lineLength, buffLength;
   DString thisLine, thisBuff;

   DString strShortName( DEFAULT_REPEAT_RECORD );
   DString strLongName( propertiesImpl.getFileName() );

   int nIndex       = 0;
   int nRepeatIndex = 0;

   // Map each field line into a property element...
   for ( count = 0; count < numLines; )
   {
      thisLine.erase();
      thisBuff.erase();
      lineLength = 0;
      do
      {
         stream.get( buffer, BUFFER_SIZE );
         thisBuff.assign( buffer );
         thisLine += thisBuff;
         buffLength = (unsigned long)stream.gcount();
         lineLength += buffLength;
         if ( stream.eof() )
         {
            throw EXCEPTIONFROMFILEIDI(DIDBRKR_UNEXPECTED_END_OF_STREAM_FILE,
                                     msg.c_str() );
         }

         if ( stream.fail() )
         {
            throw EXCEPTIONFROMFILEIDI( DIDBRKR_ERROR_READING_STREAM_FILE,
                                      msg.c_str() );
         }
      } while ( buffLength == BUFFER_SIZE - 1 );

      if ( stream.peek() == 10 )
      {
         // munch the new line
         stream.get();
      }

      if ( lineLength < MIN_LINE_SIZE )
      {
         throw EXCEPTIONFROMFILEIDI( DIDBRKR_INVALID_LINE_LENGTH,
                                   msg.c_str() );
      }

      // Map each field in the structure into the appropriate property item...
      name.assign( thisLine, ELEMENTNAME_POS, ELEMENTNAME_SIZE );
      stripTrailing( name, ' ' );
      switch ( thisLine[ TYPECODE_POS ] )
      {
         case 'X':
            propType = DEP::STRING;
            break;
         case 'B':
            propType = DEP::BINARY;
            break;
         case 'S':
            propType = DEP::DECIMAL;
            break;
         case '9':
            propType = DEP::INTEGER;
            break;
         case 'Y':
            if ( !repeatFlag )
            {
               nRepeatIndex = 0;
               repeatFlag = true;
               propType = DEP::NO_TYPE;

               // Create new properties for the repeat area...
               if ( I_("Begin_") == name.substr( 0, 6 ))
               {
                  name = name.substr( 6 );
               }
               else if ( I_("Begin") == name.substr( 0, 5 ))
               {
                  name = name.substr( 5 );
               }
               repeatPtr =
                  new DP( strLongName + name,
                          ClientLocale::getDefaultClientLocale(),
                          true );
               if ( !repeatPtr )
               {
                  throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
               }
               propertyPtr = repeatPtr;

               pPropertyInfo = new DataPropertiesImpl::PROPERTY_INFO(
                                                        propertyPtr, nIndex++ );

               if ( ! pPropertyInfo )
               {
                  throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
               }

               // Insert it into the property lists...
               propertiesImpl._propertyMap[ name ] = pPropertyInfo;

               propertiesImpl._propertyOrder.push_back( propertyPtr );
               ++count;
               continue;
            }
            else
            {
               repeatFlag = FALSE;
               ++count;
               if ( repeatPtr )
               {
                  repeatPtr->_pImpl->_propertyCount =
                                       repeatPtr->_pImpl->_propertyOrder.size();
               }
               continue;  // skip End_Repeat_Record
            }
            break;

         default:
            propType = DEP::NO_TYPE;
            break;
      }
      tempStr.assign( thisLine, LENGTH_POS, LENGTH_SIZE );
      length = convertToULong( tempStr );
      if ( DEP::DECIMAL == propType )
      {
         tempStr.assign( thisLine, DECIMAL_POS, DECIMAL_SIZE );
         decimalPlace = convertToULong( tempStr );
      }
      else
      {
         decimalPlace = 0;
      }

      // Create a new property element...
      if ( lineLength > MIN_LINE_SIZE + 1 )
      {
         DString extraStuff( thisLine.substr( MIN_LINE_SIZE ));
         if ( extraStuff.substr( 0, 10 ) == I_("DSTLENGTH=") )
         {
            DString strLength( extraStuff.substr( 10 )), lengthString;
            DString::size_type position = strLength.find( ';' );
            if ( position != -1 )
            {
               lengthString = strLength.substr( 0, position );
               extraStuff = strLength.substr( position + 1 );
            }
            else
            {
               lengthString = strLength;
               extraStuff = NULL_STRING;
            }
            length = convertToULong( lengthString );
            propertyPtr = new DEP( name, ClientLocale::getDefaultClientLocale(),
                                   strEmpty, false, 0, length,
                                   propType, 0, decimalPlace, ' ',
                                   DEP::STRING,DEP::LEFT, strEmpty, extraStuff);
         }
         else
         {
            propertyPtr = new DEP( name, ClientLocale::getDefaultClientLocale(),
                                   strEmpty, false, 0, length, propType,
                                   0, decimalPlace, ' ', DEP::STRING,
                                   DEP::LEFT, strEmpty,
                                   thisLine.substr( MIN_LINE_SIZE ));
         }
         if ( !propertyPtr )
         {
            throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
         }
      }
      else
      {
         propertyPtr = new DEP( name, ClientLocale::getDefaultClientLocale(),
                                strEmpty, false, 0, length,
                                propType, 0, decimalPlace );
         if ( !propertyPtr )
         {
            throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
         }
      }

      // Insert it into the property lists...
      if ( repeatFlag )
      {
         if ( repeatPtr->_pImpl->_propertyMap.end() !=
              repeatPtr->_pImpl->_propertyMap.find( name ) )
         {
            DString msg( I_("ele=") );
            msg += name;
            msg += I_(";Data Set=");
            msg += propertiesImpl.getName();
            throw EXCEPTIONFROMFILEIDI( DIDBRKR_DUPLICATE_PROPERTIES,
                                      msg.c_str() );
         }

         pPropertyInfo = new DataPropertiesImpl::PROPERTY_INFO( propertyPtr,
                                                                nRepeatIndex++);
         if ( !pPropertyInfo )
         {
            throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
         }

         repeatPtr->_pImpl->_propertyMap[ name ] = pPropertyInfo;

         repeatPtr->_pImpl->_propertyOrder.push_back( propertyPtr );

         unsigned long lFieldId = PropertyRepository::getInstance()->
            getFieldIdFromName( name );

         if ( ULONG_MAX != lFieldId )
         {
            repeatPtr->_pImpl->_propertyIndex[ lFieldId ] = pPropertyInfo;
         }
      }
      else
      {
         if ( propertiesImpl._propertyMap.end() !=
              propertiesImpl._propertyMap.find( name ) )
         {
            DString msg( I_("ele=") );
            msg += name;
            msg += I_(";Data Set=");
            msg += propertiesImpl.getName();
            throw EXCEPTIONFROMFILEIDI( DIDBRKR_DUPLICATE_PROPERTIES,
                                      msg.c_str() );
         }

         pPropertyInfo =
               new DataPropertiesImpl::PROPERTY_INFO( propertyPtr, nIndex++ );
         if ( !pPropertyInfo )
         {
            throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
         }

         propertiesImpl._propertyMap[ name ] = pPropertyInfo;
         propertiesImpl._propertyOrder.push_back( propertyPtr );

         unsigned long lFieldId = PropertyRepository::getInstance()->
            getFieldIdFromName( name );

         if ( ULONG_MAX != lFieldId )
         {
            propertiesImpl._propertyIndex[ lFieldId ] = pPropertyInfo;
         }
      }
      ++count;
   } // for

   lineLength = 0;
   do
   {
      buffLength = 0;
      stream.get( buffer, BUFFER_SIZE );
      buffLength = (unsigned long)stream.gcount();
      lineLength += buffLength;
      if ( stream.eof() )
      {
         break;
      }

   } while ( buffLength == BUFFER_SIZE - 1 );
   if ( lineLength >= MIN_LINE_SIZE )
   {
      throw EXCEPTIONFROMFILEIDI( DIDBRKR_EXTRA_LINES_IN_PROPERTIES_FILE,
                                msg.c_str() );
   }

   propertiesImpl._propertyCount = propertiesImpl._propertyOrder.size();

   DCP *dataCompProps = NULL;

   for ( count = 0L; count < propertiesImpl._propertyCount; ++count )
   {
      dataCompProps = const_cast<DCP *>(&propertiesImpl.getProperty( count ));
      propertiesImpl.assignVectorIndexes( *dataCompProps );
   }

   return stream;
}


void DataPropertiesImpl::assignVectorIndexes( DCP &dataCompProps )
{
   // Every data component property needs to have an index.  Otherwise
   // "Repeat_Record" will hav an index of 0, which cause problems later on.
   // DMUM 26 Sep 1997
   dataCompProps.setVectorIndex(
                               getVectorIndexFromName( dataCompProps.getName() ));

   if ( DCP::eDEP != dataCompProps.getType() )
   {
      DP *dataProps = static_cast<DP *>(&dataCompProps);
      unsigned long ulPropertyCount = dataProps->getPropertyCount();
      DCP *rptDataCompProps = NULL;

      for ( unsigned long count = 0L; count < ulPropertyCount; ++count )
      {
         rptDataCompProps = const_cast<DCP *>(&dataProps->getProperty( count ));
         dataProps->assignVectorIndexes( *rptDataCompProps );
      }
   }
}


bool DataPropertiesImpl::exists( const DString &propertyName ) const
{
   if ( _propertyMap.end() == _propertyMap.find( propertyName ) )
   {
      return false;
   }

   return true;
}


bool DataPropertiesImpl::exists( long id ) const
{
   if ( _propertyIndex.end() == _propertyIndex.find( id ) )
   {
      return false;
   }

   return true;
}


unsigned long DataPropertiesImpl::getFieldIdFromName( const DString &name ) const
{
   DCPPtrMapType::const_iterator iter = _propertyMap.find( name );

   if ( _propertyMap.end() == iter )
   {
      return ULONG_MAX;
   }
   else
   {
      return (*iter).second->pProperties->getId();
   }
}


unsigned long DataPropertiesImpl::getFixedByteLength() const
{
   if ( _ulCalcFixedByteLength )
   {
      return _ulCalcFixedByteLength;
   }

   Guard crit( &s_mutex );

   if ( 0 == _ulCalcFixedByteLength )
   {
      DCPPtrVectorType::const_iterator iter;
      for ( iter = _propertyOrder.begin();
            iter != _propertyOrder.end();
            ++iter )
      {
         if ( DCP::eDEP == ( *iter )->getType() )
         {
            unsigned long length = ( *iter )->getMaxLength();
            if ( static_cast< DataElementProperties * >( 
               ( *iter ) )->getStoredType() != DEP::BINARY ) 
            {  // Adjust by char size
               length = length * sizeof( I_CHAR );
            }
            _ulCalcFixedByteLength += length;
         }
      }
   }

   return _ulCalcFixedByteLength;
}


unsigned long DataPropertiesImpl::getMaxLength()
{
   if ( 0L == _maxLength )
   {
      DCPPtrVectorType::iterator iter;
      for ( iter = _propertyOrder.begin();
            iter != _propertyOrder.end();
            ++iter )
      {
         if ( (*iter)->getMaxLength() > _maxLength )
         {
            _maxLength = (*iter)->getMaxLength();
         }
      }
   }
   return _maxLength;
}


const DCP& DataPropertiesImpl::getProperty( const DString &propertyName ) const
{
   DCPPtrMapType::const_iterator iter = _propertyMap.find( propertyName );

   if ( _propertyMap.end() == iter )
   {
      DString msg( I_("prop=") );
      msg += propertyName;
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                      I_("DataPropertiesImpl::getProperty( const DString & )"),
                      DIDBRKR_PROPERTY_DOES_NOT_EXIST, msg.c_str() );
   }

   return *((*iter).second->pProperties);
}


const DCP& DataPropertiesImpl::getProperty( unsigned long index ) const
{
   if ( index >= _propertyCount )
   {
      DString msg( I_("index=") );
      msg.appendULong( index );
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                      I_("DataPropertiesImpl::getProperty( unsigned long )"),
                      DIDBRKR_PROPERTY_DOES_NOT_EXIST_AT_INDEX,
                      msg.c_str() );
   }

   return *(_propertyOrder[index]);
}


const DCP& DataPropertiesImpl::getPropertyByFieldIndex( long id ) const
{
   DCPPtrMapIndexType::const_iterator iter = _propertyIndex.find( id );

   if ( _propertyIndex.end() == iter )
   {
      DString msg( I_("prop=") );
      msg.appendLong( id );
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                      I_("DataPropertiesImpl::getProperty( const DString & )"),
                      DIDBRKR_PROPERTY_DOES_NOT_EXIST, msg.c_str() );
   }

   return *((*iter).second->pProperties);
}


void DataPropertiesImpl::getRedefines( const DString &oldName,
                                       string_vector &vecRedefines )
{
// DTWK thread safe?
   vecRedefines.erase( vecRedefines.begin(), vecRedefines.end() );

   RedefineMapType::iterator iter = m_redefineMap.find( oldName );
   if ( m_redefineMap.end() != iter )
   {
      string_vector::iterator iterVec = iter->second.begin();
      while ( iter->second.end() != iterVec )
      {
         vecRedefines.insert( vecRedefines.end(), *iterVec );
         ++iterVec;
      }
   }
}


unsigned long DataPropertiesImpl::getTotalMaxLength()
{
   unsigned long retVal = 0L;
   DCPPtrVectorType::iterator iter;
   for ( iter = _propertyOrder.begin();
         iter != _propertyOrder.end();
         ++iter )
   {
      retVal += (*iter)->getTotalMaxLength();
   }
   return retVal;
}


long DataPropertiesImpl::getTotalNumberOfLines() const
{
   DataComponentProperties *dcpPtr;
   DataProperties *dpPtr;
   long retVal = 0L;

   for ( DCPPtrVectorType::const_iterator iter = _propertyOrder.begin();
         iter != _propertyOrder.end(); ++iter )
   {
      dcpPtr = (*iter);
      if ( ( DCP::eDEP != dcpPtr->getType() ) && dcpPtr->isRepeatable() )
      {
         dpPtr = static_cast< DataProperties * >(dcpPtr);
         retVal += dpPtr->getTotalNumberOfLines();
         retVal += 2;
      }
      else
      {
         retVal++;
      }
   }
   return retVal;
}


long DataPropertiesImpl::getTotalNumberOfProperties() const
{
   DataComponentProperties *dcpPtr;
   DataProperties *dpPtr;
   long retVal = 0L;

   for ( DCPPtrVectorType::const_iterator iter = _propertyOrder.begin();
         iter != _propertyOrder.end(); ++iter )
   {
      dcpPtr = (*iter);
      if ( ( DCP::eDEP != dcpPtr->getType() ) && dcpPtr->isRepeatable() )
      {
         dpPtr = static_cast< DataProperties * >(dcpPtr);
         retVal += dpPtr->getTotalNumberOfProperties();
      }
      else
      {
         retVal++;
      }
   }
   return retVal;
}


DataProperties::EReturn DataPropertiesImpl::getValueFromBuffer(
   long id,
   DString &strOut,
   const unsigned char *rpDataBuffer,
   unsigned long formatFlags,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   ) const
{
   const PropertyInfo *rpInfo = _getPropertyInfoForDEP( id );
   if ( !rpInfo )
   {  // Element not found
      return DataProperties::NOT_FOUND;
   }
   // Guaranteed to be a DEP pointer at this point
   const DEP *rpDEP = static_cast< DEP *> ( rpInfo->pProperties );
   unsigned char *rpDataStart = (unsigned char *)( rpDataBuffer + rpInfo->lOffset );

   rpDEP->getValueFromBuffer( strOut, rpDataStart, formatFlags,
      rpClientLocale, i18nFormat );
   return DataProperties::SUCCESS;
}


DataProperties::EReturn DataPropertiesImpl::getValueFromBuffer(
   long id,
   unsigned char *binBuff,
   const unsigned char *rpDataBuffer,
   unsigned long buffLength,
   unsigned long &returnedLength
   ) const
{
   const PropertyInfo *rpInfo = _getPropertyInfoForDEP( id );
   if ( !rpInfo )
   {  // Element not found
      return DataProperties::NOT_FOUND;
   }
   // Guaranteed to be a DEP pointer at this point
   const DEP *rpDEP = static_cast< DEP *> ( rpInfo->pProperties );
   unsigned char *rpDataStart = (unsigned char *)( rpDataBuffer + rpInfo->lOffset );

   rpDEP->getValueFromBuffer( binBuff, rpDataStart, buffLength, returnedLength );
   return DataProperties::SUCCESS;
}


long DataPropertiesImpl::getVectorIndexFromName( const DString &name ) const
{
   DString strName( name );

   // If the properties name ends with "Repeat_Record", then it's probably
   // of the form <VW file name + "Repeat_Record">.  Eliminate what comes
   // before "Repeat_Record".  This is kind of a hack, but it's important
   // for performance.

   PropertyRepository *pProp = PropertyRepository::getInstance();

   if ( pProp->isCaseSensitive() )
   {
      if ( strName.substr( 0, _id.length() ) == _id )
      {
         strName = strName.substr( _id.length() );
      }
   }
   else
   {
      if ( 0 == i_stricmp( strName.substr( 0, _id.length() ).c_str(),
                           _id.c_str() ) )
      {
         strName = strName.substr( _id.length() );
      }
   }

   DCPPtrMapType::const_iterator iter = _propertyMap.find( strName );

   if ( _propertyMap.end() == iter )
   {
      return -1L;
   }
   else
   {
      return (*iter).second->lIndex;
   }
}


bool DataPropertiesImpl::isValid( const DString &idiString,
                                  const ClientLocale *pClientLocale ) const
{
   DString key;
   DString value;
   int length = idiString.length();
   int start = 0;
   DString::size_type separatorPosition;
   DString::size_type terminatorPosition;
   bool done = false;

   while( !done )
   {
      // Stop if at end-of-string
      if ( start >= length - 1 )
      {
         return true;
      }

      // Look for the next separator
      separatorPosition = idiString.find( SEPARATOR_CHAR, start );

      if ( -1 == separatorPosition )
      {
         // Stop if a separator was not found
         done = true;
      }
      else
      {
         // Extract the key & look for the next terminator
         key = strip( idiString.substr( start, separatorPosition - start ) );

         terminatorPosition = idiString.find( TERMINATOR_CHAR,
                                              separatorPosition + 1 );

         if ( -1 == terminatorPosition )
         {
            // Stop if a terminator was not found, but
            terminatorPosition = length;
            done = true;
         }

         // Extract the value & add it to the object
         value = strip( idiString.substr( separatorPosition + 1,
                        terminatorPosition - separatorPosition - 1 ) );

         if ( exists( key ) )
         {
            if ( !getProperty( key ).isValid( value, pClientLocale ) )
            {
               return false;
            }
         }
         else
         {
            return false;
         }
         start = terminatorPosition + 1;
      }
   }
   return true;
}


DataProperties::EReturn DataPropertiesImpl::setValueInBuffer(
   long id,
   const DString &valueIn,
   unsigned char *rpDataBuffer,
   const ClientLocale *rpClientLocale,
   bool displayFormat,
   const DString &i18nFormat
   ) const
{
   const PropertyInfo *rpInfo = _getPropertyInfoForDEP( id );
   if ( !rpInfo )
   {  // Element not found
      return DataProperties::NOT_FOUND;
   }
   
   // Guaranteed to be a DEP pointer at this point
   const DEP *rpDEP = static_cast< DEP *> ( rpInfo->pProperties );
   unsigned char *rpDataStart = rpDataBuffer + rpInfo->lOffset;

   if ( rpDEP->setValueInBuffer( valueIn, rpDataStart, rpClientLocale,
      displayFormat, i18nFormat ) )
   {
      return DataProperties::SUCCESS;
   }
   else
   {
      return DataProperties::FAILURE;
   }
}


DataProperties::EReturn DataPropertiesImpl::setValueInBuffer(
   long id,
   unsigned char *binBuff,
   unsigned char *rpDataBuffer,
   unsigned long buffLength,
   unsigned long &returnedLength
   ) const
{
   const PropertyInfo *rpInfo = _getPropertyInfoForDEP( id );
   if ( !rpInfo )
   {  // Element not found
      return DataProperties::NOT_FOUND;
   }
   
   // Guaranteed to be a DEP pointer at this point
   const DEP *rpDEP = static_cast< DEP *> ( rpInfo->pProperties );
   unsigned char *rpDataStart = rpDataBuffer + rpInfo->lOffset;

   if ( rpDEP->setValueInBuffer( binBuff, rpDataStart, buffLength, 
      returnedLength ) )
   {
      return DataProperties::SUCCESS;
   }
   else
   {
      return DataProperties::FAILURE;
   }
}


DataProperties::EReturn DataPropertiesImpl::setValueInBufferFromHost(
   long id,
   DString &valueIn,
   unsigned char *rpDataBuffer
   ) const
{
   const PropertyInfo *rpInfo = _getPropertyInfoForDEP( id );
   if ( !rpInfo )
   {  // Element not found
      return DataProperties::NOT_FOUND;
   }
   
   // Guaranteed to be a DEP pointer at this point
   const DEP *rpDEP = static_cast< DEP *> ( rpInfo->pProperties );
   unsigned char *rpDataStart = rpDataBuffer + rpInfo->lOffset;

   if ( rpDEP->setValueInBufferFromHost( valueIn, rpDataStart ) )
   {
      return DataProperties::SUCCESS;
   }
   else
   {
      return DataProperties::FAILURE;
   }
}


void DataPropertiesImpl::streamOutComponents( i_ostream &stream,
                                              unsigned long &counter,
                                              unsigned long &lineNum,
                                              const DString &viewName,
                                              const DString &propName )
{
   DCP *dcpPtr;
   DEP *propPtr;
   DP *dataPropPtr;
   unsigned long numProps = getTotalNumberOfProperties();
   I_CHAR typeChar, tempBuff[13];

   if ( isRepeatable() )
   {
      stream.setf( i_ios::left );
      stream.fill( ' ' );
      DString begPropName = I_("Begin_") + propName;
      stream << viewName << std::setw( ELEMENTNAME_SIZE ) <<
         begPropName << I_("Y");
      stream.unsetf( i_ios::left );
      stream.fill( '0' );
      i_sprintf( tempBuff, I_("00000000%04lu"), lineNum );
      stream << tempBuff << std::endl;
      ++lineNum;
   }
   for ( unsigned long thisCounter = 0; thisCounter < numProps;
         ++thisCounter, ++lineNum )
   {
      dcpPtr = _propertyOrder[ thisCounter ];
      if ( DCP::eDEP == dcpPtr->getType() )
      {
         propPtr = static_cast< DEP * >(dcpPtr);
         switch ( propPtr->getStoredType() )
         {
            case DEP::BINARY:
               typeChar = 'B';
               break;
            case DEP::STRING:
               typeChar = 'X';
               break;
            case DEP::DECIMAL:
               typeChar = 'S';
               break;
            case DEP::INTEGER:
               typeChar = '9';
               break;
            default:
               typeChar = ' ';
               break;
         }

         stream.setf( i_ios::left );
         stream.fill( ' ' );
         stream << viewName
                << std::setw( ELEMENTNAME_SIZE ) << propPtr->getName();
         stream << DString( 1, typeChar );
         stream.unsetf( i_ios::left );
         stream.fill( '0' );
         DString strMaxLength( asString( propPtr->getMaxLength()) );
         i_sprintf( tempBuff, I_("%04.4s%04lu%04lu"), strMaxLength,
                  propPtr->getDecimalPlace(),
                  lineNum );
         stream << tempBuff;

         if ( propPtr->getMaxLength() > 9999 )
         {
            stream << I_("DSTLENGTH=") << propPtr->getMaxLength() << I_(";");
         }
         if ( propPtr->hasSubstitutes() )
         {
            DString subValues;
            propPtr->getAllSubstituteValues( subValues );
            stream << subValues.c_str();
            stream << std::endl;
         }
         else if ( propPtr->hasMask() )
         {
            stream << I_("DSTMASK=") << propPtr->getMask().c_str();
            stream << std::endl;
         }
         else
         {
            stream << std::endl;
         }
      }
      else
      {
         dataPropPtr = static_cast< DP * >(dcpPtr);
         if ( dataPropPtr->isRepeatable() )
         {
            dataPropPtr->streamOutComponents( stream, counter, lineNum,
               viewName, getPropertyElementName( thisCounter ) );
         }
         else
         {
            typeChar = ' ';
            stream.setf( i_ios::left );
            stream.fill( ' ' );
            stream << viewName
                   << std::setw( ELEMENTNAME_SIZE )
                   << dataPropPtr->getName();
            stream << DString( 1, typeChar );
            stream.unsetf( i_ios::left );
            stream.fill( '0' );
            i_sprintf( tempBuff, I_("%04lu%04lu%04lu"), 0,
                     0,
                     lineNum );
            stream << tempBuff;

         }
      }
   }
   if ( isRepeatable() )
   {
      stream.setf( i_ios::left );
      stream.fill( ' ' );
      DString endPropName( I_("End_") );
      endPropName += propName;
      stream << viewName.c_str()
             << std::setw( ELEMENTNAME_SIZE ) << endPropName.c_str() << I_("Y");
      stream.unsetf( i_ios::left );
      stream.fill( '0' );
      i_sprintf( tempBuff, I_("00000000%04lu"), lineNum );
      stream << tempBuff << std::endl;
   }
}


void DataPropertiesImpl::unauthorizedSetValueInBuffer(
   long id,
   const DString &valueIn,
   unsigned char *rpDataBuffer
   ) const
{
   const PropertyInfo *rpInfo = _getPropertyInfoForDEP( id );
   if ( rpInfo )
   {  // Element must be found
      // Guaranteed to be a DEP pointer at this point
      const DEP *rpDEP = static_cast< DEP *> ( rpInfo->pProperties );
      unsigned char *rpDataStart = rpDataBuffer + rpInfo->lOffset;

      rpDEP->unauthorizedSetValueInBuffer( valueIn, rpDataStart );
   }
}


i_ostream &operator<< ( i_ostream &stream,
                      const DataPropertiesImpl &propertiesImpl )
{
   MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME,
                     I_("DataPropertiesImpl::operator<<") );
   DString viewName( propertiesImpl.getName() );
   DString strRR( DEFAULT_REPEAT_RECORD );
   if ( viewName.find( '.' ) != -1 )
   {
      viewName.getImp().resize( viewName.find('.'));
   }
   unsigned long numTotalElements = propertiesImpl._propertyOrder.size();
   I_CHAR typeChar;
   DEP *propPtr;
   DP *dataPropPtr;
   DCP *dcpPtr;
   I_CHAR tempBuff[13];

   numTotalElements = propertiesImpl.getPropertyCount();
   padRight( viewName.getImp(), VIEWNAME_SIZE );

   stream.setf( i_ios::left );
   stream.fill( ' ' );
   stream << viewName.c_str()
          << std::setw( ELEMENTNAME_SIZE )
          << I_("ZZZZ") << DString( 1, ' ' );
   stream.unsetf( i_ios::left );
   stream.fill( '0' );
   i_sprintf( tempBuff, I_("%04lu"), propertiesImpl.getTotalNumberOfLines() );
   stream << std::setw( 4 ) << tempBuff << I_("00000000") << std::endl;

   for ( unsigned long counter = 0, lineNum = 1;
         counter < numTotalElements;
         ++counter, ++lineNum )
   {
      dcpPtr = propertiesImpl._propertyOrder[ counter ];
      if ( DCP::eDEP == dcpPtr->getType() )
      {
         propPtr = static_cast<DEP *>(dcpPtr);
         dataPropPtr = NULL;
      }
      else
      {
         propPtr = NULL;
         dataPropPtr = static_cast<DP *>(dcpPtr);
      }

      if ( !propPtr && !dataPropPtr )
      {
         throw EXCEPTIONFROMFILE( DIDBRKR_INVALID_PROPERTY_POINTER );
      }

      if ( dataPropPtr )
      {
         if ( dataPropPtr->isRepeatable() )
         {
            dataPropPtr->streamOutComponents( stream, counter, lineNum,
               viewName, propertiesImpl.getPropertyElementName( counter ) );
         }
         else
         {
            typeChar = ' ';
            stream.setf( i_ios::left );
            stream.fill( ' ' );
            stream << viewName.c_str()
                   << std::setw( ELEMENTNAME_SIZE )
                   << dataPropPtr->getName().c_str();
            stream << DString( 1, typeChar );
            stream.unsetf( i_ios::left );
            stream.fill( '0' );
            i_sprintf( tempBuff, I_("%04lu%04lu%04lu"), 0,
                     0,
                     lineNum );
            stream << tempBuff;

         }
      }
      else // if ( propPtr )
      {
         switch ( propPtr->getStoredType() )
         {
            case DEP::BINARY:
               typeChar = 'B';
               break;
            case DEP::STRING:
               typeChar = 'X';
               break;
            case DEP::DECIMAL:
               typeChar = 'S';
               break;
            case DEP::INTEGER:
               typeChar = '9';
               break;
            default:
               typeChar = ' ';
               break;
         }

         stream.setf( i_ios::left );
         stream.fill( ' ' );
         stream << viewName.c_str()
                << std::setw( ELEMENTNAME_SIZE ) << propPtr->getName().c_str();
         stream << DString( 1, typeChar );
         stream.unsetf( i_ios::left );
         stream.fill( '0' );
         DString strMaxLength( asString( propPtr->getMaxLength()) );
         i_sprintf( tempBuff, I_("%04.4s%04lu%04lu"), strMaxLength.c_str(),
                  propPtr->getDecimalPlace(),
                  lineNum );
         stream << tempBuff;

         if ( propPtr->getMaxLength() > 9999 )
         {
            stream << I_("DSTLENGTH=") << propPtr->getMaxLength() << I_(";");
         }
         if ( propPtr->hasSubstitutes() )
         {
            DString subValues;
            propPtr->getAllSubstituteValues( subValues );
            stream << subValues.c_str();
            stream << std::endl;
         }
         else if ( propPtr->hasMask() )
         {
            stream << I_("DSTMASK=") << propPtr->getMask().c_str();
            stream << std::endl;
         }
         else
         {
            stream << std::endl;
         }
      }
   }
   return stream;
}


//******************************************************************************
//              Protected Methods
//******************************************************************************


//******************************************************************************
//              Private Methods
//******************************************************************************

void DataPropertiesImpl::_calculateOffsets()
{
   DCPPtrVectorType::iterator iterVec = _propertyOrder.begin();
   long lOffset = 0;
   long length;

   while ( _propertyOrder.end() != iterVec )
   {
      PropertyInfo *pPI = _propertyMap[ ( *iterVec )->getName() ];

      if ( pPI && pPI->pProperties->getType() == DCP::eDEP )
      {
         const DEP *rpDEP = static_cast< DEP *> ( pPI->pProperties );
         pPI->lOffset = lOffset;
         length = rpDEP->getMaxLength();
         if ( rpDEP->getStoredType() != DEP::BINARY )
         {  // Offset adjust for char size
            length *= sizeof( I_CHAR );
         }
         lOffset += length;
      }

      ++iterVec;
   }
}


DPI::DCPPtrVectorType::iterator DPI::findPropertyInVector(
                                             DCPPtrVectorType &propVector,
                                             DataComponentProperties *propPtr ) const
{
   DCPPtrVectorType::iterator findIter, endIter = propVector.end();
   for ( findIter = propVector.begin();
         findIter != endIter;
         ++findIter )
   {
      if ( propPtr == (*findIter) )
      {
         return findIter;
      }
   }
   return endIter;
}


//******************************************************************************
//
// ^PRIVATE METHOD : getPropertyElementName
//
// ^DESCRIPTION    : Returns the name of the property at the givent index in the
//                   _propertyMap.
//
// ^PARAMETERS     :
//    ^^ unsigned long index - (in) index of the property to retrieve the name
//                   for.
//
// ^RETURNS        : Returns a string containing the name of the property
//                   element.
//
// ^THROWS         : string& - if the index is out of range
//
//******************************************************************************

const DString &DataPropertiesImpl::getPropertyElementName( unsigned long index ) const
{
   if ( index >= _propertyCount )
   {
      DString msg( I_("index=") );
      msg.appendULong( index );
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                      I_("DataPropertiesImpl::getPropertyElementName"),
                      DIDBRKR_PROPERTY_DOES_NOT_EXIST_AT_INDEX,
                      msg.c_str() );
   }

   DCP *dcpPtr = _propertyOrder[index];

   const DString &strId = dcpPtr->getName();

   if ( dcpPtr->isRepeatable() )
   {
      if ( _id == strId.substr( 0, _id.length()))
      {
         DCPPtrMapType::const_iterator iter =
            _propertyMap.find( strId.substr( _id.length()));

         if ( iter != _propertyMap.end() )
         {
            return (*iter).first;
         }
         else
         {
            return dcpPtr->getName();
         }
      }
      else
      {
         return dcpPtr->getName();
      }
   }
   else
      return dcpPtr->getName();
}


//******************************************************************************
//
// ^PRIVATE METHOD : _getPropertyInfoForDEP
//
// ^DESCRIPTION    : Returns the PropertyInfo for given id.
//
// ^PARAMETERS     :
//    ^^ unsigned long id - id of the property to retrieve info for.
//
// ^RETURNS        : pointer to PropertyInfo or null if not found
//
// ^THROWS         : condition if not DataElementProperty
//
//******************************************************************************

const DataPropertiesImpl::PropertyInfo *DataPropertiesImpl::_getPropertyInfoForDEP(
   long id ) const
{
   DCPPtrMapIndexType::const_iterator iter = _propertyIndex.find( id );

   if ( _propertyIndex.end() != iter )
   {  // Make sure DEP
      if ( DCP::eDEP == (*iter).second->pProperties->getType() )
      {
         return (*iter).second;
      }
      else
      {  // Really a mismatch instead of not exist
         DString msg( I_("prop=") );
         msg.appendLong( id );
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                   I_("DataPropertiesImpl::getPropertyInfoForDEP( long )"),
                   DIDBRKR_PROPERTY_DOES_NOT_EXIST, msg.c_str() );
      }
   }
   return NULL;
}


/*
long DataPropertiesImpl::getOffset( unsigned long ulId ) const
{
   DCPPtrMapIndexType::iterator iter = _propertyIndex.find( ulId );
   if ( _propertyIndex.end() != iter )
   {
      return ( *iter ).second->lOffset;
   }

   DString msg( I_( "comp=" ) );
   msg.appendLong( ulId );
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                     I_( "DataPropertiesImpl::getOffset" ),
                     DIDBRKR_ELEMENT_NOT_FOUND, msg.c_str() );
}
*/

void DataPropertiesImpl::_recalculateVectorIndexes()
{
   DCPPtrVectorType::iterator iterVec = _propertyOrder.begin();
   long lIndex = 0;

   while ( _propertyOrder.end() != iterVec )
   {
      PropertyInfo *pPI = _propertyMap[ ( *iterVec )->getName() ];
      pPI->lIndex = lIndex;

      ++lIndex;
      ++iterVec;
   }
}


bool DataPropertiesImpl::_redefineProperties( const DString& dstrField,
                                              DataPropertiesImpl *pDPIAdd )
{
   // The only thing that should be calling this method is Data::_setRedefine()!

// DTWK thread safe?

   PropertyRepository *pPropRep = PropertyRepository::getInstance();

   DCPPtrVectorType::iterator iterNewFields = pDPIAdd->_propertyOrder.begin();
   while ( pDPIAdd->_propertyOrder.end() != iterNewFields )
   {
      // Make sure that none of the fields that we are adding already
      // exist in the properties.
      if ( exists( ( *iterNewFields )->getId() ) )
      {
         // "Element %element% from redefine %redefine% already exists in the
         // Data object."
         DString msg( I_( "element=" ) );
         msg += ( *iterNewFields )->getName();
         msg += I_( ";redefine=" );
         msg += pDPIAdd->getName();
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_( "DataPropertiesImpl::_redefineProperties" ),
                           DIDBRKR_REDEFINE_HAS_DUPLICATE,
                           msg.c_str() );
      }

      // Make sure that no repeatable elements are in the replacements!
      if ( ( *iterNewFields )->isRepeatable() )
      {
         // Error redefining field. Redefining dataset %dataset% contains
         // a repeatable component, %comp%.
         DString msg( I_( "dataset=" ) );
         msg += pDPIAdd->getName();
         msg += I_( ";comp=" );
         msg += ( *iterNewFields )->getName();
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_( "DataPropertiesImpl::_redefineProperties" ),
                           DIDBRKR_REDEFINE_REPEATS_NOT_ALLOWED,
                           msg.c_str() );
      }

      ++iterNewFields;
   }

   // Get the set of properties that we will be replacing
   RedefineMapType::iterator iter = m_redefineMap.find( dstrField );
   if ( m_redefineMap.end() == iter )
   {
      // If it's empty, then this element/field has never been redefined
      // Initialize the set with the field
      string_vector vecFieldsToReplace;
      vecFieldsToReplace.insert( vecFieldsToReplace.begin(), dstrField );
      m_redefineMap[ dstrField ] = vecFieldsToReplace;
   }

   iter = m_redefineMap.find( dstrField );
   string_vector &vecFieldsToReplace = ( *iter ).second;

   // Make sure the vector is not reallocated in the middle of the insertions
   // This should ensure that our iterator is still valid even though we are
   // adding elements.
   _propertyOrder.reserve( _propertyOrder.size() +
                              pDPIAdd->_propertyOrder.size() +
                              vecFieldsToReplace.size() );

   // Find the first element to remove.  We will add all new elements
   // just before this one (to ensure property order)
   const DString &dstrFirstRemove =  *( vecFieldsToReplace.begin() );
   DCPPtrMapType::iterator iterAddLocation = _propertyMap.find( dstrFirstRemove );

   if ( _propertyMap.end() == iterAddLocation )
   {
      return false;
   }

   // Save of a pointer to the first element that we will be removing
   // The PropertyInfo contains an index into _propertyOrder vector
   PropertyInfo *pPIFirstToRemove = iterAddLocation->second;

   // Add in the new elements just before the ones we are about to remove
   iterNewFields = pDPIAdd->_propertyOrder.end();
   while ( pDPIAdd->_propertyOrder.begin() != iterNewFields )
   {
      --iterNewFields;
      PropertyInfo *pPICurrent =
         new PropertyInfo(
                    *( pDPIAdd->_propertyMap[ ( *iterNewFields )->getName() ] ) );

      _propertyOrder.insert( _propertyOrder.begin() + pPIFirstToRemove->lIndex,
                             pPICurrent->pProperties );
      _propertyMap[ ( *iterNewFields )->getName() ] = pPICurrent;

      _propertyIndex[
         pPropRep->getFieldIdFromName( ( *iterNewFields )->getName() ) ] =
            pPICurrent;
      ++_propertyCount;
   }

   // The starting index of the elements we want to remove is now it's original
   // index + the number of elements we just inserted
   long lDeleteIndex = pPIFirstToRemove->lIndex + pDPIAdd->_propertyCount;

   // Remove the property entries that are being replaced
   for ( unsigned int iCount = 0; iCount < vecFieldsToReplace.size(); ++iCount )
   {
      DataComponentProperties *pDCPRemove = _propertyOrder[ lDeleteIndex ];
      _propertyOrder.erase( _propertyOrder.begin() + lDeleteIndex );
      _propertyMap.erase( pDCPRemove->getName() );
      _propertyIndex.erase(
                          pPropRep->getFieldIdFromName( pDCPRemove->getName() ) );
      --_propertyCount;
   }

   // Recalculate because our insertions/removals may have changed it
   getMaxLength();

   // Update our map of sets with the latest redefine fields. This is made
   // complicated by the idea of redefines within redefines
   _updateRedefineMap( dstrField, pDPIAdd );

   // Recalculate because our insertions/removals may have changed it
   _recalculateVectorIndexes();

   return true;
}


bool DataPropertiesImpl::_redefineProperties( const DString& dstrField )

{
   // The only thing that should be calling this method is Data::_setRedefine()!

// DTWK thread safe?

   PropertyRepository *pPropRep = PropertyRepository::getInstance();

   // Make sure that none of the fields that we are adding already
   // exist in the properties.
   if ( exists( dstrField ) )
   {
      // "Element %element% from redefine %redefine% already exists in the
      // Data object."
      DString msg( I_( "element=" ) );
      msg += dstrField.c_str();
      msg += I_( ";redefine=" );
      msg += dstrField.c_str();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_( "DataPropertiesImpl::_redefineProperties" ),
                        DIDBRKR_REDEFINE_HAS_DUPLICATE,
                        msg.c_str() );
   }

   // Get the set of properties that we will be replacing
   RedefineMapType::iterator iter = m_redefineMap.find( dstrField );
   if ( m_redefineMap.end() == iter )
   {
      // If it's empty, then this element/field has never been redefined
      // Initialize the set with the field
      string_vector vecFieldsToReplace;
      vecFieldsToReplace.insert( vecFieldsToReplace.begin(), dstrField );
      m_redefineMap[ dstrField ] = vecFieldsToReplace;
   }

   iter = m_redefineMap.find( dstrField );
   string_vector &vecFieldsToReplace = ( *iter ).second;

   // Make sure the vector is not reallocated in the middle of the insertions
   // This should ensure that our iterator is still valid even though we are
   // adding elements.
   _propertyOrder.reserve( _propertyOrder.size() + 1 +
                              vecFieldsToReplace.size() );

   // Find the first element to remove.  We will add all new elements
   // just before this one (to ensure property order)
   const DString &dstrFirstRemove =  *( vecFieldsToReplace.begin() );
   DCPPtrMapType::iterator iterAddLocation = _propertyMap.find( dstrFirstRemove );

   if ( _propertyMap.end() == iterAddLocation )
   {
// DTWK kick with an error
      return false;
   }

   // Save of a pointer to the first element that we will be removing
   // The PropertyInfo contains an index into _propertyOrder vector
   PropertyInfo *pPIFirstToRemove = iterAddLocation->second;

   // Get a copy of the properties for an un-redefined version of this data object
// DT17817
   DataPropertiesImpl *pDPIOrig =
      pPropRep->getDataSet( _id, ClientLocale::getDefaultClientLocale() );

   // Add in the new elements just before the ones we are about to remove
   PropertyInfo *pPICurrent =
                   new PropertyInfo( *( pDPIOrig->_propertyMap[ dstrField ] ) );

   _propertyOrder.insert( _propertyOrder.begin() + pPIFirstToRemove->lIndex,
                          pPICurrent->pProperties );
   _propertyMap[ dstrField ] = pPICurrent;

   _propertyIndex[
      pPropRep->getFieldIdFromName( dstrField ) ] =
         pPICurrent;
   ++_propertyCount;

   // The starting index of the elements we want to remove is now it's original
   // index + the number of elements we just inserted
   long lDeleteIndex = pPIFirstToRemove->lIndex + 1;

   // Remove the property entries that are being replaced
   for ( unsigned int iCount = 0; iCount < vecFieldsToReplace.size(); ++iCount )
   {
      DataComponentProperties *pDCPRemove = _propertyOrder[ lDeleteIndex ];
      _propertyOrder.erase( _propertyOrder.begin() + lDeleteIndex );
      _propertyMap.erase( pDCPRemove->getName() );
      _propertyIndex.erase(
                          pPropRep->getFieldIdFromName( pDCPRemove->getName() ) );
      --_propertyCount;
   }

   // Recalculate because our insertions/removals may have changed it
   getMaxLength();

   // Update our map of sets with the latest redefine fields. This is made
   // complicated by the idea of redefines within redefines
   _updateRedefineMap( dstrField, 0 );

   // Recalculate because our insertions/removals may have changed it
   _recalculateVectorIndexes();

   return true;
}


void DataPropertiesImpl::_replaceVectorSubSequence( string_vector &vecMain,
                                                    string_vector &vecRemove,
                                                    string_vector &vecAdd )
{
// DTWK what happens if one of the sets is empty?

   string_vector::const_iterator iterRemove = vecRemove.begin();
   string_vector::iterator iterVec =
           findInContainer< string_vector, DString >( vecMain, *iterRemove );

   bool fFound = true;

   while ( ( vecRemove.end() == iterRemove  ) && fFound )
   {
      if ( vecMain.end() == iterVec )
      {
         fFound = false;
      }
      else if ( ( *iterRemove ) != ( *iterVec ) )
      {
         fFound = false;
      }
      else
      {
         ++iterRemove;
         ++iterVec;
      }
   }

   if ( fFound )
   {
      // Make sure we have enough space so that our iterators don't get
      // invalidated by our adds/deletes.
      vecMain.reserve( vecMain.size() + vecAdd.size() + vecRemove.size() );

      iterRemove = vecRemove.begin();
      iterVec = findInContainer< string_vector, DString >( vecMain, *iterRemove );

      // Add in reverse order because the order is reversed by the add loop
      string_vector::iterator iterAdd = vecAdd.end();
      while ( vecAdd.begin() != iterAdd )
      {
         --iterAdd;
         vecMain.insert( iterVec, *iterAdd );
      }

      // Remove the elements to be replaced
      vecMain.erase( iterVec + vecAdd.size(),
                     iterVec + vecAdd.size() + vecRemove.size() );
   }
}


void DataPropertiesImpl::_updateRedefineMap( const DString &dstrField,
                                             DataPropertiesImpl *pDPIAdd )
{
   // Assume that dstrField is a valid redefine (this is checked in
   // _redefineProperties, which is our only entry point)

   // Get the set of properties that we will be replacing
   RedefineMapType::iterator iter = m_redefineMap.find( dstrField );
   if ( m_redefineMap.end() == iter )
   {
// DTWK kick with a severe error?
      return;
   }
   string_vector vecFieldsToReplace = iter->second;

   // Make a set of the replacements. This is either all the fields in pDPIAdd,
   // or just dstrField if pDPIAdd is null (this is the case where we are
   // resetting the redefine back to its original state.
   string_vector vecReplacements;
   if ( 0 == pDPIAdd )
   {
      vecReplacements.insert( vecReplacements.begin(), dstrField );
   }
   else
   {
      DCPPtrVectorType::iterator iterNewFields = pDPIAdd->_propertyOrder.begin();
      while ( pDPIAdd->_propertyOrder.end() != iterNewFields )
      {
         vecReplacements.insert( vecReplacements.end(),
                                 ( *iterNewFields )->getName() );
         ++iterNewFields;
      }
   }

   // If our redefinable field is a member of other redefinable fields,
   // we will need to replace it in those other fields too.
   iter = m_redefineMap.begin();
   while ( m_redefineMap.end() != iter )
   {
      _replaceVectorSubSequence( iter->second, vecFieldsToReplace,
                                 vecReplacements );
      ++iter;
   }

   // Spin through all sets of redefines and remove any elements that are in the
   // the set of fields to replace.  This makes the (safe) assumption that a
   // properties object cannot have more than one field the same name.
   iter = m_redefineMap.begin();
   while ( m_redefineMap.end() != iter )
   {
      string_vector::iterator iterRemoveFields = vecFieldsToReplace.begin();
      while ( vecFieldsToReplace.end() != iterRemoveFields )
      {
         string_vector::iterator iterRemoveField =
            findInContainer< string_vector, DString >( iter->second, *iterRemoveFields );

         if ( iter->second.end() != iterRemoveField )
         {
            iter->second.erase( iterRemoveField );
         }

         ++iterRemoveFields;
      }

      ++iter;
   }
}


//******************************************************************************
//              Static Methods
//******************************************************************************


DataPropertiesImpl *DataPropertiesImpl::getInstancePointer(
   const DString &name,
   const ClientLocale &clientLocale,
   bool isRepeatable )
{
   DataPropertiesImpl *returnPointer = NULL;
   PropertyRepository *pPropRep = PropertyRepository::getInstance();
   if ( pPropRep )
   {
      returnPointer = pPropRep->getDataSet( name, clientLocale );
   }
   if ( !returnPointer )
   {  // Try to get from file
      returnPointer = new DataPropertiesImpl( name, isRepeatable );
      if ( !returnPointer )
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME,
                        I_("DataPropertiesImpl::getInstancePointer"),
                        BASE_ALLOC_FAIL );
      }
   }
   return returnPointer;
}


DataPropertiesImpl *DataPropertiesImpl::getInstancePointer(
   unsigned long id,
   const ClientLocale &clientLocale,
   bool isRepeatable )
{
   DataPropertiesImpl *returnPointer = NULL;
   PropertyRepository *pPropRep = PropertyRepository::getInstance();
   if ( pPropRep )
   {
      return pPropRep->getDataSet( id, clientLocale );
   }
   return NULL;
}


void DataPropertiesImpl::dumpPIMap() const
{
   for ( DCPPtrMapType::const_iterator iter = _propertyMap.begin(); iter != _propertyMap.end(); ++iter )
   {
      i_cout << I_( "name: " ) << (*iter).first << std::endl << I_( "index: " ) << (*iter).second->lIndex << std::endl;
      i_cout << I_( "props ptr: " ) << (*iter).second->pProperties << std::endl << I_( "props name: " ) << (*iter).second->pProperties->getName() << std::endl;
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/datapropertiesimpl.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:26   kovacsro
// Initial revision.
// 
//    Rev 1.31   May 18 2001 15:08:08   dt24433
// Updated implementation for binary field support.
// Added setValueInBufferFromHost.
// Switched to Guard\CriticalSectionLock from CriticalSection\MutexSemaphore.
// 
//    Rev 1.30   Mar 22 2001 16:32:40   dt24433
//  
// 
//    Rev 1.29   Mar 09 2001 11:24:34   dt24433
//  
// 
//    Rev 1.28   Mar 02 2001 14:08:36   dt24433
//  
// 
//    Rev 1.27   Jan 22 2001 12:01:48   dt24433
// Added getFixedByteLength.  getFixedLength will not work with binary data.
// 
//    Rev 1.26   Jan 19 2001 17:11:52   DT11159
// oops
//
//    Rev 1.25   Jan 19 2001 16:52:58   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.24   Jan 04 2001 16:46:52   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.23   Nov 22 2000 07:05:06   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.22   Jun 08 2000 11:49:48   dtwk
// Add support for case-insensitivity
//
//    Rev 1.21   May 31 2000 09:33:04   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.20   Apr 10 2000 11:47:04   dtwk
// Updates for thread-safety
//
//    Rev 1.19   Apr 04 2000 10:01:54   dtwk
// Updates for thread safety
//
//    Rev 1.18   Nov 29 1999 07:31:46   dtwk
// Add support for redefines
//
//    Rev 1.17   Oct 06 1999 11:35:38   DCYK
// Add support for redefines.
//
//
//    Rev 1.16   Oct 04 1999 15:25:04   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.15   Sep 02 1999 13:12:44   DCYK
// Add addLocale function, to add a locale on
// an existing properties object.
//
//
//    Rev 1.14   Aug 20 1999 15:35:40   DCYK
// Added locale parameter to isValid, added isI18NValid function.
//
//
//    Rev 1.13   Aug 06 1999 14:21:18   DCYK
// Performance improvements.
//
//
//    Rev 1.12   Jul 29 1999 10:33:14   DCYK
// Minor performance improvements.
//
//    Rev 1.11   May 28 1999 14:53:38   DCYK
// Fix so Data objects return numerical id.
//
//
//    Rev 1.10   May 14 1999 11:29:42   DTWK
// Add ability to access Data through Repository Group/Field Id's
//
//    Rev 1.9   May 05 1999 13:11:34   DCYK
// Change getVectorIndex calls to
// getVectorIndexFromName to allow
// re-use of element properties.
//
//
//    Rev 1.8   Apr 30 1999 14:52:04   DCYK
// Clear conditions if read from repository
// fails.
//
//
//    Rev 1.7   Apr 20 1999 16:49:36   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.6   09 Mar 1999 12:50:44   DT14177
// Unicode-izing
//
//    Rev 1.5   Mar 05 1999 10:25:42   DCYK
// Changes for I18N.
//
//
//    Rev 1.4   Feb 11 1999 15:04:18   DCYK
// Add support for binary elements.
//
//
//    Rev 1.3   Jan 28 1999 14:03:56   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Sep 16 1998 10:19:36   dcyk
// Added condition for extra lines in properties
// file.
//
//
//    Rev 1.1   Aug 27 1998 16:53:04   dcyk
// Have functions check for entire repeat
// record name, not just "Repeat_Record".
// Was causing problems for PlanTrac.
//
//
//    Rev 1.0   29 Jul 1998 20:31:00   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.13   Jul 22 1998 10:12:46   dcyk
// Performance improvements
// from Paul D.
//
//
//    Rev 1.12   Jul 08 1998 10:04:56   dcyk
// Performance improvements.
//
//
//    Rev 1.11   Jun 18 1998 11:11:52   dcyk
// Remove tracing.
//
//
//    Rev 1.10   Feb 12 1998 09:52:32   dcyk
// Added condition for duplicate elements
// in a properties file.
//
//
//    Rev 1.9   Nov 10 1997 14:47:04   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.8   26 Sep 1997 15:45:52   dmum
// Fixed bug where the data component property representing the
// collection of repeat records did not have an index assigned.
//
//
//    Rev 1.7   23 Sep 1997 16:29:22   dcyk
// Add support for vector indices, so Data objects
// can store elements in a vector, not a map.
//
//
//    Rev 1.6   17 Sep 1997 14:15:30   dcyk
// Make changes for registry change.
//
//
//    Rev 1.5   05 Sep 1997 07:56:54   dcyk
// Removed most calls to MAKEFRAME, use
// TRACE_METHOD & THROWFROMFILE
// instead.
//
//
//    Rev 1.4   29 Aug 1997 14:58:18   dcyk
// Changed calls to registry class.
//
//
//    Rev 1.3   07 Aug 1997 15:05:38   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
// Use registry for .vw file locations.
//
//
//    Rev 1.2   24 Jul 1997 09:34:26   dcyk
// Use new tracing stuff.
//
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
