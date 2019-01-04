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
//    Copyright 2002 by International Financial
//
//
//******************************************************************************
//
// ^FILE   : FeeThrshldSys.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 08, 2002
//
// ^CLASS    : FeeThrshldSys
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeThrshldSys.hpp"
#include "FeeThrshldSysList.hpp"
#include "FeeParamSys.hpp"
#include <bfcbo\bfobjiter.hpp>
#include "fundfeelist.hpp"
#include <ifastdataimpl\dse_dstc0231_vw.hpp>
#include <ifastdataimpl\dse_dstc0197_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "feescalesyslist.hpp"

#include "feeparamconfiglist.hpp"
#include "feeparamconfig.hpp"



namespace CND
{  // Conditions used
	extern const long ERR_RATE_IS_OUT_OF_RANGE;
	extern const long ERR_RATE_LESS_THAN_MIN;
}

namespace  
{
   const I_CHAR * const CLASSNAME		= I_( "FeeThrshldSys" );
   const I_CHAR * const IDI_RATE		= I_("RATE");
   const I_CHAR * const IDI_MIN_RATE	= I_("MINRATE");
   const I_CHAR * const IDI_MAX_RATE	= I_("MAXRATE");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId    RecType;
   extern CLASS_IMPORT const BFIntegerFieldId ThrshldRangeID;
   extern CLASS_IMPORT const BFDecimalFieldId ThrshldUpper;
   extern CLASS_IMPORT const BFDecimalFieldId ThrshldLower;
   extern CLASS_IMPORT const BFIntegerFieldId ThrshldLevel;
   extern CLASS_IMPORT const BFTextFieldId UpdateRule;
   extern CLASS_IMPORT const BFDateFieldId FMLastProcDate;
}


//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::RecType,			      BFCBO::NONE, 0 }, 
   { ifds::ThrshldRangeID,			BFCBO::NONE, 0 }, 
   { ifds::ThrshldUpper,         BFCBO::NONE, 0 }, 
   { ifds::ThrshldLower,         BFCBO::NONE, 0 }, 
   { ifds::ThrshldLevel,         BFCBO::NONE, 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FeeThrshldSys::FeeThrshldSys( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, localData(0)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

}
//------------------------------------------------------------------------
FeeThrshldSys::~FeeThrshldSys()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete localData;
}     
//------------------------------------------------------------------------------------
SEVERITY FeeThrshldSys::init( const BFData& InstData, bool bDefault )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData& )" ) );
   localData = new BFData(InstData);
   attachDataObject( const_cast<BFData&>(*localData), false, true );
   
   bool bReadOnly = isThresholdReadOnly(BF::HOST);

   setFieldReadOnly(ifds::ThrshldUpper, BF::HOST,bReadOnly);
   setFieldReadOnly(ifds::ThrshldLower, BF::HOST,bReadOnly);   
   setFieldReadOnly(ifds::ThrshldLevel, BF::HOST,bReadOnly); 

   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************
bool FeeThrshldSys::isTheSameBusinessDate(const BFDataGroupId& idDataGroup)
{
   DString strCurBusDate,strEffectiveDate;
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
   getParent()->getParent()->getField(ifds::EffectiveDate,strEffectiveDate,idDataGroup,false);
   if( DSTCommonFunctions::CompareDates(strCurBusDate,strEffectiveDate ) != DSTCommonFunctions::SECOND_EARLIER )
   {
      return(true);
   }
   return(false);
}

