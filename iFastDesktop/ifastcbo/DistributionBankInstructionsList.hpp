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
// ^FILE   : DistributionBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : DistributionBankInstructionsList
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

class IFASTCBO_LINKAGE DistributionBankInstructionsList : public BankInstructionsExList
{
public:
   // X-structors
   DistributionBankInstructionsList(BFAbstractCBO &parent);
   virtual ~DistributionBankInstructionsList();

protected:
   virtual SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, 
      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doCreateObject(const BFData &data, BFCBO *&pObjOut);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DistributionBankInstructionsList.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:30:52   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Oct 04 2003 15:58:54   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.1   Jun 03 2003 20:58:46   popescu
//Added the Ex Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
//
//   Rev 1.0   Jun 01 2003 17:09:38   popescu
//Initial revision.
//
 */
