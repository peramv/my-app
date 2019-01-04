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
//    Copyright 2002 by International Financial, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAMSLmtTrxnBuilder.cpp
// ^AUTHOR : May Lin
// ^DATE   : July 11,2003
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAMSLmtTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcAMSLmttrxnbuilder.hpp"
#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0261_req.hpp>
#include <ifastdataimpl\dse_dstc0261_vw.hpp>

#include "AmsMstrInfo.hpp"
#include "amslmtoverridelist.hpp"
#include "amslmtoverride.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_LMT_OVERRIDE_LIST_UPDATE;

}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAMSLmtTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
   const I_CHAR * const CFDS = I_("Canada");

}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{

}

namespace KEYTYPES
{
 //  extern CLASS_IMPORT I_CHAR * const RuleType;
}


int DSTCAMSLmtTrxnBuilder::buildIndex = 0;

//******************************************************************************

void DSTCAMSLmtTrxnBuilder::buildTrxnKey( DString& strKey, AmsLmtOverride* pAmsLmtOverride )
{
   DString dstrRuleType;

   if ( pAmsLmtOverride )
   {
		pAmsLmtOverride->getField( ifds::RuleType, dstrRuleType, BF::HOST, true );
		dstrRuleType.strip();
		addIDITagValue( strKey, TRXNTAG::RULETYPETAG, dstrRuleType );
	}
	addIDITagValue( strKey, TRXNTAG::AMSLMTTAG, DString::asString( buildIndex++ ) );

}




//******************************************************************************
SEVERITY DSTCAMSLmtTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                     BFAbstractCBO* pObj,
                                                     HostTransactionContainer* pTrCont, 
                                                     BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   AmsMstrInfo* pAmsMstrInfo = dynamic_cast<AmsMstrInfo*>(pObj);

   if( pAmsMstrInfo )
   {
		AmsLmtOverrideList* pAmsLmtOverrideList = NULL;

	   severity = pAmsMstrInfo->getAmsLmtOverrideList( pAmsLmtOverrideList, BF::HOST, true );
       if( pAmsLmtOverrideList && severity <= WARNING )
	   {

			 bool bAmsUpdate( false );

			  //define an iterator on the 
			 BFObjIter iterList( *pAmsLmtOverrideList, BF::HOST );

			 DString keyString;
			 DSTCAMSLmtTrxnBuilder::buildTrxnKey( keyString, NULL );

			 //define an iterator on the HostTransactionContainer
			 HostTransactionContainerIterator iterTrxnContList( pTrCont );
			 //set filter to look for distribution fixed area
			 iterTrxnContList.walkStrKey( keyString );
			 //the trxn hasn't been handled yet, no group and sub type set,
			 iterTrxnContList.walkTrxnGroup( NO_GROUP );
			 iterTrxnContList.walkTrxnSubType( 0 );


			 while( !iterList.end() )
			 {
				AmsLmtOverride* pAmsLmtOverride = dynamic_cast<AmsLmtOverride*>( iterList.getObject() );
				BF_OBJ_ACTIVITY listObjActivity = iterList.getKey().getActivity();

           
				bAmsUpdate = AMSUpdated ( pAmsLmtOverride, listObjActivity );

				BFData * pDataReq = NULL;
				BFData * pDataRes = NULL;

				if( bAmsUpdate || objActivity == OBJ_ACTIVITY_DELETED)
				{
				   iterTrxnContList.begin();
				   // If first update then update fix area : build key and add transaction
				   if( iterTrxnContList.end() )
				   {

					  pDataReq = new BFData( ifds::DSTC0261_REQ );
					  pDataRes = new BFData( ifds::DSTC0261_VW );

					  DString strTrack,strActivity;
					  pAmsLmtOverrideList->getTrackActivity(strTrack, strActivity);
					  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
					  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

					  DString mgmtCoId;
					  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
					  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

					  //fill in the request update
					  pAmsMstrInfo->getData( *pDataReq, BF::HOST );

//					  DSTCWorkSession::setRunMode(pDataReq, listObjActivity);
					  DString dstStrKey;
					  DSTCAMSLmtTrxnBuilder::buildTrxnKey( dstStrKey, pAmsLmtOverride );

					  DString keyTypes = NULL_STRING;

					  JData *jdata = new JData( DSTC_REQUEST::AMS_LMT_OVERRIDE_LIST_UPDATE, pDataReq, pDataRes);
					  pTrCont->addTransaction( dstStrKey, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );
				   }  // if first object on the update list
				   else
				   {
					  pDataRes = (*iterTrxnContList)->getRequestDataObject();
				   }
					//create a repeat for the request and filled in
					BFData repeat( ifds::DSTC0261_REQRepeat_Record );
					//fill in the request update, only the part for which the Entity is responsible
					pAmsLmtOverride->getData( repeat, BF::HOST );
					//add the repeat to the retrieved request
					if ( objActivity == OBJ_ACTIVITY_DELETED )
						DSTCWorkSession::setRunMode( &repeat, objActivity );
					else
						DSTCWorkSession::setRunMode( &repeat, listObjActivity );
					pDataReq->addRepeat( repeat );
					unsigned long rptCount = pDataReq->getRepeatCount();
					pDataReq->setElementValue( ifds::RepeatCount, DString::asString( rptCount ), false, false );

				}
				++iterList;
			 }  // while loop
		}
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool DSTCAMSLmtTrxnBuilder::AMSUpdated ( BFAbstractCBO* pCBO, BF_OBJ_ACTIVITY ObjActivity, bool recursive )
{
   bool iupdate ( false );

   if( pCBO == NULL )
   {
      iupdate = false;
   }
   else if( ObjActivity == OBJ_ACTIVITY_ADDED || pCBO->hasTransactionUpdates( recursive ) || ObjActivity == OBJ_ACTIVITY_DELETED )
   {
      iupdate = true;
   }

   return(iupdate);
}






















