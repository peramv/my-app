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
// ^FILE   : FundSponsorFee.cpp
// ^AUTHOR : 
// ^DATE   : July 26, 2004
//
// ^CLASS    : FundSponsorFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundSponsorFee.hpp"
#include "FundSponsorFeelist.hpp"
#include "FeeScaleSysList.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0230_vw.hpp>
#include <ifastdataimpl\dse_dstc0230_req.hpp>
#include <ifastdataimpl\dse_dstc0229_vw.hpp>
//#include "FundCommGroupList.hpp"
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
#include "FeeParamSysList.hpp"
#include "FeeParamSys.hpp"
namespace  
{
   const I_CHAR * const CLASSNAME						= I_( "FundSponsorFee" );
   const I_CHAR * const FEE_SCALE_SYS_LIST				= I_( "FeeScaleSysList" );
   const I_CHAR * const FLAT							= I_( "0" );
   const I_CHAR * const PERCENT							= I_( "1" );
   const I_CHAR * const SCALE							= I_( "2" );
   const I_CHAR * const TIER							= I_( "3" );   
   const I_CHAR * const YES								= I_("Y");
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE			= I_("18");
   const I_CHAR * const FEE_CODE_MANAGEMENT_REBATE		= I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT	= I_("180");
   const I_CHAR * const IDI_FUNDCLASS					= I_("FUNDCLASS");   
   const I_CHAR * const IDI_RATE						= I_("RATE");
   const I_CHAR * const IDI_MIN_RATE					= I_("MINRATE");
   const I_CHAR * const IDI_MAX_RATE					= I_("MAXRATE");
   const I_CHAR * const IDI_GRADE						= I_("GRADE");
   const I_CHAR * const SEARCH_BY_FEE_CODE				= I_("FeeCode");
   const I_CHAR * const NO								= I_("No");
   const I_CHAR * const BASEDON_SCALE					= I_( "1" );
   const I_CHAR * const IDI_CODE						= I_("CODE");  
   const I_CHAR * const VALIDATE_TYPE					= I_("DupCheck");
   const I_CHAR * const FEE_CODE_VISCOUNT_FEE			= I_("118");
   const I_CHAR * const SYSTEM_LEVEL					= I_("SYSTEM");
   const I_CHAR * const FUND_SPONSOR            = I_("FUNDSPONSOR");
   const I_CHAR * const FEEMODEL                = I_("FEEMODEL");
   const I_CHAR * const ModelOption                = I_("MODELOPTION");
   const I_CHAR * const FeeCode                    = I_("FEECODE");

   const I_CHAR * const BONIMAX				      		= I_("3");
   const I_CHAR * const BUYATNAV				      	= I_("2");
   const I_CHAR * const DISCOUNTMODEL					= I_("1");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId Level;
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
   extern CLASS_IMPORT const BFTextFieldId SystematicCrossField1;
   extern CLASS_IMPORT const BFTextFieldId FeeModelOption;
   extern CLASS_IMPORT const BFTextFieldId ChargeOptionList;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit1;
}

