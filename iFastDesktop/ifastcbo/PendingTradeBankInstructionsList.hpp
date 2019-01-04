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
// ^FILE   : PendingTradeBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : PendingTradeBankInstructionsList
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

class IFASTCBO_LINKAGE PendingTradeBankInstructionsList : 
   public BankInstructions4TrxnList
{
public:
   // X-structors
   PendingTradeBankInstructionsList (BFAbstractCBO &parent);
   virtual ~PendingTradeBankInstructionsList();
   // Initialize function
   SEVERITY initLastEFT ( const DString &accountNum,
                          const DString &transType,
                          const DString &currency,
                          const DString &payType,
                          const DString &effectiveDate,
                          const BFDataGroupId &idDataGroup, 
                          const DString &dstrTrack = I_("N"), 
                          const DString &dstrPageName = NULL_STRING);
   SEVERITY init ( const DString &accountNum,
                   const BFDataGroupId &idDataGroup, 
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PendingTradeBankInstructionsList.hpp-arc  $
//
//   Rev 1.4   27 Jul 2007 15:40:50   popescu
//Incident 948449 - disabled the last EFT banking records call
//
//   Rev 1.3   Nov 14 2004 14:51:00   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Nov 04 2004 17:38:16   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.1   Nov 10 2003 14:53:02   popescu
//Revised the names of the suppporting objects based on Desktop's naming standards
//
//   Rev 1.0   Oct 19 2003 19:08:38   popescu
//Initial revision.
//
//
 */
