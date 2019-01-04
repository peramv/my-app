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
//
//******************************************************************************
//
// ^FILE   : RESPBeneficiaryAllocation.hpp
// ^AUTHOR : 
// ^DATE   : February, 2010
//
// ^CLASS    : RESPBeneficiaryAllocation
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

class RESPBeneficiaryValidation;

class IFASTCBO_LINKAGE RESPBeneficiaryAllocation : public MFCanBFCbo, private boost::noncopyable
{
public:
   friend class RESPBeneficiaryAllocationList;
	
	RESPBeneficiaryAllocation (BFAbstractCBO &parent);
	virtual ~RESPBeneficiaryAllocation();
	
	SEVERITY init (const BFData& data, bool bSetFieldsReadOnly = false);
	SEVERITY initNew (const BFDataGroupId& idDataGroup, bool bSetFieldsReadOnly = false);
	SEVERITY setBeneficiaryAmountInvalid (const BFDataGroupId& idDataGroup);
   SEVERITY getBeneficiaryValidation ( RESPBeneficiaryValidation *&pRESPBeneficiaryValidation,
                                       const BFDataGroupId &idDataGroup);

protected:	
	virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);
	virtual SEVERITY doValidateField (const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
	virtual SEVERITY doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
	virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);	
   virtual void getField( const BFFieldId& idField, 
                          DString & strValue, 
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn = false ) const;
	SEVERITY validateBeneficiary (const DString &dstrBenefId, const BFDataGroupId &idDataGroup);
	SEVERITY validateBeneficiary (const BFDataGroupId &idDataGroup);
	SEVERITY validateIfGrantExists (const BFDataGroupId &idDataGroup);
    
private:

   SEVERITY setPercentage ( const BFDataGroupId& idDataGroup );
   SEVERITY setAmount ( const BFDataGroupId& idDataGroup );	
   SEVERITY validatePercentage(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateAmount(const DString& strAmount, const BFDataGroupId& idDataGroup);
	SEVERITY commonInit (bool bSetFieldsReadOnly, const BFDataGroupId& idDataGroup);
	bool	m_bChoosingBenef,
      m_bSettingAmountField,
      m_bSettingPercentField;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPBeneficiaryAllocation.hpp-arc  $
//
//   Rev 1.7   Apr 09 2010 14:44:22   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog - fixed refresh issue when updating allocations
//
//   Rev 1.6   Mar 30 2010 18:59:58   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.5   Mar 30 2010 16:32:52   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.4   Mar 29 2010 22:59:36   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
 */