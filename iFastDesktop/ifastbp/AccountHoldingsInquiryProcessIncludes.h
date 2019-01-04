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

#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>


// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int MFACCOUNT_HOLDING_LIST = 1;
//CP20030319const int MFACCOUNT_CBO = 2;
//CP20030319const int ACCOUNT_HOLDINGS_BY_CURRENCY_LIST = 3;
//CP20030319const int FUND_CLASS_HOLDINGS_LIST = 4;
//CP20030319const int ACCOUNT_DISTRIBUTION_LIST = 5;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_DISTRIBUTION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_HOLDINGS_BY_CURRENCY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_CLASS_HOLDINGS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_HOLDING_LIST;
}
namespace ACCTHOLDINGSLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountHoldingsInquiryProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 21 2003 17:34:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:52:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:22:04   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:14:48   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Oct 30 2001 11:48:00   VASILEAD
//Added distribution information
//
//   Rev 1.0   Mar 05 2001 13:28:40   VASILEAD
//Initial revision.
 * 
//    Rev 1.0   Nov 22 1999 11:23:02   FENGYONG
// Initial revision.
 *
 */

