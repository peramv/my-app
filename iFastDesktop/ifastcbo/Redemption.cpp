
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
//
//******************************************************************************
//
// ^FILE   : Redemption.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : Redemption - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "redemption.hpp"

#include "acctcategorylist.hpp"
#include "amsmstrinfo.hpp"
#include "bankinstructions.hpp"
#include "certificatelist.hpp"
#include "entity.hpp"
#include "estateallocationlist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "intermediary.hpp"
#include "intermediarylist.hpp"
#include "investorauthorization.hpp"
#include "investorauthorizationlist.hpp"
#include "lsifcodeslist.hpp"
#include "mfaccountholdinglist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "mfaccount.hpp"
#include "pendingtradelist.hpp"
#include "redemptionvalidation.hpp"
#include "redcodebytaxtypelist.hpp"
#include "redcodebytaxtype.hpp"
#include "shareholder.hpp"
#include "supportedproductslist.hpp"
#include "taxtyperule.hpp"
#include "tradefundalloclist.hpp"
#include "translationtable.hpp"
#include "accountentityxrefobject.hpp"
#include "AMSMstrList.hpp"
#include "AmsFundAllocList.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "IntraDayPricing.h"

#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_warn_includes.h>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME                     = I_("Redemption");
   const I_CHAR * const BEARERREDCODELIST             = I_("16,17"); // bearer certificate red code list
   const I_CHAR * const YES                           = I_("Y");
   const I_CHAR * const NET                           = I_("N");
   const I_CHAR * const REDEMPTION_TPA_FEE            = I_("213");
   const I_CHAR * const CANADIAN_DOLLAR_LIST          = I_("CDN,CAD");
   const I_CHAR * const RESP_TAX_TYPES                = I_("9,M");
   const I_CHAR * const RESP_TRANSFER_RED_CODES       = I_("64,65");
   //const I_CHAR * const RESP_AIP_RED_CODES            = I_("66,67,79,80,B1");
   const I_CHAR * const RESP_AIP_RED_CODES            = I_("66,67,79,80");
   const I_CHAR * const REDCODE_RESP_REDEEM_CONTRIB   = I_( "60" );
   const I_CHAR * const REDCODE_CLB_RETURN            = I_( "75" );
   const I_CHAR * const REDCODE_ACES_RETURN           = I_( "76" );
   const I_CHAR * const REDCODE_QESI_SPECIAL_TAX		  = I_( "78" );
   const I_CHAR * const REDCODE_QESI_INCREASE_SPECIAL_TAX = I_( "IR" );
   const I_CHAR * const REDCODE_CESG_RETURN				  = I_( "83" );
   const I_CHAR * const REDCODE_CESG_BASIC_RETURN		  = I_( "GR" );
   const I_CHAR * const REDCODE_CESG_ADDITIONAL_RETURN	  = I_( "AR" );
   const I_CHAR * const REDCODE_ADDITIONAL_REPAYMENT	  = I_( "AG" );   
   const I_CHAR * const REDCODE_RESP_OC_WITHDRAWAL    = I_( "86" );
   const I_CHAR * const REDCODE_QESI_BASIC_ADJ        = I_( "Q1" );
   const I_CHAR * const REDCODE_QESI_INC_ADJ          = I_( "Q2" );
   const I_CHAR * const REDCODE_QESI_INTR_PMT         = I_( "Q3" );
   const I_CHAR * const REDCODE_UNCLAIMED             = I_( "UP" );
   const I_CHAR * const REDCODE_SAGES_GRANT_RETURN	  = I_( "SR" );
   const I_CHAR * const REDCODE_SAGES_CORRECTION	  = I_( "SC" );
   //const I_CHAR * const NOT_REQUIRED_RESP_BENEF_PW    = I_( "60,62,63,66,67,68,70,71,79,80" );
   const I_CHAR * const NOT_REQUIRED_RESP_BENEF_PW    = I_("62,63,70,71,B1");
   const I_CHAR * const RETURN_RECODES				  = I_("75,76,83,AR,GR,AG"); //IN2346626_WO599061
   const I_CHAR * const ENTITY_ANNUITANT              = I_("05");
   const I_CHAR * const ACCT_DESIGNATION_CLIENT       = I_("1");
   const I_CHAR * const DEFAULT_REDEMPTION_ORDER      = I_("FM");
   const I_CHAR * const SUPPRESS_CHEQUE				  = I_("99");
   const I_CHAR * const VERIFY						  = I_("03");
   const I_CHAR * const REDCODE_RESP_REDEEM_CONTRIB_CLOSE_ACCOUNT   = I_( "68" );
   const I_CHAR * const REDCODE_BCTESG_GRANT_RETURN	  = I_( "BR" );
   const I_CHAR * const REDCODE_BCTESG_CORRECTION	  = I_( "BC" );
   const I_CHAR * const PRICETYPE_REDEMPTION_RECLASS  = I_( "SR" );
   const I_CHAR * const REDCODE_REDEMPTION_RECLASS    = I_( "RL" );
   const I_CHAR * const PAYTYPE_SUPPRESS              = I_( "X" );
   const I_CHAR * const RDSP_TAX_TYPE				  = I_("RS");
   const I_CHAR * const EXTERNAL_RDSP_TRANSFER_OUT	  = I_("RT");	
   const I_CHAR * const CALLING_TYPE                  = I_( "Gating" );
}

namespace ifds
{
//management company options
   extern CLASS_IMPORT const BFTextFieldId ACHRedemption;
   extern CLASS_IMPORT const BFTextFieldId CheqDeliveryDefault;
   extern CLASS_IMPORT const BFTextFieldId ValueDateApplic;
   extern CLASS_IMPORT const BFTextFieldId BusRounding;
   extern CLASS_IMPORT const BFTextFieldId AutomaticAll;
   extern CLASS_IMPORT const BFTextFieldId NoWithTax;
   extern CLASS_IMPORT const BFTextFieldId TaxOnRRIFRed;
   extern CLASS_IMPORT const BFTextFieldId RIFTTaxableRedCode;
   extern CLASS_IMPORT const BFTextFieldId WithTaxOverride;
   extern CLASS_IMPORT const BFTextFieldId PQLIFLIRAJuris;
   extern CLASS_IMPORT const BFTextFieldId PQLIFLIRATaxType;
   extern CLASS_IMPORT const BFTextFieldId TRExclRedCodes;
   extern CLASS_IMPORT const BFTextFieldId FullRedCode;
   extern CLASS_IMPORT const BFTextFieldId UpdOrdType;
   extern CLASS_IMPORT const BFTextFieldId PartTransAsFull;
   extern CLASS_IMPORT const BFTextFieldId LipClient;
   extern CLASS_IMPORT const BFTextFieldId CotClient;
   extern CLASS_IMPORT const BFTextFieldId DeathRedCode;
   extern CLASS_IMPORT const BFTextFieldId Residency1;
   extern CLASS_IMPORT const BFTextFieldId Residency2;
   extern CLASS_IMPORT const BFTextFieldId Residency3;
   extern CLASS_IMPORT const BFTextFieldId DefSetlCurrency;
   extern CLASS_IMPORT const BFTextFieldId RdAcctCurrency;
   extern CLASS_IMPORT const BFTextFieldId NetworkTypeUpd;
   extern CLASS_IMPORT const BFTextFieldId RedPayEntExist;
//fund fields
   extern CLASS_IMPORT const BFIntegerFieldId SettlePurDays;
   extern CLASS_IMPORT const BFDateFieldId NextNightRun;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFTextFieldId PayIntOn;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundCurrency;
//redemption validation
   extern CLASS_IMPORT const BFDecimalFieldId LSIFUnitsAvail;
   extern CLASS_IMPORT const BFTextFieldId RRIFDetlErr;
   extern CLASS_IMPORT const BFTextFieldId RedCodesErr;
   extern CLASS_IMPORT const BFDecimalFieldId RemAmtPayFirst;
   extern CLASS_IMPORT const BFTextFieldId LowRemainBal;
   extern CLASS_IMPORT const BFTextFieldId LLPValMsg;
   extern CLASS_IMPORT const BFTextFieldId MinWithAgeErr1;
   extern CLASS_IMPORT const BFTextFieldId MinWithAgeErr2;
   extern CLASS_IMPORT const BFTextFieldId PenInfoErr;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeRulErr;
   extern CLASS_IMPORT const BFTextFieldId TransExist;
//attributes grid
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesFields;
   extern CLASS_IMPORT const BFTextFieldId RedemptionAttributes;
   extern CLASS_IMPORT const BFTextFieldId RedemptionPayType;
   extern CLASS_IMPORT const BFTextFieldId RedempSourceOfFund;
//substituion sets
   extern CLASS_IMPORT const BFTextFieldId AmtTypeRedemption;
   extern CLASS_IMPORT const BFTextFieldId AmtTypeMultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonQESI;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonCommon;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonRDSP;
//account fields
   extern CLASS_IMPORT const BFDecimalFieldId AccountBalance;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId TaxOnFullRed;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId Certificates;
   extern CLASS_IMPORT const BFTextFieldId MaxApplies;
   extern CLASS_IMPORT const BFTextFieldId PensionJuris;
   extern CLASS_IMPORT const BFTextFieldId DeathClaim;
   extern CLASS_IMPORT const BFTextFieldId Currency;   
   extern CLASS_IMPORT const BFTextFieldId SiblingOnly;
   extern CLASS_IMPORT const BFTextFieldId AIPWithdrawalExists;
   extern CLASS_IMPORT const BFTextFieldId ProdPortfolioUUID;
//shareholder
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
//unrelated fields   
   extern CLASS_IMPORT const BFTextFieldId PlanType;
   extern CLASS_IMPORT const BFTextFieldId LockedIn;
   extern CLASS_IMPORT const BFTextFieldId Residency;
   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
   extern CLASS_IMPORT const BFDecimalFieldId AmtSysCalc;
   extern CLASS_IMPORT const BFTextFieldId MaximumApplies;
   extern CLASS_IMPORT const BFTextFieldId MinimumApplies;
   extern CLASS_IMPORT const BFTextFieldId AmntOverMax;
   extern CLASS_IMPORT const BFTextFieldId UnitHeld;
   extern CLASS_IMPORT const BFTextFieldId CurrLIPSetup;
   extern CLASS_IMPORT const BFTextFieldId AmountOver;
   extern CLASS_IMPORT const BFTextFieldId DTAEligible;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
//cross edits
   extern CLASS_IMPORT const BFTextFieldId AmountGrossNet;
   extern CLASS_IMPORT const BFTextFieldId AmtTypeGrossNet;
   extern CLASS_IMPORT const BFTextFieldId FedTaxRatePUD;
   extern CLASS_IMPORT const BFTextFieldId ProvTaxRatePUD;
   extern CLASS_IMPORT const BFTextFieldId FedProvTaxRatePUDXEdit;
   extern CLASS_IMPORT const BFTextFieldId WireOrdFndCls;
   extern CLASS_IMPORT const BFTextFieldId AmountAmtType;
   extern CLASS_IMPORT const BFTextFieldId ClearAcctPayTypeSuppCode;
   extern CLASS_IMPORT const BFTextFieldId FundCodeRedCodeAmount;
   extern CLASS_IMPORT const BFTextFieldId AmtTypeRedCode;
   extern CLASS_IMPORT const BFTextFieldId DeathStat;
   extern CLASS_IMPORT const BFTextFieldId AmtOverMin;
   extern CLASS_IMPORT const BFIntegerFieldId WDFeeDefn;
   extern CLASS_IMPORT const BFTextFieldId DirectDepositBankApplicable;
   extern CLASS_IMPORT const BFTextFieldId FundSubCat;
   extern CLASS_IMPORT const BFTextFieldId IAFundIndicator;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId EligDateforCLB;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFTextFieldId Residency1;
   extern CLASS_IMPORT const BFTextFieldId Residency2;
   extern CLASS_IMPORT const BFTextFieldId Residency3;
   extern CLASS_IMPORT const BFTextFieldId Pre98Contrib;
   extern CLASS_IMPORT const BFTextFieldId RedCodeOCRdmYearXEdit;
   extern CLASS_IMPORT const BFTextFieldId RedCodeTaintedXEdit;
   extern CLASS_IMPORT const BFTextFieldId GrantRepayReasonQESI2;
   extern CLASS_IMPORT const BFTextFieldId EAPEarningCodes; //P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
   extern CLASS_IMPORT const BFTextFieldId RtnMailStageList;
   extern CLASS_IMPORT const BFTextFieldId StaleChqStageList;
   extern CLASS_IMPORT const BFTextFieldId RemittedChqStageList;
   extern CLASS_IMPORT const BFNumericFieldId ErrorCode;
   extern CLASS_IMPORT const BFTextFieldId ErrorDesc;
   extern CLASS_IMPORT const BFTextFieldId ContractType;
   extern CLASS_IMPORT const BFIntegerFieldId ContractVer;
   extern CLASS_IMPORT const BFTextFieldId GIRedemOrder;
   extern CLASS_IMPORT const BFTextFieldId GIRedemAmountType;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_PW_IA;  //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA; //P0186486_FN15_The Source of Funds

   extern CLASS_IMPORT const BFTextFieldId SpouseBenefReLn;
   extern CLASS_IMPORT const BFTextFieldId ChildBenefReLn;
   extern CLASS_IMPORT const BFTextFieldId RelateCode;
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId XRedCode;
   extern CLASS_IMPORT const BFTextFieldId PymtRoutingMthd;
   extern CLASS_IMPORT const BFTextFieldId TradelevelOveride;    
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId AssocFund;
   extern CLASS_IMPORT const BFTextFieldId AssocClass;
   extern CLASS_IMPORT const BFTextFieldId TrackTrActive;
   extern CLASS_IMPORT const BFTextFieldId TrackTrRedCode;
   extern CLASS_IMPORT const BFTextFieldId Deconversion;
   extern CLASS_IMPORT const BFTextFieldId PriceTypes;
   extern CLASS_IMPORT const BFTextFieldId GateOverrideIndicator;
   extern CLASS_IMPORT const BFTextFieldId GrossNetType;
}

namespace CND
{
   extern const long ERR_ORDERTYPE_MUST_BE_DIRECT;
   extern const long ERR_FIRST_DTA_TRADE_MUST_BE_PURCHASE;
   extern const long ERR_ACCT_BALANCE_ZERO;   
   extern const long ERR_VALUE_DATE_EARLIER_THAN_CYCLE;
   extern const long ERR_NET_UNIT_REDEEM_NOT_ALLOWED;
   extern const long ERR_NET_AMOUNT_WITH_ZERO;
   extern const long ERR_INVALID_AMTTYPE_FOR_BEL_REDEMPTION;
   extern const long ERR_INVALID_AMTTYPE_FOR_REDEMPTION;
   extern const long ERR_AMOUNT_NOT_ALLOWED;
   extern const long ERR_INVALID_AMTCODE_FOR_INVESTMENT_ALLOCATION;
   extern const long WARN_OVERRIDE_FED_TAX_RATE_LESS_THEN_DEFAULT;
   extern const long WARN_OVERRIDE_PROV_TAX_RATE_LESS_THEN_DEFAULT;
   extern const long WARN_NO_CHECK_ON_TAXRATE_FOR_NON_DOLLAR_AMTTYPE;
   extern const long ERR_REDEMPTION_TOTAL_TAX_RATE_GREATER_THAN_100;
   extern const long ERR_AS_PENSION_ACCT;
   extern const long ERR_WARN_AS_PENSION_ACCT;
   extern const long ERR_FUND_CLASS_REDEMPTION_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_REDEMPTION_STOP_FLAG_ON;
   extern const long ERR_WARN_CERT_UNITS_EXISTS;
   extern const long WARN_PAYOUT_AMOUNT_MAYBE_CHANGED;
   extern const long ERR_MAX_PAYMENT_EXCEED;
   extern const long WARN_MAX_PAYMENT_EXCEED;
   extern const long WARN_UNITS_CANNOT_BE_REDEEMED;
   extern const long ERR_WARN_TOTAL_REDEMPTION_EXCEEDS_MAXIMUM;
   extern const long ERR_TOTAL_REDEMPTION_EXCEEDS_MAXIMUM;
   extern const long ERR_FULL_REDEMPTION_NOT_ALLOW;
   extern const long WARN_FULL_REDEMPTION_NOT_ALLOW;
   extern const long ERR_INVALID_AMTTYPE_FOR_LSIF_REDEMPTION;
   extern const long ERR_FULL_REDEMPTION_INDICATED;
   extern const long ERR_REDEMPTION_SUPPRESS_CODE_INVALID_FOR_NON_CLEARING_ACCOUNT;
   extern const long ERR_REDEMPTION_SUPPRESS_CODE_INVALID_FOR_NON_CLEARING_PAY_TYPE;
   extern const long ERR_REDEMPTION_SUPPRESS_CODE_MUST_BE_CLEARING_FOR_CLEARING_ACCOUNT;
   extern const long ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS;
   extern const long ERR_AMOUNT_MUST_BE_ZERO_WHEN_CLOSING_ACCOUNT;
   extern const long ERR_FUND_CODES_MUST_BE_BLANK_FOR_REDEMPTION;
   extern const long ERR_INVALID_INTEREST_ON_CLOSE_FUND_REDEMPTION;
   extern const long ERR_INVALID_CLOSE_FUND_REDEMPTION;
   extern const long ERR_RED_AMT_MORE_THAN_HOLDING;
   extern const long ERR_WARN_RED_AMT_MORE_THAN_HOLDING;
   extern const long ERR_LSIF_REDEMPTION_NOT_ENOUGH_UNITS_AVAILABLE;
   extern const long WARN_LSIF_REDEMPTION_NOT_ENOUGH_UNITS_AVAILABLE;
   extern const long WARN_ACCOUNT_HAS_STOP_REDEMPTION;
   extern const long ERR_SPECIFIE_FUND_WHEN_AMOUNT_IS_ZERO;
   extern const long ERR_REMAIN_AMOUNT_MUSTBE_PAID;
   extern const long WARN_REMAIN_AMOUNT_MUSTBE_PAID;
   extern const long ERR_SCHEDULED_PAYMENT_NOT_AVAILABLE;
   extern const long WARN_SCHEDULED_PAYMENT_NOT_AVAILABLE;
   extern const long ERR_REDEMPTION_CODE_RULES_NOT_SETUP;
   extern const long WARN_REDEMPTION_CODE_RULES_NOT_SETUP;
   extern const long ERR_ACCT_CANNOT_BE_CLOSE;
   extern const long ERR_REMAIN_ACCT_BALANCE;
   extern const long WARN_REMAIN_ACCT_BALANCE;
   extern const long ERR_LIP_VAL_MSG;
   extern const long ERR_CLIENT_AGE_LESS_THAN_MINWITHAGE1;
   extern const long ERR_CLIENT_AGE_LESS_THAN_MINWITHAGE2;
   extern const long ERR_NO_PENSION_INFO;
   extern const long ERR_NO_TAXTYPE_RULE;
   extern const long ERR_ACCOUNTHOLDER_DEATH_DATE_REQUIRED;
   extern const long ERR_ACCOUNT_NUM_NEEDED_FOR_CLOSE_ACCOUNT;
   extern const long ERR_MISSING_ACCTHOLDER_DOFBIRTH;
   extern const long ERR_TRANSACTION_NOT_ALLOWED_AFTER_69;
   extern const long ERR_DEATH_DATE_EXIST_FOR_ACCTHOLDER;
   extern const long ERR_CANADIAN_RESIDENT_WITHDRAW;
   extern const long ERR_CONTRACT_ACCT_STATUS_ACTIVE;
   extern const long ERR_WARN_CONTRACT_ACCT_STATUS_ACTIVE;
   extern const long ERR_DEATH_CLAIM_REDEMPTION_CODE;
   extern const long ERR_WARN_DEATH_CLAIM_REDEMPTION_CODE;
   extern const long ERR_DTA_NOT_ALLOWED_FOR_THIS_REDCODE;
   extern const long ERR_WARN_MAXMIN_AMT_RECALCULATION;
   extern const long ERR_WARN_DATE_OF_BIRTH_REQUIRED_FOR_CASH_REDEMPTION;
   extern const long ERR_AMOUNT_TYPE_NOT_VALID_FOR_REDCODE;
   extern const long ERR_ILLEGAL_REDEMPTION_CODE_FOR_ACCT_TAX_TYPE;
   extern const long WARN_NET_REDEMPTION_OVER_MINIMUM;
   extern const long ERR_NET_REDEMPTION_OVER_MINIMUM;
   extern const long WARN_GROSS_REDEMPTION_MINIMUM_APPLIES;
   extern const long ERR_GROSS_REDEMPTION_MINIMUM_APPLIES;
   extern const long ERR_EF;
   extern const long ERR_DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING;
   extern const long WARN_DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING;
   extern const long ERR_PW_DIRECT_DPST_INTERESTED_FUND_SUB_CAT;
   extern const long ERR_FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE;
   extern const long WARN_FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE;
   extern const long ERR_DIRECT_DEPST_FOR_CAN_CUR_ONLY;
   extern const long WARN_GRANT_REPAYMENT_NOT_REPORTED_HRDC; 
   extern const long ERR_REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT;
   extern const long WARN_REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT;
   extern const long ERR_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern const long WARN_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern const long ERR_INVALID_CESG_REPAYMENT_REASON_CODE;
   extern const long WARN_INVALID_CESG_REPAYMENT_REASON_CODE;
   extern const long ERR_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED;
   extern const long WARN_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED;
   extern const long ERR_INVALID_YEAR_RESP_OC_WITHDRAWAL;
   extern const long WARN_INVALID_YEAR_RESP_OC_WITHDRAWAL;
   extern const long ERR_TAINTED_FIELD_REQUIRED;
   extern const long WARN_RESP_TRANSACTION_AMT_EQ_LESS_FIFTHY_THSND;
   extern const long WARN_RESP_TRANSACTION_MIGHT_TRIGGER_GRANT_REPAYMENT;
   extern const long ERR_BENEF_SELECTED_DATE_BIRTH_NOT_ELIG_FOR_CLB;
   extern const long ERR_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS;
   extern const long WARN_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS;
   extern const long ERR_REDEMPTION_CODE_APPLICABLE_ONLY_FOR_NON_RESIDENT_BENEFICIARIES;
   extern const long WARN_REDEMPTION_CODE_APPLICABLE_ONLY_FOR_NON_RESIDENT_BENEFICIARIES;
   extern const long ERR_REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT;
   extern const long WARN_REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT;
   extern const long WARN_TAINTED_ONLY_APPLICABLE_IF_PRE98CONTRIB_IS_YES;
   extern const long ERR_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern const long WARN_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern const long WARN_RESP_TRANSFER_OUT;
   extern const long ERR_INVALID_GRANT_REPAYMENT_REASON_REDCODE;
   extern const long ERR_DOD_ENTITY_TYPE_MISSING;
   extern const long WARN_DOD_ENTITY_TYPE_MISSING;
   extern const long ERR_REDCODE_APPLICABLE_CLIENT;
   extern const long ERR_REDCODE_APPLICABLE_S3_S4;
   extern const long ERR_REDIRECT_TO_REG_AGENT_NOT_ALLOWED;
   extern const long ERR_REGAGENT_BANKING_UNAVILABLE;
   extern const long ERR_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE; //P0186486_FN15_The Source of Funds
   extern const long WARN_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE; 
   extern const long ERR_NET_UNIT_PERCENT_NOT_ALLOW;
   extern const long ERR_ESTATE_ALLOCATION_REQUIRED_FOR_DEATH_REDEMPTIONS;
   extern const long ERR_REDCODE_AND_TAXJURIS_DO_NOT_MATCH_FOR_BENEFICIARY;
   extern const long ERR_ENTITY_CANNOT_BE_USED_WITH_REDEMPTION_CODE;
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL;
   extern const long WARN_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL;
   extern const long ERR_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS;
   extern const long WARN_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS;
   extern const long ERR_AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE;
   extern const long WARN_AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE;
   extern const long ERR_AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP;
   extern const long WARN_AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP;
   extern const long ERR_AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP;
   extern const long WARN_AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP;
   extern const long ERR_RDSP_REPAYMENT_REASON_MANDATORY;
   extern const long WARN_RDSP_REPAYMENT_REASON_MANDATORY;
   extern const long ERR_RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED;
   extern const long WARN_RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED;
   extern const long ERR_RDSP_EXTERNAL_CONTRACT_MANDATORY;
   extern const long WARN_RDSP_EXTERNAL_CONTRACT_MANDATORY;
   extern const long ERR_RDSP_EXTERNAL_PLAN_MANDATORY;
   extern const long WARN_RDSP_EXTERNAL_PLAN_MANDATORY;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const EFT;
   extern CLASS_IMPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const REFUND_REDEMPTION;
}

namespace FUND_LOAD_TYPE
{
   extern CLASS_IMPORT I_CHAR * const BACKEND_LOAD;
   extern CLASS_IMPORT I_CHAR * const CHARGEBACK;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const SYSTEM_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const DIRECT;
   extern CLASS_IMPORT I_CHAR * const EFT;
   extern CLASS_IMPORT I_CHAR * const CLEARING;
   extern CLASS_IMPORT I_CHAR * const MANUAL_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const SUPPRESS;
   extern CLASS_IMPORT I_CHAR * const DIRECT_DEPOSIT;
} 

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING_TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const UPD_ORD_TYPE_REDEMPTION;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT_REDEMPTION;
   extern const I_CHAR * const ALT_EFT_REDEMPTION;
   extern const I_CHAR * const DIRECT_DEPOSIT;
}

namespace IFASTERR
{         
   extern CLASS_IMPORT I_CHAR * const AN_AS_PENSION_PLAN_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const MAXIMUM_PAYOUT_AMOUNT_IS_EXCEEDED;
   extern CLASS_IMPORT I_CHAR * const TOTAL_REDEMPTION_EXCEEDS_MAXIMUM;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_AMOUNT_IS_GREATER_THAN_ACCOUNT_BALANCE;
   extern CLASS_IMPORT I_CHAR * const REMAINING_MINIMUM_AMOUNT_MUST_BE_PAID_FIRST;
   extern CLASS_IMPORT I_CHAR * const SCHEDULED_PAYMENT_INFORMATION_NOT_AVAILABLE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_CODE_RULES_NOT_SETUP;
   extern CLASS_IMPORT I_CHAR * const REMAINING_ACCT_BALANCE_IS_INSUFFICIENT;
   extern CLASS_IMPORT I_CHAR * const CONTRACT_ACCOUNT_STATUS_IS_ACTIVE;
   extern CLASS_IMPORT I_CHAR * const MUST_ENTER_A_DEATH_CLAIM_REDEMPTION_CODE;
   extern CLASS_IMPORT I_CHAR * const GROSS_REDEMPTION_MINIMUM_APPLIES;
   extern CLASS_IMPORT I_CHAR * const NET_REDEMPTION_OVER_MINIMUM;
   extern CLASS_IMPORT I_CHAR * const FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE;
   extern CLASS_IMPORT I_CHAR * const DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT;
   extern CLASS_IMPORT I_CHAR * const SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const INVALID_CESG_REPAYMENT_REASON_CODE;
   extern CLASS_IMPORT I_CHAR * const AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const INVALID_YEAR_RESP_OC_WITHDRAWAL;
   extern CLASS_IMPORT I_CHAR * const DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_CODE_APPLICABLE_ONLY_FOR_NON_RESIDENT_BENEFICIARIES;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT;
   extern CLASS_IMPORT I_CHAR * const SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const DOD_ENTITY_TYPE_MISSING;
   extern CLASS_IMPORT I_CHAR * const SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE;
   extern CLASS_IMPORT I_CHAR * const PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL;
   extern CLASS_IMPORT I_CHAR * const CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_GROSS_NET_FOR_REDEMPTION_OVERIDDEN;
   extern CLASS_IMPORT I_CHAR * const AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE;
   extern CLASS_IMPORT I_CHAR * const AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP;
   extern CLASS_IMPORT I_CHAR * const AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP;
   extern CLASS_IMPORT I_CHAR * const RDSP_REPAYMENT_REASON_MANDATORY;
   extern CLASS_IMPORT I_CHAR * const RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const RDSP_EXTERNAL_CONTRACT_MANDATORY;
   extern CLASS_IMPORT I_CHAR * const RDSP_EXTERNAL_PLAN_MANDATORY;
}

namespace DATE_VALIDATION
{
   extern const I_CHAR * const DEFAULT_TRADE_DATE;
   extern const I_CHAR * const VALUE_DATE;
   extern const I_CHAR * const TRADE_DATE;
}

namespace PAYMENT_FOR
{
   extern const I_CHAR * REDEMPTION;
}

