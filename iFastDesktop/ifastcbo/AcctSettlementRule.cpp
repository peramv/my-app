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
//    Copyright 2008 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctSettlementRule.cpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 2008
//
// ^CLASS    : AcctLvlSttlmntRule
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "AcctSettlementRule.hpp"
#include "ErrMsgRulesList.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "fundbrokerdefault.hpp"
#include "fundbrokerelig.hpp"
#include "fundbroker.hpp"
#include "fundbrokerlist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundlist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "agent.hpp"
#include "agentlist.hpp"
#include "branch.hpp"
#include "branchlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "AcctSettlementRuleDuplicationCheck.hpp"
#include "mfaccount.hpp"
#include "FundGroupSubList.hpp"

#include <ifastdataimpl\dse_dstc0386_vw.hpp>
#include <ifastdataimpl\dse_dstc0386_req.hpp>
#include <ifastdataimpl\dse_dstc0386_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ACCT_CONTROL_INQUIRY;
};

namespace 
{
    const I_CHAR * const CLASSNAME           = I_( "AcctLvlSttlmntRule" );

    const I_CHAR * const SETTLE_DAYS_ED     = I_( "24" );
    const I_CHAR * const SETTLE_DAYS_PW     = I_( "25" );
    const I_CHAR * const SETTLE_DAYS_TO     = I_( "26" );
    const I_CHAR * const SETTLE_DAYS_TI     = I_( "27" );
    const I_CHAR * const SETTLE_DAYS_EO     = I_( "28" );
    const I_CHAR * const SETTLE_DAYS_EI     = I_( "29" );

    const I_CHAR * const YES                = I_( "Y" );
    const I_CHAR * const NO                 = I_( "N" );
    const I_CHAR * const DEFAULT_SETTLE_DAY = I_( "2" );
	const I_CHAR * const CURRENT_BUS_DATE   = I_( "CURRENT_BUS_DATE" );
};

namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const PURCHASE;
    extern CLASS_IMPORT I_CHAR * const REDEMPTION;
    extern CLASS_IMPORT I_CHAR * const TRANSFER;
    extern CLASS_IMPORT I_CHAR * const EXCHANGE;
	extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
	extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
	extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
	extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
}

// Reference to Fields
namespace ifds
{
    extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
    extern CLASS_IMPORT const BFTextFieldId FundNumber;
    extern CLASS_IMPORT const BFTextFieldId FundEligSlsRepLvl;
    extern CLASS_IMPORT const BFTextFieldId FundBrokerApplicable;

    extern CLASS_IMPORT const BFTextFieldId AcctType;
    extern CLASS_IMPORT const BFTextFieldId TaxType;
    extern CLASS_IMPORT const BFTextFieldId BrokerCode;
    extern CLASS_IMPORT const BFTextFieldId BranchCode;
    extern CLASS_IMPORT const BFTextFieldId BrokerFund;
    extern CLASS_IMPORT const BFTextFieldId BrokerName;
    extern CLASS_IMPORT const BFTextFieldId AgencyCode;
    extern CLASS_IMPORT const BFTextFieldId BranchName;
    extern CLASS_IMPORT const BFTextFieldId Slsrep;
    extern CLASS_IMPORT const BFTextFieldId SlsrepName;
    extern CLASS_IMPORT const BFTextFieldId RepByBranch;

    extern CLASS_IMPORT const BFTextFieldId FundAllow;
    extern CLASS_IMPORT const BFTextFieldId AddPerm;
    extern CLASS_IMPORT const BFTextFieldId ValidationPassed;

    extern CLASS_IMPORT const BFTextFieldId SettleDays;

    extern CLASS_IMPORT const BFTextFieldId OverrideChar;
    extern CLASS_IMPORT const BFTextFieldId OverrideLogical;
    extern CLASS_IMPORT const BFDecimalFieldId OverrideAmt;

    extern CLASS_IMPORT const BFTextFieldId AcctLvlSettlementRuleType;

    extern CLASS_IMPORT const BFTextFieldId SettlementRulecrossRuleType;
    extern CLASS_IMPORT const BFTextFieldId SettlementRulecrossSettleDays;
};

// Conditions used
namespace CND
{
    extern const long ERR_INVALID_FUND_CLASS_CODES;
    extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER;
    extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP;
    extern const long ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON;
    extern const long ERR_WARN_FUND_CLASS_PURCHASE_STOP_FLAG_ON;

    extern const long ERR_ACCT_CONTROL_EXISTS;
    extern const long ERR_ACCT_CONTROL_NOT_EXISTS;
    extern const long ERR_ACCT_CONTROL_UNABLE_TO_MODIFY;
    extern const long ERR_SETTLEMENT_RULE_EFFECTIVE_DATE;
    extern const long ERR_SETTLEMENT_RULE_INVALID_SETTLE_DAYS_VALUE;
	extern const long ERR_SETTLEMENT_RULE_PENDING_TRADE_EXISTS;
	extern const long WARN_SETTLEMENT_RULE_PENDING_TRADE_EXISTS;
	extern const long ERR_SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE;
	extern const long WARN_SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE;

    extern const long ERR_UNKNOWN_EXCEPTION;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT_RULE_PENDING_TRADE_EXISTS;
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE;
}

extern BF_OBJ_TYPE OBJ_TYPE_ACCT_SETTLEMENT_RULE;

