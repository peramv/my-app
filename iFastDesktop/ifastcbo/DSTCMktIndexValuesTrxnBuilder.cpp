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
// ^FILE   : DSTCMktIndexValuesTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCMktIndexValuesTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCMktIndexValuesTrxnBuilder.hpp"
#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0248_req.hpp>
#include <ifastdataimpl\dse_dstc0248_vw.hpp>
#include "MktIndexValues.hpp"
#include "MktIndexValuesList.hpp"
#include "MktIndexFunds.hpp"
#include "MktIndexFundsList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MKT_INDEX_VALUES_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCMktIndexValuesTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

int DSTCMktIndexValuesTrxnBuilder::buildIndex = 0;

//******************************************************************************

void DSTCMktIndexValuesTrxnBuilder::buildTrxnKey( DString& strKey, MktIndexValues* pMktIndexValues )
{
   DString dstrMktIndexCode, dstrEffectiveDate, dstrGoodBad, dstrClosingValue;

   if( pMktIndexValues ) 
   {
		pMktIndexValues->getField( ifds::IndexCode, dstrMktIndexCode, BF::HOST, false );
		dstrMktIndexCode.strip();
		addIDITagValue( strKey, I_("INDEXCODE"), dstrMktIndexCode );

      pMktIndexValues->getField( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false );
      dstrEffectiveDate.strip();
      addIDITagValue( strKey, I_("TRADEDATE"), dstrEffectiveDate );

      pMktIndexValues->getField( ifds::ClosingValue, dstrClosingValue, BF::HOST, true );
      dstrClosingValue.strip();
      addIDITagValue( strKey, I_("CLOSE"), dstrClosingValue );
	}
	addIDITagValue( strKey, I_("INDEXVALUES"), DString::asString( buildIndex++ ) );  // TRXNTAG::AMSMSTRINFOTAG
}

//******************************************************************************

SEVERITY DSTCMktIndexValuesTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                           BFAbstractCBO* pObj,
                                                           HostTransactionContainer* pTrCont, 
                                                           BF_OBJ_ACTIVITY objActivity)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   MktIndexValuesList* pMktIndexValuesList = dynamic_cast<MktIndexValuesList*>(pObj);

   if( pMktIndexValuesList && pMktIndexValuesList->hasTransactionUpdates( true ) )
   {
      bool bMktIndexUpdate( false );

      BFObjIter iterList( *pMktIndexValuesList, BF::HOST );

      DString keyString;
      DSTCMktIndexValuesTrxnBuilder::buildTrxnKey( keyString, NULL );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );
      iterTrxnContList.walkStrKey( keyString );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      BFData * pDataReq = NULL;
      BFData * pDataRes = NULL;

      // Fixed

      iterTrxnContList.begin();
      // If first update then update fix area : build key and add transaction
      if( iterTrxnContList.end() )
      {
         pDataReq = new BFData( ifds::DSTC0248_REQ );
         pDataRes = new BFData( ifds::DSTC0248_VW );

         DString dstrTrack, dstrActivity;
         pMktIndexValuesList->getTrackActivity(dstrTrack, dstrActivity);
         pDataReq->setElementValue( ifds::Track, dstrTrack, false, false );
         pDataReq->setElementValue( ifds::Activity, dstrActivity, false, false );

         DString mgmtCoId;
         workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
         pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

         DString keyTypes;

         JData *jdata = new JData( DSTC_REQUEST::MKT_INDEX_VALUES_UPDATE, pDataReq, pDataRes);
         pTrCont->addTransaction( keyString, jdata, objActivity, NOT_PERSISTENT, keyTypes );
      }  // if first object on the update list
      else
      {
         pDataRes = (*iterTrxnContList)->getRequestDataObject();
      }

      // Repeat Section
      BFObjIter iterMktIndexValuesList( *pMktIndexValuesList, BF::HOST );
      while( !iterMktIndexValuesList.end() )
      {
         MktIndexValues* pMktIndexValues = dynamic_cast<MktIndexValues*>( iterMktIndexValuesList.getObject() );
         BF_OBJ_ACTIVITY MktIndexObjActivity = iterMktIndexValuesList.getKey().getActivity();

         if( MktIndexUpdated( pMktIndexValues, MktIndexObjActivity ) )
         {
            //create a repeat for the request and filled in
            BFData repeat( ifds::DSTC0248_REQRepeat_Record );
            pMktIndexValues->getData( repeat, BF::HOST );
            DSTCWorkSession::setRunMode( &repeat, MktIndexObjActivity );

            pDataReq->addRepeat( repeat );
            pDataReq->setElementValue( ifds::RepeatCount, DString::asString( pDataReq->getRepeatCount() ) );
         }
         ++iterMktIndexValuesList;
      } // while
   } // Updated
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool DSTCMktIndexValuesTrxnBuilder::MktIndexUpdated( BFAbstractCBO* pCBO, BF_OBJ_ACTIVITY ObjActivity, bool bRecursive )
{
   bool bUpdate( false );
   bUpdate = ( pCBO != NULL ) && ( ObjActivity == OBJ_ACTIVITY_ADDED || pCBO->hasTransactionUpdates( bRecursive ) || ObjActivity == OBJ_ACTIVITY_DELETED );
   return( bUpdate );
}