namespace
{
   const I_CHAR * const TFSA_TAX_TYPE           = I_("V");
   const I_CHAR * const EXTERNAL_TFSA_TAX_TYPE  = I_("Z");
   const I_CHAR * const TIF_FUND_SUB_CAT        = I_("12");
   const I_CHAR * const TIF_FUND_INDICATOR      = I_("I");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
  //Field DD Id,              State Flags,      Group Flags 
    { ifds::AmountGrossNet,            BFCBO::IMMEDIATE_VALIDATION, 0},
    { ifds::FedTaxRatePUD,             BFCBO::IMMEDIATE_VALIDATION, 0},
    { ifds::ProvTaxRatePUD,            BFCBO::IMMEDIATE_VALIDATION, 0},
    { ifds::FedProvTaxRatePUDXEdit,    BFCBO::IMMEDIATE_VALIDATION, 0},
    { ifds::RedCodeOCRdmYearXEdit,     BFCBO::IMMEDIATE_VALIDATION, 0},
    { ifds::RedCodeTaintedXEdit,       BFCBO::IMMEDIATE_VALIDATION, 0},
    { ifds::XRedCode,                  BFCBO::IMMEDIATE_VALIDATION, 0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
Redemption::Redemption (BFAbstractCBO &parent) : Trade (parent),
_blTaxable (false),
_dstrEAPEarningCodes(NULL_STRING)//IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
   registerMemberData( NUM_FIELDS,
                        (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0,
                        NULL);

   addCrossEdit (ifds::AmountGrossNet, ifds::Amount); 
   addCrossEdit (ifds::AmountGrossNet, ifds::GrossOrNet); 
// Withholding Tax validation support for Federal Tax Rates/Types
   addCrossEdit (ifds::FedTaxRatePUD,  ifds::FedRate);
   addCrossEdit (ifds::FedTaxRatePUD,  ifds::TransRatePUDFed);	
// Withholding Tax validation support for Federal Tax Rates/Types
   addCrossEdit (ifds::ProvTaxRatePUD, ifds::ProvRate);
   addCrossEdit (ifds::ProvTaxRatePUD, ifds::TransRatePUDProv);

// Withholding Tax validation support for Federal and Provincial Tax Rates/Types
   addCrossEdit (ifds::FedProvTaxRatePUDXEdit, ifds::FedRate);
   addCrossEdit (ifds::FedProvTaxRatePUDXEdit, ifds::TransRatePUDFed);		
   addCrossEdit (ifds::FedProvTaxRatePUDXEdit, ifds::ProvRate);
   addCrossEdit (ifds::FedProvTaxRatePUDXEdit, ifds::TransRatePUDProv);	

   addCrossEdit (ifds::RedCodeOCRdmYearXEdit,ifds::RedCode);
   addCrossEdit (ifds::RedCodeOCRdmYearXEdit,ifds::OCRdmYear);

   addCrossEdit (ifds::RedCodeTaintedXEdit,ifds::RedCode);
   addCrossEdit (ifds::RedCodeTaintedXEdit,ifds::Tainted);
   
   addCrossEdit (ifds::XRedCode, ifds::RedCode);
}

//******************************************************************************
Redemption::~Redemption ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY Redemption::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::REDEMPTION, 
                        idDataGroup, 
                        false);
   //IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
   getWorkSession ().getOption (ifds::EAPEarningCodes, _dstrEAPEarningCodes, idDataGroup, false); 
   _dstrEAPEarningCodes.stripAll();

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
      setFieldSubstituteValues ( ifds::AmtType, idDataGroup, _multiCurrency == Y ? ifds::AmtTypeMultiCurrency : ifds::AmtTypeRedemption);

   };
   DString outdstrpymtLevelRoutingSet   = NULL_STRING;
   buildPaymentRoutingSet(idDataGroup,outdstrpymtLevelRoutingSet);
   outdstrpymtLevelRoutingSet.empty();
   if(!outdstrpymtLevelRoutingSet.empty())
   {
      BFProperties *pBFProperties = getFieldProperties (ifds::PymtRoutingMthd, idDataGroup); 
      assert (pBFProperties);
      if (pBFProperties)
      {
         pBFProperties->setAllSubstituteValues (outdstrpymtLevelRoutingSet);
      } 
   }
   setFieldReadOnly(ifds::PymtRoutingMthd, idDataGroup,true); 
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Redemption::supportsAllocations (const BFDataGroupId &idDataGroup)
{
	DString dstrRedCode;
	getField(ifds::RedCode, dstrRedCode, idDataGroup);
	if(dstrRedCode == I_("EP") || isAllFundsFullMoneyOutIndc(idDataGroup))
		return false;
	else
		return !canCloseAccount (idDataGroup);
}

//******************************************************************************
bool Redemption::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
void Redemption::getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                            BFFieldId &classCodeFieldId
                                          )
{
   fundCodeFieldId = ifds::FromFund;
   classCodeFieldId = ifds::FromClass;
}

//******************************************************************************
void Redemption::getAccountFieldId (BFFieldId &accountFieldId)
{
   accountFieldId = ifds::AccountNum;
}

//******************************************************************************
inline bool Redemption::areTaxRatesAllowed (const BFDataGroupId &idDataGroup)
{
   return _blTaxable;
}

//******************************************************************************
bool Redemption::isSplitCommissionAllowed (const BFDataGroupId &idDataGroup)
{
   bool bAllowed = Trade::isSplitCommissionAllowed (idDataGroup);

   if (bAllowed)
   {
      DString redCode;
      
      getField (ifds::RedCode, redCode, idDataGroup, false);      
      bAllowed = redCode != I_("16") && redCode != I_("17");
   }
   return bAllowed; 
}

//******************************************************************************
bool Redemption::isSettleLocAllowed (const BFDataGroupId &idDataGroup)
{
   bool bIsClearingAcct = false;
   MFAccount *pMFAccount = NULL;   

   if ( getAccount ( pMFAccount, idDataGroup) <= WARNING  && 
        pMFAccount) 
   {
      DString payType;

      getField (ifds::TradesPayType, payType, idDataGroup, false);
      bIsClearingAcct = pMFAccount->isClearingAcount (idDataGroup) &&
                        pMFAccount->hasSettlementLocation (idDataGroup) &&
                        payType == PAYTYPE::CLEARING;
   }
   return bIsClearingAcct;
}

//multiple settle location
//******************************************************************************
bool Redemption::areMultipleSettleLocAllowed (const BFDataGroupId &idDataGroup)
{
   DString settleLocOpt;
   DString payType;

   getWorkSession ().getOption (ifds::SettleLocOpt, settleLocOpt, idDataGroup,  false);
   getField (ifds::TradesPayType, payType, idDataGroup, false);

   return settleLocOpt == I_("2") && payType != PAYTYPE::CLEARING && !payType.empty ();
}

//******************************************************************************
bool Redemption::isPSEEAPAllowed (const BFDataGroupId &idDataGroup)
{
   bool bIsPSEEAPAllowed (false);
   if (isRESPTradeAccount (idDataGroup))
   {
      DString redCode;
      
      getField (ifds::RedCode, redCode, idDataGroup, false);
      bIsPSEEAPAllowed = DSTCommonFunctions::codeInList (redCode, I_("61,69,77,84,85,EP"));
   }
   return bIsPSEEAPAllowed;
}

//******************************************************************************
bool Redemption::isAssociationWithBeneficiaryAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAssociatedBeneficiaryAllowed"));
   
   DString redCode;
   
   getField (ifds::RedCode, redCode, idDataGroup, false);

   //for redemption code "68", user should not select any beneficiary on desktop. Aligning with base. 
   /*if (redCode == REDCODE_RESP_REDEEM_CONTRIB_CLOSE_ACCOUNT)
	   return false;
   else*/
	   return Trade::isAssociationWithBeneficiaryAllowed (idDataGroup) && 
          !( DSTCommonFunctions::codeInList (redCode, NOT_REQUIRED_RESP_BENEF_PW) /*&&
             !getWorkSession().isQESIClient(idDataGroup)*/);
}

//******************************************************************************
bool Redemption::isShareholderAddressNeeded (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isShareholderAddressNeeded"));
   DString payType;

   getField (ifds::TradesPayType, payType, idDataGroup, false);
   return Trade::isShareholderAddressNeeded (idDataGroup) ||
          (payType == PAYTYPE::SYSTEM_CHEQUE && !arePayInstructAllowed (idDataGroup)) ||
          payType == PAYTYPE::MANUAL_CHEQUE ||
          payType == PAYTYPE::SUPPRESS;
}

//******************************************************************************
bool Redemption::arePayInstructAllowed (const BFDataGroupId &idDataGroup)
{
   DString payInstrOption;

   getField (ifds::PayInstrOption, payInstrOption, idDataGroup, false);
   return payInstrOption == I_("01"); //redirect to pay entity
}

//******************************************************************************
void Redemption::getDefaultPaymentFor ( DString &paymentFor, 
                                        const BFDataGroupId &idDataGroup)
{
   paymentFor = PAYMENT_FOR::REDEMPTION; 
}

//******************************************************************************
bool Redemption::isFullRedemption (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isFullRedemption"));

   DString redCode, 
      fundCode, 
      classCode, 
      amount, 
      fullRedCode;

   getField (ifds::Amount, amount, idDataGroup);

   double dec_amount = DSTCommonFunctions::convertToDouble (amount);

   getField (ifds::RedCode, redCode, idDataGroup);
   getField (ifds::FromFund, fundCode, idDataGroup); 
   getField (ifds::FromClass, classCode, idDataGroup);

   getWorkSession().getOption ( ifds::FullRedCode, 
                                fullRedCode, 
                                BF::HOST, 
                                false);
   return 
      DSTCommonFunctions::codeInList (redCode, fullRedCode) && 
      dec_amount == 0 && 
      fundCode == NULL_STRING && 
      classCode == NULL_STRING;
}

//******************************************************************************
SEVERITY Redemption::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
//base class call   
   Trade::preInitWithDefaultValues (idDataGroup);

   if (!isAdminFee (idDataGroup))
   {
      DString redemptionPayTypeSubstList;
      BFProperties *pBFProperties = 
         getFieldProperties (ifds::RedemptionPayType, idDataGroup);

      assert (pBFProperties);
      if (pBFProperties)
      {
         pBFProperties->getAllSubstituteValues (redemptionPayTypeSubstList);
//redemption pay type
         if ( !getWorkSession ().
              hasCreatePermission (UAF::DIRECT_TRADING_TRANSACTION)) //remove direct trading pay type
         {
            //remove the direct pay type
            redemptionPayTypeSubstList = 
               removeItemFromSubtList ( redemptionPayTypeSubstList, 
                                        PAYTYPE::DIRECT);
         }
         setFieldAllSubstituteValues ( ifds::TradesPayType, 
                                       idDataGroup, 
                                       redemptionPayTypeSubstList);
      }
   }
//lsif code substitution list
   SupportedProductsList *pSupportedProductsList = NULL;

   if (getMgmtCo ().
         getSupportedProductsList (pSupportedProductsList) <= WARNING && 
               pSupportedProductsList
      )
   {
      if (pSupportedProductsList->isLSIFProductActive ())
      {
         LSIFCodesList *pLSIFCodesList;

         if (getMgmtCo ().
               getLSIFCodesList (pLSIFCodesList) <= WARNING && 
                  pLSIFCodesList
            )
         {
            setFieldAllSubstituteValues ( ifds::LSIFCode, 
                                          idDataGroup, 
                                          pLSIFCodesList->getLSIFCodesSubstitutionList ());
         }
      }
   }
// redemption source of fund
   TranslationTable *pTranslationTable = NULL;
   if ( getMgmtCo().getTranslationTable ( I_("PS"), 
                                         pTranslationTable ) <= WARNING &&
        NULL != pTranslationTable )
   {

      //P0186486_FN15_The Source of Funds
      DString sourceOfFundApp;

      getWorkSession().getOption(ifds::SourceOfFundApp, sourceOfFundApp, idDataGroup, false);
      sourceOfFundApp.strip().upperCase();


      if(sourceOfFundApp == I_("Y"))
      {
         loadBusinessTypeSubslist(idDataGroup);
      }
      else
      {
         DString dstrRedemptionSrcOfFundCodeList;
         pTranslationTable->getRedemptionSrcOfFundCodeList( dstrRedemptionSrcOfFundCodeList );

         // Intended for pending/rebooked RRIF
         DString dstrTransType;
         getField( ifds::TradesTransType, dstrTransType, idDataGroup );
         dstrTransType.stripAll();
         if ( ( (_bInitPending || isRebook() )&& 
            I_( "AW" ) == dstrTransType ) )   // RRIF
         {
            DString dstrSourceOfFund;
            getField( ifds::SrcOfFund, dstrSourceOfFund, idDataGroup );
            if ( !DSTCommonFunctions::codeInList( dstrSourceOfFund, dstrRedemptionSrcOfFundCodeList ) )				
               dstrRedemptionSrcOfFundCodeList += dstrSourceOfFund + I_(","); 
         }

         loadSubstitutionList( ifds::SrcOfFund, 
            idDataGroup,
            dstrRedemptionSrcOfFundCodeList);
      }
   }
   
//amount type substitution sets
   setFieldSubstituteValues ( ifds::AmtType, 
                              idDataGroup, 
                              _multiCurrency == Y ? ifds::AmtTypeMultiCurrency : ifds::AmtTypeRedemption);
   DString cheqDeliveryDefault, 
      payType;

   getField (ifds::TradesPayType, payType, idDataGroup, false); 
   getWorkSession().getOption ( ifds::CheqDeliveryDefault, 
                                cheqDeliveryDefault, 
                                BF::HOST,
                                false);
   setFieldReadOnly (ifds::DeliveryMethod, idDataGroup, 
                     cheqDeliveryDefault.empty() || 
                     payType != PAYTYPE::SYSTEM_CHEQUE);
   loadNetworkIDValues (idDataGroup);
   respRedcodeRelatedChange(idDataGroup);
   rdspRedcodeRelatedChange(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Redemption::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
//call base class
   Trade::doInitWithDefaultValues (idDataGroup);

   setFieldNoValidate ( ifds::DepositType, I_("99"), idDataGroup, false,
                        false,  //force validation 
                        true);  //notify

   MFAccount *pMFAccount = NULL;
   DString dstrTaxType;
   if ( getAccount ( pMFAccount, idDataGroup) <= WARNING  && 
         NULL != pMFAccount ) 
   {
      pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup );
      dstrTaxType.strip().upperCase();
   }

   if ( getWorkSession ().isLIFLike (dstrTaxType) || I_( "L" ) == dstrTaxType )
   {
      setFieldNoValidate( ifds::RedCode, 
                          I_("10"),      // Minimum RRIF/LIF/LRIF Payment
                          idDataGroup, 
                          false, 
                          false,         //force validation
                          true );        //notify
   }
   else if ( dstrTaxType == RDSP_TAX_TYPE && isRedemption (idDataGroup))
   {
      setFieldNoValidate( ifds::RedCode, 
                          I_("DP"),      // RDSP DAP Payment
                          idDataGroup, 
                          false, 
                          false,         //force validation
                          true );        //notify
   }   
   else
   {
      setFieldNoValidate ( ifds::RedCode, 
                           I_("01"), 
                           idDataGroup, 
                           false, 
                           false,  //force validation
                           true);  //notify
                           
   }

   setFieldRequired (ifds::RedCode, idDataGroup, true);
//currency
   DString defSetlCurrency,
      rdAcctCurrency;

   getWorkSession().getOption ( ifds::DefSetlCurrency, 
                                defSetlCurrency, 
                                BF::HOST, 
                                false);
   getWorkSession().getOption ( ifds::RdAcctCurrency, 
                                rdAcctCurrency, 
                                BF::HOST, 
                                false);
   if (defSetlCurrency == N && rdAcctCurrency == Y)
   {
      //get the account currency      
      if ( pMFAccount ) 
      {
         DString accountCurrency;

         pMFAccount->getField (ifds::Currency, accountCurrency, idDataGroup, false);
         setFieldNoValidate (ifds::SettleCurrency, accountCurrency, idDataGroup, false, false, true);
      }
   }
//acq fee option
   setFieldNoValidate (ifds::AcqFeeOption, I_("2"), idDataGroup, false); //buy at NAV
//Incident# 726814 - catches the full redemptions 
//it will be an issue if the user switches from an lsif fund to a non-lsif and
//places a full redemption - not very often to happen...
   SupportedProductsList *pSupportedProductsList = NULL;

   if ( getMgmtCo ().getSupportedProductsList (pSupportedProductsList) <= WARNING && 
        pSupportedProductsList)
   {
      if (pSupportedProductsList->isLSIFProductActive ())
      {
         DString lsifSubstVal;
         BFProperties *pBFProperties = getFieldProperties ( ifds::LSIFCode, 
                                                            idDataGroup);
         pBFProperties->getAllSubstituteValues (lsifSubstVal);
         if (!lsifSubstVal.empty())
         {
            setFieldNoValidate ( ifds::LSIFCode, I_("0"), idDataGroup, false, //As charged
                                 true,
                                 true, //notify
                                 true);
         }
      }
   }

   if (bIsTaxTypeRelatedtoRegAgent(idDataGroup))
   {
      setFieldNoValidate ( ifds::PayInstrOption, I_("03"), idDataGroup,  //redirect to Reg Agent
                           false, 
                           false,
                           true);
      setFieldReadOnly (ifds::PayInstrOption, idDataGroup, true);
   }
   DString outdstrpymtLevelRoutingSet   = NULL_STRING;
   buildPaymentRoutingSet(idDataGroup,outdstrpymtLevelRoutingSet);
   outdstrpymtLevelRoutingSet.stripAll();
   if(!outdstrpymtLevelRoutingSet.empty())
   {
	 BFProperties *pBFProperties = getFieldProperties (ifds::PymtRoutingMthd, idDataGroup); 
     assert (pBFProperties);
     if (pBFProperties)
     {
      pBFProperties->setAllSubstituteValues (outdstrpymtLevelRoutingSet);
     } 
   }

   addBlankToSubSet (ifds::Deconversion, idDataGroup);
   setFieldNoValidate (ifds::Deconversion, I_("N"), idDataGroup, false);
   if (isNew())
   {	   
	   setFieldReadOnly( ifds::Deconversion, idDataGroup, false );
   }
}

//read the trade defaults from the management company options
//******************************************************************************
SEVERITY Redemption::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges"));
   DString redemptionAttributeSubstList;

   BFProperties *pBFProperties = 
      getFieldProperties (ifds::RedemptionAttributes, idDataGroup);
   
   pBFProperties->getAllSubstituteValues (redemptionAttributeSubstList);
//lsif grid related changes
   SupportedProductsList *pSupportedProductsList = NULL;

   if ( getMgmtCo ().getSupportedProductsList (pSupportedProductsList) <= WARNING && 
        pSupportedProductsList)
   {
      if (!pSupportedProductsList->isLSIFProductActive ())
      {
         redemptionAttributeSubstList = 
            removeItemFromSubtList ( redemptionAttributeSubstList, 
                                     I_("LSIFReason"));
      }
   }
   if (!isACHApplicable (idDataGroup))
   {
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("PayMethod"));
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("FileProcessor"));
   }

   DString networkTypeUpd;

   getWorkSession().getOption ( ifds::NetworkTypeUpd,
                                networkTypeUpd,
                                BF::HOST,
                                false);
   if (networkTypeUpd == N)
   {
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("NetworkID"));
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("SendRefNum"));
     redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("DeliveryNetwork"));
   }

   DString cheqDeliveryDefault;

   getWorkSession().getOption ( ifds::CheqDeliveryDefault, 
                                cheqDeliveryDefault, 
                                BF::HOST,
                                false);
   if (cheqDeliveryDefault.empty ())
   {
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                    I_("LUX_DeliveryMethod"));
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                    I_("CAD_DeliveryMethod"));
   }

   if (!isMCHSecRecIndApplicable (idDataGroup))
   {
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("MCHFileIndicator"));
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("SecRecFileIndicator"));
   }
   if ( !isAutoWithdraw (idDataGroup) || 
        DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG)
   {
      redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("ESGSettle"));
   }

   DString redPayEntExist;

   getWorkSession().getOption ( ifds::RedPayEntExist,
                                redPayEntExist,
                                BF::HOST,
                                false);
/*   if (redPayEntExist == N && !bIsTaxTypeRelatedtoRegAgent(idDataGroup))
   {
	   redemptionAttributeSubstList = 
		   removeItemFromSubtList ( redemptionAttributeSubstList, 
		   I_("PayInstrOption"));
   }
*/
   DString dstrTransType;
   getField (ifds::TradesTransType, dstrTransType, idDataGroup, false);
   if (dstrTransType == I_("PW"))
   {
       redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("MFPayment"));
   }

   if (dstrTransType != TRADETYPE::REFUND_REDEMPTION)
   {
       redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("RefundAmtOpt"));
   }

   if( !isNetworkRespReqApplicable() ) 
   {
	 redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("NetworkRespRequired"));
   }
   DString dstrTradeLevelOveride;
   getWorkSession ().getOption (ifds::TradelevelOveride, dstrTradeLevelOveride,idDataGroup,false);
   if( dstrTradeLevelOveride != YES ) 
   {
	 redemptionAttributeSubstList = 
         removeItemFromSubtList ( redemptionAttributeSubstList, 
                                  I_("PymtRoutingMthd"));
   }

   if( TRADETYPE::CROSS_SYSTEM_TRANSFER_OUT != dstrTransType )
   {
     redemptionAttributeSubstList = removeItemFromSubtList ( redemptionAttributeSubstList, 
                                                              I_("CrossSysAcctNum"));
   }
   if (dstrTransType != TRADETYPE::REDEMPTION)
   {
	   redemptionAttributeSubstList = removeItemFromSubtList ( redemptionAttributeSubstList, 
															   I_("ExternalInstitution"));
   }
//attributes grid
   setFieldAllSubstituteValues ( ifds::TradeAttributesFields, 
                                 idDataGroup, 
                                 redemptionAttributeSubstList);
