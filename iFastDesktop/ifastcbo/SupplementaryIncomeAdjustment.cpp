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
// ^FILE   : SupplementaryIncomeAdjustment.cpp
// ^AUTHOR :   
// ^DATE   : 
//
// ^CLASS    : SupplementaryIncomeAdjustment 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "SupplementaryIncomeAdjustment.hpp"
#include "fundmasterlist.hpp"
#include "FundClassDistribOptionsList.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId ManualTradesTransType;
    extern CLASS_IMPORT const BFDateFieldId LastDivdDate;
    extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId TradeDivType;
}

namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const SUPPLEMENTARY_INCOME_ADJ;
}


namespace
{
    const I_CHAR * const CLASSNAME		= I_("SupplementaryIncomeAdjustment");
    const I_CHAR * const YES            = I_("Y");
    const I_CHAR * const NO             = I_("N");
}

namespace CND
{
    extern const long ERR_DIV_TYPE_IS_NOT_AVAIL_FOR_FUNDCLASS;
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
SupplementaryIncomeAdjustment::SupplementaryIncomeAdjustment(BFAbstractCBO &parent) : ManualDividendAdjustment(parent)
{
    TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}


//******************************************************************************
SupplementaryIncomeAdjustment::~SupplementaryIncomeAdjustment()
{
    TRACE_DESTRUCTOR(CLASSNAME);
}     

//******************************************************************************
SEVERITY SupplementaryIncomeAdjustment::doInit(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

    setFieldSubstituteValues(ifds::TradesTransType, idDataGroup, ifds::ManualTradesTransType);
    setFieldNoValidate(ifds::TradesTransType, TRADETYPE::SUPPLEMENTARY_INCOME_ADJ, idDataGroup, false);
    setFieldNoValidate(ifds::TradeDivType, TRADETYPE::SUPPLEMENTARY_INCOME_ADJ, idDataGroup, false);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void SupplementaryIncomeAdjustment::doInitWithDefaultValues(const BFDataGroupId &idDataGroup)
{
    ManualDividendAdjustment::doInitWithDefaultValues (idDataGroup);

    setFieldNoValidate(ifds::DepositType, I_("30"), idDataGroup, false);
}

//******************************************************************************
SEVERITY SupplementaryIncomeAdjustment::doApplyRelatedChanges(const BFFieldId &idField, 
                                                              const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

    ManualDividendAdjustment::doApplyRelatedChanges (idField, idDataGroup);

    /*if (idField == ifds::TradesTransType)
    {

    }*/

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SupplementaryIncomeAdjustment::doValidateField(const BFFieldId &idField, 
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
SEVERITY SupplementaryIncomeAdjustment::validateFundClass(const DString &fundCode, 
                                                          const DString &classCode, 
                                                          const DString &accountNum, 
                                                          const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"))

    FundClassDistribOptionsList *pFundClassDistribOptionsList = NULL;
    FundClassDistribOptions *pFundClassDistribOptions = NULL;

    if (getFundClassDistribOptionsList(TRADETYPE::SUPPLEMENTARY_INCOME_ADJ, fundCode, classCode, idDataGroup, pFundClassDistribOptionsList) <= WARNING &&
        pFundClassDistribOptionsList && 
        pFundClassDistribOptionsList->getFundClassDistribOptions(TRADETYPE::SUPPLEMENTARY_INCOME_ADJ, idDataGroup, pFundClassDistribOptions) <= WARNING)
    {
        if (!pFundClassDistribOptions)
        {
            DString strIDI, dstrTradeTransType;

            getField(ifds::TradesTransType, dstrTradeTransType, idDataGroup, true);;

            addIDITagValue(strIDI, I_("DIVTYPE"), TRADETYPE::SUPPLEMENTARY_INCOME_ADJ);
            addIDITagValue(strIDI, I_("FUNDFROM"), fundCode);
            addIDITagValue(strIDI, I_("CLASSFROM"), classCode);

            ADDCONDITIONFROMFILEIDI (CND::ERR_DIV_TYPE_IS_NOT_AVAIL_FOR_FUNDCLASS, strIDI);
        }
    }

    validateAccountHolding(fundCode, classCode, idDataGroup);
    
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SupplementaryIncomeAdjustment::validateToFundClass(const DString &toFund, 
                                                            const DString &toClass, 
                                                            const DString &accountNum, 
                                                            const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateToFundClass"));

    ManualDividendAdjustment::validateToFundClass(toFund, toClass, accountNum, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SupplementaryIncomeAdjustment::validateFromToFundClass(const DString &fromFund,
                                                                const DString &fromClass,
                                                                const DString &toFund,
                                                                const DString &toClass,
                                                                const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFromToFundClass"));

    return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY SupplementaryIncomeAdjustment::getFundClassDistribOptionsList(const DString &distributionType, 
                                                                       const DString &fundCode, 
                                                                       const DString &classCode,
                                                                       const BFDataGroupId &idDataGroup,
                                                                       FundClassDistribOptionsList *&pFundClassDistribOptionsList)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundClassDistribOptionsList"));

    pFundClassDistribOptionsList = NULL;

    if (!distributionType.empty() && !fundCode.empty() && !classCode.empty())
    {
        DString strKey = I_("FundClassDistribOptionsList_") + distributionType + 
            I_("_") + fundCode + I_("_") + classCode;	

        pFundClassDistribOptionsList = dynamic_cast<FundClassDistribOptionsList*>(getObject(strKey, idDataGroup));

        if (!pFundClassDistribOptionsList)
        {
            pFundClassDistribOptionsList = new FundClassDistribOptionsList (*this);
            if (pFundClassDistribOptionsList->init (distributionType, fundCode, classCode ) > WARNING)
            {
                delete pFundClassDistribOptionsList;
                pFundClassDistribOptionsList = NULL;
            }
            else
            {
                setObject(pFundClassDistribOptionsList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
void SupplementaryIncomeAdjustment::setDefaultEffectiveDate(const BFDataGroupId &idDataGroup)
{    
    DString dstrFromFund, dstrFromClass;
    FundClassDistribOptionsList *pFundClassDistribOptionsList = NULL;
    FundClassDistribOptions *pFundClassDistribOptions = NULL;

    getField(ifds::FromFund, dstrFromFund, idDataGroup);
    getField(ifds::FromClass, dstrFromClass, idDataGroup);

    if (getFundClassDistribOptionsList(TRADETYPE::SUPPLEMENTARY_INCOME_ADJ, dstrFromFund, dstrFromClass, idDataGroup, pFundClassDistribOptionsList) <= WARNING &&
        pFundClassDistribOptionsList && 
        pFundClassDistribOptionsList->getFundClassDistribOptions(TRADETYPE::SUPPLEMENTARY_INCOME_ADJ, idDataGroup, pFundClassDistribOptions) <= WARNING &&
        pFundClassDistribOptions)
    {
        DString dstrLastDivdDate;
        pFundClassDistribOptions->getField(ifds::LastDivdDate, dstrLastDivdDate, idDataGroup, false);

        setFieldNoValidate(ifds::EffectiveDate, NULL_STRING, idDataGroup, false , true, false, false);

        if (!dstrLastDivdDate.empty() && dstrLastDivdDate != I_("01010001"))
        {
            setField(ifds::EffectiveDate, dstrLastDivdDate, idDataGroup, false, true);
        }
        else
        {
            DString dstrCurrBusDate;
            getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

            setField(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false, true);
        }
    }
}