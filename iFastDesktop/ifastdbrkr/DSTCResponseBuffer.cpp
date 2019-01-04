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
// ^FILE   :  DSTCResponseBuffer.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "dstcresponsebuffer.hpp"
#include "dstcrequest.hpp"
#include <conditionmanager.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <assert.h>
#include <configmanager.hpp>
#include <ifastdbrkr/ifastdbrkr.hpp>

namespace
{
   const I_CHAR *CLASSNAME = I_( "DSTCRequestBuffer" );
}

namespace CND
{
   extern const I_CHAR *IFASTDBRKR_CONDITION;
   extern const long ERR_MALFORMED_DSTC_RESPONSE_BUFFER;
   extern const long ERR_UNKNOWN_RESPONSE_TYPE;
}

//******************************************************************************
DSTCResponseBuffer::DSTCResponseBuffer(const DSTCRequest &request, const DStringA &buffer)
: _request(request)
, _buffer(buffer)
, _position(0)
, _responseType(OK_RESPONSE)
, _hostErrorCode(0L)
, _hostErrorCodeString( I_( "Unknown error code" ) )
, _hostErrorMessage( I_( "Unknown error message" ) )
, _hostErrorTrackId( I_("") )
, _chDelimiter( 0xfe )
{
   // pre-parse header

   if( _buffer.length() < 36 )
      THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("DSTCResponseBuffer"),
                         CND::ERR_MALFORMED_DSTC_RESPONSE_BUFFER, buildResponseExeptionParameterIDI("response header") );

   if( _buffer.length() == 36 )
      _position = DString::npos;//empty response (no fields)
   else
      _position = 36; // set position past the header...

      setDelimiter( buffer.at(36));
      ++_position;

   DStringA responseTypeString( buffer.substr( 11, 5 ) ); 

   if( responseTypeString == "-0001" )
   {
      _responseType = UNKNOWN_ERROR_RESPONSE;
      parserError();
   }
   else if( responseTypeString == "-0002" )
   {
      _responseType = SMQ_FRAMEWORK_ERROR_RESPONSE;
      parserError();
   }
   else if( responseTypeString == "00001" )
   {
      _responseType = ERROR_RESPONSE;
      parserError();
   }
   else if( responseTypeString == "00002" )
   {
      _responseType = OK_RESPONSE;
   }
   else
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("DSTCResponseBuffer"), CND::ERR_UNKNOWN_RESPONSE_TYPE);

}

//******************************************************************************
DSTCResponseBuffer::~DSTCResponseBuffer()
{
}

//******************************************************************************
DSTCResponseBuffer::ResponseType
DSTCResponseBuffer::getResponseType() const
{
   return(_responseType);
}

DStringA 
DSTCResponseBuffer::getPersistHandle() const
{
   return(_buffer.substr(16, 15));
}

void DSTCResponseBuffer::setPersistHandle( const DStringA& dstrPersistHandle )
{
   DStringA buffer = _buffer.substr(0,16);
   buffer += dstrPersistHandle;
   buffer += _buffer.substr(31);
}


//******************************************************************************
long 
DSTCResponseBuffer::getHostErrorCode() const
{
   assert( OK_RESPONSE != getResponseType() );
   return(_hostErrorCode);
}

//******************************************************************************
DString 
DSTCResponseBuffer::getHostErrorCodeString() const
{
   assert( OK_RESPONSE != getResponseType() );
   return(_hostErrorCodeString);
}

//******************************************************************************
DString 
DSTCResponseBuffer::getHostErrorMessage() const
{
   assert( OK_RESPONSE != getResponseType() );
   return(_hostErrorMessage);
}

//******************************************************************************
void 
DSTCResponseBuffer::readStart()
{
   assert( OK_RESPONSE == getResponseType() );
}

//******************************************************************************
void 
DSTCResponseBuffer::readStartFixed()
{
   assert( OK_RESPONSE == getResponseType() );
}


