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
//    DATE   : June 2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//payment instructions
#include <ifastdataimpl\dse_dstc0256_vw.hpp>
//bank instructions
#include <ifastdataimpl\dse_dstc0052_vw.hpp>

const BFFieldId EnableBanking(1);
const BFFieldId ReloadBankList(2);
const BFFieldId OnlyBankListIsUpdated(3);
const BFFieldId RemoveBanks(4);
const BFFieldId HAS_NON_RECORDS(5);

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId PAYMENT_INSTRUCTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId BANK_INSTRUCTIONS_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AddressLine;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SalesRepName;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFTextFieldId PaymentInstructionsListHeading;
   extern CLASS_IMPORT const BFTextFieldId BankInstrHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId Status;
   extern CLASS_IMPORT const BFTextFieldId PaymentIdMethod;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PaymentInstructionsProcessIncludes.h-arc  $
//
//   Rev 1.6   Aug 09 2007 14:01:38   jankovii
//PET 2388 FN01 - Swift Payment Method ID.
//
//   Rev 1.5   Dec 09 2004 11:50:20   Fengyong
//PET1034745 - Add info box when no payment instruction record was added
//
//   Rev 1.4   Jul 31 2003 21:59:00   popescu
//Added support for PayType 'X' and support for Historical Info at the process level
//
//   Rev 1.3   Jul 29 2003 14:19:32   popescu
//Fixes regarding the Discard/Cancel dialog
//
//   Rev 1.2   Jul 10 2003 22:20:12   popescu
//check in for payment instruct, used mfcan_ip_param for some interporcess param passing
//
//   Rev 1.1   Jul 02 2003 17:49:32   popescu
//work for payment instructions feature 
//
//   Rev 1.0   Jul 01 2003 18:12:16   popescu
//Initial revision.
//
 */

