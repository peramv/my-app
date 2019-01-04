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
//    Copyright 2003 by International Financial, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCMktIndexMasterTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCMktIndexMasterTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCMktIndexMasterTrxnBuilder.hpp"
#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0242_req.hpp>
#include <ifastdataimpl\dse_dstc0242_vw.hpp>
#include "MktIndexMaster.hpp"
#include "MktIndexMasterList.hpp"
#include "MktIndexFunds.hpp"
#include "MktIndexFundsList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INDEX_MASTER_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCMktIndexMasterTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

int DSTCMktIndexMasterTrxnBuilder::buildIndex = 0;

//******************************************************************************

void DSTCMktIndexMasterTrxnBuilder::buildTrxnKey( DString& strKey, MktIndexMaster* pMktIndexMaster )
{
   DString dstrMktIndexCode;

   if( pMktIndexMaster ) 
   {
		pMktIndexMaster->getField( ifds::IndexCode, dstrMktIndexCode, BF::HOST, true );
		dstrMktIndexCode.strip();
		addIDITagValue( strKey, I_("INDEXCODE"), dstrMktIndexCode );  // TRXNTAG::AMSCODETAG
	}
	addIDITagValue( strKey, I_("INDEXMASTER"), DString::asString( buildIndex++ ) );  // TRXNTAG::AMSMSTRINFOTAG
}

//******************************************************************************

SEVERITY DSTCMktIndexMasterTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                           BFAbstractCBO* pObj,
                                                           HostTransactionContainer* pTrCont, 
                                                           BF_OBJ_ACTIVITY objActivity)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   MktIndexMasterList* pMktIndexMasterList = dynamic_cast<MktIndexMasterList*>(pObj);

   if( pMktIndexMasterList && pMktIndexMasterList->hasTransactionUpdates( true ) )
   {
      BFObjIter iterList( *pMktIndexMasterList, BF::HOST );

      DString keyString;
      DSTCMktIndexMasterTrxnBuilder::buildTrxnKey( keyString, NULL );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );
      iterTrxnContList.walkStrKey( keyString );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      while( !iterList.end() )
      {
         MktIndexMaster* pMktIndexMaster = dynamic_cast<MktIndexMaster*>( iterList.getObject() );
         BF_OBJ_ACTIVITY listObjActivity = iterList.getKey().getActivity();

         BFData * pDataReq = NULL;
         BFData * pDataRes = NULL;

         if( MktIndexUpdated( pMktIndexMaster, listObjActivity ) )
         {
            iterTrxnContList.begin();
            // If first update then update fix area : build key and add transaction
            if( iterTrxnContList.end() )
            {
               pDataReq = new BFData( ifds::DSTC0242_REQ );
               pDataRes = new BFData( ifds::DSTC0242_VW );

               DString dstrTrack, dstrActivity;
               pMktIndexMasterList->getTrackActivity( dstrTrack, dstrActivity );
               pDataReq->setElementValue( ifds::Track, dstrTrack, false, false );
               pDataReq->setElementValue( ifds::Activity, dstrActivity, false, false );

               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

               //fill in the request update
               pMktIndexMaster->getData( *pDataReq, BF::HOST );

               DSTCWorkSession::setRunMode(pDataReq, listObjActivity);
               DString dstStrKey;
               DSTCMktIndexMasterTrxnBuilder::buildTrxnKey( dstStrKey, pMktIndexMaster );

               DString keyTypes;

               JData *jdata = new JData( DSTC_REQUEST::INDEX_MASTER_UPDATE, pDataReq, pDataRes);
               pTrCont->addTransaction( dstStrKey, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );
            }  // if first object on the update list
            else
            {
               pDataRes = (*iterTrxnContList)->getRequestDataObject();
            }

            MktIndexFundsList* pMktIndexFundsList = NULL;

            SEVERITY sev1 = pMktIndexMaster->getMktIndexFundsList( pMktIndexFundsList, BF::HOST, false );

            if( pMktIndexFundsList )
            {
               BFObjIter iterFundsList( *pMktIndexFundsList, BF::HOST );

               while( !iterFundsList.end() )
               {
                  MktIndexFunds* pMktIndexFunds = dynamic_cast<MktIndexFunds*>( iterFundsList.getObject() );
                  BF_OBJ_ACTIVITY FundToObjActivity = iterFundsList.getKey().getActivity();

                  if( MktIndexUpdated( pMktIndexFunds, FundToObjActivity ) 
                      || listObjActivity == OBJ_ACTIVITY_DELETED )
                  {
                     BFData repeat( ifds::DSTC0242_REQRepeat_Record );
                     pMktIndexFunds->getData( repeat, BF::HOST );

                     if( listObjActivity == OBJ_ACTIVITY_DELETED )
                     {
                        repeat.setElementValue( ifds::RunMode, RUNMODE::DELETED );
                     }
                     else
                     {
                        DSTCWorkSession::setRunMode( &repeat, FundToObjActivity );
                     }

                     pDataReq->addRepeat( repeat );
                     pDataReq->setElementValue( ifds::RepeatCount, DString::asString( pDataReq->getRepeatCount() ) );
                  }
                  ++iterFundsList;
               }
            }
         }
         ++iterList;
      }  // while loop
   } // if
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool DSTCMktIndexMasterTrxnBuilder::MktIndexUpdated( BFAbstractCBO* pCBO, BF_OBJ_ACTIVITY ObjActivity, bool bRecursive )
{
   bool bUpdate( false );
   bUpdate = ( pCBO != NULL ) && ( ObjActivity == OBJ_ACTIVITY_ADDED || pCBO->hasTransactionUpdates( bRecursive ) || ObjActivity == OBJ_ACTIVITY_DELETED );
   return( bUpdate );
}
