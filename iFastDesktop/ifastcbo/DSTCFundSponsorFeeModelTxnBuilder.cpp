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
// ^FILE   : DSTCFundSponsorFeeModelTxnBuilder.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : August 11, 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCFundSponsorFeeModelTxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "DSTCFundSponsorFeeModelTxnBuilder.hpp"
#include <ifastdataimpl\dse_dstc0308_req.hpp>
#include <ifastdataimpl\dse_dstc0308_vw.hpp>
#include "mgmtco.hpp"
#include "FundSponsorFeeModel.hpp"
#include "FundSponsorFeeModelList.hpp"
#include "DSTCFundSponsorFeeTxnBuilder.hpp"
#include "ifasthosttransactioncontainer.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUNDSPONSOR_FEE_MODEL_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCFundSponsorFeeModelTxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
}





int DSTCFundSponsorFeeModelTxnBuilder::buildIndex = 0;


//******************************************************************************

void DSTCFundSponsorFeeModelTxnBuilder::buildTrxnKey( DString& strKey, BFCBO* pCBO  )
{

   DString dstrFundSponsor,dstrFeeModelCode;
   pCBO->getField( ifds::FeeModelCode, dstrFeeModelCode, BF::HOST, false );
   dstrFeeModelCode.strip();
   addIDITagValue( strKey, TRXNTAG::FEEMODELTAG, dstrFeeModelCode );
   pCBO->getField( ifds::FundGroup, dstrFundSponsor, BF::HOST, false );
   dstrFundSponsor.strip();
   addIDITagValue( strKey, TRXNTAG::FUNDSPONSORTAG, dstrFundSponsor );

}

//******************************************************************************
SEVERITY DSTCFundSponsorFeeModelTxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                     BFAbstractCBO* pObj, 
                                                     HostTransactionContainer* pTrCont,
																	  BF_OBJ_ACTIVITY objActivity
																	  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   FundSponsorFeeModelList* pFundSponsorFeeModelList = dynamic_cast<FundSponsorFeeModelList*>(pObj);

   if( pFundSponsorFeeModelList )
   {
         BFObjIter iterList( *pFundSponsorFeeModelList, BF::HOST );
         while( !iterList.end() )
         {
            FundSponsorFeeModel* pFundSponsorFeeModel = dynamic_cast<FundSponsorFeeModel*>( iterList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterList.getKey().getActivity();

            if( pFundSponsorFeeModel != NULL && (listObjActivity == OBJ_ACTIVITY_ADDED 
										|| pFundSponsorFeeModel->hasTransactionUpdates(false ) 
										|| listObjActivity == OBJ_ACTIVITY_DELETED ) )
            {

               DString strKey;

               BFData *request = new BFData( ifds::DSTC0308_REQ );
               BFData *response = new BFData( ifds::DSTC0308_VW );
               DString strTrack, strActivity;
               pFundSponsorFeeModelList->getTrackActivity(strTrack,strActivity);                     
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strActivity, false, false );

               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );

               int count = 0;

               DSTCFundSponsorFeeModelTxnBuilder::buildTrxnKey( strKey, pFundSponsorFeeModel );

               //define an iterator on the HostTransactionContainer
               HostTransactionContainerIterator iterTrxnContList( pTrCont );

               // look for the systematic record in the HostTransactionContainer
               iterTrxnContList.walkStrKey( strKey );
               //the trxn hasn't been handled yet, no group and sub type set,
               iterTrxnContList.walkTrxnGroup( NO_GROUP );
               iterTrxnContList.walkTrxnSubType( 0 );
               iterTrxnContList.begin();

               pFundSponsorFeeModel->getData( *request, BF::HOST ); 
               DSTCWorkSession::setRunMode( request, listObjActivity );
			      DString keyTypes; 
               JData *jdata = new JData( DSTC_REQUEST::FUNDSPONSOR_FEE_MODEL_UPDATE, request, response );
               pTrCont->addTransaction( strKey, jdata, listObjActivity, NOT_PERSISTENT, 
				   keyTypes,NO_GROUP );

            }
                   // builder fee transaction here
			   DSTCFundSponsorFeeTxnBuilder::buildTransactions( workSession,
									pFundSponsorFeeModel,pTrCont );            
				
				++iterList;        
         }
      }//end of if pFundSponsorFeeModelList	

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFundSponsorFeeModelTxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:32:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 15 2004 15:20:34   YINGBAOL
// PET1117: when user update the child, desktop should not build the parent.
// 
//    Rev 1.0   Sep 07 2004 14:06:48   YINGBAOL
// Initial revision.

*/