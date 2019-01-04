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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : FeeThrshldSysList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FeeThrshldSysList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeThrshldSysList.hpp"
#include "FeeThrshldSys.hpp"
#include <ifastdataimpl\dse_dstc0231_req.hpp>
#include <ifastdataimpl\dse_dstc0231_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "feescalesys.hpp"
#include "feescalesyslist.hpp"


namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FeeThrshldSysList" );  
   const I_CHAR * IDISCALE = I_( "SCALE" );
}


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_SCALE_LIST;
}

namespace CND
{  // Conditions used
	extern const long ERR_LB_UP_OVERLAPED_THRSHLD;
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
FeeThrshldSysList::FeeThrshldSysList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
//: FeeScaleBaseList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*********************************************************************************
FeeThrshldSysList::~FeeThrshldSysList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FeeThrshldSysList:: init( const DString& dstrSysFeeParamId, bool bDefault, const DString& dstrTrack,
                             const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( DString&" ) );

	DString mgmtCoIdOut;
	bDefault_ = bDefault;
	BFData requestData(ifds::DSTC0231_REQ);  
	requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	//   requestData230->setElementValue( ifds::Track, dstrTrack );
	//   requestData230->setElementValue( ifds::Activity, dstrPageName );
	requestData.setElementValue( ifds::NextKey,     NULL_STRING );
	requestData.setElementValue( ifds::FeeID, dstrSysFeeParamId );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::FEE_PARAM_SYSTEM_SCALE_LIST, requestData, ifds::DSTC0231_VW, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
SEVERITY FeeThrshldSysList::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ));

	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void  FeeThrshldSysList::getStrKey (DString &strKey, const BFData *data)
{
//   strKey = data->getElementValue(ifds::ThrshldRangeID);

   strKey = data->getElementValue(ifds::ThrshldLevel);

   
   if(strKey != NULL_STRING)
   {
      strKey.strip();
      strKey.padLeft(9, '0');
      strKey += I_("-");
      strKey += data->getElementValue(ifds::ThrshldRangeID);
   }
}

//**********************************************************************************
SEVERITY FeeThrshldSysList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject") );

   DString dstrRecType = data.getElementValue(ifds::RecType);
   dstrRecType.strip();

   if(I_("T") == dstrRecType)
   {
      pObjOut = new FeeThrshldSys( *this );
      ((FeeThrshldSys*) pObjOut)->init( data );
   }
   else if (I_("S") == dstrRecType)
   {
      pObjOut = NULL;
      DString dstrThrshldRangeID = data.getElementValue(ifds::ThrshldRangeID);
      dstrThrshldRangeID.strip();
      
      BFObjIter iterList(*this, BF::HOST, false );
      while( !iterList.end() )
      {
			FeeThrshldSys* pFeeThrshldSys = dynamic_cast<FeeThrshldSys*>(iterList.getObject());
         if(pFeeThrshldSys)
         {
            DString dstrCurrThrshldRangeID;
            pFeeThrshldSys->getField(ifds::ThrshldRangeID, dstrCurrThrshldRangeID, BF::HOST, false);
            if(dstrCurrThrshldRangeID == dstrThrshldRangeID)
            {
               FeeScaleSysList* pFeeScaleSysList = NULL; 
               FeeScaleBaseList* pFeeScaleBaseList = NULL;
               pFeeThrshldSys->getFeeScaleSysList(pFeeScaleBaseList, BF::HOST, true);
               if(pFeeScaleBaseList != NULL)
               {
                  pFeeScaleSysList = dynamic_cast<FeeScaleSysList*> (pFeeScaleBaseList);
                  FeeScaleSys* pFeeScaleSys = new FeeScaleSys( *pFeeScaleSysList);
                  pFeeScaleSys->init( data );
                  DString strKey;
                  pFeeScaleSysList->getStrKey (strKey, &data);
                  pFeeScaleSysList->setObject(strKey, pFeeScaleSys);
               }
            }
         }
         ++iterList;
      }
   //   FeeThrshldSys* pFeeThrshldSys = dynamic_cast<FeeThrshldSys*>(getObject(dstrThrshldRangeID, BF::HOST));
   //   if(pFeeThrshldSys != NULL)
   //   {
   //      FeeScaleSysList* pFeeScaleSysList = NULL;
   //      FeeScaleBaseList* pFeeScaleBaseList = NULL;
   //      pFeeThrshldSys->getFeeScaleSysList(pFeeScaleBaseList, BF::HOST, true);
   //      if(pFeeScaleBaseList != NULL)
   //      {
   //         pFeeScaleSysList = dynamic_cast<FeeScaleSysList*> (pFeeScaleBaseList);
   //         FeeScaleSys* pFeeScaleSys = new FeeScaleSys( *pFeeScaleSysList);
   //         pFeeScaleSys->init( data );
   //         DString strKey;
   //         pFeeScaleSysList->getStrKey (strKey, &data);
   //         pFeeScaleSysList->setObject(strKey, pFeeScaleSys);
   //      }
   //   }
   }

