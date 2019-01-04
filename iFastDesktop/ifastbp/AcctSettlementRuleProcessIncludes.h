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
//    Copyright 2008 by International Financial Data Services
//    AUTHOR : Chatchai Daecha
//    DATE   : Febuary 2008
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
    extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
    extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
    extern IFASTBP_LINKAGE const BFContainerId ACCT_SETTLEMENT_RULE_LIST;  
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId AcctSettlementRuleHeadingSet;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE;

const BFFieldId IsSettlementRulePendingTrade (10000001, I_("IsSettlementRulePendingTrade"));

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0386_req.hpp>
#include <ifastdataimpl\dse_dstc0386_vw.hpp>
#include <ifastdataimpl\dse_dstc0386_vwrepeat_record.hpp>

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctSettlementRuleProcessIncludes.h-arc  $ */
//
//   Rev 1.1   Apr 16 2008 18:28:02   daechach
//PET2385 FN02&07 - Modified code regarding code review.
