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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : SoftCappedValidation.cpp
// ^AUTHOR : 
// ^DATE   : Jan, 2016
//
// ^CLASS    : SoftCappedValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "SoftCappedValidation.h"
#include "mgmtco.hpp"
#include "funddetaillist.hpp"
#include "FundDetail.hpp"
#include "FundRuleList.hpp"
#include "FundGroupTypeList.hpp"
#include <ifastdataimpl\dse_dstc0167_req.hpp>
#include <ifastdataimpl\dse_dstc0167_vw.hpp>

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_fund_capped_at_account.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_fund_capped_at_account.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_fund_capped_at_fnd_cls.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_fund_capped_at_fnd_cls.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_soft_capped_fund_level.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_soft_capped_fund_level.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_soft_capped_fund_group_level.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_soft_capped_fund_group_level.h>

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest TRADE_MIN_AMT_CHECK;
}

namespace ifds
{
    extern CLASS_IMPORT const BFDateFieldId FundStatusDate;
    extern CLASS_IMPORT const BFDateFieldId StartDate;
}

namespace FUND_RULE_TYPE
{
    extern CLASS_IMPORT I_CHAR * const SOFT_CAPPED;
}

namespace FUND_RULE_LEVEL
{
    extern CLASS_IMPORT I_CHAR * const FUNDCLASS;
    extern CLASS_IMPORT I_CHAR * const FUND;
    extern CLASS_IMPORT I_CHAR * const FUNDGROUP;
}

namespace FUND_GROUP_TYPE
{
    extern CLASS_IMPORT I_CHAR * const SOFT_CAPPED;
}

namespace CND
{  
    
   extern const long WARN_SOFT_CAPPED_FUND_GROUP_LEVEL;
   extern const long ERR_SOFT_CAPPED_FUND_GROUP_LEVEL;
   extern const long ERR_SOFT_CAPPED_FUND_LEVEL;
   extern const long WARN_SOFT_CAPPED_FUND_LEVEL;
   extern const long WARN_FUND_CAPPED_AT_ACCOUNT;
   extern const long ERR_FUND_CAPPED_AT_ACCOUNT;
   extern const long ERR_FUND_CAPPED_AT_FND_CLS;
   extern const long WARN_FUND_CAPPED_AT_FND_CLS;
}

namespace IFASTERR
{
   
}

namespace
{
    const I_CHAR * const CLASSNAME                     = I_("SoftCappedValidation");
    const I_CHAR * const YES                           = I_("Y");
    const I_CHAR * const NO                            = I_("N");
    const I_CHAR * const FUND                          = I_("FUND");
    const I_CHAR * const CLASS                         = I_("CLASS");
    const I_CHAR * const ASOF                          = I_("ASOF");
    const I_CHAR * const EWI_ERROR                     = I_("E");
    const I_CHAR * const EWI_WARNING                   = I_("W");

    const long FUND_CAPPED_AT_ACCOUNT	               = 766;
    const long FUND_CAPPED_AT_FND_CLS	               = 767;
    const long SOFT_CAPPED_FUND_LEVEL                  = 968;
    const long SOFT_CAPPED_FUND_GROUP_LEVEL            = 969;
}

/*const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags 
    {ifds::FundCode,      BFCBO::NOT_ON_HOST,             0},
    {ifds::ClassCode,     BFCBO::NOT_ON_HOST,             0},
};

static const int NUM_FIELDS = sizeof  (classFieldInfo) / sizeof  (BFCBO::CLASS_FIELD_INFO);*/

//******************************************************************************
SoftCappedValidation::SoftCappedValidation(BFAbstractCBO &parent)
:MFCanBFCbo (parent),
 _fundCode(NULL_STRING),
 _classCode(NULL_STRING),
 _tradeDate(NULL_STRING)
{
    TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
    //registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

    setObjectAsList();
}

