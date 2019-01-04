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
//    Copyright 2010 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : InvestmentHistoryDetails.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "InvestmentHistoryInterest.hpp"
#include "InvestmentHistoryInterestList.hpp"

#include <ifastdataimpl\dse_dstc0425_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME				= I_( "InvestmentHistoryInterest" );
}

namespace ifds
{
};

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ ifds::InvHisIncomeUUID,					BFCBO::NONE,		0},
	{ ifds::InvHisIntDate,						BFCBO::NONE,		0},
	{ ifds::InvHisIntAmt,						BFCBO::NONE,		0},
	{ ifds::InvestStatus1,						BFCBO::NONE,		0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
InvestmentHistoryInterest::InvestmentHistoryInterest( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
InvestmentHistoryInterest::~InvestmentHistoryInterest()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  


//******************************************************************************
SEVERITY InvestmentHistoryInterest::init (const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject(const_cast<BFData&>(data), false); 
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryInterest.cpp-arc  $
// 
//    Rev 1.3   Apr 18 2012 15:31:00   wp040100
// IN # 2891939 - Added "Forced Indicator" column in Grid 1 and "Status" in Grid 3.
// 
//    Rev 1.2   Dec 01 2011 19:07:34   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.1   Nov 25 2011 13:54:52   wp040100
// P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
