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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : SettlementTradeBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// ^CLASS    : SettlementTradeBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\bankinstructionsexlist.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SettlementTradeBankInstructionsList : public BankInstructionsExList
{
public:
   // X-structors
   SettlementTradeBankInstructionsList(BFAbstractCBO &parent);
   virtual ~SettlementTradeBankInstructionsList();

protected:
   virtual SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, 
      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTradeBankInstructionsList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:54:20   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Oct 04 2003 16:01:02   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.0   Jun 10 2003 16:13:12   popescu
//Initial revision.
//
//
 */
