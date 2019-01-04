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
// ^FILE   : DataElement.cpp
// ^AUTHOR : Tony Stryker
// ^DATE   : 10/24/96
//
// ----------------------------------------------------------
//
// ^CLASS : DataElement
//
// ^INHERITS FROM : DataComponent
//
// ^MEMBER VARIABLES :
//
//    ^NAME :        _maskedValue
//    ^TYPE :        string
//    ^DESCRIPTION : Stores the DataElement object's value after the mask has
//                   been applied to it.
//
// ^CODING COMMENTS  :
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

#ifndef INCLUDED_SSTREAM
#define INCLUDED_SSTREAM
   #include <sstream>
#endif

#ifndef INCLUDED_IOMANIP
#define INCLUDED_IOMANIP
   #include <iomanip>
#endif

#ifndef DATAELEMENT_HPP
   #include "dataelement.hpp"
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
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

#ifndef DATAELEMENTPROPERTIES_HPP
   #include "dataelementproperties.hpp"
#endif

#ifndef JAVADATE_HPP
   #include "javadate.hpp"
#endif

#ifndef JAVANUMBER_HPP
   #include "javanumber.hpp"
#endif

#ifndef JAVASIMPLEDATEFORMAT_HPP
   #include "javasimpledateformat.hpp"
#endif

#ifndef JAVADECIMALFORMAT_HPP
   #include "javadecimalformat.hpp"
#endif

typedef DataComponentProperties DCP;
typedef DataElementProperties DEP;
typedef DataComponent DC;

namespace
{
   const I_CHAR const *CLASS_NAME = I_( "DataElement" );
}

const I_CHAR DataElement::NULL_VALUE = '\a';

//******************************************************************************
//              Public Methods
//******************************************************************************

DataElement::DataElement( const DString &value, const DString &name,
                          DC *pBase) :
   DC( value, NULL, true, pBase ),
   _binaryBuffer( NULL ), _binaryBufferLength( 0 ), _strName( name ),
   m_fValueIsNull( false )
{
   _initElement( value, NULL, true, &ClientLocale::getDefaultClientLocale() );
}


DataElement::DataElement( const DString &value, DEP *properties,
                          bool initElement,
                          const ClientLocale &clientLocale ) :
   DC( value, properties, initElement, NULL, clientLocale ),
   _binaryBuffer( NULL ), _binaryBufferLength( 0 ),
   m_fValueIsNull( false )
{
   _initElement( value, properties, initElement, &clientLocale );
}


DataElement::~DataElement()
{
}


DataElement &DataElement::operator=( const DataElement &copy )
{
   if ( this == &copy )
   {
      return *this;
   }

   if ( ( _dataProperties && !copy._dataProperties ) ||
        ( !_dataProperties && copy._dataProperties ))
   {
      THROWFROMFILE( DIDBRKR_COMPONENT_NAME,
                     I_("DataElement::operator="),
                     DIDBRKR_CANNOT_ASSIGN_DATAELEMENT_OBJECTS );
   }
   if ( ( _dataProperties && copy._dataProperties ) &&
        ( _dataProperties != copy._dataProperties ) )
   {
      DString msg( I_("ele1=") );
      msg += _dataProperties->getName();
      msg += I_(";ele2=");
      msg += copy._dataProperties->getName();
      THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME, I_("DataElement::operator="),
                        DIDBRKR_PROPERTIES_DONT_MATCH, msg.c_str() );
   }

   (static_cast<DC &> (*this)) = copy;

   _strValue = copy._strValue;
   if ( _binaryBuffer )
   {
      delete [] _binaryBuffer;
      _binaryBuffer = NULL;
      _binaryBufferLength = 0;
   }
   if ( copy._binaryBufferLength )
   {
      _binaryBuffer = new unsigned char[ copy._binaryBufferLength ];
      _binaryBufferLength = copy._binaryBufferLength;
      memcpy( _binaryBuffer, copy._binaryBuffer,
              _binaryBufferLength * sizeof( unsigned char ));
   }

   m_fValueIsNull = copy.m_fValueIsNull;
   return *this;
}


