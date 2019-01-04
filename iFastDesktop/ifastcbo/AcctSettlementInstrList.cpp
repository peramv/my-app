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
//    Copyright 2003 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : AcctSettlementInstrList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "AcctSettlementInstr.hpp"
#include "AcctSettlementInstrList.hpp"
#include "SettlementInstrList.hpp"

#include <ifastdataimpl\dse_dstc0317_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0317_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLEMENT_INSTRUCTIONS_LIST_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AcctSettlementInstrList" );
   const I_CHAR * const STOP_DATE      = I_( "DATE") ;
}

namespace ifds
{
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace CND
{
   extern const long ERR_MISSING_DEFAULT_SETTLEMENT_INSTR;
   extern const long ERR_MULTIPLE_DEFAULT_SETTLEMENT_INSTR;
   extern const long WARN_MISSING_FUTURE_DEFAULT_SETTL_INSTR;
}

****************************************************************************
AcctSettlementInstrList::AcctSettlementInstrList( BFAbstractCBO &parent )
: SettlementInstrList( parent ),
m_requestData( ifds::DSTC0317_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	
   setObjectAsList( );
}

//******************************************************************************
AcctSettlementInstrList::~AcctSettlementInstrList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}



//***********************************************************************************
SEVERITY AcctSettlementInstrList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
	pObjOut =  new AcctSettlementInstr( *this );
   ((AcctSettlementInstr*) pObjOut)->init( data );
   
	return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY AcctSettlementInstrList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   
	pObjOut =  new AcctSettlementInstr( *this );
   ((AcctSettlementInstr*) pObjOut)->init( idDataGroup );
   
	return( GETCURRENTHIGHESTSEVERITY() );
}

//**********************************************************************************
void  AcctSettlementInstrList::getStrKey( DString &dstrKey, const BFData *data  )
{
   if (data) 
   { 
		DString dstrAccountNum = data->getElementValue (ifds::AccountNum );
		DString dstrSettleInstrCode = data->getElementValue (ifds::SettlementInstrCode );
		DString dstrEffectiveDate = data->getElementValue (ifds::EffectiveDate );
		DString dstrStopDate = data->getElementValue (ifds::StopDate );
      
		buildKey(	dstrKey, 
					dstrAccountNum, 
					dstrSettleInstrCode,
					dstrEffectiveDate,
					dstrStopDate);		
   }
   else
   {
		BFCBO::getStrKey (dstrKey, NULL);
   }
}

//**********************************************************************************
void  AcctSettlementInstrList::buildKey( DString &dstrKey, 
					  					 const DString &dstrAccountNum,
										 const DString &dstrSettleInstrCode,
										 const DString &dstrEffectiveDate,
										 const DString &dstrStopDate)
{
	DString dstrLocalAccountNum(dstrAccountNum),
		    dstrLocalSettleInstrCode(dstrSettleInstrCode),
			dstrLocalEffectiveDate (dstrEffectiveDate),
			dstrLocalStopDate (dstrStopDate);   
	
	dstrKey = I_("AccountNum=") + dstrLocalAccountNum.stripAll().upperCase() +
			  I_(";SettlementInstrCode=") + dstrLocalSettleInstrCode.stripAll().upperCase() +
			  I_(";EffectiveDate=") + dstrLocalEffectiveDate.stripAll().upperCase() +
			  I_(";StopDate=") + dstrLocalStopDate.stripAll().upperCase();
}

//**********************************************************************************
SEVERITY AcctSettlementInstrList:: getAcctSettlementInstr(	const DString &dstrSettleInstrCode,	
											   				const BFDataGroupId &idDataGroup,
												            AcctSettlementInstr *&pAcctSettlementInstr )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAcctSettlementInstr") );

	pAcctSettlementInstr = NULL;

	DString dstrKey, dstrAccountNum;
	getParent()->getParent()->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
	buildKey( dstrKey, dstrAccountNum, dstrSettleInstrCode, NULL_STRING, NULL_STRING );

	pAcctSettlementInstr = dynamic_cast<AcctSettlementInstr*>( getObject( dstrKey, idDataGroup ) );

	return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************
