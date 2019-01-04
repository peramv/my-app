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
// ^FILE      : BankInstructions4Trxn.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : October, 2003
//
// ^CLASS     : BankInstructions4Trxn
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "bankinstructions.hpp"

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE BankInstructions4Trxn : public BankInstructions
{
public:
   BankInstructions4Trxn(BFAbstractCBO &parent, const DString &transType, const DString &payType = I_("E"));
   virtual ~BankInstructions4Trxn();
   SEVERITY init (const BFData &data, const DString &dstrBankType);
protected:
   virtual SEVERITY postInit(const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInit(const BFDataGroupId &idDataGroup);
private:
   DString _transType;
   DString _payType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructions4Trxn.hpp-arc  $
//
//   Rev 1.2   Dec 29 2003 18:35:38   popescu
//PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
//
//   Rev 1.1   Oct 30 2003 17:26:50   FENGYONG
//Add paytype as a parameter
//
//   Rev 1.0   Oct 19 2003 19:08:32   popescu
//Initial revision.
//
 */