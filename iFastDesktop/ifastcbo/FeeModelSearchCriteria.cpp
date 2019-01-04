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
//    Copyright 2002 by International Financial
//
//
//******************************************************************************
//
// ^FILE   : FeeModelSearchCriteria.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FeeModelSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeModelSearchCriteria.hpp"

#include <ifastdataimpl\dse_dstc0448_req.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME                  = I_( "FeeModelSearchCriteria" );
   const I_CHAR * const YES                        = I_("Y");
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId SrcHoldingCompCode;
   extern CLASS_IMPORT const BFTextFieldId SrcHoldingCompName;
   extern CLASS_IMPORT const BFTextFieldId SrcFeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId SrcFeeModelDesc;
   extern CLASS_IMPORT const BFDateFieldId AsofDate;
   extern CLASS_IMPORT const BFTextFieldId SearchAll;
}


//  Field DD Id,                    State Flags,         Group Flags       

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   { ifds::SrcHoldingCompCode, BFCBO::NONE,  0 },
   { ifds::SrcHoldingCompName, BFCBO::NONE,  0 },
   { ifds::SrcFeeModelCode,    BFCBO::NONE,  0 },
   { ifds::SrcFeeModelDesc,    BFCBO::NONE,  0 },
   { ifds::SearchAll,          BFCBO::NONE,  0 },
   { ifds::AsofDate,           BFCBO::NONE,  0 },
   { ifds::HoldingCompCode,    BFCBO::NONE,  0 },
   { ifds::HoldingCompName,    BFCBO::NONE,  0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FeeModelSearchCriteria::FeeModelSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

}
//******************************************************************************************
FeeModelSearchCriteria::~FeeModelSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY FeeModelSearchCriteria::Init()

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );

   return(GETCURRENTHIGHESTSEVERITY());
   
}

