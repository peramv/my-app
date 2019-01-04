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
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : DSTCAcctRegDetailsTrxnBuilder.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : DSTCAcctRegDetailsTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCAcctRegDetailsTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "AcctRegDetailsList.hpp"
#include "AcctRegDetails.hpp"
#include "MFAccount.hpp"
#include "DSTCWorkSession.hpp"
#include "MgmtCo.hpp"

#include <ifastdataimpl\dse_dstc0452_req.hpp>
#include <ifastdataimpl\dse_dstc0452_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0452_vw.hpp>


namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest ACCT_REG_DETAILS_UPDATE;
}

namespace
{
	const I_CHAR* CLASSNAME = I_("DSTCAcctRegDetailsTrxnBuilder");
	const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ReqIndiciaSearch;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace KEYTYPES
{
	extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

extern BF_OBJ_TYPE OBJ_TYPE_ACCT_REG_DETAILS_LIST;


//******************************************************************************
void DSTCAcctRegDetailsTrxnBuilder::buildTrxnKey(DString& dstrKey, MFAccount *pMFAccount) 
{
	DString dstrAccountNum;

	pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
	dstrAccountNum.stripLeading( '0' );
	dstrAccountNum.strip();

	//build the key
	addIDITagValue( dstrKey, TRXNTAG::ACCTREGDETAILS, dstrAccountNum );

	addIDITagValue( dstrKey, TRXNTAG::ACCTTAG, dstrAccountNum );
}


//******************************************************************************
SEVERITY DSTCAcctRegDetailsTrxnBuilder::buildTransactions(DSTCWorkSession &workSession,
														  BFAbstractCBO *pObj, 
														  HostTransactionContainer *pTrCont, 
														  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

	MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);
	AcctRegDetailsList *pAcctRegDetailsList = NULL;
	DString dstrKey,dstrAccountNum;
	int count = 0;

	if(pMFaccount)
	{
		DString dstAccountNum, dstTrnKey, dstKeyTypes;

		pMFaccount->getField (ifds::AccountNum, dstAccountNum, BF::HOST, true);

		if (pMFaccount->getAcctRegDetailsList(pAcctRegDetailsList, BF::HOST) <= WARNING && pAcctRegDetailsList && pAcctRegDetailsList->hasTransactionUpdates())
		{
			BFData *pDataReq = NULL;
			BFData *pDataRes = NULL;

			BFObjIter iter( *pAcctRegDetailsList, BF::HOST );
			AcctRegDetails* pAcctRegDetails = NULL;

			DSTCAcctRegDetailsTrxnBuilder::buildTrxnKey( dstTrnKey, pMFaccount );

			HostTransactionContainerIterator iterTrxnContList( pTrCont );

			iterTrxnContList.walkStrKey( dstTrnKey );
			iterTrxnContList.walkTrxnGroup( NO_GROUP );
			iterTrxnContList.walkTrxnSubType( 0 );

			iterTrxnContList.begin();

			//fill in the fixed area
			if( iterTrxnContList.end() )
			{
				TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_ACCOUNT_REGULATORY_DETAILS : UPDATE_ACCOUNT_REGULATORY_DETAILS;

				pDataReq = new BFData( ifds::DSTC0452_REQ );
				pDataRes = new BFData( ifds::DSTC0452_VW );

				DString strTrack, strActivity;

				pAcctRegDetailsList->getTrackActivity(strTrack,strActivity);         
				pDataReq->setElementValue( ifds::Track, strTrack, false, false );
				pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

				//fill in the request update
				DString mgmtCoId;
				workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

            DString reqIndiciaSearch;
            pAcctRegDetailsList->getField( ifds::ReqIndiciaSearch, reqIndiciaSearch, BF::HOST,false);
            reqIndiciaSearch.strip().upperCase();

				pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
				pDataReq->setElementValue( ifds::AccountNum, dstAccountNum );
            pDataReq->setElementValue( ifds::ReqIndiciaSearch, reqIndiciaSearch );

				dstAccountNum.stripLeading( '0' );
				dstAccountNum.strip();

				addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

				JData *jdata = new JData( DSTC_REQUEST::ACCT_REG_DETAILS_UPDATE, pDataReq, pDataRes );
				pTrCont->addTransaction( dstTrnKey, jdata, objActivity, trxnType, dstKeyTypes );
			}
			else
				pDataRes = (*iterTrxnContList)->getRequestDataObject();

			//iter.begin();

         //if(!iter.end())
         //{
			//while( !iter.end() )
			//{
			//	//if( iter.hasTransactionUpdates() )
			//	{//
			//		count++;
			//		pAcctRegDetails = dynamic_cast<AcctRegDetails*>( iter.getObject() );

			//		//create a repeat for the request and fill it in
			//		BFData repeat( ifds::DSTC0452_REQRepeat_Record);

			//		//fill in the request update
			//		/pAcctRegDetails->getData( repeat, BF::HOST );

			//		//set the RunMode field 
			//		DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity() );

			//		//add the lDataRepeat to the request
			//		pDataReq->addRepeat( repeat );
			//		DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
			//		pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
			//	}
			//	++iter;
			//}
         //}
         //else
         //{
            /* we would have one dummy record to retain old flow 
			 Currently, there will be all dummy sending to view as it 
			 is not necessary to send anything for modification. */
            BFData repeat( ifds::DSTC0452_REQRepeat_Record);

            DString currBuzDay;
            workSession.getOption(ifds::CurrBusDate, currBuzDay, BF::HOST, false);


            //fill in the request update
            repeat.setElementValue( ifds::AcctRegDetailsUUID, NULL_STRING);
            repeat.setElementValue( ifds::EffectiveDate, currBuzDay);
            repeat.setElementValue( ifds::StopDate, I_("12319999"));
            repeat.setElementValue( ifds::FICategory,  NULL_STRING);
            repeat.setElementValue( ifds::FinInstRegDetlUUID, NULL_STRING);
            repeat.setElementValue( ifds::ComplyAction,  NULL_STRING);
            repeat.setElementValue( ifds::Consented, I_("N"));
            repeat.setElementValue( ifds::VersionAcctRegDetl,  NULL_STRING);
            repeat.setElementValue( ifds::Regulatory,  NULL_STRING);

            //set the RunMode field 
            repeat.setElementValue( ifds::RunMode, I_("M"));

            //add the lDataRepeat to the request
            pDataReq->addRepeat( repeat );
            pDataReq->setElementValue( ifds::RepeatCount, DString::asString( 1 ), false, false );
         //}
		} 
	}


	return GETCURRENTHIGHESTSEVERITY();
}
