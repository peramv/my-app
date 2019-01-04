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
// ^FILE   : DSTCAMSTrxnBuilder.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov.  15,2002 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAMSTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcAMStrxnbuilder.hpp"
#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0219_req.hpp>
#include <ifastdataimpl\dse_dstc0219_vw.hpp>

#include "AmsMstrInfo.hpp"
#include "AmsMstrList.hpp"
#include "AmsFundAlloc.hpp"
#include "AmsFundAllocList.hpp"
#include "dstcamslmttrxnbuilder.hpp"
#include "DSTCAMSDeltaTrxnBuilder.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_INFO_UPDATE;
   extern CLASS_IMPORT const DSTCRequest AMS_LMT_OVERRIDE_LIST_UPDATE;

}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAMSTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
   const I_CHAR * const CFDS = I_("Canada");
//	const I_CHAR * const AMSCODE = I_("AmsCode");

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
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}


int DSTCAMSTrxnBuilder::buildIndex = 0;

//******************************************************************************

void DSTCAMSTrxnBuilder::buildTrxnKey( DString& strKey, AmsMstrInfo* amsmstrinfo )
{
   DString dstrAmsCode;

   if(amsmstrinfo){
		amsmstrinfo->getField( ifds::AMSCode, dstrAmsCode, BF::HOST, true );
		dstrAmsCode.strip();
		addIDITagValue( strKey, TRXNTAG::AMSCODETAG, dstrAmsCode );
	}
	addIDITagValue( strKey, TRXNTAG::AMSMSTRINFOTAG, DString::asString( buildIndex++ ) );

}




//******************************************************************************
SEVERITY DSTCAMSTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                     BFAbstractCBO* pObj,
                                                     HostTransactionContainer* pTrCont, 
                                                     BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   AMSMstrList* pAMSMstrList = dynamic_cast<AMSMstrList*>(pObj);

   if( pAMSMstrList != NULL )
   {
      bool bAmsUpdate( false );

          //define an iterator on the 
         BFObjIter iterList( *pAMSMstrList, BF::HOST );

         DString keyString;
         DSTCAMSTrxnBuilder::buildTrxnKey( keyString, NULL );

         //define an iterator on the HostTransactionContainer
         HostTransactionContainerIterator iterTrxnContList( pTrCont );
         //set filter to look for distribution fixed area
         iterTrxnContList.walkStrKey( keyString );
         //the trxn hasn't been handled yet, no group and sub type set,
         iterTrxnContList.walkTrxnGroup( NO_GROUP );
         iterTrxnContList.walkTrxnSubType( 0 );


         while( !iterList.end() )
         {
            AmsMstrInfo* pAmsMstrInfo = dynamic_cast<AmsMstrInfo*>( iterList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterList.getKey().getActivity();

           
            bAmsUpdate = AMSUpdated ( pAmsMstrInfo, listObjActivity, true );

            BFData * pDataReq = NULL;
            BFData * pDataRes = NULL;

            if( bAmsUpdate )
            {
               iterTrxnContList.begin();
               // If first update then update fix area : build key and add transaction
               if( iterTrxnContList.end() )
               {

                  pDataReq = new BFData( ifds::DSTC0219_REQ );
                  pDataRes = new BFData( ifds::DSTC0219_VW );

                  DString strTrack,strActivity;
                  pAMSMstrList->getTrackActivity(strTrack, strActivity);
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                  //fill in the request update
                  pAmsMstrInfo->getData( *pDataReq, BF::HOST );

                  DSTCWorkSession::setRunMode(pDataReq, listObjActivity);
                  DString dstStrKey;
                  DSTCAMSTrxnBuilder::buildTrxnKey( dstStrKey, pAmsMstrInfo );

                  DString keyTypes;
                 // addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::AMS_INFO_UPDATE, pDataReq, pDataRes);
                  pTrCont->addTransaction( dstStrKey, jdata, listObjActivity, NOT_PERSISTENT, keyTypes );
               }  // if first object on the update list
               else
               {
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();
               }

               AmsFundAllocList* pAllocList = NULL;

               SEVERITY sev1 = pAmsMstrInfo->getAMSFundAllocList( pAllocList, BF::HOST, false );


               if( pAllocList != NULL )
               {
                  BFObjIter iterAllocList( *pAllocList, BF::HOST );

                  while( !iterAllocList.end() )
                  {
                     AmsFundAlloc* pAmsFundAlloc = dynamic_cast<AmsFundAlloc*>( iterAllocList.getObject() );
                     BF_OBJ_ACTIVITY FundToObjActivity = iterAllocList.getKey().getActivity();

                     bool bUpdated = AMSUpdated ( pAmsFundAlloc, FundToObjActivity );

                     if( bUpdated || listObjActivity == OBJ_ACTIVITY_DELETED || bUpdated )
                     {
                        //create a repeat for the request and filled in
                        BFData repeat( ifds::DSTC0219_REQRepeat_Record );


                        pAmsFundAlloc->getData( repeat, BF::HOST );


                        if( listObjActivity == OBJ_ACTIVITY_DELETED )
                        {
                           repeat.setElementValue( ifds::AllocRunMode, RUNMODE::DELETED );
                        }
                        else
                        {
                           if( FundToObjActivity == OBJ_ACTIVITY_NONE )
                              repeat.setElementValue( ifds::AllocRunMode, RUNMODE::MODIFIED );
                           else if( FundToObjActivity == OBJ_ACTIVITY_ADDED )
                              repeat.setElementValue( ifds::AllocRunMode, RUNMODE::ADDED );
                           else if( FundToObjActivity == OBJ_ACTIVITY_DELETED )
                              repeat.setElementValue( ifds::AllocRunMode, RUNMODE::DELETED );
                           else
                           {
                              //shouldn't get here
                              assert( 0 );
                              throw;
                           }
                        }

                        pDataReq->addRepeat( repeat );
                        pDataReq->setElementValue( ifds::RepeatCount, DString::asString( pDataReq->getRepeatCount() ) );
                     }
                     ++iterAllocList;
                  }
               }
            }
			DSTCAMSLmtTrxnBuilder::buildTransactions(workSession, pAmsMstrInfo, pTrCont, listObjActivity);
			DSTCAMSDeltaTrxnBuilder::buildTransactions(workSession, pAmsMstrInfo,pTrCont, listObjActivity);
            ++iterList;
         }  // while loop
		}
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool DSTCAMSTrxnBuilder::AMSUpdated ( BFAbstractCBO* pCBO, BF_OBJ_ACTIVITY ObjActivity, bool recursive )
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






















