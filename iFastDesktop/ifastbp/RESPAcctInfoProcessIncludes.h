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
//    Copyright 2010 by International Financial Data Services, Ltd.
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
}

namespace ifds
{
    //extern CLASS_IMPORT const BFTextFieldId InvestorAuthorizationHeadingSet;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_ACCT_INFO;

const BFFieldId PRIMARY_ACCOUNT_OWNER(600);

#include <ifastdataimpl\dse_dstc0004_vw.hpp>

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/RESPAcctInfoProcessIncludes.h-arc  $ 
//
//   Rev 1.0   Mar 12 2010 14:23:00   dchatcha
//Initial revision.
//

