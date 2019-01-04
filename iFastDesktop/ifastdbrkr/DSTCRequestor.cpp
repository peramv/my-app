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
//
//******************************************************************************
//
// ^FILE   :  DSTCRequestor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include <bfconmgr\bfrecordconnection.hpp>
#include <bfconmgr\bfconnectionmanager.hpp>
#include <bfdbrkr\bfhost.hpp>
#include <conditionmanager.hpp>
#include <configmanager.hpp>
#include <bfdbrkr\dbrkrlogger.hpp>
#include "dstchost.hpp"
#include "dstcrequest.hpp"
#include "dstcrequestbuffer.hpp"
#include "dstcrequestor.hpp"
#include "dstcresponsebuffer.hpp"
#include "dstcsecurity.hpp"
#include <bfutil\bfhrtimer.hpp>

#include <assert.h>

namespace DSTC_REQUEST
{
   extern CLASS_EXPORT const DSTCRequest LOGON;
}

//data dictionary stuff needed for the security and view calls
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId MoreAvailable;
   extern CLASS_IMPORT const BFNumericFieldId RepeatCount;
   extern CLASS_IMPORT const BFTextFieldId NextKey;
   extern CLASS_IMPORT const BFTextFieldId SessionId;
   extern CLASS_IMPORT const BFTextFieldId User_Id;
   extern CLASS_IMPORT const BFTextFieldId LanguageCode;
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
}

namespace CND
{
   extern const I_CHAR *IFASTDBRKR_CONDITION;

   extern const long IFASTDBRKR_NOT_LOGGED_ON;
   extern const long IFASTDBRKR_TRANS_FAILED;

   // Conditions used
   extern const long ERR_UNKNOWN_ERROR;
   extern const long ERR_DATA_NOT_FOUND;
   // Access denied, section
   extern const long ERR_AD_AFTER_MANDATORY_LOGOFF_TIME;
   extern const long ERR_AD_BEFORE_ALLOWABLE_LOGON_TIME;
   extern const long ERR_AD_INVALID_PASSWORD;
   extern const long ERR_AD_INVALID_PROFILE;
   extern const long ERR_AD_MAXIMUM_SESSIONS_ALREADY_RUNNING;
   extern const long ERR_AD_NO_COMPANY_ACCESS;
   extern const long ERR_AD_PAST_PASSWORD_GRACE_PERIOD;
   extern const long ERR_AD_PROFLE_HAS_NO_ACCESS_TODAY;
   extern const long ERR_AD_SHAREHOLDER_DOES_NOT_EXIST;
   extern const long ERR_AD_TOO_MANY_FAILED_LOGONS;
   extern const long ERR_AD_UNKNOWN_ACCESS_PROFILE;
   extern const long ERR_AD_UNKNOWN_USER;
   extern const long ERR_AD_USER_ACCOUNT_NOT_ACTIVE;
   extern const long ERR_AD_USER_HAS_NO_COMPANY_ACCESS;
   //End Access denied, section }
   extern const long ERR_COULD_NOT_CREATE_THE_SHAREHOLDER_REMARKS_RECORD;
   extern const long ERR_EFT_PAYMENT_DETAILS_NOT_FOUND;
   extern const long ERR_INVALID_PROFILE;
   extern const long ERR_NO_MATCHES_FOUND;
   //{ Password denied, section
   extern const long ERR_PD_THREE_OF_SAME_CHARS_NOT_ALLOWED;
   extern const long ERR_PD_CANNOT_CHANGE_PASSORD_FOR;
   extern const long ERR_PD_HAS_BEEN_USED_RECENTLY_CHOOSE_ANOTHER;
   extern const long ERR_PD_NEED_TWO_OR_MORE_NON_ALPHA_CHARS;
   extern const long ERR_PD_NEED_TWO_OR_MORE_ALPHABETIC_CHARS;
   extern const long ERR_PD_NO_BLANKS_ALLOWED;
   extern const long ERR_PD_OLD_PASSWORD_INCORRECT;
   extern const long ERR_PD_ONLY_ONE_REPETITION_OF_CHARS_ALLOWED;
   extern const long ERR_PD_ONLY_SEVEN_CHARS_IN_A_ROW;
   extern const long ERR_PD_PASSWORD_CAN_ONLY_BE;
   extern const long ERR_PD_PASSWORD_MUST_BE_AT_LEAST;
   extern const long ERR_PD_UNKNOWN_ACCESS_PROFILE;
   extern const long ERR_PD_UNKNOWN_USER;
   //End Password denied, section }
   extern const long ERR_TRANSACTION_NOT_FOUND;
   extern const long ERR_UNKNOWN_ACCOUNT;
   extern const long ERR_UNKNOWN_START_DATE;
   extern const long ERR_JOINT_INFORMATION_ONLY_FOR_JOINT_ACCOUNTS;
   extern const long ERR_PENDING_TRADE_NOT_FOUND;
   extern const long ERR_TRADE_NOT_FOUND;
   extern const long ERR_CHEQUE_NOT_FOUND;
   extern const long ERR_ACCOUNT_ENTITY_NOT_FOUND;
   extern const long ERR_ENTITY_NOT_FOUND;
   extern const long ERR_REGISTERED_ADDRESS_DEFAULT_NOT_FOUND;
   extern const long ERR_BROKER_NOT_FOUND;
   extern const long ERR_INTERMEDIARY_NOT_FOUND;
   extern const long ERR_ENTITY_NOT_ASSOCIATED_WITH_AN_ACCOUNT;
   extern const long ERR_ACCOUNT_NUMBER_IS_INVALID;
   extern const long ERR_NOT_ENOUGH_INPUT_INFO_FOR_RECORD_SELECTION;
   extern const long ERR_SALESREP_CANNOT_ACCESS_THIS_ACCOUNT;
   extern const long ERR_PLEASE_SEND_AGAIN_AS_LAST_RECORD_WAS_DELETED;
   extern const long ERR_INVALID_FUND_CODE;
   extern const long ERR_NEXT_KEY_DID_NOT_MATCH_EXPECTED_FORMAT;
   extern const long ERR_NO_INTEREST_ACCRUAL_INFORMATION_AVAILABLE;
   extern const long ERR_AS_OF_DATE_WAS_NOT_ENTERED;
   extern const long ERR_INVALID_CLASS_CODE;
   extern const long ERR_NO_ADDRESS_RECORD_AVAILABLE;
   extern const long ERR_NO_ADDRESS_RECORD_AVAILABLE;
   extern const long ERR_INVALID_CHUIR;
   extern const long ERR_CLAN_PLAN_NOT_AVAILABLE;
   extern const long ERR_NO_RELATED_CHUI_FUNCTIONS;
   extern const long ERR_NO_RESP_ACCOUNT_INFORMATION;
   extern const long ERR_ALLFUNDS_OR_FUND_CLASSCODE;
   extern const long ERR_NO_SETUP_RECORD;
   extern const long ERR_INPUT_ACCOUNT_IS_NOT_RESP;
   extern const long ERR_INPUT_ACCOUNT_IS_NOT_RIF;
   extern const long ERR_NO_RIF_SETUP_INFO;
   extern const long ERR_NO_RIF_ALLOCATION_INFO;
   extern const long ERR_PASSWORD_DENIED_CHANGE_NO_ALLOWED;
   extern const long ERR_RECORD_LOCKED;
   extern const long ERR_UNABLE_TO_UPDATE_RECORD;
   extern const long ERR_UNABLE_TO_DELETE_LAST_ADDRESS;
   extern const long ERR_UNABLE_TO_ADD_RECORD_ADDRESS_EXISTS;
   extern const long ERR_REGISTER_ADDRESS_NOT_AVAILABLE;
   extern const long ERR_NO_BENEFICIARY_RECORD_AVAILABLE;
   extern const long ERR_NO_ESCROW_REP_RECORD_AVAILABLE;
   extern const long ERR_NON_JOINT_ACCOUNT_ONE_ACCOUNTHOLDER;
   extern const long ERR_ACCOUNT_MAY_ONLY_HAVE_ONE_NOMINEE_OWNER;
   extern const long ERR_CLIENT_ACCOUNT_CANNOT_HAVE_A_NOMINEE_OWNER;
   extern const long ERR_UNABLE_TO_DELETE_RECORD;
   //extern const int ERR_NO_MESSAGE;
   extern const long ERR_NO_JOINT_ENTITY_RECORD_AVAILABLE;
   extern const long ERR_NOT_AN_EFT_TRANSACTION;
   extern const long ERR_INVALID_GROUP;
   extern const long ERR_INVALID_SHAREHOLDER;
   extern const long ERR_UNABLE_TO_ADD_RECORD_ACCOUNT_EXISTS;
   extern const long ERR_SHAREHOLDER_NUMBER_GREATER_THEN_ZERO;
   extern const long ERR_SHAREHOLDER_NUMBER_NOT_GREATER_THEN_SIX_DIGITS;
   extern const long ERR_INVALID_MRS_ACCOUNT;
   extern const long ERR_INVALID_GROUP_CODE;
   extern const long ERR_UNABLE_TO_ADD_RECORD_SHAREHOLDER_EXISTS;
   extern const long ERR_ADDRESS_USED_FOR_MAILING;
   extern const long ERR_RUN_MODE_INVALID;
   extern const long ERR_CONTROLS_NAME_RECORD_ENTITYID_NOT_FOUND;
   extern const long ERR_UNABLE_TO_DELETE_ENTITY;
   extern const long ERR_UNABLE_TO_MODIFY_ENTITY;
   extern const long ERR_IDENTIFICATION_RECORD_NOT_EXIST;
   extern const long ERR_INVALID_ID_TYPE;
   extern const long ERR_USER_ACCESS_RECORD_NOT_FOUND;
   extern const long ERR_USER_STATUS_IS_INACTIVE_IN_COMPANY_DB;
   extern const long ERR_ACCT_UPDATE_FAILED_AS_ACCTENTITY_UPDATE_FAILED;
   extern const long ERR_WRONG_SHRHOLDER_VERSION;
   extern const long ERR_PERSISTENT_NEEDED;
   extern const long ERR_NO_ACTIVE_BATCH;
   extern const long ERR_NO_SLSREP_FOUND;
   extern const long ERR_NO_BRANCH_FOUND;
   extern const long ERR_DUPLICATE_DISTRIBUTION;
   extern const long ERR_DISTRIBUTION_IS_LOCKED;
   extern const long ERR_DISTRIBUTION_NOT_FOUND;
   extern const long ERR_WRONG_DISTRIBUTION_VERSION;
   extern const long ERR_DISTRIBANK_IS_LOCKED;
   extern const long ERR_DISTRIBANK_NOT_FOUND;
   extern const long ERR_WRONG_BANK_VERSION;
   extern const long ERR_DUPLICATE_SYSTEMATIC;
   extern const long ERR_DUPLICATE_AUTO_TRANSFER;
   extern const long ERR_NO_ACCESS_TO_SLSREP;
   extern const long ERR_DATE_OF_BIRTH_MANDATORY;
   extern const long ERR_MATURITY_DATE;
   extern const long ERR_MISSING_ALLOCATION_INFO;
   extern const long ERR_NO_CLAN_PLAN_UPDATE;
   extern const long ERR_NO_FUTURE_DATE_MIN_MAX;
   extern const long ERR_INVALID_SORT_BY;
   extern const long ERR_INVALID_REQUEST_TYPE;
   extern const long ERR_DATA_PROBLEM_MISSING_PRICE;
   extern const long ERR_NO_MAILING_INFO_AVAILABLE;
   extern const long ERR_NO_ACCT_CONTRACT_AVAILABLE;
   extern const long ERR_REMARKS_NO_FOUND;
   extern const long ERR_BANKACCT_NOT_FOUND; 
   extern const long ERR_ACCT_ENTITY_BENEF_NOT_FOUND;
   extern const long ERR_ACCT_ENTITY_JOINT_NOT_FOUND;
   extern const long ERR_ASSIGN_INFO_NOT_FOUND;
   extern const long ERR_SECURITY_SETUP_NOT_FOUND;
   extern const long ERR_FUND_INFO_NOT_FOUND;
   extern const long ERR_NO_ACCOUNT_SHR_NUMBER;
   extern const long ERR_PROGRESS_ERROR;
   extern const long ERR_SEARCH_FOR_SLSREP_BY_BROKER_CODE;
   extern const long ERR_TAX_TYPES_RULES_NOT_SET_UP;
   extern const long ERR_PENSION_INFORMATION_NA;
   extern const long ERR_THIS_TAX_TYPE_NOT_LOCKED_IN;
   extern const long ERR_NO_PENDING_TRADES_FOUND;
   extern const long ERR_NO_PROCESSED_TRADES_FOUND;
   extern const long ERR_ACCESS_DENIED_NO_SESSION_RECORD;
   extern const long ERR_ACCESS_DENIED_PASSWORD_MUST_BE_RESET;
   extern const long ERR_ACCESS_DENIED_PASS_LOGOFF_TIME;
   extern const long ERR_BANK_RECORD_SHOULD;
   extern const long ERR_DISTRIB_NA;
   extern const long ERR_TRANSACTION_TYPE_INVALID;
   extern const long ERR_ADDRID_NOT_FOUND;
   extern const long ERR_ENTITY_ADDR_NA;
   extern const long ERR_ENTITY_ADDR_XREF_NA;
   extern const long ERR_PROVINCE_FILE_NA;
   extern const long ERR_DEALER_FUNDS_NA;
   extern const long ERR_ADDRESS_CODE_AT_LEAST_TWO;
   extern const long ERR_INST_CODE_EXCEEDS;
   extern const long ERR_TRANSIT_NO_EXCEEDS;
   extern const long ERR_BANK_ACC_NUMERIC;
   extern const long ERR_BANK_ACC_MUST_BE_ENTERED;
   extern const long ERR_BANK_ACC_EXCEEDS;
   extern const long ERR_ERROR_UPD_BANK_TABLE;
   extern const long ERR_CANNOT_DELETE_ACCOWNER;
   extern const long ERR_FUND_RECORD_NA;
   extern const long ERR_FEE_RECORD_NA;
   extern const long ERR_TRANSNUM_ALREADY_EXISTS;
   extern const long ERR_PENDING_TRADE_NOT_EXISTS;
   extern const long ERR_PENDING_TRADE_BANK_INVALID;
   extern const long ERR_INVALID_DEPOSIT_ID;
   extern const long ERR_BATCH_CANNOT_BE_BLANK;
   extern const long ERR_BATCH_NOT_ACTIVE;
   extern const long ERR_INVALID_TRANSID_CURRENCY_FOR_TRANBANKING;
   extern const long ERR_INVALID_BROKER_CODE;
   extern const long ERR_NOT_VALID_FUND;
   extern const long ERR_CLOSEACCTCODE_NOT_FUND;
   extern const long ERR_WITHOUT_FULL_REDEMPTION;
   extern const long ERR_NO_ACCOUNTHOLDING;
   extern const long ERR_UNITS_NOT_ALLOWED;
   extern const long ERR_FULL_REDEMPTION_NOT_ALLOWED;
   extern const long ERR_REDEMPTIONCODE_NOT_AVAILABLE;
   extern const long ERR_INVALID_FUND_AND_CLASS;
   extern const long ERR_AMOUNT_GREATER;
   extern const long ERR_BROKER_NOT_ELIGIBLE;
   extern const long ERR_DATABASE_UNAVAILABLE;
   extern const long ERR_DATABASE_NOT_CONNECTED;
   extern const long ERR_NO_COMPANY_RECORD;
   extern const long ERR_UNKNOW_RESPONSE_TYPE;
   extern const long ERR_CANNOT_PRINT_DUPLICATE;
   extern const long ERR_NO_USERID;
   extern const long ERR_NO_UNIQE_NAME_FOUND;
   extern const long ERR_ACCOUNTENTITY_ALREADY_EXISTS;
   extern const long ERR_AMOUNT_SHOULD_MANDATORY;
   extern const long ERR_NO_ENOUGH_INPUT;
   extern const long ERR_BATCHTYPE_INVALID;
   extern const long ERR_BATCHNAME_SHOULD_BLANK;
   extern const long ERR_BATCHNAME_CANNOT_BLANK;
   extern const long ERR_INVALID_FUND_GROUP_TYPE;
   extern const long ERR_ACCOUNTENTITY_NOT_FOUND;
   extern const long ERR_CONTRACT_RECORD_NOT_FOUND;
   extern const long ERR_CYCLE_RUN_UNAVAILABLE;
   extern const long ERR_NO_CONTRACTMSTR;
   extern const long ERR_NO_COT_CONTRACT_SHGROUP;
   extern const long ERR_UNABLE_MODIFY_COT_ACCT_CONTRACT;
   extern const long ERR_RRIFINFO_ALREADY_EXISTS;
   extern const long ERR_INVALID_CALLNUM;
   extern const long ERR_BANKMST_UNAVAILABLE;
   extern const long ERR_BATCHES_NOT_MATCH;
   extern const long ERR_NO_PURCHASE;
   extern const long ERR_RRIF_DETAIL_RECID_INVALID;
   extern const long ERR_UNITDETL_NOT_FOUND; 
   extern const long ERR_POSTAL_CODE_NOT_FOUND;
   extern const long ERR_INSUFFICIENT_INFO;
   extern const long ERR_STREET_NAME_NOT_FOUND;
   extern const long ERR_BOX_NUM_NOT_FOUND;
   extern const long ERR_APARTMENT_NUM_MISSING;
   extern const long ERR_MULITIPLE_ADDRESS; 
   extern const long ERR_INVALID_ADDRESS;
   extern const long ERR_NO_TAXTYPE_AVAILABLE;
   extern const long ERR_INVALID_DEPOSIT_TYPE;
   extern const long ERR_ENTITYTYPE_MUST_POPULATED;
   extern const long ERR_ORIGTRANSLD_MUST_BLANK;
   extern const long ERR_NOT_CONFIGURED; 
   extern const long ERR_SEQNUM_NOT_EXIST;
   extern const long ERR_TIME_ZONE_INVALID;
   extern const long ERR_FINANCIAL_TIMEZONE_INVALID;
   extern const long ERR_UNABLE_ASSIGN_CONNUM;
   extern const long ERR_WRONG_BANKENTITY;
   extern const long ERR_BROKER_NOT_ENTERED;
   extern const long ERR_BROKER_BRANCH_NOT_ENTERED;
   extern const long ERR_BROKER_BRANCH_SLSREP_NOT_ENTERED;
   extern const long ERR_BROKER_SLSREP_NOT_ENTERED;

   extern const long ERR_BANK_INFO_IS_MANDATORY_FOR_EFT;
   extern const long ERR_INVALID_CODE_TYPE;
   extern const long ERR_RECIPIENT_INFO_NOT_SET_UP;
   extern const long ERR_NO_DEP_ID_RECORDS_AVAILABLE;
   extern const long ERR_INVALID_RESON_CODE;
   extern const long ERR_ACTIVE_CONTRACT_EXISTS;
   extern const long ERR_INVALID_BANKTYPE;
   extern const long ERR_BANKTYPE_IDNUM_NOT_ENTERED;
   extern const long ERR_FUNDTO_CLASSTO_CANNOT_BLANK_FOR_TRANSFERS;
   extern const long ERR_SPLITCOM_FEE_DEF_NOT_FOUND;
   extern const long ERR_FEES_WAIVED;
   extern const long ERR_NO_COMM_SCALE_RECORD_AVAILABLE;
   extern const long ERR_FEE_PARAMS_NOT_AVAILABLE;
   extern const long ERR_LAST_BANK_TYPE_MUST_BE;
   extern const long ERR_ACCT_NUM_BLANK_FOR_TRANSPENDING;
   extern const long ERR_TRANSPENDING_MUST_BE;
   extern const long ERR_FUND_NOT_ELIGIBLE_FOR_COMMISSION;
   extern const long ERR_INVALID_VALIDATION_TYPE;
   extern const long ERR_TAX_TYPE_NOT_FOUND;
   extern const long ERR_DUPLICATE_CONTRACT;
   extern const long ERR_CYCLE_RUNNING;
   extern const long ERR_TRADE_DATE_FUTURE;
   extern const long ERR_INVALID_REPEAT_RECORD_TYPE;
   extern const long ERR_PLAN_CODE_NOT_FOUND;
   extern const long ERR_CANNOT_DELETE_CONTRACT_ACCOUNT_ACTIVITY;
   extern const long ERR_SPLITCOM_EXISTS;
   extern const long ERR_ACCOUNT_SPLITCOMM_NOT_FOUND;
   extern const long ERR_USERTYPE_DOES_NOT_HAVE_ACCESS;
   extern const long ERR_SECURITY_PROFILE_DOES_NOT_HAVE_ACCESS;
   extern const long ERR_EFFECTIVE_DATE_PRIOR_TO_LAST_RUN;   
   extern const long ERR_TRANSFER_NOT_BUY_OR_SELL;
   extern const long ERR_TRANSIT_NUMBER_MUST_BE_ENTERED;
   extern const long ERR_AMT_LESS_THAN_MIN_INIT_REDEMP;
   extern const long ERR_AMT_MAY_LESS_THAN_MIN_INIT_REDEMP;
   extern const long ERR_AMT_IS_LESS_THAN_MIN_SUBSEQ_REDEMP;
   extern const long ERR_AMT_MAY_LESS_THAN_MIN_SUBSEQ_REDEMP;
   extern const long ERR_FUNDCLASS_BAL_LESS_THAN_MIN;
   extern const long ERR_FUNDCLASS_BAL_MAY_LESS_THAN_MIN;
   extern const long ERR_ACCT_BAL_WILL_BE_LESS_MIN;
   extern const long ERR_ACCT_BAL_MAY_BE_LESS_MIN;
   extern const long ERR_AMT_IS_LESS_FUND_PURC_MIN;
   extern const long ERR_AMT_MAY_LESS_FUND_PURC_MIN;
   extern const long ERR_MIN_INITIAL_PURCH;
   extern const long ERR_COMM_ENTITY_DOES_NOT_EXIST;
   extern const long ERR_MUST_HAVE_ONE_ACTIVE_REC;
   extern const long ERR_INVALID_ENTITY_TYPE_SPLIT_COMM;
   extern const long ERR_ACCOUNT_SPLITCOMM_RECORD_EXISTS;
   extern const long ERR_NO_TITLE_RESTRICT_REC_AVAIL;
   extern const long ERR_INVALID_TAX_TYPE_ACCT_TYPE;
   extern const long ERR_UNABLE_TO_MOD_PAC_INDEX_RID_DIFF;
   extern const long ERR_PAC_INDEX_LOCKED_BY_ANOTHER_USER;
   extern const long ERR_CANNOT_LOCATE_PAC_INDEX_REC;
   extern const long ERR_UNABLE_TO_ADD_ESOP_REC;
   extern const long ERR_CONTRACT_EXIST_BUT_NOT_EFFECTIVE;
   extern const long ERR_ANNUIT_AGE_GREATER_THAN_MIN;
   extern const long ERR_AMS_CODE_NOT_VALID;
   extern const long ERR_DISTRIB_TO_CASH_NOT_ALLOWED;
   extern const long ERR_RB_DEFAULT_ALLOCATION_NOT_SET_UP;
   extern const long ERR_PAST_CUT_OFF_TIME;

