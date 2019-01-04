//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : TradeSettlementLocationsList.cpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// ^CLASS    : TradeSettlementLocationsList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "TradeSettlementLocationsList.hpp"
#include "TradeSettlementLocations.hpp"
#include "SysLvlSettlementInstrList.hpp"
#include "SysLvlSettlementInstr.hpp"

#include <ifastdataimpl\dse_dstc0269_vw.hpp>
#include <ifastdataimpl\dse_dstc0269_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0269_req.hpp>
#include <ifastdataimpl\dse_dstc0397_req.hpp>
#include <ifastdataimpl\dse_dstc0397_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0397_vw.hpp>

#include "mgmtco.hpp"


namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest MULTI_SETTLEMENT_LOCATIONS_INQUIRY;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "TradeSettlementLocationsList");  
}

namespace ifds
{   
	extern CLASS_IMPORT const BFTextFieldId TransId;
	extern CLASS_IMPORT const BFTextFieldId Active;
	extern CLASS_IMPORT const BFDecimalFieldId Amount;
}

namespace CND
{ 	
	extern const long ERR_DUPLICATE_RECORD;	
	extern const long ERR_TOTAL_AMT_ON_SETTLINSTR;
}

//*********************************************************************************
TradeSettlementLocationsList::TradeSettlementLocationsList (BFAbstractCBO &parent) : MFCanBFCbo (parent),
_idDataGroup (BF::HOST),
_bSetFieldsReadOnly (false),
m_TotalAmount (0),
m_TradeAmount (NULL_STRING),
m_TransId (NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	setObjectAsList();
}

//*********************************************************************************
TradeSettlementLocationsList::~TradeSettlementLocationsList()
{
	TRACE_DESTRUCTOR (CLASSNAME);
}

//*********************************************************************************

