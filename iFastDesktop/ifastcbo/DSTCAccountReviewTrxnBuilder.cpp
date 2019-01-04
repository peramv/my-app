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
// ^FILE   : DSTCAccountReviewTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAccountReviewTRXNBUILDER
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcaccountreviewtrxnbuilder.hpp"
#include "accountreview.hpp"
#include "accountreviewlist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0205_req.hpp>
#include <ifastdataimpl\dse_dstc0205_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNTREVIEW_LIST_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAccountReviewTrxnBuilder" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************

SEVERITY DSTCAccountReviewTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

   if( pMFAccount != NULL )
   {
      DString dstrAccountNum, dstTrnKey, dstKeyTypes;
      pMFAccount->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
      addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );
      //set filter to look for Entity fixed area
      iterTrxnContList.walkStrKey( dstTrnKey );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      AccountReviewList* pAccountReviewList = NULL;

      //if no list do not go and get one from the database
      severity = pMFAccount->getAccountReviewList( pAccountReviewList, BF::HOST, false );

      if( pAccountReviewList != NULL && severity <= WARNING )
      {
         BFData *pDataReq = NULL;
         BFData *pDataRes = NULL;

         BFObjIter iterAccountReviewList( *pAccountReviewList, BF::HOST );
         AccountReview* pAccountReview = NULL;

         iterAccountReviewList.begin();
         while( !iterAccountReviewList.end() )
         {
            //in case of a list the obj_activity is known only by the list,
            //so ask the key about it
            pAccountReview = dynamic_cast<AccountReview*>( iterAccountReviewList.getObject() );

            if( iterAccountReviewList.hasTransactionUpdates( ) )
            {
               iterTrxnContList.begin();
               //fill in the fixed area
               if( iterTrxnContList.end() )
               {
                  pDataReq = new BFData( ifds::DSTC0205_REQ );
                  pDataRes = new BFData( ifds::DSTC0205_VW );

                  DString strTrack, strActivity;
                  pAccountReviewList->getTrackActivity(strTrack,strActivity);          
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
                  pDataReq->setElementValue( ifds::AccountNum, dstrAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::ACCOUNTREVIEW_LIST_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
               }
               else
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();

               //create a repeat for the request and filled it in
               BFData lDataRepeat( ifds::DSTC0205_REQRepeat_Record );

               //fill in the request update, only the part for which the Account Review is responsible
               pAccountReview->getData( lDataRepeat, BF::HOST );

               //set the RunMode field
               DSTCWorkSession::setRunMode( &lDataRepeat, iterAccountReviewList.getKey().getActivity() );

               //add the lDataRepeat to the request
               pDataReq->addRepeat( lDataRepeat );
               DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
               pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
            }
            ++iterAccountReviewList;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAccountReviewTrxnBuilder.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:31:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 18:03:32   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:54:14   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:55:18   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   31 May 2002 13:49:40   HERNANDO
// Revised for Rel47.
// 
//    Rev 1.1   22 May 2002 18:26:48   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   08 May 2002 18:07:44   HERNANDO
// Initial revision.
// 
*/