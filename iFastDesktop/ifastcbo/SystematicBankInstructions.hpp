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
// ^FILE      : SystematicBankInstructions.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : May, 2003
//
// ^CLASS     : SystematicBankInstructions
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


class IFASTCBO_LINKAGE SystematicBankInstructions : public BankInstructionsEx
{
public:
   SystematicBankInstructions (BFAbstractCBO &parent);
   virtual ~SystematicBankInstructions();
protected:
   virtual SEVERITY doApplyRelatedChanges (
                              const BFFieldId& idField, 
                              const BFDataGroupId& idDataGroup);
   virtual SEVERITY postInit (
                              const BFDataGroupId& idDataGroup);
   virtual SEVERITY doInitBeforeCloning (
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentCurrency (
                              DString &currency,
                              DString &description,
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentProcessDate ( DString &processDate, 
                                           const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SystematicBankInstructions.hpp-arc  $
//
//   Rev 1.8   Sep 29 2005 18:57:38   popescu
//Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
//
//   Rev 1.7   Nov 14 2004 14:56:44   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Sep 23 2004 10:10:34   popescu
//PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
//
//   Rev 1.5   Sep 09 2004 13:20:14   popescu
//PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
//
//   Rev 1.4   Nov 19 2003 10:17:22   popescu
//Fixed issue with copying banking info from Default banking to Systematic. In non-multi currency environment a bank info record should be copied only if the currencies of the sytematic transaction and bank acct match. This is a synch-up from Rel 54.0.0.0.3
//
//   Rev 1.3   Oct 04 2003 16:01:32   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.2   Jun 18 2003 17:45:14   popescu
//RRIF Banking Enhancement , business rules, bug fixes 
//
//   Rev 1.1   Jun 03 2003 20:59:30   popescu
//Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
//
//   Rev 1.0   Jun 01 2003 17:09:40   popescu
//Initial revision.
//
 */