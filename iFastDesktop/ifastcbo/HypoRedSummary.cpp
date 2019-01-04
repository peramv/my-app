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
// ^FILE   : HypoRedSummary.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedSummary
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "hyporeddetaillist.hpp"
#include "hyporedsummary.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0217_vw.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedSummary" );
   const I_CHAR * const RED_DETAIL_LIST      = I_( "RedDetailList" );

}

namespace  CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

namespace ifds
{
	extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
}

//~the following code is here to fix a base bug (they round Units field to 4 decimals
   //and FreeUnits to 3 decimals, therefore they might get small negative values
   //for ApplicableUnits when actually the real value should be zero
   //same problem for FreeAmount
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,                                    State Flags,       Group Flags 
   
   { ifds::ApplicableUnits, BFCBO::NONE,       0 }, 
   { ifds::ApplicableAmt,   BFCBO::NONE,       0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//~end for character base bug fix

//****************************************************************************
HypoRedSummary::HypoRedSummary( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   //~the following code is here to fix an ifast bug (they round Units field to 4 decimals
   //and FreeUnits to 3 decimals, therefore they might get small negative values
   //for ApplicableUnits when actually the real value should be zero
   //same problem for FreeAmount
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   //~end for character base bug fix
}

//****************************************************************************
HypoRedSummary::~HypoRedSummary()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY HypoRedSummary::init( const BFData& summaryData, const BFData& allDetailsData,
										const DString& dstrTrack /*= I_("N")*/,
										const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	//attach the summary data object
   attachDataObject( const_cast<BFData&>(summaryData), false );

	//create the details list for each summary
	DString strFundCode, strClassCode;
	getField(ifds::FundCode, strFundCode, BF::HOST, false);
	getField(ifds::ClassCode, strClassCode, BF::HOST, false);
	HypoRedDetailList *pHypoRedDetailList = new HypoRedDetailList( *this );
   pHypoRedDetailList->init(strFundCode.strip(), strClassCode.strip(), allDetailsData);
   setObject( pHypoRedDetailList, RED_DETAIL_LIST, OBJ_ACTIVITY_NONE, BF::HOST );

   //~the following code is here to fix an ifast bug (they round Units field to 4 decimals
   //and FreeUnits to 3 decimals, therefore they might get small negative values
   //for ApplicableUnits when actually the real value should be zero
   //same problem for FreeAmount
   DString strTemp;
   getField(ifds::ApplicableUnits, strTemp, BF::HOST, false);
   double dAppUnits = DSTCommonFunctions::convertToDouble(strTemp);
   if (dAppUnits <= 0)
      setFieldNoValidate(ifds::ApplicableUnits, I_("0"), BF::HOST, false);
   getField(ifds::ApplicableAmt, strTemp, BF::HOST, false);
   double dAppAmount = DSTCommonFunctions::convertToDouble(strTemp);
   if (dAppAmount <= 0)
      setFieldNoValidate(ifds::ApplicableAmt, I_("0"), BF::HOST, false);
   //~end for character base bug fix

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void HypoRedSummary::getField( const BFFieldId& idField,
                         DString& strFieldValue,
                         const BFDataGroupId& idDataGroup,
                         bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
   if( idField == ifds::Amount || idField == ifds::FreeAmount 
		|| idField == ifds::ApplicableAmt || idField == ifds::DSC 		
		|| idField == ifds::Fee || idField == ifds::FedTax || idField == ifds::ProvTax  		
		&& formattedReturn )
   {
      DString strCurrency;
      getField( ifds::FundCurrency, strCurrency, idDataGroup, false );
      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( strCurrency.strip(), strFieldValue, strFieldValue );
   }
	else if (idField == ifds::Units || idField == ifds::FreeUnits 
		|| idField == ifds::ApplicableUnits && formattedReturn)
	{
      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
		(const_cast<HypoRedSummary*>(this))->formatUnits(strFieldValue, idDataGroup);
	}
}
//******************************************************************************

void HypoRedSummary::formatUnits(DString& strValue, const BFDataGroupId& idDataGroup)
{
	DString dstrAmountType, dstrCurrency;
   int iUnitsPrecision = 0;

   FundDetail *pFundDetail = NULL;
	FundDetailList *pFundDetailList = NULL;
   DString dstrUnitsPrecision, dstrFundCode, dstrClassCode;
	getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
	getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
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

SEVERITY HypoRedSummary::getHypoRedDetailList( HypoRedDetailList *&pHypoRedDetailList, 
                                   const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getHypoRedDetailList" ) );

   //only create details list during init
   pHypoRedDetailList = dynamic_cast<HypoRedDetailList*>(BFCBO::getObject( RED_DETAIL_LIST, idDataGroup ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedSummary.cpp-arc  $
// 
//    Rev 1.6   Jun 14 2007 11:24:56   porteanm
// PET 2363 FN?? - GAP 5  - Cleanup
// 
//    Rev 1.5   Jun 14 2007 10:52:58   porteanm
// PET 2363 FN?? - GAP 5  - for BKK.
// 
//    Rev 1.4   Nov 14 2004 14:44:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Mar 21 2003 18:14:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 06 2002 12:05:24   KOVACSRO
// FreeAmt is sometimes negative, too. Show zero, whenever it is negative.
// 
//    Rev 1.1   Nov 25 2002 09:41:40   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:54   KOVACSRO
// Initial Revision
// 
 
*/


