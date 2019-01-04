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
// ^FILE   : InvestmentHistoryInterestList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : InvestmentHistoryInterestList
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

class InvestmentHistoryInterest;

class IFASTCBO_LINKAGE InvestmentHistoryInterestList : public MFCanBFCbo, private boost::noncopyable
{
public:
	InvestmentHistoryInterestList( BFAbstractCBO &parent );
	virtual ~InvestmentHistoryInterestList();

	SEVERITY init (const DString& dstrInvHisInvestId);
   SEVERITY getMore();
protected:
	SEVERITY doCreateObject (const BFData& data, BFCBO*& pObjOut);

private:
	BFData m_requestData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryInterestList.hpp-arc  $
//
//   Rev 1.2   Dec 01 2011 19:07:08   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.1   Nov 25 2011 13:55:16   wp040100
//P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
