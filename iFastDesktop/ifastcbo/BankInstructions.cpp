//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : BankInstructions.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 2/9/01
//
// ^CLASS    : BankInstructions
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "bankinstructions.hpp"
#include "bankinstructionslist.hpp"
#include "currencylist.hpp"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include <ifastdataimpl\dse_dstc0052_vw.hpp>
#include <ifastdataimpl\dse_dstc0100_req.hpp>
#include <ifastdataimpl\dse_dstc0100_vw.hpp>
#include "distributionbankinstructions.hpp"
#include "dstcommonfunction.hpp"
#include "dynamicsublistholder.hpp"
#include "financialinstitution.hpp"
#include "financialinstitutionlist.hpp"
#include "financialinstitutiontransitlist.hpp"
#include "groupfundlist.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "rrifbankinstructions.hpp"
#include "systematicbankinstructions.hpp"
#include "settlementtradebankinstructions.hpp"
#include "tradebankinstructions.hpp"
#include "investorauthorizationlist.hpp"
#include "matsweepinstrbank.hpp"
#include "acctcommitbank.hpp"
#include "ContractMatInstrBank.hpp"
#include "Shareholder.hpp"
#include <algorithm>

namespace
{
   // Trace literals
   const I_CHAR *  EFT_REDEMPTION_BANK_CODE              = I_( "07" );
   const I_CHAR *  ALTERNATIVE_EFT_REDEMPTION_BANK_CODE  = I_( "36" );
   const I_CHAR *  BANKING_LEVEL                         = I_( "1" );
}

namespace CND
{  // Conditions used
   extern const long ERR_BANK_COUNTRY_CODE_REQUIRED;
   extern const long WARN_BANK_COUNTRY_CODE_REQUIRED;
   extern const long ERR_DIRECT_DEPST_SHRHLDR_ONLY;
   extern const long WARN_DIRECT_DEPST_SHRHLDR_ONLY;
   extern const long WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT;
   extern const long ERR_DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY;
   extern const long WARN_DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY;
   extern const long ERR_DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY;
   extern const long WARN_DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY;
   extern const long ERR_DIRECT_DEPST_BANK_REQUIRED;
   extern const long ERR_DIRCT_DEPT_PAYTYPE_FOR_DIRCT_DEPT_BANK_ONLY;
   extern const long ERR_DIRCT_DEPT_PAYTYPE_FOR_CLNT_NON_REGIS_ONLY;
   extern const long WARN_INVESTOR_AUTHORIZATION_INFO_MISSING;
   extern const long ERR_INVESTOR_AUTHORIZATION_INFO_MISSING;
   extern const long ERR_DIRECT_DPST_BANK_BEFORE_ACCT_EFFDATE;
   extern const long ERR_WRONG_VERIFY_STATUS;
   extern const long ERR_BANK_IN_USE;
   extern const long WARN_BANK_IN_USE;
   extern const long ERR_UNVERIFIED_BANK;
   extern const long WARN_UNVERIFIED_BANK;
   extern const long WARN_EFFECTIVE_DATE_AFTER_STOP_DATE;
   extern const long ERR_BSB_FORMAT_IS_INCORRECT;
   extern const long ERR_BSB_BANK_ACCT_AUD_FORMAT_IS_INCORRECT;
   extern const long ERR_BSB_BANK_ACCT_FOREIGN_FORMAT_IS_INCORRECT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TemplateNumber;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankType;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankUpd;
   extern CLASS_IMPORT const BFTextFieldId ACHSavingsPlan;
   extern CLASS_IMPORT const BFTextFieldId ACHPAC;
   extern CLASS_IMPORT const BFTextFieldId ACHSWP;
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
   extern CLASS_IMPORT const BFTextFieldId InstAddressCB;
   extern CLASS_IMPORT const BFTextFieldId InstAddress;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId RunMode;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFDecimalFieldId BankLayout;
   extern CLASS_IMPORT const BFTextFieldId PayTypeFileProc;
   extern CLASS_IMPORT const BFTextFieldId ACHDividend;
   extern CLASS_IMPORT const BFTextFieldId ACHCommission;
   extern CLASS_IMPORT const BFTextFieldId ACHTrailerFee;
   extern CLASS_IMPORT const BFTextFieldId ACHRedemption;
   extern CLASS_IMPORT const BFNumericFieldId DefaultBankInstCode; 
   extern CLASS_IMPORT const BFTextFieldId ACHAdminFee;
   extern CLASS_IMPORT const BFTextFieldId ACHPurch;
   extern CLASS_IMPORT const BFTextFieldId EFTRedemptionXEdit;
   extern CLASS_IMPORT const BFTextFieldId SwitchBanks;
   extern CLASS_IMPORT const BFTextFieldId IsDefault;

   // Investor Authorization fields
   extern CLASS_IMPORT const BFTextFieldId DirectDepositBankApplicable;
   extern CLASS_IMPORT const BFTextFieldId BankAcctUseCodeCurrType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFNumericFieldId AcctAuthRid;

   extern CLASS_IMPORT const BFTextFieldId EFTPurchaseXEdit;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   extern CLASS_IMPORT const BFTextFieldId PayInstrOption;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboDefault;
   extern CLASS_IMPORT const BFTextFieldId TradeFileProcessorDefault;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const SYSTEMATIC;
   extern CLASS_IMPORT I_CHAR * const RRIF;
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT;
   extern CLASS_IMPORT I_CHAR * const FUND;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
   extern CLASS_IMPORT I_CHAR * const CLIENT;
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING;
   extern CLASS_IMPORT I_CHAR * const TRADE;
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const FUND_GROUP;
   extern CLASS_IMPORT I_CHAR * const FUND_SPONSOR;
   extern CLASS_IMPORT I_CHAR * const REG_AGENT;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const MATURITY_INSTRUCTIONS;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_COMMITMENT;
}

namespace BANKENTITY
{
   extern I_CHAR * const CLIENT;
   extern I_CHAR * const BROKER;
   extern I_CHAR * const BRANCH;
   extern I_CHAR * const SALESREP;
   extern I_CHAR * const FUND_CLASS;
   extern I_CHAR * const SHAREHOLDER;
   extern I_CHAR * const FUND;
   extern I_CHAR * const FUND_GROUP;
   extern I_CHAR * const FUND_SPONSOR;
   extern I_CHAR * const ACCOUNT;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const SAVING_PLAN;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,             Group Flags 
   {ifds::ShrNum,                   BFCBO::NONE,                  0}, 
   {ifds::RunMode,                  BFCBO::NONE,                  0}, 
   {ifds::SwiftCode,                BFCBO::NONE,                  0}, 
   {ifds::RefNumber,                BFCBO::NONE,                  0}, 
   {ifds::BankAcctNum,              BFCBO::REQUIRED,              0}, 
   {ifds::BankAcctName,             BFCBO::NONE,                  0}, 
   {ifds::BankAcctType,             BFCBO::NONE,                  0}, 
   {ifds::BankAcctCurrency,         BFCBO::REQUIRED,              0}, 
   {ifds::EffectiveDate,            BFCBO::REQUIRED,              0}, 
   {ifds::StopDate,                 BFCBO::REQUIRED,              0}, 
   {ifds::PayReason1,               BFCBO::NONE,                  0}, 
   {ifds::PayReason2,               BFCBO::NONE,                  0}, 
   {ifds::AcctUseCode,              BFCBO::REQUIRED,              0}, 
   {ifds::InstName,                 BFCBO::NONE,                  0}, 
   {ifds::InstAddress,              BFCBO::NONE,                  0}, 
   {ifds::BankAcctVer,              BFCBO::NONE,                  0}, 
   {ifds::BankAcctRid,              BFCBO::NONE,                  0}, 
   {ifds::BankIdType,               BFCBO::REQUIRED,              0}, 
   {ifds::BankIdValue,              BFCBO::REQUIRED,              0}, 
   {ifds::TransitNo,                BFCBO::NONE,                  0}, 
   {ifds::BankIdTypeCB,             BFCBO::NONE,                  0}, 
   {ifds::BankIdValueCB,            BFCBO::NONE,                  0}, 
   {ifds::TransitNoCB,              BFCBO::NONE,                  0}, 
   {ifds::InstNameCB,               BFCBO::NONE,                  0}, 
   {ifds::InstAddressCB,            BFCBO::NONE,                  0}, 
   {ifds::TemplateNumber,           BFCBO::NONE,                  0}, 
   {ifds::ACHProcessor,             BFCBO::NONE,                  0}, 
   {ifds::BankPostal,               BFCBO::NONE,                  0}, 
   {ifds::BankCountry,              BFCBO::NONE,                  0}, 
   {ifds::BankContact,              BFCBO::NONE,                  0}, 
   {ifds::BankPostalCB,             BFCBO::NONE,                  0}, 
   {ifds::BankCountryCB,            BFCBO::NONE,                  0}, 
   {ifds::BankContactCB,            BFCBO::NONE,                  0}, 
   {ifds::FFC,                      BFCBO::NONE,                  0}, 
   {ifds::FFC1,                     BFCBO::NONE,                  0}, 

   {ifds::BankAddr1,                BFCBO::NONE,                  0}, 
   {ifds::BankAddr2,                BFCBO::NONE,                  0}, 
   {ifds::BankAddr3,                BFCBO::NONE,                  0}, 
   {ifds::BankAddr4,                BFCBO::NONE,                  0}, 
   {ifds::BankAddr5,                BFCBO::NONE,                  0}, 

   {ifds::BankAddrCB1,              BFCBO::NONE,                  0}, 
   {ifds::BankAddrCB2,              BFCBO::NONE,                  0}, 
   {ifds::BankAddrCB3,              BFCBO::NONE,                  0}, 
   {ifds::BankAddrCB4,              BFCBO::NONE,                  0}, 
   {ifds::BankAddrCB5,              BFCBO::NONE,                  0}, 
   {ifds::CorrespBankId,            BFCBO::NONE,                  0}, 
   {ifds::BankId,                   BFCBO::NONE,                  0}, 

   {ifds::ModDate,                  BFCBO::NONE,                  0}, 
   {ifds::Username,                 BFCBO::NONE,                  0}, 
   {ifds::ModUser,                  BFCBO::NONE,                  0}, 
   {ifds::ProcessDate,              BFCBO::NONE,                  0}, 

   {ifds::DistribDetlRid,           BFCBO::NONE,                  0}, 
   {ifds::PayMethod,                BFCBO::NONE,                  0}, 
   {ifds::TransType,                BFCBO::NONE,                  0}, 
   {ifds::FundCode,                 BFCBO::CALCULATED_FIELD,      0}, 
   {ifds::ClassCode,                BFCBO::CALCULATED_FIELD,      0}, 
   {ifds::BankInstrType,            BFCBO::CALCULATED_FIELD,      0}, 
   {ifds::EFTRedemptionXEdit,       BFCBO::IMMEDIATE_VALIDATION,  0}, 
   {ifds::EFTPurchaseXEdit,         BFCBO::IMMEDIATE_VALIDATION,  0}, 
   {ifds::BankAcctUseCodeCurrType,  BFCBO::IMMEDIATE_VALIDATION,  0}, 
   {ifds::VerifyStat,               BFCBO::NONE,                  0}, 
   {ifds::AcctID,                   BFCBO::NONE,                  0},
   {ifds::EffectiveStopDate,        BFCBO::IMMEDIATE_VALIDATION,  0}, 
   {ifds::PayInstrOption,           BFCBO::NONE,				  0},
   {ifds::rxAcctNum,                BFCBO::NONE,                  0}, 
   {ifds::rxBankingEntity,          BFCBO::NONE,                  0},
   {ifds::AccountNum,               BFCBO::NONE,                  0},
};

const BFFieldId fieldsInCorresBank[]=
{
   ifds::BankIdTypeCB,
   ifds::BankIdValueCB,
   ifds::TransitNoCB,
   ifds::InstNameCB,
   ifds::InstAddressCB,
   ifds::BankPostalCB,
   ifds::BankCountryCB,
   ifds::BankContactCB,
   ifds::BankAddrCB1,
   ifds::BankAddrCB2,
   ifds::BankAddrCB3,
   ifds::BankAddrCB4,
   ifds::BankAddrCB5,
   ifds::CorrespBankId,
};

const BFFieldId fieldsInBeneficialBank[]=
{
   ifds::BankIdType,
   ifds::BankIdValue,
   ifds::TransitNo,
   ifds::InstName,
   ifds::InstAddress,
   ifds::BankPostal,
   ifds::BankCountry,
   ifds::BankContact,
   ifds::BankAddr1,
   ifds::BankAddr2,
   ifds::BankAddr3,
   ifds::BankAddr4,
   ifds::BankAddr5,
   ifds::BankId,
};

const BFFieldId fieldsInBankOption[]=
{
   ifds::BankAcctType,
   ifds::BankAcctCurrency,
   ifds::EffectiveDate,
   ifds::StopDate,
   ifds::PayMethod,
   ifds::ACHProcessor,
   ifds::BankContact,
   ifds::BankContactCB,
   ifds::VerifyStat,
};

const BFFieldId fieldsInBankGenInfo[]=
{
   ifds::BankAcctNum,
   ifds::BankAcctName,
};

const BFFieldId fieldsInBankFFC[]=
{
   ifds::FFC,
   ifds::FFC1,
   ifds::PayReason1,
   ifds::PayReason2,
};

namespace
{
   I_CHAR *  NO   = I_( "N" );
   I_CHAR *  YES  = I_( "Y" );
}

static const int numFieldsInCorresBank = sizeof (fieldsInCorresBank) / sizeof (BFFieldId);
static const int numFieldsInBeneficialBank = sizeof (fieldsInBeneficialBank) / sizeof (BFFieldId);
static const int numFieldsInBankOption = sizeof (fieldsInBankOption) / sizeof (BFFieldId);
static const int numFieldsInBankGenInfo = sizeof (fieldsInBankGenInfo) / sizeof (BFFieldId);
static const int numFieldsInBankFFC = sizeof (fieldsInBankFFC) / sizeof (BFFieldId);

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME                  = I_ ( "BankInstructions" );
   const I_CHAR * const NON_REGISTERED_TAX_TYPE    = I_ ( "0" );
   const I_CHAR * const CLIENT_ACCOUNT_DESIGNATION = I_ ( "1" );
   const I_CHAR * const CANADIAN_BANK              = I_ ( "03" );
   const I_CHAR * const CANADIAN_DOLLAR_LIST       = I_ ( "CDN,CAD" );
   const I_CHAR * const UNVERIFIED                 = I_ ( "02" );
   const I_CHAR * const VERIFIED                   = I_ ( "01" );
}

namespace AcctUseCode
{
   extern CLASS_EXPORT const I_CHAR * const DEFAULT                  = I_ ("00");
   extern CLASS_EXPORT const I_CHAR * const COMMISSION               = I_ ("01");
   extern CLASS_EXPORT const I_CHAR * const COMM_CLEAR               = I_ ("04");
   extern CLASS_EXPORT const I_CHAR * const EFT_REDEMPTION           = I_ ("07");
   extern CLASS_EXPORT const I_CHAR * const ALT_EFT_REDEMPTION       = I_ ("36");
   extern CLASS_EXPORT const I_CHAR * const EFT_PURCHASE             = I_ ("11");
   extern CLASS_EXPORT const I_CHAR * const EFT                      = I_ ("11");
   extern CLASS_EXPORT const I_CHAR * const ABSATZMELDUNG            = I_ ("12");
   extern CLASS_EXPORT const I_CHAR * const FUND_DEBIT               = I_ ("15");
   extern CLASS_EXPORT const I_CHAR * const EFT_DIVIDEND             = I_ ("16");
   extern CLASS_EXPORT const I_CHAR * const INTERNATIONAL_WIRE       = I_ ("24");
   extern CLASS_EXPORT const I_CHAR * const DIVIDEND                 = I_ ("28");
   extern CLASS_EXPORT const I_CHAR * const TRAILER_FEE              = I_ ("29");
   extern CLASS_EXPORT const I_CHAR * const PAC                      = I_ ("31");
   extern CLASS_EXPORT const I_CHAR * const SWP                      = I_ ("32");
   extern CLASS_EXPORT const I_CHAR * const MANAGEMENT_COMPANY       = I_ ("33");
   extern CLASS_EXPORT const I_CHAR * const DIRECT_TRADING           = I_ ("35");
   extern CLASS_EXPORT const I_CHAR * const DIRECT_DEPOSIT           = I_ ("37");
   extern CLASS_EXPORT const I_CHAR * const ALT_EFT_PURCHASE         = I_ ("38");
   extern CLASS_EXPORT const I_CHAR * const FUND_CREDIT              = I_ ("39");
   extern CLASS_EXPORT const I_CHAR * const RRIF                     = I_ ("1000");

}

