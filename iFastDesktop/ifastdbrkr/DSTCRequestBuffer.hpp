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
// ^FILE   : DSTCRequestBuffer.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : DSTCRequestBuffer
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfdbrkr\bfwritebuffer.hpp>
#include <ifastdbrkr\dstcpersistentrequestor.hpp>

class BFData;
class BFRequest;
class DSTCSecurity;

class DSTCRequestBuffer : public BFWriteBuffer
{
public:
   DSTCRequestBuffer(const BFRequest &request, DSTCPersistMode persistMode = NO_PERSIST, const DStringA &persistHandle = "");
   virtual ~DSTCRequestBuffer();

   DStringA getViewNumber() const;

   const DStringA &getString() const;

   virtual void writeStart();

   virtual void writeStartFixed();
   virtual void writeField( const BFData &data, const BFFieldId& idField );
   virtual void writeEndFixed();

   virtual void writeStartRepeatSection();
   virtual void writeStartRepeat();
   virtual void writeEndRepeat();
   virtual void writeEndRepeatSection();

   virtual void writeEnd();

private:
   const char *getDelimiter() const { return _chDelimiter; }
   void setDelimiter(const char *chDelim) { _chDelimiter = chDelim; }
   const char* getDelimiterString();
   const char *_chDelimiter;

   DStringA &escapeField(DStringA &fieldValue);

   DStringA _buffer;
   bool _firstField;
};


//CP#endif // #ifndef DSTCREQUESTBUFFER_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCRequestBuffer.hpp-arc  $
//
//   Rev 1.8   Jul 28 2009 09:09:32   purdyech
//CR24095 - Performance Update to work around OpenEdge problem.
//
//   Rev 1.7   Feb 06 2009 14:54:12   purdyech
//Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
//
//   Rev 1.6   Oct 09 2002 23:55:22   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:51:20   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   May 28 2002 12:17:34   PURDYECH
//BFData Implementation - Phase II
//
//   Rev 1.3   22 Mar 2002 15:36:04   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//BFData integration
//
//   Rev 1.2   17 Jun 2001 11:23:14   PURDYECH
//EFAN_REL_12.0 integration with Infrastructure Release 1.9
//
//   Rev 1.1   18 Jan 2001 11:55:58   SMITHDAV
//Moved PersistMode enum from DSTCRequestBuffer scope to global scope and into file DSTCPersistentRequestor.hpp so that it can be accessed outside of the DstcDbrkr lib.
//
//   Rev 1.0   23 Oct 2000 20:31:26   SMITHDAV
//Initial revision.
*/