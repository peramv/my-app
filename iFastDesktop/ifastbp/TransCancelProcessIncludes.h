#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransCancelProcessinclude.h
// ^AUTHOR : 
// ^DATE   : 03/15/2005
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

#include <ifastdataimpl\dse_dstc0337_vw.hpp>

#include <bfproc/bfcontainerid.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRANS_CANCEL;   
}

namespace TRANSCANCEL
{
   extern IFASTBP_LINKAGE const I_CHAR * const DISPLAY_REBOOK;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const CASH_DIV_PAID_AFTER;
   extern IFASTBP_LINKAGE const I_CHAR * const BULK_CANCEL;
   extern IFASTBP_LINKAGE const I_CHAR * const TRADE_DATE;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASS;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const TRADE_ADJUST_ID;
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransCancelProcessIncludes.h-arc  $
//
//   Rev 1.4   Dec 29 2005 13:13:14   porteanm
//Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
//
//   Rev 1.3   Nov 08 2005 18:39:00   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.2   Nov 06 2005 15:57:40   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.1   Jul 08 2005 09:38:34   Yingbaol
//PET1235,FN01:cancellation rebook
//
//   Rev 1.0   Mar 03 2005 19:01:34   Fengyong
//Initial revision.
 */