namespace TransType
{
   extern const I_CHAR * const ADMIN_FEE        = I_("AFE");
   extern const I_CHAR * const COMMISSION       = I_("CO");
   extern const I_CHAR * const TRAILER_FEE      = I_("TF");
   extern const I_CHAR * const EFT_DIVIDEND     = I_("ID"); 
   extern const I_CHAR * const PAC              = I_("PAC");
   extern const I_CHAR * const PURCHASE         = I_("PUR");
   extern const I_CHAR * const REDEMPTION       = I_("RED");
   extern const I_CHAR * const SWP              = I_("SWP");
}

namespace FI_CATEGORY
{
   extern I_CHAR * const BANK;
   extern I_CHAR * const BANK_TRANSIT;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const BANK_COUNTRY_CODE_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const DIRECT_DEPST_SHRHLDR_ONLY;
   extern CLASS_IMPORT I_CHAR * const DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY;
   extern CLASS_IMPORT I_CHAR * const DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY;
   extern CLASS_IMPORT I_CHAR * const INVESTOR_AUTHORIZE_FOR_DIRECT_DEPOSIT_BANK_MISSING;
   extern CLASS_IMPORT I_CHAR * const BANK_IN_USE;
   extern CLASS_IMPORT I_CHAR * const UNVERIFIED_BANK_TRADE;
   extern CLASS_IMPORT I_CHAR * const UNVERIFIED_BANK_SETTLEMENT;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const BANKING_VERIFICATION;
}

//******************************************************************************
struct IARecordPeriod
{
   DString strAcctAuthRid;
   DString strEffectiveDate;
   DString strStopDate;
};

typedef std::vector<IARecordPeriod> vIARecordPeriod;

//******************************************************************************
bool BankInstructions::sortByEffectiveDate(const IARecordPeriod& input1, 
                                           const IARecordPeriod& input2)
{
   DString strEffDate1 = input1.strEffectiveDate;
   DString strEffDate2 = input2.strEffectiveDate;

   DSTCommonFunctions::DATE_ORDER result = 
      DSTCommonFunctions::CompareDates( strEffDate1, strEffDate2 );

   if( result == DSTCommonFunctions::FIRST_EARLIER || 
       result == DSTCommonFunctions::EQUAL )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//******************************************************************************
BankInstructions::BankInstructions (BFAbstractCBO &parent)
: MFCanBFCbo (parent),
_bGetsCloned (false),
_dstrVerifyStatus (NULL_STRING),
_bIsDirty (false),
_bCanVerify (false),
_bVerificationEnabled (false),
_bInit (true)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   
   DString dstrSwitchBanks;
   getWorkSession ().getOption ( ifds::SwitchBanks, dstrSwitchBanks, BF::HOST, false);

   addCrossEdit(ifds::EFTRedemptionXEdit, ifds::AcctUseCode );
   addCrossEdit(ifds::EFTRedemptionXEdit, ifds::BankAcctCurrency );

   addCrossEdit(ifds::EFTPurchaseXEdit, ifds::AcctUseCode );
   addCrossEdit(ifds::EFTPurchaseXEdit, ifds::BankAcctCurrency );

   if (dstrSwitchBanks == NO)
   {
      addCrossEdit(ifds::EFTRedemptionXEdit, ifds::EffectiveDate );
      addCrossEdit(ifds::EFTRedemptionXEdit, ifds::StopDate );

      addCrossEdit(ifds::EFTPurchaseXEdit, ifds::EffectiveDate );
      addCrossEdit(ifds::EFTPurchaseXEdit, ifds::StopDate );
   }
   else
   {
      addCrossEdit(ifds::EffectiveStopDate, ifds::EffectiveDate );
      addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate );
   }

   DString dstrDirectDepositBankApplicable;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, dstrDirectDepositBankApplicable, BF::HOST, false);

   if ( dstrDirectDepositBankApplicable == YES )
   {
      addCrossEdit(ifds::BankAcctUseCodeCurrType, ifds::BankIdType );
      addCrossEdit(ifds::BankAcctUseCodeCurrType, ifds::BankAcctCurrency );
      addCrossEdit(ifds::BankAcctUseCodeCurrType, ifds::AcctUseCode );
   }

   addCrossEdit(ifds::EffectiveStopDate, ifds::EffectiveDate);
   addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate);

   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

//******************************************************************************
BankInstructions::~BankInstructions ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY BankInstructions::init ( const BFData& data, 
                                  const DString &bankInstrType,
                                  bool bBaseDelete)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   attachDataObject (const_cast<BFData&> (data), bBaseDelete, true);
   commonInit (bankInstrType, BF::HOST);

   DString bankIdValue;

   getField (ifds::BankIdValue, bankIdValue, BF::HOST, false);
   //we do not want to modify an existing bank record
   if (!bankIdValue.empty())
   {
      setBankInfoReadOnly (fieldsInBeneficialBank);
   }

   initVerifyStatus (BF::HOST, false);

   _bInit = false;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::initNew ( const DString &bankInstrType, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("initNew"));
   commonInit (bankInstrType, idDataGroup);
   initVerifyStatus (idDataGroup, true);

   DString dstrCurrBankTypeSel, dstrAcctNum;
   getParent ()->getField (ifds::AccountNum, dstrAcctNum, idDataGroup, false);
   
   if(BANKTYPE::ACCOUNT == bankInstrType || BANKTYPE::SHAREHOLDER == bankInstrType )
   {
     setFieldNoValidate(ifds::rxAcctNum, dstrAcctNum, idDataGroup, false, true, true);
     DString dstrBankEntity ;
     dstrBankEntity = BANKTYPE::ACCOUNT == bankInstrType ? BANKENTITY::ACCOUNT : BANKENTITY::SHAREHOLDER;
     setFieldNoValidate(ifds::rxBankingEntity, dstrBankEntity,idDataGroup, false, true, true);
     //these are not updatable fields in banking update ..just used in enquiry as helper..
     //should not trigger an update request based on the field update.. 
     setFieldUpdated(ifds::rxAcctNum, idDataGroup, false);
     setFieldUpdated(ifds::rxBankingEntity, idDataGroup, false);
   }   
   _bInit = false;
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::preInit (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("preInit"));
   DString strAcctUseCode, strPayMethod;
   //pay method is not in view 52
   //probably the right thing to do is to add this field to view 52
   //until then, it is default as WIRE if market is Inter, Otherwise, EFT.
   getField (ifds::AcctUseCode, strAcctUseCode, idDataGroup, false);
   if(strAcctUseCode == AcctUseCode::DIRECT_DEPOSIT)
       strPayMethod = I_("DDER");
   else
       strPayMethod = ( DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): I_("EFT") );
   setFieldNoValidate (ifds::PayMethod, strPayMethod, idDataGroup, false, true, true, false);
   //PayMethod is read-only
   setFieldReadOnly (ifds::PayMethod, idDataGroup, true);
   //Default ACHProcessor from generic control:TradeDeafault.FileProcessor for domestic clients.
   if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
	   DString fileProcessorList;  
	   getWorkSession().getOption (ifds::TradeFileProcessorDefault, 
								   fileProcessorList, 
								   BF::HOST, 
								   false);
	   setFieldNoValidate (ifds::ACHProcessor, fileProcessorList, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::commonInit ( const DString &bankInstrType,
                                        const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("commonInit"));

   setFieldNoValidate ( ifds::BankInstrType, 
                        bankInstrType, 
                        BF::HOST, 
                        false);

//country code needs to be invalidated, to trigger validation
   setFieldValid (ifds::BankCountry, idDataGroup, false);
//some things must be done before
   preInit (idDataGroup);
   //group of mandatory sets

//default bank id type
   DString bankIdType;

   getField (ifds::BankIdType, bankIdType, idDataGroup, false);
   if (bankIdType.empty () || isNew())
   {
      getWorkSession ().getOption ( ifds::DefaultBankType, 
                                    bankIdType, 
                                    BF::HOST, 
                                    false);
      setFieldNoValidate (ifds::BankIdType, bankIdType, idDataGroup, false);
   }
   //is bank id type updatable?
   DString bankTypeUpdate;

   getWorkSession ().getOption ( ifds::DefaultBankUpd, 
                                 bankTypeUpdate, 
                                 BF::HOST, 
                                 false
   );
   if (bankTypeUpdate.upperCase () == NO && !bankIdType.empty ())
   {
      setFieldReadOnly (ifds::BankIdType, idDataGroup, true);
   }

//stop date
   DString stopDate;

   getField (ifds::StopDate, stopDate, idDataGroup, false);
   if (stopDate.empty())
   {
      getWorkSession ().getDateInHostFormat ( stopDate, 
                                              DSTCWorkSession::DATE_TYPE::DAY12319999, 
                                              idDataGroup);
      setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false, true, true);
   }
//set the account name
   DString accountNum, 
         entityName;

   getField (ifds::BankAcctName, entityName, idDataGroup, false);
   getParent ()->getField (ifds::AccountNum, accountNum, idDataGroup, false);
   if (!accountNum.empty () && entityName.strip ().empty ())
   {
      MFAccount *pMFAccount = NULL;

      if (getWorkSession ().getMFAccount (idDataGroup, accountNum, 
            pMFAccount) <= WARNING && pMFAccount)
      {
         pMFAccount->getAcctName (entityName, idDataGroup);
         setFieldNoValidate (ifds::BankAcctName, entityName, idDataGroup, false);
      }
   }
   if (isShareholderBank (idDataGroup)||
       isAccountBank (idDataGroup)||
       isRegAgentBank(idDataGroup)) //set the account name mandatory for shareholder banking
   {
      //the bank account name should be required
      setValidFlag (ifds::BankAcctName, idDataGroup, false);
      setFieldRequired (ifds::BankAcctName, idDataGroup, true);
   }
//preparatory sets
   if (isRRIFBank (idDataGroup))
   {
      //for now hardcode the RRIF account usage substitution list
      setFieldAllSubstituteValues ( ifds::AcctUseCode, 
                                    idDataGroup, 
                                    I_ ("1000=RRIF;"));
   }
   else
   {
      DynamicSubListHolder *pDynamicSubListHolder = getMgmtCo ().getDynamicSubListHolder ();

      assert (pDynamicSubListHolder);

      setFieldAllSubstituteValues ( ifds::AcctUseCode, idDataGroup, 
                                    pDynamicSubListHolder->getBankAcctUseSubList (bankInstrType));
   }

   DString dstrDirDepsBnkApplicable;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, dstrDirDepsBnkApplicable, BF::HOST, false);

   if (dstrDirDepsBnkApplicable == I_("N"))
   {
      DString substList1,substList2;
      BFProperties *pProperties = getFieldProperties (ifds::AcctUseCode, idDataGroup);
      if( pProperties )
      {
         pProperties->getAllSubstituteValues (substList1);
      }
      substList2 = substList1;
      substList1 = removeItemFromSubtList( substList1, AcctUseCode::DIRECT_DEPOSIT );
      setFieldAllSubstituteValues ( ifds::AcctUseCode, idDataGroup, 
                                    substList1);
   }

   DString bankLayout;

   getWorkSession ().getOption ( ifds::BankLayout, 
                                 bankLayout, 
                                 BF::HOST, 
                                 false);
   if (bankLayout == I_("2")) //bank account type is mandatory
   {
      setFieldRequired (ifds::BankAcctType, idDataGroup, true);
      setValidFlag (ifds::BankAcctType, idDataGroup, false);
   }
   
   bool bIsCorrBankInfoApplicable = isCorrBankInfoApplicable (idDataGroup);

   setFieldReadOnly (ifds::BankIdValueCB, idDataGroup, !bIsCorrBankInfoApplicable);
   setFieldReadOnly (ifds::BankIdTypeCB, idDataGroup, !bIsCorrBankInfoApplicable);   
   DString strAcctUseCode;

   getField (ifds::AcctUseCode, strAcctUseCode, idDataGroup, false);
   strAcctUseCode.strip().upperCase();
   bool bFFCReadonly = (isShareholderBank (idDataGroup)||
                        isAccountBank (idDataGroup) ||
                        isTradeBank(idDataGroup) ||
                        isPendingTradeBank(idDataGroup) ||
                        isTransactionBank(idDataGroup) ||
						isRegAgentBank(idDataGroup)) &&
                        (strAcctUseCode == AcctUseCode::EFT_PURCHASE ||
                         strAcctUseCode == AcctUseCode::ALT_EFT_PURCHASE);
   
   if (!bIsCorrBankInfoApplicable) //set the correspondent bank fields as read only
   {
      setFieldNoValidate (ifds::BankIdTypeCB, 
         NULL_STRING, idDataGroup, false, true, true, false);
      setBankInfoReadOnly (fieldsInCorresBank, idDataGroup);

      if (bFFCReadonly)
      {
         setFieldsReadOnly (fieldsInBankFFC, numFieldsInBankFFC, idDataGroup, bFFCReadonly);
      }
   }
   else
   {
      DString dstrBankIdValueCB;

      getField (ifds::BankIdValueCB, dstrBankIdValueCB, idDataGroup);
      if (dstrBankIdValueCB != NULL_STRING)
      {
         setBankInfoReadOnly (fieldsInCorresBank, idDataGroup);
      } 
      else if (isNew())
      {
         // set CB fields updatable for new record
         setReadOnlyAndClearCorrBank (false, idDataGroup);
      }

      setFieldsReadOnly (fieldsInBankFFC, numFieldsInBankFFC, idDataGroup, bFFCReadonly);
   }
   fileProcessorRelatedChanges (idDataGroup);
   currencyRelatedChanges (idDataGroup);
   if(bIsRedirect2RegAgentInst(idDataGroup))//redirect to RA
   {
	 setFieldsReadOnly(fieldsInCorresBank,numFieldsInCorresBank, idDataGroup);
	 setFieldsReadOnly(fieldsInBankFFC,numFieldsInBankFFC,idDataGroup);
   }
   //some things must be done after
   postInit (idDataGroup);

   _bIsDirty = false;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void BankInstructions::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   DString currBusDate,
      bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
