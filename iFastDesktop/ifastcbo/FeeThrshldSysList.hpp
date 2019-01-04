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
// ^FILE   : FeeThrshldSysList.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// ^CLASS    : FeeThrshldSysList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\FeeScaleBaseList.hpp>
#include <boost\utility.hpp>

// Forward references
class FeeScaleSys;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeThrshldSysList : public MFCanBFCbo, private boost::noncopyable //FeeScaleBaseList
{
public:

   // X-structors
   FeeThrshldSysList( BFAbstractCBO &parent );
   virtual ~FeeThrshldSysList();
   // Initialize function
   SEVERITY init( const DString& AcctFeeParamId,bool bDefault = false, const DString& dstrTrack = I_("N"),
                             const DString& dstrPageName = NULL_STRING );
   SEVERITY initNew(const BFDataGroupId& idDataGroup);
   SEVERITY AddNewFeeScale( FeeScaleBaseList* pFeeScaleList, const DString& strKey, const BFDataGroupId& idDataGroup );
   SEVERITY clone(const BFDataGroupId& idDataGroup, FeeThrshldSysList*& pFeeThrshldSysList);

protected:
	virtual void  getStrKey( DString &strKey, const BFData *data  );
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

private:
	bool bDefault_;
};

