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
// ^FILE   : MgmtFeeRebateAdjustment.cpp
// ^AUTHOR :   
// ^DATE   : 
//
// ^CLASS    : MgmtFeeRebateAdjustment 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "MgmtFeeRebateAdjustment.hpp"
#include "fundmasterlist.hpp"
#include "funddetaillist.hpp"
#include "FundDetail.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"


namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId ManualTradesTransType;
    extern CLASS_IMPORT const BFDateFieldId LastMFRebateDate;
    extern CLASS_IMPORT const BFTextFieldId MgtFeeRbtElig;
    extern CLASS_IMPORT const BFTextFieldId MFRCorporateFund;
    extern CLASS_IMPORT const BFTextFieldId MFRPayment;
    extern CLASS_IMPORT const BFTextFieldId Slsrep;
    extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId TradeDivType;
    extern CLASS_IMPORT const BFTextFieldId FromFundClassValid;
    extern CLASS_IMPORT const BFTextFieldId ToFundClassValid;
    extern CLASS_IMPORT const BFTextFieldId GetTransType;
    extern CLASS_IMPORT const BFTextFieldId GetNextAvailRate;
}

namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const MGMT_FEE_REBATE_ADJ;
}


namespace
{
    const I_CHAR * const CLASSNAME		= I_("MgmtFeeRebateAdjustment");
    const I_CHAR * const YES            = I_("Y");
    const I_CHAR * const NO             = I_("N");
    const I_CHAR * const CORPORATE_TAX	= I_("I");
    const I_CHAR * const CASH_FUND	    = I_("CASH");;
    const I_CHAR * const NA				= I_("59");
    const I_CHAR * const MR_TYPE        = I_("MR");
    const I_CHAR * const NEXT_MR_UNIT_DATE = I_("NextMRUnitDate");
}

namespace CND
{
    extern const long ERR_MGMT_FEE_REBATE_NOT_ALLOWED;
	extern const long ERR_TOFUND_SAME_OR_CASH;
	extern const long ERR_INVALID_MF_PAYMENT;
	extern const long WARN_INVALID_MF_PAYMENT;
    extern const long ERR_NO_DIVTYPE_UNIT_RATE_EXISTS_FOR_THIS_DATE;
}

namespace IFASTERR
{
    extern CLASS_IMPORT I_CHAR * const INVALID_MF_PAYMENT;
}

namespace CALCULATEFROM
{
    extern CLASS_IMPORT I_CHAR * const AMOUNT;
    extern CLASS_IMPORT I_CHAR * const NUM_UNIT_ELIG_DIV;
    extern CLASS_IMPORT I_CHAR * const NUM_UNIT_DIV;
}

//******************************************************************************
MgmtFeeRebateAdjustment::MgmtFeeRebateAdjustment(BFAbstractCBO &parent) : ManualDividendAdjustment(parent)
{
    TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}


//******************************************************************************
MgmtFeeRebateAdjustment::~MgmtFeeRebateAdjustment()
{
    TRACE_DESTRUCTOR(CLASSNAME);
}     

