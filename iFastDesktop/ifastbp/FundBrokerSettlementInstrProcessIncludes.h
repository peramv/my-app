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
//    Copyright 2004 by International Financial Data Services
//    AUTHOR : 
//    DATE   : 
//
//******************************************************************************

#include "SettlementInstrProcessincludes.h"

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundMgmtSettlInstrHeadingSet;
	extern CLASS_IMPORT const BFTextFieldId SettleLocationAcctLvlHeading;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_BROKER_SETTLEMENT_INSTR;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUND_BROKER_SETTLEMENT_INSTR;

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId FUND_BROKER_LIST;	
}

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0269_vw.hpp>
#include <ifastdataimpl\dse_dstc0269_req.hpp>
#include <ifastdataimpl\dse_dstc0317_req.hpp>
#include <ifastdataimpl\dse_dstc0317_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/FundBrokerSettlementInstrProcessIncludes.h-arc  $
//
//   Rev 1.0   Nov 26 2004 16:52:42   aguilaam
//Initial revision.
//
//   Rev 1.0   Oct 13 2004 15:22:30   VADEANUM
//Initial revision.
//
