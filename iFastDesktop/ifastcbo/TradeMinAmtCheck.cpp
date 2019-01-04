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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeMinAmtCheck.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : July, 2001
//
// ^CLASS    : TradeMinAmtCheck
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "trademinamtcheck.hpp"
#include "mfaccount.hpp"
#include <ifastdataimpl\dse_dstc0167_req.hpp>
#include <ifastdataimpl\dse_dstc0167_vw.hpp>
#include "mgmtco.hpp"

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;

   const char *const CFX_TRANS = "CFXTRAN";
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADE_MIN_AMT_CHECK;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFDateFieldId FundStatusDate;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId PensionJuris;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeSchedule;
   extern CLASS_IMPORT const BFTextFieldId FullExchPrntToPrnt;
}


namespace CND
{  
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;

   extern  const long ERR_WARN_MIN_FUND_BALANCE;//276
   extern  const long ERR_WARN_MIN_ACCOUNT_BALANCE;//278
   extern  const long ERR_WARN_MIN_INIT_REDEMPTION;//272
   extern  const long ERR_WARN_MIN_INIT_PURCHASE;//282
   extern  const long ERR_WARN_MIN_SUBS_REDEMPTION;//274
   extern  const long ERR_WARN_MIN_SUBS_PURCHASE;//280
   extern  const long ERR_WARN_MAYBE_MIN_ACCOUNT_BALANCE;//279
   extern  const long ERR_WARN_MAYBE_MIN_FUND_BALANCE;//277
   extern  const long ERR_WARN_MAYBE_MIN_INIT_PURCHASE;//
   extern  const long ERR_WARN_MAYBE_MIN_INIT_REDEMPTION;//273
   extern  const long ERR_WARN_MAYBE_MIN_SUBS_PURCHASE;//281
   extern  const long ERR_WARN_MAYBE_MIN_SUBS_REDEMPTION;//275
   extern  const long WARN_AMOUNT_IS_OVER_THRESHOLD;
   extern  const long ERR_AMOUNT_IS_OVER_THRESHOLD;//532

   extern  const long ERR_MIN_INIT_PURCHASE;
   extern  const long ERR_MIN_INIT_REDEMPTION;
   extern  const long ERR_MIN_SUBS_PURCHASE;
   extern  const long ERR_MIN_SUBS_REDEMPTION;

   extern const long ERR_ACCT_MIN_INIT_PURCHASE;
   extern const long ERR_BROKER_MIN_INIT_PURCHASE;
   extern const long ERR_BRANCH_MIN_INIT_PURCHASE;
   extern const long ERR_SLSREP_MIN_INIT_PURCHASE;

   extern const long ERR_ACCT_MIN_ALLOWABLE_PURCHASE;
   extern const long ERR_BROKER_MIN_ALLOWABLE_PURCHASE;
   extern const long ERR_BRANCH_MIN_ALLOWABLE_PURCHASE;
   extern const long ERR_SLSREP_MIN_ALLOWABLE_PURCHASE;

   extern const long ERR_ACCT_PURCHASE_NOT_ALLOWED;
   extern const long ERR_BROKER_PURCHASE_NOT_ALLOWED;
   extern const long ERR_BRANCH_PURCHASE_NOT_ALLOWED;
   extern const long ERR_SLSREP_PURCHASE_NOT_ALLOWED;
   extern const long ERR_PURCHASE_NOT_ALLOWED_FOR_FUND;

   extern const long ERR_ACCT_REDEMPTION_NOT_ALLOWED;
   extern const long ERR_BROKER_REDEMPTION_NOT_ALLOWED;
   extern const long ERR_BRANCH_REDEMPTION_NOT_ALLOWED;
   extern const long ERR_SLSREP_REDEMPTION_NOT_ALLOWED;

   extern const long ERR_ACCT_TO_TRANSFER_NOT_ALLOWED;
   extern const long ERR_BROKER_TO_TRANSFER_NOT_ALLOWED;
   extern const long ERR_BRANCH_TO_TRANSFER_NOT_ALLOWED;
   extern const long ERR_SLSREP_TO_TRANSFER_NOT_ALLOWED;
   extern const long ERR_TRANSFERIN_NOT_ALLOWED_FOR_FUND;

   extern const long ERR_ACCT_FROM_TRANSFER_NOT_ALLOWED;
   extern const long ERR_BROKER_FROM_TRANSFER_NOT_ALLOWED;
   extern const long ERR_BRANCH_FROM_TRANSFER_NOT_ALLOWED;
   extern const long ERR_SLSREP_FROM_TRANSFER_NOT_ALLOWED;
   extern const long ERR_TRANSFER_OUT_NOT_ALLOWED_FOR_FUND; 

   extern const long ERR_ACCT_MIN_BALANCE;
   extern const long ERR_BROKER_MIN_BALANCE;
   extern const long ERR_BRANCH_MIN_BALANCE;
   extern const long ERR_SALESREP_MIN_BALANCE;

   extern const long ERR_MGMT_FEE_MODEL_MISSING;
   extern const long WARN_MGMT_FEE_MODEL_MISSING;

   extern const long WARN_ACCT_MIN_INIT_PURCHASE;
   extern const long WARN_BROKER_MIN_INIT_PURCHASE;
   extern const long WARN_BRANCH_MIN_INIT_PURCHASE;
   extern const long WARN_SLSREP_MIN_INIT_PURCHASE;

