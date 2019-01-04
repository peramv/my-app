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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : DateValidation.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : May 5, 2000
//
// ^CLASS    : DateValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : This is for Trade date, settlement date and business date validation
//
//******************************************************************************


#include "stdafx.h"
#include "datevalidation.hpp"
#include <ifastdataimpl\dse_dstc0135_req.hpp>
#include <ifastdataimpl\dse_dstc0135_vw.hpp>
#include "errmsgruleslist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DATE_VALIDATION;
}

namespace
{
   const I_CHAR * const NO   = I_ ("N");
   const I_CHAR * const YES  = I_ ("Y");
   const I_CHAR * const Short_SETTLEDATE = I_ ("Short_SETTLEDATE");
   const I_CHAR * const SETTLEMENT_TYPE  = I_ ("SETTLEMENT_TYPE");
   const I_CHAR * const FUND_SETTLEMENT_TYPE = I_ ("FUND_SETTLEMENT_TYPE");

}
namespace IFASTERR
{
	 extern CLASS_IMPORT I_CHAR * const SETTLEDATE_LESS_THEN_FUND_LEVEL_SETTLEDATE;
}
namespace CND
{
   extern const long WARN_TRADE_DATE_PAST_CUTOFF_DATE;
   extern const long WARN_TRADING_TIME_PASSED_AGGREGATED_ORDER_CUTOFF_TIME;
   extern const long WARN_TRADING_TIME_PASSED_CLIENT_AND_AGGREGATED_ORDER_CUTTOF_TIME;
   extern const long WARN_CUSTOM_TRADING_SCHEDULE_IS_MISSING;
   extern const long WARN_TRADE_PASSED_FUND_CUTOFF_TIME;
   extern const long ERR_SETTLEDATE_LESS_THAN_FUND_LEVEL_SETTLEDATE;
   extern const long WARN_SETTLEDATE_LESS_THAN_FUND_LEVEL_SETTLEDATE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   {ifds::TradeDate,           BFCBO::NONE, 0}, 
   {ifds::TradeDateFailed,     BFCBO::NONE, 0}, 
   {ifds::SettleDate,          BFCBO::NONE, 0}, 
   {ifds::SettleDateFailed,    BFCBO::NONE, 0}, 
   {ifds::EffectiveDate,       BFCBO::NONE, 0}, 
   {ifds::EffectiveDateFailed, BFCBO::NONE, 0}, 
   {ifds::TradeInDate,         BFCBO::NONE, 0},
   {ifds::TradeInDateFailed,   BFCBO::NONE, 0},
};

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_ ("DateValidation");

}

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
DateValidation::DateValidation (BFAbstractCBO &parent) : MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

