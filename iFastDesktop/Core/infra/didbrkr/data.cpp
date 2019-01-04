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
// ^FILE   : Data.cpp
// ^AUTHOR : Tony Stryker
// ^DATE   : 10/24/96
//
// ----------------------------------------------------------
//
// ^CLASS : Data
//
// ^INHERITS FROM : DataComponent
//
// ^MEMBER VARIABLES :
//    ^NAME :        _dataIndexMap
//    ^TYPE :        map< unsigned long, DataComponent*, less< unsigned long > >
//    ^DESCRIPTION : Map structure containing the id and value pairs for
//                   appended elements and nested data and repeat objects.

//    ^NAME :        _fieldNameMap
//    ^TYPE :        map< string, unsigned long, less< string > >
//    ^DESCRIPTION : Map structure containing the name and value pairs to map names
//                   to ids.
//
//    ^NAME :        _repeatData
//    ^TYPE :        vector< Data*, allocator >
//    ^DESCRIPTION : Vector of Data objects that are the repeat records for this
//                   Data object.
//
//    ^NAME :        _dataStreamBuffer
//    ^TYPE :        char *
//    ^DESCRIPTION : Array of characters, passed to the DataElements in this
//                   Data object, used when streaming in values.
//
// ^CODING COMMENTS  :
//
// A Data object is meant to contain a block of data.  This can be made up of
// DataElements, or in the case of repeat data, an array of Data objects.  The
// Data class is part of a "Composite" pattern, which also includes the
// DataComponent and DataElement classes.
//
// The properties of this Data object are described in a DataProperties object.
//
// The Data and appended DataElement objects contained in this Data object, are
// stored in the _dataIndexMap structure.  This is a typedef'ed map, whose
// elements are pairs of id keys and pointers to DataComponent objects.
// _fieldNameMap is a map of name and ids for each appended DataElements.
//
// For data with repeats, the Data object has a Data object in it's
// _dataIndexMap, called "Repeat_Record", and that Data object contains the
// different repeat records.  For data with multiple repeat areas, the Data
// objects will have names different from "Repeat_Record".
//
// The _dataStreamBuffer member variable is an array of characters, with enough
// space allocated for the largest DataElement in this Data object.  The array
// is passed to DataElement's as they are constructed, and is used when a value
// is streamed into a DataElement from a buffer.
//
//******************************************************************************

#define DIDBRKR_DLL

#include <dstring.hpp>

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
 
#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef BASE_H
   #include "base.h"
#endif

#ifndef DATA_HPP
   #include "data.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DATAELEMENT_HPP
   #include "dataelement.hpp"
#endif

#ifndef DATAELEMENTPROPERTIES_HPP
   #include "dataelementproperties.hpp"
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#ifndef DATAPROPERTIESIMPL_HPP
   #include "datapropertiesimpl.hpp"
#endif

#ifndef DIDBRKR_H
   #include "didbrkr.h"
#endif

#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp"
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

#ifndef INCLUDED_ALGORITHM
#define INCLUDED_ALGORITHM
   #include <algorithm>
#endif

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
   #include <fstream>
#endif

#ifndef INCLUDED_ISTREAM
#define INCLUDED_ISTREAM
   #include <istream>
#endif

#ifndef INCLUDED_SSTREAM
#define INCLUDED_SSTREAM
   #include <sstream>
#endif

#ifndef INCLUDED_STRSTREAM
#define INCLUDED_STRSTREAM
   #include <strstream>
#endif

#ifndef INCLUDED_TYPEINFO
#define INCLUDED_TYPEINFO
   #include <typeinfo>
#endif

namespace
{
   static const DString SEPARATOR_CHAR = I_("=");
   static const DString TERMINATOR_CHAR = I_(";");
   static const DString EOL_CHAR = I_("\n");
   const I_CHAR *CLASS_NAME = I_("Data");
   const unsigned long MAX_USER_ID = 1000000;      // Max allowable user id for appends
}

class Data::DataStream
{
public:
   virtual ~DataStream() {}

   virtual bool read( char *buffer, long bufferLength )
   {
      return false;
   }
   virtual bool write( char *buffer, long length )
   {
      return false;
   }
};

class Data::BufferStream : public Data::DataStream
{
public:
   BufferStream( char *buffer, long bufferLength ) :
      _buffer( buffer ),
      _bufferLength( bufferLength ) {}

   bool read( char *buffer, long bufferLength )
   {
      if ( bufferLength > _bufferLength )
         bufferLength = _bufferLength;

      memcpy( buffer, _buffer, bufferLength );

      _buffer       += bufferLength;
      _bufferLength -= bufferLength;
      return true;
   }
   bool write( char *buffer, long length )
   {
      if ( length > _bufferLength )
         length = _bufferLength;

      memcpy( _buffer, buffer, length );

      _buffer       += length;
      _bufferLength -= length;
      return true;
   }

private:
   char *_buffer;
   long  _bufferLength;
};

class Data::InStream : public Data::DataStream
{
public:
   InStream( std::istream& strm ) :
      _strm( &strm ),
      _wstrm( NULL )
   {}

#ifdef DST_UNICODE
   InStream( i_istream& wstrm ) :
      _strm( NULL ),
      _wstrm( &wstrm )
   {}
#endif

   bool read( char *buffer, long bufferLength )
   {
#ifdef DST_UNICODE
      if ( _wstrm )
      {
         _wstrm->read( (I_CHAR *) buffer, bufferLength / sizeof( I_CHAR ) );
         return !_wstrm->fail();
      }
      else
#endif
      {
         _strm->read( buffer, bufferLength );
         return !_strm->fail();
      }
   }

private:
   std::istream *_strm;
#ifdef DST_UNICODE
   i_istream *_wstrm;
#else
   void *_wstrm;
#endif
};

class Data::OutStream : public Data::DataStream
{
public:
   OutStream( std::ostream& strm ) :
      _strm( &strm ),
      _wstrm( NULL )
   {}

#ifdef DST_UNICODE
   OutStream( i_ostream& wstrm ) :
      _strm( NULL ),
      _wstrm( &wstrm )
   {}
#endif

   bool write( char *buffer, long length )
   {
#ifdef DST_UNICODE
      if ( _wstrm )
      {
         _wstrm->write( (I_CHAR *) buffer, length / sizeof( I_CHAR ) );
         return !_wstrm->fail();
      }
      else
#endif
      {
         _strm->write( buffer, length );
         return !_strm->fail();
      }
   }

private:
   std::ostream *_strm;
#ifdef DST_UNICODE
   i_ostream *_wstrm;
#else
   void *_wstrm;
#endif
};

const DString Data::EMPTY_STRING = NULL_STRING;

typedef DataProperties DP;
typedef DataComponentProperties DCP;
typedef DataElementProperties DEP;
typedef DataComponent DC;
typedef DataElement DE;

//******************************************************************************
//              Public Methods
//******************************************************************************

static bool isIdLess( const DCP *dcp1, const DCP *dcp2 )
{
   return ( dcp1->getName() < dcp2->getName() );
}

Data::Data() : DC(), _repeatData( NULL ),
   _dataIndexMap( NULL ),
   m_nextId( 0L ),
   _fieldNameMap( NULL ),
   m_pLocale( 0 ),
   _pDataBuffer( 0 )
{
   TRACE_CONSTRUCTOR( CLASS_NAME, I_("Data::Data()") );
   _dataProperties = NULL;
}

Data::Data( const Data &copy ) : DC(),
   _repeatData( NULL ), _dataIndexMap( NULL ), m_nextId( 0L ),
   _fieldNameMap( NULL ),
   m_pLocale( 0 ),
   _pDataBuffer( 0 )
{
   TRACE_CONSTRUCTOR( CLASS_NAME, I_("Data::Data( const Data & )") );

   _dataProperties = NULL;
   *this = copy;
}

Data::Data( const DString &propertiesId, const DString &idiString,
            bool appendNew, bool ignoreOnNoAppend,
            const ClientLocale &clientLocale )
   : DC(), _repeatData( NULL ), _dataIndexMap( NULL ),
   _fieldNameMap( NULL ),
     m_nextId( 0L ), m_pLocale( 0 ), _pDataBuffer( 0 )
{
   TRACE_CONSTRUCTOR( CLASS_NAME,
             I_("Data::Data( const DString &, const DString &,bool , bool )") );

#ifdef _DEBUG
   DString strMsg( I_("Creating data object '"));
   strMsg += propertiesId;
   strMsg += I_("'");
   TRACE_MSG( strMsg );
#endif

   m_pLocale = new ClientLocale( clientLocale );

   _dataProperties = new DP( propertiesId, *m_pLocale );
   if ( !_dataProperties )
   {
      THROWFROMBASE( DIDBRKR_COMPONENT_NAME,
               I_("Data::Data( const DString &, const DString &,bool , bool )"),
                     BASE_ALLOC_FAIL );
   }

   _initialize( static_cast<DP *>(_dataProperties) );

   if ( !setValues( idiString, appendNew, ignoreOnNoAppend, &clientLocale ) )
   {
      DString msg( I_("props=") );
      msg += propertiesId;
      // Throw if some keys or values are bad...
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
               I_("Data::Data( const DString &, const DString &,bool , bool )"),
                        DIDBRKR_CANT_SET_VALUES, msg.c_str() );
   }
}

Data::Data( unsigned long id, const DString &idiString,
            bool appendNew, bool ignoreOnNoAppend,
            const ClientLocale &clientLocale )
   : DC(), _repeatData( NULL ), _dataIndexMap( NULL ),
   _fieldNameMap( NULL ),
     m_nextId( 0L ), m_pLocale( 0 ), _pDataBuffer( 0 )
{
   TRACE_CONSTRUCTOR( CLASS_NAME,
             I_("Data::Data( const DString &, const DString &,bool , bool )") );

#ifdef _DEBUG
   DString strMsg( I_("Creating data object '"));
   strMsg.appendLong( id );
   strMsg += I_("'");
   TRACE_MSG( strMsg );
#endif

   m_pLocale = new ClientLocale( clientLocale );

   _dataProperties = new DP( id, *m_pLocale );
   if ( !_dataProperties )
   {
      THROWFROMBASE( DIDBRKR_COMPONENT_NAME,
               I_("Data::Data( unsigned long, const DString &,bool , bool )"),
                     BASE_ALLOC_FAIL );
   }

   _initialize( static_cast<DP *>(_dataProperties) );

   if ( !setValues( idiString, appendNew, ignoreOnNoAppend, &clientLocale ) )
   {
      DString msg( I_("props=") );
      msg.appendLong(id);
      // Throw if some keys or values are bad...
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
               I_("Data::Data( unsigned long, const DString &,bool , bool )"),
                        DIDBRKR_CANT_SET_VALUES, msg.c_str() );
   }
}

Data::~Data()
{
   TRACE_DESTRUCTOR( CLASS_NAME );

   delete _fieldNameMap;

   if ( _repeatData )
   {
      removeAllRepeats();
      delete _repeatData;
   }

   _deleteDataIndexMapContents();
   delete _dataIndexMap;

   delete _dataProperties;

   if ( _pDataBuffer )
   {
      delete [] _pDataBuffer;
      _pDataBuffer = 0;
   }

   if ( m_pLocale )
   {
      delete m_pLocale;
   }
}

Data& Data::operator[] ( unsigned int index )
{
   unsigned int numRepeats = getRepeatCount();

   if ( !numRepeats || index < 0 || index >= numRepeats )
   {
      MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME, I_("Data::operator[]") );
      DString msg( I_("props=") );
      msg += _dataProperties->getName();
      if ( 0 == numRepeats )
      {
         throw EXCEPTIONFROMFILEIDI( DIDBRKR_DATA_HAS_NO_REPEATS, msg.c_str() );
      }
      else
      {
         std::ostrstream charIndex;
         charIndex << index << std::ends;
         std::ostrstream numRpts;
         numRpts << getRepeatCount() << std::ends;
         msg += I_(";num=");
         msg += DString( DStringA( charIndex.str() ));
         msg += I_(";numrpts=");
         msg += DString( DStringA( numRpts.str() ));
         throw EXCEPTIONFROMFILEIDI( DIDBRKR_REPEAT_INDEX_OUT_OF_RANGE,
                                   msg.c_str() );
      }
   }
   return static_cast<Data &>(*(*_repeatData)[ index ]);
}

