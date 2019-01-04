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
// ^FILE      : RedemptionFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : RedemptionFee
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include "acquisitionfee.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class Trade;

class IFASTCBO_LINKAGE RedemptionFee : public AcquisitionFee 
{
public:
   RedemptionFee (BFAbstractCBO &parent);
   virtual ~RedemptionFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
protected:
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeMinMax (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeProperties (const BFDataGroupId &idDataGroup);
   virtual void getFeeConfigDefaults ( bool bChargeOptionDefaultsRead,
                                       bool bChargeTradeFeeOptionDefaultsRead,
                                       bool bChargeFeeTypeOptionDefaultsRead,
                                       const BFDataGroupId &idDataGroup);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RedemptionFee.hpp-arc  $
//
//   Rev 1.6   Apr 11 2005 16:10:36   popescu
//Incident #285556 - user is able to charge any flat fee amount for full redemptions. Also, for partial redemption validation is meant to stop the user charge a fee that is more then the redemption amount.
//
//   Rev 1.5   Feb 28 2005 11:29:26   popescu
//PET 1117/56, set the correct min/max values based on the fee types
//
//   Rev 1.4   Jan 31 2005 10:09:36   popescu
//PTS 10038434, set the charge option field to read only, the fee is not driven by set-up
//
//   Rev 1.3   Jan 23 2005 13:57:22   popescu
//PTS 10037346, made exchange available for the user
//
//   Rev 1.2   Jan 12 2005 20:00:14   popescu
//PTS 10037339, fixed min/max for percentage type fee and do not allow redemption fee for an AFT environment
//
//   Rev 1.1   Jan 12 2005 18:52:34   popescu
//PTS 10037339, allowed user to set Redemption Fee up
//
//   Rev 1.0   Jan 12 2005 17:30:18   popescu
//Initial revision.
//

 */