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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : InvestmentHistoryList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : InvestmentHistoryList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class InvestmentHistory;

class IFASTCBO_LINKAGE InvestmentHistoryList : public MFCanBFCbo, private boost::noncopyable
{
public:
   InvestmentHistoryList( BFAbstractCBO &parent );
   virtual ~InvestmentHistoryList();

	SEVERITY init (	const DString& dstrAccountNum, 
					const DString& dstrTransId, 
					const DString& dstrFund,
					const DString& dstrClass,
					const DString& dstrInvNum,
					const DString& dstrInvStatus,
					const DString& dstrSearchBy,
					const BFDataGroupId& idDataGroup);
	SEVERITY init (const BFDataGroupId& idDataGroup);
	SEVERITY getMore();

	bool isAnyStatusBlank (const BFDataGroupId &idDataGroup);

	SEVERITY setDummyFlag (const BFDataGroupId &idDataGroup);

protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
    SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
											 const BFDataGroupId &idDataGroup);
	SEVERITY doValidateField ( const BFFieldId &idField, 
							   const DString &strValue, 
							   const BFDataGroupId &idDataGroup);

private:
	BFData m_requestData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryList.hpp-arc  $
//
//   Rev 1.2   Nov 25 2011 17:41:06   wp040100
//P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