Data &Data::operator=( const Data &copy )
{
   MAKEFRAME( DIDBRKR_COMPONENT_NAME, I_("Data::operator=") );

   Data &constCopy = ( Data& )copy;

   if ( this == &constCopy )
   {
      return *this;
   }

   if ( _dataProperties && _dataProperties->isRepeatable() )
   {
      removeAllRepeats();
   }

   DC::operator=( constCopy );

   if ( _fieldNameMap )
   {
      _fieldNameMap->clear();
   }
   _deleteDataIndexMapContents();

   if ( m_pLocale )
   {
      delete m_pLocale;
      m_pLocale = 0;
   }

   if ( constCopy.m_pLocale )
   {
      m_pLocale = new ClientLocale( *constCopy.m_pLocale );
   }

   if ( constCopy._dataProperties )
   {
      if ( _dataProperties )
      {
         delete _dataProperties;
      }
      _dataProperties = new DP( *(static_cast<DP *>(constCopy._dataProperties)) );
      if ( !_dataProperties )
      {
         throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
      }

      _initialize( (DP*)_dataProperties, false );
   }
   else
   {
      delete _dataProperties;
      _dataProperties = NULL;
   }

   if ( constCopy._dataIndexMap )
   {
      DString tmpStr;
      for ( ComponentPtrIndexMap::iterator iter = constCopy._dataIndexMap->begin();
         iter != constCopy._dataIndexMap->end();
         ++iter )
      {  // need to create new data elements for data elements in original and
         //  add to new copies map.
         DE *pCopyDE = dynamic_cast< DE * >( (*iter).second );
         if ( pCopyDE )
         {  // We have a data element
            // Get const DataElementProperties as appropriate - this should be
            //  defined const in DataComponent and above so we wouldn't have to
            //  "unconst" in these situations.
            DCP *copyDCP = const_cast< DCP * >( pCopyDE->getProperties() );
            DEP *copyDEP = static_cast< DEP * >( copyDCP );
            // Create new DataElement based off of original
            DE *pDE = new DE( pCopyDE->getValue( tmpStr ), _getBase(),
               copyDEP, false, getLocale() );
            if ( !pDE )
            {
               THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::setElementValue"),
                           BASE_ALLOC_FAIL );
         }
            pDE->_setName( pCopyDE->getName() );
            // This takes care of adding to both _DataIndexMap and _fieldNameMap
            _addElementToMaps( pDE );
         }
      }
   }

   if ( constCopy.getRepeatCount() )
   {
      unsigned long numRepeats = constCopy.getRepeatCount();

      if ( !_repeatData )
      {
         _repeatData = new RepeatPtrVector;
      }
      if ( numRepeats )
      {
         _repeatData->reserve( numRepeats );
      }

      Data *rptData;
      DataComponent *pBase = _getBase();

      for ( unsigned long count = 0;  count < numRepeats;  ++count )
      {
         rptData = new Data( *(*(constCopy._repeatData))[ count ], pBase );
         if ( !rptData )
         {
            throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
         }
         _repeatData->push_back( rptData );
      }
   }

   if ( constCopy._pDataBuffer )
   {
      unsigned long ulLength = 0;

      if ( _dataProperties )
      {
         ulLength = ( ( DataProperties * )_dataProperties )->getFixedByteLength();
      }

      if ( !_pDataBuffer )
      {
         _pDataBuffer = (I_CHAR *)new char[ ulLength ];
      }

      memcpy( _pDataBuffer, constCopy._pDataBuffer, ulLength );
   }
   else
   {
      if ( _pDataBuffer )
      {
         delete [] _pDataBuffer;
         _pDataBuffer = 0;
      }
   }

   // Need to get repeatrecords too!
   // This does not handle nested repeats or fixed areas after repeat areas.
   // It assumes that the last element in a Dataset is the only field that
   // can be a repeat area. - Should just be able to change this to a loop over
   // the properties to do this.
   const DP *rpDP = getDataProperties();
   if ( rpDP && ( rpDP->getType() == DCP::eDP ) )
   {
      long lNumProperties = rpDP->getPropertyCount();

      if ( lNumProperties > 0 )
      {
         const DCP *pDCP = &( rpDP->getProperty( lNumProperties - 1 ) );

         if ( DCP::eDP == pDCP->getType() )
         {  // Handle data object
            DC *dataComp = _getDataElement( pDCP->getId(), NO_INIT );
            Data *rpData = static_cast< Data * >(dataComp);
            Data *rpDataOrig =
               static_cast< Data* >(
                  constCopy._getDataElement( pDCP->getId(), NO_INIT ) );
            *rpData = *rpDataOrig;
         }
      }
   }

   return *this;
}

// DT17817 This does not handle nested repeats or fixed areas after repeat areas
std::istream &operator>> ( std::istream &stream, Data &data )
{
   MAKEFRAME( DIDBRKR_COMPONENT_NAME, I_("operator>> (istream &, Data &)") );

   Data::InStream strm( stream );

   data._readFromStream( strm );

   return stream;
}

std::ostream &operator<< ( std::ostream &stream, const Data &data )
{
   TRACE_METHOD( DIDBRKR_COMPONENT_NAME, I_("operator<< (istream &, Data &)") );

   Data::OutStream strm( stream );

   data._writeToStream( strm );

   return stream;
}

#ifdef  DST_UNICODE
// These methods are only here for backward compatibility for DSTC and are
//  deprecated because they will not work correctly for binary data types
i_istream &operator>> ( i_istream &stream, Data &data )
{
   MAKEFRAME( DIDBRKR_COMPONENT_NAME, I_("operator>> (i_istream &, Data &)") );

   Data::InStream strm( stream );

   data._readFromStream( strm );

   return stream;
}

i_ostream &operator<< ( i_ostream &stream, const Data &data )
{
   TRACE_METHOD( DIDBRKR_COMPONENT_NAME, I_("operator<< (i_istream &, Data &)") );

   Data::OutStream strm( stream );

   data._writeToStream( strm );

   return stream;
}
#endif

Data::const_repeat_iterator Data::repeatBegin() const
{
   if ( !_repeatData )
   {
      DString msg( I_("props=") );
      msg += _dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("const Data::repeatBegin"),
                      DIDBRKR_DATA_HAS_NO_REPEATS,
                      msg.c_str() );
   }
   return _repeatData->begin();
}

Data::repeat_iterator Data::repeatBegin()
{
   if ( !_repeatData )
   {
      DString msg( I_("props=") );
      msg += _dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::repeatBegin"),
                      DIDBRKR_DATA_HAS_NO_REPEATS,
                      msg.c_str() );
   }
   return _repeatData->begin();
}

Data::const_repeat_iterator Data::repeatEnd() const
{
   if ( !_repeatData )
   {
      DString msg( I_("props=") );
      msg += _dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::repeatBegin"),
                      DIDBRKR_DATA_HAS_NO_REPEATS,
                      msg.c_str() );
   }
   return _repeatData->end();
}

Data::repeat_iterator Data::repeatEnd()
{
   if ( !_repeatData )
   {
      DString msg( I_("props=") );
      msg += _dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::repeatBegin"),
                      DIDBRKR_DATA_HAS_NO_REPEATS,
                      msg.c_str() );
   }
   return _repeatData->end();
}

bool Data::operator== ( const Data &data ) const
{
   // Compare the data components.
   if ( static_cast<DC &> ( *( const_cast<Data *>(this) ) ) != data )
   {
      return false;
   }

   // Compare the locales.
   if ( m_pLocale || data.m_pLocale )
   {
      const ClientLocale & locale =
         m_pLocale ? *m_pLocale : ClientLocale::getDefaultClientLocale();

      const ClientLocale & data_locale =
         data.m_pLocale ? *data.m_pLocale : ClientLocale::getDefaultClientLocale();

      if ( !( locale == data_locale ) )
      {
         return false;
      }
   }

   // Compare the repeat counts.
   unsigned long rptCount = getRepeatCount();
   unsigned long data_rptCount = data.getRepeatCount();

   if ( rptCount != data_rptCount )
   {
      return false;
   }

   if ( rptCount )
   {
      // Compare the repeated data objects.
      Data *repeat;
      Data *data_repeat;

      for ( unsigned long count = 0; count < rptCount; ++count )
      {
         repeat = (*(_repeatData))[count];
         data_repeat = (*(data._repeatData))[count];

         if ( (  repeat && !data_repeat ) ||
              ( !repeat &&  data_repeat ) )
         {
            return false;
         }

         if ( !( *repeat == *data_repeat ) )
         {
            return false;
         }
      }
   }
   else
   {
      const DP * rpDP          = getDataProperties();
      const DP * data_rpDP     = data.getDataProperties();

      if ( rpDP || data_rpDP )
      {
         // Compare the data properties.
         if ( (  rpDP && !data_rpDP ) ||
              ( !rpDP &&  data_rpDP ) )
         {
            return false;
         }

         if ( !( *rpDP == *data_rpDP ) )
         {
            return false;
         }

         // Compare the lengths of the fixed areas.
         unsigned long currentLen = rpDP->getFixedByteLength();
         unsigned long data_currentLen = data_rpDP->getFixedByteLength();

         if ( currentLen != data_currentLen )
         {
            return false;
         }

         // Both should have a buffer, or neither should.
         if ( (  _pDataBuffer && !data._pDataBuffer ) ||
              ( !_pDataBuffer &&  data._pDataBuffer ) )
         {
            return false;
         }

         // Compare the fixed areas.
         if ( _pDataBuffer && data._pDataBuffer )
         {
            if ( memcmp( _pDataBuffer, data._pDataBuffer, currentLen ) )
            {
               return false;
            }
         }

         // Compare the number of properties.
         unsigned long numValues  = rpDP->getPropertyCount();
         unsigned long data_numValues  = data_rpDP->getPropertyCount();

         if ( numValues != data_numValues )
         {
            return false;
         }

         if ( _dataIndexMap || data._dataIndexMap )
         {
            // Both should have a map, or neither should.
            if ( (  _dataIndexMap && !data._dataIndexMap ) ||
                 ( !_dataIndexMap &&  data._dataIndexMap ) )
            {
               return false;
            }

            // Both maps should be the same size.
            if ( _dataIndexMap->size() != data._dataIndexMap->size() )
            {
               return false;
            }

            // Compare the two maps.
            for ( ComponentPtrIndexMap::iterator iter = _dataIndexMap->begin();
                  iter != _dataIndexMap->end();
                  ++iter )
            {
               Data *pData = dynamic_cast<Data *>( (*iter).second );

               if ( pData )
               {
                  // Compare nested data objects.
                  Data *data_pData = dynamic_cast<Data*>(
                                        data._getDataElement( pData->getId(),
                                                              Data::INIT_FROM_BUFFER ) );
                  if ( !data_pData || !( *pData == *data_pData ) )
                  {
                     return false;
                  }
               }
               else
               {
                  // Compare appended data elements.
                  DataElement *pDataElement = dynamic_cast<DataElement *>( (*iter).second );

                  if ( pDataElement )
                  {
                     DString name( pDataElement->getName() );
                     unsigned long data_id = data.getFieldIdFromName( name );
                     DataElement *data_pDataElement;
                     data_pDataElement = dynamic_cast<DataElement *>(
                                            data._getDataElement( data_id,
                                                                  Data::INIT_FROM_BUFFER ) );
                     if ( !data_pDataElement || !( *pDataElement == *data_pDataElement ) )
                     {
                        return false;
                     }
                  }
                  else
                  {
                     return false;
                  }
               }
            }
         }
      }
   }

   return true;
}

void Data::addElement( DataElement &dataEl )
{
   DCP *newDCP = const_cast< DCP * >(dataEl.getProperties());
   DEP *newDEP = static_cast< DEP * >(newDCP);
   DataElement *newDE = new DataElement( dataEl.getValue(), newDEP );
   if ( !newDE )
   {
      THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::addElement"),
                     BASE_ALLOC_FAIL );
   }
   _addElementToMaps( newDE );
}

void Data::_setId( unsigned long newId )
{
   _id = newId;
}

bool Data::addRepeat( const Data &newRepeat )
{
   TRACE_METHOD(CLASS_NAME,I_("addRepeat( const Data & )"));

   if ( !_dataProperties )
   {
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::addRepeat"),
                      DIDBRKR_DATA_HAS_NO_REPEATS,
                      I_("props=noProperties") );
   }
   else if ( !_dataProperties->isRepeatable() )
   {
      DString msg( I_("props=") );
      msg += _dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::addRepeat"),
                      DIDBRKR_DATA_HAS_NO_REPEATS,
                      msg.c_str() );
   }
   else
   {
      if ( !_repeatData )
      {
         setRepeatCount( 0L );
      }

      Data *newData = new Data( newRepeat, _getBase() );
      if ( newData )
      {
         _repeatData->push_back( newData );

         return true;
      }
      else
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::addRepeat"),
                        BASE_ALLOC_FAIL );
      }
   }
   return false;
}

bool Data::appendRepeatData( const Data &data, bool overwriteFixedArea )
{
   TRACE_METHOD( CLASS_NAME,
       I_("appendRepeatData( const Data &, bool, bool )") );

   Data &constData = const_cast< Data & >( data );

   if ( !_dataProperties )
   {
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::appendRepeat"),
                      DIDBRKR_DATA_HAS_NO_REPEATS, I_("props=noName") );
   }
   else if ( !getData( DEFAULT_REPEAT_RECORD )._dataProperties->isRepeatable() )
   {
      DString msg( I_("props=") );
      msg += _dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::appendRepeat"),
                      DIDBRKR_DATA_HAS_NO_REPEATS,
                      msg.c_str() );
   }

   if ( *(this->getProperties()) != *(constData.getProperties()) )
   {
      return false;
   }

   const DP *rpDP = getDataProperties();

   const type_info& typeDataElement = typeid( DataElement );

   if ( overwriteFixedArea )
   {
      if ( _pDataBuffer && data._pDataBuffer )
      {
         memcpy( _pDataBuffer, data._pDataBuffer, rpDP->getFixedByteLength() );
      }
   }

   Data *fromRepeat =
      const_cast<Data *> (&constData.getData( DEFAULT_REPEAT_RECORD ));
   Data *toRepeat = const_cast<Data *> (&getData( DEFAULT_REPEAT_RECORD ));

   if ( !fromRepeat->_repeatData )
   {  // Repeatable without repeats - we've done all the copying we need.
      return true;
   }
   if ( !toRepeat->_repeatData )
   {
      toRepeat->setRepeatCount( 0L );
   }
   unsigned long numRpts = fromRepeat->_repeatData->size();
   for ( unsigned long count = 0; count < numRpts; ++count )
   {
      toRepeat->addRepeat( *(*(fromRepeat->_repeatData))[ count ] );
   }
   return true;
}

bool Data::moveRepeatData( Data &data )
{
   TRACE_METHOD(
               CLASS_NAME,
               I_( "moveRepeatData( Data &data )" ) );

   if ( !_dataProperties )
   {
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::moveRepeatData" ),
                        DIDBRKR_DATA_HAS_NO_REPEATS, I_( "props=noName" ) );
   }
   else if ( !getData( DEFAULT_REPEAT_RECORD )._dataProperties->isRepeatable() )
   {
      DString msg( I_( "props=" ) );
      msg += _dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::moveRepeatData" ),
                        DIDBRKR_DATA_HAS_NO_REPEATS,
                        msg.c_str() );
   }

   if ( *( this->getProperties() ) != *( data.getProperties() ) )
   {
      DString msg( I_( "props1=" ) );
      msg += _dataProperties->getName();
      msg += I_( ";props2=" );
      msg += data._dataProperties->getName();
      // Cannot assign data objects, properties %props1% and %props2%
      // don't match.
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::moveRepeatData" ),
                        DIDBRKR_CANNOT_ASSIGN_DATA_OBJECTS,
                        msg.c_str() );
   }

   Data *fromRepeat =
      const_cast< Data * > ( &data.getData( DEFAULT_REPEAT_RECORD ) );
   Data *toRepeat = const_cast< Data * > ( &getData( DEFAULT_REPEAT_RECORD ) );

   if ( !fromRepeat->_repeatData )
   {
      return false;
   }
   if ( !toRepeat->_repeatData )
   {
      toRepeat->setRepeatCount( 0L );
   }
   unsigned long numRpts = fromRepeat->_repeatData->size();
   for ( unsigned long count = 0; count < numRpts; ++count )
   {
      toRepeat->_appendRepeat( fromRepeat->_removeRepeat( 0 ) );
   }
   return true;
}

