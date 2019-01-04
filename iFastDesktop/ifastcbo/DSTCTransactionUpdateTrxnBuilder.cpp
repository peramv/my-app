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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCTransactionUpdateTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : May 2009
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCTransactionUpdateTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : Create the transaction and put it into the container
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCTransactionUpdateTrxnBuilder.hpp"
#include "transactiondetails.hpp"
#include "pendingtradeDetails.hpp"
#include "transactionupdate.hpp"
#include "transactionlist.hpp"
#include "MFAccount.hpp"
#include "mgmtco.hpp"
#include "pendingtradelist.hpp"
#include <ifastdataimpl\dse_dstc0393_req.hpp>
#include <ifastdataimpl\dse_dstc0393_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADE_AUTHORIZATION;
}
namespace
{
   const I_CHAR* TRADEAUTHORIZATIONSCLASSNAME = I_( "DSTCTransactionUpdateTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
   const I_CHAR* TRANS_NUM = I_( "TransNum" );
}

namespace ifds
{
   // Fields used
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
}

namespace CND
{
   // Conditions used
   extern const I_CHAR* IFASTCBO_CONDITION;
}

//******************************************************************************
void DSTCTransactionUpdateTrxnBuilder::buildTrxnKey( DString& strKey, TransactionUpdate *pTransactionUpdate)
{
   assert( pTransactionUpdate != NULL );
   DString transNum;

   pTransactionUpdate->getField( ifds::TransNum, transNum, BF::HOST, true );
   transNum.strip();

   //build the key
   addIDITagValue (strKey, TRXNTAG::TRADEAUTHORIZATIONTAG, transNum);
}

//******************************************************************************
SEVERITY DSTCTransactionUpdateTrxnBuilder::buildTransactions (DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, TRADEAUTHORIZATIONSCLASSNAME, BUILDTRANSACTIONS );

	buildProcTransactions (workSession, pObj, pTrCont, objActivity);