	return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************

SEVERITY FeeThrshldSysList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject") );
   pBase =  new FeeThrshldSys( *this );
   ((FeeThrshldSys*) pBase)->init( idDataGroup );


	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FeeThrshldSysList::AddNewFeeScale( FeeScaleBaseList *pFeeScaleList, const DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "AddNewFeeScale" ) );

   BFObjIter iterScale(*pFeeScaleList,BF::HOST,false,BFObjIter::ITERTYPE::NON_DELETED );
   
   while( !iterScale.end() )
  {
	   BFCBO* pCBO = dynamic_cast<BFCBO *>(iterScale.getObject());

	   BFObjectKey objKey( strKey, idDataGroup );

	   FeeThrshldSys *pFeeThrshldSys = dynamic_cast<FeeThrshldSys*>(getNewListItem( objKey ));

	   pFeeThrshldSys->setValueFromDefault(pCBO, idDataGroup );

       ++ iterScale;

  }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeThrshldSysList::clone(const BFDataGroupId& idDataGroup, FeeThrshldSysList*& pFeeThrshldSysListClone)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clone" ) );

   pFeeThrshldSysListClone = new FeeThrshldSysList((BFAbstractCBO&)(*this));

   BFObjIter iter(*this,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      FeeThrshldSys* pFeeThrshldSys = dynamic_cast<FeeThrshldSys*>(iter.getObject());
      if(pFeeThrshldSys)
      {
         FeeThrshldSys* pFeeThrshldSysClone = NULL;
         pFeeThrshldSys->clone(idDataGroup, pFeeThrshldSysClone);
         if(pFeeThrshldSysClone)
         {
            BFObjectKey objKey(iter.getKey().getStringKey(), idDataGroup, OBJ_ACTIVITY_ADDED);
            pFeeThrshldSysListClone->setObject(objKey, pFeeThrshldSysClone);
            pFeeThrshldSysListClone->setFieldUpdated(ifds::Level, idDataGroup, true);
         }
      }
      ++iter;
   }

   return(GETCURRENTHIGHESTSEVERITY());
};

//*********************************************************************************
SEVERITY FeeThrshldSysList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString strLowBound1, strLowBound2,dstrUpBound1,dstrUpBound2,dstrLevel1,dstrLevel2;
   double dLB1,dUB1,dLB2,dUB2;
   while( !iter.end() )
   {
      (iter.getObject() )->getField(ifds::ThrshldUpper, dstrUpBound1, idDataGroup,true);
      (iter.getObject() )->getField(ifds::ThrshldLower, strLowBound1, idDataGroup,true);
      (iter.getObject() )->getField(ifds::ThrshldLevel, dstrLevel1, idDataGroup,true);
      dUB1 = DSTCommonFunctions::convertToDouble( dstrUpBound1 );
      dLB1 = DSTCommonFunctions::convertToDouble( strLowBound1 );    
      iter1.positionByKey( iter.getStringKey() );
      ++iter1;
      for( iter1; !iter1.end(); ++iter1 )
      {
         (iter1.getObject() )->getField(ifds::ThrshldUpper, dstrUpBound2, idDataGroup,true);
         (iter1.getObject() )->getField(ifds::ThrshldLower, strLowBound2, idDataGroup,true);
         (iter1.getObject() )->getField(ifds::ThrshldLevel, dstrLevel2, idDataGroup,true);

         dUB2 = DSTCommonFunctions::convertToDouble( dstrUpBound2 );
         dLB2 = DSTCommonFunctions::convertToDouble( strLowBound2 );   
         if( dLB2 <= dLB1 &&  dUB2 > dLB1 || dLB2 < dUB1 && dUB2 >= dUB1 ||
             dLB1 <= dLB2 &&  dUB1 > dLB2 || dLB1 < dUB2 && dUB1 >= dUB2 )
         {
            DString strTemp;                 
            addIDITagValue( strTemp, I_("THRSHLD"), dstrLevel1 +I_(" ") + dstrLevel2 );          
            ADDCONDITIONFROMFILEIDI( CND::ERR_LB_UP_OVERLAPED_THRSHLD, strTemp);
            return(GETCURRENTHIGHESTSEVERITY());     
         }
      }   
      ++iter;
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

