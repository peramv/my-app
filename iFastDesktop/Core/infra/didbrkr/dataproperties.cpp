//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, databases and
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
// ^FILE   : DataProperties.cpp
// ^AUTHOR : Tony Stryker
// ^DATE   : 10/31/96
//
// ----------------------------------------------------------
//
// ^CLASS : DataProperties
//
// ^INHERITS FROM : DataComponentProperties
//
// ^MEMBER VARIABLES :
//    ^NAME :        _fUsingRepository
//    ^TYPE :        bool
//    ^DESCRIPTION : Specifies if the DataPropertiesImpl object will be in a
//                   repository.
//
//    ^NAME :        _pImpl
//    ^TYPE :        DataPropertiesImpl *
//    ^DESCRIPTION : Pointer to the implementation object.
//
// ^CODING COMMENTS  :
//
// The DataProperties class is part of a "Composite" pattern with the
// DataElementProperties and DataComponentProperties objects.
//
// The DataProperties class uses the DataPropertiesImpl class for its
// implementation.  The implementation object contains the _propertyMap map and
// the _propertyOrder vector, which contain the elements that make up this
// DataProperties object.
//
//******************************************************************************

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef INCLUDED_STRSTREAM
#define INCLUDED_STRSTREAM
   #include <strstream>
#endif

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
   #include <fstream>
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#ifndef DATAPROPERTIESIMPL_HPP
   #include "datapropertiesimpl.hpp"
#endif

#ifndef BASE_H
   #include "base.h"
#endif

#ifndef DIDBRKR_H
   #include "didbrkr.h"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif

#ifndef PROPERTYREPOSITORY_HPP
   #include "propertyrepository.hpp"
#endif

typedef DataComponentProperties DCP;
typedef DataPropertiesImpl DPI;

namespace
{
   const I_CHAR * const CLASS_NAME = I_( "DataProperties" );
   const DString EMPTY_STRING = NULL_STRING;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

DataProperties::DataProperties( const DString &id, const ClientLocale& clientLocale,
                                bool repeatable,
                                const DString &repeatSizeComponentName,
                                ULONG fixedRepeatSize ) :
   DCP( id, repeatable, DCP::eDP )
{
   _fUsingRepository = true;

   _pImpl = DPI::getInstancePointer( id, clientLocale, repeatable );
}


DataProperties::DataProperties( long id, const ClientLocale& clientLocale,
                                bool repeatable,
                                const DString &repeatSizeComponentName,
                                ULONG fixedRepeatSize ) :
   DCP( NULL_STRING, repeatable, DCP::eDP )
{
   _fUsingRepository = true;

   _pImpl = DPI::getInstancePointer( id, clientLocale, repeatable );
}


DataProperties::DataProperties( DataPropertiesImpl *dpi ) :
   DCP( NULL_STRING, dpi->isRepeatable(), DCP::eDP )
{
   _fUsingRepository = true;
   _pImpl = dpi;
}


DataProperties::DataProperties( const DataProperties &copy ) :
   DCP(), _pImpl( 0 )
{
   _fUsingRepository = true;
   *this = copy;
}



DataProperties::~DataProperties()
{
   if ( _pImpl )
   {
      if ( !_fUsingRepository )
      {
         delete _pImpl;
      }
   }
}



//Note: This is currently very specific to the current VW formats & limitations.
// This doesn't recursively operate with Data objects, assumes "Repeat_Count"
// exists, assumes there are not repeatable fixed areas, & assumes there is only
// one repeat area.
i_istream &operator>> ( i_istream &stream, DataProperties &properties )
{
   return stream >> *(properties._pImpl);
}


i_ostream &operator<< ( i_ostream &stream, const DataProperties &properties )
{
   return stream << *(properties._pImpl);
}



bool DataProperties::operator== ( const DataProperties &properties ) const
{
   if (( static_cast<DCP &> (*const_cast< DataProperties *>(this))) !=
                                                                    properties )
   {
      return false;
   }

   if ( _pImpl != properties._pImpl )
   {
      return false;
   }

   return true;
}


void DataProperties::assignVectorIndexes( DCP &dataCompProps )
{
   if ( _pImpl )
   {
      _pImpl->assignVectorIndexes( dataCompProps );
   }
}


bool DataProperties::exists( const DString &propertyName ) const
{
   if ( _pImpl )
   {
      return _pImpl->exists( propertyName );
   }
   else
   {
      return false;
   }
}



bool DataProperties::exists( long id ) const
{
   if ( _pImpl )
   {
      return _pImpl->exists( id );
   }
   else
   {
      return false;
   }
}


DataProperties::DCPPtrVectorType::iterator DataProperties::findPropertyInVector(
                                             DCPPtrVectorType &propVector,
                                             DataComponentProperties *propPtr ) const
{
   if ( _pImpl )
   {
      return _pImpl->findPropertyInVector( propVector, propPtr );
   }
//   DCPPtrVectorType::iterator dummyIter;
   return propVector.end();//dummyIter;
}


bool DataProperties::formatValue( DString &valueString,
                                  bool checkValidity ) const
{
   return true;
}


const DString &DataProperties::getDefaultValue(
   const ClientLocale *pClientLocale
   ) const
{
   return EMPTY_STRING;
}


unsigned long DataProperties::getFieldIdFromName( const DString &name ) const
{
   if ( _pImpl )
   {
      return _pImpl->getFieldIdFromName( name );
   }
   else
   {
      return 0xFFFFFFFF;
   }
}


DString DataProperties::getFileName() const
{
   if ( _pImpl )
   {
      return _pImpl->getFileName().c_str();
   }
   else
   {
      return EMPTY_STRING;
   }
}


unsigned long DataProperties::getFixedByteLength() const
{
   if ( _pImpl )
   {
      return _pImpl->getFixedByteLength();
   }
   return 0;
}


unsigned long DataProperties::getId() const
{
   if ( _pImpl )
   {
      return _pImpl->getId();
   }
   else
   {
      return ULONG_MAX;
   }
}


ULONG DataProperties::getMaxLength() const
{
   if ( _pImpl )
   {
      return _pImpl->getMaxLength();
   }
   else
   {
      return 0L;
   }
}


const DString &DataProperties::getName() const
{
   if ( _pImpl )
   {
      return _pImpl->getName();
   }
   return EMPTY_STRING;
}

/*
long DataProperties::getOffset( unsigned long ulId ) const
{
   if ( _pImpl )
   {
      return _pImpl->getOffset( ulId );
   }
   return -1;
}
*/

const DCP &
DataProperties::getProperty( const DString &propertyName ) const
{
   if ( !_pImpl )
   {
      MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME,
                  I_("DataProperties::getProperty( const DString & )") );
      DString msg( I_("prop=") );
      msg += propertyName;
      throw EXCEPTIONFROMFILEIDI( DIDBRKR_PROPERTY_DOES_NOT_EXIST,
                                msg.c_str() );
   }