//******************************************************************************
bool 
DSTCResponseBuffer::readField(const BFDataFieldProperties& fieldProperties, DString &outFieldValue)
{
   assert( OK_RESPONSE == getResponseType() );

   if( getUnknownFlag() )
      return(false);

   DStringA fieldString;

   if( fieldProperties.isNumeric() )
   {
      getNumericFieldValue(fieldString);
   }
   else
   {
      getUnescapedFieldValue(fieldString);
   }
#ifdef DST_UNICODE
   DString unicodeFieldString;
   outFieldValue = multiByteToUnicode(fieldString, unicodeFieldString);
#else
   outFieldValue = fieldString;
#endif

   return(true);
}

//******************************************************************************
void 
DSTCResponseBuffer::readEndFixed()
{
   assert( OK_RESPONSE == getResponseType() );
}

//******************************************************************************
bool 
DSTCResponseBuffer::readStartRepeatSection()
{
   assert( OK_RESPONSE == getResponseType() );

   if( _position == DStringA::npos )
      return(false);

   return(true);
}

//******************************************************************************
bool 
DSTCResponseBuffer::readStartRepeat()
{
   assert( OK_RESPONSE == getResponseType() );

   if( _position == DStringA::npos )
      return(false);

   return(true);
}

//******************************************************************************
void 
DSTCResponseBuffer::readEndRepeat()
{
   assert( OK_RESPONSE == getResponseType() );
}

//******************************************************************************
void 
DSTCResponseBuffer::readEndRepeatSection()
{
   assert( OK_RESPONSE == getResponseType() );
}


//******************************************************************************
void 
DSTCResponseBuffer::readEnd()
{
   assert( OK_RESPONSE == getResponseType() );

   if( _position != DStringA::npos )
      throw;
}

//******************************************************************************
bool 
DSTCResponseBuffer::getUnknownFlag()
{

   if( _buffer[_position] == 'T' )
   {
      incrementPosition(); // get past the "unknown" flag
      if( _buffer[_position] == getDelimiter() )
         incrementPosition(); // get past the field seperator

      return(true);
   }
   if( _buffer[_position] != 'F' )
      THROWFROMFILEIDI2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("DSTCResponseBuffer"),
                         CND::ERR_MALFORMED_DSTC_RESPONSE_BUFFER, buildResponseExeptionParameterIDI("field") );

   incrementPosition(); // get past the "unknown" flag

   return(false);

}

//******************************************************************************
void 
DSTCResponseBuffer::getNumericFieldValue(DStringA &fieldString)
{

   fieldString.erase();

   // at the end??? - must be empty field.
   if( _position == DStringA::npos )
      return;

   // strip out leading '+' if it exists
   if( _buffer[_position] == '+' )
   {
      incrementPosition();
      // at the end??? - must be empty field.
      if( _position == DStringA::npos )
         return;
   }

   DStringA::size_type pos = _position;
   pos = _buffer.find_first_of(getDelimiterString().c_str(), _position);
   bool bEnd = pos >= _buffer.length(); 

   if( pos == DStringA::npos || bEnd )
   {
      // copy to the end of buffer
      fieldString.append(_buffer, _position, ( (_buffer.length() ) - _position ) );
      _position = DStringA::npos;
      return;
   }
   else
   {
      // copy to seperator
      fieldString.append(_buffer, _position, (pos-_position) );
      _position = pos;

      if( _buffer[_position] == getDelimiter() )
         // get past the field seperator and exit
         incrementPosition();
   }
}

//******************************************************************************
void 
DSTCResponseBuffer::getUnescapedFieldValue(DStringA &fieldString)
{

   fieldString.erase();

   // at the end??? - must be empty field.
   if( _position == DStringA::npos )
      return;

   DStringA::size_type pos = _position;
   while( 1 )
   {
         pos = _buffer.find_first_of(getDelimiter(), _position);

      if( pos == DStringA::npos )
      {
         // copy the last segment
         fieldString.append(_buffer, _position, ( (_buffer.length()) - _position ) );
         _position = DStringA::npos;

         break;
      }
      else
      {
         // copy this segment
         fieldString.append(_buffer, _position, (pos-_position) );
         _position = pos;

         if( _buffer[_position] == '\\' )
         {
            // take next character as literal
            fieldString.append(1, _buffer[_position+1]);
            incrementPosition(2);
            // boundary case:  if we have incremented to the end of the buffer then we have to exit the processing (CP 07Jul2002)
            if( _position == DStringA::npos )
            {
               break;
            }
            continue;
         }
         else if( _buffer[_position] == getDelimiter() )
         {
            // get past the field seperator and exit
            incrementPosition();
            break;
         }
      }

   } // while

}

