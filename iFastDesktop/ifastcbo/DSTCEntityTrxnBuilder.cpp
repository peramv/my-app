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
// ^FILE   : DSTCEntityTrxnBuilder.cpp
// ^AUTHOR : Ram Singaram
// ^DATE   : October 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCENTITYTRXNBUILDER
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "accountentityxref.hpp"
#include "dstcentitytrxnbuilder.hpp"
#include "dstcentityidstrxnbuilder.hpp"
#include "dstcentityaddresstrxnbuilder.hpp"
#include "AcctCutOffTimesTrxnBuilder.hpp"
#include "DSTCRegDocumentListTrxnBuilder.hpp"
#include "entity.hpp"
#include "entitylist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0078_req.hpp>
#include <ifastdataimpl\dse_dstc0078_vw.hpp>
#include <ifastdataimpl\dse_dstc0078_reqrepeat_record.hpp>
#include "worksessionentitylist.hpp"
#include "DSTCWhereUseTrxnBuilder.hpp"
#include "DSTCDemographicsTrxnBuilder.hpp"
#include "DSTCEntityRegDetailsTrxnBuilder.hpp"
#include "DSTCEntityRegJurisDetailsTrxnBuilder.hpp"
#include "DSTCEntityRiskTrxnBuilder.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCEntityTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

//******************************************************************************
void DSTCEntityTrxnBuilder::buildTrxnKey( DSTCWorkSession &workSession,
                                          DString& strKey, 
                                          Entity* entity )
{
   DString entityId;

   //get the entity id off the entity
   entity->getEntityId( entityId );
   entityId.stripLeading( '0' );
   entityId.strip();

   AccountEntityXref *pAccountEntityXref;
   workSession.getAccountEntityXref( BF::HOST, pAccountEntityXref );

   //build the key
   DString searchKey;
   AccountEntityXref::buildPartialKeyForEntityId( searchKey, entityId );
   BFObjIter iterAccountEntityXrefOut( *pAccountEntityXref, BF::HOST, true );
   iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   if( !iterAccountEntityXrefOut.end() )
   {

      DString key = iterAccountEntityXrefOut.getStringKey();
      DString accNum;

      AccountEntityXref::getValueForTag( key, I_( "AccountNum" ), accNum );
      accNum.stripLeading( '0' );
      accNum.strip();
      if (!accNum.empty())
      {
         addIDITagValue (strKey, TRXNTAG::ACCTTAG, accNum);
      }
   }
   addIDITagValue( strKey, TRXNTAG::ENTITYIDTAG, TRXNTAG::ENTITYIDTAG );
}