//default effective date and stop date
//for non host banks let the parents decide about the effective date
   if ( !(isRRIFBank (idDataGroup) ||
          isSystematicBank (idDataGroup) ||
          isDistributionBank (idDataGroup) ||
          isSettlementBank (idDataGroup) ||
          isTradeBank (idDataGroup))) 
   {
      getWorkSession ().getOption ( ifds::CurrBusDate, 
                                    currBusDate, 
                                    idDataGroup, 
                                    false);
      setFieldNoValidate ( ifds::EffectiveDate, 
                           currBusDate, 
                           idDataGroup, 
                           false);
   }
   if (isDirectTradingBank (idDataGroup))
   {
      setFieldNoValidate ( ifds::AcctUseCode, 
                           AcctUseCode::DIRECT_TRADING, 
                           idDataGroup, 
                           false);
//set default institution number
      DString defaultBankInstCode;

      getWorkSession ().getOption ( ifds::DefaultBankInstCode, 
                                    defaultBankInstCode, 
                                    BF::HOST, 
                                    false);
      setFieldNoValidate ( ifds::BankIdValue, 
                          defaultBankInstCode, 
                          idDataGroup, 
                          false);
   }
   setFieldNoValidate (ifds::BankAcctType, I_("1"), idDataGroup, false);
   initVerifyStatus (idDataGroup, true);
   if (_bGetsCloned)
   {
      _bGetsCloned = false;
   }
   if(isShareholderBank(idDataGroup) )
   {
    setFieldNoValidate(ifds::rxBankingEntity, BANKENTITY::SHAREHOLDER, idDataGroup, false, true, false,false);    
   }
   if(isAccountBank(idDataGroup))
   {
    setFieldNoValidate(ifds::rxBankingEntity, BANKENTITY::ACCOUNT, idDataGroup, false, true, false,false);
   }
   setFieldUpdated(ifds::rxAcctNum, idDataGroup, false);
   setFieldUpdated(ifds::rxBankingEntity, idDataGroup, false);
   _bInit = false;
}

//******************************************************************************
SEVERITY BankInstructions::postInit (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("postInit"));
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void BankInstructions::doReset (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doReset"));
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   commonInit (bankInstrType, idDataGroup);
   initVerifyStatus (idDataGroup, isNew ());
}

