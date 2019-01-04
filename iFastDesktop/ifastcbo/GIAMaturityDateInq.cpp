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
// Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : GIAMaturityDateInq.cpp
// ^AUTHOR : 
// ^DATE   : Nov, 2011
//
// ^CLASS    : GIAMaturityDateInq
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "giamaturitydateinq.hpp"

#include <ifastdataimpl\dse_dstc0426_req.hpp>
#include <ifastdataimpl\dse_dstc0426_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "GIAMaturityDateInq" );
}

namespace ifds
{
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest GIA_MATURITY_DATE_INQUIRY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags
   { ifds::MaturityDate,      BFCBO::NONE,         0 }, 
   { ifds::NextIntCredDate,   BFCBO::NONE,         0 },
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************************
GIAMaturityDateInq::GIAMaturityDateInq( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
}

//******************************************************************************************
GIAMaturityDateInq::~GIAMaturityDateInq()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY GIAMaturityDateInq::init(const DString& dstrTradeDate,
                                  const DString& dstrInvestTerm,
                                  const DString& dstrIntCredFreq,
                                  const DString& dstrLastIntCredDate,
                                  const DString& strTrack,
                                  const DString& strPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;

   BFData requestData_  = BFData(ifds::DSTC0426_REQ);

   requestData_.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData_.setElementValue (ifds::TradeDate, dstrTradeDate);
   requestData_.setElementValue (ifds::InvestTerm, dstrInvestTerm);
   requestData_.setElementValue (ifds::IntCredFreq, dstrIntCredFreq);
   requestData_.setElementValue (ifds::LastIntCredDate, dstrLastIntCredDate);
   requestData_.setElementValue (ifds::Track, strTrack);
   requestData_.setElementValue (ifds::Activity, strPageName);

   ReceiveData(DSTC_REQUEST::GIA_MATURITY_DATE_INQUIRY, requestData_, 
      ifds::DSTC0426_VW, DSTCRequestor(getSecurity(), true, true, false));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/GIAMaturityDateInq.cpp-arc  $
// 
//    Rev 1.1   Nov 30 2011 17:59:22   dchatcha
// P0186477/FN03 - GIA - Purchase, fix crashing on reading an update maturity date.
// 
//    Rev 1.0   Nov 30 2011 00:19:24   dchatcha
// Initial revision.
// 
