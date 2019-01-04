#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : MgmtFeeRebate.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November, 2006
//
// ^CLASS    : MgmtFeeRebate
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\purchase.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE MgmtFeeRebate : public Purchase
{
public:
   MgmtFeeRebate (BFAbstractCBO &parent);
   virtual ~MgmtFeeRebate();
//whether tax rates are allowed
   virtual bool areTaxRatesAllowed (const BFDataGroupId &idDataGroup);
//whether split commissions are allowed
   virtual bool isSplitCommissionAllowed (const BFDataGroupId &idDataGroup);
//whether settle locations are allowed
   virtual bool isSettleLocAllowed (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId& idField, 
                                            const BFDataGroupId& idDataGroup);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual bool isWireSupported (const BFDataGroupId &idDataGroup);
   virtual SEVERITY RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MgmtFeeRebate.hpp-arc  $
//
//   Rev 1.2   01 Aug 2007 15:59:12   popescu
//Incident # 956780 - mgfeerebate should always be direct
//
//   Rev 1.1   Nov 16 2006 11:11:56   popescu
//PET 2252. FN01 - mgmt fee rebate
//
//   Rev 1.0   Nov 16 2006 10:45:02   popescu
//Initial revision.
//
*/