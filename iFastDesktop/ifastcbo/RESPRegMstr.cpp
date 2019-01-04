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
// ^FILE   : RESPRegMstr.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPRegMstr
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPRegMstr.hpp"

#include <bfutil\bfdate.hpp>
#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "RESPRegMstrList.hpp"


namespace
{
	const I_CHAR * const CLASSNAME				= I_("RESPRegMstr");
	const I_CHAR * const YES					= I_("Y"); 
	const I_CHAR * const NO						= I_("N");
}

namespace ifds
{

}

namespace CND
{  

}

namespace IFASTERR
{
	
}

//****************************************************************************
RESPRegMstr::RESPRegMstr (BFAbstractCBO &parent) :
MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}


//****************************************************************************
RESPRegMstr::~RESPRegMstr()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//****************************************************************************
SEVERITY RESPRegMstr::init (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	commonInit(BF::HOST);

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY RESPRegMstr::initNew (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY RESPRegMstr::commonInit(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
void RESPRegMstr::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{

}


//********************************************************************************************
SEVERITY RESPRegMstr::doValidateField(const BFFieldId& idField,
										 const DString& strValue,
										 const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

	return GETCURRENTHIGHESTSEVERITY();
}


//********************************************************************************************
SEVERITY RESPRegMstr::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY RESPRegMstr::doApplyRelatedChanges (const BFFieldId &idField, 
												  const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
	
	return GETCURRENTHIGHESTSEVERITY();
}

