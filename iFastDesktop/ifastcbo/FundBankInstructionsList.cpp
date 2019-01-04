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
// ^FILE   : FundBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ^CLASS    : FundBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include "fundbankinstructionslistrepository.hpp"
#include "fundbankinstructionslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("FundBankInstructionsList");
}

namespace ifds //should be deleted eventualy, is part of req 52

{
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundSponsor;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,	  Group Flags
   { ifds::FundSponsor, BFCBO::NONE, 0 }, 
   { ifds::FundCode,    BFCBO::NONE, 0 }, 
   { ifds::ClassCode,   BFCBO::NONE, 0 }, 
};

namespace BANKENTITY
{
   extern I_CHAR * const FUND;
   extern I_CHAR * const FUND_CLASS;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const FUND;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
FundBankInstructionsList::FundBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsList(parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList();
   //the parent of this list should always be a FundBankInstructionsListRepository object
   assert (dynamic_cast<FundBankInstructionsListRepository*>(&parent));
}

//******************************************************************************
FundBankInstructionsList::~FundBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY FundBankInstructionsList::init( const DString &dstrFundCode, 
                                         const BFDataGroupId &idDataGroup,
                                         const DString& dstrTrack /*= I_("N")*/, 
                                         const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
  
   BFData requestData (ifds::DSTC0052_REQ);

   requestData.setElementValue (ifds::BankingEntity, BANKENTITY::FUND);
   requestData.setElementValue (ifds::FundCode, dstrFundCode);
   setFieldNoValidate (ifds::FundCode, dstrFundCode, idDataGroup, false, true, true);
   BankInstructionsList::init (requestData, BANKTYPE::FUND, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundBankInstructionsList::init( const DString &fundCode, 
                                         const DString &classCode, 
                                         const BFDataGroupId &idDataGroup,
                                         const DString& dstrTrack /*= I_("N")*/, 
                                         const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
  
   BFData requestData (ifds::DSTC0052_REQ);

   requestData.setElementValue (ifds::BankingEntity, BANKENTITY::FUND_CLASS);
   requestData.setElementValue (ifds::FundCode, fundCode);
   requestData.setElementValue (ifds::ClassCode, classCode);
   setFieldNoValidate (ifds::FundCode, fundCode, idDataGroup, false, true, true);
   setFieldNoValidate (ifds::ClassCode, classCode, idDataGroup, false, true, true);
   BankInstructionsList::init(requestData, BANKTYPE::FUND_CLASS, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBankInstructionsList.cpp-arc  $
// 
//    Rev 1.3   Oct 18 2006 15:53:38   popescu
// PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
// 
//    Rev 1.2   Nov 14 2004 14:41:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jun 09 2003 17:40:00   popescu
// Added support for fund and class search, still stopped at the Gui level, because it shouldn't be functional yet; do not know the id for the bank entity when seraching for bank using fund and class
// 
//    Rev 1.0   May 31 2003 12:00:50   popescu
// Initial revision.
 */