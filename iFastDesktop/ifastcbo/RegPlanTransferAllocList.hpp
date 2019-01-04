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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RegPlanTransferAllocList.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS  : RegPlanTransferAllocList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RegPlanTransferAllocList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   RegPlanTransferAllocList( BFAbstractCBO &parent );
   virtual ~RegPlanTransferAllocList();
   // Initialization method
   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& strRegTransferMstrUUID, const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING );
   SEVERITY initNew( const BFDataGroupId& idDataGroup );

   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   SEVERITY initWithDefaultAllocations( const BFDataGroupId& idDataGroup, 
                                        const DString& dstrTransTypeIn, 
                                        const DString& dstrAcctNumIn, 
                                        const DString& dstrCurrency,
                                        const DString& dstrAmount,
                                        const DString& dstrEffectiveDate,
                                        bool bDummyAllocations = false );
   void getTotalAllocAmountPercent(const BFDataGroupId& idDataGroup, double &dTotalAmount, double &dTotalPercentage);
   void getTotalAllocAmountPercent(const BFDataGroupId& idDataGroup, BigDecimal &dTotalAmount, BigDecimal &dTotalPercentage);
   void getTotal (const BFFieldId& idField, DString &dstrTotal, const BFDataGroupId& idDataGroup);
   int getNbrOfAllocInList(const BFDataGroupId& idDataGroup);
   void setPercentTypeAlloc(const BFDataGroupId& idDataGroup, boolean isPercent);
   void ModelOffer(RegPlanTransferAllocList *Model, const BFDataGroupId& idDataGroup);
   void updateTotalAmount(const BFDataGroupId& idDataGroup, BigDecimal totalAmount);

protected:
   SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup);
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:
   DString dstrRegTransferMstrUUID;
   boolean isPercent;
};

