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
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : InterestSegmentList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "InterestSegmentList.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0422_vw.hpp>
#include <ifastdataimpl\dse_dstc0422_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0422_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INTEREST_SEGMENT_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME	= I_( "InterestSegmentList" );
}

namespace ifds
{

}

namespace CND
{  
   extern const long ERR_INVALID_FUND_CLASS_CODES;
}

//******************************************************************************
InterestSegmentList::InterestSegmentList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0422_REQ)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	setObjectAsList ();
}

//******************************************************************************
InterestSegmentList::~InterestSegmentList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY InterestSegmentList::init (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InterestSegmentList::init( const DString& dstrAccountNum, 
									const DString& dstrIntInvestId, 
									const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	DString mgmtCoIdOut, dstrInquire;
	dstrInquire = I_("INQUIRE");
	
	//m_requestData.setElementValue( ifds::InputAcctNum, dstrAccountNum);
	m_requestData.setElementValue( ifds::IntInvestId, dstrIntInvestId);
	//m_requestData.setElementValue( ifds::Inquiry, dstrInquire);
	m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	m_requestData.setElementValue( ifds::Track, I_("N") );

	ReceiveData (DSTC_REQUEST::INTEREST_SEGMENT_INQUIRY, m_requestData,
				 ifds::DSTC0422_VW, DSTCRequestor(getSecurity(), true, true), false);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InterestSegmentList.cpp-arc  $
// 
//    Rev 1.2   Jan 13 2012 10:47:48   wp040100
// P0186477/FN03 - GIA - Investment History Changes - Bug fixes.
// 
//    Rev 1.1   Dec 12 2011 11:59:40   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.0   Dec 09 2011 19:47:02   wp040100
// Initial revision.
// 
//
//
 * 
 * 
// 
*/
