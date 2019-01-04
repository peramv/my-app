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
//    Copyright 2005 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : AcctCutOffTimesList.cpp
//
//********************************************************************************
#include "stdafx.h"
#include "AcctCutOffTimesList.hpp"
#include "AcctCutOffTimes.hpp"
#include <ifastdataimpl\dse_dstc0348_vw.hpp>
#include <ifastdataimpl\dse_dstc0348_req.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest CUT_OFF_TIMES_LIST;
}

namespace
{
	const I_CHAR * const CLASSNAME		= I_("AcctCutOffTimesList");
   	const I_CHAR * const ACCTLEVEL		= I_("01");    
	const I_CHAR * const NETSENDERLEVEL	= I_("02");    
	const I_CHAR * const BROKERLEVEL	= I_("03");    
}

namespace CND
{
	extern const long ERR_CUT_OFF_TIME_DUPLICATE;
}

//******************************************************************************

AcctCutOffTimesList::AcctCutOffTimesList(BFAbstractCBO &parent)
: MFCanBFCbo(parent), m_requestData(ifds::DSTC0348_REQ)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	setObjectAsList();
}

//******************************************************************************

AcctCutOffTimesList::~AcctCutOffTimesList()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************

SEVERITY AcctCutOffTimesList::init()
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init()"));
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctCutOffTimesList::init(const DString& AccountNum,
								   const DString& EntityId,
								   const DString& BrokerCode,
                                   const DString& dstrTrack,
                                   const DString& dstrPageName
                                 )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init(...)" ));
	
	DString mgmtCoIdOut;
	m_requestData.setElementValue(ifds::NextKey, NULL_STRING);
	m_requestData.setElementValue(ifds::Track, dstrTrack);
	m_requestData.setElementValue(ifds::Activity, dstrPageName);
	m_requestData.setElementValue(ifds::AccountNum, AccountNum);
	m_requestData.setElementValue(ifds::EntityId, EntityId);
	m_requestData.setElementValue(ifds::BrokerCode, BrokerCode);
	m_requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   
	/* Check level of cut-off*/
	if(AccountNum != NULL_STRING)
		dstrCutOffLevel = ACCTLEVEL;
	else if(EntityId != NULL_STRING)
		dstrCutOffLevel = NETSENDERLEVEL;
	else if(BrokerCode != NULL_STRING)
	{
		dstrCutOffLevel = BROKERLEVEL;
		dstrBrokerCode = BrokerCode;
	}
	
	ReceiveData(DSTC_REQUEST::CUT_OFF_TIMES_LIST, m_requestData, ifds::DSTC0348_VW, DSTCRequestor(getSecurity(), false /*allResults*/, false /*noDataIsErrorCondition*/), true /*InsertLast*/);
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

DString AcctCutOffTimesList::getBrokerCode()
{
	return dstrBrokerCode;
}

//******************************************************************************

DString AcctCutOffTimesList::getCutOffLevel()
{
	return dstrCutOffLevel;
}

//******************************************************************************

SEVERITY AcctCutOffTimesList::getMore()
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

	if(doMoreRecordsExist())
	{
		const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> (getSecurity());
		ReceiveData(DSTC_REQUEST::CUT_OFF_TIMES_LIST, m_requestData, ifds::DSTC0348_VW, DSTCRequestor(getSecurity(), false) );
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************

SEVERITY AcctCutOffTimesList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
	pObjOut = new AcctCutOffTimes( *this, dstrCutOffLevel );
	((AcctCutOffTimes*) pObjOut)->init( data );
	return( GETCURRENTHIGHESTSEVERITY() );
}

//*************************************************************************************

SEVERITY AcctCutOffTimesList::doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
	AcctCutOffTimes *pAcctCutOffTimes = new AcctCutOffTimes( *this, dstrCutOffLevel );

	pAcctCutOffTimes->init( idDataGroup );
	pBase = pAcctCutOffTimes;
return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
// This will catch duplicates that came from the back-end. :)
SEVERITY AcctCutOffTimesList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

	// Check for duplicates
	std::set< DString > setDuplicates;
	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	while( !iter.end() )
	{
		DString CutOffTimeType, FundGroup, FundCode, ClassCode;
		iter.getObject()->getField(ifds::CutOffTimeType, CutOffTimeType, idDataGroup, false);
		iter.getObject()->getField(ifds::FundGroup, FundGroup, idDataGroup, false);
		iter.getObject()->getField(ifds::FundCode, FundCode, idDataGroup, false);
		iter.getObject()->getField(ifds::ClassCode, ClassCode, idDataGroup, false);
		DString dstrEntry = CutOffTimeType.strip().upperCase() + FundGroup.strip().upperCase() +
							FundCode.strip().upperCase() + ClassCode.strip().upperCase();

		if( !setDuplicates.insert( dstrEntry ).second )
		{
			DString CutOffTimeTypeDesc, FundGroupDesc, FundCodeDesc, ClassCodeDesc;
			iter.getObject()->getField(ifds::CutOffTimeType, CutOffTimeTypeDesc, idDataGroup, true );
			iter.getObject()->getField(ifds::FundGroup, FundGroupDesc, idDataGroup, true );
			iter.getObject()->getField(ifds::FundCode, FundCodeDesc, idDataGroup, true );
			iter.getObject()->getField(ifds::ClassCode, ClassCodeDesc, idDataGroup, true );

			DString dstrParameter = CutOffTimeTypeDesc.strip().upperCase() + I_(", ");

			if (!FundGroupDesc.empty ())
			dstrParameter += FundGroupDesc.strip().upperCase();
			else if (!FundCodeDesc.empty () && !ClassCodeDesc.empty ())
			{
			dstrParameter +=  FundCodeDesc.strip().upperCase() + I_(", ");
			dstrParameter +=  ClassCodeDesc.strip().upperCase();
			}

			DString dstrTag;
			addIDITagValue( dstrTag, I_("CODE"), dstrParameter );
			ADDCONDITIONFROMFILEIDI( CND::ERR_CUT_OFF_TIME_DUPLICATE, dstrTag );
			break;
		}
		++iter; 
	}

	return (GETCURRENTHIGHESTSEVERITY());
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCutOffTimesList.cpp-arc  $
// 
//    Rev 1.3   Jul 21 2006 14:07:40   jankovii
// PET 2192 FN02 - Dealings-Sender Cut-Off Time.
// 
//    Rev 1.2   Jul 25 2005 15:52:28   hernando
// PET1250 FN01 - Added init() as a stub for new accounts.
// 
//    Rev 1.1   Jul 07 2005 15:04:48   hernando
// PET1250 FN01 - Revised the Condition display.
// 
//    Rev 1.0   Jul 05 2005 17:17:06   hernando
// Initial revision.
