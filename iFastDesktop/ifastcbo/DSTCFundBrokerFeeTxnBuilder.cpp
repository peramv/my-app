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
//    Copyright 2004 by Internantial Financial
//
//
//******************************************************************************
//
// ^FILE   : DSTCFundBrokerFeeTxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : August 11, 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCFundBrokerFeeTxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "DSTCFundBrokerFeeTxnBuilder.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0232_req.hpp>
#include <ifastdataimpl\dse_dstc0232_vw.hpp>
#include <ifastdataimpl\dse_dstc0307_vw.hpp>

#include "FundBrokerFeeList.hpp"
#include "FundBrokerFee.hpp"
#include "FundBroker.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCFundBrokerFeeTxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundBrokerCode;

}



int DSTCFundBrokerFeeTxnBuilder::buildIndex = 0;


//******************************************************************************

void DSTCFundBrokerFeeTxnBuilder::buildTrxnKey( DString& strKey,BFCBO* pParent, BFCBO* pObj  )
{
   DString dstrFeeCode;

   DString dstrFundBroker;
   pParent->getField( ifds::FundBrokerCode, dstrFundBroker, BF::HOST, false );
   dstrFundBroker.strip();
   addIDITagValue( strKey, TRXNTAG::FUNDBROKERTAG, dstrFundBroker );
   pObj->getField( ifds::FeeCode, dstrFeeCode, BF::HOST, false );
   dstrFeeCode.strip();
   addIDITagValue( strKey, TRXNTAG::FEETAG, dstrFeeCode );

   addIDITagValue( strKey, TRXNTAG::FEEPARAMSYSTAG, DString::asString( buildIndex++ ) );

}

//******************************************************************************
SEVERITY DSTCFundBrokerFeeTxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                     BFAbstractCBO* pObj, 
                                                     HostTransactionContainer* pTrCont,
																	  BF_OBJ_ACTIVITY objActivity
																	  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;

   FundBroker* pFundBroker = dynamic_cast<FundBroker*>(pObj);
   FundBrokerFeeList* pFundBrokerFeeList = NULL;

   if( pFundBroker )
   {
	   severity = pFundBroker->getFundBrokerFeeList(pFundBrokerFeeList,BF::HOST,false);		  
      int count = 0;
      if( pFundBrokerFeeList != NULL && severity <= WARNING )
      {


         BFObjIter iterFeeList( *pFundBrokerFeeList, BF::HOST );
         while( !iterFeeList.end() )
         {
            FundBrokerFee* pFeeObj = dynamic_cast<FundBrokerFee*>( iterFeeList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterFeeList.getKey().getActivity();

            if( pFeeObj != NULL && (listObjActivity == OBJ_ACTIVITY_ADDED || pFeeObj->hasTransactionUpdates( ) || listObjActivity == OBJ_ACTIVITY_DELETED ) )
            {

               DString strKey;

               BFData *request = new BFData( ifds::DSTC0232_REQ );
               BFData *response = new BFData( ifds::DSTC0232_VW );
               DString strTrack, strActivity;
               pFundBrokerFeeList->getTrackActivity(strTrack,strActivity);                     
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strActivity, false, false );
               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );

               int count = 0;

               DSTCFundBrokerFeeTxnBuilder::buildTrxnKey( strKey, pFundBroker,pFeeObj );

               //define an iterator on the HostTransactionContainer
               HostTransactionContainerIterator iterTrxnContList( pTrCont );

               // look for the systematic record in the HostTransactionContainer
               iterTrxnContList.walkStrKey( strKey );
               //the trxn hasn't been handled yet, no group and sub type set,
               iterTrxnContList.walkTrxnGroup( NO_GROUP );
               iterTrxnContList.walkTrxnSubType( 0 );
               iterTrxnContList.begin();

               pFeeObj->getData( *request, BF::HOST ); 
               DSTCWorkSession::setRunMode( request, listObjActivity );
               DString keyTypes;

               JData *jdata = new JData( DSTC_REQUEST::FEE_PARAM_SYSTEM_UPDATE, request, response );
               pTrCont->addTransaction( strKey, 
				   jdata, listObjActivity, 
				   NOT_PERSISTENT, 
				   keyTypes );
/*
               FeeScaleBaseList *pFeeScaleList = NULL;

               SEVERITY sevRtn1 = pFeeObj->getFeeScaleList( pFeeScaleList, BF::HOST,false );                     
               severity = std::max( severity, sevRtn1 );
               if( pFeeScaleList != NULL &&  severity <= WARNING )
               {
                  BFObjIter iterFeeScaleList( *pFeeScaleList, BF::HOST );
                  while( !iterFeeScaleList.end() )
                  {
                     FeeScaleSys* pFeeScaleSys = dynamic_cast<FeeScaleSys*>( iterFeeScaleList.getObject() );
                     BF_OBJ_ACTIVITY listObjActivityChild = iterFeeScaleList.getKey().getActivity();
                     if( pFeeScaleSys != NULL && (listObjActivityChild == OBJ_ACTIVITY_ADDED || 
                                               pFeeScaleSys->hasTransactionUpdates( ) || listObjActivityChild == OBJ_ACTIVITY_DELETED ) )
                     {
                        BFData dataRepeat(ifds::DSTC0232_REQRepeat_Record);

                        pFeeScaleSys->getData(dataRepeat, BF::HOST);

                        DString dstrRunMode = 
                        DSTCWorkSession::getRunMode( listObjActivityChild, pFeeScaleSys->hasTransactionUpdates( ));                                      

                        dataRepeat.setElementValue( ifds::ScaleRunMode,dstrRunMode );
                        DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );
                        request->addRepeat(dataRepeat);
                        ++ count; 

                     }
                     ++iterFeeScaleList;
                  } //while FeeScaleList iterater  
                  request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
               }
*/
            }
            ++iterFeeList;        
         }// end of while iterFeeParamList
      }//end of if pFeeParamList	
   }//end of if pMFAccount

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFundBrokerFeeTxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:32:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Nov 02 2004 16:03:06   FENGYONG
// Initial revision.
// 
/
// 

*/