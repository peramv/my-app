//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : TradeSettlementLocations.cpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// ^CLASS    : TradeSettlementLocations
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "TradeSettlementLocations.hpp"
#include "TradeSettlementLocationsList.hpp"
#include <ifastdataimpl\dse_dstc0397_vwrepeat_record.hpp>

#include "mgmtco.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_("TradeSettlementLocations");
}

namespace ifds
{   
	extern CLASS_IMPORT const BFTextFieldId RecordType;
	extern CLASS_IMPORT const BFTextFieldId RecId;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//	Field DD Id,				State Flags,	Group Flags    
	{ifds::TransClrSettlAmt,	BFCBO::NONE,	0 },
	{ifds::SettleLocCode,		BFCBO::REQUIRED,0 },
	{ifds::ForAccount,			BFCBO::NONE,	0 },
	{ifds::TransClrSettlUUID,	BFCBO::NONE,	0 },
    {ifds::RecordType,			BFCBO::NONE,	0 },
	{ifds::InFavourOf,			BFCBO::NONE,	0 },
    {ifds::DeliveryTo,			BFCBO::NONE,	0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
TradeSettlementLocations::TradeSettlementLocations( BFAbstractCBO &parent ) : MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}
//******************************************************************************************
TradeSettlementLocations::~TradeSettlementLocations()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}     

//************************************************************************************
SEVERITY TradeSettlementLocations::initNew (const BFDataGroupId &idDataGroup, bool bSetFieldsReadOnly)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));  	

	commonInit (bSetFieldsReadOnly, idDataGroup);
    
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY TradeSettlementLocations::init (const BFData& data,
                                         const BFDataGroupId& idDataGroup /*= BF::HOST*/,
                                         bool bSetFieldsReadOnly /*=false*/)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	attachDataObject (const_cast<BFData&>(data), false);
	
	commonInit (bSetFieldsReadOnly, idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TradeSettlementLocations::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{  
	setFieldNoValidate (ifds::TransClrSettlUUID, I_("0"), idDataGroup, false);
}

//***********************************************************************************
SEVERITY TradeSettlementLocations::commonInit (bool bSetFieldsReadOnly, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));
   
	DString substList;

	setFieldNoValidate (ifds::RecordType, I_("MultiSettleLoc"), idDataGroup, false);
	
	TradeSettlementLocationsList *pTradeSettlementLocationsList = dynamic_cast<TradeSettlementLocationsList*>( getParent( ) );      

	if (pTradeSettlementLocationsList)
	{
		pTradeSettlementLocationsList->getMasterList (substList, idDataGroup);		
	}
	
	setFieldAllSubstituteValues (ifds::SettleLocCode, idDataGroup, substList ); 

	if (bSetFieldsReadOnly)
	{
	   for (int i = 0; i < NUM_FIELDS; i++)
	   {
	      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
	      const BFFieldId &fieldId = fieldInfo.getFieldId();

	      setFieldReadOnly (fieldId, idDataGroup, true);
	   }
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY TradeSettlementLocations::doValidateField(const BFFieldId &idField,
                                                   const DString &strValue,
                                                   const BFDataGroupId &idDataGroup)

{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

	if (idField == ifds::SettleLocCode)
	{
		// Duplicate check
		TradeSettlementLocationsList *pTradeSettlementLocationsList = dynamic_cast<TradeSettlementLocationsList*>( getParent( ) );      

		if (pTradeSettlementLocationsList)
		{
			pTradeSettlementLocationsList->checkDuplicate( this, idDataGroup );		
		}
	}
	
	return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************************
SEVERITY TradeSettlementLocations::doApplyRelatedChanges (const BFFieldId &idField, 
                                                          const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges"));

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************

SEVERITY TradeSettlementLocations::setSettleLocAmountInvalid( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettleLocAmountInvalid" ) );

	setValidFlag( ifds::TransClrSettlAmt,   idDataGroup, false );
	setUpdatedFlag( ifds::TransClrSettlAmt, idDataGroup, true );

	return GETCURRENTHIGHESTSEVERITY();
}

/* $Log::  
*/
