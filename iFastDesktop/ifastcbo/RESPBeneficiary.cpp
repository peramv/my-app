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
// ^FILE   : RESPBeneficiary.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPBeneficiary
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPBeneficiary.hpp"

#include <ifastdataimpl\dse_dstc0411_req.hpp>
#include <ifastdataimpl\dse_dstc0411_vw.hpp>
#include <ifastdataimpl\dse_dstc0411_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "RESPBeneficiary" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ifds::BeneName,	BFCBO::NONE, 0 },
	{ifds::RESPBenefId,	BFCBO::NONE, 0 },
	{ifds::Active,		BFCBO::NONE, 0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
RESPBeneficiary::RESPBeneficiary( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
RESPBeneficiary::~RESPBeneficiary()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY RESPBeneficiary::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY RESPBeneficiary::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}