//*********************************************************************************
SEVERITY TradeSettlementLocationsList::init (const DString &transNum,
	                                         const BFDataGroupId &idDataGroup,
                                             bool bSetFieldsReadOnly, /*=false*/
                                             const DString &dstrTrack, /*=I_("N")*/
                                             const DString &dstrPageName /*=NULL_STRING*/)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	_idDataGroup = idDataGroup;
	_bSetFieldsReadOnly = bSetFieldsReadOnly;
	 
	DString mgmtCoIdOut;	
	BFData requestData (ifds::DSTC0397_REQ);
		
	requestData.setElementValue (ifds::TransNum, transNum);
	requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	requestData.setElementValue (ifds::Track, dstrTrack);
	requestData.setElementValue (ifds::Activity, dstrPageName);
	
	ReceiveData (DSTC_REQUEST::MULTI_SETTLEMENT_LOCATIONS_INQUIRY, requestData, ifds::DSTC0397_VW, DSTCRequestor (getSecurity(), false, false));
	   
	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TradeSettlementLocationsList::initNew (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

	return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY TradeSettlementLocationsList::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ));
	   
	pObjOut =  new TradeSettlementLocations( *this );
	((TradeSettlementLocations* )pObjOut )->init (data, _idDataGroup, _bSetFieldsReadOnly);
	   
	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TradeSettlementLocationsList::doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
	  
	TradeSettlementLocations* pTradeSettlementLocations = new TradeSettlementLocations (*this);

	pTradeSettlementLocations->initNew (idDataGroup, _bSetFieldsReadOnly);

	pBase = pTradeSettlementLocations;
	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeSettlementLocationsList::checkDuplicate (const TradeSettlementLocations *pTradeSettlementLocationToCheck, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );   	
	
	DString dstrSettlLocCodeToCheck;
	
	pTradeSettlementLocationToCheck->getField( ifds::SettleLocCode, dstrSettlLocCodeToCheck, idDataGroup );

	bool bHasDuplicate = false;
	
	//check first whether in the list (in memory) we have a duplicate
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();

	while (!iter.end())
	{
		TradeSettlementLocations *pTradeSettlementLocation = dynamic_cast<TradeSettlementLocations*>(iter.getObject());
		// Don't check against itself
		if ( pTradeSettlementLocation != pTradeSettlementLocationToCheck )
		{
			DString dstrCurrentSettlLocCode;

			pTradeSettlementLocation->getField( ifds::SettleLocCode, dstrCurrentSettlLocCode, idDataGroup );
			
			if (dstrCurrentSettlLocCode  == dstrSettlLocCodeToCheck )
			{
				bHasDuplicate = true;
				break;
			}
		}
		++iter;
	}

	if ( bHasDuplicate )
	{
		ADDCONDITIONFROMFILE(CND::ERR_DUPLICATE_RECORD);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeSettlementLocationsList::getMasterList (DString &settleLocList, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterList" ) );   	
	
	SysLvlSettlementInstrList *pSysLvlSettlementInstrList = NULL;
   
	if (!m_MasterSettleLocsList.empty ())
	{
		settleLocList = m_MasterSettleLocsList;
		return GETCURRENTHIGHESTSEVERITY();
	}
	getWorkSession().getSettlementLocationSysLvlList( pSysLvlSettlementInstrList, idDataGroup, true );
   
	while (pSysLvlSettlementInstrList && pSysLvlSettlementInstrList->doMoreRecordsExist())
	{
		pSysLvlSettlementInstrList->getMore ();
	}

	if (pSysLvlSettlementInstrList)
	{
		DString dstrSettleLocationCode, dstrSettleLocationDesc, dstrActive;
      
		BFObjIter bfObjIter (*pSysLvlSettlementInstrList, idDataGroup, BFObjIter::ITERTYPE::NON_DELETED);
		
		while(!bfObjIter.end())
		{
			bfObjIter.getObject()->getField( ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup, false );
			bfObjIter.getObject()->getField( ifds::SettleLocationDesc, dstrSettleLocationDesc, idDataGroup, false );
			bfObjIter.getObject()->getField( ifds::Active, dstrActive, idDataGroup, false );
			
			dstrSettleLocationCode.stripLeading().stripTrailing();
			dstrSettleLocationDesc.stripLeading().stripTrailing();
			dstrActive.stripAll().upperCase();
			
			if( dstrActive == I_("Y") )
			{	
				m_MasterSettleLocsList += dstrSettleLocationCode + I_("=") + dstrSettleLocationCode + I_(" - ") +dstrSettleLocationDesc + I_(";");
			}
			
			++bfObjIter;
		}
	}

	settleLocList = m_MasterSettleLocsList;

	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TradeSettlementLocationsList::doValidateAll (const BFDataGroupId &idDataGroup, 
                                                      long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
	  
	I_CHAR *sTradeAmount;
	getParent ()->getField (ifds::Amount, m_TradeAmount, idDataGroup);
    m_TotalAmount = 0;
	double dTradeAmount = wcstod (m_TradeAmount.c_str(), &sTradeAmount); 

	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();

	while (!iter.end())
	{
		TradeSettlementLocations *pTradeSettlementLocations = dynamic_cast <TradeSettlementLocations*> (iter.getObject());
	
		if (pTradeSettlementLocations)
	    {
			DString dstrAmount;
			pTradeSettlementLocations->getField (ifds::TransClrSettlAmt, dstrAmount, idDataGroup, false);
			dstrAmount.strip().stripAll(I_CHAR(','));
	
			I_CHAR *sAmount;
			double dAmount = wcstod (dstrAmount.c_str(), &sAmount); 
	        m_TotalAmount += dAmount;
	        ++iter;
		}
	}
	   
	if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
	{
		if (m_TotalAmount != dTradeAmount)
		{
			ADDCONDITIONFROMFILE (CND::ERR_TOTAL_AMT_ON_SETTLINSTR);
		}
	}     
		
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
/* $Log:: 
*/
