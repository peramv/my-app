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
// ^FILE   : Purchase.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : Purchase - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "purchase.hpp"

#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "agent.hpp"
#include "amsmstrinfo.hpp"
#include "amsmstrlist.hpp"
#include "bankinstructions.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "funddetail.hpp"
#include "fundlmtoverride.hpp"
#include "fundlmtoverridelist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "fundsponsorfeemodel.hpp"
#include "fundsponsorfeemodellist.hpp"
#include "fundtranstype.hpp"
#include "fundtranstypelist.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "redcodebytaxtype.hpp"
#include "redcodebytaxtypelist.hpp"
#include "segtradeentryvalidation.hpp"
#include "shareholder.hpp"
#include "splitcommission.hpp"
#include "taxtyperule.hpp"
#include "tradebankinstructionslist.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include "trademinamtcheck.hpp"
#include "translationtable.hpp"
#include "funddetaillist.hpp"

#include "DefaultSysConfigDetailList.hpp"
//deposit id validation
#include <ifastdataimpl\dse_dstc0147_req.hpp>
#include <ifastdataimpl\dse_dstc0147_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0436_vw.hpp>

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_trading_on_child_fnd_cls_not_allowed.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_trading_on_child_fnd_cls_not_allowed.h>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("Purchase");
   const I_CHAR * const BEARERCERTCODELIST          = I_("9,10");    // Bearer Certificate Code List
   const I_CHAR * const TFSA_TAX_TYPE               = I_("V");
   const I_CHAR * const EXTERNAL_TFSA_TAX_TYPE      = I_("Z");
   const I_CHAR * const MARRIAGE_BREAKDOWN          = I_("52");;
   const I_CHAR * const PURCHASE_TPA_FEE            = I_("212");;
   const I_CHAR * const RESP_TAX_TYPES              = I_("9,M");;
   const I_CHAR * const RESP_BENEFALLOC_DEPOSIT     = I_("1,2");;
   const I_CHAR * const RESP_TRANSFER_DEPOSIT       = I_("17");;
   const I_CHAR * const DEPTYPE_ADDITNL_CESG_GRANT  = I_("73");
   const I_CHAR * const DEPTYPE_CLB                 = I_("74");
   const I_CHAR * const DEPTYPE_CLB_ADMIN           = I_("75");
   const I_CHAR * const DEPTYPE_ACES                = I_("76");
   const I_CHAR * const DEPTYPE_SAGES_GRANT_PAYMENT = I_("35");
   const I_CHAR * const ENTITY_ANNUITANT            = I_("05");
   const I_CHAR * const EMPLOYEE                    = I_("08");
   const I_CHAR * const AGENT                       = I_("09");
   const I_CHAR * const CLIENT                      = I_("1");
   const I_CHAR * const EA_BONUS_PURSHASE           = I_("64");
   const I_CHAR * const NO                          = I_("N");
   const I_CHAR * const YES                         = I_("Y");
   const I_CHAR * const PAC                         = I_("2");
   const I_CHAR * const RDSP_TAX_TYPE				= I_("RS");
   const I_CHAR * const EXTERNAL_RDSP_TRANSFER_IN	= I_("67");
}

namespace ifds
{
//management company options
   extern CLASS_IMPORT const BFTextFieldId DefaultPurchPayType;
   extern CLASS_IMPORT const BFTextFieldId EFTPurchase;
   extern CLASS_IMPORT const BFTextFieldId ACHPurch;
   extern CLASS_IMPORT const BFTextFieldId DefaultAllocOverride;
   extern CLASS_IMPORT const BFTextFieldId AllowFractions;
   extern CLASS_IMPORT const BFTextFieldId DepositId2;
   extern CLASS_IMPORT const BFTextFieldId EditDeffs;
   extern CLASS_IMPORT const BFTextFieldId CashReceiptTrack;
   extern CLASS_IMPORT const BFTextFieldId AllowUnitsPurchase;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrEFTUnitPurch;
   extern CLASS_IMPORT const BFTextFieldId DisAllowPayTypeUnitPurch;
   extern CLASS_IMPORT const BFTextFieldId GrpContribution;
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
   extern CLASS_IMPORT const BFTextFieldId ErrorAcctNum;
   extern CLASS_IMPORT const BFTextFieldId ADLevyFee;
   extern CLASS_IMPORT const BFTextFieldId ADLevyFeeTransType;
   extern CLASS_IMPORT const BFTextFieldId AntiDilutionCalc;
   extern CLASS_IMPORT const BFTextFieldId UpdOrdType;
   extern CLASS_IMPORT const BFTextFieldId NetworkTypeUpd;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
//account fields
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId SiblingOnly;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId StopCommissionRebate;
   extern CLASS_IMPORT const BFTextFieldId FundType;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId UnitsCal;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundCurrency;
//substitution sets
   extern CLASS_IMPORT const BFTextFieldId PurchaseSourceOfFund;
   extern CLASS_IMPORT const BFTextFieldId PurchasePayType;
//attributes grid
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesFields;
   extern CLASS_IMPORT const BFTextFieldId PurchaseAttributes;
//unrelated fields
   extern CLASS_IMPORT const BFTextFieldId MaximumApplies;
   extern CLASS_IMPORT const BFTextFieldId DTAEligible;
   extern CLASS_IMPORT const BFTextFieldId DepValid;
   extern CLASS_IMPORT const BFTextFieldId DepClosed;
   extern CLASS_IMPORT const BFTextFieldId Initial;
   extern CLASS_IMPORT const BFTextFieldId InitPurch;
   extern CLASS_IMPORT const BFTextFieldId FeeModelOption;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
//cross-edits
   extern CLASS_IMPORT const BFTextFieldId AmtTypeSettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId AmtTypePayType;
   extern CLASS_IMPORT const BFTextFieldId LevelGroup;
   extern CLASS_IMPORT const BFTextFieldId NetOrdType;
   extern CLASS_IMPORT const BFTextFieldId WireOrdFndCls;
   extern CLASS_IMPORT const BFTextFieldId IncvActive;
   extern CLASS_IMPORT const BFTextFieldId IncvBasedOn;
   extern CLASS_IMPORT const BFTextFieldId JumboPriceApplicable;
   extern CLASS_IMPORT const BFTextFieldId FromFundClass; 
   extern CLASS_IMPORT const BFDecimalFieldId RESPPCGId;
   extern CLASS_IMPORT const BFTextFieldId AmountType;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
   extern CLASS_IMPORT const BFTextFieldId PaymentInfo;
   extern CLASS_IMPORT const BFTextFieldId FundRelnCode;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA_ED;  //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA;
   extern CLASS_IMPORT const BFTextFieldId RightToCancelDefault; 
   extern CLASS_IMPORT const BFTextFieldId RightToCancel; 
   extern CLASS_IMPORT const BFTextFieldId TimeFactor;
   extern CLASS_IMPORT const BFTextFieldId ScreenActivityType;
   extern CLASS_IMPORT const BFTextFieldId PSDAdvice;
   extern CLASS_IMPORT const BFTextFieldId AWDFieldFlag;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId AssocFund;
   extern CLASS_IMPORT const BFTextFieldId AssocClass;
   extern CLASS_IMPORT const BFTextFieldId FromSoftCapCheck;
   extern CLASS_IMPORT const BFTextFieldId TrackTrActive;
   extern CLASS_IMPORT const BFTextFieldId TrackTrDepCode;
   extern CLASS_IMPORT const BFTextFieldId PriceTypes;
}

namespace CND
{
   extern const long ERR_NET_NOT_FOR_BEL_FUND;
   extern const long ERR_DEPOSIT_TYPE_23_NOT_SUPPORT;
   extern const long ERR_COMMISSION_REBATE_NOT_ALLOWED_FOR_THIS_FUND;
   extern const long ERR_INVALID_AMOUNT_CODE_FOR_LLP_REPAYMENT;
   extern const long ERR_FUND_CANNOT_BE_BLANK_FOR_BEARER_CERTIFICATE;
   extern const long ERR_ONLY_UNIT_ALLOW_FOR_BEARER_CERTIFICATE;
   extern const long ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS;
   extern const long ERR_CANSIM_NOT_EXISTS;
   extern const long ERR_DTA_NOT_ALLOWED_FOR_THIS_DEPOSITTYPE;
   extern const long ERR_DEPOSIT_ID_CLOSED;
   extern const long ERR_DEPOSIT_ID_INVALID;
   extern const long ERR_INVALID_EFFECTIVE_DATE;
   extern const long ERR_UNIT_PURCHASE_NOT_ALLOWED;
   extern const long ERR_EFT_IN_UNITS_NOT_FOR_PURCHASE;
   extern const long ERR_FUNDCLASS_SETTLE_CURRENCY_DIFFERENT;
   extern const long ERR_NET_UNIT_PURCHASE_NOT_ALLOWED;
   extern const long ERR_FUND_CLASS_MUST_BE_SPECIFIED;
   extern const long ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_PURCHASE_STOP_FLAG_ON;
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_MAXIMUM_INPUT_AMT;
   extern const long ERR_AMOUNT_IS_LESS_THEN_MINIMUM_REQUIRED;
   extern const long WARN_AMOUNT_IS_LESS_THEN_MINIMUM_REQUIRED;
   extern const long ERR_ACQ_FEE_OPTION_NOT_APPLICABLE_FOR_ADL_ENV;
   extern const long ERR_ACQ_FEE_OPTION_ONLY_APPLICABLE_FOR_3RD_PARTY_FUNDS;
   extern const long ERR_REGULAR_ACQ_FEE_OPTION_DOES_NOT_APPLY;
   extern const long WARN_FEE_MODEL_OVERRIDDEN;
   extern CLASS_IMPORT const long ERR_FNDSPONSOR_FEEMODEL_DOES_NOT_EXIST;
   extern const long WARN_PURC_RESP_NOT_SUPPORTED;
   extern const long WARN_PURCHASE_NON_BELL_FOR_DEPOSIT_27;
   extern const long ERR_PURCH_NAV_ACCT_BEL_FUND_NAV_DEPOSIT_TYPE;
   extern const long ERR_PURCHASE_INVALID_DEPOSIT_TYPE_FOR_ALLOC;
   extern const long ERR_JUMBO_PRICE_NOT_APPLICABLE;
   extern const long ERR_FEE_OPTION_DOSE_NOT_APPLY;   
   extern const long ERR_CASH_TRADE_NOT_ALLOWED_FOR_TAX_TYPE;
   extern const long ERR_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS;
   extern const long WARN_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS;
   extern const long ERR_BENEFICIARY_IS_NOT_LINKED_TO_PCG;
   extern const long WARN_BENEFICIARY_IS_NOT_LINKED_TO_PCG;
   extern const long ERR_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern const long WARN_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern const long ERR_REDIRECT_TO_PAY_ENTITY_NOT_ALLOWED;
   extern const long EFT_PURCHASE_NOT_APPLICABLE_ALLOC_TRADE;
   extern const long ERR_DOD_ENTITY_TYPE_MISSING;
   extern const long WARN_DOD_ENTITY_TYPE_MISSING;
   extern const long ERR_PAYMENT_STATUS_IS_OUTSTANDING;
   extern const long WARN_PAYMENT_STATUS_IS_OUTSTANDING;
   extern const long ERR_PAYMENT_STATUS_EMPTY;
   extern const long WARN_PAYMENT_STATUS_EMPTY;
   extern const long ERR_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT;
   extern const long WARN_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT;
   extern const long ERR_CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern const long WARN_CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern const long ERR_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
   extern const long WARN_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
	//P0186486FN09 - Employee and Agent Account Gap#8A
   extern const long ERR_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS;
   extern const long WARN_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS;
   extern const long ERR_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT;
   extern const long WARN_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT;
   extern const long ERR_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL;
   extern const long WARN_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL;
   extern const long ERR_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS;
   extern const long WARN_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS;
   extern const long WARN_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
   extern const long ERR_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
   extern const long ERR_DIF_FUND_ONLY_ALLOW_DIRECT_ORDER;
   extern const long WARN_DIF_FUND_ONLY_ALLOW_DIRECT_ORDER;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS;
   extern CLASS_IMPORT I_CHAR * const BENEFICIARY_IS_NOT_LINKED_TO_PCG;
   extern CLASS_IMPORT I_CHAR * const SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const DOD_ENTITY_TYPE_MISSING;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_STATUS_EMPTY;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_STATUS_IS_OUTSTANDING;
   extern CLASS_IMPORT I_CHAR * const ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const CONTRACT_TYPE_AND_VERSION_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT;
   //P0186486FN09 - Employee and Agent Account Gap#8A
   extern CLASS_IMPORT I_CHAR * const CHANGE_REPS_IS_NOT_APPLICABLE;
   extern CLASS_IMPORT I_CHAR * const EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS;
   extern CLASS_IMPORT I_CHAR * const EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT;
   extern CLASS_IMPORT I_CHAR * const PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL;
   extern CLASS_IMPORT I_CHAR * const CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
   extern CLASS_IMPORT I_CHAR * const TRADING_ON_CHILD_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
   extern CLASS_IMPORT I_CHAR * const DIF_FUND_ONLY_ALLOW_DIRECT_ORDER;
}
namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_IN;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const EFT;
   extern CLASS_IMPORT I_CHAR * const CASH;
   extern CLASS_IMPORT I_CHAR * const DIRECT;
   extern CLASS_IMPORT I_CHAR * const CLEARING;
} 

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING_TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const AMS_MIX_OVERRIDE;
   extern CLASS_IMPORT I_CHAR * const UPD_ORD_TYPE_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const SOURCE_OF_FUNDS_CHECKED;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT_PURCHASE;
   extern const I_CHAR * const ALT_EFT_PURCHASE;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEPOSIT;
}
namespace DATE_VALIDATION
{
	extern const I_CHAR * const TRADE_DATE;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
  //Field DD Id,              State Flags,      Group Flags 
   { ifds::AmtTypeSettleCurrency,      BFCBO::IMMEDIATE_VALIDATION,  0 },
   { ifds::AmtTypePayType,             BFCBO::IMMEDIATE_VALIDATION,  0 },
   { ifds::LevelGroup,                 BFCBO::IMMEDIATE_VALIDATION,  0 },
   { ifds::ScreenActivityType,		   BFCBO::CALCULATED_FIELD,		 0 },
};
const FIELD_DEFAULT_RULE m_FieldDefaultRule[] = { 
// FieldID,			Key1,				key2,			  Key3,			    Key4,					 Key5,					MODE

{ifds::PSDAdvice, ifds::Platform, ifds::SourceOfTrade, ifds::ChannelOfTrade, ifds::ScreenActivityType, ifds::TimeFactor, MODE_INIT | MODE_REBOOK },

};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
static const int _numFieldDefaultRule = sizeof(m_FieldDefaultRule) / sizeof(FIELD_DEFAULT_RULE);

//******************************************************************************
Purchase::Purchase (BFAbstractCBO &parent) : Trade (parent),
_defaultFeeModelOption (NULL_STRING)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,NULL);

   addCrossEdit (ifds::AmtTypeSettleCurrency, ifds::AmtType); 
   addCrossEdit (ifds::AmtTypeSettleCurrency, ifds::SettleCurrency); 

   addCrossEdit (ifds::AmtTypePayType, ifds::AmtType); 
   addCrossEdit (ifds::AmtTypePayType, ifds::TradesPayType); 
// to validate borrowed funds
   addCrossEdit (ifds::LevelGroup, ifds::SlsrepCode);
   addCrossEdit (ifds::LevelGroup, ifds::BorrowedFunds);
}


