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
//    Copyright 2003 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MsgActivityList.cpp
// ^CLASS  : MsgActivityList
//
//******************************************************************************

#include "stdafx.h"
#include "MsgActivity.hpp"
#include "MsgActivityList.hpp"
#include <ifastdataimpl\dse_dstc0336_req.hpp>
#include <ifastdataimpl\dse_dstc0336_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MsgActivityList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MSG_ACTIVITY_LIST;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
    { ifds::ProcessID,        BFCBO::NONE,               0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

MsgActivityList::MsgActivityList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

MsgActivityList::~MsgActivityList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MsgActivityList::initExisting(const DString& dstrTrack, const DString& dstrPageName,
                                         const DString& _dstrProcessID )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   DString dstrProcessID( _dstrProcessID );

   BFData* pReqList =  new BFData( ifds::DSTC0336_REQ );

   DString mgmtCoIdOut;
   pReqList->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   pReqList->setElementValue( ifds::CompanyCode, getMgmtCoId( mgmtCoIdOut ) );
   pReqList->setElementValue( ifds::NextKey, NULL_STRING );
   pReqList->setElementValue( ifds::Track, dstrTrack );
	pReqList->setElementValue( ifds::ProcessID, dstrProcessID );
   pReqList->setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::MSG_ACTIVITY_LIST, *pReqList, ifds::DSTC0336_VW, 
               DSTCRequestor( getSecurity(), true /*allResults*/), true /*InsertLast*/);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY MsgActivityList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new MsgActivity ( *this );
   dynamic_cast< MsgActivity * >( pObjOut )->initExisting( data );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgActivityList.cpp-arc  $
// 
//    Rev 1.1   Feb 21 2005 16:28:28   hernando
// PET1117 FN66-68 - Changed values passed in for DSTCRequestor and ReceiveData.
