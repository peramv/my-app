//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : TradedUnitPosition.cpp
// ^AUTHOR : 
// ^DATE   : Dec 2009
//
//********************************************************************************
#include "stdafx.h"
#include "TradedUnitPosition.hpp"


#include <ifastdataimpl\dse_dstc0401_req.hpp> 
#include <ifastdataimpl\dse_dstc0401_vw.hpp> 

namespace
{
	const I_CHAR * const CLASSNAME		= I_( "TradedUnitPosition" );
}


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADED_UNIT_POSTION_INQUIRY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,					State Flags,		Group Flags 
	{ ifds::FullMoneyOutFound,		BFCBO::NONE,		0 },
	{ ifds::ToleranceAmtExceeded,	BFCBO::NONE,		0 },
	{ ifds::TUPUnits,				BFCBO::NONE,		0 },
	{ ifds::TUPToleranceRate,		BFCBO::NONE,		0 },
	{ ifds::TUPToleranceUnits,		BFCBO::NONE,		0 },
	{ ifds::TradeEstimatedUnits,	BFCBO::NONE,		0 },
	{ ifds::TUPOversellUnits,		BFCBO::NONE,		0 },
	{ ifds::TUPOversell,			BFCBO::NONE,		0 },
	{ ifds::TUPCalcFailed,			BFCBO::NONE,		0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
TradedUnitPosition::TradedUnitPosition( BFAbstractCBO &parent ) : MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	
}

//******************************************************************************
TradedUnitPosition::~TradedUnitPosition()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//*******************************************************************************
SEVERITY TradedUnitPosition::init (const DString &accountNum,
	                               const DString &fundCode,
				                   const DString &classCode,
				                   const DString &amount,
				                   const DString &amountType,
				   				   const DString &transNum,
								   const DString &transType,
								   const DString &tradeDate,
								   const DString &settleDate,
								   const DString &settleCurrency,
								   const DString &orderType,
								   const DString &transId,
								   const DString &exchRate,
								   const DString &dstrAccountTo,
								   const DString &dstrRedCode,
								   const DString &dstrPriceCode,
								   const DString &dstrPriceInCode,
				                   const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
	
	BFData queryData (ifds::DSTC0401_REQ);
	BFData *receivedData = new BFData(ifds::DSTC0401_VW);

	DString mgmtCoIdOut;

	queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	queryData.setElementValue (ifds::Track, I_("N"));
	queryData.setElementValue (ifds::Activity, NULL_STRING);

	queryData.setElementValue (ifds::AccountNum, accountNum); 
	queryData.setElementValue (ifds::FundCode, fundCode);
	queryData.setElementValue (ifds::ClassCode, classCode);
	queryData.setElementValue (ifds::Amount, amount);
	queryData.setElementValue (ifds::AmountType, amountType);
	queryData.setElementValue (ifds::TransNum, transNum);
	queryData.setElementValue (ifds::TransType, transType);
	queryData.setElementValue (ifds::TradeDate, tradeDate);
	queryData.setElementValue (ifds::SettleDate, settleDate);
	queryData.setElementValue (ifds::SettleCurrency, settleCurrency);
	queryData.setElementValue (ifds::OrderType, orderType);
	queryData.setElementValue (ifds::TransId, transId);
	queryData.setElementValue (ifds::ExchRate, exchRate);
	queryData.setElementValue (ifds::AccountTo, dstrAccountTo);
	queryData.setElementValue (ifds::RedCode  , dstrRedCode  );
	queryData.setElementValue (ifds::PriceCode  , dstrPriceCode  );
	queryData.setElementValue (ifds::PriceInCode  , dstrPriceInCode  );

	ReceiveData (DSTC_REQUEST::TRADED_UNIT_POSTION_INQUIRY, queryData, *receivedData, DSTCRequestor (getSecurity()));


	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TradedUnitPosition::buildKey (const DString &accountNum,
	                               const DString &fundCode,
				                   const DString &classsCode,
				                   const DString &amount,
				                   const DString &amountType,
				   				   const DString &transNum,
								   const DString &transType,
								   const DString &tradeDate,
								   const DString &settleDate,
								   const DString &settleCurrency,
								   const DString &orderType,
								   const DString &transId,
								   const DString &exchRate,
								   const DString &dstrAccountTo, 
								   const DString &dstrRedCode,
								   const DString &dstrPriceCode,
								   const DString &dstrPriceInCode,
                                   DString &strKey)
{
	DString dstrAccountNum (accountNum),
	        dstrFundCode (fundCode),
		    dstrClassCode (classsCode),
		    dstrAmount (amount),
		    dstrAmountType (amountType),
		    dstrTransNum (transNum),
			dstrTransType (transType),
	        dstrTradeDate (tradeDate),
			dstrSettleDate (settleDate),
			dstrSettleCurrency (settleCurrency),
			dstrOrderType (orderType),
			dstrTransId (transId),
			dstrExchRate (exchRate),
			dstrAcctTo(dstrAccountTo),
			dstrRedemptionCode(dstrRedCode),
			dstrPrice_Code(dstrPriceCode),
			dstrPriceIn_Code(dstrPriceInCode);

   dstrTransType.strip().upperCase();
   dstrTransNum.strip ();
   dstrAccountNum.strip();
   dstrTradeDate.strip();
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   dstrAmount.strip();
   dstrAmountType.strip().upperCase();
   dstrSettleDate.strip();
   dstrSettleCurrency.strip();
   dstrOrderType.strip().upperCase();
   dstrTransId.strip ();
   dstrExchRate.strip ();
   dstrAcctTo.stripAll();
   dstrRedemptionCode.stripAll();

   strKey = DString (I_("TradedUnitPosition")) + 
            I_("TransType=") + dstrTransType + I_(";") +
            I_("AccountNum=") + dstrAccountNum + I_(";") +
            I_("TransNum=") + dstrTransNum + I_(";") +
            I_("TradeDate=") + dstrTradeDate + I_(";") +
            I_("FundCode=") + dstrFundCode + I_(";") +
            I_("ClassCode=") + dstrClassCode + I_(";") +
            I_("Amount=") + dstrAmount + I_(";") +
            I_("AmountType=") + dstrAmountType + I_(";") +
            I_("SettleDate=") + dstrSettleDate + I_(";") +
            I_("SettleCurrency=") + dstrSettleCurrency + I_(";") +
            I_("OrderType=") + dstrOrderType + I_(";") + 
			I_("TransId=") + dstrTransId + I_(";") +
			I_("ExchRate=") + dstrExchRate + I_(";")+
			I_("AccountTo=")+ dstrAcctTo   + I_(";")+
			I_("RedCode=")  + dstrRedemptionCode + I_(";")+
			I_("PriceCode=")  + dstrPrice_Code + I_(";")+
			I_("PriceInCode=")  + dstrPriceIn_Code + I_(";");
}
//*******************************************************************************

/* $Log::  
 */