//******************************************************************************
Purchase::~Purchase ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY Purchase::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::PURCHASE, 
                        idDataGroup, 
                        false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Purchase::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool Purchase::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool Purchase::isSettleLocAllowed (const BFDataGroupId &idDataGroup)
{
   bool bIsClearingAcct = false;
   MFAccount *pMFAccount = NULL;   

   if ( getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING  && 
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
bool Purchase::areMultipleSettleLocAllowed (const BFDataGroupId &idDataGroup)
{
   DString settleLocOpt;
   DString payType;

   getWorkSession ().getOption (ifds::SettleLocOpt, settleLocOpt, idDataGroup,  false);
   getField (ifds::TradesPayType, payType, idDataGroup, false);

   return settleLocOpt == I_("2") && payType != PAYTYPE::CLEARING && !payType.empty ();
}

//GIA-INA
//******************************************************************************
bool Purchase::isGIAAttribAllowed (const BFDataGroupId &idDataGroup)
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
bool Purchase::isMaturityInstrAllowed (const BFDataGroupId &idDataGroup)
{
   bool isMaturityInstrAllowed = false;
   DString fundCode;
   
   getField (ifds::FromFund, fundCode, idDataGroup, false);

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
void Purchase::getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                         BFFieldId &classCodeFieldId)
{
   fundCodeFieldId = ifds::FromFund;
   classCodeFieldId = ifds::FromClass;
}

//******************************************************************************
void Purchase::getPurchaseFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                                 BFFieldId &classCodeFieldId)
{
   fundCodeFieldId = ifds::FromFund;
   classCodeFieldId = ifds::FromClass;
}

//******************************************************************************
void Purchase::getAccountFieldId (BFFieldId &accountFieldId)
{
   accountFieldId = ifds::AccountNum;
}

//******************************************************************************
void Purchase::getPurchaseAccountFieldId (BFFieldId &accountFieldId)
{
   accountFieldId = ifds::AccountNum;
}

//******************************************************************************
SEVERITY Purchase::getPurchaseFundField ( const BFFieldId &idField, 
                                          DString &strValue,
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getPurchaseFundField"));
   DString fundCode, 
      classCode;
   BFFieldId fundFieldId (ifds::NullFieldId),
      classFieldId (ifds::NullFieldId);

   strValue = NULL_STRING;
   getPurchaseFundAndClassFieldIds (fundFieldId, classFieldId);
   getField (fundFieldId, fundCode, idDataGroup, false);
   getField (classFieldId, classCode, idDataGroup, false);
   if ( !fundCode.empty() &&
        !classCode.empty()) 
   {
      Trade::getFundField (fundCode, classCode, idField, strValue);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::getPurchaseAccountField ( const BFFieldId &idField, 
                                             DString &strValue,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAccountField"));
   DString accountNum;
   
   BFFieldId accountNumFieldId (ifds::NullFieldId);

   strValue = NULL_STRING;
   getPurchaseAccountFieldId (accountNumFieldId);
   getField (accountNumFieldId, accountNum, idDataGroup, false);
   if (!accountNum.empty()) 
   {
      Trade::getAccountField (idField, strValue, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::getPurchaseAccount ( MFAccount *&pMFAccount, 
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getPurchaseAccount"));
   DString accountNum;
   pMFAccount = NULL;

   getPurchaseAccountField (ifds::AccountNum, accountNum, idDataGroup);
   if (!accountNum.empty()) 
   {      
      getWorkSession ().getMFAccount (idDataGroup, accountNum, pMFAccount);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
//base class call   
   Trade::preInitWithDefaultValues (idDataGroup);

//purchase pay type
   DString purchasePayTypeSubstList,
      eftPurchaseFlag;
   BFProperties *pBFPropertiesPPT = 
      getFieldProperties (ifds::PurchasePayType, idDataGroup);

   assert (pBFPropertiesPPT);
   if (pBFPropertiesPPT)
   {
      pBFPropertiesPPT->getAllSubstituteValues (purchasePayTypeSubstList);
      if (!getWorkSession ().
            hasCreatePermission (UAF::DIRECT_TRADING_TRANSACTION)) //remove direct trading pay type
      {
         purchasePayTypeSubstList = 
            removeItemFromSubtList (purchasePayTypeSubstList, PAYTYPE::DIRECT);
      }

      DString eftPurchase;

      getWorkSession ().getOption ( ifds::EFTPurchase, 
                                    eftPurchase, 
                                    BF::HOST,
                                    false);
      if (eftPurchase == I_("N")) //remove eft purchase pay type
      {
         purchasePayTypeSubstList = 
            removeItemFromSubtList (purchasePayTypeSubstList, PAYTYPE::EFT);

         DString payType;

         getField (ifds::TradesPayType, payType, idDataGroup, false);
         if (payType == PAYTYPE::EFT && !_bInitPending)
         {
//if eft purchase is not allowed, but the trade default for pay type is incorrect 
//set to 'E', then let the user decide what default is appropriate.
            setFieldNoValidate (ifds::TradesPayType, NULL_STRING, idDataGroup, false);
            setFieldValid (ifds::TradesPayType, idDataGroup, false); //forces validation
         }
      }
      setFieldAllSubstituteValues (ifds::TradesPayType, idDataGroup, purchasePayTypeSubstList);
   }
//purchase source of fund		   
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
         DString dstrPurchaseSrcOfFundCodeList;
         pTranslationTable->getPurchaseSrcOfFundCodeList( dstrPurchaseSrcOfFundCodeList );

         // Intended for pending/rebooked PAC
         DString dstrDepositType;
         getField( ifds::DepositType, dstrDepositType, idDataGroup );
         dstrDepositType.stripAll();
         if ( ( (_bInitPending || isRebook() )&& 
            I_( "2" ) == dstrDepositType ) )   // 2 PAC
         {
            DString dstrSourceOfFund;
            getField( ifds::SrcOfFund, dstrSourceOfFund, idDataGroup );
            if ( !DSTCommonFunctions::codeInList( dstrSourceOfFund, dstrPurchaseSrcOfFundCodeList ) )				
               dstrPurchaseSrcOfFundCodeList += dstrSourceOfFund + I_(","); 
         }

         loadSubstitutionList( ifds::SrcOfFund, 
            idDataGroup,
            dstrPurchaseSrcOfFundCodeList );
      }
   }
   
   DString updOrdType, accountNum, depositType;

   getWorkSession ().getOption ( ifds::UpdOrdType, 
                                 updOrdType, 
                                 BF::HOST,
                                 false) ;
   setFieldReadOnly ( ifds::OrderType, idDataGroup, 
      !getWorkSession().hasReadPermission (UAF::UPD_ORD_TYPE_PURCHASE) || updOrdType != Y);
   loadNetworkIDValues (idDataGroup);
   
   setFieldReadOnly ( ifds::ValueDate,idDataGroup,true);
  
   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   getField (ifds::DepositType, depositType, idDataGroup, false);

   bool bIsRDSPGrantOrBond = (isRDSPTradeAccount (idDataGroup, accountNum) && DSTCommonFunctions::codeInList (depositType, I_("49,66"))) ? true : false; // 49-RDSP Grant, 66-RDSP Bond  

   setFieldReadOnly (ifds::RDSPPaymtDate, idDataGroup, !bIsRDSPGrantOrBond);
  
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Purchase::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
//call base class
   Trade::doInitWithDefaultValues (idDataGroup);
   setFieldRequired (ifds::AcqFeeOption, idDataGroup, true);
   setFieldValid (ifds::Amount, idDataGroup, false); 
    
   loadPaymentStatusSubstList (idDataGroup);
   setFieldNoValidate (ifds::PaymentInfo, NULL_STRING, idDataGroup, false);	
   setFieldReadOnly ( ifds::PaymentInfo, idDataGroup, true);

   
   DString RgtToCancelDefault;
   getWorkSession ().getOption (ifds::RightToCancelDefault, RgtToCancelDefault, idDataGroup,  false);
   RgtToCancelDefault.stripAll();
   RightToCancelRelatedChanges (RgtToCancelDefault, idDataGroup);   
   DString dstrPSDAdvice;
   getWorkSession ().getOption (ifds::PSDAdvice, dstrPSDAdvice, idDataGroup,  false);
   dstrPSDAdvice.stripAll();
   setFieldNoValidate(ifds::ScreenActivityType, I_("T"), idDataGroup); 
   populateFieldsWithDefaultValues(idDataGroup, MODE_INIT);
   setFieldReadOnly (ifds::PSDAdvice, idDataGroup,  NO == dstrPSDAdvice.stripAll());
   addBlankToSubSet( ifds::SourceofFundsChecked, idDataGroup, true);
   setFieldNoValidate( ifds::SourceofFundsChecked, NULL_STRING, idDataGroup, false);   
   setSourceOfFundsChecked(idDataGroup);  
}

//******************************************************************************
SEVERITY Purchase::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges"));
   DString purchaseAttributeSubstList;

   BFProperties *pBFProperties = 
      getFieldProperties (ifds::PurchaseAttributes, idDataGroup);
   
   pBFProperties->getAllSubstituteValues (purchaseAttributeSubstList);

   if (!isROATransType (idDataGroup))
   {
      purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("ROAAmount"));
   
   }
   if (!isACHApplicable (idDataGroup))
   {
      purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("PayMethod"));
      purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("FileProcessor"));
   }

   if (!isMCHSecRecIndApplicable (idDataGroup))
   {
      purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("MCHFileIndicator"));
      purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("SecRecFileIndicator"));
   }

   DString networkTypeUpd;

   getWorkSession().getOption ( ifds::NetworkTypeUpd,
                                networkTypeUpd,
                                BF::HOST,
                                false);
   if (networkTypeUpd == N)
   {
      purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("NetworkID"));
      purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("SendRefNum"));
     purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("DeliveryNetwork"));
   }
   if( ! isNetworkRespReqApplicable() ) 
   {
      purchaseAttributeSubstList = 
         removeItemFromSubtList ( purchaseAttributeSubstList, 
                                  I_("NetworkRespRequired"));
   }

   DString dstrTransType;
   
   getField( ifds::TradesTransType, dstrTransType, idDataGroup );
   if( TRADETYPE::CROSS_SYSTEM_TRANSFER_IN != dstrTransType )
   {
      purchaseAttributeSubstList = removeItemFromSubtList ( purchaseAttributeSubstList,  
                                                            I_("CrossSysAcctNum"));
   }

	if (dstrTransType != TRADETYPE::PURCHASE)
	{
      purchaseAttributeSubstList = 
            removeItemFromSubtList ( purchaseAttributeSubstList, 
                                     I_("ExternalInstitution"));
	}
   //attributes grid
   setFieldAllSubstituteValues ( ifds::TradeAttributesFields, 
                                 idDataGroup, 
                                 purchaseAttributeSubstList);

   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Purchase::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   Trade::doInit (data);
   DString accountNum;

   getField (ifds::AccountNum, accountNum, BF::HOST, false);
   loadDepRedCodeSubstList ( accountNum, 
                             I_("D"),  //deposit type
                             BF::HOST
                           );
   amsAccountRelatedChanges (BF::HOST);
