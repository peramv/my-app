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
//    Copyright 2002, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : DSTCSettlementTrxnBuilder.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : June 3,2002
//
// ^CLASS    : DSTCSettlementTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCSettlementTrxnBuilder.hpp"
#include "SettlementTradeList.hpp"
#include "SettlementTrade.hpp"
#include "Settlement.hpp"
#include "SettlementTotalList.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0201_req.hpp>
#include <ifastdataimpl\dse_dstc0201_vw.hpp>
#include <ifastdataimpl\dse_dstc0201_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0208_req.hpp>
#include <ifastdataimpl\dse_dstc0208_vw.hpp>
#include <ifastdataimpl\dse_dstc0208_reqrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLEMENT_UPDATE;
   extern CLASS_IMPORT const DSTCRequest SETTLEMENT_MAIN;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCSettlementTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
//   extern CLASS_IMPORT const BFTextFieldId rxCompCode;
//   extern CLASS_IMPORT const BFNumericFieldId Settled;
     extern CLASS_IMPORT const BFDecimalFieldId NetTotalSettle;
     extern CLASS_IMPORT const BFTextFieldId rxBatchName;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const TRANSID;
}

int contorChangedTrades = 0;
int contorUnchangedTrades = 0;


//******************************************************************************
void DSTCSettlementTrxnBuilder::buildTrxnKeyForChangedTrades( DSTCWorkSession &workSession,
                                                              DString& strKey, 
                                                              SettlementTrade* settl )
{
   DString str( I_( "ChangedTrade" ) );
   strKey = I_( "" );

   addIDITagValue( strKey, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG );
   addIDITagValue( strKey, TRXNTAG::SETTLEMENTTAG, str );
   addIDITagValue( strKey, TRXNTAG::SETTLEMENTTAG, DString::asString( contorChangedTrades ) );
}

//******************************************************************************
void DSTCSettlementTrxnBuilder::buildTrxnKeyForUnchangedTrades( DSTCWorkSession &workSession,
                                                                DString& strKey, 
                                                                SettlementTrade* settl )
{
   DString str( I_("UnchangedTrade" ) );
   strKey = I_( "" );

   addIDITagValue( strKey, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG );
   addIDITagValue( strKey, TRXNTAG::SETTLEMENTTAG, str );
   addIDITagValue( strKey, TRXNTAG::SETTLEMENTTAG, DString::asString( contorUnchangedTrades ) );
}