std::istream &operator>> ( std::istream &stream, DataElement &element )
{

// This streaming operator is only used to stream data into element from parent
//  data buffer - not very efficient.  Other streaming currently happens at
//  data level into the data object's buffer.  Don't know if a streaming
//  operator will be needed here or not to support multiple repeats.
   unsigned long maxLen = 0;

   DEP *properties = dynamic_cast<DEP *>(element._dataProperties);
   if ( properties )
   {  // Max length is either length of binary field or length in characters
      maxLen = properties->getMaxLength();
   }

// Obviously not expecting to handle elements without properties here,
//  since maxLen would be set to 0 for the rest of this code.  Should
//  we return/ error message or what?  (use of properties after this would
//  explode...)

   if ( properties->getStoredType() == DEP::BINARY )
   {
      if ( !element._binaryBuffer )
      {
         element._binaryBuffer = new unsigned char[ maxLen ];
      }
      element._binaryBufferLength = maxLen;
      stream.read( (char *)element._binaryBuffer, maxLen );
   }
   else
   {
      I_CHAR *buffer = NULL;
      buffer = new I_CHAR[ maxLen ];

      stream.read( (char *)buffer, maxLen * sizeof( I_CHAR * ) );
      if ( DataElement::NULL_VALUE == buffer[0] &&
           properties->getAllowNull() )
      {
         element.m_fValueIsNull = true;
         element.resetValue();
      }
      else
      {
         DString tempString( buffer, maxLen );
         properties->mapToFormattedValue( tempString );
         element._strValue = tempString;
      }

      delete [] buffer;
   }
   return stream;
}


std::ostream &operator<< ( std::ostream &stream, const DataElement &element )
{
// Both streaming operators need to be tested............. both depend on
//  properties.
   if ( element.getProperties() )
   {
      DCP *dcpPtr = const_cast< DCP * >(element.getProperties());
      DEP *depPtr = dynamic_cast< DEP * >(dcpPtr);
      if ( depPtr->getStoredType() == DEP::BINARY )
      {
         stream << std::setw( element._binaryBufferLength )
                << element._binaryBuffer;
         return stream;
      }
   }

   if ( element.m_fValueIsNull )
   {
      if ( element.getProperties() )
      {
         DCP *dcpPtr = const_cast< DCP * >(element.getProperties());
         DEP *depPtr = dynamic_cast< DEP * >(dcpPtr);

         I_CHAR chSpace = ' ';
         DString tmpStr( chSpace, depPtr->getMaxLength() );
         stream << DataElement::NULL_VALUE;
         stream << std::setw( depPtr->getMaxLength() * sizeof(I_CHAR *) )
            << (char *) tmpStr.c_str();
      }
   }
   else
   {
      DString nativeValue( element._strValue );
      DEP *depPtr = static_cast<DEP *>( element._dataProperties );
         depPtr->mapToNativeValue( nativeValue );
      stream << std::setw( depPtr->getMaxLength() * sizeof(I_CHAR *) )
         << (char *)nativeValue.c_str();
   }

   return stream;
}


bool DataElement::operator== ( const DataElement &element ) const
{
   if (  _strValue != element._strValue )
   {
      return false;
   }

   if ( (static_cast<DC &> (*(const_cast<DataElement *>(this))) != element ))
   {
      return false;
   }

   return true;
}

// Commenting out to see if any projects use.  8)  03/01/2001
/*
void DataElement::assignUnsignedCharBuffer( I_UCHAR *inBuffer )
{
   DEP *properties = dynamic_cast<DEP *>(_dataProperties);
   if ( properties )
   {
      unsigned long maxLen;

      maxLen = properties->getMaxLength();
      if ( properties->getStoredType() == DEP::BINARY )
      {
         if ( !_binaryBuffer )
         {
            _binaryBuffer = new unsigned char[ maxLen ];
         }
         _binaryBufferLength = maxLen;
         memcpy( _binaryBuffer, inBuffer, maxLen * sizeof( unsigned char ) );
      }
      else
      {
         _strValue.assign( (I_CHAR *)inBuffer, maxLen );
         properties->mapToFormattedValue( _strValue );
      }
   }

   return;
}
*/

