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
// ^FILE   : FeeModel.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FeeModel
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FeeModelCopyToGroupList;

class IFASTCBO_LINKAGE FeeModel : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeModel( BFAbstractCBO &parent );
   virtual ~FeeModel();

   SEVERITY Init(const BFData& data);

   virtual SEVERITY InitNew( const BFDataGroupId& idDataGroup ); //for creating new object
   SEVERITY InitNew(const BFData& data,const BFDataGroupId& idDataGroup); // for cloned object
   void setFromHoldingCompany(const DString& dstrHoldingCompCode, const BFDataGroupId& idDataGroup);
   SEVERITY getFeeModelSetup(const BFDataGroupId& idDataGroup, BFAbstractCBO*& pFeeModelSetup);
   SEVERITY getFeeModelCopyToGroupList(FeeModelCopyToGroupList *&pFeeModelCopyToGroupList,
                                       const DString feeModel,
                                       const BFDataGroupId& idDataGroup,
                                       bool bCreated);
   SEVERITY removeFeeModelCopyToGroupList(const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup );
   virtual void setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly); 
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY validateOverlap( const BFDataGroupId& idDataGroup );
   SEVERITY validateEffectiveStopDate( const BFDataGroupId& idDataGroup);
   SEVERITY FeeModelTypeRelatedChanges(const BFDataGroupId& idDataGroup);
   SEVERITY UpdateFeeModelFundGroupSubst(const BFDataGroupId& idDataGroup);
   SEVERITY UpdateHoldingCompRelated(const DString& dstrHoldingCompCode, const BFDataGroupId& idDataGroup);
   SEVERITY validateHoldingCompCode( const BFDataGroupId& idDataGroup );
   SEVERITY validateHoldingCompCodeMandatory( const BFDataGroupId& idDataGroup );
   SEVERITY validateFeeModelCode(const BFDataGroupId& idDataGroup);
   void resetSubstBasedOnFeeModelType(const BFFieldId& idField, const DString& dstrSubstValues, 
                                      const BFDataGroupId& idDataGroup, bool showAll = false);
   void setCBOFieldsReadOnly(const BFDataGroupId& idDataGroup);

private:
   DString orgDEFF;
   DString m_dstrFromHoldingComp;
   bool _bIsCloned;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeModel.hpp-arc  $
// 
