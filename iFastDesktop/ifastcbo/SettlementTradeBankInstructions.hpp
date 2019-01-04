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
// ^FILE      : SettlementTradeBankInstructions.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : June 2003
//
// ^CLASS     : SettlementTradeBankInstructions
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


class IFASTCBO_LINKAGE SettlementTradeBankInstructions : public BankInstructionsEx
{
public:
   SettlementTradeBankInstructions(BFAbstractCBO &parent);
   virtual ~SettlementTradeBankInstructions();
   void setFieldsReadOnly (const BFDataGroupId& idDataGroup = BF::HOST, bool bReadOnly = false);
   bool hasPermChangeAddrBank ();
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTradeBankInstructions.hpp-arc  $
//
//   Rev 1.9   Sep 29 2005 18:57:34   popescu
//Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
//
//   Rev 1.8   Nov 14 2004 14:54:18   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.7   Sep 23 2004 10:10:28   popescu
//PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
//
//   Rev 1.6   Sep 09 2004 13:20:08   popescu
//PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
//
//   Rev 1.5   Feb 09 2004 10:15:46   FENGYONG
//PET965.FN1 SSB Profile restriction
//
//   Rev 1.4   Dec 29 2003 18:35:46   popescu
//PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
//
//   Rev 1.3   Oct 19 2003 19:16:44   popescu
//synch-up from 54, for  PTS 10023054
//
//   Rev 1.2   Oct 04 2003 16:00:58   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.1   Jun 18 2003 17:45:12   popescu
//RRIF Banking Enhancement , business rules, bug fixes 
//
//   Rev 1.0   Jun 10 2003 16:13:10   popescu
//Initial revision.
//
 */