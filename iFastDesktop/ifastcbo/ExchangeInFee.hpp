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
// ^FILE      : ExchangeInFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : ExchangeInFee
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
class Trade;

class IFASTCBO_LINKAGE ExchangeInFee : public TransFeeRate
{
public:
   ExchangeInFee (BFAbstractCBO &parent);
   virtual ~ExchangeInFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
protected:
   virtual bool useToSide ();
   virtual bool ignoreTypeForFeeRate ();
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ExchangeInFee.hpp-arc  $
//
//   Rev 1.4   Mar 02 2005 08:41:00   popescu
//PET 1117/56 show and validate exch in/out fee base on set-up
//
//   Rev 1.3   Nov 17 2004 16:14:58   popescu
//PET 1117/06, Trade processing fees
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