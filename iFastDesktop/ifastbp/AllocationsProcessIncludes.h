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
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0006_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0007_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0058_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0069_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0060_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0067_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0068_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0115_req.hpp>
#include <ifastdataimpl\dse_dstc0115_reqrepeat_record.hpp>

#include <bfproc\bfcontainerid.hpp>

//#include "DSTC0056_VWRepeat_Record.hpp"

//#include "DSTC0004_VWRepeat_Record.hpp"

//name of the params used at transfering the search criteria to the business process 

// Temporarily, defining fields to use

/*const int RX_FUND_ = 1;
const int RX_CLASS_ = 2;
const int SETTLED_UNITS_ = 3;
const int SETTLED_VALUE_ = 4;
const int UNSETTLED_UNITS_ = 5;
const int UNSETTLED_VALUE_ = 6;
const int FUND_NAV_ = 7;
const int FUND_CODE_ = 8;
const int CLASS_CODE_ = 9;
const int CURRENCY_ = 10;
const int ACCOUNT_NUM_ = 11;*/

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCT_ALLOCATIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AT_ACCT_TRANS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AT_ACCT_TRANS_LIST_AS_CBO;
   extern IFASTBP_LINKAGE const BFContainerId AT_FUND_TRANS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AT_SYSTEMATIC_CBO;
   extern IFASTBP_LINKAGE const BFContainerId FUND_ALLOCATIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_LIF_LRIF_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_LIF_LRIF_INFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SHR_ALLOCATIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SYSTEMATIC_ALLOCATIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SYSTEMATIC_ALLOCATIONS_LIST_AS_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SYSTEMATIC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRADE_ACCOUNT_ALLOCATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRADE_FUND_ALLOCATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRADES_LIST;
}
namespace ifds
{
   // Type of allocations in the calling dialog
   extern CLASS_IMPORT const BFTextFieldId AllocationType;

   //names of the substitute list fields
   extern CLASS_IMPORT const BFTextFieldId AllocationUsage;

   //names of the fields used by the process
   extern CLASS_IMPORT const BFTextFieldId AllocTaxType;
   extern CLASS_IMPORT const BFDecimalFieldId AcctTotalPercent;
   extern CLASS_IMPORT const BFDecimalFieldId FundTotalPercent;
   extern CLASS_IMPORT const BFTextFieldId LV_DefaultAllocShrHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_DefaultAllocAcctHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_DefaultAllocFundHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_OneTimeAllocSystematicHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_OneTimeAllocFundHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_OneTimeRRIFAllocHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_OneTimeRRIFFundHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_OneTimeTradeAllocHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId LV_OneTimeTradeHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId LV_TradeAllocAcctHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId AutoTransferAllocHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId ReplaceAsDefault;
   extern CLASS_IMPORT const BFTextFieldId LV_OneTimeRRIFAllocHeading;
   extern CLASS_IMPORT const BFTextFieldId XSFundsValidate;

   //names used for Systematic Allocations
   extern CLASS_IMPORT const BFTextFieldId SystematicKey;

   //names used for Transaction Allocations
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFNumericFieldId TransCode;
   extern CLASS_IMPORT const BFNumericFieldId TransNum;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId PendingOrTransHist;
   extern CLASS_IMPORT const BFDecimalFieldId TransactionAmount;
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFDecimalFieldId TotAmount;
   extern CLASS_IMPORT const BFTextFieldId IsAllocationChanged;
}

namespace ALLOCATIONSPROC
{
   // Trace literals
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   // Allocation type
   const I_CHAR * const ALLOCATION_TYPE = I_( "Allocation Type" );
   // Types of allocations
   const I_CHAR * const SHAREHOLDER_DEFAULT  = I_( "Shareholder Default" );
   const I_CHAR * const SYSTEMATIC_ONE_TIME  = I_( "Systematic One-Time" );
   const I_CHAR * const TRANSACTION_ONE_TIME = I_( "Transaction One-Time" );
   const I_CHAR * const TRADE_ONE_TIME       = I_( "Trade One-Time" );
   const I_CHAR * const SYSTEMATIC_AUTO_TRANSFER = I_( "Systematic Automatic-Transfer" );
   const I_CHAR * const RRIF_LIF_LRIF_ONE_TIME = I_( "RRIF_LIF_LRIF One-Time" );

