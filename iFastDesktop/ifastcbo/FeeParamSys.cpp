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
// ^FILE   : FeeParamSys.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 10, 2002
//
// ^CLASS    : FeeParamSys
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeParamSys.hpp"
#include "FeeParamSyslist.hpp"
#include "FeeScaleSysList.hpp"
#include <ifastdataimpl\dse_dstc0229_vw.hpp>
#include <ifastdataimpl\dse_dstc0230_req.hpp>
#include <ifastdataimpl\dse_dstc0230_vw.hpp>
#include <ifastdataimpl\dse_dstc0253_vw.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "FundCommGroupList.hpp"
#include "grouplist.hpp"
#include "CurrencyClass.hpp"
#include "feeparamconfiglist.hpp"
#include "feeparamconfig.hpp"
#include "fundfeelist.hpp"
#include "broker.hpp"
#include "agentlist.hpp"
#include "branchlist.hpp"
#include "brokerlist.hpp"
#include "shrfamily.hpp"
#include "documenttypeoverridelist.hpp"
#include "FeeScaleSys.hpp"
#include "feethrshldsyslist.hpp"
#include "feemodel.hpp"
#include "feemodellist.hpp"
#include "fundmasterlist.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME						= I_( "FeeParamSys" );
   const I_CHAR * const FEE_SCALE_SYS_LIST			= I_( "FeeScaleSysList" );
   const I_CHAR * const FLAT							   = I_( "0" );
   const I_CHAR * const PERCENT							= I_( "1" );
   const I_CHAR * const SCALE							   = I_( "2" );
   const I_CHAR * const TIER							   = I_( "3" );   
   const I_CHAR * const YES								= I_("Y");
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE		= I_("18");
   const I_CHAR * const FEE_CODE_MANAGEMENT_REBATE	= I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT	= I_("180");
   const I_CHAR * const FEE_GUARANTEE_FEE				= I_("816");
   const I_CHAR * const IDI_FUNDCLASS					= I_("FUNDCLASS");   
   const I_CHAR * const IDI_RATE						   = I_("RATE");
   const I_CHAR * const IDI_MIN_RATE					= I_("MINRATE");
   const I_CHAR * const IDI_MAX_RATE					= I_("MAXRATE");
   const I_CHAR * const IDI_GRADE						= I_("GRADE");
   const I_CHAR * const SEARCH_BY_FEE_CODE			= I_("FeeCode");
   const I_CHAR * const NO								   = I_("No");
   const I_CHAR * const BASEDON_SCALE					= I_( "1" );
   const I_CHAR * const GARANTED_WITHDRAWAL_BENEFIT = I_( "5" );
   const I_CHAR * const IDI_CODE						   = I_("CODE");  
   const I_CHAR * const VALIDATE_TYPE					= I_("DupCheck");
   const I_CHAR * const FEE_CODE_VISCOUNT_FEE		= I_("118");
   const I_CHAR * const SYSTEM_LEVEL					= I_("SYSTEM");
   const I_CHAR * const TRAILER_FEE                = I_("8");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;

   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId FeeFundClassCross;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId SplitCommTransTypes;
   extern CLASS_IMPORT const BFTextFieldId MgtFeeElig;
   extern CLASS_IMPORT const BFTextFieldId MgtFeeRbtElig;
   extern CLASS_IMPORT const BFTextFieldId FeeCodeFundClassDateCross;
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit1;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit2;
   extern CLASS_IMPORT const BFTextFieldId FeeRecordOverlapCheck;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId NewBusiness;
   extern CLASS_IMPORT const BFTextFieldId BrokerBranch;
   extern CLASS_IMPORT const BFDateFieldId ScaleEffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId DuplicateExist;
   extern CLASS_IMPORT const BFTextFieldId FeeModelFundGroupFund;
   extern CLASS_IMPORT const BFTextFieldId FeeLevel;
   extern CLASS_IMPORT const BFTextFieldId FundList;
   extern CLASS_IMPORT const BFTextFieldId ThresholdAmtApply;
   extern CLASS_IMPORT const BFTextFieldId TrailerFeeArch;
   extern CLASS_IMPORT const BFDecimalFieldId ScaleMinRateChk;
   extern CLASS_IMPORT const BFDecimalFieldId ScaleMaxRateChk;
   extern CLASS_IMPORT const BFTextFieldId FeeModelType;
   extern CLASS_IMPORT const BFTextFieldId FeeModelFundGroup;
   extern CLASS_IMPORT const BFTextFieldId CalcCurrency;
   extern CLASS_IMPORT const BFTextFieldId ModelAggregationMethod;
   extern CLASS_IMPORT const BFTextFieldId CalcRateType;
   extern CLASS_IMPORT const BFTextFieldId EligibleFundBy;
   extern CLASS_IMPORT const BFTextFieldId GroupFundClass;
   extern CLASS_IMPORT const BFTextFieldId AdvisorFeeAppl;
   extern CLASS_IMPORT const BFTextFieldId FeeCodeOverrideDescription;
   extern CLASS_IMPORT const BFTextFieldId FundClassFeeCode;
}

namespace CND
{  // Conditions used
   extern const long ERR_AT_LEAST_ONE_RECORD_FOR_SCALE;
   extern const long ERR_FEE_CODE_OVERLAPED;  
   extern const long ERR_INVALID_FAMILY_CODE;  
   extern const long ERR_BROKER_EMPTY;
   extern const long ERR_BRANCH_EMPTY;
   extern const long ERR_SALES_REP_EMPTY;
   extern const long ERR_INVALID_BROKER_CODE;  
   extern const long ERR_INVALID_BRANCH_CODE;  
   extern const long ERR_INVALID_SALES_REP_CODE;  
   extern const long ERR_SALESPERSON_IS_NOT_PERMITTED;  
   extern const long ERR_FEE_TYPE_SCALE_ONLY;
   extern const long ERR_RATE_IS_OUT_OF_RANGE;
   extern const long ERR_RATE_LESS_THAN_MIN;
   extern const long ERR_SYS_FEE_INVALID_GWB_BASEDON;
   extern const long ERR_NEW_ARCH_TRAILER_FEE;
   extern const long ERR_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP;
   extern const long WARN_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP;
   extern const long ERR_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND;
   extern const long WARN_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND;
   extern const long ERR_BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND;
   extern const long WARN_BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND;
}


namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP;
   extern CLASS_IMPORT I_CHAR * const FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND;
   extern CLASS_IMPORT I_CHAR * const BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND;
}

