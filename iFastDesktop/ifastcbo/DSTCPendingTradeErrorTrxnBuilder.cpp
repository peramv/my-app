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
// ^FILE   : DSTCMinimumInvestmentTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCMinimumInvestmentTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "DSTCPendingTradeErrorTrxnBuilder.hpp"
#include "trade.hpp"
#include "mfaccount.hpp"
#include "trademinamtcheck.hpp"
#include "UnusualTradingValidation.hpp"
#include "worksessiontradeslist.hpp"

#include <ifastdataimpl\dse_dstc0475_req.hpp>
#include <ifastdataimpl\dse_dstc0475_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0475_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PENDING_TRADE_ERROR_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCPendingTradeErrorTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}
namespace ifds
{
	extern CLASS_IMPORT const BFDecimalFieldId ErrNum;
	extern CLASS_IMPORT const BFTextFieldId ErrMsg;
	extern CLASS_IMPORT const BFTextFieldId Slsrep;
	extern CLASS_IMPORT const BFTextFieldId FromCurrency;
}
namespace TRADETYPE
{
	extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
	extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
	extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
	extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
	extern CLASS_IMPORT I_CHAR * const EXCHANGE;
	extern CLASS_IMPORT I_CHAR * const TRANSFER;
}

//******************************************************************************
void DSTCPendingTradeErrorTrxnBuilder::buildTrxnKey( DString& dstrKey ) 
{
}

