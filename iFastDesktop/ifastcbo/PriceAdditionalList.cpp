//******************************************************************************
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
// ^FILE   : PriceAdditionalList.cpp
// ^AUTHOR :
// ^DATE   : 03 May 2017
//
// ^CLASS    : PriceAdditionalList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "PriceAdditionalList.hpp"
#include "PriceAdditional.hpp"

using namespace std;

namespace
{
	const I_CHAR * const CLASSNAME = I_("PriceAdditionalList");
}

namespace ifds
{
    extern CLASS_IMPORT const BFDateFieldId ValueAsAt;
    extern CLASS_IMPORT const BFTextFieldId FundName;
    extern CLASS_IMPORT const BFTextFieldId rxFundCode;
    extern CLASS_IMPORT const BFTextFieldId rxClassCode;
}

namespace PRICE_ADDI
{
    extern CLASS_EXPORT I_CHAR * const UNIT_ID     = I_("UnitId");
    extern CLASS_EXPORT I_CHAR * const TRADE_DATE  = I_("TraeDate");
    extern CLASS_EXPORT I_CHAR * const FUND_CODE   = I_("FundCode");
    extern CLASS_EXPORT I_CHAR * const CLASS_CODE  = I_("ClassCode");

    extern CLASS_EXPORT I_CHAR * const PRICE_CODE = I_("PriceCode");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE = I_("UnitValue");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR = I_("ChgFactor");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,                       State Flags,            Group Flags 
   { ifds::ValueAsAt,                  BFCBO::NOT_ON_HOST,           0 },
   { ifds::FundName,                   BFCBO::NOT_ON_HOST,           0 },
   { ifds::rxFundCode,                 BFCBO::NOT_ON_HOST,           0 },
   { ifds::rxClassCode,                BFCBO::NOT_ON_HOST,           0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
PriceAdditionalList::PriceAdditionalList(BFAbstractCBO &parent)
    :MFCanBFCbo(parent)
{
    TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

    registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
    setObjectAsList();
}


//******************************************************************************
PriceAdditionalList::~PriceAdditionalList()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}


//******************************************************************************
SEVERITY PriceAdditionalList::init(const DString &tradeDate, 
                                   const DString &fundCode, 
                                   const DString &classCode, 
                                   list<map<DString, DString>> &priceList, 
                                   const BFDataGroupId &idDataGroup)                            
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

    setFieldNoValidate(ifds::ValueAsAt, tradeDate, idDataGroup, false, true, true);
    setFieldNoValidate(ifds::rxFundCode, fundCode, idDataGroup, false, true, true);
    setFieldNoValidate(ifds::rxClassCode, classCode, idDataGroup, false, true, true);

    DString dstrFundName;
    getWorkSession().getFundName(fundCode, dstrFundName);
    setFieldNoValidate(ifds::FundName, dstrFundName, idDataGroup, false, true, true);

    for (list<map<DString, DString>>::iterator iterPriceList = priceList.begin(); iterPriceList != priceList.end(); iterPriceList++)
    {
        DString transType = (*iterPriceList)[PRICE_ADDI::PRICE_CODE];
        DString unitValue = (*iterPriceList)[PRICE_ADDI::UNIT_VALUE];
        DString chgFactor = (*iterPriceList)[PRICE_ADDI::CHG_FACTOR];

        if (!transType.stripAll().empty())
        {
            DString dstrKey;
            BFObjectKey objKey(dstrKey, idDataGroup);
            PriceAdditional *pPriceAdditional = NULL;

            pPriceAdditional = dynamic_cast<PriceAdditional*>(getNewListItem(objKey));   
            pPriceAdditional->init(transType, unitValue, chgFactor, idDataGroup);
        }
    }

    clearUpdatedFlags(idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PriceAdditionalList::doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   PriceAdditional *pPriceAdditional = new PriceAdditional(*this);
   pObjOut = pPriceAdditional;

   return GETCURRENTHIGHESTSEVERITY();
}