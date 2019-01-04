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
// ^FILE      : TransFeeCharge.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November, 2004
//
// ^CLASS     : TransFeeCharge
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif
#include <ifastcbo\transfee.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE TransFeeCharge : public TransFee
{
public:
   TransFeeCharge (BFAbstractCBO &parent, const DString &feeCode);
   virtual ~TransFeeCharge();

   virtual SEVERITY init (const BFData &viewData);
   virtual SEVERITY init (const BFDataGroupId &idDataGroup);
//should respond whether the fee is a yes/no charge type of fee
   virtual bool isChargeFee (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup
                                    );
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup
                                          );
   virtual void getFeeConfigDefaults ( bool bChargeOptionDefaultsRead,
                                       bool bChargeTradeFeeOptionDefaultsRead,
                                       bool bChargeFeeTypeOptionDefaultsRead,
                                       const BFDataGroupId &idDataGroup
                                     );
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFeeCharge.hpp-arc  $
//
//   Rev 1.4   Dec 08 2004 22:08:30   popescu
//PET 1117/06, more fees
//
//   Rev 1.3   Nov 17 2004 16:15:54   popescu
//No change.
//
//   Rev 1.2   Nov 15 2004 16:23:38   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.0   Nov 05 2004 21:30:22   popescu
//Initial revision.
//
 */