bool Data::exists( const DString &componentName ) const
{
   if ( _dataProperties &&
        getDataProperties()->exists( componentName ) )
   {
      return true;
   }
   else if ( _fieldNameMap &&
      ( _fieldNameMap->end() != _fieldNameMap->find( componentName ) ) )
   {
      return true;
   }

   return false;
}

bool Data::exists( unsigned long id ) const
{
   if ( _dataProperties &&
        getDataProperties()->exists( id ) )
   {
      return true;
   }

   if ( _dataIndexMap &&
        _dataIndexMap->end() != _dataIndexMap->find( id ) )
   {
      return true;
   }

   return false;
}

long Data::findRepeatIndex( const DString &idiKeysValue,
                            unsigned long startIndex ) const
{
   TRACE_METHOD( CLASS_NAME,
                 I_("findRepeatIndex( const DString &, unsigned long") );
   DString key;
   DString value;
   int length = idiKeysValue.length();
   int start = 0;
   DString::size_type separatorPosition;
   DString::size_type terminatorPosition;
   bool done = false;
   bool allOK = true;
   typedef std::map< DString, DString, std::less< DString > > myMap;
   myMap idiMap;
   long counter = 0L;
   long repeatCount = getRepeatCount();

   if (( 0 == repeatCount ) || ( 0 == length ) || ( (long)startIndex > repeatCount ))
   {
      return DataComponent::REPEAT_INDEX_NOT_FOUND;
   }

   const DP *rpDP = getDataProperties();
   while( !done && allOK )
   {
      // Look for the next separator
      separatorPosition = idiKeysValue.find( SEPARATOR_CHAR, start );

      if ( -1 == separatorPosition )
      {
         // Stop if a separator was not found
         done = true;
      }
      else
      {
         // Extract the key & look for the next terminator
         key = strip( idiKeysValue.substr( start, separatorPosition - start ) );

         // Check if the key indicates a replacement but doesn't exist
         if ( !exists( key ) )
         {
            allOK = false;
         }

         terminatorPosition = idiKeysValue.find( TERMINATOR_CHAR,
                                              separatorPosition + 1 );

         if ( -1 == terminatorPosition )
         {
            // Stop if a terminator was not found, but
            terminatorPosition = length;
            done = true;
         }

         // Extract the value & add it to the object
         value = strip( idiKeysValue.substr( separatorPosition + 1,
                        terminatorPosition - separatorPosition - 1 ) );
         // Search through the properties map, looking for the
         // DataProperties object for this key.
         // Typecast what was found from a DataProperties to a
         // DataElementProperties.
         if ( allOK )
         {
            DEP *elementProperties = static_cast<DEP *>(const_cast<DCP *>
                                  ( &( rpDP->getProperty( key ) ) ) );
            // Now that we have gotten to the DataElementProperties object,
            // format the value we are searching for, using the same
            // function that formats a data element's value on creation.
            elementProperties->formatValue( value );
         }
         idiMap[ key ] = value;

         start = terminatorPosition + 1;
      }
   }
   if ( allOK )
   {
      DString tmpStr;
      myMap::iterator iter;
      done = false;
      allOK = true;
      if ( idiMap.size() > 0 )
      {
         myMap::iterator idiMapEnd = idiMap.end(), idiMapBegin = idiMap.begin();
         for ( counter = startIndex; counter < repeatCount && !done; ++counter )
         {
            bool thisOneDone = false;
            for ( iter = idiMapBegin;
                  iter != idiMapEnd && !thisOneDone;
                  ++iter )
            {
               // Construct a string for the key we are searching for.
               const DString& theKey = (*iter).first;
               // Construct a string for the value we are comparing.
               DString theValue( (*iter).second );
               // Finally, compare the newly formatted value to the value
               // for this data component.
               DString compValue( ( *_repeatData )[ counter ]->
                                  getElementValue( theKey, 
                                                   tmpStr ) );
               strip( compValue );
               
               DEP *elementProperties = static_cast<DEP *>(const_cast<DCP *>
                                     ( &( rpDP->getProperty( theKey ) ) ) );
               // Now that we have gotten to the DataElementProperties object,
               // format the value we are searching for, using the same
               // function that formats a data element's value on creation.
               elementProperties->formatValue( compValue );
               
               if ( theValue != compValue )
               {
                  thisOneDone = true;
               }
            }
            done = !thisOneDone;
         }
      }
   }

   if ( done )
   {
      return counter - 1;
   }
   else
   {
      return DataComponent::REPEAT_INDEX_NOT_FOUND;
   }
}

// DT17817 Need to _flush DE's (maybe in other methods too)
void Data::getAllValues( DString &idiString, bool insertEOLs,
                         bool usePropertiesOrder, unsigned long flags,
                         const ClientLocale *pClientLocale ) const
{
   TRACE_METHOD( CLASS_NAME,
                 I_("getAllValues( DString &, bool, bool, unsigned long )") );

   DString tmpStr;
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &getLocale();

   idiString.erase();
   if ( _dataProperties )
   {
      const DP *rpDP = getDataProperties();
      if ( usePropertiesOrder )
      {
         unsigned long numValues = 0L;
         numValues = rpDP->getPropertyCount();

         for ( unsigned long counter = 0;  counter < numValues;  ++counter )
         {
            idiString.append( rpDP->getPropertyElementName( counter ) );
            idiString.append( SEPARATOR_CHAR );
            const DCP *pDCP = &( rpDP->getProperty( counter ) );
            if ( DCP::eDEP == pDCP->getType() )
            {
               idiString.append( getElementValue( pDCP->getId(), tmpStr, flags,
                  pLocClientLocale ) );
            }

            idiString.append( TERMINATOR_CHAR );
            if ( insertEOLs )
            {
               idiString.append( EOL_CHAR );
            }
         }
      }
      else
      {
         typedef std::vector< DataComponentProperties * > DCPPtrVector;
         DCPPtrVector propVector = rpDP->getImplVector();
         std::sort( propVector.begin(), propVector.end(), isIdLess );
         unsigned long numValues = rpDP->getPropertyCount();

         for ( unsigned long counter = 0;  counter < numValues;  ++counter )
         {
            unsigned long transIndex =
               rpDP->getVectorIndexFromName(propVector[counter]->getName());

            idiString.append( rpDP->getPropertyElementName( transIndex ) );
            idiString.append( SEPARATOR_CHAR );
            const DCP *pDCP = &( rpDP->getProperty( transIndex ) );
            if ( DCP::eDEP == pDCP->getType() )
            {
               idiString.append( getElementValue( pDCP->getId(), tmpStr, flags,
                  pLocClientLocale ) );
            }
            idiString.append( TERMINATOR_CHAR );
            if ( insertEOLs )
            {
               idiString.append( EOL_CHAR );
            }
         }
      }
   }
   if ( _fieldNameMap )
   {
      FieldNameMap::const_iterator mapIter;
      for ( mapIter = _fieldNameMap->begin(); mapIter != _fieldNameMap->end(); ++mapIter )
      {
         idiString.append( (*mapIter).first );
         idiString.append( SEPARATOR_CHAR );
         idiString.append( getElementValue( (*mapIter).second, tmpStr, flags, pLocClientLocale ) );
         idiString.append( TERMINATOR_CHAR );
         if ( insertEOLs )
         {
            idiString.append( EOL_CHAR );
         }
      }
   }
}

bool Data::_writeToStream( DataStream& strm ) const
{
   TRACE_METHOD( DIDBRKR_COMPONENT_NAME, I_("_writeToStream") );

   unsigned long  numRepeats = getRepeatCount();

   if ( numRepeats )
   {
      Data *rptData;

      for ( unsigned long count = 0; count < numRepeats; ++count )
      {
         rptData = (*(_repeatData))[count];
         rptData->_writeToStream( strm );
      }
   }
   else
   {
      const DP *    rpDP       = getDataProperties();

      if ( !rpDP )
      {
         return false;
      }

      unsigned long currentLen = rpDP->getFixedByteLength();
      unsigned long numValues  = rpDP->getPropertyCount();
      const DCP *   pDCP;

      // Copy fixed area
      strm.write( reinterpret_cast<char *> ( _pDataBuffer ), currentLen );

      for ( unsigned long counter = 0; counter < numValues; ++counter )
      {
         pDCP = &( rpDP->getProperty( counter ) );

         if ( DCP::eDP == pDCP->getType() )
         {
            Data *pData = static_cast<Data*>(
                                  _getDataElement( pDCP->getId(),
                                                   Data::INIT_FROM_BUFFER ) );
            pData->_writeToStream( strm );
         }
      }
   }

   return true;
}

bool Data::_readFromStream( DataStream& strm )
{
   MAKEFRAME( DIDBRKR_COMPONENT_NAME, I_("_readFromStream") );

   const DP *rpDP = getDataProperties();

   if ( !rpDP )
   {
      return false;
   }

   unsigned long currentLen = rpDP->getFixedByteLength();

   if ( rpDP->isRepeatable() )
   {
      // Get a reference to the repeat data
      Data::RepeatPtrVector& repeatData = *_repeatData;

      // Loop through all the repeat objects and read them in from the buffer
      unsigned long       numRepeats = getRepeatCount();
      Data               *rptData;
      DP                 *rptProperty;
      DataComponent      *pBase = _getBase();
      // Get impl for repeats to use
      DataPropertiesImpl *rpImpl =
                  DataPropertiesImpl::getInstancePointer( rpDP->getId(),
                                                          *( m_pLocale ),
                                                          false );

      for ( long count = 0;  count < (long)numRepeats;  ++count )
      {
         // Check to see if there is already a repeat in the position
         rptData = repeatData[count];

         if ( rptData != NULL )
         {
            // There was so remove it
            delete rptData;
         }

         // Create a new repeat for this position
         rptData = ( repeatData[count] = new Data( pBase ) );
         if ( !rptData )
         {
            throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
         }

         // Create the properites
         rptProperty = new DP( rpImpl );
         if ( !rptProperty )
         {
            throw EXCEPTIONFROMBASE( BASE_ALLOC_FAIL );
         }

         // Initialize the the data object
         rptData->_initialize( rptProperty, false );

         // Read in from the stream
         strm.read( reinterpret_cast<char *> ( rptData->_pDataBuffer ), currentLen );
      }
   }
   else
   {
      strm.read( reinterpret_cast<char *> ( _pDataBuffer ), currentLen );

      // Need to get repeatrecords too!
      // This does not handle nested repeats or fixed areas after repeat areas.
      // It assumes that the last element in a Dataset is the only field that
      // can be a repeat area.
      unsigned long numValues = rpDP->getPropertyCount();

      if ( numValues > 0 )
      {
         DC* pDC = _getDataElementByIndex( numValues - 1, Data::NO_INIT );

         if ( pDC && ( typeid( *pDC ) == typeid( Data ) ) )
         {
            static_cast<Data*>( pDC )->_readFromStream( strm );
         }
      }
   }

   return true;
}

bool Data::getAsUnsignedCharBuffer( char *buffer,
                                    unsigned long buffLength ) const
{
   TRACE_METHOD( DIDBRKR_COMPONENT_NAME, I_("getAsUnsignedCharBuffer") );

   if ( buffer == 0L || buffLength <= 0L )
   {
      return false;
   }

   BufferStream strm( buffer, buffLength );

   return _writeToStream( strm );
}

bool Data::setAsUnsignedCharBuffer( const char *buffer,
                                    unsigned long buffLength )
{
   TRACE_METHOD( DIDBRKR_COMPONENT_NAME, I_("setAsUnsignedCharBuffer") );

   if ( buffer == 0L )
   {
      return false;
   }

   BufferStream strm( const_cast< char * > ( buffer ), buffLength );

   return _readFromStream( strm );
}

const DC &Data::getComponent( const DString &componentName ) const
{
   unsigned long id = getFieldIdFromName( componentName );
   if ( ULONG_MAX == id )
   {  // no find
      DString msg( I_( "comp=" ) );
      msg += componentName;
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getComponent"),
                      DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
   }
   return getComponent( id );
}

