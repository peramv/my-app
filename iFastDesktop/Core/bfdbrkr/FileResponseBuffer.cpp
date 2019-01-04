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
// ^FILE   :  FileResponseBuffer.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <SrcPrag.h>
#include "FileResponseBuffer.hpp"
#include <conditionmanager.hpp>

namespace
{
   const I_CHAR *CLASSNAME = I_( "FileResponseBuffer" );
}

namespace CND
{
   extern const I_CHAR *BFDBRKR_CONDITION;
   extern const long ERR_MALFORMED_FILE_RESPONSE_BUFFER;
}

//******************************************************************************
FileResponseBuffer::FileResponseBuffer(const DStringA &buffer)
: _buffer(buffer),
_position(0)
{
}

//******************************************************************************
FileResponseBuffer::~FileResponseBuffer()
{
}

//******************************************************************************
void 
FileResponseBuffer::readStart()
{
   if( 0 != _buffer.compare( _position, 8, "{Start}\n" ) )
      THROWFROMFILE2(CND::BFDBRKR_CONDITION, CLASSNAME, I_("readStart"), CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER);

   _position+=8;
}

//******************************************************************************
void 
FileResponseBuffer::readStartFixed()
{
   if( 0 != _buffer.compare( _position, 13, "{StartFixed}\n" ) )
      THROWFROMFILE2(CND::BFDBRKR_CONDITION, CLASSNAME, I_("readStartFixed"), CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER);

   _position+=13;
}


//******************************************************************************
bool 
FileResponseBuffer::readField(const BFDataFieldProperties& fieldProperties, DString &outFieldValue)
{
   if( 0 != _buffer.compare( _position, 7, "{Field}" ) )
      return(false);

   _position+=7;

   // find the terminating tag
   DStringA::size_type fieldTermPosition = _buffer.find("{EndField}\n", _position);

   if( DStringA::npos == fieldTermPosition )
      THROWFROMFILE2(CND::BFDBRKR_CONDITION, CLASSNAME, I_("readField"), CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER);

   DStringA fieldString = _buffer.substr(_position, (fieldTermPosition - _position));

#ifdef DST_UNICODE
   DString unicodeFieldString;
   outFieldValue = multiByteToUnicode(fieldString, unicodeFieldString);
#else
   outFieldValue = fieldString;
#endif

   // get past the '\n' terminator
   _position = fieldTermPosition + 11;

   return(true);
}

//******************************************************************************
void 
FileResponseBuffer::readEndFixed()
{
   if( 0 != _buffer.compare( _position, 11, "{EndFixed}\n" ) )
      THROWFROMFILE2(CND::BFDBRKR_CONDITION, CLASSNAME, I_("readEndFixed"), CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER);

   _position+=11;
}

//******************************************************************************
bool 
FileResponseBuffer::readStartRepeatSection()
{
   if( 0 != _buffer.compare( _position, 21, "{StartRepeatSection}\n" ) )
      return(false);

   _position+=21;
   return(true);
}

//******************************************************************************
bool 
FileResponseBuffer::readStartRepeat()
{
   if( 0 != _buffer.compare( _position, 14, "{StartRepeat}\n" ) )
      return(false);

   _position+=14;
   return(true);
}

//******************************************************************************
void 
FileResponseBuffer::readEndRepeat()
{
   if( 0 != _buffer.compare( _position, 12, "{EndRepeat}\n" ) )
      THROWFROMFILE2(CND::BFDBRKR_CONDITION, CLASSNAME, I_("readEndRepeat"), CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER);

   _position+=12;
}

//******************************************************************************
void 
FileResponseBuffer::readEndRepeatSection()
{
   if( 0 != _buffer.compare( _position, 19, "{EndRepeatSection}\n" ) )
      THROWFROMFILE2(CND::BFDBRKR_CONDITION, CLASSNAME, I_("readEndRepeatSection"), CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER);

   _position+=19;
}


//******************************************************************************
void 
FileResponseBuffer::readEnd()
{
   if( 0 != _buffer.compare( _position, 6, "{End}\n" ) )
      THROWFROMFILE2(CND::BFDBRKR_CONDITION, CLASSNAME, I_("readEnd"), CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER);

   _position+=6;
}

//******************************************************************************
const DStringA &
FileResponseBuffer::getString() const
{
   return(_buffer);
}

//******************************************************************************
const bool
FileResponseBuffer::isAtEnd() const 
{
   return _position == DStringA::npos;
}
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/FileResponseBuffer.cpp-arc  $
// 
//    Rev 1.6   Oct 09 2002 17:40:44   PURDYECH
// New PVCS Database
// 
//    Rev 1.5   Aug 29 2002 12:49:28   PURDYECH
// ClientLocale and Field corrections
// 
//    Rev 1.4   May 28 2002 12:15:40   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.3   22 Mar 2002 15:17:12   PURDYECH
// BFData integration
// 
//    Rev 1.2   26 Oct 2001 11:05:46   HSUCHIN
// added getString() functionality.
*/
