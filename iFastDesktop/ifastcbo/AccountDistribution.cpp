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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountDistribution.cpp
// ^AUTHOR : Zijian Ying + Yingbao( for M2 )
// ^DATE   : 10/21/99
//
// ^CLASS    : AccountDistribution
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "dstcommonfunction.hpp"
#include "addresslist.hpp"
#include "accountdistribution.hpp"
#include "accountdistributionlist.hpp"
#include "accountmailinglist.hpp"
#include "bankinstructions.hpp"
#include "distributionbankinstructionslist.hpp"
#include "distributionbankinstructions.hpp"
#include "distributorbankinstructionslist.hpp"
#include "distributorrepository.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundlist.hpp"
#include "fundmasterlist.hpp"
#include "fundtolist.hpp"
#include "groupfundlist.hpp"
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"
#include "paytoentity.hpp"
#include "paytoentitylist.hpp"
#include "paymentinstructions.hpp"
#include "shareholder.hpp"
#include "ShareholderBankInstructionsList.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"
#include "tradepayinstructlist.hpp"
#include "tradepayinstruct.hpp"
#include <ifastdataimpl\dse_dstc0016_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0069_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0096_reqrepeat_record.hpp>
#include "dstcworksession.hpp"
#include "dynamicsublistholder.hpp"
#include "trade.hpp"

#include "FundClassDistribOptionsList.hpp"
#include "FundClassDistribOptions.hpp"

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_CHAR;
   extern const long ERR_ENTRY_BOTH_FIELDS;
   extern const long ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_INSTCODE_NOT_EXIST;
   extern const long ERR_FUND_NOT_EFFECTIVE;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_ACCT_FUND_CLASS_NOT_UNIQUE;
   extern const long ERR_PERCENTAGE_NOT_EQUAL_100;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long ERR_FIELD_REQUIRED_PLS_SELECT;
   extern const long ERR_BLANK_FUND;
   extern const long ERR_BLANK_CLASS;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_INSTCODE_TOO_BIG;
   extern const long ERR_TRANSITNO_TOO_BIG;
   extern const long ERR_BANKACCTNUM_TOO_BIG;
   extern const long ERR_CASH_NOT_ALLOWED;
   extern const long ERR_INVALID_PAY_TYPE;
   extern const long ERR_INVALID_PAYMANT_TYPE;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_THIS_FUND_HAS_NO_MGT_REBATE_FEE;
   extern const long ERR_ADDRESS_CODE_NOT_EFFECTIVE;
   extern const long ERR_ADDRESS_CODE_NOT_SETUP;
   extern const long ERR_FUND_CLASS_XFER_NOT_ALLOWED;
   extern const long ERR_FUNDTO_CLASSTO_DIFFERENT;
   extern const long ERR_NSCC_CURRENCY_INVALID;
   extern const long ERR_ONLY_NSCC_PAYTYPE_ALLOWED;
   extern const long ERR_ONLY_PAY_TO_ENTITY_PAYTYPE_ALLOWED;
   extern const long ERR_MISSING_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTIONS;
   extern const long WARN_NSCC_PAYMENT;
   extern const long ERR_INVALID_PAYMENTYPE_FOR_CURRENCY;
   extern const long ERR_FUND_CLASS_NOT_SUPPORTED_FOR_DISTRIB_TYPE;
   extern const long ERR_CASH_DISTRIB_NOT_ALLOWED_FOR_FROM_FUND_CLASS;
   extern const long ERR_REINVESTMENT_NOT_ALLOWED;
   extern const long ERR_REDIRECTING_NOT_ALLOWED;
   extern const long ERR_FUND_CLASS_XFER_NOT_ALLOWED;
   extern const long WARN_DISTRIBUTION_BULKING_BENEFICIAL;
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long WARN_DEFAULT_BANK_INFO_FOR_ACCT_DISTRIB_NOT_FOUND;
   extern const long ERR_WRONG_VERIFY_STATUS;
   extern const long ERR_ADDRESS_NOT_VERIFY;
   extern const long ERR_PAY_ENTITY_BANK_NOT_VERIFY;
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
   extern const long ERR_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION;
   extern const long WARN_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION;
}

namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION;      
}

namespace ifds
{  // Conditions used
   extern CLASS_IMPORT const BFTextFieldId DistributionTransType;
   extern CLASS_IMPORT const BFTextFieldId DummyDistributionPayType;
   extern CLASS_IMPORT const BFTextFieldId DivChqAddr;
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId Baycom;
   extern CLASS_IMPORT const BFTextFieldId ReinDistOnly;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankType;
   extern CLASS_IMPORT const BFTextFieldId AllowCashDistrib;
   extern CLASS_IMPORT const BFTextFieldId MFRDistributionPay;
   extern CLASS_IMPORT const BFTextFieldId MgtFeeRbtElig;
   extern CLASS_IMPORT const BFTextFieldId ReinvInOtherFundAllowed;
   extern CLASS_IMPORT const BFTextFieldId CashDivAvail;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId FromToFundClass;
   extern CLASS_IMPORT const BFTextFieldId PayTypeMethod;
   extern CLASS_IMPORT const BFTextFieldId ACHDividend;
   extern CLASS_IMPORT const BFTextFieldId NSCCCompliant;
   extern CLASS_IMPORT const BFTextFieldId NSCCCurrencyList;
   extern CLASS_IMPORT const BFTextFieldId NSCCDummyDistributionPayType;
   extern CLASS_IMPORT const BFTextFieldId NSCCMFRDistributionPay;
   extern CLASS_IMPORT const BFTextFieldId TransTypeDefault;
   extern CLASS_IMPORT const BFTextFieldId TradePayTypeDefault;
   extern CLASS_IMPORT const BFTextFieldId RedPayEntExist;
   extern CLASS_IMPORT const BFTextFieldId FromFundClass;
   extern CLASS_IMPORT const BFTextFieldId ToFundClass;
   extern CLASS_IMPORT const BFTextFieldId DistribChkAllowTfr; //to check if reinv distrib will need check of the allowable transfers.
   extern CLASS_IMPORT const BFTextFieldId AllFundsDistrib;
   extern CLASS_IMPORT const BFTextFieldId ConsolTransType;
   extern CLASS_IMPORT const BFTextFieldId PayTypeMethodCurrOpt;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
   extern CLASS_IMPORT const BFTextFieldId DelDistribAlloc;
   extern CLASS_IMPORT const BFTextFieldId DistribInstrAsRatioOpt;
   extern CLASS_IMPORT const BFDecimalFieldId LastIDRate;
   extern CLASS_IMPORT const BFDecimalFieldId TotalDistribRate;
   extern CLASS_IMPORT const BFTextFieldId DistribInputMethod;
   extern CLASS_IMPORT const BFDecimalFieldId TotalAllocPercent;
   extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;
   extern CLASS_IMPORT const BFTextFieldId TradeFileProcessorDefault;
}

namespace  
{
   const I_CHAR * const AccountDistribution_CODE_K = I_( "K0123456789" );

   const I_CHAR * const CASH                       = I_( "CASH" );
//DistributionPayType
   const I_CHAR * const EFT                        = I_( "E" );
   const I_CHAR * const INTERNATIONAL_WIRE         = I_( "I" );
   const I_CHAR * const MANUAL_CHEQUE              = I_( "M" );
   const I_CHAR * const SYSTEM_GENERATED_CHEQUE    = I_( "S" );

   const I_CHAR * const SUPPRESS                   = I_( "X" );  //suppress
   const I_CHAR * const EX_FER_IN_CODE             = I_( "XFIN" );   // trade trans type Exchange In 
   const I_CHAR * const EX_FER_OUT_CODE            = I_( "XFOUT" );  // trade trans type Exchange Out
// bankvalid1
   const I_CHAR * const BANK_NO_AUTOCREATION          = I_( "1" );  //no validation for bank info and no auto creation of Bank-Mstr
   const I_CHAR * const BANK_AUTOCREATION             = I_( "2" );  //no validation for bank info and view will create Bank-Mstr
   const I_CHAR * const BANK_VALID_AUTOCREATION       = I_( "3" );  //validate banking info by view and no auto creation of Bank-Mstr
   const I_CHAR * const BANK_NOT_VALID_AUTOCREATION   = I_( "4" );  //Banking info noy validate against Bank-Mstr and view  will automatically create Bank-Mstr
//banklayout
   const I_CHAR * const INTERNATIONAL_BANK            = I_( "1" );  //International Banking 
   const I_CHAR * const INTERNATIONAL_BANK_ADD        = I_( "2" );  //International Banking with addtional fields
   const I_CHAR * const NORTH_AMERICAN_BANK           = I_( "3" );  //North American banking 
   const I_CHAR * const NO_COMBINATION_BANK           = I_( "0" );  //combination does not exist among clients 

   const I_CHAR * const YES                           = I_( "Y" );
   const I_CHAR * const NO                            = I_( "N" );
   const I_CHAR * const MFR                           = I_( "MR" );
   const I_CHAR * const LOCK_TRANS_TYPE               = I_( "LOCK_TRANS_TYPE" );
   const I_CHAR * const VALIDATE_ADDR_CODE            = I_( "VALIDATE_ADDR_CODE" );
   const I_CHAR * const INCOME_DISTRIBUTION           = I_( "ID" );

   const I_CHAR * const USD                           = I_( "USD" );
   const I_CHAR * const USA                           = I_( "USA" );

   const I_CHAR * const FUND                          = I_( "FUND" );
   const I_CHAR * const CLASS                         = I_( "CLASS" );
   const I_CHAR * const TO_FUND                       = I_( "TO_FUND" );
   const I_CHAR * const TO_CLASS                      = I_( "TO_CLASS" );
   const I_CHAR * const WIRE                          = I_( "WIRE" );
   const I_CHAR * const CHQ                           = I_( "CHQ" );
   const I_CHAR * const BAFF                          = I_( "BAFF" );
   const I_CHAR * const NSCCPayType                   = I_("N");
   const I_CHAR * const NSCCPayTypeSet                = I_("N=NSCC;");
   const I_CHAR * const RegistrationAgentPayType      = I_("RA");
   
   const I_CHAR * const CASH_ACCT_LEVEL               = I_("CS");//can't we be consistent? Why do we need CASH and CS in the same time?
   const I_CHAR * const REINVEST                      = I_("RI");
   const I_CHAR * const REDIRECT                      = I_("RD");
   const I_CHAR * const FUND_CURRENCY                 = I_("01");
   const I_CHAR * const PREFERRED_CURRECNY            = I_("02");
   const I_CHAR * const DISTRIB_LEVEL                 = I_("02");
   const I_CHAR * const BANK_CATEGORY                 = I_("1");
   const I_CHAR * const DISTRIB_CATEGORY              = I_("2");
   const I_CHAR * const BROKER_LEVEL                  = I_("06");
   const I_CHAR * const BRANCH_LEVEL                  = I_("07");
   const I_CHAR * const SLSREP_LEVEL                  = I_("08");
   const I_CHAR * const UNVERIFIED                    = I_("02");
   const I_CHAR * const VERIFIED                      = I_("01");
   const I_CHAR * const TAX_TYPE_SA                   = I_("SA");
   const I_CHAR * const TAX_TYPE_OA                   = I_("OA");
   const I_CHAR * const TAX_TYPE_SRS                  = I_("SR");

}

namespace PAYMENT_FOR
{
   extern const I_CHAR * DISTRIBUTION;
}

namespace PAY_TO
{
   extern I_CHAR * const BROKER;
   extern I_CHAR * const BRANCH;
   extern I_CHAR * const SALESREP;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const DISTRIB_VERIFICATION;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const SYSTEM_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const EFT;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT_DIVIDEND;
}

extern BF_OBJ_TYPE OBJ_TYPE_DISTRIB_OPTIONS;

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   // Field DD Id,              State Flags,   Group Flags
   { ifds::FundCode,            BFCBO::NONE,        0 },          
   { ifds::ClassCode,           BFCBO::NONE,        0 },          
   { ifds::EffectiveDate,       BFCBO::NONE,        0 },          
   { ifds::FundToCode,          BFCBO::NONE,        0 },          
   { ifds::ClassToCode,         BFCBO::NONE,        0 },          
   { ifds::AllocPercent,        BFCBO::NONE,        0 },          
   { ifds::ProcessDate,         BFCBO::NONE,        0 },          
   { ifds::Username,            BFCBO::NONE,        0 },          
   { ifds::DistributionPayType, BFCBO::NONE,        0 },          
   { ifds::PayTypeDesc,         BFCBO::NONE,        0 },          
   { ifds::Currency,            BFCBO::NONE,        0 },          
   { ifds::CurrencyName,        BFCBO::NONE,        0 },          
   { ifds::BankIdValue,         BFCBO::NONE,        BANK_GROUP }, 
   { ifds::SwiftCode,           BFCBO::NONE,        BANK_GROUP }, 
   { ifds::RefNumber,           BFCBO::NONE,        BANK_GROUP }, 
   { ifds::TransitNo,           BFCBO::NONE,        BANK_GROUP }, 
   { ifds::BankAcctNum,         BFCBO::NONE,        BANK_GROUP }, 
   { ifds::BankAcctName,        BFCBO::NONE,        0 },          
   { ifds::PayReason1,          BFCBO::NONE,        0 },          
   { ifds::PayReason2,          BFCBO::NONE,        0 },          
   { ifds::BankAcctType,        BFCBO::NONE,        BANK_GROUP }, 
   { ifds::BankAcctTypeDesc,    BFCBO::NONE,        0 },          
   { ifds::InstName,            BFCBO::NONE,        BANK_GROUP }, 
   { ifds::BankDetlVer,         BFCBO::NONE,        0 },          
   { ifds::BankDetlRid,         BFCBO::NONE,        0 },          
   { ifds::DistribDetlVer,      BFCBO::NONE,        0 },          
   { ifds::DistribDetlRid,      BFCBO::NONE,        0 },          
   { ifds::ModUser,             BFCBO::NONE,        0 },          
   { ifds::ModDate,             BFCBO::NONE,        0 },          
   { ifds::TransType,           BFCBO::NONE,        0 },          
   { ifds::TransTypeDesc,       BFCBO::NOT_ON_HOST, 0 },          

   { ifds::FrFundNumber,        BFCBO::NONE,        0 },          
   { ifds::ToFundNumber,        BFCBO::NONE,        0 },          
   { ifds::BankIdValueCB,       BFCBO::NONE,        0 },          
   { ifds::BankIdType,          BFCBO::NONE,        0 },          
   { ifds::BankIdTypeCB,        BFCBO::NONE,        0 },          
   { ifds::FFC,                 BFCBO::NONE,        0 },          
   { ifds::FFC1,                BFCBO::NONE,        0 },          
   { ifds::ACHProcessor,        BFCBO::NONE,        0 },
   { ifds::PayMethod,           BFCBO::NONE,        0 },
   { ifds::BankContactCB,       BFCBO::NONE,        0 },          
   { ifds::BankCountryCB,       BFCBO::NONE,        0 },          
   { ifds::BankPostalCB,        BFCBO::NONE,        0 },          
   { ifds::BankAddrCB1,         BFCBO::NONE,        0 },          
   { ifds::BankAddrCB2,         BFCBO::NONE,        0 },          
   { ifds::BankAddrCB3,         BFCBO::NONE,        0 },          
   { ifds::BankAddrCB4,         BFCBO::NONE,        0 },          
   { ifds::BankAddrCB5,         BFCBO::NONE,        0 },          
   { ifds::BankAddr1,           BFCBO::NONE,        0 },          
   { ifds::BankAddr2,           BFCBO::NONE,        0 },          
   { ifds::BankAddr3,           BFCBO::NONE,        0 },          
   { ifds::BankAddr4,           BFCBO::NONE,        0 },          
   { ifds::BankAddr5,           BFCBO::NONE,        0 },          
   { ifds::BankContact,         BFCBO::NONE,        0 },          
   { ifds::BankPostal,          BFCBO::NONE,        0 },          
   { ifds::TransitNoCB,         BFCBO::NONE,        0 },          
   { ifds::InstNameCB,          BFCBO::NONE,        0 },          
   { ifds::BankId,              BFCBO::NONE,        0 },          
   { ifds::BankIdValueCB,       BFCBO::NONE,        0 },          
   { ifds::CorrespBankId,       BFCBO::NONE,        0 },          
   { ifds::AddrCode,            BFCBO::NONE,        0 },          
   { ifds::BankCountry,         BFCBO::NONE,        0 },          
   { ifds::FundClass,           BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::FromToFundClass,     BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::PayTypeMethod,       BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::FromFundClass,       BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::ToFundClass,         BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::ToSoftCapCheck,      BFCBO::IMMEDIATE_VALIDATION,   0 }, 
   { ifds::AllFundsDistrib,     BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::AcctDistribOpt,             BFCBO::NONE,            0 },
   { ifds::AcctDistribCurrencyOption,  BFCBO::NONE,            0 },
   { ifds::PayTypeMethodCurrOpt, BFCBO::IMMEDIATE_VALIDATION,  0 },
   { ifds::VerifyStat,          BFCBO::NONE,        0 },
   { ifds::DistribGBCD,         BFCBO::NONE,        0 },
   { ifds::DelDistribAlloc,     BFCBO::NONE,        0 },
   { ifds::DistribRate,			BFCBO::NONE,        0 },
   { ifds::TotalDistribRate,	BFCBO::CALCULATED_FIELD,        0 },
   { ifds::LastIDRate,			BFCBO::NONE,        0 },
   { ifds::DistribInputMethod,	BFCBO::NONE,        0 },
   { ifds::TotalAllocPercent,	BFCBO::CALCULATED_FIELD,        0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountDistribution" );
}

//******************************************************************************
AccountDistribution::AccountDistribution( BFAbstractCBO &parent ) :
MFCanBFCbo( parent ),
_pSplitList( 0 ),
strCurrencySubstList( NULL_STRING ),
_pMFAccount(NULL),
_currentBusinessDate (NULL_STRING),
_dstrVerifyStatus (NULL_STRING),
_bIsDirty (false),
_bCanVerify (false),
_bVerificationEnabled (false),
_bInit (true)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
   addCrossEdit(ifds::FundClass, ifds::FrFundNumber);
   addCrossEdit(ifds::FromToFundClass, ifds::FundToCode);
   addCrossEdit(ifds::FromToFundClass, ifds::ClassToCode);   
   //addCrossEdit(ifds::FromToFundClass, ifds::ToFundNumber);

   addCrossEdit(ifds::FromFundClass, ifds::FundCode);
   addCrossEdit(ifds::FromFundClass, ifds::ClassCode);

   addCrossEdit(ifds::ToFundClass, ifds::FundToCode);
   addCrossEdit(ifds::ToFundClass, ifds::ClassToCode);
   addCrossEdit(ifds::ToFundClass, ifds::FundCode);
   addCrossEdit(ifds::ToFundClass, ifds::ClassCode);

   addCrossEdit(ifds::PayTypeMethod, ifds::PayMethod);   
   addCrossEdit(ifds::PayTypeMethod, ifds::DistributionPayType);  

   addCrossEdit(ifds::PayTypeMethodCurrOpt, ifds::PayMethod);   
   addCrossEdit(ifds::PayTypeMethodCurrOpt, ifds::DistributionPayType);
   addCrossEdit(ifds::PayTypeMethodCurrOpt, ifds::AcctDistribCurrencyOption);  

   
   addCrossEdit(ifds::ToSoftCapCheck, ifds::FundToCode);
   addCrossEdit(ifds::ToSoftCapCheck, ifds::ClassToCode);
   addCrossEdit(ifds::ToSoftCapCheck, ifds::EffectiveDate);

   getWorkSession ().getOption ( ifds::CurrBusDate, 
                                 _currentBusinessDate, 
                                 BF::HOST, 
                                 false);
}

//******************************************************************************

AccountDistribution::~AccountDistribution()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _distributionData )
   {
      //delete _distributionData;
      _distributionData = NULL;
   }
}

//******************************************************************************

