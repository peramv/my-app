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
// ^FILE   : FeeScaleList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 24, 2002
//
// ^CLASS    : FeeScaleList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feescalelist.hpp"
#include "feescale.hpp"
#include <ifastdataimpl\dse_dstc0194_req.hpp>
#include <ifastdataimpl\dse_dstc0194_vw.hpp>
#include <ifastdataimpl\dse_dstc0195_vw.hpp>
#include <ifastdataimpl\dse_dstc0195_req.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FeeScaleList" );  
   const I_CHAR * IDISCALE = I_( "SCALE" );

}

namespace CND
{  // Conditions used
   extern const long ERR_LB_UP_OVERLAPED;
   extern const long ERR_DELETE_FEE_PARAMETER;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
FeeScaleList::FeeScaleList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),iLevel(0)

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FeeScaleList::~FeeScaleList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FeeScaleList::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );


   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeScaleList:: init(const BFData& viewData, const DString& AcctFeeParamId)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&, DString&" ) );

   DString strKey;
   int cRepeats = viewData.getRepeatCount();

   for( int i = 0; i < cRepeats; ++i )
   {
      const BFData& repeatData = viewData.getRepeat( i );
      DString dstr = repeatData.getElementValue( I_("AcctFeeParamId") );
      dstr.strip().stripLeading( I_CHAR( '0' ) );
      if( AcctFeeParamId == dstr ) // link object with AcctFeeParamId
      {
         DString strKey;
         getStrKey( strKey );
         FeeScale *pFeeScale = new FeeScale( *this );
         pFeeScale->init( repeatData );
         setObject( pFeeScale, strKey, OBJ_ACTIVITY_NONE, BF::HOST );  
         DString dstrLevel = repeatData.getElementValue( I_("Level") );
         dstrLevel.strip();
         int iTLevel = dstrLevel.asInteger();
         if( iTLevel > iLevel ) iLevel = iTLevel;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeScaleList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
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
      }   
      ++iter;
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeScaleList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new FeeScale( *this );
   ((FeeScale* )pBase)->init( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
// 
bool FeeScaleList::canDeleteObject    ( const DString&  strKey,   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );

   // logic: if it is new, or if it is just created today, delete is allowed 
   DString strProcessDate,strCurBusDate;
   getWorkSession().getDateInHostFormat(strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);  
   getParent()->getField(ifds::ProcessDate,strProcessDate,idDataGroup,false);
   BFAbstractCBO* pObj = getObject(strKey, idDataGroup);
   assert( pObj );
   if( pObj->isNew() || 
       DSTCommonFunctions::CompareDates(strCurBusDate,strProcessDate ) == DSTCommonFunctions::EQUAL )
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

//*********************************************************************************************
SEVERITY FeeScaleList::adjustLevel(DString dstrLevel,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "adjustLevel" ) );
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   int idLevel = dstrLevel.asInteger();
   DString dstrOLevel;
   while( !iter.end() )
   {
      ( dynamic_cast<FeeScale* > (iter.getObject()) )->ChangeLevel( idLevel, idDataGroup );  
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleList.cpp-arc  $
// 
//    Rev 1.13   Nov 14 2004 14:40:36   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.12   Mar 21 2003 18:10:04   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Oct 09 2002 23:54:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.10   Aug 29 2002 12:55:50   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   22 May 2002 22:23:18   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   05 Apr 2002 15:15:20   YINGBAOL
// fix
// 
//    Rev 1.7   Apr 04 2002 11:44:02   YINGBAOL
// added adjustLevel method.
// 
//    Rev 1.6   Mar 20 2002 16:04:30   YINGBAOL
// small change
// 
//    Rev 1.5   Mar 19 2002 09:51:08   YINGBAOL
// add canDeleteObject logic
// 
//    Rev 1.4   Mar 07 2002 18:21:34   YINGBAOL
// samll fix
// 
//    Rev 1.3   Feb 28 2002 12:48:42   YINGBAOL
// change error message
// 
//    Rev 1.2   Feb 27 2002 13:18:36   YINGBAOL
// take care of Level
// 
//    Rev 1.1   Feb 22 2002 14:18:44   YINGBAOL
// more function added
// 
//    Rev 1.0   Feb 01 2002 15:16:14   YINGBAOL
// Initial revision.
 * 

  */