const DC &Data::getComponent( unsigned long id ) const
{
   ComponentPtrIndexMap::const_iterator mapIter;

   // check properties first
   DC *pDC = _getDataElement( id, INIT_FROM_BUFFER );

   if ( pDC )
   {
      return *pDC;
   }

   //check appends
   if ( _dataIndexMap )
   {
      mapIter = _dataIndexMap->find( id );
      if ( mapIter != _dataIndexMap->end() )
      {
         return *( (*mapIter).second );
      }
   }
   DString msg( I_( "comp=" ) );
   msg.appendULong( id );
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getComponent"),
                   DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

unsigned long Data::getComponentCount() const
{
   unsigned long lSize = 0;

   if ( _fieldNameMap )
   { // add appended elements
      lSize += _fieldNameMap->size();
   }

   if ( _dataProperties )
   {
      lSize += getDataProperties()->getPropertyCount();
   }

   return lSize;
}

const Data &Data::getData( const DString &componentName ) const
{
   return *(static_cast<const Data *>(&getComponent( componentName )));
}

const Data &Data::getData( unsigned long id ) const
{
   return *(static_cast<const Data *>(&getComponent( id )));
}

const DP *Data::getDataProperties() const
{
   return static_cast<const DP *>( getProperties() );
}

const DString &Data::getElementLabel(
   unsigned long id,
   const ClientLocale *rpClientLocale
   ) const
{
   const DP *rpDP = getDataProperties();
   if ( rpDP && rpDP->exists( id ) )
   {
      const DEP *dep =
         static_cast< const DEP * >( &rpDP->getPropertyByFieldIndex( id ) );
      const ClientLocale *pLocClientLocale =
         rpClientLocale ? rpClientLocale : &getLocale();
      return dep->getFieldLabel( pLocClientLocale );
   }
   else if ( _dataIndexMap )
   {
      ComponentPtrIndexMap::iterator iter = _dataIndexMap->find( id );
      if ( iter != _dataIndexMap->end() )
      {
         DataElement *de = static_cast< DataElement * >( (*iter).second );
         return de->getLabel();
      }
   }
   return EMPTY_STRING;
}

const DString &Data::getElementLabel(
   const DString &name,
   const ClientLocale *rpClientLocale
   ) const
{
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX != id )
   {
      return getElementLabel( id, rpClientLocale );
   }

   DString msg( I_( "comp=" ) );
   msg += name;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::getElementLabel" ),
                   DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

const DEP *Data::getElementProperties(
   unsigned long id
   ) const
{
   const DP *rpDP = getDataProperties();
   if ( rpDP && rpDP->exists( id ) )
   {
      const DEP *dep =
         dynamic_cast< const DEP * >( &rpDP->getPropertyByFieldIndex( id ) );
      return dep;
   }
   else if ( _dataIndexMap )
   {
      ComponentPtrIndexMap::iterator iter = _dataIndexMap->find( id );
      if ( iter != _dataIndexMap->end() )
      {
         DataElement *pDE = dynamic_cast< DataElement * >( (*iter).second );
         if ( pDE )
         {
            const DEP *pDEP = dynamic_cast< const DEP * >( pDE->getProperties() );
            return pDEP;
         }
         // found but no properties
         return NULL;
      }
   }
   DString msg( I_( "comp=" ) );
   msg.appendLong( id );
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::getElementProperties" ),
                   DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

const DEP *Data::getElementProperties(
   const DString &name
   ) const
{
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX != id )
   {
      return getElementProperties( id );
   }

   DString msg( I_( "comp=" ) );
   msg += name;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::getElementProperties" ),
                   DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

bool Data::getElementValue(
   unsigned long id,
   unsigned char *binBuff,
   unsigned long buffLength,
   unsigned long &returnedLength
   ) const
{
  if ( _dataProperties )
   {  // First try to get via data dictionary properties
      const DataProperties *rpDP = getDataProperties();
      const DEP *dep =
         static_cast< const DEP * >( &rpDP->getPropertyByFieldIndex( id ) );
      if ( dep->getStoredType() == DEP::BINARY )
      {  // only works for binary types
         DataProperties::EReturn eRtn = rpDP->getValueFromBuffer( id, binBuff,
            (unsigned char *)getDataBuffer(), buffLength, returnedLength );
         if ( DataProperties::SUCCESS == eRtn )
         {  // Success
            return true;
         }
         else if ( DataProperties::FAILURE == eRtn )
         {
            return false;
         }
      }
      else
      {  // Invalid type
         return false;
      }
   }

   // Not defined in data set properties - try append map
   ComponentPtrIndexMap::const_iterator iter;
   if ( !_dataIndexMap ||
        ( ( iter = _dataIndexMap->find( id ) ) == _dataIndexMap->end() ) )
   {
      DString msg( I_("comp=") );
      msg.appendLong( id );
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getElementValue"),
                        DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
   }

   DataElement *de = static_cast< DataElement * >( (*iter).second );
   if ( de->getProperties() )
   {
      const DEP *dep = static_cast< const DEP * >( de->getProperties() );
      if ( dep && dep->getStoredType() == DEP::BINARY )
      {
         return de->getBinaryValue( binBuff, buffLength, returnedLength );
      }
   }

   return false;
}

bool Data::getElementValue(
   const DString &name,
   unsigned char *binBuff,
   unsigned long buffLength,
   unsigned long &returnedLength
   ) const
{
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX != id )
   {
      return getElementValue( id, binBuff, buffLength, returnedLength );
   }

   DString msg( I_("comp=") );
   msg += name;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getElementValue"),
                   DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

DString &Data::getElementValue(
   const DString &name,
   DString &outputValue,
   unsigned long formatFlags,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   ) const
{
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX != id )
   {
      return getElementValue( id, outputValue, formatFlags, rpClientLocale,
         i18nFormat );
   }

   DString msg( I_("comp=") );
   msg += name;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getElementValue"),
                   DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

DString Data::getElementValue(
   const DString &name,
   unsigned long formatFlags,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   ) const
{
   DString dstrRet;

   return getElementValue( name, dstrRet, formatFlags,
                           rpClientLocale, i18nFormat );
}

DString Data::getElementValue(
   unsigned long id,
   unsigned long formatFlags,
   const ClientLocale *pClientLocale,
   const DString &i18nFormat
   ) const
{
   DString dstrRet;
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &getLocale();

   return getElementValue( id, dstrRet, formatFlags,
                           pLocClientLocale, i18nFormat );
}

DString &Data::getElementValue( unsigned long id, DString &outputValue,
                                unsigned long formatFlags,
                                const ClientLocale *pClientLocale,
                                const DString &i18nFormat ) const
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &getLocale();

   if ( _dataProperties )
   {  // First try to get via data dictionary properties
      const DataProperties *rpDP = getDataProperties();
      DataProperties::EReturn eRtn = rpDP->getValueFromBuffer( id, outputValue,
         (unsigned char *)getDataBuffer(), formatFlags, pLocClientLocale, i18nFormat );
      if ( DataProperties::SUCCESS == eRtn )
      {  // Success
         return outputValue;
      }
   }

   // Not defined in data set properties - try append map
   ComponentPtrIndexMap::const_iterator iter;
   if ( !_dataIndexMap ||
        ( ( iter = _dataIndexMap->find( id ) ) == _dataIndexMap->end() ) )
   {
      DString msg( I_("comp=") );
      msg.appendLong( id );
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getElementValue"),
                        DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
   }

   ( (*iter).second )->getValue( outputValue, formatFlags, pLocClientLocale,
      i18nFormat );
   return outputValue;
}

unsigned long Data::getFieldIdFromName( const DString &name ) const
{
   unsigned long id = ULONG_MAX;
   if ( _dataProperties )
   {  // First try to get via data set properties
      const DP *rpDP = getDataProperties();
      id = rpDP->getFieldIdFromName( name );
   }

   if ( ULONG_MAX == id && _fieldNameMap )
   {  // try to get from append map
      FieldNameMap::const_iterator mapIter = _fieldNameMap->find( name );
      if ( mapIter != _fieldNameMap->end() )
      {
         id = ( *mapIter ).second;
      }
   }
   return id;
}

const DString &Data::getFieldNameFromId( unsigned long id ) const
{
   const DP *rpDP = getDataProperties();
   if ( rpDP && rpDP->exists( id )  )
   {  // First try to get via data set properties
      return rpDP->getPropertyByFieldIndex( id ).getName();
   }

   // Not defined in data set properties - try append map
   ComponentPtrIndexMap::const_iterator iter;
   if ( !_dataIndexMap ||
        ( ( iter = _dataIndexMap->find( id ) ) == _dataIndexMap->end() ) )
   {
      DString msg( I_("comp=") );
      msg.appendLong( id );
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getFieldNameFromId"),
                        DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
   }

   DataElement *pDE = dynamic_cast< DataElement * >( (*iter).second );
   if ( pDE )
   {
      return pDE->getName();
   }

   // Shouldn't occur - component wasn't a data element.
   DString msg( I_("comp=") );
   msg.appendLong( id );
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getFieldNameFromId"),
                     DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

unsigned long Data::getId() const
{
   if ( _dataProperties )
   {
      return _dataProperties->getId();
   }
   else
   {
      return _id;
   }
}

unsigned long Data::getMaxLength() const
{
   if ( _dataProperties )
   {
      return _dataProperties->getMaxLength();
   }
   return ULONG_MAX;
}

const DString &Data::getName() const
{
   if ( _dataProperties )
   {
      return _dataProperties->getName();
   }
   return EMPTY_STRING;
}

const Data & Data::getRepeat( unsigned long repeatIndex ) const
{
   if ( repeatIndex >= getRepeatCount() )
   {
      MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME, I_("Data::getRepeat") );
      std::ostrstream charIndex;
      charIndex << repeatIndex << std::ends;
      std::ostrstream numRpts;
      numRpts << getRepeatCount() << std::ends;
      DString msg( I_("props=") );
      msg += I_(";num=");
      msg += DString( DStringA( charIndex.str() ));
      msg += I_(";numrpts=");
      msg += DString( DStringA( numRpts.str() ));
      throw EXCEPTIONFROMFILEIDI( DIDBRKR_REPEAT_INDEX_OUT_OF_RANGE,
                                msg.c_str() );
   }
   return static_cast<Data &>(*(*_repeatData)[ repeatIndex ]);
}

unsigned long Data::getRepeatCount() const
{
   if ( _repeatData )
   {
      return _repeatData->size();
   }
   else
   {
      return 0L;
   }
}

bool Data::getSelectedValues( Data &data )
{
   TRACE_METHOD( CLASS_NAME, I_("getSelectedValues( Data & )") );
   bool allOK = true;
   DString tmpStr;
   const DP *rpDP = data.getDataProperties();

   if ( rpDP && rpDP->getType() == DCP::eDP )
   {
      long lCount = rpDP->getPropertyCount();

      for ( long lIndex = 0; lIndex < lCount; ++lIndex )
      {
         unsigned long id = rpDP->getProperty( lIndex ).getId();
         try
         {
            data.setElementValue( id, getElementValue( id, tmpStr ) );
         }
         catch( ... )
         {
            allOK = false;
         }
      }
   }

   if ( data._fieldNameMap )
   {
      FieldNameMap::iterator toMapIter;
      for ( toMapIter = data._fieldNameMap->begin();
            toMapIter != data._fieldNameMap->end();
            ++toMapIter )
      {
         try
         {
            data.setElementValue( (*toMapIter).first,
                                  getElementValue( (*toMapIter).first, tmpStr ) );
         }
         catch( ... )
         {
            allOK = false;
         }
      }
   }
   return allOK;
}

unsigned long Data::getTotalMaxByteLength() const
{
   if ( getRepeatCount() )
   {  // Get length for all repeats
      unsigned long numRepeats = getRepeatCount();
      Data *rptData = (*(_repeatData))[0];
      unsigned long rptLength = rptData->getTotalMaxByteLength();
      return numRepeats * rptLength;
   }

   if ( _dataProperties )
   {  // get length for self starting with fixed length
      const DP *rpDP = getDataProperties();
      unsigned long totLength = rpDP->getFixedByteLength();
      unsigned long numValues = rpDP->getPropertyCount();
      for ( unsigned long counter = 0;  counter < numValues;  ++counter )
      {
         const DCP *pDCP = &( rpDP->getProperty( counter ) );

         if ( DCP::eDP == pDCP->getType() )
         {  // Handle data object
            DC *dataComp = _getDataElement( pDCP->getId(), INIT_FROM_BUFFER );
            Data *dataPtr = static_cast< Data * >( dataComp );
            totLength += dataPtr->getTotalMaxByteLength();
         }
      }
      return totLength;
   }

   return 0L;
}

DString &Data::getValue( DString &valueOut, unsigned long formatFlags,
                        const ClientLocale *pClientLocale,
                        const DString &i18nFormat ) const
{
   valueOut = I_( " " );
   return valueOut;
}

DString Data::getValue( unsigned long formatFlags,
                        const ClientLocale *pClientLocale,
                        const DString &i18nFormat ) const
{
   // Returning an actual string should be OK because I am told that most
   // compilers are smart enough to avoid unnecessary temp variables now.
   return DString( I_( " " ) );
}

bool Data::setValue( const DString &value, bool checkValidity,
                     const ClientLocale *pClientLocale,
                     bool displayFormat,
                     const DString &i18nFormat )
{
   return false;
}

bool Data::isDefault(
   unsigned long id,
   const ClientLocale *rpClientLocale
   ) const
{
   const ClientLocale *rpLocClientLocale =
      rpClientLocale ? rpClientLocale : &getLocale();
   bool bDefault = false;
   const DP *rpDP = getDataProperties();
   if ( rpDP && rpDP->exists( id ) )
   {
      DString value;
      getElementValue( id, value, 0, rpLocClientLocale );
      bDefault = ( value == rpDP->getPropertyByFieldIndex( id ).getDefaultValue( rpLocClientLocale ) );
   }
   else
   {  // Not defined in data set properties - try append map
      ComponentPtrIndexMap::const_iterator iter;
      if ( !_dataIndexMap ||
           ( ( iter = _dataIndexMap->find( id ) ) == _dataIndexMap->end() ) )
      {
         DString msg( I_("comp=") );
         msg.appendLong( id );
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getFieldNameFromId"),
                           DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
      }

      DataElement *pDE = dynamic_cast< DataElement * >( (*iter).second );
      if ( pDE )
      {
         bDefault = pDE->isDefault();
      }
      else
      {  // Shouldn't occur - component wasn't a data element.
         DString msg( I_("comp=") );
         msg.appendLong( id );
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getFieldNameFromId"),
                           DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
      }
   }
   return bDefault;
}

bool Data::isDefault(
   const DString &name,
   const ClientLocale *rpClientLocale
   ) const
{
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX != id )
   {
      return isDefault( id, rpClientLocale );
   }

   DString msg( I_("comp=") );
   msg += name;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::isDefault"),
                   DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

// If there are appended items, this would not behave appropriately since they
//  don't affect the outcome of this method.
// Nested data sets/repeats are not handled in this method
bool Data::isDefault( const ClientLocale *rpClientLocale ) const
{
   const ClientLocale *rpLocClientLocale =
      rpClientLocale ? rpClientLocale : &getLocale();
   bool isNot = false;
   if ( _dataProperties )
   {
      const DP *rpDP = getDataProperties();
      unsigned long numValues = rpDP->getPropertyCount();
      DString tmpStr;

      for ( unsigned long counter = 0;  counter < numValues;  ++counter )
      {
         const DCP *rpDCP = &( rpDP->getProperty( counter ) );
         if ( DCP::eDEP == rpDCP->getType() )
         {
            getElementValue( rpDCP->getId(), tmpStr, 0, rpLocClientLocale );
            if ( tmpStr != rpDCP->getDefaultValue( rpLocClientLocale ) )
            {
               isNot = true;
               break;
            }
         }
         // Nested data sets/repeats are not hanlded in this method
      }
   }
   return !isNot;
}

void Data::removeAllRepeats()
{
   TRACE_METHOD( CLASS_NAME, I_("removeAllRepeats()") );
   if ( !_dataProperties )
   {
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::removeAllRepeats"),
                      DIDBRKR_NOT_REPEATABLE, I_("props=noProperties") );
   }
   if ( !_dataProperties->isRepeatable() )
   {
      DString msg( I_("props=") );
      msg += _dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::removeAllRepeats"),
                      DIDBRKR_NOT_REPEATABLE, msg.c_str());
   }
   if ( _repeatData )
   {
      unsigned long rptCount = getRepeatCount();
      for ( unsigned long count = 0; count < rptCount; ++count )
      {
         if ( (*_repeatData)[ count ] )
         {
            delete (*_repeatData)[ count ];
         }
      }
      _repeatData->erase( _repeatData->begin(), _repeatData->end() );
   }
}

