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
//    Copyright 2003 by Internantional Financial.
//
//******************************************************************************

#include <ifastdataimpl\dse_dstc0067_vw.hpp>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0129_req.hpp>
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId RRIF_LIF_LRIF_INFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_FROM_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_TO_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACOUNT;
}


namespace FTALLOCATION  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const CURRENT_KEY;
   const BFFieldId PRIMARY_ACCOUNT_OWNER(100L);
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFDecimalFieldId TotAmount;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
	extern CLASS_IMPORT const BFTextFieldId	LV_FundAllocation;
   extern CLASS_IMPORT const BFTextFieldId TransType;


}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FromToAllocationProcessIncludes.h-arc  $
//
//   Rev 1.0   Jun 09 2003 11:17:04   YINGBAOL
//Initial revision.

 * 
 */