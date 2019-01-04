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
// ^FILE   : ManualForeignCapGainAllocAdjustment.hpp
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : ManualForeignCapGainAllocAdjustment
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\manualdividend.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE ManualForeignCapGainAllocAdjustment : public ManualDividend
{
public:
   ManualForeignCapGainAllocAdjustment (BFAbstractCBO &parent);
   virtual ~ManualForeignCapGainAllocAdjustment();

   double getFCUnitPrice( const DString &fundCode,
                          const DString &classCode,
                          const DString &fromDate,
                          const DString &toDate,
                          const BFDataGroupId &idDataGroup );
                          
   virtual SEVERITY setField ( const BFFieldId &idField, 
                               const DString &dstrValue,
                               const BFDataGroupId &idDataGroup, 
                               bool bFormatted = true, 
                               bool bSideEffect = false, 
                               bool bCheckCurrentValue = true);

protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFromToFundClass ( const DString &fromCode,
                                              const DString &fromClass,
                                              const DString &toCode,
                                              const DString &toClass,
                                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateNegativeAmount( const DString &amount,
                                            const BFDataGroupId &idDataGroup);

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ManualForeignCapGainAllocAdjustment.hpp-arc  $
//
//   Rev 1.2   17 Aug 2009 10:38:40   popescu
//IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop - revised the code a little bit
//
//   Rev 1.1   Aug 17 2009 08:37:00   dchatcha
//IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop.
//

