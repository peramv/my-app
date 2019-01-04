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
// ^FILE   : FeeParamBase.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 10, 2003
//
// ^CLASS    : FeeParamBase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feeparamBase.hpp"
#include "feeparamBaselist.hpp"
#include "feescalebase.hpp"
#include "feescaleBaselist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "FeeParamSysList.hpp"
#include "feeparamconfig.hpp"
#include "feeparamconfiglist.hpp"

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_RATE_IS_OUT_OF_RANGE;
   extern const long ERR_FEE_SET_UP_IS_NOT_ALLOWED;
   extern const long ERR_AT_LEAST_ONE_RECORD_FOR_SCALE;
   extern const long ERR_FUND_FEE_DOES_NOT_EXIST;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_FUND_COMMGROUP_MUST_BE_ENTERED;
   extern const long ERR_EMPTY_FUNDCLASS;
   extern const long ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST;
   extern const long ERR_MAX_LESS_THAN_MIN;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN;
   extern const long WARN_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN;
}

namespace
{
   const I_CHAR * const CLASSNAME                              = I_( "FeeParamBase" );
   const I_CHAR * const FEE_SCALE_LIST                         = I_( "FeeScaleBaseList" );
   const I_CHAR * const FLAT                                   = I_( "0" );
   const I_CHAR * const PERCENT                                = I_( "1" );
   const I_CHAR * const SCALE                                  = I_( "2" );
   const I_CHAR * const TIER                                   = I_( "3" );
   const I_CHAR * const YES                                    = I_("Y");
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE                = I_("18");
   const I_CHAR * const FEE_CODE_MANAGEMENT_REBATE             = I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT           = I_("180");
   const I_CHAR * const FEE_CODE_MANAGEMENT_HST_OVERRIDE_LIST  = I_("79,81,85,86");
   const I_CHAR * const FEE_CODE_DIVIDEND_WITHHOLDING_TAX      = I_("38");
   const I_CHAR * const IDI_FUNDCLASS                          = I_("FUNDCLASS");
   const I_CHAR * const IDI_RATE                               = I_("RATE");
   const I_CHAR * const IDI_MIN_RATE                           = I_("MINRATE");
   const I_CHAR * const IDI_MAX_RATE                           = I_("MAXRATE");
   const I_CHAR * const IDI_GRADE                              = I_("GRADE");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId FeeFundClassCross;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId SplitCommTransTypes;
   extern CLASS_IMPORT const BFTextFieldId FeeCodeFundClassDateCross;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundFromCode;
   extern CLASS_IMPORT const BFTextFieldId ClassFromCode;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId FreqMinMaxApp;
   extern CLASS_IMPORT const BFTextFieldId CommGroup;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFTextFieldId AllowOverwrite;
   extern CLASS_IMPORT const BFTextFieldId CommFeeCodes;
   extern CLASS_IMPORT const BFTextFieldId CalcSwitch;
   extern CLASS_IMPORT const BFTextFieldId GroupFundClass;
   extern CLASS_IMPORT const BFDecimalFieldId ScaleRate;
   extern CLASS_IMPORT const BFTextFieldId GroupFundXEdit;
   extern CLASS_IMPORT const BFDateFieldId FMLastProcDate;
   extern CLASS_IMPORT const BFTextFieldId UpdateRule;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
}