   extern const long ERR_NO_AMS_RECORD;
   extern const long ERR_PRODUCT_GROUP_CODE_INVALID;
   extern const long ERR_OVERLAPPING_OR_SAME_DAY_COMMISSION;
   extern const long ERR_SYSTEM_UNAVAILABLE;
   extern const long ERR_CONTRACT_MATURITY_DATE_GREATER_THAN_LEGAL;
   extern const long ERR_ONLINE_ACCESS_FOR_CLIENT_HELD_ACC;
   extern const long ERR_MULTIPLE_ENTITIES_MATCH;
   extern const long ERR_ACC_LASTNAME_POSTALCODE_BLANK;  
   extern const long ERR_ACCOUNT_INACTIVE;
   extern const long ERR_REQUEST_FIELDS_INVALID;
   extern const long ERR_VALUATION_SCHEDULE_GROUP_FUND_SETUP;
   extern const long ERR_NO_VALUATION_SCHEDULE_GROUP_FUND_SETUP;
   extern const long ERR_NO_VALUATION_SCHEDULE_FOR_FUNDGROUP;
   extern const long ERR_SALES_REP_DOES_NOT_EXIST;
   extern const long ERR_SALES_REP_NO_LONGER_ACTIVE; 
   extern const long ERR_INVALID_USER_ID;
   extern const long ERR_USER_CANNOT_ACCESS_ACCOUNT;
   extern const long ERR_USER_ID_EXIST;
   extern const long ERR_PASSWORD_DENIED_TOO_SHORT;
   extern const long ERR_PASSWORD_DENIED_TOO_LONG;
   extern const long ERR_INVALID_MODE;
   extern const long ERR_USER_ID_NEDEED;
   extern const long ERR_IDENTIFYING;
   extern const long ERR_USER_EXISTS;
   extern const long ERR_USER_DOES_NOT_EXISTS;
   extern const long ERR_NO_PRODUCT_GROUP_CODE;
   extern const long ERR_EXCHANGE_RATE_NOT_AVAIL;
   extern const long ERR_MORE_THAN_ONE_MATCH_THE_SEARCH_CRITERIA;
   extern const long ERR_BROKERCODE_AND_SRCHALTACCOUNT_MUST_BE_PROVIDED;
   extern const long ERR_NO_ESOP_INFO_RECORD_AVAILIABLE;
   extern const long ERR_INTERDETL_RECORD_LOCKED_TRY_AGAIN_LATER;
   extern const long ERR_SPLIT_COMMISSION_RECORD_DOES_NOT_EXIST;
   extern const long ERR_SPLIT_COMMISSION_RECORD_ALREADY_EXISTS_FOR_THIS_ENTITY;
   extern const long ERR_CAN_ONLY_DELETE_ON_THE_DATE_RECORD_IS_CREATED;
   extern const long ERR_FEE_PARAMETER_ALREADY_EXISTS;
   extern const long ERR_SCALE_DETL_RECORD_NOT_AVAILABLE;
   extern const long ERR_INVALID_ACCRUAL_TYPE;
   extern const long ERR_NO_FEE_DEFINED_FOR_FEE_OVERRIDE;
   extern const long ERR_NO_FEE_ACCRUAL_INFORMATION_AVAILABLE;
   extern const long ERR_AMOUNT_CANNOT_BE_GREATER_AMOUNT_TYPE_P;
   extern const long ERR_CALCULATING_MANAGEMENT_FEE_ACCRUALS;
   extern const long ERR_INVALID_AMOUNT_TYPE;
   extern const long ERR_INVALID_BAYCOM;
   extern const long ERR_AMOUNT_MUST_BE_ZERO_FOR_AMOUNTTYPE_T;
   extern const long ERR_NOT_APPLICABLE_FOR_THIS_FUNDCLASS;
   extern const long ERR_NO_PENSION_INFO_REC_AVAIL;
   extern const long ERR_UNABLE_TO_ADD_PENSION_RECORD;
   extern const long ERR_ACCOUNT_REVIEW_DETAIL_NOT_FOUND;
   extern const long ERR_ACCOUNT_REVIEW_RECORD_EXISTS;
   extern const long ERR_INVALID_SEARCH_TYPE;
   extern const long ERR_FUNDCODE_CANNOT_BE_BLANK_BANK_ENTITY;
   extern const long ERR_INVALID_DATE_RANGE;
   extern const long ERR_ADDR_CODE_EXISTS_FOR_ENTITY;
   extern const long ERR_PROCESS_TYPE_MUST_BE_11;
   extern const long ERR_CALCULATING_DIVIDENTS;
   extern const long ERR_TRANS_MODIFIED_UNABLE_SETTLE;
   extern const long ERR_INVALID_TRANSLATIONTYPE;
   extern const long ERR_INVALID_LANG;
   extern const long ERR_DELIVERY_METHOD_EXISTS_FOR_DOC_TYPE;
   extern const long ERR_NO_ACTENTDELOPTN_REC_AVAIL;
   extern const long ERR_SEE_ERROR_LOG_REDEMLOGD;
   extern const long ERR_REMAINING_ACCT_BAL_INSUFFICIENT;
   extern const long ERR_TAX_TYPE_RULE_NOT_AVAIL;
   extern const long ERR_SCHEDULED_PAYMENT_NOT_AVAIL;
   extern const long ERR_REDEMP_CODE_RULE_NOT_SETUP;
   extern const long ERR_REMAIN_MIN_AMT_REDEPM_NOT_PROCESSED;
   extern const long ERR_FUND_IS_NOT_ESOP_ELIGIBLE;
   extern const long ERR_PROCESS_REDEMP_ESOP_INVEST;
   extern const long ERR_PROCESS_REDEMP_ESOP_PARTICIP;
   extern const long ERR_ESOP_MUST_CLOSE_ACCT;
   extern const long ERR_REDEMP_NOT_ALLOW_ESOP;
   extern const long ERR_CONTRACT_ACCT_STATUS_ACTIVE;
   extern const long ERR_CONTRACT_ACCT_NOT_ACTIVE;
   extern const long ERR_CONTRACT_ACCT_STATUS_DEATH;
   extern const long ERR_NON_INT_AMT_ZERO_PRECISION;
   extern const long ERR_LLP_ERROR;
   extern const long ERR_ESTATE;
   extern const long ERR_EXCHANGE_RATE_TAX_CALC_NOT_FOUND;
   extern const long ERR_ACCT_NOT_ACTIVE_AT_TRADE_DATE;
   extern const long ERR_CURRENCY_NOT_ALLOWED_TAX_TYPE;
   extern const long ERR_STOP_DATE_FUND_SAME_TRADE_DATE;
   extern const long ERR_NO_ACCT_VALUE_REC_EXISTS;
   extern const long ERR_TRANS_MUST_BE_VERIFIED;
   extern const long ERR_FIFO_NOT_EXIST;
   extern const long ERR_NO_AVAIL_UNITS;
   extern const long ERR_DEALER_NOT_AUTH_TO_DEAL_FUND;
   extern const long ERR_INSUF_FUND_AT_TRADE_DATE;
   extern const long ERR_UNISSUED_CERT_UNIT_EXIST;
   extern const long ERR_EXCEED_USER_SETUP_AMT;
   extern const long ERR_TRADE_IS_THIRTY_OLD_OLDER;
   extern const long ERR_STOP_BEFORE_START;
   extern const long ERR_INVALID_SETTLE_SOURCE;
   extern const long ERR_INVALID_SETTLE_SOURCE_ACCT_DESIGN;
   extern const long ERR_INVALID_ORDER_SOURCE;
   extern const long ERR_INVALID_SETTLEMENT_TYPE;
   extern const long ERR_INVALID_SETTLE_TYPE_DEALER_INTERM;
   extern const long ERR_WIRE_ORDER_REDEMP_NOT_ALLOW;
   extern const long ERR_INVALID_ORDER_SOURCE_ACCT_DESGIN;
   extern const long ERR_INTERM_IS_NOT_PERMIT_WIRE;
   extern const long ERR_BROKER_IS_NOT_PERMIT_MONEY_MKT;
   extern const long ERR_DEALER_CANNOT_SETTLE_INTERM;
   extern const long ERR_BATCH_IS_ACTIVE;
   extern const long ERR_BATCH_IS_LOCKED;
   extern const long ERR_BATCH_DOES_NOT_EXIST;
   extern const long ERR_INVALID_REDEMP_CODE;
   extern const long ERR_GROUP_REDEMP_STOP_FLAG_ENABLE;
   extern const long ERR_REDEMP_STOP_FLAG_ENABLED;
   extern const long ERR_ASSIGNED_FLAG_ENABLED;
   extern const long ERR_FEE_ENTERED_WITHOUT_OVERRIDE;
   extern const long ERR_FULL_REDEMP_NOT_ALLOWED;
   extern const long ERR_REDEMP_NOT_ALLOWED_FUND;
   extern const long ERR_FEE_OVERRIDE_NO_FEE_DEFINED;
   extern const long ERR_ACQ_FEE_CALC_DURING_RUN;
   extern const long ERR_NO_AMOUNT_AVAIL_IN_CASH_FUND;
   extern const long ERR_TYPE_TRANS_NOT_SUPPORT_FAMILY;
   extern const long ERR_ONLY_RD_ALLOW_RESP_TRANSFER;
   extern const long ERR_DP_RD_NOT_ALLOW_TRANSER;
   extern const long ERR_NO_RESPCONTRDETL_REC_AVAIL;
   extern const long ERR_TRADE_DATE_LATER_THAN_RESP_CONTRIB;
   extern const long ERR_RESP_PLAN_LIMIT_EXCEEDED;
   extern const long ERR_RESP_YEAR_LIMIT_EXCEEDED;
   extern const long ERR_NO_EARNING_IN_THE_ACCT;
   extern const long ERR_RESP_REDEMP_EXCEED_EARNINGS;
   extern const long ERR_RESP_REDEMP_EXCEED_CONTRIB;
   extern const long ERR_NOT_ENOUGH_GRANT_AMT_RETURN;
   extern const long ERR_RESP_TRANSFER_AMT_TOO_HIGH;
   extern const long ERR_AMS_CODE_NOT_FOUND;
   extern const long ERR_CANNOT_DELETE_AMS_CODE_IN_USE;
   extern const long ERR_CANNOT_DELETE_AMSCODE_IN_MSTR;
   extern const long ERR_AMSCODE_ALREADY_EXISTS;
   extern const long ERR_ALLOCATION_EXISTS_FOR_FUND_CLASS;
   extern const long ERR_UNKNOWN_SCHED_USER_INTERFACE;
   extern const long ERR_CANNOT_LOCATE_SCHED_JOB;
   extern const long ERR_INVALID_RESON_CODE;
   extern const long ERR_JOBID_NOT_GEN_CHECK_PROCESS;
   extern const long ERR_NO_PRINTER_RECORDS_AVAIL;
   extern const long ERR_NO_JOBS_AVAIL;
   extern const long ERR_NO_PARAM_REC_AVAIL; 
   extern const long ERR_INVALID_VALID_TYPE;
   extern const long ERR_ACCTNBR_MUST_BE_ENTERED;
   extern const long ERR_SCALE_REC_REQUIRED_FEE_2_3;
   extern const long ERR_SHAREHOLDER_FAMILY_EXISTS;
   extern const long ERR_DSC_REC_EXISTS_THIS_FAMILY_NO_DELETE;
   extern const long ERR_PROTECTED_FUND_DOES_NOT_EXIST;
   extern const long ERR_FUND_CLASS_USED_IN_ACTIVE_CONTRACT;
   extern const long ERR_PROTECTED_FUND_EXISTS;
   extern const long ERR_INDEX_CODE_CANNOT_BE_BLANK;
   extern const long ERR_MKT_INDEX_RECORD_LOCKED;
   extern const long ERR_MKT_INDEX_NOT_FOUND;
   extern const long ERR_VERSION_NUM_DO_NOT_MATCH;
   extern const long ERR_MKT_INDEX_EXISTS_WITH_INDEX_CODE;
   extern const long ERR_FUND_RUNMODE_NOT_VALID;
   extern const long ERR_FUND_DETL_REC_IS_LOCKED;
   extern const long ERR_FUND_DETL_DATA_NOT_FOUND;
   extern const long ERR_ACCT_CAT_REC_DOES_NOT_EXISTS;
   extern const long ERR_CAT_TYPE_EXISTS_FOR_ACCT;
   extern const long ERR_MKT_INDEX_REC_LOCKED;
   extern const long ERR_MKT_INDEX_DETAIL_NOT_FOUND;
   extern const long ERR_MKT_INDEX_DETAIL_EXISTS;
   extern const long ERR_FROM_TO_DATE_MUST_ENTERED;
   extern const long ERR_INDEX_CODE_MUST_BE_ENTERED;
   extern const long ERR_BROKER_NOT_ELIGIBLE_WRAP;
   extern const long ERR_SLS_REP_NOT_ELIGIBLE_FOR_WRAP;
   extern const long ERR_FUND_DEALER_ELIG_DATA_NOT_FOUND;
   extern const long ERR_BROKER_AMS_NOT_EXIST;
   extern const long ERR_BROKER_AMS_USED_BY_ACCOUNT;
   extern const long ERR_CANNOT_MODIFY_A_BAD_REC;
   extern const long ERR_BROKER_AMS_ALREADY_EXISTS;
   extern const long ERR_NETWORKORDER_ALREADY_EXISTS;
   extern const long ERR_SPLITCOMM_FEEDEFN_NOT_FOUND;
   extern const long ERR_EXIST_AS_BAD;
   extern const long ERR_CURRENCY_NOT_AVAILABLE;
   extern const long ERR_MISMATCHED_UNIT_AVAILABLE;
   extern const long ERR_KYC_DATA_NOT_FOUND;
   extern const long ERR_KYC_RECORD_ALREADY_EXIST;
   extern const long ERR_PAYENTITY_ALREADY_EXIST_FOR_BROKER;
   extern const long ERR_PAYENTITY_DOES_NOT_EXIST;
   extern const long ERR_PAYINSTRUCT_ALREADY_EXISTS_FOR_BROKER;
   extern const long ERR_PAYINSTRUCT_DOES_NOT_EXIST;

   extern const long ERR_AMS_RULES_REC_EXISTS;
   extern const long ERR_BANK_MASTER_REC_EXISTS;
   extern const long ERR_BANK_MASTER_DEL_ON_DATE;
   extern const long ERR_TRANS_NUM_OR_ACCT_REQUIRED;
   extern const long ERR_TRANS_NUM_MANDATORY;
   extern const long ERR_TRANS_NUM_EXISTS;
   extern const long ERR_EXT_TRANSFER_ACCT_REC_NON_EXISTANT;
   extern const long ERR_EXT_TRANSFER_ACCT_DETL_NON_EXISTANT;
   extern const long ERR_SHAREHOLDER_RESIDENCY_NOT_VALID;
   extern const long ERR_DTA_REC_DOES_NOT_EXIST;
   extern const long ERR_DTA_REC_EXISTS;
   extern const long ERR_INVALID_TRANSFER;
   extern const long ERR_DTA_REC_DOES_NOT_EXIST;
   extern const long ERR_DTA_REC_EXISTS;
   extern const long ERR_TRANSFER_TRACK_HAS_NONOUTSTANDING;
   extern const long ERR_TRANSFER_TRACK_DEL_IF_OUTSTANDING;
   extern const long ERR_SETTLE_LOC_DOES_NOT_EXIST;
   extern const long ERR_SETTLE_LOC_ALREADY_EXISTS;
   extern const long ERR_SETTLE_LOC_ACCT_DOES_NOT_EXIST;
   extern const long ERR_SETTLE_LOC_ACCT_ALREADY_EXISTS;
   extern const long ERR_NO_DATA_IN_REPEAT_SECTION;
   extern const long ERR_TRANS_CLEARING_SETTLE_REC_EXISTS;
   extern const long ERR_SETTLE_LOC_DATA_NOT_FOUND;
   extern const long ERR_SETTLE_LOC_ACCT_DATA_NOT_FOUND;
   extern const long ERR_DAILY_FEE_RECORD_ALREADY_EXISTS;
   extern const long ERR_DAILY_FEE_RECORD_DOES_NOT_EXIST;
   extern const long ERR_SHR_FUND_SPONSOR_AGRMNT_ALREADY_EXISTS;
   extern const long ERR_SHR_FUND_SPONSOR_AGRMNT_DOES_NOT_EXIST;
   extern const long ERR_TRANSACTION_PROCESSED_550 ;
   extern const long ERR_SETTLEMENT_NOT_ALLOWED_551;
   extern const long ERR_TRANSACTION_CANCELED_552;
   extern const long ERR_MFCS_COMPLIANT_553;
   extern const long ERR_FEE_MODEL_CODE;
   extern const long ERR_FUND_SPONSOR_REQUIRED;
   extern const long ERR_INVALID_FUND_SPONSOR;
   extern const long ERR_SHR_FUND_BROKER_ALREADY_EXISTS;
   extern const long ERR_UNABLE_TO_MODIFY_RECORD;
   extern const long ERR_ACCOUNT_OR_FUNDBROKER_SHOULD_BE_BLANK;
   extern const long ERR_INVALID_FUND_BROKER;
   extern const long ERR_INVALID_SETTLEMENT_INSTRUCTION_CODE;
   extern const long ERR_FUND_BROKER_NOT_EXIST;
   extern const long ERR_FUND_BROKER_WHERE_USE_RECORD_NOT_EXIST;
   extern const long ERR_PRI_CONTACT_WHERE_USE_RECORD_NOT_EXIST;
   extern const long ERR_SEC_CONTACT_WHERE_USE_RECORD_NOT_EXIST;
   extern const long ERR_FUND_BROKER_ALREADY_EXIST;
   extern const long ERR_ENTITY_WHEREUSE_ALREADY_EXIST;
   extern const long ERR_CLEARINGSETTLEINSTR_DATA_NOT_FOUND;
   extern const long ERR_AGGREGATE_ORDER_DOES_NOT_EXIST;
   extern const long ERR_AGGREGATION_REF_NUMBER_BLANK;
   extern const long ERR_ROUTING_REF_NUMBER_BLANK;
   extern const long ERR_ORDER_STATUS_BLANK;
   extern const long ERR_AGGREGATE_ORDER_DOES_NOT_EXIST;
   extern const long ERR_CLEARINGSETTLEINSTR_ALREADY_EXISTS;
   extern const long ERR_DEFAULT_FUNDBROKER_ALREADY_EXISTS;
   extern const long ERR_AMOUNT_EXCEEDS_VARIANCE_LIMIT;
   extern const long ERR_NEW_PASSWORD_TOO_LONG;
   extern const long ERR_ORDER_HEADER_ALREADY_EXISTS;
   extern const long ERR_ORDER_DETAIL_ALREADY_EXISTS;
   extern const long ERR_ORDER_DETAIL_DOES_NOT_EXIST;
   extern const long ERR_ALL_REQUEST_FIELDS_BLANK;
   extern const long ERR_AMT_EXCEEDS_THRESHOLD_TRADE_LIMIT;
   extern const long ERR_CANNOT_DELETE_FEEMODEL_CODE;
   extern const long ERR_FEEMODEL_ALREADY_EXISTS;
   extern const long ERR_FEEMODEL_DOES_NOT_EXIST;
   extern const long ERR_FEEMODEL_LOCKED;
   extern const long ERR_FEEMODELCODE_INUSE_CANNOT_DELETE;
   extern const long ERR_FNDSPONSOR_FEEMODEL_ALREADY_EXISTS;
   extern const long ERR_FNDSPONSOR_FEEMODEL_DOES_NOT_EXIST;
   extern const long ERR_FNDSPONSOR_FEEMODEL_LOCKED;
   extern const long ERR_FNDSPONSOR_FEEMODEL_NOT_FOUND;
   extern const long ERR_INVALID_FEEMODEL_CODE;
   extern const long ERR_TAXEXEMPT_AUTH_ALREADY_EXISTS;
   extern const long ERR_TAXEXEMPT_AUTH_DOES_NOT_EXIST;
   extern const long ERR_STOP_PW_FLAG_ACTIVE;
   extern const long ERR_TRANSTYPE_RC_REQUIRES_FUNDCLASS;
   extern const long ERR_BONIMAX_VALUE_LESS_THAN_ZERO;

   extern const long ERR_TRADING_TIME_AGGR;
   extern const long ERR_TRADING_TIME_CLIENT_CUT;
   extern const long ERR_KV_NUM_MUST_BE_ENTERED;
   extern const long ERR_KV_NUM_DOES_NOT_EXIST;
   extern const long ERR_FUND_NON_EXISTANT_UNDER_TYPEVAL;
   extern const long ERR_FUNDIDTYPE_FUNDIDVALUE;
   extern const long ERR_INVALID_ENVELOPE_ID;
   extern const long ERR_INVALID_ACTIVITY_ID;
   extern const long ERR_INVALID_PROCESS_ID;
   extern const long ERR_TRANS_TYPE_REQUIRED;
   extern const long ERR_NUM_UNITS_REQUIRED;
   extern const long ERR_TRADE_DATE_REQUIRED;
   extern const long ERR_WHEREUSE_MUST_BE_01_03;
   extern const long ERR_INVALID_PROCESS_CATEGORY;
   extern const long ERR_ENTITYWHEREUSE_NOT_FOUND;
   extern const long ERR_ENTITYWHEREUSE_EXISTS;
   extern const long ERR_COUNTRY_REQUIRED;
   extern const long ERR_LINK_CANNOT_BE_DEL;
   extern const long ERR_INVALID_COMPANY_CODE;
   extern const long ERR_INVALID_PROCESS_TYPE;
   extern const long ERR_CANCEL_INSTR_EXISTS;
   extern const long ERR_CANCEL_DOES_NOT_EXIST;
   extern const long ERR_DILUTION_DOES_NOT_EXIST;