//******************************************************************************
SEVERITY DSTCPendingTradeErrorTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
															  BFAbstractCBO* pObj, 
															  HostTransactionContainer* pTrCont, 
															  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

	Trade *pTrade = dynamic_cast<Trade*>(pObj);
	if (pTrade)
	{
		DString dstTransNum, dstTrnKey, dstKeyTypes;
		pTrade->getField( ifds::TransNum, dstTransNum, BF::HOST, true );
		addIDITagValue( dstTrnKey,TRXNTAG::PENDINGTRADEERRORTAG, dstTransNum.stripLeading('0').strip() );

		HostTransactionContainerIterator iterTrxnContList( pTrCont );

		iterTrxnContList.walkStrKey( dstTrnKey );
		iterTrxnContList.walkTrxnGroup( NO_GROUP );
		iterTrxnContList.walkTrxnSubType( 0 );
		TradeMinAmtCheck *pTradeMinAmtCheck = NULL;
		UnusualTradingValidation *pUnusualTradingValidation = NULL;
		WorksessionTradesList *pWorksessionTradesList =  NULL;
		workSession.getTradesList(pWorksessionTradesList, BF::HOST);
		bool duplicateTradeExist;
		duplicateTradeExist = pWorksessionTradesList->getDuplicateTrade ();
		DString fundCode, classCode, toFundCode, toClassCode, accountTo, tradeInDate, strKey, strKey1, strKeyUnusual ;

		pTrade->getField (ifds::FromFund, fundCode, BF::HOST, false);
		pTrade->getField (ifds::FromClass, classCode, BF::HOST, false);

		if (!fundCode.empty() && !classCode.empty())
		{
			DString tradeDate, exchRate, depositType,orderType,amtType,amount, currency, 
				broker, branch, slsrep,accountNum , strTransTypeIndc,dstrFromCurrency;

			pTrade->getField (ifds::AccountNum, accountNum, BF::HOST, false);
			pTrade->getField (ifds::AmtType, amtType, BF::HOST, false);
			pTrade->getField (ifds::Amount, amount, BF::HOST, false);
			pTrade->getField (ifds::EffectiveDate, tradeDate, BF::HOST, false);
			pTrade->getField (ifds::SettleCurrency, currency, BF::HOST);
			pTrade->getField (ifds::Broker, broker, BF::HOST, false);
			pTrade->getField (ifds::Branch, branch, BF::HOST, false);
			pTrade->getField (ifds::SlsrepCode, slsrep, BF::HOST, false);
			pTrade->getField (ifds::ExchRate, exchRate, BF::HOST, false);
			pTrade->getField (ifds::DepositType, depositType, BF::HOST); 
			pTrade->getField (ifds::OrderType, orderType, BF::HOST);
			pTrade->getField( ifds::TradesTransType, strTransTypeIndc, BF::HOST);

			int iTransTypeLength = 2;
			DString strTransType;
			if (strTransTypeIndc.length() > iTransTypeLength )
			{
				strTransType = strTransTypeIndc.substr(0,iTransTypeLength);
			}
			else
			{
				strTransType = strTransTypeIndc;
			}

			BFData *pDataReq = NULL;
			BFData *pDataRes = NULL;
			TradeMinAmtCheck *pTradeMinAmtCheckMoneyIn = NULL;
			UnusualTradingValidation *pUnusualTradingValidationTwoSide = NULL;

			DString dstrTransType, strKeyMoneyIn, strKeyMoneyOut, 
					dstrTransTypeMoneyOut, dstrTransTypeMoneyIn,
					strUnusualTradingTwoSide;

			strKeyUnusual = 
				I_("Account=")       + accountNum +
				I_(";TransType=")    + strTransTypeIndc +
				I_(";FundCode=")     + fundCode  +
				I_(";ClassCode=")    + classCode +
				I_(";AmtType=")      + amtType   +
				I_(";Amount=")       + amount    +
				I_(";Currency=")     + currency  +
				I_(";Broker=")       + broker +
				I_(";Branch=")       + branch +
				I_(";SlsRep=")       + slsrep +
				I_(";TradeDate=")    + tradeDate +
				I_(";DepositType=")  + depositType +
				I_(";OrderType=")    + orderType ;

			pUnusualTradingValidation = dynamic_cast<UnusualTradingValidation*>(pTrade->getObject(strKeyUnusual, BF::HOST));

			if ( strTransType != TRADETYPE::EXCHANGE &&  strTransType!= TRADETYPE::TRANSFER )
			{
				strKey = 
					I_("TradeMinAmtCheck_Account=")  + accountNum +
					I_(";TransType=")    + strTransType +
					I_(";FundCode=")     + fundCode  +
					I_(";ClassCode=")    + classCode +
					I_(";AmtType=")      + amtType   +
					I_(";Amount=")       + amount    +
					I_(";Currency=")     + currency  +
					I_(";Broker=")       + broker    +
					I_("Branch=")        + branch    +
					I_("SlsRep=")        + slsrep    +
					I_("TradeDate=")     + tradeDate +
					I_("DepositType=")   + depositType +
					I_("OrderType=")     + orderType +
					I_(";FullExchPrntToPrnt=")  + N ; 

				pTradeMinAmtCheck = dynamic_cast<TradeMinAmtCheck*>(pTrade->getObject(strKey, BF::HOST));

				if (pTradeMinAmtCheck || pUnusualTradingValidation ||  duplicateTradeExist)
				{

					iterTrxnContList.begin();

					//fill in the fixed area
					if( iterTrxnContList.end() )
					{
						pDataReq = new BFData( ifds::DSTC0475_REQ );
						pDataRes = new BFData( ifds::DSTC0475_VW );
       
						pDataReq->setElementValue( ifds::Track, I_("N"), false, false );
						pDataReq->setElementValue( ifds::Activity, NULL_STRING, false, false );

						//fill in the request update
						DString mgmtCoId;
						workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

						pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
						pDataReq->setElementValue( ifds::TransNum, dstTransNum );

						JData *jdata = new JData( DSTC_REQUEST::PENDING_TRADE_ERROR_UPDATE, pDataReq, pDataRes );
						pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
					}
					else
						pDataRes = (*iterTrxnContList)->getRequestDataObject();
	
					if (pTradeMinAmtCheck)
					{
						BFObjIter iter  (*pTradeMinAmtCheck, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
						iter.begin ();

						while  (!iter.end ())
						{
							//create a repeat for the request and fill it in
							BFData repeat( ifds::DSTC0475_REQRepeat_Record);

							DString errNum, errDesc, severityCode;
							iter.getObject ()->getField  (ifds::ErrNum, errNum, BF::HOST, false);
							iter.getObject ()->getField  (ifds::ErrMsg, errDesc, BF::HOST, true);
							iter.getObject ()->getField  (ifds::EWI, severityCode, BF::HOST, false);

							const DSTCSecurity *pSecurity = 
								dynamic_cast<const DSTCSecurity *>(workSession.getSecurity(DSTCHost::getPrimaryHost()));
							DString dstrCurrentUser = pSecurity->getUserId();
							dstrCurrentUser.strip().upperCase();

							DString errorDescription = fundCode + I_(" ") + classCode + I_(" ") + errDesc;
							repeat.setElementValue(ifds::ErrorCode, errNum, false, false);
							repeat.setElementValue(ifds::ErrorDesc, errorDescription, false, false);
							repeat.setElementValue(ifds::EWI, severityCode, false, false);
							repeat.setElementValue(ifds::Username, dstrCurrentUser, false, false);

							//set the RunMode field 
							DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity());

							//add the lDataRepeat to the request
							pDataReq->addRepeat( repeat );
							DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
							pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );

							++iter;
						}
					}
					if (pUnusualTradingValidation)
					{
						BFObjIter iter1  (*pUnusualTradingValidation, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
						iter1.begin ();
						while  (!iter1.end ())
						{
							//create a repeat for the request and fill it in
							BFData repeat( ifds::DSTC0475_REQRepeat_Record);

							DString errNum, errDesc, severityCode;
							iter1.getObject ()->getField  (ifds::ErrNum, errNum, BF::HOST, false);
							iter1.getObject ()->getField  (ifds::ErrMsg, errDesc, BF::HOST, true);
							iter1.getObject ()->getField  (ifds::EWI, severityCode, BF::HOST, false);

							const DSTCSecurity *pSecurity = 
								dynamic_cast<const DSTCSecurity *>(workSession.getSecurity(DSTCHost::getPrimaryHost()));
							DString dstrCurrentUser = pSecurity->getUserId();
							dstrCurrentUser.strip().upperCase();

							repeat.setElementValue(ifds::ErrorCode, errNum, false, false);
							repeat.setElementValue(ifds::ErrorDesc, errDesc, false, false);
							repeat.setElementValue(ifds::EWI, severityCode, false, false);
							repeat.setElementValue(ifds::Username, dstrCurrentUser, false, false);

							//set the RunMode field 
							DSTCWorkSession::setRunMode( &repeat, iter1.getKey().getActivity());

							//add the lDataRepeat to the request
							pDataReq->addRepeat( repeat );
							DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
							pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );

							++iter1;
						}
					}

				}

			}
			else 
			{
				if (strTransType == TRADETYPE::TRANSFER)
				{
					dstrTransTypeMoneyOut = TRADETYPE::TRANSFER_OUT;
					pTrade->getField (ifds::FromCurrency, dstrFromCurrency, BF::HOST, false);
					strKeyMoneyOut = 
						I_("TradeMinAmtCheck_Account=")  + accountNum +
						I_(";TransType=")    + dstrTransTypeMoneyOut +
						I_(";FundCode=")     + fundCode  +
						I_(";ClassCode=")    + classCode +
						I_(";AmtType=")      + amtType   +
						I_(";Amount=")       + amount    +
						I_(";Currency=")     + dstrFromCurrency  +
						I_(";Broker=")       + broker    +
						I_("Branch=")        + branch    +
						I_("SlsRep=")        + slsrep    +
						I_("TradeDate=")     + tradeDate +
						I_("DepositType=")   + depositType +
						I_("OrderType=")     + orderType +
						I_(";FullExchPrntToPrnt=")  + N ;

					pTrade->getField (ifds::AccountTo,accountTo,BF::HOST, false);

					MFAccount *pMFAccountTo = NULL;
					DString brokerTo, branchTo, slsrepTo;
					if (workSession.getMFAccount (BF::HOST, accountTo, pMFAccountTo) <= WARNING && pMFAccountTo)
					{
						pMFAccountTo->getField (ifds::BrokerCode, brokerTo, BF::HOST); 
						pMFAccountTo->getField (ifds::BranchCode, branchTo, BF::HOST);
						pMFAccountTo->getField (ifds::Slsrep, slsrepTo, BF::HOST);
					}

					dstrTransTypeMoneyIn = TRADETYPE::TRANSFER_IN;
					pTrade->getField (ifds::TradeInDate, tradeDate, BF::HOST, false);
					strKeyMoneyIn = 
						I_("TradeMinAmtCheck_Account=")  + accountTo +
						I_(";TransType=")    + dstrTransTypeMoneyIn +
						I_(";FundCode=")     + fundCode  +
						I_(";ClassCode=")    + classCode +
						I_(";AmtType=")      + amtType   +
						I_(";Amount=")       + amount    +
						I_(";Currency=")     + dstrFromCurrency  +
						I_(";Broker=")       + brokerTo  +
						I_("Branch=")        + branchTo  +
						I_("SlsRep=")        + slsrepTo  +
						I_("TradeDate=")     + tradeDate +
						I_("DepositType=")   + depositType +
						I_("OrderType=")     + orderType +
						I_(";FullExchPrntToPrnt=")  + N ;
				}
				else if (strTransType == TRADETYPE::EXCHANGE)
				{
					dstrTransTypeMoneyOut = TRADETYPE::EXCHANGE_OUT;
					pTrade->getField (ifds::FromCurrency, dstrFromCurrency, BF::HOST, false);
					strKeyMoneyOut = 
						I_("TradeMinAmtCheck_Account=")  + accountNum +
						I_(";TransType=")    + dstrTransTypeMoneyOut +
						I_(";FundCode=")     + fundCode  +
						I_(";ClassCode=")    + classCode +
						I_(";AmtType=")      + amtType   +
						I_(";Amount=")       + amount    +
						I_(";Currency=")     + dstrFromCurrency  +
						I_(";Broker=")       + broker    +
						I_("Branch=")        + branch    +
						I_("SlsRep=")        + slsrep    +
						I_("TradeDate=")     + tradeDate +
						I_("DepositType=")   + depositType +
						I_("OrderType=")     + orderType +
						I_(";FullExchPrntToPrnt=")  + N ;

					pTrade->getField (ifds::ToFund, toFundCode, BF::HOST, false);
					pTrade->getField (ifds::ToClass, toClassCode, BF::HOST, false);
					dstrTransTypeMoneyIn = TRADETYPE::EXCHANGE_IN;
					pTrade->getField (ifds::TradeInDate, tradeInDate, BF::HOST, false);
					strKeyMoneyIn = 
						I_("TradeMinAmtCheck_Account=")  + accountNum +
						I_(";TransType=")    + dstrTransTypeMoneyIn +
						I_(";FundCode=")     + toFundCode  +
						I_(";ClassCode=")    + toClassCode +
						I_(";AmtType=")      + amtType   +
						I_(";Amount=")       + amount    +
						I_(";Currency=")     + dstrFromCurrency  +
						I_(";Broker=")       + broker    +
						I_("Branch=")        + branch    +
						I_("SlsRep=")        + slsrep    +
						I_("TradeDate=")     + tradeInDate +
						I_("DepositType=")   + depositType +
						I_("OrderType=")     + orderType +
						I_(";FullExchPrntToPrnt=")  + N ;
				}

				pTrade->getField (ifds::AccountTo,accountTo,BF::HOST, false);
				pTrade->getField (ifds::ToFund, toFundCode, BF::HOST, false);
				pTrade->getField (ifds::ToClass, toClassCode, BF::HOST, false);
				pTrade->getField (ifds::FromCurrency, currency, BF::HOST, false);
				pTrade->getField (ifds::TradeInDate, tradeInDate, BF::HOST, false);

				strUnusualTradingTwoSide =
					I_("Account=")       + accountNum +
					I_(";TransType=")    + strTransTypeIndc +
					I_(";FundCode=")     + fundCode  +
					I_(";ClassCode=")    + classCode +
					I_(";AmtType=")      + amtType   +
					I_(";Amount=")       + amount    +
					I_(";Currency=")     + currency  +
					I_(";Broker=")       + broker +
					I_(";Branch=")       + branch +
					I_(";SlsRep=")       + slsrep +
					I_(";TradeDate=")    + tradeDate +
					I_(";DepositType=")  + depositType +
					I_(";OrderType=")    + orderType +
					I_(";ToFundCode=")   + toFundCode  +
					I_(";ToClassCode=")  + toClassCode +
					I_(";ToAccount=")    + accountTo +
					I_(";TradeInDate=")  + tradeInDate;

				pTradeMinAmtCheck = dynamic_cast<TradeMinAmtCheck*>(pTrade->getObject(strKeyMoneyOut, BF::HOST));
				pTradeMinAmtCheckMoneyIn = dynamic_cast<TradeMinAmtCheck*>(pTrade->getObject(strKeyMoneyIn, BF::HOST));
				pUnusualTradingValidationTwoSide = dynamic_cast<UnusualTradingValidation*>(pTrade->getObject(strUnusualTradingTwoSide, BF::HOST));

				if (pTradeMinAmtCheck || pTradeMinAmtCheckMoneyIn || pUnusualTradingValidationTwoSide)
				{

					iterTrxnContList.begin();

					//fill in the fixed area
					if( iterTrxnContList.end() )
					{
						pDataReq = new BFData( ifds::DSTC0475_REQ );
						pDataRes = new BFData( ifds::DSTC0475_VW );

						pDataReq->setElementValue( ifds::Track, I_("N"), false, false );
						pDataReq->setElementValue( ifds::Activity, NULL_STRING , false, false );

						//fill in the request update
						DString mgmtCoId;
						workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

						pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
						pDataReq->setElementValue( ifds::TransNum, dstTransNum );

						JData *jdata = new JData( DSTC_REQUEST::PENDING_TRADE_ERROR_UPDATE, pDataReq, pDataRes );
						pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
					}
					else
						pDataRes = (*iterTrxnContList)->getRequestDataObject();

					//create a repeat for the request and fill it in
					BFData repeat( ifds::DSTC0475_REQRepeat_Record);
					if (pTradeMinAmtCheck)
					{
						BFObjIter iter  (*pTradeMinAmtCheck, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
						iter.begin ();

						while  (!iter.end ())
						{

							DString errNum, errDesc, severityCode;
							iter.getObject ()->getField  (ifds::ErrNum, errNum, BF::HOST, false);
							iter.getObject ()->getField  (ifds::ErrMsg, errDesc, BF::HOST, true);
							iter.getObject ()->getField  (ifds::EWI, severityCode, BF::HOST, false);

							const DSTCSecurity *pSecurity = 
								dynamic_cast<const DSTCSecurity *>(workSession.getSecurity(DSTCHost::getPrimaryHost()));
							DString dstrCurrentUser = pSecurity->getUserId();
							dstrCurrentUser.strip().upperCase();

							DString errorDescription = fundCode + I_(" ") + classCode + I_(" ") + errDesc;
							repeat.setElementValue(ifds::ErrorCode, errNum, false, false);
							repeat.setElementValue(ifds::ErrorDesc, errorDescription, false, false);
							repeat.setElementValue(ifds::EWI, severityCode, false, false);
							repeat.setElementValue(ifds::Username, dstrCurrentUser, false, false);

							//set the RunMode field 
							DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity());

							//add the lDataRepeat to the request
							pDataReq->addRepeat( repeat );
							DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
							pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );

							++iter;
						}
					}
					if( pTradeMinAmtCheckMoneyIn )
					{
						BFObjIter iter1  (*pTradeMinAmtCheckMoneyIn, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
						iter1.begin ();

						while  (!iter1.end ())
						{

							DString errNum, errDesc, severityCode;
							iter1.getObject ()->getField  (ifds::ErrNum, errNum, BF::HOST, false);
							iter1.getObject ()->getField  (ifds::ErrMsg, errDesc, BF::HOST, true);
							iter1.getObject ()->getField  (ifds::EWI, severityCode, BF::HOST, false);

							const DSTCSecurity *pSecurity = 
								dynamic_cast<const DSTCSecurity *>(workSession.getSecurity(DSTCHost::getPrimaryHost()));
							DString dstrCurrentUser = pSecurity->getUserId();
							dstrCurrentUser.strip().upperCase();

							DString errorDescription = fundCode + I_(" ") + classCode + I_(" ") + errDesc;
							repeat.setElementValue(ifds::ErrorCode, errNum, false, false);
							repeat.setElementValue(ifds::ErrorDesc, errorDescription, false, false);
							repeat.setElementValue(ifds::EWI, severityCode, false, false);
							repeat.setElementValue(ifds::Username, dstrCurrentUser, false, false);

							//set the RunMode field 
							DSTCWorkSession::setRunMode( &repeat, iter1.getKey().getActivity());

							//add the lDataRepeat to the request
							pDataReq->addRepeat( repeat );
							DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
							pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );

							++iter1;
						}
					}
					if (pUnusualTradingValidationTwoSide)
					{
						BFObjIter iterUnusual  (*pUnusualTradingValidationTwoSide, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
						iterUnusual.begin ();
						while  (!iterUnusual.end ())
						{
							//create a repeat for the request and fill it in
							BFData repeat( ifds::DSTC0475_REQRepeat_Record);

							DString errNum, errDesc, severityCode;
							iterUnusual.getObject ()->getField  (ifds::ErrNum, errNum, BF::HOST, false);
							iterUnusual.getObject ()->getField  (ifds::ErrMsg, errDesc, BF::HOST, true);
							iterUnusual.getObject ()->getField  (ifds::EWI, severityCode, BF::HOST, false);

							const DSTCSecurity *pSecurity = 
								dynamic_cast<const DSTCSecurity *>(workSession.getSecurity(DSTCHost::getPrimaryHost()));
							DString dstrCurrentUser = pSecurity->getUserId();
							dstrCurrentUser.strip().upperCase();

							repeat.setElementValue(ifds::ErrorCode, errNum, false, false);
							repeat.setElementValue(ifds::ErrorDesc, errDesc, false, false);
							repeat.setElementValue(ifds::EWI, severityCode, false, false);
							repeat.setElementValue(ifds::Username, dstrCurrentUser, false, false);

							//set the RunMode field 
							DSTCWorkSession::setRunMode( &repeat, iterUnusual.getKey().getActivity());

							//add the lDataRepeat to the request
							pDataReq->addRepeat( repeat );
							DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
							pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );

							++iterUnusual;
						}
					}
				}
			}

			BFObjIter iterTrades( *pWorksessionTradesList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
			iterTrades.begin();
			//create a repeat for the request and fill it in
			BFData repeat( ifds::DSTC0475_REQRepeat_Record);
			while (!iterTrades.end())
			{
				if(duplicateTradeExist)
				{
					const DSTCSecurity *pSecurity = 
						dynamic_cast<const DSTCSecurity *>(workSession.getSecurity(DSTCHost::getPrimaryHost()));
					DString dstrCurrentUser = pSecurity->getUserId();
					dstrCurrentUser.strip().upperCase();
					DString strValue;
					repeat.setElementValue(ifds::ErrorCode, I_("1940"), false, false);
					pWorksessionTradesList->getErrMsgValue (I_("1940"),BF::HOST, strValue);
					repeat.setElementValue(ifds::ErrorDesc,I_("Duplicate trade already exists"), false, false);
					repeat.setElementValue(ifds::EWI,strValue, false, false);
					repeat.setElementValue(ifds::Username, dstrCurrentUser, false, false);

					//set the RunMode field 
					DSTCWorkSession::setRunMode( &repeat, iterTrades.getKey().getActivity());

					//add the lDataRepeat to the request
					pDataReq->addRepeat( repeat );
					DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
					pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
				}
				++iterTrades;
			}

		}
}
		return GETCURRENTHIGHESTSEVERITY();
}

