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
// ^FILE   : BFHostConnectionMonitor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : BFHostConnectionMonitor
// ^INHERITS FROM : Thread
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract host connection monitor class 
//    with basic interval connection refreshing.
//
//******************************************************************************
#include <win32\platform.h>

class BFHostConnectionManager;

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE BFHostConnectionMonitor
{
public:

   virtual ~BFHostConnectionMonitor();
   virtual bool refresh() = 0;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/BFHostConnectionMonitor.hpp-arc  $
// 
//    Rev 1.7   Oct 09 2002 17:40:20   PURDYECH
// New PVCS Database
// 
//    Rev 1.6   22 Mar 2002 15:11:36   PURDYECH
// Removed compile-time "including..." message
// Use #pragma once as include guard
// Include files with lower-case only names
// 
//    Rev 1.5   Jun 26 2001 12:54:44   PURDYECH
// Infrastructure Release 1.9 Integration.
// 
//    Rev 1.4   Jun 20 2001 18:40:30   IVESPAUL
// Creation and destroy host connection monitors.
// 
//    Rev 1.3   03 May 2001 14:03:22   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.2   06 Dec 2000 11:47:44   SMITHDAV
// Update monitoring console; Added DataBroker monitor.
// 
//    Rev 1.1   23 Oct 2000 20:13:20   SMITHDAV
// Change linkage to support new library BFConMfg.
// 
//    Rev 1.0   Apr 28 2000 19:01:12   SMITHDAV
// Initial revision.
//
//   Rev 1.0   Apr 14 2000 13:47:42   SMITHDAV
//Initial revision.
*/