//*********************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                      State Flags,             Group Flags 
   { ifds::FundCode,                  BFCBO::NONE,                 0 }, 
   { ifds::ClassCode,                 BFCBO::NONE,                 0 }, 
   { ifds::FeeCode,                   BFCBO::NONE,                 0 }, 
   { ifds::ParamFeeType,              BFCBO::REQUIRED,             0 }, 
   { ifds::Rate,                      BFCBO::NONE,                 0 }, 
   { ifds::EffectiveDate,             BFCBO::NONE,                 0 }, 
   { ifds::StopDate,                  BFCBO::NONE,                 0 }, 
   { ifds::FundNumber,                BFCBO::NONE,                 0 }, 
   { ifds::FundClass,                 BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FeeFundClassCross,         BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::CompoundDate,              BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::GroupFundClass,            BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FeeCodeFundClassDateCross, BFCBO::NONE,                 0 }, 
   { ifds::CommGroup,                 BFCBO::NONE,                 0 }, 
   { ifds::GroupFundXEdit,            BFCBO::IMMEDIATE_VALIDATION, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//*********************************************************************************
FeeParamBase::FeeParamBase( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
// NOTE: it is inherently unsafe to use "this" in an initializer.  CP20041110
#pragma warning( push )
#pragma warning( disable:4355 )
, m_FundClassRules(*this)
#pragma warning( pop )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit(ifds::CompoundDate, ifds::EffectiveDate);
   addCrossEdit(ifds::CompoundDate, ifds::StopDate);
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
   addCrossEdit(ifds::FeeFundClassCross,  ifds::ParamFeeType );
   addCrossEdit(ifds::FeeFundClassCross,  ifds::FeeCode );
//	addCrossEdit(DBR::FeeCodeFundClassDateCross,	DBR::FeeCode );
   addCrossEdit(ifds::FeeCodeFundClassDateCross,   ifds::FundCode );
   addCrossEdit(ifds::FeeCodeFundClassDateCross,   ifds::ClassCode );
   //addCrossEdit(DBR::FeeCodeFundClassDateCross,	DBR::EffectiveDate );
   addCrossEdit(ifds::GroupFundClass,   ifds::FundCode );
   addCrossEdit(ifds::GroupFundClass,   ifds::ClassCode );
   addCrossEdit(ifds::GroupFundClass,   ifds::CommGroup );

   addCrossEdit(ifds::GroupFundXEdit,   ifds::FundCode );
   addCrossEdit(ifds::GroupFundXEdit,   ifds::CommGroup );

   m_FundClassRules.init( ifds::FundNumber,ifds::FundCode,ifds::ClassCode,
                          ifds::EffectiveDate );
}

//*********************************************************************************
FeeParamBase::~FeeParamBase()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
//Fee Parm should be updatable as long as the effective date is equal or greater then the current business date. 
//Remove logic that stop user from update based on the process date.
bool FeeParamBase::isTheSameBusinessDate(const BFDataGroupId& idDataGroup)
{
   DString strCurBusDate,strEffectiveDate;
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
//   getField(ifds::ProcessDate,strProcessDate,idDataGroup,false);
//   if( DSTCommonFunctions::CompareDates(strCurBusDate,strProcessDate ) == DSTCommonFunctions::EQUAL )
   getField(ifds::EffectiveDate,strEffectiveDate,idDataGroup,false);

   if( DSTCommonFunctions::CompareDates(strCurBusDate,strEffectiveDate ) != DSTCommonFunctions::SECOND_EARLIER )
   {
      return(true);
   }

   return(false);
}

//*********************************************************************************
SEVERITY FeeParamBase::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   
   if( idField == ifds::FeeCode )
   {
      doFeeCodeRelatedChanges( idDataGroup );
   }
   else if( idField == ifds::CommGroup )
   {
      doCommGroupRelatedChanges( idDataGroup );
   }
   else if( idField == ifds::ParamFeeType )
   {
      doParamFeeTypeRelatedChanges( idDataGroup );
   }
   else if( idField == ifds::EffectiveDate )
   {
      doEffectiveDateRelatedChanges( idDataGroup );
   }
   if( idField == ifds::FeeCode || idField == ifds::FundCode || idField == ifds::ClassCode
       || idField == ifds::EffectiveDate  || idField == ifds::ParamFeeType || idField == ifds::CommGroup)
   { 
      doFundLevelFeeRelatedChanges( idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeParamBase::ValidateEffectiveStopDate(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateEffectiveStopDate" ) );
   DString EffectiveDate, StopDate;
   getField(ifds::EffectiveDate, EffectiveDate, idDataGroup);
   getField(ifds::StopDate, StopDate, idDataGroup);
   if( DSTCommonFunctions::CompareDates( StopDate, EffectiveDate ) 
      == DSTCommonFunctions::FIRST_EARLIER)
   {
      ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE );
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY FeeParamBase::validateFundCode(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );

   m_FundClassRules.validateFundCode( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY FeeParamBase::validateClassCode(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );

   m_FundClassRules.validateClassCode( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
bool FeeParamBase::allowNegRate(const BFDataGroupId &idDataGroup)
{
    bool allowNeg = false;
    DString dstrFeeCode;
    FeeParamConfigList *pFeeParamConfigList = NULL;
    FeeParamConfig* pFeeParamConfig = NULL;

    getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);
    dstrFeeCode.stripAll();

    if (!dstrFeeCode.empty() &&
        getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING && pFeeParamConfigList &&
        pFeeParamConfigList->getFeeParamConfig(pFeeParamConfig, dstrFeeCode, idDataGroup) <= WARNING && pFeeParamConfig)
    {
        allowNeg = pFeeParamConfig->allowNegativeRate();
    }

    return allowNeg;
}

//******************************************************************************
SEVERITY FeeParamBase::validateScaleRate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRate" ) )
   DString dstrParaFeeType,dstrFeeType;
   getField(ifds::ParamFeeType,dstrParaFeeType,idDataGroup,false);
   dstrParaFeeType.strip();
   DString dstrRatePara;
   getField(ifds::Rate,dstrRatePara,idDataGroup );
   double dRatePara =  DSTCommonFunctions::convertToDouble( dstrRatePara );
   if( dstrParaFeeType == PERCENT )
   {
       if (dRatePara > 100.0 || (dRatePara < 0.0  && !allowNegRate(idDataGroup)))
      {
         ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
void FeeParamBase::setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly) 
{
   setFieldReadOnly(ifds::FundCode,idDataGroup,bReadOnly ); 
   setFieldReadOnly(ifds::ClassCode,idDataGroup,bReadOnly);   
   setFieldReadOnly(ifds::FundNumber,idDataGroup,bReadOnly);  
   setFieldReadOnly(ifds::EffectiveDate,idDataGroup, idDataGroup != BF::HOST && bReadOnly);  
   setFieldReadOnly(ifds::StopDate,idDataGroup,idDataGroup != BF::HOST && bReadOnly); 
   setFieldReadOnly(ifds::ParamFeeType,idDataGroup,bReadOnly);   
   setFieldReadOnly(ifds::Rate,idDataGroup,bReadOnly);  
   setFieldReadOnly(ifds::CommGroup,idDataGroup,bReadOnly); 	
}

//******************************************************************************************
void FeeParamBase::doFeeCodeRelatedChanges( const BFDataGroupId& idDataGroup )
{
   DString dstrFeeCode;
   getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
   dstrFeeCode.strip();
   if( dstrFeeCode != NULL_STRING )
   {
      setFieldReadOnly(ifds::FeeCode,idDataGroup,true);
      setFieldsReadOnly( idDataGroup, false);

  /*       DString dstrCommGroup;
         getField(ifds::CommGroup,dstrCommGroup,idDataGroup,false );

         bool bRequired = (dstrFeeCode != FEE_CODE_MANAGEMENT_DISCOUNT && dstrCommGroup.empty()); 
         
         setFieldRequired(ifds::FundCode , idDataGroup, bRequired );
         setFieldRequired(ifds::ClassCode , idDataGroup, bRequired );

         MgmtCoOptions* pMgmtCoOptions;
         getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
         if( pMgmtCoOptions )
         {
            DString dstrCommFeeCode,dstrSplitCommTransType,dstrCalcSwitch;
            pMgmtCoOptions->getField(ifds::CommFeeCodes,dstrCommFeeCode,idDataGroup,false);
            pMgmtCoOptions->getField(ifds::SplitCommTransTypes,dstrSplitCommTransType,idDataGroup,false);
            pMgmtCoOptions->getField(ifds::CalcSwitch,dstrCalcSwitch,idDataGroup,false);       
            dstrCommFeeCode.strip();
            dstrSplitCommTransType.strip();
            bool bReadOnly = dstrCommFeeCode == dstrFeeCode || dstrSplitCommTransType == dstrFeeCode;
            setFieldReadOnly(ifds::ParamFeeType,idDataGroup,bReadOnly );
            setFieldReadOnly(ifds::FundFromCode,idDataGroup,bReadOnly );
            setFieldReadOnly(ifds::ClassFromCode,idDataGroup,bReadOnly );
            setFieldReadOnly(ifds::MaxFee,idDataGroup,bReadOnly && dstrFeeCode != I_("88") );  
            setFieldReadOnly(ifds::MinFee,idDataGroup,bReadOnly && dstrFeeCode != I_("88") && dstrCalcSwitch != I_("Y") );         
         }

         if( dstrFeeCode == FEE_CODE_MANAGEMENT_DISCOUNT )
         {
            setFieldNoValidate(ifds::ParamFeeType,PERCENT,idDataGroup,false,true,true );
            setFieldReadOnly(ifds::ParamFeeType,idDataGroup,true );
            setFieldReadOnly(ifds::FundCode,idDataGroup,true );
            setFieldReadOnly(ifds::ClassCode,idDataGroup,true );
            setFieldReadOnly(ifds::FundNumber,idDataGroup,true );
         }
   */
   }
}

//******************************************************************************************
void FeeParamBase::doParamFeeTypeRelatedChanges( const BFDataGroupId& idDataGroup )
{
   DString dstrFeeType;
   getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip();
   if( dstrFeeType == SCALE || dstrFeeType == TIER )
   {
      setFieldNoValidate(ifds::Rate,I_("0.0"),idDataGroup,true,true,true);
   }
   else 
   {
      setValidFlag(ifds::Rate, idDataGroup, false); 

      FeeScaleBaseList *pFeeScaleList = NULL;
      getFeeScaleList( pFeeScaleList,idDataGroup );
      if( pFeeScaleList != NULL )
      {
         BFObjIter iterScale(*pFeeScaleList,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
         while( !iterScale.end() )
         {
            BFAbstractCBO* cbo = iterScale.getObject();
            if( cbo->isNew() )
            {
               iterScale.removeObjectFromMap(true);
            }
            else
               ++iterScale;
         }
      }
   }
}

//******************************************************************************************
void FeeParamBase::doEffectiveDateRelatedChanges( const BFDataGroupId& idDataGroup )
{
   setValidFlag(ifds::FeeCodeFundClassDateCross, idDataGroup, false); 
}

//******************************************************************************************
void FeeParamBase::doCommGroupRelatedChanges( const BFDataGroupId& idDataGroup )
{
   DString dstrCommGroup;
   getField(ifds::CommGroup,dstrCommGroup,idDataGroup,false );
   setFieldRequired(ifds::FundCode , idDataGroup, dstrCommGroup.empty() );
   setFieldRequired(ifds::ClassCode , idDataGroup, dstrCommGroup.empty() );
}

//******************************************************************************
SEVERITY FeeParamBase::validateFundClassCommGroup(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGroupFundClass" ) );

   DString dstrFundCode, dstrClassCode,dstrCommGroupCode,dstrFeeCode;
   FeeParamConfigList *pFeeParamConfigList = NULL;
   FeeParamConfig* pFeeParamConfig = NULL;
   bool envLvlFee = false;

   getField( ifds::FeeCode,dstrFeeCode,idDataGroup,false );
   dstrFeeCode.strip();
   if( FEE_CODE_MANAGEMENT_DISCOUNT == dstrFeeCode )
      return(GETCURRENTHIGHESTSEVERITY());

   
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING && pFeeParamConfigList &&
       pFeeParamConfigList->getFeeParamConfig(pFeeParamConfig, dstrFeeCode, idDataGroup) <= WARNING && pFeeParamConfig)
   {
       envLvlFee = pFeeParamConfig->isEnvLvlFee();
   }

   getField(ifds::FundCode,dstrFundCode,idDataGroup,false );
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false );
   getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
   dstrFundCode.strip();dstrClassCode.strip();dstrCommGroupCode.strip();

   if ( (!DSTCommonFunctions::codeInList(dstrFeeCode, FEE_CODE_MANAGEMENT_HST_OVERRIDE_LIST) ) &&
        ( dstrFeeCode != FEE_CODE_DIVIDEND_WITHHOLDING_TAX )
      )
   {
      if (dstrCommGroupCode.empty())
      {
         if ((dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING) && !envLvlFee)
            ADDCONDITIONFROMFILE( CND::ERR_EMPTY_FUNDCLASS );
      }
      else
      {
         if( dstrFundCode != NULL_STRING || dstrClassCode != NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST );
         }
      }
   }
   else
   {
      // for fee code 38,79,81 that can be setup Fund level..
      // we should not allow to set the class level
      if( DSTCommonFunctions::codeInList(dstrFeeCode, FEE_CODE_MANAGEMENT_HST_OVERRIDE_LIST) )
      {
         if (dstrCommGroupCode.empty())
         {
            // fund group not set . fund should be valid.class may be empty 
            if (dstrFundCode.empty() )
            {
               ADDCONDITIONFROMFILE( CND::ERR_EMPTY_FUNDCLASS );
            }
            else 
            {
               validateFundCode(idDataGroup);

               if ( !dstrClassCode.empty() )
               {
                  validateClassCode(idDataGroup);
               }
            }
         }
         else
         {
            // fund group set...fund and class should be empty
            if( !dstrFundCode.empty() || !dstrClassCode.empty() )
            {
               ADDCONDITIONFROMFILE( CND::ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST );
            }
         }
      }
      else
      {
         if (dstrFundCode == NULL_STRING && dstrClassCode != NULL_STRING)
         {
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
bool FeeParamBase::canUpdateObject(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canUpdateObject" ) );

   DString strCurBusDate;
   DString strEffectiveDate;

   if(!getSession().isBFWorkSession())
      return false;

   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);
   getField(ifds::EffectiveDate,strEffectiveDate,idDataGroup,false);
   
   DString dstrFeeCode;
   getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);
   DString dstrUpdateRule = I_("0");

   DString dstrFeeModelCode;
   getField(ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false);

   FeeParamConfigList *pFeeParamConfigList = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING && pFeeParamConfigList)
   {
		DString dstrFeeCodeSubList;	
      FeeParamConfig* pFeeParamConfig = NULL;
      if(pFeeParamConfigList->getFeeParamConfig(pFeeParamConfig, dstrFeeCode, idDataGroup) <= WARNING && pFeeParamConfig)
      {
         pFeeParamConfig->getField(ifds::UpdateRule, dstrUpdateRule, idDataGroup, false);
      }
   }
   DString dstrFMLastProcDate;
   getField(ifds::FMLastProcDate, dstrFMLastProcDate, idDataGroup, false);
   
   //DString dstrEffectiveDate;
   //getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);


   if( isNew() || 
       dstrUpdateRule == I_("0") && DSTCommonFunctions::CompareDates(strCurBusDate,strEffectiveDate) != DSTCommonFunctions::SECOND_EARLIER ||
       dstrUpdateRule == I_("1") && (dstrFMLastProcDate == NULL_STRING || dstrFMLastProcDate == I_("12319999")
//      ||DSTCommonFunctions::CompareDates(dstrEffectiveDate, dstrFMLastProcDate) == DSTCommonFunctions::SECOND_EARLIER 
      )
      )
   {
      return(true);
   }
   return(false);
}
//******************************************************************************************
void FeeParamBase::doFundLevelFeeRelatedChanges( const BFDataGroupId& idDataGroup )
{
   setValidFlag(ifds::Rate, idDataGroup, false);
   DString dstrFeeType;
   getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip().upperCase();
   bool bScale = dstrFeeType == SCALE || dstrFeeType == TIER; 
   FeeScaleBaseList *pFeeScaleList = NULL;
   if(bScale)
   {
      getFeeScaleList( pFeeScaleList,idDataGroup );
      if( pFeeScaleList != NULL )
      {
         BFObjIter iterScale(*pFeeScaleList,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
         while( !iterScale.end() )
         {
            dynamic_cast<FeeScaleBase* >(iterScale.getObject())->setValidFlagDerive(ifds::ScaleRate,idDataGroup,!bScale );
            ++iterScale;
         }
      }
   }
}

//*****************************************************************************************
SEVERITY FeeParamBase::doValidateField( const BFFieldId& idField,
                                        const DString& strValue,
                                        const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( idField == ifds::FundCode )
   {
      m_FundClassRules.validateFundCode(idDataGroup);
   }
   else if (idField == ifds::ClassCode )
   {
      m_FundClassRules.validateClassCode(idDataGroup);
   }
   else if(idField == ifds::GroupFundClass )
   {
      validateFundClassCommGroup(idDataGroup);
   }
   else if( idField == ifds::CompoundDate)
   {
      ValidateEffectiveStopDate(idDataGroup);
   }
   else if ( idField == ifds::GroupFundXEdit )
   {
      validateGroupFundXEdit(idDataGroup);
   }
   else if (idField == ifds::MaxFee)
   {
       validateMax(strValue, idDataGroup);
   }
   else if (idField == ifds::MinFee)
   {
       validateMin(strValue, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeParamBase::validateMin(const DString &strValue, const BFDataGroupId  &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMin"));

    double dMinFee = DSTCommonFunctions::convertToDouble(strValue);
    DString dstrParamFeeType;

    getField(ifds::ParamFeeType, dstrParamFeeType, idDataGroup, false);

    if (dstrParamFeeType == PERCENT && ((dMinFee > 100) || (dMinFee < 0 && !allowNegRate(idDataGroup))))
    {
        ADDCONDITIONFROMFILE(CND::ERR_VALUE_BETWEEN_0_AND_100);
    }

    return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY FeeParamBase::validateMax(const DString &strValue, const BFDataGroupId  &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMax"));

    double dMaxFee = DSTCommonFunctions::convertToDouble(strValue);
    DString dstrFeeCode, dstrParamFeeType;
    FeeParamConfigList *pFeeParamConfigList = NULL;
    FeeParamConfig* pFeeParamConfig = NULL;

    getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);
    getField(ifds::ParamFeeType, dstrParamFeeType, idDataGroup, false);

    if (dstrParamFeeType == PERCENT && ((dMaxFee > 100) || (dMaxFee < 0 && !allowNegRate(idDataGroup))))
    {
        ADDCONDITIONFROMFILE(CND::ERR_VALUE_BETWEEN_0_AND_100);
    }

    if (GETCURRENTHIGHESTSEVERITY() <= WARNING &&
        getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING && pFeeParamConfigList &&
        pFeeParamConfigList->getFeeParamConfig(pFeeParamConfig, dstrFeeCode, idDataGroup) <= WARNING && pFeeParamConfig)
    {
        DString dstrFeeConfigMaxFee;
        double dFeeConfigMaxFee;

        pFeeParamConfig->getField(ifds::MaxFee, dstrFeeConfigMaxFee, idDataGroup, false);
        dFeeConfigMaxFee = DSTCommonFunctions::convertToDouble(dstrFeeConfigMaxFee);

        if (dFeeConfigMaxFee != 0.0 && dMaxFee > dFeeConfigMaxFee)
        {
            DString idiStr;
            addIDITagValue(idiStr, I_("RATE"), dstrFeeConfigMaxFee);

            getErrMsg(IFASTERR::THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN,
                CND::ERR_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN,
                CND::WARN_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN,
                idDataGroup,
                idiStr);
        }
    }

    return (GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY FeeParamBase::validateMinMax(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMinMax" ) );

   DString strValue;
   double dMax,dMin;
   getField(ifds::MaxFee,strValue,idDataGroup,false);
   dMax = DSTCommonFunctions::convertToDouble( strValue );
   getField(ifds::MinFee,strValue,idDataGroup,false);
   dMin = DSTCommonFunctions::convertToDouble( strValue );

   if( dMax < dMin )
   {
      ADDCONDITIONFROMFILE( CND::ERR_MAX_LESS_THAN_MIN );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// this method is called by FeeParamSysList
//
SEVERITY FeeParamBase::validateFeeScaleList(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeScaleList" ) )
   DString dstrFeeType;
   getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip();
   if(isNew() && ( dstrFeeType == SCALE  || dstrFeeType == TIER ) )
   {
      FeeScaleBaseList *pFeeScaleList = NULL;
      getFeeScaleList( pFeeScaleList,idDataGroup );
      if( pFeeScaleList != NULL )
      {
         BFObjIter iterScale(*pFeeScaleList,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
         int iNum = iterScale.getNumberOfItemsInList();
         if( iNum >1|| (iNum == 1 && !iterScale.isDummy() ) )
            return(GETCURRENTHIGHESTSEVERITY());
      }
      ADDCONDITIONFROMFILE( CND::ERR_AT_LEAST_ONE_RECORD_FOR_SCALE );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY FeeParamBase::getFeeParamSysDef( FeeParamSys *&pFeeParamSys, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeParamSysDef" ) );

   DString strFeeCode, strFundCode, strClassCode, strFundGroup;
   FeeParamSysList *pFeeParamSysDefList = NULL;
   pFeeParamSys = NULL;
   getField(ifds::FeeCode,strFeeCode,idDataGroup,false );
   strFeeCode.strip().upperCase();
   getField( ifds::FundCode, strFundCode, idDataGroup );
   getField( ifds::ClassCode, strClassCode, idDataGroup );
   getField( ifds::CommGroup, strFundGroup, idDataGroup );

   strFundCode.strip().upperCase();
   strClassCode.strip().upperCase();
   strFundGroup.strip().upperCase();

   if (getMgmtCo().getDefaultFeeParamSysList(pFeeParamSysDefList) <= WARNING && pFeeParamSysDefList)
   {
      pFeeParamSysDefList->getDefaultFeeParamRecord( pFeeParamSys, 
                                                     strFeeCode,
                                                     strFundCode,
                                                     strClassCode,
                                                     strFundGroup,
                                                     BF::HOST,
                                                     true
                                                    );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeParamBase::validateGroupFundXEdit( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSysFeeGroupFundXEdit" ) );

   DString dstrFeeCode;
   getField( ifds::FeeCode,dstrFeeCode,idDataGroup,false );
   dstrFeeCode.strip();

   if ( DSTCommonFunctions::codeInList(dstrFeeCode, FEE_CODE_MANAGEMENT_HST_OVERRIDE_LIST) )
   {
      DString dstrFundCode,
         dstrClassCode,
         dstrCommGroupCode;

      getField(ifds::FundCode,dstrFundCode,idDataGroup,false );
      getField(ifds::ClassCode,dstrClassCode,idDataGroup,false );
      getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
      dstrFundCode.strip();dstrClassCode.strip();dstrCommGroupCode.strip();

      if (dstrCommGroupCode.empty())
      {
         if ( dstrFundCode == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_EMPTY_FUNDCLASS );
         }
         else
         {
            // fund group not set ...fund should be valid...class may be empty 
            m_FundClassRules.validateFundCode(idDataGroup);

            if( !dstrClassCode.empty() )
            {
               m_FundClassRules.validateClassCode(idDataGroup);
            }
         }
      }
      else
      {
         // fund group set...fund and class should be empty
         if ( !dstrFundCode.empty() || !dstrClassCode.empty() ) 
         {
            ADDCONDITIONFROMFILE( CND::ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamBase.cpp-arc  $
// 
//    Rev 1.25   Jun 09 2011 18:05:54   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level,  compile error!.
// 
//    Rev 1.24   Jun 09 2011 16:29:34   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level, got claification from business perspective.
// 
//    Rev 1.23   Apr 04 2011 09:03:48   kitticha
// PETP0184437_FN03_IN0_Tax Withheld on Distributions.
// 
//    Rev 1.22   Feb 28 2011 18:27:14   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level.
// 
//    Rev 1.21   Feb 21 2011 14:58:56   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level., recheck in for R11.4
// 
//    Rev 1.20   Feb 21 2011 14:50:56   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level., restore 1.18, code promoteion was move to R11.4
// 
//    Rev 1.19   Feb 10 2011 15:31:02   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level.
// 
//    Rev 1.18   Apr 14 2005 08:57:20   yingbaol
// Incident 265632 Change set default fee logic for FundSponsorFee
// 
//    Rev 1.17   Nov 14 2004 14:40:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.16   Sep 10 2004 15:51:30   FENGYONG
// PET1117 FN5 - Client Fee
// 
//    Rev 1.15   Aug 10 2004 11:24:06   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.14   Jul 21 2003 14:51:02   linmay
// PTS Ticket #10014935
// 
//    Rev 1.13   May 27 2003 13:00:42   linmay
// PTS Ticket #10017099
// 
//    Rev 1.12   Mar 21 2003 18:09:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Mar 10 2003 14:43:36   linmay
// modified doFeeCodeRelatedChanges
// 
//    Rev 1.10   Feb 17 2003 10:18:00   YINGBAOL
// clean FundFeeList
// 
//    Rev 1.9   Jan 28 2003 15:58:16   linmay
// modified setFieldsReadOnly()
// 
//    Rev 1.8   Jan 27 2003 15:19:20   linmay
// added validateMinMax(const BFDataGroupId& idDataGroup )
// 
//    Rev 1.7   Jan 22 2003 09:58:22   YINGBAOL
// do  not validate against FundFeeList
// 
//    Rev 1.6   Jan 21 2003 11:42:26   YINGBAOL
// FundClassRules change Sync.
// 
//    Rev 1.5   Jan 20 2003 15:09:06   linmay
// modified setfieldsreadonly
// 
//    Rev 1.4   Jan 18 2003 17:23:38   YINGBAOL
// add doValidateField and change FeeType to FeeParamType
// 
//    Rev 1.3   Jan 17 2003 17:56:50   linmay
// added validatefundclasscommgroup()
// 
//    Rev 1.2   Jan 15 2003 11:57:18   linmay
// added Log Comment
// 
*/
