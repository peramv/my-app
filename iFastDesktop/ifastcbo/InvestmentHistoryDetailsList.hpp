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
// ^FILE   : InvestmentHistoryDetailsList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : InvestmentHistoryDetailsList
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

class InvestmentHistoryDetails;

class IFASTCBO_LINKAGE InvestmentHistoryDetailsList : public MFCanBFCbo, private boost::noncopyable
{
public:
	InvestmentHistoryDetailsList( BFAbstractCBO &parent );
	virtual ~InvestmentHistoryDetailsList();

	SEVERITY init (const DString& dstrInvHisLotId);
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryDetailsList.hpp-arc  $
//
//   Rev 1.2   Dec 01 2011 19:07:46   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.1   Nov 25 2011 13:54:44   wp040100
//P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
