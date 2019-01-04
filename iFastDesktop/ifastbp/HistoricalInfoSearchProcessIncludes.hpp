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
//    Copyright 1997 by DST Systems, Inc.
//    AUTHOR : Serban Popescu
//    DATE   : Feb 2003
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
   extern IFASTBP_LINKAGE const BFContainerId HISTORICAL_INFO_SEARCH_CRITERIA;
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId FundName;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId SalesRepCode;
   extern CLASS_IMPORT const BFTextFieldId SalesRepName;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId HistoricalSearchInfo;
}

namespace
{
   //const I_CHAR * const BRANCH_NAME = I_( "BranchName" );
   //const I_CHAR * const SALESREP_NAME = I_( "SalesRepName" );
   //const I_CHAR * const FUND_NAME = I_( "FundName" );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalInfoSearchProcessIncludes.hpp-arc  $
//
//   Rev 1.3   Jun 30 2003 16:56:24   popescu
//added historical info search to the Broker Features search;
//moved some param names to the mfcaniterprocparam namespace
//
//   Rev 1.2   Mar 21 2003 17:41:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Feb 11 2003 14:41:08   popescu
//changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
//
//   Rev 1.0   Feb 06 2003 11:53:54   popescu
//Initial revision.
 * 
 */

