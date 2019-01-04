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
// ^FILE   : SysLoadRequestor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : SysLoadRequestor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class implements a data requestor for standing data.
//
//******************************************************************************
#include <win32\platform.h>
#include <bfdbrkr\bfrequestor.hpp>
#include <assert.h>

// forward declarations
class FileRequestor;

class SysLoadRequestor : public BFRequestor
{
public:
   SysLoadRequestor(FileRequestor &fileRequestor, BFRequestor &baseRequestor);
   virtual ~SysLoadRequestor();

   virtual SEVERITY receive( const BFRequest &request, BFData &queryData, BFData &receivedData, bool *outMoreAvailable = NULL );

   virtual BFRequestor *clone() const
   {
      assert(0);
      throw; // TODO: throw something reasonable
   }

   virtual unsigned long getRequestTime() const { return(0);}
   virtual unsigned long getConnectionTime() const { return(-1);}
   virtual unsigned long getAssignTime() const { return(-1);}

private:
   SysLoadRequestor();
   bool isArchiveValid( const DString& fileName );

   FileRequestor &_fileRequestor;
   BFRequestor &_baseRequestor;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/SysLoadRequestor.hpp-arc  $
//
//   Rev 1.10   Oct 09 2002 17:40:46   PURDYECH
//New PVCS Database
//
//   Rev 1.9   Aug 29 2002 12:49:30   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.8   22 May 2002 17:56:10   PURDYECH
//BFData Implementation
//
//   Rev 1.7   22 Mar 2002 15:17:14   PURDYECH
//BFData integration
//
//   Rev 1.6   29 Oct 2001 16:21:52   PURDYECH
//Added code to support connectionTime reporting for IPBlast
//
//   Rev 1.5   18 Sep 2001 15:20:44   PURDYECH
//Get STUB_DATA working again.
//
//   Rev 1.4   07 Aug 2001 11:24:44   PURDYECH
//Added code to get timing data for the assignment of incoming data to a Data object.
//
//   Rev 1.3   17 Jul 2001 11:08:48   PURDYECH
//Added getRequestTime method
//
//   Rev 1.2   03 May 2001 14:03:10   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   30 Oct 2000 11:18:50   SMITHDAV
//Added more recordes available supprort. To requestors.
//
//   Rev 1.0   23 Oct 2000 20:21:16   SMITHDAV
//Initial revision.
 */
