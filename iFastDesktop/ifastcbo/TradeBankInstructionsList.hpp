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
// ^FILE   : TradeBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 2004
//
// ^CLASS    : TradeBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "bankinstructionsexlist.hpp"


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeBankInstructionsList : public BankInstructionsExList
{
public:
   // X-structors
   TradeBankInstructionsList(BFAbstractCBO &parent);
   virtual ~TradeBankInstructionsList();
   SEVERITY init ( const DString &accountNum,
                   bool bRebook,
                   const BFDataGroupId &idDataGroup, 
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING
                 );
protected:
   virtual SEVERITY doCreateNewObject (BFCBO *&pBase, 
                                       DString &strKey, 
                                       const BFDataGroupId& idDataGroup
                                      );
   virtual SEVERITY doCreateObject (const BFData& data, 
                                    BFCBO *&pObjOut
                                   );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeBankInstructionsList.hpp-arc  $
//
//   Rev 1.3   Aug 08 2005 09:13:54   Yingbaol
//PET1235,FN01:fix banking issue
//
//   Rev 1.2   Dec 11 2004 11:47:58   popescu
//PET 1117/56 more fixes, pending trade mods
//
//   Rev 1.1   Nov 14 2004 14:57:48   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Nov 01 2004 12:46:52   popescu
//Initial revision.
//
//Initial revision.
//
 */
