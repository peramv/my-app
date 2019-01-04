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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : EstateAllocationList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : EstateAllocationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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

class EstateAllocation;

class IFASTCBO_LINKAGE EstateAllocationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   EstateAllocationList( BFAbstractCBO &parent );
   virtual ~EstateAllocationList();

	SEVERITY init (const DString& dstrAccountNum, 
					   const DString& dstrTransId, 
                  const DString& dstrAmount,
                  const DString& dstrAmountType,
                  const DString& dstrFund,
					   const DString& dstrClass,
                  const DString& dstrTradeDate,
					   const BFDataGroupId& idDataGroup,
                  bool  bReadOnly = false);

   SEVERITY init (const BFDataGroupId& idDataGroup);
   SEVERITY recalculateAmounts(const DString& dstrAmount, const DString& dstrAmountType, 
                               const BFDataGroupId& idDataGroup);
   SEVERITY getBenefAmount(const BFDataGroupId& idDataGroup, BigDecimal& bdTotalBenefAmount);
   SEVERITY getBenefAmount(const BFDataGroupId& idDataGroup, DString& dstrTotalBenefAmount);
  
protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
    SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
											 const BFDataGroupId &idDataGroup);
	SEVERITY doValidateField ( const BFFieldId &idField, 
							   const DString &strValue, 
							   const BFDataGroupId &idDataGroup);

private:
	BFData  m_requestData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EstateAllocationList.hpp-arc  $
//
//   Rev 1.1   10 Aug 2012 13:07:16   if991250
//Estate Allocation
//
//   Rev 1.0   25 Jul 2012 15:26:26   if991250
//Initial revision.
// 
*/
