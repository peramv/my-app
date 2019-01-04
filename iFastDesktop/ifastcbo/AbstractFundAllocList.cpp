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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AbstractFundAllocList.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : Nov. 13, 2002
//
// ^CLASS    : AbstractFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Abstract Fund Allocation List
//
//******************************************************************************

#include "stdafx.h"
#include "AbstractFundAlloc.hpp"
#include "AbstractFundAllocList.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AbstractFundAllocList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
	const double dSmallValue       = .0000000001;

}

namespace CND
{
      extern const long ERR_NO_ALLOCATION_SETUP;
      extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
      extern const long ERR_IDENTICAL_FUND_ALLOCS;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFDecimalFieldId	AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId		FundCode;
   extern CLASS_IMPORT const BFTextFieldId		ClassCode;
}
//******************************************************************************
AbstractFundAllocList::AbstractFundAllocList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
}

//******************************************************************************
AbstractFundAllocList::~AbstractFundAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************
SEVERITY AbstractFundAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

	if( bOneItemMustExit() )
	{

		BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
		int  iNum = iter.getNumberOfItemsInList();
		if( !iNum )
		{
			ADDCONDITIONFROMFILE( CND::ERR_NO_ALLOCATION_SETUP );
			return(GETCURRENTHIGHESTSEVERITY());
		}
		else
		{
			bool bAllDummy = true;
			while( !iter.end() )
			{
				if( !iter.isDummy() )
				{
					bAllDummy=false;
					break;
				}
				++iter;
			}
			if( bAllDummy )
				{
				ADDCONDITIONFROMFILE( CND::ERR_NO_ALLOCATION_SETUP );
				return(GETCURRENTHIGHESTSEVERITY());
				}
		}
	}
   std::set< DString > setCharacteristic;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strAllocFundCode, strAllocClassCode;
      iter.getObject()->getField(ifds::FundCode, strAllocFundCode, idDataGroup, false);
      iter.getObject()->getField(ifds::ClassCode, strAllocClassCode, idDataGroup, false);
      DString strNewEntry = strAllocFundCode.strip().upperCase() + strAllocClassCode.strip().upperCase();

      if( !setCharacteristic.insert( strNewEntry ).second )
      {
         ADDCONDITIONFROMFILE( CND::ERR_IDENTICAL_FUND_ALLOCS );
         break;
      }
      ++iter; 
   }
   double dTotalPercent = getTotalPercentage( idDataGroup );
   if( fabs( dTotalPercent - 100 ) > dSmallValue )
      ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );
	return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
double AbstractFundAllocList::getTotalPercentage(const BFDataGroupId& idDataGroup)
{
 
   double dTotalValue = 0.0;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strAllocValue;
		iter.getObject()->getField( ifds::AllocPercentage, strAllocValue, idDataGroup, false );
		double dAllocValue = DSTCommonFunctions::convertToDouble( strAllocValue.strip() );

		dTotalValue += dAllocValue;
      ++iter; 
   }
	return dTotalValue;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AbstractFundAllocList.cpp-arc  $
// 
//    Rev 1.3   Mar 21 2003 17:53:42   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Nov 27 2002 11:40:06   YINGBAOL
// check FundCode Class Code to see if it is already in the list
// 
//    Rev 1.1   Nov 19 2002 13:26:14   YINGBAOL
// fix
// 
//    Rev 1.0   Nov 13 2002 10:00:42   YINGBAOL
// Initial Revision

 * 
 * 
 */