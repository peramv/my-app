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
// ^FILE   : DSTCTradeAuthorizaitonTrxnBuilder.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : October 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCTradeAuthorizaitonTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : Create the transaction and put it into the container
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCTradeAuthorizaitonTrxnBuilder.hpp"
#include "dstcmfshareholdertrxnbuilder.hpp"
#include "shareholder.hpp"
#include "tradeauthorization.hpp"
#include "MFAccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0393_req.hpp>
#include <ifastdataimpl\dse_dstc0393_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADE_AUTHORIZATION;
}
namespace
{
   const I_CHAR* TRADEAUTHORIZATIONSCLASSNAME = I_( "DSTCTradeAuthorizaitonTrxnBuilder" );
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
void DSTCTradeAuthorizaitonTrxnBuilder::buildTrxnKey( DString& strKey, TradeAuthorization *pTradeAuthorization)
{
   assert( pTradeAuthorization != NULL );
   DString transNum;

   pTradeAuthorization->getField( ifds::TransNum, transNum, BF::HOST, true );
   transNum.strip();

   //build the key
   addIDITagValue (strKey, TRXNTAG::TRADEAUTHORIZATIONTAG, transNum);
}

//******************************************************************************
SEVERITY DSTCTradeAuthorizaitonTrxnBuilder::buildTransactions (DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, TRADEAUTHORIZATIONSCLASSNAME, BUILDTRANSACTIONS );

	SEVERITY severity = SEVERE_ERROR;
	TradeAuthorization* pTradeAuthorization = NULL;
	
	MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);
   
	if( pMFAccount != NULL )
	{
		severity = pMFAccount->getTradeAuthorization (pTradeAuthorization, BF::HOST);
     	
		if (pTradeAuthorization != NULL  && severity <= WARNING&& pTradeAuthorization->hasTransactionUpdates ())
		{
			
			BFData* request = new BFData( ifds::DSTC0393_REQ );
			BFData* response = new BFData( ifds::DSTC0393_VW );
			DString strTrack,strAvtivity;

			pTradeAuthorization->getTrackActivity(strTrack,strAvtivity);;

			request->setElementValue( ifds::Track, strTrack, false, false );
			request->setElementValue( ifds::Activity, strAvtivity, false, false );

			//fill in the request update, only the part for which the Demographics is responsible
			pTradeAuthorization->getData( *request, BF::HOST );
	       
			DSTCWorkSession::setRunMode( request, objActivity );
			DString strKey;

			//get the string key for the 
			DSTCTradeAuthorizaitonTrxnBuilder::buildTrxnKey( strKey, pTradeAuthorization);

			DString mgmtCoId;
			workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
			request->setElementValue( ifds::CompanyId, mgmtCoId );

			DString	keyTypes, 
					transNum,
					transId,
					recordType,
					authorization;
        
			pTradeAuthorization->getField( ifds::TransNum, transNum, BF::HOST, true );
			pTradeAuthorization->getField( ifds::TransId, transId, BF::HOST, true );
			pTradeAuthorization->getField( ifds::PendProcRecordType, recordType, BF::HOST, false );
			pTradeAuthorization->getField( ifds::StcPendTrdAuthorization, authorization, BF::HOST, false );
        
			request->setElementValue (ifds::TransNum, transNum, false, false );
			request->setElementValue (ifds::TransId, transId, false, false );
			request->setElementValue (ifds::PendProcRecordType, recordType, false, false );
			request->setElementValue (ifds::StcPendTrdAuthorization, authorization, false, false );

			addIDITagValue( keyTypes, TRANS_NUM, transNum);

			JData *jdata = new JData( DSTC_REQUEST::TRADE_AUTHORIZATION, request, response );
			pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log::   
*/