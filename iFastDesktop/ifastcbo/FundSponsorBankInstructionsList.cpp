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
// ^FILE   : FundSponsorBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2006
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include "fundsponsorbankinstructionslist.hpp"
#include "fundbankinstructionslistrepository.hpp"

namespace
{
   const I_CHAR * CLASSNAME = I_("FundSponsorBankInstructionsList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundSponsor;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,	  Group Flags
   { ifds::FundSponsor, BFCBO::NONE, 0 }, 
};

namespace BANKENTITY
{
   extern I_CHAR * const FUND_SPONSOR;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const FUND_SPONSOR;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
FundSponsorBankInstructionsList::FundSponsorBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsList(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList();
//the parent of this list should always be a FundBankInstructionsListRepository object
   assert(dynamic_cast<FundBankInstructionsListRepository*>(&parent));
}

//******************************************************************************
FundSponsorBankInstructionsList::~FundSponsorBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY FundSponsorBankInstructionsList::init( const DString &fundSponsor, 
                                                const BFDataGroupId &idDataGroup,
                                                const DString& dstrTrack /*= I_("N")*/, 
                                                const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
  
   BFData requestData (ifds::DSTC0052_REQ);

   requestData.setElementValue (ifds::BankingEntity, BANKENTITY::FUND_SPONSOR);
   requestData.setElementValue (ifds::FundSponsor, fundSponsor);
   setFieldNoValidate (ifds::FundSponsor, fundSponsor, idDataGroup, false, true, true);
   BankInstructionsList::init (requestData, BANKTYPE::FUND_SPONSOR, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSponsorBankInstructionsList.cpp-arc  $
// 
//    Rev 1.0   Oct 18 2006 15:47:14   popescu
// Initial revision.
// 
//    Rev 1.1   Nov 14 2004 14:42:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Sep 21 2004 16:42:50   HERNANDO
// Initial revision.
