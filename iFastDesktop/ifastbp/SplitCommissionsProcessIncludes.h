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

#include <ifastdataimpl\dse_dstc0151_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//calculated fields
const BFFieldId SPLIT_RATE_TOTAL(100);
const BFFieldId SPLIT_PERCENT_TOTAL(101);
const BFFieldId SPLIT_AMOUNT_TOTAL(102);
const BFFieldId RENUNCIATION_AMOUNT(103);
const BFFieldId TOTAL_PERCENT(104);
const BFFieldId TOTAL_AMOUNT(105);
const BFFieldId FEE_TYPE (106);

//dlg, control groups
const UINT FUND_ALLOCATION_GROUP = 200;
const UINT SPLIT_COMMISSION_GROUP = 201;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SPLIT_COMMISSION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_ALLOCATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSACTION_HISTORY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MATCH_TRANSFER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SYS_ALLOCATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SYS_ATALLOCATION_LIST;
}

namespace SPLITCOMM
{
   //parameters
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const CALLER;
   extern IFASTBP_LINKAGE const I_CHAR * const MAIN_LIST_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const ALLOCATION_LIST_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const SPLIT_COMM_LIST_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSACTION_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSACTION_TYPE_DESC;
   extern IFASTBP_LINKAGE const I_CHAR * const MATCH_TRANSACTION_ID;

   //possible callers
   extern IFASTBP_LINKAGE const I_CHAR * const MATCH_TRANSFER;
   //extern IFASTBP_LINKAGE const I_CHAR * const SYSTEMATIC;
   extern IFASTBP_LINKAGE const I_CHAR * const SYSTEMATIC_ALLOCATION;
   extern IFASTBP_LINKAGE const I_CHAR * const SYSTEMATIC_ATALLOCATION;
   extern IFASTBP_LINKAGE const I_CHAR * const TRADE;
   extern IFASTBP_LINKAGE const I_CHAR * const TRADE_ALLOCATION;   
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSACTION_HISTORY;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSACTION_PENDING;   
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSACTION_PENDING_ALLOCATION;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSACTION_HISTORY_ALLOCATION;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SplitCommissionsProcessIncludes.h-arc  $
//
//   Rev 1.21   Mar 04 2011 12:05:22   jankovii
//PET181943 FN01 - XMLPhase 2
//
//   Rev 1.20   Nov 27 2004 21:21:14   popescu
//PET 1117/06, trades processing
//
//   Rev 1.19   May 14 2003 11:15:50   popescu
//added extra param to the process layer, which is used to pass the key string of the current selected item in the allocations list, in order to set selection on it in split commission dialog
//
//   Rev 1.18   May 13 2003 10:05:06   popescu
//Split commission re-work
//
//   Rev 1.17   Mar 21 2003 17:48:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.16   Oct 09 2002 23:53:38   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.15   Aug 29 2002 12:53:42   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.14   22 May 2002 18:19:42   PURDYECH
//BFData Implementation
//
//   Rev 1.13   19 Mar 2002 13:18:34   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.12   Aug 16 2001 13:25:18   ZHANGCEL
//Added content for MatchTransfer
//
//   Rev 1.11   May 03 2001 15:46:08   HERNANDO
//Added Parameters.
//
//   Rev 1.10   03 Apr 2001 20:23:56   HSUCHIN
//added a couple of key to store trade list info
//
//   Rev 1.9   01 Apr 2001 09:50:34   HSUCHIN
//added ATSysAllocation hook up (doesn't work yet)
//
//   Rev 1.8   Mar 22 2001 18:30:34   HERNANDO
//Revised parameters.
//
//   Rev 1.7   Mar 22 2001 14:13:42   HSUCHIN
//added transaction allocations hook up
//
//   Rev 1.6   Mar 21 2001 13:30:12   HSUCHIN
//more improvements and bug fix
//
//   Rev 1.5   Mar 18 2001 17:51:44   HSUCHIN
//check in for winnie
//
//   Rev 1.4   Mar 18 2001 11:52:02   HSUCHIN
//additioanl features and support
//
//   Rev 1.3   Mar 13 2001 09:15:40   HSUCHIN
//Check in for Zijian
//
//   Rev 1.2   Mar 09 2001 13:11:20   HSUCHIN
//bug fix and check in for inquiry test
//
//   Rev 1.1   Mar 08 2001 15:25:58   HSUCHIN
//check in for Ulli
 *
 */
