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
    extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
    extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
    extern IFASTBP_LINKAGE const BFContainerId ACCT_ROUNDING_RULE_LIST;  
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId AcctRoundingRuleHeadingSet;
}

namespace NASULIT // NASU literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_ACCOUNT;
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_SHAREHOLDER;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCT_ROUNDING_RULE;

const BFFieldId IsAcctRoundingRulePendProcTrade (10000002, I_("IsAcctRoundingRulePendProcTrade"));

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0480_req.hpp>
#include <ifastdataimpl\dse_dstc0480_vw.hpp>
#include <ifastdataimpl\dse_dstc0480_vwrepeat_record.hpp>