namespace CND
{  // Conditions used
   extern const long ERR_AT_LEAST_ONE_RECORD_FOR_SCALE;
   extern const long ERR_FEE_CODE_OVERLAPED;  
   extern const long ERR_INVALID_FAMILY_CODE;  
   extern const long ERR_FEE_TYPE_SCALE_ONLY;
   extern const long ERR_RATE_IS_OUT_OF_RANGE;
   extern const long ERR_RATE_LESS_THAN_MIN;
   extern const long ERR_STOPDATE_INVALID_FOR_BUYATNAV;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_FEECODE_NOT_APPLY_TO_MODELOPTION;
   extern const long WARN_FEECODE_NOT_APPLY_TO_MODELOPTION;
   extern const long ERR_RATE_IS_OUT_OF_RANGE;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FeeCode,              BFCBO::NONE,                 0 }, 
   { ifds::ParamFeeType,             BFCBO::NONE,                 0 }, 
   { ifds::EffectiveDate,				   BFCBO::NONE,                 0 }, 
   { ifds::StopDate,				   BFCBO::NONE,                 0 }, 

   { ifds::Rate,                    BFCBO::NONE,                 0 }, 
   { ifds::Currency,                    BFCBO::NONE,                 0 }, 
   { ifds::SystematicCrossField1,   BFCBO::IMMEDIATE_VALIDATION,                 0 }, 
   { ifds::CompoundDate,					   BFCBO::NONE,                 0 }, 
   //{ ifds::FeeCodeSet,                BFCBO::NONE,                 0 }, 
   { ifds::ChargeOption,            BFCBO::NONE,                 0 }, 
   { ifds::FeeModelCode,		   BFCBO::NONE,	0 }, 
   { ifds::CommGroup,		   BFCBO::NONE,	0 }, 
   { ifds::MaxFee,		   BFCBO::NONE,	0 }, 
   { ifds::MinFee,		   BFCBO::NONE,	0 }, 
   { ifds::FieldCrossEdit1, BFCBO::NONE,                 0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FundSponsorFee::FundSponsorFee( BFAbstractCBO &parent )
: FeeParamBase( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit(ifds::CompoundDate, ifds::EffectiveDate);
   addCrossEdit(ifds::CompoundDate, ifds::StopDate);

   addCrossEdit(ifds::SystematicCrossField1, ifds::EffectiveDate);
   addCrossEdit(ifds::SystematicCrossField1, ifds::StopDate);
   addCrossEdit(ifds::SystematicCrossField1, ifds::FeeCode);

   addCrossEdit(ifds::FieldCrossEdit1, ifds::MaxFee);
   addCrossEdit(ifds::FieldCrossEdit1, ifds::MinFee);
   addCrossEdit(ifds::FieldCrossEdit1, ifds::Rate);

   //addCrossEdit(ifds::SystematicCrossField1, ifds::ParamFeeType);

}
//******************************************************************************************
FundSponsorFee::~FundSponsorFee()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//************************************************************************************

SEVERITY FundSponsorFee::InitNew( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "InitNew" ) );