   // For systematic allocations
   const I_CHAR * const SYSTEMATIC_KEY = I_( "SystematicKey" );

   // The KEY for the selected item when lauched from the parent screen
   const I_CHAR * const SELECTION_KEY = I_( "SelectionKey" );


   // For transaction allocations
   const I_CHAR * const PENDING_OR_TRANS_HIST = I_( "PendingOrTransHist" );
   const I_CHAR * const TRANS_CODE = I_( "TransCode" );
   const I_CHAR * const TRANS_NUM = I_( "TransNum" );
   const I_CHAR * const TRADE_DATE = I_( "TradeDate" );
   const I_CHAR * const SETTLE_CURRENCY = I_( "SettleCurrency" );
   const I_CHAR * const TRANSACTION_AMOUNT = I_( "TransactionAmount" );
   const I_CHAR * const PENDING = I_( "Pending" );
   const I_CHAR * const TRANS_HIST = I_( "TransHist" );
   const I_CHAR * const TRANS_TYPE = I_( "TransType" );


   // Need to define list and search ID's to be used by a GUI object talking to the
   // process.
//CP20030319   const int MFACCOUNT_CBO = 1;
//CP20030319   const int SHAREHOLDER_CBO = 2;
//CP20030319   const int SHR_ALLOCATIONS_LIST = 3;
//CP20030319   const int ACCT_ALLOCATIONS_LIST = 4;//default
//CP20030319   const int FUND_ALLOCATIONS_LIST = 5;//default
//CP20030319   const int SYSTEMATIC_LIST = 6;
//CP20030319   const int SYSTEMATIC_ALLOCATIONS_LIST = 7;
//CP20030319   const int SYSTEMATIC_ALLOCATIONS_LIST_AS_CBO = 8;
   //const int FUND_DETAIL_LIST = 9;
//CP20030319   const int MFACCOUNT_LIST = 10;
   //const int TRANSACTION_ALLOCATIONS_LIST = 11;
   //const int GROUP_FUND_LIST = 12;
   //const int FUND_DETAIL_LIST = 13;
//CP20030319   const int RRIF_LIF_LRIF_INFO_LIST = 14;
//CP20030319   const int RRIF_LIF_LRIF_ALLOC_LIST = 15;

//CP20030319   const int TRADES_LIST = 16;
//CP20030319   const int TRADE_FUND_ALLOCATION_LIST = 17;

//CP20030319   const int AT_SYSTEMATIC_CBO = 18;
//CP20030319   const int AT_ACCT_TRANS_LIST  = 19;
//CP20030319   const int AT_FUND_TRANS_LIST  = 20;
//CP20030319   const int AT_ACCT_TRANS_LIST_AS_CBO = 21;

//CP20030319   const int TRADE_ACCOUNT_ALLOCATION_LIST = 22;


}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllocationsProcessIncludes.h-arc  $
 * 
 *    Rev 1.21   Apr 16 2012 23:17:26   popescu
 * 2901148 - Gurantee Flag Override
 * 
 *    Rev 1.20   Jun 09 2003 14:52:16   YINGBAOL
 * remove RRIF allocation for allocation screen
 * 
 *    Rev 1.19   Mar 21 2003 17:35:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.18   Jan 12 2003 18:32:26   KOVACSRO
 * Added XSFundsValidate field
 * 
 *    Rev 1.17   Oct 09 2002 23:53:02   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.16   Jul 16 2002 16:33:48   KOVACSRO
 * Added  LV_OneTimeRRIFAllocHeading.
 * 
 *    Rev 1.15   22 May 2002 22:22:20   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.14   29 Apr 2002 15:56:10   KOVACSRO
 * Added TotAmount field
 * 
 *    Rev 1.13   22 Apr 2002 09:59:02   KOVACSRO
 * Rel.47 : new design for Allocations.
 * 
 *    Rev 1.12   19 Mar 2002 13:15:06   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 *
 *    Rev 1.11   12 Jun 2001 15:48:12   KOVACSRO
 * Added TRADE_ALLOC_AMOUNT field.
 * 
 *    Rev 1.10   13 Mar 2001 13:13:34   KOVACSRO
 * Added TotPercentage.
 * 
 *    Rev 1.9   10 Mar 2001 17:09:54   KOVACSRO
 * Added LV_TradeAllocAccHeadingSet.
 * 
 *    Rev 1.8   01 Mar 2001 16:48:32   KOVACSRO
 * Changed name into TRADE_FUND_ALLOCATION_LIST and added TRADE_ACCOUNT_ALLOCATION_LIST
 * 
 *    Rev 1.7   Sep 01 2000 14:44:04   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.6   May 17 2000 15:01:28   YINGBAOL
 * remove some duplicated constant
 * 
 *    Rev 1.5   May 01 2000 09:40:50   YINGBAOL
 * add validation and other logic
 * 
 *    Rev 1.4   Apr 10 2000 12:31:40   HUANGSHA
 * Added TradeAllocations processing routines
 * 
 *    Rev 1.3   Mar 24 2000 10:07:48   YINGBAOL
 * change
 * 
 *    Rev 1.2   Mar 20 2000 16:45:40   HSUCHIN
 * check in for Yingbao
 * 
 *    Rev 1.1   Feb 15 2000 18:56:14   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.18   Feb 01 2000 13:02:46   PRAGERYA