void DateValidation::buildKey ( const DString &validationType,
                                const DString &tradeDate,
                                const DString &settleDate,
                                const DString &depositDate,
                                const DString &valueDate,
                                const DString &transType,
                                const DString &payType,
                                const DString &broker,
                                const DString &fundCode,
                                const DString &classCode,
                                const DString &toFund,
                                const DString &toClass,
                                const DString &orderType,
                                const DString &dealDate,
                                const DString &dealTime,
                                const DString &settleCurrency,
                                const DString &amount,
                                const DString &amountType,
                                DString &strKey,
                                const DString &accountNum,
                                const DString &accountNumTo,
                                const DString &fromCurrency,
                                const DString &toCurrency,
                                const DString &settleInDate,
                                const DString &valuationDt,
								const DString &dstrNetworkID,
								const DString &tradeInDate,
								const DString &valuationInDate)
{
    DString strOrderType;

    strOrderType = orderType;
    strOrderType.strip().upperCase();

    if ( strOrderType != YES && strOrderType != NO )
    {
        if ( strOrderType == I_("WI") || strOrderType == I_("WIRE") )
        {
            strOrderType = YES;
        }
        else if ( strOrderType == I_("DI") || strOrderType == I_("DIRECT") )
        {
            strOrderType = NO;
        }
        else
        {
            strOrderType = YES;
        }
    }

    strKey = 
            I_("ValidationType=")   + validationType    +
            I_(";TradeDate=")       + tradeDate         +
            I_(";SettleDate=")      + settleDate        +
            I_(";DepositDate=")     + depositDate       +
            I_(";ValueDate=")       + valueDate         +
            I_(";TransType =")      + transType         +
            I_(";PayType=")         + payType           +
            I_(";Broker=")          + broker            +
            I_(";FundCode=")        + fundCode          +
            I_(";ClassCode=")       + classCode         +
            I_(";ToFund=")          + toFund            +
            I_(";ToClass=")         + toClass           +
            I_(";OrderType=")       + strOrderType      +
            I_(";DealDate=")        + dealDate          +
            I_(";DealTime=")        + dealTime          +
            I_(";SettleCurrency=")  + settleCurrency    +
            I_(";Amount=")          + amount            +
            I_(";AmountType=")      + amountType        +
            I_(";AccountNum=")      + accountNum        +
            I_(";AccountTo=")       + accountNumTo      +
            I_(";FrSettlCurrency=") + fromCurrency      +
            I_(";ToSettlCurrency=") + toCurrency        +
            I_(";SettleInDate=")    + settleInDate      + 
            I_(";ValuationDt=")     + valuationDt       +
            I_(";NetworkID=")       + dstrNetworkID     +
			I_(";TradeInDate=")      + tradeInDate       +
			I_(";ValuationInDt=")    + valuationInDate    ;
}

//******************************************************************************
DateValidation::~DateValidation (void)
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY DateValidation::init()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_("init"));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DateValidation::init ( const DString &validationType,
                                const DString &tradeDate,
                                const DString &settleDate,
                                const DString &depositDate,
                                const DString &valueDate,
                                const DString &transType,
                                const DString &payType,
                                const DString &broker,
                                const DString &fundCode,
                                const DString &classCode,
                                const DString &toFund,
                                const DString &toClass,
                                const DString &orderType,
                                const DString &dealDate,
                                const DString &dealTime,
                                const DString &settleCurrency,
                                const DString &amount,
                                const DString &amountType, 
                                const DString &settleInDate,
                                const DString &brokerTo,
                                const DString &accountNum,
                                const DString &accountNumTo,
                                const DString &fromCurrency,
                                const DString &toCurrency,
                                const DString &dstrTrack,
                                const DString &dstrPageName,
                                const DString &valuationDt,
                                const DString &dstrNetworkID,
								const DString &dstrTradeInDate,
								const DString &dstrValuationInDate)

