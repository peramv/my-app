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
// ^FILE   : FeeScaleBase.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 08, 2002
//
// ^CLASS    : FeeScaleBase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feescaleBase.hpp"
#include "feescaleBaselist.hpp"
#include "feeparamBase.hpp"
#include <bfcbo\bfobjiter.hpp>
#include "mgmtco.hpp"
//#include "mgmtcooptions.hpp"
#include "fundfeelist.hpp"
#include "FeeParamSys.hpp"
#include "FeeParamConfig.hpp"
#include "FeeParamConfigList.hpp"

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_UPBOUND_LESS_THAN_LOWER_BOUND;
   extern const long ERR_SCALE_RATE_TOO_LARGE;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_RATE_IS_OUT_OF_RANGE;
   extern const long ERR_MAX_LESS_THAN_MIN;
   extern const long ERR_RATE_LESS_THAN_MIN;
   extern const long ERR_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN;
   extern const long WARN_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN;
}

namespace  
{
   const I_CHAR * const CLASSNAME         = I_( "FeeScaleBase" );
   const I_CHAR * const IDI_RATE          = I_("RATE");
   const I_CHAR * const IDI_GRADE         = I_("GRADE");
   const I_CHAR * const IDI_MIN_RATE		= I_("MINRATE");
   const I_CHAR * const IDI_MAX_RATE		= I_("MAXRATE");
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ScaleRate;
   extern CLASS_IMPORT const BFDecimalFieldId UpperBound;
   extern CLASS_IMPORT const BFDecimalFieldId LowerBound;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFDateFieldId ScaleEffectiveDate;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
}

namespace IFASTERR
{
    extern CLASS_IMPORT I_CHAR * const THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN;
}