   extern const long ERR_CANCEL_FAILED;
   extern const long ERR_DILUTION_RECORDS_EXISTS;
   extern const long ERR_TRADEADJUST_RECORDS_EXISTS;
   extern const long ERR_INVALID_STATUS;
   extern const long ERR_SPLIT_DILUTION_NOT_ALLOWED;
   extern const long ERR_REASON_ACCOUNTABLE_CAN_NOT_BLANK;
   extern const long ERR_ACCOUNTABLE_SHOULD_BLANK_WHEN_DILUTION_EXISTS;   
   extern const long IFASTDBRKR_ERR_USERDEFMAT_DATE_EXISTS;
   extern const long IFASTDBRKR_ERR_USERDEFMAT_RECORD_NOT_FOUND;
   extern const long IFASTDBRKR_ERR_USERDEFMAT_GREATER_THAN_LEGAL;
   extern const long IFASTDBRKR_ERR_USERDEFMAT_BLANK;
   extern const long IFASTDBRKR_ERR_TXN_PERPETUAL_DSC;
   extern const long IFASTDBRKR_ERR_UPDATE_PERPETUAL_DSC_INFO;
   extern const long IFASTDBRKR_ERR_NO_FAMILY_CODE_SHRHOLDER;
   extern const long IFASTDBRKR_ERR_UPDATE_PDSC_INFO;
   extern const long IFASTDBRKR_ERR_REVERSE_INVENTORY_UNITS;
   extern const long IFASTDBRKR_ERR_NIGHTCYCLE_ID_NOT_FOUND;
   extern const long IFASTDBRKR_ERR_ACCT_NOT_ACTIVE;
   extern const long IFASTDBRKR_ERR_TRAN_ACCT_NOT_ACTIVE;
   extern const long IFASTDBRKR_ERR_INSUFFICIENT_UNITS;
   extern const long IFASTDBRKR_ERR_INSUFFICIENT_UNITS_CANCEL;
   extern const long IFASTDBRKR_ERR_ACCT_VALUE_DOES_NOT_EXIST;
   extern const long IFASTDBRKR_ERR_ACCT_CERT_UNIT_NOT_ENOUGH;
   extern const long IFASTDBRKR_ERR_ACCT_BALANCE_BELOW_ZERO;
   extern const long IFASTDBRKR_ERR_FUND_SCHED_VALN_GROUP_NOT_FOUND;
   extern const long IFASTDBRKR_ERR_CANCEL_NOTIONAL_DISTRIB_DSC;
   extern const long IFASTDBRKR_ERR_NO_PERM_CANCEL_NOTIONAL_DISTRIB;
   extern const long IFASTDBRKR_ERR_NO_FUND_VALUATION_RECORD;
   extern const long IFASTDBRKR_ERR_UPDATING_LLPWTHDRWL_TABLE;
   extern const long IFASTDBRKR_ERR_TRANS_DETL_NOT_FOUND;
   extern const long IFASTDBRKR_ERR_NO_LLPWTHDRWL_RECORD_DEACTIV;
   extern const long IFASTDBRKR_ERR_UNKNOWN_FUNCTION_UPDATE;
   extern const long IFASTDBRKR_ERR_CREATE_POST_ADJUSTMENT_DIV;
   extern const long IFASTDBRKR_ERR_INSUFFICIENT_UNITS_NEG_ADJ;
   extern const long IFASTDBRKR_ERR_INVSUMM_ID_TO_NOT_PASSED;
   extern const long IFASTDBRKR_ERR_TRACE_NO_TO_NOT_PASSED;
   extern const long IFASTDBRKR_ERR_NO_INVSUMM_ID_RECORD;
   extern const long IFASTDBRKR_ERR_TAX_JURIS_SHRHOLDER_BLANK;
   extern const long IFASTDBRKR_ERR_INVENTORY_BALANCE_NEGATIVE;
   extern const long IFASTDBRKR_ERR_GIC_DOES_NOT_EXIST;
   extern const long IFASTDBRKR_ERR_GIC_MATURED;
   extern const long IFASTDBRKR_ERR_GIC_PURCHASE_REDUCED;
   extern const long IFASTDBRKR_ERR_INVENTORY_DOES_NOT_EXIST;
   extern const long IFASTDBRKR_ERR_TXN_REDUCED_ALREADY;
   extern const long ERR_INVALID_REG_AGENT_CODE;
   extern const long ERR_EMPTY_REG_AGENT_CODE;
   extern const long ERR_CD_POLICY_IMPACT_DOB;
   extern const long ERR_DOB_IMPACT_MATUR_POLICY;
   extern const long ERR_NEW_DATE_BIRTH_CANNOTBE_BLANK;
   extern const long ERR_NEW_LEGAL_CONTRACT_MAT_DATE;
   extern const long ERR_TXN_CANNOT_EXIST_AFTER_DECADE;
   extern const long ERR_AGGREGATE_ORDER_LOSS;
   extern const long ERR_AMT_EXCEED_VARIANCE_AGGRORD;
   extern const long ERR_REPRINT_RECORD_ALREADY_EXISTS;
   extern const long ERR_REPRINT_RECORD_DOES_NOT_EXIST;
   extern const long ERR_No_Valid_Acct_Level_CONTRACT;
   extern const long ERR_GUARANTEE_ADJUSTMENT_MADE;
   extern const long ERR_PENDING_TRADE_CANNOT_EXIST;
   extern const long ERR_NEGATIVE_GUARANTEE_CANNOT_EXIT;
   extern const long ERR_TXN_EXIST_AFTER_CLOSING_DECADE;
   extern const long ERR_GUARANTEE_ADJUST_NEED_CANCELLATION;
   extern const long ERR_REVERSAL_CODE_TOP_UP_INCORRECT;
   extern const long ERR_GEN_CTRL_TRADE_DEFLT_DOES_NOT_EXIST;
   extern const long ERR_ACCT_LVL_CUT_OFF_TIME_NOT_EXIT;
   extern const long ERR_ACCT_LVL_CUT_OFF_TIME_ALREADY_EXIT;
   extern const long ERR_RECREATING_POLICY_PERIOD;
   extern const long ERR_NO_VALID_CONTRACT_ORIG_TRADEDATE;
   extern const long ERR_RESET_OCCURED_SINCE_ORIG_TRADEDATE;
   extern const long ERR_NEGATIVE_GUARANTEE_ORIG_TRADEDATE;
   extern const long ERR_DM_EVENT_SINCE_ORGI_TRADEDATE;
   extern const long ERR_TRADE_PARTOF_DM_EVENT;
   extern const long ERR_CANCEL_GUAR_ADJ_EXIST_FOR_ACCT_CONTRACT_AFTR_TRADE_DATE;
   extern const long ERR_GRNTE_MATURED_PER_CNTRCT_TERM;
   extern const long ERR_SEG_CALC_REQUEST_DURING_CANCEL;
   extern const long ERR_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT;
   extern const long ERR_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT;
   extern const long ERR_CANCEL_MONEY_OUT_TXNS;
   extern const long ERR_TRANSFER_ACCOUNT_PURGED;
   extern const long ERR_TRANSACTION_MORE_THAN_ONE_SHAREHOLDER;
   extern const long ERR_PENDING_EXIST_WITH_TRANSNUM;
   extern const long ERR_UNSETTLE_CANNOT_CANCEL_FOR_DIVIDEND_FUND;
   extern const long ERR_MIRROR_CHILD_AMS_REBALANCE;
   extern const long ERR_SEG_GUAR_MAT_RECORD_NOT_FOUND;
   extern const long ERR_SEG_GUAR_DETL_RECORD_NOT_FOUND;
   extern const long ERR_NOT_ENOUGH_SETTLED_UNITS_TO_SETTLE_REDEMPTION;
   extern const long ERR_CONTRACT_CLOSED_FOR_NEW_BUSINESS;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE;
   extern const long ERR_INVALID_TRANSACTION_STATUS;
   extern const long ERR_TRADEDATE_FUNDCLASS_BLANK;
   extern const long ERR_INVALID_TRANS_STATUS;
   extern const long ERR_INVALID_ADJUST_TYPE;
   extern const long ERR_BULK_CANC_NO_TXN_TO_CANCEL;
   extern const long ERR_BULK_CANC_NO_TXN_TO_REBOOK;
   extern const long ERR_CANC_NOT_ALLOWED_ACTIVE_CYCLE; 
   extern const long ERR_EUSD_OVERRIDE_DOES_NOT_EXIST;
   extern const long ERR_PWD_NOT_CONTAIN_USER;
   extern const long ERR_INVALID_PARAMETER_NEED_BROKERCODE;
   extern const long ERR_PWD_USER_NOT_BE_SAME;
   extern const long ERR_INSUFFICIENT_NOTIONAL_BALANCE;
   extern const long ERR_PA_NOT_FOUND;
   extern const long ERR_NO_ENTITY_TAX_HIST_FOUND_FOR_PA;
   extern const long ERR_TAX_JURIS_NOT_FOUND_FOR_OWNER;
   extern const long ERR_NO_ACTIVE_OWNER_FOUND;

   extern const long ERR_MISSING_CUSTOM_TRADING_SCHD;
   extern const long ERR_NO_BUSSINESS_DAY_RECORD_AVAIL;
   extern const long ERR_INVALID_CUSTOM_TRADING_SCHD;

   extern const long ERR_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE;
   extern const long ERR_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE;
   extern const long ERR_CONTRACT_TYPE_MUST_BE_ENTERED;
   extern const long ERR_TAXTYPE_MUST_BE_ENTERED;
   extern const long ERR_PROVINCE_MUST_BE_ENTERED;
   extern const long ERR_EFFECTIVEDATE_MUST_BE_ENTERED;
   extern const long ERR_CANNOT_FIND_TIME_ZONE_INFORMATION;
   extern const long ERR_SEG_MANUAL_EVENTS_SINCE_ORIGINAL_TRADE_DATE;

   extern const long ERR_PAY_ENTITY_EXISTS_FOR_DATE_RANGE;
   extern const long ERR_PAY_INSTRUCT_EXISTS_FOR_DATE_RANGE;
   extern const long ERR_TRADE_PAY_INSTRUCT_RECORD_LOCKED;
   extern const long ERR_TRADE_PAY_INSTRUCT_RECORD_DOES_NOT_EXIST;
   extern const long ERR_TRADE_PAY_INSTRUCT_RECORD_ALREADY_EXISTS;
   extern const long ERR_PAYENTITY_DOES_NOT_EXIST_FOR_DATE_RANGE;
   extern const long ERR_PAYENTITY_ALREADY_STOPDATED; //added for INC0031322

   extern const long ERR_RTS_CONFIG_ISSUE;
   extern const long ERR_RTS_OUT_OF_MEMERY;
   extern const long ERR_RTS_OUT_OF_DISK_SPACE;
   extern const long ERR_RTS_SYSTEM_ISSUE;
   extern const long ERR_RTS_IFAST_NOT_RESPONDING;
   extern const long ERR_RTS_DATABASE_CONNECTION;

   extern const long ERR_NOMINEE_ENTITY_NOT_FOUND;
   extern const long ERR_INTERMEDIARY_ENTITY_NOT_FOUND;

   extern const long ERR_TRXR_CANCEL_FAILED;
   extern const long ERR_SWITCH_SETTLE_FAILED;
   extern const long ERR_EXCH_RATE_DOES_NOT_EXIST;
   extern const long ERR_INVENTORY_TRACKING_ERROR;
   extern const long ERR_ACCOUNT_AMS_RECORD_DOES_NOT_EXIST;
   extern const long ERR_INVALID_BILL_TO_ENTITY;
   extern const long ERR_INVALID_BILL_TO_ENTITY_TYPE;
   extern const long ERR_INVALID_ASSOCIATED_ACCNUM;
   extern const long ERR_ACCOUNT_AMS_RECORD_ALREADY_EXISTS;
   extern const long ERR_KYC_RECORD_NOT_FOUND;
   extern const long ERR_MANAGEMENT_FEE_MODEL_MISSING;
   extern const long ERR_INVALID_ACCESS_ID;
   extern const long ERR_ACCESS_ID_OVERRIDE_NOT_ALLOWED;
   extern const long ERR_NO_DATA_AVAILABLE;  

   extern const long ERR_AMS_ACTIVE_CERTS_EXIST;

   extern const long IFASTDBRKR_ERR_ACCT_CONTROL_NOT_EXISTS;
   extern const long IFASTDBRKR_ERR_ACCT_CONTROL_EXISTS;
   extern const long IFASTDBRKR_ERR_ACCT_CONTROL_UNABLE_TO_MODIFY;

   extern const long ERR_CANCELLATION_FAILED_TO_CANCEL_ASSOC_UNSTTL_CASH_ID;
   extern const long ERR_CANCELLATION_UNDONE_BY_ERROR_OR_ENDKEY;
   extern const long ERR_CANCELLATION_DEPOSIT_DTE_BLNK_FOR_LSIF_FND;
   extern const long ERR_CANCELLATION_LOCK_ACCT_VAL_TO_RESET_ACB_SUPPRESS_FLAG_FAILED;
   extern const long ERR_CANCELLATION_CALC_EUSD_FAILED_FUND_INFO_NOT_FOUND;
   extern const long ERR_CANCELLATION_CALC_EUSD_FAILED_PRICE_DISTRIB_RATE_NOT_FOUND;
   extern const long ERR_CANCELLATION_CALC_EUSD_FAILED_PAYING_AGENT_NOT_FOUND;
   extern const long ERR_CANCELLATION_CALC_EUSD_FAILED_ENTITY_IDENTITY_PAYING_AGENT_NOT_FOUND;
   extern const long ERR_CANCELLATION_CALC_EUSD_FAILED_TAX_HIST_PAYING_AGENT_NOT_FOUND;
   extern const long ERR_CANCELLATION_CALC_EUSD_FAILED_TAX_HIST_OWNER_NOT_FOUND;
   extern const long ERR_CANCELLATION_CALC_EUSD_FAILED_ACCTIVE_OWNER_NOT_FOUND;
   extern const long ERR_CANCELLATION_CALC_EUSD_FAILED_CURRENCY_NOT_FOUND;

   extern const long WARN_STOP_REASON_MISSING_SYSTEM;
   extern const long WARN_STOP_REASON_DECEASED_SYSTEM;
   extern const long WARN_STOP_REASON_STOPFLAGS_DECESED_REMOVED;
   extern const long WARN_STOP_REASON_STOPFLAGS_KYC_REMOVED;

   extern const long ERR_CHQ_DETL_NOT_FOUND;
   extern const long ERR_SALES_REP_ALREADY_EXISTS;
   extern const long ERR_NOT_WIRE_ORDER_TRADE;

   extern const long ERR_MULTIPLE_ALLOC_SAME_EFF_DATE_NOT_ALLOWED;
   extern const long ERR_CONFLICT_ADDRESS_EXIST;
   extern const long ERR_BATCHTRACE_REC_NOTFOUND;
   extern const long ERR_USER_BATCH_ISNOT_ACTIVE;

   extern const long ERR_SMQ_FRAMEWORK_ERROR;
   extern const long ERR_SMQ_AUTHORIZATION_ERROR;
   extern const long ERR_SMQ_AUTHORIZATION_DENIED;
   extern const long ERR_SMQ_SESSION_EXPIRED;
   extern const long ERR_SMQ_APPSERVER_ERROR;
   extern const long ERR_SMQ_NO_APPSERVER;
   extern const long ERR_SMQ_BROKEN_APPSERVER_CONNECTION;
   extern const long ERR_SMQ_SONICMQ_ERROR;

   extern const long ERR_ACCT_LEVEL_IA_RECORD_NOT_EXISTS;
   extern const long ERR_ACCT_LEVEL_IA_RECORD_EXISTS;
   extern const long ERR_ACCT_LEVEL_IA_RECORD_VERSION_DIFF;
   extern const long ERR_ACCT_LEVEL_IA_RECORD_INVALID_PAYMENT_TYPE;

   extern const long ERR_USER_DO_NOT_HAVE_ACCESS_TO_DESKTOP;
   extern const long ERR_VERIFY_REQUEST_RUN_MODE_NOT_VALID;
   extern const long ERR_VERIFY_REQUEST_VERIFY_CATEGORY_NOT_VALID;
   extern const long ERR_VERIFY_REQUEST_VERIFY_LEVEL_NOT_VALID;
   extern const long ERR_VERIFY_REQUEST_VERIFY_BLANK_LINKID;
   extern const long ERR_VERIFY_REQUEST_VERIFY_BLANK_UUID;
   extern const long ERR_VERIFY_REQUEST_RECORD_LOCKED;
   extern const long ERR_VERIFY_REQUEST_RECORD_NOT_EXIST;
   extern const long ERR_TRADE_BANK_NOT_VERIFIED;
   extern const long ERR_SETTLE_BANK_NOT_VERFIED;
   extern const long ERR_SHRHLDR_ADDR_NOT_VERIFIED_FOR_SETTLEMENT;
   extern const long ERR_RESP_BENEF_RECORD_LOCKED;
   extern const long ERR_RESP_BENEF_RECORD_VERSION_NOT_MATCH;
   extern const long ERR_RESP_BENEF_RECORD_NOT_FOUND;
   extern const long ERR_INVALID_CALL_TYPE;
   extern const long ERR_RESP_RECORD_LOCKED;
   extern const long ERR_RESP_RECORD_UNAVAILABLE;
   extern const long ERR_INVALID_TRADE_TYPE;
   extern const long ERR_INVALID_CALLTYPE_TRADETYPE;
   extern const long ERR_TRANSFER_DETAIL_RECORD_LOCKED;
   extern const long ERR_TRANSFER_DETAIL_RECORD_NOT_AVAILABLE;
   extern const long ERR_RESP_TRINFO_NOT_AVAILABLE;
   extern const long ERR_CLINET_RECORD_ALREADY_EXISTS;
   extern const long ERR_WARNCODE_TABLE_NOT_AVAIL;
   extern const long ERR_SETTLEMENT_NOT_ALLOWED_DURING_CYCLE;
   extern const long ERR_NO_TRANSACTION_NUMBER;
   extern const long ERR_ACCT_FOR_TRANSACTION_NOT_AVAILABLE;
   extern const long ERR_RESP_ACCT_INFO_NOT_AVAILABLE;
   extern const long ERR_NOT_FOUND_RESP_EARNING_GRANT_REDCODES_CONTROLS_RECORD;
   extern const long ERR_DBKR_BATCH_BELONGS_TO_OTHERUSER;
   extern const long ERR_BRK_EPA_STATUS_NOT_ACTIVE;
   extern const long ERR_511_RECORDS_NOT_ALLOWED;
   extern const long ERR_SHAREHOLDER_FAMILY_RECORD_NOT_EXISTS;
   extern const long ERR_FAMILY_RECORD_NOT_EXISTS;
   extern const long ERR_INTINVEST_LOCKED;
   extern const long ERR_INTINVEST_NOT_AVAIL;
   extern const long ERR_BANKACCT_LOCKED;
   extern const long ERR_INTINVEST_VERSION_DIFFERENT;
   extern const long ERR_BANKACCT_VERSION_DIFFERENT;
   extern const long ERR_SUBSEQUENT_EVENTS_TAKEN_PLACE_AT_CANCELLATION;
   extern const long ERR_EQ_TRADE_CANCEL;
   extern const long ERR_NO_ADDITIONAL_TRADE_DATE_EXIST;
   extern const long ERR_INCREASE_NOT_ALLOWED_MISSED_PACS;
   extern const long ERR_COMMISION_EXCEED_FUND_DEFAULT_RATE;
   extern const long ERR_INSTRUCTION_ALREADY_EXISTS;
   extern const long ERR_AMOUNT_DONOT_CROSSFOOT;
   extern const long ERR_NEGATIVE_GUARANTEES_FOLLOWING_MUST_BE_CANCELLED;
   extern const long ERR_HOLDING_ENTITY_CODE_ALREADY_EXISTS;
   extern const long ERR_HOLDING_ENTITY_RECORD_DOES_NOT_EXIST;
   extern const long ERR_HOLDING_ENTITY_CODE_BAD_RECORD_EXISTS;
   extern const long ERR_FEE_MODEL_RECORD_WITH_SAME_FEE_MODEL_CODE_IS_ALREADY_DELETED;
   extern const long ERR_HOLDING_COMPANY_CODE_IS_ALREADY_DELETED;
   extern const long ERR_CODE_USED_BY_FUNDSPONSOR_CANNOT_DELETE;
   extern const long ERR_DUPLICATE_PARENT_FUND_CLASS;
   extern const long ERR_ACCTREGDETAILS_NOT_AVAILABLE;
   extern const long ERR_UNABLE_TO_MODIFY_ACCTREGDETAILS;
   extern const long ERR_ACCT_REG_DETAILS_DOES_NOT_EXIST;
   extern const long ERR_TRANSACTION_CANNOT_BE_CANCELLED_BEFORE_NIGHT_RUN;   
   extern const long ERR_FULL_PARTIAL_EXEMPTION_SCOPE_EXIST_ACCT_FUND_CLASS;
   extern const long ERR_ENT_REG_LOCKED;
   extern const long ERR_ENT_REG_NOT_AVAIL;
   extern const long ERR_ENT_REG_VER_DIFF;
   extern const long ERR_ENT_REG_DUP_ID_REG;
   extern const long ERR_ENT_REG_JUR_LOCKED;
   extern const long ERR_ENT_REG_JUR_NOT_AVAIL;
   extern const long ERR_ENT_REG_JUR_VER_DIFF;
   extern const long ERR_ENT_REG_JUR_DUP_TAX;
   extern const long ERR_PLEASE_CANCLE_MONEY_OUT_TEANS_FOR_BACKDATED_PRIOR;
   extern const long ERR_TRADE_DATE_DELAY_EXIST_FOR_FUNDCLASS_UNABLE_TO;
   extern const long ERR_TRADE_DATE_IS_IN_FUTURE_FOR_THE_SELECTED_VALUATION_DATE;
   extern const long ERR_DILUTION_RECORD_IS_NOT_AVAIL;
   extern const long ERR_ENTER_A_VALID_SUPPRESS_CODE_FOR_PAYTYPE_X_OR_BLANK_FOR_S;
   extern const long ERR_PF_CRYSTALISATION_IS_NOT_YET_COMPLETED_FOR_FUNDCLASS;
   extern const long ERR_SHARELOT_UNITS_DO_NOT_MATCH_TRANSACTION_UNITS;
   extern const long ERR_NO_SHAARELOT_RECORD_AVAILABLE;
   extern const long ERR_MISMATCHED_UNITS_AVAIL;
   extern const long ERR_CANNOT_CALCULATE_EUSD;
   extern const long ERR_TRADE_DOES_NOT_BELONG_TO_EXISTING_FUND;
   extern const long ERR_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT;
   extern const long ERR_CONTRACT_TYPE_IS_NOT_FOUND_FOR_THIS_ACCOUNT;
   extern const long ERR_CANCEL_ALL_TRANS_OR_CHANGE_TRADEDATE;
   extern const long ERR_TRADE_ALREADY_VERIFIED;
   extern const long ERR_INVALID_VALUATION_DATE_FOR_FUND_CLASS;
   extern const long ERR_ACCOUNT_ALREADY_IN_MAIL_HOUSEHOLD;
   extern const long ERR_ACCOUNT_NOT_ASSOCIATED;
   extern const long ERR_COPY_FAIL_EXPIRED_FEE_MODEL;
   extern const long ERR_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE;
   extern const long ERR_FUND_CLASS_IS_NOT_LINKED_TO_CURRENT_ACTIVE_AMS_MODEL;
   extern const long ERR_ERJD_EXISTS;
   extern const long ERR_ALLOCATION_NOT_SUPPORT;
   extern const long ERR_LINK_TYPE_IS_NOT_FOUND;
   extern const long ERR_DBRKR_DILUTION_LINK_ID_DOES_NOT_EXIST;
   extern const long ERR_DBRKR_FUND_SUSPENDED_NO_TRANSACTIONS_ALLOWED;
   extern const long ERR_DBRKR_REDEMPTIONS_SUSPENDED_LIQUIDITY_MEASURE;
   extern const long ERR_DBRKR_RDSP_CANNOT_CANCEL_MONEY_IN_BEFORE_MONEY_OUT;
   extern const long ERR_DBRKR_RDSP_CANNOT_CANCEL_RECONCILED_EXTERNAL_TRANSFER_IN;
   extern const long ERR_DBRKR_RDSP_CANNOT_CANCEL_REPORTED_EXTERNAL_TRANSFER_IN;
}

