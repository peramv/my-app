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
// ^FILE   : RRIFBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : RRIFBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\bankinstructionsexlist.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RRIFBankInstructionsList : public BankInstructionsExList
{
public:
   // X-structors
   RRIFBankInstructionsList(BFAbstractCBO &parent);
   virtual ~RRIFBankInstructionsList();

protected:
   virtual SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, 
      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFBankInstructionsList.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:53:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Oct 04 2003 16:00:56   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.1   Jun 03 2003 20:59:28   popescu
//Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
//
//   Rev 1.0   May 31 2003 12:00:58   popescu
//Initial revision.
//
 */
