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
#include <ifastdataimpl\dse_dstc0060_vwrepeat_record.hpp>

//name of the params used at transfering the search criteria to the business process 

//name of the substitute list fields
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_ALLOCATIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_ALLOCATIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AllocationUsage;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFNumericFieldId TransCode;
   extern CLASS_IMPORT const BFNumericFieldId TransNum;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId PendingOrTransHist;
   extern CLASS_IMPORT const BFDecimalFieldId TransactionAmount;
   extern CLASS_IMPORT const BFTextFieldId LV_AccountAllocation;
   extern CLASS_IMPORT const BFTextFieldId LV_FundAllocation;
}

namespace TRANSACTION_ALLOCATIONSPROC
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const PENDING_OR_TRANS_HIST = I_( "PendingOrTransHist" );
   const I_CHAR * const TRANS_CODE = I_( "TransCode" );
   const I_CHAR * const TRANS_NUM = I_( "TransNum" );
   const I_CHAR * const TRADE_DATE = I_( "TradeDate" );
   const I_CHAR * const SETTLE_CURRENCY = I_( "SettleCurrency" );
   const I_CHAR * const SETTLE_CURRENCY_CODE = I_( "SettleCurrencyCode" );
   const I_CHAR * const TRANSACTION_AMOUNT = I_( "TransactionAmount" );
   const I_CHAR * const SETTLED = I_( "Settled" );
   const I_CHAR * const PENDING = I_( "Pending" );
   const I_CHAR * const TRANSHIST = I_( "TransHist" );
   const I_CHAR * const PENDING_LIST_CURKEY = I_( "Pending_List_CurKey" );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//


