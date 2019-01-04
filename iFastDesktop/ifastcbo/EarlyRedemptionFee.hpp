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
// ^FILE      : EarlyRedemptionFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : EarlyRedemptionFee
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include "transfeecharge.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE EarlyRedemptionFee : public TransFeeCharge
{
public:
   EarlyRedemptionFee (BFAbstractCBO &parent);
   virtual ~EarlyRedemptionFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
   virtual SEVERITY restore ( BFCBO &rpParent, const BFDataGroupId &idDataGroup);

protected:
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup
                                    );
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EarlyRedemptionFee.hpp-arc  $
//
//   Rev 1.6   Jan 13 2006 17:06:30   AGUILAAM
//IN 518397 - for rebook of trade that's not entered thru Desktop, get ChargeERSTTRFee from original trade instead of TransFee (it does not exist in this case) 
//
//   Rev 1.5   Dec 08 2004 22:08:14   popescu
//PET 1117/06, more fees
//
//   Rev 1.4   Nov 17 2004 16:14:56   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.3   Nov 15 2004 16:22:26   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.1   Nov 09 2004 16:49:12   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 05 2004 17:06:46   popescu
//Initial Revision
//
//   Rev 1.1   Nov 04 2004 17:37:00   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 04 2004 11:03:40   popescu
//Initial revision.
//
 */