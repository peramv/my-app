//******************************************************************************
//
// COPYRIGHT:
//
//  The computer systems, procedures, data bases and
//  programs created and maintained by International Financial Data Services,
//  are proprietary in nature and as such are confidential.
//  Any unauthorized use or disclosure of such information
//  may result in civil liabilities.
//
//  Copyright 2018 by International Financial Data Services
//
//
//******************************************************************************
//
// FILE   : RDSPTradeValidation.cpp
// AUTHOR : 
// DATE   : 
//
// CLASS    : RDSPTradeValidation
// SUBCLASS :
//
// CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtco.hpp"
#include "RDSPTradeValidation.hpp"
#include <ifastdataimpl\dse_dstc0167_req.hpp>
#include <ifastdataimpl\dse_dstc0167_vw.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest TRADE_MIN_AMT_CHECK;
}

namespace CND
{
	extern const long ERR_RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA;
	extern const long WARN_RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA;
	extern const long ERR_RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION;
	extern const long WARN_RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION;
	extern const long ERR_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_SDSP_ELECT;
	extern const long WARN_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_SDSP_ELECT;
	extern const long ERR_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT;
	extern const long WARN_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT;
	extern const long ERR_RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS;
	extern const long WARN_RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS;
	extern const long ERR_RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH;
	extern const long WARN_RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH;
	extern const long ERR_RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED;
	extern const long WARN_RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED;
	extern const long ERR_RDSP_EXTERNAL_CONTRACT_MANDATORY;
	extern const long WARN_RDSP_EXTERNAL_CONTRACT_MANDATORY;
	extern const long ERR_RDSP_EXTERNAL_PLAN_MANDATORY;
	extern const long WARN_RDSP_EXTERNAL_PLAN_MANDATORY;
	extern const long ERR_RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS;
	extern const long WARN_RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS;		
	extern const long ERR_RDSP_INVALID_REPAYMENT_REASON;
	extern const long WARN_RDSP_INVALID_REPAYMENT_REASON;
	extern const long ERR_RDSP_FMV_LESS_THAN_AHA_AMOUNT;
	extern const long WARN_RDSP_FMV_LESS_THAN_AHA_AMOUNT;
	extern const long ERR_RDSP_DAP_INVALID_REPAYMENT_REASON;
	extern const long WARN_RDSP_DAP_INVALID_REPAYMENT_REASON;
	extern const long ERR_RDSP_LDAP_INVALID_REPAYMENT_REASON;
	extern const long WARN_RDSP_LDAP_INVALID_REPAYMENT_REASON;
	extern const long ERR_RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON;
	extern const long WARN_RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON;
	extern const long ERR_RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX;
	extern const long WARN_RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX;
	extern const long ERR_RDSP_API_TIMEOUT;
	extern const long WARN_RDSP_API_TIMEOUT;
	extern const long ERR_RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED;
	extern const long WARN_RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED;
	extern const long ERR_RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT;
	extern const long WARN_RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT;
}

namespace IFASTERR
{

}

namespace
{
	const I_CHAR * const CLASSNAME									= I_("RDSPTradeValidation");
	const I_CHAR * const EWI_ERROR									= I_("E");
	const I_CHAR * const EWI_WARNING								= I_("W");
	const I_CHAR * const YES										= I_("Y");
	const I_CHAR * const NO											= I_("N");

	const long RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA			= 2071;
	const long RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION			= 2072;
	const long RDSP_TRADE_NOT_ALLOWED_ACCOUNT_SDSP_ELECT			= 2090;
	const long RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT				= 2091;
	const long RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS				= 2092;
	const long RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH		= 2093;
	const long RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED					= 2094;
	const long RDSP_EXTERNAL_CONTRACT_MANDATORY						= 2140;
	const long RDSP_EXTERNAL_PLAN_MANDATORY							= 2141;
	const long RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS	= 2180;		
	const long RDSP_INVALID_REPAYMENT_REASON						= 2183;
	const long RDSP_FMV_LESS_THAN_AHA_AMOUNT						= 2184;
	const long RDSP_DAP_INVALID_REPAYMENT_REASON					= 2185;
	const long RDSP_LDAP_INVALID_REPAYMENT_REASON					= 2186;
	const long RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON		= 2187;
	const long RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX						= 2188;
	const long RDSP_API_TIMEOUT										= 2194;
	const long RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED				= 2206;
	const long RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT	= 2217;
}

