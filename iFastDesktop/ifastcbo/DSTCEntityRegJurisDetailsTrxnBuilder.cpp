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
// ^FILE   : DSTCEntityRegJurisDetailsTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 15 January  2014
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCEntityRegJurisDetailsTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0459_req.hpp>
#include <ifastdataimpl\dse_dstc0459_vw.hpp>

#include "ifasthosttransactioncontainer.hpp"
#include "DstcEntityRegJurisDetailsTrxnBuilder.hpp"
#include "Entity.hpp"
#include "EntityRegJurisDetails.hpp"
#include "EntityRegJurisDetailslist.hpp"

#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "trade.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENT_REG_JURIS_DETAILS_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCEntityRegJurisDetailsTrxnBuilder" );
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
void DSTCEntityRegJurisDetailsTrxnBuilder::buildTrxnKey(DString& dstrKey, 
													    const DString &accNum, 
													    const DString &entityId) 
{
	//build the key
	addIDITagValue( dstrKey, TRXNTAG::ENTITYREGJURISDETAILS, I_("EntityRegJurisDetails") );

	addIDITagValue( dstrKey, TRXNTAG::ACCTTAG, accNum );
		
	addIDITagValue( dstrKey, TRXNTAG::ENTITYIDTAG, entityId );
}

//******************************************************************************
SEVERITY DSTCEntityRegJurisDetailsTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
																  BFAbstractCBO *pObj, 
																  HostTransactionContainer *pTrCont, 
																  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   BFCBO *pHolder (NULL);
   DString dstrAccountNum(I_("0")), dstrEntityId(I_("0")), dstrLevel, dstrCurrentEntRegAcctNum;
   
   EntityRegJurisDetailsList *pEntityRegJurisDetailsList = NULL;
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

	int count = 0;
	TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_ENTITY_REGULATORY_JURIS_DETAILS : UPDATE_ENTITY_REGULATORY_JURIS_DETAILS;

	if(pHolder)
	{
		DString dstTrnKey, dstKeyTypes;

		if (dstrLevel == I_("Account"))
		{
			pMFAccount->getEntityRegJurisDetailsList(pEntityRegJurisDetailsList, I_("0"), BF::HOST, false);
		}
		else if (dstrLevel == I_("Entity"))
		{
			pEntity->getEntityRegJurisDetailsList(pEntityRegJurisDetailsList, BF::HOST, dstrCurrentEntRegAcctNum);		
		}

		if (pEntityRegJurisDetailsList && pEntityRegJurisDetailsList->hasTransactionUpdates())
		{
			BFData *pDataReq = NULL;
			BFData *pDataRes = NULL;

			BFObjIter iter( *pEntityRegJurisDetailsList, BF::HOST );
			EntityRegJurisDetails* pEntityRegJurisDetails = NULL;

			DSTCEntityRegJurisDetailsTrxnBuilder::buildTrxnKey( dstTrnKey, dstrAccountNum, dstrEntityId );

			HostTransactionContainerIterator iterTrxnContList( pTrCont );

			iterTrxnContList.walkStrKey( dstTrnKey );
			iterTrxnContList.walkTrxnGroup( NO_GROUP );
			iterTrxnContList.walkTrxnSubType( 0 );

			iterTrxnContList.begin();

			//fill in the fixed area
			if( iterTrxnContList.end() )
			{
				//TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_ENTITY_REGULATORY_JURIS_DETAILS : UPDATE_ENTITY_REGULATORY_JURIS_DETAILS;

				pDataReq = new BFData( ifds::DSTC0459_REQ );
				pDataRes = new BFData( ifds::DSTC0459_VW );

				DString strTrack, strActivity;

				pEntityRegJurisDetailsList->getTrackActivity(strTrack,strActivity);         
				pDataReq->setElementValue( ifds::Track, strTrack, false, false );
				pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

				//fill in the request update
				DString mgmtCoId;
				workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

				pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
				pDataReq->setElementValue( ifds::AccountNum, dstrAccountNum );

				addIDITagValue( dstKeyTypes, I_("OBJECT"), I_("EntityRegJurisDetails") );
				addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

			}
			else
				pDataRes = (*iterTrxnContList)->getRequestDataObject();

			iter.begin();
			while( !iter.end() )
			{
				if( iter.hasTransactionUpdates() )
				{
					BFDataGroupId idDataGroup = iter.getKey().getDataGroupId ();
					count++;
					pEntityRegJurisDetails = dynamic_cast<EntityRegJurisDetails*>( iter.getObject() );
				
					dstrEntityId = I_("0");

					pEntityRegJurisDetails->getField(ifds::EntityName, dstrEntityId, BF::HOST, false);

					addIDITagValue( dstKeyTypes, KEYTYPES::ENTITYID, dstrEntityId );				

					//create a repeat for the request and fill it in
					BFData repeat( ifds::DSTC0459_REQRepeat_Record);

					//fill in the request update
					pEntityRegJurisDetails->getData( repeat, BF::HOST );

					//set the RunMode field 
					DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity() );

					//add the lDataRepeat to the request
					pDataReq->addRepeat( repeat );
					DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
					pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );

					


				}
				++iter;
			}

			JData *jdata = new JData( DSTC_REQUEST::ENT_REG_JURIS_DETAILS_UPDATE, pDataReq, pDataRes );
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