//******************************************************************************
SEVERITY DSTCEntityTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                   BFAbstractCBO* pObj,
                                                   HostTransactionContainer* pTrCont, 
                                                   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY severity = SEVERE_ERROR;
   WorkSessionEntityList* pWorkSessionEntityList = dynamic_cast< WorkSessionEntityList* >(pObj);
   if( pWorkSessionEntityList )
   {
      BFObjIter bfIter( *pWorkSessionEntityList, BF::HOST );
      while( !bfIter.end() )
      {

         Entity* pEntity = dynamic_cast< Entity* >( bfIter.getObject() );
         BF_OBJ_ACTIVITY lObjActivity = bfIter.getKey().getActivity();

         if( pEntity != NULL && ( lObjActivity == OBJ_ACTIVITY_DELETED || 
                                  lObjActivity == OBJ_ACTIVITY_ADDED || 
                                  pEntity->hasTransactionUpdates( false ) ) )
         {
            //define an iterator on the HostTransactionContainer
            HostTransactionContainerIterator iterTrxnContList( pTrCont );

            DString keyString;

            buildTrxnKey( workSession, keyString, pEntity );
            //set filter to look for Entity fixed area
            iterTrxnContList.walkStrKey( keyString );
            //the trxn hasn't been handled yet, no group and sub type set,
            iterTrxnContList.walkTrxnGroup( NO_GROUP );
            iterTrxnContList.walkTrxnSubType( 0 );
            //check if the fixed area of the 'Entity' update request is already in the HostTransactionContainer
            iterTrxnContList.begin();

            BFData* pDataReq = NULL;
            BFData* pDataRes = NULL;

            if( iterTrxnContList.end() )
            // Fixed Area either does not exists, so create a new one
            {
               pDataReq   = new BFData( ifds::DSTC0078_REQ );
               pDataRes   = new BFData( ifds::DSTC0078_VW );

               DString strTrack,strActivity;
               pEntity->getTrackActivity(strTrack,strActivity);
               pDataReq->setElementValue( ifds::Track, strTrack, false, false );
               pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

               DString keyTypes;
               DString entityId;

               //get the entity number off the entity
               pEntity->getEntityId( entityId );
               entityId.stripLeading( '0' );
               entityId.strip();
               addIDITagValue( keyTypes, KEYTYPES::ENTITYID, entityId );

               TRXN_TYPE trxnType = lObjActivity == OBJ_ACTIVITY_ADDED ? NEW_ENTITY : UPDATE_ENTITY;

               //add the transaction to the container;
               JData *jdata = new JData( DSTC_REQUEST::ENTITY_UPDATE, pDataReq, pDataRes );
               pTrCont->addTransaction( keyString, jdata, lObjActivity, trxnType, keyTypes );
            }
            else
            {
               pDataReq = (*iterTrxnContList)->getRequestDataObject();
            }

            //create a repeat for the request and filled in
            BFData repeat( ifds::DSTC0078_REQRepeat_Record );
            //fill in the request update, only the part for which the Entity is responsible
            pEntity->getData( repeat, BF::HOST );
            //set the enity id as well
            DString entityId;

            pEntity->getEntityId( entityId );
            repeat.setElementValue( ifds::EntityId, entityId, false, false );
            //add the repeat to the retrieved request
            //set the RunMode field to the EntityUpdate trxn
            DSTCWorkSession::setRunMode( &repeat, lObjActivity );
            pDataReq->addRepeat( repeat );
            unsigned long rptCount = pDataReq->getRepeatCount();
            pDataReq->setElementValue( ifds::RepeatCount, DString::asString( rptCount ), false, false );
         }

         //call the transaction builders of the objects that are contained by the entity
         //for the entity ids
         DSTCEntityIdsTrxnBuilder::buildTransactions( workSession, pEntity, pTrCont, lObjActivity );
         //for the entity address
         DSTCEntityAddressTrxnBuilder::buildTransactions( workSession, pEntity, pTrCont, lObjActivity );
         // where used
         DSTCWhereUseTrxnBuilder::buildTransactions( workSession, pEntity, pTrCont, lObjActivity );

         AcctCutOffTimesTrxnBuilder::buildTransactions1( workSession, pEntity, pTrCont, lObjActivity );

         //DString strShrNum;
         //pEntity->getField( ifds::ShrNum, strShrNum, BF::HOST, false );
         //strShrNum.stripAll();

         //// If there is adding new entity where use record without linking to account/shr holder
         //// then skip calling to Demographics with ShrNum = 0, because it raise condition for blank field 
         //// however, this is temporary work out, we may need to find better way ! 
         //if ( !strShrNum.empty() )
         {
            DSTCDemographicsTrxnBuilder::buildTransactions1( workSession, pEntity, pTrCont, lObjActivity );
         }
		 //EntityRegDetails update
		 DSTCEntityRegDetailsTrxnBuilder::buildTransactions (workSession, pEntity, pTrCont, lObjActivity);

		 //EntityRegJurisDetails update
		 DSTCEntityRegJurisDetailsTrxnBuilder::buildTransactions (workSession, pEntity, pTrCont, lObjActivity);

         DSTCEntityRiskTrxnBuilder::buildTransactions(workSession, pEntity, pTrCont, lObjActivity);

         ++bfIter;
      }

   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCEntityTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.25   Nov 14 2008 05:30:10   daechach
 * PET5517 FN71 Unclaimed Property Phase 2 - take out logic that cause problem with KYC Phase 2.
 * 
 *    Rev 1.24   Nov 06 2008 02:12:26   daechach
 * PET5517 FN71 Unclaimed Property Phase 2
 * 
 *    Rev 1.23   31 Oct 2008 16:18:12   popescu
 * KYC/AML - joint accounts feature
 * 
 *    Rev 1.22   Sep 12 2008 06:30:42   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.21   Jul 25 2008 14:55:04   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.20   26 Mar 2007 16:49:04   popescu
 * Incidents# 844319/847768 - protect DSK from extra records returned in vew 61
 * 
 *    Rev 1.19   Jul 21 2006 14:05:58   jankovii
 * PET 2192 FN02 - Dealings-Sender Cut-Off Time.
 * 
 *    Rev 1.18   Mar 06 2005 15:40:40   yingbaol
 * PET1171,FN01: EU Saving add where use transaction builder
 * 
 *    Rev 1.17   Nov 14 2004 14:32:20   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.16   Oct 29 2004 11:52:20   YINGBAOL
 * PTS10034532: take out EntityId as part of the key
 * 
 *    Rev 1.15   Sep 28 2004 10:46:30   YINGBAOL
 * PET1145 FN01 Entity update support
 * 
 *    Rev 1.14   Mar 21 2003 18:05:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:54:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 12:55:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   22 May 2002 18:27:54   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   Feb 25 2002 18:55:30   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.9   Oct 09 2001 11:35:54   YINGBAOL
 * more fixes
 * 
 *    Rev 1.8   Oct 04 2001 11:55:36   YINGBAOL
 * fix transaction problem
 * 
 *    Rev 1.7   23 May 2001 14:39:50   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.6   03 May 2001 14:06:18   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   09 Mar 2001 18:03:46   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.4   Feb 02 2001 18:28:12   MCNABBGL
 * scrubbed code
 * 
 *    Rev 1.3   Jan 31 2001 16:10:58   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.2   Jan 16 2001 13:53:34   OLTEANCR
 * 
 *    Rev 1.1   Dec 17 2000 20:23:06   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.15   Feb 03 2000 10:52:00   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.14   Feb 02 2000 10:33:58   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.13   Jan 27 2000 15:39:34   POPESCUS
// fixes to the trxns; adding repeats to the entity ids builder
// 
//    Rev 1.12   Jan 20 2000 11:45:00   POPESCUS
// fix order of checking the update flags
// 
//    Rev 1.11   Jan 07 2000 17:45:52   WINNIE
// fix deletion
// 
//    Rev 1.10   Jan 06 2000 12:02:56   POPESCUS
// fix related to filter more the HTC 
// 
//    Rev 1.9   Dec 15 1999 07:42:54   POPESCUS
// setting the entity id
// 
//    Rev 1.8   Dec 12 1999 17:55:40   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/