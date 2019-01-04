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
// ^FILE      : TradeFromFundAlloc.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : June 2003
//
// ^CLASS     : TradeFromFundAlloc
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\fundalloc.hpp>
///#endif

class SplitCommissionList;
class MFAccountHoldingList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeFromFundAlloc : public FundAlloc
{
public:
   TradeFromFundAlloc (BFAbstractCBO &parent);
   virtual ~TradeFromFundAlloc();

   virtual SEVERITY initNew(const BFDataGroupId& idDataGroup,
                    const DString& dstrTrack = I_("N"),
                    const DString& dstrPageName = NULL_STRING );
   virtual SEVERITY initExisting(const BFData &data);
   virtual SEVERITY getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, 
                                             const BFDataGroupId& idDataGroup, 
                                             bool bCreate = true, 
                                             bool bGetDefault = false 
                                           )
   {
      pSplitCommissionList = NULL;
      return NO_CONDITION;
   }
	virtual bool isSegFundValidationReq() 
   {
      return false;
   }
   SEVERITY copyDataFromParent(const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doValidateField(const BFFieldId& idField, 
      const DString& strValue, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges(const BFFieldId& idField, 
      const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);
private:
   SEVERITY calculateEstimatedAllocAmount(const BFDataGroupId &idDataGroup);
   SEVERITY commonInit(const BFDataGroupId& idDataGroup);
   SEVERITY getNumberOfUnits(double &dAvalUnits, 
      const BFDataGroupId& idDataGroup);
   SEVERITY getNumberOfUnits (DString &dstrAvalUnits, 
      const BFDataGroupId& idDataGroup);
   SEVERITY getBalance(double &dBalance, 
      const BFDataGroupId& idDataGroup);
   SEVERITY getBalance(DString &dstrBalance, 
      const BFDataGroupId& idDataGroup);
   SEVERITY getHoldings(MFAccountHoldingList *&pHoldingsList, 
      const BFDataGroupId& idDataGroup);
   SEVERITY getFundNAV (double &dFundNAV, const BFDataGroupId& idDataGroup);
   SEVERITY fullTransferChanges(const BFDataGroupId& idDataGroup);
   void clearAllocCondition (Frame *pFrame, int conditionCode);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeFromFundAlloc.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:57:52   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Nov 06 2004 00:43:10   popescu
//PET 1117/06, synch changes
//
//   Rev 1.3   Sep 12 2003 10:44:22   popescu
//PET809, FN02 CIBC multi fund transfer
//Moved the cross objects validation between FromFundList and ToFundList from the process layer to the CBO layer, and since the Trade object owns both lists, the most logical place to put the validation seemed to be doValidateAll method of the Trade object
//
//   Rev 1.2   Sep 05 2003 18:29:30   popescu
//PET809_FN02, fixex
//
//   Rev 1.1   Sep 01 2003 21:32:40   popescu
//PET 809, FN 02 CIBC Multi Fund Transfer
//
//   Rev 1.0   Aug 13 2003 20:12:40   popescu
//Initial revision.
//
 */