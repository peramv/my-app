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
// ^FILE   : DSTCEntityidsTrxnBuilder.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : November 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCDistributionsTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcentityidstrxnbuilder.hpp"
#include "accountentityxref.hpp"
#include "entity.hpp"
#include "entityids.hpp"
#include "entityidslist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0079_req.hpp>
#include <ifastdataimpl\dse_dstc0079_vw.hpp>
#include <ifastdataimpl\dse_dstc0079_reqrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITYSEARCHID_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCEntityIdsTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
   extern const long OBJECT_DOES_NOT_EXIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

//*****************************************************************************************************
SEVERITY DSTCEntityIdsTrxnBuilder::buildTrxnKey( DSTCWorkSession &workSession,
                                             DString& strKey, 
                                             Entity* entity )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTrxnKey" ) );

   DString entityId,accNum, dstrRoutingType;
   //get the entity id off the entity
   entity->getEntityId( entityId );
   entityId.stripLeading( '0' );
   entityId.strip();

   //entity->getField( ifds::RoutingType, dstrRoutingType, BF::HOST );
   //dstrRoutingType.strip();

   //build the key
   AccountEntityXref *pAccountEntityXref = NULL;	
	workSession.getAccountEntityXref( BF::HOST, pAccountEntityXref );
	if( pAccountEntityXref )
	{

		DString searchKey;
		AccountEntityXref::buildPartialKeyForEntityId( searchKey, entityId );
		BFObjIter iterAccountEntityXrefOut( *pAccountEntityXref, BF::HOST, true );
		if( !iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
		{
           // we add condition, so that it is easy for us to trace internal error in production
				DString strTemp;
				addIDITagValue (strTemp, I_("OBJECT"), I_("AccountEntityXrefObj") );
				//ADDCONDITIONFROMFILEIDI (CND::OBJECT_DOES_NOT_EXIST, strTemp);
				//return( GETCURRENTHIGHESTSEVERITY() );
		}
      else
      {		
	      iterAccountEntityXrefOut.getObject()->getField( ifds::AccountNum, accNum, BF::HOST );
      }
	
	}
   accNum.stripLeading( '0' );
   accNum.strip();
   if( accNum != NULL_STRING )
      addIDITagValue( strKey, TRXNTAG::ACCTTAG, accNum );

   addIDITagValue( strKey, TRXNTAG::ENTITYIDTAG, entityId );
	//here put the entity id 'cause we should put something in
   //addIDITagValue( strKey, TRXNTAG::ENTITYIDSTAG, entityId );
   addIDITagValue( strKey, TRXNTAG::ENTITYIDSTAG, TRXNTAG::ENTITYIDSTAG );
	return NO_CONDITION;


}