//******************************************************************************
SEVERITY DSTCSettlementTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY severity = SEVERE_ERROR;
   bool first_time = true;
   Settlement* pSettlement = dynamic_cast< Settlement* >(pObj);
   DString batchName;

   if( pSettlement )
   {
      SettlementTradeList *pSettlementTradeList;
      pSettlement->getSettlementTradeList( pSettlementTradeList, BF::HOST, false, false );
	  pSettlement->getField (ifds::rxBatchName, batchName, BF::HOST);
      DString settleAll;
      pSettlementTradeList->getField( ifds::SettleAll, settleAll, BF::HOST, false );
		settleAll.strip().upperCase();
      if( pSettlementTradeList )
      {
         BFObjIter bfIter( *pSettlementTradeList, BF::HOST );
         while( !bfIter.end() )
         {
            SettlementTrade* pSettlementTrade = dynamic_cast< SettlementTrade* >( bfIter.getObject() );
            BF_OBJ_ACTIVITY lObjActivity = bfIter.getKey().getActivity();
            DString settled; 
            pSettlementTrade->getField( ifds::Settled, settled, BF::HOST, false );
				settled.strip().upperCase();

            if( pSettlementTrade != NULL && pSettlementTrade->hasTransactionUpdates( false ) 
					||  settled == I_( "N" ) && settleAll == I_("Y")  )
            {


               pSettlementTrade->setSettledUpdated( BF::HOST, false ); // reset update status for Settled field
               // to find out if any other field has been updated

               //define an iterator on the HostTransactionContainer
               HostTransactionContainerIterator iterTrxnContList( pTrCont );
               DString keyString;

               bool hasUpdates = pSettlementTrade->hasTransactionUpdates( false );
               if( hasUpdates && settled == I_( "Y" ) )
               {
                  buildTrxnKeyForChangedTrades( workSession, keyString, pSettlementTrade );
                  //set filter to look for Entity fixed area
                  iterTrxnContList.walkStrKey( keyString );
                  //the trxn hasn't been handled yet, no group and sub type set,
                  iterTrxnContList.walkTrxnGroup( NO_GROUP );
                  iterTrxnContList.walkTrxnSubType( 0 );
                  //check if the fixed area of the 'Entity' update request is already in the HostTransactionContainer
                  iterTrxnContList.begin();

                  BFData* pDataReq = NULL;
                  BFData* pDataRes = NULL;

                  if( iterTrxnContList.end() )
                  // Fixed Area either does not exists, so create a new one
                  {
                     pDataReq   = new BFData( ifds::DSTC0201_REQ );
                     pDataRes   = new BFData( ifds::DSTC0201_VW );

                     DString strTrack,strActivity;
                     pSettlementTrade->getTrackActivity(strTrack,strActivity);
                     pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                     pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                     DString mgmtCoId;
                     workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                     pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                     DString keyTypes;
                     DString str( I_( "ChangedTrade" ) );

                     addIDITagValue( keyTypes, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG );
                     addIDITagValue( keyTypes, TRXNTAG::SETTLEMENTTAG, str );

                     TRXN_TYPE trxnType = UPDATE_SETTLEMENT;

                     //add the transaction to the container;
                     JData *jdata = new JData( DSTC_REQUEST::SETTLEMENT_UPDATE, pDataReq, pDataRes );
                     pTrCont->addTransaction( keyString, jdata, lObjActivity, trxnType, keyTypes );
                  }

                  else
                  {
                     pDataReq = (*iterTrxnContList)->getRequestDataObject();
                     unsigned long rptCount = pDataReq->getRepeatCount();
                     if( rptCount == 50 ) //if we reached 50 repeats then start a new transaction
                     {
                        contorChangedTrades++;
                                             // Fixed Area either does not exists, so create a new one
                        pDataReq   = new BFData( ifds::DSTC0201_REQ );
                        pDataRes   = new BFData( ifds::DSTC0201_VW );

                        DString strTrack,strActivity;
                        pSettlementTrade->getTrackActivity(strTrack,strActivity);
                        pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                        pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                        DString mgmtCoId;
                        workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                        pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                        DString keyTypes;
                        DString str( I_( "ChangedTrade" ) );                     

                        addIDITagValue( keyTypes, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG );
                        addIDITagValue( keyTypes, TRXNTAG::SETTLEMENTTAG, str );

                        TRXN_TYPE trxnType = UPDATE_SETTLEMENT;

                        //add the transaction to the container;
                        JData *jdata = new JData( DSTC_REQUEST::SETTLEMENT_UPDATE, pDataReq, pDataRes );
                        pTrCont->addTransaction( keyString, jdata, lObjActivity, trxnType, keyTypes );
                     }
                  }

                  //create a repeat for the request and filled in
                  BFData repeat( ifds::DSTC0201_REQRepeat_Record );
                  pSettlementTrade->getData( repeat, BF::HOST );
                  //set the enity id as well
                  DString transId;

                  //               pSettlementTrade->getField( ifds::TransId, transId, BF::HOST );
                  //               repeat.setElementValue( ifds::EntityId, entityId, false, false );
                  //add the repeat to the retrieved request
                  //set the RunMode field to the EntityUpdate trxn
                  DSTCWorkSession::setRunMode( &repeat, lObjActivity );
                  pDataReq->addRepeat( repeat );
                  unsigned long rptCount = pDataReq->getRepeatCount();
                  pDataReq->setElementValue( ifds::RepeatCount, DString::asString( rptCount ), false, false );
               }

               if( ( settleAll == I_( "Y" ) && settled == I_( "N" ) ) || ( settleAll == I_( "N" ) && settled == I_( "Y" ) )
                   || ( first_time && ( settleAll == I_( "Y" ) && settled == I_( "Y" ) ) ) )
               {
                  buildTrxnKeyForUnchangedTrades( workSession, keyString, pSettlementTrade );
                  //set filter to look for Entity fixed area
                  iterTrxnContList.walkStrKey( keyString );
                  //the trxn hasn't been handled yet, no group and sub type set,
                  iterTrxnContList.walkTrxnGroup( NO_GROUP );
                  iterTrxnContList.walkTrxnSubType( 0 );
                  //check if the fixed area of the 'Entity' update request is already in the HostTransactionContainer
                  iterTrxnContList.begin();

                  BFData* pDataReq = NULL;
                  BFData* pDataRes = NULL;

                  if( iterTrxnContList.end() )
                  // Fixed Area either does not exists, so create a new one
                  {
                     pDataReq   = new BFData( ifds::DSTC0208_REQ );
                     pDataRes   = new BFData( ifds::DSTC0208_VW );

                     DString strTrack,strActivity;
                     pSettlementTrade->getTrackActivity(strTrack,strActivity);
                     pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                     pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                     DString mgmtCoId;
                     workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                     pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                     DString str;
                     BFData& req = pSettlementTradeList->getRequestData();

                     //copy the search criteria used in view 200 into the request for 208
                     req.getElementValue( ifds::SearchType, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::SearchType, str, false, false );
                     DString dstrTotal=getNetSettlement(str,  pSettlement );
                     pDataReq->setElementValue( ifds::NetSettlement, dstrTotal, false, false );

                     req.getElementValue( ifds::RegAgentCode, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::RegAgentCode, str, false, false );

                     req.getElementValue( ifds::WireOrdNum, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::WireOrdNum, str, false, false );
                     req.getElementValue( ifds::TransNum, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::TransNum, str, false, false );
                     req.getElementValue( ifds::AccountNum, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::AccountNum, str, false, false );
                     req.getElementValue( ifds::TransType, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::TransType, str, false, false );
                     req.getElementValue( ifds::CompanyCode, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::CompanyCode, str, false, false );
                     req.getElementValue( ifds::BrokerCode, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::BrokerCode, str, false, false );
                     req.getElementValue( ifds::InterCode, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::InterCode, str, false, false );
                     req.getElementValue( ifds::FundCode, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::FundCode, str, false, false );
                     req.getElementValue( ifds::SettleCurrency, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::SettleCurrency, str, false, false );
                     req.getElementValue( ifds::TradeDate, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::TradeDate, str, false, false );
                     req.getElementValue( ifds::SettleDate, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::SettleDate, str, false, false );
							req.getElementValue( ifds::StartDate, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::StartDate, str, false, false );
                     							
							req.getElementValue( ifds::EndDate, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::EndDate, str, false, false );
                     req.getElementValue( ifds::VolSettleType, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::VolSettleType, str, false, false );

                     pDataReq->setElementValue( ifds::BatchName, batchName, false, false );
                     pDataReq->setElementValue( ifds::SettleAll, settleAll, false, false );

                     req.getElementValue( ifds::ExternalIdType, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::ExternalIdType, str, false, false );

							req.getElementValue( ifds::ExternalId, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::ExternalId, str, false, false );
					 req.getElementValue( ifds::ExcludeStopSettle, str );
                     str.strip();
                     pDataReq->setElementValue( ifds::ExcludeStopSettle, str, false, false );


                     DString keyTypes;
                     str = I_( "UnchangedTrade" );

                     addIDITagValue( keyTypes, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG );
                     addIDITagValue( keyTypes, TRXNTAG::SETTLEMENTTAG, str );

                     TRXN_TYPE trxnType = UPDATE_SETTLEMENT;

                     //add the transaction to the container;
                     JData *jdata = new JData( DSTC_REQUEST::SETTLEMENT_MAIN, pDataReq, pDataRes );
                     pTrCont->addTransaction( keyString, jdata, lObjActivity, trxnType, keyTypes );
                     first_time = false;
                  }
                  else
                  {
                     pDataReq = (*iterTrxnContList)->getRequestDataObject();
                     unsigned long rptCount = pDataReq->getRepeatCount();
                     if( rptCount == 3000 ) //if we reached 3000 repeats then start a new transaction
                     {
                        contorUnchangedTrades++;

                        // Fixed Area either does not exists, so create a new one
                        pDataReq   = new BFData( ifds::DSTC0208_REQ );
                        pDataRes   = new BFData( ifds::DSTC0208_VW );

                        DString strTrack,strActivity;
                        pSettlementTrade->getTrackActivity(strTrack,strActivity);
                        pDataReq->setElementValue( ifds::Track, strTrack, false, false );
                        pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

                        DString mgmtCoId;
                        workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
                        pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

                        DString str;
                        BFData& req = pSettlementTradeList->getRequestData();
                        //copy the search criteria used in view 200 into the request for 208
                        req.getElementValue( ifds::SearchType, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::SearchType, str, false, false );
                        DString dstrTotal=getNetSettlement(str,  pSettlement );
                        pDataReq->setElementValue( ifds::NetSettlement, dstrTotal, false, false );
                        req.getElementValue( ifds::WireOrdNum, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::WireOrdNum, str, false, false );
                        req.getElementValue( ifds::TransNum, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::TransNum, str, false, false );
                        req.getElementValue( ifds::AccountNum, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::AccountNum, str, false, false );
                        req.getElementValue( ifds::TransType, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::TransType, str, false, false );
                        req.getElementValue( ifds::CompanyCode, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::CompanyCode, str, false, false );
                        req.getElementValue( ifds::BrokerCode, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::BrokerCode, str, false, false );
                        req.getElementValue( ifds::InterCode, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::InterCode, str, false, false );
                        req.getElementValue( ifds::FundCode, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::FundCode, str, false, false );
                        req.getElementValue( ifds::SettleCurrency, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::SettleCurrency, str, false, false );
                        req.getElementValue( ifds::TradeDate, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::TradeDate, str, false, false );
                        req.getElementValue( ifds::SettleDate, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::SettleDate, str, false, false );
                     	req.getElementValue( ifds::StartDate, str );
								str.strip();
                        pDataReq->setElementValue( ifds::StartDate, str, false, false );
  								req.getElementValue( ifds::EndDate, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::EndDate, str, false, false );
                        req.getElementValue( ifds::VolSettleType, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::VolSettleType, str, false, false );

                        pDataReq->setElementValue( ifds::BatchName, batchName, false, false );
                        pDataReq->setElementValue( ifds::SettleAll, settleAll, false, false );

                        req.getElementValue( ifds::ExternalIdType, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::ExternalIdType, str, false, false );

						req.getElementValue( ifds::ExternalId, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::ExternalId, str, false, false );
						
						req.getElementValue( ifds::ExcludeStopSettle, str );
                        str.strip();
                        pDataReq->setElementValue( ifds::ExcludeStopSettle, str, false, false );

                        DString keyTypes;
                        str = I_( "UnchangedTrade" );

                        addIDITagValue( keyTypes, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG );
                        addIDITagValue( keyTypes, TRXNTAG::SETTLEMENTTAG, str );

                        TRXN_TYPE trxnType = UPDATE_SETTLEMENT;

                        //add the transaction to the container;
                        JData *jdata = new JData( DSTC_REQUEST::SETTLEMENT_MAIN, pDataReq, pDataRes );
                        pTrCont->addTransaction( keyString, jdata, lObjActivity, trxnType, keyTypes );
                     }

                  }

                  if( !( ( settleAll == I_( "Y" ) && settled == I_( "Y" ) ) ) )
                  {
                     //create a repeat for the request and filled in
                     BFData repeat( ifds::DSTC0208_REQRepeat_Record );
                     //pSettlementTrade->getData( repeat, BF::HOST );
                     //set the enity id as well
                     DString str;

                     pSettlementTrade->getField( ifds::TransId, str, BF::HOST );
                     repeat.setElementValue( ifds::TransId, str, false, false );
                     pSettlementTrade->getField( ifds::Settled, str, BF::HOST, false );
                     str.strip();
                     repeat.setElementValue( ifds::Settled, str, false, false );
                     pSettlementTrade->getField( ifds::TransType, str, BF::HOST, false );
                     str.strip();
                     repeat.setElementValue( ifds::IndTransType, str, false, false );
					 //Cash Date Field 
					 pSettlementTrade->getField( ifds::CashDate, str, BF::HOST, false);
					 repeat.setElementValue( ifds::CashDate, str, false, false );
                     //add the repeat to the retrieved request
                     //set the RunMode field to the EntityUpdate trxn
                     DSTCWorkSession::setRunMode( &repeat, lObjActivity );
                     pDataReq->addRepeat( repeat );
                  }
                  unsigned long rptCount = pDataReq->getRepeatCount();
                  pDataReq->setElementValue( ifds::RepeatCount, DString::asString( rptCount ), false, false );
               }
            }
            ++bfIter;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************
DString DSTCSettlementTrxnBuilder::getNetSettlement(DString& dstrSearchType, 
                                                    Settlement* pSettlement )
{
   DString dstrNetSettlement = I_("0.0");
   dstrSearchType.strip();
   if(dstrSearchType == I_( "BR" ) )  // broker settlement
   {
      if( pSettlement )
      {
         SettlementTotalList* pSettlementTotalList = NULL;
         if( pSettlement->getSettlementTotalList( pSettlementTotalList, BF::HOST,false,false)<= WARNING )
         {
            if( pSettlementTotalList )
            {
                BFObjIter iter( *pSettlementTotalList, BF::HOST );
                if( iter.getNumberOfItemsInList() == 1 )
                {
                   iter.getObject()->getField(ifds::NetTotalSettle,dstrNetSettlement,BF::HOST,false );
                   dstrNetSettlement.strip();
                }            
            }
         }                                   
      }
   }
   return dstrNetSettlement;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCSettlementTrxnBuilder.cpp-arc  $
// 
//    Rev 1.16   Apr 27 2012 09:53:20   if991250
// CPF - Account Setup & Settlement 
// 
//    Rev 1.15   May 12 2009 14:55:24   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.14   Mar 30 2007 14:04:58   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.12   Mar 21 2007 13:05:36   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.11   Dec 23 2004 14:46:00   yingbaol
// PTS10036615: send Netsettlement amount back to view.
// 
//    Rev 1.10   Dec 06 2004 17:25:14   vadeanum
// PTS10036548 - Missing External Id and External Id Type.
// 
//    Rev 1.9   Nov 14 2004 14:33:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Oct 20 2004 10:53:44   YINGBAOL
// PTS10034784:set StartDate to View 208 request
// 
//    Rev 1.7   Apr 16 2003 10:21:28   YINGBAOL
// fix PTS10015615
// 
//    Rev 1.6   Mar 21 2003 18:06:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Jan 08 2003 19:09:00   WINNIE
// Sync up Rev 1.4   Oct 26 2002 14:53:36 Fix to attach additional 201 repeat records to the list 
// 
//    Rev 1.4   Oct 09 2002 23:54:22   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:55:36   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   Jun 15 2002 15:26:52   VASILEAD
// Fixed bug when SettleAll=Y and none unsettled
// 
//    Rev 1.1   Jun 13 2002 19:06:20   VASILEAD
// Send fixed area when SettleAll = Y and all trades are settled and unchanged
// 
//    Rev 1.0   Jun 12 2002 21:08:32   VASILEAD
// Initial revision.
 * 
 *    Rev 1.11   22 May 2002 18:27:54   PURDYECH
 * BFData Implementation
//
 * 
*/