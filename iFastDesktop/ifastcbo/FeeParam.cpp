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
// ^FILE   : FeeParam.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 24, 2002
//
// ^CLASS    : FeeParam
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feeparam.hpp"
#include "feeparamlist.hpp"
#include "feescale.hpp"
#include "feescalelist.hpp"
#include "funddetaillist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "fundmasterlist.hpp"
#include "fundfeelist.hpp"
#include "mfaccount.hpp"
#include "groupfundlist.hpp"
#include <ifastdataimpl\dse_dstc0194_vw.hpp>
#include <ifastdataimpl\dse_dstc0194_req.hpp>
#include <ifastdataimpl\dse_dstc0195_vw.hpp>
#include <ifastdataimpl\dse_dstc0197_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0229_vw.hpp>
#include "FundCommGroupList.hpp"
#include "feeparamconfiglist.hpp"
#include "feeparamconfig.hpp"
#include "documenttypeoverridelist.hpp"

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_FUND_CLASS_FOR_MANAGEMENT_FEE;
   extern const long ERR_FUND_CLASS_FOR_MANAGEMENT_FEE_REBATE;
   extern const long ERR_RATE_IS_OUT_OF_RANGE;
   extern const long ERR_MANAGEMENT_FEE_TYPE;
   extern const long ERR_FEE_SET_UP_IS_NOT_ALLOWED;
   extern const long ERR_AT_LEAST_ONE_RECORD_FOR_SCALE;
   extern const long ERR_FUND_FEE_DOES_NOT_EXIST;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_FUND_COMMGROUP_MUST_BE_ENTERED;
   extern const long ERR_EMPTY_FUNDCLASS;
   extern const long ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST;
   extern const long ERR_FEE_CODE_OVERLAPED;  
   extern const long ERR_FUND_NOT_EFFECTIVE;
   extern const long ERR_FEECODE_CANNOT_COEXIT;
   extern const long ERR_NEW_ARCH_TRAILER_FEE;
   extern const long ERR_BLANK_FUND;
}

namespace  
{
   const I_CHAR * const CLASSNAME                              = I_( "FeeParam" );
   const I_CHAR * const FEE_SCALE_LIST                         = I_( "FeeScaleList" );
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
   const I_CHAR * const FEE_CODE_TRAILER_FEE_REBATE            = I_("93");
   const I_CHAR * const IDI_FUNDCLASS                          = I_("FUNDCLASS");
   const I_CHAR * const IDI_RATE                               = I_("RATE");
   const I_CHAR * const IDI_MIN_RATE                           = I_("MINRATE");
   const I_CHAR * const IDI_MAX_RATE                           = I_("MAXRATE");
   const I_CHAR * const IDI_GRADE                              = I_("GRADE");
   const I_CHAR * const VALIDATE_TYPE_FIND_RECORD              = I_("FindRecord");
   const I_CHAR * const VALIDATE_TYPE_DUP_CHECK                = I_("DupCheck");
   const I_CHAR * const VALIDATE_TYPE_COEXIST                  = I_("ExclFeeCheck");
   const I_CHAR * const TRAILER_FEE                            = I_("8");

   const I_CHAR * const IDI_CODE                               = I_("CODE");  
   const I_CHAR * const ACCOUNT_LEVEL                          = I_("ACCOUNT");
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
   extern CLASS_IMPORT const BFTextFieldId AcctGroup;
   extern CLASS_IMPORT const BFTextFieldId MgtFeeElig;
   extern CLASS_IMPORT const BFTextFieldId MgtFeeRbtElig;
   extern CLASS_IMPORT const BFTextFieldId FeeCodeFundClassDateCross;
   extern CLASS_IMPORT const BFTextFieldId GroupFundClass;
   extern CLASS_IMPORT const BFNumericFieldId	AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FeeRecordOverlapCheck;
   extern CLASS_IMPORT const BFTextFieldId FeeLevel;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
}

