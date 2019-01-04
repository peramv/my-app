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
// ^FILE   : DefaultRegulatoryStandard.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 01 August 2013
//
// ^CLASS    : DefaultRegulatoryStandard
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "DefaultRegulatoryStandard.hpp"

#include <bfutil\bfdate.hpp>
#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0453_vw.hpp>
#include <ifastdataimpl\dse_dstc0453_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest DEFAULT_REG_STANDARD_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME       = I_("DefaultRegulatoryStandard");
	const I_CHAR * const YES             = I_("Y"); 
	const I_CHAR * const NO              = I_("N"); 
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId AcctType;
	extern CLASS_IMPORT const BFTextFieldId TaxType;
	extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
	extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
	extern CLASS_IMPORT const BFTextFieldId TypeOfInvestor;
	extern CLASS_IMPORT const BFTextFieldId InvestingOnBehalf;
	extern CLASS_IMPORT const BFTextFieldId RegStandardId;
}

namespace CND
{  

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
	//  Field DD Id,              State Flags,    Group Flags 
	{ifds::RegStandardId,      BFCBO::READ_ONLY,  0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
DefaultRegulatoryStandard::DefaultRegulatoryStandard (BFAbstractCBO &parent) :
MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}


//****************************************************************************
DefaultRegulatoryStandard::~DefaultRegulatoryStandard()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//****************************************************************************
SEVERITY DefaultRegulatoryStandard::init (const BFDataGroupId& idDataGroup,
										  const DString& dstrAcctType,
										  const DString& dstrTaxType,
										  const DString& dstrAcctDesignation,
										  const DString& dstrTaxJurisCode,
										  const DString& dstrTypeOfInvestor,
										  const DString& dstrInvestingOnBehalf,
										  const DString& dstrTrack, 
										  const DString& dstrPageName)  
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	DString mgmtCoIdOut;

	BFData requestData(ifds::DSTC0453_REQ); 
	
	requestData.setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	requestData.setElementValue(ifds::Track, dstrTrack );
	requestData.setElementValue(ifds::Activity, dstrPageName );
	requestData.setElementValue(ifds::AcctType, dstrAcctType);
	requestData.setElementValue(ifds::TaxType, dstrTaxType);
	requestData.setElementValue(ifds::AcctDesignation, dstrAcctDesignation);
	requestData.setElementValue(ifds::TaxJurisCode, dstrTaxJurisCode);
	requestData.setElementValue(ifds::TypeOfInvestor, dstrTypeOfInvestor);
	requestData.setElementValue(ifds::InvestingOnBehalf, dstrInvestingOnBehalf);
	
	ReceiveData(DSTC_REQUEST::DEFAULT_REG_STANDARD_INQUIRY, requestData, ifds::DSTC0453_VW, DSTCRequestor(getSecurity(), true));

	return GETCURRENTHIGHESTSEVERITY();
}