//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
    // Field DD Id,                         State Flags,            Group Flags
    { ifds::AccountNum,                     BFCBO::NONE,                  0 },

    { ifds::RuleType,                       BFCBO::NONE,                  0 },
    { ifds::FundCode,                       BFCBO::NONE,                  0 },
    { ifds::FundNumber,                     BFCBO::NONE,                  0 },
    { ifds::ClassCode,                      BFCBO::NONE,                  0 },
    { ifds::EffectiveDate,                  BFCBO::NONE,                  0 },
    { ifds::StopDate,                       BFCBO::NONE,                  0 },
    { ifds::SettleDays,                     BFCBO::NONE,                  0 },
    { ifds::ProcessDate,                    BFCBO::NONE,                  0 },
    { ifds::Username,                       BFCBO::NONE,                  0 },
    { ifds::ModUser,                        BFCBO::NONE,                  0 },
    { ifds::ModDate,                        BFCBO::NONE,                  0 },
    { ifds::AcctControlsID,                 BFCBO::NONE,                  0 },
    { ifds::AcctControlsVer,                BFCBO::NONE,                  0 },
    { ifds::AcctControlsRID,                BFCBO::NONE,                  0 },
	{ ifds::FundGroup,                      BFCBO::NONE,                  0 },

    { ifds::rxAcctControlsRID,              BFCBO::NONE,                  0 },


    { ifds::OverrideChar,                   BFCBO::NONE,                  0 },
    { ifds::OverrideLogical,                BFCBO::NONE,                  0 },
    { ifds::OverrideAmt,                    BFCBO::NONE,                  0 },

    // broker/branch/sales rep
    { ifds::BrokerCode,                     BFCBO::NONE,                  0 },
    { ifds::BranchCode,                     BFCBO::NONE,                  0 },
    { ifds::Slsrep,                         BFCBO::NONE,                  0 },

    // cross-edit validation
    { ifds::SettlementRulecrossRuleType,    BFCBO::NONE,                  0 },
    { ifds::SettlementRulecrossSettleDays,  BFCBO::NONE,                  0 },

    //// rule-duplication checking
    //{ ifds::DuplicateExist,                 BFCBO::NONE,                  0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
//const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
//{
//    // Object Label,                        State Flags,                Group Flags 
//    { I_( "" ),                             BFCBO::NONE,                  0},
//};
//
//static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************
AcctLvlSttlmntRule::AcctLvlSttlmntRule(BFAbstractCBO &parent)
: MFCanBFCbo( parent ),
_pErrMsgRulesList( NULL )
{
    TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
    registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
    _dstrAccountNum = NULL_STRING;

    addCrossEdit( ifds::SettlementRulecrossRuleType,ifds::RuleType );
    addCrossEdit( ifds::SettlementRulecrossRuleType,ifds::FundCode );
    addCrossEdit( ifds::SettlementRulecrossRuleType,ifds::ClassCode );
    //addCrossEdit( ifds::SettlementRulecrossRuleType,ifds::EffectiveDate );
    //addCrossEdit( ifds::SettlementRulecrossRuleType,ifds::StopDate );

    addCrossEdit( ifds::SettlementRulecrossSettleDays,ifds::SettleDays );
    addCrossEdit( ifds::SettlementRulecrossSettleDays,ifds::FundCode );
    addCrossEdit( ifds::SettlementRulecrossSettleDays,ifds::ClassCode );
}

