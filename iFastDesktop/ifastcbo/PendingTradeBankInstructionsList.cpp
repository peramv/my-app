//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : PendingTradeBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : PendingTradeBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "pendingtradebankinstructionslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("PendingTradeBankInstructionsList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId PendingRid;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId PayType2;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
}

namespace BANK_TRXN_TYPE
{
   extern I_CHAR * const PENDING_TRADE;
   extern I_CHAR * const LAST_PENDING_TRADE;
}

//******************************************************************************
PendingTradeBankInstructionsList::PendingTradeBankInstructionsList(
   BFAbstractCBO &parent) : 
   BankInstructions4TrxnList (parent, BANKTYPE::PENDING_TRADE) 
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
PendingTradeBankInstructionsList::~PendingTradeBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY PendingTradeBankInstructionsList::initLastEFT ( const DString &accountNum,
                                                         const DString &transType,
                                                         const DString &currency,
                                                         const DString &payType,
                                                         const DString &effectiveDate, 
                                                         const BFDataGroupId &idDataGroup, 
                                                         const DString &dstrTrack /*= I_("N")*/, 
                                                         const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initLastEFT"));

   BankInstructions4TrxnList::init (accountNum, 
                                    NULL_STRING, 
                                    transType,
                                    BANK_TRXN_TYPE::LAST_PENDING_TRADE, 
                                    transType + payType,
                                    currency,
                                    effectiveDate);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PendingTradeBankInstructionsList::init ( const DString &accountNum,
                                                  const BFDataGroupId &idDataGroup, 
                                                  const DString &dstrTrack /*= I_("N")*/, 
                                                  const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString recordId, 
      transType, 
      payType2;

   getParent()->getField(ifds::PendingRid, recordId, idDataGroup, false);
   getParent()->getField(ifds::TransType, transType, idDataGroup, false);
   getParent()->getField(ifds::PayType2, payType2, idDataGroup, false);
   BankInstructions4TrxnList::init ( accountNum, 
                                     recordId, 
                                     transType,
                                     BANK_TRXN_TYPE::PENDING_TRADE, 
                                     I_("P-") + payType2,
                                     NULL_STRING,
                                     NULL_STRING);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PendingTradeBankInstructionsList.cpp-arc  $
// 
//    Rev 1.5   27 Jul 2007 15:40:48   popescu
// Incident 948449 - disabled the last EFT banking records call
// 
//    Rev 1.4   Nov 14 2004 14:51:00   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Nov 04 2004 17:38:16   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.2   Nov 10 2003 14:53:00   popescu
// Revised the names of the suppporting objects based on Desktop's naming standards
// 
//    Rev 1.1   Oct 28 2003 10:39:30   FENGYONG
// Add transpaytype as a parameter when get the list
// 
//    Rev 1.0   Oct 19 2003 19:08:36   popescu
// Initial revision.
// 
// Initial revision.
 */