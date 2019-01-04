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
//    DATE   : Jul 23,2017
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
   extern IFASTBP_LINKAGE const BFContainerId AMS_HYPO_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId REPORT_CRITERIA_LIST;
}
namespace AMS_LMT_OVERRIDE_PROC
{
	const BFFieldId updated(1000);
}

namespace AMS_HYPO_ALLOC_Para
{
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_TYPE; 
   extern IFASTBP_LINKAGE const I_CHAR * const EFFECTIVE_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
}


namespace ifds
{

   extern CLASS_IMPORT const BFTextFieldId AMSType;
   extern CLASS_IMPORT const BFTextFieldId AMSFundAllocHeading;
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace LIST_CHK
{
	const BFFieldId HasCurrPrcntAlloc (30001, I_("HasCurrPrcntAlloc"));
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDCLASS;


#include <ifastdataimpl\dse_dstc0218_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>
#include <ifastdataimpl\dse_dstc0218_vwrepeat_record.hpp>


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AMSHypoAllocProcessIncludes.h-arc  $
//   Rev 1.0   Jul 24 2017 09:25:00   Thanisorn S.
//Initial Revision
//
//
*/

