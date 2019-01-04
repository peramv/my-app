#pragma once
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
// FILE   : RDSPTradeValidation.hpp
// AUTHOR : 
// DATE   : 
//
// CLASS    : RDSPTradeValidation
// SUBCLASS :
//
// CLASS DESCRIPTION :
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

class IFASTCBO_LINKAGE RDSPTradeValidation : public MFCanBFCbo, private boost::noncopyable
{
public:
  RDSPTradeValidation(BFAbstractCBO &parent);
  virtual ~RDSPTradeValidation();
  
  SEVERITY init(const DString &dstrAccountNum,
				const DString &dstrFundCode, 
                const DString &dstrClassCode, 
				const DString &dstrTransType,
				const DString &dstrEffectiveDate, 
				const DString &dstrDepositType,
				const DString &dstrRedCode,
				const DString &dstrAmount,
				const DString &dstrGRRepayReason,
				const DString &dstrRDSPPaymtDate);

  SEVERITY addConditions(const BFDataGroupId &idDataGroup);

};