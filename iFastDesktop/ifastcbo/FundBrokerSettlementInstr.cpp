//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : FundBrokerSettlementInstr.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"

#include "FundBrokerSettlementInstr.hpp"

//#include "MgmtCoOptions.hpp"
//#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_req.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>


namespace
{
   const I_CHAR * const CLASSNAME = I_( "FundBrokerSettlementInstr" );
}

namespace ifds
{   	
	
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,				     State Flags,  Group Flags    
	{ ifds::DeliveryTo,             BFCBO::NONE,     0 },
	{ ifds::ForAccount,             BFCBO::NONE,     0 },	
    { ifds::CashMsgType,            BFCBO::NONE,     0 },
    { ifds::IntermediaryBank,       BFCBO::NONE,     0 },
    { ifds::ReceivingBank,          BFCBO::NONE,     0 },
    { ifds::Beneficiary,            BFCBO::NONE,     0 },
    { ifds::SpecialInstructions,    BFCBO::NONE,     0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );



//******************************************************************************
FundBrokerSettlementInstr::FundBrokerSettlementInstr( BFAbstractCBO &parent )
: SettlementInstr( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
FundBrokerSettlementInstr::~FundBrokerSettlementInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerSettlementInstr.cpp-arc  $
// 
//    Rev 1.1   Nov 26 2004 16:56:24   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.0   Nov 17 2004 15:38:54   aguilaam
// Initial revision.
// 
//    Rev 1.0   Oct 13 2004 13:47:04   VADEANUM
// Initial revision.
//