//******************************************************************************
SEVERITY BankInstructions::setField ( const BFFieldId &idField, 
                                      const DString &dstrValue,
                                      const BFDataGroupId &idDataGroup, 
                                      bool bFormatted, 
                                      bool bSideEffect, 
                                      bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_ ("setField"));

   DString value (dstrValue);
   DString temp (dstrValue);
   bool isBlank = temp.strip ().stripLeading ('0') == NULL_STRING;

   //if transit no comes as 0, then its value should be reset to null_string
   //so the validation can pass, and the field is not set as required
   if (( idField == ifds::TransitNo || 
         idField == ifds::TransitNoCB ||
         idField == ifds::BankIdValue) && isBlank)
   {
      value = NULL_STRING;
   }

   BFCBO::setField ( idField, 
                     value, 
                     idDataGroup, 
                     bFormatted && 
                        !((idField == ifds::TransitNo || 
                        idField == ifds::TransitNoCB) && 
                        value == NULL_STRING), 
                     bSideEffect, 
                     bCheckCurrentValue);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::doValidateField ( const BFFieldId &idField,
                                             const DString &strValue, 
                                             const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));

   DString bankType, 
      bankIDValue;

   if (idField == ifds::BankIdValue)
   {
      getField (ifds::BankIdType, bankType, idDataGroup, false);
      FinancialInstitution::
            validateBankCode ( getWorkSession (), 
                               bankType, 
                               strValue);
	  bool bMatch = FinancialInstitution::
		    validatePreformatted (bankType,
								  strValue);

	  if (!bMatch)
	  {
		 ADDCONDITIONFROMFILE (CND::ERR_BSB_FORMAT_IS_INCORRECT);
	  }
   }
   else if (idField == ifds::TransitNo)
   {
      getField (ifds::BankIdType, bankType, idDataGroup, false);
      getField (ifds::BankIdValue, bankIDValue, idDataGroup, false);
      FinancialInstitution::
            validateBankTransitNum ( getWorkSession (), 
                                     bankType, 
                                     bankIDValue, 
                                     strValue);
   }
   //fields that check if it is international wire
   if ( idField == ifds::BankIdValueCB || 
        idField == ifds::TransitNoCB) 
   {
      if (isCorrBankInfoApplicable (idDataGroup))
      {
         if (idField == ifds::BankIdValueCB)
         {
            getField (ifds::BankIdTypeCB, bankType, idDataGroup, false);
            if (!bankType.strip ().empty ())
            {
               FinancialInstitution::
                     validateBankCode ( getWorkSession (), 
                                        bankType, 
                                        strValue);
			   bool bMatch = FinancialInstitution::
					 validatePreformatted (bankType,
					 					   strValue);

			   if (!bMatch)
			   {
			       ADDCONDITIONFROMFILE (CND::ERR_BSB_FORMAT_IS_INCORRECT);
			   }
            }
         }
         else if (idField == ifds::TransitNoCB)
         {
            getField (ifds::BankIdTypeCB, bankType, idDataGroup, false);
            getField (ifds::BankIdValueCB, bankIDValue, idDataGroup, false);
            if (!bankType.strip ().empty ())
            {
               FinancialInstitution::
                     validateBankTransitNum ( getWorkSession (), 
                                              bankType, 
                                              bankIDValue, 
                                              strValue);
            }
         }
      }
   }
   else if (idField == ifds::BankCountry)
   {
      validateCountryCode (strValue, idDataGroup);

   }
   else if (idField == ifds::EFTRedemptionXEdit)
   {
      validateStopDateEffDate(idDataGroup);

      BankInstructionsList *pBankInstructionsList = dynamic_cast<BankInstructionsList*>( getParent( ) );      

      if (pBankInstructionsList)
      {
         if (pBankInstructionsList->validateEFTRedemptionBanking (this, idDataGroup) <= WARNING &&
             (isShareholderBank (idDataGroup) || isAccountBank(idDataGroup))) 
         {
            pBankInstructionsList->displayEFTWarning(this, idDataGroup);
         }
      }
   }
   else if ( idField == ifds::EFTPurchaseXEdit )
   {
      validateStopDateEffDate(idDataGroup);

      BankInstructionsList *pBankInstructionsList = dynamic_cast<BankInstructionsList*>( getParent( ) );      

      if (pBankInstructionsList)
      {
         if (pBankInstructionsList->validateEFTPurchaseBanking (this, idDataGroup) <= WARNING &&
            isShareholderBank (idDataGroup)) 
         {
            pBankInstructionsList->displayEFTWarning(this, idDataGroup);
         }
      }
   }
   else if ( idField == ifds::AcctUseCode)
   {
      validateAcctUseCodeForInvestorAuthorizationInfo(idDataGroup);
   }
   else if ( idField == ifds::BankAcctUseCodeCurrType )
   {
      validateBankAcctUseCodeCurrType(idDataGroup);
   }
   else if ( idField == ifds::EffectiveDate)
   {
      validateBankForIA( idDataGroup );
   }
   else if (idField == ifds::VerifyStat)
   {
      if (strValue == UNVERIFIED && !_bGetsCloned)
      {
         ADDCONDITIONFROMFILE (CND::ERR_WRONG_VERIFY_STATUS);
      }
   }
   else if ( idField == ifds::EffectiveStopDate )
   {
      validateStopDateEffDate(idDataGroup);
   }
   else if ( idField == ifds::BankAcctNum )
   {
	  DString currency;
	  getField (ifds::BankIdType, bankType, idDataGroup, false);
	  getField (ifds::BankAcctCurrency, currency, idDataGroup, false);

	  bool bMatch = FinancialInstitution::
				  validateAcctNbrformatted (bankType,
											currency,
					   				        strValue);
	  if (!bMatch)
	  {
		if (currency == I_("AUD"))
		{
		  ADDCONDITIONFROMFILE (CND::ERR_BSB_BANK_ACCT_AUD_FORMAT_IS_INCORRECT);
		}
		else
		{
		  ADDCONDITIONFROMFILE (CND::ERR_BSB_BANK_ACCT_FOREIGN_FORMAT_IS_INCORRECT);
		}
	  }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::doValidateAll (const BFDataGroupId &idDataGroup, 
                                          long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   DString verifyStatus;
   DString tradeExists;

   getField (ifds::VerifyStat, verifyStatus, idDataGroup, false);
   getField (ifds::TradeExists, tradeExists, idDataGroup, false);

   if (_bIsDirty)
   {
      setFieldNoValidate (ifds::AcctID, I_("0"), idDataGroup);
   }

   // proceed with verification:
   if (!_bVerificationEnabled)
      return GETCURRENTHIGHESTSEVERITY ();

   if ((isTradeBank (idDataGroup) || isDistributionBank (idDataGroup)) && verifyStatus== UNVERIFIED)
   {
      getErrMsg (IFASTERR::UNVERIFIED_BANK_TRADE, 
                 CND::ERR_UNVERIFIED_BANK, 
                 CND::WARN_UNVERIFIED_BANK, 
                 idDataGroup);
   }
   else if (isSettlementBank (idDataGroup) && verifyStatus== UNVERIFIED)
   {
      getErrMsg (IFASTERR::UNVERIFIED_BANK_SETTLEMENT, 
                 CND::ERR_UNVERIFIED_BANK, 
                 CND::WARN_UNVERIFIED_BANK, 
                 idDataGroup);
   }
   else if (verifyStatus== UNVERIFIED && tradeExists == I_("Y"))
   {
      getErrMsg (IFASTERR::BANK_IN_USE, 
                 CND::ERR_BANK_IN_USE, 
                 CND::WARN_BANK_IN_USE, 
                 idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doApplyRelatedChanges"))

   if (idField == ifds::BankIdType)
   {
      DString bankType,
         bankIdValue,
         tempBankIdValue;

      getField (ifds::BankIdType, bankType, idDataGroup, false);
      getField (ifds::BankIdValue, bankIdValue, idDataGroup, false);
      tempBankIdValue = bankIdValue;

      setValidFlag (ifds::BankIdValue, idDataGroup, false);
      setValidFlag (ifds::TransitNo, idDataGroup, false);

      //TransitNo should be required if it exists for the current bank type
      bool transitNoReq = isBankTransitNumRequired (bankType);

      setFieldRequired (ifds::TransitNo, idDataGroup, transitNoReq);
      if (!transitNoReq)
      {
         setFieldNoValidate (ifds::TransitNo, NULL_STRING, 
            idDataGroup, false, true, true);
      }
      else 
      {
         DString transitNo,
            tempTransitNo;

         getField (ifds::TransitNo, transitNo, idDataGroup, false);
         tempTransitNo = transitNo;

         if (tempTransitNo.empty ())
         {
            setFieldNoValidate (ifds::TransitNo, NULL_STRING, idDataGroup, false, false, true); //not valid, required
         }
      }
   }
   else if (idField == ifds::BankIdTypeCB)
   {
      DString bankTypeCB;

      getField (ifds::BankIdTypeCB, bankTypeCB, idDataGroup, false);
      setValidFlag (ifds::BankIdValueCB, idDataGroup, false);
      setValidFlag (ifds::TransitNoCB, idDataGroup, false);

//TransitNoCB should be required if it exists for the current bank type
      bool transitNoReq = isBankTransitNumRequired (bankTypeCB);
   
      setFieldRequired (ifds::TransitNoCB, idDataGroup, transitNoReq);
      if (!transitNoReq)
      {
         setFieldNoValidate ( ifds::TransitNoCB, NULL_STRING, idDataGroup, false, 
                              true, 
                              true); //notify
      }
      else
      {
         DString transitNoCB;

         getField (ifds::TransitNoCB, transitNoCB, idDataGroup, false);
         if (transitNoCB == I_("0"))
         {
            setFieldNoValidate ( ifds::TransitNoCB, NULL_STRING, idDataGroup, false, 
                                 false, 
                                 true); //notify, //not valid, required
         }
      }
      if (bankTypeCB.strip ().empty ())
      {
         //clear the corresp bank info
         for (int i = 0; i < numFieldsInCorresBank; ++i)
         {
            DString str;
            BFFieldId fieldId = fieldsInCorresBank[i];

            getField (fieldId, str, idDataGroup, false);
            if (!str.strip ().empty ())
            {
               setFieldNoValidate (fieldId, NULL_STRING, idDataGroup, false, true, true);
            }
         }
      }
   }
   else if (idField == ifds::AcctUseCode)
   {
      DString strAcctUseCode, strPayMethod;
      //do this before anything else, 
      //because it affects all fields
      if (!isCorrBankInfoApplicable (idDataGroup))
      {
         setReadOnlyAndClearCorrBank (true, idDataGroup);
         setFieldRequired (ifds::BankIdTypeCB, idDataGroup, false);
         setFieldRequired (ifds::BankIdValueCB, idDataGroup, false);
      }
      else
      {  // SSB does not want CB info mandatory 
         setReadOnlyAndClearCorrBank (false, idDataGroup);         
      }
      fileProcessorRelatedChanges (idDataGroup);
      currencyRelatedChanges (idDataGroup);
      eftRedemptionRelatedChanges (idDataGroup);
      eftPurchaseRelatedChanges (idDataGroup);
      getField (ifds::AcctUseCode, strAcctUseCode, idDataGroup, false);

      if(strAcctUseCode == AcctUseCode::DIRECT_DEPOSIT)
	     strPayMethod = I_("DDER");
      else
         strPayMethod = ( DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): I_("EFT") );
      setFieldNoValidate (ifds::PayMethod, strPayMethod, idDataGroup, false, true, true, false);
   }
   else if (idField == ifds::BankAcctCurrency)
   {
      fileProcessorRelatedChanges (idDataGroup);
      eftRedemptionRelatedChanges (idDataGroup);
      eftPurchaseRelatedChanges (idDataGroup);
	  setFieldValid(ifds::BankAcctNum,idDataGroup,false);
   }
   else if (idField == ifds::ACHProcessor)
   {
      currencyRelatedChanges (idDataGroup);
   }
   if ( idField == ifds::BankIdValue || 
        idField == ifds::TransitNo || 
        idField == ifds::BankIdType)
   {
      getBankInfo (fieldsInBeneficialBank, idDataGroup);
   }
   if ( idField == ifds::BankIdValueCB || 
        idField == ifds::TransitNoCB || 
        idField == ifds::BankIdTypeCB)
   {
      getBankInfo (fieldsInCorresBank, idDataGroup);
   }
   if( ifds::BankInstrComboDefault == idField )
   {
     Shareholder* pShareHolder = NULL;
     pShareHolder = dynamic_cast <Shareholder*>(getParent ()->getParent());
     DString dstrCurSel = NULL_STRING;
     if( pShareHolder )
        pShareHolder->getCurrentBankingSel(dstrCurSel); 
     BFProperties *pBFProperties = getFieldProperties (ifds::BankInstrComboDefault, idDataGroup);
     assert (pBFProperties);
     if(pBFProperties && (BANKTYPE::ACCOUNT == dstrCurSel || BANKTYPE::SHAREHOLDER == dstrCurSel))
     {
          DString dstrBankTypeSubValues, dstrnewSubValues, dstrValue, dstrcode, tmp, dstrFindString;
          dstrValue =I_("Default");
          dstrcode = BANKTYPE::ACCOUNT == dstrCurSel ? BANKTYPE::SHAREHOLDER :BANKTYPE::ACCOUNT ;
          pBFProperties->getAllSubstituteValues(dstrBankTypeSubValues);
          dstrBankTypeSubValues = removeItemFromSubtList ( dstrBankTypeSubValues, dstrcode);
          setFieldAllSubstituteValues ( ifds::BankInstrComboDefault, 
                                        idDataGroup, dstrBankTypeSubValues);     
     }
   }
   verifyStatusRelatedChanges (idField, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY BankInstructions::verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("verifyStatusRelatedChanges"));

   bool bFlipFlag = true;

   if (_bInit && !isNonStaticDataBank (idDataGroup))
      return GETCURRENTHIGHESTSEVERITY ();

   if (idFieldId == ifds::AcctUseCode)
   {
      DString acctUseCode, origAcctUseCode;

      getField (ifds::AcctUseCode, acctUseCode, idDataGroup, false);
      getFieldBeforeImage (ifds::AcctUseCode,    origAcctUseCode );
      origAcctUseCode.strip ();

      // if acct use code is flipped to ALT_EFT_REDEMPTION do not change verify status
      // keep the Verify Status as it was on the original record
      if ( ( acctUseCode ==  AcctUseCode::ALT_EFT_REDEMPTION && 
          origAcctUseCode == AcctUseCode::EFT_REDEMPTION) || 
          ( acctUseCode ==  AcctUseCode::ALT_EFT_PURCHASE && 
          origAcctUseCode == AcctUseCode::EFT_PURCHASE) )
      {
         bFlipFlag = false;
      }
   }

   if (idFieldId != ifds::VerifyStat && 
       idFieldId != ifds::EFTRedemptionXEdit && 
       idFieldId != ifds::EFTPurchaseXEdit && 
       !_bIsDirty )
   {
      if (bFlipFlag)
      {
         _bIsDirty = isObjectDirty (idDataGroup);

         if (_bIsDirty )
         {
            // stupid init is making object dirty.
            if (isNonStaticDataBank (idDataGroup))
            {
               // break the link as field got changed on the original bank
               //setFieldNoValidate (ifds::AcctID, I_("0"), idDataGroup);
            }
            else
            {
               if (_bVerificationEnabled )
               {
                  setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
               }
            }

            setFieldReadOnly (ifds::VerifyStat, idDataGroup, true);
         }
      }
   }


   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::getBankInfo ( const BFFieldId fieldIds[], 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getBankInfo"));

   DString bankInstrType, 
      dstrBankIDValue, 
      dstrTransitNo;
   bool readOnly = false;

   getField (fieldIds[0], bankInstrType, idDataGroup, false);
   getField (fieldIds[1], dstrBankIDValue, idDataGroup, false);
   getField (fieldIds[2], dstrTransitNo, idDataGroup, false);

   DString 
      bankType (bankInstrType),
      bankCode (dstrBankIDValue), 
      transitNo (dstrTransitNo);

   bankType.strip ().upperCase ();
   transitNo.strip ().stripLeading ('0').upperCase ();
   
   int iBankNumMaxLength = -1, 
       iAllBankNumMaxLength = -1;
   bool bBankIsDigits = false;

   FinancialInstitution::getBankIdNumInfo (
      bankType, 
      iBankNumMaxLength, 
      bBankIsDigits, 
      iAllBankNumMaxLength);

   if (bBankIsDigits)
   {
      bankCode.strip ();
   }
   else
   {
      bankCode.strip ().upperCase();
   }
   
   int iTransitNumMaxLength = -1, 
      iAllTransitNumMaxLength = -1;
   bool bTransitIsDigits = false;
   bool bHasTransit = 
      FinancialInstitution::getBankTransitNumInfo (
         bankType, 
         iTransitNumMaxLength, 
         bTransitIsDigits, 
         iAllTransitNumMaxLength) && 
      iTransitNumMaxLength > 0;
   
   if (bTransitIsDigits)
   {
      transitNo.strip ();
   }
   else
   {
      transitNo.strip ().upperCase();
   }
   if (!bankCode.empty () && !bankType.empty () && 
       (!bHasTransit || (bHasTransit && !transitNo.empty ())))
   {
      MFCanBFCbo *fiSearch = NULL;
      if (bHasTransit)
      {
         fiSearch = new FinancialInstitutionTransitList(*this);
      }
      else
      {
         fiSearch = new FinancialInstitutionList(*this);
      }

      bool bRecordsExist = bHasTransit ?
         //check for transits
         dynamic_cast<FinancialInstitutionTransitList*>(fiSearch)->init 
            (FI_CATEGORY::BANK_TRANSIT, bankType, 
            bankCode, transitNo) <= WARNING :
         //check for banks
         dynamic_cast<FinancialInstitutionList*>(fiSearch)->init 
            (FI_CATEGORY::BANK, bankType, bankCode) <= WARNING;

      if (bRecordsExist)
      {
         BFObjIter bfIter (*fiSearch, idDataGroup);
         
         bfIter.begin ();
         if (!bfIter.end ())
         {
            DString dstrValue;
    
            readOnly = true;
            bfIter.getObject ()->getField (ifds::Name, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[3], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankAddr1, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[8], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankAddr2, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[9], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankAddr3, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[10], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankAddr4, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[11], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankAddr5, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[12], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankContact, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[7], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankCountry, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[6], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankPostal, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[5], dstrValue, idDataGroup, false, true, true);
            bfIter.getObject ()->getField (ifds::BankId, dstrValue, idDataGroup);
            setFieldNoValidate (fieldIds[13], dstrValue, idDataGroup, false, true, true);
         }
         else // if record does not exist in bank master, assign code with zero 
              // and blank out all the other fields (to prevent users from blindly saving a new record with old info into the database - yes it happened for AIM, and not once)
         {
            DString dstrValue = NULL_STRING;
            if( !_bGetsCloned )
            {
               setFieldNoValidate (fieldIds[13], I_ ("0"), idDataGroup, false, true, true);
               setFieldNoValidate (fieldIds[3], dstrValue, idDataGroup, false, true, true);
               setFieldNoValidate (fieldIds[8], dstrValue, idDataGroup, false, true, true);
               setFieldNoValidate (fieldIds[9], dstrValue, idDataGroup, false, true, true);
               setFieldNoValidate (fieldIds[10], dstrValue, idDataGroup, false, true, true);
               setFieldNoValidate (fieldIds[11], dstrValue, idDataGroup, false, true, true);
               setFieldNoValidate (fieldIds[12], dstrValue, idDataGroup, false, true, true);
               setFieldNoValidate (fieldIds[7], dstrValue, idDataGroup, false, true, true);
               setFieldNoValidate (fieldIds[6], dstrValue, idDataGroup, false, true, true);
               setFieldValid (fieldIds[6], idDataGroup, false);//BankCountry is a mandatory field, so make sure that it will be validated
               setFieldNoValidate (fieldIds[5], dstrValue, idDataGroup, false, true, true);			
            }
         }
      }
      if (fiSearch)
      {
         bHasTransit ?
            //transits
            delete dynamic_cast<FinancialInstitutionTransitList*>(fiSearch) :
            //banks
            delete dynamic_cast<FinancialInstitutionList*>(fiSearch);
         fiSearch = NULL;
      }
   }
   setBankInfoReadOnly (fieldIds, idDataGroup, readOnly);
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
bool BankInstructions::isCorrBankInfoEmpty (BFCBO* pCBO, 
   const BFDataGroupId& idDataGroup)
{
   for (int i=0; i< numFieldsInCorresBank; ++i)
   {
      DString str;
      pCBO->getField (fieldsInCorresBank[i], str, idDataGroup, false);
      if (!str.strip ().stripLeading ('0').empty ())
         return (false);
   }
   return (true);
}

//******************************************************************************
bool BankInstructions::isCorrBankInfoEntered (BFCBO* pCBO, 
   const BFDataGroupId& idDataGroup)
{
   DString str;
   pCBO->getField (ifds::BankIdTypeCB, str, idDataGroup, false);
   if (str.strip ().empty ())
      return (false);

   return (true);
}

//******************************************************************************
SEVERITY BankInstructions::currencyRelatedChanges (
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_("currencyRelatedChanges"));
   DString transType,
      achControl,
      substList;

   if (getTransTypeFor207Call (transType, achControl, idDataGroup) <= WARNING)
   {
      if (achControl == YES)
      {
         DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().
            getDynamicSubListHolder();

         assert(pDynamicSubListHolder);

         DString payMethod, 
            fileProcessor;

         getField (ifds::PayMethod, payMethod, idDataGroup, false);
         payMethod.strip();
         getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
         fileProcessor.strip();
         if (fileProcessor.empty() || isShareholderBank (idDataGroup)|| isAccountBank (idDataGroup) || isRegAgentBank(idDataGroup)) 
         {
            substList = pDynamicSubListHolder->getCurrencySubList (transType, 
               payMethod);
         }
         else
         {
            substList = pDynamicSubListHolder->getCurrencySubList (transType, 
               payMethod, fileProcessor);
         }
      }
   }
   if (substList.empty())
   {
//get the currencies set....
      BFProperties *pProperties = 
         getFieldProperties (ifds::BankAcctCurrency, BF::HOST);
   
      pProperties->getAllSubstituteValues (substList);
   }
   setFieldAllSubstituteValues (ifds::BankAcctCurrency, idDataGroup, substList);
//have to force validation, because substitute values have changed
   setValidFlag (ifds::BankAcctCurrency, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::fileProcessorRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fileProcessorRelatedChanges"));

   DString transType, 
      achControl,
      substList;
   bool bAchProcessorRequired = false;
//DO NOT EXCLUDE file processor for Sharholder banking because API needs to set-up the default value!!!!!
   if ( !isFundBank (idDataGroup) && 
        !isClientBank (idDataGroup) && 
        !isFundGroupBank (idDataGroup) && 
        !isFundSponsorBank (idDataGroup) && 
        getTransTypeFor207Call ( transType, 
                                 achControl, 
                                 idDataGroup) <= WARNING)
   {
      if (achControl == YES)
      {
         DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();     
         assert (pDynamicSubListHolder);

         DString payMethod, 
               currency;
		 
         getField (ifds::PayMethod, payMethod, idDataGroup, false);
         payMethod.strip();
         getField (ifds::BankAcctCurrency, currency, idDataGroup, false);
         currency.strip();
         substList = pDynamicSubListHolder->
            getFileProcSubList (transType, payMethod, currency);
      }
   }
   setFieldAllSubstituteValues ( ifds::ACHProcessor, 
                                 idDataGroup, 
                                 substList);
   bAchProcessorRequired = !substList.empty();
   if (!bAchProcessorRequired)
   {
	   //Default ACHProcessor value when cannot get value from VEW207. Domestic clients use generic control:TradeDefault.FileProcessor. Inter cleints set null string.
	   if (DSTCommonFunctions::getMarket () != MARKET_IDS::CANADA)
	   {
		   setFieldNoValidate ( ifds::ACHProcessor, 
				                NULL_STRING, 
						        idDataGroup, 
							    false, 
								true, 
								true);
	   }
	   else
	   {
		   DString fileProcessorList;  
		   getWorkSession().getOption (ifds::TradeFileProcessorDefault, 
									   fileProcessorList, 
									   BF::HOST, 
									   false);
		   setFieldNoValidate (ifds::ACHProcessor, fileProcessorList, idDataGroup, false);
   	   }
   }
   else
   {
	   if (DSTCommonFunctions::getMarket () == MARKET_IDS::CANADA)
	   {
		   setFieldNoValidate ( ifds::ACHProcessor, 
				                substList.substr(0,substList.find('=')), 
						        idDataGroup, 
							    false, 
								true, 
								true);
	   }
   }
   setFieldRequired (ifds::ACHProcessor,idDataGroup, bAchProcessorRequired);
   setFieldReadOnly (ifds::ACHProcessor, idDataGroup, !bAchProcessorRequired);
   setValidFlag (ifds::ACHProcessor, idDataGroup, !bAchProcessorRequired);
   return GETCURRENTHIGHESTSEVERITY ();
}

// This method establishes if CorrBankInfo is applicable
//******************************************************************************
bool BankInstructions::isCorrBankInfoApplicable (const BFDataGroupId &idDataGroup)
{
   bool bReturn = false;

   if (DSTCommonFunctions::getMarket () == MARKET_IDS::LUXEMBOURG)
   {
      DString acctUsage,
         multiCurrency;
   
      getWorkSession ().getOption ( ifds::MultiCurrency, 
                                    multiCurrency, 
                                    BF::HOST, 
                                    false);
      multiCurrency.strip ().upperCase ();
      if (multiCurrency == YES)
      {
         getField (ifds::AcctUseCode, acctUsage, idDataGroup, false);
         bReturn = 
            ( (isTradeBank (idDataGroup) && 
              (acctUsage == AcctUseCode::EFT_REDEMPTION || 
               acctUsage == AcctUseCode::ALT_EFT_REDEMPTION)) ||

            ( isPendingTradeBank (idDataGroup) && 
               (acctUsage == AcctUseCode::EFT_REDEMPTION ||
                acctUsage == AcctUseCode::EFT_DIVIDEND ||
                acctUsage == AcctUseCode::ALT_EFT_REDEMPTION)) ||

            ( isTransactionBank (idDataGroup) && 
               (acctUsage == AcctUseCode::EFT_REDEMPTION ||
                acctUsage == AcctUseCode::EFT_DIVIDEND ||
                acctUsage == AcctUseCode::ALT_EFT_REDEMPTION)) ||

            ( isShareholderBank (idDataGroup) && 
              (acctUsage == AcctUseCode::EFT_REDEMPTION || 
               acctUsage == AcctUseCode::ALT_EFT_REDEMPTION ||
               acctUsage == AcctUseCode::EFT_DIVIDEND)) || 
   
            ( isAccountBank (idDataGroup) && 
              (acctUsage == AcctUseCode::EFT_REDEMPTION || 
               acctUsage == AcctUseCode::ALT_EFT_REDEMPTION ||
               acctUsage == AcctUseCode::EFT_DIVIDEND)) || 

		    ( isRegAgentBank (idDataGroup) &&
			  (acctUsage == AcctUseCode::EFT_REDEMPTION || 
			   acctUsage == AcctUseCode::ALT_EFT_REDEMPTION ||
			   acctUsage == AcctUseCode::EFT_DIVIDEND)) || 

            ( isShareholderBank (idDataGroup) && 
              acctUsage == AcctUseCode::DEFAULT)||

            ( isAccountBank (idDataGroup) && 
              acctUsage == AcctUseCode::DEFAULT)||

		    ( isRegAgentBank (idDataGroup) && 
              acctUsage == AcctUseCode::DEFAULT)||

            ( isDistributionBank (idDataGroup) &&
              (acctUsage == AcctUseCode::EFT || 
               acctUsage == AcctUseCode::EFT_DIVIDEND)) ||

            ( isDistributorBank (idDataGroup)) ||

            ( isSettlementBank (idDataGroup) &&
              (acctUsage == AcctUseCode::EFT_REDEMPTION || 
               acctUsage == AcctUseCode::ALT_EFT_REDEMPTION)) ) ||

            ( isFundBank (idDataGroup) &&
              (acctUsage == AcctUseCode::FUND_CREDIT ))||

            ( isClientBank (idDataGroup) &&
              (acctUsage == AcctUseCode::FUND_CREDIT ))||

            ( isFundSponsorBank (idDataGroup) &&
              (acctUsage == AcctUseCode::FUND_CREDIT ));
      }
   }
   return bReturn;
}

//******************************************************************************
void BankInstructions::setReadOnlyAndClearCorrBank ( bool readonly, 
                                                     const BFDataGroupId &idDataGroup)
{
   for (int i=0; i < numFieldsInCorresBank; ++i)
   {
      if (readonly)
      {
         setFieldNoValidate ( fieldsInCorresBank[i], NULL_STRING, 
                              idDataGroup, 
                              false, 
                              true, 
                              true);
      }
      setFieldReadOnly (fieldsInCorresBank[i], idDataGroup, readonly);
   }
}

//set read only methods
//******************************************************************************
void BankInstructions::setBankInfoReadOnly ( const BFFieldId fieldIds[], 
                                             const BFDataGroupId& idDataGroup /*= BF::HOST*/, 
                                             bool bReadOnly /*= true*/)
{
   setFieldReadOnly (fieldIds[3], idDataGroup, bReadOnly);
   setFieldReadOnly (fieldIds[8], idDataGroup, bReadOnly);
   setFieldReadOnly (fieldIds[9], idDataGroup, bReadOnly);
   setFieldReadOnly (fieldIds[10], idDataGroup, bReadOnly);
   setFieldReadOnly (fieldIds[11], idDataGroup, bReadOnly);
   setFieldReadOnly (fieldIds[12], idDataGroup, bReadOnly);
   setFieldReadOnly (fieldIds[7], idDataGroup, bReadOnly);
   setFieldReadOnly (fieldIds[6], idDataGroup, bReadOnly);
   setFieldReadOnly (fieldIds[5], idDataGroup, bReadOnly);
   //if BankCountry or BankCountryCB are empty then set them updateable
   if (bReadOnly)
   {
      DString strCountry, 
         strBankType;

      getField (fieldIds[6], strCountry, idDataGroup, false);
      getField (fieldIds[0], strBankType, idDataGroup, false);

      if (strCountry.strip ().empty () && !strBankType.strip ().empty ())
      {
         setFieldReadOnly (fieldIds[6], idDataGroup, false);
         setValidFlag (fieldIds[6], idDataGroup, false);
      }
   }
}

//******************************************************************************
void BankInstructions::setFieldsReadOnly ( const BFFieldId fieldsArray[], 
                                           int numFields, 
                                           const BFDataGroupId& idDataGroup /*= BF::HOST*/, 
                                           bool bReadOnly /*= true*/)
{
   for (int i = 0; i < numFields; i++)
   {
      setFieldReadOnly (fieldsArray[i], idDataGroup, bReadOnly);
   }
}

//******************************************************************************
SEVERITY BankInstructions::getTransTypeFor207Call ( DString &transType, 
                                                    DString &achControl,
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getTransTypeFor207Call"));
   DString acctUsage;

   achControl = NO;
   getField (ifds::TransType, transType, idDataGroup, false);
   transType.strip ();
   getField (ifds::AcctUseCode, acctUsage, idDataGroup, false);
   acctUsage.strip ();
   if (isSystematicBank (idDataGroup))
   {
      if (transType == TRADETYPE::SAVING_PLAN)
      {
         getWorkSession ().getOption2 ( ifds::ACHSavingsPlan, 
                                        achControl, 
                                        idDataGroup, 
                                        false);
      }
      
//set the apropriate transaction type for systematic
      if (transType == TRADETYPE::PAC)
      {
         getWorkSession ().getOption2 ( ifds::ACHPAC, 
                                        achControl, 
                                        idDataGroup, 
                                        false);
         transType = TransType::PAC;
      }
      else if (transType == TRADETYPE::SWP)
      {
         getWorkSession ().getOption2 ( ifds::ACHSWP, 
                                        achControl, 
                                        idDataGroup, 
                                        false);
         transType = TransType::SWP;
      }
   }
   // for INA : Account Commitment screen
   else if (isAcctCommitBank(idDataGroup))
   {
     getWorkSession ().getOption2(ifds::ACHPAC, 
                                  achControl, 
                                  idDataGroup, 
                                  false);
     transType = TransType::PAC;
   }
//for broker, branch salesrep banking
   else if (isDistributorBank (idDataGroup))
   {
      if (acctUsage == AcctUseCode::COMMISSION)
      {
         getWorkSession ().getOption ( ifds::ACHCommission, 
                                       achControl, 
                                       idDataGroup, 
                                       false);         
         transType = TransType::COMMISSION;
      }
      else if (acctUsage == AcctUseCode::TRAILER_FEE)
      {
         getWorkSession ().getOption ( ifds::ACHTrailerFee, 
                                       achControl, 
                                       idDataGroup, 
                                       false);   
         transType = TransType::TRAILER_FEE;
      }
      else if ( acctUsage == AcctUseCode::EFT_DIVIDEND || 
                acctUsage == AcctUseCode::DIVIDEND )
      {
         getWorkSession ().getOption ( ifds::ACHDividend, 
                                       achControl, 
                                       idDataGroup, 
                                       false);   
         transType = TransType::EFT_DIVIDEND;
      }
      else if (acctUsage == AcctUseCode::EFT_REDEMPTION )
      {
         getWorkSession ().getOption ( ifds::ACHRedemption, 
                                       achControl, 
                                       idDataGroup, 
                                       false);   
         transType = TransType::REDEMPTION;
      }
   }
   else if (isDistributionBank (idDataGroup))
   {
      getWorkSession().getOption ( ifds::ACHDividend, 
                                   achControl, 
                                   idDataGroup, 
                                   false);
   }
   else if (isShareholderBank (idDataGroup)|| isAccountBank(idDataGroup) || isRegAgentBank(idDataGroup) || isMaturityBank(idDataGroup))
   {
      if ( acctUsage == AcctUseCode::EFT_REDEMPTION      ||
           acctUsage == AcctUseCode::ALT_EFT_REDEMPTION  ||
           acctUsage == AcctUseCode::DEFAULT)
      {
         getWorkSession().getOption ( ifds::ACHRedemption, 
                                      achControl, 
                                      idDataGroup, 
                                      false);
         transType = TRADETYPE::REDEMPTION;
      }
      else if (acctUsage == AcctUseCode::EFT_DIVIDEND || 
               acctUsage == AcctUseCode::DIVIDEND )
      {
         getWorkSession ().getOption ( ifds::ACHDividend, 
                                       achControl, 
                                       idDataGroup, 
                                       false);   
         transType = TransType::EFT_DIVIDEND;
      }
      else if (acctUsage == AcctUseCode::EFT_PURCHASE || 
               acctUsage == AcctUseCode::ALT_EFT_PURCHASE )
      {
         getWorkSession ().getOption ( ifds::ACHPurch, 
                                       achControl, 
                                       idDataGroup, 
                                       false);   
         transType = TRADETYPE::PURCHASE;
      }
   }
   /*else if (isFundBank (idDataGroup))
   {
      if (acctUsage == AcctUseCode::COMMISSION)
      {
         getWorkSession ().getOption (ifds::ACHCommission, 
            achControl, idDataGroup, false);         
         transType = TransType::COMMISSION;
      }
      else if (acctUsage == AcctUseCode::EFT_DIVIDEND)
      {
         getWorkSession ().getOption (ifds::ACHDividend, 
            achControl, idDataGroup, false);   
         transType = TransType::EFT_DIVIDEND;
      }
      else if (acctUsage == AcctUseCode::TRAILER_FEE)
      {
         getWorkSession ().getOption (ifds::ACHTrailerFee, 
            achControl, idDataGroup, false);   
         transType = TransType::TRAILER_FEE;
      }
   }*/
   else if ( isTradeBank (idDataGroup) || 
             isPendingTradeBank (idDataGroup) ||
             isTransactionBank (idDataGroup) ||
             isSettlementBank (idDataGroup))
   {
      if (acctUsage == AcctUseCode::EFT_REDEMPTION)
      {
         getWorkSession().getOption ( ifds::ACHRedemption, 
                                      achControl, 
                                      idDataGroup, 
                                      false);
         transType = TransType::REDEMPTION;
      }
      if (acctUsage == AcctUseCode::EFT_PURCHASE)
      {
         getWorkSession().getOption ( ifds::ACHPurch, 
                                      achControl, 
                                      idDataGroup, 
                                      false);
         transType = TransType::PURCHASE;
      }
      else if (acctUsage == AcctUseCode::EFT_DIVIDEND)
      {
         getWorkSession ().getOption ( ifds::ACHDividend, 
                                       achControl, 
                                       idDataGroup, 
                                       false);   
         transType = TransType::EFT_DIVIDEND;
      }
      if (acctUsage == AcctUseCode::COMM_CLEAR)
      {
         getWorkSession().getOption ( ifds::ACHAdminFee, 
                                      achControl, 
                                      idDataGroup, 
                                      false);
         transType = TransType::ADMIN_FEE;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::validateCountryCode ( const DString& countryCode, 
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateCountryCode"));

   if (countryCode.empty())
   {
      getErrMsg ( IFASTERR::BANK_COUNTRY_CODE_REQUIRED,
                  CND::ERR_BANK_COUNTRY_CODE_REQUIRED, 
                  CND::WARN_BANK_COUNTRY_CODE_REQUIRED, 
                  idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::eftRedemptionRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,  CLASSNAME, I_("eftRedemptionRelatedChanges"));

   DString dstrAcctUsage, dstrCurrency;

   getField (ifds::AcctUseCode, dstrAcctUsage, idDataGroup);
   getField (ifds::BankAcctCurrency, dstrCurrency, idDataGroup);

   if (dstrAcctUsage.empty() || dstrCurrency.empty ())
      return GETCURRENTHIGHESTSEVERITY ();

   DString dstrSwitchBanks;

   getWorkSession ().getOption ( ifds::SwitchBanks, dstrSwitchBanks, idDataGroup, false);

   if (dstrSwitchBanks == NO)
      return GETCURRENTHIGHESTSEVERITY();

   BankInstructionsList *pBankInstructionsList = dynamic_cast<BankInstructionsList*>( getParent( ) );      

   if (pBankInstructionsList && (isShareholderBank (idDataGroup) || isAccountBank(idDataGroup) ) )
      pBankInstructionsList->switchToAlternativeEFTRedemption (this, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::eftPurchaseRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,  CLASSNAME, I_("eftPurchaseRelatedChanges"));

   DString dstrAcctUsage, 
      dstrCurrency;

   getField (ifds::AcctUseCode, dstrAcctUsage, idDataGroup);
   getField (ifds::BankAcctCurrency, dstrCurrency, idDataGroup);

   dstrAcctUsage.strip().upperCase();
   if (!dstrAcctUsage .empty())
   {
      bool bFFCReadonly = ((isShareholderBank(idDataGroup) || isAccountBank(idDataGroup) ||
                           isTradeBank(idDataGroup) ||
                           isPendingTradeBank(idDataGroup) ||
                           isTransactionBank(idDataGroup) ||
						   isRegAgentBank(idDataGroup)) &&
                           (dstrAcctUsage == AcctUseCode::EFT_PURCHASE ||
                           dstrAcctUsage == AcctUseCode::ALT_EFT_PURCHASE));
      setFieldsReadOnly (fieldsInBankFFC, numFieldsInBankFFC, idDataGroup, bFFCReadonly);
   }

   if (dstrAcctUsage.empty() || dstrCurrency.empty ())
      return GETCURRENTHIGHESTSEVERITY ();


   DString dstrSwitchBanks;

   getWorkSession ().getOption ( ifds::SwitchBanks, dstrSwitchBanks, idDataGroup, false);

   if (dstrSwitchBanks == NO)
      return GETCURRENTHIGHESTSEVERITY();

   BankInstructionsList *pBankInstructionsList = dynamic_cast<BankInstructionsList*>( getParent( ) );      

   if (pBankInstructionsList && (isShareholderBank (idDataGroup)|| isAccountBank(idDataGroup)))
   {
      pBankInstructionsList->switchToAlternativeEFTPurchase (this, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//methods that determine the type of bank
//******************************************************************************
bool BankInstructions::isDistributorBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::BROKER || 
          bankInstrType == BANKTYPE::BRANCH ||
          bankInstrType == BANKTYPE::SALESREP;
}

//******************************************************************************
bool BankInstructions::isShareholderBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::SHAREHOLDER;
}
//******************************************************************************
bool BankInstructions::isAccountBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return ( bankInstrType ==  BANKTYPE::ACCOUNT);
}
//******************************************************************************
bool BankInstructions::isDistributionBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::DISTRIBUTION;
}

//******************************************************************************
bool BankInstructions::isRRIFBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::RRIF;
}

//******************************************************************************
bool BankInstructions::isSystematicBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::SYSTEMATIC;
}

//******************************************************************************
bool BankInstructions::isSettlementBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::SETTLEMENT;
}

//******************************************************************************
bool BankInstructions::isFundBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::FUND || 
      bankInstrType == BANKTYPE::FUND_CLASS;
}

//******************************************************************************
bool BankInstructions::isClientBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::CLIENT;
}

//******************************************************************************
bool BankInstructions::isDirectTradingBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::DIRECT_TRADING;
}

//******************************************************************************
bool BankInstructions::isTradeBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::TRADE;
}

