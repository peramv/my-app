//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FundSERVBrokerValidation.cpp
// ^AUTHOR : 
// ^DATE   : Apr, 2012
//
// ^CLASS    : FundSERVBrokerValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundservbrokervalidation.hpp"

#include <ifastdataimpl\dse_dstc0439_req.hpp>
#include <ifastdataimpl\dse_dstc0439_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "FundSERVBrokerValidation" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_SERV_BROKER_VALIDATION;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                   State Flags,      Group Flags
   {ifds::WarnCode,                BFCBO::NONE,           0},
   {ifds::WarnDesc,                BFCBO::NONE,           0},
   {ifds::WarnValue1,              BFCBO::NONE,           0},
   {ifds::WarnValue2,              BFCBO::NONE,           0},
   {ifds::WarnValue3,              BFCBO::NONE,           0},
   {ifds::WarnValue4,              BFCBO::NONE,           0},
   {ifds::AutoUpdateSvcAgent,      BFCBO::NONE,           0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);


//******************************************************************************************
FundSERVBrokerValidation::FundSERVBrokerValidation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
}

//******************************************************************************************
FundSERVBrokerValidation::~FundSERVBrokerValidation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY FundSERVBrokerValidation::init(const DString& dstrValidationType,
                                        const DString& dstrAccountNum,
                                        const DString& dstrCurBrokerCode,
                                        const DString& dstrCurBranchCode,
                                        const DString& dstrCurSlsRep,
                                        const DString& dstrNewBrokerCode,
                                        const DString& dstrNewBranchCode,
                                        const DString& dstrNewSlsRep,
                                        const DString& strTrack,
                                        const DString& strPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;

   BFData requestData_(ifds::DSTC0439_REQ);

   requestData_.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData_.setElementValue (ifds::ValidateType, dstrValidationType);
   requestData_.setElementValue (ifds::AccountNum, dstrAccountNum);
   requestData_.setElementValue (ifds::Broker, dstrCurBrokerCode);
   requestData_.setElementValue (ifds::Branch, dstrCurBranchCode);
   requestData_.setElementValue (ifds::Slsrep, dstrCurSlsRep);
   requestData_.setElementValue (ifds::BrokerCodeNew, dstrNewBrokerCode);
   requestData_.setElementValue (ifds::BranchCodeNew, dstrNewBranchCode);
   requestData_.setElementValue (ifds::SlsRepCodeNew, dstrNewSlsRep);
   requestData_.setElementValue (ifds::Track, strTrack);
   requestData_.setElementValue (ifds::Activity, strPageName);

   ReceiveData(DSTC_REQUEST::FUND_SERV_BROKER_VALIDATION, requestData_, 
      ifds::DSTC0439_VW, DSTCRequestor(getSecurity(), false, false));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSERVBrokerValidation.cpp-arc  $
// 
//    Rev 1.1   May 11 2012 18:24:30   dchatcha
// P0186479 FN10 - Gap 14G - Block Service Unit Transfers.
// 
//    Rev 1.0   May 03 2012 09:39:46   dchatcha
// Initial revision.
// 