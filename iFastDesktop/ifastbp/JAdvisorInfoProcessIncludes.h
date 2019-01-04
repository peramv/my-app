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
#include <ifastdataimpl\dse_dstc0092_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0090_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0091_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int ADVISORINFO_LIST = 1;
//CP20030319const int BROKER_LIST = 2;
//CP20030319const int BRANCH_LIST = 3;
//CP20030319const int MGMTCOOPTIONS_LIST = 4;
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ADVISORINFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId BRANCH_LIST;
   extern IFASTBP_LINKAGE const BFContainerId BROKER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MGMTCOOPTIONS_LIST;
}
namespace ADVISORINFOLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const BROKERCODE;  
   extern IFASTBP_LINKAGE const I_CHAR * const BRANCHCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SLSREP;
   extern IFASTBP_LINKAGE const I_CHAR * const ALLRESULT; 
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAdvisorInfoProcessIncludes.h-arc  $
 * 
 *    Rev 1.7   Mar 21 2003 17:43:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   22 May 2002 18:20:38   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:17:42   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Nov 17 2000 14:39:54   FENGYONG
 * Add allresult
 * 
 *    Rev 1.2   Mar 30 2000 15:45:08   FENGYONG
 * Add CurrentDate
 * 
 *    Rev 1.1   Mar 24 2000 12:22:46   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.1   Feb 29 2000 15:28:48   FENGYONG
// Add Fileds
// 
//    Rev 1.0   Feb 25 2000 16:19:26   FENGYONG
// Initial revision.
// 
//    Rev 1.0   Feb 18 2000 09:27:48   FENGYONG
// Initial revision.
 * 
 *
 */

