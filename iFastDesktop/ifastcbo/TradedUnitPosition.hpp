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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : TradedUnitPosition.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : TradedUnitPosition
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradedUnitPosition : public MFCanBFCbo
{
public:

	TradedUnitPosition( BFAbstractCBO &parent );
	virtual ~TradedUnitPosition();

   
	SEVERITY init(const DString &accountNum,
	              const DString &fundCode,
				  const DString &classsCode,
				  const DString &amount,
				  const DString &amountType,
				  const DString &transNum,
				  const DString &transType,
				  const DString &tradeDate,
				  const DString &settleDate,
				  const DString &settleCurrency,
				  const DString &orderType,
				  const DString &transId,
				  const DString &exchRate,
				  const DString &dstrAccountTo,
				  const DString &dstrRedCode,
				  const DString &dstrPriceCode,
				  const DString &dstrPriceInCode,
				  const BFDataGroupId& idDataGroup);
	
	static void buildKey (const DString &accountNum,
	                      const DString &fundCode,
				          const DString &classsCode,
				          const DString &amount,
				          const DString &amountType,
				          const DString &transNum,
				          const DString &transType,
				          const DString &tradeDate,
				          const DString &settleDate,
				          const DString &settleCurrency,
				          const DString &orderType,
						  const DString &transId,
						  const DString &exchRate,
						  const DString &dstrAccountTo,
						  const DString &dstrRedCode,  
						  const DString &dstrPriceCode,
						  const DString &dstrPriceInCode,
                          DString &strKey);
protected:

private:

};

/* $Log::   
 */