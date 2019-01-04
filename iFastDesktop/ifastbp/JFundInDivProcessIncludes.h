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
#include <ifastdataimpl\dse_dstc0104_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0136_vwrepeat_record.hpp>
// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int FUNDINDIV_LIST = 1;
//CP20030319const int FUNDSRCH_LIST = 2;
//CP20030319const int TRANSLATION_LIST = 3;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUNDINDIV_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDSRCH_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSLATION_LIST;
}
namespace FUNDINDIVLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDCODE;  
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSCODE; 
   extern IFASTBP_LINKAGE const I_CHAR * const FROMDATE;  
   extern IFASTBP_LINKAGE const I_CHAR * const TODATE;  
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JFundInDivProcessIncludes.h-arc  $
 * 
 *    Rev 1.8   Mar 21 2003 17:43:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   22 May 2002 18:20:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:17:48   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Aug 22 2000 16:58:40   FENGYONG
 * Fix French Fundname
 * 
 *    Rev 1.3   Jul 05 2000 13:44:54   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.2   Mar 30 2000 15:43:58   FENGYONG
 * Add FundCode and ClassCode
 * 
 *    Rev 1.1   Mar 24 2000 12:22:50   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:19:50   FENGYONG
// Initial revision.
// 
// Initial revision.
 * 
 *
 */

