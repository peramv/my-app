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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : Transfer.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : Transfer - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "transfer.hpp"

#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "amsmstrinfo.hpp"
#include "contractinfo.hpp"
#include "contractinfolist.hpp"
#include "entity.hpp"
#include "entityidslist.hpp"
#include "funddetail.hpp"
#include "fundtolist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "fundgrouptypelist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "mfaccount.hpp"
#include "protectedfundlist.hpp"
#include "redcodebytaxtypelist.hpp"
#include "redcodebytaxtype.hpp"
#include "segtradeentryvalidation.hpp"
#include "seqfundvalidation.hpp"
#include "shareholder.hpp"
#include "splitcommissionlist.hpp"
#include "taxtyperule.hpp"
#include "tradeacctalloc.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include "trademinamtcheck.hpp"
#include "transfeelist.hpp"
#include "translationtable.hpp"
#include "AMSMstrList.hpp"
#include "UnusualTradingValidation.hpp"
#include "funddetaillist.hpp"
#include "FundSuspensionValidation.h"
#include "IntraDayPricing.h"

#include <ifastdataimpl\dse_dstc0436_vw.hpp>
#include <ifastdataimpl\dse_dstc0486_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>

#include <ifastdataimpl\dse_dstc0487_req.hpp>
#include <ifastdataimpl\dse_dstc0487_vw.hpp>

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_trading_on_child_fnd_cls_not_allowed.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_trading_on_child_fnd_cls_not_allowed.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_parent_fund_is_not_allowed.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_parent_fund_is_not_allowed.h>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME                              = I_( "Transfer" );
   const I_CHAR * const REALIGNMENT                            = I_( "RLG" );
   const I_CHAR * const TFSA_TAX_TYPE                          = I_( "V" );
   const I_CHAR * const EXTERNAL_TFSA_TAX_TYPE                 = I_("Z");
   const I_CHAR * const YES                                    = I_("Y");
   const I_CHAR * const GROSS                                  = I_("Y");
   const I_CHAR * const RESP_TAX_TYPES                         = I_("9,M");
   const I_CHAR * const RESP_BENEFALLOC_DEPOSIT                = I_("1");
   const I_CHAR * const RESP_TR_RED_CODES                      = I_("64,65");
   const I_CHAR * const RESP_AIP_RED_CODES                     = I_("66,67,79,80,B1");
   const I_CHAR * const BENEF_NAME                             = I_("BENNAME");
   const I_CHAR * const REDCODE_CLB_RETURN                     = I_( "75" );
   const I_CHAR * const REDCODE_ACES_RETURN                    = I_( "76" );
   const I_CHAR * const REDCODE_CESG_RETURN                    = I_( "83" );
   const I_CHAR * const SD_EXTERNAL_RESP_TAX_TYPES             = I_("F,N");
   const I_CHAR * const ENTITY_ANNUITANT                       = I_("05");
   const I_CHAR * const DEFAULT_REDEMPTION_ORDER               = I_("FM");
   const I_CHAR * const CONTRACT_STATUS_PENDINGDEATH           = I_("02");
   const I_CHAR * const ENTITY_ACCOUNTHOLDER                   = I_("01");
   const I_CHAR * const REDEMPTION_CODE_UC					   = I_("UC");	
   const I_CHAR * const DEPOSIT_CODE_UC						   = I_("90"); 
   const I_CHAR * const FUND_SUB_CAT_LOW_LOADED                = I_("05");
   const I_CHAR * const FUND_SUB_CAT_LOW_LOADED_4              = I_("06");
   const int            TRANS_TYPE_LENGTH				       = 2; 
   const I_CHAR * const CALLING_TYPE                  = I_( "Gating" );
}

namespace ifds
{
//management company options
   extern CLASS_IMPORT const BFTextFieldId DefaultAllocOverride;
   extern CLASS_IMPORT const BFTextFieldId TitleRestrict;
   extern CLASS_IMPORT const BFTextFieldId GICAllocOnly;
   extern CLASS_IMPORT const BFTextFieldId TIKRedCodes;
   extern CLASS_IMPORT const BFTextFieldId FndMrgRedCod;
   extern CLASS_IMPORT const BFTextFieldId DeathRedCode;
   extern CLASS_IMPORT const BFTextFieldId TIKRedCodes;
   extern CLASS_IMPORT const BFTextFieldId DefltRedCodeFlag;
   extern CLASS_IMPORT const BFTextFieldId TfrToDiffSH;
   extern CLASS_IMPORT const BFTextFieldId SpouseBenefReLn;
   extern CLASS_IMPORT const BFTextFieldId DeathRedCode;
   extern CLASS_IMPORT const BFTextFieldId ChildBenefReLn;
   extern CLASS_IMPORT const BFTextFieldId DefltRedCode;
   extern CLASS_IMPORT const BFTextFieldId TRExclRedCodes;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId DftOrdTypeDSK;
   extern CLASS_IMPORT const BFIntegerFieldId DftOrdTypeTR;
//attributes grid
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesFields;
   extern CLASS_IMPORT const BFTextFieldId TransferAttributes;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFTextFieldId FundGroupCode;
   extern CLASS_IMPORT const BFTextFieldId ClassReq;
   extern CLASS_IMPORT const BFTextFieldId FundToISIN;
   extern CLASS_IMPORT const BFTextFieldId PayIntOn;
   extern CLASS_IMPORT const BFTextFieldId FundToWKN;
   extern CLASS_IMPORT const BFTextFieldId FundToLFC;
   extern CLASS_IMPORT const BFTextFieldId ToCUSIP;
   extern CLASS_IMPORT const BFTextFieldId Currency;
//account fields
   extern CLASS_IMPORT const BFTextFieldId Unseizable;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId PensionJuris;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFDecimalFieldId OutstLLP;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId ClearingID;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFTextFieldId SelfDirected;
   extern CLASS_IMPORT const BFTextFieldId DeathStat;
   extern CLASS_IMPORT const BFTextFieldId DeathClaim;
//subst sets
   extern CLASS_IMPORT const BFTextFieldId TransferSourceOfFund;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeExchange;
//unrelated fields
   extern CLASS_IMPORT const BFTextFieldId PlanType;
   extern CLASS_IMPORT const BFTextFieldId EscrowFund;
   extern CLASS_IMPORT const BFTextFieldId EscrowClass;
   extern CLASS_IMPORT const BFDateFieldId EscrowDeff;
   extern CLASS_IMPORT const BFTextFieldId Escrow;
   extern CLASS_IMPORT const BFTextFieldId ExistAssignee;
   extern CLASS_IMPORT const BFDateFieldId EscrowStopDate;
   extern CLASS_IMPORT const BFDecimalFieldId AmtAssigned;
   extern CLASS_IMPORT const BFTextFieldId DepositTypeList;
   extern CLASS_IMPORT const BFTextFieldId FromCurrency;
   extern CLASS_IMPORT const BFTextFieldId InitPurch;
//cross-edits
   extern CLASS_IMPORT const BFTextFieldId WireOrdFndCls;
   extern CLASS_IMPORT const BFTextFieldId ToFundClass;
   extern CLASS_IMPORT const BFTextFieldId SettleLocRealignFromToFundXEdit;
   extern CLASS_IMPORT const BFTextFieldId SettleLocRealignFromToClassXEdit;
   extern CLASS_IMPORT const BFTextFieldId AcctToRedCode;
   extern CLASS_IMPORT const BFTextFieldId FromFundClassAcctTo;
   extern CLASS_IMPORT const BFTextFieldId FromToFundClass;
   extern CLASS_IMPORT const BFTextFieldId AmountAmtType;
   extern CLASS_IMPORT const BFTextFieldId IncvActive;
   extern CLASS_IMPORT const BFTextFieldId IncvBasedOn;
   extern CLASS_IMPORT const BFTextFieldId TransType; 
   extern CLASS_IMPORT const BFTextFieldId LockedIn;
   extern CLASS_IMPORT const BFDateFieldId SettleInDate;
   extern CLASS_IMPORT const BFTextFieldId DftOrdType;
   extern CLASS_IMPORT const BFTextFieldId DeathClaimRedCodes;
   extern CLASS_IMPORT const BFTextFieldId MinimumApplies;
   extern CLASS_IMPORT const BFTextFieldId DepAllowed;
   extern CLASS_IMPORT const BFTextFieldId SiblingOnly;
   extern CLASS_IMPORT const BFTextFieldId AIPWithdrawalExists;
   extern CLASS_IMPORT const BFTextFieldId RESPTradeCrossEdit;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFTextFieldId WarnParam1;
   extern CLASS_IMPORT const BFTextFieldId WarnParam2;
   extern CLASS_IMPORT const BFDecimalFieldId Fee;
   //extern CLASS_IMPORT const BFTextFieldId AmtTypeRedCode;
   extern CLASS_IMPORT const BFTextFieldId FieldAssignment;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFTextFieldId EAPEarningCodes; //P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
   extern CLASS_IMPORT const BFTextFieldId PFCrystalisation;
   extern CLASS_IMPORT const BFTextFieldId RedCodesGuaranteeOverride;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId AcctFromToXEdit;
   extern CLASS_IMPORT const BFTextFieldId GIRedemOrder;
   extern CLASS_IMPORT const BFTextFieldId GIRedemAmountType;
   extern CLASS_IMPORT const BFTextFieldId Status;
   extern CLASS_IMPORT const BFTextFieldId FromToSegTradeEntryCheck;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit1;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit2;
   extern CLASS_IMPORT const BFTextFieldId SDRTExemptCode;
   extern CLASS_IMPORT const BFTextFieldId SDRTReportFlag;  
   extern CLASS_IMPORT const BFTextFieldId FundSubCat;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFTextFieldId AllowableTransferValidation;   
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;

   extern CLASS_IMPORT const BFDateFieldId LastValDate;
   extern CLASS_IMPORT const BFDateFieldId TradeInDate;
   extern CLASS_IMPORT const BFTextFieldId XferInTradeDat;
   extern CLASS_IMPORT const BFTextFieldId PriceTypes;
}

namespace CND
{
   extern const long ERR_ORDERTYPE_MUST_BE_DIRECT;
   extern const long ERR_TO_ACCT_MUST_DIFF_FROM_ACCT_FOR_TRANSFER;
   extern const long ERR_TRANSFER_TAX_TYPE;
   extern const long ERR_TRANSFER_TO_PENSION_JURISDICTION_NOT_SAME;
   extern const long ERR_TRANSFER_TO_LIRA_NOT_ALLOWED;
   extern const long ERR_TRANSFER_TO_LIRA_NOT_ALLOWED_FOR_SHAREHOLDER_69;
   extern const long ERR_TRANSFER_TO_LRSP_NOT_ALLOWED;
   extern const long ERR_TRANSFER_TO_LRSP_NOT_ALLOWED_FOR_SHAREHOLDER_69;
   extern const long ERR_UNSEIZABLE_ACCOUNT_TRANSFER;
   extern const long ERR_WARN_LLP_REPAYMENT_EXCEED;
   extern const long ERR_DEPOSIT_TYPE_INVALID_FOR_TAXTYPE;
   extern const long ERR_DEPOSIT_TYPE_MUST_BE_06_OR_07;
   extern const long ERR_WARN_DEPOSIT_TYPE_07_INDICATES_EXCESS_FUND;
   extern const long ERR_WARN_LLP_REPAYMENT_PREVENT;
   extern const long ERR_LLP_REPAYMENT_UNALLOWED;
   extern const long ERR_DEPOSIT_TYPE_07_MUST_BEUSED_RIF;
   extern const long ERR_ANNITANT_BIRTHDAY_NOT_FOUND;
   extern const long ERR_ANNUITANT_OLDER_THAN_69;
   extern const long ERR_SHAREHOLDER_DECEASED;
   extern const long ERR_FUND_CLASS_TRANSFEROUT_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_TRANSFEROUT_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_NOT_APPLICABLE;
   extern const long WARN_FUND_CLASS_NOT_APPLICABLE;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_FUND_CLASS_TRANSFERIN_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_TRANSFERIN_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_XFER_NOT_ALLOWED;
   extern const long ERR_PARTIAL_TRANSFER_NOT_ALLOWED;
   extern const long ERR_FULL_TRANSFER_NOT_ALLOWED;
   extern const long ERR_TRANSFER_FUNDS_INVALID_FOR_TIK;
   extern const long ERR_INVALID_AMTTYPE_FOR_FULL_TRANSFER;
   extern const long ERR_FULL_EXCHANGE_INDICATED;
   extern const long ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND;
   extern const long ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND;
   extern const long ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS;
   extern const long ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS;
   extern const long ERR_AMTTYPE_APPL_TO_BEL_FUND;
   extern const long ERR_REDEMPTION_CODE_IS_NOT_ALLOWED;
   extern const long ERR_ACCOUNTHOLDER_DEATH_DATE_REQUIRED;
   extern const long ERR_RED_CODE_NOT_ALLOWED_FOR_ALLOCATED_TRADE;
   extern const long ERR_INVALID_CODE_FOR_TRANSFER;
   extern const long ERR_AT_COST_ALLOCATION_NOT_ALLOWED;
   extern const long ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS;
   extern const long ERR_EX_AMT_MORE_THAN_HOLDING;
   extern const long ERR_WARN_EX_AMT_MORE_THAN_HOLDING;
   extern const long ERR_INVALID_CLOSE_FUND_REDEMPTION;
   extern const long ERR_INVALID_INTEREST_ON_CLOSE_FUND_REDEMPTION;
   extern const long ERR_ACCT_DESIGNATION_MUST_SAME_IN_KIND_TRANS;
   extern const long ERR_ACCT_TYPE_MUST_SAME_IN_KIND_TRANS;
   extern const long ERR_PLAN_TYPE_MUST_SAME_IN_KIND_TRANS;
   extern const long ERR_ACCT_OWNER_MUST_SAME_IN_KIND_TRANS;
   extern const long ERR_WARN_IN_KIND_TRANS_ACB;
   extern const long ERR_WARN_CANNOT_TRANSFER_FROM_RRIF;
   extern const long ERR_WARN_TRANSFER_TO_DIFF;
   extern const long ERR_WARN_CANNOT_TRANSFER_TO_DIFF;
   extern const long ERR_CAN_TRANSFER_ONLY_TO_RRSP_RRIF;
   extern const long ERR_TRANSFER_BETWEEN_RRSP_INDIV_AND_RRSP_SPOUSAL_NOT_ALLOWED;
   extern const long ERR_WARN_CANNOT_TRANSFER_TO_DIFF;
   extern const long ERR_BENEF_WRONG_RELATE;
   extern const long ERR_CAN_TRANSFER_ONLY_TO_RRSP_RRIF;
   extern const long ERR_CAN_TRANSFER_ONLY_TO_RRIF;
   extern const long ERR_TFR_PROTECTED_FUND_TO_DIFFERENT_SIN;
   extern const long ERR_INVALID_AMTTYPE_FOR_INVESTMENT_ALLOCATION;
   extern const long ERR_NO_APPLICATBLE_FOR_TOFUND;
   extern const long ERR_INVALID_SETTLE_CURRENCY;
   extern const long ERR_TRANSFER_DEPOSIT_TYPE_NOT_APPLICABLE;
   extern const long ERR_SETTLEMENT_SOURCE_NOT_UPDATABLE;
   extern const long WARN_SETTLEMENT_SOURCE_NOT_UPDATABLE;

   extern const long ERR_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE;
   extern const long WARN_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE;
   extern const long ERR_LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED;
   extern const long WARN_LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED;
   extern const long ERR_LOCKEDIN_TO_NON_REGISTED_ALLOWED;
   extern const long WARN_LOCKEDIN_TO_NON_REGISTED_ALLOWED;

   extern const long WARN_CAN_TRANSFER_ONLY_TO_RRSP_RRIF;   
   extern const long WARN_REDEMPTION_CODE_IS_NOT_ALLOWED;

   extern const long ERR_ORDERTYPE_WIRE;
   extern const long WARN_ORDERTYPE_WIRE;
   extern const long ERR_ORDERTYPE_DIRECT;
   extern const long WARN_ORDERTYPE_DIRECT;
   extern const long ERR_TR_INVALID_RED_CODE;

   extern const long ERR_EMPTY_FUNDCLASS;
   extern const long ERR_SAME_FUND_CLASS_FOR_REALIGNMENT_TR;

   extern const long ERR_FR_TO_CLEARING_METHOD_NOT_SAME_AND_NOT_RLG;
   extern const long ERR_INVALID_CLEARING_METHOD_FOR_REALIGNMNT_TR;

   extern const long WARN_GROSS_REDEMPTION_MINIMUM_APPLIES;
   extern const long ERR_GROSS_REDEMPTION_MINIMUM_APPLIES;
   
   extern const long ERR_DEPOSITS_NOT_ALLOWED;
   extern const long ERR_DIFFERENT_SIBLINGONLY_STATUS;
   extern const long WARN_DIFFERENT_SIBLINGONLY_STATUS;

   extern const long ERR_DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX;
   extern const long WARN_DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX;
   extern const long ERR_DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER;
   extern const long WARN_DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER;
   extern const long ERR_DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER;
   extern const long WARN_DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER;
   extern const long ERR_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED;
   extern const long WARN_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED;
   extern const long ERR_TRX_NOTINAL_BALANCE;
   extern const long ERR_DEPTYPE_REDCODE_NOT_ALLOWED_NON_QESI_ENV;
   //extern const long ERR_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   //extern const long WARN_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern const long WARN_RESP_TRANSACTION_AMT_EQ_LESS_FIFTHY_THSND;
   extern const long WARN_RESP_TRANSACTION_MIGHT_TRIGGER_GRANT_REPAYMENT;
   extern const long ERR_DOD_ENTITY_TYPE_MISSING;
   extern const long WARN_DOD_ENTITY_TYPE_MISSING;
   extern const long ERR_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT;
   extern const long WARN_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT;
   extern const long ERR_ANNUITANT_SIN_NOT_THE_SAME;
   extern const long ERR_GUARANTEE_OVERRIDE_FLAG_IS_REQUIRED;
   extern const long WARN_GUARANTEE_OVERRIDE_FLAG_IS_YES;
   extern const long WARN_GUARANTEE_OVERRIDE_FLAG_IS_NO;
   extern const long ERR_TIK_WITH_GUARANTEE_OVERRIDE_SAME_FUND_CLASS;
   extern const long ERR_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED;
   extern const long WARN_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED;
   extern const long ERR_LWA_AGE_RATE_IS_NOT_APPLICABLE;
   extern const long WARN_LWA_AGE_RATE_IS_NOT_APPLICABLE;
   extern const long ERR_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME;
   extern const long WARN_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME;
   extern const long ERR_LWA_OPTION_NOT_MATCH;
   extern const long WARN_LWA_OPTION_NOT_MATCH;
   extern const long ERR_DEATH_CLAIM_REDEMPTION_CODE;
   extern const long ERR_WARN_DEATH_CLAIM_REDEMPTION_CODE;
   extern const long ERR_CONTRACT_ACCT_STATUS_ACTIVE;
   extern const long ERR_WARN_CONTRACT_ACCT_STATUS_ACTIVE;
   extern const long ERR_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
   extern const long WARN_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
   extern const long ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM;
   extern const long ERR_TRANSFER_DIFFERENT_TO_FROM_FUND_CLASS;
   extern const long WARN_TRANSFER_DIFFERENT_TO_FROM_FUND_CLASS;
   extern const long ERR_TRFX_AGE_DIFF_NOT_ALLOWED;
   extern const long WARN_TRFX_AGE_DIFF_NOT_ALLOWED;
   extern const long ERR_TRFX_AGE_DIFF_NOT_ALLOWED;
   extern const long WARN_TRFX_AGE_DIFF_NOT_ALLOWED;
   extern const long ERR_REDEMPTION_DEPOSIT_CODE_NOT_VALID;
   extern const long ERR_INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES;
   extern const long WARN_INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES;
   extern const long ERR_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME;
   extern const long WARN_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME;
   extern const long ERR_TR_NOT_ALLOW_FROM_TAXTYPE_TO_TAXTYPE;
   extern const long ERR_ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME;
   extern const long ERR_ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS;
   extern const long WARN_ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME;
   extern const long WARN_ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS;
   extern const long ERR_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL;
   extern const long WARN_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL;
   extern const long ERR_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
   extern const long WARN_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
   extern const long WARN_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
   extern const long ERR_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
   extern const long ERR_FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT;
   extern const long WARN_FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT;
   extern const long ERR_FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT;
   extern const long WARN_FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT;
   extern const long ERR_FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT;
   extern const long WARN_FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT;
   extern const long WARN_CASH_DATE_MANDATORY;
   extern const long ERR_CASH_DATE_MANDATORY;
}


namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_MIX_OVERRIDE;
   extern CLASS_IMPORT I_CHAR * const UNSEIZABLE_ACC;
   extern CLASS_IMPORT I_CHAR * const TRANSF_BETWEEN_2_RRIF_SH;
   extern CLASS_IMPORT I_CHAR * const TRANS_DIFF_SH;
}

namespace IFASTERR
{
   // if order source is valid for account designation
   extern CLASS_IMPORT I_CHAR * const CONTRACT_ACCT_STATUS_INACTIVE;
   extern CLASS_IMPORT I_CHAR * const TR_XR_AMOUNT_IS_GREATER_THAN_ACCOUNT_BALANCE;
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT_SOURCE_IS_NOT_UPDATABLE;
   extern CLASS_IMPORT I_CHAR * const DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE;
   extern CLASS_IMPORT I_CHAR * const LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const LOCKEDIN_TO_NON_REGISTED_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const ORDERTYPE_WIRE;
   extern CLASS_IMPORT I_CHAR * const ORDERTYPE_DIRECT;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_CODE_IS_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const CAN_TRANSFER_ONLY_TO_RRSP_RRIF;
   extern CLASS_IMPORT I_CHAR * const GROSS_REDEMPTION_MINIMUM_APPLIES;
   extern CLASS_IMPORT I_CHAR * const DIFFERENT_SIBLINGONLY_STATUS;
   extern CLASS_IMPORT I_CHAR * const DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX;
   extern CLASS_IMPORT I_CHAR * const AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED;
   //extern CLASS_IMPORT I_CHAR * const SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const DOD_ENTITY_TYPE_MISSING;
   extern CLASS_IMPORT I_CHAR * const ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const LWA_AGE_RATE_IS_NOT_APPLICABLE;
   extern CLASS_IMPORT I_CHAR * const ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME;
   extern CLASS_IMPORT I_CHAR * const LWA_OPTION_NOT_MATCH;
   extern CLASS_IMPORT I_CHAR * const MUST_ENTER_A_DEATH_CLAIM_REDEMPTION_CODE;
   extern CLASS_IMPORT I_CHAR * const CONTRACT_ACCOUNT_STATUS_IS_ACTIVE;
   extern CLASS_IMPORT I_CHAR * const LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE;
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_DIFFERENT_FUND_CLASS_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const TRFX_AGE_DIFF_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_NOT_APPLICABLE;
   extern CLASS_IMPORT I_CHAR * const ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME;
   extern CLASS_IMPORT I_CHAR * const ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS;
   extern CLASS_IMPORT I_CHAR * const RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL;
   extern CLASS_IMPORT I_CHAR * const RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
   extern CLASS_IMPORT I_CHAR * const TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
   extern CLASS_IMPORT I_CHAR * const TRADING_ON_CHILD_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
   extern CLASS_IMPORT I_CHAR * const PARENT_FUND_IS_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT;
   extern CLASS_IMPORT I_CHAR * const FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT;
   extern CLASS_IMPORT I_CHAR * const FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT;
   extern CLASS_IMPORT I_CHAR * const CASH_DATE_MANDATORY;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const CLEARING;
}

namespace IDS
{
   extern const I_CHAR * const SIN;
}

namespace FUND_LOAD_TYPE
{
   extern CLASS_IMPORT I_CHAR * const BACKEND_LOAD;
   extern CLASS_IMPORT I_CHAR * const CHARGEBACK;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //Field DD Id,              State Flags,      Group Flags 
   { ifds::SettleLocRealignFromToFundXEdit,  BFCBO::IMMEDIATE_VALIDATION,  0},
   { ifds::SettleLocRealignFromToClassXEdit, BFCBO::IMMEDIATE_VALIDATION,  0},
   { ifds::AcctToRedCode,                    BFCBO::IMMEDIATE_VALIDATION,  0},
   { ifds::FromFundClassAcctTo,              BFCBO::IMMEDIATE_VALIDATION,  0},
   { ifds::RESPTradeCrossEdit,               BFCBO::IMMEDIATE_VALIDATION,  0},
   { ifds::AcctFromToXEdit,                  BFCBO::IMMEDIATE_VALIDATION,  0},
   { ifds::FieldCrossEdit1,                  BFCBO::IMMEDIATE_VALIDATION,  0},
   { ifds::SDRTExemptCode,                   BFCBO::NONE,                  0}, 
};  

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

namespace DATE_VALIDATION
{
   extern const I_CHAR * const DEFAULT_TRADE_DATE;
   extern const I_CHAR * const SETTLE_DATE;
}

namespace SOURCE_OF_FUND
{
   extern const I_CHAR *const TRANSITION;
}

//******************************************************************************
Transfer::Transfer (BFAbstractCBO &parent) :Trade (parent)
, _blTaxable(false)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);

   registerMemberData( NUM_FIELDS,
                        (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0,
                        NULL);

   addCrossEdit (ifds::SettleLocRealignFromToFundXEdit,  ifds::FromFund);
   addCrossEdit (ifds::SettleLocRealignFromToFundXEdit,  ifds::ToFund);
   addCrossEdit (ifds::SettleLocRealignFromToClassXEdit, ifds::FromClass);
   addCrossEdit (ifds::SettleLocRealignFromToClassXEdit, ifds::ToClass);

   addCrossEdit (ifds::AcctToRedCode, ifds::AccountTo); 
   addCrossEdit (ifds::AcctToRedCode, ifds::RedCode);   

   addCrossEdit (ifds::FromFundClassAcctTo, ifds::FromFund);
   addCrossEdit (ifds::FromFundClassAcctTo, ifds::FromClass);
   addCrossEdit (ifds::FromFundClassAcctTo, ifds::AccountTo);

   addCrossEdit (ifds::RESPTradeCrossEdit, ifds::RedCode);
   addCrossEdit (ifds::RESPTradeCrossEdit, ifds::DepositType);

   addCrossEdit (ifds::AcctFromToXEdit, ifds::AccountNum);
   addCrossEdit (ifds::AcctFromToXEdit, ifds::AccountTo);
   addCrossEdit (ifds::AcctFromToXEdit, ifds::RedCode);

   addCrossEdit (ifds::FieldCrossEdit1, ifds::AccountNum);
   addCrossEdit (ifds::FieldCrossEdit1, ifds::AccountTo);
   addCrossEdit (ifds::FieldCrossEdit1, ifds::GuaranteesOverride);

   bValidateAll = false;
}

//******************************************************************************
Transfer::~Transfer ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY Transfer::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::TRANSFER, 
                        idDataGroup, 
                        false);

   setFieldReadOnly (ifds::GrossOrNet, idDataGroup, true);

   setFieldSubstituteValues(ifds::RedemOrder, idDataGroup, ifds::GIRedemOrder);
   
   if(isGIInvestmentListApplicable(idDataGroup))
   {
      setFieldReadOnly( ifds::RedemOrder, idDataGroup, false);
      setFieldSubstituteValues(ifds::AmtType, idDataGroup, ifds::GIRedemAmountType);
      DString redemOrder;
      getField( ifds::RedemOrder, redemOrder, idDataGroup, false);
      if(isNew())
         setFieldNoValidate ( ifds::RedemOrder, DEFAULT_REDEMPTION_ORDER, idDataGroup, false);
   }
   else
   {
      setFieldNoValidate ( ifds::RedemOrder, I_(""), idDataGroup, false);
      setFieldReadOnly( ifds::RedemOrder, idDataGroup, true);
      setFieldSubstituteValues (ifds::AmtType, idDataGroup, ifds::AmountTypeExchange);

   };

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Transfer::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool Transfer::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool Transfer::isAccountCloningAllowed (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool Transfer::isSettleLocAllowed (const BFDataGroupId &idDataGroup)
{
   bool bIsClearingAcct = false;
   DString fromAccount, 
      toAccount;

   getField (ifds::AccountNum, fromAccount, idDataGroup, false);
   getField (ifds::AccountTo, toAccount, idDataGroup, false);

   if (!fromAccount.empty())
   {
      MFAccount *pMFAccountFrom = NULL;

      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                          fromAccount, 
                                          pMFAccountFrom) <= WARNING && 
            pMFAccountFrom)
      {
         bIsClearingAcct |= pMFAccountFrom->isClearingAcount (idDataGroup) &&
                            pMFAccountFrom->hasSettlementLocation (idDataGroup);
      }
   }
   if (!toAccount.empty())
   {
      MFAccount *pMFAccountTo = NULL;

      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                           toAccount, 
                                           pMFAccountTo) <= WARNING && 
            pMFAccountTo)
      {
         bIsClearingAcct |= pMFAccountTo->isClearingAcount (idDataGroup) &&
                            pMFAccountTo->hasSettlementLocation (idDataGroup);
      }
   }
   return bIsClearingAcct;
}

//******************************************************************************
void Transfer::getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                         BFFieldId &classCodeFieldId)
{
   fundCodeFieldId = ifds::ToFund;
   classCodeFieldId = ifds::ToClass;
}

//******************************************************************************
void Transfer::getAccountFieldId (BFFieldId &accountFieldId)
{
   accountFieldId = ifds::AccountTo;
}

//******************************************************************************
SEVERITY Transfer::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
   Trade::preInitWithDefaultValues (idDataGroup);

//amount type
   setFieldSubstituteValues (ifds::AmtType, idDataGroup, ifds::AmountTypeExchange);
//transfer/exchange pay type
   setFieldAllSubstituteValues (ifds::TradesPayType, idDataGroup, NULL_STRING);
   setFieldReadOnly (ifds::TradesPayType, idDataGroup, true);
   setFieldRequired (ifds::TradesPayType, idDataGroup, false);
//source of fund
   TranslationTable *pTranslationTable = NULL;
   if ( getMgmtCo().getTranslationTable ( I_("PS"), 
                                          pTranslationTable) <= WARNING &&
        NULL != pTranslationTable )
   {
      DString dstrTransferSrcOfFundCodeList;
      pTranslationTable->getTransferSrcOfFundCodeList (dstrTransferSrcOfFundCodeList);

      loadSubstitutionList( ifds::SrcOfFund, 
                            idDataGroup,
                            dstrTransferSrcOfFundCodeList);
   }

//account to is a required field
   setFieldRequired (ifds::AccountTo, idDataGroup, true);
   setFieldValid (ifds::AccountTo, idDataGroup, false);
   setFieldReadOnly (ifds::AccountTo, idDataGroup, false);
//user not required to set the settle currency for transfers, the system will take care of it
   setFieldReadOnly (ifds::SettleCurrency, idDataGroup, true);
//not required
   setFieldRequired (ifds::SettleCurrency, idDataGroup, false);

   bool  bReadOnly = isWireSupported (idDataGroup); 

   setFieldReadOnly (ifds::OrderType, idDataGroup, !bReadOnly); 
   setFieldRequired (ifds::RedCode, idDataGroup, false);
   setFieldReadOnly (ifds::NetworkID, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Transfer::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Trade::doInitWithDefaultValues (idDataGroup);
//regradless of any defaults. pay type is null string
   setFieldNoValidate ( ifds::TradesPayType, NULL_STRING, idDataGroup, false, 
                        false, 
                        true);

   DString dstrFieldAssignment;
   DString dstrWireOrderNum;

   getField (ifds::FieldAssignment, dstrFieldAssignment, idDataGroup, false);
   getField (ifds::WireOrdNum, dstrWireOrderNum, idDataGroup, false);
   dstrWireOrderNum.stripLeading ('0');

   bool bAWDWire = dstrFieldAssignment == I_("FromAWD") && !dstrWireOrderNum.empty () ? true : false;

   if (!isWireSupported (idDataGroup) || !bAWDWire)
   {
      setFieldNoValidate ( ifds::OrderType, N, idDataGroup, false, //'direct'
                           true, 
                           true); //notify
   }

   setFieldNoValidate (ifds::RedCode, I_("01"), idDataGroup, false, false, true);
   
   setFieldNoValidate ( ifds::PFCrystalisation, I_("01"), idDataGroup, false,false,false);
   enablePFCrystalisationFlag(idDataGroup);

   setFieldNoValidate ( ifds::SDRTExemptCode, NULL_STRING, idDataGroup, false, 
	   true, 
	   true);
   DString dstrSDRTRprtFlag;
   getWorkSession ().getOption (ifds::SDRTReportFlag, dstrSDRTRprtFlag, idDataGroup,  false);
   bool SDRTReadOnly = dstrSDRTRprtFlag.stripAll().upperCase() == YES;
   setFieldReadOnly (ifds::SDRTExemptCode, idDataGroup, !SDRTReadOnly);

   addBlankToSubSet (ifds::Deconversion, idDataGroup);
   setFieldNoValidate (ifds::Deconversion, I_("N"), idDataGroup, false);
   if (isNew())
   {
	   setFieldReadOnly( ifds::Deconversion, idDataGroup, false );
   }
}

//******************************************************************************
SEVERITY Transfer::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges"));
   if (!_bInitPending)
   {
      setFieldNoValidate ( ifds::TradesPayType, NULL_STRING, idDataGroup, false, false, true, 
                           false);  //no related changes
   }
