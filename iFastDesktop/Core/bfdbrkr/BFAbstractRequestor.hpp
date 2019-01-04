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
// ^FILE   : FileRequestor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : BFAbstractRequestor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class implements a data requestor that retrieves data from a file.
//
//******************************************************************************
#include <win32\platform.h>
#include <bfdbrkr\bfrequestor.hpp>

#include <memory>

class BFWriteBuffer;
class BFReadBuffer;

#include <bfdbrkr\dbrkrlogger.hpp>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class BFDBRKR_LINKAGE BFAbstractRequestor : public BFRequestor
{
public:
   BFAbstractRequestor();
   virtual ~BFAbstractRequestor();

   BFAbstractRequestor( const BFAbstractRequestor& rhs );

   virtual SEVERITY receive( const BFRequest &request, BFData &queryData, BFData &receivedData, bool *outMoreAvailable = NULL );

   virtual unsigned long getAssignTime() const;

protected:
   virtual BFWriteBuffer *createRequestBuffer(const BFRequest &request) const = 0;
   virtual SEVERITY receiveBuffer( const BFRequest &request, 
                                   const BFWriteBuffer *queryBuffer, 
                                   BFReadBuffer **receivedBuffer, 
                                   const BFData* pQueryData = NULL ) = 0;

   void formatBuffer(const BFData &queryData, BFWriteBuffer *requestBuffer ) const;
   void parseBuffer(BFReadBuffer *responseBuffer, BFData &receivedData ) const;
   void logData ( const DString &fieldName, const DString &fieldValue );
   void logData ( const DString &dstrOutput );
   void logData ( const BFWriteBuffer* pRequestBuffer, const BFReadBuffer* pResponseBuffer, const DString& dstrLabel );
   virtual void logCallingTime() {} 

private:
   void parseBufferComponent( BFReadBuffer *responseBuffer, BFData &data ) const;
   std::auto_ptr< DbrkrLogger > arLogger_;

   mutable unsigned long _assignTime;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfdbrkr/BFAbstractRequestor.hpp-arc  $
//
//   Rev 1.13   May 16 2012 18:07:36   dchatcha
//P0186479 FN10 -Gap 14G - Block Service Unit Transfers, helper key to track view calling time.
//
//   Rev 1.12   Oct 21 2009 10:45:34   purdyech
//LDAP Authorization Support
//
//   Rev 1.11   Mar 27 2009 10:16:02   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.10   Oct 09 2002 17:40:36   PURDYECH
//New PVCS Database
//
//   Rev 1.9   Sep 09 2002 13:30:06   PURDYECH
//Added dtor and copy ctor
//
//   Rev 1.8   Aug 29 2002 12:51:02   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.7   May 28 2002 12:17:18   PURDYECH
//BFData Implementation - Phase II
//
//   Rev 1.6   22 Mar 2002 15:11:28   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.5   26 Oct 2001 12:09:56   HSUCHIN
//minor fix to support error response.
//
//   Rev 1.4   18 Sep 2001 15:20:48   PURDYECH
//Get STUB_DATA working again.
//
//   Rev 1.3   07 Aug 2001 11:33:38   PURDYECH
//Added code to get timing data for the assignment of incoming data to a Data object.
//
//   Rev 1.2   24 Jul 2001 14:43:50   HSUCHIN
//added method logData so that dervived classes can log data
//
//   Rev 1.1   28 Jun 2001 14:22:50   HSUCHIN
//added logging capabilities
//
//   Rev 1.0   17 Jun 2001 11:31:12   PURDYECH
//Initial revision.
//
//   Rev 1.1   30 Oct 2000 11:18:50   SMITHDAV
//Added more recordes available supprort. To requestors.
//
//   Rev 1.0   23 Oct 2000 21:22:38   SMITHDAV
//Initial revision.
 */
