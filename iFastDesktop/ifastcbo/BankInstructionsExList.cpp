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
// ^FILE   : BankInstructionsExList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May 2003
//
// ^CLASS    : BankInstructionsExList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "bankinstructionsexlist.hpp"
#include "bankinstructionsex.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("BankInstructionsExList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId RepeatCount;
   extern CLASS_IMPORT const BFTextFieldId MoreAvailable;
   extern CLASS_IMPORT const BFTextFieldId NextKey;
}

//******************************************************************************
BankInstructionsExList::BankInstructionsExList(BFAbstractCBO &parent,
   const DString &dstrBankType, const BFDataId &parentDataId, 
   const BFDataId &parentRepeatId)
: BankInstructionsList(parent),
_dstrBankType(dstrBankType),
_parentDataId(parentDataId),
_parentRepeatId(parentRepeatId),
_pBFData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
BankInstructionsExList::~BankInstructionsExList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pBFData)
   {
      delete _pBFData;
   }
}

//******************************************************************************
SEVERITY BankInstructionsExList::initNew(const DString &dstrAccountNum, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   setFieldNoValidate(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   //call the base
   BankInstructionsList::initNew(_dstrBankType, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsExList::init(const DString &dstrAccountNum,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   setFieldNoValidate(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
   //call the base
   BankInstructionsList::init(_dstrBankType, idDataGroup);
   buildDataObject(idDataGroup);
   createObjectForEachRepeat(*_pBFData);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsExList::buildDataObject(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildDataObject"));
   BFData *pBFDataRepeat = new BFData(_parentRepeatId);

   //create a response view object and pass it to the list
   _pBFData = new BFData(_parentDataId);
   _pBFData->setElementValue(ifds::MoreAvailable, I_("N"));
   _pBFData->setElementValue(ifds::NextKey, NULL_STRING);
   _pBFData->setElementValue(ifds::RepeatCount, I_("1"));
   //fill this object with the data from the parent,
   //only one repeat, is created
   if (getParent()->getData(*pBFDataRepeat, idDataGroup) <= WARNING)
   {
      _pBFData->addRepeat(*pBFDataRepeat);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructionsExList.cpp-arc  $
// 
//    Rev 1.1   Oct 19 2003 16:43:38   popescu
// CIBC, PET809, FN 13 banking work
// 
//    Rev 1.0   Oct 04 2003 16:08:40   popescu
// Initial revision.
// 
//    Rev 1.2   Jun 18 2003 17:45:04   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.1   Jun 10 2003 16:10:48   popescu
// Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
// 
//    Rev 1.0   Jun 03 2003 21:00:56   popescu
// Initial revision.
 */