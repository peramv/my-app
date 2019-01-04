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
//    Copyright 1997 by DST Systems, Inc.
//    AUTHOR : Serban Popescu
//    DATE   : Octber, 2006
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
}

const BFFieldId ShouldAskForRep (10001, I_("ShouldAskForRep"));
const BFContainerId CLONE_ACCOUNT (1001);


namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId InterAccount;
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId CreateRep;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CloneAccountProcessIncludes.h-arc  $
//
//   Rev 1.0   Nov 08 2006 17:32:18   popescu
//Initial revision.
//
 */