   extern const long WARN_ACCT_MIN_ALLOWABLE_PURCHASE;
   extern const long WARN_BROKER_MIN_ALLOWABLE_PURCHASE;
   extern const long WARN_BRANCH_MIN_ALLOWABLE_PURCHASE;
   extern const long WARN_SLSREP_MIN_ALLOWABLE_PURCHASE;

   extern const long WARN_ACCT_PURCHASE_NOT_ALLOWED;
   extern const long WARN_BROKER_PURCHASE_NOT_ALLOWED;
   extern const long WARN_BRANCH_PURCHASE_NOT_ALLOWED;
   extern const long WARN_SLSREP_PURCHASE_NOT_ALLOWED;
   extern const long WARN_PURCHASE_NOT_ALLOWED_FOR_FUND;

   extern const long WARN_ACCT_REDEMPTION_NOT_ALLOWED;
   extern const long WARN_BROKER_REDEMPTION_NOT_ALLOWED;
   extern const long WARN_BRANCH_REDEMPTION_NOT_ALLOWED;
   extern const long WARN_SLSREP_REDEMPTION_NOT_ALLOWED;

   extern const long WARN_ACCT_TO_TRANSFER_NOT_ALLOWED;
   extern const long WARN_BROKER_TO_TRANSFER_NOT_ALLOWED;
   extern const long WARN_BRANCH_TO_TRANSFER_NOT_ALLOWED;
   extern const long WARN_SLSREP_TO_TRANSFER_NOT_ALLOWED;
   extern const long WARN_TRANSFERIN_NOT_ALLOWED_FOR_FUND;

   extern const long WARN_ACCT_FROM_TRANSFER_NOT_ALLOWED;
   extern const long WARN_BROKER_FROM_TRANSFER_NOT_ALLOWED;
   extern const long WARN_BRANCH_FROM_TRANSFER_NOT_ALLOWED;
   extern const long WARN_SLSREP_FROM_TRANSFER_NOT_ALLOWED;
   extern const long WARN_TRANSFER_OUT_NOT_ALLOWED_FOR_FUND; 

   extern const long WARN_ACCT_MIN_BALANCE;
   extern const long WARN_BROKER_MIN_BALANCE;
   extern const long WARN_BRANCH_MIN_BALANCE;
   extern const long WARN_SALESREP_MIN_BALANCE;

   extern const long ERR_STOP_MONEY_IN_FOR_TAX_TYPE;//781
   extern const long ERR_CONTROLX_RECORD_NOT_AVAILABLE;//782

   extern const long WARN_NON_RECEIPT_FLAG_ACTIVE;
   extern const long ERR_NON_RECEIPT_FLAG_ACTIVE;
   extern const long WARN_CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED;
   extern const long ERR_CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED;

   extern const long WARN_KIID_ATTESTATION;
   extern const long ERR_KIID_ATTESTATION;
   extern const long ERR_PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS;
   extern const long WARN_PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS;
   extern const long ERR_PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS;
   extern const long WARN_PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS;
   extern const long ERR_RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL;
   extern const long WARN_RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL;
   extern const long ERR_UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES;
   extern const long WARN_UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES;
   extern const long ERR_PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS;
   extern const long WARN_PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS;
   extern const long WARN_REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE;
   extern const long ERR_REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE;
   extern const long ERR_ACCT_LESS_THAN_MIN_INIT_RED;
   extern const long WARN_ACCT_LESS_THAN_MIN_INIT_RED;
   extern const long ERR_BROKER_LESS_THAN_MIN_INIT_RED;
   extern const long WARN_BROKER_LESS_THAN_MIN_INIT_RED;
   extern const long ERR_BRANCH_LESS_THAN_MIN_INIT_RED;
   extern const long WARN_BRANCH_LESS_THAN_MIN_INIT_RED;
   extern const long ERR_SLSREP_LESS_THAN_MIN_INIT_RED;
   extern const long WARN_SLSREP_LESS_THAN_MIN_INIT_RED;
   extern const long ERR_ACCT_LESS_THAN_MIN_SUBSEQ_RED;
   extern const long WARN_ACCT_LESS_THAN_MIN_SUBSEQ_RED;
   extern const long ERR_BROKER_LESS_THAN_MIN_SUBSEQ_RED;
   extern const long WARN_BROKER_LESS_THAN_MIN_SUBSEQ_RED;
   extern const long ERR_BRANCH_LESS_THAN_MIN_SUBSEQ_RED;
   extern const long WARN_BRANCH_LESS_THAN_MIN_SUBSEQ_RED;
   extern const long ERR_SLSREP_LESS_THAN_MIN_SUBSEQ_RED;
   extern const long WARN_SLSREP_LESS_THAN_MIN_SUBSEQ_RED;
   extern const long ERR_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long WARN_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long ERR_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long WARN_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long ERR_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long WARN_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long ERR_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long WARN_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long ERR_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long WARN_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS;
   extern const long ERR_LESS_THAN_MINIMUM_INITIAL_BUYBACK_AMOUNT;
   extern const long WARN_LESS_THAN_MINIMUM_INITIAL_BUYBACK_AMOUNT;         
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const KIID_ATTESTATION;                                       
};

