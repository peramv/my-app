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
// ^FILE      : ConditionRate.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : ConditionRate
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

class IFASTCBO_LINKAGE ConditionRate : public TransFeeRate
{
public:
   ConditionRate (BFAbstractCBO &parent, const DString& feeCode);
   virtual ~ConditionRate();
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY setFeeType (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeProperties (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setChargeOption (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual bool useFeeModelCode ();
private:
   bool isApplicableForFeeModel (const BFDataGroupId &idDataGroup);
   bool isApplicableForAcqFeeOption (const BFDataGroupId &idDataGroup);
   SEVERITY calculateDiscountRate (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ConditionRate.hpp-arc  $
//
//   Rev 1.12   Mar 02 2005 09:34:28   popescu
//Incident # 254204, client condition rate is displayed with a default value of zero, even if the set-up does not exist for it. user is warned if the value of the fee is left to zero
//
//   Rev 1.11   Jan 14 2005 10:31:00   popescu
//PTS 10037865, charge option field should be 'Charge' and locked for Conditionrate and all other fees, but TrxnFee where user should be allowed to change its value.
//
//   Rev 1.10   Jan 10 2005 10:38:28   popescu
//PTS 10037553, fixed fees properties in pending mode and trade reset of the trans type combo
//
//   Rev 1.9   Dec 20 2004 14:19:20   popescu
//PTS 10037057, discount rate not updated when trade fee option changed to Override/Suppress
//
//   Rev 1.8   Dec 11 2004 11:47:24   popescu
//PET 1117/56 more fixes, pending trade mods
//
//   Rev 1.7   Dec 02 2004 20:59:18   popescu
//PET 1117/06, more fee fixes
//
//   Rev 1.6   Dec 01 2004 15:44:38   popescu
//PET 1117/56 fees processing, calculate the discount rate
//
//   Rev 1.5   Nov 24 2004 21:35:36   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.4   Nov 19 2004 14:19:24   popescu
//PET 1117/06, fees processing
//
//   Rev 1.3   Nov 17 2004 16:14:52   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.2   Nov 15 2004 16:22:24   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.0   Nov 06 2004 00:35:10   popescu
//Initial revision.
//
//   Rev 1.0   Nov 04 2004 11:03:24   popescu
//Initial revision.
//
 */