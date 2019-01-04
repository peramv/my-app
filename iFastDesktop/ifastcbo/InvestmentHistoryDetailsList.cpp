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
// ^FILE   : InvestmentHistoryDetailsList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "entity.hpp"
#include "mfaccount.hpp"
#include "InvestmentHistoryDetails.hpp"
#include "InvestmentHistoryDetailsList.hpp"
#include "worksessionentitylist.hpp"

#include <ifastdataimpl\dse_dstc0424_vw.hpp>
#include <ifastdataimpl\dse_dstc0424_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0424_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INVESTMENT_HISTORY_TRAN_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME	= I_( "InvestmentHistoryDetailsList" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId TransId;
	extern CLASS_IMPORT const BFTextFieldId IntInvestUUID;
}

namespace CND
{
}

//******************************************************************************
InvestmentHistoryDetailsList::InvestmentHistoryDetailsList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0424_REQ)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	setObjectAsList( );
}

//******************************************************************************
InvestmentHistoryDetailsList::~InvestmentHistoryDetailsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY InvestmentHistoryDetailsList::init (const DString& dstrInvHisLotId)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	DString mgmtCoIdOut;
	m_requestData.setElementValue( ifds::InvHisLotId, dstrInvHisLotId );
	m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	m_requestData.setElementValue( ifds::Track, I_("N") );
	
	ReceiveData ( DSTC_REQUEST::INVESTMENT_HISTORY_TRAN_INQUIRY, 
				  m_requestData, 
				  ifds::DSTC0424_VW, 
				  DSTCRequestor (getSecurity(), false), 
				  false);

	return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY InvestmentHistoryDetailsList::doCreateObject (const BFData& data, BFCBO*& pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   	
	pObjOut = new InvestmentHistoryDetails(*this);
	((InvestmentHistoryDetails*)pObjOut)->init(const_cast<BFData&>(data) );

	return( GETCURRENTHIGHESTSEVERITY() );
}

//*************************************************************************************
SEVERITY InvestmentHistoryDetailsList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if (doMoreRecordsExist())
   {
      ReceiveData ( DSTC_REQUEST::INVESTMENT_HISTORY_TRAN_INQUIRY, 
                    m_requestData, 
                    ifds::DSTC0424_VW, 
                    DSTCRequestor(getSecurity(), false), 
                    false);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryDetailsList.cpp-arc  $
// 
//    Rev 1.3   May 28 2012 00:35:28   wp040100
// Removed Comments
// 
//    Rev 1.2   Dec 01 2011 19:08:02   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.1   Nov 25 2011 13:54:36   wp040100
// P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/

