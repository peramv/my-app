//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use orsuch information
//    may result in civil liabilities. disclosure of 
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctCutOffTimesTrxnBuilder.cpp
// ^CLASS  : AcctCutOffTimesTrxnBuilder
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "AcctCutOffTimesTrxnBuilder.hpp"

#include "AcctCutOffTimes.hpp"
#include "AcctCutOffTimesList.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "Entity.hpp"

#include <ifastdataimpl\dse_dstc0349_req.hpp>
#include <ifastdataimpl\dse_dstc0349_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0349_vw.hpp>

namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest CUT_OFF_TIMES_LIST_UPDATE;
}
namespace
{
	const I_CHAR* CLASSNAME = I_( "AcctCutOffTimesTrxnBuilder" );
	const I_CHAR * const ACCTLEVEL		= I_( "01" );    
	const I_CHAR * const NETSENDERLEVEL	= I_( "02" );    
	const I_CHAR * const BROKERLEVEL	= I_( "03" );    
}

namespace CND
{
	extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
	extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
	extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

//******************************************************************************
SEVERITY AcctCutOffTimesTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
	SEVERITY severity = SEVERE_ERROR;
	MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);
	AcctCutOffTimesList *pBrokerCutOffList = dynamic_cast<AcctCutOffTimesList*>(pObj);
	
	if(pMFaccount)
	{
		AcctCutOffTimesList *pAcctCutOffTimesList = NULL;
		DString dstAccountNum, dstTrnKey, dstKeyTypes;
		pMFaccount->getField(ifds::AccountNum, dstAccountNum, BF::HOST, true);
		addIDITagValue(dstTrnKey, I_("AcctCutOffTimes"), dstAccountNum.stripLeading('0').strip() );
		addIDITagValue(dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

		HostTransactionContainerIterator iterTrxnContList(pTrCont);

		iterTrxnContList.walkStrKey(dstTrnKey);
		iterTrxnContList.walkTrxnGroup(NO_GROUP);
		iterTrxnContList.walkTrxnSubType(0);

		if(pMFaccount->getAcctCutOffTimesList(pAcctCutOffTimesList, BF::HOST, false) <= WARNING && pAcctCutOffTimesList)
		{
			BFData *pDataReq = NULL;
			BFData *pDataRes = NULL;
			
			BFObjIter iter(*pAcctCutOffTimesList, BF::HOST);
			AcctCutOffTimes* pAcctCutOffTimes = NULL;
			
			iter.begin();
			while(!iter.end())
			{
				pAcctCutOffTimes = dynamic_cast<AcctCutOffTimes*>(iter.getObject());
				
				if(iter.hasTransactionUpdates())
				{
					iterTrxnContList.begin();
					
					if(iterTrxnContList.end())
					{
						pDataReq = new BFData(ifds::DSTC0349_REQ);
						pDataRes = new BFData(ifds::DSTC0349_VW);
						
						DString strTrack, strActivity;
						pAcctCutOffTimesList->getTrackActivity(strTrack, strActivity);         
						pDataReq->setElementValue(ifds::Track, strTrack, false, false);
						pDataReq->setElementValue(ifds::Activity, strActivity, false, false);
						
						DString mgmtCoId;
						workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

						pDataReq->setElementValue(ifds::CompanyId, mgmtCoId);
						pDataReq->setElementValue(ifds::AccountNum, dstAccountNum);

						JData *jdata = new JData(DSTC_REQUEST::CUT_OFF_TIMES_LIST_UPDATE, pDataReq, pDataRes);
						pTrCont->addTransaction(dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes);
					}
					else
					{
						pDataRes = (*iterTrxnContList)->getRequestDataObject();
					}

					BFData repeat(ifds::DSTC0349_REQRepeat_Record);
					pAcctCutOffTimes->getData(repeat, BF::HOST);
					DSTCWorkSession::setRunMode(&repeat, iter.getKey().getActivity());
					
					pDataReq->addRepeat(repeat);
					DString dstRepeats = DString::asString(pDataReq->getRepeatCount());
					pDataReq->setElementValue(ifds::RepeatCount, dstRepeats);
				}
				++iter;
			}
		}
	}
	else if(pBrokerCutOffList && pBrokerCutOffList->getCutOffLevel() == BROKERLEVEL)
	{
		DString dstBrokerCode, dstTrnKey, dstKeyTypes;

		dstBrokerCode = pBrokerCutOffList->getBrokerCode();
		
		HostTransactionContainerIterator iterTrxnContList(pTrCont);

		iterTrxnContList.walkStrKey(dstTrnKey);
		iterTrxnContList.walkTrxnGroup(NO_GROUP);
		iterTrxnContList.walkTrxnSubType(0);

		BFData *pDataReq = NULL;
		BFData *pDataRes = NULL;
			
		BFObjIter iter(*pBrokerCutOffList, BF::HOST);
		AcctCutOffTimes* pBrokerCutOffTimes = NULL;
			
		iter.begin();
		while(!iter.end())
		{
			pBrokerCutOffTimes = dynamic_cast<AcctCutOffTimes*>(iter.getObject());
				
			if(iter.hasTransactionUpdates())
			{
				iterTrxnContList.begin();
					
				if(iterTrxnContList.end())
				{
					pDataReq = new BFData(ifds::DSTC0349_REQ);
					pDataRes = new BFData(ifds::DSTC0349_VW);
						
					DString strTrack, strActivity;
					pBrokerCutOffList->getTrackActivity(strTrack, strActivity);         
					pDataReq->setElementValue(ifds::Track, strTrack, false, false);
					pDataReq->setElementValue(ifds::Activity, strActivity, false, false);
						
					DString mgmtCoId;
					workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

					pDataReq->setElementValue(ifds::CompanyId, mgmtCoId);
					pDataReq->setElementValue(ifds::BrokerCode, dstBrokerCode);

					JData *jdata = new JData( DSTC_REQUEST::CUT_OFF_TIMES_LIST_UPDATE, pDataReq, pDataRes );
					pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
				}
				else
				{
					pDataRes = (*iterTrxnContList)->getRequestDataObject();
				}

				BFData repeat(ifds::DSTC0349_REQRepeat_Record);
				pBrokerCutOffTimes->getData(repeat, BF::HOST);
				DSTCWorkSession::setRunMode(&repeat, iter.getKey().getActivity());
					
				pDataReq->addRepeat(repeat);
				DString dstRepeats = DString::asString(pDataReq->getRepeatCount());
				pDataReq->setElementValue(ifds::RepeatCount, dstRepeats);
			}
			++iter;
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCutOffTimesTrxnBuilder::buildTransactions1(DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
	SEVERITY severity = SEVERE_ERROR;
	Entity* entity = dynamic_cast<Entity*>(pObj);
	DString dstEntityId;

	if(entity != NULL)
	{
		DString dstrEntityId, dstTrnKey, dstKeyTypes;

		entity->getEntityId(dstrEntityId);

		AcctCutOffTimesList *pCutOffTimesList = NULL;
	
		addIDITagValue(dstTrnKey, I_("AcctCutOffTimes"), dstrEntityId.stripLeading('0').strip());
		addIDITagValue(dstKeyTypes, KEYTYPES::ENTITYID, dstrEntityId);

		HostTransactionContainerIterator iterTrxnContList(pTrCont);

		iterTrxnContList.walkStrKey(dstTrnKey);
		iterTrxnContList.walkTrxnGroup(NO_GROUP);
		iterTrxnContList.walkTrxnSubType(0);

		if(entity->getNetworkSenderCutOffTimesList(pCutOffTimesList, BF::HOST, false) <= WARNING && pCutOffTimesList)
		{
			BFData *pDataReq = NULL;
			BFData *pDataRes = NULL;

			BFObjIter iter(*pCutOffTimesList, BF::HOST);
			AcctCutOffTimes* pAcctCutOffTimes = NULL;

			iter.begin();
			while(!iter.end())
			{
				pAcctCutOffTimes = dynamic_cast<AcctCutOffTimes*>( iter.getObject());

				if(iter.hasTransactionUpdates())
				{
					iterTrxnContList.begin();

					if(iterTrxnContList.end())
					{
						pDataReq = new BFData(ifds::DSTC0349_REQ);
						pDataRes = new BFData(ifds::DSTC0349_VW);

						DString strTrack, strActivity;

						pCutOffTimesList->getTrackActivity(strTrack, strActivity);         
						pDataReq->setElementValue(ifds::Track, strTrack, false, false);
						pDataReq->setElementValue(ifds::Activity, strActivity, false, false);

						DString mgmtCoId;
						workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

						pDataReq->setElementValue(ifds::CompanyId, mgmtCoId);
						pDataReq->setElementValue(ifds::EntityId, dstrEntityId);

						JData *jdata = new JData(DSTC_REQUEST::CUT_OFF_TIMES_LIST_UPDATE, pDataReq, pDataRes);
						pTrCont->addTransaction(dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes);
					}
					else
					{
						pDataRes = (*iterTrxnContList)->getRequestDataObject();
					}

					BFData repeat(ifds::DSTC0349_REQRepeat_Record);
					pAcctCutOffTimes->getData(repeat, BF::HOST);
					DSTCWorkSession::setRunMode(&repeat, iter.getKey().getActivity());

					pDataReq->addRepeat(repeat);
					DString dstRepeats = DString::asString(pDataReq->getRepeatCount());
					pDataReq->setElementValue(ifds::RepeatCount, dstRepeats);
				}
				++iter;
			}
		}
	}
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCutOffTimesTrxnBuilder.cpp-arc  $
// 
//    Rev 1.2   01 May 2007 13:55:34   popescu
// Incident: ? (got raised by Lux - C.Rigot) account# is invalid for acct cut off times trxn sent, and acct category
// 
//    Rev 1.1   Jul 21 2006 14:02:44   jankovii
// PET 2192 FN02 - Dealings-Sender Cut-Off Time.
// 
//    Rev 1.0   Jul 05 2005 17:17:22   hernando
// Initial revision.
