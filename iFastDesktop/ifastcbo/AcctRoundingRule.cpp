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
// ^FILE   : AcctRoundingRule.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcctRoundingRule
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "AcctRoundingRule.hpp"
#include "ErrMsgRulesList.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "mfaccount.hpp"

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0481_req.hpp>
#include <ifastdataimpl\dse_dstc0481_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0481_vw.hpp>

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ACCT_ROUNDING_RULE_UPDATE;
};

namespace 
{
    const I_CHAR * const CLASSNAME					= I_("AcctRoundingRule");
	const I_CHAR * const BLANK_SUBSTITUTION_VALUE	= I_("= ;");
};

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId NotApplicable;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId Username;
	extern CLASS_IMPORT const BFDateFieldId ModDate;
	extern CLASS_IMPORT const BFTextFieldId ModUser;
};

namespace CND
{      
	extern const long ERR_ACCOUNT_ROUNDING_RULE_MANDATORY;
	extern const long WARN_ACCOUNT_ROUNDING_RULE_MANDATORY;
	extern const long ERR_ACCOUNT_ROUNDING_RULE_TRADE_EXISTS;
	extern const long WARN_ACCOUNT_ROUNDING_RULE_TRADE_EXISTS;
}

namespace IFASTERR
{  	
	extern CLASS_IMPORT I_CHAR * const ACCOUNT_ROUNDING_RULE_MANDATORY;
	extern CLASS_IMPORT I_CHAR * const ACCOUNT_ROUNDING_RULE_TRADE_EXISTS;	
}

extern BF_OBJ_TYPE OBJ_TYPE_ACCT_ROUNDING_RULE;

//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
    // Field DD Id,                         State Flags,            Group Flags
    { ifds::AccountNum,                     BFCBO::NONE,                  0 },	
    { ifds::RoundFlg,                       BFCBO::NONE,                  0 },  
    { ifds::RecalcMthd,                     BFCBO::NONE,                  0 },
	{ ifds::UnitsPrecisionAcct,				BFCBO::NONE,                  0 },
	{ ifds::StartDate,						BFCBO::NONE,                  0 },
	{ ifds::StopDate,						BFCBO::NONE,                  0 },   
    { ifds::Username,                       BFCBO::NONE,                  0 },
    { ifds::ModUser,                        BFCBO::NONE,                  0 },
    { ifds::ModDate,                        BFCBO::NONE,                  0 },
	{ ifds::AcctRndRulesUUID,               BFCBO::NONE,                  0 },	
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


AcctRoundingRule::AcctRoundingRule (BFAbstractCBO &parent)
: MFCanBFCbo( parent ),
_pErrMsgRulesList( NULL )
{
    TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );  
    registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
    _dstrAccountNum = NULL_STRING;   
}

