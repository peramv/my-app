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
// ^FILE   : DSTCEntityRegDetailsTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 15 January  2014
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCEntityRegDetailsTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0457_req.hpp>
#include <ifastdataimpl\dse_dstc0457_vw.hpp>

#include "ifasthosttransactioncontainer.hpp"
#include "DstcEntityRegDetailstrxnbuilder.hpp"
#include "Entity.hpp"
#include "EntityRegDetails.hpp"
#include "EntityRegDetailslist.hpp"

#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "trade.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENT_REG_DETAILS_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCEntityRegDetailsTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
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

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId EntityName;
   extern CLASS_IMPORT const BFTextFieldId CurrentEntRegAcctNum;
}

//******************************************************************************
void DSTCEntityRegDetailsTrxnBuilder::buildTrxnKey(DString& dstrKey, 
												   const DString &accNum, 
												   const DString &entityId) 
{
	//build the key
	addIDITagValue( dstrKey, TRXNTAG::ENTITYREGDETAILS, I_("EntityRegDetails") );

	addIDITagValue( dstrKey, TRXNTAG::ACCTTAG, accNum );
		
	addIDITagValue( dstrKey, TRXNTAG::ENTITYIDTAG, entityId );
		
}

//******************************************************************************
SEVERITY DSTCEntityRegDetailsTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
														   BFAbstractCBO *pObj, 
														   HostTransactionContainer *pTrCont, 
														   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   BFCBO *pHolder (NULL);
   DString dstrAccountNum(I_("0")), dstrEntityId(I_("0")), dstrLevel, dstrCurrentEntRegAcctNum;
   
   EntityRegDetailsList *pEntityRegDetailsList = NULL;
   MFAccount *pMFAccount = dynamic_cast<MFAccount*>(pObj);
   Entity *pEntity = dynamic_cast<Entity*>(pObj);

   if (pMFAccount)
   {
      pHolder = pMFAccount;
	  pMFAccount->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
	  dstrLevel = I_("Account");
   }
   else if (pEntity)
   {
      pHolder = pEntity;
      pEntity->getField (ifds::EntityId, dstrEntityId, BF::HOST, false);
      pEntity->getField (ifds::CurrentEntRegAcctNum, dstrCurrentEntRegAcctNum, BF::HOST, false);
	  dstrLevel = I_("Entity");
   }


	DString dstrKey;
	int count = 0;
	TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_ENTITY_REGULATORY_DETAILS : UPDATE_ENTITY_REGULATORY_DETAILS;

	if(pHolder)	// just make sure there is the holder
	{
		DString dstTrnKey, dstKeyTypes;

		if (dstrLevel == I_("Account"))
		{
			pMFAccount->getEntityRegDetailsList(pEntityRegDetailsList, I_("0"), BF::HOST, false);
		}
		else if (dstrLevel == I_("Entity"))
		{
			pEntity->getEntityRegDetailsList(pEntityRegDetailsList, BF::HOST, dstrCurrentEntRegAcctNum);		
		}

		if ( pEntityRegDetailsList && pEntityRegDetailsList->hasTransactionUpdates() )
		{
			BFData *pDataReq = NULL;
			BFData *pDataRes = NULL;

			BFObjIter iter( *pEntityRegDetailsList, BF::HOST );
			EntityRegDetails* pEntityRegDetails = NULL;

			DSTCEntityRegDetailsTrxnBuilder::buildTrxnKey( dstTrnKey, dstrAccountNum, dstrEntityId );

			HostTransactionContainerIterator iterTrxnContList( pTrCont );

			iterTrxnContList.walkStrKey( dstTrnKey );
			iterTrxnContList.walkTrxnGroup( NO_GROUP );
			iterTrxnContList.walkTrxnSubType( 0 );

			iterTrxnContList.begin();

			//fill in the fixed area
			if( iterTrxnContList.end() )
			{
				//TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_ENTITY_REGULATORY_DETAILS : UPDATE_ENTITY_REGULATORY_DETAILS;

				pDataReq = new BFData( ifds::DSTC0457_REQ );
				pDataRes = new BFData( ifds::DSTC0457_VW );

				DString strTrack, strActivity;

				pEntityRegDetailsList->getTrackActivity(strTrack,strActivity);         
				pDataReq->setElementValue( ifds::Track, strTrack, false, false );
				pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

				//fill in the request update
				DString mgmtCoId;
				workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

				pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
				pDataReq->setElementValue( ifds::AccountNum, dstrAccountNum );

				addIDITagValue( dstKeyTypes, I_("OBJECT"), I_("EntityRegDetails") );
				addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

//				JData *jdata = new JData( DSTC_REQUEST::ENT_REG_DETAILS_UPDATE, pDataReq, pDataRes );
//				pTrCont->addTransaction( dstTrnKey, jdata, objActivity, trxnType, dstKeyTypes );
			}
			else
				pDataRes = (*iterTrxnContList)->getRequestDataObject();

			iter.begin();
			while( !iter.end() )
			{
				if( iter.hasTransactionUpdates() )
				{
					count++;
					pEntityRegDetails = dynamic_cast<EntityRegDetails*>( iter.getObject() );
					
					dstrEntityId = I_("0");

					pEntityRegDetails->getField(ifds::EntityName, dstrEntityId, BF::HOST, false);

					addIDITagValue( dstKeyTypes, KEYTYPES::ENTITYID, dstrEntityId );				
					
					//create a repeat for the request and fill it in
					BFData repeat( ifds::DSTC0457_REQRepeat_Record);

					//fill in the request update
					pEntityRegDetails->getData( repeat, BF::HOST );

					//set the RunMode field 
					DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity() );

					//add the lDataRepeat to the request
					pDataReq->addRepeat( repeat );
					DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
					pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
				}
				++iter;
			}

			JData *jdata = new JData( DSTC_REQUEST::ENT_REG_DETAILS_UPDATE, pDataReq, pDataRes );
			pTrCont->addTransaction( dstTrnKey, jdata, objActivity, trxnType, dstKeyTypes );
		} 
	}


   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* 
 */
