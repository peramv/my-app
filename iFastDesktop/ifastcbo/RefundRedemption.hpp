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
// ^FILE   : RefundRedemption.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RefundRedemption
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

class IFASTCBO_LINKAGE RefundRedemption : public Redemption
{
public:
	RefundRedemption (BFAbstractCBO &parent);
	virtual ~RefundRedemption();

protected:
	virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
	virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGrousp);
	virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
	virtual SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup );
   virtual SEVERITY validateMinFromFundAmount ( const DString &account,
                                                const DString &fundCode,
                                                const DString &classCode,
                                                const DString &amtType,
                                                const DString &amount,
                                                const DString &broker,
                                                const DString &branch,
                                                const DString &slsrep,
                                                const DString &depositType, 
                                                const BFDataGroupId &idDataGroup);
   //virtual SEVERITY initRefund (const BFData &data);
   //virtual SEVERITY postInitRefund ( const BFDataGroupId &idDataGroup);

private:
};
//******************************************************************************
/* $Log::  
*/