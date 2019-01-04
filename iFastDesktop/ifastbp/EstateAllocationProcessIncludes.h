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

#include <ifastdataimpl\dse_dstc0441_req.hpp> 
#include <ifastdataimpl\dse_dstc0441_vw.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRADE;
   extern IFASTBP_LINKAGE const BFContainerId ESTATE_ALLOCATION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Yes_NO;
   extern CLASS_IMPORT const BFTextFieldId Selected;
   extern CLASS_IMPORT const BFTextFieldId EstateAllocationHeading;
   extern CLASS_IMPORT const BFTextFieldId GISelectedInvestmentsHeading;
}

namespace
{
   const I_CHAR * const CALLER         = I_("Caller");
   const I_CHAR * const TRADE_LIST_KEY = I_("TradeListKey");
   const I_CHAR * const ACCOUNT_NUM    = I_("AccountNum");
}

namespace MFCAN_IP_PARAM
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const CALLER;
   extern IFASTBP_LINKAGE const I_CHAR * const LIST_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const SUB_LIST_KEY;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EstateAllocationProcessIncludes.h-arc  $
//
//   Rev 1.0   25 Jul 2012 15:27:42   if991250
//Initial revision.
//
*/