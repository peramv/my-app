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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : BatchInfo.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : BatchInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "BatchInfo.hpp"

#include <ifastdataimpl\dse_dstc0394_req.hpp> 
#include <ifastdataimpl\dse_dstc0394_vw.hpp>
#include <ifastdataimpl\dse_dstc0394_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "BatchInfo" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId BatchName;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ifds::BatchID,		BFCBO::NONE, 0 },
	{ifds::BatchStatus,	BFCBO::NONE, 0 },
	{ifds::BatchUser,	BFCBO::NONE, 0 },
	{ifds::BatchTrace,	BFCBO::NONE, 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
BatchInfo::BatchInfo( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
BatchInfo::~BatchInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY BatchInfo::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY BatchInfo::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

/* $Log::
*/