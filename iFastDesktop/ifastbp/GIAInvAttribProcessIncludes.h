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
//    Copyright 2011 by DST Systems, Inc.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0115_req.hpp> 

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRADE;
   extern IFASTBP_LINKAGE const BFContainerId PROGRESSIVE_INTEREST_RATE_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ForcedRate;
}

namespace
{
   const I_CHAR * const CALLER         = I_("Caller");
   const I_CHAR * const TRADE_LIST_KEY = I_("TradeListKey");
   const I_CHAR * const ACCOUNT_NUM    = I_("AccountNum");
}

namespace MFCAN_IP_PARAM
{
   extern IFASTBP_LINKAGE const I_CHAR * const LIST_KEY;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/GIAInvAttribProcessIncludes.h-arc  $
//
//   Rev 1.2   Dec 03 2011 01:28:16   dchatcha
//P0186477/FN03 - GIA - Purchase
//
//   Rev 1.1   Nov 27 2011 19:33:50   popescu
//INA Commission Work
//
//   Rev 1.0   Apr 20 2010 00:59:50   popescu
//Initial revision.
//
 * 
*/