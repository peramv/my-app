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
//    Copyright 2004 by IFDS.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

#include <ifastdataimpl\dse_dstc0315_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId BROKER_REMARK_LIST;
	extern IFASTBP_LINKAGE const BFContainerId BRANCH_REMARK_LIST;
	extern IFASTBP_LINKAGE const BFContainerId AGENT_REMARK_LIST;

}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerRemarkProcessIncludes.h-arc  $
//
//   Rev 1.0   Sep 24 2004 14:49:48   YINGBAOL
//Initial revision.
 * 

  */


