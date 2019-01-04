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
// Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPTradeConstantInquiry.cpp
// ^AUTHOR : 
// ^DATE   : Oct, 2010
//
// ^CLASS    : RESPTradeConstantInquiry
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPTradeConstantInquiry.hpp"

#include <ifastdataimpl\dse_dstc0416_req.hpp>
#include <ifastdataimpl\dse_dstc0416_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "RESPTradeConstantInquiry" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_TRADE_CONSTANT_INQUIRY;
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

//******************************************************************************************
RESPTradeConstantInquiry::RESPTradeConstantInquiry( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************************
SEVERITY RESPTradeConstantInquiry::init(const DString& strAccountNum,
                                        const DString& strTaxYear,
                                        const DString& strRESPBenefId,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strTrack,
                                        const DString& strPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString  mgmtCoIdOut;                             
   BFData requestData (ifds::DSTC0416_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, strTrack);
   requestData.setElementValue (ifds::Activity, strPageName);
   requestData.setElementValue (ifds::AccountNum, strAccountNum);
   requestData.setElementValue (ifds::TaxYear, strTaxYear);
   requestData.setElementValue (ifds::RESPBenefId, strRESPBenefId);
   
   ReceiveData(DSTC_REQUEST::RESP_TRADE_CONSTANT_INQUIRY, requestData, 
               ifds::DSTC0416_VW, DSTCRequestor(getSecurity(), false, false));
                          
   return GETCURRENTHIGHESTSEVERITY();                          
   
}
//******************************************************************************************
RESPTradeConstantInquiry::~RESPTradeConstantInquiry()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTradeConstantInquiry.cpp-arc  $
// 
//    Rev 1.0   Oct 29 2010 04:03:08   kitticha
// Initial revision.
// 
*/