bool Data::removeRepeat( unsigned long removeAt )
{
   TRACE_METHOD( CLASS_NAME, I_("removeRepeat( unsigned long )") );
   if ( _repeatData )
   {
      if ( removeAt >= getRepeatCount() )
      {
         std::ostrstream charIndex;
         charIndex << removeAt << std::ends;
         std::ostrstream numRpts;
         numRpts << getRepeatCount() << std::ends;
         DString msg( I_("props=") );
         msg += I_(";num=");
         msg += DString( DStringA( charIndex.str() ));
         msg += I_(";numrpts=");
         msg += DString( DStringA( numRpts.str() ));
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::removeRepeat"),
                         DIDBRKR_REPEAT_INDEX_OUT_OF_RANGE, msg.c_str() );
      }
      delete (*_repeatData)[ removeAt ];
      _repeatData->erase( _repeatData->begin() + removeAt );

      return true;
   }
   else
   {
      return false;
   }
}

// Don't know what the intent of this is - probably broken.  If intent is as
//  stated in header, no elements in properties are really being reset here.
void Data::resetValue( const ClientLocale *pClientLocale )
{
   TRACE_METHOD( CLASS_NAME, I_("resetValue()") );
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &getLocale();

   if ( _dataProperties && _dataProperties->isRepeatable() )
   {
      removeAllRepeats();
   }

   if ( _dataIndexMap )
   {
      for ( ComponentPtrIndexMap::iterator iter = _dataIndexMap->begin();
            iter != _dataIndexMap->end();
            ++iter )
      {  // need to reset nested data objects/repeats, but delete all
         //  appended elements ??

         ( *iter ).second->resetValue( pLocClientLocale );
      }
   }

   if ( _fieldNameMap )
   {
      _fieldNameMap->clear();
   }
}

void Data::resetElementValue( unsigned long id,
                              const ClientLocale *rpClientLocale )
{
   const ClientLocale *rpLocClientLocale =
      rpClientLocale ? rpClientLocale : &getLocale();

   if ( _dataProperties )
   {  // First try to get via data set properties
      const DP *rpDP = getDataProperties();
      if ( rpDP->exists( id ) )
      {
         const DCP &dcp = rpDP->getPropertyByFieldIndex( id );
         if ( DCP::eDEP == dcp.getType() )
         {
            const DEP &dep = static_cast< const DEP & >( dcp );
            DataProperties::EReturn eRtn = rpDP->setValueInBuffer( id,
               dep.getDefaultValue( rpLocClientLocale ),
               (unsigned char *)getDataBuffer(), rpLocClientLocale, false, EMPTY_STRING );
            if ( DataProperties::SUCCESS == eRtn )
            {  // Success
               return;
            }
         }
         // Actually this is a set problem or wrong component - should not be a not
         //  found problem.
         DString msg( I_("comp=") );
         msg += dcp.getName();
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::resetElementValue"),
                         DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
      }
   }

   // Not found in data set properties, so try to access via our own map
   // Not defined in data set properties - try append map
   ComponentPtrIndexMap::const_iterator iter;
   if ( !_dataIndexMap ||
      ( ( iter = _dataIndexMap->find( id ) ) == _dataIndexMap->end() ) )
   {
      DString msg( I_("comp=") );
      msg.appendULong(id);
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::resetElementValue"),
                      DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
   }

   ( (*iter).second )->resetValue( rpLocClientLocale );
}

void Data::resetElementValue( const DString &name,
                              const ClientLocale *rpClientLocale )
{
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX == id )
   {  // No match
      DString msg( I_( "comp=" ) );
      msg += name;
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::resetElementValue"),
                      DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
   }

   resetElementValue( id, rpClientLocale );
}

bool Data::setElementValue(
   unsigned long id,
   unsigned char *binBuff,
   unsigned long buffLength,
   unsigned long &returnLength
   )
{
   if ( _dataProperties )
   {  // First try to get via data dictionary properties
      const DataProperties *rpDP = getDataProperties();
      const DEP *dep =
         static_cast< const DEP * >( &rpDP->getPropertyByFieldIndex( id ) );
      if ( dep->getStoredType() == DEP::BINARY )
      {  // only works for binary types
         DataProperties::EReturn eRtn = rpDP->setValueInBuffer( id, binBuff,
            (unsigned char *)getDataBuffer(), buffLength, returnLength );
         if ( DataProperties::SUCCESS == eRtn )
         {  // Success
            return true;
         }
         else if ( DataProperties::FAILURE == eRtn )
         {
            return false;
         }
      }
      else
      {  // Invalid type
         return false;
      }
   }

   // Not defined in data set properties - try append map
   ComponentPtrIndexMap::const_iterator iter;
   if ( !_dataIndexMap ||
        ( ( iter = _dataIndexMap->find( id ) ) == _dataIndexMap->end() ) )
   {
      DString msg( I_("comp=") );
      msg.appendLong( id );
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getElementValue"),
                        DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
   }

   DataElement *de = static_cast< DataElement * >( (*iter).second );
   if ( de->getProperties() )
   {
      const DEP *dep = static_cast< const DEP * >( de->getProperties() );
      if ( dep && dep->getStoredType() == DEP::BINARY )
      {
         return de->setBinaryValue( binBuff, buffLength, buffLength );
      }
   }

   return false;
}

bool Data::setElementValue(
   const DString &name,
   unsigned char *binBuff,
   unsigned long buffLength
   )
{
   // This method is ignoring length actually copied to internal buffer
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX != id )
   {
      return setElementValue( id, binBuff, buffLength, buffLength );
   }

   DString msg( I_("comp=") );
   msg += name;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::getElementValue"),
                   DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}

void Data::setForceMatching( bool forceMatching )
{
   if ( _dataProperties )
   {
      const DP *rpDP = getDataProperties();
      const DCP* pDCP = 0;

      long lCount = rpDP->getPropertyCount();
      for ( long lIndex = 0; lIndex < lCount; ++lIndex )
      {
         pDCP = &( rpDP->getProperty( lIndex ) );
         if ( DCP::eDEP == pDCP->getType() )
         {
            const DEP* pDEP = static_cast< const DEP* >( pDCP );
            ( const_cast< DEP* >( pDEP ) )->setForceMatching( forceMatching );
         }
      }
   }
}

bool Data::setElementValue(
   unsigned long id,
   const DString &value,
   EAPPEND_MODE eAppend,
   bool displayFormat,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   )
{
   const ClientLocale *rpLocClientLocale =
      rpClientLocale ? rpClientLocale : &getLocale();

   if ( _dataProperties )
   {  // First try to get via data set properties
      const DP *rpDP = getDataProperties();
      DataProperties::EReturn eRtn = rpDP->setValueInBuffer( id, value,
         (unsigned char *)getDataBuffer(), rpLocClientLocale, displayFormat, i18nFormat );
      if ( DataProperties::SUCCESS == eRtn )
      {  // Success
         return true;
      }
      else if ( DataProperties::FAILURE == eRtn )
      {
         return false;
      }
   }

   // Not found in data set properties, so try to access via our own map
   ComponentPtrIndexMap::const_iterator iter;
   if ( _dataIndexMap &&
        ( ( iter = _dataIndexMap->find( id ) ) != _dataIndexMap->end() ) )
   {
      return ( (*iter).second )->setValue( value, true, rpLocClientLocale,
         displayFormat, i18nFormat );
   }
   else
   {
      if ( Data::APPEND_FROM_PROPERTIES == eAppend )
      {
         DEP *dep = PropertyRepository::getInstance()->getField( id,
            *rpLocClientLocale );
         if ( !dep )
         {
            DString msg( I_("comp=") );
            msg.appendLong( id );
            THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::setElementValue"),
                              DIDBRKR_ELEMENT_NOT_FOUND, msg.c_str() );
         }
         DataElement *pDE =
            new DE( value, _getBase(), dep, true, *rpLocClientLocale );
         if ( !pDE )
         {
            THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::setElementValue"),
                           BASE_ALLOC_FAIL );
         }
         pDE->_setName( dep->getName() );
         _addElementToMaps( pDE );
         return true;
      }
   }
   return false;
}

bool Data::setElementValue(
   const DString &name,
   const DString &value,
   EAPPEND_MODE eAppend,
   bool displayFormat,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   )
{
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX != id )
   {  // Already exists so use id version
      return setElementValue( id, value, eAppend, displayFormat, rpClientLocale,
         i18nFormat);
   }

   const ClientLocale *rpLocClientLocale =
      rpClientLocale ? rpClientLocale : &getLocale();

   if ( Data::APPEND_FROM_PROPERTIES == eAppend )
   {
      DEP *dep = PropertyRepository::getInstance()->getField( name,
         *rpLocClientLocale );
      if ( !dep )
      {
         DString msg( I_( "comp=" ) );
         msg.append( name );
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("Data::setElementValue"),
                           DIDBRKR_ELEMENT_NOT_FOUND, msg.c_str() );
      }
      DataElement *pDE =
         new DE( value, _getBase(), dep, true, *rpLocClientLocale );
      if ( !pDE )
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::setElementValue"),
                        BASE_ALLOC_FAIL );
      }
      pDE->_setName( name );
      _addElementToMaps( pDE );
      return true;
   }

   if ( Data::APPEND == eAppend )
   {
      DataElement *pDE =
         new DE( value, _getBase(), NULL, true, *rpLocClientLocale );
      if ( !pDE )
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::setElementValue"),
                        BASE_ALLOC_FAIL );
      }
      pDE->_setName( name );
      _addElementToMaps( pDE );
      return true;
   }

   return false;
}

bool Data::setElementValue( const DString &name, const DString &value,
                            bool appendNew, bool displayFormat,
                            const ClientLocale *rpClientLocale,
                            const DString &i18nFormat )
{
   EAPPEND_MODE eAppend = NO_APPEND;
   if ( appendNew )
   {
      eAppend = APPEND;
   }
   return setElementValue( name, value, eAppend, displayFormat,
      rpClientLocale, i18nFormat );
}

bool Data::setElementValue( unsigned long id, const DString &value,
                            bool appendNew, bool displayFormat,
                            const ClientLocale *rpClientLocale,
                            const DString &i18nFormat )
{
   EAPPEND_MODE eAppend = NO_APPEND;
   if ( appendNew )
   {  // When appending by id, must be associated with properties so can get name.
      eAppend = APPEND_FROM_PROPERTIES;
   }
   return setElementValue( id, value, eAppend, displayFormat, rpClientLocale,
      i18nFormat );
}

bool Data::setElementValueFromHost(
   unsigned long id,
   DString &value
   )
{
   if ( _dataProperties )
   {  // First try to get via data set properties
      const DP *rpDP = getDataProperties();
      DataProperties::EReturn eRtn = rpDP->setValueInBufferFromHost( id, value,
         (unsigned char *)getDataBuffer() );
      if ( DataProperties::SUCCESS == eRtn )
      {  // Success
         return true;
      }
      else if ( DataProperties::FAILURE == eRtn )
      {
         return false;
      }
   }

   // Not found in data set properties, error
   return false;
}

void Data::setRedefine( unsigned long oldId, unsigned long newId )
{
   MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME, I_("Data::setRedefine") );
   PropertyRepository *propRep = PropertyRepository::getInstance();

   if ( propRep )
   {
// Why convert to name here?  Should use Id all the way through ??
      DString oldName, newName;
      propRep->getFieldNameFromId( oldId, oldName );

      if ( oldName.length() == 0 )
      {
         DString msg( I_( "comp=" ) );
         msg.appendLong( oldId );
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::setRedefine" ),
                           DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
      }

      propRep->getFieldNameFromId( newId, newName );

      if ( newName.length() == 0 )
      {
         DString msg( I_( "comp=" ) );
         msg.appendLong( newId );
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::setRedefine" ),
                           DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
      }

      // Load the dataset to make sure all the fields are loaded in the
      // repository and that it actually exists (and is a dataset)
      DataPropertiesImpl *pReplacementProperties =
                                        propRep->getDataSet( newName, getLocale() );

      // If newId is not oldId (we are redefining our data back to its original
      // properties) and newId is not a data_set, that's an error.
      if ( ( 0 == pReplacementProperties ) &&
           ( oldId != newId ) )
      {
         DString msg( I_("oldName=") );
         msg += oldName;
         msg += I_(";newName=");
         msg += newName;
         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("Data::setRedefine"),
                           DIDBRKR_INVALID_REDEFINE, msg.c_str() );
      }

      _setRedefine( oldName, newName );
   }
}

