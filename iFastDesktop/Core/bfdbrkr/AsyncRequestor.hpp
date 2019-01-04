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
// ^FILE   : AsyncRequestor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : AsyncRequestor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class implements an asyncronous data requestor that retrieves data 
//    from the underlying data requestor.
//
//******************************************************************************
#include <win32\platform.h>
#include <bfdbrkr\bfrequestor.hpp>
#include <bfutil\bfthread.hpp>
#include <bfutil\bfsemaphore.hpp>
#include <assert.h>

class AsyncRequestListener;
class BFRequest;

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif


class BFDBRKR_LINKAGE AsyncRequestor : public BFRequestor, public BFThread
{
public:
   AsyncRequestor(const BFRequestor &baseRequestor, AsyncRequestListener *listener, int callBackOption = 0);
   AsyncRequestor(BFRequestor *baseRequestor, AsyncRequestListener *listener, int callBackOption = 0);

   virtual ~AsyncRequestor();

   virtual SEVERITY receive( const BFRequest &request, 
                             BFData &queryData, 
                             BFData &receivedData, 
                             bool *outMoreAvailable = NULL );

   virtual BFRequestor *clone() const
   {
      assert(0);
      throw; // TODO: throw something reasonable
   }

   virtual unsigned long getRequestTime() const { return(-1);}
   virtual unsigned long getConnectionTime() const { return(-1);}
   virtual unsigned long getAssignTime() const { return(-1);}

protected:
   virtual void run();

private:
   AsyncRequestor();

   BFRequestor *_baseRequestor;
   AsyncRequestListener *_listener;

   BFSemaphore _startedSemaphore;

   const BFRequest *_request;
   BFData*   queryBFData_;
   BFData*   receivedBFData_;
   int _callBackOption;

   DWORD _tidCaller;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfdbrkr/AsyncRequestor.hpp-arc  $
//
//   Rev 1.12   Oct 21 2009 10:42:50   purdyech
//LDAP Authorization Support
//
//   Rev 1.11   Oct 09 2002 17:40:34   PURDYECH
//New PVCS Database
//
//   Rev 1.10   Aug 29 2002 12:51:02   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.9   22 May 2002 18:08:42   PURDYECH
//BFData Implementation
//
//   Rev 1.8   22 Mar 2002 15:11:22   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.7   29 Oct 2001 16:22:06   PURDYECH
//Added code to support connectionTime reporting for IPBlast
//
//   Rev 1.6   07 Aug 2001 11:33:38   PURDYECH
//Added code to get timing data for the assignment of incoming data to a Data object.
//
//   Rev 1.5   17 Jul 2001 11:22:12   PURDYECH
//Added getRequestTime method
//
//   Rev 1.4   Jun 27 2001 20:07:38   PURDYECH
//Resolve Infrastructure Class Name collisions by renaming all of the classes which they expropriated into their own code.
//
//   Rev 1.3   Jun 26 2001 12:54:42   PURDYECH
//Infrastructure Release 1.9 Integration.
//
//   Rev 1.2   03 May 2001 14:03:18   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   Jan 29 2001 12:15:30   HSUCHIN
//changed Async stuff to support cbo overrides and a couple bug fixes
//
//   Rev 1.0   11 Jan 2001 10:08:28   SMITHDAV
//Initial revision.
 */
