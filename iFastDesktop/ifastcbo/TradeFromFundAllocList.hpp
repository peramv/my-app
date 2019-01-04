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
// ^FILE   : TradeFromFundAllocList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2003
//
// ^CLASS    : TradeFromFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "fundalloclist.hpp"
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeFromFundAllocList : public FundAllocList
{
public:
   // X-structors
   TradeFromFundAllocList( BFAbstractCBO &parent );
   virtual ~TradeFromFundAllocList();

   // Initialize function
   virtual SEVERITY initExisting(const DString& dstrTrack = I_("N"),
      const DString& dstrPageName = NULL_STRING);
   virtual SEVERITY initNew(const BFDataGroupId &idDataGroup, 
      const DString& dstrTrack = I_("N"),
      const DString& dstrPageName = NULL_STRING);
   virtual SEVERITY addNewAllocation(const DString& strKey, 
      const BFDataGroupId& idDataGroup, bool bGetDefault,
      bool bCopyParent, bool bAddChildren);
   SEVERITY getEstimatedTotalAmount(DString &totalEstimatedAmount, 
      const BFDataGroupId &idDataGroup, 
      bool bFormatted, 
      const DString &skipKey = NULL_STRING);
protected:
   virtual SEVERITY doApplyRelatedChanges(const BFFieldId& idField, 
      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, 
      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateAll(const BFDataGroupId& idDataGroup, 
      long lValidateGroup);
   void getFormattedAmount (const BFDataGroupId &idDataGroup, 
      DString &dstrValue);
   virtual SEVERITY doDeleteObject (const DString &strKey, 
      const BFDataGroupId &idDataGroup, bool bIsObjectDestroyed);
private:
   SEVERITY setAllowFullTransfer(const BFDataGroupId& idDataGroup);
   SEVERITY commonInit(const BFDataGroupId& idDataGroup);
   void clearAllocCondition (Frame *pFrame, int conditionCode);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeFromFundAllocList.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:57:54   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Jan 05 2004 16:33:00   popescu
//PTS 10025748, in case of a 'Full Transfer' of the From Side Multi Fund Allocation, set the amount of transaction to the To side. Before it was wrongly set to zero.
//
//   Rev 1.3   Oct 28 2003 12:40:14   popescu
//PTS 10023292, display issues of decimal fields
//
//   Rev 1.2   Sep 01 2003 21:32:42   popescu
//PET 809, FN 02 CIBC Multi Fund Transfer
//
//   Rev 1.1   Aug 15 2003 11:31:48   popescu
//fixed comp error
//
//   Rev 1.0   Aug 13 2003 20:12:44   popescu
//Initial revision.
 */
