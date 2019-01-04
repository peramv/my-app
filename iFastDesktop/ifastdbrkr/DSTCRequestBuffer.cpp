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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  DSTCRequestBuffer.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "dstcrequestbuffer.hpp"
#include "dstcrequest.hpp"
#include <bfdata\bfdata.hpp>
#include <configmanager.hpp>
#include <ifastdbrkr/ifastdbrkr.hpp>

//******************************************************************************
DSTCRequestBuffer::DSTCRequestBuffer(const BFRequest &request, DSTCPersistMode persistMode, const DStringA &persistHandle)
: _buffer(),
_firstField(true)
, _chDelimiter( "\xcf\xb8")
{
   const DSTCRequest &dstcRequest = dynamic_cast<const DSTCRequest &>(request);

   _buffer.append( "010000" );
   _buffer.append( dstcRequest.getTransId() );

   switch( persistMode )
   {
      case START_PERSIST:
         _buffer.append( "                000000000000000300001" );
         break;

      case IN_PERSIST:
         _buffer.append( "                " );
         _buffer.append( persistHandle );
         _buffer.append( "000001" );
         break;

      case END_PERSIST:
         _buffer.append( "                " );
         _buffer.append( persistHandle );
         _buffer.append( "100001" );
         break;

      default:
         _buffer.append( "                000000000000000000001" );

   }
}

//******************************************************************************
DSTCRequestBuffer::~DSTCRequestBuffer()
{
}


DStringA DSTCRequestBuffer::getViewNumber() const
{
   if( _buffer.length() > 11 ) {
      return( _buffer.substr( 6,5 ) );
   }
   return( DStringA("     ") );
}

//******************************************************************************
const DStringA &
DSTCRequestBuffer::getString() const
{
   return(_buffer);
}

//******************************************************************************
void 
DSTCRequestBuffer::writeStart()
{
}

//******************************************************************************
void 
DSTCRequestBuffer::writeStartFixed()
{
}

//******************************************************************************
void 
DSTCRequestBuffer::writeField( const BFData &data, const BFFieldId& fieldId )
{
	   static unsigned char delim[3] = { 0xc3, 0xbe, 0x00 };// c3be
      _buffer.append((const char *)delim);

   DString fieldValue;
   data.getElementValue( fieldId, fieldValue );
   fieldValue.strip();

// If this appears to cause performance problems - Infra can add a method to get 
//  properties directly from the data object.
   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( fieldId );
   if( pProps->isInteger() )
   {
      fieldValue.stripLeading( '0' );
      if( fieldValue == NULL_STRING )
         _buffer.append("F0");
      else
      {
         _buffer.append("F");
         _buffer.append( DStringA(fieldValue) ); // all ascii character (good assumption?)
      }
   }
   else if( pProps->isDecimal() )
   {
      fieldValue.stripLeading( '0' );
      if( DString::npos != fieldValue.find( I_(".")) )
         fieldValue.stripTrailing( '0' );
      if( fieldValue == I_(".") )
         _buffer.append("F0.0");
      else
      {
         _buffer.append("F");
         _buffer.append( DStringA(fieldValue) ); // all ascii character (good assumption?)
      }
   }
   else if( pProps->isDate() )
   {
      DString tempDate( fieldValue );
      tempDate.strip( '0' );
      tempDate.strip( );

      if( tempDate == NULL_STRING )
         _buffer.append("T");
      else
      {
         _buffer.append("F");
         _buffer.append( DStringA(fieldValue) ); // all ascii character (good assumption?)
      }

   }
   else
   {
#ifdef DST_UNICODE
      DStringA multiByteFieldString;
      unicodeToMultiByte( fieldValue, multiByteFieldString );
      escapeField( multiByteFieldString );
      _buffer.append( "F" );
      _buffer.append( multiByteFieldString );
#else
      escapeField( fieldValue );
      _buffer.append( "F" );
      _buffer.append( fieldValue );
#endif

   }
}

//******************************************************************************
void 
DSTCRequestBuffer::writeEndFixed()
{
}

//******************************************************************************
void 
DSTCRequestBuffer::writeStartRepeatSection()
{
}

//******************************************************************************
void 
DSTCRequestBuffer::writeStartRepeat()
{
}

//******************************************************************************
void 
DSTCRequestBuffer::writeEndRepeat()
{
}

//******************************************************************************
void 
DSTCRequestBuffer::writeEndRepeatSection()
{
}

//******************************************************************************
void 
DSTCRequestBuffer::writeEnd()
{
}

//******************************************************************************
DStringA &
DSTCRequestBuffer::escapeField(DStringA &fieldValue)
{
   return(fieldValue);
}
