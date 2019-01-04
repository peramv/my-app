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
#include <ifastdataimpl\dse_dstc0005_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0049_vw.hpp>
#include <ifastdataimpl\dse_dstc0064_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
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
//CP20030319const int REMARKS_LIST  = 1;
//CP20030319const int MFACCOUNT_CBO = 2;
//CP20030319const int COA_NAVIG_CBO = 3;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId COA_NAVIG_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId REMARKS_LIST;
}
namespace REMARKSLIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const NAME;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RemarksProcessIncludes.h-arc  $
 * 
 *    Rev 1.6   Mar 21 2003 17:46:32   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:53:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:20:12   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:10   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Oct 18 2000 11:31:44   ZHANGCEL
 * Added incluse file view64
 * 
 *    Rev 1.1   Feb 15 2000 18:56:42   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   08 Jan 2000 14:54:52   HSUCHIN
 * modified so that effective date now defaults to next business date when new remarks is added.
 * 
 *    Rev 1.5   12 Dec 1999 12:39:44   HSUCHIN
 * added NAME to the REMARKSLIT namespace
 * 
 *    Rev 1.4   Dec 10 1999 18:46:32   BUZILA
 * setting remarks flag in COANavig CBO
 * 
 *    Rev 1.3   Oct 29 1999 10:18:08   HSUCHIN
 * added ListviewHeading set
 * 
 *    Rev 1.2   Oct 24 1999 11:11:08   POPESCUS
 * Added namespace for the string param
 * 
 *    Rev 1.1   Jul 08 1999 10:03:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
