#pragma once
//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeInfoProcessIncludes.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/14/2000
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0170_req.hpp>         // Guarantee Summary List
#include <ifastdataimpl\dse_dstc0170_vw.hpp>
#include <ifastdataimpl\dse_dstc0106_req.hpp>         // Guarantee Info List (details fro summary)
#include <ifastdataimpl\dse_dstc0106_vw.hpp>
#include <ifastdataimpl\dse_dstc0351_req.hpp>         // Guarantee Detail Lits
#include <ifastdataimpl\dse_dstc0351_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CONTRACTINFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId GUARANTEE_SUMMARY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId GUARANTEEINFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId GUARANTEE_DETAIL_LIST;
}
namespace GUARANTEE
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLD_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const KEY_PARAM;   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/GuaranteeInfoProcessIncludes.h-arc  $
 * 
 *    Rev 1.12   Aug 17 2005 16:54:12   porteanm
 * Incident 351033 - Details support.
 * 
 *    Rev 1.11   Mar 21 2003 17:40:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:53:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   22 May 2002 18:20:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   19 Mar 2002 13:17:20   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.7   Aug 21 2001 16:50:46   OLTEANCR
 * added   GUAR_ACCT_TOTAL;
 * 
 *    Rev 1.6   Jul 29 2001 12:34:04   OLTEANCR
 * added GUARANTEE_SUMMARY container
 * 
 *    Rev 1.5   Jul 17 2001 09:42:22   OLTEANCR
 * added CONTRACTINFO_LIST container
 * 
 *    Rev 1.4   May 14 2001 10:56:20   OLTEANCR
 * unchanged
 * 
 *    Rev 1.3   Mar 15 2000 10:05:26   ZHANGCEL
 * Bugs fixed
 * 
 *    Rev 1.2   Mar 10 2000 12:58:30   ZHANGCEL
 * Updated
// 
//    Rev 1.1   Feb 22 2000 17:49:20   ZHANGCEL
// Chech in for release
 * 
 *
 */

