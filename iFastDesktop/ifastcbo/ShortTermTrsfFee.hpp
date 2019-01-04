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
// ^FILE      : ShortTermTrsfFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : ShortTermTrsfFee
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

class IFASTCBO_LINKAGE ShortTermTrsfFee : public TransFeeCharge
{
public:
   ShortTermTrsfFee (BFAbstractCBO &parent);
   virtual ~ShortTermTrsfFee();
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
   bool isFeeApplicableForFunds (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShortTermTrsfFee.hpp-arc  $
//
//   Rev 1.6   Jan 13 2006 17:06:34   AGUILAAM
//IN 518397 - for rebook of trade that's not entered thru Desktop, get ChargeERSTTRFee from original trade instead of TransFee (it does not exist in this case) 
//
//   Rev 1.5   Dec 08 2004 22:08:16   popescu
//PET 1117/06, more fees
//
//   Rev 1.4   Nov 17 2004 16:15:30   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.3   Nov 15 2004 16:23:32   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.1   Nov 09 2004 16:50:42   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 05 2004 21:31:08   popescu
//Initial revision.
//
//   Rev 1.1   Nov 04 2004 17:37:00   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 04 2004 11:03:40   popescu
//Initial revision.
//
 */