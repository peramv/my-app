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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : AcctCommitBank.hpp
// ^AUTHOR    : 
// ^DATE      : 
//
// ^CLASS     : AcctCommitBank
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\bankinstructionsex.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE AcctCommitBank : public BankInstructionsEx
{
public:
   AcctCommitBank (BFAbstractCBO &parent);
   virtual ~AcctCommitBank();
protected:
   virtual SEVERITY doApplyRelatedChanges (
                              const BFFieldId& idField, 
                              const BFDataGroupId& idDataGroup);
   virtual SEVERITY postInit (
                              const BFDataGroupId& idDataGroup);
   virtual SEVERITY doInitBeforeCloning (
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentCurrency (
                              DString &currency,
                              DString &description,
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentProcessDate ( DString &processDate, 
                                           const BFDataGroupId &idDataGroup);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCommitBank.hpp-arc  $
//
//   Rev 1.0   Feb 27 2012 09:15:50   if991250
//Initial revision.
//
//
 */