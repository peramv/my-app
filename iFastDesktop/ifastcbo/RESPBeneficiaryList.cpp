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
// ^FILE   : RESPBeneficiaryList.cpp
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
#include "RESPBeneficiaryList.hpp"
#include "RESPBeneficiary.hpp"

#include <ifastdataimpl\dse_dstc0411_req.hpp>
#include <ifastdataimpl\dse_dstc0411_vw.hpp>
#include <ifastdataimpl\dse_dstc0411_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_BENEFICIARY_LIST_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME	= I_( "RESPBeneficiaryList" );
}


//******************************************************************************
RESPBeneficiaryList::RESPBeneficiaryList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), _requestData(ifds::DSTC0411_REQ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}


//******************************************************************************
RESPBeneficiaryList::~RESPBeneficiaryList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//********************************************************************************
SEVERITY RESPBeneficiaryList::init (const DString& dstrAccountNum,
                                         const DString& dstrTrack,
                                         const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init( int, DString& )"));

	DString mgmtCoIdOut;

	_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	_requestData.setElementValue( ifds::Track, dstrTrack );
	_requestData.setElementValue( ifds::Activity, dstrPageName );
	_requestData.setElementValue( ifds::AccountNum, dstrAccountNum);
    _requestData.setElementValue( ifds::NextKey, NULL_STRING );
 
	ReceiveData( DSTC_REQUEST::RESP_BENEFICIARY_LIST_INQUIRY, _requestData, ifds::DSTC0411_VW, DSTCRequestor( getSecurity(), true));
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPBeneficiaryList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY RESPBeneficiaryList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
    pBase = new RESPBeneficiary(*this );
    ((RESPBeneficiary* )pBase)->initNew(idDataGroup );
      
	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY RESPBeneficiaryList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
   pObjOut = new RESPBeneficiary( *this );
   ((RESPBeneficiary* )pObjOut)->init(const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************************
void RESPBeneficiaryList::getSubstitionList(DString& beneficiarySubList, const BFDataGroupId& idDataGroup)
{
	DString	dstrBenefId, dstrBeneName;
	DString dstrAllId = I_("ALL");
	DString dstrAll = I_("All");
	DString dstrAccountLevelId = I_("ACCTLVL");
	DString dstrAccountLevel = I_("Account Level");

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

	beneficiarySubList = dstrAllId + I_("=") + dstrAll + I_(";");
	beneficiarySubList += dstrAccountLevelId + I_("=") + dstrAccountLevel + I_(";");

    while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();
        if( pObj )
        {
            pObj->getField(ifds::RESPBenefId, dstrBenefId,idDataGroup,false );
            pObj->getField(ifds::BeneName, dstrBeneName,idDataGroup,false );
            dstrBenefId.strip();
            dstrBeneName.strip();
           	
		    beneficiarySubList += dstrBenefId + I_("=") + dstrBeneName + I_(";");			
        }
        ++iter;
     }    
}

//*********************************************************************************************

