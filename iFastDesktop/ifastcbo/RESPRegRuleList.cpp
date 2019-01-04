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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE		: RESPRegRuleList.cpp
// ^AUTHOR		:
// ^DATE		: 
//
// ^CLASS		: RESPRegRuleList
// ^SUBCLASS	:
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPRegRuleList.hpp"
#include "RESPRegRule.hpp"
#include <ifastdataimpl\dse_dstc0482_req.hpp>
#include <ifastdataimpl\dse_dstc0482_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0482_vw.hpp>


namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest RESP_REG_RULE_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_("RESPRegRuleList");
}

namespace ifds
{

}

//******************************************************************************
RESPRegRuleList::RESPRegRuleList(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	setObjectAsList( );
}

//******************************************************************************
RESPRegRuleList::~RESPRegRuleList( void )
{
	TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY RESPRegRuleList::init(const DString &dstrTrack, 
							   const DString &dstrPageName)                             
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	BFData requestData(ifds::DSTC0482_REQ);
	DString mgmtCoIdOut;

	requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	requestData.setElementValue(ifds::Track, dstrTrack);
	requestData.setElementValue(ifds::Activity, dstrPageName);
	requestData.setElementValue (ifds::NextKey, NULL_STRING);

	ReceiveData(DSTC_REQUEST::RESP_REG_RULE_INQUIRY, requestData, ifds::DSTC0482_VW, DSTCRequestor(getSecurity(), true));

	while ( doMoreRecordsExist() )
	{
	   getMore();
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPRegRuleList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

	pObjOut = new RESPRegRule( *this );
	((RESPRegRule*)(pObjOut))->init(const_cast<BFData&>(data));

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPRegRuleList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

	RESPRegRule *pRESPRegRule = new RESPRegRule(*this);

	pRESPRegRule->initNew(idDataGroup);
	pBase = pRESPRegRule;

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPRegRuleList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPRegRuleList::getMore()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

	if( doMoreRecordsExist() )
	{
		BFData requestData(ifds::DSTC0482_REQ);
		ReceiveData( DSTC_REQUEST::RESP_REG_RULE_INQUIRY, requestData, ifds::DSTC0482_VW, DSTCRequestor(getSecurity()) );
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool RESPRegRuleList::isNetBalTransferRule( const DString& respRuleType, const DString& respNotlType, const BFDataGroupId& idDataGroup )
{	
	DString dstrRESPRuleType, dstrRESPNotlType, dstrRuleValue, dstrStartDate, dstrEndDate, dstrGBCD;
	bool bNetRuleValue = true;

	// one 'TransferSplit' rule type record per notional type:
	// - SAGES (Grant,AC,UC), QESIB (AC,UC,YTD,Basic), QESII, BCTESG configured as 'Net' or 'PurRed'
	// - CESG, ADCESG, CLB, CNTB, P98C configured as 'PurRed' for all clients 
	// - P2007C configured as 'Net' for all clients 

	BFObjIter bfIter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	
	bfIter.begin();
	while(!bfIter.end())
	{
		bfIter.getObject()->getField(ifds::RESPRuleType, dstrRESPRuleType, idDataGroup, false);
		bfIter.getObject()->getField(ifds::RESPNotlType, dstrRESPNotlType, idDataGroup, false);
		bfIter.getObject()->getField(ifds::RESPRuleValue, dstrRuleValue, idDataGroup, false);
		bfIter.getObject()->getField(ifds::StartDate, dstrStartDate, idDataGroup, false);
		bfIter.getObject()->getField(ifds::EndDate, dstrEndDate, idDataGroup, false);
		bfIter.getObject()->getField(ifds::GBCD, dstrGBCD, idDataGroup, false);

		dstrRESPRuleType.upperCase().stripAll();
		dstrRuleValue.upperCase().stripAll();
		dstrStartDate.stripAll();
		dstrEndDate.stripAll();
		dstrGBCD.upperCase().stripAll();

		if (dstrRESPRuleType == respRuleType && dstrRESPNotlType == respNotlType && dstrGBCD == I_("Y")) // 'TransferSplit'
		{						
			if (!dstrRuleValue.empty())
			{
				bNetRuleValue = (dstrRuleValue == I_("NET")) ? true : false;
				break;
			}		
		}

		++bfIter;
	}

	return bNetRuleValue;
}


