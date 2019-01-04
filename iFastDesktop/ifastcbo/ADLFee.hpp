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
// ^FILE      : ADLFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : July 2004
//
// ^CLASS     : ADLFee
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

class IFASTCBO_LINKAGE ADLFee : public TransFeeCharge
{
public:
   ADLFee (BFAbstractCBO &parent);
   virtual ~ADLFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
protected:
   virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
private:
   bool isApplicableForFund (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ADLFee.hpp-arc  $
//
//   Rev 1.7   Dec 17 2004 17:39:54   popescu
//PET 1117/06, removed refresh method, no use for it.
//
//   Rev 1.6   Dec 17 2004 17:36:38   popescu
//PET 1117/06, restrict the applicability of ADL Fee to funds for which the value of UnitsCal is part of AntiDilutionCalc generic control
//
//   Rev 1.5   Nov 17 2004 16:14:50   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.4   Nov 15 2004 16:22:20   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.3   Nov 09 2004 16:49:00   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.2   Nov 05 2004 16:05:46   popescu
//PET 1117/06, TP
//
//   Rev 1.1   Nov 04 2004 17:37:00   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 04 2004 11:03:40   popescu
//Initial revision.
//
 */