namespace
{
   const I_CHAR * const CLASSNAME                     = I_ ("TradeMinAmtCheck");
   const I_CHAR * const YES                           = I_ ("Y");  
   const I_CHAR * const MINIMUM_AMT                   = I_ ("MINIMUM_AMT");
   const I_CHAR * const MINIMUM_BAL                   = I_ ("MINIMUM_BAL");
   const I_CHAR * const THRESHOLD                     = I_ ("threshold");
   const I_CHAR * const FUND                          = I_ ("FUND");
   const I_CHAR * const CLASS                         = I_ ("CLASS");
   const I_CHAR * const ASOF                          = I_ ("ASOF");
   const I_CHAR * const SPACE                         = I_ (" ");
   const I_CHAR * const EWI_ERROR                     = I_ ("E");
   const I_CHAR * const EWI_WARNING                   = I_ ("W");
      
   const I_CHAR * const PUR_BUYBACK                   = I_ ("PUR_BUYBACK");
   const I_CHAR * const AMNT_UNITS                    = I_ ("AMNT_UNITS");

   const long MINIMUM_INIT_REDEMPTION       = 272;
   const long MAYBE_MINIMUM_INIT_REDEMPTION = 273;
   const long MINIMUM_SUBS_REDEMPTION       = 274;
   const long MAYBE_MINIMUM_SUBS_REDEMPTION = 275;
   const long MINIMUM_FUND_BALANCE          = 276;
   const long MAYBE_MINIMUM_FUND_BALANCE    = 277;
   const long MINIMUM_ACCOUNT_BALANCE       = 278;
   const long MAYBE_MINIMUM_ACCOUNT_BALANCE = 279;
   const long MINIMUM_SUBS_PURCHASE         = 280;  //original code 280;
   const long MAYBE_MINIMUM_SUBS_PURCHASE   = 281;
   const long MINIMUM_INIT_PURCHASE         = 282;  //original code 282;
   const long AMOUNT_OVER_THE_THRESHOLD     = 532;

   const long ACCT_MIN_INIT_PURCHASE        = 727;
   const long BROKER_MIN_INIT_PURCHASE      = 728;
   const long BRANCH_MIN_INIT_PURCHASE      = 729;
   const long SLSREP_MIN_INIT_PURCHASE      = 730;

   const long ACCT_MIN_ALLOWABLE_PURCHASE   = 731;
   const long BROKER_MIN_ALLOWABLE_PURCHASE = 732;
   const long BRANCH_MIN_ALLOWABLE_PURCHASE = 733;
   const long SLSREP_MIN_ALLOWABLE_PURCHASE = 734;

   const long ACCT_PURCHASE_NOT_ALLOWED     = 735;
   const long BROKER_PURCHASE_NOT_ALLOWED   = 736;
   const long BRANCH_PURCHASE_NOT_ALLOWED   = 737;
   const long SLSREP_PURCHASE_NOT_ALLOWED   = 738;
   const long PURCHASE_NOT_ALLOWED          = 739;

   const long ACCT_REDEMPTION_NOT_ALLOWED   = 740;
   const long BROKER_REDEMPTION_NOT_ALLOWED = 741;
   const long BRANCH_REDEMPTION_NOT_ALLOWED = 742;
   const long SLSREP_REDEMPTION_NOT_ALLOWED = 743;

   const long ACCT_TO_TRANSFER_NOT_ALLOWED    = 744;
   const long BROKER_TO_TRANSFER_NOT_ALLOWED  = 745;
   const long BRANCH_TO_TRANSFER_NOT_ALLOWED  = 746;
   const long SLSREP_TO_TRANSFER_NOT_ALLOWED  = 747;
   const long TO_TRANSFER_NOT_ALLOWED         = 748;

   const long ACCT_FROM_TRANSFER_NOT_ALLOWED    = 749;
   const long BROKER_FROM_TRANSFER_NOT_ALLOWED  = 750;
   const long BRANCH_FROM_TRANSFER_NOT_ALLOWED  = 751;
   const long SLSREP_FROM_TRANSFER_NOT_ALLOWED  = 752;
   const long FROM_TRANSFER_NOT_ALLOWED         = 753;

   const long ACCT_MIN_BALANCE		        = 754;
   const long BROKER_MIN_BALANCE	        = 755;
   const long BRANCH_MIN_BALANCE	        = 756;
   const long SLSREP_MIN_BALANCE	        = 757;
   const long FUND_CAPPED_AT_ACCOUNT	    = 766;
   const long FUND_CAPPED_AT_FND_CLS	    = 767;
   const long MGMT_FEE_MODEL_MISSING        = 769;
   const long STOP_MONEY_IN_FOR_TAX_TYPE    = 781;
   const long CONTROLX_RECORD_NOT_AVAILABLE = 782;

   const long NON_RECEIPT_FLAG_ACTIVE    = 849;
   const long CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED = 850;
   const long SOFT_CAPPED_FUND_LEVEL                 = 968;
    const long SOFT_CAPPED_FUND_GROUP_LEVEL          = 969;

   const long KIID_VALIDATION    = 1238;
   const long PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS = 1741;
   const long PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS = 1742;
   const long RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL = 1743;
   const long UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES = 1744;
   const long PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS = 1745;
   const long REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE = 1805;
   const long ACCT_LESS_THAN_MIN_INIT_RED = 977;
   const long BROKER_LESS_THAN_MIN_INIT_RED = 978;
   const long BRANCH_LESS_THAN_MIN_INIT_RED = 979;
   const long SLSREP_LESS_THAN_MIN_INIT_RED = 980;
   const long ACCT_LESS_THAN_MIN_SUBSEQ_RED = 981;
   const long BROKER_LESS_THAN_MIN_SUBSEQ_RED = 982;
   const long BRANCH_LESS_THAN_MIN_SUBSEQ_RED = 983;
   const long SLSREP_LESS_THAN_MIN_SUBSEQ_RED = 984;
   const long ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS = 1899;
   const long BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS = 1900;
   const long BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS = 1901;
   const long SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS = 1902;
   const long LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS = 1903;

