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
// ^FILE   : AsyncRequestListener.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : AsyncRequestListener
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for a listener for asyncronous request.
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

class Condition;
class Data;
class BFData;

class BFDBRKR_LINKAGE AsyncRequestListener
{
public:
   virtual ~AsyncRequestListener() {}
   virtual void notifyResponse( SEVERITY severity, 
                                const Condition *condition, 
                                BFData *receivedData, 
                                bool moreAvailable,
                                int callBackOption = 0) = 0;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/AsyncRequestListener.hpp-arc  $
//
//   Rev 1.7   Oct 09 2002 17:40:34   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Aug 29 2002 12:51:12   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   22 Mar 2002 15:11:22   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.4   03 May 2001 14:03:18   SMITHDAV
//Session management restructuring.
//
//   Rev 1.3   Jan 29 2001 12:15:30   HSUCHIN
//changed Async stuff to support cbo overrides and a couple bug fixes
//
//   Rev 1.2   11 Jan 2001 13:46:02   SMITHDAV
//Changed signature if AsyncRequestListener::notifyResponse.
//
//   Rev 1.1   11 Jan 2001 12:28:42   SMITHDAV
//add condition stuff to listener interface
//
//   Rev 1.0   11 Jan 2001 10:08:26   SMITHDAV
//Initial revision.
*/