SEVERITY AccountDistribution::init( const BFDataGroupId& idDataGroup, 
                                    const DString& dstrAccountNum, 
                                    const DString& dstrShareholderNum,
                                    DISTRIBUTION_LEVEL level, 
                                    BFData *data, 
                                    BFData *distributionData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::DistributionTransType );

   BFProperties * pProperties = getFieldProperties(ifds::Currency, idDataGroup);
   pProperties->getAllSubstituteValues(strCurrencySubstList);

   _dstrAccountNum = dstrAccountNum;
   _dstrShareholderNum = dstrShareholderNum;
   _level = level;
   _bIsDirty = false;

   _pMFAccount = NULL;
   Shareholder *pShareholder;   
   getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, _pMFAccount );
   getWorkSession().getShareholder( idDataGroup, dstrShareholderNum, pShareholder );
   pShareholder->getAddressList ( _pAddressList, idDataGroup );

   // default value of DelDistribAlloc is 'N'
   setFieldNoValidate( ifds::DelDistribAlloc,I_("N"), idDataGroup,false,true,false,false); 

   if( data )
   {
      DString dstrTransType, dstrFundCode, dstrClassCode;
      dstrTransType = data->getElementValue ( ifds::TransType );
      dstrTransType.strip();
      dstrFundCode = data->getElementValue ( ifds::FundCode );
      dstrFundCode.strip();
      dstrClassCode = data->getElementValue ( ifds::ClassCode );
      dstrClassCode.strip();
      setPayTypeSubstSet(idDataGroup, dstrTransType, dstrFundCode, dstrClassCode);
   }

   DString dstrFundCode, dstrClassCode, dstrFrFundNumber, dstrTransType; 
   if( _level == ACCOUNT_LEVEL )
   {
      setPayTypeSubstSet(idDataGroup);
      DString dstrEffectiveDate;	  
      //DString dstrFundCode, dstrClassCode, dstrFrFundNumber; 
      if( data )
      {
         dstrFundCode = data->getElementValue( ifds::FundCode );
         dstrFundCode.strip().upperCase();

         dstrClassCode = data->getElementValue( ifds::ClassCode );
         dstrClassCode.strip().upperCase();

         dstrEffectiveDate = data->getElementValue( ifds::EffectiveDate );
         dstrEffectiveDate.strip();

         dstrTransType = data->getElementValue ( ifds::TransType );
         dstrTransType.strip();
         setFieldReadOnly( ifds::EffectiveDate, idDataGroup, true );
         setFieldReadOnly( ifds::TransType, idDataGroup, true );

         const DSTCSecurity *pSecurity = 
            dynamic_cast<const DSTCSecurity *>(getWorkSession ().getSecurity(DSTCHost::getPrimaryHost()));
         DString dstrCurrentUser = pSecurity->getUserId();
         dstrCurrentUser.strip().upperCase();

         DString strVerifyStat, strDistribGBCD,strModUser,strUserName;
         strVerifyStat = data->getElementValue ( ifds::VerifyStat );
         strDistribGBCD = data->getElementValue ( ifds::DistribGBCD );
         strModUser = data->getElementValue ( ifds::ModUser );
         strUserName = data->getElementValue ( ifds::Username );
         strVerifyStat.strip().upperCase();
         strDistribGBCD.strip().upperCase();
         strModUser.strip().upperCase();
         strUserName.strip().upperCase();

         setFieldNoValidate( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
         setFieldNoValidate( ifds::DistribGBCD, strDistribGBCD, idDataGroup, false );
         setFieldNoValidate( ifds::ModUser, strModUser, idDataGroup, false );
         setFieldNoValidate( ifds::Username, strUserName, idDataGroup, false );
      }
      else
      {
         bool bVerificationEnabled = false;
         getWorkSession().getDateInHostFormat(dstrEffectiveDate, 
                                              DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY,
                                              idDataGroup);
         getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                                   DISTRIB_CATEGORY, 
                                                   DISTRIB_LEVEL, 
                                                   bVerificationEnabled);

         if ( isNew() && bVerificationEnabled )
         {
            setFieldNoValidate( ifds::VerifyStat, UNVERIFIED, idDataGroup, false );
            setFieldNoValidate( ifds::DistribGBCD, I_("Y"), idDataGroup, false );
         }
      }

      getWorkSession().GetFundNumber(  dstrFundCode, dstrClassCode, dstrFrFundNumber );
      setFieldNoValidate( ifds::FrFundNumber, dstrFrFundNumber, BF::HOST,true, true, false, false);

      setFieldNoValidate( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false, true, false, false);
//		setFieldNoValidate( DBR::TransType, I_("ID"), idDataGroup, false );      
      _distributionData = distributionData; 
      _pSplitList = new AccountDistributionList( *this );

      _pSplitList->init( false,
                         idDataGroup, 
                         dstrAccountNum,
                         dstrShareholderNum, 
                         FUND_CLASS_LEVEL, 
                         distributionData, 
                         dstrFundCode, 
                         dstrClassCode, 
                         dstrEffectiveDate,
                         dstrTransType);

      setObject( _pSplitList, I_( "SplitList" ), OBJ_ACTIVITY_NONE, idDataGroup );

      if((dstrTransType == I_( "ID" ) || dstrTransType == I_("MR"))  &&
          dstrFundCode  == NULL_STRING && 
          dstrClassCode == NULL_STRING )
      {
         //all funds distribution
         DString strAcctDistribOpt = data->getElementValue( ifds::AcctDistribOpt );
         DString strAcctDistribCurrOpt = data->getElementValue( ifds::AcctDistribCurrencyOption);
         acctLvlDistrInit( strAcctDistribOpt.strip(), strAcctDistribCurrOpt.strip(), idDataGroup );

         BFObjIter iter( *_pSplitList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         dynamic_cast<AccountDistribution*>(iter.getObject( ))->acctLvlDistrInit( strAcctDistribOpt, strAcctDistribCurrOpt, idDataGroup );

         initVerifyStatus ( idDataGroup, isNew() );
         dynamic_cast<AccountDistribution*>(iter.getObject( ))->initVerifyStatus ( idDataGroup, isNew() );

         //setNonDummyFlag();
         if ( _bVerificationEnabled )
         {
            SetReadOnlyFields(idDataGroup);
            dynamic_cast<AccountDistribution*>(iter.getObject( ))->SetReadOnlyFields( idDataGroup );
         }
      }
      else
      {
         setFieldReadOnly( ifds::AcctDistribOpt, BF::HOST, true );
         setFieldReadOnly( ifds::AcctDistribCurrencyOption, BF::HOST, true );

         initVerifyStatus ( idDataGroup, isNew() );

         if ( _bVerificationEnabled )
         {
            SetReadOnlyFields(idDataGroup);
            BFObjIter iter( *_pSplitList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

            bool bFromDistribGood = false;
            while( !iter.end() )
            {
               DString strToDistribGBCD;
               AccountDistribution* pBFCBO = dynamic_cast<AccountDistribution*>(iter.getObject( ));
               pBFCBO->initVerifyStatus ( idDataGroup, isNew() );
               pBFCBO->SetReadOnlyFields(idDataGroup);
               pBFCBO->getField( ifds::DistribGBCD, strToDistribGBCD, idDataGroup, false );
               strToDistribGBCD.strip().upperCase();
               bFromDistribGood |= strToDistribGBCD == I_("Y");
               ++iter;
            }

            // if there are allocation distrib but not all of allocation record is 'bad'
            // set parent of allocation distrib good-bad status to be 'good'
            AccountDistribution* pBFCBO = 
               dynamic_cast<AccountDistribution*>(getParent()->getParent());

            if ( isNew() )
            {
               setFieldNoValidate( ifds::DistribGBCD, I_("Y"), idDataGroup, false );
               if( pBFCBO )
               {
                  pBFCBO->setFieldNoValidate( ifds::DistribGBCD, I_("Y"), 
                                              idDataGroup, false,true,false,false );
               }
            }
            else
            {
               if( pBFCBO )
               {
                  if ( bFromDistribGood )
                  {
                     pBFCBO->setFieldNoValidate( ifds::DistribGBCD, I_("Y"), idDataGroup, false,true,false,false );
                  }
                  else
                  {
                     // all allocation is unverified-bad -> parent record would be unverified-bad as well.
                     pBFCBO->setFieldNoValidate( ifds::DistribGBCD, I_("N"), idDataGroup,false,true,false,false);
                  }
               }
            }
            setFieldValid( ifds::DistribGBCD, idDataGroup, true );
         }
      }

   }

   else if( _level == FUND_CLASS_LEVEL )
   {
      if( data )
      {
         DString dstrFundToCode, dstrClassToCode, dstrToFundNumber;

         dstrFundToCode = data->getElementValue( ifds::FundToCode );
         dstrFundToCode.strip().upperCase();

         if ( dstrFundToCode == I_("CASH") )
         {
            dstrFundCode = data->getElementValue( ifds::FundCode );
            dstrFundCode.strip().upperCase();
            dstrClassCode = data->getElementValue( ifds::ClassCode );
            dstrClassCode.strip().upperCase();
            if ( ( dstrFundCode != NULL_STRING ) && ( dstrClassCode != NULL_STRING ) )
            {
               DString dstrCurrency, dstrMultiCurrency;
               if ( WARNING >= getMgmtCo().getMgmtCoOptions( pMgmtCoOptions ) )
                  pMgmtCoOptions->getField( ifds::MultiCurrency, dstrMultiCurrency, BF::HOST );
               if ( dstrMultiCurrency == NO && _pFundDetailList )
               {
                  _pFundDetailList->getField( dstrFundCode, dstrClassCode,
                               ifds::Currency, dstrCurrency, 
                               idDataGroup, false
                             ); 
                  //GetFundCurrency ( dstrCurrency, idDataGroup );
                  setFieldNoValidate ( ifds::Currency, dstrCurrency, idDataGroup, false, true, false, false );
                  setFieldReadOnly ( ifds::Currency, idDataGroup, true );
               }
            }
         }

         dstrClassToCode = data->getElementValue( ifds::ClassToCode );
         dstrClassToCode.strip().upperCase();

         getWorkSession().GetFundNumber( dstrFundToCode, dstrClassToCode, dstrToFundNumber );

         setFieldNoValidate( ifds::ToFundNumber, dstrToFundNumber, BF::HOST,true, true, false, false);
         setFieldReadOnly( ifds::BankAcctName, idDataGroup, true );
         setFieldReadOnly( ifds::BankAcctNum, idDataGroup, true );
         setFieldReadOnly( ifds::BankIdValue, idDataGroup, true );

         //_bInit = false;
      }
      else
      {
         DString strEffectiveDate;

         getField(ifds::EffectiveDate, strEffectiveDate, idDataGroup);
         strEffectiveDate.stripAll();
         if (strEffectiveDate == NULL_STRING)
         {
            //get the parent's value of the effective date
            if (getParent()->getParent())
            {
               getParent()->getParent()->getField(ifds::EffectiveDate, 
                  strEffectiveDate, idDataGroup);
               setFieldNoValidate(ifds::EffectiveDate, 
                  strEffectiveDate, idDataGroup, false);
            }
         }

         // For new record of distrib allocation, it should be always 'Good'
         if ( isNew() && getParent()->getParent() && _bVerificationEnabled )
         {
            setFieldNoValidate (ifds::DistribGBCD, I_("Y"), idDataGroup, false);
         }
      }
   }

   DString dstrACHDividend;
   getWorkSession().getOption(ifds::ACHDividend, dstrACHDividend, BF::HOST, false);

   dstrACHDividend.strip().upperCase();
   //PayMethod default WIRE in DD
   setFieldReadOnly( ifds::PayMethod, idDataGroup, dstrACHDividend != YES );

   SetRequiredField( idDataGroup );

   if (data)
   {
      attachDataObject( *data, false, true );
      payMethodRelatedChanges(idDataGroup);
   }

   if (WARNING >= getMgmtCo().getMgmtCoOptions (pMgmtCoOptions))
   {
      pMgmtCoOptions->getField (ifds::BankingFormat, dstrBankingFormat, BF::HOST);
   }

   setValidFlag( ifds::PayTypeMethodCurrOpt, idDataGroup, false );
   setValidFlag( ifds::PayTypeMethod, idDataGroup, false );

   // This is to prevent validation of records coming back from base.   It is assumed
   // that all distributions returned are valid.  
   // REMOVE this line once BFBase has been changed to set all Fields to be valid in Release 47
   //setAllFieldsValid ( idDataGroup );
   _bInit = false;

   DString dstrAccountTaxType;
   _pMFAccount->getField(ifds::TaxType, dstrAccountTaxType, idDataGroup, false);
   if(dstrAccountTaxType == TAX_TYPE_OA || dstrAccountTaxType == TAX_TYPE_SA || 
      dstrAccountTaxType == TAX_TYPE_SRS)
   {
      if( _level == ACCOUNT_LEVEL )
      {
         if(isAllFundsMode( idDataGroup ))
         {
            setFieldNoValidate( ifds::AcctDistribCurrencyOption, PREFERRED_CURRECNY, idDataGroup, false,true,true);
            setFieldReadOnly ( ifds::AcctDistribCurrencyOption, idDataGroup, true );
         }
      }
      else if( _level == FUND_CLASS_LEVEL )
      {
         DString dstrFundToCode;
         getField(ifds::FundToCode, dstrFundToCode, idDataGroup, false);
         if(dstrFundToCode == CASH)
         {
            BFProperties* pSettleCurrencyProps = _pMFAccount->getFieldProperties(ifds::SettleCurrency, idDataGroup );
            DString dstrCurrencyAllSubst;
            pSettleCurrencyProps->getAllSubstituteValues(dstrCurrencyAllSubst);
            setFieldAllSubstituteValues(ifds::Currency, idDataGroup, dstrCurrencyAllSubst);
         }
      }
   }

   setFieldNoValidate( ifds::DistribInputMethod,I_("0"), idDataGroup,false,true,false,false); 
   if (data)
	   setLastIDRate(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
} 
//*****************************************************************************   
void  AccountDistribution::SetListPointer(FundDetailList* pFundDetailList, FundMasterList* pFundMasterList)
{
   _pFundDetailList = pFundDetailList; 
   _pFundMasterList = pFundMasterList;
}

//******************************************************************************

bool AccountDistribution::IsRightPayType(const DString& strValue, const BFDataGroupId& idDataGroup) const
{
   bool retVal = false;
   if(strValue == EFT || strValue == SYSTEM_GENERATED_CHEQUE || strValue == MANUAL_CHEQUE || 
      strValue == INTERNATIONAL_WIRE || strValue == SUPPRESS ||strValue == NSCCPayType || strValue == I_("P"))
      retVal = true; //redirect to pay to entity...
   else if(strValue == RegistrationAgentPayType)
   {
      if(_pMFAccount)
      {
         DString dstrAccountTaxType;
         _pMFAccount->getField(ifds::TaxType, dstrAccountTaxType, idDataGroup, false);

         if(dstrAccountTaxType == TAX_TYPE_OA || dstrAccountTaxType == TAX_TYPE_SA || dstrAccountTaxType == TAX_TYPE_SRS)
            retVal = true;

      }
   }
   return retVal;
}

//******************************************************************************

bool AccountDistribution::IsFundToCodeCash( const BFDataGroupId& idDataGroup ) const
{
   DString  strValue;
   getField( ifds::FundToCode, strValue, idDataGroup );
   strValue.strip().upperCase();
   return(strValue == CASH);
}

//******************************************************************************

bool AccountDistribution::IsRightFundClassTo( const DString& dstrFundCode, 
                                              const DString& dstrClassCode, const BFDataGroupId& idDataGroup ) const
{
   if( IsFundToCodeCash( idDataGroup ) )// if cash should be blank
      return(dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING);
   else//go itering view 56  
      return(IsValidFundClass( dstrFundCode, dstrClassCode, idDataGroup ));
}

//******************************************************************************

bool AccountDistribution::IsValidFund( const DString& dstrFundCode, 
                                       const BFDataGroupId& idDataGroup ) const
{
   return(_pFundMasterList->IsFundExist(dstrFundCode,idDataGroup));
}

//******************************************************************************

bool AccountDistribution::IsValidFundClass( const DString& dstrFundCode, 
                                            const DString& dstrClassCode, const BFDataGroupId& idDataGroup ) const
{
   return(_pFundDetailList->IsFundClassExist( dstrFundCode, dstrClassCode, idDataGroup ));
}

//******************************************************************************

SEVERITY AccountDistribution::doValidateField( const BFFieldId& idField, 
                                               const DString& dstrValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( _level == FUND_CLASS_LEVEL ) // fund level
   {
      if( idField == ifds::DistributionPayType )
      {
         DString dstrFundToCode;
         getField( ifds::FundToCode, dstrFundToCode, idDataGroup );
         if( dstrFundToCode.strip().upperCase() == CASH )
            validatePayType( dstrValue, idDataGroup );
      }
      else if ( idField == ifds::FromToFundClass )
      {
         canTradeFundClass( idField, idDataGroup );
      }

      if(isBankingAllowed( idDataGroup ) )
      {
         if( idField == ifds::BankIdValue )
            ValidateBankIdValue( dstrValue, idDataGroup );
         else if( idField == ifds::TransitNo )
            ValidateTransNo( dstrValue, idDataGroup );
         else if( idField == ifds::BankAcctNum )
            ValidateBankAcctNum( dstrValue, idDataGroup );
         else if( idField == ifds::BankAcctType )
            ValidateBankAcctType( dstrValue);
      }
//      else - validation on the fields below should occur regardless whether banking is allowed or not
      {
         if( idField == ifds::Currency )
         {
            ValidateCurrency( dstrValue, idDataGroup );
         }

         else if( idField == ifds::FundToCode )
         {
            ValidateFundCode( idField, dstrValue, idDataGroup );
         }
         else if( idField == ifds::ClassToCode )
         {
            ValidateClassCode( idField, dstrValue, idDataGroup );
         }

         else if( idField == ifds::ToFundNumber )
         {
            DString str; 
            getField(idField, str, idDataGroup, false );

            if( str.strip().upperCase() != I_( "N/A" ) )
            {
               DString dstrFundCode,dstrClassCode;
               if( !getWorkSession().GetFundClassCode( dstrValue,dstrFundCode,dstrClassCode) )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );
               }
            }
            else
            {
               setUpdatedFlag ( ifds::ToFundNumber, idDataGroup, false );
            }
         }
         else if( idField == ifds::ToFundClass )
            validateToFundClass( idDataGroup );
         else if (idField == ifds::ToSoftCapCheck)
         {
             validateToSoftCapCheck(idDataGroup);
         }
         else if( idField == ifds::AllocPercent )
            ValidateDistributePercentage( dstrValue, idDataGroup );
         else if( idField == ifds::PayTypeMethodCurrOpt )
         {
            validateAcctDistribPayType( idDataGroup );
         }
      }

      if( DistributionPayTypeIsSysCheck ( idDataGroup ) && idField == ifds::AddrCode )
      {
         DString dstrTransType;
         getField ( ifds::TransType, dstrTransType, idDataGroup );
         if( dstrTransType == MFR )
         {
            BFObjIter iter( *_pAddressList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
            iter.setDataFilter( asString (ifds::AddrCode.getId() ) + I_("=") + dstrValue );
            if( iter.end() )
            {
               DString error = I_( "" );
               addIDITagValue( error, I_("CODE"), dstrValue );
               ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_SETUP, error );
            }
            else
            {
               DString dstrAddrEffectiveDate, dstrAddrStopDate, dstrEffectiveDate;
               iter.getObject()->getField ( ifds::EffectiveDate, dstrAddrEffectiveDate, idDataGroup );
               iter.getObject()->getField ( ifds::StopDate, dstrAddrStopDate, idDataGroup );
               getParent()->getParent()->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );

               if( ( DSTCommonFunctions::CompareDates ( dstrAddrEffectiveDate, dstrEffectiveDate ) == 
                     DSTCommonFunctions::EQUAL ) || 
                   ( DSTCommonFunctions::CompareDates ( dstrAddrStopDate, dstrEffectiveDate ) == 
                     DSTCommonFunctions::EQUAL ) )
                  return(GETCURRENTHIGHESTSEVERITY());

               if( !( (DSTCommonFunctions::CompareDates ( dstrAddrEffectiveDate, dstrEffectiveDate ) 
                       == DSTCommonFunctions::FIRST_EARLIER ) &&
                      (DSTCommonFunctions::CompareDates ( dstrEffectiveDate, dstrAddrStopDate ) 
                       == DSTCommonFunctions::FIRST_EARLIER ) ) )
               {
                  DString error = I_( "" );
                  addIDITagValue( error, I_("CODE"), dstrValue );
                  ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_EFFECTIVE, error );
               }
            }
         }
      }
   }
   else  // account Level
   {
      if( idField == ifds::FundCode )
         ValidateFundCode( idField, dstrValue, idDataGroup );
      else if( idField == ifds::ClassCode )
         ValidateClassCode( idField, dstrValue, idDataGroup );

      else if( idField == ifds::FrFundNumber )
      {
         if( !isAllFundsMode( idDataGroup ) )
         {
            DString dstrFundCode,dstrClassCode;
            if( !getWorkSession().GetFundClassCode( dstrValue,dstrFundCode,dstrClassCode) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );
            }
         }
      }
      else if( idField == ifds::FromFundClass )
      {
         validateFromFundClass( idDataGroup );
      }
      else if( idField == ifds::AcctDistribOpt  )
      {
         validateAcctDistribOpt( dstrValue, idDataGroup );
      }
      else if( idField == ifds::AcctDistribCurrencyOption )
      {
         validateAcctDistribCurrencyOpt( dstrValue, idDataGroup );
      }
      else if (idField == ifds::VerifyStat && _bIsDirty && _bVerificationEnabled)
      {
         if ( dstrValue == UNVERIFIED )
         {
            ADDCONDITIONFROMFILE (CND::ERR_WRONG_VERIFY_STATUS);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountDistribution::validatePayType ( const DString &strValue, 
                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validatePayType" ));

   DString cashDistRule,
     validDistPayType;

   getWorkSession ().getOption (ifds::CashDistribRule, cashDistRule, BF::HOST, false);
   getWorkSession ().getOption (ifds::ValidDistributionPayType, validDistPayType, BF::HOST, false);

   if (cashDistRule.strip().upperCase() == YES)
   {
      if (!(DSTCommonFunctions::codeInList (strValue, validDistPayType)))
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_PAY_TYPE);
      }
   }
   else if (!IsRightPayType (strValue, idDataGroup))
   {
      ADDCONDITIONFROMFILE (CND:: ERR_INVALID_PAYMANT_TYPE);
   }

   if (strValue == I_("N")) // NSCC is selected payment type and must have us dollars as currency
   {
      DString currency;
      getField (ifds::Currency, currency, idDataGroup, false);
      currency.strip();

      if (currency != USD  && currency != USA)
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_PAYMENTYPE_FOR_CURRENCY);
   }

   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      if (isNSCCCompliant (idDataGroup) && strValue != I_("N"))
      {
         ADDCONDITIONFROMFILE (CND::WARN_NSCC_PAYMENT);
      }
      else if (hasPayInstructionsForDistribution (idDataGroup) && strValue != I_("P"))
      {
         ADDCONDITIONFROMFILE (CND::ERR_ONLY_PAY_TO_ENTITY_PAYTYPE_ALLOWED);
      }
      else if (!hasPayInstructionsForDistribution (idDataGroup) && strValue == I_("P"))
      {
         ADDCONDITIONFROMFILE (CND::ERR_MISSING_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTIONS);
      }
   }
   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      if (strValue == I_("P")) //redirect to pay entity
      {
         TradePayInstructList *pTradePayInstructList = NULL;

         if ( getPayInstructList (pTradePayInstructList, idDataGroup) <= WARNING &&
              pTradePayInstructList)
         {
            pTradePayInstructList->otherBrokerPaymentForExist (idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AccountDistribution::validateCash(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateCash" ) );

   DString dstrAllowCashDistribution, strAcctDistribOpt;
   getWorkSession().getOption( ifds::AllowCashDistrib, dstrAllowCashDistribution, idDataGroup, false );
   getField( ifds::AcctDistribOpt, strAcctDistribOpt, idDataGroup );

   if( dstrAllowCashDistribution.strip().upperCase() != YES ||
      (isAllFundsMode(idDataGroup) && strAcctDistribOpt.strip() == REDIRECT) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_CASH_NOT_ALLOWED );
      return(GETCURRENTHIGHESTSEVERITY());
   }

//   DString strReinDistOnly;
//   MFAccount *mfAccount = NULL;   
//   SEVERITY sevRtn = getWorkSession().getMFAccount( idDataGroup, _dstrAccountNum, mfAccount );

   DString dstrTransType, dstrFundCode, dstrClassCode ;
   getField ( ifds::TransType, dstrTransType, idDataGroup, false );
   getField ( ifds::FundCode, dstrFundCode, idDataGroup, false );
   getField ( ifds::ClassCode, dstrClassCode, idDataGroup, false );

   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   // Incident work order#24072 -- following logic should be applicable for the MFR as well
   if( ( /*sevRtn <= WARNING &&*/ _pMFAccount != NULL )) // && ( dstrTransType.strip().upperCase() != MFR ) )
   {
      TaxTypeRule *pTaxTypeRule = NULL;

      if ( _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
      {
         DString strReinDistOnly;
         pTaxTypeRule->getField( ifds::ReinDistOnly , strReinDistOnly, idDataGroup );
         if( strReinDistOnly == YES )
         {
            ADDCONDITIONFROMFILE( CND::ERR_CASH_NOT_ALLOWED );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AccountDistribution::ValidateBankIdValue(const DString& dstrBankIdValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateBankIdValue" ) );

   DString str(dstrBankIdValue);   
   str.strip().strip('0');

   // validation of the format is done by BankInstr
   if( str == NULL_STRING )
   {
      DString FieldName;
//CP		DP::getFieldNameFromId( DBR::BankIdValue, FieldName );
      //     PropertyRepository::getInstance()->getFieldNameFromId( DBR::BankIdValue, FieldName );
	  DString strAcctDistribCurrOpt;
	  getField( ifds::AcctDistribCurrencyOption, strAcctDistribCurrOpt, idDataGroup, false );
	  if( !isAllFundsMode( idDataGroup ) || strAcctDistribCurrOpt.strip() != FUND_CURRENCY ) 
	  {
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
	  }
   }
}

//******************************************************************************

void AccountDistribution::ValidateTransNo(const DString& TransNo, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateTransNo" ) );

   DString tmp(TransNo), FieldName, dstrBankIDType;
   tmp.strip().strip('0');

   getField(ifds::BankIdType, dstrBankIDType, idDataGroup, false);

   // validation of the format is done by BankInstr
   if( (dstrBankIDType == I_( "03" ) ||  dstrBankIDType == I_( "06" )) && tmp == NULL_STRING )
   {
//CP		DP::getFieldNameFromId( DBR::TransitNo, FieldName );
//      PropertyRepository::getInstance()->getFieldNameFromId( DBR::TransitNo, FieldName );
      ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
   }

}

//******************************************************************************

void AccountDistribution::ValidateBankAcctNum(const DString& BankAcctNum, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateBankAcctNum" ) );

   // validation of size should be done by the BankInstr.cpp
   if( BankAcctNum == NULL_STRING )
   {
      DString FieldName;
      // PropertyRepository::getInstance()->getFieldNameFromId( DBR::BankAcctNum, FieldName );
//CP		DP::getFieldNameFromId( DBR::BankAcctNum, FieldName );
	  DString strAcctDistribCurrOpt;
	  getField( ifds::AcctDistribCurrencyOption, strAcctDistribCurrOpt, idDataGroup, false );
	  if( !isAllFundsMode( idDataGroup ) || strAcctDistribCurrOpt.strip() != FUND_CURRENCY ) 
	  {
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
	  }
   }

   /***
   else
   {
      DString strBankAcctNumMax;
      DString strBankAcctNum(BankAcctNum);

      if ( pMgmtCoOptions )
      {
         pMgmtCoOptions->getField( DBR::BankAcctNumMax, strBankAcctNumMax, BF::HOST );
         int bankAcctNumMax = convertToULong( strBankAcctNumMax );

         if( YES == dstrBankingFormat && bankAcctNumMax > 0 && 
            strBankAcctNum.strip().length() > bankAcctNumMax )

            ADDCONDITIONFROMFILE( CND::ERR_BANKACCTNUM_TOO_BIG );
      }
   } ****/
}

//******************************************************************************

void AccountDistribution::ValidateBankAcctType(const DString& BankAcctType)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateBankAcctType" ) );   

   if( pMgmtCoOptions )
   {
      DString l;
      pMgmtCoOptions->getField( ifds::BankLayout, l, BF::HOST );
      if( l.strip() == INTERNATIONAL_BANK_ADD  && BankAcctType == NULL_STRING )
      {
//			DString FieldName;
         //       PropertyRepository::getInstance()->getFieldNameFromId( DBR::BankAcctType, FieldName );
//CP			DP::getFieldNameFromId( DBR::BankAcctType, FieldName );
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_SELECT  );
      }
   }
//	}
}

//******************************************************************************
// total of the distribution has to be 100 percent
//
//******************************************************************************
void AccountDistribution::ValidateDistributePercentage(const DString& strValue,const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateDistributePercentage" ) );
/*	DString strFundCode,strFundClass;
   getField(DBR::FundCode,strFundCode,idDataGroup);
   strFundCode.strip();
   getField(DBR::ClassCode,strFundClass,idDataGroup);
   strFundClass.strip();

   DString strFund,strClass,strPercent;
   float fPercent = 0.0;
   
   BFObjIter iterList( *_pList, idDataGroup );

   while( !iterList.end())
   {
      if(this != iterList.getObject() ){
         iterList.getObject( )->getField(DBR::FundCode, strFund, idDataGroup );
         strFund.strip();
         iterList.getObject( )->getField(DBR::ClassCode, strClass, idDataGroup );
         strClass.strip();
         if( (strFund == strFundCode) && (strClass == strFundClass)      ){
            iterList.getObject( )->getField(DBR::AllocPercent, strPercent, idDataGroup );
            strPercent.strip();
            fPercent += atof( strPercent.asA().c_str() );
            }
      }

      ++iterList;
   }

   fPercent += atof( strValue.asA().c_str()); 
   if(fPercent != 100.00)ADDCONDITIONFROMFILE( CND::ERR_PERCENTAGE_NOT_EQUAL_100 );
*/



   DString dstrPercentage(strValue);
   dstrPercentage.strip().stripAll(I_CHAR(','));
   if( dstrPercentage == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE );
      return;
   }
   double dPercent = DSTCommonFunctions::convertToDouble(dstrPercentage);
   if( dPercent > 100 || dPercent == 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
      return;
   }

}

//******************************************************************************

SEVERITY AccountDistribution::ValidateFundCode( const BFFieldId& idField, const DString& strValue,
                                            const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateFundCode" ) );

   DString dstrFundCode( strValue );
   dstrFundCode.strip().upperCase();
   if( dstrFundCode == NULL_STRING )
   {
      if( idField == ifds::FundCode )
      {
         DString dstrFrFundNumber;
         getField ( ifds::FrFundNumber, dstrFrFundNumber, idDataGroup );
         if( dstrFrFundNumber != NULL_STRING )
            setFieldNoValidate( ifds::FrFundNumber, NULL_STRING, idDataGroup, false,true,true);
         if( !isAllFundsMode( idDataGroup ) )
         {
            ADDCONDITIONFROMFILE( CND::ERR_BLANK_FUND );
         }
      }
      else if( idField == ifds::FundToCode )
      {
         DString dstrToFundNumber;
         getField ( ifds::ToFundNumber, dstrToFundNumber, idDataGroup );
         if( dstrToFundNumber != NULL_STRING )
            setFieldNoValidate( ifds::ToFundNumber, NULL_STRING, idDataGroup, false,true,true);
         if( !isAllFundsMode( idDataGroup ) )
         {
            ADDCONDITIONFROMFILE( CND::ERR_BLANK_FUND );
         }
      }

      return(GETCURRENTHIGHESTSEVERITY());
   }

   if( dstrFundCode == CASH && idField == ifds::FundToCode )
   {
      //for ReinDistOnly == 'Y', don't allow cash      
      validateCash(idDataGroup);      
      return(GETCURRENTHIGHESTSEVERITY());

   }
   if( dstrFundCode == CASH && idField == ifds::FundCode )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   if( !IsValidFund(dstrFundCode,idDataGroup) )
   {
      if( idField == ifds::FundCode )
         setFieldNoValidate( ifds::FrFundNumber, NULL_STRING, idDataGroup, false,true,true);
      else if( idField == ifds::FundToCode )
         setFieldNoValidate( ifds::ToFundNumber, NULL_STRING, idDataGroup, false,true,true);

      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES ); 
      return(GETCURRENTHIGHESTSEVERITY());
   }

   DString dstrEffectiveDate;
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
   dstrEffectiveDate.strip();
   if( _level == FUND_CLASS_LEVEL && dstrEffectiveDate == NULL_STRING )
   {
      getParent()->getParent()->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
      dstrEffectiveDate.strip();
   }
   if( ! (_pFundMasterList->IsFundValidAtDate(dstrFundCode,dstrEffectiveDate,idDataGroup) ) )
   {
      DString msg( I_( "FUNDNAME=" ) );
      msg += dstrFundCode;
      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, msg.c_str() );
   }
   if( idField == ifds::FundCode )
   {
      DString dstrClassCode = NULL_STRING;
      getField( ifds::ClassCode, dstrClassCode, idDataGroup );

      if( dstrClassCode != NULL_STRING && !(_pFundDetailList->IsFundValidAtDate(dstrFundCode,dstrClassCode,
                                                                                dstrEffectiveDate,idDataGroup) ) )
      {
         DString msg( I_( "FUNDNAME=" ) );
         msg += dstrFundCode;
         msg += I_( ";CLASSNAME=" );
         msg += dstrClassCode;
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, msg.c_str() ); 
      }
      if( ( _level==ACCOUNT_LEVEL ) && (dstrClassCode != NULL_STRING ) )
      {
         DString dstrMgtFeeRbtElig, dstrTransType;
         FundDetail *pFundDetail = NULL;
         if( _pFundDetailList->getFundDetail ( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) )
         {
            pFundDetail->getField ( ifds::MgtFeeRbtElig, dstrMgtFeeRbtElig, idDataGroup );         
            getField ( ifds::TransType, dstrTransType, idDataGroup );
            if( ( dstrTransType == MFR ) && ( dstrMgtFeeRbtElig == NO ) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_THIS_FUND_HAS_NO_MGT_REBATE_FEE );
            }
         }
      }
      return(GETCURRENTHIGHESTSEVERITY());
   }

   if( GETCURRENTHIGHESTSEVERITY() <= WARNING && (_level == FUND_CLASS_LEVEL && idField == ifds::FundToCode ))
   {
      isToFundClassAllowed ( idField, strValue, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AccountDistribution::ValidateClassCode( const BFFieldId& idField, 
                                             const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateClassCode" ) );

   DString dstrClassCode( strValue );
   dstrClassCode.strip().upperCase();
   if( dstrClassCode == NULL_STRING )
   {
      if( idField == ifds::ClassCode )
         setFieldNoValidate( ifds::FrFundNumber, NULL_STRING, idDataGroup, false,true,true);
      else if( idField == ifds::ClassToCode )
         setFieldNoValidate( ifds::ToFundNumber, NULL_STRING, idDataGroup, false,true,true);

      //ADDCONDITIONFROMFILE( CND::ERR_BLANK_CLASS );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   DString dstrFundCode;
   if( idField == ifds::ClassCode )
      getField( ifds::FundCode, dstrFundCode, idDataGroup );
   else
   {
      getField( ifds::FundToCode, dstrFundCode, idDataGroup );
   }
   dstrFundCode.strip().upperCase();
   if( dstrFundCode == NULL_STRING )
   {
      if( idField == ifds::ClassCode )
         setFieldNoValidate( ifds::FrFundNumber, NULL_STRING, idDataGroup, false,true,true);
      else if( idField == ifds::ClassToCode )
         setFieldNoValidate( ifds::ToFundNumber, NULL_STRING, idDataGroup, false,true,true);

      //	ADDCONDITIONFROMFILE( CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE );
      return(GETCURRENTHIGHESTSEVERITY());

   }
   if( dstrFundCode == CASH )
   {
      if( dstrClassCode != I_( "A" ) )
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      return(GETCURRENTHIGHESTSEVERITY());
   }

//   MFAccount *pMFAccount;
//   getWorkSession().getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount );

   DString dstrEffectiveDate;
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
   dstrEffectiveDate.strip(); 
   if( _level == FUND_CLASS_LEVEL && dstrEffectiveDate == NULL_STRING )
   {
      getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
      dstrEffectiveDate.strip();
   }
   DString dstrTradeType;
   if( _level == FUND_CLASS_LEVEL )
   {
      dstrTradeType = EX_FER_IN_CODE;
   }
   else if( _level == ACCOUNT_LEVEL )
   {

      dstrTradeType = EX_FER_OUT_CODE;

   }
/* Move to FundClass validation   
   //only validate on fund level
	if (!dstrTradeType.strip().empty() && _level == FUND_CLASS_LEVEL)
      _pMFAccount->canTradeFundClass (dstrFundCode,dstrClassCode,dstrTradeType,
                                      dstrEffectiveDate,idDataGroup );
*/
// validate fundclase effective date against fundDetailList 

   if( !(_pFundDetailList->IsFundValidAtDate(dstrFundCode,dstrClassCode,
                                             dstrEffectiveDate,idDataGroup) ) )
   {
      DString msg( I_( "FUNDNAME=" ) );
      msg += dstrFundCode;
      msg += I_( ";CLASSNAME=" );
      msg += dstrClassCode;
      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, msg.c_str() ); 
      if( ( _level==ACCOUNT_LEVEL ) && (dstrClassCode != NULL_STRING ) )
      {
         DString dstrMgtFeeRbtElig, dstrTransType;
         FundDetail *pFundDetail = NULL;
         if( _pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) )
         {
            pFundDetail->getField ( ifds::MgtFeeRbtElig, dstrMgtFeeRbtElig, idDataGroup );
            getField ( ifds::TransType, dstrTransType, idDataGroup );
            if( ( dstrTransType == MFR ) && ( dstrMgtFeeRbtElig == NO ) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_THIS_FUND_HAS_NO_MGT_REBATE_FEE );
            }
         }
      }
   }

   if ( GETCURRENTHIGHESTSEVERITY() <= WARNING && (_level == FUND_CLASS_LEVEL && idField == ifds::ClassToCode ))
   {
      isToFundClassAllowed ( idField, strValue, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AccountDistribution::getSplitList( AccountDistributionList *&pSplitList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSplitList" ) );

   //pSplitList = _pSplitList;
   pSplitList = dynamic_cast<AccountDistributionList * >(getObject( I_("SplitList"), idDataGroup ));
// if there is no splitList we create one but should not at Host level ---yingbao
   if( !pSplitList && idDataGroup != BF::HOST )
   {
      if( _distributionData )
      {
         delete _distributionData;
         _distributionData = NULL;
      }
      DString dstrEffectiveDate;
      getWorkSession().getDateInHostFormat(dstrEffectiveDate, 
                                           DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY,
                                           idDataGroup); 
      DString dstrFundCode, dstrClassCode;
      getField(ifds::FundCode,dstrFundCode,idDataGroup);
      dstrFundCode.strip().upperCase();

      getField(ifds::ClassCode,dstrClassCode,idDataGroup);
      dstrClassCode.strip().upperCase();

      getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup);
      dstrEffectiveDate.strip().upperCase();

      _pSplitList = new AccountDistributionList ( *this );

      if( _pSplitList->init( false,
                             idDataGroup, 
                             _dstrAccountNum,
                             _dstrShareholderNum, 
                             FUND_CLASS_LEVEL,
                             _distributionData,
                             dstrFundCode, 
                             dstrClassCode, 
                             dstrEffectiveDate ) <= WARNING )
      {
         setObject( _pSplitList, I_( "SplitList" ), OBJ_ACTIVITY_NONE, idDataGroup ); 
         pSplitList = _pSplitList;
      }
      else
      {
         delete _pSplitList;
         _pSplitList = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

/*******************************************************************************/

SEVERITY AccountDistribution::doApplyRelatedChanges(
                                                   const BFFieldId& idField,
                                                   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   DString str;

   DString dstrTransTypeDesc;
   getField ( ifds::TransTypeDesc, dstrTransTypeDesc, idDataGroup );
   if( dstrTransTypeDesc == LOCK_TRANS_TYPE &&  !( idField == ifds::TransTypeDesc || idField == ifds::TransType ) )
      setFieldReadOnly( ifds::TransType, idDataGroup, true );

   if( idField == ifds::TransTypeDesc && dstrTransTypeDesc == VALIDATE_ADDR_CODE )
   {
      DString dstrTransType;
      getField ( ifds::TransType, dstrTransType, idDataGroup, false );
      if( dstrTransType == MFR )
         setValidFlag ( ifds::AddrCode, idDataGroup, false );
   }

   // We should change the way we use TransTypeDesc to mark fields readonly or validate address.
   if( idField == ifds::TransTypeDesc )
      setUpdatedFlag ( ifds::TransTypeDesc, idDataGroup, false );

   if( _pSplitList && _level == ACCOUNT_LEVEL )
   {
      if( idField == ifds::FundCode                  ||
          idField == ifds::ClassCode                 ||
          idField == ifds::TransType                 ||
          idField == ifds::EffectiveDate             ||
          idField == ifds::AcctDistribOpt            ||
          idField == ifds::AcctDistribCurrencyOption ||
          idField == ifds::AllFundsDistrib           ||
          idField == ifds::VerifyStat )
      {
         getField(idField, str, idDataGroup, false );

         BFObjIter iter( *_pSplitList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

         while( !iter.end() )
         {
            dynamic_cast<AccountDistribution*>(iter.getObject( ))->setField(idField, str, idDataGroup, false);
            ++iter;
         }
      }

	  if( idField == ifds::FundCode || idField == ifds::ClassCode )
	  {
		  setFundNumber(idField,idDataGroup);

		  DString dstrFundCode, dstrClassCode;
		  getField ( ifds::FundCode, dstrFundCode, idDataGroup, false );
		  getField ( ifds::ClassCode, dstrClassCode, idDataGroup, false );

		  if( ( dstrFundCode != NULL_STRING ) && ( dstrClassCode != NULL_STRING ) )
		  { 
			  setLastIDRate( idDataGroup );
		  }
	  }

      if( idField == ifds::FrFundNumber )
      {
         setFundClassCode(idField,idDataGroup);
//  	   	setUpdatedFlag( DBR::FrFundNumber, idDataGroup, false );
      }

      if( idField == ifds::TransType )
      {
         setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::DistributionTransType );      
         //setFieldReadOnly ( ifds::TransType, idDataGroup, true );
      }

      if (idField != ifds::TransTypeDesc)
      {
         verifyStatusRelatedChanges (idField, idDataGroup);
      }	 	 
   }

   //BEGIN the following fields are on both from and to sides
   if( idField == ifds::AllFundsDistrib )
         allFundsRelatedChanges(idDataGroup);

   if( idField == ifds::AcctDistribOpt )
   {
      acctDistribOptRelChanges( idDataGroup );
   }

   if( idField == ifds::AcctDistribCurrencyOption )
   {
      acctDistribCurrencyOptRelChanges( idDataGroup );
   }

   //the following fields are on both from and to sides - END

   if (_level == FUND_CLASS_LEVEL)
   {
      DString dstrTransTypeDesc;
      getParent()->getParent()->getField ( ifds::TransTypeDesc, dstrTransTypeDesc, idDataGroup );
      if( dstrTransTypeDesc == LOCK_TRANS_TYPE &&  !( idField == ifds::TransTypeDesc || idField == ifds::TransType ) )
         getParent()->getParent()->setFieldReadOnly( ifds::TransType, idDataGroup, true );

      if (idField == ifds::Currency || idField == ifds::DistributionPayType)
      {
         DString payType;

         getField (ifds::DistributionPayType, payType, 
            idDataGroup, false);
         payType.strip().upperCase();
         if (payType == EFT)
         {
            fileProcessorRelatedChanges (idDataGroup);
         }
      }

      if ( idField == ifds::FundCode || idField == ifds::ClassCode )
      {
         setPayTypeSubstSet(idDataGroup);
         setValidFlag( ifds::DistributionPayType, idDataGroup, false );
      }

      if (idField == ifds::PayMethod || idField == ifds::DistributionPayType)
      {
         payMethodRelatedChanges (idDataGroup);
      }

      if (idField == ifds::ACHProcessor)
      {
         setCurrencySubstSet (idDataGroup);
      }

      if( idField == ifds::FundToCode )
      {
         getField(idField, str, idDataGroup, false );

         if( str.strip().upperCase() == CASH )
         {
            DString dstrTransType;
            getField ( ifds::TransType, dstrTransType, idDataGroup, false );
            setPayTypeSubstSet(idDataGroup, dstrTransType);

            setFieldNoValidate(ifds::ClassToCode, I_("A"), idDataGroup, false, true,true);
            setFieldNoValidate( ifds::ToFundNumber, I_( " N/A " ), idDataGroup, false,true,true);
//CP20030319            lFlag = getFieldStateFlags( ifds::DistributionPayType, idDataGroup );
//CP20030319            setFieldStateFlags( ifds::DistributionPayType, idDataGroup, lFlag | BFCBO::STATE_FLAGS::REQUIRED );
            setFieldRequired( ifds::DistributionPayType, idDataGroup, true );
            setValidFlag( ifds::DistributionPayType, idDataGroup, false );

//CP20030319            lFlag = getFieldStateFlags( ifds::Currency, idDataGroup );
//CP20030319            setFieldStateFlags( ifds::Currency, idDataGroup, lFlag | BFCBO::STATE_FLAGS::REQUIRED );
            DString strAcctDistribCurrOpt;
            getField( ifds::AcctDistribCurrencyOption, strAcctDistribCurrOpt, idDataGroup, false );
            if( !isAllFundsMode( idDataGroup ) || 
                strAcctDistribCurrOpt.strip()!= FUND_CURRENCY )
            {
               setFieldRequired( ifds::Currency, idDataGroup, true );
               setValidFlag( ifds::Currency, idDataGroup, false );
            }
            
            DString dstrAccountTaxType;
            _pMFAccount->getField(ifds::TaxType, dstrAccountTaxType, idDataGroup, false);

            if(dstrAccountTaxType == TAX_TYPE_OA || dstrAccountTaxType == TAX_TYPE_SA || dstrAccountTaxType == TAX_TYPE_SRS)
            {
               DString dstrAccountSettleCurrency;
               _pMFAccount->getField(ifds::SettleCurrency, dstrAccountSettleCurrency, idDataGroup, false);
               setField(ifds::Currency, dstrAccountSettleCurrency, idDataGroup, false);
               BFProperties* pSettleCurrencyProps = _pMFAccount->getFieldProperties(ifds::SettleCurrency, idDataGroup );
               DString dstrCurrencyAllSubst;
               pSettleCurrencyProps->getAllSubstituteValues(dstrCurrencyAllSubst);
               setFieldAllSubstituteValues(ifds::Currency, idDataGroup, dstrCurrencyAllSubst);
               setField(ifds::Currency, dstrAccountSettleCurrency, idDataGroup, false);
               setField(ifds::DistributionPayType, I_("RA"), idDataGroup, false);
               setFieldReadOnly(ifds::DistributionPayType, idDataGroup, true);
            }
            else
            {
               setFieldReadOnly(ifds::DistributionPayType, idDataGroup, false);
            }

         }
         else
         {
//CP20030319            lFlag = getFieldStateFlags( ifds::DistributionPayType, idDataGroup );
//CP20030319            setFieldStateFlags( ifds::DistributionPayType, idDataGroup, lFlag & ~BFCBO::STATE_FLAGS::REQUIRED );
            setFieldRequired( ifds::DistributionPayType, idDataGroup, false );
            setValidFlag( ifds::DistributionPayType, idDataGroup, true );

//CP20030319            lFlag = getFieldStateFlags( ifds::Currency, idDataGroup );
//CP20030319            setFieldStateFlags( ifds::Currency, idDataGroup, lFlag & ~BFCBO::STATE_FLAGS::REQUIRED );
            setFieldRequired( ifds::Currency, idDataGroup, false );
            setValidFlag( ifds::Currency, idDataGroup, true );
         }
         setPayTypeDefault( idDataGroup );
      }

      if( idField == ifds::FundToCode || idField == ifds::ClassToCode )
      {
         getField(idField, str, idDataGroup, false );

         if( str.strip().upperCase() != CASH )
         {
            setFundNumber(idField,idDataGroup);
         }
         
         revalidateField(ifds::ToSoftCapCheck, idDataGroup);
      }

      if( idField == ifds::ToFundNumber )
      {
         DString dstrTransType;
         getField ( ifds::TransType, dstrTransType, idDataGroup, false );
         setPayTypeSubstSet(idDataGroup, dstrTransType);

         getField(idField, str, idDataGroup, false );

         if( str.strip().upperCase() != I_( "N/A" ) )
            setFundClassCode(idField,idDataGroup);
         else
         {
            // this field is a gui field and is always updated
            setUpdatedFlag( ifds::ToFundNumber, idDataGroup, false );
         }

         revalidateField(ifds::ToSoftCapCheck, idDataGroup);
      }

      if( idField == ifds::EffectiveDate )
      {
          setValidFlag ( ifds::AddrCode, idDataGroup, false);
          revalidateField(ifds::ToSoftCapCheck, idDataGroup);
      }

      if( ( idField == ifds::FundCode ) || ( idField == ifds::ClassCode ) ||
          ( idField == ifds::FundToCode ) || ( idField == ifds::ClassToCode ) ||
          ( idField == ifds::ToFundNumber) )
      {
         DString dstrFundToCode;
         getField ( ifds::FundToCode, dstrFundToCode, idDataGroup, false );
         if( dstrFundToCode == CASH )
         {
            setValidFlag ( ifds::FundToCode, idDataGroup, false); // cash validation
            DString dstrFundCode, dstrClassCode;
            getField ( ifds::FundCode, dstrFundCode, idDataGroup, false );
            getField ( ifds::ClassCode, dstrClassCode, idDataGroup, false );
            if( ( dstrFundCode != NULL_STRING ) && ( dstrClassCode != NULL_STRING ) )
            {
               DString dstrCurrency, dstrMultiCurrency;
               if( pMgmtCoOptions )
                  pMgmtCoOptions->getField( ifds::MultiCurrency, dstrMultiCurrency, BF::HOST );
               if( dstrMultiCurrency == NO )
               {
                  GetFundCurrency ( dstrCurrency, idDataGroup );
                  setFieldNoValidate ( ifds::Currency, dstrCurrency, idDataGroup, false, true, false, false );
                  setFieldReadOnly ( ifds::Currency, idDataGroup, true );
               }
            }
         }		 
      }	

	  if( idField == ifds::TotalDistribRate ) 
	  {
		  DString dstrTotalDistribRate;
		  getField ( ifds::TotalDistribRate, dstrTotalDistribRate, idDataGroup, false );
		  if (idDataGroup != BF::HOST) 
		  {			  
			  bool bVerificationEnabled = false;
			  getWorkSession ().isVerificationEnabled ( idDataGroup, DISTRIB_CATEGORY, DISTRIB_LEVEL, bVerificationEnabled);			  
			  AccountDistributionList* pSplitList = dynamic_cast<AccountDistributionList*>( getParent() );
			  if( pSplitList )
				  pSplitList->recalculatePercentages( idDataGroup, bVerificationEnabled );
		  }
	  }

      verifyStatusRelatedChanges (idField, idDataGroup);
   }

   if (idField == ifds::TotalDistribRate || idField == ifds::TotalAllocPercent)
       setUpdatedFlag( idField, idDataGroup, false ); // this field is a gui field and is always updated

   //Softcapped must be revalidated
   if (idField != ifds::TotalDistribRate && idField != ifds::TotalAllocPercent && 
       !_bInit && isFieldUpdated(idField, idDataGroup)){
       if (_level == ACCOUNT_LEVEL && _pSplitList)
       {
           _pSplitList->setAllAllocsFndClsValidFlag(false, idDataGroup);
       }
       else if (_level == FUND_CLASS_LEVEL && idField != ifds::TransType)
       {
           AccountDistributionList* pSplitList = dynamic_cast<AccountDistributionList*>(getParent());
           if (pSplitList)
               pSplitList->setAllAllocsFndClsValidFlag(false, idDataGroup);
       }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountDistribution::allFundsRelatedChanges(const BFDataGroupId&  idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "allFundsRelatedChanges" ) );

   if( _level == ACCOUNT_LEVEL )
   {
      if( isAllFundsMode( idDataGroup ) )
      {
         setNonDummyFlag();
         //make sure that we only keep one allocation  at fund/class level
         if( _pSplitList )
         {
            BFObjIter iter( *_pSplitList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
            bool bDelete = false;
            while( !iter.end() )
            {
               if( bDelete )
               {
                  iter.deleteObject();
               }
               else
               {
                  bDelete = true;
                  ++iter;
               }
            }
         }
         setFieldRequired( ifds::FundCode, idDataGroup, false );
         setFieldRequired( ifds::ClassCode, idDataGroup, false );
         setFieldReadOnly ( ifds::FrFundNumber, idDataGroup, true );
         setFieldReadOnly ( ifds::FundCode, idDataGroup, true );
         setFieldReadOnly ( ifds::ClassCode, idDataGroup, true );
         setFieldNoValidate( ifds::FrFundNumber, NULL_STRING, idDataGroup, false,true,true);
         setFieldNoValidate( ifds::FundCode, NULL_STRING, idDataGroup, false,true,true);
         setFieldNoValidate( ifds::ClassCode, NULL_STRING, idDataGroup, false,true,true);
         setFieldReadOnly( ifds::AcctDistribOpt, idDataGroup, false );
         bool blCashAllowed = true;
         if( _pMFAccount != NULL ) 
         {
               TaxTypeRule *pTaxTypeRule = NULL;
               if ( _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
               {
                  DString strReinDistOnly;
                  pTaxTypeRule->getField( ifds::ReinDistOnly , strReinDistOnly, idDataGroup );
                  if( strReinDistOnly == YES )
                  {
                     blCashAllowed = false;
                  }
               }
            
               DString dstrAccountTaxType;
               _pMFAccount->getField(ifds::TaxType, dstrAccountTaxType, idDataGroup, false);

               if(dstrAccountTaxType == TAX_TYPE_OA || dstrAccountTaxType == TAX_TYPE_SA || dstrAccountTaxType == TAX_TYPE_SRS)
               {
                  setFieldNoValidate( ifds::AcctDistribCurrencyOption, PREFERRED_CURRECNY, idDataGroup, false,true,true);
                  setFieldReadOnly ( ifds::AcctDistribCurrencyOption, idDataGroup, true );
               }
         }

         if( blCashAllowed )
         {
            setFieldNoValidate( ifds::AcctDistribOpt, CASH_ACCT_LEVEL, idDataGroup, false,true,true);			
         }
         else
         {
            setFieldNoValidate( ifds::AcctDistribOpt, REINVEST, idDataGroup, false,true,true);			
         }
      }
      else
      {
         //not an account level distribution
         setFieldRequired( ifds::FundCode, idDataGroup, true );
         setFieldRequired( ifds::ClassCode, idDataGroup, true );
         setFieldReadOnly ( ifds::FrFundNumber, idDataGroup, false );
         setFieldReadOnly ( ifds::FundCode, idDataGroup, false );
         setFieldReadOnly ( ifds::ClassCode, idDataGroup, false );
         setFieldNoValidate( ifds::AcctDistribOpt, NULL_STRING, idDataGroup, false,true,true);
         setFieldReadOnly( ifds::AcctDistribOpt, idDataGroup, true );
         setFieldNoValidate( ifds::AcctDistribCurrencyOption, NULL_STRING, idDataGroup, false,true,true);
         setFieldReadOnly( ifds::AcctDistribCurrencyOption, idDataGroup, true );
         setValidFlag( ifds::FundCode, idDataGroup, false );
         setValidFlag( ifds::ClassCode, idDataGroup, false );
         setValidFlag( ifds::FrFundNumber, idDataGroup, false );
      }
   }
   else if( _level == FUND_CLASS_LEVEL )
   {
      if( isAllFundsMode( idDataGroup ) )
      {
         setFieldNoValidate( ifds::AllocPercent, I_("100.00"), idDataGroup, false,true,true);
         setFieldReadOnly( ifds::AllocPercent, idDataGroup, true );
      }
      else
      {
         setFieldNoValidate( ifds::FundToCode, NULL_STRING, idDataGroup, false,true,true);
         setFieldNoValidate( ifds::ClassToCode, NULL_STRING, idDataGroup, false,true,true);
         setFieldNoValidate( ifds::ToFundNumber, NULL_STRING, idDataGroup, false,true,true);
         setValidFlag( ifds::FundToCode, idDataGroup, false );
         setValidFlag( ifds::ClassToCode, idDataGroup, false );
         setValidFlag( ifds::ToFundNumber, idDataGroup, false );
         setFieldNoValidate( ifds::AllocPercent, I_("0.00"), idDataGroup, false,true,true);
         setFieldReadOnly( ifds::AllocPercent, idDataGroup, false );
         setValidFlag( ifds::AllocPercent, idDataGroup, false );
         setFieldReadOnly( ifds::FundToCode, idDataGroup, false );
         setFieldReadOnly( ifds::ClassToCode, idDataGroup, false );
         setFieldReadOnly( ifds::ToFundNumber, idDataGroup, false );
         setFieldReadOnly( ifds::Currency, idDataGroup, false );

		 setFieldNoValidate( ifds::DistribRate, I_("0.00"), idDataGroup, false,true,true);
		 setFieldReadOnly( ifds::DistribRate, idDataGroup, false );
		 setFieldNoValidate( ifds::LastIDRate, I_("0.00"), idDataGroup, false,true,true);
		 setFieldReadOnly( ifds::LastIDRate, idDataGroup, true );
		 setFieldNoValidate( ifds::TotalDistribRate, I_("0.00"), idDataGroup, false,true,true);
		 setFieldReadOnly( ifds::TotalDistribRate, idDataGroup, true );
		 setFieldNoValidate( ifds::TotalAllocPercent, I_("0.00"), idDataGroup, false,true,true);
		 setFieldReadOnly( ifds::TotalAllocPercent, idDataGroup, true );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AccountDistribution::payMethodRelatedChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "payMethodRelatedChanges" ) );

   DString payMethod;

   getField (ifds::PayMethod, payMethod, idDataGroup);
   payMethod.strip();
//deal with the file processor
   fileProcessorRelatedChanges (idDataGroup);
   setCurrencySubstSet (idDataGroup);

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);
   if (!isBankingAllowed (idDataGroup))
   {
	  //clear the banking fields
	  clearBankingFields( idDataGroup );
   
      DString fundToCode;

      getField (ifds::FundToCode, fundToCode, idDataGroup, false );
      if (fundToCode != CASH)
      {
         setFieldRequired (ifds::Currency, idDataGroup, false);
         setValidFlag (ifds::Currency, idDataGroup, true);
      }
      if (!isEFTCheckAllowed (idDataGroup))
      {
         setFieldAllSubstituteValues (ifds::Currency, 
            idDataGroup, strCurrencySubstList);
      }
   }
   else
   {
      if (payMethod !=CHQ)
      {
        setPayMethodSubstSet(idDataGroup);
        
        //currency is required, unless distrib option is FUND_CURRENCY
         DString strAcctDistribCurrOpt;
         getField( ifds::AcctDistribCurrencyOption, strAcctDistribCurrOpt, idDataGroup, false );
         if( !isAllFundsMode( idDataGroup ) || 
            strAcctDistribCurrOpt.strip()!= FUND_CURRENCY )
         {
            setFieldRequired (ifds::Currency, idDataGroup, true);
            setValidFlag (ifds::Currency, idDataGroup, false);
         }

         DString bankAcctName, 
            bankAcctType,
            payType,
            bankIdValue;

         getField (ifds::BankAcctName, bankAcctName, idDataGroup);
         bankAcctName.strip();
         if (bankAcctName == NULL_STRING)
         {
            if (_pMFAccount)
            {
               _pMFAccount->getAcctName (bankAcctName, idDataGroup);
            }
            bankAcctName.strip();   
            setFieldNoValidate (ifds::BankAcctName, bankAcctName, 
               idDataGroup, false);
         }
         // if bankIdvalue has a value already, do not change the BankIdType
         getField (ifds::BankIdValue, bankIdValue, idDataGroup);
         if (bankIdValue.strip() == NULL_STRING)  
         {
            DString defaultBankType;

            getWorkSession().getOption (ifds::DefaultBankType, 
               defaultBankType, idDataGroup, false );
            setFieldNoValidate (ifds::BankIdType, defaultBankType, 
               idDataGroup, false);
         }
         getField(ifds::BankAcctType, bankAcctType, idDataGroup);
         bankAcctType.strip();
         if (bankAcctType == NULL_STRING)
         {
            setFieldNoValidate (ifds::BankAcctType, I_("1"), idDataGroup, false);
         }
      }
   }

   bool bIsBankingAllowed = isBankingAllowed (idDataGroup);

   setFieldRequired (ifds::BankIdValue, idDataGroup, bIsBankingAllowed);
   setValidFlag (ifds::BankIdValue, idDataGroup, !bIsBankingAllowed);
   setFieldRequired (ifds::BankAcctType, idDataGroup, bIsBankingAllowed);
   setValidFlag (ifds::BankAcctType, idDataGroup, !bIsBankingAllowed);
   setFieldRequired (ifds::BankAcctNum, idDataGroup, bIsBankingAllowed);
   setValidFlag (ifds::BankAcctNum, idDataGroup, !bIsBankingAllowed);

   setFieldReadOnly( ifds::BankAcctNum, idDataGroup, true );
   setFieldReadOnly( ifds::BankIdValue, idDataGroup, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
bool AccountDistribution::isEFTCheckAllowed (const BFDataGroupId& idDataGroup) const
{
   DString distributionPayType, 
      dstrPayMethod;

   getField(ifds::DistributionPayType, distributionPayType, idDataGroup);
   getField(ifds::PayMethod, dstrPayMethod, idDataGroup);
   distributionPayType.strip().upperCase();
   dstrPayMethod.strip().upperCase();   
   return  (distributionPayType == EFT || 
      distributionPayType == INTERNATIONAL_WIRE) &&
      dstrPayMethod == CHQ;
}

//*******************************************************************************
bool AccountDistribution::isBankingAllowed (const BFDataGroupId& idDataGroup)
{
   DString distributionPayType, 
      dstrPayMethod;

   getField(ifds::DistributionPayType, distributionPayType, idDataGroup);
   getField(ifds::PayMethod, dstrPayMethod, idDataGroup);

   distributionPayType.strip().upperCase();
   dstrPayMethod.strip().upperCase();

   DString strAcctDistribCurrOpt;
   getField( ifds::AcctDistribCurrencyOption, strAcctDistribCurrOpt, idDataGroup, false );
   if( isAllFundsMode( idDataGroup ) && strAcctDistribCurrOpt.strip() == FUND_CURRENCY ) 
   {
      return false;
   }

   return ((distributionPayType == EFT && dstrPayMethod != CHQ) || 
		   (distributionPayType == INTERNATIONAL_WIRE && (dstrPayMethod == WIRE || dstrPayMethod == NULL_STRING))) ;
}

//*******************************************************************************
bool AccountDistribution::DistributionPayTypeIsSysCheck(const BFDataGroupId& idDataGroup)
{
   DString DistributionPayType;
   getField(ifds::DistributionPayType, DistributionPayType, idDataGroup);
   DistributionPayType.strip();
   return(DistributionPayType == SYSTEM_GENERATED_CHEQUE);
}

//*******************************************************************************
void AccountDistribution::CopyInfoToFundClassLevel(BFAbstractCBO *pParentDistribution, const BFDataGroupId& idDataGroup)
{
   DString str;
   
   pParentDistribution->getField(ifds::FundCode, str, idDataGroup );
   setFieldNoValidate(ifds::FundCode, str, idDataGroup, false, true, false, false);

   pParentDistribution->getField(ifds::ClassCode, str, idDataGroup );
   setFieldNoValidate(ifds::ClassCode, str, idDataGroup, false, true, false, false);

   pParentDistribution->getField(ifds::EffectiveDate, str, idDataGroup );
   setFieldNoValidate(ifds::EffectiveDate, str, idDataGroup, false, true, false, false);

   pParentDistribution->getField(ifds::TransType, str, idDataGroup );

   if (!_bVerificationEnabled )
   {
      setFieldNoValidate(ifds::TransType, str, idDataGroup);
   }
   else
   {
      // not trig to related change during copy value of account level fields 
      // to fund\class level
      setFieldNoValidate(ifds::TransType, str, idDataGroup, false, true, false, false);
   }

   SetRequiredField( idDataGroup );  
   fileProcessorRelatedChanges(idDataGroup);
}


//*******************************************************************************
void AccountDistribution::SetRequiredField( const BFDataGroupId& idDataGroup )
{
   if (_level == FUND_CLASS_LEVEL)
   {
      DString strAcctDistribOpt;
      getField( ifds::AcctDistribOpt, strAcctDistribOpt, idDataGroup, false);
      if( strAcctDistribOpt == REINVEST )
      {
         setFieldRequired( ifds::FundToCode, idDataGroup, false );
         setFieldRequired( ifds::ClassToCode, idDataGroup, false );
         setFieldRequired (ifds::ACHProcessor, idDataGroup, false);
         //setValidFlag (ifds::ACHProcessor, idDataGroup, true);
      }
      else
      {
        setFieldRequired( ifds::FundToCode, idDataGroup, true );
        setFieldRequired( ifds::ClassToCode, idDataGroup, true );
      }
      setFieldRequired( ifds::AllocPercent, idDataGroup, true );

	  DString dstrDistribInputMethod;
	  getParent()->getParent()->getField ( ifds::DistribInputMethod, dstrDistribInputMethod, idDataGroup );
	  bool bIsReadOnly =  dstrDistribInputMethod == I_("1") ? true : false;
	  setFieldReadOnly (ifds::AllocPercent, idDataGroup, bIsReadOnly);
   }
   if (_level == ACCOUNT_LEVEL)
   {
      if( !isAllFundsMode( idDataGroup ) )
      {
         setFieldRequired( ifds::FundCode, idDataGroup, true );
         setFieldRequired( ifds::ClassCode, idDataGroup, true );		
      }
      setValidFlag( ifds::FundCode, idDataGroup, false );
      setValidFlag( ifds::ClassCode, idDataGroup, false );	  
      setFieldRequired( ifds::EffectiveDate, idDataGroup, true );
      setFieldRequired( ifds::TransType, idDataGroup, true );
   }
}

//*******************************************************************************
void AccountDistribution::GetFundCurrency(DString &Currency, const BFDataGroupId& idDataGroup) const
{
   Currency = NULL_STRING;
   DString   FundCode, ClassCode;
   getField( ifds::FundCode, FundCode, idDataGroup, false );
   getField( ifds::ClassCode, ClassCode, idDataGroup, false );
   FundCode.strip().upperCase();
   ClassCode.strip().upperCase();
   _pFundDetailList->getField( FundCode, ClassCode, ifds::Currency, Currency, idDataGroup, false); 

}

//*******************************************************************************
void AccountDistribution::ValidateCurrency(const DString& Currency, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateCurrency" ) );
   DString str(Currency);
   str.strip().strip('0');

   if( str == NULL_STRING && IsFundToCodeCash( idDataGroup ) )
   {
      DString strAcctDistribCurrOpt;
      getField( ifds::AcctDistribCurrencyOption, strAcctDistribCurrOpt, idDataGroup, false );
      if( !isAllFundsMode( idDataGroup ) || strAcctDistribCurrOpt.strip() != FUND_CURRENCY ) 
      {
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
      }
   }

   DString dstrFundTo, dstrPayType, dstrNSCCCurrencyList;
   getField ( ifds::FundToCode, dstrFundTo, idDataGroup );
   getField ( ifds::DistributionPayType, dstrPayType, idDataGroup );
   if( dstrFundTo == CASH && dstrPayType == NSCCPayType )
   {
      getWorkSession().getOption( ifds::NSCCCurrencyList, dstrNSCCCurrencyList, idDataGroup, false );
      int nPos = dstrNSCCCurrencyList.find( Currency );
      if( nPos == DString::npos )
      {
//Incident# - 711561 - removed this validation - MFS's business requires user to be able to enter
//distributions for other currencies, other then the ones in the NSCCCurrency list
         //		   ADDCONDITIONFROMFILE( CND::ERR_NSCC_CURRENCY_INVALID );
      }
   }
}

//*******************************************************************************
void AccountDistribution::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   if( _level == FUND_CLASS_LEVEL )
   {
      DString dstrTemp;
      setFieldReadOnly( ifds::BankAcctName, BF::HOST, true );
      setFieldReadOnly( ifds::BankAcctNum, idDataGroup, true );	 
      setFieldReadOnly( ifds::BankIdValue, idDataGroup, true );	  

      BFCBO *pBFCBO = getParent()->getParent();
      pBFCBO->getField ( ifds::FundCode, dstrTemp, idDataGroup,false );
      setFieldNoValidate ( ifds::FundCode, dstrTemp, BF::HOST, false, true,false, false );
      pBFCBO->getField ( ifds::ClassCode, dstrTemp, idDataGroup,false );
      setFieldNoValidate ( ifds::ClassCode, dstrTemp, BF::HOST, false,true,false, false );
      setFieldValid (ifds::FundToCode, idDataGroup, false);
      setFieldValid (ifds::ClassToCode, idDataGroup, false);
      setPayTypeDefault( BF::HOST );
   }

   if( _level == ACCOUNT_LEVEL )
   {
      DString dstrEffectiveDate;
      getWorkSession().getDateInHostFormat(dstrEffectiveDate, 
                                           DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY,
                                           idDataGroup); 

      setFieldNoValidate( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false,true,false, false );
      setFieldSubstituteValues( ifds::TransType, BF::HOST, ifds::DistributionTransType );
   }

   setFieldReadOnly( ifds::AcctDistribOpt, idDataGroup, true );
   setFieldReadOnly( ifds::AcctDistribCurrencyOption, idDataGroup, true );
   setFieldNoValidate( ifds::TransType, I_("ID"), BF::HOST, false, true,false, false);
   setFieldNoValidate( ifds::TransType, I_("ID"), idDataGroup, false, true,false, false);
   setFieldNoValidate( ifds::DelDistribAlloc, I_("N"), BF::HOST, false, true,false, false);   
   setFieldNoValidate( ifds::DelDistribAlloc, I_("N"), idDataGroup, false, true,false, false);
   setFieldNoValidate(ifds::PayMethod, DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): I_("EFT"),BF::HOST,false);
   setFieldNoValidate(ifds::PayMethod, DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): I_("EFT"),idDataGroup,false);
   payMethodRelatedChanges(idDataGroup);
   setPayTypeSubstSet(idDataGroup);
   setValidFlag( ifds::PayTypeMethodCurrOpt, idDataGroup, false );
   SetRequiredField( idDataGroup );   
   _bInit = true;
   initVerifyStatus (idDataGroup, isNew ());
   _bInit = false;
}

//******************************************************************************
SEVERITY AccountDistribution::doValidateAll( const BFDataGroupId &idDataGroup, 
                                             long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   if( _level == FUND_CLASS_LEVEL )
   {
      DString dstrTransType, dstrPayType, dstrPayMethod, dstrAddrCode;
      getField ( ifds::TransType, dstrTransType, idDataGroup );
      getField ( ifds::DistributionPayType, dstrPayType, idDataGroup );
      getField ( ifds::PayMethod, dstrPayMethod, idDataGroup );
      dstrPayType.strip().upperCase();
      dstrPayMethod.strip().upperCase();

      bool bNeedAddressValidation = false;
      bool bNeedPayEntityBankValidation = false;
      bool bIsSystemCheque = DistributionPayTypeIsSysCheck ( idDataGroup );
      bool bIsOtherCheque  = ( dstrPayType == PAYTYPE::EFT && dstrPayMethod == I_("CHQ"));

      if ( dstrTransType.strip().upperCase() == INCOME_DISTRIBUTION )
      {
         bool bVerificationEnabled = false;
         getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                                   DISTRIB_CATEGORY, 
                                                   DISTRIB_LEVEL, 
                                                   bVerificationEnabled);

         DString strDivChqAddr;

         // if transtype is ID, addrcode will be from DivChqAddr of account mailing list
         getDivChqAddr(strDivChqAddr, idDataGroup);

         dstrAddrCode = strDivChqAddr;

         // Only Addr code '01' will be considered as static data
         // that required verification for now
         bNeedAddressValidation = bVerificationEnabled && 
                                 ( bIsSystemCheque || bIsOtherCheque );

         if ( dstrPayType == I_("P") ) //redirect to pay entity
         {
            bNeedPayEntityBankValidation = bVerificationEnabled;
         }
      }

      if (bNeedAddressValidation)
      {
         ValidateAddrCode(dstrAddrCode,idDataGroup);
      }

      if ( bNeedPayEntityBankValidation )
      {
         validatePayEntityBank(idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY AccountDistribution::setFundClassCode(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundClassCode" ) )
   DString dstrFundNumber;

   BFFieldId idFundCode = ifds::FundCode;
   BFFieldId idClassCode = ifds::ClassCode;
   if( idField == ifds::ToFundNumber )
   {
      idFundCode = ifds::FundToCode;
      idClassCode = ifds::ClassToCode;
   }

   getField( idField, dstrFundNumber, idDataGroup, false );

   if( dstrFundNumber.strip() != NULL_STRING )
   {
      DString dstrFundCode,dstrClassCode;
      if( getWorkSession().GetFundClassCode(dstrFundNumber,dstrFundCode,
                                            dstrClassCode) )
      {
         DString oldFundCode,oldClassCode;
         getField(idFundCode,oldFundCode,idDataGroup,false);
         getField(idClassCode,oldClassCode,idDataGroup,false);
         if( oldFundCode != dstrFundCode )
         {
            setField(idFundCode, dstrFundCode, idDataGroup, false, true);
         }
         if( oldClassCode != dstrClassCode )
         {
            setField(idClassCode, dstrClassCode, idDataGroup, false, true);
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
void AccountDistribution::setFundNumber(const BFFieldId& idField,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundNumber" ) )
   DString dstrFundNumber, dstrFundCode,dstrClassCode;

   BFFieldId idFundCode = ifds::FundToCode;
   BFFieldId idClassCode = ifds::ClassToCode;
   BFFieldId idFundNumber = ifds::ToFundNumber;
   if( idField == ifds::FundCode || idField == ifds::ClassCode )
   {
      idFundCode = ifds::FundCode;
      idClassCode = ifds::ClassCode;
      idFundNumber = ifds::FrFundNumber;
   }

   getField(idFundCode,dstrFundCode,idDataGroup,false);
   getField(idClassCode,dstrClassCode,idDataGroup,false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   if( !dstrFundCode.empty() && !dstrClassCode.empty() )
   {

      if( _pFundDetailList )
      {
         _pFundDetailList->getField( dstrFundCode, dstrClassCode, ifds::Baycom, dstrFundNumber,idDataGroup, true); 
      }
      else
      {
         getWorkSession().GetFundNumber( dstrFundCode,  dstrClassCode, dstrFundNumber );
      }

      DString oldFundNumber;  
      getField(idFundNumber,oldFundNumber,idDataGroup,false);
      if( oldFundNumber.strip() != dstrFundNumber )

         setFieldNoValidate( idFundNumber, dstrFundNumber, idDataGroup,false,true,true );
   }
}

//*******************************************************************************************
SEVERITY AccountDistribution::isToFundClassAllowed( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isToFundClassAllowed" ) );

   DString dstrFundFrom, 
      dstrClassFrom, 
      dstrFundTo, 
      dstrClassTo;

   getField (ifds::FundCode, dstrFundFrom, idDataGroup);
   getField (ifds::ClassCode, dstrClassFrom, idDataGroup);
   
   if (idField == ifds::FundToCode)
      dstrFundTo = strValue;
   else
      getField (ifds::FundToCode, dstrFundTo, idDataGroup);
   
   if (idField == ifds::ClassToCode)
      dstrClassTo = strValue;
   else 
      getField (ifds::ClassToCode, dstrClassTo, idDataGroup);

   if ( dstrFundFrom.empty() || 
        dstrClassFrom.empty() ||
        dstrFundTo.empty() || 
        dstrClassTo.empty() )
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrDistribFundsValidate;

   getWorkSession().getOption (ifds::DistribFundsValidate, dstrDistribFundsValidate, idDataGroup, false);
   
   dstrDistribFundsValidate.strip().upperCase();   
   if (dstrDistribFundsValidate == YES)
   {
         bool bAllowTransfer = false;
         FundToList  fundToList(*this);
         bAllowTransfer = fundToList.isTransferAllowed( dstrFundFrom,
                                                        dstrClassFrom, 
                                                        dstrFundTo, 
                                                        dstrClassTo);
         if (!bAllowTransfer)
         {
            DString idiStr;
            addIDITagValue( idiStr, FUND, dstrFundFrom );
            addIDITagValue( idiStr, CLASS, dstrClassFrom );
            addIDITagValue( idiStr, TO_FUND, dstrFundTo );
            addIDITagValue( idiStr, TO_CLASS, dstrClassTo );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_XFER_NOT_ALLOWED, idiStr);
         }
  }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
SEVERITY AccountDistribution::canTradeFundClass( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canTradeFundClass" ) );
   DString dstrFundCode, dstrClassCode, dstrEffectiveDate;
   getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );   
   getField ( ifds::FundToCode, dstrFundCode, idDataGroup );
   getField ( ifds::ClassToCode, dstrClassCode, idDataGroup );   
   if ( ( dstrFundCode != CASH ) && !(( dstrFundCode == NULL_STRING ) || ( dstrClassCode == NULL_STRING ))) 
   {      _pMFAccount->canTradeFundClass (dstrFundCode,dstrClassCode, EX_FER_IN_CODE, dstrEffectiveDate,idDataGroup );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountDistribution::getBankInstructionsList(
   DistributionBankInstructionsList *&pDistributionBankInstructionsList, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));

   //check whether PayType is EFT, only in this case we have banking
   if (isBankingAllowed(idDataGroup))
   {
      BFObjectKey objKey(I_("Distribution_BankInstructionsList"), idDataGroup, 
         OBJ_ACTIVITY_NONE, OBJ_TYPE_NONE);

      pDistributionBankInstructionsList = NULL;
	  pDistributionBankInstructionsList = dynamic_cast<DistributionBankInstructionsList *>(findObject(objKey));	

      if (!pDistributionBankInstructionsList && bCreate)
      {
         pDistributionBankInstructionsList = new DistributionBankInstructionsList(*this);
         if (pDistributionBankInstructionsList)
         {
            SEVERITY severity = isNew() ? 
               pDistributionBankInstructionsList->initNew(_dstrAccountNum, idDataGroup) : 
               pDistributionBankInstructionsList->init(_dstrAccountNum, idDataGroup);

            if (severity <= WARNING)
            {
               setObject(objKey, pDistributionBankInstructionsList);
            }
            else
            {
               delete pDistributionBankInstructionsList;
               pDistributionBankInstructionsList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//deal with the file processor
//******************************************************************************
SEVERITY AccountDistribution::fileProcessorRelatedChanges (const BFDataGroupId &idDataGroup,
                                                           bool forceLoad /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("fileProcessorRelatedChanges"));
   DString achDividend,
      payType;

   getField (ifds::DistributionPayType, payType, idDataGroup, false);
   payType.strip().upperCase();
   getWorkSession().getOption (ifds::ACHDividend, achDividend, BF::HOST, false);
   if (achDividend == YES && payType == EFT)
   {
      //dynamically, load subst list for ACHProcessor
      DynamicSubListHolder* pDynamicSubListHolder = 
        getMgmtCo ().getDynamicSubListHolder ();

      assert (pDynamicSubListHolder);

      DString payMethod,
         transType,
         currency,
         substList;

      getField (ifds::PayMethod, payMethod, idDataGroup, false);
      payMethod.strip();
      getField (ifds::TransType, transType, idDataGroup, false);
      transType.strip ();
      getField (ifds::Currency, currency, idDataGroup, false);
      currency.strip();
      substList = pDynamicSubListHolder->
         getFileProcSubList (transType, payMethod, currency);
      setFieldAllSubstituteValues (ifds::ACHProcessor, idDataGroup, substList);
      //have to force validation, because substitute values have changed
      setFieldRequired (ifds::ACHProcessor, idDataGroup, !substList.empty());
      setValidFlag (ifds::ACHProcessor, idDataGroup, substList.empty());
      if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      {
        setFieldNoValidate(ifds::ACHProcessor, substList.substr(0,substList.find('=')), idDataGroup, false, true, true);
      }
   }
   else
   {
      setFieldRequired (ifds::ACHProcessor, idDataGroup, false);
      setValidFlag (ifds::ACHProcessor, idDataGroup, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::setCurrencySubstSet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setCurrencySubst"));

   DString multiCurrency,
      achDividend;

   getWorkSession().getOption (ifds::ACHDividend, achDividend, BF::HOST, false);
   getWorkSession().getOption (ifds::MultiCurrency, multiCurrency, BF::HOST);
   if (/*multiCurrency == YES &&*/ achDividend == YES)
   {
      DynamicSubListHolder* pDynamicSubListHolder = 
         getMgmtCo().getDynamicSubListHolder();

      assert(pDynamicSubListHolder);

      DString transType,
         payMethod,
         fileProcessor,
         substList;

      getField (ifds::TransType, transType, idDataGroup, false);
      transType.strip ();
      getField (ifds::PayMethod, payMethod, idDataGroup, false);
      payMethod.strip();
      getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
      fileProcessor.strip();
      if (fileProcessor != NULL_STRING)
      {
         substList = pDynamicSubListHolder->getCurrencySubList (transType, 
            payMethod, fileProcessor);
      }
      else
      {
         substList = pDynamicSubListHolder->getCurrencySubList (transType, 
            payMethod);
      }
      if (substList.empty())
      {
         substList = strCurrencySubstList;
      }
      setFieldAllSubstituteValues (ifds::Currency, idDataGroup, substList);
      //have to force validation, because substitute values have changed
      setValidFlag (ifds::Currency, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::setPayTypeSubstSet ( const BFDataGroupId &idDataGroup, 
                                                   const DString &dstrTransType, 
                                                   const DString &dstrFundCode, 
                                                   const DString &dstrClassCode )
{

   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("AccountDistribution"));
   bool bNSCCCompliant = isNSCCCompliant (idDataGroup, dstrFundCode, dstrClassCode);
   bool bHasPayInstructionsForDistribution = hasPayInstructionsForDistribution (idDataGroup);

   DString dstrAccountTaxType;
   _pMFAccount->getField(ifds::TaxType, dstrAccountTaxType, idDataGroup, false);

   if (dstrTransType.empty())
   {
//Account Level
      if (bNSCCCompliant)
      {
         setFieldSubstituteValues( ifds::DistributionPayType, idDataGroup, ifds::NSCCDummyDistributionPayType );   		
         if (isNew ()) //Incident - 711561
            setFieldNoValidate (ifds::DistributionPayType, I_("N"), idDataGroup, false, true,false, false);

         //setFieldReadOnly (ifds::DistributionPayType, idDataGroup, isNSCDividend != YES);
      }
      else
      {
         setFieldSubstituteValues (ifds::DistributionPayType, idDataGroup, ifds::DummyDistributionPayType);


         if(dstrAccountTaxType == TAX_TYPE_OA || dstrAccountTaxType == TAX_TYPE_SA || dstrAccountTaxType == TAX_TYPE_SRS)
         {
            setFieldReadOnly (ifds::DistributionPayType, idDataGroup, true);
         }
         else
         {
            setFieldReadOnly (ifds::DistributionPayType, idDataGroup, false);
         }

         if (bHasPayInstructionsForDistribution)
         {
            if (isNew ())
               setFieldNoValidate (ifds::DistributionPayType, I_("P"), idDataGroup, false, true,false, false);
            setFieldReadOnly (ifds::DistributionPayType, idDataGroup, true);
         }
      }
   }
   else
   {
      if (bNSCCCompliant)
      {
         if (dstrTransType == MFR)
         {
            setFieldSubstituteValues (ifds::DistributionPayType, idDataGroup, ifds::NSCCMFRDistributionPay);
         }
         else if (dstrTransType == INCOME_DISTRIBUTION)
         {
            setFieldSubstituteValues (ifds::DistributionPayType, idDataGroup, ifds::NSCCDummyDistributionPayType);
            if (isNew ()) //Incident - 711561
               setFieldNoValidate (ifds::DistributionPayType, I_("N"), idDataGroup, false, true,false, false);

            //setFieldReadOnly (ifds::DistributionPayType, idDataGroup, isNSCDividend != YES);
         }
      }
      else
      {
         if (dstrTransType == MFR)
         {
            setFieldSubstituteValues (ifds::DistributionPayType, idDataGroup, ifds::MFRDistributionPay);
         }
         else if (dstrTransType == INCOME_DISTRIBUTION)
         {
            setFieldSubstituteValues (ifds::DistributionPayType, idDataGroup, ifds::DummyDistributionPayType);
            if(dstrAccountTaxType == TAX_TYPE_OA || dstrAccountTaxType == TAX_TYPE_SA || dstrAccountTaxType == TAX_TYPE_SRS)
            {
               setFieldReadOnly (ifds::DistributionPayType, idDataGroup, true);
            }
            else
            {
               setFieldReadOnly (ifds::DistributionPayType, idDataGroup, false);
            }


            if (bHasPayInstructionsForDistribution)
            {
               DString strFundToCode;
               getField( ifds::FundToCode, strFundToCode, idDataGroup, false );
               strFundToCode.strip().upperCase();

               if ( strFundToCode == CASH )
               {
                  // paytype 'P' (redirect to pay entity) is only avialable when
                  // fund to code is 'cash' and account is under broker whose
                  // broker's pay instruct and broker pay entity bank is available
                  setFieldNoValidate (ifds::DistributionPayType, I_("P"), idDataGroup, false, false,false, false);
                  setFieldReadOnly (ifds::DistributionPayType, idDataGroup, true);
               }

               setUpdatedFlag ( ifds::PayTypeMethod, idDataGroup, false );
               setUpdatedFlag ( ifds::PayTypeMethodCurrOpt, idDataGroup, false );
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::setPayMethodSubstSet (const BFDataGroupId &idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setPayMethodSubstSet"));

  DString achDividend;

  getWorkSession().getOption (ifds::ACHDividend, achDividend, BF::HOST, false);

  if(achDividend == YES)
  {
    DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
    assert(pDynamicSubListHolder);

    DString transType, currency, fileProcessor, substList;

    getField(ifds::TransType, transType, idDataGroup, false);
    transType.strip ();
    getField(ifds::Currency, currency, idDataGroup, false);
    currency.strip();
    getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
    fileProcessor.strip();

    if (currency != NULL_STRING)
    {
      substList = pDynamicSubListHolder->getPayMethodSubList(transType, fileProcessor, currency);
    }
    else
    {
      substList = pDynamicSubListHolder->getPayMethodSubList(transType, fileProcessor);
    }
    setFieldAllSubstituteValues(ifds::PayMethod, idDataGroup, substList);
    //have to force validation, because substitute values have changed
    setValidFlag(ifds::Currency, idDataGroup, false);
  }
  return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::setPayTypeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("AccountDistribution"));

   if (_level == FUND_CLASS_LEVEL)
   {
      DString fundToCode,
         payTypeDefaultValue (NULL_STRING);

      getField (ifds::FundToCode, fundToCode, idDataGroup, false);
      fundToCode.strip().upperCase();
      if (fundToCode == CASH)
      {
         getTradeDefault (ifds::TradePayTypeDefault, payTypeDefaultValue, idDataGroup);
         if (isNSCCCompliant (idDataGroup))
         {
            if (isNew ()) //Incident - 711561
               payTypeDefaultValue = I_("N"); //NSCC

            //setFieldReadOnly (ifds::DistributionPayType, idDataGroup, isNSCDividend != YES);
         }
         else if (hasPayInstructionsForDistribution (idDataGroup))
         {
            if (isNew())
            {
               payTypeDefaultValue = I_("P"); //Pay to entity
               setFieldReadOnly (ifds::DistributionPayType, idDataGroup, true);
            }
         }
      }

      DString dstrAccountTaxType;
      _pMFAccount->getField(ifds::TaxType, dstrAccountTaxType, idDataGroup, false);

      if(dstrAccountTaxType == TAX_TYPE_OA || dstrAccountTaxType == TAX_TYPE_SA || dstrAccountTaxType == TAX_TYPE_SRS)
      {
         payTypeDefaultValue = I_("RA");
         setFieldReadOnly (ifds::DistributionPayType, idDataGroup, true);
      }


      setFieldNoValidate ( ifds::DistributionPayType, payTypeDefaultValue, idDataGroup, 
                           false, false, false, false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::getTradeDefault ( const BFFieldId &genControlDefaultFieldId, 
                                                DString &defaultValue, 
                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getTradeDefault"));
   DString transType,
      transTypeList,
      defaultList;

   getField (ifds::TransType, transType, idDataGroup, false);
   defaultValue = NULL_STRING;
   getWorkSession().getOption ( ifds::TransTypeDefault, 
                                transTypeList, 
                                BF::HOST, 
                                false);
   getWorkSession().getOption ( genControlDefaultFieldId, 
                                defaultList, 
                                BF::HOST, 
                                false);

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
bool AccountDistribution::isNSCCCompliant ( const BFDataGroupId &idDataGroup, 
                                            const DString &dstrFundCode, 
                                            const DString &dstrClassCode)
{

   DString dstrNSCCCompliant, 
      fromFundCode, 
      fromClassCode;
   bool bNSCCCompliant = false;
   
   if (getWorkSession().getOption (ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false) <= WARNING &&
       _pMFAccount)
   {
      DString dstrBrokerCode;
      DString isNSCDividend;

      _pMFAccount->getField (ifds::IsNSCDividend, isNSCDividend, idDataGroup, false );
      _pMFAccount->getField (ifds::BrokerCode, dstrBrokerCode, idDataGroup, false );

      if ( dstrNSCCCompliant == YES && isNSCDividend == YES &&
           _pMFAccount->isBrokerNSCCCompliant (dstrBrokerCode, idDataGroup) &&
           _pMFAccount->isBrokerFileTypeD (idDataGroup))
      {
         if (_pFundDetailList)
         {
            if (dstrFundCode == NULL_STRING)
            {
               getField (ifds::FundCode, fromFundCode, idDataGroup, false);
               getField (ifds::ClassCode, fromClassCode, idDataGroup, false);
            }
            else 
            {
               fromFundCode = dstrFundCode;
               fromClassCode = dstrClassCode;
            }
            if( !fromFundCode.empty() && !fromClassCode.empty() )
            {
               FundDetail *pFundDetail = NULL;
               if (_pFundDetailList->getFundDetail (fromFundCode, fromClassCode, idDataGroup, pFundDetail))
               {
                  DString dstrfundNSCCCompliant;

                  pFundDetail->getField (ifds::NSCCCompliant, dstrfundNSCCCompliant, idDataGroup, false);
                  bNSCCCompliant = dstrfundNSCCCompliant.strip().upperCase() == YES;
               }
            }
         }
      }
   }
   return bNSCCCompliant; 
}

//******************************************************************************
SEVERITY AccountDistribution::getPayInstructList ( TradePayInstructList *&pTradePayInstructList, 
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getPayInstructList"));
   SEVERITY severity = NO_CONDITION;
   DString paymentFor (PAYMENT_FOR::DISTRIBUTION),
      strKey (I_("PayInstructList_")),
      payToEntity,
      broker,
      branch,
      slsrep;

   if (_pMFAccount)
   {
      if ( _pMFAccount->getPayToEntity (payToEntity, idDataGroup) <= WARNING &&
           !payToEntity.empty ())
      {
         if (payToEntity == PAY_TO::BROKER)
         {
            _pMFAccount->getField (ifds::BrokerCode, broker, idDataGroup);
         }
         else if (payToEntity == PAY_TO::BRANCH)
         {
            _pMFAccount->getField (ifds::BrokerCode, broker, idDataGroup);
            _pMFAccount->getField (ifds::BranchCode, branch, idDataGroup);
         }
         else if (payToEntity == PAY_TO::SALESREP)
         {
            _pMFAccount->getField (ifds::BrokerCode, broker, idDataGroup);
            _pMFAccount->getField (ifds::BranchCode, branch, idDataGroup);
            _pMFAccount->getField (ifds::Slsrep, slsrep, idDataGroup);
         }
         strKey += I_("Broker=") + broker +
                  I_(";Branch=") + branch +
                  I_(";SalesRep=") + slsrep;
      }
      pTradePayInstructList = 
         dynamic_cast <TradePayInstructList *> (getObject (strKey, idDataGroup));
      if (!payToEntity.empty ())
      {
         if (!pTradePayInstructList)
         {
            pTradePayInstructList = new TradePayInstructList (*this);
            if ( (payToEntity == PAY_TO::BROKER   && !broker.empty()) ||
                 (payToEntity == PAY_TO::BRANCH   && !broker.empty() && !branch.empty()) ||
                 (payToEntity == PAY_TO::SALESREP && !broker.empty() && !branch.empty() && !slsrep.empty()))
            {
               severity = pTradePayInstructList->init ( payToEntity,
                                                        broker, 
                                                        branch,
                                                        slsrep,
                                                        _currentBusinessDate,
                                                        paymentFor,
                                                        idDataGroup);
            }
            else //this is not valid
            {
               assert (0);
            }

            if (severity <= WARNING && pTradePayInstructList)
            {
               setObject ( pTradePayInstructList, 
                           strKey, 
                           OBJ_ACTIVITY_NONE, 
                           idDataGroup);
            }
            else
            {
               delete pTradePayInstructList;
               pTradePayInstructList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AccountDistribution::hasPayInstructionsForDistribution (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("hasPayInstructionsForDistribution"));

   bool bHasPayInstructionsForDistribution (false);
   
   TradePayInstructList *pTradePayInstructList (NULL);
   
   if ( getPayInstructList (pTradePayInstructList, idDataGroup) <= WARNING && 
        pTradePayInstructList)
   {
      BFObjIter bfIter (*pTradePayInstructList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

      bHasPayInstructionsForDistribution = bfIter.getNumberOfItemsInList () == 1;
   }
   return bHasPayInstructionsForDistribution;
}

//******************************************************************************
SEVERITY AccountDistribution::validateFromFundClass( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromFundClass"));

   DString strDistribType, strFund, strClass;
   getField( ifds::TransType, strDistribType, idDataGroup );
   getField( ifds::FundCode,  strFund, idDataGroup );
   getField( ifds::ClassCode, strClass, idDataGroup );

   FundClassDistribOptionsList * pFundClassDistribOptionsList = NULL;
   FundClassDistribOptions * pFundClassDistribOptions = NULL;
   if( getFundClassDistribOptionsList(strDistribType, strFund, strClass, idDataGroup, pFundClassDistribOptionsList ) <= WARNING )
   {
      if( pFundClassDistribOptionsList && pFundClassDistribOptionsList->getFundClassDistribOptions( strDistribType, idDataGroup, pFundClassDistribOptions ) <= WARNING )
      {
         if( pFundClassDistribOptions == NULL )
         {
            DString strIDI;
            getField( ifds::TransType, strDistribType, idDataGroup, true );
            addIDITagValue (strIDI, I_("DISTRIB_TYPE"), strDistribType );
            ADDCONDITIONFROMFILEIDI (CND::ERR_FUND_CLASS_NOT_SUPPORTED_FOR_DISTRIB_TYPE,strIDI);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::validateToFundClass( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));

   DString strDistribType, 
      strFund, 
      strClass, 
      strFundTo, 
      strClassTo;
   bool bCheckAllowableTransfers = true;

   getField (ifds::TransType,  strDistribType, idDataGroup);
   getField (ifds::FundCode,   strFund,        idDataGroup);
   getField (ifds::ClassCode,  strClass,       idDataGroup);
   getField (ifds::FundToCode, strFundTo,      idDataGroup);
   getField (ifds::ClassToCode,strClassTo,     idDataGroup);

   FundClassDistribOptionsList *pFundClassDistribOptionsList = NULL;
   if (getFundClassDistribOptionsList ( strDistribType, 
                                        strFund, 
                                        strClass, 
                                        idDataGroup, 
                                        pFundClassDistribOptionsList) <= WARNING)
   {
      FundClassDistribOptions *pFundClassDistribOptions = NULL;

      if ( pFundClassDistribOptionsList && 
           pFundClassDistribOptionsList->getFundClassDistribOptions ( strDistribType, 
                                                                      idDataGroup, 
                                                                      pFundClassDistribOptions) <= WARNING &&
           pFundClassDistribOptions)
      {
         if (IsFundToCodeCash (idDataGroup))
         {
            bCheckAllowableTransfers = false;
            if (!pFundClassDistribOptions->isCashAllowed (idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::ERR_CASH_DISTRIB_NOT_ALLOWED_FOR_FROM_FUND_CLASS);
            }
          }
         else if (strFundTo.strip() == strFund.strip() && strClassTo.strip() == strClass.strip())
         {
            if (!pFundClassDistribOptions->isReinvestmentAllowed (idDataGroup ))
            {
               ADDCONDITIONFROMFILE (CND::ERR_REINVESTMENT_NOT_ALLOWED);
               bCheckAllowableTransfers = false;
            }
         }
         else
         {
            if (!pFundClassDistribOptions->isRedistributionAllowed (idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::ERR_REDIRECTING_NOT_ALLOWED);
               bCheckAllowableTransfers = false;
            }
         }
      }
   }
   if (bCheckAllowableTransfers)
   {
      DString distribChkAllowTfr;

      getWorkSession ().getOption ( ifds::DistribChkAllowTfr, 
                                    distribChkAllowTfr, 
                                    BF::HOST, 
                                    false);

      if ( distribChkAllowTfr == Y && 
            !strFund.empty () && 
            !strClass.empty () && 
            !strFundTo.empty () && 
            !strClassTo.empty() )
      {
         bool bTransferAllowed;
         FundToList fundToList (*this );
         DString allowFullPartial;

         bTransferAllowed = fundToList.isTransferAllowed ( strFund, 
                                                           strClass, 
                                                           strFundTo, 
                                                           strClassTo, 
                                                           allowFullPartial);
         if (!bTransferAllowed)
         {
            DString idiStr;

            addIDITagValue (idiStr, I_("FUND"), strFund);
            addIDITagValue (idiStr, I_("CLASS"), strClass);
            addIDITagValue (idiStr, I_("TO_FUND"), strFundTo);
            addIDITagValue (idiStr, I_("TO_CLASS"), strClassTo);
            ADDCONDITIONFROMFILEIDI (CND::ERR_FUND_CLASS_XFER_NOT_ALLOWED, idiStr);
         }
      }
   }

   MFAccount *pMFAccount = NULL;
   if (!IsFundToCodeCash(idDataGroup) && 
       getWorkSession().getMFAccount(idDataGroup, _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
   {
       pMFAccount->validateToFundClassAgainstFundEligible(strFundTo, strClassTo, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY AccountDistribution::validateToSoftCapCheck(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateToSoftCapCheck"));

    DString accountTo, toFund, toClass, tradeDate; 
    getField (ifds::FundToCode, toFund, idDataGroup, false);
    getField (ifds::ClassToCode, toClass, idDataGroup, false);
    getField (ifds::EffectiveDate, tradeDate, idDataGroup, false); 

    getWorkSession().fundClassSoftCappedCheck(_dstrAccountNum, toFund, toClass, I_("DD"), tradeDate, idDataGroup);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::getFundClassDistribOptionsList( const DString &distributionType, 
                                                              const DString &fundCode, 
                                                              const DString &classCode,
                                                              const BFDataGroupId &idDataGroup,
                                                              FundClassDistribOptionsList *&pFundClassDistribOptionsList)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFundClassDistribOptionsList"));

   pFundClassDistribOptionsList = NULL;

   if ( !distributionType.empty() &&
        !fundCode.empty() &&
        !classCode.empty())
   {
      DString strKey = I_("FundClassDistribOptionsList_") + distributionType + 
                       I_("_") + fundCode + I_("_") + classCode;	

      pFundClassDistribOptionsList = dynamic_cast<FundClassDistribOptionsList*> (getObject (strKey, idDataGroup));
      if (!pFundClassDistribOptionsList)
      {
         pFundClassDistribOptionsList = new FundClassDistribOptionsList (*this);
         if (pFundClassDistribOptionsList->init (distributionType, fundCode, classCode ) > WARNING)
         {
            delete pFundClassDistribOptionsList;
            pFundClassDistribOptionsList = NULL;
         }
         else
         {
            setObject (pFundClassDistribOptionsList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AccountDistribution::isAllFundsMode( const BFDataGroupId &idDataGroup )
{
   DString strAllFundsMode;
   getField (ifds::AllFundsDistrib, strAllFundsMode, idDataGroup, false );
   return strAllFundsMode.strip() == I_( "Y" );
}

//******************************************************************************
SEVERITY AccountDistribution::validateAllFundsDistrib( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAllFundsDistrib"));

	if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
	{
		if ( _pMFAccount && isAllFundsMode( idDataGroup ) && isConsolIDGCOn() )
		{
			//Feb.6,2008 new requirement:
			//i) a user creates account level distribution instructions with Pay Type EFT to Account, and
			//ii)Distribution bulking is NOT turned on at the account level.  So the Distribution Consolidation Type field is either ‘blank’ or populated with option ‘Individual Payment’(as of today).
			DString payType = NULL_STRING;
			if( _pSplitList )
			{
				BFObjIter iter( *_pSplitList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
				if( !iter.end() )
				{
					//always look only at the first one
					iter.getObject()->getField( ifds::DistributionPayType, payType, idDataGroup, false );
				}
			}
			
			if (payType.strip().upperCase() == EFT)
			{
				DString strConsolTypeID;
				_pMFAccount->getField (ifds::ConsolTypeID, strConsolTypeID, idDataGroup, false );
				if( strConsolTypeID.strip() != I_( "1" ) &&//bulking
					strConsolTypeID.strip() != I_( "2" ) &&//netting
					strConsolTypeID.strip() != I_( "99" ) )//use broker payment instruction
				{
				   ADDCONDITIONFROMFILE( CND::WARN_DISTRIBUTION_BULKING_BENEFICIAL );
				}
			}
        }
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

bool AccountDistribution::isConsolIDGCOn()
{
   bool bRetVal = false;  

   if( _pMFAccount )
   {
      DString dstrConsolidation, dstrConsolDefault;
      DString dstrConsType = I_( "ID" );
      _pMFAccount->getDefaultConsolType( dstrConsType, dstrConsolidation, dstrConsolDefault, BF::HOST );
      if( dstrConsolidation.strip().upperCase() == I_( "Y" ) )
      {
         bRetVal = true;
      }
   }

   return bRetVal;
}

//******************************************************************************

SEVERITY AccountDistribution::validateAcctDistribOpt( const DString& dstrValue, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                        CLASSNAME, 
                        I_("validateAcctDistribOpt"));

   DString strValue(dstrValue);

   if( strValue.strip().empty() &&
      isAllFundsMode(idDataGroup) )
   {
      //for  account level distributions, this field should have a value
      ADDCONDITIONFROMFILE(CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AccountDistribution::validateAcctDistribCurrencyOpt( const DString& dstrValue, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAcctDistribCurrencyOpt"));

   DString strValue(dstrValue);

   if( strValue.strip().empty() &&
      isAllFundsMode(idDataGroup) )
   {
      DString strAcctDistribOpt;
      getField( ifds::AcctDistribOpt, strAcctDistribOpt, idDataGroup, false);
      if( strAcctDistribOpt.strip() == CASH_ACCT_LEVEL )
      {
         //for cash account level distributions, this field should have a value
         ADDCONDITIONFROMFILE(CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AccountDistribution::acctDistribOptRelChanges( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("acctDistribOptRelChanges"));

   DString strAcctDistribOpt;
   getField( ifds::AcctDistribOpt, strAcctDistribOpt, idDataGroup, false );
   DString dstrAccountTaxType;
   _pMFAccount->getField(ifds::TaxType, dstrAccountTaxType, idDataGroup, false);

   if( isAllFundsMode( idDataGroup ) )
   {
      if( strAcctDistribOpt.strip() == CASH_ACCT_LEVEL )
      {
         //1. make sure that AcctDistribCurrencyOpt Fund Currency and that it is updateable
         if(dstrAccountTaxType == TAX_TYPE_OA || dstrAccountTaxType == TAX_TYPE_SA || dstrAccountTaxType == TAX_TYPE_SRS)
         {
            setFieldNoValidate( ifds::AcctDistribCurrencyOption, PREFERRED_CURRECNY, idDataGroup, false,true,true);
            setFieldReadOnly ( ifds::AcctDistribCurrencyOption, idDataGroup, true );
         }
         else
         {
            setFieldNoValidate( ifds::AcctDistribCurrencyOption, FUND_CURRENCY, idDataGroup, false,true,true);
            setFieldReadOnly( ifds::AcctDistribCurrencyOption, idDataGroup, false );
         }
         //2. set FundTo to CASH and ClassTo to A
         setFieldNoValidate( ifds::FundToCode, CASH, idDataGroup, false,true,true);
         setFieldNoValidate( ifds::ClassToCode, I_("A"), idDataGroup, false,true,true);
         //3. set FundTo to CASH and ClassTo and ToFundNumber as read only
         setFieldReadOnly( ifds::FundToCode, idDataGroup, true );
         setFieldReadOnly( ifds::ClassToCode, idDataGroup, true );
         setFieldReadOnly( ifds::ToFundNumber, idDataGroup, true );
      }
      else
      {
         if(dstrAccountTaxType != TAX_TYPE_OA && dstrAccountTaxType != TAX_TYPE_SA  && dstrAccountTaxType != TAX_TYPE_SRS)
         {
            //1. make sure that AcctDistribCurrencyOpt is blanked out
            setFieldNoValidate( ifds::AcctDistribCurrencyOption, NULL_STRING, idDataGroup, false,true,true);
            //2. make sure that AcctDistribCurrencyOpt is read-only
            setFieldReadOnly( ifds::AcctDistribCurrencyOption, idDataGroup, true );	
         }
         //3. blank out FundTo, ClassTo & ToFundNumber
         setFieldNoValidate( ifds::FundToCode, NULL_STRING, idDataGroup, false,true,true);
         setFieldNoValidate( ifds::ClassToCode, NULL_STRING, idDataGroup, false,true,true);
         setFieldNoValidate( ifds::ToFundNumber, NULL_STRING, idDataGroup, false,true,true);			

         //4. make sure that bank info is not required
         clearBankingFields( idDataGroup );
         if( _level == FUND_CLASS_LEVEL )
         {
            setFieldRequired (ifds::BankIdValue, idDataGroup, false);
            setFieldRequired (ifds::BankAcctType, idDataGroup, false);
            setFieldRequired (ifds::BankAcctNum, idDataGroup, false); 
            setValidFlag(ifds::BankIdValue, idDataGroup, false);
            setValidFlag(ifds::BankAcctType, idDataGroup, false);
            setValidFlag(ifds::BankAcctNum, idDataGroup, false);
            fileProcessorRelatedChanges (idDataGroup); 
         }

         //5. if Reinvest set FundTo and ClassTo and ToFundNumber as read only
         if( strAcctDistribOpt == REINVEST )
         {
            setFieldReadOnly( ifds::FundToCode, idDataGroup, true );
            setFieldReadOnly( ifds::ClassToCode, idDataGroup, true );
            setFieldReadOnly( ifds::ToFundNumber, idDataGroup, true );
            //6. make sure that FundToCode & ClassToCode are not required
            setFieldRequired( ifds::FundToCode, idDataGroup, false );
            setFieldRequired( ifds::ClassToCode, idDataGroup, false );
            setFieldRequired (ifds::ACHProcessor, idDataGroup, false);
         }
         else//7. else (if redirect)set FundTo, ClassTo and ToFundNumber as updateable and required
         {
            setFieldReadOnly( ifds::FundToCode, idDataGroup, false );
            setFieldReadOnly( ifds::ClassToCode, idDataGroup, false );
            setFieldReadOnly( ifds::ToFundNumber, idDataGroup, false );
            if( _level == FUND_CLASS_LEVEL )
            {
               setFieldRequired( ifds::FundToCode, idDataGroup, true );
               setFieldRequired( ifds::ClassToCode, idDataGroup, true );
               setValidFlag(ifds::FundToCode, idDataGroup, false);
               setValidFlag(ifds::ClassToCode, idDataGroup, false);
               setFieldRequired (ifds::ACHProcessor, idDataGroup, false);
            }
         }

      }
   }
   else
   {
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AccountDistribution::acctDistribCurrencyOptRelChanges( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("acctDistribCurrencyOptRelChanges"));

   DString strAcctDistribCurrOpt;
   getField( ifds::AcctDistribCurrencyOption, strAcctDistribCurrOpt, idDataGroup, false );
   if( isAllFundsMode( idDataGroup ) )
   {
      if( strAcctDistribCurrOpt.strip() == FUND_CURRENCY )
      {
         //if payment in fund currency, blank out the currency, make it read-only and not required
         setFieldNoValidate( ifds::Currency, NULL_STRING, idDataGroup, false,true,true);
         setFieldReadOnly( ifds::Currency, idDataGroup, true );
         setFieldRequired( ifds::Currency, idDataGroup, false );
         //also blank out banking info, make it read-only and make banking info NOT required
         clearBankingFields( idDataGroup );
         setFieldRequired (ifds::BankIdValue, idDataGroup, false);
         setFieldRequired (ifds::BankAcctType, idDataGroup, false);
         setFieldRequired (ifds::BankAcctNum, idDataGroup, false);
         setFieldReadOnly( ifds::InstName, idDataGroup, true );
         setFieldReadOnly( ifds::BankIdValue, idDataGroup, true );
         setFieldReadOnly( ifds::BankAcctType, idDataGroup, true );
         setFieldReadOnly( ifds::BankAcctNum, idDataGroup, true );
      }
      else
      {
         if( _level == FUND_CLASS_LEVEL )
         {  //1. make sure the Currency field is updateable and required
            setFieldReadOnly( ifds::Currency, idDataGroup, false );
            setFieldRequired( ifds::Currency, idDataGroup, true );
            setValidFlag( ifds::Currency, idDataGroup, false );
            //2. if EFT paytype, banking is mandatory
            DString strPayType;
            getField( ifds::DistributionPayType, strPayType, idDataGroup, false );
            if( strPayType.strip().upperCase() == EFT )
            {
               setFieldRequired (ifds::BankIdValue, idDataGroup, true);
               //setFieldRequired (ifds::BankAcctType, idDataGroup, true);
               setFieldRequired (ifds::BankAcctNum, idDataGroup, true); 
               setValidFlag( ifds::BankIdValue, idDataGroup, false );
               //setValidFlag( ifds::BankAcctType, idDataGroup, false );
               setValidFlag( ifds::BankAcctNum, idDataGroup, false );
            }
         }
      }
       //make sure that if CASH, FundToCode, ClassToCode and ToFundNumber are read-only
      DString strAcctDistribOpt;
      getField( ifds::AcctDistribOpt, strAcctDistribOpt, idDataGroup, false );
      if( strAcctDistribOpt.strip() == CASH_ACCT_LEVEL )
      {
         //set FundTo, ClassTo and ToFundNumber as read only
         setFieldReadOnly( ifds::FundToCode, idDataGroup, true );
         setFieldReadOnly( ifds::ClassToCode, idDataGroup, true );
         setFieldReadOnly( ifds::ToFundNumber, idDataGroup, true );
      }
   }
   else
   {
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AccountDistribution::acctLvlDistrInit( const DString& strAcctDistribOpt, 
                                                const DString& strAcctDistribCurrOpt,
                                                const BFDataGroupId &idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("acctLvlDistrInit"));

   setFieldNoValidate( ifds::AllFundsDistrib, I_( "Y" ), idDataGroup , false, true, true, false );
   setFieldRequired( ifds::FundCode, idDataGroup, false );
   setFieldRequired( ifds::ClassCode, idDataGroup, false );
   setFieldReadOnly ( ifds::FrFundNumber, idDataGroup, true );
   setFieldReadOnly ( ifds::FundCode, idDataGroup, true );
   setFieldReadOnly ( ifds::ClassCode, idDataGroup, true );
   setFieldNoValidate( ifds::FrFundNumber, NULL_STRING, idDataGroup, false,true,true);
   setFieldNoValidate( ifds::FundCode, NULL_STRING, idDataGroup, false,true,true);
   setFieldNoValidate( ifds::ClassCode, NULL_STRING, idDataGroup, false,true,true);
   setFieldReadOnly( ifds::AcctDistribOpt, idDataGroup, false );
   setFieldReadOnly( ifds::AllocPercent, idDataGroup, true );

   if( strAcctDistribOpt == CASH_ACCT_LEVEL )
   {
      //FundTo,ClassTo && ToFundNumber are read-only
      setFieldReadOnly( ifds::FundToCode, idDataGroup, true );
      setFieldReadOnly( ifds::ClassToCode, idDataGroup, true );
      setFieldReadOnly( ifds::ToFundNumber, idDataGroup, true );

      if( strAcctDistribCurrOpt == FUND_CURRENCY )
      {
         setFieldRequired(ifds::Currency, idDataGroup, false );
         setFieldRequired(ifds::BankIdValue, idDataGroup, false );
         setFieldRequired(ifds::BankAcctType, idDataGroup, false );
         setFieldRequired(ifds::BankAcctNum, idDataGroup, false );
         setFieldReadOnly(ifds::Currency, idDataGroup, true );
      }
   }
   else
   {
      //1. make sure that AcctDistribCurrencyOpt is read-only
      setFieldReadOnly( ifds::AcctDistribCurrencyOption, idDataGroup, true );	

      //2. set FundTo to CASH and ClassTo and ToFundNumber as read only for reinvest
      if( strAcctDistribOpt == REINVEST )
      {
         setFieldReadOnly( ifds::FundToCode, idDataGroup, true );
         setFieldReadOnly( ifds::ClassToCode, idDataGroup, true );
         setFieldReadOnly( ifds::ToFundNumber, idDataGroup, true );
         setFieldRequired (ifds::ACHProcessor, idDataGroup, false);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::clearBankingFields( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("clearBankingFields"));
//beneficial bank
      setFieldNoValidate (ifds::BankIdType, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::BankIdValue, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::TransitNo, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::BankAcctNum, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::BankAcctName, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::BankAcctType, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::InstName, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::BankAddr1, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddr2, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddr3, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddr4, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddr5, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankPostal, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankCountry, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankContact, NULL_STRING, idDataGroup, false);   
      setFieldNoValidate (ifds::SwiftCode, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::RefNumber, NULL_STRING, idDataGroup);
   //correspondent bank      
      setFieldNoValidate (ifds::BankIdTypeCB, NULL_STRING, idDataGroup);
      setFieldNoValidate (ifds::BankIdValueCB, NULL_STRING, idDataGroup, false);   
      setFieldNoValidate (ifds::TransitNoCB, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::InstNameCB, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddrCB1, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddrCB2, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddrCB3, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddrCB4, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankAddrCB5, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankPostalCB, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankCountryCB, NULL_STRING, idDataGroup, false);
      setFieldNoValidate (ifds::BankContactCB, NULL_STRING, idDataGroup, false);   
      setFieldNoValidate (ifds::PayReason1, NULL_STRING, idDataGroup, false);   
      setFieldNoValidate (ifds::PayReason2, NULL_STRING, idDataGroup, false);   
      setFieldNoValidate (ifds::FFC, NULL_STRING, idDataGroup, false);   
      setFieldNoValidate (ifds::FFC1, NULL_STRING, idDataGroup, false);   

    return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY AccountDistribution::validateAcctDistribPayType( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAcctDistribPayType"));

   if( isAllFundsMode(idDataGroup) )
   {
      DString strAcctDistribOpt, strAcctDistribCurrOpt, dstrPayType, dstrPayMethod;
      getField( ifds::AcctDistribOpt, strAcctDistribOpt, idDataGroup, false );
      getField( ifds::AcctDistribCurrencyOption, strAcctDistribCurrOpt, idDataGroup, false );
      getField( ifds::PayMethod, dstrPayMethod, idDataGroup, false );
      getField( ifds::DistributionPayType, dstrPayType, idDataGroup, false );

      if( dstrPayType.strip().upperCase() == EFT &&
         strAcctDistribOpt.strip() == CASH_ACCT_LEVEL &&
         strAcctDistribCurrOpt.strip() == FUND_CURRENCY &&
         dstrPayMethod.strip() == WIRE)
      {
      //make sure that here is a bank
         bool blShowWarn = true;
         if ( _pMFAccount )
         {
            DString shrNum;
            _pMFAccount->getField( ifds::ShrNum, shrNum, idDataGroup, false );
            Shareholder* pShareholder = NULL;
            if( getWorkSession().getShareholder( idDataGroup, shrNum.strip(), pShareholder ) <= WARNING &&
                pShareholder)
            {
				//change for INC0026078 Starts
				DString dstrCurrAcctNum;
				_pMFAccount->getField( ifds::AccountNum, dstrCurrAcctNum, idDataGroup, false );
				//change for INC0026078 Ends
               ShareholderBankInstructionsList *pShareHolderBankInstructionsList = NULL;
               if( pShareholder->getShareholderBankInstructionsList(pShareHolderBankInstructionsList, 
                  idDataGroup,true,dstrCurrAcctNum) <= WARNING && pShareHolderBankInstructionsList)//Modified for INC0026078
               {
                  BFObjIter iter( *pShareHolderBankInstructionsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
                  if( iter.getNumberOfItemsInList() > 0 )
                  {
                     blShowWarn = false;
                  }
               }
            }
         }
         if( blShowWarn)
         {
            ADDCONDITIONFROMFILE( CND::WARN_DEFAULT_BANK_INFO_FOR_ACCT_DISTRIB_NOT_FOUND );
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::initVerifyStatus (const BFDataGroupId &idDataGroup, bool bNew, bool bReset)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("initVerifyStatus"));

   bool bReadOnly = false;
   DString modUser;

   getField (ifds::VerifyStat, _dstrVerifyStatus, idDataGroup, false);
   getField (ifds::ModUser, modUser, idDataGroup, false);
   modUser.strip().upperCase();

   if (modUser.empty())
   {
      getField (ifds::Username, modUser, idDataGroup, false);
      modUser.strip().upperCase();
   }

   getWorkSession ().canVerify (idDataGroup, 
                                UAF::DISTRIB_VERIFICATION, 
                                DISTRIB_CATEGORY, 
                                DISTRIB_LEVEL, 
                                modUser, 
                                _bCanVerify); 

   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             _bVerificationEnabled);

   // enviroment level:
   if (_bVerificationEnabled)
   {
      // field level:
      bReadOnly = !_bCanVerify;

      if ( bNew )
      {
         setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
         setFieldNoValidate (ifds::DistribGBCD, I_("Y"), idDataGroup, false);
         setValidFlag ( ifds::VerifyStat, idDataGroup, true );
         bReadOnly = true;
      }
      // if data is verified is from backend, lock verify stat
      if (idDataGroup == BF::HOST || (bReset && !bNew))
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
   else
   {
      // enviroment does not support verficaiton
      // Verify Status is read only
      // Verify Status on new distrib is set to Verified.
      if (bNew)
      {
         setFieldNoValidate (ifds::VerifyStat, VERIFIED, idDataGroup, false);
         setFieldNoValidate (ifds::DistribGBCD, I_("Y"), idDataGroup, false);
         setValidFlag ( ifds::VerifyStat, idDataGroup, true );
      }

      bReadOnly = true;
   }

   setFieldReadOnly (ifds::VerifyStat, idDataGroup, bReadOnly);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::verifyStatusRelatedChanges (const BFFieldId &idFieldId, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("verifyStatusRelatedChanges"));

   bool bFlipFlag = true;

   if (!_bVerificationEnabled || _bInit)
      return GETCURRENTHIGHESTSEVERITY ();

   if (_level == ACCOUNT_LEVEL)
   {
      if (idFieldId != ifds::VerifyStat )
      {
         if ( !_bIsDirty ) 
         {
            _bIsDirty = isObjectDirty (idDataGroup);

            if( isAllFundsMode( idDataGroup ) ) bFlipFlag = false;

            if (_bIsDirty && bFlipFlag)
            {
               setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
               setValidFlag ( ifds::VerifyStat, idDataGroup, true );
            }
         }
         else
         {
            DString strVerifyStat;
            getField(ifds::VerifyStat,strVerifyStat,idDataGroup,false);

            if ( strVerifyStat == VERIFIED )
            {
               setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
               setValidFlag ( ifds::VerifyStat, idDataGroup, true );
            }
         }
      }

      if ( _bInit || !_bCanVerify )
      {
         setFieldReadOnly (ifds::VerifyStat, idDataGroup, true );
      }
      else
      {
         setFieldReadOnly (ifds::VerifyStat, idDataGroup, _bIsDirty );
      }
   }
   else if ( _level == FUND_CLASS_LEVEL )
   {
      // a change on fund\class level will let account level verify stat change to
      // unverified state.
      AccountDistribution* pDistrib = dynamic_cast<AccountDistribution*>(getParent()->getParent());
      
      if ( pDistrib )
      {
         pDistrib->verifyStatusRelatedChangesFromChild(idFieldId, isObjectDirty (idDataGroup), idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::verifyStatusRelatedChangesFromChild(const BFFieldId &idFieldId, 
                                                                  bool isDirty,
                                                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("verifyStatusRelatedChangesFromChild"));

   bool bFlipFlag = true;

   if (!_bVerificationEnabled || _bInit)
      return GETCURRENTHIGHESTSEVERITY ();

   if (idFieldId != ifds::VerifyStat )
   {
      if ( !_bIsDirty ) 
      {
         _bIsDirty = isObjectDirty (idDataGroup) || isDirty;

         if (_bIsDirty && bFlipFlag)
         {
            setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
            setValidFlag ( ifds::VerifyStat, idDataGroup, true );
         }
      }
      else
      {
         DString strVerifyStat, strVerifyStatHost;
         getField(ifds::VerifyStat,strVerifyStat,idDataGroup,false);
         getField(ifds::VerifyStat,strVerifyStatHost,BF::HOST,false);

         // only record which is verified(from host level) will be changed to unverified
         if ( /*strVerifyStat == VERIFIED &&*/ strVerifyStatHost == VERIFIED)
         {
            setFieldNoValidate (ifds::VerifyStat, UNVERIFIED, idDataGroup, false);
            setValidFlag ( ifds::VerifyStat, idDataGroup, true );
         }
      }
   }

   if ( _bInit || !_bCanVerify )
   {
      setFieldReadOnly (ifds::VerifyStat, idDataGroup, true );
   }
   else
   {
	   DString strVerifyStat;
	   getField( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
	   strVerifyStat.strip().upperCase();

	   if ( !_bIsDirty && strVerifyStat == VERIFIED) 
	   {
		   setFieldReadOnly (ifds::VerifyStat, idDataGroup, true );
	   }
	   else
	   {
		   setFieldReadOnly (ifds::VerifyStat, idDataGroup, _bIsDirty );
	   }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AccountDistribution::SetReadOnlyFields( const BFDataGroupId& idDataGroup )
{
   // if bad and unverified record, set all fields to read-only except verify status
   // depend on user who is able verify or not though.

   bool bReadOnly = !_bCanVerify;
   DString strVerifyStat, strDistribGBCD;
   getField( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
   getField( ifds::DistribGBCD, strDistribGBCD, idDataGroup, false );
   if( strVerifyStat == UNVERIFIED && strDistribGBCD == I_("N") )
   {
      for (int i = 0; i < NUM_FIELDS; i++)
      {
         const BFFieldId idField = classFieldInfo[i].getFieldId();
         long lStateFlag = classFieldInfo[i].getStateFlags();
         
         if( ( lStateFlag != BFCBO::CALCULATED_FIELD || lStateFlag != BFCBO::NOT_ON_HOST || 
               lStateFlag != BFCBO::IMMEDIATE_VALIDATION ) && (idField != ifds::VerifyStat ) )
         {
            setFieldReadOnly(idField,idDataGroup,true);
         }
         else if ( idField == ifds::VerifyStat )
         {
            setFieldReadOnly(idField,idDataGroup,bReadOnly);
         }
      }
   }
}

//******************************************************************************
SEVERITY AccountDistribution::verifyStatusChangesFromDeletion(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("verifyStatusChangesFromDeletion"));

   setFieldNoValidate( ifds::VerifyStat, UNVERIFIED, idDataGroup,false,true,false,false);
   getField( ifds::VerifyStat, _dstrVerifyStatus, idDataGroup,false );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::ValidateAddrCode( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "ValidateAddrCode" ) );

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   BFObjIter iter( *_pAddressList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   iter.setDataFilter( asString (ifds::AddrCode.getId() ) + I_("=") + strValue );
   if( iter.end() )
   {
      DString error = I_( "" );
      addIDITagValue( error, I_("CODE"), strValue );
      ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_SETUP, error );
   }
   else
   {
      DString dstrAddrEffectiveDate, dstrAddrStopDate, dstrEffectiveDate;
      iter.getObject()->getField ( ifds::EffectiveDate, dstrAddrEffectiveDate, idDataGroup );
      iter.getObject()->getField ( ifds::StopDate, dstrAddrStopDate, idDataGroup );
      getParent()->getParent()->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );

      if( ( DSTCommonFunctions::CompareDates ( dstrAddrEffectiveDate, dstrEffectiveDate ) == 
            DSTCommonFunctions::EQUAL ) || 
            ( DSTCommonFunctions::CompareDates ( dstrAddrStopDate, dstrEffectiveDate ) == 
            DSTCommonFunctions::EQUAL ) )
         return(GETCURRENTHIGHESTSEVERITY());

      if( !( (DSTCommonFunctions::CompareDates ( dstrAddrEffectiveDate, dstrEffectiveDate ) 
               == DSTCommonFunctions::FIRST_EARLIER ) &&
               (DSTCommonFunctions::CompareDates ( dstrEffectiveDate, dstrAddrStopDate ) 
               == DSTCommonFunctions::FIRST_EARLIER ) ) )
      {
         DString error = I_( "" );
         addIDITagValue( error, I_("CODE"), strValue );
         ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_EFFECTIVE, error );

         return GETCURRENTHIGHESTSEVERITY();
      }

      if( bVerificationEnabled )
      {
         DString strVerifyStat;
         iter.getObject()->getField ( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
         strVerifyStat.strip().upperCase();

         if ( strVerifyStat == UNVERIFIED )
         {
            DString dstrIDI;
            addIDITagValue (dstrIDI, I_("OPERATION"), I_("Setup Distribution Option"));
            ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_NOT_VERIFY, dstrIDI );

            return GETCURRENTHIGHESTSEVERITY();
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AccountDistribution::getDivChqAddr(DString& strAddrCode, const BFDataGroupId& idDataGroup )
{
   strAddrCode = NULL_STRING;
   DString strAccountNum;
   
   if ( _level == FUND_CLASS_LEVEL && _pMFAccount )
   {
      _pMFAccount->getField( ifds::AccountNum, strAccountNum, idDataGroup, false );

      Shareholder *pShareholder = NULL;
      DString strShrNum = _dstrShareholderNum;
      getWorkSession().getShareholder( idDataGroup, strShrNum, pShareholder );

      AccountMailingList *pAccountMailingList = NULL;
      if( pShareholder && pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup ) <= WARNING )
      {
	     DString strKey;
         if (pShareholder->isNew ())
         {
            strKey = strAccountNum;
         }
         else
         {
            pAccountMailingList->buildKey (strKey, strAccountNum);
         }
         
         BFObjIter iter (*pAccountMailingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

         if( iter.positionByKey( strKey ) )
         {
            DString str;
            iter.getObject()->getField(ifds::DivChqAddr, str, idDataGroup, false );
            strAddrCode = str;
         }
      }
   }
}

//******************************************************************************
void AccountDistribution::doReset( const BFDataGroupId& idDataGroup )
{
   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   if( _level == ACCOUNT_LEVEL )
   {
      if ( bVerificationEnabled )
      {
         _bIsDirty = false;
         _bInit = true;
         initVerifyStatus (idDataGroup, isNew(), true);
         _bInit = false;
      }
   }
}

//******************************************************************************
SEVERITY AccountDistribution::validatePayEntityBank( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validatePayEntityBank" ) );

   TradePayInstructList *pTradePayInstructList = NULL;
   BankInstructions *pBankInstructions = NULL;

   bool bNeedPayentityBankValidation = false;

   if ( getPayInstructList (pTradePayInstructList, idDataGroup) <= WARNING &&
        pTradePayInstructList)
   {
      DString strPayToEntity;
      BFObjIter bfIter (*pTradePayInstructList, 
                        idDataGroup, 
                        false, 
                        BFObjIter::ITERTYPE::NON_DELETED);
      if ( !bfIter.end() )
      {
         TradePayInstruct* pTradePayInstruct = 
            dynamic_cast<TradePayInstruct*>(bfIter.getObject());

         if (pTradePayInstruct && pTradePayInstruct->isBankingAllowed(idDataGroup) )
         {
            pTradePayInstruct->getField( ifds::PayToEntity, strPayToEntity, idDataGroup, false );
            strPayToEntity.strip().upperCase();
         }
      }

      //Check against system configuration whether it require to
      //validate with verify status of payentity bank or not

      if ( !strPayToEntity.empty() )
      {
         DString strBankLevel;
         if (strPayToEntity == PAY_TO::BROKER)
         {
            strBankLevel = BROKER_LEVEL;
         }
         else if (strPayToEntity == PAY_TO::BRANCH)
         {
            strBankLevel = BRANCH_LEVEL;
         }
         else if (strPayToEntity == PAY_TO::SALESREP)
         {
            strBankLevel = SLSREP_LEVEL;
         }

         getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                                   BANK_CATEGORY, 
                                                   strBankLevel, 
                                                   bNeedPayentityBankValidation);

         getEntityBankInstruction( pBankInstructions, strPayToEntity, idDataGroup );
      }
   }

   if ( pBankInstructions && bNeedPayentityBankValidation )
   {
      DString strVerifyStat;
      pBankInstructions->getField( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
      strVerifyStat.strip().upperCase();

      if ( strVerifyStat == UNVERIFIED )
      {
         DString dstrIDI;
         addIDITagValue (dstrIDI, I_("OPERATION"), I_("Setup Distribution Option"));
         ADDCONDITIONFROMFILEIDI( CND::ERR_PAY_ENTITY_BANK_NOT_VERIFY, dstrIDI );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::getEntityBankInstruction(BankInstructions *&pBankInstructions,
                                                       const DString& payToEntity,
                                                       const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "getEntityBankInstruction" ) );

   DString distribEffDate;
   DString strBroker, strBranch, strSlsRep;

   getField ( ifds::EffectiveDate, distribEffDate, idDataGroup );
   if ( _pMFAccount )
   {
      if (payToEntity == PAY_TO::BROKER)
      {
         _pMFAccount->getField (ifds::BrokerCode, strBroker, idDataGroup);
      }
      else if (payToEntity == PAY_TO::BRANCH)
      {
         _pMFAccount->getField (ifds::BrokerCode, strBroker, idDataGroup);
         _pMFAccount->getField (ifds::BranchCode, strBranch, idDataGroup);
      }
      else if (payToEntity == PAY_TO::SALESREP)
      {
         _pMFAccount->getField (ifds::BrokerCode, strBroker, idDataGroup);
         _pMFAccount->getField (ifds::BranchCode, strBranch, idDataGroup);
         _pMFAccount->getField (ifds::Slsrep, strSlsRep, idDataGroup);
      }
   }

   DistributorRepository *pDistributorRepository = NULL;

   if ( getWorkSession ().getDistributorRepository (pDistributorRepository) <= WARNING &&
         pDistributorRepository)
   {
      DistributorBankInstructionsList *pDistributorBankInstructionsList = NULL;
      //call view 52 for broker/branch/slsrep banking
      if ( pDistributorRepository->
               getDistributorBankInstructionsList ( strBroker, 
                                                    strBranch, 
                                                    strSlsRep,
                                                    pDistributorBankInstructionsList, 
                                                    idDataGroup) <= WARNING &&
            pDistributorBankInstructionsList)
      {
         BFObjIter iterPayEntityBank ( *pDistributorBankInstructionsList, 
                                       idDataGroup, 
                                       0, 
                                       BFObjIter::ITERTYPE::NON_DELETED);
         while (!iterPayEntityBank.end())
         {
            DString bankAcctCurrency,
                    bankAcctUseCode,
                    bankEffectiveDate,
                    bankStopDate;

            iterPayEntityBank.getObject()->getField (ifds::BankAcctCurrency, bankAcctCurrency, idDataGroup, false);
            iterPayEntityBank.getObject()->getField (ifds::AcctUseCode, bankAcctUseCode, idDataGroup, false);
            iterPayEntityBank.getObject()->getField (ifds::EffectiveDate, bankEffectiveDate, idDataGroup, false);
            iterPayEntityBank.getObject()->getField (ifds::StopDate, bankStopDate, idDataGroup, false);
            if ( bankAcctUseCode == AcctUseCode::EFT_DIVIDEND &&
                 DSTCommonFunctions::IsDateBetween (bankEffectiveDate, bankStopDate, distribEffDate) )
            {
               // pick the first one which effective against distrib and 
               // its AcctUseCode is EFT_DIVIDEND(16)
               pBankInstructions 
                  = dynamic_cast <BankInstructions*> (iterPayEntityBank.getObject());
               break;
            }
            ++iterPayEntityBank;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountDistribution::validateDeletedChildDistrib( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateDeletedChildDistrib" ) );

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   AccountDistributionList *pSplitList = NULL;

   if ( _level == ACCOUNT_LEVEL && bVerificationEnabled )
   {
      getSplitList( pSplitList, idDataGroup);
      if ( pSplitList )
      {
         BFObjIter iterDistrib( *pSplitList, 
                                idDataGroup, 
                                false, 
                                BFObjIter::ITERTYPE::NON_DELETED);

         DString dstrVerifyStat, dstrVerifyStatOrg, dstrGoodBad;
         double dTotalPercent = 0.0;

         getField( ifds::VerifyStat, dstrVerifyStat, idDataGroup, false );
         getField( ifds::DistribGBCD, dstrGoodBad, idDataGroup, false );
         getFieldBeforeImage( ifds::VerifyStat,dstrVerifyStatOrg );
         dstrVerifyStat.strip().upperCase();
         dstrGoodBad.strip().upperCase();
         dstrVerifyStatOrg.strip().upperCase();

         bool bValidateSum = true;
         if ( ( dstrVerifyStat == VERIFIED && dstrVerifyStatOrg == UNVERIFIED ) || 
              ( dstrVerifyStat == UNVERIFIED && dstrGoodBad == I_("N") ))
         {
            bValidateSum = false;
         }

         while ( !iterDistrib.end() )
         {
            AccountDistribution* pDistrib = 
               dynamic_cast<AccountDistribution*>(iterDistrib.getObject());
               
            if ( pDistrib )
            {
               DString dstr;
               pDistrib->getField( ifds::AllocPercent, dstr, idDataGroup );
               pDistrib->getField( ifds::DistribGBCD, dstrGoodBad, idDataGroup, false );
               dstrGoodBad.strip().upperCase();
               dstr.strip().stripAll( I_CHAR( ',' ) );
               I_CHAR *stopstring;

               if ( dstrGoodBad != I_("N") )
               {
                  dTotalPercent += wcstod( dstr.c_str(), &stopstring );
               }
            }
            ++iterDistrib;
         }

         if( ( fabs( dTotalPercent - 100 ) > .0000000001) && bValidateSum )
         {
            ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );
         }

      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
double AccountDistribution::getUnitPrice ( const DString &fundCode, 
										  const DString &classCode, 
										  const DString &fromDate, 
										  const DString &toDate, 
										  const BFDataGroupId &idDataGroup,
										  const DString transType, /* = I_(""), */
										  const DString &prevDatePressed /*=I_ ("N")*/, 
										  const DString &nextDatePressed) /*=I_ ("N")*/
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
		CLASSNAME, 
		I_ ("getUnitPrice"));

	DString strKey = NULL_STRING;

	if ( transType.empty() )
	{
		strKey = 
			I_("FundList_FundCode=") + fundCode        +
			I_(";ClassCode=")        + classCode       +
			I_(";FromDate=")         + fromDate        +
			I_(";ToDate=")           + toDate          +
			I_(";PrevDatePressed=")  + prevDatePressed +
			I_(";NextDatePressed=")  + nextDatePressed;
	}
	else
	{
		strKey = 
			I_("FundList_FundCode=") + fundCode        +
			I_(";ClassCode=")        + classCode       +
			I_(";TransType=")        + transType  +
			I_(";FromDate=")         + fromDate        +
			I_(";ToDate=")           + toDate          +
			I_(";PrevDatePressed=")  + prevDatePressed +
			I_(";NextDatePressed=")  + nextDatePressed;
	}

	FundList *pFundList;
	pFundList = dynamic_cast <FundList*> (getObject (strKey, idDataGroup));

	if (!pFundList)
	{
		pFundList = new FundList (*this);
		if (pFundList->init ( const_cast <DString&> (fundCode), 
			const_cast <DString&> (classCode), 
			const_cast <DString&> (fromDate),
			const_cast <DString&> (toDate), 
			const_cast <DString&> (prevDatePressed), 
			const_cast <DString&> (nextDatePressed),
			I_("N"), NULL_STRING, I_("Y")) <= WARNING)
		{
			setObject (pFundList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
		}
		else
		{
			delete pFundList;
			pFundList = NULL;
		}
	}

	DString dstrLastIDRate;

	if (pFundList)
	{
		BFObjIter bfIter (*pFundList, idDataGroup);

		for (bfIter.begin (); !bfIter.end (); ++bfIter)
		{
			bfIter.getObject ()->getField (ifds::LastIDRate, dstrLastIDRate, idDataGroup);
			if( !dstrLastIDRate.strip().empty() )
				break;
		}
	}

	return DSTCommonFunctions::convertToDouble (dstrLastIDRate);
}

//******************************************************************************
double AccountDistribution::getIDUnitPrice ( const BFDataGroupId &idDataGroup)
{

	DString dstrFundCode, dstrClassCode, dstrCurrentDate;

	getField( ifds::FundCode, dstrFundCode, idDataGroup );
	getField( ifds::ClassCode, dstrClassCode, idDataGroup );

	dstrFundCode.strip();
	dstrClassCode.strip();

	getWorkSession ().getOption (ifds::CurrSysDate, dstrCurrentDate, idDataGroup, false);
	
	double dUnitPrice = getUnitPrice ( dstrFundCode, 
		dstrClassCode, 
		dstrCurrentDate, 
		dstrCurrentDate, 
		idDataGroup,
		I_("ID"), //  transType
		I_("N"),  //  PrevDatePressed
		I_("N")); //  NextDatePresed
		
	return (dUnitPrice);
}

//*****************************************************************************
void AccountDistribution::setLastIDRate(const BFDataGroupId& idDataGroup)
{
	DString dstrDistribRateOpt;
	getWorkSession().getOption(ifds::DistribInstrAsRatioOpt, dstrDistribRateOpt, BF::HOST, false);
	if ( dstrDistribRateOpt == NO) 
		return;

	double dLastIDRate = getIDUnitPrice (idDataGroup);

	DString dstrLastIDRate = DSTCommonFunctions::doubleToDString(ifds::LastIDRate, dLastIDRate);	
	setFieldNoValidate( ifds::LastIDRate, dstrLastIDRate, idDataGroup, false );		
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountDistribution.cpp-arc  $
 * 
 *    Rev 1.155   May 04 2012 10:51:18   if991250
 * CPF - Account Distribution
 * 
 *    Rev 1.154   Mar 29 2010 22:00:26   dchatcha
 * Fix compile error for R99.
 * 
 *    Rev 1.153   Mar 05 2010 12:31:20   popescu
 * Incident 2033491 - User is able to select Verified or Unverified when hitting RESET - issue fixed for banking/address and distribution
 * Incident 2030879 - fixed the key in the list - the issue is that for new accounts set-up the key of the account mailing list is overridden by 'docommitdatagroup' function.
 * 
 *    Rev 1.152   Feb 15 2010 16:07:12   wutipong
 * IN#1945379 - SetRequiredField( idDataGroup );
 * 
 *    Rev 1.151   Feb 08 2010 12:07:42   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one, fix compile error.
 * 
 *    Rev 1.150   Feb 08 2010 22:12:52   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.149   Feb 06 2010 17:25:40   dchatcha
 * Restore 1.147
 * 
 *    Rev 1.148   Feb 03 2010 19:08:52   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.147   Jan 19 2010 13:00:30   popescu
 * Incident 1981345 - reinvest can be set-up due to file processor required issue.
 * 
 *    Rev 1.146   Jan 19 2010 05:05:22   dchatcha
 * IN# 1975225 - DSK Error when setup Distribution with Broker's unverified bank info, existing issues found, there is logic that override payment type to 'P' for non cash of Fund-to Code result unnecessay validation of pay entity Bank.
 * 
 *    Rev 1.145   Jan 15 2010 20:10:30   dchatcha
 * IN# 1975225 - DSK Error when setup Distribution with Broker's unverified bank info.
 * 
 *    Rev 1.144   Jan 14 2010 03:56:20   dchatcha
 * IN# 1964329 - R97_Static Data - Destination address whose verification status will be checked whether it is verified or not depend on how client use the address as address for dividend cheque.
 * 
 *    Rev 1.143   Jan 13 2010 09:22:28   dchatcha
 * IN# 1971377 - R97_Static Data_File Processor&Bank are blank after deleting distribution option.
 * 
 *    Rev 1.142   Jan 11 2010 08:26:02   dchatcha
 * IN# 1964348 - R97_Static Data_Second User cannot verify after making change but reset/cancel.
 * 
 *    Rev 1.141   Jan 11 2010 05:20:02   dchatcha
 * IN# 1964329 - R97_Static Data_Only 01 Address will be verified as static data.
 * 
 *    Rev 1.140   Dec 23 2009 01:43:10   dchatcha
 * IN# 1953647 - R97 Cannot delete distribution option.
 * 
 *    Rev 1.139   Dec 03 2009 03:33:08   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.138   14 Aug 2009 10:44:50   sibuhatm
 * The BAFF issue is resolved in Account Distribution screen. The Austria and Germany will not display in File processor drop down.
 * 
 * IN1796298 - Unable to select BAFF at dividend screen in Produciton.
 * 
 * 
 *    Rev 1.137   28 Apr 2009 13:27:48   popescu
 * Incident 1669364 - Redirect to Pay Entity not correctly working 
 * 
 *    Rev 1.136   26 Feb 2009 16:17:12   kovacsro
 * IN#1586761 - Issues regarding Account Level Distribution entry on Desktop
 * 
 *    Rev 1.135   23 Feb 2009 15:51:10   popescu
 * P0155543_FN01_ Account Level Distribution 
 * 
 *    Rev 1.135   23 Feb 2009 15:36:28   kovacsro
 * P0155543_FN01_ Account Level Distribution 
 * 
 *    Rev 1.127   May 07 2008 17:43:50   wongsakw
 * IN1218721 Bank information incorrectly Displayed
 * 
 *    Rev 1.126   15 Apr 2008 12:09:32   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.125   Mar 10 2008 15:43:10   jankovii
 * IN 1208035 - Screens are not being displayed accordingly and fields must not be updateable
 * 
 *    Rev 1.124   Mar 05 2008 17:44:46   jankovii
 * IN 1200072 
 * 
 *    Rev 1.123   Mar 05 2008 12:46:32   jankovii
 * IN 1200072 - dividned screen.
 * 
 *    Rev 1.122   Mar 04 2008 15:18:12   jankovii
 * IN 1200072 - Distribution options screen prevents the set up of dividend payment via the BAFF.
 * 
 *    Rev 1.121   06 Feb 2008 16:50:20   kovacsro
 * IN#1175266 - new requirement for PET2400FN01R2.0
 * 
 *    Rev 1.120   10 Jan 2008 14:37:54   kovacsro
 * IN#1147561 - check ConsolidationSetup GC before showing bulking warning
 * 
 *    Rev 1.119   24 Dec 2007 09:52:02   kovacsro
 * PET2400FN01R2.0 - added validation when account level bulking is not turned on
 * 
 *    Rev 1.118   21 Dec 2007 14:43:16   kovacsro
 * PET2400FN01 - account level distribution instruction
 * 
 *    Rev 1.117   24 Jul 2007 20:46:44   popescu
 * GAP 20-22 AIM - moved allowable trsfs check out of the if
 * 
 *    Rev 1.116   24 Jul 2007 20:12:48   popescu
 * GAP 20 -22 AIM
 * 
 *    Rev 1.115   Jun 14 2007 12:16:58   porteanm
 * PET 2360 FN48 - GAPS 48 - Cleanup.
 * 
 *    Rev 1.114   Jun 14 2007 12:12:32   porteanm
 * PET 2360 FN48 - GAPS 48 - for BKK.
 * 
 *    Rev 1.113   Apr 18 2007 12:20:42   jankovii
 * IN# 860339 sync up - balking issue.
 * 
 *    Rev 1.112   Mar 19 2007 10:53:34   popescu
 * Incident# 711561 - fixed some NSCC validations
 * 
 *    Rev 1.111   Feb 14 2007 11:32:50   popescu
 * Incident# 819881 - MFS slowness with the distribution screen
 * 
 *    Rev 1.110   Feb 12 2007 10:37:16   jankovii
 * Incident #819881 - MFS Distributons are slow.
 * 
 *    Rev 1.109   Dec 07 2006 13:11:56   jankovii
 * Incident #711561 - NSCC distribution option.
 * 
 *    Rev 1.108   Oct 13 2006 11:03:30   popescu
 * Incident #711561 - Distribution option for NSCC clients - fix compile error
 * 
 *    Rev 1.107   Oct 06 2006 16:12:04   popescu
 * Incident #711561 - Distribution option for NSCC clients.
 * 
 *    Rev 1.106   Oct 03 2006 22:25:46   popescu
 * Incident #722094 - raise warn msgs if payment instr missing for either pw or id
 * 
 *    Rev 1.105   Sep 21 2006 17:03:12   popescu
 * STP 2217/13 Acct distribution redirect to broker payment type
 * 
 *    Rev 1.104   Sep 20 2006 10:28:26   jankovii
 * Incident #711561 - Distribution option for NSCC clients.
 * 
 *    Rev 1.103   Mar 23 2006 16:26:00   ZHANGCEL
 * PET2132 -- Sync up to 1.101.1.0
 * 
 *    Rev 1.102   Feb 14 2006 13:11:32   porteanm
 * Incident 543959 - Two lines of instructions (Pay Reason).
 * 
 *    Rev 1.101   Sep 07 2005 17:54:38   AGUILAAM
 * IN 397353 - validate ToFund in distribution set-up, should be a valid fund, not blank.
 * 
 *    Rev 1.100   Jul 06 2005 10:57:46   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.99   Mar 15 2005 10:10:48   ZHANGCEL
 * Incident #260666 -- Apply the logic checking ReinDistOnly  on the MER as well
 * 
 *    Rev 1.98   Dec 15 2004 16:07:08   Fengyong
 * PTS10036277 - set pay type default value for cash distribution.
 * 
 *    Rev 1.97   Nov 29 2004 13:17:36   hernando
 * PET1117 - Tuning Project - Revised use of FundDetailList.
 * 
 *    Rev 1.96   Nov 18 2004 13:26:50   YINGBAOL
 * PET1117: Perfermance Tunning
 * 
 *    Rev 1.95   Nov 14 2004 14:24:24   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.94   Aug 16 2004 16:11:42   popescu
 * PTS 10033088, with this fix the account distribution list handles different distribution trans types (ID, MR, etc)
 * 
 *    Rev 1.93   Aug 11 2004 17:40:38   popescu
 * PTS 10032990, cash distribution validation was not triggered for pay type EFT. Now validation kicks, regardless of the value of the pay type.
 * 
 *    Rev 1.92   Apr 16 2004 16:48:00   FENGYONG
 * PET 944 FN01, When Change from fund, reset PayType subSet
 * 
 *    Rev 1.91   Apr 07 2004 18:37:46   FENGYONG
 * PET944FN01 rel56.1 NSCC Broker
 * 
 *    Rev 1.90   Apr 05 2004 17:28:08   FENGYONG
 * PET944 FN01, release 56.1 NSCC Broker Matrix
 * 
 *    Rev 1.89   Mar 31 2004 14:59:34   ZHANGCEL
 * 10028602:Set EffectiveDate to readonly for the existing records 
 * 
 *    Rev 1.88   Feb 11 2004 14:55:50   popescu
 * PTS 10026899, the substitution list for currency it is loaded from host if empty after trying to get it dynamically; also, dealt with the 0 value of the 'TransitNo' in bank instructions
 * 
 *    Rev 1.87   Jan 30 2004 15:04:32   popescu
 * PTS 10026408, 
 * Removed hard coding of the file processor for banking, for broker/branch/slsrep, systematic,distribution,trade,shareholder.
 * Set the value of the file processor to NULL_STRING if there are no values from the back-end, 
 * For banking and distributions set the file processor NOT required if there are no values at the back-end
 * 
 *    Rev 1.86   Jan 28 2004 23:03:18   popescu
 * PTS 10026408, in distribution file processor is only required when pay type is 'E' - EFT,
 * BankInstructionsEx.cpp added a stripAll for the copied values
 * 
 *    Rev 1.85   Jan 27 2004 20:03:54   popescu
 * PTS 10026408, CITIBNK is not listed in Drop-down list for File Processor in setting up bank information, by Account - Income Distribution
 * 
 *    Rev 1.84   Oct 04 2003 15:57:04   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.83   Sep 17 2003 16:27:44   ZHANGCEL
 * PTS ticket 10021850 & 10021878: fix <Bank> botton missing when PayMethod is empty.
 * 
 *    Rev 1.82   Aug 12 2003 14:45:24   ZHANGCEL
 * undo 1.81
 * 
 *    Rev 1.81   Aug 11 2003 16:56:54   ZHANGCEL
 * Fix crash when DistributionPayType is "I"
 * 
 *    Rev 1.80   Aug 07 2003 13:22:06   FENGYONG
 * currency combo fix
 * 
 *    Rev 1.79   Aug 07 2003 11:27:36   ZHANGCEL
 * PTS ticket: 10019997, 10020301, 10020368: bug fixed for distribution cash and bank issues
 * 
 *    Rev 1.78   Jul 29 2003 15:54:10   popescu
 * removed the comment it out line that got the account # in the distrib banking
 * 
 *    Rev 1.77   Jul 29 2003 14:50:38   ZHANGCEL
 * PTS ticket 10019997: Bug fix for the CASH MFR/DIST error sign without message problem.
 * 
 *    Rev 1.76   Jul 22 2003 15:09:22   YINGBAOL
 * bug fix for ACHProcessor option sets
 * 
 *    Rev 1.75   Jul 17 2003 16:47:10   FENGYONG
 * init existing , load ACHProcessor subset
 * 
 *    Rev 1.74   Jul 04 2003 17:42:36   HERNANDO
 * PTS 10019191 - Added BankCountry to classFieldInfo array.
 * 
 *    Rev 1.73   Jun 19 2003 18:02:34   popescu
 * Check whehter pay type is EFT, only in this case we have distribution banking
 * 
 *    Rev 1.72   Jun 19 2003 17:22:12   FENGYONG
 * PET821_FN17
 * 
 *    Rev 1.71   Jun 01 2003 17:07:34   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.70   Apr 15 2003 10:42:04   linmay
 * sync with 1.68.1.0
 * 
 *    Rev 1.69   Mar 21 2003 17:53:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.68   Feb 26 2003 17:18:32   HSUCHIN
 * PTS - 10013814 - bug fix to fundnumber not populating fund/class code and account/fund/class trading check.
 * 
 *    Rev 1.67   Feb 12 2003 20:22:40   WINNIE
 * Validate Cash Distribution against the CashDivAllowed flag at fund detail level
 * 
 *    Rev 1.66   Jan 03 2003 18:03:24   WINNIE
 * must do setField in setFundClass otherwise validation on fund and class will not be triggered. 
 * 
 *    Rev 1.65   Jan 03 2003 12:40:16   HERNANDO
 * Added use of DistribFundsValidate and ReinInOtherFundAllowed flags.
 * 
 *    Rev 1.64   Jan 03 2003 10:04:18   WINNIE
 * validation for allowable transfer when reinvest to a different fund
 * 
 *    Rev 1.63   Dec 12 2002 11:01:56   FENGYONG
 * Set transtype to the current group, only check cantradefundclass for fundlevel
 * 
 *    Rev 1.62   Nov 29 2002 15:37:06   ZHANGCEL
 * Synced up to 1.62
 * 
 *    Rev 1.61   Oct 09 2002 23:53:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.60   Sep 30 2002 11:01:08   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.59   Sep 04 2002 17:15:28   KOVACSRO
 * 1. BankAcctName is set from MFAccount::getAcctName
 * 2. PTS 10009285 FromFund/FromClass validation problem fixed.
 * 
 *    Rev 1.58   Aug 29 2002 12:54:50   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.57   Aug 14 2002 11:05:18   HSUCHIN
 * bug fix for empty distribution calling dovalidate all.
 * 
 *    Rev 1.56   Jul 25 2002 08:35:28   HSUCHIN
 * bug fix which locks the transaction type after lost focus
 * 
 *    Rev 1.55   Jul 05 2002 16:22:08   HERNANDO
 * Fix - removed Warning icon that displays on valid fund numbers.
 * 
 *    Rev 1.54   Jun 17 2002 16:08:34   KOVACSRO
 * Not necessary to set TransitNo as required.
 * 
 *    Rev 1.53   Jun 17 2002 15:20:28   KOVACSRO
 * formatted versus unformatted.
 * 
 *    Rev 1.52   22 May 2002 18:26:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.51   May 16 2002 15:45:14   ZHANGCEL
 * PTS 10008201: Bug fixed for Fund & Class not displaying after TAB
 * 
 *    Rev 1.50   08 May 2002 16:59:58   HSUCHIN
 * PTS - 10008086 - currency lock for cash when multi currency is false
 * 
 *    Rev 1.49   02 May 2002 16:22:20   HSUCHIN
 * PTS 10007942 - bug fix, backend data returned is no longer validated
 * 
 *    Rev 1.48   26 Apr 2002 11:03:50   HSUCHIN
 * bug fix on substutition list
 * 
 *    Rev 1.46   19 Apr 2002 09:11:04   HSUCHIN
 * bug fix for null fund details
 * 
 *    Rev 1.45   18 Apr 2002 15:27:28   HSUCHIN
 * Added support for Management Fee Rebate Distribution
 * 
 *    Rev 1.44   Mar 05 2002 11:13:38   FENGYONG
 * sync 45 fix
 * 
 *    Rev 1.43   Feb 25 2002 18:55:06   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.42   Sep 10 2001 14:04:46   FENGYONG
 * fix validatecash allowCashDistrib check
 * 
 *    Rev 1.41   28 Aug 2001 17:00:34   WINNIE
 * add logic to check if cash distribution is allowed at system level
 * 
 *    Rev 1.40   Aug 04 2001 22:01:52   YINGBAOL
 * condition clearance
 * 
 *    Rev 1.39   02 Aug 2001 14:13:06   WINNIE
 * bug fix for bank when switching pay type between 'E' and 'I'
 * 
 *    Rev 1.38   31 Jul 2001 09:52:50   WINNIE
 * Bug fix for banking
 * 
 *    Rev 1.37   Jul 26 2001 16:22:20   ZHANGCEL
 * Fixed the bug that caused banking info disappear when user change the paytype
 * 
 *    Rev 1.36   Jun 26 2001 19:01:46   PURDYECH
 * More Infrastructure Release 1.9 Integration stuff.
 * 
 *    Rev 1.35   18 Jun 2001 11:59:40   KOVACSRO
 * getSplitList() returns now the right pointer.
 * 
 *    Rev 1.34   May 18 2001 17:21:40   ZHANGCEL
 * 1.Set default value for BankIdTypeCB 2.Added logic into ValidateDistributePercentage() and SetRequiredField() for the Percentage validation. 
 * 
 *    Rev 1.33   May 16 2001 13:30:48   WINNIE
 * sync up with 1.29.1.10 : implement pay type 'International wire'
 * 
 *    Rev 1.32   11 May 2001 14:57:52   HSUCHIN
 * resync with (1.29.1.9) missing functions
 * 
 *    Rev 1.29.1.9   Apr 19 2001 14:24:46   YINGZ
 * fix validation which cause a lot of problems
 * 
 *    Rev 1.29.1.8   Apr 19 2001 11:24:00   DINACORN
 * Add "International Wire" pay type
 * 
 *    Rev 1.29.1.7   Apr 19 2001 10:50:16   YINGZ
 * fix some datagroup id problem
 * 
 *    Rev 1.29.1.6   Apr 19 2001 10:39:38   YINGZ
 * fix missing dis thing
 * 
 *    Rev 1.29.1.5   Apr 17 2001 15:59:36   YINGZ
 * fix wrong recid, undetected changes bugs
 * 
 *    Rev 1.29.1.4   Apr 17 2001 10:41:20   YINGZ
 * fix recid problem
 * 
 *    Rev 1.29.1.3   Apr 16 2001 17:14:26   WINNIE
 * Assign default Value for bank
 * 
 *    Rev 1.29.1.2   Apr 16 2001 14:03:04   WINNIE
 * clean up banking validation code 
 * 
 *    Rev 1.29.1.1   Apr 16 2001 10:32:58   WINNIE
 * Remove old validation for bank; copy new fields for bank between bankinstr and the CBO;
 * 
 *    Rev 1.29.1.0   Apr 10 2001 10:59:54   YINGZ
 * remove reference to banklist
 * 
 *    Rev 1.29   Apr 04 2001 16:14:44   FENGYONG
 * memery leak fix
 * 
 *    Rev 1.28   Jan 31 2001 11:32:26   JANKAREN
 * Replace isFundClassExist method with getFundDetail method
 * 
 *    Rev 1.27   Jan 25 2001 09:34:28   YINGZ
 * add bankacctname in SetBankFieldStatus
 * 
 *    Rev 1.26   Jan 22 2001 15:31:10   YINGZ
 * modify SetBankFieldStatus to make xml api work
 * 
 *    Rev 1.25   Jan 17 2001 12:08:22   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.24   Jan 12 2001 13:35:30   ZHANGCEL
 * Added a new function ValidatePayType
 * 
 *    Rev 1.23   Dec 18 2000 12:31:02   HSUCHIN
 * minor optimization
 * 
 *    Rev 1.22   Dec 17 2000 20:22:06   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.21   Dec 07 2000 10:06:28   ZHANGCEL
 * Synchronized whith C2/C3
 * 
 *    Rev 1.20   01 Nov 2000 14:30:38   SMITHDAV
 * Update to use ne data broker.
 * 
 *    Rev 1.19   Oct 31 2000 10:07:00   KOVACSRO
 * Implemented validateCash().
 * 
 *    Rev 1.18   Oct 23 2000 15:04:34   KOVACSRO
 * Checking InstCode, TransitNo and BankAccNo not to be to big.
 * 
 *    Rev 1.17   Oct 19 2000 17:44:36   WINNIE
 * Move setsessionid to the beginning of init
 * 
 *    Rev 1.16   Sep 25 2000 11:24:32   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.15   Sep 22 2000 15:43:52   WINNIE
 * Setfield required for AcctLevel record; copy account level fields to fund level record in doapplyrelated changes rather than in dovalidatefield
 * 
 *    Rev 1.14   Sep 22 2000 11:38:34   WINNIE
 * BankAcctName not updatable; using FundDetail pointe r for baycom number if pointer has been assigned
 * 
 *    Rev 1.13   Sep 11 2000 10:38:06   YINGBAOL
 * clean up and improve real time behavior
 * 
 *    Rev 1.12   Sep 06 2000 14:46:30   YINGBAOL
 * change sync.
 * 
 *    Rev 1.11   Aug 18 2000 11:04:18   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.10   Aug 04 2000 13:57:16   YINGBAOL
 * change enquiry bank list
 * 
 *    Rev 1.9   Aug 03 2000 11:10:22   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.8   Jul 25 2000 14:21:44   ZHANGCEL
 * Add code for fund number, code and class relatedchanges  
 * 
 */