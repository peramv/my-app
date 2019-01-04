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
// ^FILE   : TransactionDetailsBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : TransactionDetailsBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "transactiondetailsbankinstructionslist.hpp"
#include "transactiondetails.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("TransactionDetailsBankInstructionsList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId TransId;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId PayType2;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
}

namespace BANK_TRXN_TYPE
{
   extern I_CHAR * const TRANSACTION;
}

//******************************************************************************
TransactionDetailsBankInstructionsList::TransactionDetailsBankInstructionsList(
   BFAbstractCBO &parent) : 
   BankInstructions4TrxnList (parent, BANKTYPE::TRANSACTION) 
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   //the parent of this list should always be a TransactionDetails object
   assert (dynamic_cast<TransactionDetails*> (&parent));
}

//******************************************************************************
TransactionDetailsBankInstructionsList::~TransactionDetailsBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY TransactionDetailsBankInstructionsList::init ( const DString &accountNum,
                                                        const BFDataGroupId &idDataGroup, 
                                                        const DString &dstrTrack /*= I_("N")*/, 
                                                        const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString recordId, 
      transType, 
      payType2;

   getParent()->getField (ifds::TransId, recordId, idDataGroup, false);
   getParent()->getField (ifds::TransType, transType, BF::HOST, false);
   getParent()->getField (ifds::PayType2, payType2, idDataGroup, false);

   BankInstructions4TrxnList::init ( accountNum, 
                                     recordId, 
                                     transType,  
                                     BANK_TRXN_TYPE::TRANSACTION, 
                                     I_("P-") + payType2,
                                     NULL_STRING,
                                     NULL_STRING);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionDetailsBankInstructionsList.cpp-arc  $
// 
//    Rev 1.5   27 Jul 2007 15:40:50   popescu
// Incident 948449 - disabled the last EFT banking records call
// 
//    Rev 1.4   Nov 14 2004 14:58:16   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Nov 04 2004 17:41:48   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.2   Nov 10 2003 14:53:06   popescu
// Revised the names of the suppporting objects based on Desktop's naming standards
// 
//    Rev 1.1   Oct 28 2003 10:44:46   FENGYONG
// Add transpaytype as a parameter when get the list
// 
//    Rev 1.0   Oct 19 2003 19:08:40   popescu
// Initial revision.
// 
// Initial revision.
 */