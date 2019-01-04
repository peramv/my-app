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
// ^FILE   : ClientBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : ClientBankInstructionsList
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

class IFASTCBO_LINKAGE ClientBankInstructionsList : public BankInstructionsList
{
public:
   // X-structors
   ClientBankInstructionsList(BFAbstractCBO &parent);
   virtual ~ClientBankInstructionsList();

   // Initialize function
   SEVERITY init ( const BFDataGroupId &idDataGroup,  
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING);
   void setPayInstructionsAsParentCBO  (BFAbstractCBO * payInstructionsParent);
   BFAbstractCBO * getPayInstructionsParentCBO  ();
protected:
   SEVERITY doCreateNewObject ( BFCBO*& pBase, 
                                DString& strKey, 
                                const BFDataGroupId& idDataGroup);
private:
   BFAbstractCBO *_parentCBO;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ClientBankInstructionsList.hpp-arc  $
//
//   Rev 1.2   Sep 12 2006 10:52:10   popescu
//STP - PET 2192/11
//
//   Rev 1.1   Nov 14 2004 14:29:42   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   May 31 2003 12:00:50   popescu
//Initial revision.
//
 */