//******************************************************************************
AcctRoundingRule::~AcctRoundingRule(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctRoundingRule::initNew( const DString& accountNum, 
                                    const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew" )); 

    setFieldNoValidate( ifds::AccountNum, accountNum, idDataGroup );
    commonInit( idDataGroup );

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctRoundingRule::init( const BFData& data )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init" ));

    attachDataObject(const_cast<BFData&>( data ), false); 
    commonInit( BF::HOST );	

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctRoundingRule::commonInit ( const BFDataGroupId &idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit")) ;

	DString dstrAccountNum;     	

	getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
    if ( dstrAccountNum.empty() )
    {
        MFCanBFCbo* pGrandParentCBO = dynamic_cast<MFCanBFCbo *>( getParent()->getParent() );

        pGrandParentCBO->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
        setFieldNoValidate( ifds::AccountNum, dstrAccountNum, idDataGroup, false, true, true);
    } 

	addBlankToSubSet(ifds::RoundFlg, idDataGroup ); // D-Round Down, M-Mathematical Rounding, U-Round Up
	addBlankToSubSet(ifds::RecalcMthd, idDataGroup ); // FUL-Full Recalculation, PAR-Partial Recalculation, NO-No recalculation
	addBlankToSubSet(ifds::UnitsPrecisionAcct, idDataGroup ); // 0,1,2,3,4

	setFieldReadOnly (ifds::StartDate, idDataGroup, true);
	setFieldReadOnly (ifds::StopDate, idDataGroup, true);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctRoundingRule::getErrMsg( DString dstrErrNum, 
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
void AcctRoundingRule::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{   
	DString dstrStopDate;
			
    clearUpdatedFlags( idDataGroup, true );
    
	getWorkSession().getOption( ifds::CurrBusDate, _dstrCurrentBusinessDate, BF::HOST, false );
    getWorkSession().getDateInHostFormat( dstrStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup );

	setFieldNoValidate (ifds::RoundFlg, I_(""), idDataGroup, false);
	setFieldNoValidate (ifds::RecalcMthd, I_(""), idDataGroup, false);
	setFieldNoValidate (ifds::UnitsPrecisionAcct, I_(""), idDataGroup, false);
    setFieldNoValidate( ifds::StartDate, _dstrCurrentBusinessDate, idDataGroup, false, true, true);
    setFieldNoValidate( ifds::StopDate, dstrStopDate, idDataGroup, false, true, true );   
}

//******************************************************************************
SEVERITY AcctRoundingRule::doValidateField( const BFFieldId& idField, 
                                            const DString& strValue, 
                                            const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));
  
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctRoundingRule::doValidateAll( const BFDataGroupId& idDataGroup, 
                                          long lValidateGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll" ));

	DString dstrAccountNum;	
	getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );	

	validatePendingOrProcessedTrades (dstrAccountNum, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AcctRoundingRule::getField( const BFFieldId& idField,
                                 DString& strFieldValue,
                                 const BFDataGroupId& idDataGroup,
                                 bool formattedReturn ) const
{
    BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
}

//******************************************************************************
SEVERITY AcctRoundingRule::doApplyRelatedChanges( const BFFieldId &idField, 
                                                  const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
    
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctRoundingRule::validateAccountRoundingRule( const BFDataGroupId &idDataGroup ) 
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAccountRoundingRule"));

	DString dstrRoundFlg, dstrRecalcMthd, dstrUnitsPrecisionAcct;	

	getField( ifds::RoundFlg, dstrRoundFlg, idDataGroup, false ); 
	getField( ifds::RecalcMthd,	dstrRecalcMthd, idDataGroup, false ); 
	getField( ifds::UnitsPrecisionAcct, dstrUnitsPrecisionAcct, idDataGroup, false ); 	

	dstrRoundFlg.strip().upperCase();
	dstrRecalcMthd.strip().upperCase();
	dstrUnitsPrecisionAcct.strip().upperCase();

	if (dstrRoundFlg.empty() || dstrRecalcMthd.empty() || dstrUnitsPrecisionAcct.empty())
	{
		// 1954 - Account rounding rules are mandatory.
		getErrMsg( IFASTERR::ACCOUNT_ROUNDING_RULE_MANDATORY, 
				   CND::ERR_ACCOUNT_ROUNDING_RULE_MANDATORY, 
				   CND::WARN_ACCOUNT_ROUNDING_RULE_MANDATORY,
				   idDataGroup);
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AcctRoundingRule::validatePendingOrProcessedTrades( const DString &dstrAccountNum,															   
															 const BFDataGroupId &idDataGroup) 

{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatePendingOrProcessedTrades"));
   
	MFAccount *pMFAccount = NULL;

	// cannot add or modify the rule if there is a good pending or processed trade in the account 
	if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount && !pMFAccount->isNew())
	{
		if (pMFAccount->hasTransTypePendingTrades (NULL_STRING, dstrAccountNum, NULL_STRING, NULL_STRING, idDataGroup) ||
			pMFAccount->hasTransTypeProccessedTrades (NULL_STRING, dstrAccountNum, NULL_STRING, NULL_STRING, idDataGroup) )
		{
			// 1961 - Pending or processed trade exists, account rounding rule cannot be added/modified.
			getErrMsg( IFASTERR::ACCOUNT_ROUNDING_RULE_TRADE_EXISTS, 
					   CND::ERR_ACCOUNT_ROUNDING_RULE_TRADE_EXISTS, 
					   CND::WARN_ACCOUNT_ROUNDING_RULE_TRADE_EXISTS,
					   idDataGroup);
		}
	}

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AcctRoundingRule::addBlankToSubSet( const BFFieldId &idField,
											 const BFDataGroupId &idDataGroup, 
											 bool dstrUseNotApplicableAsDesc /*= false */ )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
		CLASSNAME, 
		I_("addBlankToSubSet"));

	DString  dstrCurrSubList,dstrSubList;
	BFProperties *pBFProperties = getFieldProperties (idField, idDataGroup); 
	assert (pBFProperties);
	if (pBFProperties) 
	{
		pBFProperties->getAllSubstituteValues (dstrCurrSubList);
		DString dstrNotApplicableLangDesc;
		BFProperties *pBFPropertiesNotApplicable = getFieldProperties (ifds::NotApplicable, idDataGroup);
		pBFPropertiesNotApplicable->getDefaultValue(dstrNotApplicableLangDesc);
		pBFPropertiesNotApplicable->formatValue( ifds::NotApplicable,dstrNotApplicableLangDesc, true );
		dstrNotApplicableLangDesc = dstrUseNotApplicableAsDesc ? ( I_(" =") + dstrNotApplicableLangDesc + I_(";")): BLANK_SUBSTITUTION_VALUE;

		I_CHAR *temp = const_cast<I_CHAR*> (dstrCurrSubList.c_str ());
		bool blankNotAdded = true;
		do
		{
			DString dstrCode, dstrDescr;
			temp = parseIdiString (temp, dstrCode, dstrDescr );
			//if already in do not add again...
			if (dstrCode == I_(" "))
			{
				blankNotAdded = false;
				break;
			}
		} while (temp && temp != NULL_STRING && *temp);

		if(blankNotAdded)
		{
			dstrSubList = dstrNotApplicableLangDesc  + dstrCurrSubList;
			pBFProperties->setAllSubstituteValues( dstrSubList ); 
		}   
	} 

	return GETCURRENTHIGHESTSEVERITY();
}


