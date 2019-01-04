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
// ^FILE   : ManualDividendAdjustment.cpp
// ^AUTHOR :   
// ^DATE   : 
//
// ^CLASS    : ManualDividendAdjustment 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "ManualDividendAdjustment.hpp"
#include "fundmasterlist.hpp"
#include "fundmaster.hpp"
#include "funddetaillist.hpp"
#include "FundDetail.hpp"
#include "MFAccountHoldingList.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "Shareholder.hpp"
#include "Broker.hpp"
#include "Intermediary.hpp"
#include "IntermediaryList.hpp"
#include "AddressList.hpp"
#include "TaxTypeRule.hpp"
#include "DilutionAllocList.hpp"

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId ManualTradesTransType;
    extern CLASS_IMPORT const BFTextFieldId PrcsSpDiv;
    extern CLASS_IMPORT const BFTextFieldId AcctableTradeDate;
    extern CLASS_IMPORT const BFTextFieldId FundType;
    extern CLASS_IMPORT const BFTextFieldId IntToDateType;
    extern CLASS_IMPORT const BFTextFieldId IntFromDateType;
    extern CLASS_IMPORT const BFTextFieldId PayIntOn;
    extern CLASS_IMPORT const BFTextFieldId NegMoneyMktInt;
    extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
    extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
    extern CLASS_IMPORT const BFDateFieldId LastDivDate;
    extern CLASS_IMPORT const BFTextFieldId FromFundClass;
    extern CLASS_IMPORT const BFTextFieldId ToFundClass;
    extern CLASS_IMPORT const BFTextFieldId FromFundClassValid;
    extern CLASS_IMPORT const BFTextFieldId ToFundClassValid;
    extern CLASS_IMPORT const BFDecimalFieldId DivRate;
    extern CLASS_IMPORT const BFDecimalFieldId ReinvestmentRate;
    extern CLASS_IMPORT const BFTextFieldId GAVApply;
    extern CLASS_IMPORT const BFTextFieldId MultiPrices;
    extern CLASS_IMPORT const BFDecimalFieldId UnitValue;
    extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
    extern CLASS_IMPORT const BFNumericFieldId DivUnitId;
    extern CLASS_IMPORT const BFNumericFieldId ReInvUnitId;
    extern CLASS_IMPORT const BFDecimalFieldId USDollar;
    extern CLASS_IMPORT const BFTextFieldId RoundCalcToCents;
    extern CLASS_IMPORT const BFNumericFieldId ShrNum;
    extern CLASS_IMPORT const BFTextFieldId DivChqAddr;
    extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
    extern CLASS_IMPORT const BFTextFieldId BrokCssStatus;
    extern CLASS_IMPORT const BFTextFieldId InterCode;
    extern CLASS_IMPORT const BFTextFieldId IntrCssStatus;
    extern CLASS_IMPORT const BFTextFieldId FundCategory;
    extern CLASS_IMPORT const BFDateFieldId StopDate;
    extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId CurrChkByTaxType;
    extern CLASS_IMPORT const BFTextFieldId TaxType;
    extern CLASS_IMPORT const BFTextFieldId TaxTypeByCurrChk;
    extern CLASS_IMPORT const BFTextFieldId InvalidCurr;
    extern CLASS_IMPORT const BFTextFieldId SelfDirected;
    extern CLASS_IMPORT const BFDecimalFieldId AccBalUnits;
    extern CLASS_IMPORT const BFTextFieldId RoundFlag;
    extern CLASS_IMPORT const BFTextFieldId AcctCIDElig;
    extern CLASS_IMPORT const BFTextFieldId SuppressCode2;
    extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId SelfDirected;
    extern CLASS_IMPORT const BFTextFieldId TradeDivType;
    extern CLASS_IMPORT const BFTextFieldId FromToFundClass;
}

namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const MANUAL_DIVIDEND_ADJ;
}


namespace
{
    const I_CHAR * const CLASSNAME		= I_("ManualDividendAdjustment");
    const I_CHAR * const YES            = I_("Y");
    const I_CHAR * const NO             = I_("N");
    const I_CHAR * const CASH           = I_("CASH");
    const I_CHAR * const ID_TYPE        = I_("ID");
    const I_CHAR * const AV_TYPE        = I_("AV");
    const I_CHAR * const EX_TYPE        = I_("EX");
    const I_CHAR * const GI_FUND        = I_("G");

    const int SCALE_VALUE               = -10;
}

namespace CND
{
    extern const long ERR_NEG_MONEY_MARKET_INTEREST_NOT_APPLICABLE_FOR_THIS_FUND;
    extern const long ERR_NEG_MM_CAN_BE_REINVESTED_ONLY_SAME_FUNDCLASS;
    extern const long ERR_ACCT_NO_HOLDINGS_FOR_FUND;
    extern const long ERR_MANUAL_DIVIDEND_NOT_ALLOWED;
    extern const long ERR_NO_DIVTYPE_UNIT_RATE_EXISTS_FOR_THIS_DATE;
    extern const long ERR_PAY_OUT_ADDR_MUST_BE_EQUAL_TO;
    extern const long ERR_EXCLUDE_IS_NOT_ALLOWED;
    extern const long WARN_INCORRECT_UNIT_OF_DIVDIDEND_IS_REINVESTED;
    extern const long ERR_ADDRESS_CODE_INVALID;
    extern const long ERR_GI_FUND_IS_NOT_ALLOWED;
    extern const long WARN_GI_FUND_IS_NOT_ALLOWED1;
    extern const long ERR_NSM_SETTLE_VALUE_IS_NOT_ALLOWED;
    extern const long WARN_NSM_SETTLE_VALUE_IS_NOT_ALLOWED;
    extern const long ERR_ACCTOUNTIBILITY_BACKDATEDREASON_ARE_REQUIRED_FOR_DILUTION;
    extern const long WARN_ACCTOUNTIBILITY_BACKDATEDREASON_ARE_REQUIRED_FOR_DILUTION;
    extern const long ERR_TAX_TYPE_IS_NOT_ALLOWED_TO_TRADE_IN_FUND_CURRENCY;
    extern const long ERR_AV_UNIT_RATE_DOES_NOT_EXIST_FOR_FUND_ON_DEFF;
    extern const long ERR_INSUFFICIENT_BALANCE_FOR_NEG_MONEY_MKT;
}

namespace IFASTERR
{
     
}

namespace NSM_SETTLE
{
    extern CLASS_EXPORT const I_CHAR * INCLUDE               = I_("In");
    extern CLASS_EXPORT const I_CHAR * EXCLUDE               = I_("Ex");
}

namespace CALCULATEFROM
{
    extern CLASS_EXPORT const I_CHAR * AMOUNT               = I_("AMOUNT");
    extern CLASS_EXPORT const I_CHAR * NUM_UNIT_ELIG_DIV    = I_("DIVIDEND_RATE");
    extern CLASS_EXPORT const I_CHAR * NUM_UNIT_DIV         = I_("REINVESTMENT_RATE");
}

