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
// ^FILE   : InvestmentHistory.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "InvestmentHistory.hpp"
#include "InvestmentHistoryList.hpp"
#include "InvestmentHistoryDetailsList.hpp"
#include "InvestmentHistoryInterestList.hpp"

#include <ifastdataimpl\dse_dstc0421_vw.hpp>
#include <ifastdataimpl\dse_dstc0425_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME				= I_( "InvestmentHistory" );

   const I_CHAR * const SEARCHALL				= I_( "ALL" );	   //I_( "AL" ); //All
   const I_CHAR * const SEARCH_INV_NUM			= I_( "INVNUM" );  //I_( "IN" ); //Investment Number
   const I_CHAR * const SEARCH_INV_STATUS		= I_( "INVSTAT" ); //I_( "IS" ); //Investment Status

   const I_CHAR * const STATUS_ACTIVE			= I_( "ACTIVE" );
   const I_CHAR * const STATUS_MATURED			= I_( "MATURED" );
   const I_CHAR * const STATUS_CANCELLED		= I_( "CANCELLED" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,								State Flags,		Group Flags 
	{ ifds::IntInvestUUID,						BFCBO::NONE,		0},
	{ ifds::Fund,								BFCBO::NONE,		0},
	{ ifds::Class,								BFCBO::NONE,		0},
	{ ifds::TransNum,							BFCBO::NONE,		0},
	{ ifds::TransId,							BFCBO::NONE,		0},
	{ ifds::InvHisNumber,						BFCBO::NONE,		0},
	{ ifds::InvHisStatus,						BFCBO::NONE,		0},
	{ ifds::InvHisIntCalcMthd,					BFCBO::NONE,		0},
	{ ifds::InvHisIntRateType,					BFCBO::NONE,		0},
	{ ifds::InvHisTerm,							BFCBO::NONE,		0},
	{ ifds::InvHisIntRate,						BFCBO::NONE,		0},
	{ ifds::InvHisDepDate,						BFCBO::NONE,		0},
	{ ifds::InvHisMatDate,						BFCBO::NONE,		0},
	{ ifds::InvHisPrincipal,					BFCBO::NONE,		0},
	{ ifds::InvHisIntFreq,						BFCBO::NONE,		0},
	{ ifds::InvHisCurMktVal,					BFCBO::NONE,		0},
	{ ifds::InvHisLastIntCrdDate,				BFCBO::NONE,		0},
	{ ifds::InvHisAcurdToDate,					BFCBO::NONE,		0},
	{ ifds::InvHisLotId,						BFCBO::NONE,		0},
	{ ifds::InvHisInvestId,						BFCBO::NONE,		0},
	{ ifds::IntRateType,						BFCBO::NONE,		0},
	{ ifds::InvestStatus1,						BFCBO::NONE,		0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
InvestmentHistory::InvestmentHistory( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
InvestmentHistory::~InvestmentHistory()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************
SEVERITY InvestmentHistory::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject (const_cast<BFData&>(data), false); 

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY InvestmentHistory::getInvestmentDetails ( InvestmentHistoryDetailsList *&pInvestmentHistoryDetailsList, 
												   const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getInvestmentDetails"));

	//Check CBOBase to see if we've already built it; Otherwise, create and store with base
	pInvestmentHistoryDetailsList = 
		dynamic_cast<InvestmentHistoryDetailsList*> (getObject (I_("InvestmentHistoryDetailsList"), idDataGroup));
	
	if (!pInvestmentHistoryDetailsList)
	{
		DString  dstrInvHisLotId;
		getField (ifds::InvHisLotId, dstrInvHisLotId, idDataGroup, false);
		dstrInvHisLotId.strip();
		
		pInvestmentHistoryDetailsList = new InvestmentHistoryDetailsList (*this);
		if( pInvestmentHistoryDetailsList->init(dstrInvHisLotId) <= WARNING)
		{
			setObject (pInvestmentHistoryDetailsList, I_("InvestmentHistoryDetailsList"), OBJ_ACTIVITY_NONE, idDataGroup);
		}
		else
		{
			delete pInvestmentHistoryDetailsList;
			pInvestmentHistoryDetailsList = NULL;
		}
	}

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY InvestmentHistory::getInvestmentInterestList( InvestmentHistoryInterestList *&pInvestmentHistoryInterestList, 
													   const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getInvestmentInterestList"));

	//Check CBOBase to see if we've already built it; Otherwise, create and store with base
	pInvestmentHistoryInterestList = 
		dynamic_cast<InvestmentHistoryInterestList*>( getObject( I_( "InvestmentHistoryInterestList" ), idDataGroup ) );

	if (!pInvestmentHistoryInterestList)
	{		
		DString dstrInvHisInvestId;
		getField (ifds::InvHisInvestId, dstrInvHisInvestId, idDataGroup, false);
		dstrInvHisInvestId.strip();

		pInvestmentHistoryInterestList = new InvestmentHistoryInterestList(*this);
		if( pInvestmentHistoryInterestList->init (dstrInvHisInvestId) <= WARNING )
		{
			setObject (pInvestmentHistoryInterestList, I_("InvestmentHistoryInterestList"), OBJ_ACTIVITY_NONE, idDataGroup);
		}
		else
		{
			delete pInvestmentHistoryInterestList;
			pInvestmentHistoryInterestList = NULL;
		}
	}

   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistory.cpp-arc  $
// 
//    Rev 1.8   Apr 18 2012 15:31:36   wp040100
// IN # 2891939 - Added "Forced Indicator" column in Grid 1 and "Status" in Grid 3.
// 
//    Rev 1.7   Dec 09 2011 20:06:02   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.6   Dec 01 2011 20:38:46   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.5   Dec 01 2011 19:08:16   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.4   Nov 25 2011 17:40:42   wp040100
// P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