   return _pImpl->getProperty( propertyName );
}



const DCP& DataProperties::getProperty( ULONG index ) const
{
   if ( !_pImpl )
   {
      MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME,
                  I_("DataProperties::getProperty( ULONG )") );
      DString msg( I_("index=") );
      std::ostrstream charIndex;
      charIndex << index << std::ends;
      msg += DString( DStringA( charIndex.str() ));
      throw EXCEPTIONFROMFILEIDI( DIDBRKR_PROPERTY_DOES_NOT_EXIST_AT_INDEX,
                                msg.c_str() );
   }

   return _pImpl->getProperty( index );
}


const DCP &
DataProperties::getPropertyByFieldIndex( long id ) const
{
   if ( !_pImpl )
   {
      MAKEFRAMENOTRACE(
         DIDBRKR_COMPONENT_NAME,
         I_( "DataProperties::getPropertyByFieldIndex( long id )" ) );
      DString msg( I_( "prop=" ) );
      msg.appendLong( id );
      throw EXCEPTIONFROMFILEIDI( DIDBRKR_PROPERTY_DOES_NOT_EXIST,
                                  msg.c_str() );
   }

   return _pImpl->getPropertyByFieldIndex( id );
}


ULONG DataProperties::getPropertyCount() const
{
   if ( _pImpl )
   {
      return _pImpl->getPropertyCount();
   }
   else
   {
      return 0L;
   }
}


void DataProperties::getRedefines( const DString &oldName,
                                   string_vector &vecRedefines )
{
   if ( _pImpl )
   {
      _pImpl->getRedefines( oldName, vecRedefines );
   }
}


ULONG DataProperties::getTotalMaxLength() const
{
   if ( _pImpl )
   {
      return _pImpl->getTotalMaxLength();
   }
   else
   {
      return 0L;
   }
}


