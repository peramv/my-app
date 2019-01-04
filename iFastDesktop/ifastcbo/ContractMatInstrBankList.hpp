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
// ^FILE   : ContractMatInstrBankList.hpp
// ^AUTHOR : Chetan Balepur
// ^DATE   : 
//
// ^CLASS    : ContractMatInstrBankList
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

class IFASTCBO_LINKAGE ContractMatInstrBankList : public BankInstructionsExList
{
public:
   ContractMatInstrBankList(BFAbstractCBO &parent);

   virtual ~ContractMatInstrBankList();

protected:

   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, 
										const BFDataGroupId& idDataGroup);

   virtual SEVERITY doCreateObject ( const BFData &data, BFCBO *&pObjOut );

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractMatInstrBankList.hpp-arc  $
//
//   Rev 1.0   Mar 02 2012 16:12:06   wp040100
//Initial revision.
//
//
//
 */
