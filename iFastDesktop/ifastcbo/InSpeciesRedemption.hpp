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
// ^FILE   : InSpeciesRedemption.hpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// ^CLASS    : InSpeciesRedemption
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\Redemption.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE InSpeciesRedemption : public Redemption
{
public:
	InSpeciesRedemption (BFAbstractCBO &parent);
	virtual ~InSpeciesRedemption();

protected:
	virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
	virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGrousp);
	virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
	virtual SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup );

private:
};
//******************************************************************************
/* $Log::  
*/