bool DataElement::getBinaryValue( unsigned char *valBuffer,
                                  unsigned long valBufferLength,
                                  unsigned long &returnedLength ) const
{
   bool retVal = false;
   DEP *properties = dynamic_cast< DEP * >(_dataProperties);
   if ( properties && properties->getStoredType() == DEP::BINARY )
   {
      if ( _binaryBuffer )
      {
         returnedLength = min( valBufferLength, _binaryBufferLength );
         memcpy( valBuffer, _binaryBuffer, returnedLength );
         retVal = true;
      }
   }
   return retVal;
}


bool DataElement::setBinaryValue( unsigned char *valBuffer,
                                  unsigned long valBufferLength,
                                  unsigned long &returnedLength )
{
   bool retVal = false;
   DEP *properties = dynamic_cast< DEP * >(_dataProperties);
   unsigned long maxLength = properties->getMaxLength();
   if ( properties && properties->getStoredType() == DEP::BINARY )
   {
      returnedLength = min( valBufferLength, maxLength );
      memset( _binaryBuffer, 0, maxLength );
      memcpy( _binaryBuffer, valBuffer, returnedLength );
      retVal = true;
   }

   return retVal;
}


bool DataElement::getForceMatching() const
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties )
   {
      return properties->getForceMatching();
   }
   else
   {
      return false;
   }
}


bool DataElement::getAllSubstituteValues(
   DString &subValues,
   const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties )
   {
      return properties->getAllSubstituteValues( subValues, pLocClientLocale );
   }
   else
   {
      return false;
   }
}


unsigned long DataElement::getId() const
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


const DString &DataElement::getLabel(
   const ClientLocale *pClientLocale
   ) const
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   if ( _dataProperties )
   {
      DCP *dcpPtr = const_cast< DCP * >(_dataProperties);
      DEP *depPtr = dynamic_cast< DEP * >(dcpPtr);
      return depPtr->getFieldLabel( pLocClientLocale );
   }
   else
   {
      return getName();
   }
}


unsigned long DataElement::getMaxLength() const
{
   if ( _dataProperties )
   {
      return _dataProperties->getMaxLength();
   }
   return ULONG_MAX;
}


const DString &DataElement::getName() const
{
   if ( _dataProperties )
   {
      return _dataProperties->getName();
   }
   else
   {
      return _strName;
   }
}


DString DataElement::getSubstituteValue(
   const DString &subValue,
   const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   DEP *properties = dynamic_cast<DEP *> (_dataProperties);
   if ( properties )
   {
      return properties->getSubstituteValue( subValue, pLocClientLocale );
   }
   else
   {
      return subValue.c_str();
   }
}


const DString DataElement::getUnmodifiedValue() const
{
   // Where used?  Do we need reference version?
   return _strValue;
}


bool DataElement::getValueAsBool( bool& value ) const
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties && ( DEP::BOOLEAN == properties->getStoredType()))
   {
      return true;
   }
   else
   {
      return false;
   }
}


bool DataElement::getValueAsDouble( double &value ) const
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);
   int scanReturn;

   if ( properties && properties->getStoredType() != DEP::DECIMAL )
   {
      return false;
   }
// Maybe should have method for this in DString?
   scanReturn = i_sscanf( _strValue.c_str(), I_("%g"), &value );
   return ( 1 == scanReturn );
}


bool DataElement::getValueAsULong( unsigned long &value ) const
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties && ( properties->getStoredType() != DEP::INTEGER ))
   {
      return false;
   }

   value = _strValue.convertToULong();
   return true;
}


bool DataElement::getValueAsDate( JavaDate &value ) const
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties &&
        ( ( properties->getStoredType() != DEP::I18N_DATE ) ||
          ( properties->getStoredType() != DEP::I18N_TIME ) ) )
   {
      return false;
   }

   try
   {
      JavaSimpleDateFormat *pHostFormat = properties->getDateHostFormatter();

      if ( pHostFormat )
      {
         JavaDate *pDate = pHostFormat->parse( _strValue );

         if ( pDate )
         {
            value.setTime( pDate->getTime() );
            delete pDate;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }
   }
   catch ( ... )
   {
      return false;
   }

   return true;
}



