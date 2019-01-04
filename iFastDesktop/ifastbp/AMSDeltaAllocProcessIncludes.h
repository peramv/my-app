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
//    Copyright 2002 by International Financial Data Services
//    AUTHOR : Thanisorn Sangkrajang
//    DATE   : Jan 10,2018
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
   extern IFASTBP_LINKAGE const BFContainerId AMS_FUND_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AMS_DELTA_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AMS_MST_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}

namespace AMS_DELTA_ALLOC_Para
{
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_TYPE; 
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_EFFECTIVE_DATE; 
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_REC_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_SEARCH_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_SEARCH_CODE;

}

namespace ifds
{

   extern CLASS_IMPORT const BFTextFieldId AMSType;
   extern CLASS_IMPORT const BFTextFieldId AMSFundAllocHeading;
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace AMS_DELTA
{
   const BFFieldId oldDeltaPrcnt (30001, I_("oldDeltaPrcnt"));
}

#include <ifastdataimpl\dse_dstc0218_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>
#include <ifastdataimpl\dse_dstc0218_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0483_req.hpp>
#include <ifastdataimpl\dse_dstc0483_vw.hpp>
#include <ifastdataimpl\dse_dstc0483_vwrepeat_record.hpp>