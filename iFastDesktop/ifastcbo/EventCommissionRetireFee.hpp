#pragma once


//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE      : EventCommissionRetireFee.hpp
// ^AUTHOR    : 
// ^DATE      : Aug 2012
//
// ^CLASS     : EventCommissionRetireFee
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
class Trade;

class IFASTCBO_LINKAGE EventCommissionRetireFee : public TransFeeCharge
{
public:
   EventCommissionRetireFee (BFAbstractCBO &parent, const DString &feeCode);
   EventCommissionRetireFee (BFAbstractCBO &parent);
   virtual ~EventCommissionRetireFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   bool isEventCommissionRetireApplicable(const BFDataGroupId &idDataGroup);
private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/EventCommissionRetireFee.hpp-arc  $
//
//   Rev 1.0   Aug 15 2012 15:00:02   dchatcha
//Initial revision.
//
