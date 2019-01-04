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
// ^FILE      : AcquisitionFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : AcquisitionFee
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include "transfeerate.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class Trade;
class AcqFeeInquiry;
class SplitCommissionList;
class TradeFundAlloc;

class IFASTCBO_LINKAGE AcquisitionFee : public TransFeeRate
{
public:
   AcquisitionFee ( BFAbstractCBO &parent);
   virtual ~AcquisitionFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
   virtual SEVERITY restore ( BFCBO &rpParent, 
                              const BFDataGroupId &idDataGroup);
   SEVERITY setFeeRate(const DString& dstrFeeRate, const BFDataGroupId& idDataGroup);
   virtual SEVERITY init (const BFData &viewData);
   SEVERITY applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup);
protected:
   AcquisitionFee ( BFAbstractCBO &parent, 
                    const DString &feeCode);
   void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   SEVERITY getAcqFeeDefault ( AcqFeeInquiry *&pAcqFeeInquiry,
                               const BFDataGroupId &idDataGroup);
   SEVERITY getSplitCommission ( SplitCommissionList *&pSplitCommissionList,
                                 const BFDataGroupId &idDataGroup,
								 bool bCreate =true,
								 bool bGetDefault = false);
   SEVERITY getFirstFELTradeFundAlloc( TradeFundAlloc *&pTradeFundAlloc, const BFDataGroupId &idDataGroup);

   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeMinMax (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeType (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeProperties (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setChargeOption (const BFDataGroupId &idDataGroup);
   bool propagateFeeRateChangeToFundAlloc(const BFDataGroupId &idDataGroup, bool bApplyToSplitComm = false);
private:
   bool isTradeAllocated (const BFDataGroupId &idDataGroup);
   bool isFullExchange (const BFDataGroupId &idDataGroup);
   bool isFullRedemption (const BFDataGroupId &idDataGroup);
   bool isExchangeForNotNewMoney (const BFDataGroupId &idDataGroup);
   bool isApplicableForFund (const BFDataGroupId &idDataGroup);
   bool isApplicableForAmount (const BFDataGroupId &idDataGroup);
   bool isApplicableForAcqFeeOption (const BFDataGroupId &idDataGroup);
   bool isAcqFeeSameAsDefault (const BFDataGroupId &idDataGroup);
   DString _acqFeeDefault;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcquisitionFee.hpp-arc  $
//
//   Rev 1.14   Mar 04 2011 12:08:30   jankovii
//PET181943 FN01 - XMLPhase 2
//
//   Rev 1.13   Apr 11 2005 16:10:30   popescu
//Incident #285556 - user is able to charge any flat fee amount for full redemptions. Also, for partial redemption validation is meant to stop the user charge a fee that is more then the redemption amount.
//
//   Rev 1.12   Mar 03 2005 08:14:12   popescu
//PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
//
//   Rev 1.11   Feb 17 2005 10:20:24   popescu
//PTS 243445, set charge oprtion to '0'-Charge to save a view call to 197
//
//   Rev 1.10   Feb 15 2005 11:58:02   popescu
//237796, exchange fee default should be set to 0 if not a buy and sell exchange/transfer (not new money)
//
//   Rev 1.9   Feb 04 2005 17:16:08   popescu
//232973, Exchange Fee validation issue if amount if full exchange
//
//   Rev 1.8   Jan 23 2005 13:56:24   popescu
//PTS 10037346, made exchange available for the user
//
//   Rev 1.7   Jan 12 2005 18:51:08   popescu
//PTS 10037339, allowed user to set Redemption Fee up
//
//   Rev 1.6   Jan 10 2005 10:38:24   popescu
//PTS 10037553, fixed fees properties in pending mode and trade reset of the trans type combo
//
//   Rev 1.5   Jan 04 2005 16:14:52   popescu
//PTS 10037245, enable acq fee default for user input if trade is allocated and DisableFee4Alloc is turned off
//
//   Rev 1.4   Dec 09 2004 22:30:54   popescu
//PET 11717/06, fees and mod pending trades
//
//   Rev 1.3   Dec 08 2004 22:08:10   popescu
//PET 1117/06, more fees
//
//   Rev 1.2   Nov 17 2004 16:14:42   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.1   Nov 15 2004 16:22:16   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.0   Nov 15 2004 13:38:58   popescu
//Initial revision.
//
//   Rev 1.0   Nov 10 2004 09:31:20   popescu
//Initial revision.
//
//   Rev 1.0   Nov 06 2004 00:35:10   popescu
//Initial revision.
//
//   Rev 1.0   Nov 04 2004 11:03:24   popescu
//Initial revision.
//
 */