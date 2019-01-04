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
// ^FILE   : JAcctTransProcessinclude.h
// ^AUTHOR : Yongmei Feng
// ^DATE   : 03/11/1999
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
#include <ifastdataimpl\dse_dstc0017_vw.hpp>
#include <ifastdataimpl\dse_dstc0017_req.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
#include <ifastdataimpl\dse_dstc0022_req.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0003_req.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0136_vw.hpp>

//CP20030319const int ALLOCATION=93;


// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int TRANS_LIST = 1;
//CP20030319const int DEDUCTION_LIST = 2;
//CP20030319const int FUNDSRCH_LIST = 3;
//CP20030319const int MGMTCOOPTIONS_LIST = 4;
//CP20030319const int TRANSLATION_LIST = 5; 
//CP20030319const int TRANS_DETAILS = 6;
//CP20030319const int MFACCOUNT_CBO = 7;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ALLOCATION;
   extern IFASTBP_LINKAGE const BFContainerId DEDUCTION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUNDSRCH_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId MGMTCOOPTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANS_DETAILS;
   extern IFASTBP_LINKAGE const BFContainerId TRANS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSLATION_LIST;
}
namespace ACCTTRANSLIT //entity search literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM ;  
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_CODE ;  
   extern IFASTBP_LINKAGE const I_CHAR * const CLASS_CODE;  
   extern IFASTBP_LINKAGE const I_CHAR * const NUM_ENTRY; 
   extern IFASTBP_LINKAGE const I_CHAR * const ALL_FUND_MODE; 
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUM; 
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSID;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_DESC;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctTransProcessIncludes.h-arc  $
 * 
 *    Rev 1.10   Mar 21 2003 17:42:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   22 May 2002 18:20:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   19 Mar 2002 13:17:40   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.6   Dec 14 2000 15:53:56   FENGYONG
 * remove #3
 * 
 *    Rev 1.5   Aug 22 2000 16:57:36   FENGYONG
 * Fix French fundname and French Desc
 * 
 *    Rev 1.4   Jun 28 2000 12:01:30   VASILEAD
 * Adapted to the new views
 * 
 *    Rev 1.3   Jun 16 2000 10:35:46   VASILEAD
 * Reduced the number of transacions to be sent
 * 
 *    Rev 1.2   Mar 24 2000 12:22:46   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.4   Mar 06 2000 15:51:22   FENGYONG
// add fundname & tfrfundname
// 
//    Rev 1.3   Mar 01 2000 16:11:18   FENGYONG
// Add CurrentDate
// 
//    Rev 1.2   Dec 15 1999 10:10:44   FENGYONG
// Add calculation of grossamt
// 
//    Rev 1.1   Nov 30 1999 11:02:10   FENGYONG
// Modified to adapt multipages
 * 
 */

