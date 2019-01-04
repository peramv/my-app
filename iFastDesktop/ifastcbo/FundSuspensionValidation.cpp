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
//    Copyright 2018 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundSuspensionValidation.cpp
// ^AUTHOR : 
// ^DATE   : 10 May, 2018
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtco.hpp"
#include "FundSuspensionValidation.h"
#include <ifastdataimpl\dse_dstc0486_req.hpp>
#include <ifastdataimpl\dse_dstc0486_vw.hpp>

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;

   const char *const CFX_TRANS = "CFXTRAN";
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_SUSPENSION_VALIDATION;
}

namespace CND
{  
	
	extern const long ERR_TRADING_SUSPENSION_ACTIVE_FOR_FUND ;	
	extern const long WARN_TRADING_SUSPENSION_ACTIVE_FOR_FUND;	

	extern const long ERR_FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE;
    extern const long WARN_FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE;
}

namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const TRADING_SUSPENSION_ACTIVE_FOR_FUND;
	extern CLASS_IMPORT I_CHAR * const FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE;
	
}

namespace
{
	const I_CHAR * const CLASSNAME           = I_ ("FundSuspensionValidation");
    const I_CHAR * const FUND_CODE           = I_ ("FUND_CODE");

	const long FUND_SUSPENSION_VALIDATION = 2074 ;
    const long FUND_LIQUIDITY_GATING_MEASURE = 2129 ;

	
}
FundSuspensionValidation::FundSuspensionValidation (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	
}

//******************************************************************************
FundSuspensionValidation::~FundSuspensionValidation ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}


//******************************************************************************
SEVERITY FundSuspensionValidation::init ( const DString &strRunMode, 
										  const DString &strFromFundCode,
										  const DString &strFromClassCode, 
										  const DString &strTransType, 
										  const DString &strDealDate, 
										  const DString &strDealTime,
										  const DString &strFundToCode, 
										  const DString &strClassToCode,
										  const DString &strDepositType, 
										  const DString &strRedCode,
										  const DString &dstrTrack, 
										  const DString &dstrPageName)
{

	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
	BFData queryData  (ifds::DSTC0486_REQ);

	DString mgmtCoIdOut;

	queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	queryData.setElementValue( ifds::Track, dstrTrack );
	queryData.setElementValue( ifds::Activity, dstrPageName );
	queryData.setElementValue (ifds::RunMode, strRunMode);
	queryData.setElementValue (ifds::FromFundCode, strFromFundCode);
	queryData.setElementValue (ifds::FromClassCode, strFromClassCode);
	queryData.setElementValue (ifds::TransType, strTransType);
	queryData.setElementValue (ifds::DealDate, strDealDate);
	queryData.setElementValue (ifds::DealTime, strDealTime);
	queryData.setElementValue (ifds::FundToCode, strFundToCode);
	queryData.setElementValue (ifds::ClassToCode, strClassToCode);
	queryData.setElementValue (ifds::DepositType, strDepositType);
	queryData.setElementValue (ifds::RedCode, strRedCode);

	ReceiveData  (DSTC_REQUEST::FUND_SUSPENSION_VALIDATION, 
                 queryData, 
                 ifds::DSTC0486_VW,
                 DSTCRequestor  (getSecurity (), false));

	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY FundSuspensionValidation::addConditions ()
{
	MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("addConditions"));

	DString errNum,fundCode,idiStr;


    BFObjIter iter  (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
	iter.begin ();

	while  (!iter.end ())
	{
		idiStr = NULL_STRING;
		iter.getObject ()->getField  (ifds::RejErrNum, errNum, BF::HOST, false);
		iter.getObject ()->getField  (ifds::RejFundCode, fundCode, BF::HOST, false);

		long nErrNum = errNum.strip ().stripLeading ('0').convertToULong ();
		if(errNum.empty())
			return (GETCURRENTHIGHESTSEVERITY ());

		addIDITagValue  (idiStr, FUND_CODE, fundCode);

		switch  (nErrNum)
		{             
		case FUND_SUSPENSION_VALIDATION:
			{
				getErrMsg ( IFASTERR::TRADING_SUSPENSION_ACTIVE_FOR_FUND, 
					CND::ERR_TRADING_SUSPENSION_ACTIVE_FOR_FUND, 
					CND::WARN_TRADING_SUSPENSION_ACTIVE_FOR_FUND, 
					BF::HOST,idiStr);				
			}
			break;
		case FUND_LIQUIDITY_GATING_MEASURE:
			{
				getErrMsg ( IFASTERR::TRADING_SUSPENSION_ACTIVE_FOR_FUND, 
					CND::ERR_FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE, 
					CND::WARN_FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE, 
					BF::HOST,idiStr);				
			}
			break;
			default:
			assert(0);	
		}
		++iter;

	}
	return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/*   $*/

//  Rev 1.0   May 10 2018 15:24:04   Amit k Mallick
//	Initial revision.