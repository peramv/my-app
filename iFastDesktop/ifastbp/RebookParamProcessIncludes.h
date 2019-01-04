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
//    Copyright 2005 IFDS.
//
//******************************************************************************
//
// ^FILE   : RebookParamProcessIncludes.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 06/26/2005
//

#include <ifastdataimpl\dse_substitute_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REBOOK_PARAM;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REBOOK_PARAM;



namespace TRANS_REBOOK_PARAM
{
   //account number
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   //transaction number
   extern IFASTBP_LINKAGE const I_CHAR * const TRANS_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ESTATE_ALLOC;
   extern IFASTBP_LINKAGE const I_CHAR * const COMMISSION_REBATE;
   extern IFASTBP_LINKAGE const I_CHAR * const REBOOK_EXIST;
   extern IFASTBP_LINKAGE const I_CHAR * const FUND_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const CLASS_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const REBOOK_COPY;
}

namespace RebookField
{
   const BFFieldId UseSameAccountTransType(1000);
   const BFFieldId IsEstateAllocation(1001);
   const BFFieldId IsCommissionRebate(1002);
   const BFFieldId RebookExist(1003);
   const BFFieldId RebookCopy(1004);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RebookParamProcessIncludes.h-arc  $
//
//   Rev 1.1   Feb 07 2006 11:29:36   AGUILAAM
//IN 534395 - fixed rebook for management fee (AF91) where multiple trades are linked to one transnum; match exact trade with fund/class.
//
//   Rev 1.0   Jul 06 2005 16:35:52   Yingbaol
//Initial revision.
 * 
 *
 */

