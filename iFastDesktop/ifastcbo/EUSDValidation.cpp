//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : EUSDValidation.cpp
// ^AUTHOR :  
// ^DATE   : 
//
// ^CLASS    : EUSDValidation 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "EUSDValidation.hpp"
#include <ifastdataimpl\dse_dstc0366_req.hpp>
#include <ifastdataimpl\dse_dstc0366_vw.hpp>

namespace
{
	const I_CHAR * const CLASSNAME		= I_ ("EUSDValidation");
	const I_CHAR * const ALLOW_TRADE	= I_ ( "0" );
}

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest EUSD_VALIDATE_TRADE;
}


//******************************************************************************
EUSDValidation::EUSDValidation( BFAbstractCBO &parent ) : MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}
//******************************************************************************
EUSDValidation::~EUSDValidation ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY EUSDValidation::init (const DString& accountNumber, const DString& fundCode, 
							   const DString& fundClass, const DString& tradeDate,
							   const DString& dstrTrack, const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
	BFData	queryData(ifds::DSTC0366_REQ);
	DString mgmtCoIdOut;

	queryData.setElementValue (ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	queryData.setElementValue (ifds::Track, dstrTrack );
    queryData.setElementValue (ifds::Activity, dstrPageName );
	queryData.setElementValue (ifds::AccountNum, accountNumber);
	queryData.setElementValue (ifds::FundCode, fundCode); 
	queryData.setElementValue (ifds::FundClass, fundClass); 
	queryData.setElementValue (ifds::EffectiveDate, tradeDate);
	
	ReceiveData (DSTC_REQUEST::EUSD_VALIDATE_TRADE, queryData, ifds::DSTC0366_VW, DSTCRequestor(getSecurity(), true));

	return GETCURRENTHIGHESTSEVERITY ();
}
//****************************************************************	**************
bool EUSDValidation::isBackDatedTradeAllowed (const BFDataGroupId& idDataGroup)
{
	DString	dstrEUSDStatus;

	getField (ifds::EUSDStatus, dstrEUSDStatus, idDataGroup, false);

	return dstrEUSDStatus == ALLOW_TRADE;
}