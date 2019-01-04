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
// ^FILE   : BFRequest.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : BFRequest
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific request 
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

class BFDBRKR_LINKAGE BFRequest
{
public:
   virtual ~BFRequest() {}
   virtual const DString &getId() const = 0;
   virtual bool isSysLoadRequest() const {return(false);}
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/BFRequest.hpp-arc  $
//
//   Rev 1.3   Oct 09 2002 17:40:38   PURDYECH
//New PVCS Database
//
//   Rev 1.2   22 Mar 2002 15:11:42   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   03 May 2001 14:03:24   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   23 Oct 2000 21:22:40   SMITHDAV
//Initial revision.
*/