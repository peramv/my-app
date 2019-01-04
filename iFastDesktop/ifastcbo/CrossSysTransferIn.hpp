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
// ^FILE   : Purchase.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Nov, 2014
//
// ^CLASS    :CrossSysTransferIn
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\Purchase.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class BankInstructions;
class AmsMstrInfo;

class IFASTCBO_LINKAGE CrossSysTransferIn : virtual public Purchase
{
public:
   CrossSysTransferIn (BFAbstractCBO &parent);
   virtual ~CrossSysTransferIn ();

   //(ED98,PW98) does not provide support for  allocations, fees, commissions

   virtual bool isSplitCommissionAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isROAApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isEUSDApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup) ;
   virtual bool areAllocationsAllowed (const BFDataGroupId &idDataGroup) ;
   virtual bool areTaxRatesAllowed (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setField ( const BFFieldId &idField, 
                               const DString &dstrValue,
                               const BFDataGroupId &idDataGroup, 
                               bool bFormatted = true, 
                               bool bSideEffect = false, 
                               bool bCheckCurrentValue = true);

   virtual void getField    ( const BFFieldId &idField, 
                              DString &fieldValue, 
                              const BFDataGroupId &idDataGroup, 
                              bool formattedReturn = false) const;

protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);   
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup );

   //(ED98,PW98) does not provide support for  allocations, fees, commissions
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual bool areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup) ;
   virtual bool isRESPTransferAllowed (const BFDataGroupId &idDataGroup);

   //set the default from tarde default and not apply purchase overrides
   virtual void setDefaultPayType ( const DString dstrAccountNum, DString &payType,
                                    const BFDataGroupId &idDataGroup) ;    
   virtual SEVERITY getDefaultFundClassPayType (const DString dstrAccountNum, 
                                                DString &payType,
                                                const DString dstrFundCode,
                                                const DString dstrClassCode,
                                                const BFDataGroupId &idDataGroup) ;

   //the value i set by the system.So just return without validation.
   virtual SEVERITY validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup);
   //only direct trades for the transaction type   
   virtual bool isWireSupported (const BFDataGroupId &idDataGroup);
   virtual bool isG1G2ApplicableTrade(const BFDataGroupId &idDataGroup);
   virtual bool isRDSPTransferAllowed (const BFDataGroupId &idDataGroup);

private:
   void commonInit(const BFDataGroupId &idDataGroup);
   void validateG1G2Entries(const BFDataGroupId &idDataGroup);
   void setG1G2ReadOnlyForFundClass(const BFDataGroupId &idDataGroup);
   void getFormattedG1G2Units ( const BFDataGroupId &idDataGroup, 
                                DString &value) const;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CrossSysTransferIn.hpp-arc  $
 
*/  