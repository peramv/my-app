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
// ^FILE   : BFDataBroker.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : BFDataBroker
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an singleton data broker.
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfdata\bfdata.hpp>
#include <condition.hpp>
#include <bfutil/bfcritsec.hpp>
#include <bfutil/bfguard.hpp>

// forward declarations
class BFRequest;
class BFRequestor;
class FileRequestor;
class BaseDBSecurity;

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class BFDBRKR_LINKAGE BFDataBroker 
{
public:

   static BFDataBroker *getInstance( void );
   static void killInstance( void );

   virtual SEVERITY receive( const BFRequest &request,
                             BFData &queryData,
                             BFData &receivedData,
                             BFRequestor &requestor,
                             bool *outMoreAvailable = NULL );


   unsigned int getRequestCount() const { BFGuard g( csCount_ ); return(_requestCount); }
   unsigned int getConditionCount() const { BFGuard g( csCount_ ); return(_conditionCount); }
   unsigned int getInformationCount() const { BFGuard g( csCount_ ); return(_informationCount); }
   unsigned int getWarningCount() const { BFGuard g( csCount_ ); return(_warningCount); }
   unsigned int getSevereErrorCount() const { BFGuard g( csCount_ );  return(_severeErrorCount); }
   unsigned int getCriticalErrorCount() const { BFGuard g( csCount_ ); return(_criticalErrorCount); }

   enum StubMode
   {
      OFF = 0,
      OFFLINE,
      COLLECT
   };

   StubMode getStubMode() {return(_stubMode);}

private:
   BFDataBroker();
   ~BFDataBroker();

   void incrementRequestStats(SEVERITY severity);

   static BFDataBroker *_pInstance;

   FileRequestor *_sysLoadFileRequestor;

   mutable BFCritSec csCount_;
   unsigned int _requestCount;
   unsigned int _conditionCount;
   unsigned int _informationCount;
   unsigned int _warningCount;
   unsigned int _severeErrorCount;
   unsigned int _criticalErrorCount;

   DString  _stubFilesPath;
   StubMode _stubMode;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfdbrkr/BFDataBroker.hpp-arc  $
//
//   Rev 1.11   Aug 12 2003 10:08:00   PURDYECH
//Added new logging method (bf::log::...)
//
//   Rev 1.10   Oct 09 2002 17:40:36   PURDYECH
//New PVCS Database
//
//   Rev 1.9   Aug 29 2002 12:51:04   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.8   Jul 05 2002 08:47:20   PURDYECH
//Fixed include files
//Cleaned up obsolete code.
//
//   Rev 1.7   22 May 2002 18:08:46   PURDYECH
//BFData Implementation
//
//   Rev 1.6   22 Mar 2002 15:11:34   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.5   18 Sep 2001 15:20:48   PURDYECH
//Get STUB_DATA working again.
//
//   Rev 1.4   31 May 2001 17:41:28   YINGZ
//remove #debug
//
//   Rev 1.3   03 May 2001 14:03:20   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   06 Dec 2000 11:47:44   SMITHDAV
//Update monitoring console; Added DataBroker monitor.
//
//   Rev 1.1   30 Oct 2000 11:18:50   SMITHDAV
//Added more recordes available supprort. To requestors.
//
//   Rev 1.0   23 Oct 2000 21:22:40   SMITHDAV
//Initial revision.
*/
