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
// ^FILE   : MsgDetailList.cpp
// ^CLASS  : MsgDetailList
//
//******************************************************************************

#include "stdafx.h"
#include "MsgDetail.hpp"
#include "MsgDetailList.hpp"
#include <ifastdataimpl\dse_dstc0334_req.hpp>
#include <ifastdataimpl\dse_dstc0334_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MsgDetailList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MSG_DETAIL_LIST;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
     { ifds::ActivityID,      BFCBO::NONE,               0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

MsgDetailList::MsgDetailList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

MsgDetailList::~MsgDetailList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MsgDetailList::initExisting(const DString& dstrTrack, const DString& dstrPageName,
                                         const DString& _dstrActivityID )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   DString dstrActivityID( _dstrActivityID );

   BFData* pReqList =  new BFData( ifds::DSTC0334_REQ );

   DString mgmtCoIdOut;
   pReqList->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   pReqList->setElementValue( ifds::NextKey, NULL_STRING );
   pReqList->setElementValue( ifds::Track, dstrTrack );
	pReqList->setElementValue( ifds::ActivityID, dstrActivityID );
   pReqList->setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::MSG_DETAIL_LIST, *pReqList, ifds::DSTC0334_VW, 
               DSTCRequestor( getSecurity(), true /*allResults*/, true /*noDataIsErrorCondition*/), true /*InsertLast*/);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY MsgDetailList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new MsgDetail ( *this );
   dynamic_cast< MsgDetail * >( pObjOut )->initExisting( data );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgDetailList.cpp-arc  $
// 
//    Rev 1.1   Feb 21 2005 16:29:16   hernando
// PET1117 FN66-68 - Changed values passed in for DSTCRequestor and ReceiveData.
