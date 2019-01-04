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
// ^FILE   : FeeScaleBaseList.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 08, 2003
//
// ^CLASS    : FeeScaleBaseList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feescalebaselist.hpp"
#include "feescalebase.hpp"
#include "feeparambase.hpp"
//#include "mgmtco.hpp"
//#include "mgmtcooptions.hpp"
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_warn_includes.h>

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FeeScaleBaseList" );  
   const I_CHAR * IDISCALE = I_( "SCALE" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId UpperBound;
   extern CLASS_IMPORT const BFDecimalFieldId LowerBound;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFDecimalFieldId Level;

}



namespace CND
{  // Conditions used
   extern const long ERR_LB_UP_OVERLAPED;
   extern const long ERR_DELETE_FEE_PARAMETER;
   CIFast_IFast_ifastcbo_err_gap_between_fee_scales;
   CIFast_IFast_ifastcbo_warn_gap_between_fee_scales;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const GAP_BETWEEN_FEE_SCALES;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
FeeScaleBaseList::FeeScaleBaseList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),iLevel(0),m_pFeeParamBase(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FeeScaleBaseList::~FeeScaleBaseList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//*********************************************************************************************
SEVERITY FeeScaleBaseList::adjustLevel(DString dstrLevel,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "adjustLevel" ) );
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   int idLevel = dstrLevel.asInteger();
   DString dstrOLevel;
   while( !iter.end() )
   {
      ( dynamic_cast<FeeScaleBase* > (iter.getObject()) )->ChangeLevel( idLevel, idDataGroup );  
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeScaleBaseList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString strLowBound1, strLowBound2,dstrUpBound1,dstrUpBound2,dstrLevel1,dstrLevel2;
   double dLB1,dUB1,dLB2,dUB2;
   while( !iter.end() )
   {
      (iter.getObject() )->getField(ifds::UpperBound, dstrUpBound1, idDataGroup,true);
      (iter.getObject() )->getField(ifds::LowerBound, strLowBound1, idDataGroup,true);
      (iter.getObject() )->getField(ifds::Level, dstrLevel1, idDataGroup,true);
      dUB1 = DSTCommonFunctions::convertToDouble( dstrUpBound1 );
      dLB1 = DSTCommonFunctions::convertToDouble( strLowBound1 );    
      iter1.positionByKey( iter.getStringKey() );
      ++iter1;
      for( iter1; !iter1.end(); ++iter1 )
      {
         (iter1.getObject() )->getField(ifds::UpperBound, dstrUpBound2, idDataGroup,true);
         (iter1.getObject() )->getField(ifds::LowerBound, strLowBound2, idDataGroup,true);
         (iter1.getObject() )->getField(ifds::Level, dstrLevel2, idDataGroup,true);

         dUB2 = DSTCommonFunctions::convertToDouble( dstrUpBound2 );
         dLB2 = DSTCommonFunctions::convertToDouble( strLowBound2 );   
         if( dLB2 <= dLB1 &&  dUB2 > dLB1 || dLB2 < dUB1 && dUB2 >= dUB1 ||
             dLB1 <= dLB2 &&  dUB1 > dLB2 || dLB1 < dUB2 && dUB1 >= dUB2 )
         {
            DString strTemp;                 
            addIDITagValue( strTemp, IDISCALE, dstrLevel1 +I_(" ") + dstrLevel2 );          
            ADDCONDITIONFROMFILEIDI( CND::ERR_LB_UP_OVERLAPED, strTemp);
            return(GETCURRENTHIGHESTSEVERITY());     
         }
		double dL1 = DSTCommonFunctions::convertToDouble( dstrLevel1 );
		double dL2 = DSTCommonFunctions::convertToDouble( dstrLevel2 );
		/*Get the positive result as we need to know if we are comparing two consecutive lists or not.
		  When the result is 1, it means we are comparing with the next entry in the list.*/
		unsigned int uLevelGap = (dL2 - dL1 ) * (dL2 - dL1 ); 
 		if(( dLB1 > dLB2 && dLB1 != dUB2 || dLB1 < dLB2 && dUB1 != dLB2 ) && (uLevelGap == 1))
         {
            DString strTemp;                 
            addIDITagValue( strTemp, IDISCALE, dstrLevel1 +I_(" ") + dstrLevel2 );      
			CND::CIFast_IFast_ifastcbo_err_gap_between_fee_scales ERR_GAP_BETWEEN_FEE_SCALES;
            CND::CIFast_IFast_ifastcbo_warn_gap_between_fee_scales WARN_GAP_BETWEEN_FEE_SCALES;
			getErrMsg (IFASTERR::GAP_BETWEEN_FEE_SCALES, 
								ERR_GAP_BETWEEN_FEE_SCALES, 
								WARN_GAP_BETWEEN_FEE_SCALES, 
								idDataGroup,strTemp);
            return(GETCURRENTHIGHESTSEVERITY());     
         } 
      }   
      ++iter;
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
// 
bool FeeScaleBaseList::canDeleteObject( const DString&  strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );

   // logic: if it is new, or if it is just created today, delete is allowed 
   DString strProcessDate,strCurBusDate;
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);  
   getFeeParamBase()->getField(ifds::ProcessDate,strProcessDate,idDataGroup,false);
   BFAbstractCBO* pObj = getObject(strKey, idDataGroup);
   assert( pObj );

   FeeParamBase* pFeeParamBase = getFeeParamBase();
   bool canUpdateObject = false;
   if(pFeeParamBase)
   {
      canUpdateObject = pFeeParamBase->canUpdateObject(idDataGroup);
   }

   if( pObj->isNew() || canUpdateObject)
   {
      DString dstrLevel;
      pObj->getField( ifds::Level, dstrLevel, idDataGroup, true );
      adjustLevel( dstrLevel, idDataGroup ); 
      if( iLevel >= 1 ) --iLevel;
      return(true);
   }
   ADDCONDITIONFROMFILE( CND::ERR_DELETE_FEE_PARAMETER );
   return(false);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleBaseList.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:40:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 18:10:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Jan 31 2003 11:20:44   YINGBAOL
// init iLevel
// 
//    Rev 1.3   Jan 17 2003 17:53:26   linmay
// added getNextLevel()
// 
//    Rev 1.2   Jan 15 2003 15:20:00   linmay
// added log comment
*/