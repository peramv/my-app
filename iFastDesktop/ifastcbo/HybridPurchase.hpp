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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : HybridPurchase.hpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// ^CLASS    : HybridPurchase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\purchase.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE HybridPurchase : virtual public Purchase
{
public:

	HybridPurchase (BFAbstractCBO &parent);
	virtual ~HybridPurchase ();

protected:

	virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
	virtual SEVERITY doInit (const BFData &data);
	virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
	virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
	virtual SEVERITY doValidateField (const BFFieldId &idField, const DString &strValue, const BFDataGroupId &idDataGroup);

	virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);

	virtual SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup );
private:

};

//******************************************************************************
/* $Log::  
*/