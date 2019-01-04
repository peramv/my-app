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
// ^FILE   : MsgEvent.cpp
//
//********************************************************************************
#include "stdafx.h"
#include "MsgEvent.hpp"
#include "MsgEventList.hpp"

#include <ifastdataimpl\dse_dstc0335_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MsgEvent" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::EventCode,     BFCBO::NONE,                     0 }, 
   { ifds::EventType,     BFCBO::NONE,                     0 },
   { ifds::EventText,     BFCBO::NONE,                     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

MsgEvent::MsgEvent( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

MsgEvent::~MsgEvent()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY MsgEvent::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
//   clearUpdatedFlags( BF::HOST );  // Here in case we setFields before this.

	return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgEvent.cpp-arc  $
// 
//    Rev 1.0   Feb 21 2005 11:13:48   hernando
// Initial revision.