void Data::_setRedefine( const DString &oldName, const DString &newName )
{
// DT17817 Reimplement this
/*
   MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME, I_("Data::_setRedefine") );

   const type_info& typeDataElementProperties = typeid( DataElementProperties );
   DataComponent *dcPtr = NULL;
   const DataProperties *oldDP = static_cast<DP *>(_dataProperties);
   DataComponent *pBase = _getBase();

   PropertyRepository *pPropRep = PropertyRepository::getInstance();
   if ( !pPropRep )
   {
      return;
   }

   // This will ensure that setRedefine is only called on dataSets that came
   // from the repository
   DataPropertiesImpl *pOldProp = pPropRep->getDataSet( getId(), _locale );
   if ( 0 == pOldProp )
   {
      DString msg( I_("dataset=") );
      msg += getId();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_( "Data::_setRedefine" ),
                        DIDBRKR_DATASET_NOT_FOUND, msg.c_str() );
   }

   // Check that the oldName is actually a legitimate part of the original
   // data_set
   if ( !pOldProp->exists( oldName ) )
   {
      DString msg( I_("oldName=") );
      msg += oldName;
      msg += I_(";newName=");
      msg += newName;
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_("Data::_setRedefine"),
                        DIDBRKR_INVALID_REDEFINE, msg.c_str() );
   }

   // Make sure newName can redefine oldName
   if ( !pPropRep->isValidRedefine( oldName, newName ) )
   {
      DString msg( I_("oldName=") );
      msg += oldName;
      msg += I_(";newName=");
      msg += newName;
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_("Data::_setRedefine"),
                        DIDBRKR_INVALID_REDEFINE, msg.c_str() );
   }

   string_vector vecFieldsToReplace;

   ( static_cast<DP *>(_dataProperties ) )->getRedefines( oldName,
                                                          vecFieldsToReplace );

   if ( 0 == vecFieldsToReplace.size() )
   {

      // If it's empty, then this Data object has never been redefined
      // Initialize the set with the field
      vecFieldsToReplace.insert( vecFieldsToReplace.begin(), oldName );
   }

   // Spin through the list of fields that will be replaced and save off a
   // string that is the combination off all the values.
   DString dstrRedefinedValue;
   string_vector::iterator iterReplaceFields = vecFieldsToReplace.begin();
   while ( vecFieldsToReplace.end() != iterReplaceFields )
   {
// DTWK test to make sure this returns values that are the correct length for
// all types (STRING, DECIMAL, DATE, etc)
      dstrRedefinedValue.append( getElementValue( *iterReplaceFields ).c_str() );
      ++iterReplaceFields;
   }

   // Create a new, separate DataProperties object for this Data object.
   // Accessing the _pImpl pointer is necessary to keep the DataProperties
   // object from just getting the same pointer from the repository.
   DataPropertiesImpl *newDPI = new DataPropertiesImpl( *( oldDP->_pImpl ) );

   DataPropertiesImpl *pReplacementProperties =
      pPropRep->getDataSet( newName, _locale );

   // Add the new fields into the DPI and
   // remove the fields out of the new DPI that will be replaced
   if ( pReplacementProperties )
   {
      // This implies that we are redefining our data to a dataset

      // Do length check between the original redefinable field and the
      // redefining dataset.
      DataElementProperties *pRedefinableProps =
         dynamic_cast< DataElementProperties * >(
                                    pPropRep->getPropsPtr( oldName, &_locale ) );

      if ( pRedefinableProps->getMaxLength() !=
           pReplacementProperties->getTotalMaxLength() )
      {
         DString msg( I_( "oldName=" ) );
         msg += oldName;
         msg += I_( ";newName=" );
         msg += newName;
         msg += I_( ";oldLength=" );
         msg.appendLong( pRedefinableProps->getMaxLength() );
         msg += I_( ";newLength=" );
         msg.appendLong( pReplacementProperties->getTotalMaxLength() );

         THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                           I_("Data::_setRedefine"),
                           DIDBRKR_REDEFINE_LENGTH_MISMATCH, msg.c_str() );
      }

      newDPI->_redefineProperties( oldName, pReplacementProperties );
   }
   else
   {
      // This implies that we are redefining our data to back to our original
      // single field
      newDPI->_redefineProperties( oldName );
   }

   // Setup the string stream that we will use to fill the info for our new
   // elements
   i_istringstream valueStream( dstrRedefinedValue );

   ComponentPtrVector tempVector;

   // Add in the new elements just before the ones we are about to remove.
   // Add them in backwards because the order is reversed when we do adds this
   // way.
   // Also stream in the element with data we've saved off earlier
   if ( pReplacementProperties )
   {
      // This implies that we are redefining our data to a dataset
      for ( int iIndex = 0; iIndex < pReplacementProperties->getPropertyCount();
            ++iIndex )
      {

         DataComponentProperties &replaceDCP =
            const_cast< DCP & >( pReplacementProperties->getProperty(
                                                                     iIndex ) );
         _addRedefinedElement( replaceDCP, tempVector, valueStream, pPropRep );
      }

      // Make sure the vector is not reallocated in the middle of the
      // insertions. This should ensure that our iterator is still valid even
      // though we are adding elements.
      _dataVector.reserve( _dataVector.size() +
                              pReplacementProperties->getPropertyCount() +
                              vecFieldsToReplace.size() );
   }
   else
   {
      // This implies that we are redefining our data to back to our original
      // single field
      _addRedefinedElement(
                     *( pPropRep->getPropsPtr( oldName ) ),
                     tempVector, valueStream, pPropRep );

      // Make sure the vector is not reallocated in the middle of the
      // insertions. This should ensure that our iterator is still valid even
      // though we are adding elements.
      _dataVector.reserve( _dataVector.size() + 1 +
                              vecFieldsToReplace.size() );
   }

   // Obtain the position of the elements we are going to remove (which also is
   // the position of the elements we want to add)
   ComponentPtrVector::iterator iterAddRemovePos =
                                findInVector( *( vecFieldsToReplace.begin() ) );

   // Add in the new elements just before the ones we are about to remove.
   // Add the elements in backwards because their order will be reversed by
   // the insertion process
   ComponentPtrVector::iterator iterTemp = tempVector.end();

   while ( tempVector.begin() != iterTemp )
   {
      --iterTemp;
      _dataVector.insert( iterAddRemovePos, *iterTemp );
   }

   // Remove the DataElements and delete them
   for ( string_vector::iterator iterRemove = vecFieldsToReplace.begin();
         iterRemove != vecFieldsToReplace.end(); ++iterRemove )
   {
      ComponentPtrVector::iterator iterVecRemove = findInVector( *iterRemove );
      unsigned long lFieldId = ULONG_MAX;
      if ( _dataVector.end() != iterVecRemove )
      {
         lFieldId =
            pPropRep->getFieldIdFromName(
               ( *iterVecRemove )->getProperties()->getId() );
         delete *iterVecRemove;

         _dataVector.erase( iterVecRemove );
      }
      else
      {
// DTWK throw?
      }

      if ( ULONG_MAX != lFieldId &&
           _dataIndexMap )
      {
         _dataIndexMap->erase( lFieldId );
      }
   }

   // Delete the old DataPropertiesImpl if it was not from the repository.
   if ( !( ( dynamic_cast< DP * >( _dataProperties ) )->_fUsingRepository ) )
   {
      delete ( dynamic_cast< DP * >( _dataProperties ) )->_pImpl;
   }

   // Replace the old properties with the new one
   dynamic_cast< DP * >( _dataProperties )->_pImpl = newDPI;

   // This will cause the DPI to be deleted when the Data object goes.
   ( dynamic_cast< DP * >( _dataProperties ) )->setUsingRepository( false );

   // Make sure m_nextId is still ok.
   _getNextId();
*/
}

void Data::setRepeatCount( const DString &repeatSize )
{
   setRepeatCount( convertToULong( repeatSize ) );
}

void Data::setRepeatCount( unsigned long repeatSize )
{
   TRACE_METHOD( CLASS_NAME, I_("setRepeatCount( unsigned long )") );
   if ( !_repeatData )
   {
      _repeatData = new RepeatPtrVector;
      if ( !_repeatData )
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::setRepeatCount"),
                        BASE_ALLOC_FAIL );
      }
   }
   unsigned long oldRepeatSize = _repeatData->size();
   if ( 0 == oldRepeatSize )
   {
      _repeatData->reserve( repeatSize );
      for ( unsigned long count = 0; count < repeatSize; ++count )
      {
         _repeatData->push_back( ( Data * ) NULL );
      }
   }
   else
   {
      _repeatData->resize( repeatSize );
      if ( repeatSize > oldRepeatSize )
      {
         for ( unsigned long cnt = oldRepeatSize; cnt < repeatSize; ++cnt )
         {
            (*_repeatData)[ cnt ] = ( Data * ) NULL;
         }
      }
   }
}

void Data::setLocale( const ClientLocale& clientLocale )
{
   if ( m_pLocale )
   {
      delete m_pLocale;
   }

   const type_info& typeData = typeid( Data );
   m_pLocale = new ClientLocale( clientLocale );

   if ( _dataIndexMap )
   {
      for ( ComponentPtrIndexMap::iterator iter = _dataIndexMap->begin();
            iter != _dataIndexMap->end();
            ++iter )
      {
         if ( typeData == typeid( *( ( *iter ).second ) ) )
         {
            Data *pData = static_cast< Data* >( ( *iter ).second );
            pData->setLocale( clientLocale );
         }
      }
   }

   if ( _repeatData )
   {
      for ( unsigned int i = 0; i < _repeatData->size(); ++i )
      {
         if ( typeData == typeid( ( *_repeatData )[ i ] ) )
         {
            Data *pData = static_cast< Data* >( ( *_repeatData )[ i ] );
            pData->setLocale( clientLocale );
         }
      }
   }
}

bool Data::setValues( const DString &idiString, bool appendNew,
                      bool ignoreOnNoAppend,
                      const ClientLocale *pClientLocale )
{
   TRACE_METHOD( CLASS_NAME,
           I_("setValues( const DString &, bool, bool )") );
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &getLocale();
   DString key;
   DString value;
   int length = idiString.length();
   int start = 0;
   DString::size_type separatorPosition;
   DString::size_type terminatorPosition;
   bool done = false;
   bool doesExist = true;
   bool allOK = true;
   bool matchesFound = false;
   DataComponent *pBase = _getBase();

   while( !done )
   {
      // Stop if at end-of-string
      if ( start >= length - 1 )
      {
         return allOK;
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

         // Check if the key indicates a replacement but doesn't exist
         doesExist = exists( key );
         if ( !doesExist  &&  !appendNew  &&  !ignoreOnNoAppend )
         {
            allOK = false;
         }

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

         if ( doesExist )
         {
            matchesFound = true;
            if ( !setElementValue( key, value, false, true, pLocClientLocale ) )
            {
               allOK = false;
            }
         }
         else if ( appendNew )
         {
            DataElement *pDE = new DE( value, pBase, 0, true, *pLocClientLocale );
            if ( !pDE )
            {
               THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::setValues"),
                              BASE_ALLOC_FAIL );
            }

            pDE->_setName( key );
            _addElementToMaps( pDE );
            matchesFound = true;
         }

         start = terminatorPosition + 1;
      }
   }

   if ( !matchesFound )
   {
      return false;
   }

   return allOK;
}

bool Data::setValues( const Data &data, bool appendNew, bool ignoreOnNoAppend )
{
   bool allOK = true;
   DString tmpStr;
   ClientLocale clientLocale( data.getLocale() );

   if ( _dataProperties || appendNew )
   {
      const DP *rpDP = data.getDataProperties();

      // Check for a named data object ( which will have a valid pointer )
      if ( rpDP )
      {
         long lNumProps = rpDP->getPropertyCount();

         for ( long lIndex = 0; lIndex < lNumProps; ++lIndex )
         {
            const DCP *pDCP = &( rpDP->getProperty( lIndex ) );

            if ( DCP::eDEP == pDCP->getType() )
            {
               if ( !setElementValue( pDCP->getId(),
                  data.getElementValue( pDCP->getId(), tmpStr ), appendNew, false,
                  &clientLocale ) )
               {
                  if ( !ignoreOnNoAppend )
                  {
                     allOK = false;
                  }
               }
            }
         }
      }
   }

   if ( data._fieldNameMap )
   {
      FieldNameMap::const_iterator fromMapIter,
                                      endMapIter = data._fieldNameMap->end();
      for ( fromMapIter = data._fieldNameMap->begin();
            fromMapIter != endMapIter;
            ++fromMapIter )
      {
         if ( !setElementValue( (*fromMapIter).first,
            data.getElementValue( (*fromMapIter).first, tmpStr ), appendNew,
            true, &clientLocale ) )
         {
            if ( !ignoreOnNoAppend )
            {
               allOK = false;
            }
         }
      }
   }
   return allOK;
}

void Data::unauthorizedSetElementValue(
   unsigned long id,
   const DString &value
   )
{
   if ( _dataProperties )
   {  // First try to get via data set properties
      const DP *rpDP = getDataProperties();
      rpDP->unauthorizedSetValueInBuffer( id, value, (unsigned char *)getDataBuffer() );
      return;
   }

   DString msg( I_("comp=") );
   msg.appendLong( id );
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
      I_( "Data::unauthorizedSetElementValue" ), DIDBRKR_ELEMENT_NOT_FOUND,
      msg.c_str() );
}

void Data::unauthorizedSetElementValue(
   const DString &name,
   const DString &value
   )
{
   unsigned long id = getFieldIdFromName( name );
   if ( ULONG_MAX != id )
   {  // must exist
      unauthorizedSetElementValue( id, value );
      return;
   }
   DString msg( I_("comp=") );
   msg += name;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
      I_( "Data::unauthorizedSetElementValue" ), DIDBRKR_ELEMENT_NOT_FOUND,
      msg.c_str() );
}

//******************************************************************************
//              Private Methods
//******************************************************************************

void Data::_addElementToMaps( DataElement *newDE )
{
   unsigned long id = newDE->getId();
   if ( ULONG_MAX == id )
   {  // Need to set id
      id = _getNextId();
      if ( id != ULONG_MAX )
      {
         newDE->_setId( id );
      }
   }

   if ( !_fieldNameMap )
   {
      _fieldNameMap = new FieldNameMap;
      if ( !_fieldNameMap )
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::addElementToMaps"),
                        BASE_ALLOC_FAIL );
      }
   }
   if ( !_dataIndexMap )
   {
      _dataIndexMap = new ComponentPtrIndexMap;
      if ( !_dataIndexMap )
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::addElementToMaps"),
                        BASE_ALLOC_FAIL );
      }
   }
   (*_fieldNameMap)[ newDE->getName() ] = id;
   ( *_dataIndexMap )[ id ] = newDE;
}

