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
// ^FILE   : SettlementInstr.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "SettlementInstr.hpp"
#include "SettlementInstrList.hpp"
#include "AcctSettlementInstrList.hpp"
#include "MFAccount.hpp"

#include <ifastdataimpl\dse_dstc0317_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0317_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SettlementInstr" );
}

namespace CND
{
   extern const long ERR_DUPLICATE_RECORD;
   extern const long ERR_MULTIPLE_DEFAULT;
   extern const long ERR_EFF_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_STOP_DATE_BEFORE_BUSSINESDAY;
   extern const long ERR_EFFECTIVE_DATE_BEFORE_CURBUSDATE;
}

namespace ifds
{
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId SettlementInstrCode;
	extern CLASS_IMPORT const BFTextFieldId InstrXEdit;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,				State Flags,		Group Flags 
	{ ifds::SettlementInstrCode,    BFCBO::REQUIRED, 0 },
	{ ifds::DeliveryTo,             BFCBO::NONE,     0 },
	{ ifds::ForAccount,             BFCBO::NONE,     0 },
	{ ifds::InFavourOf,             BFCBO::NONE,     0 },
	
	{ ifds::CSDLocation,            BFCBO::NONE,     0},
	{ ifds::CSDAcctNum,             BFCBO::NONE,     0 },
	
	{ ifds::DefaultSettlementInstr, BFCBO::NONE,     0 },
	{ ifds::EffectiveDate,			BFCBO::NONE,     0 },
	{ ifds::StopDate,				BFCBO::NONE,     0 },
    { ifds::InstrXEdit,	 	        BFCBO::IMMEDIATE_VALIDATION, 0 },
    { ifds::AcctClearingMethod,     BFCBO::NONE,     0 },
    { ifds::CashMsgType,            BFCBO::NONE,     0 },
    { ifds::IntermediaryBank,       BFCBO::NONE,     0 },
    { ifds::ReceivingBank,          BFCBO::NONE,     0 },
    { ifds::Beneficiary,            BFCBO::NONE,     0 },
    { ifds::SpecialInstructions,    BFCBO::NONE,     0 },

