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
// ^FILE   : FileResponseBuffer.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : FileResponseBuffer
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific ReadBuffer 
//    classes.
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfdbrkr\bfreadbuffer.hpp>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif


class BFDBRKR_LINKAGE FileResponseBuffer : public BFReadBuffer
{
public:
   FileResponseBuffer(const DStringA &buffer);

   virtual ~FileResponseBuffer();

   virtual void readStart();

   virtual void readStartFixed();
   virtual bool readField(const BFDataFieldProperties& fieldProperties,  DString& outFieldValue);
   virtual void readEndFixed();

   virtual bool readStartRepeatSection();

   virtual bool readStartRepeat();
   virtual void readEndRepeat();

   virtual void readEndRepeatSection();

   virtual void readEnd();
   virtual const DStringA &getString() const;
   const bool isAtEnd() const;

private:
   DStringA _buffer;
   DStringA::size_type _position;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/FileResponseBuffer.hpp-arc  $
//
//   Rev 1.7   Oct 09 2002 17:40:44   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Aug 29 2002 12:49:28   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.5   Jul 05 2002 08:53:58   PURDYECH
//Fixed include files
//Removed commented-out code.
//
//   Rev 1.4   May 28 2002 12:15:40   PURDYECH
//BFData Implementation - Phase II
//
//   Rev 1.3   22 Mar 2002 15:17:14   PURDYECH
//BFData integration
//
//   Rev 1.2   26 Oct 2001 11:05:46   HSUCHIN
//added getString() functionality.
//
//   Rev 1.1   03 May 2001 14:03:10   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   23 Oct 2000 20:21:16   SMITHDAV
//Initial revision.
*/
