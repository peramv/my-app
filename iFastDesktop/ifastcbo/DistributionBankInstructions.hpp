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
// ^FILE      : DistributionBankInstructions.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : 01/08/2003
//
// ^CLASS     : DistributionBankInstructions
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\bankinstructionsex.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE DistributionBankInstructions : public BankInstructionsEx
{
public:
   DistributionBankInstructions (BFAbstractCBO &parent);
   virtual ~DistributionBankInstructions ();

protected:
   virtual SEVERITY preInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY postInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInitBeforeCloning (const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentCurrency ( DString &currency,
                                        DString &description,
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentProcessDate ( DString &processDate, 
                                           const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DistributionBankInstructions.hpp-arc  $
//
//   Rev 1.10   Sep 29 2005 18:57:22   popescu
//Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
//
//   Rev 1.9   Nov 14 2004 14:30:50   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Sep 23 2004 10:10:08   popescu
//PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
//
//   Rev 1.7   Sep 09 2004 13:19:40   popescu
//PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
//
//   Rev 1.6   Feb 13 2004 18:49:30   popescu
//PTS 10027180, set the file processor field to read only for distribution banking
//
//   Rev 1.5   Dec 29 2003 18:35:42   popescu
//PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
//
//   Rev 1.4   Dec 22 2003 16:28:48   popescu
//PTS 10025157, Rel 54 synch-up v, 1.2.1.0.
//
//   Rev 1.3   Oct 04 2003 15:58:50   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.2   Jun 18 2003 17:45:08   popescu
//RRIF Banking Enhancement , business rules, bug fixes 
//
//   Rev 1.1   Jun 03 2003 20:58:42   popescu
//Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
//
//   Rev 1.0   Jun 01 2003 17:09:36   popescu
//Initial revision.
//
 */