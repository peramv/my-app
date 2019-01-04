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
// ^FILE      : XferInFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : XferInFee
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "transfeerate.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class SplitCommissionList;
class TradeFundAlloc;

class IFASTCBO_LINKAGE XferInFee : public TransFeeRate
{
public:
   XferInFee (BFAbstractCBO &parent);
   virtual ~XferInFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
   virtual SEVERITY restore ( BFCBO &rpParent, 
                              const BFDataGroupId &idDataGroup);
   SEVERITY setFeeRate(const DString& dstrFeeRate, const BFDataGroupId& idDataGroup);
   virtual SEVERITY init (const BFData &viewData);
   SEVERITY applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup);
   bool isTradeAllocated (const BFDataGroupId &idDataGroup);
   SEVERITY getSplitCommission ( SplitCommissionList *&pSplitCommissionList,
                                 const BFDataGroupId &idDataGroup,
								 bool bCreate =true,
								 bool bGetDefault = false);
   SEVERITY getFirstFELTradeFundAlloc( TradeFundAlloc *&pTradeFundAlloc, const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeMinMax (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeType (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeProperties (const BFDataGroupId &idDataGroup);
   bool propagateFeeRateChangeToFundAlloc(const BFDataGroupId &idDataGroup, bool bApplyToSplitComm = false);
private:
   bool isApplicableForFund (const BFDataGroupId &idDataGroup);
   bool isROAApplicable (const BFDataGroupId &idDataGroup); 
   DString _acqFeeDefault;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/XferInFee.hpp-arc  $
//
//   Rev 1.7   Jun 19 2012 21:22:18   popescu
//2991448 - Exchange to FEL - Default FEL rate
//
//   Rev 1.6   Jul 04 2005 19:05:30   popescu
//Incident # 347073 - split commission is charged on the To side for environments where ROA is applicable.
//
//   Rev 1.5   Mar 03 2005 08:13:56   popescu
//PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
//
//   Rev 1.4   Jan 31 2005 10:05:36   popescu
//PTS 10038324, set charge option field to read only, there is no set-up for it.
//
//   Rev 1.3   Jan 28 2005 11:07:58   popescu
//PTS 10038324, fees display issues
//
//   Rev 1.2   Jan 28 2005 06:58:06   aguilaam
//PTS 10038324, fees display issues
//
//   Rev 1.1   Jan 21 2005 16:55:48   popescu
//PTS 10038132, not show the fees if from fund/ and class are not entered
//
//   Rev 1.0   Nov 17 2004 15:56:06   popescu
//Initial revision.
//
//   Rev 1.2   Nov 15 2004 16:22:32   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.0   Nov 10 2004 09:31:16   popescu
//Initial revision.
//
//   Rev 1.0   Nov 06 2004 00:35:10   popescu
//Initial revision.
//
//   Rev 1.0   Nov 04 2004 11:03:24   popescu
//Initial revision.
//
 */