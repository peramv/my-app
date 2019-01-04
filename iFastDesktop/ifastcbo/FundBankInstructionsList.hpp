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
// ^FILE   : FundBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : FundBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\bankinstructionslist.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundBankInstructionsList : public BankInstructionsList
{
public:
   // X-structors
   FundBankInstructionsList(BFAbstractCBO &parent);
   virtual ~FundBankInstructionsList();

   // Initialize function
   SEVERITY init(const DString& dstrFundCode, 
      const BFDataGroupId &idDataGroup,
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY init(const DString &dstrFundCode, 
      const DString &dstrClassCode, 
      const BFDataGroupId &idDataGroup,
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBankInstructionsList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:41:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Jun 09 2003 17:40:04   popescu
//Added support for fund and class search, still stopped at the Gui level, because it shouldn't be functional yet; do not know the id for the bank entity when seraching for bank using fund and class
//
//   Rev 1.0   May 31 2003 12:00:52   popescu
//Initial revision.
//
 */
