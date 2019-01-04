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
//    Copyright 2002 by Internantional Financial.
//
//******************************************************************************

//#include <ifastdataimpl\dse_dstc0305_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_dstc0230_req.hpp>
#include <ifastdataimpl\dse_dstc0230_vw.hpp>
#include <ifastdataimpl\dse_dstc0231_req.hpp>
#include <ifastdataimpl\dse_dstc0232_vw.hpp>
#include <ifastdataimpl\dse_dstc0231_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_SYSTEM_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_SYSTEM_SCALE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_SYSTEM_THRESHOLD_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeThresholdSysHeading;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleListSet;
   extern CLASS_IMPORT const BFTextFieldId FeeParamSysHeading;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleSysHeading;
   extern CLASS_IMPORT const BFTextFieldId SysFeeGridSet;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId TradingAttributesHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleSysInvestTermHeading;
   extern CLASS_IMPORT const BFTextFieldId ThrshldUserName;
}

namespace FEETYPE
{
   extern IFASTBP_LINKAGE const I_CHAR * const FLAT;
   extern IFASTBP_LINKAGE const I_CHAR * const PERCENTAGE;
   extern IFASTBP_LINKAGE const I_CHAR * const SCALE;
   extern IFASTBP_LINKAGE const I_CHAR * const TIER;
   extern IFASTBP_LINKAGE const I_CHAR * const TIER_BY_THRESHOLD;
   extern IFASTBP_LINKAGE const I_CHAR * const SCALE_BY_THRESHOLD;
}

