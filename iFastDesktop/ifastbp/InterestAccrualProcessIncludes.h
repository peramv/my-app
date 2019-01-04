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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.
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

//names of the fields used by the process
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INTEREST_ACCRUAL_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INTEREST_ACCRUAL_TOTALS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MGMT_CO_OPTIONS_CBO;
}
namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId IntAccrEffectiveDate;
   extern CLASS_IMPORT const BFDecimalFieldId IntAccrLastDivDate;
}

//name of the params used at transfering the search criteria to the business process 

// Temporarily, defining fields to use

/*const int REC_TYPE_ = 1;
const int RX_FUND_ = 2;
const int RX_CLASS_ = 3;
const int ASOF_DATE_ = 4;
const int ELIG_UNITS_ = 5;
const int INT_RATE_ = 6;
const int INT_VALUE_ = 7;
const int INT_PAID_ = 8;
const int ACCUM_TOTAL_ = 9;
const int FUND_CODE_ = 10;
const int CLASS_CODE_ = 11;
const int MASTER_FUND_CODE_ = 12;
const int FUND_TYPE_ = 13;
const int DETAIL_FUND_CODE_ = 14;
const int DETAIL_CLASS_CODE_ = 15;
const int LAST_DIV_DATE_ = 16;
const int ACCOUNT_NUM_ = 17;*/

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int INTEREST_ACCRUAL_DETAILS_LIST = 1;
//CP20030319const int INTEREST_ACCRUAL_TOTALS_LIST = 2;
//CP20030319const int FUNDS_LIST = 3;
//CP20030319const int FUND_MASTER_LIST = 4;
//CP20030319const int FUND_DETAIL_LIST = 5;
//CP20030319const int MFACCOUNT_CBO = 6;
//CP20030319const int MGMT_CO_OPTIONS_CBO = 7;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InterestAccrualProcessIncludes.h-arc  $
 * 
 *    Rev 1.5   Mar 21 2003 17:42:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:20:44   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:17:36   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Feb 15 2000 18:56:34   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.5   Jan 13 2000 14:26:42   PRAGERYA
 * Data group problem fixed
 * 
 *    Rev 1.4   Oct 28 1999 12:58:46   PRAGERYA
 * Process-level fields added
 * 
 *    Rev 1.3   Aug 23 1999 17:51:56   PRAGERYA
 * Date ranges
 * 
 *    Rev 1.2   Aug 04 1999 09:37:44   PRAGERYA
 * Bug fixes
 * 
 *    Rev 1.1   Jul 08 1999 10:03:48   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
