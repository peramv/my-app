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
// ^FILE   : FATCAMasterList.cpp
// ^AUTHOR :
// ^DATE   : 08 January 2014
//
// ^CLASS    : FATCAMasterList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FATCAMasterList.hpp"
#include "FATCAMaster.hpp"
#include <ifastdataimpl\dse_dstc0460_vw.hpp>
#include <ifastdataimpl\dse_dstc0460_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest FATCA_MASTER_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_("FATCAMasterList");
}

namespace ifds
{
//	extern CLASS_IMPORT const BFNumericFieldId EntityId;
}

namespace CND
{
	/*extern const long ERR_DATA_NOT_FOUND;
	extern const long ERR_DATE_RANGE_OVERLAP;*/
}





//******************************************************************************
FATCAMasterList::FATCAMasterList(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	setObjectAsList( );
}


//******************************************************************************
FATCAMasterList::~FATCAMasterList( void )
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY FATCAMasterList::init(const DString &dstrTrack, 
							   const DString &dstrPageName)                             
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	BFData requestData(ifds::DSTC0460_REQ);
	DString mgmtCoIdOut;

	requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	requestData.setElementValue(ifds::Track, dstrTrack);
	requestData.setElementValue(ifds::Activity, dstrPageName);


	ReceiveData(DSTC_REQUEST::FATCA_MASTER_INQUIRY, requestData, ifds::DSTC0460_VW, DSTCRequestor(getSecurity(), true));

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY FATCAMasterList::init(const BFData& data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( data )" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY FATCAMasterList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

	pObjOut = new FATCAMaster( *this );
	((FATCAMaster*)(pObjOut))->init(const_cast<BFData&>(data));

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY FATCAMasterList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

	FATCAMaster *pFATCAMaster = new FATCAMaster(*this);

	pFATCAMaster->initNew(idDataGroup);
	pBase = pFATCAMaster;

	return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************
SEVERITY FATCAMasterList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	//validateOverlappingDateRanges(idDataGroup);

	return(GETCURRENTHIGHESTSEVERITY());
}

