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
// ^FILE   : BFHost.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : BFHost
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific host 
//    classes.
//
//******************************************************************************
#include <win32\platform.h>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class DString;
class BFSecurity;

class BFDBRKR_LINKAGE BFHost
{
public:
   virtual ~BFHost() {}
   virtual const DString &getId() const = 0;
   virtual BFSecurity *createSecurity() const = 0;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/BFHost.hpp-arc  $
//
//   Rev 1.4   Oct 09 2002 17:40:38   PURDYECH
//New PVCS Database
//
//   Rev 1.3   22 Mar 2002 15:11:36   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.2   03 May 2001 14:03:22   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   23 Oct 2000 22:05:16   SMITHDAV
//Removed Include for BFRequesorFactory.hpp -no longer used.
//
//   Rev 1.0   23 Oct 2000 21:22:40   SMITHDAV
//Initial revision.
*/