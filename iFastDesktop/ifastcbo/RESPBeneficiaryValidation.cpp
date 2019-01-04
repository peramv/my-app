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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPBeneficiaryValidation.cpp
// ^AUTHOR : 
// ^DATE   : March, 2010
//
// ^CLASS    : RESPBeneficiaryValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "RESPBeneficiaryValidation.hpp"
#include <ifastdataimpl\dse_dstc0403_req.hpp>
#include <ifastdataimpl\dse_dstc0403_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_BENEF_ALLOCATION_UPDATE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFDateFieldId FundStatusDate;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId PensionJuris;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeSchedule;
}

namespace CND
{  
	extern const long ERR_RESP_PLAN_LIMIT_EXCEEDED;
	extern const long WARN_RESP_PLAN_LIMIT_EXCEEDED;
	extern const long ERR_RESP_YEAR_LIMIT_EXCEEDED;
	extern const long WARN_RESP_YEAR_LIMIT_EXCEEDED;
	extern const long ERR_RESP_BENEF_OVER21;
	extern const long WARN_RESP_BENEF_OVER21;
	extern const long ERR_RESP_BENEF_OVER31;
	extern const long WARN_RESP_BENEF_OVER31;
    extern const long ERR_LIFETIME_CONTRIB_LIMITS_NOT_SETUP;
	extern const long WARN_LIFETIME_CONTRIB_LIMITS_NOT_SETUP;
	extern const long ERR_ANNUAL_CONTRIB_LIMITS_NOT_SETUP;
	extern const long WARN_ANNUAL_CONTRIB_LIMITS_NOT_SETUP;
	extern const long WARN_BENEF_VALIDATION;
}
   

namespace
{
	const I_CHAR * const CLASSNAME							= I_ ("RESPBeneficiaryValidation");
	const I_CHAR * const VALIDATION							= I_ ("V");  
	const I_CHAR * const RESP_PLAN_LIMIT_EXCEEDED			= I_("216");
	const I_CHAR * const RESP_YEAR_LIMIT_EXCEEDED			= I_("217");
	const I_CHAR * const BENEFICIARY_IS_OVER_21				= I_("726");
	const I_CHAR * const BENEFICIARY_IS_OVER_31				= I_("999");
	const I_CHAR * const LIFETIME_CONTRIB_LIMITS_NOT_SETUP  = I_("1045");
    const I_CHAR * const ANNUAL_CONTRIB_LIMITS_NOT_SETUP    = I_("1046");
	const I_CHAR * const LIFETIME_LIMIT						= I_("LIFETIMELIMIT");
	const I_CHAR * const ANNUAL_LIMIT						= I_("ANNUALLIMIT");
	const I_CHAR * const TO_DATE							= I_("TODATE");
	const I_CHAR * const BENEF_NAME							= I_("BENNAME");
}


