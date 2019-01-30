#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

// Defines error ids to pass to ErrMsgRulesList 
namespace IFASTERR
{
   // maximum payout amount is exceeded
   extern CLASS_EXPORT I_CHAR * const MAXIMUM_PAYOUT_AMOUNT_IS_EXCEEDED                   = I_("113");
   // spousal consent is required
   extern CLASS_EXPORT I_CHAR * const SPOUSAL_CONSENT_IS_REQUIRED                         = I_("130");
   // spousal consent/waiver required
   extern CLASS_EXPORT I_CHAR * const SPOUSAL_CONSENT_WAIVER_REQUIRED                     = I_("131");
   // total redemption exceeds maximum
   extern CLASS_EXPORT I_CHAR * const TOTAL_REDEMPTION_EXCEEDS_MAXIMUM                    = I_("132");
   // remaining minimum amount must be paid first
   extern CLASS_EXPORT I_CHAR * const REMAINING_MINIMUM_AMOUNT_MUST_BE_PAID_FIRST         = I_("134");
   // remaining acct balance is insufficient
   extern CLASS_EXPORT I_CHAR * const REMAINING_ACCT_BALANCE_IS_INSUFFICIENT              = I_("135");
   // scheduled payment information not available
   extern CLASS_EXPORT I_CHAR * const SCHEDULED_PAYMENT_INFORMATION_NOT_AVAILABLE         = I_("137");
   // redemption code rules not setup
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_CODE_RULES_NOT_SETUP                     = I_("138");   
   // invalid settlement source for account designation
   extern CLASS_EXPORT I_CHAR * const INVALID_SETTLEMENT_SOURCE_FOR_ACCOUNT_DESIGNATION   = I_("203");
   // invalid settlement type for dealer/intermediary
   extern CLASS_EXPORT I_CHAR * const INVALID_SETTLEMENT_TYPE_FOR_DEALER_INTERMEDIARY     = I_("206");
   // invalid order source for account designation
   extern CLASS_EXPORT I_CHAR * const INVALID_ORDER_SOURCE_FOR_ACCOUNT_DESIGNATION        = I_("208");
   // the intermediary is not permitted to enter wire orders
   extern CLASS_EXPORT I_CHAR * const INTERMEDIARY_IS_NOT_PERMITTED_TO_ENTER_WIRE_ORDERS  = I_("209");
   // not permitted to enter money market wire orders
   extern CLASS_EXPORT I_CHAR * const NOT_PERMITTED_TO_ENTER_MONEY_MARKET_WIRE_ORDERS     = I_("210");
   // no dealer information available for broker code
   extern CLASS_EXPORT I_CHAR * const NO_DEALER_INFORMATION_AVAILABLE_FOR_BROKER_CODE     = I_("211");
   //RESP Redemption exceed Contribution
   extern CLASS_EXPORT I_CHAR * const RESP_REDEMPTION_EXCEED_CONTRIBUTION                 = I_("218");
   //fund is capped, verify if transaction is allowed
   extern CLASS_EXPORT I_CHAR * const FUND_IS_CAPPED_VERIFY_IF_TRANSACTION_IS_ALLOWED     = I_("221"); 
   //contract account status is active
   extern CLASS_EXPORT I_CHAR * const CONTRACT_ACCOUNT_STATUS_IS_ACTIVE                   = I_("222");
   //contract acount satus is death status
   extern CLASS_EXPORT I_CHAR * const CONTRACT_ACCOUNT_STATUS_IS_DEATH_STATUS             = I_("224");
   //must enter a death claim redemption code
   extern CLASS_EXPORT I_CHAR * const MUST_ENTER_A_DEATH_CLAIM_REDEMPTION_CODE            = I_("229");
   // dealer cannot settle orders placed by intermediary
   extern CLASS_EXPORT I_CHAR * const DEALER_CANNOT_SETTLE_ORDERS_PLACED_BY_INTERMEDIARY  = I_("230");
   //DP 20 or RD 61,83,84 not allowed in Transfer
   extern CLASS_EXPORT I_CHAR * const DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER                = I_("237");
   //No RESP Beneficiary selected
   extern CLASS_EXPORT I_CHAR * const NO_RESP_BENEFICIARY_SELECTED                           = I_("239");
   //No originating contribution selected
   extern CLASS_EXPORT I_CHAR * const NO_ORIGINATING_CONTRIBUTION_SELECTED                   = I_("240");
   //RESP Redemption exceed Earnings
   extern CLASS_EXPORT I_CHAR * const RESP_REDEMPTION_EXCEED_EARNINGS                        = I_("241");
   //Only RD 64 and DP 17 are allowed for RESP to RESP transfer.
   extern CLASS_EXPORT I_CHAR * const DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER   = I_("244");
   // Not enough grant amount for return.
   extern CLASS_EXPORT I_CHAR * const NOT_ENOUGH_GRANT_AMT_FOR_RETURN                        = I_("250");
   // this is an as pension plan account
   extern CLASS_EXPORT I_CHAR * const AN_AS_PENSION_PLAN_ACCOUNT                             = I_("251");
   // AIP withdrawal exists, transfer to another RESP not allowed
   extern CLASS_EXPORT I_CHAR * const AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED   = I_("322");
   // Cannot apply RESP OC withdrawal to invalid year.
   extern CLASS_EXPORT I_CHAR * const INVALID_YEAR_RESP_OC_WITHDRAWAL                        = I_("324");
   //Invalid CESG repayment reason code
   extern CLASS_EXPORT I_CHAR * const INVALID_CESG_REPAYMENT_REASON_CODE                     = I_("325");
   // DP or RD can only be used for RESP to RESP transfer
   extern CLASS_EXPORT I_CHAR * const DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX   = I_("329");
   // Settling grant repayment by units is not allowed
   extern CLASS_EXPORT I_CHAR * const SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED           = I_("331");
   // Net transaction amount exceeds net CESG owing
   extern CLASS_EXPORT I_CHAR * const NET_TRANS_AMT_EXCEED_NET_CESG_OWNING                   = I_("332");
   // nationality is not populated
   extern CLASS_EXPORT I_CHAR * const NATIONALITY_IS_NOT_POPULATED                        = I_("355");
   // the birth date of account holder or spouse is missing
   extern CLASS_EXPORT I_CHAR * const BIRTH_DATE_OF_ACCOUNT_HOLDER_OR_SPOUSE_IS_MISSING   = I_("336");
   // account holders birth date is missing
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_HOLDERS_BIRTH_DATE_IS_MISSING               = I_("337");
   // Account Escrow Flag is active
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_ESCROW_FLAG_IS_ACTIVE                       = I_("374");
   // missing redemption fee setup
   extern CLASS_EXPORT I_CHAR * const MISSING_REDEMPTION_FEE_SETUP                        = I_("389");
   //Valid SIN is required for RESP accounts
   extern CLASS_EXPORT I_CHAR * const INVALID_SIN_FOR_RESP_ACCOUNT                        = I_("395");
   // redemption amount is greater than account balance
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_AMOUNT_IS_GREATER_THAN_ACCOUNT_BALANCE   = I_("400");   
   //transfer/exchange amount is greater than account balance
   extern CLASS_EXPORT I_CHAR * const TR_XR_AMOUNT_IS_GREATER_THAN_ACCOUNT_BALANCE        = I_("401");
   // salesrepcode should only be 5 characters
   extern CLASS_EXPORT I_CHAR * const  SALESREPCODE_SHOULD_ONLY_BE_5_CHARACTERS           = I_("414");
   // whether wire number is mandatory for wire trades 
   extern CLASS_EXPORT I_CHAR * const WIRE_ORDER_NUMBER_REQUIRED                          = I_("423");
   // fund investro capable while fund broker is not
   extern CLASS_EXPORT I_CHAR * const FUND_INVESTRO_CAPABLE_WHILE_FUND_BROKER_IS_NOT      = I_("427");
   // fund broker investro capable while fund is not
   extern CLASS_EXPORT I_CHAR * const FUND_BROKER_INVESTRO_CAPABLE_WHILE_FUND_IS_NOT      = I_("428");
   // client settlement instructions required
   extern CLASS_EXPORT I_CHAR * const FUND_MGMT_CLIENT_SETTLEMENT_INSTR_REQUIRED          = I_("429");
   // whether wire order size allowed to be > 10
   extern CLASS_EXPORT I_CHAR * const WIRE_ORDER_ALLOWED_SIZE                             = I_("437");
   // whether bank country code is required
   extern CLASS_EXPORT I_CHAR * const BANK_COUNTRY_CODE_REQUIRED                          = I_("441");
   // whether sender ref num is required or not
   extern CLASS_EXPORT I_CHAR * const SENDER_REF_NUM_REQUIRED                             = I_("443");   
  // User-defined maturity date is less than %TERM% years from account effective date.
   extern CLASS_EXPORT I_CHAR * const USER_DEF_MAT_LESS                                   = I_("444");   

   // user defined maturity date cannot be blank
   extern CLASS_EXPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK          = I_("450");   

