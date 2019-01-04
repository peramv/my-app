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

// Should include data set includes used by entity here


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0006_req.hpp>
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0007_req.hpp>
#include <ifastdataimpl\dse_dstc0007_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_req.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0049_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0121_req.hpp>
#include <ifastdataimpl\dse_dstc0121_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>



namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACQFEEINQUIRY_CBO;
   extern IFASTBP_LINKAGE const BFContainerId ADDRESS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AT_ACCOUNT_ALLOCATIONLIST;
   extern IFASTBP_LINKAGE const BFContainerId AT_FUND_ALLOCATIONLIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SAVINGPLAN_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SYSALLOCATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SYSTEMATIC_LIST;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ATAllocationListHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_AtAcctAllocationHeading;
   extern CLASS_IMPORT const BFTextFieldId MonthIndicator;
   extern CLASS_IMPORT const BFTextFieldId Name;
}

namespace SYSTEMATICLIT
{

   extern const I_CHAR * const ACCOUNT_NUM;
   extern const I_CHAR * const ENTITY_ID;
   extern const I_CHAR * const ENTITY_NAME;
   extern const I_CHAR * const TRANS_TYPE;
   extern const I_CHAR * const MULTI_ALLOCATION;


   const BFFieldId PRIMARY_ACCOUNT_OWNER(500);
   const BFFieldId LISTKEY(600);
   const BFFieldId TRANS_TYPE_PARAM(700);
   const BFFieldId FEE_DISABLE_FLAG(800);
   const BFFieldId FEE_UPDATE_FLAG(900);
   const BFFieldId DEFAULT_ACQFEE(1000);
   const BFFieldId TRANSACTION_TYPE(1001);
   const BFFieldId NEW_SYSTEMATIC(1002);
   const BFFieldId ORG_KEY(1100);
   const BFFieldId DEST_KEY(1200);
   const BFFieldId WHTaxApply(1201);
   const BFFieldId FileProcessorApply(1202);
   const BFFieldId IsFundLimitedByBankuptcy(1203);
   const BFFieldId IS_XREF_WARN_APPL(7025);
   const BFFieldId AreAllSytematicRecordsInactive (8000);
}


 const BFFieldId IsSWPCustomPayoutPlan(8001);
 const BFFieldId IsSWPPortfolioPayoutPlan(8002);

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SystematicProcessIncludes.h-arc  $
 * 
 *    Rev 1.22   Jan 11 2012 15:27:42   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer
 * 
 *    Rev 1.21   Jan 04 2005 11:13:16   yingbaol
 * PTS10036915:Add Field WHTaxApply and FileProcessorApply
 * 
 *    Rev 1.20   Mar 21 2003 17:48:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.19   Jan 29 2003 14:57:14   popescu
 * Added Historical button for Systematic
 * 
 *    Rev 1.18   Oct 09 2002 23:53:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.17   Aug 29 2002 12:53:48   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.16   Jul 17 2002 14:22:44   KOVACSRO
 * Added Name field.
 * 
 *    Rev 1.15   22 May 2002 18:19:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.14   19 Mar 2002 13:18:46   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.13   Aug 27 2001 09:47:12   YINGBAOL
 * fix paytype issue
 * 
 *    Rev 1.12   Aug 09 2001 10:27:16   YINGBAOL
 * add acount list
 * 
 *    Rev 1.11   19 Jun 2001 13:23:46   KOVACSRO
 * Added DBR::MonthIndicator
 * 
 *    Rev 1.10   25 May 2001 15:06:50   YINGZ
 * add SAVINGPLAN_MASTER_LIST
 * 
 *    Rev 1.9   Dec 06 2000 17:05:26   KOVACSRO
 * Added TRANS_TYPE.
 * 
 *    Rev 1.8   May 01 2000 09:41:40   YINGBAOL
 * automatic transfer added
 * 
 *    Rev 1.7   Apr 17 2000 17:15:34   YINGZ
 * add AddCopy function for systematic
 * 
 *    Rev 1.6   Apr 17 2000 11:23:46   YINGBAOL
 * fix M3 crash problem
 * 
 *    Rev 1.5   Apr 14 2000 12:04:22   YINGBAOL
 * add Automatic Transfer in systematic screen
 * 
 *    Rev 1.4   Apr 06 2000 10:15:50   YINGBAOL
 * add Atomatic Account Transfer Allocation List
 * 
 *    Rev 1.3   Apr 05 2000 14:17:12   HSUCHIN
 * more M2 sync up
 * 
 *    Rev 1.2   Apr 04 2000 10:46:16   YINGBAOL
 * M2 Sync.
 * 
 *    Rev 1.1   Feb 15 2000 18:56:50   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.15   Feb 09 2000 12:13:52   HUANGSHA
 * check in for release
 * 
 *    Rev 1.14   Jan 06 2000 14:57:18   HUANGSHA
 * COA changed
 * 
 *    Rev 1.13   Dec 24 1999 12:11:08   HUANGSHA
 * check in
 * 
 *    Rev 1.12   Dec 23 1999 12:16:54   HUANGSHA
 * check in for Allocation testing
 * 
 *    Rev 1.11   Dec 16 1999 18:30:12   HUANGSHA
 * Check in for testing
 * 
 *    Rev 1.10   Dec 14 1999 15:35:14   HUANGSHA
 * check in for compiling
 * 
 *    Rev 1.9   Dec 02 1999 17:57:04   POPESCUS
 * Fixed crashes in search
 * 
 *    Rev 1.8   Dec 01 1999 12:57:58   HUANGSHA
 * check in for 2nd release
 * 
 *    Rev 1.7   Nov 25 1999 15:19:36   HUANGSHA
 * check in for the initial m2 release
 * 
 *    Rev 1.6   Nov 25 1999 10:26:28   HUANGSHA
 * check in for test
 * 
 *    Rev 1.5   Nov 24 1999 09:36:36   HUANGSHA
 * check in for test
 * 
 *    Rev 1.4   Nov 15 1999 14:43:34   HUANGSHA
 * temporary check in
 * 
 *    Rev 1.3   Oct 17 1999 12:12:16   POPESCUS
 * namespaces fixes
 * 
 *    Rev 1.2   Oct 17 1999 11:30:18   POPESCUS
 * added namespace for search
 * 
 *    Rev 1.1   Jul 08 1999 10:04:00   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
