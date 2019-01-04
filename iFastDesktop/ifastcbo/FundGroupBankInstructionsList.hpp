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
// ^FILE   : FundGroupBankInstructionsList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
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

class IFASTCBO_LINKAGE FundGroupBankInstructionsList : public BankInstructionsList
{
public:

   FundGroupBankInstructionsList (BFAbstractCBO &parent);
   virtual ~FundGroupBankInstructionsList();

   SEVERITY init( const DString& dstrFundGroup, 
                  const BFDataGroupId &idDataGroup,
                  const DString &dstrTrack = I_("N"), 
                  const DString &dstrPageName = NULL_STRING);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundGroupBankInstructionsList.hpp-arc  $
//
//   Rev 1.2   Oct 18 2006 15:54:00   popescu
//PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
//
//   Rev 1.1   Nov 14 2004 14:42:26   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Sep 21 2004 16:43:00   HERNANDO
//Initial revision.
