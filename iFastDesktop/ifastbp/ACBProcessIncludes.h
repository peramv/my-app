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
//
// ^FILE   : ACBProcessIncludes.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0015_vw.hpp>
#include <ifastdataimpl\dse_dstc0015_req.hpp>
#include <ifastdataimpl\dse_dstc0063_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0020_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp> //P0185327_FN01 - ROC Depleting ACB

#include <ifastdataimpl\dse_listviewheading.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACB_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}
// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int ACB_LIST = 1;
//CP20030319const int FUND_MASTER_LIST     = 2;  
//CP20030319const int FUND_LIST = 3;
//CP20030319const int MFACCOUNT_CBO = 4;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ACBProcessIncludes.h-arc  $
 * 
 *    Rev 1.7   Sep 14 2011 10:09:44   panatcha
 * P0185327_FN01 - ROC Depleting ACB
 * 
 *    Rev 1.6   Mar 21 2003 17:33:40   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:52:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:22:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:14:40   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Aug 02 2000 13:46:04   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.1   Feb 15 2000 18:56:08   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:52   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Sep 30 1999 09:54:18   YINGZ
 * use sub list
 * 
 *    Rev 1.1   Jul 08 1999 10:03:22   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

