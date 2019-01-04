////******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2014 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : SEGFundValidationRules.cpp
// ^AUTHOR : 
// ^DATE   : Aug 2014
//
// ^CLASS    : SEGFundValidationRules
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "SEGFundValidationRules.hpp"

#include <ifastdataimpl\dse_dstc0354_req.hpp>
#include <ifastdataimpl\dse_dstc0354_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SEQ_FUND_VALIDATION_354;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "SEGFundValidationRules" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId EventTransType;
}


//****************************************************************************
SEGFundValidationRules::SEGFundValidationRules( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList();
}

//****************************************************************************
SEGFundValidationRules::~SEGFundValidationRules()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY SEGFundValidationRules::init( const DString &strAccountNum,
                                       const DString &fundCode,
                                       const DString &classCode,
                                       const DString &strEventTransType,
                                       const DString &strContractType,
                                       const DString &dstrContractTypeId,
                                       const DString &strEffectiveDate,
                                       const DString &dstrTrack,
                                       const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   BFData requestData (ifds::DSTC0354_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::AccountNum, strAccountNum );
   requestData.setElementValue (ifds::FundCode, fundCode);
   requestData.setElementValue (ifds::ClassCode, classCode);
   requestData.setElementValue (ifds::ContractType, strContractType );
   requestData.setElementValue (ifds::EffectiveDate, strEffectiveDate, false, false  );
   requestData.setElementValue (ifds::EventTransType, strEventTransType );
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData (DSTC_REQUEST::SEQ_FUND_VALIDATION_354, 
                requestData, 
                ifds::DSTC0354_VW, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//  $Log:   Y:/VCS/BF iFAST/ifastcbo/SEGFundValidationRules.cpp-arc  $
// 

