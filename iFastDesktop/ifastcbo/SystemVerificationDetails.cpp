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
// ^FILE   : SystemVerificationDetails.cpp
// ^AUTHOR : 
// ^DATE   : Nov, 2009
//
// ^CLASS    : SystemVerificationDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "SystemVerificationDetails.hpp"

#include <ifastdataimpl\dse_dstc0400_req.hpp>
#include <ifastdataimpl\dse_dstc0400_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "SystemVerificationDetails" );
}

namespace ifds
{
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ifds::VerifyCategory,	BFCBO::NONE, 0 },
	{ifds::VerifyLevel,		BFCBO::NONE, 0 },
	{ifds::VerifyField,		BFCBO::NONE, 0 },
	{ifds::Active,			BFCBO::NONE, 0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
SystemVerificationDetails::SystemVerificationDetails( BFAbstractCBO &parent )
: MFCanBFCbo( parent )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//******************************************************************************************
SystemVerificationDetails::~SystemVerificationDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY SystemVerificationDetails::init( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY SystemVerificationDetails::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SystemVerificationDetails.cpp-arc  $
// 
//    Rev 1.1   Nov 17 2009 15:12:36   jankovii
// PET0166583 FN01 Static Data Changes Banking 
// 
//    Rev 1.0   Nov 16 2009 06:12:42   dchatcha
// Initial revision.
// 
