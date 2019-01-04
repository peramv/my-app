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
// ^FILE   : FundSponsorFee.hpp
// ^AUTHOR : 
// ^DATE   : July 26, 2004
//
// ^CLASS    : FundSponsorFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include "FeeParamSys.hpp"


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FundClassRules;
class FeeScaleSysList;

class IFASTCBO_LINKAGE FundSponsorFee : public FeeParamBase
{
public:
   FundSponsorFee( BFAbstractCBO &parent );
   virtual ~FundSponsorFee();

   SEVERITY Init(const BFData& data, bool bDefault = false);

   virtual SEVERITY InitNew( const BFDataGroupId& idDataGroup );
  
   virtual SEVERITY getFeeScaleList( FeeScaleBaseList* &pFeeScaleList, const BFDataGroupId& idDataGroup,bool bInquire = true, bool bDefault = false, bool bRemObj = false, bool bDelete = false);
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY setDefFeeParam(  const BFDataGroupId& idDataGroup );   
   SEVERITY validateRate( const BFDataGroupId& idDataGroup,const DString& dstrRate  );
   SEVERITY validateRateMinMax( const BFDataGroupId& idDataGroup );
	void stampCurBusinessDateToStopDate( const BFDataGroupId& idDataGroup );

protected:
	virtual SEVERITY doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup );
	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   virtual void doFeeCodeRelatedChanges( const BFDataGroupId& idDataGroup );
   SEVERITY validateFeeCode( const BFDataGroupId& idDataGroup );
	SEVERITY getFeeParamConfigDefaults( DString dstrFeeCode, const BFDataGroupId& idDataGroup, bool setDefaultParam = false );

private:
	
	SEVERITY validateFeeOverlap(const BFDataGroupId& idDataGroup);

   FeeScaleBaseList *pFeeScaleList_;

};