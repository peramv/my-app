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
// ^FILE   : FundBrokerFee.cpp
// ^AUTHOR : 
// ^DATE   : July 26, 2004
//
// ^CLASS    : FundBrokerFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundBrokerFee.hpp"
#include "FundBrokerFeelist.hpp"

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

#include "FeeParamSysList.hpp"
#include "FeeParamSys.hpp"
namespace  
{
   const I_CHAR * const CLASSNAME						= I_( "FundBrokerFee" );
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

   const I_CHAR * const BUYATNAV				      	= I_("2");
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
   extern CLASS_IMPORT const BFTextFieldId FundBrokerCode;
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
   { ifds::CommGroup,		   BFCBO::NONE,	0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FundBrokerFee::FundBrokerFee( BFAbstractCBO &parent )
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

}
//******************************************************************************************
FundBrokerFee::~FundBrokerFee()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//************************************************************************************

SEVERITY FundBrokerFee::InitNew( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "InitNew" ) );


  	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY FundBrokerFee::Init(const BFData& data, bool bDefault )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );  
   attachDataObject(const_cast<BFData&>(data), false);  

   if ( !isNew() )
   {
	   setFieldReadOnly(ifds::FeeCode, BF::HOST,true); 
   }

   DString dstrFeeCode = data.getElementValue( I_( "FeeCode" ) );
   dstrFeeCode.strip();
   FeeParamConfigList *pFeeParamConfigList = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {
      if( pFeeParamConfigList )
      {	
         DString strKey, dstrFeeTypeList;
		 pFeeParamConfigList->buildKeyForFundBrokerLevel( dstrFeeCode, strKey );

         BFObjIter iter( *pFeeParamConfigList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
         if( iter.positionByKey(strKey ) ) 
			{
				FeeParamConfig * pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
				pFeeParamConfig->getFeeTypeList(dstrFeeTypeList);
				setFieldAllSubstituteValues(ifds::ParamFeeType, BF::HOST, dstrFeeTypeList);            
			}         
      }
   }
   else
   {
		CLEARCONDITIONSFRAMECURRENT(); 
   }     

   bool bIsSameDate = isTheSameBusinessDate(BF::HOST);
   if( !bIsSameDate && !isNew() )
   {
	   setFieldReadOnly(ifds::Rate, BF::HOST,true);
	   setFieldReadOnly(ifds::ParamFeeType, BF::HOST,true);
	   setFieldReadOnly(ifds::EffectiveDate, BF::HOST,false);
	   setFieldReadOnly(ifds::StopDate, BF::HOST,false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//***********************************************************************************
SEVERITY FundBrokerFee::doValidateField( const BFFieldId &idField,
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
   else if( idField == ifds::Rate)
   {
      validateRate(idDataGroup);
   }

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundBrokerFee::validateRate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRate" ) )
   DString dstrFeeType, dstrRate;
   getField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false);
   dstrFeeType.strip().upperCase();
   getField(ifds::Rate,dstrRate,idDataGroup );
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

void FundBrokerFee::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   DString dstrCurrBusDate, stopDate;
   setFieldRequired( ifds::FeeCode, idDataGroup, true );
   setFieldReadOnly(ifds::FeeCode, idDataGroup,false);
   //set FeeCodeSubList from FeeParamConfigList by passing level as "FUNDSPONSOR" and associate the list with FeeCode field
   setFieldRequired( ifds::ParamFeeType, idDataGroup, true );
   setFieldReadOnly(ifds::ParamFeeType, idDataGroup,false);
   setFieldRequired( ifds::Currency, idDataGroup, false );
   setFieldReadOnly(ifds::Currency, idDataGroup,false);
   
   getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false);

   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false );

   FeeParamConfigList *pFeeParamConfigList = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {
		DString dstrFeeCodeSubList;	
        //need extral filter	   
        //pFeeParamConfigList->getFeeCodeList(dstrFeeCodeSubList, SYSTEM_LEVEL, I_("FNDBRK"));

		//Jan 28, 2005 PTS 10038176, Fee code list should be filtered by level = "FNDBROKER".
		pFeeParamConfigList->getFeeCodeList(dstrFeeCodeSubList, I_("FNDBROKER"));
		
		setFieldAllSubstituteValues(ifds::FeeCode, idDataGroup, dstrFeeCodeSubList);
   }
   else
   {
		CLEARCONDITIONSFRAMECURRENT(); 
   }
   
   DString dstrFundBrokerCode;
   getParent()->getParent()->getField(ifds::FundBrokerCode, dstrFundBrokerCode, idDataGroup, false );
   setFieldNoValidate (ifds::CommGroup, dstrFundBrokerCode, idDataGroup, false );
}
 