long DataProperties::getTotalNumberOfLines() const
{
   if ( _pImpl )
   {
      return _pImpl->getTotalNumberOfLines();
   }
   else
   {
      return 0L;
   }
}


long DataProperties::getTotalNumberOfProperties() const
{
   if ( _pImpl )
   {
      return _pImpl->getTotalNumberOfProperties();
   }
   else
   {
      return 0L;
   }
}


long DataProperties::getVectorIndexFromName( const DString &name ) const
{
   if ( _pImpl )
   {
      return _pImpl->getVectorIndexFromName( name );
   }
   else
   {
      return -1L;
   }
}


bool DataProperties::isValid( const DString &idiString,
                              const ClientLocale *pClientLocale ) const
{
   if ( _pImpl )
   {
      return _pImpl->isValid( idiString, pClientLocale );
   }
   else
   {
      return false;
   }
}


void DataProperties::streamOutComponents( i_ostream &stream,
                                          unsigned long &counter,
                                          unsigned long &lineNum,
                                          const DString &viewName,
                                          const DString &propName )
{
   if ( _pImpl )
   {
      _pImpl->streamOutComponents( stream, counter, lineNum, viewName, propName );
   }
}


//******************************************************************************
//              Protected Methods
//******************************************************************************


//******************************************************************************
//              Private Methods
//******************************************************************************

void DataProperties::unauthorizedSetValueInBuffer(
   long id,
   const DString &valueIn,
   unsigned char *rpDataBuffer
   ) const
{
   if ( _pImpl )
   {
      _pImpl->unauthorizedSetValueInBuffer( id, valueIn, rpDataBuffer );
   }
}


//******************************************************************************
//
// ^PRIVATE METHOD      : operator=
//
// ^DESCRIPTION : Assigns one DataProperties object to another.
//
// ^PARAMETERS  :
//    ^^ const DataProperties &copy - (in) reference to a DataProperties object,
//                whose values and attributes you want assigned to this
//                DataProperties object.
//
// ^RETURNS     : Returns a reference to this dataProperties object.
//
// ^THROWS      : ConditionException& - out of memory
//
//
//******************************************************************************

DataProperties & DataProperties::operator= ( const DataProperties &copy )
{
   if ( this == &copy )
   {
      return *this;
   }

   DCP::operator=( copy );

   _fUsingRepository = copy._fUsingRepository;

   if ( _pImpl )
   {
      if ( _fUsingRepository )
      {
         _pImpl = copy._pImpl;
      }
      else
      {
         (*_pImpl) = (*copy._pImpl);
      }
   }
   else
   {
      if ( _fUsingRepository )
      {
         _pImpl = copy._pImpl;
      }
      else
      {
         _pImpl = new DPI( *copy._pImpl );
         if ( !_pImpl )
         {
            THROWFROMBASE( DIDBRKR_COMPONENT_NAME,
                           I_("DataProperties::operator="), BASE_ALLOC_FAIL );
         }
      }
   }

   return *this;
}


DataProperties::DCPPtrVectorType DataProperties::getImplVector() const
{
   return _pImpl->_propertyOrder;
}


DataProperties::EReturn DataProperties::getValueFromBuffer(
   long id,
   DString &strOut,
   const unsigned char *rpDataBuffer,
   unsigned long formatFlags,
   const ClientLocale *rpClientLocale,
   const DString &i18nFormat
   ) const
{
   if ( _pImpl )
   {
      return _pImpl->getValueFromBuffer( id, strOut, rpDataBuffer, formatFlags,
         rpClientLocale, i18nFormat );
   }
   else
   {
      return EReturn::FAILURE;
   }
}


DataProperties::EReturn DataProperties::getValueFromBuffer(
   long id,
   unsigned char *binBuff,
   const unsigned char *rpDataBuffer,
   unsigned long buffLength,
   unsigned long &returnedLength
   ) const
{
   if ( _pImpl )
   {
      return _pImpl->getValueFromBuffer( id, binBuff, rpDataBuffer, buffLength,
         returnedLength );
   }
   else
   {
      return EReturn::FAILURE;
   }
}


//******************************************************************************
//
// ^PRIVATE METHOD : getPropertyElementName
//
// ^DESCRIPTION    : Returns the name of the property at the given index in the
//                   _propertyMap.
//
// ^PARAMETERS     :
//    ^^ ULONG index - (in) index of the property to retrieve the name
//                   for.
//
// ^RETURNS        : Returns a string containing the name of the property
//                   element.
//
// ^THROWS         : string& - if the index is out of range
//
//******************************************************************************


