//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : SettlementTrade.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
//********************************************************************************
#include "stdafx.h"
#include "settlement.hpp"
#include "settlementtrade.hpp"
#include "SettlementTradeList.hpp"

#include "acctcategorylist.hpp"
#include "settlementtradebankinstructionslist.hpp"
#include "settlementtradebankinstructions.hpp"
#include "mfaccount.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "fundmasterlist.hpp"
#include "fundmaster.hpp"
#include "mfaccountholdinglist.hpp"
#include "mgmtco.hpp"
#include "shareholder.hpp"
#include "addresslist.hpp"
#include "dynamicsublistholder.hpp"
#include "transtypefileproclist.hpp"
#include "datevalidation.hpp"
#include "TransactionDetails.hpp"
#include "TransactionList.hpp"
#include <ifastdataimpl\dse_dstc0200_vw.hpp>
#include <ifastdataimpl\dse_dstc0200_req.hpp>
#include <ifastdataimpl\dse_dstc0201_vw.hpp>
#include <ifastdataimpl\dse_dstc0201_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastdataimpl\dse_dstc0135_vw.hpp>
#include "bankinstructionslist.hpp"
#include "bankinstructions.hpp"
#include "address.hpp"
#include "ChqName.hpp"
#include "mgmtco.hpp"
#include "funddetaillist.hpp" 

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_invalid_payment_method.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "SettlementTrade" );
   const I_CHAR * const PURCHASE                = I_( "ED" );
   const I_CHAR * const REDEMPTION              = I_( "PW" );
   const I_CHAR * const TRANSFERIN              = I_( "TI" );
   const I_CHAR * const TRANSFEROUT             = I_( "TO" );
   const I_CHAR * const EXCHANGEIN              = I_( "EI" );
   const I_CHAR * const EXCHANGEOUT             = I_( "EO" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const GROSS                   = I_( "G" );
   const I_CHAR * const NET                     = I_( "N" );
   const I_CHAR * const EFT                     = I_( "E" );
   const I_CHAR * const BROKER                  = I_( "BR" );
   const I_CHAR * const TRANS_NUMBER            = I_( "TN" );
   const I_CHAR * const SETTLE_DATE             = I_( "SD" );
   const I_CHAR * const DIRECT_DEPST_REDEMPTION = I_( "D1" );
   const I_CHAR * const UNVERIFIED              = I_( "02" );
   const I_CHAR * const BANKING_LEVEL           = I_( "1" );
   const I_CHAR * const VERIFIED                = I_( "01" );
   const I_CHAR * const SHAREHOLDER             = I_( "10" );
   const I_CHAR * const SHRHLDR_LEVEL           = I_( "01" );
   const I_CHAR * const SHRHLDR_CATEGORY        = I_( "3" );
   const I_CHAR * const EPA_BROKER              = I_( "EP" );
   const I_CHAR * const SWIFT_PAYMENT_METHOD    = I_( "38" );
   const I_CHAR * const STOP_TRADE_SETTLEMENT   = I_( "01" );
}
namespace PAYMENT_ROUTING
{
   const I_CHAR * const MT103      = I_("01");
   const I_CHAR * const MT202	   = I_("02");
   const I_CHAR * const ACH        = I_("03");
}
namespace TRADETYPE
{
 extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;
}

namespace CND
{
   extern const long ERR_SETTLEMENT_VALUE_DATE;
   extern const long ERR_CORR_BANK_FIELDS_SHOUD_BE_ENTERED;
   extern const long ERR_CORR_BANK_SHOULD_BE_EMPTY;
   extern const long ERR_ADDRESS_TWO_LINE;
   extern const long ERR_Net_SETTLEMENT_NOT_ALLOWED;
   extern const long ERR_VALUEDATE_CANNOT_EARLIER_THAN_CURRENT_DATE;
   extern const long ERR_SETTLEMENT_PAY_TYPE_CLEARING_CANNOT_BE_SELECTED;
   extern const long ERR_SETTLEMENT_SUPPRESS_CODE_CLEARING_CANNOT_BE_SELECTED;
   extern const long ERR_ADDRESS_CODE_NOT_SETUP;
   extern const long WARN_STOP_SETTLE_REDEMPTION;
   extern const long ERR_STOP_SETTLE_REDEMPTION;
   extern const long ERR_SETTLEMENT_INSUFFICIENT_SETTLED_UNITS;
   extern const long WARN_SETTLE_ALL;
   extern const long ERR_SETTLEMENT_PAY_TYPE_DIRECT_DEPOSIT_CANNOT_BE_SELECTED;
   extern const long ERR_UNVERIFIED_BANK;
   extern const long WARN_UNVERIFIED_BANK;
   extern const long ERR_ADDRESS_NOT_VERIFY;
   extern const long WARN_ADDRESS_NOT_VERIFY;
   extern const long ERR_EFT_TO_CHQ_NOT_ALLOWED;
   extern const long ERR_SETTLE_FUTURE_TRADE_NOT_ALLOWED_FOR_EPA_TRADE;
   extern const long ERR_TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO;
   extern const long WARN_TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO;
   extern const long ERR_INVALID_CASH_DATE;
   extern const long WARN_INVALID_CASH_DATE;
   extern const long ERR_INVALID_PAYMENT_METHOD;
   extern const long ERR_CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE;
   extern const long WARN_CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Settled;
   extern CLASS_IMPORT const BFTextFieldId TradesPayType;
   extern CLASS_IMPORT const BFTextFieldId PurchasePayType;
   extern CLASS_IMPORT const BFTextFieldId RedemptionPayType;
   extern CLASS_IMPORT const BFTextFieldId ACHRedemption;
   extern CLASS_IMPORT const BFTextFieldId SettleByLux;
   extern CLASS_IMPORT const BFTextFieldId InternationalWire;
   extern CLASS_IMPORT const BFTextFieldId Address;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId AcctCategory;
   extern CLASS_IMPORT const BFTextFieldId DeliveryMethod2;
   extern CLASS_IMPORT const BFTextFieldId DirectDepositBankApplicable;
   extern CLASS_IMPORT const BFTextFieldId VerifyStat;
   extern CLASS_IMPORT const BFDecimalFieldId AcctID;
   extern CLASS_IMPORT const BFTextFieldId EftToChqAllowed;
   extern CLASS_IMPORT const BFTextFieldId AllowChqChange;
   extern CLASS_IMPORT const BFTextFieldId PymtRoutingMthd;
   extern CLASS_IMPORT const BFTextFieldId TradelevelOveride;
   extern CLASS_IMPORT const BFTextFieldId CatValue;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TradeRestriction;
   extern CLASS_IMPORT const BFDateFieldId NextSettleDate;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SETTLE_PAY_INSTRUCTION;
}

namespace FUND_TYPE
{
   extern const I_CHAR * const MONEY_MARKET;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const MANUAL_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const SYSTEM_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const EFT;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const UNVERIFIED_BANK_SETTLEMENT;
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_ADDRESS_NOT_VERIFIED_FOR_SETTLEMENT;
   extern CLASS_IMPORT I_CHAR * const TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO;
   extern CLASS_IMPORT I_CHAR * const INVALID_CASH_DATE;
   extern CLASS_IMPORT I_CHAR * const CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE;
}
namespace ACCOUNT_TYPE
{
   const I_CHAR * const INDIVIDUAL_ACCT_LIKE = I_("0,1,2,3");
   const I_CHAR * const CORPORATE_ACCT_LIKE  = I_("4,5,6,7,8,9,F,G");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,              State Flags,            Group Flags 
   { ifds::CompanyCode,       BFCBO::NONE,                 0 }, 
   { ifds::AccountNum,        BFCBO::NONE,                 0 }, 
   { ifds::WireOrdNum,        BFCBO::NONE,                 0 }, 
   { ifds::TransNum,          BFCBO::NONE,                 0 }, 
   { ifds::FundCode,          BFCBO::NONE,                 0 }, 
   { ifds::ClassCode,         BFCBO::NONE,                 0 }, 
   { ifds::GrossAmt,          BFCBO::NONE,                 0 }, 
   { ifds::TransId,           BFCBO::NONE,                 0 }, 
   { ifds::TransType,         BFCBO::NONE,                 0 }, 
   { ifds::TradeDate,         BFCBO::NONE,                 0 }, 
   { ifds::ValueDate,         BFCBO::NONE,                 0 }, 
   { ifds::BrokerCode,        BFCBO::NONE,                 0 }, 
   { ifds::BranchCode,        BFCBO::NONE,                 0 }, 
   { ifds::SlsrepCode,        BFCBO::NONE,                 0 }, 
   { ifds::SettleCurrency,    BFCBO::NONE,                 0 }, 
   { ifds::TransDetlRid,      BFCBO::NONE,                 0 }, 
   { ifds::Commission,        BFCBO::NONE,                 0 }, 
   { ifds::AddrCode,          BFCBO::NONE,                 0 }, 
   { ifds::Name1,             BFCBO::NONE,                 0 }, 
   { ifds::Name2,             BFCBO::NONE,                 0 }, 
   { ifds::AddrLine1,         BFCBO::NONE,                 0 }, 
   { ifds::AddrLine2,         BFCBO::NONE,                 0 }, 
   { ifds::AddrLine3,         BFCBO::NONE,                 0 }, 
   { ifds::AddrLine4,         BFCBO::NONE,                 0 }, 
   { ifds::AddrLine5,         BFCBO::NONE,                 0 }, 
   { ifds::PostalCode,        BFCBO::NONE,                 0 }, 
   { ifds::CountryCode,       BFCBO::NONE,                 0 }, 
   { ifds::DistFee,           BFCBO::NONE,                 0 }, 
   { ifds::Fee,               BFCBO::NONE,                 0 }, 
   { ifds::Units,             BFCBO::NONE,                 0 }, 
   { ifds::AcctValue,         BFCBO::NONE,                 0 }, 
   { ifds::Price,             BFCBO::NONE,                 0 }, 
   { ifds::NetAmt,            BFCBO::NONE,                 0 }, 
   { ifds::PayType,           BFCBO::REQUIRED,             0 }, 
   { ifds::PayMethod,         BFCBO::NONE,                 0 }, 
   { ifds::AltAccount,        BFCBO::NONE,                 0 }, 
   { ifds::SettleDate,        BFCBO::NONE,                 0 }, 
   { ifds::Commission2,       BFCBO::NONE,                 0 }, 
   { ifds::OrderSource,       BFCBO::NONE,                 0 }, 
   { ifds::SettleSource,      BFCBO::NONE,                 0 }, 
   { ifds::SettleType,        BFCBO::NONE,                 0 }, 
   { ifds::BankChrgs,         BFCBO::NONE,                 0 }, 
   { ifds::DeliveryMethod,    BFCBO::NONE,                 0 }, 
   { ifds::VolSettleType,     BFCBO::NONE,                 0 }, 
   { ifds::SettledBy,         BFCBO::NONE,                 0 }, 
   { ifds::SuppressCode,      BFCBO::NONE,                 0 }, 
   { ifds::ExchRate,          BFCBO::NONE,                 0 }, 
   { ifds::BatchName,         BFCBO::NONE,                 0 }, 
   { ifds::InstName,          BFCBO::NONE,                 0 }, 
   { ifds::SwiftCode,         BFCBO::NONE,                 0 }, 
   { ifds::RefNumber,         BFCBO::NONE,                 0 }, 
   { ifds::TransitNo,         BFCBO::NONE,                 0 }, 
   { ifds::BankAcctNum,       BFCBO::NONE,                 0 }, 
   { ifds::BankAcctName,      BFCBO::NONE,                 0 }, 
   { ifds::BankAcctType,      BFCBO::NONE,                 0 }, 
   { ifds::BankAcctTypeDesc,  BFCBO::NONE,                 0 }, 
   { ifds::BankAcctCurrency,  BFCBO::NONE,                 0 }, 
   { ifds::BankAcctCurrDesc,  BFCBO::NONE,                 0 }, 
   { ifds::PayReason1,        BFCBO::NONE,                 0 }, 
   { ifds::PayReason2,        BFCBO::NONE,                 0 }, 
   { ifds::CorrespBankId,     BFCBO::NONE,                 0 }, 
   { ifds::BankIdType,        BFCBO::NONE,                 0 }, 
   { ifds::BankIdTypeCB,      BFCBO::NONE,                 0 }, 
   { ifds::BankIdValueCB,     BFCBO::NONE,                 0 }, 
   { ifds::FFC,               BFCBO::NONE,                 0 }, 
   { ifds::FFC1,              BFCBO::NONE,                 0 }, 
   { ifds::ACHProcessor,      BFCBO::NONE,                 0 }, 
   { ifds::BankContactCB,     BFCBO::NONE,                 0 }, 
   { ifds::BankCountryCB,     BFCBO::NONE,                 0 }, 
   { ifds::BankPostalCB,      BFCBO::NONE,                 0 }, 
   { ifds::BankAddrCB1,       BFCBO::NONE,                 0 }, 
   { ifds::BankAddrCB2,       BFCBO::NONE,                 0 }, 
   { ifds::BankAddrCB3,       BFCBO::NONE,                 0 }, 
   { ifds::BankAddrCB4,       BFCBO::NONE,                 0 }, 
   { ifds::BankAddrCB5,       BFCBO::NONE,                 0 }, 
   { ifds::BankAddr1,         BFCBO::NONE,                 0 }, 
   { ifds::BankAddr2,         BFCBO::NONE,                 0 }, 
   { ifds::BankAddr3,         BFCBO::NONE,                 0 }, 
   { ifds::BankAddr4,         BFCBO::NONE,                 0 }, 
   { ifds::BankAddr5,         BFCBO::NONE,                 0 }, 
   { ifds::BankContact,       BFCBO::NONE,                 0 }, 
   { ifds::BankCountry,       BFCBO::NONE,                 0 }, 
   { ifds::BankPostal,        BFCBO::NONE,                 0 }, 
   { ifds::TransitNoCB,       BFCBO::NONE,                 0 }, 
   { ifds::InstNameCB,        BFCBO::NONE,                 0 }, 
   { ifds::PACSWPId,          BFCBO::NONE,                 0 }, 
   { ifds::DistribDetlRid,    BFCBO::NONE,                 0 }, 
   { ifds::BankIdValue,       BFCBO::NONE,                 0 }, 
   { ifds::BankId,            BFCBO::NONE,                 0 }, 
   { ifds::ShrNum,            BFCBO::NONE,                 0 }, 
   { ifds::ExpGNSettle,       BFCBO::NONE,                 0 }, 
   { ifds::GNSettle,          BFCBO::NONE,                 0 }, 
   { ifds::Settled,           BFCBO::NONE,                 0 }, 
   { ifds::InternationalWire, BFCBO::NONE,                 0 }, 
   { ifds::Address,           BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::StopRedSettle,     BFCBO::NONE,                 0 }, 
   { ifds::StopDate,          BFCBO::NONE,                 0 },
   { ifds::BnkAcctIDLink,     BFCBO::NONE,                 0 },
   { ifds::AcctID,            BFCBO::NONE,                 0 },
   { ifds::VerifyStat,        BFCBO::NONE,                 0 },
   { ifds::PymtRoutingMthd,	  BFCBO::NONE,                 0 },  
   { ifds::Valoren, 	      BFCBO::CALCULATED_FIELD,     0 }, 
   { ifds::TDCC,	          BFCBO::CALCULATED_FIELD,	   0 }, 
   { ifds::CUSIP,             BFCBO::CALCULATED_FIELD,	   0 }, 
   { ifds::CashDate,          BFCBO::NONE,                 0 },
   
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "" ),                      BFCBO::NONE,            0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

