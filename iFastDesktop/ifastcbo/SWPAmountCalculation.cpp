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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : SWPAmountCalculation.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SWPAmountCalculation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "SWPAmountCalculation.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0437_req.hpp>
#include <ifastdataimpl\dse_dstc0437_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMOUNT_CALCULATION;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "SWPAmountCalculation" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
	//   Field DD Id,				State Flags,	Group Flags 
	{ ifds::SWPCalculatedAmount,	BFCBO::NONE,	0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,    State Flags,         Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
SWPAmountCalculation::SWPAmountCalculation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
SWPAmountCalculation::~SWPAmountCalculation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************
SEVERITY SWPAmountCalculation::init(const DString &accountNum,
									const DString &amountType,
									const DString &effectiveDate,
									const DString &stopDate,
									const DString &endOfMonth,
									const DString &january,
									const DString &february,        
									const DString &march,
									const DString &april,       
									const DString &may,
									const DString &june,       
									const DString &july,
									const DString &august,
									const DString &september,
									const DString &october,
									const DString &november,
									const DString &december,
									const DString &dstrTrack /*= I_("N")*/,
									const DString &dstrPageName /*= NULL_STRING*/)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   
	BFData queryData(ifds::DSTC0437_REQ);
	BFData *receivedData = new BFData(ifds::DSTC0437_VW);
	DString mgmtCoIdOut;
   
	queryData.setElementValue( ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
	queryData.setElementValue( ifds::Track,          dstrTrack );
	queryData.setElementValue( ifds::Activity,       dstrPageName );
 
	queryData.setElementValue( ifds::AccountNum,	accountNum );
	queryData.setElementValue( ifds::AmountType,    amountType );
	queryData.setElementValue( ifds::EffectiveDate, effectiveDate, false, false );
	queryData.setElementValue( ifds::StopDate,      stopDate );
	queryData.setElementValue( ifds::EndOfMonth,    endOfMonth );
	queryData.setElementValue( ifds::January,       january );
	queryData.setElementValue( ifds::February,		february );
	queryData.setElementValue( ifds::March,			march );
	queryData.setElementValue( ifds::April,			april );
	queryData.setElementValue( ifds::May,			may );
	queryData.setElementValue( ifds::June,			june );
	queryData.setElementValue( ifds::July,			july );
	queryData.setElementValue( ifds::August,        august );
	queryData.setElementValue( ifds::September,     september );
	queryData.setElementValue( ifds::October,       october );
	queryData.setElementValue( ifds::November,      november );
	queryData.setElementValue( ifds::December,      december );
									
	ReceiveData (DSTC_REQUEST::AMOUNT_CALCULATION, queryData,  *receivedData, DSTCRequestor (getSecurity()));

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void SWPAmountCalculation::buildKey (const DString &accountNum,
									 const DString &amountType, 
									 const DString &effectiveDate,    
									 const DString &stopDate,
									 const DString &endOfMonth,
									 const DString &january,
									 const DString &february,        
									 const DString &march,
									 const DString &april,       
									 const DString &may,
									 const DString &june,       
									 const DString &july,
									 const DString &august,
  									 const DString &september,
  									 const DString &october,
  									 const DString &november,
  									 const DString &december,
									 DString &strKey)
{
   DString	dstrAccountNum (accountNum),
	        dstrAmountType (amountType), 
			dstrEffectiveDate (effectiveDate), 
			dstrStopDate (stopDate), 
			dstrEndOfMonth (endOfMonth),
			dstrJanuary (january),
			dstrFebruary (february),
			dstrMarch (march),
			dstrApril (april),       
			dstrMay (may),
			dstrJune (june),       
			dstrJuly (july),
			dstrAugust (august),
			dstrSeptember (september),
			dstrOctober (october),
			dstrNovember (november),
			dstrDecember (december);

   strKey = DString (I_("SWPAmountCalculation_")) + 
			I_("AccountNum=") + dstrAccountNum + I_(";") +
			I_("AmountType=") + dstrAmountType + I_(";") +
			I_("EffectiveDate=") + dstrEffectiveDate + I_(";") +
			I_("StopDate=") + dstrStopDate + I_(";") +
			I_("EndOfMonth=") + dstrEndOfMonth + I_(";") +
			I_("Jan=") + dstrJanuary + I_(";") +
			I_("Feb=") + dstrFebruary + I_(";") +
			I_("Mar=") + dstrMarch + I_(";") +
			I_("Apr=") + dstrApril + I_(";") +
			I_("May=") + dstrMay + I_(";") +
			I_("Jun=") + dstrJune + I_(";") +
			I_("Jul=") + dstrJuly + I_(";") +
			I_("Aug=") + dstrAugust + I_(";") +
			I_("Sep=") + dstrSeptember + I_(";") +
			I_("Oct=") + dstrOctober + I_(";") +
			I_("Nov=") + dstrNovember + I_(";") +
			I_("Dec=") + dstrDecember + I_(";");
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SWPAmountCalculation.cpp-arc  $
// 
//    Rev 1.0   May 11 2012 13:18:00   jankovii
// Initial revision.
// 
 
*/