   // dmd later then legal maturity date
   extern CLASS_EXPORT I_CHAR * const DMD_LATER_THAN_LEGAL_MATURITY_DATE                  = I_("451");   
   // cmd later then legal maturity date
   extern CLASS_EXPORT I_CHAR * const CMD_LATER_THAN_LEGAL_MATURITY_DATE                  = I_("452");   
   // whether trade can be backdated for EUSD
   extern CLASS_EXPORT I_CHAR * const MONEY_OUT_TXN_SHOULD_BE_CANCELELD_FIRST             = I_("464");
   // whether duplicate SIN is allowed or not AND whether same SIN is allowed for different entities
   extern CLASS_EXPORT I_CHAR * const DUPLICATE_SIN                                       = I_("467");  
   // Matching BIC code not found for the participant
   extern CLASS_EXPORT I_CHAR * const MATCHING_BIC_CODE_NOT_FOUND                         = I_("476");  
   // Annuitant is older then lates age to open/purchase contract
   extern CLASS_EXPORT I_CHAR * const ANNUITANT_IS_OLDER                                  = I_("482");  
   // Transaction is not allowed during settlement pahse
   extern CLASS_EXPORT I_CHAR * const TRANS_IS_NOT_ALLOWED_DURING_SETTLEMENTPHASE         = I_("483");
   // Payment for both Redemption and Distribution must be setup to broker
   extern CLASS_EXPORT I_CHAR * const BROKER_PAYMENT_FOR_SETUP_NOT_IN_PAIR                = I_("498");
   //Min Max Age validation
   extern CLASS_EXPORT I_CHAR * const MIN_MAX_AGE                                         = I_("561"); 
   //Non resident tax jurisdiction for tax type
   extern CLASS_EXPORT I_CHAR * const NON_RESIDENT_TAX_JURID                              = I_("562"); 
   //Contribution not allowed for non resident tax jurisdiction
   extern CLASS_EXPORT I_CHAR * const NON_RESIDENT_TAX_JURISD_CONTR_NOT_ALLOWED           = I_("563"); 
   //Stop active PAC / AT; contribution not allowed for non resident tax jurisdiction
   extern CLASS_EXPORT I_CHAR * const NON_RESIDENT_TAX_JURISD_STOP_PAC                    = I_("564");
   //Account owner has blank tax jurisdiciton
   extern CLASS_EXPORT I_CHAR * const TAX_JURIS_NOT_FOUND_FOR_OWNER                       = I_("708");
   //Deposit Code is applicable for Sibling Only accounts
   extern CLASS_EXPORT I_CHAR * const DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS   = I_("710");
   //Beneficiary is not linked to a PCG.
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_IS_NOT_LINKED_TO_PCG                       = I_("711");
   // Account is not Sibling Only. Grant Amount is not applicable
   extern CLASS_EXPORT I_CHAR * const GRANT_AMOUNT_NOT_APPLICABLE                            = I_("716"); 
   // Beneficiary is not eligible for CLB
   extern CLASS_EXPORT I_CHAR * const BENEF_NOT_ELIGIBLE_FOR_CLB                             = I_("718"); 
   //CLB amount cannot be transfered sin not the same
   extern CLASS_EXPORT I_CHAR * const CLB_AMOUNT_CANNOT_BE_TRANSFERED                        = I_("719");
   //Redemption code is invalid since beneficiary is non-resident
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT = I_("720");
   //Redemption code '77' applicable only for non-resident beneficiaries
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_CODE_APPLICABLE_ONLY_FOR_NON_RESIDENT_BENEFICIARIES = I_("723");
   //Beneficiary's Date of Birth is missing
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_DOB_MISSING                             = I_("724");
   //Beneficiary's Gender is missing
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_GENDER_MISSING                          = I_("725");
   // Rebalancing status
   extern CLASS_EXPORT I_CHAR * const REBALANCING_STATUS                                  = I_("798");
   //settlement source is not updatable
   extern CLASS_EXPORT I_CHAR * const SETTLEMENT_SOURCE_IS_NOT_UPDATABLE                  = I_("913");
   // Deposit type not allowed for RedCode <%1>
   extern CLASS_EXPORT I_CHAR * const DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE                = I_("943");
   // Allowed Transfer is from LonckIn to Non LockedIn Registered
   extern CLASS_EXPORT I_CHAR * const LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED                    = I_("944");
   // Allowed Transfer is from LonckIn to Non Registered
   extern CLASS_EXPORT I_CHAR * const LOCKEDIN_TO_NON_REGISTED_ALLOWED                    = I_("945");
   // Redeem is not allowed for Assignment
   extern CLASS_EXPORT I_CHAR * const ASSIGNMENT_REDEEM_NOT_ALLOW                         = I_("946");
   // Direct order type not allowed for participant transfers
   extern CLASS_EXPORT I_CHAR * const ORDERTYPE_WIRE                                      = I_("947");
   // Wire order type not allowed for non-participant transfers
   extern CLASS_EXPORT I_CHAR * const ORDERTYPE_DIRECT                                    = I_("948");
   // AMS set-up not allowed if Stop Purchase or Stop Redemption
   extern CLASS_EXPORT I_CHAR * const AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM           = I_("950");
   // Fund Load Group not the same under AMS Allocation Set-up
   extern CLASS_EXPORT I_CHAR * const FUND_LOAD_GRP_TYPE_DIFF_FOR_AMS_ALLOC_SETUP         = I_("956");
   // AMS set-up not allowed for Institutional Account
   extern CLASS_EXPORT I_CHAR * const AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL             = I_("957");
   // Redemption code is not allowed for transfer
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_CODE_IS_NOT_ALLOWED                      = I_("959");
   // Can transfer only to RRSP and RRIF 
   extern CLASS_EXPORT I_CHAR * const CAN_TRANSFER_ONLY_TO_RRSP_RRIF                      = I_("960");
   // Private account flagging is only allowed for client accounts
   extern CLASS_EXPORT I_CHAR * const PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT            = I_("961");
   // AIM field is blank
   extern CLASS_EXPORT I_CHAR * const FIELD_IS_BLANK                                      = I_("967");
   // RESP NASU is not avaialable 
   extern CLASS_EXPORT I_CHAR * const RESP_NASU_NOT_AVAILABLE                             = I_("969");
   // Invalid MF Payment period.
   extern CLASS_EXPORT I_CHAR * const INVALID_MF_PAYMENT                                  = I_("974");
   // AMS Active Certificates exist
   extern CLASS_EXPORT I_CHAR * const AMS_ACTIVE_CERTS_EXIST                              = I_("975");
   // RO Effective Date cannot be modified 
   extern CLASS_EXPORT I_CHAR * const RO_EFF_DATE                                         = I_("976");
   // Stopdate cannot be futuredated
   extern CLASS_EXPORT I_CHAR * const FUTURE_DATED_STOPDATE                               = I_("977");
   // Duplicate Bank With Same Usage and Currency
   extern CLASS_EXPORT I_CHAR * const DUPLICATE_BANK_WITH_SAME_USAGE_AND_CURRENCY         = I_("979");
   // Unit trading not allowed.
   extern CLASS_EXPORT I_CHAR * const UNIT_TRADING_NOT_ALLOWED                            = I_("982");
   // Redemption is contrary to client guarantee guard protection setting rules.
   extern CLASS_EXPORT I_CHAR * const REDEMP_CONTRARY_CLIENT_GUAGUARD_PROTECTION          = I_("984");
   // Transfer is contrary to client guarantee guard protection setting rules.
   extern CLASS_EXPORT I_CHAR * const TRANSFER_CONTRARY_CLIENT_GUAGUARD_PROTECTION        = I_("985");
   // accounts have different sibling only flags
   extern CLASS_EXPORT I_CHAR * const DIFFERENT_SIBLINGONLY_STATUS                        = I_("987");
   // Regulatory Standard is blank
   extern CLASS_EXPORT I_CHAR * const BLANK_REG_STANDARD                                  = I_("990");
   // Paytype must be 'EFT to Redemption' if Pay Instruction Option is set to 'Redirect to Entity'
   extern CLASS_EXPORT I_CHAR * const PAYTYPE_MUST_EFT_FOR_BRKLV_PAYINS                   = I_("993");
   // Invalid Fund code for Fund on Fund Category
   extern CLASS_EXPORT I_CHAR * const INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND    = I_("1001");
   //Redemption  exceeds Grant Plus Earnings.
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_EXCEEDS_GRANT_PLUS_EARNINGS              = I_("1003");
   //EAP Amount exceeds Market Value.
   extern CLASS_EXPORT I_CHAR * const EAP_AMOUNT_EXCEEDS_MARKET_VALUE                     = I_("1004");
   // Account level AMS effective date
   extern CLASS_EXPORT I_CHAR * const ACCT_LVL_EFFECTIVE_DATE                             = I_("1005");
   // Shareholder tax jurisdiction or residence provice is unassigned
   extern CLASS_EXPORT I_CHAR * const SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED               = I_("1006");
   // NET Redemption minimum
   extern CLASS_EXPORT I_CHAR * const NET_REDEMPTION_OVER_MINIMUM                         = I_("1007");
   // Gross Redemption minimum applies
   extern CLASS_EXPORT I_CHAR * const GROSS_REDEMPTION_MINIMUM_APPLIES                    = I_("1008");
   // Demographics data are required
   extern CLASS_EXPORT I_CHAR * const DEMOGRAPHICS_DATA_REQUIRED                          = I_("1009");
   // Doclist data are required
   extern CLASS_EXPORT I_CHAR * const DOCUMENT_LIST_DATA_REQUIRED                         = I_("1010");
   //Fee Code is not defined, cannot store deducted fee
   extern CLASS_EXPORT I_CHAR * const FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE     = I_("1011");
   // Direct deposit bank use code is for shareholder banking only
   extern CLASS_EXPORT I_CHAR * const DIRECT_DEPST_SHRHLDR_ONLY                           = I_("1012");
   // Direct deposit bank use code is for Canadian Bank only
   extern CLASS_EXPORT I_CHAR * const DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY                 = I_("1013");
   // Direct deposit bank use code is for Canadian Dollar account only
   extern CLASS_EXPORT I_CHAR * const DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY        = I_("1014");
   // LWA Option of TO and TI sides do not match
   extern CLASS_EXPORT I_CHAR * const LWA_OPTION_NOT_MATCH                                = I_("1019");
   //Direct Deposit Banking and/or Investor Authorize missing
   extern CLASS_EXPORT I_CHAR * const DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING      = I_("1020");
   //There are investor authorization setup that missing direct deposit banking Information
   extern CLASS_EXPORT I_CHAR * const DIRECT_DEPOSIT_BANK_FOR_INVESTOR_AUTHORIZE_MISSING  = I_("1021");
   //There are direct deposit banking setup that missing investor authorization Information
   extern CLASS_EXPORT I_CHAR * const INVESTOR_AUTHORIZE_FOR_DIRECT_DEPOSIT_BANK_MISSING  = I_("1022");
   //Amount on the trade and total amount on settle instr do not match
   extern CLASS_EXPORT I_CHAR * const SETTL_LOC_IS_MISSING                                = I_("1023");
   // Federal tax rate is less than system calculated 
   extern CLASS_EXPORT I_CHAR * const RIF_FED_RATE_LESS_THAN_DEFAULT                      = I_("1025");
   // Provincial tax rate is less than system calculated 
   extern CLASS_EXPORT I_CHAR * const RIF_PROV_RATE_LESS_THAN_DEFAULT                     = I_("1026");
   // Unverfied Bank - Trade
   extern CLASS_EXPORT I_CHAR * const UNVERIFIED_BANK_TRADE                               = I_("1027");
   // Unverfied Bank - Settlement
   extern CLASS_EXPORT I_CHAR * const UNVERIFIED_BANK_SETTLEMENT                          = I_("1028");
   // Fund has a certificate units
   extern CLASS_EXPORT I_CHAR * const FUND_HAS_CERTIFICATE_UNITS                          = I_("1029");
   // Shareholder address information is not verified when user is placing trade
   extern CLASS_EXPORT I_CHAR * const SHAREHOLDER_ADDRESS_NOT_VERIFIED_FOR_TRADE          = I_("1030");
   // Shareholder address information is not verified when user is performing settlement for trade
   extern CLASS_EXPORT I_CHAR * const SHAREHOLDER_ADDRESS_NOT_VERIFIED_FOR_SETTLEMENT     = I_("1031");
   // Bank in use
   extern CLASS_EXPORT I_CHAR * const BANK_IN_USE                                         = I_("1032");
   // Traded Unit Position calculation error
   extern CLASS_EXPORT I_CHAR * const TUP_CALCULATION_ERROR                               = I_("1034");
   // Redemption TUP Oversell Message
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_TUP_OVERSELL                             = I_("1035");
   // Transfer TUP Oversell Message
   extern CLASS_EXPORT I_CHAR * const TRANSFER_TUP_OVERSELL                               = I_("1036");
   // Exchange TUP Oversell Message
   extern CLASS_EXPORT I_CHAR * const EXCHANGE_TUP_OVERSELL                               = I_("1037");
   // Insufficient QESI Grants.
   extern CLASS_EXPORT I_CHAR * const INSUFFICIENT_QESI_GRANTS                            = I_("1043");
   // No Lifetime Contribution Limits has been set up.
   extern CLASS_EXPORT I_CHAR * const NO_LIFETIME_CONTRIB_LIMIT_SET_UP                    = I_("1045");
   //CESG Amount to be returned because of this redemption
   extern CLASS_EXPORT I_CHAR * const CESG_AMOUNT_TO_BE_RETURNED                          = I_("1074");
   //This transaction will reduce the YTD contribution to negative
   extern CLASS_EXPORT I_CHAR * const YTD_CONTRIBUTION_WILL_BE_NEGATIVE                   = I_("1075");
   // RESP Plan Limit exceeded 
   extern CLASS_EXPORT I_CHAR * const RESP_PLAN_LIMIT_EXCEEDED                            = I_("216");
   // RESP Year Limit exceeded 
   extern CLASS_EXPORT I_CHAR * const RESP_YEAR_LIMIT_EXCEEDED                            = I_("217");
   // Beneficiary is over 21 
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_IS_OVER_21                              = I_("726");
   // Beneficiary is over 31 
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_IS_OVER_31                              = I_("999");
   //Life time grant limit exceeded
   extern CLASS_EXPORT I_CHAR * const QESI_LIFE_TIME_GRANT_LIMIT_EXCEEDED                 = I_("1042");
   //refund of special taxes
   extern CLASS_EXPORT I_CHAR * const REFUND_OF_SPECIAL_TAXES_EXCEED_REDEMPTION           = I_("1044");
   // Lifetime Contribution Limits not setup 
   extern CLASS_EXPORT I_CHAR * const LIFETIME_CONTRIB_LIMITS_NOT_SETUP                   = I_("1045");
   // Annual Contribution Limits not setup
   extern CLASS_EXPORT I_CHAR * const ANNUAL_CONTRIB_LIMITS_NOT_SETUP                     = I_("1046");
   // Beneficiary is not a resident of Quebec
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_NOT_QUEBEC_RESIDENT                     = I_("1061");
   // Beneficiary is greater than 18 years of age
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_IS_OVER_18                              = I_("1062");
   // Net annual Contribution for the year is zero
   extern CLASS_EXPORT I_CHAR * const NET_ANNUAL_CONTRIBUTION_IS_ZERO                     = I_("1063");
   // QESI Basic Limit exceeded for the year
   extern CLASS_EXPORT I_CHAR * const QESI_BASIC_LIMIT_EXCEEDED_FOR_YEAR                  = I_("1064");
   // QESI Increase Limit exceeded for the year
   extern CLASS_EXPORT I_CHAR * const QESI_INCREASE_LIMIT_EXCEEDED_FOR_YEAR               = I_("1065");
   // Redemption amount for Adjustment of QESI Basic has exceeded the total amount that was received
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_AMOUNT_FOR_ADJUSTMENT_OF_QESI_BASIC_HAS_EXCEEDED       = I_("1066");
   // Redemption amount for Adjustment of QESI Increase has exceeded the total amount that was received
   extern CLASS_EXPORT I_CHAR * const REDEMPTION_AMOUNT_FOR_ADJUSTMENT_OF_QESI_INCREASE_HAS_EXCEEDED    = I_("1067");
   // Assisted Contribution amount is more than the Unassisted amount available for the tax year
   extern CLASS_EXPORT I_CHAR * const ASSISTED_CONTRIBUTION_AMOUNT_MORE_THAN_UNASSISTED_AMOUNT          = I_("1068");
   // Beneficiary is not eligible for QESI Increase since Account is not siblingonly
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_NOT_ELIGIBLE_FOR_QESI_INCREASE_NOT_SIBLINGONLY        = I_("1069");
   // Trading on RESP account not allowed
   extern CLASS_EXPORT I_CHAR * const TRADING_ON_RESPACCT_NOT_ALLOWED                                   = I_("1070");
   // RESP specific edit check
   extern CLASS_EXPORT I_CHAR * const RESP_SPECIFIC_EDIT_CHECK_NOT_PERFORMED                            = I_("1071");
   // Duplicate NEQ
   extern CLASS_EXPORT I_CHAR * const DUPLICATE_NEQ                                                     = I_("1077"); 
   // Missing NEQ
   extern CLASS_EXPORT I_CHAR * const MISSING_NEQ                                                       = I_("1078"); 
   // Account Balance is less than transaction amount
   extern CLASS_EXPORT I_CHAR * const BALANCE_LESS_THEN_TRANS_AMOUNT                                    = I_("1080");
   // Beneficiary is not eligible for CLB
   extern CLASS_EXPORT I_CHAR * const BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT                            = I_("1081"); 
   // Assisted Contribution amount to be reversed is more than the Assisted amount available for the tax year
   extern CLASS_EXPORT I_CHAR * const ASSISTED_CONTRIBUTION_AMOUNT_MORE_THAN_AVAILABLE_ASSISTED_AMOUNT  = I_("1082");
   // QESI Grant Request not available for the Beneficiary in the Tax Year
   extern CLASS_EXPORT I_CHAR * const QESI_GRANT_REQUEST_NOT_AVAILABLE_FOR_BENEFICIARY                  = I_("1083");
   // QESI Amount cannot be greater than 10% of existing QESI Unassisted amount for the beneficiary and tax year
   extern CLASS_EXPORT I_CHAR * const QESI_AMOUNT_GREATER_THAN_10_PRCNT_OF_EXISTING_QESI_UNASSISTED_AMOUNT  = I_("1084");
   // DP 78,79,80,81 or RD Q1,Q2,Q3 are not allowed
   extern CLASS_EXPORT I_CHAR * const QESI_DP_RD_NOT_ALLOWED                                            = I_("1085");
   // Election of LWA Age Rate is only allowed When LWA rates between accounts is the same
   extern CLASS_EXPORT I_CHAR * const ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME         = I_("1086");
   // Amendment may be required.
   extern CLASS_EXPORT I_CHAR * const AMENDMENT_MAY_BE_REQUIRED                                         = I_("1088");
   // Adjustment may be required.
   extern CLASS_EXPORT I_CHAR * const ADJUSTMENT_MAY_BE_REQUIRED                                        = I_("1089");
   // Trade exist for Tax Year.
   extern CLASS_EXPORT I_CHAR * const TRADE_EXIST_FOR_TAX_YEAR                                          = I_("1090");
   // May need to add new Grant Request for applicable Tax Year.
   extern CLASS_EXPORT I_CHAR * const MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR                    = I_("1091");
   // May need to flip status to Request or create new request for applicable  Tax Year
   extern CLASS_EXPORT I_CHAR * const MAY_NEED_TO_FLIP_OR_NEW_REQUEST_MAY_BE_REQUIRED_FOR_TAX_YEAR      = I_("1093");
   // SIN Effective Date is mandatory.
   extern CLASS_EXPORT I_CHAR * const SIN_EFFECTIVE_DATE_IS_MANDATORY                     = I_("1094");  
   // Guarantee Guard not same between TO/TI accounts.
   extern CLASS_EXPORT I_CHAR * const GUAGUARD_NOT_SAME_BETWEEN_TO_TI                     = I_("1095");  
   // AIP Entity is not Canadian resident
   extern CLASS_EXPORT I_CHAR * const AIP_TO_NONRESIDENT_NOT_ALLOWED                      = I_("1097"); 
   // AIP Entity address is missing
   extern CLASS_EXPORT I_CHAR * const ENTITY_ADDRESS_IS_MISSING                           = I_("1099");   
   // System will trigger amendment and recalculate QESI notional balance for the tax year.
   extern CLASS_EXPORT I_CHAR * const SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE      = I_("1100");
   // SIN Effective date cannot be unknown.
   extern CLASS_EXPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN                = I_("1101");
   // SIN Effective date cannot be earlier than the Date of birth.
   extern CLASS_EXPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB      = I_("1102");
   // SIN Effective date cannot be a future date.
   extern CLASS_EXPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE            = I_("1103");
   // Redemption Amount has exceeded the total QESI Amount that was received.
   extern CLASS_EXPORT I_CHAR * const REDEMPT_AMT_EXCEEDED_QESI_AMT_RECEIVED              = I_("1107");
   // Account is being activated
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_IS_BEING_ACTIVATED                          = I_("1109");
   // To cancel trade that settle batch has prefix SP or DC. The cancel batch must be prefixed same as settle batch.
   extern CLASS_EXPORT I_CHAR * const CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC                 = I_("1114");   
   // This Social Code is not applicable.
   extern CLASS_EXPORT I_CHAR * const SOCIAL_CODE_NOT_APPLICABLE                          = I_("1115");
   // You must indicate if the transfer-in entails a full or partial RESP property to proceed.
   extern CLASS_EXPORT I_CHAR * const QESI_TOTAL_TRANSFER_FILED_IS_BLANK                  = I_("1118");   
   // Update Tax Jurisdiction History if beneficiary was a resident of Quebec on December 31 of the applicable
   //       historical year(s) and Create the QESI grant request for the applicable historical year(s).
   extern CLASS_EXPORT I_CHAR * const NON_TRUSTEE_UPDATE_HIST_INFO_REQ                    = I_("1119");
   // Date of death of the annuitant entity of account missing
   extern CLASS_EXPORT I_CHAR * const DOD_ENTITY_TYPE_MISSING                             = I_("1121");
   //Historical RESP transferred-in notional balances for the QESI can only be entered for a beneficiary who is associated with the transfer-in transaction.
   extern CLASS_EXPORT I_CHAR * const NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED                 = I_("1124"); 
   //  Account level RESP notional information is not entered.
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_NOTINALS_ARE_ZERO                           = I_("1125");

