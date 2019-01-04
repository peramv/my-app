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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

//******************************************************************************
//
// ^FILE   : ClientProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 22/04/1999
//
// -----------------------------------------------------------------------------


// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by entity here

// Temporarily, defining fields to use


// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//const int PROC_GEN_LIST    = 1;
//CP20030319const int ACCOUNT_SEARCH_LIST = 1;

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0198_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_SEARCH_LIST;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountSearchProcessIncludes.h-arc  $
//
//   Rev 1.4   Mar 21 2003 17:34:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:52:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   22 May 2002 18:21:56   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:14:50   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   Jan 25 2002 11:57:54   FENGYONG
//Initial revision.
 * 
 */

