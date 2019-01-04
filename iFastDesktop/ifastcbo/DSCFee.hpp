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
// ^FILE      : DSCFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : DSCFee
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

class IFASTCBO_LINKAGE DSCFee : public TransFeeRate
{
public:
   DSCFee (BFAbstractCBO &parent, const DString &feeCode);
   DSCFee (BFAbstractCBO &parent);
   virtual ~DSCFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
   virtual SEVERITY restore ( BFCBO &rpParent, 
                              const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY setFeeMinMax (const BFDataGroupId &idDataGroup);
private:
   bool isApplicableForFund (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSCFee.hpp-arc  $
//
//   Rev 1.3   Nov 27 2011 19:40:22   popescu
//INA Commission Work
//
//   Rev 1.2   Mar 03 2005 08:13:30   popescu
//PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
//
//   Rev 1.1   Feb 28 2005 09:04:32   popescu
//PET 1117/06, set the correct maximum for the fee; fee cannot be greater the trade amount
//
//   Rev 1.0   Nov 17 2004 15:57:12   popescu
//Initial revision.
//
//Initial revision.
//
 */