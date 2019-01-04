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
// ^FILE   : YTDContributionProcessIncludes.h
// ^AUTHOR : 
// ^DATE   : 03/08/2001
//
//******************************************************************************

#include <ifastdataimpl\dse_dstc0173_vw.hpp>
#include <ifastdataimpl\dse_dstc0174_vw.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>


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
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId RSP_CONTRIBUTION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RSP_RECEIPTS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_MAILING_LIST;


}
namespace YTD
{
//CP20030319   const int RSP_CONTRIBUTION_LIST  = 1;
//CP20030319   const int RSP_RECEIPTS_LIST  = 2; 
//CP20030319   const int ACCOUNT  = 3;

   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const SHR_NUM;

}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId PlanType;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/YTDContributionProcessIncludes.h-arc  $
//
//   Rev 1.7   Dec 02 2004 11:38:00   yingbaol
//PET1137,FN01: Add Epost functionality
//
//   Rev 1.6   Mar 21 2003 17:50:24   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:53:44   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   22 May 2002 18:18:10   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:20:16   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   Nov 20 2001 16:22:42   ZHANGCEL
//Many changes for getting Address from  view174
//
//   Rev 1.1   18 Aug 2001 09:28:34   HSUCHIN
//implemented moreAvailiable and other enhancements
//
//   Rev 1.0   05 Aug 2001 15:31:42   HSUCHIN
//Initial revision.
 */
