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
// ^FILE   : UnusualTradingValidation.cpp
// ^AUTHOR : 
// ^DATE   : March, 2017
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtco.hpp"
#include "UnusualTradingValidation.hpp"
#include <ifastdataimpl\dse_dstc0479_req.hpp>
#include <ifastdataimpl\dse_dstc0479_vw.hpp>
#include <ifastdataimpl\dse_dstc0479_vwrepeat_record.hpp>

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;

   const char *const CFX_TRANS = "CFXTRAN";
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest UNUSUAL_TRADING_VALIDATION;
}

namespace CND
{  
	extern const long ERR_ABSOLUTE_VALUE_THRESHOLD_BREACHED;
	extern const long WARN_ABSOLUTE_VALUE_THRESHOLD_BREACHED;
	extern const long ERR_PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED;
	extern const long WARN_PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED;
	extern const long ERR_INITIAL_MONEY_IN_TO_A_CLASS;
	extern const long WARN_INITIAL_MONEY_IN_TO_A_CLASS;
  extern const long WARN_PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_BREACHED;
  extern const long ERR_PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_BREACHED;
  extern const long ERR_PERCENTAGE_OF_TRADES_AMOUNT_TYPE_BREACHED;
  extern const long WARN_PERCENTAGE_OF_TRADES_AMOUNT_TYPE_BREACHED;

  extern const long ERR_FUND_COMPANY_APPROVAL_REQUIRED;
  extern const long WARN_FUND_COMPANY_APPROVAL_REQUIRED;
  extern const long ERR_GENERAL_AGREEMENT_NOT_AVAILABLE;
  extern const long WARN_GENERAL_AGREEMENT_NOT_AVAILABLE;
  extern const long ERR_ACCOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT;
  extern const long WARN_ACCOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT;
}

namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const ABSOLUTE_VALUE_THRESHOLD_BREACHED;
	extern CLASS_IMPORT I_CHAR * const PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED;
	extern CLASS_IMPORT I_CHAR * const INITIAL_MONEY_IN_TO_A_CLASS;
	extern CLASS_IMPORT I_CHAR * const PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY;                    
	extern CLASS_IMPORT I_CHAR * const PERCENTAGE_OF_TRADES_AMOUNT_TYPE;  

	extern CLASS_IMPORT I_CHAR * const FUND_COMPANY_APPROVAL_REQUIRED;                               
	extern CLASS_IMPORT I_CHAR * const GENERAL_AGREEMENT_NOT_AVAILABLE;
	extern CLASS_IMPORT I_CHAR * const AMOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT;
}

namespace ifds
{
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFTextFieldId Currency;
    extern CLASS_IMPORT const BFTextFieldId ToFund;
    extern CLASS_IMPORT const BFTextFieldId ToClass;
    extern CLASS_IMPORT const BFNumericFieldId ToAccount;
	extern CLASS_IMPORT const BFDateFieldId TradeInDate;
}
 
namespace
{
	const I_CHAR * const CLASSNAME           = I_ ("UnusualTradingValidation");
	const I_CHAR * const EWI_ERROR                     = I_ ("E");
	const I_CHAR * const EWI_WARNING                   = I_ ("W");

	const long ABSOLUTE_VALUE_THRESHOLD_VALIDATION = 1935 ;
	const long PERCENTAGE_OF_CLASS_HOLDINGS_VALIDATION = 1936;
	const long INITIAL_MONEY_IN_TO_A_CLASS_VALIDATION = 1939;
	const long PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_VALIDATION = 1937 ;
	const long PERCENTAGE_OF_TRADES_AMOUNT_TYPE_VALIDATION = 1938;
	const long FUND_COMPANY_APPROVAL_REQUIRED = 1956;
	const long GENERAL_AGREEMENT_NOT_AVAILABLE = 1957;
	const long AMOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT = 1958;

}
//******************************************************************************
UnusualTradingValidation::UnusualTradingValidation (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	
}

