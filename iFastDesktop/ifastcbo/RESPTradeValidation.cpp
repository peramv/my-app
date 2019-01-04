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
// Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPTradeValidation.cpp
// ^AUTHOR : 
// ^DATE   : Aprl, 2010
//
// ^CLASS    : RESPTradeValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPTradeValidation.hpp"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

#include <ifastdataimpl\dse_dstc0405_req.hpp>
#include <ifastdataimpl\dse_dstc0405_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "RESPTradeValidation" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFTextFieldId WarnParam1;
   extern CLASS_IMPORT const BFTextFieldId WarnParam2;
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

//******************************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,          Group Flags
   { ifds::WarnCode,                   BFCBO::NONE,               0 }, 
   { ifds::WarnParam1,                 BFCBO::NONE,               0 }, 
   { ifds::WarnParam2,                 BFCBO::NONE,               0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
RESPTradeValidation::RESPTradeValidation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//******************************************************************************************
RESPTradeValidation::~RESPTradeValidation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY RESPTradeValidation::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTradeValidation.cpp-arc  $
// 
//    Rev 1.0   Apr 21 2010 23:25:14   dchatcha
// Initial revision.
//
*/
