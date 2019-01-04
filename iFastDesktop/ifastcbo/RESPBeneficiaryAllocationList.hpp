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
// ^FILE   : RESPBeneficiaryAllocationList.hpp
// ^AUTHOR : 
// ^DATE   : February, 2010
//
// ^CLASS    : RESPBeneficiaryAllocationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class RESPBeneficiaryAllocation;

class IFASTCBO_LINKAGE RESPBeneficiaryAllocationList : public MFCanBFCbo, private boost::noncopyable
{
public:
	// X-structors
	RESPBeneficiaryAllocationList (BFAbstractCBO &parent);
	virtual ~RESPBeneficiaryAllocationList ();
	
	// Initialize function
	SEVERITY init ( const DString &accountNum,
                   const DString &transId,
                   const DString& tradeType = I_("Pend"),
				       bool bSetFieldsReadOnly = false,
				       const DString &dstrTrack = I_("N"),
				       const DString &dstrPageName = NULL_STRING);
	SEVERITY initNew ( const DString &accountNum, 
                      const BFDataGroupId& idDataGroup);
   SEVERITY add100PercentBeneAlloc (const BFDataGroupId &idDataGroup);
	SEVERITY checkDuplicate ( const RESPBeneficiaryAllocation *pRESPBeneficiaryAllocationToCheck, 
                             const BFDataGroupId &idDataGroup);
	SEVERITY getBeneficiaryMasterList (DString &beneficiaryList, const BFDataGroupId &idDataGroup);
	SEVERITY getRESPEntityInfo (const DString dstrEntityId, 
                               const BFDataGroupId &idDataGroup, 
							          DString& dstrRESPAllocPrcnt,
							          DString& dstrBenefDofBirth,
							          DString& dstrHRDCRelateCode,
							          DString& dstrTaxJuris,
							          DString& dstrEffectiveDate);

	SEVERITY getEntitySeqNumber ( const DString dstrEntityId, 
								         const BFDataGroupId &idDataGroup, 
							            DString& dstrSeqNumber);

	SEVERITY validateBeneficiaryEffectiveDate (const DString &dstrTradeDate, const BFDataGroupId &idDataGroup);
   void  getFormattedAmount (const BFDataGroupId &idDataGroup, 
                             DString &dstrValue);
   void formatAmtUsingCurrency (const BFDataGroupId& idDataGroup, 
                                DString &dstrValue);
   void getTotalAmount ( DString &strTotalAmount, 
                         const BFDataGroupId &idDataGroup, 
                         bool bFormatted = true);
   void getTotalPercentage (DString &strTotalPercentage, 
                            const BFDataGroupId& idDataGroup, 
                            bool bFormatted = true);
   void getOtherAllocTotalAmount(DString &strTotalAmount, 
                                 const BFDataGroupId& idDataGroup, 
                                 bool bFormatted = true, 
                                 RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = NULL);
   void getOtherAllocTotalPercentage(DString &strTotalPercentage, 
                                     const BFDataGroupId& idDataGroup, 
                                     bool bFormatted = true, 
                                     RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = NULL);
   //P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
   void getOtherBenefsField(const BFFieldId& fieldId,
							       DString &dstrValueOut, 
							       const BFDataGroupId &idDataGroup,
							       const RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = NULL) ;
protected:

	virtual SEVERITY doCreateObject (const BFData &data, BFCBO *&pObjOut);
	virtual SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey,  const BFDataGroupId &idDataGroup);
	virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
	
	SEVERITY validateTotalAmount (const BFDataGroupId &idDataGroup);
	SEVERITY validateNumberOfRESPAllocations (const BFDataGroupId &idDataGroup);
   void  getTotalValue ( const BFFieldId& fieldId, 
                         DString &strTotalValue, 
                         const BFDataGroupId& idDataGroup,
                         RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = NULL);
   SEVERITY validateHRDCPending (const BFDataGroupId& idDataGroup);
   
private:
   SEVERITY setAmount (const BFDataGroupId& idDataGroup);
   SEVERITY validateRESPInfoUpdate ( const BFDataGroupId &idDataGroup );
	bool _bSetFieldsReadOnly;
	DString m_MasterBeneficiaryList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log::   Y:/VCS/BF iFAST/ifastcbo/RESPBeneficiaryAllocationList.hpp-arc  $
//
//   Rev 1.8   Oct 13 2011 04:13:26   panatcha
//P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
//
//   Rev 1.7   Oct 29 2010 05:27:36   kitticha
//PET0165541 FN03 - QESI Phase3.
//
