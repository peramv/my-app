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
// ^FILE   : MessageEnvelopeListcpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/17/2005
//
// ^CLASS    : MessageEnvelopeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "MessageEnvelope.hpp"
#include "MessageEnvelopeList.hpp"
#include <ifastdataimpl\dse_dstc0332_req.hpp>
#include <ifastdataimpl\dse_dstc0332_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MSG_ENVELOPE_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "MessageEnvelopeList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  NetworkID;
	extern CLASS_IMPORT const BFTextFieldId  FileName;
	extern CLASS_IMPORT const BFDateFieldId  StartDate;
	extern CLASS_IMPORT const BFDateFieldId  EndDate;
	extern CLASS_IMPORT const BFTextFieldId  Track;
	extern CLASS_IMPORT const BFTextFieldId  Activity;
}

//******************************************************************************
MessageEnvelopeList::MessageEnvelopeList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************
MessageEnvelopeList::~MessageEnvelopeList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//********************************************************************************
SEVERITY MessageEnvelopeList::init( const DString& dstrNetWorkId, 
										const DString& dstrFileName,
										const DString& dstrStartDate,
										const DString& dstrEndDate,
                              const DString& dstrTrack,
                              const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init( int, DString& )"));

   queryData = ifds::DSTC0332_REQ;

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	queryData.setElementValue( ifds::CompanyCode, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::NetworkID, dstrNetWorkId ); 
	queryData.setElementValue( ifds::FileName, dstrFileName ); 
	queryData.setElementValue( ifds::StartDate, dstrStartDate ); 
	queryData.setElementValue( ifds::EndDate, dstrEndDate ); 
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );
  

   ReceiveData( DSTC_REQUEST::MSG_ENVELOPE_LIST, queryData, ifds::DSTC0332_VW, DSTCRequestor( getSecurity(), false, true ) );
   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MessageEnvelopeList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MessageEnvelopeList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new MessageEnvelope( *this );

   ((MessageEnvelope* )pObjOut)->init( const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MessageEnvelopeList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
   
	//BFData queryData(ifds::DSTC0332_REQ);
   ReceiveData(DSTC_REQUEST::MSG_ENVELOPE_LIST, queryData, ifds::DSTC0332_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MessageEnvelopeList.cpp-arc  $
// 
//    Rev 1.1   Mar 30 2005 17:18:24   ZHANGCEL
// Incident #276685 -- Fix <More> functionality issue
// 
//    Rev 1.0   Feb 24 2005 17:43:26   ZHANGCEL
// Initial revision.
*/