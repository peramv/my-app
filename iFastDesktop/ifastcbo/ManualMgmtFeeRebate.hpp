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
// ^FILE   : ManualMgmtFeeRebate.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Sept, 2007
//
// ^CLASS    : ManualMgmtFeeRebate
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

class IFASTCBO_LINKAGE ManualMgmtFeeRebate : public ManualDividend
{
public:
   ManualMgmtFeeRebate (BFAbstractCBO &parent);
   virtual ~ManualMgmtFeeRebate();
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
   virtual SEVERITY validateESGSettle ( const DString &strValue, 
                                        const BFDataGroupId &idDataGroup);
private:
   bool isMgtFeeRbtElig ( const DString &fundCode, 
                          const DString &classCode, 
                          const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ManualMgmtFeeRebate.hpp-arc  $
//
//   Rev 1.1   Sep 16 2007 15:42:02   jankovii
//IN #990336 - User is unable to process manual/adhoc MFR trades.
//
//   Rev 1.0   Sep 06 2007 17:24:24   popescu
//Initial revision.
//
//Initial revision.
//
*/