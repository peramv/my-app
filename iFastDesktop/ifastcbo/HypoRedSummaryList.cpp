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
// ^FILE   : HypoRedSummaryList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedSummaryList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "hyporedacctholdingslist.hpp"
#include "hyporedcriteria.hpp"
#include "hyporedcurrencylist.hpp"
#include "hyporedsummary.hpp"
#include "hyporedsummarylist.hpp"
#include "mfaccount.hpp"

#include <ifastdataimpl\dse_dstc0227_vw.hpp>
#include <ifastdataimpl\dse_dstc0398_vw.hpp>
#include <ifastdataimpl\dse_dstc0227_req.hpp>
#include <ifastdataimpl\dse_dstc0398_req.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedSummaryList" );
   const I_CHAR * const HYPO_RED_PERSISTENCY = I_( "SIMRED" );
   const double dSmallValue                  = .0000000001;

}

namespace ifds
{
	extern CLASS_IMPORT const BFDecimalFieldId Amount;
	extern CLASS_IMPORT const BFTextFieldId rxFundCode;
	extern CLASS_IMPORT const BFTextFieldId rxClassCode;

}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HYPO_REDEMPTION_SUMMARY;
   extern CLASS_IMPORT const DSTCRequest HYPO_REDEMPTION_DETAILS;
   extern CLASS_IMPORT const DSTCRequest HYPO_REDEMPTION;
}

namespace CND
{  
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

//****************************************************************************
HypoRedSummaryList::HypoRedSummaryList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_pView227(NULL),
_pView398(NULL),
_pRequest398(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
}

//****************************************************************************
HypoRedSummaryList::~HypoRedSummaryList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
	if (_pView227)
		delete _pView227;
	if (_pView398)
		delete _pView398;
	if (_pRequest398)
		delete _pRequest398;
}   

//****************************************************************************

SEVERITY HypoRedSummaryList::init( const BFDataGroupId& idDataGroup, const DString& dstrTrack /*= I_("N")*/,
								  const DString& dstrPageName /*= NULL_STRING*/ )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	if (_pView227) delete _pView227;
	if (_pView398) delete _pView398;
	if (_pRequest398) delete _pRequest398;

	_pRequest398 = new BFData(ifds::DSTC0398_REQ);

	DString mgmtCoId;
	_pRequest398->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoId ) );
	_pRequest398->setElementValue( ifds::Track, dstrTrack );
	_pRequest398->setElementValue( ifds::Activity, dstrPageName );

	prepareRequest(idDataGroup);

	_pView398 = new BFData(ifds::DSTC0398_VW);


	//ReceiveData( DSTC_REQUEST::HYPO_REDEMPTION, *_pRequest398, *_pView398, DSTCRequestor( getSecurity(), true ) );

	if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::HYPO_REDEMPTION_SUMMARY, *_pRequest398, *_pView398, DSTCRequestor( getSecurity(), true ) ) > WARNING )
	{
		viewFailureCleanup(idDataGroup);
		return(GETCURRENTHIGHESTSEVERITY());
	}

	int cRepeats = _pView398->getRepeatCount();

	// create view227 out of 398
	_pView227 = new BFData(ifds::DSTC0227_VW);
	int cRepeatCount = 0;
	for(int i=0;i<cRepeats;i++)
	{
		const BFData &data = _pView398->getRepeat( i );
		DString recordtype;

		data.getElementValue( ifds::RecType, recordtype );
		if(I_("D") == recordtype.strip())
		{
			BFData *repeate = new BFData (ifds::DSTC0398_VWRepeat_Record);
			DString tmp;
			repeate->setElementValue (ifds::FundCode, data.getElementValue( ifds::FundCode, tmp ));
			repeate->setElementValue (ifds::ClassCode, data.getElementValue( ifds::ClassCode, tmp ));
			repeate->setElementValue (ifds::Baycom, data.getElementValue( ifds::Baycom, tmp ));
			repeate->setElementValue (ifds::FundCurrency, data.getElementValue( ifds::FundCurrency, tmp ));
			repeate->setElementValue (ifds::Amount, data.getElementValue( ifds::Amount, tmp ));
			repeate->setElementValue (ifds::Units, data.getElementValue( ifds::Units, tmp ));
			repeate->setElementValue (ifds::FeePercent, data.getElementValue( ifds::FeePercent, tmp ));
			repeate->setElementValue (ifds::DSC, data.getElementValue( ifds::DSC, tmp ));
			repeate->setElementValue (ifds::FedClawback, data.getElementValue( ifds::FedClawback, tmp ));
			repeate->setElementValue (ifds::ProvClawback, data.getElementValue( ifds::ProvClawback, tmp ));
			repeate->setElementValue (ifds::AdditionalProvClawback, data.getElementValue( ifds::AdditionalProvClawback, tmp ));
			repeate->setElementValue (ifds::TotCBAmount, data.getElementValue( ifds::TotCBAmount, tmp ));

			_pView227->addRepeat(*repeate);
			++cRepeatCount;
		}
	}
	DString repeatCount;
	repeatCount.appendInt( cRepeatCount );
	_pView227->setElementValue( ifds::RepeatCount, repeatCount );

	//everything went well; build summary list
	if( 0 != cRepeats )
	{
		for( int i = 0; i < cRepeats; i++ )
		{
			const BFData &data = _pView398->getRepeat( i );
			DString recordtype;

			data.getElementValue( ifds::RecType, recordtype );
			if(I_("S") == recordtype.strip())
			{
				DString dstrKeySummary;
				getStrKey( dstrKeySummary, &data );
				HypoRedSummary *pHypoRedSummary = new HypoRedSummary( *this );
				setObject( pHypoRedSummary, dstrKeySummary, OBJ_ACTIVITY_NONE, BF::HOST );
				pHypoRedSummary->init( data, *_pView227 );
			} 
		}
	}

	refreshCurrencyList(idDataGroup);

	return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************

