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
// ^FILE   : BFConnectionMonitor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : BFConnectionMonitor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for a specific connection 
//    monitor. Derived classes are used for ConnectionManager notifications.
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>

class BFHostConnectionManager;

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE BFConnectionMonitor
{
public:
   virtual ~BFConnectionMonitor()
   {
   }

   virtual void registerHostConnectionManager(const BFHostConnectionManager *hostConnectionManager) = 0;
   virtual void unregisterHostConnectionManager(const BFHostConnectionManager *hostConnectionManager) = 0;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/BFConnectionMonitor.hpp-arc  $
// 
//    Rev 1.5   Oct 09 2002 17:40:18   PURDYECH
// New PVCS Database
// 
//    Rev 1.4   22 Mar 2002 15:11:32   PURDYECH
// Removed compile-time "including..." message
// Use #pragma once as include guard
// Include files with lower-case only names
// 
//    Rev 1.3   May 22 2001 13:49:20   MCNABBGL
// server monitoring functionality, explicit server registration with connection manager, fastrequestor modifications
// 
//    Rev 1.2   03 May 2001 14:03:20   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   23 Oct 2000 20:13:16   SMITHDAV
// Change linkage to support new library BFConMfg.
// 
//    Rev 1.0   Apr 28 2000 19:01:10   SMITHDAV
// Initial revision.
//
//   Rev 1.0   Apr 14 2000 14:10:04   SMITHDAV
//Initial revision.
*/