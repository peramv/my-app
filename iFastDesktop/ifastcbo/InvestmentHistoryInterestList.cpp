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
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : InvestmentHistoryInterestList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "entity.hpp"
#include "mfaccount.hpp"
#include "InvestmentHistoryInterest.hpp"
#include "InvestmentHistoryInterestList.hpp"

#include <ifastdataimpl\dse_dstc0425_vw.hpp>
#include <ifastdataimpl\dse_dstc0425_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0425_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INVESTMENT_HISTORY_INT_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME	= I_( "InvestmentHistoryInterestList" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId IntInvestUUID;
}

namespace CND
{  
}

//******************************************************************************
InvestmentHistoryInterestList::InvestmentHistoryInterestList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0425_REQ)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	setObjectAsList( );
}

//******************************************************************************
InvestmentHistoryInterestList::~InvestmentHistoryInterestList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY InvestmentHistoryInterestList::init (const DString& dstrInvHisInvestId)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	DString mgmtCoIdOut;
	m_requestData.setElementValue( ifds::InvHisInvestId, dstrInvHisInvestId);
	m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	m_requestData.setElementValue( ifds::Track, I_("N") );
	
	ReceiveData (DSTC_REQUEST::INVESTMENT_HISTORY_INT_INQUIRY, 
				 m_requestData, 
				 ifds::DSTC0425_VW, 
				 DSTCRequestor (getSecurity(), false), 
				 false);

	return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY InvestmentHistoryInterestList::doCreateObject (const BFData& data, 
														BFCBO*& pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   	
	pObjOut = new InvestmentHistoryInterest(*this);
	((InvestmentHistoryInterest*)pObjOut)->init(const_cast<BFData&>(data) );

	return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY InvestmentHistoryInterestList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if (doMoreRecordsExist())
   {
      ReceiveData ( DSTC_REQUEST::INVESTMENT_HISTORY_INT_INQUIRY, 
                    m_requestData, 
                    ifds::DSTC0425_VW, 
                    DSTCRequestor(getSecurity(), false), 
                    false);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryInterestList.cpp-arc  $
// 
//    Rev 1.2   Dec 01 2011 19:07:22   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.1   Nov 25 2011 13:55:08   wp040100
// P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
