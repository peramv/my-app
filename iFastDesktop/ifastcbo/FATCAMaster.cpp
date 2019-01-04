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
// ^FILE   : FATCAMaster.cpp
// ^AUTHOR : 
// ^DATE   : 08 January 2014
//
// ^CLASS    : FATCAMaster
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FATCAMaster.hpp"

#include <bfutil\bfdate.hpp>
#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "FATCAMasterlist.hpp"


namespace
{
	const I_CHAR * const CLASSNAME				= I_("FATCAMaster");
	const I_CHAR * const YES					= I_("Y"); 
	const I_CHAR * const NO						= I_("N");
	const I_CHAR * const FATCA					= I_("FA");
	const I_CHAR * const SINGLE_REPORT_FFI		= I_("02");
	const I_CHAR * const MULTIPLE_REPORT_FFI	= I_("03");
	const I_CHAR * const INDIVIDUAL_ACCOUNT		= I_("0,1,2");
	const I_CHAR * const REJERR_ERROR			= I_("E");
	const I_CHAR * const REJERR_WARNING			= I_("W");
	const I_CHAR * const REJERR_IGNORE			= I_("I");
	const I_CHAR * const TAG_FFI_STARTDATE      = I_("STARTDATE");
	const I_CHAR * const TAG_FFI_STOPDATE       = I_("STOPDATE");
	const I_CHAR * const TAG_REC_STARTDATE      = I_("STARTDATE");
	const I_CHAR * const TAG_REC_STOPDATE       = I_("STOPDATE");
}

namespace ifds
{
//	extern CLASS_IMPORT const BFNumericFieldId AccountNum;

}

namespace CND
{  

}

namespace IFASTERR
{
	//extern CLASS_IMPORT I_CHAR * const START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI;
}


//const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//	//  Field DD Id,              State Flags,    Group Flags 
//	//{ifds::AccountNum,          BFCBO::NONE,    	0 }, 
//	
//};

//static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
FATCAMaster::FATCAMaster (BFAbstractCBO &parent) :
MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

	//registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

	//addCrossEdit(ifds::EffectiveStopDate, ifds::EffectiveDate);
	//addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate);
}


//****************************************************************************
FATCAMaster::~FATCAMaster()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//****************************************************************************
SEVERITY FATCAMaster::init (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	commonInit(BF::HOST);

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY FATCAMaster::initNew (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));


	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY FATCAMaster::commonInit(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
void FATCAMaster::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{


}


//********************************************************************************************
SEVERITY FATCAMaster::doValidateField(const BFFieldId& idField,
										 const DString& strValue,
										 const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));



	return GETCURRENTHIGHESTSEVERITY();
}


//********************************************************************************************
SEVERITY FATCAMaster::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY FATCAMaster::doApplyRelatedChanges (const BFFieldId &idField, 
												  const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
	


	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
void FATCAMaster::doReset (const BFDataGroupId &idDataGroup)
{

}


//****************************************************************************
SEVERITY FATCAMaster::setReportingFFISubstitution(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setReportingFFISubstitution"));



	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY FATCAMaster::setDefaultReportingFFI(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setReportingFFISubstitution"));



	return GETCURRENTHIGHESTSEVERITY();
}
