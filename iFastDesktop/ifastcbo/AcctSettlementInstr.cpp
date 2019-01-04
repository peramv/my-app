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
// ^FILE   : AcctSettlementInstr.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"

#include "AcctSettlementInstr.hpp"

//#include "MgmtCoOptions.hpp"
//#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0317_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AcctSettlementInstr" );
}

namespace CND
{
   extern const long ERR_INVALID_SETTLEMENT_INSTR_CODE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,				  State Flags,	  Group Flags    
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
AcctSettlementInstr::AcctSettlementInstr( BFAbstractCBO &parent )
: SettlementInstr( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
AcctSettlementInstr::~AcctSettlementInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//*******************************************************************************
void AcctSettlementInstr::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   assert (getParent() &&  getParent()->getParent());
	
	DString dstrClearingID;

	getParent()->getParent()->getField (ifds::ClearingID, dstrClearingID, idDataGroup);

	// If Clearing ID is PUEV...
	if ( I_( "P" ) ==  dstrClearingID ) // dstrClearingID.strip().upperCase() )
	{
		setFieldNoValidate( ifds::DeliveryTo, I_( "Clearstream" ), idDataGroup );

		DString dstrAltAccount;
		getParent()->getParent()->getField( ifds::AltAccount, dstrAltAccount, idDataGroup );

		setFieldNoValidate( ifds::ForAccount, dstrAltAccount, idDataGroup );
	}
}

//*********************************************************************************
SEVERITY AcctSettlementInstr::doValidateField( const BFFieldId& idField, 
															  const DString& dstrValue, 
												           const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

	if (idField == ifds::SettlementInstrCode )
	{
	   if ( I_("N/A") == dstrValue )
      {
         // "Invalid value for Settlement Instructions Code"
			ADDCONDITIONFROMFILE( CND::ERR_INVALID_SETTLEMENT_INSTR_CODE );		

      }
   }

   SettlementInstr::doValidateField( idField, dstrValue, idDataGroup );
   
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementInstr.cpp-arc  $
// 
//    Rev 1.5   Dec 09 2004 16:44:12   aguilaam
// PET1117_FN21: settlement instructions, deliveryto required
// 
//    Rev 1.4   Dec 03 2004 16:19:02   vadeanum
// PET1117_FN21:  settlement instructions.
// 
//    Rev 1.3   Nov 30 2004 18:44:24   aguilaam
// PET1117_FN21:  settlement instructions.
// 
//    Rev 1.2   Nov 24 2004 13:02:48   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.1   Nov 19 2004 17:32:22   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0   Oct 13 2004 13:47:04   VADEANUM
// Initial revision.
//
