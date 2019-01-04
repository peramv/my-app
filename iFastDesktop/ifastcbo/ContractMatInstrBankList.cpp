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
// ^FILE   : ContractMatInstrBankList.cpp
// ^AUTHOR : Chetan Balepur
// ^DATE   :
//
// ^CLASS    : ContractMatInstrBankList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0430_vw.hpp>
#include "ContractMatInstrBank.hpp"
#include "ContractMatInstrBankList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("ContractMatInstrBankList");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const MATURITY_INSTRUCTIONS;
}

//******************************************************************************
ContractMatInstrBankList::ContractMatInstrBankList(BFAbstractCBO &parent)
: BankInstructionsExList(parent, BANKTYPE::MATURITY_INSTRUCTIONS, 
   ifds::DSTC0430_VW, ifds::DSTC0430_VWRepeat_Record)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   setObjectAsList();
}

//******************************************************************************
ContractMatInstrBankList::~ContractMatInstrBankList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY ContractMatInstrBankList::doCreateNewObject(BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   ContractMatInstrBank *pContractMatInstrBank = new ContractMatInstrBank (*this);

   pContractMatInstrBank->initNew(idDataGroup);

   pBase = pContractMatInstrBank;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractMatInstrBankList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   ContractMatInstrBank *pContractMatInstrBank = new ContractMatInstrBank (*this);

   //this is Mat Instruction's repeat view data
   pContractMatInstrBank->init(data, BF::HOST);

   pObjOut = pContractMatInstrBank;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractMatInstrBankList.cpp-arc  $
// 
//    Rev 1.0   Mar 02 2012 16:13:00   wp040100
// Initial revision.
// 
//
// 
 */