//******************************************************************************
RDSPTradeValidation::RDSPTradeValidation(BFAbstractCBO &parent):MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
	setObjectAsList();
}

//******************************************************************************
RDSPTradeValidation::~RDSPTradeValidation()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY RDSPTradeValidation::init(const DString &dstrAccountNum,
								   const DString &dstrFundCode, 
								   const DString &dstrClassCode, 
								   const DString &dstrTransType,
								   const DString &dstrEffectiveDate, 
								   const DString &dstrDepositType,
								   const DString &dstrRedCode,
								   const DString &dstrAmount,
								   const DString &dstrGRRepayReason,
								   const DString &dstrRDSPPaymtDate)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	DString mgmtCoIdOut;

	BFData queryData(ifds::DSTC0167_REQ);
		
	queryData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	queryData.setElementValue(ifds::AccountNum, dstrAccountNum);
	queryData.setElementValue(ifds::FundCode, dstrFundCode);
	queryData.setElementValue(ifds::ClassCode, dstrClassCode);
	queryData.setElementValue(ifds::TransType, dstrTransType);
	queryData.setElementValue(ifds::Amount, dstrAmount);
	queryData.setElementValue(ifds::AmountType, NULL_STRING);
	queryData.setElementValue(ifds::EffectiveDate, dstrEffectiveDate);
	queryData.setElementValue(ifds::SettleCurrency, NULL_STRING);
	queryData.setElementValue(ifds::ExchRate, NULL_STRING);
	queryData.setElementValue(ifds::AMSCode, NULL_STRING);
	queryData.setElementValue(ifds::AMSType, NULL_STRING);
	queryData.setElementValue(ifds::BrokerCode, NULL_STRING);
	queryData.setElementValue(ifds::BranchCode, NULL_STRING);
	queryData.setElementValue(ifds::SalesRepCode, NULL_STRING);	
	queryData.setElementValue(ifds::DepositType, dstrDepositType);
	queryData.setElementValue(ifds::OrderType, NO);
	queryData.setElementValue(ifds::FullExchPrntToPrnt, NO);
	queryData.setElementValue(ifds::Indc, NULL_STRING);
	queryData.setElementValue(ifds::AdjTransNum, NULL_STRING);
	queryData.setElementValue(ifds::DilutionLinkNum, NULL_STRING);
	queryData.setElementValue(ifds::RedCode, dstrRedCode);
	queryData.setElementValue(ifds::RDSPValidation, YES);
	queryData.setElementValue(ifds::GRRepayReason, dstrGRRepayReason);
	queryData.setElementValue(ifds::RDSPPaymtDate, dstrRDSPPaymtDate);
	
	ReceiveData(DSTC_REQUEST::TRADE_MIN_AMT_CHECK, queryData, ifds::DSTC0167_VW, DSTCRequestor(getSecurity (), true, true));

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RDSPTradeValidation::addConditions(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addConditions"));

	DString errNum, severityCode;

	BFObjIter iter(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
	iter.begin();	

	while(!iter.end())
	{
		iter.getObject()->getField(ifds::ErrNum, errNum, BF::HOST, false);
		iter.getObject()->getField(ifds::EWI, severityCode, BF::HOST, false);
		severityCode.upperCase ();

		long nErrNum = errNum.strip().stripLeading('0').convertToULong();

		if(errNum.empty())
			return GETCURRENTHIGHESTSEVERITY();

		switch (nErrNum)
		{
			case RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA:
				{
					// 2071 - Beneficiary tax jurisdiction must be Canadian at the trade effective date.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA);					
				}
				break;
			case RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION:
				{
					// 2072 - RDSP Beneficiary is over the age of contribution.					
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION);		
				}
				break;
			case RDSP_TRADE_NOT_ALLOWED_ACCOUNT_SDSP_ELECT:
				{
					// 2090 - Trade not allowed for a RDSP account SDSP elect.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_SDSP_ELECT);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_SDSP_ELECT);		
				}
				break;
			case RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT:
				{
					// 2091 - Trade not allowed for a RDSP account DTC elect.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT);							
				}
				break;
			case RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS:
				{
					// 2092 - RDSP Registration Status doesn't allow contributions.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS);		
				}
				break;
			case RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH:
				{
					// 2093 - Trade date is after Beneficiary's Date of Death.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH);
				}
				break;
			case RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED:
				{
					// 2094 - RDSP Maximum Contributions LTA exceeded.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED);				
				}
				break;
			case RDSP_EXTERNAL_CONTRACT_MANDATORY:
				{
					// 2140 - External RDSP Account Contract Number is mandatory.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_EXTERNAL_CONTRACT_MANDATORY);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_EXTERNAL_CONTRACT_MANDATORY);
				}
				break;	
			case RDSP_EXTERNAL_PLAN_MANDATORY:
				{
					// 2141 - External RDSP Specimen Plan Number is mandatory.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_EXTERNAL_PLAN_MANDATORY);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_EXTERNAL_PLAN_MANDATORY);
				}
				break;
			case RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS:
				{
					// 2180 - Cannot backdate the trade before the Money-out transaction.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS);					
				}
				break;			
			case RDSP_INVALID_REPAYMENT_REASON:
				{
					// 2183 - Invalid Repayment Reason.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_INVALID_REPAYMENT_REASON);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_INVALID_REPAYMENT_REASON);
				}
				break;
			case RDSP_FMV_LESS_THAN_AHA_AMOUNT:
				{
					// 2184 - FMV is less than AHA amount, payment may be rejected.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_FMV_LESS_THAN_AHA_AMOUNT);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_FMV_LESS_THAN_AHA_AMOUNT);
				}
				break;
			case RDSP_DAP_INVALID_REPAYMENT_REASON:
				{
					// 2185 - Repayment reason does not match for DAP.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_DAP_INVALID_REPAYMENT_REASON);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_DAP_INVALID_REPAYMENT_REASON);
				}
				break;
			case RDSP_LDAP_INVALID_REPAYMENT_REASON:
				{
					// 2186 - Repayment reason does not match for LDAP.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_LDAP_INVALID_REPAYMENT_REASON);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_LDAP_INVALID_REPAYMENT_REASON);
				}
				break;
			case RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON:
				{
					// 2187 - Repayment reason does not match for All Funds Full Withdrawal.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON);
				}
				break;
			case RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX:
				{
					// 2188 - Amount not in Min/Max Range.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX);
				}
				break;
			case RDSP_API_TIMEOUT:
				{
					// 2194 - RDSP Internal Error - Please contact API owner.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_API_TIMEOUT);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_API_TIMEOUT);
				}
				break;
			case RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED:
				{
					// 2206 - RDSP Transfer Out transaction cannot be processed earlier than an existing transaction.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED);
				}
				break;
			case RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT:
				{
					// 2217 - Money Out Transactions exist after Date of Payment.
					if (severityCode == EWI_ERROR)
						ADDCONDITIONFROMFILE (CND::ERR_RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT);
					if (severityCode == EWI_WARNING)
						ADDCONDITIONFROMFILE (CND::WARN_RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT);
				}
				break;
			default:				
				break;
		}

		++iter;
	}

	return GETCURRENTHIGHESTSEVERITY();
}