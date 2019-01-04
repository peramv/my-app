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
// ^FILE   : BFWriteBuffer.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : BFWriteBuffer
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific WriteBuffer 
//    classes.
//
//******************************************************************************
#include <win32\platform.h>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class BFData;
class DString;
class DStringA;
class BFFieldId;

class BFDBRKR_LINKAGE BFWriteBuffer
{
public:
   virtual ~BFWriteBuffer() {}

   virtual void writeStart() = 0;

   virtual void writeStartFixed() = 0;
   virtual void writeField( const BFData &data, const BFFieldId& idField ) = 0;
   virtual void writeEndFixed() = 0;

   virtual void writeStartRepeatSection() = 0;
   virtual void writeStartRepeat() = 0;
   virtual void writeEndRepeat() = 0;
   virtual void writeEndRepeatSection() = 0;

   virtual void writeEnd() = 0;

   virtual const DStringA &getString() const = 0;

protected:
#ifdef DST_UNICODE
   // Ideally sould be implemented in DString class as "toMultiByte" function
   static DStringA &unicodeToMultiByte(const DString &unicodeString, DStringA &outString);
#endif
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/BFWriteBuffer.hpp-arc  $
//
//   Rev 1.7   Oct 09 2002 17:40:40   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Aug 29 2002 12:51:16   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.5   May 28 2002 12:17:22   PURDYECH
//BFData Implementation - Phase II
//
//   Rev 1.4   22 Mar 2002 15:11:48   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.3   Jun 26 2001 19:01:42   PURDYECH
//More Infrastructure Release 1.9 Integration stuff.
//
//   Rev 1.2   10 May 2001 16:39:00   SMITHDAV
//Sync-up 1.0.1.0.
//
//   Rev 1.0   23 Oct 2000 21:22:40   SMITHDAV
//Initial revision.
*/
