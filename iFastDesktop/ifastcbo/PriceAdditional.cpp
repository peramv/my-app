//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : PriceAdditional.cpp
// ^AUTHOR : 
// ^DATE   : 03 May 2017
//
// ^CLASS    : PriceAdditional
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "PriceAdditional.hpp"
#include "DSTCommonFunction.hpp"

namespace
{
   const I_CHAR * const CLASSNAME               = I_("PriceAdditional");
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId TransType;
    extern CLASS_IMPORT const BFTextFieldId TransTypeDesc;
    extern CLASS_IMPORT const BFTextFieldId PriceCode;
    extern CLASS_IMPORT const BFDecimalFieldId UnitValue;
    extern CLASS_IMPORT const BFDecimalFieldId ChgFactor;
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,                       State Flags,            Group Flags 
   { ifds::TransType,                  BFCBO::NOT_ON_HOST,           0 },
   { ifds::TransTypeDesc,              BFCBO::NOT_ON_HOST,           0 },
   { ifds::UnitValue,                  BFCBO::NOT_ON_HOST,           0 },
   { ifds::ChgFactor,                  BFCBO::NOT_ON_HOST,           0 },
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************************
PriceAdditional::PriceAdditional(BFAbstractCBO &parent)
: MFCanBFCbo(parent)
{
    TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

    registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO*)&classFieldInfo, 0, NULL);
}

//******************************************************************************************
PriceAdditional::~PriceAdditional()
{
    TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************************
SEVERITY PriceAdditional::init(const DString &transType,
                               const DString &unitValue,
                               const DString &chgFactor,
                               const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

    setFieldNoValidate(ifds::TransType, transType, idDataGroup, false, true, true, false);
    setFieldNoValidate(ifds::UnitValue, unitValue, idDataGroup, false, true, true, false);
    setFieldNoValidate(ifds::ChgFactor, chgFactor, idDataGroup, false, true, true, false);

    DString transTypeDesc = DSTCommonFunctions::getDescription(transType, ifds::PriceCode);
    setFieldNoValidate(ifds::TransTypeDesc, transTypeDesc, idDataGroup, false, true, true, false);

    clearUpdatedFlags(idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}