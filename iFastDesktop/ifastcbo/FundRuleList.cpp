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
// ^FILE   : FundRuleList.cpp
// ^AUTHOR :
// ^DATE   : 31 May 2016
//
// ^CLASS    : FundRuleList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundRuleList.hpp"
#include <ifastdataimpl\dse_dstc0471_vw.hpp>
#include <ifastdataimpl\dse_dstc0471_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest FUND_RULES_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_("FundRuleList");
}

namespace FUND_RULE_LEVEL
{
    extern CLASS_EXPORT I_CHAR * const FUNDCLASS  = I_("01");
    extern CLASS_EXPORT I_CHAR * const FUND       = I_("02");
    extern CLASS_EXPORT I_CHAR * const FUNDGROUP  = I_("03");
}

namespace FUND_RULE_TYPE
{
    extern CLASS_EXPORT I_CHAR * const SOFT_CAPPED  = I_("22");
}
  

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId FundRuleType;
    extern CLASS_IMPORT const BFTextFieldId FundRuleLevel;
    extern CLASS_IMPORT const BFTextFieldId FundGroupCode;
    extern CLASS_IMPORT const BFTextFieldId FundCode;
    extern CLASS_IMPORT const BFTextFieldId ClassCode;
    extern CLASS_IMPORT const BFDateFieldId StartDate;
    extern CLASS_IMPORT const BFDateFieldId StopDate;
}

namespace CND
{
}

//******************************************************************************
FundRuleList::FundRuleList(BFAbstractCBO &parent)
:MFCanBFCbo(parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

	setObjectAsList();
}


//******************************************************************************
FundRuleList::~FundRuleList()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}