// For Winnie
// 
//    Rev 1.17   Jan 26 2000 19:49:22   PRAGERYA
// For release
// 
//    Rev 1.16   Jan 24 2000 18:11:28   PRAGERYA
// Fixes
// 
//    Rev 1.15   Dec 22 1999 11:22:24   PRAGERYA
// For Jerry
// 
//    Rev 1.14   Dec 09 1999 10:52:20   PRAGERYA
// Another check-in for Jerry
// 
//    Rev 1.13   Dec 07 1999 11:43:40   PRAGERYA
// Check in for Jerry
// 
//    Rev 1.12   Dec 01 1999 14:37:32   PRAGERYA
// Check-in for release
// 
//    Rev 1.11   Nov 25 1999 15:36:52   PRAGERYA
// Shameful check-in for Release; very little things are functional
// 
//    Rev 1.10   Nov 18 1999 16:55:42   PRAGERYA
// This is the version developed on the premises that (1) Total amount is updatable, and (2) Pending transaction allocations are updatable. 
// According to Mike Metzger's clarifications, both of these assumtions are wrong. Pending transactions are not updatable just like Transaction History ones. Total Amount is also not updatable. If it is zero, the Fund Amount edit box should be disabled, and the value in it set to zero.
// 
//    Rev 1.9   Nov 18 1999 13:48:14   PRAGERYA
// Coding for Allocations, incr2
// 
//    Rev 1.8   Nov 15 1999 15:57:24   PRAGERYA
// Incr2 partial functionality
// 
//    Rev 1.7   Nov 12 1999 10:43:20   PRAGERYA
// Changes for Incr2
// 
//    Rev 1.6   Oct 28 1999 15:35:34   PRAGERYA
// Compliance with C1
// 
//    Rev 1.5   Oct 17 1999 11:24:18   POPESCUS
// added a namespace for search purposes
// 
//    Rev 1.4   Sep 27 1999 10:46:52   PRAGERYA
// Allocations checked in for release; transaction allocations not debugged yet
// 
//    Rev 1.3   Sep 24 1999 20:17:32   PRAGERYA
// Default allocations started
// 
//    Rev 1.2   Sep 20 1999 14:53:32   PRAGERYA
// From now on, we show only allocations for the current account
// 
//    Rev 1.1   Sep 20 1999 10:53:52   PRAGERYA
// This is the implementation made on the premise that we need to show allocations for ALL accounts pertaining to the current shareholder. All the further revisions are made on the premise that we need to show only allocations pertaining to the currently active account.
// 
//    Rev 1.0   Sep 19 1999 13:40:08   PRAGERYA
// Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
