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
    extern IFASTBP_LINKAGE const BFContainerId ACCT_GUARNT_GUARD_OPTN_LIST;
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId AcctGuaranteeGuardOptHeadingSet;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_GUARNT_GUARD_OPTN;

const BFFieldId PRIMARY_ACCOUNT_OWNER(600);
const BFFieldId HasGoodGuarGuardRecordExist (601);
//const BFFieldId IsNonDummyRecord (602);
const BFFieldId AddNewAccountGuard (602);
const BFFieldId IsNewAccountGuardList (603);
const BFFieldId HasRecordAdded (604);

#include <ifastdataimpl\dse_dstc0004_vw.hpp>

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/AcctGuaranteeGuardOptProcessIncludes.h-arc  $ 
//
//   Rev 1.0   Sep 17 2010 05:27:30   kitticha
//Initial revision.
//