SEVERITY AcctSettlementInstrList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

	if (validateDuplicateDefaultInstr (idDataGroup) <= WARNING)
	{
		DString dstrInstrCode = NULL_STRING;
		DString dstrStopDate = NULL_STRING;

		if (doesActiveDefaultInstrExist (idDataGroup, dstrInstrCode, dstrStopDate) <= WARNING)
		{
			doesFutureDefaultInstrExist (idDataGroup, dstrInstrCode, dstrStopDate);
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************

SEVERITY AcctSettlementInstrList::validateDuplicateDefaultInstr(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDuplicateDefaultInstr") );

	// Check to ensure that one list item is marked default if a list exists.
	short nFound = 0;
	DString dstrDefault;
	DString dstrInstrCode,
			dstrEffectiveDate,
			dstrStopDate;
	DString tmpInstrCode,
			tmpEffectiveDate,
			tmpStopDate;
	bool	bHasDuplicate = false;

	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	while( !iter.end())
	{
		if( !iter.isDummy() )
		{
			tmpInstrCode = NULL_STRING;

			iter.getObject()->getField( ifds::DefaultSettlementInstr, dstrDefault, idDataGroup, false );
			
			if( dstrDefault != I_("Y") ) 
			{
				++iter;
				continue;
			}

			// get default data
			iter.getObject()->getField( ifds::SettlementInstrCode, dstrInstrCode, idDataGroup, false );
			iter.getObject()->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
			iter.getObject()->getField( ifds::StopDate, dstrStopDate, idDataGroup, false );

			BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			while( !iter1.end())
			{
				iter1.getObject()->getField( ifds::DefaultSettlementInstr, dstrDefault, idDataGroup, false );
				iter1.getObject()->getField( ifds::SettlementInstrCode, tmpInstrCode, idDataGroup, false );

				dstrDefault.stripAll().upperCase();

				if (dstrDefault != I_("Y") ||  dstrInstrCode == tmpInstrCode ) 
				{
					++iter1;
					continue;
				}

				iter1.getObject()->getField( ifds::EffectiveDate, tmpEffectiveDate, idDataGroup, false );
				iter1.getObject()->getField( ifds::StopDate, tmpStopDate, idDataGroup, false );

				if( DSTCommonFunctions::dateRangesOverlap (dstrEffectiveDate, dstrStopDate,
														   tmpEffectiveDate, tmpStopDate))
				{
					bHasDuplicate = true;
					break;
				}
				++iter1;
			};
		}

		if (bHasDuplicate)
			break;

		++iter;
	}
	
	if( bHasDuplicate)
	{
		ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_DEFAULT_SETTLEMENT_INSTR ); // This is backup.  Should be caught earlier.
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY AcctSettlementInstrList::doesActiveDefaultInstrExist(const BFDataGroupId& idDataGroup,
															  DString &dstrInstrCode,
															  DString &dstrStopDate)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doesActiveDefaultInstrExist") );

	bool bExist = false;
	DString dstrCurrBusDate;
	DString dstrEffectiveDate;
	DString dstrDefault;

	getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	
	while( !iter.end())
	{
		if( !iter.isDummy() )
		{
			iter.getObject()->getField( ifds::DefaultSettlementInstr, dstrDefault, idDataGroup, false );

			dstrDefault.stripAll().upperCase();
			
			if( dstrDefault == I_("Y") ) 
			{
				iter.getObject()->getField( ifds::SettlementInstrCode, dstrInstrCode, idDataGroup, false );
				iter.getObject()->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
				iter.getObject()->getField( ifds::StopDate, dstrStopDate, idDataGroup, false );

				if (((DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrCurrBusDate) == DSTCommonFunctions::FIRST_EARLIER) ||
					(DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrCurrBusDate) == DSTCommonFunctions::EQUAL)) &&
					(DSTCommonFunctions::CompareDates (dstrCurrBusDate, dstrStopDate) == DSTCommonFunctions::FIRST_EARLIER) ||
					(DSTCommonFunctions::CompareDates (dstrCurrBusDate, dstrStopDate) == DSTCommonFunctions::EQUAL))
					
				{
					bExist = true;
					break;
				}
			}
		}

		++iter;
	}
	
	if (!bExist)
		ADDCONDITIONFROMFILE( CND::ERR_MISSING_DEFAULT_SETTLEMENT_INSTR );
		
	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY AcctSettlementInstrList::doesFutureDefaultInstrExist(const BFDataGroupId& idDataGroup,
															  const DString dstrInstrCode,
															  const DString dstrStopDate)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doesActiveDefaultInstrExist") );

	bool bExist = false;
	DString	tmpInstrCode;
	DString tmpEffectiveDate;
	DString tmpStopDate;
	DString dstrDefault;
	DString dstrEndOfTime;

	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	
	while( !iter.end())
	{
		if( !iter.isDummy() )
		{
			iter.getObject()->getField( ifds::DefaultSettlementInstr, dstrDefault, idDataGroup, false );
			iter.getObject()->getField( ifds::SettlementInstrCode, tmpInstrCode, idDataGroup, false );
			dstrDefault.stripAll().upperCase();

			if (dstrInstrCode == tmpInstrCode)
			{
				++iter;
				continue;
			}
			
			if( dstrDefault == I_("Y") ) 
			{
				iter.getObject()->getField( ifds::EffectiveDate, tmpEffectiveDate, idDataGroup, false );

				if (DSTCommonFunctions::CompareDates (dstrStopDate, tmpEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER)	
				{
					bExist = true;
					break;
				}
			}
		}

		++iter;
	}
	
	if (!bExist)
	{
		DString idiStr;
		DString formatedStopDate = dstrStopDate;
		DString dstrEndDate;
   
		DSTCommonFunctions::getFormat12319999Date(dstrEndDate);

		if (dstrStopDate != NULL_STRING && dstrStopDate != dstrEndDate)
		{
			DSTCommonFunctions::FormatDate (formatedStopDate);
			addIDITagValue( idiStr, STOP_DATE, formatedStopDate );
			ADDCONDITIONFROMFILEIDI( CND::WARN_MISSING_FUTURE_DEFAULT_SETTL_INSTR, idiStr.c_str());
		}
	}
		
	return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementInstrList.cpp-arc  $
// 
//    Rev 1.6   Jun 27 2007 16:43:06   jankovii
// Incident #930341- Unable to apply account level Settlement Instructions.
// 
//    Rev 1.5   Jun 14 2007 13:37:42   jankovii
// Incident #916658- Warning msg not displayed when no default settlement instr.
// 
//    Rev 1.4   May 04 2007 13:48:04   jankovii
// PET 2321 FN01 - MT54X Default Pay Type.
// 
//    Rev 1.3   Dec 01 2004 13:34:24   aguilaam
// PET1117_FN21: settlement instructions, changed error condition used to get specific message
// 
//    Rev 1.2   Nov 24 2004 13:01:12   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.1   Nov 19 2004 17:32:24   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0   Oct 13 2004 13:47:18   VADEANUM
// Initial revision.
//
