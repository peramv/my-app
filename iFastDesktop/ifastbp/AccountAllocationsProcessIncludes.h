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
#include <ifastdataimpl\dse_dstc0058_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0069_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCT_ALLOCATIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_ALLOCATIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SHR_ALLOCATIONS_LIST;
}
namespace ifds
{
   //names of the fields used by the process
   extern CLASS_IMPORT const BFTextFieldId AllocTaxType;
   extern CLASS_IMPORT const BFDecimalFieldId AcctTotalPercent;
   extern CLASS_IMPORT const BFDecimalFieldId FundTotalPercent;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId rxTransType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace ACCOUNTALLOCATIONSPROC
{
   // Trace literals
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const TRANSTYPE = I_( "TransType" );
   const I_CHAR * const EFFECTIVEDATE = I_( "EffectiveDate" );
   // Types of allocations
   const I_CHAR * const SHAREHOLDER_DEFAULT  = I_( "Shareholder Default" );

   // The KEY for the selected item when lauched from the parent screen
   const I_CHAR * const SELECTION_KEY = I_( "SelectionKey" );


   // Need to define list and search ID's to be used by a GUI object talking to the
   // process.
//CP20030319   const int MFACCOUNT_CBO = 1;
//CP20030319   const int SHAREHOLDER_CBO = 2;
//CP20030319   const int SHR_ALLOCATIONS_LIST = 3;
//CP20030319   const int ACCT_ALLOCATIONS_LIST = 4;
//CP20030319   const int FUND_ALLOCATIONS_LIST = 5;
//CP20030319   const int MFACCOUNT_LIST = 6;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountAllocationsProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 21 2003 17:34:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:52:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:22:08   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:14:44   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Jan 17 2002 14:58:02   FENGYONG
//change name for api
//
//   Rev 1.0   Dec 20 2001 18:19:54   FENGYONG
//Initial revision.
 */
