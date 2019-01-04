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
// ^FILE   : AcctCommitBankList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcctCommitBankList
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

class IFASTCBO_LINKAGE AcctCommitBankList : public BankInstructionsExList
{
public:
   // X-structors
   AcctCommitBankList(BFAbstractCBO &parent);
   virtual ~AcctCommitBankList();

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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCommitBankList.hpp-arc  $
//
//   Rev 1.0   Feb 27 2012 09:16:16   if991250
//Initial revision.
//
//
 */
