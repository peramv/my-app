#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by IFDS
//
//******************************************************************************
//
// ^FILE   : TransactionLinkProcessIncludes.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 25/06/2005
//
// -----------------------------------------------------------------------------
//
#include <ifastdataimpl\dse_substitute_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_dstc0350_vw.hpp>
#include <ifastdataimpl\dse_dstc0350_req.hpp>
#include <ifastdataimpl\dse_dstc0350_vwrepeat_record.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRANSACTION_LINK_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACOUNT;
   extern IFASTBP_LINKAGE const BFContainerId TRANS_LIST;
}
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANS_LINK;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRANS_LINK;

namespace TRANS_LINK_PARAM
{
   //account number
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   //transaction number
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_NUM;
}






//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionLinkProcessIncludes.h-arc  $
//
//   Rev 1.0   Jul 06 2005 16:40:26   Yingbaol
//Initial revision.
 * 
 *
 */

