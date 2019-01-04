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
// ^FILE   : EntityRisk.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : EntityRisk
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EntityRisk.hpp"
#include "EntityRiskList.hpp"
#include "translationtable.hpp"

#include <bfutil\bfdate.hpp>
#include "Entity.hpp"
#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_country_of_exposure_is_required.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_country_of_exposure_is_required.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_country_of_expr_is_required.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_country_of_expr_is_required.h>

namespace
{
    const I_CHAR * const CLASSNAME				= I_("EntityRisk");
    const I_CHAR * const APPL_FOR_CNTRY_ISSUE   = I_("3,6,7,8");
    const I_CHAR * const GROUPCODE_RISK_LEVEL   = I_( "RK" );
    const I_CHAR * const UNASSIGNED_COUNTRY     = I_( "0000" );
    const I_CHAR * const EFFECTIVE_DATE_APPL_LIST = I_("6,7,8");
}

namespace ifds
{
    extern CLASS_IMPORT const BFNumericFieldId EntityId;
    extern CLASS_IMPORT const BFTextFieldId RiskLevel;
    extern CLASS_IMPORT const BFTextFieldId CountryOfExposure;
    extern CLASS_IMPORT const BFTextFieldId RiskDetlUUID;
    extern CLASS_IMPORT const BFTextFieldId HighestRiskLevel;
    extern CLASS_IMPORT const BFTextFieldId RiskLevelRanking;
    extern CLASS_IMPORT const BFTextFieldId HighRiskLevels;
    extern CLASS_IMPORT const BFTextFieldId EntityRiskLevel;
    extern CLASS_IMPORT const BFTextFieldId WhereUse;
    extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
    extern CLASS_IMPORT const BFDateFieldId StopDate;
    extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
}

namespace CND
{  
}

