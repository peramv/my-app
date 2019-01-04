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
//    DATE   : August, 2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0058_vw.hpp>

const BFFieldId TotalAmount(1);
const BFFieldId TotalPercent(2);
const BFFieldId AllowFullTransfer(3);

const BFContainerId TRADE_P(11);
const BFContainerId TRADE_H(21);
const BFContainerId TRADE(31);
const BFContainerId ACCOUNT_FROM(41);
const BFContainerId ACCOUNT_TO(51);

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRADE_FROM_FUND_ALLOCATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_ALLOCATION_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId AmtType;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId ToAllocListHeading;
   extern CLASS_IMPORT const BFTextFieldId FromAllocListHeading;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
   extern CLASS_IMPORT const BFNumericFieldId AccountTo;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId TfrAcct;
   extern CLASS_IMPORT const BFTextFieldId Allocation;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFTextFieldId AllowFullTransfer;
   extern CLASS_IMPORT const BFTextFieldId FullTransfer;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MultiFundAllocationProcessIncludes.h-arc  $
//
//   Rev 1.1   Sep 01 2003 21:21:14   popescu
//PET 809 FN 02, CIBC Multi fund enhancement
//
//   Rev 1.0   Aug 14 2003 15:48:18   popescu
//Initial revision.
 */

