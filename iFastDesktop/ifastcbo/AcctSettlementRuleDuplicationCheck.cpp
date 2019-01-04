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
//    Copyright 2008 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctSettlementRuleDuplicationCheck.cpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : April 2008
//
// ^CLASS    : AcctSettlementRuleDuplicationCheck
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "AcctSettlementRuleDuplicationCheck.hpp"

#include <ifastdataimpl\dse_dstc0386_vw.hpp>
#include <ifastdataimpl\dse_dstc0386_req.hpp>
#include <ifastdataimpl\dse_dstc0386_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ACCT_CONTROL_INQUIRY;
};

namespace 
{
    const I_CHAR * const CLASSNAME           = I_( "AcctSettlementRuleDuplicationCheck" );

    const I_CHAR * const NO   = I_ ("N");
    const I_CHAR * const YES  = I_ ("Y");
}

// Reference to Fields
namespace ifds
{
};

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
    //  Field DD Id,                        State Flags,            Group Flags
    { ifds::DuplicateExist,                 BFCBO::NONE,                  0 },
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
AcctSettlementRuleDuplicationCheck::AcctSettlementRuleDuplicationCheck( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
    TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

    registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

    setObjectAsList();
}

//******************************************************************************
AcctSettlementRuleDuplicationCheck::~AcctSettlementRuleDuplicationCheck(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctSettlementRuleDuplicationCheck::init( const DString &dstrAccountNum,
                                                   const DString &dstrRuleType,
                                                   const DString &dstrFundCode,
                                                   const DString &dstrClassCode,
                                                   const DString &dstrEffectiveDate,
                                                   const DString &dstrStopDate,
                                                   const DString &dstrAcctControlsRID,
												   const DString &dstrFundGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init" ));

    BFData requestData( ifds::DSTC0386_REQ );
    BFData responseData( ifds::DSTC0386_VW );

    DString mgmtCoIdOut;
    requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
    requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
    requestData.setElementValue( ifds::NextKey, NULL_STRING );
    requestData.setElementValue( ifds::Track, I_( "N" ) );
    requestData.setElementValue( ifds::Activity, NULL_STRING );
    requestData.setElementValue( ifds::RuleType, dstrRuleType );
    requestData.setElementValue( ifds::FundCode, dstrFundCode );
    requestData.setElementValue( ifds::ClassCode, dstrClassCode );
    requestData.setElementValue( ifds::EffectiveDate, dstrEffectiveDate );
    requestData.setElementValue( ifds::StopDate, dstrStopDate );
    requestData.setElementValue( ifds::AcctControlsRID, dstrAcctControlsRID );
    requestData.setElementValue( ifds::DuplicateCheck, I_( "Y" ) );
    requestData.setElementValue( ifds::InquiryType, I_("SETMNTRULE") );
	requestData.setElementValue( ifds::FundGroup, dstrFundGroup );

    DSTCRequestor& dstcRequestor = DSTCRequestor( getSecurity(), true);
    dstcRequestor.setRecycleOnReceive( true );

    ReceiveData( DSTC_REQUEST::ACCT_CONTROL_INQUIRY, 
                 requestData, 
                 //responseData,
                 ifds::DSTC0386_VW,
                 DSTCRequestor( getSecurity (), true, true ) );

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AcctSettlementRuleDuplicationCheck::buildKey( DString &strKey,
                                                    const DString &dstrAccountNum,
                                                    const DString &dstrRuleType,
                                                    const DString &dstrFundCode,
                                                    const DString &dstrClassCode,
                                                    const DString &dstrEffectiveDate,
                                                    const DString &dstrStopDate,
                                                    const DString &dstrAcctControlsRID,
													const DString &dstrFundGroup
                                                  )
{
    strKey = 
            I_("AccountNum=")       + dstrAccountNum    +
            I_(";RuleType=")        + dstrRuleType      +
            I_(";FundCode=")        + dstrFundCode      +
            I_(";ClassCode=")       + dstrClassCode     +
            I_(";EffectiveDate=")   + dstrEffectiveDate +
            I_(";StopDate=")        + dstrStopDate      +
			I_(";FundGroup=")       + dstrFundGroup; //     +
            //I_(";AcctControlsRID=")          + dstrAcctControlsRID;

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementRuleDuplicationCheck.cpp-arc  $ */
// 
//    Rev 1.1   Jan 31 2011 18:03:22   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.0   Apr 16 2008 18:43:52   daechach
// Initial revision.
