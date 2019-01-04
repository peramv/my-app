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
// ^FILE   : RegPlanTransferAlloc.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS    : RegPlanTransferAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class SplitCommissionList;
class Systematic;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RegPlanTransferAlloc : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: remove public default constructor if using repository
   RegPlanTransferAlloc( BFAbstractCBO &parent );
   virtual ~RegPlanTransferAlloc();
   SEVERITY init();
   SEVERITY init(const BFData &viewData);
   void getField( const BFFieldId& idField, DString& strFieldValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   SEVERITY setField( const BFFieldId& idField, const DString& dstrValue, const BFDataGroupId& idDataGroup, bool bFormatted = true, bool bSideEffect = false, bool  bCheckCurrentValue = true );
   SEVERITY doValidateField(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField,const BFDataGroupId& idDataGroup );                                      
   void setPercentTypeAlloc(const BFDataGroupId& idDataGroup, boolean isPercent);
   void ModelOffer(RegPlanTransferAlloc* Model, const BFDataGroupId& idDataGroup);

private:
   void validateAmount(const DString& Amount, const BFDataGroupId& idDataGroup );
   void validatePercentage( const DString& strValue, const BFDataGroupId& idDataGroup ) const;
   void validateFundClass(const BFDataGroupId& idDataGroup );
   void setFundClassCode( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   void setFundNumber( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   SEVERITY validateFundCode( const DString& dstrfundCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateClassCode( const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateAllocCurrency( const BFDataGroupId& idDataGroup );
   SEVERITY validateFundClassAccNumDate ( const BFDataGroupId& idDataGroup );
};
