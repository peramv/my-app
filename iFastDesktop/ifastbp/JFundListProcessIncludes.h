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
#include <ifastdataimpl\dse_dstc0023_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0136_vwrepeat_record.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int FUND_LIST = 1;
//CP20030319const int FUNDSRCH_LIST = 2;
//CP20030319const int TRANSLATION_LIST = 3;
//CP20030319const int MGMTCOOPTIONS_LIST = 4;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUND_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDSRCH_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MGMTCOOPTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSLATION_LIST;
}
namespace FUNDLISTLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDCODE;  
   extern IFASTBP_LINKAGE const I_CHAR * const CLASSCODE; 
   extern IFASTBP_LINKAGE const I_CHAR * const FROMDATE;  
   extern IFASTBP_LINKAGE const I_CHAR * const TODATE;  
   extern IFASTBP_LINKAGE const I_CHAR * const PREVDATEPRESSED;
   extern IFASTBP_LINKAGE const I_CHAR * const NEXTDATEPRESSED;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JFundListProcessIncludes.h-arc  $
 * 
 *    Rev 1.8   Mar 21 2003 17:44:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   22 May 2002 18:20:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:17:50   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Dec 11 2000 11:53:54   VASILEAD
 * Fixed the fund prices list for a range date bug
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

