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
// ^FILE   : BFConnection.hpp
// ^AUTHOR : David B. Smith
// ^DATE   : January 2000
//
// ^CLASS    : BFConnection
// ^INHERITS FROM :
//
// ^CLASS DESCRIPTION :
//    This class provides an abstract interface for the specific connection
//    classes.
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE BFConnection
{
public:
   virtual ~BFConnection()
   {
   }

   virtual const DStringA &getHostId() const = 0;
   virtual const DStringA &getDescription() const = 0;

   virtual bool recycle()
   {
      return(true);
   }
   virtual void setRecycleRequired()
   {
   }
   virtual bool isRecycleRequired() const
   {
      return(false);
   }

   virtual bool isStale() const = 0;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfconmgr/BFConnection.hpp-arc  $
//
//   Rev 1.8   Jan 27 2003 14:53:06   PURDYECH
//Added BFRecordConnection
//
//   Rev 1.7   Oct 09 2002 17:40:16   PURDYECH
//New PVCS Database
//
//   Rev 1.6   22 Mar 2002 15:11:32   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.5   Oct 22 2001 17:17:30   HUDAVID
//Connection Recycle code.
//
//   Rev 1.4   03 May 2001 14:03:20   SMITHDAV
//Session management restructuring.
//
//   Rev 1.3   29 Nov 2000 11:19:24   SMITHDAV
//Update to stale-out failed connection so they are not reused.
//
//   Rev 1.2   23 Oct 2000 20:13:10   SMITHDAV
//Change linkage to support new library BFConMfg.
//
//   Rev 1.1   Apr 28 2000 19:23:08   SMITHDAV
//Add virtual destructor ... as a result needed to export the class. (Don't you just love C++ )
//
//   Rev 1.0   Apr 14 2000 14:10:04   SMITHDAV
//Initial revision.
*/