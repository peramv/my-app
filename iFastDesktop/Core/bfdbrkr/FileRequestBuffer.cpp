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
// ^FILE   :  FileRequestBuffer.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <SrcPrag.h>
#include "FileRequestBuffer.hpp"
#include "BFRequest.hpp"
#include <bfdata\bfdata.hpp>

//******************************************************************************
FileRequestBuffer::FileRequestBuffer(const BFRequest &request)
: _buffer(request.getId())
{
}

//******************************************************************************
FileRequestBuffer::~FileRequestBuffer()
{
}

//******************************************************************************
void 
FileRequestBuffer::writeStart()
{
   _buffer.append("_");
}

//******************************************************************************
void 
FileRequestBuffer::writeStartFixed()
{
   _buffer.append("_");
}

//******************************************************************************
void 
FileRequestBuffer::writeField( const BFData &data, const BFFieldId& idField )
{
   DString tmpStr;
   data.getElementValue( idField, tmpStr );
#ifdef DST_UNICODE
   DStringA multiByteFieldString;
   unicodeToMultiByte( tmpStr, multiByteFieldString);

   _buffer.append(multiByteFieldString);
#else
   _buffer.append( tmpStr );
#endif

   _buffer.append("_");
}

//******************************************************************************
void 
FileRequestBuffer::writeEndFixed()
{
   _buffer.append("_");
}

//******************************************************************************
void 
FileRequestBuffer::writeStartRepeatSection()
{
   _buffer.append("_");
}

//******************************************************************************
void 
FileRequestBuffer::writeStartRepeat()
{
   _buffer.append("_");
}

//******************************************************************************
void 
FileRequestBuffer::writeEndRepeat()
{
   _buffer.append("_");
}

//******************************************************************************
void 
FileRequestBuffer::writeEndRepeatSection()
{
   _buffer.append("_");
}

//******************************************************************************
void 
FileRequestBuffer::writeEnd()
{
   _buffer.append("_");
}

//******************************************************************************
const DStringA &
FileRequestBuffer::getString() const
{
   return(_buffer);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/FileRequestBuffer.cpp-arc  $
// 
//    Rev 1.7   Oct 09 2002 17:40:42   PURDYECH
// New PVCS Database
// 
//    Rev 1.6   Aug 29 2002 12:49:28   PURDYECH
// ClientLocale and Field corrections
// 
//    Rev 1.5   May 28 2002 12:15:40   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.4   22 Mar 2002 15:17:12   PURDYECH
// BFData integration
// 
//    Rev 1.3   Jun 26 2001 19:01:32   PURDYECH
// More Infrastructure Release 1.9 Integration stuff.
// 
//    Rev 1.2   10 May 2001 12:12:56   SMITHDAV
// Sync-up 1.0.1.0.
*/