const DString &DataProperties::getPropertyElementName( ULONG index ) const
{
   if ( !_pImpl )
   {
      MAKEFRAMENOTRACE( DIDBRKR_COMPONENT_NAME,
                  I_("DataProperties::getPropertyElementName") );
      DString msg( I_("index=") );
      std::ostrstream charIndex;
      charIndex << index << std::ends;
      msg += DString( DStringA( charIndex.str() ));
      throw EXCEPTIONFROMFILEIDI( DIDBRKR_PROPERTY_DOES_NOT_EXIST_AT_INDEX,
                                msg.c_str() );
   }

   return _pImpl->getPropertyElementName( index );
}


void DataProperties::setId( unsigned long lId )
{
   if ( _pImpl )
   {
      _pImpl->setId( lId );
   }
}


DataProperties::EReturn DataProperties::setValueInBuffer(
   long id,
   const DString &valueIn,
   unsigned char *rpDataBuffer,
   const ClientLocale *rpClientLocale,
   bool displayFormat,
   const DString &i18nFormat
   ) const
{
   if ( _pImpl )
   {
      return _pImpl->setValueInBuffer( id, valueIn, rpDataBuffer, rpClientLocale,
         displayFormat, i18nFormat );
   }
   else
   {
      return EReturn::FAILURE;
   }
}


DataProperties::EReturn DataProperties::setValueInBuffer(
   long id,
   unsigned char *binBuff,
   unsigned char *rpDataBuffer,
   unsigned long buffLength,
   unsigned long &returnedLength
   ) const
{
   if ( _pImpl )
   {
      return _pImpl->setValueInBuffer( id, binBuff, rpDataBuffer, buffLength,
         returnedLength );
   }
   else
   {
      return EReturn::FAILURE;
   }
}


