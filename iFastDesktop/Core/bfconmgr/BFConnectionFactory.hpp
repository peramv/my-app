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
// ^FILE   : BFConnection.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : BFConnectionFactory
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the specific connection 
//    factory classes.
//
//******************************************************************************
#include <win32\platform.h>

class BFConnection;

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE BFConnectionFactory
{
public:
   virtual ~BFConnectionFactory() {}

   virtual BFConnection *createConnection(const DStringA &hostId) = 0;
   virtual void destroyConnection(BFConnection *connection) = 0;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/BFConnectionFactory.hpp-arc  $
//
//   Rev 1.5   Oct 09 2002 17:40:16   PURDYECH
//New PVCS Database
//
//   Rev 1.4   22 Mar 2002 15:11:32   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.3   03 May 2001 14:03:20   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   23 Oct 2000 20:13:14   SMITHDAV
//Change linkage to support new library BFConMfg.
//
//   Rev 1.1   Apr 28 2000 19:24:02   SMITHDAV
//Added destructor ... as a result nedded export the class.
//
//   Rev 1.0   Apr 14 2000 14:10:04   SMITHDAV
//Initial revision.
*/