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
#include <ifastdataimpl\dse_dstc0117_vw.hpp>
#include <ifastdataimpl\dse_dstc0117_req.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int TRANS_SUMMARY_LIST = 1;
//CP20030319const int TRANS_SUMMARY_LIST_DETAILS = 2;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRANS_SUMMARY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANS_SUMMARY_LIST_DETAILS;
}
namespace TRANSSUMMARYLIT //entity search literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM ;  
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_DATE; 
   extern IFASTBP_LINKAGE const I_CHAR * const TO_DATE; 
   extern IFASTBP_LINKAGE const I_CHAR * const NEXTORPREVIOUS;  
   extern IFASTBP_LINKAGE const I_CHAR * const SORTORDER; 
   extern IFASTBP_LINKAGE const I_CHAR * const NEXT_KEY;  
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionSummaryProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 21 2003 17:49:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:42   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:19:14   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:19:02   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Mar 19 2001 10:05:12   VASILEAD
//Added details
 * 
 *    Rev 1.6   Dec 14 2000 15:53:56   FENGYONG
 * remove #3
 * 
 */

