#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial Data Services
//    AUTHOR : 
//    DATE   : 
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId FUND_MGMT_SETTLEMENT_INSTR_LIST;	
	extern IFASTBP_LINKAGE const BFContainerId SETTLEMENT_INSTRUCTIONS_LIST;

	extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId FundMgmtSettleInstrHeadingSet;
	extern CLASS_IMPORT const BFTextFieldId SettlementInstrHeadingSet;

	extern CLASS_IMPORT const BFTextFieldId SettleAccountNum;
    extern CLASS_IMPORT const BFTextFieldId InternalSettlementAccount;
}

#include <ifastdataimpl\dse_dstc0269_vw.hpp>
#include <ifastdataimpl\dse_dstc0269_req.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0317_req.hpp>
#include <ifastdataimpl\dse_dstc0317_vw.hpp>



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/SettlementInstrProcessIncludes.h-arc  $
//
//   Rev 1.1   Nov 19 2004 17:32:20   aguilaam
//PET117_FN21: settlement instructions enhancement (temporary check-in for build)
//
//   Rev 1.0   Oct 13 2004 15:18:02   VADEANUM
//Initial revision.
//
