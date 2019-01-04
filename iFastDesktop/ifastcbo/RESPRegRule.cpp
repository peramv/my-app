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
// ^FILE		: RESPRegRule.cpp
// ^AUTHOR		: 
// ^DATE		: 
//
// ^CLASS		: RESPRegRule
// ^SUBCLASS	:
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPRegRule.hpp"

#include <bfutil\bfdate.hpp>
#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "RESPRegRuleList.hpp"


namespace
{
	const I_CHAR * const CLASSNAME				= I_("RESPRegRule");
	const I_CHAR * const YES					= I_("Y"); 
	const I_CHAR * const NO						= I_("N");
}

namespace ifds
{

}

//****************************************************************************
RESPRegRule::RESPRegRule (BFAbstractCBO &parent) :
MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
RESPRegRule::~RESPRegRule()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY RESPRegRule::init (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	commonInit(BF::HOST);

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY RESPRegRule::initNew (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY RESPRegRule::commonInit(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

	return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY RESPRegRule::doValidateField(const BFFieldId& idField,
										 const DString& strValue,
										 const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

	return GETCURRENTHIGHESTSEVERITY();
}


//********************************************************************************************
SEVERITY RESPRegRule::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	return GETCURRENTHIGHESTSEVERITY();
}
