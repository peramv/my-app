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
// ^FILE   : RESPPACDateCalculator.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPPACDateCalculator
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPPACDateCalculator.hpp"
#include "mgmtco.hpp"
#include "funddetail.hpp"
#include <ifastdataimpl\dse_dstc0440_req.hpp>
#include <ifastdataimpl\dse_dstc0440_vw.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest RESP_PAC_DATE_CALCULATION;
}

namespace  
{
	const I_CHAR * const CLASSNAME		= I_( "RESPPACDateCalculator" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	//   Field DD Id,		State Flags,	Group Flags 
	{ ifds::PACDeff,           BFCBO::NONE,	0 },
	{ ifds::NextProcessDate,	BFCBO::NONE,	0 },
};

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId ContractType;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,    State Flags,         Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
RESPPACDateCalculator::RESPPACDateCalculator( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
RESPPACDateCalculator::~RESPPACDateCalculator()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************
SEVERITY RESPPACDateCalculator::init(const DString &dstrAcctCommitMstrUUID,
					                      const DString &dstrPACDeff,
					                      const DString &dstrPACDrawDeff,
					                      const DString &dstrTrack /*= I_("N")*/,
					                      const DString &dstrPageName /*= NULL_STRING*/)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   
	BFData queryData(ifds::DSTC0440_REQ);
	BFData *receivedData = new BFData(ifds::DSTC0440_VW);
	DString mgmtCoIdOut;
   
	queryData.setElementValue( ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
	queryData.setElementValue( ifds::Track,          dstrTrack );
	queryData.setElementValue( ifds::Activity,       dstrPageName );
 
	queryData.setElementValue( ifds::AcctCommitMstrUUID,	dstrAcctCommitMstrUUID);
	queryData.setElementValue( ifds::PACDeff,             dstrPACDeff);
	queryData.setElementValue( ifds::PACDrawDeff,		   dstrPACDrawDeff);
								
	ReceiveData (DSTC_REQUEST::RESP_PAC_DATE_CALCULATION, queryData,  *receivedData, DSTCRequestor (getSecurity()));

	return GETCURRENTHIGHESTSEVERITY();
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPPACDateCalculator.cpp-arc  $
// 
//    Rev 1.0   Jun 26 2012 17:32:18   if991250
// Initial revision.
// 
// 
*/