   // Admin/Date fields
   { ifds::ProcessDate, BFCBO::NONE,     0 }, 
   { ifds::Username,    BFCBO::NONE,     0 }, 
   { ifds::ModDate,     BFCBO::NONE,     0 }, 
   { ifds::ModUser,     BFCBO::NONE,     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
SettlementInstr::SettlementInstr( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	

   addCrossEdit(ifds::InstrXEdit, ifds::SettlementInstrCode );
   addCrossEdit(ifds::InstrXEdit, ifds::EffectiveDate );
   addCrossEdit(ifds::InstrXEdit, ifds::StopDate );
}

//******************************************************************************
SettlementInstr::~SettlementInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//*******************************************************************************
SEVERITY SettlementInstr::init(const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
	
	setFieldNoValidate(ifds::DefaultSettlementInstr, I_("N"), idDataGroup, false ); 

	clearUpdatedFlags( idDataGroup, true );

	setFieldRequired (ifds::DeliveryTo, idDataGroup, true ); 
   
	DString dstrStopDate,  dstrCurrBusDate;

	getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
	getWorkSession().getDateInHostFormat(dstrStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

	setFieldNoValidate( ifds::EffectiveDate, dstrCurrBusDate, idDataGroup );
	setFieldNoValidate( ifds::StopDate, dstrStopDate, idDataGroup, false, true, true );   

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementInstr::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject(const_cast<BFData&>(data), false); 

   setFieldReadOnly( ifds::SettlementInstrCode, BF::HOST, true );
   setFieldReadOnly( ifds::EffectiveDate, BF::HOST, true );

   setFieldRequired (ifds::DeliveryTo, BF::HOST, true ); 

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY SettlementInstr::doValidateField( const BFFieldId& idField, 
																 const DString& dstrValue, 
												             const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

	if (idField == ifds::SettlementInstrCode )
	{
		validateSettlementInstrCode( dstrValue, idDataGroup );
    }
	else if (idField == ifds::EffectiveDate)
	{
		validateEffectiveDate (dstrValue, idDataGroup);
	}
	else if (idField == ifds::StopDate)
	{
		validateStopDate (dstrValue, idDataGroup);
	}
	else if (idField == ifds::InstrXEdit)
	{
		 SettlementInstrList *pSettlementInstrList = dynamic_cast<SettlementInstrList*>( getParent( ) );      

		if (pSettlementInstrList)
		{
				pSettlementInstrList->checkDuplicate( this, idDataGroup );		
		}
	}

   	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void SettlementInstr::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
}

//*******************************************************************************
SEVERITY SettlementInstr::validateSettlementInstrCode( const DString& dstrSettlementInstrCode, 
																		 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSettlementLocation") );

	//DString dstrLocaldSettlementInstrCode( dstrSettlementInstrCode );
 //  dstrLocaldSettlementInstrCode.strip().upperCase();

 //  if( !dstrLocaldSettlementInstrCode.empty() )
 //  {     	
	//   
	//	//bool bExist = (dynamic_cast<SettlementInstrList*>(getParent()) )->isDuplicateSettlementLocation( dstrLocaldSettlementInstrCode, 
	//	//	                                                                                              idDataGroup );
	//	//if( bExist )
	//	//{
	//	//	// "Duplicate record"
	//	//	ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_RECORD );		
	//	//}
	//}
	
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY SettlementInstr::validateEffectiveDate( const DString& dstrEffectiveDate, 
								                 const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEffectiveDate") );

	DString dstrCurrBusDate;
	DString dstrStopDate;

	getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
	getField(ifds::StopDate,dstrStopDate,idDataGroup );

	if (DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrCurrBusDate) == DSTCommonFunctions::FIRST_EARLIER)
	{
		ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVE_DATE_BEFORE_CURBUSDATE);
	}
	else if (DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrStopDate) == DSTCommonFunctions::SECOND_EARLIER)
	{
		ADDCONDITIONFROMFILE(CND::ERR_EFF_DATE_LATE_THAN_STOP_DATE);
	}


	return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************
SEVERITY SettlementInstr::validateStopDate( const DString& dstrStopDate, 
										    const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateStopDate") );

	DString dstrEffectiveDate;
	DString dstrCurrBusDate;

	getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
	getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup );
	
	if (DSTCommonFunctions::CompareDates (dstrStopDate, dstrCurrBusDate) == DSTCommonFunctions::FIRST_EARLIER)
	{
		ADDCONDITIONFROMFILE(CND::ERR_STOP_DATE_BEFORE_BUSSINESDAY);
	}
	else if (DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrStopDate) == DSTCommonFunctions::SECOND_EARLIER)
	{
		ADDCONDITIONFROMFILE(CND::ERR_EFF_DATE_LATE_THAN_STOP_DATE);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY SettlementInstr::validateDefaultSettlementInstr( const DString& dstrDefaultCode, 
																          const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDefault") );
	
   DString dstrLocalDefault( dstrDefaultCode );
   dstrLocalDefault.strip().upperCase();

   if( !dstrLocalDefault.empty() )
   {      
		bool bExist = (dynamic_cast<SettlementInstrList*>(getParent()) )->isDuplicateDefault( dstrLocalDefault, 
																														  idDataGroup );
		if( bExist )
		{
			// Multiple default items assigned.
			//ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_DEFAULT );		
		}
	}	

   return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementInstr.cpp-arc  $
// 
//    Rev 1.8   Nov 07 2007 12:06:02   daechach
// PET 5614 FN 01 - Acct Level Override for Clearing Settle Method
// 
//    Rev 1.7   May 04 2007 13:49:30   jankovii
// PET 2321 FN01 - MT54X Default Pay Type.
// 
//    Rev 1.6   Dec 09 2004 16:43:50   aguilaam
// PET1117_FN21: settlement instructions, deliveryto required
// 
//    Rev 1.5   Dec 01 2004 20:33:04   vadeanum
// PET1117_FN21: settlement instructions - the key should be read only
// 
//    Rev 1.4   Nov 26 2004 16:56:30   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.3   Nov 19 2004 17:33:16   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.2.1.0   Nov 14 2004 14:54:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Oct 13 2004 13:41:52   VADEANUM
// PET 1117 FN21 - Commented out code until field will be added to dd.
// 
//    Rev 1.1   Oct 13 2004 13:40:16   VADEANUM
// PET 1117 FN21 - Commented out field until it will be added to dd.
// 
//    Rev 1.0   Oct 13 2004 13:33:44   VADEANUM
// Initial revision.
//
