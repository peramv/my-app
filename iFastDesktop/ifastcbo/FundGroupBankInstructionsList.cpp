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
// ^FILE   : FundGroupBankInstructionsList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include "fundgroupbankinstructionslist.hpp"

namespace
{
   const I_CHAR * CLASSNAME = I_("FundGroupBankInstructionsList");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,	  Group Flags
   { ifds::FundGroup, BFCBO::NONE, 0 }, 
};

namespace BANKENTITY
{
   extern I_CHAR * const FUND_GROUP;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const FUND_GROUP;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
FundGroupBankInstructionsList::FundGroupBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsList(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList();
   //the parent of this list should always be a FundBankInstructionsListRepository object
///   assert(dynamic_cast<FundBankInstructionsListRepository*>(&parent));
}

//******************************************************************************
FundGroupBankInstructionsList::~FundGroupBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY FundGroupBankInstructionsList::init( const DString &fundGroup, 
                                              const BFDataGroupId &idDataGroup,
                                              const DString& dstrTrack /*= I_("N")*/, 
                                              const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
  
   BFData requestData (ifds::DSTC0052_REQ);

   requestData.setElementValue (ifds::BankingEntity, BANKENTITY::FUND_GROUP);
   requestData.setElementValue (ifds::FundGroup, fundGroup);
   setFieldNoValidate (ifds::FundGroup, fundGroup, idDataGroup, false, true, true);
   BankInstructionsList::init (requestData, BANKTYPE::FUND_GROUP, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundGroupBankInstructionsList.cpp-arc  $
// 
//    Rev 1.2   Oct 18 2006 15:53:58   popescu
// PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
// 
//    Rev 1.1   Nov 14 2004 14:42:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Sep 21 2004 16:42:50   HERNANDO
// Initial revision.
