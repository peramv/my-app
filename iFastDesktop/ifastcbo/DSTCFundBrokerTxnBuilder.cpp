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
// ^FILE   : DSTCFundBrokerTrxnBuilder.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : June 3,2002
//
// ^CLASS    : DSTCFundBrokerTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCFundBrokerTxnBuilder.hpp"
#include "DSTCFundBrokerFeeTxnBuilder.hpp"
#include "DSTCFundBrokerSettlementInstrTrxnBuilder.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0320_req.hpp>
#include <ifastdataimpl\dse_dstc0320_vw.hpp>
#include <ifastdataimpl\dse_dstc0320_reqrepeat_record.hpp>

#include "FundBrokerList.hpp"
#include "FundBroker.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_BROKER_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCFundBrokerTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{

}

int DSTCFundBrokerTrxnBuilder::buildIndex = 0;
//******************************************************************************
void DSTCFundBrokerTrxnBuilder::buildTrxnKey( DString& strKey, FundBrokerList* pFundBrokerList )
{  
   
   BFObjIter iter( *pFundBrokerList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
   DString dstrEntityId;
   while( !iter.end() )
   {
      FundBroker* pFundBroker = dynamic_cast<FundBroker* >(iter.getObject() );

      pFundBroker->getField(ifds::EntityId,dstrEntityId,BF::HOST,false);
      dstrEntityId.strip();
      if(dstrEntityId != NULL_STRING)
         addIDITagValue( strKey, TRXNTAG::ENTITYIDTAG, dstrEntityId );

      pFundBroker->getField(ifds::Contact1EntityID,dstrEntityId,BF::HOST,false);
      dstrEntityId.strip();
      if(dstrEntityId != NULL_STRING)
         addIDITagValue( strKey, TRXNTAG::ENTITYIDTAG, dstrEntityId );

      pFundBroker->getField(ifds::Contact2EntityID,dstrEntityId,BF::HOST,false);
      dstrEntityId.strip();
      if(dstrEntityId != NULL_STRING)
         addIDITagValue( strKey, TRXNTAG::ENTITYIDTAG, dstrEntityId );

      ++iter;
   }   
}

//******************************************************************************
SEVERITY DSTCFundBrokerTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

    SEVERITY severity = SEVERE_ERROR;
    bool first_time = true;
    FundBrokerList* pFundBrokerList = dynamic_cast< FundBrokerList* >(pObj);

    DString tmp;
    BFData* pDataReq = NULL;
    BFData* pDataRes = NULL;
    unsigned long cRepeats = 0;   

    DString keyString;
    addIDITagValue( keyString, TRXNTAG::FUNDBROKERTAG, DString::asString( buildIndex++ ) );

	//walk through BrokerAMSList
    BFObjIter bfIter( *pFundBrokerList, BF::HOST );
	 bfIter.begin();
    while( !bfIter.end() )
    {
       FundBroker* pFundBroker = dynamic_cast< FundBroker* >( bfIter.getObject() );
       BF_OBJ_ACTIVITY lObjActivity = bfIter.getKey().getActivity();	

		 if( lObjActivity == OBJ_ACTIVITY_ADDED || lObjActivity == OBJ_ACTIVITY_DELETED
                || pFundBroker->hasTransactionUpdates() )
       {	         
          //define an iterator on the HostTransactionContainer
	      HostTransactionContainerIterator iterTrxnContList( pTrCont );
	      //set filter to look for BrokerAMS fixed area
	      iterTrxnContList.walkStrKey( keyString );
	      //the trxn hasn't been handled yet, no group and sub type set,
	      iterTrxnContList.walkTrxnGroup( NO_GROUP );
	      iterTrxnContList.walkTrxnSubType( 0 );
	      iterTrxnContList.begin();

	      if( iterTrxnContList.end() )
	      // Fixed Area either does not exists, so create a new one
	      {
		      pDataReq   = new BFData( ifds::DSTC0320_REQ );
		      pDataRes   = new BFData( ifds::DSTC0320_VW );

		      pDataReq->setElementValue( ifds::Track, I_("N") );
		      pDataReq->setElementValue( ifds::Activity, I_("") );

		      DString mgmtCoId;
		      workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
		      pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

		      DString dstrKeyTypes;
            DSTCFundBrokerTrxnBuilder::buildTrxnKey( dstrKeyTypes, pFundBrokerList );
		      //add the transaction to the container;
		      JData *jdata = new JData( DSTC_REQUEST::FUND_BROKER_LIST_UPDATE, pDataReq, pDataRes );
		      pTrCont->addTransaction( keyString, jdata, lObjActivity, NOT_PERSISTENT, dstrKeyTypes );
	      }
	      else
	      {
		      pDataReq = (*iterTrxnContList)->getRequestDataObject();
	      }

            //create a repeat for the request and filled in
            BFData repeat( ifds::DSTC0320_REQRepeat_Record );
            //fill in the request update, only the part for which the BrokerAMS is responsible
            pFundBroker->getData( repeat, BF::HOST );

            //set the RunMode field to the EntityUpdate trxn
            DSTCWorkSession::setRunMode( &repeat, lObjActivity );            
            
            //add the repeat to the retrieved request
            pDataReq->addRepeat( repeat );
            //cRepeats = pDataReq->getRepeatCount();
            //pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );
			   cRepeats ++;
       }

       DSTCFundBrokerFeeTxnBuilder::buildTransactions( workSession, pFundBroker, pTrCont );
       DSTCFundBrokerSettlementInstrTrxnBuilder::buildTransactions( workSession, pFundBroker, pTrCont, lObjActivity );

		 ++bfIter;
       
    }//end while

	 if(cRepeats > 0)
		pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFundBrokerTxnBuilder.cpp-arc  $
// 
//    Rev 1.4   Dec 10 2004 17:22:18   vadeanum
// PET117_FN21: settlement instructions enhancement.
// 
//    Rev 1.3   Nov 30 2004 18:44:44   aguilaam
// PET1117_FN21:  settlement instructions.
// 
//    Rev 1.2   Nov 15 2004 15:41:28   Fengyong
// Syncup - after .net conversion
// 
//    Rev 1.1   Nov 14 2004 14:32:36   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Nov 02 2004 16:03:16   FENGYONG
// Initial revision.
// 
*/