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
// ^FILE   : DSTCRequestor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : DSTCRequestor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include <win32\platform.h>
#include <bfdbrkr\BFAbstractRequestor.hpp>

#include <map>
#include <set>

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
   #define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
   #define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class DSTCHost;
class DSTCSecurity;
class BFHost;
class BFRecordConnection;

class IFASTDBRKR_LINKAGE DSTCRequestor : public BFAbstractRequestor
{
public:   
   DSTCRequestor(const DSTCSecurity *security, 
                 bool allResults = true, 
                 bool noDataIsErrorCondition = false,
                 bool bRecycleOnReceive = true );
   DSTCRequestor(const DSTCRequestor &copy);

   virtual ~DSTCRequestor();

   virtual BFRequestor *clone() const;

   virtual unsigned long getRequestTime() const;
   virtual void setRequestTime( unsigned long requestTime );

   virtual unsigned long getConnectionTime() const;
   virtual void setConnectionTime( unsigned long connectionTime );

   virtual SEVERITY receive( const BFRequest &request, 
                             BFData &queryData, 
                             BFData &receivedData, 
                             bool *outMoreAvailable = NULL );

   void filterHostCondition(long condition);
   void clearHostConditionFilter();

   void setRecycleOnReceive( bool bRecycleOnReceive ) { bRecycleOnReceive_ = bRecycleOnReceive; }
   bool getRecycleOnReceive() const { return bRecycleOnReceive_; }

protected:
   virtual BFWriteBuffer *createRequestBuffer(const BFRequest &request) const;
   virtual SEVERITY receiveBuffer( const BFRequest &request, 
                                   const BFWriteBuffer *queryBuffer, 
                                   BFReadBuffer **receivedBuffer, 
                                   const BFData* pQueryData = NULL );

   DSTCRequestor(); // not implemented

   virtual void logCallingTime();

protected:
   const DSTCSecurity *_security;  
private:
   bool _allResults;

   BFRecordConnection *_connection;
   bool bRecycleOnReceive_;

   // HostConditionFilter nested class contains DSTC conditions which will be filtered.
   class HostConditionFilter : public std::set< long, std::less<long> >
   {
   public:
      bool contains(long condition);
   } _hostConditionFilter;

   // HostConditionMap nested class maps all host error codes to DSTC conditions.
   class HostConditionMap : protected std::map< long, long, std::less<long> >
   {
   public:
      HostConditionMap(const long hostConditionArray[][2]);

      long getCondition(long hostErrorCode) const;
   private:
      HostConditionMap(); // not implemented
      void addCondition(long hostErrorCode, long condition);
   };

   static const HostConditionMap _hostConditions;
   static const HostConditionMap _rtsConditions;
   static const HostConditionMap _smqConditions;

   unsigned long  _requestTime;
   unsigned long  _connectionTime;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCRequestor.hpp-arc  $
//
//   Rev 1.19   May 16 2012 18:10:40   dchatcha
//P0186479 FN10 -Gap 14G - Block Service Unit Transfers, helper key to track view calling time.
//
//   Rev 1.18   Oct 21 2009 10:20:00   purdyech
//LDAP Authorization Support
//
//   Rev 1.17   Jun 05 2009 08:21:14   purdyech
//Fixed names of SonicSingle and SonicMulti queues in configuration.
//SonicErrorMessages are now handled appropriately.
//
//   Rev 1.16   Mar 27 2009 10:22:18   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.15   Mar 12 2007 12:07:32   purdyech
//Implemented changes for "RecycleOnReceive" logic.  Needed getter/setter for bRecycleOnReceive_
//
//   Rev 1.14   Nov 08 2006 14:34:44   fengyong
//Incident 751006 - matching rts conditions
//
//   Rev 1.13   Feb 25 2004 11:07:40   PURDYECH
//PET910 - Updated recycling logic
//
//   Rev 1.12   Mar 21 2003 18:29:20   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.11   Oct 09 2002 23:55:22   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.10   22 May 2002 18:21:24   PURDYECH
//BFData Implementation
//
//   Rev 1.9   13 Nov 2001 14:15:16   PURDYECH
//Add connectionTime implementation
//
//   Rev 1.8   25 Sep 2001 13:23:42   PURDYECH
//Added setRequestTime method to allow the request time to be set externally.
//
//   Rev 1.7   07 Aug 2001 11:33:50   PURDYECH
//Added code to get timing data for the assignment of incoming data to a Data object.
//
//   Rev 1.6   17 Jul 2001 11:24:00   PURDYECH
//Added getRequestTime method
//
//   Rev 1.5   Jun 26 2001 12:54:52   PURDYECH
//Infrastructure Release 1.9 Integration.
//
//   Rev 1.4   03 May 2001 14:04:02   SMITHDAV
//Session management restructuring.
//
//   Rev 1.3   Feb 12 2001 15:53:36   HSUCHIN
//The host is not set on the constuctor, but set using setHost method
//
//   Rev 1.2   15 Nov 2000 15:28:42   SMITHDAV
//Add support for condition filtering.
//
//   Rev 1.1   30 Oct 2000 11:21:54   SMITHDAV
//Add support for getting more records. Also ignore no data found conditions by default.
//
//   Rev 1.0   23 Oct 2000 20:34:32   SMITHDAV
//Initial revision.
 */