SettlementTrade::SettlementTrade( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
   addCrossEdit(ifds::InternationalWire, ifds::SettleCurrency);
   addCrossEdit(ifds::InternationalWire, ifds::BankCountry);
   addCrossEdit(ifds::Address, ifds::AddrLine1);
   addCrossEdit(ifds::Address, ifds::AddrLine2);
   addCrossEdit(ifds::Address, ifds::AddrLine3);
   addCrossEdit(ifds::Address, ifds::AddrLine4);
   addCrossEdit(ifds::Address, ifds::AddrLine5);

   hasTRXRs = false;
}

//******************************************************************************

SettlementTrade::~SettlementTrade()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY SettlementTrade::init(const BFData&   data,const DString& dstrSearchType, const bool bInd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   setIndividual( bInd );
   _dstrSearchType = dstrSearchType;
   //setFieldNoValidate(ifds::GNSettle,I_("G"),BF::HOST,false );	
   DString dstrSettle;     
   getParent()->getField( ifds::SettleAll,dstrSettle,BF::HOST,false );  
   setFieldNoValidate(ifds::Settled,dstrSettle,BF::HOST,false,true,false,false );
   DString dstrTransType;
   getField(ifds::TransType,dstrTransType, BF::HOST,false);
   if ( dstrTransType == REDEMPTION )
   {
      DString dstrDirDepsBnkApplicable;
      getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, 
                                    dstrDirDepsBnkApplicable, BF::HOST, false);

      // make sure that direct deposit pay type is available only when generic control is active
      if (dstrDirDepsBnkApplicable == I_("N"))
      {
         DString substList1,substList2;
         BFProperties *pProperties = getFieldProperties (ifds::RedemptionPayType, BF::HOST);
         if( pProperties )
         {
            pProperties->getAllSubstituteValues (substList1);
         }
         substList2 = substList1;
         substList1 = removeItemFromSubtList( substList1, DIRECT_DEPST_REDEMPTION );
         setFieldAllSubstituteValues ( ifds::PayType, BF::HOST, 
                                       substList1);
      }
      else
      {
         setFieldSubstituteValues( ifds::PayType, BF::HOST, ifds::RedemptionPayType );
      }
   }
   else if ( dstrTransType == PURCHASE )
      setFieldSubstituteValues( ifds::PayType, BF::HOST, ifds::PurchasePayType );

   if (dstrTransType == TRANSFERIN || dstrTransType == TRANSFEROUT ||
       dstrTransType == EXCHANGEIN || dstrTransType == EXCHANGEOUT)
       hasTRXRs = true;

   Settlement* pSettlement = dynamic_cast<Settlement* >(getParent()->getParent() ); 
   bool bPermit = pSettlement->hasPermissionForSearchType(dstrSearchType);
   setFieldReadOnly( ifds::Settled, BF::HOST, !bPermit);

   if( dstrSearchType == TRANS_NUMBER)
      setFieldReadOnly( ifds::Settled, BF::HOST, true);
   
   DString dstrPymtGen;
   getField(ifds::PymtGen, dstrPymtGen, BF::HOST);
   setFieldReadOnly( ifds::GNSettle, BF::HOST, !bPermit || dstrPymtGen == I_("Y"));

   getField( ifds::GNSettle, _dstrGNSettle,BF::HOST, false);
   _dstrGNSettle.strip().upperCase();
   bool bUpdate = isIndividual() && dstrTransType == PURCHASE && bPermit;     
   setFieldReadOnly( ifds::SettledBy, BF::HOST, !bUpdate);

   DString dstrPayType;
   getField(ifds::PayType,dstrPayType,BF::HOST,false);
   bUpdate = I_("S")== dstrPayType.strip() && dstrTransType == REDEMPTION && bPermit ;      
   setFieldReadOnly( ifds::DeliveryMethod, BF::HOST, !bUpdate);
   setFieldNoValidate(ifds::DeliveryMethod, I_("01"),   BF::HOST,false);

//valuedate
   setFieldReadOnly( ifds::ValueDate, BF::HOST, dstrTransType == PURCHASE || !bPermit);

   // setFieldNoValidate(ifds::SettledBy, I_("0"),   BF::HOST,false);  
   DString dstrMarket = DSTCommonFunctions::getMarket();
   if ( MARKET_IDS::LUXEMBOURG == dstrMarket )
      setFieldAllSubstituteValues(ifds::SettledBy, BF::HOST,ifds::SettleByLux);

   DString dstrIndCode;
   getField(ifds::Indc,dstrIndCode, BF::HOST, false);
   dstrIndCode.strip();

   bUpdate = dstrIndCode != I_("2" ) && 
             ( I_("S")== dstrPayType.strip() ||
               I_("X")== dstrPayType.strip())&& 
             dstrTransType == REDEMPTION && 
             isIndividual() && 
             bPermit;

   setFieldReadOnly( ifds::PayType, BF::HOST, !bUpdate);

   if ( dstrPayType.stripAll() == I_( "R" ) )
      setFieldReadOnly( ifds::PayType, BF::HOST, true );

//BankCharge
   bUpdate =  ( ( EFT == dstrPayType.strip() ||     
                  DIRECT_DEPST_REDEMPTION == dstrPayType.strip() ) ) && 
              ( dstrTransType == REDEMPTION )   && 
              isIndividual() && bPermit;
   setFieldReadOnly( ifds::BankChrgs, BF::HOST, !bUpdate);

   setFieldRequired( ifds::BankChrgs,     BF::HOST, bUpdate );
   loadFileProcessor(BF::HOST);
   //File Processor
   DString dstrACHRedemption;
   getWorkSession().getOption2( ifds::ACHRedemption, dstrACHRedemption, BF::HOST, false);
   dstrACHRedemption.strip();
   bUpdate = ( YES == dstrACHRedemption )    && 
             ( ( EFT == dstrPayType.strip()  || 
                 DIRECT_DEPST_REDEMPTION == dstrPayType.strip() ) ) && 
             ( dstrTransType == REDEMPTION ) && 
             isIndividual() && bPermit;
   setFieldReadOnly( ifds::ACHProcessor, BF::HOST, !bUpdate);

   DString strSearchType(dstrSearchType);
   strSearchType.strip().upperCase();

   if ( strSearchType == EPA_BROKER ) 
   {
      DString strEftToChqAllowed;
      getField( ifds::EftToChqAllowed, strEftToChqAllowed, BF::HOST, false );
      strEftToChqAllowed.strip().upperCase();

      if( EFT == dstrPayType.strip() && dstrTransType == REDEMPTION && 
          strEftToChqAllowed == I_("Y") )
      {
         setFieldReadOnly( ifds::PayType, BF::HOST, false );
      }
   }

   doAddressRelatedChange(BF::HOST);
   doPayTypeRelatedChange(BF::HOST);

   //the following code should be taken off late; .//fix view problem  
   DString dstrDate; 
   getField(ifds::ValueDate,dstrDate,BF::HOST,false);
   dstrDate.strip();
// if(dstrDate == NULL_STRING ){
   DSTCommonFunctions::getFormat12319999Date(dstrDate);
// setFieldNoValidate(ifds::ValueDate,dstrDate,BF::HOST,false);
// }
   setFieldNoValidate(ifds::StopDate,dstrDate,BF::HOST,false);
   doBankRelatedChange(BF::HOST);

   DString companyCode (NULL_STRING);
   getWorkSession().getOption (ifds::CompanyCode, companyCode, BF::HOST, false);
   companyCode = companyCode.upperCase();
