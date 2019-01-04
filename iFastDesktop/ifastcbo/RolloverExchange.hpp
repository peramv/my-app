#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : RolloverExchange.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Nov 2013
// ^CLASS  : RolloverExchange
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Used for the rollover exchnage trade object creation
//	Remark:The rolllover exchanges doesnot support any allocations and FeeSetup
//         based for inital version.Enhnacement is needed to support these
//         functionalities.
//******************************************************************************
#include <ifastcbo\Exchange.hpp>
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif 

//Forward declarations   
class IFASTCBO_LINKAGE RolloverExchange : public Exchange
{
public:
   RolloverExchange (BFAbstractCBO &parent);
   virtual ~RolloverExchange();        

protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGrousp);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void commonInit(const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup); 

   //validation methods
   virtual SEVERITY validateFundClass ( const DString &dstrFundCode, 
                                        const DString &dstrClassCode, 
                                        const DString &dstrAccountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmountAmtType (const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateOrderType ( const DString &orderType, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountTrade( MFAccount *pMFAccount, const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountToTrade(MFAccount *pMFAccountTo, const BFDataGroupId &idDataGroup);
   bool skipAccountLevelStopFlags(const DString& dstrTransType,
								  const DString& dstrFundCode,
								  const DString& dstrClassCode,
								  const DString& dstrAccountNum,
								  const BFDataGroupId &idDataGroup);
   virtual bool isWireSupported (const BFDataGroupId &idDataGroup){ return false; }
   virtual SEVERITY setDefaultOrderType (const BFDataGroupId &idDataGroup);
   //No allocation supported for Rollover Exchanges
   virtual bool areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup){ return false;}
   virtual bool isRESPTransferAllowed (const BFDataGroupId &idDataGroup){ return false;}
   virtual bool areAllocationsAllowed (const BFDataGroupId &idDataGroup){ return false; }
   virtual bool isSplitCommissionAllowed (const BFDataGroupId &idDataGroup){ return false; }
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup){ return false; }
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup){ return false; }
   virtual bool isSettleLocAllowed (const BFDataGroupId &idDataGroup){ return false; }
   virtual bool areMultipleSettleLocAllowed (const BFDataGroupId &idDataGroup){ return false; }
   virtual SEVERITY validateFromToFundClass ( const DString &fromFund, const DString &fromClass,
											  const DString &toFund, const DString &toClass,
											  const BFDataGroupId &idDataGroup);
   bool accountHasTradeAfterTradeDate(const BFDataGroupId &idDataGroup);

private:
   void setDepositAndRedemptionCode(const BFDataGroupId &idDataGroup);
   virtual SEVERITY amtTypeExtraRelatedChanges (const BFDataGroupId &idDataGroup);           
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Exchange.hpp-arc  $
*/