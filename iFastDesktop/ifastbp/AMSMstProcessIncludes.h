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
//    AUTHOR : Yingbao Li
//    DATE   : May 24,2002
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
   extern IFASTBP_LINKAGE const BFContainerId AMS_ALLOCATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AMS_MST_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AMS_MST_SEARCH;

}
namespace AMS_PROC
{

//CP20030319   const int AMS_MST_LIST = 1;
//CP20030319   const int AMS_ALLOCATION_LIST = 2;
	const BFFieldId updated(1000);
    const BFFieldId ORG_KEY(1100);
    const BFFieldId DEST_KEY(1200);

}

namespace AMS_Para
{
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCR; 
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_DETAIL; 
   extern IFASTBP_LINKAGE const I_CHAR * const AMS_TYPE; 
   extern IFASTBP_LINKAGE const I_CHAR * const DEFAULT_AMS_TYPE; 
   extern IFASTBP_LINKAGE const I_CHAR * const EFFECTIVE_DATE;; 



}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AMSGlobalHeading;
   extern CLASS_IMPORT const BFTextFieldId AMSFundAllocHeading;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFTextFieldId  ClientAMSType;
   extern CLASS_IMPORT const BFTextFieldId ForeignRelFundNum;
   extern CLASS_IMPORT const BFTextFieldId RoundingFundNum;
   extern CLASS_IMPORT const BFTextFieldId AMSSearchType;

}

namespace AMS_DELTA
{
  const BFFieldId IsAMSUpdate(40001, I_("IsAMSUpdate"));
  const BFFieldId IsAMSFundUpdate(40002, I_("IsAMSFundUpdate"));
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDCLASS;



#include <ifastdataimpl\dse_dstc0179_vw.hpp>
#include <ifastdataimpl\dse_dstc0218_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>
#include <ifastdataimpl\dse_dstc0219_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AMSMstProcessIncludes.h-arc  $
//
//   Rev 1.5   Aug 22 2003 13:21:06   linmay
//added AMS_MST_SEARCH and AmsSearchType
//
//   Rev 1.4   Jul 18 2003 11:18:30   linmay
//modified for CIBC AMS
//
//   Rev 1.3   Apr 21 2003 09:40:06   YINGBAOL
//reimplemt AMSType 
//
//   Rev 1.2   Mar 21 2003 17:36:00   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Dec 27 2002 11:18:42   linmay
//added AMSType
//
//   Rev 1.0   Nov 25 2002 10:04:32   YINGBAOL
//Initial Revision
//



 */

