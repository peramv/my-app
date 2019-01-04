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
// ^FILE   : FundBrokerFee.hpp
// ^AUTHOR : 
// ^DATE   : July 26, 2004
//
// ^CLASS    : FundBrokerFee
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

class IFASTCBO_LINKAGE FundBrokerFee : public FeeParamBase
{
public:
   FundBrokerFee( BFAbstractCBO &parent );
   virtual ~FundBrokerFee();

   SEVERITY Init(const BFData& data, bool bDefault = false);

   virtual SEVERITY InitNew( const BFDataGroupId& idDataGroup );  
   
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY setDefFeeParam(  const BFDataGroupId& idDataGroup );   
   SEVERITY validateRate( const BFDataGroupId& idDataGroup );	

   virtual SEVERITY getFeeScaleList( FeeScaleBaseList* &pFeeScaleList, const BFDataGroupId& idDataGroup,bool bInquire = true, bool bDefault = false, bool bRemObj = false, bool bDelete = false);

protected:
	virtual SEVERITY doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup );
	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   virtual void doFeeCodeRelatedChanges( const BFDataGroupId& idDataGroup );   

private:
	
	SEVERITY validateFeeOverlap(const BFDataGroupId& idDataGroup);
};