//*************************************************************************************
bool FeeThrshldSys::isThresholdReadOnly(const BFDataGroupId& idDataGroup)
{
   DString strCurBusDate;
   DString strEffectiveDate;
   DString strFMLastProcDate;

	DString dstrFeeCode;
	DString dstrGroupType;
   DString dstrUpdateRule = I_("0");

   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
   FeeThrshldSysList* pFeeThrshldSysList = dynamic_cast<FeeThrshldSysList* >(getParent());
   if(pFeeThrshldSysList)
   {
      FeeParamSys* pFeeParamSys = dynamic_cast<FeeParamSys*>(pFeeThrshldSysList->getParent());
      if(pFeeParamSys)
      {
      	pFeeParamSys->getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);
      }
   }
   if(dstrFeeCode != NULL_STRING)
   {
	   FeeParamConfigList*	pFeeParamConfigList = NULL;
	   FeeParamConfig *pFeeParamConfig = NULL;
      if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
	   {
	   	if (pFeeParamConfigList)
	      {
            pFeeParamConfigList->getFeeParamConfig(pFeeParamConfig, dstrFeeCode, idDataGroup);
            if(pFeeParamConfigList)
            {
               pFeeParamConfig->getField(ifds::UpdateRule, dstrUpdateRule, idDataGroup, false);
            }
         }
      }
   }

   if(dstrUpdateRule == I_("0"))
   {
      getParent()->getParent()->getField(ifds::EffectiveDate,  strEffectiveDate,  idDataGroup,false);
      if( DSTCommonFunctions::CompareDates(strCurBusDate,strEffectiveDate ) == DSTCommonFunctions::SECOND_EARLIER )
      {
         return(true);
      }
   }
   else
   {
      getParent()->getParent()->getField(ifds::FMLastProcDate, strFMLastProcDate, idDataGroup, false);
      if(strFMLastProcDate == NULL_STRING || strFMLastProcDate == I_("12319999"))
      {
         return false;
      }
      else 
      {
         return true;
      }
   }

   return(false);
}

//*************************************************************************************
SEVERITY FeeThrshldSys::init(const BFDataGroupId& idDataGroup ) // init new
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long )" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY FeeThrshldSys::doValidateField( const BFFieldId& idField,
										         const DString& strValue,
										         const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   SEVERITY  svrn = NO_CONDITION;

   return(GETCURRENTHIGHESTSEVERITY());
}
//************************************************************************************************
SEVERITY FeeThrshldSys::doApplyRelatedChanges ( const BFFieldId& idField, 
                                              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FeeThrshldSys::setValueFromDefault( BFCBO* pCBO, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFieldFromCBO" ) );

   DString strScaleRate, strUBound, strLBound, strMinFee, strMaxFee;
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
//If default record exists, validate scale rate against the default value of MinFee/MaxFee
SEVERITY FeeThrshldSys::validateScaleRate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateScaleRate" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY FeeThrshldSys::getFeeScaleSysList(FeeScaleBaseList*& pFeeScaleSysList, const BFDataGroupId& idDataGroup, bool createNew)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "AddNewFeeScale" ) );
   
	DString dstrKey = I_("FeeScaleSysList");
   pFeeScaleSysList = dynamic_cast<FeeScaleBaseList* > (getObject(dstrKey, idDataGroup) );
   if(pFeeScaleSysList == NULL && createNew)
   {
      pFeeScaleSysList = new FeeScaleSysList(*this);
      FeeParamBase* pFeeParamBase = dynamic_cast<FeeParamBase*>(getParent()->getParent());
      pFeeScaleSysList->setFeeParamBase(pFeeParamBase);
      setObject(pFeeScaleSysList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup);
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY FeeThrshldSys::clone(const BFDataGroupId& idDataGroup, FeeThrshldSys*& pFeeThrshldSysClone)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clone" ) );

   pFeeThrshldSysClone = new FeeThrshldSys((BFAbstractCBO&)(*this));

   for (int i = 0; i < NUM_FIELDS; i++)
   {
      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
      const BFFieldId &fieldId = fieldInfo.getFieldId();

      DString fieldValue;

      getField (fieldId, fieldValue, idDataGroup, false);
      pFeeThrshldSysClone->setFieldNoValidate (fieldId, fieldValue, idDataGroup, false, true, false, false);
   }

   FeeScaleBaseList* pFeeScaleBaseList = NULL;
   getFeeScaleSysList(pFeeScaleBaseList, idDataGroup, false);
   FeeScaleSysList* pFeeScaleSysListClone = NULL;
   FeeScaleSysList* pFeeScaleSysList = NULL;
   pFeeScaleSysList = dynamic_cast<FeeScaleSysList*>(pFeeScaleBaseList);
   if(pFeeScaleSysList)
   {
      pFeeScaleSysList->clone(idDataGroup, pFeeScaleSysListClone);

	   DString dstrKey = I_("FeeScaleSysList");
      pFeeThrshldSysClone->setObject(pFeeScaleSysListClone, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup);
   }
   return(GETCURRENTHIGHESTSEVERITY());
};










