#ifndef COMMONPORT_H
   #include <commonport.h>
#endif
#include <string>
#include <vector>
static std::vector<std::wstring> s_vecUAFBand;
static std::vector<std::wstring> s_vecUAFCode;

static int addToUAFMap( const I_CHAR* pszBand, const I_CHAR* pszCode ) {
   s_vecUAFBand.push_back( std::wstring( pszBand ) );
   s_vecUAFCode.push_back( std::wstring( pszCode ) );
   return( 0 );
}

namespace UAF {
   extern CLASS_EXPORT bool getUAFValue( unsigned int index, std::wstring& dstrBand, std::wstring& dstrCode ) {
      if( index >= s_vecUAFBand.size() ) {
         return( false );
      }
      dstrBand = s_vecUAFBand[index];
      dstrCode = s_vecUAFCode[index];
      return( true );
   }
}

#ifndef XSTRINGIFY
   #define XSTRINGIFY(str) XSTRINGIFY_W( #str )
   #define XSTRINGIFY_W( str ) L ## str
#endif

#define DEFINE_UAF( band, code ) \
   namespace UAF {extern CLASS_EXPORT I_CHAR* const band = code;} \
   static int s_ignore ## band = addToUAFMap( XSTRINGIFY(band), code )


//defines the user access function codes, retured by view#64
//namespace UAF
//{
   DEFINE_UAF( SEARCH_FOR_ACCOUNT_OR_ENTITY,  I_( "1" ));
   DEFINE_UAF( SEARCH_FOR_CHEQUE,  I_( "2" ));
   DEFINE_UAF( SEARCH_FOR_CERTIFICATE,  I_( "3" ));
   DEFINE_UAF( ACCOUNT_DETAIL,  I_( "4" ));
   DEFINE_UAF( ADDRESS_BOOK,  I_( "5" ));
   DEFINE_UAF( DEMOGRAPHICS,  I_( "6" ));
   DEFINE_UAF( REMARKS,  I_( "7" ));
   DEFINE_UAF( BANKING_INSTRUCTION,  I_( "8" ));
   DEFINE_UAF( DEFAULT_ALLOCATION,  I_( "9" ));
   DEFINE_UAF( DISTRIBUTION,  I_( "10" ));
   DEFINE_UAF( ENTITY_MAINTANENCE,  I_( "11" ));
   DEFINE_UAF( SPOUSAL,  I_( "12" ));
   DEFINE_UAF( BENEFICIARY,  I_( "13" ));
   DEFINE_UAF( JOINT_OWNER,  I_( "14" ));
   DEFINE_UAF( ESCROW,  I_( "15" ));
   DEFINE_UAF( ACCOUNT_CERTIFICATE_INFO,  I_( "16" ));
   DEFINE_UAF( SAVING_PLAN,  I_( "17" )); // same code as pac
   DEFINE_UAF( PAC,  I_( "17" ));
   DEFINE_UAF( SWP,  I_( "18" ));
   DEFINE_UAF( PENDING_TRADE,  I_( "19" ));
   DEFINE_UAF( TRANSACTION_HISTORY,  I_( "20" ));
   DEFINE_UAF( INTEREST_ACCRUAL,  I_( "21" ));
   DEFINE_UAF( ACB,  I_( "22" ));
   DEFINE_UAF( CHEQUE,  I_( "23" ));
   DEFINE_UAF( HISTORICAL_MARKET_VALUE,  I_( "24" ));
   DEFINE_UAF( COMBINE_WITH_NO_11,  I_( "25" ));
   DEFINE_UAF( FUND_NAV,  I_( "26" ));
   DEFINE_UAF( MARKETING_FLAG,  I_( "27" ));
   DEFINE_UAF( ESCROW_BAND,  I_( "28" ));
   DEFINE_UAF( UPDATE_ENTITY_PHONE_INFO,  I_( "29" ));
   DEFINE_UAF( TEN_PERCENT_FREE_INFO,  I_( "30" ));
   DEFINE_UAF( RIF_LIF_LRIF_INFO,  I_( "31" ));
   DEFINE_UAF( RIF_LIF_LRIF_ALLOC_INFO,  I_( "32" ));
   DEFINE_UAF( SEG_FUND_CONTRACT,  I_( "33" ));
   DEFINE_UAF( SEG_FUND_GUARANTEE,  I_( "34" ));
   DEFINE_UAF( BACKDATE_TRADES,  I_( "36" ));
   DEFINE_UAF( RIF_LIF_LRIF_FIELD_INFO,  I_( "37" ));
   DEFINE_UAF( TRADING_PURCHASE,  I_( "38" ));
   DEFINE_UAF( TRADING_EXCHANGE,  I_( "39" ));
   DEFINE_UAF( ENTITY_INFO_UPDATE,  I_( "40" ));
   DEFINE_UAF( UNSEIZABLE_ACC,  I_( "41" ));
   DEFINE_UAF( GRP_STOP_REDEMPT,  I_( "42" ));
   DEFINE_UAF( TRANS_DIFF_SH,  I_( "43" ));
   DEFINE_UAF( TRANSF_BETWEEN_2_RRIF_SH,  I_( "44" ));
   DEFINE_UAF( UPD_ORD_TYPE_REDEMPTION,  I_( "45" ));
   DEFINE_UAF( UPD_ORD_TYPE_PURCHASE,  I_( "46" ));
   DEFINE_UAF( AUTOMATIC_TRANSFER,  I_( "47" ));
   DEFINE_UAF( TRADING_REDEMPTION,  I_( "48" ));
   DEFINE_UAF( TAX_RATES,  I_( "49" ));
   DEFINE_UAF( RESP_INFO,  I_( "50" ));
   DEFINE_UAF( SEG_FUND_MULTI_CONTRACT,  I_( "51" ));
   DEFINE_UAF( ACCT_SPLIT_COMM,  I_( "52" ));
   DEFINE_UAF( YTD,  I_( "53" ));
   DEFINE_UAF( AS_PENSION_PLAN,  I_( "54" ));
   DEFINE_UAF( ESOP,  I_( "55" ));
   DEFINE_UAF( FEE_PARAMETER,  I_( "56" ));
   DEFINE_UAF( HYPOTHETICAL_REDEMPTION,  I_( "57" ));
   DEFINE_UAF( DSC_REDEMPTION,  I_( "58" ));
   DEFINE_UAF( BANKING_BROKER_CODE,  I_( "59" ));
   DEFINE_UAF( BANKING_BRANCH_CODE,  I_( "60" ));
   DEFINE_UAF( BANKING_REP_CODE,  I_( "61" ));
   DEFINE_UAF( ACCOUNTREVIEW,  I_( "62" ));
   DEFINE_UAF( BANKING_CLIENT,  I_( "63" ));
   DEFINE_UAF( BANKING_FUND,  I_( "64" ));
   DEFINE_UAF( PENSION_INFO,  I_( "65" ));
   DEFINE_UAF( SETTLE_ALL_TRADE,  I_( "66" ));
   DEFINE_UAF( BANK_ACCT_NAME,  I_( "67" ));
   DEFINE_UAF( SETTLE_WIRE_ORDER,  I_( "68" ));
   DEFINE_UAF( SETTLE_BROKER,  I_( "69" ));
   DEFINE_UAF( SETTLE_ACCOUNT,  I_( "70" ));
   DEFINE_UAF( ESTATEMENT,  I_( "73" ));
   DEFINE_UAF( AMS_GLOBAL,  I_( "74" ));
   DEFINE_UAF( AMS_REPORT,  I_( "75" ));
   DEFINE_UAF( SHR_FAMILY,  I_( "76" ));
   DEFINE_UAF( PROTECTED_FUND_ACCT_CONTRACT,  I_( "77" ));
   DEFINE_UAF( PROTECTED_FUND_SETUP,  I_( "78" ));
   DEFINE_UAF( PROTECTED_FUND_RESET_INSTR,  I_( "79" ));
   DEFINE_UAF( FEE_PARAMETER_SYSTEM,  I_( "80" ));
   DEFINE_UAF( ACCT_CATEGORY,  I_( "81" ));
   DEFINE_UAF( MKT_INDEX_MASTER,  I_( "82" ));
   DEFINE_UAF( MKT_INDEX_VALUES,  I_( "83" ));
   DEFINE_UAF( BROKER_AMS_RESTRICT,  I_( "84" ));
   DEFINE_UAF( TRADE_SEARCH,  I_( "85" ));
   DEFINE_UAF( RESTART_PAC_ON_CAPPED_FUND,  I_( "86" ));
   DEFINE_UAF( MANUAL_DIVIDEND,  I_( "87" ));
   DEFINE_UAF( PAYMENT_INSTRUCTIONS,  I_( "88" ));
   DEFINE_UAF( UPD_NEXT_REB_DATE,  I_( "89" ));
   DEFINE_UAF( CHARGE_WD_FEE,  I_( "90" ));
   DEFINE_UAF( RETURNED_MAIL_AUTOMATION,  I_( "91" ));
   DEFINE_UAF( AMS_RULES_REQUIRED,  I_( "92" ));
   DEFINE_UAF( AMS_MIX_OVERRIDE,  I_( "93" ));
   DEFINE_UAF( PAY_TO_ENTITY,  I_( "94" ));
   DEFINE_UAF( TRADE_TAX_RATE_OVERRIDE,  I_( "95" ));
   DEFINE_UAF( INSTITUTION_MAINTENANCE,  I_( "96" ));
   DEFINE_UAF( DIRECT_TRADING_TRANSACTION,  I_( "102" ));
   DEFINE_UAF( DIRECT_TRADING_AGREEMENT,  I_( "103" ));
   DEFINE_UAF( TRADE_VERIFICATION   , I_("105"));
   DEFINE_UAF( SETTLE_LOCATION_ACCT_LVL,  I_( "107" ));
   DEFINE_UAF( SETTLE_LOCATION_SYS_LVL,  I_( "108" ));
   DEFINE_UAF( SETTLE_PAY_INSTRUCTION,  I_( "109" ));
   DEFINE_UAF( DAILY_TRANSACTIONS_FEES,  I_( "110" ));
   DEFINE_UAF( FOREIGN_CONTENT,  I_( "113" ));
   DEFINE_UAF( SHR_FUND_SPONSOR_AGREEMENT,  I_( "114" ));
   DEFINE_UAF( TAX_EXEMPT_AUTHORIZATION,  I_( "115" ));
   DEFINE_UAF( FEE_MODEL,  I_( "116" ));
   DEFINE_UAF( FUNDSPONSOR_FEE_MODEL,  I_( "117" ));
   DEFINE_UAF( ACCOUNT_FEE_MODEL,  I_( "118" ));
   DEFINE_UAF( FUND_GROUP_BANK_INSTR,  I_( "119" ));
   DEFINE_UAF( AGGREGATED_ORDER_INFORMATION,  I_( "120" ));
   DEFINE_UAF( FUND_BROKER_MAINTENANCE,  I_( "122" ));
   DEFINE_UAF( SHR_FUND_BROKER,  I_( "123" ));
   DEFINE_UAF( AGGREGATE_OPTION,  I_( "124" ));
   DEFINE_UAF( AGGREGATED_ORDER_TRADE_DATE,  I_( "125" ));
   DEFINE_UAF( MSG_SEARCH,  I_( "126" ));
   DEFINE_UAF( FILE_SEARCH,  I_( "127" ));
   DEFINE_UAF( VERIFY_CANCEL_INSTRUCTION,  I_( "128" ));
   DEFINE_UAF( TRANCE_CANCELLATION,  I_( "129" ));
   DEFINE_UAF( SEG_GUAR_ADJ_BAND,  I_( "130" ));
   DEFINE_UAF( ACCT_LVL_CUT_OFF_TIME,  I_( "131" ));
   DEFINE_UAF( CANCEL_SETTLE,  I_( "132" ));
   DEFINE_UAF( CANCEL_DIVIDEND,  I_( "133" ));
   DEFINE_UAF( SWP_TAX_OVERRIDE,  I_( "134" ));
   DEFINE_UAF( BULK_CANCELLATION,  I_( "135" ));
   DEFINE_UAF( CANCELLATION_INSTRUCTION,  I_( "136" ));
   DEFINE_UAF( SAVINGS_DIRECTIVE,  I_( "137" ));
   DEFINE_UAF( TRANS_HIST_DILUTION_ALLOC_LIST,  I_( "138" ));
   DEFINE_UAF( MCH_AND_SECUR_REC_FILE_INDICATOR,  I_( "139" ));
   DEFINE_UAF( SETTLEMENT_PHASE_STATUS_CHANGE,  I_( "140" ));
   DEFINE_UAF( PAYMENT_SEARCH,  I_( "142" ));
   DEFINE_UAF( ASSIGNEE_ENTITY_TYPE_SETUP,  I_( "143" ));
   DEFINE_UAF( MGMTCO_PAYMENT_INSTRUCTION,  I_( "144" ));
   DEFINE_UAF( ACCOUNT_TRADING_OVERRIDES,  I_( "145" ));
   DEFINE_UAF( BROKER_TRADING_OVERRIDES,  I_( "146" ));
   //DEFINE_UAF( CLONE_ACCOUNT,  I_( "148" ));
   DEFINE_UAF( CLONE_ACCOUNT,  I_( "149" ));
   DEFINE_UAF( PAYMENT_BATCH,  I_( "150" ));
   DEFINE_UAF( AMS_STATUS_UPDATE,  I_( "152" ));
   DEFINE_UAF( AMS_ACCT_LVL,  I_( "153" ));
   DEFINE_UAF( ACCOUNT_BALANCE_OVERRIDE,  I_( "154" ));  // PMI
   DEFINE_UAF( DILUTION_CALCULATOR,  I_( "156" ));  // PMI
   DEFINE_UAF( AMS_ASSET,  I_( "157" ));
   DEFINE_UAF( AFFLUENT,  I_( "158" ));
   DEFINE_UAF( CTRBT_RCPT_CANCELLATION,  I_( "159" ));
   DEFINE_UAF( TRADE_BANKING,  I_( "160" ));
   DEFINE_UAF( ACCT_LEVEL_SETTLEMENT_RULE,  I_( "162" ));
   DEFINE_UAF( LIF_GAIN_LOSS,  I_( "163" ));
   DEFINE_UAF( FUND_MASTER,  I_( "164" )); 
   DEFINE_UAF( FUND_DETAIL,  I_( "165" )); 
   DEFINE_UAF( REGULATORY_STANDARDS,  I_( "168" )); 
   DEFINE_UAF( REGULATORY_DOCUMENTS,  I_( "167" ));  
   DEFINE_UAF( SYSTEM_STOP_REASON,  I_( "169" )); 
   DEFINE_UAF( DOC_LIST,  I_( "170" )); 
   DEFINE_UAF( REG_DOCUMENT_WAVESTATUS,  I_( "171" ));
   DEFINE_UAF( UNCLAIM_RETURN_MAIL,  I_( "173" ));
   DEFINE_UAF( CHEQUE_LIST,  I_( "174" ));
   DEFINE_UAF( RELEASE_FROZEN_ACCOUNT,  I_( "175" ));
   DEFINE_UAF( TRADE_AUTHORIZATION,  I_( "176" ));
   DEFINE_UAF( TFSA_CONTRIBUTION_INFO,  I_( "177" ));
   DEFINE_UAF( FUND_CLASS_COPY,  I_( "178" )); 
   DEFINE_UAF( RIF_LIF_LRIF_TAX_UPDATE,  I_( "179" ));
   DEFINE_UAF( MODIFY_BATCH_ID,  I_( "180" ));
   DEFINE_UAF( BATCH,  I_( "181" ));
   DEFINE_UAF( FUND_CLASS_MAINTENANCE,  I_( "182" ));
   DEFINE_UAF( INVESTOR_AUTHORIZATION_INFO,  I_( "183" ));
   DEFINE_UAF( BANKING_VERIFICATION,  I_( "184" ));
   DEFINE_UAF( TRADE_SETTLEMENT_LOCS,  I_( "185" ));
   DEFINE_UAF( DISTRIB_VERIFICATION,  I_( "186" ));
   DEFINE_UAF( SHR_ADDRESS_VERIFICATION,  I_( "187" ));
   DEFINE_UAF( ACCOUNT_STATIC_DATA_VERIFY,  I_( "188" ));
   DEFINE_UAF( RESP_ACCOUNT_INFROMATION,  I_( "189" ));
   DEFINE_UAF( RESP_NOTIONAL_INFORMATION,  I_( "190" ));
   DEFINE_UAF( RESP_BENEFICIARY , I_( "191" ));
   DEFINE_UAF( RESP_GRANTS_REQUEST, I_( "192" ));
   DEFINE_UAF( RESP_GRANTS, I_( "193" ));
   DEFINE_UAF( ENTITY_TAX_JURIS_HISTORY,  I_( "194" ));
   DEFINE_UAF( RESP_ALLOCATION, I_( "195" ));
   DEFINE_UAF( RESP_BENEFICIARY_ALLOCATION, I_( "196" ));
   DEFINE_UAF( EXTERNAL_PROVIDER_UPDATE, I_( "197" ));
   DEFINE_UAF( RESP_TRANSFER, I_( "199" ));
   DEFINE_UAF( RESP_ACCOUNT_TERMINATION, I_( "200" ));
   DEFINE_UAF( RESP_ZERO_GRANT, I_( "201" ));
   DEFINE_UAF( RESP_INTERFACE_FILE, I_( "202" ));
   DEFINE_UAF( ACCT_GUARNT_GUARD_OPTN, I_( "203" ));
   DEFINE_UAF( SYSTEMLVL_TRAILER_FEE_SETUP, I_( "204" ));
   DEFINE_UAF( RESP_GOVT_FILING_AMENDMENT, I_( "205" ));
   DEFINE_UAF( ACCTLVL_TRAILERFEE_SETUP, I_( "206" )); 
   DEFINE_UAF( SMART_FORM, I_( "207" )); 
   DEFINE_UAF( REL_STOP_RED, I_( "208" )); 
   DEFINE_UAF( COMMISSION_REDUCTION, I_( "209" )); 
   DEFINE_UAF( PORTFOLIO_SETUP, I_( "210" ));
   DEFINE_UAF( GLOBAL_SEARCH, I_( "211" )); 
   DEFINE_UAF( INTEREST_CONFIGURATION, I_( "212" ));
   DEFINE_UAF( INTEREST_MAINTENANCE, I_( "213" ));
   DEFINE_UAF( GUARANTEE_RULES, I_( "214" ));
   DEFINE_UAF( SEG_ATTRIBUTES, I_( "215" ));
   DEFINE_UAF( UNCLM_REMIT_DATE_UPDATE, I_( "216" ));
   DEFINE_UAF( GUARANTEE_INFORMATION,  I_( "217" ));
   DEFINE_UAF( SEG_FORCE_TRANSACTION,  I_( "218" ));
   DEFINE_UAF( MMF_PAYMENT_INFO, I_( "219" ));
   DEFINE_UAF( INVESTMENT_HISTORY_LIST,  I_( "220" ));
   DEFINE_UAF( MATURITYSWPEEP_INSTR, I_( "221" )); 
   DEFINE_UAF( SEG_PROCESSING, I_( "222" ));
   DEFINE_UAF( TFSA_AMENDMENT, I_( "223" ));//IN2747587 - guifn 223 - TFSA Amendment
   DEFINE_UAF( LANGUAGE_TOGGLE, I_( "224" )); 
   DEFINE_UAF( EVENT_DATE_GEN,  I_( "225" ));
   DEFINE_UAF( EVENT_SCH_MAIN,  I_( "226" )); 
   DEFINE_UAF( TRADE_SCH_MAIN,  I_( "228" )); 
   DEFINE_UAF( RESP_DIPLOMA,  I_( "232" )); 
   DEFINE_UAF( ACCT_FEE_MODEL_ASSOCIATION, I_( "233" )); 
   DEFINE_UAF( VALUE_VARIATION, I_( "234" )); 
   DEFINE_UAF( REMIT_UNCLM_ACCT, I_( "235" )); 
   DEFINE_UAF( HOLDING_COMP_MAINT, I_( "236" )); 
   DEFINE_UAF( SHR_STATEMENT_SCHED, I_( "238" )); 
   DEFINE_UAF( INVOICE_INSTRUCTION, I_( "239"));
   DEFINE_UAF( REPORT_GROUP, I_( "240"));
   DEFINE_UAF( ADDITIONAL_ASSETS, I_( "241"));
   DEFINE_UAF( ASSET_VALUE, I_( "242"));
   DEFINE_UAF( FFI_MAINT, I_( "244" )); 
   DEFINE_UAF( BROKER_IDENT_MAINT, I_( "245" )); 
   DEFINE_UAF( FUND_IDENT_MAINT, I_( "246" )); 
   DEFINE_UAF( ACCT_REGIS_MAINT, I_("247"));
   DEFINE_UAF( ENTITY_REGULATORY_MAINT, I_( "248" ));
   DEFINE_UAF( FUNDGROUP_REGULATORY    ,  I_( "249" ));
   DEFINE_UAF( BROKER_REGULATORY       ,  I_( "250" ));
   DEFINE_UAF( INTERMEDIARY_REGULATORY ,  I_( "251" ));
   DEFINE_UAF( TRAILER_FEES_INQUIRY    ,  I_( "252" ));
   DEFINE_UAF( ACCOUNT_GROUPING        ,  I_( "253" ));
   DEFINE_UAF( PRIVATE_WEALTH_INFO     ,  I_( "254" ));
   DEFINE_UAF( ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT, I_("255"));
   DEFINE_UAF( UPDATE_INDICIA_SEARCH_REQUEST, I_("257"));
   DEFINE_UAF( FATCA_FILING_DETAIL     ,  I_("258"));
   DEFINE_UAF( SOURCE_OF_FUNDS_CHECKED ,  I_("259"));
   DEFINE_UAF( RESP_NOTIONAL_BALANCE,  I_( "260" ));
   DEFINE_UAF( RESP_GRANT_INFORMATION, I_( "261" ));
   DEFINE_UAF( RESP_NOTIONAL_ACTIVITY  ,  I_("262"));
   DEFINE_UAF( AMS_REBAL_REQ_ON_DEMAND ,  I_("264"));
   DEFINE_UAF( ACCOUNT_GROUPING_INFO, I_("265"));
   DEFINE_UAF( FUND_RULES_MAINTENANCE, I_("266"));
   DEFINE_UAF( TRANSFER_OF_ACCOUNTS, I_("267"));
   DEFINE_UAF( REMARK_ALERT, I_("268"));
   DEFINE_UAF( FUND_GROUP, I_("269"));
   DEFINE_UAF( FUND_BROKER_LINKAGE, I_("270"));
   DEFINE_UAF( REG_PLAN_TRANSFER, I_("271"));
   DEFINE_UAF( REGULATORY_AGREEMENT, I_("272"));
   DEFINE_UAF( ACCT_ROUNDING_RULE, I_("274"));
   DEFINE_UAF( BROKER_CUT_OFF, I_("273"));
   DEFINE_UAF( EXTERNAL_TA_FUND_LINKAGE, I_("275"));
   DEFINE_UAF( ACCT_DELETION_REVIEW, I_("276"));
   DEFINE_UAF( REG_ACCT_EXTR, I_("277"));
   DEFINE_UAF( REG_ACCT_INFO_REV, I_("278"));
   DEFINE_UAF( WITHHODLDING_TAX_RATES_MAINTANENCE, I_("279"));
   DEFINE_UAF( FUND_DISTRIBUTION_SPLIT_MAINTENANCE, I_("280"));
   DEFINE_UAF( APAC_SUPREGN, I_("281"));
   DEFINE_UAF( RDSP_TRANSFER, I_("282"));
   DEFINE_UAF( RDSP_ACCOUNT_INFORMATION, I_("283"));
   DEFINE_UAF( RDSP_NOTIONAL_ACTIVITY, I_("284"));
   DEFINE_UAF( RDSP_NOTIONAL_BALANCE, I_("285"));
   DEFINE_UAF( RDSP_INTERFACE_TRANSACTIONS, I_("286"));   

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastids/ifastuafids.cpp-arc  $
 * 
 *    Rev 1.155   Apr 10 2012 14:43:54   if991250
 * changed to DEFINE_UAF( RESP_DIPLOMA,  I_( "232" )); 
 * 
 *    Rev 1.154   Feb 15 2012 12:20:34   if991250
 * RESP Diploma Desktop Web
 * 
 *    Rev 1.153   Feb 03 2012 18:38:22   dchatcha
 * Synch up: IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.152   Jan 25 2012 09:06:02   panatcha
 * IN2747587 - guifn 223 - TFSA Amendment
 * 
 *    Rev 1.151   Jan 24 2012 00:02:50   panatcha
 * P0188394 - iFast Performance Fee
 * 
 *    Rev 1.150   Jan 09 2012 12:23:50   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.149   Dec 30 2011 08:37:06   if991250
 * Language toggle UAF
 * 
 *    Rev 1.148   Dec 26 2011 21:29:00   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.147   Dec 08 2011 11:11:12   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.146   Dec 08 2011 00:22:04   wp040032
 *  P0183989 - Money Market Non Receipt
 * 
 *    Rev 1.145   Dec 01 2011 19:03:46   wp040100
 * P0186477/FN03 - GIA - Investment History Changes
 * 
 *    Rev 1.144   Nov 27 2011 21:49:14   wp040100
 * P0186477/FN03 - GIA - Investment History Changes
 * 
 *    Rev 1.143   Nov 10 2011 20:25:24   wp040100
 * P0186477/FN03 - GIA - Added Investment History UAF entry
 * 
 *    Rev 1.142   Oct 28 2011 13:27:42   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.141   Oct 19 2011 18:09:14   popescu
 * SEG - Configuration  S1 (SEG and Desktop skeleton)
 * 
 *    Rev 1.140   Oct 07 2011 00:36:14   kitticha
 * PETP0183105 FN02 - Unclaimed Property Alberta.
 * 
 *    Rev 1.139   Sep 19 2011 10:50:18   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.138   Sep 02 2011 17:52:30   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.137   Aug 22 2011 15:09:06   jankovii
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.136   Aug 04 2011 18:24:56   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.135   Jul 28 2011 11:36:58   jankovii
 * PET186484 - Global Search
 * 
 *    Rev 1.134   Apr 20 2011 22:52:12   kitticha
 * PETP0183105 FN01 - Unclaimed Property for Alberta.
 * 
 *    Rev 1.133   Mar 17 2011 13:14:42   jankovii
 * PET 179563 FN01 - Smart Forms
 * 
 *    Rev 1.132   Nov 23 2010 00:44:22   dchatcha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.131   Sep 30 2010 10:13:18   jankovii
 * PET168727 FN22 - Trailer Fee Setup
 * 
 *    Rev 1.130   Sep 20 2010 01:50:34   dchatcha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.129   Jun 09 2010 07:46:30   panatcha
 * PET0166541_FN02_IN2142963 - update enable/disable  Tax Juris Hist button for RESP2 product
 * 
 *    Rev 1.128   May 27 2010 16:35:58   popescu
 * IN 2130000 - PET165541 -  the grant request field is guarded by UAF 192
 * 
 *    Rev 1.127   May 27 2010 12:12:22   popescu
 * IN 2130000 - PET165541 -  Access to Grant SCreen should be done via the same function level security as the DSK web browser screen therefore modified the value from 192 to 193
 * 
 *    Rev 1.126   May 12 2010 11:59:24   popescu
 * RESP/QESI - adding extra security to the EPP where used type
 * 
 *    Rev 1.125   Apr 23 2010 09:24:48   jankovii
 * PET0165541 FN01 QESI Trading.
 * 
 *    Rev 1.124   Apr 14 2010 16:40:20   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.123   Mar 23 2010 13:29:06   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.122   Mar 15 2010 09:07:42   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.121   Mar 12 2010 14:18:22   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.120   Mar 05 2010 15:53:32   jankovii
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.119   Feb 24 2010 13:24:12   jankovii
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.118   Jan 28 2010 17:07:06   jankovii
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.117   Dec 02 2009 09:54:34   popescu
 * P0160872 - Fund Setup Phase II
 * 
 *    Rev 1.116   Nov 20 2009 11:42:48   popescu
 * Static Data - entity verify names -linked the web screen
 * 
 *    Rev 1.115   Nov 17 2009 15:15:34   jankovii
 * PET0166583 FN01 Static Data Changes Banking 
 * 
 *    Rev 1.114   Oct 27 2009 23:37:26   purdyech
 * Restructured so that the entries can be iterated
 * 
 *    Rev 1.113   Aug 11 2009 12:01:12   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.112   Jul 23 2009 10:59:32   jankovii
 * PET 0164646 FN01 - TFSA phase 3.
 * 
 *    Rev 1.111   Jul 08 2009 07:29:02   dchatcha
 * PET 156681 - FN 14 - Investor Authorization.
 * 
 *    Rev 1.110   May 19 2009 14:09:08   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.109   May 14 2009 15:03:34   dchatcha
 * PET160872 FN01 Fund Setup-Class Level.
 * 
 */ 

