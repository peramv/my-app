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
// ^FILE   : SettlementTradeBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2003
//
// ^CLASS    : SettlementTradeBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0200_vw.hpp>
#include "SettlementTradeBankInstructions.hpp"
#include "SettlementTradeBankInstructionsList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("SettlementTradeBankInstructionsList");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT;
}

//******************************************************************************
SettlementTradeBankInstructionsList::SettlementTradeBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsExList(parent, BANKTYPE::SETTLEMENT, 
   ifds::DSTC0200_VW, ifds::DSTC0200_VWRepeat_Record)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
SettlementTradeBankInstructionsList::~SettlementTradeBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY SettlementTradeBankInstructionsList::doCreateNewObject(BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   SettlementTradeBankInstructions *pSettlementTradeBankInstructions = 
      new SettlementTradeBankInstructions(*this);

   pSettlementTradeBankInstructions->initNew(idDataGroup);
   pBase = pSettlementTradeBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementTradeBankInstructionsList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   SettlementTradeBankInstructions *pSettlementTradeBankInstructions = 
      new SettlementTradeBankInstructions(*this);

   //this is Settlement Trade's repeat view data
   pSettlementTradeBankInstructions->init(data, BF::HOST);
   pObjOut = pSettlementTradeBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTradeBankInstructionsList.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:54:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Oct 04 2003 16:01:00   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.0   Jun 10 2003 16:13:12   popescu
// Initial revision.
// 
 */