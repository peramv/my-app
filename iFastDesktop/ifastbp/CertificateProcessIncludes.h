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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by entity here

// Temporarily, defining fields to use

#include <ifastdataimpl\dse_dstc0018_vw.hpp>
#include <ifastdataimpl\dse_dstc0018_req.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CERTIFICATE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
}
namespace CERTLIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const INACCTNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const INFUND;
   extern IFASTBP_LINKAGE const I_CHAR * const INCERTNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const INXREFNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const IGNOREDNF;
   extern IFASTBP_LINKAGE const I_CHAR * const IGNORENOTENINFO;
//CP20030319   const int FUND_DETAIL_LIST = 2;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Address;
}
// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int CERTIFICATE_LIST = 1;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CertificateProcessIncludes.h-arc  $
 * 
 *    Rev 1.7   Mar 21 2003 17:37:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   22 May 2002 18:21:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:15:22   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Jun 06 2000 08:39:46   BUZILA
 * finished M3 syncup
 * 
 *    Rev 1.2   Mar 13 2000 17:28:38   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.1   Feb 15 2000 18:56:18   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Dec 05 1999 18:58:40   VASILEAD
 * Friday night changes( don't be so hard on us )
 * 
 *    Rev 1.2   Jul 14 1999 17:06:28   POPESCUS
 * Added a new param
 * 
 *    Rev 1.1   Jul 08 1999 10:03:32   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

