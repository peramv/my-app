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

#include <dataimpl\dse_dstc0136_vw.hpp>
#include <dataimpl\dse_dstc0056_vw.hpp>
#include <dataimpl\dse_dstc0063_vw.hpp>
#include <dataimpl\dse_dstc0083_vw.hpp>
#include <dataimpl\dse_dstc0107_vw.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int FUND_TO_LIST        = 1;
//CP20030319const int FUNDMASTER_LIST     = 2;
//CP20030319const int FUNDDETAILS_LIST    = 3;
//CP20030319const int FUNDSPONSORS_LIST   = 4;
//CP20030319const int TRANSLATION_LIST    = 5;
//CP20030319const int FEEINFOINQUIRY_CBO   = 6;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FEEINFOINQUIRY_CBO;
   extern IFASTBP_LINKAGE const BFContainerId FUND_TO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDDETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDMASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDSPONSORS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSLATION_LIST;
}
namespace FUNDLISTLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDCODE;  
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSCODE; 
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundToListProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 21 2003 17:40:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:16   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:21:00   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:17:16   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Mar 21 2001 13:00:34   FENGYONG
//get fundtolist by fromfund,fromclass or sponsorcode
//
//   Rev 1.0   Dec 04 2000 13:11:34   VASILEAD
//Initial revision.
 * 
 *    Rev 1.3   Aug 22 2000 16:58:42   FENGYONG
 * Fix French Fundname
 * 
 *    Rev 1.2   Jul 05 2000 13:45:00   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.1   Mar 24 2000 12:22:50   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.1   Mar 06 2000 15:52:32   FENGYONG
// add fundCode & classcode
// 
//    Rev 1.0   Feb 25 2000 16:19:54   FENGYONG
// Initial revision.
// 
// Initial revision.
 * 
 *
 */