namespace 
{

   const I_CHAR *const CLASSNAME          = I_( "DSTCRequestor" );
   const I_CHAR *const RECEIVE_BUFFER     = I_( "receiveBuffer" );
   const I_CHAR *const RECEIVE            = I_( "receive" );

   const I_CHAR *const IDI_ERROR_CODE     = I_( "code" );
   const I_CHAR *const IDI_ERROR_MSG      = I_( "msg" );
   const I_CHAR *const IDI_ERROR_TRACKID  = I_( "trackid" );

   const long hostConditionArray[][2] = { { CND::ERR_UNKNOWN_ERROR      , -1 },
        //{ CND::ERR_DATA_OK                                            ,  0 },
        { CND::ERR_DATA_NOT_FOUND                                       ,  1 },
        //{ Access denied, section
        { CND::ERR_AD_AFTER_MANDATORY_LOGOFF_TIME                       ,  2 },
        { CND::ERR_AD_BEFORE_ALLOWABLE_LOGON_TIME                       ,  3 },
        { CND::ERR_AD_INVALID_PASSWORD                                  ,  4 },
        { CND::ERR_AD_INVALID_PROFILE                                   ,  5 },
        { CND::ERR_AD_MAXIMUM_SESSIONS_ALREADY_RUNNING                  ,  6 },
        { CND::ERR_AD_NO_COMPANY_ACCESS                                 ,  7 },
        { CND::ERR_AD_PAST_PASSWORD_GRACE_PERIOD                        ,  8 },
        { CND::ERR_AD_PROFLE_HAS_NO_ACCESS_TODAY                        ,  9 },
        { CND::ERR_AD_SHAREHOLDER_DOES_NOT_EXIST                        , 10 },
        { CND::ERR_AD_TOO_MANY_FAILED_LOGONS                            , 11 },
        { CND::ERR_AD_UNKNOWN_ACCESS_PROFILE                            , 12 },
        { CND::ERR_AD_UNKNOWN_USER                                      , 13 },
        { CND::ERR_AD_USER_ACCOUNT_NOT_ACTIVE                           , 14 },
        { CND::ERR_AD_USER_HAS_NO_COMPANY_ACCESS                        , 15 },
        //End Access denied, section }
        { CND::ERR_COULD_NOT_CREATE_THE_SHAREHOLDER_REMARKS_RECORD      , 16 },
        { CND::ERR_EFT_PAYMENT_DETAILS_NOT_FOUND                        , 17 },
        { CND::ERR_INVALID_PROFILE                                      , 18 },
        { CND::ERR_NO_MATCHES_FOUND                                     , 19 },
        //{ Password denied, section
        { CND::ERR_PD_THREE_OF_SAME_CHARS_NOT_ALLOWED                   , 20 },
        { CND::ERR_PD_CANNOT_CHANGE_PASSORD_FOR                         , 21 },
        { CND::ERR_PD_HAS_BEEN_USED_RECENTLY_CHOOSE_ANOTHER             , 22 },
        { CND::ERR_PD_NEED_TWO_OR_MORE_NON_ALPHA_CHARS                  , 23 },
        { CND::ERR_PD_NEED_TWO_OR_MORE_ALPHABETIC_CHARS                 , 24 },
        { CND::ERR_PD_NO_BLANKS_ALLOWED                                 , 25 },
        { CND::ERR_PD_OLD_PASSWORD_INCORRECT                            , 26 },
        { CND::ERR_PD_ONLY_ONE_REPETITION_OF_CHARS_ALLOWED              , 27 },
        { CND::ERR_PD_ONLY_SEVEN_CHARS_IN_A_ROW                         , 28 },
        { CND::ERR_PD_PASSWORD_CAN_ONLY_BE                              , 29 },
        { CND::ERR_PD_PASSWORD_MUST_BE_AT_LEAST                         , 30 },
        { CND::ERR_PD_UNKNOWN_ACCESS_PROFILE                            , 31 },
        { CND::ERR_PD_UNKNOWN_USER                                      , 32 },
        //End Password denied, section }
        { CND::ERR_TRANSACTION_NOT_FOUND                                , 33 },
        { CND::ERR_UNKNOWN_ACCOUNT                                      , 34 },
        { CND::ERR_UNKNOWN_START_DATE                                   , 35 },
        { CND::ERR_JOINT_INFORMATION_ONLY_FOR_JOINT_ACCOUNTS            , 36 },
        { CND::ERR_PENDING_TRADE_NOT_FOUND                              , 37 },
        { CND::ERR_TRADE_NOT_FOUND                                      , 38 },
        { CND::ERR_CHEQUE_NOT_FOUND                                     , 39 },
        { CND::ERR_ACCOUNT_ENTITY_NOT_FOUND                             , 40 },
        { CND::ERR_ENTITY_NOT_FOUND                                     , 41 },
        { CND::ERR_REGISTERED_ADDRESS_DEFAULT_NOT_FOUND                 , 42 },
        { CND::ERR_BROKER_NOT_FOUND                                     , 43 },
        { CND::ERR_INTERMEDIARY_NOT_FOUND                               , 44 },
        { CND::ERR_ENTITY_NOT_ASSOCIATED_WITH_AN_ACCOUNT                , 45 },
        { CND::ERR_ACCOUNT_NUMBER_IS_INVALID                            , 46 },
        { CND::ERR_NOT_ENOUGH_INPUT_INFO_FOR_RECORD_SELECTION           , 47 },
        { CND::ERR_SALESREP_CANNOT_ACCESS_THIS_ACCOUNT                  , 48 },
        { CND::ERR_PLEASE_SEND_AGAIN_AS_LAST_RECORD_WAS_DELETED         , 49 },
        { CND::ERR_INVALID_FUND_CODE                                    , 50 },
        { CND::ERR_NEXT_KEY_DID_NOT_MATCH_EXPECTED_FORMAT               , 51 },
        { CND::ERR_NO_INTEREST_ACCRUAL_INFORMATION_AVAILABLE            , 52 },
        { CND::ERR_AS_OF_DATE_WAS_NOT_ENTERED                           , 53 },
        { CND::ERR_INVALID_CLASS_CODE                                   , 54 },
        { CND::ERR_NO_ADDRESS_RECORD_AVAILABLE                          , 55 },
        { CND::ERR_INVALID_CHUIR                                        , 56 },
        { CND::ERR_CLAN_PLAN_NOT_AVAILABLE                              , 57 },
        { CND::ERR_NO_RELATED_CHUI_FUNCTIONS                            , 58 },
        { CND::ERR_NO_RESP_ACCOUNT_INFORMATION                          , 59 },
        { CND::ERR_ALLFUNDS_OR_FUND_CLASSCODE                           , 60 },
        { CND::ERR_NO_SETUP_RECORD                                      , 61 },
        { CND::ERR_INPUT_ACCOUNT_IS_NOT_RESP                            , 62 },
        { CND::ERR_INPUT_ACCOUNT_IS_NOT_RIF                             , 63 },
        { CND::ERR_NO_RIF_SETUP_INFO                                    , 64 },
        { CND::ERR_NO_RIF_ALLOCATION_INFO                               , 65 },
        { CND::ERR_PASSWORD_DENIED_CHANGE_NO_ALLOWED                    , 66 },
        { CND::ERR_RECORD_LOCKED                                        , 67 },
        { CND::ERR_UNABLE_TO_UPDATE_RECORD                              , 68 },
        { CND::ERR_UNABLE_TO_DELETE_LAST_ADDRESS                        , 69 },
        { CND::ERR_UNABLE_TO_ADD_RECORD_ADDRESS_EXISTS                  , 70 },
        { CND::ERR_REGISTER_ADDRESS_NOT_AVAILABLE                       , 71 },
        { CND::ERR_NO_BENEFICIARY_RECORD_AVAILABLE                      , 72 },
        { CND::ERR_NO_ESCROW_REP_RECORD_AVAILABLE                       , 73 },
        { CND::ERR_NON_JOINT_ACCOUNT_ONE_ACCOUNTHOLDER                  , 74 },
        { CND::ERR_ACCOUNT_MAY_ONLY_HAVE_ONE_NOMINEE_OWNER              , 75 },
        { CND::ERR_CLIENT_ACCOUNT_CANNOT_HAVE_A_NOMINEE_OWNER           , 76 },
        { CND::ERR_UNABLE_TO_DELETE_RECORD                              , 77 },
        //{ CND::ERR_NO_MESSAGE                                         , 78 },
        { CND::ERR_NO_JOINT_ENTITY_RECORD_AVAILABLE                     , 79 },
        { CND::ERR_NOT_AN_EFT_TRANSACTION                               , 80 },
        { CND::ERR_INVALID_GROUP                                        , 81 },
        { CND::ERR_INVALID_SHAREHOLDER                                  , 82 },
        { CND::ERR_UNABLE_TO_ADD_RECORD_ACCOUNT_EXISTS                  , 83 },
        { CND::ERR_SHAREHOLDER_NUMBER_GREATER_THEN_ZERO                 , 84 },
        { CND::ERR_SHAREHOLDER_NUMBER_NOT_GREATER_THEN_SIX_DIGITS       , 85 },
        { CND::ERR_INVALID_MRS_ACCOUNT                                  , 86 },
        { CND::ERR_INVALID_GROUP_CODE                                   , 87 },
        { CND::ERR_UNABLE_TO_ADD_RECORD_SHAREHOLDER_EXISTS              , 88 },
        { CND::ERR_ADDRESS_USED_FOR_MAILING                             , 89 },
        { CND::ERR_RUN_MODE_INVALID                                     , 90 },
        { CND::ERR_CONTROLS_NAME_RECORD_ENTITYID_NOT_FOUND              , 91 },
        { CND::ERR_UNABLE_TO_DELETE_ENTITY                              , 92 },
        { CND::ERR_UNABLE_TO_MODIFY_ENTITY                              , 93 },
        { CND::ERR_IDENTIFICATION_RECORD_NOT_EXIST                      , 94 },
        { CND::ERR_INVALID_ID_TYPE                                      , 95 },
        { CND::ERR_USER_ACCESS_RECORD_NOT_FOUND                         , 96 },
        { CND::ERR_USER_STATUS_IS_INACTIVE_IN_COMPANY_DB                , 97 },
        { CND::ERR_ACCT_UPDATE_FAILED_AS_ACCTENTITY_UPDATE_FAILED       , 98 },
        { CND::ERR_WRONG_SHRHOLDER_VERSION                              , 99 },
        { CND::ERR_PERSISTENT_NEEDED                                    , 100 },
        { CND::ERR_NO_ACTIVE_BATCH                                      , 101 },
        { CND::ERR_NO_SLSREP_FOUND                                      , 102 },
        { CND::ERR_NO_BRANCH_FOUND                                      , 103 },
        { CND::ERR_DUPLICATE_DISTRIBUTION                               , 104 },
        { CND::ERR_DISTRIBUTION_IS_LOCKED                               , 105 },
        { CND::ERR_DISTRIBUTION_NOT_FOUND                               , 106 },
        { CND::ERR_WRONG_DISTRIBUTION_VERSION                           , 107 },
        { CND::ERR_DISTRIBANK_IS_LOCKED                                 , 108 },
        { CND::ERR_DISTRIBANK_NOT_FOUND                                 , 109 },
        { CND::ERR_WRONG_BANK_VERSION                                   , 110 },
        { CND::ERR_NOT_VALID_FUND                                       , 111 }, 
        { CND::ERR_DUPLICATE_SYSTEMATIC                                 , 112 },
        { CND::ERR_DUPLICATE_AUTO_TRANSFER                              , 113 },
        { CND::ERR_NO_ACCESS_TO_SLSREP                                  , 114 },
        { CND::ERR_DATE_OF_BIRTH_MANDATORY                              , 115 },
        { CND::ERR_MATURITY_DATE                                        , 116 },
        { CND::ERR_CLOSEACCTCODE_NOT_FUND                               , 117 },
        { CND::ERR_WITHOUT_FULL_REDEMPTION                              , 118 },
        { CND::ERR_NO_ACCOUNTHOLDING                                    , 119 },
        { CND::ERR_UNITS_NOT_ALLOWED                                    , 120 },
        { CND::ERR_FULL_REDEMPTION_NOT_ALLOWED                          , 121 },
        { CND::ERR_REDEMPTIONCODE_NOT_AVAILABLE                         , 122 },
        { CND::ERR_INVALID_FUND_AND_CLASS                               , 123 },
        { CND::ERR_AMOUNT_GREATER                                       , 124 },
        { CND::ERR_TAX_TYPES_RULES_NOT_SET_UP                           , 125 },
        { CND::ERR_PENSION_INFORMATION_NA                               , 126 },
        { CND::ERR_THIS_TAX_TYPE_NOT_LOCKED_IN                          , 127 },
        { CND::ERR_MISSING_ALLOCATION_INFO                              , 128 },
        { CND::ERR_NO_CLAN_PLAN_UPDATE                                  , 129 },
        { CND::ERR_BROKER_NOT_ELIGIBLE                                  , 130 },
        { CND::ERR_NO_FUTURE_DATE_MIN_MAX                               , 131 },
        { CND::ERR_INVALID_SORT_BY                                      , 132 },
        { CND::ERR_INVALID_REQUEST_TYPE                                 , 133 },
        { CND::ERR_DATA_PROBLEM_MISSING_PRICE                           , 134 },
        { CND::ERR_NO_PENDING_TRADES_FOUND                              , 135 },
        { CND::ERR_NO_PROCESSED_TRADES_FOUND                            , 136 },
        { CND::ERR_NO_MAILING_INFO_AVAILABLE                            , 137 },
        { CND::ERR_DATABASE_UNAVAILABLE                                 , 150 },
        { CND::ERR_DATABASE_NOT_CONNECTED                               , 151 },
        { CND::ERR_NO_COMPANY_RECORD                                    , 152 },
        { CND::ERR_UNKNOW_RESPONSE_TYPE                                 , 153 },
        { CND::ERR_ACCESS_DENIED_NO_SESSION_RECORD                      , 154 },
        { CND::ERR_ACCESS_DENIED_PASSWORD_MUST_BE_RESET                 , 155 },
        { CND::ERR_ACCESS_DENIED_PASS_LOGOFF_TIME                       , 156 },
        { CND::ERR_BANK_RECORD_SHOULD                                   , 157 },
        { CND::ERR_CANNOT_PRINT_DUPLICATE                               , 158 },
        { CND::ERR_NO_ACCT_CONTRACT_AVAILABLE                           , 159 },
        { CND::ERR_REMARKS_NO_FOUND                                     , 160 },
        { CND::ERR_DISTRIB_NA                                           , 161 },
        { CND::ERR_BANKACCT_NOT_FOUND                                   , 162 },
        { CND::ERR_TRANSACTION_TYPE_INVALID                             , 163 },
        { CND::ERR_ADDRID_NOT_FOUND                                     , 164 },
        { CND::ERR_ENTITY_ADDR_NA                                       , 165 },
        { CND::ERR_ENTITY_ADDR_XREF_NA                                  , 166 },
        { CND::ERR_ACCT_ENTITY_BENEF_NOT_FOUND                          , 167 },
        { CND::ERR_ACCT_ENTITY_JOINT_NOT_FOUND                          , 168 },
        { CND::ERR_ASSIGN_INFO_NOT_FOUND                                , 169 },
        { CND::ERR_SECURITY_SETUP_NOT_FOUND                             , 170 },
        { CND::ERR_PROVINCE_FILE_NA                                     , 171 },
        { CND::ERR_DEALER_FUNDS_NA                                      , 172 },
        { CND::ERR_ADDRESS_CODE_AT_LEAST_TWO                            , 173 },
        { CND::ERR_FUND_INFO_NOT_FOUND                                  , 174 },
        { CND::ERR_INST_CODE_EXCEEDS                                    , 175 },
        { CND::ERR_TRANSIT_NO_EXCEEDS                                   , 176 },
        { CND::ERR_BANK_ACC_NUMERIC                                     , 177 },
        { CND::ERR_BANK_ACC_MUST_BE_ENTERED                             , 178 },
        { CND::ERR_BANK_ACC_EXCEEDS                                     , 179 },
        { CND::ERR_ERROR_UPD_BANK_TABLE                                 , 180 },
        { CND::ERR_CANNOT_DELETE_ACCOWNER                               , 181 },
        { CND::ERR_NO_ACCOUNT_SHR_NUMBER                                , 182 },
        { CND::ERR_PROGRESS_ERROR                                       , 183 },
        { CND::ERR_SEARCH_FOR_SLSREP_BY_BROKER_CODE                     , 184 },
        { CND::ERR_FUND_RECORD_NA                                       , 185 },
        { CND::ERR_FEE_RECORD_NA                                        , 186 },
        { CND::ERR_NO_USERID                                            , 187 },
        { CND::ERR_NO_UNIQE_NAME_FOUND                                  , 188 },
        { CND::ERR_ACCOUNTENTITY_ALREADY_EXISTS                         , 189 },
        { CND::ERR_TRANSNUM_ALREADY_EXISTS                              , 190 },
        { CND::ERR_PENDING_TRADE_NOT_EXISTS                             , 191 },
        { CND::ERR_PENDING_TRADE_BANK_INVALID                           , 192 },
        { CND::ERR_INVALID_DEPOSIT_ID                                   , 193 },
        { CND::ERR_AMOUNT_SHOULD_MANDATORY                              , 194 },
        { CND::ERR_BATCH_CANNOT_BE_BLANK                                , 195 },
        { CND::ERR_BATCH_NOT_ACTIVE                                     , 196 },
        { CND::ERR_NO_ENOUGH_INPUT                                      , 197 },
        { CND::ERR_BANK_INFO_IS_MANDATORY_FOR_EFT                       , 198 },
        { CND::ERR_BATCHTYPE_INVALID                                    , 199 },
        { CND::ERR_BATCHNAME_SHOULD_BLANK                               , 200 },
        { CND::ERR_BATCHNAME_CANNOT_BLANK                               , 201 },
        { CND::ERR_INVALID_FUND_GROUP_TYPE                              , 202 },
        { CND::ERR_INVALID_TRANSID_CURRENCY_FOR_TRANBANKING             , 203 },
        { CND::ERR_ACCOUNTENTITY_NOT_FOUND                              , 205 },
        { CND::ERR_CONTRACT_RECORD_NOT_FOUND                            , 206 },
        { CND::ERR_CYCLE_RUN_UNAVAILABLE                                , 207 },
        { CND::ERR_NO_CONTRACTMSTR                                      , 208 },
        { CND::ERR_NO_COT_CONTRACT_SHGROUP                              , 209 },
        { CND::ERR_UNABLE_MODIFY_COT_ACCT_CONTRACT                      , 210 },
        { CND::ERR_RRIFINFO_ALREADY_EXISTS                              , 211 },
        { CND::ERR_INVALID_CALLNUM                                      , 212 },
        //{ CND::ERR_INVALID_FROM_CURRENCY                              , 213 },
        //{ CND::ERR_EXCH_RATE_NOT_AVAILABLE                            , 214 },
        { CND::ERR_BANKMST_UNAVAILABLE                                  , 215 },
        { CND::ERR_BATCHES_NOT_MATCH                                    , 216 },
        { CND::ERR_INVALID_VALIDATION_TYPE                              , 217 },
        { CND::ERR_INVALID_BROKER_CODE                                  , 218 },
        { CND::ERR_TAX_TYPE_NOT_FOUND                                   , 219 },
        { CND::ERR_INVALID_CODE_TYPE                                    , 220 },
        { CND::ERR_NO_PURCHASE                                          , 221 },
        { CND::ERR_RRIF_DETAIL_RECID_INVALID                            , 222 },
        { CND::ERR_UNITDETL_NOT_FOUND                                   , 223 },
        { CND::ERR_POSTAL_CODE_NOT_FOUND                                , 224 },
        { CND::ERR_INSUFFICIENT_INFO                                    , 225 },
        { CND::ERR_STREET_NAME_NOT_FOUND                                , 226 },
        { CND::ERR_BOX_NUM_NOT_FOUND                                    , 227 },
        { CND::ERR_APARTMENT_NUM_MISSING                                , 228 },
        { CND::ERR_MULITIPLE_ADDRESS                                    , 229 },
        { CND::ERR_INVALID_ADDRESS                                      , 230 },
        { CND::ERR_NO_TAXTYPE_AVAILABLE                                 , 231 },
        { CND::ERR_INVALID_DEPOSIT_TYPE                                 , 232 },
        { CND::ERR_ENTITYTYPE_MUST_POPULATED                            , 233 },
        { CND::ERR_ORIGTRANSLD_MUST_BLANK                               , 234 },
        { CND::ERR_NOT_CONFIGURED                                       , 235 },
        { CND::ERR_SEQNUM_NOT_EXIST                                     , 236 },
        { CND::ERR_TIME_ZONE_INVALID                                    , 237 },
        { CND::ERR_FINANCIAL_TIMEZONE_INVALID                           , 238 },
        { CND::ERR_UNABLE_ASSIGN_CONNUM                                 , 239 },
        { CND::ERR_TRADE_DATE_FUTURE                                    , 240 },
        { CND::ERR_RECIPIENT_INFO_NOT_SET_UP                            , 241 },
        { CND::ERR_NO_DEP_ID_RECORDS_AVAILABLE                          , 242 },
        { CND::ERR_INVALID_RESON_CODE                                   , 243 },
        { CND::ERR_ACTIVE_CONTRACT_EXISTS                               , 244 },
        { CND::ERR_FUNDTO_CLASSTO_CANNOT_BLANK_FOR_TRANSFERS            , 245 },
        { CND::ERR_USERTYPE_DOES_NOT_HAVE_ACCESS                        , 246 },
        { CND::ERR_SECURITY_PROFILE_DOES_NOT_HAVE_ACCESS                , 247 },
        { CND::ERR_EFFECTIVE_DATE_PRIOR_TO_LAST_RUN                     , 248 },
        { CND::ERR_WRONG_BANKENTITY                                     , 249 },
        { CND::ERR_BROKER_NOT_ENTERED                                   , 250 },
        { CND::ERR_BROKER_BRANCH_NOT_ENTERED                            , 251 },
        { CND::ERR_BROKER_BRANCH_SLSREP_NOT_ENTERED                     , 252 },
        { CND::ERR_BROKER_SLSREP_NOT_ENTERED                            , 253 },
        { CND::ERR_SPLITCOM_FEE_DEF_NOT_FOUND                           , 254 },
        { CND::ERR_FEES_WAIVED                                          , 255 },
        { CND::ERR_TRANSFER_NOT_BUY_OR_SELL                             , 256 },
        { CND::ERR_NO_COMM_SCALE_RECORD_AVAILABLE                       , 257 },
        { CND::ERR_FEE_PARAMS_NOT_AVAILABLE                             , 258 },
        { CND::ERR_LAST_BANK_TYPE_MUST_BE                               , 259 },
        { CND::ERR_ACCT_NUM_BLANK_FOR_TRANSPENDING                      , 260 },
        { CND::ERR_TRANSPENDING_MUST_BE                                 , 261 },
        { CND::ERR_FUND_NOT_ELIGIBLE_FOR_COMMISSION                     , 262 },
        { CND::ERR_INVALID_BANKTYPE                                     , 263 },
        { CND::ERR_TRANSIT_NUMBER_MUST_BE_ENTERED                       , 264 },
        { CND::ERR_BANKTYPE_IDNUM_NOT_ENTERED                           , 265 },
        { CND::ERR_INVALID_REPEAT_RECORD_TYPE                           , 266 },
        { CND::ERR_PLAN_CODE_NOT_FOUND                                  , 267 },
        { CND::ERR_DUPLICATE_CONTRACT                                   , 268 },
        { CND::ERR_CANNOT_DELETE_CONTRACT_ACCOUNT_ACTIVITY              , 269 },
        { CND::ERR_CYCLE_RUNNING                                        , 270 },
        { CND::ERR_SPLITCOM_EXISTS                                      , 271 },
        { CND::ERR_AMT_LESS_THAN_MIN_INIT_REDEMP                        , 272 },
        { CND::ERR_AMT_MAY_LESS_THAN_MIN_INIT_REDEMP                    , 273 },
        { CND::ERR_AMT_IS_LESS_THAN_MIN_SUBSEQ_REDEMP                   , 274 },
        { CND::ERR_AMT_MAY_LESS_THAN_MIN_SUBSEQ_REDEMP                  , 275 },
        { CND::ERR_FUNDCLASS_BAL_LESS_THAN_MIN                          , 276 },
        { CND::ERR_FUNDCLASS_BAL_MAY_LESS_THAN_MIN                      , 277 },
        { CND::ERR_ACCT_BAL_WILL_BE_LESS_MIN                            , 278 },
        { CND::ERR_ACCT_BAL_MAY_BE_LESS_MIN                             , 279 },
        { CND::ERR_AMT_IS_LESS_FUND_PURC_MIN                            , 280 },
        { CND::ERR_AMT_MAY_LESS_FUND_PURC_MIN                           , 281 },
        { CND::ERR_MIN_INITIAL_PURCH                                    , 282 },
        { CND::ERR_COMM_ENTITY_DOES_NOT_EXIST                           , 283 },
        { CND::ERR_MUST_HAVE_ONE_ACTIVE_REC                             , 284 },
        { CND::ERR_INVALID_ENTITY_TYPE_SPLIT_COMM                       , 285 },
        { CND::ERR_ACCOUNT_SPLITCOMM_RECORD_EXISTS                      , 286 },
        { CND::ERR_NO_TITLE_RESTRICT_REC_AVAIL                          , 287 },
        { CND::ERR_ACCOUNT_SPLITCOMM_NOT_FOUND                          , 288 },
        { CND::ERR_INVALID_TAX_TYPE_ACCT_TYPE                           , 289 },
        { CND::ERR_UNABLE_TO_MOD_PAC_INDEX_RID_DIFF                     , 290 },
        { CND::ERR_PAC_INDEX_LOCKED_BY_ANOTHER_USER                     , 291 },
        { CND::ERR_CANNOT_LOCATE_PAC_INDEX_REC                          , 292 },
        // 292 duplicate
        //    { CND::ERR_NO_ESOP_INFO_REC_AVAIL                         , 292 },
        { CND::ERR_UNABLE_TO_ADD_ESOP_REC                               , 293 },
        { CND::ERR_CONTRACT_EXIST_BUT_NOT_EFFECTIVE                     , 294 },
        { CND::ERR_ANNUIT_AGE_GREATER_THAN_MIN                          , 295 },
        { CND::ERR_AMS_CODE_NOT_VALID                                   , 296 },
        { CND::ERR_DISTRIB_TO_CASH_NOT_ALLOWED                          , 297 },
        { CND::ERR_NO_AMS_RECORD                                        , 298 },
        { CND::ERR_PRODUCT_GROUP_CODE_INVALID                           , 299 },
        { CND::ERR_NO_PRODUCT_GROUP_CODE                                , 300 },
        { CND::ERR_OVERLAPPING_OR_SAME_DAY_COMMISSION                   , 301 },
        { CND::ERR_SYSTEM_UNAVAILABLE                                   , 302 },
        { CND::ERR_CONTRACT_MATURITY_DATE_GREATER_THAN_LEGAL            , 303 },
        { CND::ERR_ONLINE_ACCESS_FOR_CLIENT_HELD_ACC                    , 304 },
        { CND::ERR_MULTIPLE_ENTITIES_MATCH                              , 305 },
        { CND::ERR_ACC_LASTNAME_POSTALCODE_BLANK                        , 306 },
        { CND::ERR_ACCOUNT_INACTIVE                                     , 307 },
        { CND::ERR_REQUEST_FIELDS_INVALID                               , 308 },
        { CND::ERR_RB_DEFAULT_ALLOCATION_NOT_SET_UP                     , 309 },
        { CND::ERR_VALUATION_SCHEDULE_GROUP_FUND_SETUP                  , 310 },
        { CND::ERR_NO_VALUATION_SCHEDULE_FOR_FUNDGROUP                  , 311 },//no 311 error
        { CND::ERR_NO_VALUATION_SCHEDULE_GROUP_FUND_SETUP               , 312 },
        { CND::ERR_SALES_REP_DOES_NOT_EXIST                             , 313 },
        { CND::ERR_SALES_REP_NO_LONGER_ACTIVE                           , 314 },
        { CND::ERR_PAST_CUT_OFF_TIME                                    , 315 },
        { CND::ERR_INVALID_USER_ID                                      , 316 },
        { CND::ERR_USER_CANNOT_ACCESS_ACCOUNT                           , 317 },
        { CND::ERR_USER_ID_EXIST                                        , 318 },
        { CND::ERR_PASSWORD_DENIED_TOO_SHORT                            , 319 },
        { CND::ERR_PASSWORD_DENIED_TOO_LONG                             , 320 },
        { CND::ERR_INVALID_MODE                                         , 321 },
        { CND::ERR_USER_ID_NEDEED                                       , 322 },
        { CND::ERR_IDENTIFYING                                          , 323 },
        { CND::ERR_USER_EXISTS                                          , 324 },
        { CND::ERR_USER_DOES_NOT_EXISTS                                 , 325 },
        { CND::ERR_EXCHANGE_RATE_NOT_AVAIL                              , 326 },
        { CND::ERR_MORE_THAN_ONE_MATCH_THE_SEARCH_CRITERIA              , 327 },
        { CND::ERR_BROKERCODE_AND_SRCHALTACCOUNT_MUST_BE_PROVIDED       , 328 },
        { CND::ERR_NO_ESOP_INFO_RECORD_AVAILIABLE                       , 329 },
        { CND::ERR_INTERDETL_RECORD_LOCKED_TRY_AGAIN_LATER              , 330 },
        { CND::ERR_SPLIT_COMMISSION_RECORD_DOES_NOT_EXIST               , 331 },
        { CND::ERR_SPLIT_COMMISSION_RECORD_ALREADY_EXISTS_FOR_THIS_ENTITY , 332 },
        { CND::ERR_CAN_ONLY_DELETE_ON_THE_DATE_RECORD_IS_CREATED        , 333 },
        { CND::ERR_FEE_PARAMETER_ALREADY_EXISTS                         , 334 },
        { CND::ERR_SCALE_DETL_RECORD_NOT_AVAILABLE                      , 335 },
        { CND::ERR_INVALID_ACCRUAL_TYPE                                 , 336 },
        { CND::ERR_NO_FEE_DEFINED_FOR_FEE_OVERRIDE                      , 337 },
        { CND::ERR_NO_FEE_ACCRUAL_INFORMATION_AVAILABLE                 , 338 },
        { CND::ERR_AMOUNT_CANNOT_BE_GREATER_AMOUNT_TYPE_P               , 339 },
        { CND::ERR_CALCULATING_MANAGEMENT_FEE_ACCRUALS                  , 340 },
        { CND::ERR_INVALID_AMOUNT_TYPE                                  , 341 },
        { CND::ERR_INVALID_BAYCOM                                       , 342 },
        //{ CND::, 343 },                                          
        { CND::ERR_AMOUNT_MUST_BE_ZERO_FOR_AMOUNTTYPE_T                 , 344 },
        { CND::ERR_NOT_APPLICABLE_FOR_THIS_FUNDCLASS                    , 345 },
        { CND::ERR_NO_PENSION_INFO_REC_AVAIL                            , 346 },
        { CND::ERR_UNABLE_TO_ADD_PENSION_RECORD                         , 347 },
        { CND::ERR_ACCOUNT_REVIEW_DETAIL_NOT_FOUND                      , 348 },
        { CND::ERR_ACCOUNT_REVIEW_RECORD_EXISTS                         , 349 },
        { CND::ERR_INVALID_SEARCH_TYPE                                  , 350 },
        { CND::ERR_FUNDCODE_CANNOT_BE_BLANK_BANK_ENTITY                 , 351 },
        { CND::ERR_INVALID_DATE_RANGE                                   , 352 },
        { CND::ERR_ADDR_CODE_EXISTS_FOR_ENTITY                          , 353 },
        { CND::ERR_PROCESS_TYPE_MUST_BE_11                              , 354 },
        { CND::ERR_CALCULATING_DIVIDENTS                                , 355 },
        { CND::ERR_TRANS_MODIFIED_UNABLE_SETTLE                         , 356 },
        { CND::ERR_INVALID_TRANSLATIONTYPE                              , 357 },
        { CND::ERR_INVALID_LANG                                         , 358 },
        { CND::ERR_DELIVERY_METHOD_EXISTS_FOR_DOC_TYPE                  , 359 },
        { CND::ERR_NO_ACTENTDELOPTN_REC_AVAIL                           , 360 },
        //{ CND::, 361 },
        { CND::ERR_SEE_ERROR_LOG_REDEMLOGD                              , 362 },
        { CND::ERR_REMAINING_ACCT_BAL_INSUFFICIENT                      , 363 },
        { CND::ERR_TAX_TYPE_RULE_NOT_AVAIL                              , 364 },
        { CND::ERR_SCHEDULED_PAYMENT_NOT_AVAIL                          , 365 },
        { CND::ERR_REDEMP_CODE_RULE_NOT_SETUP                           , 366 },
        { CND::ERR_REMAIN_MIN_AMT_REDEPM_NOT_PROCESSED                  , 367 },
        { CND::ERR_FUND_IS_NOT_ESOP_ELIGIBLE                            , 368 },
        { CND::ERR_PROCESS_REDEMP_ESOP_INVEST                           , 369 },
        { CND::ERR_PROCESS_REDEMP_ESOP_PARTICIP                         , 370 },
        { CND::ERR_ESOP_MUST_CLOSE_ACCT                                 , 371 },
        { CND::ERR_REDEMP_NOT_ALLOW_ESOP                                , 372 },
        { CND::ERR_CONTRACT_ACCT_STATUS_ACTIVE                          , 373 },
        { CND::ERR_CONTRACT_ACCT_NOT_ACTIVE                             , 374 },
        { CND::ERR_CONTRACT_ACCT_STATUS_DEATH                           , 375 },
        { CND::ERR_NON_INT_AMT_ZERO_PRECISION                           , 376 },
        { CND::ERR_LLP_ERROR                                            , 377 },
        { CND::ERR_ESTATE                                               , 378 },
        { CND::ERR_EXCHANGE_RATE_TAX_CALC_NOT_FOUND                     , 379 },
        { CND::ERR_ACCT_NOT_ACTIVE_AT_TRADE_DATE                        , 380 },
        { CND::ERR_CURRENCY_NOT_ALLOWED_TAX_TYPE                        , 381 },
        { CND::ERR_STOP_DATE_FUND_SAME_TRADE_DATE                       , 382 },
        { CND::ERR_NO_ACCT_VALUE_REC_EXISTS                             , 383 },
        { CND::ERR_TRANS_MUST_BE_VERIFIED                               , 384 },
        { CND::ERR_FIFO_NOT_EXIST                                       , 385 },
        { CND::ERR_NO_AVAIL_UNITS                                       , 386 },
        { CND::ERR_DEALER_NOT_AUTH_TO_DEAL_FUND                         , 387 },
        { CND::ERR_INSUF_FUND_AT_TRADE_DATE                             , 388 },
        { CND::ERR_UNISSUED_CERT_UNIT_EXIST                             , 389 },
        { CND::ERR_EXCEED_USER_SETUP_AMT                                , 390 },
        { CND::ERR_TRADE_IS_THIRTY_OLD_OLDER                            , 391 },
        { CND::ERR_STOP_BEFORE_START                                    , 392 },
        { CND::ERR_INVALID_SETTLE_SOURCE                                , 393 },
        { CND::ERR_INVALID_SETTLE_SOURCE_ACCT_DESIGN                    , 394 },
        { CND::ERR_INVALID_ORDER_SOURCE                                 , 395 },
        { CND::ERR_INVALID_SETTLEMENT_TYPE                              , 396 },
        { CND::ERR_INVALID_SETTLE_TYPE_DEALER_INTERM                    , 397 },
        { CND::ERR_WIRE_ORDER_REDEMP_NOT_ALLOW                          , 398 },
        { CND::ERR_INVALID_ORDER_SOURCE_ACCT_DESGIN                     , 399 },
        { CND::ERR_INTERM_IS_NOT_PERMIT_WIRE                            , 400 },
        { CND::ERR_BROKER_IS_NOT_PERMIT_MONEY_MKT                       , 401 },
        { CND::ERR_DEALER_CANNOT_SETTLE_INTERM                          , 402 },
        { CND::ERR_BATCH_IS_ACTIVE                                      , 403 },
        { CND::ERR_BATCH_IS_LOCKED                                      , 404 },
        { CND::ERR_BATCH_DOES_NOT_EXIST                                 , 405 },
        { CND::ERR_INVALID_REDEMP_CODE                                  , 406 },
        { CND::ERR_GROUP_REDEMP_STOP_FLAG_ENABLE                        , 407 },
        { CND::ERR_REDEMP_STOP_FLAG_ENABLED                             , 408 },
        { CND::ERR_ASSIGNED_FLAG_ENABLED                                , 409 },
        { CND::ERR_FEE_ENTERED_WITHOUT_OVERRIDE                         , 410 },
        { CND::ERR_FULL_REDEMP_NOT_ALLOWED                              , 411 },
        { CND::ERR_REDEMP_NOT_ALLOWED_FUND                              , 412 },
        { CND::ERR_FEE_OVERRIDE_NO_FEE_DEFINED                          , 413 },
        { CND::ERR_ACQ_FEE_CALC_DURING_RUN                              , 414 },
        { CND::ERR_NO_AMOUNT_AVAIL_IN_CASH_FUND                         , 415 },
        { CND::ERR_TYPE_TRANS_NOT_SUPPORT_FAMILY                        , 416 },
        { CND::ERR_ONLY_RD_ALLOW_RESP_TRANSFER                          , 417 },
        { CND::ERR_DP_RD_NOT_ALLOW_TRANSER                              , 418 },
        { CND::ERR_NO_RESPCONTRDETL_REC_AVAIL                           , 419 },
        { CND::ERR_TRADE_DATE_LATER_THAN_RESP_CONTRIB                   , 420 },
        { CND::ERR_RESP_PLAN_LIMIT_EXCEEDED                             , 421 },
        { CND::ERR_RESP_YEAR_LIMIT_EXCEEDED                             , 422 },
        { CND::ERR_NO_EARNING_IN_THE_ACCT                               , 423 },
        { CND::ERR_RESP_REDEMP_EXCEED_EARNINGS                          , 424 },
        { CND::ERR_RESP_REDEMP_EXCEED_CONTRIB                           , 425 },
        { CND::ERR_NOT_ENOUGH_GRANT_AMT_RETURN                          , 426 },
        { CND::ERR_RESP_TRANSFER_AMT_TOO_HIGH                           , 427 },
        { CND::ERR_AMS_CODE_NOT_FOUND                                   , 428 },
        { CND::ERR_CANNOT_DELETE_AMS_CODE_IN_USE                        , 429 },
        { CND::ERR_CANNOT_DELETE_AMSCODE_IN_MSTR                        , 430 },
        { CND::ERR_AMSCODE_ALREADY_EXISTS                               , 431 },
        { CND::ERR_ALLOCATION_EXISTS_FOR_FUND_CLASS                     , 432 },
        { CND::ERR_UNKNOWN_SCHED_USER_INTERFACE                         , 433 },
        { CND::ERR_CANNOT_LOCATE_SCHED_JOB                              , 434 },
        { CND::ERR_INVALID_RESON_CODE                                   , 435 },
        { CND::ERR_JOBID_NOT_GEN_CHECK_PROCESS                          , 436 },
        { CND::ERR_NO_PRINTER_RECORDS_AVAIL                             , 437 },
        { CND::ERR_NO_JOBS_AVAIL                                        , 438 },
        { CND::ERR_NO_PARAM_REC_AVAIL                                   , 439 },
        { CND::ERR_INVALID_VALID_TYPE                                   , 440 },
        { CND::ERR_ACCTNBR_MUST_BE_ENTERED                              , 441 },
        //442
        { CND::ERR_SCALE_REC_REQUIRED_FEE_2_3                           , 443 },
        { CND::ERR_SHAREHOLDER_FAMILY_EXISTS                            , 444 },
        { CND::ERR_DSC_REC_EXISTS_THIS_FAMILY_NO_DELETE                 , 445 },
        { CND::ERR_PROTECTED_FUND_DOES_NOT_EXIST                        , 446 },
        { CND::ERR_FUND_CLASS_USED_IN_ACTIVE_CONTRACT                   , 447 },
        { CND::ERR_PROTECTED_FUND_EXISTS                                , 448 },
        { CND::ERR_INDEX_CODE_CANNOT_BE_BLANK                           , 449 },
        { CND::ERR_MKT_INDEX_RECORD_LOCKED                              , 450 },
        { CND::ERR_MKT_INDEX_NOT_FOUND                                  , 451 },
        { CND::ERR_VERSION_NUM_DO_NOT_MATCH                             , 452 },
        { CND::ERR_MKT_INDEX_EXISTS_WITH_INDEX_CODE                     , 453 },
        { CND::ERR_FUND_RUNMODE_NOT_VALID                               , 454 },
        { CND::ERR_FUND_DETL_REC_IS_LOCKED                              , 455 },
        { CND::ERR_FUND_DETL_DATA_NOT_FOUND                             , 456 },
        //457
        { CND::ERR_ACCT_CAT_REC_DOES_NOT_EXISTS                         , 458 },
        { CND::ERR_CAT_TYPE_EXISTS_FOR_ACCT                             , 459 },
        { CND::ERR_MKT_INDEX_REC_LOCKED                                 , 460 },
        { CND::ERR_MKT_INDEX_DETAIL_NOT_FOUND                           , 461 },
        { CND::ERR_MKT_INDEX_DETAIL_EXISTS                              , 462 },
        { CND::ERR_FROM_TO_DATE_MUST_ENTERED                            , 463 },
        { CND::ERR_INDEX_CODE_MUST_BE_ENTERED                           , 464 },
        { CND::ERR_BROKER_NOT_ELIGIBLE_WRAP                             , 465 },
        { CND::ERR_SLS_REP_NOT_ELIGIBLE_FOR_WRAP                        , 466 },
        { CND::ERR_FUND_DEALER_ELIG_DATA_NOT_FOUND                      , 467 },
        { CND::ERR_BROKER_AMS_NOT_EXIST                                 , 468 },
        { CND::ERR_BROKER_AMS_USED_BY_ACCOUNT                           , 469 },
        { CND::ERR_CANNOT_MODIFY_A_BAD_REC                              , 470 },
        { CND::ERR_BROKER_AMS_ALREADY_EXISTS                            , 471 },
        { CND::ERR_NETWORKORDER_ALREADY_EXISTS                          , 472 },
        { CND::ERR_SPLITCOMM_FEEDEFN_NOT_FOUND                          , 473 },
        { CND::ERR_EXIST_AS_BAD                                         , 474 },

        { CND::ERR_CURRENCY_NOT_AVAILABLE                               , 475 },
        { CND::ERR_MISMATCHED_UNIT_AVAILABLE                            , 476 },
        { CND::ERR_KYC_DATA_NOT_FOUND                                   , 478 },
        { CND::ERR_KYC_RECORD_ALREADY_EXIST                             , 482 },
        { CND::ERR_PAYENTITY_ALREADY_EXIST_FOR_BROKER                   , 483 },
        { CND::ERR_PAYENTITY_DOES_NOT_EXIST                             , 484 },
        { CND::ERR_PAYINSTRUCT_ALREADY_EXISTS_FOR_BROKER                , 485 },
        { CND::ERR_PAYINSTRUCT_DOES_NOT_EXIST                           , 486 },

        { CND::ERR_AMS_RULES_REC_EXISTS                                 , 487 },
        { CND::ERR_BANK_MASTER_REC_EXISTS                               , 488 },
        { CND::ERR_BANK_MASTER_DEL_ON_DATE                              , 489 },
        { CND::ERR_TRANS_NUM_OR_ACCT_REQUIRED                           , 490 },
        { CND::ERR_TRANS_NUM_MANDATORY                                  , 491 },
        // 492 Empty
        { CND::ERR_TRANS_NUM_EXISTS                                     , 493 },
        { CND::ERR_EXT_TRANSFER_ACCT_REC_NON_EXISTANT                   , 494 },
        { CND::ERR_EXT_TRANSFER_ACCT_DETL_NON_EXISTANT                  , 495 },
        { CND::ERR_SHAREHOLDER_RESIDENCY_NOT_VALID                      , 496 },
        { CND::ERR_DTA_REC_DOES_NOT_EXIST                               , 497 },
        { CND::ERR_DTA_REC_EXISTS                                       , 498 },
        { CND::ERR_INVALID_TRANSFER                                     , 499 },
        { CND::ERR_TRANSFER_TRACK_HAS_NONOUTSTANDING                    , 500 },
        { CND::ERR_TRANSFER_TRACK_DEL_IF_OUTSTANDING                    , 501 },
        { CND::ERR_SETTLE_LOC_DOES_NOT_EXIST                            , 502 },
        { CND::ERR_SETTLE_LOC_ALREADY_EXISTS                            , 503 },
        { CND::ERR_SETTLE_LOC_ACCT_DOES_NOT_EXIST                       , 504 },
        { CND::ERR_SETTLE_LOC_ACCT_ALREADY_EXISTS                       , 505 },
        { CND::ERR_NO_DATA_IN_REPEAT_SECTION                            , 506 },
        { CND::ERR_TRANS_CLEARING_SETTLE_REC_EXISTS                     , 507 },
        { CND::ERR_SETTLE_LOC_DATA_NOT_FOUND                            , 508 },
        { CND::ERR_SETTLE_LOC_ACCT_DATA_NOT_FOUND                       , 509 },
        { CND::ERR_NEW_PASSWORD_TOO_LONG                                , 510 },
        { CND::ERR_DAILY_FEE_RECORD_ALREADY_EXISTS                      , 511 },
        { CND::ERR_DAILY_FEE_RECORD_DOES_NOT_EXIST                      , 512 },

        { CND::ERR_ORDER_HEADER_ALREADY_EXISTS                          , 516 },
        { CND::ERR_ORDER_DETAIL_ALREADY_EXISTS                          , 517 },
        { CND::ERR_ORDER_DETAIL_DOES_NOT_EXIST                          , 518 },
        { CND::ERR_PWD_USER_NOT_BE_SAME                                 , 526 },

        { CND::ERR_STOP_PW_FLAG_ACTIVE                                  , 529 },
        { CND::ERR_SHR_FUND_SPONSOR_AGRMNT_ALREADY_EXISTS               , 530 },
        { CND::ERR_SHR_FUND_SPONSOR_AGRMNT_DOES_NOT_EXIST               , 531 },
        { CND::ERR_AMT_EXCEEDS_THRESHOLD_TRADE_LIMIT                    , 532 },

        { CND::ERR_TAXEXEMPT_AUTH_ALREADY_EXISTS                        , 537 },
        { CND::ERR_TAXEXEMPT_AUTH_DOES_NOT_EXIST                        , 538 },
        { CND::ERR_UNABLE_TO_MODIFY_RECORD                              , 539 },
        { CND::ERR_INVALID_FEEMODEL_CODE                                , 540 },
        { CND::ERR_FEEMODEL_LOCKED                                      , 541 },
        { CND::ERR_FEEMODEL_DOES_NOT_EXIST                              , 542 },
        { CND::ERR_FEEMODEL_ALREADY_EXISTS                              , 543 },
        { CND::ERR_FEEMODELCODE_INUSE_CANNOT_DELETE                     , 544 },
        { CND::ERR_FNDSPONSOR_FEEMODEL_DOES_NOT_EXIST                   , 545 },
        { CND::ERR_FNDSPONSOR_FEEMODEL_LOCKED                           , 546 },
        { CND::ERR_FNDSPONSOR_FEEMODEL_NOT_FOUND                        , 547 },
        { CND::ERR_FNDSPONSOR_FEEMODEL_ALREADY_EXISTS                   , 548 },
        { CND::ERR_CANNOT_DELETE_FEEMODEL_CODE                          , 549 },
        { CND::ERR_TRANSACTION_PROCESSED_550                            , 550 },
        { CND::ERR_SETTLEMENT_NOT_ALLOWED_551                           , 551 },
        { CND::ERR_TRANSACTION_CANCELED_552                             , 552 },
        { CND::ERR_MFCS_COMPLIANT_553                                   , 553 },
        { CND::ERR_FEE_MODEL_CODE                                       , 554 },
        { CND::ERR_FUND_SPONSOR_REQUIRED                                , 555 },
        { CND::ERR_INVALID_FUND_SPONSOR                                 , 556 },

        { CND::ERR_TRANSTYPE_RC_REQUIRES_FUNDCLASS                      , 558 },
        { CND::ERR_ALL_REQUEST_FIELDS_BLANK                             , 559 },
        { CND::ERR_ACCOUNT_OR_FUNDBROKER_SHOULD_BE_BLANK                , 560 },
        { CND::ERR_INVALID_FUND_BROKER                                  , 561 },
        { CND::ERR_INVALID_SETTLEMENT_INSTRUCTION_CODE                  , 562 },
        { CND::ERR_AGGREGATION_REF_NUMBER_BLANK                         , 563 },
        { CND::ERR_ROUTING_REF_NUMBER_BLANK                             , 564 },
        { CND::ERR_ORDER_STATUS_BLANK                                   , 565 },
        { CND::ERR_AGGREGATE_ORDER_DOES_NOT_EXIST                       , 566 },
        { CND::ERR_FUND_BROKER_NOT_EXIST                                , 567 },
        { CND::ERR_FUND_BROKER_WHERE_USE_RECORD_NOT_EXIST               , 568 },
        { CND::ERR_PRI_CONTACT_WHERE_USE_RECORD_NOT_EXIST               , 569 },
        { CND::ERR_SEC_CONTACT_WHERE_USE_RECORD_NOT_EXIST               , 570 },
        { CND::ERR_FUND_BROKER_ALREADY_EXIST                            , 571 },
        { CND::ERR_ENTITY_WHEREUSE_ALREADY_EXIST                        , 572 },
        { CND::ERR_CLEARINGSETTLEINSTR_DATA_NOT_FOUND                   , 573 },
        { CND::ERR_CLEARINGSETTLEINSTR_ALREADY_EXISTS                   , 574 },
        { CND::ERR_DEFAULT_FUNDBROKER_ALREADY_EXISTS                    , 575 },
        { CND::ERR_SHR_FUND_BROKER_ALREADY_EXISTS                       , 576 },
        { CND::ERR_BONIMAX_VALUE_LESS_THAN_ZERO                         , 577 },
        { CND::ERR_AMOUNT_EXCEEDS_VARIANCE_LIMIT                        , 578 },
        { CND::ERR_TRADING_TIME_AGGR                                    , 579 },
        { CND::ERR_TRADING_TIME_CLIENT_CUT                              , 580 },
        { CND::ERR_KV_NUM_MUST_BE_ENTERED                               , 581 },
        { CND::ERR_KV_NUM_DOES_NOT_EXIST                                , 582 },
        { CND::ERR_FUND_NON_EXISTANT_UNDER_TYPEVAL                      , 583 },
        { CND::ERR_FUNDIDTYPE_FUNDIDVALUE                               , 584 },
        { CND::ERR_INVALID_ENVELOPE_ID                                  , 585 },
        { CND::ERR_INVALID_ACTIVITY_ID                                  , 586 },
        { CND::ERR_INVALID_PROCESS_ID                                   , 587 },
        { CND::ERR_TRANS_TYPE_REQUIRED                                  , 588 },
        { CND::ERR_NUM_UNITS_REQUIRED                                   , 589 },
        { CND::ERR_TRADE_DATE_REQUIRED                                  , 590 },
        { CND::ERR_WHEREUSE_MUST_BE_01_03                               , 591 },
        { CND::ERR_INVALID_PROCESS_CATEGORY                             , 592 },
        { CND::ERR_ENTITYWHEREUSE_NOT_FOUND                             , 593 },
        { CND::ERR_ENTITYWHEREUSE_EXISTS                                , 594 },
        { CND::ERR_COUNTRY_REQUIRED                                     , 595 },
        { CND::ERR_LINK_CANNOT_BE_DEL                                   , 596 },
        { CND::ERR_INVALID_COMPANY_CODE                                 , 597 },
        { CND::ERR_INVALID_PROCESS_TYPE                                 , 598 },
        { CND::ERR_INVALID_PROCESS_CATEGORY /*REPEAT OF 592 */          , 599 },
        { CND::ERR_CANCEL_INSTR_EXISTS                                  , 600 },
        { CND::ERR_CANCEL_DOES_NOT_EXIST                                , 601 },
        { CND::ERR_DILUTION_DOES_NOT_EXIST                              , 602 },
        { CND::ERR_CANCEL_FAILED                                        , 603 },
        { CND::ERR_DILUTION_RECORDS_EXISTS                              , 604 },
        { CND::ERR_TRADEADJUST_RECORDS_EXISTS                           , 605 },
        { CND::ERR_INVALID_STATUS                                       , 606 },
        { CND::IFASTDBRKR_ERR_USERDEFMAT_DATE_EXISTS                    , 607 },
        { CND::IFASTDBRKR_ERR_USERDEFMAT_RECORD_NOT_FOUND               , 608 },
        { CND::ERR_SPLIT_DILUTION_NOT_ALLOWED                           , 609 },
        { CND::ERR_REASON_ACCOUNTABLE_CAN_NOT_BLANK                     , 610 },
        { CND::ERR_ACCOUNTABLE_SHOULD_BLANK_WHEN_DILUTION_EXISTS        , 611 },
        { CND::IFASTDBRKR_ERR_USERDEFMAT_GREATER_THAN_LEGAL             , 612 },
        { CND::IFASTDBRKR_ERR_USERDEFMAT_BLANK                          , 613 },
        { CND::IFASTDBRKR_ERR_TXN_PERPETUAL_DSC                         , 614 },
        { CND::IFASTDBRKR_ERR_UPDATE_PERPETUAL_DSC_INFO                 , 615 },
        { CND::IFASTDBRKR_ERR_NO_FAMILY_CODE_SHRHOLDER                  , 616 },
        { CND::IFASTDBRKR_ERR_UPDATE_PDSC_INFO                          , 617 },
        { CND::IFASTDBRKR_ERR_REVERSE_INVENTORY_UNITS                   , 618 },
        { CND::IFASTDBRKR_ERR_NIGHTCYCLE_ID_NOT_FOUND                   , 619 },
        { CND::IFASTDBRKR_ERR_ACCT_NOT_ACTIVE                           , 620 },
        { CND::IFASTDBRKR_ERR_TRAN_ACCT_NOT_ACTIVE                      , 621 },
        { CND::IFASTDBRKR_ERR_INSUFFICIENT_UNITS                        , 622 },
        { CND::IFASTDBRKR_ERR_INSUFFICIENT_UNITS_CANCEL                 , 623 },
        { CND::IFASTDBRKR_ERR_ACCT_VALUE_DOES_NOT_EXIST                 , 624 },
        { CND::IFASTDBRKR_ERR_ACCT_CERT_UNIT_NOT_ENOUGH                 , 625 },
        { CND::IFASTDBRKR_ERR_ACCT_BALANCE_BELOW_ZERO                   , 626 },
        { CND::IFASTDBRKR_ERR_FUND_SCHED_VALN_GROUP_NOT_FOUND           , 627 },
        { CND::IFASTDBRKR_ERR_CANCEL_NOTIONAL_DISTRIB_DSC               , 628 },
        { CND::IFASTDBRKR_ERR_NO_PERM_CANCEL_NOTIONAL_DISTRIB           , 629 },
        { CND::IFASTDBRKR_ERR_NO_FUND_VALUATION_RECORD                  , 630 },
        { CND::IFASTDBRKR_ERR_UPDATING_LLPWTHDRWL_TABLE                 , 631 },
        { CND::IFASTDBRKR_ERR_TRANS_DETL_NOT_FOUND                      , 632 },
        { CND::IFASTDBRKR_ERR_NO_LLPWTHDRWL_RECORD_DEACTIV              , 633 },
        { CND::IFASTDBRKR_ERR_UNKNOWN_FUNCTION_UPDATE                   , 634 },
        { CND::IFASTDBRKR_ERR_CREATE_POST_ADJUSTMENT_DIV                , 635 },
        { CND::IFASTDBRKR_ERR_INSUFFICIENT_UNITS_NEG_ADJ                , 636 },
        { CND::IFASTDBRKR_ERR_INVSUMM_ID_TO_NOT_PASSED                  , 637 },
        { CND::IFASTDBRKR_ERR_TRACE_NO_TO_NOT_PASSED                    , 638 },
        { CND::IFASTDBRKR_ERR_NO_INVSUMM_ID_RECORD                      , 639 },
        { CND::IFASTDBRKR_ERR_TAX_JURIS_SHRHOLDER_BLANK                 , 640 },
        { CND::IFASTDBRKR_ERR_INVENTORY_BALANCE_NEGATIVE                , 641 },
        { CND::IFASTDBRKR_ERR_INSUFFICIENT_UNITS_NEG_ADJ                , 642 },
        { CND::IFASTDBRKR_ERR_CREATE_POST_ADJUSTMENT_DIV                , 643 },
        { CND::IFASTDBRKR_ERR_GIC_DOES_NOT_EXIST                        , 644 },
        { CND::IFASTDBRKR_ERR_GIC_MATURED                               , 645 },
        { CND::IFASTDBRKR_ERR_GIC_PURCHASE_REDUCED                      , 646 },
        { CND::IFASTDBRKR_ERR_INVENTORY_DOES_NOT_EXIST                  , 647 },
        { CND::IFASTDBRKR_ERR_TXN_REDUCED_ALREADY                       , 648 },
        { CND::ERR_CD_POLICY_IMPACT_DOB                                 , 649 },
        { CND::ERR_DOB_IMPACT_MATUR_POLICY                              , 650 },
        { CND::ERR_NEW_DATE_BIRTH_CANNOTBE_BLANK                        , 651 },
        { CND::ERR_NEW_LEGAL_CONTRACT_MAT_DATE                          , 652 },
        { CND::ERR_TXN_CANNOT_EXIST_AFTER_DECADE                        , 653 },
        { CND::ERR_AGGREGATE_ORDER_LOSS                                 , 654 },
        { CND::ERR_AMT_EXCEED_VARIANCE_AGGRORD                          , 655 },
        { CND::ERR_REPRINT_RECORD_ALREADY_EXISTS                        , 656 },
        { CND::ERR_REPRINT_RECORD_DOES_NOT_EXIST                        , 657 },
        { CND::ERR_No_Valid_Acct_Level_CONTRACT                         , 658 },
        { CND::ERR_GUARANTEE_ADJUSTMENT_MADE                            , 659 },
        { CND::ERR_PENDING_TRADE_CANNOT_EXIST                           , 660 },
        { CND::ERR_NEGATIVE_GUARANTEE_CANNOT_EXIT                       , 661 },
        { CND::ERR_TXN_EXIST_AFTER_CLOSING_DECADE                       , 662 },
        { CND::ERR_GUARANTEE_ADJUST_NEED_CANCELLATION                   , 663 },
        { CND::ERR_REVERSAL_CODE_TOP_UP_INCORRECT                       , 664 },
        { CND::ERR_GEN_CTRL_TRADE_DEFLT_DOES_NOT_EXIST                  , 665 },
        { CND::ERR_ACCT_LVL_CUT_OFF_TIME_NOT_EXIT                       , 666 },
        { CND::ERR_ACCT_LVL_CUT_OFF_TIME_ALREADY_EXIT                   , 667 },
        { CND::ERR_RECREATING_POLICY_PERIOD                             , 668 },
        { CND::ERR_NO_VALID_CONTRACT_ORIG_TRADEDATE                     , 669 },
        { CND::ERR_RESET_OCCURED_SINCE_ORIG_TRADEDATE                   , 670 },
        { CND::ERR_NEGATIVE_GUARANTEE_ORIG_TRADEDATE                    , 671 },
        { CND::ERR_DM_EVENT_SINCE_ORGI_TRADEDATE                        , 672 },
        { CND::ERR_TRADE_PARTOF_DM_EVENT                                , 673 },
        { CND::ERR_CANCEL_GUAR_ADJ_EXIST_FOR_ACCT_CONTRACT_AFTR_TRADE_DATE, 674 },
        { CND::ERR_GRNTE_MATURED_PER_CNTRCT_TERM                        , 675 },
        { CND::ERR_SEG_CALC_REQUEST_DURING_CANCEL                       , 676 },
        { CND::ERR_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT                       , 677 },
        { CND::ERR_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT          , 678 },
        { CND::ERR_TRANSFER_ACCOUNT_PURGED                              , 679 },
        { CND::ERR_TRANSACTION_MORE_THAN_ONE_SHAREHOLDER                , 680 },
        { CND::ERR_PENDING_EXIST_WITH_TRANSNUM                          , 681 },
        { CND::ERR_UNSETTLE_CANNOT_CANCEL_FOR_DIVIDEND_FUND             , 682 },
        { CND::ERR_MIRROR_CHILD_AMS_REBALANCE                           , 683 },
        { CND::ERR_CANCEL_MONEY_OUT_TXNS                                , 685 },
        { CND::ERR_SEG_GUAR_MAT_RECORD_NOT_FOUND                        , 686 },
        { CND::ERR_SEG_GUAR_DETL_RECORD_NOT_FOUND                       , 687 },
        { CND::ERR_NOT_ENOUGH_SETTLED_UNITS_TO_SETTLE_REDEMPTION        , 688 },
        //	{ CND::ERR_CONTRACT_CLOSED_FOR_NEW_BUSINESS                 , 689 },
        { CND::ERR_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE             , 689 },
        { CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE                , 690 },
        { CND::ERR_INVALID_TRANSACTION_STATUS                           , 691 },
        { CND::ERR_TRADEDATE_FUNDCLASS_BLANK                            , 692 },
        { CND::ERR_BULK_CANC_NO_TXN_TO_CANCEL                           , 693 },
        { CND::ERR_BULK_CANC_NO_TXN_TO_REBOOK                           , 694 },
        { CND::ERR_CANC_NOT_ALLOWED_ACTIVE_CYCLE                        , 695 },
        { CND::ERR_INVALID_TRANS_STATUS                                 , 698 },
        { CND::ERR_INVALID_ADJUST_TYPE                                  , 699 },
        { CND::ERR_EUSD_OVERRIDE_DOES_NOT_EXIST                         , 701 },
        { CND::ERR_PWD_NOT_CONTAIN_USER                                 , 703 },
        { CND::ERR_INVALID_PARAMETER_NEED_BROKERCODE                    , 704 },
        { CND::ERR_INSUFFICIENT_NOTIONAL_BALANCE                        , 705 },
        { CND::ERR_PA_NOT_FOUND                                         , 706 },
        { CND::ERR_NO_ENTITY_TAX_HIST_FOUND_FOR_PA                      , 707 },
        { CND::ERR_TAX_JURIS_NOT_FOUND_FOR_OWNER                        , 708 },
        { CND::ERR_NO_ACTIVE_OWNER_FOUND                                , 709 },
        { CND::ERR_MISSING_CUSTOM_TRADING_SCHD                          , 710 },
        { CND::ERR_INVALID_CUSTOM_TRADING_SCHD                          , 711 },
        { CND::ERR_NO_BUSSINESS_DAY_RECORD_AVAIL                        , 712 },
        { CND::ERR_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE              , 713 },
        { CND::ERR_CONTRACT_TYPE_MUST_BE_ENTERED                        , 714 },
        { CND::ERR_TAXTYPE_MUST_BE_ENTERED                              , 715 },
        { CND::ERR_PROVINCE_MUST_BE_ENTERED                             , 716 },
        { CND::ERR_EFFECTIVEDATE_MUST_BE_ENTERED                        , 717 },
        { CND::ERR_CANNOT_FIND_TIME_ZONE_INFORMATION                    , 718 },
        { CND::ERR_SEG_MANUAL_EVENTS_SINCE_ORIGINAL_TRADE_DATE          , 719 },
        //{ CND::720
        { CND::ERR_PAY_ENTITY_EXISTS_FOR_DATE_RANGE                     , 721 },
        { CND::ERR_PAY_INSTRUCT_EXISTS_FOR_DATE_RANGE                   , 722 },
        { CND::ERR_TRADE_PAY_INSTRUCT_RECORD_LOCKED                     , 723 },
        { CND::ERR_TRADE_PAY_INSTRUCT_RECORD_DOES_NOT_EXIST             , 724 },
        { CND::ERR_TRADE_PAY_INSTRUCT_RECORD_ALREADY_EXISTS             , 725 },
        { CND::ERR_PAYENTITY_DOES_NOT_EXIST_FOR_DATE_RANGE              , 726 },
        { CND::ERR_NOMINEE_ENTITY_NOT_FOUND                             , 727 },
        { CND::ERR_INTERMEDIARY_ENTITY_NOT_FOUND                        , 728 },
        { CND::ERR_TRXR_CANCEL_FAILED                                   , 758 },
        { CND::ERR_SWITCH_SETTLE_FAILED                                 , 759 },
        { CND::ERR_NO_DATA_AVAILABLE                                    , 760 },
        { CND::ERR_EXCH_RATE_DOES_NOT_EXIST                             , 762 },
        { CND::ERR_INVENTORY_TRACKING_ERROR                             , 763 },
        { CND::ERR_ACCOUNT_AMS_RECORD_DOES_NOT_EXIST                    , 764 },
        { CND::ERR_ACCOUNT_AMS_RECORD_ALREADY_EXISTS                    , 765 },
        { CND::ERR_KYC_RECORD_NOT_FOUND                                 , 768 },
        { CND::ERR_MANAGEMENT_FEE_MODEL_MISSING                         , 769 },
        { CND::ERR_INVALID_ACCESS_ID                                    , 770 },
        { CND::ERR_ACCESS_ID_OVERRIDE_NOT_ALLOWED                       , 771 },
        { CND::ERR_INVALID_BILL_TO_ENTITY_TYPE                          , 772 },
        { CND::ERR_INVALID_BILL_TO_ENTITY                               , 773 },
        { CND::ERR_INVALID_ASSOCIATED_ACCNUM                            , 774 },
        { CND::ERR_AMS_ACTIVE_CERTS_EXIST                               , 776 },
        { CND::IFASTDBRKR_ERR_ACCT_CONTROL_NOT_EXISTS                   , 778 },
        { CND::IFASTDBRKR_ERR_ACCT_CONTROL_EXISTS                       , 779 },
        { CND::IFASTDBRKR_ERR_ACCT_CONTROL_UNABLE_TO_MODIFY             , 780 },
        { CND::ERR_CANCELLATION_FAILED_TO_CANCEL_ASSOC_UNSTTL_CASH_ID   , 783 },
        { CND::ERR_CANCELLATION_UNDONE_BY_ERROR_OR_ENDKEY               , 784 },
        { CND::ERR_CANCELLATION_DEPOSIT_DTE_BLNK_FOR_LSIF_FND           , 785 },
        { CND::ERR_CANCELLATION_LOCK_ACCT_VAL_TO_RESET_ACB_SUPPRESS_FLAG_FAILED        , 786 },
        { CND::ERR_CANCELLATION_CALC_EUSD_FAILED_FUND_INFO_NOT_FOUND    , 787 },
        { CND::ERR_CANCELLATION_CALC_EUSD_FAILED_PRICE_DISTRIB_RATE_NOT_FOUND          , 788 },
        { CND::ERR_CANCELLATION_CALC_EUSD_FAILED_PAYING_AGENT_NOT_FOUND , 789 },
        { CND::ERR_CANCELLATION_CALC_EUSD_FAILED_ENTITY_IDENTITY_PAYING_AGENT_NOT_FOUND, 790 },
        { CND::ERR_CANCELLATION_CALC_EUSD_FAILED_TAX_HIST_PAYING_AGENT_NOT_FOUND       , 791 },
        { CND::ERR_CANCELLATION_CALC_EUSD_FAILED_TAX_HIST_OWNER_NOT_FOUND              , 792 },
        { CND::ERR_CANCELLATION_CALC_EUSD_FAILED_ACCTIVE_OWNER_NOT_FOUND, 793 },
        { CND::ERR_CANCELLATION_CALC_EUSD_FAILED_CURRENCY_NOT_FOUND     , 794 },

        { CND::WARN_STOP_REASON_MISSING_SYSTEM                          , 795 },
        { CND::WARN_STOP_REASON_DECEASED_SYSTEM                         , 796 },
        { CND::WARN_STOP_REASON_STOPFLAGS_DECESED_REMOVED               , 797 },
        { CND::WARN_STOP_REASON_STOPFLAGS_KYC_REMOVED                   , 799 },
        { CND::ERR_CHQ_DETL_NOT_FOUND                                   , 800 },
        { CND::ERR_SALES_REP_ALREADY_EXISTS                             , 801 },
        { CND::ERR_NOT_WIRE_ORDER_TRADE                                 , 802 },
        { CND::ERR_MULTIPLE_ALLOC_SAME_EFF_DATE_NOT_ALLOWED             , 803 },
        { CND::ERR_CONFLICT_ADDRESS_EXIST                               , 804 },
        { CND::ERR_BATCHTRACE_REC_NOTFOUND                              , 805 },
        { CND::ERR_ACCT_LEVEL_IA_RECORD_NOT_EXISTS                      , 806 },
        { CND::ERR_ACCT_LEVEL_IA_RECORD_EXISTS                          , 807 },
        { CND::ERR_USER_BATCH_ISNOT_ACTIVE                              , 808 },
        { CND::ERR_ACCT_LEVEL_IA_RECORD_VERSION_DIFF                    , 809 },
        { CND::ERR_ACCT_LEVEL_IA_RECORD_INVALID_PAYMENT_TYPE            , 810 },
        { CND::ERR_USER_DO_NOT_HAVE_ACCESS_TO_DESKTOP                   , 811 },
        { CND::ERR_VERIFY_REQUEST_RUN_MODE_NOT_VALID                    , 812 },
        { CND::ERR_VERIFY_REQUEST_VERIFY_CATEGORY_NOT_VALID             , 813 },
        { CND::ERR_VERIFY_REQUEST_VERIFY_LEVEL_NOT_VALID                , 814 },
        { CND::ERR_VERIFY_REQUEST_VERIFY_BLANK_LINKID                   , 815 },
        { CND::ERR_VERIFY_REQUEST_VERIFY_BLANK_UUID                     , 816 },
        { CND::ERR_VERIFY_REQUEST_RECORD_LOCKED                         , 817 },
        { CND::ERR_VERIFY_REQUEST_RECORD_NOT_EXIST                      , 818 },
        { CND::ERR_SETTLE_BANK_NOT_VERFIED                              , 819 },
        { CND::ERR_TRADE_BANK_NOT_VERIFIED                              , 820 },
        { CND::ERR_SHRHLDR_ADDR_NOT_VERIFIED_FOR_SETTLEMENT             , 821 },
        { CND::ERR_RESP_BENEF_RECORD_LOCKED                             , 823 },
        { CND::ERR_RESP_BENEF_RECORD_VERSION_NOT_MATCH                  , 824 },
        { CND::ERR_RESP_BENEF_RECORD_NOT_FOUND                          , 825 },
        { CND::ERR_INVALID_CALL_TYPE                                    , 826 },
        { CND::ERR_RESP_RECORD_LOCKED                                   , 827 },
        { CND::ERR_RESP_RECORD_UNAVAILABLE                              , 828 },
        { CND::ERR_INVALID_TRADE_TYPE                                   , 829 },
        { CND::ERR_INVALID_CALLTYPE_TRADETYPE                           , 830 },
        { CND::ERR_SETTLEMENT_NOT_ALLOWED_DURING_CYCLE                  , 831 },
        { CND::ERR_CLINET_RECORD_ALREADY_EXISTS                         , 833 },
        { CND::ERR_TRANSFER_DETAIL_RECORD_LOCKED                        , 834 },
        { CND::ERR_TRANSFER_DETAIL_RECORD_NOT_AVAILABLE                 , 835 },
        { CND::ERR_RESP_TRINFO_NOT_AVAILABLE                            , 836 },
        { CND::ERR_DBKR_BATCH_BELONGS_TO_OTHERUSER                      , 837 },
        { CND::ERR_WARNCODE_TABLE_NOT_AVAIL                             , 838 },
        { CND::ERR_NO_TRANSACTION_NUMBER                                , 839 },
        { CND::ERR_ACCT_FOR_TRANSACTION_NOT_AVAILABLE                   , 840 },
        { CND::ERR_RESP_ACCT_INFO_NOT_AVAILABLE                         , 841 },
        { CND::ERR_NOT_FOUND_RESP_EARNING_GRANT_REDCODES_CONTROLS_RECORD   , 842 },
        { CND::ERR_BRK_EPA_STATUS_NOT_ACTIVE                            , 846 },
        { CND::ERR_511_RECORDS_NOT_ALLOWED                              , 848 },
        { CND::ERR_SHAREHOLDER_FAMILY_RECORD_NOT_EXISTS                 , 867 },
        { CND::ERR_FAMILY_RECORD_NOT_EXISTS                             , 868 },
        { CND::ERR_INTINVEST_LOCKED                                     , 869 },
        { CND::ERR_INTINVEST_NOT_AVAIL                                  , 870 },
        { CND::ERR_BANKACCT_LOCKED                                      , 871 },
        { CND::ERR_INTINVEST_VERSION_DIFFERENT                          , 872 },
        { CND::ERR_BANKACCT_VERSION_DIFFERENT                           , 873 },
        { CND::ERR_INSTRUCTION_ALREADY_EXISTS                           , 875 },
        { CND::ERR_SUBSEQUENT_EVENTS_TAKEN_PLACE_AT_CANCELLATION        , 879 },
        { CND::ERR_EQ_TRADE_CANCEL                                      , 880 },
        { CND::ERR_NO_ADDITIONAL_TRADE_DATE_EXIST                       , 881 },
        { CND::ERR_INCREASE_NOT_ALLOWED_MISSED_PACS                     , 884 },
        { CND::ERR_EMPTY_REG_AGENT_CODE                                 , 882 },
        { CND::ERR_INVALID_REG_AGENT_CODE                               , 883 },
        { CND::ERR_COMMISION_EXCEED_FUND_DEFAULT_RATE                   , 903 },
        { CND::ERR_AMOUNT_DONOT_CROSSFOOT                               , 904 },
        { CND::ERR_NEGATIVE_GUARANTEES_FOLLOWING_MUST_BE_CANCELLED      , 905 },
        { CND::ERR_HOLDING_ENTITY_CODE_ALREADY_EXISTS                   , 908 },
        { CND::ERR_HOLDING_ENTITY_RECORD_DOES_NOT_EXIST                 , 909 },
        { CND::ERR_HOLDING_ENTITY_CODE_BAD_RECORD_EXISTS                , 910 },
        { CND::ERR_FEE_MODEL_RECORD_WITH_SAME_FEE_MODEL_CODE_IS_ALREADY_DELETED , 911 },
        { CND::ERR_HOLDING_COMPANY_CODE_IS_ALREADY_DELETED              , 912 },
        { CND::ERR_CODE_USED_BY_FUNDSPONSOR_CANNOT_DELETE               , 913 },
        { CND::ERR_DUPLICATE_PARENT_FUND_CLASS                          , 915 },
        { CND::ERR_ACCTREGDETAILS_NOT_AVAILABLE                         , 916 },
        { CND::ERR_UNABLE_TO_MODIFY_ACCTREGDETAILS                      , 917 },
        { CND::ERR_ACCT_REG_DETAILS_DOES_NOT_EXIST                      , 918 },
        { CND::ERR_TRANSACTION_CANNOT_BE_CANCELLED_BEFORE_NIGHT_RUN     , 919 },
        { CND::ERR_FULL_PARTIAL_EXEMPTION_SCOPE_EXIST_ACCT_FUND_CLASS   , 922 },
        { CND::ERR_ENT_REG_LOCKED                                       , 923 },
        { CND::ERR_ENT_REG_NOT_AVAIL                                    , 924 },
        { CND::ERR_ENT_REG_VER_DIFF                                     , 925 },
        { CND::ERR_ENT_REG_DUP_ID_REG                                   , 926 },
        { CND::ERR_ENT_REG_JUR_LOCKED                                   , 927 },
        { CND::ERR_ENT_REG_JUR_NOT_AVAIL                                , 928 },
        { CND::ERR_ENT_REG_JUR_VER_DIFF                                 , 929 },
        { CND::ERR_ENT_REG_JUR_DUP_TAX                                  , 930 },
        { CND::ERR_DILUTION_RECORD_IS_NOT_AVAIL                         , 931 },
        { CND::ERR_ENTER_A_VALID_SUPPRESS_CODE_FOR_PAYTYPE_X_OR_BLANK_FOR_S , 932 },
        { CND::ERR_TRADE_DATE_IS_IN_FUTURE_FOR_THE_SELECTED_VALUATION_DATE  , 933 },
        { CND::ERR_TRADE_DATE_DELAY_EXIST_FOR_FUNDCLASS_UNABLE_TO           , 934 },
        { CND::ERR_CANNOT_CALCULATE_EUSD                                , 935 },
        { CND::ERR_PF_CRYSTALISATION_IS_NOT_YET_COMPLETED_FOR_FUNDCLASS , 936 },
        { CND::ERR_SHARELOT_UNITS_DO_NOT_MATCH_TRANSACTION_UNITS        , 937 },
        { CND::ERR_NO_SHAARELOT_RECORD_AVAILABLE                        , 938 },
        { CND::ERR_MISMATCHED_UNITS_AVAIL                               , 939 },
        { CND::ERR_PLEASE_CANCLE_MONEY_OUT_TEANS_FOR_BACKDATED_PRIOR    , 940 },
        { CND::ERR_TRADE_DOES_NOT_BELONG_TO_EXISTING_FUND               , 941 },
        { CND::ERR_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT , 942 },
        { CND::ERR_TRADE_ALREADY_VERIFIED                               , 943 },
        { CND::ERR_CONTRACT_TYPE_IS_NOT_FOUND_FOR_THIS_ACCOUNT          , 946 },
        { CND::ERR_CANCEL_ALL_TRANS_OR_CHANGE_TRADEDATE                 , 947 },
        { CND::ERR_INVALID_VALUATION_DATE_FOR_FUND_CLASS                , 949 },
        { CND::ERR_ACCOUNT_ALREADY_IN_MAIL_HOUSEHOLD                    , 950 },
        { CND::ERR_ACCOUNT_NOT_ASSOCIATED                               , 951 },
        { CND::ERR_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE, 952 },
        { CND::ERR_COPY_FAIL_EXPIRED_FEE_MODEL                          , 953 },
        { CND::ERR_FUND_CLASS_IS_NOT_LINKED_TO_CURRENT_ACTIVE_AMS_MODEL   , 970 },
		{ CND::ERR_PAYENTITY_ALREADY_STOPDATED							 , 971 }, //added for INC0031322
		{ CND::ERR_ERJD_EXISTS											 , 985 }, 
		{ CND::ERR_ALLOCATION_NOT_SUPPORT								 , 986 },
		{ CND::ERR_LINK_TYPE_IS_NOT_FOUND								 , 987 },
		{ CND::ERR_DBRKR_DILUTION_LINK_ID_DOES_NOT_EXIST				 , 988 },
		{ CND::ERR_DBRKR_FUND_SUSPENDED_NO_TRANSACTIONS_ALLOWED			 , 990 },
		{ CND::ERR_DBRKR_REDEMPTIONS_SUSPENDED_LIQUIDITY_MEASURE		 , 991 },
		{ CND::ERR_DBRKR_RDSP_CANNOT_CANCEL_MONEY_IN_BEFORE_MONEY_OUT	 , 992 },
		{ CND::ERR_DBRKR_RDSP_CANNOT_CANCEL_RECONCILED_EXTERNAL_TRANSFER_IN	 , 993 },
		{ CND::ERR_DBRKR_RDSP_CANNOT_CANCEL_REPORTED_EXTERNAL_TRANSFER_IN , 994 },
        { -1L, -1L }
        };

