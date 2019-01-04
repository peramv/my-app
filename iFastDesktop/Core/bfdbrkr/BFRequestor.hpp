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
// ^FILE   : BFRequestor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : BFRequestor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific requestor 
//    classes.
//
//******************************************************************************
#include <win32\platform.h>
#include <condition.hpp>


// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

// forward declarations
class BFData;
class BFRequest;

class BFDBRKR_LINKAGE BFRequestor
{
public:
   virtual ~BFRequestor() {}

   virtual SEVERITY receive( const BFRequest &request, BFData &queryData, BFData &receivedData, bool *outMoreAvailable = NULL ) = 0;

   // required to provide the deep copies required by the CompositeRequestor.
   // A new copy of this object must be allocated and returned.
   virtual BFRequestor *clone() const = 0;

   /**
    * return the amount of time the request took to execute, in milliseconds.
    * 
    * @return The number of milliseconds the request took to execute, regardless
    *         of success or failure.  If the request hasn't been executed yet
    *         it should return -1.
    */
   virtual unsigned long getRequestTime() const = 0;


   /**
    * set the value of the RequestTime.  This is useful if the requestor
    * is diverted and a proxy does the work.  The proxy can then set
    * the RequestTime for the (apparently) real requestor
    * 
    * @param requestTime
    *               The time taken to satisfy the request, in milliseconds.
    */
   virtual void setRequestTime( unsigned long requestTime ) {}

   virtual unsigned long getConnectionTime() const = 0;
   virtual void setConnectionTime( unsigned long requestTime ) {}

   /**
    * return the amount of time the request took to assign the result to a Data object, in milliseconds.
    * 
    * @return The number of milliseconds the request took to assign to receivedData, regardless
    *         of success or failure.  If the request hasn't been assigned yet
    *         it should return -1.
    */
   virtual unsigned long getAssignTime() const = 0;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/BFRequestor.hpp-arc  $
//
//   Rev 1.10   Oct 09 2002 17:40:40   PURDYECH
//New PVCS Database
//
//   Rev 1.9   Aug 29 2002 12:51:14   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.8   22 May 2002 18:08:50   PURDYECH
//BFData Implementation
//
//   Rev 1.7   22 Mar 2002 15:11:44   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.6   29 Oct 2001 16:22:06   PURDYECH
//Added code to support connectionTime reporting for IPBlast
//
//   Rev 1.5   25 Sep 2001 13:23:40   PURDYECH
//Added setRequestTime method to allow the request time to be set externally.
//
//   Rev 1.4   07 Aug 2001 11:33:40   PURDYECH
//Added code to get timing data for the assignment of incoming data to a Data object.
//
//   Rev 1.3   17 Jul 2001 11:22:10   PURDYECH
//Added getRequestTime method
//
//   Rev 1.2   03 May 2001 14:03:24   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   30 Oct 2000 11:18:50   SMITHDAV
//Added more recordes available supprort. To requestors.
//
//   Rev 1.0   23 Oct 2000 21:22:40   SMITHDAV
//Initial revision.
 */
