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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AlertMessageList.cpp
// ^AUTHOR :
// ^DATE   : 04 April 2016
//
// ^CLASS    : AlertMessageList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AlertMessageList.hpp"
#include <ifastdataimpl\dse_dstc0470_vw.hpp>
#include <ifastdataimpl\dse_dstc0470_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest ALERT_MESSAGES_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME = I_("AlertMessageList");
}

namespace ALERT_MSG_CODE
{
    extern CLASS_EXPORT I_CHAR * const REMARK_ALERT = I_("05");
}

namespace ifds
{
}

namespace CND
{
}

//******************************************************************************
AlertMessageList::AlertMessageList(BFAbstractCBO &parent)
:MFCanBFCbo(parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

	setObjectAsList();
}


//******************************************************************************
AlertMessageList::~AlertMessageList()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}


//******************************************************************************
SEVERITY AlertMessageList::init(const DString &accountNum,
                                const DString &effectiveDate,
                                const DString &fromScreen,
                                const DString &dstrTrack, 
							    const DString &dstrPageName)                             
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	BFData requestData(ifds::DSTC0470_REQ);
	DString mgmtCoIdOut;

	requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
	requestData.setElementValue(ifds::Track, dstrTrack);
	requestData.setElementValue(ifds::Activity, dstrPageName);
    requestData.setElementValue(ifds::AccountNum, accountNum);
    requestData.setElementValue(ifds::EffectiveDate, effectiveDate);
    requestData.setElementValue(ifds::FromScreen, fromScreen);

    ReceiveData(DSTC_REQUEST::ALERT_MESSAGES_INQUIRY, requestData, ifds::DSTC0470_VW, DSTCRequestor(getSecurity(), true));

	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
/*SEVERITY AlertMessageList::init(const BFData& data)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init(data)"));

	attachDataObject(const_cast<BFData&>(data), false, true);

	return GETCURRENTHIGHESTSEVERITY();
}*/