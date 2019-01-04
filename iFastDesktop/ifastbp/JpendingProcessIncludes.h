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
// ^FILE   : TransactionHistoryProcessinclude.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/04/1999
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


#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_req.hpp>
#include <ifastdataimpl\dse_dstc0054_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_req.hpp>
#include <ifastdataimpl\dse_dstc0136_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0121_vw.hpp>


// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int FUND_DETAIL_LIST = 1;
//CP20030319const int PENDING_LIST = 2;
//CP20030319const int TRANSLATION_LIST = 3;
//CP20030319const int MGMTCOOPTIONS_LIST = 4;
//CP20030319const int ADDR_LIST = 5;
//CP20030319const int ACQFEEINQUIRY_CBO = 6;
//CP20030319const int PENDING_DETAILS = 7;

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACQFEEINQUIRY_CBO;
   extern IFASTBP_LINKAGE const BFContainerId ADDR_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MGMTCOOPTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId PENDING_DETAILS;
   extern IFASTBP_LINKAGE const BFContainerId PENDING_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANSLATION_LIST;
}
namespace PENDINGLIT
{
   // Trace literals
   extern IFASTBP_LINKAGE const I_CHAR * const pACCOUNTNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const pSHAREHOLDERNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const pFUNDCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const pCLASSCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const pNUMENTRY;
   extern IFASTBP_LINKAGE const I_CHAR * const pTRANSTYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const pTRANSNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const pTRADEDATE;
   extern IFASTBP_LINKAGE const I_CHAR * const pBROKERCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const pBRANCHCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const pSLSREPCODE;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JpendingProcessIncludes.h-arc  $
//
//   Rev 1.9   Mar 21 2003 17:44:18   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.8   Oct 09 2002 23:53:26   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.7   22 May 2002 18:20:30   PURDYECH
//BFData Implementation
//
//   Rev 1.6   19 Mar 2002 13:17:50   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.5   Mar 12 2001 12:58:36   VASILEAD
//Modified for FUNDcom release
//
//   Rev 1.4   Jan 02 2001 11:52:40   VASILEAD
//Fixed DSC Override bug
//
//   Rev 1.3   Dec 14 2000 15:53:58   FENGYONG
//remove #3
//
//   Rev 1.2   Oct 04 2000 13:51:06   FENGYONG
//Add EntityList to get firstname and lastname
//
//   Rev 1.1   Sep 13 2000 16:55:40   FENGYONG
//Add brokercode, branchcode,slsrep
//
//   Rev 1.0   Sep 07 2000 11:56:56   FENGYONG
//Initial revision.
 *
 */