//******************************************************************************
SEVERITY DSTCEntityIdsTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                      BFAbstractCBO* pObj,
                                                      HostTransactionContainer* pTrCont, 
                                                      BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   Entity* entity = dynamic_cast<Entity*>(pObj);

   if( entity != NULL )
   {
      //walk the list of entities ids
      EntityIdsList* identificationlist = NULL;

      entity->getEntityIdsList( identificationlist, BF::HOST, false );

      DString entityId;
      entity->getEntityId( entityId );
      entityId.stripLeading( '0' );
      entityId.strip();

      if( identificationlist != NULL )
      {
         BFObjIter iteridlist( *identificationlist, BF::HOST );

         while( !iteridlist.end() )
         {
            EntityIds* idsObject = dynamic_cast<EntityIds *>(iteridlist.getObject());
            // we have to be very cautions because we have internal error here and there.
            // YB Oct., 15, 2004

				if( idsObject ) 

				{
					BF_OBJ_ACTIVITY listObjActivity = iteridlist.getKey().getActivity();

					if( iteridlist.hasTransactionUpdates( ) )
					{
						//define an iterator on the HostTransactionContainer
						HostTransactionContainerIterator iterTrxnContList( pTrCont );
						//** Data* fixedArea = NULL;
						//set filter to look for Entity id fixed area
						DString keyString;

						if( DSTCEntityIdsTrxnBuilder::buildTrxnKey( workSession, keyString, entity ) >= WARNING )
						{
						   break; // there are error, we will not build. 						
						}
						//set the filter on the string key
						iterTrxnContList.walkStrKey( keyString );
						//the trxn hasn't been handled yet, no group and sub type set,
						iterTrxnContList.walkTrxnGroup( NO_GROUP );
						iterTrxnContList.walkTrxnSubType( 0 );
						//start walking the list
						iterTrxnContList.begin();

						BFData* pDataReq = NULL;
						BFData* pDataRes = NULL;
						if( iterTrxnContList.end() )    // Fixed Area does not exist, so create one
						{
							pDataReq = new BFData( ifds::DSTC0079_REQ );
							pDataRes = new BFData( ifds::DSTC0079_VW );

							DString strTrack,strActivity;
							identificationlist->getTrackActivity(strTrack, strActivity);
							pDataReq->setElementValue( ifds::Track, strTrack, false, false );
							pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

							DString mgmtCoId;
							workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
							pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

							DString keyTypes;
							addIDITagValue( keyTypes, KEYTYPES::ENTITYID, entityId );

							//not quite relevant here
							TRXN_TYPE trxnType = listObjActivity == OBJ_ACTIVITY_ADDED ? NEW_ENTITY_IDS : UPDATE_ENTITY_IDS;

							JData *jdata = new JData( DSTC_REQUEST::ENTITYSEARCHID_UPDATE, pDataReq, pDataRes );
							pTrCont->addTransaction( keyString, jdata, listObjActivity, trxnType, keyTypes );
						}
						else
						{
							pDataReq = (*iterTrxnContList)->getRequestDataObject();
						}

						//create a repeat for the request and filled in
						BFData repeat( ifds::DSTC0079_REQRepeat_Record );

						//initialize count to the previous repeat count
						DString strCount = pDataReq->getElementValue( ifds::RepeatCount );
						int count = strCount.asInteger();
						//increase the number of repeats
						count++;
						//fixedarea....
						pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
						//fill in the request update, only the part for which the Entity id is responsible
						idsObject->getData( repeat, BF::HOST );
						repeat.setElementValue( ifds::EntityId, entityId, false, false );

						//set the RunMode field to the EntityIdUpdate trxn
						DSTCWorkSession::setRunMode( &repeat, listObjActivity );
						//add the repeat to the retrieved request
						pDataReq->addRepeat( repeat );
					}
            }
            ++iteridlist;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCEntityIdsTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.16   Nov 14 2004 14:32:18   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.15   Nov 04 2004 11:01:12   FENGYONG
 * PET1117 FN54 - Fund broker static temp check in for 59 build
 * 
 *    Rev 1.14   15 Oct 2004 17:12:24   YINGBAOL
 * PTS10034771: desktop sends temp entityID to back end.
 * 
 *    Rev 1.13   Mar 21 2003 18:05:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:54:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:55:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:27:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   Feb 25 2002 18:55:28   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.8   23 May 2001 14:39:52   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.7   03 May 2001 14:06:16   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   09 Mar 2001 18:03:44   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.5   09 Feb 2001 15:01:30   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.4   Jan 31 2001 16:10:56   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.3   Jan 16 2001 14:04:16   OLTEANCR
 * modified buildTransaction(..)
 * 
 *    Rev 1.2   Jan 16 2001 13:53:34   OLTEANCR
 * 
 *    Rev 1.1   Dec 17 2000 20:23:04   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:54   SMITHDAV
 * Initial revision.
// 
//    Rev 1.17   Feb 03 2000 10:51:58   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.16   Feb 02 2000 10:33:56   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.15   Jan 27 2000 15:39:34   POPESCUS
// fixes to the trxns; adding repeats to the entity ids builder
// 
//    Rev 1.14   Jan 09 2000 13:18:38   POPESCUS
// added the group id to the lists
// 
//    Rev 1.13   Jan 07 2000 17:37:48   WINNIE
// fix deletion 
// 
//    Rev 1.12   Jan 06 2000 12:02:56   POPESCUS
// fix related to filter more the HTC 
// 
//    Rev 1.11   Jan 05 2000 14:53:26   WINNIE
// assignment of entityid for view 97 repeating section
// 
//    Rev 1.10   Dec 15 1999 11:47:38   POPESCUS
// do not get the list from the database if there is none in repository
// 
//    Rev 1.9   Dec 14 1999 15:50:48   WINNIE
// change logic not to use dynamic allocation for view 79 repeatrecord; add repeat count assignment
// 
//    Rev 1.8   Dec 12 1999 17:55:38   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/