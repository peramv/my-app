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
// ^FILE   : FinInstRegDetl.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : FinInstRegDetl
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FinInstRegDetl.hpp"

#include <bfutil\bfdate.hpp>
#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace
{
	const I_CHAR * const CLASSNAME       = I_("FinInstRegDetl");
	const I_CHAR * const YES             = I_("Y"); 
	const I_CHAR * const NO              = I_("N"); 
}

namespace ifds
{
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFTextFieldId FILevel;
	extern CLASS_IMPORT const BFTextFieldId FICode;
	extern CLASS_IMPORT const BFTextFieldId FICategory;
	extern CLASS_IMPORT const BFTextFieldId ComplyRule;
	extern CLASS_IMPORT const BFTextFieldId ComplyCode;
	extern CLASS_IMPORT const BFTextFieldId Description;
	extern CLASS_IMPORT const BFTextFieldId FinInstRegDetlUUID;
}

namespace CND
{  
	//extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
	//  Field DD Id,              State Flags,    Group Flags 
	{ifds::EffectiveDate,      BFCBO::READ_ONLY,  0 }, 
	{ifds::StopDate,           BFCBO::READ_ONLY,  0 }, 
	{ifds::FILevel,            BFCBO::READ_ONLY,  0 }, 
	{ifds::FICode,             BFCBO::READ_ONLY,  0 }, 
	{ifds::FICategory,         BFCBO::READ_ONLY,  0 }, 
	{ifds::FinInstRegDetlUUID, BFCBO::READ_ONLY,  0 },
	{ifds::ComplyRule,         BFCBO::READ_ONLY,  0 },
	{ifds::ComplyCode,         BFCBO::READ_ONLY,  0 },
	{ifds::Description,        BFCBO::READ_ONLY,  0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
FinInstRegDetl::FinInstRegDetl (BFAbstractCBO &parent) :
MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}


//****************************************************************************
FinInstRegDetl::~FinInstRegDetl()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//****************************************************************************
SEVERITY FinInstRegDetl::init (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	return GETCURRENTHIGHESTSEVERITY();
}