   extern CLASS_EXPORT I_CHAR * const BROKER_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME = I_("1126");
   // Loan Type is mandatory.
   extern CLASS_EXPORT I_CHAR * const LOAN_TYPE_MANDATORY                                 = I_("1127");
   // Duplicate Loan Types are not allowed.
   extern CLASS_EXPORT I_CHAR * const DUPLICATE_LOAN_TYPE                                 = I_("1128");
   // Loan Type only applicable for Escrow Entity.
   extern CLASS_EXPORT I_CHAR * const LOAN_TYPE_FOR_ESCROW                                = I_("1129");
   // Loan Number is mandatory.
   extern CLASS_EXPORT I_CHAR * const LOAN_NUM_MANDATORY                                  = I_("1130");
   // Duplicate Loan Numbers are not allowed.
   extern CLASS_EXPORT I_CHAR * const DUPLICATE_LOAN_NUM                                  = I_("1131");
   // Loan Number only applicable for Accountholder Entity.
   extern CLASS_EXPORT I_CHAR * const LOAN_NUM_FOR_ACCTHOLDER                             = I_("1132");
   // Portfolio UUID or Porfolio Plan UUID are required.
   extern CLASS_EXPORT I_CHAR * const PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED              = I_("1133");  
   // CESG limit of %WARNPARM141% has been exceeded.
   extern CLASS_EXPORT I_CHAR * const CESG_LIMIT_EXCEEDED                                 = I_("1136");   //P0185010.FN02.R01.02 - new field CESG Grant paid          
   // Loan Number only applicable for Accountholder of Escrow account.
   extern CLASS_EXPORT I_CHAR * const LOAN_NUMBER_FOR_ESCROW_ACCOUNT                      = I_("1151"); 
   // EAP Beneficiary address is missing
   extern CLASS_EXPORT I_CHAR * const BENEF_ADDRESS_IS_MISSING                            = I_("1152");  //P0185010.FN02.R02.01 - Delivering EAP written notice and tax info return             
   //Classes involved in the transaction do not belong to same Fund.
   extern CLASS_EXPORT I_CHAR * const FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND             = I_("1176");
   //F/X rate is not entered for the transaction
   extern CLASS_EXPORT I_CHAR * const FX_RATE_IS_EMPTY                                    = I_("1177");
   //Account is not eligible to trade in ERISA prohibited Fund/Class
   extern CLASS_EXPORT I_CHAR * const ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT   = I_("1178");
   //Transaction with Deposit code 100 cannot be placed
   extern CLASS_EXPORT I_CHAR * const DEPOSIT_TYPE_40_CANNOT_BE_PLACED                          = I_("1179");
   //Transaction with Redemption code 100 cannot be placed
   extern CLASS_EXPORT I_CHAR * const RED_CODE_40_CANNOT_BE_PLACED                              = I_("1180");
   //Payment Status cannot be blank.
   extern CLASS_EXPORT I_CHAR * const PAYMENT_STATUS_EMPTY                                      = I_("1181");
   //The trade will not be priced with Payment Status as �Payment Outstanding�
   extern CLASS_EXPORT I_CHAR * const PAYMENT_STATUS_IS_OUTSTANDING                             = I_("1182");
   //Days Basis cannot be blank.
   extern CLASS_EXPORT I_CHAR * const DAYS_BASIS_EMPTY                                          = I_("1183");
   //Input Data Type cannot be blank.
   extern CLASS_EXPORT I_CHAR * const INPUTDATATYPE_EMPTY                                       = I_("1184");
   //Index Value is entered between existing effective dates. Hurdle Rate will be calculated between <Start Date1> to <End Date1> and <Start Date 2> to <End Date 2>.
   extern CLASS_EXPORT I_CHAR * const VALUE_BETWEEN_TWO_REOCRDS                                 = I_("1185");
   //Hurdle Rate will be calculated between <Start Date> to <End Date>.
   extern CLASS_EXPORT I_CHAR * const HURDLE_CALCULATED                                         = I_("1186");
   //Hurdle Rate is entered between existing effective dates.
   extern CLASS_EXPORT I_CHAR * const HURDLE_BETWEEN_TWO_REOCRDS                                = I_("1187");
   //Hurdle Rate cannot be zero.
   extern CLASS_EXPORT I_CHAR * const HURDLE_RATE_ZERO                                          = I_("1188");
   //Index Value cannot be zero.
   extern CLASS_EXPORT I_CHAR * const VALUE_ZERO                                                = I_("1189");
   //Duplicate Hurdle.
   extern CLASS_EXPORT I_CHAR * const DUPLICATE_HURDLE_ENTRY                                    = I_("1166");

