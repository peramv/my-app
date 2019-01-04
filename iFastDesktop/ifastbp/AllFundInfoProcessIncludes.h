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

#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0121_vw.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int FUNDMASTER_LIST     = 1;
//CP20030319const int FUNDDETAILS_LIST    = 2;
//CP20030319const int FUNDSPONSORS_LIST   = 3;
//CP20030319const int MGMTCOOPTIONS_LIST  = 4;
//CP20030319const int TRANSLATION_LIST    = 5;
//CP20030319const int ACQFEEINQUIRY_CBO   = 6;
//CP20030319const int FEEINFOINQUIRY_CBO   = 7;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACQFEEINQUIRY_CBO;
   extern IFASTBP_LINKAGE const BFContainerId FEEINFOINQUIRY_CBO;
   extern IFASTBP_LINKAGE const BFContainerId FUNDDETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDMASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDSPONSORS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MGMTCOOPTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSLATION_LIST;
}
namespace ALLFUNDINFOLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_CODE; 
   extern IFASTBP_LINKAGE const I_CHAR * const CLASS_CODE;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllFundInfoProcessIncludes.h-arc  $
//
//   Rev 1.6   Mar 21 2003 17:35:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:53:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   22 May 2002 18:21:54   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:15:04   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   May 08 2001 10:30:52   FENGYONG
//Add FEEINFOCBO
//
//   Rev 1.1   Nov 27 2000 11:37:12   VASILEAD
//Added AllFundInfo support to provide with fund information for the global object in ECOMM
//
//   Rev 1.0   Nov 20 2000 17:54:10   VASILEAD
//Initial revision.
 * 
 *    Rev 1.4   Aug 22 2000 16:58:42   FENGYONG
 */

