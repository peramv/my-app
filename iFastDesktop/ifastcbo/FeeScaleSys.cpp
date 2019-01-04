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
// ^FILE   : FeeScaleSys.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 08, 2002
//
// ^CLASS    : FeeScaleSys
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeScaleSys.hpp"
#include "FeeScaleSysList.hpp"
#include "FeeParamSys.hpp"
#include <bfcbo\bfobjiter.hpp>
#include "fundfeelist.hpp"
#include <ifastdataimpl\dse_dstc0231_vw.hpp>
#include <ifastdataimpl\dse_dstc0197_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

#include "feeparamconfiglist.hpp"
#include "feeparamconfig.hpp"
#include "FeeThrshldSys.hpp"



namespace CND
{  // Conditions used
	extern const long ERR_RATE_IS_OUT_OF_RANGE;
	extern const long ERR_RATE_LESS_THAN_MIN;
}

namespace  
{
   const I_CHAR * const CLASSNAME		= I_( "FeeScaleSys" );
   const I_CHAR * const IDI_RATE		= I_("RATE");
   const I_CHAR * const IDI_MIN_RATE	= I_("MINRATE");
   const I_CHAR * const IDI_MAX_RATE	= I_("MAXRATE");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit1;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit2;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFTextFieldId UpdateRule;
   extern CLASS_IMPORT const BFDateFieldId FMLastProcDate;

}


