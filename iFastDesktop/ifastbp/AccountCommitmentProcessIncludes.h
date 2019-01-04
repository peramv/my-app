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
#include <ifastdataimpl\dse_dstc0432_vw.hpp>
#include <ifastdataimpl\dse_dstc0433_vw.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_COMMITMENT;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_COMMITMENT_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_COMMITMENT_ACTIVITY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId COMMITMENT_PRODUCT_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ForcedRate;
   extern CLASS_IMPORT const BFTextFieldId AccountCommitmentsHeading;
   extern CLASS_IMPORT const BFTextFieldId AccountCommitActivityHeading;
   extern CLASS_IMPORT const BFTextFieldId IsDuringNASU;

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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountCommitmentProcessIncludes.h-arc  $
//
//   Rev 1.3   Feb 24 2012 18:39:28   if991250
//Account Commitment
//
//   Rev 1.2   Feb 22 2012 16:55:58   if991250
//Account Commitment
//
//   Rev 1.1   Feb 17 2012 10:34:10   if991250
//Account Commitment
//
//   Rev 1.0   Jan 20 2012 16:21:10   if991250
//Initial revision.
 * 
*/