namespace PRECISION
{
    extern CLASS_EXPORT const I_CHAR * AMOUNT               = I_("AMOUNT");
    extern CLASS_EXPORT const I_CHAR * NUM_UNIT_ELIG_DIV    = I_("DIVIDEND_RATE");
    extern CLASS_EXPORT const I_CHAR * NUM_UNIT_DIV         = I_("REINVESTMENT_RATE");
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    { ifds::NegMoneyMktInt,                 BFCBO::NONE,                 0},
    { ifds::RoundCalcToCents,               BFCBO::NOT_ON_HOST,          0},
    { ifds::PrcsSpDiv,                      BFCBO::NOT_ON_HOST,          0},
    { ifds::NumUnitEligDividends,           BFCBO::CALCULATED_FIELD,     0},
    { ifds::NumUnitDividends,               BFCBO::CALCULATED_FIELD,     0},
    { ifds::ReinvestmentRate,               BFCBO::NONE,                 0},
    { ifds::DivRate,                        BFCBO::NOT_ON_HOST,          0},
    { ifds::FromFundClassValid,             BFCBO::NOT_ON_HOST,          0},
    { ifds::ToFundClassValid,               BFCBO::NOT_ON_HOST,          0},
    { ifds::DivUnitId,                      BFCBO::NONE,                 0},
    { ifds::ReInvUnitId,                    BFCBO::NONE,                 0},
    { ifds::TradeDivType,                 BFCBO::NOT_ON_HOST,          0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
ManualDividendAdjustment::ManualDividendAdjustment(BFAbstractCBO &parent) : ManualDividend(parent)
{
    TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

    registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0, NULL);
}


//******************************************************************************
ManualDividendAdjustment::~ManualDividendAdjustment()
{
    TRACE_DESTRUCTOR(CLASSNAME);
}     

//******************************************************************************
SEVERITY ManualDividendAdjustment::doInit(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

    setFieldSubstituteValues(ifds::TradesTransType, idDataGroup, ifds::ManualTradesTransType);
    setFieldNoValidate(ifds::TradesTransType, TRADETYPE::MANUAL_DIVIDEND_ADJ, idDataGroup, false);
    setFieldNoValidate(ifds::TradeDivType, TRADETYPE::MANUAL_DIVIDEND_ADJ, idDataGroup, false);

    return GETCURRENTHIGHESTSEVERITY();
}



//******************************************************************************
void ManualDividendAdjustment::doInitWithDefaultValues(const BFDataGroupId &idDataGroup)
{
    ManualDividend::doInitWithDefaultValues (idDataGroup);

    DString dstrTradesTransType;
    getField(ifds::TradesTransType,  dstrTradesTransType, idDataGroup);

    setFieldNoValidate(ifds::AmtType, I_("D"), idDataGroup, false);
    setFieldNoValidate(ifds::PendTrdContract, NULL_STRING, idDataGroup, false, true, false, false);
    setFieldNoValidate(ifds::RightToCancel, NULL_STRING, idDataGroup, false, true, false, false);

    //These fields are not required for TRADETYPE::POST_ADJUSTMENT_LIST
    setFieldRequired(ifds::SettleDate, idDataGroup, false);
    setFieldRequired(ifds::SettleCurrency, idDataGroup, false);
    setFieldRequired(ifds::BackDatedReason, idDataGroup, false);
    setFieldRequired(ifds::Accountable, idDataGroup, false);

    //Change the suppress code list.
    setFieldSubstituteValues(ifds::SuppressCode, idDataGroup, ifds::SuppressCode2);
}

//******************************************************************************
SEVERITY ManualDividendAdjustment::doApplyRelatedChanges(const BFFieldId &idField, 
                                                         const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

    ManualDividend::doApplyRelatedChanges (idField, idDataGroup);

    if (idField == ifds::FromFund || 
        idField == ifds::FromClass ||
        idField == ifds::FromFundNumber)
    {
        DString dstrFromFundClassValid;
        getField(ifds::FromFundClassValid, dstrFromFundClassValid, idDataGroup);

        if (dstrFromFundClassValid == YES)
        {
            setDefaultEffectiveDate(idDataGroup);
            setDefaultToFundClass(idDataGroup);
            
            setFieldValid(ifds::NegMoneyMktInt, idDataGroup, false);
            setFieldValid(ifds::EffectiveDate, idDataGroup, false);
        }
    }
    else if (idField == ifds::FromFundClass)
    {
        DString dstrFromFundClassValid;
        getField(ifds::FromFundClassValid, dstrFromFundClassValid, idDataGroup);

        if(dstrFromFundClassValid == YES)
        {
            setDefaultEffectiveDate(idDataGroup);
            setDefaultToFundClass(idDataGroup);

            setFieldValid(ifds::EffectiveDate, idDataGroup, false);
        }
    }
    else if (idField == ifds::ToFund ||
             idField == ifds::ToClass ||
             idField == ifds::ToFundNumber)
    {
        BigDecimal bdReinvestmentRate;
        DString dstrReinvestmentUnitId, dstrToFundClassValid;
        getField(ifds::ToFundClassValid, dstrToFundClassValid, idDataGroup);

        if (dstrToFundClassValid == YES)
        {
            getReinvestmentRate(bdReinvestmentRate, dstrReinvestmentUnitId, idDataGroup);

            setFieldNoValidate(ifds::ReInvUnitId, dstrReinvestmentUnitId, idDataGroup, false, true, true, true);
            setFieldNoValidate(ifds::ReinvestmentRate, bdReinvestmentRate.asDString(SCALE_VALUE), idDataGroup, false, true, true, true);

            setFieldValid(ifds::NegMoneyMktInt, idDataGroup, false);

            DString dstrToFund;
            getField(ifds::ToFund, dstrToFund, idDataGroup);

            if (dstrToFund == CASH)
            {
                // In order to revalidate AV Rate From Fund/Class.
                setFieldValid(ifds::EffectiveDate, idDataGroup, false);

                updateReinvestmentRateForCash(idDataGroup);
            }
        }
    }
    else if (idField == ifds::EffectiveDate)
    {
        updateRates(idDataGroup);
    }
    else if (idField == ifds::DivRate)
    {
        DString newNumUnitEligDividends = calculateNumUnitEligDividendsFromAmount(idDataGroup).asDString(SCALE_VALUE);
        setFieldNoValidate(ifds::NumUnitEligDividends, getRoundedValue(PRECISION::NUM_UNIT_ELIG_DIV, newNumUnitEligDividends, idDataGroup), idDataGroup, true, true, true, false);
    }
    else if (idField == ifds::ReinvestmentRate)
    {
        DString newNumUnitDividends = calculateNumUnitDividendsFromAmount(idDataGroup).asDString(SCALE_VALUE);
        setFieldNoValidate(ifds::NumUnitDividends, getRoundedValue(PRECISION::NUM_UNIT_DIV, newNumUnitDividends, idDataGroup), idDataGroup, true, true, true, false); 
    }
    else if (idField == ifds::Amount)
    {
        //Round amount itself - To see this new value, gui will update control when lost of focus.
        DString dstrAmount;
        getField(ifds::Amount, dstrAmount, idDataGroup);
        setFieldNoValidate(ifds::Amount, getRoundedValue(PRECISION::AMOUNT, dstrAmount, idDataGroup), idDataGroup, false, true, true, false);

        //Update investment & reinvestment units.
        DString newNumUnitEligDividends = calculateNumUnitEligDividendsFromAmount(idDataGroup).asDString(SCALE_VALUE);
        DString newNumUnitDividends = calculateNumUnitDividendsFromAmount(idDataGroup).asDString(SCALE_VALUE);

        setFieldNoValidate(ifds::NumUnitEligDividends,  getRoundedValue(PRECISION::NUM_UNIT_ELIG_DIV, newNumUnitEligDividends, idDataGroup), idDataGroup, true, true, true, false);
        setFieldNoValidate(ifds::NumUnitDividends,      getRoundedValue(PRECISION::NUM_UNIT_DIV,      newNumUnitDividends,     idDataGroup), idDataGroup, true, false, true, false);
    }
    else if (idField == ifds::NumUnitEligDividends)
    {
        //Round unit itself - To see this new value, gui will update control when lost of focus.
        DString dstrNumUnitEligDividends;
        getField(ifds::NumUnitEligDividends, dstrNumUnitEligDividends, idDataGroup);
        setFieldNoValidate(ifds::NumUnitEligDividends, getRoundedValue(PRECISION::NUM_UNIT_ELIG_DIV, dstrNumUnitEligDividends, idDataGroup), idDataGroup, true, true, true, false);

        //1. update amount first
        DString newAmount = calculateAmount(CALCULATEFROM::NUM_UNIT_ELIG_DIV, idDataGroup).asDString(SCALE_VALUE);
        setFieldNoValidate(ifds::Amount, getRoundedValue(PRECISION::AMOUNT, newAmount, idDataGroup), idDataGroup, false, true, true, false);

        //2. update reinvestment unit
        DString newNumUnitDividends = calculateNumUnitDividendsFromAmount(idDataGroup).asDString(SCALE_VALUE);
        setFieldNoValidate(ifds::NumUnitDividends, getRoundedValue(PRECISION::NUM_UNIT_DIV, newNumUnitDividends, idDataGroup), idDataGroup, true, true, true, false);

        //3. update itself with the new amount value (if rounded).
        DString newNumUnitEligDividends = calculateNumUnitEligDividendsFromAmount(idDataGroup).asDString(SCALE_VALUE);
        setFieldNoValidate(ifds::NumUnitEligDividends, getRoundedValue(PRECISION::NUM_UNIT_ELIG_DIV, newNumUnitEligDividends, idDataGroup), idDataGroup, true, true, true, false);
    }
    else if (idField == ifds::NumUnitDividends)
    {
        //Round unit itself - To see this new value, gui will update control when lost of focus.
        DString dstrNumUnitDividends;
        getField(ifds::NumUnitDividends, dstrNumUnitDividends, idDataGroup);
        setFieldNoValidate(ifds::NumUnitDividends, getRoundedValue(PRECISION::NUM_UNIT_DIV, dstrNumUnitDividends, idDataGroup), idDataGroup, true, true, true, false);

        //1. update amount first
        DString newAmount = calculateAmount(CALCULATEFROM::NUM_UNIT_DIV, idDataGroup).asDString(SCALE_VALUE);
        setFieldNoValidate(ifds::Amount, getRoundedValue(PRECISION::AMOUNT, newAmount, idDataGroup), idDataGroup, false, true, true, false);

        //2. update investment unit
        DString newNumUnitEligDividends = calculateNumUnitEligDividendsFromAmount(idDataGroup).asDString(SCALE_VALUE);
        setFieldNoValidate(ifds::NumUnitEligDividends, getRoundedValue(PRECISION::NUM_UNIT_ELIG_DIV, newNumUnitEligDividends, idDataGroup), idDataGroup, true, true, true, false);

        //3. update itself with the new amount value (if rounded).
        DString newNumUnitDividends = calculateNumUnitDividendsFromAmount(idDataGroup).asDString(SCALE_VALUE);
        setFieldNoValidate(ifds::NumUnitDividends, getRoundedValue(PRECISION::NUM_UNIT_DIV, newNumUnitDividends, idDataGroup), idDataGroup, true, false, true, false);
    }
    else if (idField == ifds::RoundCalcToCents)
    {
        DString dstrAmount;
        getField(ifds::Amount, dstrAmount, idDataGroup);

        setFieldNoValidate(ifds::Amount, getRoundedValue(PRECISION::AMOUNT, dstrAmount, idDataGroup), idDataGroup, false, true, true, true);
    }
    else if (idField == ifds::ESGSettle)
    {
        setFieldValid(ifds::AddrCode, idDataGroup, false);
    }
    else if (idField == ifds::NegMoneyMktInt)
    {
        setFieldValid(ifds::NumUnitDividends, idDataGroup, false);
    }
    else if (idField == ifds::TradesPayType)
    {
        DString toFund, payType;

        getField (ifds::ToFund, toFund, idDataGroup, false);
        getField (ifds::TradesPayType, payType, idDataGroup, false);

        bool bIsToFundCash = toFund.stripAll().upperCase() == CASH;
        bool bUpdateESGSettle = payType == I_("S") && bIsToFundCash && isCASHSettleESGElig(idDataGroup);

        setFieldReadOnly (ifds::ESGSettle, idDataGroup, !bUpdateESGSettle);
        setFieldNoValidate(ifds::ESGSettle, bUpdateESGSettle ? NSM_SETTLE::INCLUDE : NULL_STRING, idDataGroup, true, false, true);
        setFieldValid (ifds::ESGSettle, idDataGroup, false );
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ManualDividendAdjustment::updateRates(const BFDataGroupId &idDataGroup)
{
    BigDecimal bdDivRate, bdReinvestmentRate;
    DString dstrDivUnitId, dstrReinvestmentUnitId;

    getDivRate(bdDivRate, dstrDivUnitId, idDataGroup);
    getReinvestmentRate(bdReinvestmentRate, dstrReinvestmentUnitId, idDataGroup);

    setFieldNoValidate(ifds::DivUnitId, dstrDivUnitId, idDataGroup, false, true, true, true);
    setFieldNoValidate(ifds::ReInvUnitId, dstrReinvestmentUnitId, idDataGroup, false, true, true, true);

    setFieldNoValidate(ifds::DivRate, bdDivRate.asDString(SCALE_VALUE), idDataGroup, false, true, true, true);
    setFieldNoValidate(ifds::ReinvestmentRate, bdReinvestmentRate.asDString(SCALE_VALUE), idDataGroup, false, true, true, true);

    updateReinvestmentRateForCash(idDataGroup);
}

//******************************************************************************
void ManualDividendAdjustment::updateReinvestmentRateForCash(const BFDataGroupId &idDataGroup)
{
    // If ToFund is CASH, assign AV rate from FromFund/FromClass.
    DString dstrFromFundClassValid, dstrToFund, dstrReinvestmentUnitId;
    BigDecimal bdReinvestmentRate;

    getField(ifds::FromFundClassValid, dstrFromFundClassValid, idDataGroup);
    getField(ifds::ToFund, dstrToFund, idDataGroup);

    if (dstrToFund == CASH && dstrFromFundClassValid == YES)
    {
        getAVRateFromFundFromClass(bdReinvestmentRate, dstrReinvestmentUnitId, idDataGroup);
        
        setFieldNoValidate(ifds::ReInvUnitId, dstrReinvestmentUnitId, idDataGroup, false, true, true, true);
        setFieldNoValidate(ifds::ReinvestmentRate, bdReinvestmentRate.asDString(SCALE_VALUE), idDataGroup, false, true, true, true);
    }
}

//******************************************************************************
void ManualDividendAdjustment::setDefaultToFundClass(const BFDataGroupId &idDataGroup)
{

}

//******************************************************************************
void ManualDividendAdjustment::setDefaultEffectiveDate(const BFDataGroupId &idDataGroup)
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
SEVERITY ManualDividendAdjustment::doValidateField(const BFFieldId &idField, 
                                                   const DString &strValue, 
                                                   const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

    if (idField == ifds::Amount || idField == ifds::AcctableTradeDate)
    {
    }
    else if (idField == ifds::FromFund)
    {
        validateFundCategory(strValue, idDataGroup);
        ManualDividend::doValidateField(idField, strValue, idDataGroup);
    }
    else if (idField == ifds::ToFund)
    {
        validateFundCategory(strValue, idDataGroup);
        ManualDividend::doValidateField(idField, strValue, idDataGroup);
    }
    else if (idField == ifds::FromFundClass || idField == ifds::FromFundNumber) // cross edit for FromFund/FromClass which is validated by validateFundClass(..)
    {
        if (idField == ifds::FromFundNumber)
        {
            ManualDividend::doValidateField(idField, strValue, idDataGroup);
        }

        DString dstrFromFund, dstrFromClass, dstrAccountNum;
        getField(ifds::FromFund, dstrFromFund, idDataGroup);
        getField(ifds::FromClass, dstrFromClass, idDataGroup);
        getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
        dstrAccountNum.stripLeading ('0').strip();

        setFieldNoValidate(ifds::FromFundClassValid, validateFundClass(dstrFromFund, dstrFromClass, dstrAccountNum, idDataGroup) <= WARNING ? YES:NO, idDataGroup, false, true);
        setFieldValid(ifds::NegMoneyMktInt, idDataGroup, false);
    }
    else if (idField == ifds::ToFundClass || idField == ifds::ToFundNumber) // cross edit for ToFund/ToClass which is validated by validateToFundClass(..)
    {
        if (idField == ifds::ToFundNumber)
        {
            ManualDividend::doValidateField(idField, strValue, idDataGroup);
        }

        DString dstrToFund, dstrToClass, dstrAccountNum;
        getField(ifds::ToFund, dstrToFund, idDataGroup);
        getField(ifds::ToClass, dstrToClass, idDataGroup);
        getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
        dstrAccountNum.stripLeading ('0').strip();

        setFieldNoValidate(ifds::ToFundClassValid, validateToFundClass(dstrToFund, dstrToClass, dstrAccountNum, idDataGroup) <= WARNING ? YES:NO, idDataGroup, false, true);
    }
    else if (idField == ifds::NegMoneyMktInt)
    {
        validateNegMoneyMktInt(strValue, idDataGroup);
        setFieldValid(ifds::NumUnitDividends, idDataGroup, false);
    }
    else if (idField == ifds::EffectiveDate)
    {
        ManualDividend::doValidateField(idField, strValue, idDataGroup);

        validateEffectiveDateAgainstIDRecord(idDataGroup);
        updateRates(idDataGroup);
    }
    else if (idField == ifds::AddrCode)
    {
        validateAddrCode(idDataGroup);        
    }
    else if (idField == ifds::NumUnitDividends)
    {
        // For Neg Money Mkt = yes. (Interest accrual Fund)
        validateAcctBalanceForNegMoneyMkt(idDataGroup);
    }
    else
    {
        ManualDividend::doValidateField(idField, strValue, idDataGroup);
    }

    return GETCURRENTHIGHESTSEVERITY ();
}



//******************************************************************************
SEVERITY ManualDividendAdjustment::validateEffectiveDateAgainstIDRecord(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEffectiveDateAgainstIDRecords"))

    DString dstrFromFund, dstrFromClass, dstrToFund, dstrToClass;
    DString dstrFromFundClassValid, dstrToFundClassValid, dstrTradeDivType;

    getField(ifds::FromFund, dstrFromFund, idDataGroup);
    getField(ifds::FromClass, dstrFromClass, idDataGroup);
    getField(ifds::ToFund, dstrToFund, idDataGroup);
    getField(ifds::ToClass, dstrToClass, idDataGroup);
    getField(ifds::FromFundClassValid, dstrFromFundClassValid, idDataGroup);
    getField(ifds::ToFundClassValid, dstrToFundClassValid, idDataGroup);
    getField(ifds::TradeDivType, dstrTradeDivType, idDataGroup, true);

    if (dstrFromFundClassValid == YES && isDivRateRequired())
    {
        BigDecimal bdDivRate;
        DString dstrUnitId;

        getDivRate(bdDivRate, dstrUnitId, idDataGroup);

        if (bdDivRate == 0)
        {
            DString strIDI;

            addIDITagValue(strIDI, I_("DIVTYPE"), dstrTradeDivType);
            ADDCONDITIONFROMFILEIDI(CND::ERR_NO_DIVTYPE_UNIT_RATE_EXISTS_FOR_THIS_DATE, strIDI);
        }
    }

    DString dstrEffectiveDateFormat;
    getField(ifds::EffectiveDate, dstrEffectiveDateFormat, idDataGroup, true);

    if (dstrToFundClassValid == YES)
    {
        BigDecimal bdReinvestmentRate;
        DString dstrUnitId;

        getReinvestmentRate(bdReinvestmentRate, dstrUnitId, idDataGroup);

        if (bdReinvestmentRate == 0 && dstrToFund != CASH && !dstrToFund.empty() && isReinvestmentRateRequired())
        {
            DString strIDI;

            addIDITagValue(strIDI, I_("FUNDFROM"), dstrToFund); //Show to Fund
            addIDITagValue(strIDI, I_("DEFF"), dstrEffectiveDateFormat);
            ADDCONDITIONFROMFILEIDI(CND::ERR_AV_UNIT_RATE_DOES_NOT_EXIST_FOR_FUND_ON_DEFF, strIDI);
        }
    } 

    if (dstrToFund == CASH)
    {
        DString dstrUnitId;
        BigDecimal bdAVRateFromFundFromClass;

        getAVRateFromFundFromClass(bdAVRateFromFundFromClass, dstrUnitId, idDataGroup);

        if (bdAVRateFromFundFromClass == 0)
        {
            DString strIDI;

            addIDITagValue(strIDI, I_("FUNDFROM"), dstrFromFund); // Show from fund.
            addIDITagValue(strIDI, I_("DEFF"), dstrEffectiveDateFormat);
            ADDCONDITIONFROMFILEIDI(CND::ERR_AV_UNIT_RATE_DOES_NOT_EXIST_FOR_FUND_ON_DEFF, strIDI);
        }
    }

    return GETCURRENTHIGHESTSEVERITY ();
}



//****************************************************************************** 
SEVERITY ManualDividendAdjustment::validateAcctBalanceForNegMoneyMkt(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"))

    // For Neg Money Mkt = yes. (Interest accrual Fund)
    DString dstrNegMoneyMkt, dstrNumUnitDividends, dstrAccountNum, dstrFromFund, dstrFromClass, 
            dstrEffectiveDate, dstrEffectiveDateFormat;
    BigDecimal dNumUnitDividends;
    MFAccountHoldingList *pMFAccountHoldingList = NULL;

    getField(ifds::NegMoneyMktInt, dstrNegMoneyMkt, idDataGroup);
    getField(ifds::NumUnitDividends, dstrNumUnitDividends, idDataGroup);
    getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
    getField(ifds::FromFund, dstrFromFund, idDataGroup);
    getField(ifds::FromClass, dstrFromClass, idDataGroup);
    getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
    getField(ifds::EffectiveDate, dstrEffectiveDateFormat, idDataGroup, true);

    dNumUnitDividends =  DSTCommonFunctions::convertToBigDecimal(dstrNumUnitDividends);
    
    if (validateNegMoneyMktInt(dstrNegMoneyMkt, idDataGroup, false) <= WARNING &&//isFieldValid(ifds::NegMoneyMktInt, idDataGroup) &&
        dstrNegMoneyMkt == YES &&
        dNumUnitDividends < 0 &&
        getMFAccountHoldingList(dstrAccountNum, dstrFromFund, dstrFromClass, dstrEffectiveDate, I_("ExPur"), pMFAccountHoldingList, idDataGroup) <= WARNING &&
        pMFAccountHoldingList)
    {
        DString dstrAccBalUnits;
        BigDecimal dAccBalUnits;

        pMFAccountHoldingList->getField(ifds::AccBalUnits, dstrAccBalUnits, idDataGroup);
        dAccBalUnits = DSTCommonFunctions::convertToBigDecimal(dstrAccBalUnits);

        if (dNumUnitDividends.abs() > dAccBalUnits)
        {
            DString strIDI;
            addIDITagValue(strIDI, I_("UNITS"), dstrNumUnitDividends);
            addIDITagValue(strIDI, I_("ACCTUNITS"), dstrAccBalUnits);
            addIDITagValue(strIDI, I_("DEFFDATE"), dstrEffectiveDateFormat);

            ADDCONDITIONFROMFILEIDI(CND::ERR_INSUFFICIENT_BALANCE_FOR_NEG_MONEY_MKT, strIDI);
        }
    }

    return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY ManualDividendAdjustment::validateFundClass(const DString &fundCode, 
                                                     const DString &classCode, 
                                                     const DString &accountNum, 
                                                     const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"))

    if (!fundCode.empty() && !classCode.empty())
    {
        /*validateEUSDBackdates(fundCode,
                              classCode,
                              accountNum,
                              idDataGroup); */

        validateAccountHolding(fundCode, classCode, idDataGroup);
    }

    return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY ManualDividendAdjustment::validateAccountHolding(const DString &fundCode, const DString &classCode, const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAccountHolding"))

    MFAccountHoldingList *pMFAccountHoldingList = NULL;

    if (!fundCode.empty() && !classCode.empty() &&
        getAccountHoldings(pMFAccountHoldingList, idDataGroup) <= WARNING && pMFAccountHoldingList)
    {
        if (pMFAccountHoldingList->isFundInHoldings(fundCode, classCode,  idDataGroup))
        {
            /*DString tradeDate;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
            double dUnitPrice = getUnitPrice ( fundCode, 
            classCode, 
            tradeDate, 
            tradeDate, 
            idDataGroup,
            I_(""),   //  transType
            I_("N"),  //  PrevDatePressed
            I_("N")); //  NextDatePresed

            if (dUnitPrice == 0.0)
            {
            // Unit price is not available for this fund.
            ADDCONDITIONFROMFILE (CND::ERR_FUND_UNIT_PRICE_NOT_AVAILABLE);
            }*/
        }
        else
        {
            // Account has no holdings for this fund.
            ADDCONDITIONFROMFILE (CND::ERR_ACCT_NO_HOLDINGS_FOR_FUND); 
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ManualDividendAdjustment::validateToFundClass(const DString &toFund, 
                                                       const DString &toClass, 
                                                       const DString &accountNum, 
                                                       const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateToFundClass"));

    FundDetail *pToFundDetail = NULL;

    if (!toFund.empty() &&
        getWorkSession().getFundDetail(toFund, toClass, idDataGroup, pToFundDetail) && pToFundDetail)
    {
        DString dstrToFundCurrency;
        pToFundDetail->getField(ifds::Currency, dstrToFundCurrency, idDataGroup);

        validateCurrencyTaxType(accountNum, dstrToFundCurrency, idDataGroup);
    }

    validateMasterActAMS(idDataGroup);
    validateToFundClassAgainstFundEligible(toFund, toClass, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ManualDividendAdjustment::validateCurrencyTaxType(const DString &accountNum_, 
                                                           const DString &currency_, 
                                                           const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
        CLASSNAME, 
        I_ ("validateCurrencyTaxType"));

    DString currChkByTaxType;

    getWorkSession ().getOption ( ifds::CurrChkByTaxType, 
        currChkByTaxType, 
        BF::HOST, 
        false);
    currChkByTaxType.strip().upperCase();
    if (currChkByTaxType == Y)
    {
        DString accountNum (accountNum_),
            currency (currency_);

        accountNum.strip ().stripLeading ('0');
        MFAccount *pMFAccount = NULL;
        if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
            pMFAccount
            )
        {
            DString taxType,
                invalidCurr,
                taxTypeByCurrChk;

            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
            getWorkSession().getOption ( ifds::TaxTypeByCurrChk,
                taxTypeByCurrChk,
                BF::HOST,
                false);
            getWorkSession().getOption ( ifds::InvalidCurr,
                invalidCurr,
                BF::HOST,
                false);

            TaxTypeRule *pTaxTypeRule = NULL;
            
            if (pMFAccount->getTaxTypeRule(pTaxTypeRule, idDataGroup) <= WARNING && pTaxTypeRule &&
                DSTCommonFunctions::codeInList (taxType, taxTypeByCurrChk) &&
                DSTCommonFunctions::codeInList (currency, invalidCurr))
            {
                DString dstrSelfDirected;
                pTaxTypeRule->getField(ifds::SelfDirected, dstrSelfDirected, idDataGroup);

                if (dstrSelfDirected.stripAll().upperCase() == NO)
                {
                    DString strIDI, dstrTaxTypeFormat;
                    pMFAccount->getField(ifds::TaxType, dstrTaxTypeFormat, idDataGroup, true);

                    addIDITagValue(strIDI, I_("TAXTYPE"), dstrTaxTypeFormat);
                    addIDITagValue(strIDI, I_("FUNDCURRENCY"), currency);
                    ADDCONDITIONFROMFILEIDI(CND::ERR_TAX_TYPE_IS_NOT_ALLOWED_TO_TRADE_IN_FUND_CURRENCY, strIDI);
                }
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualDividendAdjustment::validateFromToFundClass(const DString &fromFund,
                                                           const DString &fromClass,
                                                           const DString &toFund,
                                                           const DString &toClass,
                                                           const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFromToFundClass"));

    //ManualDividend::validateFromToFundClass(fromFund, fromClass, toFund, toClass, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//**** Returned value is not rounded yet. **************************************************************************
BigDecimal ManualDividendAdjustment::calculateAmount(const DString &calculateFrom, const BFDataGroupId &idDataGroup)
{
    BigDecimal bdAmount(0);

    if (calculateFrom == CALCULATEFROM::NUM_UNIT_ELIG_DIV)
    {
        DString dstrDivRate, dstrNumUnitEligDividends;
        BigDecimal bdDivRate, dNumUnitEligDividends;

        getField(ifds::DivRate, dstrDivRate, idDataGroup, false);
        getField(ifds::NumUnitEligDividends, dstrNumUnitEligDividends, idDataGroup, false);

        bdDivRate = DSTCommonFunctions::convertToBigDecimal(dstrDivRate);
        dNumUnitEligDividends = DSTCommonFunctions::convertToBigDecimal(dstrNumUnitEligDividends);
        
        bdAmount = dNumUnitEligDividends * bdDivRate;
    }
    else if (calculateFrom == CALCULATEFROM::NUM_UNIT_DIV)
    {
        DString dstrReinvestmentRate, dstrNumUnitDividends;
        BigDecimal bdReinvestmentRate, dNumUnitDividends;

        getField(ifds::ReinvestmentRate, dstrReinvestmentRate, idDataGroup, false);
        getField(ifds::NumUnitDividends, dstrNumUnitDividends, idDataGroup, false);

        bdReinvestmentRate = DSTCommonFunctions::convertToBigDecimal(dstrReinvestmentRate);
        dNumUnitDividends = DSTCommonFunctions::convertToBigDecimal(dstrNumUnitDividends);
        
        bdAmount = dNumUnitDividends * bdReinvestmentRate;
    }

    return bdAmount;
}

//****** Returned value is not rounded yet. ************************************************************************
BigDecimal ManualDividendAdjustment::calculateNumUnitEligDividendsFromAmount(const BFDataGroupId &idDataGroup)
{
    BigDecimal dNumUnitEligDividends(0);
    BigDecimal bdDivRate, bdAmount;
    DString dstrDivRate, dstrAmount;

    //ifds::Amount must be updated first before calling this.
    
    getField(ifds::DivRate, dstrDivRate, idDataGroup, false);
    getField(ifds::Amount, dstrAmount, idDataGroup, false);

    bdDivRate = DSTCommonFunctions::convertToBigDecimal(dstrDivRate);
    bdAmount = DSTCommonFunctions::convertToBigDecimal(dstrAmount);

    dNumUnitEligDividends = (bdDivRate != 0) ? (bdAmount / bdDivRate):0;

    return dNumUnitEligDividends;
}

//***** Returned value is not rounded yet. *************************************************************************
BigDecimal ManualDividendAdjustment::calculateNumUnitDividendsFromAmount(const BFDataGroupId &idDataGroup)
{
    DString dstrToFund;
    BigDecimal dNumUnitDividends(0);

    getField(ifds::ToFund, dstrToFund, idDataGroup);

    if (dstrToFund != CASH)
    {
        //ifds::Amount must be updated first before calling this.

        BigDecimal bdReinvestmentRate, bdAmount;
        DString dstrReinvestmentRate, dstrAmount;

        getField(ifds::ReinvestmentRate, dstrReinvestmentRate, idDataGroup, false);
        getField(ifds::Amount, dstrAmount, idDataGroup, false);

        bdReinvestmentRate = DSTCommonFunctions::convertToBigDecimal(dstrReinvestmentRate);
        bdAmount = DSTCommonFunctions::convertToBigDecimal(dstrAmount);

        dNumUnitDividends = (bdReinvestmentRate != 0) ? (bdAmount / bdReinvestmentRate):0;
    }

    return dNumUnitDividends;
}

//***** (From Fund/Class) *************************************************************************
void ManualDividendAdjustment::getDivRate(BigDecimal &bdDivRate, DString &strUnitId, const BFDataGroupId &idDataGroup, const DString &getTransType, const DString &getNextAvailRate)
{
    DString dstrTradeDate, dstrFromFund, dstrFromClass, dstrUnitId, dstrTradeDivType;
    BigDecimal dTmp;

    getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup);
    getField(ifds::FromFund, dstrFromFund, idDataGroup);
    getField(ifds::FromClass, dstrFromClass, idDataGroup);
    getField(ifds::TradeDivType, dstrTradeDivType, idDataGroup, true);

    if (!dstrFromFund.empty() && !dstrFromClass.empty())
    {
        getUnitPriceDetl(bdDivRate, 
                         dTmp,
                         dTmp,
                         strUnitId,
                         dstrFromFund, 
                         dstrFromClass, 
                         dstrTradeDate, 
                         dstrTradeDate, 
                         idDataGroup,
                         dstrTradeDivType,   
                         NO,  
                         NO,
                         getTransType,
                         getNextAvailRate);
    }
}

//***** (To Fund/Class) *************************************************************************
void ManualDividendAdjustment::getReinvestmentRate(BigDecimal &bdReinvestmentRate, DString &strUnitId, const BFDataGroupId &idDataGroup)
{
    DString dstrToFund, dstrToClass, dstrTradeDate;
    
    getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup);
    getField(ifds::ToFund, dstrToFund, idDataGroup);
    getField(ifds::ToClass, dstrToClass, idDataGroup);

    getAVRate(dstrToFund, dstrToClass, dstrTradeDate, bdReinvestmentRate, strUnitId, idDataGroup);
}

//***** (AV - From Fund/Class) *************************************************************************
void ManualDividendAdjustment::getAVRateFromFundFromClass(BigDecimal &dAVRate, DString &strUnitId, const BFDataGroupId &idDataGroup)
{
    DString dstrTradeDate, dstrFromFund, dstrFromClass, dstrUnitId;

    getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup);
    getField(ifds::FromFund, dstrFromFund, idDataGroup);
    getField(ifds::FromClass, dstrFromClass, idDataGroup);

    getAVRate(dstrFromFund, dstrFromClass, dstrTradeDate, dAVRate, strUnitId, idDataGroup);
}

//******************************************************************************
void ManualDividendAdjustment::getAVRate(const DString &dstrFund,
                                         const DString &dstrClass, 
                                         const DString &dstrTradeDate, 
                                         BigDecimal &dAVRate, 
                                         DString &strUnitId,
                                         const BFDataGroupId &idDataGroup)
{
    BigDecimal dEX_UnitValue, dEX_GAVRate, dEX_MultiPriceUsageID;
    BigDecimal dAV_UnitValue, dAV_GAVRate, dAV_MultiPriceUsageID;

    dAVRate = 0;
    strUnitId = NULL_STRING;

    if (dstrFund != CASH && !dstrFund.empty() && !dstrClass.empty())
    {
        FundDetailList *pFundDetailList = NULL;
        FundDetail *pFundDetail = NULL;
        DString dstrGAVApply, dstrMultiPrices, dstrUnitId;

        getWorkSession().getOption(ifds::MultiPrices, dstrMultiPrices, idDataGroup, false);

        if (getWorkSession().getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList &&
            pFundDetailList->getFundDetail(dstrFund, dstrClass, idDataGroup, pFundDetail) && pFundDetail)
        {
            pFundDetail->getField(ifds::GAVApply, dstrGAVApply, idDataGroup);
        }

        // #1. Find EX value first
        getUnitPriceDetl(dEX_UnitValue, 
                         dEX_GAVRate,
                         dEX_MultiPriceUsageID,
                         strUnitId,
                         dstrFund, 
                         dstrClass, 
                         dstrTradeDate, 
                         dstrTradeDate, 
                         idDataGroup,
                         EX_TYPE,   
                         NO,  
                         NO);

        // EX rate exists.
        if (dEX_UnitValue > 0)
        {
            dAVRate = (dstrMultiPrices == YES && dEX_MultiPriceUsageID > 0) ? dEX_MultiPriceUsageID:dEX_UnitValue;

            //If GAV is applied and has value, use this rate instead.
            dAVRate = (dstrGAVApply != I_("01") && dEX_GAVRate > 0) ? dEX_GAVRate:dAVRate;
        }  


        // #2. In case of no EX value, find AV rate instead.
        if ( !(dEX_UnitValue > 0) )
        {
            getUnitPriceDetl(dAV_UnitValue, 
                             dAV_GAVRate,
                             dAV_MultiPriceUsageID,
                             strUnitId,
                             dstrFund, 
                             dstrClass, 
                             dstrTradeDate, 
                             dstrTradeDate, 
                             idDataGroup,
                             AV_TYPE,   
                             NO,  
                             NO);

            // AV rate exists.
            if (dAV_UnitValue > 0)
            {
                dAVRate = (dstrMultiPrices == YES && dAV_MultiPriceUsageID > 0) ? dAV_MultiPriceUsageID:dAV_UnitValue;

                //If GAV is applied and has value, use this rate instead.
                dAVRate = (dstrGAVApply != I_("01") && dAV_GAVRate > 0) ? dAV_GAVRate:dAVRate;
            }  
        }
    }
}


//******************************************************************************
DString ManualDividendAdjustment::getRoundedValue(const DString &precisionField, const DString &value, const BFDataGroupId &idDataGroup)
{
    DString dstrValue = value;
    int precision = 0;

    if (precisionField == PRECISION::AMOUNT)
    {
        precision = isRoundCalToCents(idDataGroup) ? 2:4;
        DSTCommonFunctions::formattedField(ifds::USDollar, precision, dstrValue);
    }
    else if (precisionField == PRECISION::NUM_UNIT_ELIG_DIV)
    {
        FundDetail *pFromFundDetail = NULL;
        DString dstrFromFund, dstrFromClass, dstrUnitsPrecision;

        getField(ifds::FromFund, dstrFromFund, idDataGroup);
        getField(ifds::FromClass, dstrFromClass, idDataGroup);

        if (getWorkSession().getFundDetail(dstrFromFund, dstrFromClass, idDataGroup, pFromFundDetail) && pFromFundDetail)
        {
            pFromFundDetail->getField(ifds::UnitsPrecision, dstrUnitsPrecision, idDataGroup);
            precision = dstrUnitsPrecision.asInteger();
        }

        DSTCommonFunctions::formattedField(ifds::USDollar, precision, dstrValue);
    }
    else if (precisionField == PRECISION::NUM_UNIT_DIV)
    {
        FundDetail *pToFundDetail = NULL;
        DString dstrToFund, dstrToClass, dstrUnitsPrecision, dstrRoundFlag;
        
        getField(ifds::ToFund, dstrToFund, idDataGroup);
        getField(ifds::ToClass, dstrToClass, idDataGroup);

        if (getWorkSession().getFundDetail(dstrToFund, dstrToClass, idDataGroup, pToFundDetail) && pToFundDetail)
        {
            pToFundDetail->getField(ifds::UnitsPrecision, dstrUnitsPrecision, idDataGroup);
            pToFundDetail->getField(ifds::RoundFlag, dstrRoundFlag, idDataGroup);

            dstrRoundFlag.stripAll().upperCase();

            
            if (dstrRoundFlag == I_("U") || dstrRoundFlag == I_("D"))
            {
                BigDecimal unroundedValue, truncatedValue;
                precision = dstrUnitsPrecision.asInteger();
                
                unroundedValue = DSTCommonFunctions::convertToBigDecimal(dstrValue);
                truncatedValue = DSTCommonFunctions::convertToBigDecimal(dstrValue.left(dstrValue.find_first_of('.') + precision + 1));

                if (dstrRoundFlag == I_("U"))
                {
                    if (unroundedValue.abs() > truncatedValue.abs())
                    {
                        BigDecimal bdAdjustmentValue(1);

                        for (int i = 0; i < precision; i++)
                            bdAdjustmentValue = bdAdjustmentValue / 10;

                        if (unroundedValue < 0)
                        {
                            truncatedValue = truncatedValue + (bdAdjustmentValue * -1);
                        }
                        else
                        {
                            truncatedValue = truncatedValue + (bdAdjustmentValue * 1);
                        }

                        dstrValue = truncatedValue.asDString(SCALE_VALUE);
                    }
                    else
                    {
                        dstrValue = truncatedValue.asDString(SCALE_VALUE);
                    }
                }
                else if (dstrRoundFlag == I_("D"))
                {
                    dstrValue = truncatedValue.asDString(SCALE_VALUE);
                }
            }
            else
            {
                precision = dstrUnitsPrecision.asInteger();
                DSTCommonFunctions::formattedField(ifds::USDollar, precision, dstrValue);
            }
        }
    }
    else
        return NULL_STRING;
    
    return dstrValue;
}

//******************************************************************************
bool ManualDividendAdjustment::isRoundCalToCents(const BFDataGroupId &idDataGroup)
{
    DString dstrRoundCalcToCents;
    getField(ifds::RoundCalcToCents, dstrRoundCalcToCents, idDataGroup, false);

    return dstrRoundCalcToCents.stripAll().upperCase() == YES;
}

//******************************************************************************
SEVERITY ManualDividendAdjustment::validateNegMoneyMktInt(const DString &strValue, const BFDataGroupId &idDataGroup, const bool &addConditions)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,  CLASSNAME, I_("validateNegMoneyMktInt"));

    FundMasterList *pFundMasterList = NULL;
    FundMaster *pFundMaster = NULL;
    DString dstrTradesTransType, dstrToFund, dstrToClass, dstrFromFund, dstrFromClass;

    getField(ifds::FromFund, dstrFromFund, idDataGroup);
    getField(ifds::ToFund, dstrToFund, idDataGroup);
    getField(ifds::FromClass, dstrFromClass, idDataGroup);
    getField(ifds::ToClass, dstrToClass, idDataGroup);
    getField(ifds::TradesTransType, dstrTradesTransType, idDataGroup);

    if (strValue == YES &&
        getMgmtCo().getFundMasterList(pFundMasterList) <= WARNING && pFundMasterList &&
        pFundMasterList->getFundMaster(dstrFromFund, idDataGroup, pFundMaster) && pFundMaster)
    {
        DString dstrPayIntOn, dstrIntToDateType, dstrIntFromDateType, dstrFundType;
        pFundMaster->getField(ifds::FundType, dstrFundType, idDataGroup);
        pFundMaster->getField(ifds::IntToDateType, dstrIntToDateType, idDataGroup);
        pFundMaster->getField(ifds::IntFromDateType, dstrIntFromDateType, idDataGroup);
        pFundMaster->getField(ifds::PayIntOn, dstrPayIntOn, idDataGroup);

        if (dstrFromFund != dstrToFund || dstrFromClass != dstrToClass)
        {
            if (addConditions)
            {
                ADDCONDITIONFROMFILE(CND::ERR_NEG_MM_CAN_BE_REINVESTED_ONLY_SAME_FUNDCLASS);
            }
            else
            {
                return SEVERE_ERROR;
            }
        }
        else if (dstrTradesTransType != TRADETYPE::MANUAL_DIVIDEND_ADJ ||
                 dstrFundType.stripAll().upperCase() != I_("I") ||
                 dstrPayIntOn.stripAll().upperCase() != I_("01") ||
                 dstrIntToDateType.stripAll().upperCase() == I_("C") ||
                 dstrIntFromDateType.stripAll().upperCase() == I_("C")) 
        {
            if (addConditions)
            {
                ADDCONDITIONFROMFILE(CND::ERR_NEG_MONEY_MARKET_INTEREST_NOT_APPLICABLE_FOR_THIS_FUND);
            }
            else
            {
                return SEVERE_ERROR;
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ManualDividendAdjustment::isDivRateRequired()
{
    return true;
}

//******************************************************************************
bool ManualDividendAdjustment::isReinvestmentRateRequired()
{
    return true;
}

//****************************************************************************** 
SEVERITY ManualDividendAdjustment::validateESGSettle (const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateESGSettle")); 


   return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************** 
SEVERITY ManualDividendAdjustment::validateFundCategory(const DString &fundCode, const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundCategory")); 

    FundMasterList *pFundMasterList = NULL;
    FundMaster *pFundMaster = NULL;
    DString dstrFundCategory;

    if (!fundCode.empty() && 
        getMgmtCo().getFundMasterList(pFundMasterList) <= WARNING && pFundMasterList &&
        pFundMasterList->getFundMaster(fundCode, idDataGroup, pFundMaster) && pFundMaster)
    {
        pFundMaster->getField(ifds::FundCategory, dstrFundCategory, idDataGroup);

        if (dstrFundCategory.stripAll().upperCase() == GI_FUND)
        {
            ADDCONDITIONFROMFILE(CND::ERR_GI_FUND_IS_NOT_ALLOWED);
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY ManualDividendAdjustment::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll")); 

    ManualDividend::doValidateAll(idDataGroup, lValidateGroup);

    /*DString dstrNumUnitDividends, dstrAmount;
    double dCalAmount = 0, bdAmount;

    getField(ifds::NumUnitDividends, dstrNumUnitDividends, idDataGroup);
    getField(ifds::Amount, dstrAmount, idDataGroup);

    bdAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
    dCalAmount = DSTCommonFunctions::convertToDouble(dstrNumUnitDividends) * bdAmount;
    dCalAmount = getRoundedValue(
    

    if (isReinvestmentRateRequired() && dstrToFund != CASH && )
    {
        ADDCONDITIONFROMFILE(CND::WARN_INCORRECT_UNIT_OF_DIVDIDEND_IS_REINVESTED);
    }*/

    DilutionAllocList *pDilutionAllocList = NULL;

    if (getDilutionAllocList(pDilutionAllocList, idDataGroup, false) <= WARNING && pDilutionAllocList)
    {
        BFObjIter iter(*pDilutionAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

        while (!iter.end())
        {
            DString dstrBackDatedReason, dstrAccountable;

            iter.getObject()->getField(ifds::BackDatedReason, dstrBackDatedReason, idDataGroup);
            iter.getObject()->getField(ifds::Accountable, dstrAccountable, idDataGroup);

            if (dstrBackDatedReason.empty() || dstrAccountable.empty())
            {
                ADDCONDITIONFROMFILE(CND::ERR_ACCTOUNTIBILITY_BACKDATEDREASON_ARE_REQUIRED_FOR_DILUTION);
                break;
            }

            ++iter;
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY ManualDividendAdjustment::validateAddrCode(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAddrCode")); 
    
    DString dstrESGSettle, dstrAddrCode, dstrToFund, dstrIDI;

    getField(ifds::ESGSettle, dstrESGSettle, idDataGroup);
    getField(ifds::AddrCode, dstrAddrCode, idDataGroup);
    getField(ifds::ToFund, dstrToFund, idDataGroup);

    if (isShareholderAddressNeeded(idDataGroup) && !isFoundActiveAddrCode(dstrAddrCode, idDataGroup))
    {
        ADDCONDITIONFROMFILE(CND::ERR_ADDRESS_CODE_INVALID);
    }
    else if (dstrToFund == CASH && dstrESGSettle != NSM_SETTLE::EXCLUDE && isCASHSettleESGElig(idDataGroup) && dstrAddrCode != getDivChqAddr(idDataGroup))
    {
        addIDITagValue(dstrIDI, I_("DIVCHQADDR"), getDivChqAddr(idDataGroup));
        ADDCONDITIONFROMFILEIDI(CND::ERR_PAY_OUT_ADDR_MUST_BE_EQUAL_TO, dstrIDI);
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
bool ManualDividendAdjustment::isCASHSettleESGElig(const BFDataGroupId &idDataGroup)
{
    bool isEnable = false;
    DString dstrToFund, dstrAccDivChqAddr;

    getField(ifds::ToFund, dstrToFund, idDataGroup);
    dstrAccDivChqAddr = getDivChqAddr(idDataGroup);

    if (dstrToFund == CASH && (dstrAccDivChqAddr == I_("01") || dstrAccDivChqAddr.empty()))
    {
        MFAccount *pMFAccount = NULL;   

        if (getAccount (pMFAccount, idDataGroup) <= WARNING  && pMFAccount) 
        {
            DString dstrAcctDesignation, dstrAcctCIDElig;
            pMFAccount->getField (ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false);
            pMFAccount->getField (ifds::AcctCIDElig, dstrAcctCIDElig, idDataGroup, false);

            if ((dstrAcctDesignation == I_("2") || dstrAcctDesignation == I_("3")) &&
                dstrAcctCIDElig == YES)
            {
                isEnable = true;
            }
        }
    }

    return isEnable;
}

//****************************************************************************** 
bool ManualDividendAdjustment::isFoundActiveAddrCode(const DString &searchAddrCode, const BFDataGroupId &idDataGroup)
{
    bool isFound = false;

    if (isShareholderAddressNeeded(idDataGroup))
    {
        DString shrNum;
        Shareholder *pShareholder = NULL;
        AddressList *pAddressList = NULL;

        if (getAccountField(ifds::ShrNum, shrNum, idDataGroup) <= WARNING && !shrNum.empty() &&
            getWorkSession().getShareholder(idDataGroup, shrNum, pShareholder) <= WARNING && pShareholder &&
            pShareholder->getAddressList(pAddressList, idDataGroup) <= WARNING && pAddressList)
        {
            DString dstrCurrBusDate, addrEffectiveDate, addrStopDate, addrCode;
            getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

            BFObjIter iter(*pAddressList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

            while (!iter.end())
            {
                iter.getObject()->getField(ifds::AddrCode, addrCode, idDataGroup);
                iter.getObject()->getField(ifds::EffectiveDate, addrEffectiveDate, idDataGroup);
                iter.getObject()->getField(ifds::StopDate, addrStopDate, idDataGroup);

                if (searchAddrCode == addrCode && DSTCommonFunctions::IsDateBetween(addrEffectiveDate, addrStopDate, dstrCurrBusDate))
                {
                    isFound = true;
                    break;
                }

                ++iter;
            }
        }
    }

    return isFound;
}

//****************************************************************************** 
SEVERITY ManualDividendAdjustment::addressRelatedChanges(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addressRelatedChanges")); 

    DString dstrPayType, dstrToFund;

    getField(ifds::TradesPayType, dstrPayType, idDataGroup);
    getField(ifds::ToFund, dstrToFund, idDataGroup);

    if (dstrPayType == I_("S") && dstrToFund == I_("CASH"))
    {
        setFieldNoValidate(ifds::AddrCode, getDivChqAddr(idDataGroup), idDataGroup, false);
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ManualDividendAdjustment::setField ( const BFFieldId &idField, 
                           const DString &dstrValue,
                           const BFDataGroupId &idDataGroup, 
                           bool bFormatted, 
                           bool bSideEffect, 
                           bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setField"));

   if (idField == ifds::Amount)
   {
       BFCBO::setField ( idField, 
                        dstrValue, 
                        idDataGroup,                         
                        bFormatted, 
                        bSideEffect, 
                        bCheckCurrentValue);
   }
   else
   {
       Trade::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect, bCheckCurrentValue);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ManualDividendAdjustment::getField ( const BFFieldId &idField, 
                       DString &fieldValue, 
                       const BFDataGroupId &idDataGroup, 
                       bool formattedReturn) const
{
    if (idField == ifds::Amount)
    {
        BFCBO::getField (idField, fieldValue, idDataGroup, formattedReturn);
    }
    else
    {
        Trade::getField (idField, fieldValue, idDataGroup, formattedReturn);
    }
}