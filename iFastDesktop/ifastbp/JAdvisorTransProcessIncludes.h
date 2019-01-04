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
#include <ifastdataimpl\dse_dstc0093_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0136_vwrepeat_record.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int ADVISORTRANS_LIST = 1;
//CP20030319const int MGMTCOOPTIONS_LIST = 2;
//CP20030319const int TRANSLATION_LIST = 3;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ADVISORTRANS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MGMTCOOPTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSLATION_LIST;
}
namespace ADVISORTRANSLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const BROKERCODE;  
   extern IFASTBP_LINKAGE const I_CHAR * const BRANCHCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SLSREP;
   extern IFASTBP_LINKAGE const I_CHAR * const FROMDATE;
   extern IFASTBP_LINKAGE const I_CHAR * const TODATE;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAdvisorTransProcessIncludes.h-arc  $
 * 
 *    Rev 1.7   Mar 21 2003 17:43:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   22 May 2002 18:20:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:17:44   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Aug 22 2000 16:58:40   FENGYONG
 * Fix French Fundname
 * 
 *    Rev 1.2   Jul 05 2000 13:45:02   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.1   Mar 24 2000 12:22:48   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.1   Feb 29 2000 15:29:14   FENGYONG
// Add currentDate
// 
// Initial revision.
 * 
 *
 */