{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                            CLASSNAME,
                            I_("init()"));

    BFData requestData (ifds::DSTC0135_REQ);

    DString mgmtCoIdOut;
    DString strOrderType;

    strOrderType = orderType;
    strOrderType.strip().upperCase();

    if ( strOrderType != YES && strOrderType != NO )
    {
        if ( strOrderType == I_("WI") || strOrderType == I_("WIRE") )
        {
            strOrderType = YES;
        }
        else if ( strOrderType == I_("DI") || strOrderType == I_("DIRECT") )
        {
            strOrderType = NO;
        }
        else
        {
            strOrderType = YES;
        }
    }

    requestData.setElementValue (ifds::CompanyId,       getMgmtCoId (mgmtCoIdOut));
    requestData.setElementValue (ifds::ValidationType,  validationType);
    requestData.setElementValue (ifds::TradeDate,       tradeDate, false, false);
    requestData.setElementValue (ifds::SettleDate,      settleDate, false, false);
    requestData.setElementValue (ifds::SettleInDate,    settleInDate, false, false);
    requestData.setElementValue (ifds::EffectiveDate,   depositDate, false, false);
    requestData.setElementValue (ifds::ValueDate,       valueDate, false, false);
    requestData.setElementValue (ifds::TransType,       transType, false, false);
    requestData.setElementValue (ifds::PayType,         payType, false, false) ;
    requestData.setElementValue (ifds::BrokerCode,      broker);
    requestData.setElementValue (ifds::BrokerToCode,    brokerTo);
    requestData.setElementValue (ifds::FundCode,        fundCode);
    requestData.setElementValue (ifds::ClassCode,       classCode);
    requestData.setElementValue (ifds::FundToCode,      toFund);
    requestData.setElementValue (ifds::ClassToCode,     toClass);
    requestData.setElementValue (ifds::OrderType,       strOrderType);
    requestData.setElementValue (ifds::DealDate,        dealDate, false, false);
    requestData.setElementValue (ifds::DealTime,        dealTime, false, false);
    requestData.setElementValue (ifds::SettleCurrency,  settleCurrency);
    requestData.setElementValue (ifds::Amount,          amount);
    requestData.setElementValue (ifds::AmountType,      amountType, false, false);
    requestData.setElementValue (ifds::AccountNum,      accountNum );
    requestData.setElementValue (ifds::AccountTo,       accountNumTo );
    requestData.setElementValue (ifds::FrSettlCurrency, fromCurrency );
    requestData.setElementValue (ifds::ToSettlCurrency, toCurrency );
    requestData.setElementValue (ifds::Track,           dstrTrack);
    requestData.setElementValue (ifds::Activity,        dstrPageName);
    requestData.setElementValue (ifds::ValuationDt,     valuationDt);
    requestData.setElementValue (ifds::NetworkID,       dstrNetworkID);
	requestData.setElementValue (ifds::TradeInDate,     dstrTradeInDate);
	requestData.setElementValue (ifds::ValuationInDt,   dstrValuationInDate);

    ReceiveData ( DSTC_REQUEST::DATE_VALIDATION, 
                    requestData, 
                    ifds::DSTC0135_VW, 
                    DSTCRequestor (getSecurity()));
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void DateValidation::getField ( const BFFieldId &idField, 
                                DString &strValue, 
                                const BFDataGroupId &idDataGroup, 
                                bool formattedReturn) const 
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                            CLASSNAME,
                            I_("getField"));

    DString tempValue;

    tempValue = NO;

    if (idField == ifds::TradeDate)
    {
        BFCBO::getField  (ifds::TradeDateFailed, tempValue, idDataGroup);
    }
    if (idField == ifds::SettleDate)
    {
        BFCBO::getField  (ifds::SettleDateFailed, tempValue, idDataGroup);
    }
    if (idField == ifds::EffectiveDate)
    {
        BFCBO::getField  (ifds::EffectiveDateFailed, tempValue, idDataGroup);
    }
    if (idField == ifds::ValueDate)
    {
        tempValue = YES;
    }
	if (idField == ifds::ValuationDt)
    {
        tempValue = YES;
    }
    if (idField == ifds::SuggestSettleInDate)
    {
        tempValue = YES;
    }
	if (idField == ifds::TradeInDate)
	{
		BFCBO::getField  (ifds::TradeInDateFailed, tempValue, idDataGroup);
	}
	if (idField == ifds::ValuationInDt)
    {
        tempValue = YES;
    }
    // YES means Date in the request and Date return in response are different
    // therefore only get the date value if it is equal to "Y"
    if (tempValue == YES)
    {
        BFCBO::getField (idField, strValue, idDataGroup,  formattedReturn);
    }
}