   //Rej Error 1200: User Defined CMD should be within minimum and maximum age restriction
   extern CLASS_EXPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE  = I_("1200");
   //Rej Error 1201: User Defined CMD should be at least greater than minimum term
   extern CLASS_EXPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM = I_("1201");
   //Rej Error 1202: User defined CMD cannot be greater than legal contract maturity date
   extern CLASS_EXPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE        = I_("1202");

   extern CLASS_EXPORT I_CHAR * const HKID_NRIC_HARD_STOP                                       = I_("1212");
   //Contract type and version is need to be setup first.
   extern CLASS_EXPORT I_CHAR * const CONTRACT_TYPE_AND_VERSION_REQUIRED                        = I_("1213");
   //BackDate: Cancel all transactions on or after %TRADE_DATE% or change tradedate.
   extern CLASS_EXPORT I_CHAR * const TRADE_NOT_ALLOWED_TO_CANCEL                               = I_("1214");
   //Cannot backdate trades before LE scheduled date.
   extern CLASS_EXPORT I_CHAR * const BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE                     = I_("1215");
   //Cannot backdate trades before LWA Option.
   extern CLASS_EXPORT I_CHAR * const BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA                    = I_("1216");
   //No valid contract for the original trade date.
   extern CLASS_EXPORT I_CHAR * const NO_VALID_CONTRACT_FOR_ORIGINAL_TRADE_DATE                 = I_("1217");
   //A reset has occured since the original trade.
   extern CLASS_EXPORT I_CHAR * const RESET_HAS_OCCURED                                         = I_("1218");
   //The trade is part of DM event - cannot cancel.
   extern CLASS_EXPORT I_CHAR * const DM_EVENT_HAS_OCCURED                                      = I_("1219");
   //Fund and class is not allowed to trade under the account.
   extern CLASS_EXPORT I_CHAR * const FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT                      = I_("1221");
   // Transfer between Tiered and Non-Tiered Account is not allowed
   extern CLASS_EXPORT I_CHAR * const TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED             = I_("1224");
   // LWA Age Rate is not applicable, event not allowed for the effective date
   extern CLASS_EXPORT I_CHAR * const LWA_AGE_RATE_IS_NOT_APPLICABLE                            = I_("1225");
   // Only client account is applicable to set up Employee/Agent funds relationship.
   extern CLASS_EXPORT I_CHAR * const EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT             = I_("1226"); 
   // Fund relationship cannot be changed to %ACCOUNT_TYPE% when account balance > 0.
   extern CLASS_EXPORT I_CHAR * const EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT                 = I_("1227");
   // Changing sales representative is not applicable for %ACCOUNT_TYPE% accounts.
   extern CLASS_EXPORT I_CHAR * const CHANGE_REPS_IS_NOT_APPLICABLE                             = I_("1228");
   // LWA election date is later than transfer date
   extern CLASS_EXPORT I_CHAR * const LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE                = I_("1229");
   // User defined maturity date is less than the minimum term
   extern CLASS_EXPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM             = I_("1230");
   //Employee/Agent Bonus Purchase is not applicable for %FUND_CATEGORY%.
   extern CLASS_EXPORT I_CHAR * const EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS = I_("1233");
   //Employee/Agent Bonus Purchase is only applicable for Employee/Agent accounts.
   extern CLASS_EXPORT I_CHAR * const EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT = I_("1234");
   //Reference no. is mandatory for this Source of Fund.
   extern CLASS_EXPORT I_CHAR * const REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND              = I_("1235");
   //Account KIID confirmation unavailable in iFast.
   extern CLASS_EXPORT I_CHAR * const KIID_ATTESTATION                                          = I_("1238");
   //Invalid - Transfer must be within the same Fund/Class
   extern CLASS_EXPORT I_CHAR * const TRANSFER_DIFFERENT_FUND_CLASS_NOT_ALLOWED                 = I_("1239");
   //The pay type for this source of fund should be suppress.
   extern CLASS_EXPORT I_CHAR * const SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE                 = I_("1240");
   //The Compensation Agent must be changed before changing the Service Agent.
   extern CLASS_EXPORT I_CHAR * const COMPENSATION_AGENT_MUST_BE_CHANGED                        = I_("1246");
   //Only one Compensation Agent is applicable for a FundSERV broker
   extern CLASS_EXPORT I_CHAR * const ONE_COMPENSATION_AGENT_IS_ALLOWED                         = I_("1247");
   //The Service Agent must be changed before changing the Compensation Agent.
   extern CLASS_EXPORT I_CHAR * const SERVICE_AGENT_MUST_BE_CHANGED                             = I_("1248");
   //The Service Agent will be automatically changed by the Compensation Agent.
   extern CLASS_EXPORT I_CHAR * const SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT               = I_("1249");
   //Guarantee Adjustment exists after trade date
   extern CLASS_EXPORT I_CHAR * const GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE              = I_("1251");

   extern CLASS_EXPORT I_CHAR * const VARIABLE_DSC_FEE_AMOUNT                                   = I_("1252");

   extern CLASS_EXPORT I_CHAR * const DIFFERENT_REG_AGENT										= I_("1253");

   //The Contract Maturity redumption should be 100%.
   extern CLASS_EXPORT I_CHAR * const CONTR_MATURITY_REDUMPTION_TO_BE_100_PERCENT               = I_("1254");