//******************************************************************************
UnusualTradingValidation::~UnusualTradingValidation ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY UnusualTradingValidation::init (const DString &strAccountNum, 
                                 const DString &strFundCode, 
                                 const DString &strClassCode, 
                                 const DString &strTransType, 
                                 const DString &strAmountType, 
                                 const DString &strAmount, 
                                 const DString &strEffectiveDate, 
                                 const DString &strSettleCurrency, 
                                 const DString &strExchRate,
                                 const DString &dstrBrokerCode, 
                                 const DString &dstrBranchCode,
                                 const DString &dstrSalesRepCode,
                                 const DString &dstrAMSCode, 
                                 const DString &dstrAMSType,
                                 const DString &dstrDepositType, 
                                 const DString &dstrOrderType,
								 const DString &strToFundCode,
								 const DString &strToClassCode,
								 const DString &strToAccount,
								 const DString &strTradeInDate,
                                 bool ignoreDataNotFound, 
                                 bool bFullExchPrntToPrnt,
                                 const DString &Indc,
                                 const DString &adjForTransNum)
{


   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
   BFData queryData  (ifds::DSTC0479_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::AccountNum, strAccountNum);
   queryData.setElementValue (ifds::FundCode, strFundCode);
   queryData.setElementValue (ifds::ClassCode, strClassCode);
   queryData.setElementValue (ifds::TransType, strTransType);
   queryData.setElementValue (ifds::Amount, strAmount);
   queryData.setElementValue (ifds::AmountType, strAmountType);
   queryData.setElementValue (ifds::EffectiveDate, strEffectiveDate, false, false);
   queryData.setElementValue (ifds::SettleCurrency, strSettleCurrency);
   queryData.setElementValue (ifds::ExchRate, strExchRate);
   queryData.setElementValue (ifds::AMSCode, dstrAMSCode);
   queryData.setElementValue (ifds::AMSType, dstrAMSType);
   queryData.setElementValue (ifds::BrokerCode, dstrBrokerCode);
   queryData.setElementValue (ifds::BranchCode, dstrBranchCode);
   queryData.setElementValue (ifds::SalesRepCode, dstrSalesRepCode);
   queryData.setElementValue (ifds::DepositType, dstrDepositType); 
   queryData.setElementValue (ifds::OrderType, dstrOrderType);
   queryData.setElementValue (ifds::FullExchPrntToPrnt, bFullExchPrntToPrnt ? Y:N);
   queryData.setElementValue (ifds::Indc, Indc);
   queryData.setElementValue (ifds::AdjTransNum, adjForTransNum);
   queryData.setElementValue (ifds::ToFund, strToFundCode);
   queryData.setElementValue (ifds::ToClass, strToClassCode);
   queryData.setElementValue (ifds::ToAccount, strToAccount);
   queryData.setElementValue (ifds::TradeInDate, strTradeInDate);

   ReceiveData  (DSTC_REQUEST::UNUSUAL_TRADING_VALIDATION, 
                 queryData, 
                 ifds::DSTC0479_VW,
                 DSTCRequestor  (getSecurity (), true, ignoreDataNotFound));

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY UnusualTradingValidation::addConditions ()
{
	MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("addConditions"));


	DString errNum,severityCode;

	BFObjIter iter  (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
	iter.begin ();

	while  (!iter.end ())
	{
		iter.getObject ()->getField  (ifds::ErrNum, errNum, BF::HOST, false);
		iter.getObject ()->getField  (ifds::EWI, severityCode, BF::HOST, false);

		long nErrNum = errNum.strip ().stripLeading ('0').convertToULong ();
		if(errNum.empty())
			return (GETCURRENTHIGHESTSEVERITY ());
		switch  (nErrNum)
		{             
		case ABSOLUTE_VALUE_THRESHOLD_VALIDATION:
			{
				getErrMsg ( IFASTERR::ABSOLUTE_VALUE_THRESHOLD_BREACHED, 
					CND::ERR_ABSOLUTE_VALUE_THRESHOLD_BREACHED, 
					CND::WARN_ABSOLUTE_VALUE_THRESHOLD_BREACHED, 
					BF::HOST);
			}
			break;
		case PERCENTAGE_OF_CLASS_HOLDINGS_VALIDATION:
			{
				getErrMsg ( IFASTERR::PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED, 
					CND::ERR_PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED, 
					CND::WARN_PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED, 
					BF::HOST);
			}
			break;
		case INITIAL_MONEY_IN_TO_A_CLASS_VALIDATION:
			{
				getErrMsg ( IFASTERR::INITIAL_MONEY_IN_TO_A_CLASS, 
					CND::ERR_INITIAL_MONEY_IN_TO_A_CLASS, 
					CND::WARN_INITIAL_MONEY_IN_TO_A_CLASS, 
					BF::HOST);
			}
			break;
		case PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_VALIDATION:
			{
				getErrMsg ( IFASTERR::PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY, 
					CND::ERR_PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_BREACHED, 
					CND::WARN_PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_BREACHED, 
					BF::HOST);
			}
			break;		
		case PERCENTAGE_OF_TRADES_AMOUNT_TYPE_VALIDATION:
			{
				getErrMsg ( IFASTERR::PERCENTAGE_OF_TRADES_AMOUNT_TYPE, 
					CND::ERR_PERCENTAGE_OF_TRADES_AMOUNT_TYPE_BREACHED, 
					CND::WARN_PERCENTAGE_OF_TRADES_AMOUNT_TYPE_BREACHED, 
					BF::HOST);
			}
			break;	
		case FUND_COMPANY_APPROVAL_REQUIRED:
			{
				if  (severityCode == EWI_WARNING)
					ADDCONDITIONFROMFILE (CND::WARN_FUND_COMPANY_APPROVAL_REQUIRED);
				if  (severityCode == EWI_ERROR)
					ADDCONDITIONFROMFILE (CND::ERR_FUND_COMPANY_APPROVAL_REQUIRED);
			}
			break;
		case GENERAL_AGREEMENT_NOT_AVAILABLE:
			{
				if  (severityCode == EWI_WARNING)
					ADDCONDITIONFROMFILE (CND::WARN_GENERAL_AGREEMENT_NOT_AVAILABLE);
				if  (severityCode == EWI_ERROR)
					ADDCONDITIONFROMFILE (CND::ERR_GENERAL_AGREEMENT_NOT_AVAILABLE);
			}
			break;
		case AMOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT:
			{
				if  (severityCode == EWI_WARNING)
					ADDCONDITIONFROMFILE (CND::WARN_ACCOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT);
				if  (severityCode == EWI_ERROR)
					ADDCONDITIONFROMFILE (CND::ERR_ACCOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT);
			}
			break;
		default:
			assert(0);
		}
		++iter;

	}
   return (GETCURRENTHIGHESTSEVERITY ());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/UnusualTradingValidation.cpp-arc  $*/
