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
//    Copyright 2002 by International Financial Data Services
//    AUTHOR : 
//    DATE   : May 24,2002
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId DIRECT_TRADING_LIST;
   extern IFASTBP_LINKAGE const BFContainerId BANK_INSTRUCTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}

namespace DirectTrading_Para
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DirectTradingHeadSet;
   extern CLASS_IMPORT const BFTextFieldId DTAType;
}

//#include <ifastdataimpl\dse_dstc0200_vw.hpp>

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/*
 */