//pay type, set default
   DString payType;

   getField (ifds::TradesPayType, payType, idDataGroup, false);
   if (payType.empty())
   {
      payType = PAYTYPE::SYSTEM_CHEQUE;
      setFieldNoValidate ( ifds::TradesPayType, payType, idDataGroup, false, 
                           false, 
                           true, 
                           false);  //no related changes
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Redemption::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   Trade::doInit (data);
   DString accountNum;

   getField (ifds::AccountNum, accountNum, BF::HOST, false);

   if (!isMgmtFee (BF::HOST) && !isAdvisorFee(BF::HOST))
   {
      loadDepRedCodeSubstList ( accountNum, 
                                I_("R"),  //redemption code type
                                BF::HOST);
   }
   redCodeRelatedChanges (BF::HOST);
   withholdingTaxRelatedChanges (BF::HOST);
   thirdPartyFundRelatedChanges (BF::HOST);

   bool bFeeApplicable;
   isFeeApplicable (REDEMPTION_TPA_FEE, bFeeApplicable, BF::HOST);

   if (bFeeApplicable)
   {
      setFieldNoValidate (ifds::GrossOrNet, Y, BF::HOST, false, true, true);
      setFieldReadOnly (ifds::GrossOrNet, BF::HOST, true);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Redemption::doApplyRelatedChanges ( const BFFieldId &idField, 
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   if (Trade::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::AccountNum)
      {
         DString accountNum;

         getField (ifds::AccountNum, accountNum, idDataGroup, false);

         if (!isMgmtFee (idDataGroup) && !isAdvisorFee(idDataGroup))
         {
            loadDepRedCodeSubstList ( accountNum, 
                                      I_("R"),  //redemption code type
                                      idDataGroup);
         }
         withholdingTaxRelatedChanges (idDataGroup);
         setFieldValid (ifds::TradesPayType, idDataGroup, false);
         //if necessary...
         setAccountHoldingsCurrency (idDataGroup);

         bool bFeeApplicable;
         isFeeApplicable (REDEMPTION_TPA_FEE, bFeeApplicable, idDataGroup);

         if (bFeeApplicable)
         {
            setFieldNoValidate (ifds::GrossOrNet, Y, idDataGroup, false, true, true);
            setFieldReadOnly (ifds::GrossOrNet, idDataGroup, true);
         }
      }
      else if (idField == ifds::AmtType)
      {
         DString fundCode,
            classCode;

         if ( getFundField (ifds::FundCode, fundCode, idDataGroup) <= WARNING &&
              getFundField (ifds::ClassCode, classCode, idDataGroup) <= WARNING)
         {
            if (!fundCode.empty() && !classCode.empty())
            {
               DString amtType,
                  loadType;

               getField (ifds::AmtType, amtType, idDataGroup, false);
               getFundField (ifds::LoadType, loadType, idDataGroup);
               if ( DSTCommonFunctions::codeInList (amtType, I_("T,F,M")) &&
                    loadType == I_("BEL"))
               {
                  setFieldNoValidate (ifds::Amount, I_("0"), idDataGroup);
               }
            }
         }
         setFieldValid (ifds::FundCodeRedCodeAmount, idDataGroup, false);

         recalculateEstateAllocation(idDataGroup);
      }
      else if (idField == ifds::RedCode ||
               idField == ifds::RESPContrDetlTaxYear ||
               idField == ifds::LinkedEntityId )        
      {
         if(idField == ifds::RedCode)
         {
            // specific logic for redemption
            redCodeRelatedChanges (idDataGroup);
            withholdingTaxRelatedChanges (idDataGroup);
            removeAllocationsIfAccountCanBeClosed (idDataGroup);
            aggregateOptionRelatedChanges (idDataGroup);
            //if necessary...
            setAccountHoldingsCurrency (idDataGroup);
		    setDefaultForRedCode(idDataGroup);
         }
         if (isRESPTradeAccount(idDataGroup))
         {
            // idField is RedCode, RESPContrDetlTaxYear and Beneficiary Id
            // invoke view 416 to populate 10 percent ACAmount
            DString dstrRedCode, dstrRESPContrDetlTaxYear, dstrLinkedEntityId;
            getField(ifds::RedCode, dstrRedCode, idDataGroup, false);
            getField(ifds::RESPContrDetlTaxYear, dstrRESPContrDetlTaxYear, idDataGroup, false);
            getField(ifds::LinkedEntityId, dstrLinkedEntityId, idDataGroup, false);
            dstrRedCode.strip();
            dstrRESPContrDetlTaxYear.strip();
            dstrLinkedEntityId.strip().stripLeading('0');

            if(dstrRedCode == I_("Q1") &&
               dstrRESPContrDetlTaxYear != NULL_STRING &&
               dstrLinkedEntityId != NULL_STRING)
            {
               
               setDefaultValueRESPAssistedContrAmt(dstrRESPContrDetlTaxYear,
                                                   dstrLinkedEntityId,
                                                   idDataGroup);
            
            }

			bool bEPTrade = (dstrRedCode == I_("EP")) ? true : false;
			setFieldReadOnly (ifds::GrossOrNet, idDataGroup, bEPTrade);

			if (bEPTrade)
				setFieldNoValidate (ifds::GrossOrNet, N, idDataGroup, false, true, true);				
			else
				setFieldValid (ifds::GrossOrNet, idDataGroup, false);
         }

		 DString accountNum, dstrRedCode;
		 getField (ifds::AccountNum, accountNum, idDataGroup, false);
		 getField(ifds::RedCode, dstrRedCode, idDataGroup, false);
		 if (isRDSPTradeAccount (idDataGroup, accountNum) && DSTCommonFunctions::codeInList (dstrRedCode, I_("BP,GP,RB,RG"))) // BP-RDSP Bond Repayment, GP-RDSP Grant Repayment, RB-RDSP Bond Return, RG-RDSP Grant Return
		 {
			  setFieldNoValidate ( ifds::RDSPPaymtDate, _currentBusinessDate, idDataGroup, false, true, true, false);
			  setFieldReadOnly (ifds::RDSPPaymtDate, idDataGroup, false);
		 }
		 else
		 {
			 setFieldNoValidate ( ifds::RDSPPaymtDate, NULL_STRING, idDataGroup, false, true, true, false);
			 setFieldReadOnly (ifds::RDSPPaymtDate, idDataGroup, true);
		 }
      }
      else if (idField == ifds::Amount)
      {
         withholdingTaxRelatedChanges (idDataGroup);
         removeAllocationsIfAccountCanBeClosed (idDataGroup);
         //if necessary...
         setAccountHoldingsCurrency (idDataGroup);

         setSettleLocsInstructionsInvalid (idDataGroup);

         updateNotinalDataWarning (idDataGroup);
         recalculateEstateAllocation(idDataGroup);

      }
      else if (idField == ifds::OverrideTax)
      {
         DString dstrOverrideTax;

         getField( ifds::OverrideTax, dstrOverrideTax, idDataGroup );	
         if ( I_( "N" ) == dstrOverrideTax.stripAll() )
         {
            RedemptionValidation *pRedemptionValidation = NULL;
            if ( getRedemptionValidation (pRedemptionValidation, idDataGroup ) <= WARNING &&
               pRedemptionValidation)
            {
               DString dstrDefaultFedTaxRate, 
                  dstrDefaultProvTaxRate;

               pRedemptionValidation->getField (ifds::FedRate,  dstrDefaultFedTaxRate,  idDataGroup);
               pRedemptionValidation->getField (ifds::ProvRate, dstrDefaultProvTaxRate, idDataGroup);

               setField (ifds::FedRate, dstrDefaultFedTaxRate, idDataGroup, true);
               setField (ifds::ProvRate, dstrDefaultProvTaxRate, idDataGroup, true);
               setField (ifds::TransRatePUDFed, I_("P"), idDataGroup);
               setField (ifds::TransRatePUDProv, I_("P"), idDataGroup);
            }
         }
      }
      else if (idField == ifds::LSIFCode)
      {
//to trigger validation on Ok
         setFieldValid (ifds::FundCodeRedCodeAmount, idDataGroup, false);
         DString amount,
            lsifCode;
         
         getField (ifds::Amount, amount, idDataGroup);
         getField (ifds::LSIFCode, lsifCode, idDataGroup);

         double dec_amount = DSTCommonFunctions::convertToDouble( amount );

         if ( (dec_amount == 0.0)   && 
               ( lsifCode == I_("2")  ||
                 lsifCode == I_("11") ||
                 lsifCode == I_("12")))
         {
            getMaturedUnits (idDataGroup);
         }
      }
      else if (idField == ifds::EffectiveDate)
      {
         setFieldValid (ifds::FundCodeRedCodeAmount, idDataGroup, false);
         withholdingTaxRelatedChanges(idDataGroup);
      }
      else if ( idField == ifds::FromFund ||
                idField == ifds::FromClass)
      {
         removeAllocationsIfAccountCanBeClosed (idDataGroup);
      }
      else if ( idField == ifds::Broker ||  idField == ifds::OrderSource )
      {
         setFieldValid (ifds::SettleSource, idDataGroup, false); //invalidate settle source
      }
      else if ( idField == ifds::GRRepayReason )
      {
		 DString redCode;
		 getField(ifds::RedCode, redCode, idDataGroup, false);

         // Some scenario, user changes reason from others to I01, I02 after assoctranid is valid.
         // Assoctransid should be revalidated.
         if ( isAssociationToOriginalContribAllowed (idDataGroup) )
         {
            setFieldValid (ifds::AssocTransId, idDataGroup, false); //invalidate AssocTransId

            // no need to report to HRDC if grant repayment reason is either I01 or I02
            setFieldNoValidate (ifds::RESPReportHRDC, I_("N"), idDataGroup, false);
         }
         else if (!DSTCommonFunctions::codeInList (redCode, I_("SC,BC")))
         {
            setFieldNoValidate (ifds::RESPReportHRDC, I_("Y"), idDataGroup, false);
         }
      }
	  else if ( idField == ifds::PayInstrOption || idField == ifds::TradesPayType )
	  {
		DString dstrPayInstrOption,dstrTradesPayType;
		DString dstrTradePymtRoutingMthd = NULL_STRING;
		getField(ifds::PayInstrOption, dstrPayInstrOption, idDataGroup);
		getField(ifds::TradesPayType, dstrTradesPayType, idDataGroup);
		DString dstrTradelevelOveride ;
		getWorkSession ().getOption (ifds::TradelevelOveride, dstrTradelevelOveride, BF::HOST, false);
		if( dstrTradelevelOveride == YES && 
			dstrTradesPayType == PAYTYPE::EFT && 
			dstrPayInstrOption == I_("02"))//redirect to shareholder
		{
			setFieldReadOnly(ifds::PymtRoutingMthd, idDataGroup, false); 
			getField(ifds::PymtRoutingMthd, dstrTradePymtRoutingMthd, idDataGroup);
		    dstrTradePymtRoutingMthd.stripAll();
			if(!_bInitPending && dstrTradePymtRoutingMthd.empty()) 
			{
              setPaymentRoutingSetDefault(idDataGroup);
			}
		}
		else
		{
		 setFieldNoValidate(ifds::PymtRoutingMthd, NULL_STRING, idDataGroup, false, false);
		 setFieldReadOnly(ifds::PymtRoutingMthd, idDataGroup, true ) ;
		}
	  }
	  else if (idField == ifds::FullMoneyOutIndc)        
	  {  
		  redCodeRelatedChanges (idDataGroup);
	  }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::doValidateField ( const BFFieldId &idField, 
                                       const DString &strValue, 
                                       const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));

   if ( (idField == ifds::FromFund  || idField == ifds::FromClass || idField == ifds::ToFund || idField == ifds::ToClass) && isAllFundsFullMoneyOutIndc(idDataGroup) )
   {
      ;//skip validation
   }
   else if (Trade::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::AmountGrossNet)
      {
         validateAmountGrossNet (idDataGroup);
      }
      else if( idField == ifds::FedTaxRatePUD )
      {
         validateTaxRatePUD (I_("Federal"), idDataGroup);
      }
      else if( idField == ifds::ProvTaxRatePUD )
      {
         validateTaxRatePUD (I_("Provincial"), idDataGroup);
      }
      else if (ifds::FedProvTaxRatePUDXEdit == idField)
      {
         validateFedProvTaxRatePUD (idDataGroup);
      }
      else if (idField == ifds::FundBrokerCode)
      {
         validateFundBrokerCode (strValue, idDataGroup);
      }
      else if (idField == ifds::SuppressCode)
      {
         validateSuppressCode (idDataGroup);	
      }
      else if (idField == ifds::OrderType)
      {
         validateStopSettleRedemption (strValue, idDataGroup);
      }
      else if (idField == ifds::RESPReportHRDC)
      {
         validateRESPReportHRDC (strValue, idDataGroup);
      }
      else if (idField == ifds::GRRepayReason)
      {
         validateGrantRepaymentReason (strValue, idDataGroup);
      }
      else if (idField == ifds::RedCodeOCRdmYearXEdit)
      {
         DString ocRedmYear;
         getField( ifds::OCRdmYear, ocRedmYear, idDataGroup, false);
         ocRedmYear.strip().upperCase();

         validateOverContrbRedmYear (ocRedmYear, idDataGroup);
      }
      else if (idField == ifds::RedCodeTaintedXEdit)
      {
         DString tainted;
         getField( ifds::Tainted, tainted, idDataGroup, false);
         tainted.strip().upperCase();

         validateTainted(tainted,idDataGroup);
      }
      else if (idField == ifds::LinkedEntityId)
      {
         validateAIPEntity (idDataGroup);
         //P0185010.FN02.R02.01 - Delivering EAP written notice and tax info return
         validateEAPEntityAddress(idDataGroup);
      }
      else if(idField == ifds::SrcOfFund)
      {
         validateSrcOfFund(strValue, idDataGroup);
      }
      else if(idField == ifds::XRedCode)
      {
         validateXRedCode(idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateXRedCode(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateXRedCode"));
   DString redCode;
   getField(ifds::RedCode, redCode, idDataGroup, false);

   DString dstrDeathRedCode;
   DString dstrResidency1;
   DString dstrResidency2;
   DString dstrResidency3;
   DString dstrSpouseBenefReLn;
   DString dstrChildBenefReLn;
   
   getWorkSession().getOption ( ifds::Residency1, dstrResidency1, BF::HOST, false);
   getWorkSession().getOption ( ifds::Residency2, dstrResidency2, BF::HOST, false);
   getWorkSession().getOption ( ifds::Residency3, dstrResidency3, BF::HOST, false);
   
   getWorkSession().getOption ( ifds::SpouseBenefReLn, dstrSpouseBenefReLn, BF::HOST, false);
   getWorkSession().getOption ( ifds::ChildBenefReLn,  dstrChildBenefReLn,  BF::HOST, false);
   getWorkSession().getOption ( ifds::DeathRedCode,    dstrDeathRedCode,    BF::HOST, false);

   MFAccount *pMFAccount = NULL;
   if (DSTCommonFunctions::codeInList(redCode, dstrDeathRedCode) && 
        getAccount ( pMFAccount, idDataGroup) <= WARNING  && pMFAccount) 
   {
      ACCTENTITYOBJ_VECTOR vBenefEntities;
      pMFAccount->getBeneficiaries(vBenefEntities, idDataGroup );    
      ACCTENTITYOBJ_VECTOR::iterator iter = vBenefEntities.begin();
      while(iter != vBenefEntities.end())
      {
         DString dstrTaxJurisCode;
         AccountEntityXrefObject* pAccountEntityXrefObject = *iter;
         if(pAccountEntityXrefObject)
         {
            DString dstrEntityId;
            pAccountEntityXrefObject->getField(ifds::EntityId, dstrEntityId, idDataGroup);

            pAccountEntityXrefObject->getField(ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup);
            dstrTaxJurisCode.strip();
            bool bTaxJurisInRecidencyCodes = 
                  DSTCommonFunctions::codeInList(dstrTaxJurisCode, dstrResidency1) ||
                  DSTCommonFunctions::codeInList(dstrTaxJurisCode, dstrResidency2) ||
                  DSTCommonFunctions::codeInList(dstrTaxJurisCode, dstrResidency3);

            if(dstrTaxJurisCode.strip() == I_("") ||
               (redCode == I_("07") || redCode == I_("41")) && bTaxJurisInRecidencyCodes ||
               (redCode == I_("08") || redCode == I_("34") || redCode == I_("57") || redCode == I_("58") ) && !bTaxJurisInRecidencyCodes)
            {
               DString idiStr;
               addIDITagValue (idiStr, I_("EntityID"), dstrEntityId);
               ADDCONDITIONFROMFILEIDI(CND::ERR_REDCODE_AND_TAXJURIS_DO_NOT_MATCH_FOR_BENEFICIARY, idiStr);
               break;
            }

            DString dstrRelateCode;
            pAccountEntityXrefObject->getField(ifds::RelateCode, dstrRelateCode, idDataGroup);

            DString dstrSegClient;
            getWorkSession().getOption (ifds::SegClient, dstrSegClient, BF::HOST);
   //               bool bSegFund = isSegTrade(idDataGroup);
            bool bSegFund = dstrSegClient.strip() == I_("Y");

            if(redCode == I_("57") && !DSTCommonFunctions::codeInList(dstrRelateCode, dstrSpouseBenefReLn) ||
               redCode == I_("58") && !DSTCommonFunctions::codeInList(dstrRelateCode, dstrChildBenefReLn)  ||
               redCode == I_("41") && !bSegFund && !DSTCommonFunctions::codeInList(dstrRelateCode, dstrChildBenefReLn) && !DSTCommonFunctions::codeInList(dstrRelateCode, dstrSpouseBenefReLn)     ||
               redCode == I_("41") && bSegFund && !DSTCommonFunctions::codeInList(dstrRelateCode, dstrSpouseBenefReLn)    ||
               redCode == I_("58") && bSegFund)
            {
               DString idiStr;
               addIDITagValue (idiStr, I_("entityid"), dstrEntityId);
               addIDITagValue (idiStr, I_("redcode"),  redCode);

               ADDCONDITIONFROMFILEIDI(CND::ERR_ENTITY_CANNOT_BE_USED_WITH_REDEMPTION_CODE, idiStr);
               break;
            }
         }
         iter++;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}





//******************************************************************************
SEVERITY Redemption::validateRedCode ( const DString &redCode, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRedCode"));
      
   /* RedCode 01 : CASH
      RedCode 23 : Shortened Life Expectancy
      RedCode 24 : LLP Withdrawal
      RedCode 32 : Death Transfer to Annuity
      RedCode 33 : Death Transfer to Annuity - Close Account
      RedCode 51 : Partial Transfer Out of RRIF/LIF/LRIF
      RedCode 52 : Full Transfer Out (Close a/c) RRIF/LIF/L
      RedCode 53 : Transfer to Purchase Annuity from RRIF
   */
   if (Trade::validateRedCode (redCode, idDataGroup) <= WARNING)
   {
   //if RedCode is listed in TRExclRedCodes and AccountNum = 0, issue error, mainly for API
      DString trexclRCList,
         accountNum,
         lipClient;

      getWorkSession().getOption ( ifds::TRExclRedCodes, 
                                   trexclRCList, 
                                   BF::HOST,
                                   false);
      getWorkSession().getOption ( ifds::LipClient, 
                                   lipClient, 
                                   idDataGroup, 
                                   false);
      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      accountNum.stripLeading ('0').strip();
      if (DSTCommonFunctions::codeInList (redCode, trexclRCList) && accountNum.empty())
      {
         ADDCONDITIONFROMFILE (CND::ERR_ACCOUNT_NUM_NEEDED_FOR_CLOSE_ACCOUNT);
      }
      else
      {
         DString amtType;

   // For full Redemption, Amount Type must be 'M','F' or 'T'
         getField (ifds::AmtType, amtType, idDataGroup);
         if ( !DSTCommonFunctions::codeInList (amtType, I_("T,F,M")) && 
               DSTCommonFunctions::codeInList (redCode, trexclRCList))
         {
            //ADDCONDITIONFROMFILE (CND::ERR_FULL_REDEMPTION_INDICATED); //give a warning
            raiseFullRedemptionMessage(idDataGroup);
         }
         MFAccount *pMFAccount = NULL;
         if ( getAccount ( pMFAccount, idDataGroup) <= WARNING  && 
              pMFAccount) 
         {            
            DString taxType,
               dstrDofBirth;

            pMFAccount->getDofBirthofOwnerSeq01 (dstrDofBirth, idDataGroup);
            pMFAccount->getField( ifds::TaxType, taxType, idDataGroup );
            taxType.strip().upperCase();
            TaxTypeRule *pTaxTypeRule = NULL;
            if ( pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
            {
               // if year of EffectiveDate >= year of current business date 
               // and minimumapplies and maximumapplies = yes
               // issue warning
               DString effectiveDate, 
                  dstrMaxApplies (N), 
                  dstrMinApplies (N);
               int effectiveYear (0), 
                  currBusDateYear (0);

               getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
               effectiveYear = DSTCommonFunctions::getYearFromUnFormattedDate (effectiveDate);
               currBusDateYear = DSTCommonFunctions::getYearFromUnFormattedDate (_currentBusinessDate);
               if (effectiveYear >= currBusDateYear)
               {
                  RedCodeByTaxTypeList *pRedCodeList = NULL;
                  
                  pTaxTypeRule->getRedCodeList (pRedCodeList, idDataGroup);
                  if (pRedCodeList)
                  {
                     RedCodeByTaxType *pRedCode = NULL;

                     if ( pRedCodeList->getRedCodeByTaxType (redCode, pRedCode, idDataGroup) &&
                          pRedCode)
                     {
                        pRedCode->getField (ifds::MaximumApplies, dstrMaxApplies, idDataGroup, false);
                        pRedCode->getField (ifds::MinimumApplies, dstrMinApplies, idDataGroup, false);

                        DString payType;

                        getField (ifds::TradesPayType, payType, idDataGroup);
                        if (payType == PAYTYPE::DIRECT)
                        {
                           DString dstrDTAEligible;

                           pRedCode->getField (ifds::DTAEligible, dstrDTAEligible, BF::HOST, false);
                           if (dstrDTAEligible == I_("0"))
                           {
                              ADDCONDITIONFROMFILE (CND::ERR_DTA_NOT_ALLOWED_FOR_THIS_REDCODE);
                           }
                        }

                        if (dstrMaxApplies.strip().upperCase() == Y)
                        {
                           ADDCONDITIONFROMFILE (CND::ERR_WARN_MAXMIN_AMT_RECALCULATION);
                        }

                        if (dstrMinApplies.strip().upperCase() == Y)
                        {
                           DString grossOrNet;

                           getField (ifds::GrossOrNet, grossOrNet, idDataGroup, false);

                           if (grossOrNet == NET) //net
                           {
                              RedemptionValidation *pRedemptionValidation = NULL;

                              if (getRedemptionValidation (pRedemptionValidation, idDataGroup) <= WARNING  && pRedemptionValidation)
                              {
                                 DString amtOverMin;
                                 pRedemptionValidation->getField (ifds::AmtOverMin, amtOverMin, idDataGroup);

                                 if (amtOverMin == YES)
                                 {
                                    getErrMsg (IFASTERR::NET_REDEMPTION_OVER_MINIMUM,
                                               CND::ERR_NET_REDEMPTION_OVER_MINIMUM, 
                                               CND::WARN_NET_REDEMPTION_OVER_MINIMUM,
                                               idDataGroup);
                                 }
                              }
                           }
                           else // gross
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
   //if RedCode is '01', LipClient-83 is 'yes', DofBirth is null and LockedIn-87 is 'yes' - issue warning
               if (redCode == I_("01") && lipClient == Y)
               {
                  DString lockedIn;

                  pTaxTypeRule->getField (ifds::LockedIn, lockedIn, idDataGroup, false);
                  if (dstrDofBirth.empty() && lockedIn == Y)
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_WARN_DATE_OF_BIRTH_REQUIRED_FOR_CASH_REDEMPTION);
                  }
               }
            }

         if ( ( getWorkSession ().isLIFLike (taxType) || I_( "L" ) == taxType ) &&
            I_( "01" ) == redCode ) 
         {
            // IN 650931
            // Withdrawal Code illegal for the Account's tax type				
            ADDCONDITIONFROMFILE( CND::ERR_ILLEGAL_REDEMPTION_CODE_FOR_ACCT_TAX_TYPE );
         }
   //if RedCode = '24'
         //Case 1: DofBirth = blank, issue error
         //Case 2: DofBirth != blank and year of EffectiveDate - year of DofBirth > 69, issue error
         //case 3: DofDeath != blank, issue error
         //case 4: TaxJurisCode-69 is not listed in Residency1-83, Residency2-83 or Residency3-83, issue error
         if (redCode == I_("24"))
         {
   //Case 1
            DString dstrDofDeath;
            int OwnerAge(0);

            pMFAccount->getDofDeathofOwnerSeq01 (dstrDofDeath, idDataGroup);
            OwnerAge = pMFAccount->getAgeofOwnerSeq01 (idDataGroup);

            if (dstrDofBirth.empty())
            {
               ADDCONDITIONFROMFILE (CND::ERR_MISSING_ACCTHOLDER_DOFBIRTH) ;
            }
   //Case 2
            else
            {
               if (OwnerAge > 71)
               {
                  ADDCONDITIONFROMFILE (CND::ERR_TRANSACTION_NOT_ALLOWED_AFTER_69);
               }
            }
   //Case 3
            if (!dstrDofDeath.empty())
            {
               ADDCONDITIONFROMFILE (CND::ERR_DEATH_DATE_EXIST_FOR_ACCTHOLDER);
            }
   //Case 4
            DString residency1, 
               residency2, 
               residency3, 
               dstrTaxJurisCode, 
               dstrShrNum;

            getWorkSession().getOption (ifds::Residency1, residency1, BF::HOST, false);
            getWorkSession().getOption (ifds::Residency2, residency2, BF::HOST, false);
            getWorkSession().getOption (ifds::Residency3, residency3, BF::HOST, false);

            pMFAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup);
            Shareholder *pShareholder = NULL;

            if ( getWorkSession().getShareholder (idDataGroup, dstrShrNum, pShareholder) <= WARNING &&
                 pShareholder)
            {
               pShareholder->getField (ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup);
            }

            if( !( DSTCommonFunctions::codeInList (dstrTaxJurisCode, residency1) ||
                  DSTCommonFunctions::codeInList (dstrTaxJurisCode, residency2) ||
                  DSTCommonFunctions::codeInList (dstrTaxJurisCode, residency3) ))
            {
               ADDCONDITIONFROMFILE (CND::ERR_CANADIAN_RESIDENT_WITHDRAW);
            }
         } //red code 24
   //Redemption code in the death redemption code list
   //case 1: m_strCotClient is 'yes' and DeathClaim-4 is 'yes' then error # 229
   //case 2: m_strCotClient is 'yes' and DeathClaim-4 is 'no' then error # 222
   //case 3: dstrDofDeath is null, issue error
            DString dstrDeathRedCode;
            getWorkSession().getOption ( ifds::DeathRedCode, 
                                         dstrDeathRedCode, 
                                         BF::HOST, 
                                         false);
            DString dstrDeathClaim, 
                    dstrDofDeath,
                    dstrDeathStat,
                    cotClient;

            pMFAccount->getField (ifds::DeathClaim, dstrDeathClaim, idDataGroup );
            pMFAccount->getField (ifds::DeathStat, dstrDeathStat, idDataGroup );
            pMFAccount->getDofDeathofOwnerSeq01 (dstrDofDeath, idDataGroup);
            getWorkSession ().getOption ( ifds::CotClient, 
                                          cotClient, 
                                          BF::HOST, 
                                          false);
            cotClient.strip ().upperCase ();
            if (isSegTrade (idDataGroup))
            {
               /* Account has Pending Death Claim Status and entered Redemption Code 
                * is not in the List of the valid Death Claim Redemption Codes
                */
               if (dstrDeathClaim == Y)
               {
                  if ( !DSTCommonFunctions::codeInList(redCode, dstrDeathRedCode))
                  {
                     getErrMsg ( IFASTERR::MUST_ENTER_A_DEATH_CLAIM_REDEMPTION_CODE, //229
                                 CND::ERR_DEATH_CLAIM_REDEMPTION_CODE, 
                                 CND::ERR_WARN_DEATH_CLAIM_REDEMPTION_CODE, 
                                 idDataGroup); 

                  }
                  else  if (dstrDofDeath.empty())
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_ACCOUNTHOLDER_DEATH_DATE_REQUIRED);
                  }

               }
               /* Account has Acitve Contract Status and entered Redemption Code is in
                * the list of the valid Death Claim Redemption Codes
                */
               else if (dstrDeathClaim == N && dstrDeathStat == N )
               {
                  if ( DSTCommonFunctions::codeInList(redCode, dstrDeathRedCode))
                  {
                     getErrMsg ( IFASTERR::CONTRACT_ACCOUNT_STATUS_IS_ACTIVE, //222
                                 CND::ERR_CONTRACT_ACCT_STATUS_ACTIVE, 
                                 CND::ERR_WARN_CONTRACT_ACCT_STATUS_ACTIVE, 
                                 idDataGroup); 
                  }
               }

            /* if (DSTCommonFunctions::codeInList(redCode, dstrDeathRedCode))
            {
               DString dstrDeathClaim, 
                  dstrDofDeath,
                  cotClient;

               pMFAccount->getField (ifds::DeathClaim, dstrDeathClaim, idDataGroup );
               pMFAccount->getDofDeathofOwnerSeq01 (dstrDofDeath, idDataGroup);
               getWorkSession ().getOption ( ifds::CotClient, 
                                             cotClient, 
                                             BF::HOST, 
                                             false);
               cotClient.strip ().upperCase ();
               if (cotClient == Y)
               {
                  //case 1
                  if (dstrDeathClaim == Y)
                  {
                     getErrMsg ( IFASTERR::MUST_ENTER_A_DEATH_CLAIM_REDEMPTION_CODE, //229
                                 CND::ERR_DEATH_CLAIM_REDEMPTION_CODE, 
                                 CND::ERR_WARN_DEATH_CLAIM_REDEMPTION_CODE, 
                                 idDataGroup); 
                  }
                  //case 2
                  else
                  {
                     getErrMsg ( IFASTERR::CONTRACT_ACCOUNT_STATUS_IS_ACTIVE, //222
                                 CND::ERR_CONTRACT_ACCT_STATUS_ACTIVE, 
                                 CND::ERR_WARN_CONTRACT_ACCT_STATUS_ACTIVE, 
                                 idDataGroup); 
                  }
               } */
               //case 3
               //if (dstrDofDeath.empty())
               //{
               //   ADDCONDITIONFROMFILE (CND::ERR_ACCOUNTHOLDER_DEATH_DATE_REQUIRED);
               //}
            }

            // Following are implemented by Celia for the missing rules
            /* Missing business rule for the ticket 10013247
             * If  RedCode-115 is one of ’32’, ‘52’ or ‘53’ or (RedCode = ‘51’ and TransAsFull-83 = Yes) 
             * and  LockedIn-87 = Yes and PlanType-87 = ‘RIF’ and RRIFDetlErr-143 = No  
             * and RedCodesErr-143 = No and RemAmtPayFirst-143 > 0, display error with severity 
             * depending on the view 142 as follows : Find  record with ErrNum-142 = 134.  
             * If EWI-142 is equal to ‘I’, don’t issue error message. If EWI-142 is ‘W’, issue just 
             * a warning. If EWI-142 is equal to ‘E’ then issue error message. The message is in field 
             * ErrMsg-142.
             */
            if (DSTCommonFunctions::codeInList (redCode, I_("01,24,32,51,52,53"))) //RRIF/LIF transfer code list
            {
               RedemptionValidation *pRedemptionValidation = NULL;
               if ( getRedemptionValidation (pRedemptionValidation, idDataGroup) <= WARNING  && 
                    pRedemptionValidation)
               {
                  if (DSTCommonFunctions::codeInList (redCode, trexclRCList))
                  {
                     DString transExist;

                     pRedemptionValidation->getField (ifds::TransExist, transExist, idDataGroup);
                     transExist.strip().upperCase();
                     if (transExist == Y)
                     {
                        ADDCONDITIONFROMFILE (CND::ERR_ACCT_CANNOT_BE_CLOSE);
                     }
                  }
                  if (GETCURRENTHIGHESTSEVERITY () <= WARNING) //check other rules
                  {
                     validateLifTransferRedCode(redCode, idDataGroup);
                  } //account cannot be closed
                  if (redCode == I_("24"))
                  {
                     DString strLLPValMsg;
                     pRedemptionValidation->getField (ifds::LLPValMsg, strLLPValMsg, idDataGroup );
                     if (!strLLPValMsg.empty())
                     {
                        DString idiStr;
                        addIDITagValue (idiStr,I_("FIELDNAME"), strLLPValMsg);

                        ADDCONDITIONFROMFILEIDI (CND::ERR_LIP_VAL_MSG, idiStr);
                     }
                  }
                  if (redCode == I_("01"))
                  {
                     if (lipClient == Y)
                     {
                        DString strMinWithAgeErr1, 
                           strMinWithAgeErr2, 
                           strPenInfoErr, 
                           strTaxTypeRulErr;

                        pRedemptionValidation->getField (ifds::MinWithAgeErr1, strMinWithAgeErr1, idDataGroup);
                        if (strMinWithAgeErr1 == Y)
                        {
                           ADDCONDITIONFROMFILE (CND::ERR_CLIENT_AGE_LESS_THAN_MINWITHAGE1);
                        }
                        pRedemptionValidation->getField (ifds::MinWithAgeErr2, strMinWithAgeErr2, idDataGroup);
                        if (strMinWithAgeErr2 == Y)
                        {
                           ADDCONDITIONFROMFILE (CND::ERR_CLIENT_AGE_LESS_THAN_MINWITHAGE2);
                        }
                        pRedemptionValidation->getField (ifds::PenInfoErr, strPenInfoErr, idDataGroup);
                        if (strPenInfoErr == Y)
                        {
                           ADDCONDITIONFROMFILE (CND::ERR_NO_PENSION_INFO);
                        }
                        pRedemptionValidation->getField (ifds::TaxTypeRulErr, strTaxTypeRulErr, idDataGroup);
                        if (strTaxTypeRulErr == Y)
                        {
                           ADDCONDITIONFROMFILE (CND::ERR_NO_TAXTYPE_RULE);
                        }
                     }
                  }
               } // if (pRedemptionValidation)
            }  // RRIF/LIF transfer code list
            if (redCode== I_("EF"))
            {
               DString dstrShrNum;

               pMFAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup);
               Shareholder *pShareholder = NULL;
               DString AcctDesignation;
               if (getWorkSession().getShareholder (idDataGroup, dstrShrNum, pShareholder) <= WARNING &&
                   pShareholder)
               {
                  pShareholder->getField(ifds::AcctDesignation, AcctDesignation, idDataGroup);
               }
               if (AcctDesignation == I_("1"))
               {
                  ADDCONDITIONFROMFILE (CND::ERR_EF);	
               }
            }
            if ( redCode == REDCODE_CLB_RETURN ||
                 //redCode == REDCODE_ACES_RETURN ||
                 //redCode == REDCODE_CESG_RETURN)
                 redCode == REDCODE_ACES_RETURN || 
				 redCode == REDCODE_SAGES_GRANT_RETURN )
            {
               DString dstrSiblingOnly;
               
               pMFAccount->getField(ifds::SiblingOnly, dstrSiblingOnly, idDataGroup, false);
               dstrSiblingOnly.strip().upperCase();
               if (dstrSiblingOnly != YES)
               {
                  // raise rejerror 710
                  DString idiStr;
                  addIDITagValue (idiStr, I_("CODE_TYPE"), I_("Redemption Code"));

                  getErrMsg ( IFASTERR::DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS,
                              CND::ERR_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS,
                              CND::WARN_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS,
                              idDataGroup,
                              idiStr);

               }
            }
// validation from PET0165541 QESI Transaction. Section A, 2 
            if (DSTCommonFunctions::codeInList (redCode, RESP_TRANSFER_RED_CODES))
            {
               DString aipWithdrawalExists;
               
               pMFAccount->getField (ifds::AIPWithdrawalExists, aipWithdrawalExists, idDataGroup, false);
               aipWithdrawalExists.strip().upperCase();

               if (aipWithdrawalExists == Y)
               {
                  // raise rejerror 322
                  getErrMsg ( IFASTERR::AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED,
                              CND::ERR_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED,
                              CND::WARN_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED,
                              idDataGroup ); 
               }
            }
            if(DSTCommonFunctions::codeInList (redCode, I_("64,65")))
            {
               ADDCONDITIONFROMFILE(CND::WARN_RESP_TRANSFER_OUT);
            }
            
            if (DSTCommonFunctions::codeInList (redCode, dstrDeathRedCode))
            {
               // do checking for annuitant owner DOD
               DString dstrDofDeath;
               DString dstrSegClient;
               getWorkSession().getOption (ifds::SegClient, dstrSegClient, BF::HOST);
               dstrSegClient.strip();
               if(dstrSegClient == I_("Y"))
                  pMFAccount->getDofDeathofEntityType (ENTITY_ANNUITANT,dstrDofDeath, idDataGroup);//Modified for INC0033364
               else
                  pMFAccount->getDofDeathofOwnerSeq01(dstrDofDeath, idDataGroup);

               dstrDofDeath.strip();

               if( (DSTCommonFunctions::CompareDates (dstrDofDeath, I_("12319999"))== DSTCommonFunctions::EQUAL) ||
                     dstrDofDeath.empty() )
               {
                  DString idiStr;
                  addIDITagValue (idiStr, I_("ENTITY_TYPE"), I_("Annuitant"));
                  getErrMsg ( IFASTERR::DOD_ENTITY_TYPE_MISSING,
                              CND::ERR_DOD_ENTITY_TYPE_MISSING,
                              CND::WARN_DOD_ENTITY_TYPE_MISSING,
                              idDataGroup,
                              idiStr );
               }

            }
         } //MFAccount
      }
      validateRedCodeAgainstWDFeeDefault( idDataGroup );
      
      validateRedCodeUnclaimedProperty( idDataGroup );
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateLifTransferRedCode(const DString &redCode,
                                                const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE(CLASSNAME, I_("vaidateLifTransferRedCode"));

    if (!DSTCommonFunctions::codeInList(redCode, I_("32,51,52,53"))) // lif transfer list
        return GETCURRENTHIGHESTSEVERITY();

    MFAccount *pMFAccount = nullptr;
    if (getAccount(pMFAccount, idDataGroup) > WARNING || !pMFAccount)
        return GETCURRENTHIGHESTSEVERITY();

    DString taxType;
    pMFAccount->getField(ifds::TaxType, taxType, idDataGroup);
    taxType.strip().upperCase();

    TaxTypeRule *pTaxTypeRule = nullptr;
    if (pMFAccount->getTaxTypeRule(pTaxTypeRule, idDataGroup) > WARNING || !pTaxTypeRule)
        return GETCURRENTHIGHESTSEVERITY();

    DString strPlanType;
    pTaxTypeRule->getField(ifds::PlanType, strPlanType, idDataGroup);
    strPlanType.strip().upperCase();

    DString strLockedIn;
    pTaxTypeRule->getField(ifds::LockedIn, strLockedIn, idDataGroup);
    strLockedIn.strip().upperCase();

    DString strRRIFDetlErr, strRedCodesErr, partTransAsFull;
    RedemptionValidation *pRedemptionValidation = nullptr;
    if (getRedemptionValidation(pRedemptionValidation, idDataGroup) > WARNING ||
        !pRedemptionValidation)
        return GETCURRENTHIGHESTSEVERITY();

    getWorkSession().getOption(ifds::PartTransAsFull, partTransAsFull, BF::HOST, false);
    partTransAsFull.strip().upperCase();

    pRedemptionValidation->getField(ifds::RRIFDetlErr, strRRIFDetlErr, idDataGroup);
    strRRIFDetlErr.strip().upperCase();

    pRedemptionValidation->getField(ifds::RedCodesErr, strRedCodesErr, idDataGroup);
    strRedCodesErr.strip().upperCase();

    if (strPlanType == I_("RIF") && strRRIFDetlErr == Y)
    {
        getErrMsg(IFASTERR::SCHEDULED_PAYMENT_INFORMATION_NOT_AVAILABLE, // 137
                  CND::ERR_SCHEDULED_PAYMENT_NOT_AVAILABLE,
                  CND::WARN_SCHEDULED_PAYMENT_NOT_AVAILABLE, idDataGroup);
    }
	/* Notes - RedCodesErr == N means the the validation fails. 
	Please refer to REMMIN0.P for more details */
    else if (strRedCodesErr == I_("N"))
    {
        getErrMsg(IFASTERR::REDEMPTION_CODE_RULES_NOT_SETUP, // 138
                  CND::ERR_REDEMPTION_CODE_RULES_NOT_SETUP,
                  CND::WARN_REDEMPTION_CODE_RULES_NOT_SETUP, 
				  idDataGroup);
    }
	
    else if ((redCode != I_("51") || partTransAsFull == Y) &&
		strPlanType == I_("RIF") && strLockedIn == Y)
    {
        DString strRemAmtPayFirst;
        pRedemptionValidation->getField(ifds::RemAmtPayFirst, strRemAmtPayFirst, idDataGroup);
        auto dec_RemAmtPayFirst = DSTCommonFunctions::convertToDouble(strRemAmtPayFirst);

        if (dec_RemAmtPayFirst > 0)
        {
            DString idiStr;
            addIDITagValue(idiStr, I_("amount"), strRemAmtPayFirst);
            getErrMsg(IFASTERR::REMAINING_MINIMUM_AMOUNT_MUST_BE_PAID_FIRST, // 134
                      CND::ERR_REMAIN_AMOUNT_MUSTBE_PAID, 
					  CND::WARN_REMAIN_AMOUNT_MUSTBE_PAID,
                      idDataGroup, 
					  idiStr);
        }
    }

    else if (redCode == I_("51") && partTransAsFull == N)
    {
        DString strLowRemainBal;
        pRedemptionValidation->getField(ifds::LowRemainBal, strLowRemainBal, idDataGroup);
        strLowRemainBal.strip().upperCase();
        if (strLowRemainBal == Y)
        {
            getErrMsg(IFASTERR::REMAINING_ACCT_BALANCE_IS_INSUFFICIENT, // 135
                      CND::ERR_REMAIN_ACCT_BALANCE, 
					  CND::WARN_REMAIN_ACCT_BALANCE, 
					  idDataGroup);
        }
    }

	removeAllocationsIfAccountCanBeClosed (idDataGroup);
    return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Redemption::validateFundCodeRedCodeAmount (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundCodeRedCodeAmount"));

   DString redCode, 
      accountNum,
      fundCode, 
      classCode,
      amount;

   getField (ifds::Amount, amount, idDataGroup);
   getField (ifds::RedCode, redCode, idDataGroup);
   getField (ifds::FromFund, fundCode, idDataGroup);
   getField (ifds::FromClass, classCode, idDataGroup);
   getField (ifds::AccountNum, accountNum, idDataGroup, false);

   double dec_amount = DSTCommonFunctions::convertToDouble (amount);

   if ( DSTCommonFunctions::codeInList (redCode, BEARERREDCODELIST) &&
        DSTCommonFunctions::NumOfDecimals (amount) != 0)
   {
      ADDCONDITIONFROMFILE (CND::ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS);
   }
//deal with full redemptions/close accounts/close funds
   DString trexclRCList,
      fullRedCode;

   getWorkSession().getOption ( ifds::TRExclRedCodes, 
                                trexclRCList, 
                                BF::HOST,
                                false);
   getWorkSession().getOption ( ifds::FullRedCode, 
                                fullRedCode, 
                                BF::HOST, 
                                false);
//if redemption is part of the codes, used to close an account
   if (DSTCommonFunctions::codeInList (redCode, trexclRCList))
   {
      if (dec_amount != 0)
      {
         //the amount should be zero
         ADDCONDITIONFROMFILE (CND::ERR_AMOUNT_MUST_BE_ZERO_WHEN_CLOSING_ACCOUNT);
      }
      //also the fund code must be blanked out
      if (!fundCode.empty())
      {
         ADDCONDITIONFROMFILE (CND::ERR_FUND_CODES_MUST_BE_BLANK_FOR_REDEMPTION);
      }
   }
   else if (!DSTCommonFunctions::codeInList (redCode, fullRedCode)) // if neither full redemption nor close acct
   {
      if (dec_amount == 0 && fundCode.empty() && !isAllFundsFullMoneyOutIndc(idDataGroup))
      {
         ADDCONDITIONFROMFILE (CND::ERR_SPECIFIE_FUND_WHEN_AMOUNT_IS_ZERO);
      }
   }
//close fund redemption
   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      //1. If redcode = '90 - Close Fund', only unallocated trade and full redemption, transfer-out
      //or exchange-out is allowed
      //2. If redcode = '90 - Close Fund', only PayInterestOn flag is '03' allowed
      if (redCode == I_("90"))
      {
         if ((fundCode.empty() && classCode.empty()) || dec_amount != 0)
         {
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_CLOSE_FUND_REDEMPTION);
         }
//check if PayIntOn on Fund Master is set to '03' - Interest on Close Fund
         FundMasterList *pFundMasterList; 
         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING &&
              pFundMasterList)
         {
            DString payIntOn;
            FundMaster *pFundMaster = NULL;

            if ( pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster) &&
                 pFundMaster
               )
            {
               pFundMaster->getField (ifds::PayIntOn, payIntOn, idDataGroup, false);
            }
            if (payIntOn != I_("03"))
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_INTEREST_ON_CLOSE_FUND_REDEMPTION);
            }
         }
      }
   }
   if (validateFundBalance (accountNum, fundCode, classCode, amount, idDataGroup) <= WARNING)
   {
   //lsif available units validation
   //get the fund master list      
      FundMasterList *pFundMasterList = NULL; 
   //check if fund is LSIF
      if ( !fundCode.empty() &&
           !classCode.empty() &&
           getMgmtCo().getFundMasterList( pFundMasterList ) <= WARNING &&
           pFundMasterList &&
           pFundMasterList->isLSIFFund (fundCode) 
         )
      {
         DString lsifUnitsAvail;
         bool bNotEnoughUnits = false,
            bRaiseWarning = false;

         RedemptionValidation *pRedemptionValidation = NULL;

         if ( getRedemptionValidation (pRedemptionValidation, idDataGroup) <= WARNING &&
              pRedemptionValidation)
         {
            pRedemptionValidation->getField ( ifds::LSIFUnitsAvail, 
                                              lsifUnitsAvail, 
                                              idDataGroup, 
                                              false);
            double dec_lsifUnitsAvail = DSTCommonFunctions::convertToDouble (lsifUnitsAvail);
            if (dec_amount == 0)
            {
               bNotEnoughUnits = dec_lsifUnitsAvail == 0.0;
            }
            else
            {
               DString amtType;
         
               getField (ifds::AmtType, amtType, idDataGroup, false);
               if (amtType == I_("D")) //dollar amount
               {
   //get current from fund NAV, based on the trade date
                  double dec_fundNAV = getFundNAV ( accountNum, 
                                                    fundCode, 
                                                    classCode, 
                                                    idDataGroup);
                  bRaiseWarning = bNotEnoughUnits = dec_amount > dec_fundNAV * dec_lsifUnitsAvail;
               }
               else
               {
                  bNotEnoughUnits = dec_amount > dec_lsifUnitsAvail;
               }
            }
         }
         if (bNotEnoughUnits)
         {        
   //raise error         
            DString idiStr,
               tradeDate;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup, true);
            DSTCommonFunctions::DisplayFormat( lsifUnitsAvail, ifds::LSIFUnitsAvail );
            addIDITagValue (idiStr, I_("FUND"), fundCode);
            addIDITagValue (idiStr, I_("CLASS"), classCode);
            addIDITagValue (idiStr, I_("DATE"), tradeDate);
            addIDITagValue (idiStr, I_("AVAL"), lsifUnitsAvail);
            if (!bRaiseWarning)
            {
               ADDCONDITIONFROMFILEIDI (CND::ERR_LSIF_REDEMPTION_NOT_ENOUGH_UNITS_AVAILABLE, idiStr);
            }
            else 
            {
               ADDCONDITIONFROMFILEIDI (CND::WARN_LSIF_REDEMPTION_NOT_ENOUGH_UNITS_AVAILABLE, idiStr);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Redemption::validateFundBalance ( const DString &accountNum,
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


   if (!fundCode.empty() && 
       !classCode.empty()) 
   {

      MFAccount *pMFAccount = NULL;

      if ( getAccount ( pMFAccount, idDataGroup) <= WARNING  && 
           pMFAccount) 
      {
		  if (!pMFAccount->negativeBalanceAllowed (idDataGroup, fundCode, classCode))
		  //   if ( !accountHasCategory( I_( "07" ), idDataGroup) )
          {
            double dec_amount = DSTCommonFunctions::convertToDouble (amount);
            double dec_fundbalance = getFundBalance (accountNum, fundCode, classCode, idDataGroup);
            DString dstrAmtType;
            getField(ifds::AmtType,dstrAmtType,idDataGroup);

            // Amount convert to fund currency might be needed
            if (dstrAmtType == I_("S"))
            {
               DString dstrSettleCurrency, 
                  dstrFundCurrency;

               getField(ifds::SettleCurrency, dstrSettleCurrency, idDataGroup);
               getFundField (fundCode, classCode, ifds::Currency, dstrFundCurrency);
               //getField(ifds::FundCurrency, dstrFundCurrency, idDataGroup);

               //Different Currency, conversion is needed.
               if (dstrSettleCurrency != dstrFundCurrency)
               {
                  //Get the exchange rate field
                  double dec_exchRate = 0.0;
                  DString tradeDate,
                     exchRate;

                  getField (ifds::ExchRate, exchRate, idDataGroup, false);
                  getField (ifds::EffectiveDate, tradeDate, idDataGroup);
                  dec_exchRate = DSTCommonFunctions::convertToDouble (exchRate);
                  if (dec_exchRate == 0.0)
                  {
//retrieve the exchange rate if it's not manually altered...
                     Trade::getExchRate( dstrSettleCurrency, 
                                         dstrFundCurrency, 
                                         tradeDate,
                                         dec_exchRate, 
                                         idDataGroup,
                                         N); //get the most recent exchange rate
                  }
                  else
                  {
                     dec_exchRate = 1 / dec_exchRate;
                  }
                  dec_amount *= dec_exchRate;
               }
            }

            if (dec_amount > dec_fundbalance)
            {
               DString idiStr;

               addIDITagValue (idiStr, I_("FUNDNAME"), fundCode);
               addIDITagValue (idiStr, I_("CLASSNAME"), classCode);
               getErrMsg ( IFASTERR::REDEMPTION_AMOUNT_IS_GREATER_THAN_ACCOUNT_BALANCE, //400
                           CND::ERR_RED_AMT_MORE_THAN_HOLDING, 
                           CND::ERR_WARN_RED_AMT_MORE_THAN_HOLDING, 
                           idDataGroup,
                           idiStr ); 
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Redemption::validateOrderType ( const DString &orderType,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateOrderType"));

   DString redCode;

   getField (ifds::RedCode, redCode, idDataGroup);

// if wire order
   if ( orderType == Y && 
        DSTCommonFunctions::codeInList (redCode, BEARERREDCODELIST)) 
   {
      ADDCONDITIONFROMFILE (CND::ERR_ORDERTYPE_MUST_BE_DIRECT);
   }
   return GETCURRENTHIGHESTSEVERITY();
} 

//*******************************************************************************
SEVERITY Redemption::orderTypeRelatedChanges ( const BFDataGroupId &idDataGroup, 
                                               bool bValidateDate /* = true*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("orderTypeRelatedChanges"));
   if (Trade::orderTypeRelatedChanges (idDataGroup, bValidateDate) <= WARNING)
   {
      DString orderType,
         valueDateApplic;

   //read mgmt company option, is value date applicable
      getWorkSession ().getOption ( ifds::ValueDateApplic, 
                                    valueDateApplic, 
                                    BF::HOST, 
                                    false);         
      getField (ifds::OrderType, orderType, idDataGroup, false);
      if (valueDateApplic == Y) 
      {
          DString fundCode, 
             classCode;
      
         getFundField (ifds::FundCode, fundCode, idDataGroup);
         getFundField (ifds::ClassCode, classCode, idDataGroup);
         if ( !fundCode.empty () && 
              !classCode.empty ())
         {
            DString tradeDate;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
            if( !_bInitPending )
            {
                  validateDate ( DATE_VALIDATION::TRADE_DATE, 
                                 ifds::EffectiveDate, 
                                 tradeDate, 
                                 idDataGroup);
            }
         }
      }
      if (orderType == N )
      {
         // clear field value if wire-order type is direct and revalidate this filed, to clear remain condition
         setFieldNoValidate (ifds::WireOrdNum, NULL_STRING, idDataGroup, false, false, true);
      }
      else if (orderType == Y) //wire order
      {
         setFieldValid (ifds::SettleSource, idDataGroup, false); //invalidate settle source
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY Redemption::validateValueDate ( const DString &valueDate, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateValueDate"));

   DString valueDateApplic;

//read mgmt company option, is value date applicable
   getWorkSession ().getOption ( ifds::ValueDateApplic, 
                                 valueDateApplic, 
                                 BF::HOST, 
                                 false);         
   if (valueDateApplic == Y)
   {
      DString nextNightRun;

      if (getFundField (ifds::NextNightRun, nextNightRun, idDataGroup) <= WARNING)
      {
         if ( !nextNightRun.empty() && 
              DSTCommonFunctions::
                  CompareDates (valueDate, nextNightRun) == DSTCommonFunctions::FIRST_EARLIER)
         {
            ADDCONDITIONFROMFILE (CND::ERR_VALUE_DATE_EARLIER_THAN_CYCLE);
         }
      }
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         //have to (re)set the default value for ValueDate
         validateDate ( DATE_VALIDATION::VALUE_DATE, 
                        ifds::ValueDate, 
                        valueDate, 
                        idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY Redemption::validateSettleSource ( const DString &settleSource,
                                            const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSettleSource"));

   Trade::commonValidateSettleSource( settleSource, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline bool Redemption::isACHApplicable (const BFDataGroupId &idDataGroup)
{
   DString achRedemption;

   getWorkSession().getOption ( ifds::ACHRedemption, 
                                achRedemption, 
                                BF::HOST, 
                                false);
   return achRedemption == Y;
}

//******************************************************************************
SEVERITY Redemption::validatePayType ( const DString &payType,
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validatePayType"));

   if (Trade::validatePayType (payType, idDataGroup))
   {
      if (payType == PAYTYPE::DIRECT)
      {
         MFAccount *pMFAccount = NULL;
         DString accountNum;

         getField( ifds::AccountNum, accountNum, idDataGroup );
         if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
              pMFAccount)
         {
            DString accountBalance;

            pMFAccount->getField (ifds::AccountBalance, accountBalance, idDataGroup, false);
            accountBalance.stripLeading ('0').strip ();
            if (accountBalance.empty())
            {
               ADDCONDITIONFROMFILE (CND::ERR_ACCT_BALANCE_ZERO);
            }
            else
            {
               PendingTradeList *pPendingTradeList = NULL;

               if (pMFAccount->getPendingTradesList (pPendingTradeList, idDataGroup) <= WARNING)
               {
                  bool bNoPendingTrades = !pPendingTradeList;

                  if (!bNoPendingTrades)
                  {
                     BFObjIter iter (*pPendingTradeList, idDataGroup);

                     bNoPendingTrades = iter.getNumberOfItemsInList () < 1;

                  }
                  if (bNoPendingTrades)
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_FIRST_DTA_TRADE_MUST_BE_PURCHASE);
                  }
               }
            }
         }
      }

	  // P0186486_FN15_The Source of Funds
	  {
		  DString srcOfFund;
		  getField(ifds::SrcOfFund, srcOfFund, idDataGroup, false); 
		  srcOfFund.stripAll().upperCase();

		  if(!srcOfFund.empty())
		  {
			  if(getWorkSession ().isSrcOfFundRequired(srcOfFund, idDataGroup))
			  {
				  if(payType != PAYTYPE::SUPPRESS)
				  {
					  getErrMsg (IFASTERR::SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE, 
						  CND::ERR_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE, 
						  CND::WARN_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE, 
						  idDataGroup);
				  }
			  }
		  }
	  }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::payTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("payTypeRelatedChanges"));

   if (Trade::payTypeRelatedChanges (idDataGroup) <= WARNING)
   {
      DString payType;

      getField (ifds::TradesPayType, payType, idDataGroup, false);
      if (payType == PAYTYPE::CLEARING)
      {
         if (!_bInitPending)
         {
            setFieldNoValidate ( ifds::SuppressCode, I_("16"), idDataGroup, false, 
                                 false, //invalid
                                 true);   //notify
         }
         setFieldReadOnly (ifds::SuppressCode, idDataGroup, true);
      }
//Incident #323484 - added delivery method on the attribute box
      DString cheqDeliveryDefault,
         deliveryMethod;

      getField (ifds::TradesPayType, payType, idDataGroup, false); 
      getWorkSession().getOption ( ifds::CheqDeliveryDefault, 
                                   cheqDeliveryDefault, 
                                   BF::HOST,
                                   false);
      bool bSetDefault = !cheqDeliveryDefault.empty() && payType == PAYTYPE::SYSTEM_CHEQUE;
      if (bSetDefault)
      {
         deliveryMethod = cheqDeliveryDefault;
      }
      if (!_bInitPending)
      {
         setFieldNoValidate ( ifds::DeliveryMethod, deliveryMethod, idDataGroup, false,
                              true,
                              true);
      }
      setFieldReadOnly (ifds::DeliveryMethod, idDataGroup, !bSetDefault);

      DString redCode;
      getField(ifds::RedCode, redCode, idDataGroup, false);
      redCode.strip();
      if(isRESPTradeAccount(idDataGroup) && DSTCommonFunctions::codeInList (redCode, I_("75,76,78,83,Q1,Q2,Q3,AG,AR,GR,IR")))
      {
         // actually, if redcode is 75,76,78,83 for RESP Trading, paytype is suppress but just ensure it is suppress...
         if (payType == PAYTYPE::SUPPRESS)
         {
            setFieldNoValidate (ifds::SuppressCode, I_("01"), idDataGroup, false);
            setFieldReadOnly (ifds::SuppressCode, idDataGroup, true); 
         }
      }

	  if (isRESPTradeAccount(idDataGroup) && DSTCommonFunctions::codeInList (redCode, I_("SC,SR,BC,BR"))) // SC-SAGES Correction, SR-SAGES Grant Return, BC-BCTESG Correction, BR-BCTESG Grant Return
		  setFieldReadOnly (ifds::SuppressCode, idDataGroup, true); 
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::getDefaultBankInstructions ( BankInstructions *&pBankInstructions, 
                                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDefaultBankInstructions"));

   if ((!arePayInstructAllowed (idDataGroup)) && (!bIsRegAgentPayInstOption(idDataGroup))) //look for shareholder banking
   {
      DString payType;

      getField (ifds::TradesPayType, payType, idDataGroup, false);

	  if(PAYTYPE::EFT == payType)
      {
         if ( getShareholderBankInstructions ( pBankInstructions, 
                                             AcctUseCode::EFT_REDEMPTION, 
                                             idDataGroup) <= WARNING)
         {
            DString dstrAcctUse;

            if (pBankInstructions)
            {
               pBankInstructions->getField (ifds::AcctUseCode, dstrAcctUse, idDataGroup);

               if (dstrAcctUse == AcctUseCode::EFT_REDEMPTION)
                  return GETCURRENTHIGHESTSEVERITY ();

               if (dstrAcctUse != AcctUseCode::EFT_REDEMPTION)
               {
                  BankInstructions *pAltBankInstructions = NULL;
                  //if not found look for the last eft bank used
                  if ( getShareholderBankInstructions (pAltBankInstructions, 
                                                      AcctUseCode::ALT_EFT_REDEMPTION,
                     idDataGroup) <= WARNING)
                  {
                     if (pAltBankInstructions != NULL)
                     {
                        pBankInstructions = pAltBankInstructions;
                     }
                  }
               }
            }
            else 
            {
               // did not find EFT_REDEMPTION or Default look for ALT_EFT_REDEMPTION if applicable
               //if not found look for the last eft bank used
               if ( getShareholderBankInstructions ( pBankInstructions, 
                                                   AcctUseCode::ALT_EFT_REDEMPTION,
                                                   idDataGroup) <= WARNING && 
                                                   !pBankInstructions )
               {
                  getLastEFTBankInstructions (pBankInstructions, idDataGroup);
               }
            }
         }
      }
      else if (payType == PAYTYPE::DIRECT_DEPOSIT)
      {
         getShareholderBankInstructions ( pBankInstructions, 
                                          AcctUseCode::DIRECT_DEPOSIT, 
                                          idDataGroup);
      }
   }
   else if (bIsRegAgentPayInstOption (idDataGroup))
   {
	   DString dstrPayType,dstrPayMeathod;
	   getField (ifds::TradesPayType, dstrPayType, idDataGroup, false);
	   getField (ifds::PayMethod, dstrPayMeathod, idDataGroup, false);
	   if (dstrPayType == PAYTYPE::EFT && dstrPayMeathod == I_("WIRE"))
	   {
		   if(getRegAgentBankInstructions(pBankInstructions, AcctUseCode::EFT_REDEMPTION,
			   idDataGroup)<= WARNING )//EFT redemption is default usage code for Reg Agent
		   {
			   if(!pBankInstructions)
				   ADDCONDITIONFROMFILE (CND::ERR_REGAGENT_BANKING_UNAVILABLE);
		   }
	   }
	   else
      {
		   ADDCONDITIONFROMFILE (CND::ERR_REDIRECT_TO_REG_AGENT_NOT_ALLOWED);
      }
   }
   else //look for the pay entity banking
   {
      getPayEntityBankInstructions (pBankInstructions, AcctUseCode::EFT_REDEMPTION, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::canAccountTrade ( MFAccount *pMFAccount, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canTradeAccount"));
//calls base class   
   if (Trade::canAccountTrade (pMFAccount, idDataGroup) <= WARNING)
   {
      DString tradeDate;

      getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
      if (pMFAccount->canRedeem (tradeDate, idDataGroup) <= WARNING)
      {
         pMFAccount->escrowRedeem (tradeDate, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateAccount ( MFAccount *pMFAccount, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAccount"));
   if (Trade::validateAccount (pMFAccount, idDataGroup) <= WARNING)
   {
      DString taxType;

      pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
      if (taxType == I_("P"))
      {
         getErrMsg ( IFASTERR::AN_AS_PENSION_PLAN_ACCOUNT, 
                     CND::ERR_AS_PENSION_ACCT, 
                     CND::ERR_WARN_AS_PENSION_ACCT, 
                     idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateFundCode ( const DString &fundCode, 
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundCode"));
   if (!fundCode.empty())
   {
      DString accountNum;

      getAccountField (ifds::AccountNum, accountNum, idDataGroup);
      validatePUEVCapableFund (fundCode, accountNum, idDataGroup);
      validateInvestroCapableFund (fundCode, accountNum, idDataGroup);
      validateFundSponsorFeeModelCode (fundCode, accountNum, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Redemption::validateMasterActAMS(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMasterActAMS"));

   DString dstrFundCode, dstrClassCode, dstrAcctNum;
   MFAccount *pMFAccount = NULL;

   getField(ifds::AccountNum, dstrAcctNum, idDataGroup, false);
   getField(ifds::FromFund, dstrFundCode, idDataGroup);
   getField(ifds::FromClass, dstrClassCode, idDataGroup);

   if (getWorkSession().getMFAccount(idDataGroup, dstrAcctNum, pMFAccount) <= WARNING && pMFAccount &&
       pMFAccount->isAMSAccount(idDataGroup))
   {
        DString dstrAcctAMSCode, dstrTradeDate, dstrAMSFund, dstrAMSClass;
        FundDetail *pFundDetail = NULL;
        AmsMstrInfo *pAMSMstrInfo = NULL;
		AMSMstrList *pAMSMstrList = NULL;

        pMFAccount->getField(ifds::AMSCode, dstrAcctAMSCode, idDataGroup);
        getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup, false);

        if (getWorkSession().getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail &&
            pMFAccount->getAMSMstrList(pAMSMstrList, idDataGroup,  dstrTradeDate) <= WARNING && pAMSMstrList)
        {
            pAMSMstrList->getAMSMstrInfo(I_("RB"), dstrAcctAMSCode, dstrTradeDate, pAMSMstrInfo, idDataGroup);

            if (pAMSMstrInfo)
            {
                pAMSMstrInfo->getField(ifds::AssocFund, dstrAMSFund, idDataGroup);
                pAMSMstrInfo->getField(ifds::AssocClass, dstrAMSClass, idDataGroup);
            }

            if (pFundDetail->isAMSParentFund(idDataGroup) &&
                ((dstrFundCode != dstrAMSFund) || (dstrClassCode != dstrAMSClass)))
            {
                getErrMsg(IFASTERR::PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL,
                          CND::ERR_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL,
                          CND::WARN_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL,
                          idDataGroup);
            }
            else if (pFundDetail->isAMSChildFund(idDataGroup) && 
                     pAMSMstrInfo && !pAMSMstrInfo->isFundInAMS(dstrFundCode, dstrClassCode, idDataGroup))
            {
                getErrMsg(IFASTERR::CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS,
                          CND::ERR_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS,
                          CND::WARN_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS,
                          idDataGroup);
            }
        }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY Redemption::validateFundClass ( const DString &fundCode, 
                                         const DString &classCode, 
                                         const DString &accountNum, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));

//calls base
   if (Trade::validateFundClass ( fundCode, 
                                  classCode, 
                                  accountNum, 
                                  idDataGroup) <= WARNING)
   {
//get the values of broker/branch/sales rep from trade      
      DString broker,
              branch,
              agent;

      getField (ifds::Broker, broker, idDataGroup);
      getField (ifds::Branch, branch, idDataGroup);
      getField (ifds::SlsrepCode, agent, idDataGroup);
      if (canFundTrade ( broker,
                         branch,
                         agent,
                         TRADETYPE::REDEMPTION,
                         accountNum,
                         fundCode,
                         classCode,
                         CND::ERR_FUND_CLASS_REDEMPTION_STOP_FLAG_ON,
                         CND::ERR_WARN_FUND_CLASS_REDEMPTION_STOP_FLAG_ON,
                         idDataGroup) <= WARNING
         )
      {
         MFAccount *pMFAccount = NULL;

         if ( getAccount (pMFAccount, idDataGroup) <= WARNING &&
              pMFAccount)
         {
// check certificate
            CertificateList *pCertificateList = NULL;
            double dIssueUnits = 0;
            DString dstrCertExists (N);

            pMFAccount->getField (ifds::Certificates, dstrCertExists, idDataGroup, false);
            if (dstrCertExists.strip().upperCase() == Y)
            {
               if ( pMFAccount->getCertificateList ( pCertificateList, 
                                                     idDataGroup) < WARNING && 
                    pCertificateList)
               {
                  if ( pCertificateList->certIssueUnitsExist ( fundCode, 
                                                               classCode, 
                                                               dIssueUnits, 
                                                               idDataGroup))
                  {
                     DString idiStr;
                     DString dstrIssueUnits = DSTCommonFunctions::doubleToDString (ifds::SettledUnits, dIssueUnits);
                     DSTCommonFunctions::DisplayFormat( dstrIssueUnits, ifds::SettledUnits );
                     addIDITagValue(idiStr, I_("ISSUEUNITS"), dstrIssueUnits);
                     ADDCONDITIONFROMFILEIDI(CND::ERR_WARN_CERT_UNITS_EXISTS, idiStr);
                  }
               }
            }
         }
         //validateFundSubCatIAFundIndicator(fundCode,classCode,idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::fromFundClassRelatedChanges ( const DString &fundCode, 
                                                   const DString &classCode, 
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromFundClassRelatedChanges"));
   Trade::fromFundClassRelatedChanges (fundCode, classCode, idDataGroup);
   {
      refreshAllocations (idDataGroup);
      setSettleCurrencyFromFund (fundCode, classCode, idDataGroup);

      DString dstrEffectiveDate;
      getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
      validateDate (DATE_VALIDATION::DEFAULT_TRADE_DATE, ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
 
      setFieldValid (ifds::RedCode, idDataGroup, false);
      setFieldValid (ifds::FundCodeRedCodeAmount, idDataGroup, false);
//invalidate the wireordfndclass
      setFieldValid (ifds::WireOrdFndCls, idDataGroup, false); //wireorder should be checked against fund
      setFieldValid (ifds::AmountAmtType, idDataGroup, false); //depends on redemption validations
      setFieldValid (ifds::AmtType, idDataGroup, false);

//lsif code initialization  :  incident#243397 moved to Trade.cpp to also initialize transfer-out on LSIF funds, Feb 15, 2005
      thirdPartyFundRelatedChanges (idDataGroup);
//API needs this field to be invalid
      setFieldValid (ifds::FundCurrency, idDataGroup, false);
      setFieldValid (ifds::SettleSource, idDataGroup, false); //invalidate settle source
//Incident# 273841 - set the other confirm type to 1 if account/fund are PUEV capable
      setOtherConfirmTypeDefaultValues (idDataGroup);
//give the green light for refreshing splits...
      _bShouldRefreshSplitCommissions = true;
      refreshSplitCommissions (idDataGroup);
      if(isGIInvestmentListApplicable(idDataGroup))
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
         setFieldSubstituteValues ( ifds::AmtType, idDataGroup, _multiCurrency == Y ? ifds::AmtTypeMultiCurrency : ifds::AmtTypeRedemption);

      };

	  if ( !fundCode.empty() && !classCode.empty() )
	  {
		  withholdingTaxRelatedChanges (idDataGroup);
        FundDetail *pFundDetail = NULL;
        DString dstrGrossNetDefault , dstrFormattedValue;
        if( getWorkSession().getFundDetail(fundCode, classCode, idDataGroup, pFundDetail)  && pFundDetail ) 	
        {
            pFundDetail->getGrossNetDefault(idDataGroup, dstrGrossNetDefault, dstrFormattedValue);
            if(!dstrGrossNetDefault.empty())
               setFieldNoValidate(ifds::GrossOrNet, dstrGrossNetDefault, idDataGroup, false, false, true);
        }
	  }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY Redemption::validateAmtType ( const DString &amtType, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtType"));
   if (Trade::validateAmtType (amtType, idDataGroup) <= WARNING)
   {
      DString fundCode, classCode;
      FundDetail *pFndDetl = NULL;

      if ( getFundField (ifds::FundCode, fundCode, idDataGroup) <= WARNING &&
           getFundField (ifds::ClassCode, classCode, idDataGroup) <= WARNING)
      {
         if (!fundCode.empty() && !classCode.empty() &&
            getWorkSession().getFundDetail(fundCode, classCode, idDataGroup, pFndDetl) && pFndDetl &&
            !pFndDetl->isAmtTypeValidForLoadType(getWorkSession(), amtType, idDataGroup))
         {
             DString loadType, amtTypeDesc, idiDesc, amtTypeSubList;
             BFProperties *pBFProperties = getFieldProperties(ifds::AmtType, idDataGroup);

             if (pBFProperties)
                pBFProperties->getSubstituteValues(amtTypeSubList);

             amtTypeDesc = DSTCommonFunctions::getDescription(amtType, amtTypeSubList);
             getFundField(ifds::LoadType, loadType, idDataGroup);
             loadType.stripAll().upperCase();

             if (loadType == FUND_LOAD_TYPE::BACKEND_LOAD)
             {
                 addIDITagValue(idiDesc, I_("AMT_TYPE"), amtTypeDesc);
                 getErrMsg(IFASTERR::AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP,
                           CND::ERR_AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP,
                           CND::WARN_AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP, 
				           idDataGroup,
                           idiDesc);
             }
             else if (loadType == FUND_LOAD_TYPE::CHARGEBACK)
             {
                 addIDITagValue(idiDesc, I_("AMT_TYPE"), amtTypeDesc);
                 getErrMsg(IFASTERR::AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP,
                           CND::ERR_AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP,
                           CND::WARN_AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP, 
				           idDataGroup,
                           idiDesc);
             }
             else
             {
                 addIDITagValue(idiDesc, I_("AMT_TYPE"), amtTypeDesc);
                 getErrMsg(IFASTERR::AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE,
                           CND::ERR_AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE,
                           CND::WARN_AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE, 
				           idDataGroup,
                           idiDesc);
             }
         }
         else if ( fundCode.empty() &&
                   classCode.empty() &&
                   hasAllocations (idDataGroup) || 
                   hasFromAllocations (idDataGroup))
         {
//if fundCode is blank and allocationAllowed is yes, amount type only allow
//if one of the following is true:
//1. chkRounding is yes and amtType is Settlecurrency
//2. multiCurrency is yes and amtType is Amount or amtType is Settlecurrency
//3. multiCurrency is no and amtType is amount
            DString chkRounding;
         
            getWorkSession ().getOption ( ifds::BusRounding, 
                                          chkRounding, 
                                          BF::HOST,
                                          false);

            if (!((chkRounding == Y && amtType == I_("S")) || //case 1
                  (_multiCurrency == Y && (amtType == I_("D") || amtType == I_("S"))) || //case 2
                  (_multiCurrency == N && amtType == I_("D")))) //case 3
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMTCODE_FOR_INVESTMENT_ALLOCATION);
            }
         }
      }

      DString redCode;

      getField (ifds::RedCode, redCode, idDataGroup);

      if ( DSTCommonFunctions::codeInList (redCode, BEARERREDCODELIST) && 
           amtType != I_("U"))
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMTTYPE_FOR_REDEMPTION);
      }

      if ( amtType == I_("D") && 
           _multiCurrency == Y)
      {
         if (hasAllocations (idDataGroup))
         {
            TradeFundAllocList *pFundAllocationList = NULL;

            if ( getFundAllocationList (pFundAllocationList, idDataGroup, false) <= WARNING &&
                 pFundAllocationList)
            {
               DString settleCurrency;

               pFundAllocationList->getAllocCurrency (settleCurrency, idDataGroup);
               if (settleCurrency.empty())
               {
                  ADDCONDITIONFROMFILE (CND::ERR_AMOUNT_NOT_ALLOWED);
               }
            }
         }
      }
//add validation for LSIF funds, amount type should only be units or amount (U,D)
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         FundMasterList *pFundMasterList = NULL; 

         if ( getMgmtCo().getFundMasterList (pFundMasterList) &&
              pFundMasterList)
         {      
            if ( amtType != I_("D") && 
                 amtType != I_("U"))
            {
               //allocations will always exist
               TradeFundAllocList *pFundAllocationList = NULL;

               if ( getFundAllocationList ( pFundAllocationList, 
                                           idDataGroup) <= WARNING &&
                                           pFundAllocationList)
               {
                  BFObjIter iter ( *pFundAllocationList, 
                                   idDataGroup, 
                                   false, 
                                   BFObjIter::ITERTYPE::NON_DELETED);
                  DString _fundCode;

                  while (!iter.end())
                  {
                     iter.getObject()->getField ( ifds::FundCode, 
                                                  _fundCode, 
                                                 idDataGroup, 
                                                 false);
                     if (pFundMasterList->isLSIFFund (_fundCode))
                     {
                        ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMTTYPE_FOR_LSIF_REDEMPTION);
                        break;
                     }
                     ++iter;
                  }
               }
            }

            DString networkID;

            getField (ifds::NetworkID, networkID, idDataGroup);
            networkID.strip();

			DString networkIDForAmountTrade;
			getWorkSession().getOption ( ifds::NetworkIDForAmountTrade, 
										 networkIDForAmountTrade, 
										 idDataGroup, 
										 false);
			networkIDForAmountTrade.strip();
			bool bIsSwift = !networkID.empty() && DSTCommonFunctions::codeInList (networkID, networkIDForAmountTrade);
            //bool bIsSwift = !networkID.empty() && networkID == I_("SWFT");

//PET 1117/66,67,68 SWIFT/Investro/PWLD
            if ( (amtType == I_("D") ||
                  amtType == I_("S")) &&
                  !bIsSwift) //Incident# 554580 - remove current validation for SWIFT monetary amount trades
            {
               DString accountNum;

               getField( ifds::AccountNum, accountNum, idDataGroup );
               validateAmtTypeForNetworkIDAndFundBroker (accountNum, fundCode, idDataGroup);
            }

            if (amtType == I_("U"))
            {
               bool bIsMasterActWithOneChild = getWorkSession().isMasterActWithOneChild(idDataGroup);
               if (bIsMasterActWithOneChild)
               {
                  validateParentFundAgainstAmtType(idDataGroup);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeGrossNet ") );

   DString grossOrNet;

   getField (ifds::GrossOrNet, grossOrNet, idDataGroup, false);
   if (grossOrNet == N) //net
   {
      DString amtType;

      getField (ifds::AmtType, amtType, idDataGroup);
      if (amtType.upperCase() == I_("U")) //units
      {
         ADDCONDITIONFROMFILE (CND::ERR_NET_UNIT_REDEEM_NOT_ALLOWED);
      }
      else if (amtType.upperCase() == I_("P")) //percent
      {
         ADDCONDITIONFROMFILE (CND::ERR_NET_UNIT_PERCENT_NOT_ALLOW);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::validateAmountGrossNet (const BFDataGroupId &idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_( "validateAmountGrossNet" ));

   DString amount, 
   grossOrNet;

   getField (ifds::GrossOrNet, grossOrNet, idDataGroup);
   getField (ifds::Amount, amount, idDataGroup);

   double dec_amount = DSTCommonFunctions::convertToDouble (amount);

   if (grossOrNet == N && dec_amount == 0)
   {
      ADDCONDITIONFROMFILE (CND::ERR_NET_AMOUNT_WITH_ZERO);
   }
   DString dstrFundCode, dstrClassCode;
   getField (ifds::FromFund, dstrFundCode, idDataGroup, false);
   getField (ifds::FromClass, dstrClassCode, idDataGroup, false);
   if(!dstrFundCode.empty() &&  !dstrClassCode.empty() && dec_amount != 0 )
   {
      FundDetail *pFundDetail = NULL;
      DString dstrGrossNetDefault, dstrFormattedValue ;
      if( getWorkSession().getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail ) 	
      {
         pFundDetail->getGrossNetDefault(idDataGroup, dstrGrossNetDefault, dstrFormattedValue);
         DString dstrGrossOrNet;
         getField(ifds::GrossOrNet, dstrGrossOrNet, idDataGroup, false);
         if(!dstrGrossNetDefault.empty() && dstrGrossOrNet != dstrGrossNetDefault )
         {
            CND::CIFast_IFast_ifastcbo_warn_Red_Fund_class_grossnetdefault_value_overidden WARN_FUND_CLASS_GROSS_NET_FOR_REDEMPTION_OVERIDDEN;
            CND::CIFast_IFast_ifastcbo_err_Red_Fund_class_grossnetdefault_value_overidden  ERR_FUND_CLASS_GROSS_NET_FOR_REDEMPTION_OVERIDDEN;
            DString dstrTemp ;
            addIDITagValue( dstrTemp, I_("FUND_CLASS_DEFAULT"), dstrFormattedValue);
            getErrMsg (IFASTERR::FUND_CLASS_GROSS_NET_FOR_REDEMPTION_OVERIDDEN, 
								         ERR_FUND_CLASS_GROSS_NET_FOR_REDEMPTION_OVERIDDEN, 
								         WARN_FUND_CLASS_GROSS_NET_FOR_REDEMPTION_OVERIDDEN, 
								         idDataGroup,dstrTemp);
        }
      }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::validateAmountAmtType (const BFDataGroupId& idDataGroup)
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
      
      if (dec_amount == 0 && !DSTCommonFunctions::codeInList (amtType, I_("T,F,M")))
      {
         //ADDCONDITIONFROMFILE (CND::ERR_FULL_REDEMPTION_INDICATED); //give a warning sign!
         raiseFullRedemptionMessage(idDataGroup);
      }
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         RedemptionValidation *pRedemptionValidation = NULL;
         MFAccount *pMFAccount = NULL;

         if ( getRedemptionValidation (pRedemptionValidation, idDataGroup) <= WARNING &&
              getAccount (pMFAccount, idDataGroup) <= WARNING &&
              pMFAccount)
         {
            DString taxType;

            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
            if (dec_amount == 0 && !DSTCommonFunctions::codeInList (amtType, I_("M,F,T")))
            {
               DString dstrPensionJuris,
                  dstrCurrLIPSetup, 
                  damountOver,
                  dstrPQLIFLIRATaxType, 
                  dstrPQLIFLIRAJuris;

               pMFAccount->getField (ifds::PensionJuris, dstrPensionJuris, idDataGroup);
               dstrPensionJuris.strip();
               getWorkSession().getOption ( ifds::PQLIFLIRAJuris, 
                                            dstrPQLIFLIRAJuris, 
                                            BF::HOST, 
                                            false);
               dstrPQLIFLIRAJuris.strip();
               getWorkSession().getOption ( ifds::PQLIFLIRATaxType, 
                                            dstrPQLIFLIRATaxType, 
                                            BF::HOST, 
                                            false);
               dstrPQLIFLIRATaxType.strip().upperCase();
               pRedemptionValidation->getField( ifds::CurrLIPSetup, dstrCurrLIPSetup, idDataGroup );
               dstrCurrLIPSetup.strip().upperCase();
               pRedemptionValidation->getField( ifds::AmountOver, damountOver, idDataGroup );
               damountOver.strip().upperCase();
               if ( DSTCommonFunctions::codeInList( dstrPensionJuris, dstrPQLIFLIRAJuris ) &&
                    DSTCommonFunctions::codeInList( taxType, dstrPQLIFLIRATaxType ))
               {
                  if (dstrCurrLIPSetup == N)
                  {
                     ADDCONDITIONFROMFILE( CND::ERR_FULL_REDEMPTION_NOT_ALLOW );
                  }
                  else
                  {
                     ADDCONDITIONFROMFILE( CND::WARN_FULL_REDEMPTION_NOT_ALLOW );
                  }
               }
               if ( (getWorkSession ().isLIFLike (taxType) || getWorkSession ().isLIRALike (taxType)) && damountOver == Y )
               {
                  getErrMsg ( IFASTERR::TOTAL_REDEMPTION_EXCEEDS_MAXIMUM, 
                              CND::ERR_TOTAL_REDEMPTION_EXCEEDS_MAXIMUM, 
                              CND::ERR_WARN_TOTAL_REDEMPTION_EXCEEDS_MAXIMUM, 
                              idDataGroup);
               }

               DString dstrUnitHeld;

               pRedemptionValidation->getField (ifds::UnitHeld, dstrUnitHeld, idDataGroup);
               dstrUnitHeld.strip().upperCase();
               if (dstrUnitHeld == Y)
               {
                  ADDCONDITIONFROMFILE (CND::WARN_UNITS_CANNOT_BE_REDEEMED);	
               }
            }
            else
            {
               DString amntOverMax,
                  maxApplies;

               pRedemptionValidation->getField (ifds::AmntOverMax, amntOverMax, idDataGroup);
               pMFAccount->getField (ifds::MaxApplies, maxApplies, idDataGroup);

               TaxTypeRule *pTaxTypeRule = NULL;
               if ( pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
               {
                  DString planType, 
                     maximumApplies;

                  if (pTaxTypeRule)
                  {
                     pTaxTypeRule->getField (ifds::PlanType, planType, idDataGroup);
                     pTaxTypeRule->getField (ifds::MaximumApplies, maximumApplies, idDataGroup);
                     planType.strip ().upperCase ();
                     maximumApplies.strip ().upperCase ();
                     if ( amntOverMax == Y && 
                          maxApplies == Y && 
                          planType == I_ ("RIF") && 
                          maximumApplies == Y)
                     {
                         getErrMsg ( IFASTERR::MAXIMUM_PAYOUT_AMOUNT_IS_EXCEEDED, 
                                     CND::ERR_MAX_PAYMENT_EXCEED, 
                                     CND::WARN_MAX_PAYMENT_EXCEED, 
                                     idDataGroup);
                     }
                  }

                  if (getWorkSession ().isIntRIFPlan (taxType))
                  {
                     DString strAmtSysCalc;
                     //If it is a RIF account, display system calculated redemption amount AmtSysCalc_143
                     pRedemptionValidation->getField (ifds::AmtSysCalc, strAmtSysCalc, idDataGroup);

                     DString idiStr;
                     DSTCommonFunctions::DisplayFormat( strAmtSysCalc,ifds::AmtSysCalc );
                     addIDITagValue (idiStr, I_("AMOUNT"), strAmtSysCalc);
                     ADDCONDITIONFROMFILEIDI (CND::WARN_PAYOUT_AMOUNT_MAYBE_CHANGED, idiStr);
                  }
               }
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::validateAmount ( const DString &amount,  
                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmount"));

   double dec_amount = DSTCommonFunctions::convertToDouble (amount);

   if (Trade::validateAmount (amount, idDataGroup) <= WARNING)
   {
      if (dec_amount != 0)
      {
         DString amtType;

         getField (ifds::AmtType, amtType, idDataGroup);
         if ( amtType == I_("D") || //amount
              amtType == I_("S"))   //settle currency
         {
            Trade::validateAmountPrecision (idDataGroup);
         }
      }
	  else
	  {
		  DString redCode;
		  getField (ifds::RedCode, redCode, idDataGroup, false);
		  if (redCode == I_("EP") && (dec_amount == 0))
		  {
			  ADDCONDITIONFROMFILE (CND::ERR_VALUE_CANNOT_BE_ZERO);
		  }
	  }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY Redemption::validateMinFromFundAmount ( const DString &accountNum,
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
   DString currency,
      initPurch,tradeDate;

   getField (ifds::SettleCurrency, currency, idDataGroup);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);

   bool bOverrideFundLevelCheck = false;
//first check ams
   amsMinAmtCheck ( TRADETYPE::REDEMPTION,
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
      fundClassTradeMinimumAmtCheck ( TRADETYPE::REDEMPTION,
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
                                      idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************        
SEVERITY Redemption::amsFundClassTradeMinAmtCheck ( const DString &transType,
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

   MFAccount *pMFAccount = NULL;
   
   if ( getAccount (pMFAccount, idDataGroup) <= WARNING &&
        pMFAccount)
   {
      bool bRecordFound = false;
      double dPercent = 0.0;
      double dFundClassBalance;

      double dCurrentAmount =  DSTCommonFunctions::convertToDouble (amount);

      dFundClassBalance = 
         pMFAccount->fundClassBalance ( fundCode, 
                                        classCode, 
                                        bRecordFound, 
                                        ifds::SettledValue, 
                                        idDataGroup,
                                        effectiveDate);
   //check if the record is found.
      if (bRecordFound) 
      {
         if (dFundClassBalance > 0)
         {
            dPercent = dCurrentAmount / dFundClassBalance * 100;
         }
         else
         {
            dPercent = 0;
         }
         pAMSMstrInfo->maxRedeem ( taxJuris, 
                                   provResid, 
                                   accountType, 
                                   taxType, 
                                   acctDesign, 
                                   dPercent, 
                                   bOverrideFundLevelCheck, 
                                   idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Redemption::isBrokerAllowed ( const DString &transType,
                                   const DString &accountNum,
                                   const DString &fundCode, 
                                   const DString &classCode,
                                   const BFDataGroupId &idDataGroup)
{
//allows for special processing at class level
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isBrokerAllowed"));
   bool bOverride (false);
   bool bErrorSeverity (true);

   checkEntityOverride ( transType,
                         fundCode, 
                         classCode, 
                         accountNum, 
                         bOverride, 
                         bErrorSeverity, 
                         idDataGroup);
   return bOverride;
}

//******************************************************************************
SEVERITY Redemption::recalculateEstateAllocation(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("recalculateEstateAllocation"));
   if(isEstateAllocationListApplicable(idDataGroup))
   {
      EstateAllocationList* pEstateAllocationList = NULL;
      if(getEstateAllocationList (pEstateAllocationList, idDataGroup, true) <= WARNING && pEstateAllocationList)
      {
         DString dstrAmount;
         DString dstrAmountType;
         getField( ifds::Amount, dstrAmount, idDataGroup );
         getField( ifds::AmtType, dstrAmountType, idDataGroup );
         pEstateAllocationList->recalculateAmounts(dstrAmount, dstrAmountType, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::validateEstateAllocationPresent(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEstateAllocationPresent"));
       
   DString dstrRedCode;
   getField (ifds::RedCode,      dstrRedCode,    idDataGroup, false);

   DString dstrDeathRedCode;
   getWorkSession().getOption (ifds::DeathRedCode, dstrDeathRedCode, BF::HOST, false);
   
   if(DSTCommonFunctions::codeInList(dstrRedCode, dstrDeathRedCode) && 
      !isEstateAllocationListApplicable(idDataGroup))
   {
      ADDCONDITIONFROMFILE(CND::ERR_ESTATE_ALLOCATION_REQUIRED_FOR_DEATH_REDEMPTIONS);      
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::withholdingTaxRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("withholdingTaxRelatedChanges"));
   _blTaxable = false;

   MFAccount* pMFAccount = NULL;
   if ( getAccount (pMFAccount, idDataGroup) <= WARNING &&
      pMFAccount)
   {
      // Registered status
      DString dstrTaxType, 
         dstrPlanType;

      pMFAccount->getField (ifds::TaxType, dstrTaxType, idDataGroup );
      TaxTypeRule *pTaxTypeRule = NULL;
      if ( pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
      {
         pTaxTypeRule->getField( ifds::PlanType, dstrPlanType, idDataGroup );
         dstrPlanType.strip().upperCase();
      }

      DString dstrAutomaticAll;
      getWorkSession().getOption( ifds::AutomaticAll, dstrAutomaticAll, BF::HOST, false );	

      // Registered Account Type for cases 1 and 3
      if( I_( "UNREG" ) != dstrPlanType )
      {
         DString dstrRRIFProduct = I_("2,P,B,BR,L"); //rif product

         // get Redemption Code to check if it's in the allowable list
         DString dstrRedCode;
         getField( ifds::RedCode, dstrRedCode, idDataGroup );

         //get system features
         DString dstrNoWithTax, dstrTaxOnRRIFRed;
         getWorkSession().getOption( ifds::NoWithTax,    dstrNoWithTax,    BF::HOST, false );   
         getWorkSession().getOption( ifds::TaxOnRRIFRed, dstrTaxOnRRIFRed, BF::HOST, false );
         // retrieve char2 for generic control "TaxWithHeldPW" that has listed 
         // allowable Red Codes for Withholding Taxes
         DString dstrRIFTTaxableRedCodes;
         getWorkSession().getOption( ifds::RIFTTaxableRedCode, dstrRIFTTaxableRedCodes, BF::HOST, false);	//RedCode li	

			// 3. All of the following  conditions are true:
			//    3.1  Account has tax type RRIF. The full list of tax types are:
			//         - 2 RRIF
			//         - R PRIF
			//         - B LIF
			//         - L LRIF
			//    3.2  Redemption code is on a list of redemption codes for unscheduled payments, 
			//         on generic control TaxWithHeld PW.
			//    3.3  system feature NoWithTax is turned off, meaning tax must be withheld,
			//    3.4  system feature TaxOnRRIFRed is on
			if( dstrRRIFProduct.find( dstrTaxType ) != DString::npos &&
				 dstrRIFTTaxableRedCodes.find( dstrRedCode ) != DString::npos &&
				 N == dstrNoWithTax &&
				 Y == dstrTaxOnRRIFRed )
			{
				_blTaxable = true;
			}			
			else 
			{
				// get logical1 for generic control = "WithTaxOverride"
				DString dstrWithTaxOverride;
				getWorkSession().getOption( ifds::WithTaxOverride, dstrWithTaxOverride, BF::HOST, false );
				// 1. Both are true:
				//    1.1 Flag 'OverrideTax' on generic control 'WithTaxOverride' is on 
				//        AutomaticAll = Yes
				//    AND 
				//    1.2 Registered account
				if ( Y == dstrWithTaxOverride &&
					  Y == dstrAutomaticAll.stripAll() ) 	
				{
					_blTaxable = true;
				}		
			}
		}
	   else 
		{			
			// get logical1 for generic control = "WithTaxOverride"
			DString dstrWithTaxOverride;
			getWorkSession().getOption( ifds::WithTaxOverride, dstrWithTaxOverride, BF::HOST, false );

			if (dstrWithTaxOverride == Y)
         {
            // Residency Status
			   DString dstrResidency, dstrShrNum;
			   pMFAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup );
			   Shareholder* pShareholder = NULL;
			   if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder ) <= WARNING && 
				    pShareholder)
			   {
				   pShareholder->getField( ifds::Residency, dstrResidency, idDataGroup );
			   }		
   			
			   // get Amount to check if Full Redemption
			   DString dstrAmount;
			   getField( ifds::Amount, dstrAmount, idDataGroup );
			   double dblAmount = DSTCommonFunctions::convertToDouble( dstrAmount );				

			   // Taxable status for a full redemption based on Account Holdings per curr year	 
			   DString dstrTaxOnFullRed;
		      MFAccountHoldingList *pMFAccountHoldingList = NULL;
		      //should pass asofdate get currentyear records.
		      if ( getAccountHoldings (pMFAccountHoldingList, idDataGroup) <= WARNING &&
		           pMFAccountHoldingList )
			   {
			      pMFAccountHoldingList->getField (ifds::TaxOnFullRed, dstrTaxOnFullRed, idDataGroup, false);
			   }
   			
			   // 2. All of the following  conditions are true:
			   //    2.1 Flag 'OverrideTax' on generic control 'WithTaxOverride' is on 
			   //        AutomaticAll = yes
			   //    2.2 Non-Registered account 
			   //    2.3 Non-resident
			   //    2.4 Full redemption
			   //    2.5 Any fund that account held during the calendar year has the fund type listed on 
			   //        the generic control WithTaxOverride FundType Use	
			   //     
			   if( //Y == dstrWithTaxOverride && 
		          I_( "UNREG" ) == dstrPlanType && 
			  	    N == dstrResidency && 
				    0 == dblAmount &&
				    Y == dstrTaxOnFullRed &&
				    Y == dstrAutomaticAll.stripAll())
			   {				
				   _blTaxable = true;
			   }			
		   }
      }

      // for IWT environment
      if( getWorkSession().isIWTClient( idDataGroup ) )
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
	/* 
	 *	Default the FedRate and ProvRate whenever they are applicable.
	 *  Also, do not set default if it is init Pending state
	 *  and the checkbox is checked (User Override, do not need to default).
	 */
	if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
	{
		DString dstrOverrideTax;
		getField(ifds::OverrideTax, dstrOverrideTax, idDataGroup, false);

		if ( _blTaxable && !_bInitPending && (dstrOverrideTax == I_("N")) )
		{
			RedemptionValidation *pRedemptionValidation = NULL;
			if ( getRedemptionValidation (pRedemptionValidation, idDataGroup ) <= WARNING &&
				pRedemptionValidation)
			{
				DString dstrDefaultFedTaxRate, 
					dstrDefaultProvTaxRate;

				pRedemptionValidation->getField (ifds::FedRate,  dstrDefaultFedTaxRate,  idDataGroup);
				pRedemptionValidation->getField (ifds::ProvRate, dstrDefaultProvTaxRate, idDataGroup);

				setField (ifds::FedRate, dstrDefaultFedTaxRate, idDataGroup, true);
				setField (ifds::ProvRate, dstrDefaultProvTaxRate, idDataGroup, true);
				setField (ifds::TransRatePUDFed, I_("P"), idDataGroup);
				setField (ifds::TransRatePUDProv, I_("P"), idDataGroup);
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::validateTaxRatePUD ( const DString &dstrTax,
                                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "ValideTaxRatePUD"));

   // Check if we fall under 1 of the 3 cases in which Withholding Tax is applicable
   if (areTaxRatesAllowed (idDataGroup))
   {
      DString dstrOverrideTax;
      getField( ifds::OverrideTax, dstrOverrideTax, idDataGroup );

      if ( I_( "Y" ) == dstrOverrideTax.stripAll() )
      {
         DString dstrAmtType;
         getField( ifds::AmtType, dstrAmtType, idDataGroup );
         if( dstrAmtType == I_("D") ) //amount
         {
            // Ok, now do the validation
            RedemptionValidation *pRedemptionValidation = NULL;
            if ( getRedemptionValidation( pRedemptionValidation, idDataGroup ) <= WARNING &&
               NULL != pRedemptionValidation )	   
            {
               // get the default rates values
               DString dstrDefaultFedTaxRate, dstrDefaultProvTaxRate;
               pRedemptionValidation->getField( ifds::FedRate,  dstrDefaultFedTaxRate,  idDataGroup );
               pRedemptionValidation->getField( ifds::ProvRate, dstrDefaultProvTaxRate, idDataGroup );
               double dblDefaultFedTaxRate  = DSTCommonFunctions::convertToDouble( dstrDefaultFedTaxRate );
               double dblDefaultProvTaxRate = DSTCommonFunctions::convertToDouble( dstrDefaultProvTaxRate );

               // set the variables for the type of tax we are dealing with (Fed or Prov)
               BFFieldId TaxRateFieldId,
                         TaxRatePUDFieldId;
               double dblDefaultTaxRate = 0;
               if ( I_( "Federal" ) == dstrTax )
               {
                  TaxRateFieldId        = ifds::FedRate;
                  TaxRatePUDFieldId     = ifds::TransRatePUDFed;
                  dblDefaultTaxRate     = dblDefaultFedTaxRate;	
                  setFieldUpdated( ifds::FedRate, idDataGroup, true );
               }
               else if ( I_( "Provincial" ) == dstrTax )
               {
                  TaxRateFieldId        = ifds::ProvRate;
                  TaxRatePUDFieldId     = ifds::TransRatePUDProv;
                  dblDefaultTaxRate     = dblDefaultProvTaxRate;	
                  setFieldUpdated( ifds::ProvRate, idDataGroup, true );
               }

               DString dstrTaxRate, dstrGrossOrNet, dstrTaxRatePUD, dstrProvRatePUD;
               getField( TaxRateFieldId,    dstrTaxRate,    idDataGroup );
               getField( TaxRatePUDFieldId, dstrTaxRatePUD, idDataGroup );
               double dblTaxRate  = DSTCommonFunctions::convertToDouble( dstrTaxRate ); 		

               // If Tax is Dollar Amount, then calculate Tax Amount
               double dblDefaultTaxAmt  = 0;
               if ( I_("D") == dstrTaxRatePUD )
               {
                  getDefaultTaxAmount( dblDefaultTaxRate,
                                       dblDefaultFedTaxRate,
                                       dblDefaultProvTaxRate,
                                       idDataGroup,
                                       dblDefaultTaxAmt );
               }

               if ( ( I_("P") == dstrTaxRatePUD && dblTaxRate < dblDefaultTaxRate ) ||					
                  ( I_("D") == dstrTaxRatePUD && dblTaxRate < dblDefaultTaxAmt ) )
               {
                  if ( I_( "Federal" ) == dstrTax )
                  {
                     ADDCONDITIONFROMFILE( CND::WARN_OVERRIDE_FED_TAX_RATE_LESS_THEN_DEFAULT );
                  }
                  else if ( I_( "Provincial" ) == dstrTax )
                  {
                     ADDCONDITIONFROMFILE( CND::WARN_OVERRIDE_PROV_TAX_RATE_LESS_THEN_DEFAULT );
                  }
               }
            }
         }
         else
         {
            //issue warning No Checking on Tax Rates for Trade Amount not in Dollar
            ADDCONDITIONFROMFILE( CND::WARN_NO_CHECK_ON_TAXRATE_FOR_NON_DOLLAR_AMTTYPE );
         }
      }
   }
   else
   {
      setField( ifds::OverrideTax, N, idDataGroup, false, true );
   }
   return GETCURRENTHIGHESTSEVERITY();  
}

//******************************************************************************
SEVERITY Redemption::validateFedProvTaxRatePUD (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateFedProvTaxRatePUD" ));

   /************************ Withholding Tax Validation for ************************/
   /**** Fed Rate Amount and Type ******* and ******* Prov Rate Amount and Type ****/
   //**** based on Redemption Amount Type, Redemption Code, and System Settings ****/

   // Check if we fall under 1 of the 3 cases in which Withholding Tax is applicable
   if (areTaxRatesAllowed (idDataGroup))
   {
      DString dstrOverrideTax;
      getField( ifds::OverrideTax, dstrOverrideTax, idDataGroup );

      if ( I_( "Y" ) == dstrOverrideTax.stripAll() )
      {
         // Ok, now do the validation
         DString dstrFedTaxRate, dstrProvTaxRate, dstrGrossOrNet, dstrFedRatePUD, dstrProvRatePUD;
         getField( ifds::FedRate,          dstrFedTaxRate,  idDataGroup );
         getField( ifds::ProvRate,         dstrProvTaxRate, idDataGroup );
         getField( ifds::GrossOrNet,       dstrGrossOrNet,  idDataGroup );
         getField( ifds::TransRatePUDFed,  dstrFedRatePUD,  idDataGroup );
         getField( ifds::TransRatePUDProv, dstrProvRatePUD, idDataGroup );

         double dblFedTaxRate  = DSTCommonFunctions::convertToDouble( dstrFedTaxRate ); 
         double dblProvTaxRate = DSTCommonFunctions::convertToDouble( dstrProvTaxRate ); 

         // Check if both or each exceeds 100% when Tax Type is Percent
         if ( // Both Tax Types are percent but all together they exceed 100%
               ( (( dblFedTaxRate + dblProvTaxRate)) > 100.0 && 
                  I_("P") == dstrFedRatePUD && I_("P") == dstrProvRatePUD )
               ||
              // Either of the Tax Type is percent and the value exceeds 100%
               ( ( (dblFedTaxRate) > 100.0  && I_("P") == dstrFedRatePUD ) ||
                  ( (dblProvTaxRate) > 100.0 && I_("P") == dstrProvRatePUD )
               )
            )
         {
            // Issue Severe Error
            ADDCONDITIONFROMFILE( CND::ERR_REDEMPTION_TOTAL_TAX_RATE_GREATER_THAN_100 );
         }
      }
   }
   else
   {
      setField (ifds::OverrideTax, N, idDataGroup, false, true);
   }

   return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
SEVERITY Redemption::getDefaultTaxAmount ( double dblDefaultTaxRate,
                                           double dblDefaultFedTaxRate,
                                           double dblDefaultProvTaxRate,
                                           const BFDataGroupId& idDataGroup,
                                           double &dblDefaultTaxAmt ) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getDefaultTaxAmount" ) );

   dblDefaultTaxAmt  = 0.0;

   DString dstrAmtType;
   getField( ifds::AmtType, dstrAmtType, idDataGroup );

   // If Amount Type is Dollar
   if( I_( "D" ) == dstrAmtType )
   {   
      DString dstrGrossOrNet, dstrAmount;
      getField( ifds::GrossOrNet, dstrGrossOrNet, idDataGroup );
      getField( ifds::Amount,     dstrAmount,     idDataGroup );
      double dblAmount = DSTCommonFunctions::convertToDouble( dstrAmount );

      if( Y == dstrGrossOrNet )     // i.e. Gross
      {
         dblDefaultTaxAmt  = dblAmount * dblDefaultTaxRate  / 100;
      }
      else
      {
         dblDefaultTaxAmt  = dblAmount * dblDefaultTaxRate  / ( 100 - dblDefaultFedTaxRate - dblDefaultProvTaxRate );			
      }
   }
   else  // For anything else there is Master Card
   {
      dblDefaultTaxAmt  = 0.0;		
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
SEVERITY Redemption::validateSuppressCode (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateSuppressCode" ) );   

   DString dstrAccountNum;
   getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

   MFAccount *pMFAccount = NULL;
   if ( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING &&
      pMFAccount)
   {
      DString dstrPayType, dstrSuppressCode;
      getField( ifds::TradesPayType, dstrPayType,      idDataGroup );
      getField( ifds::SuppressCode,  dstrSuppressCode, idDataGroup );

      if ( I_( "16" ) == dstrSuppressCode.stripAll() && !pMFAccount->isClearingAcount( idDataGroup ) )
      {
         //"Suppress Code Clearing cannot be selected for non Clearing Account"
         ADDCONDITIONFROMFILE( CND::ERR_REDEMPTION_SUPPRESS_CODE_INVALID_FOR_NON_CLEARING_ACCOUNT );			
      }

      if ( I_( "16" ) == dstrSuppressCode.stripAll() && pMFAccount->isClearingAcount( idDataGroup ) &&
         I_( "X" ) == dstrPayType.stripAll() )
      {
         //"Suppress Code Clearing cannot be selected for non Clearing Pay Type."
         ADDCONDITIONFROMFILE( CND::ERR_REDEMPTION_SUPPRESS_CODE_INVALID_FOR_NON_CLEARING_PAY_TYPE );			
      }

      if ( I_( "R" ) == dstrPayType.stripAll() && I_( "16" ) != dstrSuppressCode.stripAll() &&
         pMFAccount->isClearingAcount( idDataGroup ) )
      {
         //"Suppress Code must be Clearing for Clearing Account"
         ADDCONDITIONFROMFILE( CND::ERR_REDEMPTION_SUPPRESS_CODE_MUST_BE_CLEARING_FOR_CLEARING_ACCOUNT );			
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Redemption::validateStopSettleRedemption ( const DString &orderType,
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "validateStopSettleRedemption"));

   MFAccount * pMFAccount = NULL;
   if ( getAccount (pMFAccount, idDataGroup) <= WARNING  && 
        pMFAccount) 
   {
      if ( !(pMFAccount->isSettleRedeptionAllowed (idDataGroup)) && 
            orderType == Y) //wire
      {
         ADDCONDITIONFROMFILE (CND::WARN_ACCOUNT_HAS_STOP_REDEMPTION);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::removeAllocationsIfAccountCanBeClosed (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "removeAllocationsIfAccountCanBeClosed"));
   if (canCloseAccount (idDataGroup))
   {
//blow the allocations, if exist
      BFObjIter iter (*this, idDataGroup);

      if (iter.positionByKey (I_("AccountAllocationList")))
      {
         iter.removeObjectFromMap (true);
         //also, reset the fund fields
         setFieldNoValidate ( ifds::FromFund, NULL_STRING, idDataGroup, false, 
                              false,  //invalid
                              true,   //notify
                              false); //do apply
         setFieldNoValidate ( ifds::FromClass, NULL_STRING, idDataGroup, false, 
                              false,  //invalid
                              true,   //notify
                              false); //do apply
         setFieldNoValidate ( ifds::FromFundNumber, NULL_STRING, idDataGroup, false, 
                              false,  //invalid
                              true,   //notify
                              false); //do apply
         setFieldNoValidate ( ifds::FundISIN, NULL_STRING, idDataGroup, false, 
                              false,  //invalid
                              true,   //notify
                              false); //do apply
         setFieldNoValidate ( ifds::FundWKN, NULL_STRING, idDataGroup, false, 
                              false,  //invalid
                              true,   //notify
                              false); //do apply
      }
   }
   else
   {
      refreshAllocations (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::filterSettleCurrencyForFund ( const DString &inCurrSubstList,
                                                   DString &currSubstList,
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("filterSettleCurrencyForFund"));
   DString fundCode,
      classCode;

   getFundField (ifds::FundCode, fundCode, idDataGroup);
   getFundField (ifds::ClassCode, classCode, idDataGroup);
//call base class method
   Trade::filterSettleCurrencyForFund ( fundCode, 
                                        classCode, 
                                        inCurrSubstList, 
                                        currSubstList, 
                                        idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::redCodeRelatedChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("redCodeRelatedChanges"));
   DString redCode;

   getField (ifds::RedCode, redCode, idDataGroup, false);
//for bearer certificate redemption code, from fund field is required
   setFieldRequired ( ifds::FromFund, 
                      idDataGroup, 
                      DSTCommonFunctions::codeInList (redCode, BEARERREDCODELIST));
//if RedCode is not '18 - GIC Maturity', WireOrderNum is updatable
   setFieldReadOnly (ifds::WireOrdNum, idDataGroup, redCode == I_("18"));
   if (redCode != I_("18"))
   {
      DString updOrdType;

      getWorkSession ().getOption ( ifds::UpdOrdType, 
                                    updOrdType, 
                                    BF::HOST,
                                    false);
      setFieldReadOnly ( ifds::OrderType, idDataGroup, 
         !getWorkSession().hasReadPermission (UAF::UPD_ORD_TYPE_REDEMPTION) || updOrdType != Y);
   }
   setFieldValid (ifds::AmtType, idDataGroup, false); //invalidate amt type - 
   setFieldValid (ifds::OrderType, idDataGroup, false); //invalidate order type - 
   setFieldValid (ifds::TradesPayType, idDataGroup, false); //invalidate pay type - 
   setFieldValid (ifds::RESPReportHRDC, idDataGroup, false); //invalidate RESPReportHRDC -
   setFieldValid (ifds::GRRepayReason, idDataGroup, false); //invalidate GRRepayReason - 
   respRedcodeRelatedChange(idDataGroup);
   rdspRedcodeRelatedChange(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Redemption::setDefaultPayType (const DString dstrAccountNum, 
                                    DString &payType,
                                    const BFDataGroupId &idDataGroup)
{
   setClearingAccDefaultPayType (dstrAccountNum, payType, idDataGroup);
}

//******************************************************************************
SEVERITY Redemption::setGIDIFTradePayType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setGIDIFTradePayType"));
	/* 
		Redemption of non residency account holding GI, DIF. The paytype should be suppress readonly.
		The user needs to recalculate the taxable amount manually.			
	*/
	MFAccount *pMFAccount = NULL;

	if (getAccount (pMFAccount, idDataGroup) <= WARNING  && pMFAccount) 
	{
		DString dstrNonRegNonResident,
			prodPortfolioUUID,
			dstrFromFund,
			dstrFromClass;

		pMFAccount->getField (ifds::ProdPortfolioUUID, prodPortfolioUUID, idDataGroup, false);
		prodPortfolioUUID.stripAll ();

		pMFAccount->isNonRegNonResident(dstrNonRegNonResident, idDataGroup);

		getField(ifds::FromFund, dstrFromFund, idDataGroup, false);
		getField(ifds::FromClass, dstrFromClass, idDataGroup, false);
		dstrFromFund.strip().upperCase();
		dstrFromClass.strip().upperCase();

		if ( (!prodPortfolioUUID.empty()) && (dstrNonRegNonResident == YES) )
		{
			bool bApplySuppressReadOnly = false;
			if (dstrFromFund.empty() && dstrFromClass.empty())
			{
				/* 
					In case of Full account redemption, paytype must be suppress read-only whenever
					there is GI or DIF fund with account balance > 0 in the account. Users have to manual cheque to 
					re-calculate taxable amount manually.
				*/
				MFAccountHoldingList *pMFAccountHoldingList = NULL;
				if ( getAccountHoldings (pMFAccountHoldingList, idDataGroup) <= WARNING &&
		             pMFAccountHoldingList )
				{
				    BFObjIter bfIter (*pMFAccountHoldingList, idDataGroup);

					bfIter.begin();
					while (!bfIter.end()) //do we have holdings?
					{
						DString dstrFundCode, dstrSettledValue;						
						bfIter.getObject()->getField(ifds::rxFundCode, dstrFundCode, idDataGroup, false);
						bfIter.getObject()->getField(ifds::SettledValue, dstrSettledValue, idDataGroup, false);
						
						BigDecimal dec_settle_value = DSTCommonFunctions::convertToBigDecimal (dstrSettledValue);

						if ( (isGIAFund(dstrFundCode) || isDIFFund(dstrFundCode)) && dec_settle_value > 0 )
						{
							// one of fund holding list is GI or DIF and bal > 0, paytype is suppress, readonly.
							bApplySuppressReadOnly = true;
							break;
						}
						++bfIter;
					}

				}
			}
			else
			{
				/* Partial redemption, apply only redemption of GI and DIF fund */
				if ( isGIAFund(dstrFromFund) || isDIFFund(dstrFromFund) )
				{
					bApplySuppressReadOnly = true;
				}
			}

			if (bApplySuppressReadOnly)
			{
				setFieldNoValidate (ifds::TradesPayType, PAYTYPE::SUPPRESS, idDataGroup, false);
				setFieldNoValidate (ifds::SuppressCode, SUPPRESS_CHEQUE, idDataGroup, false, true, true, false); 
			}
			setFieldReadOnly (ifds::TradesPayType, idDataGroup, bApplySuppressReadOnly); 

		}
	}	

	return GETCURRENTHIGHESTSEVERITY ();
}   

//******************************************************************************
SEVERITY Redemption::getMaturedUnits( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getMaturedUnits"));

   DString dstrLSIFUnitsAvail = NULL_STRING;

   DString fundCode,classCode;

   getField (ifds::FromFund,fundCode,idDataGroup,false);
   getField (ifds::FromClass,classCode,idDataGroup,false);

   RedemptionValidation *pRedemptionValidation = NULL;

   if ( getRedemptionValidation (pRedemptionValidation, idDataGroup) <= WARNING && 
        pRedemptionValidation)
   {
      pRedemptionValidation->getField (ifds::LSIFUnitsAvail, dstrLSIFUnitsAvail,idDataGroup);
   }

   setFieldNoValidate (ifds::AmtType,I_("U"),idDataGroup, false, false, true);
   setFieldNoValidate (ifds::Amount, dstrLSIFUnitsAvail,idDataGroup, false, false, true);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::getFormerSpouseList( DString& strFormerSpouses, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFormerSpouseList"));

   strFormerSpouses = I_("0=N/A;");
   DString strTaxType, strRedCode, strAccountNum;   
   MFAccount *pMFAccount = NULL;

   getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
   strAccountNum.strip().stripLeading ('0');
   if ( !strAccountNum.empty() && 
        getWorkSession().getMFAccount (idDataGroup, strAccountNum, pMFAccount) <= WARNING && pMFAccount)
   {
      pMFAccount->getField (ifds::TaxType, strTaxType, idDataGroup);
      /*if( strTaxType.strip().upperCase() == TFSA_TAX_TYPE ||
            strTaxType == EXTERNAL_TFSA_TAX_TYPE )*/
      {
         getField( ifds::RedCode, strRedCode, idDataGroup, false );
         if( strRedCode.strip() == I_("29") ||
            strRedCode.strip() == I_("30") )
         {
            populateFormerSpouseList( strAccountNum, strFormerSpouses, idDataGroup );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
SEVERITY Redemption::validateFundSubCatIAFundIndicator(const DString& strFundCode,
                                                       const DString& strClassCode,
                                                       const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundSubCatIAFundIndicator"));

   DString dstrDirDepsBnkApplicable, dstrPayType, dstrTradeDate;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, 
                                 dstrDirDepsBnkApplicable, BF::HOST, false);
   getField (ifds::TradesPayType, dstrPayType, idDataGroup, false);
   getField (ifds::EffectiveDate, dstrTradeDate, idDataGroup, false);

   if (GETCURRENTHIGHESTSEVERITY() <= WARNING && dstrDirDepsBnkApplicable == I_("Y") && 
       !dstrPayType.empty() && dstrPayType == PAYTYPE::DIRECT_DEPOSIT )
   {
      DString strFundCurrency;
      getFundField (strFundCode, strClassCode, ifds::Currency, strFundCurrency);

      if ( !DSTCommonFunctions::codeInList( strFundCurrency ,CANADIAN_DOLLAR_LIST) )
      {
         ADDCONDITIONFROMFILE(CND::ERR_DIRECT_DEPST_FOR_CAN_CUR_ONLY);
         return GETCURRENTHIGHESTSEVERITY();
      }

      BankInstructions *pBankInstructions = NULL;
      InvestorAuthorization *pInvestorAuthorization = NULL;

      getDefaultBankInstructions(pBankInstructions,idDataGroup);
      getActiveInvestorAuthorization( pInvestorAuthorization, dstrTradeDate, idDataGroup );

      if ( GETCURRENTHIGHESTSEVERITY() <= WARNING && pBankInstructions && pInvestorAuthorization )
      {
         DString strIAFundIndicator;
         pInvestorAuthorization->getField( ifds::IAFundIndicator,
                                           strIAFundIndicator,
                                           idDataGroup,
                                           false );
         if ( strIAFundIndicator == TIF_FUND_INDICATOR ) // trimark interest fund
         {
            DString strFundSubCatList;
            getFundField (strFundCode, strClassCode, ifds::FundSubCat, strFundSubCatList);

            if ( !DSTCommonFunctions::codeInList( TIF_FUND_SUB_CAT, strFundSubCatList ))
            {
               ADDCONDITIONFROMFILE(CND::ERR_PW_DIRECT_DPST_INTERESTED_FUND_SUB_CAT);
            }
         }
      }
      else
      {
         DString idiStr, dstrTradeDateFmt;
         getField (ifds::EffectiveDate, dstrTradeDateFmt, idDataGroup, true);

         // only bank instruction missing on specified date
         if ( !pBankInstructions && pInvestorAuthorization )
         {
            addIDITagValue (idiStr, I_("MISSING"), 
               I_("Direct Deposit Banking Information"));
         }
         // only investor authorization rule missing on specified date
         else if ( pBankInstructions && !pInvestorAuthorization )
         {
            addIDITagValue (idiStr, I_("MISSING"), 
               I_("Investor Authorization Information"));
         }
         // both of them missing!, on specified date
         else if ( !pBankInstructions && !pInvestorAuthorization )
         {
            DString strMissing;
            strMissing  = I_("Direct Deposit Banking Information");
            strMissing += I_(" and ");
            strMissing += I_("Investor Authorization Information");
            addIDITagValue (idiStr, I_("MISSING"), strMissing);
         }
         addIDITagValue (idiStr, I_("DATE"), dstrTradeDateFmt);

         getErrMsg ( IFASTERR::DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING, 
                     CND::ERR_DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING, 
                     CND::WARN_DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING, 
                     idDataGroup,
                     idiStr);
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
SEVERITY Redemption::getActiveInvestorAuthorization( InvestorAuthorization *&pInvestorAuthorization ,
                                                     const DString& strTradeDate,
                                                     const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getActiveInvestorAuthorization"));

   MFAccount * pMFAccount = NULL;
   if ( getAccount (pMFAccount, idDataGroup) <= WARNING  && pMFAccount) 
   {
      InvestorAuthorizationList *pInvestorAuthorizationList = NULL;
      if ( pMFAccount->getInvestorAuthorizationList(pInvestorAuthorizationList,idDataGroup) <= WARNING &&
           pInvestorAuthorizationList != NULL )
      {
         BFObjIter bfIter (*pInvestorAuthorizationList, idDataGroup);

         while ( !bfIter.end() )
         {
            DString strIAEffDate, strIAStopDate;
            InvestorAuthorization* pObj = dynamic_cast <InvestorAuthorization*> (bfIter.getObject());
            pObj->getField( ifds::EffectiveDate, strIAEffDate, idDataGroup, false );
            pObj->getField( ifds::StopDate, strIAStopDate, idDataGroup, false );
            
            if ( ( DSTCommonFunctions::CompareDates (strIAEffDate, strTradeDate) == DSTCommonFunctions::FIRST_EARLIER ||
                   DSTCommonFunctions::CompareDates (strIAEffDate, strTradeDate) == DSTCommonFunctions::EQUAL ) && 
                 ( DSTCommonFunctions::CompareDates (strTradeDate, strIAStopDate)== DSTCommonFunctions::FIRST_EARLIER ||
                   DSTCommonFunctions::CompareDates (strTradeDate, strIAStopDate)== DSTCommonFunctions::EQUAL ))
            {
               pInvestorAuthorization = pObj;
               break;
            }
            ++bfIter;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
SEVERITY Redemption::validateTradePayTypeFundClass( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTradePayTypeFundClass"));

   DString dstrFundCode,dstrClassCode;

   getField (ifds::FromFund,dstrFundCode,idDataGroup,false);
   getField (ifds::FromClass,dstrClassCode,idDataGroup,false);

   validateFundSubCatIAFundIndicator(dstrFundCode,dstrClassCode,idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateRedCodeAgainstWDFeeDefault( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRedCodeAgainstWDFeeDefault"));

   MFAccount * pMFAccount = NULL;
   if ( getAccount (pMFAccount, idDataGroup) <= WARNING  && pMFAccount) 
   {
      DString strAcctTaxType;
      pMFAccount->getField( ifds::TaxType, strAcctTaxType, idDataGroup, false );

      RedCodeByTaxTypeList *pRedCodeTaxTypeList = NULL;
      pRedCodeTaxTypeList = new RedCodeByTaxTypeList(*this);

      DString codeType = I_("R");
      if( pRedCodeTaxTypeList->init(strAcctTaxType, codeType ) <= WARNING )
      {
         RedCodeByTaxType *pRedCode = NULL;
         BFObjIter bfIter (*pRedCodeTaxTypeList, idDataGroup);

         bool bFound = false;
         DString strTradeRedCode;
         getField( ifds::RedCode, strTradeRedCode, idDataGroup, false );
         while ( !bfIter.end() )
         {
            DString strRedCodeTaxType;

            pRedCode = dynamic_cast <RedCodeByTaxType*> (bfIter.getObject());
            pRedCode->getField( ifds::RedCode, strRedCodeTaxType, idDataGroup, false );

            if( strRedCodeTaxType == strTradeRedCode )
            {
               bFound = true;
               break;
            }
            ++bfIter;
         }

         if( bFound )
         {
            //If Withdrawal Fee for this redemption code is not defined
            //raise condition up to system severity
            DString strWDFeeDefn;
            pRedCode->getField( ifds::WDFeeDefn, strWDFeeDefn, idDataGroup, false );
            if( strWDFeeDefn.upperCase().stripAll() == I_("0") || strWDFeeDefn.empty() )
            {
               getErrMsg( IFASTERR::FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE,
                          CND::ERR_FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE, 
                          CND::WARN_FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE, 
                          idDataGroup); 
            }
         }
      }
      delete pRedCodeTaxTypeList;
      pRedCodeTaxTypeList = NULL;
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::doValidateAll ( const BFDataGroupId& idDataGroup, 
                                     long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_ ("doValidateAll"));

   if (Trade::doValidateAll (idDataGroup, lValidateGroup) <= WARNING)
   {
      validateSettleLocations (idDataGroup);
      validateEstateAllocationPresent(idDataGroup);

	  DString grRepayReason;
	  getField (ifds::GRRepayReason, grRepayReason, idDataGroup, false);
	  validateGrantRepaymentReason (grRepayReason, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Redemption::isRESPTransferAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRESPTransferAllowed"));

   MFAccount *pMFAccount = NULL;

   if ( getAccount (pMFAccount, idDataGroup) <= WARNING  && pMFAccount) 
   {
      DString taxType;
      DString redCode;

      pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
      taxType.strip().upperCase();

      getField (ifds::RedCode, redCode, idDataGroup, false);

      redCode.stripAll();

      if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES) && 
          DSTCommonFunctions::codeInList (redCode, RESP_TRANSFER_RED_CODES))
         return true;
   }

   return false;
}

//******************************************************************************
bool Redemption::isAIPAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAIPAllowed"));

   MFAccount *pMFAccount = NULL;

   if ( getAccount (pMFAccount, idDataGroup) <= WARNING  && pMFAccount) 
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
	     Also, transfer CBO as well.
	  */
      if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES) && 
          DSTCommonFunctions::codeInList (redCode, RESP_AIP_RED_CODES))
         return true;
   }

   return false;
}

//******************************************************************************
bool Redemption::isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAssociationToOriginalContribAllowed"));

   DString accountNum, redCode;

   bool bIsAssociationToOriginalContribAllowed = false;

   getAccountField (ifds::AccountNum, accountNum, idDataGroup);
   getField (ifds::RedCode, redCode, idDataGroup, false);  

   if (isRESPTradeAccount (idDataGroup))
   {
      DString grPayReason;

      getField (ifds::GRRepayReason, grPayReason, idDataGroup, false);
         
      bIsAssociationToOriginalContribAllowed = 
					(DSTCommonFunctions::codeInList (redCode, RETURN_RECODES) &&  //IN2346626_WO599061
		        	DSTCommonFunctions::codeInList (grPayReason, I_("I01,I02")));
   }
   else if (isRDSPTradeAccount (idDataGroup, accountNum))
   {    
	   bIsAssociationToOriginalContribAllowed = DSTCommonFunctions::codeInList (redCode, I_("BP,GP,RB,RG")); // BP-RDSP Bond Repayment, GP-RDSP Grant Repayment, RB-RDSP Bond Return, RG-RDSP Grant Return
   }

   return bIsAssociationToOriginalContribAllowed;
}

//******************************************************************************
bool Redemption::isRDSPTransferAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRDSPTransferAllowed"));

   MFAccount *pMFAccount = NULL;

	if (getAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
	{
		DString taxType;
		DString redCode;

		pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
		taxType.strip().upperCase();

		getField( ifds::RedCode, redCode, idDataGroup );
		redCode.stripAll();

		if (taxType == RDSP_TAX_TYPE && redCode == EXTERNAL_RDSP_TRANSFER_OUT) // RT - External RDSP Transfer
			return true;
	}
   
   return false;
}

//***********************************************************************************************
SEVERITY Redemption::validateRESPReportHRDC ( const DString &strValue, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateRESPReportHRDC"));

   if (isRESPTradeAccount (idDataGroup))
   {
      DString redCode;
      
      getField (ifds::RedCode, redCode, idDataGroup, false);
      redCode.strip();
      if ( redCode == REDCODE_CLB_RETURN ||
           redCode == REDCODE_ACES_RETURN ||
//           redCode == REDCODE_QESI_SPECIAL_TAX ||
           redCode == REDCODE_CESG_RETURN ||
		   redCode == REDCODE_CESG_BASIC_RETURN ||
		   redCode == REDCODE_CESG_ADDITIONAL_RETURN ||
		   redCode == REDCODE_ADDITIONAL_REPAYMENT ||
		   redCode == REDCODE_SAGES_GRANT_RETURN)
      {
// HRDC Reporting validation
         DString dstrRESPReportHRDC;

         getField (ifds::RESPReportHRDC, dstrRESPReportHRDC, idDataGroup, false);
         dstrRESPReportHRDC.strip().upperCase();
         if (dstrRESPReportHRDC == N)
         {
            ADDCONDITIONFROMFILE (CND::WARN_GRANT_REPAYMENT_NOT_REPORTED_HRDC);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateGrantRepaymentReason ( const DString &strValue, 
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateGrantRepaymentReason"));

   
   DString redCode;
   DString grRepayReason = strValue;
   grRepayReason.strip().upperCase();

   getField (ifds::RedCode, redCode, idDataGroup, false);
   redCode.strip();

   if (isRESPTradeAccount (idDataGroup))
   {
      // GrantRepayment validation.
	  if ( redCode == REDCODE_CLB_RETURN ||
           redCode == REDCODE_ACES_RETURN ||
           redCode == REDCODE_QESI_SPECIAL_TAX ||
		   redCode == REDCODE_QESI_INCREASE_SPECIAL_TAX	||
           redCode == REDCODE_CESG_RETURN ||
		   redCode == REDCODE_CESG_BASIC_RETURN ||
		   redCode == REDCODE_CESG_ADDITIONAL_RETURN ||
		   redCode == REDCODE_ADDITIONAL_REPAYMENT ||
           redCode == REDCODE_QESI_BASIC_ADJ ||
           redCode == REDCODE_QESI_INC_ADJ ||
           redCode == REDCODE_QESI_INTR_PMT || 
		   redCode == REDCODE_SAGES_GRANT_RETURN ||
           redCode == REDCODE_BCTESG_GRANT_RETURN)
      {
         if (grRepayReason.empty ())
         {

// display rejerror 325
            getErrMsg ( IFASTERR::INVALID_CESG_REPAYMENT_REASON_CODE,
                        CND::ERR_INVALID_CESG_REPAYMENT_REASON_CODE,
                        CND::WARN_INVALID_CESG_REPAYMENT_REASON_CODE,
                        idDataGroup );
         }
      }

      if ( (redCode == REDCODE_QESI_SPECIAL_TAX || redCode == REDCODE_QESI_INCREASE_SPECIAL_TAX) && grRepayReason == I_("Q23")) // 78,IR
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_GRANT_REPAYMENT_REASON_REDCODE);
      }
   }

   DString dstrAccountNum;
   getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);	

   if (isRDSPTradeAccount (idDataGroup, dstrAccountNum))
   {
	   if (DSTCommonFunctions::codeInList (redCode, I_("BP,DP,GP,LP,TW")))	// BP-RDSP Bond Repayment, DP-RDSP DAP Payment, GP-RDSP Grant Repayment, LP-RDSP LDAP Payment, TW-RDSP Termination Withdrawal
	   {
		   if (grRepayReason.empty ())
		   {			 
			   // 2181 - Repayment reason must be specified on RDSP withdrawal.
			   getErrMsg (IFASTERR::RDSP_REPAYMENT_REASON_MANDATORY,
						  CND::ERR_RDSP_REPAYMENT_REASON_MANDATORY,
						  CND::WARN_RDSP_REPAYMENT_REASON_MANDATORY,
						  idDataGroup);
		   }
	   }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateOverContrbRedmYear (const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateOverContrbRedmYear"));

   DString redCode;
   getField( ifds::RedCode, redCode, idDataGroup, false );
   redCode.strip().upperCase();

   if ( redCode == REDCODE_RESP_OC_WITHDRAWAL && isRESPTradeAccount(idDataGroup) )
   {
      DString ocRedmYear = strValue;
      ocRedmYear.strip().upperCase();

      int currBusDateYear (0), iOCRedmYear;
      currBusDateYear = DSTCommonFunctions::getYearFromUnFormattedDate (_currentBusinessDate);
      iOCRedmYear = (int)DSTCommonFunctions::convertToDouble( ocRedmYear );

      if ( ocRedmYear.empty() || ocRedmYear == I_("0") || iOCRedmYear > currBusDateYear )
      {
         getErrMsg ( IFASTERR::INVALID_YEAR_RESP_OC_WITHDRAWAL,
                     CND::ERR_INVALID_YEAR_RESP_OC_WITHDRAWAL,
                     CND::WARN_INVALID_YEAR_RESP_OC_WITHDRAWAL,
                     idDataGroup );
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//**************************************************************************************************
SEVERITY Redemption::validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateLinkedEntity"));

   if( Trade::validateLinkedEntity(strValue, idDataGroup) <= WARNING )
   {
      if ( isAssociationWithBeneficiaryAllowed (idDataGroup) )
      {
         DString dstrRedCode;
         getField(ifds::RedCode, dstrRedCode, idDataGroup, false);
         dstrRedCode.strip();

         if( dstrRedCode == REDCODE_CLB_RETURN )
         {
            // validation from PET0165541 QESI Transaction. Section A, 17
            DString dstrLinkedEntityDofBirth;
            Entity *pEntity = NULL;
            if ( getWorkSession().getEntity ( idDataGroup, 
                                             strValue, 
                                             pEntity) <= WARNING && 
               pEntity )
            {
               pEntity->getField(ifds::DofBirth, dstrLinkedEntityDofBirth, idDataGroup, false);
               dstrLinkedEntityDofBirth.strip();
               // get eligible date for CLB
               DString dstrEligDateforCLB;
               getWorkSession ().getOption ( ifds::EligDateforCLB, dstrEligDateforCLB, BF::HOST, false );
               dstrEligDateforCLB.strip();

               if (DSTCommonFunctions::CompareDates (dstrLinkedEntityDofBirth, 
                                                   dstrEligDateforCLB) == 
                                                   DSTCommonFunctions::FIRST_EARLIER)
               {
                  ADDCONDITIONFROMFILE( CND::ERR_BENEF_SELECTED_DATE_BIRTH_NOT_ELIG_FOR_CLB );
               }
            }
         }
      }
      else if (isAIPAllowed (idDataGroup))
      {
         validateAIPEntity (idDataGroup);
      }

   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateTainted(const DString& strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateTainted"));

   DString strTainted = strValue;
   DString strRedCode;

   getField(ifds::RedCode, strRedCode, idDataGroup, false);
   strRedCode.strip().upperCase();

   if ( strRedCode == REDCODE_RESP_REDEEM_CONTRIB )
   {
      if ( strTainted.strip().upperCase().empty()  )
      {
         // raise an error
         ADDCONDITIONFROMFILE (CND::ERR_TAINTED_FIELD_REQUIRED);
      }
      else if ( strTainted.strip().upperCase() == YES )
      {
         // raise warning
         ADDCONDITIONFROMFILE (CND::WARN_TAINTED_ONLY_APPLICABLE_IF_PRE98CONTRIB_IS_YES);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY Redemption::respRedcodeRelatedChange(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("respRedcodeRelatedChange"));
   
   DString redCode(NULL_STRING);
   getField(ifds::RedCode, redCode, idDataGroup, false);
   bool bGRReadOnly = true;
   if (!_bInitPending)
   {
      setFieldNoValidate (ifds::AssistedContrAmt, I_("0.00"), idDataGroup, false, true, true);  
      setFieldNoValidate (ifds::RESPContrDetlTaxYear, NULL_STRING, idDataGroup, false, false, true);
   }
   setFieldReadOnly (ifds::RESPContrDetlTaxYear, idDataGroup, true);
   bool bAssistedAmountApply = false;

   setFieldReadOnly (ifds::AmtType, idDataGroup, false);
   if(isGIInvestmentListApplicable(idDataGroup))
	   setFieldSubstituteValues(ifds::AmtType, idDataGroup, ifds::GIRedemAmountType);
   else
	   setFieldSubstituteValues ( ifds::AmtType, idDataGroup, _multiCurrency == Y ? ifds::AmtTypeMultiCurrency : ifds::AmtTypeRedemption);

   if (isRESPTradeAccount(idDataGroup))
   {
      // All of redemption codes except 75, 76 and 83 would result 'Report to HRDC' to be 'N'
      // then reset this flag to be 'N' first and later if redemption code is either 75, 76 or 83
      // will be 'Y'
	  //PRB0041075 - Do not set this value here as this is overriding the user selection
      //setFieldNoValidate (ifds::RESPReportHRDC, I_("N"), idDataGroup, false); 

      if (DSTCommonFunctions::codeInList (redCode, I_("75,76,78,83,Q1,Q2,Q3,SC,SR,BC,BR,AG,AR,GR,IR")))
      {
         DString grantRepayReasonSubstList;
         BFProperties *pBFProperties = NULL;

         if (DSTCommonFunctions::codeInList (redCode,I_("78,Q1,Q2,Q3,IR"))) 
         {
            setFieldReadOnly (ifds::RESPContrDetlTaxYear, idDataGroup, false);
            setFieldValid (ifds::RESPContrDetlTaxYear, idDataGroup, false);

            if (DSTCommonFunctions::codeInList (redCode,I_("78,IR")))
            {
               setFieldSubstituteValues (ifds::GRRepayReason, idDataGroup, ifds::GRRepayReasonQESI);
               pBFProperties = 
                  getFieldProperties (ifds::GRRepayReason, idDataGroup);
               pBFProperties->getSubstituteValues( grantRepayReasonSubstList );

               setFieldAllSubstituteValues ( ifds::GRRepayReason, 
                                             idDataGroup, 
                                             grantRepayReasonSubstList);
            }
            else
            {
               setFieldSubstituteValues (ifds::GRRepayReason, idDataGroup, ifds::GrantRepayReasonQESI2);
               pBFProperties = 
                  getFieldProperties (ifds::GRRepayReason, idDataGroup);
               pBFProperties->getSubstituteValues( grantRepayReasonSubstList );

               setFieldAllSubstituteValues ( ifds::GRRepayReason, 
                                             idDataGroup, 
                                             grantRepayReasonSubstList);

               if(redCode == I_("Q1"))
               {
                  setFieldReadOnly (ifds::AssistedContrAmt, idDataGroup, false);
                  setFieldValid (ifds::AssistedContrAmt, idDataGroup, false);
                  bAssistedAmountApply = true;
               }
            }
         }
         else if (DSTCommonFunctions::codeInList (redCode, I_("75,76,83,SC,SR,BC,BR,AG,AR,GR")))
         {
            setFieldSubstituteValues (ifds::GRRepayReason, idDataGroup, ifds::GRRepayReasonCommon);

            pBFProperties = 
               getFieldProperties (ifds::GRRepayReason, idDataGroup);
            pBFProperties->getSubstituteValues( grantRepayReasonSubstList );

			if (DSTCommonFunctions::codeInList (redCode, I_("SC,SR"))) // SC-SAGES Correction, SR-SAGES Grant Return
			{
				setFieldNoValidate (ifds::SuppressCode, I_("25"), idDataGroup, false); // SAGES Grant
				setFieldReadOnly (ifds::SuppressCode, idDataGroup, true); 

				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("I01"));
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("I02"));

				if (redCode == I_("SC"))
				{
					setFieldNoValidate (ifds::RESPReportHRDC, I_("N"), idDataGroup, false);
					setFieldNoValidate (ifds::AmtType, I_("D"), idDataGroup, false, true, true);
					setFieldReadOnly (ifds::AmtType, idDataGroup, true);
				}
			}

			if (DSTCommonFunctions::codeInList (redCode, I_("BC,BR"))) // BC-BCTESG Correction, BR-BCTESG Grant Return
			{
				setFieldNoValidate (ifds::SuppressCode, I_("28"), idDataGroup, false); // BCTESG Grant
				setFieldReadOnly (ifds::SuppressCode, idDataGroup, true); 

				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("1"));
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("9"));
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("10"));
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("12"));
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("I01"));
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("I02"));

				if (redCode == I_("BC"))
				{
					setFieldNoValidate (ifds::RESPReportHRDC, I_("N"), idDataGroup, false);
					setFieldNoValidate (ifds::AmtType, I_("D"), idDataGroup, false, true, true);
					setFieldReadOnly (ifds::AmtType, idDataGroup, true);
				}
			}

			if (DSTCommonFunctions::codeInList (redCode, I_("75"))) // 75-CLB Return
			{				
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("1"));
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("10"));				
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("I01"));
				grantRepayReasonSubstList = removeItemFromSubtList ( grantRepayReasonSubstList, I_("I02"));
			}	

            setFieldAllSubstituteValues ( ifds::GRRepayReason, 
                                          idDataGroup, 
                                          grantRepayReasonSubstList);
			//PRB0041075 - Do not set this value here as this is overriding the user selection
            //setFieldNoValidate (ifds::RESPReportHRDC, I_("Y"), idDataGroup, false); 
         }

         pBFProperties = getFieldProperties (ifds::GRRepayReason, idDataGroup);

         // force 'GRRepayReason' field to use substitution value from dynamic list
         pBFProperties->setSubstituteValues(NULL);

         setFieldValid(ifds::GRRepayReason, idDataGroup, false);
         bGRReadOnly = false;

         setFieldNoValidate (ifds::Tainted, I_("N"), idDataGroup, false); 
         setFieldNoValidate (ifds::OCRdmYear, NULL_STRING, idDataGroup, false);
         setFieldReadOnly (ifds::Tainted, idDataGroup, true);
         setFieldReadOnly (ifds::OCRdmYear, idDataGroup, true);   

         setFieldNoValidate (ifds::TradesPayType, PAYTYPE::SUPPRESS, idDataGroup, false);
         setFieldReadOnly (ifds::TradesPayType, idDataGroup, true);     
      }
      else
      {
         bool bDefaultTainted = false;
         bool bEnableOCRdmYear = false;
         MFAccount * pMFAccount = NULL;
         if (getAccount (pMFAccount, idDataGroup) <= WARNING  && pMFAccount)
         {
            DString pre98Contrib;
            pMFAccount->getField( ifds::Pre98Contrib, pre98Contrib, idDataGroup, false );
            pre98Contrib.strip().upperCase();

            if (redCode == REDCODE_RESP_REDEEM_CONTRIB)  // 60
            {
               if (pre98Contrib != I_("Y"))
               {
                  bDefaultTainted = true;
               }
            }
            else if (redCode == REDCODE_RESP_OC_WITHDRAWAL)
            {
               bEnableOCRdmYear = true;
               bDefaultTainted = true;
            }
            // for others redcodes, default tainted to NO, avoid crash!!
            else
               bDefaultTainted = true;

            if (!_bInitPending)
            {
               if( bDefaultTainted )
                  setFieldNoValidate (ifds::Tainted, I_("N"), idDataGroup, false);
               else
                  setFieldNoValidate (ifds::Tainted, NULL_STRING, idDataGroup, false, false, true);               
               
               if ( bEnableOCRdmYear )
                  setFieldNoValidate (ifds::OCRdmYear, I_("0"), idDataGroup, false, false, true);
               else
                  setFieldNoValidate (ifds::OCRdmYear, NULL_STRING, idDataGroup, false);

            }
            setFieldReadOnly (ifds::Tainted, idDataGroup, bDefaultTainted);
            setFieldReadOnly (ifds::OCRdmYear, idDataGroup, !bEnableOCRdmYear);
            setFieldReadOnly (ifds::RESPContrDetlTaxYear, idDataGroup, true);
         }
         setFieldReadOnly (ifds::TradesPayType, idDataGroup, false);
         setFieldReadOnly (ifds::SuppressCode, idDataGroup, false);
      }

      if( !bAssistedAmountApply )
      {
         setFieldReadOnly (ifds::AssistedContrAmt, idDataGroup, true);
         setFieldNoValidate (ifds::AssistedContrAmt, I_("0.00"), idDataGroup, false, true, true);  
      }
      //IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
      if (DSTCommonFunctions::codeInList (redCode, _dstrEAPEarningCodes))
      {
         setFieldReadOnly (ifds::EAPCESGPaid, idDataGroup, false);        
      }
      else
      {
         setFieldReadOnly (ifds::EAPCESGPaid, idDataGroup, true);  
      }
      //---
      
   }

   if (!_bInitPending)
   {
      setFieldNoValidate (ifds::GRRepayReason, NULL_STRING, idDataGroup, false, false, true);
      setFieldNoValidate (ifds::EAPCESGPaid, I_("0.00"), idDataGroup, false);
   }
   setFieldReadOnly(ifds::GRRepayReason, idDataGroup, bGRReadOnly);   

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
bool Redemption::isEAPAllowed (const BFDataGroupId &idDataGroup)
{  //P0185010.FN02.R02.01 - Delivering EAP written notice and tax info return
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isEAPAllowed"));

   MFAccount *pMFAccount = NULL;

   if ( getAccount (pMFAccount, idDataGroup) <= WARNING  && pMFAccount) 
   {
      DString taxType;
      DString redCode;

      pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
      taxType.strip().upperCase();

      getField (ifds::RedCode, redCode, idDataGroup, false);
      
      redCode.stripAll();
      
      if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES) && 
          DSTCommonFunctions::codeInList (redCode, _dstrEAPEarningCodes))
         return true;
   }

   return false;
}
//******************************************************************************
SEVERITY Redemption::validateRedCodeUnclaimedProperty(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateRedCodeUnclaimedProperty"));
 
   MFAccount *pMFAccount = NULL;
   DString dstrRedCode, dstrTaxType, dstrAcctDesignation;
   
   getField(ifds::RedCode, dstrRedCode, idDataGroup, false);
   dstrRedCode.strip();
   
   if ( dstrRedCode == REDCODE_UNCLAIMED )
   {
      if ( getAccount ( pMFAccount, idDataGroup) <= WARNING  && 
          pMFAccount)     
      {
         pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);
         
         if( DSTCommonFunctions::codeInList (dstrTaxType, I_("0,V")) )    // Non-Registered, TFSA
         {
            DString dstrAcctDesignation, dstrRtnMailStageList, dstrStaleChqStageList, dstrRemittedChqStageList;
            // validate the account designation
            pMFAccount->getField(ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false);
            dstrAcctDesignation.strip();

            if( dstrAcctDesignation != ACCT_DESIGNATION_CLIENT )
            {
               ADDCONDITIONFROMFILE (CND::ERR_REDCODE_APPLICABLE_CLIENT);
            }

            // validate the unclaimed stages   
            pMFAccount->getField(ifds::RtnMailStageList, dstrRtnMailStageList, idDataGroup, false);
            pMFAccount->getField(ifds::StaleChqStageList, dstrStaleChqStageList, idDataGroup, false);
            pMFAccount->getField(ifds::RemittedChqStageList, dstrRemittedChqStageList, idDataGroup, false);
            dstrRtnMailStageList.strip().upperCase();
            dstrStaleChqStageList.strip().upperCase();
            dstrRemittedChqStageList.strip().upperCase();
            
            bool bApply = false;
            // S3 = Unclaimed, S4 = Below Threshold
            if( DSTCommonFunctions::codeInList (dstrRtnMailStageList, I_("S3,S4")) )
               bApply = true;

            if (!bApply)
               ADDCONDITIONFROMFILE (CND::ERR_REDCODE_APPLICABLE_S3_S4);      
            
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::validateMoneyMktFund(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMoneyMktFund"));

   editCheckOnMMF( TRADETYPE::REDEMPTION, false, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();	
}

//GIA-INA
//******************************************************************************
bool Redemption::isGIInvestmentListApplicable(const BFDataGroupId &idDataGroup)
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
bool Redemption::isEstateAllocationListApplicable(const BFDataGroupId &idDataGroup)
{
   bool isEstateAllocationListApplicable = false;
   DString dstrFund;
   DString dstrClass;
   DString dstrAccountNum;
   DString dstrTransId;
   DString dstrAmount;  
   DString dstrAmountType;
   DString dstrRedCode;

   getField (ifds::FromFund,     dstrFund,       idDataGroup, false);
   getField (ifds::FromClass,    dstrClass,      idDataGroup, false);
   getField (ifds::AccountNum,   dstrAccountNum, idDataGroup, false);
   getField (ifds::TransId,      dstrTransId,    idDataGroup, false);
   getField (ifds::Amount,       dstrAmount,     idDataGroup, false);
   getField (ifds::AmtType,      dstrAmountType, idDataGroup, false);
   getField (ifds::RedCode,      dstrRedCode,    idDataGroup, false);

   DString dstrDeathRedCode;
   getWorkSession().getOption ( ifds::DeathRedCode, dstrDeathRedCode, BF::HOST, false);
   bool bFoundBeneficiaries = false;
   bool bFoundBeneficiaryWithNoTaxJuris    = false;
   bool bRedCodeAndTaxJurisdictionNotOK    = false;
   bool bRedCodeAndEntityRelationshipNotOK = false;

   dstrAmountType.stripAll();

   MFAccount* pMFAccount = NULL;
   if(getAccount(pMFAccount, idDataGroup)<= WARNING && pMFAccount)
   {
      DString dstrResidency1;
      DString dstrResidency2;
      DString dstrResidency3;
      DString dstrSpouseBenefReLn;
      DString dstrChildBenefReLn;
      getWorkSession().getOption ( ifds::Residency1, dstrResidency1, BF::HOST, false);
      getWorkSession().getOption ( ifds::Residency2, dstrResidency2, BF::HOST, false);
      getWorkSession().getOption ( ifds::Residency3, dstrResidency3, BF::HOST, false);
      
      getWorkSession().getOption ( ifds::SpouseBenefReLn, dstrSpouseBenefReLn, BF::HOST, false);
      getWorkSession().getOption ( ifds::ChildBenefReLn,  dstrChildBenefReLn,  BF::HOST, false);
      
      ACCTENTITYOBJ_VECTOR vBenefEntities;
      pMFAccount->getBeneficiaries(vBenefEntities, idDataGroup );    
      ACCTENTITYOBJ_VECTOR::iterator iter = vBenefEntities.begin();
      while(iter != vBenefEntities.end())
      {
         bFoundBeneficiaries = true;
         DString dstrTaxJurisCode;
         AccountEntityXrefObject* pAccountEntityXrefObject = *iter;
         if(pAccountEntityXrefObject)
         {
            pAccountEntityXrefObject->getField(ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup);
            if(dstrTaxJurisCode.strip() == I_(""))
            {
               bFoundBeneficiaryWithNoTaxJuris = true;
               break;
            }

            bool bTaxJurisInRecidencyCodes = 
                  DSTCommonFunctions::codeInList(dstrTaxJurisCode, dstrResidency1) ||
                  DSTCommonFunctions::codeInList(dstrTaxJurisCode, dstrResidency2) ||
                  DSTCommonFunctions::codeInList(dstrTaxJurisCode, dstrResidency3);

            if((dstrRedCode == I_("07") || dstrRedCode == I_("41")) && bTaxJurisInRecidencyCodes ||
               (dstrRedCode == I_("08") || dstrRedCode == I_("34") || dstrRedCode == I_("57") || dstrRedCode == I_("58") ) && !bTaxJurisInRecidencyCodes)
            {
               bRedCodeAndTaxJurisdictionNotOK = true;
               break;
            }

            DString dstrRelateCode;
            pAccountEntityXrefObject->getField(ifds::RelateCode, dstrRelateCode, idDataGroup);

            if(dstrRedCode == I_("57") && !DSTCommonFunctions::codeInList(dstrRelateCode, dstrSpouseBenefReLn))
            {
               bRedCodeAndEntityRelationshipNotOK = true;
               break;
            }
            if(dstrRedCode == I_("58") && !DSTCommonFunctions::codeInList(dstrRelateCode, dstrChildBenefReLn))
            {
               bRedCodeAndEntityRelationshipNotOK = true;
               break;
            }
            
            DString dstrSegClient;
            getWorkSession().getOption (ifds::SegClient, dstrSegClient, BF::HOST);
            bool bSegFund = dstrSegClient.strip() == I_("Y");

            if(dstrRedCode == I_("41") )
            {
               if(!bSegFund)
               {
                  if(!DSTCommonFunctions::codeInList(dstrRelateCode, dstrChildBenefReLn) &&
                     !DSTCommonFunctions::codeInList(dstrRelateCode, dstrSpouseBenefReLn))
                  {
                     bRedCodeAndEntityRelationshipNotOK = true;
                     break;
                  }
               }
               else
               {
                  if(!DSTCommonFunctions::codeInList(dstrRelateCode, dstrSpouseBenefReLn))
                  {
                     bRedCodeAndEntityRelationshipNotOK = true;
                     break;
                  }
               }
            }

            if(dstrRedCode == I_("58") && bSegFund)
            {
               bRedCodeAndEntityRelationshipNotOK = true;
               break;
            }

         }
         iter++;
      }
   }

   if (!dstrFund.empty() && !dstrClass.empty() && 
       DSTCommonFunctions::codeInList(dstrRedCode, dstrDeathRedCode) &&
      !dstrAccountNum.empty() &&  
      !dstrTransId.empty() && !dstrAmount.empty() && !dstrAmountType.empty() && 
      bFoundBeneficiaries &&
      !bFoundBeneficiaryWithNoTaxJuris &&
      !bRedCodeAndTaxJurisdictionNotOK &&
      !bRedCodeAndEntityRelationshipNotOK &&
      DSTCommonFunctions::codeInList(dstrAmountType, I_("P,U,D")))
   {
      isEstateAllocationListApplicable = true;
   }
   return isEstateAllocationListApplicable;
}

/*******************************************************************************
Input:BFDataGroupID.
PutPut:None
Return:bool
Functionality:Call the function to see if the Account is of Tax Type Related 
              to reg agent
*******************************************************************************/
bool Redemption::bIsTaxTypeRelatedtoRegAgent (const BFDataGroupId &idDataGroup)
{
  
 MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("bIsTaxTypeRelatedtoRegAgent"))
 MFAccount *pMFAccount = NULL;
 bool bTaxTypeRegAgent = false;
  if( getAccount ( pMFAccount, idDataGroup)<= WARNING && 
      pMFAccount )
   bTaxTypeRegAgent =pMFAccount->bIsTaxTypeRelatedtoRegAgent(idDataGroup);
  return (bTaxTypeRegAgent);  		
}

/******************************************************************************
Input:DataGroupID
OutPut:None
Return:Bool
Functionality:Checks the Pay instr option is redirect to reg agent or not
******************************************************************************/
bool Redemption::bIsRegAgentPayInstOption (const BFDataGroupId &idDataGroup)
{
   DString payInstrOption;

   getField (ifds::PayInstrOption, payInstrOption, idDataGroup, false);
   return payInstrOption == I_("03"); //redirect to reg agent
}

//******************************************************************************
SEVERITY Redemption::validateSrcOfFund(const DString& strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSrcOfFund"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::loadBusinessTypeSubslist( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("loadBusinessTypeSubslist"));
   //P0186486_FN15_The Source of Funds
   DString sourceOfFundApp;

   getWorkSession().getOption(ifds::SourceOfFundApp, sourceOfFundApp, idDataGroup, false);
   sourceOfFundApp.strip().upperCase();

   if(sourceOfFundApp == I_("Y")) 
   {
      DString SrcOfFunds_IA_PW_List;
      getWorkSession().getOption(ifds::SrcOfFunds_IA_PW, SrcOfFunds_IA_PW_List, idDataGroup, false);
      SrcOfFunds_IA_PW_List.strip().upperCase();
      if(!SrcOfFunds_IA_PW_List.empty())
      {
         replaceSubstitutionList(SrcOfFunds_IA_PW_List,
                                 ifds::SrcOfFunds_IA, 
                                 ifds::SrcOfFund, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
SEVERITY Redemption::raiseFullRedemptionMessage( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("raiseFullRedemptionMessage"));

   ADDCONDITIONFROMFILE (CND::ERR_FULL_REDEMPTION_INDICATED); //give a warning

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
bool Redemption::isExternalInstitutionTrackingEnable(const BFDataGroupId& idDataGroup)
{
   bool bReturnValue = false;

   DString strTrackTrActive,strTrackTrRedCode;
   getWorkSession().getOption2(ifds::TrackTrActive,strTrackTrActive,idDataGroup,false);
   getWorkSession().getOption2(ifds::TrackTrRedCode,strTrackTrRedCode,idDataGroup,false);
   strTrackTrActive.strip().upperCase();
   strTrackTrRedCode.strip().upperCase();

   if (!strTrackTrActive.empty() && strTrackTrActive == I_("Y") && !strTrackTrRedCode.empty())
   {
      DString redCode;

      getField (ifds::RedCode, redCode, idDataGroup, false);
      redCode.strip().upperCase();
      bReturnValue = DSTCommonFunctions::codeInList (redCode, strTrackTrRedCode);
   }

   return bReturnValue;
}
//**********************************************************************************************************************************
SEVERITY Redemption::setDefaultForRedCode(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setDefaultForRedCode"));

	DString dstrRedCode;
    getField (ifds::RedCode,dstrRedCode, idDataGroup, false );

	if (dstrRedCode == REDCODE_REDEMPTION_RECLASS)
	{
		DString dstrFromFundCode,dstrFromClassCode,dstrFromPriceTypesList;

		getField (ifds::FromFund,dstrFromFundCode, idDataGroup, false );
		getField (ifds::FromClass,dstrFromClassCode, idDataGroup, false );
		FundDetailList * pFundDetailList = NULL;
		getMgmtCo().getFundDetailList(pFundDetailList);

		if(pFundDetailList)
		{  
			FundDetail* pFundDetail = NULL;
			dstrFromFundCode.strip().upperCase();
			dstrFromClassCode.strip().upperCase();
			pFundDetailList->getFundDetail(dstrFromFundCode,dstrFromClassCode,idDataGroup,pFundDetail);
			if(pFundDetail)
			{
				pFundDetail->getField(ifds::PriceTypes,dstrFromPriceTypesList,idDataGroup,false);
			}
		}
		std::list<DString> FromPriceTypesList;
		DString::size_type pos = 0;
		DString dstrFromPriceType;
		while (dstrFromPriceTypesList != NULL_STRING)
		{
			EXTRACT_VALUE(dstrFromPriceTypesList, dstrFromPriceType);
			CHOP_STRING(dstrFromPriceTypesList);
			FromPriceTypesList.push_back(dstrFromPriceType);			
		}				
		for(std::list<DString>::iterator itr = FromPriceTypesList.begin();itr != FromPriceTypesList.end();itr++)
		{
			if(PRICETYPE_REDEMPTION_RECLASS == *itr)
			{
				setFieldNoValidate (ifds::TradesPayType, PAYTYPE_SUPPRESS, idDataGroup, false, false, true);
				setFieldNoValidate (ifds::PricingCode, PRICETYPE_REDEMPTION_RECLASS, idDataGroup, false, false, true);
			}
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//****************************************************************************************************************************
SEVERITY Redemption::initPriceTypesList(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initPriceTypesList"));

	DString dstrFromFundCode,dstrFromClassCode;

	getField (ifds::FromFund,dstrFromFundCode, idDataGroup, false );
	getField (ifds::FromClass,dstrFromClassCode, idDataGroup, false );

	if (dstrFromFundCode != NULL_STRING && dstrFromClassCode != NULL_STRING )
	{
		DString dstrGroupCodeSubsList,dstrFromPriceTypesList,dstrPriceTypesList;
		setFieldReadOnly( ifds::PricingCode, idDataGroup, false );

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

		}
		dstrBufferName.append( I_("= ;"));
		dstrGroupCodeSubsList.insert(0,dstrBufferName.c_str());
		setFieldAllSubstituteValues(ifds::PricingCode, idDataGroup, dstrGroupCodeSubsList);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************************************
SEVERITY Redemption::hasWaiveGatingFund(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("hasWaiveGatingFund"));
	DString strRunMode, 
			strFromFund,			
			strTransType, 
			strDealDate,
			strCallingType,
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
bool Redemption::isAllFundsFullMoneyOutIndc (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAllFundsFullMoneyOutIndc"));

   DString redCode, fullMoneyOutIndc;
   bool bAllFundsFullMoneyOut = false;

   getField(ifds::RedCode, redCode, idDataGroup, false);
   getField (ifds::FullMoneyOutIndc, fullMoneyOutIndc, idDataGroup, false);
   fullMoneyOutIndc.stripAll().upperCase();

   if ( DSTCommonFunctions::codeInList (redCode, I_("BP,DP,GP,RT,TW")) && !fullMoneyOutIndc.empty() && fullMoneyOutIndc == I_("ALLFND") ) // BP-RDSP Bond Repayment, DP-RDSP DAP Payment, GP-RDSP Grant Repayment, RT-External RDSP Transfer, TW-RDSP Termination Withdrawal
   {	
	   bAllFundsFullMoneyOut = true;	  
   }
  
   return bAllFundsFullMoneyOut;
}

//******************************************************************************
bool Redemption::fullMoneyOutRelatedChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("fullMoneyOutRelatedChanges"));
 
   bool bDisable = false;

   setFieldNoValidate (ifds::AmtType, I_("D"), idDataGroup, false, true, true);	// Amount
   setFieldReadOnly (ifds::AmtType, idDataGroup, true);

   if (isAllFundsFullMoneyOutIndc(idDataGroup))
   {	
	   bDisable = true;

	   setFieldNoValidate (ifds::FromFundNumber, NULL_STRING, idDataGroup, false, true, true);
	   setFieldNoValidate (ifds::FromFund, NULL_STRING, idDataGroup, false, true, true);
	   setFieldNoValidate (ifds::FromClass, NULL_STRING, idDataGroup, false, true, true);
	   setFieldNoValidate (ifds::Amount, I_("0"), idDataGroup, false, true, true);	   
	   setFieldNoValidate (ifds::GrossOrNet, I_("Y"), idDataGroup, false, true, true); // Gross	

	   BFObjIter iter (*this, idDataGroup);
	   if (iter.positionByKey (I_("AccountAllocationList")))
	   {
		   iter.removeObjectFromMap (true);      
	   }
   }

   setFieldReadOnly (ifds::FromFundNumber, idDataGroup, bDisable);
   setFieldReadOnly (ifds::FromFund, idDataGroup, bDisable);
   setFieldReadOnly (ifds::FromClass, idDataGroup, bDisable);
   setFieldReadOnly (ifds::Amount, idDataGroup, bDisable); 
   setFieldReadOnly (ifds::GrossOrNet, idDataGroup, bDisable);

   setFieldRequired (ifds::FromFundNumber, idDataGroup, !bDisable);
   setFieldRequired (ifds::FromFund, idDataGroup, !bDisable);
   setFieldRequired (ifds::FromClass, idDataGroup, !bDisable);
   
   return bDisable;
}

//******************************************************************************
SEVERITY Redemption::rdspRedcodeRelatedChange(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("rdspRedcodeRelatedChange"));

	DString accountNum;
	getField (ifds::AccountNum, accountNum, idDataGroup, false);

	bool bIsRDSPGrantOrBond = false;

	if (isRDSPTradeAccount(idDataGroup, accountNum))
	{  
		DString grantRepayReasonSubstList;
		BFProperties *pBFProperties = NULL;

		DString redCode;
		getField(ifds::RedCode, redCode, idDataGroup, false);	
		redCode.stripAll().upperCase();				

		bool bGRReadOnly = true;

		if (DSTCommonFunctions::codeInList (redCode, I_("BP,DP,GP,LP,TW"))) // BP-RDSP Bond Repayment, DP-RDSP DAP Payment, GP-RDSP Grant Repayment, LP-RDSP LDAP Payment, TW-RDSP Termination Withdrawal			
		{	
			setFieldSubstituteValues (ifds::GRRepayReason, idDataGroup, ifds::GRRepayReasonRDSP);	

			setFieldNoValidate (ifds::AmtType, I_("D"), idDataGroup, false, true, true);
			setFieldReadOnly (ifds::AmtType, idDataGroup, true);

			pBFProperties = getFieldProperties (ifds::GRRepayReason, idDataGroup);
			pBFProperties->getSubstituteValues (grantRepayReasonSubstList);

			setFieldAllSubstituteValues ( ifds::GRRepayReason, idDataGroup, grantRepayReasonSubstList);
			pBFProperties->setSubstituteValues(NULL);

			setFieldValid(ifds::GRRepayReason, idDataGroup, false);
			bGRReadOnly = false;				        
		}		        

		setFieldReadOnly(ifds::GRRepayReason, idDataGroup, bGRReadOnly);		

		fullMoneyOutRelatedChanges (idDataGroup);
	
		bIsRDSPGrantOrBond = DSTCommonFunctions::codeInList (redCode, I_("BP,GP,RB,RG")) ? true : false; // BP-RDSP Bond Repayment, GP-RDSP Grant Repayment, RB-RDSP Bond Return, RG-RDSP Grant Return 

		getGrossNetType(idDataGroup);

	}

	setFieldReadOnly (ifds::RDSPPaymtDate, idDataGroup, !bIsRDSPGrantOrBond);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Redemption::validateRDSPTrade (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRDSPTrade"));

	DString dstrAccountNum, dstrRedCode, dstrFullMoneyOutIndc, dstrExtAccount, dstrExtSpecimenPlanNo;

	getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);	
	getField( ifds::RedCode, dstrRedCode, idDataGroup );
	getField (ifds::FullMoneyOutIndc, dstrFullMoneyOutIndc, idDataGroup, false);
	getField (ifds::ExtAccount, dstrExtAccount, idDataGroup, false);
	getField (ifds::ExtSpecimenPlanNo, dstrExtSpecimenPlanNo, idDataGroup, false);

	dstrRedCode.stripAll();
	dstrFullMoneyOutIndc.stripAll();
	dstrExtAccount.stripAll();
	dstrExtSpecimenPlanNo.stripAll();

	if (!dstrAccountNum.empty() && !isAllFundsFullMoneyOutIndc(idDataGroup))
	{
		Trade::validateRDSPTrade (idDataGroup, dstrAccountNum);

		if (dstrRedCode == EXTERNAL_RDSP_TRANSFER_OUT)
		{
			if (dstrFullMoneyOutIndc.empty())
			{
				// 2209 - Partial transfers not permitted for RDSP accounts.
				getErrMsg (IFASTERR::RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED,
						   CND::ERR_RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED,
						   CND::WARN_RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED,
						   idDataGroup);
			}

			if (dstrExtAccount.empty())
			{
				// 2140 - External RDSP Account Contract Number is mandatory.
				getErrMsg (IFASTERR::RDSP_EXTERNAL_CONTRACT_MANDATORY,
						   CND::ERR_RDSP_EXTERNAL_CONTRACT_MANDATORY,
						   CND::WARN_RDSP_EXTERNAL_CONTRACT_MANDATORY,
						   idDataGroup);
			}

			if (dstrExtSpecimenPlanNo.empty())
			{
				// 2141 - External RDSP Specimen Plan Number is mandatory.
				getErrMsg (IFASTERR::RDSP_EXTERNAL_PLAN_MANDATORY,
						   CND::ERR_RDSP_EXTERNAL_PLAN_MANDATORY,
						   CND::WARN_RDSP_EXTERNAL_PLAN_MANDATORY,
						   idDataGroup);
			}		
		}
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Redemption::getGrossNetType( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getGrossNetType"));

   DString dstrGrossNetType = NULL_STRING, grossNetType;

   RedemptionValidation *pRedemptionValidation = NULL;

   if ( getRedemptionValidation (pRedemptionValidation, idDataGroup) <= WARNING && 
	   pRedemptionValidation)
   {
	   pRedemptionValidation->getField (ifds::GrossNetType, dstrGrossNetType, idDataGroup);
   }

   dstrGrossNetType.stripAll().upperCase();

   if (!dstrGrossNetType.empty() && (dstrGrossNetType != I_("B"))) // G-Gross, N-Net, B-Both
   {
	   grossNetType = (dstrGrossNetType == N) ? N : Y;
	   setFieldNoValidate (ifds::GrossOrNet, grossNetType, idDataGroup, false, true, true);
	   setFieldReadOnly (ifds::GrossOrNet, idDataGroup, true);		
   }   

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Redemption.cpp-arc  $
// 
//    Rev 1.354   10 Aug 2012 13:07:26   if991250
// Estate Allocation
// 
//    Rev 1.353   02 Aug 2012 17:47:58   if991250
// IN3043023: net percent redemptions are not allowed
// 
//    Rev 1.352   25 Jul 2012 17:49:32   if991250
// P0186484 : Estate Allocation
// 
//    Rev 1.351   Jun 08 2012 14:11:56   jankovii
// IN 2957854 - P0186477_FN05_03_Same transno. in distrib-delt to be used & changes to misc-info
// 
//    Rev 1.350   Jun 01 2012 11:57:16   popescu
// Synch-up - Incident 2950725 - R12.3-FN05-Issue during Redemption on Death on Annuitant - Red Code 57
// 
//    Rev 1.349   May 25 2012 15:45:56   jankovii
// Percent Fee changes have been revised to its original code.
// 
//    Rev 1.345   May 18 2012 11:04:04   popescu
// PETP0187485 - Trade Entry And Processing
// 
//    Rev 1.344   May 10 2012 18:03:20   wp040027
// PETP0187485 - Trade Entry And Processing
// 
//    Rev 1.343   May 07 2012 07:34:18   popescu
// PETP0187485 - Trade Entry And Processing
// 
// 
//    Rev 1.342   May 04 2012 11:28:40   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.341   Apr 24 2012 21:13:32   wp040039
// PETP0187485 - Trade Entry And Processing
// 
// 
//    Rev 1.340   Apr 24 2012 21:10:54   wp040039
// PETP0187485 - Trade Entry And Processing
// 
//    Rev 1.339   Apr 20 2012 11:54:16   popescu
// 2924906 - R12.3 Regression - Pay Type of Redemptions cannot be changed
// 
//    Rev 1.338   Apr 20 2012 03:38:44   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.337   Apr 05 2012 11:32:38   jankovii
// Sync up: IN 2898233 - R12.3-P0186477-Enable manual tax calculation of money out transactions for NR
// 
//    Rev 1.336   Mar 19 2012 12:52:52   if991250
// RedemOrder default value
// 
//    Rev 1.335   Mar 14 2012 12:27:38   wutipong
// IN2831801 - Value Date can be modified in iFAST/Desktop for Direct
// 
//    Rev 1.334   Mar 08 2012 10:01:24   if991250
// GI Money Out
// 
//    Rev 1.333   Mar 05 2012 11:45:28   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.332   Feb 13 2012 04:37:00   wutipong
// Remove changes done in rev.1.331. IN2831801.
// 
//    Rev 1.331   Feb 10 2012 11:12:28   wutipong
// IN2831801 - sync up.
// 
//    Rev 1.330   Jan 06 2012 13:38:42   if991250
// IA money out
// 
//    Rev 1.329   Dec 22 2011 11:17:22   kitticha
// PETP0183105 FN02 IN2774076 - SDC is not applied redcode UP.
// 
//    Rev 1.328   Dec 08 2011 21:47:36   wp040032
// P0183989 - Money Market Non Receipt
// 
//    Rev 1.327   Oct 28 2011 04:38:20   kitticha
// PETP0188150 FN01 - Irish Withholding Tax Functionality.
// 
//    Rev 1.326   Oct 21 2011 09:42:12   kitticha
// PETP0188150 FN01 - Irish Withholding Tax Functionality.
// 
//    Rev 1.325   Oct 14 2011 12:32:38   panatcha
// IN2689391 - [update] change field to EAPCESGPaid
// 
//    Rev 1.324   Oct 13 2011 06:19:30   panatcha
// IN2689391 - PET0185010_FN01: CESG Paid is tracked at the EAP level
// 
//    Rev 1.323   Oct 07 2011 01:15:06   kitticha
// PETP0183105 FN02 - Unclaimed Property Alberta.
// 
//    Rev 1.322   Oct 06 2011 10:49:42   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.321   Aug 29 2011 03:10:54   wutipong
// IN2623194 Value date not updated for Direct Trades (after fund is updated)
// 
//    Rev 1.320   Aug 03 2011 11:28:38   wp040027
// P0186774 - Mutual Fund Order Processing
// 
//    Rev 1.319   Jul 20 2011 18:05:14   dchatcha
// P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
// 
//    Rev 1.318   Mar 21 2011 22:49:38   panatcha
// IN2346626_WO599061 - NeedToReportToHRSC 'N' for RD75,76 and GrantRepayReason I01,I02
// 
//    Rev 1.317   Feb 18 2011 04:59:24   kitticha
// PET0165541_FN12_IN2385316 - Default the assisted contribution amount for ED 78(same as PW Q1).
// 
//    Rev 1.316   Jan 26 2011 06:28:06   panatcha
// [Sync up] PET0165541_FN12_IN2392349_WO580043 – Incorrect amt prepopulated in AC field-Q1 redemption
// 
//    Rev 1.315   Jan 13 2011 15:49:50   dchatcha
// IN# 2389426 - P0165541FN12 - DSK Edits and Labels
// 
//    Rev 1.314   Jan 12 2011 14:22:58   dchatcha
// IN# 2346626 - NeedToReportto HRSDC flag should be switched to N for RD-83 and GRRepayReason-I01 or I02.
// 
//    Rev 1.313   Jan 10 2011 15:32:16   dchatcha
// IN# 2380683 - P0165541FN12 - Q1,Q2 and Q3 reason code.
// 
//    Rev 1.312   Nov 29 2010 02:43:26   kitticha
// IN#2291872 - Release 99, QESI project. Q1 and Q2 redemption cannot deplete more than balance.
// 
//    Rev 1.311   Nov 23 2010 00:18:22   dchatcha
// Synch up: IN# 2304816 - Rel 100 QESI project. T06 special tax.
// 
//    Rev 1.310   Nov 11 2010 04:07:34   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.309   Nov 05 2010 04:18:16   dchatcha
// IN# 2312326 - Error Encountered - Redemption Code 18 in Desktop during trade entry
// 
//    Rev 1.308   Nov 03 2010 07:06:32   dchatcha
// IN# 2312326 - Error Encountered - Redemption Code 18 in Desktop during trade entry
// 
//    Rev 1.307   Oct 29 2010 05:06:46   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.306   Sep 29 2010 11:35:08   jankovii
// PET0175377 FN01 - AIP for Joint RESP Account
// 
//    Rev 1.305   Sep 24 2010 14:27:52   jankovii
// PET0175377 FN01 - AIP for Joint RESP Account
// 
//    Rev 1.304   Aug 05 2010 23:48:02   dchatcha
// IN# 2202493 - QESI prerel99 - 'Need to report to HRDC' field default. Logic would cover other RedCodes though.
// 
//    Rev 1.303   Aug 05 2010 05:19:28   dchatcha
// IN# 2202493 - QESI prerel99 - 'Need to report to HRDC' field default.
// 
//    Rev 1.302   Jun 11 2010 04:09:18   kitticha
// PETP0165541 FN01 IN#2140699 - Additional warning for redcode 64, 65.
// 
//    Rev 1.301   May 28 2010 13:51:20   popescu
// remove special tax redemption code 78 from the validation of the reported to HRDC warning message.
// 
//    Rev 1.300   May 27 2010 06:10:00   kitticha
// PETP0165541 FN02 QESI Phase2.
// 
//    Rev 1.299   May 18 2010 11:48:04   dchatcha
// RESP - Removed Redcode-83 from edit check , modify condition description to depend on trade type.
// 
//    Rev 1.298   May 12 2010 07:55:46   popescu
// RESP - Added TaxYear and related validation
// 
//    Rev 1.297   May 11 2010 07:31:16   kitticha
// PET0165541 FN01 IN#2112487 - Missing steps upon doing Red Code 60.
// 
//    Rev 1.296   May 04 2010 10:18:18   jankovii
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.295   Apr 30 2010 08:07:46   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.294   Apr 29 2010 23:21:08   popescu
// RES-QESI Trading - PSE/EAP work
// 
//    Rev 1.293   Apr 29 2010 11:51:42   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.292   Apr 27 2010 15:52:04   popescu
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.291   Apr 27 2010 10:57:46   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.290   Apr 27 2010 02:18:34   dchatcha
// Fix compile error.
// 
//    Rev 1.289   Apr 26 2010 13:33:00   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.288   Apr 23 2010 22:21:52   popescu
// PET0165541 FN01 QESI RESP Trading - restore ordertype logic.
// 
//    Rev 1.287   Apr 23 2010 02:54:12   kitticha
// PET0165541 FN01 QESI RESP Trading - restore ordertype logic.
// 
//    Rev 1.286   Apr 22 2010 07:54:48   dchatcha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.285   Apr 22 2010 04:04:06   dchatcha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.284   Apr 21 2010 13:53:18   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.283   Apr 21 2010 01:21:16   popescu
// RESP-QESI Resp transfer screen
// 
//    Rev 1.282   Apr 20 2010 00:53:40   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - PSE/EAP   screen
// 
//    Rev 1.281   Apr 14 2010 23:58:22   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.280   Apr 14 2010 09:42:00   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.279   Dec 18 2009 10:39:18   jankovii
// PET0166095 FN01 Validations on Money Out Transactions
// 
//    Rev 1.278   Dec 10 2009 23:22:54   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2. Core review, move all of logic from Redemption object to Trade object.
// 
//    Rev 1.277   Dec 03 2009 03:02:34   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2.
// 
//    Rev 1.276   Oct 19 2009 04:53:04   dchatcha
// IN# 1808372 - 95 - Investor Authorization - Error message not clear for few scenarios, fix for date formatting.
// 
//    Rev 1.275   Oct 07 2009 12:36:26   dchatcha
// IN# 1808372 - 95 - Investor Authorization - Error message not clear for few scenarios.
// 
//    Rev 1.274   Aug 27 2009 12:03:46   dchatcha
// IN#1813640 - Rel 95 - not allowed to enter trade for day IA is expiring.
// 
//    Rev 1.273   Aug 14 2009 14:11:26   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.272   Aug 13 2009 15:58:30   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.271   Aug 11 2009 13:55:26   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.270   Jul 30 2009 18:37:34   dchatcha
// Synch up:IN#1611516 - New edit at desktop trade level to prevent enter redemption, if there is improper default fee setup.
// 
//    Rev 1.269   27 Jul 2009 15:14:18   popescu
// Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
// 
//    Rev 1.268   Jul 16 2009 19:31:58   dchatcha
// PET156681 FN14 H36 Investor Authorization, Code Review.
// 
//    Rev 1.267   Jul 09 2009 15:04:26   dchatcha
// PET156681 FN14 H36 Investor Authorization.
// 
//    Rev 1.266   29 Jun 2009 17:03:44   popescu
// PET 156681 - FN 14 - Investor Authorization
// 
//    Rev 1.265   29 Jun 2009 16:32:18   popescu
// Incident  1725375 - fixed the recalculatin of the trade if the order type is flippend back and forth between wire and direct - synch-up
// 
//    Rev 1.264   11 May 2009 09:44:24   sibuhatm
// Added condition for validating Account designation is "Client" when selecting Redemption code "EF".
// 
//    Rev 1.263   Apr 17 2009 10:49:06   jankovii
// PET 157825 FN04 Manual RRIF Redemption.
// 
//    Rev 1.262   06 Apr 2009 12:11:18   popescu
// Incident 1605422 - recalculate the value date by calling vew 135 with validation type 1 - if order type changes.
// 
//    Rev 1.261   06 Apr 2009 12:09:36   popescu
// Incident 1605422 - recalculate the value date by calling vew 135 with validation type 1 - if order type changes.
// 
//    Rev 1.260   19 Mar 2009 14:10:32   popescu
// Incident 1605422 - recalculate the value date by calling vew 135 with validation type 1 - if order type changes.
// 
//    Rev 1.259   18 Mar 2009 18:27:26   popescu
// IN 1402420,1594221 - RL91 - Override tax rate issues. Take out code that related to overriding tax issue.
// 
//    Rev 1.258   Mar 13 2009 00:03:36   wutipong
// IN1358908 -- Correct 'MAKEFROMEAUTOPROMOTE' call in 'getFormerSpouseList()' function.
// 
//    Rev 1.257   03 Mar 2009 09:08:18   kovacsro
// IN#1605382 - Modify Value date not update for Direct order Redemption
// 
//    Rev 1.256   Feb 23 2009 04:12:36   dchatcha
// IN 1402420,1594221 - RL91 - Override tax rate issues.
// 
//    Rev 1.255   Jan 23 2009 06:27:30   daechach
// IN 1402420 - No warning message when override tax rate less than default rate.
// 
//    Rev 1.254   12 Jan 2009 22:30:08   popescu
// Incident 1321751 - manually altered FX's are taken for redemption validations  - subsequent fix
// 
//    Rev 1.253   03 Dec 2008 15:18:02   popescu
// Incident 1321751 - manually altered FX's are taken for redemption validations 
// 
//    Rev 1.252   Nov 28 2008 14:45:04   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.251   06 Oct 2008 13:19:36   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.250   01 Oct 2008 11:58:58   popescu
// Check in for incident 1419539
// 
//    Rev 1.249   18 Jun 2008 15:06:30   popescu
// Incident# 1315311 - do not calculate the reciprocal...get this from the database
// 
//    Rev 1.248   16 Jun 2008 16:34:08   popescu
// Incident# 1315311 - param the Exact Date input field for view 134 that reads the exchange rates
// 
//    Rev 1.247   May 14 2008 11:55:58   jankovii
// Sync up: IN 1280950 - The check of the GC  for trade entry should be removed from Desktop.
// 
//    Rev 1.246   Apr 28 2008 17:31:54   wongsakw
// Sync up : IN1235049 -- SSIIL iFAST UAT issue - Unsettled Units Redemption Validation fx issue
// 
//    Rev 1.245   Apr 23 2008 15:24:16   jankovii
// Sync up: IN 1254788 - Desktop default bank in trade where acct has only Alt EFT Redemption bank.
// 
//    Rev 1.244   16 Apr 2008 09:21:22   kovacsro
// PET2255FN47 - UT fixes
// 
//    Rev 1.243   15 Apr 2008 12:09:52   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.242   Apr 01 2008 14:52:28   jankovii
// IN 1235803 - Ifast Desktop Error Message/ redemption processing.
// 
//    Rev 1.241   Feb 20 2008 09:49:38   jankovii
// PET 2385 FN06 Bank Details upload.
// 
//    Rev 1.240   Jan 29 2008 16:13:32   yingz
// fix incident 1152960 - overridetax issue
// 
//    Rev 1.239   23 Nov 2007 11:31:04   kovacsro
// PET5685FN25 - age71 changes for RRSP&RIF
// 
//    Rev 1.238   Oct 08 2007 15:11:42   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.237   Sep 06 2007 10:26:32   popescu
// Switched the code around - moved the call in doApplyRelatedChanges
// 
//    Rev 1.236   Sep 05 2007 09:42:28   smithdav
// IN 980102
// 
//    Rev 1.235   Aug 10 2007 14:11:10   jankovii
// PET 2360 FN14&FN19 - Management Fee.
// 
//    Rev 1.234   24 Jul 2007 20:13:22   popescu
// GAP 20 -22 AIM
// 
//    Rev 1.233   23 Jul 2007 16:49:52   popescu
// PET 2360 - FN 20 - GAP 20 Soft cap functionality
// 
//    Rev 1.232   May 04 2007 13:58:02   jankovii
// PET 2321 FN01 - MT54X Default Pay Type.
// 
//    Rev 1.231   Nov 24 2006 18:06:04   popescu
// Incident# 726814 - defaulted the lsifcode to '0' for env. that suport lsif funds - to catch the full redemptions
// 
//    Rev 1.230   Nov 24 2006 17:29:02   ZHANGCEL
// Incident #765688 -- Fix but related with Death Date validation
// 
//    Rev 1.229   Nov 24 2006 17:26:14   ZHANGCEL
// Incident #765688 -- Fix bug for Death Date validation issue. 
// 
//    Rev 1.228   Oct 30 2006 17:04:32   jankovii
// PET 2185 FN04 - Trade restrictions.
// 
//    Rev 1.227   Oct 19 2006 16:06:58   popescu
// Incident# 699545 - validation for RedCode = 02 applied to Free/Non Age amount type
// 
//    Rev 1.226   Oct 19 2006 15:34:38   popescu
// Incident# 722294 - users will be able to override the trade payment instructions with system cheque
// 
//    Rev 1.225   Oct 13 2006 15:05:56   ZHANGCEL
// Incident #697014 -- Fix Death redemtion issue
// 
//    Rev 1.224   Sep 12 2006 10:53:02   popescu
// STP - PET 2192/11
// 
//    Rev 1.223   Sep 10 2006 17:59:50   popescu
// STP 2192/12
// 
//    Rev 1.222   Sep 07 2006 21:38:04   popescu
// STP 2192/02
// 
//    Rev 1.221   Aug 29 2006 18:15:54   popescu
// STP PET 2192 FN10/11 - bulking netting redemption
// 
//    Rev 1.220   Jul 24 2006 15:17:04   porteanm
// Incident 650931 - Added ERR_ILLEGAL_REDEMPTION_CODE_FOR_ACCT_TAX_TYPE.
// 
//    Rev 1.219   Jun 09 2006 14:44:22   popescu
// Incident# 640084 - Added edit check where user cannot place a redemption if redemption code is 02 - Close Account and amount type is all free units.
// 
//    Rev 1.218   May 23 2006 15:19:46   ZHANGCEL
// Incident # 624726 -- Remove ESGSettle from redemptionAttributeSubstList if the Market is Lux
// 
//    Rev 1.217   Apr 06 2006 10:42:50   jankovii
// PET 1334 Alternative Product. If view 135 returns and error still initalize data.
// 
//    Rev 1.216   Feb 28 2006 11:20:28   popescu
// /Incident# 554580 - remove current validation for SWIFT monetary amount trades
// 
//    Rev 1.215   Feb 20 2006 13:03:34   ZHANGCEL
// PET 1334 - FN1 -- Added new function for the ESG Settlement enhancement
// 
//    Rev 1.214   Jan 12 2006 13:48:16   AGUILAAM
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files - Trade Entry/Rebook/Trans History
// 
//    Rev 1.213   Nov 19 2005 15:52:18   popescu
// BPS Performance issue - cached view call 20 and passed params fund/class in as params
// 
//    Rev 1.212   Oct 25 2005 18:42:00   porteanm
// Incident 438377 - Source of Fund for RRIF rebooking.
// 
//    Rev 1.211   Sep 20 2005 12:15:22   AGUILAAM
// PET1250_FN09_Custody Client Accounts and Negative Balances; also fixed Refresh functionality for Settlements.
// 
//    Rev 1.210   Jul 14 2005 15:29:24   popescu
// Incident 356593 - fix trade crash if default allocations/ams are available for an account, when placing redemptions/purchases/transfers
// 
//    Rev 1.209   Jul 14 2005 15:26:22   porteanm
// PET1171 EUSD 1B - Req change - remove  validateEUSDBackDates() call.
// 
//    Rev 1.208   Jul 11 2005 17:24:00   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.207   Jul 07 2005 11:34:00   porteanm
// PET1171 EUSD 1B - Call validateEUSDBackDates().
// 
//    Rev 1.206   Jun 29 2005 11:56:46   popescu
// Incident# 342270 - guard the refresh of split commissions with a boolean for fund related changes; save several view calls to 158
// 
//    Rev 1.205   Jun 22 2005 14:08:56   popescu
// PET 1117/08 - renamed method activestRelatedChanges to thirdPartyFundRelatedChanges
// 
//    Rev 1.204   Jun 17 2005 19:28:18   popescu
// Incident#273734 - settlement currency automatically assigned if all funds held by account are in the same currency. 
// User stoped from placing a EFT Full Redemption (no fund, zero amount) if the account has non zero holding on funds with different currency.
// 
//    Rev 1.203   Jun 16 2005 19:00:50   popescu
// Incident# 323484 - added Delivery Method field to attribute box on the trade entry screen
// 
//    Rev 1.202   May 11 2005 16:32:08   porteanm
// PET1203 FN05 - Class B NAV Share Lots.
// 
//    Rev 1.201   May 02 2005 11:54:28   porteanm
// Incident 290690 - Source Of Fund.
// 
//    Rev 1.200   Apr 26 2005 17:11:16   popescu
// Incident# 262582 - invalidate amount type and order type if red code changes - validation should be triggered
// 
//    Rev 1.199   Apr 12 2005 10:32:30   porteanm
// PET1190 FN14 - Wire order redemption against unsettled units.
// 
//    Rev 1.198   Mar 29 2005 18:08:04   popescu
// Incident# 273841, missed requirment, set the other confirm type to 1-Create PUEV note if fund and account are PUEV capable for an Investro network id.
// 
//    Rev 1.197   Mar 24 2005 12:44:46   popescu
// Incident# 271131, open up address field for redemptions with suppress/manual cheque pay type , synch-up from release 59
// 
//    Rev 1.196   Mar 10 2005 12:36:46   porteanm
// Incident 243157/243387 - Settle Source validation.
// 
//    Rev 1.195   Mar 08 2005 17:49:16   popescu
// PET 1117/06, checked the read permission for order type, synch-up from rel 59
// 
//    Rev 1.194   Feb 16 2005 13:36:36   aguilaam
// incident # 243397 - sync-up from Rel59; moved initialization of LSIFCode for money-out on LSIF funds from Redemption.cpp to Trade.cpp
// 
//    Rev 1.193   Feb 01 2005 11:45:08   popescu
// PET 1117/66/67/68, API validations for SWIFT/Investro/Pwld
// 
//    Rev 1.192   Jan 20 2005 17:49:08   popescu
// PTS 10032958, ensured that the settle source validation is triggered by invalidating the 'SettleSource' field if order type is set to Wire, also fixed a typo.
// 
//    Rev 1.191   Jan 04 2005 17:10:58   popescu
// PTS 10037456, consider deposit 9 and 10 -bearer certificate when setting the default values for aggregate option
// 
//    Rev 1.190   Dec 31 2004 13:38:20   popescu
// PTS 10037395, settlement currency should be set as required if for redemption the account closes or a full redemption is processed. Also, isFullNotCloseAcctRed method name to isFullRedemption
// 
//    Rev 1.189   Dec 30 2004 12:41:18   popescu
// PTS 10037260, moved check whether fund sponsor fee model  exists at Trade CBO level, and called the validation for redemptions/purchases as well, missed req: PET1117.FN6.R3.7. 0
// 
//    Rev 1.188   Dec 30 2004 10:45:50   popescu
// PTS 10036944, added adtional restrictions for updating the order type field. System checks generic control UpdOrdType and user permission for update controlled by ids 46  for purchases and 45 for redemptions.
// 
//    Rev 1.187   Dec 29 2004 11:22:10   popescu
// PTS 10037302, do not validate amount precision for amount type units
// 
//    Rev 1.186   Dec 22 2004 12:07:08   popescu
// PTS 10036944, open-up field OrderType
// 
//    Rev 1.185   Dec 17 2004 17:33:54   popescu
// PET 1117/56, set the value of AcqFeeOption to '2' buy at NAV
// 
//    Rev 1.184   Dec 16 2004 12:15:08   popescu
// PET 1117/06/56, fixed allocations issues for transfers in pending mode, also set of a settle curr if DefSettleCurr-83 is N
// 
//    Rev 1.183   Dec 15 2004 16:59:32   popescu
// PET 1117/06, quick fix for settlement currency default
// 
//    Rev 1.182   Dec 13 2004 14:18:32   popescu
// PET 1117/56, SuppressCode should follow the base class login if paytype is not clearing
// 
//    Rev 1.181   Dec 11 2004 11:47:38   popescu
// PET 1117/56 more fixes, pending trade mods
// 
//    Rev 1.180   Dec 07 2004 21:20:28   popescu
// PET 1117/06, pending trades/fees fixes, add-ons
// 
//    Rev 1.179   Dec 07 2004 01:37:42   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.178   Dec 02 2004 18:23:00   popescu
// PET 1117/06/56, trades processing/fees processing
// 
//    Rev 1.177   Dec 01 2004 15:44:48   popescu
// PET 1117/56 fees processing, calculate the discount rate
// 
//    Rev 1.176   Nov 30 2004 20:10:00   popescu
// PET 1117/06
// 
//    Rev 1.175   Nov 29 2004 20:51:58   popescu
// PTS 10035296, check fund balance only if fund/class are not empty. Force a check in to catch the ticket in the PTS tracking database
// 
//    Rev 1.174   Nov 29 2004 20:30:28   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.173   Nov 27 2004 21:19:02   popescu
// PET 1117/06, trades processing
// 
//    Rev 1.172   Nov 25 2004 14:59:06   popescu
// PET 1117/06, settle locations
// 
//    Rev 1.171   Nov 24 2004 21:36:06   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.170   Nov 22 2004 13:09:22   popescu
// PET 1117/56. fees processing
// 
//    Rev 1.169   Nov 19 2004 14:17:22   popescu
// PET 1117/56 third party processing
// 
//    Rev 1.168   Nov 15 2004 17:33:18   popescu
// PTS 10032958, added extra condition for rule 3, validateSettleSource (orderType == Y)
// 
//    Rev 1.167   Nov 15 2004 16:23:26   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.166   Nov 14 2004 14:51:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.165   Nov 09 2004 18:47:36   popescu
// PTS 10032958, added extra condition for rule 3, validateSettleSource
// 
//    Rev 1.164   Nov 06 2004 00:42:18   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.6   Nov 04 2004 17:38:22   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.5   Nov 02 2004 19:19:32   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.4   Oct 28 2004 18:23:50   popescu
// PET 1117/06
// 
//    Rev 1.3   Oct 27 2004 11:26:58   popescu
// PET 1117/06
// 
//    Rev 1.2   Oct 22 2004 19:58:50   popescu
// PET 1117/06, work in progress...
// 
//    Rev 1.1   Oct 21 2004 06:29:14   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.0   Oct 01 2004 19:29:54   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
