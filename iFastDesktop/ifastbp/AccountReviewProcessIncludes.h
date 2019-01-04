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

#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0204_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int ACCOUNTREVIEW_LIST  = 1;
//CP20030319const int MFACCOUNT_CBO = 2;
//CP20030319const int COA_NAVIG_CBO = 3;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNTREVIEW_LIST;
   extern IFASTBP_LINKAGE const BFContainerId COA_NAVIG_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}
namespace ACCOUNTREVIEWLITERALS
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const NAME;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUMBER;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountReviewProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 17 2005 14:12:44   aguilaam
//IN_234826: display shrnum, acctnum, entity owner name on acctreview screen
//
//   Rev 1.4   Mar 21 2003 17:34:42   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:52:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   31 May 2002 13:46:36   HERNANDO
//Revised for Rel47.  Added #include "dse_dstc0149_vw.hpp"
//
//   Rev 1.1   22 May 2002 18:21:56   PURDYECH
//BFData Implementation
//
//   Rev 1.0   08 May 2002 18:10:56   HERNANDO
//Initial revision.
 * 
 */
