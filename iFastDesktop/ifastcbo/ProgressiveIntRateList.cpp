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
// ^FILE   : ProgressiveIntRateList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "progressiveintratelist.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0423_vw.hpp>
#include <ifastdataimpl\dse_dstc0423_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0423_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PROGRESSIVE_INT_RATE_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME   = I_( "ProgressiveIntRateList" );
}

namespace ifds
{

}

namespace CND
{  
   extern const long ERR_INVALID_FUND_CLASS_CODES;
}

//******************************************************************************
ProgressiveIntRateList::ProgressiveIntRateList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0423_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList ();
}

//******************************************************************************
ProgressiveIntRateList::~ProgressiveIntRateList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY ProgressiveIntRateList::init (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProgressiveIntRateList::init( const DString& dstrAccountNum, 
                                       const DString& dstrIntInvestId, 
                                       const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut, dstrInquire;
   dstrInquire = I_("INQUIRE");

   m_requestData.setElementValue( ifds::InputAcctNum, dstrAccountNum);
   m_requestData.setElementValue( ifds::InvHisInvestId, dstrIntInvestId);
   m_requestData.setElementValue( ifds::Inquiry, dstrInquire);
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_requestData.setElementValue( ifds::Track, I_("N") );

   ReceiveData (DSTC_REQUEST::PROGRESSIVE_INT_RATE_INQUIRY, m_requestData,
      ifds::DSTC0423_VW, DSTCRequestor(getSecurity(), true, true), false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProgressiveIntRateList::initForTrade( const DString& dstrAccountNum, 
                                               const DString& dstrFund,
                                               const DString& dstrClass,
                                               const DString& dstrInquiry,
                                               const DString& dstrInvHisInvestId, 
                                               const DString& dstrInvHisIntRateType, 
                                               const DString& dstrIInvHisIntCalcMthd, 
                                               const DString& dstrInvHisTerm, 
                                               const DString& dstrInvHisIntDate, 
                                               const DString& dstrInvHisTradeAmt, 
                                               const DString& dstrInvHisAddlAmt,
											              const DString& dstrCommRedRate,
                                               const DString& dstrForcedRate,
                                               const DString& dstrForcedRateAmt)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;

   m_requestData.setElementValue( ifds::InputAcctNum, dstrAccountNum);
   m_requestData.setElementValue( ifds::InvestmentHistoryFund, dstrFund);
   m_requestData.setElementValue( ifds::InvestmentHistoryClass, dstrClass);
   m_requestData.setElementValue( ifds::InvHisInvestId, dstrInvHisInvestId);
   m_requestData.setElementValue( ifds::Inquiry, dstrInquiry);
   m_requestData.setElementValue( ifds::InvHisIntRateType, dstrInvHisIntRateType);
   m_requestData.setElementValue( ifds::InvHisIntCalcMthd, dstrIInvHisIntCalcMthd);
   m_requestData.setElementValue( ifds::InvHisTerm, dstrInvHisTerm);
   m_requestData.setElementValue( ifds::InvHisIntDate, dstrInvHisIntDate);
   m_requestData.setElementValue( ifds::InvHisTradeAmt, dstrInvHisTradeAmt);
   m_requestData.setElementValue( ifds::InvHisAddlAmt, dstrInvHisAddlAmt);
   m_requestData.setElementValue( ifds::ForcedRate, dstrForcedRate);
   m_requestData.setElementValue( ifds::ForcedRateAmt, dstrForcedRateAmt);
   m_requestData.setElementValue( ifds::CommRedRate, dstrCommRedRate);
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_requestData.setElementValue( ifds::Track, I_("N") );

   ReceiveData (DSTC_REQUEST::PROGRESSIVE_INT_RATE_INQUIRY, m_requestData,
      ifds::DSTC0423_VW, DSTCRequestor(getSecurity(), true), false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ProgressiveIntRateList.cpp-arc  $
// 
//    Rev 1.6   Feb 23 2012 08:54:22   jankovii
// IN 2817781- P0186477FN03- Commission Reduction on GI Trading
// 
//    Rev 1.5   Jan 13 2012 10:48:06   wp040100
// P0186477/FN03 - GIA - Investment History Changes - Bug fixes.
// 
//    Rev 1.4   Dec 03 2011 11:05:22   dchatcha
// P0186477/FN03 - GIA - Purchase, read all records for progressive interest rate
// 
//    Rev 1.3   Dec 03 2011 01:23:30   dchatcha
// P0186477/FN03 - GIA - Purchase
// 
//    Rev 1.2   Dec 01 2011 19:06:24   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.1   Nov 28 2011 21:37:40   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.0   Nov 27 2011 21:22:14   wp040100
// Initial revision.
*/