//******************************************************************************
SEVERITY MgmtFeeRebateAdjustment::doInit(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

    setFieldSubstituteValues(ifds::TradesTransType, idDataGroup, ifds::ManualTradesTransType);
    setFieldNoValidate(ifds::TradesTransType, TRADETYPE::MGMT_FEE_REBATE_ADJ, idDataGroup, false);
    setFieldSubstituteValues (ifds::MFPayment, idDataGroup, ifds::MFRPayment);
    setFieldReadOnly(ifds::NumUnitEligDividends, idDataGroup, true);
    setFieldNoValidate(ifds::TradeDivType, TRADETYPE::MGMT_FEE_REBATE_ADJ, idDataGroup, false);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void MgmtFeeRebateAdjustment::doInitWithDefaultValues(const BFDataGroupId &idDataGroup)
{
    ManualDividendAdjustment::doInitWithDefaultValues (idDataGroup);

    setFieldRequired(ifds::SrcOfFund, idDataGroup, false);
}

//******************************************************************************
SEVERITY MgmtFeeRebateAdjustment::doApplyRelatedChanges(const BFFieldId &idField, 
                                                        const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

    ManualDividendAdjustment::doApplyRelatedChanges (idField, idDataGroup);

    if (idField == ifds::TradesTransType)
    {
        setFieldRequired (ifds::MFPayment, idDataGroup, true);
        setFieldValid (ifds::MFPayment, idDataGroup, false);
    }
    else if (idField == ifds::AccountNum)
    {
        DString accountNum;

        getField (ifds::AccountNum, accountNum, idDataGroup, false);

        if (!accountNum.empty ())
        {
            MFAccount *pMFAccount = NULL;

            if (getWorkSession ().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
                pMFAccount)
            {
                DString brokerCode, branchCode,  slsrepCode;

                pMFAccount->getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
                pMFAccount->getField (ifds::BranchCode, branchCode, idDataGroup, false);
                pMFAccount->getField (ifds::Slsrep, slsrepCode, idDataGroup, false);

                setFieldNoValidate (ifds::Broker, brokerCode, idDataGroup, false, false, true, false); 
                setFieldNoValidate (ifds::Branch, branchCode, idDataGroup, false, false, true, false); 
                setFieldNoValidate (ifds::SlsrepCode, slsrepCode, idDataGroup, false, false, true, false); 
            }
        }
    }
    else if (idField == ifds::FromFund || 
             idField == ifds::FromClass)
    {
        setFieldNoValidate(ifds::SrcOfFund, NULL_STRING, idDataGroup, false, true, false, false);
    }
    else if (idField == ifds::ToFund || 
             idField == ifds::ToClass)
    {
        setFieldNoValidate(ifds::SrcOfFund, NULL_STRING, idDataGroup, false, true, false, false);
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MgmtFeeRebateAdjustment::doValidateField(const BFFieldId &idField, 
                                                  const DString &strValue, 
                                                  const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

    if (ManualDividendAdjustment::doValidateField (idField, strValue, idDataGroup) <= WARNING)
    {
        if (idField == ifds::MFPayment)
        {
            DString mfPayment;

            getField (ifds::MFPayment, mfPayment, idDataGroup, false);

            if (mfPayment == NA)
            {
                getErrMsg (IFASTERR::INVALID_MF_PAYMENT,
                    CND::ERR_INVALID_MF_PAYMENT, 
                    CND::WARN_INVALID_MF_PAYMENT, 
                    idDataGroup);
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY ();
}



//******************************************************************************
SEVERITY MgmtFeeRebateAdjustment::validateEffectiveDateAgainstIDRecord(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEffectiveDateAgainstIDRecords"))

    DString dstrFromFundClassValid, dstrTradeDivType;

    getField(ifds::FromFundClassValid, dstrFromFundClassValid, idDataGroup);
    getField(ifds::TradeDivType, dstrTradeDivType, idDataGroup, true);

    if (dstrFromFundClassValid == YES && isDivRateRequired())
    {
        BigDecimal bdDivRate;
        DString dstrUnitId;

        getDivRate(bdDivRate, dstrUnitId, idDataGroup, dstrTradeDivType, YES); 

        //No MR rate is found on trade date and after trade date.
        if (bdDivRate == 0)
        {
            DString strIDI;

            addIDITagValue(strIDI, I_("DIVTYPE"), dstrTradeDivType);
            ADDCONDITIONFROMFILEIDI(CND::ERR_NO_DIVTYPE_UNIT_RATE_EXISTS_FOR_THIS_DATE, strIDI);
        }
    }

    // **Reinvestment Rate validation isn't required.

    return GETCURRENTHIGHESTSEVERITY ();
}



//******************************************************************************
bool MgmtFeeRebateAdjustment::isMgtFeeRbtElig ( const DString &fundCode, 
                                               const DString &classCode, 
                                               const BFDataGroupId &idDataGroup)
{
    DString mgtFeeRbtElig;
    getFundField (fundCode, classCode, ifds::MgtFeeRbtElig, mgtFeeRbtElig);

    return mgtFeeRbtElig == Y;
}


//****************************************************************************** 
SEVERITY MgmtFeeRebateAdjustment::validateFundClass(const DString &fundCode, 
                                                    const DString &classCode, 
                                                    const DString &accountNum, 
                                                    const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"))

        if (!fundCode.empty() && !classCode.empty())
        {
            if (isMgtFeeRbtElig (fundCode, classCode, idDataGroup))
            {
                validateAccountHolding(fundCode, classCode, idDataGroup);
            }
            else
            {
                // management fee rebate is not allowed. 
                ADDCONDITIONFROMFILE (CND::ERR_MGMT_FEE_REBATE_NOT_ALLOWED);
            }
        }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MgmtFeeRebateAdjustment::validateToFundClass(const DString &toFund, 
                                                      const DString &toClass, 
                                                      const DString &accountNum, 
                                                      const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateToFundClass"));

    ManualDividendAdjustment::validateToFundClass(toFund, toClass, accountNum, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MgmtFeeRebateAdjustment::validateFromToFundClass(const DString &fromFund,
                                                          const DString &fromClass,
                                                          const DString &toFund,
                                                          const DString &toClass,
                                                          const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFromToFundClass"));

    FundMasterList	*pFundMasterList;
    DString			taxType;
    DString			mfrCorporateFund;

    getWorkSession().getOption( ifds::MFRCorporateFund, mfrCorporateFund, idDataGroup, false );

    if (getMgmtCo ().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList != NULL)
        taxType = pFundMasterList->getTaxType (fromFund);

    // need to see for cash fund
    if  (mfrCorporateFund == YES && taxType == CORPORATE_TAX)
    {
        if (fromFund != toFund && fromClass != toClass)
        {
            ADDCONDITIONFROMFILE (CND::ERR_TOFUND_SAME_OR_CASH);
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
void MgmtFeeRebateAdjustment::setDefaultEffectiveDate(const BFDataGroupId &idDataGroup)
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
        DString dstrLastMFRebateDate;
        pFundDetail->getField(ifds::LastMFRebateDate, dstrLastMFRebateDate, idDataGroup);

        setFieldNoValidate(ifds::EffectiveDate, NULL_STRING, idDataGroup, false , true, false, false);

        if (!dstrLastMFRebateDate.empty() && dstrLastMFRebateDate != I_("01010001"))
        {
            setField(ifds::EffectiveDate, dstrLastMFRebateDate, idDataGroup, false, true);
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
bool MgmtFeeRebateAdjustment::isDivRateRequired()
{
    return true;
}

//******************************************************************************
void MgmtFeeRebateAdjustment::getField(const BFFieldId &idField, 
                                       DString &fieldValue, 
                                       const BFDataGroupId &idDataGroup, 
                                       bool formattedReturn) const
{
    if (idField == ifds::NumUnitEligDividends && formattedReturn)
    {
        //The actual value will not be shown on the screen, but it still be sent to the back-end.
        fieldValue = I_("0.0000");
    }
    else
    {
        ManualDividendAdjustment::getField(idField, fieldValue, idDataGroup, formattedReturn);
    }
}