   extern CLASS_EXPORT I_CHAR * const DEFAULT_FUND_BRKR_REQUIRED_FOR_TRADE                      = I_("1256");
   //Adding new entity as 'Estate of Deceased' with non-estate account, not allowed
   extern CLASS_EXPORT I_CHAR * const UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT    = I_("1258");
   //ID number is not applicable for entity category 
   extern CLASS_EXPORT I_CHAR * const ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY             = I_("1259");
   //Country of Issue is required for Business Number and Trust Number
   extern CLASS_EXPORT I_CHAR * const COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER  = I_("1260");
   //Trust Account Number format is invalid
   extern CLASS_EXPORT I_CHAR * const TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID                    = I_("1261");
   //ID number is required for entity category
   extern CLASS_EXPORT I_CHAR * const ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY                   = I_("1262");
   //Cash instructions are not permitted for registered accounts.
   extern CLASS_EXPORT I_CHAR * const CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC                        = I_("1263");
   //Entity Category(EmployeeClass) is required
   extern CLASS_EXPORT I_CHAR * const ENTITY_CATEGORY_IS_REQUIRED                               = I_("1264");
   // QESI limit of grant has been exceeded.
   extern CLASS_EXPORT I_CHAR * const QESI_LIMIT_EXCEEDED                                       = I_("1287");
   extern CLASS_EXPORT I_CHAR * const DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV                    = I_("1284");
   extern CLASS_EXPORT I_CHAR * const DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC                     = I_("1286");
   //Transfer from one account to another account whose annuitant's ages are different, is not allowed.
   extern CLASS_EXPORT I_CHAR * const TRFX_AGE_DIFF_NOT_ALLOWED                                 = I_("1288");
   //The first trade into account must be transfer.
   extern CLASS_EXPORT I_CHAR * const FIRST_TRADE_MUST_BE_TRANSFER                              = I_("1289");
   //Tax ID Number is required for Individual. specific for FATCA
   extern CLASS_EXPORT I_CHAR * const ID_NUMBER_IS_REQUIRED_FOR_INDIVIDUAL                      = I_("1290");
   //Employer Number is required for Corporate. specific for FATCA
   extern CLASS_EXPORT I_CHAR * const EMPLOYER_NUMBER_IS_REQUIRED_FOR_CORPORATE                 = I_("1291");
   //DEAL DATE AND DEAL TIME with the UCITS Arrow UK project during trade entry/Modification/cancellation
   extern CLASS_EXPORT I_CHAR * const EVENT_RECIEPT_DATE_AND_TIME_EMPTY                         = I_("1294");
   // Service agent belongs to FundSERV broker, and identical with compensate agent, change by compensated agent screen 
   extern CLASS_EXPORT I_CHAR * const SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER                    = I_("1296");
   // funds\ classes are not allowed to exchanged
   extern CLASS_EXPORT I_CHAR * const FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE                        = I_("1303");
   // Fee Model Effective Date is not applicable to the tree
   extern CLASS_EXPORT I_CHAR * const FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC                   = I_("1304");
   // Waive paper can not be set to yes when other mailing types are all set to no
   extern CLASS_EXPORT I_CHAR * const WAIVE_PAPER_CANNOT_BE_YES                                 = I_("1305");
   // Mailing types can not all be set to no
   extern CLASS_EXPORT I_CHAR * const MAIL_OPTION_CANNOT_BE_ALL_NO                              = I_("1306");
   // there is ENOUGH contributions in the account to cover the charges, but NOT ENOUGH income
   extern CLASS_EXPORT I_CHAR * const EAP_REDEMPT_EXCEEDED_EARNING                              = I_("1307");
   // if consent is no not allow mail to be no
   extern CLASS_EXPORT I_CHAR * const MAIL_CANNOT_BE_NO_FOR_NO_WAIVE                            = I_("1308");
   // if there is no yes is any of mailing option not allow suppress to be yes
   extern CLASS_EXPORT I_CHAR * const NO_MAIL_TO_SUPPRESS                                       = I_("1309");
   // Do not allow to palce manual trade if UC or stock transfer for configured environment.
   extern CLASS_EXPORT I_CHAR * const INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES                  = I_("1318");
   // Fund Class Must be an AMS Parent Fund
   extern CLASS_EXPORT I_CHAR * const FUND_CLASS_MUST_BE_AMS_PARENT_FUND                           = I_("1319");
   // Parent Fund Class cannot be a part of Asset Allocation Mix
   extern CLASS_EXPORT I_CHAR * const PARENT_FUND_CLASS_CANNOT_BE_A_PART_OF_ASSET_ALLOCATION_MIX   = I_("1320");
   // The AMS Model is associated with another account under same shareholder
   extern CLASS_EXPORT I_CHAR * const THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR      = I_("1321");
   // Fee model code must belong to a valid comm group
   extern CLASS_EXPORT I_CHAR * const FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP             = I_("1323");
   // Fee model code must belong to a valid comm group or fund
   extern CLASS_EXPORT I_CHAR * const FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND     = I_("1324");
   // Benefeciary tax jurisdiction not same as the shareholder tax jurisdiction
   extern CLASS_EXPORT I_CHAR * const JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION                = I_("1326");
   // Transfer not allowed: Contract Type and/or contract version not the same
   extern CLASS_EXPORT I_CHAR * const TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME  = I_("1327");
   // Gender cannot be blank for NMCR Single Life contract
   extern CLASS_EXPORT I_CHAR * const GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT            = I_("1330");
   // Gender change is not allowed on elected NMCR Single Life contract
   extern CLASS_EXPORT I_CHAR * const GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT = I_("1331");
   // The selected Reporting FFI is active from %STARTDATE% to %STOPDATE%
   extern CLASS_EXPORT I_CHAR * const START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI                   = I_("1333");
   // format of user entry FATCA Global Intermediary Indentification number is invalid
   extern CLASS_EXPORT I_CHAR * const INVALID_GIIN_FORMAT                                             = I_("1334");
   // Multiple National Id is not allowed for an entity, no national id issued by same country overlapped as well
   extern CLASS_EXPORT I_CHAR * const MULTIPLE_NATIONAL_ID_NOT_ALLOWED                                = I_("1335");
   // Multiple GIIN is not allowed for an entity, no GIIN issued by same country overlapped as well
   extern CLASS_EXPORT I_CHAR * const MULTIPLE_GIIN_NOT_ALLOWED                                       = I_("1336");
   // Invalid or missing Annuitant Sex
   extern CLASS_EXPORT I_CHAR * const INVALID_OR_MISSING_ANNUITANT_SEX                                = I_("1342");
   // Pending or unsettled trade exists, Initial Next Draw Date cannot be changed
   extern CLASS_EXPORT I_CHAR * const PENDING_OR_UNSETTLED_TRADE_EXISTS                               = I_("1350");
   // The date must be equal or greater than current Cycle date + 3 business dates
   extern CLASS_EXPORT I_CHAR * const DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE   = I_("1352");
   //The date must be equal or earlier than end of the second month of the original Diploma commitment date
   extern CLASS_EXPORT I_CHAR * const DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE        = I_("1353");
   // Regulatory Document status needs to be manually updated
   extern CLASS_EXPORT I_CHAR * const REG_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED                     = I_("1354");
   // Transaction has been flagged as stop settlement.
   extern CLASS_EXPORT I_CHAR * const TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO                           = I_("1355");
   // Unassisted Balance $%UC_AMT% is less than Residual Unassisted $%RES_AMT%.
   extern CLASS_EXPORT I_CHAR * const UC_AMT_LESS_THAN_RES_AMT                                        = I_("1359");
   //Signature Date is required for the PAC Plan
   extern CLASS_EXPORT I_CHAR * const PAC_STOP_DATE_RESTRICTION                                       = I_("1360");
   //Signature Date later than the PAC Effective Date
   extern CLASS_EXPORT I_CHAR * const SIGNATURE_DATE_REQUIRED                                         = I_("1361");
   //Stop Date cannot be greater than the should be between %Current Business Date % and %Current PAC Stop Date% 
   extern CLASS_EXPORT I_CHAR * const SIGNATURE_DATE_LATER                                            = I_("1362");
   //PAC setup requires BIC banking Instructions for BAFF
   extern CLASS_EXPORT I_CHAR * const BIC_BANKING_MANDATORY_FOR_PAC                                   = I_("1363");
   //Subsequent trade exists in Omnibus account
   extern CLASS_EXPORT I_CHAR * const TRADE_EXITS_IN_OMNIBUS_ACCT                                     = I_("1367");
   //Full rollover indicated for an Omnibus Account
   extern CLASS_EXPORT I_CHAR * const FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT                         = I_("1368");
   //Fee model cannot be stopped before last fee model process date.
   extern CLASS_EXPORT I_CHAR * const FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE            = I_("1376");
   //Subsequent trade exists in Non Omnibus account
   extern CLASS_EXPORT I_CHAR * const TRADE_EXITS_IN_ACCT                                             = I_("1377");
   //The maximum fee rate is greater than %RATE%%
   extern CLASS_EXPORT I_CHAR * const THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN                            = I_("1378");
   //Distribution rates must sum up to the recent distribution
   extern CLASS_EXPORT I_CHAR * const SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION               = I_("1379");
   //Net setllement not allowed for puchase for chargeback fund
   extern CLASS_EXPORT I_CHAR * const NET_SETTLEMENT_NOT_ALLOWED_FOR_PURCHASE                         = I_("1380");
   //SAGES Assisted Contribution amount is zero
   extern CLASS_EXPORT I_CHAR * const SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO                      = I_("1382");
																									  
   extern CLASS_EXPORT I_CHAR * const DIFFERNT_SETTLESOURCE_THAN_CANCELLATION                         = I_("1385");
   extern CLASS_EXPORT I_CHAR * const SETTLE_TYPE_INDIVIDUAL_NOT_ALLOW_THROUGH_FUNDSERV               = I_("1384");
   extern CLASS_EXPORT I_CHAR * const BROKER_DIFFERENT_THAN_ACCOUNT_BROKER                            = I_("1388");
   extern CLASS_EXPORT I_CHAR * const SETTLE_NETWORK_APPLIED_TO_CANCELLATION_AND_REBOOK               = I_("1386");
   extern CLASS_EXPORT I_CHAR * const DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV    = I_("1387");
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED                        = I_("1390");

   //Trade date must be equal or greater than 01Jan2013
   extern CLASS_EXPORT I_CHAR * const TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF              = I_("1391");
   //Bene tax jurisdiction must be 'SK' as of the Trade date
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT                           = I_("1392");
   //SAGES Amount to be returned because of the redemption
   extern CLASS_EXPORT I_CHAR * const SAGES_AMOUNT_TO_BE_RETURNED                                     = I_("1393");
   //Account must be Sibling Only for SAGES
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES                          = I_("1395");

   extern CLASS_EXPORT I_CHAR * const SETTLE_TYPE_BLOCK_NOT_ALLOW_NOT_THROUGH_FUNDSERV                = I_("1398");
   //Termination not allowed. SAGES Balance is greater than zero.
   extern CLASS_EXPORT I_CHAR * const TERMINATION_NOT_ALLOWED_SAGES_BALANCE_GREATER_THAN_ZERO         = I_("1399");
   //Allocation option not available (in this environment).
   extern CLASS_EXPORT I_CHAR * const ALLOCATION_OPTION_NOT_AVAILABLE                                 = I_("1400");
   //Invalid Amount Type for transaction type
   extern CLASS_EXPORT I_CHAR * const INVALID_AMOUNT_TYPE_BY_SEG_RULES                                = I_("1401");
   //Related Party cannot be a Corporate.
   extern CLASS_EXPORT I_CHAR * const RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE                         = I_("1403");
   //Tax Payer Status Reason is missing.
   extern CLASS_EXPORT I_CHAR * const TAX_PAYER_STATUS_REASON_IS_MISSING                              = I_("1404");
   //Related Party can be only Individual.
   extern CLASS_EXPORT I_CHAR * const RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL                            = I_("1411");
   //The annuitants for the From and To account must be the same.
   extern CLASS_EXPORT I_CHAR * const ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME                         = I_("1412");
   //The annuitant for the To account must be at least 50 years of age.
   extern CLASS_EXPORT I_CHAR * const ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS                 = I_("1413");

   extern CLASS_EXPORT I_CHAR * const CROSS_SYSTEM_ACCT_NUM_EMPTY                                     = I_("1571");
   
   extern CLASS_EXPORT I_CHAR * const FUND_IN_FOREIGN_CURRENCY                                        = I_("1572");

   extern CLASS_EXPORT I_CHAR * const FUND_CLASS_NOT_APPLICABLE                                       = I_("1573");
   // Service Only SlsRep is not permitted for new accounts.
   extern CLASS_EXPORT I_CHAR * const SERVICE_ONLY_SALES_REP                                          = I_("1577");

