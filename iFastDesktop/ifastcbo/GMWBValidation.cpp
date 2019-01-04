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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : GMWBValidation.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : GMWBValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "GMWBValidation.hpp"
#include "mgmtco.hpp"
#include "funddetail.hpp"
#include <ifastdataimpl\dse_dstc0438_req.hpp>
#include <ifastdataimpl\dse_dstc0438_vw.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest GMWB_VALIDATION;
}

namespace  
{
	const I_CHAR * const CLASSNAME		= I_( "GMWBValidation" );
	const I_CHAR * const EWI_ERROR      = I_ ("E");
	const I_CHAR * const EWI_WARNING    = I_ ("W");
	const I_CHAR * const CONTRACTTYPE   =I_("ContractType");

    const long ACTIVE_SWP_CONTRACT_TYPE     = 1241;
	const long ACTIVE_SWP_AMT_TYPE			= 1242;
	const long NON_GMBW_FUND				= 1243;
	const long RIF_AMT_TYPE					= 1244;
	const long NON_GMBW_PAYOPTION			= 1250;
}

namespace CND
{  
	extern const long ERR_ACTIVE_SWP_CONTTYPE_EXISTS;
	extern  const long WARN_ACTIVE_SWP_CONTTYPE_EXISTS;
	extern  const long ERR_ACTIVE_SWP_AMTTYPE_EXISTS;
	extern  const long WARN_ACTIVE_SWP_AMTTYPE_EXISTS;
	extern  const long ERR_SWP_NON_GMWB_FUNDS;
	extern  const long WARN_SWP_NON_GMWB_FUNDS;
	extern  const long ERR_GMWB_PAYOPTION;
	extern  const long WARN_GMWB_PAYOPTION;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	//   Field DD Id,		State Flags,	Group Flags 
	{ ifds::ErrorCode,		BFCBO::NONE,	0 },
	{ ifds::EWI,			BFCBO::NONE,	0 },
};

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId ContractType;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,    State Flags,         Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
GMWBValidation::GMWBValidation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
GMWBValidation::~GMWBValidation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************
SEVERITY GMWBValidation::init(const DString &accountNum,
							  const DString &validateType,
							  const DString &transNum,
							  const DString &fundCode,
							  const DString &classCode,
							  const DString &effectiveDate,
							  const DString &stopDate,
							  const DString &payOption,
							  const DString &recId,
							  const DString &runMode,
							  const DString &dstrTrack /*= I_("N")*/,
							  const DString &dstrPageName /*= NULL_STRING*/)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   
	BFData queryData(ifds::DSTC0438_REQ);
	BFData *receivedData = new BFData(ifds::DSTC0438_VW);
	DString mgmtCoIdOut;
   
	queryData.setElementValue( ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
	queryData.setElementValue( ifds::Track,          dstrTrack );
	queryData.setElementValue( ifds::Activity,       dstrPageName );
 
	queryData.setElementValue( ifds::AccountNum,	accountNum );
	queryData.setElementValue( ifds::ValidateType,  validateType );
	queryData.setElementValue( ifds::TransNum,		transNum );
	queryData.setElementValue( ifds::Fund,			fundCode );
	queryData.setElementValue( ifds::Class,			classCode );
	queryData.setElementValue( ifds::EffectiveDate, effectiveDate, false, false );
	queryData.setElementValue( ifds::StopDate,      stopDate );
	queryData.setElementValue( ifds::PayOption,     payOption);
	queryData.setElementValue( ifds::RecId,			recId );
	queryData.setElementValue( ifds::RunMode,       runMode );
								
	ReceiveData (DSTC_REQUEST::GMWB_VALIDATION, queryData,  *receivedData, DSTCRequestor (getSecurity()));

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void GMWBValidation::buildKey (const DString &accountNum,
							   const DString &validateType,
							   const DString &transNum,
							   const DString &fundCode,
							   const DString &classCode,
							   const DString &effectiveDate,
							   const DString &stopDate,
							   const DString &payOption,
							   const DString &recId,
							   const DString &runMode,
							   DString &strKey)
{
   DString	dstrAccountNum (accountNum),
	        dstrValidateType (validateType), 
			dstrEffectiveDate (effectiveDate), 
			dstrStopDate (stopDate), 
			dstrTransNum (transNum),
			dstrFundCode (fundCode),
			dstrClassCode (classCode),
			dstrPayOption (payOption),       
			dstrRecId (recId);

   strKey = DString (I_("GMWBValidation_")) + 
			I_("AccountNum=") + dstrAccountNum + I_(";") +
			I_("ValidateType=") + dstrValidateType + I_(";") +
			I_("EffectiveDate=") + dstrEffectiveDate + I_(";") +
			I_("StopDate=") + dstrStopDate + I_(";") +
			I_("TransNum=") + dstrTransNum + I_(";") +
			I_("FundCode=") + dstrFundCode + I_(";") +
			I_("ClassCode=") + dstrClassCode + I_(";") +
			I_("PayOption=") + dstrPayOption + I_(";") +
			I_("RecId=") + dstrRecId + I_(";") ;
}

//******************************************************************************
SEVERITY GMWBValidation::validateGMWB (const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateGMWB"));

	DString dstrErrorCode;
	DString dstrEWI;

	getField (ifds::ErrorCode, dstrErrorCode, BF::HOST, false);
    
    getField  (ifds::EWI, dstrEWI, BF::HOST, false);
            
    long nErrNum = dstrErrorCode.strip ().stripLeading ('0').convertToULong ();
            
	switch  (nErrNum)
    {
		case ACTIVE_SWP_CONTRACT_TYPE:
        {
			if (dstrEWI == EWI_ERROR)
				ADDCONDITIONFROMFILE (CND::ERR_ACTIVE_SWP_CONTTYPE_EXISTS);
            
			if (dstrEWI == EWI_WARNING)
				ADDCONDITIONFROMFILE (CND::WARN_ACTIVE_SWP_CONTTYPE_EXISTS);

			break;
		}

		case ACTIVE_SWP_AMT_TYPE:
        {
			if (dstrEWI == EWI_ERROR)
				ADDCONDITIONFROMFILE (CND::ERR_ACTIVE_SWP_AMTTYPE_EXISTS);
            
			if (dstrEWI == EWI_WARNING)
				ADDCONDITIONFROMFILE (CND::WARN_ACTIVE_SWP_AMTTYPE_EXISTS);

			break;
		}

		case NON_GMBW_FUND:
        {
			if (dstrEWI == EWI_ERROR)
				ADDCONDITIONFROMFILE (CND::ERR_SWP_NON_GMWB_FUNDS);
            
			if (dstrEWI == EWI_WARNING)
				ADDCONDITIONFROMFILE (CND::WARN_SWP_NON_GMWB_FUNDS);

			break;
		}

		case NON_GMBW_PAYOPTION:
        {
			if (dstrEWI == EWI_ERROR)
				ADDCONDITIONFROMFILE (CND::ERR_GMWB_PAYOPTION);
            
			if (dstrEWI == EWI_WARNING)
				ADDCONDITIONFROMFILE (CND::WARN_GMWB_PAYOPTION);

			break;
		}
		  	
		default:
			break;
	}
   
	return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GMWBValidation.cpp-arc  $
// 
//    Rev 1.1   May 14 2012 15:37:48   jankovii
// P0186481 FN07-GWA LWA Payment Options for SWP RRIF v4.
// 
//    Rev 1.0   May 11 2012 13:16:34   jankovii
// Initial revision.
// 
 
*/


