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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : HypoRedDetail.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedDetail
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "hyporedcriteria.hpp"
#include "hyporeddetail.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0227_vw.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedDetail" );

}

namespace  CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCurrency;
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;

}

//****************************************************************************
HypoRedDetail::HypoRedDetail( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
HypoRedDetail::~HypoRedDetail()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY HypoRedDetail::init( const BFData& data, const DString& dstrTrack /*= I_("N")*/,
                         const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	//attach the summary data object
   attachDataObject( const_cast<BFData&>(data), false );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void HypoRedDetail::getField( const BFFieldId& idField,
                         DString& strFieldValue,
                         const BFDataGroupId& idDataGroup,
                         bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
   if( idField == ifds::Amount || idField == ifds::DSC && formattedReturn )
   {
      DString strCurrency;
      getParent()->getParent()->getField( ifds::FundCurrency, strCurrency, idDataGroup, false );
      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( strCurrency.strip(), strFieldValue, strFieldValue );
   }
	else if (idField == ifds::Units && formattedReturn)
	{
      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
		(const_cast<HypoRedDetail*>(this))->formatUnits(strFieldValue, idDataGroup);
	}
}

//******************************************************************************

void HypoRedDetail::formatUnits(DString& strValue, const BFDataGroupId& idDataGroup)
{
	DString dstrAmountType, dstrCurrency;
   int iUnitsPrecision = 0;

   FundDetail *pFundDetail = NULL;
	FundDetailList *pFundDetailList = NULL;
   DString dstrUnitsPrecision, dstrFundCode, dstrClassCode;
	getParent()->getParent()->getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
	getParent()->getParent()->getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
	getMgmtCo().getFundDetailList( pFundDetailList );
	assert(pFundDetailList);
   if (pFundDetailList->getFundDetail( dstrFundCode.strip().upperCase(), 
		dstrClassCode.strip().upperCase(), idDataGroup, pFundDetail ) )
   {
		pFundDetail->getField( ifds::UnitsPrecision, dstrUnitsPrecision, BF::HOST, false  );
      iUnitsPrecision = dstrUnitsPrecision.asInteger(); 
      const BFFieldId& idField = ifds::USDollar;
      DSTCommonFunctions::formattedField( idField, iUnitsPrecision, strValue ); 
   }
}
//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedDetail.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:44:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 18:14:16   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 25 2002 09:40:28   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:54   KOVACSRO
// Initial Revision
// 
 
*/