   extern CLASS_EXPORT I_CHAR * const GAP_BETWEEN_FEE_SCALES                                          = I_("1682");
   //Transmitter number format incorrect.
   extern CLASS_EXPORT I_CHAR * const TRANSMITTER_NUMBER_FORMAT_INCORRECT                             = I_("1683");
   //Tax Exempth Authorization's stop date is 31/12/9999
   extern CLASS_EXPORT I_CHAR * const TAX_EXEMPT_AUTH_STOPDATE_NOT_VALID                              = I_("1685");
   //Transfer-out transaction must be cancelled prior to this operation
   extern CLASS_EXPORT I_CHAR * const TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION                 = I_("1688");
   //Additional Account Number must be setup in Identification
   extern CLASS_EXPORT I_CHAR * const ADDITIONAL_ACCTNUM_MUST_BE_SETUP_IN_IDENTIFICATION              = I_("1689");
   //Cancellation not allowed due to Notional Balance going Negative
   extern CLASS_EXPORT I_CHAR * const CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE		  = I_("1701");
   //Transaction date must be greater than program start date 
   extern CLASS_EXPORT I_CHAR * const RESP_TRANSACTION_DATE_MUST_BE_GREATER_THAN_PROGRAM_START_DATE	  = I_("1702");
   //Suppression Reason code cannot be blank..
   extern CLASS_EXPORT I_CHAR * const SUPRESSION_CODE_EMPTY                                           = I_("1703");
   //The Allocation RESP fund transfer is not allowed to transfer the Residual Grant
   extern CLASS_EXPORT I_CHAR * const RESP_RESIDUAL_GRANT_TRANSFER_NOT_ALLOWED                        = I_("1704");
   //Account must be Sibling Only for BCTESG
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG                         = I_("1710");
   //Amount exceeds BCTESG balance
   extern CLASS_EXPORT I_CHAR * const AMOUNT_EXCEEDS_BCTESG_BALANCE									  = I_("1711");
   //Transfer in trades with BCTESG amount cannot be processed before August 15, 2015
   extern CLASS_EXPORT I_CHAR * const TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF		  = I_("1712");
    //SIF REGULATION VALIDATION..
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_NOT_SIF_ELIGABLE                                        = I_("1706");
   // Country of exposure is required for politically exposed person
   extern CLASS_EXPORT I_CHAR * const COUNTRY_OF_EXPOSURE_IS_REQUIRED                                 = I_("1713");
   // Transaction is awaiting a response from HRSDC hence cannot change allocations.
   extern CLASS_EXPORT I_CHAR * const TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS	  = I_("1714");
   // Bene tax jurisdiction must be 'BC' as of the Trade date.
   extern CLASS_EXPORT I_CHAR * const BENEFICIARY_NOT_BC_RESIDENT									  = I_("1715");
   // account level ams model cannot hold global model funds(parent fund)
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS                = I_("1737");
   // only child fund can be added to allocation
   extern CLASS_EXPORT I_CHAR * const ONLY_CHILD_FUND_CAN_BE_ADDED_TO_ALLOCATION                      = I_("1738");
   //The parent fund class is different from the parent fund class on the current global AMS model.
   extern CLASS_EXPORT I_CHAR * const PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL                           = I_("1739");
   //The receiving account's global AMS model does not contain this global AMS model child fund class.
   extern CLASS_EXPORT I_CHAR * const RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD   = I_("1740");
   //A pending trade exists on the parent fund class.
   extern CLASS_EXPORT I_CHAR * const PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS                        = I_("1741");
   //A pending trade exists on one of the child fund classes.
   extern CLASS_EXPORT I_CHAR * const PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS                  = I_("1742");
   //The receiving account and relinquishing account are linked to different AMS models.
   extern CLASS_EXPORT I_CHAR * const RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL  = I_("1743");
   //An unsettled trade exists on one of the child fund classes.
   extern CLASS_EXPORT I_CHAR * const UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES             = I_("1744");
   //A pending parent-to-parent full exchange exists.
   extern CLASS_EXPORT I_CHAR * const PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS                      = I_("1745");
   //The receiving account is linked to a different global AMS model.
   extern CLASS_EXPORT I_CHAR * const RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL                         = I_("1746");
   //The current global AMS model does not contain this child fund class.
   extern CLASS_EXPORT I_CHAR * const CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS             = I_("1747");
   // parent fund is not allowed
   extern CLASS_EXPORT I_CHAR * const PARENT_FUND_IS_NOT_ALLOWED                                      = I_("1748");
   // stopping ams model require full money out trade
   extern CLASS_EXPORT I_CHAR * const STOPPING_AMS_MODEL_REQUIRE_FULL_MONEY_OUT_TRADE                 = I_("1749");
   //Trading on a global AMS model parent fund class is not allowed, as the account is not linked to any global model.
   extern CLASS_EXPORT I_CHAR * const TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS = I_("1751");
   //Redemption Fund class value overriden 
   extern CLASS_EXPORT I_CHAR * const FUND_CLASS_GROSS_NET_FOR_REDEMPTION_OVERIDDEN                   = I_("1756");
   // PSE Information is required for this redemption.
   extern CLASS_EXPORT I_CHAR * const PSE_INFORMATION_REQUIRED                                        = I_("1757");
   // Enter amounts with negative sign (-) on redemption and paid out column.
   extern CLASS_EXPORT I_CHAR * const NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE                               = I_("1759");
   // Broker %BROKER_CODE% is not eligible for fund class %FUND%/%CLASS%.
   extern CLASS_EXPORT I_CHAR * const BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS							  = I_("1760");
   // Sale rep %BROKER_CODE% %SLSREP_CODE% is not eligible for fund class %FUND%/%CLASS%.
   extern CLASS_EXPORT I_CHAR * const SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS						  = I_("1761");
   // planholder does not meet the minimum age requirement for this particular registered account
   extern CLASS_EXPORT I_CHAR * const PLANHOLDER_MINIMUM_AGE_LIMIT                                    = I_("1762");
   // when user left field external institution as blank for a specific combination of taxtype and redcode or deptype
   extern CLASS_EXPORT I_CHAR * const EXTINSTITUTION_NAME_NOT_PROVIDED                                = I_("1781");
   // when user enter an invalida external institution code
   extern CLASS_EXPORT I_CHAR * const INVALID_INSTITUTION_CODE                                        = I_("1782");
   // Trading on a child fund class is not allowed, as the account is not linked to any global model.
   extern CLASS_EXPORT I_CHAR * const TRADING_ON_CHILD_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS = I_("1783");
   // LTD Contribution must be equal to the total of Pre-1998 + CESG Assisted + CESG Unassisted amounts
   extern CLASS_EXPORT I_CHAR * const LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC				  = I_("1786");
   // The QESI Pre Feb 2007 is not equal to LTD - QESI AC - QESI UC - QESI YTD.
   extern CLASS_EXPORT I_CHAR * const QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD		  = I_("1790");
   // ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN
   extern CLASS_EXPORT I_CHAR * const ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN				  = I_("1792");
   // PLAN_CANNOT_BE_MANUALLY_CREATED
   extern CLASS_EXPORT I_CHAR * const PLAN_CANNOT_BE_MANUALLY_CREATED               				  = I_("1793");
   // ONLY_DOLLAR_AMOUNT_IS_ALLOWED_FOR_CUSTOM_PAYOUT
   extern CLASS_EXPORT I_CHAR * const ONLY_DOLLAR_AMOUNT_IS_ALLOWED_FOR_CUSTOM_PAYOUT 				  = I_("1794");
   // NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP
   extern CLASS_EXPORT I_CHAR * const NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP				  = I_("1795");
   // ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS
   extern CLASS_EXPORT I_CHAR * const ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS				  = I_("1806");
   // ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM
   extern CLASS_EXPORT I_CHAR * const ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM				  = I_("1807");
   // AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE
   extern CLASS_EXPORT I_CHAR * const AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE				              = I_("1809");
   // AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP
   extern CLASS_EXPORT I_CHAR * const AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP				  = I_("1810");
   // AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP
   extern CLASS_EXPORT I_CHAR * const AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP				      = I_("1811");
   // FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT
   extern CLASS_EXPORT I_CHAR * const FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT				          = I_("1812");
   // FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT
   extern CLASS_EXPORT I_CHAR * const FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT				      = I_("1813");
   // FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT
   extern CLASS_EXPORT I_CHAR * const FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT				  = I_("1814");
   // Pending trade exists.
   extern CLASS_EXPORT I_CHAR * const SETTLEMENT_RULE_PENDING_TRADE_EXISTS							  = I_("1815");
   // Stop date must be earlier than current business date.
   extern CLASS_EXPORT I_CHAR * const SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE = I_("1816");
   // Settle date less then fund level settle date.
   extern CLASS_EXPORT I_CHAR * const SETTLEDATE_LESS_THEN_FUND_LEVEL_SETTLEDATE					  = I_("1890");   
   // Seg event
   extern CLASS_EXPORT I_CHAR * const SEG_EVENT_DURING_CREATE_TRADE                                   = I_("1904");
   // Settle days less then Fund level Settle Days
   extern CLASS_EXPORT I_CHAR * const SETTLEDAYS_LESS_THEN_FUND_LEVEL_SETTLEDAYS                      = I_("1963");
   // CESG, ADCESG Amount to be returned because of this redemption
   extern CLASS_EXPORT I_CHAR * const CESG_ADCESG_AMOUNT_TO_BE_RETURNED								  = I_("1906");

   extern CLASS_EXPORT I_CHAR * const ABSOLUTE_VALUE_THRESHOLD_BREACHED                               = I_("1935");
   extern CLASS_EXPORT I_CHAR * const PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED                           = I_("1936");
   extern CLASS_EXPORT I_CHAR * const PERCENTAGE_OF_TRADES_AMOUNT_TYPE                                = I_("1938");
   extern CLASS_EXPORT I_CHAR * const INITIAL_MONEY_IN_TO_A_CLASS                                     = I_("1939");
   extern CLASS_EXPORT I_CHAR * const DUPLICATE_ALREADY_EXIST                                         = I_("1940");
   extern CLASS_EXPORT I_CHAR * const PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY                        = I_("1937");
   
   // Cash Date Mandatory
   extern CLASS_EXPORT I_CHAR * const CASH_DATE_MANDATORY                                             = I_("1941");
   // Trade will create negative notional balance in UC, AC or YTD Amount.
   extern CLASS_EXPORT I_CHAR * const TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD			  = I_("1952");
   // Account rounding rules are mandatory.
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_ROUNDING_RULE_MANDATORY								  = I_("1954");

   //Share class
   extern CLASS_EXPORT I_CHAR * const FUND_COMPANY_APPROVAL_REQUIRED								  = I_("1956");
   extern CLASS_EXPORT I_CHAR * const GENERAL_AGREEMENT_NOT_AVAILABLE                                 = I_("1957");

   extern CLASS_EXPORT I_CHAR * const AMOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT				  = I_("1958");