   const long ACCOUNT_LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT = 1942;
   const long BROKER_LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT = 1943;
   const long BRANCH_LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT = 1944;
   const long SALES_LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT = 1945;
   const long LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT = 1946;

   const long ACCOUNT_LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS = 1947;
   const long BROKER_LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS = 1948;
   const long BRANCH_LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS = 1949;
   const long SALES_LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS = 1950;
   const long LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS = 1951;   

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags 
   {ifds::InitPurch,     BFCBO::NONE,             0},
};

static const int NUM_FIELDS = sizeof  (classFieldInfo) / sizeof  (BFCBO::CLASS_FIELD_INFO);



//******************************************************************************
TradeMinAmtCheck::TradeMinAmtCheck (BFAbstractCBO &parent)
: MFCanBFCbo (parent),
_fundCode  (NULL_STRING),
_classCode  (NULL_STRING),
_accountNum(NULL_STRING),
_tradeDate(NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

   setObjectAsList ();
}

//******************************************************************************
TradeMinAmtCheck::~TradeMinAmtCheck ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY TradeMinAmtCheck::init (const DString &strAccountNum, 
                                 const DString &_fundCodeCode, 
                                 const DString &strClassCode, 
                                 const DString &strTransType, 
                                 const DString &strAmountType, 
                                 const DString &strAmount, 
                                 const DString &strEffectiveDate, 
                                 const DString &strSettleCurrency, 
                                 const DString &strExchRate,
                                 const DString &dstrBrokerCode, 
                                 const DString &dstrBranchCode,
                                 const DString &dstrSalesRepCode,
                                 const DString &dstrAMSCode, 
                                 const DString &dstrAMSType,
                                 const DString &dstrDepositType, //in1419539
                                 const DString &dstrOrderType,
                                 bool ignoreDataNotFound, /*=true*/
                                 bool bFullExchPrntToPrnt,
                                 const DString &Indc,
                                 const DString &adjForTransNum)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
   BFData queryData  (ifds::DSTC0167_REQ);

   _fundCode = _fundCodeCode;
   _classCode = strClassCode;
   _accountNum = strAccountNum;
   _accountNum.strip().stripLeading( '0' );
   _tradeDate = strEffectiveDate;

   _fundCode.upperCase();
   _classCode.upperCase();

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::AccountNum, strAccountNum);
   queryData.setElementValue (ifds::FundCode, _fundCodeCode);
   queryData.setElementValue (ifds::ClassCode, strClassCode);
   queryData.setElementValue (ifds::TransType, strTransType);
   queryData.setElementValue (ifds::Amount, strAmount);
   queryData.setElementValue (ifds::AmountType, strAmountType);
   queryData.setElementValue (ifds::EffectiveDate, strEffectiveDate, false, false);
   queryData.setElementValue (ifds::SettleCurrency, strSettleCurrency);
   queryData.setElementValue (ifds::ExchRate, strExchRate);
   queryData.setElementValue (ifds::AMSCode, dstrAMSCode);
   queryData.setElementValue (ifds::AMSType, dstrAMSType);
   queryData.setElementValue (ifds::BrokerCode, dstrBrokerCode);
   queryData.setElementValue (ifds::BranchCode, dstrBranchCode);
   queryData.setElementValue (ifds::SalesRepCode, dstrSalesRepCode);
   queryData.setElementValue (ifds::DepositType, dstrDepositType); //in1419539
   queryData.setElementValue (ifds::OrderType, dstrOrderType);
   queryData.setElementValue (ifds::FullExchPrntToPrnt, bFullExchPrntToPrnt ? Y:N);
   queryData.setElementValue (ifds::Indc, Indc);
   queryData.setElementValue (ifds::AdjTransNum, adjForTransNum);
   queryData.setElementValue(ifds::DilutionLinkNum, NULL_STRING);
   queryData.setElementValue(ifds::RDSPValidation, N);
   queryData.setElementValue(ifds::GRRepayReason, NULL_STRING);
   queryData.setElementValue(ifds::RDSPPaymtDate, NULL_STRING);

   ReceiveData  (DSTC_REQUEST::TRADE_MIN_AMT_CHECK, 
                 queryData, 
                 ifds::DSTC0167_VW,
                 DSTCRequestor  (getSecurity (), true, ignoreDataNotFound));
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY TradeMinAmtCheck::addConditions ()
{
   MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("addConditions"));

   FundDetailList	*pFundDetailList;
   FundDetail *pFundDetail;

   if  (getMgmtCo ().getFundDetailList  (pFundDetailList) <= WARNING &&
        pFundDetailList)
   {
      if  (pFundDetailList->getFundDetail  (_fundCode, _classCode, BF::HOST, pFundDetail) &&
           pFundDetail)
      {
         DString idiStr, 
            fundCurrency, 
            errNum, 
            amount, 
            severityCode;

         pFundDetail->getField  (ifds::Currency, fundCurrency, BF::HOST);

         BFObjIter iter  (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
         iter.begin ();
         
         while  (!iter.end ())
         {
            idiStr = NULL_STRING;
            iter.getObject ()->getField  (ifds::ErrNum, errNum, BF::HOST, false);
            iter.getObject ()->getField  (ifds::Amount, amount, BF::HOST, true);
            iter.getObject ()->getField  (ifds::EWI, severityCode, BF::HOST, false);
            DSTCommonFunctions::DisplayFormat  (amount, ifds::Amount);
            severityCode.upperCase ();            
            addIDITagValue  (idiStr, FUND, _fundCode);
            addIDITagValue  (idiStr, CLASS, _classCode);
            
            long nErrNum = errNum.strip ().stripLeading ('0').convertToULong ();
            if(errNum.empty())
             	return (GETCURRENTHIGHESTSEVERITY ());
            switch  (nErrNum)
            {
               case MINIMUM_INIT_REDEMPTION:
                  {
                     addIDITagValue (idiStr, MINIMUM_AMT, amount + SPACE + fundCurrency);

                     if (severityCode == EWI_WARNING)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MIN_INIT_REDEMPTION, idiStr);
                     if (severityCode == EWI_ERROR)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_MIN_INIT_REDEMPTION, idiStr);
                  }
                  break;
               case MAYBE_MINIMUM_INIT_REDEMPTION:
                  {
                     addIDITagValue (idiStr, MINIMUM_AMT, amount + SPACE + fundCurrency);
                     ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MAYBE_MIN_INIT_REDEMPTION, idiStr);
                  }
                  break;
               case MINIMUM_SUBS_REDEMPTION:
                  {
                     addIDITagValue (idiStr, MINIMUM_AMT, amount + SPACE + fundCurrency);

                     if  (severityCode == EWI_WARNING)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MIN_SUBS_REDEMPTION, idiStr);
                     if  (severityCode == EWI_ERROR)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_MIN_SUBS_REDEMPTION, idiStr);      
                  }
                  break;
               case MAYBE_MINIMUM_SUBS_REDEMPTION:
                  {
                     addIDITagValue (idiStr, MINIMUM_AMT, amount + SPACE + fundCurrency);
                     ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MAYBE_MIN_SUBS_REDEMPTION, idiStr);
                  }
                  break;
               case MINIMUM_FUND_BALANCE:
                  {
                     addIDITagValue (idiStr, MINIMUM_BAL, amount);
                     ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MIN_FUND_BALANCE, idiStr);
                  }
                  break;
               case MAYBE_MINIMUM_FUND_BALANCE:
                  {
                     addIDITagValue (idiStr, MINIMUM_BAL, amount);
                     ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MAYBE_MIN_FUND_BALANCE, idiStr);
                  }
                  break;
               case MINIMUM_ACCOUNT_BALANCE:
                  {
                     idiStr = NULL_STRING;
                     addIDITagValue (idiStr, MINIMUM_BAL, amount);
                     ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MIN_ACCOUNT_BALANCE, idiStr);
                  }
                  break;
               case MAYBE_MINIMUM_ACCOUNT_BALANCE:
                  {
                     idiStr = NULL_STRING;
                     addIDITagValue (idiStr, MINIMUM_BAL, amount);
                     ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MAYBE_MIN_ACCOUNT_BALANCE, idiStr);
                  }
                  break;
               case MINIMUM_SUBS_PURCHASE:
                  {
                     addIDITagValue (idiStr, MINIMUM_AMT, amount + SPACE + fundCurrency);

                     if  (severityCode == EWI_WARNING)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MIN_SUBS_PURCHASE, idiStr);
                     if  (severityCode == EWI_ERROR)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_MIN_SUBS_PURCHASE, idiStr);
                  }
                  break;
               case MAYBE_MINIMUM_SUBS_PURCHASE:
                  {
                     addIDITagValue (idiStr, MINIMUM_AMT, amount + SPACE + fundCurrency);
                     ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MAYBE_MIN_SUBS_PURCHASE, idiStr);
                  }
                  break;
               case MINIMUM_INIT_PURCHASE:
                  {
                     addIDITagValue (idiStr, MINIMUM_AMT, amount + SPACE + fundCurrency);

                     if  (severityCode == EWI_WARNING)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_MIN_INIT_PURCHASE, idiStr);
                     if  (severityCode == EWI_ERROR)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_MIN_INIT_PURCHASE, idiStr);
                  }
                  break;
               case AMOUNT_OVER_THE_THRESHOLD:
                  {
                     addIDITagValue (idiStr, THRESHOLD, amount);
                     if  (severityCode == EWI_WARNING)
                        ADDCONDITIONFROMFILEIDI (CND::WARN_AMOUNT_IS_OVER_THRESHOLD, idiStr);
                     if  (severityCode == EWI_ERROR)
                        ADDCONDITIONFROMFILEIDI (CND::ERR_AMOUNT_IS_OVER_THRESHOLD, idiStr);
                  }
                  break;

   		      case ACCT_MIN_INIT_PURCHASE:
	   		      {
                     if  (severityCode == EWI_WARNING)
                        ADDCONDITIONFROMFILE (CND::WARN_ACCT_MIN_INIT_PURCHASE);
                     if  (severityCode == EWI_ERROR)
                        ADDCONDITIONFROMFILE (CND::ERR_ACCT_MIN_INIT_PURCHASE);
		   	      }
			         break;
		         case BROKER_MIN_INIT_PURCHASE:
			         {
			            if (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_BROKER_MIN_INIT_PURCHASE);
                        if (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_BROKER_MIN_INIT_PURCHASE);
			         }
			         break;
		         case BRANCH_MIN_INIT_PURCHASE:
			         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_BRANCH_MIN_INIT_PURCHASE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_BRANCH_MIN_INIT_PURCHASE);
			         }
			         break;
		         case SLSREP_MIN_INIT_PURCHASE:
			         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_SLSREP_MIN_INIT_PURCHASE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_SLSREP_MIN_INIT_PURCHASE);
			         }
			         break;
         			 			
		         case ACCT_MIN_ALLOWABLE_PURCHASE:
			         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_ACCT_MIN_ALLOWABLE_PURCHASE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_ACCT_MIN_ALLOWABLE_PURCHASE);
			         }
			         break;
		         case BROKER_MIN_ALLOWABLE_PURCHASE:
			         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_BROKER_MIN_ALLOWABLE_PURCHASE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_BROKER_MIN_ALLOWABLE_PURCHASE);
			         }
			         break;
		         case BRANCH_MIN_ALLOWABLE_PURCHASE:
		 	         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_BRANCH_MIN_ALLOWABLE_PURCHASE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_BRANCH_MIN_ALLOWABLE_PURCHASE);
			         }
			         break;
		         case SLSREP_MIN_ALLOWABLE_PURCHASE:
			         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_SLSREP_MIN_ALLOWABLE_PURCHASE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_SLSREP_MIN_ALLOWABLE_PURCHASE);
			         }
			         break;
		         case ACCT_PURCHASE_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_ACCT_PURCHASE_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_ACCT_PURCHASE_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case BROKER_PURCHASE_NOT_ALLOWED:
			         {
		               addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BROKER_PURCHASE_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BROKER_PURCHASE_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case BRANCH_PURCHASE_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BRANCH_PURCHASE_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BRANCH_PURCHASE_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case SLSREP_PURCHASE_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_SLSREP_PURCHASE_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_SLSREP_PURCHASE_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case  PURCHASE_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_PURCHASE_NOT_ALLOWED_FOR_FUND, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_PURCHASE_NOT_ALLOWED_FOR_FUND, idiStr);
			         }
			         break;
		         case ACCT_REDEMPTION_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_ACCT_REDEMPTION_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_ACCT_REDEMPTION_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case BROKER_REDEMPTION_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BROKER_REDEMPTION_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BROKER_REDEMPTION_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case BRANCH_REDEMPTION_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BRANCH_REDEMPTION_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BRANCH_REDEMPTION_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case SLSREP_REDEMPTION_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_SLSREP_REDEMPTION_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_SLSREP_REDEMPTION_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case ACCT_TO_TRANSFER_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_ACCT_TO_TRANSFER_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_ACCT_TO_TRANSFER_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case BROKER_TO_TRANSFER_NOT_ALLOWED:
			         {
 			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BROKER_TO_TRANSFER_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BROKER_TO_TRANSFER_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case BRANCH_TO_TRANSFER_NOT_ALLOWED:
			         {
 			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BRANCH_TO_TRANSFER_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BRANCH_TO_TRANSFER_NOT_ALLOWED, idiStr);

			         }
			         break;
		         case SLSREP_TO_TRANSFER_NOT_ALLOWED:
			         {
 			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_SLSREP_TO_TRANSFER_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_SLSREP_TO_TRANSFER_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case TO_TRANSFER_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_TRANSFERIN_NOT_ALLOWED_FOR_FUND, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_TRANSFERIN_NOT_ALLOWED_FOR_FUND, idiStr);				 
			         }
			         break;
		         case ACCT_FROM_TRANSFER_NOT_ALLOWED:
			         {
 			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_ACCT_FROM_TRANSFER_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_ACCT_FROM_TRANSFER_NOT_ALLOWED, idiStr);				 
			         }
			         break;
		         case BROKER_FROM_TRANSFER_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BROKER_FROM_TRANSFER_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BROKER_FROM_TRANSFER_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case BRANCH_FROM_TRANSFER_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BRANCH_FROM_TRANSFER_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BRANCH_FROM_TRANSFER_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case SLSREP_FROM_TRANSFER_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_SLSREP_FROM_TRANSFER_NOT_ALLOWED, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_SLSREP_FROM_TRANSFER_NOT_ALLOWED, idiStr);
			         }
			         break;
		         case FROM_TRANSFER_NOT_ALLOWED:
			         {
			            addIDITagValue (idiStr, FUND, _fundCode);
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILEIDI (CND::WARN_TRANSFER_OUT_NOT_ALLOWED_FOR_FUND, idiStr);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILEIDI (CND::ERR_TRANSFER_OUT_NOT_ALLOWED_FOR_FUND, idiStr);
			         }
			         break;
		         case ACCT_MIN_BALANCE:
			         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_ACCT_MIN_BALANCE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_ACCT_MIN_BALANCE);
			         }
			         break;
		         case BROKER_MIN_BALANCE:
			         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_BROKER_MIN_BALANCE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_BROKER_MIN_BALANCE);
			         }
			         break;
		         case BRANCH_MIN_BALANCE:
			         {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_BRANCH_MIN_BALANCE);
                        if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_BRANCH_MIN_BALANCE);
			         }
			         break;
		         case SLSREP_MIN_BALANCE:
   			      {
			            if  (severityCode == EWI_WARNING)
                           ADDCONDITIONFROMFILE (CND::WARN_SALESREP_MIN_BALANCE);
                     if  (severityCode == EWI_ERROR)
                           ADDCONDITIONFROMFILE (CND::ERR_SALESREP_MIN_BALANCE);
			         }
			         break;
			   case MGMT_FEE_MODEL_MISSING:
				   {
                       if(severityCode == EWI_WARNING) ADDCONDITIONFROMFILE(CND::WARN_MGMT_FEE_MODEL_MISSING);
                       if(severityCode == EWI_ERROR) ADDCONDITIONFROMFILE(CND::ERR_MGMT_FEE_MODEL_MISSING);
				   }
				   break;
            case STOP_MONEY_IN_FOR_TAX_TYPE:
            {
              DString strTaxTypeDesc, TaxTypeSchedDesc, strJurisdDesc, strGrandFatheredDate;
              MFAccount *pMFAccount= NULL;
              if( getWorkSession().getMFAccount( BF::HOST, _accountNum, pMFAccount ) <= WARNING && pMFAccount )
              {
						   pMFAccount->getGrandfatheredDate( strGrandFatheredDate, BF::HOST, NULL_STRING, NULL_STRING, NULL_STRING, true );
						   pMFAccount->getField( ifds::TaxType, strTaxTypeDesc, BF::HOST, true );
						   bool bApplic = false;
						   DString strMsg = strJurisdDesc+I_(" ")+strTaxTypeDesc;
						   pMFAccount->isTaxTypeScheduleApplicable( bApplic, NULL_STRING, NULL_STRING, NULL_STRING, BF::HOST );
						   if( bApplic )
                {
                              pMFAccount->getField( ifds::TaxTypeSchedule, TaxTypeSchedDesc, BF::HOST, true );
							  strMsg += I_(" ")+TaxTypeSchedDesc;
                }
						   pMFAccount->getField( ifds::PensionJuris, strJurisdDesc, BF::HOST, true );						   
                DString idiStr;
                addIDITagValue( idiStr, I_("VAR1"), strMsg );
						   addIDITagValue( idiStr, I_("GRANDFATHEREDDATE"), strGrandFatheredDate );
                ADDCONDITIONFROMFILEIDI( CND::ERR_STOP_MONEY_IN_FOR_TAX_TYPE, idiStr);               
              }             
            }
            break;
			   case CONTROLX_RECORD_NOT_AVAILABLE:
				   {
					   ADDCONDITIONFROMFILE (CND::ERR_CONTROLX_RECORD_NOT_AVAILABLE);
				   }
				   break;
				case NON_RECEIPT_FLAG_ACTIVE:
				   {
					   addIDITagValue  (idiStr, FUND, _fundCode);
                       addIDITagValue  (idiStr, CLASS, _classCode);

					   if  (severityCode == EWI_WARNING)
							ADDCONDITIONFROMFILEIDI (CND::WARN_NON_RECEIPT_FLAG_ACTIVE,idiStr);					  
					   if  (severityCode == EWI_ERROR)
							ADDCONDITIONFROMFILEIDI (CND::ERR_NON_RECEIPT_FLAG_ACTIVE,idiStr);
					   
				   }
				   break;

			   case CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED:
				   {					   
					   addIDITagValue  (idiStr, FUND, _fundCode);
                       addIDITagValue  (idiStr, CLASS, _classCode);

					   if  (severityCode == EWI_WARNING)
							ADDCONDITIONFROMFILEIDI (CND::WARN_CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED,idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED,idiStr);
				   }
				   break;
			  case KIID_VALIDATION :
				  {
					  getErrMsg ( IFASTERR::KIID_ATTESTATION, 
								  CND::ERR_KIID_ATTESTATION, 
								  CND::WARN_KIID_ATTESTATION, 
								  BF::HOST);
		   	      }
				  break;
              case PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS);
                  }
                  break;
              case PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS);
                  }
                  break;
              case RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL);
                  }
                  break;
              case UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES);
                  }
                  break;
              case PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS);
                  }
                  break;
               case REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE);
                  }
                  break;
               case ACCT_LESS_THAN_MIN_INIT_RED:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_ACCT_LESS_THAN_MIN_INIT_RED);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_ACCT_LESS_THAN_MIN_INIT_RED);
                  }
                  break;
               case BROKER_LESS_THAN_MIN_INIT_RED:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_BROKER_LESS_THAN_MIN_INIT_RED);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_BROKER_LESS_THAN_MIN_INIT_RED);
                  }
                  break;
               case BRANCH_LESS_THAN_MIN_INIT_RED:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_BRANCH_LESS_THAN_MIN_INIT_RED);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_BRANCH_LESS_THAN_MIN_INIT_RED);
                  }
                  break;
               case SLSREP_LESS_THAN_MIN_INIT_RED:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_SLSREP_LESS_THAN_MIN_INIT_RED);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_SLSREP_LESS_THAN_MIN_INIT_RED);
                  }
                  break;
               case ACCT_LESS_THAN_MIN_SUBSEQ_RED:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_ACCT_LESS_THAN_MIN_SUBSEQ_RED);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_ACCT_LESS_THAN_MIN_SUBSEQ_RED);
                  }
                  break;
               case BROKER_LESS_THAN_MIN_SUBSEQ_RED:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_BROKER_LESS_THAN_MIN_SUBSEQ_RED);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_BROKER_LESS_THAN_MIN_SUBSEQ_RED);
                  }
                  break;
               case BRANCH_LESS_THAN_MIN_SUBSEQ_RED:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_BRANCH_LESS_THAN_MIN_SUBSEQ_RED);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_BRANCH_LESS_THAN_MIN_SUBSEQ_RED);
                  }
                  break;
               case SLSREP_LESS_THAN_MIN_SUBSEQ_RED:
                  {
                      if  (severityCode == EWI_WARNING)
                          ADDCONDITIONFROMFILE (CND::WARN_SLSREP_LESS_THAN_MIN_SUBSEQ_RED);
                      if  (severityCode == EWI_ERROR)
                          ADDCONDITIONFROMFILE (CND::ERR_SLSREP_LESS_THAN_MIN_SUBSEQ_RED);
                  }
                  break;
			   case ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Purchase")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Purchase")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS,idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS,idiStr);
				   }
				   break;
			   case BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Purchase")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Purchase")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Purchase")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS,idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case ACCOUNT_LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Amount")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case BROKER_LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Amount")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS,idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS,idiStr);
				   }
				   break;
			   case BRANCH_LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Amount")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case SALES_LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Amount")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case LESS_THAN_MINIMUM_INITITAL_BUYBACK_AMOUNT:
				   {
					   addIDITagValue(idiStr, MINIMUM_AMT , amount + SPACE + fundCurrency);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_LESS_THAN_MINIMUM_INITIAL_BUYBACK_AMOUNT,idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_LESS_THAN_MINIMUM_INITIAL_BUYBACK_AMOUNT, idiStr);
				   }
				   break;
			   case ACCOUNT_LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case BROKER_LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS,idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS,idiStr);
				   }
				   break;
			   case BRANCH_LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case SALES_LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;
			   case LESS_THAN_MINIMUM_INITITAL_BUYBACK_UNITS:
				   {
					   addIDITagValue(idiStr, PUR_BUYBACK , DString(I_ ("Buyback")));
					   addIDITagValue(idiStr, AMNT_UNITS, DString(I_ ("Units")));
					   addIDITagValue(idiStr, MINIMUM_AMT , amount);

					   if  (severityCode == EWI_WARNING)
						   ADDCONDITIONFROMFILEIDI (CND::WARN_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS,idiStr);
					   if  (severityCode == EWI_ERROR)
						   ADDCONDITIONFROMFILEIDI (CND::ERR_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS, idiStr);
				   }
				   break;			   			  			  
		      default:
                  assert(0);
            }
            ++iter;
         }
      }
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}





