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
// ^FILE   : SEGTradeEntryValidation.cpp
// ^AUTHOR : 
// ^DATE   : Feb, 2012
//
// ^CLASS    : SEGTradeEntryValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "segtradeentryvalidation.hpp"

#include <ifastdataimpl\dse_dstc0436_req.hpp>
#include <ifastdataimpl\dse_dstc0436_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "SEGTradeEntryValidation" );
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
   extern CLASS_IMPORT const DSTCRequest SEG_TRADE_ENTRY_VALIDATION;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                   State Flags,      Group Flags
   {ifds::WarnCode,                BFCBO::NONE,           0},
   {ifds::WarnDesc,                BFCBO::NONE,           0},
   {ifds::WarnValue1,              BFCBO::NONE,           0},
   {ifds::WarnValue2,              BFCBO::NONE,           0},
   {ifds::WarnValue3,              BFCBO::NONE,           0},
   {ifds::WarnValue4,              BFCBO::NONE,           0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************************
SEGTradeEntryValidation::SEGTradeEntryValidation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
}

//******************************************************************************************
SEGTradeEntryValidation::~SEGTradeEntryValidation()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************************
SEVERITY SEGTradeEntryValidation::init(const DString& dstrAccountNum,
                                       const DString& dstrFundCode,
                                       const DString& dstrClassCode,
                                       const DString& dstrAccountTo,
                                       const DString& dstrFundToCode,
                                       const DString& dstrClassToCode,
                                       const DString& dstrTradeDate,
                                       const DString& dstrValidationType,
                                       const DString& dstrTransType,
                                       const DString& dstrTransID,
                                       const DString& strTrack,
                                       const DString& strPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;

   BFData requestData_(ifds::DSTC0436_REQ);

   requestData_.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData_.setElementValue (ifds::AccountNum, dstrAccountNum);
   requestData_.setElementValue (ifds::FundCode, dstrFundCode);
   requestData_.setElementValue (ifds::ClassCode, dstrClassCode);
   requestData_.setElementValue (ifds::AccountTo, dstrAccountTo);
   requestData_.setElementValue (ifds::FundTo, dstrFundToCode);
   requestData_.setElementValue (ifds::ClassTo, dstrClassToCode);
   requestData_.setElementValue (ifds::TradeDate, dstrTradeDate);
   requestData_.setElementValue (ifds::ValidateType, dstrValidationType);
   requestData_.setElementValue (ifds::TransType, dstrTransType);
   requestData_.setElementValue (ifds::TransId, dstrTransID);
   requestData_.setElementValue (ifds::Track, strTrack);
   requestData_.setElementValue (ifds::Activity, strPageName);

   ReceiveData(DSTC_REQUEST::SEG_TRADE_ENTRY_VALIDATION, requestData_, 
      ifds::DSTC0436_VW, DSTCRequestor(getSecurity(), false, false));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SEGTradeEntryValidation.cpp-arc  $
// 
//    Rev 1.1   Mar 05 2012 11:48:00   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.0   Feb 28 2012 20:41:12   dchatcha
// Initial revision.
// 