DataProperties::EReturn DataProperties::setValueInBufferFromHost(
   long id,
   DString &valueIn,
   unsigned char *rpDataBuffer
   ) const
{
   if ( _pImpl )
   {
      return _pImpl->setValueInBufferFromHost( id, valueIn, rpDataBuffer );
   }
   else
   {
      return EReturn::FAILURE;
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/dataproperties.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:24   kovacsro
// Initial revision.
// 
//    Rev 1.28   May 18 2001 15:05:24   dt24433
// Updated signatures for binary support and added
// setValueInBufferFromHost.
// 
//    Rev 1.27   Mar 22 2001 16:32:36   dt24433
//  
// 
//    Rev 1.26   Mar 09 2001 11:24:24   dt24433
// Changed getPropertyElementName to return const DString &
// 
//    Rev 1.25   Mar 02 2001 14:08:30   dt24433
// Added support for get/set values directly from/to data object's buffer.
// getId was split to getId and getName as appropriate.
// getFixedLength was changed to getFixedByteLength because it will now always return length in bytes to properly support Binary fields.
// getDefaultValue changed to return const DString & instead of DString
// 
//    Rev 1.24   Jan 22 2001 12:01:34   dt24433
// Added getFixedByteLength.  getFixedLength will not work with binary data.
// 
//    Rev 1.23   Jan 19 2001 16:53:56   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.22   Jan 09 2001 14:06:44   dt24433
// Changed constructor which take DPI * to not create string to pass in to DCP constructor (unused).
//
//    Rev 1.21   Jan 04 2001 16:46:50   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.20   Nov 22 2000 07:05:02   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.19   May 31 2000 09:33:00   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.18   Apr 10 2000 11:47:00   dtwk
// Updates for thread-safety
//
//    Rev 1.17   Jan 16 2000 14:12:08   dtwk
// Remove dead method
//
//    Rev 1.16   Nov 29 1999 07:31:42   dtwk
// Add support for redefines
//
//    Rev 1.15   Oct 06 1999 11:35:34   DCYK
// Add support for redefines.
//
//
//    Rev 1.14   Oct 04 1999 15:25:00   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.13   Sep 02 1999 13:12:42   DCYK
// Add addLocale function, to add a locale on
// an existing properties object.
//
//
//    Rev 1.12   Aug 20 1999 15:35:36   DCYK
// Added locale parameter to isValid, added isI18NValid function.
//
//
//    Rev 1.11   Aug 10 1999 15:42:20   DCYK
// Remove calls to MAKEFRAME, change calls from "throw EXCEPTION" to THROWEXCEPTION.
//
//
//    Rev 1.10   Jul 14 1999 15:50:00   DCYK
//
//
//    Rev 1.9   24 Jun 1999 16:03:50   DCYK
// Fix minor bugs.
//
//
//    Rev 1.8   May 18 1999 09:40:58   DCYK
// Fix problems with index numbers.
//
//
//    Rev 1.7   May 14 1999 11:29:36   DTWK
// Add ability to access Data through Repository Group/Field Id's
//
//    Rev 1.6   May 05 1999 13:10:56   DCYK
// Change getVectorIndex calls to
// getVectorIndexFromName to allow
// re-use of element properties.
//
//
//    Rev 1.5   Apr 20 1999 16:49:34   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.4   09 Mar 1999 12:50:42   DT14177
// Unicode-izing
//
//    Rev 1.3   Mar 05 1999 10:25:38   DCYK
// Changes for I18N.
//
//
//    Rev 1.2   Feb 11 1999 15:04:16   DCYK
// Add support for binary elements.
//
//
//    Rev 1.1   Jan 28 1999 14:03:54   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   29 Jul 1998 20:30:56   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.7   Jul 08 1998 10:04:54   dcyk
// Performance improvements.
//
//
//    Rev 1.6   Jun 18 1998 11:11:44   dcyk
// Remove tracing.
//
//
//    Rev 1.5   Nov 11 1997 10:11:30   dcyk
// Fixed inclusion guards for srcprag.h
//
//
//    Rev 1.4   Nov 10 1997 14:47:02   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.3   23 Sep 1997 16:28:28   dcyk
// Add support for vector indices, so Data objects
// can store elements in a vector, not a map.
//
//
//    Rev 1.2   24 Jul 1997 09:34:10   dcyk
// Use new tracing stuff.
//
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.1   08 Jul 1997 09:06:18   dcyk
// Added STL casting operators and RTTI.
//
//
//    Rev 1.0   Jun 13 1997 16:31:40   DTWK
//
//
//    Rev 1.14   13 Jun 1997 16:20:12   dcyk
//
//
//    Rev 1.13   May 29 1997 09:51:16   dcyk
// Added support for substitute values
// and masking.
//
//
//    Rev 1.12   May 09 1997 16:42:26   dcyk
//
//
//    Rev 1.11   May 06 1997 10:14:14   dcyk
// Cleaned up documentation & comments.
//
//
//    Rev 1.10   May 01 1997 08:43:56   dcyk
// Moved isValid functionality to
// DataPropertiesImpl.
//
// Added documentation.
//
//
//    Rev 1.9   Apr 11 1997 08:57:00   dcyk
//
//
//    Rev 1.8   Mar 25 1997 15:56:58   dcyk
// Added:  formatValue, getMaxLength,
// getDefaultValue, getFileName,
// getProperty( ulong index ).
//
// Removed:  default constructor.
//
// Modify to use DataPropertiesImpl for
// implementation.
//
//
//    Rev 1.7   Feb 11 1997 14:26:58   dcyk
// Added #include "srcprag.h" to supress
// compiler warnings.
// Added support for Rogue Wave's STL.
// Constructor now can search for the
// properties file.  First looks in current
// directory, then in directory specified by
// environment variable "DB_PROPERTIES_PATH".
//
//
//    Rev 1.6   Jan 21 1997 14:55:12   dcyk
// If the properties file is not found in the
// current directory, search the
// DB_PROPERTIES_PATH environment
// variable.
//
//
//    Rev 1.5   Jan 19 1997 13:00:32   DRUS
// Implemented == and != operators.  Fixed copy constructor
// and operators.
//
//    Rev 1.4   Jan 15 1997 17:30:04   dcyk
// Made the "_id" from DataComponentProperties
// be just an id, and handle the file name
// separately.
//
//    Rev 1.3   Jan 10 1997 08:38:18   DRUS
// Added support for repeat records, including a constructor
// which accepts repeat information.
//
//    Rev 1.2   Dec 31 1996 13:44:18   DRUS
// Implemented the default constructor & the isValid() method.
//
//    Rev 1.1   Nov 21 1996 14:38:12   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:18   DRUS
//
//

//void DataProperties::dumpPIMap()
//{
//   _pImpl->dumpPIMap();
//}
