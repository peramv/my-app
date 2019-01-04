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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AggregatedOrder.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 13/07/2004
//
// ^CLASS    : AggregatedOrder
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "aggregatedorder.hpp"
#include "aggregatedorderlist.hpp"

#include <bfutil\bfdate.hpp>
#include "datevalidation.hpp"
#include "dstcommonfunction.hpp"
#include "fundbrokersettlementinstr.hpp"
#include "fundbrokersettlementinstrlist.hpp"
#include "fundmgmtsettlementinstr.hpp"
#include "fundmgmtsettlementinstrlist.hpp"
#include "fundbroker.hpp"
#include "fundbrokerlist.hpp"
#include "fundbrokerfeelist.hpp"
#include "fundfeelist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "pendingtradelist.hpp"
#include "pendingtradedetails.hpp"
#include "trade.hpp"
#include "tradesearchcriteria.hpp"
#include "worksessiontradeslist.hpp"

#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0323_req.hpp>
#include <ifastdataimpl\dse_dstc0323_vw.hpp>
#include <ifastdataimpl\dse_dstc0230_req.hpp>
#include <ifastdataimpl\dse_dstc0230_vw.hpp>
#include <ifastdataimpl\dse_dstc0324_req.hpp>
#include <ifastdataimpl\dse_dstc0324_vw.hpp>
namespace
{
   const I_CHAR * const BLANK_SUBSTITUTION               = I_( " = ;");    // substitution with only one element with tag = value = " " 
   const I_CHAR * const CLASSNAME                        = I_( "AggregatedOrder" );
   const I_CHAR * const AGGREGATED                       = I_( "01" );
   const I_CHAR * const ORDER_SENT                       = I_( "02" );
   const I_CHAR * const DONOT_SEND                       = I_( "03" );
   const I_CHAR * const PRICE_LOADED                     = I_( "04" );
   const I_CHAR * const PRICE_POSTED                     = I_( "05" );
   const I_CHAR * const CANCEL_REQUESTED                 = I_( "08" );
   const I_CHAR * const CANCELED                         = I_( "09" ); 
   const I_CHAR * const NAV                              = I_( "01" );
   const I_CHAR * const OFFER_PRICE                      = I_( "02" );
   const I_CHAR * const BROKER_PRICE                     = I_( "03" );
   const I_CHAR * const YES                              = I_( "Y" );
   const I_CHAR * const NO	                              = I_( "N" );

   const I_CHAR * const FUND_BROKER_EXTERNAL_CHARGE      = I_( "114" );
   const I_CHAR * const FUND_BROKER_COMMISSION           = I_( "115" );
   const I_CHAR * const REBATE_AMOUNT                    = I_( "116" );
   const I_CHAR * const BEARER_CERTIFICATE               = I_( "1" );
   const I_CHAR * const REBATERATE                       = I_("Rebate Rate");
   const I_CHAR * const EXTERNCHARGE                     = I_("External Charge");
   const I_CHAR * const COMMISSION                       = I_("Commission");
   const I_CHAR * const AMOUNT                           = I_("D");

   const I_CHAR * const SUPPRESS_INDICATOR_DEFAULT_CODE	= I_("2");
   const I_CHAR * const CONFIRMED_AMOUNT_EXCEEDS_LIMIT	= I_("853");
   const I_CHAR * const ALLOWED_TO_CANCEL_STATUS        = I_("01,02,03,04,08"); //Aggregated = 01, Order Send =02,
                                                                                //Do not send price =03,Price Loaded = 04
                                                                                //Cancel requested = 08
}

namespace ifds
{  
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId StatusPriceBrkSettlAmtUnits;
   extern CLASS_IMPORT const BFTextFieldId SearchType;
   extern CLASS_IMPORT const BFTextFieldId ExternalIdType;
   extern CLASS_IMPORT const BFTextFieldId ExternalId;
   extern CLASS_IMPORT const BFTextFieldId FeeType;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
   extern CLASS_IMPORT const BFTextFieldId AggrOrdRefreshed;
   extern CLASS_IMPORT const BFTextFieldId TradeDateFailed;
   extern CLASS_IMPORT const BFTextFieldId AccountableMandatory;
   extern CLASS_IMPORT const BFNumericFieldId rxAcctNum;
   extern CLASS_IMPORT const BFTextFieldId MCHSRActive;
   extern CLASS_IMPORT const BFTextFieldId BatchVerify;
}

namespace CND
{  // Conditions used   
   extern const long ERR_PRICE_CANNOT_BE_ZERO;
   extern const long ERR_BROKER_STTL_AMOUNT_CANNOT_BE_ZERO;
   extern const long ERR_VALUE_CANNOT_BE_MINUS;
   extern const long ERR_INVALID_STATUS;
   extern const long ERR_INVALID_PRICE_TYPE;
   extern const long ERR_TRANSTYPE_DOES_NOT_MATCH;
   extern const long ERR_FUND_CLASS_DOES_NOT_MATCH;
   extern const long ERR_AMOUNT_DOES_NOT_MATCH;
   extern const long ERR_CURRENCY_DOES_NOT_MATCH; 
   extern const long ERR_TRADE_DATE_DOESNOT_MATCH;
   extern const long ERR_PRICETYPE_DOESNOT_MATCH;
   extern const long ERR_SETTLEMENT_DATE_DOES_NOT_MATCH; 
   extern const long ERR_SETTLEMENT_AMOUNT_DOES_NOT_MATCH;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_AGGREGATED_ORDER_TRADE_DATE_INVALID;
   extern const long ERR_FUND_BROKER_IS_NOT_EFFECTIVE;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long WARN_LOSS_SITUATION;   
   extern const long ERR_PRCPOSTER_SAME_AS_PRCLOADER;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AGGREGATED_ORDER_LIST_UPDATE;
   extern CLASS_IMPORT const DSTCRequest AGGREGATED_ORDER_LIST;
}

namespace DATE_VALIDATION
{
   extern const I_CHAR * const TRADE_DATE; 
   extern const I_CHAR * const DEFAULT_VALUE_DATE;
}

const  BFFieldId SttlInstrReadOnlyFields[] = 
{
    ifds::IntermediaryBank,   
    ifds::ReceivingBank,      
    ifds::Beneficiary,         
    ifds::SpecialInstructions, 
    ifds::CashMsgType, 
} ;

const int numSttlInstrReadOnlyFields = sizeof(SttlInstrReadOnlyFields) / sizeof(BFFieldId);

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                       State Flags,         Group Flags 
   { ifds::BrkSettlDate,               BFCBO::REQUIRED,        0 }, 
   { ifds::OrdStatus,                  BFCBO::REQUIRED,        0 },
   { ifds::Amount,                     BFCBO::NONE,            0 },
   { ifds::AmountType,                 BFCBO::NONE,            0 }, 
   { ifds::BrkSettlPUD,                BFCBO::NONE,            0 }, 
   { ifds::BrkSettlAmtUnits,           BFCBO::REQUIRED,        0 }, 
   { ifds::Price,                      BFCBO::NONE,            0 }, 
   { ifds::AggrPriceType,              BFCBO::REQUIRED,        0 }, 
   { ifds::RoutingRef,                 BFCBO::NONE,            0 }, 
   { ifds::RoutingType,                BFCBO::NONE,            0 }, 
   { ifds::Commission,                 BFCBO::NONE,            0 }, 
   { ifds::ExternCharge,               BFCBO::NONE,            0 }, 
   { ifds::RebateRate,                 BFCBO::NONE,            0 }, 
   { ifds::NAV,                        BFCBO::NONE,            0 }, 
   { ifds::OfferPrice,                 BFCBO::NONE,            0 }, 
   { ifds::AFTBenefit,                 BFCBO::NONE,            0 }, 
   { ifds::SettlInstrCode,             BFCBO::REQUIRED,        0 }, 
   { ifds::SettleLocationCode,         BFCBO::REQUIRED,        0 }, 
   { ifds::DeliveryTo,                 BFCBO::NONE,            0 }, 
   { ifds::ForAccount,                 BFCBO::NONE,            0 }, 
   { ifds::InFavourOf,                 BFCBO::NONE,            0 }, 
   { ifds::ClrSettlMethod,             BFCBO::REQUIRED,        0 }, 
   { ifds::RemarksAggr,                BFCBO::NONE,            0 }, 
   { ifds::StatusPriceBrkSettlAmtUnits,   BFCBO::NONE,         0 }, 
   { ifds::AggrOrdVer,                 BFCBO::NONE,            0 }, 
   { ifds::Recalculate,                BFCBO::NONE,            0 }, 
   { ifds::SettleAccountNum,           BFCBO::NONE,            0 }, 
   { ifds::AggrOrdRefreshed,           BFCBO::NONE,            0 }, 
   { ifds::TransType,                  BFCBO::NONE,            0 }, 
   { ifds::FundCode,                   BFCBO::NONE,            0 }, 
   { ifds::ClassCode,                  BFCBO::NONE,            0 }, 
   { ifds::Currency,                   BFCBO::NONE,            0 }, 
   { ifds::TradeDate,                  BFCBO::NONE,            0 }, 
   { ifds::FundIDType,                 BFCBO::NONE,            0 }, 
   { ifds::FundIDValue,                BFCBO::NONE,            0 }, 
   { ifds::WarnMsgCode,                BFCBO::NONE,            0 }, 
   { ifds::ModUser,                    BFCBO::NONE,            0 }, 
   { ifds::ModDate,                    BFCBO::NONE,            0 }, 
   { ifds::SecRecFileIndicator,        BFCBO::NONE,            0 }, 
   { ifds::CashMsgType,                BFCBO::NONE,            0 },
   { ifds::IntermediaryBank,           BFCBO::NONE,            0 },
   { ifds::ReceivingBank,              BFCBO::NONE,            0 },
   { ifds::Beneficiary,                BFCBO::NONE,            0 },
   { ifds::SpecialInstructions,        BFCBO::NONE,            0 },
   { ifds::InternalSettlementAccount,  BFCBO::NONE,            0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AGGREGATED_ORDER_TRADE_DATE;
   extern CLASS_IMPORT I_CHAR * const MCH_AND_SECUR_REC_FILE_INDICATOR;
}

//****************************************************************************
AggregatedOrder::AggregatedOrder( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   addCrossEdit(ifds::StatusPriceBrkSettlAmtUnits, ifds::OrdStatus);
   addCrossEdit(ifds::StatusPriceBrkSettlAmtUnits, ifds::Price);
   addCrossEdit(ifds::StatusPriceBrkSettlAmtUnits, ifds::BrkSettlAmtUnits);
      pFundBrokerList = NULL;
}

//****************************************************************************
AggregatedOrder::~AggregatedOrder()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY AggregatedOrder::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   doInitData( BF::HOST  );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void AggregatedOrder::doInitData( const BFDataGroupId& idDataGroup )
{
   setFieldNoValidate (ifds::Recalculate, NO, idDataGroup );
   setFieldNoValidate (ifds::AggrOrdRefreshed, NO, idDataGroup );
   StatusRelatedChanges( idDataGroup );
   setSttlLocationAndInstr( idDataGroup );
   DString dsrOrderStatus;
   getField(ifds::OrdStatus, dsrOrderStatus, idDataGroup );
   getField(ifds::OrdStatus, _oldOrdStatus, idDataGroup );
   SetReadOnlyForUpdateingFields( idDataGroup, (dsrOrderStatus != PRICE_LOADED) );
   setSecRecFileIndicator( idDataGroup);
   setFieldReadOnly(ifds::SettleAccountNum, idDataGroup, true);
   m_iNumberOfLossTrade = -1;  
}

