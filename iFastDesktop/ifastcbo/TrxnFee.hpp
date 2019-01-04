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
// ^FILE      : TrxnFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : TrxnFee
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

class IFASTCBO_LINKAGE TrxnFee : public TransFeeRate
{
public:
   TrxnFee (BFAbstractCBO &parent, const DString &feeCode);
   virtual ~TrxnFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY setFeeType (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup
                                          );
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeProperties (const BFDataGroupId &idDataGroup);
   virtual bool useFeeModelCode ();
private:
   bool isApplicableForFund (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TrxnFee.hpp-arc  $
//
//   Rev 1.4   Jan 14 2005 10:31:10   popescu
//PTS 10037865, charge option field should be 'Charge' and locked for Conditionrate and all other fees, but TrxnFee where user should be allowed to change its value.
//
//   Rev 1.3   Dec 10 2004 18:12:10   popescu
//PET 1117/06, more fixes
//
//   Rev 1.2   Dec 02 2004 20:59:44   popescu
//PET 1117/06, more fee fixes
//
//   Rev 1.1   Nov 24 2004 21:36:46   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.0   Nov 18 2004 11:55:48   popescu
//Initial revision.
//

//
 */