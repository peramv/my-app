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
// ^FILE   : TransactionDetailsBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : TransactionDetailsBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include "bankinstructions4trxnlist.hpp"



#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TransactionDetailsBankInstructionsList : 
   public BankInstructions4TrxnList
{
public:
   // X-structors
   TransactionDetailsBankInstructionsList (BFAbstractCBO &parent);
   virtual ~TransactionDetailsBankInstructionsList();
   // Initialize function
   SEVERITY init (const DString &dstrAccountNum,
      const BFDataGroupId &idDataGroup, 
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionDetailsBankInstructionsList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:58:16   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Nov 10 2003 14:53:08   popescu
//Revised the names of the suppporting objects based on Desktop's naming standards
//
//   Rev 1.0   Oct 19 2003 19:08:40   popescu
//Initial revision.
//
//
 */