//******************************************************************************
RESPBeneficiaryValidation::RESPBeneficiaryValidation (BFAbstractCBO &parent)
: MFCanBFCbo (parent),
m_BenefName (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
RESPBeneficiaryValidation::~RESPBeneficiaryValidation ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY RESPBeneficiaryValidation::init (const DString &strTransId,
										  const DString &strAccountNum,
										  const DString &strTradeType,
										  const DString &strTradeDate,
										  const DString &strTradeAmount,
	                                      const DString &strEntityType, 
                                          const DString &strEntityTypeSeq, 
                                          const DString &strRESPBenefId,
										  const DString &strRESPBenefName,
                                          const DString &strRESPAllocAmount, 
                                          const DString &strRESPAllocPercent, 
                                          const DString &strRESPContrDetlVer,
										  const DString &strCallType,
										  const DString &strCreateEscrow,
                                          bool ignoreDataNotFound /*=true*/)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

	m_BenefName = strRESPBenefName;
	
	BFData queryData  (ifds::DSTC0403_REQ);
	BFData repeatData  (ifds::DSTC0403_REQRepeat_Record);
	DString mgmtCoIdOut;

	// non repeating data
	queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	queryData.setElementValue (ifds::TransId, strTransId); 
	queryData.setElementValue (ifds::CallType, strCallType); 
	queryData.setElementValue (ifds::TradeType, strTradeType); 
	queryData.setElementValue (ifds::AccountNum, strAccountNum); 
	queryData.setElementValue (ifds::EffectiveDate, strTradeDate); 
	queryData.setElementValue (ifds::Amount, strTradeAmount); 

	// repeating data
	repeatData.setElementValue (ifds::AllocEntityType, strEntityType);
	repeatData.setElementValue (ifds::AllocEntityTypeSeq, strEntityTypeSeq);
	repeatData.setElementValue (ifds::RESPBenefId, strRESPBenefId);
	repeatData.setElementValue (ifds::RESPAllocAmt, strRESPAllocAmount);
	repeatData.setElementValue (ifds::RESPAllocPrcnt, strRESPAllocPercent);
	repeatData.setElementValue (ifds::RESPContrDetlVer, strRESPContrDetlVer);
	repeatData.setElementValue (ifds::CreateEscrow, strCreateEscrow);

    repeatData.setElementValue (ifds::RunMode, I_("M"));

	queryData.setElementValue( ifds::RepeatCount, I_("1"), false, false);
	queryData.addRepeat (repeatData);

	ReceiveData  (DSTC_REQUEST::RESP_BENEF_ALLOCATION_UPDATE, queryData, ifds::DSTC0403_VW,
                  DSTCRequestor (getSecurity (), true, ignoreDataNotFound));

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPBeneficiaryValidation::validateBeneficiary (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateBeneficiary"));

	DString warnCode1, warnCode2, warnCode3, 
		    warnCode4, warnCode5, warnCode6,
			warnCode7, warnCode8, warnCode9, 
			warnCode10, warnCode11, warnCode12;
	DString param1, param2;
	DString param51, param52;
	DString param61, param62;
    
	getField (ifds::WarnCode1, warnCode1, idDataGroup, false);
	getField (ifds::WarnCode2, warnCode2, idDataGroup, false);
	getField (ifds::WarnCode3, warnCode3, idDataGroup, false);
	getField (ifds::WarnCode4, warnCode4, idDataGroup, false);
	getField (ifds::WarnCode5, warnCode5, idDataGroup, false);
	getField (ifds::WarnCode6, warnCode6, idDataGroup, false);
	getField (ifds::WarnCode7, warnCode7, idDataGroup, false);
	getField (ifds::WarnCode8, warnCode8, idDataGroup, false);
	getField (ifds::WarnCode9, warnCode9, idDataGroup, false);
	getField (ifds::WarnCode10, warnCode10, idDataGroup, false);
	getField (ifds::WarnCode11, warnCode11, idDataGroup, false);
	getField (ifds::WarnCode12, warnCode12, idDataGroup, false);
    
	getField (ifds::WarnParam51, param51, idDataGroup, false);
	getField (ifds::WarnParam52, param52, idDataGroup, false);
	getField (ifds::WarnParam61, param61, idDataGroup, false);
	getField (ifds::WarnParam62, param62, idDataGroup, false);


	if (!warnCode1.empty ())
	{
		displayErrorMessage (warnCode1, param1, param2, idDataGroup);
	}
	
	if (!warnCode2.empty ())
	{
		displayErrorMessage (warnCode2, param1, param2, idDataGroup);
	}
	
	if (!warnCode3.empty ())
	{
		displayErrorMessage (warnCode3, param1, param2, idDataGroup);
	}
	
	if (!warnCode4.empty ())
	{
		displayErrorMessage (warnCode4, param1, param2, idDataGroup);
	}
	
	if (!warnCode5.empty ())
	{
		displayErrorMessage (warnCode5, param51, param52, idDataGroup);
	}
	
	if (!warnCode6.empty ())
	{
		displayErrorMessage (warnCode6, param61, param62, idDataGroup);
	}
	
	if (!warnCode7.empty ())
	{
		displayErrorMessage (warnCode7, param1, param2, idDataGroup);
	}
	
	if (!warnCode8.empty ())
	{
		displayErrorMessage (warnCode8, param1, param2, idDataGroup);
	}

	if (!warnCode9.empty ())
	{
		displayErrorMessage (warnCode9, param1, param2, idDataGroup);
	}

	if (!warnCode10.empty ())
	{
		displayErrorMessage (warnCode10, param1, param2, idDataGroup);
	}

	if (!warnCode11.empty ())
	{
		displayErrorMessage (warnCode11, param1, param2, idDataGroup);
	}

	if (!warnCode12.empty ())
	{
		displayErrorMessage (warnCode12, param1, param2, idDataGroup);
	}
	return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
SEVERITY RESPBeneficiaryValidation::displayErrorMessage (const DString &errorNumber,
														 const DString &param1,
														 const DString &param2,
														 const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("displayErrorMessage"));

	if (errorNumber == RESP_PLAN_LIMIT_EXCEEDED)
	{
		DString idiStr1 = NULL_STRING;

	    addIDITagValue (idiStr1, BENEF_NAME, m_BenefName);
		addIDITagValue (idiStr1, LIFETIME_LIMIT, param1);
		addIDITagValue (idiStr1, TO_DATE, param2);

		getErrMsg (RESP_PLAN_LIMIT_EXCEEDED,
				   CND::ERR_RESP_PLAN_LIMIT_EXCEEDED,
				   CND::WARN_RESP_PLAN_LIMIT_EXCEEDED,
			       idDataGroup, idiStr1);		
	}
	else if (errorNumber == RESP_YEAR_LIMIT_EXCEEDED)
	{
		DString idiStr2 = NULL_STRING;

	    addIDITagValue (idiStr2, BENEF_NAME, m_BenefName);
		addIDITagValue (idiStr2, ANNUAL_LIMIT, param1);
		addIDITagValue (idiStr2, TO_DATE, param2);

		getErrMsg (RESP_YEAR_LIMIT_EXCEEDED,
				   CND::ERR_RESP_YEAR_LIMIT_EXCEEDED,
				   CND::WARN_RESP_YEAR_LIMIT_EXCEEDED,
			       idDataGroup, idiStr2);
	}
	else if (errorNumber == BENEFICIARY_IS_OVER_21)
	{
		DString idiStr = NULL_STRING;

	    addIDITagValue (idiStr, BENEF_NAME, m_BenefName);
		
		getErrMsg (BENEFICIARY_IS_OVER_21,
				   CND::ERR_RESP_BENEF_OVER21,
				   CND::WARN_RESP_BENEF_OVER21,
			       idDataGroup, idiStr);
	}
	else if (errorNumber == BENEFICIARY_IS_OVER_31)
	{
		DString idiStr = NULL_STRING;

	    addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

		getErrMsg (BENEFICIARY_IS_OVER_31,
				   CND::ERR_RESP_BENEF_OVER31,
				   CND::WARN_RESP_BENEF_OVER31,
			       idDataGroup, idiStr);
	}
	else if (errorNumber == LIFETIME_CONTRIB_LIMITS_NOT_SETUP)
	{
		DString idiStr = NULL_STRING;

	    addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

		getErrMsg (LIFETIME_CONTRIB_LIMITS_NOT_SETUP,
				   CND::ERR_LIFETIME_CONTRIB_LIMITS_NOT_SETUP,
				   CND::WARN_LIFETIME_CONTRIB_LIMITS_NOT_SETUP,
			       idDataGroup, idiStr);
	}
	else if (errorNumber == ANNUAL_CONTRIB_LIMITS_NOT_SETUP)
	{
		DString idiStr = NULL_STRING;

	    addIDITagValue (idiStr, BENEF_NAME, m_BenefName);

		getErrMsg (ANNUAL_CONTRIB_LIMITS_NOT_SETUP,
				   CND::ERR_ANNUAL_CONTRIB_LIMITS_NOT_SETUP,
				   CND::WARN_ANNUAL_CONTRIB_LIMITS_NOT_SETUP,
			       idDataGroup, idiStr);
	}
	// TO DO: add QESI messages!!!

	return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************
void RESPBeneficiaryValidation::buildKey (const DString &_strTransId,
	                                      const DString &_strEntityType, 
                                          const DString &_strEntityTypeSeq, 
                                          const DString &_strRESPBenefId, 
                                          const DString &_strRESPAllocAmount, 
                                          const DString &_strRESPAllocPercent,
									      DString &strKey)
{
	DString strTransId (_strTransId),
		    strEntityType (_strEntityType), 
			strEntityTypeSeq (_strEntityTypeSeq), 
            strRESPBenefId (_strRESPBenefId), 
            strRESPAllocAmount (_strRESPAllocAmount), 
            strRESPAllocPercent (_strRESPAllocPercent);

   strTransId.strip ();
   strEntityType.strip().upperCase();
   strEntityTypeSeq.strip();
   strRESPBenefId.strip();
   strRESPAllocAmount.strip().upperCase();
   strRESPAllocPercent.strip().upperCase();
  

   strKey = DString (I_("RESPBeneficiaryValidation_")) + 
                    I_("TransId=") + strTransId + I_(";") +
                    I_("EntityType=") + strEntityType + I_(";") +
                    I_("EntityTypeSeq=") + strEntityTypeSeq + I_(";") +
                    I_("BenefId=") + strRESPBenefId + I_(";") +
                    I_("AllocAmount=") + strRESPAllocAmount + I_(";") +
                    I_("AllocPercent=") + strRESPAllocPercent + I_(";");
}

/* $Log::   
*/

