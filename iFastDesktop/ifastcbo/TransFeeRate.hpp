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
// ^FILE      : TransFeeRate.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November, 2004
//
// ^CLASS     : TransFeeRate
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

class IFASTCBO_LINKAGE TransFeeRate : public TransFee
{
public:
   TransFeeRate (BFAbstractCBO &parent, const DString &feeCode);
   virtual ~TransFeeRate();

   virtual SEVERITY init (const BFData &viewData);
   virtual SEVERITY init (const BFDataGroupId &idDataGroup);
//should respond whether the fee is a yes/no charge type of fee
   virtual bool isChargeFee (const BFDataGroupId &idDataGroup);
   virtual void getField ( const BFFieldId &idField, 
                           DString &fieldValue, 
                           const BFDataGroupId &idDataGroup, 
                           bool formattedReturn = false
                         ) const;

   virtual SEVERITY setField ( const BFFieldId &idField, 
                               const DString &dstrValue,
                               const BFDataGroupId &idDataGroup, 
                               bool bFormatted = true, 
                               bool bSideEffect = false, 
                               bool bCheckCurrentValue = true);
protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup
                                    );
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup
                                          );
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeMinMax (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   virtual bool ignoreTypeForFeeRate ();
   bool isFeeTypePercentage (const BFDataGroupId &idDataGroup) const;
   void getFormattedFee ( const BFDataGroupId& idDataGroup, 
                          DString &strValue) const;
private:
   SEVERITY validateFeeRate ( const DString &strValue, 
                              const BFDataGroupId &idDataGroup
                            );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFeeRate.hpp-arc  $
//
//   Rev 1.6   Apr 09 2005 14:12:16   porteanm
//Incident 276992 - FeeRate not saved with the right precision.
//
//   Rev 1.5   Mar 02 2005 08:33:14   popescu
//PET 1117/56 added virtual method meant to let the base class know whether to ignore the fee type or not when sets the min/max or validates the fee rate against min/max
//
//   Rev 1.4   Nov 17 2004 16:16:02   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.3   Nov 15 2004 16:24:26   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.1   Nov 09 2004 16:51:18   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 05 2004 21:30:30   popescu
//Initial revision.
//
 */