namespace IFASTERR
{
    extern CLASS_IMPORT I_CHAR * const COUNTRY_OF_EXPOSURE_IS_REQUIRED;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    //  Field DD Id,              State Flags,    Group Flags 
    {ifds::RiskLevel,           BFCBO::REQUIRED,    	0 }, 
    {ifds::CountryOfExposure,   BFCBO::NONE,    	    0 }, 
    {ifds::RiskDetlUUID,        BFCBO::NONE,    	    0 }, 
    {ifds::EffectiveDate,       BFCBO::NONE,    	    0 }, 
    {ifds::StopDate,            BFCBO::NONE,    	    0 },  
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
EntityRisk::EntityRisk (BFAbstractCBO &parent) :
    MFCanBFCbo (parent)
{
    TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

    registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}


//****************************************************************************
EntityRisk::~EntityRisk()
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY EntityRisk::commonInit(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "commonInit" ) );

    DString dstrRiskLevel;
    getField(ifds::RiskLevel, dstrRiskLevel, idDataGroup);
    setFieldReadOnly(ifds::CountryOfExposure, idDataGroup, !DSTCommonFunctions::codeInList(dstrRiskLevel, APPL_FOR_CNTRY_ISSUE));

    return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRisk::init (const BFData &data)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

    attachDataObject( const_cast<BFData&>(data), false, true );
    initializeSubstitutionList (ifds::RiskLevel, GROUPCODE_RISK_LEVEL, BF::HOST);

    commonInit(BF::HOST);

    return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRisk::initNew (const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

    setFieldNoValidate(ifds::RiskDetlUUID, dynamic_cast<EntityRiskList*>(getParent())->getNewUUID(), idDataGroup, false, true);
    initializeSubstitutionList (ifds::RiskLevel, GROUPCODE_RISK_LEVEL, idDataGroup);
    
    commonInit(idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void EntityRisk::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
    DString dstrCurrBusDate;
    getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

    setFieldNoValidate(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false, false, true, false);
    setFieldNoValidate(ifds::StopDate, I_("12319999"), idDataGroup, false, false, true, false);
}


//********************************************************************************************
SEVERITY EntityRisk::doValidateField(const BFFieldId& idField,
                                     const DString& strValue,
                                     const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

    if (idField == ifds::CountryOfExposure )
    {
        DString strRiskLevel, strCountryOfExposure(strValue);

        getField( ifds::RiskLevel, strRiskLevel, idDataGroup, false );
        strRiskLevel.strip().upperCase();
        strCountryOfExposure.strip().upperCase();

        if (DSTCommonFunctions::codeInList(strRiskLevel, APPL_FOR_CNTRY_ISSUE) &&
            (strCountryOfExposure.empty() || strCountryOfExposure == UNASSIGNED_COUNTRY)) 
        {
            if (strRiskLevel == I_("3"))
            {
                CND::CIFast_IFast_ifastcbo_warn_country_of_exposure_is_required warnCond;
                CND::CIFast_IFast_ifastcbo_err_country_of_exposure_is_required errCond;

                getErrMsg(IFASTERR::COUNTRY_OF_EXPOSURE_IS_REQUIRED,
                          errCond,
                          warnCond,
                          idDataGroup);
            }
            else
            {
                DString idiString, riskDesc;
                CND::CIFast_IFast_ifastcbo_warn_country_of_expr_is_required warnCond;
                CND::CIFast_IFast_ifastcbo_err_country_of_expr_is_required errCond;

                getField(ifds::RiskLevel, riskDesc, idDataGroup, true);
                addIDITagValue(idiString, I_("RISK_TYPE"), riskDesc); 

                getErrMsg(IFASTERR::COUNTRY_OF_EXPOSURE_IS_REQUIRED,
                          errCond,
                          warnCond,
                          idDataGroup,
                          idiString);
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}


//********************************************************************************************
SEVERITY EntityRisk::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

    return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRisk::doApplyRelatedChanges(const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

    if (idField == ifds::RiskLevel)
    {
        DString dstrRiskLevel;
        getField(ifds::RiskLevel, dstrRiskLevel, idDataGroup, false);
        
        if (DSTCommonFunctions::codeInList(dstrRiskLevel, APPL_FOR_CNTRY_ISSUE))
        {
            setFieldValid(ifds::CountryOfExposure, idDataGroup, false);
            setFieldReadOnly(ifds::CountryOfExposure, idDataGroup, false);
        }
        else
        {
            setFieldNoValidate(ifds::CountryOfExposure, NULL_STRING, idDataGroup, false, false, true);
            setFieldReadOnly(ifds::CountryOfExposure, idDataGroup, true);
        }

        if (!DSTCommonFunctions::codeInList(dstrRiskLevel, EFFECTIVE_DATE_APPL_LIST)) //Reset to default date
        {
            DString dstrCurrBusDate;
            getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

            setFieldNoValidate(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false, false, true, false);
            setFieldNoValidate(ifds::StopDate, I_("12319999"), idDataGroup, false, false, true, false);
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void EntityRisk::initializeSubstitutionList(const BFFieldId& idField, 
                                            const DString &dstrGroupCode, 
                                            const BFDataGroupId& idDataGroup)
{
   TranslationTable* pTranslationTable = NULL;
   DString dstrSubstitutionList;

   getMgmtCo().getTranslationTable (dstrGroupCode, pTranslationTable);

   if (pTranslationTable)
   {
      pTranslationTable->getSubstitutionList(dstrSubstitutionList);
      setFieldAllSubstituteValues(idField, idDataGroup, dstrSubstitutionList);
   }
}

//******************************************************************************
void EntityRisk::setAllFieldReadOnly(bool isReadonly, const BFDataGroupId &idDataGroup)
{
    const CLASS_FIELD_INFO* pClassFieldInfo = (const CLASS_FIELD_INFO *)&classFieldInfo;

    for (int i = 0; i < NUM_FIELDS; i++, pClassFieldInfo++)
    {
        setFieldReadOnly(pClassFieldInfo->m_fieldId, idDataGroup, isReadonly);
    }  

    DString dstrRiskLevel;
    getField(ifds::RiskLevel, dstrRiskLevel, idDataGroup);
    setFieldReadOnly(ifds::CountryOfExposure, idDataGroup, isReadonly || !DSTCommonFunctions::codeInList(dstrRiskLevel, APPL_FOR_CNTRY_ISSUE));
}

//******************************************************************************
bool EntityRisk::effectiveDateApplicable(const BFDataGroupId &idDataGroup)
{
    DString dstrRiskLevel;
    getField(ifds::RiskLevel, dstrRiskLevel, idDataGroup);

    return DSTCommonFunctions::codeInList(dstrRiskLevel, EFFECTIVE_DATE_APPL_LIST);
}