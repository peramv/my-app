//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : NEQDetailsList.cpp
// ^AUTHOR : 
// ^DATE   : Nov, 2009
//
// ^CLASS    : NEQDetailsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0408_vw.hpp>
#include <ifastdataimpl\dse_dstc0408_req.hpp>
#include <ifastdataimpl\dse_dstc0408_vwrepeat_record.hpp>

#include "NEQDetails.hpp"
#include "NEQDetailsList.hpp"

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest RESP_NEQ_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME		= I_( "NEQDetailsList" );
   const I_CHAR * const NA				= I_( "0=0000000000-N/A;" );
   const I_CHAR * const EXT_PROVIDER	= I_( "12" );
}

//******************************************************************************
NEQDetailsList::NEQDetailsList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	setObjectAsList( );
}

//******************************************************************************
NEQDetailsList::~NEQDetailsList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY NEQDetailsList::init( const DString& dstrTrack,
                               const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init( DString&, BFDataGroupId& )"));

	DString mgmtCoIdOut;
	BFData requestData (ifds::DSTC0408_REQ);

	requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	requestData.setElementValue (ifds::Track, dstrTrack);
	requestData.setElementValue (ifds::Activity, dstrPageName);

	ReceiveData( DSTC_REQUEST::RESP_NEQ_INQUIRY, requestData, ifds::DSTC0408_VW, DSTCRequestor (getSecurity(), true));

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY NEQDetailsList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

	pObjOut = new  NEQDetails( *this );
	((NEQDetails*) pObjOut )->init( data );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY NEQDetailsList::getNEQList( DString &dstrNEQList, 
									 const DString dstrWhereUse, 
									 const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getNEQList" ) );

  	DString dstrNEQId, dstrName, dstrWhereUseCode;

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

	if (dstrWhereUse == EXT_PROVIDER)
	{
		dstrNEQList = NA;
	}

	while( !iter.end() )
	{
		BFAbstractCBO* pObj = iter.getObject();
	    
		if( pObj )
		{
			pObj->getField (ifds::NEQID, dstrNEQId, idDataGroup,false );
			pObj->getField (ifds::Name, dstrName, idDataGroup,false );
			pObj->getField (ifds::WhereUse, dstrWhereUseCode, idDataGroup,false );
	            
			dstrNEQId.strip();
			dstrName.strip();
			dstrWhereUseCode.strip();
	            
			if (dstrWhereUseCode == dstrWhereUse )
			{
				dstrNEQList += dstrNEQId + I_("=") +  dstrNEQId + I_("-") + dstrName + I_(";");			

			}
		}

		++iter;
	}    

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY NEQDetailsList::getNEQId( DString &dstrNEQId, 
								   const DString dstrWhereUse, 
								   const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getNEQId" ) );

  	DString dstrWhereUseCode;

	dstrNEQId = NULL_STRING;

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

	while( !iter.end() )
	{
		BFAbstractCBO* pObj = iter.getObject();
	    
		if( pObj )
		{
			pObj->getField (ifds::NEQID, dstrNEQId, idDataGroup,false );
			pObj->getField (ifds::WhereUse, dstrWhereUseCode, idDataGroup,false );
	            
			dstrNEQId.strip();
			dstrWhereUseCode.strip();
	            
			if (dstrWhereUseCode == dstrWhereUse )
			{
				break;		
			}
		}

		++iter;
	}    

	return GETCURRENTHIGHESTSEVERITY();
}
// $Log::  
// 