//************************************************************************************
FeeScaleBase::FeeScaleBase( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
 
}
//************************************************************************************
FeeScaleBase::~FeeScaleBase()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//*************************************************************************************************
SEVERITY FeeScaleBase::ChangeLevel( const int idLevel,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ChangeLevel" ) );
   DString  dstrOLevel;      
   getField(ifds::Level, dstrOLevel, idDataGroup,true);
   int  iLevel = dstrOLevel.asInteger();
   if( iLevel > idLevel )
   {
      setFieldNoValidate(ifds::Level,DString::asString( --iLevel ), idDataGroup,true,true,true); 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY FeeScaleBase::validateScaleRate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateScaleRate" ) );

   DString dstrRateScale;
   getField(ifds::ScaleRate,dstrRateScale,idDataGroup );
   double dRate =  DSTCommonFunctions::convertToDouble( dstrRateScale );
   if( dRate < 0.0 || dRate > 100.0 )
   {

      ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
   }
   DString _dstrMinFee = NULL_STRING;
   DString _dstrMaxFee = NULL_STRING;
   // find the default record

   FeeParamSys *pFeeParamSysDef = NULL;

   
   FeeScaleBaseList* pFeeScaleBaseList = dynamic_cast<FeeScaleBaseList*>(getParent());
   pFeeScaleBaseList->getFeeParamBase()-> getFeeParamSysDef(pFeeParamSysDef, idDataGroup );

   if( pFeeParamSysDef )
   {   
	   DString dstrFeeType, dstrFeeTypeDef;
	   pFeeScaleBaseList->getFeeParamBase()->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup);
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


   DString dstrScaleRate;
   double dScaleRate;

   getField(ifds::ScaleRate,dstrScaleRate,idDataGroup );
   dScaleRate =  DSTCommonFunctions::convertToDouble( dstrScaleRate );

   if (!_dstrMinFee.empty() && !_dstrMaxFee.empty()) //Defalut value exists.
   {
       double dScaleMax, dScaleMin;

       dScaleMax =  DSTCommonFunctions::convertToDouble( _dstrMaxFee );
       dScaleMin =  DSTCommonFunctions::convertToDouble( _dstrMinFee );

       if ( dScaleMax == 0 && dScaleMin >0 )
       {
           if ( dScaleRate < dScaleMin )
           {
               DString dstrIDI;
               DSTCommonFunctions::DisplayFormat( _dstrMinFee, ifds::MinFee );
               addIDITagValue( dstrIDI, IDI_MIN_RATE, _dstrMinFee );
               ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_LESS_THAN_MIN, dstrIDI ); 
           }

       }
       else if (dScaleRate < dScaleMin || dScaleRate > dScaleMax)
       {
           DString dstrIDI;
           DSTCommonFunctions::DisplayFormat( _dstrMinFee, ifds::MinFee );
           DSTCommonFunctions::DisplayFormat( _dstrMaxFee, ifds::MaxFee );
           addIDITagValue( dstrIDI, IDI_MIN_RATE, _dstrMinFee );
           addIDITagValue( dstrIDI, IDI_MAX_RATE, _dstrMaxFee );

           ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_IS_OUT_OF_RANGE, dstrIDI ); 
       }
   }

    
    FeeParamConfigList *pFeeParamConfigList = NULL;
    FeeParamConfig* pFeeParamConfig = NULL;
    DString dstrFeeCode;

    getParent()->getParent()->getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);

    if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING && pFeeParamConfigList &&
        pFeeParamConfigList->getFeeParamConfig(pFeeParamConfig, dstrFeeCode, idDataGroup) <= WARNING && pFeeParamConfig)
    {
        DString dstrFeeConfigMaxFee;
        double dFeeConfigMaxFee;

        pFeeParamConfig->getField(ifds::MaxFee, dstrFeeConfigMaxFee, idDataGroup, false);
        dFeeConfigMaxFee = DSTCommonFunctions::convertToDouble(dstrFeeConfigMaxFee);

        if (dFeeConfigMaxFee != 0.0 && dScaleRate > dFeeConfigMaxFee)
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

/*
   FundFeeList* pFundFeeList = NULL;
   SEVERITY sev = getMgmtCo().getFundFeeList( pFundFeeList );
   if( sev <= WARNING && pFundFeeList )
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
            DString dstrFundRate,dstrScaleRate;
            double dFundRate,dScaleRate;
            getField(ifds::ScaleRate,dstrScaleRate,idDataGroup );
            iterFundFee.getObject()->getField(ifds::ScaleRate,dstrFundRate,idDataGroup );
            dFundRate =  DSTCommonFunctions::convertToDouble( dstrFundRate );
            dScaleRate =  DSTCommonFunctions::convertToDouble( dstrScaleRate );              
            if( dScaleRate > dFundRate )
            {
               DString dstrIDI;
               addIDITagValue(dstrIDI, IDI_GRADE, dstrLevel);
               addIDITagValue(dstrIDI, IDI_RATE, dstrFundRate);
               ADDCONDITIONFROMFILEIDI( CND::ERR_SCALE_RATE_TOO_LARGE, dstrIDI );                  
            }

			DString dstrScaleMax, dstrScaleMin;
			double dScaleMax, dScaleMin;
			iterFundFee.getObject()->getField(ifds::MaxFee,dstrScaleMax,idDataGroup );
			iterFundFee.getObject()->getField(ifds::MinFee,dstrScaleMin,idDataGroup );
			dScaleMax =  DSTCommonFunctions::convertToDouble( dstrScaleMax );
			dScaleMin =  DSTCommonFunctions::convertToDouble( dstrScaleMin );
			if (dScaleRate < dScaleMin || dScaleRate > dScaleMax)
			{
				DString dstrIDIRate;
				addIDITagValue(dstrIDIRate, IDI_RATE, dstrRateScale);
				ADDCONDITIONFROMFILEIDI( CND::ERR_RATE_IS_OUT_OF_RANGE, dstrIDIRate ); 
			}

            break;
         }
         ++iterFundFee;
      }                             
   }
	*/
   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
SEVERITY FeeScaleBase::validateLUBound(const BFDataGroupId& idDataGroup )

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
void FeeScaleBase::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{

   DString strValue;
   //getWorkSession().getDateInHostFormat(strValue, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY,idDataGroup );
  // effectiv date should took from FeeParamSys
   FeeScaleBaseList* pFeeScaleBaseList = dynamic_cast<FeeScaleBaseList*>(getParent());
	pFeeScaleBaseList->getFeeParamBase()->getField( ifds::EffectiveDate,strValue,idDataGroup,false );
	
	
	setFieldNoValidate( ifds::ScaleEffectiveDate, strValue, idDataGroup , false );
   strValue = pFeeScaleBaseList->getNextLevel();
   setFieldNoValidate(ifds::Level,strValue,idDataGroup );
   setFieldNoValidate(ifds::ScaleRate,I_("0.0"),idDataGroup );
}

//*****************************************************************************
SEVERITY FeeScaleBase::validateMinMax(const BFDataGroupId& idDataGroup )

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
SEVERITY FeeScaleBase::validateMaxFee(const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMaxFee" ) );

   FeeParamConfigList *pFeeParamConfigList = NULL;
   FeeParamConfig* pFeeParamConfig = NULL;
   DString dstrFeeCode, dstrMaxFee;
   double dMaxFee;

   getField(ifds::MaxFee,dstrMaxFee,idDataGroup);
   dMaxFee = DSTCommonFunctions::convertToDouble(dstrMaxFee);

   getParent()->getParent()->getField(ifds::FeeCode, dstrFeeCode, idDataGroup, false);

   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING && pFeeParamConfigList &&
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

   return GETCURRENTHIGHESTSEVERITY();
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleBase.cpp-arc  $
// 
//    Rev 1.10   Jul 11 2005 17:23:02   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.9   Nov 14 2004 14:40:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Aug 10 2004 11:24:20   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.7   Oct 15 2003 16:49:40   YINGBAOL
// PTS10019803 EffectiveDate Changes
// 
//    Rev 1.6   Mar 21 2003 18:09:54   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Jan 24 2003 16:17:28   linmay
// added validateMinMax(const BFDataGroupId& idDataGroup );
// 
//    Rev 1.4   Jan 22 2003 09:53:54   YINGBAOL
// do not validate against FundFeeList
// 
//    Rev 1.3   Jan 17 2003 17:54:06   linmay
// added changelevel()
// 
//    Rev 1.2   Jan 15 2003 15:20:30   linmay
// added log comment
*/