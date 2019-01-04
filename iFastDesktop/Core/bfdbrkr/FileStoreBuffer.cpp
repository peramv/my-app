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
// ^FILE   :  FileStoreBuffer.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "filestorebuffer.hpp"
#include <bfdata\bfdata.hpp>

//******************************************************************************
FileStoreBuffer::FileStoreBuffer()
: _buffer()
{
}

//******************************************************************************
FileStoreBuffer::~FileStoreBuffer()
{
}

//******************************************************************************
void 
FileStoreBuffer::writeStart()
{
   _buffer.append("{Start}\n");
}

//******************************************************************************
void 
FileStoreBuffer::writeStartFixed()
{
   _buffer.append("{StartFixed}\n");
}


//******************************************************************************
void 
FileStoreBuffer::writeField( const BFData &data, const BFFieldId& idField )
{
   DString tmpStr;
   data.getElementValue( idField, tmpStr );
   _buffer.append("{Field}");

#ifdef DST_UNICODE
   DStringA multiByteFieldString;
   unicodeToMultiByte( tmpStr, multiByteFieldString );

   _buffer.append(multiByteFieldString);
#else
   _buffer.append( tmpStr );
#endif

   _buffer.append("{EndField}\n");
}

//******************************************************************************
void 
FileStoreBuffer::writeEndFixed()
{
   _buffer.append("{EndFixed}\n");
}

//******************************************************************************
void 
FileStoreBuffer::writeStartRepeatSection()
{
   _buffer.append("{StartRepeatSection}\n");
}

//******************************************************************************
void 
FileStoreBuffer::writeStartRepeat()
{
   _buffer.append("{StartRepeat}\n");
}

//******************************************************************************
void 
FileStoreBuffer::writeEndRepeat()
{
   _buffer.append("{EndRepeat}\n");
}

//******************************************************************************
void 
FileStoreBuffer::writeEndRepeatSection()
{
   _buffer.append("{EndRepeatSection}\n");
}

//******************************************************************************
void 
FileStoreBuffer::writeEnd()
{
   _buffer.append("{End}\n");
}

//******************************************************************************
const DStringA &
FileStoreBuffer::getString() const
{
   return(_buffer);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/FileStoreBuffer.cpp-arc  $
// 
//    Rev 1.7   Oct 09 2002 17:40:46   PURDYECH
// New PVCS Database
// 
//    Rev 1.6   Aug 29 2002 12:49:30   PURDYECH
// ClientLocale and Field corrections
// 
//    Rev 1.5   May 28 2002 12:15:40   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.4   22 Mar 2002 15:17:14   PURDYECH
// BFData integration
// 
//    Rev 1.3   Jun 26 2001 19:01:32   PURDYECH
// More Infrastructure Release 1.9 Integration stuff.
// 
//    Rev 1.2   10 May 2001 12:13:30   SMITHDAV
// Sync-up 1.0.1.0.
// 
//    Rev 1.0.1.0   Apr 12 2001 18:26:00   DINACORN
// Add getString() method
*/
