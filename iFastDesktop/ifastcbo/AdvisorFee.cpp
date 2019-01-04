//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : AdvisorFee.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 26 December 2013
//
// ^CLASS    : AdvisorFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "AdvisorFee.hpp"

namespace
{
    const I_CHAR * const CLASSNAME = I_("AdvisorFee");
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId TradesTransType;
}

namespace CND
{
    
}

namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const ADVISOR_FEE;
}

namespace PAYTYPE
{
    extern CLASS_IMPORT I_CHAR * const SYSTEM_CHEQUE;
} 

//******************************************************************************
AdvisorFee::AdvisorFee(BFAbstractCBO &parent): MgmtFee(parent), Redemption(parent), Trade(parent)
{
    TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}


//******************************************************************************
AdvisorFee::~AdvisorFee()
{
    TRACE_DESTRUCTOR(CLASSNAME);
} 


//******************************************************************************
SEVERITY AdvisorFee::doInit(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

    setFieldNoValidate(ifds::TradesTransType, TRADETYPE::ADVISOR_FEE, idDataGroup, false);

    return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
void AdvisorFee::doInitWithDefaultValues(const BFDataGroupId &idDataGroup)
{
    MgmtFee::doInitWithDefaultValues(idDataGroup);

    setFieldNoValidate(ifds::SuppressCode,  NULL_STRING, idDataGroup, false, true, true); 
    setFieldNoValidate(ifds::RedCode,       I_("DF"), idDataGroup, false, true, true);
    setFieldNoValidate(ifds::TradesPayType, PAYTYPE::SYSTEM_CHEQUE, idDataGroup, false, true, true);
    setFieldNoValidate(ifds::MFPayment,     I_("99"), idDataGroup, false, false, true);
}


//******************************************************************************
SEVERITY AdvisorFee::doValidateField(const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

    if (Redemption::doValidateField(idField, strValue, idDataGroup) <= WARNING)
    {

    }

    return GETCURRENTHIGHESTSEVERITY();
}



//****************************************************************************** 
SEVERITY AdvisorFee::validateFundClass(const DString &fundCode, 
                                       const DString &classCode, 
                                       const DString &accountNum, 
                                       const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"));

    if (Redemption::validateFundClass(fundCode, classCode, accountNum, idDataGroup) <= WARNING)
    {

    }

    return GETCURRENTHIGHESTSEVERITY();
}



//******************************************************************************
SEVERITY AdvisorFee::transTypeRelatedChanges(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("transTypeRelatedChanges"));

    Redemption::transTypeRelatedChanges (idDataGroup);

    setFieldNoValidate(ifds::TradesPayType, PAYTYPE::SYSTEM_CHEQUE, idDataGroup, false, false, true, false);

    return GETCURRENTHIGHESTSEVERITY ();
}
