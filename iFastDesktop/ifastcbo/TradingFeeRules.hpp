#pragma once
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
//    Copyright 2003 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : TradingFeeRules.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : March, 2003
//
// ^CLASS    : TradingFeeRules
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

class FundFeeList;

class IFASTCBO_LINKAGE TradingFeeRules : public MFCanBFCbo, private boost::noncopyable
{
public:
	TradingFeeRules(BFAbstractCBO &parent);
   static SEVERITY getExchangeOutFeeRules(BFAbstractCBO &parent, 
      TradingFeeRules*& rpTradingFeeRules,
      const BFFieldId& tradeFeeFieldId, const BFFieldId& tradeFeeTypeFieldId,
      const BFFieldId& fundCodeFieldId, const BFFieldId& classCodeFieldId,
      const BFFieldId& effectiveDateFieldId, const BFFieldId& accountNumFieldId,
      const BFFieldId& brokerFieldId, const BFFieldId& branchFieldId,
      const BFFieldId& slsrepFieldId, 
      const BFDataGroupId& idDataGroup,
      bool ignoreFeeNotExists = true);
   static SEVERITY getERFeeRules(BFAbstractCBO &parent, 
      TradingFeeRules*& rpTradingFeeRules,
      const BFFieldId& tradeFeeFieldId, const BFFieldId& tradeFeeTypeFieldId,
      const BFFieldId& fundCodeFieldId, const BFFieldId& classCodeFieldId,
      const BFFieldId& effectiveDateFieldId, const BFFieldId& accountNumFieldId,
      const BFFieldId& brokerFieldId, const BFFieldId& branchFieldId,
      const BFFieldId& slsrepFieldId, 
      const BFDataGroupId& idDataGroup,
      bool ignoreFeeNotExists = true);
   static SEVERITY getSTTRFeeRules(BFAbstractCBO &parent, 
      TradingFeeRules*& rpTradingFeeRules,
      const BFFieldId& tradeFeeFieldId, const BFFieldId& tradeFeeTypeFieldId,
      const BFFieldId& fundCodeFieldId, const BFFieldId& classCodeFieldId,
      const BFFieldId& effectiveDateFieldId, const BFFieldId& accountNumFieldId,
      const BFFieldId& brokerFieldId, const BFFieldId& branchFieldId,
      const BFFieldId& slsrepFieldId, 
      const BFDataGroupId& idDataGroup,
      bool ignoreFeeNotExists = true);
	
	 SEVERITY getWithdrawalFeeRules( const DString &dstrTransType,
		                              const DString &dstrFeeCode,			 			  				  	                                               											          
											   TradingFeeRules*& rpTradingFeeRules,
												const DString &dstrTradeFee, 
												const DString &dstrTradeFeeType,
												const DString &dstrFundCode, 
												const DString &dstrClassCode,
												const DString &dstrEffectiveDate, 
												const DString &dstrAccountNum,
												const DString &dstrBroker, 
												const DString &dstrBranch,
												const DString &dstrSlsrep, 
												const BFDataGroupId& idDataGroup,
												bool ignoreFeeNotExists = true );

   virtual ~TradingFeeRules();
   SEVERITY validateTradingFee(const BFDataGroupId& idDataGroup);
   bool feeExists(const BFDataGroupId& idDataGroup);
private:
   
   SEVERITY init(const DString& strTradeTypeId, const DString& strFeeCode,
      const BFFieldId& tradeFeeFieldId, const BFFieldId& tradeFeeTypeFieldId,
      const BFFieldId& fundCodeFieldId, const BFFieldId& classCodeFieldId,
      const BFFieldId& effectiveDateFieldId, const BFFieldId& accountNumFieldId,
      const BFFieldId& brokerFieldId, const BFFieldId& branchFieldId,
      const BFFieldId& slsrepFieldId, 
      const BFDataGroupId& idDataGroup = BF::HOST,
      bool ignoreFeeNotExists = true);
private:
   SEVERITY initFeeDefaults(const BFDataGroupId& idDataGroup, bool ignoreFeeNotExists);
   FundFeeList *_pFundFeeList;
   DString _tradeType;
   DString _feeCode;
   BFFieldId _tradeFeeFieldId;
   BFFieldId _tradeFeeTypeFieldId;
   BFFieldId _tradeFeeMaxFieldId;
   BFFieldId _tradeFeeMinFieldId;
   BFFieldId _fundCodeFieldId;
   BFFieldId _classCodeFieldId;
   BFFieldId _effectiveDateFieldId;
   BFFieldId _accountNumFieldId;
   BFFieldId _brokerFieldId;
   BFFieldId _branchFieldId;
   BFFieldId _slsrepFieldId;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradingFeeRules.hpp-arc  $
//
//   Rev 1.9   Nov 14 2004 14:58:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Dec 17 2003 09:38:14   VADEANUM
//PTS 10025195 - syncup from 54.1P - rewrote getWithdrawalFeeRules() to support Allocation Funds Fees validation.
//
//   Rev 1.7   Dec 08 2003 15:28:54   popescu
//PTS 10023645, split commission re-work
//
//   Rev 1.6   Jul 29 2003 11:08:46   VADEANUM
//PET 809 F05 - Withdrawal Fee support.
//
//   Rev 1.5   Apr 04 2003 10:19:02   popescu
//split commsion work
//
//   Rev 1.4   Mar 21 2003 21:07:24   PURDYECH
//Sync 1.1.1.0 back to trunk
//
//   Rev 1.3   Mar 20 2003 11:26:04   popescu
//Early redemption fee and short term transfer fee work
//
//   Rev 1.2   Mar 19 2003 14:44:58   popescu
//Exchange Out fee automatic transfer, and Trad
//
//   Rev 1.1   Mar 18 2003 21:10:44   popescu
//Exchange out fee work
//
//   Rev 1.0   Mar 13 2003 15:24:12   popescu
//Initial revision.
*/