//************************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FundCode,                  BFCBO::NONE,                 0 }, 
   { ifds::ClassCode,                 BFCBO::NONE,                 0 }, 
   { ifds::FundFromCode,              BFCBO::NONE,                 0 }, 
   { ifds::ClassFromCode,             BFCBO::NONE,                 0 }, 
   { ifds::FeeCode,                   BFCBO::NONE,                 0 }, 
   { ifds::ParamFeeType,              BFCBO::REQUIRED,             0 }, 
   { ifds::Rate,                      BFCBO::NONE,                 0 }, 
   { ifds::MinFee,                    BFCBO::NONE,                 0 }, 
   { ifds::MaxFee,                    BFCBO::NONE,                 0 }, 
   { ifds::EffectiveDate,             BFCBO::NONE,                 0 }, 
   { ifds::StopDate,                  BFCBO::NONE,                 0 }, 
   { ifds::FreqMinMaxApp,             BFCBO::NONE,                 0 }, 
   { ifds::ChrgOnPrtlRed,             BFCBO::NONE,                 0 }, 
   { ifds::ChrgOnFullRed,             BFCBO::NONE,                 0 }, 
   { ifds::FundNumber,                BFCBO::NONE,                 0 }, 
   { ifds::FundClass,                 BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FeeFundClassCross,         BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::CompoundDate,              BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::GroupFundClass,            BFCBO::IMMEDIATE_VALIDATION, 0 },

   { ifds::Status,                    BFCBO::NONE,                 0 }, 
   { ifds::FeeCodeFundClassDateCross, BFCBO::NONE,                 0 }, 
   { ifds::CommGroup,                 BFCBO::NONE,                 0 }, 
   { ifds::BrokerCode,                BFCBO::NONE,                 0 }, 
   { ifds::BasedOn,                   BFCBO::NONE,                 0 }, 

   { ifds::FeeRecordOverlapCheck,     BFCBO::NONE,                 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//************************************************************************************
const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//************************************************************************************
FeeParam::FeeParam( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
,_pFundFeeList(NULL)
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
// addCrossEdit(DBR::FeeCodeFundClassDateCross,	DBR::FeeCode );
   addCrossEdit(ifds::FeeCodeFundClassDateCross,   ifds::FundCode );
   addCrossEdit(ifds::FeeCodeFundClassDateCross,   ifds::ClassCode );

   addCrossEdit(ifds::GroupFundClass,   ifds::FundCode );
   addCrossEdit(ifds::GroupFundClass,   ifds::ClassCode );
   addCrossEdit(ifds::GroupFundClass,   ifds::CommGroup );

   addCrossEdit(ifds::FeeRecordOverlapCheck, ifds::EffectiveDate);
   addCrossEdit(ifds::FeeRecordOverlapCheck, ifds::StopDate);

   //addCrossEdit(DBR::FeeCodeFundClassDateCross,	DBR::EffectiveDate );
}

//************************************************************************************
FeeParam::~FeeParam()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//************************************************************************************
SEVERITY FeeParam::doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   SEVERITY  svrn = NO_CONDITION;
   if( idField == ifds::CompoundDate )
   {
      ValidateDate( idField, idDataGroup );
   }
   else if( idField == ifds::FundCode )
   {
      validateFundCode( strValue, idDataGroup);
   }
   else if( idField == ifds::ClassCode )
   {
      DString dstrFundCode;
      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      validateClassCode( dstrFundCode, strValue, idDataGroup);
   }
   else if( idField == ifds::FundNumber )
   {
      DString dstrFundNumber(strValue);
      if( dstrFundNumber.strip() != NULL_STRING )
      {
         DString dstrFundCode,dstrClassCode;
         if( !getWorkSession().GetFundClassCode( strValue,dstrFundCode,dstrClassCode) )
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );
      }
   }
   else if( idField ==  ifds::FundClass )
   {
      validateFundClass(idDataGroup );   
   }
 /*  else if( idField == ifds::FeeFundClassCross )
   {
      validateFeeParamTypeFundClass( idDataGroup);
   }
*/
   else if( idField == ifds::FeeCodeFundClassDateCross )
   {

      validateFeeCodeFundClass(idDataGroup);
   }
   else if( idField == ifds::Rate )
   {
      validateRate( idDataGroup );
   }
   else if( idField == ifds::GroupFundClass )
   {
      validateGroupFundClass(idDataGroup );
   } 
   else if (idField == ifds::FeeRecordOverlapCheck)
   {
      validateFeeOverlap(idDataGroup);
   }
   else if (idField == ifds::FeeCode)
   {
      validateFeeCode (strValue, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY FeeParam::init( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&, BFData*,Dstring&)" ) );

  // at begin we set all fields readonly except FeeCode 
//   setFieldsReadOnly(idDataGroup, true);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
void FeeParam::setFieldsReadOnly(const BFDataGroupId& idDataGroup,  bool bReadOnly) 
{
   setFieldReadOnly(ifds::FundCode,idDataGroup,bReadOnly); 
   setFieldReadOnly(ifds::ClassCode,idDataGroup,bReadOnly);   
   setFieldReadOnly(ifds::FundNumber,idDataGroup,bReadOnly);  
   setFieldReadOnly(ifds::EffectiveDate,idDataGroup,bReadOnly);  
   setFieldReadOnly(ifds::StopDate,idDataGroup,bReadOnly); 
   setFieldReadOnly(ifds::ParamFeeType,idDataGroup,bReadOnly); 
   setFieldReadOnly(ifds::CommGroup,idDataGroup,bReadOnly); 	
   setFieldReadOnly(ifds::Rate,idDataGroup,bReadOnly);  
   setFieldReadOnly(ifds::BasedOn,idDataGroup,bReadOnly);  
}

//************************************************************************************
SEVERITY FeeParam::init(const BFData& data,const BFData *pAcctFeeScaleData,const DString& AcctFeeParamId)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&, BFData*,Dstring&)" ) );  
   attachDataObject(const_cast<BFData&>(data), false);  

// only tier, scale has FeeScale List, perhaps we have to limit to create FeeScaleList  
   FeeScaleList* pFeeScaleList = new FeeScaleList ( *this );
   pFeeScaleList->init( *pAcctFeeScaleData, AcctFeeParamId);
   setObject( pFeeScaleList, FEE_SCALE_LIST, OBJ_ACTIVITY_NONE, BF::HOST );
   DString dstrFundCode,dstrClassCode,strValue;
   BFCBO::getField(ifds::FundCode,dstrFundCode,BF::HOST);
   BFCBO::getField(ifds::ClassCode,dstrClassCode,BF::HOST);
   getWorkSession().GetFundNumber( dstrFundCode,dstrClassCode, strValue );   
   setFieldNoValidate( ifds::FundNumber, strValue, BF::HOST, false,true, false, false  ); 

   bool bIsSameDate = isTheSameBusinessDate(BF::HOST); 
   setFieldReadOnly(ifds::FeeCode,BF::HOST,true);
   setupFeeCodeRelatedFields(BF::HOST, bIsSameDate);

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
//Fee Parm should be updatable as long as the effective date is equal or greater then the current business date. 
//Remove logic that stop user from update based on the process date.
bool FeeParam::isTheSameBusinessDate(const BFDataGroupId& idDataGroup)
{
   DString strEffectiveDate,strCurBusDate;
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
 //  getField(ifds::ProcessDate,strProcessDate,idDataGroup,false);
 //  if( DSTCommonFunctions::CompareDates(strCurBusDate,strProcessDate ) == DSTCommonFunctions::EQUAL )
   getField(ifds::EffectiveDate,strEffectiveDate,idDataGroup,false);
   if( DSTCommonFunctions::CompareDates(strCurBusDate,strEffectiveDate ) != DSTCommonFunctions::SECOND_EARLIER )
   {
      return(true);
   }
   return(false);
}

//************************************************************************************
SEVERITY FeeParam::getFeeScaleList( FeeScaleList *&pFeeScaleList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeScaleList" ) );
   DString strFeeType;
   pFeeScaleList = NULL;
   getField(ifds::ParamFeeType,strFeeType,idDataGroup,false );
   //if(SCALE == strFeeType || TIER == strFeeType ){
   pFeeScaleList = dynamic_cast<FeeScaleList*>(BFCBO::getObject( FEE_SCALE_LIST, idDataGroup ) );
   if( pFeeScaleList == NULL )
   {
      // if it is not existed, create a new one
      pFeeScaleList = new FeeScaleList( *this );
      pFeeScaleList->initNew(idDataGroup);
      setObject( pFeeScaleList, FEE_SCALE_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
   }
// }
   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
SEVERITY FeeParam::validateFeeCode (const DString &dstrFeeCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeCode" ) );

   DString dstrTrailerFeeArch;

   getWorkSession().getOption( ifds::TrailerFeeArch, dstrTrailerFeeArch, idDataGroup, false );

   if (dstrFeeCode == TRAILER_FEE && dstrTrailerFeeArch == YES)
   {
      ADDCONDITIONFROMFILE(CND::ERR_NEW_ARCH_TRAILER_FEE);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
SEVERITY FeeParam::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   
   if( idField == ifds::CommGroup )
   {
      DString dstrCommGroup;
      getField(ifds::CommGroup,dstrCommGroup,idDataGroup,false );
      setFieldValid( ifds::FeeCodeFundClassDateCross, idDataGroup, false );

 //     setFieldRequired(ifds::FundCode , idDataGroup, dstrCommGroup.empty() );
  //    setFieldRequired(ifds::ClassCode , idDataGroup, dstrCommGroup.empty() );
   }
   else
   if( idField == ifds::FeeCode )
   {
      DString dstrFeeCode;
      getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
      dstrFeeCode.strip().upperCase();
      if( dstrFeeCode != NULL_STRING )
      {
         setFieldReadOnly(ifds::FeeCode,idDataGroup,true);
         bool bIsSameDate = isTheSameBusinessDate(idDataGroup);
         setupFeeCodeRelatedFields(idDataGroup, bIsSameDate);
//         setFieldsReadOnly( idDataGroup,  false);

     //    DString dstrCommGroup;
      //   getField(ifds::CommGroup,dstrCommGroup,idDataGroup,false );

         bool bRequired = (dstrFeeCode != FEE_CODE_MANAGEMENT_DISCOUNT ); 
         setValidFlag( ifds::GroupFundClass,idDataGroup,!bRequired );

         MgmtCoOptions* pMgmtCoOptions;
         getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
         if( pMgmtCoOptions )
         {
            DString dstrCommFeeCode,dstrSplitCommTransType,dstrCalcSwitch;
            pMgmtCoOptions->getField(ifds::CommFeeCodes,dstrCommFeeCode,idDataGroup,false);
            pMgmtCoOptions->getField(ifds::SplitCommTransTypes,dstrSplitCommTransType,idDataGroup,false);
            pMgmtCoOptions->getField(ifds::CalcSwitch,dstrCalcSwitch,idDataGroup,false);       
            dstrCommFeeCode.strip().upperCase();
            dstrSplitCommTransType.strip();
            bool bReadOnly = dstrCommFeeCode == dstrFeeCode || dstrSplitCommTransType == dstrFeeCode;
            setFieldReadOnly(ifds::ParamFeeType,idDataGroup,bReadOnly );
            setFieldReadOnly(ifds::FundFromCode,idDataGroup,bReadOnly );
            setFieldReadOnly(ifds::ClassFromCode,idDataGroup,bReadOnly );
            setFieldReadOnly(ifds::MaxFee,idDataGroup,bReadOnly && dstrFeeCode != I_("88") );  
            setFieldReadOnly(ifds::MinFee,idDataGroup,bReadOnly && dstrFeeCode != I_("88") && dstrCalcSwitch != I_("Y") );         
         }
 /*
         if( dstrFeeCode == FEE_CODE_MANAGEMENT_DISCOUNT )
         {
            setFieldNoValidate(ifds::ParamFeeType,PERCENT,idDataGroup,false,true,true );
            setFieldReadOnly(ifds::ParamFeeType,idDataGroup,true );
            setFieldReadOnly(ifds::FundCode,idDataGroup,true );
            setFieldReadOnly(ifds::ClassCode,idDataGroup,true );
            setFieldReadOnly(ifds::FundNumber,idDataGroup,true );
            setFieldReadOnly(ifds::CommGroup,idDataGroup,true );

         }
 */     }
   }
   else if( idField == ifds::ParamFeeType )
   {
      DString dstrFeeType;
      getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
      dstrFeeType.strip().upperCase();
      if( dstrFeeType == SCALE || dstrFeeType == TIER )
         setFieldNoValidate(ifds::Rate,I_("0.0"),idDataGroup,true,true,true);
      else setValidFlag(ifds::Rate, idDataGroup, false); 
   }
   else if( idField == ifds::EffectiveDate )
   {
      setValidFlag(ifds::FeeCodeFundClassDateCross, idDataGroup, false);        
   }
   if( idField == ifds::FeeCode || idField == ifds::FundCode || idField == ifds::ClassCode
      || idField == ifds::CommGroup )
   {
      setValidFlag(ifds::FeeRecordOverlapCheck, idDataGroup, false);
   }

   if( idField == ifds::FeeCode || idField == ifds::FundCode || idField == ifds::ClassCode
       || idField == ifds::EffectiveDate  || idField == ifds::ParamFeeType || idField == ifds::CommGroup || idField == ifds::Rate )   
   { // ParamFeeType will be removed late
      if ( idField == ifds::Rate && _pFundFeeList )
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }
      refreshFundFeeList( idDataGroup);     
      setValidFlag(ifds::Rate, idDataGroup, false); 
//temp code will be removed when base support
      DString dstrFeeType;
      getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
      dstrFeeType.strip().upperCase();
      bool bScale = dstrFeeType == SCALE || dstrFeeType == TIER; 
      FeeScaleList *pFeeScaleList = NULL;
      getFeeScaleList( pFeeScaleList,idDataGroup );
      if( pFeeScaleList != NULL )
      {
         BFObjIter iterScale(*pFeeScaleList,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
         while( !iterScale.end() )
         {
            dynamic_cast<FeeScale* >(iterScale.getObject())->setValidFlagDerive(ifds::ScaleRate,idDataGroup,!bScale );
            ++iterScale;
         }
      }
// end temp
      if( _pFundFeeList )
      {
         DString dstrFeeCode/*,dstrAllowOverRide */;
         //_pFundFeeList->getField(ifds::AllowOverwrite,dstrAllowOverRide,idDataGroup,false);
         //dstrAllowOverRide.strip().upperCase();
         getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);

         MgmtCoOptions* pMgmtCoOptions;
         getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
         if( pMgmtCoOptions )
         {
            DString dstrCommFeeCode,dstrSplitCommTransType;
            pMgmtCoOptions->getField(ifds::CommFeeCodes,dstrCommFeeCode,idDataGroup,false);
            pMgmtCoOptions->getField(ifds::SplitCommTransTypes,dstrSplitCommTransType,idDataGroup,false);
            bool bReadOnly = dstrCommFeeCode == dstrFeeCode || dstrSplitCommTransType == dstrFeeCode;
            setFieldReadOnly(ifds::Rate,idDataGroup,bReadOnly /*|| dstrAllowOverRide == I_("0")*/ );
         }
      }
      else
      {
         CLEARCONDITIONSFRAMECURRENT();   
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
void FeeParam::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   DString strValue;
   getWorkSession().getDateInHostFormat(strValue, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY,idDataGroup );
   setFieldNoValidate( ifds::EffectiveDate, strValue, idDataGroup , false,true,false,false );
   getWorkSession().getDateInHostFormat(strValue);
   setFieldNoValidate( ifds::StopDate, strValue, idDataGroup , false,true,false,false );
   setFieldNoValidate( ifds::ChrgOnPrtlRed, I_("N"), idDataGroup , false,true, false,false );
   setFieldNoValidate( ifds::ChrgOnFullRed, I_("N"), idDataGroup , false,true,false,false );
   setFieldNoValidate( ifds::Status, I_("Y"), idDataGroup , false,true,false,false );
   setFieldNoValidate( ifds::Rate, I_("0.0"), idDataGroup , true,true,false,false );
   setFieldsReadOnly(idDataGroup, true);

   FeeParamConfigList *pFeeParamConfigList = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {
      DString dstrFeeCodeSubList;	
      pFeeParamConfigList->getFeeCodeList(dstrFeeCodeSubList, ACCOUNT_LEVEL);
      setFieldAllSubstituteValues(ifds::FeeCode, idDataGroup, dstrFeeCodeSubList);
   }
}

//*******************************************************************************
void FeeParam::getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   if( idField == ifds::Currency )
   {
      DString dstrFundCode,dstrClassCode;
      BFCBO::getField(ifds::FundCode,dstrFundCode,idDataGroup);
      BFCBO::getField(ifds::ClassCode,dstrClassCode,idDataGroup);
      FundDetailList * pFundDetailList = NULL;
      const_cast<MgmtCo &>(getMgmtCo()).getFundDetailList(pFundDetailList);
      if( pFundDetailList )
      {
         pFundDetailList->getField( dstrFundCode, dstrClassCode,
                                    ifds::Currency, strValue, idDataGroup, true);        
      }
      return;
   }

   BFCBO::getField( idField, strValue, idDataGroup, formattedReturn );
}

//*********************************************************************************
SEVERITY FeeParam::ValidateDate( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateDate" ) );
   DString EffectiveDate, StopDate;
   getField(ifds::EffectiveDate, EffectiveDate, idDataGroup);
   getField(ifds::StopDate, StopDate, idDataGroup);
   if( DSTCommonFunctions::CompareDates( StopDate, EffectiveDate ) 
       != DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE );
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY FeeParam::validateFundCode( const DString& dstrfundCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );

   FundMasterList* pFundMasterList;
   getMgmtCo().getFundMasterList( pFundMasterList );
   if( dstrfundCode == I_( "CASH" ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      return(GETCURRENTHIGHESTSEVERITY());  
   }
   if( pFundMasterList != NULL && dstrfundCode != NULL_STRING )
   {
      if( pFundMasterList->IsFundExist( dstrfundCode, idDataGroup ) == false )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
      else
      {
         DString dstrEffectiveDate, dstrclassCode;
         getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
         getField( ifds::ClassCode, dstrclassCode, idDataGroup, false );
         if( pFundMasterList->IsFundValidAtDate ( dstrfundCode, dstrEffectiveDate, idDataGroup) == false )
         {
            DString idiStr;
            addIDITagValue( idiStr, I_( "FUNDNAME" ),  dstrfundCode );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, idiStr );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY FeeParam::validateClassCode( const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );

   FundDetailList *pFundDetailList;
   getMgmtCo().getFundDetailList( pFundDetailList );

   DString dstrFeeCode;
   getField( ifds::FeeCode,dstrFeeCode,idDataGroup,false );
   dstrFeeCode.strip().upperCase();

   // Class code can be blank for setup Account/Fund level.
   if ( (!dstrfundCode.empty()) && dstrClassCode.empty() )
   {
      if ( dstrFeeCode == FEE_CODE_DIVIDEND_WITHHOLDING_TAX )
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }

   DString dstrCommGroupCode;
   getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);

   if ( !dstrCommGroupCode.strip().upperCase().empty() )
   {
      if( DSTCommonFunctions::codeInList(dstrFeeCode, FEE_CODE_MANAGEMENT_HST_OVERRIDE_LIST) ||
          dstrFeeCode == FEE_CODE_TRAILER_FEE_REBATE)
      {
         if( !dstrfundCode.empty() && !dstrClassCode.empty())
         {
            ADDCONDITIONFROMFILE( CND::ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST);
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
   }
   else
   {
      if ( (!dstrfundCode.empty()) && dstrClassCode.empty() && 
           (DSTCommonFunctions::codeInList(dstrFeeCode, FEE_CODE_MANAGEMENT_HST_OVERRIDE_LIST) ||
            dstrFeeCode == FEE_CODE_TRAILER_FEE_REBATE))
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }

   if( pFundDetailList != NULL && (!dstrfundCode.empty() || !dstrClassCode.empty()) )
   {
      FundDetail *pFundDetail = NULL;
      if( pFundDetailList->getFundDetail( dstrfundCode, dstrClassCode, idDataGroup, pFundDetail ) == false )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
      else
      {
         DString dstrEffectiveDate;
         getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );

         //if fundcode is not effective then do not need to validate classCode
         SEVERITY sev = NO_CONDITION;
         sev = validateFundCode( dstrfundCode, idDataGroup);
         if(sev <= WARNING)
         {
            if( pFundDetailList->IsFundValidAtDate ( dstrfundCode, dstrClassCode, dstrEffectiveDate, idDataGroup) == false )
            {
               DString idiStr;
               addIDITagValue( idiStr, I_( "FUNDNAME" ),  dstrfundCode );
               addIDITagValue( idiStr, I_( "CLASSNAME" ), dstrClassCode );
               ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr );
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());  
}

//**************************************************************************************
SEVERITY FeeParam::setFundNumber(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundNumber" ) )
   DString dstrFundNumber,dstrFundCode,dstrCalssCode;
   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrCalssCode,idDataGroup,false);
   dstrFundCode.strip().upperCase();
   dstrCalssCode.strip().upperCase();
   getWorkSession().GetFundNumber( dstrFundCode, 
                                   dstrCalssCode, dstrFundNumber );
   DString oldFundNumber;

   getField(idField,oldFundNumber,idDataGroup,false);
   if( oldFundNumber.strip() != dstrFundNumber )
      setFieldNoValidate( ifds::FundNumber, dstrFundNumber, idDataGroup, false, false, true);
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************************
// this method is called when create a new FeeParam and user already input FundCode,FeeCode,ClassCode
// EffectiveDate
//
SEVERITY FeeParam::refreshFundFeeList(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refreshFundFeeList" ) )
   
   DString dstrFeeCode,dstrFundCode,dstrClassCode,dstrEffectiveDate,dstrCommGroupCode,dstrStopDate;
   DString dstrBrokerCode, dstrFeeId, dstrBranchCode, dstrSlsrepCode;

   getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false);
   getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
   getField(ifds::StopDate,dstrStopDate,idDataGroup,false);
//   getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false);
   getField(ifds::AcctFeeParamId,dstrFeeId,idDataGroup,false);
   dstrFeeId.strip().stripLeading('0');
   dstrFeeCode.strip().upperCase();
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   dstrEffectiveDate.strip(); 
   dstrStopDate.strip(); 
//   dstrBrokerCode.strip();
   dstrCommGroupCode.strip().upperCase();

  // if( dstrCommGroupCode == NULL_STRING && dstrFundCode == NULL_STRING ) return NO_CONDITION;

   if( dstrFeeCode == NULL_STRING || dstrEffectiveDate == NULL_STRING ) return(GETCURRENTHIGHESTSEVERITY());
/*   if (dstrCommGroupCode.empty() && (dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING)) 
   {
      ADDCONDITIONFROMFILE(CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      return(GETCURRENTHIGHESTSEVERITY());
   }
*/
  if( _pFundFeeList ) delete _pFundFeeList;  // every time create a new one
      _pFundFeeList = new FundFeeList(*this);
   DString dstrAcctNum = NULL_STRING;
// getParent()->getParent()->getField(ifds::AccountNum,dstrAcctNum,idDataGroup,false);
// dstrAcctNum.strip().stripLeading('0');

   getParent()->getParent()->getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup, false );
   getParent()->getParent()->getField( ifds::BranchCode, dstrBranchCode, idDataGroup, false );
   getParent()->getParent()->getField( ifds::Slsrep, dstrSlsrepCode, idDataGroup, false );
   dstrBrokerCode.strip();
   dstrBranchCode.strip();
   dstrSlsrepCode.strip();

   if( _pFundFeeList->init( dstrFeeCode
                           ,dstrFundCode
                           ,dstrClassCode
                           ,dstrCommGroupCode
                           ,dstrEffectiveDate
                           ,dstrAcctNum
                           ,VALIDATE_TYPE_FIND_RECORD
                           ,dstrFeeId
                           ,NULL_STRING
                           ,NULL_STRING
                           ,NULL_STRING
                           ,dstrStopDate
                           ,dstrBrokerCode
                           ,NULL_STRING
                           ,dstrBranchCode
                           ,dstrSlsrepCode
                           ) > WARNING )
   {
      delete _pFundFeeList;
      _pFundFeeList =NULL;
   }

   return(GETCURRENTHIGHESTSEVERITY());  
}

//*****************************************************************************************
SEVERITY FeeParam::validateAllowOveride(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAllowOveride" ) )
   DString dstrAllowOverride;
   if( _pFundFeeList )
   {
      _pFundFeeList->getField(ifds::AllowOverwrite,dstrAllowOverride,   idDataGroup,false);
      if( dstrAllowOverride.strip() != I_("0") )
      {
         return(  NO_CONDITION );
      }
   }
   // condition need to be added	
   ADDCONDITIONFROMFILE( CND::ERR_FEE_SET_UP_IS_NOT_ALLOWED );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************************
void FeeParam::setFeeTypeRate(const BFDataGroupId& idDataGroup)
{
   DString dstrRate,dstrFeeType;
   if( _pFundFeeList )
   {
      _pFundFeeList->getField(ifds::FeeType,dstrFeeType, idDataGroup,false);
      _pFundFeeList->getField(ifds::Rate,dstrRate, idDataGroup,false);
      setFieldNoValidate(ifds::ParamFeeType,dstrFeeType,idDataGroup ); 
      setFieldNoValidate(ifds::Rate,dstrRate,idDataGroup );
   }
}

//********************************************************************************************
SEVERITY FeeParam::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) )

   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************
SEVERITY FeeParam::setField( const BFFieldId& idField, const DString& dstrValue,
                             const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );

   SEVERITY  sevRtn = BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );
   if( sevRtn > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundNumber )
   {
      setFundClassCode(idField, idDataGroup);
   }
   else if( idField == ifds::FundCode || idField == ifds::ClassCode )
   {
      setFundNumber(idField, idDataGroup);
   }
   else if( idField == ifds::EffectiveDate )
   {
      setFieldForScale( idField, dstrValue, idDataGroup,bFormatted );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************
void FeeParam::setFundClassCode(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundClassCode" ) )
   DString dstrFundNumber,dstrFundCode(NULL_STRING),dstrCalssCode(NULL_STRING);

   getField(idField,dstrFundNumber,idDataGroup,false);

   if( dstrFundNumber.strip() != NULL_STRING )
      getWorkSession().GetFundClassCode( dstrFundNumber,dstrFundCode,dstrCalssCode);

   DString oldFundCode,oldClassCode;
   getField(ifds::FundCode,oldFundCode,idDataGroup,false);
   getField(ifds::ClassCode,oldClassCode,idDataGroup,false);

   if( oldFundCode.upperCase() != dstrFundCode.upperCase() )
   {
      setFieldNoValidate( ifds::FundCode, dstrFundCode, idDataGroup, false, true, true );
   }
   if( oldClassCode.upperCase() != dstrCalssCode.upperCase() )
   {
      setFieldNoValidate( ifds::ClassCode, dstrCalssCode, idDataGroup, false, true, true  );
   }
}

//*******************************************************************************************
SEVERITY FeeParam::validateFundClass(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) )

   DString dstrFeeCode;
   getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
   dstrFeeCode.strip().upperCase();
   bool bManageFee,bManageFeeRebate;
   FundManagementFeeOrRebate( idDataGroup, bManageFee, bManageFeeRebate );
   DString dstrFundCode,dstrClassCode;
   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
   dstrClassCode.strip().upperCase();dstrFundCode.strip().upperCase();
   DString dstrIDI,dstrFundClass;
   dstrFundClass = dstrFundCode + I_(" ") + dstrClassCode; 
   addIDITagValue( dstrIDI, IDI_FUNDCLASS, dstrFundClass );

   if( dstrFeeCode == FEE_CODE_MANAGEMENT_FEE && !bManageFee )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_FOR_MANAGEMENT_FEE, dstrIDI );            
   }
   else if( dstrFeeCode == FEE_CODE_MANAGEMENT_REBATE && !bManageFeeRebate )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_FOR_MANAGEMENT_FEE_REBATE, dstrIDI );              
   }
   else if ( DSTCommonFunctions::codeInList(dstrFeeCode, FEE_CODE_MANAGEMENT_HST_OVERRIDE_LIST) ||
      dstrFeeCode == FEE_CODE_TRAILER_FEE_REBATE)
   {
      DString commGroup;
      getField( ifds::CommGroup, commGroup, idDataGroup, false );
      commGroup.strip().upperCase();

      if (commGroup.empty())
      {
         // fund group not set - fund should be valid...
         // class may be empty - 
         if (dstrFundCode.empty() )
         {
            ADDCONDITIONFROMFILE( CND::ERR_EMPTY_FUNDCLASS );
         }
         else 
         {
            validateFundCode(dstrFundCode,idDataGroup);

            if (!dstrClassCode.empty())
            {
               validateClassCode(dstrFundCode,dstrClassCode,idDataGroup);
            }
         }
      }
      else
      {
         // fund group set.- fund and class should be empty
         if( !dstrFundCode.empty() || !dstrClassCode.empty())
         {
            ADDCONDITIONFROMFILE( CND::ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY  FeeParam::FundManagementFeeOrRebate(const BFDataGroupId& idDataGroup,bool& bManageFee,
                                              bool& bManageFeeRebate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "FundManagementFeeOrRebate" ) )
   DString dstrFundCode,dstrClassCode;
   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
   dstrClassCode.strip().upperCase();dstrFundCode.strip().upperCase();
   if( dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING ) return(GETCURRENTHIGHESTSEVERITY());
   MFAccount * pMFAccount = dynamic_cast<MFAccount *>(getParent()->getParent() );
   if( pMFAccount )
   {
      DString strGroupCode;
      pMFAccount->getField(ifds::AcctGroup, strGroupCode, idDataGroup, false);
      strGroupCode.strip().upperCase();
      GroupFundList *pGroupFundList = NULL;
      if( pMFAccount->getGroupFundListFromGroup( strGroupCode, dstrFundCode, idDataGroup, pGroupFundList) <= WARNING )
      {
         BFObjIter iter(*pGroupFundList,idDataGroup);
         DString strKey;
         pGroupFundList->getStrKey(strKey, strGroupCode, dstrFundCode, dstrClassCode);
         if( iter.positionByKey(strKey) )
         {
            DString strManageFee,dstrManageFeeRebate; 
            iter.getObject()->getField(ifds::MgtFeeElig, strManageFee, BF::HOST, false);
            iter.getObject()->getField(ifds::MgtFeeRbtElig, dstrManageFeeRebate, BF::HOST, false);
            bManageFee = strManageFee == YES? true:false;
            bManageFeeRebate = dstrManageFeeRebate == YES? true:false;        
         }//if position		
      }

	  /*if ( pGroupFundList )
		  delete pGroupFundList;*/

   }//if MFAccount
   return(GETCURRENTHIGHESTSEVERITY());
}

/*
//*****************************************************************************
SEVERITY FeeParam::validateFeeParamTypeFundClass(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeParamTypeFundClass" ) )
   DString dstrFeeType,dstrFeeCode;
   getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip().upperCase();
   getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
   dstrFeeCode.strip().upperCase();
 
	if( (dstrFeeType == SCALE  || dstrFeeType == TIER) && (dstrFeeCode != FEE_CODE_MANAGEMENT_FEE
                                                          && dstrFeeCode != FEE_CODE_MANAGEMENT_REBATE  ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_MANAGEMENT_FEE_TYPE );                
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
*/

//***************************************************************************
SEVERITY FeeParam::validateFeeCodeFundClass(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeCodeFundClass" ) )
   DString dstrFeeCode;
   getField( ifds::FeeCode,dstrFeeCode,idDataGroup,false );
   dstrFeeCode.strip().upperCase();
   if( FEE_CODE_MANAGEMENT_DISCOUNT == dstrFeeCode )
      return(GETCURRENTHIGHESTSEVERITY());

   if( _pFundFeeList == NULL && isNew() )
   {
      refreshFundFeeList( idDataGroup );
   }
   if( _pFundFeeList )
   {
      validateAllowOveride( idDataGroup);
   }
   else
   {
  /*    DString dstrFundCode, dstrClassCode,dstrCommGroupCode;
      getField(ifds::FundCode,dstrFundCode,idDataGroup,false );
      getField(ifds::ClassCode,dstrClassCode,idDataGroup,false );
      getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
      dstrFundCode.strip();dstrClassCode.strip();dstrCommGroupCode.strip();
      if( dstrCommGroupCode != NULL_STRING || dstrClassCode != NULL_STRING ||
         dstrFundCode != NULL_STRING )
      {*/

      bool bAddCondition = false;
      FeeParamConfigList*	pFeeParamConfigList;
      if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
      {
         BFObjIter iter( *pFeeParamConfigList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

         DString dstrFeeCodeComp;
         DString dstrKey;
         bool bFind = false;
         pFeeParamConfigList->buildKeyForAccountLevel(dstrFeeCode,dstrKey);
         if( iter.positionByKey(dstrKey ) ) //find record at account level
         {
            FeeParamConfig* pConfig = dynamic_cast<FeeParamConfig *>( iter.getObject() );
            if( pConfig && pConfig->isValidateSysLevelApplicable()  )
            {
               bAddCondition = true;
            }
         }
      }
      if( bAddCondition )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FUND_FEE_DOES_NOT_EXIST );
         CONDITIONVECTOR* _pCond;
         getFieldConditionVector(ifds::FeeCode,idDataGroup,_pCond );
         if( _pCond == NULL )
            _pCond = new CONDITIONVECTOR;
         int count = CURRENTCONDITIONCOUNT( );
         Condition   *c = NULL;
         for( int i = 0; i < count; i++ )
         {
            c = new Condition( *GETCURRENTCONDITION( i ));
            _pCond->push_back( c );
         };
         setFieldConditionVector(ifds::FeeCode, idDataGroup,_pCond );
         notifyObservers( ifds::FeeCode, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
      }
      else  // clear conditions which comes from view
      {
         CLEARCONDITIONSFRAMEBELOW();   
      }

//    }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeParam::validateRate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRate" ) )
   DString dstrParaFeeType,dstrFeeType;
   getField(ifds::ParamFeeType,dstrParaFeeType,idDataGroup,false);
   dstrParaFeeType.strip().upperCase();
   DString dstrRatePara;
   getField(ifds::Rate,dstrRatePara,idDataGroup );
   double dRatePara =  DSTCommonFunctions::convertToDouble( dstrRatePara );
   if( dstrParaFeeType == PERCENT )
   {
      if( dRatePara > 100.0 || dRatePara < 0.0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
      }
   }
   // for Management Fee Discount, we do not do the validation against Min and Max
   DString dstrFeeCode;
   getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false );
   dstrFeeCode.strip().upperCase();
   if( dstrFeeCode == FEE_CODE_MANAGEMENT_DISCOUNT )  return(GETCURRENTHIGHESTSEVERITY());

   if( _pFundFeeList == NULL ) return(GETCURRENTHIGHESTSEVERITY());

   _pFundFeeList->getField(ifds::FeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip().upperCase();
   if( dstrParaFeeType == dstrFeeType && (dstrParaFeeType != SCALE && dstrParaFeeType != TIER ) )
   {
      DString dstrMaxRate,dstrMinRate;
      _pFundFeeList->getField(ifds::MinFee,dstrMinRate,idDataGroup );
      _pFundFeeList->getField(ifds::MaxFee,dstrMaxRate,idDataGroup );
      double dMaxRate,dMinRate;
      dMaxRate =  DSTCommonFunctions::convertToDouble( dstrMaxRate );
      dMinRate =  DSTCommonFunctions::convertToDouble( dstrMinRate );
      if( dRatePara > dMaxRate || dRatePara < dMinRate )
      {
         DString dstrIDI;
         addIDITagValue( dstrIDI, IDI_MIN_RATE, dstrMinRate );
         addIDITagValue( dstrIDI, IDI_MAX_RATE, dstrMaxRate );
         ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_IS_OUT_OF_RANGE, dstrIDI );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// this method is called by FeeParamList
//
SEVERITY FeeParam::validateFeeScaleList(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeScaleList" ) )
   DString dstrFeeType;
   getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip().upperCase();
   if( dstrFeeType == SCALE  || dstrFeeType == TIER )
   {
      FeeScaleList *pFeeScaleList = NULL;
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

//*******************************************************************************
SEVERITY FeeParam::doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted )
{
   if( idField== ifds::FundCode )
   {
      strValue.strip().upperCase();
   }
   else if( idField == ifds::ClassCode )
   {
      strValue.strip().upperCase();
   }

   return(NO_CONDITION);
}

//*********************************************************************************
// this method is used to avoid view problem in update transaction
//
SEVERITY FeeParam::setFieldForScale( const BFFieldId& idField, const DString&  strValue, const BFDataGroupId& idDataGroup,bool bFormat )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFieldForScale" ) )

   DString dstrFeeType;
   getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip().upperCase();
   if( dstrFeeType == SCALE  || dstrFeeType == TIER )
   {
      FeeScaleList *pFeeScaleList = NULL;
      getFeeScaleList( pFeeScaleList,idDataGroup );
      if( pFeeScaleList != NULL )
      {
         BFObjIter iterScale(*pFeeScaleList,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
         while( !iterScale.end() )
         {
            iterScale.getObject()->setField(idField,strValue,idDataGroup,bFormat );
            ++iterScale;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeParam::validateGroupFundClass(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGroupFundClass" ) );
   DString dstrFundCode, dstrClassCode,dstrCommGroupCode,dstrFeeCode;
   getField( ifds::FeeCode,dstrFeeCode,idDataGroup,false );
   dstrFeeCode.strip().upperCase();

   if( FEE_CODE_MANAGEMENT_DISCOUNT == dstrFeeCode )
      return(GETCURRENTHIGHESTSEVERITY());

   getField(ifds::FundCode,dstrFundCode,idDataGroup,false );
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false );
   getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   dstrCommGroupCode.strip().upperCase();

   if (dstrCommGroupCode.empty())
   {  // fund code and class code both blank for some feecode

      //if (dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING)
      //{
      //   FeeParamConfig*  pFeeConfig = getFeeConfigObject( dstrFeeCode );
      //   if( pFeeConfig )
      //   {
      //      if( pFeeConfig->isFundClassApplicable() )
      //      {
      //         ADDCONDITIONFROMFILE( CND::ERR_EMPTY_FUNDCLASS );

      //      }
      //   }
      //}

      // fund group not set-fund should be valid.class may be empty.
      if ( DSTCommonFunctions::codeInList(dstrFeeCode,FEE_CODE_MANAGEMENT_HST_OVERRIDE_LIST) ||
         dstrFeeCode == FEE_CODE_TRAILER_FEE_REBATE)
      {
         if (dstrFundCode.empty() )
         {
            ADDCONDITIONFROMFILE( CND::ERR_EMPTY_FUNDCLASS );
         }
         else 
         {
            validateFundCode(dstrFundCode,idDataGroup);

            if ( !dstrClassCode.empty() )
            {
               validateClassCode(dstrFundCode,dstrClassCode,idDataGroup);
            }
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

   return(GETCURRENTHIGHESTSEVERITY());
} 

//***********************************************************************************
// 
//
SEVERITY FeeParam::validateFeeOverlap(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeOverlap" ) );

   SEVERITY sev = NO_CONDITION;

   DString dstrFeeCode, dstrFundCode, dstrClassCode;

   getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
   dstrFeeCode.strip().upperCase();
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   FeeParamList* pList = dynamic_cast<FeeParamList*>( getParent() );
   if( pList->doMoreRecordsExist() ) 
   {
      // tuning: if there is more exist we check back end 
      // otherwise we will only check desktop
      // hopefully 90% will be covered by desktop

      DString dstrCommGroupCode, dstrEffectiveDate,dstrStopDate;
      DString dstrBrokerCode;
      DString dstrAcctNum;
      DString dstrFeeId;

      getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
      getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false);

      getField(ifds::StopDate,dstrStopDate,idDataGroup,false);
      getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false);
      getField(ifds::AcctFeeParamId,dstrFeeId, idDataGroup,false);

      getParent()->getParent()->getField(ifds::AccountNum,dstrAcctNum,idDataGroup,false);
      dstrAcctNum.strip().stripLeading('0');
      dstrEffectiveDate.strip(); 
      dstrStopDate.strip();
      dstrBrokerCode.strip();
      dstrCommGroupCode.strip().upperCase();
      dstrFeeId.strip().stripLeading('0');	
      sev = checkDuplicateAndCoexit( idDataGroup
                                    ,dstrFeeCode
                                    ,dstrFundCode 
                                    ,dstrClassCode
                                    ,dstrCommGroupCode
                                    ,dstrEffectiveDate
                                    ,dstrAcctNum
                                    ,VALIDATE_TYPE_DUP_CHECK
                                    ,dstrFeeId
                                    ,NULL_STRING
                                    ,NULL_STRING
                                    ,NULL_STRING
                                    ,dstrStopDate
                                    ,dstrBrokerCode
                                    ,NULL_STRING
                                    ,NULL_STRING 
                                    ,NULL_STRING
                                    ,NULL_STRING
                                    );

      if ( sev <= WARNING )
      {
         DString excludeFeeCode(NULL_STRING);	 
         // check coexist for 18 and 180
         if(dstrFeeCode == FEE_CODE_MANAGEMENT_DISCOUNT || dstrFeeCode == FEE_CODE_MANAGEMENT_FEE )
         {
            excludeFeeCode = dstrFeeCode == FEE_CODE_MANAGEMENT_DISCOUNT?
                                            FEE_CODE_MANAGEMENT_FEE:FEE_CODE_MANAGEMENT_DISCOUNT;
            sev = checkDuplicateAndCoexit( idDataGroup
                                          ,dstrFeeCode
                                          ,dstrFundCode 
                                          ,dstrClassCode
                                          ,dstrCommGroupCode
                                          ,dstrEffectiveDate
                                          ,dstrAcctNum
                                          ,VALIDATE_TYPE_COEXIST
                                          ,dstrFeeId
                                          ,NULL_STRING
                                          ,NULL_STRING
                                          ,NULL_STRING
                                          ,dstrStopDate
                                          ,dstrBrokerCode
                                          ,NULL_STRING
                                          ,NULL_STRING 
                                          ,NULL_STRING
                                          ,excludeFeeCode
                                          );
         }
      }
   }

   else{ // All records are already at desktop side, go here

      if( pList->FindDeletedOverlapRecord(this,idDataGroup,NULL_STRING,BFObjIter::NON_DELETED) )
      { // validate overlapping

         DString dstrTemp;                 
         addIDITagValue( dstrTemp, IDI_CODE, dstrFeeCode +I_(" ") + dstrFundCode + I_(" ") + dstrClassCode);         
         ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_CODE_OVERLAPED, dstrTemp);
         sev = GETCURRENTHIGHESTSEVERITY();		
      }
      else
      { // check coexist here

         DString excludeFeeCode(NULL_STRING);	 
         // check coexist for 18 and 180
         if(dstrFeeCode == FEE_CODE_MANAGEMENT_DISCOUNT || dstrFeeCode == FEE_CODE_MANAGEMENT_FEE )
         {
            excludeFeeCode = dstrFeeCode == FEE_CODE_MANAGEMENT_DISCOUNT?
                                            FEE_CODE_MANAGEMENT_FEE:FEE_CODE_MANAGEMENT_DISCOUNT;

            if( pList->FindDeletedOverlapRecord(this,idDataGroup,excludeFeeCode,BFObjIter::NON_DELETED) )
            { 
               DString dstrTemp;                 
               addIDITagValue( dstrTemp, I_("FEECODE1"), dstrFeeCode);
               addIDITagValue( dstrTemp, I_("FEECODE2"), excludeFeeCode);					
               ADDCONDITIONFROMFILEIDI( CND::ERR_FEECODE_CANNOT_COEXIT, dstrTemp);
               sev = GETCURRENTHIGHESTSEVERITY();
            }
         }
      }	
   }

   return sev;
}

//***********************************************************************************
void  FeeParam::setupFeeCodeRelatedFields(const BFDataGroupId& idDataGroup, bool bIsSameDate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setupFeeCodeRelatedFields" ) );
	DString dstrFeeCode;
	getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);
	dstrFeeCode.strip().upperCase();
   
	FeeParamConfig *pFeeParamConfig = getFeeConfigObject(dstrFeeCode);
	if ( pFeeParamConfig )
	{
			//for those fields with substitute list, get the substitute list from FeeParamConfig CBO
			//and set them to field properties.
			DString dstrSubList = NULL_STRING;
			pFeeParamConfig->getFeeTypeList(dstrSubList);
			setFieldAllSubstituteValues(ifds::ParamFeeType, idDataGroup, dstrSubList);

			//For CommGroup, call getFundGroupType from FeeParamConfig, and the value will be used as
			//input parameter for view 229 (FundCommGroupList)
			DString dstrGroupType = NULL_STRING;
			pFeeParamConfig->getFundGroupType(dstrGroupType);
			dstrSubList = I_("NA=;");
			if (dstrGroupType != NULL_STRING) 
			{
				FundCommGroupList* pFundCommGroupListP = NULL;
				if(getMgmtCo().getFundCommGroupList( dstrGroupType,pFundCommGroupListP ) <= WARNING )
				{
					pFundCommGroupListP->getCommGroupSubstitute(dstrSubList);
				}
			}
			setFieldAllSubstituteValues( ifds::CommGroup,idDataGroup, dstrSubList );
			//setup Basedon list
			dstrSubList = NULL_STRING;		
			pFeeParamConfig->getBaseOnList(dstrSubList);
			setFieldAllSubstituteValues(ifds::BasedOn, idDataGroup, dstrSubList);
			setFieldRequired( ifds::BasedOn, idDataGroup, !dstrSubList.empty() );
			setValidFlag( ifds::BasedOn, idDataGroup, dstrSubList.empty());

			if (!bIsSameDate && idDataGroup == BF::HOST ) //existing record with different business date
			{
				setFieldReadOnly(ifds::FundCode, idDataGroup, true);
				setFieldReadOnly(ifds::ClassCode, idDataGroup, true);
				setFieldReadOnly(ifds::FundNumber, idDataGroup, true);
				setFieldReadOnly(ifds::ParamFeeType, idDataGroup, true);
				setFieldReadOnly(ifds::CommGroup, idDataGroup,true);
				setFieldReadOnly(ifds::EffectiveDate, idDataGroup, false);
				setFieldReadOnly(ifds::StopDate, idDataGroup, false);
				setFieldReadOnly(ifds::Rate, idDataGroup, true);
				setFieldReadOnly(ifds::BasedOn, idDataGroup, true);

			}
			else
			{
			//newly created records, or have same business date
			//for those fields not applicable in class FeeParamConfig CBO, set them to read only
				bool bFundClassApplicable = pFeeParamConfig->isFundClassApplicable();
				setFieldReadOnly(ifds::FundCode, idDataGroup, !bFundClassApplicable);
				setFieldReadOnly(ifds::ClassCode, idDataGroup, !bFundClassApplicable);
				setFieldReadOnly(ifds::FundNumber, idDataGroup, !bFundClassApplicable);
				setFieldReadOnly(ifds::ParamFeeType, idDataGroup, false);
				setFieldReadOnly(ifds::CommGroup, idDataGroup,false);
				setFieldReadOnly(ifds::EffectiveDate, idDataGroup, false);
				setFieldReadOnly(ifds::StopDate, idDataGroup, false);
				setFieldReadOnly(ifds::Rate, idDataGroup, false);
				setFieldReadOnly(ifds::BasedOn, idDataGroup, false);
				setFieldValid( ifds::FeeCodeFundClassDateCross, idDataGroup, false );
				setFieldValid( ifds::GroupFundClass, idDataGroup, false );				
		
/*
				if (idDataGroup == BF::HOST && bFundClassApplicable )
				{

	

					bool bRequired = dstrFeeCode != FEE_CODE_MANAGEMENT_DISCOUNT; 
					setFieldRequired(ifds::FundCode , idDataGroup, bRequired );
					setFieldRequired(ifds::ClassCode , idDataGroup, bRequired );

				}
*/
			}	

	}
   if( GETCURRENTHIGHESTSEVERITY() > WARNING )
   {
      PROMOTECONDITIONS();
      CLEARCONDITIONSFRAMECURRENT();
   }
}

//***********************************************************************************
FeeParamConfig*  FeeParam::getFeeConfigObject(const DString& dstrFeeCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeConfigObject" ) );

   FeeParamConfig* pFeeParamConfig = NULL;
   FeeParamConfigList*	pFeeParamConfigList;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {

      if (pFeeParamConfigList)
      {
         BFObjIter iter( *pFeeParamConfigList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

         DString dstrFeeCodeComp;
         DString dstrKey;
         bool bFind = false;
         pFeeParamConfigList->buildKeyForAccountLevel(dstrFeeCode,dstrKey);
         if( iter.positionByKey(dstrKey ) ) //find record at account level
         {
            bFind = true;
         }
         else 
         {
            pFeeParamConfigList->buildKeyForSystemLevel(dstrFeeCode,dstrKey);
            if( iter.positionByKey(dstrKey ) )
            {
               bFind = true;

            }
         }
         if(bFind )
         {
            pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
         }

      }
   }
   else {	
      PROMOTECONDITIONS();
      CLEARCONDITIONSFRAMECURRENT(); 	
   }

   return pFeeParamConfig;
}

//***********************************************************************************
SEVERITY FeeParam::/*validateFeeByFundFeeList*/
                   checkDuplicateAndCoexit 
                   (	 
                   const BFDataGroupId& idDataGroup
                   ,const DString& dstrFeeCode
                   ,const DString& dstrFundCode 
                   ,const DString& dstrClassCode
                   ,const DString& dstrCommGroupCode
                   ,const DString& dstrEffectiveDate
                   ,const DString& dstrAcctNum
                   ,const DString& dstrValidateType
                   ,const DString& dstrFeeId
                   ,const DString& dstrFamilyCode
                   ,const DString& dstrFundFrom
                   ,const DString& dstrClassFrom
                   ,const DString& dstrStopDate
                   ,const DString& dstrBrokerCode
                   ,const DString& dstrShGroup
                   ,const DString& dstrBranchCode 
                   ,const DString& dstrSalesRepCode
                   ,const DString& dstrExcludeFeeCode

                   )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeOverlap" ) );

   SEVERITY sev = NO_CONDITION;
   FundFeeList *pFundFeeList = new FundFeeList(*this);


   if( pFundFeeList->init(dstrFeeCode,
                          dstrFundCode, 
                          dstrClassCode,
                          dstrCommGroupCode,
                          dstrEffectiveDate,
                          dstrAcctNum,
                          dstrValidateType,
                          dstrFeeId,
                          NULL_STRING,
                          NULL_STRING,
                          NULL_STRING,   
                          dstrStopDate,
                          dstrBrokerCode,
                          NULL_STRING,
                          NULL_STRING,
                          NULL_STRING,
                          dstrExcludeFeeCode
                          ) <= WARNING )

	{
		DString dstrDupCheck;
		pFundFeeList->getField(ifds::DuplicateExist,dstrDupCheck,idDataGroup,false);

		if (dstrDupCheck.strip().upperCase() == YES )
		{
			FeeParamList* pList = dynamic_cast<FeeParamList* >( getParent() );
			if( dstrExcludeFeeCode != NULL_STRING )
			{
				DString dstrTemp;                 
				addIDITagValue( dstrTemp, I_("FEECODE1"), dstrFeeCode);
				addIDITagValue( dstrTemp, I_("FEECODE2"), dstrExcludeFeeCode);					
				ADDCONDITIONFROMFILEIDI( CND::ERR_FEECODE_CANNOT_COEXIT, dstrTemp);
				sev = GETCURRENTHIGHESTSEVERITY();
			}
			else
			{  // overlapping
			
				DString dstrTemp;                 
				addIDITagValue( dstrTemp, IDI_CODE, dstrFeeCode +I_(" ") + dstrFundCode + I_(" ") + dstrClassCode);         
				ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_CODE_OVERLAPED, dstrTemp);
				sev = GETCURRENTHIGHESTSEVERITY();
				
			}
		}
	}
   else
   {
      sev = GETCURRENTHIGHESTSEVERITY();
   }
   if (pFundFeeList) 
   {
      delete pFundFeeList;
      pFundFeeList =NULL;       
   }

   return(sev);
}

//************************************************************************************
bool FeeParam::isActiveRecord(const BFDataGroupId& idDataGroup)
{
   DString strCurBusDate, strStopDate;
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
   getField(ifds::StopDate,strStopDate,idDataGroup,false);

   if( DSTCommonFunctions::CompareDates(strCurBusDate,strStopDate ) != DSTCommonFunctions::SECOND_EARLIER )
   {
      return(true);
   }
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParam.cpp-arc  $
// 
//    Rev 1.60   Jun 14 2011 16:17:24   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level, logic block missing .
// 
//    Rev 1.59   Jun 09 2011 16:28:48   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level, got claification from business perspective.
// 
//    Rev 1.58   Jun 08 2011 15:35:54   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level, new issue on account level fee setup, for fee code 79,81 where fund group is available only fund code is allowed.
// 
//    Rev 1.57   Jun 06 2011 04:28:14   kitticha
// IN#2547729 - Error displayed when fee parameter set at acct-fund level for FLAT fee type.
// 
//    Rev 1.56   Jun 03 2011 12:21:20   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level, new issue on account level fee setup, take out logic which skip validation on class level. 
// 
//    Rev 1.55   May 31 2011 05:49:56   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level, new issue on account level fee setup.
// 
//    Rev 1.54   May 03 2011 14:33:12   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level, new issue.
// 
//    Rev 1.53   Feb 28 2011 18:32:18   dchatcha
// IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level.
// 
//    Rev 1.52   Oct 15 2010 09:37:44   jankovii
// IN 2292935 - R101 - AIC Trailer Phase 2 -  A/C Level existing Fee Parameter
// 
//    Rev 1.51   Oct 25 2005 12:51:26   popescu
// Incident# 434042 - removed the deletes of the group fund list. since now is cached at the mgmt co leve.
// 
//    Rev 1.50   Mar 13 2005 17:14:52   winnie
// Restore the previous version. No longer have a pointer in Group object for GroupFundList but instead have the object which create it delete the GroupFundList as soon as finish using it.
//
//    Rev 1.49   Mar 11 2005 14:08:46   smithdav
// Fixed bug in Group::getGroupFundListByFund function where BPS threads clashed the function call concurrently.
// 
//    Rev 1.48   Feb 15 2005 20:18:34   winnie
// PTS 237768 : Get Group Fund by Fund Code to speed up the performance.
// 
//    Rev 1.47   Nov 14 2004 14:40:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.46   Nov 04 2004 17:37:28   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.45   Jun 02 2004 14:08:30   YINGBAOL
// PTS10021889:if there is more record available, validation based on view
// 
//    Rev 1.44   Mar 18 2004 10:51:04   YINGBAOL
// PTS10021889: 1. separate checking overlapping and coeixst logic in view 197;2. Turning: if all records are already at desktop side, desktop will not call view 197, this will improve real time performance.
// 
//    Rev 1.43   Jan 19 2004 11:54:04   YINGBAOL
// PTS10026088: validate Fee Param at higher level  is now based on the feesetup table.
// 
//    Rev 1.42   Sep 09 2003 18:21:14   HERNANDO
// Sync'd with 1.35.1.4; PTS 10018491.
// 
//    Rev 1.41   Sep 08 2003 09:12:54   YINGBAOL
// remove force user to input fund/class if fundClassApplicabe is Yes in feeconfiguration table.
// 
//    Rev 1.40   Aug 30 2003 16:07:16   YINGBAOL
// AMS Fee Calculation enhancement
// 
//    Rev 1.39   Jul 04 2003 15:42:46   YINGBAOL
// fix reset issue
// 
//    Rev 1.38   Jun 26 2003 10:10:04   linmay
// modified init() for Pinnacle Flat fee
// 
//    Rev 1.37   Jun 20 2003 16:21:10   linmay
// added Flat Fee and Syc with 1.35.1.3
// 
//    Rev 1.36   Jun 03 2003 10:07:16   linmay
// added BasedOn Field
// 
//    Rev 1.34   May 27 2003 12:59:34   linmay
// PTS Ticket # 10017099
// 
//    Rev 1.33   Apr 12 2003 15:14:34   FENGYONG
// When fund is not effective then don't need to check if class is effective
// 
//    Rev 1.32   Apr 02 2003 16:41:32   linmay
// sync up
// 
//    Rev 1.31   Mar 25 2003 14:44:34   linmay
// sync up 
// 
//    Rev 1.30   Mar 21 2003 18:09:02   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.29   Mar 18 2003 18:04:20   linmay
// modified setupFeeCodeRelatedFields(const BFDataGroupId& idDataGroup, bool bIsSameDate)
// 
//    Rev 1.28   Mar 18 2003 11:54:02   linmay
// added validateType for view229
// 
//    Rev 1.27   Mar 10 2003 14:42:48   linmay
// added validateFeeOverlap, setupFeeCodeRelatedFields
// 
//    Rev 1.26   Feb 17 2003 15:33:20   YINGBAOL
// sync. 1.23.1.0
// 
//    Rev 1.25   Feb 17 2003 13:10:38   linmay
// added BrokerCode
// 
//    Rev 1.24   Feb 17 2003 10:17:20   YINGBAOL
// FundFeeList change
// 
//    Rev 1.23   Jan 22 2003 17:51:04   YINGBAOL
// Set CommGroup Substitute
// 
//    Rev 1.22   Jan 14 2003 13:53:24   YINGBAOL
// fix validation CommGroup issues
// 
//    Rev 1.21   Jan 04 2003 15:28:28   WINNIE
// Either Fund/Class or CommGroup must be entered; FundClass only required if CommGroup is blank
// 
//    Rev 1.20   Jan 03 2003 19:43:42   YINGBAOL
// change FundGroup to CommGroup
// 
//    Rev 1.19   Jan 03 2003 16:25:52   linmay
// rename CommGroupCode to FundGroup
// 
//    Rev 1.18   Jan 02 2003 15:19:26   linmay
// added ValidateGroupFundClass(), modified validateClassCode(), validateFundCode(), refreshFundFeeList(), validateFeeCodeFundClass(),
// added CommGroup to ClassFieldInfo
// 
//    Rev 1.17   Nov 19 2002 10:16:02   HSUCHIN
// changed fundnumber from decimal to text
// 
//    Rev 1.16   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.15   Aug 29 2002 12:55:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.14   Jul 04 2002 12:02:36   YINGBAOL
// fix date format
// 
//    Rev 1.13   24 May 2002 15:07:08   KOVACSRO
// doPresetField changes.
// 
//    Rev 1.12   22 May 2002 18:28:36   PURDYECH
// BFData Implementation
// 
//    Rev 1.11   Mar 19 2002 16:50:58   YINGBAOL
// add setFieldForScale
// 
//    Rev 1.10   Mar 19 2002 09:50:12   YINGBAOL
// add logic for management Fee Discount
// 
//    Rev 1.9   Mar 08 2002 10:10:50   YINGBAOL
// Add condition ERR_VALUE_BETWEEN_0_AND_100 
// 
//    Rev 1.8   Mar 07 2002 18:23:56   YINGBAOL
// don't check FundFeeList at begin
// 
//    Rev 1.7   Mar 06 2002 15:41:18   YINGBAOL
// change some business rules
// 
//    Rev 1.6   Mar 05 2002 14:00:54   YINGBAOL
// change rate validation
// 
//    Rev 1.5   Mar 01 2002 16:24:36   YINGBAOL
// add dopresetField 
// 
//    Rev 1.4   Mar 01 2002 14:56:18   YINGBAOL
// fix FeeType Validation
// 
//    Rev 1.3   Feb 28 2002 12:45:38   YINGBAOL
// add more validation
// 
//    Rev 1.2   Feb 26 2002 13:11:38   YINGBAOL
// fix validate date etc.
// 
//    Rev 1.1   Feb 22 2002 14:18:42   YINGBAOL
// more function added
// 
//    Rev 1.0   Feb 01 2002 15:16:12   YINGBAOL
// Initial revision.
 * 

  */