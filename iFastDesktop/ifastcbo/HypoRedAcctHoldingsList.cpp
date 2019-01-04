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
// ^FILE   : HypoRedAcctHoldingsList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedAcctHoldingsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "hyporedacctholding.hpp"
#include "hyporedacctholdingslist.hpp"

#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0020_req.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedAcctHoldingsList" );
	const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const AMOUNT               = I_( "D" );
   const I_CHAR * const UNITS                = I_( "U" );
   const double dSmallValue                  = .0000000001;

}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MFACCOUNT_HOLDINGS;
}

namespace  CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId FullRed;
   extern CLASS_IMPORT const BFTextFieldId AmtType;

}

//****************************************************************************
HypoRedAcctHoldingsList::HypoRedAcctHoldingsList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
}

//****************************************************************************
HypoRedAcctHoldingsList::~HypoRedAcctHoldingsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
	if( _pRequestData )
      delete _pRequestData;
}   

//****************************************************************************

SEVERITY HypoRedAcctHoldingsList::init( const BFDataGroupId& idDataGroup, const DString& dstrTrack /*= I_("N")*/,
                         const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
	//make the view call(view 20) using trade date from parent (HypoRedCriteria)
	DString strTradeDate, mgmtCoIdOut, strAccountNum;
	getParent()->getField(ifds::TradeDate, strTradeDate, idDataGroup, false);
	getParent()->getParent()->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);

	if (_pRequestData) delete _pRequestData;
	_pRequestData = new BFData(ifds::DSTC0020_REQ); 

   _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue( ifds::AccountNum, strAccountNum, false, false );
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   _pRequestData->setElementValue( ifds::AsofDate, strTradeDate, false, false );
   _pRequestData->setElementValue( ifds::CalculateACB, NO, false, false );
   _pRequestData->setElementValue (ifds::ConvertAmount, I_("Y"), false, false);


   ReceiveData( DSTC_REQUEST::MFACCOUNT_HOLDINGS, *_pRequestData, 
		ifds::DSTC0020_VW, DSTCRequestor(getSecurity()) );

   setDefaultAmounts(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY HypoRedAcctHoldingsList::doCreateObject( const BFData& data, 
                                                  BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   //create a HypoRedAcctHolding object
	pObjOut =  new HypoRedAcctHolding( *this );
   ((HypoRedAcctHolding*) pObjOut)->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool HypoRedAcctHoldingsList::needsRefresh(const BFDataGroupId& idDataGroup)
{
	if (_pRequestData)
	{
		DString strOldTradeDate, strTradeDate;
		_pRequestData->getElementValue(ifds::AsofDate, strOldTradeDate); 
		getParent()->getField(ifds::TradeDate, strTradeDate, idDataGroup, false);
		if (strOldTradeDate.strip().empty() || strOldTradeDate != strTradeDate.strip())
			return true;
	}
   else
      return true;

	return false;
}
//******************************************************************************

bool HypoRedAcctHoldingsList::isValidForInquiry(const BFDataGroupId& idDataGroup)
{
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	if (!iter.getNumberOfItemsInList())
		return false;

	int nValidHoldings = 0;
	while( !iter.end() )
   {
      DString strAmount;
      iter.getObject()->getField(ifds::Amount, strAmount, idDataGroup, false);
		double dAmount = DSTCommonFunctions::convertToDouble(strAmount);
		if( dAmount > dSmallValue )//greater than zero
		{
			if (iter.getObject()->getErrorState(ifds::Amount, idDataGroup)>WARNING)
				return false;
			else
				nValidHoldings++;
		}
		++iter; 
   }

	return( nValidHoldings != 0 );
}
//******************************************************************************

void HypoRedAcctHoldingsList::setDefaultAmounts(const BFDataGroupId& idDataGroup)
{
   //rule : if Criteria::FullRedemption is Yes, the Amount field is populated with
   //a) Market Value, if Criteria::AmountType is Amount (Dollars)
   //b) Settled Units, if Criteria::AmountType is Units
   //in both cases, Amount is read-only for full redemption and updateable for partial redemptions
   DString strFullred, strAmtType;
	getParent()->getField(ifds::FullRed, strFullred, idDataGroup, false);
   if (strFullred.strip() != YES)
      return;

	getParent()->getField(ifds::AmtType, strAmtType, idDataGroup, false);
   strAmtType.strip().upperCase();

   BFObjIter iter( *this, BF::HOST);
	while( !iter.end() )
   {
      DString strAmount(I_("0"));
      if (strAmtType == AMOUNT)
         iter.getObject()->getField(ifds::SettledValue, strAmount, BF::HOST, false);
      else if (strAmtType == UNITS)
         iter.getObject()->getField(ifds::SettledUnits, strAmount, BF::HOST, false);
      else assert(0);

      if (strAmount != I_("0"))
      {
         iter.getObject()->setField(ifds::Amount, strAmount, idDataGroup, false);
         iter.getObject()->setFieldReadOnly(ifds::Amount, idDataGroup, true);
      }

		++iter; 
   }
}

//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedAcctHoldingsList.cpp-arc  $
// 
//    Rev 1.4   May 29 2007 12:13:00   jankovii
// Incident #899142 - cannot place trade.
// 
//    Rev 1.3   Nov 14 2004 14:44:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 18:13:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 25 2002 09:37:10   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:50   KOVACSRO
// Initial Revision
// 
 
*/