//******************************************************************************
SEVERITY FundRuleList::init(const DString &dstrFundRuleType,
                            const DString &dstrTrack, 
							const DString &dstrPageName)                             
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	BFData requestData(ifds::DSTC0471_REQ);
	DString mgmtCoIdOut;

	requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	requestData.setElementValue(ifds::Track, dstrTrack);
	requestData.setElementValue(ifds::Activity, dstrPageName);
    requestData.setElementValue(ifds::FundRuleType, dstrFundRuleType);

    ReceiveData(DSTC_REQUEST::FUND_RULES_INQUIRY, requestData, ifds::DSTC0471_VW, DSTCRequestor(getSecurity(), true));

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FundRuleList::isRuleApplied(const DString &FundRuleType,
                                 const DString &FundRuleLevel,
                                 const DString &fundGroupCode,
                                 const DString &fundCode,
                                 const DString &classCode,
                                 const DString &date)
{
    bool ruleApplied = false;
    DString dstrFundCode(fundCode), dstrClassCode(classCode), dstrFundGroupCode(fundGroupCode);
    BFObjIter iterFundRule(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

    dstrFundCode.stripAll().upperCase();
    dstrClassCode.stripAll().upperCase();
    dstrFundGroupCode.stripAll().upperCase();

    while (!iterFundRule.end())
    {
        DString iterFundRuleLevel, iterStartDate, iterStopDate, iterFundGroupCode, iterFundRuleType;
        DString iterFundCode, iterClassCode;

        iterFundRule.getObject()->getField(ifds::FundRuleType, iterFundRuleType, BF::HOST);
        iterFundRule.getObject()->getField(ifds::FundRuleLevel, iterFundRuleLevel, BF::HOST);
        iterFundRule.getObject()->getField(ifds::FundGroupCode, iterFundGroupCode, BF::HOST);
        iterFundRule.getObject()->getField(ifds::FundCode, iterFundCode, BF::HOST);
        iterFundRule.getObject()->getField(ifds::ClassCode, iterClassCode, BF::HOST);
        iterFundRule.getObject()->getField(ifds::StartDate, iterStartDate, BF::HOST);
        iterFundRule.getObject()->getField(ifds::StopDate, iterStopDate, BF::HOST);

        if (iterFundRuleType == FundRuleType && 
            iterFundRuleLevel == FundRuleLevel && 
            DSTCommonFunctions::IsDateBetween(iterStartDate, iterStopDate, date))
        {
            iterFundGroupCode.stripAll().upperCase();
            iterFundCode.stripAll().upperCase();
            iterClassCode.stripAll().upperCase();

            if (FundRuleLevel == FUND_RULE_LEVEL::FUNDGROUP &&
                iterFundGroupCode == dstrFundGroupCode)
            {
                ruleApplied = true;
                break;
            }
            else if (FundRuleLevel == FUND_RULE_LEVEL::FUND &&
                     iterFundCode == dstrFundCode)
            {
                ruleApplied = true;
                break;
            }
            else if (FundRuleLevel == FUND_RULE_LEVEL::FUNDCLASS &&
                     iterFundCode == dstrFundCode &&
                     iterClassCode == dstrClassCode)
            {
                ruleApplied = true;
                break;
            }
        }

        ++iterFundRule;
    }

    return ruleApplied;
}

//******************************************************************************
bool FundRuleList::isSoftCapped(const DString &fundCode,
                                const DString &classCode,
                                const DString &fundGroupCode,
                                const DString &date)
{
    return isSoftCappedAtFundGroupLvl(date, fundGroupCode) ||
           isSoftCappedAtFundLvl(date, fundCode) ||
           isSoftCappedAtFundClassLvl(date, fundCode, classCode);
}

//******************************************************************************
bool FundRuleList::isSoftCappedAtFundGroupLvl(const DString &date,
                                              const DString &dstrFundGroupCode)
{
    return isRuleApplied(FUND_RULE_TYPE::SOFT_CAPPED, FUND_RULE_LEVEL::FUNDGROUP, dstrFundGroupCode, NULL_STRING, NULL_STRING, date);
}

//******************************************************************************
bool FundRuleList::isSoftCappedAtFundLvl(const DString &date,
                                         const DString &dstrFundCode)
{
    return isRuleApplied(FUND_RULE_TYPE::SOFT_CAPPED, FUND_RULE_LEVEL::FUND, NULL_STRING, dstrFundCode, NULL_STRING, date);
}

//******************************************************************************
bool FundRuleList::isSoftCappedAtFundClassLvl(const DString &date,
                                              const DString &dstrFundCode,
                                              const DString &dstrClassCode)
{
    return isRuleApplied(FUND_RULE_TYPE::SOFT_CAPPED, FUND_RULE_LEVEL::FUNDCLASS, NULL_STRING, dstrFundCode, dstrClassCode, date);
}

//******************************************************************************
DString FundRuleList::getRuleDetailByDate(const DString &FundRuleType,
                                          const DString &FundRuleLevel,
                                          const BFFieldId idField,
                                          const DString &fundGroupCode,
                                          const DString &fundCode,
                                          const DString &classCode,
                                          const DString &date,
                                          const bool formatted)
{
    DString fieldVal;
    DString dstrFundCode(fundCode), dstrClassCode(classCode), dstrFundGroupCode(fundGroupCode);
    BFObjIter iterFundRule(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

    dstrFundCode.stripAll().upperCase();
    dstrClassCode.stripAll().upperCase();
    dstrFundGroupCode.stripAll().upperCase();

    while (!iterFundRule.end())
    {
        DString iterFundRuleLevel, iterStartDate, iterStopDate, iterFundGroupCode, iterFundRuleType;
        DString iterFundCode, iterClassCode;

        iterFundRule.getObject()->getField(ifds::FundRuleType, iterFundRuleType, BF::HOST);
        iterFundRule.getObject()->getField(ifds::FundRuleLevel, iterFundRuleLevel, BF::HOST);
        iterFundRule.getObject()->getField(ifds::FundGroupCode, iterFundGroupCode, BF::HOST);
        iterFundRule.getObject()->getField(ifds::FundCode, iterFundCode, BF::HOST);
        iterFundRule.getObject()->getField(ifds::ClassCode, iterClassCode, BF::HOST);
        iterFundRule.getObject()->getField(ifds::StartDate, iterStartDate, BF::HOST);
        iterFundRule.getObject()->getField(ifds::StopDate, iterStopDate, BF::HOST);

        if (iterFundRuleType == FundRuleType && 
            iterFundRuleLevel == FundRuleLevel && 
            DSTCommonFunctions::IsDateBetween(iterStartDate, iterStopDate, date))
        {
            iterFundGroupCode.stripAll().upperCase();
            iterFundCode.stripAll().upperCase();
            iterClassCode.stripAll().upperCase();

            if (FundRuleLevel == FUND_RULE_LEVEL::FUNDGROUP &&
                iterFundGroupCode == dstrFundGroupCode)
            {
                iterFundRule.getObject()->getField(idField, fieldVal, BF::HOST, formatted);
                break;
            }
            else if (FundRuleLevel == FUND_RULE_LEVEL::FUND &&
                     iterFundCode == dstrFundCode)
            {
                iterFundRule.getObject()->getField(idField, fieldVal, BF::HOST, formatted);
                break;
            }
            else if (FundRuleLevel == FUND_RULE_LEVEL::FUNDCLASS &&
                     iterFundCode == dstrFundCode &&
                     iterClassCode == dstrClassCode)
            {
                iterFundRule.getObject()->getField(idField, fieldVal, BF::HOST, formatted);
                break;
            }
        }

        ++iterFundRule;
    }

    return fieldVal;
}