//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FeeCode,			      BFCBO::NONE, 0 }, 
   { ifds::Level,			         BFCBO::NONE, 0 }, 
   { ifds::ScaleRate,            BFCBO::NONE, 0 }, 
   { ifds::UpperBound,           BFCBO::NONE, 0 }, 
   { ifds::LowerBound,           BFCBO::NONE, 0 }, 
   { ifds::MinFee,			      BFCBO::NONE, 0 }, 
   { ifds::MaxFee,               BFCBO::NONE, 0 }, 
   { ifds::ScaleEffectiveDate,   BFCBO::NONE, 0 }, 
   { ifds::InvestTerm,		      BFCBO::NONE, 0 }, 
   { ifds::FieldCrossEdit1,      BFCBO::NONE, 0 }, 
   { ifds::FieldCrossEdit2,      BFCBO::NONE, 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FeeScaleSys::FeeScaleSys( BFAbstractCBO &parent ) 
: FeeScaleBase( parent )
, localData(0)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit(ifds::FieldCrossEdit1, ifds::LowerBound);
   addCrossEdit(ifds::FieldCrossEdit1, ifds::UpperBound);
   addCrossEdit(ifds::FieldCrossEdit2, ifds::MaxFee);
   addCrossEdit(ifds::FieldCrossEdit2, ifds::MinFee);

}
//------------------------------------------------------------------------
FeeScaleSys::~FeeScaleSys()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete localData;
}     
//------------------------------------------------------------------------------------
SEVERITY FeeScaleSys::init( const BFData& InstData, bool bDefault )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData& )" ) );
   localData = new BFData(InstData);
   attachDataObject( const_cast<BFData&>(*localData), false, true );
   bool bReadOnly = false;
   if ( !bDefault )
   {
	   bReadOnly = isScaleReadOnly(BF::HOST);
   }
   setFieldReadOnly(ifds::ScaleRate,BF::HOST,bReadOnly);
   setFieldReadOnly(ifds::UpperBound,BF::HOST,bReadOnly);   
   setFieldReadOnly(ifds::LowerBound,BF::HOST,bReadOnly); 
   setFieldReadOnly(ifds::MinFee,BF::HOST,bReadOnly); 
   setFieldReadOnly(ifds::MaxFee,BF::HOST,bReadOnly); 
   setFieldReadOnly(ifds::InvestTerm, BF::HOST, bReadOnly);

   return(GETCURRENTHIGHESTSEVERITY());
}
//------------------------------------------------------------------------------------
bool FeeScaleSys::isTheSameBusinessDate(const BFDataGroupId& idDataGroup)
{
   DString strCurBusDate,strEffectiveDate;
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
//   getField(ifds::ProcessDate,strProcessDate,idDataGroup,false);
//   if( DSTCommonFunctions::CompareDates(strCurBusDate,strProcessDate ) == DSTCommonFunctions::EQUAL )
   getParent()->getParent()->getField(ifds::EffectiveDate,strEffectiveDate,idDataGroup,false);
   if( DSTCommonFunctions::CompareDates(strCurBusDate,strEffectiveDate ) != DSTCommonFunctions::SECOND_EARLIER )
   {
      return(true);
   }
   return(false);
}
//------------------------------------------------------------------------------------
bool FeeScaleSys::isScaleReadOnly(const BFDataGroupId& idDataGroup)
{
   DString strCurBusDate;
   DString strEffectiveDate;
   DString strFMLastProcDate;

	DString dstrFeeCode;
	DString dstrGroupType;
   DString dstrUpdateRule = I_("0");

   FeeParamSys* pFeeParamSys = NULL;
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   
   FeeScaleSysList* pFeeScaleSysList = dynamic_cast<FeeScaleSysList* >(getParent());
   if(pFeeScaleSysList)
   {
      pFeeParamSys = dynamic_cast<FeeParamSys*>(pFeeScaleSysList->getFeeParamBase());
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
      FeeThrshldSys *pFeeThrshldSys = dynamic_cast<FeeThrshldSys*>(getParent()->getParent());
      
      if (pFeeThrshldSys) // FeeScaleSys of Fee Type: Tier By Threshold 
      {
          pFeeThrshldSys->getParent()->getParent()->getField(ifds::EffectiveDate, strEffectiveDate,  idDataGroup,false);
      }
      else  // FeeScaleSys of other fee types
      {
          getParent()->getParent()->getField(ifds::EffectiveDate, strEffectiveDate,  idDataGroup,false);
      }

      if( DSTCommonFunctions::CompareDates(strCurBusDate,strEffectiveDate ) == DSTCommonFunctions::SECOND_EARLIER )
      {
         return(true);
      }
   }
   else
   {
      if(pFeeParamSys)
      {
         pFeeParamSys->getField(ifds::FMLastProcDate, strFMLastProcDate, idDataGroup, false);
         if(strFMLastProcDate == NULL_STRING || strFMLastProcDate == I_("12319999"))
         {
            return false;
         }
         else 
         {
            return true;
         }
      }
      return true;
   }

   return(false);
}
//*************************************************************************************
SEVERITY FeeScaleSys::init(const BFDataGroupId& idDataGroup ) // init new
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long )" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY FeeScaleSys::doValidateField( const BFFieldId& idField,
										         const DString& strValue,
										         const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   SEVERITY  svrn = NO_CONDITION;
   if( idField == ifds::FieldCrossEdit1 )
      validateLUBound(  idDataGroup );
   else if ( idField == ifds::FieldCrossEdit2 )
	  validateMinMax( idDataGroup );
   else if( idField == ifds::ScaleRate )
      validateScaleRate( idDataGroup );
   else if (idField == ifds::MaxFee)
      validateMaxFee(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//************************************************************************************************
SEVERITY FeeScaleSys::doApplyRelatedChanges ( const BFFieldId& idField, 
                                              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if (idField == ifds::LowerBound  || 
       idField == ifds::UpperBound)
   {
      setValidFlag (ifds::ScaleRate, idDataGroup, false); 
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FeeScaleSys::setValueFromDefault( BFCBO* pCBO, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFieldFromCBO" ) );

   DString strScaleRate, strUBound, strLBound, strMinFee, strMaxFee;
   pCBO->getField( ifds::ScaleRate, strScaleRate, idDataGroup, false );
   pCBO->getField( ifds::UpperBound, strUBound, idDataGroup, false );
   pCBO->getField( ifds::LowerBound, strLBound, idDataGroup, false );
   pCBO->getField( ifds::MinFee, strMinFee, idDataGroup, false );
   pCBO->getField( ifds::MaxFee, strMaxFee, idDataGroup, false );


   setFieldNoValidate( ifds::ScaleRate, strScaleRate, idDataGroup, false,true);
   setFieldNoValidate( ifds::UpperBound, strUBound, idDataGroup, false,true);
   setFieldNoValidate( ifds::LowerBound, strLBound, idDataGroup, false,true);
   setFieldNoValidate( ifds::MinFee, strMinFee, idDataGroup, false,true);
   setFieldNoValidate( ifds::MaxFee, strMaxFee, idDataGroup, false,true);
   setFieldUpdated( ifds::ScaleRate, idDataGroup, true );
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
//If default record exists, validate scale rate against the default value of MinFee/MaxFee
SEVERITY FeeScaleSys::validateScaleRate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateScaleRate" ) );
   FeeScaleBase::validateScaleRate(idDataGroup);
/*
   DString _dstrMinFee = NULL_STRING;
   DString _dstrMaxFee = NULL_STRING;
   // find the default record

   FeeParamSys *pFeeParamSysDef = NULL;

   dynamic_cast<FeeParamSys* >(getParent()->getParent() ) -> getFeeParamSysDef(pFeeParamSysDef, idDataGroup );

   if( pFeeParamSysDef )
   {   
	   DString dstrFeeType, dstrFeeTypeDef;
	   getParent()->getParent()->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup);
	   pFeeParamSysDef ->getField(ifds::ParamFeeType, dstrFeeTypeDef, BF::HOST);
	   if ( dstrFeeType == dstrFeeTypeDef )
	   {

		   FeeScaleBaseList *pFeeScaleDefaultList = NULL;
		   pFeeParamSysDef ->getFeeScaleList( pFeeScaleDefaultList,BF::HOST, true, true );
		   if ( pFeeScaleDefaultList )
			{
				BFObjIter iterScaleList(*pFeeScaleDefaultList,BF::HOST);
				DString dstrLevel, dstrScaleLevel;   
				getField(ifds::Level,dstrScaleLevel,idDataGroup );
				iterScaleList.begin();
				while( !iterScaleList.end() )
				{
					 BFAbstractCBO* pObj = iterScaleList.getObject();
					 if( pObj )
					 {
						 pObj->getField(ifds::Level,dstrLevel,BF::HOST );
						 if ( dstrScaleLevel == dstrLevel )
						 {

							 pObj->getField(ifds::MaxFee,_dstrMaxFee,BF::HOST );
							 pObj->getField(ifds::MinFee,_dstrMinFee,BF::HOST );
							 break;
						 }  
					 }
					 ++iterScaleList;
				}         
		   }
	   }
	}

   if ( _dstrMinFee.empty() || _dstrMaxFee.empty() ) // no default exist
		return(GETCURRENTHIGHESTSEVERITY());
	   		
	DString dstrScaleRate;
	double dScaleRate, dScaleMax, dScaleMin;

	getField(ifds::ScaleRate,dstrScaleRate,idDataGroup );
	dScaleRate =  DSTCommonFunctions::convertToDouble( dstrScaleRate );              
	dScaleMax =  DSTCommonFunctions::convertToDouble( _dstrMaxFee );
	dScaleMin =  DSTCommonFunctions::convertToDouble( _dstrMinFee );

	if ( dScaleMax == 0 && dScaleMin >0 )
	{
		if ( dScaleRate < dScaleMin )
		{
			DString dstrIDI;
			addIDITagValue( dstrIDI, IDI_MIN_RATE, _dstrMinFee );
			ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_LESS_THAN_MIN, dstrIDI ); 
		}

	}
	else if (dScaleRate < dScaleMin || dScaleRate > dScaleMax)
	{
		DString dstrIDI;
		addIDITagValue( dstrIDI, IDI_MIN_RATE, _dstrMinFee );
		addIDITagValue( dstrIDI, IDI_MAX_RATE, _dstrMaxFee );

		ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_IS_OUT_OF_RANGE, dstrIDI ); 
	}
		
*/   
   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY FeeScaleSys::clone(const BFDataGroupId& idDataGroup, FeeScaleSys*& pFeeScaleSysClone)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clone" ) );

   pFeeScaleSysClone = new FeeScaleSys((BFAbstractCBO&)(*this));

   for (int i = 0; i < NUM_FIELDS; i++)
   {
      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
      const BFFieldId &fieldId = fieldInfo.getFieldId();

      DString fieldValue;

      getField (fieldId, fieldValue, idDataGroup, false);
      pFeeScaleSysClone->setFieldNoValidate (fieldId, fieldValue, idDataGroup, false, true, false, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleSys.cpp-arc  $
// 
//    Rev 1.12   Dec 01 2011 00:18:08   popescu
// INA - Commission Work
// 
//    Rev 1.11   Nov 14 2004 14:40:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Sep 10 2004 15:51:46   FENGYONG
// PET1117 FN5 - Client Fee
// 
//    Rev 1.9   Aug 10 2004 11:24:24   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.8   Jul 21 2003 15:05:16   linmay
// PTS Ticket #10014935
// 
//    Rev 1.7   Jun 20 2003 16:28:22   linmay
// PTS#10014935
// 
//    Rev 1.6   Mar 21 2003 18:10:10   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Jan 24 2003 16:15:12   linmay
// modified doValidateFieldto validate min & max.
// 
//    Rev 1.4   Jan 22 2003 10:01:26   YINGBAOL
// change head file
// 
//    Rev 1.3   Jan 17 2003 17:52:34   linmay
// added doValidateField()
// 
//    Rev 1.2   Jan 15 2003 15:19:34   linmay
// added log comment
*/