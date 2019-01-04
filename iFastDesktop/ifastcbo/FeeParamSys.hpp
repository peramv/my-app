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
// ^FILE   : FeeParamSys.hpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 10, 2002
//
// ^CLASS    : FeeParamSys
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include "FeeScaleBaseList.hpp"
#include "FeeParamBase.hpp"


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FundClassRules;
class FeeScaleSysList;
class FeeThrshldSysList;

class IFASTCBO_LINKAGE FeeParamSys : public FeeParamBase
{
public:
   FeeParamSys( BFAbstractCBO &parent );
   virtual ~FeeParamSys();

   SEVERITY Init(const BFData& data, bool bDefault = false);

   virtual SEVERITY InitNew( const BFDataGroupId& idDataGroup ); //for creating new object
  
   virtual SEVERITY getFeeScaleList( FeeScaleBaseList* &pFeeScaleList, const BFDataGroupId& idDataGroup,bool bInquire = true, bool bDefault = false, bool bRemObj = false, bool bDelete = false );
   virtual SEVERITY getFeeThresholdList( FeeThrshldSysList* &pFeeThrshldSysList, const BFDataGroupId& idDataGroup);
   void getDefaultBranchCode( DString &dstrBranchCode, const BFDataGroupId& idDataGroup );
   void clearUpdateFlags(const BFDataGroupId& idDataGroup);
	SEVERITY getFeeParamSysDef( FeeParamSys *&pFeeParamSys, const BFDataGroupId& idDataGroup );
	SEVERITY copyData(FeeParamSys *&pFeeParamSys, const BFDataGroupId& idDataGroup );
	bool isDIFFund ( const DString& fundCode);

protected:
	virtual SEVERITY doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup );
      virtual void setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly); 
      virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
      virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
      virtual void doFeeCodeRelatedChanges( const BFDataGroupId& idDataGroup );
      virtual void doCommGroupRelatedChanges( const BFDataGroupId& idDataGroup );
      void doFundClassRelatedChanges( const BFDataGroupId& idDataGroup );
      virtual SEVERITY validateScaleRate( const BFDataGroupId& idDataGroup );
      virtual SEVERITY validateFeeCode (const DString &dstrFeeCode, const BFDataGroupId& idDataGroup);
      SEVERITY validateFeeModelFundGroup(const BFDataGroupId& idDataGroup);
      SEVERITY validateFeeModelFundGroupOrFund(const BFDataGroupId& idDataGroup);
      void doFeeModelCodeRelatedChanges(const BFDataGroupId& idDataGroup, bool updateFeeCode = true);

private:
	void setCurrencyFromFundClassFields ( const BFDataGroupId& idDataGroup );
	void setScaleFromBasedOnField ( const BFDataGroupId& idDataGroup );
	void setFeeCodeSubstituteList(const BFDataGroupId& idDataGroup);
  void overrideDealerServiceFeeDescription(const BFDataGroupId &idDataGroup);
	
	SEVERITY validateFeeOverlap(const BFDataGroupId& idDataGroup);
	SEVERITY setupFeeCodeRelatedFields(const BFDataGroupId& idDataGroup, bool bIsSameDate);
	SEVERITY validateFamilyCode( const BFDataGroupId& idDataGroup );
	SEVERITY validateBranchCode( const BFDataGroupId& idDataGroup);
	SEVERITY validateSalesRepCode( const BFDataGroupId& idDataGroup);
	SEVERITY validateBrokerCode( const BFDataGroupId& idDataGroup);
	SEVERITY validateBasedOn (const BFDataGroupId& idDataGroup);

	void doBrokerCodeRelatedChanges(const BFDataGroupId& idDataGroup);
	void doBranchCodeRelatedChanges(const BFDataGroupId& idDataGroup);
	void doSlsRepRelatedChanges(const BFDataGroupId& idDataGroup);
	void doFamilyCodeRelatedChanges(const BFDataGroupId& idDataGroup);
	bool slsRepByBranch ( const BFDataGroupId& idDataGroup );
	void setValueFromDefaultRecord(
									const DString strFeeCode, 
									const DString strFundCode, 
									const DString strClassCode, 
									const DString strFundGroup, 
									const BFDataGroupId& idDataGroup
								  );
	SEVERITY validateFeeTypeForBasedOn (const BFDataGroupId& idDataGroup );

    FundClassRules m_FundClassRules;
    DString _salesRepByBranch;
	DString _familyName;
	DString _slsrepName;
	DString _branchName;
	DString _branchCode;
	DString _dstrFeeType;
	DString _dstrMinRate;
	DString _dstrMaxRate;
	DString _dstrTresholdAmtApply;
   FeeScaleBaseList *pFeeScaleList_;

};