	buildPendTransactions (workSession, pObj, pTrCont, objActivity);

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTCTransactionUpdateTrxnBuilder::buildProcTransactions (DSTCWorkSession &workSession,
                                                                  BFAbstractCBO* pObj,
                                                                  HostTransactionContainer* pTrCont, 
                                                                  BF_OBJ_ACTIVITY objActivity)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, TRADEAUTHORIZATIONSCLASSNAME, BUILDTRANSACTIONS );

	SEVERITY severity = SEVERE_ERROR;
	TransactionUpdate*	pTransactionUpdate = NULL;
	TransactionList*	pTransactionsList = NULL;
	TransactionDetails* pTransactionDetails = NULL;
	MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);
   
	if( pMFAccount != NULL )
	{
		pTransactionsList = dynamic_cast<TransactionList*>(pMFAccount->getObject( I_( "TransactionHistoryList" ), BF::HOST ) );
     	
		if (pTransactionsList)
		{
			BFObjIter iterTransactionsList (*pTransactionsList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

			while (!iterTransactionsList.end())
			{
				pTransactionDetails = dynamic_cast <TransactionDetails*> (iterTransactionsList.getObject());

				if (pTransactionDetails)
				{
					severity = pTransactionDetails->getTransactionUpdate (pTransactionUpdate, I_(""), I_(""), I_(""), BF::HOST, false);

					if (pTransactionUpdate != NULL  && severity <= WARNING && pTransactionUpdate->hasTransactionUpdates ())
					{
						BFData* request = new BFData( ifds::DSTC0393_REQ );
						BFData* response = new BFData( ifds::DSTC0393_VW );
						DString strTrack,strAvtivity;

						pTransactionUpdate->getTrackActivity(strTrack,strAvtivity);;

						request->setElementValue( ifds::Track, strTrack, false, false );
						request->setElementValue( ifds::Activity, strAvtivity, false, false );

						//fill in the request update, only the part for which the Demographics is responsible
						pTransactionUpdate->getData( *request, BF::HOST );
	       
						DSTCWorkSession::setRunMode( request, objActivity );
						DString strKey;

						//get the string key for the 
						DSTCTransactionUpdateTrxnBuilder::buildTrxnKey( strKey, pTransactionUpdate);

						DString mgmtCoId;
						workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
						request->setElementValue( ifds::CompanyId, mgmtCoId );

						DString	keyTypes, 
								transNum,
								transId,
								recordType,
								authorization,
								settleBatch,
								paymentInfo;
        
						pTransactionUpdate->getField( ifds::TransNum, transNum, BF::HOST, true );
						pTransactionUpdate->getField( ifds::TransId, transId, BF::HOST, true );
						pTransactionUpdate->getField( ifds::PendProcRecordType, recordType, BF::HOST, false );
						pTransactionUpdate->getField( ifds::StcPendTrdAuthorization, authorization, BF::HOST, false );
						pTransactionUpdate->getField( ifds::SettleBatch, settleBatch, BF::HOST, false );
						pTransactionUpdate->getField( ifds::PaymentInfo, paymentInfo, BF::HOST, false );

						request->setElementValue (ifds::TransNum, transNum, false, false );
						request->setElementValue (ifds::TransId, transId, false, false );
						request->setElementValue (ifds::PendProcRecordType, recordType, false, false );
						request->setElementValue (ifds::StcPendTrdAuthorization, authorization, false, false );
						request->setElementValue (ifds::SettleBatch, settleBatch, false, false );
						request->setElementValue (ifds::PaymentInfo, paymentInfo, false, false );

						addIDITagValue( keyTypes, TRANS_NUM, transNum);

						JData *jdata = new JData( DSTC_REQUEST::TRADE_AUTHORIZATION, request, response );
						pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );
					}
				}

				++iterTransactionsList;
			}
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTCTransactionUpdateTrxnBuilder::buildPendTransactions (DSTCWorkSession &workSession,
                                                                  BFAbstractCBO* pObj,
                                                                  HostTransactionContainer* pTrCont, 
                                                                  BF_OBJ_ACTIVITY objActivity)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, TRADEAUTHORIZATIONSCLASSNAME, BUILDTRANSACTIONS );

	SEVERITY severity = SEVERE_ERROR;
	TransactionUpdate*	pTransactionUpdate = NULL;
	PendingTradeList*	pPendingTradeList = NULL;
	PendingTradeDetails* pPendingDetails = NULL;
	MFAccount*          pMFAccount = dynamic_cast<MFAccount*>(pObj);
   
	if( pMFAccount != NULL )
	{
		pPendingTradeList = dynamic_cast<PendingTradeList*>(pMFAccount->getObject( I_( "PendingTradeList" ), BF::HOST ) );

		//pMFAccount->getPendingTradesList (pPendingTradeList, BF::HOST);

		if (pPendingTradeList)
		{
			BFObjIter iterTransactionsList (*pPendingTradeList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

			while (!iterTransactionsList.end())
			{
				pPendingDetails = dynamic_cast <PendingTradeDetails*> (iterTransactionsList.getObject());

				if (pPendingDetails)
				{
					severity = pPendingDetails->getTransactionUpdate (pTransactionUpdate, I_(""), I_(""), I_(""), BF::HOST, false);

					if (pTransactionUpdate != NULL  && severity <= WARNING && pTransactionUpdate->hasTransactionUpdates ())
					{
						BFData* request = new BFData( ifds::DSTC0393_REQ );
						BFData* response = new BFData( ifds::DSTC0393_VW );
						DString strTrack,strAvtivity;

						pTransactionUpdate->getTrackActivity(strTrack,strAvtivity);;

						request->setElementValue( ifds::Track, strTrack, false, false );
						request->setElementValue( ifds::Activity, strAvtivity, false, false );

						//fill in the request update, only the part for which the Demographics is responsible
						pTransactionUpdate->getData( *request, BF::HOST );
	       
						DSTCWorkSession::setRunMode( request, objActivity );
						DString strKey;

						//get the string key for the 
						DSTCTransactionUpdateTrxnBuilder::buildTrxnKey( strKey, pTransactionUpdate);

						DString mgmtCoId;
						workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
						request->setElementValue( ifds::CompanyId, mgmtCoId );

						DString	keyTypes, 
								transNum,
								transId,
								recordType,
								authorization,
								settleBatch;
        
						pTransactionUpdate->getField( ifds::TransNum, transNum, BF::HOST, true );
						pTransactionUpdate->getField( ifds::TransId, transId, BF::HOST, true );
						pTransactionUpdate->getField( ifds::PendProcRecordType, recordType, BF::HOST, false );
						pTransactionUpdate->getField( ifds::StcPendTrdAuthorization, authorization, BF::HOST, false );
						pTransactionUpdate->getField( ifds::SettleBatch, settleBatch, BF::HOST, false );

						request->setElementValue (ifds::TransNum, transNum, false, false );
						request->setElementValue (ifds::TransId, transId, false, false );
						request->setElementValue (ifds::PendProcRecordType, recordType, false, false );
						request->setElementValue (ifds::StcPendTrdAuthorization, authorization, false, false );
						request->setElementValue (ifds::SettleBatch, settleBatch, false, false );

						addIDITagValue( keyTypes, TRANS_NUM, transNum);

						JData *jdata = new JData( DSTC_REQUEST::TRADE_AUTHORIZATION, request, response );
						pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );
					}
				}

				++iterTransactionsList;
			}
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log::   
*/