//******************************************************************************
bool BankInstructions::isPendingTradeBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::PENDING_TRADE;
}

//******************************************************************************
bool BankInstructions::isTransactionBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::TRANSACTION;
}

//******************************************************************************
bool BankInstructions::isFundGroupBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::FUND_GROUP;
}

//******************************************************************************
bool BankInstructions::isFundSponsorBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::FUND_SPONSOR;
}

/***************************************************************************************
Input:DatdGroupID
Output:None
Return:Bool
Functionality:Determines the Bank Type is regAgentBank
***************************************************************************************/
//***************************************************************************************
bool BankInstructions::isRegAgentBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::REG_AGENT;
}

//***************************************************************************************
bool BankInstructions::isMaturityBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS;
}

//***************************************************************************************
bool BankInstructions::isAcctCommitBank (const BFDataGroupId &idDataGroup)
{
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   return bankInstrType == BANKTYPE::ACCOUNT_COMMITMENT;
}

//******************************************************************************
bool BankInstructions::isNonStaticDataBank (const BFDataGroupId &idDataGroup)
{
   bool bBank = isTradeBank (idDataGroup) || 
                isSettlementBank (idDataGroup) ||
                isPendingTradeBank (idDataGroup) || 
                isTransactionBank (idDataGroup) ||
                isDistributionBank (idDataGroup) || 
                isRRIFBank (idDataGroup) ||
                isSystematicBank (idDataGroup)? true : false;

   return bBank;
}

//******************************************************************************
bool BankInstructions::isBankTransitNumRequired (const DString &bankInstrType)
{
   int nTransitMaxLength = -1;
   int nAllTransitMaxLength = -1;
   bool bIsAllDigits = false;
   bool bBankInfoFound = FinancialInstitution::getBankTransitNumInfo (
      bankInstrType, 
      nTransitMaxLength, 
      bIsAllDigits, 
      nAllTransitMaxLength);

   return nTransitMaxLength > 0;
}

