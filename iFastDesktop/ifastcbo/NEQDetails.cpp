//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : NEQDetails.cpp
// ^AUTHOR : 
// ^DATE   : Nov, 2009
//
// ^CLASS    : NEQDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "NEQDetails.hpp"

#include <ifastdataimpl\dse_dstc0408_req.hpp>
#include <ifastdataimpl\dse_dstc0408_vw.hpp>
#include <ifastdataimpl\dse_dstc0408_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME	= I_( "NEQDetails" );
}

namespace ifds
{ 
   extern CLASS_IMPORT const BFTextFieldId NEQID;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId WhereUse;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ifds::NEQID,		BFCBO::NONE, 0 },
	{ifds::Name,		BFCBO::NONE, 0 },
	{ifds::WhereUse,	BFCBO::NONE, 0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
NEQDetails::NEQDetails( BFAbstractCBO &parent )
: MFCanBFCbo( parent )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************************
NEQDetails::~NEQDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY NEQDetails::init( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY NEQDetails::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );

   return GETCURRENTHIGHESTSEVERITY();
}
//*****************************************************************************
//
// $Log::   
// 
