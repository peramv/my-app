//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// FILE   : RDSPTransfer.cpp
// AUTHOR : 
// DATE   : 
//
// CLASS    : RDSPTransfer
// SUBCLASS :
//
// CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RDSPTransfer.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0488_req.hpp>
#include <ifastdataimpl\dse_dstc0488_vw.hpp>

namespace
{
	const I_CHAR * const CLASSNAME = I_("RDSPTransfer");	
}

//namespace UAF
//{
//	extern CLASS_IMPORT I_CHAR * const RDSP_TRANSFER;
//}

namespace ifds
{   
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFNumericFieldId TransNum;
	extern CLASS_IMPORT const BFTextFieldId TransType;
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFTextFieldId DepositType;
	extern CLASS_IMPORT const BFTextFieldId RedCode;	
}

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest RDSP_TRANSFER_INQUIRY;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,                     State Flags,      Group Flags  
	{ifds::AccountNum,					BFCBO::NONE,         0 },
	{ifds::TransNum,					BFCBO::NONE,		 0},
	{ifds::TransType,					BFCBO::NONE,		 0 },
	{ifds::EffectiveDate,				BFCBO::NONE,		 0 },
	{ifds::DepositType,					BFCBO::NONE,		 0 }, 
	{ifds::RedCode,						BFCBO::NONE,		 0 },	
	{ifds::ExtAccount,					BFCBO::NONE,		 0 }, 
	{ifds::ExtSpecimenPlanNo,			BFCBO::NONE,		 0 },
	{ifds::NontaxContrib,				BFCBO::NONE,         0 },
	{ifds::Rollovers,					BFCBO::NONE,         0 },
	{ifds::CDSGrant,					BFCBO::NONE,         0 },
	{ifds::CDSBond,						BFCBO::NONE,         0 },
	{ifds::CurrYrFMV,					BFCBO::NONE,         0 },
	{ifds::PrevYrGrantBond,				BFCBO::NONE,         0 },
	{ifds::PrevYrContrib,               BFCBO::NONE,         0 },
	{ifds::PrevYrNonTaxRedAmt,          BFCBO::NONE,         0 },   
	{ifds::PrevYrTaxRedAmt,             BFCBO::NONE,         0 },
	{ifds::CurrYrNonTaxRedAmt,          BFCBO::NONE,         0 },
	{ifds::CurrYrTaxRedAmt,             BFCBO::NONE,         0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
RDSPTransfer::RDSPTransfer (BFAbstractCBO &parent) : MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************************
RDSPTransfer::~RDSPTransfer()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}

//************************************************************************************
SEVERITY RDSPTransfer::initNew (const BFDataGroupId &idDataGroup,
								const DString &accountNum,
								const DString &transNum,							 
								const DString &transType,
								const DString &tradeDate,
								const DString &depositType,
								const DString &redCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   setObjectNew();

   setFieldNoValidate (ifds::AccountNum, accountNum, idDataGroup, false);

   doInitWithDefaultValues( idDataGroup );  
   
   commonInit (idDataGroup);  

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY RDSPTransfer::init (const DString &accountNum,
							 const DString &transNum,							 
							 const DString &transType,
							 const DString &tradeDate,
							 const DString &depositType,
							 const DString &redCode, 							
							 const DString &tradeType,   /*=I_("Pend")*/							
							 const DString &dstrTrack,   /*=I_("N")*/
							 const DString &dstrPageName /*=NULL_STRING*/)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));  

	DString mgmtCoIdOut;

	BFData requestData (ifds::DSTC0488_REQ);
	BFData *receivedData = new BFData (ifds::DSTC0488_VW);		
	
	setFieldNoValidate (ifds::AccountNum, accountNum, BF::HOST, false);
	setFieldNoValidate (ifds::TransNum, transNum, BF::HOST, false);
	setFieldNoValidate (ifds::TransType, transType, BF::HOST, false);
	setFieldNoValidate (ifds::EffectiveDate, tradeDate, BF::HOST, false);
	setFieldNoValidate (ifds::DepositType, depositType, BF::HOST, false);
	setFieldNoValidate (ifds::RedCode, redCode, BF::HOST, false);	

	requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	requestData.setElementValue (ifds::Track, dstrTrack);
	requestData.setElementValue (ifds::Activity, dstrPageName);
	requestData.setElementValue (ifds::AccountNum, accountNum);
	requestData.setElementValue (ifds::TransNum, transNum);
	requestData.setElementValue (ifds::TransType, transType);	

	ReceiveData( DSTC_REQUEST::RDSP_TRANSFER_INQUIRY, requestData, *receivedData, DSTCRequestor(getSecurity()) );

	commonInit (BF::HOST); 

	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RDSPTransfer::commonInit (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));   

	setFieldRequired (ifds::ExtAccount, idDataGroup, true);
	setFieldRequired (ifds::ExtSpecimenPlanNo, idDataGroup, true);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RDSPTransfer::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{	
	setFieldNoValidate (ifds::ExtAccount, I_(""), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::ExtSpecimenPlanNo, I_(""), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::NontaxContrib, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::Rollovers, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::CDSGrant, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::CDSBond, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::CurrYrFMV, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::PrevYrGrantBond, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::PrevYrContrib, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::PrevYrNonTaxRedAmt, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::PrevYrTaxRedAmt, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::CurrYrNonTaxRedAmt, I_("0.00"), idDataGroup, false, false, true);
	setFieldNoValidate (ifds::CurrYrTaxRedAmt, I_("0.00"), idDataGroup, false, false, true);
}

//***********************************************************************************
SEVERITY RDSPTransfer::doValidateField( const BFFieldId &idField,
									   const DString &strValue,
									   const BFDataGroupId &idDataGroup)

{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RDSPTransfer::doApplyRelatedChanges (const BFFieldId &idField, 
											  const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges"));	

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RDSPTransfer::doValidateAll (const BFDataGroupId &idDataGroup, 
									  long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));   	

	return GETCURRENTHIGHESTSEVERITY();
}






