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
// ^FILE   : DSTCResponseBuffer.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : DSTCResponseBuffer
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfdbrkr\bfreadbuffer.hpp>

class DSTCRequest;
class BFDataFieldProperties;

class DSTCResponseBuffer : public BFReadBuffer
{
public:

   enum ResponseType
   {
      OK_RESPONSE = 0,
      ERROR_RESPONSE,
      UNKNOWN_ERROR_RESPONSE,
      SMQ_FRAMEWORK_ERROR_RESPONSE
   };

   DSTCResponseBuffer(const DSTCRequest &request, const DStringA &buffer);
   virtual ~DSTCResponseBuffer();

   ResponseType getResponseType() const;

   long getHostErrorCode() const;
   DString getHostErrorCodeString() const;
   DString getHostErrorMessage() const;
   const DString& getHostErrorTrackId() const { return _hostErrorTrackId; }

   DStringA getPersistHandle() const;
   void setPersistHandle( const DStringA& dstrPersistHandle );

   virtual void readStart();

   virtual void readStartFixed();
   virtual bool readField(const BFDataFieldProperties& fieldProperties,  DString &outFieldValue);
   virtual void readEndFixed();

   virtual bool readStartRepeatSection();

   virtual bool readStartRepeat();
   virtual void readEndRepeat();

   virtual void readEndRepeatSection();

   virtual void readEnd();
   virtual const DStringA &getString() const;
   virtual const bool isAtEnd() const {return _position == DStringA::npos;}
private:
   char getDelimiter() const { return _chDelimiter; }
   const DStringA getDelimiterString() const { 
      char szDelim[2]; szDelim[0] = getDelimiter(); szDelim[1] = 0x00; 
      return DStringA(szDelim); }
   void setDelimiter(char chDelim) { _chDelimiter = chDelim; }
   char _chDelimiter;

   bool getUnknownFlag();
   void getUnescapedFieldValue(DStringA &fieldString);
   void getNumericFieldValue(DStringA &fieldString);
   void parserError();

   DStringA::size_type incrementPosition(DStringA::size_type increment=1);

   DString buildResponseExeptionParameterIDI(const DStringA &expected);

   const DSTCRequest &_request;

   DStringA _buffer;
   DStringA::size_type _position;

   ResponseType _responseType;
   long _hostErrorCode;
   DString _hostErrorCodeString;
   DString _hostErrorMessage;
   DString _hostErrorTrackId;

};

//CP
//CP#endif // #ifndef DSTCRESPONSEBUFFER_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCResponseBuffer.hpp-arc  $
//
//   Rev 1.12   Jul 28 2009 09:12:32   purdyech
//CR24095 - Performance Update to work around OpenEdge problem.
//
//   Rev 1.11   Jun 05 2009 08:23:58   purdyech
//Fixed names of SonicSingle and SonicMulti queues in configuration.
//SonicErrorMessages are now handled appropriately.
//
//   Rev 1.10   Feb 06 2009 14:54:00   purdyech
//Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
//
//   Rev 1.9   Oct 09 2002 23:55:24   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Aug 29 2002 12:51:20   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.7   May 28 2002 12:17:34   PURDYECH
//BFData Implementation - Phase II
//
//   Rev 1.6   22 Mar 2002 15:36:08   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//BFData integration
//
//   Rev 1.5   26 Oct 2001 11:05:48   HSUCHIN
//added getString() functionality.
//
//   Rev 1.4   16 Feb 2001 14:40:16   SMITHDAV
//Fixed UNKNOWN_ERROR_RESPONSE response type handling.
//
//   Rev 1.3   09 Feb 2001 14:37:10   SMITHDAV
//Improve DSTCResponseBuffer exception reporting.
//
//   Rev 1.2   20 Nov 2000 17:37:46   SMITHDAV
//Fixed parsing to handle end of buffer correctly .
//
//   Rev 1.1   26 Oct 2000 17:25:40   SMITHDAV
//Added numeric support
//
//   Rev 1.0   23 Oct 2000 20:31:26   SMITHDAV
//Initial revision.
*/