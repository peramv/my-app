#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : AcctSplitCommProcessIncludes.h
// ^AUTHOR : 
// ^DATE   : 03/08/2001
//
//******************************************************************************

#include <ifastdataimpl\dse_dstc0175_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCT_SPLITCOMM_DATE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCT_SPLITCOMM_REP_LIST;
}
namespace ACCTSPLIT
{
//CP20030319   const int ACCT_SPLITCOMM_DATE_LIST  = 1;
//CP20030319   const int ACCT_SPLITCOMM_REP_LIST = 2;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const SHR_NUM;
   const BFFieldId NEWITEM(100);
   const BFFieldId TOTAL_RENUNCIATION(101);
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveShrNum;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId AcctSplitCommDateHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId AcctSplitCommRepHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId CommEntType;
   extern CLASS_IMPORT const BFDecimalFieldId CommAmount;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctSplitCommProcessIncludes.h-arc  $
//
//   Rev 1.7   Mar 21 2003 17:35:12   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:53:00   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:51:40   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   22 May 2002 18:21:54   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:14:54   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   25 Sep 2001 12:16:52   HSUCHIN
//added shareholder constant
//
//   Rev 1.1   29 Aug 2001 16:11:38   HSUCHIN
//added enhancements and validation
//
//   Rev 1.0   23 Aug 2001 14:51:40   HSUCHIN
//Initial revision.
 */