//******************************************************************************
SEVERITY BankInstructions::validateBankAcctUseCodeCurrType(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateBankAcctUseCodeCurrType"));
   // validation logic!
   // it must be client account type with non-register tax
   // canadian banktype (03) canadian currency (CDN)
   // direct deposit account use code
   DString strAccountNum;
   DString strCurrntMarket;
   DString strCanadaMarket = MARKET_IDS::CANADA;
   strCanadaMarket.strip().upperCase();
   strCurrntMarket = DSTCommonFunctions::getMarket();
   strCurrntMarket.strip().upperCase();
   
   getParent ()->getField (ifds::AccountNum, strAccountNum, idDataGroup, false);

   if (!strAccountNum.empty () && ( strCurrntMarket == strCanadaMarket ))
   {
      MFAccount *pMFAccount = NULL;

      if (getWorkSession ().getMFAccount (idDataGroup, strAccountNum, 
            pMFAccount) <= WARNING && pMFAccount)
      {
         DString strAcctUseCode;
         getField( ifds::AcctUseCode, strAcctUseCode, idDataGroup,false);
         if ( strAcctUseCode.strip().upperCase() == AcctUseCode::DIRECT_DEPOSIT )
         {
            DString strBankIdType,
                    strBankAcctCurrency,
                    strBrokerCode,
                    strBranchCode,
                    strSlsrep,
                    strTaxType,
                    strAcctDesignation;
                    
            pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup,false);
            pMFAccount->getField( ifds::AcctDesignation, strAcctDesignation, idDataGroup,false);

            if ( isShareholderBank (idDataGroup)|| isAccountBank(idDataGroup) || isRegAgentBank(idDataGroup))
            {
               if ( strTaxType != NON_REGISTERED_TAX_TYPE || strAcctDesignation != CLIENT_ACCOUNT_DESIGNATION ) 
               {
                  getErrMsg ( IFASTERR::DIRECT_DEPST_SHRHLDR_ONLY, 
                              CND::ERR_DIRECT_DEPST_SHRHLDR_ONLY, 
                              CND::WARN_DIRECT_DEPST_SHRHLDR_ONLY, 
                              idDataGroup);
                  return GETCURRENTHIGHESTSEVERITY ();
               }
            }
            else
            {
               // allow user to override direct deposit bank for
               // trade, settlement
               if ( !isTradeBank (idDataGroup) && !isSettlementBank(idDataGroup) )
               {
                  getErrMsg ( IFASTERR::DIRECT_DEPST_SHRHLDR_ONLY, 
                              CND::ERR_DIRECT_DEPST_SHRHLDR_ONLY, 
                              CND::WARN_DIRECT_DEPST_SHRHLDR_ONLY, 
                              idDataGroup);
                  return GETCURRENTHIGHESTSEVERITY ();
               }
            }

            getField( ifds::BankIdType, strBankIdType, idDataGroup,false);
            
            if ( strBankIdType.strip().upperCase() != CANADIAN_BANK )
            {
               getErrMsg ( IFASTERR::DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY, 
                           CND::ERR_DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY, 
                           CND::WARN_DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY, 
                           idDataGroup);
               return GETCURRENTHIGHESTSEVERITY ();
            }

            getField( ifds::BankAcctCurrency, strBankAcctCurrency, idDataGroup,false);
            strBankAcctCurrency.strip().upperCase();
            if ( !DSTCommonFunctions::codeInList( strBankAcctCurrency, CANADIAN_DOLLAR_LIST) )
            {
               getErrMsg ( IFASTERR::DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY, 
                           CND::ERR_DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY, 
                           CND::WARN_DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY, 
                           idDataGroup);
               return GETCURRENTHIGHESTSEVERITY ();
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::validateAcctUseCodeForInvestorAuthorizationInfo(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAcctUseCodeForInvestorAuthorizationInfo"));

   DString dstrDirectDepositBankApplicable, dstrAcctUseCode, strCurrBusDate;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, 
                                 dstrDirectDepositBankApplicable, 
                                 BF::HOST, 
                                 false);
                                 
   getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup, false );
   getWorkSession().getOption (ifds::CurrBusDate, strCurrBusDate, idDataGroup, false);

   // looking for IA record if baning instruction is direct deposit
   if ( dstrDirectDepositBankApplicable == YES &&
        (isShareholderBank (idDataGroup) || isAccountBank(idDataGroup))&&
        dstrAcctUseCode == AcctUseCode::DIRECT_DEPOSIT )
   {
      DString strAccountNum;

      getParent ()->getField (ifds::AccountNum, strAccountNum, idDataGroup, false);
      if (!strAccountNum.empty () )
      {
         MFAccount *pMFAccount = NULL;
         DString strBankEffDate, strBankStopDate;

         getField( ifds::EffectiveDate, strBankEffDate, idDataGroup, false );
         getField( ifds::StopDate, strBankStopDate, idDataGroup, false );

         if (getWorkSession ().getMFAccount (idDataGroup, strAccountNum, 
               pMFAccount) <= WARNING && pMFAccount)
         {
            bool bFoundIAInstructions = false;
            std::vector<DString> vDateList;
            InvestorAuthorizationList *pInvestorAuthorizationList = NULL;
            if( pMFAccount->getInvestorAuthorizationList(pInvestorAuthorizationList,
                                                         idDataGroup) <= WARNING || 
                                                         pInvestorAuthorizationList )
            {
               BFObjIter iter ( *pInvestorAuthorizationList, 
                                 idDataGroup);

               DString strIAEffDate, strIANextEffDate, strIAStopDate, strIANextStopDate,
                       strAcctAuthRid;

               vIARecordPeriod IARecordPeriods;

               while (!iter.end())
               {
                  iter.getObject()->getField( ifds::EffectiveDate, strIAEffDate, idDataGroup, false );
                  iter.getObject()->getField (ifds::StopDate, strIAStopDate, idDataGroup, false);
                  iter.getObject()->getField( ifds::AcctAuthRid, strAcctAuthRid, idDataGroup, false );

                  IARecordPeriod newElement;
                  newElement.strEffectiveDate = strIAEffDate;
                  newElement.strStopDate = strIAStopDate;
                  newElement.strAcctAuthRid = strAcctAuthRid;

                  IARecordPeriods.push_back(newElement);
                  ++iter;
               }

               if ( iter.getNumberOfItemsInList() > 1)
               {
                  sort(IARecordPeriods.begin(), 
                       IARecordPeriods.end(), 
                       BankInstructions::sortByEffectiveDate );
               }

               vIARecordPeriod::iterator iterIARecordPeriods = 
                  IARecordPeriods.begin();

               // make long period
               while( iterIARecordPeriods     != IARecordPeriods.end() &&
                      iterIARecordPeriods + 1 != IARecordPeriods.end() )
               {
                  DString strIAEffDate, strIAStopDate, strIANxtEffDate, strIANxtStopDate;

                  IARecordPeriod iaRecordPeriod = *(iterIARecordPeriods);
                  IARecordPeriod iaNxtRecordPeriod = *(iterIARecordPeriods+1);

                  strIAEffDate = iaRecordPeriod.strEffectiveDate;
                  strIAStopDate = iaRecordPeriod.strStopDate;
                  strIANxtEffDate = iaNxtRecordPeriod.strEffectiveDate;
                  strIANxtStopDate = iaNxtRecordPeriod.strStopDate;

                  DString strTestDate;
                  DSTCommonFunctions::addDays(strIAStopDate,strTestDate,1);
                  if( DSTCommonFunctions::CompareDates( strTestDate, strIANxtEffDate ) == 
                      DSTCommonFunctions::EQUAL )
                  {
                     iterIARecordPeriods->strEffectiveDate = strIAEffDate;
                     iterIARecordPeriods->strStopDate = strIANxtStopDate;
                     IARecordPeriods.erase(iterIARecordPeriods+1);

                     continue;
                  }
                  ++iterIARecordPeriods;
               }

               iterIARecordPeriods = IARecordPeriods.begin();
               while( iterIARecordPeriods != IARecordPeriods.end() )
               {
                  DString strIAEffDate, strIAStopDate, strIANextStopDate;

                  IARecordPeriod iaRecordPeriod = *(iterIARecordPeriods);

                  strIAEffDate = iaRecordPeriod.strEffectiveDate;
                  strIAStopDate = iaRecordPeriod.strStopDate;

                  if ( DSTCommonFunctions::IsDateBetween( strBankEffDate, strBankStopDate, strIAEffDate ) && 
                       DSTCommonFunctions::CompareDates( strBankEffDate, strIAEffDate ) == 
                        DSTCommonFunctions::FIRST_EARLIER )
                  {
                     vDateList.push_back( strBankEffDate );
                     break;
                  }
                  else if ( DSTCommonFunctions::IsDateBetween( strBankEffDate, strBankStopDate, strIAStopDate ) && 
                            DSTCommonFunctions::CompareDates( strBankStopDate, strIAStopDate ) == 
                              DSTCommonFunctions::SECOND_EARLIER )
                  {
                     DSTCommonFunctions::addDays(strIAStopDate,strIANextStopDate,1);
                     vDateList.push_back( strIANextStopDate );
                     break;
                  }
                  ++iterIARecordPeriods;
               }
            }

            // after cleaning, if there is still date existing in list 
            // it should be displayed as begining of gap
            if ( vDateList.size() > 0 )
            {
               std::vector<DString>::iterator itDateLists = vDateList.begin();

               DString strErrorDateFmt = *(itDateLists); // get only first of list to display
               DSTCommonFunctions::FormatDate(strErrorDateFmt);
               DString dstrIDI;
               addIDITagValue (dstrIDI, I_("DATE"), strErrorDateFmt);
               //ADDCONDITIONFROMFILEIDI (CND::WARN_INVESTOR_AUTHORIZATION_INFO_MISSING_ON_DATE , dstrIDI);
               getErrMsg ( IFASTERR::INVESTOR_AUTHORIZE_FOR_DIRECT_DEPOSIT_BANK_MISSING, 
                           CND::ERR_INVESTOR_AUTHORIZATION_INFO_MISSING, 
                           CND::WARN_INVESTOR_AUTHORIZATION_INFO_MISSING, 
                           idDataGroup, 
                           dstrIDI);
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::validateBankForIA( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateBankForIA"));

   DString dstrDirectDepositBankApplicable,
            dstrAcctUseCode;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, 
                                 dstrDirectDepositBankApplicable, 
                                 BF::HOST, false);

   getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup, false ); 

   if (( isShareholderBank (idDataGroup)|| isAccountBank(idDataGroup)) && dstrDirectDepositBankApplicable == YES && 
         dstrAcctUseCode == AcctUseCode::DIRECT_DEPOSIT )
   {
      DString dstrAccountNum, dstrEffectiveDate, dstrAcctEffDate;

      getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      if ( !dstrAccountNum.empty() )
      {
         MFAccount *pMFAccount = NULL;
         if (getWorkSession ().getMFAccount (idDataGroup, dstrAccountNum, 
               pMFAccount) <= WARNING && pMFAccount)
         {
            getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false ); 
            pMFAccount->getField( ifds::EffectiveDate, dstrAcctEffDate, idDataGroup, false );
            
            if ( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrAcctEffDate ) == 
                  DSTCommonFunctions::FIRST_EARLIER )
            {
               ADDCONDITIONFROMFILE (CND::ERR_DIRECT_DPST_BANK_BEFORE_ACCT_EFFDATE);
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBankForIA"));

   bool bReadOnly = false;
   DString bankInstrType;
   DString modUser;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   getField (ifds::VerifyStat, _dstrVerifyStatus, idDataGroup, false);
   getField (ifds::ModUser, modUser, idDataGroup, false);

   if (modUser.empty()) // is empty only for new records that have not been modified.
   {
      getField (ifds::Username, modUser, idDataGroup, false);
      modUser.strip().upperCase();
   }

   DString bankEntity =  getBankingEntity (bankInstrType);

   getWorkSession ().canVerify (idDataGroup, UAF::BANKING_VERIFICATION, BANKING_LEVEL, bankEntity, modUser, _bCanVerify); 
   getWorkSession ().isVerificationEnabled (idDataGroup, BANKING_LEVEL, bankEntity, _bVerificationEnabled);   

   // enviroment level:
   if (_bVerificationEnabled)
   {
      // field level:
      bReadOnly = !_bCanVerify;

      if (isNonStaticDataBank (idDataGroup))
      {
         if (!bNew || (bNew && !_bGetsCloned))
         {
            setFieldReadOnly (ifds::VerifyStat, idDataGroup, false);
            setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false, true, true);
         }

         bReadOnly = true;
      }
      else 
      {
         if (bNew && !_bGetsCloned)
         {
            setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
            bReadOnly = true;
         }
         // if data is verified is from backend, lock verify stat
         if ( idDataGroup == BF::HOST )
         {
            DString strVerifyStat;
            getField( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
            strVerifyStat.strip().upperCase();
            
            if (strVerifyStat == VERIFIED )
            {
               bReadOnly = true;
            }
         }
      }
   }
   else
   {
      // enviroment does not support bank verficaiton
      // Verify Status is read only
      // Verify Status on new bank is set to Verified.
      //if (bNew)
      {
         setFieldNoValidate (ifds::VerifyStat,VERIFIED, idDataGroup, false);
      }
	  
      bReadOnly = true;
   }

   setFieldReadOnly (ifds::VerifyStat, idDataGroup, bReadOnly);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY BankInstructions::validateStopDateEffDate(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateStopDateEffDate"));

   DString strEffDate, strStopDate;

   getField( ifds::EffectiveDate, strEffDate, idDataGroup, false );
   getField( ifds::StopDate , strStopDate, idDataGroup, false );

   strEffDate.strip();
   strStopDate.strip();

   DSTCommonFunctions::DATE_ORDER result = 
      DSTCommonFunctions::CompareDates( strStopDate, strEffDate );

   if( result == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE (CND::WARN_EFFECTIVE_DATE_AFTER_STOP_DATE);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
DString BankInstructions::getBankingEntity(const DString& strBankType)
{
   DString strBankEntity = NULL_STRING;
   DString strBankTypeCopy(strBankType);

   // mapping need to be the same as in misc-info only for VerifyStatus field:
   strBankTypeCopy.strip();
   if (strBankTypeCopy == BANKTYPE::SHAREHOLDER ||
       strBankTypeCopy == BANKTYPE::ACCOUNT || 
       strBankTypeCopy == BANKTYPE::DIRECT_TRADING ||
       strBankTypeCopy == BANKTYPE::TRADE ||
       strBankTypeCopy == BANKTYPE::TRANSACTION ||
       strBankTypeCopy == BANKTYPE::PENDING_TRADE ||
       strBankTypeCopy == BANKTYPE::SYSTEMATIC ||
       strBankTypeCopy == BANKTYPE::RRIF ||
       strBankTypeCopy == BANKTYPE::DISTRIBUTION ||
       strBankTypeCopy == BANKTYPE::SETTLEMENT)
   {
      strBankEntity = I_("01");
   }
   else if (strBankTypeCopy == BANKTYPE::CLIENT)
   {
      strBankEntity = I_("10");
   }
   else if (strBankTypeCopy == BANKTYPE::BROKER)
   {
      strBankEntity = I_("06");
   }
   else if (strBankTypeCopy == BANKTYPE::BRANCH)
   {
      strBankEntity = I_("07");
   }
   else if (strBankTypeCopy == BANKTYPE::SALESREP)
   {
      strBankEntity = I_("08");
   }
   else if (strBankTypeCopy == BANKTYPE::FUND)
   {
      strBankEntity = I_("09");
   }
   else if (strBankTypeCopy == BANKTYPE::FUND_CLASS)
   {
      strBankEntity = I_("04");
   }
   else if( strBankTypeCopy == BANKTYPE::FUND_GROUP)
   {
      strBankEntity = I_("03");
   }
   else if (strBankTypeCopy == BANKTYPE::FUND_SPONSOR)
   {
      strBankEntity = I_("05");
   }
   else if (strBankTypeCopy == BANKTYPE::REG_AGENT)
   {
	  strBankEntity = I_("11");
   }
   return strBankEntity;
}

//******************************************************************************
void BankInstructions::setFieldsDistribBankReadOnly ( const BFDataGroupId &idDataGroup, 
                                                      bool bReadOnly)
{
   if ( isDistributionBank(idDataGroup) )
   {
      setFieldsReadOnly( fieldsInBeneficialBank, numFieldsInBeneficialBank, idDataGroup, bReadOnly );
      setFieldsReadOnly( fieldsInCorresBank, numFieldsInCorresBank, idDataGroup, bReadOnly );
      setFieldsReadOnly( fieldsInBankOption, numFieldsInBankOption, idDataGroup, bReadOnly );
      setFieldsReadOnly( fieldsInBankGenInfo, numFieldsInBankGenInfo, idDataGroup, bReadOnly );
   }
}

//cloning methods
//******************************************************************************
SEVERITY BankInstructions::cloneInto ( SystematicBankInstructions *&pBankInstructions, 
                                       BFAbstractCBO *pParent, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cloneInto"));

   return cloneInto_X (pBankInstructions, pParent, idDataGroup);
}

//******************************************************************************
SEVERITY BankInstructions::cloneInto ( DistributionBankInstructions *&pBankInstructions, 
                                       BFAbstractCBO *pParent, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cloneInto"));

   return cloneInto_X (pBankInstructions, pParent, idDataGroup);
}

//******************************************************************************
SEVERITY BankInstructions::cloneInto ( RRIFBankInstructions *&pBankInstructions, 
                                       BFAbstractCBO *pParent, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cloneInto"));

   return cloneInto_X (pBankInstructions, pParent, idDataGroup);
}

//******************************************************************************
SEVERITY BankInstructions::cloneInto ( SettlementTradeBankInstructions *&pBankInstructions, 
                                       BFAbstractCBO *pParent, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cloneInto"));

   return cloneInto_X (pBankInstructions, pParent, idDataGroup);
}

//******************************************************************************
SEVERITY BankInstructions::cloneInto ( TradeBankInstructions *&pBankInstructions, 
                                       BFAbstractCBO *pParent, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cloneInto"));

   return cloneInto_X (pBankInstructions, pParent, idDataGroup);
}

//******************************************************************************
SEVERITY BankInstructions::cloneInto ( MatSweepInstrBank *&pBankInstructions, 
                                       BFAbstractCBO *pParent, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cloneInto"));

   return cloneInto_X (pBankInstructions, pParent, idDataGroup);
}

//******************************************************************************
SEVERITY BankInstructions::cloneInto ( AcctCommitBank *&pBankInstructions, 
                                       BFAbstractCBO *pParent, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cloneInto"));

   return cloneInto_X (pBankInstructions, pParent, idDataGroup);
}

//******************************************************************************
SEVERITY BankInstructions::cloneInto ( ContractMatInstrBank *&pBankInstructions, 
                                       BFAbstractCBO *pParent, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cloneInto"));

   return cloneInto_X (pBankInstructions, pParent, idDataGroup);
}

//******************************************************************************
template <class _X>
   SEVERITY BankInstructions::cloneInto_X ( _X *&pBankInstructions, 
                                            BFAbstractCBO *pParent, 
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("cloneInto"));
//build a data object, so we can get the values from 'this' BankInstructions object
   BFData rpBFData0052Repeat (ifds::DSTC0052_VWRepeat_Record);
   
   pBankInstructions = NULL;
   if (getData (rpBFData0052Repeat, idDataGroup) <= WARNING)
   {
//init the banking object, as if it was a new object, 
//but do not copy the data from the parent
//tell to the 'initNew' method that this is a cloned object
      pBankInstructions = new _X (*pParent);
      if ( pBankInstructions->initBeforeCloning (idDataGroup) > WARNING || 
           pBankInstructions->setData (rpBFData0052Repeat, idDataGroup) > WARNING ||
           pBankInstructions->initNew (idDataGroup, true) > WARNING)
      {
//if something went wrong, delete
         delete pBankInstructions;
         pBankInstructions = NULL;
      }
   }
   if (pBankInstructions)
   {
      if (pBankInstructions->_bGetsCloned)
      {
         pBankInstructions->_bGetsCloned = false;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
/******************************************************************************
Input:None
Output:BFDataGroupID
Return:bool
Functionality:Detrmines if the Banking Instructions is for Redirect to RegAgent .
******************************************************************************/
bool BankInstructions::bIsRedirect2RegAgentInst(const BFDataGroupId &idDataGroup)
{
   DString dstrPayInstrOption,dstrBankType; 
   //assert(getParent()->getParent());//get from trade
   //getParent()->getParent()->
   getField (ifds::PayInstrOption, dstrPayInstrOption, idDataGroup);
   return(isTradeBank(idDataGroup) && (I_("03") == dstrPayInstrOption.stripAll())); 
}
/******************************************************************************
Input:DatdGroupID
Output: bIsDirty
Return:bool
Functionality:Detrmines if the Banking screen is updated by user and object is dirty
******************************************************************************/
bool BankInstructions::isBankingUpdatedByUser(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isBankingUpdatedByUser"));
	return isObjectDirty(idDataGroup);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructions.cpp-arc  $
 * 
 *    Rev 1.159   Apr 24 2012 20:52:56   wp040039
 * PETP0187485-Trade Entry And Processing
 * 
 *    Rev 1.158   Apr 03 2012 20:11:34   wp040039
 * PETP0187485-Registartion Agent  Banking
 * 
 *    Rev 1.157   Mar 02 2012 16:39:12   wp040100
 * P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
 * 
 *    Rev 1.156   Feb 24 2012 18:40:32   if991250
 * Account Commitment
 * 
 *    Rev 1.155   Feb 02 2012 15:05:08   if991250
 * Maturity/Interest Instructions banking
 * 
 *    Rev 1.154   Apr 29 2011 16:00:36   popescu
 * IN 2500714 - FCC Information field in Desktop greyed out
 * 
 *    Rev 1.153   Apr 26 2011 13:13:12   popescu
 * IN 2500714 - FCC Information field in Desktop greyed out
 * 
 *    Rev 1.152   Apr 21 2011 13:26:44   jankovii
 * IN 2500714 - FCC Information field in Desktop greyed out
 * 
 *    Rev 1.151   Mar 25 2011 17:16:54   popescu
 * IN# 2466703 - P11.3PR-PET0179308FN01-DSK correspondent bank info for EFT ED Bank
 * 
 *    Rev 1.150   Mar 23 2011 13:38:52   dchatcha
 * IN# 2466703 - P11.3PR-PET0179308FN01-DSK correspondent bank info for EFT ED Bank
 * 
 *    Rev 1.149   Feb 18 2011 10:18:02   kitticha
 * PET0179308_FN01_IN2431866 - Remove the DSK logic to make the Correspondent & Originator required.
 * 
 *    Rev 1.148   Feb 18 2011 09:45:40   kitticha
 * PET0179308_FN01_IN2431866 - Remove the DSK logic to make the Correspondent & Originator required.
 * 
 *    Rev 1.147   Jan 31 2011 18:08:52   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.146   Dec 02 2010 15:44:02   jankovii
 * PET171086 FN01 Red Flag Report.
 * 
 *    Rev 1.145   Mar 08 2010 12:14:06   popescu
 * Incident 2039534 - fixed the issue where unverified banking instruction are not copied with the proper value of the verify status field. they get reset to verified, if they are un-verified
 * 
 *    Rev 1.144   Mar 04 2010 17:39:26   popescu
 * Incident 2033491 - Issue with the default value of the Verified field in envs where static data is turned off
 * 
 *    Rev 1.143   Mar 04 2010 17:17:34   popescu
 * Incident 2033491 - User is able to select Verified or Unverified when hitting RESET - issue fixed for banking/address and distribution
 * 
 *    Rev 1.142   Mar 03 2010 14:43:02   popescu
 * Incident 2033491 - User is able to select Verified or Unverified when hitting RESET - issue fixed for banking/address and distribution
 * 
 *    Rev 1.141   Jan 13 2010 09:27:12   dchatcha
 * IN# 1971377 - R97_Static Data_File Processor&Bank are blank after deleting distribution option.
 * 
 *    Rev 1.140   Jan 12 2010 15:34:24   jankovii
 * IN 1964321 & 1964324 - Static data issues.
 * 
 *    Rev 1.139   Dec 03 2009 10:37:50   jankovii
 * PET0166583 FN01 Static Data Changes Banking .
 * 
 *    Rev 1.138   Dec 01 2009 11:48:50   jankovii
 * PET0166583 FN01 Static Data Changes Banking .
 * 
 *    Rev 1.137   Nov 27 2009 06:12:38   dchatcha
 * Synch up: IN# 1872743 - PET156681-FN14 Inactive Banking a/c warning message, QA test failed due multiple records without gap still display warning.
 * 
 *    Rev 1.136   Nov 26 2009 14:28:36   popescu
 * #1357237 - transit# should be required
 * 
 *    Rev 1.135   Nov 26 2009 13:22:52   jankovii
 * PET0166583 FN01 Static Data Changes Banking 
 * 
 *    Rev 1.134   Nov 23 2009 16:22:00   jankovii
 * PET0166583 FN01 Static Data Changes Banking 
 * 
 *    Rev 1.133   Nov 17 2009 15:20:42   jankovii
 * PET0166583 FN01 Static Data Changes Banking 
 * 
 *    Rev 1.132   Oct 26 2009 09:49:18   dchatcha
 * IN# 1872743 - PET156681-FN14 Inactive Banking a/c warning message.
 * 
 *    Rev 1.131   Sep 25 2009 15:53:52   popescu
 * #1357237 - More fix : fix the problem when changing around the id type cause transit become non-require.
 * 
 *    Rev 1.130   Sep 02 2009 14:40:44   wutipong
 * #1357237 - More fix : fix the problem when changing around the id type cause transit become non-require.
 * 
 *    Rev 1.129   Aug 21 2009 10:09:58   dchatcha
 * Synch up: IN#1808388 - R95 - Inv Auth - Error returned for multiple active banking instruction.
 * 
 *    Rev 1.128   Aug 18 2009 09:31:34   wutipong
 * #1357237 - parts of code changes are reverted, based on Zijian's suggestion.
 * 
 *    Rev 1.127   Aug 04 2009 21:21:40   wutipong
 * #1357237 Trade settled w/ no institiution and branch#. ECF
 * 
 *    Rev 1.126   Jul 22 2009 08:20:26   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Code review. 
 * 
 *    Rev 1.125   Jul 16 2009 19:12:14   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Integration issues.
 * 
 *    Rev 1.124   Jul 10 2009 14:14:26   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Code review.
 * 
 *    Rev 1.123   Jul 09 2009 14:59:34   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.121   29 Jun 2009 17:03:22   popescu
 * PET 156681 - FN 14 - Investor Authorization
 * 
 *    Rev 1.120   29 Jun 2009 16:08:18   popescu
 * PET 156681 - FN 14 - Investor Authorization
 * 
 *    Rev 1.119   09 Jun 2009 14:58:24   popescu
 * Incident 1720498 - opened up correspondant banking for distribution banking EFT_Dividend account usage code = 16
 * 
 *    Rev 1.118   Mar 13 2009 14:03:24   jankovii
 * IN 1357237 - Trade settled w/ no institiution and branch#. ECF
 * 
 *    Rev 1.117   10 Mar 2009 16:19:26   kovacsro
 * IN#1606065 - PET155543R92 File processor is blank when Bank Use is EFT Dividend
 * 
 *    Rev 1.116   09 Mar 2009 11:12:38   kovacsro
 * IN#1609264 - PET155543R92 Bank name not display in acct level distrib instruction
 * 
 *    Rev 1.115   Dec 22 2008 13:15:34   jankovii
 * IN 1338777 - Alternate EFT Redemption banking instruction application issue
 * 
 *    Rev 1.114   02 Jul 2008 08:41:46   kovacsro
 * Backed out IN#1215473 at client's request
 * 
 *    Rev 1.111.1.1   26 Jun 2008 15:48:06   popescu
 * IN1325445 - Sev 1 required - Problem with Bank payment records - for 85 - fixed a copy/paste error
 * 
 *    Rev 1.111.1.0   25 Jun 2008 14:53:26   popescu
 * IN1325445 - Sev 1 required - Problem with Bank payment records - for 85
 * 
 *    Rev 1.111   29 Feb 2008 14:46:32   kovacsro
 * IN#1200300 - blank out bank name&address when creating new institution (to prevent users from blindly copying over bad data)
 * 
 *    Rev 1.110   Feb 20 2008 09:51:28   jankovii
 * PET 2385 FN06 Bank Details upload.
 * 
 *    Rev 1.109   Apr 18 2007 16:31:24   jankovii
 * IN#860345 - Cannot add Correspondent Banking details at Broker level.
 * 
 *    Rev 1.108   Dec 21 2006 14:28:04   jankovii
 * Incident #779493 - Enabled corresponding bank fields for "Default" account usage type.
 * 
 *    Rev 1.107   Oct 18 2006 15:53:24   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.106   Oct 16 2006 09:18:02   porteanm
 * Incident 733900 - File processor not saved for Redemption banking. This is more to be consistent with Distribution since for PW the process is different.
 * 
 *    Rev 1.105   Oct 12 2006 14:32:48   porteanm
 * Incident XXXXXX - File processor not saved for Distribution banking.
 * 
 *    Rev 1.104   Sep 21 2006 19:28:10   popescu
 * STP PET 2213/17
 * 
 *    Rev 1.103   Sep 12 2006 10:51:58   popescu
 * STP - PET 2192/11
 * 
 *    Rev 1.102   Sep 10 2006 17:58:22   popescu
 * STP 2192/12
 * 
 *    Rev 1.101   Jul 31 2006 15:27:40   ZHANGCEL
 * PET2192 FN11 -- MgmtCo Banking related changes
 * 
 *    Rev 1.100   Jun 09 2006 16:54:42   popescu
 * Incident# 640012 - distribution banking is shown for processed transactions
 * 
 *    Rev 1.99   Nov 30 2005 10:21:14   zhengcon
 * Incident #458619 -- fixed problem that the correspondent banking details will not be saved
 * 
 *    Rev 1.98   Nov 09 2005 14:12:22   popescu
 * Incident# 446956 - opened up corresp. banking info for trading/pending trades/trans history
 * 
 *    Rev 1.97   Jan 18 2005 12:53:46   popescu
 * PTS 10037935, added new rej-error code to control whether bank information country code is mandatory or not
 * 
 *    Rev 1.96   Dec 17 2004 11:28:38   popescu
 * PTS 10036680, restored file processor at shareholder level banking, for API use, and removed copying the file processor for SettlementTrade banking if bank is cloned. This is a synch-up from release 58.
 * 
 *    Rev 1.95   Nov 23 2004 12:28:44   popescu
 * PET 1117/06 new acct usage code, (12-Absatzmeldung)
 * 
 *    Rev 1.94   Nov 14 2004 14:28:08   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.93   Nov 07 2004 17:29:50   popescu
 * PET 1117/06, added 4 new fields to class field info
 * 
 *    Rev 1.92   Nov 04 2004 17:37:08   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.91   Sep 23 2004 10:09:40   popescu
 * PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
 * 
 *    Rev 1.90   Sep 21 2004 13:33:10   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.  Added isFundGroupBank.
 * 
 *    Rev 1.89   Sep 15 2004 16:22:40   popescu
 * PET 1094/06, file processor is not applicable for fund sponsor banking
 * 
 *    Rev 1.88   Sep 14 2004 16:11:28   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface - Purchase support.
 * 
 *    Rev 1.87   Sep 14 2004 14:53:36   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files Enhancement - Added constant.
 * 
 *    Rev 1.86   Sep 08 2004 17:57:52   ZHANGCEL
 * PET1094-FN8 -- AdminFee related changes
 * 
 *    Rev 1.85   Sep 01 2004 16:13:34   VADEANUM
 * PET 1094 FN4 - Activest Bank File - Renamed ACHPACSWP to ACHPAC and intorduced ACHSWP.
 * 
 *    Rev 1.84   Sep 01 2004 16:01:06   ZHANGCEL
 * PET1094_FN8 -- New Fee Type related change
 * 
 *    Rev 1.83   Jul 22 2004 09:56:28   popescu
 * PTS 10027951, acct usage of the banking infor for a CASH ID transaction is displayed as 'EFT Dividend'
 * 
 *    Rev 1.82   May 06 2004 11:11:24   popescu
 * PTS 10029945, removed striping the leading zeros when retrieving the banking info for numerical bank ids
 * 
 *    Rev 1.81   May 04 2004 10:29:44   FENGYONG
 * PTS 10029835, Settlement banking
 * 
 *    Rev 1.80   Apr 05 2004 16:25:38   popescu
 * PTS 10028532, reset button doesn' work properly
 * 
 *    Rev 1.79   Apr 01 2004 10:51:36   popescu
 * PTS 10028751,  sunch-up version 1.74.1.3 from release 55.1.1
 * 
 *    Rev 1.78   Mar 25 2004 17:53:02   popescu
 * PTS 10028543, synch-up from release 55.1.1, v 1.74.1.2
 * 
 *    Rev 1.77   Mar 05 2004 10:46:34   popescu
 * PTS 10027880, synch-up from release 55.0.4, v 1.74.1.1
 * 
 *    Rev 1.76   Mar 04 2004 18:58:54   popescu
 * PTS 10027880, synch-up from release 55.0.4, v 1.74.1.0
 * 
 *    Rev 1.75   Feb 14 2004 13:52:44   popescu
 * PET965.FN1 SSB Profile restriction, re-added the banking files to avoid branching
 * 
 *    Rev 1.74   Feb 13 2004 18:04:34   popescu
 * PTS 10027188, copy the value of the file processor field into trading screen, and trade banking screen, when modifying a pending trade; removed the substitution list of the BankInstrType, since the combo is being loaded anyhow in the dialog. This field is not  updatable. Assign the correct transaction type to the bankinstructions4trxn object and set all the fields to read only in postInit
 * 
 *    Rev 1.73   Feb 11 2004 18:45:14   popescu
 * PTS 10026899, reloaded currency set for Suppress pay type in Payment Instructions, loaded banking currency dynamically based on the file processor value if not empty
 * 
 *    Rev 1.72   Feb 11 2004 15:00:00   popescu
 * PTS 10026899, the substitution list for currency it is loaded from host if empty after trying to get it dynamically; also, dealt with the 0 value of the 'TransitNo' in bank instructions
 * 
 *    Rev 1.71.1.0   Feb 11 2004 14:55:56   popescu
 * PTS 10026899, the substitution list for currency it is loaded from host if empty after trying to get it dynamically; also, dealt with the 0 value of the 'TransitNo' in bank instructions
 * 
 *    Rev 1.71   Jan 30 2004 15:04:42   popescu
 * PTS 10026408, 
 * Removed hard coding of the file processor for banking, for broker/branch/slsrep, systematic,distribution,trade,shareholder.
 * Set the value of the file processor to NULL_STRING if there are no values from the back-end, 
 * For banking and distributions set the file processor NOT required if there are no values at the back-end
 * 
 *    Rev 1.70   Jan 28 2004 13:36:52   popescu
 * PET 987, fixed bank search for ids that are non-numerical
 * 
 *    Rev 1.69   Jan 27 2004 20:04:02   popescu
 * PTS 10026408, CITIBNK is not listed in Drop-down list for File Processor in setting up bank information, by Account - Income Distribution
 * 
 *    Rev 1.68   Dec 29 2003 18:35:28   popescu
 * PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
 * 
 *    Rev 1.67   Dec 22 2003 16:27:48   popescu
 * PTS 10025157, removed DistributionPayType field from BankInstructions object, now the value is being read directly from the parent (Distribution object)
 * 
 *    Rev 1.66   Dec 22 2003 11:41:30   popescu
 * PTS 10020696, Removed the temporary code which opens up the country field (when the Bank_Mstr record exists and country code is empty),  since the user can edit a Bank_Mstr record using the Institution/Transits Maintenace screen available from the Main menu
 * 
 *    Rev 1.65   Nov 19 2003 18:14:06   popescu
 * Field TransitNo should be set as required. Fixed a broken code while working on PET 809, FN 17
 * 
 *    Rev 1.64   Nov 19 2003 10:18:22   popescu
 * Synch-up with Rel 54, PTS 10024132
 * 
 *    Rev 1.63   Oct 30 2003 16:22:42   HERNANDO
 * Synch'd with 1.56.1.2; PTS 10022566.
 * 
 *    Rev 1.62   Oct 27 2003 19:48:32   popescu
 * CIBC PET809, FN 13, added Transit Search by name
 * 
 *    Rev 1.61   Oct 24 2003 17:19:10   popescu
 * CIBC PET 809, FN 13
 * 
 *    Rev 1.60   Oct 23 2003 17:51:02   FENGYONG
 * set defaultbankInsCode but didn't set it readonly if banktype = directrading
 * 
 *    Rev 1.59   Oct 19 2003 16:43:24   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.58   Oct 06 2003 12:42:58   popescu
 * Added banking support for DirectTrading enhancement
 * 
 *    Rev 1.57   Oct 04 2003 15:57:10   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.56   Sep 25 2003 17:19:44   popescu
 * PTS 10022248, the BAFF option for File processor has been made available for Client level banking, as well
 * 
 *    Rev 1.55   Sep 05 2003 09:51:24   popescu
 * Reversed to a hard-coded BAFF subst set, because datadictionary doesn't allow an empty code for a subst set item
 * 
 *    Rev 1.54   Aug 28 2003 17:28:22   popescu
 * PTS 10020269 Rel. 52.1,
 * validateTransitNo, failed for nMaxLength != -1, should be tested fro nMaxLength > 0
 * 
 *    Rev 1.53   Aug 17 2003 16:15:50   popescu
 * load BAFF subst list from Data dictionary for distributor banking, as well
 * 
 *    Rev 1.52   Aug 07 2003 18:39:06   popescu
 * make the account usage codes and payment for, visible to the GUI layer
 * 
 *    Rev 1.51   Aug 07 2003 10:17:44   FENGYONG
 * remove currency validation for fundbanking.
 * 
 *    Rev 1.50   Aug 02 2003 11:39:24   popescu
 * more banking
 * 
 *    Rev 1.49   Jul 31 2003 19:29:44   popescu
 * Since PayMethod is not a field of view 52, moved the initialization of PayMethod in the commonInit function, and we know for sure that this field is always set to Wire
 * 
 *    Rev 1.48   Jul 31 2003 17:09:34   popescu
 * few fixes and fund/class search
 * 
 *    Rev 1.47   Jul 31 2003 13:50:44   popescu
 * PTS 10020265, added more bank fields to the RRIF object so they can be copied over to the update view 129, in case new bank mstr needs to be created
 * 
 *    Rev 1.46   Jul 30 2003 11:34:50   popescu
 * Correspondent banking is enabled for Distribution banking, AcctUsage EFT, and moved some acct usage codes under the namespace AcctUseCode
 * 
 *    Rev 1.45   Jul 29 2003 17:07:02   popescu
 * Enabled correspondent banking for AcctUsage Commission and Trailer Fee
 * 
 *    Rev 1.44   Jul 29 2003 10:41:12   popescu
 * Fixed PTS 10002134
 * 
 *    Rev 1.43   Jul 25 2003 17:47:48   popescu
 * Externalize the AccUseCode namespace constant
 * 
 *    Rev 1.42   Jul 11 2003 13:46:50   popescu
 * fixes related to the confirmation screen showing up even if there are no changes for the payment instructions screen, added validation for the Currency if BAAF is selected as the file processor
 * 
 *    Rev 1.41   Jun 25 2003 12:18:50   FENGYONG
 * PET821_FN17.1.1
 * 
 *    Rev 1.40   Jun 18 2003 17:45:00   popescu
 * RRIF Banking Enhancement , business rules, bug fixes 
 * 
 *    Rev 1.39   Jun 10 2003 16:37:46   popescu
 * added the Settlement bank check for the effective date default
 * 
 *    Rev 1.38   Jun 10 2003 16:10:48   popescu
 * Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
 * 
 *    Rev 1.37   Jun 05 2003 10:42:12   popescu
 * business rules work for banking
 * 
 *    Rev 1.36   Jun 03 2003 20:58:38   popescu
 * Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
 * 
 *    Rev 1.35   Jun 01 2003 17:19:38   popescu
 * Removed obsolete code
 * 
 *    Rev 1.34   Jun 01 2003 17:07:36   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.33   May 31 2003 20:29:12   popescu
 * RRIF work part ||
 * 
 *    Rev 1.32   May 31 2003 11:54:40   popescu
 * RRIF bank work
 * 
 *    Rev 1.31   May 27 2003 13:14:02   popescu
 * RRIF Banking work
 * 
 *    Rev 1.30   May 23 2003 10:04:12   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.29   May 22 2003 14:11:56   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
// 
//    Rev 1.58   May 17 2003 11:58:30   WINNIE
// Expand bank account should be 35 characters rather than 36 characters.
// 
//    Rev 1.57   May 14 2003 11:35:24   WINNIE
// Expand bank account number for all Lux market from 16 characters to 36 charactes for SSB request PET 821
// 
//    Rev 1.56   Mar 21 2003 18:00:10   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.55   Feb 04 2003 17:19:54   KOVACSRO
// SWIFT enhancement - enable ACHProcessor for default redemption bank
// 
//    Rev 1.54   Oct 09 2002 23:54:04   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.53   Sep 09 2002 12:14:52   KOVACSRO
// Sync-up PTS 10009768 : removed corr bank edit check and some fixes
// 
//    Rev 1.52   Sep 04 2002 17:12:20   KOVACSRO
// Changed the way BankAcctName is assigned : for shareholder bank using the first account's name, for other banks using the account name
// 
//    Rev 1.51   Aug 29 2002 12:55:06   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.50   Jul 25 2002 16:22:02   KOVACSRO
// PTS 10009152 : PayMethod read-only.
// 
//    Rev 1.49   Jul 22 2002 13:24:12   KOVACSRO
// BankAcctName updateable.
// 
//    Rev 1.48   Jul 19 2002 12:14:42   KOVACSRO
// Added more logic in setDefaultBankIdType (if generic control DefaultBankUpd == N, we set the field as readonly)
// 
//    Rev 1.47   Jul 19 2002 10:18:14   KOVACSRO
// 1. Added clearCorrBankFields ();
// 2. PTS 10008759 : checking BankDetlName to decide if BankAcctName is updateable or readonly.
// 
//    Rev 1.46   Jul 05 2002 16:33:02   KOVACSRO
// payMethodRelatedChanges fix.
// 
//    Rev 1.45   Jul 05 2002 11:54:28   KOVACSRO
// Dynamically loading AcctUse subst. list.
// 
//    Rev 1.44   Jun 21 2002 17:42:34   KOVACSRO
// Added isCorrBankInfoAplicable
// 
//    Rev 1.43   Jun 20 2002 16:54:44   KOVACSRO
// A required field should be invalid by default if it's empty; it seems it is not, so let's force the validation.
// 
//    Rev 1.42   Jun 20 2002 13:34:38   KOVACSRO
// Added isMultiCurrency. Check multicurrency for Intern. Wire
// 
//    Rev 1.41   Jun 17 2002 17:28:08   KOVACSRO
// name change.
// 
//    Rev 1.40   Jun 16 2002 17:02:56   KOVACSRO
// Added setBankAcctName. Some data group changes.
// 
//    Rev 1.39   Jun 16 2002 12:53:56   HSUCHIN
// added some new functions and renamed setFieldFlag to setBankAcctTypeRequired
// 
//    Rev 1.38   Jun 15 2002 14:45:38   KOVACSRO
// Uncomment.
// 
//    Rev 1.37   Jun 15 2002 11:26:42   HSUCHIN
// Datagroup bug fix
// 
//    Rev 1.36   Jun 14 2002 17:36:20   KOVACSRO
// 1. new TradeBankInstructions class modifications.
// 2. Corr. bank fields read only for Broker, branch, rep, fund, client banking.
// 
//    Rev 1.35   Jun 14 2002 14:02:54   HSUCHIN
// added function setFieldsReadOnly
// 
//    Rev 1.34   Jun 13 2002 17:36:20   HSUCHIN
// added extra parameter to init
// 
//    Rev 1.33   Jun 13 2002 17:28:14   KOVACSRO
// Pending trade modifications.
// Some getBankInfo fixes.
// 
//    Rev 1.32   Jun 12 2002 18:21:34   KOVACSRO
// Loading ACHProcessor substitutions every time, not only for EFT redemption.
// 
//    Rev 1.31   Jun 12 2002 17:42:12   KOVACSRO
// Added a cross edit for International wire.
// Some other bug fixes
// 
//    Rev 1.30   Jun 11 2002 12:24:04   HSUCHIN
// added new init for settlement
// 
//    Rev 1.29   Jun 07 2002 17:43:06   KOVACSRO
// International Wire modifications. 
// 
//    Rev 1.28   03 Jun 2002 15:18:44   KOVACSRO
// Added PayMethod, other changes.
// 
//    Rev 1.27   22 May 2002 22:23:18   PURDYECH
// BFData Implementation
// 
//    Rev 1.26   Apr 24 2002 16:53:46   YINGBAOL
// fix getField ---PTS10007940
// 
//    Rev 1.25   17 Apr 2002 18:14:30   WINNIE
// call setFieldRequired
// 
//    Rev 1.24   Mar 26 2002 16:17:44   ZHANGCEL
// Bug fix for PTS ticket 10007599: added a overrited function getField ()
// 
//    Rev 1.23   Feb 25 2002 18:55:10   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.22   28 Dec 2001 11:21:16   KOVACSRO
// Added the ACHProcessor logic to default bank, too.
// 
//    Rev 1.21   Dec 05 2001 09:59:04   JANKAREN
// Make ACHProcessor not updatable when generic control is not turned on
// 
//    Rev 1.20   01 Oct 2001 13:24:44   WINNIE
// validate bankIdvalue and transit no based on the control 'bankValid1' (system feature PAC validation & AutoBankMstr)
// 
//    Rev 1.19   05 Aug 2001 14:36:28   YINGZ
// fix reset problem
// 
//    Rev 1.18   Aug 04 2001 22:01:54   YINGBAOL
// condition clearance
// 
//    Rev 1.17   Jul 29 2001 14:53:16   YINGBAOL
// modify condition version sync. up
// 
//    Rev 1.16   17 Jul 2001 10:12:14   YINGZ
// implementing ACHProcessor
// 
//    Rev 1.15   Jul 04 2001 11:34:10   ZHANGCEL
// Sync up with 1.9.1.15
// 
//    Rev 1.14   17 May 2001 14:33:46   HSUCHIN
// bug fix
// 
//    Rev 1.13   May 16 2001 17:30:46   WINNIE
// sync up with 1.9.1.11
// 
//    Rev 1.12   10 May 2001 12:15:24   KOVACSRO
// sync up.
// 
//    Rev 1.11   09 May 2001 14:29:50   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.9.1.9   May 04 2001 10:50:12   WINNIE
// fix bug for checking bankidnum numeric; make corresponding bank info optional
// 
//    Rev 1.9.1.8   02 May 2001 14:05:58   BUZILAMI
// saving  the bank fields from inside systematic
// 
//    Rev 1.9.1.7   Apr 28 2001 15:31:46   WINNIE
// bug fix : getfield with groupid
// 
//    Rev 1.9.1.6   Apr 27 2001 14:27:56   WINNIE
// Fix international wire for redemption
// 
//    Rev 1.9.1.5   Apr 17 2001 16:39:36   YINGZ
// fix distribution bank recid problem
// 
//    Rev 1.9.1.4   Apr 17 2001 13:20:46   WINNIE
// new method to disable fields that belongs to parent CBO
// 
//    Rev 1.9.1.3   Apr 16 2001 10:33:02   WINNIE
// Remove old validation for bank; copy new fields for bank between BankInstructions and the CBO;
// 
//    Rev 1.9.1.2   12 Apr 2001 15:27:42   BUZILAMI
// Trading Bank Changes
// 
//    Rev 1.9.1.1   10 Apr 2001 16:12:32   BUZILAMI
// distrib bank changes
// 
//    Rev 1.9.1.0   Apr 06 2001 17:04:32   WINNIE
// default banktype for systematic 
// 
//    Rev 1.9   04 Apr 2001 18:13:20   BUZILAMI
// fix
// 
//    Rev 1.8   Apr 04 2001 15:33:34   WINNIE
// Assign BankId from view 100
// 
//    Rev 1.7   Apr 04 2001 14:35:06   WINNIE
// set read only for corresponding bank; set read only for banking info if the bank already exists in the bank master; get bank info from the database if after user enter the bankvalue
// 
//    Rev 1.6   Apr 03 2001 20:08:50   WINNIE
// systematic default
// 
//    Rev 1.5   Apr 03 2001 14:29:24   WINNIE
// disable for corresponding bank related fields if not international wire
// 
//    Rev 1.4   Apr 02 2001 09:06:24   WINNIE
// Fix validation
// 
//    Rev 1.3   Apr 01 2001 16:18:14   WINNIE
// Assign Default Value; validate bank code format based on bank type;
// 
//    Rev 1.2   30 Mar 2001 17:09:24   BUZILAMI
// Systematic bank changes
// 
//    Rev 1.1   20 Mar 2001 16:00:08   BUZILAMI
// address changes
// 
//    Rev 1.0   Feb 21 2001 16:02:34   BUZILAMI
// Initial revision.
// 
 * 
*/
