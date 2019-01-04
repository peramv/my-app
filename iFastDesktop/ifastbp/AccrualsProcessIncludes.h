#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0062_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0063_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0020_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0049_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INTEREST_ACCRUAL_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INTEREST_ACCRUAL_SUMMARY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INTEREST_SEARCH_CRITERIA_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MF_ACCRUAL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MF_ACCRUAL_SUMMARY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MF_REBATE_ACCRUAL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MF_REBATE_ACCRUAL_SUMMARY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MF_REBATE_SEARCH_CRITERIA_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MF_SEARCH_CRITERIA_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MGMT_CO_OPTIONS_CBO;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AccrualType;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId InclUnsettled;
   extern CLASS_IMPORT const BFDecimalFieldId IntAccrEffectiveDate;
   extern CLASS_IMPORT const BFDecimalFieldId IntAccrLastDivDate;
}

//CP20030319const int INTEREST_ACCRUAL_DETAILS_LIST = 1;
//CP20030319const int MF_ACCRUAL_LIST= 3;
//CP20030319const int MF_REBATE_ACCRUAL_LIST = 4;
//CP20030319const int FUNDS_LIST = 5;
//CP20030319const int FUND_MASTER_LIST = 6;
//CP20030319const int FUND_DETAIL_LIST = 7;
//CP20030319const int MFACCOUNT_CBO = 8;
//CP20030319const int MGMT_CO_OPTIONS_CBO = 9;
//CP20030319const int INTEREST_SEARCH_CRITERIA_CBO = 10;
//CP20030319const int MF_SEARCH_CRITERIA_CBO = 11;
//CP20030319const int MF_REBATE_SEARCH_CRITERIA_CBO = 12;
const BFFieldId TOTALS_FIELD1(13);
const BFFieldId TOTALS_FIELD2(14);
const BFFieldId TOTALS_FIELD3(15);
const BFFieldId TOTALS_FIELD4(16);
const BFFieldId TOTALS_FIELD5(17);
const BFFieldId TOTALS_FIELD6(18);
const BFFieldId TOTALS_FIELD7(19);
const BFFieldId DO_NOT_CONNECT(20);
//CP20030319const int INTEREST_ACCRUAL_SUMMARY_LIST = 21;
//CP20030319const int MF_ACCRUAL_SUMMARY_LIST= 22;
//CP20030319const int MF_REBATE_ACCRUAL_SUMMARY_LIST = 23;
const BFFieldId TOTALS_FIELD8(24);
const BFFieldId TOTALS_FIELD9(25);


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccrualsProcessIncludes.h-arc  $
//
//   Rev 1.9   Mar 21 2003 17:34:56   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.8   Nov 18 2002 10:55:36   PURDYECH
//BFObjectKey changes.
//
//   Rev 1.7   Oct 09 2002 23:53:00   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:51:34   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   22 May 2002 22:22:18   PURDYECH
//BFData Implementation
//
//   Rev 1.4   16 Apr 2002 14:46:12   HSUCHIN
//added TOTALS_FIELD8, TOTALS_FIELD9
//
//   Rev 1.3   19 Mar 2002 13:14:52   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   12 Mar 2002 10:26:38   HSUCHIN
//added support for summary containers
//
//   Rev 1.1   07 Mar 2002 16:31:22   HSUCHIN
//new field ids
//
//   Rev 1.0   21 Feb 2002 15:59:02   HSUCHIN
//Initial revision.
 */
