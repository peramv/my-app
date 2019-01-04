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
#include "InvestmentHistoryDetails.hpp"
#include "InvestmentHistoryDetailsList.hpp"

#include <ifastdataimpl\dse_dstc0424_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME				= I_( "InvestmentHistoryDetails" );
}

namespace ifds
{
};

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ ifds::SharelotDetlUUID,					BFCBO::NONE,		0},
	{ ifds::InvHisTransType,					BFCBO::NONE,		0},
	{ ifds::InvHisTradeDate,					BFCBO::NONE,		0},
	{ ifds::InvHisPrincipalGrossMoneyOut,		BFCBO::NONE,		0},
	{ ifds::InvHisMVA,							BFCBO::NONE,		0},
	{ ifds::InvHisAdminFee,						BFCBO::NONE,		0},
	{ ifds::InvHisNetOfFees,					BFCBO::NONE,		0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
InvestmentHistoryDetails::InvestmentHistoryDetails( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
InvestmentHistoryDetails::~InvestmentHistoryDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************
SEVERITY InvestmentHistoryDetails::init (const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject(const_cast<BFData&>(data), false); 
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryDetails.cpp-arc  $
// 
//    Rev 1.1   Nov 25 2011 13:54:10   wp040100
// P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