bool DataElement::getValueAsNumber( JavaNumber &value ) const
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties &&
        ( ( properties->getStoredType() != DEP::I18N_DECIMAL ) ||
          ( properties->getStoredType() != DEP::I18N_INTEGER ) ||
          ( properties->getStoredType() != DEP::I18N_PERCENT ) ||
          ( properties->getStoredType() != DEP::I18N_CURRENCY ) ) )
   {
      return false;
   }

   try
   {
      JavaDecimalFormat *pHostFormat = properties->getNumberHostFormatter();

      if ( pHostFormat )
      {
         JavaNumber javaNumber;

         pHostFormat->parse( _strValue.getImp(), javaNumber );
         value = javaNumber;
      }
      else
      {
         return false;
      }
   }
   catch ( ... )
   {
      return false;
   }

   return true;
}


DString &DataElement::getValue( DString &valueOut, unsigned long formatFlags,
                               const ClientLocale *pClientLocale,
                               const DString &i18nFormat ) const
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   if ( formatFlags == 0L )
   {
      valueOut = _strValue;
      DEP *properties = dynamic_cast<DEP *> (_dataProperties);
      if ( properties && properties->getStoredType() == DEP::DECIMAL )
      {
         stripLeading( valueOut );
      }
   }
   else
   {
      DEP *properties = dynamic_cast<DEP *> (_dataProperties);

      if ( properties )
      {
         if ( ( formatFlags & DataElement::USE_SUBSTITUTES ) &&
              properties->hasSubstitutes( pLocClientLocale ) )
         {
            valueOut = properties->getSubstituteValue( _strValue, pLocClientLocale );
         }
         else if ( ( formatFlags & DataElement::USE_MASK ) &&
                   ( properties->hasMask( pLocClientLocale ) ||
                     i18nFormat.length() ) )
         {
            valueOut = _strValue;
            properties->formatUsingMask( valueOut, pLocClientLocale, i18nFormat );
         }
         else
         {
            valueOut = _strValue;
         }

         if ( properties->getStoredType() == DEP::STRING )
         {
            if ( formatFlags & DataElement::STRIP_LEADING )
            {
               stripLeading( valueOut );
            }
            if ( formatFlags & DataElement::STRIP_TRAILING )
            {
               stripTrailing( valueOut );
            }
         }
      }
      else
      {
         valueOut = _strValue;
      }
   }
   return valueOut;
}


DString DataElement::getValue( unsigned long formatFlags,
                               const ClientLocale *pClientLocale,
                               const DString &i18nFormat ) const
{
   DString tmpStr;

   return getValue( tmpStr, formatFlags, pClientLocale, i18nFormat );
}


bool DataElement::isDefault( const ClientLocale *pClientLocale ) const
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   if ( _dataProperties )
   {
      return ( _strValue ==
               _dataProperties->getDefaultValue( pLocClientLocale ) );
   }
   else
   {
      return false;
   }
}


void DataElement::resetValue( const ClientLocale *pClientLocale )
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   if ( _dataProperties )
   {
      _strValue = _dataProperties->getDefaultValue( pClientLocale );

      DEP *properties = dynamic_cast< DEP * >( _dataProperties );
      m_fValueIsNull = properties->getDefaultValueIsNull();
   }
   else
   {
      _strValue = NULL_STRING;
   }
}


void DataElement::setForceMatching( bool forceMatching )
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties )
   {
      properties->setForceMatching( forceMatching );
   }
}


bool DataElement::setValue( bool value )
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);
   if ( properties && properties->getStoredType() != DEP::BOOLEAN )
   {
      return false;
   }
   else
   {
      return true;
   }
}


bool DataElement::setValue( double value )
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);
   std::ostrstream locBuffer;
   if ( properties && properties->getStoredType() != DEP::DECIMAL )
   {
      return false;
   }
   locBuffer << value << std::ends;
   DString tempValue( DStringA( locBuffer.str() ));
   return setValue( tempValue, true );
}