//attributes grid
   DString transferAttributeSubstList;

   BFProperties *pBFProperties = 
      getFieldProperties (ifds::TransferAttributes, idDataGroup);
   
   pBFProperties->getAllSubstituteValues (transferAttributeSubstList);

   if(  !isROATransType( idDataGroup ) )
   {
      transferAttributeSubstList = 
         removeItemFromSubtList ( transferAttributeSubstList, 
                                  I_("ROAAmount"));   
   }

   if (!isMCHSecRecIndApplicable (idDataGroup))
   {
      transferAttributeSubstList = 
         removeItemFromSubtList ( transferAttributeSubstList, 
                                  I_("MCHFileIndicator"));
      transferAttributeSubstList = 
         removeItemFromSubtList ( transferAttributeSubstList, 
                                  I_("SecRecFileIndicator"));
   }

   if (!isWireSupported(idDataGroup))
   {
      transferAttributeSubstList = 
         removeItemFromSubtList ( transferAttributeSubstList, 
         I_("SettlementType"));
   }


   if (!isXferInDateActive(idDataGroup))
   {
	   transferAttributeSubstList =  removeItemFromSubtList ( transferAttributeSubstList, 
															I_("TradeInDate"));
		transferAttributeSubstList = removeItemFromSubtList ( transferAttributeSubstList, 
															I_("ValuationInDt"));
   }
   setFieldAllSubstituteValues ( ifds::TradeAttributesFields, 
                                 idDataGroup, 
                                 transferAttributeSubstList);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::doValidateField ( const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (Trade::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if ( idField == ifds::SettleLocRealignFromToFundXEdit) 
      {
         validateFromToFundForRealignClearingMethod (idDataGroup);
      }
      else if (idField == ifds::SettleLocRealignFromToClassXEdit) 
      {
         validateFromToClassForRealignClearingMethod (idDataGroup);
      }
      else if (idField == ifds::AcctToRedCode)
      {
         validateAccountToRedCode (idDataGroup); 
      }
      else if (idField == ifds::FromFundClassAcctTo) 
      {
         validateProtectedFundAllowedTransfers (idDataGroup);
      } 
      else if (idField == ifds::FrClearingMethod || 
               idField == ifds::ToClearingMethod)
      {
         validateClearingForRealignmntTr( idDataGroup );
      }
      else if ( idField == ifds::RESPTradeCrossEdit )
      {
         validateRedCodeDepTypeRESPTrade ( idDataGroup );
      }
      else if (idField == ifds::LinkedEntityId)
      {
         validateAIPEntity (idDataGroup);
         //P0185010.FN02.R02.01 - Delivering EAP written notice and tax info return
         validateEAPEntityAddress(idDataGroup);
      }
      else if (idField == ifds::GuaranteesOverride)
      {
         validateGuaranteesOverride(strValue,idDataGroup);
      }
      else if ( idField == ifds::FieldCrossEdit1)
      {
         validateGuaranteesOverrideAcctFromTo(idDataGroup);
      }
      else if(idField == ifds::AcctFromToXEdit)
      {
         //validateAcctFromToXEdit(idDataGroup);
      }
	  else if ( idField == ifds::RedCode    || 
	            idField == ifds::DepositType )
	  {
		  validateRedCodeDepTypeUCTrade( idDataGroup );

          if (idField == ifds::DepositType) 
          {
              MFAccount *pMFAccountTo = NULL;
              DString dstrAcctTo;

              getField(ifds::AccountTo, dstrAcctTo, idDataGroup);

              if (!dstrAcctTo.empty() && DSTCommonFunctions::codeInList (strValue, I_("1,2,71")) &&
                  getWorkSession().getMFAccount(idDataGroup, dstrAcctTo, pMFAccountTo) <= WARNING && pMFAccountTo)
              {
                  pMFAccountTo->validateMoneyInTFSA(idDataGroup);
              }
          }
	  }

      //Softcapped validation
      if (idField == ifds::ToFund || idField == ifds::ToClass)
      {
          validateToSoftCapCheck(idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Transfer::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   Trade::doInit (data);

   DString accountNum,
      accountTo;

   getField (ifds::AccountNum, accountNum, BF::HOST, false);
   getField (ifds::AccountTo, accountTo, BF::HOST, false);
//redemption code list
   loadDepRedCodeSubstList (accountNum, I_("R"), BF::HOST);
//load deposit code subst list
   loadDepRedCodeSubstList ( accountTo, 
                             I_("D"),  //deposit type
                             BF::HOST);

   clearingRelatedChanges (BF::HOST, false); //to side
   amsAccountRelatedChanges (BF::HOST);
   
   DString dstrToSettleInstrCode;

   // clearing to Side
   getField (ifds::ToSettlInstrCode, dstrToSettleInstrCode, BF::HOST, false);   
   bool bNotApplicable = dstrToSettleInstrCode == I_("N/A") || dstrToSettleInstrCode.empty();
   setFieldReadOnly (ifds::ToDeliveryTo, BF::HOST, !bNotApplicable);
   setFieldReadOnly (ifds::ToInFavourOf, BF::HOST, !bNotApplicable);
   setFieldReadOnly (ifds::ToForAccount, BF::HOST, !bNotApplicable);

   withholdingTaxRelatedChanges (BF::HOST);
   
   DString dstrSDRTRprtFlag;
   getWorkSession ().getOption (ifds::SDRTReportFlag, dstrSDRTRprtFlag, BF::HOST,  false);
   bool SDRTReadOnly = dstrSDRTRprtFlag.stripAll().upperCase() == YES;
   setFieldReadOnly (ifds::SDRTExemptCode, BF::HOST, !SDRTReadOnly);
   refreshIntradayPricing(BF::HOST);
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Transfer::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   if (Trade::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      // if there are any changes 'to fund/to class' must be revalidated against softcap.
      setFieldValid(ifds::ToSoftCapCheck, idDataGroup, false);
      TradeFundAllocList *pFundAllocationList = NULL;

      if (isFieldUpdated(idField, idDataGroup) && 
          getFundAllocationList(pFundAllocationList, idDataGroup, false) <= WARNING && pFundAllocationList)
      {
            pFundAllocationList->setAllAllocsFndClsValidFlag(false, idDataGroup);
      }
      
      if (idField == ifds::AccountNum)
      {
         DString accountNum;

         getField (ifds::AccountNum, accountNum, idDataGroup, false);
         loadDepRedCodeSubstList (accountNum, I_("D"), idDataGroup);
         loadDepRedCodeSubstList (accountNum, I_("R"), idDataGroup);
         clearingRelatedChanges (idDataGroup);
         setFieldValid (ifds::DepositType, idDataGroup, false);
         setFieldValid (ifds::RedCode, idDataGroup, false);

         withholdingTaxRelatedChanges (idDataGroup);
      }
      else if (idField == ifds::AccountTo)
      {
//account to has changed; reset ToFund, ToClass and ToFundNumber
         setFieldNoValidate ( ifds::ToFund, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false);
         setFieldNoValidate ( ifds::ToClass, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false);
         setFieldNoValidate ( ifds::ToFundNumber, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false);
         setFieldNoValidate ( ifds::FundToISIN, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false);
         setFieldNoValidate ( ifds::FundToWKN, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false);
         setFieldNoValidate ( ifds::FundToLFC, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false);
		 setFieldNoValidate ( ifds::ToCUSIP, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false);
         DString strFormerSpouses;
         
         if( getFormerSpouseList( strFormerSpouses, idDataGroup ) <= WARNING )
         {
            setFieldAllSubstituteValues (ifds::LinkedEntityId, idDataGroup, strFormerSpouses);
            if( strFormerSpouses.strip() == I_("0=N/A;") )
            {
               setFieldNoValidate( ifds::LinkedEntityId, I_("0"), idDataGroup, false, true, true);
            }
         }

         DString accountNum;
         MFAccount *pMFAccount = NULL;

         getField (ifds::AccountTo, accountNum, idDataGroup, false);
         if ( getWorkSession().getMFAccount ( idDataGroup, 
                                              accountNum, 
                                              pMFAccount) <= WARNING && 
              pMFAccount)
         {
            //completely remove allocations
            BFObjIter iter (*this, idDataGroup);

            if (iter.positionByKey (I_("AccountAllocationList")))
            {
               iter.removeObjectFromMap (true);
               //also, reset the fund field
               setFieldNoValidate ( ifds::ToFund, NULL_STRING, idDataGroup, false, 
                                    false, //invalid
                                    true,  //notify
                                    true);   //do apply
               setFieldNoValidate ( ifds::ToClass, NULL_STRING, idDataGroup, false, 
                                    false, //invalid
                                    true,  //notify
                                    true);   //do apply
               setFieldNoValidate ( ifds::ToFundNumber, NULL_STRING, idDataGroup, false, 
                                    false, //invalid
                                    true,  //notify
                                    true);   //do apply
               setFieldNoValidate ( ifds::FundToISIN, NULL_STRING, idDataGroup, false, 
                                    false, //invalid
                                    true,  //notify
                                    true);   //do apply
               setFieldNoValidate ( ifds::FundToWKN, NULL_STRING, idDataGroup, false, 
                                    false, //invalid
                                    true,  //notify
                                    true);   //do apply
               setFieldNoValidate ( ifds::FundToLFC, NULL_STRING, idDataGroup, false, 
                                    false, //invalid
                                    true,  //notify
                                    true);   //do apply
			   setFieldNoValidate ( ifds::ToCUSIP, NULL_STRING, idDataGroup, false, 
                                    false, //invalid
                                    true,  //notify
                                    true);   //do apply
            }
            //load deposit code subst list
            loadDepRedCodeSubstList ( accountNum, 
                                      I_("D"),  //deposit type
                                      idDataGroup);

            amsAccountRelatedChanges (idDataGroup);
            setFieldNoValidate ( ifds::DepositType, I_("1"), idDataGroup, false, 
                                 false, //invalid
                                 true,  //notify
                                 true);   //do apply
            clearingRelatedChanges (idDataGroup, false); //to side
            setFieldValid (ifds::DepositType, idDataGroup, false);
            setFieldValid (ifds::RedCode, idDataGroup, false);

			orderRoutingRelatedChanges (idDataGroup);
		 }
         updateGuaranteeFeeOverride (idDataGroup);
      }
	  else if (idField == ifds::EffectiveDate || idField == ifds::TradeInDate)
      {
         // to force validation (can Fund still trade?)
         setFieldValid (ifds::ToFundClass, idDataGroup, false); 
         setFieldValid (ifds::FromToSegTradeEntryCheck, idDataGroup, false);
         validateTransferToLIRA (idDataGroup);
         validateTransferToLRSP (idDataGroup);
         PFCrystalisationRelatedChanges(idDataGroup);
         
         DString dstrToFund, dstrToClass;
         getField(ifds::ToFund, dstrToFund, idDataGroup);
         getField(ifds::ToClass, dstrToClass, idDataGroup);

         REVALIDATEFIELD(ifds::ToFund, idDataGroup);
         REVALIDATEFIELD(ifds::ToClass, idDataGroup);

         if (!dstrToFund.empty() && !dstrToClass.empty() &&
             isFieldValid(ifds::ToFund, idDataGroup) && 
             isFieldValid(ifds::ToClass, idDataGroup))
         {
             refreshAllocations(idDataGroup);
             setSettleCurrencyToFund(dstrToFund, dstrToClass, idDataGroup);
         }
		
		 orderRoutingRelatedChanges (idDataGroup);
		 
      }
      else if (idField == ifds::ToSettlLocCode)
      {
         setSettleLocationDescription (ifds::ToSettlLocCode, ifds::ToSettlLocDescription, idDataGroup);
      }
      else if (idField == ifds::ToSettlInstrCode)
      {
         DString settleInstrCode,
            accountNum;
         
         getField (ifds::AccountTo, accountNum, idDataGroup, false);
         getField (ifds::ToSettlInstrCode, settleInstrCode, idDataGroup, false);
         bool bNotApplicable = settleInstrCode == I_("N/A") || settleInstrCode.empty();

         if (!bNotApplicable)
         {
            setAcctSettlementInstr (settleInstrCode, accountNum, idDataGroup, false);
         }
         else //blank out the fields
         {
            setFieldNoValidate (ifds::ToDeliveryTo, NULL_STRING, idDataGroup, false, false, true);
            setFieldNoValidate (ifds::ToInFavourOf, NULL_STRING, idDataGroup, false, false, true);
            setFieldNoValidate (ifds::ToForAccount, NULL_STRING, idDataGroup, false, false, true);
         }
         setFieldReadOnly (ifds::ToDeliveryTo, idDataGroup, !bNotApplicable);
         setFieldReadOnly (ifds::ToInFavourOf, idDataGroup, !bNotApplicable);
         setFieldReadOnly (ifds::ToForAccount, idDataGroup, !bNotApplicable);
      }
      else if (idField == ifds::RedCode)
      {
         setFieldValid (ifds::DepositType, idDataGroup, false);
         PFCrystalisationRelatedChanges (idDataGroup);
         updateGuaranteeFeeOverride (idDataGroup);
      }
	  else if ( (ifds::ToClass == idField  ||  ifds::FromClass == idField ) && !_bInitPending) 
      {
		 PFCrystalisationRelatedChanges(idDataGroup);
      }
      else if (idField == ifds::FromToFundClass)
      {
         setFieldValid (ifds::AmountAmtType, idDataGroup, false);
         setFieldValid (ifds::FromToSegTradeEntryCheck, idDataGroup, false);
         setFieldValid (ifds::ToSoftCapCheck, idDataGroup, false);
		 //initPriceTypesList (idDataGroup);  
      }
      else if (idField == ifds::Amount)
      {
         if (isROAApplicable (idDataGroup))
         {
            roaAmountRelatedChanges( idDataGroup );
         }

         setBeneficiaryAllocationsInvalid (idDataGroup);
         updateNotinalDataWarning (idDataGroup);
      }
      else if (idField == ifds::FrClearingMethod || 
               idField == ifds::ToClearingMethod)
      {
         if (isWireSupported (idDataGroup) && !_bInitPending)
         {
            setDefaultOrderType (idDataGroup); 
         }
         setFieldValid (ifds::FromToFundClass, idDataGroup, false);
         setFieldValid (ifds::OrderType, idDataGroup, false);
      }
      else if( idField == ifds::OrderType )
      {
         DString dstrOrderType;
         getField (ifds::OrderType, dstrOrderType, idDataGroup, false);

         if(dstrOrderType == N )
         {
            //reset to default and set to readonly
            setFieldReadOnly (ifds::SettleType, idDataGroup, true);
            setFieldNoValidate (ifds::SettleType, I_("I"), idDataGroup, false, false, true, true);
         }
         else
         {
            setFieldReadOnly (ifds::SettleType, idDataGroup, false);

         }
      }
	  else if (idField == ifds::AmtType)
	  {
		  setFieldValid(ifds::ToFundClass, idDataGroup, false);
	  }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::canAccountTrade ( MFAccount *pMFAccount, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountTrade"));
//calls base class, 
   if (Trade::canAccountTrade (pMFAccount, idDataGroup) <= WARNING)
   {
      DString tradeDate;

      getField (ifds::EffectiveDate, tradeDate, idDataGroup);
      if (pMFAccount->canTrfExchOut (tradeDate, idDataGroup) <= WARNING)
      {
         pMFAccount->trferEscrow (tradeDate, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::canAccountToTrade ( MFAccount *pMFAccountTo, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountToTrade"));
//calls base class, 
   if (Trade::canAccountToTrade (pMFAccountTo, idDataGroup) <= WARNING)
   {
      DString accountNum,
         accountTo;

      getField (ifds::AccountNum, accountNum, idDataGroup);
      pMFAccountTo->getField (ifds::AccountNum, accountTo, idDataGroup, false);
      if (accountNum == accountTo)
      {
         ADDCONDITIONFROMFILE (CND::ERR_TO_ACCT_MUST_DIFF_FROM_ACCT_FOR_TRANSFER);
      }
      else
      {
         DString tradeDate;

         getField (ifds::EffectiveDate, tradeDate, idDataGroup);
         pMFAccountTo->canTrfExchIn (tradeDate, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::validateAccountTo ( MFAccount *pMFAccountTo, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAccountTo"));

   if ( Trade::validateAccountTo (pMFAccountTo, idDataGroup) <= WARNING)
   {
   // Rule 4: check if transfer from tax type to tax type is valid 
      DString accountNum,
         taxTypeFr, 
         taxTypeTo, 
         taxTypeFrForm, 
         taxTypeToForm;

      MFAccount *pMFAccount = NULL;

      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                           accountNum, 
                                           pMFAccount) <= WARNING && 
            pMFAccount )
      {
         pMFAccount->getField (ifds::TaxType, taxTypeFr, idDataGroup);
         pMFAccount->getField (ifds::TaxType, taxTypeFrForm, idDataGroup, true);
         pMFAccountTo->getField (ifds::TaxType, taxTypeTo, idDataGroup);
         pMFAccountTo->getField (ifds::TaxType, taxTypeToForm, idDataGroup, true);
         taxTypeFr.upperCase();
         taxTypeTo.upperCase();

         TaxTypeRule *pTaxTypeRule = NULL;
         if ( pMFAccountTo->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
         {// to account tax type rule
          // search TaxTypeFr in TaxTypeTo list; if it exists, return true

            if (!pTaxTypeRule->validTransfer (taxTypeFr, idDataGroup))
            {
               bool bEstateTransfer = false;

               if (DSTCommonFunctions::getMarket () == MARKET_IDS::CANADA)
               {
                  bEstateTransfer = isEstateTransfer (idDataGroup);
               }

               if (!bEstateTransfer)
               {
                  DString idiStr;
                  addIDITagValue (idiStr, I_( "FROMTAX"), taxTypeFrForm);
                  addIDITagValue (idiStr, I_( "TOTAX"), taxTypeToForm);
                  ADDCONDITIONFROMFILEIDI (CND::ERR_TRANSFER_TAX_TYPE, idiStr);
               }
            }
         }

         // If resp accounts validate sybling only flag:
         if (DSTCommonFunctions::codeInList (taxTypeFr, RESP_TAX_TYPES) &&
            DSTCommonFunctions::codeInList (taxTypeTo, RESP_TAX_TYPES))
         {
            DString fromSiblingOnly;
            DString toSibligOnly;

            pMFAccount->getField (ifds::SiblingOnly, fromSiblingOnly, idDataGroup);
            pMFAccountTo->getField (ifds::SiblingOnly, toSibligOnly, idDataGroup);

            if (fromSiblingOnly != toSibligOnly)
            {
               getErrMsg ( IFASTERR::DIFFERENT_SIBLINGONLY_STATUS,
                           CND::ERR_DIFFERENT_SIBLINGONLY_STATUS, 
                           CND::WARN_DIFFERENT_SIBLINGONLY_STATUS, 
                           idDataGroup);
            }
         }
      }

      if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         validateEscrowTaxTypeRIFTransfer (idDataGroup);
      }	 
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//fund validation
//******************************************************************************
SEVERITY Transfer::validateFundCode ( const DString &fundCode, 
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateFundCode"));
   if (Trade::validateFundCode (fundCode, idDataGroup) <= WARNING)
   {
      validateGICFund (fundCode, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateToFundCode ( const DString &fundCode, 
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateFundCode"));
   if (Trade::validateToFundCode (fundCode, idDataGroup) <= WARNING)
   {
      validateGICFund (fundCode, idDataGroup);
      DString accountNum;

      getField (ifds::AccountTo, accountNum, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Transfer::validateGICFund ( const DString &fundCode, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateGICFund"));

   FundMasterList *pFundMasterList; 

   if ( getMgmtCo().getFundMasterList (pFundMasterList) && 
        pFundMasterList)
   {
      DString gicAllocOnly;

      getWorkSession().getOption ( ifds::GICAllocOnly, 
                                   gicAllocOnly, 
                                   idDataGroup, 
                                   false
                                 );
      if (gicAllocOnly == Y)
      {
         if (pFundMasterList->isGICFund (fundCode))
         {
            //TODO add a more meaningful error message
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Transfer::validateFundClass (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));
   
   if (Trade::validateFundClass ( idDataGroup ) <= WARNING )
   {
     if (isSegEnvironment (idDataGroup))
     {
      // if SegClient and CotClient do the SegFundValidation
      DString accountNum, fundCode, classCode, tradeDate;
      getField (ifds::AccountNum,    accountNum, idDataGroup, false );
      getField (ifds::FromFund,      fundCode,   idDataGroup, false );
      getField (ifds::FromClass,     classCode,  idDataGroup, false );
      getField (ifds::EffectiveDate, tradeDate,  idDataGroup);

      if ( !fundCode.empty() &&
           !classCode.empty() &&
           !accountNum.empty())
      {
         SeqFundValidation *pSeqFundValidation = NULL;

         DString transType;
         getField( ifds::TradesTransType, transType, idDataGroup, false );

         if ( getSegFundValidation ( pSeqFundValidation, 
                                     fundCode, 
                                     classCode, 
                                     accountNum, 
                                     tradeDate,
                                     idDataGroup, 
                                     NULL_STRING,
                                     transType,
                                     NULL_STRING,
                                     NULL_STRING,
                                     NULL_STRING) <= WARNING &&
            pSeqFundValidation)
      
         {
            pSeqFundValidation->canTradeFundClass (idDataGroup);
         }
      }
     }
   }   
   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY Transfer::validateFundClass ( const DString &fundCode, 
                                       const DString &classCode, 
                                       const DString &accountNum, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));

   if (Trade::validateFundClass ( fundCode, 
                                  classCode, 
                                  accountNum, 
                                  idDataGroup) <= WARNING)
   {
//get the values of broker/branch/sales rep from trade (the 'from side')
      DString broker,
         branch,
         agent;

      getField (ifds::Broker, broker, idDataGroup);
      getField (ifds::Branch, branch, idDataGroup);
      getField (ifds::SlsrepCode, agent, idDataGroup);
      if (canFundTrade ( broker,
                         branch,
                         agent,
                         TRADETYPE::TRANSFER_OUT,
                         accountNum,
                         fundCode,
                         classCode,
                         CND::ERR_FUND_CLASS_TRANSFEROUT_STOP_FLAG_ON,
                         CND::ERR_WARN_FUND_CLASS_TRANSFEROUT_STOP_FLAG_ON,
                         idDataGroup) <= WARNING)
      {
         validateIfAllocatedAtCostTIKAllowed (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Transfer::validateToFundClass ( const DString &fundCode, 
                                         const DString &classCode, 
                                         const DString &accountNum, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));

   if (Trade::validateToFundClass ( fundCode, 
                                    classCode, 
                                    accountNum, 
                                    idDataGroup) <= WARNING)
   {
//get the values of broker/branch/sales rep to account (the 'to side')
      MFAccount *pMFAccountTo = NULL;
      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                           accountNum, 
                                           pMFAccountTo) <= WARNING &&
           pMFAccountTo)
      {
         DString broker,
            branch,
            agent;

         pMFAccountTo->getField (ifds::BrokerCode, broker, idDataGroup);
         pMFAccountTo->getField (ifds::BranchCode, branch, idDataGroup);
         pMFAccountTo->getField (ifds::Slsrep, agent, idDataGroup);
         if (canFundTrade ( broker,
                            branch,
                            agent,
                            TRADETYPE::TRANSFER_IN,
                            accountNum,
                            fundCode,
                            classCode,
                            CND::ERR_FUND_CLASS_TRANSFERIN_STOP_FLAG_ON,
                            CND::ERR_WARN_FUND_CLASS_TRANSFERIN_STOP_FLAG_ON,
                            idDataGroup) <= WARNING)
         {         
            bool bEmpty = fundCode.empty () && classCode.empty () ? true : false;

            if (!bEmpty && !isHypo())
            {
               // PET 1334: View will check if to/from funds are the same for Transfers.  
               // If funds are the same then view will check if there was existing EUSD Override on the In-Fund transaction, 
               // if yes, then trade is subject to EUSD and error 464 will be raised.  

               validateEUSDBackdates( fundCode, classCode, accountNum, idDataGroup );
            }

            moreValidateToFundClass (fundCode, classCode, idDataGroup);
            revalidateField(ifds::ToSoftCapCheck, idDataGroup);
         }
      }
      
      validateFundToWithSegValidation(idDataGroup) ;

      FundDetail *pFundDetail = nullptr;

      if (getWorkSession().getFundDetail(fundCode, classCode, idDataGroup, pFundDetail) && pFundDetail &&
           pFundDetail->isAMSParentFund(idDataGroup))
      {
         DString dstrAcctNumFr, 
            dstrAcctNumTo,
            dstrTradeDate;

         getField (ifds::AccountNum, dstrAcctNumFr, idDataGroup);
         getField (ifds::AccountTo, dstrAcctNumTo, idDataGroup);
         getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup, false);
         MFAccount *pMFAccount = nullptr,
            *pMFAccountTo = nullptr;

         if ( getWorkSession().getMFAccount (idDataGroup, dstrAcctNumFr, pMFAccount) <= WARNING && 
               pMFAccount &&
               getWorkSession().getMFAccount (idDataGroup, dstrAcctNumTo, pMFAccountTo) <= WARNING && 
               pMFAccountTo &&
               pMFAccount->isAMSAccount(idDataGroup) &&
               pMFAccountTo->isAMSAccount(idDataGroup) 
            )
         {
            DString dstrAcctFromAMSCode, dstrAcctToAMSCode;
            pMFAccount->getField(ifds::AMSCode, dstrAcctFromAMSCode, idDataGroup);
            pMFAccountTo->getField(ifds::AMSCode, dstrAcctToAMSCode, idDataGroup);

            if ( dstrAcctFromAMSCode != dstrAcctToAMSCode && dstrAcctToAMSCode.strip().empty())
            {
               getErrMsg(IFASTERR::TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS,
                  CND::ERR_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS,
                  CND::WARN_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS,
                  idDataGroup);
            }
            else if (dstrAcctFromAMSCode != dstrAcctToAMSCode && !dstrAcctToAMSCode.strip().empty())
            {
               getErrMsg(IFASTERR::RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL,
                  CND::ERR_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL,
                  CND::WARN_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL,
                  idDataGroup);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateToSoftCapCheck (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToSoftCapCheck "));

   DString accountTo, toFund, toClass, transType, fromFund, fromClass, tradeDate;

   getField (ifds::AccountTo, accountTo, idDataGroup, false);
   getField (ifds::ToFund, toFund, idDataGroup, false);
   getField (ifds::ToClass, toClass, idDataGroup, false);
   getField (ifds::FromFund, fromFund, idDataGroup, false);
   getField (ifds::FromClass, fromClass, idDataGroup, false);
   getField (ifds::TradesTransType, transType, idDataGroup, false);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
   
   if (transType == TRADETYPE::TRANSFER &&     //Twitch - different from/to account and different fund/class.
       !toFund.empty() && !toClass.empty() &&
       (fromFund.upperCase() != toFund.upperCase() || fromClass.upperCase() != toClass.upperCase()))
   {
       //AccountTo - Transfer In
       getWorkSession().fundClassSoftCappedCheck(accountTo, toFund, toClass, I_("DD"), tradeDate, idDataGroup);
   } 

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Transfer::moreValidateToFundClass ( const DString &fundCode,
                                             const DString &classCode,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("moreValidateToFundClass"));

   DString amtType;

   getField (ifds::AmtType, amtType, idDataGroup, false);
   if ( !fundCode.empty() &&
        !classCode.empty() &&
        DSTCommonFunctions::codeInList (amtType, I_("F,T")))
   {
      DString fromFund,
            fromClass,
            fromLoadType,
            toLoadType;

      getField (ifds::FromFund, fromFund, idDataGroup);
      getField (ifds::FromClass, fromClass, idDataGroup);
      if ( getFundField ( fromFund, 
                          fromClass, 
                          ifds::LoadType, 
                          fromLoadType) <= WARNING &&
           getFundField ( fundCode, 
                          classCode, 
                          ifds::LoadType, 
                          toLoadType) <= WARNING &&
           !(fromLoadType == I_("BEL") && toLoadType == I_("FEL")))
      {
         getErrMsg(IFASTERR::FUND_CLASS_NOT_APPLICABLE,
			          CND::ERR_FUND_CLASS_NOT_APPLICABLE,
			          CND::WARN_FUND_CLASS_NOT_APPLICABLE,
			  		  idDataGroup);
      }
   }
   if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
   {
      // if FundStatus_63 ( where ToFundCode = FundCode_63) = '02' and EffectiveDate > StatusDate_63,
      // then based on the Cfg-CappedFund value, issued error, warning or simply ignore the error
      FundMasterList *pFundMasterList = NULL;

      if ( getMgmtCo().getFundMasterList(pFundMasterList) <= WARNING && 
           pFundMasterList)
      {
         DString tradeDate;
         FundMaster *pFundMaster = NULL;

         getField (ifds::EffectiveDate, tradeDate, idDataGroup);
         if (pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster))
         {
            pFundMaster->cappedFundRule (tradeDate, idDataGroup);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Transfer::validateFromToFundClass ( const DString &fromFund_,
                                             const DString &fromClass_,
                                             const DString &toFund_,
                                             const DString &toClass_,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromToFundClass"));
   DString fromFund (fromFund_), 
   fromClass (fromClass_), 
    toFund (toFund_), 
    toClass (toClass_);
   DString allowFullPartial; // 0 - allow both, 1 - allow Partial only, 2 - allow Full only
   FundDetail *pFundDetail = NULL;
   bool bTransferAllowed;
   FundToList fundToList (*this );

   bTransferAllowed = fundToList.isTransferAllowed ( fromFund, 
                                                     fromClass, 
                                                     toFund, 
                                                     toClass, 
                                                     allowFullPartial);
   if (!bTransferAllowed)
   {
      DString idiStr;

      addIDITagValue (idiStr, I_("FUND"), fromFund);
      addIDITagValue (idiStr, I_("CLASS"), fromClass);
      addIDITagValue (idiStr, I_("TO_FUND"), toFund);
      addIDITagValue (idiStr, I_("TO_CLASS"), toClass);
      ADDCONDITIONFROMFILEIDI (CND::ERR_FUND_CLASS_XFER_NOT_ALLOWED, idiStr);
   }

   bool bEmpty = fromFund.empty () && fromClass.empty () && 
                 toFund.empty   () && toClass.empty   () ? true : false;

   if (!bEmpty && !isHypo() && bTransferAllowed)
   {
      DString   accountTo;

      getField (ifds::AccountTo, accountTo, idDataGroup, false);
      validateEUSDBackdates (toFund, toClass, accountTo, idDataGroup);
   }

   bool blValidTransfer = true;
   if ( isTransferInKind( fromFund, 
                          fromClass, 
                          toFund, 
                          toClass, 
                          idDataGroup,
                          blValidTransfer) > WARNING ||
         false == blValidTransfer)
   {
      // Funds invalid for Transfer In Kind. 
      ADDCONDITIONFROMFILE  (CND::ERR_TRANSFER_FUNDS_INVALID_FOR_TIK);
   }

   validateClearingForRealignmntTr (idDataGroup);

// PET157837 FN02 Country Schedule - Cross edit for validate account closed country.
// Transfer to same fund class, it will pass validation, 
   if ( !(fromFund.strip().upperCase()  == toFund.strip().upperCase() &&
          fromClass.strip().upperCase() == toClass.strip().upperCase()))
   {
      DString   accountTo;

      getField (ifds::AccountTo, accountTo, idDataGroup, false);
      validateClosedCountry (accountTo, idDataGroup);

   }
   if ( !(fromFund.strip().upperCase()  == toFund.strip().upperCase() &&
      fromClass.strip().upperCase() == toClass.strip().upperCase()))
   {
      DString transType;

      getField (ifds::TradesTransType, transType, idDataGroup, false);
      if (transType == TRADETYPE::TRANSFER )
      {
         getErrMsg ( IFASTERR::TRANSFER_DIFFERENT_FUND_CLASS_NOT_ALLOWED,
                     CND::ERR_TRANSFER_DIFFERENT_TO_FROM_FUND_CLASS, 
                     CND::WARN_TRANSFER_DIFFERENT_TO_FROM_FUND_CLASS, 
                     idDataGroup);
      }
   }

   DString accountNum,
      accountTo,
      fundCode,
      fundToCode,
      classCode,
      classToCode,
      tradeDate,
      transType,
      transId;

   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   getField (ifds::AccountTo, accountTo, idDataGroup, false);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
   getField (ifds::TradesTransType, transType, idDataGroup, false);
   getField (ifds::TransId, transId, idDataGroup,false);

   validateFromToSegTradeEntryCheck(accountNum,
                                    fromFund,
                                    fromClass,
                                    accountTo,
                                    toFund,
                                    toClass,
                                    tradeDate,
                                    transType,
                                    transId,
                                    idDataGroup);

   validateMasterActAMS(idDataGroup);

   // twitch, transfer to differnce account difference fund\class
   if ( !(fromFund.strip().upperCase()  == toFund.strip().upperCase() &&
      fromClass.strip().upperCase() == toClass.strip().upperCase()))
   {
      validateTwitchAgaintAMS(idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::isTransferInKind ( const DString &dstrFromFund, 
                                      const DString &dstrFromClass, 
                                      const DString &dstrToFund, 
                                      const DString &dstrToClass, 
                                      const BFDataGroupId &idDataGroup,
                                      bool &blValidTransfer)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "isTransferInKind" ) );

   blValidTransfer = true;

   DString dstrLocalFromFund( dstrFromFund ),
           dstrLocalFromClass( dstrFromClass ), 
           dstrLocalToFund( dstrToFund ),
           dstrLocalToClass( dstrToClass );

   dstrLocalFromFund.strip().upperCase();
   dstrLocalFromClass.strip().upperCase();
   dstrLocalToFund.strip().upperCase();
   dstrLocalToClass.strip().upperCase();
   
   // the code below mirrors night/TRANACB1.I, called by TRANSFR11.P (that checks only for fund match)
   // with the addition of Class check if FundGroupTypeList.ClassRequired = Y.
   if ( dstrLocalFromFund != dstrToFund )
   {   
      DString dstrFromFundGroupCode, dstrToFundGroupCode;

      DString dstrRedCode;
      getField( ifds::RedCode, dstrRedCode.stripAll(), idDataGroup );

      DString dstrTIKRedCodes,dstrFundMergerRedCodes;
      getWorkSession().getOption( ifds::TIKRedCodes, dstrTIKRedCodes, BF::HOST, false );      

      if( DSTCommonFunctions::codeInList( dstrRedCode, dstrTIKRedCodes ) )
      {
         getWorkSession().getOption( ifds::FndMrgRedCod, dstrFundMergerRedCodes, BF::HOST, false );         
         if ( !DSTCommonFunctions::codeInList( dstrRedCode, dstrFundMergerRedCodes ) )
         {
            blValidTransfer = false;
         }
         else
         {
            FundGroupTypeList *pFundGroupTypeList = NULL;
            if ( getMgmtCo().getFundGroupTypeList( pFundGroupTypeList, I_( "Umbrel" ) ) <= WARNING && 
                 NULL != pFundGroupTypeList )
            {
               blValidTransfer = false;

               bool blFromFundFound = false, 
                    blToFundFound = false;
               
               BFObjIter iter( *pFundGroupTypeList, idDataGroup, true , BFObjIter::ITERTYPE::NON_DELETED );
               iter.begin();
               while ( !iter.end() )
               {
                  BFCBO *pFundGroupType = dynamic_cast<BFCBO*>(iter.getObject());
                  if( NULL != pFundGroupType )
                  {
                     DString dstrClassRequired;
                     pFundGroupType->getField( ifds::ClassReq, dstrClassRequired,  idDataGroup );

                     if ( !blFromFundFound )
                     {
                        DString dstrCurrentFund, dstrCurrentClass;
                        pFundGroupType->getField( ifds::FundCode,  dstrCurrentFund,  idDataGroup );
                        if ( dstrCurrentFund.strip().upperCase() == dstrLocalFromFund )
                        {
                           if ( I_( "Y" ) == dstrClassRequired.stripAll().upperCase() )
                           {
                              pFundGroupType->getField( ifds::ClassCode, dstrCurrentClass, idDataGroup );
                           }
                           else
                              dstrLocalFromClass = I_( "" );

                           if ( dstrCurrentClass.strip().upperCase() == dstrLocalFromClass )
                           {
                              pFundGroupType->getField( ifds::FundGroupCode, dstrFromFundGroupCode, idDataGroup );
                              blFromFundFound = true;
                           }
                        }
                     }

                     if ( !blToFundFound )
                     {
                        DString dstrCurrentFund, dstrCurrentClass;
                        pFundGroupType->getField( ifds::FundCode,  dstrCurrentFund,  idDataGroup );
                        if ( dstrCurrentFund.strip().upperCase() == dstrLocalToFund )
                        {
                           if ( I_( "Y" ) == dstrClassRequired.stripAll().upperCase() )
                           {
                              pFundGroupType->getField( ifds::ClassCode, dstrCurrentClass, idDataGroup );
                           }
                           else
                              dstrLocalToClass = I_( "" );

                           if ( dstrCurrentClass.strip().upperCase() == dstrLocalToClass )
                           {
                              pFundGroupType->getField( ifds::FundGroupCode, dstrToFundGroupCode, idDataGroup );
                              blToFundFound = true;
                           }
                        }
                     }
                  
                     if ( blFromFundFound && blToFundFound )
                     {
                        if ( dstrFromFundGroupCode.strip().upperCase() == dstrToFundGroupCode.strip().upperCase() )
                        {
                           blValidTransfer = true;
                        }
                           
                        break;
                     }
                  }
                  ++iter;
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Transfer::fromFundClassRelatedChanges ( const DString &fundCode, 
                                                 const DString &classCode, 
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromFundClassRelatedChanges"));

   Trade::fromFundClassRelatedChanges (fundCode, classCode, idDataGroup);

   {
      //to trigger validation since for BEL funds transfers are allowed for certain amt types
      setFieldValid (ifds::AmtType, idDataGroup, false);

      setFieldValid (ifds::RedCode, idDataGroup, false);

      DString enableDefault, 
         defRedCode;
      getWorkSession().getOption (ifds::DefltRedCodeFlag, enableDefault, BF::HOST, false );
      getWorkSession().getOption (ifds::DefltRedCode, defRedCode, BF::HOST, false );

      if (enableDefault == Y && !defRedCode.empty())
      {
         bool blIsAtCostTIK = false;

         if ( getAtCostTIKStatus ( idDataGroup, 
                                   I_( "" ), 
                                   I_( "" ),  
                                   false, /* No allocation*/
                                   blIsAtCostTIK ) <= WARNING &&   
              blIsAtCostTIK )  
         {
            setField (ifds::RedCode, defRedCode, idDataGroup, false, true);
         }
      }
      clearROAAmount (idDataGroup);
       
      _bShouldRefreshSplitCommissions = true;
      refreshSplitCommissions(idDataGroup);

      if (isGIInvestmentListApplicable(idDataGroup))
      {
         DString redemOrder;
         getField(ifds::RedemOrder, redemOrder, idDataGroup, false);
         if(redemOrder == I_(""))
            setFieldNoValidate ( ifds::RedemOrder, DEFAULT_REDEMPTION_ORDER, idDataGroup, false);

         setFieldReadOnly( ifds::RedemOrder, idDataGroup, false);
         setFieldSubstituteValues(ifds::AmtType, idDataGroup, ifds::GIRedemAmountType);
      }
      else
      {
         setFieldReadOnly( ifds::RedemOrder, idDataGroup, true);
         setFieldNoValidate ( ifds::RedemOrder, I_(""), idDataGroup, false);
         setFieldSubstituteValues (ifds::AmtType, idDataGroup, ifds::AmountTypeExchange);
      };

      updateGuaranteeFeeOverride (idDataGroup);

      // move from trade CBO
      //PET 212427 FN 01 - Project Thunder  
      //Default the source of fund for pending trade if the value is specified in ‘ApplySrcofFund’ field. 
      //If the default is available, user cannot override it. 
      FundToList fundToList (*this);

      DString dstrApplySrcOfFund = fundToList.getApplySrcOfFund (fundCode, classCode, NULL_STRING, NULL_STRING);
      //bool bApplySrcOfFund = !dstrApplySrcOfFund.empty() && (dstrApplySrcOfFund  != SOURCE_OF_FUND::TRANSITION);
      bool bApplySrcOfFund = !dstrApplySrcOfFund.empty();

      if( bApplySrcOfFund ) {
         setFieldNoValidate(ifds::SrcOfFund, dstrApplySrcOfFund, idDataGroup, false, false, false);
      } else {
         setFieldNoValidate(ifds::SrcOfFund, NULL_STRING, idDataGroup, false, false, false);
      }
      setFieldReadOnly (ifds::SrcOfFund, idDataGroup, bApplySrcOfFund);
      //setFieldNoValidate(ifds::SrcOfFund, dstrApplySrcOfFund, idDataGroup, false, false, false);
      //setFieldReadOnly (ifds::SrcOfFund, idDataGroup, bApplySrcOfFund);

   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Transfer::toFundClassRelatedChanges ( const DString &fundCode, 
                                               const DString &classCode, 
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("toFundClassRelatedChanges"));
   Trade::toFundClassRelatedChanges (fundCode, classCode, idDataGroup);
   {
      if (isWireSupported (idDataGroup) && !_bInitPending)
      {
         setDefaultOrderType (idDataGroup); 
      }
      //do not refresh split commissions until all the apply related changes are done
      _bShouldRefreshSplitCommissions = false; 
      refreshAllocations (idDataGroup);

      //always set settlement currency to fund currency, always
      setSettleCurrencyToFund(fundCode, classCode, idDataGroup);
      setFieldReadOnly (ifds::UseEnteredFee, idDataGroup, !fundCode.empty() || !classCode.empty());
//invalidate the wireordfndclass
      setFieldValid (ifds::WireOrdFndCls, idDataGroup, false); //wireorder should be checked against fund   
      setFieldValid (ifds::RedCode, idDataGroup, false);
      setFieldValid (ifds::AmtType, idDataGroup, false);
      
      //trade date lag enhancement
      DString effectiveDate, tradeInDate;

	  if(isXferInDateActive(idDataGroup))
	  {  
			getField (ifds::TradeInDate, tradeInDate, idDataGroup, false );
			validateDate (DATE_VALIDATION::DEFAULT_TRADE_DATE, ifds::TradeInDate, tradeInDate, idDataGroup);
	  }
	  else
	  {
		  	getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false );
			validateDate (DATE_VALIDATION::DEFAULT_TRADE_DATE, ifds::EffectiveDate, effectiveDate, idDataGroup);
	  }

      clearROAAmount (idDataGroup);
//reset the EUSD field
      setFieldNoValidate (ifds::OverrideCost, I_("N"), idDataGroup, true);
      setFieldNoValidate (ifds::OverrideTIS, I_("N"), idDataGroup, true);
//give the green light for refreshing splits and allocations...
      _bShouldRefreshSplitCommissions = true;
      refreshSplitCommissions (idDataGroup);
      SplitCommissionList *pSplitCommissionList = NULL;
      getSplitCommissionList(pSplitCommissionList, idDataGroup, false, false);
      DString feeRate;
      if(pSplitCommissionList)
      {
         pSplitCommissionList->getField(ifds::Rate, feeRate, idDataGroup);	
      }

      TransFeeList *pTransFeeList = NULL;
      DString strKey = I_("TransFeeList");

      pTransFeeList = dynamic_cast <TransFeeList *> (getObject (strKey, idDataGroup));
      if ( //pTrade->getTransFeeList (pTransFeeList, idDataGroup, false) <= WARNING &&
            pTransFeeList)
      {
         pTransFeeList->setForcingRefresh(true);
         pTransFeeList->onNotify (FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_("ForceRefresh")); 
      }

      updateGuaranteeFeeOverride (idDataGroup);

      // move from trade CBO
      //PET 212427 FN 01 - Project Thunder  
      //Default the source of fund for pending trade if the value is specified in ‘ApplySrcofFund’ field. 
      //If the default is available, user cannot override it. 
      FundToList fundToList (*this);
      DString fromFundCode, fromClassCode;

      getField (ifds::FromFund, fromFundCode, idDataGroup, false);
      getField (ifds::FromClass, fromClassCode, idDataGroup, false);

      DString dstrApplySrcOfFund = fundToList.getApplySrcOfFund (fromFundCode, fromClassCode, fundCode, classCode);
      //bool bApplySrcOfFund = !dstrApplySrcOfFund.empty() && (dstrApplySrcOfFund  != SOURCE_OF_FUND::TRANSITION);
      bool bApplySrcOfFund = !dstrApplySrcOfFund.empty();

      if( bApplySrcOfFund ) {
         setFieldNoValidate(ifds::SrcOfFund, dstrApplySrcOfFund, idDataGroup, false, false, false);
      } else {
         setFieldNoValidate(ifds::SrcOfFund, NULL_STRING, idDataGroup, false, false, false);
      }
      setFieldReadOnly (ifds::SrcOfFund, idDataGroup, bApplySrcOfFund);
      //setFieldNoValidate(ifds::SrcOfFund, dstrApplySrcOfFund, idDataGroup, false, false, false);
      //setFieldReadOnly (ifds::SrcOfFund, idDataGroup, bApplySrcOfFund);

	  DString orderType;
	  getField(ifds::OrderType,orderType,idDataGroup,false);
	  if (orderType == I_("Y"))
	  {
		  DString settleDate,settleInDate;
		  getField (ifds::SettleDate, settleDate, idDataGroup, false);
		  getField (ifds::SettleInDate, settleInDate, idDataGroup, false);

		  validateDate (DATE_VALIDATION::SETTLE_DATE, ifds::SettleDate, settleDate, idDataGroup);
		  setFieldValid (ifds::SettleDate, idDataGroup, false); 

		  validateDate (DATE_VALIDATION::SETTLE_DATE, ifds::SettleInDate, settleInDate, idDataGroup);
		  setFieldValid (ifds::SettleInDate, idDataGroup, false); 

	  }
	  tradeInDateRelatedChanges (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateCurrency ( const DString &currency,
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateCurrency" ));

   DString accountTo;

   getField (ifds::AccountTo, accountTo, idDataGroup, false );
   if (validateCurrencyTaxType (accountTo, currency, idDataGroup) <= WARNING)
   {
      DString fundCode,
         classCode;

      getField (ifds::ToFund, fundCode, idDataGroup );
      getField (ifds::ToClass, classCode, idDataGroup );
      if (!fundCode.empty() && !classCode.empty())
      {
         DString fundCurrency;

//get the fund currency
         getFundField (fundCode, classCode, ifds::Currency, fundCurrency);
         if (fundCurrency != currency)
         {
            //currency must be to fund currency for transfer and exchange
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_SETTLE_CURRENCY);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************        
SEVERITY Transfer::amsFundClassTradeMinAmtCheck ( const DString &transType,
                                                  const DString &accountNum,
                                                  const DString &fundCode, 
                                                  const DString &classCode,
                                                  const DString &amtType, 
                                                  const DString &amount, 
                                                  const DString &currency, 
                                                  const DString &exchRate, 
                                                  const DString &effectiveDate, 
                                                  const DString &broker,
                                                  const DString &branch,
                                                  const DString &slsrep,
                                                  const DString &depositType, //in1419539
                                                  //ams   
                                                  const DString &amsCode,
                                                  AmsMstrInfo *pAMSMstrInfo,
                                                  const DString &taxJuris,
                                                  const DString &provResid,
                                                  const DString &accountType,
                                                  const DString &taxType,
                                                  const DString &acctDesign,
                                                  bool &bOverrideFundLevelCheck,
                                                  const BFDataGroupId &idDataGroup,
                                                  bool bFullExchPrntToPrnt)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("amsFundClassTradeMinAmtCheck"));

//this applies for both transfers/exchanges
   TradeMinAmtCheck tradeMinAmtCheck (*this);
   DString initPurch;
  
   if ( tradeMinAmtCheck.init ( accountNum, 
                                fundCode, 
                                classCode, 
                                transType,
                                amtType,
                                amount, 
                                effectiveDate, 
                                currency, 
                                exchRate, 
                                broker,
                                branch,
                                slsrep,
                                amsCode, 
                                I_("RB"),
                                depositType, //in1419539 //in1337808
                                NULL_STRING,
                                true, 
                                bFullExchPrntToPrnt) <= WARNING) 
   {         
      tradeMinAmtCheck.getField (ifds::InitPurch, initPurch, idDataGroup);
      setField (ifds::InitPurch, initPurch, idDataGroup, false);
   }
   if (isAMSLimitationCheckRequired (accountNum, idDataGroup)) 
   {
      pAMSMstrInfo->minPurchase ( taxJuris, 
                                  provResid, 
                                  accountType, 
                                  taxType, 
                                  acctDesign, 
                                  amount, 
                                  bOverrideFundLevelCheck, 
                                  initPurch == Y,
                                  idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Transfer::isBrokerAllowed ( const DString &transType,
                                 const DString &accountNum,
                                 const DString &fundCode, 
                                 const DString &classCode,
                                 const BFDataGroupId &idDataGroup)
{
//allows for special processing at class level
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isBrokerAllowed"));
   bool bCallOverride = true;
   bool bOverride (false);
   bool bErrorSeverity (true);

   if (transType == TRADETYPE::TRANSFER_IN) //the funds and acct sent in are the 'to' side
   {
      //call the entity override only if is a transfer in kind - read the from fund
      DString fromFund,
         fromClass;

      getField (ifds::FromFund, fromFund, idDataGroup, false);
      getField (ifds::FromClass, fromClass, idDataGroup, false);
      
      bool bInKindTransfer = false;

      bCallOverride =  
         isTransferInKind ( fromFund, 
                            fromClass, 
                            fundCode, 
                            classCode, 
                            idDataGroup, 
                            bInKindTransfer) <= WARNING &&
                            bInKindTransfer;
   }
   if (bCallOverride)
   {
      checkEntityOverride ( transType, 
                            fundCode, 
                            classCode, 
                            accountNum, 
                            bOverride, 
                            bErrorSeverity, 
                            idDataGroup);
   }
   return bOverride;
}

//***********************************************************************************
SEVERITY Transfer::validateMinFromFundAmount ( const DString &accountNum,
                                               const DString &fundCode,
                                               const DString &classCode,
                                               const DString &amtType,
                                               const DString &amount,
                                               const DString &broker,
                                               const DString &branch,
                                               const DString &slsrep,
                                               const DString &depositType, //in1419539
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMinFromFundAmount"));
   DString currency, initPurch, tradeDate;

   getField (ifds::FromCurrency, currency, idDataGroup);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);

   DString dstrFromFund, dstrFromClass;
   bool isFullExchgParentToParent = false;

   getField(ifds::FromFund, dstrFromFund, idDataGroup);
   getField(ifds::FromClass, dstrFromClass, idDataGroup);
   isFullExchgParentToParent = isFullExchgParentFndClsToParentFndCls(idDataGroup, dstrFromFund, dstrFromClass, fundCode, classCode);

   fundClassTradeMinimumAmtCheck ( TRADETYPE::TRANSFER_OUT,
                                   accountNum,
                                   fundCode,
                                   classCode,
                                   amtType,
                                   amount,
                                   currency,
                                   initPurch,
                                   broker,
                                   branch,
                                   slsrep,
                                   depositType, //in1419539
								   tradeDate,
                                   idDataGroup,
                                   isFullExchgParentToParent);
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY Transfer::validateMinToFundAmount ( const DString &accountNum,
                                             const DString &fundCode,
                                             const DString &classCode,
                                             const DString &amtType,
                                             const DString &amount,
                                             const DString &broker,
                                             const DString &branch,
                                             const DString &slsrep,
                                             const DString &depositType, //in1419539
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMinToFundAmount"));
   
   DString currency,
      initPurch,tradeDate;
//the 'to side'
   getField (ifds::FromCurrency, currency, idDataGroup);
   getField (ifds::TradeInDate, tradeDate, idDataGroup, false);

   bool bOverrideFundLevelCheck = false;
//first check ams
   amsMinAmtCheck ( TRADETYPE::TRANSFER_IN,
                    accountNum,
                    fundCode, 
                    classCode,
                    amtType, 
                    amount, 
                    currency, 
                    broker,
                    branch,
                    slsrep,
                    depositType, //in1419539
                    bOverrideFundLevelCheck,
					tradeDate,
                    idDataGroup);

   if (!bOverrideFundLevelCheck && GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      double dec_amount = DSTCommonFunctions::convertToDouble (amount);
      DString dstrFromFund, dstrFromClass;
      bool isFullExchgParentToParent = false;

      getField(ifds::FromFund, dstrFromFund, idDataGroup);
      getField(ifds::FromClass, dstrFromClass, idDataGroup);
      isFullExchgParentToParent = isFullExchgParentFndClsToParentFndCls(idDataGroup, dstrFromFund, dstrFromClass, fundCode, classCode);

      if (dec_amount != 0)
      {
         fundClassTradeMinimumAmtCheck ( TRADETYPE::TRANSFER_IN,
                                         accountNum,
                                         fundCode,
                                         classCode,
                                         amtType,
                                         amount,
                                         currency,
                                         initPurch,
                                         broker,
                                         branch,
                                         slsrep,
                                         depositType, //in1419539
										 tradeDate,
                                         idDataGroup,
                                         isFullExchgParentToParent);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Transfer::validateOrderType ( const DString &orderType,
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateOrderType"));

   if (isParticipantTransfer (idDataGroup) && orderType == N) //direct
   {
      getErrMsg ( IFASTERR::ORDERTYPE_WIRE,
                  CND::ERR_ORDERTYPE_WIRE, 
                  CND::WARN_ORDERTYPE_WIRE, 
                  idDataGroup);
   }
   else if (isRealignmentTransfer (idDataGroup) && orderType == Y) //wire
   {
      getErrMsg ( IFASTERR::ORDERTYPE_DIRECT,
                  CND::ERR_ORDERTYPE_DIRECT, 
                  CND::WARN_ORDERTYPE_DIRECT, 
                  idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
} 

//******************************************************************************
SEVERITY Transfer::validateAmountAmtType (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmountAmtType"));
   if (Trade::validateAmountAmtType (idDataGroup) <= WARNING)
   {
      DString amount,
         amtType;


      getField (ifds::Amount, amount, idDataGroup, false);
      getField (ifds::AmtType, amtType, idDataGroup, false);

      double dec_amount = DSTCommonFunctions::convertToDouble (amount);

      // same with validation in TRANSUPD.P in iFast/base
      if (dec_amount == 0) //full transfer
      {
         // TRANSFR11.P accepts these amttypes pts 10033507
         if (!DSTCommonFunctions::codeInList (amtType, I_("D,F,T,M,X,Y")))
         {
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMTTYPE_FOR_FULL_TRANSFER);
         }
         else
         {
            ADDCONDITIONFROMFILE (CND::ERR_FULL_EXCHANGE_INDICATED); //give people a warning sign
//this will dirty the allocations
//fix for incident 666813 - cycle crash - dsk does not send the allocations over to the back-end.
            if (hasAllocations (idDataGroup))
            {
               TradeAcctAllocList *pAccountAllocationList = NULL;

               if ( getAccountAllocationList ( pAccountAllocationList, 
                                               idDataGroup, 
                                               //don't create it here, if not already created
                                               false ) <= WARNING &&
                   pAccountAllocationList)
               {
                  BFObjIter iterActAlloc (*pAccountAllocationList, idDataGroup);

                  while (!iterActAlloc.end())
                  {
//this is the only item...
                     TradeAcctAlloc *pTradeAcctAlloc =  
                           dynamic_cast <TradeAcctAlloc*> (iterActAlloc.getObject());
                     
                     if (pTradeAcctAlloc)
                     {
                        pTradeAcctAlloc->setNonDummyFlag();
                     }
                     ++iterActAlloc;
                  }
               }
            }
         }
      }
      if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         DString fromFund,
            fromClass,
            toFund,
            toClass;

         getField (ifds::FromFund, fromFund, idDataGroup);
         getField (ifds::FromClass, fromClass, idDataGroup);
         getField (ifds::ToFund, toFund, idDataGroup);
         getField (ifds::ToClass, toClass, idDataGroup);
         if ( !fromFund.empty() && 
              !fromClass.empty() &&
              !toFund.empty() && 
              !toClass.empty())
         {
            FundToList fundToList( *this );
            DString allowFullPartial;

            if (fundToList.isTransferAllowed ( fromFund, 
                                               fromClass, 
                                               toFund, 
                                               toClass, 
                                               allowFullPartial))
            {
//check if this allowed based on the from/to fund combination
               // 0 - allow both, 1 - allow Partial only, 2 - allow Full only
               if (allowFullPartial == I_("1") && dec_amount == 0) // Partial allowed only
               {
                  ADDCONDITIONFROMFILE (CND::ERR_FULL_TRANSFER_NOT_ALLOWED);
               }
               if (allowFullPartial == I_("2") && dec_amount != 0)// Full allowed only
               {
                  ADDCONDITIONFROMFILE (CND::ERR_PARTIAL_TRANSFER_NOT_ALLOWED);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::validateAmtType ( const DString &amtType,
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateAmtType" ));

   if (Trade::validateAmtType (amtType, idDataGroup) <= WARNING)
   {     
      if (amtType == I_("P") && hasAllocations (idDataGroup))
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMTTYPE_FOR_INVESTMENT_ALLOCATION);
      }
      else if (amtType == I_("U"))
      {
         bool bIsMasterActWithOneChild = getWorkSession().isMasterActWithOneChild(idDataGroup);
         if (bIsMasterActWithOneChild)
         {
            validateParentFundAgainstAmtType(idDataGroup);
         }
      }

      //--- From fund/class ---
      DString fundCode, classCode;
      FundDetail *pFromFundDetail = NULL;

      getField (ifds::FromFund, fundCode, idDataGroup );
      getField (ifds::FromClass, classCode, idDataGroup );

      if (!fundCode.empty() && !classCode.empty() &&
          getWorkSession().getFundDetail(fundCode, classCode, idDataGroup, pFromFundDetail) && pFromFundDetail &&
          !pFromFundDetail->isAmtTypeValidForLoadType(getWorkSession(), amtType, idDataGroup))
      { 
          DString loadType, amtTypeDesc, idiDesc, amtTypeSubList;
          BFProperties *pBFProperties = getFieldProperties(ifds::AmtType, idDataGroup);

          if (pBFProperties)
              pBFProperties->getSubstituteValues(amtTypeSubList);

          amtTypeDesc = DSTCommonFunctions::getDescription(amtType, amtTypeSubList);
          pFromFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false); 
          loadType.stripAll().upperCase();

          if (loadType == FUND_LOAD_TYPE::BACKEND_LOAD)
          {
              addIDITagValue(idiDesc, I_("AMT_TYPE"), amtTypeDesc);
              getErrMsg(IFASTERR::FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT,
                  CND::ERR_FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT,
                  CND::WARN_FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT, 
                  idDataGroup,
                  idiDesc);
          }
          else if (loadType == FUND_LOAD_TYPE::CHARGEBACK)
          {
              addIDITagValue(idiDesc, I_("AMT_TYPE"), amtTypeDesc);
              getErrMsg(IFASTERR::FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT,
                  CND::ERR_FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT,
                  CND::WARN_FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT, 
                  idDataGroup,
                  idiDesc);
          }
          else
          {
              addIDITagValue(idiDesc, I_("AMT_TYPE"), amtTypeDesc);
              getErrMsg(IFASTERR::FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT,
                  CND::ERR_FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT,
                  CND::WARN_FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT, 
                  idDataGroup,
                  idiDesc);
          }
      }

      //--- To fund/class ---
      if (DSTCommonFunctions::codeInList (amtType, I_("F,T,M,X,Y")))
      {
          DString toFund, toClass;

          getField (ifds::ToFund, toFund, idDataGroup, false);
          getField (ifds::ToClass, toClass, idDataGroup, false);
          if (!toFund.empty() && !toClass.empty())
          {   
              FundDetail *pFundDetail = NULL;

              if ( getWorkSession ().getFundDetail ( toFund, 
                  toClass, 
                  idDataGroup, 
                  pFundDetail) && 
                  pFundDetail)
              {
                  DString loadType, fundSubCat;
                  bool bIsLowLoaded = false;

                  pFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false);
                  pFundDetail->getField (ifds::FundSubCat, fundSubCat, idDataGroup, false);
                  fundSubCat.strip().upperCase();

                  bIsLowLoaded = DSTCommonFunctions::codeInList (FUND_SUB_CAT_LOW_LOADED, fundSubCat)||
                      DSTCommonFunctions::codeInList (FUND_SUB_CAT_LOW_LOADED_4, fundSubCat);

                  // only transfer from back-end-load to low-load is allowed
                  if (loadType == I_("BEL") && !bIsLowLoaded)
                  {
                      ADDCONDITIONFROMFILE (CND::ERR_NO_APPLICATBLE_FOR_TOFUND);
                  }
              }
          }
      }
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Transfer::validateEscrowTaxTypeRIFTransfer (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateEscrowTaxTypeRIFTransfer"));
   
   if (isEscrowTaxTypeRIFTransferApplicable (idDataGroup))
   {
      MFAccount *pMFAccount = NULL;
      MFAccount *pMFAccountTo = NULL;
      DString accountNum,
         accountTo;
      
      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      getField (ifds::AccountTo, accountTo, idDataGroup, false);
      if (getWorkSession().getMFAccount ( idDataGroup, 
                                          accountNum, 
                                          pMFAccount) <= WARNING &&
                                          pMFAccount &&
          getWorkSession().getMFAccount ( idDataGroup, 
                                          accountTo, 
                                          pMFAccountTo) <= WARNING &&
                                          pMFAccountTo)
      {
//rule 1 ProvReg and AcctDesignation check
         DString taxTypeFrom,
            taxTypeTo,
            pensionJurisFrom,
            pensionJurisTo,
            acctDesignation,
            acctToDesignation;
         
         pMFAccount->getField (ifds::TaxType, taxTypeFrom, idDataGroup, false);
         pMFAccountTo->getField (ifds::TaxType, taxTypeTo, idDataGroup, false);
         /* Incident #706688 -- Requirment 1) Modify the "Pension Jurisdiction must be the same"
          * validation in Transfer Entry Screen to be done only for Transfer between
          * TaxType = B(LIF), C(LIRA), L(LRIF), R(PRIF)
          */
         bool bFromLIFLike = getWorkSession ().isLIFLike (taxTypeFrom);
		 bool bToLIFLike = getWorkSession ().isLIFLike (taxTypeTo);
		 bool bFromLIRALike = getWorkSession ().isLIRALike (taxTypeFrom);
		 bool bToLIRALike = getWorkSession ().isLIRALike (taxTypeTo);

         if (( bFromLIFLike || bFromLIRALike || DSTCommonFunctions::codeInList (taxTypeFrom, I_("L,R"))) 
			 && (bToLIFLike || bToLIRALike || DSTCommonFunctions::codeInList (taxTypeTo, I_("L,R"))))
         {
            pMFAccount->getField (ifds::PensionJuris, pensionJurisFrom, idDataGroup, false);
            pMFAccount->getField (ifds::AcctDesignation, acctDesignation, idDataGroup, false);
            pMFAccountTo->getField (ifds::PensionJuris, pensionJurisTo, idDataGroup, false);
            pMFAccountTo->getField (ifds::AcctDesignation, acctToDesignation, idDataGroup, false);            

            int iAcctDesFrom = acctDesignation.asInteger(); //!!!!!!!!!!!!!! ????????????
            int iAcctDesTo = acctToDesignation.asInteger(); //!!!!!!!!!!!!!! ????????????
            
            if ( pensionJurisFrom != pensionJurisTo && 
                (iAcctDesFrom == 1 || iAcctDesFrom == 9) && //this doesn't seem right! (what's 9 as acct designation??)
                (iAcctDesTo == 1 || iAcctDesTo == 9 )       //this doesn't seem right!
               )
            {
               ADDCONDITIONFROMFILE( CND::ERR_TRANSFER_TO_PENSION_JURISDICTION_NOT_SAME);
            }
         }
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING) //rule 2
         {
            validateTransferToLIRA (idDataGroup);
            validateTransferToLRSP (idDataGroup);
         }
//rule 3 unseizable and function check
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            DString unSeizable,
               unSeizableConf,
               strFunctionId,
               strInqPerm;

            pMFAccount->getField (ifds::Unseizable, unSeizable,idDataGroup, false);         
            getWorkSession().getOption ( ifds::Unseizable, 
                                         unSeizableConf, 
                                         idDataGroup, 
                                         false 
                                       );
            if ( unSeizable == Y && 
                 unSeizableConf == Y &&
                 getWorkSession().hasReadPermission (UAF::UNSEIZABLE_ACC)
               )
            {
               ADDCONDITIONFROMFILE (CND::ERR_UNSEIZABLE_ACCOUNT_TRANSFER);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Transfer::validateTransferToLIRA (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTransferToLIRA ")
                         );

   if (isEscrowTaxTypeRIFTransferApplicable (idDataGroup))
   {
      MFAccount *pMFAccount = NULL;
      MFAccount *pMFAccountTo = NULL;
      DString accountNum,
         accountTo;
   
      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      getField (ifds::AccountTo, accountTo, idDataGroup, false);
      if (getWorkSession().getMFAccount ( idDataGroup, 
                                          accountNum, 
                                          pMFAccount) <= WARNING &&
                                          pMFAccount &&
          getWorkSession().getMFAccount ( idDataGroup, 
                                          accountTo, 
                                          pMFAccountTo) <= WARNING &&
                                          pMFAccountTo )
      {
//rule 2 PlanType == LIRA age >= 72
         DString taxTypeFrom,
            taxTypeTo, 
            planType;
   
         pMFAccount->getField (ifds::TaxType, taxTypeFrom, idDataGroup, false);
         pMFAccountTo->getField (ifds::TaxType, taxTypeTo, idDataGroup, false);

         TaxTypeRule *pTaxTypeRule = NULL;
       if ( pMFAccountTo->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
       {
            pTaxTypeRule->getField (ifds::PlanType, planType, idDataGroup);    
         }           
         if (planType == I_("LIRA"))
         {
            DString tradeDate,
               toShareholderBirthDate;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
            pMFAccountTo->getDofBirthofOwnerSeq01 (toShareholderBirthDate, idDataGroup);
            if (!tradeDate.empty() && !toShareholderBirthDate.empty())
            {
               if (getYear (tradeDate) - getYear (toShareholderBirthDate) >= 72)
               {
                  ADDCONDITIONFROMFILE (CND::ERR_TRANSFER_TO_LIRA_NOT_ALLOWED);
               }
            }
            if ( taxTypeFrom == I_("R") || //PRIF
                 taxTypeFrom == I_("K")    //External PRIF
               )   
            {
               DString fromShareholderBirthDate;

               pMFAccount->getDofBirthofOwnerSeq01 (fromShareholderBirthDate, idDataGroup);
               if (!tradeDate.empty() && !fromShareholderBirthDate.empty())
               {
                  if (getYear (tradeDate) - getYear (fromShareholderBirthDate) >= 72)
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_TRANSFER_TO_LIRA_NOT_ALLOWED_FOR_SHAREHOLDER_69);
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************************
SEVERITY Transfer::validateTransferToLRSP (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTransferToLRSP ")
                         );

   if (isEscrowTaxTypeRIFTransferApplicable (idDataGroup))
   {
      MFAccount *pMFAccount = NULL;
      MFAccount *pMFAccountTo = NULL;
      DString accountNum,
         accountTo;
   
      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      getField (ifds::AccountTo, accountTo, idDataGroup, false);
      if (getWorkSession().getMFAccount ( idDataGroup, 
                                          accountNum, 
                                          pMFAccount) <= WARNING &&
                                          pMFAccount &&
          getWorkSession().getMFAccount ( idDataGroup, 
                                          accountTo, 
                                          pMFAccountTo) <= WARNING &&
                                          pMFAccountTo )
      {
//rule 2 PlanType == LRSP age >= 72
         DString taxTypeFrom,
            taxTypeTo, 
            planType;
   
         pMFAccount->getField (ifds::TaxType, taxTypeFrom, idDataGroup, false);
         pMFAccountTo->getField (ifds::TaxType, taxTypeTo, idDataGroup, false);

         TaxTypeRule *pTaxTypeRule = NULL;
       if ( pMFAccountTo->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
       {
            pTaxTypeRule->getField (ifds::PlanType, planType, idDataGroup);    
         }           
         if (planType == I_("LRSP"))
         {
            DString tradeDate,
               toShareholderBirthDate;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
            pMFAccountTo->getDofBirthofOwnerSeq01 (toShareholderBirthDate, idDataGroup);
            if (!tradeDate.empty() && !toShareholderBirthDate.empty())
            {
               if (getYear (tradeDate) - getYear (toShareholderBirthDate) >= 72)
               {
                  ADDCONDITIONFROMFILE (CND::ERR_TRANSFER_TO_LRSP_NOT_ALLOWED);
               }
            }
            if ( taxTypeFrom == I_("R") || //PRIF
                 taxTypeFrom == I_("K")    //External PRIF
               )   
            {
               DString fromShareholderBirthDate;

               pMFAccount->getDofBirthofOwnerSeq01 (fromShareholderBirthDate, idDataGroup);
               if (!tradeDate.empty() && !fromShareholderBirthDate.empty())
               {
                  if (getYear (tradeDate) - getYear (fromShareholderBirthDate) >= 72)
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_TRANSFER_TO_LRSP_NOT_ALLOWED_FOR_SHAREHOLDER_69);
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

///********************************************************************************************
bool Transfer::isEscrowTaxTypeRIFTransferApplicable (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isEscrowTaxTypeRIFTransferApplicable"));
   return getEscrowFundClassState (idDataGroup) == 0;
}

//**********************************************************************************************
int Transfer::getEscrowFundClassState (const BFDataGroupId &idDataGroup)
{
   int iState = 0;
   DString titleRestrict;
   
   getWorkSession().getOption ( ifds::TitleRestrict, 
                                titleRestrict, 
                                idDataGroup, 
                                false);
   if (titleRestrict != Y)
   {
      DString entityType;
      AccountEntityXref *pAccountEntityXref = NULL;
      
      if ( getWorkSession().getAccountEntityXref ( idDataGroup, 
                                                   pAccountEntityXref) <= WARNING && 
           pAccountEntityXref)
      {
         DString accountTo;
         MFAccount *pMFAccount = NULL;

         getField (ifds::AccountTo, accountTo, idDataGroup, false);
         if ( !accountTo.empty() && 
              getWorkSession().getMFAccount (idDataGroup, accountTo, pMFAccount) <= WARNING && pMFAccount)
         {
            if (pAccountEntityXref->PopulateAccountOwner ( idDataGroup, 
                                                           NULL_STRING, 
                                                           accountTo, 
                                                           NULL_STRING, 
                                                           NULL_STRING ) <= WARNING )
            {
               BFObjIter iter ( *pAccountEntityXref, 
                                 idDataGroup, 
                                 true, 
                                 BFObjIter::ITERTYPE::NON_DELETED);
               DString searchKey; // build a key with accountTo, entityType, ignore sequence
               int iSeq = 1;

               while (true)
               {
                  DString dstrSeq (DString::asString (iSeq));
                  
                  iSeq++;
                  //build a key

                  DString dstrExistEscrow, 
                     dstrExistAssignee, 
                     dstrEntityType;

                  pMFAccount->getField (ifds::Escrow, dstrExistEscrow, idDataGroup, false);
                  pMFAccount->getField (ifds::ExistAssignee, dstrExistAssignee, idDataGroup, false);

                  if (dstrExistEscrow.strip ().upperCase () == Y)
                  {
                     dstrEntityType = I_("11"); // escrow representative entity type 
                  }
                  else if (dstrExistAssignee.strip ().upperCase () == Y)
                  {
                     dstrEntityType = I_("53"); // Assignee entitytype
                  }

                  AccountEntityXref::buildPartialKeyForRetrievingEntity ( searchKey, 
                                                                          accountTo, 
                                                                          dstrEntityType, //escrow representative 
                                                                          dstrSeq);
                  if (iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey))
                  {
                     if (iter.getObject() != NULL)
                     {
                        DString escrowFund,
                              escrowClass,
                              escrowDeff,
                              escrowStopDate,
                              amtAssigned,
                              fromFund, 
                              fromClass, 
                              tradeDate;

                        iter.getObject()->getField (ifds::EscrowFund, escrowFund, idDataGroup, false);
                        iter.getObject()->getField (ifds::EscrowClass, escrowClass, idDataGroup, false);
                        iter.getObject()->getField (ifds::EscrowDeff, escrowDeff, idDataGroup, false);
                        iter.getObject()->getField (ifds::EscrowStopDate, escrowStopDate, idDataGroup, false);
                        iter.getObject()->getField (ifds::AmtAssigned, amtAssigned, idDataGroup, false);                  
                        getField (ifds::FromFund, fromFund, idDataGroup, false); 
                        getField (ifds::FromClass, fromClass, idDataGroup, false); 
                        getField (ifds::EffectiveDate, tradeDate, idDataGroup, false); 

                        bool bEffectiveDate = 
                           !(DSTCommonFunctions::
                                 CompareDates (tradeDate, escrowDeff) == DSTCommonFunctions::SECOND_EARLIER) &&
                           DSTCommonFunctions::
                                 CompareDates (_currentBusinessDate, escrowStopDate) == DSTCommonFunctions::FIRST_EARLIER; 
                        double dbAmtAssigned = DSTCommonFunctions::convertToDouble (amtAssigned);
                        bool bAmtAssigned = dbAmtAssigned == 0;

                        if ( fromFund == escrowFund &&
                             fromClass == escrowClass && 
                             bAmtAssigned && 
                             bEffectiveDate)
                        {
                           iState = 3;
                           break;
                        }
                        if ( fromFund == escrowFund &&
                             escrowClass.empty() && 
                             bAmtAssigned && 
                             bEffectiveDate)
                        {
                           iState = 2;
                           break;
                        }
                        if ( escrowFund.empty() &&
                             escrowClass.empty() && 
                             bAmtAssigned && 
                             bEffectiveDate)
                        {
                           iState = 1;
                           break;
                        }
                     }
                     else
                     {
                        break;
                     }
                  } //endof  if ( iter.begin() )
                  if (iter.end())
                  {
                     break;
                  }
               }// end of while
            }
         }
      }     
   }
   return iState;
}

//******************************************************************************
SEVERITY Transfer::validateFundCodeRedCodeAmount (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundCodeRedCodeAmount"));

   DString redCode,
      amount;

   getField (ifds::RedCode, redCode, idDataGroup);
   getField (ifds::Amount, amount, idDataGroup);

   double dec_amount = DSTCommonFunctions::convertToDouble (amount);

   if ( DSTCommonFunctions::codeInList (redCode, I_("16,17")) &&
        DSTCommonFunctions::NumOfDecimals (amount) != 0)
   {
      ADDCONDITIONFROMFILE (CND::ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS);
   }
   else
   {
      DString accountNum,
         fundCode, 
         classCode;

      getField (ifds::AccountNum, accountNum, idDataGroup);
      getField (ifds::FromFund, fundCode, idDataGroup);
      getField (ifds::FromClass, classCode, idDataGroup);

      if (validateFundBalance (accountNum, fundCode, classCode, amount, idDataGroup) <= WARNING)
      {
//Close Fund Redemption
//1. If redcode = '90 - Close Fund', only unallocated trade and full redemption, transfer-out
//or exchange-out is allowed
//2. If redcode = '90 - Close Fund', only PayInterestOn flag is '03' allowed
         if (redCode == I_("90"))
         {
            if (fundCode.empty() && classCode.empty() || dec_amount != 0)
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_CLOSE_FUND_REDEMPTION);
            }
            else
            {
               //check if PayIntOn on Fund Master is set to '03' - Interest on Close Fund
               FundMasterList *pFundMasterList; 

               if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
                    pFundMasterList)
               {
                  DString dstrPayIntOn;
                  FundMaster *pFundMaster = NULL;

                  if ( pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster) &&
                       pFundMaster)
                  {
                     pFundMaster->getField (ifds::PayIntOn, dstrPayIntOn, idDataGroup, false);
                  }
                  if (dstrPayIntOn != I_("03"))
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_INVALID_INTEREST_ON_CLOSE_FUND_REDEMPTION);
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateRedCode ( const DString& redCode, 
                                     const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateRedCode" ));

   // RedCode : 08 - Death Transfer, TaxType = 1,2,3,4,5,6,7,8,C,CR
   // RedCode : 32 - Death Transfer, TaxType = B,BR,C,CR,L
   // RedCode : 33 - Death Transfer, TaxType = B,BR,C,CR,L
   // RedCode : 51 - Partial Transfer, TaxType = B,BR,C,CR,L
   // RedCode : 52 - Full Transfer, TaxType = L,B,BR,C,CR
   // RedCode : 53 - Transfer to Purchase Annuity, TaxType = L,B,BR,C,CR
   // RedCode : 57 - Qualifying Death Transfer Spouse, TaxType = 1,2,B,BR,C,CR,L
   // RedCode : 58 - Qualifying Death Transfer Child, TaxType = 1,2,B,BR,C,CR,L
   // RedCode : 59 - Qualifying Death xTransfer for successor, TaxType = B,C,CR,L
   
   DString accountTo;

   getField (ifds::AccountTo, accountTo, idDataGroup, false);

   if (!accountTo.empty ())
   {
      MFAccount *pMFAccount = NULL;

      if ( getWorkSession().getMFAccount (idDataGroup, accountTo, pMFAccount) <= WARNING && 
           pMFAccount)
      {
         DString   taxType;

         pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);

         if (redCode == I_("QU"))
         {
            if (taxType != I_("1") && taxType != I_("2"))
            {
               ADDCONDITIONFROMFILE( CND::ERR_TR_INVALID_RED_CODE );
            }
         }


      }
   }

   if (Trade::validateRedCode (redCode, idDataGroup))
   {
      DString deathRedCode;

      getWorkSession().getOption ( ifds::DeathRedCode, 
                                   deathRedCode, 
                                   idDataGroup,
                                   false);
      bool isDeathRedCode = DSTCommonFunctions::codeInList (redCode, deathRedCode);

// If RedCode is one of listed in DeathRedCode_83 and RedCode is not one of '08','57','58','59'
// issue error "redemption Code is not allowed for transfer"
// Add 34 to the list to is not a good idea and proper solution, will revise to get values from 
// redcode table by view program.
	  if ( isDeathRedCode && 
           !DSTCommonFunctions::codeInList (redCode, I_("08,34,57,58,59"))) 
      {
         getErrMsg ( IFASTERR::REDEMPTION_CODE_IS_NOT_ALLOWED, 
                     CND::ERR_REDEMPTION_CODE_IS_NOT_ALLOWED,  
                     CND::WARN_REDEMPTION_CODE_IS_NOT_ALLOWED, 
                     idDataGroup);
      }
      else if (isDeathRedCode)
      {
// If RedCode is one of Listed in DeathRedCode_83 and RedCode is one of '08','57','58','59'
// DofDeath_51 must not be blank. Issue error.
         DString accountNum;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, accountNum, idDataGroup );
         if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
              pMFAccount)
         {
            DString dstrDofDeath;

            pMFAccount->getDofDeathofOwnerSeq01 (dstrDofDeath, idDataGroup);
            dstrDofDeath.strip();
            if (dstrDofDeath.empty())
            {
               ADDCONDITIONFROMFILE (CND::ERR_ACCOUNTHOLDER_DEATH_DATE_REQUIRED);
            }

            // do checking for annuitant DOD
			dstrDofDeath = NULL_STRING; //Added for INC0033364
            pMFAccount->getDofDeathofEntityType (ENTITY_ANNUITANT,dstrDofDeath, idDataGroup);//Modified for INC0033364
            dstrDofDeath.strip();

            if( (DSTCommonFunctions::CompareDates (dstrDofDeath, I_("12319999"))== DSTCommonFunctions::EQUAL) ||
               dstrDofDeath.empty() )
            {
               DString idiStr,
                  strEntityTypeFmt(ENTITY_ANNUITANT);

               BFDataField::formatValue( ifds::EntityType, strEntityTypeFmt );
               addIDITagValue (idiStr, I_("ENTITY_TYPE"), strEntityTypeFmt);
               getErrMsg ( IFASTERR::DOD_ENTITY_TYPE_MISSING,
                           CND::ERR_DOD_ENTITY_TYPE_MISSING,
                           CND::WARN_DOD_ENTITY_TYPE_MISSING,
                           idDataGroup,
                           idiStr );
            }
         }
      }

//if RedCode is in TIKRedCode list and the trade is allocated or it is not a special exch or TIK, issue error
      DString tikRedCodes;
      getWorkSession().getOption ( ifds::TIKRedCodes, 
                                   tikRedCodes, 
                                   BF::HOST, 
                                   false);

      if (DSTCommonFunctions::codeInList (redCode, tikRedCodes) && hasAllocations (idDataGroup))
      {
         DString idiStr, 
            redCodeDesc; 

         //get red code description
         getField (ifds::RedCode, redCodeDesc, idDataGroup, true);
         addIDITagValue (idiStr, I_("RED_CODE"), redCodeDesc);
         ADDCONDITIONFROMFILEIDI (CND::ERR_RED_CODE_NOT_ALLOWED_FOR_ALLOCATED_TRADE, idiStr);
      }      

      validateRedCodeExclCodes (redCode, idDataGroup);
      validateGrossTransfer (redCode, idDataGroup);

      DString guaranteeCalcByRules;
      getWorkSession().getOption ( ifds::GuaranteeCalcByRules, 
                                   guaranteeCalcByRules, 
                                   BF::HOST, 
                                   false);      
      guaranteeCalcByRules.strip().upperCase();
      
      if( guaranteeCalcByRules == I_("Y"))
      {
         DString accountNum;
         MFAccount *pMFAccount = NULL;

         getField( ifds::AccountNum, accountNum, idDataGroup );
         if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
              pMFAccount)
         {
            DString dstrDeathClaim, 
                    dstrDeathStat,
                    dstrContractStat;

            pMFAccount->getField (ifds::DeathClaim, dstrDeathClaim, idDataGroup, false );
            pMFAccount->getField (ifds::DeathStat, dstrDeathStat, idDataGroup, false );
            dstrDeathClaim.strip().upperCase();
            dstrDeathStat.strip().upperCase();
            
            bool bFoundDeathContract = false;
            ContractInfoList* pContractInfoList = NULL;
            if( pMFAccount->getContractInfoList(pContractInfoList, idDataGroup) &&
                pContractInfoList )
            {
               DString dstrContractStatus;
               
               BFObjIter iterContractList( *pContractInfoList, idDataGroup );
               iterContractList.begin();
               while( !iterContractList.end() )
               {
                  ContractInfo *pContractInfo = dynamic_cast< ContractInfo* >( iterContractList.getObject() );
                  if(pContractInfo)
                  {
                     pContractInfo->getField(ifds::Status,dstrContractStatus, idDataGroup, false);
                     dstrContractStatus.strip().upperCase();
                     
                     if(dstrContractStatus == CONTRACT_STATUS_PENDINGDEATH)
                     {
                        bFoundDeathContract = true;
                        break;
                     }
                  }
                  ++iterContractList;
               }               
            }
            
            if(bFoundDeathContract)
            {
               if(!isDeathRedCode)
               {
                  getErrMsg ( IFASTERR::MUST_ENTER_A_DEATH_CLAIM_REDEMPTION_CODE, //229
                              CND::ERR_DEATH_CLAIM_REDEMPTION_CODE, 
                              CND::ERR_WARN_DEATH_CLAIM_REDEMPTION_CODE, 
                              idDataGroup);               
               }
            }
            
            if(isDeathRedCode && !bFoundDeathContract)
            {
               if (dstrDeathClaim == I_("N") && dstrDeathStat == I_("N") )
               {
                  getErrMsg ( IFASTERR::CONTRACT_ACCOUNT_STATUS_IS_ACTIVE, //222
                              CND::ERR_CONTRACT_ACCT_STATUS_ACTIVE, 
                              CND::ERR_WARN_CONTRACT_ACCT_STATUS_ACTIVE, 
                              idDataGroup);               
               }
            }
         }      
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateGrossTransfer (const DString &redCode, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateGrossTransfer"));

   DString grossNet;
   DString dstrAcctNumFr;
   MFAccount *pMFAccount = NULL;

   getField (ifds::GrossOrNet, grossNet, idDataGroup, false);
   getField (ifds::AccountNum, dstrAcctNumFr, idDataGroup);

   if (getWorkSession ().getMFAccount (idDataGroup, dstrAcctNumFr, pMFAccount ) <= WARNING  && pMFAccount) 
   {            
      DString taxType;

      pMFAccount->getField( ifds::TaxType, taxType, idDataGroup );

      taxType.strip().upperCase();

      TaxTypeRule *pTaxTypeRule = NULL;

      if (pMFAccount->getTaxTypeRule (pTaxTypeRule, idDataGroup) <= WARNING && pTaxTypeRule)
      {

         DString dstrMinApplies;
         RedCodeByTaxTypeList *pRedCodeList = NULL;

         pTaxTypeRule->getRedCodeList (pRedCodeList, idDataGroup);

         if (pRedCodeList)
         {
            RedCodeByTaxType *pRedCode = NULL;

            if (pRedCodeList->getRedCodeByTaxType (redCode, pRedCode, idDataGroup) && pRedCode)
            {
               pRedCode->getField (ifds::MinimumApplies, dstrMinApplies, idDataGroup, false);

               if (dstrMinApplies == YES && grossNet == GROSS)
               {
                  getErrMsg (IFASTERR::GROSS_REDEMPTION_MINIMUM_APPLIES,
                             CND::ERR_GROSS_REDEMPTION_MINIMUM_APPLIES, 
                             CND::WARN_GROSS_REDEMPTION_MINIMUM_APPLIES, 
                             idDataGroup); 
               }
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Transfer::validateRedCodeExclCodes ( const DString &redCode,
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_ ("validateRedCodeExclCodes"));
// Ticket 10012083 : if NOT All Fund Transfer, user is not allowed to choose the close account redemption code
// this method is empty in AllTransfer
   DString trExclRedCodes;

   getWorkSession ().getOption ( ifds::TRExclRedCodes, 
                                 trExclRedCodes, 
                                 BF::HOST, 
                                 false);
   if (DSTCommonFunctions::codeInList (redCode, trExclRedCodes))
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_CODE_FOR_TRANSFER);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************************
SEVERITY Transfer::validateFundBalance ( const DString &accountNum,
                                         const DString &fundCode,
                                         const DString &classCode,
                                         const DString &amount,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundBalance"));
   

   if (isTUPApplicable (idDataGroup))
		return GETCURRENTHIGHESTSEVERITY();

   if ( !fundCode.empty() && 
        !classCode.empty()) 
   {
      double dec_amount = DSTCommonFunctions::convertToDouble (amount);
      double dec_fundbalance = getFundBalance (accountNum, fundCode, classCode, idDataGroup);
      
      if (dec_amount > dec_fundbalance)
      {
         MFAccount *pMFAccount = NULL;

         if ( getAccount ( pMFAccount, idDataGroup) <= WARNING  && 
              pMFAccount) 
         {
			 if (!pMFAccount->negativeBalanceAllowed (idDataGroup, fundCode, classCode) )
             {
               DString idiStr;

               addIDITagValue (idiStr, I_("FUNDNAME"), fundCode);
               addIDITagValue (idiStr, I_("CLASSNAME"), classCode);	
               getErrMsg ( IFASTERR::TR_XR_AMOUNT_IS_GREATER_THAN_ACCOUNT_BALANCE, //401
                           CND::ERR_EX_AMT_MORE_THAN_HOLDING, 
                           CND::ERR_WARN_EX_AMT_MORE_THAN_HOLDING, 
                           idDataGroup,
                           idiStr);
			   //for UC exchanges and all transfers	if the env level error INSUFFICENT_UNITS_FOR _UC_TRANSFER_TRADES 
		       //do not allow manual trade's	//robs
				  DString dstrRedCode, dstrDepositType; 		 
				  getField (ifds::RedCode, dstrRedCode, idDataGroup, false);
				  getField (ifds::DepositType, dstrDepositType, idDataGroup, false);
                  bool isExchg = isExchange(idDataGroup) || isInterClassSwitch(idDataGroup);
				  bool bIsNotAllowed = !isExchg || //all transfers
								       (isExchg && REDEMPTION_CODE_UC == dstrRedCode && DEPOSIT_CODE_UC == dstrDepositType);//UC trades
				  if( bIsNotAllowed )
				  {
				  getErrMsg ( IFASTERR::INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES,
                              CND::ERR_INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES , 
                              CND::WARN_INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES, 
							  idDataGroup,
                              idiStr);
				  }

            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::validateIfAllocatedAtCostTIKAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateIfAllocatedAtCostTIKAllowed" ));

   //check for AtCost allocation, only if GenericControl.ACBTransferRules.logical1 (i.e. DefltRedCodeFlag) is set to Yes
   DString dstrEnableDefault;

   getWorkSession().getOption (ifds::DefltRedCodeFlag, dstrEnableDefault, BF::HOST, false);
   if (Y == dstrEnableDefault)
   {
      TradeFundAllocList *pTradeFundAllocList = NULL;

      if ( getFundAllocationList (pTradeFundAllocList, idDataGroup, false) <= WARNING &&
           pTradeFundAllocList)
      {
         BFObjIter iter (*pTradeFundAllocList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
         while (!iter.end())
         {
            TradeFundAlloc *pFundAllocation = dynamic_cast <TradeFundAlloc*> (iter.getObject());
            if (pFundAllocation)
            {
               //if it is single fund allocations it is OK  
               DString dstrPercent;
               pFundAllocation->getField (ifds::AllocPercentage, dstrPercent, idDataGroup, false);
               double dblAllocPercentage = DSTCommonFunctions::convertToDouble (dstrPercent);
               if ( fabs( dblAllocPercentage - 100 ) > .0000000001)
               {
                  DString dstrClassCode, dstrFundCode;
                  
                  pFundAllocation->getField(ifds::FundCode,  dstrFundCode,  idDataGroup, false );
                  pFundAllocation->getField(ifds::ClassCode, dstrClassCode, idDataGroup, false );

                  bool blIsAtCostTIK = false;
                  getAtCostTIKStatus( idDataGroup, 
                                      dstrFundCode, 
                                      dstrClassCode,
                                      true ,             // We have an allocation
                                      blIsAtCostTIK );   // false, we don't need the return value (if it is At Cost or not)
               }
            }
            ++iter;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************************
SEVERITY Transfer::validateAccountToRedCode (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAccountToRedCode"));

   DString accountTo,
      redCode;

   getField (ifds::AccountTo, accountTo, idDataGroup);
   accountTo.strip().stripLeading( '0' );
   getField (ifds::RedCode, redCode, idDataGroup, false);

   DString dstrTfrToDiffSH, 
      dstrCotClient, 
      dstrSpouseBenefReLn, 
      dstrDeathRedCode,
      dstrChildBenefReLn, 
      dstrAllFundsTransfers;

   getWorkSession().getOption (ifds::TfrToDiffSH, dstrTfrToDiffSH, BF::HOST, false);
   getWorkSession().getOption (ifds::SpouseBenefReLn, dstrSpouseBenefReLn, BF::HOST, false);
   getWorkSession().getOption (ifds::DeathRedCode, dstrDeathRedCode, BF::HOST, false);
   getWorkSession().getOption (ifds::ChildBenefReLn, dstrChildBenefReLn, BF::HOST, false);
   dstrTfrToDiffSH.strip().upperCase();
   dstrSpouseBenefReLn.strip();
   dstrDeathRedCode.strip();
   dstrChildBenefReLn.strip();

   if (validate27RedCodeTIK (redCode, idDataGroup) <= WARNING)
   {   
      DString dstrFromAccount, 
            dstrTaxTypeFr, 
            dstrFromAccountType, 
            dstrTaxTypeTo, 
            dstrToAccountType, 
            dstrTransferType,
            dstrAcctDesignation, 
            dstrSelfDirected, 
            dstrDeathStat, 
            dstrDeathClaim,
            dstrShrNumFr, 
            dstrShrNumTo, 
            dstrAcctDesignationTo,
            dstrLockedInFr,
            dstrLockedInTo,
            dstrSINFrom, 
            dstrSINTo;

      MFAccount *pMFAccount = NULL;

      getField (ifds::AccountNum, dstrFromAccount, idDataGroup);
      dstrFromAccount.strip().stripLeading( '0' );
      if ( getWorkSession().getMFAccount (idDataGroup, dstrFromAccount, pMFAccount) <= WARNING && 
           pMFAccount)
      {
         pMFAccount->getField( ifds::AcctType, dstrFromAccountType, idDataGroup );
         dstrFromAccountType.stripAll();

         pMFAccount->getField( ifds::TaxType, dstrTaxTypeFr, idDataGroup );
         dstrTaxTypeFr.strip().upperCase();

         pMFAccount->getField( ifds::LockedIn, dstrLockedInFr, idDataGroup );
         dstrLockedInFr.strip().upperCase();

         pMFAccount->getField( ifds::AcctDesignation, dstrAcctDesignation, idDataGroup );
         dstrAcctDesignation.strip();

         pMFAccount->getField( ifds::SelfDirected, dstrSelfDirected, idDataGroup );
         dstrSelfDirected.strip().upperCase();

         pMFAccount->getField( ifds::DeathStat, dstrDeathStat, idDataGroup );
         dstrDeathStat.strip().upperCase();

         pMFAccount->getField( ifds::DeathClaim, dstrDeathClaim, idDataGroup );
         dstrDeathClaim.strip().upperCase();

         pMFAccount->getField( ifds::ShrNum, dstrShrNumFr, idDataGroup );
         dstrShrNumFr.strip().stripLeading ('0');

         pMFAccount->getIDOfSequenced01OfEntityObject (IDS::SIN, ENTITY_ACCOUNTHOLDER, dstrSINFrom, idDataGroup);
         dstrSINFrom.strip().upperCase();

         pMFAccount = NULL;

         if ( getWorkSession().getMFAccount (idDataGroup, accountTo, pMFAccount) <= WARNING && 
              pMFAccount)
         {
            pMFAccount->getField( ifds::ShrNum, dstrShrNumTo, idDataGroup );
            dstrShrNumTo.strip().stripLeading( '0' );

            pMFAccount->getField( ifds::TaxType, dstrTaxTypeTo, idDataGroup );
            dstrTaxTypeTo.strip().upperCase();

            pMFAccount->getField( ifds::LockedIn, dstrLockedInTo, idDataGroup );
            dstrLockedInTo.strip().upperCase();


            pMFAccount->getField( ifds::AcctType, dstrToAccountType, idDataGroup );
            dstrToAccountType.stripAll();

            pMFAccount->getIDOfSequenced01OfEntityObject (IDS::SIN, ENTITY_ACCOUNTHOLDER, dstrSINTo, idDataGroup);
            dstrSINTo.strip().upperCase();
         }

         // Following logic check whether the client allow transfer from a registered account
         // to a different sharholder
         if ( !getWorkSession().isNonRegLike( dstrTaxTypeFr ) )
         {
            bool bDiffAccountOwner = dstrSINFrom != dstrSINTo;

            if( !( DSTCommonFunctions::codeInList( redCode, I_("08,57,58,59") ) ) &&
               ( dstrShrNumFr != NULL_STRING && dstrShrNumTo != NULL_STRING  )   &&
               ( dstrShrNumFr != dstrShrNumTo ) && bDiffAccountOwner )
            {
               bool bRunPerm_44 = 
                  getWorkSession().hasReadPermission (UAF::TRANSF_BETWEEN_2_RRIF_SH);
               bool bRunPerm_43 = 
                  getWorkSession().hasReadPermission (UAF::TRANS_DIFF_SH);

               // Rule 5: 
               if( (dstrTaxTypeFr == I_("2") || dstrTaxTypeFr == I_("R") ) && ( !bRunPerm_44 || dstrTfrToDiffSH == N ) )
               {
                  DString dstrTaxType = I_("RRIF");
                  if( dstrTaxTypeFr == I_("R") ) dstrTaxType = I_("PRIF");
                  DString idiStr;
                  addIDITagValue( idiStr, I_("TAXTYPE"), dstrTaxType );
                  ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_CANNOT_TRANSFER_FROM_RRIF, idiStr );
               }

               // Rule 6: 
               else if( ( dstrTaxTypeFr != I_("2") || dstrTaxTypeFr == I_("R") )&& 
                        ( ( bRunPerm_43 && dstrTfrToDiffSH == Y ) ||
                           dstrAcctDesignation != I_("1") || dstrSelfDirected == Y 
                         ) 
                      )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_WARN_TRANSFER_TO_DIFF );
               }
               /* Incident #706688 -- New RedCode 43 - LockedIn to Non Locked-In Registered and
                *                         RedCode 44 - LockedIn to Non Registed are allowed
                */
       
               if (  redCode == I_("43") &&
                     ( dstrLockedInFr == I_("N")  ||  dstrLockedInTo == I_("Y") || getWorkSession().isNonRegLike( dstrTaxTypeTo ) ) 
                  )
               {
                  // Checked with Jennifer, as long as TaxType is not "0", we can consider it as registered.
                  // So, we don't need to check PlanType.
                  
                  // RedCode 43 only allow tranfer from Locked In to non locked In Registed
                  // How to identify non locked in registed? Using PlanType_87 !!!!
                  getErrMsg ( IFASTERR::LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED,  // 944
                                    CND::ERR_LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED, 
                                    CND::WARN_LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED, 
                              idDataGroup);

               }
               if ( redCode == I_("44") && ( dstrLockedInFr != I_("Y") || !getWorkSession().isNonRegLike( dstrTaxTypeTo ) ) )
               {
                  // RedCode 44 only allow tranfer from Locked In to non Registed
                  getErrMsg ( IFASTERR::LOCKEDIN_TO_NON_REGISTED_ALLOWED,  //945
                                    CND::ERR_LOCKEDIN_TO_NON_REGISTED_ALLOWED, 
                                    CND::WARN_LOCKEDIN_TO_NON_REGISTED_ALLOWED, 
                              idDataGroup);
               }
               // Rule 7: 
               else
               {
                  ADDCONDITIONFROMFILE( CND::ERR_WARN_CANNOT_TRANSFER_TO_DIFF);
               }
            }
         }
         // Rule 10:
         if ( DSTCommonFunctions::codeInList (redCode, dstrDeathRedCode) && 
              DSTCommonFunctions::codeInList (redCode, I_("57,59")) 
            )
         {
            if( !isValidTransBeneficiary( dstrFromAccount, accountTo, I_( "Spousal" ), idDataGroup ) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_BENEF_WRONG_RELATE );
            }
         }

         // Rule 11:
         if( DSTCommonFunctions::codeInList( redCode, dstrDeathRedCode) && redCode == I_("58") )
         {
            if( !isValidTransBeneficiary( dstrFromAccount, accountTo, I_( "Child" ), idDataGroup ) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_BENEF_WRONG_RELATE );
            }
         }

         // Rule 12:
         if( DSTCommonFunctions::codeInList( redCode, dstrDeathRedCode)
            && redCode == I_("08") )
         {
            if( isValidBeneficiary( dstrFromAccount, accountTo, idDataGroup ) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_BENEF_WRONG_RELATE );
            }
         }

         // Rule 13:
         if( DSTCommonFunctions::codeInList( redCode, I_( "08,57,58" ) ) && 
             DSTCommonFunctions::codeInList( redCode, dstrDeathRedCode) && 
             !(DSTCommonFunctions::codeInList( dstrTaxTypeFr, I_("1,2") )&& 
               DSTCommonFunctions::codeInList( dstrTaxTypeTo, I_("1,2"))))
         {

            getErrMsg ( IFASTERR::CAN_TRANSFER_ONLY_TO_RRSP_RRIF,    
                        CND::ERR_CAN_TRANSFER_ONLY_TO_RRSP_RRIF,  
                        CND::WARN_CAN_TRANSFER_ONLY_TO_RRSP_RRIF, 
                        idDataGroup);

         }
         // Rule 14:
         if( redCode == I_("59")
            && DSTCommonFunctions::codeInList( redCode, dstrDeathRedCode)
            && ( dstrTaxTypeFr == I_("2") || dstrTaxTypeFr == I_("R") )  
         )
         {
            if( dstrTaxTypeTo != I_("2") || dstrTaxTypeTo != I_("R") )
            {
               ADDCONDITIONFROMFILE( CND::ERR_CAN_TRANSFER_ONLY_TO_RRIF );
            }
         }


         /* 1151000 - Remove this code block as suggested by Winnie 
         
		   // Ticket 10023617, applicable to Transfers and All Funds Transfers, as per TRANSFV2.P
		   // Exchanges will be excluded because From Account Type will be same with To Account Type
		   if ( !DSTCommonFunctions::codeInList( redCode, dstrDeathRedCode ) &&
			   ( ( dstrFromAccountType == I_( "0" ) && dstrToAccountType == I_( "1" ) ) ||
				   ( dstrFromAccountType == I_( "1" ) && dstrToAccountType == I_( "0" ) ) ) )
		   {					
			   TaxTypeRule *pFromTaxTypeRule = NULL;      
			   TaxTypeRule *pToTaxTypeRule = NULL;
			   if ( getTaxTypeRule( pFromTaxTypeRule, dstrTaxTypeFr, idDataGroup ) <= WARNING &&
				   NULL != pFromTaxTypeRule &&
				   getTaxTypeRule( pToTaxTypeRule, dstrTaxTypeTo, idDataGroup ) <= WARNING &&
				   NULL != pToTaxTypeRule )
			   {      
				   DString dstrFromPlanType, dstrFromSelfDirected, dstrToPlanType, dstrToSelfDirected;
				   pFromTaxTypeRule->getField( ifds::PlanType,     dstrFromPlanType,     idDataGroup );
				   pFromTaxTypeRule->getField( ifds::SelfDirected, dstrFromSelfDirected, idDataGroup );

				   pToTaxTypeRule->getField( ifds::PlanType,     dstrToPlanType,     idDataGroup );
				   pToTaxTypeRule->getField( ifds::SelfDirected, dstrToSelfDirected, idDataGroup );
         
				   dstrFromPlanType.stripAll().upperCase();
				   dstrFromSelfDirected.stripAll();
				   dstrToPlanType.stripAll().upperCase();
				   dstrToSelfDirected.stripAll();
               	DString dstrDepositType;
               getField(ifds::DepositType,dstrDepositType,idDataGroup);
				   if ( ( dstrFromPlanType == I_( "RSP" ) && dstrFromSelfDirected == I_( "N" ) ) &&
					   ( dstrToPlanType   == I_( "RSP" ) && dstrToSelfDirected   == I_( "N" ) )  &&
					   !(redCode == I_("30") && dstrDepositType ==I_("4")) )
				   {
					   ADDCONDITIONFROMFILE( CND::ERR_TRANSFER_BETWEEN_RRSP_INDIV_AND_RRSP_SPOUSAL_NOT_ALLOWED );				
				   }
			   }
		   }*/
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validate27RedCodeTIK ( const DString &redCode, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateRedCodeInKindTrans" ));
   DString tikRedCodes, dstrDeathRedCode;

   getWorkSession().getOption ( ifds::TIKRedCodes, 
                                tikRedCodes, 
                                idDataGroup, 
                                false);
   getWorkSession().getOption (	ifds::DeathRedCode, 
								dstrDeathRedCode, 
								BF::HOST, 
								false);

   if ( redCode == I_( "27" ) && 
        DSTCommonFunctions::codeInList (redCode, tikRedCodes))
   {
      DString dstrAcctNumFr, 
         dstrAcctNumTo;

      getField (ifds::AccountNum, dstrAcctNumFr, idDataGroup);
      getField (ifds::AccountTo, dstrAcctNumTo, idDataGroup);
      MFAccount *pMFAccount = NULL,
         *pMFAccountTo = NULL;

      if ( getWorkSession().getMFAccount (idDataGroup, dstrAcctNumFr, pMFAccount) <= WARNING && 
           pMFAccount &&
           getWorkSession().getMFAccount (idDataGroup, dstrAcctNumTo, pMFAccountTo) <= WARNING && 
           pMFAccountTo)
      {
         DString dstrAcctDesignationFr, 
            dstrAcctDesignationTo, 
            dstrAcctTypeFr, 
            dstrAcctTypeTo, 
            dstrPlanTypeFr, 
            dstrPlanTypeTo;

         pMFAccount->getField (ifds::AcctDesignation, dstrAcctDesignationFr, idDataGroup);
         dstrAcctDesignationFr.strip();
         pMFAccount->getField (ifds::AcctType, dstrAcctTypeFr, idDataGroup);
         dstrAcctTypeFr.strip();
         pMFAccount->getField (ifds::PlanType, dstrPlanTypeFr, idDataGroup);
         dstrPlanTypeFr.strip().upperCase();
         pMFAccountTo->getField (ifds::AcctDesignation, dstrAcctDesignationTo, idDataGroup);
         dstrAcctDesignationTo.strip();
         pMFAccountTo->getField (ifds::AcctType, dstrAcctTypeTo, idDataGroup);
         dstrAcctTypeTo.strip();
         pMFAccountTo->getField (ifds::PlanType, dstrPlanTypeTo, idDataGroup);
         dstrPlanTypeTo.strip().upperCase();

         if ( !(dstrAcctDesignationFr == dstrAcctDesignationTo && dstrAcctDesignationFr == I_( "2" )) && 
              !(dstrAcctDesignationFr == dstrAcctDesignationTo && dstrAcctDesignationFr == I_( "3" )))
         {
            if (dstrAcctNumFr == dstrAcctNumTo)
            {
               ADDCONDITIONFROMFILE (CND::ERR_ACCT_DESIGNATION_MUST_SAME_IN_KIND_TRANS);
            }
         }
         if (dstrAcctTypeFr != dstrAcctTypeTo)
         {
            ADDCONDITIONFROMFILE (CND::ERR_ACCT_TYPE_MUST_SAME_IN_KIND_TRANS);
         }
         if (dstrPlanTypeFr != dstrPlanTypeTo)
         {
            ADDCONDITIONFROMFILE (CND::ERR_PLAN_TYPE_MUST_SAME_IN_KIND_TRANS);
         }
         if (!isSameAccountOwner (idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_ACCT_OWNER_MUST_SAME_IN_KIND_TRANS);
         }
      }
   } // end of if( redCode == I_( "27" )
   else if (DSTCommonFunctions::codeInList (redCode, tikRedCodes) && 
	   !DSTCommonFunctions::codeInList(redCode, dstrDeathRedCode))
   {
      ADDCONDITIONFROMFILE (CND::ERR_WARN_IN_KIND_TRANS_ACB);
      // Incident 621359
      ////////validateTIKRedCodes (redCode, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateTIKRedCodes ( const DString &redCode,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateRedCodeInKindTrans" ));
// empty implementations in Exchange/AllTransfer 
// although in all transfers the account num/to can be different
   if (!isSameAccountOwner (idDataGroup))
   {
      ADDCONDITIONFROMFILE (CND::ERR_ACCT_OWNER_MUST_SAME_IN_KIND_TRANS);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::getAtCostTIKStatus ( const BFDataGroupId& idDataGroup, 
                                        const DString& dstrFundCodeIn, 
                                        const DString& dstrClassCodeIn,
                                        bool  blInAllocation,
                                        bool &blIsAtCostTIK)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "getAtCostTIKStatus" ) );
   
   bool blAtCostTIKAllowed = true;

// TIK functionality, same with TRANSTIK.P as of June 12, 2003
   DString dstrFromFund, 
      dstrToFund (dstrFundCodeIn), 
      dstrFromClass, 
      dstrToClass (dstrClassCodeIn);

   getField( ifds::FromFund,  dstrFromFund,  idDataGroup, false);
   if( dstrToFund.strip().upperCase().empty())
      getField( ifds::ToFund,    dstrToFund,    idDataGroup, false);
   getField( ifds::FromClass, dstrFromClass, idDataGroup, false);
   if( dstrToClass.strip().upperCase().empty() )
      getField( ifds::ToClass,   dstrToClass,   idDataGroup, false);

   if( !dstrFromFund.strip().upperCase().empty() &&
       !dstrToFund.strip().upperCase().empty()   && 
       !dstrFromClass.strip().upperCase().empty()&& 
       !dstrToClass.strip().upperCase().empty() )
   {   
      DString dstrFromAccount, 
         dstrToAccount;

      getField( ifds::AccountNum, dstrFromAccount, idDataGroup );
      getField( ifds::AccountTo,  dstrToAccount, idDataGroup );

      MFAccount *pMFAccountFrom = NULL, 
            *pMFAccountTo = NULL;

      if( getWorkSession().getMFAccount (idDataGroup, dstrFromAccount, pMFAccountFrom ) <= WARNING && 
          pMFAccountFrom &&
          getWorkSession().getMFAccount (idDataGroup, dstrToAccount, pMFAccountTo ) <= WARNING && 
          pMFAccountTo )
      { 
         DString shrNumTo,
            shrNumFrom;
         Shareholder *pShareholderFrom = NULL,
            *pShareholderTo = NULL;

         pMFAccountFrom->getField (ifds::ShrNum, shrNumFrom, idDataGroup, false);
         pMFAccountTo->getField (ifds::ShrNum, shrNumTo, idDataGroup, false);
         if ( getWorkSession ().getShareholder (idDataGroup, shrNumFrom, pShareholderFrom) <= WARNING &&
              pShareholderFrom &&
              getWorkSession ().getShareholder (idDataGroup, shrNumTo, pShareholderTo) <= WARNING &&
              pShareholderTo) 
         {
            DString dstrFromGroup,
               dstrToGroup;
            
            pShareholderFrom->getField (ifds::GroupCode, dstrFromGroup, idDataGroup, false);
            pShareholderTo->getField (ifds::GroupCode, dstrToGroup, idDataGroup, false);
            if ( 0 != dstrFromGroup.stripAll().length() &&
                 0 != dstrToGroup.stripAll().length()   &&
                 dstrFromGroup.stripAll() == dstrToGroup.strip() &&
                 dstrFromFund.stripAll()  == dstrToFund.stripAll() &&
                 dstrFromClass.stripAll() == dstrToClass.stripAll() &&
                 isSameAccountOwner (idDataGroup))
            {
// check if same taxtype
               DString dstrTaxTypeFrom, 
                  dstrTaxTypeTo;

               pMFAccountFrom->getField (ifds::TaxType, dstrTaxTypeFrom, idDataGroup);
                 pMFAccountTo->getField (ifds::TaxType,   dstrTaxTypeTo,   idDataGroup);
               // Tax Types must be the same and of type RSP(1,3,4) or RIF(2,5,6) or LIRA(C,H) or
               // LIF(B,G) or LRIF(I,L) or RESP(9,F,M,N) or RPP(8,P) or ESOP(D,E) or 
               // PRIF(R,K) or Non-Reg (0)
               if ( dstrTaxTypeFrom.stripAll() == dstrTaxTypeTo.stripAll() &&
                     ( dstrTaxTypeFrom.stripAll() != I_( "7" ) ||   // RRSP Plan
                       dstrTaxTypeFrom.stripAll() != I_( "A" ) ||   // Quebec RHOSP   
                       dstrTaxTypeFrom.stripAll() != I_( "T" ) ||   // Taxable
                       dstrTaxTypeFrom.stripAll() != I_( "W" ) ||   // Switch Plan
                       dstrTaxTypeFrom.stripAll() != I_( "X" ) ) )  // Tax Exempt 
               {
                  if ( blInAllocation )
                  {
                     blAtCostTIKAllowed = false;
                  }
                  else
                  {
                     blIsAtCostTIK = true;
                  }
               }
            }
            else if ( 0 != dstrFromGroup.stripAll().length()              &&
                      0 != dstrToGroup.stripAll().length()                &&
                      dstrFromGroup.strip()    == dstrToGroup.strip()     &&
                      dstrFromFund.stripAll()  == dstrToFund.stripAll()   &&
                      dstrFromClass.stripAll() == dstrToClass.stripAll()  )
            {
               if (blInAllocation)
               {
                  blAtCostTIKAllowed = false;
               }
            }
         }
      }
      else    // is exchange
      {      
         if ( dstrFromFund.stripAll()  == dstrToFund.stripAll() )
         {
            DString dstrFromLoad, 
               dstrToLoad;
            FundDetail *pFundDetail = NULL;

            if (getWorkSession().getFundDetail (
                  dstrFromFund, dstrFromClass, idDataGroup, pFundDetail) && 
                  pFundDetail)
            {  
               pFundDetail->getField(ifds::LoadType, dstrFromLoad, BF::HOST, false);
            }

            pFundDetail=NULL;
            if( getWorkSession().getFundDetail (
                  dstrToFund, dstrToClass, idDataGroup, pFundDetail) && 
                  pFundDetail )
            { 
               pFundDetail->getField(ifds::LoadType, dstrToLoad, BF::HOST, false);
            }
            if( dstrFromLoad.strip().upperCase() == dstrToLoad.strip().upperCase() )
            {
                  if ( blInAllocation )
                     blAtCostTIKAllowed = false;
                  else
                     blIsAtCostTIK = true; 
            }
         }
      }   
   }
   if (!blAtCostTIKAllowed)
   {
      ADDCONDITIONFROMFILE (CND::ERR_AT_COST_ALLOCATION_NOT_ALLOWED);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateDepositType ( const DString &depositType,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateDepositType"));

   if (Trade::validateDepositType (depositType, idDataGroup) <= WARNING)
   {
      MFAccount *pMFAccountTo = NULL;
   
      if ( getAccount (pMFAccountTo, idDataGroup) <= WARNING && 
           pMFAccountTo)
      {
         DString effectiveDate,
                 taxTypeTo;

         getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
         pMFAccountTo->getField (ifds::TaxType, taxTypeTo, idDataGroup);
         taxTypeTo.upperCase();  

   // Rule 3:
         TaxTypeRule *pTaxTypeRule = NULL;
       if ( pMFAccountTo->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
       {
            DString depositTypeList;

            pTaxTypeRule->getField (ifds::DepositTypeList, depositTypeList, idDataGroup);
            if (!DSTCommonFunctions::codeInList (depositType, depositTypeList, true))
            {
               ADDCONDITIONFROMFILE (CND::ERR_DEPOSIT_TYPE_INVALID_FOR_TAXTYPE);
            }
         }

   // Rule 4:
         DString dofBirth;

         pMFAccountTo->getDofBirthofOwnerSeq01 (dofBirth, idDataGroup);
         if (depositType == I_("57") && dofBirth.empty())
         {
            ADDCONDITIONFROMFILE (CND::ERR_ANNITANT_BIRTHDAY_NOT_FOUND);
         }

   // Rule 5:
         DString dofDeath;

         pMFAccountTo->getDofDeathofOwnerSeq01 (dofDeath, idDataGroup);
         if ( depositType == I_("57") && 
              dofDeath.empty() && 
              !dofBirth.empty() && 
              !effectiveDate.empty()
            )
         {
            if (getYear (effectiveDate ) - getYear (dofBirth) > 71)
            {
               ADDCONDITIONFROMFILE (CND::ERR_ANNUITANT_OLDER_THAN_69);
            }
         }

   // Rule 6:
         if (depositType == I_("57") && !dofDeath.empty())
         {
            ADDCONDITIONFROMFILE (CND::ERR_SHAREHOLDER_DECEASED);
         }

   // Rule 7:
         DString accountNum;

         getField (ifds::AccountNum, accountNum, idDataGroup);
         MFAccount *pMFAccount = NULL;
         DString taxTypeFrom;

         if ( getWorkSession().getMFAccount ( idDataGroup, 
                                              accountNum, 
                                              pMFAccount
                                            ) <= WARNING && 
              pMFAccount)
         {
            pMFAccount->getField (ifds::TaxType, taxTypeFrom, idDataGroup);
            taxTypeFrom.upperCase();
            if (depositType == I_("57") && !getWorkSession().isNonRegLike( taxTypeFrom ) ) // non-registered account
            {
               ADDCONDITIONFROMFILE (CND::ERR_LLP_REPAYMENT_UNALLOWED);
            }
   // Rule 10:
/* removed with GAP 63 - AIM
            if ( depositType == I_("7") &&
                 ( taxTypeFrom != I_("2") ||  //RRIF
                   taxTypeFrom != I_("R")))     //PRIF
            {
               ADDCONDITIONFROMFILE (CND::ERR_DEPOSIT_TYPE_07_MUST_BEUSED_RIF);
            }
*/
         } // if ( sevRtn <= WARNING && pMFAccountFr != NULL )
      } // if ( sevRtn <= WARNING && pMFAccountTo != NULL )

   // Rule 8:
      if (depositType == I_("57"))
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_LLP_REPAYMENT_PREVENT);
      }

   // Rule 9:
      DString redCode;
   
      getField (ifds::RedCode, redCode, idDataGroup, false);
      if (DSTCommonFunctions::codeInList (redCode, I_("08,57,58,59")))
      {
         if (depositType != I_("6") && depositType != I_("7"))
         {
            ADDCONDITIONFROMFILE (CND::ERR_DEPOSIT_TYPE_MUST_BE_06_OR_07);
         }
      }

      /* Incident #706688 
       *  New RedCode 43 - LockedIn to Non Locked-In Registered, DepositType should be 4 
       *      RedCode 44 - LockedIn to Non Registed are allowed, DepositType should be 1
       */
      if ( redCode == I_("43") && depositType != I_("4") )
      {
         // Deposit type must be %DEPOSITTYPE% for RedCode %REDCODE%
         DString idiStr;
         //DString dstrDepositCode = I_("4");
         //DString dstrRedCode = I_("43");

         addIDITagValue (idiStr, I_("DEPOSITTYPE"), I_("4"));
         addIDITagValue (idiStr, I_("REDCODE"), I_("43") );
         getErrMsg ( IFASTERR::DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE, //943
                     CND::ERR_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE, 
                     CND::WARN_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE, 
                     idDataGroup,
                     idiStr);
      }
      
      if ( redCode == I_("44") && depositType != I_("1") )
      {

         DString idiStr;

         addIDITagValue (idiStr, I_("DEPOSITTYPE"), I_("1") );
         addIDITagValue (idiStr, I_("REDCODE"), I_("44") );
         getErrMsg ( IFASTERR::DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE, //943
                     CND::ERR_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE, 
                     CND::WARN_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE, 
                     idDataGroup,
                     idiStr);

      }
   // Rule 11:
      if (depositType == I_("7"))
      {
         ADDCONDITIONFROMFILE (CND::ERR_WARN_DEPOSIT_TYPE_07_INDICATES_EXCESS_FUND);
      }

     if ( depositType == I_( "27" ) )
     {
         // Deposit Type is not applicable for Transaction Type."
       ADDCONDITIONFROMFILE (CND::ERR_TRANSFER_DEPOSIT_TYPE_NOT_APPLICABLE );
     }

     // validation from QESI Project RESP Trading.
     if(isRESPTradeAccount(idDataGroup))
     {
        if(depositType == I_("2")  ||
           depositType == I_("80") || // QESI Interest
           depositType == I_("81") )  // QESI Earning Adjustment
        {
           ADDCONDITIONFROMFILE (CND::ERR_INVALID_CODE_FOR_TRANSFER);           
        }
     }
   }
   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
void Transfer::setSettleCurrencyToFund(const DString &toFund, const DString &toClass, const BFDataGroupId &idDataGroup)
{
    DString fundCurrency;

    getFundField(toFund, toClass, ifds::Currency, fundCurrency);
    setField(ifds::SettleCurrency, fundCurrency, idDataGroup, true, true);
}

//*********************************************************************************************
SEVERITY Transfer::validateProtectedFundAllowedTransfers (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateProtectedFundTransferAllowed" ) 
                         );
// if protected fund and transfer from and to account does not have the same SIN, then give warning
// if from account not blank and to account not blank and they are not equal then do edit check
   DString accountNum, 
      accountTo;

   getField (ifds::AccountNum, accountNum, idDataGroup);
   getField (ifds::AccountTo, accountTo, idDataGroup);   
   if ( !accountNum.empty() && 
        !accountTo.empty() && 
         accountNum != accountTo //not for exchanges
      )
   {
      ProtectedFundList *pProtectedFundList = NULL;
      
      
      if ( getWorkSession().getProtectedFundList (pProtectedFundList) <= WARNING &&
           pProtectedFundList
         )
      {
         DString fromFund, 
            fromClass;

         getField (ifds::FromFund, fromFund, idDataGroup);   
         getField (ifds::FromClass, fromClass, idDataGroup);
         if ( !fromFund.empty()  && 
              !fromClass.empty() &&
              pProtectedFundList->isProtectedFund (fromFund, fromClass, idDataGroup)
            )
         {
            MFAccount *pFromMFAccount = NULL,
               *pToMFAccount = NULL;
            
            if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pFromMFAccount) <= WARNING && 
                 pFromMFAccount &&
                 getWorkSession().getMFAccount (idDataGroup, accountTo, pToMFAccount) <= WARNING && 
                 pToMFAccount
               )
            {
               DString dstrToSIN, 
                  dstrFromSIN;            

               pFromMFAccount->getSINAcctOwnerSeq01 (dstrFromSIN, idDataGroup);
               pToMFAccount->getSINAcctOwnerSeq01 (dstrToSIN, idDataGroup);
               //should we better check if same owner ????
               if (dstrToSIN.strip() != dstrFromSIN.strip())
               {
                  ADDCONDITIONFROMFILE (CND::ERR_TFR_PROTECTED_FUND_TO_DIFFERENT_SIN); 
               }
            }
         } //if protected fund
      } // if ProtectedFundList available
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
inline SEVERITY Transfer::validateSettleType ( const DString &settleType,
                                               const BFDataGroupId &idDataGroup
                                             )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSettleType")
                         );
//empty
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::validateFromToFundForRealignClearingMethod( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFromToFundForRealignClearingMethod" ) );   

   DString dstrTransType;
   getField( ifds::TradesTransType, dstrTransType, idDataGroup, false );
   dstrTransType.stripAll();

   DString dstrFromFund, dstrToFund;
   getField( ifds::FromFund, dstrFromFund,  idDataGroup );
   getField( ifds::ToFund,   dstrToFund,    idDataGroup );

   // Validate only for Transfers, not applicable to Exchanges
   //TODO empty method in exchange/aftr
   if ( dstrTransType == TRADETYPE::TRANSFER &&
         dstrFromFund.stripAll() != dstrToFund.stripAll() ) 
   {                        
      // Check From side of the Instruction
      DString dstrAccountNum;
      getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      dstrAccountNum.strip().stripLeading( '0' );
      MFAccount *pMFAccount = NULL;
      if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
           pMFAccount != NULL &&
           pMFAccount->isClearingAcount( idDataGroup ) && 
           pMFAccount->hasSettlementLocation( idDataGroup ) )
      {                           
         DString dstrFromClearingId, dstrFromClearingMethod;
         pMFAccount->getField( ifds::ClearingID, dstrFromClearingId, idDataGroup );
         getField( ifds::FrClearingMethod, dstrFromClearingMethod, idDataGroup );
         
         if (  I_( "RLG" ) == dstrFromClearingMethod && 
               I_( "C" )   == dstrFromClearingId )            
         {
            // Realignment Method for From side of Settlement Instruction allowed only for same From and To Fund.
            ADDCONDITIONFROMFILE( CND::ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND );                                          
         }
      }

      // Check To side of the Instruction
      DString dstrAccountTo;
      getField( ifds::AccountTo, dstrAccountTo, idDataGroup );
      dstrAccountTo.stripAll();
      MFAccount *pMFAccountTo = NULL;
      if( getWorkSession().getMFAccount (idDataGroup, dstrAccountTo.stripAll(), pMFAccountTo) <= WARNING && 
          NULL != pMFAccountTo &&
          pMFAccountTo->isClearingAcount( idDataGroup ) &&
          pMFAccountTo->hasSettlementLocation( idDataGroup ) )
      {
         DString dstrToClearingId, dstrToClearingMethod;
         pMFAccountTo->getField( ifds::ClearingID, dstrToClearingId, idDataGroup );
          getField( ifds::ToClearingMethod, dstrToClearingMethod,   idDataGroup );
         
         if ( I_( "RLG" ) == dstrToClearingMethod &&
              I_( "C" )   == dstrToClearingId )
         {
            // Realignment Method for To side of Settlement Instruction allowed only for same From and To Fund.
            ADDCONDITIONFROMFILE( CND::ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Transfer::validateFromToClassForRealignClearingMethod( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFromToClassForRealignClearingMethod" ) );   

   DString dstrTransType;
   getField( ifds::TradesTransType, dstrTransType, idDataGroup, false );
   dstrTransType.stripAll();

   DString dstrFromClass, dstrToClass;
   getField( ifds::FromClass, dstrFromClass,  idDataGroup );
   getField( ifds::ToClass,   dstrToClass,    idDataGroup );

   //TODO empty method in exchange/aftr
   if ( ( dstrTransType == TRADETYPE::TRANSFER ) &&
         dstrFromClass.stripAll() != dstrToClass.stripAll() ) 
   {
      // Check From side of the Instruction
      DString dstrAccountNum;
      getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
      dstrAccountNum.strip().stripLeading( '0' );
      MFAccount *pMFAccount = NULL;
      if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
           pMFAccount != NULL &&
           pMFAccount->isClearingAcount( idDataGroup ) && 
           pMFAccount->hasSettlementLocation( idDataGroup ) )
      {
         DString dstrFromClearingId, dstrFromClearingMethod;
         pMFAccount->getField( ifds::ClearingID, dstrFromClearingId, idDataGroup );
         getField( ifds::FrClearingMethod, dstrFromClearingMethod, idDataGroup );
         
         if (  I_( "RLG" ) == dstrFromClearingMethod && 
               I_( "C" )   == dstrFromClearingId )
         {
            // Realignment Method for From side of Settlement Instruction allowed only for same From and To Class.
            ADDCONDITIONFROMFILE( CND::ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS );
         }
      }

      // Check To side of the Instruction
      DString dstrAccountTo;
      getField( ifds::AccountTo, dstrAccountTo, idDataGroup );
      dstrAccountTo.stripAll();
      MFAccount *pMFAccountTo = NULL;
      if (getWorkSession().getMFAccount( idDataGroup, dstrAccountTo.stripAll(), pMFAccountTo) <= WARNING && 
          NULL != pMFAccountTo &&
          pMFAccountTo->isClearingAcount( idDataGroup ) &&
          pMFAccountTo->hasSettlementLocation( idDataGroup ) )
      {
         DString dstrToClearingId, dstrToClearingMethod;
         pMFAccountTo->getField( ifds::ClearingID, dstrToClearingId, idDataGroup );
          getField( ifds::ToClearingMethod, dstrToClearingMethod,   idDataGroup );
         
         if ( I_( "RLG" ) == dstrToClearingMethod &&
              I_( "C" )   == dstrToClearingId )
         {
            // Realignment Method for To side of Settlement Instruction allowed only for same From and To Class.
            ADDCONDITIONFROMFILE( CND::ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS );
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Transfer::isValidTransBeneficiary( const DString &dstrAcctNumFr, 
                                        const DString &dstrAcctNumTo, 
                                        const DString &SpouseOrChild, 
                                        const BFDataGroupId &idDataGroup  
                                       )
{

   bool bValid = false;
   typedef std::vector< DString > ENTITIES_VECTOR;
   ENTITIES_VECTOR acctOwnerEntities;
   DString dstrEntityId;

   MFAccount *pMFAccountTo = NULL;
   if ( getWorkSession().getMFAccount (idDataGroup, dstrAcctNumTo, pMFAccountTo) <= WARNING && 
        pMFAccountTo
      )
   {
      pMFAccountTo->getAcctOwnerEntities( acctOwnerEntities, idDataGroup );
      int iNumOfEntities = acctOwnerEntities.size();

      MFAccount *pMFAccountFr = NULL;
      if ( getWorkSession().getMFAccount (idDataGroup, dstrAcctNumFr, pMFAccountFr) <= WARNING && 
           pMFAccountFr
         )
      {
         for( int i = 0; i < iNumOfEntities; ++i )
         {
            dstrEntityId = acctOwnerEntities[i] ;
            if (SpouseOrChild == I_("Spousal"))
            {
               bValid = pMFAccountFr->isSpousalBeneficiary(  dstrEntityId, idDataGroup );
               if( bValid )
                  break;
            }
            else if (SpouseOrChild == I_("Child"))
            {
               bValid = pMFAccountFr->isChildBeneficiary(  dstrEntityId, idDataGroup );
               if (bValid)
               {
                  break;
               }
            }
         }
      }
      else
      {
         bValid = false;
      }
   }
   else
   {
      bValid = false;
   }

   return bValid;
}

//******************************************************************************
bool Transfer::isValidBeneficiary ( const DString &dstrAcctNumFr, 
                                    const DString &dstrAcctNumTo, 
                                    const BFDataGroupId &idDataGroup 
                                  )
{
   bool bValid = false;
   ENTITIES_VECTOR acctOwnerEntities;
   DString dstrEntityId;

   MFAccount *pMFAccountTo = NULL;
   if ( getWorkSession().getMFAccount (idDataGroup, dstrAcctNumTo, pMFAccountTo) <= WARNING && 
        pMFAccountTo 
      )
   {
      pMFAccountTo->getAcctOwnerEntities( acctOwnerEntities, idDataGroup );
      int iNumOfEntities = acctOwnerEntities.size();

      MFAccount *pMFAccountFr = NULL;
      if ( getWorkSession().getMFAccount (idDataGroup, dstrAcctNumFr, pMFAccountFr) <= WARNING && 
           pMFAccountFr 
         )
      {
         for (int i = 0; i < iNumOfEntities; ++i)
         {
            dstrEntityId = acctOwnerEntities[i] ;
            bValid = pMFAccountFr->isBeneficiary (dstrEntityId, idDataGroup);
            if( bValid )
               break;
         }
      }
   }
   return bValid;
}

//******************************************************************************
SEVERITY Transfer::amsAccountRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("amsAccountRelatedChanges")
                         );
   DString accountNum;
   MFAccount *pMFAccount = NULL;

   getField (ifds::AccountTo, accountNum, idDataGroup, false);
   if ( getWorkSession().getMFAccount ( idDataGroup, 
                                        accountNum, 
                                        pMFAccount
                                      ) <= WARNING && 
        pMFAccount
      )
   {
      bool bReadOnly = false;

      if (pMFAccount->isAMSAccount (idDataGroup)) 
      {
         DString defaultAllocOverride;

         getWorkSession().getOption ( ifds::DefaultAllocOverride, 
                                       defaultAllocOverride, 
                                       idDataGroup, 
                                       false
                                    ); 
         if (defaultAllocOverride == Y)  
         {
            bReadOnly = !getWorkSession().hasUpdatePermission (UAF::AMS_MIX_OVERRIDE);
         }
      }
      setFieldReadOnly (ifds::ToFundNumber, idDataGroup, bReadOnly);
      setFieldReadOnly (ifds::ToFund, idDataGroup, bReadOnly);
      setFieldReadOnly (ifds::ToClass, idDataGroup, bReadOnly);
      setFieldReadOnly (ifds::FundToISIN, idDataGroup, bReadOnly);
      setFieldReadOnly (ifds::FundToWKN, idDataGroup, bReadOnly);
      setFieldReadOnly (ifds::FundToLFC, idDataGroup, bReadOnly);
	  setFieldReadOnly (ifds::ToCUSIP, idDataGroup, bReadOnly);
      setFieldRequired (ifds::ToFund, idDataGroup, !bReadOnly);
      setFieldRequired (ifds::ToClass, idDataGroup, !bReadOnly);
//to force validation
      setFieldValid (ifds::ToFund, idDataGroup, bReadOnly);
      setFieldValid (ifds::ToClass, idDataGroup, bReadOnly);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
bool Transfer::isROAApplicable( const BFDataGroupId &idDataGroup )
{
   bool bRet = false;
   DString fund,clss,toFund,toClass,loadType;
   if ( isROATransType(idDataGroup) )
   {
      getField(ifds::FromFund,fund,idDataGroup,false );
      getField(ifds::FromClass,clss,idDataGroup,false );
      FundDetail *pfrFundDetail = NULL;
      if ( getWorkSession ().getFundDetail ( fund, clss,idDataGroup, pfrFundDetail)  && pfrFundDetail != NULL)
      {
         DString incvActive,incvBaseOn;
         pfrFundDetail->getFeeInfoInquiryField(ifds::IncvActive, incvActive, idDataGroup, false);
         pfrFundDetail->getFeeInfoInquiryField(ifds::IncvBasedOn, incvBaseOn, idDataGroup, false);
         incvActive.strip().upperCase();
         incvBaseOn.strip().upperCase();
         if( incvActive == I_("Y") && incvBaseOn == I_("3") )
         {
               getField(ifds::ToFund,toFund,idDataGroup,false );
               getField(ifds::ToClass,toClass,idDataGroup,false );
               FundDetail *ptoFundDetail = NULL;
               if ( getWorkSession ().getFundDetail ( toFund, toClass,idDataGroup, ptoFundDetail) && ptoFundDetail != NULL)
               {
                  ptoFundDetail->getField ( ifds::LoadType,loadType,idDataGroup,false);
                  loadType.strip().upperCase();
                  if( loadType == I_("FEL") )
                  {
                     bRet = true;
                  }
               }
         }
      }     
   }
   return bRet;
}
//******************************************************************************
void Transfer::getROARelatedFields ( DString &amt,
                                     DString &amtType, 
                                     DString &currency,
                                     DString &exchRate, 
                                     const BFDataGroupId &idDataGroup)
{
  DString roaAmnt;

  getField (ifds::ROAAmount,roaAmnt,idDataGroup,false );
  double dAmt = DSTCommonFunctions::convertToDouble(roaAmnt);
  if (isROAApplicable( idDataGroup ) && dAmt > 0.0)
  {
      amt = roaAmnt;
      amtType = I_("D"); 
      exchRate = I_("1.0");
      
      FundDetail *pToFundDetail = NULL;
      DString  fund,
         clss;

      getField (ifds::ToFund, fund, idDataGroup, false);
      getField (ifds::ToClass, clss, idDataGroup, false);
      if ( getWorkSession ().getFundDetail (fund, clss, idDataGroup, pToFundDetail) && 
           pToFundDetail)
      {
         pToFundDetail->getField (ifds::Currency, currency, idDataGroup, false);
         currency.strip();
      }
  }
  else
  {
     Trade::getROARelatedFields ( amt,amtType,currency,exchRate, idDataGroup );
  }
}
//******************************************************************************
bool Transfer::isSplitCommissionAllowed (const BFDataGroupId &idDataGroup)
{
   DString roaAmnt;

   getField (ifds::ROAAmount, roaAmnt, idDataGroup, false); 
   double dAmt = DSTCommonFunctions::convertToDouble(roaAmnt);

   if (isROAApplicable(idDataGroup) && dAmt <= 0.0) // split commission is not applicable if ROA amount is 0.0
   {
      return false;
   }
   else
   {
      return Trade::isSplitCommissionAllowed (idDataGroup);
   }
}

//*****************************************************************************
void Transfer::roaAmountRelatedChanges (const BFDataGroupId &idDataGroup)
{
   DString roaAmnt;
   
   getField(ifds::ROAAmount,roaAmnt,idDataGroup,false );
   double dAmt = DSTCommonFunctions::convertToDouble(roaAmnt);
   
   if (isROAApplicable( idDataGroup ) && dAmt <= 0.0) 
   {
         bool bDelSplit =  false;
         TradeFundAllocList *pFundAllocationList = NULL;
         if ( getFundAllocationList (pFundAllocationList, idDataGroup, false) <= WARNING &&
              pFundAllocationList)
         {
            BFObjIter iterAllocList (*pFundAllocationList, idDataGroup);
            while (!iterAllocList.end())
            {
               TradeFundAlloc *pTradeFundAlloc = 
                     dynamic_cast <TradeFundAlloc *> (iterAllocList.getObject());

               if (pTradeFundAlloc)
               {
                  if (isNew())
                  {
                     BFObjIter iterAlloc (*pTradeFundAlloc, idDataGroup);

                     if (iterAlloc.positionByKey (I_("SplitCommissionList")))
                     {
                        iterAlloc.removeObjectFromMap (true);
                        bDelSplit = true;
                     }
                  }
                  else
                  {
                     SplitCommissionList* pSplitCommissionList = NULL;
                     pTradeFundAlloc->getSplitCommissionList ( pSplitCommissionList, 
                                                               idDataGroup, 
                                                               false);
                     if (pSplitCommissionList)
                     {
                        BFObjIter itSplit (*pSplitCommissionList, idDataGroup);
                         
                        while (!itSplit.end())
                        {
                           itSplit.deleteObject();
                           bDelSplit = true;
                           ++itSplit;
                        }                  
                     }// end of split commission
                  }
               }
               ++iterAllocList;
            }            
         }
         if (bDelSplit) // if split commission has been deleted, we need to notify fee
         {
            TransFeeList *pTransFeeList = NULL;
            if ( getTransFeeList (pTransFeeList, idDataGroup, false) <= WARNING &&
                 pTransFeeList)
            {
               pTransFeeList->onNotify (FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_("ForceRefresh"));
            }            
         }
   }
   else
   {
      Trade::roaAmountRelatedChanges (idDataGroup);
   }
}

//******************************************************************************
bool Transfer::isEUSDApplicable (const BFDataGroupId &idDataGroup)
{
   DString eusdParticip;

   getWorkSession ().getOption ( ifds::EUSDParticip, 
                                 eusdParticip, 
                                 BF::HOST,
                                 false);
   return eusdParticip == I_("Y");
}

//******************************************************************************
SEVERITY Transfer::validateSettleSource ( const DString &settleSource,
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSettleSource"));

   if (Trade::commonValidateSettleSource (settleSource, idDataGroup) <= WARNING)
   {
      if (settleSource != I_("D") && !isInterClassSwitch(idDataGroup)) //this is the default
      {
         getErrMsg ( IFASTERR::SETTLEMENT_SOURCE_IS_NOT_UPDATABLE, 
                     CND::ERR_SETTLEMENT_SOURCE_NOT_UPDATABLE, 
                     CND::WARN_SETTLEMENT_SOURCE_NOT_UPDATABLE, 
                     idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateSegBackdates (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSeqBackdates"));

   DString fundCode, toFundCode, classCode, toClassCode, transType;
   DString accountNum, toAccountNum, tradeDate;
   SeqFundValidation *pSeqFundValidation = NULL;

   getField (ifds::AccountNum, accountNum, idDataGroup);
   getField (ifds::FromFund, fundCode, idDataGroup);
   getField (ifds::FromClass, classCode, idDataGroup);

   if (!fundCode.empty () && !classCode.empty () && !accountNum.empty ())
   {
      getField (ifds::TradesTransType, transType, idDataGroup);
      getField (ifds::EffectiveDate, tradeDate, idDataGroup);   
      getField (ifds::AccountTo, toAccountNum, idDataGroup);

      if (isSegEnvironment (idDataGroup) && isBackdatedTrade (idDataGroup))
      {
         if (hasAllocations (idDataGroup))
         {
            TradeFundAllocList *pTradeFundAllocList = NULL;
            
            if (getFundAllocationList (pTradeFundAllocList, idDataGroup) <= WARNING &&pTradeFundAllocList)
            {
               TradeFundAlloc *pTradeFundAlloc = NULL;

               BFObjIter iter (*pTradeFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
            
               while (!iter.end ()) 
               {
                  pTradeFundAlloc = dynamic_cast <TradeFundAlloc*> (iter.getObject ());

                  if (pTradeFundAlloc)
                  {
                     pTradeFundAlloc->getField (ifds::FundCode, toFundCode, idDataGroup);
                     pTradeFundAlloc->getField (ifds::ClassCode, toClassCode, idDataGroup);

                     if (getSegFundValidation ( pSeqFundValidation, fundCode, classCode, accountNum, 
                                                tradeDate, idDataGroup, NULL_STRING, transType, 
                                                toFundCode, toClassCode, toAccountNum) <= WARNING && pSeqFundValidation)
                     {
                        if (pSeqFundValidation->checkBackdatedAllowed (tradeDate, idDataGroup) > WARNING)
                        {
                           break;
                        }
                     }
                  }
                  ++iter;
               }//while
            }
         }
         else
         {
            if (!fundCode.empty () && !classCode.empty () && !accountNum.empty ())
            {
               getField (ifds::ToFund, toFundCode, idDataGroup, false);
               getField (ifds::ToClass, toClassCode, idDataGroup, false);
            
               if (getSegFundValidation ( pSeqFundValidation, fundCode, classCode,   accountNum, 
                                          tradeDate, idDataGroup, NULL_STRING, transType,
                                          toFundCode, toClassCode, toAccountNum) <= WARNING && pSeqFundValidation)
               {
                  pSeqFundValidation->checkBackdatedAllowed (tradeDate, idDataGroup);
               }
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::doValidateAll ( const BFDataGroupId& idDataGroup, long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));

   if (Trade::doValidateAll (idDataGroup, lValidateGroup) <= WARNING)
   {
      if (DSTCommonFunctions::getMarket () == MARKET_IDS::CANADA)
      {
         // validation postponed due to LIF Restriction project
         MFAccount *pMFAccount = NULL;
         DString accountNum;

         bValidateAll = true;
         getField (ifds::AccountTo, accountNum, idDataGroup, false);

         if (getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
            pMFAccount)
         {
            validateAccountTo (pMFAccount, idDataGroup);
            bValidateAll = false;
         }
      }

      validateBeneficiaryAllocation (idDataGroup);
      validatePerfFeeFromToClassesWithFund ( idDataGroup );
      validatePerfFeeFXRate ( idDataGroup );

      validateAllSegTransfer(idDataGroup);

	  //PET 212427 FN 01 - Project Thunder
	  //From and To transfer (different account) for contract must be the same contract type and contract version if to from contract has a LWA GPR Method = NMCR series. 
	  //New Rej-error to trigger this edit check. EWI should be set to ‘E’ as minimum severity. System processing does not support otherwise.
	  //Also, Annuitant (younger one for joint annuitant contract) of the from and to account must have the same age as of year end. 
	  //Must be the same gender if it is a single annuitant account. 
	  //This is to ensure the carry over guarantee rate at transaction level is applicable to the ‘To account’. 	   
	  validateNMCRContractTypeAndVersion ( idDataGroup );	

      validateToSoftCapCheck(idDataGroup);

	  validateCashDateToFundMandatory(idDataGroup);

	  validateUnusualTrading(idDataGroup);
	  validateSuspendedFund(idDataGroup);

   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::setDefaultOrderType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setDefaultOrderType"));

   DString orderType (N);

   if (isRealignmentTransfer (idDataGroup))
   {
      orderType = N; //direct
   }
   else if (isParticipantTransfer (idDataGroup))
   {
      orderType = Y; //wire
   }
   setFieldNoValidate ( ifds::OrderType, orderType, idDataGroup, false, 
                        false,
                        true, //notify
                        true);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Transfer::isAClearingSameFundTransfer (bool bCheckBothAccounts,
                                            const BFDataGroupId &idDataGroup)
{
   DString accountTo, 
      accountFrom,
      fromFund, 
      fromClass, 
      toFund, 
      toClass;

   MFAccount *pMFAccountFrom = NULL,
      *pMFAccountTo = NULL;

   getField (ifds::AccountNum, accountFrom, idDataGroup);
   getField (ifds::AccountTo, accountTo, idDataGroup);
   getField (ifds::FromFund, fromFund, idDataGroup);
   getField (ifds::FromClass, fromClass, idDataGroup);
   getField (ifds::ToFund, toFund, idDataGroup);
   getField (ifds::ToClass, toClass, idDataGroup);

   bool bIsAClearingTransfer = false;

   if (bCheckBothAccounts)
   {
      bIsAClearingTransfer = 
           !accountFrom.empty () && 
           getWorkSession ().getMFAccount (idDataGroup, accountFrom, pMFAccountFrom) <= WARNING &&
           pMFAccountFrom &&
           pMFAccountFrom->isClearingAcount (idDataGroup) &&
           !accountTo.empty () && 
           getWorkSession ().getMFAccount (idDataGroup, accountTo, pMFAccountTo) <= WARNING &&
           pMFAccountTo &&
           pMFAccountTo->isClearingAcount (idDataGroup);
   }
   else 
   {
      bIsAClearingTransfer = 
           (!accountFrom.empty () && 
            getWorkSession ().getMFAccount (idDataGroup, accountFrom, pMFAccountFrom) <= WARNING &&
            pMFAccountFrom &&
            pMFAccountFrom->isClearingAcount (idDataGroup)) ||
           (!accountTo.empty () && 
            getWorkSession ().getMFAccount (idDataGroup, accountTo, pMFAccountTo) <= WARNING &&
            pMFAccountTo &&
            pMFAccountTo->isClearingAcount (idDataGroup));

   }
   return  bIsAClearingTransfer &&
           !fromFund.empty () &&
           !fromClass.empty () &&
           !toFund.empty () &&
           !toClass.empty () &&
           fromFund == toFund &&
           fromClass == toClass;
}

//******************************************************************************
bool Transfer::isParticipantTransfer (const BFDataGroupId &idDataGroup)
{
   bool bIsParticipantTransfer = false;

//for participant transfer at least one account should be clearing
   if (isAClearingSameFundTransfer (false /*at least one account */, idDataGroup))
   {
      DString fromClearingMethod,
         toClearingMethod;

      getField (ifds::FrClearingMethod, fromClearingMethod, idDataGroup, false);
      getField (ifds::ToClearingMethod, toClearingMethod, idDataGroup, false);
      bIsParticipantTransfer = fromClearingMethod != REALIGNMENT && toClearingMethod != REALIGNMENT;
   }
   return bIsParticipantTransfer;
}

//******************************************************************************
bool Transfer::isWireSupported (const BFDataGroupId &idDataGroup)
{

   DString   dftOrdTypeDSK;

   getWorkSession ().getOption (ifds::DftOrdTypeDSK, dftOrdTypeDSK, idDataGroup, false);
   bool supported = dftOrdTypeDSK == Y;

   if (supported)
   {
      DString dftOrdTypeTREX;

      getWorkSession ().getOption (ifds::DftOrdTypeTR, dftOrdTypeTREX, idDataGroup, false);
      supported = dftOrdTypeTREX != I_("0");
   }

   return supported;
}

//******************************************************************************
bool Transfer::isRealignmentTransfer (const BFDataGroupId& idDataGroup)
{
   bool bIsRealignmentTransfer = false;

//for realignment transfer both accounts should be clearing
   if (isAClearingSameFundTransfer (true /*check both accounts*/, idDataGroup))
   {
      DString fromClearingMethod,
         toClearingMethod;

      getField (ifds::FrClearingMethod, fromClearingMethod, idDataGroup, false);
      getField (ifds::ToClearingMethod, toClearingMethod, idDataGroup, false);
      bIsRealignmentTransfer = fromClearingMethod == REALIGNMENT && toClearingMethod == REALIGNMENT;
   }
   return bIsRealignmentTransfer;
}

//******************************************************************************
bool Transfer::isEstateTransfer (const BFDataGroupId &idDataGroup)
{
	DString	deathClaimRedCodes;
	DString	redmptionCode;
	DString accountNum;
	MFAccount *pMFAccount = NULL;

	// check if from account have death date set.
    getField( ifds::AccountNum, accountNum, idDataGroup );
    if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
         pMFAccount)
    {
		DString dstrDofDeath;

        pMFAccount->getDofDeathofOwnerSeq01 (dstrDofDeath, idDataGroup);
        dstrDofDeath.strip();
        if (dstrDofDeath.empty())
			return false;
	}

	if (bValidateAll)
	{
		getWorkSession ().getOption (ifds::DeathClaimRedCodes, deathClaimRedCodes, idDataGroup, false);
		getField( ifds::RedCode, redmptionCode, idDataGroup, false );

		bool isDeathClaimRedCode = DSTCommonFunctions::codeInList (redmptionCode, deathClaimRedCodes);
  
		return isDeathClaimRedCode;
	}
	else
		return true;
}
//******************************************************************************
SEVERITY Transfer::validateClearingForRealignmntTr (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateClearingForRealignmntTr"));

   if (isAClearingSameFundTransfer (true, idDataGroup))
   {
      DString frClearingMethod,
         toClearingMethod;

      getField (ifds::FrClearingMethod, frClearingMethod, idDataGroup);
      getField (ifds::ToClearingMethod, toClearingMethod, idDataGroup);

      if (!frClearingMethod.empty() && !toClearingMethod.empty())
      {
         if ( (frClearingMethod == REALIGNMENT && toClearingMethod != REALIGNMENT) ||
              (frClearingMethod != REALIGNMENT && toClearingMethod == REALIGNMENT))
         {
            ADDCONDITIONFROMFILE( CND::ERR_FR_TO_CLEARING_METHOD_NOT_SAME_AND_NOT_RLG );
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Transfer::isResidencyRequired ( DString& dstrAccountNum, 
                                     const BFDataGroupId &idDataGroup)
{
   bool bRetVal = false;

   MFAccount *pMFAccount = NULL;
   getField (ifds::AccountTo, dstrAccountNum, idDataGroup);
   dstrAccountNum.strip ().stripLeading ('0');
   if ( isTransfer( idDataGroup ) &&
	    getWorkSession().getMFAccount (idDataGroup, dstrAccountNum,
		pMFAccount) <= WARNING && pMFAccount)
   {
      DString dstrTaxType;
      
      pMFAccount->getField (ifds::TaxType, dstrTaxType, idDataGroup);
      if( dstrTaxType.strip().upperCase() == TFSA_TAX_TYPE )
      {
		  bRetVal = true;
      }
   }
   return bRetVal;
}

//******************************************************************************
SEVERITY Transfer::getFormerSpouseList( DString& strFormerSpouses, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFormerSpouseList"));
   
   strFormerSpouses = I_("0=N/A;");
   DString strTaxType, strRedCode, strToAccount;

   //getField (ifds::AccountTo, strToAccount, idDataGroup, false);
   getField (ifds::AccountNum, strToAccount, idDataGroup, false);
   if (!strToAccount.strip().empty())
   {
      MFAccount *pMFAccount = NULL;
      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                          strToAccount, 
                                          pMFAccount) <= WARNING && pMFAccount)
      {
         pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup, false );
         /*if( strTaxType.strip().upperCase() == TFSA_TAX_TYPE ||
         strTaxType == EXTERNAL_TFSA_TAX_TYPE )*/
         {
            getField( ifds::RedCode, strRedCode, idDataGroup, false );
            if( strRedCode.strip() == I_("29") ||
                strRedCode.strip() == I_("30") )
            {
               populateFormerSpouseList( strToAccount, strFormerSpouses, idDataGroup );
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
SEVERITY Transfer::validateClosedCountryForPendingTrades (const BFDataGroupId &idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateClosedCountryForPendingTrades"));

   DString dstrFromFund, dstrFromClass,
           dstrToFund, dstrToClass;

   getField(ifds::FromFund, dstrFromFund, idDataGroup, false);
   getField(ifds::FromClass, dstrFromClass, idDataGroup, false);
   getField(ifds::ToFund, dstrToFund, idDataGroup, false);
   getField(ifds::ToClass, dstrToClass, idDataGroup, false);

   if ( !( dstrFromFund.strip().upperCase() == dstrToFund.strip().upperCase() && 
           dstrFromClass.strip().upperCase() == dstrToClass.strip().upperCase() )) 
   {
      DString dstrAccountTo;

      getField (ifds::AccountTo, dstrAccountTo, idDataGroup);
      validateClosedCountry (dstrAccountTo, idDataGroup);
   }
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::validateFundToWithSegValidation(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
      CLASSNAME, 
      I_("validateFundToWithSegValidation"));
   if (isSegEnvironment (idDataGroup))
   {  
      DString dstrToFundCode, dstrToClassCode, dstrToAccountNum;
      getField( ifds::ToFund, dstrToFundCode, idDataGroup);
      getField( ifds::ToClass, dstrToClassCode, idDataGroup);
      getField( ifds::AccountTo, dstrToAccountNum, idDataGroup);

      if ( !dstrToFundCode.empty() &&
           !dstrToClassCode.empty() &&
           !dstrToAccountNum.empty())
      {
         SeqFundValidation *pSeqFundValidation = NULL;
         DString dstrTransType, dstrTradeDate, dstrFromFundCode, 
            dstrFromClassCode, dstrFromAccountNum;

         getField( ifds::FromFund, dstrFromFundCode, idDataGroup);
         getField( ifds::FromClass, dstrFromClassCode, idDataGroup);
         getField( ifds::AccountNum, dstrFromAccountNum, idDataGroup);

         getField( ifds::TradesTransType, dstrTransType, idDataGroup, false );
         getField (ifds::EffectiveDate, dstrTradeDate,  idDataGroup);
         if ( getSegFundValidation ( pSeqFundValidation, 
                                     dstrFromFundCode, 
                                     dstrFromClassCode, 
                                     dstrFromAccountNum, 
                                     dstrTradeDate,
                                     idDataGroup, 
                                     NULL_STRING,
                                     dstrTransType,
                                     dstrToFundCode, 
                                     dstrToClassCode, 
                                     dstrToAccountNum) <= WARNING &&
             pSeqFundValidation)
         {
            DString strDepAllowed;
            pSeqFundValidation->getField(ifds::DepAllowed, strDepAllowed, idDataGroup);
            if( strDepAllowed == I_("N") )
            {
               ADDCONDITIONFROMFILE( CND::ERR_DEPOSITS_NOT_ALLOWED );
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Transfer::validateMasterActAMS(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMasterActAMS"));

    DString dstrFundCode, dstrClassCode, dstrAccountTo, dstrAccountFrom, dstrTradeDate;
    MFAccount *pMFAccountTo = NULL;
    MFAccount *pMFAccountFrom = NULL;
    FundDetail *pFundDetailTo = NULL;
    AMSMstrList *pAMSMstrListTo = NULL;
    AmsMstrInfo *pAMSMstrInfoTo = NULL;

    getField(ifds::AccountNum, dstrAccountFrom, idDataGroup);
    getField(ifds::AccountTo, dstrAccountTo, idDataGroup);
    getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup, false);

    if (getWorkSession().getMFAccount(idDataGroup, dstrAccountFrom, pMFAccountFrom) <= WARNING && pMFAccountFrom &&
        getWorkSession().getMFAccount(idDataGroup, dstrAccountTo, pMFAccountTo) <= WARNING && pMFAccountTo )
    {
       // both are AMS
       if ( pMFAccountFrom->isAMSAccount(idDataGroup) &&
          pMFAccountTo->isAMSAccount(idDataGroup) &&
          pMFAccountTo->getAMSMstrList(pAMSMstrListTo, idDataGroup,  dstrTradeDate) <= WARNING && pAMSMstrListTo)
       {
          DString dstrAcctFromAMSCode, dstrAcctToAMSCode, dstrTradeDate;
          DString dstrToFund, dstrToClass;

          pMFAccountFrom->getField(ifds::AMSCode, dstrAcctFromAMSCode, idDataGroup);
          pMFAccountTo->getField(ifds::AMSCode, dstrAcctToAMSCode, idDataGroup);

          getField(ifds::ToFund, dstrToFund, idDataGroup);
          getField(ifds::ToClass, dstrToClass, idDataGroup);

          pAMSMstrListTo->getAMSMstrInfo(I_("RB"), dstrAcctToAMSCode, dstrTradeDate, pAMSMstrInfoTo, idDataGroup);

          if (getWorkSession().getFundDetail(dstrToFund, dstrToClass, idDataGroup, pFundDetailTo) && pFundDetailTo)
          {
             if (pFundDetailTo->isAMSParentFund(idDataGroup) &&
                dstrAcctFromAMSCode != dstrAcctToAMSCode)
             {
                getErrMsg(IFASTERR::RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL,
                          CND::ERR_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL,
                          CND::WARN_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL,
                          idDataGroup);
             }
             else if (pFundDetailTo->isAMSChildFund(idDataGroup) &&
                !pAMSMstrInfoTo->isFundInAMS(dstrToFund, dstrToClass, idDataGroup))
             {
                getErrMsg(IFASTERR::RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD,
                          CND::ERR_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD,
                          CND::WARN_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD,
                          idDataGroup);
             }
          }
       }
       else if (pMFAccountFrom->isAMSAccount(idDataGroup) &&
                !pMFAccountTo->isAMSAccount(idDataGroup) )
       {
          // to-side is not AMS
          DString dstrToFund, dstrToClass;
          FundDetail *pFundDetail = NULL;

          getField(ifds::ToFund, dstrToFund, idDataGroup);
          getField(ifds::ToClass, dstrToClass, idDataGroup);

          if (getWorkSession().getFundDetail(dstrToFund, dstrToClass, idDataGroup, pFundDetail) && pFundDetail &&
             pFundDetail->isAMSParentFund(idDataGroup))
          {
             CND::CIFast_IFast_ifastcbo_warn_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams warnCond;
             CND::CIFast_IFast_ifastcbo_err_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams errCond;

             MFCanBFCbo::getErrMsg(IFASTERR::TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS,
                                   errCond,
                                   warnCond,
                                   idDataGroup);
          }
          else if (getWorkSession().getFundDetail(dstrToFund, dstrToClass, idDataGroup, pFundDetail) && pFundDetail &&
             pFundDetail->isAMSChildFund(idDataGroup))
          {
             CND::CIFast_IFast_ifastcbo_warn_trading_on_child_fnd_cls_not_allowed warnCond;
             CND::CIFast_IFast_ifastcbo_err_trading_on_child_fnd_cls_not_allowed errCond;

             MFCanBFCbo::getErrMsg (IFASTERR::TRADING_ON_CHILD_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS, // 1783
                                    errCond,
                                    warnCond,
                                    idDataGroup);
          }
       }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Transfer::allowToFndClsBeParentAMS(const BFDataGroupId &idDataGroup)
{
    // Allow FundTo/ClassTo to be AMS Parent Fund/Class if an environment is MasterActWithOneChild

    DString dstrToFundCode, dstrToClassCode;
    FundDetail *pToFundDetail = NULL;
    bool isParentAMS = false;

    getField(ifds::ToFund, dstrToFundCode, idDataGroup);
    getField(ifds::ToClass, dstrToClassCode, idDataGroup);

    if (getWorkSession().getFundDetail(dstrToFundCode, dstrToClassCode, idDataGroup, pToFundDetail) && pToFundDetail)
    {
        isParentAMS = pToFundDetail->isAMSParentFund(idDataGroup);
    }

    return isParentAMS && getWorkSession().isMasterActWithOneChild(idDataGroup);
}

//******************************************************************************
bool Transfer::areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("areRESPBenefAllocationsAllowed"));

   MFAccount *pMFAccountFrom = NULL;
   MFAccount *pMFAccountTo = NULL;
   DString accountFrom;
   DString accountTo;

   getField(ifds::AccountNum, accountFrom, idDataGroup, false);
   getField(ifds::AccountTo, accountTo, idDataGroup, false);

   accountFrom.strip();
   accountTo.strip();

   if (getWorkSession().getMFAccount (idDataGroup, accountFrom, pMFAccountFrom) <= WARNING && 
      pMFAccountFrom)
   {
      DString taxType;

      pMFAccountFrom->getField (ifds::TaxType, taxType, idDataGroup);
      taxType.strip().upperCase();

      if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES))
         return false;
   }

   if (getWorkSession().getMFAccount (idDataGroup, accountTo, pMFAccountTo) <= WARNING && 
      pMFAccountTo)
   {
      DString taxType;
      DString depositType;
      DString redCode;

      pMFAccountTo->getField (ifds::TaxType, taxType, idDataGroup);
      taxType.strip().upperCase();

      getField( ifds::DepositType, depositType, idDataGroup );
      getField( ifds::RedCode, redCode, idDataGroup );

      depositType.stripAll();
      redCode.stripAll();

      if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES) && 
         DSTCommonFunctions::codeInList (depositType, RESP_BENEFALLOC_DEPOSIT) &&
         !DSTCommonFunctions::codeInList (redCode, RESP_TR_RED_CODES))
      {
         return true;
      }
   }

   return false;
}

//******************************************************************************
bool Transfer::isRESPTransferAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRESPTransferAllowed"));

   DString dstrDepositType;
   DString dstrRedemptionCode;
   DString dstrAccountNum;
   DString dstrAccountToNum;

   MFAccount *pMFAccount = NULL;
   MFAccount *pMFAccountTo = NULL;

   getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getField (ifds::AccountTo, dstrAccountToNum, idDataGroup, false);

   if ((getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount) &&
      (getWorkSession().getMFAccount (idDataGroup, dstrAccountToNum, pMFAccountTo) <= WARNING && pMFAccountTo))
   {

      DString dstrTaxTypeFrom;
      DString dstrTaxTypeTo;

      pMFAccount->getField (ifds::TaxType, dstrTaxTypeFrom, idDataGroup);
      pMFAccountTo->getField (ifds::TaxType, dstrTaxTypeTo, idDataGroup);

      if (DSTCommonFunctions::codeInList (dstrTaxTypeFrom, RESP_TAX_TYPES) &&
         DSTCommonFunctions::codeInList (dstrTaxTypeTo, RESP_TAX_TYPES))
      {
         // transfer from RESP to RESP
         getField( ifds::DepositType, dstrDepositType.stripAll(), idDataGroup );
         getField( ifds::RedCode, dstrRedemptionCode.stripAll(), idDataGroup );

         if (dstrDepositType == I_("17") && (dstrRedemptionCode == I_("64") || dstrRedemptionCode == I_("65")))
         {
            return true;
         }
      }
      else if (DSTCommonFunctions::codeInList (dstrTaxTypeFrom, SD_EXTERNAL_RESP_TAX_TYPES) &&
         DSTCommonFunctions::codeInList (dstrTaxTypeTo, RESP_TAX_TYPES))
      {
         // transfer exteranl RESP to RESP
         getField( ifds::DepositType, dstrDepositType.stripAll(), idDataGroup );

         if (dstrDepositType == I_("17"))
         {
            return true;
         }

      }
      else if (DSTCommonFunctions::codeInList (dstrTaxTypeFrom, RESP_TAX_TYPES) &&
         DSTCommonFunctions::codeInList (dstrTaxTypeTo, SD_EXTERNAL_RESP_TAX_TYPES))
      {
         // transfer RESP to exteranal RESP
         getField( ifds::RedCode, dstrRedemptionCode.stripAll(), idDataGroup );

         if (dstrRedemptionCode == I_("64") || dstrRedemptionCode == I_("65"))
         {
            return true;
         }
      }
   }

   return false;
}

//******************************************************************************
bool Transfer::isAIPAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAIPAllowed"));

   DString dstrFromAccount;

   getField (ifds::AccountNum, dstrFromAccount, idDataGroup, false);

   if (!dstrFromAccount.empty())
   {
      MFAccount *pMFAccount = NULL;

      if ( getWorkSession().getMFAccount (idDataGroup, dstrFromAccount, pMFAccount) <= WARNING  && pMFAccount) 
      {
         DString taxType;
         DString redCode;

         pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
         taxType.strip().upperCase();

         getField (ifds::RedCode, redCode, idDataGroup, false);      
         redCode.stripAll();

		 /*		 
		    The RESP AIP redemption code should get from GC "RESP Earning&Grant RedCod",
		    For future changes, we should add the new response field in V149 for matching.
			Also, redemption CBO as well.
		 */

         if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES) && 
            DSTCommonFunctions::codeInList (redCode, RESP_AIP_RED_CODES))
            return true;
      }
   }

   return false;
}

//******************************************************************************
bool Transfer::isPSEEAPAllowed (const BFDataGroupId &idDataGroup)
{
   bool bIsPSEEAPAllowed (false);
   MFAccount *pMFAccount (NULL);

   DString dstrAccountNum;

   getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);

   if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
   {

      DString dstrTaxTypeFrom;

      pMFAccount->getField (ifds::TaxType, dstrTaxTypeFrom, idDataGroup);

      if (DSTCommonFunctions::codeInList (dstrTaxTypeFrom, RESP_TAX_TYPES))
      {
         DString redCode;
         
         getField (ifds::RedCode, redCode, idDataGroup, false);
         bIsPSEEAPAllowed = DSTCommonFunctions::codeInList (redCode, I_("61,69,77,84,85,EP"));
      }
   }
   return bIsPSEEAPAllowed;
}


//******************************************************************************
bool Transfer::isRDSPTransferAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRDSPTransferAllowed"));

   return false;
}

//******************************************************************************
SEVERITY Transfer::validateRedCodeDepTypeRESPTrade(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRedCodeDepTypeRESPTrade"));

   MFAccount *pMFAccount = NULL;
   MFAccount *pMFAccountTo = NULL;

   DString dstrAccountNum,dstrAccountToNum,dstrRedCode,dstrDepositType;

   getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getField (ifds::AccountTo, dstrAccountToNum, idDataGroup, false);
   getField (ifds::RedCode, dstrRedCode, idDataGroup, false);
   getField (ifds::DepositType, dstrDepositType, idDataGroup, false);
   dstrRedCode.strip();
   dstrDepositType.strip();

   if ((getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount) &&
      (getWorkSession().getMFAccount (idDataGroup, dstrAccountToNum, pMFAccountTo) <= WARNING && pMFAccountTo))
   {
      DString dstrTaxTypeFrom;
      DString dstrTaxTypeTo;

      pMFAccount->getField (ifds::TaxType, dstrTaxTypeFrom, idDataGroup);
      pMFAccountTo->getField (ifds::TaxType, dstrTaxTypeTo, idDataGroup);

      if (dstrDepositType == I_("17") && (dstrRedCode == I_("64") || dstrRedCode == I_("65")))
      {
         if (!(DSTCommonFunctions::codeInList (dstrTaxTypeFrom, RESP_TAX_TYPES) &&
               DSTCommonFunctions::codeInList (dstrTaxTypeTo, RESP_TAX_TYPES)))
         {
            // 329
            getErrMsg (IFASTERR::DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX ,
                       CND::ERR_DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX, 
                       CND::WARN_DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX, 
                       idDataGroup);
         }

         if (DSTCommonFunctions::codeInList (dstrTaxTypeFrom, RESP_TAX_TYPES) &&
             DSTCommonFunctions::codeInList (dstrTaxTypeTo, RESP_TAX_TYPES))
         {
            DString siblingOnly, siblingOnlyTo;
            pMFAccount->getField (ifds::SiblingOnly, siblingOnly, idDataGroup);
            pMFAccountTo->getField (ifds::SiblingOnly, siblingOnlyTo, idDataGroup);
            siblingOnly.strip().upperCase();
            siblingOnlyTo.strip().upperCase();

            if ( (!siblingOnly.empty() && !siblingOnlyTo.empty() && siblingOnly != siblingOnlyTo) || 
                  (siblingOnly.empty() && siblingOnlyTo == I_("Y")) ||
                  (siblingOnlyTo.empty() && siblingOnly == I_("Y")))
            {
               // 987
               getErrMsg (IFASTERR::DIFFERENT_SIBLINGONLY_STATUS,
                          CND::ERR_DIFFERENT_SIBLINGONLY_STATUS, 
                          CND::WARN_DIFFERENT_SIBLINGONLY_STATUS, 
                          idDataGroup);
            }

            DString strAIPWithdrawalExists;
            pMFAccount->getField (ifds::AIPWithdrawalExists, strAIPWithdrawalExists, idDataGroup);
            strAIPWithdrawalExists.strip().upperCase();
            if ( strAIPWithdrawalExists == I_("Y") )
            {
               // rej 322
               getErrMsg (IFASTERR::AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED,
                          CND::ERR_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED, 
                          CND::WARN_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED, 
                          idDataGroup);
            }
         }
      }
      else if( ( dstrDepositType == I_("17") && dstrRedCode == I_("01") && 
                 !(DSTCommonFunctions::codeInList (dstrTaxTypeFrom, SD_EXTERNAL_RESP_TAX_TYPES) &&
                   DSTCommonFunctions::codeInList (dstrTaxTypeTo, RESP_TAX_TYPES))) || 
               ( dstrDepositType == I_("1") && dstrRedCode == I_("64") && 
                 !(DSTCommonFunctions::codeInList (dstrTaxTypeFrom, RESP_TAX_TYPES) &&
                   DSTCommonFunctions::codeInList (dstrTaxTypeTo, SD_EXTERNAL_RESP_TAX_TYPES)))) // # 20, 21
      {
         ADDCONDITIONFROMFILE( CND::ERR_TRX_NOTINAL_BALANCE );
      }
      else if (DSTCommonFunctions::codeInList (dstrDepositType, I_("20,73,74,75,76,77,94")) ||
               DSTCommonFunctions::codeInList (dstrRedCode, I_("75,76,78,83,AG,AR,GR,IR")) ) // # 8, 9
      {
         // 237
         getErrMsg (IFASTERR::DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER,
                     CND::ERR_DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER, 
                     CND::WARN_DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER, 
                     idDataGroup);

      }
      else if (DSTCommonFunctions::codeInList (dstrTaxTypeFrom, RESP_TAX_TYPES) &&
               DSTCommonFunctions::codeInList (dstrTaxTypeTo, RESP_TAX_TYPES))
      {
         validateRESPtoRESPTransfer(dstrDepositType,dstrRedCode,dstrTaxTypeFrom,dstrTaxTypeTo,idDataGroup);
      }
      else if ( DSTCommonFunctions::codeInList (dstrDepositType, I_("77,94")) || DSTCommonFunctions::codeInList (dstrRedCode, I_("78,IR")))
      {
         if ( !getWorkSession().isQESIClient(idDataGroup) )
         {
            ADDCONDITIONFROMFILE( CND::ERR_DEPTYPE_REDCODE_NOT_ALLOWED_NON_QESI_ENV );
         }
      }
      else if ( dstrDepositType == I_("1") && dstrRedCode == I_("B1"))
      {
         if ( !DSTCommonFunctions::codeInList (dstrTaxTypeFrom, RESP_TAX_TYPES)  ||
			  dstrTaxTypeTo != I_("RD") )
         {
			DString idiStr, dstrTaxTypeFromDesc, dstrTaxTypeToDesc;

	        pMFAccount->getField (ifds::TaxType, dstrTaxTypeFromDesc, idDataGroup, true);
		    pMFAccountTo->getField (ifds::TaxType, dstrTaxTypeToDesc, idDataGroup, true);
			addIDITagValue (idiStr, I_("FROMTAXTYPE"), dstrTaxTypeFromDesc);
			addIDITagValue (idiStr, I_("TOTAXTYPE"), dstrTaxTypeToDesc);
			ADDCONDITIONFROMFILEIDI (CND::ERR_TR_NOT_ALLOW_FROM_TAXTYPE_TO_TAXTYPE,idiStr);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::getAccountNumToPopulateRespBeneficiary (DString &accountNum, 
                                                           const BFDataGroupId &idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("getAccountNumToPopulateRespBeneficiary"));

   DString dstrAccountNum, dstrAccountTo;

   getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getField(ifds::AccountTo, dstrAccountTo, idDataGroup, false);
   dstrAccountNum.strip();
   dstrAccountTo.strip();
   // default, to ensure that if non resp -> non resp method will return account number.
   accountNum = dstrAccountNum;
   if( !dstrAccountNum.empty() && !dstrAccountTo.empty() )
   {
      MFAccount *pMFAccount(NULL), *pMFAccountTo(NULL);   
      if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
           getWorkSession().getMFAccount (idDataGroup, dstrAccountTo, pMFAccountTo) <= WARNING &&
           ( pMFAccount && pMFAccountTo ) )
      {
         DString dstrTaxType, dstrTaxTypeTo;
         pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);
         pMFAccountTo->getField(ifds::TaxType, dstrTaxTypeTo, idDataGroup, false);
         dstrTaxType.strip().upperCase();
         dstrTaxTypeTo.strip().upperCase();

         if(DSTCommonFunctions::codeInList (dstrTaxType, RESP_TAX_TYPES))
            accountNum = dstrAccountNum;
         else if (DSTCommonFunctions::codeInList (dstrTaxTypeTo, RESP_TAX_TYPES))
            accountNum = dstrAccountTo;
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Transfer::validateRESPtoRESPTransfer(const DString& strDepType, 
                                              const DString& strRedCode, 
                                              const DString& strTaxTypeFrom, 
                                              const DString& strTaxTypeTo, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateRESPtoRESPTransfer"));

   if (strDepType != I_("17") || !DSTCommonFunctions::codeInList(strRedCode, I_("64,65")))
   {
      // 244
      getErrMsg (IFASTERR::DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER,
                 CND::ERR_DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER, 
                 CND::WARN_DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER, 
                 idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
bool Transfer::isEAPAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isEAPAllowed"));

   DString dstrFromAccount;

   getField (ifds::AccountNum, dstrFromAccount, idDataGroup, false);

   if (!dstrFromAccount.empty())
   {
      MFAccount *pMFAccount = NULL;

      if ( getWorkSession().getMFAccount (idDataGroup, dstrFromAccount, pMFAccount) <= WARNING  && pMFAccount) 
      {
         DString taxType;
         DString redCode;
         DString dstrEAPEarningCodes;

         pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
         taxType.strip().upperCase();

         getField (ifds::RedCode, redCode, idDataGroup, false);
         getWorkSession ().getOption (ifds::EAPEarningCodes, dstrEAPEarningCodes, idDataGroup, false);

         redCode.stripAll();
         dstrEAPEarningCodes.stripAll();
         
         if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES) && 
            DSTCommonFunctions::codeInList (redCode, dstrEAPEarningCodes))
            return true;
      }
   }


   return false;
}

//******************************************************************************
bool Transfer::areTaxRatesAllowed (const BFDataGroupId &idDataGroup)
{
   return _blTaxable;
}

//******************************************************************************
bool Transfer::isGuaranteeFeeOverrideAllowed (const BFDataGroupId &idDataGroup)
{
   bool bIsGuaranteeFeeOverrideAllowed (false);
   
   DString dstrRedCode,
      dstrRedCodesGuaranteeOverride,
      dstrGuaranteeCalcByRules;
   getWorkSession().getOption (ifds::RedCodesGuaranteeOverride, 
                               dstrRedCodesGuaranteeOverride, 
                               idDataGroup, 
                               false);
   getWorkSession().getOption (ifds::GuaranteeCalcByRules, 
                               dstrGuaranteeCalcByRules, 
                               idDataGroup, 
                               false);

   dstrGuaranteeCalcByRules.strip().upperCase();
   getField (ifds::RedCode, dstrRedCode, idDataGroup, false);
   dstrRedCode.strip().upperCase();

   bIsGuaranteeFeeOverrideAllowed = DSTCommonFunctions::codeInList (dstrRedCode, dstrRedCodesGuaranteeOverride) && 
                                    dstrGuaranteeCalcByRules == I_("Y");
   
   MFAccount *pMFAccount (NULL),
      *pMFAccountTo (NULL);
   DString dstrAccountNum,
      dstrAccountToNum;

   getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getField (ifds::AccountTo, dstrAccountToNum, idDataGroup, false);
   dstrAccountNum.strip().upperCase();
   dstrAccountToNum.strip().upperCase();
   bIsGuaranteeFeeOverrideAllowed = bIsGuaranteeFeeOverrideAllowed && 
                                    !dstrAccountNum.empty() && 
                                    !dstrAccountToNum.empty();
   
   if (bIsGuaranteeFeeOverrideAllowed)
   {
      AccountEntityXref *pAccountEntityXref = NULL,
         *pAccountToEntityXref = NULL;
      getWorkSession().getAccountEntityXref(idDataGroup, pAccountEntityXref);

      if(pAccountEntityXref &&
         pAccountEntityXref->GetNumberOfEntityByType(dstrAccountNum, ENTITY_ANNUITANT, idDataGroup) == 1 &&
         pAccountEntityXref->GetNumberOfEntityByType(dstrAccountToNum, ENTITY_ANNUITANT, idDataGroup) == 1)
      {

         AccountEntityXrefObject *pAccountEntityXrefObject = NULL;
         AccountEntityXrefObject *pAccountToEntityXrefObject = NULL;
         
         Entity *pAnnuitantEntity = NULL, 
            *pAnnuitantEntityTo = NULL;

         DString dstrEntityId, dstrEntityIdTo;
         DString sinFrom, sinTo;

         if(pAccountEntityXref->GetAccountEntityXrefObjectByType(
                  dstrAccountNum, 
                  ENTITY_ANNUITANT, 
                  0, 
                  idDataGroup,
                  pAccountEntityXrefObject) <= WARNING && 
            pAccountEntityXrefObject &&
            pAccountEntityXref->GetAccountEntityXrefObjectByType(
               dstrAccountToNum, 
               ENTITY_ANNUITANT, 
               0, 
               idDataGroup,
               pAccountToEntityXrefObject ) <= WARNING &&
            pAccountToEntityXrefObject)
         {
            pAccountEntityXrefObject->getField(ifds::EntityId, dstrEntityId, idDataGroup);
            pAccountToEntityXrefObject->getField(ifds::EntityId, dstrEntityIdTo, idDataGroup);
         }
         if(!dstrEntityId.empty() && 
            !dstrEntityIdTo.empty() && 
            getWorkSession().getEntity(idDataGroup, dstrEntityId, pAnnuitantEntity) <= WARNING &&
            pAnnuitantEntity &&
            getWorkSession().getEntity(idDataGroup, dstrEntityIdTo, pAnnuitantEntityTo) <= WARNING &&
            pAnnuitantEntityTo)
         {
            EntityIdsList* pEntityIdsList = NULL, *pToEntityIdsList = NULL;

            if(pAnnuitantEntity->getEntityIdsList(pEntityIdsList, idDataGroup) <= WARNING &&
               pEntityIdsList != NULL && 
               pAnnuitantEntityTo->getEntityIdsList(pToEntityIdsList, idDataGroup) <= WARNING &&
               pToEntityIdsList != NULL)
            {
               pEntityIdsList->getIdByType(IDS::SIN, idDataGroup, sinFrom);
               pToEntityIdsList->getIdByType(IDS::SIN, idDataGroup, sinTo);
            }
         }
         
         sinFrom.strip().upperCase();
         sinTo.strip().upperCase();

         bIsGuaranteeFeeOverrideAllowed = sinFrom != sinTo;
      }
      else
      {
         bIsGuaranteeFeeOverrideAllowed = true;
      }

      bIsGuaranteeFeeOverrideAllowed = bIsGuaranteeFeeOverrideAllowed && !hasAllocations (idDataGroup);      
      if (bIsGuaranteeFeeOverrideAllowed)
      {
         DString fundCode, 
            classCode, 
            toFundCode, 
            toClassCode;

         getField (ifds::FromFund, fundCode, idDataGroup, false );
         getField (ifds::FromClass, classCode, idDataGroup, false);
         getField( ifds::ToFund, toFundCode, idDataGroup, false);
         getField( ifds::ToClass, toClassCode, idDataGroup, false);

         fundCode.strip().upperCase();
         classCode.strip().upperCase();
         toFundCode.strip().upperCase();
         toClassCode.strip().upperCase();

         bIsGuaranteeFeeOverrideAllowed = ((fundCode == toFundCode) && (classCode == toClassCode));

         if (!fundCode.empty() && !toFundCode.empty())
         {
            bIsGuaranteeFeeOverrideAllowed = bIsGuaranteeFeeOverrideAllowed && 
                                             isSEGFund (fundCode) && 
                                             isSEGFund (toFundCode);
         }
      }
   }

   return bIsGuaranteeFeeOverrideAllowed;
}

//******************************************************************************
SEVERITY Transfer::withholdingTaxRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("withholdingTaxRelatedChanges"));
            
   // for IWT environment
   if( getWorkSession().isIWTClient( idDataGroup ) )
   {
      MFAccount *pMFAccount = NULL;
      DString dstrAccountNum;
      getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
           pMFAccount)
      {      
         if (!pMFAccount->isIWTNonTaxable(idDataGroup))
         {
            _blTaxable = true;
         }
      }
   }

   if ( !_blTaxable )
   {
      setField (ifds::OverrideTax, N, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateMoneyMktFund(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMoneyMktFund"));

   DString dstrFromFund, dstrFromClass, dstrToFund, dstrToClass;
   bool bFullExchPrntToPrnt;

   getField(ifds::FromFund, dstrFromFund, idDataGroup);
   getField(ifds::FromClass, dstrFromClass, idDataGroup);
   getField(ifds::ToFund, dstrToFund, idDataGroup);
   getField(ifds::ToClass, dstrToClass, idDataGroup);
   bFullExchPrntToPrnt = isFullExchgParentFndClsToParentFndCls(idDataGroup, dstrFromFund, dstrFromClass, dstrToFund, dstrToClass);

   editCheckOnMMF( TRADETYPE::TRANSFER_OUT, bFullExchPrntToPrnt, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();	
}

//******************************************************************************
SEVERITY Transfer::PFCrystalisationRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("PFCrystalisationRelatedChanges "));

   DString dstrFromFund = NULL_STRING, 
      dstrToFund	= NULL_STRING, 
      dstrFromClass= NULL_STRING,
      dstrToClass	= NULL_STRING;

   getField (ifds::FromFund, dstrFromFund, idDataGroup, false);
   getField (ifds::FromClass, dstrFromClass, idDataGroup, false);
   getField (ifds::ToFund, dstrToFund, idDataGroup, false);
   getField (ifds::ToClass, dstrToClass, idDataGroup, false);

   bool bFromIsPF = getWorkSession ().isPerfFeeFund(dstrFromFund,dstrFromClass,idDataGroup);
   bool bToIsPF   = getWorkSession ().isPerfFeeFund(dstrToFund,dstrToClass,idDataGroup);
   bool bEnable   = bFromIsPF && bToIsPF;

   if( bFromIsPF && bToIsPF )
   {
      DString dstrRedCode;
      getField (ifds::RedCode, dstrRedCode, idDataGroup, false);
      if( dstrRedCode == I_("25") || dstrRedCode == I_("27") )
      {
         setFieldNoValidate (ifds::PFCrystalisation, I_("02"), idDataGroup, false, false, false);
      }
      else
      {
         setFieldNoValidate (ifds::PFCrystalisation, I_("03"), idDataGroup, false, false, false);
      }
   }
   else if( bFromIsPF && !bToIsPF )
   {
      setFieldNoValidate (ifds::PFCrystalisation, I_("03"), idDataGroup, false, false, false);
   }
   else
   {
      setFieldNoValidate (ifds::PFCrystalisation, I_("01"), idDataGroup, false, false, false);
   }
   setFieldReadOnly (ifds::PFCrystalisation, idDataGroup, !bEnable);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateFundForERISAAccount ( const DString &fundCode, 
                               const DString &classCode, 
                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundForERISAAccount"));

   bool bIsERISAAccount = false;
   DString toAccount;
   getField (ifds::AccountTo, toAccount, idDataGroup, false);
  
   if (!toAccount.empty())
   {
      MFAccount *pMFAccountTo = NULL;

      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                          toAccount, 
                                          pMFAccountTo) <= WARNING && 
            pMFAccountTo)
      {
         bIsERISAAccount = pMFAccountTo->isERISAAccount (idDataGroup);
      }
   }
   if( bIsERISAAccount )
   {
      if (isFundERISAProhibited(fundCode,classCode,idDataGroup))
      {
         getErrMsg ( IFASTERR::ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT,
                     CND::ERR_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT,
                     CND::WARN_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT,
                     idDataGroup );
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validatePerfFeeFromToClassesWithFund (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validatePerfFeeFromToClassesWithFund"));
   
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Transfer::validatePerfFeeFXRate (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validatePerfFeeFXRate"));
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateGuaranteesOverride (const DString& strValue,
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateGuaranteesOverride"));

   DString dstrGuaranteeCalcByRules;
   getWorkSession().getOption (ifds::GuaranteeCalcByRules, 
                               dstrGuaranteeCalcByRules, 
                               idDataGroup, 
                               false);

   if (isGuaranteeFeeOverrideAllowed (idDataGroup))
   {
      DString strGuaranteeOverride (strValue);
      strGuaranteeOverride.strip().upperCase();
      
      if (strGuaranteeOverride.empty())
      {
         ADDCONDITIONFROMFILE (CND::ERR_GUARANTEE_OVERRIDE_FLAG_IS_REQUIRED);
      }
      else if (!strGuaranteeOverride.empty() && strGuaranteeOverride == I_("Y"))
      {
         ADDCONDITIONFROMFILE( CND::WARN_GUARANTEE_OVERRIDE_FLAG_IS_YES );
      }
      else if (!strGuaranteeOverride.empty() && strGuaranteeOverride == I_("N"))
      {
         ADDCONDITIONFROMFILE( CND::WARN_GUARANTEE_OVERRIDE_FLAG_IS_NO );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateAcctFromToXEdit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAcctFromToXEdit"));

   DString dstrGuaranteeCalcByRules;
   getWorkSession().getOption (ifds::GuaranteeCalcByRules, 
                               dstrGuaranteeCalcByRules, 
                               idDataGroup, 
                               false);

   if (isGuaranteeFeeOverrideAllowed(idDataGroup))
   {
      MFAccount *pMFAccount = NULL;
      MFAccount *pMFAccountTo = NULL;

      DString dstrAccountNum,dstrAccountToNum;

      getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      getField (ifds::AccountTo, dstrAccountToNum, idDataGroup, false);
      dstrAccountNum.strip().upperCase();
      dstrAccountToNum.strip().upperCase();

      if( dstrAccountNum.empty() || dstrAccountToNum.empty())
      {
         return GETCURRENTHIGHESTSEVERITY();
      }

      if ((getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount) &&
         (getWorkSession().getMFAccount (idDataGroup, dstrAccountToNum, pMFAccountTo) <= WARNING && pMFAccountTo))
      {
         DString sinFrom,sinTo;
         pMFAccount->getIDOfSequenced01OfEntityObject(IDS::SIN, ENTITY_ANNUITANT, sinFrom, idDataGroup);
         pMFAccountTo->getIDOfSequenced01OfEntityObject(IDS::SIN, ENTITY_ANNUITANT, sinTo, idDataGroup);
         sinFrom.strip().upperCase();
         sinTo.strip().upperCase();

         if(sinFrom != sinTo )
         {
            ADDCONDITIONFROMFILE( CND::ERR_ANNUITANT_SIN_NOT_THE_SAME );
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//GIA-INA
//******************************************************************************
bool Transfer::isGIInvestmentListApplicable(const BFDataGroupId &idDataGroup)
{
   bool isGIAAttribAllowed = false;
   DString fundCode;
   getField (ifds::FromFund, fundCode, idDataGroup, false);

   if (!fundCode.empty())
   {
      FundMasterList *pFundMasterList (NULL);

      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList)
      {
         isGIAAttribAllowed = pFundMasterList->isGIAFund (fundCode);
      }
   }
   return isGIAAttribAllowed;
}

//******************************************************************************
bool Transfer::isMaturityInstrAllowed (const BFDataGroupId &idDataGroup)
{
   bool isMaturityInstrAllowed = false;
   DString fundCode;
   
   getField (ifds::ToFund, fundCode, idDataGroup, false);

   if (!fundCode.empty())
   {
      FundMasterList *pFundMasterList (NULL);

      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList)
      {
         isMaturityInstrAllowed = pFundMasterList->isGIAFund (fundCode);
      }
   }
   return isMaturityInstrAllowed;
}

//******************************************************************************
SEVERITY Transfer::validateAllSegTransfer (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAllSegTransfer"));

   DString dstrGuaranteeCalcByRules;
   getWorkSession().getOption (ifds::GuaranteeCalcByRules, 
                               dstrGuaranteeCalcByRules, 
                               idDataGroup, 
                               false);

   if (dstrGuaranteeCalcByRules.strip().upperCase() == I_("Y"))
   {
      DString fundCode, toFundCode, classCode, toClassCode, transType, transId;
      DString accountNum, toAccountNum, tradeDate;

      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      getField (ifds::FromFund, fundCode, idDataGroup, false );
      getField (ifds::FromClass, classCode, idDataGroup, false);
      getField (ifds::TradesTransType, transType, idDataGroup, false);
      getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
      getField (ifds::AccountTo, toAccountNum, idDataGroup, false );
      getField (ifds::TransId, transId, idDataGroup, false );
      fundCode.strip().upperCase();
      classCode.strip().upperCase();
      transType.strip().upperCase();
      accountNum.strip().upperCase();
      toAccountNum.strip().upperCase();
      tradeDate.strip().upperCase();
      transId.strip().upperCase();

      SEGTradeEntryValidation validationObj(*this);

      if (hasAllocations (idDataGroup))
      {
         TradeFundAllocList *pTradeFundAllocList = NULL;

         if (getFundAllocationList (pTradeFundAllocList, idDataGroup) <= WARNING &&pTradeFundAllocList)
         {
            TradeFundAlloc *pTradeFundAlloc = NULL;

            BFObjIter iter (*pTradeFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

            while (!iter.end ()) 
            {
               pTradeFundAlloc = dynamic_cast <TradeFundAlloc*> (iter.getObject ());

               if (pTradeFundAlloc)
               {
                  pTradeFundAlloc->getField (ifds::FundCode, toFundCode, idDataGroup);
                  pTradeFundAlloc->getField (ifds::ClassCode, toClassCode, idDataGroup);
                  toFundCode.strip().upperCase();
                  toClassCode.strip().upperCase();

                  if( validationObj.init(accountNum,
                                         fundCode,
                                         classCode,
                                         toAccountNum, // account to
                                         toFundCode, // fund to
                                         toClassCode, // class to
                                         tradeDate,
                                         I_("All"),
                                         transType,
                                         transId) <= WARNING )
                  {
                     DString strErrorCode;
                     validationObj.getField(ifds::WarnCode, strErrorCode, idDataGroup, false);
                     strErrorCode.strip().upperCase();

                     switch( strErrorCode.asInteger())
                     {
                        case 1019:
                        {
                           getErrMsg ( IFASTERR::LWA_OPTION_NOT_MATCH,
                                       CND::ERR_LWA_OPTION_NOT_MATCH, 
                                       CND::WARN_LWA_OPTION_NOT_MATCH, 
                                       idDataGroup);
                        }
                           break;
                        case 1086:
                        {
                           getErrMsg ( IFASTERR::ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME,
                                       CND::ERR_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME, 
                                       CND::WARN_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME, 
                                       idDataGroup);
                        }
                           break;
                        case 1224:
                        {
                           getErrMsg ( IFASTERR::TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED,
                                       CND::ERR_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED, 
                                       CND::WARN_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED, 
                                       idDataGroup);
                        }
                           break;
                        case 1225:
                        {
                           getErrMsg ( IFASTERR::LWA_AGE_RATE_IS_NOT_APPLICABLE,
                                       CND::ERR_LWA_AGE_RATE_IS_NOT_APPLICABLE, 
                                       CND::WARN_LWA_AGE_RATE_IS_NOT_APPLICABLE, 
                                       idDataGroup);
                        }
                           break;
                        case 1230:
                        {
                           getErrMsg ( IFASTERR::USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM,
                                       CND::ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM, 
                                       CND::WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM, 
                                       idDataGroup);
                        }
                           break;
                        default:
                           break;
                     }
                  }

               }
               ++iter;
            }
         }
      }
      else
      {
         getField( ifds::ToFund, toFundCode, idDataGroup, false);
         getField( ifds::ToClass, toClassCode, idDataGroup, false);
         toFundCode.strip().upperCase();
         toClassCode.strip().upperCase();

         if( validationObj.init(accountNum,
                                fundCode,
                                classCode,
                                toAccountNum, // account to
                                toFundCode, // fund to
                                toClassCode, // class to
                                tradeDate,
                                I_("All"),
                                transType,
                                transId) <= WARNING )
         {
            DString strErrorCode;
            validationObj.getField(ifds::WarnCode, strErrorCode, idDataGroup, false);
            strErrorCode.strip().upperCase();

            switch( strErrorCode.asInteger())
            {
               case 1019:
               {
                  getErrMsg ( IFASTERR::LWA_OPTION_NOT_MATCH,
                              CND::ERR_LWA_OPTION_NOT_MATCH, 
                              CND::WARN_LWA_OPTION_NOT_MATCH, 
                              idDataGroup);
               }
                  break;
               case 1086:
               {
                  getErrMsg ( IFASTERR::ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME,
                              CND::ERR_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME, 
                              CND::WARN_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME, 
                              idDataGroup);
               }
                  break;
               case 1224:
               {
                  getErrMsg ( IFASTERR::TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED,
                              CND::ERR_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED, 
                              CND::WARN_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED, 
                              idDataGroup);
               }
                  break;
               case 1225:
               {
                  getErrMsg ( IFASTERR::LWA_AGE_RATE_IS_NOT_APPLICABLE,
                              CND::ERR_LWA_AGE_RATE_IS_NOT_APPLICABLE, 
                              CND::WARN_LWA_AGE_RATE_IS_NOT_APPLICABLE, 
                              idDataGroup);
               }
                  break;
               case 1230:
               {
                  getErrMsg ( IFASTERR::USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM,
                              CND::ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM, 
                              CND::WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM, 
                              idDataGroup);
               }
                  break;
               default:
                  break;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateGuaranteesOverrideAcctFromTo(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateGuaranteesOverrideAcctFromTo"));

   if (isGuaranteeFeeOverrideAllowed (idDataGroup))
   {
      DString strGuaranteesOverride;
      getField(ifds::GuaranteesOverride, strGuaranteesOverride, idDataGroup, false );
      strGuaranteesOverride.strip().upperCase();

      if(strGuaranteesOverride == I_("N"))
      {
         MFAccount *pMFAccount (NULL),
            *pMFAccountTo (NULL);
         DString dstrAccountNum,
            dstrAccountToNum;

         getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
         getField (ifds::AccountTo, dstrAccountToNum, idDataGroup, false);
         dstrAccountNum.strip().upperCase();
         dstrAccountToNum.strip().upperCase();

         if ((getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount) &&
             (getWorkSession().getMFAccount (idDataGroup, dstrAccountToNum, pMFAccountTo) <= WARNING && pMFAccountTo))
         {
            DString ageInYearFrom,ageInMnthFrom,
               ageInYearTo,ageInMnthTo;

            pMFAccount->getAgeOfSequenced01OfEntityObject (ENTITY_ANNUITANT, ageInYearFrom, ageInMnthFrom, idDataGroup);
            pMFAccountTo->getAgeOfSequenced01OfEntityObject (ENTITY_ANNUITANT, ageInYearTo, ageInMnthTo, idDataGroup);

            if( ageInYearFrom != ageInYearTo || ageInMnthFrom != ageInMnthTo)
            {
               // raise error, P0203495 - changed to be rej-error.
               getErrMsg ( IFASTERR::TRFX_AGE_DIFF_NOT_ALLOWED,
                           CND::ERR_TRFX_AGE_DIFF_NOT_ALLOWED, 
                           CND::WARN_TRFX_AGE_DIFF_NOT_ALLOWED, 
                           idDataGroup);
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Transfer::RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("RDRAdviceRelatedChanges"));
   
   DString accountTo, toFund, toClass,tradeInDate;
   getField (ifds::AccountTo, accountTo, idDataGroup, false);
   getField (ifds::ToFund, toFund, idDataGroup, false);
   getField (ifds::ToClass, toClass, idDataGroup, false);
   getField (ifds::TradeInDate,tradeInDate,idDataGroup,false);
   
   setRDRAdviceFlag( TRADETYPE::TRANSFER_IN,
					 accountTo,
					 toFund,
					 toClass,
					 tradeInDate,
					 idDataGroup);
   
   return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
InPut :	BFDataGroupId &idDataGroup
Out :   None
Return: Severity 
Functionality: Check if the Deposit code and Redemption code for Unit conversionTrade 
			   is valid
******************************************************************************/
SEVERITY Transfer::validateRedCodeDepTypeUCTrade(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRedCodeDepTypeUCTrade"));
	DString dstrRedCode, dstrDepositType; 		 
	getField (ifds::RedCode, dstrRedCode, idDataGroup, false);
	getField (ifds::DepositType, dstrDepositType, idDataGroup, false);
	if(isExchange(idDataGroup) || isInterClassSwitch(idDataGroup))
	{
		if( (REDEMPTION_CODE_UC  == dstrRedCode     && DEPOSIT_CODE_UC    != dstrDepositType)  ||
		    (DEPOSIT_CODE_UC     == dstrDepositType && REDEMPTION_CODE_UC != dstrRedCode  ))
		{
			DString idiStr;
			addIDITagValue (idiStr, I_("DEP_CODE"), dstrDepositType);
			addIDITagValue (idiStr, I_("RED_CODE"), dstrRedCode);
			ADDCONDITIONFROMFILEIDI (CND::ERR_REDEMPTION_DEPOSIT_CODE_NOT_VALID,idiStr);
		}
	}
	else
		Trade::validateRedCodeDepTypeUCTrade(idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateNMCRContractTypeAndVersion ( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateContractTypeAndVersion"));

	DString dstrAccountNum, dstrContractType, dstrContractVer;	
	getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	bool bNMCRContract = getContractTypeAndVersion (idDataGroup, dstrAccountNum, dstrContractType, dstrContractVer);

	DString dstrAccountTo, dstrContractTypeTo, dstrContractVerTo;
	getField(ifds::AccountTo, dstrAccountTo, idDataGroup, false);
	bool bNMCRContractTo = getContractTypeAndVersion (idDataGroup, dstrAccountTo, dstrContractTypeTo, dstrContractVerTo);	
		
	if (bNMCRContract && bNMCRContractTo && !dstrContractType.empty() && !dstrContractVer.empty() && !dstrContractTypeTo.empty() && !dstrContractVerTo.empty()) 
	{
		bool bSameNMCRContractType = (dstrContractType == dstrContractTypeTo) ? true : false;
		bool bSameNMCRContractVersion = (dstrContractVer.asInteger() == dstrContractVerTo.asInteger()) ? true : false;

		if (!bSameNMCRContractType || !bSameNMCRContractVersion) 
		{
			getErrMsg ( IFASTERR::TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME,
						CND::ERR_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME,
						CND::WARN_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME,
						idDataGroup,
						NULL_STRING);
		} 
		else 
        {
            bool bValidateAgeAndGender = true;
            DString strGuaranteesOverride;

            getField(ifds::GuaranteesOverride, strGuaranteesOverride, idDataGroup, false );
            strGuaranteesOverride.strip().upperCase();

			if (isGuaranteeFeeOverrideAllowed(idDataGroup))
			{
				if(strGuaranteesOverride == I_("Y")) // Y = Guarantee as Purchase, N = Carry Over Guarantee
					bValidateAgeAndGender = false;
			}

            if (!strGuaranteesOverride.empty())
            {
                /* The user should not have been able to place a trade as the new annuitant's age under the new AVIE 2 
                   contract is below 50 years old.*/

                validateAnnuitantAgeForToAcct(idDataGroup);
            }

            if (strGuaranteesOverride == I_("N"))
            {
                /* The validation based on AGE + GENDER did not work here. 
                   We can only do a Carry-over Guarantee when the annuitant is the same in the old account and 
                   the new account.*/

                validateAnnuitantSINsForFromToAcct(idDataGroup);
            }
            else if (bValidateAgeAndGender)
            {
                validateAgeAndGender ( idDataGroup );
            }
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY Transfer::validateAnnuitantSINsForFromToAcct(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateAnnuitantSINsForFromToAcct"));

    DString dstrFromAccount, dstrToAccount, dstrFromSIN, dstrToSIN;
    MFAccount *pFromMFAccount = NULL, *pToMFAccount = NULL;

    getField(ifds::AccountNum, dstrFromAccount, idDataGroup);
    dstrFromAccount.strip().stripLeading('0');

    getField(ifds::AccountTo, dstrToAccount, idDataGroup);
    dstrFromAccount.strip().stripLeading('0');

    if (getWorkSession().getMFAccount(idDataGroup, dstrFromAccount, pFromMFAccount) <= WARNING && pFromMFAccount &&
        getWorkSession().getMFAccount(idDataGroup, dstrToAccount, pToMFAccount) <= WARNING && pToMFAccount)
    {
        pFromMFAccount->getIDOfSequenced01OfEntityObject(IDS::SIN, ENTITY_ACCOUNTHOLDER, dstrFromSIN, idDataGroup);
        dstrFromSIN.strip().upperCase();

        pToMFAccount->getIDOfSequenced01OfEntityObject(IDS::SIN, ENTITY_ACCOUNTHOLDER, dstrToSIN, idDataGroup);
        dstrToSIN.strip().upperCase();

        if (!dstrFromSIN.empty() && !dstrToSIN.empty() && dstrFromSIN != dstrToSIN)
        {
            getErrMsg(IFASTERR::ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME,
                CND::ERR_ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME, 
                CND::WARN_ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME, 
                idDataGroup);
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY Transfer::validateAnnuitantAgeForToAcct(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateAnnuitantAgeForToAcct"));

    MFAccount *pMFAccountTo(NULL);
    DString dstrAccountToNum;

    getField(ifds::AccountTo, dstrAccountToNum, idDataGroup, false);
    dstrAccountToNum.strip().upperCase();

    if (getWorkSession().getMFAccount(idDataGroup, dstrAccountToNum, pMFAccountTo) <= WARNING && pMFAccountTo)
    {
        DString ageInYearTo,ageInMnthTo;

        pMFAccountTo->getAgeOfSequenced01OfEntityObject(ENTITY_ANNUITANT, ageInYearTo, ageInMnthTo, idDataGroup);

        if (ageInYearTo < 50)
        {
            getErrMsg(IFASTERR::ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS,
                CND::ERR_ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS, 
                CND::WARN_ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS, 
                idDataGroup);
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateAgeAndGender ( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateAgeAndGender"));	

	DString dstrAccountNum, dstrAnnuitantYoungerAge, dstrEntityId, dstrGender;
	MFAccount *pMFAccount = NULL;
	Entity *pEntity = NULL;

	getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);	
	if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING)
	{ 		   
		pMFAccount->getAnnuitantYoungerAge( dstrAnnuitantYoungerAge, idDataGroup );
		pMFAccount->GetEntityIdForAcctOwnerSeq1( idDataGroup, dstrEntityId );
		if ( getWorkSession().getEntity ( idDataGroup, dstrEntityId, pEntity) <= WARNING && pEntity)
		{               
			pEntity->getGender( dstrGender, idDataGroup );			
		}
	}

	DString dstrAccountTo, dstrAnnuitantYoungerAgeTo, dstrEntityIdTo, dstrGenderTo;
	MFAccount *pMFAccountTo = NULL;
	Entity *pEntityTo = NULL;

	getField(ifds::AccountTo, dstrAccountTo, idDataGroup, false);	
	if (getWorkSession().getMFAccount (idDataGroup, dstrAccountTo, pMFAccountTo) <= WARNING)
	{ 		  
		pMFAccountTo->getAnnuitantYoungerAge( dstrAnnuitantYoungerAgeTo, idDataGroup );
		pMFAccountTo->GetEntityIdForAcctOwnerSeq1( idDataGroup, dstrEntityIdTo );
		if ( getWorkSession().getEntity ( idDataGroup, dstrEntityIdTo, pEntityTo) <= WARNING && pEntityTo)
		{               
			pEntityTo->getGender( dstrGenderTo, idDataGroup );
		}
	}

	if (!dstrAnnuitantYoungerAge.empty() && !dstrAnnuitantYoungerAgeTo.empty()) 
	{
		bool bAnnuitantYoungerAge = (dstrAnnuitantYoungerAge.asInteger() == dstrAnnuitantYoungerAgeTo.asInteger()) ? true : false;	 
		bool bGender = true;		

		if (pMFAccount->isSingle(idDataGroup) && pMFAccountTo->isSingle(idDataGroup) && !dstrGender.empty() && !dstrGenderTo.empty())
		{
			bGender = (dstrGender == dstrGenderTo) ? true : false;
		}

		if (!bAnnuitantYoungerAge || !bGender) {

			getErrMsg ( IFASTERR::TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME,
						CND::ERR_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME,
						CND::WARN_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME,
						idDataGroup,
						NULL_STRING);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
 Input: DataGroup
 OutPut:None
 Return:Bool
 Functionality:Checks if the transtype is excluded from AllowableTransferValidation
			   based on the env level configuration	of indicator code
******************************************************************************/
bool  Transfer::bskipAllowableTransferValidation(const BFDataGroupId &idDataGroup)
{
 DString dstrTransType, dstrSkipAllowableTransferValidation, dstrIndcatorCode;
 getField(ifds::TradesTransType, dstrTransType, idDataGroup, false);
 getWorkSession().getOption ( ifds::AllowableTransferValidation, dstrSkipAllowableTransferValidation, 
                              idDataGroup, false );
 dstrSkipAllowableTransferValidation.stripAll();
 //Extract the Indicator code from the TradesTransType
 DString::size_type pos = dstrTransType.length();
 dstrIndcatorCode = dstrTransType.substr(TRANS_TYPE_LENGTH, pos);
 return ( DSTCommonFunctions::codeInList (dstrIndcatorCode, dstrSkipAllowableTransferValidation ));

}

//******************************************************************************
SEVERITY Transfer::validateAnnuitantGender (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateAnnuitantGender"));

	DString dstrAccount;
	getField (ifds::AccountTo, dstrAccount, idDataGroup, false); 

	Trade::validateAnnuitantGender (idDataGroup, dstrAccount);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Transfer::getContractTypeAndVersion ( const BFDataGroupId &idDataGroup,
										   const DString &dstrAccountNum,	
										   DString &contractType, 
										   DString &contractVer)
{	
	MFAccount *pMFAccount = NULL;
	ContractInfoList* pContractInfoList = NULL;
	DString fundCode, classCode;
	bool bNMCRContract = false;	
	
	if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING)
	{
		TradeFundAllocList *pTradeFundAllocList = NULL;
		if ( getFundAllocationList (pTradeFundAllocList, idDataGroup, false) <= WARNING && pTradeFundAllocList )
		{
			TradeFundAlloc *pTradeFundAlloc = NULL;
			BFObjIter iter (*pTradeFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
			while (!iter.end ()) 
			{
				iter.getObject()->getField (ifds::FundCode, fundCode, idDataGroup);
				iter.getObject()->getField (ifds::ClassCode, classCode, idDataGroup);
				bNMCRContract = hasNMCRContract( pMFAccount, fundCode, classCode, contractType, contractVer, idDataGroup);
				if ( bNMCRContract )
					break;
				++iter;
			}
		}
	}

	return (bNMCRContract);
}

//******************************************************************************
SEVERITY Transfer::validateTwitchAgaintAMS(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTwitchAgaintAMS"));

   DString toFund, toClass, fromFund, fromClass, accountFrom, accountTo;

   getField(ifds::AccountNum, accountFrom, idDataGroup);
   getField(ifds::AccountTo, accountTo, idDataGroup);

   if ( accountFrom.strip().upperCase() == accountTo.strip().upperCase() )
   {
      return GETCURRENTHIGHESTSEVERITY ();
   }

   MFAccount *pMFAccountTo = nullptr;
   if (getWorkSession().getMFAccount (idDataGroup, accountTo, pMFAccountTo) <= WARNING &&
      pMFAccountTo &&
      !pMFAccountTo->isAMSAccount(idDataGroup))
   {
      getField(ifds::FromFund, fromFund, idDataGroup);
      getField(ifds::FromClass, fromClass, idDataGroup);
      getField(ifds::ToFund, toFund, idDataGroup);
      getField(ifds::ToClass, toClass, idDataGroup);

      // receiving fund
      FundDetail *pToFundDetail = nullptr,*pFromFundDetail = nullptr;

      if (getWorkSession().getFundDetail(toFund, toClass, idDataGroup, pToFundDetail) && pToFundDetail &&
         pToFundDetail->isAMSParentFund(idDataGroup))
      {
         CND::CIFast_IFast_ifastcbo_warn_parent_fund_is_not_allowed warnCond;
         CND::CIFast_IFast_ifastcbo_err_parent_fund_is_not_allowed errCond;

         MFCanBFCbo::getErrMsg (IFASTERR::PARENT_FUND_IS_NOT_ALLOWED,
                                 errCond,
                                 warnCond,
                                 idDataGroup);
      }

      // relinquishing fund
      if (getWorkSession().getFundDetail(fromFund, fromClass, idDataGroup, pFromFundDetail) && pFromFundDetail &&
         pFromFundDetail->isAMSParentFund(idDataGroup))
      {
         CND::CIFast_IFast_ifastcbo_warn_parent_fund_is_not_allowed warnCond;
         CND::CIFast_IFast_ifastcbo_err_parent_fund_is_not_allowed errCond;

         MFCanBFCbo::getErrMsg (IFASTERR::PARENT_FUND_IS_NOT_ALLOWED,
                                 errCond,
                                 warnCond,
                                 idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
bool Transfer::setCashDateUpdatable( DString &tradeDate, const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setCashDateUpdatable"));

	DString fundCode, classCode, cashDateOverride, lastValDate;
	bool blReadOnly = true;

	getField (ifds::ToFund, fundCode,  idDataGroup, false);
	getField (ifds::ToClass, classCode, idDataGroup, false);

	getWorkSession().getOption (ifds::OrderUserOverride, cashDateOverride, BF::HOST, false); // OrdEntryUserOverride attribute in PendingTradeCashDate function control: 01-no override, 02-override backdated trades, 03-override all	

	if (!fundCode.strip ().empty () && !classCode.strip ().empty ())
	{
		// Check if transaction is backdated
		if ( (cashDateOverride != I_("03") &&
			  getFundField ( fundCode, 
							 classCode, 
							 ifds::LastValDate, 
							 lastValDate) <= WARNING &&
							 DSTCommonFunctions::CompareDates (tradeDate, lastValDate) == DSTCommonFunctions::FIRST_EARLIER ) ||
			 (cashDateOverride == I_("03")) )			
		{
			FundMasterList *pFundMasterList = NULL;
			if ( getMgmtCo ().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList)
			{
				FundMaster *pFundMaster = NULL;
				if ( pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster) && pFundMaster)
				{
					blReadOnly = !isCashDateUpdatable (pFundMaster, idDataGroup);
				}
			}
		}
	}

	return blReadOnly;

}
//******************************************************************************
SEVERITY Transfer::validateCashDateToFundMandatory (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateCashDateMandatory")); 

	// Default condition
	SEVERITY sevRtn = NO_CONDITION;

	DString tradeDate, fundCode, classCode, cashDateOverride, lastValDate;

	getField( ifds::EffectiveDate, tradeDate,idDataGroup, false);
	getField (ifds::ToFund, fundCode,  idDataGroup);
	getField (ifds::ToClass, classCode, idDataGroup);

	getWorkSession().getOption (ifds::OrderUserOverride, cashDateOverride, BF::HOST, false); // OrdEntryUserOverride attribute in PendingTradeCashDate function control: 01-no override, 02-override backdated trades, 03-override all	

	if (!fundCode.strip ().empty () && !classCode.strip ().empty ())
	{
		getField (ifds::EffectiveDate, tradeDate, idDataGroup);
		// Check if transaction is backdated
		if ( (cashDateOverride != I_("03") &&
			  getFundField ( fundCode, 
							 classCode, 
							 ifds::LastValDate, 
							 lastValDate) <= WARNING &&
							 DSTCommonFunctions::CompareDates (tradeDate, lastValDate) == DSTCommonFunctions::FIRST_EARLIER ) ||
			 (cashDateOverride == I_("03") &&
			  getFundField ( fundCode, 
							 classCode, 
							 ifds::LastValDate, 
							 lastValDate) <= WARNING &&
							 (DSTCommonFunctions::CompareDates (tradeDate, lastValDate) == DSTCommonFunctions::FIRST_EARLIER || 
							  DSTCommonFunctions::CompareDates (tradeDate, lastValDate) == DSTCommonFunctions::EQUAL)) )			
		{
			FundMasterList *pFundMasterList = NULL;
			if ( getMgmtCo ().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList)
			{
				FundMaster *pFundMaster = NULL;
				if ( pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster) &&
					 pFundMaster  &&
					 isCashDateUpdatable (pFundMaster, idDataGroup))
				{
					DString emptyDate, dstrCashdate;
					getWorkSession().getDateInHostFormat (emptyDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
					getField (ifds::CashDate, dstrCashdate, idDataGroup, false);

					if (dstrCashdate.compare(emptyDate)== 0)
					{
						// 1941 - Cash Date is mandatory for Backdated Trades.
						getErrMsg(IFASTERR::CASH_DATE_MANDATORY,
								  CND::ERR_CASH_DATE_MANDATORY,
								  CND::WARN_CASH_DATE_MANDATORY,
								  idDataGroup);
					}
				}
			}
		}
	}

return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Transfer::validateUnusualTrading (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateUnusualTrading"));
	
	DString dstrAccountNum,
			dstrFundCode,
			dstrClassCode,
			dstrTransType,
			dstrAmount,
			dstrAmtType,
			dstrEffectiveDate,
			dstrSettleCurrency,
			dstrExchRate,
			dstrBrokerCode,
			dstrBranchCode,
			dstrSalesRepcode,
			dstrDepositType,
			dstrTradeDate,
			dstrCurrency,
			dstrOrderType,
			dstrFromFundcode,
			dstrFromClassCode,
			dstrFromAccount,
			dstrTradeInDate;
	
	getField (ifds::FromFund, dstrFromFundcode, idDataGroup, false);
	getField (ifds::FromClass, dstrFromClassCode, idDataGroup, false);
	getField (ifds::AccountNum, dstrFromAccount, idDataGroup, false);

	getField (ifds::AmtType, dstrAmtType, idDataGroup);
	getField (ifds::Amount, dstrAmount, idDataGroup);
	getField (ifds::ToFund, dstrFundCode, idDataGroup);
	getField (ifds::ToClass, dstrClassCode, idDataGroup);
	getField (ifds::TradesTransType, dstrTransType, idDataGroup);
	getField (ifds::EffectiveDate, dstrTradeDate, idDataGroup, false);
	getField (ifds::FromCurrency, dstrCurrency, idDataGroup, false);
	getField (ifds::OrderType, dstrOrderType, idDataGroup );
	getField (ifds::ExchRate, dstrExchRate, idDataGroup, false);
	getField (ifds::AccountTo, dstrAccountNum, idDataGroup, false);
	getField (ifds::DepositType, dstrDepositType, idDataGroup);
	getField (ifds::TradeInDate, dstrTradeInDate, idDataGroup,false);


	MFAccount *pMFAccountTo = NULL;

	if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccountTo) <= WARNING && pMFAccountTo)
	{
		pMFAccountTo->getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup); 
		pMFAccountTo->getField (ifds::BranchCode, dstrBranchCode, idDataGroup);
		pMFAccountTo->getField (ifds::Slsrep, dstrSalesRepcode, idDataGroup);
	}


	UnusualTradingValidation *pUnusualTradingValidation = NULL;
      DString strKey = 
         I_("Account=")       + dstrFromAccount +
         I_(";TransType=")    + dstrTransType +
         I_(";FundCode=")     + dstrFromFundcode  +
         I_(";ClassCode=")    + dstrFromClassCode +
         I_(";AmtType=")      + dstrAmtType   +
         I_(";Amount=")       + dstrAmount    +
         I_(";Currency=")     + dstrCurrency  +
         I_(";Broker=")       + dstrBrokerCode    +
         I_(";Branch=")       + dstrBranchCode    +
         I_(";SlsRep=")       + dstrSalesRepcode    +
         I_(";TradeDate=")    + dstrTradeDate +
		 I_(";DepositType=")  + dstrDepositType +
		 I_(";OrderType=")    + dstrOrderType +
		 I_(";ToFundCode=")   + dstrFundCode  +
		 I_(";ToClassCode=")  + dstrClassCode +
		 I_(";ToAccount=")     + dstrAccountNum +
		 I_(";TradeInDate=")  + dstrTradeInDate ;

      pUnusualTradingValidation = 
            dynamic_cast<UnusualTradingValidation*> (getObject (strKey, idDataGroup));

      if (!pUnusualTradingValidation)
      {
         pUnusualTradingValidation = new UnusualTradingValidation (*this);
         if ( pUnusualTradingValidation->init ( dstrFromAccount, 
                                        dstrFromFundcode, 
                                        dstrFromClassCode, 
                                        dstrTransType, 
                                        dstrAmtType,
                                        dstrAmount, 
										dstrTradeDate, 
										dstrCurrency, 
										dstrExchRate,
										dstrBrokerCode,
										dstrBranchCode,
										dstrSalesRepcode,
										NULL_STRING,
										NULL_STRING,
										dstrDepositType,
										dstrOrderType,
										dstrFundCode,
										dstrClassCode,
										dstrAccountNum,
										dstrTradeInDate) <= WARNING)
         {
            setObject (pUnusualTradingValidation, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
         }
         else
         {
            delete pUnusualTradingValidation;
            pUnusualTradingValidation = NULL;
         }
      }
      if (pUnusualTradingValidation)
      {
         pUnusualTradingValidation->addConditions ();
      }

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Transfer::tradeInDateRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "tradeInDateRelatedChanges" ));
 
   DString fromFund,
			toFund,
			fromClass,
			toClass;;
		 
   getField (ifds::FromFund, fromFund, idDataGroup, false );
   getField (ifds::ToFund, toFund, idDataGroup, false );
   getField (ifds::FromClass, fromClass, idDataGroup, false );
   getField (ifds::ToClass, toClass, idDataGroup, false );

   if (fromFund == toFund && fromClass == toClass)
   {
		setFieldReadOnly (ifds::TradeInDate, idDataGroup, true);
   }
      return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************************************************
SEVERITY Transfer::initPriceTypesList(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initPriceTypesList"));

	DString dstrFromFundCode,dstrFromClassCode,dstrToFundCode,dstrToClassCode;

	getField (ifds::FromFund,dstrFromFundCode, idDataGroup, false );
	getField (ifds::FromClass,dstrFromClassCode, idDataGroup, false );
	getField (ifds::ToFund,dstrToFundCode, idDataGroup, false );
	getField (ifds::ToClass,dstrToClassCode, idDataGroup, false );

	if ((dstrFromFundCode != NULL_STRING && dstrFromClassCode != NULL_STRING )&&
		(dstrToFundCode != NULL_STRING && dstrToClassCode != NULL_STRING))
	{
		DString dstrGroupCodeSubsList,dstrFromPriceTypesList,dstrToPriceTypesList,dstrPriceTypesList;
		setFieldReadOnly( ifds::PricingCode, idDataGroup, false );
		setFieldReadOnly( ifds::PriceInCode, idDataGroup, false );

		BFProperties *pProperties = getFieldProperties(ifds::PricingCode, idDataGroup);
		if(pProperties)
		{
			 pProperties->reinitAllSubstValues();
			 pProperties->getAllSubstituteValues(dstrGroupCodeSubsList);
		}
		DString dstrBufferName;
		FundDetailList * pFundDetailList = NULL;
		getMgmtCo().getFundDetailList(pFundDetailList);

		if(pFundDetailList )
		{  
			FundDetail* pFundDetail = NULL;
			dstrFromFundCode.strip().upperCase();
			dstrFromClassCode.strip().upperCase();
			pFundDetailList->getFundDetail(dstrFromFundCode,dstrFromClassCode,idDataGroup,pFundDetail);
			if( pFundDetail )
			{
				pFundDetail->getField(ifds::PriceTypes,dstrFromPriceTypesList,idDataGroup,false);
			}
			dstrToFundCode.strip().upperCase();
			dstrToClassCode.strip().upperCase();
			pFundDetailList->getFundDetail(dstrToFundCode,dstrToClassCode,idDataGroup,pFundDetail);
			if( pFundDetail )
			{
				pFundDetail->getField(ifds::PriceTypes,dstrToPriceTypesList,idDataGroup,false);
			}
			std::list<DString> FromPriceTypesList,
				ToPriceTypesList,
				CommonPriceTypesList;
			while (dstrFromPriceTypesList != NULL_STRING || dstrToPriceTypesList != NULL_STRING)
			{
				DString::size_type pos = 0;
				DString dstrFromPriceType ,dstrToPriceType;
				if(dstrFromPriceTypesList != NULL_STRING)
				{
					EXTRACT_VALUE(dstrFromPriceTypesList, dstrFromPriceType);
					CHOP_STRING(dstrFromPriceTypesList);
					FromPriceTypesList.push_back(dstrFromPriceType);			
				}
				if(dstrToPriceTypesList != NULL_STRING)
				{
					EXTRACT_VALUE(dstrToPriceTypesList, dstrToPriceType);
					CHOP_STRING(dstrToPriceTypesList);
				    ToPriceTypesList.push_back(dstrToPriceType);					
				}		
			}
			std::set_intersection(FromPriceTypesList.begin(),FromPriceTypesList.end(),
				ToPriceTypesList.begin(),ToPriceTypesList.end(),std::back_inserter(CommonPriceTypesList));

			for( std::list<DString>::iterator itr = CommonPriceTypesList.begin();itr != CommonPriceTypesList.end();itr++ )
			{
				if(dstrPriceTypesList == NULL_STRING)
				{
					dstrPriceTypesList = *itr ;
				}
				else
				{
					dstrPriceTypesList +=  I_(",") + *itr ;
				}			
			}
		}
		else
		{
			dstrPriceTypesList = dstrFromPriceTypesList;
		}

		DString tmpGroupCodeSubsList = dstrGroupCodeSubsList;

		while (tmpGroupCodeSubsList != NULL_STRING)
		{
			DString::size_type pos = 0;
			DString dstrGroupCodeDesc, dstrGroupCode;

			EXTRACT_VALUE_BY_DELIMITER(tmpGroupCodeSubsList, dstrGroupCodeDesc, I_(";"));
			CHOP_STRING2(tmpGroupCodeSubsList, I_(";"));

			EXTRACT_VALUE_BY_DELIMITER(dstrGroupCodeDesc, dstrGroupCode, I_("="));
			dstrGroupCode.stripLeading(I_('0'));

			if (!DSTCommonFunctions::codeInList(dstrGroupCode, dstrPriceTypesList))
			{
				dstrGroupCodeSubsList = removeItemFromSubtList(dstrGroupCodeSubsList, dstrGroupCode);
			}

		}  
		dstrBufferName.append( I_("= ;"));
		dstrGroupCodeSubsList.insert(0,dstrBufferName.c_str());
		setFieldAllSubstituteValues(ifds::PriceInCode, idDataGroup, NULL_STRING);

		setFieldAllSubstituteValues(ifds::PricingCode, idDataGroup, dstrGroupCodeSubsList);		
		setFieldAllSubstituteValues(ifds::PriceInCode, idDataGroup, dstrGroupCodeSubsList);	
			
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Transfer::validateSuspendedFund (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSuspendedFund"));

	DString strRunMode, 
			strFromFundCode,
			strFromClassCode, 
			strTransType, 
			strDealDate, 
			strDealTime,
			strFundToCode, 
			strClassToCode,
			strDepositType, 
			strRedCode;

	strRunMode = I_("A");
	getField (ifds::FromFund, strFromFundCode, idDataGroup);
	getField (ifds::FromClass,strFromClassCode, idDataGroup);
	getField (ifds::TradesTransType, strTransType, idDataGroup);
	getField (ifds::DealDate, strDealDate, idDataGroup);
	getField (ifds::DealTime, strDealTime, idDataGroup);
	getField (ifds::ToFund,strFundToCode, idDataGroup);
	getField (ifds::ToClass, strClassToCode, idDataGroup);
	getField (ifds::DepositType, strDepositType, idDataGroup);
	getField (ifds::RedCode, strRedCode, idDataGroup);

	FundSuspensionValidation *pFundSuspensionValidation = NULL;
	DString strKey = 
		I_("RunMode=")				+ strRunMode  +
		I_(";FromFundCode=")		+ strFromFundCode +
		I_(";FromClassCode=")       + strFromClassCode +
		I_(";TransType=")			+ strTransType +
		I_(";DealDate=")			+ strDealDate +
		I_(";DealTime=")			+ strDealTime +
		I_(";FundToCode=")			+ strFundToCode +
		I_(";ClassToCode=")			+ strClassToCode +
		I_(";DepositType=")			+ strDepositType ;
		I_(";RedCode=")				+ strRedCode ;

		pFundSuspensionValidation = 
            dynamic_cast<FundSuspensionValidation*> (getObject (strKey, idDataGroup));

      if (!pFundSuspensionValidation)
      {
         pFundSuspensionValidation = new FundSuspensionValidation (*this);
		 if ( pFundSuspensionValidation->init ( strRunMode, 
												strFromFundCode,
												strFromClassCode, 
												strTransType, 
												strDealDate, 
												strDealTime,
												strFundToCode, 
												strClassToCode,
												strDepositType, 
												strRedCode ) <= WARNING)
         {
            setObject (pFundSuspensionValidation, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
         }
         else
         {
            delete pFundSuspensionValidation;
            pFundSuspensionValidation = NULL;
         }
      }
      if (pFundSuspensionValidation)
      {
         pFundSuspensionValidation->addConditions ();
      }

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY Transfer::refreshIntradayPricing(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("refreshIntradayPricing"));
	if(isIntraDayPricingEnable(idDataGroup ) )
	{
		DString strRunMode,
			strFromFund,
			strFromClass,
			strToFund,
			strToClass,
			strDealDate,
			strDealTime,
			strTradeFromDate,
			strTradeInDate,
			dstrTrack,
			dstrPageName,
			dstrTransType,
			dstrPriceCode,
			dstrPriceCodeList,
			dstrPriceInCode,
			dstrPriceInCodeList,
			strCallingType;
		if(_bInitPending)
			strRunMode = I_("M") ;
		else
			strRunMode = I_("A") ;
		getField (ifds::FromFund, strFromFund, idDataGroup);
		getField (ifds::FromClass,strFromClass, idDataGroup);
		getField (ifds::ToFund,strToFund, idDataGroup, false );
		getField (ifds::ToClass,strToClass, idDataGroup, false );
		if(strFromFund.empty() || strFromClass.empty() || strToFund.empty() || strToClass.empty())
		{
			return GETCURRENTHIGHESTSEVERITY();
		}
		getField (ifds::DealDate, strDealDate, idDataGroup);
		getField (ifds::DealTime, strDealTime, idDataGroup);
		DString::size_type iPos = strDealTime.find (I_(":"));
		if(iPos != std::string::npos)
		{
			strDealTime.replace(iPos,1,NULL_STRING);
		}
		getField (ifds::EffectiveDate, strTradeFromDate, idDataGroup);
		getField (ifds::TradeInDate, strTradeInDate, idDataGroup);
		getField(ifds::TradesTransType, dstrTransType, idDataGroup, false);
		strCallingType=I_("IntraPrice");
		IntraDayPricing *pIntraDayPricing = NULL;
		DString strKey =
			I_("RunMode=")				+ strRunMode  +
			I_(";Fund=")				+ strFromFund +
			I_(";Class=")				+ strFromClass +
			I_(";FundTo=")				+ strToFund +
			I_(";ClassTo=")				+ strToClass +
			I_(";DealDate=")			+ strDealDate +
			I_(";DealTime=")			+ strDealTime +
			I_(";TradeDate=")			+ strTradeFromDate +
			I_(";TradeInDate=")			+ strTradeInDate +
			I_(";TransType=")			+ dstrTransType +
			I_(";CallingType=")			+ strCallingType ;
		pIntraDayPricing =
				dynamic_cast<IntraDayPricing*> (getObject (strKey, idDataGroup));
		if (!pIntraDayPricing)
		  {
			 pIntraDayPricing = new IntraDayPricing (*this);
			 if ( pIntraDayPricing->init ( strRunMode,
											strFromFund,
											strFromClass,
											strToFund,
											strToClass,
											strDealDate ,
											strDealTime ,
											strTradeFromDate,
											strTradeInDate,
											dstrTransType,
											strCallingType) <= WARNING)
			 {
				setObject (pIntraDayPricing, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
			 }
			 else
			 {
				delete pIntraDayPricing;
				pIntraDayPricing = NULL;
			 }
		  }
		if(pIntraDayPricing)
		{
			pIntraDayPricing->getField (ifds::PriceCode,dstrPriceCode, idDataGroup, false );
			pIntraDayPricing->getField (ifds::PriceCodeList,dstrPriceCodeList, idDataGroup, false );
			pIntraDayPricing->getField (ifds::PriceInCode,dstrPriceInCode, idDataGroup, false );
			pIntraDayPricing->getField (ifds::PriceInCodeList,dstrPriceInCodeList, idDataGroup, false );
			setFieldAllSubstituteValues(ifds::PricingCode, idDataGroup, NULL_STRING);
			setFieldAllSubstituteValues(ifds::PriceInCode, idDataGroup, NULL_STRING);
			initPriceTypesList(idDataGroup);
			if(dstrPriceCodeList.empty() && dstrPriceInCodeList.empty() )
			{
				setFieldNoValidate ( ifds::PricingCode, NULL_STRING, idDataGroup, false,
							   false,
							   true);
				setFieldNoValidate ( ifds::PriceInCode, NULL_STRING, idDataGroup, false,
							   false,
							   true);
				return GETCURRENTHIGHESTSEVERITY();
			}
			if(_bInitPending)
			{
				getField(ifds::PricingCode,dstrPriceCode,idDataGroup,false);
				getField(ifds::PriceInCode,dstrPriceInCode,idDataGroup,false);
			}
			if(!dstrPriceCodeList.empty() )
			{
				fromIntradayPricing(idDataGroup,dstrPriceCode,dstrPriceCodeList);	
			}
			else
			{
				setFieldNoValidate ( ifds::PricingCode, dstrPriceCode, idDataGroup, false,
							   false,
							   true);
			}
			if(!dstrPriceInCodeList.empty() )
			{
				toIntradayPricing(idDataGroup,dstrPriceInCode,dstrPriceInCodeList);	
			}
			else
			{
				setFieldNoValidate ( ifds::PriceInCode, dstrPriceInCode, idDataGroup, false,
							   false,
							   true);
			}
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************************************************
SEVERITY Transfer::toIntradayPricing(const BFDataGroupId &idDataGroup,DString dstrPriceCode,DString  dstrPriceCodeList)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("refreshIntradayPricing"));
	DString dstrGroupCodeSubsList, dstrFromPriceTypesList,dstrPriceTypesList;
	BFProperties *pProperties = getFieldProperties(ifds::PriceInCode, idDataGroup);
	if(pProperties)
	{
			pProperties->reinitAllSubstValues();
			pProperties->getAllSubstituteValues(dstrGroupCodeSubsList);
	}
	DString dstrBufferName;
	if(!dstrPriceCodeList.empty() )
	{
		setFieldAllSubstituteValues(ifds::PriceInCode, idDataGroup, NULL_STRING);
		dstrFromPriceTypesList=dstrPriceCodeList;
		std::list<DString> FromPriceTypesList;
		DString::size_type pos = 0;
		DString dstrFromPriceType ;
		while (dstrFromPriceTypesList != NULL_STRING)
		{
			EXTRACT_VALUE(dstrFromPriceTypesList, dstrFromPriceType);
			CHOP_STRING(dstrFromPriceTypesList);
			FromPriceTypesList.push_back(dstrFromPriceType);
		}
		for( std::list<DString>::iterator itr = FromPriceTypesList.begin();itr != FromPriceTypesList.end();itr++ )
		{
			if(dstrPriceTypesList == NULL_STRING)
			{
				dstrPriceTypesList = *itr ;
			}
			else
			{
				dstrPriceTypesList +=  I_(",") + *itr ;
			}
		}
	}
	else
	{
		dstrPriceTypesList = dstrFromPriceTypesList;
	}
	DString tmpGroupCodeSubsList = dstrGroupCodeSubsList;
	while (tmpGroupCodeSubsList != NULL_STRING)
	{
		DString::size_type pos = 0;
		DString dstrGroupCodeDesc, dstrGroupCode;
		EXTRACT_VALUE_BY_DELIMITER(tmpGroupCodeSubsList, dstrGroupCodeDesc, I_(";"));
		CHOP_STRING2(tmpGroupCodeSubsList, I_(";"));
		EXTRACT_VALUE_BY_DELIMITER(dstrGroupCodeDesc, dstrGroupCode, I_("="));
		dstrGroupCode.stripLeading(I_('0'));
		if (!DSTCommonFunctions::codeInList(dstrGroupCode, dstrPriceTypesList))
		{
			dstrGroupCodeSubsList = removeItemFromSubtList(dstrGroupCodeSubsList, dstrGroupCode);
		}
		setFieldAllSubstituteValues(ifds::PriceInCode, idDataGroup, NULL_STRING);
		setFieldAllSubstituteValues(ifds::PriceInCode, idDataGroup, dstrGroupCodeSubsList);
		setFieldNoValidate ( ifds::PriceInCode, dstrPriceCode, idDataGroup, false,
							   false,
							   true);
	}				
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************************************************
SEVERITY Transfer::hasWaiveGatingFund(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("hasWaiveGatingFund"));
	DString strRunMode, 
			strFromFund,			
			strTransType, 
			strDealDate,
			strCallingType,
			strToFund,
			dstrGateOverrideIndicator;
	if(_bInitPending)
	{
		strRunMode = I_("M") ;
		getField(ifds::GateOverrideIndicator,dstrGateOverrideIndicator,idDataGroup,false);
		if(!dstrGateOverrideIndicator.empty())
		{
			setWaiveGatingDropdown(idDataGroup,dstrGateOverrideIndicator);
			return GETCURRENTHIGHESTSEVERITY();
		}
	}		
	else
	{
		strRunMode = I_("A") ;	
	}	
	getField (ifds::FromFund, strFromFund, idDataGroup);
	getField (ifds::DealDate, strDealDate, idDataGroup);
	getField(ifds::TradesTransType, strTransType, idDataGroup, false);
	strCallingType=CALLING_TYPE;
	getField (ifds::ToFund,strToFund, idDataGroup, false );
	if(strFromFund.empty() || strToFund.empty() )
	{
		setFieldReadOnly( ifds::GateOverrideIndicator, idDataGroup, true );
		setFieldNoValidate ( ifds::GateOverrideIndicator, NULL_STRING, idDataGroup, false,
								false,
								true);
		return GETCURRENTHIGHESTSEVERITY();
	}
	if(strFromFund.compare(strToFund)==0)
	{
		setFieldReadOnly( ifds::GateOverrideIndicator, idDataGroup, true );
		setFieldNoValidate ( ifds::GateOverrideIndicator, NULL_STRING, idDataGroup, false,
							false,
							true);
		return GETCURRENTHIGHESTSEVERITY();
	}
	IntraDayPricing *pWaiveGating = NULL;
	DString strKey = 
		I_("RunMode=")				+ strRunMode  +
		I_(";FromFundCode=")		+ strFromFund +
		I_(";DealDate=")			+ strDealDate +
		I_(";TransType=")			+ strTransType+
		I_(";CallingType=")			+ strCallingType ;
		
	pWaiveGating = 
            dynamic_cast<IntraDayPricing*> (getObject (strKey, idDataGroup));
      if (!pWaiveGating)
      {
         pWaiveGating = new IntraDayPricing (*this);
		 if ( pWaiveGating->init (	strRunMode,
									strFromFund,
									NULL_STRING,
									NULL_STRING,
									NULL_STRING,
									strDealDate,
									NULL_STRING,
									NULL_STRING,
									NULL_STRING,
									strTransType,
									strCallingType) <= WARNING)
         {
            setObject (pWaiveGating, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
         }
         else
         {
            delete pWaiveGating;
            pWaiveGating = NULL;
         }
      }
	if(pWaiveGating)
	{
		pWaiveGating->getField (ifds::GateOverrideIndicator,dstrGateOverrideIndicator, idDataGroup, false );
		setWaiveGatingDropdown(idDataGroup,dstrGateOverrideIndicator);
	}
	else
	{
		setFieldReadOnly( ifds::GateOverrideIndicator, idDataGroup, true );
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Transfer::validateRDSPTrade (const BFDataGroupId &idDataGroup)
{

	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRDSPTrade"));

	DString dstrAccountNum, dstrAccountTo;

	getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	getField (ifds::AccountTo, dstrAccountTo, idDataGroup, false); 

	if (!dstrAccountNum.empty())
	{
		Trade::validateRDSPTrade (idDataGroup, dstrAccountNum);
	}

	if (!dstrAccountTo.empty())
	{
		Trade::validateRDSPTrade (idDataGroup, dstrAccountTo);
	}

	return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Transfer.cpp-arc  $
// 
//    Rev 1.359   Aug 01 2012 15:49:52   wp040132
// P0199891_FN01_Arrow_FAST_File - Code review comments - Removed redundant code
// 
//    Rev 1.358   Jul 27 2012 08:27:06   wp040132
// P0199891 _FN01_Arrow_FAST_File
// 
//    Rev 1.357   Jul 26 2012 10:45:04   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.356   Jun 08 2012 14:12:48   jankovii
// IN 2957854 - P0186477_FN05_03_Same transno. in distrib-delt to be used & changes to misc-info
// 
//    Rev 1.355   Jun 05 2012 11:42:16   dchatcha
// IN#2969458- Bypass  the editing for age difference if the new "Guarantees Override" flag set as "Yes"
// 
//    Rev 1.354   Apr 27 2012 16:52:28   wp040132
// P0197311 - Added error message for Transfer order of different fund/class.
// 
//    Rev 1.353   Apr 16 2012 23:20:44   popescu
// 2901148 - Gurantee Flag Override
// 
//    Rev 1.352   Apr 11 2012 17:43:06   dchatcha
// IN# 2914672 - P0186479 Issues on Guarantee Override field on Trade Entry screen
// 
//    Rev 1.351   Apr 11 2012 12:02:50   dchatcha
// IN# 2914672 - P0186479 Issues on Guarantee Override field on Trade Entry screen
// 
//    Rev 1.350   Apr 11 2012 11:40:16   dchatcha
// IN# 2901157 - Issue on SEG Trade Processing, revise allocation related logics.
// 
//    Rev 1.349   Apr 03 2012 10:02:38   dchatcha
// IN#2901157 - Issue on SEG Trade Processing
// 
//    Rev 1.348   Mar 27 2012 10:23:50   dchatcha
// P0186484 FN05 SEG Trade Processing, modify trade case, shoud not change guarantee override flag.
// 
//    Rev 1.347   Mar 27 2012 10:17:32   dchatcha
// P0186484 FN05 SEG Trade Processing.
// 
//    Rev 1.346   Mar 23 2012 16:02:38   wp040133
// In:2888340
// WO:750919
// PF Crystalisation error for various erorrs
// 
//    Rev 1.345   Mar 22 2012 15:27:20   dchatcha
// P0186484 FN 05 - SEG Trade Processing, transfer validations during fund\class changed.
// 
//    Rev 1.344   Mar 20 2012 16:43:14   if991250
// IN 2885623 - GI Money Oout
// 
//    Rev 1.343   Mar 19 2012 12:52:14   if991250
// RedemOrder default value
// 
//    Rev 1.342   Mar 19 2012 18:02:38   dchatcha
// P0186484 FN 05 - SEG Trade Processing, transfer validations against contract & etc.
// 
//    Rev 1.341   Mar 16 2012 13:47:22   dchatcha
// P0186484 FN05 - SEG Trade Processing, new validations.
// 
//    Rev 1.340   Mar 15 2012 18:01:14   if991250
// IN 2879297: Money Out
// 
//    Rev 1.339   Mar 13 2012 17:38:50   if991250
// IN 2879297: Money Out
// 
//    Rev 1.338   Mar 09 2012 16:40:52   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.337   Mar 06 2012 10:53:36   dchatcha
// P0186484 FN05 - SEG Trade Processing, new validation to make sure that only same fund\class would be allowed with guarantee override redcodes.
// 
//    Rev 1.336   Mar 05 2012 15:40:42   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.335   Mar 05 2012 12:19:50   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.334   Jan 20 2012 15:49:04   wp040027
// P0188394_Performance Fees - Order Entry
// 
//    Rev 1.333   Dec 08 2011 21:53:18   wp040032
// P0183989 - Money Market Non Receipt
// 
//    Rev 1.332   Oct 28 2011 04:40:28   kitticha
// PETP0188150 FN01 - Irish Withholding Tax Functionality.
// 
//    Rev 1.331   Oct 24 2011 07:19:00   kitticha
// PETP0188150 FN01 - Irish Withholding Tax Functionality.
// 
//    Rev 1.330   Oct 21 2011 09:43:28   kitticha
// PETP0188150 FN01 - Irish Withholding Tax Functionality.
// 
//    Rev 1.329   Oct 06 2011 10:48:40   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.328   Sep 02 2011 14:01:08   yingz
// fix 2609169. When WireOrder-TR/EX is set to NOT allow wire for exchange/transfer, the order type on trade screen will be set to direct.  
// 
//    Rev 1.327   Jul 22 2011 18:30:06   dchatcha
// P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting, code review.
// 
//    Rev 1.326   Jul 20 2011 18:07:10   dchatcha
// P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
// 
//    Rev 1.325   Dec 10 2010 15:20:04   jankovii
// Sync up: IN 2352462 - VT26860 - P0175377_FN01 RESP AIP for Joint A/c's Testing UAT-AIMVOL
// 
//    Rev 1.324   Nov 22 2010 13:22:48   jankovii
// PET175778 FN01 - Upstreaming Phase 2
// 
//    Rev 1.323   Sep 29 2010 11:31:00   jankovii
// PET0175377 FN01 - AIP for Joint RESP Account
// 
//    Rev 1.322   Sep 24 2010 14:31:22   jankovii
// PET0175377 FN01 - AIP for Joint RESP Account
// 
//    Rev 1.321   Sep 23 2010 08:09:40   dchatcha
// IN# 2257866 - Trade Entry Screen - Deposit Code 52 not displayed in dropdown.
// 
//    Rev 1.320   Aug 19 2010 23:22:10   dchatcha
// IN# 2222368 - Deposite code 80 81 should not be available for TR/EX trade type.
// 
//    Rev 1.319   Aug 02 2010 07:55:28   dchatcha
// IN# 2196483 - QESI phase 1 - PET165541 - cannot process exchanges.
// 
//    Rev 1.318   Jun 01 2010 15:09:44   jankovii
// IN 2117398 - All Fund Transfer.
// 
//    Rev 1.317   May 21 2010 22:15:28   dchatcha
// RESP-QESI Trading, Take validation logic for not applicable DT,RC for non QESI env back.
// 
//    Rev 1.316   May 20 2010 11:14:54   jankovii
// IN 2128208 - PETP0165541 - Transferring from a RESP to a non RESP account.
// 
//    Rev 1.315   May 19 2010 06:13:30   dchatcha
// RESP-QESI Trading, modified validation logic per Winnie's suggestions.
// 
//    Rev 1.314   May 13 2010 15:39:14   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.313   May 05 2010 16:23:14   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.312   May 04 2010 10:17:08   jankovii
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.311   Apr 29 2010 10:50:46   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.310   Apr 27 2010 15:03:42   popescu
// PET0165541 FN01 QESI RESP Trading - issue with stripping zeros on red codes and deposit types
// 
//    Rev 1.309   Apr 27 2010 02:55:36   kitticha
// PET0165541 FN01 QESI RESP Trading - Fix issue Transfer of notional error.
// 
//    Rev 1.308   Apr 26 2010 14:04:56   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.307   Apr 22 2010 10:30:58   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.306   Apr 22 2010 04:01:32   dchatcha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.305   Apr 21 2010 22:28:18   popescu
// RESP QESI restored isPSEEAPAllowed
// 
//    Rev 1.304   Apr 21 2010 14:09:02   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.303   Apr 20 2010 00:54:44   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - PSE/EAP   screen
// 
//    Rev 1.302   Apr 14 2010 09:45:08   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.301   Mar 27 2010 19:19:50   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.300   Mar 08 2010 13:21:04   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
// 
//    Rev 1.299   Dec 18 2009 10:41:40   jankovii
// PET0166095 FN01 Validations on Money Out Transactions
// 
//    Rev 1.298   Oct 26 2009 18:12:02   wutipong
// #1412263 - code refactor as per Zijian's suggestion
// 
//    Rev 1.297   Oct 22 2009 15:40:04   wutipong
// Inc#1412263 - GL-1287 (Pending Trades)A/C 15443175 & 15979446 Seg fund transfer error message.
// 
//    Rev 1.296   Jun 26 2009 06:50:54   kitticha
// IN#1738640 - R94 - Country Schedule - Cannot modify TX even when FundFrom and FundTo are same
// 
//    Rev 1.295   Jun 19 2009 07:02:16   wutipong
// IN1639282 clean up code comments
// 
//    Rev 1.294   Jun 11 2009 12:19:46   wutipong
// #IN1639282 Refresh SplitCommission when TransFeeList is refreshed (after from fund is changed).
// 
//    Rev 1.293   10 Jun 2009 18:35:28   popescu
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
// 
//    Rev 1.292   Jun 09 2009 06:12:30   kitticha
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
// 
//    Rev 1.291   Apr 17 2009 10:44:12   jankovii
// PET 157825 FN04 Manual RRIF Redemption.
// 
//    Rev 1.290   Mar 13 2009 00:02:40   wutipong
// IN1358908 -- Correct 'MAKEFROMEAUTOPROMOTE' call in 'getFormerSpouseList()' function.
// 
//    Rev 1.289   Jan 19 2009 12:03:36   wongsakw
// IN1393123 -- Non same day Switches not being settled through cycle autosettlement
// 
//    Rev 1.288   Dec 23 2008 17:17:18   wongsakw
// IN1393123 -- Non same day Switches not being settled through cycle autosettlement
// 
// More changes based on Serban's suggestion.
// 
//    Rev 1.287   Dec 19 2008 17:11:36   wongsakw
// IN1393123 Non same day switches not being settled through cycle autosettlement
// 
//    Rev 1.286   Dec 02 2008 14:59:06   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.285   Nov 03 2008 22:16:54   phiwponp
// IN 1419539 - Due to unit testing of Incident 1337808 Add error 761, unable to process by an AMS account.
// 
//    Rev 1.284   24 Oct 2008 11:58:18   popescu
// Incident 1309030 - re-coded the realignment transfer logic 
// 
//    Rev 1.283   09 Oct 2008 15:43:30   kovacsro
// PET142007FN01 - use FromAccount for Transfer to display the list of former spuses
// 
//    Rev 1.282   06 Oct 2008 13:20:44   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.281   01 Oct 2008 12:14:20   popescu
// Check in for incident 1419539
// 
//    Rev 1.280   12 Sep 2008 15:41:24   kovacsro
// PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
// 
//    Rev 1.279   Jul 28 2008 18:26:10   daechach
// in# 1309030 - Realignment transfer entry issues. Code review.
// 
//    Rev 1.278   Jul 04 2008 15:55:50   daechach
// in# 1309030 - Realignment transfer entry issues.
// 
//    Rev 1.277   May 07 2008 19:22:40   wongsakw
// PET5815 FN02 Realignment Transfer
// 
//    Rev 1.276   15 Apr 2008 12:13:34   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.275   Mar 28 2008 11:13:32   wongsakw
// IN 1151000 - remove restriction to allow transfering between individual acc. to spousal acc. 
// 
//    Rev 1.274   Feb 06 2008 16:57:18   wongsakw
// Incident#1060973 Trans code 30-04
// 
//    Rev 1.273   Nov 26 2007 11:00:36   jankovii
// PET 5685 FN25 - Age 71
// 
//    Rev 1.272   23 Nov 2007 09:48:14   popescu
// Incident 1055178 - sub sequent fix to invalidate the OrderType field when the clearing method is updated
// 
//    Rev 1.271   23 Nov 2007 09:35:50   kovacsro
// PET5685FN25 Age71 changes
// 
//    Rev 1.270   30 Oct 2007 10:00:32   kovacsro
// IN# 1055178
// 
//    Rev 1.269   Oct 08 2007 12:17:10   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.268   01 Aug 2007 15:59:28   popescu
// Incident # 956780 - mgfeerebate should always be direct
// 
//    Rev 1.267   24 Jul 2007 20:13:58   popescu
// GAP 20 -22 AIM
// 
//    Rev 1.266   28 Jun 2007 16:42:44   popescu
// AIM GAP 63 - BKK synch-up estate processing
// 
//    Rev 1.265   May 09 2007 16:19:28   jankovii
// MT54X PET2321 FN03 -Participant Transfer.
// 
//    Rev 1.264   Mar 30 2007 14:09:02   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.262   Mar 26 2007 11:07:04   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.261   Mar 21 2007 13:27:00   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.260   Mar 14 2007 14:40:08   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.259   Feb 08 2007 13:24:40   popescu
// Incident# 621638 - refresh trade after to fund was entered - to default trade date.
// 
//    Rev 1.258   Dec 14 2006 16:50:52   ZHANGCEL
// Change a conments in ValidateAccountToRedCode
// 
//    Rev 1.257   Dec 07 2006 12:59:56   jankovii
// Incident #702329 - Transfer vs. Systematic.
// 
//    Rev 1.256   Nov 27 2006 16:49:40   ZHANGCEL
// Incident #706688 -- Add logic for Locked in Transfer
// 
//    Rev 1.255   Nov 20 2006 06:46:30   porteanm
// Incident# 693254 - settlement source field opened for TR/XR - syncup
// 
//    Rev 1.254   Nov 09 2006 00:08:26   popescu
// PET 2281/Fn01 - cloning account - TA  synch-up from rel 73
// 
//    Rev 1.253   Oct 30 2006 17:08:14   jankovii
// PET 2185 FN04 - Trade restrictions.
// 
//    Rev 1.252   Oct 18 2006 11:22:40   jankovii
// Undone changes done in fixing incident 702739.
// 
//    Rev 1.251   Sep 12 2006 13:57:44   ZHANGCEL
// Incident #702739 -- Fix bug in Validate
// AmtType
// 
//    Rev 1.250   Sep 05 2006 19:05:46   popescu
// Incident# 693254 - settlement source field opened for TR/XR
// 
//    Rev 1.249   Aug 31 2006 11:00:38   popescu
// Incident# 666813 - cycle crash DSK does not send the allocations over to the back-end for full transfers/exchanges
// 
//    Rev 1.248   Jul 14 2006 11:05:10   popescu
// PET 2145 FN01 - format the code and check for <= WARNING
// 
//    Rev 1.247   Jul 04 2006 13:45:10   ZHANGCEL
// PET 2145 FN01 - Change logic in getEscrowFundClassState() to handle Assignee.
// 
//    Rev 1.245   Jun 14 2006 16:19:56   popescu
// PET 2102.FN02 Flex 
// 
//    Rev 1.244   Jun 14 2006 10:50:42   jankovii
// PET2102 FN02 - Manulife Flex  Trade/Systematic Entry.
// 
//    Rev 1.243   May 25 2006 16:01:36   popescu
// Backed out the code for: Incident# 604249 - PIMCO trade date should be refreshed when to fund/class changes
// 
//    Rev 1.242   May 25 2006 14:41:30   porteanm
// Incident 621359 - For a TIK redcode, except 27, account owner does not have to be the same.
// 
//    Rev 1.241   May 25 2006 09:37:32   jankovii
// PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
// 
//    Rev 1.240   May 08 2006 16:33:46   popescu
// Incident# 604249 - PIMCO trade date should be refreshed when to fund/class changes
// 
//    Rev 1.239   Apr 07 2006 17:00:08   popescu
// PET 1334 Alternative Product. If view 135 returns an error still initalize data.
// 
//    Rev 1.238   Apr 06 2006 10:50:26   jankovii
// PET 1334 Alternative Product. If view 135 returns an error still initalize data.
// 
//    Rev 1.237   Apr 05 2006 11:58:02   jankovii
// EUSD Backdated validation. Validation will be invoked even when to/from fund is the same.
// 
//    Rev 1.236   Mar 22 2006 16:23:58   jankovii
// EUSD Backdated trade validation.
// 
//    Rev 1.235   Jan 19 2006 13:53:40   AGUILAAM
// PET1295_FN01: addl enhancements - do not display MCH/SecRec fields if not supported by client
// 
//    Rev 1.234   Dec 08 2005 17:04:44   AGUILAAM
// IN 486592 - FEL in ifast/base, in this case, refers to funds with feeflag[1] (acquisition fee) active.  This is true for both FEL and NOL funds. Reject transfer with amounttype T or F only if transferring to BEL fund.
// 
//    Rev 1.233   Nov 29 2005 15:24:22   AGUILAAM
// PET_1228_FN02: EUSD Phase 2
// 
//    Rev 1.232   Oct 04 2005 11:16:46   ZHANGCEL
// PET1244 - FN01 - Specify EventTransType to determine whether the SegCapRules needs to be involved
// 
//    Rev 1.231   Sep 27 2005 13:56:32   porteanm
// Incident 395614 - SegFundValidation, super ugly implementation when is too late for a change of design.
// 
//    Rev 1.230   Sep 20 2005 12:15:28   AGUILAAM
// PET1250_FN09_Custody Client Accounts and Negative Balances; also fixed Refresh functionality for Settlements.
// 
//    Rev 1.229   Jul 14 2005 14:51:40   popescu
// Incident 356593 - fix trade crash if default allocations/ams are available for an account, when placing redemptions/purchases/transfers
// 
//    Rev 1.228   Jul 07 2005 17:59:52   popescu
// PET1171 EUSD 1B - Call validateEUSDBackDates().
// 
//    Rev 1.227   Jul 07 2005 17:52:42   popescu
// Incident# 350901 - removed split commissions when not needed, do not call split commissions when trade is roa applicable, trans type is transfer and side of the splits is To
// 
//    Rev 1.226   Jul 07 2005 14:00:04   porteanm
// PET1171 EUSD 1B - Call validateEUSDBackDates().
// 
//    Rev 1.225   Jun 30 2005 15:41:36   popescu
// Incident # 346892 - fee should not be reset when modifying a split commission in pending mode. Clearing the ROAAmount should be done only if the field is available for business
// 
//    Rev 1.224   Jun 29 2005 11:57:40   popescu
// Incident# 342270 - guard the refresh of split commissions with a boolean for fund related changes; save several view calls to 158
// 
//    Rev 1.223   Jun 01 2005 17:40:44   popescu
// PET 1203/05 - after code review minor changes - mainly formatting and changed getROAFields access to protected
// 
//    Rev 1.222   May 27 2005 11:13:40   yingbaol
// PEt1203,FN01:Delete split commission when ROA amount is 0.0 for transfer
// 
//    Rev 1.221   May 24 2005 15:57:42   yingbaol
// PET1203,FN01:fix splitcommission
// 
//    Rev 1.220   May 18 2005 09:03:42   yingbaol
// PET1203,FN01 Commission-Class A enhancement
// 
//    Rev 1.219   May 11 2005 16:34:38   porteanm
// PET1203 FN05 - Class B NAV Share Lots.
// 
//    Rev 1.218   May 02 2005 11:55:52   porteanm
// Incident 290690 - Source Of Fund.
// 
//    Rev 1.217   Feb 16 2005 15:53:22   Fengyong
// 244475 - Deposit code list is different between modify Transfer and transfer entry screen.
// 
//    Rev 1.216   Dec 30 2004 13:31:00   popescu
// PTS  10037345 , validation for amt type All Free Units should be done against 'tofund'
// 
//    Rev 1.215   Dec 29 2004 13:19:20   popescu
// PTS 10037187, assign FromCurrency field in the base class (Trade) so exch rate can be properly set for pending trades, also wire should always be the default for pay type
// 
//    Rev 1.214   Dec 29 2004 11:22:34   popescu
// PTS 10037302, do not validate amount precision for amount type units
// 
//    Rev 1.213   Dec 15 2004 15:54:00   popescu
// PET 1117/06, fixes related to setting-up a transfer
// 
//    Rev 1.212   Dec 15 2004 10:41:18   popescu
// PET 1117/06, delay the full transfer/exchange not allowed errror
// 
//    Rev 1.211   Dec 14 2004 15:02:48   popescu
// PET 1117/56, pay method/file proc related changes and fixes
// 
//    Rev 1.210   Dec 13 2004 14:19:16   popescu
// PET 1117/56, set the 'FromFundCurrency' when mod pending trades
// 
//    Rev 1.209   Dec 11 2004 11:48:12   popescu
// PET 1117/56 more fixes, pending trade mods
// 
//    Rev 1.208   Dec 07 2004 18:01:56   popescu
// PET 1117/06, fund fields should not be read only
// 
//    Rev 1.207   Dec 07 2004 01:38:04   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.206   Dec 06 2004 10:41:46   popescu
// PET 1117/56, fees processing
// 
//    Rev 1.205   Dec 03 2004 16:26:26   vadeanum
// PET1117_FN21:  settlement instructions.
// 
//    Rev 1.204   Dec 01 2004 15:45:26   popescu
// PET 1117/56 fees processing, calculate the discount rate
// 
//    Rev 1.203   Nov 30 2004 20:10:30   popescu
// PET 1117/06
// 
//    Rev 1.202   Nov 29 2004 20:31:00   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.201   Nov 27 2004 21:19:30   popescu
// PET 1117/06, trades processing
// 
//    Rev 1.200   Nov 26 2004 17:52:08   popescu
// PTS 10033507, synch-up rel 58/58.1 branch 1.190.2.0
// 
//    Rev 1.199   Nov 25 2004 14:59:22   popescu
// PET 1117/06, settle locations
// 
//    Rev 1.198   Nov 25 2004 11:44:24   popescu
// PET 1117/06, settle locations
// 
//    Rev 1.197   Nov 24 2004 21:36:40   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.196   Nov 22 2004 13:09:46   popescu
// PET 1117/56. fees processing
// 
//    Rev 1.195   Nov 18 2004 13:28:38   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.194   Nov 15 2004 15:06:24   popescu
// PET 1117/06, ,NET synch changes
// 
//    Rev 1.192   Nov 08 2004 12:31:20   popescu
// PET 1117/06 trade processing
// 
//    Rev 1.191   Nov 06 2004 00:43:22   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.6   Nov 04 2004 17:41:48   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.5   Nov 02 2004 19:19:40   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.4   Oct 28 2004 18:23:58   popescu
// PET 1117/06
// 
//    Rev 1.3   Oct 27 2004 11:27:06   popescu
// PET 1117/06
// 
//    Rev 1.2   Oct 22 2004 19:58:58   popescu
// PET 1117/06, work in progress...
// 
//    Rev 1.1   Oct 21 2004 06:29:28   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.0   Oct 01 2004 19:30:04   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