//    if ( companyCode == I_("AIM") || companyCode == I_("AIS") )
//    {
//        setFieldSubstituteValues (ifds::DeliveryMethod, BF::HOST, ifds::DeliveryMethod2);
//    }

   DString outdstrPymtLevelRoutingSet   = NULL_STRING;
   buildPaymentRoutingSet(BF::HOST,outdstrPymtLevelRoutingSet);
   outdstrPymtLevelRoutingSet.empty();
   if(!outdstrPymtLevelRoutingSet.empty())
   {
	 BFProperties *pBFProperties = getFieldProperties (ifds::PymtRoutingMthd, BF::HOST); 
     assert (pBFProperties);
     if (pBFProperties)
     {
      pBFProperties->setAllSubstituteValues (outdstrPymtLevelRoutingSet);
     } 
   }
  
   DString fundCode, classCode;
   getField(ifds::FundCode,fundCode,BF::HOST);
   getField(ifds::ClassCode,classCode,BF::HOST);
   FundMasterList *pFundMasterList = NULL;
   if ( getMgmtCo ().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList)
   {
	   FundMaster *pFundMaster = NULL;
	   if (!( pFundMasterList->getFundMaster (fundCode, BF::HOST, pFundMaster) && 
		   pFundMaster &&
		   isCashDateUpdatable (pFundMaster, BF::HOST)))
	   {
		   setFieldReadOnly (ifds::CashDate, BF::HOST, true);
	   }
   }
   DString dstrCashDate =  NULL_STRING;
   getField(ifds::CashDate,dstrCashDate,BF::HOST,false);
   if (dstrCashDate == I_ (""))
   {
	   DString emptyDate;
	   getWorkSession().getDateInHostFormat (emptyDate, DSTCWorkSession::DATE_TYPE::DAY12319999, BF::HOST);
	   setFieldNoValidate (ifds::CashDate, emptyDate, BF::HOST, false,  true, true); 
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
bool SettlementTrade::isIndividual()
{
   return _bIndividual == true;
}

//*************************************************************************************

SEVERITY SettlementTrade::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

   if ( idField == ifds::GNSettle )
   {
      validateGNSettl( strValue, idDataGroup  );
   }
   else if ( idField == ifds::ValueDate )
   {
      validateValueDate( strValue, idDataGroup );
   }
   else if ( idField == ifds::InternationalWire )
   {
      validateInternationalWire ( idDataGroup );
   }
   else if ( idField == ifds::Address )
   {
      validateAddress(idField,strValue,idDataGroup);
   }
   else if ( idField == ifds::PayType )
   {
      // If original Pay Type is not Clearing, user cannot change it to Clearing
      DString dstrOrigPayType;
      getFieldBeforeImage( ifds::PayType, dstrOrigPayType );
      DString dstrPayType = strValue;
      if ( I_( "R" ) != dstrOrigPayType.stripAll() && I_( "R" ) == dstrPayType.stripAll() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_SETTLEMENT_PAY_TYPE_CLEARING_CANNOT_BE_SELECTED );
      }
      if ( DIRECT_DEPST_REDEMPTION != dstrOrigPayType.stripAll() && 
           DIRECT_DEPST_REDEMPTION == dstrPayType.stripAll() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_SETTLEMENT_PAY_TYPE_DIRECT_DEPOSIT_CANNOT_BE_SELECTED );
      }

      validatePayTypeForEPATrade(strValue,idDataGroup);
   }
   else if ( idField == ifds::PayMethod )
   {
      DString strPayType, strPayMethod;

      getField( ifds::PayType, strPayType, idDataGroup, false );
      getField( ifds::PayMethod, strPayMethod, idDataGroup, false );

      strPayType.strip().upperCase();
      strPayMethod.strip().upperCase();

      if( ( (strPayMethod == I_("DDER") ) && (strPayType != DIRECT_DEPST_REDEMPTION) ) || 
	      ( (strPayMethod != I_("DDER") ) && (strPayType == DIRECT_DEPST_REDEMPTION) ) )
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_PAYMENT_METHOD);
      }
   }
   else if ( idField == ifds::SuppressCode )
   {
      // If original Suppress Code is not Clearing, user cannot change it to Clearing
      DString dstrOrigSuppressCode;
      getFieldBeforeImage( ifds::SuppressCode, dstrOrigSuppressCode );
      DString dstrSuppressCode = strValue;
      if ( I_( "16" ) != dstrOrigSuppressCode.stripAll() && I_( "16" ) == dstrSuppressCode.stripAll() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_SETTLEMENT_SUPPRESS_CODE_CLEARING_CANNOT_BE_SELECTED );
      }
   }
   else if ( idField == ifds::AddrCode )
   {
      validateAddressCode(strValue,idDataGroup);   
   }
   else if ( idField  == ifds::Settled)
   {
      validateStopRedemption( idDataGroup );
      validateSettledUnitsForRedemption( strValue, idDataGroup );
      validateSettledForEPATrade( strValue, idDataGroup );
   }
   else if( idField == ifds::CashDate )
   {
	   validateCashDate( strValue,idDataGroup );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
SEVERITY SettlementTrade::validateAddress( const BFFieldId& idField,const DString strLine, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAddress" ));
   DString dstrTransType, dstrPayType,dstrPayMethod;
   getField(ifds::TransType,dstrTransType,idDataGroup,false );
   getField(ifds::PayType,dstrPayType,idDataGroup,false );
   getField(ifds::PayMethod,dstrPayMethod,idDataGroup,false );

   bool  bVerificationEnabled;

   getWorkSession().isVerificationEnabled( idDataGroup, 
                                           SHRHLDR_CATEGORY, 
                                           SHRHLDR_LEVEL, 
                                           bVerificationEnabled);

   bool bRequire = isIndividual() && (REDEMPTION == dstrTransType) &&(
                                                                     I_("S") == dstrPayType || ((I_("E") == dstrPayType) && (I_("CHQ") == dstrPayMethod)) ); 
   if ( bRequire )
   {
      if ( (getAddressLines(idField,strLine,idDataGroup) < 2 ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ADDRESS_TWO_LINE );
         return GETCURRENTHIGHESTSEVERITY();
      }

      DString dstrWireOrdNum;
      getField ( ifds::WireOrdNum, dstrWireOrdNum, idDataGroup, false );
      dstrWireOrdNum.strip().upperCase();

      // if trade which is going to be settled is wire order trade
      // (wire order number is not blank), it should be validated
      // address for all kind of cheque .
      if ( I_("E") == dstrPayType && !dstrWireOrdNum.empty())
      {
         if ( I_("CHQ") == dstrPayMethod && bVerificationEnabled )
         {
            validateAddrVerifyStatus(idDataGroup);
         }
      }
      else if ( (dstrPayType == PAYTYPE::SYSTEM_CHEQUE  || 
                 dstrPayType == PAYTYPE::MANUAL_CHEQUE)  && bVerificationEnabled )
      {
         validateAddrVerifyStatus(idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//************************************************************************************************
int SettlementTrade::getAddressLines(const BFFieldId& idField, const DString strLine1,const BFDataGroupId& idDataGroup)
{
   int   _iLine = 0;
   DString strAddr;
   DString strLine(strLine1);
   strLine.strip();
   const BFFieldId idAddrLine[]=
   {
      ifds::AddrLine1,
      ifds::AddrLine2,
      ifds::AddrLine3,
      ifds::AddrLine4,
      ifds::AddrLine5,  
   };

   if ( strLine != I_("") ) _iLine++;
   for ( int i = 0;i<5;i++ )
   {
      if ( idField != idAddrLine[i] )
      {
         getField(idAddrLine[i],strAddr,idDataGroup);
         strAddr.strip();
         if ( strAddr != I_("") ) _iLine++;
      }

   }
   return(_iLine);
}

//***********************************************************************************************
SEVERITY SettlementTrade::validateValueDate( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateValueDate" ));
   DateValidation* _dateValidation = new DateValidation ( *this );

   DString fundCode,classCode,payType,transType,validateType,tradeDate,settleDate,settleInDate,effectiveDate,valueDate;
   DString brokerCode,orderType,settleCurrency,dealDate,dealTime,toFund,toClass,amount,amountType;
   DString dstrCurBusDate;
   getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
   if ( DSTCommonFunctions::CompareDates( strValue, dstrCurBusDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_VALUEDATE_CANNOT_EARLIER_THAN_CURRENT_DATE );
      return GETCURRENTHIGHESTSEVERITY();
   }
   getField(ifds::FundCode,fundCode,idDataGroup);
   getField(ifds::ClassCode,classCode,idDataGroup);
   getField(ifds::PayType,payType,idDataGroup,false);
   getField(ifds::TransType,transType,idDataGroup,false);
   validateType = I_("7");
   getField(ifds::TradeDate,tradeDate,idDataGroup,false);
   getField(ifds::SettleDate,settleDate,idDataGroup,false);
   //getField(ifds::SettleInDate,settleInDate,idDataGroup,false);
   getField(ifds::ValueDate,valueDate,idDataGroup,false);
   getField(ifds::BrokerCode,brokerCode,idDataGroup);
   getField(ifds::SettleCurrency,settleCurrency,idDataGroup);
   orderType = I_("Y");
   SEVERITY sevRtn = _dateValidation->init( validateType, 
                                            tradeDate,
                                            settleDate,
                                            effectiveDate,
                                            valueDate,
                                            transType,
                                            payType,
                                            brokerCode,
                                            fundCode,
                                            classCode,
                                            toFund,
                                            toClass,
                                            orderType,
                                            dealDate,
                                            dealTime,
                                            settleCurrency,
                                            amount,
                                            amountType,
                                            NULL_STRING,
                                            NULL_STRING,
                                            NULL_STRING,
                                            NULL_STRING,
                                            NULL_STRING,
                                            NULL_STRING,
                                            I_("N"),
                                            I_(""),
                                            I_(""),
                                            I_("")); 


      //SEVERITY sevRtn = _dateValidation->init( fundCode, classCode, payType,transType,
      //                                     validateType,tradeDate,settleDate,effectiveDate,valueDate,brokerCode,orderType,
      //                                     settleCurrency,dealDate,dealTime,toFund,toClass,amount,amountType );


   if ( sevRtn > WARNING )
   {

      delete _dateValidation;
      return GETCURRENTHIGHESTSEVERITY(); 
   }

   DString dstrValueDate;
   _dateValidation->getField(ifds::ValueDate,dstrValueDate,idDataGroup,false);

   if ( DSTCommonFunctions::CompareDates( dstrValueDate, valueDate ) != DSTCommonFunctions::EQUAL )
   {
      DString idiStr;
      _dateValidation->getField(ifds::ValueDate,dstrValueDate,idDataGroup,true);

      addIDITagValue( idiStr, I_("DATE"), dstrValueDate );
      ADDCONDITIONFROMFILEIDI( CND::ERR_SETTLEMENT_VALUE_DATE, idiStr.c_str() );  
   }
   delete _dateValidation;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY SettlementTrade::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );

   bool  bVerificationEnabled;

   getWorkSession().isVerificationEnabled( idDataGroup, 
                                           SHRHLDR_CATEGORY, 
                                           SHRHLDR_LEVEL, 
                                           bVerificationEnabled);

   if ( idField == ifds::Settled )
   {
      DString dstrSettleAll;
      getParent()->getField(ifds::SettleAll, dstrSettleAll, idDataGroup);
      if( !isSettleAll() )
	  {
         DString dstrTransType;
         getField(ifds::TransType,dstrTransType,idDataGroup,false);
         dstrTransType.strip();	  	
         if(dstrTransType == REDEMPTION && isSettleRedemptionAllowed( idDataGroup ) || dstrTransType != REDEMPTION )
         {
             Settlement* pSettlement = dynamic_cast<Settlement* >(getParent()->getParent() );
             pSettlement-> UserChangeSettle( this,ifds::Settled,idDataGroup );
         }
         setFieldValid( ifds::SettledBy, idDataGroup, isFieldReadOnly( ifds::SettledBy, idDataGroup ) ); //force to do validation
         setValidFlag( ifds::PayType, idDataGroup, isFieldReadOnly( ifds::PayType, idDataGroup ) ); //force to do validation
      }

      if( bVerificationEnabled )
      {
         setValidFlag( ifds::Address, idDataGroup, false ); //force to do validation
      }
   }
/*	else if( idField == ifds::GNSettle )
   {
      Settlement* pSettlement = dynamic_cast<Settlement* >(getParent()->getParent() );
      pSettlement->UserChangeSettle( this,idField,idDataGroup );

   }
*/
   else if ( idField == ifds::PayMethod )
   {
      loadFileProcessor(idDataGroup);
      doAddressRelatedChange( idDataGroup );
      doBankRelatedChange(idDataGroup);
   }

   else if ( idField == ifds::PayType )
   {
      doPayTypeRelatedChange(idDataGroup);
      doAddressRelatedChange( idDataGroup );
      doBankRelatedChange(idDataGroup);
      bankChrgsRelatedChanges(idDataGroup);
   }
   else if ( idField == ifds::AddrCode )
   {
      doAddressCodeRelatedChanges( idDataGroup );
   }

   setValidFlag( ifds::Settled, idDataGroup, false ); //force to do validation

   return GETCURRENTHIGHESTSEVERITY();
}
//***********************************************************************************
SEVERITY SettlementTrade::doPayTypeRelatedChange(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doPayTypeRelatedChange") );
   DString dstrPayType,dstrTransType,dstrPymtGen;
   bool bPaymentGen;
   getField(ifds::TransType,dstrTransType,idDataGroup,false);
   getField(ifds::PayType,dstrPayType,idDataGroup,false);
   getField(ifds::PymtGen,dstrPymtGen, BF::HOST,false);
   dstrPayType.strip().upperCase();
   dstrTransType.strip().upperCase();
   DString dstrSearchType;
   Settlement* pSettlement = dynamic_cast<Settlement* >(getParent()->getParent() ); 
   pSettlement->getField(ifds::SearchType,dstrSearchType,idDataGroup,false);
   bool bPermit = pSettlement->hasPermissionForSearchType(dstrSearchType);


   bool bUpdate =  I_("S")== dstrPayType.strip() && dstrTransType == REDEMPTION  && bPermit;       
   setFieldReadOnly( ifds::DeliveryMethod, idDataGroup, !bUpdate);
   DString dstrACHRedemption;

   getWorkSession().getOption2( ifds::ACHRedemption, dstrACHRedemption, BF::HOST, false);
   dstrACHRedemption.strip().upperCase();
   if ( EFT                     == dstrPayType || 
        DIRECT_DEPST_REDEMPTION == dstrPayType )
   { // EFT
      DString dstrName1, dstrBankAcctName;
      getField ( ifds::BankAcctName, dstrBankAcctName, idDataGroup, false );
      // We only want to copy over when the Bank Account Name is NULL_STRING
      if ( dstrBankAcctName == NULL_STRING )
      {
         getField ( ifds::Name1, dstrName1, idDataGroup );
         setFieldNoValidate ( ifds::BankAcctName, dstrName1, idDataGroup );
      }
   }
   if ( isIndividual() )
   {
      if ( EFT                     == dstrPayType || 
           DIRECT_DEPST_REDEMPTION == dstrPayType)
      { // EFT
         bUpdate = YES == dstrACHRedemption &&  dstrTransType == REDEMPTION && bPermit;

         setFieldRequired(ifds::PayMethod,idDataGroup,bUpdate);
         setFieldRequired(ifds::ACHProcessor,idDataGroup,bUpdate);
         setFieldReadOnly(ifds::PayMethod,idDataGroup,!bUpdate);
         setFieldReadOnly(ifds::ACHProcessor,idDataGroup,!bUpdate);

         if ( idDataGroup != BF::HOST )
         {
            setValidFlag(ifds::PayMethod,idDataGroup,false);
            setValidFlag(ifds::ACHProcessor,idDataGroup,false);        
         }

         DString dstrPayMethod;
         getField(ifds::PayMethod,dstrPayMethod,idDataGroup,false);
         if ( NULL_STRING == dstrPayMethod.strip() )
		 {
			 if(EFT == dstrPayType)
				 setFieldNoValidate(ifds::PayMethod, DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): I_("EFT"), idDataGroup, false);
			 else if(DIRECT_DEPST_REDEMPTION == dstrPayType && DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
				 setFieldNoValidate(ifds::PayMethod, I_("DDER"), idDataGroup, false);
			 else
				 setFieldNoValidate(ifds::PayMethod, DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA ? I_("WIRE"): NULL_STRING, idDataGroup, false);
		 }
         bUpdate = dstrTransType == REDEMPTION;
         setFieldReadOnly(ifds::BankChrgs,idDataGroup,!bUpdate);
         //	DString dstrPayMethod;
         //	getField(ifds::PayMethod,dstrPayMethod,idDataGroup,false);
         //	return GETCURRENTHIGHESTSEVERITY();
      }
      else
      { // clear payment Method and FileProcessor
         setFieldNoValidate(ifds::ACHProcessor,NULL_STRING,idDataGroup);
         setFieldNoValidate(ifds::PayMethod,NULL_STRING,idDataGroup);

         setFieldRequired(ifds::PayMethod,idDataGroup,false);
         setFieldRequired(ifds::ACHProcessor,idDataGroup,false);
      }
   }

   bool bReadOnly;
   bReadOnly = !( ( I_("E") == dstrPayType || DIRECT_DEPST_REDEMPTION == dstrPayType ) &&
                  YES == dstrACHRedemption &&  dstrTransType == REDEMPTION && bPermit);

   setFieldReadOnly(ifds::ACHProcessor,idDataGroup,bReadOnly);
   setFieldReadOnly(ifds::PayMethod,idDataGroup,bReadOnly );  

   setFieldReadOnly(ifds::SuppressCode,idDataGroup,I_("X") != dstrPayType || !bPermit ); 	
   setFieldRequired(ifds::SuppressCode,idDataGroup,I_("X") == dstrPayType && bPermit );
   if ( I_("X") == dstrPayType || I_("R") == dstrPayType )
   {
      setValidFlag(ifds::SuppressCode,idDataGroup,false);  //force to do validation		

      DString dstrSuppressCode;
      getField( ifds::SuppressCode, dstrSuppressCode, idDataGroup );
      if ( I_( "16" ) == dstrSuppressCode.stripAll() && I_("R") == dstrPayType )
      {
         setFieldReadOnly( ifds::SuppressCode, idDataGroup, true );
      }
   }
   else
   {
      setFieldNoValidate(ifds::SuppressCode,NULL_STRING,idDataGroup); // clear fields
   }

   if( I_("S")== dstrPayType.strip().upperCase() && dstrTransType == REDEMPTION )
   {
      // default address code to register address code (01) 
      // when paytype was changed to "S" and let next routine to
      // do some related changed

      setFieldNoValidate(ifds::AddrCode,I_("01"),idDataGroup,false,false,true,false);
   }

   DString dstrPayMethod;
   getField( ifds::PayMethod, dstrPayMethod, idDataGroup);

   if ( (dstrPayType != I_("E") && dstrPayType != DIRECT_DEPST_REDEMPTION) || (dstrPayMethod != I_("WIRE") && dstrPayMethod != I_("EFT") && dstrPayMethod != I_("DDER")))
    {
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
   }
   DString dstrTradePymtRoutingMthd = NULL_STRING;
   bool bSetRoutingReadOnly = true;
   if (isCodeInList( dstrTransType, TRADETYPE::REDEMPTION_LIKE )&&
	   dstrPayType == PAYTYPE::EFT )
   { 
       bSetRoutingReadOnly = false;
	   getField(ifds::PymtRoutingMthd, dstrTradePymtRoutingMthd, idDataGroup);
       dstrTradePymtRoutingMthd.stripAll();
       if(dstrTradePymtRoutingMthd.empty())//if not empty use the same while trade placed
	   {
	       setPaymentRoutingSetDefault(idDataGroup);
	   }  

       bPaymentGen = I_("Y") == dstrPymtGen;

       setFieldReadOnly( ifds::SettledBy, idDataGroup,bPaymentGen);
       setFieldReadOnly(ifds::PayType, BF::HOST,bPaymentGen);
       setFieldReadOnly( ifds::SuppressCode, idDataGroup, bPaymentGen );
       setFieldReadOnly( ifds::DeliveryMethod, idDataGroup, bPaymentGen);
       setFieldReadOnly(ifds::PayMethod,idDataGroup,bPaymentGen);       
       setFieldReadOnly(ifds::ACHProcessor,idDataGroup,bPaymentGen);
       setFieldReadOnly(ifds::BankChrgs,idDataGroup,bPaymentGen);
       setFieldReadOnly( ifds::ValueDate, idDataGroup, bPaymentGen);

   }
   if(bSetRoutingReadOnly)
     setFieldNoValidate( ifds::PymtRoutingMthd  ,NULL_STRING , idDataGroup); 
   setFieldReadOnly(ifds::PymtRoutingMthd, idDataGroup, bSetRoutingReadOnly); 
   return GETCURRENTHIGHESTSEVERITY();
}
//****************************************************************************************
SEVERITY SettlementTrade::doAddressCodeRelatedChanges(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doAddressCodeRelatedChanges") );
   if( idDataGroup == BF::HOST ) return NO_CONDITION;	
   DString dstrAddrCode;
   getField(ifds::AddrCode,dstrAddrCode,idDataGroup,false);
   dstrAddrCode.strip();
   DString dstrShrNum;
   getField(ifds::ShrNum,dstrShrNum,idDataGroup,false);
   dstrShrNum.strip();
   Shareholder* pShareholder = NULL;
   getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder );
   if ( pShareholder )
   {
      AddressList* pAddressList = NULL;
      pShareholder->getAddressList( pAddressList, idDataGroup );
      if ( pAddressList )
      {

         const BFFieldId idCopyField[] = {
            ifds::Name1,
            ifds::Name2,
            ifds::AddrLine1,
            ifds::AddrLine2,
            ifds::AddrLine3,
            ifds::AddrLine4,
            ifds::AddrLine5,
            ifds::PostalCode,
            ifds::CountryCode,
            ifds::NullFieldId };

         Address* pAddress = NULL;

         if (pAddressList->getAddress (pAddress, dstrAddrCode, 
               NULL_STRING, idDataGroup) <= WARNING &&
            pAddress)
         {

            int i =0;
            while ( idCopyField[i] != ifds::NullFieldId )
            {
               DString dstrValue;
               pAddress->getField(idCopyField[i],dstrValue,idDataGroup,false);
               setFieldNoValidate(idCopyField[i],dstrValue,idDataGroup,false,true,false,false    );
               ++i;
            }

				//pack address lines
				int iAdj = 0;
				DString dstrValue;
				for(i = 2;i<7; i++)
				{
					dstrValue = NULL_STRING;
					if( i+iAdj > 6) break;
					do {
						getField(idCopyField[i + iAdj ],dstrValue,idDataGroup,false);
						if( dstrValue.strip() == NULL_STRING ) {
							iAdj++;
						}			
					}while (dstrValue.strip() == NULL_STRING && (i+iAdj <7 ) ); 
					setFieldNoValidate(idCopyField[i],dstrValue,idDataGroup,false,true,false,false);	
				}
				// clear address lines moved
				for( i=1; i<iAdj+1; i++ ) 
				{				
					setFieldNoValidate(idCopyField[6-iAdj + i],NULL_STRING,idDataGroup,false,true,false,false);			
				}

				//get sharehoder name if there is no name here
				DString name1,name2,name;
				getField(ifds::Name1,name1,idDataGroup,false);
				getField(ifds::Name2,name2,idDataGroup,false);
				name1.strip();name2.strip();
				
            if (NULL_STRING == name1 && 
               NULL_STRING == name2)
				{
					
               DString dstrAcctNum;

               getField (ifds::AccountNum, dstrAcctNum, idDataGroup, false);
					dstrAcctNum.strip();
			
               ChqName chqName (getWorkSession());

               if (chqName.init (dstrAcctNum) <= WARNING )
               {
                  DString Name1, Name2;

                  chqName.getField(ifds::Name1, Name1, idDataGroup, false ) ;
                  chqName.getField(ifds::Name2, Name2, idDataGroup, false ) ;

                  setFieldNoValidate (ifds::Name1, Name1, idDataGroup, 
                     false, true, false, false);
                  setFieldNoValidate (ifds::Name2, Name2, idDataGroup, 
                     false, true, false, false);
               }
            }
         }
         else { //clear all the field
            int i = 0;
            while(idCopyField[i] != ifds::NullFieldId )
            {
               setFieldNoValidate(idCopyField[i],NULL_STRING,idDataGroup,false,false,false,false);	
               ++i;
            }
         }
      }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************
SEVERITY SettlementTrade::loadFileProcessor( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadFileProcessor") );
   DString dstrTransType,dstrPaymethod,dstrCurrency,dstrSubstitue;
   getField(ifds::TransType,dstrTransType,idDataGroup,false);
   getField(ifds::PayMethod,dstrPaymethod,idDataGroup,false);
   getField(ifds::SettleCurrency,dstrCurrency,idDataGroup,false);
   if ( dstrTransType != PURCHASE )
   {
      dstrSubstitue = getMgmtCo().getDynamicSubListHolder()->getFileProcSubList(dstrTransType,dstrPaymethod,dstrCurrency);
      setFieldAllSubstituteValues( ifds::ACHProcessor, idDataGroup,dstrSubstitue );
	  if (DSTCommonFunctions::getMarket () == MARKET_IDS::CANADA)
	  {
		  setFieldNoValidate ( ifds::ACHProcessor, 
							   dstrSubstitue.substr(0,dstrSubstitue.find('=')), 
						       idDataGroup, 
							   false, 
							   true, 
							   true);
	  }
      //notifyObservers( ifds::ACHProcessor, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT eEventId, const DString&  hint )
   }
   else
      setFieldAllSubstituteValues( ifds::ACHProcessor, idDataGroup,NULL_STRING );
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************
SEVERITY SettlementTrade::doAddressRelatedChange( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doAddressRelatedChange") );
   DString dstrTransType, dstrPayType,dstrPayMethod;
   getField(ifds::TransType,dstrTransType,idDataGroup,false );
   getField(ifds::PayType,dstrPayType,idDataGroup,false );
   getField(ifds::PayMethod,dstrPayMethod,idDataGroup,false );
      
   DString dstrSearchType;

   Settlement* pSettlement = dynamic_cast<Settlement* >(getParent()->getParent() ); 
   pSettlement->getField(ifds::SearchType,dstrSearchType,idDataGroup,false);

   dstrSearchType.strip().upperCase();

   bool bPermit = pSettlement->hasPermissionForSearchType(dstrSearchType);
   bool bUpdate = isIndividual() && 
				(REDEMPTION == dstrTransType) && 
				bPermit && isAddressRelatedUpdateable(NULL_STRING,idDataGroup);;
   bool bUpdateEPA = isIndividual() && 
			(REDEMPTION == dstrTransType) && 
				bPermit && isAddressRelatedUpdateable(dstrSearchType,idDataGroup);

   bool bHasPermChangeAddrBank = hasPermChangeAddrBank();

   setFieldReadOnly( ifds::AddrCode,   idDataGroup, !bUpdateEPA);
   setFieldReadOnly( ifds::Name1,      idDataGroup, !bUpdateEPA || !bHasPermChangeAddrBank);
   setFieldReadOnly( ifds::Name2,      idDataGroup, !bUpdateEPA || !bHasPermChangeAddrBank);
   
   // following fields should not be restricted with EPA search type and few flags
   setFieldReadOnly( ifds::AddrLine1,  idDataGroup, !bUpdate || !bHasPermChangeAddrBank);
   setFieldReadOnly( ifds::AddrLine2,  idDataGroup, !bUpdate || !bHasPermChangeAddrBank);
   setFieldReadOnly( ifds::AddrLine3,  idDataGroup, !bUpdate || !bHasPermChangeAddrBank);
   setFieldReadOnly( ifds::AddrLine4,  idDataGroup, !bUpdate || !bHasPermChangeAddrBank);
   setFieldReadOnly( ifds::AddrLine5,  idDataGroup, !bUpdate || !bHasPermChangeAddrBank);
   setFieldReadOnly( ifds::PostalCode, idDataGroup, !bUpdate || !bHasPermChangeAddrBank);
   setFieldReadOnly( ifds::CountryCode,idDataGroup, !bUpdate || !bHasPermChangeAddrBank);   
   bool bRequired = bUpdate;

   setFieldRequired( ifds::AddrCode,      idDataGroup, bRequired );
   setFieldRequired( ifds::AddrLine1,     idDataGroup, bRequired );
   setFieldRequired( ifds::AddrLine2,     idDataGroup, bRequired );
   setFieldRequired( ifds::CountryCode,   idDataGroup, bRequired );
   setValidFlag(  ifds::AddrCode,  idDataGroup, !bRequired );
   setValidFlag(  ifds::AddrLine1,  idDataGroup, !bRequired );
   setValidFlag(  ifds::AddrLine2,  idDataGroup, !bRequired );
   setValidFlag(  ifds::CountryCode,  idDataGroup, !bRequired );

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY SettlementTrade::doBankRelatedChange( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doBankRelatedChange") );
   DString dstrTransType, dstrPayType,dstrPayMethod;
   getField(ifds::TransType,dstrTransType,idDataGroup,false );
   getField(ifds::PayType,dstrPayType,idDataGroup,false );
   getField(ifds::PayMethod,dstrPayMethod,idDataGroup,false );

   bool bRequired;
   bRequired = ( (REDEMPTION == dstrTransType) &&
                 ((I_("DDER") == dstrPayMethod &&
                   DIRECT_DEPST_REDEMPTION == dstrPayType &&
                   DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA) ||
                   (I_("CHQ") != dstrPayMethod &&
                   EFT == dstrPayType )) || 
                   ( (PURCHASE == dstrTransType)   && 
                   (I_("WIRE") == dstrPayMethod) && 
                   (EFT == dstrPayType) ) );  

   bRequired = isIndividual() && bRequired;

   setFieldRequired( ifds::BankIdType, idDataGroup, bRequired );
   setFieldRequired( ifds::BankAcctNum,   idDataGroup, bRequired );
   setFieldRequired( ifds::BankIdValue,   idDataGroup, bRequired );
   setFieldReadOnly( ifds::BankIdType, idDataGroup, true );
   setFieldReadOnly( ifds::BankIdTypeCB, idDataGroup, true );
   setFieldReadOnly( ifds::BankIdValue,   idDataGroup, true );
   setFieldReadOnly( ifds::BankIdValueCB, idDataGroup, true );
   setFieldReadOnly( ifds::InstName,   idDataGroup, true );

   setValidFlag(  ifds::BankIdType,  idDataGroup, false );
   setValidFlag(  ifds::BankAcctNum,  idDataGroup, false );
   setValidFlag(  ifds::BankIdValue,  idDataGroup, false );
   
   if(!bRequired)
   {
      //clear the banking fields
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
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementTrade::bankChrgsRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("bankChrgsRelatedChanges"));

   //set the correct bank charges flag, read default again from account
   DString bankCharge (I_("0"));

   DString payMethod, payType, dstrAccountNum;

   getField (ifds::PayType, payType, idDataGroup, false);
   getField (ifds::PayMethod, payMethod, idDataGroup, false);

   if( (payMethod != I_("CHQ") )  &&  (payType == EFT || payType == DIRECT_DEPST_REDEMPTION) )
   {
      getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
      MFAccount* pMFAccount = NULL;
      getWorkSession().getMFAccount( idDataGroup, const_cast<DString&>(dstrAccountNum), pMFAccount); 
      if ( pMFAccount )
      {
         pMFAccount->getField(ifds::BankChrgs, bankCharge, idDataGroup, false);
         bankCharge.strip();
      }
   }

   if (!bankCharge.empty())
   {
      setFieldNoValidate ( ifds::BankChrgs, bankCharge, idDataGroup, false,
                           true,
                           true, //side effect
                           false);
   }

   bool bIsBankChrgsUpdatable =  ( payType != EFT ) && 
                                 ( payType != DIRECT_DEPST_REDEMPTION );

   //bank charges should be updatable if pay type is 'E'
   setFieldReadOnly ( ifds::BankChrgs, idDataGroup, bIsBankChrgsUpdatable );
   return GETCURRENTHIGHESTSEVERITY ();
}
//***************************************************************************************
SEVERITY SettlementTrade::validateGNSettl( const DString& dstrValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateGNSettl") );
   DString dstrTransType,dstrAccountNum,dstrAcctDesignation;

   getField(ifds::TransType,dstrTransType,idDataGroup,false);
   dstrTransType.strip();
   getField(ifds::AccountNum,dstrAccountNum,idDataGroup);
   MFAccount* pMFAccount = NULL;
   getWorkSession().getMFAccount( idDataGroup, const_cast<DString&>(dstrAccountNum), pMFAccount); 
   if ( pMFAccount )
   {
      pMFAccount->getField(ifds::AcctDesignation,dstrAcctDesignation,idDataGroup,false);
      dstrAcctDesignation.strip();
   }
   DString dstrBrokerCode,dstrBrokerNetAllowed;
   getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false);



   BrokerList *pBrokerList;
   Broker *pBroker = NULL;
   if ( dstrBrokerCode != NULL_STRING && getWorkSession().getBrokerList(pBrokerList) <= WARNING &&
        pBrokerList->getBroker(dstrBrokerCode, pBroker) <= WARNING && pBroker )
   {
      pBroker->getField(ifds::NetAllowed,dstrBrokerNetAllowed,idDataGroup,false);

   }

   FundMasterList* pFundMastList;

   SEVERITY sevRtn1 = getMgmtCo().getFundMasterList( pFundMastList );
   BFObjIter iter( *pFundMastList, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   DString dstrFundCode,dstrFundNetAllowed;
   getField(ifds::FundCode,dstrFundCode,idDataGroup,false );
   dstrFundCode.strip();
   if ( iter.positionByKey(dstrFundCode) )
   {
      iter.getObject()->getField(ifds::NetAllowed,dstrFundNetAllowed,idDataGroup,false);
   }

   bool bOK = true;
   if ( dstrTransType == REDEMPTION && dstrAcctDesignation == I_("1") ||
        dstrTransType == PURCHASE &&  dstrBrokerNetAllowed == NO && dstrFundNetAllowed == NO )
   {
      if ( dstrValue == NET )
      {
         ADDCONDITIONFROMFILE( CND::ERR_Net_SETTLEMENT_NOT_ALLOWED );
         bOK = false;
         //addcondition here
         //return	
      }
   }

   if( _dstrGNSettle != dstrValue && bOK )
   {
      _dstrGNSettle = dstrValue;
      DString settle;
      getField(ifds::Settled,settle,idDataGroup,false);
      if( settle.strip().upperCase() == YES )
      {
         if(dstrTransType == REDEMPTION && isSettleRedemptionAllowed( idDataGroup ) || dstrTransType != REDEMPTION )
         {
            Settlement* pSettlement = dynamic_cast<Settlement* >(getParent()->getParent() );
            pSettlement->UserChangeSettle( this,ifds::GNSettle,idDataGroup );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY SettlementTrade::copyAddress( const DString& dstrKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("copyAddress") );
   Shareholder* pShareholder = NULL;
   DString dstrShrNum;
   const BFFieldId idCopyField[] = {ifds::AddrCode,
      ifds::Name1,
      ifds::Name2,
      ifds::AddrLine1,
      ifds::AddrLine2,
      ifds::AddrLine3,
      ifds::AddrLine4,
      ifds::AddrLine5,
      ifds::PostalCode,
      ifds::CountryCode,
      ifds::NullFieldId };

   getField(ifds::ShrNum,dstrShrNum,idDataGroup,false);
   dstrShrNum.strip();
   getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder );
   if ( pShareholder )
   {
      AddressList* pAddressList = NULL;
      pShareholder->getAddressList( pAddressList, idDataGroup );
      if ( pAddressList )
      {
         BFObjIter iter( *pAddressList, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
         iter.positionByKey( dstrKey);
         BFAbstractCBO* pCBO = iter.getObject();
         if ( pCBO )
         {
            int i=0;
            DString dstrValue;
            while ( idCopyField[i] != ifds::NullFieldId )
            {
               pCBO->getField(idCopyField[i],dstrValue,idDataGroup,false);
               setFieldNoValidate(idCopyField[i],dstrValue,idDataGroup,false,true,false,false);
               ++i;
            }
         }
      }
   }


   int iAdj = 0;
   DString dstrValue;
   for(int i = 3;i<7; i++)
   {
      dstrValue = NULL_STRING;
      if( i+iAdj > 6) break;
      do {
         getField(idCopyField[i + iAdj ],dstrValue,idDataGroup,false);
         if( dstrValue.strip() == NULL_STRING ) {
            iAdj++;
         }
      }while (dstrValue.strip() == NULL_STRING && (i+iAdj <7 ) ); 

      setFieldNoValidate(idCopyField[i],dstrValue,idDataGroup,false,true,false,false);	
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementTrade::getBankInstructionsList (SettlementTradeBankInstructionsList *&pSettlementTradeBankInstructionsList, 
												   const BFDataGroupId& idDataGroup, 
												   bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));

   // Adding PayMethod value to ObjectKey to handle bank details for different PayMethod
   DString dstrPaymethod;
   getField(ifds::PayMethod, dstrPaymethod, idDataGroup);

   BFObjectKey objKey(I_("SettlementTrade_BankInstructionsList;PayMethod=") + dstrPaymethod, idDataGroup, 
      OBJ_ACTIVITY_NONE, OBJ_TYPE_NONE);

   pSettlementTradeBankInstructionsList = NULL;
   pSettlementTradeBankInstructionsList = 
      dynamic_cast<SettlementTradeBankInstructionsList *>(findObject(objKey));
   if (!pSettlementTradeBankInstructionsList && bCreate)
   {
      pSettlementTradeBankInstructionsList = new SettlementTradeBankInstructionsList(*this);
      if (pSettlementTradeBankInstructionsList)
      {
         DString accountNum;

         getField (ifds::AccountNum, accountNum, idDataGroup, false);

         if (pSettlementTradeBankInstructionsList->initNew (accountNum, idDataGroup) <= WARNING)
         {
            setObject(objKey, pSettlementTradeBankInstructionsList);
         }
         else
         {
            delete pSettlementTradeBankInstructionsList;
            pSettlementTradeBankInstructionsList = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void SettlementTrade::setSettledUpdated( const BFDataGroupId& idDataGroup, bool val )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setSettledUpdated") );

   setUpdatedFlag( ifds::Settled, idDataGroup, val );
}

//******************************************************************************

SEVERITY SettlementTrade::validateInternationalWire (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateInternationalWire" ) );

   return NO_CONDITION;//~IntWireStuff~

   bool bIsInternationalWire = false;
   DString strFundCode, strClassCode, strSettleCurrency, strCountryCode;
   getField(ifds::FundCode, strFundCode, idDataGroup, false);
   getField(ifds::ClassCode, strClassCode, idDataGroup, false);
   getField(ifds::SettleCurrency, strSettleCurrency, idDataGroup, false);
   getField(ifds::BankCountry, strCountryCode, idDataGroup, false);
   BankInstructionsList::isInternationalWire(*this, strFundCode, strClassCode, strSettleCurrency, strCountryCode, bIsInternationalWire);
   if ( bIsInternationalWire )
   {
      if ( !BankInstructions::isCorrBankInfoEntered(this, idDataGroup) )
         ADDCONDITIONFROMFILE( CND::ERR_CORR_BANK_FIELDS_SHOUD_BE_ENTERED );
   }
   else if ( !BankInstructions::isCorrBankInfoEmpty(this, idDataGroup) )//domestic
      ADDCONDITIONFROMFILE( CND::ERR_CORR_BANK_SHOULD_BE_EMPTY );
   return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
bool SettlementTrade::hasPermChangeAddrBank( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("hasPermChangeAddrBank") );

   bool PermCreate = true;
   bool PermUpdate = true;

   PermCreate = getWorkSession().hasUpdatePermission( UAF::SETTLE_PAY_INSTRUCTION );
   PermUpdate = getWorkSession().hasCreatePermission( UAF::SETTLE_PAY_INSTRUCTION );

   //return PermCreate && PermUpdate;
   return PermUpdate;
}

//*******************************************************************************************
SEVERITY SettlementTrade::validateAddressCode( const DString dstrAddrCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAddress" ));

   //bool  PermCreate = true;
   //PermCreate = getWorkSession().hasUpdatePermission( UAF::SETTLE_PAY_INSTRUCTION );
   if(!hasPermChangeAddrBank())
   {
      DString dstrShrNum;
      getField(ifds::ShrNum,dstrShrNum,idDataGroup,false);
      dstrShrNum.strip();
      Shareholder* pShareholder = NULL;
      getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder );
      if ( pShareholder )
      {
         AddressList* pAddressList = NULL;
         pShareholder->getAddressList( pAddressList, idDataGroup );
         if ( pAddressList )
         {
            Address* pAddress = NULL; 

            if (pAddressList->getAddress (pAddress, dstrAddrCode, 
               NULL_STRING, idDataGroup) > WARNING || 
               !pAddress )
            {
               DString error = I_( "" );
               addIDITagValue( error, I_("CODE"), dstrAddrCode );
               ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_SETUP, error );
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
bool SettlementTrade::isSettleRedemptionAllowed(const BFDataGroupId& idDataGroup )
{
   DString dstrStopSettle;
   getField(ifds::StopRedSettle,dstrStopSettle,idDataGroup,false );
   dstrStopSettle.strip();

   return (dstrStopSettle == NO );
}

//*******************************************************************************************
SEVERITY SettlementTrade::validateStopRedemption(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateStopRedemption" ));   

   DString dstrTransType,dstrSettle,dstrSettleAll;
   getField(ifds::TransType,dstrTransType, idDataGroup,false);
   if ( dstrTransType == REDEMPTION )
   getField(ifds::Settled,dstrSettle, idDataGroup,false);
   dstrSettle.strip().upperCase();
   getParent()->getField( ifds::SettleAll,dstrSettleAll,idDataGroup,false );  
   dstrSettleAll.strip().upperCase();
   SettlementTradeList* pList =  dynamic_cast<SettlementTradeList* >(getParent() );
   if( dstrTransType == REDEMPTION && dstrSettle == YES && !isSettleRedemptionAllowed( idDataGroup ) )
   {
      if(dstrSettleAll == YES && userChangeFields( idDataGroup ) == false  && 
         pList->doYouHaveLegalToSettle( idDataGroup )  )
      {
         ADDCONDITIONFROMFILE( CND::WARN_STOP_SETTLE_REDEMPTION );				
      }
      else 
      {
         ADDCONDITIONFROMFILE( CND::ERR_STOP_SETTLE_REDEMPTION );					 
      }   
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
SEVERITY SettlementTrade::validateSettledUnitsForRedemption( const DString &dstrSettled,
                                                             const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateSettledUnitsForRedemption" ));   

   if ( isCheckSettledUnitsForRedemptionApplicable( dstrSettled, idDataGroup )  )
	{
		DString dstrCurrentBusinessDate;
		getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );
		
		DString dstrAccountNum;
		getField(ifds::AccountNum, dstrAccountNum, idDataGroup );
		MFAccount* pMFAccount = NULL;
		if ( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum , pMFAccount ) &&
			NULL != pMFAccount )
		{
			MFAccountHoldingList *pMFAccountHoldingList = NULL;
			if ( pMFAccount->getAccountHoldingsAsOfDate( dstrCurrentBusinessDate, 
				                                         pMFAccountHoldingList,
														 idDataGroup ) <= WARNING &&
                 NULL != pMFAccountHoldingList )
			{
				DString dstrFundCode, dstrClassCode;
				getField( ifds::FundCode,  dstrFundCode,  idDataGroup );
				getField( ifds::ClassCode, dstrClassCode, idDataGroup );
				double dSettledUnits = pMFAccountHoldingList->getSettledFundBalanceForAmtType( dstrFundCode,
					                                                                           dstrClassCode,
																	                           I_( "U" ),
																		                       idDataGroup );
				
				// For Redemption, Units is a negative number;
				DString dstrSettlementTradeUnits;
				getField( ifds::Units, dstrSettlementTradeUnits, idDataGroup );
				double dSettlementTradeUnits = DSTCommonFunctions::convertToDouble( dstrSettlementTradeUnits );

				if ( dSettledUnits + dSettlementTradeUnits < 0 )
				{
					// Insufficient account holdings due to unsettled units. 
					ADDCONDITIONFROMFILE( CND::ERR_SETTLEMENT_INSUFFICIENT_SETTLED_UNITS );	
				}
			}			
		}
    }
    
   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************************
bool SettlementTrade::isCheckSettledUnitsForRedemptionApplicable( const DString &dstrSettled, 
                                                                  const BFDataGroupId& idDataGroup )
{
	bool bCheckUnsettled = false;
	
	DString dstrLocalSettled( dstrSettled), dstrSettleAll, dstrTransType;         
	getParent()->getField( ifds::SettleAll, dstrSettleAll, idDataGroup, false );  
	getField( ifds::TransType, dstrTransType, idDataGroup, false );

	if ( I_( "Y" ) == dstrLocalSettled.strip().upperCase() &&
		 I_( "N" ) == dstrSettleAll.strip().upperCase() &&
		 REDEMPTION == dstrTransType.strip().upperCase() )
	{
		DString dstrActCatNegBal, dstrActCatWireSett ;        		
		getWorkSession().getOption( ifds::ActCatNegBal, dstrActCatNegBal, idDataGroup, false );	
		getWorkSession().getOption( ifds::ActCatWireSett, dstrActCatWireSett, idDataGroup, false );	
		
		if ( dstrActCatNegBal != I_( "" )  || 
			dstrActCatNegBal   != I_( "*" ) ||
			dstrActCatWireSett != I_( "" )     )
			
		{

			DString dstrAccountNum;
			getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
			MFAccount *pMFAccount = NULL;       
			if ( getWorkSession().getMFAccount( idDataGroup, 
												dstrAccountNum, 
												pMFAccount ) <= WARNING &&
				 NULL != pMFAccount )
			{
				DString dstrAcctCategoryExist;
				bool bInActCatNegBalList = false, bInActCatWireSettList = false ;


				pMFAccount->getField( ifds::AcctCategoryExist, dstrAcctCategoryExist, idDataGroup );
				
				if ( I_( "Y" ) == dstrAcctCategoryExist.strip().upperCase() )
				{
					AcctCategoryList *pAccountCategoryList = NULL;
					if ( pMFAccount->getAcctCategoryList( pAccountCategoryList, 
														  idDataGroup ) <= WARNING &&
					     NULL != pAccountCategoryList )	
					{
						BFObjIter iterAccountCategory( *pAccountCategoryList, 
                                                       idDataGroup, 
                                                       false, 
                                                       BFObjIter::ITERTYPE::NON_DELETED );                       

						DString dstrAcctCategory;

						while (!iterAccountCategory.end())
						{
					   	iterAccountCategory.getObject()->getField (	ifds::AcctCategory, 
																						dstrAcctCategory, 
																						idDataGroup, 
																						false );
							
							if ( isCodeInList( dstrAcctCategory, dstrActCatWireSett ) )
							{
								bInActCatWireSettList = true;
								break;
							}
														
							++iterAccountCategory;
						}
					

						while (!iterAccountCategory.end())
						{
							iterAccountCategory.getObject()->getField (	ifds::AcctCategory, 
																						dstrAcctCategory, 
																						idDataGroup, 
																						false );
							

							if ( isCodeInList( dstrAcctCategory, dstrActCatNegBal ) )
							{
								bInActCatNegBalList = true;
								break;
							}
														
							++iterAccountCategory;
						}
					}
				}

				if ( ( dstrActCatWireSett == I_( "*" ) && !bInActCatNegBalList ) ||
							(bInActCatWireSettList && !bInActCatNegBalList) )
				{
					bCheckUnsettled = true;
				}
			}
		}		
	}

	return bCheckUnsettled;
}


//**********************************************************************************************
bool SettlementTrade::userChangeFields(const BFDataGroupId& idDataGroup )
{

   const BFFieldId fieldId[] = {ifds::AddrCode,
      ifds::Name1,
      ifds::Name2,
      ifds::AddrLine1,
      ifds::AddrLine2,
      ifds::AddrLine3,
      ifds::AddrLine4,
      ifds::AddrLine5,
      ifds::PostalCode,
      ifds::CountryCode,
      ifds::DeliveryMethod,
      ifds::SettledBy,
      ifds::PayType,
      ifds::SuppressCode,
      ifds::PayMethod,
      ifds::ValueDate,
      ifds::ACHProcessor,
      ifds::BankChrgs,
      ifds::BankIdTypeCB,
      ifds::BankIdType,
      ifds::NullFieldId };

   int i=0;
   while( fieldId[i] != ifds::NullFieldId )
   {
      if( isFieldUpdated( fieldId[i],idDataGroup ) )
      {
         return true;
      }
      i++;
   }

   return false;
}

//**********************************************************************************************
SEVERITY SettlementTrade::doValidateAll (const BFDataGroupId &idDataGroup, 
                                         long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   DString dstrSettle;
   getParent()->getField( ifds::SettleAll,dstrSettle,BF::HOST,false );  

   DString dstrWireOrdNum, dstrPayType, dstrPayMethod;
   getField( ifds::WireOrdNum, dstrWireOrdNum, idDataGroup, false );
   getField( ifds::PayType,dstrPayType,idDataGroup,false);
   getField( ifds::PayMethod, dstrPayMethod, idDataGroup);

   dstrWireOrdNum.strip().upperCase();
   dstrPayType.strip().upperCase();
   dstrPayMethod.strip().upperCase();

   // if trade which is going to be settled is wire order trade
   // and linked with banking instruction(payment method is 'wire') 
   // need to be validated against bank verifation status
   if ( I_("E") == dstrPayType && !dstrWireOrdNum.empty())
   {
      if ( I_("WIRE") == dstrPayMethod || I_("EFT") == dstrPayMethod )
      {
         validateBankVerifyStatus (idDataGroup);
      }
   }

   if (dstrSettle == YES && hasTRXRs && _dstrSearchType != SETTLE_DATE)
   {
      ADDCONDITIONFROMFILE (CND::WARN_SETTLE_ALL);
   }

   validateStopTradeSettlement(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementTrade::validateBankVerifyStatus (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBankStatus"));

   SettlementTradeBankInstructionsList *pSettlementTradeBankInstructionsList = NULL;

   bool	bVerificationEnabled;

   getWorkSession ().isVerificationEnabled (idDataGroup, BANKING_LEVEL, SHAREHOLDER, bVerificationEnabled);   

   //if (!bVerificationEnabled)
   //   return GETCURRENTHIGHESTSEVERITY ();

   if (getBankInstructionsList (pSettlementTradeBankInstructionsList, idDataGroup) <= WARNING &&
      pSettlementTradeBankInstructionsList)
   {
      BFObjIter iter (*pSettlementTradeBankInstructionsList, idDataGroup);

      if (!iter.end()) //the bank list has only one item
      {
         DString dstrVerifyStatus, acctID;

         iter.getObject() ->getField (ifds::VerifyStat, dstrVerifyStatus, idDataGroup);
         iter.getObject() ->getField (ifds::AcctID, acctID, idDataGroup);

         setFieldNoValidate (ifds::BnkAcctIDLink, acctID, idDataGroup);

         if (dstrVerifyStatus == UNVERIFIED)
         {
            getErrMsg ( IFASTERR::UNVERIFIED_BANK_SETTLEMENT, 
                        CND::ERR_UNVERIFIED_BANK, 
                        CND::WARN_UNVERIFIED_BANK, 
                        idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY SettlementTrade::validateAddrVerifyStatus( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("validateAddrVerifyStatus"));

   // check whether address is verified or not
   DString dstrShrNum, dstrAddrCode;
   getField(ifds::ShrNum,dstrShrNum,idDataGroup,false);
   getField(ifds::AddrCode,dstrAddrCode,idDataGroup,false);

   dstrShrNum.strip();
   dstrAddrCode.stripTrailing();

   Shareholder* pShareholder = NULL;
   getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder );
   if ( pShareholder )
   {
      AddressList* pAddressList = NULL;
      pShareholder->getAddressList( pAddressList, idDataGroup );
      if ( pAddressList )
      {
         Address* pAddress = NULL; 

         if (pAddressList->getAddress (pAddress, dstrAddrCode, 
                                       NULL_STRING, 
                                       idDataGroup) <= WARNING && 
               pAddress )
         {
            DString dstrVerifyStat;
            pAddress->getField( ifds::VerifyStat, dstrVerifyStat, idDataGroup, false );
            if( dstrVerifyStat == UNVERIFIED)
            {
               DString dstrIDI;
               addIDITagValue (dstrIDI, I_("OPERATION"), I_("Trade Settle"));
               getErrMsg ( IFASTERR::SHAREHOLDER_ADDRESS_NOT_VERIFIED_FOR_SETTLEMENT, 
                           CND::ERR_ADDRESS_NOT_VERIFY, 
                           CND::WARN_ADDRESS_NOT_VERIFY, 
                           idDataGroup,
                           dstrIDI);
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY SettlementTrade::validatePayTypeForEPATrade(const DString &strValue,const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("validatePayTypeForEPATrade"));

   DString dstrOrigPayType;
   getFieldBeforeImage( ifds::PayType, dstrOrigPayType );
   DString dstrPayType = strValue;
   DString dstrSearchType = _dstrSearchType;

   dstrOrigPayType.strip().upperCase();
   dstrPayType.strip().upperCase();

   DString strEftToChqAllowed;
   getField( ifds::EftToChqAllowed, strEftToChqAllowed, idDataGroup, false );
   strEftToChqAllowed.strip().upperCase();

   if(strEftToChqAllowed == I_("N"))
   {
      if( dstrPayType == I_("S") && dstrOrigPayType == I_("E") )
      {
         ADDCONDITIONFROMFILE (CND::ERR_EFT_TO_CHQ_NOT_ALLOWED);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
bool SettlementTrade::isAddressRelatedUpdateable(const DString& dstrValue, const BFDataGroupId &idDataGroup)
{
   DString allowChqChange,
      dstrSearchType(dstrValue),
      dstrTransType, 
      dstrPayType,
      dstrPayMethod;

   bool bResult = false;

   getField(ifds::TransType,dstrTransType,idDataGroup,false );
   getField(ifds::PayType,dstrPayType,idDataGroup,false );
   getField(ifds::PayMethod,dstrPayMethod,idDataGroup,false );

   dstrTransType.strip().upperCase();
   dstrPayType.strip().upperCase();
   dstrPayMethod.strip().upperCase();
   dstrSearchType.strip().upperCase();

   getWorkSession().getOption( ifds::AllowChqChange, allowChqChange, idDataGroup, false );
   allowChqChange.strip().upperCase();

   if( dstrPayType == I_("S") )
   {
      if ( dstrSearchType != EPA_BROKER )
      {
         bResult = true;
      }
      else
      {
         bResult = (allowChqChange == I_("Y"));
      }
   }
   else if (dstrPayType == I_("E"))
   {
      bResult = (I_("CHQ") == dstrPayMethod);
   }

   return bResult;
}

//*****************************************************************************
SEVERITY SettlementTrade::validateSettledForEPATrade(const DString& dstrValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("validateSettledForEPATrade"));

   DString dstrSearchType;

   Settlement* pSettlement = dynamic_cast<Settlement* >(getParent()->getParent() );

   if( pSettlement )
   {
      pSettlement->getField(ifds::SearchType,dstrSearchType,idDataGroup,false);

      dstrSearchType.strip().upperCase();

      if ( dstrSearchType == EPA_BROKER )
      {
         DString dstrCurBusDate, settleDate, settle;
         getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
         getField(ifds::SettleDate,settleDate,idDataGroup,false);
         settle = dstrValue;
         settle.strip().upperCase();

         if ( DSTCommonFunctions::CompareDates( settleDate, dstrCurBusDate ) == DSTCommonFunctions::SECOND_EARLIER && 
              settle == YES )
         {
            ADDCONDITIONFROMFILE( CND::ERR_SETTLE_FUTURE_TRADE_NOT_ALLOWED_FOR_EPA_TRADE );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

/******************************************************************************
Input:DataGroupID
OutPut:DString with traderoutingtype list
Return:Severity
Functionality:Returns the valid list for tradelevel routing over-ride
******************************************************************************/
SEVERITY SettlementTrade::buildPaymentRoutingSet(const BFDataGroupId &idDataGroup,DString &outdstrpymtLevelRoutingSet)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("buildPaymentRoutingSet"));
	DString dstrTradelevelOveride,dstrPymtRoutingMthd,dstrPymtRoutingMthdSet;
	getWorkSession ().getOption (ifds::TradelevelOveride,dstrTradelevelOveride,BF::HOST,false); 
	getWorkSession ().getOption (ifds::PymtRoutingMthd,dstrPymtRoutingMthd,BF::HOST,false); 
	BFProperties *pBFProperties=
      getFieldProperties (ifds::PymtRoutingMthd, idDataGroup); 
    assert (pBFProperties);
    if (pBFProperties)
    {
      pBFProperties->getAllSubstituteValues (dstrPymtRoutingMthdSet);
    } 
	outdstrpymtLevelRoutingSet.stripAll();
	dstrPymtRoutingMthdSet.stripAll();
	if(	dstrTradelevelOveride != YES || 
		dstrPymtRoutingMthd.empty()  ||
		dstrPymtRoutingMthdSet.empty() )
	{
		outdstrpymtLevelRoutingSet = NULL_STRING;
		outdstrpymtLevelRoutingSet.stripAll();
		return GETCURRENTHIGHESTSEVERITY();
	}
    I_CHAR *temp = const_cast<I_CHAR*> (dstrPymtRoutingMthdSet.c_str ());
    do
    {
         DString dstrPymtRoutingMthdSetCode,dstrPymtRoutingMthdSetDescr;   
         temp = parseIdiString (temp, dstrPymtRoutingMthdSetCode, dstrPymtRoutingMthdSetDescr);         
         if (isCodeInList (dstrPymtRoutingMthdSetCode,dstrPymtRoutingMthd))
         {
            outdstrpymtLevelRoutingSet += dstrPymtRoutingMthdSetCode + I_("=") + 
				                          dstrPymtRoutingMthdSetDescr + I_(";");
         }
    } while (temp && temp != NULL_STRING && *temp);

	 return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
Input:DataGroupID
OutPut:None
Return:Severity
Functionality:Sets the default value for the TradeLevelRouting
******************************************************************************/
SEVERITY SettlementTrade::setPaymentRoutingSetDefault( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("setPaymentRoutingSetDefault"));
   DString dstrAccountNum; 
   getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
   MFAccount *pMFAccount = NULL; 
   if ( getWorkSession ().getMFAccount ( idDataGroup, dstrAccountNum, 
                                          pMFAccount ) <= WARNING && NULL != pMFAccount)
   {
         DString dstrAcctType; 
	     AcctCategoryList *pAcctCategoryList = NULL;
         if ( pMFAccount->getAcctCategoryList( pAcctCategoryList, 
                                              idDataGroup ) <= WARNING &&
             NULL != pAcctCategoryList )
         {
		    DString dstrDefaultPymtRoutingMthd = NULL_STRING;
			BFObjIter iter (*pAcctCategoryList, idDataGroup);
            while (!iter.end ())
            {
              DString acctCategory;                     
              iter.getObject () ->getField (ifds::AcctCategory, acctCategory, idDataGroup, false);
              if (acctCategory == SWIFT_PAYMENT_METHOD)
                {
                    iter.getObject ()->getField(ifds::CatValue, dstrDefaultPymtRoutingMthd, idDataGroup, false) ;
                    break;
                }
               ++iter;
             }
			dstrDefaultPymtRoutingMthd.stripAll();
			if(dstrDefaultPymtRoutingMthd.empty())
			{
				pMFAccount->getField(ifds::AcctType, dstrAcctType, idDataGroup, false) ;
				if (isCodeInList(dstrAcctType,ACCOUNT_TYPE::INDIVIDUAL_ACCT_LIKE))
				{
					dstrDefaultPymtRoutingMthd = PAYMENT_ROUTING::MT103;
				}
				else if (isCodeInList(dstrAcctType,ACCOUNT_TYPE::CORPORATE_ACCT_LIKE))
				{
					dstrDefaultPymtRoutingMthd = PAYMENT_ROUTING::MT202;
				}
				else
				{
					//what other acount types do we have?
					assert (0);
				}
			}
			setFieldNoValidate (ifds::PymtRoutingMthd, dstrDefaultPymtRoutingMthd, 
								idDataGroup, false, true, true);
         }
      
   }
   return GETCURRENTHIGHESTSEVERITY(); 
}
/******************************************************************************
 Input: IdField,dataGroup,Formatted Return
 OutPut:strFieldValue
 Return:None
 Functionality:	Const function that returns the Fund ID value for the idField
 ******************************************************************************/
void SettlementTrade::getField( const BFFieldId& idField, DString& strFieldValue, const BFDataGroupId& idDataGroup, 
                           bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
   if( ifds::TDCC  == idField ||ifds::Valoren == idField || ifds::CUSIP == idField )
   {
    DString dstrFundCode,dstrClassCode;
	FundDetailList * pFundDetailList = NULL;
	getField( ifds::FundCode,dstrFundCode, idDataGroup, true );
	dstrFundCode.strip();
	getField( ifds::ClassCode,dstrClassCode, idDataGroup, true );
	dstrClassCode.strip();
	if( const_cast<MgmtCo &> (getMgmtCo()).getFundDetailList(pFundDetailList) <= WARNING &&
		pFundDetailList)
			pFundDetailList->getField(dstrFundCode, dstrClassCode, idField, strFieldValue,
									  idDataGroup, false);
   }
}


 //***********************************************************************************
SEVERITY SettlementTrade::validateStopTradeSettlement(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("validateStopTradeSettlement"));

	DString dstrSettleAll, dstrExcludeStopSettle;
	getParent()->getField(ifds::SettleAll, dstrSettleAll, idDataGroup);
	getParent()->getParent()->getField(ifds::ExcludeStopSettle, dstrExcludeStopSettle, idDataGroup);

	if (dstrSettleAll == Y && dstrExcludeStopSettle == N)
	{
		DString dstrTransId, dstrTradeRestriction;
		TransactionDetails *pTransactionDetails = NULL;

		if (getTransactionDetails(pTransactionDetails, idDataGroup) <= WARNING && pTransactionDetails)
		{
			pTransactionDetails->getField(ifds::TradeRestriction, dstrTradeRestriction, idDataGroup);
			
			if (dstrTradeRestriction == STOP_TRADE_SETTLEMENT)
			{
				DString dstrIDI, dstrSubList;
				BFProperties *pProperties = getFieldProperties(ifds::TradeRestriction, idDataGroup);
				
				if (pProperties)
				{
					pProperties->getAllSubstituteValues(dstrSubList);
				}

				addIDITagValue (dstrIDI, I_("REASON"), DSTCommonFunctions::getDescription(dstrTradeRestriction, dstrSubList));

				getErrMsg(IFASTERR::TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO,
					CND::ERR_TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO,
					CND::WARN_TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO,
					idDataGroup,
					dstrIDI);
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY(); 
}


//******************************************************************************
SEVERITY SettlementTrade::getTransactionDetails ( TransactionDetails *&pTransactionDetails,
                                                          const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransactionDetails"));

	pTransactionDetails = NULL;
	DString transId(NULL_STRING), dstrAccountNum;

	getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
	getField(ifds::TransId, transId, idDataGroup, false);
	DString strKey = I_("TransId=") + transId;

	TransactionList *pTransactionList = dynamic_cast <TransactionList*> (getObject (strKey, idDataGroup));

	if (!pTransactionList)
	{
		pTransactionList = new TransactionList (*this);
		if (pTransactionList->init ( dstrAccountNum, 
			NULL_STRING, 
			NULL_STRING,
			NULL_STRING,
			I_("N"),
			transId) <= WARNING && 
			pTransactionList)
		{
			//here we should only get one hit...
			BFObjIter bfIter (*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

			if (!bfIter.end())
			{
				pTransactionDetails = pTransactionList ->getItem (bfIter.getStringKey (), idDataGroup);
			}
		}
		else
		{
			delete pTransactionList;
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY SettlementTrade::validateCashDate ( const DString &cashDate, 
                                   const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
		CLASSNAME, 
		I_("validateCashDate"));

	DString fundCode, 
		classCode;

	DString dstrCashDate;
	getField (ifds::CashDate, dstrCashDate, idDataGroup);

	if (dstrCashDate != I_ ("12319999"))
	{
		getField (ifds::FundCode, fundCode,  idDataGroup);
		getField (ifds::ClassCode, classCode, idDataGroup);
		if (!fundCode.empty () && !classCode.empty ())
		{
			FundMasterList *pFundMasterList = NULL;
			if ( getMgmtCo ().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList)
			{
				FundMaster *pFundMaster = NULL;
				if ( pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster) && 
					pFundMaster &&
					isCashDateUpdatable (pFundMaster, idDataGroup))
				{
					DString nextSettleDate, 
						tradeDate;

					getField (ifds::TradeDate, tradeDate, idDataGroup);
					if ( getFundField ( fundCode, 
						classCode, 
						ifds::NextSettleDate, 
						nextSettleDate ) <= WARNING &&
						!DSTCommonFunctions::IsDateBetween (tradeDate, nextSettleDate, cashDate))
					{
						// 2240 - Invalid cash date.
						getErrMsg (IFASTERR::INVALID_CASH_DATE,
								   CND::ERR_INVALID_CASH_DATE,
								   CND::WARN_INVALID_CASH_DATE,
								   idDataGroup);	
					}

					if (DSTCommonFunctions::CompareDates (cashDate, tradeDate) == DSTCommonFunctions::FIRST_EARLIER)
					{
						// 2241 - Overridden cash date should be greater than or equal to trade date.
						getErrMsg (IFASTERR::CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE,
								   CND::ERR_CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE,
								   CND::WARN_CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE,
								   idDataGroup);
					}
				}
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
bool SettlementTrade::isCashDateUpdatable ( FundMaster *pFundMaster,
                                  const BFDataGroupId &idDataGroup)
{
   bool blUpdateable = false;
   DString fundType;

   pFundMaster->getField (ifds::FundType, fundType, BF::HOST, false); 
   fundType.strip().upperCase();
   if (fundType == FUND_TYPE::MONEY_MARKET) //money market fund
   {
      DString dividendType, 
         intFromDateType, 
         intToDateType;

      pFundMaster->getField (ifds::DividentType,    dividendType,    BF::HOST);
      pFundMaster->getField (ifds::IntFromDateType, intFromDateType, BF::HOST);
      pFundMaster->getField (ifds::IntToDateType,   intToDateType,   BF::HOST);

      dividendType.strip().upperCase();
      intFromDateType.strip().upperCase();
      intToDateType.strip().upperCase();
      blUpdateable = I_("S") == dividendType && 
                     I_("C") == intFromDateType || 
                     I_("C") == intToDateType;
   }

   DString cashDateOverride; 
   getWorkSession().getOption (ifds::OrderUserOverride, cashDateOverride, BF::HOST, false); // UserOverride attribute in PendingTradeCashDate function control: 01-no override, 02-override backdated trades, 03-override all 
   return (blUpdateable && DSTCommonFunctions::codeInList (cashDateOverride, I_("02,03")));

   return blUpdateable;
}
 //*****************************************************************************
SEVERITY SettlementTrade::getFundField ( const DString &fundCode, 
                               const DString &classCode, 
                               const BFFieldId &idField, 
                               DString &strValue)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
		CLASSNAME, 
		I_("getFundField"));
	//this method based on the given values of 'fund/class' code 
	//returns the value for the 'idField' from the FundDetail object
	FundDetail *pFundDetail = NULL;

	if ( getWorkSession().getFundDetail (fundCode, classCode, BF::HOST, pFundDetail) &&
		pFundDetail)
	{
		pFundDetail->getField (idField, strValue, BF::HOST, false);
		strValue.strip ().upperCase ();
	}
	return GETCURRENTHIGHESTSEVERITY ();
}
//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTrade.cpp-arc  $
// 
//    Rev 1.90   Feb 01 2011 14:45:18   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.89   Jan 22 2011 10:53:44   dchatcha
// IN# 2398106 - R11.2-PETP0175716FN02-EPA Futured dated trade got settled
// 
//    Rev 1.88   Jan 18 2011 18:08:34   dchatcha
// Compile error!...
// 
//    Rev 1.87   Jan 17 2011 18:45:24   dchatcha
// IN# 2390240 - For the EPA settlement screen user unable to change the EFT to S.
// 
//    Rev 1.86   Dec 14 2010 04:26:42   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement, revised an edit check.
// 
//    Rev 1.85   Dec 13 2010 06:15:50   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement, edit check is only for EPA Trade.
// 
//    Rev 1.84   Dec 02 2010 23:46:44   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.83   Dec 02 2010 15:39:54   jankovii
// PET171086 FN01 Red Flag Report
// 
//    Rev 1.82   Dec 01 2010 06:37:56   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.81   Jan 22 2010 10:43:22   dchatcha
// IN# 1982727 - User can not modify paytype "X" to "E" in DSK Settlement screen.
// 
//    Rev 1.80   Jan 13 2010 09:35:32   dchatcha
// IN# 1973754 - Unable to manually settle  w/o PW  after verifying shareholder addr, issue# 1. unverified banking instruction should not be validated against wire order trade linked with address.
// 
//    Rev 1.79   Dec 17 2009 15:02:22   popescu
// Incident 1950173 - validation triggered for banking at settlement level
// 
//    Rev 1.78   Dec 03 2009 02:58:10   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2.
// 
//    Rev 1.77   Nov 26 2009 13:42:44   jankovii
// PET0166583 FN01 Static Data Changes Banking 
// 
//    Rev 1.76   Sep 02 2009 22:14:06   dchatcha
// Synch up : Incident  1814032 - fixed disply of banking instructions for setltements.
// 
//    Rev 1.75   Aug 15 2009 12:38:22   dchatcha
// Synch up : PET 156681 - FN 14 - Investor Authorization, Settlement screen issue.
// 
//    Rev 1.74   Aug 04 2009 21:21:58   wutipong
// #1357237 Trade settled w/ no institiution and branch#. ECF
// 
//    Rev 1.73   Jul 22 2009 08:13:12   dchatcha
// PET156681 FN14 H36 Investor Authorization, Code review. 
// 
//    Rev 1.72   Jul 16 2009 19:22:20   dchatcha
// PET156681 FN14 H36 Investor Authorization, Integration issues.
// 
//    Rev 1.71   Jul 09 2009 15:01:54   dchatcha
// PET156681 FN14 H36 Investor Authorization.
// 
//    Rev 1.70   11 Jun 2008 10:33:08   popescu
// in#1283327 - Trade created with invalid settlement date, Code review regarding modification of Trade and DateValidation CBO.
// 
//    Rev 1.69   May 07 2008 14:17:32   wongsakw
// IN1218721 Bank information incorrectly Displayed
// 
//    Rev 1.68   Jan 10 2008 18:00:56   daechach
// in#1143330 - Delivery type Direct-ICS
// 
//    Rev 1.67   Aug 13 2007 11:45:22   smithdav
// Fix compile error.
// 
//    Rev 1.66   Aug 13 2007 11:40:08   smithdav
// PET 2360 FN.   Customize DeliveryMethod values for AIM
// 
//    Rev 1.65   Mar 21 2007 13:24:28   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.64   Oct 13 2006 10:12:46   AGUILAAM
// IN 688963 - changed validation to be exactly like SETL15.P; if either fund or broker allow net settlements, then net settlements will be allowed.
// 
//    Rev 1.63   Oct 24 2005 12:34:46   porteanm
// PET1250_FN09 : modified validation
// 
//    Rev 1.62   Oct 06 2005 17:39:42   AGUILAAM
// PET1250_FN09 : modified validation
// 
//    Rev 1.61   Sep 20 2005 12:15:26   AGUILAAM
// PET1250_FN09_Custody Client Accounts and Negative Balances; also fixed Refresh functionality for Settlements.
// 
//    Rev 1.60   Aug 03 2005 11:46:20   ZHANGCEL
// PET1280 -- Enhancement for SSBL Barclays bank charge field
// 
//    Rev 1.59   Apr 25 2005 17:48:28   ZHANGCEL
// PET 1190 - FN06 -- Settltment by TransNum enhancement
// 
//    Rev 1.58   Apr 12 2005 10:31:26   porteanm
// PET1190 FN14 - Wire order redemption against unsettled units.
// 
//    Rev 1.57   Mar 22 2005 16:45:40   ZHANGCEL
// Incident #269682 -- Change the order of parameters to match the method defination
// 
//    Rev 1.56   Dec 20 2004 10:06:40   yingbaol
// PTS10036028: clear addreee lines if it has been packed.
// 
//    Rev 1.55   Dec 08 2004 16:15:42   hernando
// PET910 - Added Field Info for StopDate.
// 
//    Rev 1.54   Nov 14 2004 14:54:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.53   Oct 12 2004 13:43:32   YINGBAOL
// PET10034502: add logic to issue critical error when user select "SettleAll" and all records are not allowed to settle.
// 
//    Rev 1.52   Sep 01 2004 10:53:18   YINGBAOL
// PET1124: Change transtype == PURCHASE to != Redemption as Winnie's suggestion
// 
//    Rev 1.51   Aug 31 2004 12:01:34   YINGBAOL
// PET1124:raise critical error if user change anything for concrate settlement.
// 
//    Rev 1.50   Aug 13 2004 13:55:42   YINGBAOL
// PET1027 StopRedeemption Settlement
// 
//    Rev 1.49   Jul 02 2004 14:48:20   AGUILAAM
// pts 10030921 - assign name1, name2 from new view 297 for settlement cheque
// 
//    Rev 1.48   May 20 2004 14:17:12   popescu
// PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
// 
//    Rev 1.47   Mar 02 2004 15:06:04   YINGBAOL
// PTS10025097:setPaytype to readonly for AMS rebalancing trade
// 
//    Rev 1.45   Feb 09 2004 10:15:44   FENGYONG
// PET965.FN1 SSB Profile restriction
// 
//    Rev 1.44   Dec 23 2003 11:39:52   VADEANUM
// PET892 FN1 - Trade Settlement Location support - Pay Type.
// 
//    Rev 1.43   Dec 18 2003 14:43:18   VADEANUM
// PET892 FN1 - Trade Settlement Location support 
// 
//    Rev 1.42   Nov 24 2003 10:45:52   popescu
// PTS 10024305, the name of the entity is displayed in the format 'FirstName LastName'  if client uses BAFF
// 
//    Rev 1.41   Oct 01 2003 09:33:20   YINGBAOL
// change settlement total logic PTS10018597
// 
//    Rev 1.40   Sep 10 2003 14:39:22   YINGBAOL
// add dstrGNSettleFlag.
// 
//    Rev 1.39   Jul 24 2003 09:46:30   YINGBAOL
// PTS10018597---recalculate total settlement when user change s the Gross/Net
// 
//    Rev 1.38   Jun 10 2003 16:11:20   popescu
// Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
// 
//    Rev 1.37   May 22 2003 14:13:06   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.36   Apr 24 2003 16:46:18   YINGBAOL
// if Name1 and Name2 is blank in shareholder address, assign accound holder's name to name1.
// 
//    Rev 1.35   Apr 10 2003 09:58:06   YINGBAOL
// Fix address display issue( view will return address for settlement)---PTS10013531
// 
//    Rev 1.34   Mar 21 2003 18:24:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.33   Feb 03 2003 14:45:24   ZHANGCEL
// fix incomplete sync up issue
// 
//    Rev 1.32   Jan 29 2003 16:59:34   ZHANGCEL
// fix uncompleted sync up issue
// 
//    Rev 1.31   Dec 11 2002 16:53:36   YINGBAOL
// fix individual Settlement
// 
//    Rev 1.30   Nov 07 2002 10:59:36   YINGBAOL
// Sync. from release 49
// 
//    Rev 1.32   Oct 24 2002 17:25:02   HSUCHIN
// bug fix .. BankIdTypeCB should also be ReadOnly
// 
//    Rev 1.31   Oct 23 2002 10:01:12   YINGBAOL
// fix PTS10010500
// 
//    Rev 1.30   Oct 18 2002 10:51:38   YINGBAOL
// if AddrCode is blank for wire, default to 01
// 
//    Rev 1.29   Oct 18 2002 10:32:54   YINGBAOL
// populate address line when change pay method
// 
//    Rev 1.28   Oct 04 2002 10:34:16   YINGBAOL
// sync. 1.23.1.1
// 
//    Rev 1.27   Sep 09 2002 12:16:02   KOVACSRO
// Sync-up PTS 10009768 : removed corr bank edit check 
// 
//    Rev 1.26   Aug 29 2002 12:56:38   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.25   Aug 16 2002 13:57:42   YINGBAOL
// add permission check
// 
//    Rev 1.24   Aug 13 2002 11:23:20   KOVACSRO
// Release 48 : fixed spelling.
// 
//    Rev 1.23   Aug 08 2002 16:42:32   YINGBAOL
// AddressCode enhancement
// 
//    Rev 1.22   Jul 29 2002 17:13:08   YINGBAOL
// add condition for Value date
// 
//    Rev 1.21   Jul 26 2002 17:08:50   YINGBAOL
// fix Gross Net validation
// 
//    Rev 1.20   Jul 19 2002 18:18:02   WINNIE
// Bug fix for Paymethod setting on required and default value; fix FileProcessor setting for EFT 
// 
//    Rev 1.19   Jul 19 2002 11:44:50   YINGBAOL
// take out setdefault value for GNSettle
// 
//    Rev 1.18   Jul 08 2002 17:26:48   YINGBAOL
// fix
// 
//    Rev 1.17   Jul 02 2002 15:29:18   YINGBAOL
// force to do validation for SettleBy and PayType
// 
//    Rev 1.16   Jun 28 2002 15:12:48   YINGBAOL
// add condition for net settlement
// 
//    Rev 1.15   Jun 28 2002 13:38:44   YINGBAOL
// add validate for address Line etc.
// 
//    Rev 1.14   Jun 27 2002 13:29:02   YINGBAOL
// more fix
// 
//    Rev 1.13   Jun 18 2002 16:40:50   HSUCHIN
// copy name1 to bankacctname when paymethod is switch to EFT and datagroup bug fix
// 
//    Rev 1.12   Jun 17 2002 17:02:34   YINGBAOL
// do not copy name1 and name2 from address and change SettleBy field substitute according to the market
// 
//    Rev 1.11   Jun 17 2002 16:08:34   YINGBAOL
// add more logic for ACHProcessor and Paymethod
// 
//    Rev 1.10   Jun 16 2002 14:08:20   HSUCHIN
// added international wire validation
// 
//    Rev 1.9   Jun 15 2002 15:47:52   YINGBAOL
// validate valuedate and change SettleMethod to SettleBy
// 
//    Rev 1.8   Jun 14 2002 16:27:02   YINGBAOL
// add ExpGNSettle
// 
//    Rev 1.7   Jun 14 2002 10:11:40   YINGBAOL
// set default value for Valuedate  and Stopdate
// 
//    Rev 1.6   Jun 13 2002 15:53:26   YINGBAOL
// change view 200 
// 
//    Rev 1.5   Jun 13 2002 09:51:56   VASILEAD
// Added setSettleUpdated()
// 
//    Rev 1.4   Jun 13 2002 09:22:34   HSUCHIN
// added settlementtradebanklist
// 
//    Rev 1.3   Jun 11 2002 11:42:40   YINGBAOL
// more business rules added
// 
//    Rev 1.2   Jun 06 2002 16:08:24   YINGBAOL
// save work
//



//