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
// ^FILE   : ReinvestPurchase.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : ReinvestPurchase
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

class IFASTCBO_LINKAGE ReinvestPurchase : public Purchase
{
public:
   ReinvestPurchase (BFAbstractCBO &parent);
   virtual ~ReinvestPurchase();
protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup
                                    );
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup 
                                          );
   virtual SEVERITY validateDepositType ( const DString &depositType, 
                                          const BFDataGroupId &idDataGroup
                                        );
//validation methods
private:
   SEVERITY validateReinvestPurchaseSchedule (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReinvestPurchase.hpp-arc  $
//
//   Rev 1.7   Dec 24 2004 09:55:54   popescu
//PTS 10037200, modify button for reinvest purchase is not actvie
//
//   Rev 1.6   Dec 07 2004 01:37:46   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.5   Dec 03 2004 10:46:08   popescu
//PET 1117/06, fees processing
//
//   Rev 1.4   Nov 29 2004 20:30:38   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.3   Nov 14 2004 14:51:44   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Nov 06 2004 00:42:26   popescu
//PET 1117/06, synch changes
//
//   Rev 1.1   Nov 04 2004 17:38:26   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Oct 29 2004 20:27:36   popescu
//Initial revision.
//
*/