//****************************************************************************
void AggregatedOrder::doReset( const BFDataGroupId& idDataGroup )
{
   DString dstrOrdStatus, OrdStatusSubst;
   getField(ifds::OrdStatus, dstrOrdStatus, idDataGroup );
   setFieldAllSubstituteValues( ifds::OrdStatus, idDataGroup, ifds::OrdStatus );
   setFieldNoValidate (ifds::OrdStatus, dstrOrdStatus, idDataGroup,true, true, true );
}

//********************************************************************************************
SEVERITY AggregatedOrder::doValidateField( const BFFieldId &idField,
                                           const DString &strValue,
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::OrdStatus )
   {
      ValidateOrdStatus( strValue, idDataGroup );
   }
   else if ( idField == ifds::StatusPriceBrkSettlAmtUnits )
   {
      validateStatusPriceBrkSettlAmtUnits( idDataGroup );
   }   
   else if ( idField == ifds::Commission )
   {
      double dec_Commission = DSTCommonFunctions::convertToDouble( strValue );
      if ( dec_Commission < 0 || dec_Commission > 100 )
      {
         ADDCONDITIONFROMFILE (CND::ERR_VALUE_BETWEEN_0_AND_100 ); 
      }
   }
   else if ( idField == ifds::ExternCharge )
   {
      double dec_ExternCharge = DSTCommonFunctions::convertToDouble( strValue );
      if ( dec_ExternCharge < 0 )
      {
         ADDCONDITIONFROMFILE ( CND::ERR_VALUE_CANNOT_BE_MINUS ); 
      }
   }
   else if ( idField == ifds::RebateRate )
   {
      double dec_RebateRate = DSTCommonFunctions::convertToDouble( strValue );
      if ( dec_RebateRate < 0 || dec_RebateRate > 100 )
      {
         
         ADDCONDITIONFROMFILE ( CND::ERR_VALUE_BETWEEN_0_AND_100 ); 
      }
   }
   else if ( idField == ifds::AggrPriceType )
   {
      validateAggrPriceType(  strValue, idDataGroup );
      matchingValues( idField, strValue,CND::ERR_PRICETYPE_DOESNOT_MATCH,1);   
   }
   else if ( idField == ifds::TransType )
   {
      matchingValues( idField, strValue,CND::ERR_TRANSTYPE_DOES_NOT_MATCH,1);
   }
   else if ( idField == ifds::FundCode || idField == ifds::ClassCode 
      || idField == ifds::FundIDType || idField == ifds::FundIDValue      
      )
   {
      DString dstr(strValue);
      dstr.stripAll();
      if(dstr != NULL_STRING )
      {
         matchingValues( idField, strValue,CND::ERR_FUND_CLASS_DOES_NOT_MATCH,1);
      }  
   }
   else if (/*idField == ifds::AmountType ||*/idField == ifds::Amount)
   {
         //matchingValues( idField, strValue,CND::ERR_AMOUNT_DOES_NOT_MATCH, idField == ifds::AmountType?1:2);
		CalculatBrkSettlAmt( idDataGroup, true );
   }
   else if (idField == ifds::Currency)
   {
      DString currency,fundCode,classCode,newCurrency(strValue);
      FundDetailList*  pFundDetailList = NULL;
      getMgmtCo().getFundDetailList(pFundDetailList);
      if(pFundDetailList )
      {  
         FundDetail* fundDetail = NULL;
         getField(ifds::FundCode,fundCode,BF::HOST,false);
         getField(ifds::ClassCode,classCode,BF::HOST,false);
         fundCode.strip().upperCase();
         classCode.strip().upperCase();
         pFundDetailList->getFundDetail(fundCode,classCode,BF::HOST,fundDetail);
         if( fundDetail )
         {
            fundDetail->getField(ifds::Currency,currency,BF::HOST,false);
            currency.strip().upperCase();
            newCurrency.strip().upperCase();
            if(currency != newCurrency )
            {
               ADDCONDITIONFROMFILE (CND::ERR_CURRENCY_DOES_NOT_MATCH );
            }
         }
      }
   }
   else if (idField == ifds::TradeDate)
   {      
      if( !getWorkSession().hasUpdatePermission (UAF::AGGREGATED_ORDER_TRADE_DATE) )
      {
         matchingValues (idField, strValue, CND::ERR_TRADE_DATE_DOESNOT_MATCH, 3);
      }
      else
      {
         validateTradeDate (strValue, idDataGroup);
      }
   }
   else if (idField == ifds::BrkSettlDate)
   {      
     matchingValues( idField, strValue,CND::ERR_SETTLEMENT_DATE_DOES_NOT_MATCH,3);   
   }
   else if (idField == ifds::BrkSettlAmtUnits )
   {
       //Dlg layer will popup message box after click Refresh button if warnmsgcode=578,	   
      DString dstrWarnMsgCode;
      getField(ifds::WarnMsgCode, dstrWarnMsgCode, idDataGroup);
      dstrWarnMsgCode.strip();
      if ( dstrWarnMsgCode == I_("578") )
      {
         //matchingValues( idField, strValue,CND::ERR_SETTLEMENT_AMOUNT_DOES_NOT_MATCH,2);   
         ADDCONDITIONFROMFILE ( CND::ERR_SETTLEMENT_AMOUNT_DOES_NOT_MATCH );
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY AggregatedOrder::validateTradeDate ( const DString &strValue, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("doValidateField"));
//check whether the trade date is valid, call view 135
   DateValidation trade_DateValidation (*this);

   DString fundCode,
      classCode;

   getField (ifds::FundCode, fundCode, idDataGroup);
   getField (ifds::ClassCode, classCode, idDataGroup);
   if (trade_DateValidation.init ( DATE_VALIDATION::TRADE_DATE, //4
                                   strValue,     //tradeDate
                                   NULL_STRING,  //settleDate
                                   NULL_STRING,  //depositDate
                                   NULL_STRING,  //valueDate
                                   NULL_STRING,  //transType
                                   NULL_STRING,  //payType
                                   NULL_STRING,  //broker
                                   fundCode,
                                   classCode,
                                   NULL_STRING,  //toFund
                                   NULL_STRING,  //toClass
                                   N,            //orderType - Direct
                                   NULL_STRING,  //dealDate
                                   NULL_STRING,  //dealTime
                                   NULL_STRING,  //settleCurrency
                                   NULL_STRING,  //amount
                                   NULL_STRING,  //amtType
                                   NULL_STRING,  //settleInDate
                                   NULL_STRING,  //brokerTo,
                                   NULL_STRING,  //accountNum,
                                   NULL_STRING,  //accountNumTo,
                                   NULL_STRING,  //fromCurrency,
                                   NULL_STRING,  //toCurrency,
                                   I_("N"),      //Track,
                                   NULL_STRING)  //PageName
                                               <= WARNING)
   {
      DString tradeDate;

      trade_DateValidation.getField  (ifds::TradeDate, tradeDate, idDataGroup);
      if (!tradeDate.empty() && tradeDate != strValue)
      {
         ADDCONDITIONFROMFILE (CND::ERR_AGGREGATED_ORDER_TRADE_DATE_INVALID);
      }
   }
//check the effectiveness of fund and class
   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      FundDetailList *pFundDetailList = NULL;

      if ( getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING && 
           pFundDetailList &&
           !fundCode.empty () &&
           !classCode.empty() &&
           !pFundDetailList->IsFundValidAtDate (fundCode, classCode, strValue, idDataGroup))
      {
         DString idiStr;

         addIDITagValue (idiStr, I_("FUNDNAME"), fundCode);
         addIDITagValue (idiStr, I_("CLASSNAME"), classCode);
         ADDCONDITIONFROMFILEIDI (CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr);
      }
   }
//check the effectiveness of fund broker
   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      DString fundBrokerCode;
      getField (ifds::FundBrokerCode, fundBrokerCode, idDataGroup, false);

      FundBrokerList *pFundBrokerList = NULL;
      if ( getWorkSession().getFundBrokerList (pFundBrokerList, idDataGroup, true, fundBrokerCode ) <= WARNING &&
           pFundBrokerList)
      {
         FundBroker *pFundBroker = NULL;
         
         
         if ( pFundBrokerList->getFundBroker ( fundBrokerCode, 
                                               idDataGroup, 
                                               pFundBroker) <= WARNING &&
              pFundBroker)
         {
            DString fbEffectiveDate,
               fbStopDate;
         
            pFundBroker->getField (ifds::EffectiveDate, fbEffectiveDate, idDataGroup, false);
            pFundBroker->getField (ifds::StopDate, fbStopDate, idDataGroup, false);
            //check if fund broker is effective
            if (!DSTCommonFunctions::IsDateBetween (fbEffectiveDate, fbStopDate, strValue))
            {
               ADDCONDITIONFROMFILE (CND::ERR_FUND_BROKER_IS_NOT_EFFECTIVE);
            }
         }
      }
   }
   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      PendingTradeList *pPendingList = NULL;

      if ( getPendingTradeList (pPendingList, idDataGroup) <= WARNING &&
           pPendingList)

      {
         for (BFObjIter iter (*pPendingList, idDataGroup); !iter.end(); ++iter)
         {
            PendingTradeDetails *pPendingTradeDetails = 
               dynamic_cast <PendingTradeDetails *> (iter.getObject());
            
            if (pPendingTradeDetails)
            {
               setTradeDateOnEachPendingTrade (pPendingList, pPendingTradeDetails, strValue, idDataGroup);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************
SEVERITY AggregatedOrder::setTradeDateOnEachPendingTrade ( PendingTradeList *pPendingList,
                                                           PendingTradeDetails *pPendingTradeDetails,
                                                           const DString &tradeDate, 
                                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("setTradeDateOnEachPendingTrade"));

   assert (pPendingTradeDetails);
   BFData data53Rpt (ifds::DSTC0053_VWRepeat_Record);
   DString strKey;

   if (pPendingTradeDetails->getData (data53Rpt, idDataGroup) <= WARNING)
   {
      pPendingList->getStrKey (strKey, &data53Rpt);
      if (!strKey.empty())
      {
         pPendingList->getItem (strKey, idDataGroup, YES );
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            //can create a trade object...
            WorksessionTradesList *pWorksessionTradesList = NULL;

            if ( getWorkSession().getTradesList ( pWorksessionTradesList, 
                                                  idDataGroup, 
                                                  true) <= WARNING &&
                 pWorksessionTradesList)
            {
               DString tradeKey, 
                  transNum, 
                  accountNum;
               Trade *pTrade = NULL;

               pPendingTradeDetails->getField (ifds::TransNum, transNum, idDataGroup);
               pPendingTradeDetails->getField (ifds::rxAcctNum, accountNum, idDataGroup);
               //set the new trade date on the pending details object as well...this is in host
               WorksessionTradesList::buildKey (accountNum, transNum, tradeKey);

               BFObjIter iterTrade ( *pWorksessionTradesList, 
                                      idDataGroup, 
                                      true, //match substrings
                                      BFObjIter::ITERTYPE::NON_DELETED);
               
               if (!iterTrade.positionByKey (tradeKey)) //look for the trade, is it in the list ?
               {
                  //create a new trade...
                  if (pWorksessionTradesList->fromPending2Trade ( pPendingTradeDetails, 
                                                                  idDataGroup,
                                                                  true,
                                                                  tradeKey) <= WARNING)
                  {
                     //use another iterator..our bf iterator has some reinit issues...
                     BFObjIter iterTrade ( *pWorksessionTradesList, 
                                            idDataGroup, 
                                            true, //match substrings
                                            BFObjIter::ITERTYPE::NON_DELETED);
                     
                     iterTrade.positionByKey (tradeKey); //position ourselves on the object...
                     pTrade = dynamic_cast <Trade*> (iterTrade.getObject());
                  }
               }
               else
               {
                  pTrade = dynamic_cast <Trade*> (iterTrade.getObject());
               }
               if (pTrade)
               {
                  if (pTrade->setField (ifds::EffectiveDate, tradeDate, idDataGroup, false) <= WARNING)
                  {
                     DString accountableMandatory;

                     getWorkSession ().getOption ( ifds::AccountableMandatory, 
                                                   accountableMandatory, 
                                                   BF::HOST, 
                                                   false);
                     //no errors, check if this is a backdated trade and set the accountability code
                     //and backdated reason, accordingly
                     if (accountableMandatory == Y && pTrade->isBackdatedTrade (idDataGroup))
                     {
                        pTrade->setField (ifds::Accountable, I_("02"), idDataGroup, false); //fund code
                        pTrade->setField (ifds::BackDatedReason, I_("99"), idDataGroup, false); //misc
                     }
                  }
                  pTrade->validateAll (idDataGroup);
               }//end if pTrade
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************
SEVERITY AggregatedOrder::matchingValues ( const BFFieldId &idField,
                                           const DString &strValue,
                                           long lCondition,
                                           int iType)
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "matchingValues" ) );
  DString newValue(strValue),oldValue;
  getField(idField,oldValue,BF::HOST,false);
  switch( iType )
  {
   case 1:  // string
      {  
         newValue.strip().upperCase();
         oldValue.strip().upperCase();
         if(newValue != oldValue )
         {         
            ADDCONDITIONFROMFILE ( lCondition );
         }
      }
      break;
   case 2: //float     
      {
         double dNew,dOld;
         dNew = DSTCommonFunctions::convertToDouble (newValue);
         dOld = DSTCommonFunctions::convertToDouble (oldValue);
         if( dNew != dOld )
         {
            ADDCONDITIONFROMFILE ( lCondition );
         }
      }
      break;
   case 3:  //date
      {
         if( DSTCommonFunctions::CompareDates( newValue,oldValue ) 
         != DSTCommonFunctions::EQUAL )
         {
            ADDCONDITIONFROMFILE ( lCondition );
         }
      }
      break;
   default:
      break;
  }
  return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
SEVERITY AggregatedOrder::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
     
// Set Recalculate to Yes to enable the Refresh and trigger view call 324 to recalculate the values
   if ( /*idField == ifds::OrdStatus || */
        idField == ifds::AggrPriceType    || 
        idField == ifds::BrkSettlAmtUnits ||
        idField == ifds::Price            ||
        idField == ifds::Commission       ||
        idField == ifds::ExternCharge     ||
        idField == ifds::RebateRate 	  ||
		idField == ifds::Amount)
   {
      setFieldNoValidate (ifds::Recalculate, YES, idDataGroup );
   }
   if (idField == ifds::OrdStatus)
   {
      StatusRelatedChanges (idDataGroup);
      setSttlLocationAndInstr (idDataGroup);
   }
   else if (idField == ifds::AggrPriceType)
   {
      PriceTypeRelatedChanges( idDataGroup );
   }
   else if (idField == ifds::SettlInstrCode)
   {
      SettlInstrCodeRelatedChanges (idDataGroup);
   }
   else if (idField == ifds::SettleLocationCode)
   {
      setSettleAccountNum (idDataGroup);
   }
   else if (idField == ifds::TradeDate)
   {
//      setTradeDateOnEachPendingTrade (idDataGroup);
   }
   if ( idField == ifds::AggrPriceType || 
        idField == ifds::Price ||
        idField == ifds::Commission ||
        idField == ifds::ExternCharge ||
        idField == ifds::RebateRate)
   {
      CalculatBrkSettlAmt( idDataGroup );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY AggregatedOrder::StatusRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "StatusRelatedChanges" ) );
   SEVERITY  sevRtn = NO_CONDITION;
   setSubstituteValueForOrderStatus(idDataGroup);
   DString str;
   getField (ifds::OrdStatus, str, idDataGroup);

   BFProperties *pBFPropertiesAllOrdStatus = getFieldProperties (ifds::OrdStatus, idDataGroup);

   if( str == AGGREGATED )
   {
      SetReadOnlyForUpdateingFields( idDataGroup, true );
      //setFieldReadOnly (ifds::OrdStatus, idDataGroup, true);//need to allow cancel and cancel requeted for the order status
   }
   else if ( str == ORDER_SENT )
   {
      SetReadOnlyForUpdateingFields(idDataGroup, false );

      //remove "Aggregate" and "Do not Send" from the list
      if (pBFPropertiesAllOrdStatus)
      {
         DString allOrdStatus, OrdStatusSubst;

         pBFPropertiesAllOrdStatus->getAllSubstituteValues (OrdStatusSubst);

         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, AGGREGATED  );
         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, DONOT_SEND  );


         setFieldAllSubstituteValues ( ifds::OrdStatus, idDataGroup,	OrdStatusSubst	);
      }
   }
   else if (str == DONOT_SEND  )
   {
      SetReadOnlyForUpdateingFields( idDataGroup, false );
      // remove "Aggregate" and "Sent"  from the list
      if (pBFPropertiesAllOrdStatus)
      {
         DString allOrdStatus, OrdStatusSubst;

         pBFPropertiesAllOrdStatus->getAllSubstituteValues (OrdStatusSubst);

         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, AGGREGATED  );
         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, ORDER_SENT  );

         setFieldAllSubstituteValues ( ifds::OrdStatus, idDataGroup,	OrdStatusSubst	);
      }
   }
   else if ( str == PRICE_LOADED )
   {
      SetReadOnlyForUpdateingFields( idDataGroup, false );

      /* this logic alraedy handled by SetReadOnlyForUpdateingFields
      DString dstrPriceType;
      getField (ifds::AggrPriceType, dstrPriceType, idDataGroup);
      if ( str == OFFER_PRICE )
         setFieldReadOnly (ifds::RebateRate, idDataGroup, true);
      else
         setFieldReadOnly (ifds::RebateRate, idDataGroup, false); */

            //remove "Aggregate", "Do not Send" and "Sent" from the list
      if (pBFPropertiesAllOrdStatus)
      {
         DString allOrdStatus, OrdStatusSubst;

         pBFPropertiesAllOrdStatus->getAllSubstituteValues (OrdStatusSubst);

         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, AGGREGATED  );
         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, ORDER_SENT  );
         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, DONOT_SEND  );


         setFieldAllSubstituteValues ( ifds::OrdStatus, idDataGroup,	OrdStatusSubst	);
      }

   }
   else if ( str == PRICE_POSTED )
   {
      SetReadOnlyForUpdateingFields( idDataGroup, true );
      setFieldReadOnly (ifds::OrdStatus, idDataGroup, true);
   }
   else if ( CANCELED == str )
   {
     SetReadOnlyForUpdateingFields( idDataGroup, true );
     setFieldReadOnly (ifds::OrdStatus, idDataGroup, isOrderAlreadyCancelled( idDataGroup ));
   }
   else if( CANCEL_REQUESTED == str)
   {
     //make sure cancel requested selection is not providing with the extra options to the drop down,than the value on host is restricted to
     cancelRequestedStatusRelatedChanges(idDataGroup);
     SetReadOnlyForUpdateingFields( idDataGroup, true );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AggregatedOrder::cancelRequestedStatusRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "CancelRequestedStatusRelatedChanges" ) );
   
   DString str;
   getFieldBeforeImage(ifds::OrdStatus, str );
   str.stripAll();
   BFProperties *pBFPropertiesAllOrdStatus = getFieldProperties (ifds::OrdStatus, idDataGroup);

   if( str == AGGREGATED )
   {
      SetReadOnlyForUpdateingFields( idDataGroup, true );
      //setFieldReadOnly (ifds::OrdStatus, idDataGroup, true);//need to allow cancel and cancel requeted for the order status
   }
   else if ( str == ORDER_SENT )
   {
      SetReadOnlyForUpdateingFields(idDataGroup, false );

      //remove "Aggregate" and "Do not Send" from the list
      if (pBFPropertiesAllOrdStatus)
      {
         DString allOrdStatus, OrdStatusSubst;

         pBFPropertiesAllOrdStatus->getAllSubstituteValues (OrdStatusSubst);

         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, AGGREGATED  );
         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, DONOT_SEND  );


         setFieldAllSubstituteValues ( ifds::OrdStatus, idDataGroup,	OrdStatusSubst	);
      }
   }
   else if (str == DONOT_SEND  )
   {
      SetReadOnlyForUpdateingFields( idDataGroup, false );
      // remove "Aggregate" and "Sent"  from the list
      if (pBFPropertiesAllOrdStatus)
      {
         DString allOrdStatus, OrdStatusSubst;

         pBFPropertiesAllOrdStatus->getAllSubstituteValues (OrdStatusSubst);

         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, AGGREGATED  );
         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, ORDER_SENT  );

         setFieldAllSubstituteValues ( ifds::OrdStatus, idDataGroup,	OrdStatusSubst	);
      }
   }
   else if ( str == PRICE_LOADED )
   {
      SetReadOnlyForUpdateingFields( idDataGroup, false );

      /* this logic alraedy handled by SetReadOnlyForUpdateingFields
      DString dstrPriceType;
      getField (ifds::AggrPriceType, dstrPriceType, idDataGroup);
      if ( str == OFFER_PRICE )
         setFieldReadOnly (ifds::RebateRate, idDataGroup, true);
      else
         setFieldReadOnly (ifds::RebateRate, idDataGroup, false); */

            //remove "Aggregate", "Do not Send" and "Sent" from the list
      if (pBFPropertiesAllOrdStatus)
      {
         DString allOrdStatus, OrdStatusSubst;

         pBFPropertiesAllOrdStatus->getAllSubstituteValues (OrdStatusSubst);

         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, AGGREGATED  );
         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, ORDER_SENT  );
         OrdStatusSubst = removeItemFromSubtList ( OrdStatusSubst, DONOT_SEND  );


         setFieldAllSubstituteValues ( ifds::OrdStatus, idDataGroup,	OrdStatusSubst	);
      }

   }
   else if ( str == PRICE_POSTED )
   {
      SetReadOnlyForUpdateingFields( idDataGroup, true );
      setFieldReadOnly (ifds::OrdStatus, idDataGroup, true);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::getFundFeeList( FundFeeList *&pFundFeeList, 
                                          const DString feeCode, 
                                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundFeeList" ) );
   SEVERITY  sevRtn = NO_CONDITION;
   DString fundCode, classCode, effectiveDate, broker , stopdate;

   getField (ifds::BrkSettlDate, effectiveDate, idDataGroup);
   stopdate = effectiveDate;
   if (feeCode == FUND_BROKER_EXTERNAL_CHARGE || feeCode == FUND_BROKER_COMMISSION)
   {
      getField (ifds::FundBrokerCode, broker, idDataGroup);
   }
   else if (feeCode == REBATE_AMOUNT)
   {
      getField (ifds::FundCode, fundCode, idDataGroup);
      getField (ifds::ClassCode, classCode, idDataGroup);
      broker = NULL_STRING;
   }

   DString strKey = 
         I_("FundFeeList_FeeCode")  + feeCode         +
         I_(";FundCode=")           + fundCode        +
         I_(";ClassCode=")          + classCode       +
         I_(";EffectiveDate=")      + effectiveDate   +
         I_(";CommGroup=")          + broker          +
         I_(";AccountNum=")         + NULL_STRING     +
         I_(";Broker=")             + NULL_STRING     +
         I_(";Branch=")             + NULL_STRING     +
         I_(";SlsrepCode=")         + NULL_STRING     +
         I_(";stopdate=")           + stopdate        +
         I_(";FeeModelCode=")       + NULL_STRING;

   pFundFeeList = new FundFeeList (*this);
   if ( pFundFeeList->init ( feeCode, 
                             fundCode,
                             classCode,
                             broker,
                             effectiveDate,
                             NULL_STRING,
                             I_("FindRecord"),
                             NULL_STRING, 
                             NULL_STRING, 
                             NULL_STRING,
                             NULL_STRING,
                             stopdate, 
                             NULL_STRING, 
                             NULL_STRING, 
                             NULL_STRING, 
                             NULL_STRING) <= WARNING)
   {
      setObject ( pFundFeeList, strKey, OBJ_ACTIVITY_NONE, idDataGroup );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::PriceTypeRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "PriceTypeRelatedChanges" ) );
   SEVERITY  sevRtn = NO_CONDITION;

   DString dstrPriceType,  dstrFundBrokerCode, dstrFeeCode;
   DString dstrTradeDate, dstrEffectiveDate, dstrRebateRate; 
   DString dstrCommission, dstrExternCharge, dstrCurrency;

   getField ( ifds::TradeDate, dstrTradeDate, idDataGroup );

   getField(ifds::FundBrokerCode, dstrFundBrokerCode, idDataGroup);


   FundFeeList *pFundFeeList = NULL;
   FundBrokerFeeList *pFundBrokerFeeList = NULL;

   getField(ifds::AggrPriceType, dstrPriceType, idDataGroup);
   dstrPriceType.strip();
   if( dstrPriceType == NAV || dstrPriceType == BROKER_PRICE )
   {
      if( (getFundFeeList( pFundFeeList, FUND_BROKER_EXTERNAL_CHARGE, idDataGroup)) <= WARNING 
          && pFundFeeList )
      {
         pFundFeeList->getField(ifds::Rate, dstrExternCharge, idDataGroup);
         setFieldNoValidate (ifds::ExternCharge, dstrExternCharge, idDataGroup,true, true, true, true );

      }
      if( (getFundFeeList( pFundFeeList, FUND_BROKER_COMMISSION, idDataGroup)) <= WARNING 
         && pFundFeeList )
      {
         pFundFeeList->getField(ifds::Rate, dstrCommission, idDataGroup);
         setFieldNoValidate (ifds::Commission, dstrCommission, idDataGroup,true, true, true, true );
      }
      dstrRebateRate = I_("0.00");
      setFieldNoValidate (ifds::RebateRate, dstrRebateRate, idDataGroup,true, true, true, true ); 
      setFieldReadOnly (ifds::RebateRate, idDataGroup, true);
   //	setFieldReadOnly (ifds::Commission, idDataGroup, false);
   //	setFieldReadOnly (ifds::ExternCharge, idDataGroup, false);
   }
   else if( dstrPriceType == OFFER_PRICE )
   {
      if( (getFundFeeList( pFundFeeList, REBATE_AMOUNT, idDataGroup)) <= WARNING  && pFundFeeList )
      {
         pFundFeeList->getField(ifds::Rate, dstrRebateRate, idDataGroup);
         setFieldNoValidate (ifds::RebateRate, dstrRebateRate, idDataGroup,true, true, true, true );
      }
      setFieldReadOnly (ifds::RebateRate, idDataGroup, false);
      dstrCommission = I_("0.00");
      setFieldNoValidate (ifds::Commission, dstrCommission, idDataGroup,true, true, true, true );
      //setFieldReadOnly (ifds::Commission, idDataGroup, true);

      dstrExternCharge = I_("0.00");
      setFieldNoValidate (ifds::ExternCharge, dstrExternCharge, idDataGroup,true, true, true, true );
      //setFieldReadOnly (ifds::ExternCharge, idDataGroup, true);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::SettlInstrCodeRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "SettlInstrCodeRelatedChanges" ) );
   SEVERITY  sevRtn = NO_CONDITION;

   DString dsrSettlInstrCode;
   getField(ifds::SettlInstrCode, dsrSettlInstrCode, idDataGroup);
   dsrSettlInstrCode.strip().upperCase();

   FundBrokerSettlementInstrList *pSettlementInstrList = NULL;
   FundBrokerSettlementInstr *pFundBrokerSettlementInstr = NULL;
   getSettlementInstrList( pSettlementInstrList, idDataGroup);
   if (pSettlementInstrList)
   {
      pSettlementInstrList->getFundBrokerSettlementInstr( dsrSettlInstrCode, idDataGroup,
                                                          pFundBrokerSettlementInstr );
      if (pFundBrokerSettlementInstr)
      {
         DString dsrDeliveryTo, dsrForAccount, dstrInFavourOf;
         pFundBrokerSettlementInstr->getField(ifds::DeliveryTo, dsrDeliveryTo, idDataGroup);
         setFieldNoValidate (ifds::DeliveryTo, dsrDeliveryTo, idDataGroup, true, true, true, true );

         pFundBrokerSettlementInstr->getField(ifds::ForAccount, dsrForAccount, idDataGroup);
         setFieldNoValidate (ifds::ForAccount, dsrForAccount, idDataGroup, true, true, true, true );

         pFundBrokerSettlementInstr->getField(ifds::InFavourOf, dstrInFavourOf, idDataGroup);
         setFieldNoValidate (ifds::InFavourOf, dstrInFavourOf, idDataGroup, true, true, true, true );
      }
   }

   if( dsrSettlInstrCode == I_("N/A") )
   {
      setFieldReadOnly (ifds::DeliveryTo, idDataGroup, false);
      setFieldReadOnly (ifds::ForAccount, idDataGroup, false);
      setFieldReadOnly (ifds::InFavourOf, idDataGroup, false);
      for( int i=0; i< numSttlInstrReadOnlyFields; i++)
      {
        setFieldReadOnly( SttlInstrReadOnlyFields[i], idDataGroup, false);
      }
   }
   else
   {
      setFieldReadOnly (ifds::DeliveryTo, idDataGroup, true);
      setFieldReadOnly (ifds::ForAccount, idDataGroup, true);
      setFieldReadOnly (ifds::InFavourOf, idDataGroup, true);
      for( int i=0; i< numSttlInstrReadOnlyFields; i++)
      {
        setFieldReadOnly( SttlInstrReadOnlyFields[i], idDataGroup, true);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AggregatedOrder::SetReadOnlyForUpdateingFields( const BFDataGroupId& idDataGroup, bool bReadOnly )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "SetReadOnlyForUpdateingFields" ) );
   SEVERITY  sevRtn = NO_CONDITION;

   DString dstrPriceType, dstrReasonCode;
   bool bBearerCert = false;

   getField(ifds::AggrPriceType, dstrPriceType, idDataGroup);
   dstrPriceType.strip().upperCase();

   getField(ifds::ReasonCode, dstrReasonCode, idDataGroup);
   bBearerCert = ( dstrPriceType.strip().upperCase() == BEARER_CERTIFICATE );
   DString dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup);

   DString dstrAmountType;
   getField(ifds::AmountType, dstrAmountType, idDataGroup);
   setFieldReadOnly (ifds::AggrPriceType, idDataGroup, ( bReadOnly || bBearerCert || dstrTransType== I_("PW")|| dstrAmountType.strip().upperCase() == AMOUNT ) );
   setFieldReadOnly (ifds::Price, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::BrkSettlDate, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::BrkSettlAmtUnits, idDataGroup, (bReadOnly || bBearerCert));
   setFieldReadOnly (ifds::RebateRate, idDataGroup, (bReadOnly || dstrPriceType != OFFER_PRICE || bBearerCert)); // if not Offer Price, it must be read only
   setFieldReadOnly (ifds::ExternCharge, idDataGroup, (bReadOnly  || bBearerCert)); // Ticket 10038242 -- Does not need check PriceType any more, because it should be applicable for all three kind of price types
   setFieldReadOnly (ifds::Commission, idDataGroup, (bReadOnly || bBearerCert)); //Ticket 10038242 -- Does not need check PriceType any more, because it should be applicable for all three kind of price type
   setFieldReadOnly (ifds::ClrSettlMethod, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::SettleLocationCode, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::SettlInstrCode, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::DeliveryTo, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::ForAccount, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::InFavourOf, idDataGroup, bReadOnly);
   for( int i=0; i< numSttlInstrReadOnlyFields; i++)
   {
     setFieldReadOnly( SttlInstrReadOnlyFields[i], idDataGroup, bReadOnly);
   }
   // Incident #318565 -- Original Aggr Order business rule only allow update of Remarks once th e Status has been changed to Price Posted.
   // TradeDate enhancement should align with it.
   setFieldReadOnly (ifds::TradeDate, idDataGroup, ( bReadOnly || !getWorkSession().hasUpdatePermission (UAF::AGGREGATED_ORDER_TRADE_DATE)));
   //if ( ! bReadOnly )
      //setSttlLocationAndInstr( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::getPendingTradeList ( PendingTradeList *&pPendingList, 
                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPendingTradeList" ) );
   TradeSearchCriteria *pTradeSearchCriteria  =
      dynamic_cast <TradeSearchCriteria*> (getObject (I_("TradeSearchCriteria"), idDataGroup));

   if (!pTradeSearchCriteria)
   {
      pTradeSearchCriteria = new TradeSearchCriteria (*this);

      DString dstrAggrOrdId;
      
      pTradeSearchCriteria->init();
      getField (ifds::OmnibusID, dstrAggrOrdId, idDataGroup);
      pTradeSearchCriteria->setField (ifds::SearchType, I_("ExternalIdType"), idDataGroup);
      pTradeSearchCriteria->setField (ifds::ExternalIdType, I_("OMNI"), idDataGroup);  
      pTradeSearchCriteria->setField (ifds::ExternalId, dstrAggrOrdId, idDataGroup);
      if (pTradeSearchCriteria->getPendingTradeList (pPendingList, idDataGroup) <= WARNING)
      {
         setObject (pTradeSearchCriteria, I_("TradeSearchCriteria"), OBJ_ACTIVITY_NONE, idDataGroup);
      }
   }
   else
   {
      pPendingList = dynamic_cast <PendingTradeList *> 
         (pTradeSearchCriteria->getObject (I_("PendingList"), idDataGroup));
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AggregatedOrder::getAggregatedOrderPendingTrades ( PendingTradeList *pAggregatedOrderPendingTrades,
                                                            const DString &tradeDate,
                                                            const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAggregatedOrderPendingTrades"));


//the caller should create the pointer for us   
   assert (pAggregatedOrderPendingTrades);

   PendingTradeList *pPendingList = NULL;
   if ( getPendingTradeList (pPendingList, idDataGroup) <= WARNING &&
        pPendingList)

   {
      for (BFObjIter iter (*pPendingList, idDataGroup ); !iter.end(); ++iter)
      {
         PendingTradeDetails *pPendingTradeDetails = 
            dynamic_cast <PendingTradeDetails *> (iter.getObject());

         if (pPendingTradeDetails)
         {
            //set the trade date in any circumstance...
            if (setTradeDateOnEachPendingTrade ( pPendingList, 
                                                 pPendingTradeDetails, 
                                                 tradeDate, 
                                                 idDataGroup) > WARNING)
            {
//clear the errors...
               int count = CONDITIONCOUNT();
               Condition *c = NULL;
               for (int i = 0; i < count; i++)
               {
                  CLEARCONDITION( i );
               }
            }
         }
         pPendingList->getItem (iter.getStringKey(), idDataGroup, YES);
         //set the object on the caller's list
         pAggregatedOrderPendingTrades->setObject ( iter.getObject(),
                                                    iter.getStringKey(),
                                                    OBJ_ACTIVITY_NONE,
                                                    idDataGroup,
                                                    OBJ_TYPE_NONE,
                                                    BFCBO::OBJ_DELETE::NO_DELETE_ON_DTOR);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
int AggregatedOrder::getNumberOfLossTrade (const BFDataGroupId &idDataGroup)
{
   PendingTradeList *pPendingList = NULL;

   if ( getPendingTradeList (pPendingList, idDataGroup) <= WARNING &&
        pPendingList)
   {
      DString dstrLossCount;

      pPendingList->getField (ifds::LossCount, dstrLossCount, idDataGroup, false);
      m_iNumberOfLossTrade = dstrLossCount.asInteger();
   }
   return m_iNumberOfLossTrade;

}
//******************************************************************************
SEVERITY AggregatedOrder::ForceToDoCalculation(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ForceToDoCalculation" ) );

   // Before force culculate, the price and brkSettlAmtUnit must be validated

   BFCBO::validateAll( idDataGroup );
   //validateStatusPriceBrkSettlAmtUnits( idDataGroup );
   //ValidateOrdStatus( strValue, idDataGroup );

   if ( GETCURRENTHIGHESTSEVERITY() > WARNING )
         return(GETCURRENTHIGHESTSEVERITY());

   //to do calculation
   DString dstrRecalculate;

   getField (ifds::Recalculate, dstrRecalculate, idDataGroup, false);

   if	( dstrRecalculate.strip().upperCase() == YES  )
   {
      /*
      1. get those fields for the view call
      2. make view call 
      3. set calculated fileds
      4. m_iNumberOfLossTrade = getNumberOfLossTrade( idDataGroup );
      */
      BFObjIter iter (*this, idDataGroup);

      iter.positionByKey (I_("TradeSearchCriteria"));
      if (!iter.end ())
      {
         iter.removeObjectFromMap (true);
      }

      BFData query324 (ifds::DSTC0324_REQ);

      DString mgmtCoIdOut, tempstr;

      //set the request   
      query324.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
      query324.setElementValue (ifds::Track, I_("N"));
      query324.setElementValue (ifds::Activity, NULL_STRING );

      getField (ifds::OmnibusID, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::OmnibusID, tempstr);

      getField (ifds::BrkSettlDate, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::BrkSettlDate, tempstr);

      getField (ifds::BrkSettlAmtUnits, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::BrkSettlAmtUnits, tempstr);

      getField (ifds::BrkSettlPUD, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::BrkSettlPUD, tempstr);

      getField (ifds::Price, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::Price, tempstr);

	  getField (ifds::Amount, tempstr, idDataGroup, false);
	  query324.setElementValue (ifds::Amount, tempstr);

      getField (ifds::AggrPriceType, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::AggrPriceType, tempstr);

      getField (ifds::Commission, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::Commission, tempstr);


      getField (ifds::ExternCharge, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::ExternCharge, tempstr);

      getField (ifds::RebateRate, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::RebateRate, tempstr);

      getField (ifds::OrdStatus, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::OrdStatus, tempstr);

      getField (ifds::DeliveryTo, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::DeliveryTo, tempstr);

      getField (ifds::ForAccount, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::ForAccount, tempstr);

      getField (ifds::InFavourOf, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::InFavourOf, tempstr);

      getField (ifds::ClrSettlMethod, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::ClrSettlMethod, tempstr);

      getField (ifds::SettlInstrCode, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::SettlInstrCode, tempstr);

      getField (ifds::SettleLocationCode, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::SettleLocationCode, tempstr);

      getField (ifds::AggrOrdId, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::AggrOrdId, tempstr);

      getField (ifds::AggrOrdVer, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::AggrOrdVer, tempstr);

      query324.setElementValue (ifds::Recalculate, YES);

      getField (ifds::RemarksAggr, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::RemarksAggr, tempstr);

      getField (ifds::TradeDate, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::TradeDate, tempstr);

      getField (ifds::SecRecFileIndicator, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::SecRecFileIndicator, tempstr);

      getField (ifds::IntermediaryBank, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::IntermediaryBank, tempstr);

      getField (ifds::CashMsgType, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::CashMsgType, tempstr);

      getField (ifds::ReceivingBank, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::ReceivingBank, tempstr);

      getField (ifds::Beneficiary, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::Beneficiary, tempstr);

      getField (ifds::SpecialInstructions, tempstr, idDataGroup, false);
      query324.setElementValue (ifds::SpecialInstructions, tempstr);

      query324.setElementValue (ifds::RunMode, I_("M"));

      BFData *response = new BFData(ifds::DSTC0324_VW);

      if (BFDataBroker::getInstance()->receive ( DSTC_REQUEST::AGGREGATED_ORDER_LIST_UPDATE, 
                                                 query324, *response, DSTCRequestor (getSecurity ())) > WARNING )
      {
         delete response;
         response = NULL;
         return GETCURRENTHIGHESTSEVERITY();
      }

      // To fix version do not match issue, move following code to setCuculatedFields
      /*else
      {
         DString dstrNewAggrOrdVer;
         //read the response and refresh the data in the object
         dstrNewAggrOrdVer = response->getElementValue (ifds::NewAggrOrdVer);
         dstrNewAggrOrdVer.strip();  
         setFieldNoValidate (ifds::AggrOrdVer, dstrNewAggrOrdVer, idDataGroup );
         setFieldNoValidate (ifds::Recalculate, NO, idDataGroup ); //reset it to NO after refresh
      }*/

      // Incident #288887 -- For the purpose to return a warning message, view side change NewAggrOrdVer to WarnMsgCode
      DString dstrWarnMsgCode;
      dstrWarnMsgCode = response->getElementValue (ifds::WarnMsgCode);
      dstrWarnMsgCode.strip();  
      setFieldNoValidate (ifds::WarnMsgCode, dstrWarnMsgCode, idDataGroup );
      setFieldValid( ifds::BrkSettlAmtUnits, idDataGroup, false );

      setCuculatedFields(idDataGroup);
      setFieldNoValidate (ifds::AggrOrdRefreshed, YES, idDataGroup ); // Set to YES after refresh
      if(response)
      {
         delete response;
         response = NULL;
      }

      // avoid making another call to v323; moduser needs to be set for more validation
      DString modUser, currBusDate;

      const DSTCSecurity* pDSTCSecurity(getSecurity());

      if (pDSTCSecurity != NULL)
      {
         modUser = pDSTCSecurity -> getUserId();
         setFieldNoValidate (ifds::ModUser, modUser, idDataGroup ); 
      }
      getWorkSession ().getOption ( ifds::CurrBusDate, 
                                    currBusDate, 
                                    BF::HOST, 
                                    false);
      setFieldNoValidate (ifds::ModDate, currBusDate, idDataGroup ); 

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::setCuculatedFields(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ForceToDoCalculation" ) );  

   BFData query323 (ifds::DSTC0323_REQ);

   //set the request

   DString mgmtCoIdOut, tempstr;

   query323.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   query323.setElementValue (ifds::Track, I_("N"));
   query323.setElementValue (ifds::Activity, NULL_STRING );


   getField (ifds::OmnibusID, tempstr, idDataGroup, false);
   query323.setElementValue (ifds::OmnibusID, tempstr);

   query323.setElementValue( ifds::FromDate, NULL_STRING );
   query323.setElementValue( ifds::ToDate, NULL_STRING );
   query323.setElementValue( ifds::rxOrdStatus, NULL_STRING );
   query323.setElementValue( ifds::FundBroker, NULL_STRING );
   query323.setElementValue( ifds::FundCode, NULL_STRING );
   query323.setElementValue( ifds::RoutingRef, NULL_STRING );
   query323.setElementValue( ifds::SearchType, I_( "AORDNUM " ) );

   BFData *_pView323Data = new BFData(ifds::DSTC0323_VW);


   if (BFDataBroker::getInstance()->receive ( DSTC_REQUEST::AGGREGATED_ORDER_LIST, 
                                              query323, *_pView323Data, DSTCRequestor (getSecurity ())) > WARNING )
   {
      delete _pView323Data;
      _pView323Data = NULL;
      return GETCURRENTHIGHESTSEVERITY();
   }

   int cRepeats = _pView323Data->getRepeatCount();
   if (0 != cRepeats)
   {
      const BFData &data = _pView323Data->getRepeat(0);

      DString dstrAFTBenefit, dstrNAV, dstrOfferPrice;
      //read the response and refresh the data in the object
      dstrAFTBenefit = data.getElementValue (ifds::AFTBenefit );
      dstrAFTBenefit.strip();  
      setFieldNoValidate (ifds::AFTBenefit, dstrAFTBenefit, idDataGroup, true, true, true );

      dstrNAV = data.getElementValue (ifds::NAV );
      dstrNAV.strip();  
      setFieldNoValidate (ifds::NAV, dstrNAV, idDataGroup, true, true, true );

      dstrOfferPrice = data.getElementValue (ifds::OfferPrice );
      dstrOfferPrice.strip();  
      setFieldNoValidate (ifds::OfferPrice, dstrOfferPrice, idDataGroup, true, true, true );
      // To fix "version do not match" issue
      DString dstrNewAggrOrdVer;
      dstrNewAggrOrdVer = data.getElementValue (ifds::AggrOrdVer);
      dstrNewAggrOrdVer.strip();  
      setFieldNoValidate (ifds::AggrOrdVer, dstrNewAggrOrdVer, idDataGroup );
      setFieldNoValidate (ifds::Recalculate, NO, idDataGroup ); //reset it to NO after refres

   }
   if (_pView323Data )
   {
      delete _pView323Data;
      _pView323Data = NULL;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::ValidateOrdStatus( const DString& strValue,
                                             const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateOrdStatus" ) );

    // don't do validation for API
    if ( bfutil::isServerContext() )
    {
      DString dstrWarnMsgCode;
      getField(ifds::WarnMsgCode, dstrWarnMsgCode, idDataGroup);
      dstrWarnMsgCode.strip();
      if ( dstrWarnMsgCode == I_("654") || dstrWarnMsgCode == I_("655") )
      {
         ADDCONDITIONFROMFILE ( CND::WARN_LOSS_SITUATION );
      }
        return (GETCURRENTHIGHESTSEVERITY());
    }
   /*Check OrdStatus, 
   If OrdStatus is "Price Loaded" or "Price Posted", check m_iNumberOfLossTrade, 
   if it is -1, means the refresh button has not been  pressed, 
      and the trade was  not been calculated, issue error "not a valid status"*/
   int m_iNumberOfLossTrade = getNumberOfLossTrade( idDataGroup );
   if( ( strValue == PRICE_LOADED || strValue == PRICE_POSTED )&&  m_iNumberOfLossTrade < 0 )
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_STATUS);
   }
   else if (strValue == PRICE_POSTED && m_iNumberOfLossTrade != 0 )
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_STATUS);
   }

   // user who did price_load cannot be the same person to do price_post;
   // validation to be done only if moduser is not blank; API is able to PRICE_POST directly without
   // prior modify

   if (GETCURRENTHIGHESTSEVERITY() <= WARNING )
   {
      if (!bfutil::isServerContext())
      {
         if (strValue == PRICE_POSTED) 
         {
            DString dstrPreviousUser;
            getField(ifds::ModUser, dstrPreviousUser, idDataGroup);	

            if (_oldOrdStatus != PRICE_LOADED && dstrPreviousUser == NULL_STRING)
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_STATUS);
            }
            else
            {
               if (dstrPreviousUser != NULL_STRING)
               {
                  const DSTCSecurity* pDSTCSecurity(getSecurity());

                  if (pDSTCSecurity != NULL)
                  {
                     DString dstrCurrentUser;

                     dstrCurrentUser = pDSTCSecurity -> getUserId();
                     
                     if (dstrCurrentUser == dstrPreviousUser)
                     {
                        ADDCONDITIONFROMFILE (CND::ERR_PRCPOSTER_SAME_AS_PRCLOADER);
                     }

                  }
               }
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::validateAggrPriceType( const DString& strValue,
                                                 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAggrPriceType" ) );

   DString dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup);
   if(dstrTransType.strip().upperCase() == I_("PW") && strValue != NAV )
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_PRICE_TYPE);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::validateStatusPriceBrkSettlAmtUnits( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateStatusPriceBrkSettlAmtUnits" ) );

   DString dstrReasonCode, dstrOrdStatus;
   getField (ifds::ReasonCode, dstrReasonCode, idDataGroup, false);
   getField (ifds::OrdStatus, dstrOrdStatus, idDataGroup, false);

   if ( dstrReasonCode.strip() != BEARER_CERTIFICATE && dstrOrdStatus == PRICE_LOADED )
   {
      DString dstrPrice, dstrBrkSettlAmtUnits;
      getField (ifds::Price, dstrPrice, idDataGroup, false);
      double dec_Price = DSTCommonFunctions::convertToDouble( dstrPrice );
      if ( dec_Price == 0 )
      {
         // Issue error "Price can not be zero."
         ADDCONDITIONFROMFILE (CND::ERR_PRICE_CANNOT_BE_ZERO);
      }

      getField (ifds::BrkSettlAmtUnits, dstrBrkSettlAmtUnits, idDataGroup, false);
      double dec_BrkSettlAmtUnits = DSTCommonFunctions::convertToDouble( dstrBrkSettlAmtUnits );
      if ( dec_BrkSettlAmtUnits ==0 )
      {
         // Issue error "Broker settlement amount can not be zero."
         ADDCONDITIONFROMFILE (CND::ERR_BROKER_STTL_AMOUNT_CANNOT_BE_ZERO);
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::getFndMgmtSettlementInstrList( FundMgmtSettlementInstrList *&pFundMgmtSettlementInstrList, 
                                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFndMgmtSettlementInstrList" ) );
   DString dsrFundBrokerCode, dstrSettleInstrSubstList, dstrSettleLocSubstList, dstrSettleLocationCode;

   getField(ifds::FundBrokerCode, dsrFundBrokerCode, idDataGroup );
   dsrFundBrokerCode.strip();

   if (dsrFundBrokerCode != NULL_STRING)
   {
      if ( !pFundBrokerList)
           getWorkSession().getFundBrokerList (pFundBrokerList, idDataGroup, true, dsrFundBrokerCode);

      if ( pFundBrokerList )
      {
         FundBroker *pFundBroker = NULL;
         if ( pFundBrokerList->getFundBroker ( dsrFundBrokerCode, idDataGroup, pFundBroker)
               <= WARNING && pFundBroker )
         {
            pFundBroker->getFndMgmtSettlementInstrList( pFundMgmtSettlementInstrList, idDataGroup);
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::getSettlementInstrList(   FundBrokerSettlementInstrList *&pSettlementInstrList, 
                                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundBrokerSettlementInstrList" ) );

   DString dsrFundBrokerCode;
   getField(ifds::FundBrokerCode, dsrFundBrokerCode, idDataGroup );
   dsrFundBrokerCode.strip();

   if (dsrFundBrokerCode != NULL_STRING)
   {
      if ( !pFundBrokerList )
         getWorkSession().getFundBrokerList (pFundBrokerList, idDataGroup, true, dsrFundBrokerCode );
      if ( pFundBrokerList )
      {
         FundBroker *pFundBroker = NULL;
         if ( pFundBrokerList->getFundBroker ( dsrFundBrokerCode, idDataGroup, pFundBroker)
            <= WARNING && pFundBroker )
         {
            pFundBroker->getSettlementInstrList( pSettlementInstrList, idDataGroup);
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AggregatedOrder::setSettleAccountNum( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettleAccountNum" ) );

   FundMgmtSettlementInstrList *pFundMgmtSettlementInstrList = NULL;
   FundMgmtSettlementInstr *pFundMgmtSettlementInstr = NULL;
   DString dstrSettleLocationCode, FromSettleLocationCode, dstrSettleAccountNum;
   getField (ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup, false);

   if (getFndMgmtSettlementInstrList(  pFundMgmtSettlementInstrList, idDataGroup ) <= WARNING
                                       && pFundMgmtSettlementInstrList)
   {
      for ( BFObjIter Iter( *pFundMgmtSettlementInstrList, idDataGroup, true,	BFObjIter::ITERTYPE::NON_DELETED ); !Iter.end(); ++Iter )
      {
         pFundMgmtSettlementInstr = dynamic_cast<FundMgmtSettlementInstr*>( Iter.getObject() );

         pFundMgmtSettlementInstr->getField( ifds::SettleLocationCode, FromSettleLocationCode, idDataGroup );
         if ( dstrSettleLocationCode == FromSettleLocationCode )
         {
            pFundMgmtSettlementInstr->getField( ifds::SettleAccountNum, dstrSettleAccountNum, idDataGroup );
            setFieldNoValidate (ifds::SettleAccountNum,dstrSettleAccountNum, idDataGroup,true,true, true,true );
            break;
         }
      }
   }
   if( !isSetlLocationChanged(idDataGroup) )
    {
        DString dstrStlAcct, dstrIntStlAcct;
        getFieldBeforeImage( ifds::SettleAccountNum, dstrStlAcct);
        getFieldBeforeImage( ifds::InternalSettlementAccount, dstrIntStlAcct);
        setFieldNoValidate( ifds::SettleAccountNum , dstrStlAcct , idDataGroup, false, true, true, false);
        setFieldNoValidate( ifds::InternalSettlementAccount , dstrIntStlAcct , idDataGroup, false, true, true, false);
    }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::setSttlLocationAndInstr( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettleAccountNum" ) );

   DString dsrFundBrokerCode, dstrSettleInstrSubstList, dstrSettleLocSubstList;
   DString dsrSettlInstrCode, dstrSettleLocationCode;

   FundMgmtSettlementInstrList *pFundMgmtSettlementInstrList = NULL;
   getField(ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup);
   dstrSettleLocationCode.strip().upperCase();

   getFndMgmtSettlementInstrList( pFundMgmtSettlementInstrList, idDataGroup);
   if (pFundMgmtSettlementInstrList)
   {
      pFundMgmtSettlementInstrList->getSettlementLocationSubstList( dstrSettleLocSubstList, 
                                                                    idDataGroup );
      dstrSettleInstrSubstList.upperCase ();
      setFieldAllSubstituteValues (ifds::SettleLocationCode, idDataGroup, dstrSettleLocSubstList);
      setFieldNoValidate (ifds::SettleLocationCode,dstrSettleLocationCode, idDataGroup,true,true, true,true );
   }

   getField(ifds::SettlInstrCode, dsrSettlInstrCode, idDataGroup);
   dsrSettlInstrCode.strip().upperCase();
   FundBrokerSettlementInstrList *pSettlementInstrList = NULL;
   getSettlementInstrList( pSettlementInstrList, idDataGroup);
   if( pSettlementInstrList )
   {
      if ( pSettlementInstrList->getSettlementCodeSubstList( dstrSettleInstrSubstList, idDataGroup ) <= WARNING &&
           !dstrSettleInstrSubstList.strip().empty() )
      {
         dstrSettleInstrSubstList.upperCase ();
         setFieldAllSubstituteValues (ifds::SettlInstrCode, idDataGroup, dstrSettleInstrSubstList);
         setFieldNoValidate (ifds::SettlInstrCode,dsrSettlInstrCode, idDataGroup,true,true, true,true );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::setDecimalForAmount( DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDecimalForAmount" ) );
   DString dstrAmountType;
   int iUnitsPrecision = 2;
   getField(ifds::AmountType, dstrAmountType, idDataGroup );
   dstrAmountType.strip().upperCase();

   if ( dstrAmountType == I_("D") )
   {
      iUnitsPrecision = 2; 
      DSTCommonFunctions::formattedField (ifds::USDollar, iUnitsPrecision, strValue); 
   }
   else if ( dstrAmountType == I_("U"))
   {
      iUnitsPrecision = 4; 
      DSTCommonFunctions::formattedField (ifds::USDollar, iUnitsPrecision, strValue); 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AggregatedOrder::setDecimalForBrkSettlAmtUnits( DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDecimalForAmount" ) );
   DString dstrBrkSettlPUD;
   int iUnitsPrecision = 2;
   getField(ifds::BrkSettlPUD, dstrBrkSettlPUD, idDataGroup );
   dstrBrkSettlPUD.strip().upperCase();

   if ( dstrBrkSettlPUD == I_("D"))
   {
      iUnitsPrecision = 2; 
      DSTCommonFunctions::formattedField (ifds::USDollar, iUnitsPrecision, strValue); 
   }
   else if ( dstrBrkSettlPUD == I_("U"))
   {
      iUnitsPrecision = 4; 
      DSTCommonFunctions::formattedField (ifds::USDollar, iUnitsPrecision, strValue); 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AggregatedOrder::getField ( const BFFieldId &idField, 
                                 DString &fieldValue, 
                                 const BFDataGroupId &idDataGroup, 
                                 bool formattedReturn
                               ) const
{
   if ( idField == ifds::Amount && formattedReturn )
   {
      BFCBO::getField( idField, fieldValue, idDataGroup, false );
      (const_cast<AggregatedOrder*>(this))->setDecimalForAmount(fieldValue, idDataGroup);
   }
   else if ( idField == ifds:: BrkSettlAmtUnits && formattedReturn )
   {
      BFCBO::getField( idField, fieldValue, idDataGroup, false );
      (const_cast<AggregatedOrder*>(this))->setDecimalForBrkSettlAmtUnits(fieldValue, idDataGroup);
   }
   else
   {
      BFCBO::getField (idField, fieldValue, idDataGroup, formattedReturn);
   }
}

//************************************************************************************
SEVERITY AggregatedOrder::setField( const BFFieldId& idField, 
                                    const DString& dstrValue,
                                    const BFDataGroupId& idDataGroup, 
                                    bool  bFormatted, 
                                    bool  bSideEffect, 
                                    bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );   

   if( idField == ifds::BrkSettlDate )
   {
      DateValidation *pDateValidation = NULL;
      DString tradeDate, rxsettleDate;

      getField (ifds::TradeDate, tradeDate, idDataGroup, false);

      if( dstrValue == NULL_STRING )
      {
         if ( getDateValidation ( pDateValidation, 
                                  DATE_VALIDATION::DEFAULT_VALUE_DATE,
                                  tradeDate, 
                                  idDataGroup) <= WARNING &&
              pDateValidation)
         {
            pDateValidation->getField (ifds::SettleDate, rxsettleDate, idDataGroup, false);
         }
      }
      else
      {
         rxsettleDate = dstrValue;
      }
      BFCBO::setField( idField, rxsettleDate, idDataGroup, bFormatted, bSideEffect );
   }

   else
   {
      BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );
   }
     
   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
SEVERITY AggregatedOrder::getDateValidation ( DateValidation *&pDateValidation, 
                                              const DString &validationType,
                                              const DString &tradeDate, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDateValidation"));
   DString fundCode, 
           classCode, 
           payType, 
           transType, 
           broker, 
           brokerTo,
           orderType = I_("Y"), 
           settleCurrency,
           dealDate, 
           dealTime, 
           toFund, 
           toClass, 
           amount, 
           amtType, 
           accountNumTo, 
           fromCurrency, 
           toCurrency; 

   DString AccountNum, settleDate, depositDate, valueDate, settleInDate;

   getField (ifds::FundCode, fundCode, idDataGroup);
   getField (ifds::ClassCode, classCode, idDataGroup);
   fundCode.strip ().upperCase ();
   classCode.strip ().upperCase ();   

//call 135 always, even if fund and class are empty, for allocations...
//   if (!fundCode.empty() && !classCode.empty())
   {
      DString strKey;

      DateValidation::buildKey ( validationType,
                                 tradeDate,
                                 settleDate,
                                 depositDate,
                                 valueDate,
                                 transType,
                                 payType,
                                 broker,
                                 fundCode,
                                 classCode,
                                 toFund,
                                 toClass,
                                 orderType,
                                 dealDate,
                                 dealTime,
                                 settleCurrency,
                                 amount,
                                 amtType,
                                 strKey,
                                 NULL_STRING,  // AccountNum
                                 NULL_STRING,  // AccountNumTo
                                 NULL_STRING,  // fromCurrency
                                 NULL_STRING,  // toCurrency
                                 NULL_STRING   // settleInDate
                                 );
      pDateValidation = 
         dynamic_cast<DateValidation *> (getObject (strKey, idDataGroup));
      if (!pDateValidation)
      {
         pDateValidation = new DateValidation (*this);
         if (pDateValidation->init ( validationType,
                                     tradeDate,
                                     settleDate,
                                     depositDate,
                                     valueDate,
                                     transType,
                                     payType,
                                     broker,
                                     fundCode,
                                     classCode,
                                     toFund,
                                     toClass,
                                     orderType,
                                     dealDate,
                                     dealTime,
                                     settleCurrency,
                                     amount,
                                     amtType,
                                     settleInDate,
                                     brokerTo, 
                                     AccountNum,
                                     NULL_STRING,  // accountNumTo
                                     NULL_STRING,  // fromCurrency
                                     NULL_STRING   // toCurrency
                                     ) <= WARNING)
         {
            setObject (pDateValidation, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
         }
         else
         {
            delete pDateValidation;
            pDateValidation = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY (); 
}


//******************************************************************************
SEVERITY AggregatedOrder::CalculatBrkSettlAmt(const BFDataGroupId& idDataGroup, bool bRaiseError /*=false*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "CalculatBrkSettlAmt" ) );

      BFData query324 (ifds::DSTC0324_REQ);
   DString mgmtCoIdOut, tempstr;
   //set the request   
   query324.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   query324.setElementValue (ifds::Track, I_("N"));
   query324.setElementValue (ifds::Activity, NULL_STRING );

   getField (ifds::OmnibusID, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::OmnibusID, tempstr);

   getField (ifds::BrkSettlDate, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::BrkSettlDate, tempstr);

   getField (ifds::BrkSettlAmtUnits, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::BrkSettlAmtUnits, tempstr);

   getField (ifds::BrkSettlPUD, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::BrkSettlPUD, tempstr);

   getField (ifds::Price, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::Price, tempstr);

   getField (ifds::Amount, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::Amount, tempstr);	

   getField (ifds::AggrPriceType, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::AggrPriceType, tempstr);

   getField (ifds::Commission, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::Commission, tempstr);

   getField (ifds::ExternCharge, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::ExternCharge, tempstr);

   getField (ifds::RebateRate, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::RebateRate, tempstr);


   getField (ifds::OrdStatus, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::OrdStatus, tempstr);

   getField (ifds::DeliveryTo, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::DeliveryTo, tempstr);

   getField (ifds::ForAccount, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::ForAccount, tempstr);

   getField (ifds::InFavourOf, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::InFavourOf, tempstr);

   getField (ifds::ClrSettlMethod, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::ClrSettlMethod, tempstr);

   getField (ifds::SettlInstrCode, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::SettlInstrCode, tempstr);

   getField (ifds::SettleLocationCode, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::SettleLocationCode, tempstr);

   getField (ifds::AggrOrdId, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::AggrOrdId, tempstr);

   getField (ifds::AggrOrdVer, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::AggrOrdVer, tempstr);

   query324.setElementValue (ifds::Recalculate, YES);

   getField (ifds::RemarksAggr, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::RemarksAggr, tempstr);

   getField (ifds::TradeDate, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::TradeDate, tempstr);

   getField (ifds::SecRecFileIndicator, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::SecRecFileIndicator, tempstr);
      
   getField (ifds::IntermediaryBank, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::IntermediaryBank, tempstr);

   getField (ifds::CashMsgType, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::CashMsgType, tempstr);

   getField (ifds::ReceivingBank, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::ReceivingBank, tempstr);

   getField (ifds::Beneficiary, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::Beneficiary, tempstr);

   getField (ifds::SpecialInstructions, tempstr, idDataGroup, false);
   query324.setElementValue (ifds::SpecialInstructions, tempstr);

   query324.setElementValue (ifds::RunMode, I_("M"));
   query324.setElementValue (ifds::CalcBrkAmount, I_("Y"));

   BFData *response = new BFData(ifds::DSTC0324_VW);

   if ( BFDataBroker::getInstance()->receive ( DSTC_REQUEST::AGGREGATED_ORDER_LIST_UPDATE, 
                                               query324, *response, DSTCRequestor (getSecurity ())) > WARNING )
   {
      delete response;
      response = NULL;
      return GETCURRENTHIGHESTSEVERITY();
   }

   if (bRaiseError)
   {
	   DString dstrWarnMsgCode;
	   dstrWarnMsgCode = response->getElementValue (ifds::WarnMsgCode);
	   dstrWarnMsgCode.strip();
	
	   if ( dstrWarnMsgCode == CONFIRMED_AMOUNT_EXCEEDS_LIMIT )
	   {
		   ADDCONDITIONFROMFILE ( CND::ERR_AMOUNT_DOES_NOT_MATCH );
	   }
   }
   if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
   {
	   DString dstrBrkSettlAmtUnit, dstrBrkSettlPUD;
	   getField(ifds::BrkSettlPUD, dstrBrkSettlPUD, idDataGroup );
	   dstrBrkSettlPUD.strip().upperCase();

	   if ( dstrBrkSettlPUD == I_("D"))
	   {
		   dstrBrkSettlAmtUnit = response->getElementValue (ifds::BrkSettlAmt);
	   }
	   else
	   {
		   dstrBrkSettlAmtUnit = response->getElementValue (ifds::BrkSettlUnits);
	   }
	   dstrBrkSettlAmtUnit.strip();  
	   setFieldNoValidate (ifds::BrkSettlAmtUnits, dstrBrkSettlAmtUnit, idDataGroup );	
   }
   if(response)
   {
      delete response;
      response = NULL;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AggregatedOrder::setSecRecFileIndicator (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSecRecFileIndicator" ) );

   DString dstrMCHSRActive;

   getWorkSession().getOption ( ifds::MCHSRActive, 
                                 dstrMCHSRActive, 
                                 BF::HOST,
                                 false);

   dstrMCHSRActive.stripAll().upperCase();

   if (dstrMCHSRActive== YES)
   {
      //remove "N/A" from the list
      BFProperties *pBFPropertiesPPT = 
         getFieldProperties (ifds::SecRecFileIndicator, idDataGroup);

      if (pBFPropertiesPPT)
      {
         DString dstrSecRecFileIndicatorSubstList, dstrProcessedTrade;
         pBFPropertiesPPT->getAllSubstituteValues (dstrSecRecFileIndicatorSubstList);
         dstrSecRecFileIndicatorSubstList = 
               removeItemFromSubtList (dstrSecRecFileIndicatorSubstList, SUPPRESS_INDICATOR_DEFAULT_CODE);
         setFieldAllSubstituteValues ( ifds::SecRecFileIndicator, idDataGroup, dstrSecRecFileIndicatorSubstList	);

         getField (ifds::ProcessedTrade, dstrProcessedTrade, idDataGroup, false);
         dstrProcessedTrade.stripAll().upperCase();

         if (getWorkSession ().hasUpdatePermission  (UAF::MCH_AND_SECUR_REC_FILE_INDICATOR) && dstrProcessedTrade == NO) 
         {
            setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, false );
         }
         else
         {
            setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, true );
         }
      }
   }
   else
   {
      setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, true );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AggregatedOrder::setSubstituteValueForOrderStatus( const BFDataGroupId &idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "removeCancelrequestedFromOrderStatus" ) );
  
  BFProperties *pBFProperties = getFieldProperties (ifds::OrdStatus, idDataGroup);     
  DString dstrOrderStatusList, /*dstrNewOrderStatusList*/ dstrOrderStatus , dstrCurrrentUser, dstrRequestedUser,
          dstrLastModfiedStatus;

  assert( pBFProperties ) ;
  if( pBFProperties )
  {
   pBFProperties->reinitAllSubstValues();//Get the full list and not the operated one
   pBFProperties->getAllSubstituteValues (dstrOrderStatusList);
  }
  DString dstrBatchVerify; 
  getWorkSession().getOption ( ifds::BatchVerify, dstrBatchVerify, BF::HOST, false);

  getFieldBeforeImage( ifds::OrdStatus, dstrOrderStatus); 
  dstrOrderStatus.stripAll(); 
  if( !DSTCommonFunctions::codeInList ( dstrOrderStatus.stripAll(), ALLOWED_TO_CANCEL_STATUS ) ||
      YES != dstrBatchVerify ) //remove two step verification if verification not active
        dstrOrderStatusList =  removeItemFromSubtList ( dstrOrderStatusList,  CANCEL_REQUESTED );
  //canceled option should be avilable only after canacel requested in verification active env
  if( YES == dstrBatchVerify ) 
  {
      dstrOrderStatusList =  removeItemFromSubtList ( dstrOrderStatusList,  CANCELED );
      pBFProperties->setAllSubstituteValues(dstrOrderStatusList);
  }
  if( AGGREGATED == dstrOrderStatus )
  {
    pBFProperties->getAllSubstituteValues(dstrOrderStatusList);
    if (!dstrOrderStatusList.empty())
    {
        DString dstrNewSubList;//, dstrSubList;
        dstrNewSubList = dstrOrderStatusList;
        I_CHAR *temp = const_cast<I_CHAR*> (dstrOrderStatusList.c_str ());
        do
        {
            DString dstrStatusCode, dstrStatusDescr;
            temp = parseIdiString (temp, dstrStatusCode, dstrStatusDescr);         
            if( AGGREGATED != dstrStatusCode &&
                dstrStatusCode != CANCELED && dstrStatusCode != CANCEL_REQUESTED && temp) 
            {
              dstrNewSubList = removeItemFromSubtList ( dstrNewSubList,  dstrStatusCode );
            }
         } while (temp && temp != NULL_STRING && *temp);
        dstrOrderStatusList = dstrNewSubList;
     }
  }
  if( CANCEL_REQUESTED == dstrOrderStatus )
  { 
    const DSTCSecurity *pSecurity =
        dynamic_cast<const DSTCSecurity *>(getWorkSession ().getSecurity(DSTCHost::getPrimaryHost()));
    DString dstrCurrentUser = pSecurity->getUserId();
    dstrCurrentUser.stripAll().upperCase();  
    pBFProperties->reinitAllSubstValues();//Get the full list and not the operated one
    pBFProperties->getAllSubstituteValues(dstrOrderStatusList);
    getField( ifds::CancelRequestedUser, dstrRequestedUser, idDataGroup, false);
    dstrRequestedUser.stripAll().upperCase();
    getField( ifds::LastModfiedStatus, dstrLastModfiedStatus, idDataGroup );
    //remove the ability to verify the cancel requested if the user is the requested user.
    if( dstrRequestedUser == dstrCurrentUser)
        dstrOrderStatusList =  removeItemFromSubtList ( dstrOrderStatusList,  CANCELED );
    if (!dstrOrderStatusList.empty())
    {
        DString dstrNewSubList;// dstrSubList;
        dstrNewSubList = dstrOrderStatusList;
        I_CHAR *temp = const_cast<I_CHAR*> (dstrOrderStatusList.c_str ());
        do
        {
            DString dstrStatusCode, dstrStatusDescr;
            temp = parseIdiString (temp, dstrStatusCode, dstrStatusDescr);         
            if( dstrLastModfiedStatus != dstrStatusCode &&
                dstrStatusCode != CANCELED && dstrStatusCode != CANCEL_REQUESTED && temp ) 
              {
                 dstrNewSubList = removeItemFromSubtList ( dstrNewSubList,  dstrStatusCode );
              }
        } while (temp && temp != NULL_STRING && temp);
       dstrOrderStatusList = dstrNewSubList;
    }    
    
 } //  CANCEL_REQUESTED == dstrOrderStatus 
 if( CANCELED == dstrOrderStatus )
 {
    DString dstrNewSubList;
    pBFProperties->reinitAllSubstValues();//Get the full list and not the operated one
    pBFProperties->getAllSubstituteValues(dstrOrderStatusList);
    dstrNewSubList = dstrOrderStatusList;
    I_CHAR *temp = const_cast<I_CHAR*> (dstrOrderStatusList.c_str ());
    do
    {
        DString dstrStatusCode, dstrStatusDescr;
        temp = parseIdiString (temp, dstrStatusCode, dstrStatusDescr);         
        if( dstrStatusCode != CANCELED && temp) 
        {
            dstrNewSubList = removeItemFromSubtList ( dstrNewSubList,  dstrStatusCode );
        }
    } while (temp && temp != NULL_STRING && *temp);
    dstrOrderStatusList = dstrNewSubList;     
 }//  CANCELED == dstrOrderStatus 
 setFieldAllSubstituteValues ( ifds::OrdStatus, idDataGroup, dstrOrderStatusList);
}

//******************************************************************************
bool AggregatedOrder::isSetlLocationChanged( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isSetlLocationChnaged" ) );
   //For an exisiting aggregated order use the value stored in the omnibus-id for the settlement Account and Int Setl Acct
   //chnage in the exixiitng behaviour...
   DString dstrOrgLocCode, dstrNewLocCode;
   getFieldBeforeImage( ifds::SettleLocationCode, dstrOrgLocCode );
   getField(ifds::SettleLocationCode, dstrNewLocCode, idDataGroup );
   return ( dstrNewLocCode != dstrOrgLocCode );
}
//******************************************************************************
bool AggregatedOrder::isOrderAlreadyCancelled( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isOrderAlredayCancelled" ) );
   //For an exisiting aggregated order use the value stored in the omnibus-id for the settlement Account and Int Setl Acct
   //chnage in the exixiitng behaviour...
   DString dstrOrgStatus;
   getFieldBeforeImage( ifds::OrdStatus, dstrOrgStatus );
   dstrOrgStatus.stripAll();
   return ( CANCELED == dstrOrgStatus );
}
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AggregatedOrder.cpp-arc  $
// 
//    Rev 1.54   Jul 27 2011 11:00:40   wp040027
// PET P0186065 - Aggregated Amount Orders via Swift- Enable 'Orig Amt' field to allow user to enter broker confirmed amount
// 
//    Rev 1.53   Jun 09 2008 00:19:02   daechach
// in#1283327 - Trade created with invalid settlement date, Code review regarding modification of Trade and DateValidation CBO.
// 
//    Rev 1.52   Mar 21 2007 13:22:02   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.51   Jul 28 2006 10:44:28   popescu
// Incident# 668128 - changed the default value for SecrecFileIndincator to 2 instead of N/A; read the field if view 324 is called.
// 
//    Rev 1.50   Jan 12 2006 15:38:24   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Aggregate Order
// 
//    Rev 1.49   Nov 09 2005 10:31:02   popescu
// Incindent #359636 - set the value of rqdrefresh flag to true, so the field will be set to Y in 115
// 
//    Rev 1.48   Oct 20 2005 16:39:10   AGUILAAM
// PET1283_FN02:  additional validation requested
// 
//    Rev 1.47   Oct 13 2005 12:39:10   AGUILAAM
// PET1286_FN01: additional fix
// 
//    Rev 1.46   Oct 12 2005 17:06:20   AGUILAAM
// PET1286_FN02: additional validation for PRICE_POSTED status per Wendy
// 
//    Rev 1.45   Oct 05 2005 10:37:18   AGUILAAM
// PET1286_FN02_Verification of Aggregated Order Fund Price
// 
//    Rev 1.44   Aug 18 2005 16:49:18   fengyong
// Incident 379172 - call view 324 calculate settleAmt/Units
// 
//    Rev 1.43   Aug 05 2005 14:16:40   Fengyong
// Incident 366368 - If settledate set to null then use T+2 as the settledate
// 
//    Rev 1.42   Aug 04 2005 15:54:02   Fengyong
// Incident 366368 - Add ClrSettleMothod validation
// 
//    Rev 1.41   Jun 16 2005 20:18:22   popescu
// Incident# 328435 - enable trade modify button in any circumstances for an aggregated order with status price loaded
// 
//    Rev 1.40   Jun 14 2005 15:41:00   Fengyong
// #Incident 328435 - Add IgnoreActiveBatch field to 54 request
// 
//    Rev 1.39   May 31 2005 00:14:30   popescu
// Incident# 317930 - set the trade date in any circumstance
// 
//    Rev 1.38   May 30 2005 22:33:06   popescu
// Incident# 317930 - modified the getPendingTradeWithLoss method to also return the trades with errors when trade date is set.
// 
//    Rev 1.37   May 27 2005 17:27:46   Fengyong
// #Incident 317930 - modify function setTradeDateOnEachPendingTrade
// 
//    Rev 1.36   May 25 2005 14:13:42   ZHANGCEL
// Incident #318565 -- Change logic to follow the original rule for the TradeDate enhancement
// 
//    Rev 1.35   May 20 2005 14:46:56   Fengyong
// #Incident 295389 - only give warning for settle amount when #324 get back 578 warning code.
// 
//    Rev 1.34   Apr 28 2005 14:39:44   popescu
// Incident# 298886 - call 135 with validation type 4
// 
//    Rev 1.33   Apr 28 2005 11:16:04   Fengyong
// #28887 - Add condition for aggregate order 324 view return msgcode "WARN_LOSS_SITUATION" for API
// 
//    Rev 1.32   Apr 27 2005 14:03:44   popescu
// Incident# 298886 - should not render the trade date as invalid since if view 135 returns trade date failed = N
// 
//    Rev 1.31   Apr 27 2005 11:26:40   ZHANGCEL
// Incident #288887 -- Bug fix for the warning return from view324 issue
// 
//    Rev 1.30   Apr 25 2005 15:15:24   yingbaol
// Incindet279739: sync up version 1.20.1.5
// 
//    Rev 1.29   Apr 25 2005 13:59:00   popescu
// PET 1190/04  trade date aggregated order update - added the trade date field to the 324 request - 'ForceToDoCalculation' method
// 
//    Rev 1.28   Apr 18 2005 10:34:02   popescu
// Incident #285862, fixed validation issue with the trade date on the aggregated order screen
// 
//    Rev 1.27   Apr 14 2005 12:56:48   Fengyong
// Incident #287048: Allow change trade date only when function: Aggregated_Order_Trade_Date active.
// 
//    Rev 1.26   Apr 14 2005 11:18:56   yingbaol
// Incident 287048: sync. 1.20.1.4 validate pricetype
// 
//    Rev 1.25   Mar 29 2005 14:37:46   ZHANGCEL
// Incident #268038 -- Before press <Refresh>, validate all updated fields
// 
//    Rev 1.24   Mar 28 2005 17:05:14   ZHANGCEL
// Incident #268038 --force validateStatusPriceBrkSettlAmtUnits when the <Refresh> button get pressed
// 
//    Rev 1.23   Mar 23 2005 18:12:12   ZHANGCEL
// Incident #267769 -- Remove useless code and accelate the performance
// 
//    Rev 1.22   Mar 21 2005 16:47:06   Fengyong
// PET1190 FN04, trade date aggregated order update
// 
//    Rev 1.21   Mar 10 2005 09:46:10   popescu
// PET 1190/04, trade date aggregated order update
// 
//    Rev 1.19   Feb 28 2005 14:53:06   ZHANGCEL
// Magic #247576 -- Using AmountType rather than BrkSttlUPD
// 
//    Rev 1.18   Feb 25 2005 13:57:12   ZHANGCEL
// Magic #247576 -- Synch up from 1.11.1.9
// 
//    Rev 1.17   Feb 24 2005 17:22:54   ZHANGCEL
// Magic #247576 -- Synch up from 1.11.1.8
// 
//    Rev 1.16   Feb 10 2005 11:37:40   zhangcel
// PTS 10038581 -- Synch-up from 1.11.1.7
// 
//    Rev 1.15   Feb 03 2005 17:38:10   zhangcel
// Sync up to 1.11.1.6
// 
//    Rev 1.14   Jan 26 2005 11:18:04   zhangcel
// Correct the Sync up mistakes.
// 
//    Rev 1.13   Jan 26 2005 11:08:34   yingbaol
// Sync. up Version 1.11.1.0: PTS ticket 10038242 -- Change logic to make Commission and ExternalCharge are applicable for the three kind of PriceType
// 
//    Rev 1.12   Jan 26 2005 11:01:32   yingbaol
// PET1117 FN67 enhance Aggregate order for API
// 
//    Rev 1.11   Dec 17 2004 17:50:38   popescu
// PET 1117/56 remove comment for loss check
// 
//    Rev 1.10   Dec 17 2004 12:37:52   zhangcel
// PET 1117 FN 08 -- Add three new function for the Amount decimal setting
// 
//    Rev 1.9   Dec 15 2004 19:06:20   zhangcel
// PET1117 FN 08 -- More code enhancement
// 
//    Rev 1.8   Dec 10 2004 10:52:30   winnie
// PET 1117 FN08 : correct read only based for bearer certificate; initialize Recalculate for existing record to No; reset Recalculate to No after Force calculation of Price; Force calculation only should take place if certain fields are changed; changing settlement instr or remarks do not require recalculation.
// 
//    Rev 1.7   Dec 09 2004 14:46:52   winnie
// PET 1117 FN08 - Set fields to read only for inquiry of existing data based on the price type. Enable and disable field based on price type change or status change. Fix assignment for AggrVersion
// 
//    Rev 1.6   Dec 08 2004 18:08:12   winnie
// PET1117 FN08 : Add logic to the ForceToCalculate method to involve view 324 for Price Loaded operation
// 
//    Rev 1.5   Dec 08 2004 17:17:28   popescu
// PET 1117/56 build the loss pending trades list
// 
//    Rev 1.4   Dec 08 2004 12:42:02   zhangcel
// PET1117-FN08 More code for the enhancement
// 
//    Rev 1.3   Dec 03 2004 17:06:04   zhangcel
// PET 1117 FN 08 -- More logic implemented
// 
//    Rev 1.2   Nov 19 2004 15:25:08   zhangcel
// PET 1117 fn 08 -- Bug fix for StatusPriceBrkSettlAmtUnits
// 
//    Rev 1.1   Nov 19 2004 14:10:42   zhangcel
// PET 1117 FN8 -- Bug fix for the getPendingTradeList
// 
//    Rev 1.0   Nov 18 2004 13:55:54   zhangcel
// Initial revision.
// 

 */
