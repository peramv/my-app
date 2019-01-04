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
// ^FILE      : TradeBankInstructions.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : October 2004
//
// ^CLASS     : TradeBankInstructions
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


class IFASTCBO_LINKAGE TradeBankInstructions : public BankInstructionsEx
{
public:
   TradeBankInstructions(BFAbstractCBO &parent);
   virtual ~TradeBankInstructions();
   SEVERITY init (const BFData &data);
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
   virtual SEVERITY sSetFieldsReadOnly4RegAgent(const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeBankInstructions.hpp-arc  $
//
//   Rev 1.4   Apr 24 2012 21:26:44   wp040039
//PETP0187485 - Trade Entry And Processing
//
//   Rev 1.3   Sep 29 2005 18:58:10   popescu
//Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
//
//   Rev 1.2   Dec 11 2004 13:25:34   popescu
//PET 1117/06, more fixes for banking instr in pending mode.
//
//   Rev 1.1   Nov 14 2004 14:57:46   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Nov 01 2004 12:46:48   popescu
//Initial revision.
//
//
 */