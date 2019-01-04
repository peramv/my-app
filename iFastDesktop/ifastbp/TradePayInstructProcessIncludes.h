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
//    DATE   : August, 2006
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//trade payment instructions
#include <ifastdataimpl\dse_dstc0374_req.hpp>
#include <ifastdataimpl\dse_dstc0374_vw.hpp>
//bank instructions
#include <ifastdataimpl\dse_dstc0052_vw.hpp>

const BFFieldId EnableBanking (1);

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRADE_PAYMENT_INSTRUCTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRADE;
   extern IFASTBP_LINKAGE const BFContainerId PENDING_DETAILS;
   extern IFASTBP_LINKAGE const BFContainerId TRANSACTION_DETAILS;
}

const BFContainerId BANK (1001);

namespace BANKTYPE
{
	extern CLASS_IMPORT I_CHAR * const TRADE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AddressLine;
   extern CLASS_IMPORT const BFTextFieldId PaymentInstructionsListHeading;
   extern CLASS_IMPORT const BFTextFieldId TradePayInstructHeadSet;
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercent;
   extern CLASS_IMPORT const BFTextFieldId Broker;
   extern CLASS_IMPORT const BFTextFieldId Branch;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;	
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradePayInstructProcessIncludes.h-arc  $
//
//   Rev 1.3   Sep 22 2006 00:46:54   popescu
//STP 2217/13
//
//   Rev 1.2   Sep 21 2006 01:50:12   popescu
//STP PET 2217/13
//
//   Rev 1.1   Sep 07 2006 21:37:40   popescu
//STP 2192/02
//
//   Rev 1.0   Aug 29 2006 18:26:00   popescu
//Initial revision.
//
 */

