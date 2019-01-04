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
//    Copyright 2005 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : MsgEventList.cpp
//
//********************************************************************************
#include "stdafx.h"
#include "MsgEventList.hpp"
#include "MsgEvent.hpp"
#include <ifastdataimpl\dse_dstc0335_vw.hpp>
#include <ifastdataimpl\dse_dstc0335_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MSG_EVENT_LIST;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MsgEventList" );
}

//******************************************************************************

MsgEventList::MsgEventList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), m_requestData( ifds::DSTC0335_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************

MsgEventList::~MsgEventList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MsgEventList::initExisting(const DString& dstrTrack,
                                    const DString& dstrPageName,
                                    const DString& _dstrActivityID,
												const DString& _dstrEnvelopeID
                                   )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   DString dstrActivityID( _dstrActivityID );
	DString dstrEnvelopeID( _dstrEnvelopeID );
   m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );
   m_requestData.setElementValue( ifds::ActivityID, dstrActivityID );
	m_requestData.setElementValue( ifds::EnvelopeID, dstrEnvelopeID );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::MSG_EVENT_LIST, m_requestData, ifds::DSTC0335_VW, DSTCRequestor(getSecurity(), true /*allResults*/, false /*noDataIsErrorCondition*/), true /*InsertLast*/);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MsgEventList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new MsgEvent( *this );
   ((MsgEvent*) pObjOut)->init( data );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**********************************************************************************

void  MsgEventList::getStrKey( DString &strKey, const BFData *data  )
{
   BFCBO::getStrKey( strKey, NULL );
}
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgEventList.cpp-arc  $
// 
//    Rev 1.2   Feb 24 2005 17:32:26   ZHANGCEL
// PET1117- FN66-68 - Added parameter EnvelopeID in function initExist()
// 
//    Rev 1.1   Feb 21 2005 16:30:56   hernando
// PET1117 FN66-68 - Changed values passed in for DSTCRequestor and ReceiveData.
