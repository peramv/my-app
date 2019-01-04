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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcqFeeInquiry.hpp
// ^AUTHOR : Shaobo Huang
// ^DATE   : Feb 11, 2000
//
// ^CLASS    : AcqFeeInquiry
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//       Acquisition Fee Calculation Inquiry
//


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE 
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT 
#else 
   #define IFASTCBO_LINKAGE CLASS_IMPORT 
#endif

class IFASTCBO_LINKAGE AcqFeeInquiry : public MFCanBFCbo, private boost::noncopyable
{
public:
   AcqFeeInquiry( BFAbstractCBO &parent );
   virtual ~AcqFeeInquiry();
   SEVERITY init( const DString& dstrTaxType,
                  const DString& dstrTransType,
                  const DString& dstrEffectiveDate,
                  const DString& dstrAmount,
                  const DString& dstrAmountType,
                  const DString& dstrFundCode,
                  const DString& dstrClassCode,
                  const DString& dstrCurrency,
                  const DString& dstrBrokerCode,
                  const DString& dstrFundToCode  = I_(""),
                  const DString& dstrClassToCode = I_(""),
						const DString& FlatPercent = I_("N"), 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING ,
						const DString& dstrToTaxType = I_("") ,
						const DString& AcctNumbr = NULL_STRING, 
				 const DString& tradeInDate = NULL_STRING);

   SEVERITY init();

   bool recordMatch( const DString& tradeTaxType, const DString& tradeTransType, 
                     const DString& tradeTradeDate, const DString& tradeAmount, 
                     const DString& tradeAmountType, const DString& tradeFundCode, 
                     const DString& tradeClassCode, const DString& tradeCurrency, 
                     const DString& tradeBrokerCode, const DString& tradeToFund, 
                     const DString& tradeToClass, const BFDataGroupId& idDataGroup );

   virtual void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   void setFundCurrency(const DString& dstrFundCurrency) {_dstrFundCurrency = dstrFundCurrency;}
private:

   DString _dstrFundCurrency;

   DString acqFeeTaxType;
   DString acqFeeTransType;
   DString acqFeeEffectiveDate;
   DString acqFeeAmount;
   DString acqFeeAmountType;
   DString acqFeeFromFund;
   DString acqFeeFromClass;
   DString acqFeeCurrency;
   DString acqFeeBrokerCode;
   DString acqFeeToFund;
   DString acqFeeToClass;
   DString acqFlatPercent;


};

