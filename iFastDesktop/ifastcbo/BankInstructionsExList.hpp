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
// ^FILE   : BankInstructionsExList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : BankInstructionsExList
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

class IFASTCBO_LINKAGE BankInstructionsExList : public BankInstructionsList
{
public:
   // X-structors
   BankInstructionsExList(BFAbstractCBO &parent,
      const DString &dstrBankType, const BFDataId &parentDataId, 
      const BFDataId &parentRepeatId);
   virtual ~BankInstructionsExList();

   // Initialize function
   SEVERITY initNew(const DString &dstrAccountNum,
      const BFDataGroupId& idDataGroup);
   SEVERITY init(const DString &dstrAccountNum,
      const BFDataGroupId& idDataGroup);
private:
   SEVERITY buildDataObject(const BFDataGroupId& idDataGroup);
   BFDataId _parentDataId;
   BFDataId _parentRepeatId;
   DString _dstrBankType;
   BFData *_pBFData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructionsExList.hpp-arc  $
//
//   Rev 1.0   Oct 04 2003 16:08:40   popescu
//Initial revision.
//
//   Rev 1.1   Jun 10 2003 16:10:50   popescu
//Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
//
//   Rev 1.0   Jun 03 2003 21:00:58   popescu
//Initial revision.
//
 */
