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
// ^FILE   : TradeSettlementLocationsList.hpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// ^CLASS    : TradeSettlementLocationsList
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

class TradeSettlementLocations;

class IFASTCBO_LINKAGE TradeSettlementLocationsList : public MFCanBFCbo, private boost::noncopyable
{
public:
	// X-structors
	TradeSettlementLocationsList (BFAbstractCBO &parent);
	virtual ~TradeSettlementLocationsList ();
	
	// Initialize function
	SEVERITY init (const DString &transNum,
		           const BFDataGroupId &idDataGroup, 
				   bool bSetFieldsReadOnly = false,
				   const DString &dstrTrack = I_("N"),
				   const DString &dstrPageName = NULL_STRING);

	SEVERITY initNew (const BFDataGroupId& idDataGroup);

	SEVERITY checkDuplicate ( const TradeSettlementLocations *pTradeSettlementLocationToCheck, const BFDataGroupId &idDataGroup);
	SEVERITY getMasterList (DString &settleLocList, const BFDataGroupId &idDataGroup);

	double getTotalAmount ()
	{
		return m_TotalAmount;
	}
	
protected:

	virtual SEVERITY doCreateObject (const BFData &data, BFCBO *&pObjOut);
	virtual SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey,  const BFDataGroupId &idDataGroup);
	virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);

private:

	BFDataGroupId	_idDataGroup;
	bool			_bSetFieldsReadOnly;
	double			m_TotalAmount;
	DString			m_TradeAmount;
	DString			m_TransId;
	DString			m_MasterSettleLocsList;
};

/* $Log::  
*/
