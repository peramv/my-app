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
// ^FILE      : ExchangeFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : Jan 2005
//
// ^CLASS     : ExchangeFee
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

class IFASTCBO_LINKAGE ExchangeFee : public AcquisitionFee 
{
public:
   ExchangeFee (BFAbstractCBO &parent);
   virtual ~ExchangeFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
protected:
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeProperties (const BFDataGroupId &idDataGroup);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ExchangeFee.hpp-arc  $
//
//   Rev 1.1   Jan 31 2005 10:09:32   popescu
//PTS 10038434, set the charge option field to read only, the fee is not driven by set-up
//
//   Rev 1.0   Jan 24 2005 10:26:22   popescu
//Initial revision.
//

 */