/* commented out as of incident #251618
//should check whether account has a fee model; if yes do not include the 'Regular' option for
//the acquisition fee option field
   DString feeModelCode;

   if ( getFeeModelCode (accountNum, feeModelCode, BF::HOST) <= WARNING && 
        !feeModelCode.empty()) 
   {
      DString acqFeeOptionSubstList;

      BFProperties *pBFProperties = 
         getFieldProperties (ifds::AcqFeeOption, BF::HOST);
      
      pBFProperties->getAllSubstituteValues (acqFeeOptionSubstList);
      acqFeeOptionSubstList = 
         removeItemFromSubtList ( acqFeeOptionSubstList, 
                                  I_("0")); //remove 'Regular'
      setFieldAllSubstituteValues (ifds::AcqFeeOption, BF::HOST, acqFeeOptionSubstList);
   }
*/
   acqFeeOptionDefault (BF::HOST);
   thirdPartyFundRelatedChanges (BF::HOST);

   DString dstrFundCode, dstrClassCode,
          dstrLoadType, dstrDepositType;
   getPurchaseFundField( ifds::FundCode,    dstrFundCode,    BF::HOST );
   getPurchaseFundField( ifds::ClassCode,   dstrClassCode,   BF::HOST );
   getPurchaseFundField( ifds::LoadType,    dstrLoadType,    BF::HOST );
   getField( ifds::DepositType, dstrDepositType, BF::HOST );
   if ( accountHasCategory( I_( "11" ), BF::HOST ) &&
        !dstrFundCode.empty() &&
        !dstrClassCode.empty() &&
        dstrLoadType.strip().upperCase() == I_("BEL") &&
        dstrDepositType == I_( "27" ) )
   {
      setFieldReadOnly( ifds::DepositType, BF::HOST, true );
   }

   bool bFeeApplicable;
   isFeeApplicable (PURCHASE_TPA_FEE, bFeeApplicable, BF::HOST);

   if (bFeeApplicable)
   {
      setFieldNoValidate (ifds::GrossOrNet, Y, BF::HOST, false, true, true);
      setFieldReadOnly (ifds::GrossOrNet, BF::HOST, true);
   }
   DString depositType;
   getField(ifds::DepositType, depositType, BF::HOST, false);
   depositType.strip();

   if (DSTCommonFunctions::codeInList (depositType, I_("77,78,79,80,81,94"))) 
      setFieldReadOnly (ifds::RESPContrDetlTaxYear, BF::HOST, false);
   else
      setFieldReadOnly (ifds::RESPContrDetlTaxYear, BF::HOST, true);
   
   if(DSTCommonFunctions::codeInList (depositType, I_("78,79")))
      setFieldReadOnly (ifds::AssistedContrAmt, BF::HOST, false);
   else
      setFieldReadOnly (ifds::AssistedContrAmt, BF::HOST, true);

   giAttribRelatedChanges (BF::HOST);
   difFundRelatedChanges (BF::HOST);
   
   DString rightToCancel;  
   getField (ifds::RightToCancel, rightToCancel, BF::HOST);
   if (isRebook())
	   getWorkSession ().getOption (ifds::RightToCancelDefault, rightToCancel, BF::HOST,  false);
   rightToCancel.stripAll();
   RightToCancelRelatedChanges (rightToCancel, BF::HOST); 
   DString dstrPSDAdvice;
   getWorkSession ().getOption (ifds::PSDAdvice, dstrPSDAdvice, BF::HOST,  false);
   dstrPSDAdvice.stripAll();
   setFieldNoValidate(ifds::ScreenActivityType, I_("T"), BF::HOST, false, false, true); 
   if(isRebook())
	   populateFieldsWithDefaultValues(BF::HOST, MODE_REBOOK);
   setFieldReadOnly (ifds::PSDAdvice, BF::HOST, NO == dstrPSDAdvice.stripAll());
   bool bSrc_Channel_ReadOnly  = false;
   DString dstrNetworkID,dstrAWDFieldFlag;
   getField (ifds::NetworkID, dstrNetworkID, BF::HOST);
   getWorkSession ().getOption (ifds::AWDFieldFlag, dstrAWDFieldFlag,BF::HOST,false);
   if( !dstrNetworkID.empty()&& !( I_("AWD") == dstrNetworkID  && YES == dstrAWDFieldFlag ))  //AWD integration flag Yes use default,no change
   {  
	bSrc_Channel_ReadOnly  = true;        
	if(isRebook())
	{
    setFieldNoValidate(ifds::SourceOfTrade, dstrNetworkID, BF::HOST, false, true, true, !_bInitPending );
	setFieldNoValidate(ifds::ChannelOfTrade, NULL_STRING, BF::HOST, false, true, true, !_bInitPending );	
	}
  }
  setFieldReadOnly(ifds::SourceOfTrade,  BF::HOST, bSrc_Channel_ReadOnly );
  setFieldReadOnly(ifds::ChannelOfTrade, BF::HOST, bSrc_Channel_ReadOnly );
  addBlankToSubSet( ifds::SourceofFundsChecked, BF::HOST, true);
  setSourceOfFundsChecked(BF::HOST);

  return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Purchase::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   if (Trade::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      // if there are any changes 'to fund/to class' must be revalidated against softcap.
      setFieldValid(ifds::FromSoftCapCheck, idDataGroup, false);
      TradeFundAllocList *pFundAllocationList = NULL;

      if (isFieldUpdated(idField, idDataGroup) &&
          getFundAllocationList(pFundAllocationList, idDataGroup, false) <= WARNING && pFundAllocationList)
      {
            pFundAllocationList->setAllAllocsFndClsValidFlag(false, idDataGroup);
      }

      if (idField == ifds::AccountNum)
      {
         DString accountNum;
         MFAccount *pMFAccount = NULL;

         getField (ifds::AccountNum, accountNum, idDataGroup, false);
         if ( getWorkSession().getMFAccount ( idDataGroup, 
                                              accountNum, 
                                              pMFAccount) <= WARNING && 
              pMFAccount)
         {
            loadDepRedCodeSubstList ( accountNum, 
                                      I_("D"),  //deposit type
                                      idDataGroup);
            setFieldValid (ifds::TradesPayType, idDataGroup, false);
         }         
         amsAccountRelatedChanges (idDataGroup);
/* commented out as of incident #251618
//should check whether account has a fee model; if yes do not include the 'Regular' option for
//the acquisition fee option field
         DString feeModelCode;
         if ( getFeeModelCode (accountNum, feeModelCode, idDataGroup) <= WARNING && 
              !feeModelCode.empty()) 
         {
            DString acqFeeOptionSubstList;

            BFProperties *pBFProperties = 
               getFieldProperties (ifds::AcqFeeOption, idDataGroup);
            
            pBFProperties->getAllSubstituteValues (acqFeeOptionSubstList);
            acqFeeOptionSubstList = 
               removeItemFromSubtList ( acqFeeOptionSubstList, 
                                       I_("0")); //remove 'Regular'
            setFieldAllSubstituteValues (ifds::AcqFeeOption, idDataGroup, acqFeeOptionSubstList);
         }
*/
         bool bFeeApplicable;
         isFeeApplicable (PURCHASE_TPA_FEE, bFeeApplicable, idDataGroup);

         if (bFeeApplicable)
         {
            setFieldNoValidate (ifds::GrossOrNet, Y, idDataGroup, false, true, true);
            setFieldReadOnly (ifds::GrossOrNet, idDataGroup, true);
         }
      }
      else if (idField == ifds::TradesPayType)
      {
         REVALIDATEFIELD (ifds::AmtTypeSettleCurrency, idDataGroup);

         DString tradesPayType;
         getField (ifds::TradesPayType, tradesPayType, idDataGroup, false);
         tradesPayType.strip().upperCase();

         bool isEFTPurchase = tradesPayType == PAYTYPE::EFT;

         if (isACHApplicable (idDataGroup))
         {
            setFieldRequired (ifds::ACHProcessor, idDataGroup, isEFTPurchase );
            setFieldRequired (ifds::PayMethod, idDataGroup, isEFTPurchase );
         }
      }
      else if (idField == ifds::AmtType)
      {
         acqFeeOptionDefault (idDataGroup);
         //deposit type bearer certificate is only allowed for units,
         //call this in case deposit type validation fails since amount type is not unit
         aggregateOptionRelatedChanges (idDataGroup);
         setFieldValid (ifds::DepositType, idDataGroup, false); //invalidate deposit type
      } 
      else if (idField == ifds::AcqFeeOption)
      {
         DString acqFeeOption;

         getField (ifds::AcqFeeOption, acqFeeOption, idDataGroup);
         if (acqFeeOption == I_("4"))
         {
            setFieldNoValidate (ifds::ROAAmount, I_("0"), idDataGroup, false);
            setFieldReadOnly (ifds::ROAAmount, idDataGroup, true);
         }
         else if( isROAApplicable(  idDataGroup ) )
         {
            setFieldReadOnly ( ifds::ROAAmount, idDataGroup,false );                 
         }
         if (acqFeeOption != I_("1")) //not a discount fee model
         {
            //discount rate field should be set to 0
            setField (ifds::DiscountRate, I_("0"), idDataGroup, false);
         }
      }
      else if (idField == ifds::DepositType ||
               idField == ifds::RESPContrDetlTaxYear ||
               idField == ifds::LinkedEntityId)
      {
         DString depositType, dstrAccountNum;
         getField (ifds::DepositType, depositType, idDataGroup, false);
         
         if( idField == ifds::DepositType )
         {
            if (DSTCommonFunctions::codeInList (depositType, BEARERCERTCODELIST))
            {
               //blow the split commission list, from allocations
               TradeFundAllocList *pTradeFundAllocList;

               if ( getFundAllocationList (pTradeFundAllocList, idDataGroup) <= WARNING &&
                  pTradeFundAllocList)
               {
                  BFObjIter iterAllocList (*pTradeFundAllocList, idDataGroup);

                  while (!iterAllocList.end())
                  {
                     TradeFundAlloc *pTradeFundAlloc = 
                        dynamic_cast <TradeFundAlloc *> (iterAllocList.getObject());
                     if (pTradeFundAlloc)
                     {
                        BFObjIter iterAlloc (*pTradeFundAlloc, idDataGroup);

                        if (iterAlloc.positionByKey (I_("SplitCommissionList")))
                        {
                           iterAlloc.removeObjectFromMap (true);
                        }
                     }
                     ++iterAllocList;
                  }
               }
            }
            aggregateOptionRelatedChanges (idDataGroup);
            
            if (isRESPTradeAccount(idDataGroup))
            {
               if (!_bInitPending)
               {               
                  setFieldNoValidate (ifds::AssistedContrAmt, I_("0.00"), idDataGroup, false, true, true, false);   // do not trig related changes
                  setFieldNoValidate (ifds::RESPContrDetlTaxYear, NULL_STRING, idDataGroup, false, false, true, false); // do not trig related changes                                
               }
               bool bAssistedAmountApply = false;
               if (DSTCommonFunctions::codeInList (depositType, I_("77,78,79,80,81,94"))) 
               {
                  setFieldReadOnly (ifds::RESPContrDetlTaxYear, idDataGroup, false);
                  setFieldValid (ifds::RESPContrDetlTaxYear, idDataGroup, false);
                  setFieldValid (ifds::AmtType, idDataGroup, false);

                  if(DSTCommonFunctions::codeInList (depositType, I_("78,79")))
                  {   
                     setFieldReadOnly (ifds::AssistedContrAmt, idDataGroup, false);
                     setFieldValid (ifds::AssistedContrAmt, idDataGroup, false);
                     bAssistedAmountApply = true;
                  }          
               }
               else
               {
                  setFieldReadOnly (ifds::RESPContrDetlTaxYear, idDataGroup, true);           
               }
               if( !bAssistedAmountApply )
               {
                  setFieldReadOnly (ifds::AssistedContrAmt, idDataGroup, true);            
               }
               setFieldValid (ifds::EffectiveDate, idDataGroup, false); 
            }
            setSourceOfFundsChecked( idDataGroup );
         }                  

         // IN2385316, this for DepositType, RESPContrDetlTaxYear, LinkedEntityId
         if (isRESPTradeAccount(idDataGroup) && depositType == I_("78"))
         {
            DString dstrRESPContrDetlTaxYear, dstrLinkedEntityId;

            getField(ifds::RESPContrDetlTaxYear, dstrRESPContrDetlTaxYear, idDataGroup, false);
            getField(ifds::LinkedEntityId, dstrLinkedEntityId, idDataGroup, false);
            dstrRESPContrDetlTaxYear.strip();
            dstrLinkedEntityId.strip().stripLeading('0');

            if( dstrRESPContrDetlTaxYear != NULL_STRING &&
                dstrLinkedEntityId != NULL_STRING )
            {
               setDefaultValueRESPAssistedContrAmt(dstrRESPContrDetlTaxYear,
                                                   dstrLinkedEntityId,
                                                   idDataGroup);             

            }
         }
	
		 getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);	

		 if (isRDSPTradeAccount (idDataGroup, dstrAccountNum) && DSTCommonFunctions::codeInList (depositType, I_("49,66"))) // 49-RDSP Grant, 66-RDSP Bond
		 {
			  setFieldNoValidate ( ifds::RDSPPaymtDate, _currentBusinessDate, idDataGroup, false, true, true, false);
			  setFieldReadOnly (ifds::RDSPPaymtDate, idDataGroup, false);
		 }
		 else
		 {
			 setFieldNoValidate ( ifds::RDSPPaymtDate, NULL_STRING, idDataGroup, false, true, true, false);
			 setFieldReadOnly (ifds::RDSPPaymtDate, idDataGroup, true);
		 }

		 refreshSplitCommissions (idDataGroup);
      }
      else if (idField == ifds::Broker || idField == ifds::OrderSource)
      {
         setFieldValid (ifds::SettleSource, idDataGroup, false); //invalidate settle source
      }
      else if (idField == ifds::OrderType)
      {
         DString dstrOrderType;

         getField( ifds::OrderType, dstrOrderType, idDataGroup );
         if ( dstrOrderType == Y )   //wire order
         {
            setFieldValid (ifds::SettleSource, idDataGroup, false); //invalidate settle source
         }
		 PaymentStatusRelatedChanges(idDataGroup);
      }
      else if (idField == ifds::Amount)
      {
         setSettleLocsInstructionsInvalid (idDataGroup);
         setBeneficiaryAllocationsInvalid (idDataGroup);
         updateNotinalDataWarning (idDataGroup);
      }
      else if (idField == ifds::PayMethod)
      {
         // most of the job would be already done since base level, therefore
         // this level logic would take care only EFT purchase stuffs

         DString tradesPayType, fileProcessor, payMethod;
         getField (ifds::TradesPayType, tradesPayType, idDataGroup, false);
         getField (ifds::PayMethod, payMethod, idDataGroup, false);
         getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
         tradesPayType.strip().upperCase();
         payMethod.strip().upperCase();
         fileProcessor.strip().upperCase();

         bool isEFTPurchase = tradesPayType == PAYTYPE::EFT;

         if( isACHApplicable (idDataGroup) && isEFTPurchase && 
             payMethod != I_("CHQ") && !fileProcessor.empty() )
         {
            // trig related change of file processor to start, by re-set this field
            // due to trade level doesn't trig, this will result reload file processor 
            // on trade bank level for eft purchase bank

            TradeBankInstructionsList *pTradeBankInstructionsList = NULL;

            if (  getBankInstructionsList ( pTradeBankInstructionsList, 
                                             idDataGroup) <= WARNING &&
                  pTradeBankInstructionsList)
            {
               BFObjIter iter (*pTradeBankInstructionsList, idDataGroup);

               if (!iter.end()) //the bank list has only one item
               {
                  iter.getObject()->setField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
               }
            }
         }
      }
      else if ( idField == ifds::EffectiveDate )	  
      {
         PaymentStatusRelatedChanges(idDataGroup);

         DString dstrFromFund, dstrFromClass;
         getField(ifds::FromFund, dstrFromFund, idDataGroup);
         getField(ifds::FromClass, dstrFromClass, idDataGroup);

         REVALIDATEFIELD(ifds::FromFund, idDataGroup);
         REVALIDATEFIELD(ifds::FromClass, idDataGroup);

         if (!dstrFromFund.empty() && !dstrFromClass.empty() &&
             isFieldValid(ifds::FromFund, idDataGroup) && 
             isFieldValid(ifds::FromClass, idDataGroup))
         {
             refreshAllocations(idDataGroup);
             setSettleCurrencyFromFund(dstrFromFund, dstrFromClass, idDataGroup);
         }
      }
	  if ( ifds::SourceOfTrade == idField || ifds::ChannelOfTrade == idField ||
		   ifds::DealTime == idField ) 
	  {
		  DString dstrTime;
		  getField(ifds::DealTime, dstrTime, idDataGroup );
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
  }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::doValidateField ( const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (Trade::doValidateField (idField, strValue, idDataGroup))
   {
      if (idField == ifds::AmtTypePayType)
      {
         validateAmtTypePayType (idDataGroup);
      }
      else if (idField == ifds::AmtTypeSettleCurrency)
      {
         validateAmtTypeSettleCurrency (idDataGroup);
      }
      else if (idField == ifds::DepId)
      {
         validateDepositId (strValue, idDataGroup);
      }
      else if (idField == ifds::LevelGroup) 
      {
         validateBorrowedFunds (idDataGroup);
      }
      else if (idField == ifds::FundBrokerCode)
      {
         validateFundBrokerCode (strValue, idDataGroup);
      }
      else if (idField == ifds::AcqFeeOption)
      {
         validateAcqFeeOption (strValue, idDataGroup);
      }
      else if (idField == ifds::PaymentInfo)
      {
         validatePayStatus (idDataGroup);
      }
      else if (idField == ifds::FromClass)
      {
         if (!strValue.empty())
         {
            DString fundCode;

            getField (ifds::FromFund, fundCode, idDataGroup);
            validateFundForERISAAccount(fundCode, strValue, idDataGroup);
         }
      }
      else if (idField == ifds::DepositType)
      {
          MFAccount *pMFAccount = NULL;
          DString dstrAcct;

          getField(ifds::AccountNum, dstrAcct, idDataGroup);

          if (!strValue.empty() && DSTCommonFunctions::codeInList (strValue, I_("1,2,71")) &&
              getWorkSession().getMFAccount(idDataGroup, dstrAcct, pMFAccount) <= WARNING && pMFAccount)
          {
              pMFAccount->validateMoneyInTFSA(idDataGroup);
          }
      }

      //Softcapped validation
      if (idField == ifds::FromFund || idField == ifds::FromClass)
      {
          DString dstrFromFund, dstrFromClass, dstrAcctNum, dstrEffectiveDate;

          getField(ifds::FromFund, dstrFromFund, idDataGroup);
          getField(ifds::FromClass, dstrFromClass, idDataGroup);
          getField(ifds::AccountNum, dstrAcctNum, idDataGroup, false);
          getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

          getWorkSession().fundClassSoftCappedCheck(dstrAcctNum, dstrFromFund, dstrFromClass, I_("ED"), dstrEffectiveDate, idDataGroup);
          revalidateField(ifds::FromSoftCapCheck, idDataGroup);
      }

	  // DIF fund and order type validation
	  if(idField == ifds::OrderType)
	  {
			DString fundCode, orderType;
			getPurchaseFundField(ifds::FundCode, fundCode, idDataGroup);   
			getField(ifds::OrderType, orderType, idDataGroup);

			if(orderType == I_("Y") && isDIFFund(fundCode))
			{
				getErrMsg(IFASTERR::DIF_FUND_ONLY_ALLOW_DIRECT_ORDER,
						  CND::ERR_DIF_FUND_ONLY_ALLOW_DIRECT_ORDER,
						  CND::WARN_DIF_FUND_ONLY_ALLOW_DIRECT_ORDER,
						  idDataGroup);
			}
	  }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::doValidateAll ( const BFDataGroupId& idDataGroup, 
                                   long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_ ("doValidateAll"));

   if (Trade::doValidateAll (idDataGroup, lValidateGroup) <= WARNING)
   {
      DString dstrDepositType;

      getField( ifds::DepositType, dstrDepositType, idDataGroup, false );
      if (dstrDepositType == I_( "27" ) &&  
         hasAllocations (idDataGroup ))
      {
         // Invalid Deposit Type for allocated Trade
         ADDCONDITIONFROMFILE( CND::ERR_PURCHASE_INVALID_DEPOSIT_TYPE_FOR_ALLOC );
      }
      validateSettleLocations (idDataGroup);
      validateBeneficiaryAllocation (idDataGroup);
      validatePayStatus (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
inline bool Purchase::isACHApplicable (const BFDataGroupId &idDataGroup)
{
   DString achPurch;

   getWorkSession().getOption ( ifds::ACHPurch, 
                                achPurch, 
                                BF::HOST, 
                                false);
   return achPurch == I_("Y");
}

//******************************************************************************
bool Purchase::isSplitCommissionAllowed (const BFDataGroupId &idDataGroup)
{
   bool bAllowed = Trade::isSplitCommissionAllowed (idDataGroup);

   if (bAllowed )
   {
      DString depositType;
   
      getField (ifds::DepositType, depositType, idDataGroup, false);
      bAllowed = 
         depositType != I_("9") && 
         depositType != I_("10") &&
         depositType != I_("18") && 
         depositType != I_("70") && 
         depositType != I_("98");
//MFS PET 1203/05 - commission class A 
      bAllowed = bAllowed && 
                 ((isROATransType (idDataGroup) && isROAApplicable (idDataGroup)) ||
                 !isROATransType (idDataGroup));

      if (!bAllowed)
      {
         TradeFundAllocList *pFundAllocationList = NULL;

         if ( getFundAllocationList (pFundAllocationList, idDataGroup, false) <= WARNING &&
              pFundAllocationList)
         {
            BFObjIter iter (*pFundAllocationList, idDataGroup);

            while (!iter.end())
            {
               TradeFundAlloc *pTradeFundAlloc = dynamic_cast <TradeFundAlloc *> (iter.getObject());

               if (pTradeFundAlloc)
               {
                  pTradeFundAlloc->setField (ifds::SplitComm, N, idDataGroup, false);
               }
               ++iter;
            }
         }
      }
   }
   return bAllowed; 
}

//validations methods
//******************************************************************************
SEVERITY Purchase::canAccountTrade ( MFAccount *pMFAccount, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountTrade"));
//calls base class   
   if (Trade::canAccountTrade (pMFAccount, idDataGroup) <= WARNING)
   {
      DString tradeDate;

      getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
      if (pMFAccount->canPurchase (tradeDate, idDataGroup) <= WARNING)
      {
         pMFAccount->escrowPurchase (tradeDate, idDataGroup);
      }

      DString accountNum;

      pMFAccount->getField (ifds::AccountNum, accountNum, idDataGroup, false);
      validateClosedCountry (accountNum, idDataGroup);

   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateFundCode ( const DString &fundCode, 
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundCode"));
   FundMasterList *pFundMasterList = NULL;

   if (!fundCode.empty())
   {
      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList)
      {
         FundMaster *pFundMaster = NULL;

         if ( pFundMasterList->getFundMaster ( fundCode, 
                                               idDataGroup, 
                                               pFundMaster) &&
              pFundMaster)
         {
            DString tradeDate;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup);
            pFundMaster->cappedFundRule (tradeDate, idDataGroup);
         }
      }

      DString accountNum;

      getPurchaseAccountField (ifds::AccountNum, accountNum, idDataGroup);
      validatePUEVCapableFund (fundCode, accountNum, idDataGroup);
      validateInvestroCapableFund (fundCode, accountNum, idDataGroup);
      validateFundSponsorFeeModelCode (fundCode, accountNum, idDataGroup);
   }
   else 
   {
//if DepositType is bearer certificate code, fund and class cannot be blank	
      DString depositType;
      getField (ifds::DepositType, depositType, idDataGroup, false);

      if (DSTCommonFunctions::codeInList (depositType, BEARERCERTCODELIST))
      {
         ADDCONDITIONFROMFILE (CND::ERR_FUND_CLASS_MUST_BE_SPECIFIED);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Purchase::validateMasterActAMS(const BFDataGroupId &idDataGroup)
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
   else //Account doesn't linked to any AMS
   {
       FundDetail *pFundDetail = NULL;

       if (getWorkSession().getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail &&
           pFundDetail->isAMSParentFund(idDataGroup))
       {
          DString dstrAcctNum;
          getField (ifds::AccountNum, dstrAcctNum, idDataGroup);
          MFAccount *pMFAccount = nullptr;
          if ( getWorkSession().getMFAccount (idDataGroup, dstrAcctNum, pMFAccount) <= WARNING && 
               pMFAccount /*&&
               pMFAccount->isAMSAccount(idDataGroup)*/
             )
          {
             DString dstrAcctAMSCode;
             pMFAccount->getField(ifds::AMSCode, dstrAcctAMSCode, idDataGroup);
             if ( dstrAcctAMSCode.strip().empty() )
             {
                getErrMsg(IFASTERR::TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS,
                   CND::ERR_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS,
                   CND::WARN_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS,
                   idDataGroup);
             }
          }
       }
       else if (getWorkSession().getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail &&
          pFundDetail->isAMSChildFund(idDataGroup))
       {
          DString dstrAcctNum;
          getField (ifds::AccountNum, dstrAcctNum, idDataGroup);
          MFAccount *pMFAccount = nullptr;
          if ( getWorkSession().getMFAccount (idDataGroup, dstrAcctNum, pMFAccount) <= WARNING && 
               pMFAccount )
          {
             DString dstrAcctAMSCode;
             pMFAccount->getField(ifds::AMSCode, dstrAcctAMSCode, idDataGroup);
             if ( dstrAcctAMSCode.strip().empty() )
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
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY Purchase::validateFundClass ( const DString &fundCode, 
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
      DString broker,
         branch,
         agent;
//rollover will answer with the 'to side'
      getPurchaseRepInfoFields (broker, branch, agent, idDataGroup);
      if ( canFundTrade( broker,
                         branch,
                         agent,
                         TRADETYPE::PURCHASE,
                         accountNum,
                         fundCode,
                         classCode,
                         CND::ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON,
                         CND::ERR_WARN_FUND_CLASS_PURCHASE_STOP_FLAG_ON,
                         idDataGroup,
                         true) <= WARNING)  //check broker permits 'AddPerm'
      {
         if (!isHypo())
         {
            validateEUSDBackdates( fundCode,
                                   classCode,
                                   accountNum,
                                   idDataGroup);

            DString transType,
               tradeDate,
               transID;

            getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
            getField (ifds::TradesTransType, transType, idDataGroup, false);
            getField (ifds::TransId, transID, idDataGroup,false);

            validateSEGTradeEntry(accountNum,
                                  fundCode,
                                  classCode,
                                  tradeDate,
                                  I_("Fund"),
                                  transType,
                                  transID,
                                  idDataGroup);
            //P0186486FN09 - Employee and Agent Account Gap#8A           
            validateEmployeeAgentPurchase(fundCode, idDataGroup);
           
            revalidateField(ifds::FromSoftCapCheck, idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::fromFundClassRelatedChanges ( const DString &fundCode, 
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
//invalidate the wireordfndclass
      setFieldValid (ifds::WireOrdFndCls, idDataGroup, false); //wireorder should be checked against fund
      setFieldValid (ifds::NetOrdType, idDataGroup, false); //net orders are not allowed for bel funds
      setFieldValid (ifds::Amount, idDataGroup, false); 
      setFieldValid (ifds::SettleSource, idDataGroup, false); //invalidate settle source
      thirdPartyFundRelatedChanges (idDataGroup);
      acqFeeOptionDefault (idDataGroup);
//API needs this field to be invalid
      setFieldValid (ifds::FundCurrency, idDataGroup, false);
//Incident# 273841 - set the other confirm type to 1 if account/fund are PUEV capable
      setOtherConfirmTypeDefaultValues (idDataGroup);
      clearROAAmount (idDataGroup);

      DString loadType;
      bool bDepositTypeReadOnly = false;

      getPurchaseFundField (ifds::LoadType, loadType, idDataGroup);
      if ( accountHasCategory(I_( "11" ),idDataGroup) &&
           !fundCode.empty() &&
           !classCode.empty() &&
           loadType == I_("BEL"))
      {
         setFieldNoValidate (ifds::DepositType, I_("27"), idDataGroup, false, true, false, false );
         bDepositTypeReadOnly = true;
      }
      else
      {
         bDepositTypeReadOnly = false;
      }

      // Incident 345808 - Deposit Type combo loading only descriptions 
      DString accountNum;
      getPurchaseAccountField (ifds::AccountNum, accountNum, idDataGroup);
      loadDepRedCodeSubstList ( accountNum, 
                                I_("D"),  //deposit type
                                idDataGroup);

      setFieldReadOnly (ifds::DepositType, idDataGroup, bDepositTypeReadOnly);
      setFieldValid (ifds::DepositType, idDataGroup, false);
// PET 1203 FN 04 -- flag AcqFeeOption to invalid, therefore desktop will trigger validate AcqFeeOption
      setFieldValid (ifds::AcqFeeOption, idDataGroup, false);
//reset the EUSD field
      setFieldNoValidate (ifds::OverrideCost, I_("N"), idDataGroup, true);
      setFieldNoValidate (ifds::OverrideTIS, I_("N"), idDataGroup, true);
      
      GIAInvAttribList *pGIAInvAttribList (NULL);
      
      getGIFundDefaults (pGIAInvAttribList, idDataGroup);
      giAttribRelatedChanges (idDataGroup);
	  difFundRelatedChanges (idDataGroup);
//give the green light for refreshing splits      
      _bShouldRefreshSplitCommissions = true;
      refreshSplitCommissions (idDataGroup);
	  PaymentStatusRelatedChanges(idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//***********************************************************************************
SEVERITY Purchase::getPurchaseRepInfoFields ( DString &broker, 
                                              DString &branch, 
                                              DString &agent, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getPurchaseRepInfoFields"));

//get the values of broker/branch/sales rep from trade 
   getField (ifds::Broker, broker, idDataGroup);
   getField (ifds::Branch, branch, idDataGroup);
   getField (ifds::SlsrepCode, agent, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//***********************************************************************************
SEVERITY Purchase::validateTradeDate ( const DString &tradeDate,
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTradeDate"));

   if (Trade::validateTradeDate (tradeDate, idDataGroup) <= WARNING)
   {
    /*  DString editDeffs;

      getWorkSession().getOption ( ifds::EditDeffs, 
                                   editDeffs, 
                                   idDataGroup, 
                                   false);
      if (editDeffs == I_("N"))
      {
         DString dateOut;

         if ( DSTCommonFunctions::addDays (_currentBusinessDate, dateOut, 366) && 
              DSTCommonFunctions::
                  CompareDates (dateOut.stripAll(), tradeDate) == DSTCommonFunctions::FIRST_EARLIER)
         {
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_EFFECTIVE_DATE);
         }
      }*/
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateCurrency ( const DString &currency,
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateCurrency"));

   if (Trade::validateCurrency (currency, idDataGroup) <= WARNING)
   {
      DString accountNum;

      getPurchaseAccountField (ifds::AccountNum, accountNum, idDataGroup);
      validateCurrencyTaxType (accountNum, currency, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::filterSettleCurrencyForFund ( const DString &inCurrSubstList,
                                                 DString &currSubstList,
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("filterSettleCurrencyForFund"));
   DString fundCode,
      classCode;

   getPurchaseFundField (ifds::FundCode, fundCode, idDataGroup);
   getPurchaseFundField (ifds::ClassCode, classCode, idDataGroup);
//call base class method
   Trade::filterSettleCurrencyForFund ( fundCode, 
                                        classCode, 
                                        inCurrSubstList, 
                                        currSubstList, 
                                        idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateNetOrdType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateNetOrdType"));

   DString orderType;

   getField (ifds::OrderType, orderType, idDataGroup, false);
   if (orderType == I_("Y")) //wire order
   {
      DString loadType;

      if (getPurchaseFundField (ifds::LoadType, loadType, idDataGroup) <= WARNING)
      {
         DString grossOrNet;
   
         getField (ifds::GrossOrNet, grossOrNet, idDataGroup, false);
         // for wire orders, 'net' is not allowed for back end load funds
         if (loadType == I_("BEL") && grossOrNet == I_("N"))
         {
            ADDCONDITIONFROMFILE (CND::ERR_NET_NOT_FOR_BEL_FUND);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::getDefaultBankInstructions ( BankInstructions *&pBankInstructions, 
                                                const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDefaultBankInstructions"));

   DString payType;

   getField (ifds::TradesPayType, payType, idDataGroup, false);

   if (payType == PAYTYPE::EFT)
   {
      if ( getShareholderBankInstructions ( pBankInstructions, 
                                            AcctUseCode::EFT_PURCHASE, 
                                            idDataGroup) <= WARNING )
      {
         DString dstrAcctUse;

         if (pBankInstructions)
         {
            pBankInstructions->getField (ifds::AcctUseCode, dstrAcctUse, idDataGroup);

            if (dstrAcctUse == AcctUseCode::EFT_PURCHASE)
               return GETCURRENTHIGHESTSEVERITY ();

            if (dstrAcctUse != AcctUseCode::EFT_PURCHASE)
            {
               BankInstructions *pAltBankInstructions = NULL;
               //if not found look for the last eft bank used
               if ( getShareholderBankInstructions (pAltBankInstructions, 
                                                   AcctUseCode::ALT_EFT_PURCHASE,
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
            if ( getShareholderBankInstructions ( pBankInstructions, 
                                                  AcctUseCode::ALT_EFT_PURCHASE,
                                                  idDataGroup) <= WARNING && 
                                                  !pBankInstructions )
            {
               //if not found look for the last eft bank used
               getLastEFTBankInstructions (pBankInstructions, idDataGroup);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::validateDepositType ( const DString &depositType,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateDepositType"));

   Trade::validateDepositType (depositType, idDataGroup);
   
   DString amtType;

   getField (ifds::AmtType, amtType, idDataGroup, false);
   if (depositType == I_("23"))
   {
// currently we do not support deposit type 23, 
// but for future enhancements a new validation is added in here,
// as of the LSIF enhancement, PET 985, FN 01
      DString fundCode_,
         classCode_;
      bool bStopCommissionRebate = false;
      typedef std::vector< DString > _VECTOR;
      _VECTOR vFundCode,
         vClassCode;
      
      TradeFundAllocList *pTradeFundAllocList = NULL;

      if ( getFundAllocationList ( pTradeFundAllocList, 
                                   idDataGroup, 
                                   false) <= WARNING && //do not create the allocations
           pTradeFundAllocList)
      {
         BFObjIter iter ( *pTradeFundAllocList, 
                          idDataGroup, 
                          false, 
                          BFObjIter::ITERTYPE::NON_DELETED);

         iter.begin ();
         while (!iter.end ())
         {       
            iter.getObject ()->getField (ifds::FundCode, fundCode_, idDataGroup, false);
            iter.getObject ()->getField (ifds::ClassCode, classCode_, idDataGroup, false);
            vFundCode.push_back (fundCode_);
            vClassCode.push_back (classCode_);
            ++iter;
         }
      }
      else //if no allocations, used the given fund/class 
      {
         getPurchaseFundField (ifds::FundCode, fundCode_, idDataGroup);
         getPurchaseFundField (ifds::ClassCode, classCode_, idDataGroup);
         vFundCode.push_back (fundCode_);
         vClassCode.push_back (classCode_);
      }

      int errNdx = 0;

      for (_VECTOR::size_type i = 0; i < vFundCode.size(); ++i)
      {
         FundDetail *pFundDetail = NULL;

         if ( getWorkSession ().getFundDetail ( vFundCode[i], 
                                                vClassCode[i], 
                                                idDataGroup, 
                                                pFundDetail) && 
              pFundDetail)
         {
            DString stopCommissionRebate;

            pFundDetail->getField ( ifds::StopCommissionRebate, 
                                    stopCommissionRebate, 
                                    idDataGroup, 
                                    false);
            bStopCommissionRebate = stopCommissionRebate == I_("Y");
            if (bStopCommissionRebate)
            {
               errNdx = i;
               break;
            }
         }
      }
      if (bStopCommissionRebate)
      {
         DString idiStr;

         addIDITagValue (idiStr, I_("FUND"), vFundCode [errNdx]);
         addIDITagValue (idiStr, I_("CLASS"), vClassCode [errNdx]);
         ADDCONDITIONFROMFILEIDI (CND::ERR_COMMISSION_REBATE_NOT_ALLOWED_FOR_THIS_FUND, idiStr);
      }
   }
   else if ( amtType != I_("D") &&  //Amount
             depositType == I_("57"))
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMOUNT_CODE_FOR_LLP_REPAYMENT);
   }
   else
   {
      DString allowFractions,
         amount,
         fundCode;

      getFundField (ifds::FundCode, fundCode, idDataGroup);
      getField (ifds::Amount, amount, idDataGroup, false);
      getWorkSession().getOption ( ifds::AllowFractions, 
                                   allowFractions, 
                                   BF::HOST, 
                                   false);
      if (DSTCommonFunctions::codeInList (depositType, BEARERCERTCODELIST))
      {
         if (fundCode.empty())
         {
            ADDCONDITIONFROMFILE (CND::ERR_FUND_CANNOT_BE_BLANK_FOR_BEARER_CERTIFICATE); 
         }
         if (amtType != I_("U")) //units
         {
            ADDCONDITIONFROMFILE (CND::ERR_ONLY_UNIT_ALLOW_FOR_BEARER_CERTIFICATE);
         }
         if (allowFractions == I_("N") && DSTCommonFunctions::NumOfDecimals (amount) != 0)
         {
            ADDCONDITIONFROMFILE (CND::ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS);
         }
      }

      DString classCode, dstrLoadType;
      getPurchaseFundField (ifds::ClassCode, classCode, idDataGroup);
      getPurchaseFundField( ifds::LoadType,  dstrLoadType, idDataGroup );

      if ( !fundCode.empty() &&
           !classCode.empty() )
      {
         if ( depositType == I_( "27" ) &&
            dstrLoadType.strip().upperCase() != I_( "BEL" ) )
            // AND ACCOUNT CATEGORY 11 ???
         {
            // Non back-end load fund chosen for Deposit Type 27
            ADDCONDITIONFROMFILE( CND::WARN_PURCHASE_NON_BELL_FOR_DEPOSIT_27 );					
         }

         if ( depositType != I_( "27" ) &&
            dstrLoadType.strip().upperCase() == I_( "BEL" ) &&
            accountHasCategory( I_( "11" ), idDataGroup ) )
         {
            // Only deposit type 27 is allowed for BEL funds purchase in a NAV Share account
            ADDCONDITIONFROMFILE( CND::ERR_PURCH_NAV_ACCT_BEL_FUND_NAV_DEPOSIT_TYPE );					
         }
      }

      if (GETCURRENTHIGHESTSEVERITY () <= WARNING) //no error, yet
      {
         MFAccount *pMFAccount = NULL;

         if (getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
         {
            DString taxType;

            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
            taxType.upperCase ();

            if ( getWorkSession ().isLIFLike (taxType) || //LIF
                 taxType == I_("L"))     //LRIF
            {

               TaxTypeRule *pTaxTypeRule = NULL;

               if (pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
               {
                  RedCodeByTaxTypeList *pRedCodeList = NULL;
             
                  pTaxTypeRule->getDepTypeList (pRedCodeList, idDataGroup);
                  if (pRedCodeList)
                  {
                     BFObjIter iterRedCode ( *pRedCodeList, 
                                             idDataGroup, 
                                             true, 
                                             BFObjIter::ITERTYPE::NON_DELETED);

                     iterRedCode.begin ();
                     DString copyOfDepositType (depositType),
                        strDepositCode,
                        positionKey;
   //copyOfDepositType contains DepositType__DepTypeDescription;have to extract the deposit type
                     int nWords = copyOfDepositType.words ();
                     if (nWords > 0)
                     {
                        strDepositCode = copyOfDepositType.word (0);
                     }
                     strDepositCode.strip ();

                     BFData data;

                     data.setElementValue (ifds::RedCode, strDepositCode, true, NULL);
                     pRedCodeList->getStrKey (positionKey, &data);
                     if (iterRedCode.positionByKey (positionKey))
                     {
                        BFAbstractCBO * pBase = iterRedCode.getObject (); 
                        RedCodeByTaxType* pRedCodeByTaxType = 
                           dynamic_cast<RedCodeByTaxType*> (iterRedCode.getObject ());

                        if (pRedCodeByTaxType)
                        {
                           DString strMaxApplies;

                           pRedCodeByTaxType->getField (ifds::MaximumApplies, strMaxApplies, idDataGroup);
                           if (strMaxApplies == I_("Y"))
                           {
                              DString strLIPRateExist;

                              pMFAccount->getLIPRateExist (strLIPRateExist, idDataGroup);
                              if (strLIPRateExist == I_("N"))
                              {
                                 ADDCONDITIONFROMFILE (CND::ERR_CANSIM_NOT_EXISTS);
                              }
                           }

                           DString payType,
                              dtaEligible;

                           getField (ifds::TradesPayType, payType, idDataGroup, false);
                           if (payType == PAYTYPE::DIRECT)
                           {
                              pRedCodeByTaxType->getField ( ifds::DTAEligible, 
                                                            dtaEligible, 
                                                            idDataGroup, 
                                                            false);
                              if (dtaEligible == I_("0"))
                              {
                                 ADDCONDITIONFROMFILE (CND::ERR_DTA_NOT_ALLOWED_FOR_THIS_DEPOSITTYPE);
                              } 
                           }
                        }
                     }
                  } // pRedCode List
               } // taxTypeRule exists
            } // if LIF or LRIF 		
// RESP OR Family Plan RESP
            else if (taxType == I_ ("9") || taxType == I_( "M" ))
            {
               if ( depositType == DEPTYPE_ADDITNL_CESG_GRANT ||
                    depositType == DEPTYPE_CLB ||
                    depositType == DEPTYPE_CLB_ADMIN || 
                    depositType == DEPTYPE_ACES ||
					depositType == DEPTYPE_SAGES_GRANT_PAYMENT )
               {
                  DString dstrSiblingOnly;
                  
                  pMFAccount->getField (ifds::SiblingOnly, dstrSiblingOnly, idDataGroup, false);
                  dstrSiblingOnly.strip().upperCase();
                  if (dstrSiblingOnly != Y)
                  {
                     // raise rejerror 710
                     DString idiStr;
                     addIDITagValue (idiStr, I_("CODE_TYPE"), I_("Deposit Type"));

                     getErrMsg ( IFASTERR::DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS,
                                 CND::ERR_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS,
                                 CND::WARN_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS,
                                 idDataGroup,
                                 idiStr );
                  }
               }
            }
         } // if pMFAccount != NULL
      }
   }
   if (depositType == I_("1"))
   {
      MFAccount *pMFAccount = NULL;
      DString strTradesTransType;
      getField( ifds::TradesTransType, strTradesTransType, idDataGroup );
      if( strTradesTransType.strip().upperCase() == TRADETYPE::PURCHASE )
      {
         if (getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
         {
            DString taxType;

            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
            taxType.strip().upperCase();
            if ( getWorkSession ().isLIFLike (taxType) || //LIF
               taxType == I_("L") || //LRIF
               getWorkSession ().isLIRALike (taxType)) //LIRA like   
            {
               ADDCONDITIONFROMFILE( CND::ERR_CASH_TRADE_NOT_ALLOWED_FOR_TAX_TYPE );
            }
         }
      }
   }
   
   if (depositType == I_("59") || depositType == I_("63"))
   {
      MFAccount *pMFAccount = NULL;
      DString strTradesTransType;
      getField( ifds::TradesTransType, strTradesTransType, idDataGroup );
      if( strTradesTransType.strip().upperCase() == TRADETYPE::PURCHASE )
      {
         if (getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
         {
            // do checking for annuitant DOD
            DString dstrDofDeath;
            pMFAccount->getDofDeathofEntityType (ENTITY_ANNUITANT,dstrDofDeath, idDataGroup);//Modified for INC0033364
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
      }
   }

   else if (depositType == EA_BONUS_PURSHASE)//64
   { //P0186486FN09 - Employee and Agent Account Gap#8A
      MFAccount *pMFAccount = NULL;

      if (getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
      {
         validateAccountType(pMFAccount, idDataGroup);
      }
      
      DString fundCode;  
      getField (ifds::FromFund, fundCode, idDataGroup, false); 
      if(!fundCode.empty())
      {
	      validateEmployeeAgentPurchase(fundCode, idDataGroup);
	   }
	}
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateDepositId ( const DString &depId,
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateDepositId"));

   //if DepositId-83 is Yes and OrderType is Direct or DepositIdMand is No
   //and DepositId-115 is blank, issue error based on ErrNum '231'

   DString depositIdMand,
      depositId2,
      orderType;

   getField (ifds::OrderType, orderType, idDataGroup, false);
   getWorkSession().getOption2 ( ifds::DepositId2, 
                                 depositIdMand, 
                                 idDataGroup, 
                                 false);
   getWorkSession().getOption ( ifds::DepositId2, 
                                depositId2,
                                idDataGroup,
                                false);

   if ( !( depositId2 == I_("N") &&
           ( orderType == I_("Y") || //direct
             depositIdMand == I_("Y"))))
   {
      if (!depId.empty())
//if DepositId-83 is Yes and OrderType is Direct or DepositIdMand is No
//and DepositId-115 is not blank and if DepValid is No or DepClosed is Yes,
//issue error
      {
         BFData queryData (ifds::DSTC0147_REQ);
         BFData *response = new BFData(ifds::DSTC0147_VW);

         DString mgmtCoIdOut;
         queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
         queryData.setElementValue (ifds::DepId, depId);
         queryData.setElementValue (ifds::Track, I_("N"));
         queryData.setElementValue (ifds::Activity, NULL_STRING);
         if (BFDataBroker::getInstance()->receive ( DSTC_REQUEST::DEPOSIT, 
                                                    queryData, 
                                                    *response, 
                                                    DSTCRequestor (getSecurity())) <= WARNING)
         {
            DString depValid, 
               depClosed;

            depValid = response->getRepeat (0).getElementValue (ifds::DepValid);
            depClosed = response->getRepeat (0).getElementValue (ifds::DepClosed);
            if (depValid.strip().upperCase() == I_("N"))
            {
               ADDCONDITIONFROMFILE (CND::ERR_DEPOSIT_ID_INVALID);
            }
            if (depClosed.strip().upperCase() == I_("Y"))
            {
               ADDCONDITIONFROMFILE (CND::ERR_DEPOSIT_ID_CLOSED);
            }
         }
         else
         {
            delete response;
            response = NULL;
         } 
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::validateBorrowedFunds (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateBorrowedFunds"));

   MFAccount *pMFAccount = NULL;

   if (getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
   {      
      if (isHouseBroker (idDataGroup))
      {
         Agent *pAgent = NULL;

         if ( getAgent (pAgent, idDataGroup) <= WARNING &&
              pAgent)
         {
            DString borrowedFunds;
      
            getField (ifds::BorrowedFunds, borrowedFunds, idDataGroup, false);
            if (borrowedFunds == I_("Y")) 
            {
               pAgent->canPurchase (idDataGroup, true);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Purchase::isCashDateUpdatable ( FundMaster *pFundMaster,
                                     const BFDataGroupId &idDataGroup)
{
   DString cashReceiptTrack,
      fundType;
   getWorkSession().getOption ( ifds::CashReceiptTrack, 
                                cashReceiptTrack, 
                                BF::HOST, 
                                false);
   pFundMaster->getField (ifds::FundType, fundType, BF::HOST, false);
   fundType.upperCase();
   cashReceiptTrack.upperCase();
   return Trade::isCashDateUpdatable (pFundMaster, idDataGroup) ||
          ( fundType != I_("I") && //not a money market fund
            I_("Y") == cashReceiptTrack);
}

//******************************************************************************
SEVERITY Purchase::validateAmtType ( const DString &amtType, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtType"));

   bool bIsMasterActWithOneChild = getWorkSession().isMasterActWithOneChild(idDataGroup);

   if (Trade::validateAmtType (amtType, idDataGroup) <= WARNING)
   {
      DString allowUnitsPurchase;

      getWorkSession().getOption ( ifds::AllowUnitsPurchase, 
                                   allowUnitsPurchase, 
                                   idDataGroup, 
                                   false);

//only amount and units allowed for purchases
      if (amtType == I_("U"))
      {
         if (bIsMasterActWithOneChild)
         {
            validateParentFundAgainstAmtType(idDataGroup);
         }

         if (allowUnitsPurchase == I_("N")) //non allocated purchase
         {
            ADDCONDITIONFROMFILE (CND::ERR_UNIT_PURCHASE_NOT_ALLOWED);
         }
      }

//If DepositType is '57', AmountType must be 'D'
//same logic applies to validateDepositType
      DString depositType;

      getField (ifds::DepositType, depositType, idDataGroup);

      if ( amtType != I_("D") &&  //amount
           depositType == I_("57"))
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMOUNT_CODE_FOR_LLP_REPAYMENT);
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

//PET1117.FN66 SWIFT R2.7, R2.8, 
//PET1117.FN67 Investro R17.1.0.
      if ( amtType == I_("D") &&
           !bIsSwift) //Incident# 554580 - remove current validation for SWIFT monetary amount trades
      {         
         DString fundCode,
            accountNum;

         getPurchaseFundField (ifds::FundCode, fundCode, idDataGroup);
         getPurchaseAccountField (ifds::AccountNum, accountNum, idDataGroup);
         validateAmtTypeForNetworkIDAndFundBroker (accountNum, fundCode, idDataGroup/*, I_("SWFT")*/);
      }
      if(isAssociationWithBeneficiaryAllowed(idDataGroup))
      {
         DString amtType, depositType;
         getField(ifds::DepositType, depositType, idDataGroup, false);
         depositType.strip();

         if(DSTCommonFunctions::codeInList (depositType, I_("77,78,79,80,81,94")))
         {
            getField(ifds::AmtType, amtType, idDataGroup, false);
            amtType.strip();         
            if (amtType != I_("D"))
            {
               // raise error...
               // display rejerror 331
               getErrMsg ( IFASTERR::SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED,
                           CND::ERR_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED,
                           CND::WARN_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED,
                           idDataGroup);

            }
         }      
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::validateAmount ( const DString &amount,  
                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmount"));

// amount cannot be zero if transaction type = purchase
   double dec_amount = DSTCommonFunctions::convertToDouble (amount);

   if (dec_amount == 0)
   {
      ADDCONDITIONFROMFILE (CND::ERR_VALUE_CANNOT_BE_ZERO);
   }
   else if (Trade::validateAmount (amount, idDataGroup) <= WARNING)
   {
      DString amtType;

      getField (ifds::AmtType, amtType, idDataGroup);
      if (amtType == I_("D")) //amount
      {
         Trade::validateAmountPrecision (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::validateAmtTypeSettleCurrency ( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeSettleCurrency"));
   DString payType,
      amtType,
      allowUnitsPurchase, 
      multCurrEFTUnitPurchase, 
      invalidPayType;

   getField (ifds::TradesPayType, payType, idDataGroup, false);
   getField (ifds::AmtType, amtType, idDataGroup, false);
   getWorkSession().getOption ( ifds::AllowUnitsPurchase, 
                                allowUnitsPurchase, 
                                idDataGroup, 
                                false);
   getWorkSession().getOption ( ifds::MultiCurrEFTUnitPurch, 
                                multCurrEFTUnitPurchase, 
                                idDataGroup, 
                                false);
   getWorkSession().getOption ( ifds::DisAllowPayTypeUnitPurch, 
                                invalidPayType, 
                                idDataGroup, 
                                false);

   if ( amtType == I_("U") &&
        allowUnitsPurchase == I_("Y") &&
        _multiCurrency == I_("Y") &&
        multCurrEFTUnitPurchase == I_("N") &&
        payType == PAYTYPE::EFT)
   {
      DString fundCurrency,
         settleCurrency;

      getField (ifds::SettleCurrency, settleCurrency, idDataGroup);
      if (getPurchaseFundField (ifds::Currency, fundCurrency, idDataGroup) <= WARNING)
      {
         if ( !settleCurrency.empty() && 
              !fundCurrency.empty() &&
              settleCurrency != fundCurrency)
         {
            ADDCONDITIONFROMFILE (CND::ERR_FUNDCLASS_SETTLE_CURRENCY_DIFFERENT);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeGrossNet"));
   DString amtType;

   getField (ifds::AmtType, amtType, idDataGroup, false);
   if (amtType == I_("U"))
   {
      DString allowUnitsPurchase;

      getWorkSession().getOption ( ifds::AllowUnitsPurchase, 
                                   allowUnitsPurchase, 
                                   idDataGroup, 
                                   false);
      if (allowUnitsPurchase == I_("Y")) //non allocated purchase
      {
         DString loadType, 
            grossOrNet;

         getPurchaseFundField (ifds::LoadType, loadType, idDataGroup);
         getField (ifds::GrossOrNet, grossOrNet, idDataGroup);
         if ( loadType == I_("BEL") && 
              grossOrNet == I_("N")) //net
         {
            ADDCONDITIONFROMFILE (CND::ERR_NET_UNIT_PURCHASE_NOT_ALLOWED);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::validateAmtTypePayType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtType"));
   DString amtType,
      payType,
      invalidPayType;

   getField (ifds::TradesPayType, payType, idDataGroup, false);
   getField (ifds::AmtType, amtType, idDataGroup, false);

   getWorkSession().getOption ( ifds::DisAllowPayTypeUnitPurch, 
                                invalidPayType, 
                                idDataGroup, 
                                false);
   if ( amtType == I_("U") &&
        DSTCommonFunctions::codeInList (payType, invalidPayType))
   {
      ADDCONDITIONFROMFILE (CND::ERR_EFT_IN_UNITS_NOT_FOR_PURCHASE)
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY Purchase::validateMinFromFundAmount ( const DString &accountNum,
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
   double dec_amount = DSTCommonFunctions::convertToDouble (amount);
//first check ams
   amsMinAmtCheck ( TRADETYPE::PURCHASE, 
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
      //getField (ifds::DepositType, depositType, idDataGroup ); //comment by in1419539
      if ( depositType != I_("2") && 
           fundClassTradeMinimumAmtCheck ( TRADETYPE::PURCHASE,
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
                                           idDataGroup) <= WARNING)
      {
         setField (ifds::InitPurch, initPurch, idDataGroup, false);
      }
   }
   if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
   {
      MFAccount *pMFAccount = NULL;

      if ( getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING &&
           pMFAccount)
      {
         DString taxType,
            grpContribution;

         getWorkSession ().getOption ( ifds::GrpContribution, 
                                       grpContribution, 
                                       BF::HOST,
                                       false);
         pMFAccount->getField (ifds::TaxType, taxType, idDataGroup, false);
         if ( grpContribution == Y &&
              (taxType == I_("1") || //RRSP
               taxType == I_("2") || //RRIF
               getWorkSession ().isLIFLike (taxType) || //LIF
               getWorkSession ().isLIRALike (taxType)|| //LIRA & LRSP
               taxType == I_("L") || //LRIF
               taxType == I_("R")))  //PRIF
         {
            DString contributionLimit;

            if ( pMFAccount->groupContributMax (idDataGroup, contributionLimit) <= WARNING && 
                 dec_amount > DSTCommonFunctions::convertToDouble (contributionLimit))
            {
               DString sysCurrency,
                  idiStr;

               getWorkSession ().getOption ( ifds::SysCurrency, 
                                             sysCurrency, 
                                             BF::HOST, 
                                             true);

               if ( contributionLimit.empty() || 
                    contributionLimit == I_("+"))
               {
                  contributionLimit = I_("0");
               }
               contributionLimit += I_(" ");
               
               addIDITagValue (idiStr, I_("MAXIMUM_AMT"), contributionLimit + sysCurrency);
               ADDCONDITIONFROMFILEIDI (CND::ERR_MAXIMUM_INPUT_AMT, idiStr);
            }
         }
      }
   }

   if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
   {
//if AllowFractions is 'No' and DepositType is Bearer Certificate code, Amount must be full units
//validation also put in ::validateDepositType
      if (amtType == I_("U"))
      {
         DString allowFractions;

         getWorkSession().getOption ( ifds::AllowFractions, 
                                      allowFractions, 
                                      BF::HOST, 
                                      false);

         if ( allowFractions == I_("N") && 
              DSTCommonFunctions::NumOfDecimals (amount) != 0 && 
              DSTCommonFunctions::codeInList (depositType, BEARERCERTCODELIST))
         {
            ADDCONDITIONFROMFILE (CND::ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS);
         }
      }   
   }
//PET1117.FN56.R2.4.0
   if (GETCURRENTHIGHESTSEVERITY() <= WARNING) //still good to go and make antoher check?
   {
      if (amtType == I_("U")) //units, 
      {
         DString errorAcctNum;

         getWorkSession().getOption ( ifds::ErrorAcctNum,
                                      errorAcctNum,
                                      BF::HOST,
                                      false);
//apply the rule if the erroracctnum is not the account for which the purchase has been placed
         if (errorAcctNum != accountNum) 
         {
            //apply the min units rule, only for 3rd party funds, (for now); 
            //no need to check if fund is 3rd party
            //if there is no set-up for the rule, then the rule does not apply
            DString minUnits,
               errorSeverityLevel;

            if (readMinUnits ( TRADETYPE::PURCHASE, 
                               fundCode, 
                               classCode, 
                               accountNum, 
                               minUnits, 
                               errorSeverityLevel, 
                               idDataGroup) <= WARNING)
            {
               if (dec_amount < DSTCommonFunctions::convertToDouble (minUnits))
               {
                  DString idiStr;

                  addIDITagValue (idiStr, I_("min"), minUnits);
                  if (errorSeverityLevel == I_("E")) //error
                  {
                     ADDCONDITIONFROMFILEIDI (CND::ERR_AMOUNT_IS_LESS_THEN_MINIMUM_REQUIRED, idiStr);
                  }
                  else if (errorSeverityLevel == I_("W")) //warning
                  {
                     ADDCONDITIONFROMFILEIDI (CND::WARN_AMOUNT_IS_LESS_THEN_MINIMUM_REQUIRED, idiStr);
                  }
                  else if (errorSeverityLevel == I_("I")) //ignore
                  {
                     ;//do nothing! nobody cares of the minimum required
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************        
SEVERITY Purchase::amsFundClassTradeMinAmtCheck ( const DString &transType,
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
                                depositType //in1419539 //in1337808
                                ) <= WARNING) 
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
                                  initPurch == I_("Y"),
                                  idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************        
SEVERITY Purchase::validateCertRequired ( const DString &certRequired,
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("valideateCertRequired"));

   DString fundCode,
      classCode;
   
   if ( getPurchaseFundField (ifds::FundCode, fundCode, idDataGroup) <= WARNING &&
        getPurchaseFundField (ifds::ClassCode, classCode, idDataGroup) <= WARNING)
   {
      Trade::validateCertRequired (fundCode, classCode, certRequired, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::readMinUnits ( const DString &transType,
                                  const DString &fundCode,
                                  const DString &classCode,
                                  const DString &accountNum,
                                  DString &minUnits, 
                                  DString &errorSeverityLevel, 
                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("readMinUnits"));
   FundDetail *pFundDetail = NULL;

   if ( getWorkSession().getFundDetail ( fundCode, 
                                         classCode, 
                                         idDataGroup, 
                                         pFundDetail) &&
        pFundDetail)
   {
      FundTransTypeList *pFundTransTypeList = NULL;

      if ( pFundDetail->getFundTransTypeList (pFundTransTypeList) <= WARNING &&
           pFundTransTypeList)
      {
         FundTransType *pFundTransType = NULL;

         if ( pFundTransTypeList->getFundTransType ( transType, 
                                                     pFundTransType, 
                                                     idDataGroup) <= WARNING &&
              pFundTransType)
         {
            DString minSeverityCode;

            if ( pFundTransType->getMinUnits ( getWorkSession(),
                                               accountNum, 
                                               minUnits, 
                                               errorSeverityLevel, 
                                               idDataGroup) <= WARNING)
            {
               ;//do nothing
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::acqFeeOptionDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("acqFeeOptionDefault"));
   DString fundCode,
      acqFeeOptionDefault (I_("0"));
   bool bReadOnly = true;
   DString feeModelCode,
      accountNum;
   
//get the fee model code from account/shareholder
   getPurchaseAccountField (ifds::AccountNum, accountNum, idDataGroup);
   if ( getFeeModelCode (accountNum, feeModelCode, idDataGroup) <= WARNING && feeModelCode.empty()) 
   {  
      // PET 1203 FN04 -- if FeeModelCode is empty and isJumboPriceApplicable, then
      if ( feeModelCode.empty() && isJumboPriceApplicable( idDataGroup ) )
      {
         bReadOnly = false;
      }
   }
//if FeeModel is not empty for acct/shrholder, then get the default from FundSponsorFeeModel based 
//on the FundGroup of the Fund
   else 
   {
      getPurchaseFundField (ifds::FundCode, fundCode, idDataGroup);
      if (!fundCode.empty())
      {
         FundMasterList *pFundMasterList = NULL;
         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
              pFundMasterList)
         {
            DString loadType;
            if ( getPurchaseFundField (ifds::LoadType, loadType, idDataGroup) <= WARNING &&
                 loadType != I_("FEL"))//front end load
            {
               ;// do nothing; set field no validate is done at the end of the method
            }
            else // if front end load fund then do the followings
            {
               DString unitsCal;

               if (getPurchaseFundField (ifds::UnitsCal, unitsCal, idDataGroup) <= WARNING)
               {
                  if (unitsCal == I_("D")) //discount
                  {
                     DString amtType;

                     getField (ifds::AmtType, amtType, idDataGroup);
                     if ( pFundMasterList->is3rdPartyFund (fundCode) &&
                        amtType == I_("D")) //amount
                     { //buy at NAV is the default 
                        acqFeeOptionDefault = I_("2");
                     }
                     else //get the default based on the discount fee model 
                     {
                        //get the fund master object to find out to fund group
                        bReadOnly = false;
                        FundMaster *pFundMaster = NULL;

                        if ( pFundMasterList->getFundMaster ( fundCode, 
                           idDataGroup, 
                           pFundMaster) &&
                           pFundMaster)
                        {
                           DString fundGroup;

                           pFundMaster->getField (ifds::FundGroup, fundGroup, idDataGroup);
                           //call view 307, to get the default model option
                           FundSponsorFeeModelList *pFundSponsorFeeModelList = NULL;

                           if ( getFundSponsorFeeModelList ( accountNum, 
                                                             fundCode, 
                                                             pFundSponsorFeeModelList, 
                                                             idDataGroup) <= WARNING &&
                                pFundSponsorFeeModelList)
                           {
                              FundSponsorFeeModel *pFundSponsorFeeModel = NULL;

                              if ( pFundSponsorFeeModelList->getFundSponsorFeeModel ( feeModelCode,
                                                                                      fundGroup,
                                                                                      pFundSponsorFeeModel,
                                                                                      idDataGroup) <= WARNING &&
                                   pFundSponsorFeeModel)
                              {
                                 pFundSponsorFeeModel->getField ( ifds::FeeModelOption, 
                                                                  acqFeeOptionDefault,
                                                                  idDataGroup);
                                 if ( acqFeeOptionDefault == I_("3") && //bonimax
                                      !pFundMasterList->is3rdPartyFund (fundCode)) 
                                 {
                                    //bonimax doesn't apply for non-3rd party funds,
                                    //let the user choose another option
                                    acqFeeOptionDefault = NULL_STRING; 
                                 }
                              }
                           }
                           else //clear the condition, let the user decide, which acq fee option to use
                           {
                              int count = CONDITIONCOUNT();
                              Condition *c = NULL;
                              for (int i = 0; i < count; i++)
                              {
                                 c = GETCONDITION( i );
                                 int condCode = c->getCode();
                                 //do not want to promote this condition
                                 if (condCode == CND::ERR_FNDSPONSOR_FEEMODEL_DOES_NOT_EXIST) 
                                 {
                                    CLEARCONDITION( i );
                                    bReadOnly = true; //user should not be able to modify the field
                                    break;
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   if (!_bInitPending)
   {
      setFieldNoValidate (ifds::AcqFeeOption, acqFeeOptionDefault, idDataGroup, false, false, true);
   }
   _defaultFeeModelOption = acqFeeOptionDefault;
   setFieldReadOnly (ifds::AcqFeeOption, idDataGroup, bReadOnly);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateAcqFeeOption ( const DString &acqFeeOption, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAcqFeeOption"));
   DString feeModelCode,
      accountNum;
   
//get the fee model code from account/shareholder
   getPurchaseAccountField (ifds::AccountNum, accountNum, idDataGroup);
   bool bFeeModelCodeExists = getFeeModelCode (accountNum, feeModelCode, idDataGroup) <= WARNING && 
                             !feeModelCode.empty();

   if (acqFeeOption == I_("3")) //boni max
   {
      DString fundCode;

      getPurchaseFundField (ifds::FundCode, fundCode, idDataGroup);
      if (!fundCode.empty())
      {
         FundMasterList *pFundMasterList = NULL;
         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
              pFundMasterList)
         {
            if (!pFundMasterList->is3rdPartyFund (fundCode))
            {
               DString acqFeeOptionDescr,
                  idiStr;

               getField (ifds::AcqFeeOption, acqFeeOptionDescr, idDataGroup, true);
               addIDITagValue (idiStr, I_("acqoption"), acqFeeOptionDescr);               
               ADDCONDITIONFROMFILEIDI (CND::ERR_ACQ_FEE_OPTION_ONLY_APPLICABLE_FOR_3RD_PARTY_FUNDS, idiStr)
            }
         }
      }
   }
   else if (acqFeeOption == I_("0"))
   {
//should check whether account has a fee model; if yes and fund is a FEL fund 
//raise error
      if (bFeeModelCodeExists)
      {
         DString fundCode;

         getPurchaseFundField (ifds::FundCode, fundCode, idDataGroup);
         if (!fundCode.empty())
         {
            DString loadType,
               unitsCal;

            if ( getPurchaseFundField (ifds::LoadType, loadType, idDataGroup) <= WARNING &&
                 loadType == I_("FEL") && //front end load
                 getPurchaseFundField (ifds::UnitsCal, unitsCal, idDataGroup) <= WARNING &&
                 unitsCal == I_("D"))  //discount
            {
               ADDCONDITIONFROMFILE (CND::ERR_REGULAR_ACQ_FEE_OPTION_DOES_NOT_APPLY);
            }
         }
      }
   }
   // PET 1203 FN04 enhancement
   else if ( acqFeeOption == I_("4") && !(isJumboPriceApplicable( idDataGroup)) )
   {
      ADDCONDITIONFROMFILE (CND::ERR_JUMBO_PRICE_NOT_APPLICABLE );
   }
   if( acqFeeOption == I_("1") ||acqFeeOption == I_("2") ||acqFeeOption == I_("3") ) 
   {
      if( !bFeeModelCodeExists || isJumboPriceApplicable( idDataGroup  ) )
      {
         DString acqFeeOptionDescr,
            idiStr;         
         getField (ifds::AcqFeeOption, acqFeeOptionDescr, idDataGroup, true);
         addIDITagValue (idiStr, I_("acqoption"), acqFeeOptionDescr);               
         ADDCONDITIONFROMFILEIDI (CND::ERR_FEE_OPTION_DOSE_NOT_APPLY, idiStr)
      }
   }

   DString dstrFundCode;
   getPurchaseFundField (ifds::FundCode, dstrFundCode, idDataGroup);
   if (bFeeModelCodeExists && GETCURRENTHIGHESTSEVERITY () <= WARNING && !dstrFundCode.empty())
   {
      if (acqFeeOption != _defaultFeeModelOption)
      {
         DString acqFeeOptionDescr,
            idiStr;

         getField (ifds::AcqFeeOption, acqFeeOptionDescr, idDataGroup, true);
         addIDITagValue (idiStr, I_("acqoption"), acqFeeOptionDescr);
         ADDCONDITIONFROMFILEIDI (CND::WARN_FEE_MODEL_OVERRIDDEN, idiStr)
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::amsAccountRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("amsAccountRelatedChanges"));
   DString accountNum;
   MFAccount *pMFAccount = NULL;

   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   if ( getWorkSession().getMFAccount ( idDataGroup, 
                                        accountNum, 
                                        pMFAccount) <= WARNING && 
        pMFAccount &&
        pMFAccount->isAMSAccount (idDataGroup))
   {
      DString defaultAllocOverride;

      getWorkSession().getOption ( ifds::DefaultAllocOverride, 
                                    defaultAllocOverride, 
                                    idDataGroup, 
                                    false); 
      if (defaultAllocOverride == I_("Y"))  
      {
         bool bAMSMixOverride = 
               getWorkSession().hasUpdatePermission (UAF::AMS_MIX_OVERRIDE);
         
         setFieldReadOnly (ifds::FromFundNumber, idDataGroup, !bAMSMixOverride);
         setFieldReadOnly (ifds::FromFund, idDataGroup, !bAMSMixOverride);
         setFieldReadOnly (ifds::FromClass, idDataGroup, !bAMSMixOverride);
         setFieldReadOnly (ifds::FundISIN, idDataGroup, !bAMSMixOverride);
         setFieldReadOnly (ifds::FundWKN, idDataGroup, !bAMSMixOverride);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY Purchase::validateSettleSource ( const DString &settleSource,
                                          const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSettleSource"));

   Trade::commonValidateSettleSource( settleSource, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
bool Purchase::isROAApplicable (const BFDataGroupId &idDataGroup)
{
   bool bIsROAApplicable = false;

   if (isROATransType(idDataGroup))
   {
      FundDetail *pFundDetail = NULL;
      DString fund,
         clss,
         loadType;

      getField (ifds::FromFund, fund, idDataGroup, false);
      getField (ifds::FromClass, clss, idDataGroup, false);      
      if ( getWorkSession ().getFundDetail (fund, clss, idDataGroup, pFundDetail) && 
           pFundDetail != NULL )
      {
         pFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false);
         loadType.strip().upperCase();
         bIsROAApplicable = loadType == I_("FEL");
      }
   }
   return bIsROAApplicable;
}

//******************************************************************************
void Purchase::getROARelatedFields ( DString &amt,
                                     DString &amtType, 
                                     DString &currency,
                                     DString &exchRate, 
                                     const BFDataGroupId &idDataGroup)
{
   DString roaAmnt;

   getField (ifds::ROAAmount, roaAmnt, idDataGroup, false);

   double dAmt = DSTCommonFunctions::convertToDouble(roaAmnt);

   if (isROAApplicable( idDataGroup ) && dAmt > 0.0)
   {
      amt = roaAmnt;
      amtType = I_("D"); 
      exchRate = I_("1.0");
      FundDetail *pFundDetail = NULL;
      DString fund,
         clss;

      getField (ifds::FromFund, fund, idDataGroup, false );
      getField (ifds::FromClass, clss, idDataGroup, false );
      if ( getWorkSession ().getFundDetail (fund, clss, idDataGroup, pFundDetail) && 
           pFundDetail)
      {
         pFundDetail->getField ( ifds::Currency,currency,idDataGroup,false);
         currency.strip();
      }
   }
   else
   {
      Trade::getROARelatedFields ( amt,amtType,currency,exchRate, idDataGroup );
   }
}

//******************************************************************************
bool Purchase::isJumboPriceApplicable (const BFDataGroupId &idDataGroup)
{
   DString dstrJumboPriceAppl;
   getWorkSession().getOption ( ifds::JumboPriceApplicable, dstrJumboPriceAppl, BF::HOST, false);
   if ( dstrJumboPriceAppl == I_("Y") )
   {
      DString dstrLoadType;
      DString fund, clss;
      getField(ifds::FromFund, fund, idDataGroup, false );
      getField(ifds::FromClass, clss, idDataGroup, false );

      if ( !fund.empty() && !clss.empty()) 
      {
         Trade::getFundField (fund, clss, ifds::LoadType, dstrLoadType);
      }
      if (dstrLoadType == I_("FEL"))
      {

         FundDetail *pfrFundDetail = NULL;
         if ( getWorkSession ().getFundDetail ( fund, clss,idDataGroup, pfrFundDetail)  && pfrFundDetail != NULL)
         {
            DString incvActive,incvBaseOn;
            pfrFundDetail->getFeeInfoInquiryField(ifds::IncvActive, incvActive, idDataGroup, false);
            pfrFundDetail->getFeeInfoInquiryField(ifds::IncvBasedOn, incvBaseOn, idDataGroup, false);
            incvActive.strip().upperCase();
            incvBaseOn.strip().upperCase();
            if( incvActive == I_("Y") && incvBaseOn == I_("6") )
            {
               return true;
            }
         }
      }
   }
   return false;
}
//******************************************************************************
void Purchase::setDefaultPayType (const DString dstrAccountNum, 
                                  DString &payType,
                                  const BFDataGroupId &idDataGroup)
{
   bool bIsAcctDeftPayTypeAvailable = false;
   MFAccount *pMFAccount = NULL;
   DString strFundCode,
      strClassCode,
      strAcctPayTypeDef;

   getField (ifds::FromFund, strFundCode, idDataGroup, false);
   getField (ifds::FromClass, strClassCode, idDataGroup, false);

   if( !dstrAccountNum.empty() )
   {
      if( getWorkSession ().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
          pMFAccount )
      {
         pMFAccount->getDefaultPaymentTypeInfo( TRADETYPE::PURCHASE,
                                                strFundCode,
                                                strClassCode,
                                                strAcctPayTypeDef,
                                                idDataGroup );
         strAcctPayTypeDef.strip().upperCase();
         if( !strAcctPayTypeDef.empty()  )
         {
            bIsAcctDeftPayTypeAvailable = true;
         }
      }
   }

   if( !bIsAcctDeftPayTypeAvailable )
   {
      setClearingAccDefaultPayType (dstrAccountNum, payType, idDataGroup);
   }
   else
   {
      payType = strAcctPayTypeDef;
   }
}
//******************************************************************************
SEVERITY Purchase::getDefaultFundClassPayType (const DString dstrAccountNum, 
                                               DString &payType,
                                               const DString dstrFundCode,
                                               const DString dstrClassCode,
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("getDefaultFundClassPayType"));
                          
   // Separate this function from setDefaultPayType
   // To make the Fund/Class level take precedence if there is exist
   // And to avoid the effect with existing default paytype process.
   bool bIsAcctDeftPayTypeAvailable = false;
   MFAccount *pMFAccount = NULL;
   DString dstrFundClassPayType;

   if( !dstrAccountNum.empty() )
   {
      if( getWorkSession ().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
          pMFAccount )
      {
         pMFAccount->getDefaultPaymentTypeInfo( TRADETYPE::PURCHASE,
                                                dstrFundCode,
                                                dstrClassCode,
                                                dstrFundClassPayType,
                                                idDataGroup );
         dstrFundClassPayType.strip().upperCase();
         if( !dstrFundClassPayType.empty()  )
         {
            payType = dstrFundClassPayType;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Purchase::isEUSDApplicable (const BFDataGroupId &idDataGroup)
{
   DString eusdParticip;

   getWorkSession ().getOption ( ifds::EUSDParticip, 
                                 eusdParticip, 
                                 BF::HOST,
                                 false);
   return eusdParticip == I_("Y");
}

//******************************************************************************
SEVERITY Purchase::validateFromSoftCapCheck (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromSoftCapCheck"));

   DString accountNum,
      fromFund,
      fromClass;

   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   getField (ifds::FromFund, fromFund, idDataGroup, false);
   getField (ifds::FromClass, fromClass, idDataGroup, false);
   fundClassSoftCapCheck (TRADETYPE::PURCHASE, accountNum, fromFund, fromClass, idDataGroup);   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Purchase::isResidencyRequired( DString& dstrAccountNum, const BFDataGroupId &idDataGroup )
{
   bool bRetVal = false;

   MFAccount *pMFAccount = NULL;
   getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
   dstrAccountNum.strip ().stripLeading ('0');
   if ( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum,
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
SEVERITY Purchase::getFormerSpouseList( DString& strFormerSpouses, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFormerSpouseList"));

   strFormerSpouses = I_("0=N/A;");
   DString strTaxType, strDepType, strAccountNum;   
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
         getField( ifds::DepositType, strDepType, idDataGroup, false );
         if( strDepType.strip() == MARRIAGE_BREAKDOWN )
         {
            populateFormerSpouseList( strAccountNum, strFormerSpouses, idDataGroup );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
SEVERITY Purchase::validateClosedCountryForPendingTrades (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateClosedCountryForPendingTrades"));

   DString accountNum;

   getField (ifds::AccountNum, accountNum, idDataGroup);
   validateClosedCountry (accountNum, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Purchase::areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("areRESPBenefAllocationsAllowed"));

   MFAccount *pMFAccount = NULL;

   if (getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
   {
      DString taxType;
      DString depositType;

      pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
      taxType.strip().upperCase();

      getField( ifds::DepositType, depositType, idDataGroup );
      depositType.stripAll();

      if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES) && 
         DSTCommonFunctions::codeInList (depositType, RESP_BENEFALLOC_DEPOSIT))
         return true;
   }

   return false;
}

//******************************************************************************
bool Purchase::isRESPTransferAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRESPTransferAllowed"));

   MFAccount *pMFAccount = NULL;

   if (getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
   {
      DString taxType;
      DString depositType;

      pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
      taxType.strip().upperCase();

      getField( ifds::DepositType, depositType, idDataGroup );
      depositType.stripAll();

      if (DSTCommonFunctions::codeInList (taxType, RESP_TAX_TYPES) && 
         DSTCommonFunctions::codeInList (depositType, RESP_TRANSFER_DEPOSIT))
         return true;
   }

   return false;
}

//******************************************************************************
bool Purchase::isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAssociationToOriginalContribAllowed"));
   
   DString accountNum, depositType;

   bool bIsAssociationToOriginalContribAllowed = false;   
 
   getField (ifds::AccountNum, accountNum, idDataGroup, false);		
   getField (ifds::DepositType, depositType, idDataGroup, false);

   if (isRESPTradeAccount (idDataGroup))
   {    
	   bIsAssociationToOriginalContribAllowed = DSTCommonFunctions::codeInList (depositType, I_("20,35,73")); // 20-CESG Grant,35-SAGES Grant Payment,73-Additional CESG Grant
   }
   else if (isRDSPTradeAccount (idDataGroup, accountNum))
   {    
	   bIsAssociationToOriginalContribAllowed = (depositType == I_("49")) ? true : false; // 49-RDSP Grant
   }

   return bIsAssociationToOriginalContribAllowed;
}

//******************************************************************************
bool Purchase::isRDSPTransferAllowed (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRDSPTransferAllowed"));

	MFAccount *pMFAccount = NULL;

	if (getPurchaseAccount (pMFAccount, idDataGroup) <= WARNING && pMFAccount)
	{
		DString taxType;
		DString depositType;

		pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
		taxType.strip().upperCase();

		getField( ifds::DepositType, depositType, idDataGroup );
		depositType.stripAll();

		if (taxType == RDSP_TAX_TYPE && depositType == EXTERNAL_RDSP_TRANSFER_IN) // 67 - External RDSP to RDSP Transfer
			return true;
	}

	return false;
}

//******************************************************************************
SEVERITY Purchase::validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateLinkedEntity"));

   if( Trade::validateLinkedEntity(strValue, idDataGroup) <= WARNING )
   {
      DString dstrDepositType;
      getField(ifds::DepositType, dstrDepositType, idDataGroup, false);
      dstrDepositType.strip();
      if( DSTCommonFunctions::codeInList(dstrDepositType, I_("73,74,75")) )
      {
         // validation from PET0165541 QESI Transaction. Section A, 14

         AccountEntityXref *pAccountEntityXref = NULL;
         if ( getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING &&
            pAccountEntityXref )
         {
            BFObjIter iterAccountEntityXrefOut( *pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
            DString searchKey;
            AccountEntityXref::buildPartialKeyForEntityId( searchKey, strValue );

            iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

            while( !iterAccountEntityXrefOut.end() )
            {
               AccountEntityXrefObject* pObj = dynamic_cast <AccountEntityXrefObject *> (iterAccountEntityXrefOut.getObject());
               DString dstrPCGId;
               pObj->getField(ifds::RESPPCGId, dstrPCGId, idDataGroup, false);
               if( dstrPCGId.empty() || dstrPCGId == I_("0") )
               {
                  // raise rejerror 711
                  getErrMsg ( IFASTERR::BENEFICIARY_IS_NOT_LINKED_TO_PCG,
                              CND::ERR_BENEFICIARY_IS_NOT_LINKED_TO_PCG,
                              CND::ERR_BENEFICIARY_IS_NOT_LINKED_TO_PCG,
                              idDataGroup );

               }
            
               ++iterAccountEntityXrefOut;
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateAmtTypeRedCode (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeRedCode"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateAmountRedCode (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeRedCode"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateRESPTradeResidency(const DString &redcode, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRESPTradeResidency"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validatePayInstrOption(const DString& strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validatePayInstrOption"));

   if( Trade::validatePayInstrOption(strValue, idDataGroup) <= WARNING )
   {
      DString strPayType, strPayInstrOption;
      getField( ifds::TradesPayType, strPayType, idDataGroup, false);
      strPayInstrOption = strValue;
      strPayType.strip().upperCase();
      strPayInstrOption.strip().upperCase();

      if( strPayType == PAYTYPE::EFT && strPayInstrOption == I_("01") )
      {
         ADDCONDITIONFROMFILE (CND::ERR_REDIRECT_TO_PAY_ENTITY_NOT_ALLOWED );
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateTradePayTypeFundClass( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTradePayTypeFundClass"));

   DString dstrFundCode,
      dstrClassCode,
      dstrTradesPayType;

   getField (ifds::FromFund,dstrFundCode,idDataGroup,false);
   getField (ifds::FromClass,dstrClassCode,idDataGroup,false);
   getField (ifds::TradesPayType,dstrTradesPayType,idDataGroup,false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   dstrTradesPayType.strip().upperCase();

   if( dstrTradesPayType == PAYTYPE::EFT && (dstrFundCode.empty() || dstrClassCode.empty() ))
   {
      ADDCONDITIONFROMFILE (CND::EFT_PURCHASE_NOT_APPLICABLE_ALLOC_TRADE);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::payTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("payTypeRelatedChanges"));

   if (Trade::payTypeRelatedChanges (idDataGroup) <= WARNING)
   {
      DString payType;

      getField (ifds::TradesPayType, payType, idDataGroup, false);
      if (payType == PAYTYPE::EFT)
      {
       //  DString dstrSubst;
       //  BFProperties *pUseBFProperties = getFieldProperties ( ifds::PayMethod, idDataGroup );
      	//pUseBFProperties->getAllSubstituteValues ( dstrSubst );
      	//dstrSubst = removeItemFromSubtList ( dstrSubst, I_("CHQ"));
       //  setFieldAllSubstituteValues (ifds::PayMethod, idDataGroup, dstrSubst);
         
         setFieldValid (ifds::PayMethod, idDataGroup, false);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::giAttribRelatedChanges (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("giAttribRelatedChanges"));
                      
   if( isGIAAttribAllowed (idDataGroup))
   {
	    Shareholder *pShareholder = NULL;
        DString shrNum;
		DString accountNum;
		MFAccount *pMFAccount = NULL;

		getField (ifds::AccountNum, accountNum, idDataGroup, false);
		accountNum.stripLeading ('0').strip();

		if (getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && pMFAccount)
		{
			pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup);
        
			if (getWorkSession ().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING && pShareholder)
			{
               DString dstrFundRelCode;

               pShareholder->getField (ifds::FundRelnCode, dstrFundRelCode, idDataGroup, false);

			   bool bReadOnly = dstrFundRelCode == AGENT || dstrFundRelCode == EMPLOYEE ? true : false;

		   		setFieldReadOnly (ifds::CommRedRate, idDataGroup, bReadOnly); 
			}
		}

	   if (!_bInitPending)
	   {
			setFieldNoValidate ( ifds::OrderType, I_("N"), idDataGroup, false, true, true, false); //no related changes
			setFieldNoValidate ( ifds::WireOrdNum, NULL_STRING, idDataGroup, false);
			setFieldNoValidate ( ifds::AmtType, I_("D"), idDataGroup, false, true, true, false); //no related changes   
	   }

      setFieldReadOnly (ifds::OrderType, idDataGroup, true);
	  // need to confirm this with Philip:
      //setFieldReadOnly (ifds::DepositDate, idDataGroup, true);
      setFieldValid (ifds::DepositDate, idDataGroup, true);
      setFieldRequired (ifds::DepositDate, idDataGroup, false);
      setFieldRequired (ifds::WireOrdNum, idDataGroup, false);
      setFieldValid (ifds::WireOrdNum, idDataGroup, true);

	  // making GI fields mandatory:
	  setFieldRequired (ifds::IntInvestType, idDataGroup, true);
      setFieldValid (ifds::IntInvestType, idDataGroup, false);
      setFieldRequired (ifds::IntCalcMthd, idDataGroup, true);
	  setFieldValid (ifds::IntCalcMthd, idDataGroup, false);
      setFieldRequired (ifds::InvestTerm, idDataGroup, true);
      setFieldValid (ifds::InvestTerm, idDataGroup, false);
      setFieldRequired (ifds::IntCredFreq, idDataGroup, true);
      setFieldValid (ifds::IntCredFreq, idDataGroup, false);

	  setFieldRequired (ifds::ForcedRate, idDataGroup, true);
      setFieldValid (ifds::ForcedRate, idDataGroup, false);
   }  
   else
   {
		setFieldNoValidate ( ifds::IntInvestType, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::IntCalcMthd, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::InvestTerm, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::GIMaturityDate, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::IntCredFreq, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::NextIntCredDate, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::CommRedRate, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::AddlAmt, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::ForcedRate, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::IntRate, I_(""), idDataGroup, false, true, true, false); 
		//setFieldNoValidate ( ifds::InvestStatus, I_(""), idDataGroup, false, true, true, false); 

	    setFieldRequired (ifds::IntInvestType, idDataGroup, false);
        setFieldValid (ifds::IntInvestType, idDataGroup, true);
        setFieldRequired (ifds::IntCalcMthd, idDataGroup, false);
        setFieldValid (ifds::IntCalcMthd, idDataGroup, true);
        setFieldRequired (ifds::InvestTerm, idDataGroup, false);
        setFieldValid (ifds::InvestTerm, idDataGroup, true);
        setFieldRequired (ifds::IntCredFreq, idDataGroup, false);
        setFieldValid (ifds::IntCredFreq, idDataGroup, true);
		setFieldRequired (ifds::ForcedRate, idDataGroup, false);
        setFieldValid (ifds::ForcedRate, idDataGroup, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::difFundRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("difFundRelatedChanges"));
                           
   DString fundCode;

   getPurchaseFundField (ifds::FundCode, fundCode, idDataGroup);   
   
   if( isDIFFund (fundCode))
   {
	    if (!_bInitPending)
	   {
			setFieldNoValidate ( ifds::OrderType, I_("N"), idDataGroup, false, true, true, false);
			setFieldNoValidate ( ifds::WireOrdNum, NULL_STRING, idDataGroup, false);
			setFieldNoValidate ( ifds::AmtType, I_("D"), idDataGroup, false, true, true, false); //no related changes   
	   }

      //setFieldReadOnly (ifds::OrderType, idDataGroup, true);  

	  setFieldNoValidate ( ifds::WireOrdNum, NULL_STRING, idDataGroup, false);
      setFieldRequired (ifds::WireOrdNum, idDataGroup, false);
      setFieldValid (ifds::WireOrdNum, idDataGroup, true);
   }                           


   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Purchase::areAllocationsAllowed (const BFDataGroupId &idDataGroup)
{
   if( isGIAAttribAllowed (idDataGroup))
   {
      return false;
   }
   else
   {
      return Trade::areAllocationsAllowed (idDataGroup);
   }
}
//******************************************************************************
SEVERITY Purchase::validatePayStatus (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validatePayStatus" ));
   if( isValueDatePriorToTradeDate(idDataGroup) )
   {
	   DString payStatus;
	   getField (ifds::PaymentInfo, payStatus, idDataGroup, false);
	   if( payStatus == NULL_STRING)
	   {
		   getErrMsg ( IFASTERR::PAYMENT_STATUS_EMPTY,
						CND::ERR_PAYMENT_STATUS_EMPTY,
						CND::WARN_PAYMENT_STATUS_EMPTY,
						idDataGroup );
	   }
	   else if( payStatus == I_("O"))
	   {
		   getErrMsg ( IFASTERR::PAYMENT_STATUS_IS_OUTSTANDING,
						CND::ERR_PAYMENT_STATUS_IS_OUTSTANDING,
						CND::WARN_PAYMENT_STATUS_IS_OUTSTANDING,
						idDataGroup );
	   }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Purchase::validateFundForERISAAccount ( const DString &fundCode, 
                                                 const DString &classCode, 
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundForERISAAccount"));

   bool bIsERISAAccount = false;
   DString fromAccount;
   getField (ifds::AccountNum, fromAccount, idDataGroup, false);

   if (!fromAccount.empty())
   {
      MFAccount *pMFAccountFrom = NULL;

      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                          fromAccount, 
                                          pMFAccountFrom) <= WARNING && 
            pMFAccountFrom)
      {
          bIsERISAAccount = pMFAccountFrom->isERISAAccount (idDataGroup);
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
SEVERITY Purchase::validateSEGTradeEntry(const DString &accountNum,
                                         const DString &fundCode,
                                         const DString &classCode,
                                         const DString &tradeDate,
                                         const DString &validationType,
                                         const DString &transType,
                                         const DString &transID,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSEGTradeEntry"));

   if( isSEGFund (fundCode))
   {
      SEGTradeEntryValidation validationObj(*this);

      SEVERITY svrReturn =  validationObj.init(accountNum,
                                               fundCode,
                                               classCode,
                                               NULL_STRING, // account to
                                               NULL_STRING, // fund to
                                               NULL_STRING, // class to
                                               tradeDate,
                                               I_("Fund"),
                                               transType,
                                               transID);

      if( svrReturn <= WARNING )
      {
         DString strErrorCode;
         validationObj.getField(ifds::WarnCode, strErrorCode, idDataGroup, false);
         strErrorCode.strip().upperCase();

         switch( strErrorCode.asInteger())
         {
            case 1213:
            {
               DString strIDI,
                  strWarnValue1,
                  strWarnValue2;
               validationObj.getField(ifds::WarnValue1, strWarnValue1, idDataGroup, false);
               validationObj.getField(ifds::WarnValue2, strWarnValue2, idDataGroup, false);
               addIDITagValue( strIDI, I_( "CONTRACT_TYPE" ), strWarnValue1 );
               addIDITagValue( strIDI, I_( "CONTRACT_VERSION" ), strWarnValue2 );
               getErrMsg ( IFASTERR::CONTRACT_TYPE_AND_VERSION_REQUIRED,
                           CND::ERR_CONTRACT_TYPE_AND_VERSION_REQUIRED, 
                           CND::WARN_CONTRACT_TYPE_AND_VERSION_REQUIRED, 
                           idDataGroup,
                           strIDI);
            }
               break;
            case 1221:
            {
               getErrMsg ( IFASTERR::FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT,
                           CND::ERR_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT, 
                           CND::WARN_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT, 
                           idDataGroup);
            }
               break;
            default:
               break;
         }
      }
      
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************* 
SEVERITY Purchase::orderTypeRelatedChanges ( const BFDataGroupId &idDataGroup, 
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
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Purchase::validateAccountType ( MFAccount *pMFAccount, 
                                        const BFDataGroupId &idDataGroup)
{//P0186486FN09 - Employee and Agent Account Gap#8A
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
      CLASSNAME, 
      I_("validateAccountType"));

   DString depositType;
   getField (ifds::DepositType, depositType, idDataGroup, false);
   depositType.stripAll();
   
   if( depositType == EA_BONUS_PURSHASE )//64
   {
      if(pMFAccount)
      {
         bool isValid(false);
         DString acctDesignation;

         pMFAccount->getField (ifds::AcctDesignation, acctDesignation, idDataGroup);

         if(acctDesignation == CLIENT)
         {
            Shareholder *pShareholder = NULL;
            DString shrNum;

            pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup);

            if (getWorkSession ().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING &&
               pShareholder) 
            {
                  DString fundRelCodePre;

                  pShareholder->getField (ifds::FundRelnCode, fundRelCodePre, idDataGroup);
                  fundRelCodePre.strip();        

                  if( fundRelCodePre == EMPLOYEE || 
                     fundRelCodePre == AGENT)
                  {
                     isValid = true;
                  }  
            }
         }


         if(!isValid)
         {
            getErrMsg ( IFASTERR::EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT,
               CND::ERR_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT, 
               CND::WARN_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT, 
               idDataGroup);
         }
      }
   }
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::validateEmployeeAgentPurchase( const DString &fundCode, const BFDataGroupId &idDataGroup)
{ //P0186486FN09 - Employee and Agent Account Gap#8A
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateEmployeeAgentPurchase"));

   DString depositType ;

   getField (ifds::DepositType, depositType, idDataGroup, false);

   if( !fundCode.empty() && ( depositType == EA_BONUS_PURSHASE )) //64
   {
      if( !isSEGFund (fundCode))
      {
         DString fundCategory;

            getFundCategory(fundCode, fundCategory);

            TranslationTable *pTranslationTable = NULL;
            if ( getMgmtCo().getTranslationTable ( I_("FG"), pTranslationTable ) <= WARNING &&
               NULL != pTranslationTable )
            {
               DString fundDesc,strIDI;

               pTranslationTable->getDescByCode( fundCategory, fundDesc );

               addIDITagValue( strIDI, I_("FUND_CATEGORY"), fundDesc );

               getErrMsg ( IFASTERR::EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS,
                  CND::ERR_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS, 
                  CND::WARN_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS, 
                  idDataGroup,
                  strIDI);

         }
      }

   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::loadBusinessTypeSubslist( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("loadBusinessTypeSubslist"));
   
   //P0186486_FN15_The Source of Funds
   DString sourceOfFundApp;

   getWorkSession().getOption(ifds::SourceOfFundApp, sourceOfFundApp, idDataGroup, false);
   sourceOfFundApp.strip().upperCase();

   if(sourceOfFundApp == I_("Y")) 
   {       
      DString SrcOfFunds_IA_ED_List;
      getWorkSession().getOption(ifds::SrcOfFunds_IA_ED, SrcOfFunds_IA_ED_List, idDataGroup, false);
      SrcOfFunds_IA_ED_List.strip().upperCase();
      if(!SrcOfFunds_IA_ED_List.empty())
      {
         replaceSubstitutionList(SrcOfFunds_IA_ED_List,
                                 ifds::SrcOfFunds_IA, 
                                 ifds::SrcOfFund, idDataGroup);
      }
    }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
SEVERITY Purchase::RightToCancelRelatedChanges (DString &dstrRTC, const BFDataGroupId& idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("RightToCancelRelatedChanges"));
	setFieldNoValidate (ifds::RightToCancel, dstrRTC, idDataGroup, false);
	if ( dstrRTC == I_("00") )  // Right To Cancel is N/A
	{
		setFieldReadOnly (ifds::RightToCancel, idDataGroup, true); 
	}
	else
	{
		DString cancellationRightSubstList;

		BFProperties *pBFProperties = 
			getFieldProperties (ifds::RightToCancel, idDataGroup);
		if (pBFProperties)
		{
			pBFProperties->getAllSubstituteValues (cancellationRightSubstList);

			cancellationRightSubstList = 
				removeItemFromSubtList ( cancellationRightSubstList, 
				I_("00"));
			setFieldAllSubstituteValues ( ifds::RightToCancel, 
				idDataGroup, 
				cancellationRightSubstList);
		}
	}
	return GETCURRENTHIGHESTSEVERITY(); 
}
//******************************************************************************
SEVERITY Purchase::RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("RDRAdviceRelatedChanges"));
   
   DString fromAccount, fromFund, fromClass,tradeDate;
   getField (ifds::AccountNum, fromAccount, idDataGroup, false);
   getField (ifds::FromFund, fromFund, idDataGroup, false);
   getField (ifds::FromClass, fromClass, idDataGroup, false);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);

   setRDRAdviceFlag( TRADETYPE::PURCHASE,
                     fromAccount,
                     fromFund,
                     fromClass,
					 tradeDate,
                     idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
Input:Field ID ,DataGroupID
OutPut:Empty
Return:Severity
Functionality:Default all the field values with the configurtion matrix
******************************************************************************/
void Purchase::populateFieldsWithDefaultValues(const BFDataGroupId &idDataGroup, const long &lMod)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("populateFieldsWithDefaultValues"));
   //call base class first
   Trade::populateFieldsWithDefaultValues(idDataGroup, lMod );
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
void Purchase::setFieldWithDefaultValue(const BFFieldId &idField,const BFDataGroupId &idDataGroup )
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFieldWithDefaultValue"));
  //call base calss first 
   Trade::setFieldWithDefaultValue(idField, idDataGroup);
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
            setFieldNoValidate(m_FieldDefaultRule[i]._FieldID, dstrDefValue, idDataGroup, bformattedReturn, false, true, false);
            break;
         }
      }
   }	 
}

//******************************************************************************
SEVERITY Purchase::validateAnnuitantGender (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAnnuitantGender"));

   DString dstrAccount;
   getField (ifds::AccountNum, dstrAccount, idDataGroup);

   Trade::validateAnnuitantGender (idDataGroup, dstrAccount);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Purchase::setSourceOfFundsChecked (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setSourceOfFundChecked"));
   DString dstrDepositType;
   getField( ifds::DepositType, dstrDepositType, idDataGroup, false);    
   bool bReadOnly = isNew() ? !getWorkSession().hasCreatePermission ( UAF::SOURCE_OF_FUNDS_CHECKED ):
                              !getWorkSession().hasUpdatePermission ( UAF::SOURCE_OF_FUNDS_CHECKED );
   setFieldReadOnly( ifds::SourceofFundsChecked, idDataGroup, bReadOnly || PAC == dstrDepositType  );
   if( PAC == dstrDepositType)
      setFieldNoValidate( ifds::SourceofFundsChecked, NULL_STRING, idDataGroup, false);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Purchase::isExternalInstitutionTrackingEnable(const BFDataGroupId& idDataGroup)
{
   bool bReturnValue = false;

   DString strTrackTrActive,strTrackTrDepCode;
   getWorkSession().getOption2(ifds::TrackTrActive,strTrackTrActive,idDataGroup,false);
   getWorkSession().getOption2(ifds::TrackTrDepCode,strTrackTrDepCode,idDataGroup,false);
   strTrackTrActive.strip().upperCase();
   strTrackTrDepCode.strip().upperCase();

   if (!strTrackTrActive.empty() && strTrackTrActive == I_("Y") && !strTrackTrDepCode.empty())
   {
      DString depType;

      getField (ifds::DepositType, depType, idDataGroup, false);
      depType.strip().upperCase();
      bReturnValue = DSTCommonFunctions::codeInList (depType, strTrackTrDepCode);
   }

   return bReturnValue;
}
//****************************************************************************************************************************
SEVERITY Purchase::initPriceTypesList(const BFDataGroupId &idDataGroup)
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

//******************************************************************************
SEVERITY Purchase::validateRDSPTrade (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRDSPTrade"));

	DString dstrAccountNum;
	getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);	

	if (!dstrAccountNum.empty())
	{
		Trade::validateRDSPTrade (idDataGroup, dstrAccountNum);
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Purchase.cpp-arc  $
// 
//    Rev 1.233   Jul 26 2012 10:47:16   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.232   Jul 02 2012 19:03:46   wp040132
// P0199883_FN01_Cancellation Rights - Right To Cancel
// 
//    Rev 1.231   May 16 2012 05:14:04   panatcha
// IN2929301 -  Agent and Employee
// 
//    Rev 1.230   May 04 2012 11:29:30   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.229   Apr 23 2012 15:50:50   wp040027
// Sync up: R12.3P0188394_Value date incorrect in ED & PW Non PF fund class
// 
//    Rev 1.228   Apr 20 2012 03:43:20   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.227   Apr 10 2012 05:03:36   panatcha
// P0186486FN09 - Employee and Agent Account Gap#8A
// 
//    Rev 1.226   Mar 05 2012 12:12:30   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.225   Feb 03 2012 16:37:06   jankovii
// Sync up: IN 2829155 - P0186477FN03 - Commission Reduction is N/A for agent or employee
// 
//    Rev 1.224   Feb 03 2012 15:16:16   jankovii
// Sync up: GIA related changes.
// 
//    Rev 1.223   Jan 26 2012 15:00:04   wp040027
// P0188394_Performance Fees - Review Comments Incorporated
// 
//    Rev 1.222   Jan 25 2012 15:56:36   jankovii
// Sync up: IN 2820320 - Rel12.2 PET0186477 - DIF Trade Entry Screen Issues
// 
//    Rev 1.221   Jan 25 2012 13:59:32   jankovii
// Sync up: IN 2820320 - Rel12.2 PET0186477 - DIF Trade Entry Screen Issues
// 
//    Rev 1.220   Jan 20 2012 15:53:26   wp040027
// P0188394_Performance Fees - Order Entry
// 
//    Rev 1.219   Nov 30 2011 17:57:44   dchatcha
// P0186477/FN03 - GIA - Purchase
// 
//    Rev 1.218   Nov 27 2011 19:42:04   popescu
// INA Commission Work
// 
//    Rev 1.217   Oct 19 2011 22:22:38   popescu
// P0186477/03 - GIA Trading Money In - prep work
// 
//    Rev 1.216   Aug 03 2011 11:27:10   wp040027
// P0186774 - Mutual Fund Order Processing
// 
//    Rev 1.215   Jul 20 2011 18:03:32   dchatcha
// P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
// 
//    Rev 1.214   Mar 11 2011 11:21:52   kitticha
// IN2450642 - Modify program to support fund-class hierarchy.
// 
//    Rev 1.213   Mar 11 2011 17:54:52   dchatcha
// Synch up: IN#2447057 - R11.3PR-PET0179308FN01-Cannot creat new EFT Purchase bank at trade, force FileProcessing field on trade banking get update when there is a change at trade level. 
// 
//    Rev 1.212   Mar 07 2011 08:44:18   kitticha
// IN2450642 - Fund validation by default sub paytype & EFT Purchase Cheque.
// 
//    Rev 1.211   Feb 18 2011 05:21:50   kitticha
// PET0165541_FN12_IN2385316 - Default the assisted contribution amount for ED 78(same as PW Q1).
// 
//    Rev 1.210   Feb 07 2011 18:31:08   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.209   Jan 31 2011 18:43:16   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.208   May 27 2010 06:09:16   kitticha
// PETP0165541 FN02 QESI Phase2.
// 
//    Rev 1.207   May 26 2010 07:59:22   kitticha
// PET0165541 FN01 QESI Trading - Tax Year default value fix.
// 
//    Rev 1.206   May 18 2010 11:51:08   dchatcha
// RESP - Modify condition description to depend on trade type.
// 
//    Rev 1.205   May 14 2010 06:49:54   dchatcha
// PET0165541 FN01 QESI RESP Trading, view 405 is not called.
// 
//    Rev 1.204   May 12 2010 07:55:36   popescu
// RESP - Added TaxYear and related validation
// 
//    Rev 1.203   May 04 2010 10:17:44   jankovii
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.202   Apr 22 2010 07:29:50   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.201   Apr 21 2010 14:00:32   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.200   Apr 21 2010 01:20:52   popescu
// RESP-QESI Resp transfer screen
// 
//    Rev 1.199   Apr 14 2010 23:57:46   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.198   Apr 14 2010 09:40:40   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.197   Mar 27 2010 19:16:28   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.196   Mar 08 2010 13:18:30   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
// 
//    Rev 1.195   Aug 14 2009 14:12:12   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.194   Aug 13 2009 15:58:54   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.193   Aug 11 2009 13:54:36   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.192   27 Jul 2009 15:13:44   popescu
// Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
// 
//    Rev 1.191   Jun 26 2009 06:22:50   kitticha
// IN#1738640 - R94 - Country Schedule - Cannot modify TX even when FundFrom and FundTo are same
// 
//    Rev 1.190   15 Jun 2009 08:38:44   popescu
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
// 
//    Rev 1.189   10 Jun 2009 18:35:06   popescu
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
// 
//    Rev 1.188   Jun 09 2009 05:45:48   kitticha
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
// 
//    Rev 1.187   Mar 13 2009 00:03:18   wutipong
// IN1358908 -- Correct 'MAKEFROMEAUTOPROMOTE' call in 'getFormerSpouseList()' function.
// 
//    Rev 1.186   Nov 28 2008 14:40:46   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.185   Nov 03 2008 22:11:48   phiwponp
// IN 1419539 - Due to unit testing of Incident 1337808 Add error 761, unable to process by an AMS account.
// 
//    Rev 1.184   06 Oct 2008 13:19:26   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.183   01 Oct 2008 11:57:04   popescu
// Check in for incident 1419539	
// 
//    Rev 1.182   15 Apr 2008 12:09:50   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.181   08 Nov 2007 16:16:28   kovacsro
// IN#1054798 / PET2360FN00 - no cash purchases for LRSP, LIRA, LIF, LRIF
// 
//    Rev 1.180   Oct 08 2007 12:16:34   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.179   23 Jul 2007 16:49:46   popescu
// PET 2360 - FN 20 - GAP 20 Soft cap functionality
// 
//    Rev 1.178   May 04 2007 13:56:58   jankovii
// PET 2321 FN01 - MT54X Default Pay Type.
// 
//    Rev 1.177   Nov 02 2006 11:52:04   ZHANGCEL
// PET2258 FN01 -- Deal Date Deal Time related changes
// 
//    Rev 1.176   Oct 30 2006 17:03:22   jankovii
// PET 2185 FN04 - Trade restrictions.
// 
//    Rev 1.175   Apr 06 2006 10:42:18   jankovii
// PET 1334 Alternative Product. If view 135 returns and error still initalize data.
// 
//    Rev 1.174   Feb 28 2006 11:19:56   popescu
// /Incident# 554580 - remove current validation for SWIFT monetary amount trades
// 
//    Rev 1.173   Jan 19 2006 13:53:32   AGUILAAM
// PET1295_FN01: addl enhancements - do not display MCH/SecRec fields if not supported by client
// 
//    Rev 1.172   Nov 29 2005 15:24:08   AGUILAAM
// PET_1228_FN02: EUSD Phase 2
// 
//    Rev 1.171   Oct 11 2005 16:49:20   porteanm
// Incident 418404 - Source of Fund for a pending PAC.
// 
//    Rev 1.170   Sep 28 2005 17:24:22   popescu
// Incident #406322 - called Trade::inHouseBroker, cached view 90 call.
// 
//    Rev 1.169   Aug 22 2005 16:54:56   fengyong
// Incident 373761 - ValidateAcqOption only when have a valid fund
// 
//    Rev 1.168   Jul 29 2005 15:19:00   Yingbaol
// PET1203,FN04: Change ROAAmount to updatable if AcqFeeOption changes.
// 
//    Rev 1.167   Jul 28 2005 16:07:34   ZHANGCEL
// PET1203 FN04 --  Fix bug in doApplyRelatedChanges
// 
//    Rev 1.166   Jul 26 2005 11:13:04   Yingbaol
// PET1203,FN04: add another condition for AcqFeeOption
// 
//    Rev 1.165   Jul 26 2005 10:33:40   ZHANGCEL
// PET1203 FN04 -- Bug fix for in doApplyRelatedChanges
// 
//    Rev 1.164   Jul 18 2005 14:55:26   ZHANGCEL
// PET1203 FN04 -- Bug fix for Jumbo Pricing enhancement
// 
//    Rev 1.163   Jul 15 2005 16:46:14   ZHANGCEL
// PET1203 FN04 -- Jumbo Pricing enhancement
// 
//    Rev 1.162   Jul 15 2005 16:25:50   popescu
// Incident 356593 - fix trade crash if default allocations/ams are available for an account, snch-up from 63.0.0
// 
//    Rev 1.161   Jul 15 2005 16:05:14   ZHANGCEL
// PET1203 FN04 -- Jumbo Pricing enhancement
// 
//    Rev 1.160   Jul 08 2005 11:19:10   popescu
// PET1171 EUSD 1B - Call validateEUSDBackDates().
// 
//    Rev 1.159   Jul 08 2005 11:17:26   popescu
// Incident# 350901 - do not show th split commission tab if split not available
// 
//    Rev 1.158   Jul 07 2005 11:33:34   porteanm
// PET1171 EUSD 1B - Call validateEUSDBackDates().
// 
//    Rev 1.157   Jul 04 2005 13:25:48   porteanm
// Incident 345808 - Deposit Type combo loading only descriptions.
// 
//    Rev 1.156   Jun 30 2005 15:40:22   popescu
// Incident # 346892 - fee should not be reset when modifying a split commission in pending mode. Clearing the ROAAmount should be done only if the field is available for business
// 
//    Rev 1.155   Jun 29 2005 11:56:34   popescu
// Incident# 342270 - guard the refresh of split commissions with a boolean for fund related changes; save several view calls to 158
// 
//    Rev 1.154   Jun 22 2005 14:08:36   popescu
// PET 1117/08 - renamed method activestRelatedChanges to thirdPartyFundRelatedChanges
// 
//    Rev 1.153   Jun 10 2005 10:35:30   popescu
// PET 1117/08 - cached the fund fee sponsor model list at the Trade level for better perfomance
// 
//    Rev 1.152   Jun 01 2005 17:48:20   popescu
// PET 1203/05 - fixed warning message in getROAFields
// 
//    Rev 1.151   Jun 01 2005 17:40:10   popescu
// PET 1203/05 - after code review minor changes - mainly formatting and changed getROAFields access to protected
// 
//    Rev 1.150   May 18 2005 16:19:40   porteanm
// PET1203 FN05 - Class B NAV Share Lots - added doValidateAll().
// 
//    Rev 1.149   May 18 2005 09:03:32   yingbaol
// PET1203,FN01 Commission-Class A enhancement
// 
//    Rev 1.148   May 11 2005 16:30:48   porteanm
// PET1203 FN05 - Class B NAV Share Lots.
// 
//    Rev 1.147   May 02 2005 12:56:08   porteanm
// PET1156 - RESP warning message for Deposit Type 17.
// 
//    Rev 1.146   May 02 2005 11:53:28   porteanm
// Incident 290690 - Source Of Fund.
// 
//    Rev 1.145   Apr 29 2005 13:27:18   porteanm
// PET1156 - undid RESP warning message for Deposit Type 17.
// 
//    Rev 1.144   Apr 28 2005 13:50:22   porteanm
// PET1156 - RESP warning message for Deposit Type 17.
// 
//    Rev 1.143   Apr 06 2005 19:17:32   popescu
// Incident #282933, missed req - raise a warning if user changes from acq fee option - model got changed 
// 
//    Rev 1.142   Mar 29 2005 18:07:38   popescu
// Incident# 273841, missed requirment, set the other confirm type to 1-Create PUEV note if fund and account are PUEV capable for an Investro network id.
// 
//    Rev 1.141   Mar 24 2005 10:40:26   popescu
// Incident # 260181, split commissions not applicable for ED's with deposittypes 9,10,18
// 
//    Rev 1.140   Mar 15 2005 15:40:42   aguilaam
// IN_260181: split commissions not applicable for ED's with deposittypes 9,10,18
// 
//    Rev 1.139   Mar 10 2005 11:38:58   porteanm
// Incident 243157/243387 - SettleSource validation.
// 
//    Rev 1.138   Mar 08 2005 17:49:52   popescu
// PET 1117/06, checked the read permission for order type
// 
//    Rev 1.137   Mar 03 2005 15:53:58   popescu
// Incident# 257570, removed the old default rules for paytype for Purchases
// 
//    Rev 1.136   Mar 03 2005 08:29:22   popescu
// Incident# 251618, fixed validation for 'regular' acq fee option; it should only happen if unitcalc of the fund is 'D'
// 
//    Rev 1.135   Feb 25 2005 18:36:52   popescu
// Incident# 251618, restored the 'regular' subst value for acq fee option, and raised error if user chooses regular for a shareholder that has fee model and fund is FEL; synch-up from release 59.0.4
// 
//    Rev 1.134   Feb 04 2005 13:53:54   popescu
// 234691, allocated purchase should be not allowed to be placed if amout is zero, Rel_59.0.2, synch-up 1.132.1.1
// 
//    Rev 1.133   Feb 01 2005 11:45:02   popescu
// PET 1117/66/67/68, API validations for SWIFT/Investro/Pwld
// 
//    Rev 1.128   Jan 19 2005 14:48:54   popescu
// PTS 10037380, less then minimum units required rule, compared the 'double' amounts, not strings!
// 
//    Rev 1.127   Jan 06 2005 14:24:54   popescu
// PTS 10037580, acq fee option default when amount type 'Amount' should be 'BuyAtNAV' = 2, and if user changes amount type to units, the default for AcqFeeOption should be read from the fund sponsor fee model
// 
//    Rev 1.126   Jan 04 2005 17:10:46   popescu
// PTS 10037456, consider deposit 9 and 10 -bearer certificate when setting the default values for aggregate option
// 
//    Rev 1.125   Dec 30 2004 15:11:00   popescu
// PTS 10037326, invalidate amount field at trade level, rather then purchase
// 
//    Rev 1.124   Dec 30 2004 12:41:06   popescu
// PTS 10037260, moved check whether fund sponsor fee model  exists at Trade CBO level, and called the validation for redemptions/purchases as well, missed req: PET1117.FN6.R3.7. 0
// 
//    Rev 1.123   Dec 30 2004 10:45:36   popescu
// PTS 10036944, added adtional restrictions for updating the order type field. System checks generic control UpdOrdType and user permission for update controlled by ids 46  for purchases and 45 for redemptions.
// 
//    Rev 1.122   Dec 29 2004 18:41:48   popescu
// PTS 10037326, allocations should not trigger amount is zero error if booking a purchase. Also, fixed allocations list selection.
// 
//    Rev 1.121   Dec 29 2004 11:21:58   popescu
// PTS 10037302, do not validate amount precision for amount type units
// 
//    Rev 1.120   Dec 24 2004 14:03:58   popescu
// PTS 10037260, added missed validation against fund code; if fee model code exists at account/shareholder level and fund has fund sponsor then a fund sponsor fee model should be set-up
// 
//    Rev 1.119   Dec 24 2004 08:54:54   popescu
// PTS 10037240, minor source edit  fix
// 
//    Rev 1.118   Dec 23 2004 18:09:02   popescu
// PTS 10037240, fix validation related to group contribution limits
// 
//    Rev 1.117   Dec 17 2004 17:35:36   popescu
// PET 1117/56, removed validation AcqFeeOption -DiscountMode, in relation with AntiDilutionCalc generic control and ADL Fee applicability 
// 
//    Rev 1.116   Dec 15 2004 15:55:30   popescu
// PET 1117/06, fixes related to condition rates scale type/ acq fee option defaults
// 
//    Rev 1.115   Dec 15 2004 10:40:28   popescu
// PET 1117/06, acq fee option default overridden only if unitscal-56='d'
// 
//    Rev 1.114   Dec 13 2004 14:17:54   popescu
// PET 1117/56, AcqFeeOption, should always be defaulted to '0' Regular, and should be set to read only if FundSponsor FeeModel does not exist
// 
//    Rev 1.113   Dec 11 2004 11:47:34   popescu
// PET 1117/56 more fixes, pending trade mods
// 
//    Rev 1.112   Dec 07 2004 01:37:38   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.111   Dec 02 2004 18:22:58   popescu
// PET 1117/06/56, trades processing/fees processing
// 
//    Rev 1.110   Dec 01 2004 15:44:44   popescu
// PET 1117/56 fees processing, calculate the discount rate
// 
//    Rev 1.109   Nov 30 2004 20:09:58   popescu
// PET 1117/06
// 
//    Rev 1.108   Nov 29 2004 20:30:24   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.107   Nov 27 2004 21:18:54   popescu
// PET 1117/06, trades processing
// 
//    Rev 1.106   Nov 24 2004 21:35:58   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.105   Nov 22 2004 13:09:16   popescu
// PET 1117/56. fees processing
// 
//    Rev 1.104   Nov 19 2004 14:17:16   popescu
// PET 1117/56 third party processing
// 
//    Rev 1.103   Nov 14 2004 14:51:16   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.102   Nov 06 2004 00:42:12   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.6   Nov 04 2004 17:38:18   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.5   Nov 02 2004 19:19:28   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.4   Oct 28 2004 18:23:48   popescu
// PET 1117/06
// 
//    Rev 1.3   Oct 27 2004 11:26:54   popescu
// PET 1117/06
// 
//    Rev 1.2   Oct 22 2004 19:58:48   popescu
// PET 1117/06, work in progress...
// 
//    Rev 1.1   Oct 21 2004 06:29:08   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.0   Oct 01 2004 19:29:50   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
