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
// ^FILE   : MatSweepInstrBankList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May 2003
//
// ^CLASS    : MatSweepInstrBankList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0428_vw.hpp>
#include "MatSweepInstrBank.hpp"
#include "MatSweepInstrBankList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("MatSweepInstrBankList");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const MATURITY_INSTRUCTIONS;
}

//******************************************************************************
MatSweepInstrBankList::MatSweepInstrBankList(BFAbstractCBO &parent)
: BankInstructionsExList(parent, BANKTYPE::MATURITY_INSTRUCTIONS, 
   ifds::DSTC0428_VW, ifds::DSTC0428_VWRepeat_Record)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
MatSweepInstrBankList::~MatSweepInstrBankList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY MatSweepInstrBankList::doCreateNewObject(BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   MatSweepInstrBank *pMatSweepInstrBank = 
      new MatSweepInstrBank(*this);

   pMatSweepInstrBank->initNew(idDataGroup);
   pBase = pMatSweepInstrBank;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrBankList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   MatSweepInstrBank *pMatSweepInstrBank = 
      new MatSweepInstrBank(*this);

   //this is Mat Instruction's repeat view data
   pMatSweepInstrBank->init(data, BF::HOST);
   pObjOut = pMatSweepInstrBank;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstrBankList.cpp-arc  $
// 
//    Rev 1.0   Feb 01 2012 13:33:22   if991250
// Initial revision.
// 
 */