unsigned long Data::_getNextId()
{
   if ( m_nextId + 1 < MAX_USER_ID )
   {
      return ++m_nextId;
   }
   return ULONG_MAX;
}

Data::Data( DP *properties ) : DC( NULL_STRING , properties, false ),
   _repeatData( NULL ), _dataIndexMap( NULL ),
   _fieldNameMap( NULL ),
   m_nextId( 0L ),
   m_pLocale( 0 ),
   _pDataBuffer( 0 )
{
   TRACE_CONSTRUCTOR( CLASS_NAME, "Data::Data( DP *properties )" );
   _initialize( properties );
}

Data::Data( const Data &copy, DataComponent *pBase ) :
   DC( pBase ), _repeatData( NULL ),
   _dataIndexMap( NULL ), m_nextId( 0L ),
   _fieldNameMap( NULL ),
   m_pLocale( 0 ),
   _pDataBuffer( 0 )
{
   TRACE_CONSTRUCTOR( CLASS_NAME, "Data::Data( const Data &copy, "
                                  "DataComponent *pBase )" );
   if ( m_pLocale )
   {
      delete m_pLocale;
      m_pLocale = 0;
   }

   if ( copy.m_pLocale )
   {
      m_pLocale = new ClientLocale( *( copy.m_pLocale ) );
   }

   if ( copy._dataProperties )
   {
      _dataProperties =
        new DP( *static_cast<DP *>((const_cast<DCP *>(copy._dataProperties))));
      if ( !_dataProperties )
      {
         THROWFROMBASE( DIDBRKR_COMPONENT_NAME,
                     I_("Data::Data( const Data &copy, DataComponent *pBase )"),
                        BASE_ALLOC_FAIL );
      }
   }
   else
   {
      _dataProperties = NULL;
   }

   *this = copy;
}

Data::Data( DataComponent *pBase ) :
   DC( pBase ), _repeatData( NULL ),
   _dataIndexMap( NULL ), m_nextId( 0L ),
   _fieldNameMap( NULL ),
   m_pLocale( 0 ),
   _pDataBuffer( 0 )
{
   TRACE_CONSTRUCTOR( CLASS_NAME, "Data::Data( DataComponent *pBase )" );
   _dataProperties = NULL;
}

Data::Data( const DString &propertiesId, const DString &idiString,
            bool appendNew, bool ignoreOnNoAppend,
            DataComponent *pBase, const ClientLocale* pClientLocale ) :
   DC( pBase ), _repeatData( NULL ), _dataIndexMap( NULL ),
   _fieldNameMap( NULL ),
   m_nextId( 0L ), m_pLocale( 0 ), _pDataBuffer( 0 )
{
   TRACE_CONSTRUCTOR( CLASS_NAME, "Data::( const DString &propertiesId, "
                              "const DString &idiString, bool appendNew, "
                              "bool ignoreOnNoAppend, DataComponent *pBase )" );

   m_pLocale = new ClientLocale( *pClientLocale );

   _dataProperties = new DP( propertiesId, *m_pLocale );
   if ( !_dataProperties )
   {
      THROWFROMBASE( DIDBRKR_COMPONENT_NAME,
                     I_("Data::( const DString &, const DString &, bool ," )
                     I_(" bool , DataComponent *)"),
                     BASE_ALLOC_FAIL );
   }

   _initialize( static_cast<DP *>(_dataProperties) );

   if ( !setValues( idiString, appendNew, ignoreOnNoAppend ) )
   {
      DString msg( I_("props=") );
      msg += propertiesId;
      // Throw if some keys or values are bad...
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                        I_("Data::( const DString &, const DString &, bool , ")
                        I_("bool , DataComponent *)"),
                        DIDBRKR_CANT_SET_VALUES, msg.c_str() );
   }
}

void Data::_addRedefinedElement( DataComponentProperties &replaceDCP,
                                 ComponentPtrVector &tempVector,
                                 std::istringstream &valueStream,
                                 PropertyRepository *pPropRep )
{
   DataComponentProperties *pReplaceDCP = &replaceDCP;
   DataComponent *newComponentPtr;

   if ( ( pReplaceDCP->getType() == DCP::eDP ) && pReplaceDCP->isRepeatable() )
   {
      DCP *dcProps = const_cast< DCP * >( pReplaceDCP );
      DataProperties *dataProps =
         static_cast< DataProperties * >( dcProps );
      DataProperties *newDataProps = new DataProperties( *dataProps );
      newComponentPtr = new Data( newDataProps );

      // Stream the user values into our new data component
      valueStream >> *( dynamic_cast< Data * >( newComponentPtr ) );
   }
   else if ( DCP::eDEP != pReplaceDCP->getType() )
   {
      newComponentPtr = new Data( pReplaceDCP->getId() );

      // Stream the user values into our new data component
      valueStream >> *( dynamic_cast< Data * >( newComponentPtr ) );
   }
   else
   {
      newComponentPtr =
         new DE( EMPTY_STRING, _getBase(),
                 static_cast< DEP * >( const_cast<DCP *>( pReplaceDCP ) ),
                 true, getLocale() );

      // Stream the user values into our new data component
      valueStream >> *( dynamic_cast< DE * >( newComponentPtr ) );
   }

   // Place the new component into our properties
   tempVector.insert( tempVector.end(), newComponentPtr );

   if ( _dataIndexMap )
   {
// DTWK yak if return is -1
      ( *_dataIndexMap )[
         pPropRep->getFieldIdFromName(
            newComponentPtr->getProperties()->getName() ) ] =
               newComponentPtr;
   }
}

void Data::_appendRepeat( Data *pData )
{
   if ( !_repeatData )
   {
      _repeatData = new RepeatPtrVector;
   }

   _repeatData->push_back( pData );
}

void Data::_deleteDataIndexMapContents()
{
   TRACE_METHOD( CLASS_NAME, I_("_deleteDataIndexMapContents()") );
   if ( _dataIndexMap )
   {
      for ( ComponentPtrIndexMap::iterator iter = _dataIndexMap->begin();
            iter != _dataIndexMap->end();
            ++iter )
      {
         delete (*iter).second;
      }
      _dataIndexMap->clear();
   }
}

DataComponent* Data::_getDataElement( unsigned long lElement,
                                      GET_DE_INIT eInit ) const
{
   if ( !_dataProperties )
   {
      return 0;
   }

   if ( _dataIndexMap )
   {
      ComponentPtrIndexMap::iterator iter = _dataIndexMap->find( lElement );

      if ( _dataIndexMap->end() != iter )
      {
         return ( *iter ).second;
      }
   }

   return 0;
}

DataComponent* Data::_getDataElementByIndex( long lIndex,
                                             GET_DE_INIT eInit ) const
{
   if ( _dataProperties )
   {
      const DP *rpDP = getDataProperties();

      if ( rpDP->getType() == DCP::eDP )
      {
         try
         {
            const DCP* pProp = &( rpDP->getProperty( lIndex ) );

            if ( pProp )
            {
               return _getDataElement( pProp->getId(), eInit );
            }
         }
         catch ( ... )
         {
            return 0;
         }
      }
   }

   return 0;
}

//******************************************************************************
//
// ^PRIVATE METHOD : initialize
//
// ^DESCRIPTION : Initializes the Data object, creating pointers in
//                _dataIndexMap to match nested Data or repeats in the
//                properties parameter.
//
// ^PARAMETERS  : properties - (in/out) pointer to a DataProperties object,
//                containing descriptions of all of the elements this Data
//                object should contain.
//
// ^RETURNS     : None
//
// ^THROWS      : ConditionException& - out of memory
//
//
//******************************************************************************
void Data::_initialize( DP *properties, bool initElements )
{
   TRACE_METHOD( DIDBRKR_COMPONENT_NAME, I_("Data::_initialize") );
   const DCP *compProp = 0;
   DataComponent *pComponentPtr = NULL;

   DataComponent * pBase = _getBase();

   if ( _dataProperties != properties )
   {
      delete _dataProperties;
      _dataProperties = (DCP *)properties;
   }

   // Insert the elements for the defined data...
   unsigned long numValues = properties->getPropertyCount();

   if ( _pDataBuffer )
   {
      delete [] _pDataBuffer;
   }

   _pDataBuffer = (I_CHAR *)new char[ properties->getFixedByteLength() ];

   _deleteDataIndexMapContents();

   for ( unsigned long counter = 0;  counter < numValues;  ++counter )
   {
      compProp = &(properties->getProperty( counter ));
      unsigned long ulId = compProp->getId();

      if ( DCP::eDEP != compProp->getType() )
      {
         if ( compProp->isRepeatable() )
         {
            DCP *dcProps = const_cast< DCP * >( compProp );
            DataProperties *dataProps = static_cast< DataProperties * >(dcProps);
            DataProperties *newDataProps = new DataProperties( *dataProps );
            pComponentPtr = new Data( newDataProps );
         }
         else
         {
            pComponentPtr = new Data( ulId );
         }
         if ( !pComponentPtr )
         {
            THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::_initialize"),
                           BASE_ALLOC_FAIL );
         }
         // Need to put repeats, nested data in our map for future reference
         if ( !_dataIndexMap )  // Create if needed only
         {
            _dataIndexMap = new ComponentPtrIndexMap;
            if ( !_dataIndexMap )
            {
               THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("Data::_initialize"),
                              BASE_ALLOC_FAIL );
            }
         }
         ( *_dataIndexMap )[ ulId ] = pComponentPtr;
      }
      else
      {
         if ( initElements )
         {
            resetElementValue( ulId );
         }
         else if ( ULONG_MAX == ulId )
         {  // Invalid condition, right?
            assert( 0 );
         }
      }
   }
}

