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
// ^FILE   : AcctFundLevelSettleDays.cpp
// ^AUTHOR : 
// ^DATE   : February, 2017
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtco.hpp"
#include "AcctFundLevelSettleDays.hpp"
#include "funddetaillist.hpp"
#include <ifastdataimpl\dse_dstc0476_vw.hpp>
#include <ifastdataimpl\dse_dstc0476_req.hpp>
#include <ifastdataimpl\dse_dstc0476_vwrepeat_record.hpp>

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;

   const char *const CFX_TRANS = "CFXTRAN";
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_FUND_LEVEL_SETTLEDAYS_INQUIRY;
}

namespace CND
{  
  extern const long WARN_SETTLEDAYS_LESS_THAN_FUND_LEVEL_SETTLEDAYS;
  extern const long ERR_SETTLEDAYS_LESS_THAN_FUND_LEVEL_SETTLEDAYS;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const SETTLEDAYS_LESS_THEN_FUND_LEVEL_SETTLEDAYS;
}

namespace ifds
{
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
}

namespace
{
	const I_CHAR * const CLASSNAME           = I_ ("AcctFundLevelSettleDays");
	const I_CHAR * const Short_SETTLEDAYS    = I_ ("Short_SETTLEDAYS");
}
//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ ifds::SettleDays,                     BFCBO::NONE,                  0 },
	{ ifds::FundCode,						BFCBO::NONE,                  0 },
	{ ifds::ClassCode,                      BFCBO::NONE,                  0 },
	{ ifds::EffectiveDate,                  BFCBO::NONE,                  0 },
};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AcctFundLevelSettleDays::AcctFundLevelSettleDays (BFAbstractCBO &parent)
: MFCanBFCbo (parent),
_fundCode(NULL),
_classCode (NULL)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
AcctFundLevelSettleDays::~AcctFundLevelSettleDays ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
void AcctFundLevelSettleDays::buildKey( DString &strKey,
						  const DString &dstrAccountNum,
						  const DString &dstrFundCode,
						  const DString &dstrClassCode,
						  const DString &dstrTransType,
						  const DString &dstrSettleDays,
						  const DString &dstrStartDate )
{
	    strKey = I_("AccountNum=")       + dstrAccountNum    +
				 I_(";FundCode=")        + dstrFundCode      +
				 I_(";ClassCode=")       + dstrClassCode     +
				 I_(";TransType=")       + dstrTransType     +
				 I_(";SettleDays=")      + dstrSettleDays    +
				 I_(";StartDate=")		 + dstrStartDate;
}
//******************************************************************************
SEVERITY AcctFundLevelSettleDays::init (const DString &dstrAccountNum, 
                                 const DString &dstrfundCode, 
                                 const DString &dstrclassCode, 
                                 const DString &dstrTransType, 
                                 const DString &dstrSettleDays, 
                                 const DString &dstrStartDate,
								 const DString &dstrTrack, 
								 const DString &dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	requestData = new BFData (ifds::DSTC0476_REQ);
	DString mgmtCoIdOut;

	_fundCode = dstrfundCode;
	_classCode = dstrclassCode;

	requestData->setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	requestData->setElementValue( ifds::Track, dstrTrack );
	requestData->setElementValue( ifds::Activity, dstrPageName );
	requestData->setElementValue(ifds::AccountNum, dstrAccountNum);
	requestData->setElementValue(ifds::FundCode, dstrfundCode);
	requestData->setElementValue(ifds::ClassCode, dstrclassCode);
	requestData->setElementValue(ifds::TransType, dstrTransType);
	requestData->setElementValue(ifds::SettleDays, dstrSettleDays);
	requestData->setElementValue(ifds::StartDate, dstrStartDate);

	ReceiveData(DSTC_REQUEST::ACCT_FUND_LEVEL_SETTLEDAYS_INQUIRY, 
				*requestData,
				ifds::DSTC0476_VW, 
				DSTCRequestor(getSecurity(), false));

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY AcctFundLevelSettleDays::addConditions ()
{
	MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("addConditions"));

	FundDetailList	*pFundDetailList;
	FundDetail *pFundDetail;

	if  (getMgmtCo ().getFundDetailList  (pFundDetailList) <= WARNING &&
		pFundDetailList)
	{
		if  (pFundDetailList->getFundDetail  (_fundCode, _classCode, BF::HOST, pFundDetail) &&
			pFundDetail)
		{
			DString idiStr, errNum, errMsg;

			BFObjIter iter  (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
			iter.begin ();

			while  (!iter.end ())
			{
				idiStr = NULL_STRING;
				iter.getObject ()->getField  (ifds::ErrNum, errNum, BF::HOST, false);         
				iter.getObject ()->getField  (ifds::ErrMsg, errMsg, BF::HOST, false);
				addIDITagValue  (idiStr, Short_SETTLEDAYS, errMsg);
				long nErrNum = errNum.strip ().stripLeading ('0').convertToULong ();
				if( !errNum.empty() && errNum == IFASTERR::SETTLEDAYS_LESS_THEN_FUND_LEVEL_SETTLEDAYS )
				{ 
					getErrMsg(IFASTERR::SETTLEDAYS_LESS_THEN_FUND_LEVEL_SETTLEDAYS,
						CND::ERR_SETTLEDAYS_LESS_THAN_FUND_LEVEL_SETTLEDAYS,
						CND::WARN_SETTLEDAYS_LESS_THAN_FUND_LEVEL_SETTLEDAYS,
						BF::HOST, idiStr);
				}  
				++iter;
			}
		}
	}
	return (GETCURRENTHIGHESTSEVERITY ());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctFundLevelSettleDays.cpp-arc  $*/
