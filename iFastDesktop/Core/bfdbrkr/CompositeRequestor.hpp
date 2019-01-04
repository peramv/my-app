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
// ^FILE   : CompositeRequestor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : CompositeRequestor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class implements a composite requestor of two or more BFRequestor instances.
//    The receive method calls,in order, the receive method of each of the contained
//    requestors.
//
//******************************************************************************
#include <win32\platform.h>
#include <bfdbrkr\BFRequestor.hpp>
#include <vector>
#include <assert.h>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class BFRequestorFactory;
class BFData;

class BFDBRKR_LINKAGE CompositeRequestor : public BFRequestor
{
public:
   CompositeRequestor(const CompositeRequestor &copy);

   virtual ~CompositeRequestor();

   virtual SEVERITY receive( const BFRequest &request, BFData &queryData, BFData &receivedData, bool *outMoreAvailable = NULL );

   virtual BFRequestor *clone() const
   {
      assert(0);
      throw; // TODO: throw something reasonable
   }

   virtual unsigned long getRequestTime() const { return(-1);}
   virtual unsigned long getConnectionTime() const { return(-1);}
   virtual unsigned long getAssignTime() const { return(-1);}

   virtual int getCompositeCount() const;
   virtual BFRequestor **getCompositeElements() const;

private:
   CompositeRequestor();

   int _count;
   BFRequestor **_elements;

   friend BFDBRKR_LINKAGE CompositeRequestor operator+(const BFRequestor &requestor1, const BFRequestor &requestor2);
};

BFDBRKR_LINKAGE CompositeRequestor operator+(const BFRequestor &requestor1, const BFRequestor &requestor2);

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/CompositeRequestor.hpp-arc  $
//
//   Rev 1.9   Oct 09 2002 17:40:42   PURDYECH
//New PVCS Database
//
//   Rev 1.8   Aug 29 2002 12:51:16   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.7   22 May 2002 18:08:52   PURDYECH
//BFData Implementation
//
//   Rev 1.6   22 Mar 2002 15:11:50   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.5   29 Oct 2001 16:22:06   PURDYECH
//Added code to support connectionTime reporting for IPBlast
//
//   Rev 1.4   07 Aug 2001 11:33:40   PURDYECH
//Added code to get timing data for the assignment of incoming data to a Data object.
//
//   Rev 1.3   17 Jul 2001 11:22:30   PURDYECH
//Added getRequestTime method
//
//   Rev 1.2   03 May 2001 14:03:28   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   30 Oct 2000 11:18:52   SMITHDAV
//Added more recordes available supprort. To requestors.
//
//   Rev 1.0   23 Oct 2000 21:22:40   SMITHDAV
//Initial revision.
*/
