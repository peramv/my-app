#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services, Ltd.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2009 by International Financial Data Services, Ltd.
//    AUTHOR : 
//    DATE   : 
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
    extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
    extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
    extern IFASTBP_LINKAGE const BFContainerId INVESTOR_AUTHORIZATION_INFO;  
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId InvestorAuthorizationHeadingSet;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION;

const BFFieldId PRIMARY_ACCOUNT_OWNER(600);

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0395_req.hpp>
#include <ifastdataimpl\dse_dstc0395_vw.hpp>
#include <ifastdataimpl\dse_dstc0395_vwrepeat_record.hpp>

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/InvestorAuthorizationInfoProcessIncludes.h-arc  $ 
//
//   Rev 1.1   Jul 09 2009 23:30:08   dchatcha
//PET156681 FN14 H36 Investor Authorization,Fix compile error.
//
//   Rev 1.0   Jul 09 2009 14:40:42   dchatcha
//Initial revision.
//
