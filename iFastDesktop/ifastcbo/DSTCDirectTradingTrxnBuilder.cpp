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
// ^FILE   : DSTCDSTCDirectTradingTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : January 21, 2003
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCDirectTradingTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCDirectTradingTrxnBuilder.hpp"

#include "DirectTrading.hpp"
#include "DirectTradingList.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0266_req.hpp>
#include <ifastdataimpl\dse_dstc0266_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0266_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DIRECT_TRADING_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME         = I_( "DSTCDirectTradingTrxnBuilder" );
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
SEVERITY DSTCDirectTradingTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);

   DirectTradingList  *pDirectTradingList  = NULL;


   if( pMFaccount )
   {
      DString dstAccountNum, dstTrnKey, dstKeyTypes;
      pMFaccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST, true );
      addIDITagValue( dstTrnKey,   TRXNTAG::DIRECTTRADINGTAG, dstAccountNum.stripLeading('0').strip() );

      HostTransactionContainerIterator iterTrxnContList( pTrCont );

      iterTrxnContList.walkStrKey( dstTrnKey );
      iterTrxnContList.walkTrxnGroup( NO_GROUP );
      iterTrxnContList.walkTrxnSubType( 0 );

      if (pMFaccount->getDirectTradingList(pDirectTradingList, BF::HOST, false) <= WARNING && pDirectTradingList)
      {
         BFData *pDataReq = NULL;
         BFData *pDataRes = NULL;

         BFObjIter iter( *pDirectTradingList, BF::HOST );
         DirectTrading* pDirectTrading = NULL;

         iter.begin();
         while( !iter.end() )
         {
            pDirectTrading = dynamic_cast<DirectTrading*>( iter.getObject() );

            if( iter.hasTransactionUpdates() )
            {
               iterTrxnContList.begin();

               //fill in the fixed area
               if( iterTrxnContList.end() )
               {
				  //TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_DIRECT_TRADING : UPDATE_DIRECT_TRADING;

                  pDataReq = new BFData( ifds::DSTC0266_REQ );
                  pDataRes = new BFData( ifds::DSTC0266_VW );

                  DString strTrack, strActivity;

                  pDirectTradingList->getTrackActivity(strTrack,strActivity);         
                  pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                  pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                  //fill in the request update
                  DString mgmtCoId;
                  workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

                  pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
                  pDataReq->setElementValue( ifds::AccountNum, dstAccountNum );

                  JData *jdata = new JData( DSTC_REQUEST::DIRECT_TRADING_UPDATE, pDataReq, pDataRes );
                  pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
               }
               else
                  pDataRes = (*iterTrxnContList)->getRequestDataObject();


               //create a repeat for the request and fill it in
               BFData repeat( ifds::DSTC0266_REQRepeat_Record);
               
               //fill in the request update
               pDirectTrading->getData( repeat, BF::HOST );

               //set the RunMode field 
               DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity() );

               //add the lDataRepeat to the request
               pDataReq->addRepeat( repeat );
               DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
               pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
            }
            //move to the next AcctMailingOverride
            ++iter;
         } //meaning we have at least one AcctMailingOverride
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDirectTradingTrxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:32:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Oct 16 2003 12:17:32   FENGYONG
// PET809 FN08 Direct Trading enhancement
// 
//    Rev 1.0   Oct 08 2003 10:53:00   FENGYONG
// Initial Revision
// 
 */