     const long rtsConditionArray[][2] = {
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 1 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 2 },
        { CND::ERR_RTS_OUT_OF_MEMERY                                    , 3 },
        { CND::ERR_RTS_OUT_OF_DISK_SPACE                                , 4 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 5 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 6 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 7 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 8 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 9 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 10 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 11 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 12 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 13 },
        { CND::ERR_RTS_SYSTEM_ISSUE                                     , 14 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 15 },
        { CND::ERR_RTS_IFAST_NOT_RESPONDING                             , 16 },
        { CND::ERR_RTS_DATABASE_CONNECTION                              , 17 },
        { CND::ERR_RTS_IFAST_NOT_RESPONDING                             , 18 },
        { CND::ERR_RTS_SYSTEM_ISSUE                                     , 19 },
        { CND::ERR_RTS_SYSTEM_ISSUE                                     , 20 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 21 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 22 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 23 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 24 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 25 },
        { CND::ERR_RTS_CONFIG_ISSUE                                     , 26 },
        { -1L, -1L}
   };
   const long smqConditionArray[][2] = {
     { CND::ERR_SMQ_FRAMEWORK_ERROR                                  , 1 },   // ESB Exception
     { CND::ERR_SMQ_FRAMEWORK_ERROR                                  , 2 },   // AppServer/4GL Error
     { CND::ERR_SMQ_FRAMEWORK_ERROR                                  , 3 },   // invalid error message
     { CND::ERR_SMQ_FRAMEWORK_ERROR                                  , 4 },   // unsupported message type
     { CND::ERR_SMQ_AUTHORIZATION_ERROR                              , 5 },   // Error from Authorization Service
     { CND::ERR_SMQ_SESSION_EXPIRED                                  , 6 },   // Sonic Session has expired.
     { CND::ERR_SMQ_AUTHORIZATION_DENIED                             , 7 },   // Authorization is denied.
     { CND::ERR_SMQ_NO_APPSERVER                                     , 8 },   // Can't connect to AppServer (probably not running)
     { CND::ERR_SMQ_BROKEN_APPSERVER_CONNECTION                      , 9 },   // Temporary read problem from AppServer (READPACKET error)
     { CND::ERR_SMQ_APPSERVER_ERROR                                  , 10 },  // 4GL Error
     { CND::ERR_SMQ_SONICMQ_ERROR                                    , 11 },  // JMS Exception
     { -1L, -1L}
   };
}



