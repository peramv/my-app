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
// ^FILE   : DSTCFundSponsorFeeTxnBuilder.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : August 11, 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCFundSponsorFeeTxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "DSTCFundSponsorFeeTxnBuilder.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0232_req.hpp>
#include <ifastdataimpl\dse_dstc0232_vw.hpp>
#include <ifastdataimpl\dse_dstc0307_vw.hpp>

#include "FundSponsorFeeList.hpp"
#include "FundSponsorFee.hpp"
#include "FundSponsorFeeModel.hpp"
#include "FeeScaleSys.hpp"
#include "FeeScaleSysList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCFundSponsorFeeTxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundGroup;

}



int DSTCFundSponsorFeeTxnBuilder::buildIndex = 0;


//******************************************************************************

void DSTCFundSponsorFeeTxnBuilder::buildTrxnKey( DString& strKey,BFCBO* pParent, BFCBO* pObj  )
{
   DString dstrFeeCode;

   DString dstrFundSponsor,dstrFeeModelCode;
   pParent->getField( ifds::FeeModelCode, dstrFeeModelCode, BF::HOST, false );
   dstrFeeModelCode.strip();
   addIDITagValue( strKey, TRXNTAG::FEEMODELTAG, dstrFeeModelCode );
   pParent->getField( ifds::FundGroup, dstrFundSponsor, BF::HOST, false );
   dstrFundSponsor.strip();
   addIDITagValue( strKey, TRXNTAG::FUNDSPONSORTAG, dstrFundSponsor );
   pObj->getField( ifds::FeeCode, dstrFeeCode, BF::HOST, false );
   dstrFeeCode.strip();
   addIDITagValue( strKey, TRXNTAG::FEETAG, dstrFeeCode );

   addIDITagValue( strKey, TRXNTAG::FEEPARAMSYSTAG, DString::asString( buildIndex++ ) );

}

//******************************************************************************
SEVERITY DSTCFundSponsorFeeTxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                     BFAbstractCBO* pObj, 
                                                     HostTransactionContainer* pTrCont,
																	  BF_OBJ_ACTIVITY objActivity
																	  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   DString  dstrFeeModelId;
   FundSponsorFeeModel* pFundSponsorFeeModel = dynamic_cast<FundSponsorFeeModel*>(pObj);
   pFundSponsorFeeModel->getField(ifds::FundSpFMRid,dstrFeeModelId,BF::HOST,false);
   dstrFeeModelId.strip();
  
   FundSponsorFeeList* pFundSponsorFeeList = NULL;

   if( pFundSponsorFeeModel )
   {
	  severity = pFundSponsorFeeModel->getFundSponsorFeeList(pFundSponsorFeeList,BF::HOST,false);		  
      int count = 0;
      if( pFundSponsorFeeList != NULL && severity <= WARNING )
      {


         BFObjIter iterFeeList( *pFundSponsorFeeList, BF::HOST );
         while( !iterFeeList.end() )
         {
            FundSponsorFee* pFeeObj = dynamic_cast<FundSponsorFee*>( iterFeeList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterFeeList.getKey().getActivity();

            if( pFeeObj != NULL && (listObjActivity == OBJ_ACTIVITY_ADDED || pFeeObj->hasTransactionUpdates( ) || listObjActivity == OBJ_ACTIVITY_DELETED ) )
            {

               DString strKey;

               BFData *request = new BFData( ifds::DSTC0232_REQ );
               BFData *response = new BFData( ifds::DSTC0232_VW );
               DString strTrack, strActivity;
               pFundSponsorFeeList->getTrackActivity(strTrack,strActivity);                     
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strActivity, false, false );
               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );

               int count = 0;

               DSTCFundSponsorFeeTxnBuilder::buildTrxnKey( strKey, pFundSponsorFeeModel,pFeeObj );

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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFundSponsorFeeTxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:32:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 13 2004 14:12:08   YINGBAOL
// PET1117: fix Null point
// 
//    Rev 1.0   Sep 07 2004 14:07:50   YINGBAOL
// Initial revision.
// 
/
// 

*/