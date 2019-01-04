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
//    Copyright 2010, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : EstateAllocation.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : EstateAllocation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class EstateAllocationDetailsList;
class EstateAllocationInterestList;

class IFASTCBO_LINKAGE EstateAllocation : public MFCanBFCbo
{
public:
   EstateAllocation( BFAbstractCBO &parent );
   virtual ~EstateAllocation();
   SEVERITY init(const BFData& data);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup);
   
   virtual SEVERITY doValidateField( const BFFieldId &fieldId,
                                     const DString& strValue,
                                     const BFDataGroupId& idDataGroup );

   SEVERITY EstateAllocation::calculateFees(const BFDataGroupId &idDataGroup);
   SEVERITY recalculateAmount(const DString& dstrAmount, const DString& dstrAmountType, 
                              const DString& dstrFundNAV, const BFDataGroupId& idDataGroup);
   SEVERITY recalculateForPercentChange(const BFDataGroupId& idDataGroup);
   SEVERITY recalculateForAmountChange(const BFDataGroupId& idDataGroup);
   SEVERITY recalculateForUnitsChange(const BFDataGroupId& idDataGroup);
   SEVERITY validateAddressCode(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateAddressLevel(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY updateAddress(const BFDataGroupId& idDataGroup);

protected:
   SEVERITY setBenefAddrCodeSubst(const BFDataGroupId &idDataGroup);

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EstateAllocation.hpp-arc  $
//
//   Rev 1.1   10 Aug 2012 13:06:54   if991250
//Estate Allocation
//
//   Rev 1.0   25 Jul 2012 15:26:08   if991250
//Initial revision.
//
*/
