#pragma once

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
// ^FILE   : FileRequestBuffer.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : FileRequestBuffer
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific RequestBuffer 
//    classes.
//
//******************************************************************************
#include <win32\platform.h>
#include <DString.hpp>
#include <bfdbrkr\BFWriteBuffer.hpp>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

//CPclass DataElement;
class BFData;
class BFRequest;
class BFFieldId;

class BFDBRKR_LINKAGE FileRequestBuffer : public BFWriteBuffer
{
public:
   FileRequestBuffer(const BFRequest &request);
   virtual ~FileRequestBuffer();

   virtual void writeStart();

   virtual void writeStartFixed();
   virtual void writeField( const BFData &data, const BFFieldId& idField );
   virtual void writeEndFixed();

   virtual void writeStartRepeatSection();
   virtual void writeStartRepeat();
   virtual void writeEndRepeat();
   virtual void writeEndRepeatSection();

   virtual void writeEnd();

   const DStringA &getString() const;

private:

   DStringA _buffer;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/FileRequestBuffer.hpp-arc  $
//
//   Rev 1.7   Oct 09 2002 17:40:44   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Aug 29 2002 12:49:28   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.5   May 28 2002 12:15:40   PURDYECH
//BFData Implementation - Phase II
//
//   Rev 1.4   22 Mar 2002 15:17:12   PURDYECH
//BFData integration
//
//   Rev 1.3   Jun 26 2001 19:01:32   PURDYECH
//More Infrastructure Release 1.9 Integration stuff.
//
//   Rev 1.2   10 May 2001 12:12:56   SMITHDAV
//Sync-up 1.0.1.0.
//
//   Rev 1.1   03 May 2001 14:03:08   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   23 Oct 2000 20:21:14   SMITHDAV
//Initial revision.
*/
