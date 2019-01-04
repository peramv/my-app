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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RegPlanTransferProcessIncludes.h
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
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

#include <ifastdataimpl\dse_dstc0472_vw.hpp>
#include <ifastdataimpl\dse_dstc0473_vw.hpp>
#include <ifastdataimpl\dse_dstc0474_vw.hpp>
#include <ifastdataimpl\dse_dstc0474_req.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId REG_PLAN_TRANSFER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId REG_PLAN_TRANSFER_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;

}
namespace REG_PLAN_TRANSFER
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLD_NUMBER;
   const BFFieldId AreAllRecordsInactive(8001);
   const BFFieldId ORG_KEY(1100);
}

namespace ifds
{ 
   extern CLASS_IMPORT const BFTextFieldId IsDuringNASU;
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFDecimalFieldId TotAmount;
}

namespace NASULIT //nasu literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_ACCOUNT;
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_SHAREHOLDER;
}