//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeMinAmtCheck.cpp-arc  $*/
// 
//    Rev 1.26   May 18 2012 18:47:12   wp040132
// Removed KIID Flag
// 
//    Rev 1.25   May 16 2012 16:55:00   wp040132
// P0195754_FN01_ KIID_UCITs - KIID Validation - Replaced addconditionfromfile( ) with getErrMsg( )
// 
//    Rev 1.24   May 07 2012 19:52:04   wp040043
// P0195754_FN01_ KIID_UCITs - KIID Validation
// 
//    Rev 1.23   Dec 08 2011 21:50:14   wp040032
// P0183989 - Money Market Non Receipt
// 
//    Rev 1.22   01 Oct 2008 12:12:16   popescu
// Check in for incident 1419539
// 
//    Rev 1.21   03 Jun 2008 10:14:08   kovacsro
// IN#1300093 - incorrect date for the error message
// 
//    Rev 1.20   01 May 2008 13:58:14   kovacsro
// PET2255 FN47 - New Ontario LIF - finalized
// 
//    Rev 1.19   Aug 10 2007 14:10:24   jankovii
// PET 2360 FN14&FN19 - Management Fee.
// 
//    Rev 1.18   23 Jul 2007 16:50:20   popescu
// PET 2360 - FN 20 - GAP 20 Soft cap functionality
// 
//    Rev 1.17   Oct 30 2006 17:07:32   jankovii
// PET 2185 FN04 - Trade restrictions.
// 
//    Rev 1.16   Jul 11 2005 17:24:40   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.15   Dec 08 2004 12:49:38   popescu
// PET 1117/06, adde threshold amount validation for trade amount
// 
//    Rev 1.14   Nov 14 2004 14:58:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Aug 31 2004 10:40:16   WINNIE
// setfield failed due to class field info not yet defined
// 
//    Rev 1.12   Aug 15 2003 15:30:56   HSUCHIN
// added support for AMS Initial purchase check
// 
//    Rev 1.11   Mar 21 2003 18:27:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.10   Jan 30 2003 19:04:00   WINNIE
// Convert into upperCase before comparison
// 
//    Rev 1.9   Jan 28 2003 16:52:02   WINNIE
// Change the error number back to 282 and 280 to sync up with View code
// 
//    Rev 1.8   Jan 21 2003 18:35:40   WINNIE
// assign new error # based on view changes; add logic to allow minimum amount edit check severity code to control warning or error
// 
//    Rev 1.7   Oct 09 2002 23:55:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:56:56   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   Aug 21 2002 10:50:16   KOVACSRO
// PTS10009487 : don't display Fund and class for account balance.
// 
//    Rev 1.4   22 May 2002 18:30:08   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   07 Aug 2001 09:47:18   KOVACSRO
// Added a space between Amount and Currency.
// 
//    Rev 1.2   05 Aug 2001 14:57:06   KOVACSRO
// first bug fix.
// 
//    Rev 1.1   02 Aug 2001 14:10:12   KOVACSRO
// it is a list now.
// 
//    Rev 1.0   27 Jul 2001 15:54:54   KOVACSRO
// Initial revision.

