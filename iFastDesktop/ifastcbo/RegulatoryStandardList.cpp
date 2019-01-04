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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RegulatoryStandardList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RegulatoryStandardList.hpp"
#include "RegulatoryStandard.hpp"

#include <ifastdataimpl\dse_dstc0388_req.hpp>
#include <ifastdataimpl\dse_dstc0388_vw.hpp>
#include <ifastdataimpl\dse_dstc0388_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REGULATORY_STANDARDS;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME  = I_( "RegulatoryStandardList" );
}


//******************************************************************************
RegulatoryStandardList::RegulatoryStandardList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), _requestData(ifds::DSTC0388_REQ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}


//******************************************************************************
RegulatoryStandardList::~RegulatoryStandardList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//********************************************************************************
SEVERITY RegulatoryStandardList::init( const DString& dstrTypeOfInvestor,
									   const DString& dstrInvsetOnBehalf,
									   const DString& dstrCountry,
                                       const DString& dstrAcctEffDate,
                                       const DString& dstrTrack,
                                       const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init( int, DString& )"));

	DString mgmtCoIdOut;

	_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	_requestData.setElementValue( ifds::Track, dstrTrack );
	_requestData.setElementValue( ifds::Activity, dstrPageName );
	_requestData.setElementValue( ifds::TypeOfInvestor, dstrTypeOfInvestor);
	_requestData.setElementValue( ifds::InvestingOnBehalf, dstrInvsetOnBehalf);
	_requestData.setElementValue( ifds::CountryCode, dstrCountry);
   _requestData.setElementValue( ifds::AcctEffDate, dstrAcctEffDate);
 
	ReceiveData( DSTC_REQUEST::REGULATORY_STANDARDS, _requestData, ifds::DSTC0388_VW, DSTCRequestor( getSecurity(), true));
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RegulatoryStandardList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY RegulatoryStandardList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
    pBase = new RegulatoryStandard(*this );
    ((RegulatoryStandard* )pBase)->initNew(idDataGroup );
      
	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY RegulatoryStandardList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
   pObjOut = new RegulatoryStandard( *this );
   ((RegulatoryStandard* )pObjOut)->init(const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************************
void RegulatoryStandardList::getSubstitionList(DString& regStandardSubList, const BFDataGroupId& idDataGroup)
{
	DString	dstrRegStandardName, dstrRegStandardId;

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

    while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();
        if( pObj )
        {
            pObj->getField(ifds::RegStandardName, dstrRegStandardName,idDataGroup,false );
            pObj->getField(ifds::RegStandardId, dstrRegStandardId,idDataGroup,false );
            dstrRegStandardId.strip();
            dstrRegStandardName.strip();
            
			if (dstrRegStandardName == NULL_STRING || dstrRegStandardName.empty ())
			{
				++iter;
				continue;
			}

			dstrRegStandardName.stripAll (';');
			
		    regStandardSubList += dstrRegStandardId + I_("=") + dstrRegStandardName + I_(";");			
        }
        ++iter;
     }    
}

//*********************************************************************************************

