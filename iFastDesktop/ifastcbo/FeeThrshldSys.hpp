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
// ^FILE   : FeeThrshldSys.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FeeThrshldSys
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\FeeScaleBase.hpp>
#include <boost\utility.hpp>
class BFData;
class FeeScaleBaseList;


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeThrshldSys : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeThrshldSys( BFAbstractCBO &parent );
   virtual ~FeeThrshldSys();
   SEVERITY init( const BFData& InstData, bool bDefault = false);
   SEVERITY init(const BFDataGroupId& idDataGroup ); // init new
   SEVERITY setValueFromDefault( BFCBO* pCBO, const BFDataGroupId& idDataGroup );
   bool isTheSameBusinessDate(const BFDataGroupId& idDataGroup);
   bool isThresholdReadOnly(const BFDataGroupId& idDataGroup);
   SEVERITY getFeeScaleSysList(FeeScaleBaseList*& pFeeScaleSysList, const BFDataGroupId& idDataGroup, bool createNew = true);
   SEVERITY clone(const BFDataGroupId& idDataGroup, FeeThrshldSys*& pFeeThrshldSysClone);

protected: 
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY validateScaleRate( const BFDataGroupId& idDataGroup ); 

   
private:
   BFData* localData;

};
