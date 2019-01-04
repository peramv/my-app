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
//    Copyright 2018 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : IntraDayPricing.cpp
// ^AUTHOR : 
// ^DATE   : 10 July, 2018
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtco.hpp"
#include "IntraDayPricing.h"
#include <ifastdataimpl\dse_dstc0487_req.hpp>
#include <ifastdataimpl\dse_dstc0487_vw.hpp>

namespace CORFAX
{
	extern CLASS_IMPORT const DSTCHost HOST;
	const char *const CFX_TRANS = "CFXTRAN";
}

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest TRADE_INTRA_DAY_PRICING;
}

namespace CND
{  
	
}
namespace
{
	const I_CHAR * const CLASSNAME           = I_ ("IntraDayPricing");
}

IntraDayPricing::IntraDayPricing (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}

//******************************************************************************
IntraDayPricing::~IntraDayPricing ()
{
	TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY IntraDayPricing::init ( 
								const DString &strRunMode,
								const DString &strFromFund,
								const DString &strFromClass, 
								const DString &strToFund, 
								const DString &strToClass, 
								const DString &strDealDate,
								const DString &strDealTime, 
								const DString &strTradeFromDate,
								const DString &strTradeInDate,								
								const DString &strTransType,
								const DString &strCallingType,
								const DString &dstrTrack, 
								const DString &dstrPageName
								)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
	BFData queryData  (ifds::DSTC0487_REQ);
	DString mgmtCoIdOut;
	queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	queryData.setElementValue( ifds::Track, dstrTrack );
	queryData.setElementValue( ifds::Activity, dstrPageName );
	queryData.setElementValue (ifds::RunMode, strRunMode);
	queryData.setElementValue (ifds::Fund, strFromFund);
	queryData.setElementValue (ifds::Class, strFromClass);	
	queryData.setElementValue (ifds::DealDate, strDealDate);
	queryData.setElementValue (ifds::DealTime, strDealTime);
	queryData.setElementValue (ifds::FundTo, strToFund);
	queryData.setElementValue (ifds::ClassTo, strToClass);
	queryData.setElementValue (ifds::TradeDate, strTradeFromDate);
	queryData.setElementValue (ifds::TradeInDate, strTradeInDate);
	queryData.setElementValue (ifds::TransType, strTransType);
	queryData.setElementValue (ifds::CallingType, strCallingType);
	ReceiveData  (DSTC_REQUEST::TRADE_INTRA_DAY_PRICING, 
                 queryData, 
                 ifds::DSTC0487_VW,
                 DSTCRequestor  (getSecurity (), false));

	return GETCURRENTHIGHESTSEVERITY();
}