   // Account Rounding Rules record already exists.
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_ROUNDING_RULE_EXISTS									  = I_("1960");
   // Pending or processed trade exists, account rounding rule cannot be added/modified.
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_ROUNDING_RULE_TRADE_EXISTS							  = I_("1961");
   // Firstname is required
   extern CLASS_EXPORT I_CHAR * const FIRSTNAME_MANDATORY                                 			  = I_("1962");
   // annuitant/successor annuitant date of birth is changing
   extern CLASS_EXPORT I_CHAR * const ANNUITANT_DOFBIRTH_IS_CHANGING                                  = I_("1964");
   // Update of transfer notional values for a cancelled and/or reversed trade is not allowed.
   extern CLASS_EXPORT I_CHAR * const NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED = I_("1966");
   // Manual Override of notionals is recommended for multiple transfers.
   extern CLASS_EXPORT I_CHAR * const NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS	  = I_("1967");
   // Transfer out or Grant repayment transaction exists in the account. Manual override may be required.
   extern CLASS_EXPORT I_CHAR * const NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED						  = I_("1968");  
   // PIM and Institutional accounts must be added to the Account Custodian 
   extern CLASS_EXPORT I_CHAR * const PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN						  = I_("1976");
   // DIF fund only allow direct order 
   extern CLASS_EXPORT I_CHAR * const DIF_FUND_ONLY_ALLOW_DIRECT_ORDER								  = I_("1977");
   // Bonus Interest Rate can be setup only for DIF fund
   extern CLASS_EXPORT I_CHAR * const BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND					  = I_("1978");
   // Paid By Other Institution is a balance and must be positive.
   extern CLASS_EXPORT I_CHAR * const NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE				  = I_("1979");
   //validation for tax file number
   extern CLASS_EXPORT I_CHAR * const INVALID_TFN_VALUE												  = I_("1982");
   //validation for Australian business number
   extern CLASS_EXPORT I_CHAR * const INVALID_ABN_VALUE												  = I_("1983");
   // Unreversed Termination Entries exist that may need to be reversed and reprocessed.
   extern CLASS_EXPORT I_CHAR * const UNREVERSED_TERMINATION_ENTRIES_EXIST							  = I_("2007");
   //The Dilution Link ID will be automatically generated
   extern CLASS_EXPORT I_CHAR * const DILUTION_LINK_ID_AUTO_GENERATE								  = I_("2006");
   //Only one record with 100% accountability is allowed for a dealer or an intermediary.
   extern CLASS_EXPORT I_CHAR * const ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED							  = I_("2040");
   //Fundserv (Settle) Dilution and External Sys Pymt via N$M are mutually exclusive; only one can be set to “Yes”.
   extern CLASS_EXPORT I_CHAR * const DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES						  = I_("2045");
   // Beneficiary must be a Canadian resident.
   extern CLASS_EXPORT I_CHAR * const RDSP_BENEFICIARY_NON_RESIDENT									  = I_("2049");
   // Beneficiary must be no more than 59 years of age.
   extern CLASS_EXPORT I_CHAR * const RDSP_BENEFICIARY_OVER_AGE_LIMIT								  = I_("2050");
   // RDSP Primary Care Giver is mandatory as beneficiary is age 18 years or less.        
   extern CLASS_EXPORT I_CHAR * const RDSP_PCG_ENTITY_MUST_BE_SETUP									  = I_("2051");
   extern CLASS_EXPORT I_CHAR * const DUPLICATE_BUSINESS_NUMBER                                       = I_("2053");
   // Beneficiary tax jurisdiction must be Canadian at the trade effective date.
   extern CLASS_EXPORT I_CHAR * const RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA					  = I_("2071");
   // RDSP Beneficiary is over the age of contribution.
   extern CLASS_EXPORT I_CHAR * const RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION						  = I_("2072");   
   extern CLASS_EXPORT I_CHAR * const TRADING_SUSPENSION_ACTIVE_FOR_FUND							  = I_("2074");
   // validation for pending trade date
   extern CLASS_EXPORT I_CHAR * const  PENDING_ALLOCATION_NOT_ALLOWED_TRADE							  = I_("2087"); //INC0039323
   // Trade not allowed for a RDSP account SDSP elect.
   extern CLASS_EXPORT I_CHAR * const RDSP_TRADE_NOT_ALLOWED_ACCOUNT_SDSP_ELECT						  = I_("2090");
   // Trade not allowed for a RDSP account DTC elect.
   extern CLASS_EXPORT I_CHAR * const RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT						  = I_("2091");
   // RDSP Registration Status doesn't allow contributions.
   extern CLASS_EXPORT I_CHAR * const RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS						  = I_("2092");
   // Trade date is after Beneficiary's Date of Death.
   extern CLASS_EXPORT I_CHAR * const RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH				  = I_("2093");
   // RDSP Maximum Contributions LTA exceeded.
   extern CLASS_EXPORT I_CHAR * const RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED							  = I_("2094");	
   // Relationship between Accountholder and RDSP Beneficiary must be specified.
   extern CLASS_EXPORT I_CHAR * const RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED						  = I_("2116");
   // Only 2 RDSP Primary Caregivers are allowed.
   extern CLASS_EXPORT I_CHAR * const RDSP_ONLY_TWO_PCG_ALLOW										  = I_("2117"); 
   // RDSP Beneficiary can not be more than one.
   extern CLASS_EXPORT I_CHAR * const RDSP_ONLY_ONE_BENF_ALLOW										  = I_("2118");
   // Attention Fund subject to liquidity gating measure.
   extern CLASS_EXPORT I_CHAR * const FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE                        = I_("2129");
   extern CLASS_EXPORT I_CHAR * const FUND_SUBJECT_TO_LIQUIDITY_FEE_MEASURE                           = I_("2130");
   // External RDSP Account Contract Number is mandatory.
   extern CLASS_EXPORT I_CHAR * const RDSP_EXTERNAL_CONTRACT_MANDATORY								  = I_("2140");
   // External RDSP Specimen Plan Number is mandatory.
   extern CLASS_EXPORT I_CHAR * const RDSP_EXTERNAL_PLAN_MANDATORY									  = I_("2141");
   // Cannot backdate the trade before the Money-out transaction.        
   extern CLASS_EXPORT I_CHAR * const RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS				  = I_("2180");
   // Repayment reason must be specified on RDSP withdrawal.        
   extern CLASS_EXPORT I_CHAR * const RDSP_REPAYMENT_REASON_MANDATORY								  = I_("2181");
   // Invalid Repayment Reason.        
   extern CLASS_EXPORT I_CHAR * const RDSP_INVALID_REPAYMENT_REASON									  = I_("2183");  
   // FMV is less than AHA amount, payment may be rejected.        
   extern CLASS_EXPORT I_CHAR * const RDSP_FMV_LESS_THAN_AHA_AMOUNT									  = I_("2184");
   // Repayment reason does not match for DAP.       
   extern CLASS_EXPORT I_CHAR * const RDSP_DAP_INVALID_REPAYMENT_REASON								  = I_("2185");
   // Repayment reason does not match for LDAP.        
   extern CLASS_EXPORT I_CHAR * const RDSP_LDAP_INVALID_REPAYMENT_REASON							  = I_("2186");
   // Repayment reason does not match for All Funds Full Withdrawal.       
   extern CLASS_EXPORT I_CHAR * const RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON					  = I_("2187");
   // Invalid Repayment Reason.        
   extern CLASS_EXPORT I_CHAR * const RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX								  = I_("2188");
   // RDSP Internal Error - Please contact API owner.
   extern CLASS_EXPORT I_CHAR * const RDSP_API_TIMEOUT												  = I_("2194");
   // RDSP Transfer Out transaction cannot be processed earlier than an existing transaction.
   extern CLASS_EXPORT I_CHAR * const RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED						  = I_("2206");
   // Partial transfers not permitted for RDSP accounts.
   extern CLASS_EXPORT I_CHAR * const RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED							  = I_("2209");
   // Money Out Transactions exist after Date of Payment.
   extern CLASS_EXPORT I_CHAR * const RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT				  = I_("2217");   
   // Email Phone Details cannot be blank
   extern CLASS_EXPORT I_CHAR * const EMAIL_PHONE_CANNOT_BE_BLANK                                     = I_("2220");
   extern CLASS_EXPORT I_CHAR * const BIC_CODE_LINKED_MSG                                             = I_("2222");
   // Invalid cash date.
   extern CLASS_EXPORT I_CHAR * const INVALID_CASH_DATE												  = I_("2240");
   // Overridden cash date should be greater than or equal to trade date.
   extern CLASS_EXPORT I_CHAR * const CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE						  = I_("2241");
   // Please note cash date will remain as assigned.
   extern CLASS_EXPORT I_CHAR * const CASH_DATE_WILL_REMAIN_AS_ASSIGNED								  = I_("2242");
   // Insufficient grant/bond balance, repayment may reject.
   extern CLASS_EXPORT I_CHAR * const RDSP_INSUFFICIENT_GRANT_BOND_BALANCE							  = I_("2243");
   // Grant Return amount cannot be greater than the grant purchase amount.
   extern CLASS_EXPORT I_CHAR * const RDSP_GRANT_RETURN_CANNOT_BE_GREATER_THAN_GRANT_PURCHASE		  = I_("2254");
   // Bond Return amount cannot be greater than the bond purchase amount.
   extern CLASS_EXPORT I_CHAR * const RDSP_BOND_RETURN_CANNOT_BE_GREATER_THAN_BOND_PURCHASE			  = I_("2255");
   // Account has unverified data
   extern CLASS_EXPORT I_CHAR * const ACCOUNT_HAS_UNVERIFIED_DATA                                     = I_("2256");
   // RDSP Beneficiary's Date of Birth is missing.
   extern CLASS_EXPORT I_CHAR * const RDSP_BENEFICIARY_DOFBIRTH_MISSING								  = I_("2266");
}
   
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastids/ifasterrorids.cpp-arc  $
// 
//    Rev 1.123   Aug 16 2012 10:12:18   wp040027
// IN#3008167-P187485-CPF- Account Entity (RA) validation
// 
//    Rev 1.122   Jul 25 2012 15:54:08   wp040240
// IN3014673 - P0181067 Added Error condition to avoid cash instructions  to registered client accounts
// 
//    Rev 1.121   Jul 23 2012 17:03:46   dchatcha
// P0179630 FN01 FATCA Project - Entity level.
// 
//    Rev 1.120   Jul 12 2012 19:10:12   dchatcha
// P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
// 
//    Rev 1.119   Jul 10 2012 18:10:12   wp040039
// PETP0201166- SSBG- Fund Broker validation
// 
//    Rev 1.118   Jun 26 2012 22:11:44   popescu
// IN#2948564 - Error condtions for Contract maturity Instrucitons screen added. 
// 
//    Rev 1.117   Jun 26 2012 17:26:26   if991250
// DSC Scale at Contract level
// 
//    Rev 1.116   Jun 26 2012 14:17:54   wp040240
// IN#2948564 - Error condtions for Contract maturity Instrucitons screen added. 
// 
//    Rev 1.115   Jun 18 2012 17:29:20   if991250
// Added    VARIABLE_DSC_FEE_AMOUNT
// 
//    Rev 1.114   Jun 01 2012 15:41:02   dchatcha
// IN#2952786 - Err Msg when keying Purchase Before Guarantee Adjustment- Trade Entry Screen
// 
//    Rev 1.113   May 25 2012 11:06:26   if991250
// added rej errors 1200, 1201, 1202
// 
//    Rev 1.112   May 16 2012 16:48:16   wp040132
// P0195754_FN01_ KIID_UCITs - KIID Validation - Included error no 1238
// 
//    Rev 1.111   May 11 2012 18:26:32   dchatcha
// P0186479 FN10 - Gap 14G - Block Service Unit Transfers.
// 
//    Rev 1.110   May 10 2012 10:06:26   dchatcha
// P0186479 FN10 - Gap 14G - Block Service Unit Transfers, fix typo!
// 
//    Rev 1.109   May 08 2012 16:55:52   dchatcha
// P0186479 FN10 - Gap 14G - Block Service Unit Transfers.
// 
//    Rev 1.108   May 03 2012 00:11:58   panatcha
// P0186486_FN15_The Source of Funds.
// 
//    Rev 1.107   Apr 27 2012 20:28:06   wp040132
// P0197311 - Error message display for transfer order of different fund/class.
// 
//    Rev 1.106   Apr 20 2012 03:00:04   panatcha
// P0186486_FN15_The Source of Funds.
// 
//    Rev 1.105   Apr 10 2012 00:22:00   panatcha
// P0186486FN09 - Employee and Agent Account Gap#8A
// 
//    Rev 1.104   Apr 04 2012 20:58:32   wp040039
// PETP0187485-Entity Maintenance
// 
//    Rev 1.103   Mar 29 2012 23:12:36   dchatcha
// IN#2901157 - Issues on SEG Trade Processing
// 
//    Rev 1.102   Mar 23 2012 06:37:48   panatcha
// P0186486FN09 - Employee and Agent Account Gap#8A
// 
//    Rev 1.101   Mar 16 2012 13:30:44   dchatcha
// P0186484 FN05 - SEG Trade Processing, new validations.
// 
//    Rev 1.100   Mar 05 2012 11:13:06   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.99   Jan 20 2012 15:32:50   wp040027
// P0188394_Performance Fees - Order Entry 
// 
//    Rev 1.98   Jan 16 2012 13:42:40   wp040027
// P0188394_Performance Fees - Benchmark Upload/Trade Search/ERISA
// 
//    Rev 1.97   Oct 25 2011 06:11:04   panatcha
// IN2708311 - New Error Message should be "Beneficiary Address is Missing
// 
//    Rev 1.96   Oct 14 2011 03:04:20   kitticha
// PETP0186486 FN01 IN2685299 - RRSP Loan program issues.
// 
//    Rev 1.95   Oct 06 2011 10:54:04   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.94   Oct 04 2011 18:10:08   dchatcha
// P0186477 FN01 - GIA Enhancements, display validate portfolio fields based on environment functionality(UAF).
// 
//    Rev 1.93   Sep 02 2011 13:12:18   kitticha
// PETP0186486 FN01 - RRSP Loan Program.
// 
//    Rev 1.92   Aug 03 2011 11:15:14   wp040027
// P0186774 - Mutual Fund Order Processing
// 
//    Rev 1.91   Jul 20 2011 18:13:24   dchatcha
// P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
// 
//    Rev 1.90   Jul 14 2011 08:16:58   panatcha
// DRAFT - IN2584478, IN5285248, IN2591262 
// 
//    Rev 1.89   Jun 28 2011 09:48:40   panatcha
// P0184541_FN01_InvescoQESItrans
// 
//    Rev 1.88   Apr 21 2011 07:44:38   kitticha
// PETP0181067 FN00 IN2483647 - SSG Social Code enhancement.
// 
//    Rev 1.87   Apr 05 2011 06:42:38   kitticha
// PETP0181067_FN00_IN2460780_Empire Autobatch Development on Cancelled SP and DC trades.
// 
//    Rev 1.86   Feb 07 2011 18:58:06   dchatcha
// Synch up: Incident 2409562 - Fix to return warning message for DOFB changes
// 
//    Rev 1.85   Jan 31 2011 15:50:52   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.84   Dec 17 2010 00:17:58   panatcha
// PET0168296FN09 - TFSA Cancellation: Add new code for Stop Reason field and Rej-Error for changing account status from Terminated to Active.
// 
//    Rev 1.83   Nov 26 2010 09:34:34   kitticha
// IN#2291872 - Release 99, QESI project. Q1 and Q2 redemption cannot deplete more than balance.
// 
//    Rev 1.82   Nov 04 2010 10:43:04   kitticha
// IN#2314478 - P173756FN02- No message display when processing transfer.
// 
//    Rev 1.81   Oct 28 2010 06:41:52   kitticha
// PET0165541 FN03 - QESI Phase3
// 
//    Rev 1.80   Oct 07 2010 11:34:02   jankovii
// PET0175377 FN01 AIP for Joint RESP Account
// 
//    Rev 1.79   Sep 17 2010 06:42:08   kitticha
// PETP0173756 FN02 Don't Bust the Rules.
// 
//    Rev 1.78   May 27 2010 05:11:40   kitticha
// PETP0165541 FN02 QESI Phase2 - Add additional rejerror 1085.
// 
//    Rev 1.77   May 27 2010 05:02:34   kitticha
// PETP0165541 FN02 QESI Phase2.
// 
//    Rev 1.76   May 14 2010 16:17:24   jankovii
// IN 2117956 - PET165541-Grant can be entered in RESP Transfer Info screen when sibling only=no
// 
//    Rev 1.75   May 06 2010 03:19:32   dchatcha
// PET0165541 FN01 QESI RESP Trading, wrong number for reject error code!
// 
//    Rev 1.74   Apr 30 2010 15:33:04   popescu
// RES-QESI Trading - PSE/EAP work
// 
//    Rev 1.73   Apr 27 2010 10:33:14   kitticha
// PET0165541 FN01 QESI RESP Trading - Additional errors.
// 
//    Rev 1.72   Apr 26 2010 12:30:44   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.71   Apr 22 2010 10:20:00   kitticha
// PET0165541 FN01 QESI RESP Trading - Remove duplicate error 1074.
// 
//    Rev 1.70   Apr 21 2010 15:35:20   jankovii
// PET0165541 FN01 QESI Trading.
// 
//    Rev 1.69   Apr 21 2010 12:14:04   dchatcha
// PET0165541 FN01 QESI Trading.
// 
//    Rev 1.68   Apr 19 2010 14:50:08   jankovii
// PET0165541 FN01 QESI Trading.
// 
//    Rev 1.67   Apr 19 2010 07:55:56   dchatcha
// PET0165541 FN01 QESI Trading.
// 
//    Rev 1.66   Apr 16 2010 09:38:08   kitticha
// PET0165541 FN01 QESI Trading.
// 
//    Rev 1.65   Apr 14 2010 16:39:14   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.64   Apr 07 2010 09:59:58   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.63   Mar 27 2010 19:52:28   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.62   Mar 22 2010 14:57:32   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.61   Mar 12 2010 14:17:22   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.60   Mar 05 2010 15:54:26   jankovii
// PET165541 FN01 - QESI - RESP Gap.
// 
//    Rev 1.59   Dec 18 2009 10:37:50   jankovii
// PET0166095 FN01 Validations on Money Out Transactions
// 
//    Rev 1.58   Dec 03 2009 02:46:10   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2.
// 
//    Rev 1.57   Nov 17 2009 15:16:16   jankovii
// PET0166583 FN01 Static Data Changes Banking 
// 
//    Rev 1.56   Nov 10 2009 09:44:44   jankovii
// PET0166583 FN01 Static Data Changes_Banking information
// 
//    Rev 1.55   Oct 26 2009 16:27:30   jankovii
// PET157825 FN08 FN11 FN14 AMS Gaps
// 
//    Rev 1.54   Sep 23 2009 02:45:02   dchatcha
// IN#1825476 - error raised instead of warning.
// 
//    Rev 1.53   Aug 11 2009 12:04:12   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.52   Jul 30 2009 18:33:56   dchatcha
// Synch up : IN#1611516 - New edit at desktop trade level to prevent enter redemption, if there is improper default fee setup.
// 
//    Rev 1.51   Jul 08 2009 07:31:50   dchatcha
// PET 156681 - FN 14 - Investor Authorization.
// 
//    Rev 1.50   Apr 24 2009 04:56:02   dchatcha
// Synch up : IN 1653090 - The KYC screen need to made mandatory in the NASU process.
// 
//    Rev 1.49   Apr 13 2009 14:56:24   jankovii
// PET 158825  FN04 - Manula RRIF Redemption.
// 
//    Rev 1.48   Mar 06 2009 11:45:44   jankovii
// IN 1549352 - RESIDENCE PROVINCE AND TAX JURISDICTION
// 
//    Rev 1.47   Jan 30 2009 10:25:18   jankovii
// IN 1543838 - AMS Rebalancing - AMS Mstr Setup -R91 - QA Testing
// 
//    Rev 1.46   Oct 28 2008 05:20:50   phiwponp
// PET22486FN45 - Fund on Funds Account Report.
// 
//    Rev 1.45   23 Sep 2008 16:19:30   kovacsro
// PET 142007 FN01 TFSA
// 
//    Rev 1.44   Aug 04 2008 05:25:52   daechach
// in# 1222816 - Pay Instruction Field No Longer Displayed. (check in for Noom)
// 
//    Rev 1.43   Jul 16 2008 10:07:12   jankovii
// PET 59888 - AML Enhancemement.
// 
//    Rev 1.42   Dec 05 2007 15:04:30   jankovii
// IN 1098016 - Desktop Account Level AMS screen 'Status' Field.
// 
//    Rev 1.41   Oct 24 2007 19:09:52   smithdav
// IN1024380 - AMSAcctLevel active Certificates edit.
// 
//    Rev 1.40   19 Oct 2007 16:21:44   kovacsro
// IN#1038318 - added rej erros / hard edit to prevent users from entering future dated Stop dates on AMS and modifying Effective Date for RB/RO default allocations on Allocation screen
// 
//    Rev 1.39   Sep 16 2007 15:47:52   jankovii
// IN #990336 - User is unable to process manual/adhoc MFR trades.
// 
//    Rev 1.38   Aug 09 2007 09:40:06   kovacsro
// PET2360 FN29 RESP
// 
//    Rev 1.37   Jul 27 2007 17:30:12   kovacsro
// PET 2372 FN02 FDP-AIM KYC
// 
//    Rev 1.36   Jul 18 2007 09:34:46   smithdav
// PET2360 FN02
// 
//    Rev 1.35   28 Jun 2007 16:42:40   popescu
// AIM GAP 63 - BKK synch-up estate processing
// 
//    Rev 1.34   28 Jun 2007 10:03:20   popescu
// PET 2236 - Gap 50 - Private act
// 
//    Rev 1.33   27 Jun 2007 23:58:10   popescu
// PET 2236 - Gap 50 - Private act
// 
//    Rev 1.32   Jun 27 2007 11:50:02   porteanm
// PET 2360 FN02 - AMS - New errors 956 and 957.
// 
//    Rev 1.31   May 09 2007 16:05:16   jankovii
// MT54X PET2321 FN03 -Participant Transfer.
// 
//    Rev 1.30   Feb 27 2007 15:10:36   ZHANGCEL
// Incident #728172 -- Add RejError for Redeem allowed for Assignment
// 
//    Rev 1.29   Nov 27 2006 16:50:38   ZHANGCEL
// Incident #706688 -- Add error conditons for Locked in Transfer
// 
//    Rev 1.28   Sep 30 2006 00:55:04   popescu
// Incident 720294 - pay entity eff. dates
// 
//    Rev 1.27   Sep 05 2006 19:05:50   popescu
// Incident# 693254 - settlement source field opened for TR/XR
// 
//    Rev 1.26   Aug 28 2006 15:42:46   ZHANGCEL
// PET2212 FN10 -- Added new errorID for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.25   Jun 06 2006 17:27:56   porteanm
// PET 2102 FN01 - Added 444 and 450.
// 
//    Rev 1.24   May 24 2006 12:43:08   jankovii
// PET 2102 FN02 - Manulife Flex - Trade/Systematic Entry.
// 
//    Rev 1.23   May 02 2006 14:27:04   jankovii
// PET 2102 Manulife Flex - User Defined Maturity Dates.
// 
//    Rev 1.22   Dec 20 2005 14:47:24   jankovii
// Incident #496604 - Support Vestima Trading for SSBG.
// 
//    Rev 1.21   Jul 06 2005 16:28:10   porteanm
// PET1171 EUSD 1B - Rej error 464.
// 
//    Rev 1.20   Jun 24 2005 16:13:02   popescu
// Incident 332074 - Duplicate SIN rej-error. - rej-error code 467
// 
//    Rev 1.19   Jun 23 2005 14:38:18   porteanm
// Incident 332074 - Duplicate SIN rej-error.
// 
//    Rev 1.18   Mar 10 2005 10:31:16   porteanm
// Incident 243157/243387 - Settle Source validation.
// 
//    Rev 1.17   Jan 27 2005 20:25:06   popescu
// PET 1117/66/67/68.
// 
//    Rev 1.16   Jan 18 2005 12:54:02   popescu
// PTS 10037935, added new rej-error code to control whether bank information country code is mandatory or not
// 
//    Rev 1.15   Jan 11 2005 18:01:22   popescu
// PTS 10037687, modifyed error code
// 
//    Rev 1.14   Nov 30 2004 20:10:44   popescu
// PET 1117/06
// 
//    Rev 1.13   Nov 29 2004 20:31:10   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.12   Nov 29 2004 09:50:24   popescu
// PET 1117/06, more errors
// 
//    Rev 1.11   Nov 23 2004 12:46:52   aguilaam
// PET1117_FN21: settlement instructions enhancement
// 
//    Rev 1.10   Nov 23 2004 12:36:32   popescu
// PET 1117/06, new error ids
// 
//    Rev 1.9   Nov 19 2004 14:18:04   popescu
// PET 1117/56, third party funds processing
// 
//    Rev 1.8   Nov 15 2004 14:03:28   popescu
// PET 1117/06, new error ids
// 
//    Rev 1.7   Nov 07 2004 15:04:40   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.6   Nov 04 2004 17:42:18   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.5   Oct 28 2004 09:50:04   popescu
// PET 1117/06, Trade processing, new error codes
// 
//    Rev 1.4   Oct 27 2004 12:03:28   popescu
// PET 1117/06, Trade processing, new error codes
// 
//    Rev 1.3   Sep 30 2004 21:01:44   popescu
// PET 1117/06, SSB Germany - Trade Processing, added a new namespace for pay types and couple of error codes
 * 
**/
