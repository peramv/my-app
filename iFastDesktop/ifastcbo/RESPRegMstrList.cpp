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
// ^FILE   : RESPRegMstrList.cpp
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : RESPRegMstrList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPRegMstrList.hpp"
#include "RESPRegMstr.hpp"
#include <ifastdataimpl\dse_dstc0467_req.hpp>
#include <ifastdataimpl\dse_dstc0467_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0467_vw.hpp>


namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest RESP_REG_MSTR_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_("RESPRegMstrList");
}

namespace ifds
{

}

namespace CND
{
	
}


//******************************************************************************
RESPRegMstrList::RESPRegMstrList(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	setObjectAsList( );
}


//******************************************************************************
RESPRegMstrList::~RESPRegMstrList( void )
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY RESPRegMstrList::init(const DString &dstrTrack, 
							   const DString &dstrPageName)                             
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	BFData requestData(ifds::DSTC0467_REQ);
	DString mgmtCoIdOut;

	requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	requestData.setElementValue(ifds::Track, dstrTrack);
	requestData.setElementValue(ifds::Activity, dstrPageName);
	requestData.setElementValue (ifds::NextKey, NULL_STRING);

	ReceiveData(DSTC_REQUEST::RESP_REG_MSTR_INQUIRY, requestData, ifds::DSTC0467_VW, DSTCRequestor(getSecurity(), true));

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPRegMstrList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

	pObjOut = new RESPRegMstr( *this );
	((RESPRegMstr*)(pObjOut))->init(const_cast<BFData&>(data));

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY RESPRegMstrList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

	RESPRegMstr *pRESPRegMstr = new RESPRegMstr(*this);

	pRESPRegMstr->initNew(idDataGroup);
	pBase = pRESPRegMstr;

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY RESPRegMstrList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool RESPRegMstrList::isGrantTypeActive( const DString &dstrTradeDate, const DString& respNotlType, const BFDataGroupId& idDataGroup )
{
	bool bIsGrantTypeClient = false;
	DString dstrRESPNotlType, dstrStartDate, dstrEndDate, dstrGBCD;

	BFObjIter bfIter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

	bfIter.begin();
	while(!bfIter.end())
	{
		bfIter.getObject()->getField(ifds::RESPNotlType, dstrRESPNotlType, idDataGroup, false);
		bfIter.getObject()->getField(ifds::GrantStartDate, dstrStartDate, idDataGroup, false);
		bfIter.getObject()->getField(ifds::GrantEndDate, dstrEndDate, idDataGroup, false);
		bfIter.getObject()->getField(ifds::GrantGBCD, dstrGBCD, idDataGroup, false);

		dstrRESPNotlType.upperCase().stripAll();
		dstrStartDate.upperCase().stripAll();
		dstrEndDate.upperCase().stripAll();
		dstrGBCD.upperCase().stripAll();

		if (dstrRESPNotlType == respNotlType && dstrGBCD == I_("Y")) 
		{
			if (!dstrTradeDate.empty())
			{
				bIsGrantTypeClient = DSTCommonFunctions::CompareDates (dstrStartDate, dstrTradeDate) == DSTCommonFunctions::FIRST_EARLIER &&
									 DSTCommonFunctions::CompareDates (dstrEndDate,   dstrTradeDate) == DSTCommonFunctions::SECOND_EARLIER;
			}
			else 
				bIsGrantTypeClient = true;

			break;
		}
		++bfIter;
	}

	return bIsGrantTypeClient;
}