//******************************************************************************
AcctLvlSttlmntRule::~AcctLvlSttlmntRule(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::initNew( const DString& accountNum, 
                                      const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew" )); 

    setFieldNoValidate( ifds::AccountNum, accountNum, idDataGroup );
    commonInit( idDataGroup );

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::init( const BFData& data )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init" ));

    attachDataObject(const_cast<BFData&>( data ), false); 
    commonInit( BF::HOST );

    setFieldsReadOnly( BF::HOST, !isNew() );

    return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
void AcctLvlSttlmntRule::initSubSets( const BFDataGroupId& idDataGroup )
{
	FundGroupSubList *pFundGroupSubList = NULL;
	DString substrlist;
	if(getMgmtCo().getFundGroupSubList( pFundGroupSubList, I_("SCYFG") ) <= WARNING )
	{
		if (pFundGroupSubList)
		{
			substrlist = pFundGroupSubList->getFundGroupSubList( I_("SCYFG") );

			if( !substrlist.empty() )
			{
				setFieldAllSubstituteValues( ifds::FundGroup, BF::HOST, substrlist );
			}
		}
	}
}
//******************************************************************************
SEVERITY AcctLvlSttlmntRule::commonInit ( const BFDataGroupId &idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit")) ;

    DString dstrRuleType,dstrFundCode,dstrClassCode,dstrEffectiveDate,dstrStopDate;
    DString dstrOverrideChar,dstrOverrideLog,dstrOverrideAmt;
    DString dstrAcctControlsID,dstrAcctControlsVer,dstrAcctControlsRID;
    DString dstrAccountNum;


    getField( ifds::RuleType,         dstrRuleType,       idDataGroup,false );
    getField( ifds::OverrideLogical,  dstrOverrideLog,    idDataGroup,false );
    getField( ifds::OverrideAmt,      dstrOverrideAmt,    idDataGroup,false );
    getField( ifds::rxAcctControlsRID,  dstrAcctControlsRID,    idDataGroup,false );

    double dRuleType = DSTCommonFunctions::convertToDouble(dstrRuleType);
    int iRuleType = (int)dRuleType;

    if ( (iRuleType < 24) || (iRuleType > 29) )
    {
        // out of range then set to default rule type
        dstrRuleType = SETTLE_DAYS_ED;
    }

    if ( dstrOverrideLog == NULL_STRING )
    {
        // default value for this field is 'NO'
        dstrOverrideLog = I_("N");
    }

    getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
    if ( dstrAccountNum.empty() )
    {
        MFCanBFCbo* pGrandParentCBO = dynamic_cast<MFCanBFCbo *>( getParent()->getParent() );

        pGrandParentCBO->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
        setFieldNoValidate( ifds::AccountNum, dstrAccountNum, idDataGroup, false, true, true);
    }

    setFieldNoValidate( ifds::AcctControlsRID,  dstrAcctControlsRID,idDataGroup, false, true, true);

    setFieldRequired( ifds::RuleType,       idDataGroup, true );
    setFieldRequired( ifds::EffectiveDate,  idDataGroup, true );
    setFieldRequired( ifds::StopDate,       idDataGroup, true );

    setFieldReadOnly( ifds::BrokerCode,     idDataGroup, true );
    setFieldReadOnly( ifds::BranchCode,     idDataGroup, true );
    setFieldReadOnly( ifds::Slsrep,         idDataGroup, true );

    if ( dstrRuleType == SETTLE_DAYS_ED || 
         dstrRuleType == SETTLE_DAYS_PW ||
         dstrRuleType == SETTLE_DAYS_TO ||
         dstrRuleType == SETTLE_DAYS_TI ||
         dstrRuleType == SETTLE_DAYS_EO ||
         dstrRuleType == SETTLE_DAYS_EI )
    {
        setFieldNoValidate( ifds::SettleDays, dstrOverrideAmt, idDataGroup, false, true, true );
    }
    else
    {
        setFieldNoValidate( ifds::SettleDays, DEFAULT_SETTLE_DAY, idDataGroup, false, true, true );
    }

    setFieldSubstituteValues ( ifds::RuleType, idDataGroup, ifds::AcctLvlSettlementRuleType );
	
	initSubSets(idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::getErrMsg( DString dstrErrNum, 
                                        long lErrConditionId, 
                                        long lWarnConditionId, 
                                        const BFDataGroupId& idDataGroup, 
                                        DString idiStr)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getErrMsg" ));

    if( _pErrMsgRulesList == NULL )
    {
        SEVERITY sevRtn = getWorkSession().getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
    }

    if( _pErrMsgRulesList )
    {
        _pErrMsgRulesList->getEWI( dstrErrNum, lErrConditionId, lWarnConditionId, idDataGroup, idiStr );
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AcctLvlSttlmntRule::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
    getWorkSession().getOption( ifds::MultiCurrency, _dstrMultiCurrency, BF::HOST,false );
    getWorkSession().getOption( ifds::CurrBusDate, _dstrCurrentBusinessDate, BF::HOST, false );

    clearUpdatedFlags( idDataGroup, true );

    DString dstrStopDate;

    getWorkSession().getDateInHostFormat( dstrStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup );

    setFieldNoValidate( ifds::EffectiveDate, _dstrCurrentBusinessDate, idDataGroup, false, true, true);
    setFieldNoValidate( ifds::StopDate, dstrStopDate, idDataGroup, false, true, true );   
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::doValidateField( const BFFieldId& idField, 
                                              const DString& strValue, 
                                              const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));

    if( idField == ifds::SettlementRulecrossRuleType )
    {
        DString dstrFundCode, dstrClassCode;
        getField( ifds::FundCode,      dstrFundCode,  idDataGroup,false );
        getField( ifds::ClassCode,      dstrClassCode,  idDataGroup,false );

        dstrFundCode.strip().upperCase();
        dstrClassCode.strip().upperCase();

        if ( !dstrFundCode.empty() && !dstrClassCode.empty() )
        {
            validateClassCode ( dstrFundCode, dstrClassCode, idDataGroup );
        }
    }
    else if( idField == ifds::StopDate || idField == ifds::EffectiveDate)
    {
        DString dstrEffectiveDate, dstrStopDate;

        getField( ifds::EffectiveDate,  dstrEffectiveDate,  idDataGroup,false );
        getField( ifds::StopDate,       dstrStopDate,       idDataGroup,false );

        if ( !dstrEffectiveDate.empty() && !dstrStopDate.empty() ) 
        {
            // stop date must not be earlier than effective date
            if ( DSTCommonFunctions::CompareDates( dstrEffectiveDate,dstrStopDate ) == DSTCommonFunctions::SECOND_EARLIER )
            {
                ADDCONDITIONFROMFILE( CND::ERR_SETTLEMENT_RULE_EFFECTIVE_DATE );
                return GETCURRENTHIGHESTSEVERITY();
            }
        }

		if ( idField == ifds::StopDate && !dstrStopDate.empty() && !isNew()) 
		{
			// stop date must be earlier than current business date.
			DString dstrCurrBussinesDate;
			getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBussinesDate, idDataGroup, false );
			
			if ( !(DSTCommonFunctions::CompareDates( dstrCurrBussinesDate,dstrStopDate ) == DSTCommonFunctions::SECOND_EARLIER) )
			{
				DString idiStr1 = NULL_STRING;
				DSTCommonFunctions::FormatDate (dstrCurrBussinesDate);
				addIDITagValue (idiStr1, CURRENT_BUS_DATE, dstrCurrBussinesDate);

				getErrMsg( IFASTERR::SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE, 
						   CND::ERR_SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE, 
						   CND::WARN_SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE,
						   idDataGroup, idiStr1);				
			}
		}
    }
    else if( idField == ifds::SettlementRulecrossSettleDays )
    {
        // validate settle days
        DString dstrSettleDays;
        getField( ifds::SettleDays, dstrSettleDays, idDataGroup,false );

        int iSettleDays = (int)DSTCommonFunctions::convertToDouble(dstrSettleDays);

        if ( iSettleDays < 0 )
        {
            ADDCONDITIONFROMFILE( CND::ERR_SETTLEMENT_RULE_INVALID_SETTLE_DAYS_VALUE );
        }
    }
    else if( idField == ifds::FundCode )
    {
        FundMasterList *pFundMasterList;

        if ( !strValue.empty() )
        {
            if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
                pFundMasterList)
            {
                if ( !pFundMasterList->IsFundExist (strValue, idDataGroup) )
                {
                    ADDCONDITIONFROMFILE ( CND::ERR_INVALID_FUND_CLASS_CODES );
                }
                else
                {
                    validateFundCode (strValue, idDataGroup);
                }
            }
        }
    }
    else if( idField == ifds::ClassCode )
    {
        if ( !strValue.empty() )
        {
            DString dstrFundCode,dstrClassCode;
            getField ( ifds::FundCode, dstrFundCode, idDataGroup, false );
            dstrClassCode = strValue;

            dstrFundCode.strip().upperCase();
            dstrClassCode.strip().upperCase();

            validateClassCode ( dstrFundCode, dstrClassCode, idDataGroup );
        }
    }
	else if (idField == ifds::SettleDays)
	{
		validateFundLevelSettleDays(idDataGroup);
	}

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::doValidateAll( const BFDataGroupId& idDataGroup, 
                                            long lValidateGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll" ));

	DString dstrAccountNum, dstrFundCode, dstrClassCode, dstrRuleType, dstrFundGroup;

	getField( ifds::AccountNum,     dstrAccountNum,     idDataGroup,false );
	getField( ifds::RuleType,       dstrRuleType,       idDataGroup,false );
	getField( ifds::FundCode,       dstrFundCode,       idDataGroup,false );
	getField( ifds::ClassCode,      dstrClassCode,      idDataGroup,false );
	getField( ifds::FundGroup,      dstrFundGroup,      idDataGroup,false );

	dstrFundCode.strip().upperCase();
	dstrClassCode.strip().upperCase();

    if (isFieldUpdated (ifds::EffectiveDate, idDataGroup)   ||
        isFieldUpdated (ifds::StopDate,      idDataGroup)   ||
        isFieldUpdated (ifds::FundCode,      idDataGroup)   ||
        isFieldUpdated (ifds::ClassCode,     idDataGroup)   ||
        isFieldUpdated (ifds::RuleType,      idDataGroup)   ||
		isFieldUpdated (ifds::FundGroup,     idDataGroup))
    {
        // validate against date,fund-class ruletype
        
        DString dstrEffectiveDate, dstrStopDate, dstrAcctControlsRID;

        getField( ifds::EffectiveDate,  dstrEffectiveDate,  idDataGroup,false );
        getField( ifds::StopDate,       dstrStopDate,       idDataGroup,false );
        getField( ifds::AcctControlsRID,dstrAcctControlsRID,idDataGroup,false );

        if ( dstrAccountNum.empty() )
        {
            MFCanBFCbo* pParentCBO      = dynamic_cast<MFCanBFCbo *>( getParent() );
            MFCanBFCbo* pGrandParentCBO = dynamic_cast<MFCanBFCbo *>( pParentCBO->getParent() );

            pGrandParentCBO->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
        }

        SEVERITY srvRet = 
            checkDuplicate( dstrAccountNum,
                            dstrFundCode,
                            dstrClassCode,
                            dstrRuleType,
                            dstrEffectiveDate,
                            dstrStopDate,
                            dstrAcctControlsRID,
							dstrFundGroup,
                            idDataGroup );

        if ( srvRet > WARNING )
        {
            ADDCONDITIONFROMFILE( CND::ERR_ACCT_CONTROL_EXISTS );
        }
    }

	validateTransTypePendingTrades (dstrAccountNum, dstrRuleType, dstrFundCode, dstrClassCode, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AcctLvlSttlmntRule::getField( const BFFieldId& idField,
                                   DString& strFieldValue,
                                   const BFDataGroupId& idDataGroup,
                                   bool formattedReturn ) const
{
    BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                     const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

    if (idField == ifds::FundCode || idField == ifds::ClassCode)
    {
        DString fundCode,classCode,fundNumber;

        getField (ifds::FundCode, fundCode, idDataGroup, false);
        getField (ifds::ClassCode, classCode, idDataGroup, false);
        if ( !fundCode.empty() && !classCode.empty())
        {
            getWorkSession ().GetFundNumber (fundCode, classCode, fundNumber);

            if ( !fundNumber.empty())
            {
                setFieldNoValidate ( ifds::FundNumber, fundNumber, idDataGroup, false, 
                                     true, 
                                     true, //notify
                                     false);
            }
            else
            {
            }

            // get default settle day with fund-class here
			fundClassRelatedChanges (fundCode, classCode, idDataGroup);
			setFieldNoValidate (ifds::FundGroup, I_( "" ), idDataGroup, false, false, true, false);
        } 
    }
    else if (idField == ifds::FundNumber)
    {
        DString fundNumber;

        getField (ifds::FundNumber, fundNumber, idDataGroup, false);
        if (!fundNumber.empty())
        {
            DString fundCode,classCode;

            if (getWorkSession ().GetFundClassCode (fundNumber, fundCode, classCode))
            {
                setField (ifds::FundCode, fundCode, idDataGroup, false, true);
                setField (ifds::ClassCode, classCode, idDataGroup, false, true);
            }
			setFieldNoValidate (ifds::FundGroup, I_( "" ), idDataGroup, false, false, true, false); 
        }
    }
    else if (idField == ifds::RuleType)
    {
        // get default settlement day for fund-class
    }
    else if (idField == ifds::SettleDays)
    {
        /*DString dstrRuleType;

        getField(ifds::RuleType,dstrRuleType,idDataGroup,false);

        if ( dstrRuleType == SETTLE_DAYS_ED || 
             dstrRuleType == SETTLE_DAYS_PW ||
             dstrRuleType == SETTLE_DAYS_TO ||
             dstrRuleType == SETTLE_DAYS_TI ||
             dstrRuleType == SETTLE_DAYS_EO ||
             dstrRuleType == SETTLE_DAYS_EI )
        {*/
            DString dstrSettleDays/*,dstrOverideChar*/;

			getField(ifds::SettleDays,dstrSettleDays,idDataGroup,false);
			if (!dstrSettleDays.empty())
			{
				setFieldNoValidate( ifds::OverrideAmt, dstrSettleDays, idDataGroup, false, true, true );
			}
        //}
    }
	else if (idField == ifds::FundGroup)
	{
		DString dstrFundGroup;
		getField (ifds::FundGroup, dstrFundGroup, idDataGroup);

		if (!dstrFundGroup.empty ())
		{
			// blank out fund number/fund/class.
			setFieldNoValidate( ifds::FundCode, I_( "" ), idDataGroup, false, false, true, false);			
			setFieldNoValidate( ifds::FundNumber, I_( "" ), idDataGroup, false, false, true, false);			
			setFieldNoValidate( ifds::ClassCode, I_( "" ), idDataGroup, false, false, true, false);		
		}
	}

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::fundClassRelatedChanges ( const DString &strFundCode, 
                                                       const DString &strClassCode, 
                                                       const BFDataGroupId &idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("fromFundClassRelatedChanges"));

    // do accquire default number settlement day from fund-class

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::validateClassCode ( const DString &strFundCode, 
                                                 const DString &strClassCode, 
                                                 const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateClassCode"));

    FundDetail *pFundDetail = NULL;

    if ( !strFundCode.empty() && !strClassCode.empty() &&
         !getWorkSession().getFundDetail( strFundCode, 
                                          strClassCode, 
                                          idDataGroup, 
                                          pFundDetail) ||
        !pFundDetail)
    {
        ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
    }

    return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::validateFundCode ( const DString &strFundCode, 
                                                const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("validateFundCode"));

    FundMasterList *pFundMasterList = NULL;

    if (!strFundCode.empty())
    {
        if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
            pFundMasterList)
        {
            FundMaster *pFundMaster = NULL;

            if ( pFundMasterList->getFundMaster( strFundCode, 
                                                 idDataGroup, 
                                                 pFundMaster) &&
                pFundMaster)
            {
                // actually it should have logic to validate fund code
                // but none for now
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::validateFundClass ( const DString &dstrFundCode, 
                                                 const DString &dstrClassCode, 
                                                 const DString &dstrAccountNum, 
                                                 const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"));

    DString dstrBrokerCode,dstrBranchCode,dstrAgentCode;

    getPurchaseRepInfoFields ( dstrBrokerCode, dstrBranchCode, dstrAgentCode, idDataGroup);

    DString dstrRuleType,dstrTransTypeForValidation;

    getField( ifds::RuleType,dstrRuleType,idDataGroup);

    if ( dstrRuleType == SETTLE_DAYS_ED )
    {
        dstrTransTypeForValidation = TRADETYPE::PURCHASE;
    }
    else if ( dstrRuleType == SETTLE_DAYS_PW)
    {
        dstrTransTypeForValidation = TRADETYPE::REDEMPTION;
    }
    else if ( dstrRuleType == SETTLE_DAYS_TO || 
              dstrRuleType == SETTLE_DAYS_TI )
    {
        dstrTransTypeForValidation = TRADETYPE::TRANSFER;
    }
    else if ( dstrRuleType == SETTLE_DAYS_TO || 
              dstrRuleType == SETTLE_DAYS_TI )
    {
        dstrTransTypeForValidation = TRADETYPE::EXCHANGE;
    }

    if ( canFundTrade( dstrBrokerCode,
                       dstrBranchCode,
                       dstrAgentCode,
                       dstrTransTypeForValidation,
                       dstrAccountNum,
                       dstrFundCode,
                       dstrClassCode,
                       CND::ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON,
                       CND::ERR_WARN_FUND_CLASS_PURCHASE_STOP_FLAG_ON,
                       idDataGroup,
                       true) <= WARNING)  //check broker permits 'AddPerm'
    {
    }

    return GETCURRENTHIGHESTSEVERITY ();
}

//***********************************************************************************
SEVERITY AcctLvlSttlmntRule::getPurchaseRepInfoFields ( DString &dstrBrokerCode, 
                                                        DString &dstrBranchCode, 
                                                        DString &dstrAgentCode, 
                                                        const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getPurchaseRepInfoFields"));

    getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup);
    getField (ifds::BranchCode, dstrBranchCode, idDataGroup);
    getField (ifds::Slsrep, dstrAgentCode, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::canFundTrade ( const DString &dstrBrokerCode,
                                            const DString &dstrBranchCode,
                                            const DString &dstrAgentCode,
                                            const DString &dstrTransType,
                                            const DString &dstrAccountNum,
                                            const DString &dstrFundCode,
                                            const DString &dstrClassCode,
                                            long lErrorId,
                                            long lWarnId,
                                            const BFDataGroupId &idDataGroup,
                                            bool bCheckBrokerPermits) /*=false*/ //flag is set to true by purchases/rollovers

{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canFundTrade"));

    MFAccount *pMFAccount = NULL;

    if ( getWorkSession().getMFAccount ( idDataGroup, 
                                        dstrAccountNum, 
                                        pMFAccount) <= WARNING && 
        pMFAccount)
    {
        DString brokerPermits;

        if (!dstrFundCode.empty() && !dstrClassCode.empty())
        {
            if ( validateBrokerFund ( dstrBrokerCode, 
                                      dstrTransType, 
                                      dstrAccountNum, 
                                      dstrFundCode, 
                                      dstrClassCode, 
                                      brokerPermits, //retrieve also the value of AddPerm, just in case
                                      idDataGroup) <= WARNING &&
                 validateAgentFund  ( dstrBrokerCode,
                                      dstrBranchCode,
                                      dstrAgentCode,
                                      dstrTransType, 
                                      dstrAccountNum, 
                                      dstrFundCode, 
                                      dstrClassCode, 
                                      idDataGroup) <= WARNING)
            {
            }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::validateBrokerFund ( const DString &dstrBrokerCode,
                                                  const DString &dstrTransType,
                                                  const DString &dstrAccountNum,
                                                  const DString &dstrFundCode, 
                                                  const DString &dstrClassCode, 
                                                  DString &dstrBrokerPermits,
                                                  const BFDataGroupId &idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("validateBrokerFund"));

    DString dstrFundAllowed (YES);
    DString dstrBrokerFund;

    dstrBrokerPermits = NO;
    getWorkSession ().getOption ( ifds::BrokerFund, dstrBrokerFund, BF::HOST, false);

    if ( dstrBrokerFund == YES   &&
        !dstrFundCode.empty()   &&
        !dstrClassCode.empty()  &&
        !dstrAccountNum.empty())
    {
        BrokerList brokerList (*this);

        if ( !dstrBrokerCode.empty() &&
             brokerList.initFundAllowed (dstrBrokerCode, dstrFundCode, dstrClassCode, dstrAccountNum, dstrTransType) <= WARNING)
        {
            BFObjIter bfIter (brokerList, idDataGroup);

            bfIter.begin ();
            if (!bfIter.end ())
            {
                bfIter.getObject()->getField (ifds::FundAllow, dstrFundAllowed, idDataGroup);
                bfIter.getObject()->getField (ifds::AddPerm, dstrBrokerPermits, idDataGroup);
                dstrFundAllowed.strip();
                dstrBrokerPermits.strip();
            }
        }
    }

    if ( !isBrokerAllowed ( dstrTransType, 
                            dstrAccountNum, 
                            dstrFundCode, 
                            dstrClassCode, 
                            idDataGroup) && 
        dstrFundAllowed != YES)
    {
        DString idiStr;

        addIDITagValue (idiStr, I_("FUND"), dstrFundCode);
        addIDITagValue (idiStr, I_("CLASS"), dstrClassCode);
        addIDITagValue (idiStr, I_("BROKER"), dstrBrokerCode);

        ADDCONDITIONFROMFILEIDI (CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER, idiStr);
    }

    return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool AcctLvlSttlmntRule::isBrokerAllowed ( const DString &dstrTransType,
                                           const DString &dstrAccountNum,
                                           const DString &dstrFundCode, 
                                           const DString &dstrClassCode,
                                           const BFDataGroupId &idDataGroup)
{
    return false;
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::validateAgentFund ( const DString &dstrBrokerCode,
                                                 const DString &dstrBranchCode,
                                                 const DString &dstrAgentCode,
                                                 const DString &dstrTransType,
                                                 const DString &dstrAccountNum,
                                                 const DString &dstrFundCode, 
                                                 const DString &dstrClassCode, 
                                                 const BFDataGroupId &idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateAgentFund"));

    DString dstrFundAllowed (YES);
    DString dstrFundEligSlsRepLvl;

    getWorkSession ().getOption ( ifds::FundEligSlsRepLvl, 
                                  dstrFundEligSlsRepLvl, 
                                  BF::HOST,
                                  false );

    if ( dstrFundEligSlsRepLvl == YES &&
        !dstrFundCode.empty()         &&
        !dstrClassCode.empty()        &&
        !dstrAccountNum.empty() )
    {
        AgentList agentList (*this);

        if ( !dstrBrokerCode.empty()  &&
            !dstrBranchCode.empty()  &&
            !dstrAgentCode.empty()   &&
            agentList.init2 ( dstrBrokerCode, 
                              dstrBranchCode, 
                              dstrAgentCode,
                              dstrFundCode, 
                              dstrClassCode, 
                              dstrAccountNum ) <= WARNING)
        {
            BFObjIter bfIter (agentList, idDataGroup);

            bfIter.begin ();
            if (!bfIter.end ())
            {
                bfIter.getObject()->getField (ifds::ValidationPassed, dstrFundAllowed, idDataGroup);
                dstrFundAllowed.strip();
            }
        }
    }

    if ( !isAgentAllowed (idDataGroup) && dstrFundAllowed != YES )
    {
        DString idiStr;

        addIDITagValue (idiStr, I_("FUND"), dstrFundCode );
        addIDITagValue (idiStr, I_("CLASS"), dstrClassCode );
        addIDITagValue (idiStr, I_("AGENT"), dstrAgentCode );
        ADDCONDITIONFROMFILEIDI (CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP, idiStr);
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AcctLvlSttlmntRule::isAgentAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::isEffectiveBroker( const DString& brokerCode, 
                                                const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isEffectiveBroker" ) );

    BrokerList brokerList ( *this );

    //checks for the validity of the broker code. by making a view call, and raising a condition
    //we do not want to make the view call when the broker code is NULL, because the view will
    //return us all the brokers
    if( brokerCode != NULL_STRING && 
        // 'L' for the request type will do a search for broker by code
        brokerList.init( brokerCode, NULL_STRING, I_( "L" ) ) <= WARNING )
    {
        BFObjIter bfIter( brokerList, idDataGroup );
        DString dstrStopDate;
        if( !bfIter.end() )
        {
            DString dstrBrokerName;
            Broker* pBroker = dynamic_cast <Broker*> (bfIter.getObject());
            pBroker->getField( ifds::BrokerName, dstrBrokerName, idDataGroup );

            DString dstrEffectiveDate;
            getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
            pBroker->checkEffective ( dstrEffectiveDate, idDataGroup );
        }
    }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::isEffectiveBranches( const DString& branchCode, 
                                                  const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isEffectiveBranches" ) );

    BranchList branchList ( *this );
    DString brokerCode;

    getField( ifds::AgencyCode, brokerCode, idDataGroup );
    //checks for the validity of the branch code. by making a view call, and raising a condition
    //we do not want to make the view call when the branch code is NULL, because the view will
    //return us all the branches for this broker
    if( branchCode != NULL_STRING && 
        branchList.init( brokerCode, branchCode ) <= WARNING )
    {
        BFObjIter bfIter( branchList, idDataGroup );
        DString dstrBranchName;
        if( !bfIter.end() )
        {
            Branch* pBranch = dynamic_cast <Branch*> ( bfIter.getObject() );
            DString dstrEffectiveDate;
            getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
            pBranch->getField( ifds::BranchName, dstrBranchName, idDataGroup );
            pBranch->checkEffective ( dstrEffectiveDate, idDataGroup );
        }
    }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::isEffectiveAgents( const DString& slsrepCode, 
                                                const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isEffectiveAgents" ) );

    AgentList agentList( *this );
    DString dstrBrokerCode, dstrBranchCode;

    getField( ifds::AgencyCode, dstrBrokerCode, idDataGroup );
    if( isSlsRepByBranch ( idDataGroup ) )
        getField( ifds::BranchCode, dstrBranchCode, idDataGroup );
    else
        dstrBranchCode = NULL_STRING;

    //checks for the validity of the agent code. by making a view call, and raising a condition
    //we do not want to make the view call when the slslrep code is NULL, because the view will
    //return us all the agents for this broker and branch
    if( slsrepCode != NULL_STRING && 
        agentList.init( dstrBrokerCode, dstrBranchCode, slsrepCode ) <= WARNING )
    {
        BFObjIter bfIter( agentList, idDataGroup );
        DString dstrSlsrepName, dstrSlsrepAltName;
        DString dstrBranchName, dstrBrokerName;
        if( !bfIter.end() )
        {
            Agent* pAgent = dynamic_cast <Agent*> ( bfIter.getObject() );
            pAgent->getField( ifds::SlsrepName, dstrSlsrepName, idDataGroup );
            pAgent->getField( ifds::BranchCode, dstrBranchCode, idDataGroup );
            pAgent->getField( ifds::BranchName, dstrBranchName, idDataGroup );
            DString dstrEffectiveDate;
            getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
            pAgent->checkEffective ( dstrEffectiveDate, idDataGroup );
        }
    }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctLvlSttlmntRule::isSlsRepByBranch ( const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isSlsRepByBranch" ) );

    DString dstrSalesRepByBranch;
    getWorkSession().getOption( ifds::RepByBranch, dstrSalesRepByBranch, idDataGroup );

    return( dstrSalesRepByBranch == YES );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::checkDuplicate( const DString &dstrAccountNum,
                                             const DString &dstrFundCode,
                                             const DString &dstrClassCode,
                                             const DString &dstrRuleType,
                                             const DString &dstrEffectiveDate,
                                             const DString &dstrStopDate,
											 const DString &dstrAcctControlsRID,
											 const DString &dstrFundGroup,
                                             const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );

    if ( dstrAccountNum.empty()    || dstrRuleType.empty() ||
         dstrEffectiveDate.empty() || dstrStopDate.empty() )
    {
        // value inside acccount, rule type, effective date and stop date 
        // field must not be blank
        assert(0);
    }

    // if this is new record adding to list skip for duplication checking
    if ( isNewRecordCheck( dstrAcctControlsRID ) )
    {
        return( GETCURRENTHIGHESTSEVERITY() );
    }

    AcctSettlementRuleDuplicationCheck *pDuplicationCheck = NULL;

    if ( getDuplicationCheck ( pDuplicationCheck,
                               dstrAccountNum,
                               dstrFundCode,
                               dstrClassCode,
                               dstrRuleType,
                               dstrEffectiveDate,
                               dstrStopDate,
                               dstrAcctControlsRID,
							   dstrFundGroup,
                               idDataGroup ) <= WARNING && pDuplicationCheck )
    {
        DString dstrDuplicateExist;

        pDuplicationCheck->getField( ifds::DuplicateExist, dstrDuplicateExist, idDataGroup, false );
    }

    return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::validateRuleFundClass( const DString &dstrFundCode,
                                                    const DString &dstrClassCode,
                                                    const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRuleFundClass" ) );

    DString dstrAccountNum,dstrRuleType;
    DString dstrEffectiveDate,dstrStopDate;
    DString dstrAcctControlsRID, dstrFundGroup;

    getField( ifds::AccountNum,     dstrAccountNum,     idDataGroup,false );
    getField( ifds::RuleType,       dstrRuleType,       idDataGroup,false );
    getField( ifds::EffectiveDate,  dstrEffectiveDate,  idDataGroup,false );
    getField( ifds::StopDate,       dstrStopDate,       idDataGroup,false );
    getField( ifds::AcctControlsRID,dstrAcctControlsRID,idDataGroup,false );
	getField( ifds::FundGroup,      dstrFundGroup,      idDataGroup,false ); 

    dstrAccountNum.strip().upperCase();
    dstrRuleType.strip().upperCase();
    dstrEffectiveDate.strip().upperCase();
    dstrStopDate.strip().upperCase();

    if ( !dstrAccountNum.empty()    && !dstrRuleType.empty()   && 
         !dstrEffectiveDate.empty() && !dstrStopDate.empty() 
       )
    {
        SEVERITY srvRet = NO_CONDITION;

        if ( !dstrFundCode.empty() && !dstrClassCode.empty() )
        {
            validateClassCode (dstrFundCode, dstrClassCode, idDataGroup);
        }

        srvRet = checkDuplicate( dstrAccountNum,
                                 dstrFundCode,
                                 dstrClassCode,
                                 dstrRuleType,
                                 dstrEffectiveDate,
                                 dstrStopDate,
                                 dstrAcctControlsRID,
								 dstrFundGroup,
                                 idDataGroup );

        if ( srvRet > WARNING )
        {
            ADDCONDITIONFROMFILE( CND::ERR_ACCT_CONTROL_EXISTS );

            return ( srvRet );
        }
    }

    return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
void AcctLvlSttlmntRule::setFieldsReadOnly( const BFDataGroupId& idDataGroup, bool bReadOnly  )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFieldsReadOnly" ));

    setFieldReadOnly( ifds::RuleType,   idDataGroup, bReadOnly );
    setFieldReadOnly( ifds::FundCode,   idDataGroup, bReadOnly );
    setFieldReadOnly( ifds::FundNumber, idDataGroup, bReadOnly );
    setFieldReadOnly( ifds::ClassCode,  idDataGroup, bReadOnly );
	setFieldReadOnly( ifds::FundGroup,  idDataGroup, bReadOnly );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::getDuplicationCheck( AcctSettlementRuleDuplicationCheck *&pDuplicationCheck,
                                                  const DString &dstrAccountNum,
                                                  const DString &dstrFundCode,
                                                  const DString &dstrClassCode,
                                                  const DString &dstrRuleType,
                                                  const DString &dstrEffectiveDate,
                                                  const DString &dstrStopDate,
                                                  const DString &dstrAcctControlsRID,
												  const DString &dstrFundGroup,
												  const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDuplicationCheckObj" ));

    DString strKey;

    AcctSettlementRuleDuplicationCheck::buildKey( strKey,
                                                  dstrAccountNum,
                                                  dstrRuleType,
                                                  dstrFundCode,
                                                  dstrClassCode,
                                                  dstrEffectiveDate,
                                                  dstrStopDate,
                                                  dstrAcctControlsRID,
												  dstrFundGroup
                                                 );

    pDuplicationCheck = 
        dynamic_cast<AcctSettlementRuleDuplicationCheck*> ( getObject ( strKey, idDataGroup ) );

    if (!pDuplicationCheck)
    {
        pDuplicationCheck = new AcctSettlementRuleDuplicationCheck(*this);

        if ( pDuplicationCheck->init( dstrAccountNum,
                                      dstrRuleType,
                                      dstrFundCode,
                                      dstrClassCode,
                                      dstrEffectiveDate,
                                      dstrStopDate,
                                      dstrAcctControlsRID,
									  dstrFundGroup) <= WARNING )
        {
            setObject ( pDuplicationCheck, strKey, OBJ_ACTIVITY_NONE, idDataGroup );
        }
		else
		{
			delete pDuplicationCheck;
			pDuplicationCheck = NULL;
		}
    }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctLvlSttlmntRule::isNewRecordCheck( const DString &dstrAcctControlsRID )
{
    double dAcctControlsRID = DSTCommonFunctions::convertToDouble(dstrAcctControlsRID);
    int iAcctControlsRID = (int)dAcctControlsRID;

    return  ( iAcctControlsRID == 0)?true:false;
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::validateTransTypePendingTrades ( const DString &dstrAccountNum,
															  const DString &dstrRuleType,
															  const DString &dstrFundCode,
															  const DString &dstrClassCode,
															  const BFDataGroupId &idDataGroup) 

{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTransTypePendingTrades"));

    DString dstrTransTypeForValidation;
	MFAccount *pMFAccount = NULL;

    if ( dstrRuleType == SETTLE_DAYS_ED )
    {
        dstrTransTypeForValidation = TRADETYPE::PURCHASE;
    }
    else if ( dstrRuleType == SETTLE_DAYS_PW)
    {
        dstrTransTypeForValidation = TRADETYPE::REDEMPTION;
    }
    else if ( dstrRuleType == SETTLE_DAYS_TO )
    {
        dstrTransTypeForValidation = TRADETYPE::TRANSFER_OUT;
    }
	else if ( dstrRuleType == SETTLE_DAYS_TI )
    {
        dstrTransTypeForValidation = TRADETYPE::TRANSFER_IN;
    }  
	else if ( dstrRuleType == SETTLE_DAYS_EO )
    {
        dstrTransTypeForValidation = TRADETYPE::EXCHANGE_OUT;
    }
	else if ( dstrRuleType == SETTLE_DAYS_EI )
    {
        dstrTransTypeForValidation = TRADETYPE::EXCHANGE_IN;
    }

	if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
	{
		if (pMFAccount->hasTransTypePendingTrades (dstrTransTypeForValidation, dstrAccountNum, dstrFundCode, dstrClassCode, idDataGroup))
		{
			getErrMsg( IFASTERR::SETTLEMENT_RULE_PENDING_TRADE_EXISTS, 
					   CND::ERR_SETTLEMENT_RULE_PENDING_TRADE_EXISTS, 
					   CND::WARN_SETTLEMENT_RULE_PENDING_TRADE_EXISTS,
					   idDataGroup);
		}
	}

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRule::validateFundLevelSettleDays(const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundLevelSettleDays"));

	DString dstrFundCode,dstrClassCode, dstrSettleDays, dstrStartDate, dstrRuleType, dstrAccountNum;
	getField ( ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	getField ( ifds::FundCode, dstrFundCode, idDataGroup, false );
	getField ( ifds::ClassCode, dstrClassCode, idDataGroup, false );
	getField ( ifds::SettleDays, dstrSettleDays, idDataGroup, false );
	getField ( ifds::EffectiveDate, dstrStartDate, idDataGroup, true );
	
	getField( ifds::RuleType, dstrRuleType, idDataGroup, false);
	DString dstrTransType;
	if ( dstrRuleType == SETTLE_DAYS_ED )
	{
		dstrTransType = TRADETYPE::PURCHASE;
	}
	else if ( dstrRuleType == SETTLE_DAYS_PW)
	{
		dstrTransType = TRADETYPE::REDEMPTION;
	}
	else if ( dstrRuleType == SETTLE_DAYS_TO )
	{
		dstrTransType = TRADETYPE::TRANSFER_OUT;
	}
	else if ( dstrRuleType == SETTLE_DAYS_TI )
	{
		dstrTransType = TRADETYPE::TRANSFER_IN;
	}  
	else if ( dstrRuleType == SETTLE_DAYS_EO )
	{
		dstrTransType = TRADETYPE::EXCHANGE_OUT;
	}
	else if ( dstrRuleType == SETTLE_DAYS_EI )
	{
		dstrTransType = TRADETYPE::EXCHANGE_IN;
	}

	getFundLevelSettleDays( dstrAccountNum,
							dstrFundCode,
							dstrClassCode,
							dstrTransType,
							dstrSettleDays,
							dstrStartDate,
							idDataGroup);

	return GETCURRENTHIGHESTSEVERITY ();

}
//******************************************************************************
SEVERITY AcctLvlSttlmntRule::getFundLevelSettleDays( const DString &dstrAccountNum,
									 const DString &dstrFundCode,
									 const DString &dstrClassCode,
		                             const DString &dstrTransType,
									 const DString &dstrSettleDays,
									 const DString &dstrStartDate,
									 const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundLevelSettleDays"));

	AcctFundLevelSettleDays *pAcctFundLevelSettleDays = NULL;

	DString strKey;
	pAcctFundLevelSettleDays->buildKey( strKey,
										dstrAccountNum,
										dstrFundCode,
										dstrClassCode,
										dstrTransType,
										dstrSettleDays,
										dstrStartDate);

	pAcctFundLevelSettleDays = dynamic_cast <AcctFundLevelSettleDays*>( getObject(strKey,idDataGroup));
      if (!pAcctFundLevelSettleDays)
      {
         pAcctFundLevelSettleDays = new AcctFundLevelSettleDays (*this);
         if ( pAcctFundLevelSettleDays->init ( dstrAccountNum, 
                                        dstrFundCode, 
                                        dstrClassCode, 
                                        dstrTransType, 
                                        dstrSettleDays,
                                        dstrStartDate ) <= WARNING )
         {
            setObject (pAcctFundLevelSettleDays, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
         }
         else
         {
            delete pAcctFundLevelSettleDays;
            pAcctFundLevelSettleDays = NULL;
         }
      }
      if (pAcctFundLevelSettleDays)
      {
         pAcctFundLevelSettleDays->addConditions ();
      }

   return GETCURRENTHIGHESTSEVERITY ();

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementRule.cpp-arc  $ */
// 
//    Rev 1.3   May 28 2008 15:37:54   daechach
// in#1292387 - Cannot enter Account Level settlement override of T+0.
// 
//    Rev 1.2   May 28 2008 15:29:36   daechach
// in#1268139 - Red Cross displays required only in Stop Date field.
// 
//    Rev 1.1   Apr 16 2008 18:47:20   daechach
// PET2385 FN02&07 - Modified code regarding code review.
//
//   Rev 1.0   Mar 11 2008 19:59:52   daechach
// Initial revision.
