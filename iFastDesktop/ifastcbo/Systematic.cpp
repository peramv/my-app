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
//    Copyright 1999 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : Systematic.cpp
// ^AUTHOR : David Smith
// ^DATE   : Feburary 25, 1999
//
// ^CLASS  : Systematic
// ^PARENT : 
//
// ^CLASS DESCRIPTION :
//  ements a map from the STL to hold fully instantiated CBOBase objects
//  that are created from Data objects stored in the inherited ListBase class
//
//******************************************************************************

#include "stdafx.h"
#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "acqfeeinquiry.hpp"
#include "agentlist.hpp"
#include "autotransallocation.hpp"
#include "autotransallocationlist.hpp"
#include "autoaccttransallocation.hpp"
#include "autoaccttransallocationlist.hpp"
#include "bankinstructionslist.hpp"
#include "bankinstructions.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "contractinfolist.hpp"
#include "currency.hpp"
#include "currencyclass.hpp"
#include "currencylist.hpp"
#include "dstcommonfunction.hpp"
#include "dynamicsublistholder.hpp"
#include "swpamountcalculation.hpp"
#include "gmwbvalidation.hpp"
#include "entity.hpp"
#include "errmsgruleslist.hpp"
#include "feeinfoinquiry.hpp"
#include "fundmasterlist.hpp"
#include "fundmaster.hpp"
#include "funddetaillist.hpp"
#include "funddetail.hpp"
#include "fundtolist.hpp"
#include "fundtranstypelist.hpp"
#include "fundtranstype.hpp"
#include "grouplist.hpp"
#include "groupfund.hpp"
#include "groupfundlist.hpp"
#include "mfaccount.hpp"
#include "mfaccountlist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtcooptions2.hpp"
#include "protectedfundlist.hpp"
#include "residency.hpp"
#include "savingplanmasterlist.hpp"
#include "seqfundvalidation.hpp"
#include "segfundvalidationrules.hpp"
#include "shareholder.hpp"
#include "sysallocationlist.hpp"
#include "sysallocation.hpp"
#include "sysindexlist.hpp"
#include "systematic.hpp"
#include "systematiclist.hpp"
#include "systematicbankinstructionslist.hpp"
#include "systematicbankinstructions.hpp"
#include "splitcommissionlist.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"
#include "tradingfeerules.hpp"
#include "transactionlist.hpp"
#include "trademinamtcheck.hpp"
#include "fundlmtoverride.hpp"
#include "fundlmtoverridelist.hpp"
#include "rdradvice.hpp"
#include "dstcworksession.hpp"
#include "defaultsysconfigdetaillist.hpp"
#include "RegulatoryValidationErrorList.hpp"
#include "translationtable.hpp"

#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0007_vw.hpp>
#include <ifastdataimpl\dse_dstc0049_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0084_req.hpp>
#include <ifastdataimpl\dse_dstc0095_req.hpp>
#include <ifastdataimpl\dse_dstc0101_vw.hpp>
#include <ifastdataimpl\dse_dstc0107_vw.hpp>
#include <ifastdataimpl\dse_dstc0121_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0159_vw.hpp>
#include <ifastdataimpl\dse_dstc0213_req.hpp>
#include <ifastdataimpl\dse_dstc0213_vw.hpp>
#include <ifastdataimpl\dse_dstc0354_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0437_vw.hpp>
#include <ifastdataimpl\dse_dstc0438_req.hpp>


namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const NON_RESIDENT_TAX_JURISD_CONTR_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT I_CHAR * const EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
   extern CLASS_IMPORT I_CHAR * const SIGNATURE_DATE_LATER;
   extern CLASS_IMPORT I_CHAR * const PAC_STOP_DATE_RESTRICTION;
   extern CLASS_IMPORT I_CHAR * const SIGNATURE_DATE_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const INVALID_AMOUNT_TYPE_BY_SEG_RULES;
   extern CLASS_IMPORT I_CHAR * const PLAN_CANNOT_BE_MANUALLY_CREATED;
   extern CLASS_IMPORT I_CHAR * const NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP;
 }

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME      = I_( "Systematic" );
   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const SEP_SLASH         = I_( "/" );  

   const I_CHAR * const FUNDNAME       = I_( "FUNDNAME" ); 
   const I_CHAR * const FLAGNAME       = I_( "FLAGNAME" );
   const I_CHAR * const FUND           = I_( "FUND" );
   const I_CHAR * const CLASS          = I_( "CLASS" );
   const I_CHAR * const BROKER          = I_( "BROKER" );
   const I_CHAR * const AGENT          = I_( "AGENT" );//ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 

   const I_CHAR * const MAXFEE         = I_( "MAXFEE" );
   const I_CHAR * const DECIMALS       = I_( "NUMOFDECIMALS" );
   const I_CHAR * const TRADE_TYPE     = I_( "TRADE_TYPE" );
   const I_CHAR * const CURRENCY_TAG   = I_( "CURRENCY" );

   const I_CHAR * const AMOUNT         = I_( "AMOUNT" );
   const I_CHAR * const FREQUENCY      = I_( "FREQUENCY" );
   const I_CHAR * const EFT_PAY_TYPE   = I_( "E" );
   const I_CHAR * const ZERO           = I_( "0" );
   //const I_CHAR * const ONE           = I_( "1" );
   const I_CHAR * const BLANKSTRING    = I_( " " );

   const I_CHAR * const FREQ_DAILY        = I_( "0" );
   const I_CHAR * const FREQ_WEEKLY       = I_( "1" );
   const I_CHAR * const FREQ_BIWEEKLY     = I_( "2" );
   const I_CHAR * const FREQ_MONTHLY      = I_( "3" );
   const I_CHAR * const FREQ_SEMIMONTHLY  = I_( "4" );
   const I_CHAR * const FREQ_QUARTERLY    = I_( "5" );
//   const I_CHAR * const FREQ_SEMIANNUALLY = I_( "6" );
   const I_CHAR * const FREQ_ANNUALLY     = I_( "7" );
   const I_CHAR * const FREQ_OTHER        = I_( "8" );

   const I_CHAR * const AUTO_TRANS_ALLOCATION_LIST       = I_("AutoTransAllocationList");
   const I_CHAR * const AUTO_ACCT_TRANS_ALLOCATION_LIST  = I_("AutoAcctTransAllocationList");
   //const I_CHAR * const CFDS     = I_("CFDS - Canada");
   //const I_CHAR * const JAPAN    = I_( "Japan");

   const I_CHAR * const CASH = I_("CASH");
   const I_CHAR * const MULTITRANSFER        = I_("T/E Multi Transfer/Exchange");
   const I_CHAR * const FRONT_END            = I_("Front End");
   const I_CHAR * const REDEMPTION_PERCHASE  = I_("Redemption/Purchase");

   const I_CHAR * const TRANSFER             = I_("Transfer");
   const I_CHAR * const EXCHANGE             = I_("Exchange");
   const I_CHAR * const WITHIN_FUND_CLASS    = I_("Within Fund and Class");
   const I_CHAR * const WITHIN_CLASS_FUND    = I_("Within Class of Fund");

   const I_CHAR * const RRSP_TAXTYPE = I_("1");
   const I_CHAR * const RRIF_TAXTYPE = I_("2");
   const I_CHAR * const PRIF_TAXTYPE = I_("R");

   const I_CHAR * const RRSP_TO_RRIF = I_("RRSP to RRIF");

   const I_CHAR * const PURCHASE_CODE    = I_( "ED" );     // trade trans type Purchase
   const I_CHAR * const REDEMPTION_CODE  = I_( "PW" );      // trade trans type Redemption
   const I_CHAR * const EX_FER_IN_CODE   = I_( "XFIN" );    // trade trans type Exchange In 
   const I_CHAR * const EX_FER_OUT_CODE  = I_( "XFOUT" );   // trade trans type Exchange Out
   const I_CHAR * const SWP_CHG        = I_( "SWP_CHG" );

   const I_CHAR * const SYS_INDEX_LIST  = I_( "SysIndexList" );
   const I_CHAR * const AUTO_TRFER     = I_( "AT" );
   const I_CHAR * const SAVING_PLAN     = I_( "V" );
   const I_CHAR * const AMOUNT_TYPE     = I_( "D" );
   const I_CHAR * const PAC        = I_( "P" );
   const I_CHAR * const SWP          = I_( "S" );

   const I_CHAR * const MONTHLY_VUB       = I_( "1" );
   const I_CHAR * const INITIAL_VUB       = I_( "2" );
   const I_CHAR * const VUBOPTION_WAIVED       = I_( "3" );
   const I_CHAR * const VUB_FEE_TYPE_FRACTION  = I_( "F" );
   const I_CHAR * const INITIALVUBAMT  = I_( "INITIALVUBAMT" );

   const I_CHAR * const SEMI_MONTHLY  = I_( "YYYYYYYYYYYY" );
   const I_CHAR * const MONTHLY       = I_( "YYYYYYYYYYYY" );
   const I_CHAR * const QUALTERLY     = I_( "YNNYNNYNNYNNYNN" );
//   const I_CHAR * const SEMI_ANNUALY  = I_( "YNNNNNYNNNNNYNNNNN" );
   const I_CHAR * const ANNUALY       = I_( "YNNNNNNNNNNNYNNNNNNNNNNN" );
//   const I_CHAR * const OTHER  = I_( "YNNNNNNNNNNN" );
   const I_CHAR * const COMMISSION_TYPE_ZERO = I_("0");
   const I_CHAR * const COMMISSION_TYPE_ONE  = I_("1");
   const I_CHAR * const COMMISSION_TYPE_TWO  = I_("2");   
   const I_CHAR * const BACKENDLOAD          = I_( "BEL" );
   const I_CHAR * const FRONTENDLOAD         = I_( "FEL" );
   const I_CHAR * const FROMFUND             = I_( "FROMFUND" );
   const I_CHAR * const TOFUND               = I_( "TOFUND" );
   const I_CHAR * const MINIMUM_AMT          = I_( "MINIMUM_AMT");
   const I_CHAR * const MARGIN               = I_( "02" );
   const I_CHAR * const GOOD                 = I_( "Y" );
   const I_CHAR * const GWA                  = I_( "G" );
   const I_CHAR * const LWA                  = I_( "L" );
   const I_CHAR * const EWA                  = I_( "E" );
   const I_CHAR * const GWLWA_OPTIONS        = I_( "G,L,A" );

   const I_CHAR * const VERIFY_CATEGORY_SYSTEMATIC = I_("5");  //Systematic
   const I_CHAR * const VERIFY_LEVEL_ACCOUNT       = I_("02"); //Account level 
   const I_CHAR * const RDR_ADVICE_PROVIDED   = I_ ("02");
   const I_CHAR * const VERIFIED			  = I_("01");
   const I_CHAR * const UNVERIFIED			  = I_("02");
   const I_CHAR * const BLANK_SUBSTITUTION_VALUE  = I_("= ;");
   const I_CHAR * const TRANS_TYPE_SAVING_PLAN    = I_( "V" );
   const I_CHAR * const NF_REQUIRED              = I_("02");
   const I_CHAR * const NF_SUPPRESS              = I_("01");
   const I_CHAR * const REGULATORY               = I_("ERG"); 
}

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;

   const char *const CFX_TRANS      = "CFXTRAN";
}
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RESTART_PAC_ON_CAPPED_FUND;
   extern CLASS_IMPORT I_CHAR * const SWP_TAX_OVERRIDE;
}
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEPOSIT;
   extern CLASS_IMPORT const DSTCRequest TRANS_NUM;
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
   extern CLASS_IMPORT const DSTCRequest MEXT_PROC_DATE;
}

namespace AMT_TYPE
{
    extern CLASS_EXPORT I_CHAR * const AMOUNT       = I_("D");
    extern CLASS_EXPORT I_CHAR * const CUSTOM       = I_("C");
    extern CLASS_EXPORT I_CHAR * const PORTFOLIO    = I_("R");
}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_CHAR;
   extern const long ERR_ENTRY_BOTH_FIELDS;
   extern const long ERR_INSTCODE_NOT_EXIST;
   extern const long ERR_TRANSITNO_NOT_EXIST;
   extern const long ERR_SWIFTCODE_NOT_EXIST;
   extern const long ERR_REFNUMBER_NOT_EXIST;
   extern const long ERR_INVALID_NEGATIVE_AMOUNT;
   extern const long ERR_AMOUNT_EXCEED_MAX_LIMIT;
   extern const long ERR_PAC_LESS_THAN_MINIMUM_ALLOW;
   extern const long WARN_PAC_LESS_THAN_MINIMUM_ALLOW;
   extern const long ERR_SWP_LESS_THAN_MINIMUM_ALLOW;
//	extern const long ERR_TWO_DECIMAL_POINT_ONLY;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_TO_GROUP;
   extern const long ERR_FUND_NOT_EFFECTIVE;
   extern const long ERR_REDEMP_STOPPED_FOR_SWP;
   extern const long ERR_ACCT_HAS_STOPPED_PAC_OR_PURCH;
   extern const long ERR_ACCT_HAS_STOPPED_SWP_OR_REDEM;
   extern const long ERR_FIELD_REQUIRED_PLS_SELECT;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE;

   extern const long ERR_PAC_UNITS_NOT_ALLOWED;
   extern const long ERR_SWP_FUND_BLANK;
   extern const long ERR_FUND_CAN_NOT_BE_BLANK;
   extern const long ERR_PAYTYPE_NOT_AVAIL_FOR_FUND;
   extern const long ERR_INVALID_NET;
   extern const long ERR_PAC_SWP_UNITS_NOT_ALLOWED;
   extern const long ERR_FEE_MORE_THAN_MAX;
   extern const long ERR_FREQ_DIFF_FROM_DEF;
   extern const long ERR_AT_LEAST_ONE_MONTH_MUST_ACTIVE;

   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_BLANK_FUND;
   extern const long ERR_BLANK_CLASS;

   extern const long ERR_TWO_DECIMAL_POINT_ONLY;
   extern const long ERR_INCORRECT_PRECISION;
   //tremperary put it here
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_FUNDTO_CLASSTO_ACCOUNTTO;
   extern const long ERR_AT_AMOUNT_TRANSFER;
   extern const long ERR_AT_FUNDTO_CLASSTO_ACOUNTTO_SAME_AS_FROM;
   extern const long ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED;
   extern const long ERR_FUNDTO_GIC_NOT_ALLOWED;
   extern const long ERR_ACCOUNT_NUMBER_NOT_ALL_DIGITS;
   extern const long ERR_AT_ACCOUNT_NOT_EXIST;
   extern const long ERR_TRANSFER_TAX_TYPE;
   extern const long ERR_AT_AMOUNT_TYPE;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_CAPPEDFUND_STATUSW;
   extern const long ERR_CAPPEDFUND_STATUSE;
   extern const long ERR_BANKINFO_REQUIRED;
   extern const long ERR_DAYOFWEEK_REQUIRED;
   extern const long ERR_SWP_UNDER_REGISTERED_ACCT;
   extern const long ERR_INSTCODE_TOO_BIG;
   extern const long ERR_TRANSITNO_TOO_BIG;
   extern const long ERR_BANKACCTNUM_TOO_BIG;
   extern const long ERR_SYS_DEFF_LESS_THAN_ACCT_DEFF;
   extern const long ERR_INVALID_AMT_TYPE;
   extern const long ERR_NO_ACTIVE_BATCH;
   extern const long ERR_CONFLICTING_RECORD_ALREADY_EXISTS;
   extern const long ERR_FRACTIONAL_VALUES_NOT_ALLOWED_IN_CURRENCY;
   extern const long ERR_INIT_CONTRIB_MUST_GREATER_THAN_FEE;
   extern const long ERR_INIT_CONTRIB_MUST_GREATER_THAN_FEE_12;
   extern const long ERR_WRONG_FRACTION_FORMAT;
   extern const long ERR_DENOMINATOR_IS_ZERO;
   extern const long ERR_BANK_ACCT_NUM_CANNOT_BE_BLANK;
   extern const long ERR_INDEXING_EXISTS;
   extern const long ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO;
   extern const long ERR_FEE_MUST_BE_NUMERIC;
   extern const long ERR_NEGATIVE_FEE_NOT_ALLOW;
   extern const long ERR_FEE_LESS_OR_EQUAL_100;
   extern const long ERR_INVALID_AMOUNT_TYPE_FOR_PAC;
   extern const long ERR_INVALID_AMOUNT_TYPE_FOR_SWP;
   extern const long ERR_WARN_ENTIRE_ACCT_ASSIGNED;
   extern const long ERR_FEE_DIFFER_FROM_DEFAULT;
   extern const long ERR_EXCH_IN_FEE_OVER_MAXIMUM;
   extern const long ERR_EXCH_IN_FEE_UNDER_MINIMUM;
   extern const long ERR_FEE_MORE_THAN_MIN;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER;
   extern const long ERR_WARN_NEXT_PROC_DATE_AFTER_STOP_DATE;
   extern const long ERR_WARN_NEXT_PROC_DATE_BEFORE_EFFECTIVE_DATE;
   extern const long ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE;
   extern const long ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_REDEMPTION_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_SYSGENTRFIN_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_SYSGENTRFOUT_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_PAC_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_SWP_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_PAC_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_SWP_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_SYSGENTRFIN_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_SYSGENTRFOUT_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP;
   extern const long ERR_WARN_SWP_LESS_THAN_MINIMUM_ALLOW;
   extern const long ERR_NET_UNIT_PERCENT_NOT_ALLOW;
   extern const long ERR_AMT_CAPPED_FUND_INCREASE;
   extern const long ERR_MIN_INIT_PURCHASE;
   extern const long ERR_WARN_MIN_INIT_PURCHASE;
   extern const long ERR_ACQ_FEES_MUST_BE_ZERO_FOR_AUTOMATIC_TRANSFER;
   extern const long ERR_CANNOT_RESTART_CAPPED_FUND;
   extern const long ERR_TAX_TYPE_CANNOT_TRADE_IN_THE_CURRENCY;

   extern const long ERR_REDEMPTION_TOTAL_TAX_RATE_GREATER_THAN_100;
   extern const long ERR_TAX_RATE_LESS_THAN_ZERO_OR_GREATER_THAN_100;
   extern const long ERR_TAX_AMOUNT_NEGATIVE;
   extern const long ERR_TAX_AMOUNT_GREATER_THAN_AMOUNT;
   extern const long ERR_TOTAL_TAX_AMOUNT_GREATER_THAN_AMOUNT;
   extern const long WARN_NO_CHECK_ON_TAXRATE_FOR_NON_DOLLAR_AMTTYPE;
   extern const long ERR_FEE_RATE_ABOVE_MAX;
   extern const long ERR_AMTTYPE_APPL_TO_BEL_FUND;
   extern const long ERR_FULL_EXCHANGE_INDICATED;
   extern const long ERR_INVALID_AMTTYPE_FOR_FULL_TRANSFER;
   extern const long ERR_NO_APPLICATBLE_FOR_TOFUND;

   extern const long ERR_CONTRIBUTION_NOT_ALLOWED_FOR_NON_RESIDENT;
   extern const long WARN_CONTRIBUTION_NOT_ALLOWED_FOR_NON_RESIDENT;

   extern const long ERR_TRADE_DATE_OUTSIDE_MIN_MAX;
   extern const long ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN;
   extern const long ERR_SWP_UNITS_NOT_ALLOWED;
   extern const long ERR_FUTURE_DATED_STOPDATE;
   extern const long ERR_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND;//P0186486_FN15_The Source of Funds
   extern const long WARN_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND;
   extern const long ERR_AMT_TYPE_NOTAPPLICABLE;
   extern const long ERR_SWP_CANNOT_BESETUP;
   extern const long WARN_RDR_ADVICE_UPDATED;
   extern const long ERR_INCREMENTED_AMT_IS_RDR_ADVICED;
   extern const long ERR_EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
   extern const long WARN_EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
   extern const long ERR_FUTURE_DATE;
   extern const long ERR_REQ_FIELD_EMPTY; 
   extern const long ERR_INVALID_TIME_FORMAT;  
   extern const long ERR_SIGNATURE_DATE_LATER;
   extern const long WARN_SIGNATURE_DATE_LATER;
   extern const long ERR_PAC_STOP_DATE_RESTRICTION;
   extern const long WARN_PAC_STOP_DATE_RESTRICTION;
   extern const long ERR_SIGNATURE_DATE_REQUIRED;
   extern const long WARN_SIGNATURE_DATE_REQUIRED;
   extern const long ERR_INVALID_AMOUNT_TYPE_BY_SEG_RULES;
   extern const long WARN_INVALID_AMOUNT_TYPE_BY_SEG_RULES;
   extern const long ERR_PLAN_CANNOT_BE_MANUALLY_CREATED;
   extern const long WARN_PLAN_CANNOT_BE_MANUALLY_CREATED;
   extern const long ERR_NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP;
   extern const long WARN_NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP;
   extern const long ERR_SWP_PERCENT_NOT_ALLOWED;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RESTART_PAC_ON_CAPPED_FUND;
   extern CLASS_IMPORT I_CHAR * const SWP_TAX_OVERRIDE;
}

namespace TRADETYPE 
{
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER_OUT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFTextFieldId PayTypeAddrCode;
   extern CLASS_IMPORT const BFTextFieldId PayTypeDesc;
   extern CLASS_IMPORT const BFTextFieldId PayTypeBankNum;
   extern CLASS_IMPORT const BFTextFieldId SystematicCrossField1;
   extern CLASS_IMPORT const BFTextFieldId SystematicCrossField2;
   extern CLASS_IMPORT const BFTextFieldId FundToClassToAccountTo;
   extern CLASS_IMPORT const BFTextFieldId AtFundtoClasstoCrossEdit;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeExchange;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeCrossEdit;
   extern CLASS_IMPORT const BFTextFieldId AtFrequency;
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;

   extern CLASS_IMPORT const BFTextFieldId MonthlyIndicator;
   extern CLASS_IMPORT const BFTextFieldId BankInformation;
   extern CLASS_IMPORT const BFTextFieldId AllocationFromFund;
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId CotClient;
   extern CLASS_IMPORT const BFTextFieldId SystematicPayType;
   extern CLASS_IMPORT const BFTextFieldId VUBFee;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeFrac1;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeFrac2;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeRate;
   extern CLASS_IMPORT const BFTextFieldId ExchInFeeExist;
   extern CLASS_IMPORT const BFTextFieldId MonthIndicator;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeSystematic;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeSettleCurr;
   extern CLASS_IMPORT const BFTextFieldId PACSWPFrequency;
   extern CLASS_IMPORT const BFTextFieldId SystematicPayPAC;
   extern CLASS_IMPORT const BFTextFieldId SystematicPaySWP;
   extern CLASS_IMPORT const BFTextFieldId TransTypeDefault;
   extern CLASS_IMPORT const BFTextFieldId TradePayTypeDefault;

   extern CLASS_IMPORT const BFTextFieldId VUBCrossedit;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeAT;
   extern CLASS_IMPORT const BFTextFieldId ExchInFeeFlatPercent;

   extern CLASS_IMPORT const BFTextFieldId PACallowed;
   extern CLASS_IMPORT const BFTextFieldId SWPallowed;

   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFTextFieldId ContractType;
   extern CLASS_IMPORT const BFTextFieldId MaturityType;
   extern CLASS_IMPORT const BFDateFieldId UserMaturityDate;
   extern CLASS_IMPORT const BFTextFieldId AgeBasedOn;
   extern CLASS_IMPORT const BFTextFieldId FundAllow;
   extern CLASS_IMPORT const BFDateFieldId NextProcessDate;
   extern CLASS_IMPORT const BFTextFieldId ValidationPassed;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFTextFieldId FeeType;
   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
   extern CLASS_IMPORT const BFDecimalFieldId UnsettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId UnsettledValue;
   extern CLASS_IMPORT const BFTextFieldId PACSWPOverride;

   //extern CLASS_IMPORT const BFTextFieldId SystematicGridLeftHeading;

   extern CLASS_IMPORT const BFTextFieldId FedTaxRatePUD;
   extern CLASS_IMPORT const BFTextFieldId FedTaxRateAmountPUDXEdit;
   extern CLASS_IMPORT const BFTextFieldId ProvTaxRatePUD;
   extern CLASS_IMPORT const BFTextFieldId ProvTaxRateAmountPUDXEdit;
   extern CLASS_IMPORT const BFTextFieldId FedProvTaxRatePUDXEdit;
   extern CLASS_IMPORT const BFTextFieldId FedProvTaxPercPUDXEdit;
   extern CLASS_IMPORT const BFDecimalFieldId FeeAmt;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeAlloc;

   extern CLASS_IMPORT const BFTextFieldId FromSoftCapCheck;
   extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;
   extern CLASS_IMPORT const BFDateFieldId TradeStartDate;
   extern CLASS_IMPORT const BFDateFieldId TradeStopDate;
   
   extern CLASS_IMPORT const BFTextFieldId AddPerm;
   extern CLASS_IMPORT const BFTextFieldId FromToFundClassAcctTo;
   extern CLASS_IMPORT const BFDateFieldId BatchDate;
   extern CLASS_IMPORT const BFNumericFieldId TransNum;
   extern CLASS_IMPORT const BFTextFieldId RuleType; //IN2796443 - Fund Limitation 
   extern CLASS_IMPORT const BFTextFieldId StopFlag;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_SWP_IA;//P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA_SWP;  //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SWPAmountType;
   extern CLASS_IMPORT const BFTextFieldId CalcAmountXEdit;
   extern CLASS_IMPORT const BFTextFieldId LGFundClassXEdit;

   extern CLASS_IMPORT const BFTextFieldId VerifyStat;
   extern CLASS_IMPORT const BFTextFieldId NonFinConfirms;
   extern CLASS_IMPORT const BFTextFieldId RRIFGLOpt;
   extern CLASS_IMPORT const BFTextFieldId NetOfFeesFlag;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId RDREnv;
   extern CLASS_IMPORT const BFTextFieldId RDRApplic;
   extern CLASS_IMPORT const BFTextFieldId RDRDefault;
   extern CLASS_IMPORT const BFTextFieldId XEditEventRecieptDateTime;
   extern CLASS_IMPORT const BFTextFieldId UCITFlag;
	extern CLASS_IMPORT const BFTextFieldId SrcOfFundSrcOfAcctXEdit;
   extern CLASS_IMPORT const BFTextFieldId TimeFactor;
   extern CLASS_IMPORT const BFTextFieldId ServerTime;
   extern CLASS_IMPORT const BFTextFieldId ScreenActivityType;
   extern CLASS_IMPORT const BFTextFieldId SystematicGridLeftHeading;
   extern CLASS_IMPORT const BFTextFieldId NotApplicable;
   extern CLASS_IMPORT const BFDecimalFieldId YearlyAmount;
   extern CLASS_IMPORT const BFDecimalFieldId CPIRate;
   extern CLASS_IMPORT const BFDecimalFieldId PayoutFactorRate;
   extern CLASS_IMPORT const BFTextFieldId SWPAmountTypeAllocCustomPayout;
   extern CLASS_IMPORT const BFTextFieldId SWPAmountTypeAllocPortfolioPayout;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeSettleCurrCustomPayout;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeSettleCurrPortfolioPayout;
   extern CLASS_IMPORT const BFTextFieldId TradeFileProcessorDefault;
}

namespace REG_AGENT_TAX_TYPE
{
	const I_CHAR * const ORD_ACC = I_("OA"); 
	const I_CHAR * const SPL_ACC = I_("SA");
	const I_CHAR * const SRS_ACC = I_("SR"); 
}

namespace RULE_TYPE
{
   extern const I_CHAR * const BANKRUPTCY;
}
namespace PLATFORM
{
 const I_CHAR * const DESKTOP = I_("01"); 
}

namespace FROM_TO
{
  const I_CHAR * const FROM = I_("FROM"); 
  const I_CHAR * const TO   = I_("TO"); 
}
//this is defined in the RegulatoryValidationErrorList.
namespace REGULATION
{
  extern CLASS_IMPORT const I_CHAR * const SIF ;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   //  Field DD Id,                    State Flags,            Group Flags 
   { ifds::RunMode         ,           BFCBO::NONE,                 0 },
   { ifds::AccountNum      ,           BFCBO::NONE,                 0 },
   { ifds::BrokerCode      ,           BFCBO::NONE,                 0 },
   { ifds::BranchCode      ,           BFCBO::NONE,                 0 },
   { ifds::SalesRepCode    ,           BFCBO::NONE,                 0 },
   { ifds::BrokerName      ,           BFCBO::NONE,                 0 },
   { ifds::BranchName      ,           BFCBO::NONE,                 0 },
   { ifds::SlsrepName      ,           BFCBO::NONE,                 0 },
   { ifds::Amount          ,           BFCBO::NONE,                 0 },
   { ifds::AmountType      ,           BFCBO::REQUIRED,             0 },
   { ifds::AmountTypeDesc  ,           BFCBO::NONE,                 0 },
   { ifds::GrossOrNet      ,           BFCBO::REQUIRED,             0 },
   { ifds::Fee             ,           BFCBO::NONE,                 0 },
   { ifds::FlatPercent     ,           BFCBO::NONE,                 0 },
   { ifds::FeeCurrency     ,           BFCBO::NONE,                 0 },
   { ifds::FeeCurrDesc     ,           BFCBO::NONE,                 0 },
   { ifds::AdminFeeAmt     ,           BFCBO::NONE,                 0 },
   { ifds::AdminFeeCurr    ,           BFCBO::NONE,                 0 },
   { ifds::AdminFeeCurrDesc,           BFCBO::NONE,                 0 },
   { ifds::PayType         ,           BFCBO::NONE,                 0 },
   { ifds::PayTypeDesc     ,           BFCBO::NONE,                 0 },
   { ifds::BankIdType      ,           BFCBO::NONE,                 0 },
   { ifds::BankIdValue     ,           BFCBO::NONE,                 0 },
   { ifds::BankId          ,           BFCBO::NONE,                 0 },
   { ifds::SwiftCode       ,           BFCBO::NONE,                 0 },
   { ifds::RefNumber       ,           BFCBO::NONE,                 0 },
   { ifds::TransitNo       ,           BFCBO::NONE,                 0 },
   { ifds::InstCode        ,           BFCBO::NONE,                 0 },	
   { ifds::BankAcctNum     ,           BFCBO::NONE,                 0 },
   { ifds::BankAcctName    ,           BFCBO::NONE,                 0 },
   { ifds::SourceOfBankAcct,           BFCBO::NONE,                 0 },
   { ifds::BankAcctCurrency,           BFCBO::NONE,                 0 },
   { ifds::BankCurrDesc    ,           BFCBO::NONE,                 0 },
   { ifds::BankAcctType    ,           BFCBO::NONE,                 0 },
   { ifds::BankAcctTypeDesc,           BFCBO::NONE,                 0 },
   { ifds::SrcOfFund       ,           BFCBO::NONE,                 0 },
   { ifds::SrcOFundDesc    ,           BFCBO::NONE,                 0 },
   { ifds::January         ,           BFCBO::NONE,                 0 },
   { ifds::February        ,           BFCBO::NONE,                 0 },
   { ifds::March           ,           BFCBO::NONE,                 0 },
   { ifds::April           ,           BFCBO::NONE,                 0 },
   { ifds::May             ,           BFCBO::NONE,                 0 },
   { ifds::June            ,           BFCBO::NONE,                 0 },
   { ifds::July            ,           BFCBO::NONE,                 0 },
   { ifds::August          ,           BFCBO::NONE,                 0 },
   { ifds::September       ,           BFCBO::NONE,                 0 },
   { ifds::October         ,           BFCBO::NONE,                 0 },
   { ifds::November        ,           BFCBO::NONE,                 0 },
   { ifds::December        ,           BFCBO::NONE,                 0 },
   { ifds::EndOfMonth      ,           BFCBO::NONE,                 0 },
   { ifds::LastProcessDate ,           BFCBO::NONE,                 0 },
   { ifds::NextProcessDate ,           BFCBO::NONE,                 0 },
   { ifds::AddrCode        ,           BFCBO::NONE,                 0 },
   { ifds::StatusCode      ,           BFCBO::NONE,                 0 },
   { ifds::EffectiveDate   ,           BFCBO::REQUIRED,             0 },
   { ifds::ProcessDate     ,           BFCBO::NONE,                 0 },
   { ifds::ModDate         ,           BFCBO::NONE,                 0 },
   { ifds::StopDate        ,           BFCBO::NONE,                 0 },
   { ifds::Username        ,           BFCBO::NONE,                 0 },
   { ifds::ModUser         ,           BFCBO::NONE,                 0 },
   { ifds::BankDetlVer     ,           BFCBO::NONE,                 0 },
   { ifds::AddrLine1       ,           BFCBO::NONE,                 0 },
   { ifds::AddrLine2       ,           BFCBO::NONE,                 0 },
   { ifds::AddrLine3       ,           BFCBO::NONE,                 0 },
   { ifds::AddrLine4       ,           BFCBO::NONE,                 0 },
   { ifds::AddrLine5       ,           BFCBO::NONE,                 0 },
   { ifds::PostalCode      ,           BFCBO::NONE,                 0 },
   { ifds::InstName        ,           BFCBO::NONE,                 0 },
   { ifds::SlsrepAltName   ,           BFCBO::NONE,                 0 },
   { ifds::FundCode        ,           BFCBO::NONE,                 0 },
   { ifds::ClassCode       ,           BFCBO::NONE,                 0 },
   { ifds::PACSWPId        ,           BFCBO::NONE,                 0 },
   { ifds::TransType       ,           BFCBO::NONE,                 0 },
   { ifds::BankDetlVer     ,           BFCBO::NONE,                 0 },
   { ifds::PayReason1      ,           BFCBO::NONE,                 0 },
   { ifds::PayReason2      ,           BFCBO::NONE,                 0 },

   { ifds::FundToCode      ,           BFCBO::NONE,                 0 },
   { ifds::ClassToCode     ,           BFCBO::NONE,                 0 },
   { ifds::AccountTo       ,           BFCBO::NONE,                 0 },
   { ifds::BELFee          ,           BFCBO::NONE,                 0 },
   { ifds::BatchUser       ,           BFCBO::READ_ONLY,            0 },
   { ifds::BatchName       ,           BFCBO::NONE,                 0 },
   { ifds::BatchTrace      ,           BFCBO::NONE,                 0 },
   
   { ifds::TransferType    ,           BFCBO::NONE,                 0 },
   { ifds::Frequency       ,           BFCBO::NONE,                 0 },
   { ifds::FlatPercentDesc ,           BFCBO::NONE,                 0 },
   { ifds::FrequencyDesc   ,           BFCBO::NONE,                 0 },
   { ifds::TransTypeDesc   ,           BFCBO::NONE,                 0 },

   { ifds::EntityType      ,           BFCBO::NONE,                 0 },
   { ifds::EntityTypeSeq   ,           BFCBO::NONE,                 0 },
   
   { ifds::SetAsDefault    ,           BFCBO::NONE,                 0 },
   { ifds::InitFactor      ,           BFCBO::NONE,                 0 },
   { ifds::PlanTerm        ,           BFCBO::NONE,                 0 },
   { ifds::PaymentAmt      ,           BFCBO::NONE,                 0 },
   { ifds::LastPayment     ,           BFCBO::NONE,                 0 },
   { ifds::Commission      ,           BFCBO::NONE,                 0 },
   { ifds::AdminFeeAmtClan ,           BFCBO::NONE,                 0 },
   { ifds::DayOfWeek       ,           BFCBO::NONE,                 0 },

   { ifds::AnnualMaint     ,           BFCBO::NONE,                 0 },
   { ifds::InitialAmt      ,           BFCBO::NONE,                 0 },
   { ifds::VUBExpectedAmt  ,           BFCBO::NONE,                 0 },
   { ifds::VUBCollectedAmt ,           BFCBO::NONE,                 0 },
   { ifds::VUBFeeType      ,           BFCBO::NONE,                 0 },
   { ifds::PlanCode        ,           BFCBO::NONE,                 0 },
   { ifds::IndexExist      ,           BFCBO::NONE,                 0 },
   { ifds::VUBFee          ,           BFCBO::READ_ONLY,            0 },
   { ifds::VUBFeeFrac1     ,           BFCBO::NONE,                 0 },
   { ifds::VUBFeeFrac2     ,           BFCBO::NONE,                 0 },
   { ifds::VUBFeeRate      ,           BFCBO::NONE,                 0 },
   { ifds::VUBPayOption    ,           BFCBO::NONE,                 0 },
   { ifds::AnnualFeeDate   ,           BFCBO::NONE,                 0 },


   { ifds::FundClass       ,           BFCBO::NONE,                 0 },
   { ifds::CompoundDate    ,           BFCBO::NONE,                 0 },
   { ifds::PayTypeAddrCode ,           BFCBO::NONE,                 0 },
   { ifds::PayTypeBankNum  ,           BFCBO::NONE,                 0 },
   { ifds::SystematicCrossField1,      BFCBO::NONE,                 0 },
   { ifds::FundToClassToAccountTo,     BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::AmountTypeCrossEdit,        BFCBO::NONE,                 0 },

   { ifds::FrFundNumber    ,           BFCBO::NONE,                 0 },
   { ifds::ToFundNumber    ,           BFCBO::NONE,                 0 },

   { ifds::AtFundtoClasstoCrossEdit,   BFCBO::NONE,                 0 },

   { ifds::MonthlyIndicator,           BFCBO::NONE,                 0 },
   { ifds::BankInformation ,           BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::AllocationFromFund,         BFCBO::NONE,                 0 },
   { ifds::SplitComm       ,           BFCBO::NONE,                 0 },

   { ifds::ACHProcessor    ,           BFCBO::NONE,                 0 },
   { ifds::BankId          ,           BFCBO::NONE,                 0 },
   { ifds::FFC             ,           BFCBO::NONE,                 0 },
   { ifds::FFC1            ,           BFCBO::NONE,                 0 },
   { ifds::BankAddr1       ,           BFCBO::NONE,                 0 },
   { ifds::BankAddr2       ,           BFCBO::NONE,                 0 },
   { ifds::BankAddr3,                  BFCBO::NONE,                 0 },
   { ifds::BankAddr4,                  BFCBO::NONE,                 0 },
   { ifds::BankAddr5,                  BFCBO::NONE,                 0 },
   { ifds::BankContact,                BFCBO::NONE,                 0 },
   { ifds::BankCountry,                BFCBO::NONE,                 0 },
   { ifds::BankPostal,                 BFCBO::NONE,                 0 },
   { ifds::SystematicPayType,          BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::SystematicCrossField2,      BFCBO::NONE,                 0 },
   { ifds::ExchInFee,                  BFCBO::NONE,                 0 },
   { ifds::ExchInFlatPercent,          BFCBO::NONE,                 0 },
   { ifds::ExchOutFee,                 BFCBO::NONE,                 0 },
   { ifds::ExchOutFlatPrcnt,           BFCBO::NONE,                 0 },
   { ifds::MonthIndicator,             BFCBO::NONE,                 0 },
   { ifds::ModPerm,                    BFCBO::NONE,                 0 },

   { ifds::VUBCrossedit,               BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::ATFeeApply,                 BFCBO::NONE,                 0 },
   { ifds::ExchInFeeFlatPercent,       BFCBO::IMMEDIATE_VALIDATION, 0 },

// { ifds::SystematicGridLeftHeading,  BFCBO::NONE,                 0 },
   { ifds::PayMethod,                  BFCBO::NONE,                 0 },
   { ifds::ACHProcessor,               BFCBO::NONE,                 0 },
   { ifds::BatchDate,                  BFCBO::NONE,                 0 },
   { ifds::TransNum,                   BFCBO::NONE,                 0 },

   { ifds::StopReasonPAC,                 BFCBO::READ_ONLY,            0 },

   { ifds::FedTaxPUDOverride,          BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FedRate,                    BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::ProvTaxPUDOverride,         BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::ProvRate,                   BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FedTaxRatePUD,              BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FedTaxRateAmountPUDXEdit,   BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::ProvTaxRatePUD,             BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::ProvTaxRateAmountPUDXEdit,  BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FedProvTaxRatePUDXEdit,     BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FedProvTaxPercPUDXEdit,     BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::FromSoftCapCheck,           BFCBO::IMMEDIATE_VALIDATION, 0}, 
   { ifds::ToSoftCapCheck,             BFCBO::IMMEDIATE_VALIDATION, 0}, 
   { ifds::FromToFundClassAcctTo,      BFCBO::IMMEDIATE_VALIDATION, 0},
   { ifds::CalcAmountXEdit,            BFCBO::IMMEDIATE_VALIDATION, 0},
   { ifds::LGFundClassXEdit,           BFCBO::IMMEDIATE_VALIDATION, 0},
   
   { ifds::SrcOfFunds_IA,              BFCBO::NONE,                 0}, //P0186486_FN15_The Source of Funds
   { ifds::SrcOfFundSrcOfAcctXEdit,    BFCBO::NONE,                 0 },

   { ifds::VerifyStat,                 BFCBO::NONE,                 0 },
   { ifds::NonFinConfirms,             BFCBO::NONE,                 0 },
   { ifds::RDRAdvice,                  BFCBO::NONE,                 0 },
   { ifds::EventReceiptDate,               BFCBO::NONE,                 0}, 
   { ifds::EventReceiptTime,               BFCBO::NONE,                 0},
   { ifds::XEditEventRecieptDateTime,      BFCBO::IMMEDIATE_VALIDATION, 0},
   { ifds::SourceOfTrade,			   BFCBO::NONE,                 0},
   { ifds::ChannelOfTrade,             BFCBO::NONE,                 0},
   { ifds::Platform,				   BFCBO::NONE,                 0},
   { ifds::TimeFactor,				   BFCBO::CALCULATED_FIELD,	    0},
   { ifds::ScreenActivityType,		   BFCBO::CALCULATED_FIELD,		0},
   { ifds::PSDAdvice,                  BFCBO::NONE,                 0},
   { ifds::ServerTime,                 BFCBO::NONE,                 0},
   { ifds::SystematicGridLeftHeading,  BFCBO::NONE,					0},
   { ifds::SignatureDate,			   BFCBO::NONE,                 0},
   { ifds::YearlyAmount,               BFCBO::READ_ONLY,            0},
   { ifds::CPIRate,                    BFCBO::READ_ONLY,            0},
   { ifds::PayoutFactorRate,           BFCBO::READ_ONLY,            0},
   { ifds::AmtTypeOvrd,                BFCBO::NONE,                 0},
};

const FIELD_DEFAULT_RULE m_FieldDefaultRule[] = { 
// FieldID,					Key1,				key2,			  Key3,			 Key4,			Key5,			   MODE

{ifds::SourceOfTrade,ifds::TransType,  ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, MODE_INIT },
{ifds::ChannelOfTrade,ifds::TransType, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, MODE_INIT },
{ifds::PSDAdvice, ifds::SourceOfTrade, ifds::ChannelOfTrade, ifds::Platform, ifds::TimeFactor,  ifds::NullFieldId, MODE_INIT },

};
static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
static const int _numFieldDefaultRule = sizeof(m_FieldDefaultRule) / sizeof(FIELD_DEFAULT_RULE);

//************************************************************************
Systematic::Systematic( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent ),
_pMgmtCoOption(NULL),
_pCurrencyList(NULL),
_pGroupFundList(NULL),
_pFundMasterList(NULL),
_pFundDetailList(NULL),
_pGroupList(NULL),
_pShareholder(NULL),
_pAcqFeeInquiry(NULL),
_pAtAcctAllocationList(NULL),
_pSysAllocationList(NULL),
_pMFAccount(NULL),
_pAcctEntityXref (NULL),
binit (true),
_strRDRAdviceFlag(I_(""))
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

   //default clear new Flag
   //setObjectAsNew();

   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);

   addCrossEdit(ifds::AllocationFromFund, ifds::FundCode);
   addCrossEdit(ifds::AllocationFromFund, ifds::ClassCode);

   addCrossEdit(ifds::CompoundDate, ifds::EffectiveDate);
   addCrossEdit(ifds::CompoundDate, ifds::StopDate);

   //Used for Systematic Fee checking
   addCrossEdit(ifds::SystematicCrossField1, ifds::Fee);
   addCrossEdit(ifds::SystematicCrossField1, ifds::FlatPercent);

   addCrossEdit(ifds::PayTypeAddrCode, ifds::AddrCode);

   addCrossEdit(ifds::PayTypeBankNum,  ifds::BankAcctNum);
   addCrossEdit(ifds::PayTypeBankNum,  ifds::BankAcctType);

   addCrossEdit(ifds::SystematicCrossField2, ifds::TransType);
   addCrossEdit(ifds::SystematicCrossField2, ifds::PayType);
   addCrossEdit(ifds::SystematicCrossField2, ifds::SystematicPayType);

   // for AT
   addCrossEdit(ifds::FundToClassToAccountTo, ifds::FundToCode);
   addCrossEdit(ifds::FundToClassToAccountTo, ifds::ClassToCode);
   addCrossEdit(ifds::FundToClassToAccountTo, ifds::AccountTo);
   addCrossEdit(ifds::FundToClassToAccountTo, ifds::EffectiveDate);

   addCrossEdit(ifds::AtFundtoClasstoCrossEdit, ifds::FundToCode);
   addCrossEdit(ifds::AtFundtoClasstoCrossEdit, ifds::ClassToCode);
   addCrossEdit(ifds::AtFundtoClasstoCrossEdit, ifds::FundCode);
   addCrossEdit(ifds::AtFundtoClasstoCrossEdit, ifds::ClassCode);

   addCrossEdit(ifds::AmountTypeCrossEdit, ifds::Amount);
   addCrossEdit(ifds::AmountTypeCrossEdit, ifds::AmountType);

   addCrossEdit(ifds::BankInformation,  ifds::BankAcctNum);
   addCrossEdit(ifds::BankInformation,  ifds::BankAcctType);
   addCrossEdit(ifds::BankInformation,  ifds::TransitNo);
   addCrossEdit(ifds::BankInformation,  ifds::SwiftCode);
   addCrossEdit(ifds::BankInformation,  ifds::RefNumber);

   addCrossEdit(ifds::MonthlyIndicator, ifds::Frequency);
   addCrossEdit(ifds::MonthlyIndicator, ifds::January);
   addCrossEdit(ifds::MonthlyIndicator, ifds::February);
   addCrossEdit(ifds::MonthlyIndicator, ifds::March);
   addCrossEdit(ifds::MonthlyIndicator, ifds::April);
   addCrossEdit(ifds::MonthlyIndicator, ifds::May);
   addCrossEdit(ifds::MonthlyIndicator, ifds::June);
   addCrossEdit(ifds::MonthlyIndicator, ifds::July);
   addCrossEdit(ifds::MonthlyIndicator, ifds::August);
   addCrossEdit(ifds::MonthlyIndicator, ifds::September);
   addCrossEdit(ifds::MonthlyIndicator, ifds::October);
   addCrossEdit(ifds::MonthlyIndicator, ifds::November);
   addCrossEdit(ifds::MonthlyIndicator, ifds::December);

   addCrossEdit(ifds::VUBCrossedit, ifds::InitialAmt);
   addCrossEdit(ifds::VUBCrossedit, ifds::VUBExpectedAmt);
   //addCrossEdit(DBR::VUBCrossedit, DBR::VUBPayOption);

   addCrossEdit(ifds::ExchInFeeFlatPercent, ifds::ExchInFee);       
   addCrossEdit(ifds::ExchInFeeFlatPercent, ifds::ExchInFlatPercent);

   // WH Tax
   addCrossEdit(ifds::FedTaxRatePUD, ifds::FedTaxPUDOverride );
   addCrossEdit(ifds::FedTaxRatePUD, ifds::FedRate );

   addCrossEdit(ifds::FedTaxRateAmountPUDXEdit, ifds::FedTaxPUDOverride );
   addCrossEdit(ifds::FedTaxRateAmountPUDXEdit, ifds::FedRate );	
   addCrossEdit(ifds::FedTaxRateAmountPUDXEdit, ifds::Amount );
   addCrossEdit(ifds::FedTaxRateAmountPUDXEdit, ifds::AmountType );

   addCrossEdit(ifds::ProvTaxRatePUD, ifds::ProvTaxPUDOverride );
   addCrossEdit(ifds::ProvTaxRatePUD, ifds::ProvRate );	

   addCrossEdit(ifds::ProvTaxRateAmountPUDXEdit, ifds::ProvTaxPUDOverride );
   addCrossEdit(ifds::ProvTaxRateAmountPUDXEdit, ifds::ProvRate );	
   addCrossEdit(ifds::ProvTaxRateAmountPUDXEdit, ifds::Amount );
   addCrossEdit(ifds::ProvTaxRateAmountPUDXEdit, ifds::AmountType );

   addCrossEdit(ifds::FedProvTaxPercPUDXEdit, ifds::FedTaxPUDOverride );
   addCrossEdit(ifds::FedProvTaxPercPUDXEdit, ifds::FedRate );
   addCrossEdit(ifds::FedProvTaxPercPUDXEdit, ifds::ProvTaxPUDOverride );
   addCrossEdit(ifds::FedProvTaxPercPUDXEdit, ifds::ProvRate );

   addCrossEdit(ifds::FedProvTaxRatePUDXEdit, ifds::FedTaxPUDOverride );
   addCrossEdit(ifds::FedProvTaxRatePUDXEdit, ifds::FedRate );
   addCrossEdit(ifds::FedProvTaxRatePUDXEdit, ifds::ProvTaxPUDOverride );
   addCrossEdit(ifds::FedProvTaxRatePUDXEdit, ifds::ProvRate );
   addCrossEdit(ifds::FedProvTaxRatePUDXEdit, ifds::Amount );
   addCrossEdit(ifds::FedProvTaxRatePUDXEdit, ifds::AmountType );

//soft cap check - from side
   addCrossEdit (ifds::FromSoftCapCheck, ifds::FundCode);
   addCrossEdit (ifds::FromSoftCapCheck, ifds::ClassCode);
   addCrossEdit (ifds::FromSoftCapCheck, ifds::EffectiveDate);
   addCrossEdit (ifds::FromSoftCapCheck, ifds::StopDate);
//soft cap check - to side
   addCrossEdit (ifds::ToSoftCapCheck, ifds::FundToCode);
   addCrossEdit (ifds::ToSoftCapCheck, ifds::ClassToCode);
   addCrossEdit (ifds::ToSoftCapCheck, ifds::EffectiveDate);
   addCrossEdit (ifds::ToSoftCapCheck, ifds::StopDate);
   
 //Cross edit from PET157837 FN02 Country Schedule
   addCrossEdit (ifds::FromToFundClassAcctTo, ifds::AccountTo);
   addCrossEdit (ifds::FromToFundClassAcctTo, ifds::FundCode);
   addCrossEdit (ifds::FromToFundClassAcctTo, ifds::ClassCode);
   addCrossEdit (ifds::FromToFundClassAcctTo, ifds::FundToCode);
   addCrossEdit (ifds::FromToFundClassAcctTo, ifds::ClassToCode);

   // calculate amount cross edit:
   addCrossEdit (ifds::CalcAmountXEdit, ifds::AmountType);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::EffectiveDate);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::StopDate);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::EndOfMonth);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::January);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::February);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::March);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::April);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::May);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::June);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::July);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::August);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::September);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::October);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::November);
   addCrossEdit (ifds::CalcAmountXEdit, ifds::December);

   // fund, class, amount type:

   addCrossEdit (ifds::LGFundClassXEdit, ifds::AmountType);
   addCrossEdit (ifds::LGFundClassXEdit, ifds::FundCode);
   addCrossEdit (ifds::LGFundClassXEdit, ifds::ClassCode);

   addCrossEdit (ifds::XEditEventRecieptDateTime, ifds::EventReceiptDate); 
   addCrossEdit (ifds::XEditEventRecieptDateTime, ifds::EventReceiptTime);

	addCrossEdit(ifds::SrcOfFundSrcOfAcctXEdit, ifds::SourceOfBankAcct);
   addCrossEdit(ifds::SrcOfFundSrcOfAcctXEdit, ifds::SrcOfFund);

   _dstrFee             = NULL_STRING;
   _dstrTaxType         = NULL_STRING;
   _dstrTransType       = NULL_STRING;
   _dstrEffectiveDate   = NULL_STRING;
   _dstrAmount          = NULL_STRING;
   _dstrAmountType      = NULL_STRING;
   _dstrFundCode        = NULL_STRING;
   _dstrClassCode       = NULL_STRING;
   _dstrFundToCode      = NULL_STRING;
   _dstrClassToCode     = NULL_STRING;

   _dstrCurrency        = NULL_STRING;
   _dstrBrokerCode      = NULL_STRING;

   _dstrDefaultAcqFee   = NULL_STRING;
   _dstrFeeUpdateFlag   = NO;
   _AcctFeeWaived       = NULL_STRING;
   _dstrSysCurrency     = NULL_STRING;
   _dstrFlatPercent     = NULL_STRING;

   BFProperties *pProperties = getFieldProperties (ifds::BankAcctCurrency, BF::HOST);
   if ( NULL != pProperties )
      pProperties->getAllSubstituteValues( _dstrHostCurrencyList );
   
   setFieldReadOnly( ifds::TransNum, BF::HOST, true );
   
}

//************************************************************************
Systematic::~Systematic()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pAcqFeeInquiry )
   {
      delete _pAcqFeeInquiry;
      _pAcqFeeInquiry = NULL;
   }
}

//************************************************************************
//to see why is strKey Used !!!
SEVERITY Systematic::init( const BFDataGroupId& idDataGroup, 
                           const BFData &viewData, 
                           const BFData* sysAllocData, 
                           const BFData* pAtAllocData, 
                           const DString& strKey,
						         const DString &strPayType,
					            const DString &strAmount,
					            const DString &strAmountType)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   DString dstrFeeWaived;     
   _pErrMsgRulesList = NULL;

   _dstrPayType = strPayType;
   _dstrAwdAmount = strAmount;
   _dstrAwdAmountType = strAmountType;
   attachDataObject(const_cast<BFData&>(viewData), false, true);
   SystematicList* pSystematicList = dynamic_cast <SystematicList*> (getParent());
   _pMFAccount = pSystematicList->getMFAccount();
   MgmtCoOptions* pMgmtCoOptions = pSystematicList->getMgmtCoOptions();
   _pMFAccount->getField ( ifds::FeeWaived, dstrFeeWaived, idDataGroup );
   if( dstrFeeWaived == NO )
   {
      getWorkSession().getOption( ifds::CommissionType, _featureSplitComm, idDataGroup, false );    
      if( _featureSplitComm == COMMISSION_TYPE_TWO )
         _featureSplitComm = COMMISSION_TYPE_ZERO;     // Commission type behave the same as commtype 0
   }
   else
      _featureSplitComm = COMMISSION_TYPE_ZERO;        

   DString dstTemp;

   setFrequencySubstitution(idDataGroup);
   DString dstrTransType;
   getField( ifds::TransType, dstrTransType, idDataGroup, false);   

   if (dstrTransType.strip().upperCase() == AUTO_TRFER)
   {
      setFieldReadOnly(ifds::ExchInFee, BF::HOST, true);
      setFieldReadOnly(ifds::ExchInFlatPercent, BF::HOST, true);
      setFieldReadOnly(ifds::ExchOutFee, BF::HOST, true);
      setFieldReadOnly(ifds::ExchOutFlatPrcnt, BF::HOST, true);
      initAtAcctAlloc(idDataGroup, pAtAllocData, strKey);      
      setFieldsToReadonlyWhenForBadRecord( idDataGroup );
   }
   else           //PAC or SWP
   {
      setFieldStatus( BF::HOST, dstrTransType == SAVING_PLAN );
      if( dstrTransType == SAVING_PLAN )
      {
         setFieldReadOnly( ifds::PlanCode, idDataGroup, true );

         // disable InitialAmt and VUBPayOption after first process: strLastProcessDate != NULL_STRING 
         DString strLastProcessDate;
         getField( ifds::LastProcessDate, strLastProcessDate, idDataGroup, false );
         setFieldReadOnly( ifds::InitialAmt, idDataGroup, strLastProcessDate != NULL_STRING );
         setFieldReadOnly( ifds::VUBPayOption, idDataGroup, strLastProcessDate != NULL_STRING );
      }

      setFieldsToReadonlyWhenForBadRecord( idDataGroup );

      _pSysAllocationList = new SysAllocationList ( *this );
      _pSysAllocationList->init( idDataGroup, strKey, *sysAllocData);
      setObject( _pSysAllocationList, I_( "SysAllocationList" ), OBJ_ACTIVITY_NONE, BF::HOST );
   }

   setFieldReadOnly( ifds::SystematicPayType, idDataGroup, true );
   getSegCotClient();   

   // Initialize fundNumber 
   DString dstrFrFundNumber,dstrToFundNumber,dstrFundToCode,dstrFundToClass;

   getField( ifds::FundCode,         _dstrFundCode,       idDataGroup, false );
   getField( ifds::ClassCode,        _dstrClassCode,      idDataGroup, false );
   getField( ifds::FundToCode,       dstrFundToCode,      idDataGroup, false );
   getField( ifds::ClassToCode,      dstrFundToClass,     idDataGroup, false );

   getWorkSession().GetFundNumber( _dstrFundCode.strip().upperCase(), _dstrClassCode.strip().upperCase(), dstrFrFundNumber );
   setFieldNoValidate( ifds::FrFundNumber, dstrFrFundNumber, BF::HOST, false,true, false, false  );
   getWorkSession().GetFundNumber(  dstrFundToCode.strip().upperCase(), dstrFundToClass.strip().upperCase(), dstrToFundNumber );
   setFieldNoValidate( ifds::ToFundNumber, dstrToFundNumber, BF::HOST, false, true, false, false  );

   MFAccount* pMFAccount = NULL;

   if ( dstrTransType == AUTO_TRFER) 
   {
      DString dstrAccountNum;

      getField (ifds::AccountTo, dstrAccountNum, idDataGroup);
      getMFAccount (dstrAccountNum, idDataGroup, pMFAccount);
   } 
   else 
   {
      pMFAccount = _pMFAccount;
   }

   if (pMFAccount && pMFAccount->isAMSAccount(idDataGroup)) 
   {
      DString dstrPACSWPOverride;
      
      getWorkSession().getOption (ifds::PACSWPOverride, dstrPACSWPOverride, idDataGroup, false); 
      if (dstrPACSWPOverride == YES)  
      {
         if (dstrTransType == AUTO_TRFER) 
         {
            setFieldReadOnly ( ifds::ToFundNumber, idDataGroup, true );
            setFieldReadOnly ( ifds::FundToCode, idDataGroup, true );
            setFieldReadOnly ( ifds::ClassToCode, idDataGroup, true );
         } 
         else 
         {
            setFieldReadOnly ( ifds::FrFundNumber, idDataGroup, true );
            setFieldReadOnly ( ifds::FundCode, idDataGroup, true );
            setFieldReadOnly ( ifds::ClassCode, idDataGroup, true );
         }
         DString dstrAmount;
         getField( ifds::Amount, dstrAmount, idDataGroup );
         // To handle old PACs with Fund/Class set.
         int iNum = _pSysAllocationList->getNbrOfAllocInList ( idDataGroup );
         if (( _dstrFundCode == NULL_STRING ) && ( _dstrClassCode == NULL_STRING ) && iNum == 0)
            setupDefaultAllocationList( idDataGroup, dstrAmount, true );
      }
   }
   if (dstrTransType == AUTO_TRFER)
   {
	   //IN2844236 - Disable set up bankruptcy fund
	   if(isFieldsDisabledBaseOnRuleType(RULE_TYPE::BANKRUPTCY,idDataGroup))
	   {
		   setFieldReadOnly (ifds::Amount, idDataGroup, true );
	   }
	   else
	   {
		   DString dstrAmountType;
		   getField (ifds::AmountType, dstrAmountType, idDataGroup);
		   dstrAmountType.strip().upperCase();
		   if ( DSTCommonFunctions::codeInList ( dstrAmountType, I_("F,T,M,X,Y") ) )
		   {
			   // setFieldNoValidate (ifds::Amount, I_("0") , idDataGroup, true, false, true, false);
			   setFieldReadOnly (ifds::Amount, idDataGroup, true );
		   }
		   else
		   {
			   setFieldReadOnly (ifds::Amount, idDataGroup, false );
		   }
	   }
   }

   setValidFlag( ifds::FundToClassToAccountTo, idDataGroup, false );
   setValidFlag( ifds::EffectiveDate, idDataGroup, false );

//   setFieldReadOnly( ifds::StopReasonPAC, idDataGroup, true );
   //set Source of Fund substition set
   payTypeRelatedChanges(idDataGroup);//P0186486_FN15_The Source of Funds


   DString dstNFConfBnkDetl;
   getWorkSession().getOption( ifds::NFConfBnkDetl, dstNFConfBnkDetl, BF::HOST, false );    
   dstNFConfBnkDetl.strip();

   DString dstrAcctNonFinConfirm, dstrOPCNonFinConfDefPAC;
   MFAccount* _pMFAccount = pSystematicList->getMFAccount();
   _pMFAccount->getField ( ifds::NonFinConfirm, dstrAcctNonFinConfirm, BF::HOST);
   dstrAcctNonFinConfirm.strip();

   getWorkSession().getOption(ifds::OPCNonFinConfDefPAC, dstrOPCNonFinConfDefPAC, BF::HOST, false);
   dstrOPCNonFinConfDefPAC.stripAll().upperCase();

   if (dstrOPCNonFinConfDefPAC == YES)
   {
       if (dstrTransType == PAC)
           setFieldReadOnly(ifds::NonFinConfirms, BF::HOST, false);
       else
           setFieldReadOnly (ifds::NonFinConfirms, BF::HOST, true);
   }
   else if (dstNFConfBnkDetl == I_("N") || dstrAcctNonFinConfirm == I_("N")) // OPCNonFinConfDefPAC = NO
   {
       setFieldReadOnly (ifds::NonFinConfirms, BF::HOST, true );
   }

   DString dstrVerifyStat;
   getField(ifds::VerifyStat, dstrVerifyStat, idDataGroup, false); // 02 = Unverified
   dstrVerifyStat.strip();

   DString dstrModUser;
   getField(ifds::ModUser, dstrModUser, idDataGroup, false); 
   dstrModUser.strip();

   DString dstrUsername;
   getField(ifds::Username, dstrUsername, idDataGroup, false); 
   dstrUsername.strip();

   DString dstrCurrentUser = dynamic_cast<const DSTCSecurity *> (getWorkSession ().getSecurity(DSTCHost::getPrimaryHost()))->getUserId();        

   bool bVerificationEnabled = false;
 
   getWorkSession().isVerificationEnabled (idDataGroup, VERIFY_CATEGORY_SYSTEMATIC, VERIFY_LEVEL_ACCOUNT, bVerificationEnabled);

   if(bVerificationEnabled && (dstrModUser != I_("") && dstrCurrentUser != dstrModUser || dstrModUser == I_("") && dstrCurrentUser != dstrUsername ) && dstrVerifyStat == I_("02"))
   {
      setFieldReadOnly (ifds::VerifyStat, idDataGroup, false );
   }
   else
   {
      setFieldReadOnly (ifds::VerifyStat, idDataGroup, true );
   }
  
   getField( ifds::RDRAdvice, _strRDRAdviceFlag, idDataGroup, false );
  
   DString strLastProcessDate;
   getField( ifds::LastProcessDate, strLastProcessDate, idDataGroup, false );
   setFieldReadOnly( ifds::RDRAdvice, idDataGroup, (strLastProcessDate != NULL_STRING || _strRDRAdviceFlag == I_("00")) );
   
   if( _strRDRAdviceFlag != I_("00") )
   {
	   loadRDRAdviceSubstList(idDataGroup);
   }
   bool bEventReceiptDateTimeAppl   = (bIsEventReceiptDateTimeAppl(idDataGroup)); //&& (dstrVerifyStat != VERIFIED);
   setFieldReadOnly(ifds::EventReceiptDate,idDataGroup, !bEventReceiptDateTimeAppl);
   setFieldReadOnly(ifds::EventReceiptTime,idDataGroup, !bEventReceiptDateTimeAppl);
   //mask the time returned by the view using ##:##:##
   DString dstrValue;
   getField (ifds::EventReceiptTime, dstrValue, BF::HOST, false);
   dstrValue.stripAll();
   if( !dstrValue.empty() )
      formatStringUsingMask(dstrValue, I_("##:##:##"));
   setFieldNoValidate(ifds::EventReceiptTime, dstrValue, BF::HOST, false, false, false);
	setFieldReadOnly(ifds::Platform, BF::HOST, true);
	DString dstrPSDAdvice;
	getWorkSession ().getOption (ifds::PSDAdvice, dstrPSDAdvice, BF::HOST,  false);
	if( NO == dstrPSDAdvice.stripAll())	
	{
	 addBlankToSubSet( ifds::SourceOfTrade,  BF::HOST );
	 addBlankToSubSet( ifds::ChannelOfTrade, BF::HOST);
	}
	DString dstrPlatform, dstrScreenActivityType;
	getField(ifds::Platform, dstrPlatform, BF::HOST);
	setFieldReadOnly(ifds::SourceOfTrade, BF::HOST, PLATFORM::DESKTOP != dstrPlatform || NULL_STRING != strLastProcessDate );
	setFieldReadOnly(ifds::ChannelOfTrade,BF::HOST, PLATFORM::DESKTOP != dstrPlatform || NULL_STRING != strLastProcessDate );

	if(dstrPlatform.empty())
	   setFieldNoValidate(ifds::Platform, PLATFORM::DESKTOP, BF::HOST, false, true, true);

	setFieldReadOnly(ifds::PSDAdvice, idDataGroup, NO == dstrPSDAdvice.stripAll() || NULL_STRING != strLastProcessDate );
    dstrScreenActivityType = dstrTransType == PAC ? PAC : NULL_STRING;
    setFieldNoValidate(ifds::ScreenActivityType, PAC, idDataGroup, false, false, true);
	setFieldReadOnly(ifds::SignatureDate, idDataGroup, NULL_STRING != strLastProcessDate); 

    if (isSWPPortfolioPayoutPlan(idDataGroup))
        setFieldsPropSWPPortfolioPayout(idDataGroup);

	DString dstrAmountType;
	getField( ifds::AmountType, dstrAmountType, idDataGroup );
	dstrAmountType.strip().upperCase();
	bool bIsRDSPAccount = _pMFAccount->isRDSPAccount(idDataGroup);

	if (bIsRDSPAccount && dstrTransType == SWP && DSTCommonFunctions::codeInList(dstrAmountType, I_("A,D,N,O")))
	{		
		setFieldReadOnly (ifds::Amount, idDataGroup, true);
		setFieldReadOnly (ifds::GrossOrNet, idDataGroup, true);
	}

	return(InitFieldsNotInInquiry( BF::HOST ));
}

//************************************************************************
void Systematic::setFieldsPropSWPPortfolioPayout(const BFDataGroupId &idDataGroup)
{
    for (unsigned int i = 0; i < NUM_FIELDS; i++)
    {
        BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo[i];
        const BFFieldId &fieldId = fieldInfo.getFieldId();

        setFieldReadOnly(fieldId, idDataGroup, true);
    }

    setFieldReadOnly(ifds::SystematicPayType, idDataGroup, false);
    setFieldReadOnly(ifds::AddrCode, idDataGroup, false);

    setFieldSubstituteValues(ifds::SystematicPayType, idDataGroup, ifds::SystematicPaySWP);
}

//************************************************************************
void Systematic::getParameter(DString& strAcct,DString& strFund,DString& strClass,DString& strAmount)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getParameter") );
   getField(ifds::FundToCode,strFund,BF::HOST,false);
   strFund.strip();
   getField(ifds::AccountTo,strAcct,BF::HOST,true);
   strAcct.strip().stripLeading(I_('0'));

   getField(ifds::ClassToCode,strClass,BF::HOST,false);
   strClass.strip();
   getField(ifds::Amount,strAmount,BF::HOST,false);
   strAmount.strip();

}

//************************************************************************
// initialize account level automatic transfer allocation
//
SEVERITY Systematic::initAtAcctAlloc(const BFDataGroupId& idDataGroup, 
                                     const BFData* pAtAllocData, const DString& strKey)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initAtAcctAlloc" ) );

   _pAtAcctAllocationList = new AutoAcctTransAllocationList( *this );
   _pAtAcctAllocationList->setSystematicPtr(this);

   DString dstrAccount,dstrFundTo,dstrClassTo;
   getField( ifds::AccountTo,dstrAccount,BF::HOST, true );
   getField( ifds::FundToCode,dstrFundTo,BF::HOST, false );
   getField( ifds::ClassToCode,dstrClassTo,BF::HOST, false );
   dstrClassTo.strip();
   dstrFundTo.strip();
   dstrAccount.strip().stripLeading(I_CHAR( '0' ));
   bool _bAcctFlag = true;
   if( (dstrClassTo.empty()) || (dstrFundTo.empty()) || (dstrAccount.empty()) )
      _bAcctFlag = false;

   _pAtAcctAllocationList->init( idDataGroup, strKey, *pAtAllocData,_bAcctFlag);

   setObject( _pAtAcctAllocationList,AUTO_ACCT_TRANS_ALLOCATION_LIST, OBJ_ACTIVITY_NONE, BF::HOST );
   getSegCotClient();

   return(InitFieldsNotInInquiry( BF::HOST ));
}

//************************************************************************
SEVERITY Systematic::calculateAmount (const DString &dstrAmountType, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "calculateAmount" ) );

	SWPAmountCalculation *pSWPAmountCalculation;
		
	DString dstrAccountNum, dstrEndOfMonth;
	DString dstEffectiveDate, dstrStopDate;

	getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false );
	getField(ifds::EffectiveDate, dstEffectiveDate, idDataGroup, false );
	getField(ifds::StopDate, dstrStopDate, idDataGroup, false );
	getField(ifds::EndOfMonth, dstrEndOfMonth, idDataGroup, false );

	DString dstrJan, dstrFeb, dstrMar, dstrApr, dstrMay, dstrJun;
	DString dstrJul, dstrAug, dstrSep, dstrOct, dstrNov, dstrDec;
	DString dstrFrequency, dstrDayOfWeek;
   
	getField(ifds::January, dstrJan, idDataGroup, false );
	getField(ifds::February, dstrFeb, idDataGroup, false );
	getField(ifds::March, dstrMar, idDataGroup, false );
	getField(ifds::April, dstrApr, idDataGroup, false );
	getField(ifds::May, dstrMay, idDataGroup, false );
	getField(ifds::June, dstrJun, idDataGroup, false );
	getField(ifds::July, dstrJul, idDataGroup, false );
	getField(ifds::August, dstrAug, idDataGroup, false );
	getField(ifds::September, dstrSep, idDataGroup, false );
	getField(ifds::October, dstrOct, idDataGroup, false );
	getField(ifds::November, dstrNov, idDataGroup, false );
	getField(ifds::December, dstrDec, idDataGroup, false );
	getField(ifds::Frequency, dstrFrequency, idDataGroup, false );
	getField(ifds::DayOfWeek, dstrDayOfWeek, idDataGroup, false );
   
	dstrJan.strip().upperCase();
	dstrFeb.strip().upperCase();
	dstrMar.strip().upperCase();
	dstrApr.strip().upperCase();
	dstrMay.strip().upperCase();
	dstrJun.strip().upperCase();
	dstrJul.strip().upperCase();
	dstrAug.strip().upperCase();
	dstrSep.strip().upperCase();
	dstrOct.strip().upperCase();
	dstrNov.strip().upperCase();
	dstrDec.strip().upperCase();
	dstrAccountNum.strip();
	dstrEndOfMonth.strip().upperCase();
	dstrFrequency.strip();
	dstrDayOfWeek.strip();


	if (!dstrAccountNum.empty())
	{
		DString strKey;

		SWPAmountCalculation::buildKey (dstrAccountNum,
										dstrAmountType,    
										dstEffectiveDate,    
										dstrStopDate, 
										dstrEndOfMonth,
										dstrJan,
										dstrFeb,        
										dstrMar,
										dstrApr,       
										dstrMay,
										dstrJun,       
										dstrJul,
										dstrAug,
  										dstrSep,
  										dstrOct,
  										dstrNov,
  										dstrDec,
										dstrFrequency,
										dstrDayOfWeek,
										strKey);
		pSWPAmountCalculation = dynamic_cast<SWPAmountCalculation *> (BFCBO::getObject (strKey, idDataGroup));

		if (!pSWPAmountCalculation)
		{
			pSWPAmountCalculation = new SWPAmountCalculation (*this);
			
			if (pSWPAmountCalculation->init (dstrAccountNum,
											dstrAmountType,    
											dstEffectiveDate,    
											dstrStopDate, 
											dstrEndOfMonth,
											dstrJan,
											dstrFeb,        
											dstrMar,
											dstrApr,       
											dstrMay,
											dstrJun,       
											dstrJul,
											dstrAug,
  											dstrSep,
  											dstrOct,
  											dstrNov,
  											dstrDec,
											dstrFrequency,
											dstrDayOfWeek) <= WARNING)
			{
				setObject ( pSWPAmountCalculation,  strKey, OBJ_ACTIVITY_NONE,  idDataGroup);
			}
			else
			{
				delete pSWPAmountCalculation;
				pSWPAmountCalculation = NULL;
			}
		}
	}

	if (pSWPAmountCalculation)
	{
		DString dstrSWPCalculatedAmount;

		pSWPAmountCalculation->getField (ifds::SWPCalculatedAmount, dstrSWPCalculatedAmount, idDataGroup, false);

        setFieldNoValidate (ifds::Amount, dstrSWPCalculatedAmount, idDataGroup, false, true, true, false);
	}
	
	return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY Systematic::getGMWBValidationObject(GMWBValidation*& pGMWBValidation, const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getGMWBValidationObject" ) );

	DString dstrGWLWAAvailOptions;
	DString dstrAccountNum;
	DString dstrValidateType = I_("SWP");
	DString dstrEffectiveDate;
	DString dstrStopDate;
	DString dstrTransNum;
	DString dstrFundCode (fundCode);
	DString dstrClassCode (classCode);
	DString dstrAmountType;
	DString dstrRecId;
	DString dstrRunMode = isNew () ? I_("A") : I_("M");

	//validate only if GWLWAAvailOptions is not empty
	_pMFAccount->getField ( ifds::GWLWAAvailOptions, dstrGWLWAAvailOptions, idDataGroup, false );  
	
	dstrGWLWAAvailOptions.strip ();

	if (dstrGWLWAAvailOptions.empty ())
		return GETCURRENTHIGHESTSEVERITY();

	getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false );
	getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
	getField (ifds::StopDate, dstrStopDate, idDataGroup, false );
	getField (ifds::TransNum, dstrTransNum, idDataGroup, false );
	getField (ifds::AmountType, dstrAmountType, idDataGroup, false );
	getField (ifds::PACSWPId, dstrRecId, idDataGroup, false );
	
	dstrAccountNum.strip ();
	dstrValidateType.strip ();
	dstrEffectiveDate.strip ();
	dstrStopDate.strip ();
	dstrTransNum.strip ();
	dstrFundCode.strip ();
	dstrClassCode.strip ();
	dstrAmountType.strip ();
	dstrRecId.strip ();

	if (!dstrFundCode.empty () && !dstrClassCode.empty ())
	{
		DString strKey;

		GMWBValidation::buildKey (dstrAccountNum,
								  dstrValidateType,
								  dstrTransNum,
								  dstrFundCode,
								  dstrClassCode,
								  dstrEffectiveDate,
								  dstrStopDate,
								  dstrAmountType,
								  dstrRecId,
								  dstrRunMode,
								  strKey);

		pGMWBValidation = dynamic_cast<GMWBValidation *> (BFCBO::getObject (strKey, idDataGroup));

		if (!pGMWBValidation)
		{
			pGMWBValidation = new GMWBValidation (*this);
			
			if (pGMWBValidation->init (	dstrAccountNum,
										dstrValidateType,
										dstrTransNum,
										dstrFundCode,
										dstrClassCode,
										dstrEffectiveDate,
										dstrStopDate,
										dstrAmountType,
										dstrRecId,
										dstrRunMode) <= WARNING)
			{
				setObject (pGMWBValidation,  strKey, OBJ_ACTIVITY_NONE,  idDataGroup);
			}
			else
			{
				delete pGMWBValidation;
				pGMWBValidation = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************
SEVERITY Systematic::validateGMWB (const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGMWB" ) );

	GMWBValidation *pGMWBValidation = NULL;
   
   getGMWBValidationObject(pGMWBValidation, fundCode, classCode, idDataGroup);

	if (pGMWBValidation)
	{
		pGMWBValidation-> validateGMWB (fundCode, classCode, idDataGroup);
	}
	
	return GETCURRENTHIGHESTSEVERITY();
}


//*********************************************************************************
void Systematic::init2( const BFDataGroupId& idDataGroup, SystematicList *pList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   /* binit = true;    */

   _pErrMsgRulesList = NULL;
   _pList = pList;

   _pMgmtCoOption = _pList->getMgmtCoOptions();
   _pGroupFundList = _pList->getGroupFundList();
   _pCurrencyList = _pList->getCurrencyList();

   _pMFAccount = _pList->getMFAccount();
   _pFundMasterList = _pList->getFundMasterList();
   _pFundDetailList = _pList->getFundDetailList();
   _pGroupList = _pList->getGroupList();
   _pShareholder = _pList->getShareholder();
   _pAcctEntityXref = NULL;

   _pMgmtCoOption->getField( ifds::BankLayout,   _featureBankLayout,   idDataGroup ,false );
   _pMgmtCoOption->getField( ifds::MultiCurrency, _dstrmultiCurrency, BF::HOST, false );
   _pMgmtCoOption->getField( ifds::SysCurrency,   _dstrSysCurrency, idDataGroup ,false );

   _featureBankLayout.strip().upperCase();
   _dstrmultiCurrency.strip().upperCase();
   _dstrSysCurrency.strip().upperCase();

   _dstrDefaultAcqFee   = I_("-1");

   //remember the original the Fee request paramenters
   getField( ifds::Fee, _dstrFee, idDataGroup, false );
	getField( ifds::FlatPercent, _dstrFlatPercent, idDataGroup, false);

   DString   dstrAccountNum;
   _pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST );   

   setFieldNoValidate( ifds::AccountNum, dstrAccountNum, BF::HOST );  
   _pMFAccount->getField( ifds::TaxType,   _dstrTaxType, idDataGroup, false );
   _dstrTaxType.strip().upperCase();
   _pMFAccount->getField(ifds::BrokerCode, _dstrBrokerCode,idDataGroup, false);
   _pMFAccount->getField(ifds::FeeWaived, _AcctFeeWaived, idDataGroup, false);
   if( _AcctFeeWaived == NO )
   {
      getWorkSession().getOption( ifds::CommissionType, _featureSplitComm, idDataGroup, false );  
      // Commission type behave the same as commtype 0
      if( _featureSplitComm == COMMISSION_TYPE_TWO )
         _featureSplitComm = COMMISSION_TYPE_ZERO;
   }
   else
      _featureSplitComm = COMMISSION_TYPE_ZERO;  

   initDisableAcqFee(idDataGroup);

   getField( ifds::TransType,        _dstrTransType,      idDataGroup, false );
   getField( ifds::EffectiveDate,    _dstrEffectiveDate,  idDataGroup, false );
   getField( ifds::Amount,           _dstrAmount,         idDataGroup, false );
   getField( ifds::AmountType,       _dstrAmountType,     idDataGroup, false );
   getField( ifds::BankAcctCurrency, _dstrCurrency,       idDataGroup, false );

   _dstrTransType.strip().upperCase();
   _dstrCurrency.strip().upperCase();

   getSegCotClient();

   setFieldReadOnly( ifds::BankAcctCurrency, idDataGroup, (_dstrmultiCurrency.strip() == NO) );

   if( _dstrTransType != AUTO_TRFER && _dstrmultiCurrency == NO )
   {
      // assign fund currency, this is to fix a problem in the back end:
      // systematic added through the backend may leave BankAcctCurrency blank
      DString tmp, fundCode, classCode;
      getField( ifds::PayType, tmp, idDataGroup, false );

      if( tmp == EFT_PAY_TYPE )
      {
         getField( ifds::BankAcctCurrency, tmp, idDataGroup, false );

         if( tmp.strip() == NULL_STRING )
         {
            //assign fund currency
            getField( ifds::FundCode, fundCode, idDataGroup, false );
            getField( ifds::ClassCode, classCode, idDataGroup, false );

            if( fundCode.strip() == NULL_STRING )
            {
               //assert( _pSysAllocationList ); 
			   if ( NULL != _pSysAllocationList )	
			   {               
					BFObjIter iter( *_pSysAllocationList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
					iter.begin();
					//assert (!iter.end());

					if ( !iter.end() )
					{
						BFAbstractCBO *pBFCBO = iter.getObject();
						if ( NULL != pBFCBO )
						{
							pBFCBO->getField( ifds::FundCode, fundCode, idDataGroup, false );
							pBFCBO->getField( ifds::ClassCode, classCode, idDataGroup, false );
						}
					}
			   }
            }

            CurrencyClass::getFundCurrency(getWorkSession(), fundCode, classCode, tmp);
            tmp.strip().upperCase();
            setFieldNoValidate( ifds::BankAcctCurrency, tmp, idDataGroup, false );
            setUpdatedFlag( ifds::BankAcctCurrency, idDataGroup, false );

         }
      }
   }  // if single currency and not automatic transfer


   setAmtTypeSubList ( BF::HOST ) ;

   setFieldReadOnly( ifds::FeeCurrency, idDataGroup, true );
   setFieldReadOnly( ifds::AdminFeeCurr, idDataGroup, true );

   if( _dstrTransType != AUTO_TRFER )
   {
      DString dstrIndexExist;
      getField( ifds::IndexExist, dstrIndexExist, idDataGroup, false);   
      if( dstrIndexExist == YES )
      {
         SysIndexList *pSysIndexList;
         getSystematicIndexList( idDataGroup, pSysIndexList );
         if( pSysIndexList )
         {
            bool bActiveIndex = pSysIndexList->activeIndex( idDataGroup );
            lockFrequency ( idDataGroup, bActiveIndex );   
         }
      }
   }

   setFieldReadOnly(ifds::ExchInFee, BF::HOST, true);
   setFieldReadOnly(ifds::ExchInFlatPercent, BF::HOST, true);
   setFieldReadOnly(ifds::ExchOutFee, BF::HOST, true);
   setFieldReadOnly(ifds::ExchOutFlatPrcnt, BF::HOST, true);
   setValidFlag(ifds::SystematicCrossField2,  idDataGroup, false);
   /* binit = false; */
   //initCapped ( idDataGroup );

   systematicPayTypeRelatedChangesForFileProcessor( idDataGroup );   

   transTypeWHTaxRelatedChanges( idDataGroup );	
   DString dstrFedTaxPUDOverride,dstrProvTaxPUDOverride;
   bool bTaxPermit = getWorkSession().hasUpdatePermission( UAF::SWP_TAX_OVERRIDE );
   getField( ifds::FedTaxPUDOverride,  dstrFedTaxPUDOverride,  idDataGroup );
   getField( ifds::ProvTaxPUDOverride, dstrProvTaxPUDOverride, idDataGroup );
   setFieldReadOnly( ifds::FedTaxPUDOverride,  idDataGroup, !bTaxPermit );			
   setFieldReadOnly( ifds::ProvTaxPUDOverride,  idDataGroup,!bTaxPermit );			

   // If Federal Override is No, then don't allow any entry for Rate
   setFieldReadOnly( ifds::FedRate,  idDataGroup, I_( "0" ) == dstrFedTaxPUDOverride.strip() || !bTaxPermit );			
   // If Provincial Override is No, then don't allow any entry for Rate
   setFieldReadOnly( ifds::ProvRate, idDataGroup, I_( "0" ) == dstrProvTaxPUDOverride.strip() || !bTaxPermit );	

   setValidFlag( ifds::FundToClassToAccountTo, idDataGroup, false );
   setValidFlag( ifds::EffectiveDate, idDataGroup, false );

//   setFieldReadOnly( ifds::StopReasonPAC, idDataGroup, true );
   disableFieldsBaseOnRuleType( RULE_TYPE::BANKRUPTCY, idDataGroup);

   
   DString dstrStopDate;
   getField(ifds::StopDate, dstrStopDate, idDataGroup, false);
   DString dstr12319999Date;
   DSTCommonFunctions::getFormat12319999Date(dstr12319999Date);
//   setFieldReadOnly(ifds::StopReasonPAC, idDataGroup, dstrStopDate == dstr12319999Date);
   if(!isNew())
   {
      setSettleCurrency( idDataGroup );
   }
   binit = false;
}

//************************************************************
SEVERITY Systematic::initNew( const BFDataGroupId& idDataGroup,
							  const DString &strPayType,
							  const DString &strAmount,
							  const DString &strAmountType)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   _dstrPayType = strPayType;
   _dstrAwdAmount = strAmount;
   _dstrAwdAmountType = strAmountType;

   _pErrMsgRulesList = NULL;
   _pSysAllocationList = new SysAllocationList ( *this );
   _pSysAllocationList->initNew( idDataGroup );
   setObject( _pSysAllocationList, I_( "SysAllocationList" ), OBJ_ACTIVITY_NONE, BF::HOST );

   //automatic transfer
   _pAtAcctAllocationList =  new AutoAcctTransAllocationList ( *this );
   _pAtAcctAllocationList->setSystematicPtr(this);
   _pAtAcctAllocationList->initNew(idDataGroup);
   setObject( _pAtAcctAllocationList, AUTO_ACCT_TRANS_ALLOCATION_LIST, OBJ_ACTIVITY_NONE, BF::HOST );

   setObjectAsNew(true);
   getSegCotClient();

   // initialization since dictionary initialize it as No and this field is used by other CBO
   setFieldNoValidate( ifds::ModPerm, YES, idDataGroup, false );
   setFieldNoValidate( ifds::ModPerm, YES, BF::HOST, false );

   setValidFlag( ifds::FundToClassToAccountTo, idDataGroup, false );
   setValidFlag( ifds::EffectiveDate, idDataGroup, false );

//   setFieldReadOnly( ifds::StopReasonPAC, idDataGroup, true );

   DString dstrAcctNonFinConfirm;
   
   SystematicList* pSystematicList = (SystematicList*) getParent();
   MFAccount* _pMFAccount = pSystematicList->getMFAccount();
   _pMFAccount->getField ( ifds::NonFinConfirm, dstrAcctNonFinConfirm, BF::HOST);
   dstrAcctNonFinConfirm.strip();

   DString dstrCurrentUser = dynamic_cast<const DSTCSecurity *> (getWorkSession ().getSecurity(DSTCHost::getPrimaryHost()))->getUserId();        

   DString dstNFConfBnkDetl;
   getWorkSession().getOption( ifds::NFConfBnkDetl, dstNFConfBnkDetl, BF::HOST, false );    
   dstNFConfBnkDetl.strip();

   if(dstNFConfBnkDetl == I_("N") || dstrAcctNonFinConfirm == I_("N"))
   {
		setField(ifds::NonFinConfirms, NF_SUPPRESS, idDataGroup, false); // 01 = supressed
		setFieldReadOnly (ifds::NonFinConfirms, idDataGroup, true );
   }
   else
   {
		setField(ifds::NonFinConfirms, I_(""), idDataGroup, false);
		setFieldRequired(ifds::NonFinConfirms, idDataGroup, true);
   }

   bool bVerificationEnabled = false;
 
   getWorkSession().isVerificationEnabled (idDataGroup, VERIFY_CATEGORY_SYSTEMATIC, VERIFY_LEVEL_ACCOUNT, bVerificationEnabled);
	
   if(  bVerificationEnabled )
   {
		setField(ifds::VerifyStat, I_("02"), idDataGroup, false); // 02 = Unverified
   }
   else
   {
		setField(ifds::VerifyStat, I_("01"), idDataGroup, false); // 01 = Verified
   }
   setFieldReadOnly (ifds::VerifyStat, idDataGroup, true );

	setField(ifds::StopReasonPAC, I_("00"), idDataGroup, false); // 02 = N/A
   
   setFieldNoValidate (ifds::RDRAdvice, I_("00"), idDataGroup, false); 
   setFieldReadOnly (ifds::RDRAdvice, idDataGroup, true);

   return(InitFieldsNotInInquiry( idDataGroup ));
}

//************************************************************
bool Systematic::setDisableAcqFee(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDisableAcqFee" ));

   if( _AcctFeeWaived == YES || _featureSplitComm != COMMISSION_TYPE_ZERO ) return(true);  // set read only already done by init2

   bool bDisable = false;

   DString dstrTransType, dstrFee;
   getField( ifds::TransType, dstrTransType, idDataGroup, false );
   dstrTransType.strip().upperCase();

   getField( ifds::Fee, dstrFee, idDataGroup, false );
   dstrFee.stripAll(I_(','));
   double dFee = DSTCommonFunctions::convertToDouble(dstrFee);

   DString dstrTemp;
   DString dstrFundCode, dstrClassCode;

   if( dstrTransType == AUTO_TRFER )
   {
      getField(ifds::FundToCode, dstrFundCode,  idDataGroup, false);
      getField(ifds::ClassToCode,dstrClassCode, idDataGroup, false);
   }
   else
   {
      getField(ifds::FundCode, dstrFundCode,  idDataGroup, false);
      getField(ifds::ClassCode,dstrClassCode, idDataGroup, false);
   }

   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   DString dstrAllocAllow;
   _pMgmtCoOption->getField( ifds::InvAdvice, dstrAllocAllow, idDataGroup, false );

   if( dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING )
   {
      _pMgmtCoOption->getField( ifds::DisableFee4Alloc, dstrTemp, idDataGroup, false );
      if( dstrTemp.strip().upperCase() == YES && dstrAllocAllow.strip().upperCase() == YES )
         bDisable = true;
   }
   else
   {
      if( dstrFundCode != NULL_STRING && dstrClassCode != NULL_STRING )
      {
         if( _pFundDetailList && dstrTransType != AUTO_TRFER )
         {
            DString dstrLoadType;
            _pFundDetailList->getField ( dstrFundCode, dstrClassCode, ifds::LoadType, dstrLoadType, BF::HOST, false );

            if( dstrLoadType.strip().upperCase() == I_("BEL") )
            {
               //for PAC/SWP associated with BEL funds, acquistion fees are zero, no need to apply related changes
               setFieldNoValidate (ifds::FlatPercent, I_("N"), idDataGroup, false, true, true, false);     //Percent
               setFieldNoValidate (ifds::Fee, I_("0.00"), idDataGroup, false, true, true, false);           //set to zero
               bDisable = true;
            }
         }
      }

      if( dstrTransType == AUTO_TRFER )
      {
         // more logic to be implement 	
			DString dstrATFeeApply;
			getWorkSession().getOption2( ifds::ATFeeApply, dstrATFeeApply, idDataGroup, false );
			if ( I_( "N" ) == dstrATFeeApply.stripAll() )
			{
				bDisable = true;		
			}			
      }
   }

   if( bDisable )
   {
      setFieldReadOnly( ifds::Fee,         idDataGroup, true );
      setFieldReadOnly( ifds::FlatPercent, idDataGroup, true );
      _dstrDefaultAcqFee  = NULL_STRING;
      _dstrFeeDisableFlag = YES;
      if( dFee != 0 )
         setFieldNoValidate(ifds::Fee, I_("0"), idDataGroup);
   }
   else
   {
      _dstrFeeDisableFlag = NO;

      if (!isSWPPortfolioPayoutPlan(idDataGroup))
      {
          setFieldReadOnly( ifds::Fee,         idDataGroup, false );
          setFieldReadOnly( ifds::FlatPercent, idDataGroup, false );
      }

      setValidFlag(ifds::Fee, idDataGroup, false);
   }


   if( dstrFundCode != NULL_STRING && dstrClassCode != NULL_STRING && _pFundDetailList )
   {
      DString dstrFundCurrency;
      _pFundDetailList->getField ( dstrFundCode, dstrClassCode, ifds::Currency, dstrFundCurrency, BF::HOST, false );

      setFieldNoValidate( ifds::FeeCurrency, dstrFundCurrency, idDataGroup, false, true, true, false );
      setFieldNoValidate( ifds::AdminFeeCurr, dstrFundCurrency, idDataGroup, false, true, true, false );
   }

   return(bDisable);
}


//************************************************************
bool Systematic::initDisableAcqFee(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDisableAcqFee" ) );

   if( _featureSplitComm != COMMISSION_TYPE_ZERO )
   {
      processSplitCommOption( idDataGroup );
      return(true);
   }

   bool bDisable = false;

   DString dstrFee,dstrModPerm,dstrStatusCode;

   getField( ifds::Fee, dstrFee, idDataGroup, false );
   getField( ifds::ModPerm, dstrModPerm, idDataGroup, false );
   getField( ifds::StatusCode, dstrStatusCode, idDataGroup, false );

   dstrFee.stripAll(I_(','));
   double dFee = DSTCommonFunctions::convertToDouble(dstrFee);

   if ( dstrModPerm.strip().upperCase() == NO || dstrStatusCode.strip().upperCase() == NO )
   {
      setFieldReadOnly( ifds::Fee,         idDataGroup, true );
      setFieldReadOnly( ifds::FlatPercent, idDataGroup, true );
      _dstrDefaultAcqFee  = NULL_STRING;
      _dstrFeeDisableFlag = YES;
      bDisable = true;
   }
   else if( _AcctFeeWaived == YES )
   {
      setFieldReadOnly( ifds::Fee,         idDataGroup, true );
      setFieldReadOnly( ifds::FlatPercent, idDataGroup, true );
      _dstrDefaultAcqFee  = NULL_STRING;
      _dstrFeeDisableFlag = YES;
      if( dFee != 0 )
         setFieldNoValidate(ifds::Fee, I_("0"), idDataGroup);
   }
   else
   {
      setDisableAcqFee ( idDataGroup );
   }

   return(bDisable);
}

//************************************************************

SEVERITY Systematic::requestAcqFeeInquiry(const BFDataGroupId& idDataGroup)
{
   if( _AcctFeeWaived == YES || _featureSplitComm != COMMISSION_TYPE_ZERO )
      return(NO_CONDITION);

   DString dstrTaxType, dstrFundCode, dstrClassCode, dstrFundCurrency, dstrBrokerCode, dstrFundToCode, dstrClassToCode, dstrToAccount, dstrToAcctTaxType ;
   DString dstrTransType, dstrEffectiveDate, dstrAmount, dstrAmountType, dstrCurrency, dstrFee, dstrFlatPercent, dstrAccountNum;

   getField( ifds::TransType, dstrTransType, idDataGroup, false );
   getField( ifds::FundToCode, dstrFundToCode, idDataGroup, false );
   getField( ifds::ClassToCode, dstrClassToCode, idDataGroup, false );
   getField( ifds::FundCode, dstrFundCode, idDataGroup, false );
   getField( ifds::ClassCode, dstrClassCode, idDataGroup, false );

   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   dstrFundToCode.strip().upperCase();
   dstrClassToCode.strip().upperCase();
   dstrTransType.strip().upperCase();

   if( dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING )
      return(NO_CONDITION);

   if( dstrTransType == AUTO_TRFER && ( dstrFundToCode == NULL_STRING || dstrClassToCode == NULL_STRING ) )
      return(NO_CONDITION);

   getField( ifds::Fee, dstrFee, idDataGroup, false );
	getField( ifds::FlatPercent, dstrFlatPercent, idDataGroup, false );
   _pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
   _pMFAccount->getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup, false );
   dstrTaxType.strip().upperCase();

   getField( ifds::EffectiveDate,    dstrEffectiveDate,  idDataGroup, false );
   getField( ifds::Amount,           dstrAmount,         idDataGroup, false );
   getField( ifds::AmountType,       dstrAmountType,     idDataGroup, false );
   getField( ifds::BankAcctCurrency, dstrCurrency,       idDataGroup, false );
   dstrCurrency.strip().upperCase();
   dstrTransType.strip().upperCase();

   CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrFundCurrency);

   double dec_Amount_input = DSTCommonFunctions::convertToDouble( dstrAmount );
   double dec_Amount_Default = DSTCommonFunctions::convertToDouble( _dstrAmount );

   I_CHAR *stopstring;


   bool bRequest = false;
   //_dstrFeeUpdateFlag = YES;
   if( dstrTaxType         == _dstrTaxType         &&
       dstrTransType       == _dstrTransType       &&
       dstrEffectiveDate   == _dstrEffectiveDate   &&
       dec_Amount_input    == dec_Amount_Default   &&
       dstrAmountType      == _dstrAmountType      &&
       dstrFundCode        == _dstrFundCode        &&
       dstrClassCode       == _dstrClassCode       &&
       dstrFundToCode      == _dstrFundToCode      &&
       dstrClassToCode     == _dstrClassToCode     &&
       dstrCurrency        == _dstrCurrency        &&
       dstrBrokerCode      == _dstrBrokerCode      &&
		 dstrFlatPercent     == _dstrFlatPercent     &&
		 dstrFee					== _dstrFee	 )
   {
      /*if (atof(dstrFee.asA().c_str()) == atof(_dstrFee.asA().c_str()))
         _dstrFeeUpdateFlag = NO; */
      if( _dstrDefaultAcqFee  == I_("-1") )                     //first time
         bRequest = true;
   }
   else
   {
      bRequest = true;
   }
   if( bRequest )
   {
      _dstrDefaultAcqFee   = NULL_STRING;

      _dstrTaxType         = dstrTaxType;
      _dstrTransType       = dstrTransType;
      _dstrEffectiveDate   = dstrEffectiveDate;
      _dstrAmount          = dstrAmount;
      _dstrAmountType      = dstrAmountType;
      _dstrFundCode        = dstrFundCode;
      _dstrClassCode       = dstrClassCode;
      _dstrFundToCode      = dstrFundToCode;
      _dstrClassToCode     = dstrClassToCode;
      _dstrCurrency        = dstrCurrency;
      _dstrBrokerCode      = dstrBrokerCode;
		_dstrFlatPercent     = dstrFlatPercent;

      if( _pAcqFeeInquiry )
      {
         delete _pAcqFeeInquiry;
         _pAcqFeeInquiry = NULL;
      }

      _dstrFeeDisableFlag = NO;

      double dValue = wcstod( dstrAmount.c_str(), &stopstring );
      if( !dstrFundCode.empty() && !dstrClassCode.empty() &&
          dValue > 0 && !dstrTransType.empty() && 
          !dstrAmountType.empty() )
      {
         _pAcqFeeInquiry = new AcqFeeInquiry ( *this );
         _pAcqFeeInquiry->setFundCurrency(dstrFundCurrency);

         DString tempTransType (dstrTransType);
         if( tempTransType == AUTO_TRFER )
			{
            tempTransType = I_( "TR" );
		
				getField( ifds::AccountTo, dstrToAccount, idDataGroup, false );

				if (_pMFAccount) 
					_pMFAccount->getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );

				if (dstrToAccount != dstrAccountNum)
				{
					MFAccount *pMFAccountTo = NULL;

					if ( !dstrToAccount.empty() &&
							getWorkSession().getMFAccount (idDataGroup, dstrToAccount, pMFAccountTo) <= WARNING && 
							pMFAccountTo)
					{
						pMFAccountTo->getField (ifds::TaxType, dstrToAcctTaxType, idDataGroup);
					}
				}		
			}
		 else if( tempTransType == PAC )
		 {
			if (_pMFAccount) 
					_pMFAccount->getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );
		 }

         SEVERITY sevRtn = _pAcqFeeInquiry->init( dstrTaxType,
                                                  tempTransType,
                                                  dstrEffectiveDate,
                                                  dstrAmount,
                                                  dstrAmountType,
                                                  dstrFundCode,
                                                  dstrClassCode,
                                                  dstrCurrency,
                                                  dstrBrokerCode, 
                                                  dstrFundToCode,
                                                  dstrClassToCode,
																  dstrFlatPercent,
																  I_("N"),  // track default
																  NULL_STRING ,  // activity default
																  dstrToAcctTaxType,
																  dstrAccountNum );	
         if( sevRtn > WARNING )
         {
            delete _pAcqFeeInquiry;
            _pAcqFeeInquiry = NULL;
            return(sevRtn);
         }
         calculateDefaultAcqFee(idDataGroup);
      }
   }
   return(NO_CONDITION);
}
//*****************************************************

/**
  * Calculate the default Systematic Acquisition Fee 
  * according to the Flat/Percent flag
  */
void Systematic::calculateDefaultAcqFee(const BFDataGroupId& idDataGroup)
{
   if( !_pAcqFeeInquiry )
      return;

   // calculate the Default Systematic Fee based on the Flat/Percent flag
   DString dstrAcqFeeType, dstrAcqFee, dstrFlatPercent, dstrFee;

   _pAcqFeeInquiry->getField(ifds::AcqFeeType, dstrAcqFeeType, idDataGroup, false);    
   getField(ifds::FlatPercent,   dstrFlatPercent, idDataGroup, false);

   DString dstrAmount;
   getField( ifds::Amount, dstrAmount, idDataGroup, false );
   _pAcqFeeInquiry->getField(ifds::AcqFee, dstrAcqFee,  idDataGroup, false);

   double fAmount = DSTCommonFunctions::convertToDouble( dstrAmount );
   double fAcqFee = DSTCommonFunctions::convertToDouble( dstrAcqFee );

   if( dstrAcqFeeType.strip() == I_("0") && dstrFlatPercent.strip() != YES )
   {
      fAcqFee = fAcqFee / fAmount * 100;
   }
   else if( (dstrAcqFeeType.strip() == I_("1") || dstrAcqFeeType.strip() == I_("2")) && 
            dstrFlatPercent.strip() == YES )
   {
      fAcqFee = fAcqFee * fAmount / 100;
   }

   _dstrDefaultAcqFee = DSTCommonFunctions::doubleToDString( ifds::Fee, fAcqFee );
}

//*******************************************************

SEVERITY Systematic::getAcqFeeInquiry( AcqFeeInquiry *&pAcqFeeInquiry, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcqFeeInquiry" ) );

   requestAcqFeeInquiry(idDataGroup);
   pAcqFeeInquiry = _pAcqFeeInquiry;

   return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************
SEVERITY Systematic::getSysAllocationList( SysAllocationList *&pSysAllocationList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSysAllocationList" ) );

   pSysAllocationList = _pSysAllocationList;

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************
void Systematic::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));

   DString dstrEntityName, dstrAccountNum;
   /*  binit = true; */
   _pMFAccount->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

   //getWorkSession().getFirstSequenced01AccountholderEntityName( 
   //idDataGroup, dstrAccountNum, dstrEntityName);
   setFieldNoValidate( ifds::AccountNum, dstrAccountNum, BF::HOST );
   setFieldNoValidate( ifds::AccountNum, dstrAccountNum, idDataGroup);

//$$$ For unknown reason all default value must be assign also to idDataGroup or else the default value won't show on screen
// It is different than other CBO


   DString dstrPACAvailable,dstrSWPAvailable;

   TaxTypeRule *pTaxTypeRule = NULL;

   if ( _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
   {
      pTaxTypeRule->getField(ifds::PACallowed,dstrPACAvailable,idDataGroup,false);
      pTaxTypeRule->getField(ifds::SWPallowed,dstrSWPAvailable,idDataGroup,false);  
      dstrPACAvailable.strip();
      dstrSWPAvailable.strip();
   }

   DString dstrTransType ( PAC );
   if( _pList )
   {
      dstrTransType = _pList->getTransType();
      dstrTransType.strip();
      if( dstrTransType.empty() )
         dstrTransType = PAC ;
   }
   if( dstrTransType == PAC && dstrPACAvailable == NO && dstrSWPAvailable == YES )
      dstrTransType = SWP;
   else if( dstrTransType == SWP && dstrPACAvailable == YES && dstrSWPAvailable == NO )
      dstrTransType = PAC;
   else if( dstrPACAvailable == NO && dstrSWPAvailable == NO )
      dstrTransType = AUTO_TRFER;  //AT is always available
   
   setFieldReadOnly( ifds::SystematicPayType, idDataGroup, false );
   setUpdatedFlag( ifds::SystematicPayType, idDataGroup, false );

   if ( _pMFAccount ) {
      if ( _pMFAccount->isCategoryExist ( idDataGroup, MARGIN ) )
         dstrSWPAvailable = NO;
   }   

   if( dstrSWPAvailable == YES && dstrPACAvailable == NO )
      setFieldSubstituteValues( ifds::SystematicPayType, idDataGroup, ifds::SystematicPaySWP );
   else if( dstrSWPAvailable == NO && dstrPACAvailable == YES )
      setFieldSubstituteValues( ifds::SystematicPayType, idDataGroup, ifds::SystematicPayPAC );
   else if( dstrSWPAvailable == NO && dstrPACAvailable == NO )
   { // if both PAC and SWP are not allowed, only AT is effect 
      setFieldReadOnly( ifds::SystematicPayType, BF::HOST, true );
      setFieldReadOnly( ifds::SystematicPayType, idDataGroup, true );
	  setUpdatedFlag( ifds::SystematicPayType, idDataGroup, true );
   }
   setFieldNoValidate( ifds::TransType, dstrTransType,  BF::HOST,false);//,true,false,NULL,false );
   setFieldNoValidate( ifds::TransType, dstrTransType,  idDataGroup,false);//,true,false,NULL,false );

   _dstrTransType = dstrTransType;
   setFieldStatus( idDataGroup, dstrTransType == SAVING_PLAN );

   if (dstrTransType == AUTO_TRFER)
   {
      setFieldNoValidate( ifds::PayType, I_("AT"),  BF::HOST );
      setFieldNoValidate( ifds::PayType, I_("AT"),  idDataGroup );
   }
   else if( dstrTransType == SWP ) // default to system check because SSB does not have 'SWP EFT'
   {
      setFieldNoValidate( ifds::PayType, I_("S"), BF::HOST );
      setFieldNoValidate( ifds::PayType, I_("S"), idDataGroup );
   }
   else
   {
      setFieldNoValidate( ifds::PayType, I_("E"), BF::HOST );
      setFieldNoValidate( ifds::PayType, I_("E"), idDataGroup );
   }

   setAmtTypeSubList ( idDataGroup ); // set AmountType Substitution list
   setAmtTypeSubList ( BF::HOST  ); // set AmountType Substitution list

   DString amountType = I_("D");
   
   if (!_dstrAwdAmountType.empty ())
   {
	   amountType = _dstrAwdAmountType;
   }

   setFieldNoValidate( ifds::AmountType, amountType, BF::HOST, false /*, true, true, NULL, false */);
   setFieldNoValidate( ifds::AmountType, amountType, idDataGroup, false /*, true, true, NULL, false */);


   // for bank dlg
   setFieldNoValidate( ifds::InstCode, NULL_STRING, BF::HOST );
   setFieldNoValidate( ifds::TransitNo, NULL_STRING, BF::HOST );
   setFieldNoValidate( ifds::SwiftCode, NULL_STRING, BF::HOST );
   setFieldNoValidate( ifds::RefNumber, NULL_STRING, BF::HOST );

   _pMFAccount->getAcctName(dstrEntityName, idDataGroup);
   setFieldNoValidate( ifds::BankAcctName, dstrEntityName, BF::HOST );


   if( _dstrmultiCurrency == YES )
   {
      setFieldNoValidate( ifds::BankAcctCurrency, _dstrSysCurrency, BF::HOST, false );
      setFieldNoValidate( ifds::BankAcctCurrency, _dstrSysCurrency, idDataGroup, false );

      setFieldReadOnly( ifds::BankAcctCurrency, BF::HOST, false );
   }
   else
   {
      setFieldNoValidate( ifds::BankAcctCurrency, NULL_STRING, BF::HOST, false,true,false,false );
      setFieldNoValidate( ifds::BankAcctCurrency, NULL_STRING, idDataGroup, false,true,false,false );
      setFieldReadOnly( ifds::BankAcctCurrency, BF::HOST, true );
   }
   

   DString dstrBankLayout;
   _pMgmtCoOption->getField( ifds::BankLayout,   dstrBankLayout,   idDataGroup ,false );
   if( (dstrBankLayout == I_("1") || dstrBankLayout  == I_("2")) && dstrTransType == PAC )
   {
      setFieldNoValidate( ifds::SrcOfFund, I_("03"), idDataGroup, false );
   }
   else  
   {
      setFieldNoValidate( ifds::SrcOfFund,NULL_STRING, idDataGroup, false );
   }

   setFieldNoValidate(ifds::DayOfWeek, NULL_STRING, BF::HOST );

   setFieldNoValidate( ifds::GrossOrNet, YES, BF::HOST );

   setFieldNoValidate( ifds::StatusCode, YES, BF::HOST );
   setFieldNoValidate( ifds::EndOfMonth, I_("N"), BF::HOST );
   setFieldNoValidate( ifds::Frequency, I_("3"), BF::HOST );
   setFieldNoValidate( ifds::Frequency, I_("3"), idDataGroup );

   setFieldNoValidate( ifds::January, YES, BF::HOST );
   setFieldNoValidate( ifds::February, YES, BF::HOST );
   setFieldNoValidate( ifds::March, YES, BF::HOST );
   setFieldNoValidate( ifds::April, YES, BF::HOST );
   setFieldNoValidate( ifds::May, YES, BF::HOST );
   setFieldNoValidate( ifds::June, YES, BF::HOST );
   setFieldNoValidate( ifds::July, YES, BF::HOST );
   setFieldNoValidate( ifds::August, YES, BF::HOST );
   setFieldNoValidate( ifds::September, YES, BF::HOST );
   setFieldNoValidate( ifds::October, YES, BF::HOST );
   setFieldNoValidate( ifds::November, YES, BF::HOST );
   setFieldNoValidate( ifds::December, YES, BF::HOST );


   setFieldNoValidate( ifds::Fee,         I_("0"), BF::HOST, false /*, true, true, NULL, false*/ );
   setFieldNoValidate( ifds::AdminFeeAmt, I_("0"), BF::HOST, false /*, true, true, NULL, false*/ );
   setFieldNoValidate( ifds::FlatPercent, NO,     BF::HOST, false /*, true, true, NULL, false */);
   setFieldNoValidate( ifds::Fee,         I_("0"), idDataGroup, false /*, true, true, NULL, false*/ );
   setFieldNoValidate( ifds::AdminFeeAmt, I_("0"), idDataGroup, false /*, true, true, NULL, false*/ );
   setFieldNoValidate( ifds::FlatPercent, NO,     idDataGroup, false /*, true, true, NULL, false */);

   DString str;
   getWorkSession().getDateInHostFormat(str, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);  
   //bug fix where if host is not applied first, the default allocations
   //list is not cleaned up properly.
   setFieldNoValidate( ifds::EffectiveDate, str, BF::HOST , false );
   setFieldNoValidate( ifds::EffectiveDate, str, idDataGroup , false );
   getWorkSession().getDateInHostFormat(str);
   setFieldNoValidate( ifds::StopDate, str, idDataGroup , false );
   setFieldNoValidate( ifds::StopDate, str, BF::HOST , false );

   setFieldNoValidate( ifds::BELFee, YES, idDataGroup , false );
   setFieldNoValidate( ifds::BELFee, YES, BF::HOST , false );


   setFieldReadOnly( ifds::StatusCode, idDataGroup, true );
   setFieldNoValidate( ifds::SystematicPayType, I_(""), BF::HOST, false,true,false,false);
   setFieldNoValidate( ifds::SystematicPayType, I_(" "), /*I_("P-E")*/ idDataGroup, false,true,false,false );

   setFieldNoValidate( ifds::AccountTo, I_(""), idDataGroup, false,true,false,false );
   setFieldNoValidate( ifds::AccountTo, I_(""), BF::HOST, false,true,false,false );

 //  setFieldReadOnly( ifds::SystematicPayType, idDataGroup, false );
 //  setUpdatedFlag( ifds::SystematicPayType, idDataGroup, false );
   DString payTypeDefault;

   getSystematicDefault (ifds::TradePayTypeDefault, payTypeDefault, BF::HOST);

   if (!_dstrPayType.empty ())
   {
		payTypeDefault = _dstrPayType;
   }

   if (!payTypeDefault.empty())
   {
      setFieldNoValidate( ifds::SystematicPayType, payTypeDefault, BF::HOST, false,true,false,false);
      setFieldNoValidate( ifds::SystematicPayType, payTypeDefault, idDataGroup, false,true,false,false);
	  setFieldNoValidate( ifds::PayType, payTypeDefault, BF::HOST, false,true,false,false);
      setFieldNoValidate( ifds::PayType, payTypeDefault, idDataGroup, false,true,false,false);
   }


   setValidFlag(ifds::BankInformation,  idDataGroup, false);
   setValidFlag(ifds::SystematicCrossField2,  idDataGroup, false);     

   MFAccount* pMFAccount = NULL;   

   if (dstrTransType == AUTO_TRFER) 
   {
      DString dstrAccountTo;

      getField (ifds::AccountTo, dstrAccountTo, idDataGroup);
      getMFAccount (dstrAccountTo, idDataGroup, pMFAccount);
   } 
   else 
   {
      pMFAccount = _pMFAccount;
   }
   if (pMFAccount && pMFAccount->isAMSAccount (idDataGroup))
   {
      DString dstrPACSWPOverride;
      getWorkSession().getOption( ifds::PACSWPOverride, dstrPACSWPOverride, idDataGroup, false); 
      if (dstrPACSWPOverride == YES) 
      {
         if (dstrTransType == AUTO_TRFER) 
         {
            setFieldReadOnly (ifds::ToFundNumber, idDataGroup, true);
            setFieldReadOnly (ifds::FundToCode, idDataGroup, true);
            setFieldReadOnly (ifds::ClassToCode, idDataGroup, true);
         } 
         else 
         {
            setFieldReadOnly (ifds::FrFundNumber, idDataGroup, true);
            setFieldReadOnly (ifds::FundCode, idDataGroup, true);
            setFieldReadOnly (ifds::ClassCode, idDataGroup, true);
         }
      }   
   }
   //Setup the Batch Information.
   BFData query124(ifds::DSTC0124_REQ);
   DString mgmtCoIdOut;
   query124.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   query124.setElementValue( ifds::Track, I_("N") );
   query124.setElementValue( ifds::Activity, NULL_STRING );

   BFData *response = new BFData(ifds::DSTC0124_VW);

   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ACTIVE_BATCH, query124, *response, DSTCRequestor(getSecurity()) ) <= WARNING ) {
      DString dstrBatchName;
      response->getElementValue( ifds::rxBatchName, dstrBatchName );
      setFieldNoValidate( ifds::BatchName, dstrBatchName, idDataGroup, false );
	  DString dstrServerTime;
	  response->getElementValue( ifds::ServerTime, dstrServerTime );
	  setFieldNoValidate( ifds::ServerTime, dstrServerTime, idDataGroup, false, false, true);
   }
   else      // Incident 295478 - Discard on Cancel does not work because of this error 
	         // when user has no active batch
   {
		int count = CONDITIONCOUNT();
		Condition *c = NULL;
		for (int i = 0; i < count; i++)
		{
			c = GETCONDITION( i );
			int condCode = c->getCode();
			//do not want to promote this condition 
			//if (condCode == CND::ERR_NO_ACTIVE_BATCH ) 
			//{
				CLEARCONDITION( i );			
				//break;				
			//}
		}
   }

	setFieldNoValidate( ifds::PayMethod, DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): I_("EFT"), idDataGroup );
	setFieldNoValidate( ifds::ACHProcessor, NULL_STRING,  idDataGroup );
	systematicPayTypeRelatedChangesForFileProcessor( idDataGroup );

	// WHTax 	
	setFieldNoValidate( ifds::FedTaxPUDOverride,  I_( "0" ),    idDataGroup, false );
	setFieldNoValidate( ifds::FedRate,            I_( "0.00" ), idDataGroup, false );
	setFieldNoValidate( ifds::ProvTaxPUDOverride, I_( "0" ),    idDataGroup, false );
	setFieldNoValidate( ifds::ProvRate,           I_( "0.00" ), idDataGroup, false );
   transTypeWHTaxRelatedChanges( idDataGroup );
   setValidFlag( ifds::FundToClassToAccountTo, idDataGroup, false );
   setValidFlag( ifds::EffectiveDate, idDataGroup, false );

//   setFieldReadOnly( ifds::StopReasonPAC, idDataGroup, true );

   if (!_dstrAwdAmount.empty ())
   {
		setFieldNoValidate( ifds::Amount, _dstrAwdAmount, BF::HOST, false);
		setFieldNoValidate( ifds::Amount, _dstrAwdAmount, idDataGroup, false);
   }


   if(isNewObject())
   {
      DString dstrTaxType;
      _pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);

      if(dstrTaxType == REG_AGENT_TAX_TYPE::ORD_ACC ||
         dstrTaxType == REG_AGENT_TAX_TYPE::SPL_ACC ||
         dstrTaxType == REG_AGENT_TAX_TYPE::SRS_ACC)
      {
         if(dstrTransType == PAC)
         {
            setField(ifds::SystematicPayType, I_("P-X"), idDataGroup, false);
         }
         else if(dstrTransType == SWP)
         {
            setField(ifds::SystematicPayType, I_("S-X"), idDataGroup, false);
         }
         setFieldReadOnly(ifds::SystematicPayType, idDataGroup, true);
      }
      else if (MARKET_IDS::LUXEMBOURG == DSTCommonFunctions::getMarket())
      {
         DString dstrPayTypeAllSubst = removeItemFromAllSubtList (ifds::SystematicPayType, I_("P-X"), idDataGroup);//added for market Lux by CPF, not needed for non RA regs
         dstrPayTypeAllSubst = removeItemFromSubtList (dstrPayTypeAllSubst, I_("S-X"));
         setFieldAllSubstituteValues (ifds::SystematicPayType, idDataGroup, dstrPayTypeAllSubst);
      }

		if( _dstrmultiCurrency == YES )
		{
         DString dstrSettleCurrency;
         _pMFAccount->getField(ifds::SettleCurrency, dstrSettleCurrency, idDataGroup, false);
         dstrSettleCurrency.strip();
         if(dstrSettleCurrency != I_(""))
         {
            setField(ifds::BankAcctCurrency, dstrSettleCurrency, idDataGroup, false);
         }
      }
   }

   bool bEventReceiptDateTimeAppl   = bIsEventReceiptDateTimeAppl(idDataGroup);
   setFieldNoValidate(ifds::EventReceiptDate,NULL_STRING,idDataGroup);
   setFieldNoValidate(ifds::EventReceiptTime,NULL_STRING,idDataGroup);
   setFieldValid(ifds::EventReceiptDate,idDataGroup,false);
   setFieldValid(ifds::EventReceiptTime,idDataGroup,false);
   //A new setup should allow entry irresepctive of verification status
   setFieldReadOnly(ifds::EventReceiptDate,idDataGroup, !bEventReceiptDateTimeAppl);//no apply related changes
   setFieldReadOnly(ifds::EventReceiptTime,idDataGroup, !bEventReceiptDateTimeAppl);
   setFieldNoValidate(ifds::Platform, PLATFORM::DESKTOP, idDataGroup, false, false, true);
   setFieldReadOnly(ifds::Platform, idDataGroup, true);
   DString dstrPSDAdvice;
   getWorkSession ().getOption (ifds::PSDAdvice, dstrPSDAdvice, idDataGroup,  false);
   if(  NO == dstrPSDAdvice.stripAll())
   {
	addBlankToSubSet( ifds::SourceOfTrade,  idDataGroup );
    addBlankToSubSet( ifds::ChannelOfTrade, idDataGroup );
   }
   DString dstrTime;
   getField(ifds::ServerTime, dstrTime, idDataGroup );
   if( !dstrTime.empty())
   {
	DString strTime (dstrTime), strHour, strMin;
	DString::size_type iPos = strTime.find (I_(":"));
	int ihour;
	if (iPos != std::string::npos)
		strHour = strTime.substr (0,iPos);
	else
		strHour = strTime.substr (0,2);
	ihour = strHour.asInteger ();
	dstrTime = ihour > 11 ? I_("PM") : I_("AM");
	setFieldNoValidate (ifds::TimeFactor, dstrTime, idDataGroup, false, true, true, false);
   }
   DString dstrScreenActivityType;
   dstrScreenActivityType = dstrTransType == PAC ? PAC : NULL_STRING;
   setFieldNoValidate(ifds::ScreenActivityType, PAC, idDataGroup, false, false, true); 
   populateFieldsWithDefaultValues(idDataGroup, MODE_INIT);
   setFieldReadOnly(ifds::PSDAdvice, idDataGroup, NO == dstrPSDAdvice.stripAll());
   if(dstrTransType != PAC)
   {
	 DString dstrCurrSubList; 
	 BFProperties *pBFProperties = getFieldProperties (ifds::SystematicGridLeftHeading, idDataGroup); 
	 assert (pBFProperties);
	 if (pBFProperties) 
	 {
       pBFProperties->getAllSubstituteValues (dstrCurrSubList);
	   dstrCurrSubList = removeItemFromSubtList( ifds::SystematicGridLeftHeading,I_("SourceOfTarde"), idDataGroup);
	   dstrCurrSubList = removeItemFromSubtList( ifds::SystematicGridLeftHeading,I_("ChannelOfTarde"), idDataGroup);
	   dstrCurrSubList = removeItemFromSubtList( ifds::SystematicGridLeftHeading,I_("PSDAdvice"), idDataGroup);
	   setFieldAllSubstituteValues(ifds::SystematicGridLeftHeading, idDataGroup, dstrCurrSubList);
	 }
   }  
}
//********************************************************
// the method will be called in systematic process
// 
DString Systematic::getTransactionTypeValue(const BFDataGroupId& idDataGroup)
{
   DString retValue;
   DString strFromFund,strFromClass,strToFund,strToClass,strFromLoadType,strToLoadType,strToAccount;

   getField( ifds::FundCode, strFromFund, idDataGroup, false );
   strFromFund.strip();

   getField( ifds::ClassCode, strFromClass, idDataGroup, false );
   strFromClass.strip();

   getField( ifds::FundToCode, strToFund, idDataGroup, false );
   strToFund.strip();

   getField( ifds::ClassToCode, strToClass, idDataGroup, false );
   strToClass.strip();

   getField( ifds::AccountTo, strToAccount, idDataGroup, true );
   strToAccount.strip().stripLeading(I_CHAR('0'));

   if( strToFund.empty() || strToClass.empty() || strToAccount.empty() )
   {
      retValue = MULTITRANSFER;
      return(retValue);
   }

   _pFundDetailList->getField ( strFromFund, strFromClass, ifds::LoadType, strFromLoadType, BF::HOST, false );
   strFromLoadType.strip().upperCase();

   _pFundDetailList->getField ( strToFund, strToClass, ifds::LoadType, strToLoadType, BF::HOST, false );
   strToLoadType.strip().upperCase();

   // from fund is money maeket and load type is "Front End" 
   if( (_pFundMasterList->isMoneyMarketFund(strFromFund)) && strFromLoadType == FRONT_END )
   {
      retValue = REDEMPTION_PERCHASE;
      return(retValue);
   }

   //the from fund = the to fund and the load type = the to load
   DString  retTransType;

   if( (strFromFund == strToFund) && (strFromLoadType == strToLoadType) )
   {
      retTransType = TRANSFER;
   }
   else
   {
      retTransType = EXCHANGE;
   }

   if( (strFromFund == strToFund) && (strFromLoadType == strToLoadType) )
   {
      retTransType = retTransType + WITHIN_FUND_CLASS;
   }
   else if( strFromFund != strToFund )
   {
      retTransType = retTransType + WITHIN_CLASS_FUND;
   }

   // get TaxType
   DString strFrTaxType,strToTaxType,strFrAccountNum;
   getField( ifds::AccountNum, strFrAccountNum, idDataGroup, false );
   strFrAccountNum.strip().stripLeading(I_CHAR("0"));

   MFAccount *pMFFromAccount = NULL, *pMFToAccount;
   SEVERITY sevRtn = NO_CONDITION;

   sevRtn = getMFAccount ( strFrAccountNum, idDataGroup, pMFFromAccount );
   sevRtn = getMFAccount ( strToAccount, idDataGroup, pMFToAccount );

   if( pMFFromAccount && pMFToAccount )
   {
      pMFFromAccount->getField( ifds::TaxType, strFrTaxType, idDataGroup );
      pMFToAccount->getField( ifds::TaxType, strToTaxType, idDataGroup );

      strFrTaxType.strip().upperCase();
      strToTaxType.strip().upperCase();
   }

   if( (strToTaxType == RRIF_TAXTYPE || strToTaxType == PRIF_TAXTYPE ) && strFrTaxType == RRSP_TAXTYPE )
   {
      retTransType = retTransType + RRSP_TO_RRIF;
   }
   retValue = retTransType;
   return(retValue);
}
//*********************************************************

void Systematic::SetFieldProperties(const BFDataGroupId& idDataGroup, bool bIsNewItem)
{
   setFieldReadOnly( ifds::TransType,        idDataGroup, !bIsNewItem );
   setFieldReadOnly( ifds::BankAcctCurrency, idDataGroup, !bIsNewItem );

   DString str, str1;
   _pMgmtCoOption->getField( ifds::SYMBrkUpd, str, BF::HOST, false );
   setFieldReadOnly( ifds::BrokerCode, idDataGroup, str.strip() != YES );
   setFieldReadOnly( ifds::BranchCode, idDataGroup, str.strip() != YES );
   setFieldReadOnly( ifds::SalesRepCode, idDataGroup, str.strip() != YES );
}

//****************************************************************************************
SEVERITY  Systematic::getAtAcctAllocationList( AutoAcctTransAllocationList *&pAtAcctAllocationList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getATAccntAllocationList" ) );
   pAtAcctAllocationList = _pAtAcctAllocationList;

   return(GETCURRENTHIGHESTSEVERITY());

}
//************************************************************************************

void Systematic::getField( const BFFieldId& idField, DString& strFieldValue, 
                           const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   BFCBO::getField(idField, strFieldValue, idDataGroup, formattedReturn);

   if( formattedReturn )
   {
      DString dstrCurrency;
      if( idField == ifds::Amount )
      {
         BFCBO::getField( idField, strFieldValue, idDataGroup, false );
         getFormattedAmount(idDataGroup, strFieldValue);
      }
      else if( idField == ifds::VUBExpectedAmt )
      {
         getField(ifds::BankAcctCurrency, dstrCurrency, idDataGroup, false);
         dstrCurrency.strip();
         if( !dstrCurrency.empty() )
         {
            BFCBO::getField(idField, strFieldValue, idDataGroup, false);
            CurrencyClass::FormatValue(dstrCurrency, strFieldValue, strFieldValue);
         }
      }
      else if( idField == ifds::Fee )
      {
         getFormattedFee(idDataGroup, strFieldValue);
      }
      else if( idField == ifds::AdminFeeAmt )
      {
         getField(ifds::AdminFeeCurr, dstrCurrency, idDataGroup, false);
         dstrCurrency.strip();
         if( !dstrCurrency.empty() )
         {
            BFCBO::getField(idField, strFieldValue, idDataGroup, false);
            CurrencyClass::FormatValue(dstrCurrency, strFieldValue, strFieldValue);
         }
      }
   }

   if( idField == ifds::SystematicPayType )
   {
      DString dstrTransType, dstrPayType;

      getField( ifds::TransType, dstrTransType, idDataGroup, false);
      getField( ifds::PayType, dstrPayType, idDataGroup, false);

      if( dstrTransType.strip( )  !=  NULL_STRING  ||  dstrPayType.strip( )  !=  NULL_STRING )
      {
         if( dstrTransType == AUTO_TRFER )
            strFieldValue = dstrTransType;
         else
            strFieldValue = dstrTransType.strip() + I_("-") + dstrPayType.strip();
      }
      else
         strFieldValue = BLANKSTRING;

      dstrPayType = strFieldValue.upperCase();

      if( formattedReturn )
      {
         DString sub;
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
         pProps->getAllSubstituteValues( sub, ClientLocaleContext::get() );

         strFieldValue = DSTCommonFunctions::getDescription( dstrPayType, sub );
         if( dstrPayType != NULL_STRING && strFieldValue == NULL_STRING )strFieldValue = dstrPayType;

      }
   }

   else if( idField == ifds::VUBFee )
   {
      getVUBFee(strFieldValue, idDataGroup);
   }
   else if( idField == ifds::AccountTo )
   {
      strFieldValue.strip().stripLeading('0');

   }

   /*
   if(isNew() && idField == DBR::VUBExpectedAmt)
   {
     getVUBExpectedAmt(strFieldValue, idDataGroup);
   }
   */

   if( idField == ifds::BankInformation )
   {
      DString dstrAcctNum, dstrAcctType;
      getField(ifds::BankAcctNum, dstrAcctNum, idDataGroup, true);
      getField(ifds::BankAcctType, dstrAcctType, idDataGroup, true);
      dstrAcctNum.strip();
      dstrAcctType.strip();
      if( dstrAcctNum.empty() && dstrAcctType.empty() )
         strFieldValue = NULL_STRING;
      else
         strFieldValue = dstrAcctNum + SEP_SLASH + dstrAcctType;
   }
}

//******************************************************************************
SEVERITY Systematic::setField( const BFFieldId& idField, 
                               const DString& dstrValue,
                               const BFDataGroupId& idDataGroup, 
                               bool bFormatted, 
                               bool bSideEffect, 
                               bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );

   DString dstrOrgTransType;
   if( idField == ifds::FundCode || idField == ifds::ClassCode )
   {
      setFundField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
      setFundNumber(idField, idDataGroup);
      setValidFlag(ifds::Amount, idDataGroup, false);
      return(GETCURRENTHIGHESTSEVERITY());
   }
   else if( idField == ifds::TransType )
   {
      //keep the original transaction type
      getField(idField, dstrOrgTransType, idDataGroup, false);
      dstrOrgTransType.strip().upperCase();
   }
   else if( idField == ifds::AccountTo )
   {
      DString oldValue;
      getField(idField,oldValue,idDataGroup,true);
      oldValue.strip().stripLeading('0');
      if( oldValue == dstrValue ) return(GETCURRENTHIGHESTSEVERITY());
   }
   if( idField == ifds::SystematicPayType )
   {
      DString oldValue;
      getField(idField,oldValue,idDataGroup,false);
      if( oldValue == dstrValue)
      {
          if (!isSWPPortfolioPayoutPlan(idDataGroup))
              setFieldReadOnly( ifds::SystematicPayType, idDataGroup, true );

          setUpdatedFlag( ifds::SystematicPayType, idDataGroup, false );   


/*
         // Batch
         DString dstrBatch;
         BFData query124(ifds::DSTC0124_REQ);
         DString mgmtCoIdOut;
         query124.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
         query124.setElementValue( ifds::Track, I_("N") );
         query124.setElementValue( ifds::Activity, NULL_STRING );

         BFData *response = new BFData(ifds::DSTC0124_VW);

         if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ACTIVE_BATCH, query124, *response, DSTCRequestor(getSecurity()) ) <= WARNING )
         {
            response->getElementValue( ifds::rxBatchName, dstrBatch );
            dstrBatch.strip();
            setFieldNoValidate( ifds::BatchName, dstrBatch, idDataGroup, false );
         }
         else
         {
            delete response;
            response = NULL;
            setFieldNoValidate( ifds::BatchName, NULL_STRING, idDataGroup, false );
         }

         return(GETCURRENTHIGHESTSEVERITY());
*/
			return NO_CONDITION;
      }
   }
	if ( ifds::FedTaxPUDOverride == idField )
	{						
		setField( ifds::FedRate, I_( "0.00" ), idDataGroup );				
	}
	if ( ifds::ProvTaxPUDOverride == idField )
	{						
		setField( ifds::ProvRate, I_( "0.00" ), idDataGroup );				
	}
	if (idField == ifds::Fee)
   {    
		DString dstrFee (dstrValue);

		if (bFormatted)
		{
			getFormattedFee (idDataGroup, dstrFee);
		}
		BFCBO::setField (idField, dstrFee, idDataGroup, bFormatted, true, false);
		return GETCURRENTHIGHESTSEVERITY();
   }

   SEVERITY  sevRtn = BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );

   if( sevRtn > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());


   if( idField == ifds::FrFundNumber || idField == ifds::ToFundNumber )
   {
      setFundClassCode(idField, idDataGroup);
   }
   else if( idField == ifds::FundToCode || idField == ifds::ClassToCode )
   {
      setFundNumber(idField, idDataGroup);
	  setValidFlag(ifds::Amount, idDataGroup, false);
   }
   else if( idField == ifds::Amount )
   {
      setAmountField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
   }

   else if( idField == ifds::AmountType )
   {
      BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
      DString dstrAmount;
      getField( ifds::Amount, dstrAmount, idDataGroup );
      setAmountField( ifds::Amount, dstrAmount, idDataGroup, bFormatted, bSideEffect); 
   }
   /** 
 else  this logic should be in the doapplyrelatedchange    W.Shiu July 18, 2002
 if(idField == ifds::BankAcctCurrency)
 {
   DString dstrFund;
   getField ( ifds::FundCode, dstrFund, idDataGroup );

   // the only way to change the bankacctcurrency of non-multicurrency is either by modifing the fund or 
   // modifing the allocation fund. No need to change the allocation if the change is initial from 
   // allocation
   if ( _dstrmultiCurrency == NO && dstrFund.strip() != NULL_STRING )
   {
     BFObjIter iter(*_pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
     while( !iter.end())
     {
       BFAbstractCBO *pBFCBO = iter.getObject();
       if (pBFCBO)
         pBFCBO->setField(ifds::SettleCurrency, dstrValue, idDataGroup, bFormatted, true);
       ++iter;
     }
   }
     DString dstrAmount;
     BFCBO::getField(ifds::Amount, dstrAmount, idDataGroup, false);
     setAmountField(ifds::Amount, dstrAmount, idDataGroup, false, true);
 } **/
   else if( idField == ifds::TransType )
   {
      if( dstrValue != I_("AT") ) // ying to do for saving plan
      {
         DString dstrPACSWPId, dstrLevel;

         dstrLevel = I_("3");
         getField(ifds::PACSWPId, dstrPACSWPId, idDataGroup, false);

         BFObjIter iter(*_pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         while( !iter.end() )
         {
            BFAbstractCBO *pBFCBO = iter.getObject();
            if( pBFCBO )
            {
               pBFCBO->setField(ifds::TransType, dstrValue, idDataGroup, bFormatted, true);
               pBFCBO->setField(ifds::PACSWPId, dstrPACSWPId, idDataGroup, false, true);
               pBFCBO->setField(ifds::Level, dstrLevel, idDataGroup, false, true);               
            }
            ++iter;
         }
      }
      if( dstrOrgTransType == I_("AT") && dstrValue != I_("AT") )
      {
         //if Transaction type changed from AT to PAC or SWP
         //we need to set up the allocation record correctly
         DString dstrFundCode, dstrClassCode;
         getField(ifds::FundCode, dstrFundCode, idDataGroup , false);
         getField(ifds::ClassCode, dstrClassCode, idDataGroup , false);
         if( dstrFundCode.strip() != NULL_STRING && dstrClassCode.strip() != NULL_STRING )
            setFundField(ifds::FundCode, dstrFundCode, idDataGroup, false, false);
         setFieldNoValidate( ifds::GrossOrNet, YES, idDataGroup, false, false, true );
      }
   }
   else if( idField == ifds::FlatPercent )
   {
		requestAcqFeeInquiry (idDataGroup);
   }
   else if( idField == ifds::BankInformation )
   {
      DString dstrAcctNum, dstrAcctType;
      parsingCombinedField(dstrValue, dstrAcctNum, dstrAcctType, SEP_SLASH);
      setField( ifds::BankAcctNum, dstrAcctNum, idDataGroup, false, true);
   }

   
   return(GETCURRENTHIGHESTSEVERITY());
}


//**********************************************************************************************
void Systematic::setExchInFee( const BFDataGroupId& idDataGroup )
{
   DString dstrExchInFeeExist, dstrToFund, dstrToClass,  strExit = I_( "N" );
   SEVERITY sevRtn = NO_CONDITION;

   getField (ifds::FundToCode,     dstrToFund,       idDataGroup );
   getField( ifds::ClassToCode,    dstrToClass,      idDataGroup );

   if( !dstrToFund.empty() && !dstrToClass.empty() )
   {
      FundDetail *pFundDetail = NULL;
      if( _pFundDetailList->getFundDetail( dstrToFund, dstrToClass, idDataGroup, pFundDetail ) )
      {
         pFundDetail->getField( ifds::ExchInFeeExist, strExit, idDataGroup, false  );
      }

      if( sevRtn <= WARNING && strExit.strip().upperCase() == I_( "Y" ) )
      {
         setFieldNoValidate(ifds::Fee, I_("0"), idDataGroup, false, true, true );
         //setFieldReadOnly  (ifds::Fee, idDataGroup, true );
         setFieldReadOnly  (ifds::FlatPercent, idDataGroup, true );
         setFieldReadOnly  (ifds::ExchInFee, idDataGroup, false );
         setFieldReadOnly  (ifds::ExchInFlatPercent, idDataGroup, false );
         sevRtn = setDefaultExchInFee ( dstrToFund, dstrToClass, idDataGroup );
      }
      else
      {
         //setFieldReadOnly  (ifds::Fee, idDataGroup, false );
         setFieldReadOnly  (ifds::FlatPercent, idDataGroup, false );

         setFieldNoValidate(ifds::ExchInFee, I_("0"), idDataGroup, false, true, true);
         setFieldNoValidate(ifds::ExchInFlatPercent, I_("N"), idDataGroup, false, true, true);
         setFieldReadOnly  (ifds::ExchInFee, idDataGroup, true );
         setFieldReadOnly  (ifds::ExchInFlatPercent, idDataGroup, true );
      }
   }
   else if( dstrToFund.empty() && dstrToClass.empty() )
   {
      // allocated or full exchange
      setFieldNoValidate(ifds::Fee, I_("0"), idDataGroup, false, true, true );
      setFieldNoValidate(ifds::FlatPercent, I_("N"), idDataGroup, false, true, true);
      setFieldNoValidate(ifds::ExchInFee, I_("0"), idDataGroup, false, true, true);
      setFieldReadOnly  ( ifds::Fee, idDataGroup, true );
      setFieldReadOnly  ( ifds::FlatPercent, idDataGroup, true );
      setFieldReadOnly  ( ifds::ExchInFee, idDataGroup, true );
      setFieldReadOnly  ( ifds::ExchInFlatPercent, idDataGroup, true );

   }

}


//**********************************************************************************************
SEVERITY Systematic::setExchOutFee(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultExchOutFee" ));

   DString dstTransType;

   //see whether this fee exists
   DString dstrFromFund, dstrFromClass;

   getField(ifds::FundCode, dstrFromFund, idDataGroup);
   getField(ifds::ClassCode, dstrFromClass, idDataGroup);

   if( !dstrFromFund.empty() && !dstrFromClass.empty() )
   {
      TradingFeeRules* exchangeOutRules = NULL;
      DString strRate, strFeeType;
      bool readonly = true;
      if (TradingFeeRules::getExchangeOutFeeRules(*this, 
         exchangeOutRules, 
         ifds::ExchOutFee, ifds::ExchOutFlatPrcnt,
         ifds::FundCode, ifds::ClassCode,
         ifds::EffectiveDate, ifds::AccountNum, 
         ifds::BrokerCode, ifds::BranchCode,
         ifds::SlsrepCode,
         idDataGroup) <= WARNING)
      {
         if (exchangeOutRules->feeExists(idDataGroup))
         {
            exchangeOutRules->getField(ifds::FeeType, strFeeType, idDataGroup);
            //hack for now, change this!
            if (strFeeType == I_("1"))
               setFieldNoValidate(ifds::ExchOutFlatPrcnt, I_("N"), idDataGroup, false, true, true);
            else if (strFeeType == I_("0"))
               setFieldNoValidate(ifds::ExchOutFlatPrcnt, I_("Y"), idDataGroup, false, true, true);
            exchangeOutRules->getField(ifds::Rate, strRate, idDataGroup);
            setField(ifds::ExchOutFee, strRate, idDataGroup, true, true);
            readonly = false;
         }
         else
         {
            //default values if the fee doesn't exist
            setFieldNoValidate(ifds::ExchOutFee, I_("0"), idDataGroup, true, true, true);
            setFieldNoValidate(ifds::ExchOutFlatPrcnt, I_("Y"), idDataGroup, false, true, true);
         }
      }
      if (exchangeOutRules != NULL)
      {
         delete exchangeOutRules;
      }
      //set the readonly flag on these fields
      setFieldReadOnly(ifds::ExchOutFlatPrcnt, idDataGroup, readonly);
      setFieldReadOnly(ifds::ExchOutFee, idDataGroup, readonly);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//**********************************************************************************************
SEVERITY Systematic::setDefaultExchInFee( DString dstrFundCode, DString dstrClassCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultExchInFee" ) );
   SEVERITY sevRtn = NO_CONDITION;

   DString dstrExchInFeeDefault, dstrExchInFeeDefType, dstrExchInFee;
   if( !_pFundDetailList )
   {
      getMgmtCo().getFundDetailList( _pFundDetailList );
   }

   FundDetail *pFundDetail = NULL;
   if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) &&  pFundDetail )
   {
      pFundDetail->getFeeInfoInquiryField( ifds::ExchInFeeDefault, dstrExchInFeeDefault, idDataGroup, false ); 

      pFundDetail->getFeeInfoInquiryField( ifds::ExchInFeeDefType, dstrExchInFeeDefType, idDataGroup, false ); 
   }

   if( dstrExchInFeeDefault == NULL_STRING )
   {
      dstrExchInFeeDefault = I_( "0.00" );
   }
   getField( ifds::ExchInFee, dstrExchInFee, idDataGroup, true);

   double dec_default_ExchInFee = DSTCommonFunctions::convertToDouble( dstrExchInFeeDefault );
   double dec_trade_ExchInFee = DSTCommonFunctions::convertToDouble( dstrExchInFee );
   if( dec_trade_ExchInFee == 0 && dec_default_ExchInFee != 0 )
   {
      dstrExchInFeeDefType.strip();
      if( dstrExchInFeeDefType == I_( "0" ) )  // flat
      {
         setFieldNoValidate( ifds::ExchInFee, dstrExchInFeeDefault, idDataGroup, false, true, true );
         setFieldNoValidate( ifds::ExchInFlatPercent, I_("Y"), idDataGroup, false, true, true );
      }
      else if( dstrExchInFeeDefType == I_( "1" ) ) // percent
      {
         setFieldNoValidate( ifds::ExchInFee, dstrExchInFeeDefault, idDataGroup, false, true, true );
         setFieldNoValidate( ifds::ExchInFlatPercent, I_("N"), idDataGroup, false, true, true );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY()); 

}

//-------------------------------------------------------------------------------------//-------------------------------------------------------------------------------------
bool Systematic::clearStatusFundToClassToAccountTo(const BFDataGroupId& idDataGroup )
{
   DString str1,str2,str3;
   getField(ifds::ClassToCode,str1,idDataGroup,false);
   str1.strip();
   getField(ifds::FundToCode,str1,idDataGroup,false);
   str2.strip();

   getField(ifds::AccountTo,str2,idDataGroup,false);
   str3.strip().stripLeading('0');

   if( str3.empty() && str1.empty() && str2.empty() )
   {
      clearFieldErrors( ifds::AccountTo, idDataGroup );
      clearFieldErrors( ifds::ClassToCode, idDataGroup );
      clearFieldErrors( ifds::FundToCode, idDataGroup );
      long lState = BFCBO::STATE_FLAGS::UPDATED | BFCBO::STATE_FLAGS:: VALID;
      const BFFieldId idField[] = {ifds::AccountTo,ifds::FundToCode,ifds::ClassToCode};
      for( int i = 0; i<3; i++ )
      {
         setFieldUpdated( idField[i], idDataGroup, true );
         setFieldValid( idField[i], idDataGroup, true );
         notifyObservers( idField[i], idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_STATE_CHANGE, I_( "" ));
      }
      return(true);
   }
   return(false);
}

//*******************************************************************************
SEVERITY Systematic::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   // Modification on existing Systematic
   if( !isNew() && isUpdatedForDataGroup (idDataGroup, false ) )
   {
      DString dstrTransType;
      getField(ifds::TransType, dstrTransType, idDataGroup, false);
      validateAccountClosedCountry(dstrTransType, idDataGroup);   
   }
   // for AT
   if( findTransType( idDataGroup, AUTO_TRFER ) )
   {
      DString strTemp1,strTemp(strValue);
      strTemp.strip();

      if( idField == ifds::AccountTo )
      {
         validateAccountTo( strTemp, idDataGroup );
         //setupDefaultAllocationList( idDataGroup);
      }
      else if( idField == ifds::FundToCode )
      {
         ValidateFundToCode(strTemp,idDataGroup);
         revalidateField(ifds::ToSoftCapCheck, idDataGroup);
      }
      else if (idField == ifds::ClassToCode)
      {
          revalidateField(ifds::ToSoftCapCheck, idDataGroup);
      }
      else if( idField == ifds::AtFundtoClasstoCrossEdit )
      {
         validateFundClassTransferAllowed(idDataGroup);  
      }
      else if( idField == ifds::FundToClassToAccountTo )
      {
         ValidateFundToClassToAccountTo(idDataGroup );
         clearStatusFundToClassToAccountTo(idDataGroup );
         //setObjectAsNew();
      }
   }
   if( idField  == ifds::AmountTypeCrossEdit )
   {
      validateAmountTypeCrossEdit(idDataGroup);
   }
   else if( idField == ifds::EffectiveDate )
   {
      ValidateEffectiveDate(strValue, idDataGroup);
   }
   else if( idField == ifds::BankInformation && PayTypeIsEFT( idDataGroup ) )
   {
      DString dstrTransType, dstrPayType;
      getField(ifds::TransType, dstrTransType, idDataGroup, false);
      getField(ifds::PayType,   dstrPayType,   idDataGroup, false);
      if( dstrTransType.strip().upperCase() != I_("AT") && dstrPayType == I_("E") )
         ValidateBankInformation(idDataGroup);
   }
   else if( idField == ifds::FundCode )
   {
      validateFundCode( strValue, idDataGroup);
   }
   else if( idField == ifds::ClassCode )
   {
      DString dstrFundCode;
      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      validateClassCode( dstrFundCode, strValue, idDataGroup);
   }
   else if( idField == ifds::FrFundNumber || idField == ifds::ToFundNumber )
   {
      DString dstrFundNumber(strValue);
      if( dstrFundNumber.strip() != NULL_STRING )
      {
         DString dstrFundCode,dstrClassCode;
         if( !getWorkSession().GetFundClassCode( strValue,dstrFundCode,dstrClassCode) )
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );
      }
   }
   else if (idField == ifds::BankAcctCurrency)            //trigger the amount checking
   {
      setValidFlag (ifds::Amount,  idDataGroup, false);
      validateCurrency (strValue, idDataGroup);
   }
   else if( idField == ifds::AddrCode )
   {
      ValidateAddrCode(strValue, idDataGroup);
   }
   else if( idField == ifds::PayTypeAddrCode )        //Cross Checking
   {
      SEVERITY sevRtn = getErrorState(ifds::AddrCode, idDataGroup);
      if( sevRtn < WARNING )
      {
         DString dstrAddrCode;
         getField(ifds::AddrCode, dstrAddrCode, idDataGroup, false);
         ValidateAddrCode(dstrAddrCode, idDataGroup);
      }
   }
   else if( idField == ifds::CompoundDate )
   {
      DString dstrStatusCode;
      getField(ifds::StatusCode, dstrStatusCode, idDataGroup);
      if( dstrStatusCode == YES )
      {
         ValidateDate( idField, idDataGroup );
      }
   }
   else if( idField == ifds::BrokerCode )
   {
      ValidateBrokerCode(strValue, idDataGroup);
   }
   else if( idField == ifds::BranchCode )
   {
      ValidateBranchCode(strValue, idDataGroup);
   }
   else if( idField == ifds::SalesRepCode )
   {
      ValidateSalesRepCode(strValue, idDataGroup);
   }
   else if( idField == ifds::SystematicCrossField2 )     //TransType and PayType cross checking
   {
      DString dstrTransType;
      getField(ifds::TransType, dstrTransType, idDataGroup, false);
      ValidateTransType(dstrTransType, idDataGroup);
      setValidFlag(ifds::Amount,  idDataGroup, false);
      //setValidFlag(DBR::BankInformation,  idDataGroup, false);
      validateAccountClosedCountry(dstrTransType, idDataGroup);
   }
   else if( idField == ifds::PayType )
   {
      DString dstrTransType;
      getField(ifds::TransType, dstrTransType, idDataGroup, false);

      if( dstrTransType != AUTO_TRFER && dstrTransType != SAVING_PLAN )
      {
         ValidatePayType(strValue, idDataGroup);
      }
      ValidateFundClass ( idDataGroup );
   }
   else if( idField == ifds::Amount )
   {
      ValidateAmount(strValue, idDataGroup);
	 
	  DString dstrRDREnv;
	  getWorkSession().getOption ( ifds::RDREnv,dstrRDREnv,idDataGroup,false);
	  
	  DString strLastProcessDate;
	  getField( ifds::LastProcessDate, strLastProcessDate, idDataGroup, false );

	  if( dstrRDREnv == I_("Y") && !isNew() && !strLastProcessDate.empty())
      {
		  validateRDRAdviceForAmt(strValue, idDataGroup);
	  }
   }
   else if( idField == ifds::AmountType )
   {
      ValidateAmountType(strValue, idDataGroup);
   }
   else if( idField == ifds::GrossOrNet )
   {
      ValidateGrossOrNet(strValue, idDataGroup);
   }
   else if( idField == ifds::SrcOfFund )
   {
      ValidateSrcOfFund(strValue, idDataGroup);
   }
   else if( idField == ifds::Fee )
   {
      ValidateFee(strValue, idDataGroup);
	  
	  if( _featureSplitComm == COMMISSION_TYPE_ONE )
	  {
		  DString dstrFundCode, dstrClassCode;
		  getField( ifds::FundCode,  dstrFundCode,  idDataGroup, false);
		  getField( ifds::ClassCode, dstrClassCode, idDataGroup, false);

		  SysAllocationList *pSysAllocationList = NULL;
		  getSysAllocationList(pSysAllocationList);

		  BFData matchCriteria;
		  BFObjIter iter(*pSysAllocationList, idDataGroup, true);

		  while(!iter.end())
		  {
			  SysAllocation* pSysAllocation = dynamic_cast<SysAllocation*>(iter.getObject());

			  if (pSysAllocation)
			  {
				  SplitCommissionList *pSplitCommissionList = NULL;

				  pSysAllocation->getSplitCommissionList(pSplitCommissionList, idDataGroup);

				  if (pSplitCommissionList)
				  {
					  DString initialTotalRate,maxFee,dstrFee;
					  pSplitCommissionList->getField (ifds::Fee, maxFee, idDataGroup, false);
					  pSplitCommissionList->getInitialTotalRate (initialTotalRate, idDataGroup);

					  getField( ifds::Fee, dstrFee, idDataGroup, false);

					  double dMaxFee = DSTCommonFunctions::convertToDouble (maxFee),
						  dFee = DSTCommonFunctions::convertToDouble (dstrFee),
						  dInitialTotalRate = DSTCommonFunctions::convertToDouble (initialTotalRate);

					  SplitCommissionList::canFeeBeDiscounted ( pSplitCommissionList,
																getWorkSession (), 
																dFee, 
																dInitialTotalRate,
																dMaxFee, 
																idDataGroup);
				  }
			  }
			  ++iter;
		  }
	  }
   }
   else if( idField == ifds::FlatPercent )   // feepercent????
   {
		ValidateFeePercent(strValue, idDataGroup);
   }
   else if( idField == ifds::FundClass )
   {
      ValidateFundClass(idDataGroup);
      validateFundClassPayout(idDataGroup);
   }
   else if( idField == ifds::AdminFeeAmt )
   {
      ValidateAdminFee(strValue, idDataGroup);
   }
   else if( idField == ifds::AdminFeeCurr )
   {
      ValidateAdminFeeCurr(strValue, idDataGroup);
   }
   else if( idField == ifds::SystematicCrossField1 )     //Fee cross checking
   {
      SEVERITY sevRtn = getErrorState(ifds::Fee, idDataGroup);
      if( sevRtn < WARNING )
      {
         DString dstrFee;
         getField(ifds::Fee, dstrFee, idDataGroup, false);
         ValidateFee(dstrFee, idDataGroup);
      }
   }
   //else if (idField == DBR::MonthIndicator)
   else if( idField == ifds::Frequency )
   {
      ValidateMonthlyIndicator(strValue, idDataGroup);
   }
   else if( idField == ifds::DayOfWeek )
   {
      DString dstrFreq;
      getField(ifds::Frequency, dstrFreq, idDataGroup, false);
      dstrFreq.strip();
      if( dstrFreq == FREQ_WEEKLY || dstrFreq == FREQ_BIWEEKLY )
      {
         DString dstrDayOfWeek(strValue);
         if( dstrDayOfWeek.strip() == NULL_STRING || dstrDayOfWeek.strip() == I_("0") )
            ADDCONDITIONFROMFILE( CND::ERR_DAYOFWEEK_REQUIRED );
      }
   }
   else if( idField == ifds::AllocationFromFund )
      ValidateAllocation(idDataGroup);
   else if( idField == ifds::VUBFee )
   {
      if( !VUBFeeTypeIsPercentage( idDataGroup ) )
      {
         if( !isValidFraction( strValue ) )
            ADDCONDITIONFROMFILE( CND::ERR_WRONG_FRACTION_FORMAT );
      }
   }
   else if( idField == ifds::VUBCrossedit )
   {
      DString tmp;

      getField(ifds::InitialAmt, tmp, idDataGroup, true);
      ValidateInitialAmt(tmp, idDataGroup);
   }
   else if( idField == ifds::BELFee )
   {
      SEVERITY sevRtn = validateBELFee ( strValue, idDataGroup );
   }
   else if( idField == ifds::ExchInFeeFlatPercent )
   {
      validateExchInFee( idDataGroup ); 
   }
   else if( idField == ifds::TransType )
   {
      validateTransType(idDataGroup);
   }
   else if(idField == ifds::ExchOutFee ||
      idField == ifds::ExchOutFlatPrcnt)
   {
      validateExchOutFee(idDataGroup);
   } 
   else if ( idField == ifds::StopDate ) 
   {
      if( findTransType( idDataGroup, PAC ) ) 
      {
         if ( _pSysAllocationList->hasCappedFund ( idDataGroup ) ) 
         {
            cappedDateRule ( idDataGroup );
         }
      } 
      else if ( findTransType ( idDataGroup, AUTO_TRFER ) ) 
      {
         BFObjIter iter(*_pAtAcctAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         BFAbstractCBO *pBFCBO;
         AutoTransAllocationList *pAtAllocationList;
         while( !iter.end() ) 
         {
            pBFCBO = iter.getObject();
            if( pBFCBO ) 
            {
               dynamic_cast<AutoAcctTransAllocation*>(pBFCBO)->getAtAllocationList(pAtAllocationList);
               if( pAtAllocationList->hasCappedFund ( idDataGroup ) ) 
               {
                  cappedDateRule ( idDataGroup );
                  //Capped fund rule is applied we can break, no need to apply twice.
                  break;
               }
            }
            ++iter;
         }
      }

      ValidateFundClass ( idDataGroup );
   }
   else if ( ifds::FedTaxRatePUD == idField )
   {
		// If TaxPUDOverride is 'Percentage Override', then make sure the value is between 0 and 100
		// If TaxPUDOverride is 'Amount Override', then make sure the value is positive
      DString dstrFedTaxPUDOverride, dstrFedRate;
		getField( ifds::FedTaxPUDOverride, dstrFedTaxPUDOverride, idDataGroup );
		getField( ifds::FedRate,           dstrFedRate,           idDataGroup );
		dstrFedTaxPUDOverride.strip();
		dstrFedRate.strip();

		validateTaxPUDOverride( dstrFedTaxPUDOverride, dstrFedRate, idDataGroup );	
	}
	else if ( ifds::FedTaxRateAmountPUDXEdit == idField )
	{
		// If TaxPUDOverride is 'Amount Override', then make sure is less than Transaction Amount
		// when Trade Amount Type is Dollar
		DString dstrFedTaxPUDOverride, dstrFedRate;
		getField( ifds::FedTaxPUDOverride, dstrFedTaxPUDOverride, idDataGroup );
		getField( ifds::FedRate,           dstrFedRate,           idDataGroup );
		dstrFedTaxPUDOverride.strip();
		dstrFedRate.strip();

		validateTaxAmountPUDOverride( dstrFedTaxPUDOverride, dstrFedRate, idDataGroup );	
	}
	else if ( ifds::ProvTaxRatePUD == idField )
	{
		// If TaxPUDOverride is 'Percentage Override', then make sure the value is between 0 and 100
		// If TaxPUDOverride is 'Amount Override', then make sure the value is positive.
		DString dstrProvTaxPUDOverride, dstrProvRate;
		getField( ifds::ProvTaxPUDOverride, dstrProvTaxPUDOverride, idDataGroup );
		getField( ifds::ProvRate,           dstrProvRate,           idDataGroup );
		dstrProvTaxPUDOverride.strip();
		dstrProvRate.strip();

		validateTaxPUDOverride( dstrProvTaxPUDOverride, dstrProvRate, idDataGroup );	
	}
	else if ( ifds::ProvTaxRateAmountPUDXEdit == idField )
	{
		// If TaxPUDOverride is 'Amount Override', then make sure the value is less than Transaction Amount
		// when Trade Amount Type is Dollar
		DString dstrProvTaxPUDOverride, dstrProvRate;
		getField( ifds::ProvTaxPUDOverride, dstrProvTaxPUDOverride, idDataGroup );
		getField( ifds::ProvRate,           dstrProvRate,           idDataGroup );
		dstrProvTaxPUDOverride.strip();
		dstrProvRate.strip();

		validateTaxAmountPUDOverride( dstrProvTaxPUDOverride, dstrProvRate, idDataGroup );	
	}
	else if ( ifds::FedProvTaxPercPUDXEdit == idField )
	{
		// If both Tax Types are percent check if all together they exceed 100%
		DString dstrFedTaxPUDOverride, dstrProvTaxPUDOverride;
		getField( ifds::FedTaxPUDOverride,  dstrFedTaxPUDOverride,  idDataGroup );
		getField( ifds::ProvTaxPUDOverride, dstrProvTaxPUDOverride, idDataGroup );
		// If Percentage Override...
		if ( I_( "2" ) == dstrFedTaxPUDOverride.strip() &&
			  I_( "2" ) == dstrProvTaxPUDOverride.strip() )
		{
			DString dstrFedRate, dstrProvRate;		
			getField( ifds::FedRate,  dstrFedRate,  idDataGroup );		
			getField( ifds::ProvRate, dstrProvRate, idDataGroup );
					
			double dblFedRateAmount = DSTCommonFunctions::convertToDouble( dstrFedRate );
			double dblProvRateAmount = DSTCommonFunctions::convertToDouble( dstrProvRate );

			if ( dblFedRateAmount + dblProvRateAmount > 100 )
			{
				// Total Tax Rate cannot be greater than 100%.
				ADDCONDITIONFROMFILE( CND::ERR_REDEMPTION_TOTAL_TAX_RATE_GREATER_THAN_100 );
			}			
		}		
	}
	else if ( ifds::FedProvTaxRatePUDXEdit == idField )
	{		
		DString dstrFedTaxPUDOverride, dstrProvTaxPUDOverride;
		getField( ifds::FedTaxPUDOverride,  dstrFedTaxPUDOverride,  idDataGroup );
		getField( ifds::ProvTaxPUDOverride, dstrProvTaxPUDOverride, idDataGroup );

		DString dstrAmountType;
		getField( ifds::AmountType, dstrAmountType, idDataGroup );
		if ( I_( "D" ) == dstrAmountType.strip().upperCase() )
		{
			DString dstrFedRate, dstrProvRate, dstrAmount;		
			getField( ifds::FedRate,  dstrFedRate,  idDataGroup );		
			getField( ifds::ProvRate, dstrProvRate, idDataGroup );
			getField( ifds::Amount,   dstrAmount,   idDataGroup );
						
			double dblFedRateAmount  = DSTCommonFunctions::convertToDouble( dstrFedRate );
			double dblProvRateAmount = DSTCommonFunctions::convertToDouble( dstrProvRate );
			double dblAmount         = DSTCommonFunctions::convertToDouble( dstrAmount );

			// If both Tax Types are Amount and Trade Amount Type is Dollar, make sure 
			// the total does not exceed the Trade Amount
			if ( I_( "1" ) == dstrFedTaxPUDOverride.strip() &&
				  I_( "1" ) == dstrProvTaxPUDOverride.strip() )
			{							
				if ( dblFedRateAmount + dblProvRateAmount > dblAmount)
				{
					// Total Tax Amount cannot be greater than Amount.
					ADDCONDITIONFROMFILE( CND::ERR_TOTAL_TAX_AMOUNT_GREATER_THAN_AMOUNT );
				}			
			}					

			// If Fed Tax is Amount and Prov Tax is Percent, make sure the total is less than Trade Amount
			if ( I_( "1" ) == dstrFedTaxPUDOverride.strip() &&
				  I_( "2" ) == dstrProvTaxPUDOverride.strip() )
			{			
				double dblWHTaxAmount = dblFedRateAmount + dblProvRateAmount * dblAmount / 100;
				if ( dblWHTaxAmount > dblAmount)
				{
					// Total Tax Amount cannot be greater than Amount.
					ADDCONDITIONFROMFILE( CND::ERR_TOTAL_TAX_AMOUNT_GREATER_THAN_AMOUNT );
				}			
			}				

			// If Fed Tax is Percentage and Prov Tax is Amount, make sure the total is less than Trade Amount
			if ( I_( "2" ) == dstrFedTaxPUDOverride.strip() &&
				  I_( "1" ) == dstrProvTaxPUDOverride.strip() )
			{			
				double dblWHTaxAmount = dblFedRateAmount * dblAmount / 100 + dblProvRateAmount;
				if ( dblWHTaxAmount > dblAmount)
				{
					// Total Tax Amount cannot be greater than Amount.
					ADDCONDITIONFROMFILE( CND::ERR_TOTAL_TAX_AMOUNT_GREATER_THAN_AMOUNT );
				}			
			}		
		}			
		else
		{
			// If both taxes have No Override flag on, then there is no need for the warning
			if ( I_( "0" ) != dstrFedTaxPUDOverride.strip() ||
				  I_( "0" ) != dstrProvTaxPUDOverride.strip() )
			{
				// Tax Rates can not be checked when the Trade Amount is not Dollars
				ADDCONDITIONFROMFILE( CND::WARN_NO_CHECK_ON_TAXRATE_FOR_NON_DOLLAR_AMTTYPE );
			}
		}
	}
   else if (idField == ifds::ToSoftCapCheck)
   {
      validateToSoftCapCheck (idDataGroup);
   }
   else if (idField == ifds::FromSoftCapCheck)
   {
      validateFromSoftCapCheck (idDataGroup);
   }
   else if (idField == ifds::FromToFundClassAcctTo)
   {
      validateFromToFundClassAcctTo(idDataGroup);
   }
   else if(idField == ifds::SrcOfFundSrcOfAcctXEdit)
   {//P0186486_FN15_The Source of Funds
      ValidateSourceOfBankAcct(idDataGroup);
   }
   else if (idField == ifds::CalcAmountXEdit)
   {
      bool bAmountReadOnly = false;
      DString dstrAmountType;

      getField (ifds::AmountType, dstrAmountType, idDataGroup, false);

      if (DSTCommonFunctions::codeInList ( dstrAmountType, GWLWA_OPTIONS))
      {
         calculateAmount (dstrAmountType, idDataGroup);
         bAmountReadOnly = true;
      }

      setFieldReadOnly (ifds::Amount, idDataGroup, bAmountReadOnly );
   }
   else if (idField == ifds::LGFundClassXEdit)
   {
      DString dstrFundCode;
      DString dstrClassCode;

      getField( ifds::FundCode, dstrFundCode, idDataGroup,false );
      getField( ifds::ClassCode, dstrClassCode, idDataGroup,false );
      dstrFundCode.strip().upperCase();
      dstrClassCode.strip().upperCase();

      validateGMWB (dstrFundCode, dstrClassCode, idDataGroup);

      if (!dstrFundCode.empty() && !dstrClassCode.empty())
      {
         DString strListAmttype,
            dstrAmountType,
            dstrTransTypeFmt;
         getValidListAmountTypeByFund (dstrFundCode,dstrClassCode,strListAmttype,idDataGroup);
         getField (ifds::AmountType, dstrAmountType, idDataGroup, false);
         getField (ifds::TransType, dstrTransTypeFmt, idDataGroup, true);

         dstrAmountType.strip().upperCase();

         //if (DSTCommonFunctions::codeInList (dstrAmountType, GWLWA_OPTIONS) && 
         //   !strListAmttype.empty())
         if (!strListAmttype.empty())
         {
            // if amount type is not in the list of valid amount type by fund class
            // then raise up an error
            // assume that back-end would return all of valid amount type
            if (!DSTCommonFunctions::codeInList (dstrAmountType, strListAmttype))
            {
               DString dstrTemp;
               addIDITagValue( dstrTemp, I_("TRANS_TYPE"), dstrTransTypeFmt);
               getErrMsg(IFASTERR::INVALID_AMOUNT_TYPE_BY_SEG_RULES, 
                         CND::ERR_INVALID_AMOUNT_TYPE_BY_SEG_RULES, 
                         CND::WARN_INVALID_AMOUNT_TYPE_BY_SEG_RULES,
                         idDataGroup,
                         dstrTemp);
            }
         }
      }
   }
    else if(idField == ifds::RDRAdvice) 
   {
       DString dstrRDRAdvice;
	   getField (ifds::RDRAdvice, dstrRDRAdvice, idDataGroup, false);
	   if( dstrRDRAdvice != _strRDRAdviceFlag )
	   {
		   ADDCONDITIONFROMFILE (CND::WARN_RDR_ADVICE_UPDATED);
	   }
   }
   else if( idField == ifds::EventReceiptDate || idField == ifds::EventReceiptTime )
   {
    DString dstrEventReceiptDate,dstrEventReceiptTime,dstrTemp;
	bool bEventReceiptDateTimeAppl = bIsEventReceiptDateTimeAppl(idDataGroup); 
	getField(ifds::EventReceiptDate, dstrEventReceiptDate, idDataGroup, false);
	getField(ifds::EventReceiptTime, dstrEventReceiptTime, idDataGroup, false);
	dstrEventReceiptDate.stripAll();
    dstrEventReceiptTime.stripAll();
 	//invalidate the field so that crossedit will be called  after fields validation
	setFieldValid(ifds::EventReceiptDate, idDataGroup, false);
	setFieldValid(ifds::EventReceiptTime, idDataGroup, false );
	if ( !dstrEventReceiptDate.empty() && bEventReceiptDateTimeAppl )
	{ 
		DString dstrCurrentSysDate;
        getWorkSession().getDateInHostFormat(dstrCurrentSysDate, DSTCWorkSession::DATE_TYPE::CURRENT_SYSTEM_DAY, idDataGroup);  
		// Event reciept date cannot future dated 
		if (DSTCommonFunctions::CompareDates (dstrCurrentSysDate, dstrEventReceiptDate) == DSTCommonFunctions::FIRST_EARLIER)
		{
	    	addIDITagValue( dstrTemp, I_("FieldName"), I_("Event Receipt Date"));
			ADDCONDITIONFROMFILEIDI( CND::ERR_FUTURE_DATE, dstrTemp );
		}
	}
	if ( !dstrEventReceiptTime.empty() && bEventReceiptDateTimeAppl )
	{
		if(!DSTCommonFunctions::bValidateTime(dstrEventReceiptTime))
		{
			DString dstrTemp;
			addIDITagValue( dstrTemp, I_("FORMAT"), I_("HH:MM:SS"));
            ADDCONDITIONFROMFILEIDI(CND::ERR_INVALID_TIME_FORMAT,dstrTemp)
		}
	}
	if(GETCURRENTHIGHESTSEVERITY () <= WARNING )
	{
		setFieldValid(ifds::EventReceiptDate, idDataGroup, true);
		setFieldValid(ifds::EventReceiptTime, idDataGroup, true );
	}
   }
   else if (idField == ifds::XEditEventRecieptDateTime )
   {
     bool bEventReceiptDateTimeAppl = bIsEventReceiptDateTimeAppl(idDataGroup);
     if(bEventReceiptDateTimeAppl)
	 {
		DString dstrEventReceiptDate,dstrEventReceiptTime,dstrTemp;
		getField(ifds::EventReceiptDate, dstrEventReceiptDate, idDataGroup, false);
		getField(ifds::EventReceiptTime, dstrEventReceiptTime, idDataGroup, false);
		if ( dstrEventReceiptDate.stripAll().empty())
		{
			addIDITagValue( dstrTemp, I_("FieldName"), I_("Event Receipt Date"));
			ADDCONDITIONFROMFILEIDI( CND::ERR_REQ_FIELD_EMPTY, dstrTemp );
		}
		else if ( dstrEventReceiptTime.stripAll().empty() )
		{
			addIDITagValue( dstrTemp, I_("FieldName"), I_("Event Receipt Time"));
			ADDCONDITIONFROMFILEIDI( CND::ERR_REQ_FIELD_EMPTY, dstrTemp );
		}
	 }
   }
   if( ifds::StopDate == idField || ifds::SignatureDate == idField || ifds::EffectiveDate == idField )
   {
	DString dstrSignatureDate, dstrEffectiveDate, dstrCurrentBusinessDate, idiStr, 
			dstrTransType, dstrStopDate, dstrOrgStopDate, dstrLastProcessDate, dstrDisplayDate;
	getField(ifds::TransType, dstrTransType, idDataGroup, false);

	if(PAC == dstrTransType)
	{
	 getField(ifds::SignatureDate, dstrSignatureDate, idDataGroup, false);
	 getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
	 getField(ifds::LastProcessDate, dstrLastProcessDate, idDataGroup, false);
	 getField(ifds::StopDate, dstrStopDate, idDataGroup, false);
	 getFieldBeforeImage(ifds::StopDate, dstrOrgStopDate, false);
	 getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );

	 if(DSTCommonFunctions::FIRST_EARLIER == DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrSignatureDate )&&
		NULL_STRING != dstrSignatureDate )
	   {
		idiStr = NULL_STRING;
		dstrDisplayDate = dstrSignatureDate;
		DSTCommonFunctions::formatToolTipDate( ifds::SignatureDate, dstrDisplayDate );
		addIDITagValue( idiStr, I_("DATE1"), dstrDisplayDate );
		dstrDisplayDate = dstrEffectiveDate;
		DSTCommonFunctions::formatToolTipDate( ifds::EffectiveDate, dstrDisplayDate );
		addIDITagValue( idiStr, I_("DATE2"), dstrDisplayDate );
		getErrMsg (IFASTERR::SIGNATURE_DATE_LATER, CND::ERR_SIGNATURE_DATE_LATER, CND::WARN_SIGNATURE_DATE_LATER, 
				   idDataGroup, idiStr);
	   }  

     if(NULL_STRING != dstrLastProcessDate && NULL_STRING != dstrStopDate && NULL_STRING != dstrOrgStopDate &&
	   (DSTCommonFunctions::FIRST_EARLIER == DSTCommonFunctions::CompareDates( dstrStopDate, dstrCurrentBusinessDate )||
	    DSTCommonFunctions::FIRST_EARLIER == DSTCommonFunctions::CompareDates( dstrOrgStopDate, dstrStopDate )))
	   {
	    idiStr = NULL_STRING;
		dstrDisplayDate = dstrCurrentBusinessDate;
		DSTCommonFunctions::formatToolTipDate( ifds::StopDate, dstrDisplayDate );
	    addIDITagValue( idiStr, I_("DATE1"), dstrDisplayDate);
		dstrDisplayDate = dstrOrgStopDate;
		DSTCommonFunctions::formatToolTipDate( ifds::StopDate, dstrDisplayDate );
		addIDITagValue( idiStr, I_("DATE2"), dstrDisplayDate );
	    getErrMsg (IFASTERR::PAC_STOP_DATE_RESTRICTION, CND::ERR_PAC_STOP_DATE_RESTRICTION, CND::WARN_PAC_STOP_DATE_RESTRICTION, 
				   idDataGroup, idiStr);
	   }
	}
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************
void Systematic::ValidateMonthlyIndicator(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateMonthlyIndicator" ) );

   DString dstrFreq;

   getField(ifds::Frequency, dstrFreq, idDataGroup, false);
   dstrFreq.strip();
   if( dstrFreq == FREQ_WEEKLY || dstrFreq == FREQ_BIWEEKLY || dstrFreq == FREQ_DAILY )
      return;

   DString dstrIndicator( strValue ), dstrTemp;
   dstrIndicator.strip().upperCase();

   DString dstrFreqDesc, idiStr;
   getField(ifds::Frequency, dstrFreqDesc, idDataGroup, true);

   if( dstrIndicator == I_("NNNNNNNNNNNN") &&
       (dstrFreq == FREQ_MONTHLY || dstrFreq == FREQ_QUARTERLY || dstrFreq == FREQ_OTHER) )
   {
      addIDITagValue( idiStr, FREQUENCY, dstrFreqDesc );
      ADDCONDITIONFROMFILEIDI( CND::ERR_AT_LEAST_ONE_MONTH_MUST_ACTIVE, idiStr );
   }

   DString dstrIndexExist;
   getField( ifds::IndexExist, dstrIndexExist, idDataGroup, false);   
   if( dstrIndexExist == YES )
   {
      SysIndexList *pSysIndexList;
      if( getSystematicIndexList( idDataGroup, pSysIndexList ) <= WARNING )
      {
         if( pSysIndexList->activeIndex( idDataGroup ) )
         {
            ADDCONDITIONFROMFILE( CND::ERR_INDEXING_EXISTS );
         }
      }
   }
}

//**********************************************************

void Systematic::ValidateBankInformation(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateBankInformation" ) );

   DString dstrBankAcctNum, dstrBankAcctType, dstrBankIDValue, dstrBankIDType, dstrTransitNo, dstrSwiftCode, dstrRefNumber;
   DString dstrFieldId;
   DString dstrBankingFormat;

   getField(ifds::BankAcctNum,    dstrBankAcctNum,  idDataGroup, false);
   getField(ifds::BankAcctType,   dstrBankAcctType, idDataGroup, false);
   getField(ifds::BankIdValue,      dstrBankIDValue,  idDataGroup, false);
   getField(ifds::BankIdType,     dstrBankIDType,   idDataGroup, false);
   getField(ifds::TransitNo,      dstrTransitNo,    idDataGroup, false);
   getField(ifds::SwiftCode,      dstrSwiftCode,    idDataGroup, false);
   getField(ifds::RefNumber,      dstrRefNumber,    idDataGroup, false);


   //Validate BankAccountType
   DString dstrCfgBankLayout;   // dstrCfgBankValid1, dstrCfgBankValid2;
   _pMgmtCoOption->getField( ifds::BankLayout, dstrCfgBankLayout, BF::HOST );
   //_pMgmtCoOption->getField( DBR::BankValid1, dstrCfgBankValid1, BF::HOST );
   //_pMgmtCoOption->getField( DBR::BankValid2, dstrCfgBankValid2, BF::HOST );
   //_pMgmtCoOption->getField( DBR::BankingFormat, dstrBankingFormat, BF::HOST );
   dstrCfgBankLayout.strip();
   //dstrCfgBankValid1.strip();
   //dstrCfgBankValid2.strip(); 

   //Validate Bank Account Number
   SEVERITY sevRtn = getErrorState(ifds::BankInformation, idDataGroup);

   if( sevRtn < WARNING && dstrBankAcctNum.strip() == NULL_STRING )
   {

      ADDCONDITIONFROMFILE( CND::ERR_BANK_ACCT_NUM_CANNOT_BE_BLANK );
   }
   else
   {
      DString dstrBankAcctNumMax;
      _pMgmtCoOption->getField( ifds::BankAcctNumMax, dstrBankAcctNumMax, BF::HOST );
      unsigned int iBankAcctNumMax = convertToULong( dstrBankAcctNumMax );

      // TODO dstrBankAcctNum.strip().length() returns a DString::size_type, which
      // is unsigned.  This must be reconciled with iBankAcctNumMax, which is signed.
      if( YES == dstrBankingFormat && iBankAcctNumMax > 0 && 
          dstrBankAcctNum.strip().length() > iBankAcctNumMax )
      {
         ADDCONDITIONFROMFILE( CND::ERR_BANKACCTNUM_TOO_BIG );
      }
   }



   /**** else   (Validation is done by BankInstr.cpp)
  {
      DString strInstCodeMax;
      _pMgmtCoOption->getField( DBR::InstCodeMax, strInstCodeMax, BF::HOST );
      int instCodeMax = convertToULong( strInstCodeMax );
      if( YES == dstrBankingFormat && instCodeMax > 0 && dstrInstCode.length() > instCodeMax )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INSTCODE_TOO_BIG );
      }
      else if//only check if it exists if it is in range
       ( (dstrCfgBankValid1 == I_("1") || dstrCfgBankValid1 == I_("3")) && 
            !IsThisValueExistInBankList( DBR::InstCode, dstrInstCode) )
      {
       ADDCONDITIONFROMFILE( CND::ERR_INSTCODE_NOT_EXIST );
      }
  } ****/


   /* else (handled by BankInstr.cpp)
   {
      
      DString strTransitNoMax;
      _pMgmtCoOption->getField( DBR::TransitNoMax, strTransitNoMax, BF::HOST );
      int transitNoMax = convertToULong( strTransitNoMax );
      if( YES == dstrBankingFormat && transitNoMax > 0 && dstrTransitNo.length() > transitNoMax )
      {
         ADDCONDITIONFROMFILE( CND::ERR_TRANSITNO_TOO_BIG );
      }  
      else if//only check if it exists if it is in range
         ( ( (dstrCfgBankLayout == I_("3") && dstrCfgBankValid1 == I_("3") ) ||
        ( (dstrCfgBankLayout == I_("1") || dstrCfgBankLayout == I_("2") ) && 
         (dstrCfgBankValid1 == I_("1") || dstrCfgBankValid1 == I_("3") ) &&
          dstrCfgBankValid2 == I_("Y") ) && 
             !IsThisValueExistInBankList( DBR::TransitNo, dstrTransitNo) ) )
    {
        ADDCONDITIONFROMFILE( CND::ERR_TRANSITNO_NOT_EXIST );
     }
   }***/

   /*/Validate the SwiftCode
   dstrSwiftCode.strip();
  if ((dstrCfgBankLayout == I_("1") || dstrCfgBankLayout == I_("2")) && dstrSwiftCode == NULL_STRING)
  {
    DP::getFieldNameFromId( DBR::SwiftCode, dstrFieldId );
      if (dstrRequiredFieldNames != NULL_STRING)
         dstrRequiredFieldNames += I_(",");
      dstrRequiredFieldNames += dstrFieldId;
  }
  else if( (dstrCfgBankLayout == I_("1") || dstrCfgBankLayout == I_("2") ) && 
          (dstrCfgBankValid1 == I_("1") || dstrCfgBankValid1 == I_("3") ) &&
           !IsThisValueExistInBankList( DBR::SwiftCode, dstrSwiftCode) ) 
  {
     ADDCONDITIONFROMFILE( CND::ERR_SWIFTCODE_NOT_EXIST);
  }
   //Validate the RefNumber
   dstrRefNumber.strip();
  if ((dstrCfgBankLayout == I_("1") || dstrCfgBankLayout == I_("2")) && dstrRefNumber == NULL_STRING)
  {
    DP::getFieldNameFromId( DBR::RefNumber, dstrFieldId );
      if (dstrRequiredFieldNames != NULL_STRING)
         dstrRequiredFieldNames += I_(",");
      dstrRequiredFieldNames += dstrFieldId;
  }
  else if( (dstrCfgBankLayout == I_("1") || dstrCfgBankLayout == I_("2") ) && 
     (dstrCfgBankValid1 == I_("1") || dstrCfgBankValid1 == I_("3") ) &&
     !IsThisValueExistInBankList( DBR::RefNumber, dstrRefNumber) ) 
  {
     ADDCONDITIONFROMFILE( CND::ERR_REFNUMBER_NOT_EXIST );
  }
   if (dstrRequiredFieldNames != NULL_STRING)
   {
      DString idiStr;
    addIDITagValue(idiStr, I_("BANKINFO"), dstrRequiredFieldNames );
    ADDCONDITIONFROMFILEIDI( CND::ERR_BANKINFO_REQUIRED, idiStr );
   } */

   static_cast<SystematicList*>(getParent())->checkBankCurrency( idDataGroup, this );
}

//**********************************************************

void Systematic::ValidateAddrCode(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAddrCode" ) );

   DString dstrAddrCode(strValue);
   if( dstrAddrCode.strip() == NULL_STRING )
   {
      DString dstrPayType, dstrTransType;

      getField(ifds::TransType, dstrTransType, idDataGroup, false);
      getField(ifds::PayType, dstrPayType, idDataGroup, false);
      dstrTransType.strip();
      dstrPayType.strip();
      if( dstrTransType == I_("S") && (dstrPayType == I_("C") ||
                                       dstrPayType == I_("S") ||
                                       dstrPayType == I_("M")) )
      {
         //   DString dstrFieldName;
         //  PropertyRepository::getInstance()->getFieldNameFromId( DBR::AddrCode, dstrFieldName );
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );

      }
   }
}
//**********************************************************

void Systematic::ValidateBankAccount(const DString& dstrValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateBankAccount" ) );

   DString dstrAccountNum, dstrPayType;
   dstrAccountNum = dstrValue;

   getField(ifds::PayType, dstrPayType, idDataGroup, false);
   dstrPayType.strip().upperCase();
   if( dstrPayType == I_("E") && dstrAccountNum.strip() == NULL_STRING )
   {
      //	DString FieldName;
      //   PropertyRepository::getInstance()->getFieldNameFromId( DBR::BankAcctNum, FieldName );
//CP		DP::getFieldNameFromId( DBR::BankAcctNum, FieldName );
      ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_SELECT );
      return;
   }
}

//**********************************************************

void Systematic::ValidateBankAcctType(const DString& BankAcctType)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateBankAcctType" ) );

   DString l;


   _pMgmtCoOption->getField( ifds::BankLayout, l, BF::HOST );
   if( l.strip() == I_("2")  && BankAcctType == NULL_STRING )
   {
//		DString FieldName;
//      PropertyRepository::getInstance()->getFieldNameFromId( DBR::BankAcctType, FieldName );
//CP		DP::getFieldNameFromId( DBR::BankAcctType, FieldName );
      ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_SELECT );
   }
}

//*************************************************************
void Systematic::ValidateEffectiveDate( const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup )
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateEffectiveDate" ) );

   if( findTransType( idDataGroup, AUTO_TRFER ) )
   {
      if( _pMFAccount->CheckEffectiveForAT(dstrEffectiveDate,idDataGroup) != MFAccount::ACCOUNT__SALES_REP_OK )
      {
         // add condition late
      }
   }
   else
   {
      DString dstrAcctEffecDate;
      _pMFAccount->getField(ifds::FirstEffective, dstrAcctEffecDate, idDataGroup, false);
      if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrAcctEffecDate) == DSTCommonFunctions::FIRST_EARLIER )
      {
         ADDCONDITIONFROMFILE( CND::ERR_SYS_DEFF_LESS_THAN_ACCT_DEFF );
         return;
      }

   }

   DString dstrFundCode; 
   // when user change the effective date, then check if the fund is capped as of effective date
   if( _dstrTransType == PAC || _dstrTransType == SAVING_PLAN )
   {
      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      cappedFundRule ( dstrFundCode, idDataGroup );

	  //for PAC validate residency and money in dates - TFSA project but coded generically, as per architecture's request
	  if( _dstrTransType == PAC )
      {
         DString dstrAccountNum;
         getField (ifds::AccountNum, dstrAccountNum, idDataGroup);  
         dstrAccountNum.strip().stripLeading( '0' );
         validateResidency( dstrAccountNum, idDataGroup );
         validateMoneyInDates( dstrAccountNum, dstrEffectiveDate, idDataGroup );		 	
	  }
   }
   else if ( _dstrTransType == AUTO_TRFER )
   {
      getField(ifds::FundToCode, dstrFundCode, idDataGroup, false);
      cappedFundRule ( dstrFundCode, idDataGroup );
   }
}

//*************************************************************
SEVERITY Systematic::validateMoneyInDates( const DString &dstrAccountNumber, const DString &dstrEffectiveDate, 
										   const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateDate" ) );

   MFAccount *pMFAccount = NULL;   
   DString strEffectiveDate = dstrEffectiveDate;
   DString dstrTaxType;
   //only applies for good records which have not been stopped
      DString dstrGoodBad, dstrStopDate, currBussDate;
	  getWorkSession ().getOption ( ifds::CurrBusDate, currBussDate, BF::HOST, false);
	  getField( ifds::StatusCode, dstrGoodBad, idDataGroup, false ); 
	  getField( ifds::StopDate, dstrStopDate, idDataGroup, false ); 
	  				
   if ( dstrGoodBad.strip().upperCase() == GOOD &&
        ( dstrStopDate.strip().empty() || DSTCommonFunctions::CompareDates( currBussDate, dstrStopDate ) == DSTCommonFunctions::FIRST_EARLIER ) && 
	    !strEffectiveDate.strip().empty() &&
	    getWorkSession().getMFAccount (idDataGroup, dstrAccountNumber, pMFAccount) <= WARNING && pMFAccount)
   {
	  pMFAccount->getField (ifds::TaxType, dstrTaxType, idDataGroup);
      //if( dstrTaxType.strip().upperCase() == TFSA_TAX_TYPE )
      {
         DString strStart, strEnd, strStartDesc, strEndDesc, idiStr;
		 TaxTypeRule *pTaxTypeRule = NULL;
		 if ( pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
		 {
            pTaxTypeRule->getField (ifds::TradeStartDate, strStart, idDataGroup, false);
			pTaxTypeRule->getField (ifds::TradeStopDate, strEnd, idDataGroup, false);

            if( ( !strStart.strip().empty() && DSTCommonFunctions::CompareDates (dstrEffectiveDate, strStart) == DSTCommonFunctions::FIRST_EARLIER ) ||
			    ( !strEnd.strip().empty() && DSTCommonFunctions::CompareDates (strEnd, dstrEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER ) )
            {
			   pTaxTypeRule->getField (ifds::TradeStartDate, strStartDesc, idDataGroup, true);
			   pTaxTypeRule->getField (ifds::TradeStopDate, strEndDesc, idDataGroup, true);
			   addIDITagValue (idiStr, I_("START"), strStartDesc);
			   addIDITagValue (idiStr, I_("END"), strEndDesc);
			   ADDCONDITIONFROMFILEIDI (CND::ERR_TRADE_DATE_OUTSIDE_MIN_MAX, idiStr);   
			}
         }
	  }
   }	
   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************
// group field: Effective and Stop Date
void Systematic::ValidateDate( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateDate" ) );
   DString EffectiveDate, StopDate;

   getField(ifds::EffectiveDate, EffectiveDate, idDataGroup);
   getField(ifds::StopDate, StopDate, idDataGroup);

   if( DSTCommonFunctions::CompareDates( StopDate, EffectiveDate ) 
       != DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE );
      return ;
   }
   
   checkNextProcDate( EffectiveDate, StopDate, idDataGroup );

}

//*************************************************************
void Systematic::ValidateTransType(const DString& dstrValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateTransType" ) );
   SEVERITY sevRtn = NO_CONDITION;

   DString dstrTransType(dstrValue), dstrFieldValue;
   dstrTransType.strip().upperCase();
   if( dstrTransType  != PAC  &&
       dstrTransType  != SWP  &&
       dstrTransType  != SAVING_PLAN  &&
       dstrTransType  != AUTO_TRFER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ENTRY_BOTH_FIELDS );
      return ;
   }

/*   DString dstrBatch;
   getField(ifds::BatchName, dstrBatch, idDataGroup, false);
   if( isNew() && dstrBatch.strip() == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_ACTIVE_BATCH );
      return ;
   }
*/
   if( !_pList )
   {
      _pList = dynamic_cast<SystematicList *>(getParent());
      _pMFAccount = _pList->getMFAccount();
   }

   DString idiStr, dstrTransTypeDesc, dstrEffectiveDate;
   getField(ifds::TransType, dstrTransTypeDesc, idDataGroup, true);
   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

   if( dstrTransType == PAC || dstrTransType == SAVING_PLAN )
   {
      if ( _pMFAccount->canPAC ( dstrEffectiveDate, idDataGroup ) < WARNING ) {      
         sevRtn = _pMFAccount->canPurchase( dstrEffectiveDate, idDataGroup );
         if( isNew() && sevRtn <= WARNING && _pMFAccount->validateMoneyInTFSA(idDataGroup) <= WARNING)
            sevRtn = _pMFAccount->escrowPurchase( dstrEffectiveDate, idDataGroup );
      }
   }
   if( dstrTransType == SWP )
   {
      if ( _pMFAccount->canSWP ( dstrEffectiveDate, idDataGroup ) < WARNING ) {      
         sevRtn = _pMFAccount->canRedeem ( dstrEffectiveDate, idDataGroup );

         if( sevRtn <= WARNING )
         {
            if( isNew() )
            {
               sevRtn = _pMFAccount->escrowRedeem ( dstrEffectiveDate, idDataGroup );
            }
            else
            {
               DString dstrTitleRestrict (NO);
               getWorkSession().getOption( ifds::TitleRestrict, dstrTitleRestrict, idDataGroup, false );

               if( dstrTitleRestrict == YES )
               {
                  DString acctNum;
                  getField(ifds::AccountNum, acctNum, idDataGroup);
                  acctNum.strip().stripLeading( '0' );

                  AccountEntityXref *pAccountEntityXref = NULL;

                  if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING )
                  {
                     DString strKey;

                     if( acctNum != NULL_STRING )
                        SEVERITY sevRtn = pAccountEntityXref->escrowAccount( acctNum, SWP_CHG, NULL_STRING, dstrEffectiveDate, idDataGroup);

                  } // if found AccountEntityXref
               }
            }
         }
      }

      if( sevRtn <= WARNING )
      {
         DString dstrPlanType, dstrAmountType;
         _pMFAccount->getField(ifds::PlanType, dstrPlanType, idDataGroup, false);
         dstrPlanType.strip().upperCase();
         if( dstrPlanType != I_("UNREG") )
         {
            ADDCONDITIONFROMFILE( CND::ERR_SWP_UNDER_REGISTERED_ACCT );
         }
		
		 bool bIsRDSPAccount = _pMFAccount->isRDSPAccount(idDataGroup);

		 getField(ifds::AmountType, dstrAmountType, idDataGroup);
		 dstrAmountType.strip().upperCase();
		
		 if (!bIsRDSPAccount && DSTCommonFunctions::codeInList(dstrAmountType, I_("A,N,O")) ) // A-LDAP Maximum, N-LDAP Amount, O-DAP Amount
		 {
			 ADDCONDITIONFROMFILE (CND::ERR_AMT_TYPE_NOTAPPLICABLE);
		 }
      }
   }
   if( dstrTransType == AUTO_TRFER )
   {
      if ( _pMFAccount->canATIn (dstrEffectiveDate, idDataGroup ) )
         _pMFAccount->canTrfExchOut ( dstrEffectiveDate, idDataGroup );
   }
}

//*************************************************************

void Systematic::ValidateBrokerCode(const DString& BrokerCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateBrokerCode" ) );
   DString SYMBrkUpd;

   _pMgmtCoOption->getField( ifds::SYMBrkUpd, SYMBrkUpd, BF::HOST, false );
   if( SYMBrkUpd.strip() == YES )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_CHAR );
   }
}

//*************************************************************

void Systematic::ValidateBranchCode(const DString& BranchCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateBranchCode" ) );
}

//*************************************************************

void Systematic::ValidateSalesRepCode(const DString& SalesRepCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateSalesRepCode" ) );
}

//*************************************************************
void Systematic::ValidatePayType(const DString& PayType, const BFDataGroupId& idDataGroup, const DString& dstrFundCode )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidatePayType" ) );

   if( _dstrTransType == I_("AT") ) //Paytype not applicable to Automatic Transfer.
   { 
      return;
	}

	if( PayType.empty() ) // Paytype is mandatory if it is not Automatic Transfer   if( PayType.empty() )
   {
      //	DString FieldName;
      // PropertyRepository::getInstance()->getFieldNameFromId( DBR::PayType, FieldName );
      ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_SELECT );
      return;
   }
   else
   {
      DString FundCode, str, str1;
      if( dstrFundCode == NULL_STRING )
         getField(ifds::FundCode, FundCode, idDataGroup, false);
      else
         FundCode = dstrFundCode;
      FundCode.strip().upperCase();

      FundMasterList *pFundMasterList = _pList->getFundMasterList();
      pFundMasterList->buildKey( FundCode, str );

      BFObjIter iter(const_cast<FundMasterList &>(*pFundMasterList ), BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
      if( iter.positionByKey( str ) )
      {
         iter.getObject()->getField( ifds::FundCode, str, BF::HOST, false );

         if( str.strip().upperCase() == FundCode )
         {
            iter.getObject()->getField( ifds::PACavail, str, BF::HOST, false );
            getField( ifds::TransType, str1, idDataGroup, false );
            DString idiStr;
			addIDITagValue( idiStr, FUNDNAME, FundCode );			
            if( str != YES && str1 == PAC )/*&& PayType == I_("E") ) *///PAC Avail and SWP Avail at fund-mstr level should be applied regardless of paytype
            {
			   addIDITagValue( idiStr, FLAGNAME, I_("PAC") );
               ADDCONDITIONFROMFILEIDI( CND::ERR_PAYTYPE_NOT_AVAIL_FOR_FUND, idiStr );
               return;
            }
            iter.getObject()->getField( ifds::SWPavail, str, BF::HOST, false );
            if( str != YES && str1 == SWP) /*&& PayType == I_("E") )*///PAC Avail and SWP Avail at fund-mstr level should be applied regardless of paytype
            {
			   addIDITagValue( idiStr, FLAGNAME, I_("SWP") );
               ADDCONDITIONFROMFILEIDI( CND::ERR_PAYTYPE_NOT_AVAIL_FOR_FUND, idiStr );
               return;
            }
         }
      }
   }
}

//*************************************************************
void Systematic::ValidateAmount(const DString& Amount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAmount" ) );

   DString dstrAmount(Amount);
   dstrAmount.stripAll(I_(','));
   double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);

   DString dstrFundCode, dstrClassCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   if( findTransType( idDataGroup, AUTO_TRFER ) )
   {
      if( dAmount == 0 )
      {
         int iAcctItem(0),iFundItem(0);
         BFObjIter acctIter(*_pAtAcctAllocationList,idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         iAcctItem =  acctIter.getNumberOfItemsInList();
         if( iAcctItem == 1 )
         {
            AutoAcctTransAllocation* pAutoAcctTransAllocation = dynamic_cast<AutoAcctTransAllocation*>(acctIter.getObject());
            AutoTransAllocationList* pAutoTransAllocationList;
            pAutoAcctTransAllocation->getAtAllocationList(pAutoTransAllocationList);

            BFObjIter fundIter(*pAutoTransAllocationList,idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
            iFundItem =  fundIter.getNumberOfItemsInList();
         }
         if( iAcctItem > 1 || iFundItem > 1 )
            ADDCONDITIONFROMFILE( CND::ERR_AT_AMOUNT_TRANSFER );
         return;
      }
   }
/*
   if( !_pList )
   {
      _pList = dynamic_cast<SystematicList *>(getParent());
      _pMFAccount = _pList->getMFAccount();
   }

   bool bOverrideFundLevel = false;   
   if ( _pMFAccount ) {
      DString dstrEffectiveDate;
      getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
      if (  findTransType( idDataGroup, PAC ) )
         _pMFAccount->minPAC ( dstrEffectiveDate, Amount, bOverrideFundLevel, idDataGroup );
      else if ( findTransType( idDataGroup, SWP ) )
         _pMFAccount->minSWP ( dstrEffectiveDate, Amount, bOverrideFundLevel, idDataGroup );
   }
   if ( bOverrideFundLevel )
      return;*/

   ValidateAmountLimit(dAmount, dstrFundCode, dstrClassCode, idDataGroup);

   DString dstrCappedFund (NULL_STRING),dstrOrigFund;
   if( _dstrTransType == PAC || _dstrTransType == SAVING_PLAN )
   {
      getField(ifds::FundCode, dstrCappedFund, idDataGroup, false);
  		getField(ifds::FundCode, dstrOrigFund,   BF::HOST,false );
   }
   else if ( _dstrTransType == AUTO_TRFER )
   {
      getField(ifds::FundToCode, dstrCappedFund, idDataGroup, false);
  		getField(ifds::FundToCode, dstrOrigFund,   BF::HOST,false );
   }

   if( !dstrCappedFund.empty() && isCappedFund( dstrCappedFund, idDataGroup ) )
	{
		DString dstrOrigAmount;
		getField(ifds::Amount,dstrOrigAmount,BF::HOST,false );
		dstrOrigFund.strip().upperCase();
		if( dstrOrigFund == dstrCappedFund )
		{
			ValidateCappedAmt ( dstrOrigAmount,dstrAmount, idDataGroup);
		}
	}
   //for PAC and SMARTS, We need to validate initial puchase amount
   if( findTransType( idDataGroup, PAC ) )
   {
		ValidateAmountInitPur(dAmount, dstrFundCode, dstrClassCode, idDataGroup);
   }
   else if( findTransType( idDataGroup, AUTO_TRFER ) )
   {
	   DString dstrtoFundCode, dstrtoClassCode;
	   getField( ifds::FundToCode, dstrtoFundCode, idDataGroup, false );
		dstrtoFundCode.strip().upperCase();
      getField( ifds::ClassToCode, dstrtoClassCode, idDataGroup, false );
	   ValidateAmountInitPur(dAmount, dstrtoFundCode, dstrtoClassCode, idDataGroup);

      /** handled already by the logic above
		if( !dstrtoFundCode.empty() && isCappedFund( dstrtoFundCode, idDataGroup ) )
		{	
			DString dstrOrigAmount,dstrOrigFund;
			getField(ifds::Amount,dstrOrigAmount,BF::HOST,false );
			getField(ifds::FundToCode,dstrOrigFund,BF::HOST,false );
			dstrOrigFund.strip().upperCase();
			if( dstrOrigFund == dstrtoFundCode )
			{
				ValidateCappedAmt ( dstrOrigAmount,dstrAmount, idDataGroup);
			}

		}**/
   }
}

//******************************************************************
//validate Initial puchase amount for PAC and SMARTS
void Systematic::ValidateAmountInitPur(double dAmount, const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateAmountInitPur"));

   SEVERITY sevRtn = NO_CONDITION;

	DString dstrTransType; 
 	getField( ifds::TransType, dstrTransType, idDataGroup, false );
   dstrTransType.strip().upperCase();

	MFAccount *mfAccount=NULL;

	if(dstrTransType == AUTO_TRFER)
	{
		DString dstrAccountTo;
		getField( ifds::AccountTo, dstrAccountTo, idDataGroup, false );
		sevRtn = getWorkSession().getMFAccount( idDataGroup, dstrAccountTo, mfAccount );
	}
	else if(dstrTransType == PAC)
	{
		//******fund holding not zero, skip this validation
		if( !_pMFAccount )
		{
			if( !_pList )
			   _pList = dynamic_cast<SystematicList *>(getParent());
			if( _pList )
			   _pMFAccount = _pList->getMFAccount();
		}
		mfAccount = _pMFAccount;
	}

   bool bOverrideFundLevel = false;   
   DString dstrEffectiveDate, dstrAmount;
   getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
   getField ( ifds::Amount, dstrAmount, idDataGroup );
   if ( mfAccount ) {  
      if( dstrTransType == PAC || dstrTransType == AUTO_TRFER )
         mfAccount->minPAC ( dstrEffectiveDate, dstrAmount, bOverrideFundLevel, idDataGroup );      
   }
   if ( bOverrideFundLevel )
      return;

    //******fund or class empty then skip this validation
   if(dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING )	return;

	//******error Msg is ignore, skip this validation
	DString ErrorNum, dstrErrValue;
	if ( dstrTransType == PAC )	
      ErrorNum = I_("356");
	else if(dstrTransType == AUTO_TRFER ) 
      ErrorNum = I_("357");
   getErrMsgValue( ErrorNum, idDataGroup, dstrErrValue );
   if(dstrErrValue == I_("I"))	
   return;
	
	//******fundclass not validate, skip this validation
	/*if(dstrTransType == PAC)
	{
		ValidateFundClass(idDataGroup);
	}
	else if(dstrTransType == AUTO_TRFER )
	{
		DString FundtoCode = dstrFundCode;
        ValidateFundToCode(FundtoCode,idDataGroup);
        validateFundClassTransferAllowed(idDataGroup);  
	}
	if ( GETCURRENTHIGHESTSEVERITY() > WARNING ) return;*/
   
	if(mfAccount && mfAccount->isNew() == false)
	{
		 bool recordFound=false;
		 double dec_SettleUnits (0);	 //double dec_SettleValue (0);
		 double dec_unSettleUnits (0);	 //double dec_unSettleValue (0);
		 dec_SettleUnits = mfAccount->fundClassBalance( dstrFundCode, dstrClassCode, recordFound, ifds::SettledUnits, idDataGroup );  	 //dec_SettleValue = _pMFAccount->fundClassBalance( dstrFundCode, dstrClassCode, recordFound, ifds::SettledValue, idDataGroup );  
		 dec_unSettleUnits = mfAccount->fundClassBalance( dstrFundCode, dstrClassCode, recordFound, ifds::UnsettledUnits, idDataGroup );   //dec_unSettleValue = _pMFAccount->fundClassBalance( dstrFundCode, dstrClassCode, recordFound, ifds::UnsettledValue, idDataGroup );  
		 if((dec_SettleUnits + dec_unSettleUnits) > 0) return;

		 //******Pending exist, skip this validation
		 if(mfAccount->pendingOfFundExist( dstrFundCode, dstrClassCode, idDataGroup )) return;

		 /******Transaction Exist, skip this validation
		 DString strNumEntry = I_("1");
		 DString strAllFundsMode = I_("N");
		 TransactionList * pTransactionList = NULL;
		 if(mfAccount->getTransactionHistoryList( pTransactionList , dstrFundCode, dstrClassCode, 
                                                 strNumEntry, strAllFundsMode, NULL_STRING, idDataGroup, true ) > WARNING )
		 {
			 return;
		 }
		 if(pTransactionList)
		 {	
			 //no matter what transaction type, just fund if have any transaction for that fund/class
			if(pTransactionList->fundclasstrxExist( dstrFundCode, dstrClassCode, NULL_STRING,idDataGroup ))
			{
				return;//DString strKey;pTransactionList->getStrKey(strKey,dstrFundCode,dstrClassCode,dstrTransNum,dstrTransType);
			} //BFObjIter iter( *pTransactionList,BF::HOST );if( iter.positionByKey(strKey)) return;
		 }*/
	}

	//******minimun amount validation start.
	bool bError (false);
	DString dstrMinAmt = NULL_STRING;
	sevRtn = minAmountOverride( PURCHASE_CODE, dstrFundCode, dstrClassCode, dstrMinAmt, bError, idDataGroup );

	DString dstrBankAcctCurr, idiStr,dstrCurrency, dstrEffecDate, strKey;

	if( findTransType( idDataGroup, AUTO_TRFER ) )                          // find a currency  for AT
		getFundCurrency(dstrBankAcctCurr, idDataGroup);
	else
		getField(ifds::BankAcctCurrency, dstrBankAcctCurr, idDataGroup, false);

	getField(ifds::EffectiveDate, dstrEffecDate, idDataGroup, false);

      FundDetail *pFundDetail = NULL;
      if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, BF::HOST, pFundDetail ) )
      {
         pFundDetail->getField( ifds::Currency, dstrCurrency, BF::HOST, false );

		   double dExchRate (1);
		   if( _dstrmultiCurrency == YES )
		   {
			   dExchRate = getCurrExchangeRate(dstrBankAcctCurr, dstrCurrency, dstrEffecDate);
		   }

		   if( dAmount * dExchRate < DSTCommonFunctions::convertToDouble(dstrMinAmt) )
		   {
			   DString idiStr;
			   addIDITagValue( idiStr, FUND, dstrFundCode );
			   addIDITagValue( idiStr, CLASS, dstrClassCode );
			   DSTCommonFunctions::DisplayFormat( dstrMinAmt, ifds::Amount );
			   addIDITagValue( idiStr, MINIMUM_AMT, dstrMinAmt.stripAll() );

			   if ( bError )
			   {		   
			      ADDCONDITIONFROMFILEIDI( CND::ERR_MIN_INIT_PURCHASE, idiStr );
			   }
			   else
			   {
			      ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_MIN_INIT_PURCHASE, idiStr );
			   }

			   return;
		   }
	 }
}
//******************************************************************
void Systematic::ValidateAmountLimit(double dAmount, const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateAmountLimit"));


   /* If If Cfg-PACAmtEdit equal to :
      1 -  Must be >= MinPAC-56 (in view #56) - Hard edit
      2 -  Must be >= MinPAC-56 (in view # 56) - Soft edit (give warning only)
      3 -  Must be >= PACMinAmt-83 (configuration) - Hard edit 
      4 -  Must be >= PACMinAmt-83 (configuration) - Soft edit (give warning only) */

   if( dAmount == 0 )
   {
      DString dstrAmountType;
      getField(ifds::AmountType, dstrAmountType, idDataGroup);
      if(dstrAmountType != I_("L") && dstrAmountType != I_("G")) //LWA/GWA allows zero amounts
         ADDCONDITIONFROMFILE( CND::ERR_VALUE_CANNOT_BE_ZERO );
      return;
   }
   if( dAmount < 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_NEGATIVE_AMOUNT );
      return;
   }
   if( dAmount > 999999999999 )
   {
      DString FieldName(I_("999,999,999,999.00"));
	  DSTCommonFunctions::DisplayFormat( FieldName, ifds::Amount );
      ADDCONDITIONFROMFILEIDI( CND::ERR_AMOUNT_EXCEED_MAX_LIMIT, (I_("Amount=")+FieldName).c_str() );
      return;
   }
   //Validate the precision
   DString dstrAmountType, dstrBankAcctCurr, idiStr;
   if( findTransType( idDataGroup, AUTO_TRFER ) )                          // find a currency  for AT
      getFundCurrency(dstrBankAcctCurr, idDataGroup);
   else
      getField(ifds::BankAcctCurrency, dstrBankAcctCurr, idDataGroup, false);

   //only check for dollar amount and settle currency amount for PAC & SWP
   getField(ifds::AmountType, dstrAmountType, idDataGroup, false);
   if( dstrAmountType != I_("D") && dstrAmountType != I_("S") )
      return;

   DString dstrTransType, dstrCurrency, dstrSettleCurrency, dstrEffecDate;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   getField(ifds::SettleCurrency, dstrSettleCurrency, idDataGroup, false);
   getField(ifds::EffectiveDate, dstrEffecDate, idDataGroup, false);

   dstrTransType.strip().upperCase();

   DString dstrMinAmt, strKey;

   if( dstrTransType == PAC ) //PAC
   {
      if( !_pList )
      {
         _pList = dynamic_cast<SystematicList *>(getParent());
         _pMFAccount = _pList->getMFAccount();
      }

      bool bOverrideFundLevel = false;   
      DString dstrEffectiveDate, dstrAmount;
      getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
      getField ( ifds::Amount, dstrAmount, idDataGroup );
      if ( _pMFAccount ) {      
         _pMFAccount->minPAC ( dstrEffectiveDate, dstrAmount, bOverrideFundLevel, idDataGroup );      
      }
      if ( bOverrideFundLevel )
         return;


      DString  PACAmtEdit;
      _pMgmtCoOption->getField( ifds::PACAmtEdit, PACAmtEdit, BF::HOST, false );

      if( PACAmtEdit == I_("3") || PACAmtEdit == I_("4") )
      {
         _pMgmtCoOption->getField( ifds::PACMinAmt, dstrMinAmt, BF::HOST, true );

         double dExchRate (1);
         if( _dstrmultiCurrency == YES )
            dExchRate = getCurrExchangeRate(dstrBankAcctCurr, _dstrSysCurrency, dstrEffecDate);

         if( dAmount * dExchRate < DSTCommonFunctions::convertToDouble(dstrMinAmt) )
         {
            DString tmp1 = BLANKSTRING, tmp2 = dstrMinAmt;
            if( tmp1.empty() ) tmp1 = BLANKSTRING;
            if( tmp2.empty() ) tmp2 = BLANKSTRING;

            if( PACAmtEdit == I_("3") )
            {
               addIDITagValue( idiStr, FUNDNAME, tmp1 );
			   DSTCommonFunctions::DisplayFormat( tmp2, ifds::Amount );
               addIDITagValue( idiStr, AMOUNT, tmp2.stripAll() + _dstrSysCurrency );
               ADDCONDITIONFROMFILEIDI( CND::ERR_PAC_LESS_THAN_MINIMUM_ALLOW, idiStr );
               return;
            }
            else if( PACAmtEdit == I_("4") )
            {
               addIDITagValue( idiStr, FUNDNAME, tmp1 );
			   DSTCommonFunctions::DisplayFormat( tmp2, ifds::Amount );
               addIDITagValue( idiStr, AMOUNT, tmp2.stripAll() + _dstrSysCurrency );
               ADDCONDITIONFROMFILEIDI( CND::WARN_PAC_LESS_THAN_MINIMUM_ALLOW, idiStr );
               return;
            }
         }
      }
      else if( PACAmtEdit == I_("1") || PACAmtEdit == I_("2") )
      {
         if( dstrFundCode.empty() || dstrClassCode.empty() )
            return;

         FundDetail *pFundDetail = NULL;
         if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, BF::HOST, pFundDetail ) )
         {
            //iter.getObject()->getField(ifds::MinPAC, dstrMinAmt, BF::HOST, true );
            pFundDetail->getField( ifds::Currency, dstrCurrency, BF::HOST, false );

            bool bError (false);
            if( PACAmtEdit == I_("1")) // hard edit
            {
               bError = true;
            }
            if( PACAmtEdit == I_("2"))
            {
               bError = false;
            }


            SEVERITY sevRtn = minAmountOverride( PAC, dstrFundCode, dstrClassCode, dstrMinAmt, bError, idDataGroup );

            double dExchRate (1);
            if( _dstrmultiCurrency == YES )
               dExchRate = getCurrExchangeRate(dstrBankAcctCurr, dstrCurrency, dstrEffecDate);

            if( dAmount * dExchRate < DSTCommonFunctions::convertToDouble(dstrMinAmt) )
            {
               DString tmp1 = dstrFundCode, tmp2 = dstrMinAmt.stripAll();;

               tmp1 = dstrFundCode + BLANKSTRING;
               tmp1 += dstrClassCode;
               tmp2 += dstrCurrency;
               if( tmp1.empty() ) tmp1 = BLANKSTRING;
               if( tmp2.empty() ) tmp2 = BLANKSTRING;

               addIDITagValue( idiStr, FUNDNAME, tmp1 );
			   DSTCommonFunctions::DisplayFormat( tmp2, ifds::Amount );
               addIDITagValue( idiStr, AMOUNT, tmp2 );

               if ( bError )
               {
                  ADDCONDITIONFROMFILEIDI( CND::ERR_PAC_LESS_THAN_MINIMUM_ALLOW, idiStr );
               }
               else
               {
                  ADDCONDITIONFROMFILEIDI( CND::WARN_PAC_LESS_THAN_MINIMUM_ALLOW, idiStr );
               }
               
               return;
            }
         }
      }
   }
   else if( dstrTransType == I_("S") )                //SWP
   {
      if( !_pList )
      {
         _pList = dynamic_cast<SystematicList *>(getParent());
         _pMFAccount = _pList->getMFAccount();
      }

      bool bOverrideFundLevel = false;   
      DString dstrEffectiveDate, dstrAmount;
      getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
      getField ( ifds::Amount, dstrAmount, idDataGroup );
      if ( _pMFAccount ) {      
         _pMFAccount->minSWP ( dstrEffectiveDate, dstrAmount, bOverrideFundLevel, idDataGroup );      
      }
      if ( bOverrideFundLevel )
         return;

      if( dstrFundCode.empty() || dstrClassCode.empty() )
         return;

      FundDetail *pFundDetail = NULL;
      if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, BF::HOST, pFundDetail ) )
      {
         //iter.getObject()->getField(ifds::MinSWP, dstrMinAmt, BF::HOST, true );
         pFundDetail->getField( ifds::Currency, dstrCurrency, BF::HOST, false );
         bool bError (false);

         SEVERITY sevRtn = minAmountOverride( SWP, dstrFundCode, dstrClassCode, dstrMinAmt, bError, idDataGroup );


         double dExchRate (1);
         if( _dstrmultiCurrency == YES )
            dExchRate = getCurrExchangeRate(dstrBankAcctCurr, dstrCurrency, dstrEffecDate);

         if( dAmount * dExchRate < DSTCommonFunctions::convertToDouble(dstrMinAmt) )
         {
            DString dstrTemp(dstrFundCode);
            dstrTemp += BLANKSTRING;
            addIDITagValue( idiStr, FUNDNAME, dstrTemp + dstrClassCode  );
			DSTCommonFunctions::DisplayFormat( dstrMinAmt, ifds::Amount );
            addIDITagValue( idiStr, AMOUNT, dstrMinAmt.strip() + dstrCurrency);

            if ( bError )
            {
               ADDCONDITIONFROMFILEIDI( CND::ERR_SWP_LESS_THAN_MINIMUM_ALLOW, idiStr );
            }
            else 
            {
               ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_SWP_LESS_THAN_MINIMUM_ALLOW, idiStr );
            }

            return;
         }
      }
   }

   DString dstrBusRounding;
   _pMgmtCoOption->getField( ifds::BusRounding, dstrBusRounding, BF::HOST, false );
   if( dstrBusRounding.strip() == YES )
   {
      if( dstrAmountType == I_("D") && dstrTransType == I_("S") )
      {
         DString dstrCurrency, dstrFundCode, dstrClassCode, dstrAmount;

         Currency *pCurrency = NULL;


         getField(ifds::FundCode,  dstrFundCode, idDataGroup, false);
         getField(ifds::ClassCode, dstrClassCode,idDataGroup, false);



         if( dstrFundCode.strip() != NULL_STRING && dstrClassCode.strip() != NULL_STRING )
         {
            CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrCurrency);

            BFObjIter iterCurrency( *_pCurrencyList, idDataGroup, true );
            iterCurrency.begin();
            iterCurrency.setKeyFilter(dstrCurrency);
            while( !iterCurrency.end() )
            {
               DString dstrEffectiveDate, dstrPrecision;
               iterCurrency.getObject()->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
               iterCurrency.getObject()->getField(ifds::Precision, dstrPrecision, idDataGroup);

               if( (DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrEffecDate) == DSTCommonFunctions::FIRST_EARLIER )||
                   (DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrEffecDate) == DSTCommonFunctions::EQUAL ) )
               {
                  getField(ifds::Amount, dstrAmount,idDataGroup, false);
                  int iPrecision = atoi(dstrPrecision.asA().c_str());

                  if( (DSTCommonFunctions::NumOfDecimals( dstrAmount )) > iPrecision )
                  {
                     if( iPrecision == 0 )
                     {
                        ADDCONDITIONFROMFILE( CND:: ERR_FRACTIONAL_VALUES_NOT_ALLOWED_IN_CURRENCY );
                     }
                     else
                     {
                        DString idiStr;
                        addIDITagValue( idiStr, DECIMALS, dstrPrecision.strip() );
                        addIDITagValue( idiStr, CURRENCY_TAG, dstrCurrency.strip() ); 
                        ADDCONDITIONFROMFILEIDI( CND::ERR_INCORRECT_PRECISION, idiStr );
                     } 
                  }

               }
               ++iterCurrency;
            }
         }
      }
      if( (dstrAmountType == I_("S") && dstrTransType == SWP ) || 
          ((dstrAmountType == I_("D")|| dstrAmountType == I_("S"))&& dstrTransType == I_("P")) )
      {
         DString dstrCurrency, dstrBankCurrency, dstrAmount;
         getField(ifds::BankAcctCurrency, dstrBankCurrency, idDataGroup, false);
         dstrBankCurrency.strip().upperCase();


         BFObjIter iterCurrency( *_pCurrencyList, idDataGroup, true );
         iterCurrency.begin();
         iterCurrency.setKeyFilter(dstrBankCurrency);

         while( !iterCurrency.end() )
         {
            DString dstrEffectiveDate, dstrPrecision;
            iterCurrency.getObject()->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
            iterCurrency.getObject()->getField(ifds::Precision, dstrPrecision, idDataGroup);
            int iPrecision = atoi(dstrPrecision.asA().c_str());

            if( (DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrEffecDate) == DSTCommonFunctions::FIRST_EARLIER )||
                (DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrEffecDate) == DSTCommonFunctions::EQUAL) )
            {
               getField(ifds::Amount, dstrAmount,idDataGroup, false);

               if( (DSTCommonFunctions::NumOfDecimals( dstrAmount )) > iPrecision )
               {
                  if( iPrecision == 0 )
                  {
                     ADDCONDITIONFROMFILE( CND:: ERR_FRACTIONAL_VALUES_NOT_ALLOWED_IN_CURRENCY );
                  }
                  else
                  {
                     DString idiStr;
                     addIDITagValue( idiStr, DECIMALS, dstrPrecision.strip() );
                     addIDITagValue( idiStr, CURRENCY_TAG, dstrBankCurrency.strip() ); 
                     ADDCONDITIONFROMFILEIDI( CND::ERR_INCORRECT_PRECISION, idiStr );
                  } 
               }

            }
            ++iterCurrency;
         }//if ( !iterCurrency.end() )

      }//if ((dstrAmountType == I_("S") &&...
   }//if (dstrBusRounding.strip() == YES)
}

//*************************************************************
void Systematic::ValidateAmountType(const DString& AmountType, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAmountType" ) );

   if( findTransType( idDataGroup, AUTO_TRFER ) )
   {
      DString dstrAmount;
      getField(ifds::Amount,dstrAmount,idDataGroup,false);
      double dAmount = atof(dstrAmount.asA().c_str());

		/* Incident #591211 -- A change is required to allow the use of the following transfer codes in the AmountType field
		   on the Automatic Transfer Screen: 
		   F - All Free Unit
			D - Amount
			T - Free and non-aged Unit
			M - Matured Units
			Y - Matured Units and Free
			X - Matured Units and ID
			P - Percantage of Units
			U - Unis 

			The systimatic has already handle D, P and U. This Incident focus on F, T, M, Y and X
			The logic follows base code ATRFM00.EH
		 */
		if (abs(dAmount) < 0.01 ) //full transfer
      {
         // TRANSFR11.P accepts these amttypes pts 10033507
         if ( !DSTCommonFunctions::codeInList ( AmountType, I_("D,F,T,M,X,Y") ) )
         {
            ADDCONDITIONFROMFILE ( CND::ERR_INVALID_AMTTYPE_FOR_FULL_TRANSFER );
         }
         else
         {
            ADDCONDITIONFROMFILE (CND::ERR_FULL_EXCHANGE_INDICATED); //give people a warning sign
         }
      }
		
		if ( DSTCommonFunctions::codeInList ( AmountType, I_("F,T,M,X,Y") ) )
		{
			DString fundCode,  classCode;

         getField (ifds::FundCode, fundCode, idDataGroup );
         getField (ifds::ClassCode, classCode, idDataGroup );
        
         if (!fundCode.empty() && !classCode.empty())
         { 
            FundDetail *pFundDetail = NULL;

            if ( getWorkSession ().getFundDetail ( fundCode, classCode, idDataGroup, pFundDetail ) 
                 && pFundDetail)
            {
               DString loadType;
               
               pFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false);     
               if (loadType != I_("BEL"))
               {
                  ADDCONDITIONFROMFILE (CND::ERR_AMTTYPE_APPL_TO_BEL_FUND);
               }		
            }
         }
        
         DString toFund, toClass;
         
         getField ( ifds::FundToCode, toFund, idDataGroup, false );
         getField ( ifds::ClassToCode, toClass, idDataGroup, false );
         if ( !toFund.empty() && !toClass.empty() )
         {   
            FundDetail *pFundDetail = NULL;

            if ( getWorkSession ().getFundDetail ( toFund, toClass, idDataGroup, pFundDetail) && 
                 pFundDetail )
            {
               DString loadType;
               
               pFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false);
               if (loadType == I_("BEL"))
               {
                  ADDCONDITIONFROMFILE (CND::ERR_NO_APPLICATBLE_FOR_TOFUND);
               }
            }
         }
 	   //if( (abs(dAmount) < 0.01) && (AmountType != I_("D")) )
      //{
      //   ADDCONDITIONFROMFILE( CND::ERR_AT_AMOUNT_TYPE );
      //   return;
      //}

		}
	}

   DString dstrTransType, dstrFundCode, dstrBusRounding;

   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   dstrFundCode.strip();
   if( AmountType == I_("S") && _dstrmultiCurrency.strip().upperCase() == NO && dstrTransType == I_("S") )
   {
      if( !dstrFundCode.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_AMT_TYPE );
         return;
      }
   }
	DString strMarket = DSTCommonFunctions::getMarket ();
	if ( strMarket == MARKET_IDS::CANADA && dstrTransType.strip() == I_("S") && AmountType == I_("U") )
	{
		ADDCONDITIONFROMFILE( CND::ERR_SWP_UNITS_NOT_ALLOWED );
		return;
	}

//	_pMgmtCoOption->getField( DBR::BusRounding, dstrBusRounding, BF::HOST, false );
   if( AmountType != I_("D") && dstrTransType.strip() == I_("P") )
   {
      ADDCONDITIONFROMFILE( CND::ERR_PAC_UNITS_NOT_ALLOWED );
      return;
   }
      
   bool bIsRDSPAccount = _pMFAccount->isRDSPAccount(idDataGroup);

   if ( strMarket == MARKET_IDS::CANADA && dstrTransType.strip() == I_("S") && bIsRDSPAccount && AmountType == I_("P") )
   {
	   ADDCONDITIONFROMFILE( CND::ERR_SWP_PERCENT_NOT_ALLOWED );
	   return;
   }

   if ( strMarket == MARKET_IDS::CANADA && dstrTransType.strip() == I_("S") && !bIsRDSPAccount && DSTCommonFunctions::codeInList(AmountType, I_("A,N,O")) )
   {
	   ADDCONDITIONFROMFILE( CND::ERR_AMT_TYPE_NOTAPPLICABLE );
	   return;
   }
  
/* this logic is included in  CheckAmountType.... yingbao

  BFObjIter iter(*_pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   int iAllocNum = iter.getNumberOfItemsInList();
   if( AmountType == I_("U") && iAllocNum > 1 )
   {
     ADDCONDITIONFROMFILE( CND::ERR_PAC_SWP_UNITS_NOT_ALLOWED );
      return;
  }
  if( AmountType != I_("S") && dstrTransType == I_("S") 
      && dstrBusRounding.strip() == YES && iAllocNum > 1)
  {
     ADDCONDITIONFROMFILE( CND::ERR_SWP_FUND_BLANK );
      return;
  }*/
   CheckAmountTypeForPACSWPMultiAllocation(idDataGroup );

   DString dstrClassCode, dstrSegClient, dstrCotClient;

   getWorkSession().getOption(ifds::SegClient, dstrSegClient, BF::HOST );
   getWorkSession().getOption(ifds::CotClient, dstrCotClient, BF::HOST );
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   dstrSegClient.strip().upperCase();
   dstrCotClient.strip().upperCase();

   if (!dstrFundCode.empty() && !dstrClassCode.empty() &&
      dstrSegClient == YES && dstrCotClient == YES)
   {
      DString strListAmttype,
         dstrAmountType,
         dstrTransTypeFmt;
      getValidListAmountTypeByFund (dstrFundCode,dstrClassCode,strListAmttype,idDataGroup);
      getField (ifds::AmountType, dstrAmountType, idDataGroup, false);
      getField (ifds::TransType, dstrTransTypeFmt, idDataGroup, true);

      dstrAmountType.strip().upperCase();

      //if (DSTCommonFunctions::codeInList (dstrAmountType, GWLWA_OPTIONS) && 
      //   !strListAmttype.empty())
      if (!strListAmttype.empty())
      {
         // if amount type is not in the list of valid amount type by fund class
         // then raise up an error
         // assume that back-end would return all of valid amount type
         if (!DSTCommonFunctions::codeInList (dstrAmountType, strListAmttype))
         {
            DString dstrTemp;
            addIDITagValue( dstrTemp, I_("TRANS_TYPE"), dstrTransTypeFmt);
            getErrMsg(IFASTERR::INVALID_AMOUNT_TYPE_BY_SEG_RULES, 
                      CND::ERR_INVALID_AMOUNT_TYPE_BY_SEG_RULES, 
                      CND::WARN_INVALID_AMOUNT_TYPE_BY_SEG_RULES,
                      idDataGroup,
                      dstrTemp);
         }
      }
   }

   // in the case there is no setup at fund\class level, validate agasint account level
   // which is an existing logic
   if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
   {
      // validate EWA, GWA, LWA
      DString dstrGWLWAAvailOptions;
      DString dstrAmountType;

      _pMFAccount->getField ( ifds::GWLWAAvailOptions, dstrGWLWAAvailOptions, idDataGroup, false );  

      dstrGWLWAAvailOptions.strip ();

      // if amount type is one of GWA or LWA option then we will check 
      // against an account value whether it is allowed or not
      if (DSTCommonFunctions::codeInList (AmountType, GWLWA_OPTIONS))
      {
         if (!DSTCommonFunctions::codeInList (AmountType, dstrGWLWAAvailOptions))
         {
            ADDCONDITIONFROMFILE (CND::ERR_AMT_TYPE_NOTAPPLICABLE);
         }
         else
         {
            // if an account level list of option exists then 
            // check against RRIF level
            DString dstrRRIFGLOpt;

            _pMFAccount->getField ( ifds::RRIFGLOpt, dstrRRIFGLOpt, idDataGroup, false );  

            if (!dstrRRIFGLOpt.empty ())
            {
               ADDCONDITIONFROMFILE (CND::ERR_SWP_CANNOT_BESETUP);
            }
         }
      }
   }
}

//*************************************************************
void Systematic::ValidateGrossOrNet(const DString& GrossOrNet, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateGrossOrNet" ) );

   DString strFund, dstrAmtType;
   getField( ifds::FundCode, strFund, idDataGroup, false );
   getField(ifds::AmountType,dstrAmtType,idDataGroup,false);
   dstrAmtType.strip().upperCase();

   DString strTransType;
   getField(ifds::TransType,strTransType,idDataGroup,false);
   strTransType.strip().upperCase();

   if( strTransType == AUTO_TRFER ) return;

   if( GrossOrNet == I_("N") && strFund.empty() && strTransType == PAC )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_NET );
   }

   if ( GrossOrNet == NO /*Net*/ && 
         ( dstrAmtType == I_("P") || dstrAmtType == I_("U")))
   {
      ADDCONDITIONFROMFILE( CND::ERR_NET_UNIT_PERCENT_NOT_ALLOW );   
   }

   DString dstrAmtTypeOvrd;
   getField(ifds::AmtTypeOvrd, dstrAmtTypeOvrd, idDataGroup);

   if (GrossOrNet == I_("N") && 
       strTransType == SWP &&
       dstrAmtTypeOvrd.upperCase() == AMT_TYPE::CUSTOM)
   {
       getErrMsg(IFASTERR::NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP, 
                 CND::ERR_NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP,
                 CND::WARN_NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP,
                 idDataGroup);
   };

}

//****************************************************
void Systematic::ValidateSrcOfFund(const DString& SrcOfFund, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateSrcOfFund" ) );
   
}

//****************************************************
void Systematic::ValidateAdminFee(const DString& dstrAdminFee, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAdminFee" ) );


   DString dstrBusRounding;
   _pMgmtCoOption->getField( ifds::BusRounding, dstrBusRounding, BF::HOST, false );
   if( dstrBusRounding.strip() == YES )
   {
      DString dstrAdminFeeCurr, dstrEffecDate;
      getField(ifds::AdminFeeCurr, dstrAdminFeeCurr, idDataGroup, false);

      getField(ifds::EffectiveDate, dstrEffecDate, idDataGroup, false);
      if( dstrAdminFeeCurr.strip() != NULL_STRING )
      {
         Currency *pCurrency = NULL; 
         _pCurrencyList->getCurrency(dstrAdminFeeCurr, pCurrency, idDataGroup);
         if( pCurrency != NULL )
         {
            DString dstrEffectiveDate, dstrPrecision;
            pCurrency->getField( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST );
            pCurrency->getField( ifds::Precision, dstrPrecision, BF::HOST );

            int iPrecision = atoi(dstrPrecision.asA().c_str());

            if( (DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrEffecDate) == DSTCommonFunctions::FIRST_EARLIER )||
                (DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrEffecDate) == DSTCommonFunctions::EQUAL) )
            {
               DString dstrFee(dstrAdminFee);
               if( dstrFee.find(I_(".")) != DString::npos )
                  dstrFee.stripTrailing( '0' );

               if( (DSTCommonFunctions::NumOfDecimals( dstrFee )) > iPrecision )
               {
                  if( iPrecision == 0 )
                  {
                     ADDCONDITIONFROMFILE( CND:: ERR_FRACTIONAL_VALUES_NOT_ALLOWED_IN_CURRENCY );
                  }
                  else
                  {
                     DString idiStr;
                     addIDITagValue( idiStr, DECIMALS, dstrPrecision.strip() );
                     addIDITagValue( idiStr, CURRENCY_TAG, dstrAdminFeeCurr.strip() ); 
                     ADDCONDITIONFROMFILEIDI( CND::ERR_INCORRECT_PRECISION, idiStr );
                  } 
               }

            }

         }
      }
   }
// previous stuff:

   /*DString dstrAdminFeeCurr, idiStr;
 getField(DBR::AdminFeeCurr, dstrAdminFeeCurr, idDataGroup, false);
  if (dstrAdminFeeCurr.strip() != NULL_STRING)
  {
     int iPrecision = CurrencyClass::getPrecision(getWorkSessionId(), dstrAdminFeeCurr);
     if (iPrecision != -1)
     {
        DString dstrFee(dstrAdminFee);
         if (dstrFee.find(I_(".")) != DString::npos)
           dstrFee.stripTrailing( '0' );
      if( DSTCommonFunctions::NumOfDecimals( dstrFee ) > iPrecision )
        {
           char szBuffer[40];
           sprintf(szBuffer, "%20d", iPrecision);
           DString dstrTemp;
           dstrTemp = szBuffer;
       addIDITagValue( idiStr, DECIMALS, dstrTemp.strip() );
           addIDITagValue( idiStr, CURRENCY_TAG, dstrAdminFeeCurr.strip() );
        ADDCONDITIONFROMFILEIDI( CND::ERR_INCORRECT_PRECISION, idiStr );
        }
     }
  }*/
}

//************************************************************************************************
void Systematic::ValidateAdminFeeCurr(const DString& AdminFeeCurr, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAdminFeeCurr" ) );
}

//************************************************************************************************
void Systematic::ValidateFee(const DString& Fee, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateFee" ) );
	
   DString dstrFee(Fee);
   dstrFee.stripAll(I_(','));

	DString dstrTransType;
 	getField( ifds::TransType, dstrTransType, idDataGroup, false );
   dstrTransType.strip().upperCase();

	// Ensure the Acquisition Fees are charged on any SMARTs (i.e. Automatic Transfer)
	// only if ATFeeApply = Yes
	DString dstrATFeeApply;
	getWorkSession().getOption2( ifds::ATFeeApply, dstrATFeeApply, idDataGroup, false );	
	if ( AUTO_TRFER   == dstrTransType &&
		  I_( "N" )    == dstrATFeeApply.stripAll() )
	{		
		double dblATFee = DSTCommonFunctions::convertToDouble( dstrFee );
		if ( 0.00 != dblATFee )
		{
			ADDCONDITIONFROMFILE( CND::ERR_ACQ_FEES_MUST_BE_ZERO_FOR_AUTOMATIC_TRANSFER );
		}
	}

// we check if feetype is percentage, the fee value should be between 0 and 100
   if( !isDecimal( dstrFee ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_FEE_MUST_BE_NUMERIC );
      return;
   }

	DString dstrFlatPercent;
   getField( ifds::FlatPercent, dstrFlatPercent, idDataGroup ); 

   //	if( atof(dstrFee.asA().c_str()) == 0)
   //      return;

   DString dstrFundCode, dstrClassCode;   

   if( dstrTransType == AUTO_TRFER )
   {
      getField( ifds::FundToCode, dstrFundCode, idDataGroup, false );
      getField( ifds::ClassToCode, dstrClassCode, idDataGroup, false );
   }
   else
   {
      getField( ifds::FundCode, dstrFundCode, idDataGroup, false );
      getField( ifds::ClassCode, dstrClassCode, idDataGroup, false );
   }

   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   if( dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING )
      return;

   //request the Fee Validation information

   requestAcqFeeInquiry(idDataGroup);
   if( _dstrFeeDisableFlag == YES )
      return;

   DString str, idiStr;
   /**
     *  Validate the Fee precision
     */
   getField(ifds::FlatPercent, str, idDataGroup, false);
   if( str.strip() == YES )       //Precision checking only for Flat
   {
      DString FeeCurrency,
			strFlatFee;

      getField (ifds::Fee, strFlatFee, idDataGroup, true);
		getField(ifds::FeeCurrency, FeeCurrency, idDataGroup, false);
      int iPrecision = CurrencyClass::getPrecision( getWorkSession(), FeeCurrency);
      if( iPrecision != -1 )
      {
         //DString dstrFee(Fee);
         if( strFlatFee.find(I_(".")) != DString::npos )
            strFlatFee.stripTrailing( '0' );
         if( DSTCommonFunctions::NumOfDecimals( strFlatFee ) > iPrecision )
         {
            char szBuffer[40];
            sprintf(szBuffer, "%20d", iPrecision);
            DString dstrTemp;
            dstrTemp = szBuffer;
            addIDITagValue( idiStr, DECIMALS, dstrTemp.strip() );
            addIDITagValue( idiStr, CURRENCY_TAG, FeeCurrency.strip() );
            ADDCONDITIONFROMFILEIDI( CND::ERR_INCORRECT_PRECISION, idiStr );
            return;
         }
      }
   }

   if( dstrTransType == AUTO_TRFER )
   {
      DString rate,
         dstrAcqFee,
         fundCode,
         classCode,
         dstrFundTo,
         dstrClassTo,
			dstrFeeType ;

      //SplitCommissionList *pSplitCommissionList = NULL;
      getWorkSession().getOption (ifds::AcqFeeDefault, dstrAcqFee, idDataGroup, false );
      FundDetail *pFundDetail = NULL,
         *pFundToDetail = NULL;
      
      getField (ifds::FundCode, fundCode, idDataGroup);
      getField (ifds::ClassCode, classCode, idDataGroup);
      getField (ifds::FundToCode, dstrFundTo, idDataGroup);
      getField (ifds::ClassToCode, dstrClassTo, idDataGroup);
      if ( !fundCode.empty() &&
            !classCode.empty() &&
            getWorkSession().
               getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) && 
            pFundDetail &&
            !dstrFundTo.empty() &&
            !dstrClassTo.empty() &&
            getWorkSession().
               getFundDetail (dstrFundTo, dstrClassTo, idDataGroup, pFundToDetail) && 
            pFundToDetail)
      {
         DString loadType,
            toLoadType;
         bool bNewMoney = false;

         pFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false);
               
         FundToList fundToList (*this);
         bNewMoney =  fundToList.isBuySell ( fundCode, 
                                             classCode, 
                                             dstrFundTo, 
                                             dstrClassTo);


         if ( dstrAcqFee == Y &&
              _featureSplitComm != I_("1") &&
              loadType != I_("BEL") &&
              bNewMoney)
         {
            requestAcqFeeInquiry(idDataGroup);
         }
         else   
         {
            FeeInfoInquiry feeInfoInquiry (*this) ;

            if (feeInfoInquiry.init (dstrFundTo, dstrClassTo, NULL_STRING) <= WARNING)
            {
               BFObjIter iter (feeInfoInquiry, idDataGroup);

               if (!iter.end())
               {
						DString dstrAmount;

                  iter.getObject()->getField (ifds::TfrRate, rate, idDataGroup);
						iter.getObject()->getField (ifds::TfrFeeType, dstrFeeType, idDataGroup);
                  double dec_fee = DSTCommonFunctions::convertToDouble( dstrFee );
                  double dec_tfr_rate = DSTCommonFunctions::convertToDouble( rate );
						getField (ifds::FlatPercent, dstrFlatPercent, idDataGroup);
						getField (ifds::Amount, dstrAmount, idDataGroup);
						double dec_amount = DSTCommonFunctions::convertToDouble( dstrAmount );

						if (dstrFeeType == I_("1") /* percent */ && dstrFlatPercent == I_("Y") /* flat */ )
						{
							// convert fee rate to fee amount
								dec_tfr_rate = (dec_amount * dec_tfr_rate) / 100 ;
						}
						
                  if( dec_fee > dec_tfr_rate)
                  {
                     DString idiStr,
                        feeName;

                     getField (ifds::Fee, feeName, idDataGroup, true);
                     addIDITagValue (idiStr, I_ ("name"), feeName);					 
							DString dstrMaxrate;
							
							
							if (dstrFlatPercent == I_("N") )  // percent
							{
								dstrMaxrate = DSTCommonFunctions::doubleToDString (ifds::Fee, dec_tfr_rate);
								DSTCommonFunctions::DisplayFormat( dstrMaxrate, ifds::Fee );
							}
							else  // flat
							{
								dstrMaxrate = DSTCommonFunctions::doubleToDString (ifds::FeeAmt, dec_tfr_rate);
								DSTCommonFunctions::DisplayFormat( dstrMaxrate, ifds::FeeAmt );
							}
                     addIDITagValue (idiStr, I_ ("max"), dstrMaxrate );
                     ADDCONDITIONFROMFILEIDI (CND::ERR_FEE_RATE_ABOVE_MAX, idiStr);
                  }

               }
            }
            return ;
         }
      }
   }
  /**
   * Validate the Fee value
   */
   if( !_pAcqFeeInquiry )
      return;

   DString dstrMaxFeeActive;
   _pAcqFeeInquiry->getField(ifds::MaxFeeActive, dstrMaxFeeActive, idDataGroup, false);

   DString  dstrMaxFee, dstrminFee;
//   getField(ifds::FlatPercent, dstrFlatPercent, idDataGroup, false);

   dstrMaxFee = I_("NOCHECK");
   DString per(I_(" percent"));
   if( dstrMaxFeeActive == YES )
   {
      if( dstrFlatPercent == NO )  //  check percentage
      {
         _pAcqFeeInquiry->getField(ifds::MaxPercent, dstrMaxFee, idDataGroup, true);
         _pAcqFeeInquiry->getField(ifds::MinPercent, dstrminFee, idDataGroup, false);
      }
      else
      {
         _pAcqFeeInquiry->getField(ifds::MaxFlatFundCurr, dstrMaxFee, idDataGroup, true);
         _pAcqFeeInquiry->getField(ifds::MinFee, dstrminFee, idDataGroup, false);
         per = I_(" flat");
      }
   }
   else if( dstrFlatPercent == NO )          //Percent
   {
      dstrMaxFee = I_("100");
      dstrminFee = I_("0");
   }

   double dec_Fee = DSTCommonFunctions::convertToDouble( dstrFee );
   double dec_min_Fee = DSTCommonFunctions::convertToDouble( dstrminFee );

   addIDITagValue(idiStr, FUNDNAME, dstrFundCode );
   addIDITagValue(idiStr, CLASS, dstrClassCode );
   if( dstrMaxFeeActive == YES )
   {
      DString dstrMaxFeeMsg(dstrMaxFee);
      dstrFee.stripAll(I_(','));
      dstrMaxFee.stripAll(I_(','));
      if( atof(dstrFee.asA().c_str()) > atof(dstrMaxFee.asA().c_str()) )
      {
		 DSTCommonFunctions::DisplayFormat( dstrMaxFeeMsg, ifds::Fee );
         addIDITagValue(idiStr, MAXFEE, dstrMaxFeeMsg+per);

         ADDCONDITIONFROMFILEIDI(CND::ERR_FEE_MORE_THAN_MAX, idiStr);
         return;
      }
   }
   if( dec_Fee < dec_min_Fee )
   {
      ADDCONDITIONFROMFILEIDI(CND::ERR_FEE_MORE_THAN_MIN, idiStr);
   }

   DString dstDefaultAcqFee;
   getWorkSession().getOption( ifds::AcqFeeDefault, dstDefaultAcqFee, idDataGroup, false );

   if( dstDefaultAcqFee.strip().upperCase() == YES )
   {
      DString dstrAcqFee;

      _pAcqFeeInquiry->getField(ifds::AcqFee, dstrAcqFee,  idDataGroup, false);
      double dDefAcqFee = DSTCommonFunctions::convertToDouble( dstrAcqFee );
      double dInputAcqFee = DSTCommonFunctions::convertToDouble( Fee );

      if( dDefAcqFee != dInputAcqFee )
      {
         // add condition here
         ADDCONDITIONFROMFILE( CND::ERR_FEE_DIFFER_FROM_DEFAULT );
      }
   }

}

//************************************************************************************************
void Systematic::ValidateFeePercent(const DString& FeePercent, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateFeePercent" ) );
}

//************************************************************************************************
SEVERITY Systematic::validateCurrency (
      const DString &currency, 
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateCurrency" ) );

   DString currChkByTaxType,
      transType;
   
   getField (ifds::TransType, transType, 
      idDataGroup, false );
   transType.strip().upperCase();

   if (transType == I_("P"))
   {
      getWorkSession().getOption (ifds::CurrChkByTaxType, 
         currChkByTaxType, idDataGroup, false);
      if  (currChkByTaxType == I_("Y") && !currency.empty())
      {
         DString accountNum;
   
         getField (ifds::AccountNum, accountNum, idDataGroup, false);
         accountNum.strip().stripLeading('0');

         MFAccount *pMFAccount = NULL;
      
         if (getWorkSession().getMFAccount(idDataGroup, accountNum, pMFAccount) <= WARNING &&
            pMFAccount)
         {
            DString taxType,
               invalidCurr,
               taxTypeByCurrChk;

            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
            getWorkSession().getOption ( ifds::TaxTypeByCurrChk,
                                         taxTypeByCurrChk,
                                         BF::HOST,
                                         false
                                       );
            getWorkSession().getOption ( ifds::InvalidCurr,
                                         invalidCurr,
                                         BF::HOST,
                                         false
                                       );
            if ( DSTCommonFunctions::codeInList (taxType, taxTypeByCurrChk) &&
                 DSTCommonFunctions::codeInList (currency, invalidCurr)
               )
            {
               ADDCONDITIONFROMFILE (CND::ERR_TAX_TYPE_CANNOT_TRADE_IN_THE_CURRENCY);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************************
// Group Field: Fund Code and Class Code
void Systematic::ValidateFundClass(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateFundClass" ) );

   DString dstrFundCode, dstrClassCode, dstrEffectiveDate, dstrTransType, dstrTransTypeParam;

   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );

   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   dstrEffectiveDate.strip();

   if( !dstrFundCode.empty() && !dstrClassCode.empty() )
   {
       validBrokerFund ( FROMFUND, dstrFundCode, dstrClassCode, idDataGroup);
      
	  //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
	   // remove ineffective code
      validSalesrepFund ( FROMFUND, dstrFundCode, dstrClassCode, idDataGroup);

   }

   getField( ifds::TransType, dstrTransType, idDataGroup, false );
   dstrTransType.strip().upperCase();

   if( dstrTransType == I_("P") || dstrTransType == SAVING_PLAN )
      dstrTransTypeParam = PURCHASE_CODE;
   else if( dstrTransType == I_("S") )
      dstrTransTypeParam = REDEMPTION_CODE;
   else if (dstrTransType == AUTO_TRFER)
      dstrTransTypeParam = EX_FER_OUT_CODE;

   if( !dstrFundCode.empty() && !dstrClassCode.empty() )
   {
      SEVERITY sevRtn = _pMFAccount->canTradeFundClass (dstrFundCode, dstrClassCode, dstrTransTypeParam, dstrEffectiveDate, idDataGroup);
      setValidFlag(ifds::Amount,  idDataGroup, false);
      
      if( sevRtn <= WARNING )
      {
         if (dstrTransType == AUTO_TRFER)
            dstrTransTypeParam = I_( "ATO" );
         else dstrTransTypeParam = dstrTransType;

         sevRtn= stopFlagCheck( dstrFundCode, dstrClassCode, dstrTransTypeParam, idDataGroup);

      } // if sevRtn <= WARNING

   } // if fund and class are not empty

// if SegClient and CotClient do the SegFundValidation, for PAC and SWP only
   if( m_strSegClient == YES    && m_strCotClient == YES && 
       ( dstrTransType == I_("P") || dstrTransType == I_("S") ) )
   {
      FundMasterList *pFundMasterList (NULL);
      bool isSegFund = false;


      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList)
      {
         isSegFund = pFundMasterList->isSegregatedFund(dstrFundCode);
      }
      
      if(isSegFund)
      {
         ValidateSegFund( dstrFundCode, dstrClassCode, dstrEffectiveDate, idDataGroup );
      }
   }

   setFieldValidFlag( ifds::CompoundDate, idDataGroup, false );
}

//***********************************************************************************
SEVERITY Systematic::validateFromSoftCapCheck (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromSoftCapCheck"));
//implementations only for PAC's
   DString transType,
      stopDate, 
      stopDateDB,
      stopDateFormatted;
   
   getField (ifds::TransType, transType, idDataGroup, false);
   getField (ifds::StopDate, stopDate, idDataGroup, false);
   getFieldBeforeImage (ifds::StopDate, stopDateDB);
   DSTCommonFunctions::getFormat12319999Date (stopDateFormatted);

   bool stopDateModified = stopDateDB != stopDate;
   
   if (transType == TRADETYPE::PAC && (!stopDateModified || (stopDateModified && stopDate == stopDateFormatted)))
   {
      DString accountNum,
         fromFund,
         fromClass,
         tradeDate;

         getField (ifds::AccountNum, accountNum, idDataGroup, false);
         getField (ifds::FundCode, fromFund, idDataGroup, false);
         getField (ifds::ClassCode, fromClass, idDataGroup, false);
         getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
         getWorkSession().fundClassSoftCappedCheck(accountNum, fromFund, fromClass, I_("DD"), tradeDate, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Systematic::validateFundClassPayout(const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClassPayout"));

    DString dstrFundCode, dstrClassCode, dstrAmtTypeOvrd, dstrTransType;
    FundDetail *pFundDetail = NULL;

    getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
    getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
    getField(ifds::AmtTypeOvrd, dstrAmtTypeOvrd, idDataGroup, false);
    getField(ifds::TransType, dstrTransType, idDataGroup, false);

    dstrFundCode.strip().upperCase();
    dstrClassCode.strip().upperCase();
    dstrAmtTypeOvrd.strip().upperCase();
    dstrTransType.strip().upperCase();

    if (dstrTransType == SWP &&
        dstrAmtTypeOvrd != AMT_TYPE::PORTFOLIO && 
        !dstrFundCode.empty() && 
        !dstrClassCode.empty() &&
        getWorkSession().getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) &&  pFundDetail &&
        pFundDetail->isPortfolioPayoutFund(idDataGroup))
    {
        getErrMsg(IFASTERR::PLAN_CANNOT_BE_MANUALLY_CREATED, 
                  CND::ERR_PLAN_CANNOT_BE_MANUALLY_CREATED,
                  CND::WARN_PLAN_CANNOT_BE_MANUALLY_CREATED,
                  idDataGroup);
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY Systematic::validateToSoftCapCheck (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToSoftCapCheck"));
//implementations only for Automatic Exchanges (From Account = To Account)
   DString transType;
   getField (ifds::TransType, transType, idDataGroup, false);   
   
   if (transType == TRADETYPE::AUTO_TRANSFER)
   {
      DString accountTo, accountFrom, fromFund, fromClass, toFund, toClass, tradeDate;

      getField (ifds::AccountTo, accountTo, idDataGroup, false);
      getField (ifds::AccountNum, accountFrom, idDataGroup, false);
      getField( ifds::FundCode, fromFund, idDataGroup, false );
      getField( ifds::ClassCode, fromClass, idDataGroup, false );
      getField (ifds::FundToCode, toFund, idDataGroup, false);
      getField (ifds::ClassToCode, toClass, idDataGroup, false);
      getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);

      bool isExchange = accountTo == accountFrom;
      bool isTwitch = !accountTo.empty() && !accountFrom.empty() &&
                      accountTo != accountFrom &&
                      !fromFund.empty() && !fromClass.empty() &&
                      !toFund.empty() && !toClass.empty() &&
                      (fromFund.upperCase() != toFund.upperCase() || fromClass.upperCase() != toClass.upperCase());

      if (isExchange)
      {
         getWorkSession().fundClassSoftCappedCheck(accountTo, toFund, toClass, I_("EI"), tradeDate, idDataGroup);
      }
      else if (isTwitch)
      {
          getWorkSession().fundClassSoftCappedCheck(accountTo, toFund, toClass, I_("ED"), tradeDate, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Systematic::isFundSoftCapped ( const DString &fundCode, 
                                    const DString &classCode, 
                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isFundSoftCapped"));
   FundDetail *pFundDetail = NULL;
   bool bIsFundSoftCapped = false;

   if ( getWorkSession().getFundDetail ( fundCode, 
                                         classCode, 
                                         idDataGroup, 
                                         pFundDetail) &&
        pFundDetail)

   {
      bIsFundSoftCapped = pFundDetail->isFundSoftCapped(idDataGroup);
   }
   return bIsFundSoftCapped;
}

//************************************************************************************************
// Group Field: Fund Code and Class Code
void Systematic::ValidateSegFund( DString dstrFundCode, DString dstrClassCode, 
                                  DString dstrEffectiveDate,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateSegFund" ) );
   DString dstrAccountNum;
   if( !_pMFAccount->isNew() )
   {
      _pMFAccount->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
      if( (!dstrAccountNum.empty()) && (!dstrFundCode.empty()) && (!dstrClassCode.empty()) && (!dstrEffectiveDate.empty()) )
      {
         SeqFundValidation *pSeqFundValidation = NULL;
         if( getSeqFundValidation(pSeqFundValidation, idDataGroup, dstrFundCode, dstrClassCode, dstrAccountNum, dstrEffectiveDate ) <= WARNING )
         {
            pSeqFundValidation->canTradeFundClass( idDataGroup );

				DString dstrTransType;
				getField( ifds::TransType, dstrTransType, idDataGroup, false );
				dstrTransType.strip().upperCase();
				if ( dstrTransType == I_("AT") )

					pSeqFundValidation->addSegFundValidationWarnings( idDataGroup );
         }
      }
   }
   else
   {
      if( (!dstrFundCode.empty()) && (!dstrClassCode.empty()) && (!dstrEffectiveDate.empty()) )
      {
         DString dstrAcctDesignation, dstrTaxType, dstrPensionJuris, dstrDofBirth;
         DString dstrContractType, dstrMaturityType, dstrUserMaturityDate, dstrAgeBasedOn;
         DString dstrEffectDateCnt;
         _pMFAccount->getField(ifds::AcctDesignation, dstrAcctDesignation, idDataGroup);
         _pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup);
         _pMFAccount->getField(ifds::PensionJuris, dstrPensionJuris, idDataGroup);


         DString dstrContractTypeDt;
         _pFundDetailList->getField ( dstrFundCode, dstrClassCode, ifds::ContractType, dstrContractTypeDt, idDataGroup, false );
         ContractInfoList *pContractInfoList = NULL;
         if( _pMFAccount->getContractInfoList( pContractInfoList, idDataGroup ) <= WARNING && pContractInfoList )
         {
            BFObjIter iter( *pContractInfoList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

            while( !iter.end() )
            {
               iter.getObject()->getField( ifds::ContractType, dstrContractType, idDataGroup ) ;
               if( dstrContractType == dstrContractTypeDt )
               {
                  iter.getObject()->getField( ifds::EffectiveDate, dstrEffectDateCnt, idDataGroup );
                  iter.getObject()->getField( ifds::MaturityType, dstrMaturityType, idDataGroup );
                  iter.getObject()->getField( ifds::UserMaturityDate, dstrUserMaturityDate, idDataGroup );
                  iter.getObject()->getField( ifds::AgeBasedOn, dstrAgeBasedOn, idDataGroup );
                  break;
               }
               ++iter;
            }
         }


         DString dstrEntityId;
         
         if (getWorkSession().isNonRegLike( dstrTaxType )
            && dstrAgeBasedOn == I_("01") )
            //non-reg accounts and agebasedon = '01', get annuitant's dofbirth
         {
            ACCTENTITYOBJ_VECTOR v_annuitants;
            ACCTENTITYOBJ_VECTOR::iterator v_iter;

            _pMFAccount->getAnnitants (v_annuitants, idDataGroup);
            for (v_iter = v_annuitants.begin(); v_iter != v_annuitants.end(); ++v_iter)
            {
               DString entitySeq;
               
               (*v_iter)->getField (ifds::SeqNumber, entitySeq, idDataGroup, false);
               if (entitySeq == I_("1"))
               {
                  (*v_iter)->getField (ifds::EntityId, dstrEntityId, idDataGroup, false);
                  break;
               }
            }
         }
         else // registered accounts, annuitant is also account owner, get owner's dofbirth
         {
            _pMFAccount->GetEntityIdForAcctOwnerSeq1 (idDataGroup, dstrEntityId);
         }


         Entity *pEntity = NULL;
         if( getWorkSession().getEntity(  idDataGroup, dstrEntityId, pEntity ) <= WARNING && pEntity )
         {
            pEntity->getField( ifds::DofBirth, dstrDofBirth, idDataGroup, false );
         }


         SeqFundValidation *pSeqFundValidation = NULL;
         pSeqFundValidation = new SeqFundValidation ( *this );
         DString strTag = I_("SeqFundValidation");
         if( pSeqFundValidation->init( dstrFundCode, dstrClassCode, dstrEffectiveDate,
                                       dstrAcctDesignation, dstrTaxType, dstrPensionJuris,
                                       dstrDofBirth, dstrContractType, dstrMaturityType,
                                       dstrUserMaturityDate, dstrAgeBasedOn ) <= WARNING )
            setObject( pSeqFundValidation, strTag, OBJ_ACTIVITY_NONE, idDataGroup );
         else
         {
            delete pSeqFundValidation;
            pSeqFundValidation = NULL;
         }
         if( pSeqFundValidation )
         {
            DString dstrAcctGroup;
            _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);
            pSeqFundValidation->validateSegFund( dstrAcctGroup, dstrEffectiveDate, dstrEffectDateCnt, dstrContractType, idDataGroup );
         }
      }
   }
}

//************************************************************************************************
void Systematic::ValidateAllocation(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAllocation" ) );

   DString dstrFundCode, dstrClassCode, strKey, dstrFromAccount;
   ////////////////////////////////////////////
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   DString dstrTransType, dstrTransTypeParam;
   getField( ifds::TransType, dstrTransType, idDataGroup, false );
   dstrTransType.strip().upperCase();

   if( dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING )
   {
      if (dstrTransType != AUTO_TRFER)
      {
         BFObjIter iter(*_pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         while( !iter.end() )
         {
            BFAbstractCBO *pBFCBO = iter.getObject();
            //dynamic_cast<SysAllocation*>(pBFBase)->getField(DBR::FundClass, dstrClassCode, idDataGroup, false);
            SEVERITY sevRtn = dynamic_cast<SysAllocation*>(pBFCBO)->doValidateField(ifds::FundClass, dstrClassCode, idDataGroup);
            ++iter;
         }
      }
      else if(	dstrTransType == AUTO_TRFER)
      {


      }
   }
   else if( dstrFundCode.empty() && !dstrClassCode.empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BLANK_FUND );
   }
   else if( !dstrFundCode.empty() && dstrClassCode.empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BLANK_CLASS );
   }

}

//************************************************************************************************
SEVERITY Systematic::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );


   if( idField == ifds::SystematicPayType )
   {

      DString strSystematicPayType;
      BFCBO::getField(ifds::SystematicPayType, strSystematicPayType, idDataGroup, false);

      DString dstrPayType, dstrTransType;
      parsingCombinedField(strSystematicPayType, dstrTransType, dstrPayType, I_("-"));
      dstrTransType.upperCase();
      dstrPayType.upperCase();

      setField( ifds::TransType, dstrTransType, idDataGroup, false );
      setField( ifds::PayType, dstrPayType, idDataGroup, false );
      setFieldStatus( idDataGroup, dstrTransType == SAVING_PLAN );
      //setFieldReadOnly( DBR::SystematicPayType, idDataGroup, true );
      setAmtTypeSubList ( idDataGroup ); // set AmountType Substitution list
      if( !_pMFAccount ) {
         if( !_pList )
            _pList = dynamic_cast<SystematicList *>(getParent());
         if( _pList )
            _pMFAccount = _pList->getMFAccount();
      }
      if( _pMFAccount ) {
         if ( _pMFAccount->isAMSAccount ( idDataGroup ) ) {
            DString dstrPACSWPOverride;
            getWorkSession().getOption( ifds::PACSWPOverride, dstrPACSWPOverride, idDataGroup, false); 
            if ( dstrPACSWPOverride == YES ) {
               if ( dstrTransType == AUTO_TRFER ) {
                  setFieldReadOnly ( ifds::FrFundNumber, idDataGroup, false );
                  setFieldReadOnly ( ifds::FundCode, idDataGroup, false );
                  setFieldReadOnly ( ifds::ClassCode, idDataGroup, false );
                  setFieldReadOnly ( ifds::ToFundNumber, idDataGroup, true );
                  setFieldReadOnly ( ifds::FundToCode, idDataGroup, true );
                  setFieldReadOnly ( ifds::ClassToCode, idDataGroup, true );
               } else {
                  setFieldReadOnly ( ifds::FrFundNumber, idDataGroup, true );
                  setFieldReadOnly ( ifds::FundCode, idDataGroup, true );
                  setFieldReadOnly ( ifds::ClassCode, idDataGroup, true );
                  setFieldReadOnly ( ifds::ToFundNumber, idDataGroup, false );
                  setFieldReadOnly ( ifds::FundToCode, idDataGroup, false );
                  setFieldReadOnly ( ifds::ClassToCode, idDataGroup, false );
               }
            }
         }
      }

		systematicPayTypeRelatedChangesForFileProcessor( idDataGroup );
		
		setValidFlag(ifds::SystematicCrossField2,  idDataGroup, false);
		
		//P0186486_FN15_The Source of Funds
      payTypeRelatedChanges( idDataGroup );
   }

   DString dstrPayType, dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   getField(ifds::PayType, dstrPayType, idDataGroup, false);
   dstrTransType.strip().upperCase();
   dstrPayType.strip().upperCase();

   DString dstrOPCNonFinConfDefPAC;
   getWorkSession().getOption(ifds::OPCNonFinConfDefPAC, dstrOPCNonFinConfDefPAC, BF::HOST, false);
   dstrOPCNonFinConfDefPAC.strip().upperCase();

   //setting the default allocations
   if( idField == ifds::TransType )
   {
      _dstrTransType = dstrTransType;
      DString dstrCurrSubList; 
	   BFProperties *pBFProperties = getFieldProperties (ifds::SystematicGridLeftHeading, idDataGroup); 
	   assert (pBFProperties);
      if(PAC == dstrTransType && pBFProperties )
      {
         pBFProperties->reinitAllSubstValues();
      }
      else
		{
			if (pBFProperties) 
			{
				pBFProperties->getAllSubstituteValues (dstrCurrSubList);
				dstrCurrSubList = removeItemFromSubtList( ifds::SystematicGridLeftHeading,I_("PSDAdvice"), idDataGroup);
				setFieldAllSubstituteValues(ifds::SystematicGridLeftHeading, idDataGroup, dstrCurrSubList);
			}
			setFieldNoValidate(ifds::PSDAdvice, NULL_STRING, idDataGroup, false, true, true, false);  
		 } 
      populateFieldsWithDefaultValues(idDataGroup, MODE_INIT);  
      setAmtTypeSubList ( idDataGroup ); // set AmountType Substitution list

      setupDefaultAllocationList( idDataGroup);
      setFrequencySubstitution(idDataGroup);
      setFieldReadOnly( ifds::AdminFeeAmt, idDataGroup, (dstrTransType == AUTO_TRFER));

      if( dstrTransType == AUTO_TRFER )
      {
//CP20030319         setFieldStateFlags( ifds::FundCode, idDataGroup,BFCBO::STATE_FLAGS::REQUIRED   );
   setFieldRequired( ifds::FundCode, idDataGroup, true );
//CP20030319         setFieldStateFlags( ifds::ClassCode, idDataGroup,BFCBO::STATE_FLAGS::REQUIRED  );
   setFieldRequired( ifds::ClassCode, idDataGroup, true );
//CP20030319         long  lFlag = getFieldStateFlags( ifds::DayOfWeek, idDataGroup );
//CP20030319         setFieldStateFlags(ifds::BankAcctNum, idDataGroup, lFlag | BFCBO::STATE_FLAGS::REQUIRED);     
   setFieldRequired( ifds::BankAcctNum, idDataGroup, true );
         setFieldNoValidate( ifds::PayType, I_("AT"), idDataGroup );
         setFieldNoValidate( ifds::Fee, I_("0"), idDataGroup );

         setValidFlag(ifds::FundCode,  idDataGroup,  false);
         setValidFlag(ifds::ClassCode, idDataGroup,  false);
         setValidFlag(ifds::Amount,    idDataGroup,  false);
         if( _featureSplitComm != COMMISSION_TYPE_ZERO && isNew() )
            _pAtAcctAllocationList->GetDefaultSplitComm ( idDataGroup );
      }
      else
      {
         if( (_featureBankLayout == I_("1") || _featureBankLayout  == I_("2")) && dstrTransType == PAC )
         {
            setFieldNoValidate( ifds::SrcOfFund, I_("03"), idDataGroup, false );
         }

//CP20030319         long lstate  = getFieldStateFlags(ifds::FundCode, idDataGroup );
//CP20030319         setFieldStateFlags( ifds::FundCode, idDataGroup,lstate & (!BFCBO::STATE_FLAGS::REQUIRED)  );
         setFieldRequired( ifds::FundCode, idDataGroup, false );
//CP20030319         lstate  = getFieldStateFlags(ifds::ClassCode, idDataGroup );
//CP20030319         setFieldStateFlags( ifds::ClassCode, idDataGroup,lstate & (!BFCBO::STATE_FLAGS::REQUIRED)   );
         setFieldRequired( ifds::ClassCode, idDataGroup, false );

//CP20030319         long   lFlag = getFieldStateFlags( ifds::DayOfWeek, idDataGroup );
//CP20030319         setFieldStateFlags(ifds::BankAcctNum, idDataGroup, lFlag & (~BFCBO::STATE_FLAGS::REQUIRED));
         setFieldRequired( ifds::BankAcctNum, idDataGroup, false );

         if( _dstrmultiCurrency == YES )
         {
            DString dstrSysCurrency;
            _pMgmtCoOption->getField( ifds::SysCurrency,   dstrSysCurrency, idDataGroup ,false );

            setFieldNoValidate( ifds::BankAcctCurrency,    dstrSysCurrency, idDataGroup, false, false, true, false );
            setFieldReadOnly( ifds::BankAcctCurrency, idDataGroup, false );
         }
         else
         {
            setFieldReadOnly( ifds::BankAcctCurrency, idDataGroup, true );
         }

         if( _featureSplitComm != COMMISSION_TYPE_ZERO && isNew() )
            _pSysAllocationList->GetDefaultSplitComm ( idDataGroup );

         BFObjIter iter(*_pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         while( !iter.end() )
         {
            SysAllocation *pSysAlloc = dynamic_cast<SysAllocation* >(iter.getObject() );
            if( pSysAlloc )
            {
               pSysAlloc->setTransTypePACIdFromSystematic(idDataGroup );  
            }
            ++iter;
         }
      } // else for PAC/SWP/SAVING PLAN

      DString dstNFConfBnkDetl, dstrAcctNonFinConfirm;
      SystematicList* pSystematicList = dynamic_cast<SystematicList*>(getParent());
      MFAccount *pMFAccount = NULL;
      getWorkSession().getOption(ifds::NFConfBnkDetl, dstNFConfBnkDetl, BF::HOST, false);    
      dstNFConfBnkDetl.stripAll().upperCase();

      pMFAccount = pSystematicList->getMFAccount();
      if (pMFAccount)
          pMFAccount->getField(ifds::NonFinConfirm, dstrAcctNonFinConfirm, BF::HOST);

      dstrAcctNonFinConfirm.stripAll().upperCase();

      //Set default value.
      if (dstrOPCNonFinConfDefPAC == YES)
      {
          if (dstrTransType == PAC)
          {
              setField(ifds::NonFinConfirms, NF_REQUIRED,  idDataGroup, false); 
              setFieldReadOnly(ifds::NonFinConfirms, idDataGroup, false);
          }
          else
          {
              setField(ifds::NonFinConfirms, NF_SUPPRESS, idDataGroup, false);
              setFieldReadOnly (ifds::NonFinConfirms, idDataGroup, true );
          }
      }
      else
      {
          if(dstNFConfBnkDetl == I_("N") || dstrAcctNonFinConfirm == I_("N"))
          {
              setField(ifds::NonFinConfirms, NF_SUPPRESS, idDataGroup, false);
              setFieldReadOnly (ifds::NonFinConfirms, idDataGroup, true );
          }
          else
          {
              setField(ifds::NonFinConfirms, I_(""), idDataGroup, false);
              setFieldRequired(ifds::NonFinConfirms, idDataGroup, true);
          }
      }

      transTypeWHTaxRelatedChanges( idDataGroup );
	  setPayMethod(idDataGroup);
   }

   if( idField == ifds::Frequency )
   {
      DString strFreq;
      getField(ifds::Frequency, strFreq, idDataGroup, false);
      strFreq.strip();
      if( strFreq == FREQ_WEEKLY || strFreq == FREQ_BIWEEKLY || strFreq == FREQ_DAILY )
      {
//CP20030319         long lFlag = getFieldStateFlags(ifds::DayOfWeek, idDataGroup);
//CP20030319         setFieldStateFlags(ifds::DayOfWeek, idDataGroup, lFlag | BFCBO::STATE_FLAGS::REQUIRED);
   setFieldRequired( ifds::DayOfWeek, idDataGroup, true );
         setValidFlag(ifds::DayOfWeek, idDataGroup, false);
      }
      else
      {
         setFieldNoValidate(ifds::DayOfWeek, NULL_STRING, idDataGroup );
//CP20030319         long lFlag = getFieldStateFlags(ifds::DayOfWeek, idDataGroup);
//CP20030319         setFieldStateFlags(ifds::DayOfWeek, idDataGroup, lFlag & (~BFCBO::STATE_FLAGS::REQUIRED));
         setFieldRequired(ifds::DayOfWeek, idDataGroup, false );
         setValidFlag(ifds::DayOfWeek, idDataGroup, true);

         DString dstrEOM;
         getField( ifds::EndOfMonth, dstrEOM, idDataGroup, false );
         dstrEOM.strip().upperCase();
         if( dstrEOM != YES && dstrEOM != NO )
            setFieldNoValidate( ifds::EndOfMonth, NO, idDataGroup , false);
      }

      DString dstrTransType;
      getField(ifds::TransType, dstrTransType, idDataGroup, false);
      dstrTransType.strip().upperCase();
      if( dstrTransType != AUTO_TRFER )
      {
         setDefaultMonthlyIndicator(idDataGroup);
      }

   }

   if( idField == ifds::FundCode || idField == ifds::ClassCode )
   {
      setValidFlag(ifds::FundClass, idDataGroup, false);
      setValidFlag(ifds::CompoundDate,   idDataGroup, false );
      DString dstrFundCode, dstrClassCode, dstrFundCurrency;
      getField( ifds::FundCode, dstrFundCode, idDataGroup, false );
      getField( ifds::ClassCode, dstrClassCode, idDataGroup, false );
      dstrFundCode.strip().upperCase();
      dstrClassCode.strip().upperCase();

      if( dstrFundCode != NULL_STRING && dstrClassCode != NULL_STRING )
      {
         _pFundDetailList->getField ( dstrFundCode, dstrClassCode, ifds::Currency, dstrFundCurrency, BF::HOST, false );

         setFieldNoValidate( ifds::FeeCurrency, dstrFundCurrency, idDataGroup, false, true, true );
         setFieldNoValidate( ifds::AdminFeeCurr, dstrFundCurrency, idDataGroup, false, true, true );
         DString dstrBankCurrency;
         getField( ifds::BankAcctCurrency, dstrBankCurrency, idDataGroup, false );
         dstrBankCurrency.strip();
         if( dstrBankCurrency == NULL_STRING )
            setFieldNoValidate( ifds::BankAcctCurrency, dstrFundCurrency, idDataGroup, false, false, true,false );

         updateAmountTypeRelatedFields(idDataGroup);
         setAmtTypeSubList(idDataGroup);
      }
      else
      {
         setFieldNoValidate( ifds::FeeCurrency, NULL_STRING, idDataGroup, false, true, true );
         setFieldNoValidate( ifds::AdminFeeCurr, NULL_STRING, idDataGroup, false, true, true );
      }
		if( !dstrFundCode.empty() && isCappedFund( dstrFundCode, idDataGroup ) )
		{
			setValidFlag( ifds::Amount,idDataGroup,false );		
		}
      setDisableAcqFee(idDataGroup);
	  if( isNew())
	  {
	     RDRAdviceRelatedChanges(idDataGroup);
	  }
   }


//CP20030319   long lFlag;

   if( idField == ifds::PayType )
   {
      if( !PayTypeIsEFT( idDataGroup ) )
      {
         setFieldNoValidate( ifds::InstCode, NULL_STRING, idDataGroup );
         setFieldNoValidate( ifds::SwiftCode, I_("00000000"), idDataGroup );
         setFieldNoValidate( ifds::RefNumber, I_("00000000"), idDataGroup );
         setFieldNoValidate( ifds::TransitNo, NULL_STRING, idDataGroup );

         setFieldNoValidate( ifds::BankAcctNum, NULL_STRING, idDataGroup );

         setFieldNoValidate( ifds::BankAcctName, NULL_STRING, idDataGroup );
         setFieldNoValidate( ifds::BankAcctType, NULL_STRING, idDataGroup );
         setFieldNoValidate( ifds::InstName, NULL_STRING, idDataGroup );

//CP20030319         lFlag = getFieldStateFlags( ifds::BankAcctNum, idDataGroup );
//CP20030319         setFieldStateFlags(ifds::BankAcctNum, idDataGroup, lFlag & (~BFCBO::STATE_FLAGS::REQUIRED));
         setFieldRequired(ifds::BankAcctNum, idDataGroup, false );

         setValidFlag(ifds::BankAcctNum, idDataGroup, true);

         setValidFlag(ifds::InstCode,   idDataGroup, true);
         setValidFlag(ifds::SwiftCode,  idDataGroup, true);
         setValidFlag(ifds::RefNumber,  idDataGroup, true);
         setValidFlag(ifds::TransitNo,  idDataGroup, true);
         setValidFlag(ifds::BankAcctName, idDataGroup, true);
         setValidFlag(ifds::BankAcctType, idDataGroup, true);
         setValidFlag(ifds::InstName,   idDataGroup, true);

         if( !(dstrTransType == I_("S") && (dstrPayType == I_("C") ||
                                            dstrPayType == I_("S")   ||
                                            dstrPayType == I_("M"))) )
         {
            //clear the address information
            setFieldNoValidate( ifds::AddrCode,  NULL_STRING, idDataGroup );
            //setFieldStateFlags(DBR::AddrCode, idDataGroup, lFlag & (~BFBase::STATE_FLAGS::REQUIRED));
            setValidFlag(ifds::AddrCode,   idDataGroup, true);
            setValidFlag(ifds::AddrLine1,  idDataGroup, true);
            setValidFlag(ifds::AddrLine2,  idDataGroup, true);
            setValidFlag(ifds::AddrLine3,  idDataGroup, true);
            setValidFlag(ifds::AddrLine4,  idDataGroup, true);
            setValidFlag(ifds::AddrLine5,  idDataGroup, true);
            setValidFlag(ifds::PostalCode, idDataGroup, true);

            setFieldNoValidate( ifds::AddrLine1, NULL_STRING, idDataGroup );
            setFieldNoValidate( ifds::AddrLine2, NULL_STRING, idDataGroup );
            setFieldNoValidate( ifds::AddrLine3, NULL_STRING, idDataGroup );
            setFieldNoValidate( ifds::AddrLine4, NULL_STRING, idDataGroup );
            setFieldNoValidate( ifds::AddrLine5, NULL_STRING, idDataGroup );
            setFieldNoValidate( ifds::PostalCode,NULL_STRING, idDataGroup );
         }
         else
         {
//CP20030319            lFlag = getFieldStateFlags(ifds::AddrCode, idDataGroup);
            //setFieldStateFlags(DBR::AddrCode, idDataGroup, lFlag | BFBase::STATE_FLAGS::REQUIRED);
            setValidFlag(ifds::AddrCode, idDataGroup, false);
         }
      }
      else
      {
         DString dstAcctNum, str;
         //getField(ifds::AccountNum, dstAcctNum, idDataGroup, false);

         //getWorkSession().getFirstSequenced01AccountholderEntityName( idDataGroup, dstAcctNum, str);
         if( !_pMFAccount )
         {
            if( !_pList )
               _pList = dynamic_cast<SystematicList *>(getParent());
            if( _pList )
               _pMFAccount = _pList->getMFAccount();
         }
         if( _pMFAccount )
            _pMFAccount->getAcctName(str, idDataGroup);
         str.strip(); 
         setFieldNoValidate(ifds::BankAcctName, str, idDataGroup, false);

         getWorkSession().getOption( ifds::DefaultBankType, str, idDataGroup, false );
         setFieldNoValidate( ifds::BankIdType, str, idDataGroup, false);
         setFieldNoValidate( ifds::BankAcctType, I_( "1" ), idDataGroup, false);

//CP20030319         lFlag = getFieldStateFlags(ifds::BankAcctNum, idDataGroup);
//CP20030319         setFieldStateFlags(ifds::BankAcctNum, idDataGroup, lFlag | BFCBO::STATE_FLAGS::REQUIRED);
   setFieldRequired( ifds::BankAcctNum, idDataGroup, true );
         setValidFlag(ifds::BankAcctNum, idDataGroup, false);
      }
            
      //P0186486_FN15_The Source of Funds
      payTypeRelatedChanges( idDataGroup );
   }

   if( idField == ifds::CompoundDate )
   {
      setValidFlag(ifds::FundClass, idDataGroup, false);
   }
   if( idField == ifds::AccountTo || idField == ifds::FundToCode || idField == ifds::ClassToCode )
   {
      if (dstrTransType == AUTO_TRFER )
      {
         setATAllocation(idDataGroup);
         DString dstrFrAccountNum, dstrAccountTo;
         getField( ifds::AccountNum, dstrFrAccountNum, idDataGroup, false );
         dstrFrAccountNum.strip().stripLeading( I_CHAR("0") );

         getField( ifds::AccountTo, dstrAccountTo, idDataGroup, false ) ;
         dstrAccountTo.strip().stripLeading('0');

         if( dstrFrAccountNum == dstrAccountTo )
         {
            setExchInFee( idDataGroup );
            setExchOutFee( idDataGroup );
         }
         if( idField == ifds::FundToCode || idField == ifds::ClassToCode )
         {
            setValidFlag(ifds::AtFundtoClasstoCrossEdit, idDataGroup, false);
            setDisableAcqFee(idDataGroup);
				
				DString dstrAmountType;
				getField( ifds::AmountType, dstrAmountType, idDataGroup );
				dstrAmountType.strip().upperCase();
				if ( DSTCommonFunctions::codeInList ( dstrAmountType, I_("F,T,M,X,Y") ) )
				{
					setValidFlag(ifds::AmountType, idDataGroup, false);
				}
         }
      }
   }
   if( ( idField == ifds::EffectiveDate) || ( idField == ifds::FlatPercent) )
   {
      if (dstrTransType != AUTO_TRFER) 
      {
         _pSysAllocationList->GetDefaultSplitComm ( idDataGroup );
      }
      else
      {
         _pAtAcctAllocationList->GetDefaultSplitComm ( idDataGroup );
      }

		if (idField == ifds::FlatPercent)
		{
			DString dstrFee;

			getField (ifds::Fee, dstrFee, idDataGroup, true);
			setFieldNoValidate (ifds::Fee, dstrFee, idDataGroup, true, false, true, false);
			revalidateField (ifds::Fee, idDataGroup);
		}
       if( idField == ifds::EffectiveDate && isNew() )
	   {
		   RDRAdviceRelatedChanges(idDataGroup);
	   }
   }
   if( idField == ifds::StatusCode /* && !isNew()*/ )
   {
      setFieldsToReadonlyWhenForBadRecord(idDataGroup);
      //setFieldReadOnly( DBR::StatusCode, idDataGroup, true );
   }

   if( idField == ifds::PlanCode )
   {
      setFieldReadOnly( ifds::VUBFee, idDataGroup, false );
      if( isNew() )
      {
         SavingPlanMasterList *pSavingPlanMasterList;
         getMgmtCo().getSavingPlanMasterList( pSavingPlanMasterList );

         DString tmp, percentage, frac1, frac2;
         BFCBO::getField(ifds::PlanCode, tmp, idDataGroup, false);
         BFObjIter bfIter( *pSavingPlanMasterList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         bfIter.positionByKey( tmp );
         BFAbstractCBO *pObj;
         if( !bfIter.end( ) )
         {
            pObj = bfIter.getObject();
            //pObj->getField( DBR::AnnualFeeAmt, tmp, idDataGroup, false );
            //setFieldNoValidate( DBR::AnnualFeeAmt, tmp, idDataGroup, false, true, true );
            pObj->getField( ifds::VUBFeeFrac1, frac1, idDataGroup, false );
            setFieldNoValidate( ifds::VUBFeeFrac1, frac1, idDataGroup, false, true, true );
            pObj->getField( ifds::VUBFeeFrac2, frac2, idDataGroup, false );
            setFieldNoValidate( ifds::VUBFeeFrac2, frac2, idDataGroup, false, true, true );
            pObj->getField( ifds::VUBFeeRate, percentage, idDataGroup, false );
            setFieldNoValidate( ifds::VUBFeeRate, percentage, idDataGroup, false, true, true );
            pObj->getField( ifds::VUBFeeType, tmp, idDataGroup, false );
            setFieldNoValidate( ifds::VUBFeeType, tmp, idDataGroup, false, true, true );

            if( tmp == VUB_FEE_TYPE_FRACTION )
            {
               tmp = NULL_STRING;
               getFraction( tmp, frac1, frac2 );
            }
            else
            {
               tmp = percentage;
            }
            setFieldNoValidate( ifds::VUBFee, tmp, idDataGroup, false, true, true );
         }
      }

      setFieldReadOnly( ifds::PlanCode, idDataGroup, true );
      setFieldReadOnly( ifds::VUBFee, idDataGroup, true );
   }

   if( idField == ifds::VUBFeeType )
   {
      DString strVUBFee;
      getVUBFee( strVUBFee, idDataGroup );
      BFCBO::setField( ifds::VUBFee, strVUBFee, idDataGroup, true, true );
   }

   if( idField == ifds::VUBFee )
   {
      DString strVUBFee;
      BFCBO::getField(ifds::VUBFee, strVUBFee, idDataGroup, false);
      setVUBFee(strVUBFee, idDataGroup);
   }
   if( isNew() && ( idField == ifds::FundCode || idField == ifds::ClassCode || idField == ifds::Amount ||
                    idField == ifds::FundToCode || idField == ifds::ClassToCode ) )
   {
      setDefaultAcquisitionFee( idDataGroup );   
	  setValidFlag(ifds::CompoundDate,   idDataGroup, false );
   }

   // notify the grid to recalculate and load VUBExpectedAmt
   // only happen when isnew
   if( isNew() && dstrTransType == SAVING_PLAN && (idField == ifds::Amount ||
                                                   idField == ifds::VUBFee ||
                                                   idField == ifds::VUBFeeFrac2) )
   {
      DString strVUBExpectedAmt;
      getVUBExpectedAmt(strVUBExpectedAmt, idDataGroup);

      BFCBO::setField( ifds::VUBExpectedAmt, strVUBExpectedAmt, idDataGroup, true, true );
      setUpdatedFlag( ifds::InitialAmt, idDataGroup, true );
      setValidFlag ( ifds::VUBCrossedit, idDataGroup, false );
      //	processCrossEdits( DBR::InitialAmt, idDataGroup );
   }

   if( idField == ifds::VUBPayOption )
   {
      DString strVUBPayOption, strVUBExpectedAmt;
      getField( ifds::VUBPayOption, strVUBPayOption, idDataGroup, false );

      if( strVUBPayOption == VUBOPTION_WAIVED )
      {
         setFieldNoValidate( ifds::VUBExpectedAmt, I_("0"), idDataGroup, false, false, true );
      }
      else if( strVUBPayOption == INITIAL_VUB )
      {
//CP20030319         setFieldStateFlags( ifds::InitialAmt, idDataGroup, BFCBO::STATE_FLAGS::REQUIRED   );
   setFieldRequired( ifds::InitialAmt, idDataGroup, true );
      }
      else if( strVUBPayOption == MONTHLY_VUB && isNew() )
      {
         getVUBExpectedAmt(strVUBExpectedAmt, idDataGroup);
         setFieldNoValidate( ifds::VUBExpectedAmt, strVUBExpectedAmt, idDataGroup, false, true, true );
      }

      // force validate crossedit VUBCrossedit
      /*setValidFlag ( DBR::InitialAmt, idDataGroup, true );
      setValidFlag ( DBR::VUBExpectedAmt, idDataGroup, true ); */
      setValidFlag ( ifds::VUBCrossedit, idDataGroup, false );
      //processCrossEdits( DBR::InitialAmt, idDataGroup );
   }
   if( idField == ifds::MonthIndicator )
   {
      setMonths(idDataGroup);
   }

   if( idField == ifds::EffectiveDate ) 
   {
      setDefaultMonthlyIndicator(idDataGroup);
      // Reload the AMS allocation
      MFAccount* pMFAccount = NULL;   

      if (dstrTransType == AUTO_TRFER) 
      {
         DString dstrAccountNum;

         getField (ifds::AccountTo, dstrAccountNum, idDataGroup);
         getMFAccount (dstrAccountNum, idDataGroup, pMFAccount);
      } 
      else 
      {
         pMFAccount = _pMFAccount;
      }
      if (pMFAccount && pMFAccount->isAMSAccount ( idDataGroup ) && isNew() ) 
      {
         DString dstrAmount;

         getField( ifds::Amount, dstrAmount, idDataGroup );
         setupDefaultAllocationList( idDataGroup, dstrAmount, true );
      }
   }
   if( idField == ifds::BankAcctCurrency )
   {
      DString dstrFund, dstrValue;
      getField ( ifds::FundCode, dstrFund, idDataGroup );
      getField ( ifds::BankAcctCurrency, dstrValue, idDataGroup );
      dstrValue.strip().upperCase();

      // the only way to change the bankacctcurrency of non-multicurrency is either by modifing the fund or 
      // modifing the allocation fund. No need to change the allocation if the change is initial from 
      // allocation
      if( _dstrmultiCurrency == NO && dstrFund.strip() != NULL_STRING )
      {
         BFObjIter iter(*_pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         while( !iter.end() )
         {
            BFAbstractCBO *pBFCBO = iter.getObject();
            if( pBFCBO )
               pBFCBO->setField(ifds::SettleCurrency, dstrValue, idDataGroup, false, true);
            ++iter;
         }
      }

      DString dstrAmount;
      BFCBO::getField(ifds::Amount, dstrAmount, idDataGroup, false);
      //setAmountField(ifds::Amount, dstrAmount, idDataGroup, false, false); //no side effect require since only doing format
      getFormattedAmount(idDataGroup, dstrAmount);
      setFieldNoValidate(ifds::Amount, dstrAmount, idDataGroup, true, false, true, false);

		setFileProcessor( idDataGroup );
   }
	if ( idField == ifds::PayMethod )
	{
		payMethodRelatedChanges( idDataGroup );
	}
	if ( idField == ifds::ACHProcessor )
	{
		setSettleCurrency( idDataGroup );
		// Set bank File Processor field and make it read only
	}

	if ( ifds::FedTaxPUDOverride == idField )
	{		
		// If Federal Override is No, then don't allow any entry for Rate
		DString dstrFedTaxPUDOverride;
		getField( idField, dstrFedTaxPUDOverride, idDataGroup );			
		setFieldReadOnly( ifds::FedRate, idDataGroup, I_( "0" ) == dstrFedTaxPUDOverride.strip() );		
	}
	if ( ifds::ProvTaxPUDOverride == idField )
	{			
		// If Provincial Override is No, then don't allow any entry for Rate
		DString dstrProvTaxPUDOverride;
		getField( idField, dstrProvTaxPUDOverride, idDataGroup );
		setFieldReadOnly( ifds::ProvRate, idDataGroup, I_( "0" ) == dstrProvTaxPUDOverride.strip() );		
	}

	if ( ifds::AmountType == idField )
	{		
		// Incident #591211 for Automatic Transfer, amount will be set to zero for all F, T, X, Y and M				
      DString dstrAmountType;

		getField( ifds::AmountType, dstrAmountType, idDataGroup );
		dstrAmountType.strip().upperCase();
       
	   bool bAmountReadOnly = false;
      if (DSTCommonFunctions::codeInList ( dstrAmountType, GWLWA_OPTIONS))
		{
			calculateAmount (dstrAmountType, idDataGroup);
			bAmountReadOnly = true;
		}
		
		setFieldReadOnly (ifds::Amount, idDataGroup, bAmountReadOnly );
		
		if (dstrTransType == AUTO_TRFER ) 
		{
			//DString dstrAmountType;
			//getField( ifds::AmountType, dstrAmountType, idDataGroup );
			//dstrAmountType.strip().upperCase();
			if ( DSTCommonFunctions::codeInList ( dstrAmountType, I_("F,T,M,X,Y") ) )
			{
				setFieldNoValidate (ifds::Amount, I_("0") , idDataGroup, true, false, true, false);
				setFieldReadOnly (ifds::Amount, idDataGroup, true );
			}
			else
			{
				setFieldReadOnly (ifds::Amount, idDataGroup, false );
			}
		}
	
		bool bIsRDSPAccount = _pMFAccount->isRDSPAccount(idDataGroup);

		if (bIsRDSPAccount && dstrTransType == SWP && DSTCommonFunctions::codeInList(dstrAmountType, I_("A,D,N,O")))
		{
			setFieldNoValidate( ifds::GrossOrNet, YES, idDataGroup, false, false, true );
			setFieldReadOnly (ifds::GrossOrNet, idDataGroup, true);
		}
		}

   //P0186486_FN15_The Source of Funds
   if( idField == ifds::SrcOfFund )
   {         
         setValidFlag ( ifds::SourceOfBankAcct, idDataGroup, false ); 
      }
   else if(idField == ifds::SourceOfBankAcct)
   {
   
   }
    

   if(idField == ifds::StopDate)
   {
      DString dstrStopDate;
      getField(ifds::StopDate, dstrStopDate, idDataGroup, false);
      DString dstr12319999Date;
      DSTCommonFunctions::getFormat12319999Date(dstr12319999Date);
      if(dstrStopDate == dstr12319999Date)
      {
         setFieldNoValidate(ifds::StopReasonPAC, I_("00"), idDataGroup, false, true, false, false);   
      }

//      setFieldReadOnly(ifds::StopReasonPAC, idDataGroup, dstrStopDate == dstr12319999Date);


   }
   //bool bVerificationEnabled = false;
 
   //getWorkSession().isVerificationEnabled (idDataGroup, VERIFY_CATEGORY_SYSTEMATIC, VERIFY_LEVEL_ACCOUNT, bVerificationEnabled);
   //if(bVerificationEnabled)
   //{
   //   setFieldReadOnly (ifds::VerifyStat, idDataGroup, true );
   //   setField(ifds::VerifyStat, I_("02"), idDataGroup, false); // unverified

   //}

   if(idField != ifds::VerifyStat && !binit)
   {	  
	  bool bVerificationEnabled = false;
 
      getWorkSession().isVerificationEnabled (idDataGroup, VERIFY_CATEGORY_SYSTEMATIC, VERIFY_LEVEL_ACCOUNT, bVerificationEnabled);
	
	  if( bVerificationEnabled )
	  {
		  DString dstrVerifyStat;
		  getField(ifds::VerifyStat, dstrVerifyStat, idDataGroup, false);
		  if(dstrVerifyStat == I_("01"))
		  {
			  setField(ifds::VerifyStat, I_("02"), idDataGroup, false);
			  setFieldReadOnly (ifds::VerifyStat, idDataGroup, true);
		  }
	  }

      /*DString dstNFConfBnkDetl;
      getWorkSession().getOption( ifds::NFConfBnkDetl, dstNFConfBnkDetl, BF::HOST, false );    
      dstNFConfBnkDetl.strip();

      DString dstrAcctNonFinConfirm;
      SystematicList* pSystematicList = dynamic_cast <SystematicList*> (getParent());
      MFAccount* _pMFAccount = pSystematicList->getMFAccount();
      _pMFAccount->getField ( ifds::NonFinConfirm, dstrAcctNonFinConfirm, BF::HOST);
      dstrAcctNonFinConfirm.strip();

      if(idField != ifds::NonFinConfirms && 
         (dstNFConfBnkDetl != I_("N") && dstrAcctNonFinConfirm != I_("N")))
      {
		   setFieldRequired(ifds::NonFinConfirms, idDataGroup, true);
		   setField(ifds::NonFinConfirms, I_(""), idDataGroup, false); //02 = required
      }*/
   }
   if( idField == ifds::Fee )
   {
	   if( _featureSplitComm == COMMISSION_TYPE_ONE )
	   {
		   DString dstrFundCode, dstrClassCode;
		   getField( ifds::FundCode,  dstrFundCode,  idDataGroup, false);
		   getField( ifds::ClassCode, dstrClassCode, idDataGroup, false);

		   SysAllocationList *pSysAllocationList = NULL;
		   getSysAllocationList(pSysAllocationList);

		   BFData matchCriteria;
		   BFObjIter iter(*pSysAllocationList, idDataGroup, true);

		   while (!iter.end())
		   {
			   SysAllocation* pSysAllocation = dynamic_cast<SysAllocation*>(iter.getObject());

			   if (pSysAllocation)
			   {
				   SplitCommissionList *pSplitCommissionList = NULL;

				   pSysAllocation->getSplitCommissionList(pSplitCommissionList, idDataGroup);

				   if (pSplitCommissionList)
				   {
					   DString dstrFee;
						getField(ifds::Fee, dstrFee, idDataGroup, false);
						pSplitCommissionList->setField ( ifds::Rate, 
														 dstrFee, 
														 idDataGroup, 
														 false, 
														 true);
				   }
			   }
			   ++iter;
		   }
	   }
   }
   
   if(idField == ifds::RDRAdvice)
   {
	   DString dstrRDRAdvice;
	   getField(ifds::RDRAdvice,dstrRDRAdvice,idDataGroup);

	   SysAllocationList *pSysAllocationList = NULL;
	   getSysAllocationList(pSysAllocationList);

	   pSysAllocationList->GetDefaultSplitComm ( idDataGroup );
	   BFObjIter iter(*pSysAllocationList, idDataGroup, true);

	   DString dstrFundCode,dstrClassCode;
	   getField(ifds::FundCode,dstrFundCode,idDataGroup);
	   getField(ifds::ClassCode,dstrClassCode,idDataGroup);

	   BFData matchCriteria;
	   matchCriteria.setElementValue(ifds::FundCode, dstrFundCode, true);
	   matchCriteria.setElementValue(ifds::ClassCode, dstrClassCode, true);

	   iter.positionOnNextMatch(matchCriteria, idDataGroup);

	   if (!iter.end())
	   {
		   SysAllocation* pSysAllocation = dynamic_cast<SysAllocation*>(iter.getObject());

		   if (pSysAllocation)
		   {
			   SplitCommissionList *pSplitCommissionList = NULL;

			   pSysAllocation->getSplitCommissionList(pSplitCommissionList, idDataGroup);
			   if( pSplitCommissionList )
			   {
				   if(dstrRDRAdvice == RDR_ADVICE_PROVIDED )
				   {
					   pSplitCommissionList->changeToRDRAdviceProvided(idDataGroup);
				   }
				   pSplitCommissionList->setField(ifds::RDRAdvice, dstrRDRAdvice, idDataGroup, false);
			   }
		   }
	   }
   }
   if ( ifds::SourceOfTrade == idField || ifds::ChannelOfTrade == idField ) 
   {
		DString dstrScreenActivityType,dstrTime,dstrTransType;
		getField(ifds::TransType, dstrTransType, idDataGroup );
		dstrScreenActivityType = dstrTransType == PAC ? PAC : NULL_STRING ;
		setFieldNoValidate(ifds::ScreenActivityType, dstrScreenActivityType, idDataGroup, false, false, true); 
		if( isNew ())   //for ne PAC use the serever time as the time else use the deal time
			getField(ifds::ServerTime, dstrTime, idDataGroup );
		else
			getField(ifds::EventReceiptTime, dstrTime, idDataGroup );
		//ROBS TO DO check the time and set the time factor accordingly
		if( !dstrTime.empty())
		{
		DString strTime (dstrTime), strHour, strMin;
		DString::size_type iPos = strTime.find (I_(":"));
		int ihour;
		if (iPos != std::string::npos)
			strHour = strTime.substr (0,iPos);
		else
			strHour = strTime.substr (0,2);
		ihour = strHour.asInteger ();
		dstrTime = ihour > 11 ? I_("PM") : I_("AM");
		setFieldNoValidate (ifds::TimeFactor, dstrTime, idDataGroup, false, true, true, false);
		setFieldWithDefaultValue(ifds::PSDAdvice, idDataGroup );
		}
  }

   //If any fields are changed, fund/class must be revalidated against soft capped.
   setValidFlag(ifds::FromSoftCapCheck, idDataGroup, false);
   setValidFlag(ifds::ToSoftCapCheck, idDataGroup, false);

   SysAllocationList *pSysAllocationList = NULL;
   AutoTransAllocationList *pAutoTransAllocationList = NULL;
   AutoAcctTransAllocation *pAutoAcctTransAllocation = NULL;

   if (_pAtAcctAllocationList && isFieldUpdated(idField, idDataGroup))
   {
       BFObjIter acctIter(*_pAtAcctAllocationList,idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
       if (!acctIter.end())
       {
           pAutoAcctTransAllocation = dynamic_cast<AutoAcctTransAllocation*>(acctIter.getObject());

           if (pAutoAcctTransAllocation && 
               pAutoAcctTransAllocation->getAtAllocationList(pAutoTransAllocationList) <= WARNING  && 
               pAutoTransAllocationList)
           {
               pAutoTransAllocationList->setAllAllocsFndClsValidFlag(false, idDataGroup);
           }
       }
   }

   if (isFieldUpdated(idField, idDataGroup) && getSysAllocationList(pSysAllocationList) <= WARNING && pSysAllocationList)
   {
       pSysAllocationList->setAllAllocsFndClsValidFlag(false, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

/********************************************************************************************/
bool Systematic::PayTypeIsEFT(const BFDataGroupId& idDataGroup)
{
   DString PayType;
   // for AT we do not have EFT
   if( findTransType( idDataGroup, AUTO_TRFER ) ) return(false);
   getField(ifds::PayType, PayType, idDataGroup);
   PayType.strip();
   return(PayType == EFT_PAY_TYPE);
}

/********************************************************************************************/
SEVERITY Systematic::InitFieldsNotInInquiry(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "InitFieldsNotInInquiry" ) );
   if( !isNew() )
   {
      DString strTemp;

      getField( ifds::InitFactor, strTemp, idDataGroup );
      if( strTemp.empty() )
         setFieldNoValidate( ifds::InitFactor, ZERO, idDataGroup, true, true, false, false );

      getField( ifds::SetAsDefault, strTemp, idDataGroup );
      if( strTemp.empty() )
         setFieldNoValidate( ifds::SetAsDefault, NO, idDataGroup, true, true, false, false  );

      getField( ifds::PaymentAmt, strTemp, idDataGroup );     
      if( strTemp.empty() )
         setFieldNoValidate( ifds::PaymentAmt, ZERO, idDataGroup, true, true, false, false  );

      getField( ifds::Commission, strTemp, idDataGroup );     
      if( strTemp.empty() )
         setFieldNoValidate( ifds::Commission, ZERO, idDataGroup, true, true, false, false  );

      getField( ifds::AdminFeeAmtClan, strTemp, idDataGroup );     
      if( strTemp.empty() )
         setFieldNoValidate( ifds::AdminFeeAmtClan, ZERO, idDataGroup, true, true, false, false  );
   }
   setMonthIndicatorFromMonthFields(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
bool Systematic::isSystematicListDummy(const BFDataGroupId& idDataGroup)
{
	SystematicList* pSystematicList = dynamic_cast <SystematicList*> (getParent());

	BFObjIter iter1( *pSystematicList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

	return(iter1.isDummy());
}
//******************************************************************************
//ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
void Systematic::setAllFieldsValid( const BFDataGroupId &idDataGroup, bool bValid )
{

	for ( unsigned int i = 0 ; i< NUM_FIELDS; i++ )
	{

		BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];

		const BFFieldId &fieldId = fieldInfo.getFieldId();
		setFieldValid( fieldId, idDataGroup, true );

	}
}
//*****************************************************
SEVERITY Systematic::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   /* DString dstrTransType;
    getField(DBR::TransType, dstrTransType, idDataGroup, false);
    dstrTransType.strip().upperCase();
 
   if (dstrTransType == SWP && !isNew() && isUpdatedForDataGroup( idDataGroup, true ) )
   {
     ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );
   }*/


	// IN 299732 - check if Broker/Branch/Rep active as of effectivedate of Systematic (severe error) 
	// IN 353952 - validate only if record is not being deactivated (status = good, stopdate > current business date)
	if ( isNew() || isUpdatedForDataGroup( idDataGroup, true ) ) 
	{
		DString dstrStopDate, dstrCurrBusDate, dstrStatus;
		getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );   	  
		getField(ifds::StopDate, dstrStopDate, idDataGroup, false);
		getField(ifds::StatusCode, dstrStatus, idDataGroup, false);
		if( DSTCommonFunctions::CompareDates( dstrStopDate, dstrCurrBusDate ) == DSTCommonFunctions::SECOND_EARLIER 
			&& dstrStatus == I_( "Y" )   )
		{
			DString dstrDeff;
			getField(ifds::EffectiveDate, dstrDeff, idDataGroup, false);
			_pMFAccount->isBrokerBranchRepActive(dstrDeff, idDataGroup);
		}
	}


   DString dstrTransType, AccountTo;
   getField( ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();

   if ( isNew () ) {
      BFData query124(ifds::DSTC0124_REQ);
      DString mgmtCoIdOut;
      query124.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      query124.setElementValue( ifds::Track, I_("N") );
      query124.setElementValue( ifds::Activity, NULL_STRING );

      BFData *response = new BFData(ifds::DSTC0124_VW);

      if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ACTIVE_BATCH, query124, *response, DSTCRequestor(getSecurity()) ) <= WARNING ) {
         DString dstrBatch, dstrOriBatch;
         response->getElementValue( ifds::rxBatchName, dstrBatch );
         getField ( ifds::BatchName, dstrOriBatch, idDataGroup, false );
         //I'm not sure if I should check for NULL_STRING for inactive batch.
         //Currently on iFast.  Batch cannot be created without a Name/Number.
         if( dstrBatch.strip() == NULL_STRING ) {
            ADDCONDITIONFROMFILE( CND::ERR_NO_ACTIVE_BATCH );
         } else if ( dstrOriBatch != dstrBatch ) {             
            setFieldNoValidate (ifds::BatchName, dstrBatch, idDataGroup, false, true, false, false );            
         }
      }
   }
   // Title Restrictions validation for SWP Change
   // Even Code = 14 (SWP Info Change-modify)
   // for Reason Code 01 to 06 -> issue Warning
   // for Reason Code 07 or 08 -> Ignore, no error message
   // SWP - Add is handled in ValidateTransType
   if ( dstrTransType == SWP && !isNew() && isUpdatedForDataGroup( idDataGroup, true ) )
   {
	   DString dstrTitleRestrict (NO);
	   getWorkSession().getOption( ifds::TitleRestrict, dstrTitleRestrict, idDataGroup, false );

       if( dstrTitleRestrict == YES )
       {
			AccountEntityXref *pAccountEntityXref = NULL;
            if( getAccountEntityXref( pAccountEntityXref, idDataGroup ) <= WARNING &&
				NULL != pAccountEntityXref )
            {
				DString acctNum, dstrEffectiveDate;
                getField(ifds::AccountNum, acctNum, idDataGroup);
                acctNum.strip().stripLeading( '0' );
  				getField( ifds::EffectiveDate,    dstrEffectiveDate,  idDataGroup, false );
                if( acctNum != NULL_STRING )
                       SEVERITY sevRtn = pAccountEntityXref->escrowAccount( acctNum,
					                                                        SWP_CHG, 
																			NULL_STRING, 
																			dstrEffectiveDate, 
																			idDataGroup);

            } // if found AccountEntityXref
        }                  
   }

   // Check for Active Batch
/*   DString dstrBatch;
   getField(ifds::BatchName, dstrBatch, idDataGroup, false);
   if( isNew() && dstrBatch.strip() == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_ACTIVE_BATCH );
   }
*/
   getField( ifds::AccountTo, AccountTo, idDataGroup, false );
   AccountTo.strip().stripLeading('0');

   if (dstrTransType == AUTO_TRFER )
   {
	   int iAcctItem,iFundItem;
	   BFObjIter acctIter(*_pAtAcctAllocationList,idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	   iAcctItem = acctIter.getNumberOfItemsInList();

	   AutoAcctTransAllocation* pAutoAcctTransAllocation = dynamic_cast<AutoAcctTransAllocation*>(acctIter.getObject());
	   AutoTransAllocationList* pAutoTransAllocationList;
	   pAutoAcctTransAllocation->getAtAllocationList(pAutoTransAllocationList);

	   BFObjIter fundIter(*pAutoTransAllocationList,idDataGroup, false,  BFObjIter::ITERTYPE::NON_DELETED );
	   iFundItem =  fundIter.getNumberOfItemsInList();
	   if(iAcctItem<=1 && iFundItem<=1)
	   {
		   if(AccountTo == NULL_STRING)
		   {
			   ADDCONDITIONFROMFILE( CND::ERR_AT_ACCOUNT_NOT_EXIST );
		   }
	   }
	   //IN2844236 - Disable set up bankruptcy fund
	   if(isFieldsDisabledBaseOnRuleType(RULE_TYPE::BANKRUPTCY,idDataGroup))
	   {
			setFieldReadOnly (ifds::Amount, idDataGroup, true );
	   }
	   else
	   {
		   DString dstrAmountType;
		   getField (ifds::AmountType, dstrAmountType, idDataGroup);
		   dstrAmountType.strip().upperCase();
		   if ( DSTCommonFunctions::codeInList ( dstrAmountType, I_("F,T,M,X,Y") ) )
		   {
			   setFieldNoValidate (ifds::Amount, I_("0") , idDataGroup, true, false, true, false);
			   setFieldReadOnly (ifds::Amount, idDataGroup, true );
		   }
		   else
		   {
			   setFieldReadOnly (ifds::Amount, idDataGroup, false );
		   }
	   }

   }
   if(PAC == dstrTransType)
   {
     DString dstrSignatureDate;
     getField(ifds::SignatureDate, dstrSignatureDate, idDataGroup, false);

   	 if(NULL_STRING == dstrSignatureDate)
   		getErrMsg(IFASTERR::SIGNATURE_DATE_REQUIRED, CND::ERR_SIGNATURE_DATE_REQUIRED, CND::WARN_SIGNATURE_DATE_REQUIRED,
				  idDataGroup,	NULL_STRING);
   }
   
   //do from first and if no error then to
   if( WARNING >=  doSIFRegulationSpecificValidations(idDataGroup, FROM_TO::FROM ))
       doSIFRegulationSpecificValidations(idDataGroup, FROM_TO::TO );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// we are in the target item
void Systematic::ModelOffer(Systematic *Model, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0006_VWRepeat_Record);


   BFDataFieldIter dIter( *tmp );

   DString str;
   setObjectAsNew(Model->isNewObject());

   DString dstrPayType;
   Model->getField(ifds::PayType, dstrPayType, idDataGroup, false);
   setField(ifds::PayType, dstrPayType, idDataGroup, false);
   
   for( ;dIter; ++dIter )
   {
      const BFFieldId& idField = dIter().getId();
      Model->getField( idField, str, idDataGroup, false );
      if( idField != ifds::PACSWPId && idField != ifds::PayType)//don't copy PACSWPId; it should be unique after all
         //setField(idField, str, idDataGroup, false); // This cause problem because it traggers doApplyRelatedChange()
			setFieldNoValidate(idField, str, idDataGroup, false, true, false, false );
   };

   delete tmp;

   // to do, need view to send back pre bus day
   getWorkSession().getDateInHostFormat(str, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);
   setField(ifds::EffectiveDate, str, idDataGroup, false);

   getWorkSession().getDateInHostFormat(str, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setField(ifds::StopDate, str, idDataGroup, false);

   //clear 
   //clearUpdatedFlags( idDataGroup );
   //setAllFieldsValid( idDataGroup );
   if( findTransType( idDataGroup, AUTO_TRFER ) )
   {
      BFCBO::setField( ifds::PayType, NULL_STRING, idDataGroup );
   }

   SysAllocationList *pSysAllocationList, *pModelSysAllocationList;
   Model->getSysAllocationList( pModelSysAllocationList );

   if( pModelSysAllocationList )
   {
      getSysAllocationList( pSysAllocationList );
      pSysAllocationList->ModelOffer(pModelSysAllocationList, idDataGroup);
   }

   AutoAcctTransAllocationList *pAtAcctAllocationList, *pModelAtAcctAllocationList;
   Model->getAtAcctAllocationList( pModelAtAcctAllocationList );

   if( pModelAtAcctAllocationList )
   {
      getAtAcctAllocationList( pAtAcctAllocationList );
      pAtAcctAllocationList->setSystematicPtr(this);
      pAtAcctAllocationList->ModelOffer(pModelAtAcctAllocationList, idDataGroup);
   }
}

//******************************************************************************

SEVERITY Systematic::setFundField(const BFFieldId& idField, const DString& dstrValue,
                                  const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundField"));

   DString dstrTransType;
   getField( ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();

   BFFieldId idFund = ifds::NullFieldId;
   BFFieldId idClass = ifds::NullFieldId;

   if( (idField == ifds::FundCode|| idField == ifds::ClassCode) &&
       dstrTransType != AUTO_TRFER )                               //PAC or SWP
   {
      idFund  = ifds::FundCode;
      idClass = ifds::ClassCode; 
   }
   else if( (idField == ifds::FundToCode || idField == ifds::ClassToCode) &&
            dstrTransType == AUTO_TRFER )
   {
      idFund  = ifds::FundToCode;
      idClass = ifds::ClassToCode; 
   }
   if( idFund == ifds::NullFieldId || idClass == ifds::NullFieldId )
   {
      BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
      return(GETCURRENTHIGHESTSEVERITY());
   }

   //remember the original value
   DString dstrOrgFundCode, dstrOrgClassCode;
   getField( idFund,  dstrOrgFundCode,  idDataGroup, false);
   getField( idClass, dstrOrgClassCode, idDataGroup, false);
   dstrOrgFundCode.strip().upperCase();
   dstrOrgClassCode.strip().upperCase();

   //set the field value
   BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);

   if (dstrTransType == AUTO_TRFER)            //don't handle the AT at the moment
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrFundCode, dstrClassCode, dstrAmount;
   getField( idFund,  dstrFundCode,  idDataGroup, false);
   getField( idClass, dstrClassCode, idDataGroup, false);
   getField( ifds::Amount, dstrAmount, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   dstrAmount.strip();

   SysAllocationList *pSysAllocationList = NULL;
   getSysAllocationList(pSysAllocationList);

   BFObjIter iter(*pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   int iAllocNum     = iter.getNumberOfItemsInList();
   BFAbstractCBO *pBFCBO   = NULL;
   if( !iter.end() )
      pBFCBO = iter.getObject();

   if( dstrFundCode.empty() && dstrClassCode.empty() )
   {
      if( pBFCBO && iAllocNum == 1 )
      {
         DString dstrAllocFundCode, dstrAllocClassCode;

         pBFCBO->getField( ifds::FundCode,  dstrAllocFundCode,  idDataGroup, false);
         pBFCBO->getField( ifds::ClassCode, dstrAllocClassCode, idDataGroup, false);
         dstrAllocFundCode.strip().upperCase();
         dstrAllocClassCode.strip().upperCase();
         if( (dstrAllocFundCode != NULL_STRING || dstrAllocClassCode != NULL_STRING) &&
             (dstrAllocFundCode == dstrOrgFundCode && dstrAllocClassCode == dstrOrgClassCode) )
         {
            iter.deleteObject();

            //Force to reload the default allocation list
            setupDefaultAllocationList( idDataGroup);
         }
      }
   }
   else if( !dstrFundCode.empty() && !dstrClassCode.empty() )
   {
      SysAllocation *pSysAllocation = NULL;

      BFObjIter iter2(*pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      DString dstrFundCodeB, dstrClassCodeB, dstrKey;
      while( !iter2.end() )
      {
         iter2.getObject()->getField ( ifds::FundCode, dstrFundCodeB,  idDataGroup, false );
         iter2.getObject()->getField ( ifds::ClassCode, dstrClassCodeB,  idDataGroup, false );
         iter2.getObject()->getField ( ifds::Percentage, dstrKey,  idDataGroup, false );
         if( ( dstrFundCode == dstrFundCodeB ) && ( dstrClassCode == dstrClassCodeB) )
         {
            dstrKey = iter2.getStringKey();
            pSysAllocation = dynamic_cast <SysAllocation*>(iter2.getObject());
            ++iter2;
         }
         else
         {
            iter2.deleteObject();  
         }
      }

      if( pSysAllocation == NULL )
      {
         pSysAllocation = new SysAllocation ( *pSysAllocationList );
         BFData *pDataAlloc = new BFData(ifds::DSTC0007_VWRepeat_Record);      
         getStrKey(dstrKey, pDataAlloc);
         pSysAllocation->init( *pDataAlloc);      
         pSysAllocation->doInitWithDefaultValues ( idDataGroup );
         pSysAllocationList->setObject( pSysAllocation, dstrKey, OBJ_ACTIVITY_ADDED, idDataGroup );
      }

      SEVERITY sevRtn1,sevRtn;
      sevRtn = pSysAllocation->setField(ifds::FundCode,    dstrFundCode,  idDataGroup, false, true);
      sevRtn1 = pSysAllocation->setField(ifds::ClassCode,   dstrClassCode, idDataGroup, false, true);
      pSysAllocation->setField(ifds::Percentage,  I_("100"),     idDataGroup, false, true);
      pSysAllocation->setField(ifds::AllocAmount, dstrAmount,    idDataGroup, false, true); 
      sevRtn = sevRtn > sevRtn1? sevRtn:sevRtn1;
      if( sevRtn >= WARNING )
      {
         const BFFieldId idField[] = {ifds::FundCode,ifds::ClassCode};
         CONDITIONVECTOR* pCondVect;
         for( int i = 0;i < 2; i++ )
         {
            getFieldConditionVector(idField[i],idDataGroup,pCondVect );
            if( pCondVect == NULL )
            {
               pCondVect = new CONDITIONVECTOR;
            }
            else
            {
               CONDITIONVECTOR::iterator iter = pCondVect->begin( );
               while( iter != pCondVect->end( ) )
               {
                  delete *iter;
                  iter = pCondVect->erase( iter );
               }
            }
            int count = CURRENTCONDITIONCOUNT( );
            Condition   *c = NULL;
            for( int j = 0; j < count; j++ )
            {
               c = new Condition( *GETCURRENTCONDITION( j ));
               pCondVect->push_back( c );

            }
            setFieldConditionVector(idField[i],idDataGroup,pCondVect );
            notifyObservers( idField[i], idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
         }   
      }
   }
   if( _featureSplitComm != COMMISSION_TYPE_ZERO )
   {
      DString dstr;
      pSysAllocationList->GetSplitCommFlag( idDataGroup, dstr );
      setFieldNoValidate( ifds::SplitComm, dstr, idDataGroup, false );
      //get the split commsion list
      
      BFData matchCriteria;
      BFObjIter iter(*pSysAllocationList, idDataGroup, true);

      //matchCriteria.setElementValue(ifds::AccountNum, strAccNum, true);
      matchCriteria.setElementValue(ifds::FundCode, dstrFundCode, true);
      matchCriteria.setElementValue(ifds::ClassCode, dstrClassCode, true);
      iter.positionOnNextMatch(matchCriteria, idDataGroup);
      if (!iter.end())
      {
         SysAllocation* pSysAllocation = dynamic_cast<SysAllocation*>(iter.getObject());

         if (pSysAllocation)
         {
            SplitCommissionList *pSplitCommissionList = NULL;

            pSysAllocation->getSplitCommissionList(pSplitCommissionList, idDataGroup);

            if (pSplitCommissionList)
            {
               DString strSplitTotalRate;

               pSplitCommissionList->getSplitTotalRate(strSplitTotalRate, idDataGroup);
			   //setFieldNoValidate(ifds::Fee, strSplitTotalRate, idDataGroup, true, true, true);
			   
			   
			   DString dstrTaxTypeMaxFee = pSplitCommissionList->getTaxTypeMaxFee(idDataGroup);
			   if( !dstrTaxTypeMaxFee.empty() )
			   {
				   BigDecimal bdTotalRate(strSplitTotalRate);
				   BigDecimal bdTaxTypeMaxFee(dstrTaxTypeMaxFee);

				   if( bdTaxTypeMaxFee < bdTotalRate )
				   {
				    	setFieldNoValidate(ifds::Fee, dstrTaxTypeMaxFee, idDataGroup, true, true, true, false);
						pSplitCommissionList->propagateTotalRate(dstrTaxTypeMaxFee,idDataGroup);				   
				   }
				   else
				   {
						setFieldNoValidate(ifds::Fee, strSplitTotalRate, idDataGroup, true, true, true, false);
				   }
			   }
			   else
			   {
				   setFieldNoValidate(ifds::Fee, strSplitTotalRate, idDataGroup, true, true, true, false);
			   }
            }
         }
      }
   }
   else
      setFieldNoValidate( ifds::SplitComm, NO, idDataGroup, false );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void Systematic::setupDefaultAllocationList( const BFDataGroupId& idDataGroup, const DString& dstrAmount, bool bDummyAllocations )
{
   DString dstrTransType, dstrAccountNum;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();


   if( dstrTransType == PAC || dstrTransType == SWP || dstrTransType == SAVING_PLAN )
   {
      SysAllocationList* pSysAllocationList = dynamic_cast<SysAllocationList*>(getObject(I_("SysAllocationList"), idDataGroup));
      //getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      _pMFAccount->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      dstrAccountNum.strip().stripLeading('0');

      DString dstrCurrency;
      getField(ifds::BankAcctCurrency, dstrCurrency, idDataGroup, false);
      dstrCurrency.strip().upperCase();

      if( pSysAllocationList != NULL )
      {
         BFObjIter iter(*pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         int iAllocNum = iter.getNumberOfItemsInList();
         if( iAllocNum > 0 )//delete the old allocation list
         {
            while( !iter.end() && iter.getObject() )
               iter.removeObjectFromMap(true);
         }

         /*if( dstrTransType == PAC )
            dstrTransType = I_("ED");
         else if( dstrTransType == SWP )
            dstrTransType = I_("AW");*/         

         if( dstrTransType == SAVING_PLAN )
            return;
         DString dstrEffectiveDate;
         getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
         pSysAllocationList->initWithDefaultAllocations(idDataGroup, dstrTransType, dstrAccountNum, dstrCurrency, dstrAmount, dstrEffectiveDate, bDummyAllocations);
         _pSysAllocationList = pSysAllocationList;
         BFObjIter iter1(*pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         if( iter1.getNumberOfItemsInList() > 1 )
         {
            // 'S' amount type only applicable to multi-currency and non Canadian clients
            if( dstrTransType == I_("S") && DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA && _dstrmultiCurrency == YES ) //SWP; trans type used to be AW
               setFieldNoValidate( ifds::AmountType, I_("S"), idDataGroup, false, true, true, false );
            else
               setFieldNoValidate( ifds::AmountType, I_("D"), idDataGroup, false, true, true, false );                  
            if ( dstrCurrency == NULL_STRING ) {
               DString dstrFundCode, dstrClassCode;            
               iter1.getObject()->getField ( ifds::FundCode, dstrFundCode, idDataGroup );
               iter1.getObject()->getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
               CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrCurrency);
               setFieldNoValidate ( ifds::BankAcctCurrency, dstrCurrency, idDataGroup, false, true, true, false );                              
            }
         }
		 // Allocated amounts calculated by SysAllocationList::initWithDefaultAllocations() contains invalid amounts.
		 // setAllocListAmount() is called to recalculate allocated amounts.
		 setAllocListAmount(pSysAllocationList, DSTCommonFunctions::convertToDouble(dstrAmount), idDataGroup);
      }
   } /*else if ( dstrTransType == AUTO_TRFER ) {      
      //getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      DString dstrAccountTo;
      getField ( ifds::AccountTo, dstrAccountTo, idDataGroup );
      if ( dstrAccountTo == NULL_STRING )
         return;

      MFAccount* pMFAcct;   
      getWorkSession().getMFAccount( idDataGroup, dstrAccountTo, pMFAcct );
      if ( !pMFAcct->isAMSAccount ( idDataGroup ) )
         return;

      DString dstrPACSWPOverride;
      getWorkSession().getOption( ifds::PACSWPOverride, dstrPACSWPOverride, idDataGroup, false); 
      if ( dstrPACSWPOverride != YES )
         return;    
      
      pMFAcct->getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      dstrAccountNum.strip().stripLeading('0');

      DString dstrCurrency;
      getField(ifds::BankAcctCurrency, dstrCurrency, idDataGroup, false);
      dstrCurrency.strip().upperCase();

      if( _pAtAcctAllocationList != NULL )
      {         

         BFObjIter iter(*_pAtAcctAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         AutoTransAllocationList *pAtAllocationList;
         while( !iter.end() && iter.getObject() )
         {
            BFAbstractCBO *pBFCBO = iter.getObject();
            if( pBFCBO )
            {               
               dynamic_cast<AutoAcctTransAllocation*>(pBFCBO)->getAtAllocationList(pAtAllocationList);

               BFObjIter iter1(*pAtAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
               int iAllocNum = iter1.getNumberOfItemsInList();
               if( iAllocNum > 0 )//delete the old allocation list
               {
                  while( !iter1.end() && iter1.getObject() )
                     iter1.removeObjectFromMap(true);
               }            
            }            
            iter.removeObjectFromMap(true);                       
         }
         
         DString dstrEffectiveDate;
         getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
         _pAtAcctAllocationList->initWithDefaultAllocations(idDataGroup, dstrTransType, dstrAccountNum, dstrCurrency, dstrAmount, dstrEffectiveDate);

         BFObjIter iter1(*pAtAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         if( iter1.getNumberOfItemsInList() > 1 )
         {
            // 'S' amount type only applicable to multi-currency and non Canadian clients
            if( dstrTransType == I_("S") && DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA && _dstrmultiCurrency == YES ) //SWP; trans type used to be AW
               setFieldNoValidate( ifds::AmountType, I_("S"), idDataGroup, false, true, true, false );
            else
               setFieldNoValidate( ifds::AmountType, I_("D"), idDataGroup, false, true, true, false );                  
         }
      }
   }*/
}

//******************************************************************************
SEVERITY Systematic::setAmountField(const BFFieldId& idField, const DString& dstrValue,
                                    const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAmountField"));

   DString dstrTotalAmount(dstrValue);

   getFormattedAmount(idDataGroup, dstrTotalAmount);
   dstrTotalAmount.strip().stripAll(I_CHAR(','));

   double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);

   SEVERITY  sevRtn = BFCBO::setField(idField, dstrTotalAmount, idDataGroup, bFormatted, bSideEffect);
   if( WARNING <= sevRtn )
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();
   if( dstrTransType != AUTO_TRFER )   //PAC or SWP
   {
      setAllocListAmount(_pSysAllocationList, dTotalAmount, idDataGroup);
   }
   else                                                        //AT
   {
      //set the Amount to the Account Level AT Allocation List
      setAllocListAmount(_pAtAcctAllocationList, dTotalAmount, idDataGroup);

      BFObjIter iter(*_pAtAcctAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      while( !iter.end() )
      {
         BFAbstractCBO *pBFCBO = iter.getObject();
         if( pBFCBO )
         {
            DString dstrAmount;
            pBFCBO->getField( ifds::AllocAmount, dstrAmount, idDataGroup, false);

            AutoTransAllocationList *pAtAllocationList;
            dynamic_cast<AutoAcctTransAllocation*>(pBFCBO)->getAtAllocationList(pAtAllocationList);

            if( pAtAllocationList )
            {
               double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
               setAllocListAmount(pAtAllocationList, dAmount, idDataGroup);
            }
         }
         ++iter;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************
// split the total amount to individual fund or account allocation list
//
SEVERITY Systematic::setAllocListAmount(BFCBO* pAllocListBFCBO, double dTotalAmount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAllocListAmount"));

   double dTotalAllocAmount = 0;

   BFObjIter iter(*pAllocListBFCBO, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   double dTotalPercent = 0;
   int iAllocCnt = 0;
   int iAllocNum = iter.getNumberOfItemsInList();
   while( !iter.end() )
   {
      BFCBO *pBFCBO = dynamic_cast< BFCBO* > ( iter.getObject() );
      if( pBFCBO )
      {
         DString dstrPercentage, dstrAmount;
         double dPercentage, dAmount;

         pBFCBO->getField( ifds::Percentage, dstrPercentage, idDataGroup, false);
         dstrPercentage.strip().stripAll(I_CHAR(','));

         dPercentage = DSTCommonFunctions::convertToDouble(dstrPercentage);
         if( dPercentage != 0 )
         {
            iAllocCnt++;
            dTotalPercent += dPercentage;
            char szBuffer[50];
            memset(szBuffer, 0, 50);
            if( iAllocCnt == iAllocNum && dTotalPercent == 100 )
            {
               dAmount = dTotalAmount - dTotalAllocAmount;
               dstrAmount = DStringA(_gcvt(dAmount, 40, szBuffer));
               //dstrAmount = DSTCommonFunctions::doubleToDString( ifds::Amount, dAmount );
               dstrAmount.strip().stripAll(I_CHAR(','));
               getFormattedAmount(idDataGroup, dstrAmount);

               pBFCBO->BFCBO::setField(ifds::AllocAmount, dstrAmount, idDataGroup, false, true);
            }
            else
            {
               dAmount = dTotalAmount * dPercentage / 100; 
               dstrAmount = DStringA(_gcvt(dAmount, 40, szBuffer));
               //dstrAmount = DSTCommonFunctions::doubleToDString( ifds::Amount, dAmount );
               dstrAmount.strip().stripAll(I_CHAR(','));
               getFormattedAmount(idDataGroup, dstrAmount);

               pBFCBO->BFCBO::setField(ifds::AllocAmount, dstrAmount, idDataGroup, false, true);

               dTotalAllocAmount += DSTCommonFunctions::convertToDouble(dstrAmount);
            }
         }
      }
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************

void Systematic::getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue) const
{
   DString dstrCurrency(NULL_STRING);

   DString dstrAmountType;
   getField(ifds::AmountType, dstrAmountType, idDataGroup, false);
   dstrAmountType.strip();

   if( dstrAmountType != I_("U") )
   {
      DString dstrTransType;
      getField(ifds::TransType, dstrTransType, idDataGroup, false);
      dstrTransType.strip().upperCase();
      if( dstrTransType == AUTO_TRFER )   //AT
      {
         DString dstrFundCode, dstrClassCode;
         getField(ifds::FundCode,  dstrFundCode, idDataGroup, false);
         getField(ifds::ClassCode, dstrClassCode,idDataGroup, false);

         if( dstrFundCode.strip() != NULL_STRING && dstrClassCode.strip() != NULL_STRING )
            CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrCurrency);
      }
      else
      {
         getField(ifds::BankAcctCurrency, dstrCurrency, idDataGroup, false);
         dstrCurrency.strip();
      }
      CurrencyClass::getFormattedValue( getWorkSession(), dstrValue, dstrCurrency, dstrAmountType);
   }
   else
   {
      int iUnitsPrecision = 0;

      FundDetail *pFundDetail = NULL;
      DString dstrUnitsPrecision, dstrFundCode, dstrClassCode;

      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      dstrFundCode.strip().upperCase();
      getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
      dstrClassCode.strip().upperCase();
      if( _pFundDetailList != NULL )
      {
         if( (const_cast<Systematic*>(this))->_pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) &&  pFundDetail )
         {
            pFundDetail->getField( ifds::UnitsPrecision, dstrUnitsPrecision, BF::HOST, false  );
            iUnitsPrecision = dstrUnitsPrecision.asInteger(); 

            const BFFieldId& idField = ifds::USDollar;
            DSTCommonFunctions::formattedField( idField, iUnitsPrecision, dstrValue ); 
         }
      }
   }
}

//**********************************************************

void Systematic::getFormattedFee(const BFDataGroupId& idDataGroup, DString &dstrValue) const
{
   DString dstrFlatPercent;
   getField(ifds::FlatPercent, dstrFlatPercent, idDataGroup, false);
   if( dstrFlatPercent.strip() != YES )          //Percent
      return;

   DString dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();

   BFFieldId idFund = ifds::FundToCode;
   BFFieldId idClass = ifds::ClassToCode;
   if( dstrTransType != AUTO_TRFER )   //PAC or SWP
   {
      idFund  = ifds::FundCode;
      idClass = ifds::ClassCode;
   }

   DString dstrFundCode, dstrClassCode;
   getField(idFund,  dstrFundCode, idDataGroup, false);
   getField(idClass, dstrClassCode,idDataGroup, false);

   DString dstrCurrency;
   if( dstrFundCode.strip() != NULL_STRING && dstrClassCode.strip() != NULL_STRING )
      CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrCurrency);

   CurrencyClass::getFormattedValue(getWorkSession(), dstrValue,dstrCurrency);
}
//******************************************************************************
// for AT cross edit for FundTo classTo AccountTo
void Systematic::ValidateFundToClassToAccountTo( const BFDataGroupId& idDataGroup )
{
	   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateFundToClassToAccountTo"));

   DString FundCode,FundToCode,ClassCode,ClassToCode,AccountNum,AccountTo;
   getField( ifds::FundCode, FundCode, idDataGroup, false );
   FundCode.strip().upperCase();
   getField( ifds::ClassCode, ClassCode, idDataGroup, false );
   ClassCode.strip().upperCase();
   getField( ifds::FundToCode, FundToCode, idDataGroup, false );
   FundToCode.strip().upperCase();
   getField( ifds::ClassToCode, ClassToCode, idDataGroup, false );
   ClassToCode.strip().upperCase();
   getField( ifds::AccountNum, AccountNum, idDataGroup, false );
   AccountNum.strip().stripLeading('0');
   getField( ifds::AccountTo, AccountTo, idDataGroup, false );
   AccountTo.strip().stripLeading('0');
   bool bToBlank = false;
   //rules: if one of FundToCode, classToCode is blank and AccountTo = 0, the other should be blank too;
   if( (FundToCode.empty() ) || (ClassToCode.empty() ) ||  AccountTo.empty() )
      bToBlank = true;

   if( bToBlank )
   {
      DString dstrTag;
      CLEARCONDITIONS();
      if( FundToCode.empty() && ( !ClassToCode.empty() ||  !AccountTo.empty() ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_BLANK_FUND );      
      }
      else if( ClassToCode.empty() && ( !FundToCode.empty() ||  (AccountTo != I_("0")  && !AccountTo.empty() ) ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_BLANK_FUND );      
      }
      else if( (AccountTo == I_("0") || AccountTo.empty() ) && ( !FundToCode.empty() ||  !ClassToCode.empty() ) )
      {
         //ADDCONDITIONFROMFILE( CND::ERR_AT_ACCOUNT_NOT_EXIST );      
      }
   }
 	else // else case : FundToCode and ClassToCode are not empty
   {
	   // rules: ClassCode, ClassToCode,FundCode,FundToCode,AccountNum, AccountTo can not be all the same
      if (FundCode == FundToCode && ClassCode == ClassToCode && AccountNum == AccountTo)
      {
		   ADDCONDITIONFROMFILE( CND::ERR_AT_FUNDTO_CLASSTO_ACOUNTTO_SAME_AS_FROM );
      }

      // broker fund logic for ticket 10009829 : check broker fund validation against the ToFund/ToClass using the broker of AccountTO as per E&P's request W.Shiu Oct 13, 2002
       validBrokerFund ( TOFUND, FundToCode, ClassToCode, idDataGroup);
      
      //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
	   // remove ineffective code
      validSalesrepFund ( TOFUND, FundToCode, ClassToCode, idDataGroup);


      //Validate if the fundto/classto combination is valid for the account group and if the fund/class are effective as of the 
      // PAC/SWP/AT set up date as well as checking the Stop Flag at account level, group level and fund/class level
      MFAccount *mfAccount=NULL;

      SEVERITY sevRtn = getWorkSession().getMFAccount( idDataGroup, AccountTo, mfAccount );

      DString dstrEffectiveDate, dstrTransType;
      getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
      dstrEffectiveDate.strip();

      //dstrTransType = EX_FER_IN_CODE;

      if( mfAccount != NULL )
      {
         sevRtn = mfAccount->canTradeFundClass( FundToCode, ClassToCode, EX_FER_IN_CODE, dstrEffectiveDate, idDataGroup );
         sevRtn= stopFlagCheck( FundToCode, ClassToCode, I_( "ATI" ), idDataGroup);
      }

		// ValidateSegFund
	
		getField( ifds::TransType, dstrTransType, idDataGroup, false );
		dstrTransType.strip().upperCase();

		if( dstrTransType == I_("AT") )
		{

			DString strSegClient, strCotClient;
			getWorkSession().getOption(ifds::SegClient, strSegClient, BF::HOST );
			getWorkSession().getOption(ifds::CotClient, strCotClient, BF::HOST );

			if( (strSegClient.strip() == YES && strCotClient.strip() == YES ))
			{
				SeqFundValidation *pSeqFundValidation = NULL;
				if( getSeqFundValidation( pSeqFundValidation, idDataGroup, FundToCode, ClassToCode, AccountTo, dstrEffectiveDate ) 
				<= WARNING && pSeqFundValidation )
				{
					pSeqFundValidation->addSegFundValidationWarnings( idDataGroup );
				}
			}
		}
   }

   if( _dstrTransType == AUTO_TRFER )
   {
      DString dstrAccountNum, dstrAccountTo, dstrEffectiveDate;
      getField (ifds::AccountNum, dstrAccountNum, idDataGroup);  
      dstrAccountNum.strip().stripLeading( '0' );
      getField (ifds::AccountTo, dstrAccountTo, idDataGroup);  
      dstrAccountTo.strip().stripLeading( '0' );
	  getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);  
	  if( dstrAccountNum != dstrAccountTo )
	  {
		 //we probably need to add both accountNum and accountTo to view392, so the back end can check if same accountholder
         validateResidency( dstrAccountTo, idDataGroup );
	  } 
      validateMoneyInDates( dstrAccountTo, dstrEffectiveDate, idDataGroup );      	
   }
}


//**********************************************************************************************

SEVERITY Systematic::validateResidency( const DString &dstrAccountNumber, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateFundToClassToAccountTo"));

   MFAccount* pMFAccount;
   getWorkSession().getMFAccount(idDataGroup, dstrAccountNumber, pMFAccount);

   if(pMFAccount && pMFAccount->isNew())
	   return GETCURRENTHIGHESTSEVERITY();
	   
   DString dstrEffectivedate, dstrDepositType;
   getField( ifds::EffectiveDate, dstrEffectivedate, idDataGroup, false );   
   if ( _dstrTransType == PAC || _dstrTransType == AUTO_TRFER )
   {
      //only applies for good records which have not been stopped
      DString dstrGoodBad, dstrStopDate, currBussDate;
	  getWorkSession ().getOption ( ifds::CurrBusDate, currBussDate, BF::HOST, false);
	  getField( ifds::StatusCode, dstrGoodBad, idDataGroup, false ); 
	  getField( ifds::StopDate, dstrStopDate, idDataGroup, false ); 
	  dstrDepositType = _dstrTransType == PAC ? I_("02") : I_("01");
	  Residency* residency;					
	  if( dstrGoodBad.strip().upperCase() == GOOD &&
          ( dstrStopDate.strip().empty() || DSTCommonFunctions::CompareDates( currBussDate, dstrStopDate ) == DSTCommonFunctions::FIRST_EARLIER ) &&
		  !dstrAccountNumber.empty() &&
		  getWorkSession().getResidency( residency, dstrAccountNumber, dstrEffectivedate, dstrDepositType, idDataGroup ) <= WARNING && residency )
	  {
	     if( !residency->isTaxJurisdictionValid() )
         {
	        getErrMsg ( IFASTERR::NON_RESIDENT_TAX_JURISD_CONTR_NOT_ALLOWED,
	        CND::ERR_CONTRIBUTION_NOT_ALLOWED_FOR_NON_RESIDENT,
			CND::WARN_CONTRIBUTION_NOT_ALLOWED_FOR_NON_RESIDENT,
			idDataGroup,
			NULL_STRING);						
		 }
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//**********************************************************************************************

void Systematic::validateFundClassTransferAllowed(const BFDataGroupId& idDataGroup)
{ 
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClassTransferAllowed"));
   //rules check if transfer is allowed
   DString FundCode,FundToCode,ClassCode,ClassToCode,AccountNum,dstrAccountTo;
   getField(ifds::FundCode,FundCode,idDataGroup,false);
   FundCode.strip().upperCase();
   getField(ifds::ClassCode,ClassCode,idDataGroup,false);
   ClassCode.strip().upperCase();
   getField(ifds::FundToCode,FundToCode,idDataGroup,false);
   FundToCode.strip().upperCase();
   getField(ifds::ClassToCode,ClassToCode,idDataGroup,false);
   ClassToCode.strip().upperCase();

   if( FundCode.empty() || ClassCode.empty() || ClassToCode.empty() || FundToCode.empty() )
   {
      return;
   }
	FundToList fundToList( *this );
	if( fundToList.isTransferAllowed(  FundCode, ClassCode, FundToCode, ClassToCode ) == false )
	{
		DString idiStr;
		addIDITagValue( idiStr, I_("FIELD1"), FundCode );
		addIDITagValue( idiStr, I_("FIELD2"), ClassCode );
		addIDITagValue( idiStr, I_("FIELD3"), FundToCode );
		addIDITagValue( idiStr, I_("FIELD4"), ClassToCode );
		ADDCONDITIONFROMFILEIDI( CND::ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED,idiStr );          
		return;
	}
}

//**********************************************************************************************
void Systematic::ValidateFundToCode(DString& strFundTo, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateFundToCode"));

   if( findTransType( idDataGroup, AUTO_TRFER ) )
   {

      DString strGICAlloc;
      BFData data;
      data.setElementValue( ifds::FundCode, strFundTo, true, false );
/*
    DString dstrKey;
    _pFundMasterList->getStrKey( dstrKey, &data );
    BFObjIter iterFund( *_pFundMasterList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
*/
      if( _pFundMasterList != NULL && !strFundTo.empty() )
      {
         if( _pFundMasterList->IsFundExist( strFundTo, idDataGroup ) == false )
         {
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
         }
         else  //if fund does exists
         {
            DString dstrEffectiveDate;
            getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
            if( _pFundMasterList->IsFundValidAtDate ( strFundTo, dstrEffectiveDate, idDataGroup) == false )
            {
               DString idiStr, FundCodeCopy( strFundTo );
               addIDITagValue( idiStr, I_( "FUNDNAME" ),  FundCodeCopy.strip() );
               ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, idiStr );
            }
            else
            {
               //FundMaster *pFundMaster = NULL;
               //if( _pFundMasterList->getFundMaster (strFundTo, idDataGroup, pFundMaster) )
               //{
               //    pFundMaster->cappedFundRule ( dstrEffectiveDate, idDataGroup );
               //}
				//new error number wnem modify an SMARTs to a capped fund
				if ( isCappedFund ( strFundTo,idDataGroup ) )
				{
					long errorConID (CND::ERR_CAPPEDFUND_STATUSE);
					long warningConID (CND::ERR_CAPPEDFUND_STATUSW);
					DString dstrFund;
					getField ( ifds::FundToCode, dstrFund, idDataGroup );
					DString idiStr(NULL_STRING);
					addIDITagValue( idiStr, I_( "FUND" ), dstrFund );

					getErrMsg( I_("358"), errorConID, warningConID, idDataGroup, idiStr );
				}

				
            }
         } // if fund does exists
      }
   }
}


//************************************************************************************
SEVERITY Systematic::validateAccountTo( const DString& toAcctNum, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccount" ) );


   SEVERITY    sevRtn;  
   if( !findTransType( idDataGroup, AUTO_TRFER ) ) return(GETCURRENTHIGHESTSEVERITY());

   // now it is for AT
   DString TempAcct(toAcctNum);
   TempAcct.strip().stripLeading('0');

   if( !TempAcct.isAllDigits() ) // must be all digits 
   {
      CLEARCONDITIONS();
      ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_NUMBER_NOT_ALL_DIGITS );       
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   //-----------------------------------------
   MFAccount* pMFAcct;
   TempAcct.stripLeading ('0');
   if	((!TempAcct.empty()) && (TempAcct != I_("0")))
   {
      // check account number by enquiry		
      sevRtn = getWorkSession().getMFAccount( idDataGroup, TempAcct, pMFAcct );
      if( sevRtn > WARNING || pMFAcct == NULL )
      {
         CLEARCONDITIONS();
         ADDCONDITIONFROMFILE( CND::ERR_AT_ACCOUNT_NOT_EXIST );
         return(GETCURRENTHIGHESTSEVERITY());  
      }

      //----------------------------------------
      // toAcct is a valid account	no
      DString dstrDate;
      getField(ifds::EffectiveDate,dstrDate,idDataGroup,false);
      if ( pMFAcct->canATIn ( dstrDate, idDataGroup ) ) {
         if( pMFAcct->canTrfExchIn ( dstrDate, idDataGroup ) <= WARNING &&
             pMFAcct->validateMoneyInTFSA(idDataGroup) <= WARNING)
         {
            DString dstrFromAccount;
            getField( ifds::AccountNum, dstrFromAccount, idDataGroup);

            if( TempAcct == dstrFromAccount.strip().stripLeading('0') )
            {
               MFAccount* pMFFromAccount;
               if( getMFAccount ( dstrFromAccount, idDataGroup, pMFFromAccount ) <= WARNING )
               {
                  sevRtn = pMFFromAccount->exchEscrow ( dstrDate, idDataGroup );
               }
            }
         }
      }
      //---------------------------------------------
      //check taxtype between the 2 account
      validateATAccountTaxType( toAcctNum, idDataGroup );
   }
	else
	{
		DString FundToCode, ClassToCode;

		getField( ifds::FundToCode, FundToCode, idDataGroup, false );
		FundToCode.strip().upperCase();
		getField( ifds::ClassToCode, ClassToCode, idDataGroup, false );
		ClassToCode.strip().upperCase();
		if (!FundToCode.empty() || !ClassToCode.empty()) 
      {
			ADDCONDITIONFROMFILE( CND::ERR_AT_ACCOUNT_NOT_EXIST ); 
		}
	}
   return(GETCURRENTHIGHESTSEVERITY());  

} 
//*************************************************************************************

SEVERITY Systematic::validateATAccountTaxType( const DString& ToAcctNum, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateATAccountTaxType" ) );
   SEVERITY sevRtn;
   // Check if transfer from tax type to tax type is valid *****************************/
   DString dstrFromAccount, dstrTradesType, dstrTaxTypeFrom, dstrTaxTypeTo, dstrTaxTypeFrForm, dstrTaxTypeToForm;
   getField( ifds::AccountNum, dstrFromAccount, idDataGroup );

   dstrFromAccount.strip().stripLeading( '0' );

   DString toAccount(ToAcctNum);

   if( dstrFromAccount != toAccount.strip().stripLeading( '0' ) )
   {
      MFAccount *mfAccount=NULL;
      sevRtn = getMFAccount ( toAccount, idDataGroup, mfAccount );

      if ( sevRtn <= WARNING && mfAccount != NULL )
      {
         mfAccount->getField( ifds::TaxType, dstrTaxTypeTo, idDataGroup );         
         mfAccount->getField( ifds::TaxType, dstrTaxTypeToForm, idDataGroup, true );
      }

      TaxTypeRule *pTaxTypeRule = NULL;
      if ( mfAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
      {
         sevRtn = getMFAccount ( dstrFromAccount, idDataGroup, mfAccount );

         if ( sevRtn <= WARNING && mfAccount != NULL )
         {
            mfAccount->getField( ifds::TaxType, dstrTaxTypeFrom, idDataGroup );
            mfAccount->getField( ifds::TaxType, dstrTaxTypeFrForm, idDataGroup,true );
         }

         dstrTaxTypeFrom.strip().upperCase();
         if(!(pTaxTypeRule->validTransfer ( dstrTaxTypeFrom, idDataGroup ) ))
         {
            DString idiStr;
            addIDITagValue( idiStr, I_( "FROMTAX"), dstrTaxTypeFrForm );
            addIDITagValue( idiStr, I_( "TOTAX"), dstrTaxTypeToForm );
            ADDCONDITIONFROMFILEIDI( CND::ERR_TRANSFER_TAX_TYPE, idiStr  );
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();   
} 

//******************************************************************************
bool Systematic::getFundCurrency(DString& dstrCurrency, const BFDataGroupId& idDataGroup)
{
   DString dstrFundCode,dstrClassCode;
   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   if( !dstrFundCode.empty() && !dstrClassCode.empty() )
   {
      FundDetail *pFundDetail = NULL;
      if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) )
      {
         pFundDetail->getField( ifds::Currency, dstrCurrency, BF::HOST, false );
         dstrCurrency.strip();
         return( !dstrCurrency.empty() );
      }
   }
   return(false);   
}

//****************************************************************************
void Systematic::validateAmountTypeCrossEdit(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmountTypeCrossEdit" ) );
   DString dstrAmount,dstrAmtType, dstrGrossOrNet;

   getField(ifds::AmountType,dstrAmtType,idDataGroup,false);
   getField(ifds::Amount,dstrAmount,idDataGroup,false);
   dstrAmtType.strip().upperCase();

   double fAmount = atof(dstrAmount.asA().c_str());

   // if percentage, check if it is between 0 to 100
   if( dstrAmtType == I_("P") )
   {
      if( fAmount < 0.0 )
      {
         CLEARCONDITIONS();
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_NEGATIVE_AMOUNT );   

      }
      else if( fAmount > 100.0 )
      {
         CLEARCONDITIONS();
         DString idiStr;
         addIDITagValue( idiStr, I_("Amount"), I_("100") );
         ADDCONDITIONFROMFILEIDI( CND::ERR_AMOUNT_EXCEED_MAX_LIMIT,idiStr ); 

      }
   }
   
   if( findTransType( idDataGroup, AUTO_TRFER ) )  // the rule does not apply to AT PTS 10031439
   {
	 return;
   }

   getField(ifds::GrossOrNet,dstrGrossOrNet,idDataGroup,false);
   if ( dstrGrossOrNet.strip().upperCase() == NO /*Net*/ && 
         ( dstrAmtType == I_("P") || dstrAmtType == I_("U")))
   {
      ADDCONDITIONFROMFILE( CND::ERR_NET_UNIT_PERCENT_NOT_ALLOW );   
   }

}


//****************************************************************************
/**
  *      Move to the DSTCommonFunction later
  */
double Systematic::getCurrExchangeRate(const DString& dstrFromCurrency, const DString& dstrToCurrency, const DString& dstrDate)
{
   double dExchangeRate = 1;

   if( dstrFromCurrency == dstrToCurrency )
      return(dExchangeRate);

   CurrencyList *pCurrencyList = NULL;
   getMgmtCo().getCurrencyList(pCurrencyList);

   BFData         data;
   data.setElementValue( ifds::Currency, dstrFromCurrency, true, NULL );
   DString      strKey;
   pCurrencyList->getStrKey( strKey, &data );

   BFObjIter iter((*pCurrencyList), BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( iter.positionByKey( strKey ) )
   {
      DString asOfDate = dstrDate;
      dExchangeRate = getWorkSession().getExchRate( dstrToCurrency, asOfDate,  BF::HOST);
   }
   return(dExchangeRate);
}

//***************************************************************************************
SEVERITY  Systematic::doPreSetField( const BFFieldId& idField, DString & value, const BFDataGroupId& idDataGroup, 
                                     bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreSetField" ) )
   if( idField == ifds::PayType )
   {
      if( findTransType( idDataGroup, AUTO_TRFER ) && value.empty() )
      {
         value = I_("AT");
         if( bFormatted )
            formatField( idField, value, idDataGroup );
      }
   }
   else if( idField == ifds::MonthIndicator )
   {
      value.strip().upperCase().padRight(12, 'N');
   }
   else if( idField == ifds::DayOfWeek )
   {
      value.stripLeading('0');
   }

   if (bFormatted && idField != ifds::NonFinConfirms)
   {
       DString dstrTransType, dstrOPCNonFinConfDefPAC;
       getField(ifds::TransType, dstrTransType, idDataGroup);
       getWorkSession().getOption(ifds::OPCNonFinConfDefPAC, dstrOPCNonFinConfDefPAC, idDataGroup, false);
       // If an any existing PAC info is modified, changes NonFinConfirms to REQUIRED.
       if (idField != ifds::NonFinConfirms && dstrTransType == PAC && dstrOPCNonFinConfDefPAC == YES && !isNew())
       {
           setField(ifds::NonFinConfirms, NF_REQUIRED,  idDataGroup, false); 
           setFieldReadOnly(ifds::NonFinConfirms, idDataGroup, false);
       }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//*****************************************************************************
void Systematic::setFundClassCode(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundClassCode" ) )
   DString dstrFundNumber,dstrFundCode(NULL_STRING),dstrCalssCode(NULL_STRING);

   BFFieldId idFundCode = ifds::FundCode;
   BFFieldId idClassCode = ifds::ClassCode;

   if( idField == ifds::ToFundNumber )
   {
      idFundCode = ifds::FundToCode;
      idClassCode = ifds::ClassToCode;
   }

   getField(idField,dstrFundNumber,idDataGroup,false);

   if( dstrFundNumber.strip() != NULL_STRING )
      getWorkSession().GetFundClassCode( dstrFundNumber,dstrFundCode,dstrCalssCode);

   DString oldFundCode,oldClassCode;
   getField(idFundCode,oldFundCode,idDataGroup,false);
   getField(idClassCode,oldClassCode,idDataGroup,false);

   if( oldFundCode != dstrFundCode )
   {
      setFundField(idFundCode, dstrFundCode, idDataGroup, false, true);
      //setFieldNoValidate( lFundCode, dstrFundCode, idDataGroup, false, true, true );
   }
   if( oldClassCode != dstrCalssCode )
   {
      setFundField(idClassCode, dstrCalssCode, idDataGroup, false, true);
      //setFieldNoValidate( lClassCode, dstrCalssCode, idDataGroup, false, true, true  );
   }
}
//*****************************************************************************
void Systematic::setFundNumber(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundNumber" ) )
   DString dstrFundNumber,dstrFundCode,dstrCalssCode;

   BFFieldId idFundCode = ifds::FundToCode;
   BFFieldId idClassCode = ifds::ClassToCode;
   BFFieldId idFundNumber = ifds::ToFundNumber;

   if( idField == ifds::FundCode || idField == ifds::ClassCode )
   {
      idFundCode = ifds::FundCode;
      idClassCode = ifds::ClassCode;
      idFundNumber = ifds::FrFundNumber;
   }

   getField( idFundCode,dstrFundCode,idDataGroup,false);
   getField( idClassCode,dstrCalssCode,idDataGroup,false);
   dstrFundCode.strip().upperCase();
   dstrCalssCode.strip().upperCase();
   getWorkSession().GetFundNumber( dstrFundCode, dstrCalssCode, dstrFundNumber );
   DString oldFundNumber;

   getField(idFundNumber,oldFundNumber,idDataGroup,false);
   if( oldFundNumber.strip() != dstrFundNumber )
      setFieldNoValidate( idFundNumber, dstrFundNumber, idDataGroup, false, false, true);
}

//**************************************************************************
void Systematic::setATAllocation(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setATAllocation" ) );

   DString dstrAcct,dstrFundTo,dstrClassTo, dstrTransType;

   getField(ifds::AccountTo,   dstrAcct,   idDataGroup,false);
   getField(ifds::FundToCode,  dstrFundTo, idDataGroup,false);
   getField(ifds::ClassToCode, dstrClassTo,idDataGroup,false);
   getField(ifds::TransType, dstrTransType ,idDataGroup,false);
   dstrAcct.stripLeading(I_('0')).strip();
   dstrFundTo.strip().upperCase();
   dstrClassTo.strip().upperCase();

   int iAcctItem,iFundItem;
   BFObjIter acctIter(*_pAtAcctAllocationList,idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   iAcctItem = acctIter.getNumberOfItemsInList();
   if( iAcctItem > 0 )
   {
      AutoAcctTransAllocation* pAutoAcctTransAllocation = dynamic_cast<AutoAcctTransAllocation*>(acctIter.getObject());
      AutoTransAllocationList* pAutoTransAllocationList;
      pAutoAcctTransAllocation->getAtAllocationList(pAutoTransAllocationList);

      if( iAcctItem == 1 )
      {

         BFObjIter fundIter(*pAutoTransAllocationList,idDataGroup, false,  BFObjIter::ITERTYPE::NON_DELETED );
         iFundItem =  fundIter.getNumberOfItemsInList();
			AutoTransAllocation* pAutoTrans = dynamic_cast<AutoTransAllocation* >( fundIter.getObject() );

         if( iFundItem == 1 && pAutoTrans && pAutoAcctTransAllocation)
         {
            if( dstrAcct != NULL_STRING )
            {
					pAutoAcctTransAllocation->parentFieldChangeNotify(ifds::AllocAccountNum,idDataGroup,
																			dstrAcct,false );
					pAutoTrans->parentFieldChangeNotify(ifds::AllocAccountNum,idDataGroup,
																			dstrAcct,false );

//               acctIter.getObject()->setField(ifds::AllocAccountNum,dstrAcct,idDataGroup);
 //              fundIter.getObject()->setField(ifds::AllocAccountNum,dstrAcct,idDataGroup, false, true);
            }
            if( dstrFundTo != NULL_STRING )
				{
				
					pAutoTrans->parentFieldChangeNotify(ifds::FundCode,idDataGroup,
																			dstrFundTo,false );
//             fundIter.getObject()->setField(ifds::FundCode,dstrFundTo,idDataGroup, false, true);


				}
            if( dstrClassTo != NULL_STRING )
				{
					pAutoTrans->parentFieldChangeNotify(ifds::ClassCode,idDataGroup,
																			dstrClassTo,false );
//               fundIter.getObject()->setField(ifds::ClassCode,dstrClassTo,idDataGroup, false, true);
				}
            DString dstrAmount(I_("0")), dstrPercent(I_("100"));
            if( !dstrAcct.empty() || !dstrFundTo.empty() || !dstrClassTo.empty() )
            {
               dstrPercent = I_("100");
               getField(ifds::Amount, dstrAmount,idDataGroup,false);
            }
				pAutoTrans->parentFieldChangeNotify(ifds::Percentage,idDataGroup,
																			dstrPercent,false );
				pAutoTrans->parentFieldChangeNotify(ifds::AllocAmount,idDataGroup,
																			dstrAmount,false );
				pAutoAcctTransAllocation->parentFieldChangeNotify(ifds::Percentage,idDataGroup,
																			dstrPercent,false );
			   pAutoAcctTransAllocation->parentFieldChangeNotify(ifds::AllocAmount,idDataGroup,
																			dstrAmount,false );

         //   acctIter.getObject()->setField(ifds::Percentage,  dstrPercent,idDataGroup, false, true);
         //   acctIter.getObject()->setField(ifds::AllocAmount, dstrAmount, idDataGroup, false, true);
         //   fundIter.getObject()->setField(ifds::Percentage,  dstrPercent,idDataGroup, false, true);
         //   fundIter.getObject()->setField(ifds::AllocAmount, dstrAmount, idDataGroup, false, true);
         }
      }

      DString dstrSplitComm (NO);      

      if (_featureSplitComm == I_("1")) //SSB - no split commissions for auto-transfer for everyone else
      {
         pAutoTransAllocationList->GetSplitCommFlag (idDataGroup, dstrSplitComm);
      }
      setFieldNoValidate (ifds::SplitComm, dstrSplitComm, idDataGroup, false);
   }
}


//******************************************************************************
SEVERITY Systematic::validateFundCode( const DString& dstrfundCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );

   if( dstrfundCode == I_( "CASH" ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   if( _pFundMasterList != NULL && !dstrfundCode.empty() )
   {
      if( _pFundMasterList->IsFundExist( dstrfundCode, idDataGroup ) == false )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
      else  //if fund does exists
      {
         DString dstrEffectiveDate, dstrclassCode;
         getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
         //getField( ifds::ClassCode, dstrclassCode, idDataGroup, false );
         if( _pFundMasterList->IsFundValidAtDate ( dstrfundCode, dstrEffectiveDate, idDataGroup) == false )
         {
            DString idiStr, FundCodeCopy( dstrfundCode );
            addIDITagValue( idiStr, I_( "FUNDNAME" ),  FundCodeCopy.strip() );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, idiStr );
         }
         else if( _dstrTransType == PAC || _dstrTransType == SAVING_PLAN )
         {
            cappedFundRule ( dstrfundCode, idDataGroup );
         }

      }
   }
   if ( _dstrTransType != AUTO_TRFER ) // paytype is not applicable to Automatic Transfer
   {
      DString dstrPayType;
      getField ( ifds::PayType, dstrPayType, idDataGroup );
      ValidatePayType ( dstrPayType, idDataGroup, dstrfundCode );
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY Systematic::validateClassCode( const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );

	if( _pFundDetailList != NULL && (!dstrfundCode.empty() || !dstrClassCode.empty()) )
	{
		FundDetail *pFundDetail = NULL;
		if( _pFundDetailList->getFundDetail( dstrfundCode, dstrClassCode, idDataGroup, pFundDetail ) == false )
		{
			ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
		}
		else
		{
			DString dstrEffectiveDate;
			getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );

			//If FundCode is not effective then don't need to validate classcode
			SEVERITY sev = NO_CONDITION;
			sev = validateFundCode( dstrfundCode, idDataGroup );
		 if(sev <= WARNING)
		 {
			 if( _pFundDetailList->IsFundValidAtDate ( dstrfundCode, dstrClassCode, dstrEffectiveDate, idDataGroup) == false )
			 {
				DString idiStr, FundCodeCopy( dstrfundCode ), ClassCodeCopy( dstrClassCode );
				addIDITagValue( idiStr, I_( "FUNDNAME" ),  FundCodeCopy.strip() );
				addIDITagValue( idiStr, I_( "CLASSNAME" ), ClassCodeCopy.strip() );
				ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr );
			 }
		 }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}


//******************************************************************************
SEVERITY Systematic::getMFAccount( const DString& AcctNum, const BFDataGroupId& idDataGroup, MFAccount *&pAcctOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMFAccount" ) );
   pAcctOut = NULL;
   MFAccount                * pMFAccount = NULL;
   SEVERITY sevRtn = SEVERE_ERROR;

   if( !AcctNum.empty() )
   {
      sevRtn = getWorkSession().getMFAccount( idDataGroup, AcctNum, pMFAccount );

      if( sevRtn <= WARNING && pMFAccount != NULL )
         pAcctOut = pMFAccount;
   }

   return(GETCURRENTHIGHESTSEVERITY());  
} 

//******************************************************************************
SEVERITY Systematic::getSegCotClient()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSegCotClient" ) );
   getWorkSession().getOption(ifds::SegClient, m_strSegClient, BF::HOST );
   getWorkSession().getOption(ifds::CotClient, m_strCotClient, BF::HOST );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY Systematic::getSeqFundValidation(SeqFundValidation *&pSeqFundValidation, const BFDataGroupId& idDataGroup,
                                          const DString& fundCode, const DString& classCode, const DString& acctNum,
                                          const DString& effDate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSeqFundValidation" ) );

   //check cbobase to see if we've already built it
   //if it is already built, check if the parameters are changed
   //if not built create and store with base
   //if built but parameter(s) changed, reInit with the new ones
   pSeqFundValidation = NULL;
   DString strTag = I_("SeqFundValidation");
   pSeqFundValidation = dynamic_cast<SeqFundValidation *>( BFCBO::getObject( strTag, idDataGroup ) );

	// Enhancement PET1244 -- pass EventTansType to make view140 call
	DString strTransType, strEventTransType;
   getField(ifds::TransType, strTransType, idDataGroup, false);
	if( strTransType == PAC )
		strEventTransType = I_("06");
	else if ( strTransType == AUTO_TRFER )
		strEventTransType = I_("07");
	else
		strEventTransType = NULL_STRING;


   if( pSeqFundValidation )
   {
      if( pSeqFundValidation->isChanged(fundCode, classCode, acctNum, effDate, strEventTransType) )
         pSeqFundValidation->reInit(fundCode, classCode, acctNum, effDate, strEventTransType, 
		                            NULL_STRING, NULL_STRING, NULL_STRING, strTransType);
   }
   else
   {
      pSeqFundValidation = new SeqFundValidation ( *this );
      if( pSeqFundValidation->init( fundCode, classCode, acctNum, effDate, strEventTransType, 
		  NULL_STRING, NULL_STRING, NULL_STRING, strTransType ) <= WARNING )
         setObject( pSeqFundValidation, strTag, OBJ_ACTIVITY_NONE, idDataGroup );
      else
      {
         delete pSeqFundValidation;
         pSeqFundValidation = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

/********************************************************************************************/
void Systematic::processSplitCommOption( const BFDataGroupId& idDataGroup )
{
   if( isNew() )
   {
      setFieldNoValidate( ifds::FlatPercent, NO , idDataGroup, false, true, false, false  );
   }
   else
   {

		setFieldNoValidate( ifds::FlatPercent, NO, idDataGroup, false, true, false, false  );

        if (!isSWPPortfolioPayoutPlan(idDataGroup))
        {
            setFieldReadOnly( ifds::FlatPercent, BF::HOST, _featureSplitComm != COMMISSION_TYPE_ZERO );
            setFieldReadOnly( ifds::Fee, BF::HOST, _featureSplitComm == COMMISSION_TYPE_TWO );
        }
   }
}

//****************************************************************************** 
SEVERITY Systematic::getSystematicIndexList(const BFDataGroupId& idDataGroup, SysIndexList *& pSysIndexList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSystematicIndexList" ) );

   DString strTransType;
   getField(ifds::TransType, strTransType, idDataGroup, false);
   if( strTransType != PAC && strTransType != SAVING_PLAN )
   {
      pSysIndexList = NULL;
      setObject( pSysIndexList, SYS_INDEX_LIST, OBJ_ACTIVITY_NONE, idDataGroup ); 

      return(NO_CONDITION);
   }

   pSysIndexList = dynamic_cast<SysIndexList*>(getObject( SYS_INDEX_LIST, idDataGroup ));
   if( !pSysIndexList )
   {
      pSysIndexList = new SysIndexList( *this );
      if( pSysIndexList )
      {
         DString dstrTransNum, dstrTransType, dstrAccountNum;
         getField(ifds::TransNum, dstrTransNum, idDataGroup, true);
         getField(ifds::TransType, dstrTransType, idDataGroup, false);
         _pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST );   
         //getField(DBR::AccountNum, dstrAccountNum, idDataGroup, true);
         if( pSysIndexList->init( dstrAccountNum, dstrTransNum, dstrTransType ) >= WARNING )
         {
            delete pSysIndexList;
            pSysIndexList = NULL;
         };
         setObject( pSysIndexList, SYS_INDEX_LIST, OBJ_ACTIVITY_NONE, idDataGroup ); 
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************** 

void Systematic::ValidateInitialAmt(const DString& strInitialAmt, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateInitialAmt" ) );

   DString dstrTransType, dstrAccountNum;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   if( dstrTransType != SAVING_PLAN )  return;

   if( DSTCommonFunctions::convertToDouble( strInitialAmt ) < 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO );
      return;
   }

   DString tmp;
   getField(ifds::VUBPayOption, tmp, idDataGroup, false);

   if( tmp != VUBOPTION_WAIVED && tmp != NULL_STRING )
   {
      DString tmp1;
      double VUBExpectedAmt ;

      if( tmp == INITIAL_VUB )
      {
         getField(ifds::VUBExpectedAmt, tmp1, idDataGroup, false);
         VUBExpectedAmt = DSTCommonFunctions::convertToDouble( tmp1 );
      }
      else
      {
         getVUBExpectedAmt(tmp1, idDataGroup);
         VUBExpectedAmt = DSTCommonFunctions::convertToDouble( tmp1 ); 
         VUBExpectedAmt /= 12;
      }

      if( DSTCommonFunctions::convertToDouble( strInitialAmt ) <= VUBExpectedAmt )
      {
         DString idiStr;
         tmp1 = DSTCommonFunctions::doubleToDString( ifds::VUBExpectedAmt, VUBExpectedAmt );
		 DSTCommonFunctions::DisplayFormat( tmp1, ifds::VUBExpectedAmt );
         addIDITagValue( idiStr, INITIALVUBAMT, tmp1 );

         if( INITIAL_VUB == tmp )
         {
            ADDCONDITIONFROMFILEIDI( CND::ERR_INIT_CONTRIB_MUST_GREATER_THAN_FEE, idiStr );
         }
         else
         {
            ADDCONDITIONFROMFILEIDI( CND::ERR_INIT_CONTRIB_MUST_GREATER_THAN_FEE_12, idiStr );  
         }
      }
   }
}


/********************************************************************************************/
bool Systematic::VUBFeeTypeIsPercentage(const BFDataGroupId& idDataGroup) const
{
   DString strVUBFeeType;
   getField(ifds::VUBFeeType, strVUBFeeType, idDataGroup, false);

   return(strVUBFeeType != VUB_FEE_TYPE_FRACTION);
}

/********************************************************************************************/
void Systematic::getVUBExpectedAmt(DString& strVUBExpectedAmt, const BFDataGroupId& idDataGroup) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getVUBExpectedAmt" ) );

   DString dstrTransType, dstrAccountNum;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   if( dstrTransType != SAVING_PLAN )  return;

   SavingPlanMasterList *pSavingPlanMasterList;
   const_cast<MgmtCo &>(getMgmtCo()).getSavingPlanMasterList( pSavingPlanMasterList );

   DString tmp;
   BFCBO::getField(ifds::PlanCode, tmp, idDataGroup, false);
   BFObjIter bfIter( *pSavingPlanMasterList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   bfIter.positionByKey( tmp );
   BFAbstractCBO *pObj;
   if( !bfIter.end( ) )
   {
      pObj = bfIter.getObject();
      pObj->getField( ifds::VUBFeeType, tmp, idDataGroup, false );

      if( tmp == VUB_FEE_TYPE_FRACTION )
         pObj->getField( ifds::VUBFeeFrac1, tmp, idDataGroup, false );
      else
         pObj->getField( ifds::VUBFeeRate, tmp, idDataGroup, false );

      if( DSTCommonFunctions::convertToDouble( tmp ) == 0 )
      {
         strVUBExpectedAmt = I_("0");
         const_cast< Systematic*>(this)->setFieldNoValidate( ifds::VUBFee, I_("0"), idDataGroup, false, true, true, false );
         const_cast< Systematic*>(this)->setFieldReadOnly( ifds::VUBExpectedAmt, idDataGroup, true );
      }
      else
      {
         double VUBExpectedAmt =  getContribution( idDataGroup );

         if( VUBFeeTypeIsPercentage(idDataGroup) )
         {
            BFCBO::getField(ifds::VUBFeeRate, tmp, idDataGroup, false);

            VUBExpectedAmt *= DSTCommonFunctions::convertToDouble( tmp );
            VUBExpectedAmt /= 100;
         }
         else
         {
            BFCBO::getField(ifds::VUBFeeFrac1, tmp, idDataGroup, false);
            VUBExpectedAmt *= DSTCommonFunctions::convertToDouble( tmp );

            BFCBO::getField(ifds::VUBFeeFrac2, tmp, idDataGroup, false);

            double VUBFeeFrac2 = DSTCommonFunctions::convertToDouble( tmp );

            if( !VUBFeeFrac2 )
            {
               ADDCONDITIONFROMFILE( CND::ERR_DENOMINATOR_IS_ZERO );   
               return;
            }
            VUBExpectedAmt /= VUBFeeFrac2;
         }

         strVUBExpectedAmt = DSTCommonFunctions::doubleToDString( ifds::VUBExpectedAmt, VUBExpectedAmt );
      }
   }
}

/********************************************************************************************/
void Systematic::getFraction(DString& strFraction, DString& strNumerator, DString& strDenominator) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFraction" ) );

   if( strFraction.empty() )
   {
      strFraction = strNumerator + I_("/") + strDenominator;
   }
   else
   {
      if( isValidFraction( strFraction ) )
      {
         int nPos = strFraction.find('/');

         strNumerator = strFraction.left( nPos );
         strDenominator = strFraction.right( strFraction.length() - nPos -1 );
      }
      else
      {
         strNumerator = I_("0");
         strDenominator = I_("1");
         ADDCONDITIONFROMFILE( CND::ERR_WRONG_FRACTION_FORMAT );   
      }
   }
}

/********************************************************************************************/
void Systematic::setVUBFee(const DString& strVUBFee, const BFDataGroupId& idDataGroup)
{
   DString dstrTransType, dstrAccountNum;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   if( dstrTransType != SAVING_PLAN )  return;

   if( VUBFeeTypeIsPercentage(idDataGroup) )
   {
      BFCBO::setField( ifds::VUBFeeRate, strVUBFee, idDataGroup, true );
   }
   else
   {
      DString strNumerator, strDenominator, strFraction = strVUBFee;
      getFraction( strFraction, strNumerator, strDenominator );
      BFCBO::setField( ifds::VUBFeeFrac1, strNumerator, idDataGroup, true );
      BFCBO::setField( ifds::VUBFeeFrac2, strDenominator, idDataGroup, true );
   }
}

/********************************************************************************************/
void Systematic::getVUBFee(DString& strVUBFee, const BFDataGroupId& idDataGroup) const 
{
   DString dstrTransType, dstrAccountNum;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   if( dstrTransType != SAVING_PLAN )  return;

   if( !VUBFeeTypeIsPercentage(idDataGroup) )
   {
      DString strNumerator, strDenominator;

      strVUBFee = NULL_STRING;
      BFCBO::getField(ifds::VUBFeeFrac1, strNumerator, idDataGroup, false);
      BFCBO::getField(ifds::VUBFeeFrac2, strDenominator, idDataGroup, false);
      getFraction(strVUBFee, strNumerator, strDenominator);
   }
   else
      BFCBO::getField(ifds::VUBFeeRate, strVUBFee, idDataGroup, false);
}

/********************************************************************************************/
double Systematic::getContribution(const BFDataGroupId& idDataGroup) const
{
   double contribution = 0;
   DString tmp;
   BFCBO::getField(ifds::Frequency, tmp, idDataGroup, false);

   long frequency = convertToULong( tmp );

   int factor = 1;

   switch( frequency )
   {
      case 0:
         factor = 365;
         break;

      case 1:
         factor = 54;
         break;

      case 2:
         factor = 27;
         break;

      case 3:
         factor = 12;
         break;

      case 4:
         factor = 24;
         break;

      case 5:
         factor = 4;
         break;

      case 6:
         factor = 2;
         break;

      case 7:
         factor = 1;
         break;

      case 8:
         factor = 12; // others means monthly
         break;
   }

   BFCBO::getField(ifds::Amount, tmp, idDataGroup, false);
   return(contribution = factor*DSTCommonFunctions::convertToDouble( tmp ));
}

/********************************************************************************************/
bool Systematic::isValidFraction(const DString& strIn) const
{
   DString tmp( strIn );

   int len = tmp.stripAll().length();

   return( len > 2 )  // enough char
   && ( len - tmp.find('/') > 1 ) // has number after '/'
   && ( len - 1 == tmp.stripAll('/').length() ) // do not have more than one '/'
   && ( tmp.isAllDigits() ); // contains only digit char
}

/********************************************************************************************/
void Systematic::parsingCombinedField(const DString& dstrValueIn, 
                                      DString& dstrField1, DString& dstrField2, 
                                      const DString& dstrSep) const
{
   DString::size_type findPos;
   findPos = dstrValueIn.find(dstrSep, 0);
   if( findPos == DString::npos )
   {
      dstrField1 = dstrValueIn;
      dstrField2 = NULL_STRING;
   }
   else
   {
      dstrField1 = dstrValueIn.substr(0, findPos);
      dstrField2 = dstrValueIn.substr(findPos + 1);
   }
}

//****************************************************************************** 

void Systematic::setFieldStatus( const BFDataGroupId& idDataGroup, bool isSavingPlan )
{
   if( isSavingPlan )
   {
      setFieldNoValidate( ifds::Frequency, FREQ_MONTHLY, idDataGroup, true, true, false, false );
      setFieldNoValidate( ifds::AmountType, AMOUNT_TYPE, idDataGroup, true, true, false, false );
      setFieldReadOnly( ifds::Frequency, idDataGroup, true );
      setFieldReadOnly( ifds::AmountType, idDataGroup, true );
//CP20030319      setFieldStateFlags( ifds::PlanCode, idDataGroup,BFCBO::STATE_FLAGS::REQUIRED  );
   setFieldRequired( ifds::PlanCode, idDataGroup, true );
//CP20030319      setFieldStateFlags( ifds::VUBPayOption, idDataGroup,BFCBO::STATE_FLAGS::REQUIRED  );
   setFieldRequired( ifds::VUBPayOption, idDataGroup, true );
      setFieldReadOnly( ifds::PlanCode, idDataGroup, !isNew() );
      setFieldReadOnly( ifds::VUBCollectedAmt, idDataGroup, true );
      setFieldReadOnly( ifds::VUBFeeType, idDataGroup, true );
      setFieldReadOnly( ifds::VUBFee, idDataGroup, true );
   }

   if (!isSWPPortfolioPayoutPlan(idDataGroup))
   {
       setFieldReadOnly( ifds::MonthIndicator, idDataGroup, isSavingPlan );
       setFieldReadOnly( ifds::AmountType, idDataGroup, isSavingPlan );
       setFieldReadOnly( ifds::Frequency, idDataGroup, isSavingPlan );
   }

   disableFieldsBaseOnRuleType( RULE_TYPE::BANKRUPTCY, idDataGroup);
}

//****************************************************************************** 
bool Systematic::findTransType(const BFDataGroupId& idDataGroup, const DString& transType)
{
   DString strTransType;
   getField(ifds::TransType,strTransType,idDataGroup,false);
   strTransType.strip().upperCase();
   return(strTransType == transType);
}

//****************************************************************************** 
SEVERITY Systematic::setMonths(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setMonths" ) );
	DString strMonthIndicator, strOldFreq, val, strTransType;
	// set month to perform PAC or SWP
	getField(ifds::Frequency, strOldFreq, idDataGroup, false);
	getField(ifds::MonthIndicator, strMonthIndicator, idDataGroup, false);
	strMonthIndicator.strip().upperCase();
	assert(strMonthIndicator.length() == 12);
	const BFFieldId idMonth[] = {ifds::January, ifds::February, ifds::March, ifds::April,
		ifds::May, ifds::June, ifds::July, ifds::August,
		ifds::September, ifds::October, ifds::November,ifds::December};
	for( int i=0; i<12;i++ )
	{
		val = strMonthIndicator.substr(i, 1);
		setField(idMonth[i], val, idDataGroup, false);
	}
	// set Frequency base on Monthindicator
	if( strOldFreq != FREQ_DAILY && strOldFreq != FREQ_WEEKLY && strOldFreq != FREQ_BIWEEKLY )
	{
		getField(ifds::TransType,strTransType,idDataGroup,false);
		strTransType.strip().upperCase();

      if( getNoOfYes(strMonthIndicator) == 12 )
      {
         if( strOldFreq != FREQ_SEMIMONTHLY )
            setFieldNoValidate(ifds::Frequency, FREQ_MONTHLY, idDataGroup, false, true, true, false);
      }
      else if( strTransType == AUTO_TRFER )//only Monthly or other allowed for AT
      {
         return(GETCURRENTHIGHESTSEVERITY());      
         //setFieldNoValidate(DBR::Frequency, FREQ_OTHER, idDataGroup, false, true, true, NULL, false);
      }
      else // not monthly and not AT
      {
         if( isAnnualy(strMonthIndicator) )
            setFieldNoValidate(ifds::Frequency, FREQ_ANNUALLY, idDataGroup, false, true, true, false);
         else if( isQuarterly(strMonthIndicator) )
            setFieldNoValidate(ifds::Frequency, FREQ_QUARTERLY, idDataGroup, false, true, true, false);
         else
            setFieldNoValidate(ifds::Frequency, FREQ_OTHER, idDataGroup, false, true, true, false);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************** 
int Systematic::getNoOfYes(const DString& strMonthIndicator)
{
   DString val;
   int nNoOfYes = 0;
   for( int i=0; i<12;i++ )
   {
      val = strMonthIndicator.substr(i, 1);
      if( val == YES )
         nNoOfYes++;
   }
   return(nNoOfYes);
}
//****************************************************************************** 

bool Systematic::isAnnualy(const DString& strMonthIndicator)
{
   bool bRetVal = false;
   if( getNoOfYes(strMonthIndicator) == 1 )
   {
      int iPos;
      iPos = strMonthIndicator.find(I_("Y"));

      DString strTemp, strTemp1;
      strTemp = strMonthIndicator.substr(iPos, strMonthIndicator.length()-iPos);
      strTemp1 = strMonthIndicator.substr(0, iPos);
      strTemp += strTemp1;

      iPos = strTemp.find(I_("NNNNNNNNNNN"));

      if( iPos != DString::npos )
         bRetVal = true;
   }
   return(bRetVal);
}

//****************************************************************************** 

bool Systematic::isSemiAnnualy(const DString& strMonthIndicator)
{
   bool bRetVal = false;
   if( getNoOfYes(strMonthIndicator) == 2 )
   {
      int iPos;
      iPos = strMonthIndicator.find(I_("Y"));

      DString strTemp, strTemp1;
      strTemp = strMonthIndicator.substr(iPos, strMonthIndicator.length()-iPos);
      strTemp1 = strMonthIndicator.substr(0, iPos);
      strTemp += strTemp1;

      while( true )
      {
         iPos = strTemp.find( I_( "Y" ) );
         if( iPos == DString::npos ) break;
         strTemp.replace( iPos, 1, BLANKSTRING );
      }

      if( strTemp.words() == 2 )
      {
         for( int i=0; i<2; i++ )
         {
            if( strTemp.word(i) != I_("NNNNN") )
               return(false);
         }
         bRetVal = true;
      }
   }
   return(bRetVal);
}
//****************************************************************************** 

bool Systematic::isQuarterly(const DString& strMonthIndicator)
{
   bool bRetVal = false;
   if( getNoOfYes(strMonthIndicator) == 4 )
   {
      int iPos;
      iPos = strMonthIndicator.find(I_("Y"));

      DString strTemp, strTemp1;
      strTemp = strMonthIndicator.substr(iPos, strMonthIndicator.length()-iPos);
      strTemp1 = strMonthIndicator.substr(0, iPos);
      strTemp += strTemp1;

      while( true )
      {
         iPos = strTemp.find( I_( "Y" ) );
         if( iPos == DString::npos ) break;
         strTemp.replace( iPos, 1, BLANKSTRING );
      }

      if( strTemp.words() == 4 )
      {
         for( int i=0; i<4; i++ )
         {
            if( strTemp.word(i) != I_("NN") )
               return(false);
         }
         bRetVal = true;
      }
   }
   return(bRetVal);
}
//****************************************************************************** 

SEVERITY Systematic::setMonthIndicatorFromMonthFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setMonthIndicatorFromMonthFields" ) );
   const BFFieldId idMonth[] = {ifds::January, ifds::February, ifds::March, ifds::April,
      ifds::May, ifds::June, ifds::July, ifds::August,
      ifds::September, ifds::October, ifds::November,ifds::December};
   DString dstrTemp;
   DString strMonthIndicator(NULL_STRING);
   for( int iMonth = 0; iMonth < 12; iMonth++ )
   {
      getField( idMonth[iMonth], dstrTemp, idDataGroup, false);
      strMonthIndicator += dstrTemp.substr(0, 1);
   }
   strMonthIndicator.upperCase();
   setFieldNoValidate(ifds::MonthIndicator, strMonthIndicator, idDataGroup, false, true, false, false);

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************** 
SEVERITY Systematic::setDefaultMonthlyIndicator(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultMonthlyIndicator" ) );
   DString strFrequency, strEffectiveDate, strMonthIndicator( MONTHLY ), strCurrMonth;
   int iCurrMonth = 1;
   getField(ifds::Frequency, strFrequency, idDataGroup, false);
   getField(ifds::EffectiveDate, strEffectiveDate, idDataGroup, false);

   if( !strEffectiveDate.strip().empty() )
   {
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );

      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                             dstrConfiguration,
                                             dstrKey );

      int month_pos = mask.find( I_( "MM" ) );
      if( month_pos !=  DString::npos )
         strCurrMonth = strEffectiveDate.substr(month_pos, month_pos+2);
      iCurrMonth = strCurrMonth.asInteger();
   }

   assert(iCurrMonth > 0);
   assert(iCurrMonth <= 12);

   --iCurrMonth;

   if( strFrequency == FREQ_QUARTERLY )
   {
      strMonthIndicator = &(QUALTERLY[ 3 - iCurrMonth % 3 ]);
   }
//	else if (strFrequency == FREQ_SEMIANNUALLY)
//	{
//		strMonthIndicator = &(SEMI_ANNUALY[ 6 - iCurrMonth % 6 ]);
//	}
   else if( strFrequency == FREQ_ANNUALLY )
   {
      strMonthIndicator = &(ANNUALY[ 12 - iCurrMonth % 12 ]);
   }

   if( strFrequency != FREQ_OTHER )
   {
      strMonthIndicator.assign( strMonthIndicator, 0, 12);    
      setFieldNoValidate(ifds::MonthIndicator, strMonthIndicator, idDataGroup, false, true, true, true);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************** 

void Systematic::doReset( const BFDataGroupId& idDataGroup )
{   
	if ( isUpdatedForDataGroup( idDataGroup, true ) )
	{
		DString dstrFundCode, dstrClassCode;
		getField(ifds::FundCode, dstrFundCode, idDataGroup , false);
		getField(ifds::ClassCode, dstrClassCode, idDataGroup , false);
		if( dstrFundCode.strip() != NULL_STRING && dstrClassCode.strip() != NULL_STRING )
			setFundField(ifds::FundCode, dstrFundCode, idDataGroup, false, true);
		if( isNew() )
			setupDefaultAllocationList( idDataGroup );

		setFrequencySubstitution(idDataGroup);
	}
}

//****************************************************************************** 

void Systematic::lockFrequency ( const BFDataGroupId& idDataGroup, bool bLock ) 
{
   setFieldReadOnly( ifds::Frequency,        idDataGroup, bLock );      
   setFieldReadOnly( ifds::MonthIndicator, idDataGroup, bLock );
   setValidFlag ( ifds::Frequency, idDataGroup, false );
   setValidFlag ( ifds::MonthIndicator, idDataGroup, false );
}

//******************************************************************************
void Systematic::setFrequencySubstitution(const BFDataGroupId& idDataGroup)
{
   DString dstrTransType;
   getField( ifds::TransType, dstrTransType, idDataGroup, false);

   if( dstrTransType.strip().upperCase() == AUTO_TRFER )
      setFieldSubstituteValues( ifds::Frequency, idDataGroup, ifds::AtFrequency );
   else
      setFieldSubstituteValues( ifds::Frequency, idDataGroup, ifds::PACSWPFrequency ); 
}

//******************************************************************************
void Systematic::setFieldsToReadonlyWhenForBadRecord(const BFDataGroupId& idDataGroup)
{
   DString dstrStatusCode, dstrModPerm;
   getField( ifds::StatusCode, dstrStatusCode, idDataGroup, false);
   getField( ifds::ModPerm, dstrModPerm, idDataGroup, false);

   dstrStatusCode.strip().upperCase();
   dstrModPerm.strip().upperCase();

   if( dstrStatusCode == NO || dstrModPerm == NO )
   {
      setFieldReadOnly( ifds::StatusCode, idDataGroup, true );      
      setFieldReadOnly( ifds::BankAcctCurrency, idDataGroup, true );      
      setFieldReadOnly( ifds::GrossOrNet, idDataGroup, true );      
      setFieldReadOnly( ifds::Frequency, idDataGroup, true );      
      setFieldReadOnly( ifds::FundCode, idDataGroup, true );      
      setFieldReadOnly( ifds::ClassCode, idDataGroup, true );      
      setFieldReadOnly( ifds::EndOfMonth, idDataGroup, true );      
      setFieldReadOnly( ifds::MonthIndicator, idDataGroup, true ); 
      setFieldReadOnly( ifds::FundToCode, idDataGroup, true ); 
      setFieldReadOnly( ifds::ClassToCode, idDataGroup, true ); 
      setFieldReadOnly( ifds::AccountTo, idDataGroup, true ); 
      setFieldReadOnly( ifds::Amount, idDataGroup, true ); 
      setFieldReadOnly( ifds::AmountType, idDataGroup, true ); 
      setFieldReadOnly( ifds::GrossOrNet, idDataGroup, true ); 
      setFieldReadOnly( ifds::FlatPercent, idDataGroup, true ); 
      setFieldReadOnly( ifds::EffectiveDate, idDataGroup, true ); 
      setFieldReadOnly( ifds::StopDate, idDataGroup, true ); 

      setFieldReadOnly( ifds::SrcOfFund, idDataGroup, true );      
      setFieldReadOnly( ifds::SourceOfBankAcct, idDataGroup, true );      
      setFieldReadOnly( ifds::Fee, idDataGroup, true );      
      setFieldReadOnly( ifds::ExchInFee, idDataGroup, true );      
      setFieldReadOnly( ifds::ExchInFlatPercent, idDataGroup, true ); 

      setFieldReadOnly( ifds::AdminFeeAmt, idDataGroup, true );      
      setFieldReadOnly( ifds::FlatPercent, idDataGroup, true );      
      setFieldReadOnly( ifds::BELFee, idDataGroup, true );      
      setFieldReadOnly( ifds::AnnualMaint, idDataGroup, true );      
      setFieldReadOnly( ifds::InitialAmt, idDataGroup, true ); 

      setFieldReadOnly( ifds::VUBExpectedAmt, idDataGroup, true ); 
      setFieldReadOnly( ifds::VUBCollectedAmt, idDataGroup, true ); 
      setFieldReadOnly( ifds::VUBFee, idDataGroup, true );      
      setFieldReadOnly( ifds::VUBPayOption, idDataGroup, true );      

      DString dstrIndexExist;
      getField( ifds::IndexExist, dstrIndexExist, idDataGroup, false);   
      if( dstrIndexExist == YES )
      {
         SysIndexList *pSysIndexList;
         if( getSystematicIndexList ( idDataGroup, pSysIndexList ) <= WARNING )
            pSysIndexList->markReadOnly ( idDataGroup );
      }
   }
}
//******************************************************************************

SEVERITY Systematic::validateBELFee (  const DString& dstrBELFee, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBELFee" ) );

   DString dstrBackEndLoadFee ( dstrBELFee );
   dstrBackEndLoadFee.strip();

   if( dstrBackEndLoadFee == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Systematic::validateExchInFee ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateExchInFee" ) );

   DString dstrExchInFee;
   getField( ifds::ExchInFee, dstrExchInFee, idDataGroup );

   if( !isDecimal( dstrExchInFee ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_FEE_MUST_BE_NUMERIC );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   double dec_fee=DSTCommonFunctions::convertToDouble ( dstrExchInFee );

   if( dec_fee < 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NEGATIVE_FEE_NOT_ALLOW );
   }

   DString dstrFlatPercent;
   getField( ifds::ExchInFlatPercent, dstrFlatPercent, idDataGroup ); 

   if( dstrFlatPercent.strip() == NO && dec_fee > 100 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_FEE_LESS_OR_EQUAL_100 );
   }

   DString toFund, toClass, strMaxFee, strMinFee;

   getField( ifds::FundToCode, toFund, idDataGroup );   
   getField( ifds::ClassToCode, toClass, idDataGroup );
   toFund.strip().upperCase();
   toClass.strip().upperCase();

   if( !_pFundDetailList )
   {
      getMgmtCo().getFundDetailList( _pFundDetailList );
   }

   FundDetail *pFundDetail = NULL;
   if( _pFundDetailList->getFundDetail( toFund, toClass, idDataGroup, pFundDetail ) &&  pFundDetail )
   {
      pFundDetail->getFeeInfoInquiryField( ifds::ExchInFeeMax, strMaxFee, idDataGroup, false ); 
      pFundDetail->getFeeInfoInquiryField( ifds::ExchInFeeMin, strMinFee, idDataGroup, false ); 
   }

   double dec_max_fee = DSTCommonFunctions::convertToDouble ( strMaxFee );
   double dec_min_fee = DSTCommonFunctions::convertToDouble ( strMinFee );

   if( dec_fee > dec_max_fee )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EXCH_IN_FEE_OVER_MAXIMUM );
   }
   if( dec_fee < dec_min_fee )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EXCH_IN_FEE_UNDER_MINIMUM );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************
SEVERITY Systematic::validateExchOutFee (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateExchOutFee" ) );
   TradingFeeRules* exchangeOutRules = NULL;

   if (TradingFeeRules::getExchangeOutFeeRules(*this, 
      exchangeOutRules, ifds::ExchOutFee, ifds::ExchOutFlatPrcnt,
      ifds::FundCode, ifds::ClassCode,
      ifds::EffectiveDate, ifds::AccountNum, 
      ifds::BrokerCode, ifds::BranchCode,
      ifds::SlsrepCode, idDataGroup) <= WARNING)
   {
      exchangeOutRules->validateTradingFee(idDataGroup);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void Systematic::setAmtTypeSubList ( const BFDataGroupId& idDataGroup )
{
   if( _dstrTransType == AUTO_TRFER )
      setFieldSubstituteValues( ifds::AmountType, idDataGroup, ifds::AmountTypeAT ); // P, U, D, F, T, M, X, Y
   else if( _dstrmultiCurrency == YES && _dstrTransType == SWP )
   {
       DString dstrAmtTypeOvrd;
       getField(ifds::AmtTypeOvrd, dstrAmtTypeOvrd, idDataGroup);

       if (dstrAmtTypeOvrd == AMT_TYPE::CUSTOM)
          setFieldSubstituteValues(ifds::AmountType, idDataGroup, ifds::AmountTypeSettleCurrCustomPayout);
      else if (dstrAmtTypeOvrd == AMT_TYPE::PORTFOLIO)
          setFieldSubstituteValues(ifds::AmountType, idDataGroup, ifds::AmountTypeSettleCurrPortfolioPayout);
      else
          setFieldSubstituteValues( ifds::AmountType, idDataGroup, ifds::AmountTypeSettleCurr ); // P, U, D, S
   }
   else if( _dstrmultiCurrency == NO && _dstrTransType == SWP )
   {
       DString dstrAmtTypeOvrd;
       getField(ifds::AmtTypeOvrd, dstrAmtTypeOvrd, idDataGroup);

       if (dstrAmtTypeOvrd == AMT_TYPE::CUSTOM)
           setFieldSubstituteValues(ifds::AmountType, idDataGroup, ifds::SWPAmountTypeAllocCustomPayout);
       else if (dstrAmtTypeOvrd == AMT_TYPE::PORTFOLIO)
           setFieldSubstituteValues(ifds::AmountType, idDataGroup, ifds::SWPAmountTypeAllocPortfolioPayout);
       else
           setFieldSubstituteValues( ifds::AmountType, idDataGroup, ifds::SWPAmountType ); // P, U, D
   }
   else
   {
      BFProperties * pBFProperties = getFieldProperties( ifds::AmountType, idDataGroup );
      pBFProperties->setSubstituteValues(NULL); // clear so that the dropdown will use allSubst
 
      DString dstrPACAmountType = removeItemFromAllSubtList (ifds::AmountTypeSystematic , I_("U"), idDataGroup);
      setFieldAllSubstituteValues( ifds::AmountType, idDataGroup, dstrPACAmountType); // A
       
   }
}
//*******************************************************************************
void  Systematic::setDefaultAcquisitionFee( const BFDataGroupId& idDataGroup )
{
   if( _dstrTransType == SWP || _dstrFeeDisableFlag == YES || _featureSplitComm != COMMISSION_TYPE_ZERO )
      return;
/*
  // no default fee assignment if not auto transfer and commission type = 2
  if ( _dstrTransType == AUTO_TRFER && _featureSplitComm != COMMISSION_TYPE_TWO )
    return;
*/
   DString strFundCode,strClassCode,strAmount;

   getField(ifds::Amount,strAmount,idDataGroup);
   strAmount.strip().stripLeading('0');

   if( _dstrTransType == AUTO_TRFER )
   {
      getField(ifds::FundToCode,strFundCode,idDataGroup);
      getField(ifds::ClassToCode,strClassCode,idDataGroup);
   }
   else
   {
      getField(ifds::FundCode,strFundCode,idDataGroup);
      getField(ifds::ClassCode,strClassCode,idDataGroup);
   }


   if( strFundCode == NULL_STRING || strClassCode == NULL_STRING || strAmount == NULL_STRING )
   {
      // clear fee
      DString strFieldValue ( I_( "0" ));
      getFormattedFee(idDataGroup, strFieldValue);
      setFieldNoValidate(ifds::Fee, strFieldValue, idDataGroup, true, true, true);
      return;
   }

   DString dstrAcqFee;
   getWorkSession().getOption( ifds::AcqFeeDefault, dstrAcqFee, idDataGroup, false );
   if( YES == dstrAcqFee.strip() )
   {
      bool bSetAcqFee = false;
      if( ( _dstrTransType == PAC || _dstrTransType == SAVING_PLAN ) ||
          ( _dstrTransType == AUTO_TRFER && _featureSplitComm == COMMISSION_TYPE_TWO) )
      {
         bSetAcqFee = true;
      }
      else if( ( _featureSplitComm == COMMISSION_TYPE_ZERO ) && ( _dstrTransType == AUTO_TRFER ) )
      {
         // iFee for auto transfers will always be defaulted to 0 : patterned after iFast/base

         /*DString dstrFromFundCode, dstrFromClassCode;
         DString dstrFromLoadType, dstrToLoadType;
         getField ( ifds::FundCode, dstrFromFundCode, idDataGroup );
         getField ( ifds::ClassCode, dstrFromClassCode, idDataGroup );
         dstrFromFundCode.upperCase();
         dstrFromClassCode.upperCase();
         strFundCode.upperCase();
         strClassCode.upperCase();
         _pFundDetailList->getField ( dstrFromFundCode, dstrFromClassCode, ifds::LoadType, dstrFromLoadType, BF::HOST, false );
         _pFundDetailList->getField ( strFundCode, strClassCode, ifds::LoadType, dstrToLoadType, BF::HOST, false );

         if( dstrFromLoadType == FRONTENDLOAD && dstrToLoadType != BACKENDLOAD )
         {
			   FundToList fundToList( *this );
			   if( fundToList.isBuySell( dstrFromFundCode, dstrFromClassCode, strFundCode, strClassCode ) )
			   {
				   bSetAcqFee = true;
			   }
         }*/
      }
      if( bSetAcqFee )
      {
         requestAcqFeeInquiry( idDataGroup); 
         setFieldNoValidate(ifds::Fee,_dstrDefaultAcqFee,idDataGroup,true,true,true); 
      }
      else
      {
         setFieldNoValidate(ifds::Fee,I_("0"),idDataGroup,true,true,true); 
      }
   }
}

//*****************************************************************************
void Systematic::updateAmountTypeRelatedFields(const BFDataGroupId& idDataGroup)
{
    if (allSWPCustomPayoutFndCls(idDataGroup))
    {
        setFieldNoValidate(ifds::AmountType, AMT_TYPE::AMOUNT, idDataGroup, false, true, true, true);
        setFieldNoValidate(ifds::AmtTypeOvrd, AMT_TYPE::CUSTOM, idDataGroup, false, true, false, true);
    }
    else
    {
        setFieldNoValidate(ifds::AmtTypeOvrd, NULL_STRING, idDataGroup, false, true, false, true);
    }

    setFieldValid(ifds::GrossOrNet, idDataGroup, false);
}

//*****************************************************************************
SEVERITY Systematic::CheckAmountTypeForPACSWPMultiAllocation(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "CheckAmountTypeForPACSWPMultiAllocation" ) );


   getField(ifds::TransType,_dstrTransType,idDataGroup,false);
   _dstrTransType.strip().upperCase();
   if( _dstrTransType == PAC || _dstrTransType == SWP )
   {
      if( _pSysAllocationList )
      {

         BFObjIter iter(*_pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         int inum = iter.getNumberOfItemsInList();
         if( inum > 1 )
         {
            DString dstrBusRounding, dstrAmountType;

            updateAmountTypeRelatedFields(idDataGroup);
            setAmtTypeSubList(idDataGroup);

            getField(ifds::AmountType,dstrAmountType,idDataGroup,false);
            getWorkSession().getOption( ifds::BusRounding, dstrBusRounding, idDataGroup, false );
            if( dstrBusRounding == YES && _dstrTransType == SWP && _dstrmultiCurrency == YES )
            {
               if( dstrAmountType != I_("S") )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_INVALID_AMOUNT_TYPE_FOR_SWP );   
               }
            }

			DString strMarket = DSTCommonFunctions::getMarket ();
			if (strMarket == MARKET_IDS::CANADA && _dstrTransType.strip() == SWP && dstrAmountType == I_("U") )
			{
				ADDCONDITIONFROMFILE( CND::ERR_SWP_UNITS_NOT_ALLOWED );
			}
		
			if ( strMarket == MARKET_IDS::CANADA && _dstrTransType.strip() == SWP && dstrAmountType == I_("P") )
			{				     				
				if (_pMFAccount && _pMFAccount->isRDSPAccount(idDataGroup))
					ADDCONDITIONFROMFILE( CND::ERR_SWP_PERCENT_NOT_ALLOWED );
			}

            if( _dstrTransType == PAC )
            {
               if( dstrAmountType != I_("D") )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_INVALID_AMOUNT_TYPE_FOR_PAC );   
               }
            }
            SEVERITY sev =  GETCURRENTHIGHESTSEVERITY();
            if( sev >= WARNING )
            {

               CONDITIONVECTOR* _pCond;
//CP20030319               const BFFieldId& idField = ifds::AmountType;
//CP20030319               long lFlags  = getFieldStateFlags( idField, idDataGroup );
//CP20030319               lFlags &= ~VALID; //clear valid; 
//CP20030319               setFieldStateFlags( ifds::AmountType, idDataGroup, lFlags );
               setFieldValid( ifds::AmountType, idDataGroup, false );
               getFieldConditionVector( ifds::AmountType,idDataGroup, _pCond );
               if( _pCond == NULL )
                  _pCond = new CONDITIONVECTOR;
               int count = CURRENTCONDITIONCOUNT( );
               Condition   *c = NULL;
               for( int i = 0; i < count; i++ )
               {
                  c = new Condition( *GETCURRENTCONDITION( i ));
                  _pCond->push_back( c );
               };
               setFieldConditionVector( ifds::AmountType, idDataGroup,_pCond );
               notifyObservers( ifds::AmountType, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
            }
         }

      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************       
SEVERITY Systematic::getAccountEntityXref ( AccountEntityXref *&pAccountEntityXref, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountEntityXref" ) );


   if( _pAcctEntityXref == NULL )
   {
      SEVERITY sevRtn = getWorkSession().getAccountEntityXref( idDataGroup, _pAcctEntityXref ) ;
   }

   pAccountEntityXref = _pAcctEntityXref;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************       
DString Systematic::getFeatureSplitComm()
{
   return(_featureSplitComm);
}

//******************************************************************************
bool Systematic::validBrokerFund( const DString& FromToFund, const DString& dstrFund, const DString& dstrClass, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validBrokerFund" ));
   BrokerList brokerList ( *this );
   DString brokerFund;
   _pMgmtCoOption->getField( ifds::BrokerFund,        brokerFund,        idDataGroup );
   brokerFund.strip();

   DString Fund_allowed (NO), dstrAccount, dstrTransType;;

   if( brokerFund == NO || dstrFund.empty() || dstrClass.empty() )
      return(true);

   DString dstrBroker(NULL_STRING);
   
   getField( ifds::TransType, dstrTransType, idDataGroup );
   dstrTransType.strip().upperCase();
   
   if ( FromToFund == FROMFUND )
   {
      dstrBroker = _dstrBrokerCode;
  	   getField( ifds::AccountNum, dstrAccount, idDataGroup );
      if (dstrTransType == AUTO_TRFER)
         dstrTransType = I_( "TO" );
   }
   else if ( FromToFund == TOFUND ) // get the broker code of the accountTo
   {
      MFAccount *mfAccount=NULL;

      dstrTransType = I_( "TI" );
  	   getField( ifds::AccountTo, dstrAccount, idDataGroup );
      if ( dstrAccount.strip() != NULL_STRING)
	      SEVERITY sevRtn = getWorkSession().getMFAccount( idDataGroup, dstrAccount, mfAccount );

      if ( mfAccount )
      {
         mfAccount->getField ( ifds::BrokerCode, dstrBroker, idDataGroup );
      }
   }

   //getField( ifds::Broker, dstrBroker, idDataGroup );
   dstrBroker.strip();

   // Otherwise validate if the fund and class is allowed for the broker
   if( !dstrBroker.empty() && 
       brokerList.initFundAllowed( dstrBroker, dstrFund, dstrClass, dstrAccount, dstrTransType ) <= WARNING )
   {
      BFObjIter bfIter( brokerList, idDataGroup );

      bfIter.begin();
      if( !bfIter.end() )
      {
         bfIter.getObject()->getField( ifds::FundAllow, Fund_allowed, idDataGroup );
      }
   }
   else Fund_allowed = YES;
   if (Fund_allowed != YES)
   {
		DString idiStr;
		addIDITagValue( idiStr, FUND, dstrFund );
		addIDITagValue( idiStr, CLASS, dstrClass );
		addIDITagValue( idiStr, BROKER, dstrBroker );

		// ADDCONDITIONFROMFILE( CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER );
		ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER, idiStr );
   }
   return( Fund_allowed == YES );
}


//******************************************************************************
bool Systematic::validSalesrepFund( const DString& FromToFund, const DString& dstrFund, 
                                   const DString& dstrClass, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validSalesrepFund" ));
   AgentList agentList ( *this );
   DString slsRepFund;
   _pMgmtCoOption->getField( ifds::FundEligSlsRepLvl, slsRepFund, idDataGroup );
   slsRepFund.strip();

   DString Fund_allowed (NO), dstrTransType;

   if( slsRepFund == NO || dstrFund.empty() || dstrClass.empty() )
      return(true);

   DString dstrBroker(NULL_STRING), dstrBranch, dstrSalesrep, dstrAccount;
   MFAccount *mfAccount=NULL;
   
   getField( ifds::TransType, dstrTransType, idDataGroup );
   dstrTransType.strip().upperCase();

   if ( FromToFund == FROMFUND )
   {
 	   getField( ifds::AccountNum, dstrAccount, idDataGroup );
      if (dstrTransType == AUTO_TRFER)
         dstrTransType = I_( "TO" );
   }
   if ( FromToFund == TOFUND ) // get the broker code of the accountTo
   {
  	   getField( ifds::AccountTo, dstrAccount, idDataGroup );
      dstrTransType = I_( "TI" );
   }

   if ( dstrAccount.strip() != NULL_STRING)
	   SEVERITY sevRtn = getWorkSession().getMFAccount( idDataGroup, dstrAccount, mfAccount );

   if ( mfAccount )
   {
      mfAccount->getField ( ifds::BrokerCode, dstrBroker, idDataGroup );
      mfAccount->getField ( ifds::BranchCode, dstrBranch, idDataGroup );
      mfAccount->getField ( ifds::Slsrep, dstrSalesrep, idDataGroup );
   }

   // Otherwise validate if the fund and class is allowed for the broker
   if( !dstrBroker.empty() && !dstrSalesrep.empty() &&
       agentList.init2( dstrBroker.strip(), dstrBranch.strip(), dstrSalesrep.strip(), 
         dstrFund, dstrClass, dstrAccount ) <= WARNING )
   {
      BFObjIter bfIter( agentList, idDataGroup );

      bfIter.begin();
      if( !bfIter.end() )
      {
         bfIter.getObject()->getField( ifds::ValidationPassed, Fund_allowed, idDataGroup );
      }
   }
   else Fund_allowed = YES;

   //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
   if (Fund_allowed != YES)
   {
		DString idiStr;
		addIDITagValue( idiStr, FUND, dstrFund );
		addIDITagValue( idiStr, CLASS, dstrClass );
		addIDITagValue( idiStr, AGENT, dstrSalesrep );

		ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP, idiStr );
   }
   //End ticket 2404299

   return( Fund_allowed == YES );
}

//******************************************************************************
void Systematic::checkNextProcDate( const DString& EffectiveDate, 
								    const DString& StopDate, 
									const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkNextProcDate" ) );

   DString dstrJan, dstrFeb, dstrMar, dstrApr, dstrMay, dstrJun;
   DString dstrJul, dstrAug, dstrSep, dstrOct, dstrNev, dstrDec;
   
   getField(ifds::January,         dstrJan,          idDataGroup, false );
   getField(ifds::February,        dstrFeb,          idDataGroup, false );
   getField(ifds::March,           dstrMar,          idDataGroup, false );
   getField(ifds::April,           dstrApr,          idDataGroup, false );
   getField(ifds::May,             dstrMay,          idDataGroup, false );
   getField(ifds::June,            dstrJun,          idDataGroup, false );
   getField(ifds::July,            dstrJul,          idDataGroup, false );
   getField(ifds::August,          dstrAug,          idDataGroup, false );
   getField(ifds::September,       dstrSep,          idDataGroup, false );
   getField(ifds::October,         dstrOct,          idDataGroup, false );
   getField(ifds::November,        dstrNev,          idDataGroup, false );
   getField(ifds::December,        dstrDec,          idDataGroup, false );
   
   DString dstrFrequency, dstrDayOfWeek, dstrEndOfMonth, dstrLastProcDate;
   getField(ifds::Frequency,       dstrFrequency,    idDataGroup, false );
   getField(ifds::DayOfWeek,       dstrDayOfWeek,    idDataGroup, false );
   getField(ifds::EndOfMonth,      dstrEndOfMonth,   idDataGroup, false );
   getField(ifds::LastProcessDate, dstrLastProcDate, idDataGroup, false );

   dstrJan.strip().upperCase();
   dstrFeb.strip().upperCase();
   dstrMar.strip().upperCase();
   dstrApr.strip().upperCase();
   dstrMay.strip().upperCase();
   dstrJun.strip().upperCase();
   dstrJul.strip().upperCase();
   dstrAug.strip().upperCase();
   dstrSep.strip().upperCase();
   dstrOct.strip().upperCase();
   dstrNev.strip().upperCase();
   dstrDec.strip().upperCase();
   dstrFrequency.strip().upperCase();
   dstrDayOfWeek.strip();
   dstrEndOfMonth.strip().upperCase();
   dstrLastProcDate.strip();

   DString dstrSingleFundCode, dstrSingleClassCode;
   getField( ifds::FundCode,  dstrSingleFundCode,  idDataGroup, false );
   getField( ifds::ClassCode, dstrSingleClassCode, idDataGroup, false );
   dstrSingleFundCode.strip().upperCase();
   dstrSingleClassCode.strip().upperCase();	

   // This condition should be really only for Auto Transfers which require FromFund/Class
   // and SWPs/PACs should be dealt with directly with Allocations. However, there are cases when 
   // the allocations are not updated and this validation is skipped for PACs/SWPs when non-allocated
   if ( !dstrSingleFundCode.empty() && !dstrSingleClassCode.empty() )   
   {	   	   
	    DString dstrNextProcDate, dstrPAClastRunDate, dstrSWPLastRunDate;									

		BFData query213( ifds::DSTC0213_REQ );
		DString mgmtCoIdOut;
		query213.setElementValue( ifds::CompanyId,     getMgmtCoId( mgmtCoIdOut ) );
		query213.setElementValue( ifds::Track,         I_("N") );
		query213.setElementValue( ifds::Activity,      NULL_STRING );
		query213.setElementValue( ifds::FundCode,      dstrSingleFundCode );
		query213.setElementValue( ifds::ClassCode,     dstrSingleClassCode );
		query213.setElementValue( ifds::EffectiveDate, EffectiveDate );
		query213.setElementValue( ifds::January,       dstrJan );
		query213.setElementValue( ifds::February,      dstrFeb );
		query213.setElementValue( ifds::March,         dstrMar );
		query213.setElementValue( ifds::April,         dstrApr );
		query213.setElementValue( ifds::May,           dstrMay );
		query213.setElementValue( ifds::June,          dstrJun );
		query213.setElementValue( ifds::July,          dstrJul );
		query213.setElementValue( ifds::August,        dstrAug );
		query213.setElementValue( ifds::September,     dstrSep );
		query213.setElementValue( ifds::October,       dstrOct );
		query213.setElementValue( ifds::November,      dstrNev );
		query213.setElementValue( ifds::December,      dstrDec );
		query213.setElementValue( ifds::Frequency,     dstrFrequency );
		query213.setElementValue( ifds::DayOfWeek,     dstrDayOfWeek );
		query213.setElementValue( ifds::EndOfMonth,    dstrEndOfMonth );
		query213.setElementValue( ifds::LastProcDate,  dstrLastProcDate );

		BFData *response = new BFData(ifds::DSTC0213_VW);
		if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::MEXT_PROC_DATE, query213, *response, DSTCRequestor(getSecurity()) ) <= WARNING )
		{
			response->getElementValue( ifds::NextProcessDate, dstrNextProcDate );
			dstrNextProcDate.strip();
		}
		else
		{
			delete response;
			response = NULL;
		}
		
		if( dstrNextProcDate != NULL_STRING )
		{
			if( DSTCommonFunctions::CompareDates( dstrNextProcDate, StopDate ) == DSTCommonFunctions::SECOND_EARLIER )
			{
				ADDCONDITIONFROMFILE( CND::ERR_WARN_NEXT_PROC_DATE_AFTER_STOP_DATE );
			}
			
			if( DSTCommonFunctions::CompareDates( dstrNextProcDate, EffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
			{
				ADDCONDITIONFROMFILE( CND::ERR_WARN_NEXT_PROC_DATE_BEFORE_EFFECTIVE_DATE );
			}
			
			DString idiStr;
			if( findTransType( idDataGroup, PAC ) )
			{
				getWorkSession().getOption( ifds::PACLastRunDate, dstrPAClastRunDate, idDataGroup, false );
				dstrPAClastRunDate.strip();
				if( dstrPAClastRunDate != NULL_STRING )
				{
					if( ( DSTCommonFunctions::CompareDates( dstrNextProcDate, dstrPAClastRunDate ) == DSTCommonFunctions::FIRST_EARLIER ) || 
						( DSTCommonFunctions::CompareDates( dstrNextProcDate, dstrPAClastRunDate) == DSTCommonFunctions::EQUAL ) )
					{
						DString strPAClastRunDate;
						getWorkSession().getOption( ifds::PACLastRunDate, strPAClastRunDate, idDataGroup, true );
						addIDITagValue( idiStr, I_("LAST_RUN_DATE"), strPAClastRunDate );
						ADDCONDITIONFROMFILEIDI( CND::ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE, idiStr  );
					}
				}
			}
			else if( findTransType( idDataGroup, SWP ) )
			{
				getWorkSession().getOption( ifds::SWPLastRunDate, dstrSWPLastRunDate, idDataGroup, false );
				dstrSWPLastRunDate.strip();
				if( dstrSWPLastRunDate != NULL_STRING )
				{
					if( ( DSTCommonFunctions::CompareDates( dstrNextProcDate, dstrSWPLastRunDate ) == DSTCommonFunctions::FIRST_EARLIER ) || 
						( DSTCommonFunctions::CompareDates( dstrNextProcDate, dstrSWPLastRunDate) == DSTCommonFunctions::EQUAL ) )
					{
						DString strSWPLastRunDate;
						getWorkSession().getOption( ifds::SWPLastRunDate, strSWPLastRunDate, idDataGroup, true );

						addIDITagValue( idiStr, I_("LAST_RUN_DATE"), strSWPLastRunDate );
						ADDCONDITIONFROMFILEIDI( CND::ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE, idiStr  );			
					}
				}
			}	
	   }
   }
   else    // Allocated
   {
	    // For Auto Transfer FromFund/Class are mandatory, so no from alloc	    
		if( NULL != _pSysAllocationList )
		{
			BFObjIter iter(*_pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);			
			iter.begin();		
			while( !iter.end() )
			{
				SysAllocation* pSysAllocation = dynamic_cast<SysAllocation*>(iter.getObject());
				if ( NULL != pSysAllocation )
				{
					DString dstrAllocFundCode, dstrAllocClassCode;
					pSysAllocation->getField(ifds::FundCode,  dstrAllocFundCode,  idDataGroup, false);
					pSysAllocation->getField(ifds::ClassCode, dstrAllocClassCode, idDataGroup, false);
					dstrAllocFundCode.strip().upperCase();
					dstrAllocClassCode.strip().upperCase();
					if ( !dstrAllocFundCode.empty() && !dstrAllocClassCode.empty() )
					{				
						DString dstrNextProcDate, dstrPAClastRunDate, dstrSWPLastRunDate;									

						BFData query213( ifds::DSTC0213_REQ );
						DString mgmtCoIdOut;
						query213.setElementValue( ifds::CompanyId,     getMgmtCoId( mgmtCoIdOut ) );
						query213.setElementValue( ifds::Track,         I_("N") );
						query213.setElementValue( ifds::Activity,      NULL_STRING );
						query213.setElementValue( ifds::FundCode,      dstrAllocFundCode );
						query213.setElementValue( ifds::ClassCode,     dstrAllocClassCode );
						query213.setElementValue( ifds::EffectiveDate, EffectiveDate );
						query213.setElementValue( ifds::January,       dstrJan );
						query213.setElementValue( ifds::February,      dstrFeb );
						query213.setElementValue( ifds::March,         dstrMar );
						query213.setElementValue( ifds::April,         dstrApr );
						query213.setElementValue( ifds::May,           dstrMay );
						query213.setElementValue( ifds::June,          dstrJun );
						query213.setElementValue( ifds::July,          dstrJul );
						query213.setElementValue( ifds::August,        dstrAug );
						query213.setElementValue( ifds::September,     dstrSep );
						query213.setElementValue( ifds::October,       dstrOct );
						query213.setElementValue( ifds::November,      dstrNev );
						query213.setElementValue( ifds::December,      dstrDec );
						query213.setElementValue( ifds::Frequency,     dstrFrequency );
						query213.setElementValue( ifds::DayOfWeek,     dstrDayOfWeek );
						query213.setElementValue( ifds::EndOfMonth,    dstrEndOfMonth );
						query213.setElementValue( ifds::LastProcDate,  dstrLastProcDate );

						BFData *response = new BFData(ifds::DSTC0213_VW);

						if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::MEXT_PROC_DATE, query213, *response, DSTCRequestor(getSecurity()) ) <= WARNING )
						{
							response->getElementValue( ifds::NextProcessDate, dstrNextProcDate );
							dstrNextProcDate.strip();
						}
						else
						{
							delete response;
							response = NULL;
						}						

						if( dstrNextProcDate != NULL_STRING )
						{
							if( DSTCommonFunctions::CompareDates( dstrNextProcDate, StopDate ) == DSTCommonFunctions::SECOND_EARLIER )
							{
								ADDCONDITIONFROMFILE( CND::ERR_WARN_NEXT_PROC_DATE_AFTER_STOP_DATE );
							}
							if( DSTCommonFunctions::CompareDates( dstrNextProcDate, EffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
							{
								ADDCONDITIONFROMFILE( CND::ERR_WARN_NEXT_PROC_DATE_BEFORE_EFFECTIVE_DATE );
							}

							DString idiStr;
							if( findTransType( idDataGroup, PAC ) )
							{
								getWorkSession().getOption( ifds::PACLastRunDate, dstrPAClastRunDate, idDataGroup, false );
								dstrPAClastRunDate.strip();
								if( dstrPAClastRunDate != NULL_STRING )
								{
									if( ( DSTCommonFunctions::CompareDates( dstrNextProcDate, dstrPAClastRunDate ) == DSTCommonFunctions::FIRST_EARLIER ) || 
										( DSTCommonFunctions::CompareDates( dstrNextProcDate, dstrPAClastRunDate) == DSTCommonFunctions::EQUAL ) )
									{
										DString strPAClastRunDate;
										getWorkSession().getOption( ifds::PACLastRunDate, strPAClastRunDate, idDataGroup, true );
										addIDITagValue( idiStr, I_("LAST_RUN_DATE"), strPAClastRunDate );
										ADDCONDITIONFROMFILEIDI( CND::ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE, idiStr  );
									}
								}
							}
							else if( findTransType( idDataGroup, SWP ) )
							{
								getWorkSession().getOption( ifds::SWPLastRunDate, dstrSWPLastRunDate, idDataGroup, false );
								dstrSWPLastRunDate.strip();
								if( dstrSWPLastRunDate != NULL_STRING )
								{
									if( ( DSTCommonFunctions::CompareDates( dstrNextProcDate, dstrSWPLastRunDate ) == DSTCommonFunctions::FIRST_EARLIER ) || 
										( DSTCommonFunctions::CompareDates( dstrNextProcDate, dstrSWPLastRunDate) == DSTCommonFunctions::EQUAL ) )
									{
										DString strSWPLastRunDate;
										getWorkSession().getOption( ifds::SWPLastRunDate, strSWPLastRunDate, idDataGroup, true );

										addIDITagValue( idiStr, I_("LAST_RUN_DATE"), strSWPLastRunDate );
										ADDCONDITIONFROMFILEIDI( CND::ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE, idiStr  );
									}
								}
							}
						}
					}
				}

				if ( GETCURRENTHIGHESTSEVERITY() > WARNING )
					break;

				++iter;  
			}         			            
		}				
   }           

   return;
}

//***********************************************************************************
SEVERITY Systematic::validateTransType(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTransType" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Systematic::readStopFlag ( const DString &transType,
                                    const DString &fundCode,
                                    const DString &classCode,
                                    const DString &accountNum,
                                    bool &bStopFlag, 
                                    bool &bErrorSeverity, 
                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("readStopFlag"));
   FundDetail *pFundDetail = NULL;

   if (getWorkSession().getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) &&
         pFundDetail)
   {
      FundTransTypeList *pFundTransTypeList = NULL;

      if (pFundDetail->getFundTransTypeList (pFundTransTypeList) <= WARNING &&
            pFundTransTypeList)
      {
         FundTransType *pFundTransType = NULL;

         if (pFundTransTypeList->getFundTransType (transType, 
               pFundTransType, idDataGroup) <= WARNING &&
            pFundTransType)
         {
            DString stopFlag,
               stopSeverityCode;

            pFundTransType->getStopFlag (getWorkSession(), accountNum, stopFlag, stopSeverityCode, idDataGroup);
            bStopFlag = stopFlag == YES && stopSeverityCode != I_ ("I");
            bErrorSeverity = stopSeverityCode == I_("E");
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
/*
//******************************************************************************
SEVERITY  Systematic::stopFlagOverride(const DString dstrAcctNum, 
                                  const DString dstrTransType, 
                                  const DString dstrFundCode,
                                  const DString dstrClassCode,
                                  bool &bStopFlag, bool &bErrorSeverity, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "stopFlagOverride") );

   SEVERITY sevRtn;
   FundTransTypeList *pFundTransTypeList = NULL;
   FundDetail *pFundDetail = NULL;

   if( !_pFundDetailList )
   {
      getMgmtCo().getFundDetailList( _pFundDetailList );
   }

   if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) &&  pFundDetail )
   {
      pFundDetail->getFundTransTypeList( pFundTransTypeList );

      if ( pFundTransTypeList )
      { 
         FundTransType *pFundTransType = NULL;
         pFundTransTypeList->getFundTransType ( dstrTransType, pFundTransType, idDataGroup );
         if ( pFundTransType )
         {
            DString dstrTaxJuris, dstrResProvCode, dstrTaxType, dstrAcctType, dstrAcctDesignation, dstrShrNum;
         
            MFAccount *mfAccount = NULL;

            sevRtn = getMFAccount ( dstrAcctNum, idDataGroup, mfAccount );
            if ( mfAccount ) {
               mfAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
               mfAccount->getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
               mfAccount->getField( ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false );
               mfAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup, false );
            }

            Shareholder* pShareholder = NULL;
            if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder ) <= WARNING )
            {
               if( pShareholder )
               {
                  pShareholder->getField( ifds::TaxJurisCode, dstrTaxJuris, idDataGroup );
                  pShareholder->getField( ifds::ResProvCode, dstrResProvCode, idDataGroup );
               }
            }

            DString dstrStopFlag (NO); // Stop Flag = No
            DString dstrStopSeverityCode ( I_( "E" )); //error

            sevRtn = pFundTransType->getStopFlag ( dstrTaxJuris, dstrResProvCode, dstrTaxType, 
                                          dstrAcctType, dstrAcctDesignation,
                                          dstrStopFlag, dstrStopSeverityCode, idDataGroup);
            if ( sevRtn <= WARNING )
            {
               bStopFlag = ( dstrStopFlag == YES && dstrStopSeverityCode != I_( "I" ));
               bErrorSeverity = ( dstrStopSeverityCode == I_( "E" ) );
            }
         } 
      }
   } // pFundDetail exists

   return(GETCURRENTHIGHESTSEVERITY());
}
*/
//*******************************************************************************************
SEVERITY Systematic::stopFlagCheck( const DString dstrFundCode,
                                   const DString dstrClassCode, 
                                   const DString dstrTransType,
                                   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "stopFlagCheck" ) );

   // Check Stop Flag for 

   /*ndDetail *pFundDetail = NULL;

   if( !_pFundDetailList )
   {
      getMgmtCo().getFundDetailList( _pFundDetailList );
   }*/

//   if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) &&  pFundDetail )
//   {
      bool bStopFlag (false);
//      bool bOverride (false);
      bool bErrorSeverity (true);
      long warningConID(0),errorConID(0);  //temper

      DString dstrAcctNum;
	  DString dstrRuleTypeCheck;

      getField (ifds::AccountNum, dstrAcctNum, idDataGroup);
      if (dstrTransType == PAC)
      {
//         bStopFlag = pFundDetail->stopPAC ( bOverride, idDataGroup);
         errorConID = CND::ERR_FUND_CLASS_PAC_STOP_FLAG_ON;
         warningConID = CND::ERR_WARN_FUND_CLASS_PAC_STOP_FLAG_ON;
		 dstrRuleTypeCheck = I_("08");
      }
      if ( dstrTransType == SWP )
      {
//         bStopFlag = pFundDetail->stopSWP ( bOverride, idDataGroup);
         errorConID = CND::ERR_FUND_CLASS_SWP_STOP_FLAG_ON;
         warningConID = CND::ERR_WARN_FUND_CLASS_SWP_STOP_FLAG_ON;
		 dstrRuleTypeCheck = I_("09");
      }
      if ( dstrTransType == I_( "ATO" ) )
      {
//         bStopFlag = pFundDetail->stopSysGenTrnfrOut ( bOverride, idDataGroup);
         errorConID = CND::ERR_FUND_CLASS_SYSGENTRFOUT_STOP_FLAG_ON;
         warningConID = CND::ERR_WARN_FUND_CLASS_SYSGENTRFOUT_STOP_FLAG_ON;
		 dstrRuleTypeCheck = I_("11");
      }
      if ( dstrTransType == I_( "ATI" ) )
      {
//         bStopFlag = pFundDetail->stopSysGenTrnfrIn ( bOverride, idDataGroup);
         errorConID = CND::ERR_FUND_CLASS_SYSGENTRFIN_STOP_FLAG_ON;
         warningConID = CND::ERR_WARN_FUND_CLASS_SYSGENTRFIN_STOP_FLAG_ON;
         getField( ifds::AccountTo, dstrAcctNum, idDataGroup );
		 dstrRuleTypeCheck = I_("10");
      }

  /*    if ( bOverride )
      {
         stopFlagOverride(dstrAcctNum, dstrTransType, dstrFundCode, dstrClassCode,
                          bStopFlag, bErrorSeverity, idDataGroup);
      }*/
    readStopFlag ( dstrTransType,
                     dstrFundCode,
                     dstrClassCode,
                     dstrAcctNum,
                     bStopFlag, 
                     bErrorSeverity, 
                     idDataGroup);
	  //IN2844236 - Cannot put a stop date on PAC/SWP/Automatic Transfer
	 
    if( !isNew() && isFieldsDisabledBaseOnRuleType(RULE_TYPE::BANKRUPTCY,idDataGroup))
    {
       if(isFieldUpdated (ifds::StopDate, idDataGroup))
       {
          return(GETCURRENTHIGHESTSEVERITY());
       }
    }

      if (bStopFlag)
      {    
           
         DString idiStr;
         addIDITagValue( idiStr, FUND, dstrFundCode );
         addIDITagValue( idiStr, CLASS, dstrClassCode );

         DString brokerPermits = N;
         if( dstrTransType == PAC )
         {
            DString brokerFund;
            DString accountNum;
            
            getWorkSession ().getOption ( ifds::BrokerFund, 
               brokerFund, 
               BF::HOST,
               false);
            getField(ifds::AccountNum, accountNum, idDataGroup);

            if ( brokerFund == Y &&
               !dstrFundCode.empty() &&
               !dstrClassCode.empty() &&
               !accountNum.empty())
            {
               BrokerList brokerList (*this);

               // View#90 expect TransType="PA" for PAC, 
               // not P like the other view called in this file.
               if ( !_dstrBrokerCode.empty() &&
                  brokerList.initFundAllowed (_dstrBrokerCode, dstrFundCode, 
                        dstrClassCode, accountNum, I_("PA")) <= WARNING)
               {
                  BFObjIter bfIter (brokerList, idDataGroup);

                  bfIter.begin ();
                  if (!bfIter.end ())
                  {
                     bfIter.getObject()->getField (ifds::AddPerm, 
                           brokerPermits, idDataGroup);
                     brokerPermits.strip();
                  }
               }
            }
         }
         
         if( brokerPermits == I_("N") )
         {
            if ( bErrorSeverity )
            {
               ADDCONDITIONFROMFILEIDI( errorConID, idiStr );
            }
            else 
            {
               ADDCONDITIONFROMFILEIDI( warningConID, idiStr );
            }
         }
         
         
      }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************************
// Allow user to set up "Error" or "Warning" and different Minimum amount for different tax type,
// account type, account designation, tax jurisdiction and account designation etc.
SEVERITY Systematic::minAmountOverride( const DString& dstrTransType, 
                                        const DString& dstrFundCode,
                                        const DString& dstrClassCode,
                                        DString &dstrMinAmount, bool &bErrorSeverity, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "minAmountOverride") );

   SEVERITY sevRtn;
   FundTransTypeList *pFundTransTypeList = NULL;
   FundDetail *pFundDetail = NULL;

	MFAccount *mfAccount=NULL;
	Shareholder *pShareholder=NULL;

 	DString dstrRealTransType; 
 	getField( ifds::TransType, dstrRealTransType, idDataGroup, false );
    dstrRealTransType.strip().upperCase();

	if(dstrRealTransType == AUTO_TRFER)
	{
		DString dstrAccountTo;
		getField( ifds::AccountTo, dstrAccountTo, idDataGroup, false );
		sevRtn = getWorkSession().getMFAccount( idDataGroup, dstrAccountTo, mfAccount );
	}
	else
	{
		//******fund holding not zero, skip this validation
		if( !_pMFAccount )
		{
			if( !_pList )
			   _pList = dynamic_cast<SystematicList *>(getParent());
			if( _pList )
			   _pMFAccount = _pList->getMFAccount();
		}
		mfAccount = _pMFAccount;
	}
   if (mfAccount) {

	   //DString dstrShareholderNum;
      DString accountNum;
	   //mfAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
      mfAccount->getField( ifds::AccountNum, accountNum, idDataGroup );
      
//      getWorkSession().getShareholder( idDataGroup, dstrShareholderNum, pShareholder );


      if( !_pFundDetailList )
      {
         getMgmtCo().getFundDetailList( _pFundDetailList );
      }
      
      if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) &&  pFundDetail )
      {
         pFundDetail->getFundTransTypeList( pFundTransTypeList );
         /*if ( dstrTransType == PAC )
            pFundDetail->getField( ifds::MinPAC, dstrMinAmount, idDataGroup );         
         if ( dstrTransType == SWP )
            pFundDetail->getField( ifds::MinSWP, dstrMinAmount, idDataGroup );         
         if ( dstrTransType == PURCHASE_CODE )
            pFundDetail->getField( ifds::MinInitPurAmt, dstrMinAmount, idDataGroup );         */
         if ( pFundTransTypeList )
         { 
            FundTransType *pFundTransType = NULL;
            pFundTransTypeList->getFundTransType ( dstrTransType, pFundTransType, idDataGroup );
            if ( pFundTransType )
            {
               /*DString dstrTaxJuris, dstrResProvCode, dstrTaxType, dstrAcctType, dstrAcctDesignation, dstrShrNum;
         
               mfAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
               mfAccount->getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
               mfAccount->getField( ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false );
               mfAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup, false );
  
               if( pShareholder )
               {
                  pShareholder->getField( ifds::TaxJurisCode, dstrTaxJuris, idDataGroup );
                  pShareholder->getField( ifds::ResProvCode, dstrResProvCode, idDataGroup );
               }*/
  
               DString dstrSeverityCode ( I_( "W" )); //warning

               if (dstrTransType == PURCHASE_CODE)
               {
                  sevRtn = pFundTransType->getMinAmount (
                     getWorkSession(),
                     accountNum,
                     dstrMinAmount, 
                     dstrSeverityCode, 
                     idDataGroup);
               }
               else
               {
                  sevRtn = pFundTransType->getSubseqMinAmount (
                     getWorkSession(),
                     accountNum,
                     dstrMinAmount, 
                     dstrSeverityCode, 
                     idDataGroup);
               }
               if (sevRtn <= WARNING)
               {
                  bErrorSeverity = ( dstrSeverityCode == I_( "E" ) );
               }
            } 
         }
      }
   }


   return(GETCURRENTHIGHESTSEVERITY());

}
 
//*******************************************************************************************
        
SEVERITY Systematic::cappedDateRule ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "cappedDateRule") );
   bool havepermission = getWorkSession().hasReadPermission( UAF::RESTART_PAC_ON_CAPPED_FUND );
   if ( havepermission )
      return NO_CONDITION;
   DString dstrEndDate, dstrCurrBusDate;
   getField ( ifds::StopDate, dstrEndDate, idDataGroup );        
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );   	  
   //Cannot restart a capped fund.
   if( DSTCommonFunctions::CompareDates( dstrCurrBusDate, dstrEndDate ) == DSTCommonFunctions::FIRST_EARLIER ) {
      //Raise Error cannot restart capped fund.
      ADDCONDITIONFROMFILE( CND::ERR_CANNOT_RESTART_CAPPED_FUND );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************************

SEVERITY Systematic::ValidateCappedAmt ( const DString& dstrOriAmount, const DString& dstrAmount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateProtectedAmt") );
   
   double dAmount, dOriAmount;
   dAmount = DSTCommonFunctions::convertToDouble(dstrAmount); 
   dOriAmount = DSTCommonFunctions::convertToDouble(dstrOriAmount);      
   if ( dAmount > dOriAmount ) {
      //The amount of a capped fund cannot be increased.
      ADDCONDITIONFROMFILE( CND::ERR_AMT_CAPPED_FUND_INCREASE );         
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************************

bool Systematic::isCappedFund ( const DString& dstrFundCode, const BFDataGroupId& idDataGroup )
{
   DString dstrEffectiveDate, dstrCurrBusDate, dstrCappedDate;

   //Capped Fund Rule :
   //If the effective date of the systematic is before the current business day, then use the current
   //business date to check to see if the fund is capped.
   //If the effective date of the systematic is future dated.  Use the effective date of the systematic
   //to check if the fund is capped.

   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );  
   if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrCurrBusDate ) == DSTCommonFunctions::FIRST_EARLIER ) {
      dstrCappedDate = dstrCurrBusDate;
   } else {
      dstrCappedDate = dstrEffectiveDate;
   }

   MgmtCo &mgmtCo = getMgmtCo();
   FundMasterList* pFundMasterList = NULL;
   mgmtCo.getFundMasterList ( pFundMasterList );
   FundMaster *pFundMaster = NULL;
   if( pFundMasterList && pFundMasterList->getFundMaster (dstrFundCode, idDataGroup, pFundMaster) )
   {
      return pFundMaster->isCappedFund ( dstrCappedDate, idDataGroup );
   } 
   return false;
}


//******************************************************************************
SEVERITY Systematic::getErrMsg( DString dstrErrNum,       
                            long    lErrConditionId, 
                            long    lWarnConditionId, 
                            const BFDataGroupId& idDataGroup, 
                            DString idiStr )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsg" ) );

   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
   {
      _pErrMsgRulesList->getEWI( dstrErrNum, lErrConditionId, lWarnConditionId, idDataGroup, idiStr );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void Systematic::getErrMsgValue( DString dstrErrNum,       
                            const BFDataGroupId& idDataGroup, 
                            DString& dstrErrValue )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsg" ) );

   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
   {	   
      _pErrMsgRulesList->getEWIValue( dstrErrNum, idDataGroup, dstrErrValue);
   }

}

//******************************************************************************
SEVERITY Systematic::getBankInstructionsList(
   SystematicBankInstructionsList *&pSystematicBankInstructionsList, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));
	
   //check whether PayType is EFT, only in this case we have banking
   if (PayTypeIsEFT(idDataGroup))
   {
      BFObjectKey objKey(I_("Systematic_BankInstructionsList"), idDataGroup, 
         OBJ_ACTIVITY_NONE, OBJ_TYPE_NONE);

      pSystematicBankInstructionsList = NULL;
      pSystematicBankInstructionsList = 
         dynamic_cast<SystematicBankInstructionsList *>(findObject(objKey));
      if (!pSystematicBankInstructionsList && bCreate)
      {
         pSystematicBankInstructionsList = new SystematicBankInstructionsList(*this);
         if (pSystematicBankInstructionsList)
         {
            DString dstrAccountNum;

            getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);

            SEVERITY severity = isNew() ? 
               pSystematicBankInstructionsList->initNew(dstrAccountNum, idDataGroup) : 
               pSystematicBankInstructionsList->init(dstrAccountNum, idDataGroup);

            if (severity <= WARNING)
            {
               setObject(objKey, pSystematicBankInstructionsList);
            }
            else
            {
               delete pSystematicBankInstructionsList;
               pSystematicBankInstructionsList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Systematic::isSWPGoodAtDate( const BFDataGroupId& idDataGroup, const DString& dstrDate )
{
	DString dstrTransType,dstrStatus,dstrEffectiveDate,dstrStopDate;
   getField( ifds::TransType, dstrTransType, idDataGroup, false);   
	dstrTransType.strip().upperCase();
   getField( ifds::StatusCode, dstrStatus, idDataGroup, false);   
	dstrStatus.strip().upperCase();
	getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false );
	getField(ifds::StopDate,dstrStopDate,idDataGroup,false );
	dstrEffectiveDate.strip();
	dstrStopDate.strip();
	bool bActiveDate = DSTCommonFunctions::IsDateBetween(dstrEffectiveDate, dstrStopDate,dstrDate );
   bool bRet = dstrStatus == YES && dstrTransType == SWP && bActiveDate;
	return bRet;
}

//******************************************************************************
SEVERITY Systematic::cappedFundRule ( const DString& dstrFundCode, const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("cappedFundRule"));

   DString dstrEffectiveDate, dstrCurrBusDate, dstrCappedDate;

   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );  
   if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrCurrBusDate ) == DSTCommonFunctions::FIRST_EARLIER ) 
      dstrCappedDate = dstrCurrBusDate;  // if effective date is back dated, then compare the current business date
   else 
      dstrCappedDate = dstrEffectiveDate; 

   if ( dstrFundCode != NULL_STRING )
   {
      FundMaster *pFundMaster = NULL;
      if( _pFundMasterList && _pFundMasterList->getFundMaster (dstrFundCode, idDataGroup, pFundMaster) )
      {
         if ( pFundMaster )
            pFundMaster->cappedFundRule ( dstrCappedDate, idDataGroup );
      }
   }
   return GETCURRENTHIGHESTSEVERITY();

}


//******************************************************************************
bool Systematic::isFileProcessorApplicable( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "isFileProcessorApplicable( const BFDataGroupId * )" ) );
  
	bool bIsFileProcessorApplicable = false;	
	
	if ( PayTypeIsEFT( idDataGroup ) )
	{
		DString dstrTransType;
		getField( ifds::TransType, dstrTransType, idDataGroup );

		DString dstrACH;
		if ( PAC == dstrTransType.strip().upperCase() )
			getWorkSession ().getOption (ifds::ACHPAC, dstrACH, idDataGroup, false );
		else if ( SWP == dstrTransType.strip().upperCase() )
			getWorkSession ().getOption (ifds::ACHSWP, dstrACH, idDataGroup, false );
      
		bIsFileProcessorApplicable = dstrACH.strip().upperCase() == I_( "Y") ? true : false;
	}

	return bIsFileProcessorApplicable;
}

//******************************************************************************
SEVERITY Systematic::systematicPayTypeRelatedChangesForFileProcessor( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "systematicPayTypeRelatedChangesForFileProcessor( const BFDataGroupId * )" ) );

	bool bFileProcessorApplicable = true;

//	DString dstrGridSubstList;   
//	BFProperties *pBFProperties = getFieldProperties (ifds::SystematicGridLeftHeading, idDataGroup );
//	pBFProperties->getAllSubstituteValues( dstrGridSubstList );	
	
	if ( !isFileProcessorApplicable( idDataGroup ) )
	{
		//remove Payment Method and File Processor
//		dstrGridSubstList = removeItemFromSubtList( dstrGridSubstList, I_( "PayMethod" ) );
//		dstrGridSubstList = removeItemFromSubtList( dstrGridSubstList, I_( "ACHProcessor" ) );

		// Reinitialize File Processor related fields
		setFieldNoValidate( ifds::PayMethod, DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): I_("EFT"), idDataGroup );
		setFieldNoValidate( ifds::ACHProcessor, NULL_STRING,  idDataGroup );

		bFileProcessorApplicable = false;					  
	}		
	else
	{	
//		int nPos = dstrGridSubstList.find( I_( "PayMethod" ) );
//		if (nPos == DString::npos)
//		{
//			dstrGridSubstList = I_( "PayMethod=Payment Method;ACHProcessor=File Processor;" ) + dstrGridSubstList;
			setFieldNoValidate( ifds::PayMethod, DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): I_("EFT"), idDataGroup );
			bFileProcessorApplicable = true;	
			setPayMethod(idDataGroup);
//		}
	}
	
	//setFieldAllSubstituteValues( ifds::SystematicGridLeftHeading, idDataGroup, dstrGridSubstList );

	setFieldRequired( ifds::PayMethod,    idDataGroup, bFileProcessorApplicable );
	setFieldRequired( ifds::ACHProcessor, idDataGroup, bFileProcessorApplicable );

	setFieldReadOnly (ifds::ACHProcessor, idDataGroup, !bFileProcessorApplicable );
	setFieldReadOnly (ifds::PayMethod,    idDataGroup, !bFileProcessorApplicable );

	payMethodRelatedChanges( idDataGroup );
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Systematic::payMethodRelatedChanges( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "payMethodRelatedChanges( const BFDataGroupId * )" ) );

	if( isFileProcessorApplicable( idDataGroup ) )
   {
		setFileProcessor( idDataGroup );
		setSettleCurrency( idDataGroup );

		DString dstrPayMethod;
      getField (ifds::PayMethod, dstrPayMethod, idDataGroup, false);
      dstrPayMethod.strip ();
      		
		if ( I_( "CHQ" ) == dstrPayMethod.upperCase() )
		{
			// Address Code is required
			setFieldRequired( ifds::AddrCode, idDataGroup, true );
			
			// Bank Information is not required
			setValidFlag( ifds::BankInformation, idDataGroup, true );
			
			setFieldRequired( ifds::BankAcctNum, idDataGroup, false );
			setValidFlag(ifds::BankAcctNum, idDataGroup, true );
		}
		else
		{
			// Address Code is not required
			setFieldRequired( ifds::AddrCode, idDataGroup, false );

			// Bank Information is required
			setValidFlag( ifds::BankInformation, idDataGroup, false );

			setFieldRequired( ifds::BankAcctNum, idDataGroup, true );
			setValidFlag(ifds::BankAcctNum, idDataGroup, false );
		}
   }

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Systematic::setFileProcessor( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "setFileProcessor( const BFDataGroupId * )" ) );
	
	if( isFileProcessorApplicable( idDataGroup ) )
   {
      DynamicSubListHolder *pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
      assert( pDynamicSubListHolder ); 
      
		DString dstrPayMethod, dstrTransType, dstrFileProcessorSubstList, dstrSettleCurrency;
      getField (ifds::PayMethod, dstrPayMethod, idDataGroup, false);
      dstrPayMethod.strip ();
      getField (ifds::TransType, dstrTransType, idDataGroup, false);
      dstrTransType.strip ();
      getField (ifds::BankAcctCurrency, dstrSettleCurrency, idDataGroup, false);
      dstrSettleCurrency.strip ();
      
		if ( NULL != pDynamicSubListHolder )
		{			
			if( !dstrSettleCurrency.empty() )
			{
				dstrFileProcessorSubstList = pDynamicSubListHolder->getFileProcSubList( dstrTransType,
																												dstrPayMethod,
																												dstrSettleCurrency ); 
			}
			else
			{
				dstrFileProcessorSubstList = pDynamicSubListHolder->getFileProcSubList( dstrTransType,
																												dstrPayMethod); 
			}

			setFieldAllSubstituteValues (ifds::ACHProcessor, idDataGroup, dstrFileProcessorSubstList );
		}
			
		bool bFileProcessorRequired = true;
		if ( dstrFileProcessorSubstList.empty() )
		{
			bFileProcessorRequired = false;
			setFieldNoValidate( ifds::ACHProcessor, NULL_STRING, idDataGroup );
		}
		
		setFieldRequired( ifds::ACHProcessor, idDataGroup, bFileProcessorRequired );
		setValidFlag(ifds::ACHProcessor, idDataGroup, !bFileProcessorRequired );	
		if (DSTCommonFunctions::getMarket () == MARKET_IDS::CANADA && bFileProcessorRequired)
		{
			setFieldNoValidate (ifds::ACHProcessor, 
				                dstrFileProcessorSubstList.substr(0,dstrFileProcessorSubstList.find('=')), 
						        idDataGroup, 
							    false, 
								true, 
								true);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Systematic::setPayMethod(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setPayMethodSubstSet"));
	
	if(isFileProcessorApplicable(idDataGroup))
	{
		DynamicSubListHolder *pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
		assert(pDynamicSubListHolder); 

		DString dstrTransType, dstrSettleCurrency, dstrFileprocessor, dstrPayMethodSubstList;
		getField(ifds::TransType, dstrTransType, idDataGroup, false);
		dstrTransType.strip ();
		getField(ifds::BankAcctCurrency, dstrSettleCurrency, idDataGroup, false);
		dstrSettleCurrency.strip ();
		getField(ifds::ACHProcessor, dstrFileprocessor, idDataGroup, false);
		dstrFileprocessor.strip ();

		if(NULL != pDynamicSubListHolder)
		{
			if(!dstrSettleCurrency.empty())
			{
				dstrPayMethodSubstList = pDynamicSubListHolder->getPayMethodSubList(dstrTransType, dstrFileprocessor, dstrSettleCurrency); 
			}
			else
			{
				dstrPayMethodSubstList = pDynamicSubListHolder->getPayMethodSubList(dstrTransType, dstrFileprocessor); 
			}
			setFieldAllSubstituteValues(ifds::PayMethod, idDataGroup, dstrPayMethodSubstList);
		}

		if(dstrPayMethodSubstList.empty())
		{
			BFProperties *pProperties = getFieldProperties(ifds::PayMethod, idDataGroup);
			if(pProperties)
			{
				pProperties->getAllSubstituteValues(dstrPayMethodSubstList);
			}
			setFieldAllSubstituteValues(ifds::PayMethod, idDataGroup, dstrPayMethodSubstList);
		}
		setFieldRequired(ifds::PayMethod, idDataGroup, true);
		setValidFlag(ifds::PayMethod, idDataGroup, false);	
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Systematic::setSettleCurrency( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "setSettleCurrency( const BFDataGroupId * )" ) );

	DString dstrMultiCurrency;	
   getWorkSession ().getOption (ifds::MultiCurrency, dstrMultiCurrency, BF::HOST );
	if( dstrMultiCurrency == YES)
   {
      DString dstrCurrencySubstList;
      if(isFileProcessorApplicable( idDataGroup ) )
      {
         DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo ().getDynamicSubListHolder ();
         assert( pDynamicSubListHolder ); 
         
		   DString dstrPayMethod, dstrTransType, dstrFileProcessor ;
         getField (ifds::PayMethod, dstrPayMethod, idDataGroup, false);
         dstrPayMethod.strip ();
         getField (ifds::TransType, dstrTransType, idDataGroup, false);
         dstrTransType.strip ();
         getField (ifds::ACHProcessor, dstrFileProcessor, idDataGroup, false);
         dstrFileProcessor.strip ();
         
		   if ( NULL != pDynamicSubListHolder && !dstrFileProcessor.empty() )
		   {
			   dstrCurrencySubstList = pDynamicSubListHolder->getCurrencySubList( dstrTransType, 
																									   dstrPayMethod, 
																									   dstrFileProcessor );            
		   }
      }
		// If the retrieved Currency List is empty (no record has been defined in bankfileprocdetl for the
		// passed parameters, then load the whole Currency List
		if( dstrCurrencySubstList.empty () )
      {		
			dstrCurrencySubstList = _dstrHostCurrencyList;
		}
		
      BFProperties* pSettleCurrProp = _pMFAccount->getFieldProperties(ifds::SettleCurrency, idDataGroup);
      DString dstrSettleCurrAllSubst;
      pSettleCurrProp->getAllSubstituteValues(dstrSettleCurrAllSubst);

      DString currSubstList;

      I_CHAR *temp = const_cast<I_CHAR*> (dstrSettleCurrAllSubst.c_str ());
      do 
      {
         DString currencyCode;
         DString currencyDescr;

         temp = parseIdiString (temp, currencyCode, currencyDescr);    
         currencyCode += I_("=");
//find if currency code is valid
		 if(dstrCurrencySubstList.find(currencyCode) != DString::npos )
            currSubstList += currencyCode + currencyDescr + I_(";");
         //if (isCodeInList (currencyCode, dstrCurrencySubstList))
         //{
         //   currSubstList += currencyCode + I_("=") + currencyDescr + I_(";");
         //}
      } while (temp && temp != NULL_STRING && *temp);

      
		setFieldAllSubstituteValues (ifds::BankAcctCurrency, idDataGroup, currSubstList);
		//have to force validation, because substitute values have changed
		setValidFlag (ifds::BankAcctCurrency, idDataGroup, false);		

		// Set Bank Settle Currency field, and make sure is read only
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Systematic::isWHTaxApplicable( const BFDataGroupId &idDataGroup )
{
	bool bIsTaxApplicable = false;	
	DString dstrTransType;
	getField( ifds::TransType,  dstrTransType, idDataGroup );
		
	if ( SWP == dstrTransType.strip().upperCase() )
	{		
		if ( NULL != _pMFAccount )
		{
			DString dstrTaxType, dstrRegisteredTaxTypes;
			_pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup );

			getWorkSession().getOption( ifds::RegisteredTaxTypes, dstrRegisteredTaxTypes, idDataGroup, false );
			
         if( dstrRegisteredTaxTypes.find( dstrTaxType.strip() ) != DString::npos )
			{
				bIsTaxApplicable = true;
			}
       
		}		
	}

	return bIsTaxApplicable;
}

//******************************************************************************
SEVERITY Systematic::transTypeWHTaxRelatedChanges( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "transTypeWHTaxRelatedChanges( const BFDataGroupId * )" ) );

//	DString dstrGridSubstList;   
//	BFProperties *pBFProperties = getFieldProperties (ifds::SystematicGridLeftHeading, idDataGroup );
//	pBFProperties->getAllSubstituteValues( dstrGridSubstList );	
	
	if ( !isWHTaxApplicable( idDataGroup ) )
	{
		//remove FedTaxPUDOverride, FedRate, ProvTaxPUDOverride, ProvRate
//		dstrGridSubstList = removeItemFromSubtList( dstrGridSubstList, I_( "FedTaxPUDOverride" ) );
//		dstrGridSubstList = removeItemFromSubtList( dstrGridSubstList, I_( "FedRate" ) );
//		dstrGridSubstList = removeItemFromSubtList( dstrGridSubstList, I_( "ProvTaxPUDOverride" ) );
//		dstrGridSubstList = removeItemFromSubtList( dstrGridSubstList, I_( "ProvRate" ) );

		// Reinitialize WHTax related fields
		// No Override for both Fed and Tax
		setFieldNoValidate( ifds::FedTaxPUDOverride,  I_( "0" ),    idDataGroup ); 		
		setFieldNoValidate( ifds::ProvTaxPUDOverride, I_( "0" ),    idDataGroup );			
	}		
	else
	{	
		// The four WHTAx related fields will be inserted between SplitCommission and Batch Name
//		int iPos = dstrGridSubstList.find( I_( "FedTaxPUDOverride" ) );
//		if (iPos == DString::npos)
//		{
//			unsigned uLength = dstrGridSubstList.length();
//			DString dstrGridSubstList1, dstrGridSubstList2;
//			int iPosBatchName = dstrGridSubstList.find( I_( "BatchName" ) );
//			if ( iPosBatchName != DString::npos )
//			{				
//				dstrGridSubstList1 = dstrGridSubstList.left( iPosBatchName );			
//				dstrGridSubstList2 = dstrGridSubstList.right( uLength - iPosBatchName );
//			}
			
//			dstrGridSubstList = dstrGridSubstList1 + I_( "FedTaxPUDOverride=Override Fed Tax;FedRate=Federal Tax;ProvTaxPUDOverride=Override Prov Tax;ProvRate=Provincial Tax;" ) + dstrGridSubstList2;						
	//	}
	}	


//	setFieldAllSubstituteValues( ifds::SystematicGridLeftHeading, idDataGroup, dstrGridSubstList );

	setFieldReadOnly (ifds::FedTaxPUDOverride,  idDataGroup, !isWHTaxApplicable( idDataGroup ) );		
	setFieldReadOnly (ifds::ProvTaxPUDOverride, idDataGroup, !isWHTaxApplicable( idDataGroup ) );		

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Systematic::validateTaxPUDOverride( const DString &dstrTaxPUDOverride, 
														   const DString &dstrTaxRate,
															const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "validateTaxPUDOverride( const DString &,const DString & )" ) );

	// If TaxPUDOverride is 'Percentage Override', then make sure the value is between 0 and 100
	// If TaxPUDOverride is 'Amount Override', then make sure the value is positive and less than Transaction Amount.

	double dblRateAmount = DSTCommonFunctions::convertToDouble( dstrTaxRate );

	// If Override Tax = Percentage Override
	if ( I_( "2" ) == dstrTaxPUDOverride )
	{
		// Make sure Percentage is between 0 and 100
		if ( 0 > dblRateAmount  || dblRateAmount > 100 )
		{
			// Tax Rate must be between 0% and 100%
			ADDCONDITIONFROMFILE( CND::ERR_TAX_RATE_LESS_THAN_ZERO_OR_GREATER_THAN_100 );
		}
	}
	// If Override Tax = Amount Override
	else if ( I_( "1" ) == dstrTaxPUDOverride )
	{
		// Make sure Amount is positive
		if ( 0 > dblRateAmount )
		{
			// Tax Amount cannot be negative
			ADDCONDITIONFROMFILE( CND::ERR_TAX_AMOUNT_NEGATIVE );
		}		
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Systematic::validateTaxAmountPUDOverride( const DString &dstrTaxPUDOverride, 
															      const DString &dstrTaxRate, 
																	const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "validateTaxAmountPUDOverride( const DString &,const DString & )" ) );

	// Validation done only if Trade Amount Type is Amount

	DString dstrAmountType;
	getField( ifds::AmountType, dstrAmountType,idDataGroup,false );
	dstrAmountType.strip().upperCase();

	if ( I_( "D" ) == dstrAmountType )
	{
		double dblRateAmount = DSTCommonFunctions::convertToDouble( dstrTaxRate );

		// If Override Tax = Amount Override
		if ( I_( "1" ) == dstrTaxPUDOverride )
		{		
			DString dstrAmount;
			getField( ifds::Amount, dstrAmount, idDataGroup );
			double dblAmount = DSTCommonFunctions::convertToDouble( dstrAmount );
			if ( dblRateAmount > dblAmount )
			{
				// Tax Amount cannot be greater than Amount
				ADDCONDITIONFROMFILE( CND::ERR_TAX_AMOUNT_GREATER_THAN_AMOUNT );
			}
		}		
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Systematic::getSystematicDefault ( const BFFieldId &genControlDefaultFieldId, 
                                            DString &defaultValue, 
                                            const BFDataGroupId &idDataGroup
                                          )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "getSystematicDefault" ) );

   DString transType,
      transTypeList,
      defaultList;

   getField (ifds::TransType, transType, idDataGroup, false);
   defaultValue = NULL_STRING;
   getWorkSession().getOption ( ifds::TransTypeDefault, 
                                transTypeList, 
                                BF::HOST, 
                                false
                              );
   getWorkSession().getOption ( genControlDefaultFieldId, 
                                defaultList, 
                                BF::HOST, 
                                false
                              );

//start chopping the string
   do
   {
      DString::size_type pos = 0;
      DString transType_;

      EXTRACT_VALUE(transTypeList, transType_)
      if (transType_ == transType) //found the transaction type
      {
         EXTRACT_VALUE (defaultList, defaultValue)
         break;
      }
      else //cut the string
      {
         CHOP_STRING (transTypeList)
         CHOP_STRING (defaultList)
      }
   }
   while (transTypeList != NULL_STRING);
	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Systematic::setFieldValidFlag( const BFFieldId &fieldId, 
										const BFDataGroupId &idDataGroup, 
										bool bValid )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_( "setFieldValidFlag" ) );

	setValidFlag( fieldId, idDataGroup, bValid );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY Systematic::validateAccountClosedCountry ( const DString &strTransType,
                                                    const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAccountClosedCountry"));

   /*
      PET157837 FN02 Country Schedule - Check account is closed country or not.
                                        If yes, stop the money-in transaction.
   */
   DString dstrTransType(strTransType);      
   // ensuring this is PAC
   if( dstrTransType.strip().upperCase() == TRADETYPE::PAC )
   {
      MFAccount *pMFAccount = NULL;
      // get MFAccount
      DString dstrAccountNum;
      getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      
      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                           dstrAccountNum, 
                                           pMFAccount) <= WARNING && pMFAccount )
      {
         DString dstrIsClosedCountryResident;
         pMFAccount->getField( ifds::IsClosedCountryResident, dstrIsClosedCountryResident, idDataGroup, false );  
         if ( dstrIsClosedCountryResident.strip().upperCase() == YES )
         {
            // Raise error message, No PAC allowed for closed country resident.
            
            DString idiStr, dstrTransType;
            getField(ifds::TransType, dstrTransType, idDataGroup, true);
            addIDITagValue (idiStr, I_("TRADETYPE"), dstrTransType);    
            ADDCONDITIONFROMFILEIDI (CND::ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN , idiStr);
         }      
   
      }               
   }  // end check PAC
     
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Systematic::validateFromToFundClassAcctTo (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFromToFundClassAcctTo"));

   DString dstrAccountTo,
           dstrFromFund,
           dstrFromClass,
           dstrToFund,
           dstrToClass;
           
   getField (ifds::AccountTo, dstrAccountTo, idDataGroup, false);
   getField (ifds::FundCode, dstrFromFund, idDataGroup, false);
   getField (ifds::ClassCode, dstrFromClass, idDataGroup, false);
   getField (ifds::FundToCode, dstrToFund, idDataGroup, false);
   getField (ifds::ClassToCode, dstrToClass, idDataGroup, false);
   
   
   if ( dstrAccountTo != NULL_STRING &&
        dstrFromFund != NULL_STRING &&
        dstrFromClass != NULL_STRING &&
        dstrToFund != NULL_STRING &&
        dstrToClass != NULL_STRING )  
   {
      
      // PET157837 FN02 Country Schedule - If Transfer to same fund/class as FromFund/FromClass, dont need to validate the ClosedCountry criteria
      
      if( ! (dstrFromFund.strip().upperCase() == dstrToFund.strip().upperCase() &&
             dstrFromClass.strip().upperCase() == dstrToClass.strip().upperCase()) )
      {
   
         DString dstrTransType;
	      getField(ifds::TransType, dstrTransType, idDataGroup, false);
	        
         // If ClosedCountry is applicable and Plantype is in the list. 
         if( dstrTransType.strip().upperCase() == AUTO_TRFER )
         {
            MFAccount *pMFAccount = NULL;
            // get MFAccount
            DString dstrAccountTo;
            getField(ifds::AccountTo, dstrAccountTo, idDataGroup, false);
            
            if ( getWorkSession().getMFAccount ( idDataGroup, 
                                                 dstrAccountTo, 
                                                 pMFAccount) <= WARNING && pMFAccount )
            {
               DString dstrIsClosedCountryResident;
               pMFAccount->getField( ifds::IsClosedCountryResident, dstrIsClosedCountryResident, idDataGroup, false );  
         
               if ( dstrIsClosedCountryResident.strip().upperCase() == YES )
               {
                  // Raise error message, No Customizing Service allowed for closed country resident.
                  DString idiStr;
                  addIDITagValue (idiStr, I_("TRADETYPE"), I_("Customizing Service"));    
                  ADDCONDITIONFROMFILEIDI (CND::ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN , idiStr);
               } // end if closecountry == yes   
   
            } // end if getMFAccount()       
            
         }      
      } // end if fromfund/class same as tofund/class

   
   } // end if checks NULL_STRING
   
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY Systematic::getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList,
                                              const DString& transType,
                                              const DString& fundCode,
                                              const DString& classCode,
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFundLmtOverrideList"));

   pFundLmtOverrideList = NULL;
   
   DString strKey;
   
   strKey = I_("FundLmtOverrideList");
   strKey += I_(";TransType=");
   strKey += transType;
   strKey += I_(";FundCode=");
   strKey += fundCode;   
   strKey += I_(";ClassCode=");
   strKey += classCode;   
   pFundLmtOverrideList = 
      dynamic_cast<FundLmtOverrideList *>(BFCBO::getObject(strKey, idDataGroup));

   if (!pFundLmtOverrideList )
   {
      pFundLmtOverrideList = new FundLmtOverrideList (*this);
      if (pFundLmtOverrideList->init (fundCode, classCode, transType) <= WARNING)
      {
         setObject (pFundLmtOverrideList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
      }
      else
      {
         delete pFundLmtOverrideList;
         pFundLmtOverrideList = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Systematic::disableFieldsBaseOnRuleType( const DString& ruleType, 
                                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("disableFieldsBaseOnRuleType"));
   bool bDisableStopDate = false;
   bool bReadOnlyBaseOnRuleType = isFieldsDisabledBaseOnRuleType (ruleType,idDataGroup, bDisableStopDate);
   
   if(bReadOnlyBaseOnRuleType)
   {
      for (int i = 0; i < NUM_FIELDS; i++)
      {
         const BFFieldId idField = classFieldInfo[i].getFieldId();    

         if ((idField != ifds::StatusCode ) && 
               (idField != ifds::StopDate || bDisableStopDate ))
         {
            setFieldReadOnly (idField, idDataGroup, true);
         }
      }

      DString dstrIndexExist;
      getField( ifds::IndexExist, dstrIndexExist, idDataGroup, false);   
      if( dstrIndexExist == YES )
      {
         SysIndexList *pSysIndexList;
         if( getSystematicIndexList ( idDataGroup, pSysIndexList ) <= WARNING )
            pSysIndexList->markReadOnly ( idDataGroup );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Systematic::isFieldsDisabledBaseOnRuleType( const DString& ruleType, 
                                                 const BFDataGroupId &idDataGroup,
                                                 bool &bDisableStopDate /*false*/)
{
   DString strTransType,
      accountNum,
      accountNumTo,
      fundCode,
      fundToCode,
      classCode,
      classToCode;

   getField( ifds::AccountNum, accountNum, idDataGroup, false);
   getField( ifds::TransType, strTransType, idDataGroup, false );
   getField( ifds::FundCode, fundCode, idDataGroup, false );
   getField( ifds::ClassCode, classCode, idDataGroup, false );
   strTransType.strip().upperCase();
   accountNum.strip().upperCase();
   fundCode.strip().upperCase();
   classCode.strip().upperCase();

   bool bReadOnlyBaseOnRuleType = false;
   if( strTransType == AUTO_TRFER )
   {
      FundLmtOverrideList *pFundLmtOverrideList = NULL;
      FundLmtOverrideList *pFundToLmtOverrideList = NULL;
      FundLmtOverride *pFundLmtOverride = NULL;

      getField( ifds::AccountTo, accountNumTo, idDataGroup, false );
      getField( ifds::FundToCode, fundToCode, idDataGroup, false );
      getField( ifds::ClassToCode, classToCode, idDataGroup, false );

      accountNumTo.strip().upperCase();
      fundToCode.strip().upperCase();
      classToCode.strip().upperCase();
      
      if(!fundCode.empty() && !classCode.empty())
      {
         getFundLmtOverrideList(pFundLmtOverrideList,
                                TRADETYPE::AUTO_TRANSFER_OUT,
                                fundCode,
                                classCode,
                                idDataGroup);
         if ( pFundLmtOverrideList != NULL &&
            pFundLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
                                                       accountNum, 
                                                       ruleType, 
                                                       pFundLmtOverride, 
                                                       idDataGroup) <= WARNING && 
            pFundLmtOverride )
         {
            // disable fields
            DString stopFlag;
            pFundLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
            stopFlag.strip().upperCase();

            bReadOnlyBaseOnRuleType = stopFlag == I_("Y");
         }
      }

      if(!fundToCode.empty() && !classToCode.empty())
      {
         getFundLmtOverrideList(pFundToLmtOverrideList,
                                TRADETYPE::AUTO_TRANSFER_IN,
                                fundToCode,
                                classToCode,
                                idDataGroup);

         FundLmtOverride *pFundToLmtOverride = NULL;                                
         if(!bReadOnlyBaseOnRuleType && 
            pFundToLmtOverrideList != NULL &&
            pFundToLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
                                                         accountNumTo, 
                                                         ruleType, 
                                                         pFundToLmtOverride, 
                                                         idDataGroup) <= WARNING &&                                                      
            pFundToLmtOverride)
         {
            DString stopFlag;
            pFundToLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
            stopFlag.strip().upperCase();

            bReadOnlyBaseOnRuleType = stopFlag == I_("Y");
         }
      }
      else
      {
         AutoAcctTransAllocationList *pAtAcctAllocationList = NULL;
         if( getAtAcctAllocationList(pAtAcctAllocationList) <= WARNING && 
             pAtAcctAllocationList )
         {
            BFObjIter iter2(*pAtAcctAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
            DString dstrFundCodeB, dstrClassCodeB, dstrKey;
            while( !iter2.end() )
            {
               if(dynamic_cast<AutoAcctTransAllocation*>(iter2.getObject()))
               {
                  AutoAcctTransAllocation*   pAcctTransAllocation = 
                     static_cast<AutoAcctTransAllocation*>(iter2.getObject());               

                  if(pAcctTransAllocation)
                  {   
                     AutoTransAllocationList *pInnerAtAllocationList = NULL;
                     pAcctTransAllocation->getAtAllocationList(pInnerAtAllocationList);

                     BFObjIter iter3(*pInnerAtAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

                     while( !iter3.end() )
                     {
                        iter3.getObject()->getField( ifds::FundCode, dstrFundCodeB,  idDataGroup, false );
                        iter3.getObject()->getField( ifds::ClassCode, dstrClassCodeB,  idDataGroup, false );

                        if(!dstrFundCodeB.strip().upperCase().empty() && !dstrClassCodeB.strip().upperCase().empty())
                        {
                           getFundLmtOverrideList( pFundToLmtOverrideList,
                                                   TRADETYPE::AUTO_TRANSFER_IN,
                                                   dstrFundCodeB,
                                                   dstrClassCodeB,
                                                   idDataGroup);

                           FundLmtOverride *pFundToLmtOverride = NULL;
                           if ( pFundToLmtOverrideList != NULL &&
                              pFundToLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
                                                                           accountNum, 
                                                                           ruleType, 
                                                                           pFundToLmtOverride, 
                                                                           idDataGroup) <= WARNING && 
                              pFundToLmtOverride)
                           {
                              // disable fields
                              DString stopFlag;
                              pFundToLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
                              stopFlag.strip().upperCase();

                              bReadOnlyBaseOnRuleType = stopFlag == I_("Y");
                           }
                        }

                        ++iter3;
                     }
                  }
               }

               ++iter2;
            }
         }
      }
   }
   else
   {
      FundLmtOverrideList *pFundLmtOverrideList = NULL;

      if(!fundCode.strip().upperCase().empty() && !classCode.strip().upperCase().empty())
      {
         getFundLmtOverrideList(pFundLmtOverrideList,
                              strTransType,
                              fundCode,
                              classCode,
                              idDataGroup);

         FundLmtOverride *pFundLmtOverride = NULL;
         if ( pFundLmtOverrideList != NULL &&
              pFundLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
                                                         accountNum, 
                                                         ruleType, 
                                                         pFundLmtOverride, 
                                                         idDataGroup) <= WARNING && 
            pFundLmtOverride)
         {
            // disable fields
            DString stopFlag;
            pFundLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
            stopFlag.strip().upperCase();

            bReadOnlyBaseOnRuleType = stopFlag == I_("Y");
         }
      }
      else
      {
         SysAllocationList* pSysAllocationList = NULL;
         if( getSysAllocationList(pSysAllocationList) && pSysAllocationList )
         {
            SysAllocation *pSysAllocation = NULL;

            BFObjIter iter2(*pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
            DString dstrFundCodeB, dstrClassCodeB, dstrKey;
            while( !iter2.end() )
            {
               iter2.getObject()->getField ( ifds::FundCode, dstrFundCodeB,  idDataGroup, false );
               iter2.getObject()->getField ( ifds::ClassCode, dstrClassCodeB,  idDataGroup, false );

               getFundLmtOverrideList(pFundLmtOverrideList,
                                      strTransType,
                                      dstrFundCodeB,
                                      dstrClassCodeB,
                                      idDataGroup);

               FundLmtOverride *pFundLmtOverride = NULL;
               if ( pFundLmtOverrideList != NULL &&
                    pFundLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
                                                             accountNum, 
                                                             ruleType, 
                                                             pFundLmtOverride, 
                                                             idDataGroup) <= WARNING && 
                    pFundLmtOverride)
               {
                  // disable fields
                  DString stopFlag;
                  pFundLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
                  stopFlag.strip().upperCase();

                  bReadOnlyBaseOnRuleType = stopFlag == I_("Y");
               }

               ++iter2;
            }
         }
      }
   
      if(strTransType == PAC)
      {
         DString payType;
         getField( ifds::PayType, payType, idDataGroup, false );

         if( payType == EFT_PAY_TYPE )
         {
            SystematicList* pSystematicList = dynamic_cast <SystematicList*> (getParent());
            MFAccount* pMFAccount = pSystematicList->getMFAccount();
            if(_pMFAccount)
            {
               DString commitmentStatus;
               pMFAccount->getField(ifds::CommitmentStatus, commitmentStatus, idDataGroup, false);
               if (commitmentStatus == I_("01") || commitmentStatus == I_("02") || commitmentStatus == I_("03"))
               {
                  bReadOnlyBaseOnRuleType = true;
                  bDisableStopDate =  true;
               }
            }
         }
      }
   }
   return bReadOnlyBaseOnRuleType;
}

//******************************************************************************
SEVERITY Systematic::payTypeRelatedChanges( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("payTypeRelatedChanges"));
   //P0186486_FN15_The Source of Funds
   DString sourceOfFundApp;

   getWorkSession().getOption(ifds::SourceOfFundApp, sourceOfFundApp, idDataGroup, false);
   sourceOfFundApp.strip().upperCase();

   if(sourceOfFundApp == I_("Y")) 
   {
      DString dstrPayType, dstrTransType;
      
      getField ( ifds::PayType, dstrPayType, idDataGroup );
      getField( ifds::TransType, dstrTransType, idDataGroup, false);
      dstrPayType.strip().upperCase();
      dstrTransType.strip().upperCase();
   
      
      if(dstrTransType == SWP && dstrPayType == I_("X"))
      {
         DString srcOfFunds_IA_SWP_List; 
         getWorkSession().getOption(ifds::SrcOfFunds_IA_SWP, srcOfFunds_IA_SWP_List, idDataGroup, false);
         srcOfFunds_IA_SWP_List.strip().upperCase();
         if(!srcOfFunds_IA_SWP_List.empty())
         {
            replaceSubstitutionList(srcOfFunds_IA_SWP_List,
               ifds::SrcOfFunds_IA, 
               ifds::SrcOfFund, idDataGroup);
         }
         
      }

      DString dstrAllSubSt;
      BFProperties* pProperties = getFieldProperties(ifds::SrcOfFund, idDataGroup);
      pProperties->getAllSubstituteValues(dstrAllSubSt);
      dstrAllSubSt = I_("= ;") + dstrAllSubSt;

      setFieldAllSubstituteValues(ifds::SrcOfFund, idDataGroup, dstrAllSubSt);
   }

	bool bEventReceiptDateTimeAppl   = bIsEventReceiptDateTimeAppl(idDataGroup);
	if( ! bEventReceiptDateTimeAppl && isNew() )//Do not reset the exisiting PAC with any paytype chnages
	{
	setFieldNoValidate(ifds::EventReceiptDate,NULL_STRING,idDataGroup);
	setFieldNoValidate(ifds::EventReceiptTime,NULL_STRING,idDataGroup);
	setFieldValid(ifds::EventReceiptDate,idDataGroup,false);
	setFieldValid(ifds::EventReceiptTime,idDataGroup,false);
	}
	setFieldReadOnly(ifds::EventReceiptDate,idDataGroup, !bEventReceiptDateTimeAppl);
													//|| dstrVerifyStat == VERIFIED );//no apply related changes
	setFieldReadOnly(ifds::EventReceiptTime,idDataGroup, !bEventReceiptDateTimeAppl); 
													//|| dstrVerifyStat == VERIFIED );

   return GETCURRENTHIGHESTSEVERITY(); 
}

//****************************************************
void Systematic::ValidateSourceOfBankAcct(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateSourceOfBankAcct" ) );

   //P0186486_FN15_The Source of Funds
   DString sourceOfBankAcct;
   getField(ifds::SourceOfBankAcct, sourceOfBankAcct, idDataGroup, false); 
   
   DString srcOfFund;
   getField(ifds::SrcOfFund, srcOfFund, idDataGroup, false); 
   srcOfFund.stripAll().upperCase();

   if(!srcOfFund.empty() &&
      sourceOfBankAcct.empty() && 
      getWorkSession ().isSrcOfFundRequired(srcOfFund, idDataGroup))
   {
      getErrMsg (IFASTERR::REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
         CND::ERR_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
         CND::WARN_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
         idDataGroup);
   }
   
}
//******************************************************************************
void Systematic::loadRDRAdviceSubstList(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadRDRAdviceSubstList" ) );
   
   DString RDRAdviceSubstList;
   BFProperties *pBFProperties = 
      getFieldProperties (ifds::RDRAdvice, idDataGroup);

   assert (pBFProperties);
   if (pBFProperties)
   {
      pBFProperties->getAllSubstituteValues (RDRAdviceSubstList);
	  RDRAdviceSubstList = removeItemFromSubtList ( RDRAdviceSubstList, I_("00"));
   }
   setFieldAllSubstituteValues (ifds::RDRAdvice, idDataGroup, RDRAdviceSubstList);  
}
//******************************************************************************
DString Systematic::getRDRAdviceFlag(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRDRAdviceFlag" ) );
   
   DString dstrRDRAdviceFlag = NULL_STRING,
	       dstrRDRApplic	 = NULL_STRING,
		   dstrRDRDefault    = NULL_STRING;

   DString fundCode, classCode;
   getField (ifds::FundCode, fundCode, idDataGroup, false);
   getField (ifds::ClassCode, classCode, idDataGroup, false);
   
   if (!fundCode.empty() && !classCode.empty())
   {
      DString tradeDate, broker, branch, slsrep,accountNum, transType,amount, validationType = I_("1") ;

	  getField (ifds::AccountNum, accountNum, idDataGroup, false);
	  getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
	  getField (ifds::TransType, transType, idDataGroup, false);

	  MFAccount *pMFAccount=NULL;
	  getWorkSession().getMFAccount( idDataGroup, accountNum, pMFAccount );
	  if ( pMFAccount )
      {
		pMFAccount->getField ( ifds::BrokerCode, broker, idDataGroup );
		pMFAccount->getField ( ifds::BranchCode, branch, idDataGroup );
		pMFAccount->getField ( ifds::Slsrep, slsrep, idDataGroup );
	  }
	  RDRAdvice rdrAdvice(*this);
	  SEVERITY sevRtn = rdrAdvice.init(accountNum, 
										fundCode, 
										classCode, 
										transType, 
										tradeDate, 
										broker, 
										branch,
										slsrep);
	  if( sevRtn <= WARNING )
	  {
		  rdrAdvice.getField(ifds::RDRApplic, dstrRDRApplic, idDataGroup, false);
		  rdrAdvice.getField(ifds::RDRDefault,dstrRDRDefault,idDataGroup, false);
	  }
	  if( dstrRDRApplic == I_("00") || dstrRDRApplic == I_("01") )
	  {
		  dstrRDRAdviceFlag = I_("00"); // N/A
	  }
	  else if ( dstrRDRApplic == I_("02") && dstrRDRDefault == I_("02"))
	  {
		  dstrRDRAdviceFlag = I_("02"); // Provided
	  }
	  else if ( dstrRDRApplic == I_("02") && dstrRDRDefault == I_("01"))
	  {
		  dstrRDRAdviceFlag = I_("01"); //Not provided
	  }
   }
   return dstrRDRAdviceFlag;   
}
//******************************************************************************
SEVERITY Systematic::RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("RDRAdviceRelatedChanges"));
   
   DString dstrRDREnv = NULL_STRING;
		
   getWorkSession().getOption ( ifds::RDREnv,dstrRDREnv,idDataGroup,false);
   if( dstrRDREnv == I_("Y") )
   {
	   _strRDRAdviceFlag = getRDRAdviceFlag(idDataGroup);
	   if( !_strRDRAdviceFlag.empty())
	   {
		   setFieldNoValidate (ifds::RDRAdvice, _strRDRAdviceFlag, idDataGroup, false); 
		   setFieldReadOnly (ifds::RDRAdvice, idDataGroup,_strRDRAdviceFlag == I_("00"));
		   if( _strRDRAdviceFlag != I_("00") )
		   {
			   loadRDRAdviceSubstList(idDataGroup);	
		   }	   
	   }
   }   
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Systematic::validateRDRAdviceForAmt (const DString& dstrAmount, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRDRAdviceForAmt"));
    
   DString dstrOldAmount;
   getField (ifds::Amount, dstrOldAmount, BF::HOST, false);

   BigDecimal bdOldAmt(dstrOldAmount);
   BigDecimal bdNewAmt(dstrAmount);

   if( bdNewAmt > bdOldAmt )
   {
	   DString dstrRDRAdvice = getRDRAdviceFlag(idDataGroup);
	   if( dstrRDRAdvice == RDR_ADVICE_PROVIDED )
	   {
		   ADDCONDITIONFROMFILE(CND::ERR_INCREMENTED_AMT_IS_RDR_ADVICED);
	   }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
 Input: idDataGroup
 OutPut:None
 Return:bool
 Functionality:returns true if EventReceiptDate & EventReciptTime is Applicable. 
 ******************************************************************************/
bool Systematic::bIsEventReceiptDateTimeAppl(const BFDataGroupId &idDataGroup)
{
   DString dstrTransType,dstrUCITSEnv;
   bool bEventReceiptDateTimeAppl   = false;
   getWorkSession().getOption(ifds::UCITFlag, dstrUCITSEnv, idDataGroup, false );
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();  
   bEventReceiptDateTimeAppl =  (( dstrUCITSEnv == YES) && 
	                            (dstrTransType == PAC || dstrTransType == SWP ||
								 dstrTransType == AUTO_TRFER));
					           
   return   bEventReceiptDateTimeAppl;
}
/******************************************************************************
Input:Field ID ,DataGroupID
OutPut:
Return:Severity
Functionality:Append a blank value to sub list
******************************************************************************/
SEVERITY Systematic::addBlankToSubSet(const BFFieldId &idField ,const BFDataGroupId &idDataGroup, bool dstrUseNotApplicableAsDesc /*= false */ )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("addBlankToSubSet"));

   DString  dstrCurrSubList,dstrSubList;
   BFProperties *pBFProperties = getFieldProperties (idField, idDataGroup); 
   assert (pBFProperties);
   if (pBFProperties) 
   {
    pBFProperties->getAllSubstituteValues (dstrCurrSubList);
    DString dstrNotApplicableLangDesc;
    BFProperties *pBFPropertiesNotApplicable = getFieldProperties (ifds::NotApplicable, idDataGroup);
    pBFPropertiesNotApplicable->getDefaultValue(dstrNotApplicableLangDesc);
    pBFPropertiesNotApplicable->formatValue( ifds::NotApplicable,dstrNotApplicableLangDesc, true );
    dstrNotApplicableLangDesc = dstrUseNotApplicableAsDesc ? ( I_(" =") + dstrNotApplicableLangDesc + I_(";")): BLANK_SUBSTITUTION_VALUE;
    
    I_CHAR *temp = const_cast<I_CHAR*> (dstrCurrSubList.c_str ());
    bool blankNotAdded = true;
    do
    {
      DString dstrCode, dstrDescr;
      temp = parseIdiString (temp, dstrCode, dstrDescr );
      //if alreday in do not add again..
      if (dstrCode == I_(" "))
       {
           blankNotAdded = false;
           break;
       }
    }while (temp && temp != NULL_STRING && *temp);
    if(blankNotAdded)
    {
        dstrSubList = dstrNotApplicableLangDesc  + dstrCurrSubList;
        pBFProperties->setAllSubstituteValues( dstrSubList ); 
    }   
   }      
   return GETCURRENTHIGHESTSEVERITY();
}


/******************************************************************************
Input:Field ID ,DataGroupID
OutPut:Empty
Return:Severity
Functionality:Default all the field values with the configurtion matrix
******************************************************************************/
void Systematic::populateFieldsWithDefaultValues(const BFDataGroupId &idDataGroup, const long &lMod)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("populateFieldsWithDefaultValues"));

   DefaultSysConfigDetailList* pDefaultSysConfigDetailList = NULL;
   getMgmtCo().getDefaultSysConfigDetailList(pDefaultSysConfigDetailList); 
   if(pDefaultSysConfigDetailList)
   {
	 //BFFieldId idField = ifds::NullFieldId;
	 bool bformattedReturn = false ; 
	 DString dstrDefValue; 
	 for (int i = 0; i<_numFieldDefaultRule; i++)
	 {
	    DString dstrKeyField1, dstrKeyField2, dstrKeyField3, dstrKeyField4, dstrKeyField5;
		//get the default from the matrix and set it
		getField(m_FieldDefaultRule[i]._KeyFld1, dstrKeyField1, idDataGroup, false);
		getField(m_FieldDefaultRule[i]._KeyFld2, dstrKeyField2, idDataGroup, false);
		getField(m_FieldDefaultRule[i]._KeyFld3, dstrKeyField3, idDataGroup, false);
		getField(m_FieldDefaultRule[i]._KeyFld4, dstrKeyField4, idDataGroup, false);
		getField(m_FieldDefaultRule[i]._KeyFld5, dstrKeyField5, idDataGroup, false);

		if( m_FieldDefaultRule[i].getModAppl(lMod))
		{
			pDefaultSysConfigDetailList->getFieldDefaultValue( m_FieldDefaultRule[i]._FieldID , idDataGroup, dstrDefValue, bformattedReturn,
															   dstrKeyField1, dstrKeyField2, dstrKeyField3, dstrKeyField4, dstrKeyField5);
		    setFieldNoValidate(m_FieldDefaultRule[i]._FieldID, dstrDefValue, idDataGroup, bformattedReturn, false, true);
			
		}
	 }
   }
}
/******************************************************************************
Input:Field ID ,DataGroupID
OutPut:Empty
Return:Severity
Functionality:Default the field values with the configurtion matrix
******************************************************************************/
void Systematic::setFieldWithDefaultValue(const BFFieldId &idField,const BFDataGroupId &idDataGroup )
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFieldWithDefaultValue"));
   bool bformattedReturn = false ; 
   DString dstrDefValue;
   DefaultSysConfigDetailList* pDefaultSysConfigDetailList = NULL;
   getMgmtCo().getDefaultSysConfigDetailList(pDefaultSysConfigDetailList); 
   if(pDefaultSysConfigDetailList)
   {
	 for (int i = 0; i<_numFieldDefaultRule; i++)
	 {
		 //get the default from the matrix and set it
		 if(m_FieldDefaultRule[i]._FieldID == idField )
		 {
			DString dstrKeyField1, dstrKeyField2, dstrKeyField3, dstrKeyField4, dstrKeyField5;
			getField(m_FieldDefaultRule[i]._KeyFld1, dstrKeyField1, idDataGroup, false);
			getField(m_FieldDefaultRule[i]._KeyFld2, dstrKeyField2, idDataGroup, false);
			getField(m_FieldDefaultRule[i]._KeyFld3, dstrKeyField3, idDataGroup, false);
			getField(m_FieldDefaultRule[i]._KeyFld4, dstrKeyField4, idDataGroup, false);
			getField(m_FieldDefaultRule[i]._KeyFld5, dstrKeyField5, idDataGroup, false);

			pDefaultSysConfigDetailList->getFieldDefaultValue( m_FieldDefaultRule[i]._FieldID , idDataGroup, dstrDefValue, bformattedReturn,
															   dstrKeyField1, dstrKeyField2, dstrKeyField3, dstrKeyField4, dstrKeyField5);
		    setFieldNoValidate(m_FieldDefaultRule[i]._FieldID, dstrDefValue, idDataGroup, bformattedReturn, false, true);
			break;
		}
	 }
   }	 
}

//****************************************************************************** 
bool Systematic::hasNonAMSFunds(const BFDataGroupId& idDataGroup)
{
   bool retVal = false;
   DString dstrFundCode;
   DString dstrClassCode;
   FundDetailList *pFundDetailList = NULL;

	if ( NULL != _pSysAllocationList &&
         getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList)
	{               
		BFObjIter iter( *_pSysAllocationList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
		iter.begin();

		if (!retVal && !iter.end())
		{
			BFAbstractCBO *pBFCBO = iter.getObject();
			if ( NULL != pBFCBO )
			{
				pBFCBO->getField( ifds::FundCode, dstrFundCode, idDataGroup, false );
				pBFCBO->getField( ifds::ClassCode, dstrClassCode, idDataGroup, false );
		      dstrFundCode.upperCase().strip();
            dstrClassCode.upperCase().strip();
		      if(!getWorkSession().isAMSFundClass(dstrFundCode, dstrClassCode, idDataGroup))
		      {
			      retVal = true;			
		      }
            ++iter;
			}
		}
	}
	return retVal;
}

//****************************************************************************** 
SEVERITY Systematic::getSEGFundValidationRules (SEGFundValidationRules  *&pSEGFundValidationRules,
                                                const DString& fundCode, 
                                                const DString& classCode, 
                                                const DString& acctNum,
                                                const DString& effDate,
                                                const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getSEGFundValidationRules"));

   DString strRuleObjKey = I_("RuleObj_");
   strRuleObjKey += fundCode;
   strRuleObjKey += I_("_");
   strRuleObjKey += classCode;
   strRuleObjKey += I_("_");

   DString dstrTransType,
      dstrEventTransType = NULL_STRING;
   getField (ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();

   if (dstrTransType == PAC)
      dstrEventTransType = I_("06");
   else if ( dstrTransType == AUTO_TRFER )
      dstrEventTransType = I_("07");
   else if (dstrTransType == SWP)
      dstrEventTransType = I_("12");

   strRuleObjKey += dstrEventTransType;

   SEGFundValidationRules* pRuleObj = 
         dynamic_cast<SEGFundValidationRules*> (getObject( strRuleObjKey, idDataGroup));

   if (!pRuleObj)
   {
      pRuleObj = new SEGFundValidationRules(*this);
      if ( pRuleObj->init(acctNum,
                          fundCode,
                          classCode,
                          dstrEventTransType,
                          NULL_STRING,
                          NULL_STRING,
                          effDate) <= WARNING )
      {
         setObject ( pRuleObj, strRuleObjKey,OBJ_ACTIVITY_NONE, idDataGroup);
         pSEGFundValidationRules = pRuleObj;
      }
      else
      {
         delete pRuleObj;
         pRuleObj = NULL;
      }
   }
   else
   {
      pSEGFundValidationRules = pRuleObj;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
bool Systematic::allSWPCustomPayoutFndCls(const BFDataGroupId& idDataGroup)
{
    bool ret = false;
    DString dstrTransType, dstrFundCode, dstrClassCode;
    FundDetail *pFundDetail = NULL;

    getField(ifds::TransType, dstrTransType, idDataGroup, false);
    getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
    getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

    if (dstrTransType == SWP)
    {
        if (!dstrFundCode.empty() && !dstrClassCode.empty()) //Single
        {
            ret = getWorkSession().getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail &&
                  pFundDetail->isCustomPayoutFund(idDataGroup);
        }
        else if (dstrFundCode.empty() && dstrClassCode.empty() && _pSysAllocationList)
        {
            BFObjIter iterSysAlloc(*_pSysAllocationList,idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
            DString iterFund, iterClass;

            if (!iterSysAlloc.end()) //Allocation
            {
                iterSysAlloc.getObject()->getField(ifds::FundCode, iterFund, idDataGroup);
                iterSysAlloc.getObject()->getField(ifds::ClassCode, iterClass, idDataGroup);
            }

            if (!iterFund.empty() && !iterClass.empty() &&
                getWorkSession().getFundDetail(iterFund, iterClass, idDataGroup, pFundDetail) && pFundDetail &&
                pFundDetail->isCustomPayoutFund(idDataGroup))
            {
                ret = true;
            }
        }
    }

    return ret;
}

//****************************************************************************** 
bool Systematic::isSWPCustomPayoutPlan(const BFDataGroupId& idDataGroup)
{
    DString dstrAmtTypeOvrd;
    getField(ifds::AmtTypeOvrd, dstrAmtTypeOvrd, idDataGroup);

    return dstrAmtTypeOvrd.upperCase() == AMT_TYPE::CUSTOM;
}

//****************************************************************************** 
bool Systematic::isSWPPortfolioPayoutPlan(const BFDataGroupId& idDataGroup)
{
    DString dstrAmtTypeOvrd;
    getField(ifds::AmtTypeOvrd, dstrAmtTypeOvrd, idDataGroup);

    return dstrAmtTypeOvrd.upperCase() == AMT_TYPE::PORTFOLIO;
}

//****************************************************************************** 
void Systematic::getValidListAmountTypeByFund(const DString& fundCode, 
                                              const DString& classCode, 
                                              DString &listAmtType,
                                              const BFDataGroupId& idDataGroup)
{
   SEGFundValidationRules  *pSEGFundValidationRules = NULL;

   DString dstrAccountNum,dstrCurrBusDate;
   getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
   dstrAccountNum.strip().upperCase();

   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
   getSEGFundValidationRules(pSEGFundValidationRules,fundCode,classCode,dstrAccountNum,dstrCurrBusDate,idDataGroup);

   if (pSEGFundValidationRules)
   {
      BFObjIter itSEGFundValidationRules(*pSEGFundValidationRules, idDataGroup);

      itSEGFundValidationRules.begin();

      while(!itSEGFundValidationRules.end())
      {
         DString dstrRuleCode;

         itSEGFundValidationRules.getObject()->getField(ifds::RuleCode, dstrRuleCode, idDataGroup, false);

         if (dstrRuleCode == I_("47"))
         {
            itSEGFundValidationRules.getObject()->getField(ifds::RuleValue, listAmtType, idDataGroup, false);
            listAmtType.strip().upperCase();
            break;
         }
         ++itSEGFundValidationRules;
      }
   }
}

/******************************************************************************
 Input: idataGroup, from to trade side, Regulation for specfic case
 OutPut:None
 Return:None
 Functionality:Triggers a call to the 469 view to do regulatory validations
                and display the errors.
 ******************************************************************************/
SEVERITY Systematic::doRegulatoryValidations(const BFDataGroupId &idDataGroup, const DString& dstrSide , const DString& dstrRegulation /* = NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doRegulatoryValidations" ) );
     
   DString  dstrTradeDate, dstrTransType, dstrAcctNum , dstrFund ;
   
   if( FROM_TO::FROM == dstrSide )
   {
     getField(ifds::AccountNum, dstrAcctNum, idDataGroup, false);
     getField(ifds::FundCode, dstrFund, idDataGroup, false);
   }
   else if( FROM_TO::TO == dstrSide )
   {
     getField(ifds::AccountTo, dstrAcctNum, idDataGroup, false);
     getField(ifds::FundToCode, dstrFund, idDataGroup, false);
   }
   getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup, false);
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
  
   if( dstrTransType.empty() || dstrTradeDate.empty () || dstrAcctNum.empty() || dstrFund.empty () )
       return(GETCURRENTHIGHESTSEVERITY());

   RegulatoryValidationErrorList regulatoryValidationErrorList(*this);  
   
   regulatoryValidationErrorList.doRegulatoryValidations( dstrAcctNum, dstrFund, dstrTradeDate, idDataGroup, dstrTransType, dstrRegulation ); 
   
   return(GETCURRENTHIGHESTSEVERITY());
 }
/******************************************************************************
 Input: idataGroup, from to trade side
 OutPut:None
 Return:None
 Functionality:does special handeling for SIF Regulatory validations
               1. Validation of a regulation during money-out(SWP) is not trival.SIF needs it as per BRD.
               2. Validation is only for new setup and not for modification
 ******************************************************************************/
SEVERITY Systematic::doSIFRegulationSpecificValidations(const BFDataGroupId &idDataGroup, const DString& dstrSide )
{
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doSIFRegulationSpecificValidations" ) );
   
   //check if the 
   TranslationTable* pTranslationTable = NULL;
   DString dstrCodeList;
   if (getMgmtCo ().getTranslationTable (REGULATORY, pTranslationTable) <= WARNING && pTranslationTable)
       pTranslationTable->getCodeList(dstrCodeList);  
   
   if(!isCodeInList(REGULATION::SIF, dstrCodeList) || !isNew() )//Modiifcation to setup , is excluded from SIF validation. 
       return(GETCURRENTHIGHESTSEVERITY());

   doRegulatoryValidations(idDataGroup, dstrSide, REGULATION::SIF);    
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************** 
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Systematic.cpp-arc  $
 * 
 *    Rev 1.368   Jul 31 2012 16:48:30   wp040027
 * Sync up: IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
 * 
 *    Rev 1.367   Jul 30 2012 09:07:50   wp040027
 * P0198518 - RDR Functionality - Review Comment incorporated
 * 
 *    Rev 1.366   Jul 26 2012 10:43:38   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.365   Jul 12 2012 18:36:22   wp040133
 *  IN#-3013839
 *  PET: P0187485 
 *  Can place a PAC on a CPF account when “PAC available = no”
 * 
 *    Rev 1.364   Jul 09 2012 09:49:40   if991250
 * remove EWA
 * 
 *    Rev 1.363   Jun 28 2012 11:02:50   wp040027
 * IN 2998996 - CPF - MFS- Split Commission
 * 
 *    Rev 1.362   Jun 27 2012 12:31:24   if991250
 * IN2981340 : RRIF
 * 
 *    Rev 1.361   Jun 04 2012 09:29:36   if991250
 * CPF: PAC
 * 
 *    Rev 1.360   May 28 2012 10:38:36   if991250
 * CPF - Account Entity + Systematics
 * 
 *    Rev 1.359   May 23 2012 17:51:26   dchatcha
 * IN#2911721 - AutoTransfer on DSK_Discard then Resubmit the trade, an error message displays
 * 
 *    Rev 1.358   May 18 2012 10:49:10   if991250
 * CPF - SWP has  SWP Supress pay type
 * 
 *    Rev 1.357   May 17 2012 18:22:40   if991250
 * CPF: - verification check for ModUser+UserName
 * 
 *    Rev 1.356   May 16 2012 10:12:42   jankovii
 * P0186481FN07-GWA LWA Payment Options for SWP RRIF
 * 
 *    Rev 1.355   May 14 2012 15:43:12   jankovii
 * P0186481FN07-GWA LWA Payment Options for SWP RRIF.
 * 
 *    Rev 1.354   May 14 2012 11:40:08   if991250
 * CPF- PAC - currency filtering
 * 
 *    Rev 1.353   May 13 2012 16:57:10   if991250
 * CPF - PAC
 * 
 *    Rev 1.352   May 11 2012 14:04:30   jankovii
 * P0186481 FN07 - GWA LWA Payment Options for SWP RRIF
 * 
 *    Rev 1.351   May 04 2012 11:16:38   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.350   Apr 30 2012 15:41:48   popescu
 * 2902002 - P0186480FN02 - Diploma DSK Validation
 * 
 *    Rev 1.349   Apr 27 2012 18:02:02   wp040039
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.348   Apr 20 2012 03:58:18   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.347   Apr 19 2012 07:29:54   panatcha
 * IN2923318 -  PAC vailidation
 * 
 *    Rev 1.346   Apr 02 2012 06:34:34   panatcha
 * IN2844236 - Disable set up bankruptcy fund
 * 
 *    Rev 1.345   Mar 28 2012 08:22:46   panatcha
 * IN2844236 - Disable set up bankruptcy fund
 * 
 *    Rev 1.344   Mar 23 2012 10:44:58   if991250
 * IN  2885402 - PAC-EFT Systematic readonly for active commitments, Added Insured and Policy number
 * 
 *    Rev 1.343   Feb 24 2012 04:07:12   panatcha
 * IN2844236 - Cannot put a stop date on PAC/SWP/Automatic Transfer
 * 
 *    Rev 1.342   Jan 26 2012 14:34:22   if991250
 * P0186477- GIA trading Screen Issue - Seg fund validation needs to be executed only if the fund category is segregated ('S').
 * 
 *    Rev 1.341   Jan 17 2012 18:08:26   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer, back-end take stop flag to be considered. another crash!.
 * 
 *    Rev 1.340   Jan 17 2012 16:45:16   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer, back-end take stop flag to be considered. new issues found.
 * 
 *    Rev 1.339   Jan 16 2012 16:24:00   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer, back-end take stop flag to be considered.
 * 
 *    Rev 1.338   Jan 13 2012 12:56:06   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer, fix for new entry of allocation for both of systematic and automatic transfer.
 * 
 *    Rev 1.337   Jan 11 2012 15:23:44   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer
 * 
 *    Rev 1.336   Oct 05 2011 05:45:08   wutipong
 * IN2043788 - Error at setting up systematic during NASU.
 * 
 *    Rev 1.335   Feb 27 2011 21:02:32   panatcha
 * ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
 * 
 *    Rev 1.334   Dec 21 2010 02:38:30   wichian
 * IN#2331866 - Add logic to prevent domestic user from enter systematic SWP and allocated systematic SWP in UNITS
 * 
 *    Rev 1.333   Nov 24 2010 12:01:32   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.332   Sep 27 2010 06:57:02   kitticha
 * IN#2036266 - Can not apply Acquisition Fee at 2% when saving the Auto Transfer.
 * 
 *    Rev 1.331   Sep 02 2010 11:38:06   wutipong
 * R11.2 - IN2011909 - SWP Payment does not match System Allocation
 * 
 *    Rev 1.330   Jul 05 2010 05:41:38   wichian
 * IN#2096640 - Weekly PAC only ran weekly for the Month of March & next processed date is 2011
 * 
 *    Rev 1.329   Mar 31 2010 12:06:06   wutipong
 * IN2052955 - Cloning PAC/SWPs to change banking information updates old record
 * 
 *    Rev 1.328   Nov 19 2009 22:28:30   wutipong
 * IN1845806 - more modification based on Zijian's comments.
 * 
 *    Rev 1.327   Nov 06 2009 23:43:34   wutipong
 * IN1845806 - Unable to set up a  SWP - PIN - (Ifast Desktop)
 * 
 *    Rev 1.326   05 Aug 2009 16:37:10   sibuhatm
 * IN1782392 - VT22418 Unable to Set up Auto Switch with Switch Fee using the Acquisition Fee.
 * 
 * The incident was raised for AcqFee in Systematic screen which is resetting when we change any fund or class values. But that is the logic of the screen.
 * 
 * There was an another  issue in error message displaying tool tip.
 * It was displayed BROKER, FUND and CLASS but not the actua; value.
 * 
 *    Rev 1.325   Jun 15 2009 03:06:42   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.324   Jun 09 2009 05:49:40   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.323   Feb 20 2009 05:26:22   dchatcha
 * IN 1525186 - Unable to setup F110 PAC/SWP from dsk for dealer 9190 . (Check in for Noom)
 * 
 *    Rev 1.322   Feb 04 2009 14:35:44   wongsakw
 * IN1525186 Unable to setup F110 PAC/SWP for F110 -- correct the compile error.
 * 
 *    Rev 1.321   Feb 03 2009 18:42:12   wongsakw
 * IN1525186 Unable to setup F110 PAC/SWP for F110
 * 
 *    Rev 1.320   Nov 06 2008 02:05:42   daechach
 * PET5517 FN71 Unclaimed Property Phase 2
 * 
 *    Rev 1.319   08 Oct 2008 14:54:56   kovacsro
 * PET142007  FN01 TFSA - added date validation for money in transaction
 * 
 *    Rev 1.318   07 Oct 2008 11:08:36   kovacsro
 * PET142007  FN01 TFSA - sending AccountTo for AT rather than FromAccountNum
 * 
 *    Rev 1.317   06 Oct 2008 13:19:56   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.316   01 Oct 2008 12:03:04   popescu
 * Check in for incident  1419539
 * 
 *    Rev 1.315   12 Sep 2008 15:41:10   kovacsro
 * PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
 * 
 *    Rev 1.314   Jun 04 2008 14:34:04   jankovii
 * IN 1260513 - Issue with setting up PAC EFT in an account with AMS-PIN-qaslot19
 * 
 *    Rev 1.313   15 Apr 2008 12:10:04   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.312   09 Jan 2008 14:32:24   popescu
 * Stopping a PAC should not check if the fund is softcapped. Only re-activating it should have this edit.
 * 
 *    Rev 1.311   21 Aug 2007 10:29:46   popescu
 * Incident 961552 - the soft cap check should occur is user re-activates a PAC
 * 
 *    Rev 1.310   24 Jul 2007 20:13:28   popescu
 * GAP 20 -22 AIM
 * 
 *    Rev 1.309   Oct 05 2006 17:31:02   AGUILAAM
 * IN 721266 - new field ToAcctTaxType to get applicable fees for transfers
 * 
 *    Rev 1.308   Sep 06 2006 13:24:14   popescu
 * Incident# 702374 - clear amount field - 
 * 
 *    Rev 1.307   Aug 22 2006 11:52:04   popescu
 * Incident# 591211 - set amount to read only if the AT is read from the back-end
 * 
 *    Rev 1.306   Jul 11 2006 17:52:00   ZHANGCEL
 * Incident #591211 -- Set field "Amount" is readonly when AmtType is one of the new types
 * 
 *    Rev 1.305   Jun 02 2006 16:11:46   ZHANGCEL
 * Incident #591211 -- Ensure Auto-Transfer has the same AmountType available as regular transfer
 * 
 *    Rev 1.304   May 25 2006 09:40:42   jankovii
 * PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
 * 
 *    Rev 1.303   Apr 26 2006 13:20:12   popescu
 * Incident# 588435 - backed out code for Incident 521426 - dsk will display the warning message as before
 * 
 *    Rev 1.302   Feb 14 2006 14:08:04   porteanm
 * Incident 543959 - Two lines of instructions (Pay Reason).
 * 
 *    Rev 1.301   Feb 13 2006 14:40:12   AGUILAAM
 * IN 543265 - get transfer fee for fundto/classto
 * 
 *    Rev 1.300   Jan 18 2006 15:05:52   ZHANGCEL
 * Incident #521426 -- Remove the warning ERR_WARN_NEXT_PROC_DATE_AFTER_STOP_DATE since it is no needed
 * 
 *    Rev 1.299   Dec 21 2005 10:35:00   porteanm
 * Incident 496820 - Allocations should not be updated automatically for an existing PAC/SWP when Effective Date is changed.
 * 
 *    Rev 1.298   Dec 20 2005 13:32:36   AGUILAAM
 * IN 465769 - fixed validation on fee and feepercent to issue appropriate errors, if necessary.
 * 
 *    Rev 1.297   Dec 16 2005 14:26:04   popescu
 * Incident# 496587 - fees should not be validated/apply related changes if funds associated with the PAC/SWPs are BEL
 *
 *    Rev 1.296   Dec 14 2005 11:15:10   popescu
 * Incident #489826 -- fixed problem for an "irrelevant error message" after using Reset button - extra checks
 * 
 *    Rev 1.295   Dec 14 2005 10:44:00   zhengcon
 * Incident #489826 -- fixed problem for an "irrelevant error message" after using Reset button
 * 
 *    Rev 1.294   Oct 31 2005 15:43:08   AGUILAAM
 * IN 418142 - subsequent fix; display error message with 2 decimals if flat fee, 4 decimals if percent/rate fee.
 * 
 *    Rev 1.293   Oct 04 2005 13:50:00   AGUILAAM
 * IN 418142 (R65) - If fee is defined by user as "flat" and default feetype is "percent", fee will be converted to amount or dollar value; display corresponding message right away
 * 
 *    Rev 1.292   Sep 29 2005 15:10:04   ZHANGCEL
 * PET1244 - FN01 -- Seg Fund Evolution enhancement
 * 
 *    Rev 1.291   Sep 28 2005 16:23:08   ZHANGCEL
 * PET1244 - FN01 - Seg Fund Evolution enhancement
 * 
 *    Rev 1.290   Sep 23 2005 18:26:00   ZHANGCEL
 * PET1244 FN01 -- Seg Func Evolution enhancement
 * 
 *    Rev 1.289   Sep 02 2005 16:23:12   porteanm
 * Incident 391174 - Fixed crash when a bad PAC has no allocation.
 * 
 *    Rev 1.288   Aug 29 2005 09:43:20   yingbaol
 * PET1242,FN07:Check in the right version.
 * 
 *    Rev 1.286   Jul 27 2005 18:42:44   AGUILAAM
 * IN 353952 - refine validations of Systematic records against broker/branch/rep effective/stop dates.
 * 
 *    Rev 1.285   Jul 11 2005 17:24:30   Fengyong
 * PET1250FN02 - European numeric enahncement - conditions
 * decimal format 
 * 
 *    Rev 1.284   Jun 24 2005 11:18:36   porteanm
 * Incident 299732 - Validate inactive broker/branch/rep only when in add or modify mode.
 * 
 *    Rev 1.283   May 17 2005 16:30:36   porteanm
 * Incident 295478 - Discard on Cancel does not work because of view error when user has no active batch
 * 
 *    Rev 1.282   May 17 2005 13:51:50   AGUILAAM
 * IN 299732: re-added v1.279 changes (fix for IN 266213) overwritten by v1.280
 * 
 *    Rev 1.281   May 17 2005 11:43:56   porteanm
 * Incident 295478 - Discard on Cancel does not work because of view error when user has no active batch
 * 
 *    Rev 1.280   May 16 2005 09:39:44   AGUILAAM
 * IN 299732 - inactive broker/branch/rep not allowed for systematics
 * 
 *    Rev 1.278   Apr 08 2005 16:56:10   aguilaam
 * IN 260178 - additional fix for auto transfer to prevent crash on update of effectivedate; original issue is to assign ifee properly - should not be assigned from total of split rates
 * 
 *    Rev 1.277   Apr 08 2005 15:39:46   aguilaam
 * IN 260178 - corrected assignment of fee for auto transfer
 * 
 *    Rev 1.276   Mar 17 2005 15:04:08   porteanm
 * Incident 262660 - PAC Eff Date validation for single fund and alloc.
 * 
 *    Rev 1.275   Feb 22 2005 14:01:04   porteanm
 * Incident 244225/WO 19920 - SWP - Change Escrow account validation not firing up.
 * 
 *    Rev 1.274   Jan 19 2005 17:12:30   Fengyong
 * PTS10036278 - default system pay type for generic controls
 * 
 *    Rev 1.273   Jan 04 2005 11:24:22   yingbaol
 * PTS10036915: implement display hide stingray control at dialog layor.
 * 
 *    Rev 1.272   Dec 16 2004 12:51:20   popescu
 * PTS 10036278, read the defaults for systematic pay type from generic controls
 * 
 *    Rev 1.271   Dec 16 2004 11:57:30   porteanm
 * PTS 10036915 - Corrected Provincial Tax description.
 * 
 *    Rev 1.270   Dec 08 2004 17:22:28   aguilaam
 * PET_910: clean-up for setfields
 * 
 *    Rev 1.269   Nov 29 2004 13:27:36   hernando
 * PET1117 - Tuning Project - Revised use of FundDetailList.
 * 
 *    Rev 1.267   Nov 18 2004 13:28:30   YINGBAOL
 * PET1117: Perfermance Tunning
 * 
 *    Rev 1.266   Nov 17 2004 15:02:20   PURDYECH
 * PET910 - .NET Conversion:  Fixed compiler warning messages
 * 
 *    Rev 1.265   Nov 14 2004 14:56:32   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.264   Nov 02 2004 09:32:56   AGUILAAM
 * PTS 10035298 - use owner's dofb for registered type of accounts, annuitant's dofb for non-registered and agebasedon 01
 * 
 *    Rev 1.263   Oct 28 2004 14:51:26   VADEANUM
 * PET 1010 FN02 CCB 1383 - WHTax for Registered Accts on SWPs - Warning message not shown when both taxes have No Override flag on; Changed description from Override Federal to Fed, Override Provincial to Prov.
 * 
 *    Rev 1.262   Oct 27 2004 10:35:38   VADEANUM
 * PET 1010 FN02 CCB 1383 - WHTax for Registered Accts on SWPs.
 * 
 *    Rev 1.261   Oct 25 2004 16:05:28   VADEANUM
 * PTS10034061 - Backed it out - will be delivered in 58.1 - send annuitant's dofbirth if non-registered account, else send owner's dofbirth
 * 
 *    Rev 1.260   Oct 18 2004 11:28:04   AGUILAAM
 * PTS10034061 : send annuitant's dofbirth if non-registered account, else send owner's dofbirth
 * 
 *    Rev 1.259   Sep 13 2004 16:57:52   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.258   Sep 13 2004 12:46:42   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.257   Sep 07 2004 15:07:44   VADEANUM
 * PET 1094 FN4 - Activest Bank File Processor.
 * 
 *    Rev 1.256   Aug 05 2004 13:47:08   YINGBAOL
 * PTS10031439:Skip validation for GrossOrNet if it is AT.
 * 
 *    Rev 1.255   Jul 08 2004 16:14:02   popescu
 * PTS 10032006, check the trade minimum amount for to side funds, for rollovers transaction type
 * 
 *    Rev 1.254   Jun 25 2004 19:05:22   popescu
 * PTS 10031525, Fund limitation overrides issue
 * 
 *    Rev 1.253   Jun 25 2004 16:38:36   popescu
 * PST 10031525, fund limitation override issues
 * 
 *    Rev 1.252   May 13 2004 10:45:52   AGUILAAM
 * PTS 10029479 - purchase/PAC on US funds not allowed for RRSP accounts, applies to both single-fund and allocated transactions
 * 
 *    Rev 1.251   May 11 2004 15:50:04   popescu
 * PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
 * 
 *    Rev 1.250   Apr 23 2004 18:15:42   WINNIE
 * Ticket 10021181 : Move the capped fund logic from compound date validation since update stopdate should not trigger capped fund logic. Only when modify effective date should the capped fund logic be trigger; Validate capped fund amount should only be applied to from fund for PAC and Saving Plan, applies to ToFund for Automatic Transfer
 * 
 *    Rev 1.249   Mar 17 2004 11:06:12   VADEANUM
 * PTS 10027933 - Error when deleting last PAC record.
 * 
 *    Rev 1.248   Feb 10 2004 16:00:12   YINGBAOL
 * 10021181:Validate Amount for Cap fund
 * 
 *    Rev 1.247   Feb 06 2004 16:41:28   YINGBAOL
 * PTS10026412:When field changes at systemetic level, allocation should be notified instead of call setField directly
 * 
 *    Rev 1.246   Nov 13 2003 14:44:32   HSUCHIN
 * PTS 10023860 - bug fix for Batch verification.
 * 
 *    Rev 1.245   Oct 03 2003 19:19:14   popescu
 * CIBC PET 809, FN13, removed references to BankSearch and BankList objects
 * 
 *    Rev 1.244   Sep 25 2003 16:51:28   HSUCHIN
 * PTS 10022211 - bug fix for systematic crash due to reference to a null pointer.
 * 
 *    Rev 1.243   Sep 23 2003 11:32:48   HSUCHIN
 * PTS 10022071 - bug fix with bank currency not being set when there is a default allocation.
 * 
 *    Rev 1.242   Sep 18 2003 09:28:40   HSUCHIN
 * sync up with 1.231.1.3
 * 
 *    Rev 1.241   Sep 15 2003 13:58:14   popescu
 * fix crash related to not finding a valid account number (account object) when placing a new AutomaticTransfer
 * 
 *    Rev 1.240   Sep 10 2003 10:41:16   HSUCHIN
 * bug fix with capped funds where the private fund master list was null on initialization of systematic with only one AT item.
 * 
 *    Rev 1.239   Sep 05 2003 17:21:14   HSUCHIN
 * bug fix where default allocations showed up as doubled due to datagroup issue with doinitwithdefaultvalues.
 * 
 *    Rev 1.238   Sep 04 2003 17:33:30   HSUCHIN
 * PTS 10021181 - Sync up from 1.231.1.1
 * 
 *    Rev 1.237   Aug 28 2003 16:43:24   HSUCHIN
 * refresh default allocations when effective date is changed for ams accounts
 * 
 *    Rev 1.236   Aug 25 2003 15:42:48   HSUCHIN
 * fixed bug with systematic updating for AMS accounts when nothing has changed.
 * 
 *    Rev 1.235   Aug 22 2003 12:59:04   HSUCHIN
 * bug fix to the way allocation are loaded for ams accounts. 
 * 
 *    Rev 1.234   Aug 21 2003 17:29:10   HERNANDO
 * Sync'd with 1.231.1.0
 * 
 *    Rev 1.233   Aug 15 2003 15:31:56   HSUCHIN
 * added AMS Restriction enhancement.   
 * 
 *    Rev 1.232   Aug 11 2003 11:56:04   YINGBAOL
 * add method isSWPGoodAtDate;
 * 
 *    Rev 1.231   Jul 10 2003 14:42:10   ZHANGCEL
 * PTS 10019543: Bug fix in ModelOffer() it case copied fee value being overwrited
 * 
 *    Rev 1.230   Jun 18 2003 17:50:56   popescu
 * create banking list only for Pay type EFT
 * 
 *    Rev 1.229   Jun 11 2003 16:06:20   FENGYONG
 * Sync add validation for accountto for autotransfer when there is no allocation set
 * 
 *    Rev 1.228   Jun 05 2003 16:40:42   YINGBAOL
 * PTS10017747
 * 
 *    Rev 1.227   Jun 03 2003 13:03:22   FENGYONG
 * do not check transaction history for minimum init purchase amount  validation
 * 
 *    Rev 1.226   Jun 01 2003 17:08:02   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.225   May 27 2003 10:34:10   popescu
 * sync-up with 1.222.1 and removed the checkBank method who 's not being called by anyone
 * 
 *    Rev 1.224   May 13 2003 19:37:14   popescu
 * PTS 10016228 & 10016241
 * 
 *    Rev 1.223   May 13 2003 16:33:26   FENGYONG
 * rel 52 , capped fund enhancement
 * 
 *    Rev 1.222   May 05 2003 18:04:52   popescu
 * fixed a crash when adding a PAC
 * 
 *    Rev 1.221   Apr 28 2003 15:02:14   sanchez
 * Sync. up with v.199.2.14. PTS#10016150
 * 
 *    Rev 1.220   Apr 22 2003 19:21:16   WINNIE
 * Systematic crash during NASU flow, logic to get pending trade and transaction history should only be applied to existing account.
 * 
 *    Rev 1.219   Apr 22 2003 14:30:22   FENGYONG
 * change 100.00 to 100
 * 
 *    Rev 1.218   Apr 17 2003 17:11:12   HERNANDO
 * PTS 10015300 - Check for Active Batch on doValidateAll.
 * This will be accepted by QA.  To ensure an error message occurs if an active does not exist.
 * Why do we associate Pay Type with Batch?
 * 
 *    Rev 1.217   Apr 17 2003 15:34:06   VADEANUM
 * PTS 10015621 - Fixed Cancel button functionality.
 * 
 *    Rev 1.216   Apr 16 2003 18:05:08   linmay
 * Ticket PTS 10016133 sync up version 1.199.2.10
 * 
 *    Rev 1.215   Apr 16 2003 10:04:00   FENGYONG
 * minimunoverride get realtranstype,
 * do not check if fundclass validate before check minimum amount 
 * 
 *    Rev 1.214   Apr 15 2003 15:47:14   FENGYONG
 * PTS ticket 10015376
 * 
 *    Rev 1.213   Apr 12 2003 15:14:24   FENGYONG
 * When fund is not effective then don't need to check if class is effective
 * 
 *    Rev 1.212   Apr 12 2003 13:45:32   FENGYONG
 * Add fundction get error num value
 * 
 *    Rev 1.211   Apr 11 2003 11:51:56   HERNANDO
 * PTS 10015300 - Fix.
 * 
 *    Rev 1.210   Apr 11 2003 11:35:22   FENGYONG
 * When call transactiohistory, set inquiry database to true , all fundmode is N
 * 
 *    Rev 1.209   Apr 11 2003 10:12:10   FENGYONG
 * error num change
 * 
 *    Rev 1.208   Apr 10 2003 09:38:34   VADEANUM
 * Acquisition Fee.
 * 
 *    Rev 1.207   Apr 10 2003 09:33:46   FENGYONG
 * tempery checkin for initial purchase amount validation
 * 
 *    Rev 1.206   Apr 08 2003 17:39:42   popescu
 * Fixed err msg when ExchgOutFee type is Flat
 * 
 *    Rev 1.205   Apr 08 2003 16:15:18   HERNANDO
 * [Sync with 1.199.2.2] PTS 10015300 - Prevent 'User does not have active batch' messages when deleting auto-added list items that do not have an active batch.  Also, displays condition on Pay Type for Auto Transfers.
 * 
 *    Rev 1.204   Apr 04 2003 15:59:06   popescu
 * split commsion work for Systematic
 * 
 *    Rev 1.203   Apr 04 2003 09:46:04   VADEANUM
 * Ensure Acquisition Fee apply only if ATFeeApply is Yes. PTS10015353. Don't allow any resetting if no updates. PTS10015621.
 * 
 *    Rev 1.202   Mar 25 2003 13:52:10   popescu
 * More synch-up
 * 
 *    Rev 1.201   Mar 25 2003 13:16:14   popescu
 * Synch-up back to trunc
 * 
 *    Rev 1.200   Mar 21 2003 18:25:48   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.199   Feb 25 2003 13:42:46   WINNIE
 * 10013808 : canTradeFundClass should get trigger when fundtocode, classtocode, accountto and effectivedate being changed
 * 
 *    Rev 1.198   Feb 18 2003 15:15:04   WINNIE
 * 10013804 : Validation of fund class validation was not trigger due to transaction type input parameter has the wrong value
 * 
 *    Rev 1.197   Feb 06 2003 18:22:48   HSUCHIN
 * added capped fund validation support for amount and stop date.  3 new methods initCapped, ValidateCappedAmt and isCappedFund.
 * 
 *    Rev 1.196   Feb 04 2003 10:29:20   WINNIE
 * use the same amount type substitutionlist for SWP as AT (need to include %); add business rule to Amttypecrossedit and validationGrossOrNet to issue error if amount type is 'U' or 'D' and GrossorNet = Net; Same rule applies to all transaction type. Add and correct logic to disable fields when ModPerm indicates modification is not allowed, some fields were missing in the original logic for statuscode = bad, it is now corrected
 * 
 *    Rev 1.195   Feb 03 2003 14:40:02   WINNIE
 * correct business rule for PAC minimum amount checking 
 * 
 *    Rev 1.194   Jan 30 2003 19:05:10   WINNIE
 * Call by reference for input parameters of getStopFlag, override and minimum amount 
 * 
 *    Rev 1.193   Jan 29 2003 18:50:20   WINNIE
 * Disable delete button for DCAF automatic Transfer
 * 
 *    Rev 1.192   Jan 21 2003 18:34:34   WINNIE
 * Systematic minimum edit check on amount : allow warning or error message based on the set up at fund limitation override
 * 
 *    Rev 1.191   Jan 18 2003 17:15:42   WINNIE
 * Correct field name for batch: sync up update and inquiry view. Add display of BatchName and BatchTrace for Systematic;
 * Add Capped Fund edit check for DCAF
 * 
 *    Rev 1.190   Jan 13 2003 20:14:48   WINNIE
 * Check feature FundEligible for salesrep flag for salesrep fund validation
 * 
 *    Rev 1.189   Jan 12 2003 15:53:14   WINNIE
 * Separate stop flag from regular trade (purchase, redemption and transfer/exchange)
 * 
 *    Rev 1.188   Jan 05 2003 11:54:00   HSUCHIN
 * sync up with rel 49.1 (1.184)
 * 
 *    Rev 1.187   Jan 03 2003 10:38:56   HERNANDO
 * Undid changes.
 * 
 *    Rev 1.186   Jan 02 2003 18:50:12   HERNANDO
 * Check flag to determine Distribution Funds Validation.
 * 
 *    Rev 1.185   Dec 06 2002 09:32:22   YINGBAOL
 * PRIF Enhancement
 * 
 *    Rev 1.184   Nov 29 2002 10:25:52   KOVACSRO
 * rxTransType changes
 * 
 *    Rev 1.183   Oct 09 2002 23:55:04   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.182   Sep 30 2002 11:01:22   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.181   Sep 11 2002 17:16:06   KOVACSRO
 * PTS10009805 : fixed copy bug
 * 
 *    Rev 1.180   Sep 09 2002 13:51:00   KOVACSRO
 * 1. syncup to 1.177.1.0.
 * 2. bug fixed for deleting a systematic record (error message 'Value cannot be zero' was showing for no reason)
 * 
 *    Rev 1.179   Sep 09 2002 13:39:46   HERNANDO
 * PTS 10009499 - Sync w/rel 47 of Stop purchase and capped fund logic.
 * 
 *    Rev 1.178   Sep 04 2002 17:14:18   KOVACSRO
 * BankAcctName is set from MFAccount::getAcctName
 * 
 *    Rev 1.177   Aug 30 2002 18:48:50   ZHANGCEL
 * Sync up to the 1.175.1.0
 * 
 *    Rev 1.176   Aug 29 2002 12:56:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.175   Aug 16 2002 11:22:58   HERNANDO
 * PTS 10008972 - Added call to setAmtTypeSubList ( idDataGroup ) in doApplyRelatedChanges for ifds::SystematicPayType.
 * 
 *    Rev 1.174   Aug 06 2002 13:08:48   YINGBAOL
 * fix cancel and delete last item issue
 * 
 *    Rev 1.173   Aug 01 2002 13:52:30   ZHANGCEL
 * Fix bug regarding fee validation problem
 * 
 *    Rev 1.172   Jul 29 2002 16:33:30   YINGBAOL
 * init  BankAcctCurrency should not trigger doApply relatedChanges 
 * 
 *    Rev 1.171   Jul 26 2002 11:40:14   WINNIE
 * Fix error message on amount = 0 when switch paytype to PAC during add of systematic
 * 
 *    Rev 1.170   Jul 25 2002 14:20:52   ZHANGCEL
 * PTS 10008129: Added logic for NextProcessDate checking
 * 
 *    Rev 1.169   Jul 23 2002 11:20:06   KOVACSRO
 * Allocations : added support for saving plan.
 * 
 *    Rev 1.168   Jul 19 2002 10:06:52   KOVACSRO
 * 1. commented out setObjectNew in constructor.
 * 2. in doReset, setup default allocations only for a new systematic.
 * These fixed the following bug (not a PTS) : Open systematic screen, click cancel, open it again, allocations dissapeared.
 * 
 *    Rev 1.167   Jul 18 2002 15:01:14   WINNIE
 * setamount after bankacctcurrency is set should be done in doapplyrelatedchanges; no side effect for formating amount due to change of bankacctcurrency because it caused fee always reset back to default value
 * 
 *    Rev 1.166   Jul 17 2002 17:41:16   ZHANGCEL
 * PTS 10008737: Added logic for the broker allow fund checking
 * 
 *    Rev 1.165   Jul 17 2002 14:26:54   KOVACSRO
 * BatchUser is a read-only field
 * 
 *    Rev 1.164   Jul 17 2002 10:31:10   ZHANGCEL
 * PTS 10008443: Bug fix regarding the edit checking of minimum FEL commission fee.
 * 
 *    Rev 1.163   Jul 15 2002 14:47:24   YINGBAOL
 * PTS 10008987
 * 
 *    Rev 1.162   Jun 21 2002 16:26:30   YINGBAOL
 * temperary solution---fix crash
 * 
 *    Rev 1.161   Jun 19 2002 13:35:08   KOVACSRO
 * formatted versus unformatted fields.
 * 
 *    Rev 1.160   Jun 10 2002 11:32:24   ZHANGCEL
 * PTS 10008472: bug fix regarding percentage
 * 
 *    Rev 1.159   Jun 05 2002 09:41:46   HSUCHIN
 * sync up to 1.152.1.2..  1.152.1.3 and 1.152.1.4 has already been synced.
 * 
 *    Rev 1.158   Jun 04 2002 17:36:44   ZHANGCEL
 * 1: added logic in the ValidateFee for the Minimon Fee check. 2. PTS 10008333: bug fix for the persentage and AllocAmount calculate problem -- made some changes in the SetAllocListAmount()
 * 
 *    Rev 1.157   May 30 2002 14:39:30   ZHANGCEL
 * Syn up with 1.152.1.3
 * 
 *    Rev 1.156   24 May 2002 15:09:08   KOVACSRO
 * doPresetField changes.
 * 
 *    Rev 1.155   22 May 2002 18:29:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.154   Apr 26 2002 15:52:40   YINGBAOL
 * set PlanCode as required----PTS10007947
 * 
 *    Rev 1.153   22 Apr 2002 10:06:04   KOVACSRO
 * Rel.47 : new design for Allocations.
 * 
 *    Rev 1.152   Mar 21 2002 13:27:30   YINGBAOL
 * leave effectivedate and status as it is when copy
 * 
 *    Rev 1.151   26 Feb 2002 19:25:06   WINNIE
 * Fix Capped fund validation
 * 
 *    Rev 1.150   Feb 25 2002 19:11:02   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.149   25 Feb 2002 11:56:04   WINNIE
 * Code clean up : call function in fundmstr 
 * 
 *    Rev 1.148   18 Feb 2002 16:18:20   KOVACSRO
 * Similar to PTS10007115. Whenever TransType is changed refresh the default allocation (it might be different for PAC and SWP).
 * 
 *    Rev 1.147   13 Feb 2002 14:01:22   KOVACSRO
 * Don't set/reset the required flag for AddressCode and have the validation for empty value in the same time.
 * 
 *    Rev 1.146   08 Feb 2002 17:12:42   HSUCHIN
 * PTS: 10007017 - doapplyrelatedchanges no longer changes frequency to "Other" when the systematic type is AT and the monthly indicator is changed.  The frequency "Other" is removed when systematic type is AT.
 * 
 *    Rev 1.145   08 Feb 2002 15:06:12   WINNIE
 * PTS 10007116 : Switching transtype from AT to PAC/SWP or Saving Plan should allow update of AdminFee
 * 
 *    Rev 1.144   07 Feb 2002 16:23:48   WINNIE
 * PTS 10007109 : Update of fee for auto transfer should not based on the tofund loadtype
 * 
 *    Rev 1.143   Feb 01 2002 18:48:36   ZHANGCEL
 * Uncomment several lines
 * 
 *    Rev 1.142   Feb 01 2002 18:37:16   ZHANGCEL
 * Fixed bug that cause crush when AmountType is changed.
 * 
 *    Rev 1.141   29 Jan 2002 14:29:04   WINNIE
 * no default fee if not commission type = 2 ; fix initial value for SWP paytype
 * 
 *    Rev 1.140   Jan 29 2002 10:12:12   ZHANGCEL
 * 1.Added logic to validate Exchanged in fee against maximum and minmum. 2. added logic to trigger formattedAmount() when AmtType changed.
 * 
 *    Rev 1.139   24 Jan 2002 19:07:02   WINNIE
 * do not set default fee for automatic transfer if commission type = 2
 * 
 *    Rev 1.138   Jan 14 2002 17:11:36   ZHANGCEL
 * Fixed the bug of RTS 10006738 - got truble when user set Freqence to be "Other"
 * 
 *    Rev 1.137   Dec 21 2001 17:43:42   ZHANGCEL
 * Added code for the seg fund validation during the NASU flow
 * 
 *    Rev 1.136   Dec 17 2001 15:39:40   ZHANGCEL
 * Added logic in getFormattedAmount() for the Amount Decimal places check against UnitsPrecision
 * 
 *    Rev 1.135   Nov 30 2001 17:02:48   ZHANGCEL
 * Implement logic for Saving Plan Acquisition Fee set up
 * 
 *    Rev 1.134   Nov 29 2001 14:41:42   ZHANGCEL
 * 1.Synch up to 1.131.1.5; 2. Fixed the bug regarding "modify a PAC with Bad status"
 * 
 *    Rev 1.131.1.5   20 Nov 2001 19:42:16   WINNIE
 * Default Fee for AutoTransfer always
 * 
 *    Rev 1.131.1.4   20 Nov 2001 15:05:48   WINNIE
 * Assign default fee for auto transfer based on the FundTo, ClassTo; Implement NFEL for AutoTransfer and PAC
 * 
 *    Rev 1.131.1.3   16 Nov 2001 16:23:08   HSUCHIN
 * bug fix for ::init() where the _pMFAccount pointer was not set and was used by Systematic indexing.
 * 
 *    Rev 1.131.1.2   12 Nov 2001 15:23:46   KOVACSRO
 * Bug fixed for getMFAccount();
 * 
 *    Rev 1.131.1.1   Oct 29 2001 16:27:34   ZHANGCEL
 * Fixed the problem regarding of ExchangeInFee issue
 * 
 *    Rev 1.131.1.0   Oct 22 2001 11:15:50   ZHANGCEL
 * Fixed the bug for get the value of CommissionType
 * 
 *    Rev 1.131   Oct 18 2001 15:48:44   YINGBAOL
 * implement PACAllowed and SWPAllowed logic
 * 
 *    Rev 1.130   02 Oct 2001 10:55:20   WINNIE
 * implement title restriction for SWP modification
 * 
 *    Rev 1.129   26 Sep 2001 17:01:24   HSUCHIN
 * changed SplitComm check to Commission Type check
 * 
 *    Rev 1.128   26 Sep 2001 14:02:44   WINNIE
 * escrow enhancement
 * 
 *    Rev 1.127   24 Sep 2001 12:40:08   WINNIE
 * fix initialization 
 * 
 *    Rev 1.126   13 Sep 2001 13:55:20   WINNIE
 * assign fee to zero for back end load fund
 * 
 *    Rev 1.125   Sep 12 2001 18:01:12   YINGBAOL
 * fix setDisableAcqFee
 * 
 *    Rev 1.124   Sep 12 2001 11:22:06   YINGBAOL
 * set BELFEE default to NO
 * 
 *    Rev 1.123   Sep 04 2001 17:23:50   YINGBAOL
 * notify control
 * 
 *    Rev 1.122   31 Aug 2001 15:58:14   WINNIE
 * delay validation 
 * 
 *    Rev 1.121   Aug 31 2001 13:51:48   YINGBAOL
 * setDefaultAcquisitionFee only apply to new record
 * 
 *    Rev 1.120   Aug 31 2001 12:39:38   YINGBAOL
 * fix
 * 
 *    Rev 1.119   Aug 27 2001 18:22:36   YINGBAOL
 * fix fee issue
 * 
 *    Rev 1.118   Aug 27 2001 09:46:02   YINGBAOL
 * fix amount type issue
 * 
 *    Rev 1.117   Aug 23 2001 09:32:42   YINGBAOL
 * add logic for setdefault fee and trans pay type
 * 
 *    Rev 1.116   22 Aug 2001 11:46:14   WINNIE
 * Code clean up; bug fix for default value (assign with groupid); validation of intialamount for saving plan etc.
 * 
 *    Rev 1.115   Aug 16 2001 10:24:56   YINGBAOL
 * fix amount type and clean some code
 * 
 *    Rev 1.114   Aug 15 2001 19:09:32   YINGBAOL
 * fix bug
 * 
 *    Rev 1.113   Aug 14 2001 14:26:22   YINGBAOL
 * fix delete item issue
 * 
 *    Rev 1.112   Aug 10 2001 12:58:18   YINGBAOL
 * fix amout type issue
 * 
 *    Rev 1.111   09 Aug 2001 10:51:06   YINGZ
 * recalculate expected fee in saving plan
 * 
 *    Rev 1.110   Aug 08 2001 11:38:32   FENGYONG
 * make cnd amount must between 0 to 999.... consistent
 * 
 *    Rev 1.109   Aug 07 2001 16:56:50   ZHANGCEL
 * Added logic for ExchInFee validation
 * 
 *    Rev 1.108   07 Aug 2001 14:28:04   YINGZ
 * fix stop date, statuscode and vuboption problems
 * 
 *    Rev 1.107   05 Aug 2001 18:01:16   WINNIE
 * validate systematic stop purchase flag
 * 
 *    Rev 1.106   05 Aug 2001 14:57:48   WINNIE
 * new method to validate BELFee flag to ensure it has a value
 * 
 *    Rev 1.105   Aug 04 2001 22:02:52   YINGBAOL
 * condition clearance
 * 
 *    Rev 1.104   03 Aug 2001 13:41:32   HSUCHIN
 * bug fix for systematic frequency
 * 
 *    Rev 1.103   03 Aug 2001 13:39:04   WINNIE
 * fix error message
 * 
 *    Rev 1.102   02 Aug 2001 18:43:06   WINNIE
 * Bug fix for multi-currency, banking validation; set read only for sysindex if record is bad;
 * 
 *    Rev 1.101   Aug 02 2001 02:54:26   YINGBAOL
 * fix amoutType for AT and fund transfer 
 * 
 *    Rev 1.100   Jul 29 2001 15:00:16   YINGBAOL
 * fix transtype, paytype, reset, saveplan and condition change  for morgan
 * 
 *    Rev 1.99   25 Jul 2001 13:55:54   YINGZ
 * bus rules, bug fix etc
 * 
 *    Rev 1.98   18 Jul 2001 16:10:36   YINGZ
 * fix expected fee and status problem
 * 
 *    Rev 1.97   18 Jul 2001 12:26:04   HSUCHIN
 * bug fix for indexing
 * 
 *    Rev 1.96   18 Jul 2001 11:55:48   YINGZ
 * bug fix and check in for Chin
 * 
 *    Rev 1.95   17 Jul 2001 10:20:56   YINGZ
 * change ValidateEffectiveDate
 * 
 *    Rev 1.94   17 Jul 2001 10:16:32   YINGZ
 * frequency change
 * 
 *    Rev 1.93   11 Jul 2001 15:11:02   HSUCHIN
 * added function lockfrequency
 * 
 *    Rev 1.92   10 Jul 2001 15:11:32   YINGZ
 * fix frequency
 * 
 *    Rev 1.91   05 Jul 2001 15:11:04   YINGZ
 * bus rules
 * 
 *    Rev 1.90   04 Jul 2001 18:43:00   WINNIE
 * code clean up and bug fix
 * 
 *    Rev 1.89   Jun 28 2001 16:10:16   HERNANDO
 * Modified ValidateEffectiveDate - removed duplicate record check.
 * 
 *    Rev 1.88   28 Jun 2001 13:42:26   YINGZ
 * not delete all sysalloc when changing from multiple to single fund alloc
 * 
 *    Rev 1.87   Jun 26 2001 12:55:10   PURDYECH
 * Infrastructure Release 1.9 Integration.
 * 
 *    Rev 1.86   25 Jun 2001 16:58:54   YINGZ
 * support paytype for saving plan
 * 
 *    Rev 1.85   21 Jun 2001 11:07:16   KOVACSRO
 * moved logic for month indicator into CBO
 * 
 *    Rev 1.84   Jun 16 2001 11:26:58   ZHANGCEL
 * Deal with ExchInFee and ExchInFlatPercent problem
 * 
 *    Rev 1.83   15 Jun 2001 16:21:10   YINGZ
 * assign currency
 * 
 *    Rev 1.82   Jun 15 2001 13:21:10   ZHANGCEL
 * support new fields in at
 * 
 *    Rev 1.81   14 Jun 2001 09:35:36   YINGZ
 * for celia
 * 
 *    Rev 1.80   12 Jun 2001 16:58:24   YINGZ
 * more work
 * 
 *    Rev 1.79   11 Jun 2001 15:18:58   YINGZ
 * checking in for Chris
 * 
 *    Rev 1.78   11 Jun 2001 10:14:30   YINGZ
 * add new dunctions
 * 
 *    Rev 1.77   05 Jun 2001 16:06:18   YINGZ
 * for others to compile
 * 
 *    Rev 1.76   31 May 2001 19:24:58   HSUCHIN
 * added Sys Index into the repository
 * 
 *    Rev 1.75   31 May 2001 17:08:56   YINGZ
 * just for checking
 * 
 *    Rev 1.74   31 May 2001 11:55:46   YINGZ
 * change getSystematicIndexList
 * 
 *    Rev 1.73   31 May 2001 11:14:58   YINGZ
 * check in for Chin
 * 
 *    Rev 1.72   25 May 2001 15:07:40   YINGZ
 * just save a copy
 * 
 *    Rev 1.71   17 May 2001 09:41:56   YINGZ
 * paytype fix
 * 
 *    Rev 1.70   15 May 2001 09:47:50   YINGZ
 * fix parent bug
 * 
 *    Rev 1.69   11 May 2001 10:19:32   HSUCHIN
 * Sync up with SSB (1.67.2.14)
 * 
 *    Rev 1.67.2.14   09 May 2001 11:18:04   KOVACSRO
 * Bug fixed (removed unused field PayTypeDesc)
 * 
 *    Rev 1.67.2.13   03 May 2001 13:59:08   BUZILAMI
 * added SysIndex
 * 
 *    Rev 1.67.2.12   02 May 2001 14:05:56   BUZILAMI
 * saving  the bank fields from inside systematic
 * 
 *    Rev 1.67.2.11   30 Apr 2001 15:40:54   HSUCHIN
 * fix to default flat/percent to percent
 * 
 *    Rev 1.67.2.10   30 Apr 2001 13:25:22   HSUCHIN
 * bug fix for flat percent and prevent default split comm from firing off.
 * 
 *    Rev 1.67.2.9   Apr 28 2001 12:25:26   YINGZ
 * disable fee etc for splicomm option
 * 
 *    Rev 1.67.2.8   Apr 25 2001 13:45:30   WINNIE
 * fix calling of FundToList
 * 
 *    Rev 1.67.2.7   25 Apr 2001 10:03:52   HSUCHIN
 * added Next Processed Date to Field Details
 * 
 *    Rev 1.67.2.6   Apr 17 2001 11:43:12   WINNIE
 * set Bank default
 * 
 *    Rev 1.67.2.5   16 Apr 2001 14:51:46   HSUCHIN
 * date of week fix by Ulli for Add Copy
 * 
 *    Rev 1.67.2.4   Apr 16 2001 10:33:04   WINNIE
 * Remove old validation for bank; copy new fields for bank between bankinstr and the CBO;
 * 
 *    Rev 1.67.2.3   Apr 15 2001 12:01:40   YINGZ
 * use checkBankCurrency
 * 
 *    Rev 1.67.2.2   14 Apr 2001 16:01:52   HSUCHIN
 * default split commission hook up to auto transfers
 * 
 *    Rev 1.67.2.1   Apr 11 2001 09:33:12   YINGZ
 * remove reference to banklist
 * 
 *    Rev 1.67.2.0   06 Apr 2001 18:58:14   BUZILAMI
 * fix
 * 
 *    Rev 1.67   Apr 04 2001 15:58:18   HERNANDO
 * Chg'd ModelOffer - set Status to N.  Revised ValidateMonthlyIndicator.
 * 
 *    Rev 1.66   04 Apr 2001 14:20:02   HSUCHIN
 * temp fix to prevent systematic to set the split commission to get default values
 * 
 *    Rev 1.65   04 Apr 2001 11:17:18   BUZILAMI
 * Systematic Bank fixes
 * 
 *    Rev 1.64   01 Apr 2001 12:49:52   HSUCHIN
 * added default split comm hook up
 * 
 *    Rev 1.63   Mar 27 2001 17:55:22   OLTEANCR
 * bug fix
 * 
 *    Rev 1.62   Mar 21 2001 14:42:26   FENGYONG
 * pass fundcode class code to getfundtolist
 * 
 *    Rev 1.60   Mar 14 2001 13:07:42   OLTEANCR
 * fixed bug in ValidateAmountLimit( )
 * 
 *    Rev 1.59   Mar 09 2001 11:42:10   OLTEANCR
 * added code to doInitWithDeafultValues( ), validate EffectiveDate( ), validateAmountLimit( ),  new code for  validateAdminFee
 * 
 *    Rev 1.58   Mar 05 2001 16:16:10   YINGBAOL
 * validate fundclass transfer
 * 
 *    Rev 1.57   27 Feb 2001 10:51:40   KOVACSRO
 * Added SegFundValidation.
 * 
 *    Rev 1.56   Feb 12 2001 15:16:10   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.55   Feb 06 2001 15:46:16   WINNIE
 * change for calling ExchRate
 * 
 *    Rev 1.54   Jan 31 2001 11:36:12   JANKAREN
 * Replace isFundClassExist with getFundDetail
 * 
 *    Rev 1.53   Dec 17 2000 20:24:30   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.52   Dec 07 2000 12:23:36   DINACORN
 * Synchronization to C2/C3: Added active batch checking, fix the multicurrency checking; Rename batch to batchname and include the field in the class property section
 * 
 *    Rev 1.51   Nov 15 2000 15:38:16   WINNIE
 * add getMFAccount method; simpify some code; can canPurchase, canRedeem in mfAccount
 * 
 *    Rev 1.50   Nov 03 2000 11:34:46   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.49   Nov 03 2000 10:43:24   HUANGSHA
 * fixed loading the default allocation for PAC
 * 
 *    Rev 1.48   Oct 27 2000 17:31:22   HUANGSHA
 * validate invalidateEffectDate function
 * 
 *    Rev 1.47   Oct 24 2000 16:57:34   KOVACSRO
 * Changed InstCode and TransitNo validation.
 * 
 *    Rev 1.46   Oct 24 2000 14:02:58   HUANGSHA
 * added the validation for the length of InstCode, BankAcctNum, and TransitNo
 * 
 *    Rev 1.45   Oct 19 2000 16:51:52   HUANGSHA
 * fix the bug for PAC and Others
 * 
 *    Rev 1.44   Oct 11 2000 09:54:18   HUANGSHA
 * added loading default allocation function for PAC/SWP
 * 
 *    Rev 1.43   Sep 29 2000 18:05:34   HUANGSHA
 * Clear monthly indicator for Daily, fix fund number setting  
 * 
 *    Rev 1.42   Sep 25 2000 19:19:12   WINNIE
 * get data and setfield using DatagroupID
 * 
 *    Rev 1.41   Sep 25 2000 16:11:40   HUANGSHA
 * change disabe fee flag only when Fund/Class or transtype is changed
 * 
 *    Rev 1.40   Sep 25 2000 15:44:08   HUANGSHA
 * move SetFundNumber(..) and SetFundClass(..) function from doApplyRelatedChange() to SetField(..)
 * 
 *    Rev 1.39   Sep 22 2000 16:41:18   HUANGSHA
 * Sync with M3, added fee disable logic, temporily fixed the allocation refresh problem
 * 
 *    Rev 1.38   Sep 15 2000 11:57:00   WINNIE
 * Bug fixes for cross edit for fund and class; add validation for fund and class; enable bankacctcurrency field based on the system feature; use getprecision method in currencyclass
 * 
 *    Rev 1.37   Sep 01 2000 16:36:38   HUANGSHA
 * Sync with M3
 * 
 *    Rev 1.36   Aug 11 2000 15:54:28   ZHANGCEL
 * Added code for BankAcctCurrency field attribute and value setting
 * 
 *    Rev 1.35   Aug 04 2000 13:58:42   YINGBAOL
 * change enquiry bank 
 * 
 *    Rev 1.34   Jul 26 2000 16:48:52   YINGBAOL
 * change create new item logic
 * 
 *    Rev 1.33   Jul 25 2000 17:10:10   WINNIE
 * Edit check for Fund, Class, FundTo, ClassTo by calling MFAccount method
 * 
 *    Rev 1.32   Jul 14 2000 14:04:26   YINGBAOL
 * fix cross triger
 * 
 *    Rev 1.31   Jul 11 2000 13:34:56   YINGBAOL
 * add fundnumber logic
 * 
 *    Rev 1.30   Jun 30 2000 16:05:42   HUANGSHA
 * removed the dublicated checking
 * 
 *    Rev 1.29   Jun 30 2000 14:32:46   HUANGSHA
 * fix for validating the amount limit
 * 
 *    Rev 1.28   Jun 30 2000 10:01:52   YINGBAOL
 * fix add copy and some other bugs
 * 
 *    Rev 1.27   Jun 27 2000 16:39:42   YINGBAOL
 * fix validation for PAC/SWP
 * 
 *    Rev 1.26   Jun 27 2000 16:16:48   WINNIE
 * Add new parameter for CanTrade function call
 * 
 *    Rev 1.25   Jun 27 2000 15:49:44   YINGBAOL
 * cantrade sync.
 * 
 *    Rev 1.24   Jun 27 2000 15:36:44   YINGBAOL
 * fix 
 * 
 *    Rev 1.23   Jun 27 2000 09:48:12   YINGBAOL
 * add substitute
 * 
 *    Rev 1.22   Jun 23 2000 15:07:48   HUANGSHA
 * Fix the Reset and effective date problem
 * 
 *    Rev 1.21   Jun 20 2000 11:41:42   BUZILA
 * reset fix
 * 
 *    Rev 1.20   Jun 19 2000 14:07:54   YINGBAOL
 * set AmountType substitute
 * 
 *    Rev 1.19   Jun 16 2000 16:46:40   HUANGSHA
 * PTS Calls bug fix
 * 
 *    Rev 1.18   Jun 12 2000 16:44:42   YINGBAOL
 * more validation for AT added
 * 
 *    Rev 1.17   Jun 06 2000 15:11:28   HUANGSHA
 * added validation
 * 
 *    Rev 1.16   Jun 05 2000 17:30:42   HSUCHIN
 * bug fix for invalid fund/class
 * 
 *    Rev 1.15   Jun 01 2000 16:12:04   YINGZ
 * fix date comparison
 * 
 *    Rev 1.14   May 31 2000 16:15:50   YINGBAOL
 * more validation added
 * 
 *    Rev 1.13   May 26 2000 15:21:18   HUANGSHA
 * Added the Amount Formatting routines
 * 
 *    Rev 1.12   May 24 2000 11:16:42   YINGBAOL
 * FundCode ClassCode validation added
 * 
 *    Rev 1.11   May 23 2000 15:16:04   YINGZ
 * add prebusday to addcopy
 * 
 *    Rev 1.10   May 19 2000 17:10:24   HUANGSHA
 * Removed the Market Condition for AT
 * 
 *    Rev 1.9   May 04 2000 16:56:24   WINNIE
 * change CURRENCY_HPP to CURRENCYCLASS_HPP
 * 
 *    Rev 1.8   May 01 2000 09:39:50   YINGBAOL
 * add validattion and other logic
 * 
 *    Rev 1.7   Apr 18 2000 09:18:06   YINGZ
 * addcopy forAutoAcctTransAllocationList
 * 
 *    Rev 1.6   Apr 17 2000 17:15:56   YINGZ
 * add AddCopy function for systematic
 * 
 *    Rev 1.5   Apr 17 2000 11:22:54   YINGBAOL
 * fix M3 crash
 * 
 *    Rev 1.4   Apr 14 2000 11:58:34   YINGBAOL
 * init logic and add some function for automatic transfer
 * 
 *    Rev 1.3   Apr 05 2000 10:42:36   HSUCHIN
 * systematic m2 sync up
 * 
 *    Rev 1.2   Apr 04 2000 10:47:10   YINGBAOL
 * M2 Sync.
 * 
 *    Rev 1.1   Mar 31 2000 16:21:42   YINGBAOL
 * check in for Chin to Sync.
 * 
 *    Rev 1.0   Feb 15 2000 11:00:08   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.59   Feb 09 2000 12:12:52   HUANGSHA
 * check in for release
 * 
 *    Rev 1.58   Feb 07 2000 12:30:42   BUZILA
 * fix
 * 
 *    Rev 1.57   Feb 01 2000 14:36:30   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.56   Jan 31 2000 18:03:42   HUANGSHA
 * check in
 * 
 *    Rev 1.55   Jan 31 2000 16:33:46   HUANGSHA
 * Fixed for validation
 * 
 *    Rev 1.54   Jan 31 2000 12:22:32   HUANGSHA
 * Fixed the Validation Problem
 * 
 *    Rev 1.53   Jan 29 2000 16:39:02   HUANGSHA
 * Added CrossEdit, not work
 * 
 *    Rev 1.52   Jan 28 2000 15:38:40   HUANGSHA
 * Set the TransType to allocation list 
 * 
 *    Rev 1.51   Jan 28 2000 14:42:26   PRAGERYA
 * For Shaobo
 * 
 *    Rev 1.50   Jan 28 2000 12:52:02   HUANGSHA
 * bug fix
 * 
 *    Rev 1.49   Jan 27 2000 15:33:48   HUANGSHA
 * changed the error message
 * 
 *    Rev 1.48   Jan 26 2000 19:41:56   PRAGERYA
 * For release
 * 
 *    Rev 1.47   Jan 25 2000 17:10:10   HUANGSHA
 * Fixed bugs
 * 
 *    Rev 1.46   Jan 22 2000 17:28:14   HUANGSHA
 * Removed the AsRequired flag for bank fields
 * 
 *    Rev 1.45   Jan 21 2000 17:22:16   YINGZ
 * validation
 * 
 *    Rev 1.44   Jan 18 2000 17:45:50   HUANGSHA
 * check in for release
 * 
 *    Rev 1.43   Jan 10 2000 16:52:48   YINGZ
 * change ValidateFundClass
 * 
 *    Rev 1.42   Jan 07 2000 17:09:00   YINGZ
 * set defaults
 * 
 *    Rev 1.41   Jan 06 2000 14:13:48   YINGZ
 * reflect base changes
 * 
 *    Rev 1.40   Jan 05 2000 10:52:02   YINGZ
 * validation change
 * 
 *    Rev 1.39   Jan 04 2000 17:43:18   YINGZ
 * save work
 * 
 *    Rev 1.38   Dec 24 1999 11:57:02   YINGZ
 * validation
 * 
 *    Rev 1.37   Dec 23 1999 16:51:52   YINGZ
 * validation
 * 
 *    Rev 1.36   Dec 23 1999 14:29:46   YINGZ
 * release
 * 
 *    Rev 1.35   Dec 22 1999 16:26:08   YINGZ
 * for release
 * 
 *    Rev 1.34   Dec 21 1999 17:25:28   YINGZ
 * add validation
 * 
 *    Rev 1.33   Dec 20 1999 16:45:10   YINGZ
 * add default
 * 
 *    Rev 1.32   Dec 20 1999 16:38:28   YINGZ
 * change initNew
 * 
 *    Rev 1.31   Dec 20 1999 10:54:34   YINGZ
 * validation
 * 
 *    Rev 1.30   Dec 17 1999 16:40:10   YINGZ
 * validation
 * 
 *    Rev 1.29   Dec 17 1999 15:50:20   PRAGERYA
 * init - DataGroupId added
 * 
 *    Rev 1.28   Dec 17 1999 12:18:04   YINGZ
 * validation check in
 * 
 *    Rev 1.27   Dec 16 1999 15:09:18   YINGZ
 * check in validation
 * 
 *    Rev 1.26   Dec 14 1999 12:05:38   YINGZ
 * add new fields
 * 
 *    Rev 1.25   Dec 13 1999 10:01:44   YINGZ
 * for release
 * 
 *    Rev 1.24   Dec 08 1999 17:20:46   YINGZ
 * validation
*/

