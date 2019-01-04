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
//    Copyright 2007 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundClassDistribOptions.cpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : 06/04/07
//
// ^CLASS    : FundClassDistribOptionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0379_req.hpp>
#include <ifastdataimpl\dse_dstc0379_vw.hpp>
#include <ifastdataimpl\dse_dstc0379_vwrepeat_record.hpp>


#include "dstcworksession.hpp"
#include "FundClassDistribOptionsList.hpp"
#include "FundClassDistribOptions.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundClassDistribOptionsList" );  
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DISTRIB_OPTIONS;
}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
  
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId DistributionTransType;
}

FundClassDistribOptionsList::FundClassDistribOptionsList(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

FundClassDistribOptionsList::~FundClassDistribOptionsList(void)
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


void FundClassDistribOptionsList::getStrKey( DString &strKey, const BFData *data)
{
	TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

	if( data != NULL )
	{
		DString strDistribType;
		strDistribType = data->getElementValue( ifds::DistribType );
		strKey = strDistribType.strip();
	}
	else
	{
		BFCBO::getStrKey( strKey, NULL );
	}

}

SEVERITY FundClassDistribOptionsList::init( const DString &strDistribType,
                                            const DString &strFundCode,
                                            const DString &strClassCode
										   )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   		BFData requestData(ifds::DSTC0379_REQ);
		BFData *responseData = new BFData(ifds::DSTC0379_VW);

		DString mgmtCoIdOut;
		requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
		requestData.setElementValue( ifds::TransType, strDistribType );
		requestData.setElementValue( ifds::FundCode,  strFundCode );
		requestData.setElementValue( ifds::ClassCode, strClassCode );

      ReceiveData( DSTC_REQUEST::DISTRIB_OPTIONS, requestData, *responseData, DSTCRequestor( getSecurity() ) );
	
	return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY FundClassDistribOptionsList::getFundClassDistribOptions( const DString &strDistribType,
																                  const BFDataGroupId& idDataGroup,
																                  FundClassDistribOptions *&pFundClassDistribOptions)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassDistribOptions" ) );

	pFundClassDistribOptions = NULL;
	BFObjIter iterFundClassDistribOptions(*this, idDataGroup);
	DString strKey = strDistribType;
	strKey.strip();
	iterFundClassDistribOptions.positionByKey( strKey );

	if( !iterFundClassDistribOptions.end() )
		// A match was found, get the CBO  
		pFundClassDistribOptions = static_cast<FundClassDistribOptions *>( iterFundClassDistribOptions.getObject());

	return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY FundClassDistribOptionsList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

	pObjOut =  new FundClassDistribOptions( *this );
	((FundClassDistribOptions*)pObjOut)->init( data );

	return(GETCURRENTHIGHESTSEVERITY());
}