//***********************************************************************************
SEVERITY FundBrokerFee::validateFeeOverlap(const BFDataGroupId& idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFeeOverlap" ) );

   FundBrokerFeeList *pFundBrokerFeeList = 
         dynamic_cast<FundBrokerFeeList*>(getParent());
      
   pFundBrokerFeeList->validateOverlapping(this, idDataGroup);

	return(GETCURRENTHIGHESTSEVERITY());

}


//******************************************************************************
void FundBrokerFee::doFeeCodeRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doFeeCodeRelatedChanges" ) );
	FeeParamBase::doFeeCodeRelatedChanges(idDataGroup);

   FeeParamConfigList *pFeeParamConfigList = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {
      if( pFeeParamConfigList )
      {
			DString dstrFeeCode, strKey, dstrFeeTypeList;
			getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false );
		   pFeeParamConfigList->buildKeyForFundBrokerLevel( dstrFeeCode, strKey );

         BFObjIter iter( *pFeeParamConfigList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
         if( iter.positionByKey(strKey ) ) 
			{
				FeeParamConfig * pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
            pFeeParamConfig->getFeeTypeList(dstrFeeTypeList);
            setFieldAllSubstituteValues(ifds::ParamFeeType, idDataGroup, dstrFeeTypeList);
            setDefFeeParam( idDataGroup );
			}         
      }
   }
   else
   {
		CLEARCONDITIONSFRAMECURRENT(); 
   }      
}

//*********************************************************************************
SEVERITY FundBrokerFee::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************************
SEVERITY FundBrokerFee::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   FeeParamBase::doApplyRelatedChanges( idField,idDataGroup );

	return(GETCURRENTHIGHESTSEVERITY());

}
//*****************************************************************************************
SEVERITY FundBrokerFee::setDefFeeParam(  const BFDataGroupId& idDataGroup )
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
                                       true 
													);                                     
      if( pFeeParamSys )
      {
         pFeeParamSys->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup, false );
         pFeeParamSys->getField(ifds::Rate, dstrFeeRate, idDataGroup, false );
         setField(ifds::ParamFeeType,dstrFeeType,idDataGroup,false );
         setField(ifds::Rate,dstrFeeRate,idDataGroup,false );         
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
//*****************************************************************************************
SEVERITY FundBrokerFee::getFeeScaleList( FeeScaleBaseList* &pFeeScaleList, const BFDataGroupId& idDataGroup,bool bInquire, bool bDefault, bool bRemObj, bool bDelete)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeScaleList" ) );

	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerFee.cpp-arc  $
// 
//    Rev 1.8   Apr 14 2005 14:03:16   Fengyong
// Incident #288908 - check Fundbroker fee type = "FNDBROKER"
// 
//    Rev 1.7   Apr 14 2005 08:58:28   yingbaol
// Incident 265632 Change set default fee logic for FundSponsorFee
// 
//    Rev 1.6   Mar 29 2005 14:17:42   Fengyong
// Incident #269462 - allow user modify effective date and stop date even if not the same date
// 
//    Rev 1.5   Jan 28 2005 19:00:04   Fengyong
// PET10038176 - Feecode should be filtered by Level = "FUNBROKER"
// 
//    Rev 1.4   Nov 25 2004 15:01:26   Fengyong
// do not allow modify fee is isnotsamedate
// 
//    Rev 1.3   Nov 23 2004 17:25:04   Fengyong
// PET1117FN54 - adjustment after first day intergretion test
// 
//    Rev 1.2   Nov 14 2004 14:41:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Nov 06 2004 00:41:04   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.0   Nov 02 2004 16:00:46   FENGYONG
// Initial revision.
// 
*/
