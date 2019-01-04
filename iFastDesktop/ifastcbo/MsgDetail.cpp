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
//    Copyright 2005 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MsgDetail.cpp
// ^CLASS  : MsgDetail
//
//******************************************************************************
#include "stdafx.h"
#include "MsgDetail.hpp"

#include <ifastdataimpl\dse_dstc0334_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MsgDetail" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::MsgID,           BFCBO::NONE,                        0 }, 
   { ifds::MsgType,         BFCBO::NONE,                        0 }, 
   { ifds::MsgSegment,      BFCBO::NONE,                        0 }, 
   { ifds::MsgData,         BFCBO::NONE,                        0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

MsgDetail::MsgDetail( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

MsgDetail::~MsgDetail( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MsgDetail::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );
   attachDataObject( const_cast< BFData & >( data ), false, true ); 
   setFieldReadOnly( ifds::MsgData, BF::HOST, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgDetail.cpp-arc  $
// 
//    Rev 1.0   Feb 21 2005 11:13:20   hernando
// Initial revision.
