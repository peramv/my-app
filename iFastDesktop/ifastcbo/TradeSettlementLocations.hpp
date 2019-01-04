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
// ^FILE   : TradeSettlementLocations.hpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// ^CLASS    : TradeSettlementLocations
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeSettlementLocations : public MFCanBFCbo, private boost::noncopyable
{
public:
	
	TradeSettlementLocations (BFAbstractCBO &parent);
	virtual ~TradeSettlementLocations();
	
	SEVERITY init (const BFData& data,
				   const BFDataGroupId& idDataGroup = BF::HOST,
				   bool bSetFieldsReadOnly = false);
	SEVERITY initNew (const BFDataGroupId& idDataGroup,
		              bool bSetFieldsReadOnly = false);
	SEVERITY setSettleLocAmountInvalid (const BFDataGroupId& idDataGroup);


protected:
	
	virtual void doInitWithDefaultValues (const BFDataGroupId& idDataGroup);
	virtual SEVERITY doValidateField (const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
	virtual SEVERITY doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup);

private:
	
	SEVERITY commonInit (bool bSetFieldsReadOnly, const BFDataGroupId& idDataGroup);					
};


/* $Log::   
*/