void HypoRedSummaryList::viewFailureCleanup(const BFDataGroupId& idDataGroup)
{
	delete _pView227;
	delete _pView398;
	_pView227 = NULL;
	_pView398 = NULL;
	refreshCurrencyList(idDataGroup);
}

//****************************************************************************
void HypoRedSummaryList::refreshCurrencyList(const BFDataGroupId& idDataGroup)
{
	HypoRedCurrencyList* pCurrList;
	HypoRedCriteria* pHypoRedCriteria = dynamic_cast<HypoRedCriteria*>(getParent());
	assert(pHypoRedCriteria);
	//get a new, empty currency list
	pHypoRedCriteria->getCurrencyList(pCurrList, idDataGroup, true);
	if (!_pView398)
		return;

	int cRepeats = _pView398->getRepeatCount();
	if( 0 != cRepeats )
	{
		for( int i = 0; i < cRepeats; i++ )
		{
			DString recordtype;
			const BFData &data = _pView398->getRepeat( i );
			data.getElementValue( ifds::RecType, recordtype );
			if(I_("S") == recordtype.strip())
			{
				pCurrList->changeCurrencyTotal(idDataGroup, data);
			}
		}
	}

}
//****************************************************************************
SEVERITY	HypoRedSummaryList::prepareRequest(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "prepareRequest" ) );

	DString strAmount, strAccountNum, strTradeDate, strGrossOrNet, strAmtType,
		strFullRed, strRedCode, strAcctLvlDSC;

	//set values for the fix part
	getParent()->getParent()->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   _pRequest398->setElementValue( ifds::AccountNum, strAccountNum, false, false );
	getParent()->getField(ifds::TradeDate, strTradeDate, idDataGroup, false);
   _pRequest398->setElementValue( ifds::TradeDate, strTradeDate, false, false );
	getParent()->getField(ifds::GrossOrNet, strGrossOrNet, idDataGroup, false);
   _pRequest398->setElementValue( ifds::GrossOrNet, strGrossOrNet, false, false );
	getParent()->getField(ifds::AmtType, strAmtType, idDataGroup, false);
   _pRequest398->setElementValue( ifds::AmtType, strAmtType, false, false );
	getParent()->getField(ifds::FullRed, strFullRed, idDataGroup, false);
   _pRequest398->setElementValue( ifds::FullRed, strFullRed, false, false );
	getParent()->getField(ifds::RedCode, strRedCode, idDataGroup, false);
   _pRequest398->setElementValue( ifds::RedCode, strRedCode, false, false );
	getParent()->getField(ifds::AcctLvlDSC, strAcctLvlDSC, idDataGroup, false);
   _pRequest398->setElementValue( ifds::AcctLvlDSC, strAcctLvlDSC, false, false );

	HypoRedAcctHoldingsList* pHypoRedAcctHoldingsList = NULL;
	HypoRedCriteria* pHypoRedCriteria = dynamic_cast<HypoRedCriteria*>(getParent());
	assert(pHypoRedCriteria);
   int nRepeatCount = 0;
	//add as many repeats as many fund holdings have amounts different from zero
	if (pHypoRedCriteria->getHypoRedAcctHoldingsList(pHypoRedAcctHoldingsList, idDataGroup) 
		 <= WARNING && pHypoRedAcctHoldingsList)
	{
		BFObjIter iter(*pHypoRedAcctHoldingsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		while ( !iter.end() ) 
      {
         iter.getObject()->getField(ifds::Amount, strAmount, idDataGroup, false);
			double dAmount = DSTCommonFunctions::convertToDouble(strAmount);
			if( dAmount > dSmallValue )//greater than zero
			{
				DString strFundCode, strClassCode, strAmount;
				BFData repeat398(ifds::DSTC0398_REQRepeat_Record);

				iter.getObject()->getField(ifds::rxFundCode, strFundCode, idDataGroup, false);
				repeat398.setElementValue( ifds::FundCode, strFundCode, false, false );
				iter.getObject()->getField(ifds::rxClassCode, strClassCode, idDataGroup, false);
				repeat398.setElementValue( ifds::ClassCode, strClassCode, false, false );
				iter.getObject()->getField(ifds::Amount, strAmount, idDataGroup, false);
				repeat398.setElementValue( ifds::Amount, strAmount, false, false );

				_pRequest398->addRepeat(repeat398);
            nRepeatCount++;
			}
         ++iter;
      }
	}
   DString strRepeatCount = DSTCommonFunctions::doubleToDString(ifds::RepeatCount, nRepeatCount);
   _pRequest398->setElementValue( ifds::RepeatCount, strRepeatCount, false, false );

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************

bool HypoRedSummaryList::needsRefresh(const BFDataGroupId& idDataGroup)
{
	//if criteria changed, return true

	//if 398 has never been called, return true
	if (!_pRequest398)
		return true;

	//check if the fix part changed
	if (isFixedPartChanged(idDataGroup))
		return true;

	//check if at least one repeat has changed
	HypoRedAcctHoldingsList* pHypoRedAcctHoldingsList = NULL;
	HypoRedCriteria* pHypoRedCriteria = dynamic_cast<HypoRedCriteria*>(getParent());
	assert(pHypoRedCriteria);
	int iTotalRepeats = _pRequest398->getRepeatCount();
	int iRepeat = 0;
	if (pHypoRedCriteria->getHypoRedAcctHoldingsList(pHypoRedAcctHoldingsList, idDataGroup) 
		 <= WARNING && pHypoRedAcctHoldingsList)
	{
		BFObjIter iter(*pHypoRedAcctHoldingsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
		while ( !iter.end() ) 
      {
			DString strOldFundCode, strOldClassCode, strOldAmount,
					strNewFundCode, strNewClassCode, strNewAmount;
			BFAbstractCBO *pHolding = iter.getObject();
         pHolding->getField(ifds::Amount, strNewAmount, idDataGroup, false);
			double dAmount = DSTCommonFunctions::convertToDouble(strNewAmount);
			if( dAmount > dSmallValue )//greater than zero
			{
				iRepeat++;
				BFData repeat398(ifds::DSTC0398_REQRepeat_Record);
				//if there are no repeats, or there are fewer than holdings with valid amount, have to refresh
				if (!iTotalRepeats || iRepeat > iTotalRepeats)
					return true;

            BFData& repeat = const_cast<BFData&>(_pRequest398->getRepeat( iRepeat-1 ) );

				if (isRepeatReqFieldChanged(repeat, ifds::FundCode, pHolding, ifds::rxFundCode, idDataGroup))
					return true;
				if (isRepeatReqFieldChanged(repeat, ifds::ClassCode, pHolding, ifds::rxClassCode, idDataGroup))
					return true;
				if (isRepeatReqFieldChanged(repeat, ifds::Amount, pHolding, ifds::Amount, idDataGroup))
					return true;
			}
         ++iter;
      }
	}
	//if total number of repeats does not match total number of holdings have to refresh
	if (iRepeat != iTotalRepeats)
		return true;

	return false;
}
//*****************************************************************************

bool HypoRedSummaryList::isFixedPartChanged(const BFDataGroupId& idDataGroup)
{
	BFFieldId fields[] = {ifds::TradeDate, ifds::GrossOrNet, ifds::AmtType,
		ifds::FullRed, ifds::RedCode, ifds::AcctLvlDSC, ifds::NullFieldId};

	int i = 0;
	while (fields[i] != ifds::NullFieldId)
	{
		if (isReqFieldChanged(fields[i], idDataGroup))
			return true;
		i++;
	}

	return false;
}
//******************************************************************************

bool HypoRedSummaryList::isReqFieldChanged(const BFFieldId& fieldId, const BFDataGroupId& idDataGroup)
{
	DString strOldValue, strNewValue;
	getParent()->getField(fieldId, strNewValue, idDataGroup, false);
   strOldValue = _pRequest398->getElementValue( fieldId );
	if (strOldValue.strip() != strNewValue.strip())
		return true;

	return false;
}
//******************************************************************************

bool HypoRedSummaryList::isRepeatReqFieldChanged(BFData& repeat, const BFFieldId& repeatFieldId, 
		BFAbstractCBO* pHolding, const BFFieldId& holdingFieldId, const BFDataGroupId& idDataGroup)
{
	DString strNewValue, strOldValue;
	if( repeat.exists( repeatFieldId ) )
		strOldValue = repeat.getElementValue( repeatFieldId );
	pHolding->getField(holdingFieldId, strNewValue, idDataGroup, false);
	if (strNewValue.strip() != strOldValue.strip())
		return true;

	return false;
}
//******************************************************************************

SEVERITY HypoRedSummaryList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
	assert(0);//with the current design it should never be called
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void HypoRedSummaryList::getStrKey( DString &strKey, const BFData *data )
{
	DString strFundCode, strClassCode;
	data->getElementValue(ifds::FundCode, strFundCode);
	data->getElementValue(ifds::ClassCode, strClassCode);
	strKey = strFundCode.strip() + I_(" ") + strClassCode.strip();
}

//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedSummaryList.cpp-arc  $
// 
//    Rev 1.4   Sep 11 2009 16:40:14   yingz
// using view 398
// 
//    Rev 1.3   Nov 14 2004 14:44:48   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 18:14:32   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 25 2002 09:42:20   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:56   KOVACSRO
// Initial Revision
// 
 
*/


