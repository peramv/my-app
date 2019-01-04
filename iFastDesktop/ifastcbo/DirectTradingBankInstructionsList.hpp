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
// ^FILE   : DirectTradingBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : DirectTradingBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\bankinstructions4shlist.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DirectTradingBankInstructionsList : 
   public BankInstructions4ShList
{
public:
   // X-structors
   DirectTradingBankInstructionsList (BFAbstractCBO &parent);
   virtual ~DirectTradingBankInstructionsList();

   // Initialize function
   SEVERITY initNew (const DString& shrNum, 
      const BFDataGroupId& idDataGroup);
   SEVERITY init (const DString& dstrShrNum, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DirectTradingBankInstructionsList.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:30:42   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Nov 10 2003 14:52:28   popescu
//Revised the names of the suppporting objects based on Desktop's naming standards
//
//   Rev 1.2   Oct 19 2003 16:44:18   popescu
//CIBC, PET809, FN 13 banking work
//
//   Rev 1.1   Oct 06 2003 12:47:34   popescu
//Removed un-wanted revision control comments
//
//   Rev 1.0   Oct 06 2003 12:45:34   popescu
//Initial revision.
 */