//******************************************************************************
const DSTCRequestor::HostConditionMap DSTCRequestor::_hostConditions ( hostConditionArray );
const DSTCRequestor::HostConditionMap DSTCRequestor::_rtsConditions ( rtsConditionArray );
const DSTCRequestor::HostConditionMap DSTCRequestor::_smqConditions ( smqConditionArray );

//******************************************************************************
DSTCRequestor::DSTCRequestor(const DSTCSecurity *security, 
                             bool allResults /*= true*/, 
                             bool noDataIsErrorCondition /*= false*/,
                             bool bRecycleOnReceive /*= true*/)
: _security(security)
, _connection(NULL)
, bRecycleOnReceive_( bRecycleOnReceive )
, _allResults(allResults)
, _hostConditionFilter()
, _requestTime( -1 )
{
   if( !noDataIsErrorCondition )
      _hostConditionFilter.insert(CND::ERR_DATA_NOT_FOUND);

}

//******************************************************************************
DSTCRequestor::DSTCRequestor(const DSTCRequestor &copy)
: _security(copy._security)
, _connection(NULL)
, bRecycleOnReceive_( copy.bRecycleOnReceive_ )
, _allResults(copy._allResults)
, _requestTime(copy._requestTime)
{

}

//******************************************************************************
DSTCRequestor::~DSTCRequestor()
{
   if( _connection )
      BFConnectionManager::getInstance()->freeConnection(_connection);
}