//******************************************************************************
SoftCappedValidation::~SoftCappedValidation()
{
    TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY SoftCappedValidation::init(const DString &dstrAccountNum, 
                                    const DString &dstrFundCode, 
                                    const DString &dstrClassCode, 
                                    const DString &dstrTransType,
                                    const DString &dstrEffectiveDate)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

    _fundCode = dstrFundCode;
    _classCode = dstrClassCode;
    _tradeDate = dstrEffectiveDate;

    _fundCode.upperCase();
    _classCode.upperCase();

    BFData queryData(ifds::DSTC0167_REQ);
    DString mgmtCoIdOut;
    bool ignoreDataNotFound = true;

    queryData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
    queryData.setElementValue(ifds::AccountNum, dstrAccountNum);
    queryData.setElementValue(ifds::FundCode, dstrFundCode);
    queryData.setElementValue(ifds::ClassCode, dstrClassCode);
    queryData.setElementValue(ifds::TransType, dstrTransType);
    queryData.setElementValue(ifds::EffectiveDate, dstrEffectiveDate, false, false);
    queryData.setElementValue(ifds::Amount, I_("0"));

    queryData.setElementValue(ifds::AmountType, NULL_STRING);
    queryData.setElementValue(ifds::SettleCurrency, NULL_STRING);
    queryData.setElementValue(ifds::ExchRate, NULL_STRING);
    queryData.setElementValue(ifds::BrokerCode, NULL_STRING);
    queryData.setElementValue(ifds::BranchCode, NULL_STRING);
    queryData.setElementValue(ifds::SalesRepCode, NULL_STRING);
    queryData.setElementValue(ifds::AMSCode, NULL_STRING);
    queryData.setElementValue(ifds::AMSType, NULL_STRING);
    queryData.setElementValue(ifds::DepositType, NULL_STRING); 
    queryData.setElementValue(ifds::OrderType, NULL_STRING);
    queryData.setElementValue(ifds::FullExchPrntToPrnt, NO);
	queryData.setElementValue(ifds::DilutionLinkNum, NULL_STRING);
	queryData.setElementValue(ifds::RDSPValidation, NO);
	queryData.setElementValue(ifds::GRRepayReason, NULL_STRING);
	queryData.setElementValue(ifds::RDSPPaymtDate, NULL_STRING);
	queryData.setElementValue(ifds::MatchingKey, NULL_STRING);
	queryData.setElementValue(ifds::FullMoneyOutIndc, NULL_STRING);

    ReceiveData(DSTC_REQUEST::TRADE_MIN_AMT_CHECK, 
                queryData, 
                ifds::DSTC0167_VW,
                DSTCRequestor(getSecurity (), true, ignoreDataNotFound));

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SoftCappedValidation::addConditions()
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addConditions"));
    
    FundDetailList *pFundDetailList;
    FundDetail *pFundDetail;
    
    if (getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList)
    {
        if (pFundDetailList->getFundDetail(_fundCode, _classCode, BF::HOST, pFundDetail) && pFundDetail)
        {
            DString idiStr, errNum, severityCode;
            BFObjIter iter(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

            iter.begin();

            while (!iter.end())
            {
                idiStr = NULL_STRING;
                severityCode.upperCase();  
                iter.getObject()->getField(ifds::ErrNum, errNum, BF::HOST, false);
                iter.getObject()->getField(ifds::EWI, severityCode, BF::HOST, false);

                DString fundStatusDate;
                FundDetailList *pFundDetailList = NULL;
                FundDetail *pFundDetail = NULL;

                if (getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList)
                {
                    if (pFundDetailList->getFundDetail(_fundCode, _classCode, BF::HOST, pFundDetail) && pFundDetail)
                    {
                        pFundDetail->getField(ifds::FundStatusDate, fundStatusDate, BF::HOST, true);
                    }
                }

                DSTCommonFunctions::FormatDate(fundStatusDate);
       
                addIDITagValue(idiStr, FUND, _fundCode);
                addIDITagValue(idiStr, CLASS, _classCode);

                long nErrNum = errNum.strip().stripLeading('0').convertToULong();

                if (errNum.empty())
                    return GETCURRENTHIGHESTSEVERITY();

                switch (nErrNum)
                {
                    case FUND_CAPPED_AT_ACCOUNT:
                        {
                            addIDITagValue(idiStr, ASOF, fundStatusDate);

                            if  (severityCode == EWI_WARNING)
                                ADDCONDITIONFROMFILEIDI(CND::WARN_FUND_CAPPED_AT_ACCOUNT, idiStr);
                            if  (severityCode == EWI_ERROR)
                                ADDCONDITIONFROMFILEIDI(CND::ERR_FUND_CAPPED_AT_ACCOUNT, idiStr);
                        }
                        break;
                    case FUND_CAPPED_AT_FND_CLS:
                        {
                            FundRuleList *pSoftCapRuleList = NULL;

                            if (getMgmtCo().getFundRuleList(FUND_RULE_TYPE::SOFT_CAPPED, pSoftCapRuleList) <= WARNING && pSoftCapRuleList)
                            {
                                DString startDate = pSoftCapRuleList->getRuleDetailByDate(FUND_RULE_TYPE::SOFT_CAPPED, FUND_RULE_LEVEL::FUNDCLASS, ifds::StartDate, NULL_STRING, _fundCode, _classCode, _tradeDate, true);
                                addIDITagValue(idiStr, ASOF, startDate);
                            }

                            if  (severityCode == EWI_WARNING)
                                ADDCONDITIONFROMFILEIDI(CND::WARN_FUND_CAPPED_AT_FND_CLS, idiStr);
                            if  (severityCode == EWI_ERROR)
                                ADDCONDITIONFROMFILEIDI(CND::ERR_FUND_CAPPED_AT_FND_CLS, idiStr);
                        }
                        break;
                    case SOFT_CAPPED_FUND_LEVEL:
                        {
                            FundRuleList *pSoftCapRuleList = NULL;

                            if (getMgmtCo().getFundRuleList(FUND_RULE_TYPE::SOFT_CAPPED, pSoftCapRuleList) <= WARNING && pSoftCapRuleList)
                            {
                                DString startDate = pSoftCapRuleList->getRuleDetailByDate(FUND_RULE_TYPE::SOFT_CAPPED, FUND_RULE_LEVEL::FUND, ifds::StartDate, NULL_STRING, _fundCode, NULL_STRING, _tradeDate, true);
                                addIDITagValue(idiStr, ASOF, startDate);
                            }

                            if (severityCode == EWI_WARNING)
                                ADDCONDITIONFROMFILEIDI(CND::WARN_SOFT_CAPPED_FUND_LEVEL, idiStr);
                            if (severityCode == EWI_ERROR)
                                ADDCONDITIONFROMFILEIDI(CND::ERR_SOFT_CAPPED_FUND_LEVEL, idiStr);
                        }
                        break;
                    case SOFT_CAPPED_FUND_GROUP_LEVEL:
                        {
                            FundRuleList *pSoftCapRuleList = NULL;
                            FundGroupTypeList *pFundGroupTypeList = NULL;

                            if (getMgmtCo().getFundGroupTypeList(pFundGroupTypeList, FUND_GROUP_TYPE::SOFT_CAPPED) <= WARNING && pFundGroupTypeList &&
                                getMgmtCo().getFundRuleList(FUND_RULE_TYPE::SOFT_CAPPED, pSoftCapRuleList) <= WARNING && pSoftCapRuleList)
                            {
                                DString dstrFundGroupCode, startDate;
                                dstrFundGroupCode = pFundGroupTypeList->getFundGroupCode(_fundCode, _classCode);
                                startDate = pSoftCapRuleList->getRuleDetailByDate(FUND_RULE_TYPE::SOFT_CAPPED, FUND_RULE_LEVEL::FUNDGROUP, ifds::StartDate, dstrFundGroupCode, NULL_STRING, NULL_STRING, _tradeDate, true);
                                
                                addIDITagValue(idiStr, ASOF, startDate);
                            }

                            if (severityCode == EWI_WARNING)
                                ADDCONDITIONFROMFILEIDI(CND::WARN_SOFT_CAPPED_FUND_GROUP_LEVEL, idiStr);
                            if (severityCode == EWI_ERROR)
                                ADDCONDITIONFROMFILEIDI(CND::ERR_SOFT_CAPPED_FUND_GROUP_LEVEL, idiStr);
                        }
                        break;
                    default:
                        assert(0);
                }

                ++iter;
            }
        }
    }
    
    return GETCURRENTHIGHESTSEVERITY();
}