//******************************************************************************
DStringA::size_type 
DSTCResponseBuffer::incrementPosition(DStringA::size_type increment /* =1 */)
{

   if( _position == DStringA::npos )
      return(_position);

   if( _position >= _buffer.length() )
   {
      _position = DStringA::npos;
      return(_position);
   }

   for( DStringA::size_type i=0; i<increment; ++i )
   {
      _position++;

      if( _position >= _buffer.length() )
      {
         _position = DStringA::npos;
         return(_position);
      }

   }

   return(_position);

}

DString 
DSTCResponseBuffer::buildResponseExeptionParameterIDI(const DStringA &expected)
{
   DString strIDI;
   char strPosition[32];

   addIDITagValue( strIDI, I_("REQID"), _request.getId() );
   addIDITagValue( strIDI, I_("POSITION"), DStringA(itoa( _position, strPosition, 10)) );
   addIDITagValue( strIDI, I_("EXPECTED"), expected );

   return(strIDI);
}

void 
DSTCResponseBuffer::parserError()
{
   try
   {
      if( !getUnknownFlag() )
      {
         DStringA codeString;
         getNumericFieldValue(codeString);
         _hostErrorCode = codeString.asInteger();

#ifdef DST_UNICODE
         DString unicodeFieldString;
         _hostErrorCodeString = multiByteToUnicode(codeString, unicodeFieldString);
#else
         _hostErrorCodeString = codeString;
#endif
         if( !getUnknownFlag() )
         {
            DStringA messageString;
            getUnescapedFieldValue(messageString);

#ifdef DST_UNICODE
            DString unicodeFieldString;
            _hostErrorMessage = multiByteToUnicode(messageString, unicodeFieldString);
#else
            _hostErrorMessage = messageString;
#endif

            if( _position != DString::npos && !getUnknownFlag() ) {
               DStringA trackIdString;
               getUnescapedFieldValue(trackIdString);
#ifdef DST_UNICODE
               DString unicodeFieldString;
               _hostErrorTrackId = multiByteToUnicode(trackIdString, unicodeFieldString);
#else
               _hostErrorTrackId = trackIdString;
#endif
            }
         }

      }
   }
   catch( ... )
   {
   }
}


//******************************************************************************
const DStringA &
DSTCResponseBuffer::getString() const
{
   return(_buffer);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCResponseBuffer.cpp-arc  $
// 
//    Rev 1.22   May 03 2010 04:46:32   purdyech
// IN2107238 - Remove contention on usingSonicMQ().  Add support for IFAST_NUM_BATCH logic in Views
// 
//    Rev 1.21   Oct 21 2009 10:21:22   purdyech
// LDAP Authorization Support
// 
//    Rev 1.20   Jul 28 2009 09:11:02   purdyech
// CR24095 - Performance Update to work around OpenEdge problem.
// 
//    Rev 1.19   Jun 05 2009 08:22:38   purdyech
// Fixed names of SonicSingle and SonicMulti queues in configuration.
// SonicErrorMessages are now handled appropriately.
// 
//    Rev 1.18   Feb 06 2009 14:53:44   purdyech
// Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
// 
//    Rev 1.17   Nov 14 2004 15:00:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.16   Oct 09 2002 23:55:24   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.15   Jul 07 2002 11:16:02   PURDYECH
// Fixed a boundary bug.  When the *last* character in the stream is an escaped comma the buffer would attempt to append at DStringA::npos on a subsequent pass.
// 
//    Rev 1.14   Jul 05 2002 08:54:34   PURDYECH
// Fixed include files
// Removed commented-out code.
// 
//    Rev 1.13   May 28 2002 12:17:34   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.12   22 Mar 2002 15:36:06   PURDYECH
// Removed compile-time "including..." message
// Use #pragma once as include guard
// Include files with lower-case only names
// BFData integration
// 
//    Rev 1.11   12 Dec 2001 15:37:00   KOVACSRO
// empty response is a valid response (as long as we receive a valid header)
// 
//    Rev 1.10   26 Oct 2001 11:05:48   HSUCHIN
// added getString() functionality.
*/