//******************************************************************************
BFRequestor *
DSTCRequestor::clone() const
{   
   return(new DSTCRequestor(*this)); 
}

//******************************************************************************
unsigned long DSTCRequestor::getRequestTime() const
{
   return( _requestTime );
}

//******************************************************************************
void DSTCRequestor::setRequestTime( unsigned long requestTime )
{
   _requestTime = requestTime;
}

//******************************************************************************
unsigned long DSTCRequestor::getConnectionTime() const
{
   return( _connectionTime );
}

//******************************************************************************
void DSTCRequestor::setConnectionTime( unsigned long connectionTime )
{
   _connectionTime = connectionTime;
}

//******************************************************************************
BFWriteBuffer *
DSTCRequestor::createRequestBuffer(const BFRequest &request) const
{
   return(new DSTCRequestBuffer(request));
}

//******************************************************************************
SEVERITY 
DSTCRequestor::receive( const BFRequest &request, 
                        BFData &queryData, 
                        BFData &receivedData, 
                        bool *outMoreAvailable)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, RECEIVE );

   // add security parameters to the request
   if( _security == NULL )
   {
      assert(0);
      throw;
   }

   if( (&request) != (&DSTC_REQUEST::LOGON) )
   {
      if( !_security->isLoggedOn() )
      {
         assert(0);
         THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, RECEIVE, CND::IFASTDBRKR_NOT_LOGGED_ON);
      }
      queryData.setElementValue( ifds::SessionId,    _security->getSessionId(), false, false );
      queryData.setElementValue( ifds::User_Id,      _security->getUserId(),    false, false );
      queryData.setElementValue( ifds::LanguageCode, _security->getLanguage(),  false, false );

   }

   bool moreAvailable = true;
   int numRecords = 0;
   // loop to get all results if required
   do
   {
      // reset the request time so that view time logging will not accumulate the time for the previous view
      setRequestTime( -1 );
      SEVERITY severity = BFAbstractRequestor::receive( request, queryData, receivedData );

      //in case of an error return immediately
      if( WARNING < severity )
         return(GETCURRENTHIGHESTSEVERITY());

      // get next key
      DString nextKey;
      if( receivedData.exists( ifds::NextKey ) )
         nextKey = receivedData.getElementValue( ifds::NextKey );

      // get repeat count for this iteration
      if( receivedData.exists( ifds::RepeatCount ) )
      {
         DString numRecordsString = receivedData.getElementValue( ifds::RepeatCount );
         numRecords += numRecordsString.asInteger();
      }
      else
         numRecords = 1;

      if( receivedData.exists( ifds::MoreAvailable ) )
      {
         DString moreAvailableString = receivedData.getElementValue( ifds::MoreAvailable );
         moreAvailable = ( I_("Y") == moreAvailableString );
      }
      else
         moreAvailable = false;

      // set the NextKey in the queryData
      queryData.setElementValue( ifds::NextKey, nextKey, false, false );
   }
   while( _allResults && moreAvailable );

   if( receivedData.exists( ifds::RepeatCount ) )
   {
      receivedData.setElementValue( ifds::RepeatCount, DString::asString( numRecords ), false, false );
   }

   // set if required
   if( NULL != outMoreAvailable )
      *outMoreAvailable = moreAvailable;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY 
DSTCRequestor::receiveBuffer( const BFRequest &request, 
                              const BFWriteBuffer *queryBuffer, 
                              BFReadBuffer **receivedBuffer,
                              const BFData* pQuery )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, RECEIVE_BUFFER );

   // cast parameters to reviel DSTC properties.
   const DSTCRequestBuffer *dstcRequestBuffer = dynamic_cast<const DSTCRequestBuffer *>(queryBuffer);
   const DSTCRequest &dstcRequest = dynamic_cast<const DSTCRequest &>(request);

   if( !_connection )
   {
      _connection = dynamic_cast< BFRecordConnection* >( BFConnectionManager::getInstance()->getConnection(_security->getHost()->getId() ) );
   }

   int retryCount = 0;
   bool retry = false;
   do { // retry loop
      
      retry = false;
      BFHRTimer t;
      // the real view name is the TransType and the TransID
      //    - cp21sep2004
      _connection->putRequest(dstcRequest.getTransType() + dstcRequest.getTransId(), 
                              dstcRequestBuffer->getString(), 
                              bRecycleOnReceive_, 
                              pQuery, 
                              const_cast<DSTCSecurity*>(_security) );
      DSTCResponseBuffer *dstcResponseBuffer = new DSTCResponseBuffer( dstcRequest, _connection->getResponse() );
      _requestTime = t.elapsed() + ( ( _requestTime == -1 ) ? 0 : _requestTime );

      DString dstrFileName;      
      dstrFileName = I_("DSTC") + DString (dstcRequest.getTransId()).right(4);
      logData ( I_("\n******************** TIME ELAPSED ") + dstrFileName + I_(".VW ********************\n"));
      logData ( I_("TimeElapsed"), DString::asString (_requestTime) + I_( " milliseconds" ));


      if( DSTCResponseBuffer::ERROR_RESPONSE == dstcResponseBuffer->getResponseType() )
      {
         logData ( I_("\n******************** ERROR RESPONSE ") + dstrFileName + I_(".VW ********************\n"));
         logData ( I_("ErrorCode"), dstcResponseBuffer->getHostErrorCodeString() );
         logData ( I_("ErrorMessage"), dstcResponseBuffer->getHostErrorMessage() );
         logData ( queryBuffer, *receivedBuffer, dstrFileName + I_(".REQ") );

         long condition = _hostConditions.getCondition( dstcResponseBuffer->getHostErrorCode() );

         // do not add conditions in the filter set
         if( !_hostConditionFilter.contains(condition) )
         {
            ADDCONDITIONFROMFILE ( condition );
         }
         delete dstcResponseBuffer;

      }
      else if( DSTCResponseBuffer::UNKNOWN_ERROR_RESPONSE == dstcResponseBuffer->getResponseType() )
      {

         logData ( I_("\n******************** ERROR RESPONSE ") + dstrFileName + I_(".VW ********************\n"));
         logData ( I_("ErrorCode"), dstcResponseBuffer->getHostErrorCodeString() );
         logData ( I_("ErrorMessage"), dstcResponseBuffer->getHostErrorMessage() );
         logData ( queryBuffer, *receivedBuffer, dstrFileName + I_(".REQ") );
         DString error;
         addIDITagValue( error, IDI_ERROR_CODE, dstcResponseBuffer->getHostErrorCodeString() );
         addIDITagValue( error, IDI_ERROR_MSG, dstcResponseBuffer->getHostErrorMessage() );

         int errCode = dstcResponseBuffer->getHostErrorCode();
         if( errCode < 1 || errCode > 26 )
         {
            ADDCONDITIONFROMFILEIDI( CND::IFASTDBRKR_TRANS_FAILED, error.c_str() );
            delete dstcResponseBuffer;
         }
         else if (  
            (  errCode == 17 || errCode == 16 || (errCode == 18 && dstcRequest.isQueryRequest()) ) 
               &&  bfutil::isRetry()  
               && ++retryCount < 1 ) //RTS FIX APPLIED
         {
            retry = true;
         }
         else 
         {
            long condition = _rtsConditions.getCondition( dstcResponseBuffer->getHostErrorCode() );

            if( !_hostConditionFilter.contains(condition) )
            {
               ADDCONDITIONFROMFILE ( condition );
            }
            delete dstcResponseBuffer;
         }
      }
      else if( DSTCResponseBuffer::SMQ_FRAMEWORK_ERROR_RESPONSE == dstcResponseBuffer->getResponseType() )
      {

         logData ( I_("\n******************** ERROR RESPONSE ") + dstrFileName + I_(".VW ********************\n"));
         logData ( I_("ErrorCode"), dstcResponseBuffer->getHostErrorCodeString() );
         logData ( I_("ErrorMessage"), dstcResponseBuffer->getHostErrorMessage() );
         logData ( queryBuffer, *receivedBuffer, dstrFileName + I_(".REQ") );
         DString error;
         addIDITagValue( error, IDI_ERROR_CODE, dstcResponseBuffer->getHostErrorCodeString() );
         addIDITagValue( error, IDI_ERROR_MSG, dstcResponseBuffer->getHostErrorMessage() );
         addIDITagValue( error, IDI_ERROR_TRACKID, dstcResponseBuffer->getHostErrorTrackId() );

         int errCode = dstcResponseBuffer->getHostErrorCode();
         if( errCode < 1 || errCode > 11 )
         {
            ADDCONDITIONFROMFILEIDI( CND::IFASTDBRKR_TRANS_FAILED, error.c_str() );
            delete dstcResponseBuffer;
         }
         else 
         {
            long condition = _smqConditions.getCondition( dstcResponseBuffer->getHostErrorCode() );

            if( !_hostConditionFilter.contains(condition) )
            {
               ADDCONDITIONFROMFILEIDI( condition, error.c_str() );
            }
            delete dstcResponseBuffer;
         }
      }
      else
      {
         *receivedBuffer = dstcResponseBuffer;
      }

   } while( retry );

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
void 
DSTCRequestor::filterHostCondition(long condition)
{
   _hostConditionFilter.insert(condition);
}

