#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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
// ^FILE   : BFReadBuffer.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : BFReadBuffer
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific ReadBuffer 
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

class BFDataFieldProperties;
class DString;
class DStringA;

class BFDBRKR_LINKAGE BFReadBuffer
{
public:
   virtual ~BFReadBuffer() {}

   virtual void readStart() = 0;

   virtual void readStartFixed() = 0;
   virtual bool readField(const BFDataFieldProperties& fieldProperties,  DString &outFieldValue) = 0;
   virtual void readEndFixed() = 0;

   virtual bool readStartRepeatSection() = 0;

   virtual bool readStartRepeat() = 0;
   virtual void readEndRepeat() = 0;

   virtual void readEndRepeatSection() = 0;

   virtual void readEnd() = 0;
   virtual const DStringA &getString() const = 0;
   virtual const bool isAtEnd() const = 0;

protected:
#ifdef DST_UNICODE
   // Ideally sould be implemented in DStringA class as "toUnicode" function
   static DString &multiByteToUnicode(const DStringA &multiByteString, DString &outString);
#endif
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/BFReadBuffer.hpp-arc  $
//
//   Rev 1.6   Oct 09 2002 17:40:38   PURDYECH
//New PVCS Database
//
//   Rev 1.5   Aug 29 2002 12:51:14   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.4   May 28 2002 12:17:18   PURDYECH
//BFData Implementation - Phase II
//
//   Rev 1.3   22 Mar 2002 15:11:42   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.2   26 Oct 2001 11:05:04   HSUCHIN
//added getString() to interface.
//
//   Rev 1.1   03 May 2001 14:03:24   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   23 Oct 2000 21:22:40   SMITHDAV
//Initial revision.
*/
