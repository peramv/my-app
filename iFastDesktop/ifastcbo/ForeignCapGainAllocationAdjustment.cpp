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
// ^FILE   : ForeignCapGainAllocationAdjustment.cpp
// ^AUTHOR :   
// ^DATE   : 
//
// ^CLASS    : ForeignCapGainAllocationAdjustment 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "ForeignCapGainAllocationAdjustment.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "FundDetail.hpp"
#include "FundDetailList.hpp"

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId ManualTradesTransType;
    extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
    extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
    extern CLASS_IMPORT const BFDateFieldId LastDivDate;
    extern CLASS_IMPORT const BFTextFieldId TradeDivType;
}

namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const FOREIGN_CAPGAIN_ALLOCATION_ADJ;
}


namespace
{
    const I_CHAR * const CLASSNAME		= I_("ForeignCapGainAllocationAdjustment");
    const I_CHAR * const YES            = I_("Y");
    const I_CHAR * const NO             = I_("N");
}

namespace CND
{

}

namespace IFASTERR
{

}

namespace CALCULATEFROM
{
    extern CLASS_IMPORT I_CHAR * const AMOUNT;
    extern CLASS_IMPORT I_CHAR * const NUM_UNIT_ELIG_DIV;
    extern CLASS_IMPORT I_CHAR * const NUM_UNIT_DIV;
}

//******************************************************************************
ForeignCapGainAllocationAdjustment::ForeignCapGainAllocationAdjustment(BFAbstractCBO &parent) : ManualDividendAdjustment(parent)
{
    TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}


//******************************************************************************
ForeignCapGainAllocationAdjustment::~ForeignCapGainAllocationAdjustment()
{
    TRACE_DESTRUCTOR(CLASSNAME);
}     

//******************************************************************************
SEVERITY ForeignCapGainAllocationAdjustment::doInit(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

    setFieldSubstituteValues(ifds::TradesTransType, idDataGroup, ifds::ManualTradesTransType);
    setFieldNoValidate(ifds::TradesTransType, TRADETYPE::FOREIGN_CAPGAIN_ALLOCATION_ADJ, idDataGroup, false);
    setFieldNoValidate(ifds::TradeDivType, TRADETYPE::FOREIGN_CAPGAIN_ALLOCATION_ADJ, idDataGroup, false);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ForeignCapGainAllocationAdjustment::doInitWithDefaultValues(const BFDataGroupId &idDataGroup)
{
    ManualDividendAdjustment::doInitWithDefaultValues (idDataGroup);

    setFieldReadOnly(ifds::ToFund, idDataGroup, true);
    setFieldReadOnly(ifds::ToClass, idDataGroup, true);
    setFieldReadOnly(ifds::ToFundNumber, idDataGroup, true);
    setFieldReadOnly(ifds::NumUnitDividends, idDataGroup, true);
}

//******************************************************************************
SEVERITY ForeignCapGainAllocationAdjustment::doApplyRelatedChanges(const BFFieldId &idField, 
                                                                   const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
       
    ManualDividendAdjustment::doApplyRelatedChanges (idField, idDataGroup);

    if (idField == ifds::FromFundNumber)
    {
        setDefaultToFundClass(idDataGroup);
    }    
    
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ForeignCapGainAllocationAdjustment::doValidateField(const BFFieldId &idField, 
                                                             const DString &strValue, 
                                                             const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

    if (ManualDividendAdjustment::doValidateField (idField, strValue, idDataGroup) <= WARNING)
    {

    }

    return GETCURRENTHIGHESTSEVERITY ();
}


//****************************************************************************** 
SEVERITY ForeignCapGainAllocationAdjustment::validateFundClass(const DString &fundCode, 
                                                               const DString &classCode, 
                                                               const DString &accountNum, 
                                                               const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"));

    validateAccountHolding(fundCode, classCode, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ForeignCapGainAllocationAdjustment::validateToFundClass(const DString &toFund, 
                                                                 const DString &toClass, 
                                                                 const DString &accountNum, 
                                                                 const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateToFundClass"));

    ManualDividendAdjustment::validateToFundClass(toFund, toClass, accountNum, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ForeignCapGainAllocationAdjustment::validateFromToFundClass(const DString &fromFund,
                                                                     const DString &fromClass,
                                                                     const DString &toFund,
                                                                     const DString &toClass,
                                                                     const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFromToFundClass"));

    return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
void ForeignCapGainAllocationAdjustment::setDefaultEffectiveDate(const BFDataGroupId &idDataGroup)
{    
    DString dstrFromFund, dstrFromClass, dstrFromFundNumber;
    FundDetailList *pFundDetailList = NULL;
    FundDetail *pFundDetail = NULL;

    getField(ifds::FromFund, dstrFromFund, idDataGroup);
    getField(ifds::FromClass, dstrFromClass, idDataGroup);

    if (!dstrFromFund.empty() && !dstrFromClass.empty() &&
        getWorkSession().getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList &&
        pFundDetailList->getFundDetail(dstrFromFund, dstrFromClass, idDataGroup, pFundDetail) && pFundDetail)
    {
        DString dstrLastDivDate;
        pFundDetail->getField(ifds::LastDivDate, dstrLastDivDate, idDataGroup);

        setFieldNoValidate(ifds::EffectiveDate, NULL_STRING, idDataGroup, false , true, false, false);

        if (!dstrLastDivDate.empty() && dstrLastDivDate != I_("01010001"))
        {
            setField(ifds::EffectiveDate, dstrLastDivDate, idDataGroup, false, true);
        }
        else
        {
            DString dstrCurrBusDate;
            getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

            setField(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false, true);          
        }
    }
}


//******************************************************************************
void ForeignCapGainAllocationAdjustment::setDefaultToFundClass(const BFDataGroupId &idDataGroup)
{
    DString dstrFromFund, dstrFromClass, dstrFromFundNumber;

    getField(ifds::FromFund, dstrFromFund, idDataGroup);
    getField(ifds::FromClass, dstrFromClass, idDataGroup);

    //setFieldNoValidate(ifds::ToFund, dstrFromFund, idDataGroup, false, true, false, true);
    //setFieldNoValidate(ifds::ToClass, dstrFromClass, idDataGroup, false, true, false, true);

    setField(ifds::ToFund, dstrFromFund, idDataGroup, false);
    setField(ifds::ToClass, dstrFromClass, idDataGroup, false);

    setFieldReadOnly(ifds::ToFund, idDataGroup, true);
    setFieldReadOnly(ifds::ToClass, idDataGroup, true);
    setFieldReadOnly(ifds::ToFundNumber, idDataGroup, true);
}

//******************************************************************************
bool ForeignCapGainAllocationAdjustment::isReinvestmentRateRequired()
{
    return true;
}

//***** Returned value is not rounded yet. *************************************
BigDecimal ForeignCapGainAllocationAdjustment::calculateNumUnitDividendsFromAmount(const BFDataGroupId &idDataGroup)
{
    // There is no NumUnitDividends for this transtype.

    return 0;
}