bool DataElement::setValue( unsigned long value )
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);
   std::ostrstream locBuffer;
   if ( properties && properties->getStoredType() != DEP::INTEGER )
   {
      return false;
   }
   locBuffer << value << std::ends;
   DString tempValue( DStringA( locBuffer.str() ));
   return setValue( tempValue, true );
}


bool DataElement::setValue( JavaDate &value )
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties &&
        ( ( properties->getStoredType() != DEP::I18N_DATE ) ||
          ( properties->getStoredType() != DEP::I18N_TIME ) ) )
   {
      return false;
   }

   DString tempValue;

   try
   {
      JavaSimpleDateFormat *pHostFormat = properties->getDateHostFormatter();

      if ( pHostFormat )
      {
         pHostFormat->format( value, tempValue );
      }
      else
      {
         return false;
      }
   }
   catch ( ... )
   {
      return false;
   }

   return setValue( tempValue, true );
}


bool DataElement::setValue( JavaNumber &value )
{
   DEP *properties = dynamic_cast<DEP *> (_dataProperties);

   if ( properties &&
        ( ( properties->getStoredType() != DEP::I18N_DECIMAL ) ||
          ( properties->getStoredType() != DEP::I18N_INTEGER ) ||
          ( properties->getStoredType() != DEP::I18N_PERCENT ) ||
          ( properties->getStoredType() != DEP::I18N_CURRENCY ) ) )
   {
      return false;
   }

   DString tempValue;

   try
   {
      JavaDecimalFormat *pHostFormat = properties->getNumberHostFormatter();

      if ( pHostFormat )
      {
         pHostFormat->format( value, tempValue );
      }
      else
      {
         return false;
      }
   }
   catch ( ... )
   {
      return false;
   }

   return setValue( tempValue, true );
}


bool DataElement::setValue( const DString &value, bool checkValidity,
                            const ClientLocale *pClientLocale,
                            bool displayFormat, const DString &i18nFormat )
{
   return _setValue( value, checkValidity, pClientLocale,
                     displayFormat, i18nFormat );
}


bool DataElement::setNull( bool fNull )
{
   if ( _dataProperties )
   {
      DCP *dcpPtr = const_cast< DCP * >(_dataProperties);
      DEP *depPtr = dynamic_cast< DEP * >(dcpPtr);

      if ( depPtr->getAllowNull() )
      {
         m_fValueIsNull = fNull;
         return true;
      }
      else
      {
         return false;
      }
   }

   m_fValueIsNull = fNull;
   return true;
}

//******************************************************************************
//              Private Methods
//******************************************************************************

DataElement::DataElement( const DString &value, DC *pBase, DEP *properties,
                          bool initElement,
                          const ClientLocale &clientLocale ) :
   DC( value, properties, initElement, pBase, clientLocale ),
   _binaryBuffer( NULL ), _binaryBufferLength( 0 )
{
   _initElement( value, properties, initElement, &clientLocale );
}


DataElement::DataElement( const DataElement &copy ) :
   DC(),
   _binaryBuffer( NULL ), _binaryBufferLength( 0 )
{
   *this = copy;
}


void DataElement::_initElement( const DString &value,
                                DataElementProperties *properties,
                                bool initElement,
                                const ClientLocale *pClientLocale )
{
   if ( initElement )
   {
      if ( 0 == value.length()  &&  properties )
      {
         _setId( properties->getId() );
         long maxLen = properties->getMaxLength();
         switch( properties->getStoredType() )
         {
            case DEP::BINARY:
            {
               unsigned long maxLen = properties->getMaxLength();
               _binaryBuffer = new unsigned char[ maxLen ];
               _binaryBufferLength = maxLen;
               memset( _binaryBuffer, 0, maxLen * sizeof( unsigned char ));
            }
            break;

            case DEP::STRING:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            case DEP::INTEGER:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            case DEP::DECIMAL:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            case DEP::I18N_DATE:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            case DEP::I18N_TIME:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            case DEP::I18N_DECIMAL:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            case DEP::I18N_INTEGER:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            case DEP::I18N_PERCENT:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            case DEP::I18N_CURRENCY:
               _setValue( properties->getDefaultValue( pClientLocale ), false,
                          pClientLocale, false );
            break;

            default:
            break;
         }
      }
      else //if ( 0 != value.length() )
      {
         _setValue( value, true, pClientLocale, false );
      }

      if ( properties && properties->getDefaultValueIsNull() )
      {
         m_fValueIsNull = true;
      }
   }
   else
   {
      _strValue = value;
   }
}


