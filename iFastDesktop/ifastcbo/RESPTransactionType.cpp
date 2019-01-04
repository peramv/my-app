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
// ^FILE   : RESPTransactionType.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPTransactionType
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPTransactionType.hpp"

#include <ifastdataimpl\dse_dstc0410_req.hpp>
#include <ifastdataimpl\dse_dstc0410_vw.hpp>
#include <ifastdataimpl\dse_dstc0410_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "RESPTransactionType" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ifds::TransType,		BFCBO::NONE, 0 },
	{ifds::RedCode,			BFCBO::NONE, 0 },
	{ifds::DepositType,		BFCBO::NONE, 0 },
	{ifds::TransRecId,		BFCBO::NONE, 0 },
	{ifds::TfrStat,			BFCBO::NONE, 0 },
	{ifds::RepHRDC,			BFCBO::NONE, 0 },
	{ifds::TransTypeDesc,	BFCBO::NONE, 0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
RESPTransactionType::RESPTransactionType( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
RESPTransactionType::~RESPTransactionType()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY RESPTransactionType::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY RESPTransactionType::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}
