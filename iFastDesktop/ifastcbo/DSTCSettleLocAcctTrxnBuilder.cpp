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
// ^FILE   : DSTCSettleLocAcctTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCSettleLocAcctTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCSettleLocAcctTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "SettleLocationAcctLvlList.hpp"
#include "SettleLocationAcctLvl.hpp"
#include "MFAccount.hpp"

#include <dataimpl\dse_dstc0274_req.hpp>
#include <dataimpl\dse_dstc0274_reqrepeat_record.hpp>
#include <dataimpl\dse_dstc0274_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLE_LOCATION_ACCT_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCSettleLocAcctTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCSettleLocAcctTrxnBuilder::buildTrxnKey( DString& dstrKey ) 
{
}

//******************************************************************************

SEVERITY DSTCSettleLocAcctTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

   if( pMFAccount != NULL )
   {
      DString dstrAccountNum, dstTrnKey, dstKeyTypes;
      pMFAccount->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
      addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );
      iterTrxnContList.walkStrKey( dstTrnKey );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      SettleLocationAcctLvlList *pSettleLocationAcctLvlList = NULL;
      severity = pMFAccount->getSettlementLocationAcctLvlList( pSettleLocationAcctLvlList, BF::HOST, false );

      if( pSettleLocationAcctLvlList != NULL && severity <= WARNING )
      {
         BFData *pDataReq = NULL;
         BFData *pDataRes = NULL;

         BFObjIter iterSettleLocationAcctLvlList( *pSettleLocationAcctLvlList, BF::HOST );
         SettleLocationAcctLvl* pSettleLocationAcctLvl = NULL;

         iterSettleLocationAcctLvlList.begin();
         while( !iterSettleLocationAcctLvlList.end() )
         {
            pSettleLocationAcctLvl = dynamic_cast<SettleLocationAcctLvl*>( iterSettleLocationAcctLvlList.getObject() );

            if( iterSettleLocationAcctLvlList.hasTransactionUpdates( ) )
            {
               iterTrxnContList.begin();
               if( iterTrxnContList.end() )
               {
                  pDataReq = new BFData( ifds::DSTC0274_REQ );
                  pDataRes = new BFData( ifds::DSTC0274_VW );

                  DString strTrack, strActivity;
                  pSettleLocationAcctLvlList->getTrackActivity( strTrack, strActivity );          
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
                  pDataReq->setElementValue( ifds::AccountNum, dstrAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::SETTLE_LOCATION_ACCT_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
               }
               else
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();

               BFData lDataRepeat( ifds::DSTC0274_REQRepeat_Record );
               pSettleLocationAcctLvl->getData( lDataRepeat, BF::HOST );
               DSTCWorkSession::setRunMode( &lDataRepeat, iterSettleLocationAcctLvlList.getKey().getActivity() );

               pDataReq->addRepeat( lDataRepeat );
               DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
               pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
            }
            ++iterSettleLocationAcctLvlList;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCSettleLocAcctTrxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:33:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Nov 24 2003 18:17:08   HERNANDO
// Next revision.
// 
//    Rev 1.0   Nov 20 2003 11:08:24   HERNANDO
// Initial revision.
//
