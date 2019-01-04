#pragma once


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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : UnusualTradingValidation.hpp
// ^AUTHOR : 
// ^DATE   : March 2017
//
// ^CLASS    : UnusualTradingValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE UnusualTradingValidation : public MFCanBFCbo, private boost::noncopyable
{

public:
	UnusualTradingValidation(BFAbstractCBO &parent);
	virtual ~UnusualTradingValidation();

	   SEVERITY init( const DString &strAccountNum, 
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
				  const DString &dstrAMSCode     = NULL_STRING, 
				  const DString &dstrAMSType     = NULL_STRING,
				  const DString &dstrDepositType = NULL_STRING, 
				  const DString &dstrOrderType= NULL_STRING,
				  const DString &strToFundCode = NULL_STRING,
				  const DString &strToClassCode = NULL_STRING,
				  const DString &strToAccount = NULL_STRING,
				  const DString &strTradeInDate = NULL_STRING,
				  bool ignoreDataNotFound = true,
				  bool bFullExchPrntToPrnt = false,
				  const DString &Indc = I_(""),
				  const DString &adjForTransNum = I_(""));  

	SEVERITY addConditions ();

protected:

};