//   setFieldNoValidate (ifds::FundSponsorID, dstrFundSponsorID, idDataGroup, false);
//   setFieldNoValidate (ifds::FundSponsorID, dstrFundSponsorID, BF::HOST, false);

  	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY FundSponsorFee::Init(const BFData& data, bool bDefault )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );  
   attachDataObject(const_cast<BFData&>(data), false);  

   if ( !isNew() )
   {
	   setFieldReadOnly(ifds::FeeCode, BF::HOST,true); 
   }

   DString dstrFeeCode = data.getElementValue( I_( "FeeCode" ) );
   dstrFeeCode.strip();

   getFeeParamConfigDefaults( dstrFeeCode, BF::HOST, false );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY FundSponsorFee::getFeeParamConfigDefaults( DString dstrFeeCode, const BFDataGroupId& idDataGroup, bool setDefaultParam )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeParamConfigDefaults" ) );

   FeeParamConfigList *pFeeParamConfigList = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {
      if( pFeeParamConfigList )
      {	
           DString strKey, dstrFeeTypeList;
		   pFeeParamConfigList->buildKeyForFundSponsorLevel( dstrFeeCode, strKey );

           BFObjIter iter( *pFeeParamConfigList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
           if( iter.positionByKey(strKey ) ) 
		   {
				FeeParamConfig * pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
				pFeeParamConfig->getFeeTypeList(dstrFeeTypeList);
				setFieldAllSubstituteValues(ifds::ParamFeeType, idDataGroup, dstrFeeTypeList);            

				if( setDefaultParam ) setDefFeeParam( idDataGroup );

				DString chargeOptionList;
				pFeeParamConfig->getField (ifds::ChargeOptionList, chargeOptionList, idDataGroup, false);
				bool bChargeOptionDefaultsRead = 
					loadSubstitutionList (ifds::ChargeOption, idDataGroup, chargeOptionList);
		   }         
      }
   }
   else
   {
		CLEARCONDITIONSFRAMECURRENT(); 
   } 

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************

SEVERITY FundSponsorFee::getFeeScaleList( FeeScaleBaseList* &pFeeScaleList, const BFDataGroupId& idDataGroup,bool bInquire, bool bDefault, bool bRemObj, bool bDelete)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeScaleList" ) );

   DString dstrFeeID;
   getField( ifds::FeeID, dstrFeeID, idDataGroup );

   FeeScaleSysList* pFeeScaleSysList = dynamic_cast<FeeScaleSysList*>( BFCBO::getObject( I_( "FeeScaleSysList"), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFeeScaleSysList )
   {
      if( isNew() )
      {
         pFeeScaleSysList = new FeeScaleSysList( *this );
         pFeeScaleSysList->setFeeParamBase(this);
         pFeeScaleSysList->initNew(idDataGroup);
      }
      else if( bInquire && dstrFeeID != NULL_STRING ) //make the view call
      {
         pFeeScaleSysList = new FeeScaleSysList( *this );
         pFeeScaleSysList->setFeeParamBase(this);
         pFeeScaleSysList->init( dstrFeeID );         
         idWorkingDataGroup = BF::HOST;
      }
      if( pFeeScaleSysList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
				DString dstrFeeCode;
				getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false );
				BFObjIter iter1( *pFeeScaleSysList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
				while ( !iter1.end() )
				{
					iter1.getObject()->setField(ifds::FeeCode,dstrFeeCode,idDataGroup,false );
					++iter1;
				}            

            setObject( pFeeScaleSysList, I_( "FeeScaleSysList"), OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
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
//***********************************************************************************
SEVERITY FundSponsorFee::doValidateField( const BFFieldId &idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   FeeParamBase::doValidateField( idField,strValue, idDataGroup );

   if ( idField == ifds::CompoundDate )
      FeeParamBase::ValidateEffectiveStopDate(idDataGroup );
   else if ( idField == ifds::SystematicCrossField1 )
   {
		validateFeeOverlap(idDataGroup);
   }
   else if( idField == ifds::Rate || idField == ifds::MaxFee || idField == ifds::MinFee )
   {
      validateRate(idDataGroup, strValue);
   }
   else if( idField == ifds::FeeCode)
   {
      validateFeeCode(idDataGroup);
   }
   else if ( idField == ifds::FieldCrossEdit1 )
   {
	  validateMinMax( idDataGroup );
	  validateRateMinMax(idDataGroup);
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundSponsorFee::validateRate( const BFDataGroupId& idDataGroup, const DString& dstrRate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRate" ) )
   DString dstrFeeType;
   getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip().upperCase();

   double dRate =  DSTCommonFunctions::convertToDouble( dstrRate );
   if( dstrFeeType == PERCENT )
   {
      if( dRate > 100.0 || dRate < 0.0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundSponsorFee::validateRateMinMax( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRate" ) )
   DString dstrRate, dstrMaxRate,dstrMinRate;

   getField(ifds::Rate,dstrRate,idDataGroup );
   getField(ifds::MinFee,dstrMinRate,idDataGroup );
   getField(ifds::MaxFee,dstrMaxRate,idDataGroup );
   double dMaxRate,dMinRate, dRate;
   dMaxRate =  DSTCommonFunctions::convertToDouble( dstrMaxRate );
   dMinRate =  DSTCommonFunctions::convertToDouble( dstrMinRate );   
   dRate =  DSTCommonFunctions::convertToDouble( dstrRate );
   if( dRate > dMaxRate || dRate < dMinRate )
   {
         DString dstrIDI;
         addIDITagValue( dstrIDI, IDI_MIN_RATE, dstrMinRate );
         addIDITagValue( dstrIDI, IDI_MAX_RATE, dstrMaxRate );
         //ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_IS_OUT_OF_RANGE, dstrIDI );               
		  ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_IS_OUT_OF_RANGE, I_("MINRATE=MINRATE;MAXRATE=MAXRATE;") );               
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundSponsorFee::validateFeeCode( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRate" ) )
   DString dstrFeeCode, dstrFeeModelOption, FeeCodeDesc, ModelDesc;
   getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
   getField(ifds::FeeCode,FeeCodeDesc,idDataGroup,true);


   dstrFeeCode.strip().upperCase();
   getParent()->getParent()->getField(ifds::FeeModelOption, dstrFeeModelOption, idDataGroup, false );
   getParent()->getParent()->getField(ifds::FeeModelOption, ModelDesc, idDataGroup, true );

	DString strTemp;
	addIDITagValue (strTemp, FeeCode, FeeCodeDesc );
	addIDITagValue (strTemp, ModelOption, ModelDesc );
	 
   if( ( dstrFeeModelOption == DISCOUNTMODEL /*|| dstrFeeModelOption == BONIMAX*/) && ( dstrFeeCode == I_("112") || dstrFeeCode == I_("113") ))
   {	
       FundSponsorFeeList *pFundSponsorFeeList = dynamic_cast<FundSponsorFeeList*>(getParent());       
	   if( pFundSponsorFeeList->Not100PercentDiscount( idDataGroup ) )
	   {
			ADDCONDITIONFROMFILEIDI (CND::WARN_FEECODE_NOT_APPLY_TO_MODELOPTION, strTemp);
	   }
   }
   if( ( dstrFeeModelOption == BUYATNAV || dstrFeeModelOption == BONIMAX ) && ( dstrFeeCode == I_("110") || dstrFeeCode == I_("111") ))
   {
		if( isNew() )   // for new record, issue error immediately
		{
			ADDCONDITIONFROMFILEIDI (CND::ERR_FEECODE_NOT_APPLY_TO_MODELOPTION, strTemp);
		}
		else
		{
			ADDCONDITIONFROMFILEIDI (CND::WARN_FEECODE_NOT_APPLY_TO_MODELOPTION, strTemp);
		}
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void FundSponsorFee::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   DString dstrCurrBusDate, stopDate;
   setFieldRequired( ifds::FeeCode, idDataGroup, true );
   setFieldReadOnly(ifds::FeeCode, idDataGroup,false);
   //set FeeCodeSubList from FeeParamConfigList by passing level as "FUNDSPONSOR" and associate the list with FeeCode field
   setFieldRequired( ifds::ParamFeeType, idDataGroup, true );
   setFieldReadOnly(ifds::ParamFeeType, idDataGroup,false);
   setFieldRequired( ifds::Currency, idDataGroup, true );
   setFieldReadOnly(ifds::Currency, idDataGroup,false);
   
   DString dstrSysCurrency;
   getWorkSession().getMgmtCoOptions()->getField( ifds::SysCurrency, dstrSysCurrency, idDataGroup ,false );
	dstrSysCurrency.strip().upperCase();
   setFieldNoValidate (ifds::Currency, dstrSysCurrency, idDataGroup, false );

   getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false);
/*
   DString dstrFeeModelOption;
   getParent()->getParent()->getField(ifds::FeeModelOption, dstrFeeModelOption, idDataGroup, false );
   if( dstrFeeModelOption == BUYATNAV )
   {
         DString dstrCurrBusDate;
         getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
         setField(ifds::StopDate, dstrCurrBusDate, idDataGroup, false);         
   }
   else*/
   {
      getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
      setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false );
   }

   FeeParamConfigList *pFeeParamConfigList = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {
		DString dstrFeeCodeSubList;	
	   pFeeParamConfigList->getFeeCodeList(dstrFeeCodeSubList, FEEMODEL);
		setFieldAllSubstituteValues(ifds::FeeCode, idDataGroup, dstrFeeCodeSubList);
   }
   else
   {
		CLEARCONDITIONSFRAMECURRENT(); 
   }
   //copy FeeModelCode and FundGroup from parent->parent
   DString dstrFeeModelCode, dstrFundGroup;
   getParent()->getParent()->getField(ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false );
   getParent()->getParent()->getField(ifds::FundGroup, dstrFundGroup, idDataGroup, false );
   setFieldNoValidate (ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false );
   setFieldNoValidate (ifds::CommGroup, dstrFundGroup, idDataGroup, false );
   setFieldNoValidate (ifds::ChargeOption, I_("0"), idDataGroup, false);
}
 

//***********************************************************************************
SEVERITY FundSponsorFee::validateFeeOverlap(const BFDataGroupId& idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeOverlap" ) );

   FundSponsorFeeList *pFundSponsorFeeList = 
         dynamic_cast<FundSponsorFeeList*>(getParent());
      
   pFundSponsorFeeList->validateOverlapping(this, idDataGroup);

	return(GETCURRENTHIGHESTSEVERITY());

}


//******************************************************************************
void FundSponsorFee::doFeeCodeRelatedChanges(const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doFeeCodeRelatedChanges" ) );
	FeeParamBase::doFeeCodeRelatedChanges(idDataGroup);

	DString dstrFeeCode;
	getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false );

	getFeeParamConfigDefaults( dstrFeeCode, idDataGroup, true );
}

//*********************************************************************************
SEVERITY FundSponsorFee::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   SEVERITY severity = FeeParamBase::validateFeeScaleList( idDataGroup);
   if (severity > WARNING)
   {
		PROMOTECONDITIONS();
		CLEARCONDITIONSFRAMECURRENT();      
   }

/*   //check stopdate must be currentbusdate if parent is BuyAtNAV FeeCode is 110 or 111
   DString dstrFeeModelOption, dstrFeeCode;
   getParent()->getParent()->getField(ifds::FeeModelOption, dstrFeeModelOption, idDataGroup, false );
   getField( ifds::FeeCode, dstrFeeCode, idDataGroup, false );
   if( dstrFeeModelOption == BUYATNAV && (dstrFeeCode == I_("110") || dstrFeeCode == I_("111") ) )         
   {
         DString dstrCurrBusDate,dstrStopDate;
         getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
         getField(ifds::StopDate,dstrStopDate,idDataGroup,false);         

         if( DSTCommonFunctions::CompareDates( dstrCurrBusDate, dstrStopDate ) == DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILEIDI ( CND::ERR_STOPDATE_INVALID_FOR_BUYATNAV, DString (I_ ("FIELDNAME=")) + I_("StopDate"));            
         }

   }
*/
   return(GETCURRENTHIGHESTSEVERITY());

}

//*****************************************************************************************
SEVERITY FundSponsorFee::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   FeeParamBase::doApplyRelatedChanges( idField,idDataGroup );
	if( idField == ifds::Rate  )
	{
			DString dstrRate;
			getField( ifds::Rate,dstrRate,idDataGroup,false);
//			setFieldNoValidate (ifds::MaxFee, dstrRate, idDataGroup, false );
			
			FundSponsorFeeList *pFundSponsorFeeList = dynamic_cast<FundSponsorFeeList*>(getParent());       
			pFundSponsorFeeList->setFieldValidflag( ifds::FeeCode, idDataGroup, false );
	}
	if( idField == ifds::FeeCode )
	{
		DString dstrFeeCode;
		getField( ifds::FeeCode,dstrFeeCode,idDataGroup,false);
		if( dstrFeeCode == I_("110") || dstrFeeCode == I_("111") )
		{
			setFieldNoValidate (ifds::MaxFee, I_("100"), idDataGroup, false );
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());

}

//*****************************************************************************************
SEVERITY FundSponsorFee::setDefFeeParam(  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefFeeParam" ) );
   FeeParamSysList * pFeeParamSysList;
   FeeParamSys * pFeeParamSys;
   if (getMgmtCo().getDefaultFeeParamSysList(pFeeParamSysList) <= WARNING && pFeeParamSysList)
   {
      DString dstrFeeCode, dstrFundGroup, dstrFeeType, dstrFeeRate;
		getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false );
      getParent()->getParent()->getField(ifds::FundGroup, dstrFundGroup, idDataGroup, false );

      pFeeParamSysList->getDefaultFeeParamRecord(
													pFeeParamSys, 
													dstrFeeCode,
													NULL_STRING,
													NULL_STRING,
													dstrFundGroup,																			
													BF::HOST,
                                       false,
                                       false
													);                                     
      if( pFeeParamSys )
      {
         pFeeParamSys->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup, false );
         pFeeParamSys->getField(ifds::Rate, dstrFeeRate, idDataGroup, false );
	      setFieldNoValidate (ifds::ParamFeeType, dstrFeeType, idDataGroup, false,true,true );	
	      setFieldNoValidate (ifds::Rate, dstrFeeRate, idDataGroup, false,true,true );	
      }
      else
      {
         PROMOTECONDITIONS();
		   CLEARCONDITIONSFRAMECURRENT();
      }
   }
   else
   {
		PROMOTECONDITIONS();
		CLEARCONDITIONSFRAMECURRENT();      
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//*******************************************************************************
void FundSponsorFee::stampCurBusinessDateToStopDate( const BFDataGroupId& idDataGroup )
{
   DString dstrCurrBusDate,dstrStopDate,dstrFeeCode;
   getField( ifds::FeeCode, dstrFeeCode, idDataGroup, false );	
	dstrFeeCode.strip();
	getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
	getField(ifds::StopDate,dstrStopDate,idDataGroup,false);
	if (DSTCommonFunctions::CompareDates (dstrStopDate, dstrCurrBusDate) 
               == DSTCommonFunctions::SECOND_EARLIER  && (dstrFeeCode == I_("110") ||
						dstrFeeCode == I_("111") )     )
	{	
	    setFieldNoValidate (ifds::StopDate, dstrCurrBusDate, idDataGroup, false );
       setFieldUpdated( ifds::StopDate, idDataGroup, true );
	}
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSponsorFee.cpp-arc  $
// 
//    Rev 1.36   Apr 27 2005 11:49:36   Fengyong
// #Incident 288891 - Delay validate fee rate and max min fee.
// set default max to 100 for discount rate.
// 
//    Rev 1.35   Apr 14 2005 08:58:32   yingbaol
// Incident 265632 Change set default fee logic for FundSponsorFee
// 
//    Rev 1.34   Apr 10 2005 20:43:54   popescu
// Incidentt# 285150, do not se the max value of the fee to defaul rate. Issue should not happen after the introduction of the max field
// 
//    Rev 1.33   Apr 07 2005 10:07:04   yingbaol
// Incident#280394, take out some checking for management dee discount.
// 
//    Rev 1.32   Apr 04 2005 18:08:56   Fengyong
// #280394 - Validate Max min over fee rate
// 
//    Rev 1.31   Mar 28 2005 09:43:14   Fengyong
// Incident #260676 - Add max min fee validation
// 
//    Rev 1.30   Mar 24 2005 16:01:16   Fengyong
// Incident #260676 - Add max min to fundsponsor fee parameter
// 
//    Rev 1.29   Mar 21 2005 11:34:10   yingbaol
// Incident 243190: Stopdate has not been saved to database.
// 
//    Rev 1.28   Mar 16 2005 11:46:48   Fengyong
// Incident #246230 - remove warning for bonimax + transaction and discount (100%) + transaction
// 
//    Rev 1.27   Jan 20 2005 18:18:08   winnie
// PTS 10037440 - Discount rate and Bonimax should be get warning for set up of Transaction Fee since Discount and Bonimax are similar where Bonimax is the maximum discount a trade can ever gets.
// 
//    Rev 1.26   Jan 20 2005 13:54:26   Fengyong
// PTS10038102 - alow discount fee model have fee code 112, 113
// 
//    Rev 1.25   Jan 17 2005 16:25:24   Fengyong
// PET10037923 - Charge option default value and sub list come from view #253
// 
//    Rev 1.24   Jan 05 2005 10:07:00   Fengyong
// PTS10037440 - restrict condition rate to Bonimax model option.
// 
//    Rev 1.23   Dec 20 2004 15:47:34   yingbaol
// PTS10036888:fix default fee issue
// 
//    Rev 1.22   Nov 29 2004 16:14:02   Fengyong
// PET1117 FN56 - 3rd_party fund trade processing
// 
//    Rev 1.21   Nov 14 2004 14:43:00   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.20   Nov 09 2004 10:13:30   YINGBAOL
// PTS10035274: sync. version 1.18.1.0
// 
//    Rev 1.19   Nov 06 2004 00:41:08   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.18   Nov 05 2004 11:03:10   YINGBAOL
// PTS10035274: change logic for validate feecode and validateAll
// 
//    Rev 1.17   Nov 02 2004 11:01:26   FENGYONG
// PTS10035274 - Validation between ModelOption and FeeCode
// 
//    Rev 1.16   Oct 21 2004 17:23:28   YINGBAOL
// PTS10034903: change logic for stamp current business date to stop date.
// 
//    Rev 1.15   Oct 21 2004 10:00:08   FENGYONG
// PTs 10034913 - Rate not being validate in FundSponsor Fee
// 
//    Rev 1.14   Oct 18 2004 16:55:26   FENGYONG
// PTS 10034776 - Buy And NAV overlapping check
// 
//    Rev 1.13   Oct 18 2004 09:54:20   FENGYONG
// PTS10034779 - Fee type should not be included as unique key for fee set up.
// 
//    Rev 1.12   Sep 29 2004 09:32:56   FENGYONG
// PET1117FN5 - change after ess walk through 
// 
//    Rev 1.11   Sep 21 2004 17:32:48   FENGYONG
// Add condition ERR_STOPDATE_INVALID_FOR_BUYATNAV
// 
//    Rev 1.10   Sep 20 2004 15:53:48   FENGYONG
// change stop date initialize
// 
//    Rev 1.9   Sep 20 2004 15:35:50   FENGYONG
// if parent is chargeoption = BuyAtNAV, the stop date should be currentbusdate when add new fee
// 
//    Rev 1.8   Sep 15 2004 12:21:20   FENGYONG
// ReceiveAll
// 
//    Rev 1.7   Sep 14 2004 16:41:38   FENGYONG
// Set Fundsponsor and FeeModel code to the new object
// 
//    Rev 1.6   Sep 10 2004 15:51:52   FENGYONG
// PET1117 FN5 - Client Fee
// 
//    Rev 1.5   Sep 09 2004 12:37:04   FENGYONG
// small fix - PET1117 FN5
// 
// 
//    Rev 1.4   Sep 02 2004 12:30:56   FENGYONG
// Add Conditions for PET1117 FN5
// 
//    Rev 1.3   Aug 31 2004 17:30:32   FENGYONG
// change Field names
// 
//    Rev 1.2   Aug 11 2004 18:37:20   FENGYONG
// Temp check in  PET 117 FN5  for other enhancement compiling
// 
//    Rev 1.1   Aug 10 2004 11:24:32   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.0   Aug 09 2004 10:06:18   FENGYONG
// Initial Revision
// 
*/
