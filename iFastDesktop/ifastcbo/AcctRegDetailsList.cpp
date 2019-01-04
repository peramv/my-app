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
// ^FILE   : AcctRegDetailsList.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : AcctRegDetailsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AcctRegDetailsList.hpp"
#include "AcctRegDetails.hpp"
#include <ifastdataimpl\dse_dstc0451_vw.hpp>
#include <ifastdataimpl\dse_dstc0451_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest ACCT_REG_DETAILS_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_("AcctRegDetailsList");
}

namespace ifds
{
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFTextFieldId ReqIndiciaSearch;
}

namespace CND
{
	extern const long ERR_DATA_NOT_FOUND;
	extern const long ERR_DATE_RANGE_OVERLAP;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,               State Flags,    Group Flags 
   {ifds::ReqIndiciaSearch,       BFCBO::NONE,        0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AcctRegDetailsList::AcctRegDetailsList(BFAbstractCBO &parent)
   : MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

	setObjectAsList( );
}


//******************************************************************************
AcctRegDetailsList::~AcctRegDetailsList( void )
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY AcctRegDetailsList::init(const DString &dstrAccountNum,
								  const DString &dstrComplyRule,
								  const DString& dstrTrack, 
								  const DString& dstrPageName)                             
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	BFData requestData(ifds::DSTC0451_REQ);
	DString mgmtCoIdOut;
	
	std::vector<DString> vComplyRule;
	DSTCommonFunctions::tokenizeString(dstrComplyRule, vComplyRule);
	
	unsigned int complyIndex;
	for(complyIndex = 0; complyIndex < vComplyRule.size(); complyIndex++)
	{
		requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
		requestData.setElementValue(ifds::Track, dstrTrack);
		requestData.setElementValue(ifds::Activity, dstrPageName);

		// For new account, send account# 0 - backend will handle it.
		requestData.setElementValue(ifds::AccountNum, getParent()->isNew()? I_("0"):dstrAccountNum);
		requestData.setElementValue(ifds::Regulatory, vComplyRule[complyIndex].stripAll());

		ReceiveData(DSTC_REQUEST::ACCT_REG_DETAILS_INQUIRY, requestData, ifds::DSTC0451_VW, DSTCRequestor(getSecurity(), true));
	}
	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY AcctRegDetailsList::init(const BFData& data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( data )" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY AcctRegDetailsList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

	pObjOut = new AcctRegDetails( *this );
	((AcctRegDetails*)(pObjOut))->init(const_cast<BFData&>(data));

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY AcctRegDetailsList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

	AcctRegDetails *pAcctRegDetails = new AcctRegDetails(*this);

	pAcctRegDetails->initNew(idDataGroup);
	pBase = pAcctRegDetails;

	return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************
SEVERITY AcctRegDetailsList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	//validateOverlappingDateRanges(idDataGroup);

	return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************
SEVERITY AcctRegDetailsList::validateOverlappingDateRanges(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateOverlappingDateRanges"));

	//BFObjIter iter1(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	//BFObjIter iter2(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

	//iter1.begin();

	//while(!iter1.end())
	//{
	//	DString acctRegStartDate1, acctRegStopDate1, acctRegStartDate2, acctRegStopDate2;

	//	iter1.getObject()->getField(ifds::EffectiveDate, acctRegStartDate1, idDataGroup);
	//	iter1.getObject()->getField(ifds::StopDate, acctRegStopDate1, idDataGroup);

	//	iter2.positionByKey(iter1.getStringKey()); 
	//	++iter2;

	//	while (!iter2.end())
	//	{
	//		iter2.getObject()->getField(ifds::EffectiveDate, acctRegStartDate2, idDataGroup);
	//		iter2.getObject()->getField(ifds::StopDate, acctRegStopDate2, idDataGroup);

	//		if (DSTCommonFunctions::dateRangesOverlap(acctRegStartDate1, acctRegStopDate1, acctRegStartDate2, acctRegStopDate2))
	//		{
	//			ADDCONDITIONFROMFILE(CND::ERR_DATE_RANGE_OVERLAP);
	//		}

	//		++iter2;
	//	}

	//	++iter1;
	//}
	return(GETCURRENTHIGHESTSEVERITY());
}