void DataElement::_setId( unsigned long newId )
{
   _id = newId;
}


void DataElement::_setName( const DString &newName )
{
   _strName = newName;
}


bool DataElement::_setValue( const DString &value, bool checkValidity,
                             const ClientLocale *pClientLocale,
                             bool displayFormat,
                             const DString &i18nFormat )
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   if ( _dataProperties )
   {
      DEP *properties = static_cast<DEP *> (_dataProperties);

      m_fValueIsNull = false;

      if ( properties->hasSubstitutes( pLocClientLocale ) )
      {
         if ( !properties->getForceMatching() ||
              ( properties->getForceMatching() &&
                ( properties->isValidKey( value, pLocClientLocale ) ||
                  properties->isValidValue( value, pLocClientLocale ))))
         {
            const DString &key = properties->getKeyFromValue( value, pLocClientLocale );
            if ( key != value )
            {
               _strValue = key;
            }
            else
            {
               DString localValue( value );
               if ( properties->formatValue( localValue, checkValidity ) )
               {
                  _strValue = localValue;
               }
               else
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
         DString localValue( value );
         if ( properties->hasMask( pLocClientLocale ) || i18nFormat.length() )
         {
            DString unMaskedValue( localValue );

            if ( displayFormat || i18nFormat.length() )
            {
               try
               {
                  properties->removeMaskFromValue( unMaskedValue, pLocClientLocale,
                                                   i18nFormat );
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
                  properties->formatUsingMask(
                     localValue,
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

            if ( properties->formatValue( unMaskedValue, checkValidity ))
            {
               _strValue = unMaskedValue;
            }
            else
            {
               return false;
            }
         }
         else
         {
            if ( properties->formatValue( localValue, checkValidity ))
            {
               _strValue = localValue;
            }
            else
            {
               return false;
            }
         }
      }
   } // if _dataProperties
   else
   {
      _strValue = value;
   }

   return true;
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/dataelement.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:22   kovacsro
// Initial revision.
// 
//    Rev 1.45   May 21 2001 13:50:08   DT21858
// Now includes srcprag.h correctly
//
//    Rev 1.44   Apr 26 2001 15:45:48   dt24433
// Pass in expected DString to parse instead of pulling char * out of DString.
//
//    Rev 1.43   Mar 22 2001 14:45:54   dt24433
// Changed binary buffer parm from I_UCHAR * to unsigned char *
//
//    Rev 1.42   Mar 02 2001 14:44:04   dt24433
// Only stream in/out by char to properly support binary fields.
// getLabel returns const DString reference instead of DString.
// getId has been split into getId and getName as appropriate.
// Removed code supporting sync up with Data objects data buffer as DataElements are no longer used this way.
//
//    Rev 1.41   Jan 22 2001 12:07:12   dt24433
// Changed use of _cValue and _value to DString _strValue.  Improved _syncDataBuffer.
//
//    Rev 1.40   Jan 10 2001 11:03:02   dt24433
// Changed to support new overload of getValue supporting string reference parm.
//
//    Rev 1.39   Jan 04 2001 16:46:42   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.38   Nov 22 2000 07:04:48   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.37   Sep 05 2000 06:19:52   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.36   Aug 24 2000 07:26:56   dtwk
// Add in more support for clients and markets
//
//
//    Rev 1.35   May 31 2000 09:32:48   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.34   Apr 11 2000 13:25:04   dtwk
// Synch up with ICU class changes
//
//    Rev 1.33   Jan 07 2000 15:01:02   dtwk
// Fix condition exception to correctly identify it's origin
//
//    Rev 1.32   Nov 23 1999 14:03:06   dtwk
// Fix support for setting default values from .bin file
//
//    Rev 1.31   Oct 06 1999 11:35:22   DCYK
// Add support for redefines.
//
//
//    Rev 1.30   Oct 04 1999 15:24:58   DCYK
// More changes for thread safety.  Make all functions that returned
// a DString & or a const DString &, just return a DString.
//
//
//    Rev 1.29   Sep 03 1999 15:24:28   dtwk
// In _setValue() check mask against host mask or display mask as appropriate
//
//    Rev 1.28   Aug 26 1999 13:25:58   dtwk
// Changes for better return codes from PropertyRepository::formatValue
//
//    Rev 1.27   Aug 19 1999 15:03:18   DCYK
// More minor performance improvements.
//
//
//    Rev 1.26   Aug 10 1999 15:42:18   DCYK
// Remove calls to MAKEFRAME, change calls from "throw EXCEPTION" to THROWEXCEPTION.
//
//
//    Rev 1.25   Aug 05 1999 16:37:50   DCYK
// Performance improvements from Tom H. & Michael M.
//
//
//    Rev 1.24   Jul 29 1999 10:32:56   DCYK
// Minor performance improvements.
//
//    Rev 1.23   Jul 26 1999 09:49:58   DCYK
// Change "USen" to "enUS".
//
//
//    Rev 1.22   Jul 23 1999 10:00:00   DCYK
// Fix for adding elements with value = "" to a data object that has no properties.
//
//
//    Rev 1.21   Jul 22 1999 13:41:26   DCYK
// Fix for UNICODE.
//
//
//    Rev 1.20   Jul 22 1999 09:05:52   DCYK
// Add call to _setValue in _initValue when there are no properties or when the value is not empty.
//
//
//    Rev 1.19   Jul 16 1999 10:02:16   DCYK
// Fix for UNICODE
//
//
//    Rev 1.18   Jul 14 1999 15:43:46   DCYK
// Fix problem with initializing one-byte signed fields.
//
//
//    Rev 1.17   Jul 07 1999 14:41:28   DCYK
// More fixes for single-byte signed fields.
//
//
//    Rev 1.16   Jul 07 1999 09:53:44   DCYK
// Fix for 1-byte signed fields.
//
//
//    Rev 1.15   Jun 29 1999 09:45:42   DCYK
// Added setLocale methods.
// Fixed minor bugs.
//
//
//    Rev 1.14   Jun 23 1999 12:06:24   DCYK
// Set passed-in id in getId.
//
//
//    Rev 1.13   Jun 18 1999 09:33:52   DCYK
// Add ID's for dynamically created elements.
//
//
//    Rev 1.12   Jun 14 1999 16:17:12   DCYK
// Clean up.
//
//
//    Rev 1.11   Jun 14 1999 09:54:58   DCYK
// Use javalocale object to get default locales.
//
//    Rev 1.10   Jun 06 1999 13:22:58   DTWK
// Cleanup I18N formatting
//
//    Rev 1.9   May 26 1999 17:20:58   DCYK
// Add support for getting & setting numerical id's.
//
//
//    Rev 1.8   May 25 1999 09:39:20   DTWK
// Add I18N_INTEGER and I18N_TIME types
//
//    Rev 1.7   May 24 1999 10:41:26   DTWK
// Add internationalized formatting and new types (date, decimal, percent, currency)
//
//    Rev 1.6   Apr 26 1999 13:43:40   DCYK
// Initialize _id member.
//
//
//    Rev 1.5   Apr 20 1999 16:49:30   DCYK
// Changes for Repository and I18N.
//
//
//    Rev 1.4   Mar 05 1999 10:25:28   DCYK
// Changes for I18N.
//
//
//    Rev 1.3   Feb 11 1999 15:04:08   DCYK
// Add support for binary elements.
//
//
//    Rev 1.2   Jan 28 1999 14:03:50   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   29 Jul 1998 20:30:48   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.13   Jul 22 1998 10:12:42   dcyk
// Performance improvements
// from Paul D.
//
//
//    Rev 1.12   Jul 08 1998 10:04:54   dcyk
// Performance improvements.
//
//
//    Rev 1.11   Jun 18 1998 11:11:22   dcyk
// Remove tracing.
//
//
//    Rev 1.10   May 27 1998 15:32:24   dt27994
// Changed TRACE_METHOD to use class name instead of component name.
//
//    Rev 1.9   Dec 19 1997 15:21:00   dcyk
// Don't return the space in front of
// positive signed data.
// Requested by Metzger.
//
//
//    Rev 1.8   Nov 10 1997 16:38:42   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.7   24 Sep 1997 13:41:54   dcyk
// Added support for masks for fields with
// length of one.
//
//
//    Rev 1.6   08 Sep 1997 14:26:20   dcyk
// Changes to reduce memory usage.
//
//
//    Rev 1.5   05 Sep 1997 11:24:28   dcyk
// Don't create the _maskedValue unless
// the element has a mask.
//
//
//    Rev 1.4   05 Sep 1997 07:56:24   dcyk
// Removed most calls to MAKEFRAME, use
// TRACE_METHOD & THROWFROMFILE
// instead.
//
//
//    Rev 1.3   07 Aug 1997 15:05:00   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.2   24 Jul 1997 09:33:34   dcyk
// Use new tracing stuff.
//
// Switch to ULONG, UINT, UCHAR &
// USHORT to save space.
//
//
//    Rev 1.1   08 Jul 1997 09:03:26   dcyk
// Added STL casting operators and RTTI.
//
//
//    Rev 1.0   Jun 13 1997 16:31:34   DTWK
//
//
//    Rev 1.19   13 Jun 1997 16:20:06   dcyk
//
//
//    Rev 1.18   Jun 08 1997 18:48:56   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.17   05 Jun 1997 18:01:12   dcyk
// Changed overloads of getValue to
// getValueAsULong, getValueAsBool, etc.
// Added default parameter to getValue,
// formatting flags that are enum's defined on
// DataElement.
//
//
//    Rev 1.16   May 29 1997 09:50:06   dcyk
// Added support for substitute values
// and masking.
//
//
//    Rev 1.15   May 09 1997 16:42:22   dcyk
//
//
//    Rev 1.14   May 06 1997 10:13:32   dcyk
// Cleaned up documentation & comments.
//
//
//    Rev 1.13   May 01 1997 08:43:12   dcyk
// Removed repeat handling stuff.
//
// Added documentation.
//
//
//    Rev 1.12   Apr 11 1997 08:56:56   dcyk
//
//
//    Rev 1.11   Apr 04 1997 09:49:34   dcyk
//
//
//    Rev 1.10   Mar 25 1997 15:51:20   dcyk
// Added:  getValue that returns a string,
// isDefault.
//
// Made copy constructor private.
//
// Use pointer to buffer when streaming in.
//
//
//    Rev 1.9   Feb 19 1997 10:12:10   DPQD
// Fixed bug in mapToNativeValue for signed (decimal)
// values.  Changed code to use 'stripAll' instead of 'erase'
// with iterator.
//
//    Rev 1.8   Feb 11 1997 14:21:40   dcyk
// Added #include "srcprag.h" to suppress
// compiler warnings.
//
//
//    Rev 1.7   Jan 27 1997 14:10:08   DRUS
// Removed error in copy.  The repeat count pointer is
// now updated after the copy.
//
//    Rev 1.6   Jan 19 1997 13:01:56   DRUS
// Implemented == and != operators.  Fixed copy constructor
// and operator.
//
//    Rev 1.5   Jan 17 1997 18:44:06   dcyk
// Set to default values when data element is created.
//
//    Rev 1.4   Jan 15 1997 13:33:34   dcyk
// Added setValue method that pads values to their proper lengths.
//
//    Rev 1.3   Jan 10 1997 08:54:36   DRUS
// Added support for repeat records and added the
// methods findRepeatIndex() and getRepeatElement().
//
//ÿÿÿÿÿÿÿÿev 1.2   Dec 31 1996 13:53:26   DRUS
// Implemented streaming operators for DataElements.  Implemented
// mapToFormattedValue and mapToNativeValue to convert strings between
// buffered (native) formats and useable (formatted) formats.  Implemented
// isElement() to identify objects as DataElements.
//
//    Rev 1.1   Nov 21 1996 14:38:10   DRUS
// Fixed PVCS comment syntax errors.
//
//    Rev 1.0   Nov 19 1996 10:03:14   DRUS
//
//
//