namespace FEETYPE
{
   const I_CHAR * const FLAT                 = I_( "0" );
   const I_CHAR * const PERCENTAGE           = I_( "1" );
   const I_CHAR * const SCALE                = I_( "2" );
   const I_CHAR * const TIER                 = I_( "3" );
   const I_CHAR * const TIER_BY_THRESHOLD    = I_( "4" );
   const I_CHAR * const SCALE_BY_THRESHOLD   = I_( "5" );
}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FundFromCode,				BFCBO::NONE,                 0 }, 
   { ifds::ClassFromCode,				BFCBO::NONE,                 0 }, 
   { ifds::FundCode,					   BFCBO::NONE,                 0 }, 
   { ifds::ClassCode,					BFCBO::NONE,                 0 }, 
   { ifds::MinFee,						BFCBO::NONE,                 0 }, 
   { ifds::MaxFee,						BFCBO::NONE,                 0 }, 
   { ifds::OnPW,						   BFCBO::NONE,                 0 }, 
   { ifds::OnFW,						   BFCBO::NONE,                 0 }, 
   { ifds::FundNumber,					BFCBO::NONE,                 0 }, 
   { ifds::FromFundNumber,				BFCBO::NONE,                 0 }, 
   { ifds::FundClass,					BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::Active,						BFCBO::NONE,                 0 }, 
   { ifds::FeeCodeFundClassDateCross,	BFCBO::NONE,              0 }, 
   { ifds::BrokerCode,					BFCBO::NONE,                 0 }, 
   { ifds::BrokerName,					BFCBO::NONE,                 0 }, 
   { ifds::AllowOverrideType,			BFCBO::NONE,                 0 }, 
   { ifds::BranchCode,					BFCBO::NONE,                 0 }, 
   { ifds::SlsrepCode,					BFCBO::NONE,                 0 }, 
   { ifds::BranchName,					BFCBO::NONE,                 0 }, 
   { ifds::SlsrepName,					BFCBO::NONE,                 0 }, 
   { ifds::FamilyCode,					BFCBO::NONE,                 0 }, 
   { ifds::FamilyName,					BFCBO::NONE,                 0 }, 
   { ifds::BasedOn,						BFCBO::NONE,                 0 }, 
   { ifds::HowPaid,						BFCBO::NONE,                 0 }, 
   { ifds::CommGroup,					BFCBO::NONE,                 0 }, 
   { ifds::ShGroup,						BFCBO::NONE,                 0 }, 
   { ifds::FundList,					   BFCBO::NONE,                 0 }, 
   { ifds::ThresholdAmt,				BFCBO::NONE,                 0 }, 
   { ifds::ThresholdCurrency,			BFCBO::NONE,                 0 }, 
   { ifds::ShGroupName,					BFCBO::NONE,                 0 }, 
   { ifds::Currency,					   BFCBO::NONE,                 0 }, 
   { ifds::FieldCrossEdit1,			BFCBO::NONE,			  	     0 }, 
   { ifds::FeeRecordOverlapCheck,	BFCBO::NONE,				     0 }, 
   { ifds::FieldCrossEdit2,			BFCBO::IMMEDIATE_VALIDATION, 0 }, 
	{ ifds::AppliedMethod,				BFCBO::NONE,				     0 }, 
	{ ifds::DistributionChannel,		BFCBO::NONE,				     0 }, 
	{ ifds::FeeModelCode,		      BFCBO::NONE,				     0 }, 
 	{ ifds::FundLink,		            BFCBO::NONE,				     0 }, 
   { ifds::TaxInclusive,		      BFCBO::NONE,				     0 }, 
   { ifds::ScaleMinRateChk,		   BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::ScaleMaxRateChk,		   BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FeeModelFundGroupFund,	BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FeeModelFundGroup,			BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FundClassFeeCode,			BFCBO::IMMEDIATE_VALIDATION, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FeeParamSys::FeeParamSys( BFAbstractCBO &parent )
: FeeParamBase( parent )
// NOTE: it is inherently unsafe to use "this" in an initializer.  CP20041110
#pragma warning( push )
#pragma warning( disable:4355 )
, m_FundClassRules(*this)
#pragma warning( pop )
, pFeeScaleList_( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit(ifds::FieldCrossEdit1, ifds::MaxFee);
   addCrossEdit(ifds::FieldCrossEdit1, ifds::MinFee);

   addCrossEdit(ifds::FeeRecordOverlapCheck, ifds::EffectiveDate);
   addCrossEdit(ifds::FeeRecordOverlapCheck, ifds::StopDate);

   addCrossEdit(ifds::FieldCrossEdit2, ifds::BasedOn);
   addCrossEdit(ifds::FieldCrossEdit2, ifds::ParamFeeType);
   
   //IN2981408 - System Level Performance Fee
   addCrossEdit(ifds::ScaleMinRateChk, ifds::Rate);
   addCrossEdit(ifds::ScaleMinRateChk, ifds::MinFee);
   addCrossEdit(ifds::ScaleMaxRateChk, ifds::Rate);
   addCrossEdit(ifds::ScaleMaxRateChk, ifds::MaxFee);

   addCrossEdit(ifds::FeeModelFundGroupFund,	ifds::FeeModelCode);
   addCrossEdit(ifds::FeeModelFundGroupFund, ifds::CommGroup);
   addCrossEdit(ifds::FeeModelFundGroupFund, ifds::FundCode);
   addCrossEdit(ifds::FeeModelFundGroupFund, ifds::ClassCode);

   addCrossEdit(ifds::FeeModelFundGroup, ifds::FeeModelCode);
   addCrossEdit(ifds::FeeModelFundGroup, ifds::CommGroup);

   /* DIF Fund Class cross-edit */
   addCrossEdit (ifds::FundClassFeeCode, ifds::FundCode);
   addCrossEdit (ifds::FundClassFeeCode, ifds::ClassCode);
   addCrossEdit (ifds::FundClassFeeCode, ifds::FundNumber);
   addCrossEdit (ifds::FundClassFeeCode, ifds::FeeCode);

}
//******************************************************************************************
FeeParamSys::~FeeParamSys()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//************************************************************************************
SEVERITY FeeParamSys::InitNew( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long)" ) );

	setObjectNew();
//   setFieldNoValidate(ifds::TaxInclusive, I_("0"), idDataGroup, false, true); //not applicable
   //setup substitution list for feecode 
   FeeParamConfigList *pFeeParamConfigList = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {
		   DString dstrFeeCodeSubList;	
	     pFeeParamConfigList->getFeeCodeList(dstrFeeCodeSubList, SYSTEM_LEVEL);
       setFieldAllSubstituteValues(ifds::FeeCode, idDataGroup, dstrFeeCodeSubList);
       overrideDealerServiceFeeDescription(idDataGroup);
   }
   else
   {
		CLEARCONDITIONSFRAMECURRENT(); 
   }

   // at begin we set all fields readonly except FeeCode 
    setFieldsReadOnly(idDataGroup, true);

    _salesRepByBranch = NULL_STRING;

	_familyName = NULL_STRING;
	_slsrepName = NULL_STRING;
	_branchCode = NULL_STRING;
	_dstrFeeType = NULL_STRING;
    _dstrMinRate = NULL_STRING;
    _dstrMaxRate = NULL_STRING;

  	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************************
void FeeParamSys::overrideDealerServiceFeeDescription(const BFDataGroupId &idDataGroup)
{
    DString dstrAdvisorFeeAppl, dstrFeeCodeSubList, newDescription;
    BFProperties *pBFPropertiesFeeCode =  getFieldProperties(ifds::FeeCode, idDataGroup);

    getWorkSession().getOption(ifds::AdvisorFeeAppl, dstrAdvisorFeeAppl, idDataGroup, false);
      
    if (pBFPropertiesFeeCode && dstrAdvisorFeeAppl.stripAll().upperCase() == YES)
    {
        //Change description from Dealer Service Fee(94) to Advisor Fee.
        pBFPropertiesFeeCode->getAllSubstituteValues(dstrFeeCodeSubList);

        newDescription = I_("94=94 - ") + DSTCommonFunctions::getDescription(I_("94"), ifds::FeeCodeOverrideDescription) + I_(";");

        DString tmpSubList(dstrFeeCodeSubList);
        int nPos = dstrFeeCodeSubList.find(I_("94="));

        if (nPos != -1)
        {
            dstrFeeCodeSubList = tmpSubList.left(nPos) + newDescription;
            tmpSubList = tmpSubList.right(tmpSubList.length() - nPos);

            int rnPos = tmpSubList.find(';');

            if (rnPos != -1)
            {
                dstrFeeCodeSubList = dstrFeeCodeSubList + tmpSubList.right(tmpSubList.length() - rnPos - 1);
            }

            setFieldAllSubstituteValues(ifds::FeeCode, idDataGroup, dstrFeeCodeSubList);
        }
    }
}
    

//******************************************************************************************
SEVERITY FeeParamSys::Init(const BFData& data, bool bDefault)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );  
   attachDataObject(const_cast<BFData&>(data), false);  

   if ( !bDefault )
   {
	   DString dstrFundCode,dstrClassCode,dstrFromFundCode, dstrFromClassCode,strValue;
	   BFCBO::getField(ifds::FundCode,dstrFundCode,BF::HOST);
	   BFCBO::getField(ifds::ClassCode,dstrClassCode,BF::HOST);
	   getWorkSession().GetFundNumber( dstrFundCode,dstrClassCode, strValue );   
	   setFieldNoValidate( ifds::FundNumber, strValue, BF::HOST, false,true, false, false  ); 
	   bool bIsSameDate = isTheSameBusinessDate(BF::HOST); 
	   BFCBO::getField(ifds::FundFromCode,dstrFromFundCode,BF::HOST);
	   BFCBO::getField(ifds::ClassFromCode,dstrFromClassCode,BF::HOST);
	   getWorkSession().GetFundNumber( dstrFromFundCode,dstrFromClassCode, strValue );   
	   setFieldNoValidate( ifds::FromFundNumber, strValue, BF::HOST, false,true, false, false  ); 

	   setFieldReadOnly(ifds::FeeCode, BF::HOST,true); 
     overrideDealerServiceFeeDescription(BF::HOST);

	   GroupList*  pGroupList= NULL;
	   DString dstSubstList = NULL_STRING;

	   if( getMgmtCo().getGroupList( pGroupList )  <= WARNING )
	   {
		  pGroupList->getGroupSubstList( dstSubstList, true);
		  dstSubstList.upperCase();
		  setFieldAllSubstituteValues( ifds::ShGroup, BF::HOST, dstSubstList );
	   }

	   setupFeeCodeRelatedFields(BF::HOST,bIsSameDate);
      doFeeModelCodeRelatedChanges(BF::HOST, false);
	   _salesRepByBranch = NULL_STRING;
	   _familyName = NULL_STRING;
	   _slsrepName = NULL_STRING;
	   _branchCode = NULL_STRING;
	   _dstrFeeType = NULL_STRING;
	   _dstrMinRate = NULL_STRING;
	   _dstrMaxRate = NULL_STRING;
   }
   if(!canUpdateObject(BF::HOST))
   {
      setFieldsReadOnly(BF::HOST, true);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************

SEVERITY FeeParamSys::getFeeScaleList( FeeScaleBaseList *&pFeeScaleList, const BFDataGroupId& idDataGroup,bool bInqure, bool bDefault, bool bRemObj, bool bDelete  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeScaleList" ) );
	DString dstrKey; 
	if( bDefault )
	{
		dstrKey =  I_( "defFeeScaleSysList" );
	}
	else
	{
		dstrKey =  I_( "FeeScaleSysList" );	
	}

   if( bRemObj && pFeeScaleList )
   {
      setObject( NULL, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup ); 
   }
   if ( bDelete )
   {
		pFeeScaleList = NULL;
		return(GETCURRENTHIGHESTSEVERITY());
   }

   FeeScaleSysList* pFeeScaleSysList = dynamic_cast<FeeScaleSysList*>( BFCBO::getObject( dstrKey, idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFeeScaleSysList )
   {
      if( isNew() )
      {
         pFeeScaleSysList = new FeeScaleSysList( *this );
         pFeeScaleSysList->setFeeParamBase(this);
         pFeeScaleSysList->initNew(idDataGroup);
      }
      else if( bInqure ) //make the view call
      {
         pFeeScaleSysList = new FeeScaleSysList( *this );
         DString dstrFeeID;
         getField( ifds::FeeID, dstrFeeID, idDataGroup );
         pFeeScaleSysList->setFeeParamBase(this);
         pFeeScaleSysList->init( dstrFeeID, bDefault );         
         idWorkingDataGroup = BF::HOST;
      }
      if( pFeeScaleSysList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pFeeScaleSysList, dstrKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
         }
         else
         {
            delete pFeeScaleSysList;
            pFeeScaleSysList = NULL;
         }
      }
   }
	if(pFeeScaleSysList) pFeeScaleList = pFeeScaleSysList;

	return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY FeeParamSys::getFeeThresholdList(FeeThrshldSysList *&pFeeThrshldSysList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeScaleList" ) );
	DString dstrKey =  I_( "FeeThresholdSysList" );

   pFeeThrshldSysList = dynamic_cast<FeeThrshldSysList*>( BFCBO::getObject( dstrKey, idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFeeThrshldSysList )
   {
      pFeeThrshldSysList = new FeeThrshldSysList( *this );
      if(!isNew())
      {
         DString dstrFeeID;
         getField(ifds::FeeID, dstrFeeID, idDataGroup, false);
         pFeeThrshldSysList->init(dstrFeeID);
      }
      setObject(pFeeThrshldSysList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup);

      if(!pFeeThrshldSysList->hasNonDummyEntries(BF::HOST))
      {
         BFObjectKey objKey;
         pFeeThrshldSysList->getNewListItem(objKey );
      }
   }

	return(GETCURRENTHIGHESTSEVERITY());
}
//***********************************************************************************
SEVERITY FeeParamSys::doValidateField( const BFFieldId &idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

	FeeParamBase::doValidateField( idField,strValue, idDataGroup );
	if ( idField == ifds::FieldCrossEdit1 )
		validateMinMax( idDataGroup );
	else if ( idField == ifds::FeeRecordOverlapCheck )
	{
		validateFeeOverlap(idDataGroup);
	}
	else if (idField == ifds::BrokerCode)
		validateBrokerCode(idDataGroup);
	else if (idField == ifds::BranchCode)
		validateBranchCode(idDataGroup);
	else if (idField == ifds::SlsrepCode)
		validateSalesRepCode(idDataGroup);
	else if (idField == ifds::FamilyCode)
		validateFamilyCode(idDataGroup);
	else if ( idField == ifds::FieldCrossEdit2 )
		validateFeeTypeForBasedOn(idDataGroup);
	
  else if(idField == ifds::ScaleMinRateChk || idField == ifds::ScaleMaxRateChk)
  {//IN2981408 - System Level Performance Fee
      validateScaleRate( idDataGroup );
  }
    
	else if (idField == ifds::BasedOn)
	{
		validateBasedOn (idDataGroup);
	}
	else if (idField == ifds::ThresholdAmt)
	{
        double dThresholdAmt  = DSTCommonFunctions::convertToDouble(strValue);
		
		if (dThresholdAmt == 0)
		{
		   setFieldNoValidate (ifds::ThresholdAmt, I_(""), idDataGroup, false);
		}
	}
	else if (idField == ifds::FeeCode)
	{
		validateFeeCode (strValue, idDataGroup);
	}
	else if (idField == ifds::FeeModelFundGroup)
	{
		validateFeeModelFundGroup(idDataGroup);
	}
	else if (idField == ifds::FeeModelFundGroupFund)
	{
		validateFeeModelFundGroupOrFund(idDataGroup);
	}
	else if(idField == ifds::FundClassFeeCode) // DIF fund and fee code:29 validation
	{
		DString fundCode, feeCode;
		getField(ifds::FundCode, fundCode, idDataGroup);
		getField(ifds::FeeCode, feeCode, idDataGroup);

		if(feeCode == I_("29") && !isDIFFund(fundCode))
		{
			getErrMsg(IFASTERR::BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND,
					  CND::ERR_BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND,
					  CND::WARN_BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND,
					  idDataGroup);
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}


//***********************************************************************************
SEVERITY FeeParamSys::validateFeeModelFundGroup(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeModelFundGroup" ) );
	DString dstrFeeModelCode;
	DString dstrFundGroup;

   getField (ifds::FeeModelCode, dstrFeeModelCode, idDataGroup);
   getField (ifds::CommGroup,    dstrFundGroup,    idDataGroup);

   if(dstrFeeModelCode.stripAll() != NULL_STRING && dstrFundGroup.stripAll() == NULL_STRING)
   {
		getErrMsg( IFASTERR::FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP, 
            CND::ERR_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP, 
            CND::WARN_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP,
            idDataGroup ); 
   }

	return GETCURRENTHIGHESTSEVERITY();
}
	
//******************************************************************************************
SEVERITY FeeParamSys::validateFeeModelFundGroupOrFund(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeModelFundGroupOrFund" ) );
	DString dstrFeeModelCode;
	DString dstrFundGroup;
	DString dstrFundCode;
	DString dstrClassCode;


   getField (ifds::FeeModelCode, dstrFeeModelCode, idDataGroup);
   getField (ifds::CommGroup,    dstrFundGroup,    idDataGroup);
   getField (ifds::FundCode,     dstrFundCode,     idDataGroup);
   getField (ifds::ClassCode,    dstrClassCode,    idDataGroup);


   if(dstrFeeModelCode.stripAll() != NULL_STRING && dstrFundGroup.stripAll() == NULL_STRING &&
      (dstrFundCode.stripAll() == NULL_STRING || dstrClassCode.stripAll() == NULL_STRING))
   {
		getErrMsg( IFASTERR::FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND, 
            CND::ERR_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND, 
            CND::WARN_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND,
            idDataGroup ); 
   }

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
void FeeParamSys::setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly) 
{
   FeeParamBase::setFieldsReadOnly(idDataGroup,bReadOnly);

   setFieldReadOnly(ifds::FromFundNumber,idDataGroup,bReadOnly); 
   setFieldReadOnly(ifds::FundFromCode,idDataGroup,bReadOnly ); 
   setFieldReadOnly(ifds::ClassFromCode,idDataGroup,bReadOnly);   
   setFieldReadOnly(ifds::BrokerCode,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::HowPaid,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::BasedOn,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::MinFee,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::MaxFee,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::OnPW,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::OnFW,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::AllowOverrideType,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::ShGroup,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::BranchCode,idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::SlsrepCode,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::FamilyCode,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::Currency,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::AppliedMethod,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::FundList,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::ThresholdAmt, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::ThresholdCurrency, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::FeeModelCode, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::EffectiveDate, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::DistributionChannel, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::FundLink, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::CommGroup, idDataGroup, bReadOnly);
   setFieldReadOnly(ifds::TaxInclusive, idDataGroup, bReadOnly);

}
//*****************************************************************************************
SEVERITY FeeParamSys::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	FeeParamBase::doApplyRelatedChanges( idField,idDataGroup );

	if (idField == ifds::FundCode || idField == ifds::ClassCode)
	{
		setCurrencyFromFundClassFields(idDataGroup);
		doFundClassRelatedChanges(idDataGroup);
	}
//	else if (idField == ifds::BasedOn)
//		setScaleFromBasedOnField(idDataGroup);
	else if (idField == ifds::BrokerCode)
		doBrokerCodeRelatedChanges(idDataGroup);
	else if (idField == ifds::BranchCode)
		doBranchCodeRelatedChanges(idDataGroup);
	else if (idField == ifds::SlsrepCode)
		doSlsRepRelatedChanges(idDataGroup);
	else if (idField == ifds::FamilyCode)
		doFamilyCodeRelatedChanges(idDataGroup);
	else if (idField == ifds::FeeCode)
		doFeeCodeRelatedChanges(idDataGroup);
	else if (idField == ifds::CommGroup	)
		doCommGroupRelatedChanges( idDataGroup );
	else if (idField == ifds::ThresholdAmt)
	{
		if (_dstrTresholdAmtApply == I_("Y"))
		{
			DString dstrThresholdAmt;

			getField (ifds::ThresholdAmt, dstrThresholdAmt, idDataGroup);

			double dThresholdAmt  = DSTCommonFunctions::convertToDouble(dstrThresholdAmt);

			bool bRequired = dThresholdAmt == 0;

			setFieldRequired(ifds::ThresholdAmt, idDataGroup, bRequired);
			setFieldValid (ifds::ThresholdAmt, idDataGroup, !bRequired); 
		}
	}

	if ( idField == ifds::FeeCode  || 
        idField == ifds::FundCode || 
        idField == ifds::ClassCode ||
		  idField == ifds::ShGroup || 
        idField == ifds::FundFromCode || 
        idField == ifds::ClassFromCode ||
		  idField == ifds::CommGroup || 
        idField == ifds::BrokerCode || 
        idField == ifds::BranchCode ||
		  idField == ifds::SlsrepCode)
	{
		setCrossEditInvalid( ifds::EffectiveDate,idDataGroup );
	}

   if(idField == ifds::FundCode || 
      idField == ifds::ClassCode)
   {
      DString dstrFundCode;
      DString dstrClassCode;
      DString dstrFundNumber;

      getField(ifds::FundCode,  dstrFundCode,  idDataGroup);
      getField(ifds::ClassCode, dstrClassCode, idDataGroup);
      getWorkSession ().GetFundNumber (dstrFundCode, dstrClassCode, dstrFundNumber);
      setFieldNoValidate( ifds::FundNumber, dstrFundNumber, idDataGroup, false, true, true, false );

      //if(dstrFundCode.stripAll() != NULL_STRING || dstrClassCode.stripAll() != NULL_STRING)
      //{
      //   setFieldRequired(ifds::FeeModelCode, idDataGroup, true);  
      //   setFieldValid(ifds::FeeModelCode, idDataGroup, false);  
      //}
      //else
      //{
      //   setFieldRequired(ifds::FeeModelCode, idDataGroup, false);  
      //}
   }
   else if(idField == ifds::FundNumber)
   {

      DString dstrFundNumber;
      DString dstrFundCode;
      DString dstrClassCode;

      getField(ifds::FundNumber, dstrFundNumber, idDataGroup, false);
      
      if( dstrFundNumber.strip() != NULL_STRING )
         getWorkSession().GetFundClassCode( dstrFundNumber, dstrFundCode, dstrClassCode);

      DString oldFundCode,oldClassCode;
      getField(ifds::FundCode, oldFundCode, idDataGroup,false);
      getField(ifds::ClassCode, oldClassCode, idDataGroup,false);

      if( oldFundCode.upperCase() != dstrFundCode.upperCase() )
      {
         setFieldNoValidate( ifds::FundCode, dstrFundCode, idDataGroup, false, true, true, false);
		 setFieldValid(ifds::FundClassFeeCode, idDataGroup, false);
      }
      if( oldClassCode.upperCase() != dstrClassCode.upperCase() )
      { 
         setFieldNoValidate( ifds::ClassCode, dstrClassCode, idDataGroup, false, true, true, false);
      }

      getField(ifds::FundCode,  dstrFundCode,  idDataGroup);
      getField(ifds::ClassCode, dstrClassCode, idDataGroup);
      //if(dstrFundCode.stripAll() != NULL_STRING || dstrClassCode.stripAll() != NULL_STRING)
      //{
      //   setFieldRequired(ifds::FeeModelCode, idDataGroup, true);  
      //   setFieldValid(ifds::FeeModelCode, idDataGroup, false);  
      //}
      //else
      //{
      //   setFieldRequired(ifds::FeeModelCode, idDataGroup, false);  
      //}

   }

	if( idField == ifds::EffectiveDate )
	{
		DString dstrFeeType;
		getField( ifds::ParamFeeType,dstrFeeType,idDataGroup,false );
		dstrFeeType.strip();
		if( dstrFeeType == TIER || dstrFeeType == SCALE )
		{
			FeeScaleBaseList* pFeeScaleList = NULL;
			getFeeScaleList( pFeeScaleList, idDataGroup,false, false, false, false  );
			if( pFeeScaleList )
			{
				DString dstrEffectiveDate;
				getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
				BFObjIter iter1( *pFeeScaleList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
				while ( !iter1.end() )
				{
					iter1.getObject()->setField(ifds::ScaleEffectiveDate,dstrEffectiveDate,idDataGroup,false );
					++iter1;
				}
			}
		}
	}
	if( idField == ifds::FeeModelCode )
	{
      doFeeModelCodeRelatedChanges(idDataGroup);
   }
	return(GETCURRENTHIGHESTSEVERITY());

}

//**********************************************************
void FeeParamSys::doFeeModelCodeRelatedChanges(const BFDataGroupId& idDataGroup, bool updateFeeCode)
{
   DString dstrFeeModelCode;
   getField(ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false);
   setFieldReadOnly(ifds::CommGroup, idDataGroup, false);
   if(updateFeeCode)
      setFieldNoValidate(ifds::CommGroup, I_(""), idDataGroup, false);
//   setFieldRequired(ifds::TaxInclusive, idDataGroup, false);
//   setFieldValid(ifds::TaxInclusive, idDataGroup, false);
   setFieldRequired(ifds::FundLink, idDataGroup, false);

   if(dstrFeeModelCode.stripAll() != NULL_STRING)
   {
      FeeModelList* pFeeModelList = NULL;
      getWorkSession().getFeeModelList(pFeeModelList, idDataGroup, I_(""),I_(""),I_(""),I_(""),I_(""),I_(""),
                  false, false);
      if(pFeeModelList)
      {
         FeeModel* pFeeModel = NULL; 
         pFeeModelList->getFeeModel(dstrFeeModelCode, pFeeModel, idDataGroup);
         FeeModelList lFeeModelList(*this);
         if(!pFeeModel)
         {
            lFeeModelList.init(idDataGroup, I_("N"), NULL_STRING, I_(""),I_(""),dstrFeeModelCode, I_(""),I_("Y"),I_("12319999"), true);
            lFeeModelList.getFeeModel(dstrFeeModelCode, pFeeModel, idDataGroup);
         }
         if(pFeeModel)
         {
            DString dstrFeeModelType;
            pFeeModel->getField(ifds::FeeModelType, dstrFeeModelType, idDataGroup);
            if(updateFeeCode)
            {
               if(dstrFeeModelType == I_("MF"))
               {
                  setFieldNoValidate(ifds::FeeCode, I_("18"), idDataGroup, false);
               }
               else if(dstrFeeModelType == I_("MFR"))
               {
                  setFieldNoValidate(ifds::FeeCode, I_("95"), idDataGroup, false);
               }
            }
            DString dstrFundGroup;
            pFeeModel->getField(ifds::FeeModelFundGroup, dstrFundGroup, idDataGroup);
            if(dstrFundGroup != NULL_STRING)
            {
               if(updateFeeCode)
                  setFieldNoValidate(ifds::CommGroup, dstrFundGroup, idDataGroup, false);
            }
            
            setFieldReadOnly(ifds::CommGroup, idDataGroup, true);

            DString dstrCurrency;
            pFeeModel->getField(ifds::CalcCurrency, dstrCurrency, idDataGroup);
            dstrCurrency.stripAll();
            if(updateFeeCode)
               setFieldNoValidate(ifds::Currency, dstrCurrency, idDataGroup, false);
            if(dstrCurrency != NULL_STRING)
            {
               setFieldReadOnly(ifds::Currency, idDataGroup, true);
            }

            DString dstrModelAggregationMethod;
            pFeeModel->getField(ifds::ModelAggregationMethod, dstrModelAggregationMethod, idDataGroup);
            setFieldReadOnly(ifds::FundLink, idDataGroup, dstrModelAggregationMethod.stripAll() != I_("FLK"));
            setFieldRequired(ifds::FundLink, idDataGroup, dstrModelAggregationMethod == I_("FLK"));
            if(dstrModelAggregationMethod == I_("FLK"))
            {
               setFieldValid(ifds::FundLink, idDataGroup, false);
            }
            //DString dstrCalcRateType;
            //pFeeModel->getField(ifds::CalcRateType, dstrCalcRateType, idDataGroup);
            //if(dstrCalcRateType == I_("NR"))
            //{
            //   setFieldReadOnly(ifds::TaxInclusive, idDataGroup, false);
            //   setFieldRequired(ifds::TaxInclusive, idDataGroup, true);
            //   DString dstrCurrTaxInclusive;
            //   getField(ifds::TaxInclusive, dstrCurrTaxInclusive, idDataGroup);
            //   if(dstrCurrTaxInclusive.stripAll() == NULL_STRING)
            //   {
            //      if(dstrFeeModelType == I_("MF"))
            //      {
            //         setFieldNoValidate(ifds::TaxInclusive, I_("2"), idDataGroup, true, true, true);
            //      }
            //      else if(dstrFeeModelType == I_("MFR"))
            //      {
            //         setFieldNoValidate(ifds::TaxInclusive, I_("1"), idDataGroup, true, true, true);
            //      }
            //      else
            //      {
            //         setFieldNoValidate(ifds::TaxInclusive, I_("0"), idDataGroup, true, true, true );
            //      }
            //   }
            //}
            //else
            //{
            //   setFieldReadOnly(ifds::TaxInclusive, idDataGroup, true);
         	  // setFieldNoValidate(ifds::TaxInclusive, I_(""), idDataGroup, true, true, true );
            //}

            DString dstrEligibleFundBy;
            pFeeModel->getField(ifds::EligibleFundBy, dstrEligibleFundBy, idDataGroup);

            if(dstrEligibleFundBy.stripAll() == I_("FGP"))
            {
			      setFieldReadOnly(ifds::FundCode, idDataGroup, true);
			      setFieldReadOnly(ifds::ClassCode, idDataGroup, true);
			      setFieldReadOnly(ifds::FundNumber, idDataGroup, true);
            }
            if(dstrFeeModelCode == NULL_STRING)
               setFieldReadOnly(ifds::CommGroup, idDataGroup, dstrEligibleFundBy.stripAll() != I_("FGP"));

         }
      }
   }
}
//**********************************************************
// set fund level currency 
void FeeParamSys::setCurrencyFromFundClassFields (const BFDataGroupId& idDataGroup )
{
   DString dstrFund, dstrClass,fundCurrency;
   getField( ifds::FundCode, dstrFund, idDataGroup );
   getField( ifds::ClassCode, dstrClass, idDataGroup );
   dstrFund.strip().upperCase();
   dstrClass.strip().upperCase();

   if( !dstrFund.empty() && !dstrClass.empty() )
   {
      DString dstrFeeModelCode;
      getField(ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false);
      if(dstrFeeModelCode == NULL_STRING)
      {
         CurrencyClass::getFundCurrency( getWorkSession(), dstrFund, dstrClass, fundCurrency );

	      fundCurrency.strip().upperCase();
	      setFieldNoValidate( ifds::Currency, fundCurrency, idDataGroup, true, true, true );
      }
   }

}

//******************************************************************************

void FeeParamSys::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString dstrCurDate, 
      dstrStopDate, 
      dstrCurrency, 
      dstrFeeCodeList;
   
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurDate, idDataGroup ,false );
   setFieldNoValidate (ifds::EffectiveDate, dstrCurDate, idDataGroup, false,true,false,false);
   getWorkSession().getDateInHostFormat(dstrStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

   setFieldNoValidate( ifds::StopDate,dstrStopDate, idDataGroup, false,true,false,false );
   setFieldNoValidate(ifds::OnPW, NO, idDataGroup, false,true,false,false);
   setFieldNoValidate(ifds::OnFW, NO, idDataGroup, false,true,false,false);
   getWorkSession().getMgmtCoOptions()->getField( ifds::SysCurrency, dstrCurrency, idDataGroup ,false );
   setFieldNoValidate(ifds::Currency, dstrCurrency, idDataGroup, false,true,false,false);

   GroupList*  pGroupList= NULL;
   DString dstSubstList = NULL_STRING;

   if( getMgmtCo().getGroupList( pGroupList )  <= WARNING )
   {
      pGroupList->getGroupSubstList( dstSubstList, true);
      dstSubstList.upperCase();
      setFieldAllSubstituteValues( ifds::ShGroup, idDataGroup, dstSubstList );
   }
   setFieldNoValidate( ifds::MinFee,I_("0.0"), idDataGroup, false,true,false,false );
   setFieldNoValidate( ifds::MaxFee,I_("0.0"), idDataGroup, false,true,false,false );

   FeeParamSysList* pFeeParamSysList = (FeeParamSysList*)getParent();
   if(pFeeParamSysList && pFeeParamSysList->getFromFeeModelCode() != NULL_STRING)
   {
      DString dstrFeeModelCode = pFeeParamSysList->getFromFeeModelCode();
      setFieldNoValidate(ifds::FeeModelCode, dstrFeeModelCode, idDataGroup);
      if(dstrFeeModelCode.stripAll() != NULL_STRING)
      {
         setFieldReadOnly(ifds::FeeModelCode, idDataGroup, true);
      }
   }

}

//******************************************************************************
// set ParamFeeType to scale if BasedOn=1
void FeeParamSys::setScaleFromBasedOnField (const BFDataGroupId& idDataGroup )
{
   DString dstrBasedOn;
   getField( ifds::BasedOn, dstrBasedOn, idDataGroup );
   dstrBasedOn.strip();
   if (dstrBasedOn == BASEDON_SCALE)
   {
	   setFieldNoValidate(ifds::ParamFeeType, SCALE, idDataGroup, false, true);
	   setFieldReadOnly(ifds::ParamFeeType, idDataGroup,true);
   }
   else
   {
	   setFieldReadOnly(ifds::ParamFeeType, idDataGroup,false);
   }
}
 
//***********************************************************************************
//filter fee code substitution list
void FeeParamSys::setFeeCodeSubstituteList(const BFDataGroupId& idDataGroup)
{
   DString dstrFeeCodeList = NULL_STRING;
   DString dstrCode,dstrDes;
   DString dstrAllowedFeeCode[] = {I_("18"),I_("118") };


   BFProperties * pBFProperties = getFieldProperties(ifds::FeeCode, idDataGroup);

	for (int i=0; i<2; i++)
	{
		dstrCode = dstrDes = dstrAllowedFeeCode[i];
	   
		pBFProperties->formatValue(ifds::FeeCode, dstrDes, true );   // -> should return description
		dstrFeeCodeList += dstrCode + I_("=") + dstrDes + I_(";");  // 18=Management Fee;
  
	}
	setFieldAllSubstituteValues(ifds::FeeCode, idDataGroup, dstrFeeCodeList);

}
//***********************************************************************************
SEVERITY FeeParamSys::validateFeeCode (const DString &dstrFeeCode, const BFDataGroupId& idDataGroup)
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
//***********************************************************************************
SEVERITY FeeParamSys::validateBasedOn (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBasedOn" ) );
	
	DString dstrBasedOn,
	   dstrFeeCode,
      basedOnList;

	getField (ifds::BasedOn, dstrBasedOn, idDataGroup);
	getField (ifds::FeeCode, dstrFeeCode, idDataGroup);
	dstrBasedOn.strip();

	FeeParamConfigList *pFeeParamConfigList (NULL);
	FeeParamConfig *pFeeParamConfig (NULL);

	if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
	{
		DString dstrFeeCode, 
         dstrLevel;
		
      getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);
		if (pFeeParamConfigList)
		{
			BFObjIter iter (*pFeeParamConfigList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
			DString dstrFeeCodeComp;
			for (;!iter.end();++iter)
			{

				(iter.getObject() )->getField(ifds::FeeCode, dstrFeeCodeComp, idDataGroup,false);

				if (dstrFeeCodeComp != dstrFeeCode)
				{
					continue;
				}
				else 
				{
					if (dstrLevel.upperCase() == SYSTEM_LEVEL)
					{
						pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
						break;
					}
					else
					{
						pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
					}
				}
			}
		}
	}
   
   if (pFeeParamConfig)
   {
	   pFeeParamConfig->getField (ifds::BaseOnList, basedOnList, idDataGroup, false);
   }

   if (!basedOnList.empty() &&  basedOnList == I_("BW") &&
        dstrBasedOn == GARANTED_WITHDRAWAL_BENEFIT && 
        dstrFeeCode != FEE_GUARANTEE_FEE)
	{
		ADDCONDITIONFROMFILE (CND::ERR_SYS_FEE_INVALID_GWB_BASEDON);
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY FeeParamSys::validateFeeOverlap(const BFDataGroupId& idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeOverlap" ) );

   SEVERITY sev = NO_CONDITION;

	DString dstrFeeCode, dstrFundCode, dstrClassCode, dstrCommGroupCode, dstrEffectiveDate,dstrStopDate;
	DString dstrBrokerCode, dstrFundFromCode,dstrClassFromCode,dstrShGroup;
	DString dstrFeeId, dstrBranchCode, dstrSalesRepCode,dstrDistributionChannel;
   DString dstrFeeModelCode;

	getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
	getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
	getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
	getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
	getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false);

	getField(ifds::FundFromCode,dstrFundFromCode,idDataGroup,false);
	getField(ifds::ClassFromCode,dstrClassFromCode,idDataGroup,false);
	getField(ifds::StopDate,dstrStopDate,idDataGroup,false);
	getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false);
	getField(ifds::ShGroup,dstrShGroup,idDataGroup,false);
//	getField(ifds::FeeID,dstrFeeId,idDataGroup,false);
	getField(ifds::FeeParamRid,dstrFeeId,idDataGroup,false);
	getField(ifds::BranchCode,dstrBranchCode,idDataGroup,false);
	getField(ifds::SlsrepCode,dstrSalesRepCode,idDataGroup,false);
   getField(ifds::DistributionChannel,dstrDistributionChannel,idDataGroup,false);
   getField(ifds::FeeModelCode,dstrFeeModelCode,idDataGroup,false);

	dstrFeeCode.strip().upperCase();
	dstrFundCode.strip().upperCase();
	dstrClassCode.strip().upperCase();
	dstrEffectiveDate.strip(); 
	dstrStopDate.strip();
	dstrBrokerCode.strip();
	dstrCommGroupCode.strip().upperCase();
	dstrFundFromCode.strip().upperCase();
	dstrClassFromCode.strip().upperCase();
	dstrShGroup.strip();
	dstrFeeId.strip().stripLeading('0');
	dstrBranchCode.strip();
	dstrSalesRepCode.strip();
   dstrDistributionChannel.strip();
   dstrFeeModelCode.strip();

	FundFeeList *pFundFeeList = new FundFeeList(*this);
	if( pFundFeeList->init(	 dstrFeeCode
							,dstrFundCode
							,dstrClassCode
							,dstrCommGroupCode
							,dstrEffectiveDate
							,NULL_STRING
							,VALIDATE_TYPE
							,dstrFeeId
							,NULL_STRING
							,dstrFundFromCode
							,dstrClassFromCode
							,dstrStopDate
							,dstrBrokerCode
							,dstrShGroup
							,dstrBranchCode
							,dstrSalesRepCode
                     ,NULL_STRING
                     ,dstrFeeModelCode
                     ,dstrDistributionChannel
						) <= WARNING )
	{
		DString dstrDupCheck;
		pFundFeeList->getField(ifds::DuplicateExist,dstrDupCheck,idDataGroup,false);

		if (dstrDupCheck.strip().upperCase() == YES)
		{
			DString dstrTemp;                 
			addIDITagValue( dstrTemp, IDI_CODE, dstrFeeCode +I_(" ") + dstrFundCode + I_(" ") + dstrClassCode);         
			ADDCONDITIONFROMFILEIDI( CND::ERR_FEE_CODE_OVERLAPED, dstrTemp);
			sev = GETCURRENTHIGHESTSEVERITY();
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

//***********************************************************************************
SEVERITY FeeParamSys::setupFeeCodeRelatedFields(const BFDataGroupId& idDataGroup, bool bIsSameDate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setupFeeCodeRelatedFields" ) );

	FeeParamConfigList*	pFeeParamConfigList = NULL;
	FeeParamConfig *pFeeParamConfig = NULL;
	DString dstrFeeCode;
	getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);

	if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
	{
		DString dstrLevel;
		if (pFeeParamConfigList)
		{ 
			BFObjIter iter( *pFeeParamConfigList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			DString dstrFeeCodeComp;
			for (;!iter.end();++iter)
			{

				(iter.getObject() )->getField(ifds::FeeCode, dstrFeeCodeComp, idDataGroup,false);
				(iter.getObject() )->getField(ifds::FeeLevel, dstrLevel, idDataGroup,false );
				(iter.getObject() )->getField(ifds::ThresholdAmtApply, _dstrTresholdAmtApply, idDataGroup,false );

				if (dstrFeeCodeComp != dstrFeeCode )
				{
					continue;
				}
				else 
				{
					if ( dstrLevel.upperCase() == SYSTEM_LEVEL )
					{
						pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
						break;
					}
					else
					{
						pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
					}
				}
			}
		}
	}
	if ( pFeeParamConfig )
	{
										
		DString dstrSubList = NULL_STRING;
		pFeeParamConfig->getFeeTypeList(dstrSubList);
		setFieldAllSubstituteValues(ifds::ParamFeeType, idDataGroup, dstrSubList);

		dstrSubList = NULL_STRING;
		pFeeParamConfig->getAppliedMethodList(dstrSubList);
		setFieldAllSubstituteValues(ifds::AppliedMethod, idDataGroup, dstrSubList);

		//for those fields with substitute list, get the substitute list from FeeParamConfig CBO
		//and set them to field properties.
		DString dstrGroupCode = NULL_STRING;
		dstrSubList = NULL_STRING;
		pFeeParamConfig->getBaseOnList(dstrSubList);
		setFieldAllSubstituteValues(ifds::BasedOn, idDataGroup, dstrSubList);
		setFieldRequired( ifds::BasedOn, idDataGroup, !dstrSubList.empty() );
		setValidFlag( ifds::BasedOn, idDataGroup, false );

		dstrSubList = NULL_STRING;
		pFeeParamConfig->getHowPaidList(dstrSubList);
		setFieldAllSubstituteValues(ifds::HowPaid, idDataGroup, dstrSubList);
		setFieldRequired( ifds::HowPaid, idDataGroup, !dstrSubList.empty() );
		setValidFlag( ifds::HowPaid, idDataGroup, dstrSubList.empty() );

		dstrSubList = NULL_STRING;
		pFeeParamConfig->getFundNamesList(dstrSubList);
		setFieldAllSubstituteValues(ifds::FundList, idDataGroup, dstrSubList);
		
		dstrSubList = NULL_STRING;
		pFeeParamConfig->getOverrideList(dstrSubList);
		setFieldAllSubstituteValues(ifds::AllowOverrideType, idDataGroup, dstrSubList);


		//For CommGroup, call getFundGroupType from FeeParamSetUp, and the value will be used as
		//input parameter for view 229 (FundCommGroupList)
		DString dstrGroupType = NULL_STRING;
		pFeeParamConfig->getFundGroupType(dstrGroupType);

      bool isMF_MFR = dstrFeeCode.stripAll() == I_("18") || dstrFeeCode == I_("95");
		dstrSubList = I_("NA=;");
		if (dstrGroupType != NULL_STRING)
		{
			FundCommGroupList* pFundCommGroupListP = NULL;

			if(getMgmtCo().getFundCommGroupList(dstrGroupType.strip().upperCase(), pFundCommGroupListP ) <= WARNING )
			{
				pFundCommGroupListP->getCommGroupSubstitute(dstrSubList);//, !isMF_MFR);
			}

		}

      if(isNew())
      {
         if(dstrFeeCode == I_("18"))
         {
            setFieldNoValidate(ifds::TaxInclusive, I_("2"), idDataGroup, true, true, true);
         }
         else if(dstrFeeCode == I_("95"))
         {
            setFieldNoValidate(ifds::TaxInclusive, I_("1"), idDataGroup, true, true, true);
         }
         else
         {
            setFieldNoValidate(ifds::TaxInclusive, I_("0"), idDataGroup, true, true, true );
         }
      }

		setFieldAllSubstituteValues( ifds::CommGroup,idDataGroup, dstrSubList );

      DString dstrUpdateRule = I_("0");
      pFeeParamConfig->getField(ifds::UpdateRule, dstrUpdateRule, idDataGroup, false);

      DString dstrFeeModelCode;
      pFeeParamConfig->getField(ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false);

      if (!canUpdateObject(BF::HOST)) //existing record with different business date
		{
			setFieldsReadOnly(idDataGroup, true);
		}
		else
		{
		//newly created records, or have same business date
		//for those fields not applicable in class FeeParamConfig CBO, set them to read only

			setFieldReadOnly(ifds::ShGroup, idDataGroup,!( pFeeParamConfig->isShareholderGroupApplicable() ) );
			setFieldReadOnly(ifds::BrokerCode, idDataGroup, !(pFeeParamConfig->isBrokerApplicable()));
			setFieldReadOnly(ifds::FundCode, idDataGroup, !(pFeeParamConfig->isFundClassApplicable()));
			setFieldReadOnly(ifds::ClassCode, idDataGroup, !(pFeeParamConfig->isFundClassApplicable()));
			setFieldReadOnly(ifds::FundNumber, idDataGroup, !(pFeeParamConfig->isFundClassApplicable()));
			setFieldReadOnly(ifds::FundFromCode, idDataGroup, !(pFeeParamConfig->isFromFundClassApplicable()));
			setFieldReadOnly(ifds::ClassFromCode, idDataGroup, !(pFeeParamConfig->isFromFundClassApplicable()));
			setFieldReadOnly(ifds::FromFundNumber, idDataGroup, !(pFeeParamConfig->isFromFundClassApplicable()));
			setFieldReadOnly(ifds::OnPW, idDataGroup, !(pFeeParamConfig->isOnPWApplicable()));
			setFieldReadOnly(ifds::OnFW, idDataGroup, !(pFeeParamConfig->isOnFWApplicable()));
			setFieldReadOnly(ifds::BranchCode, idDataGroup, !(pFeeParamConfig->isSalesRepApplicable()) && !(pFeeParamConfig->isBranchApplicable()));
			setFieldReadOnly(ifds::FamilyCode, idDataGroup, !(pFeeParamConfig->isFamilyCodeApplicable()));
			setFieldReadOnly(ifds::SlsrepCode, idDataGroup, !(pFeeParamConfig->isSalesRepApplicable()));
			setFieldReadOnly(ifds::MinFee, idDataGroup, false);
			setFieldReadOnly(ifds::MaxFee, idDataGroup, false);
			setFieldReadOnly(ifds::ParamFeeType, idDataGroup, false);
			setFieldReadOnly(ifds::BasedOn, idDataGroup, false);
			setFieldReadOnly(ifds::HowPaid, idDataGroup, false);
			setFieldReadOnly(ifds::FundList, idDataGroup, false);
			setFieldReadOnly(ifds::AllowOverrideType, idDataGroup,false);
			setFieldReadOnly(ifds::CommGroup, idDataGroup,false);
			setFieldReadOnly(ifds::EffectiveDate, idDataGroup, false);
			setFieldReadOnly(ifds::StopDate, idDataGroup, false);
			setFieldReadOnly(ifds::Currency, idDataGroup, false);
			setFieldReadOnly(ifds::AppliedMethod, idDataGroup, !(pFeeParamConfig->isAppliedMethodApplicable()));

			bool bTresholdAmtApply = _dstrTresholdAmtApply == I_("Y");

			setFieldReadOnly(ifds::ThresholdAmt, idDataGroup, !bTresholdAmtApply);
		    setFieldReadOnly(ifds::ThresholdCurrency, idDataGroup, !bTresholdAmtApply);

			setFieldRequired (ifds::ThresholdAmt, idDataGroup, bTresholdAmtApply);
            setFieldValid (ifds::ThresholdCurrency, idDataGroup, !bTresholdAmtApply); 
			setFieldRequired (ifds::ThresholdCurrency, idDataGroup, bTresholdAmtApply);
			setFieldValid (ifds::ThresholdCurrency, idDataGroup, !bTresholdAmtApply); 
		}	
				
	}
	if ( GETCURRENTHIGHESTSEVERITY() > WARNING )
	{
		PROMOTECONDITIONS();
		CLEARCONDITIONSFRAMECURRENT(); 
	}
	
	return NO_CONDITION;
}

//***********************************************************************************
SEVERITY FeeParamSys::validateFamilyCode( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFamilyCode" ) );

   DString dstrFamilyCode, dstrFamilyName;
   getField( ifds::FamilyCode, dstrFamilyCode, idDataGroup );
   if(  dstrFamilyCode.strip() != NULL_STRING )
   {
      ShrFamily family( *this );
      SEVERITY sevRtn=family.getFamilyName( dstrFamilyCode, 
                                            dstrFamilyName, 
                                            idDataGroup );
      if (sevRtn <= WARNING )
      {
         _familyName = dstrFamilyName.strip();
         return(NO_CONDITION);
      }
      else
      {
         _familyName = NULL_STRING;
//       ADDCONDITIONFROMFILE( CND::INVALID_FAMILY_CODE );
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
void FeeParamSys::doBrokerCodeRelatedChanges( const BFDataGroupId& idDataGroup )
{
	DString dstrBrokerCode=NULL_STRING;
	DString dstrBrokerName=NULL_STRING;

	getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup);

	if (dstrBrokerCode != NULL_STRING)
	{
		//get Broker name from broker list
		BrokerList brokerList( *this );
		// 'L' for the request type will do a search for broker by code
		SEVERITY sevRtn = brokerList.init(dstrBrokerCode, NULL_STRING,I_("L"));
		if( sevRtn <= WARNING )
		{
			BFObjIter bfIter( brokerList, idDataGroup );
      
			bfIter.begin();
			if( !bfIter.end() )
			{
				bfIter.getObject()->getField( ifds::BrokerName,dstrBrokerName, idDataGroup );
			}
		}

		  if( slsRepByBranch (idDataGroup) ) // blank out the branchcode trigger the blanking out of salesrep
		  {
			  //clear the name, clears out related fields, branch
			 _branchName = NULL_STRING;

			  //clear BranchCode, and mark the field as invalid and notify the observers
			 _branchCode = NULL_STRING;
			 setFieldNoValidate( ifds::BranchCode, NULL_STRING, idDataGroup, false, false, true );

		  }
		  else // blank out salesrep -> trigger branch code assignment
		  {
			 DString brokerBranch;

			 if( getWorkSession().getOption( ifds::BrokerBranch, brokerBranch, idDataGroup, false ) <= WARNING )
			 {
				if( brokerBranch == YES )
				{
				   _branchCode = dstrBrokerCode;
				   _branchName = dstrBrokerName;
				}
				else
				{
				   _branchCode = I_( "0000" );
				   _branchName = NULL_STRING;
				}
			 }
			 _slsrepName = NULL_STRING;
			 setFieldNoValidate( ifds::BranchCode, NULL_STRING, idDataGroup, false, false, true );
			 setFieldNoValidate( ifds::SlsrepCode, NULL_STRING, idDataGroup, false, false, true );
		  }
	}
	else 
	{
	     _branchName = NULL_STRING;
		 _branchCode = NULL_STRING;
		 _slsrepName = NULL_STRING;
		 setFieldNoValidate( ifds::BranchCode, NULL_STRING, idDataGroup, false, false, true );
		 setFieldNoValidate( ifds::SlsrepCode, NULL_STRING, idDataGroup, false, false, true );

	}
    setFieldNoValidate( ifds::BrokerName, dstrBrokerName, idDataGroup, false, true,true);
}

//***********************************************************************************
void FeeParamSys::doBranchCodeRelatedChanges(const BFDataGroupId& idDataGroup)
{
    DString branchCode;   
	getField( ifds::BranchCode, branchCode, idDataGroup );
  
	if ( branchCode == NULL_STRING || slsRepByBranch ( idDataGroup ) ) // get the branch code and name from view 92 
      {
	     //clear the names
		 _slsrepName = NULL_STRING;
		  //notify the observers
         setFieldNoValidate( ifds::SlsrepCode, NULL_STRING, idDataGroup, false, false, true );
      }
	if (branchCode.empty())
		setFieldNoValidate( ifds::BranchName, NULL_STRING, idDataGroup, false, true, true );
	else
		setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, false, true, true );
}

//***********************************************************************************
void FeeParamSys::doSlsRepRelatedChanges(const BFDataGroupId& idDataGroup)
{

	setFieldNoValidate( ifds::SlsrepName, _slsrepName, idDataGroup, false, true, true );

}

//***********************************************************************************
SEVERITY FeeParamSys::validateBrokerCode( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBrokerCode" ) );

   DString dstrBrokerCode;
	
   getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup );

   if(  dstrBrokerCode.strip() != NULL_STRING )
   {
		Broker broker( *this );
		SEVERITY sevRtn=broker.init(dstrBrokerCode, true);
		if (sevRtn <= WARNING )
		{
			return(NO_CONDITION);
		}
		else
		{
//			ADDCONDITIONFROMFILE( CND::INVALID_BROKER_CODE );
			return(GETCURRENTHIGHESTSEVERITY());
		}
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeParamSys::validateBranchCode( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBranchCode" ) );

   DString brokerCode, branchCode;

   _branchName = NULL_STRING;
   getField( ifds::BranchCode, branchCode, idDataGroup );

   if( branchCode.strip() != NULL_STRING )
   {
         getField( ifds::BrokerCode, brokerCode, idDataGroup );

		if(  brokerCode.strip()== NULL_STRING )
		{
			ADDCONDITIONFROMFILE( CND::ERR_BROKER_EMPTY );
			return(GETCURRENTHIGHESTSEVERITY());
		}

	   else
	   {
		  if( validateBrokerCode(idDataGroup ) <= WARNING )
		  {
			 BranchList branchList( *this );
			 DString branchName = NULL_STRING;
			 getField( ifds::BrokerCode, brokerCode, idDataGroup );
			 //checks for the validity of the branch code. by making a view call
			 if( branchList.init( brokerCode, branchCode ) <= WARNING )
			 {
				BFObjIter bfIter( branchList, idDataGroup );

				bfIter.begin();
				if( !bfIter.end() )
				{
					 bfIter.getObject()->getField( ifds::BranchName, branchName, idDataGroup );
					 _branchName = branchName.strip();
				}
				return(NO_CONDITION);
			 }
			 else
			 {
	//			ADDCONDITIONFROMFILE( CND::INVALID_BRANCH_CODE );
				return(GETCURRENTHIGHESTSEVERITY());
			 }
		  }
	   }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY FeeParamSys::validateSalesRepCode( const BFDataGroupId& idDataGroup )
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSalesRepCode" ) );

  DString brokerCode, branchCode, slsrepCode;
  _slsrepName = NULL_STRING;

  SEVERITY sevRtn;

  getField( ifds::SlsrepCode, slsrepCode, idDataGroup );
  getField( ifds::BrokerCode, brokerCode, idDataGroup );
  getField( ifds::BranchCode, branchCode, idDataGroup );


  if( slsrepCode.strip() != NULL_STRING )
  {

	 if( slsRepByBranch ( idDataGroup ) )
	 {
		  if( branchCode.strip() == NULL_STRING )
		  {
			  ADDCONDITIONFROMFILE( CND::ERR_BRANCH_EMPTY);
			  return(GETCURRENTHIGHESTSEVERITY());
		  }
		  else 
		  {
			  sevRtn = validateBranchCode( idDataGroup );
		  }
	 }
	 else 
	 {
	      if(  brokerCode.strip()== NULL_STRING )
		  {
			  ADDCONDITIONFROMFILE( CND::ERR_BROKER_EMPTY );
			  return(GETCURRENTHIGHESTSEVERITY());
		  }
		  else 
		  {
 			  sevRtn = validateBrokerCode(idDataGroup );
		  }

	 }

	 if( sevRtn <= WARNING )
	 {
		AgentList agentList( *this );


	   if( agentList.init( brokerCode, branchCode, slsrepCode) <= WARNING )
	   {
		   //Rule: If NewBusiness-92 is No and SegClient = Yes issue warning 
		   //  "Salesperson is not permitted new business activity"
			DString newBusiness = NULL_STRING;
			DString segClient = NULL_STRING;
			DString dstrSalesName = NULL_STRING;
			DString dstrBranchCode = NULL_STRING;
			DString dstrBranchName = NULL_STRING;
			BFObjIter bfIter( agentList, idDataGroup );

			bfIter.begin();
			if( !bfIter.end() )
			{
				bfIter.getObject()->getField( ifds::NewBusiness, newBusiness, idDataGroup );
                bfIter.getObject()->getField( ifds::SlsrepName, dstrSalesName, idDataGroup );
	            bfIter.getObject()->getField( ifds::BranchCode, dstrBranchCode, idDataGroup );
                bfIter.getObject()->getField( ifds::BranchName, dstrBranchName, idDataGroup );
			
				_slsrepName = dstrSalesName.strip();
				if ( !slsRepByBranch( idDataGroup ) )//get brancode by slarepcode
				{
					_branchCode = dstrBranchCode.strip();
					_branchName = dstrBranchName.strip();
					setFieldNoValidate( ifds::BranchCode, _branchCode, idDataGroup, true, true, true, false);
					setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, true, true, true, false);

				}

			}

			getWorkSession().getOption( ifds::SegClient, segClient, idDataGroup, false );

			if( NO == newBusiness && YES == segClient )
			{
				ADDCONDITIONFROMFILE( CND::ERR_SALESPERSON_IS_NOT_PERMITTED );
				return(GETCURRENTHIGHESTSEVERITY());
			}
	   }
	   else //No valid BrokerCode / BranchCode
	   {
		  _slsrepName = NULL_STRING;
		  if( !slsRepByBranch ( idDataGroup) )
		  {
			 _branchCode = NULL_STRING;
			 _branchName = NULL_STRING;
		  }

		  return(GETCURRENTHIGHESTSEVERITY());
	   }
	 }
  }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool FeeParamSys::slsRepByBranch ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "slsRepByBranch" ) );

   if( _salesRepByBranch == NULL_STRING )
   {
      getWorkSession().getOption( ifds::RepByBranch, _salesRepByBranch, idDataGroup, false );
		_salesRepByBranch.strip().upperCase();
   }

   return( _salesRepByBranch == YES );
}

//******************************************************************************
void FeeParamSys::doFeeCodeRelatedChanges(const BFDataGroupId& idDataGroup)
{
	FeeParamBase::doFeeCodeRelatedChanges(idDataGroup);
	bool bIsSameDate = isTheSameBusinessDate(idDataGroup);
	setupFeeCodeRelatedFields(idDataGroup,bIsSameDate);
	DString dstrFeeCode;
	getField( ifds::FeeCode, dstrFeeCode, idDataGroup ); 
	setValueFromDefaultRecord(dstrFeeCode, NULL_STRING, NULL_STRING, NULL_STRING, idDataGroup);
    setFieldValid(ifds::GroupFundClass, idDataGroup, false);

}

//******************************************************************************
void FeeParamSys::doFamilyCodeRelatedChanges(const BFDataGroupId& idDataGroup)
{
	setFieldNoValidate( ifds::FamilyName, _familyName, idDataGroup, false,true);

}

//******************************************************************************
// init with default value
void FeeParamSys::setValueFromDefaultRecord(
											const DString strFeeCode, 
											const DString strFundCode, 
											const DString strClassCode, 
											const DString strFundGroup, 
											const BFDataGroupId& idDataGroup
										   )

{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setValueFromDefaultRecord" ) );

	_dstrFeeType = NULL_STRING;
	_dstrMinRate = NULL_STRING;
	_dstrMaxRate = NULL_STRING;

	FeeParamSys *pFeeParamSysDef = NULL;

	getFeeParamSysDef(pFeeParamSysDef, idDataGroup );
	if ( pFeeParamSysDef )
	{
		DString dstrFeeType, dstrMinFee, dstrMaxFee, dstrRate, dstrBasedOn;
		pFeeParamSysDef ->getField(ifds::ParamFeeType, dstrFeeType, BF::HOST);
		pFeeParamSysDef ->getField(ifds::MinFee, dstrMinFee, BF::HOST);
		pFeeParamSysDef ->getField(ifds::MaxFee, dstrMaxFee, BF::HOST);
		pFeeParamSysDef ->getField(ifds::Rate, dstrRate, BF::HOST);
		pFeeParamSysDef ->getField(ifds::BasedOn, dstrBasedOn, BF::HOST);
		
		_dstrFeeType = dstrFeeType;
		_dstrMinRate = dstrMinFee;
		_dstrMaxRate = dstrMaxFee;

		if ( isNew() )
		{
			setFieldNoValidate( ifds::ParamFeeType, dstrFeeType, idDataGroup, false,true);
			setFieldNoValidate( ifds::MinFee, dstrMinFee, idDataGroup, false,true);
			setFieldNoValidate( ifds::MaxFee, dstrMaxFee, idDataGroup, false,true);
			setFieldNoValidate( ifds::Rate, dstrRate, idDataGroup, false,true);
			setFieldNoValidate( ifds::BasedOn, dstrBasedOn, idDataGroup, false,true);
			
			if( dstrFeeType == SCALE  || dstrFeeType == TIER ) 
		   {
				  FeeScaleBaseList *pFeeScaleDefaultList = NULL;
				  
				  pFeeParamSysDef ->getFeeScaleList( pFeeScaleDefaultList,BF::HOST, true, true );

				  if( pFeeScaleDefaultList != NULL )
				  {

					  getFeeScaleList( pFeeScaleList_,idDataGroup, true, false, true);
				      dynamic_cast<FeeScaleSysList *>(pFeeScaleList_)->AddNewFeeScale(pFeeScaleDefaultList,NULL_STRING,idDataGroup);

				  }

			}

		}
	}
	if ( GETCURRENTHIGHESTSEVERITY() > WARNING )
	{
		PROMOTECONDITIONS();
		CLEARCONDITIONSFRAMECURRENT();
	}

}

//******************************************************************************
void FeeParamSys::doCommGroupRelatedChanges(const BFDataGroupId& idDataGroup)
{
	DString dstrFeeCode, dstrFundGroup;
	FeeParamBase::doCommGroupRelatedChanges(idDataGroup);
	if ( pFeeScaleList_ ) //delete the object
	{
		getFeeScaleList( pFeeScaleList_, idDataGroup, true, false, true, true);
	}
    getField( ifds::CommGroup, dstrFundGroup, idDataGroup );
	if (!dstrFundGroup.strip().empty()) 
	{
		getField( ifds::FeeCode, dstrFeeCode, idDataGroup );
		setValueFromDefaultRecord(dstrFeeCode, NULL_STRING, NULL_STRING, dstrFundGroup,idDataGroup);

	}


}

//**********************************************************
void FeeParamSys::doFundClassRelatedChanges (const BFDataGroupId& idDataGroup )
{
	if ( pFeeScaleList_ ) //delete the object
	{
		getFeeScaleList( pFeeScaleList_, idDataGroup, true, false, true, true);
	}
   DString dstrFund, dstrClass,dstrFeeCode;
   getField( ifds::FundCode, dstrFund, idDataGroup );
   getField( ifds::ClassCode, dstrClass, idDataGroup );
   dstrFund.strip().upperCase();
   dstrClass.strip().upperCase();

   if( !dstrFund.empty() && !dstrClass.empty() )
   {
		getField( ifds::FeeCode, dstrFeeCode, idDataGroup );
		setValueFromDefaultRecord(dstrFeeCode, dstrFund, dstrClass, NULL_STRING, idDataGroup);
   }

}

//******************************************************************************
void FeeParamSys::getDefaultBranchCode( DString &dstrBranchCode, const BFDataGroupId& idDataGroup ) 
{
	dstrBranchCode = _branchCode;
}

//******************************************************************************
// set ParamFeeType to scale if BasedOn=1
SEVERITY FeeParamSys::validateFeeTypeForBasedOn (const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateParamFeeType" ) );

   DString dstrBasedOn, dstrFeeCode, dstrFeeType;
   getField( ifds::FeeCode, dstrFeeCode, idDataGroup );
   if ( dstrFeeCode != FEE_CODE_MANAGEMENT_FEE  && dstrFeeCode != FEE_CODE_VISCOUNT_FEE )
	   return NO_CONDITION;
   getField( ifds::BasedOn, dstrBasedOn, idDataGroup );
   dstrBasedOn.strip();
   if ( dstrBasedOn == BASEDON_SCALE )
   {
	   getField( ifds::ParamFeeType, dstrFeeType, idDataGroup );
		if ( dstrFeeType != SCALE )
		{
			ADDCONDITIONFROMFILE( CND::ERR_FEE_TYPE_SCALE_ONLY );
			return(GETCURRENTHIGHESTSEVERITY());
		}
   }
   return NO_CONDITION;
}
 
//*****************************************************************************************
void FeeParamSys::clearUpdateFlags(const BFDataGroupId& idDataGroup)
{
	DString dstrFeeType;
	getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
	dstrFeeType.strip();
	if( dstrFeeType != SCALE && dstrFeeType != TIER && pFeeScaleList_ )
	{
		pFeeScaleList_->clearUpdatedFlags( idDataGroup, true );
	}
}

//******************************************************************************
SEVERITY FeeParamSys::validateScaleRate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRate" ) )
  
   FeeParamBase::validateScaleRate(idDataGroup);

   // for Management Fee Discount, we do not do the validation against Min and Max
   // We do the validation against Min and Max only for Broker level
   DString dstrFeeCode, dstrBrokerCode;
   getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false );
   dstrFeeCode.strip().upperCase();

   if( dstrFeeCode == FEE_CODE_MANAGEMENT_DISCOUNT ) 
   {
	   return(GETCURRENTHIGHESTSEVERITY());
   }

	getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false );
	dstrBrokerCode.strip();

   if ( _dstrFeeType.empty() &&  dstrBrokerCode != NULL_STRING )
   {
	   FeeParamSys *pFeeParamSysDef = NULL;
	   getFeeParamSysDef(pFeeParamSysDef, idDataGroup );
	   if ( pFeeParamSysDef )
	   {
	   		DString dstrFeeType, dstrMinFee, dstrMaxFee, dstrRate, dstrBasedOn;
			pFeeParamSysDef ->getField(ifds::ParamFeeType, dstrFeeType, BF::HOST);
			pFeeParamSysDef ->getField(ifds::MinFee, dstrMinFee, BF::HOST);
			pFeeParamSysDef ->getField(ifds::MaxFee, dstrMaxFee, BF::HOST);
			
			_dstrFeeType = dstrFeeType;
			_dstrMinRate = dstrMinFee;
			_dstrMaxRate = dstrMaxFee;
	   }
   }
	if( dstrBrokerCode == NULL_STRING ) // it is Fund level
	{

			getField(ifds::ParamFeeType, _dstrFeeType, idDataGroup);
			getField(ifds::MinFee, _dstrMinRate, idDataGroup);
			getField(ifds::MaxFee, _dstrMaxRate, idDataGroup);	
	}
   if (  !_dstrFeeType.empty() 
	   && !_dstrMinRate.empty()	
	   && !_dstrMaxRate.empty()
	   )
   {
	   DString dstrParaFeeType;
	   getField(ifds::ParamFeeType,dstrParaFeeType,idDataGroup,false);
	   dstrParaFeeType.strip().upperCase();

	   if( dstrParaFeeType == _dstrFeeType && (dstrParaFeeType != SCALE && dstrParaFeeType != TIER ) )
	   {
		   DString dstrRatePara;
		   getField(ifds::Rate,dstrRatePara,idDataGroup );
		   double dRatePara =  DSTCommonFunctions::convertToDouble( dstrRatePara );
		   double dMaxRate,dMinRate;
		   dMaxRate =  DSTCommonFunctions::convertToDouble( _dstrMaxRate );
		   dMinRate =  DSTCommonFunctions::convertToDouble( _dstrMinRate );
		   
		   if ( dMaxRate == 0 && dMinRate > 0 )
		   {
				if ( dRatePara < dMinRate )
				{
					 DString dstrIDI;
					 DSTCommonFunctions::DisplayFormat( _dstrMinRate, ifds::MinFee );
					 addIDITagValue( dstrIDI, IDI_MIN_RATE, _dstrMinRate );
					 ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_LESS_THAN_MIN, dstrIDI );               
				}
		   }
		   else if( dRatePara > dMaxRate || dRatePara < dMinRate )
		   {
				 DString dstrIDI;
				 DSTCommonFunctions::DisplayFormat( _dstrMinRate, ifds::MinFee );
				 DSTCommonFunctions::DisplayFormat( _dstrMaxRate, ifds::MaxFee );
				 addIDITagValue( dstrIDI, IDI_MIN_RATE, _dstrMinRate );
				 addIDITagValue( dstrIDI, IDI_MAX_RATE, _dstrMaxRate );
				 ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_IS_OUT_OF_RANGE, dstrIDI );               
		   }
	   }
   }
   return(GETCURRENTHIGHESTSEVERITY());


}

//******************************************************************************
SEVERITY FeeParamSys::getFeeParamSysDef( FeeParamSys *&pFeeParamSys, const BFDataGroupId& idDataGroup )
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
      pFeeParamSysDefList->getDefaultFeeParamRecord ( pFeeParamSys, 
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
SEVERITY FeeParamSys::copyData(FeeParamSys *&pFeeParamSys, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "copyData" ) );
   
   BFData data230(ifds::DSTC0230_VWRepeat_Record);  
   getData(data230, idDataGroup);
   data230.setElementValue(ifds::ProcessDate, I_(""));
   data230.setElementValue(ifds::FMLastProcDate, I_(""));
   pFeeParamSys->setData(data230, idDataGroup);
   //FIELD_MAP_ITER _fieldMapIter = _fieldMap.begin( );
   //while(_fieldMapIter != _fieldMap.end())
   //{
   //   DString fieldValue;

   //   getField (( *fieldIter ).first, fieldValue, idDataGroup, false);
   //   pFeeParamSys->setFieldNoValidate (( *fieldIter ).first, fieldValue, idDataGroup, false, true, false, false);
   //}
   //for (int i = 0; i < NUM_FIELDS; i++)
   //{
   //   BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
   //   const BFFieldId &fieldId = fieldInfo.getFieldId();

   //   DString fieldValue;

   //   getField (fieldId, fieldValue, idDataGroup, false);
   //   pFeeParamSys->setFieldNoValidate (fieldId, fieldValue, idDataGroup, false, true, false, false);
   //}

   DString dstrFeeType;
   getField(ifds::ParamFeeType, dstrFeeType, idDataGroup, false);
   if(FEETYPE::TIER_BY_THRESHOLD == dstrFeeType || FEETYPE::SCALE_BY_THRESHOLD)
   {
      FeeThrshldSysList* pFeeThrshldSysList = NULL;
      getFeeThresholdList(pFeeThrshldSysList, idDataGroup);
      if(pFeeThrshldSysList)
      {
         FeeThrshldSysList* pFeeThrshldSysListClone = NULL;
         pFeeThrshldSysList->clone(idDataGroup, pFeeThrshldSysListClone);
         pFeeParamSys->setObject(pFeeThrshldSysListClone, I_( "FeeThresholdSysList" ), OBJ_ACTIVITY_NONE, idDataGroup );
      }
   }
   else if (FEETYPE::SCALE == dstrFeeType || FEETYPE::TIER == dstrFeeType)
   {
      FeeScaleBaseList* pFeeScaleBaseList = NULL;
      FeeScaleSysList*  pFeeScaleSysList = NULL;

      getFeeScaleList(pFeeScaleBaseList, idDataGroup,true);
      if(pFeeScaleBaseList)
      {
         pFeeScaleSysList = dynamic_cast<FeeScaleSysList*>(pFeeScaleBaseList);
         if(pFeeScaleSysList)
         {
            FeeScaleSysList* pFeeScaleSysListClone = NULL;
            pFeeScaleSysList->clone(idDataGroup, pFeeScaleSysListClone);
            pFeeParamSys->setObject(pFeeScaleSysListClone, I_( "FeeScaleSysList" ), OBJ_ACTIVITY_NONE, idDataGroup );
         }
      }
   }
	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool FeeParamSys::isDIFFund ( const DString& fundCode)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isDIFFund" ) );
	bool bIsDIFFund = false;
	FundMasterList *pFundMasterList = NULL;

	if(!fundCode.empty() && 
		getMgmtCo().getFundMasterList (pFundMasterList) && 
		NULL != pFundMasterList)
	{
		if(pFundMasterList->isDIFFund(fundCode))
		{
			bIsDIFFund = true;
		}
	}

	return bIsDIFFund;
}

   //******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamSys.cpp-arc  $
// 
//    Rev 1.63   Jun 28 2012 05:25:10   panatcha
// IN2981408 - System Level Performance Fee
// 
//    Rev 1.62   Dec 12 2011 22:42:58   popescu
// P0186479/FN03 - INA - Commission Work
// 
//    Rev 1.61   Dec 09 2011 22:20:22   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.60   Dec 01 2011 00:17:58   popescu
// INA - Commission Work
// 
//    Rev 1.59   Nov 08 2011 12:02:28   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.58   Oct 31 2011 10:15:14   kitticha
// PETP0186479 FN01 - IA Base Commission.
// 
//    Rev 1.57   Oct 07 2011 07:51:14   kitticha
// PETP0186479 FN01 - IA Base Commission.
// 
//    Rev 1.56   Oct 05 2010 11:49:12   jankovii
// PET168727 FN22 - Trailer Fee Setup
// 
//    Rev 1.55   Aug 28 2009 14:04:36   jankovii
// IN 1816184 - Error on Threshold Amount when setup Dealing Fee
// 
//    Rev 1.54   Aug 20 2009 11:13:44   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields 
// 
//    Rev 1.53   Aug 13 2009 11:14:14   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields 
// 
//    Rev 1.52   Sep 01 2006 11:31:46   jankovii
// PET 2236 FN02 - Grandfathering Units for Trailer Purposes.
// 
//    Rev 1.51   May 25 2006 09:33:52   jankovii
// PET 2102 FN02 - Manulife Flex System Level Fee.
// 
//    Rev 1.50   Nov 01 2005 09:17:36   AGUILAAM
// PET1243_FN00_ABN AMRO Trailer Fee Processing - additional enhancements
// 
//    Rev 1.49   Oct 25 2005 13:34:18   AGUILAAM
// PET1243_FN01_ABN AMRO Funds Trailer Fee Processing; additional enhancements (System Level Fee-Parms screen)
// 
//    Rev 1.48   Jul 11 2005 17:22:50   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.47   Apr 14 2005 08:58:18   yingbaol
// Incident 265632 Change set default fee logic for FundSponsorFee
// 
//    Rev 1.46   Nov 14 2004 14:40:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.45   Nov 04 2004 17:37:36   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.44   Feb 19 2004 10:28:38   YINGBAOL
// PTS10027189:BrokerCode, BranchCode and SalesRep and thire name can contain space string. Program should not strip all space. 
// 
//    Rev 1.43   Oct 15 2003 16:47:36   YINGBAOL
// PTS10019803 EffectiveDate changes
// 
//    Rev 1.42   Sep 18 2003 09:53:58   YINGBAOL
// FeeRate at fund level validates againt Min/Max
// 
//    Rev 1.41   Aug 30 2003 16:05:18   YINGBAOL
// AMS Fee Calculation enhancement
// 
//    Rev 1.40   Aug 01 2003 11:15:06   linmay
// PTS Ticket #10020018
// 
//    Rev 1.39   Jul 29 2003 10:42:04   linmay
// PTS Ticket #10020017
// 
//    Rev 1.38   Jul 21 2003 15:08:26   linmay
// PTS Ticket #10014935
// 
//    Rev 1.37   Jul 04 2003 15:47:08   YINGBAOL
// Sync. Version 1.33.1.3
// 
//    Rev 1.36   Jun 26 2003 11:02:32   linmay
// PTS # 10014935
// 
//    Rev 1.35   Jun 20 2003 16:41:08   linmay
// PTS#10014935 and sync with 1.33.1.3
// 
//    Rev 1.33   Jun 09 2003 10:50:38   linmay
// Sync with 1.28.1.6
// 
//    Rev 1.32   Jun 06 2003 09:00:12   linmay
// Sync up with Ver1.28.1.4
// 
//    Rev 1.31   May 28 2003 14:33:52   linmay
// clear conditions
// 
//    Rev 1.30   May 07 2003 11:50:36   linmay
// PTS Ticket#10016320
// 
//    Rev 1.29   May 02 2003 14:55:14   linmay
// modified validateFeeOverlap() and doApplyRelatedChanges()
// 
//    Rev 1.28   Apr 28 2003 09:54:16   YINGBAOL
// Some how the change lost
// 
//    Rev 1.26   Apr 02 2003 16:42:04   linmay
// sync up
// 
//    Rev 1.25   Mar 25 2003 14:45:14   linmay
// sync up
// 
//    Rev 1.24   Mar 21 2003 21:05:32   PURDYECH
// Sync 1.20.1.0 back to trunk
// 
//    Rev 1.23   Mar 20 2003 17:42:18   YINGBAOL
// fix substitute list for ShGroup etc.
// 
//    Rev 1.22   Mar 19 2003 17:12:36   linmay
// added BrokerName
// 
//    Rev 1.19   Mar 18 2003 11:52:32   linmay
// added validateType for view229
// 
//    Rev 1.18   Mar 10 2003 14:48:10   linmay
// added logic for config layer
// 
//    Rev 1.17   Feb 17 2003 10:19:48   YINGBAOL
// small change
// 
//    Rev 1.16   Feb 03 2003 15:25:36   YINGBAOL
// clear condition if there is no commission group
// 
//    Rev 1.15   Jan 31 2003 09:30:10   linmay
// modified doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
// 
//    Rev 1.14   Jan 29 2003 15:45:04   linmay
// added setFeeCodeSubstituteList();modified initnew()
// 
//    Rev 1.13   Jan 28 2003 15:57:44   linmay
// modified setFieldsReadOnly()
// 
//    Rev 1.12   Jan 27 2003 15:27:04   linmay
// added setScaleFromBasedOn(), modified dovalidateField(), and doApplyRelatedChanges()
// 
//    Rev 1.11   Jan 22 2003 16:58:36   linmay
// modify initnew()
// 
//    Rev 1.9   Jan 22 2003 15:45:02   linmay
// added doInitWithDefaultValues()
// 
//    Rev 1.8   Jan 22 2003 10:17:18   YINGBAOL
// Populate Shareholder Group substitute list
// 
//    Rev 1.7   Jan 21 2003 16:07:06   linmay
// added 		setCurrencyFromFundClassFields()
// 
//    Rev 1.6   Jan 21 2003 11:18:52   YINGBAOL
// FundClassRules change sync and some other fix
// 
//    Rev 1.5   Jan 20 2003 15:09:56   linmay
// modified initnew
// 
//    Rev 1.4   Jan 18 2003 17:25:34   YINGBAOL
// add doValidateField and set CommGroup Substitute set
// 
//    Rev 1.3   Jan 17 2003 14:06:22   YINGBAOL
// implement getFeeScaleList
// 
//    Rev 1.2   Jan 15 2003 11:57:34   linmay
// added Log Comment
// 
*/
