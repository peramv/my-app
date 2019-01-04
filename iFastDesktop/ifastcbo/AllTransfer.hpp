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
// ^FILE   : AllTransfer.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : AllTransfer
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\transfer.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE AllTransfer : public Transfer
{
public:
   AllTransfer (BFAbstractCBO &parent);
   virtual ~AllTransfer ();
protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateSegBackdates (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMasterActAMS(const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
//validation methods
   SEVERITY validateAllFundTransfer (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRedCodeExclCodes ( const DString &redCode,
                                               const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateTIKRedCodes ( const DString &redCode,
                                          const BFDataGroupId& idDataGroup);
   virtual SEVERITY getAtCostTIKStatus ( const BFDataGroupId& idDataGroup, 
                                         const DString& dstrFundCodeIn, 
                                         const DString& dstrClassCodeIn,
                                         bool  blInAllocation,
                                         bool &blIsAtCostTIK);
   virtual bool isWireSupported (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
   SEVERITY validateAnnuitantGender (const BFDataGroupId &idDataGroup);
   bool getContractTypeAndVersion ( const BFDataGroupId &idDataGroup,
		  						    const DString &dstrAccountNum,	
									DString &contractType, 
									DString &contractVer);

private:
   SEVERITY allFundsRelatedChanges (const BFDataGroupId& idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AllTransfer.hpp-arc  $
//
//   Rev 1.18   Mar 30 2007 14:13:16   jankovii
//PET 2292 FN01 - Switch Settlement.
//
//   Rev 1.17   Jun 14 2006 16:19:48   popescu
//PET 2102.FN02 Flex 
//
//   Rev 1.16   Jun 14 2006 10:52:16   jankovii
//PET2102 FN02 - Manulife Flex  Trade/Systematic Entry.
//
//   Rev 1.15   May 25 2006 09:42:18   jankovii
//PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
//
//   Rev 1.14   Dec 17 2004 16:45:18   popescu
//PET 1117/06, fixed: user blocked to book an alltransfer due to to fund/class being set as required
//
//   Rev 1.13   Dec 07 2004 01:37:28   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.12   Dec 03 2004 10:46:06   popescu
//PET 1117/06, fees processing
//
//   Rev 1.11   Nov 30 2004 20:09:54   popescu
//PET 1117/06
//
//   Rev 1.10   Nov 06 2004 00:39:52   popescu
//PET 1117/06, synch changes
//
//   Rev 1.2   Nov 04 2004 17:37:06   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.1   Nov 02 2004 19:19:22   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.0   Oct 29 2004 20:27:42   popescu
//Initial revision.
//
//   Rev 1.0   Oct 01 2004 19:30:06   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/