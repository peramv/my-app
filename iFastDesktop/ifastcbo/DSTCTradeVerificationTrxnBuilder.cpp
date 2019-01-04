//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DSTCTradeVerificationTrxnBuilder.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : JuLY 22 2014
//
//********************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0463_req.hpp>
#include <ifastdataimpl\dse_dstc0463_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0463_vw.hpp>
#include <ifastdataimpl\dse_dstc0463_vwrepeat_record.hpp>
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCNonListTrxnBuilder.hpp"
#include "DSTCTradeVerificationTrxnBuilder.hpp"
#include "TradeVerificationList.hpp"
#include "TradeVerificationSearch.hpp"
#include "TradeVerification.hpp"
#include "TradeVerificationErrorList.hpp"
#include "TradeVerificationError.hpp"
#include "mgmtco.hpp"
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADE_VERIFICATION_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME                    = I_ ("DSTCTradeVerificationTrxnBuilder");
   const I_CHAR* YES                          = I_("Y") ;
}
namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId  TransNum;
   extern CLASS_IMPORT const BFTextFieldId     VerifyAll;
   extern CLASS_IMPORT const BFTextFieldId     DeleteAll;
   extern CLASS_IMPORT const BFTextFieldId      RunMode;
}

static int countofVerifiedDeletedTrades = 0;

void DSTCTradeVerificationTrxnBuilder::buildTrxnKey(DString& dstrKey, TradeVerification *pTradeVerification)
{
  MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTrxnKey"));

  DString dstrTransNum;
  addIDITagValue( dstrKey, TRXNTAG::TRADEVERIFICATION, TRXNTAG::TRADEVERIFICATION );
  pTradeVerification->getField(ifds::TransNum, dstrTransNum, BF::HOST, true);  
  addIDITagValue( dstrKey, TRXNTAG::TRADEVERIFICATION, dstrTransNum );
  addIDITagValue( dstrKey, TRXNTAG::TRADEVERIFICATION, DString::asString( countofVerifiedDeletedTrades ) );
}

SEVERITY DSTCTradeVerificationTrxnBuilder:: buildTransactions( DSTCWorkSession &workSession, 
                                                               BFAbstractCBO* pBFCBO, 
                                                               HostTransactionContainer* pTrxnContainer,
                                                               BF_OBJ_ACTIVITY objActivity)
{
  MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));

  TradeVerificationSearch* pTradeVerificationSearch;
  workSession.getTradeVerificationSearchCriteria(pTradeVerificationSearch, BF::HOST, false);


  if(pTradeVerificationSearch )
  {
    TradeVerificationList* pTradeVerificationList; 

    if( pTradeVerificationSearch->getTradeVerificationList(pTradeVerificationList, BF::HOST, false ) <= WARNING &&
        pTradeVerificationList)
    { 
       BFObjIter bfIter( *pTradeVerificationList, BF::HOST );   
       int count = bfIter.getNumberOfItemsInList();
       //Move itreator to end..
       DString dstrkey;
       bfIter.getLastObject(dstrkey);
       bfIter.positionByKey(dstrkey);
       DString dstrLastTransNum;
       bool bTranscationUpdates = false;
       while (count )
       {
         TradeVerification* pTradeVerification = NULL; 
         pTradeVerification = dynamic_cast< TradeVerification* >( bfIter.getObject() );
         if( 1 == count && bfIter.hasTransactionUpdates())
         {
           pTradeVerification->getField(ifds::TransNum, dstrLastTransNum, BF::HOST);
           bTranscationUpdates = true;
           break; 
         }         
         if( bfIter.hasTransactionUpdates() )
         { 
           TradeVerification* pTradeVerification = NULL; 
           pTradeVerification = dynamic_cast< TradeVerification* >( bfIter.getObject() );
           pTradeVerification->getField(ifds::TransNum, dstrLastTransNum, BF::HOST);
           bTranscationUpdates = true;
           break; 
         }
         --bfIter;
         --count;
        }
       bfIter.begin(); 
       while (!bfIter.end() && bTranscationUpdates )//We already identified if has an updated transaction , so avoid itreating next loop if not
       {
          if(bfIter.hasTransactionUpdates())
          {
               TradeVerification* pTradeVerification = NULL; 
               pTradeVerification = dynamic_cast< TradeVerification* >( bfIter.getObject() );
               DSTCNonListTrxnBuilder<TradeVerification*> tradeVerificationTrxnBuilder;
               TRXNINFO tradeVerificationTrxnInfo( I_("TradeVerification"), 
                                                   DSTC_REQUEST::TRADE_VERIFICATION_UPDATE,
                                                   ifds::DSTC0463_REQ,
                                                   ifds::DSTC0463_VW  );
               DString dstrTag;
               pTradeVerification->getField( ifds::TransNum, dstrTag, BF::HOST);
               pTradeVerification->setField( ifds::LastTransNumInSetofReq, dstrLastTransNum, BF::HOST, false, false, false);
               tradeVerificationTrxnBuilder.buildTransactions(workSession, pTrxnContainer, pTradeVerification, tradeVerificationTrxnInfo , dstrTag );              
          }
           ++bfIter;
       }
   }
 }
 return GETCURRENTHIGHESTSEVERITY();     
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DSTCTradeVerificationTrxnBuilder.cpp-arc  $
// 
//    Rev 1.0  22 July 2014
// Initial revision.
*/
