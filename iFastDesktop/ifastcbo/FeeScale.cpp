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
// ^FILE   : FeeScale.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 24, 2002
//
// ^CLASS    : FeeScale
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feescale.hpp"
#include "feescalelist.hpp"
#include "feeparam.hpp"
#include <bfcbo\bfobjiter.hpp>
#include "fundfeelist.hpp"
#include <ifastdataimpl\dse_dstc0194_vw.hpp>
#include <ifastdataimpl\dse_dstc0194_req.hpp>
#include <ifastdataimpl\dse_dstc0195_vw.hpp>
#include <ifastdataimpl\dse_dstc0197_vw.hpp>

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_UPBOUND_LESS_THAN_LOWER_BOUND;
   extern const long ERR_SCALE_RATE_TOO_LARGE;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_RATE_IS_OUT_OF_RANGE;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "FeeScale" );
   const I_CHAR * const IDI_RATE          = I_("RATE");
   const I_CHAR * const IDI_GRADE         = I_("GRADE");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit1;
}


//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::AcctFeeParamId,  BFCBO::NONE, 0 }, 
   { ifds::ScaleRate,       BFCBO::NONE, 0 }, 
   { ifds::UpperBound,      BFCBO::NONE, 0 }, 
   { ifds::LowerBound,      BFCBO::NONE, 0 }, 
   { ifds::FeeCode,         BFCBO::NONE, 0 }, 
   { ifds::Level,           BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate,   BFCBO::NONE, 0 }, 
   { ifds::FieldCrossEdit1, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FeeScale::FeeScale( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, localData(0)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit(ifds::FieldCrossEdit1, ifds::LowerBound);
   addCrossEdit(ifds::FieldCrossEdit1, ifds::UpperBound);
}
//------------------------------------------------------------------------
FeeScale::~FeeScale()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete localData;
}     
//---------------------------------------------------------------------  
SEVERITY FeeScale::doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   SEVERITY  svrn = NO_CONDITION;
   if( idField == ifds::FieldCrossEdit1 )
      validateLUBound(  idDataGroup );
   else if( idField == ifds::ScaleRate )
      validateScaleRate( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
SEVERITY FeeScale::validateLUBound(const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateLUBound" ) );
   DString strValue;
   double dUpBound,dLowBound;
   getField(ifds::LowerBound,strValue,idDataGroup,false);
   dLowBound = DSTCommonFunctions::convertToDouble( strValue );
   getField(ifds::UpperBound,strValue,idDataGroup,false);
   dUpBound = DSTCommonFunctions::convertToDouble( strValue );
   if( dUpBound < dLowBound )
   {
      ADDCONDITIONFROMFILE( CND::ERR_UPBOUND_LESS_THAN_LOWER_BOUND );   
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//------------------------------------------------------------------------------------
SEVERITY FeeScale::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData& )" ) );
   localData = new BFData(InstData);
   attachDataObject( const_cast<BFData&>(*localData), false, true );
   bool bReadOnly = !(dynamic_cast<FeeParam* >(getParent()->getParent() )->isTheSameBusinessDate(BF::HOST) );  
   setFieldReadOnly(ifds::ScaleRate,BF::HOST,bReadOnly);
   setFieldReadOnly(ifds::UpperBound,BF::HOST,bReadOnly);   
   setFieldReadOnly(ifds::LowerBound,BF::HOST,bReadOnly);   
   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************
SEVERITY FeeScale::init(const BFDataGroupId& idDataGroup ) // init new
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long )" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}


//---------------------------------------------------------------------------
void FeeScale::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{

   DString strValue;
  // getWorkSession().getDateInHostFormat(strValue, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY,idDataGroup );
	getParent()->getParent()->getField( ifds::EffectiveDate,strValue,idDataGroup,false );
	
	setFieldNoValidate( ifds::EffectiveDate, strValue, idDataGroup , false );
   strValue = dynamic_cast<FeeScaleList* >(getParent() )->getNextLevel();
   setFieldNoValidate(ifds::Level,strValue,idDataGroup );
   setFieldNoValidate(ifds::ScaleRate,I_("0.0"),idDataGroup );
}

//************************************************************************************
SEVERITY FeeScale::validateScaleRate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateScaleRate" ) );

   DString dstrRateScale;
   getField(ifds::ScaleRate,dstrRateScale,idDataGroup );
   double dRate =  DSTCommonFunctions::convertToDouble( dstrRateScale );
   if( dRate < 0.0 || dRate > 100.0 )
   {

      ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
   }


   FundFeeList* pFundFeeList = NULL;
   dynamic_cast<FeeParam* >(getParent()->getParent() ) -> getFundFeeList(pFundFeeList);

   if ( !pFundFeeList ) {
      FeeParam *pFeeParam = dynamic_cast <FeeParam*>(getParent()->getParent());
      pFeeParam->refreshFundFeeList ( idDataGroup);
      pFeeParam->getFundFeeList(pFundFeeList);     
   }

   if( pFundFeeList != NULL )
   {
      BFObjIter iterFundFee(*pFundFeeList,idDataGroup);
      DString dstrScaleUp,dstrScaleLow,dstrFundUp,dstrFundLow,dstrLevel;   
      double dScaleUp,dScaleLow,dFundUp,dFundLow;
      getField(ifds::LowerBound,dstrScaleLow,idDataGroup );
      getField(ifds::UpperBound,dstrScaleUp,idDataGroup );
      dScaleUp =  DSTCommonFunctions::convertToDouble( dstrScaleUp );
      dScaleLow =  DSTCommonFunctions::convertToDouble( dstrScaleLow );
      iterFundFee.begin();
      while( !iterFundFee.end() )
      {
         BFAbstractCBO* pObj =iterFundFee.getObject();
         if( pObj )
         {
            pObj->getField(ifds::LowerBound,dstrFundLow,idDataGroup );
            pObj->getField(ifds::UpperBound,dstrFundUp,idDataGroup );
            pObj->getField(ifds::Level,dstrLevel,idDataGroup );
         }
         dFundUp =  DSTCommonFunctions::convertToDouble( dstrFundUp );
         dFundLow =  DSTCommonFunctions::convertToDouble( dstrFundLow );
         if( abs(dScaleUp - dFundUp) < 0.01 && abs( dScaleLow - dFundLow ) < 0.01 )
         {
   /*         DString dstrFundRate,dstrScaleRate;
            double dFundRate,dScaleRate;
            getField(ifds::ScaleRate,dstrScaleRate,lDataGroupId );
            iterFundFee.getObject()->getField(ifds::ScaleRate,dstrFundRate,lDataGroupId );
            dFundRate =  DSTCommonFunctions::convertToDouble( dstrFundRate );
            dScaleRate =  DSTCommonFunctions::convertToDouble( dstrScaleRate );              
            if( dScaleRate > dFundRate )
            {
               DString dstrIDI;
               addIDITagValue(dstrIDI, IDI_GRADE, dstrLevel);
               addIDITagValue(dstrIDI, IDI_RATE, dstrFundRate);
               ADDCONDITIONFROMFILEIDI( CND::ERR_SCALE_RATE_TOO_LARGE, dstrIDI );                  
            }
*/
				DString dstrScaleMax, dstrScaleMin,dstrScaleRate;
				double dScaleMax, dScaleMin,dScaleRate;

				getField(ifds::ScaleRate,dstrScaleRate,idDataGroup );
            dScaleRate =  DSTCommonFunctions::convertToDouble( dstrScaleRate );              
				iterFundFee.getObject()->getField(ifds::ScaleMaxFee,dstrScaleMax,idDataGroup );
				iterFundFee.getObject()->getField(ifds::ScaleMinFee,dstrScaleMin,idDataGroup );
				dScaleMax =  DSTCommonFunctions::convertToDouble( dstrScaleMax );
				dScaleMin =  DSTCommonFunctions::convertToDouble( dstrScaleMin );
				if (dScaleRate < dScaleMin || dScaleRate > dScaleMax)
				{
					DString dstrIDIRate;
					DSTCommonFunctions::DisplayFormat( dstrScaleMin, ifds::ScaleMinFee );
					DSTCommonFunctions::DisplayFormat( dstrScaleMax, ifds::ScaleMaxFee );
					addIDITagValue(dstrIDIRate, I_("MINRATE"), dstrScaleMin);
					addIDITagValue(dstrIDIRate, I_("MAXRATE"), dstrScaleMax);
					ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_IS_OUT_OF_RANGE, dstrIDIRate ); 
					break;
				}
			}      
         ++iterFundFee;
      }                             
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//************************************************************************************************
SEVERITY FeeScale::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( idField == ifds::LowerBound  || idField == ifds::UpperBound )
   {
      setValidFlag(ifds::ScaleRate, idDataGroup, false); 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************************
SEVERITY FeeScale::ChangeLevel( const int idLevel,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ChangeLevel" ) );
   DString  dstrOLevel;      
   getField(ifds::Level, dstrOLevel, idDataGroup,true);
   int  iLevel = dstrOLevel.asInteger();
   if( iLevel > idLevel )
   {
      setFieldNoValidate(ifds::Level,DString::asString( --iLevel ), idDataGroup,true,true,true); 
      /*if( !isNew()  ) 
         // if it is not new, iLevel has to be set to the host
         setFieldNoValidate(DBR::Level,DString::asString( --iLevel ), BF::HOST ); */
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScale.cpp-arc  $
// 
//    Rev 1.17   Jul 11 2005 17:22:56   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.16   Nov 14 2004 14:40:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.15   Oct 15 2003 16:48:50   YINGBAOL
// PTS10019803 EffectiveDateChanges
// 
//    Rev 1.14   May 13 2003 08:49:32   sanchez
// Sync up with v.1.11.1.1 PTS# 10016338
// 
//    Rev 1.13   Apr 28 2003 10:01:16   YINGBAOL
// PTS10016338 sync. up Version 1.11.1.0
// 
//    Rev 1.12   Mar 21 2003 18:09:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Jan 02 2003 15:23:52   linmay
// modified validateScaleRate()
// 
//    Rev 1.10   Oct 09 2002 23:54:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.9   Aug 29 2002 12:55:50   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.8   22 May 2002 18:28:38   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   05 Apr 2002 15:15:20   YINGBAOL
// fix
// 
//    Rev 1.6   Mar 08 2002 10:11:00   YINGBAOL
// Add condition ERR_VALUE_BETWEEN_0_AND_100 
// 
//    Rev 1.5   Mar 07 2002 18:20:52   YINGBAOL
// code clearance
// 
//    Rev 1.4   Mar 05 2002 14:08:06   YINGBAOL
// add validateScaleRate logic
// 
//    Rev 1.3   Feb 28 2002 12:48:06   YINGBAOL
// add more validation
// 
//    Rev 1.2   Feb 27 2002 13:18:12   YINGBAOL
// take care of Level
// 
//    Rev 1.1   Feb 22 2002 14:18:44   YINGBAOL
// more function added
// 
//    Rev 1.0   Feb 01 2002 15:16:14   YINGBAOL
// Initial revision.
 * 

  */