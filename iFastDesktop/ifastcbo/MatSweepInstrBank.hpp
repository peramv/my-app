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
// ^FILE      : MatSweepInstrBank.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : May, 2003
//
// ^CLASS     : MatSweepInstrBank
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


class IFASTCBO_LINKAGE MatSweepInstrBank : public BankInstructionsEx
{
public:
   MatSweepInstrBank (BFAbstractCBO &parent);
   virtual ~MatSweepInstrBank();
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstrBank.hpp-arc  $
//
//   Rev 1.0   Feb 01 2012 13:33:10   if991250
//Initial revision.
//
 */