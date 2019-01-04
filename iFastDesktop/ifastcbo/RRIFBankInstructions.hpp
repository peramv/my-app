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
// ^FILE      : RRIFBankInstructions.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : 01/08/2003
//
// ^CLASS     : RRIFBankInstructions
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\bankinstructionsex.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE RRIFBankInstructions : public BankInstructionsEx
{
public:
   RRIFBankInstructions(BFAbstractCBO &parent);
   virtual ~RRIFBankInstructions();
protected:
   virtual SEVERITY preInit (
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY postInit (
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges(
                              const BFFieldId& idField, 
                              const BFDataGroupId& idDataGroup);
   virtual SEVERITY doInitBeforeCloning (
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentCurrency (
                              DString &currency,
                              DString &description,
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentProcessDate ( DString &processDate, 
                                           const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFBankInstructions.hpp-arc  $
//
//   Rev 1.10   Sep 29 2005 18:57:32   popescu
//Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
//
//   Rev 1.9   Nov 14 2004 14:53:22   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Sep 23 2004 10:10:24   popescu
//PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
//
//   Rev 1.7   Sep 09 2004 13:19:54   popescu
//PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
//
//   Rev 1.6   Dec 29 2003 18:35:44   popescu
//PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
//
//   Rev 1.5   Oct 04 2003 16:00:52   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.4   Jun 18 2003 17:45:10   popescu
//RRIF Banking Enhancement , business rules, bug fixes 
//
//   Rev 1.3   Jun 05 2003 10:42:20   popescu
//business rules work for banking
//
//   Rev 1.2   Jun 03 2003 20:59:20   popescu
//Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
//
//   Rev 1.1   May 31 2003 20:30:28   popescu
//RRIF work part ||
//
//   Rev 1.0   May 31 2003 12:00:56   popescu
//Initial revision.
//
 */