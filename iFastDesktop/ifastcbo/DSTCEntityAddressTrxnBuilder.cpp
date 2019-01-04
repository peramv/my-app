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
// ^FILE   : DSTCEntityAddressTrxnBuilder.cpp
// ^AUTHOR : Ram Singaram
// ^DATE   : Novemeber 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCENTITYADDRESSTRXNBUILDER
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "entity.hpp"
#include "dstcentityaddresstrxnbuilder.hpp"
#include "entityaddress.hpp"
#include "addressentitylist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0080_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0080_req.hpp>
#include <ifastdataimpl\dse_dstc0080_vw.hpp>

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCEntityAddressTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITYADDRESS_UPDATE;
}

//******************************************************************************
SEVERITY DSTCEntityAddressTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   Entity* entity = dynamic_cast<Entity*>(pObj);
   DString dstEntityId;

   if( entity != NULL )
   {
      //walk the list of address
      AddressEntityList* addressList;

      //if no list do not go and get one from the database
      severity = entity->getAddressEntityList( addressList, BF::HOST, false );

      entity->getEntityId( dstEntityId );
      dstEntityId.stripLeading('0').strip();

      DString keyString;
      addIDITagValue( keyString, TRXNTAG::ENTADDRTAG, dstEntityId );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );
      //set filter to look for Entity fixed area
      iterTrxnContList.walkStrKey( keyString );
      //check if the fixed area of the 'EntityAddress' update request is already in the HostTransactionContainer
      //the trxn hasn't been handled yet, no group and sub type set,
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      if( addressList != NULL && severity <= WARNING )
      {
         //define an iterator on the addressList
         BFObjIter iterAddressList( *addressList, BF::HOST );

         //define an iterator on the HostTransactionContainer

         iterAddressList.begin();
         while( !iterAddressList.end() )
         {
            EntityAddress* entityAddress = dynamic_cast<EntityAddress*>(iterAddressList.getObject());
            BF_OBJ_ACTIVITY listObjActivity = iterAddressList.getKey().getActivity();

            BFData* pDataReq = NULL;
            BFData* pDataRes = NULL;

            if( iterAddressList.hasTransactionUpdates( ) )
            {
               iterTrxnContList.begin();
               if( iterTrxnContList.end() ) // Fixed Area does not exists, so create one
               {
                  pDataReq = new BFData( ifds::DSTC0080_REQ );
                  pDataRes = new BFData( ifds::DSTC0080_VW );

                  DString strTrack,strActivity;
                  addressList->getTrackActivity(strTrack,strActivity);;       
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                  DString keyTypes;
                  addIDITagValue( keyTypes, KEYTYPES::ENTITYID, dstEntityId );

                  JData *jdata = new JData( DSTC_REQUEST::ENTITYADDRESS_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( keyString, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );
               }
               else
               {
                  pDataReq = (*iterTrxnContList)->getRequestDataObject();
               }

               //create a repeat for the request and filled in
               BFData repeat( ifds::DSTC0080_REQRepeat_Record );
               //fill in the request update, only the part for which the Entity is responsible
               //entity->getData(repeat, BF::HOST );
               entityAddress->getData( repeat, BF::HOST );

               //set the RunMode field to the EntityUpdate trxn
               DSTCWorkSession::setRunMode( &repeat, listObjActivity );

               //set dstEntityId in the repeating section, since EntityAddress cbo does not have entityid
               repeat.setElementValue( ifds::EntityId, dstEntityId, false, false );

               //add the repeat to the retrieved request

               pDataReq->addRepeat( repeat );
               unsigned long cRepeats = pDataReq->getRepeatCount();
               pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );

            } // if entityaddress is updated and everything
            // move to the next address for the entity
            ++iterAddressList;
         } // while more addresses for entity is available
      } //if addrlist != null
   } // if entity != null

   return(GETCURRENTHIGHESTSEVERITY());   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCEntityAddressTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.14   Nov 14 2004 14:32:16   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.13   Mar 21 2003 18:05:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:54:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:55:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:27:28   PURDYECH
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
 *    Rev 1.3   Jan 16 2001 14:03:52   OLTEANCR
 * modified buildTransaction(..)
 * 
 *    Rev 1.2   Jan 16 2001 13:53:32   OLTEANCR
 * 
 *    Rev 1.1   Dec 17 2000 20:23:04   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:54   SMITHDAV
 * Initial revision.
// 
//    Rev 1.8   Feb 03 2000 10:51:58   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.7   Feb 02 2000 10:33:56   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.6   Jan 09 2000 13:18:38   POPESCUS
// added the group id to the lists
// 
//    Rev 1.5   Jan 07 2000 17:46:44   WINNIE
// fix deletion and Runmode
// 
//    Rev 1.4   Jan 06 2000 12:02:56   POPESCUS
// fix related to filter more the HTC 
// 
//    Rev 1.3   Dec 15 1999 11:47:36   POPESCUS
// do not get the list from the database if there is none in repository
// 
//    Rev 1.2   Dec 12 1999 17:55:32   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/