Data * Data::_removeRepeat( long lIndex )
{
   Data *pDataRet = 0;
   if ( _repeatData )
   {
      pDataRet = _repeatData->at( lIndex );
      _repeatData->erase( _repeatData->begin() + lIndex );
   }

   return pDataRet;
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/data.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:16   kovacsro
// Initial revision.
// 
//    Rev 1.76   25 Feb 2002 12:39:58   dt14177
// findRepeatIndex(): When the value passed in had
// leading spaces, it wasn't found in the data
// object.
// 
//    Rev 1.75   Oct 23 2001 13:27:58   DT11159
// Fixed setValues() so that it works when appending new fields.
//
//    Rev 1.74   Sep 21 2001 16:19:22   DT11159
// Made changes to support the new bin file format.
//
//    Rev 1.73   Aug 03 2001 13:46:48   DT11159
// Added setAsUnsignedCharBuffer( ) method.
// Rewrote operator== because it did not compare repeats and did not compare appended elements.
// Added internal classes DataStream, BufferStream, InStream, and OutStream (contributed by Doug Beatty).
// Rewrote streaming operators and getAsUnsignedCharBuffer( ) using the DataStream class.
//
//
//    Rev 1.72   Jul 27 2001 15:26:10   DT11159
// Fixed two bugs (see buggit #180 and #181).
//
// Fixed Data::get/setElementValue for binary data.
// Not that we can do anything about it now, but the names
// of  DataElementProperty::getProperty and
// DataElementProperty::getPropertyByFieldIndex are
// confusing.
//
// Fixed Data >> operator for unicode so that it matches
// the logic of the Data >> operator for ascii.
//
//    Rev 1.72   Jul 27 2001 14:56:46   DT11159
// Fixed two bugs (see buggit #180, #181).
// The first is that getElementValue and setElementValue
// were not working for binary data. This was fixed by calling
// DataElementProperties::getPropertyByFieldIndex( ) rather
// than DataElementProperties:getProperty( ). The names of
// these methods are rather confusing.
//
// The second bug was that the operator to stream unicode
// data into a Data object throws an exception. This was fixed
// by making the unicode >> operator match the ascii >> operator.
//
//    Rev 1.71   Jul 05 2001 14:47:16   dt24433
// Fixed copy constructor to correctly copy appended DataElements
// that have associated properties.  (Was losing properties and getting
// new ID).
//
//    Rev 1.70   Jul 05 2001 10:36:38   dt24433
// Fixed setElementValue( stringName, binbuff,...) to call
// setElementValue( id, binbuff...) instead of getElementValue...
//
//    Rev 1.69   May 18 2001 14:59:46   dt24433
// Updated binary element support, added setElementFromHost to help Canada performance
// (or any databroker that won't stream data in directly through fixed buffers.
//
//    Rev 1.68   Mar 26 2001 09:30:52   dt24433
// Changed appendRepeatData to return true if repeatable and no repeats,
// instead of throwing an error.
//
//    Rev 1.67   Mar 22 2001 16:32:32   dt24433
// Implemented unauthorizedSetElementValue.
//
//    Rev 1.66   Mar 21 2001 11:48:56   dt24433
// Removed commented code.
//
//    Rev 1.65   Mar 21 2001 11:35:42   dt24433
// Fix for streaming in to data object with no repeats.
// Removed public methd getDataElement.
// Replaced use of getDataElement in findRepeatIndex.
// Add getElementProperties, getFieldNameFromId, and isDefault.
//
//    Rev 1.64   Mar 09 2001 11:26:08   dt24433
// Changed getAllValues DString useage to use clear instead
// of = and append instead of += for performance.
//
//    Rev 1.63   Mar 06 2001 18:41:24   dt24433
// Append with property fixes.
//
//    Rev 1.62   Mar 06 2001 16:49:06   dt24433
// Fixed setElementValue to return true when appending.
//
//    Rev 1.61   Mar 02 2001 16:12:18   dt24433
// Fixed getFieldIdFromName to properly get id from appended elements when no properties exist.
//
//    Rev 1.60   Mar 02 2001 15:04:26   dt24433
// Fixed code inside #ifdef DST_UNICODE that would not compile.
//
//    Rev 1.59   Mar 02 2001 14:41:46   dt24433
// Changed use of DataMap to FieldNameMap - only dataIndexMap will have DataComponent pointers now.
// Factored code so by Name versions of methods typically call by Id methods.
// Removed code supporting DataElements to/from properties.
// DataElements are no longer used or supported for property based elements for memory/performance reasons.
//
//    Rev 1.58   Jan 22 2001 12:06:06   dt24433
// Changed getAsUnsignedCharBuff to not use streams for performance.  Changed to use getFixedByteLength in most places.
//
//    Rev 1.57   Jan 19 2001 16:55:12   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.55   Jan 09 2001 13:27:54   dt24433
// Changed operator>> to get DataPropertiesImpl to use for all repeats.
//
//    Rev 1.54   Jan 04 2001 16:46:38   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.53   Nov 22 2000 07:04:36   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.52   Oct 12 2000 13:00:46   dt17817
// Fix Data::exists( long id ) to find dynmaically added elements
//
//    Rev 1.51   Oct 03 2000 10:52:40   dt17817
// Fix instances of the client/market being lost when setting the clientlocale
//
//    Rev 1.50   Sep 27 2000 13:43:24   dt17817
// Remove ClientLocale from DataCompoentProperties
//
//    Rev 1.49   Sep 05 2000 06:19:44   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.47   Aug 24 2000 08:26:46   dtwk
// ConditionException::getCode() was changed to non-const
//
//    Rev 1.46   May 31 2000 09:32:34   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.45   Apr 20 2000 10:39:34   dtwk
// Trim some unneeded work in the copy constructor
//
//    Rev 1.44   Jan 10 2000 15:19:50   dtwk
// If you called setElementValue with an id, and fAppendNew = true,
// you couldn't call getElementValue with an id.  You had to pass in
// the component's string name.
//
//    Rev 1.43   Jan 10 2000 11:20:56   dtwk
// Add a getElementValue method that will return a
// reference to a passed in string rather than a newly
// allocated string
//
//
//    Rev 1.42   Jan 07 2000 14:59:26   dtwk
// Fix condition exception to correctly identify it's origin
//
//    Rev 1.41   Dec 16 1999 11:39:38   dtwk
// Add moveRepeatData method
//
//    Rev 1.40   Nov 29 1999 07:31:38   dtwk
// Add support for redefines
//
//    Rev 1.39   Oct 07 1999 08:06:58   DCYK
// Have _setRedefine throw DIDBRKR_INVALID_REDEFINE
// exception.
//
//
//    Rev 1.38   Oct 06 1999 11:35:06   DCYK
// Add support for redefines.
//
//
//    Rev 1.37   Oct 04 1999 10:23:08   DCYK
// Threading fixes.
//
//
//    Rev 1.36   Sep 23 1999 14:14:44   DCYK
// Remove calls to MAKEFRAME
//
//
//    Rev 1.35   Aug 19 1999 15:03:14   DCYK
// More minor performance improvements.
//
//
//    Rev 1.34   Aug 06 1999 14:20:34   DCYK
// Performance improvements.
//
//
//    Rev 1.33   Aug 05 1999 16:37:46   DCYK
// Performance improvements from Tom H. & Michael M.
//
//
//    Rev 1.32   Jul 29 1999 15:13:42   DCYK
// Very minor performance improvement in setValues( Data & ).
//
//
//    Rev 1.31   Jul 29 1999 10:32:46   DCYK
// Minor performance improvements.
//
//    Rev 1.30   Jul 28 1999 14:18:46   DCYK
// Performance improvements.
//
//
//    Rev 1.29   Jul 26 1999 09:49:40   DCYK
// Change "USen" to "enUS".
//
//
//    Rev 1.28   Jul 08 1999 11:09:00   DCYK
// Fixed bug in getComponent that would throw an unhandled exception.
//
//
//    Rev 1.27   Jun 29 1999 09:45:30   DCYK
// Added setLocale methods.
// Fixed minor bugs.
//
//
//    Rev 1.26   Jun 25 1999 16:18:18   DCYK
// Fix minor bugs with id numbers.
//
//
//    Rev 1.25   24 Jun 1999 16:03:42   DCYK
// Fix minor bugs.
//
//
//    Rev 1.24   Jun 23 1999 12:06:44   DCYK
// Set passed-in id in getId.
//
//
//    Rev 1.23   Jun 23 1999 09:57:12   DCYK
// Fix problem with setValues on empty Data objects.
//
//
//    Rev 1.22   Jun 18 1999 09:33:42   DCYK
// Add ID's for dynamically created elements.
//
//
//    Rev 1.21   Jun 14 1999 16:33:24   DCYK
// More clean up.
//
//
//    Rev 1.20   Jun 14 1999 16:16:56   DCYK
// Make value comparisons of DECIMAL values
// correct in "findRepeatIndex"
//
//
//    Rev 1.19   Jun 14 1999 09:54:52   DCYK
// Use javalocale object to get default locales.
//
//    Rev 1.18   Jun 06 1999 13:22:50   DTWK
// Cleanup I18N formatting
//
//    Rev 1.17   May 26 1999 17:20:52   DCYK
// Add support for getting & setting numerical id's.
//
//
//    Rev 1.16   May 26 1999 16:09:32   DCYK
// Add ability to pass in strings to getElementValue.
//
//    Rev 1.15   May 24 1999 15:17:22   DTWK
// Re-const some more methods
//
//    Rev 1.14   May 24 1999 13:01:18   DTWK
// Make some methods const again
//
//    Rev 1.13   May 24 1999 10:41:14   DTWK
// Add internationalized formatting and new types (date, decimal, percent, currency)
//
//    Rev 1.12   May 18 1999 09:40:40   DCYK
// Fix some problems with index numbers.
//
//
//    Rev 1.11   May 14 1999 11:29:32   DTWK
// Add ability to access Data through Repository Group/Field Id's
//
//    Rev 1.10   May 07 1999 13:30:16   DCYK
// If component not found, put component
// name in condition, not view name.
//
//
//    Rev 1.9   May 05 1999 13:10:40   DCYK
// Change getVectorIndex calls to
// getVectorIndexFromName to allow
// re-use of element properties.
//
//
//    Rev 1.8   Apr 20 1999 16:49:24   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.7   09 Mar 1999 12:50:24   DT14177
// Unicode-izing
//
//    Rev 1.6   Mar 05 1999 10:25:14   DCYK
// Changes for I18N.
//
//
//    Rev 1.5   Feb 11 1999 15:03:38   DCYK
// Add support for binary elements.
//
//
//    Rev 1.4   Jan 28 1999 14:03:40   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.4   Jan 28 1999 13:44:20   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Aug 04 1998 10:01:46   dcyk
// Fixed setValues so it doesn't croak
// on a repeat record.
//
//
//    Rev 1.0   29 Jul 1998 20:30:32   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.30   Jul 23 1998 07:59:40   dcyk
// Performance improvements
// from Paul D.
//
//
//    Rev 1.29   Jul 08 1998 10:44:44   dcyk
// Fix problem in findRepeatIndex.
//
//
//    Rev 1.28   Jul 08 1998 10:05:12   dcyk
// Performance improvements.
//
//
//    Rev 1.27   Jun 18 1998 11:10:52   dcyk
// Remove tracing.
//
//
//    Rev 1.26   May 27 1998 15:31:02   dt27994
// Changed TRACE_METHOD calls to use class name instead of component name.
//
//    Rev 1.25   May 04 1998 14:47:18   dcyk
// Fixed appendRepeatData to correctly
// overwrite the fixed area, when told to.
//
//
//    Rev 1.24   Apr 16 1998 17:10:14   dcyk
// Enhanced data destructor.
//
//
//    Rev 1.23   Apr 01 1998 10:46:54   dcyk
// Fix TRACE_CONSTRUCTOR and
// TRACE_DESTRUCTOR calls.
//
//
//    Rev 1.22   Mar 25 1998 12:15:26   dcyk
// Fix outstream.
//
//
//    Rev 1.19   Feb 20 1998 15:27:46   dcyk
// Don't use a try/throw block in
// setElementValue.
//
// Added function getId() to return the
// DataProperties id.  Returns "" if the
// Data object has no properties.
//
//
//    Rev 1.18   Feb 13 1998 10:42:42   dcyk
// Fixed problem in setElementValue to call
// exists instead of letting it throw and catch
// an exception.
//
// Fixed problem in findInVector to return the
// end() vector if the name was not in the
// dataVector.
//
// Fixed the = operator to assign the properties
// of the "from" data object to the "to" object.
//
//
//    Rev 1.17   Nov 12 1997 14:01:12   dcyk
// Fixed the exists function so it can find
// Repeat_Record components.
//
//
//    Rev 1.16   Nov 10 1997 14:46:36   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.15   23 Oct 1997 08:16:56   dcyk
// Modified setValues( Data & ), to check if
// an element exists before trying to set it.
// This eliminates two throw-catch pairs
// for each element.
//
//
//    Rev 1.14   22 Oct 1997 10:27:44   dcyk
// Changed setValues( Data & ), to iterate
// through the elements instead of creating
// an IDI string, then passing that to the other
// setValues( string & ) function.
//
//
//    Rev 1.13   02 Oct 1997 15:50:36   dcyk
// Fixed problem in copy constructor, where
// elements in the _dataMap ( those without
// properties ), were not getting copied.
//
//
//    Rev 1.12   23 Sep 1997 16:25:36   dcyk
// Store dataElements in a vector, not a map.
// This eliminates a string for every element.
//
//
//    Rev 1.11   17 Sep 1997 14:07:12   dcyk
// Fixed problem in appendRepeatData where
// it was throwing every time!
//
//
//    Rev 1.10   16 Sep 1997 16:01:56   dcyk
// Made removeAllRepeats throw if the data
// object is not repeatable.
//
//
//    Rev 1.7   09 Sep 1997 16:34:52   dcyk
// Reduce memory footprint.
//
//
//    Rev 1.5   08 Sep 1997 14:25:34   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.4   05 Sep 1997 07:56:06   dcyk
// Removed most calls to MAKEFRAME, use
// TRACE_METHOD & THROWFROMFILE
// instead.
//
//
//    Rev 1.3   07 Aug 1997 15:04:22   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.2   24 Jul 1997 09:32:44   dcyk
// Use new tracing stuff.
//
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.1   08 Jul 1997 09:01:34   dcyk
// getAllValues takes flags, not booleans.
// assignment op no longer throws on
// different properties.
// Added STL casting operators and RTTI.
//
//
//    Rev 1.0   Jun 13 1997 16:31:20   DTWK
//
//
//    Rev 1.20   13 Jun 1997 16:19:58   dcyk
// Added conditions, conditionExceptions &
// tracing.  Added repeat iterators.  Fixed
// some masking problems.
//
//
//    Rev 1.19   Jun 08 1997 18:48:52   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.18   05 Jun 1997 17:56:10   dcyk
// Added default parameter to getValue.
// Added mask & substitute parameters
// to getElementValue & getAllValues.
//
//
//    Rev 1.17   May 29 1997 09:48:28   dcyk
// Added support for substitute values
// and masking.
//
//
//    Rev 1.16   May 09 1997 16:41:50   dcyk
// Improved standards compliance.
//
// Added private methods deleteDataMapContents
// and deleteRepeatDataContents.
//
//
//    Rev 1.15   May 06 1997 10:12:18   dcyk
// Don't throw on assignment if one object
// has properties and the other doesn't.  Do
// throw if they both have properties, but the
// props don't match.
//
//
//    Rev 1.14   May 01 1997 08:41:54   dcyk
// Added addRepeat, removeRepeat and
// appendRepeatData.
//
// Added documentation.
//
//
//    Rev 1.13   Apr 11 1997 08:56:48   dcyk
// Improve performance.
//
//
//    Rev 1.12   Apr 04 1997 09:41:08   dcyk
// Improve performance in the
// stream out operator.
//
//
//    Rev 1.11   Apr 01 1997 11:07:32   dcyk
// In Data object stream out operator,
// move copying of dataMap outside of loop
// to improve performance.
//
//
//
//    Rev 1.10   Mar 25 1997 15:44:20   dcyk
// Added:  array[] operators for repeats,
// getData & getDataElement instead of getComponent,
// isDefault.
//
// Removed:  findRepeat, setValue.
//
// Changed:  getAllRawValues to getAllValues,
// getValue(string) to getElementValue(string),
// resetValue(string) to resetElementValue(string),
// setValue(string,string,bool) to setElementValue(string,string,bool).
//
//
//    Rev 1.9   Feb 24 1997 13:53:26   dcyk
// Added third parameter to getAllRawValues,
// a boolean "usePropertiesOrder", defaults to
// false.  If true, fills up the idi string in the order
// that the data components are in the Data
// Properties object, which is the order they
// appear in the "View" file as well.  If false,
// fills up the idi string alphabetically.
//
//
//    Rev 1.8   Feb 11 1997 14:14:14   dcyk
// Made changes for using Rogue Wave's
// STL.  Implemented the findRepeatIndex
// function.  Removed extra parameter in
// setValue.
//
//
//    Rev 1.7   Jan 28 1997 11:40:14   dcyk
// Added an appendNew flag to SetValue.
// Defaults to false.
//
//
//    Rev 1.6   Jan 27 1997 14:09:54   DRUS
// Removed error in copy.  The repeat count pointer is
// now updated after the copy.
//
//    Rev 1.5   Jan 19 1997 13:04:08   DRUS
// Implemented == and != operators.  Fixed copy constructor
// and operator.  Implemented the setValues method to mass copy
// matching fields of data between two Data objects.
//
//    Rev 1.4   Jan 17 1997 17:29:50   DRUS
// Added setValues method which will copy values from another
// Data object.  Also removed buffer data members.
//
//    Rev 1.3   Jan 10 1997 08:56:56   DRUS
// Added support for repeat records.  Added the method findRepeat().
//
//    Rev 1.2   Dec 31 1996 13:48:50   DRUS
// Checked the return values (validity) in calls to setValue.  Modified
// streaming to work with recursive Data objects.
//
//    Rev 1.1   Nov 21 1996 14:38:06   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:06   DRUS
//
//
//