//******************************************************************************
SEVERITY DateValidation::addConditions ( const DString &validationType,
                                         const BFDataGroupId &idDataGroup,
										 const BFFieldId &idField,
                                         CONDITIONVECTOR *&pConditionVector)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_("addConditions"));
   DString warnMsgCode;

   BFCBO::getField (ifds::WarnMsgCode, warnMsgCode, idDataGroup);
   double dec_warn_msg_code = DSTCommonFunctions::convertToDouble (warnMsgCode);
   if (validationType == I_("1") || validationType == I_("4"))
   {
      if (dec_warn_msg_code == 557) //trade date past cut-off date
      {
         ADDCONDITIONFROMFILE (CND::WARN_TRADE_DATE_PAST_CUTOFF_DATE);
      }
      else if (dec_warn_msg_code == 579) //trading time passed aggregate cut-off time
      {
         ADDCONDITIONFROMFILE (CND::WARN_TRADING_TIME_PASSED_AGGREGATED_ORDER_CUTOFF_TIME);
      }
      else if (dec_warn_msg_code == 580) //passed client cut-off and aggregate cut off time
      {
         ADDCONDITIONFROMFILE (CND::WARN_TRADING_TIME_PASSED_CLIENT_AND_AGGREGATED_ORDER_CUTTOF_TIME);
      }
      else if (dec_warn_msg_code == 710) //custome schedule missing
      {
         ADDCONDITIONFROMFILE (CND::WARN_CUSTOM_TRADING_SCHEDULE_IS_MISSING);
      }
	  else if (dec_warn_msg_code == 761) //Trade passed Fund Cut Off Time //in1337808
      {
         ADDCONDITIONFROMFILE (CND::WARN_TRADE_PASSED_FUND_CUTOFF_TIME);
      }
   }
   DString rejErrNum, idiStr, _shortSettleDate,_shortSettleInDate;
   BFCBO::getField (ifds::RejErrNum, rejErrNum, idDataGroup);
   BFCBO::getField (ifds::RestrictedSettleDate, _shortSettleDate, idDataGroup, true);
   BFCBO::getField (ifds::RestrictedSettleInDate, _shortSettleInDate, idDataGroup, true);

   if ((validationType == I_("2") || validationType == I_("9"))
	   && rejErrNum == IFASTERR::SETTLEDATE_LESS_THEN_FUND_LEVEL_SETTLEDATE)
   {
	   if ( !_shortSettleDate.empty () && idField == ifds::SettleDate)
	   {
			idiStr = NULL_STRING;
		    addIDITagValue(idiStr, SETTLEMENT_TYPE , DString(I_ ("Settle Date")));
			addIDITagValue(idiStr, FUND_SETTLEMENT_TYPE , DString(I_ ("Settle Date")));
			addIDITagValue(idiStr, Short_SETTLEDATE, _shortSettleDate);
			getErrMsg(IFASTERR::SETTLEDATE_LESS_THEN_FUND_LEVEL_SETTLEDATE,
		   		   CND::ERR_SETTLEDATE_LESS_THAN_FUND_LEVEL_SETTLEDATE,
				   CND::WARN_SETTLEDATE_LESS_THAN_FUND_LEVEL_SETTLEDATE,
		           idDataGroup, idiStr);
			PROMOTECONDITIONS();
	   }
	   else if(!_shortSettleInDate.empty () && idField == ifds::SettleInDate)
	   {
			idiStr = NULL_STRING;
		    addIDITagValue(idiStr, SETTLEMENT_TYPE , DString(I_ ("SettleIn Date")));
			addIDITagValue(idiStr, FUND_SETTLEMENT_TYPE , DString(I_ ("SettleIn Date")));
			addIDITagValue(idiStr, Short_SETTLEDATE, _shortSettleInDate);
			getErrMsg(IFASTERR::SETTLEDATE_LESS_THEN_FUND_LEVEL_SETTLEDATE,
		   		   CND::ERR_SETTLEDATE_LESS_THAN_FUND_LEVEL_SETTLEDATE,
				   CND::WARN_SETTLEDATE_LESS_THAN_FUND_LEVEL_SETTLEDATE,
		           idDataGroup, idiStr);
			PROMOTECONDITIONS();
	   }
   }
   int count = MYFRAME()->getCount();

   for (int i = 0; i < count; i++)
   {
      Condition *c = new Condition (*MYFRAME()->getCondition (i));
      if (!pConditionVector) //create one if it doesn't exist
      {
         pConditionVector = new CONDITIONVECTOR;
      }
      pConditionVector->push_back (c);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DateValidation.cpp-arc  $
// 
//    Rev 1.39   Jan 20 2012 15:38:34   wp040027
// P0188394_Performance Fees - Order Entry
// 
//    Rev 1.38   Nov 04 2008 06:15:46   phiwponp
// IN 1337808 - Add error 761 in trade entry screen.
// 
//    Rev 1.37   Jun 06 2008 07:08:12   daechach
// in#1283327 - Trade created with invalid settlement date.
// 
//    Rev 1.36   Mar 11 2008 20:01:36   daechach
// PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
// 
//    Rev 1.35   Feb 22 2008 17:41:00   daechach
// in# 1152766 - Handler Locked-function
// 
//    Rev 1.34   Sep 05 2007 14:40:38   jankovii
// IN #953708 - Unable to change Settle Out and Settle In dates at the same time.
// 
//    Rev 1.33   Mar 30 2007 14:03:32   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.31   Mar 27 2007 18:40:52   jankovii
// PET 2292 FN01 - Swithc Settlement.
// 
//    Rev 1.30   Mar 21 2007 13:23:20   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.29   May 10 2006 14:36:02   popescu
// Incident# 617623 - display default warnings and erros on the trade date
// 
//    Rev 1.28   Jul 06 2005 11:48:36   hernando
// PET1250 FN01 - Added AccountNum.
// 
//    Rev 1.27   Jan 27 2005 20:25:04   popescu
// PET 1117/66/67/68.
// 
//    Rev 1.26   Jan 06 2005 17:20:52   popescu
// PTS 10037460 , Date validation object should add the conditions on the condition vector
// 
//    Rev 1.25   Dec 14 2004 17:39:06   popescu
// PET 1117/06/56 added validation for trade cut-off date
// 
//    Rev 1.24   Nov 14 2004 14:30:16   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.23   Nov 04 2004 17:37:20   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.22   Mar 21 2003 18:02:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.21   Oct 09 2002 23:54:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.20   Sep 27 2002 15:10:30   KOVACSRO
// PTS 10010020 : added isChanged
// 
//    Rev 1.19   Aug 29 2002 12:55:14   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.18   Jun 12 2002 17:42:54   KOVACSRO
// bug fix for ValueDate
// 
//    Rev 1.17   Jun 07 2002 17:44:06   KOVACSRO
// Added ValueDate
// 
//    Rev 1.16   22 May 2002 18:26:42   PURDYECH
// BFData Implementation
// 
//    Rev 1.15   04 Mar 2002 17:40:52   WINNIE
// restore previous version, the original logic is correct
// 
//    Rev 1.14   04 Mar 2002 16:46:26   WINNIE
// get field value only if fail = NO
// 
//    Rev 1.13   09 May 2001 16:13:42   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.12   03 May 2001 14:06:06   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.11   27 Feb 2001 14:41:34   SMITHDAV
// Put the DealTime back again(undo CH's last change)
// 
//    Rev 1.10   Feb 13 2001 16:20:38   HSUCHIN
// code cleanup and changed to use async receive data
// 
//    Rev 1.9   06 Feb 2001 15:46:48   SMITHDAV
// Put the DealTime back (undo CP's last change)
// 
//    Rev 1.8   30 Jan 2001 15:18:16   PURDYECH
// Changed the signature of the init method with loads of const DString arguments so that it takes references
// Changed the init method to set DealDateTime instead of DealTime as this seems to be the correct element from VIEW0135.
// 
//    Rev 1.7   Jan 29 2001 10:54:26   VASILEAD
// Took the unformatted value from the requested fields
// 
//    Rev 1.6   Jan 18 2001 16:04:32   YINGBAOL
// add eTracker
// 
//    Rev 1.5   Jan 12 2001 13:10:08   WINNIE
// new parameters for request related to transfer/exchange
// 
//    Rev 1.4   Dec 17 2000 20:22:52   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.3   Dec 14 2000 16:20:02   JANKAREN
// new redemption logic for FeeCurrency and EffectiveDate
// 
//    Rev 1.2   Nov 07 2000 15:22:30   OLTEANCR
// new data broker
// 
//    Rev 1.1   Sep 01 2000 15:25:40   HUANGSHA
// added pClientLocale in setField(...)
// 
//    Rev 1.0   May 11 2000 10:24:20   WINNIE
// Initial revision.
*/
