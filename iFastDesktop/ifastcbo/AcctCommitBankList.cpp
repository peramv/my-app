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
// ^FILE   : AcctCommitBankList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcctCommitBankList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0432_vw.hpp>
#include "AcctCommitBank.hpp"
#include "AcctCommitBankList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("AcctCommitBankList");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_COMMITMENT;
}

//******************************************************************************
AcctCommitBankList::AcctCommitBankList(BFAbstractCBO &parent)
: BankInstructionsExList(parent, BANKTYPE::ACCOUNT_COMMITMENT, 
   ifds::DSTC0432_VW, ifds::DSTC0432_VW)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
AcctCommitBankList::~AcctCommitBankList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY AcctCommitBankList::doCreateNewObject(BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   AcctCommitBank *pAcctCommitBank = 
      new AcctCommitBank(*this);

   pAcctCommitBank->initNew(idDataGroup);
   pBase = pAcctCommitBank;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctCommitBankList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   AcctCommitBank *pAcctCommitBank = 
      new AcctCommitBank(*this);

   //this is Mat Instruction's repeat view data
   pAcctCommitBank->init(data, BF::HOST);
   pObjOut = pAcctCommitBank;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCommitBankList.cpp-arc  $
// 
//    Rev 1.0   Feb 27 2012 09:16:02   if991250
// Initial revision.
// 
// 
 */