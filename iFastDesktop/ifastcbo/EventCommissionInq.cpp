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
// ^FILE   : EventCommissionInq.cpp
// ^AUTHOR : 
// ^DATE   : Aug, 2012
//
// ^CLASS    : EventCommissionInq
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EventCommissionInq.hpp"

#include <ifastdataimpl\dse_dstc0445_req.hpp>
#include <ifastdataimpl\dse_dstc0445_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest EVENT_COMMISSION_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "EventCommissionInq" );
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

//******************************************************************************************
EventCommissionInq::EventCommissionInq( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( 0,
                       NULL,
                       0,
                       NULL );
}

//******************************************************************************************
EventCommissionInq::~EventCommissionInq()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY EventCommissionInq::init(const DString& acctNum,
                                  const DString& acctTo,
                                  const DString& redCode,
                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;
   BFData queryData (ifds::DSTC0445_REQ);
   
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::AccountNum,acctNum);   
   queryData.setElementValue (ifds::AccountTo,acctTo);
   queryData.setElementValue (ifds::RedCode,redCode);

   ReceiveData( DSTC_REQUEST::EVENT_COMMISSION_INQUIRY,
                queryData, 
                ifds::DSTC0445_VW, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/EventCommissionInq.cpp-arc  $
// 
//    Rev 1.0   Aug 15 2012 14:59:10   dchatcha
// Initial revision.
// 