//******************************************************************************
void 
DSTCRequestor::clearHostConditionFilter()
{
   _hostConditionFilter.clear();
}

//******************************************************************************
DSTCRequestor::HostConditionMap::HostConditionMap(const long hostConditionArray[][2])
{
   for( int index=0; hostConditionArray[index][0] != -1; index++ )
   {
      addCondition(hostConditionArray[index][1], hostConditionArray[index][0]);
   }
}


//******************************************************************************
long 
DSTCRequestor::HostConditionMap::getCondition(long hostErrorCode) const
{
   const_iterator iter = find(hostErrorCode);

   if( end() == iter )
   {
      assert(0);
      return(CND::ERR_UNKNOWN_ERROR);
   }

   return(*iter).second;
}

//******************************************************************************
void 
DSTCRequestor::HostConditionMap::addCondition(long hostErrorCode, long condition)
{
   const value_type value(hostErrorCode, condition);
   std::pair<iterator, bool> result = insert(value);

   assert ( result.second );

}

//******************************************************************************
bool 
DSTCRequestor::HostConditionFilter::contains(long condition)
{
   return( end() != find(condition) );
}

//******************************************************************************
void 
DSTCRequestor::logCallingTime()
{
   bool bIsRecordTime = GetConfigValueAsBool( I_("MFDSTC") , I_("Support"), I_("ViewLog_InsertDateTime") );

   if(bIsRecordTime)
   {
      SYSTEMTIME st;
      GetLocalTime( &st );

      I_CHAR szBuf[ 128 ];
      i_sprintf( szBuf, I_( "%04d-%02d-%02d %02d:%02d:%02d.%03d" ),
         st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

      DString strTimeInfoline = I_("Time of Connecting to Server: ");
      strTimeInfoline += szBuf;
      logData ( strTimeInfoline );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCRequestor.cpp-arc  $
// 
//    Rev 1.140   Jul 03 2012 17:15:00   wp040039
// PETP0202018 
// SSBG_Aggregated Amount order_SOC#1_Calculation of unit amount.
// 
//    Rev 1.139   Jun 26 2012 14:23:10   wp040240
// IN#2948564 - Error condtions for Contract maturity Instrucitons screen added. 
// 
//    Rev 1.138   May 16 2012 18:11:32   dchatcha
// P0186479 FN10 -Gap 14G - Block Service Unit Transfers, helper key to track view calling time.
// 
//    Rev 1.137   May 11 2012 14:50:24   wp040027
// PETP0187485-CPF-Broker Commission
// 
//    Rev 1.136   Apr 03 2012 21:20:48   wp040039
// PETP0187485-Registartion Agent  Banking
// 
//    Rev 1.135   Mar 05 2012 13:20:42   if991250
// added the handling for the CND::ERR_NO_ADDITIONAL_TRADE_DATE_EXIST, 881 error
// 
//    Rev 1.134   Jan 20 2012 15:35:46   wp040027
// P0188394_Performance Fees - Order Entry
// 
//    Rev 1.133   Jan 10 2012 05:05:34   kitticha
// P0186477 FN03 - Cash Sweep Instruction.
// 
//    Rev 1.132   Jan 10 2012 02:55:30   kitticha
// P0186477 FN03 - Cash Sweep Instruction.
// 
//    Rev 1.131   Dec 15 2011 23:36:40   dchatcha
// P0188902 FN02 - DYN Household Project , new data broker error codes.
// 
//    Rev 1.130   May 20 2011 05:01:04   wutipong
// IN2474907 - RESP 511 error code 5025.
// 
//    Rev 1.129   Dec 01 2010 04:13:34   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.128   Jun 02 2010 06:17:46   wutipong
// IN1976687 Autobatch Error - Add view error code 837
// 
//    Rev 1.127   Jun 01 2010 23:21:22   dchatcha
// IN#2128812 - PETP0165541 FN 01 - Cancellation of processed transaction for RESP Accounts.
// 
//    Rev 1.126   May 14 2010 16:16:58   jankovii
// IN 2117956 - PET165541-Grant can be entered in RESP Transfer Info screen when sibling only=no
// 
//    Rev 1.125   May 04 2010 10:14:34   jankovii
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.124   Apr 27 2010 16:26:50   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.123   Mar 30 2010 16:37:10   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.122   Mar 22 2010 15:05:02   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.121   Mar 12 2010 15:03:02   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.120   Dec 07 2009 23:48:26   dchatcha
// PET0166583 FN02 FN03 FN04 - Static Verification Phase 2. Correct wording of error message for CBO level and add more condition for data broker level.
// 
//    Rev 1.119   Nov 23 2009 16:15:50   jankovii
// PET0166583 FN01 Static Data Changes_Banking information.
// 
//    Rev 1.118   Nov 20 2009 03:10:24   dchatcha
// PET0166583 FN02 FN03 FN04 - Static Verification Phase 2.
// 
//    Rev 1.117   Nov 09 2009 12:22:32   purdyech
// JMSException Support
// Merge R95 changes back in
// 
//    Rev 1.116   Oct 24 2009 06:44:54   purdyech
// Made more specific Sonic Framework Error messages
// 
//    Rev 1.115   Oct 21 2009 10:18:24   purdyech
// LDAP Authorization Support
// 
//    Rev 1.114   Aug 10 2009 04:23:56   dchatcha
// P0163578 FN06 ACL Replacement, New databroker level error code.
// 
//    Rev 1.113   Jul 08 2009 07:35:16   dchatcha
// PET 156681 - FN 14 - Investor Authorization.
// 
//    Rev 1.112   Jun 05 2009 08:19:52   purdyech
// Fixed names of SonicSingle and SonicMulti queues in configuration.
// SonicErrorMessages are now handled appropriately.
// 
//    Rev 1.111   May 27 2009 11:03:00   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.110   May 25 2009 09:31:04   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.109   May 11 2009 05:23:04   dchatcha
// IN 1665615 - Address with same Effective date ans stopdate is not displayed in DESKTOP.
// 
//    Rev 1.108   Apr 03 2009 05:44:40   dchatcha
// IN 1610281 - Multiple GR allocation with the same eff. date were created via desktop.
// 
//    Rev 1.107   Mar 27 2009 10:21:16   purdyech
// Added more JMSProperties to ZTS request messages.
// 
//    Rev 1.106   Mar 03 2009 16:20:56   jankovii
// PET0159508 FN03 ESG In Cash Transfer 
// 
//    Rev 1.105   26 Nov 2008 14:44:34   kovacsro
// IN#1425864 - GL-1323 AS file discrepancy (sales rep uniqueness revisited)
// 
//    Rev 1.104   Sep 09 2008 16:07:54   jankovii
// PET 5517 FN71 Stale Cheque.
// 
//    Rev 1.103   Sep 08 2008 08:28:02   daechach
// in#1396930 - Trade cannot be cancelled, added new error code at data broker level. Rework. some codes missing.
// 
//    Rev 1.102   Aug 28 2008 14:45:36   jankovii
// IN 1388930 - NASU flow does not update document list unless at least one document.
// 
//    Rev 1.101   Jun 20 2008 18:32:44   daechach
// in#1304305 - Trade cannot be cancelled, added new error code at data broker level.
// 
//    Rev 1.100   01 May 2008 13:58:18   kovacsro
// PET2255 FN47 - New Ontario LIF - finalized
// 
//    Rev 1.99   16 Apr 2008 15:08:06   kovacsro
// PET2255-FN47 - Ontario New LIF - added 2 new conditions to prevent money in
//
//    Rev 1.98   Mar 11 2008 19:31:20   daechach
// PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
// 
//    Rev 1.97   Oct 24 2007 19:10:10   smithdav
// IN1024380 - AMSAcctLevel active Certificates edit.
// 
//    Rev 1.96   31 Aug 2007 18:24:58   popescu
// GAP6 - new conditions for validating access id/cif and updated the ACL error messages
// 
//    Rev 1.95   31 Aug 2007 10:02:58   popescu
// PET 2360 FN11 - Dillution.
// 
//    Rev 1.94   Aug 29 2007 17:01:44   jankovii
// PET 2360 FN11 - Dillution.
// 
//    Rev 1.93   Jun 27 2007 13:57:08   porteanm
// PET 2360 FN02 - AMS dbrkr error for view 382.
// 
//    Rev 1.92   May 01 2007 11:48:14   jankovii
// IN #873842 - added reject errors.
// 
//    Rev 1.91   Mar 21 2007 12:56:50   jankovii
// PET2292 FN01 - Switch Settlement.
// 
//    Rev 1.90   Nov 14 2006 15:45:04   popescu
// PET 2281/FN 01 - synch-up cond 727 & 728
// 
//    Rev 1.89   Nov 08 2006 14:34:36   fengyong
// Incident 751006 - matching rts conditions
// 
//    Rev 1.88   Sep 09 2006 15:25:30   popescu
// STP 2129/13
// 
//    Rev 1.87   Jun 29 2006 09:43:56   porteanm
// PET2003 FN03 - Added support for rej-error 491/ACL 719.
// 
//    Rev 1.86   May 25 2006 17:42:20   ZHANGCEL
// PET 2102 FN01 -- Add 4 new error conditons for view367 in ifastdbrkr
// 
//    Rev 1.85   May 19 2006 10:01:44   jankovii
// PET 2102 - Trade/Systematic Entry.
// 
//    Rev 1.84   Apr 07 2006 13:45:48   jankovii
// PET 1334 Alternative Product. Added view error 311.
// 
//    Rev 1.83   Apr 04 2006 16:05:00   jankovii
// PET 1334 Alternative Product. Added 3 new acl messages.
// 
//    Rev 1.82   Mar 22 2006 16:24:40   jankovii
// EUSD Backdated trade validation.
// 
//    Rev 1.81   Mar 08 2006 15:09:34   ZHANGCEL
// Incident 525927 -- Add error code 705
// 
//    Rev 1.80   Dec 05 2005 11:31:06   zhengcon
// Add three error conditions -- ERR_PWD_USER_NOT_BE_SAME
// ERR_PWD_NOT_CONTAIN_USER
// ERR_INVALID_PARAMETER_NEED_BROKERCODE
// 
//    Rev 1.79   Nov 29 2005 15:24:26   AGUILAAM
// PET_1228_FN02: EUSD Phase 2
// 
//    Rev 1.78   Nov 25 2005 12:13:34   porteanm
// PET1285 FN01 - Added 1 more ACL condition, ERR_CANC_NOT_ALLOWED_ACTIVE_CYCLE.
// 
//    Rev 1.77   Nov 24 2005 11:39:06   porteanm
// PET1286 FN01 - Added 2 new ACL conditions, ERR_BULK_CANC_NO_TXN_TO_CANCEL and ERR_BULK_CANC_NO_TXN_TO_REBOOK.
// 
//    Rev 1.76   Nov 11 2005 17:02:58   ZHANGCEL
// PET 1286 FN01 -- Add 4 new ACL Conditons 
// 
//    Rev 1.75   Nov 10 2005 18:08:56   fengyong
// Incident 386579 - add new attribute to API batch level, control retry error 16, 17, 18 or not
// 
//    Rev 1.73   Sep 09 2005 17:46:54   ZHANGCEL
// PET1244 FN01 -- Add new conditions for seg fund evolution enhancement
// 
//    Rev 1.72   Aug 29 2005 16:10:40   porteanm
// Incident 379193 - Added error 688 - ERR_NOT_ENOUGH_SETTLED_UNITS_TO_SETTLE_REDEMPTION.
// 
//    Rev 1.71   Aug 18 2005 16:58:02   AGUILAAM
// PET1235_FN01: error 603 is cancellation error.
// 
//    Rev 1.70   Aug 10 2005 14:26:22   porteanm
// Incident 351033 - Added ERR_SEG_GUAR_MAT_RECORD_NOT_FOUND and ERR_SEG_GUAR_DETL_RECORD_NOT_FOUND.
// 
//    Rev 1.69   Jul 17 2005 17:45:44   porteanm
// PET1171 EUSD 1B - ERR_CANCEL_MONEY_OUT_TXNS is 685 not 684.
// 
//    Rev 1.68   Jul 06 2005 14:22:48   Yingbaol
// PET1235,FN01:add conditions for cancel trade
// 
//    Rev 1.67   Jul 06 2005 14:02:14   porteanm
// PET1171 EUSD 1B - Added ERR_CANCEL_MONEY_OUT_TXNS.
// 
//    Rev 1.66   Jun 14 2005 16:15:32   porteanm
// PET1024 FN40 - Guarantee Adjustments.
// 
//    Rev 1.65   Jun 10 2005 15:50:04   georgeet
// Synch-up error conditions with view for rel63.
// 
//    Rev 1.64   Jun 08 2005 10:10:02   smithdav
// Added retry on error 101.
// 
//    Rev 1.63   May 05 2005 15:49:08   porteanm
// PET OPC Confirm Reprint - For Release 63:ERR_REPRINT_RECORD_ALREADY_EXISTS - 656
// ERR_REPRINT_RECORD_DOES_NOT_EXIST - 657.
// 
//    Rev 1.62   Apr 22 2005 11:00:58   purdyech
// PET1117 - Sync from 1.55.1.0
// 
//    Rev 1.61   Apr 22 2005 10:25:32   hernando
// Rel61 condtions Synch-up with view.
// 
//    Rev 1.60   Apr 21 2005 15:52:24   georgeet
// Rel61 condtions Synch-up with view.
// 
//    Rev 1.59   Mar 18 2005 14:23:28   georgeet
// PET 1190 FN05 - Added new Error Codes for Verification of Cancelled Trade 614-648.
// 
//    Rev 1.58   Mar 13 2005 17:55:46   hernando
// PET1024 FN02 - Added Conditions 607, 608, 612-614.
// 
//    Rev 1.57   Mar 13 2005 17:38:40   hernando
// PET1024 FN02 - Added Conditions 607, 608, 612-614.
// 
//    Rev 1.56   Mar 07 2005 18:38:52   Fengyong
// PET1190 FN04 - Add error code 603-606, 609-611
// 
//    Rev 1.55   Feb 28 2005 18:06:52   hernando
// Rel 60/61 - Added DSTCDBrkr Conditions from 579 to 602.
// 
//    Rev 1.54   Jan 31 2005 13:36:54   aguilaam
// PTS 10038461 - corrected mapping for error 577 to Bonimax error
// 
//    Rev 1.53   Dec 10 2004 16:22:36   aguilaam
// PET910 - update with errors returned by views
// 
//    Rev 1.52   Nov 25 2004 14:59:56   Fengyong
// Error synvup for PET1117 FN54
// 
//    Rev 1.51   Nov 25 2004 13:27:42   vadeanum
// PET1117 FN08 - Shareholder Fund Broker.
// 
//    Rev 1.50   Nov 14 2004 15:00:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.49   Sep 22 2004 15:58:36   HERNANDO
// PET1094 FN06 - Added 554 to 556.
// 
//    Rev 1.48   Sep 22 2004 15:43:16   PURDYECH
// PTS10034090 - Display better error message when a View timeout is detected.
// 
//    Rev 1.47   Sep 08 2004 16:52:52   YINGBAOL
// PTS10031859: add condition for settlement
// 
//    Rev 1.46   Aug 06 2004 17:34:28   ZHANGCEL
// PET 1082 FNrlc - Tax Exempt Authorization support
// 
//    Rev 1.45   Jul 26 2004 10:41:12   VADEANUM
// PET1117 FN01 - Shareholder Static Data support.
// 
//    Rev 1.44   Mar 13 2004 17:53:34   SMITHDAV
// Added retry logic to resend a view if a error 67 ( record-locked) error is returned.
// 
//    Rev 1.43   Feb 25 2004 11:07:22   PURDYECH
// PET910 - Updated recycling logic
// 
//    Rev 1.42   Feb 18 2004 15:58:08   VADEANUM
// PET859 FN23 - ADL - Added ERR_DAILY_FEE_RECORD_ALREADY_EXISTS and ERR_DAILY_FEE_RECORD_DOES_NOT_EXIST.
// 
//    Rev 1.41   Dec 08 2003 16:03:06   popescu
// Adde ERR_INAVLID_TRANSFER, cond 499 for view 158
// 
//    Rev 1.40   Nov 24 2003 15:46:42   HERNANDO
// PET859 FN1 - Added new condition error codes from 487 to 509.
// 
//    Rev 1.39   Jul 28 2003 13:22:06   YINGBAOL
// add new conditions error code from 475 to 486
// 
//    Rev 1.38   Jun 04 2003 16:09:18   ZHANGCEL
// Added a new error code 474 into ifastdbrkr_conditions
// 
//    Rev 1.37   Apr 17 2003 17:21:12   ZHANGCEL
// update error conditions
// 
//    Rev 1.36   Mar 21 2003 18:29:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.35.1.0   Mar 03 2003 14:02:20   HSUCHIN
// updated error conditions
// 
//    Rev 1.35   Feb 05 2003 10:01:30   HSUCHIN
// sync up latest conditions from view error list
// 
//    Rev 1.34   Jan 07 2003 14:44:26   HSUCHIN
// bug fix to imports
// 
//    Rev 1.33   Jan 07 2003 14:25:26   HSUCHIN
// addeded 4 new conditions ERR_INVALID_VALID_TYPE, ERR_ACCTNBR_MUST_BE_ENTERED, ERR_SCALE_REC_REQUIRED_FEE_2_3, ERR_SHAREHOLDER_FAMILY_EXISTS
// 
//    Rev 1.32   Nov 29 2002 15:46:00   HSUCHIN
// latest error list for release 50
// 
//    Rev 1.31   Oct 29 2002 13:14:42   HSUCHIN
// sync up with release 49 - 1.30
// 
//    Rev 1.30   Oct 09 2002 23:55:22   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.29   Aug 29 2002 12:51:20   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.28   Jun 17 2002 10:07:22   HSUCHIN
// sync up with 1.27.1.0
// 
//    Rev 1.27.1.0   22 May 2002 21:12:30   PURDYECH
// BFData Implementation
// 
//    Rev 1.27   26 Feb 2002 16:46:00   HSUCHIN
// new conditions for rel 46
// 
//    Rev 1.26   20 Dec 2001 12:19:12   KOVACSRO
// new conditions
// 
//    Rev 1.25   Dec 12 2001 13:38:22   JANKAREN
// Added new conditions
// 
//    Rev 1.24   13 Nov 2001 14:14:32   PURDYECH
// Add connectionTime implementation
// 
//    Rev 1.23   26 Oct 2001 12:11:18   HSUCHIN
// added logData for raw request/response
// 
//    Rev 1.22   25 Sep 2001 13:23:42   PURDYECH
// Added setRequestTime method to allow the request time to be set externally.
// 
//    Rev 1.21   31 Aug 2001 13:50:42   HSUCHIN
// new conditions
// 
//    Rev 1.20   15 Aug 2001 15:23:36   HSUCHIN
// added new conditions
// 
//    Rev 1.19   Aug 10 2001 11:33:44   OLTEANCR
// added condition ERR_DUPLICATE_CONTRACT (268)
// 
//    Rev 1.18   07 Aug 2001 11:33:50   PURDYECH
// Added code to get timing data for the assignment of incoming data to a Data object.
// 
//    Rev 1.17   24 Jul 2001 14:44:18   HSUCHIN
// added code to log error and time elapsed for transactions
// 
//    Rev 1.16   17 Jul 2001 11:23:38   PURDYECH
// Added TxnStats code to track view timing information.
// 
//    Rev 1.15   Jun 26 2001 12:54:52   PURDYECH
// Infrastructure Release 1.9 Integration.
// 
//    Rev 1.14   Jun 18 2001 17:23:36   HERNANDO
// Added conditions.
// 
//    Rev 1.13   03 May 2001 14:03:32   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.12   Mar 02 2001 15:20:14   BUZILAMI
// corresp bank changes
// 
//    Rev 1.11   16 Feb 2001 14:40:14   SMITHDAV
// Fixed UNKNOWN_ERROR_RESPONSE response type handling.
// 
//    Rev 1.10   Feb 12 2001 15:53:34   HSUCHIN
// The host is not set on the constuctor, but set using setHost method
// 
//    Rev 1.9   09 Feb 2001 14:37:14   SMITHDAV
// Improve DSTCResponseBuffer exception reporting.
// 
//    Rev 1.8   Jan 30 2001 09:26:46   HSUCHIN
// bring back ERR_INVALID_TRANSID_CURRENCY_...
// 
//    Rev 1.7   Jan 30 2001 09:24:52   HSUCHIN
// changed construction not to create a vm connection. It will create a vm connection when the receive is issued.  This is to prevent multiple vm connection when async requestor is used.
// 
//    Rev 1.6   Dec 20 2000 16:37:50   YINGZ
// bring back ERR_INVALID_TRANSID_CURRENCY_FOR_TRANBANKING
// 
//    Rev 1.5   Nov 30 2000 12:41:36   VASILEAD
// fixed the link warning for ERR_DATA_NOT_FOUND
// 
//    Rev 1.4   Nov 20 2000 15:33:06   YINGZ
// bring back ERR_INVALID_BROKER_CODE so that view 135 work
// 
//    Rev 1.3   15 Nov 2000 15:28:40   SMITHDAV
// Add support for condition filtering.
// 
//    Rev 1.2   06 Nov 2000 14:53:06   SMITHDAV
// Add exception handling for new data broker system.
// 
//    Rev 1.1   30 Oct 2000 11:21:58   SMITHDAV
// Add support for getting more records. Also ignore no data found conditions by default.
// 
//    Rev 1.0   23 Oct 2000 20:31:26   SMITHDAV
// Initial revision.
 */

