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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AWDCommon.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : 12 Jul 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : AWDCommon
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#pragma warning ( disable : 4503 ) 

#include "stdafx.h"
#include "awdcommon.hpp"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\addresslist.hpp>
#include <bfcbo\bfobjiter.hpp>
#include <bfproc\bpsessiontags.h>
#include <configmanager.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\entityidslist.hpp>
#include <ifastcbo\entitylist.hpp>
#include <bfproc\genericinterface.hpp>
#include <idistring.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\entity.hpp>
#include <uibase\oleglobal.hpp>
#include <bfdata\bffieldid.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastdbrkr\DSTCHost.hpp>

#include <bfsessn\bfcpsession.hpp>
#include <bfsessn\bfcpsessiontags.h>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <afxpriv.h>

// from MFAccount
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0011_vw.hpp>
#include <ifastdataimpl\dse_dstc0015_vw.hpp>
#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0091_vw.hpp>
#include <ifastdataimpl\dse_dstc0092_vw.hpp>
#include <ifastdataimpl\dse_dstc0088_vw.hpp>
#include <ifastdataimpl\dse_dstc0120_vw.hpp>
#include <ifastdataimpl\dse_dstc0142_vw.hpp>
#include <ifastdataimpl\dse_dstc0144_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
// From Trade
#include <ifastdataimpl\dse_dstc0147_req.hpp>
#include <ifastdataimpl\dse_dstc0147_vw.hpp>
#include <ifastdataimpl\dse_dstc0127_req.hpp>
#include <ifastdataimpl\dse_dstc0127_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0115_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_req.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
// From Address
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_req.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_vw.hpp>
// From Entity
#include <ifastdataimpl\dse_dstc0051_req.hpp>

namespace 
{
   const I_CHAR * const DRIVER_LICENSE       = I_( "01" );
   const I_CHAR * const PASSPORT             = I_( "02" );
   const I_CHAR * const BIRTH_CERTIFICATE    = I_( "03" );
   const I_CHAR * const CREDIT_CARD          = I_( "04" );
   const I_CHAR * const NATIONAL_ID          = I_( "05" );
   const I_CHAR * const SOCIAL_SEC_INS_CARD  = I_( "06" );
   const I_CHAR * const OTHER                = I_( "99" );
   const I_CHAR * WORKSTATION                = I_( "Workstation" );
   const I_CHAR * SETTINGS                   = I_( "Settings" );
   const I_CHAR * const ICHARS_Y             = I_( "Y" );
   const I_CHAR * const ICHARS_N             = I_( "N" );
   const I_CHAR * const ICHARS_DD            = I_( "DD" );
   const I_CHAR * const ICHARS_MM            = I_( "MM" );
   const I_CHAR * const ICHARS_YYYY          = I_( "YYYY" );
   const I_CHAR * const ICHARS_MINUS         = I_( "-" );
}

namespace AWD
{
   // Common
   extern const I_CHAR *Amount;
   extern const I_CHAR *Business_Area;
   extern const I_CHAR *Currency;
   extern const I_CHAR *Fund;
   extern const I_CHAR *Account_Num;   // Added to Lux

   // Canadian
   extern const I_CHAR *Shareholder_Num;
   extern const I_CHAR *Entity_ID;
   extern const I_CHAR *Phone_Num;
   extern const I_CHAR *Passport_Num;
   extern const I_CHAR *Social_Num;
   extern const I_CHAR *DL_Num;
   extern const I_CHAR *SIN_Num;
   extern const I_CHAR *Birth_Cert;
   extern const I_CHAR *Credit_Card;
   extern const I_CHAR *National_ID;
   extern const I_CHAR *Other;
   extern const I_CHAR *Broker_Code;
   extern const I_CHAR *Broker_Name;
   extern const I_CHAR *RepresentativeCode;
   extern const I_CHAR *RepresentativeName;
   extern const I_CHAR *Address1;
   extern const I_CHAR *Address2;
   extern const I_CHAR *Address3;
   extern const I_CHAR *Address4;
   extern const I_CHAR *Address5;
   extern const I_CHAR *Batch_Num;
   extern const I_CHAR *CSR_Phone;
   extern const I_CHAR *Caller_Name;
   extern const I_CHAR *Caller_Phone;
   extern const I_CHAR *Postal;
   extern const I_CHAR *Country;
   extern const I_CHAR *To_Account;
   extern const I_CHAR *From_Account;
   extern const I_CHAR *Entity_FName;
   extern const I_CHAR *Entity_LName;
   extern const I_CHAR *System_ID;
   extern const I_CHAR *Branch_Code;
   extern const I_CHAR *Group_Code;

   // Lux
   extern const I_CHAR *Trade_Date;
   extern const I_CHAR *Settlement_Date;
   extern const I_CHAR *Reference_Number;
   extern const I_CHAR *Order_Number;
   extern const I_CHAR *Participant_Number;
   extern const I_CHAR *Phoenix_Account;
   extern const I_CHAR *VIP_Flag;
   extern const I_CHAR *FX;
   extern const I_CHAR *Payment_Method;
   extern const I_CHAR *Amount_Type;
   extern const I_CHAR *Originator;
   extern const I_CHAR *Plan_Number;
   extern const I_CHAR *Payment_Reference;
   extern const I_CHAR *Bank_Account;
   extern const I_CHAR *Value_Date;
   extern const I_CHAR *Free_Text;
   extern const I_CHAR *Cusip_Code;
}

namespace SessionTags
{
   extern const I_CHAR *SESSION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId SettleDate;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId AmtType;
   extern CLASS_IMPORT const BFTextFieldId TradesPayType;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId XrefNum;
   extern CLASS_IMPORT const BFNumericFieldId TransNum;
   extern CLASS_IMPORT const BFDecimalFieldId ExchRate;
   extern CLASS_IMPORT const BFTextFieldId Batch;
   extern CLASS_IMPORT const BFDecimalFieldId PurchaseTotal;
}

// NEW IMPLEMENTATION
// From Account
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFTextFieldId DefaultGrp;
   extern CLASS_IMPORT const BFTextFieldId rxGroupCode;
   extern CLASS_IMPORT const BFTextFieldId GroupType;
   extern CLASS_IMPORT const BFTextFieldId MorganAcctTypeForX;
   extern CLASS_IMPORT const BFTextFieldId MorganAcctTypeForT;
   extern CLASS_IMPORT const BFTextFieldId MorganTaxType;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForRep;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForMail;
   extern CLASS_IMPORT const BFDecimalFieldId MinFndClsBal;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId EscrowFund;
   extern CLASS_IMPORT const BFTextFieldId EscrowClass;
   extern CLASS_IMPORT const BFDateFieldId EscrowDeff;
   extern CLASS_IMPORT const BFDateFieldId EscrowStopDate;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFDecimalFieldId AmtAssigned;
   extern CLASS_IMPORT const BFTextFieldId GICallowed;
   extern CLASS_IMPORT const BFTextFieldId FundType;
   extern CLASS_IMPORT const BFTextFieldId AccountTypes;
   extern CLASS_IMPORT const BFTextFieldId InitPurch;
   extern CLASS_IMPORT const BFTextFieldId SettledFieldsInitialized;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFDateFieldId DofDeath;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForSWPStop;
   extern CLASS_IMPORT const BFTextFieldId SWPallowed;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeAcctType;
   extern CLASS_IMPORT const BFTextFieldId MaximumApplies;
   extern CLASS_IMPORT const BFTextFieldId DuplicateAltAcct;
   extern CLASS_IMPORT const BFTextFieldId SortBy;
   extern CLASS_IMPORT const BFTextFieldId SrchAltAcct;
   extern CLASS_IMPORT const BFTextFieldId SrchBroker;
   extern CLASS_IMPORT const BFTextFieldId TaxTypePensionJuris;
}

// From Trade
namespace ifds 
{
   extern CLASS_IMPORT const BFTextFieldId AmtTypeFundTradeType;
   extern CLASS_IMPORT const BFTextFieldId AmountPrecision;
   extern CLASS_IMPORT const BFTextFieldId AcctTradeType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId AllocationFromFund;
   extern CLASS_IMPORT const BFTextFieldId AllocationToFund;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId InvAdvice;
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFTextFieldId FundClassTradeType;
   extern CLASS_IMPORT const BFTextFieldId ToFundClassTradeDate;
   extern CLASS_IMPORT const BFTextFieldId ToFundClass;
   extern CLASS_IMPORT const BFTextFieldId MinToFundAmount;
   extern CLASS_IMPORT const BFTextFieldId MinFromFundAmount;
   extern CLASS_IMPORT const BFDecimalFieldId MinInitPurAmt;
   extern CLASS_IMPORT const BFDecimalFieldId MinSubPurAmt;
   extern CLASS_IMPORT const BFDecimalFieldId MinInitRedAmt;
   extern CLASS_IMPORT const BFDecimalFieldId MinSubRedAmt;
   extern CLASS_IMPORT const BFDecimalFieldId MinFndClsBal;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId WireOrdFndCls;
   extern CLASS_IMPORT const BFTextFieldId WireOrdNumOrdType;
   extern CLASS_IMPORT const BFTextFieldId WireNumMandatory;
   extern CLASS_IMPORT const BFTextFieldId WireElig;
   extern CLASS_IMPORT const BFTextFieldId ValuationDate;
   extern CLASS_IMPORT const BFTextFieldId AcctableTradeDate;
   extern CLASS_IMPORT const BFTextFieldId NetAllocation;
   extern CLASS_IMPORT const BFTextFieldId NetOrdType;
   extern CLASS_IMPORT const BFTextFieldId NetMultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId AmountPrecision;
   extern CLASS_IMPORT const BFTextFieldId AmtTypeFundTradeType;
   extern CLASS_IMPORT const BFNumericFieldId Precision;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFTextFieldId AcctTradeType;
   extern CLASS_IMPORT const BFTextFieldId BusRounding;
   extern CLASS_IMPORT const BFDecimalFieldId BankLayout;
   extern CLASS_IMPORT const BFDecimalFieldId BankValid1;
   extern CLASS_IMPORT const BFTextFieldId BankValid2;
   extern CLASS_IMPORT const BFNumericFieldId InstCode;
   extern CLASS_IMPORT const BFTextFieldId DisableFee4Alloc;
   extern CLASS_IMPORT const BFTextFieldId AcqFeeDefault;
   extern CLASS_IMPORT const BFDecimalFieldId AcqFee;
   extern CLASS_IMPORT const BFTextFieldId AcqFeeType;
   extern CLASS_IMPORT const BFTextFieldId MaxFeeActive;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFTextFieldId MaxFeeType;
   extern CLASS_IMPORT const BFDecimalFieldId MaxPercent;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFlatFundCurr;
   extern CLASS_IMPORT const BFTextFieldId ToFundClassAllowed;
   extern CLASS_IMPORT const BFTextFieldId MaxAcqFeePurchase;
   extern CLASS_IMPORT const BFTextFieldId MaxAcqFeeTransfer;
   extern CLASS_IMPORT const BFTextFieldId NetAllowed;
   extern CLASS_IMPORT const BFTextFieldId PayTypeBankNum;
   extern CLASS_IMPORT const BFTextFieldId TradingAttribFieldsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId TradeAttributes;
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesExchange;
   extern CLASS_IMPORT const BFTextFieldId Initial;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId TradingAttributesHeadingSet;
   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId AccountBalance;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId FromCurrency;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeExchange;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
   extern CLASS_IMPORT const BFTextFieldId WireNumDefault;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFundMandatory;
   extern CLASS_IMPORT const BFTextFieldId TradeSrcOfFund;
   extern CLASS_IMPORT const BFTextFieldId AcctNumSet;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId CertIssued;
   extern CLASS_IMPORT const BFTextFieldId FundAllow;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId DuplicateTrade;
   extern CLASS_IMPORT const BFTextFieldId DepValid;
   extern CLASS_IMPORT const BFTextFieldId MaximumApplies;
   extern CLASS_IMPORT const BFTextFieldId FundCodeRedCodeAmount;
   extern CLASS_IMPORT const BFTextFieldId FundType;
   extern CLASS_IMPORT const BFDateFieldId NextSettleDate;
   extern CLASS_IMPORT const BFDateFieldId LastValDate;
   extern CLASS_IMPORT const BFTextFieldId RedemptionPayType;
   extern CLASS_IMPORT const BFTextFieldId TradeRedemptionAttribute;
   extern CLASS_IMPORT const BFTextFieldId AmtTypeRedemption;
   extern CLASS_IMPORT const BFTextFieldId EmptySetField;
   extern CLASS_IMPORT const BFTextFieldId AllowWire;
   extern CLASS_IMPORT const BFTextFieldId MMWire;
   extern CLASS_IMPORT const BFDecimalFieldId PurchaseTotal;
   extern CLASS_IMPORT const BFIntegerFieldId SettlePurDays;
   extern CLASS_IMPORT const BFTextFieldId VolSettleType;
   extern CLASS_IMPORT const BFTextFieldId AcctToRedCode;
   extern CLASS_IMPORT const BFTextFieldId AllFundTransfer;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFNumericFieldId PendingRid;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId AccountTo;
   extern CLASS_IMPORT const BFTextFieldId Fund;
   extern CLASS_IMPORT const BFTextFieldId FundTo;
   extern CLASS_IMPORT const BFTextFieldId Class;
   extern CLASS_IMPORT const BFTextFieldId ClassTo;
   extern CLASS_IMPORT const BFTextFieldId PUD;
   extern CLASS_IMPORT const BFTextFieldId FlatPrcnt;
   extern CLASS_IMPORT const BFTextFieldId InPayType;
   extern CLASS_IMPORT const BFDecimalFieldId IAmount;
   extern CLASS_IMPORT const BFTextFieldId InTransType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId InGrossNet;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFNumericFieldId TransNum;
   extern CLASS_IMPORT const BFNumericFieldId TransSeq;
   extern CLASS_IMPORT const BFTextFieldId TradeBankSelection;
   extern CLASS_IMPORT const BFTextFieldId DepositTypeList;
   extern CLASS_IMPORT const BFTextFieldId RedCodeList;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankType;
   extern CLASS_IMPORT const BFDecimalFieldId CorrespBankId;
   extern CLASS_IMPORT const BFTextFieldId PayReason1;
   extern CLASS_IMPORT const BFTextFieldId PayReason2;
   extern CLASS_IMPORT const BFDecimalFieldId UnitValue;
   extern CLASS_IMPORT const BFTextFieldId ManualSettleDates;
   extern CLASS_IMPORT const BFTextFieldId ExchInFeeFlatPercent;
   extern CLASS_IMPORT const BFDecimalFieldId UnsettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId UnsettledValue;
   extern CLASS_IMPORT const BFTextFieldId DispClientTradeID;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForRep;
   extern CLASS_IMPORT const BFTextFieldId SplitOnAddPur;
   extern CLASS_IMPORT const BFTextFieldId SplitOnModPur;
   extern CLASS_IMPORT const BFDecimalFieldId AcctBalance;
   extern CLASS_IMPORT const BFTextFieldId SettledFieldsInitialized;
   extern CLASS_IMPORT const BFDateFieldId NextNightRun;
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
   extern CLASS_IMPORT const BFTextFieldId AllocationsAllowed;
   extern CLASS_IMPORT const BFTextFieldId CreateAllocations;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
   extern CLASS_IMPORT const BFDecimalFieldId MinPercent;
   extern CLASS_IMPORT const BFTextFieldId PurchaseSourceOfFund;
   extern CLASS_IMPORT const BFTextFieldId RedempSourceOfFund;
   extern CLASS_IMPORT const BFTextFieldId TransferSourceOfFund;
   extern CLASS_IMPORT const BFTextFieldId AcctFromRedCode;
   extern CLASS_IMPORT const BFTextFieldId PendingAllocExists;
   extern CLASS_IMPORT const BFTextFieldId AccNumTradeDate;
   extern CLASS_IMPORT const BFTextFieldId ValueDateApplic;
   extern CLASS_IMPORT const BFTextFieldId PayTypeFileProc;
   extern CLASS_IMPORT const BFTextFieldId BankFileProcExist;
   extern CLASS_IMPORT const BFTextFieldId InternationalWire;
   extern CLASS_IMPORT const BFDateFieldId SpouseBirth; 
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
}

// From Address
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Address;
   extern CLASS_IMPORT const BFTextFieldId KanaAddress;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId AddrCntryCode;
   extern CLASS_IMPORT const BFTextFieldId RegAddrCode;

   extern CLASS_IMPORT const BFTextFieldId Addr11Line1;
   extern CLASS_IMPORT const BFTextFieldId Addr11Line2;
   extern CLASS_IMPORT const BFTextFieldId Addr11Line3;
   extern CLASS_IMPORT const BFTextFieldId Addr11Line4;
   extern CLASS_IMPORT const BFTextFieldId Addr11Line5;

   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId FieldAssignment;
}

// From Entity
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
}

enum FILTER_FLAGS
{
   NO_FILTER            = 0x0000,
   STRIP                = 0x0001,
   STRIP_LEADING_ZEROS  = 0x0002,
   UPPERCASE            = 0x0004,
   AWD_DATE_FORMAT      = 0x0008,      // Convert iFast date to std AWD Date format (CCYY-MM-DD)
};

namespace SOURCE {
   enum 
   {
      SHAREHOLDER,
      ACCOUNT,
      ENTITY,
      ADDRESS_CODE01,
      TRADE,
      USERSESSION_GLOBAL,
//      AWD_SESSION,
//      SESSION,
      AWD_FIELD,
      GENERATED,
   };
}

// May use smaller data types to save space (eg. unsigned char for Source and FilterFlags, short for MappingField)
struct AwdIntegrationMapping
{
   AwdIntegrationMapping( long  lMappingFieldId, 
                          const BFFieldId &idField,
                          short nSource, 
                          long  lFilterFlags)
   : m_lMappingFieldId(lMappingFieldId)
   , m_idField(idField)
   , m_nSource(nSource)
   , m_lFilterFlags(lFilterFlags)
   {
   }

   long m_lMappingFieldId;
   BFFieldId m_idField;
   short m_nSource;
   long m_lFilterFlags;
};

const AwdIntegrationMapping aMapping[] = {
   // Shareholder
   AwdIntegrationMapping( 100000, ifds::ShrNum,              SOURCE::SHAREHOLDER,      STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100001, ifds::AcctDesignation,     SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100002, ifds::AcctDesignationDesc, SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100003, ifds::TaxJurisCode,        SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100004, ifds::ResProvCode,         SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100005, ifds::GroupCode,           SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100006, ifds::FamilyCode,          SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100007, ifds::FundRelnCode,        SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100008, ifds::EffectiveDate,       SOURCE::SHAREHOLDER,      AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100009, ifds::PrimMstrVer,         SOURCE::SHAREHOLDER,      NO_FILTER ),
   AwdIntegrationMapping( 100010, ifds::Name1,               SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100011, ifds::Name2,               SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100012, ifds::GroupName1,          SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100013, ifds::GroupName2,          SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100014, ifds::FamilyName,          SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100015, ifds::ConsolEFT,           SOURCE::SHAREHOLDER,      STRIP ),
   AwdIntegrationMapping( 100016, ifds::GrpCodeLevel,        SOURCE::SHAREHOLDER,      STRIP ),

   // Account
   AwdIntegrationMapping( 100100, ifds::ShrNum,              SOURCE::ACCOUNT,          STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100101, ifds::AccountNum,          SOURCE::ACCOUNT,          STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100102, ifds::BeneficialOwner,     SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100103, ifds::AcctType,            SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100104, ifds::TaxType,             SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100105, ifds::RecipientType,       SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100106, ifds::Currency,            SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100107, ifds::BrokerCode,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100108, ifds::BranchCode,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100109, ifds::Slsrep,            SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100110, ifds::AcctStatus,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100111, ifds::DateOfReg,           SOURCE::ACCOUNT,          AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100112, ifds::PensionJuris,        SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100113, ifds::MarketMail,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100114, ifds::EffectiveDate,       SOURCE::ACCOUNT,          AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100115, ifds::AltAccount,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100116, ifds::AMSCode,             SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100117, ifds::BrokerName,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100118, ifds::BranchName,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100119, ifds::SlsrepName,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100120, ifds::SlsrepAltName,       SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100121, ifds::AcctGroup,           SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100122, ifds::AcctGroupName,       SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100123, ifds::LockedIn,            SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100124, ifds::XrefNum,             SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100125, ifds::InterCode,           SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100126, ifds::InterAccount,        SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100127, ifds::RRSPFee,             SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100128, ifds::StopPurchase,        SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100129, ifds::StopXferIn,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100130, ifds::StopXferOut,         SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100131, ifds::StopRed,             SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100132, ifds::FeeWaived,           SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100133, ifds::Unseizable,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100134, ifds::RegCompleted,        SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100135, ifds::SupConf,             SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100136, ifds::SupEmpConf,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100137, ifds::InTrustFor,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100138, ifds::Escrow,              SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100139, ifds::AcctMstrVer,         SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100140, ifds::AcctMstrRid,         SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100141, ifds::AcctDesignation,     SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100142, ifds::AccountBalance,      SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100143, ifds::Username,            SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100144, ifds::ModDate,             SOURCE::ACCOUNT,          AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100145, ifds::ModUser,             SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100146, ifds::Employee,            SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100147, ifds::AddAcctFlag,         SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100148, ifds::TransFound,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100149, ifds::ExistBeneficiary,    SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100150, ifds::ContractExist,       SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100151, ifds::SocialCode,          SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100152, ifds::StopFCrebal,         SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100153, ifds::GSTExempt,           SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100154, ifds::ApplyPST,            SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100155, ifds::BankChrgs,           SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100156, ifds::ConsolidEFT,         SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100157, ifds::SettledFieldsInitialized, SOURCE::ACCOUNT,     STRIP ),
   AwdIntegrationMapping( 100158, ifds::SettledValue,        SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100159, ifds::UnsettledValue,      SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100160, ifds::AcctFeesExist,       SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100161, ifds::FirstEffective,      SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100162, ifds::ShouldAskForSWPStop, SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100163, ifds::TaxTypeAcctType,     SOURCE::ACCOUNT,          STRIP ),
   AwdIntegrationMapping( 100164, ifds::TaxTypePensionJuris, SOURCE::ACCOUNT,          STRIP ),

   // Trade
   AwdIntegrationMapping( 100200, ifds::AccountNum,          SOURCE::TRADE,            STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100201, ifds::TradesTransType,     SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100202, ifds::Broker,              SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100203, ifds::Branch,              SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100204, ifds::SlsrepCode,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100205, ifds::Amount,              SOURCE::TRADE,            STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100206, ifds::AmtType,             SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100207, ifds::GrossOrNet,          SOURCE::TRADE,            STRIP | UPPERCASE ),
   AwdIntegrationMapping( 100208, ifds::Fee,                 SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100209, ifds::FlatPercent,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100210, ifds::TradesPayType,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100211, ifds::SrcOfFund,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100212, ifds::EffectiveDate,       SOURCE::TRADE,            AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100213, ifds::SettleDate,          SOURCE::TRADE,            AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100214, ifds::DealDate,            SOURCE::TRADE,            AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100215, ifds::DealTime,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100216, ifds::OrderType,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100217, ifds::OrderSource,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100218, ifds::FromFund,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100219, ifds::FromClass,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100220, ifds::ToFund,              SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100221, ifds::ToClass,             SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100222, ifds::AccountTo,           SOURCE::TRADE,            STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100223, ifds::RedCode,             SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100224, ifds::DepositType,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100225, ifds::DepositDate,         SOURCE::TRADE,            AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100226, ifds::ExchRate,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100227, ifds::UseEnteredFee,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100228, ifds::Accountable,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100229, ifds::BackDatedReason,     SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100230, ifds::GoodBad,             SOURCE::TRADE,            STRIP | UPPERCASE ),
   AwdIntegrationMapping( 100231, ifds::CertRequired,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100232, ifds::RecptIssued,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100233, ifds::WireOrdNum,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100234, ifds::GICId,               SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100235, ifds::Remarks1,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100236, ifds::Remarks2,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100237, ifds::Remarks3,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100238, ifds::ProvSales,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100239, ifds::SettleCurrency,      SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100240, ifds::SettledBy,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100241, ifds::SettleType,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100242, ifds::ExpGNSettle,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100243, ifds::SrcOfAccount,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100244, ifds::DepId,               SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100245, ifds::SettleSource,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100246, ifds::CashDate,            SOURCE::TRADE,            AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100247, ifds::BatchName,           SOURCE::TRADE,            STRIP ), // DO NOT REMOVE LEADING ZEROS
   AwdIntegrationMapping( 100248, ifds::Trace,               SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100249, ifds::SetAsDefault,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100250, ifds::ShrNum,              SOURCE::TRADE,            STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100251, ifds::BrokerName,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100252, ifds::BranchName,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100253, ifds::SlsrepName,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100254, ifds::SlsrepAltName,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100255, ifds::InterDetlRid,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100256, ifds::InstCode,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100257, ifds::SwiftCode,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100258, ifds::RefNumber,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100259, ifds::TransitNo,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100260, ifds::BankAcctNum,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100261, ifds::BankAcctName,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100262, ifds::BankAcctType,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100263, ifds::TransNum,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100264, ifds::CreateRep,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100265, ifds::InstName,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100266, ifds::AcctTradeType,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100267, ifds::FundClassTradeType,  SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100268, ifds::ToFundClass,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100269, ifds::MinToFundAmount,     SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100270, ifds::MinFromFundAmount,   SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100271, ifds::AmountPrecision,     SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100272, ifds::ValuationDate,       SOURCE::TRADE,            AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100273, ifds::AmtTypeFundTradeType,SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100274, ifds::WireOrdFndCls,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100275, ifds::WireOrdNumOrdType,   SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100276, ifds::AcctableTradeDate,   SOURCE::TRADE,            AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100277, ifds::NetOrdType,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100278, ifds::NetAllocation,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100279, ifds::NetMultiCurrency,    SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100280, ifds::ToFundClassAllowed,  SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100281, ifds::MaxAcqFeePurchase,   SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100282, ifds::MaxAcqFeeTransfer,   SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100283, ifds::PayTypeBankNum,      SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100284, ifds::Initial,             SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100285, ifds::AllocationToFund,    SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100286, ifds::AllocationFromFund,  SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100287, ifds::TradeAttributesExchange, SOURCE::TRADE,        STRIP ),
   AwdIntegrationMapping( 100288, ifds::SettledUnits,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100289, ifds::AccountBalance,      SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100290, ifds::Currency,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100291, ifds::FromCurrency,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100292, ifds::AmountTypeExchange,  SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100293, ifds::AcctUseCode,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100294, ifds::TradeSrcOfFund,      SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100295, ifds::SrcOfFundMandatory,  SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100296, ifds::AcctNumSet,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100297, ifds::FromFundNumber,      SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100298, ifds::ToFundNumber,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100299, ifds::CertIssued,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100300, ifds::FundAllow,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100301, ifds::DuplicateTrade,      SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100302, ifds::DepValid,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100303, ifds::DepClosed,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100304, ifds::SettledValue,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100305, ifds::FundCodeRedCodeAmount, SOURCE::TRADE,          STRIP ),
   AwdIntegrationMapping( 100306, ifds::FundType,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100307, ifds::SuppressCode,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100308, ifds::AddrCode,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100309, ifds::DeliveryMethod,      SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100310, ifds::FeeCurrency,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100311, ifds::ExternalId,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100312, ifds::AcctToRedCode,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100313, ifds::AllFundTransfer,     SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100314, ifds::DSCOverrideCode,     SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100315, ifds::DSCOverrideAmt,      SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100316, ifds::AllocAmount,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100317, ifds::BankAcctCurrency,    SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100318, ifds::AcctFromRedCode,     SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100319, ifds::BankIdValue,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100320, ifds::BankIdType,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100321, ifds::BankIdTypeCB,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100322, ifds::InstNameCB,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100323, ifds::TransitNoCB,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100324, ifds::BankIdValueCB,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100325, ifds::FFC,                 SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100326, ifds::FFC1,                SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100327, ifds::ACHProcessor,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100328, ifds::BankContactCB,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100329, ifds::BankCountryCB,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100330, ifds::BankPostalCB,        SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100331, ifds::BankAddrCB1,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100332, ifds::BankAddrCB2,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100333, ifds::BankAddrCB3,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100334, ifds::BankAddrCB4,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100335, ifds::BankAddrCB5,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100336, ifds::BankAddr1,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100337, ifds::BankAddr2,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100338, ifds::BankAddr3,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100339, ifds::BankAddr4,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100340, ifds::BankAddr5,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100341, ifds::BankContact,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100342, ifds::BankCountry,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100343, ifds::BankPostal,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100344, ifds::BankIdValue,         SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100345, ifds::BankId,              SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100346, ifds::TransSeq,            SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100347, ifds::VersionNum,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100348, ifds::SplitComm,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100349, ifds::InvAdvice,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100350, ifds::TradeBankSelection,  SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100351, ifds::ExchInFee,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100352, ifds::ExchInFlatPercent,   SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100353, ifds::PayReason1,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100354, ifds::PayReason2,          SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100355, ifds::ExchInFeeFlatPercent,SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100356, ifds::ClientTradeId,       SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100357, ifds::ShouldAskForRep,     SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100358, ifds::PayMethod,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100359, ifds::ValueDate,           SOURCE::TRADE,            AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100360, ifds::BankChrgs,           SOURCE::TRADE,            STRIP ),
   AwdIntegrationMapping( 100361, ifds::BankFileProcExist,   SOURCE::TRADE,            STRIP ),

   // Entity
   AwdIntegrationMapping( 100400, ifds::LastName,         SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100401, ifds::FirstName,          SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100402, ifds::Salutation,       SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100403, ifds::BirthLastName,      SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100404, ifds::BirthFirstName,     SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100405, ifds::DofBirth,         SOURCE::ENTITY,           AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100406, ifds::Gender,           SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100407, ifds::SIN,              SOURCE::ENTITY,           STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100408, ifds::Language,         SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100409, ifds::LanguageCode,       SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100410, ifds::HomePhone,          SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100411, ifds::BusinessPhone,      SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100412, ifds::BusinessExt,        SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100413, ifds::BusinessFax,        SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100414, ifds::Telex,            SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100415, ifds::Email,            SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100416, ifds::DofDeath,         SOURCE::ENTITY,           AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100417, ifds::DofDeathNotice,     SOURCE::ENTITY,           AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100418, ifds::EffectiveDate,      SOURCE::ENTITY,           AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100419, ifds::HomeFax,          SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100420, ifds::OccupationCode,      SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100421, ifds::OccupationDesc,      SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100422, ifds::ProcessDate,        SOURCE::ENTITY,           AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100423, ifds::EntityIdentityVer,   SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100424, ifds::EntityIdentityRid,   SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100425, ifds::CompoundDate,        SOURCE::ENTITY,           AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100426, ifds::HomePhoneArea,       SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100427, ifds::BusinessPhoneArea,   SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100428, ifds::HomeFaxArea,         SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100429, ifds::BusFaxArea,          SOURCE::ENTITY,           STRIP ),
   AwdIntegrationMapping( 100430, ifds::EmployeeClass,     SOURCE::ENTITY,           STRIP ),

   // Address
   AwdIntegrationMapping( 100500, ifds::ShrNum,              SOURCE::ADDRESS_CODE01,   STRIP | STRIP_LEADING_ZEROS ),
   AwdIntegrationMapping( 100501, ifds::Confirm,             SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100502, ifds::AddrCode,            SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100503, ifds::AddrCodeDesc,        SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100504, ifds::Name1,               SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100505, ifds::Name2,               SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100506, ifds::AddrLine1,           SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100507, ifds::AddrLine2,           SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100508, ifds::AddrLine3,           SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100509, ifds::AddrLine4,           SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100510, ifds::AddrLine5,           SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100511, ifds::PostalCode,          SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100512, ifds::CountryName,         SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100513, ifds::CountryCode,         SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100514, ifds::AddressFileRid,      SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100515, ifds::AddressFileVer,      SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100516, ifds::Salutation,          SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100517, ifds::EffectiveDate,       SOURCE::ADDRESS_CODE01,   AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100518, ifds::StopDate,            SOURCE::ADDRESS_CODE01,   AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100519, ifds::kAddrLine1,          SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100520, ifds::kAddrLine2,          SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100521, ifds::kAddrLine3,          SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100522, ifds::kAddrLine4,          SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100523, ifds::kAddrLine5,          SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100524, ifds::KAddrFileRid,        SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100525, ifds::KAddrFileVer,        SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100526, ifds::Address,             SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100527, ifds::KanaAddress,         SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100528, ifds::EffectiveStopDate,   SOURCE::ADDRESS_CODE01,   AWD_DATE_FORMAT ),
   AwdIntegrationMapping( 100529, ifds::AddrCntryCode,       SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100530, ifds::RegAddrCode,         SOURCE::ADDRESS_CODE01,   STRIP ),
   AwdIntegrationMapping( 100531, ifds::FieldAssignment,     SOURCE::ADDRESS_CODE01,   STRIP ),

   // User Session - Global
   AwdIntegrationMapping( 100800, ifds::CallerName,          SOURCE::USERSESSION_GLOBAL, STRIP ),
   AwdIntegrationMapping( 100801, ifds::LastActiveAccountNum,SOURCE::USERSESSION_GLOBAL, STRIP | STRIP_LEADING_ZEROS ),

   // AWD Fields
   AwdIntegrationMapping( 800000, ifds::NullFieldId, SOURCE::AWD_FIELD, NO_FILTER ), // Business Area 
   AwdIntegrationMapping( 800001, ifds::NullFieldId, SOURCE::AWD_FIELD, NO_FILTER ), // Work Type 
   AwdIntegrationMapping( 800002, ifds::NullFieldId, SOURCE::AWD_FIELD, NO_FILTER ), // Status 

   // Generated
   AwdIntegrationMapping( 990000, ifds::NullFieldId, SOURCE::GENERATED, NO_FILTER ), // Transfer Agency - 'COR 
   AwdIntegrationMapping( 990001, ifds::NullFieldId, SOURCE::GENERATED, NO_FILTER ), // Luxembourg - Amount Type (Shares/Cash) - Valid values (S)hares || (C)ash 
   AwdIntegrationMapping( 990002, ifds::NullFieldId, SOURCE::GENERATED, NO_FILTER ), // Luxembourg - Payment Method - Valid values (C)heque || (W)ire 
   AwdIntegrationMapping( 990003, ifds::NullFieldId, SOURCE::GENERATED, NO_FILTER ), // Luxembourg - From first Trade Object; based on ifds::ExchRate return 'Y' or 'N' appropriately 
   AwdIntegrationMapping( 990004, ifds::NullFieldId, SOURCE::GENERATED, NO_FILTER ), // Transfer Agency - Amount field populated with either Amount/Purchase Total 
};


static const int NUM_FIELDS_IN_MAPPING = sizeof( aMapping ) / sizeof( AwdIntegrationMapping );

// Check Constant AWD Integration Mapping table to ensure no duplicate MappingFieldIds are used.
bool AWDCommon::IsMappingTableValid(void) 
{
   for( int iCtr = 0; iCtr < NUM_FIELDS_IN_MAPPING - 1; ++iCtr )
   {
      for( int iCtr2 = iCtr + 1; iCtr2 < NUM_FIELDS_IN_MAPPING; ++iCtr2 )
      {
         if( aMapping[iCtr].m_lMappingFieldId == aMapping[iCtr2].m_lMappingFieldId )
         {
            return(false);
         }
      }
   }
   return(true);
}

// Verify that a config table (eg. CASE TABLE or WORK TABLE) is mapped correctly to the Array.
// This routine doesn't check the validity/existence of the AWD Field or the Right-Side value of those entries.
bool AWDCommon::IsSessionTableValid(DString &dstrTable)
{
   ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
   Configuration cfgTable = pMgr->retrieveConfig( dstrTable );

   // Check All Fields in .INI table
   // ITERATE
   bool bFound;
   DString dstrMappingID;
   long lMappingID;
   Configuration::iterator xiter = cfgTable.begin();
   while( xiter != cfgTable.end() )
   {
      dstrMappingID = ( *xiter ).getKey();
      dstrMappingID.strip();
      lMappingID = dstrMappingID.asInteger();

      // Check for existence of field in mapping table
      bFound = false;
      for( int iCtr = 0; iCtr < NUM_FIELDS_IN_MAPPING; ++iCtr )
      {
         if( aMapping[iCtr].m_lMappingFieldId == lMappingID )
         {
            bFound = true;
            break;
         }
      }
      if( !bFound ) return(false);

      ++xiter;
   }

   return(true);
}

void AWDCommon::getDataForAWD( BFData &data, GenericInterface &rpGIUserSession )
{  
   SEVERITY sevRtn;
   BFData *criteria; 
   MFAccount *pAccount;
   AddressList *pAddressList;
   Shareholder *pShareholder;
   Entity *pEntity;
   EntityIdsList *pEntityIDList;
   AccountEntityXref *pAccountEntityXref;
   WorksessionTradesList *pWorksessionTradesList = NULL;

   DString dstrValue, dstrMappingID, dstrAccountNum, dstrEntityId, dstrShareholderNum;
   BFObjIter *paddrIter;
   long lMappingID;
   bool bFound;
   int iCtr;

   ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
   Configuration cfgWorkTable = pMgr->retrieveConfig( SessionTags::WORK_TABLE );

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(rpGIUserSession.getBFWorkSession());

   // Get Date Mask from Registry
   DString dstrDateMask = GetConfigValueAsString( I_( "LocaleFormats" ), I_( "HostMasks" ), I_("D") );
   dstrDateMask.upperCase();

   // Retrieve account number from User Session Work Global
   rpGIUserSession.getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );

   // Get Account
   sevRtn = dstWorkSession->getMFAccount( BF::HOST, dstrAccountNum, pAccount );
   if( (sevRtn >= WARNING) || !pAccount )
   {
      return;
   }

   // Get Shareholder
   pAccount->getField(ifds::ShrNum, dstrShareholderNum, BF::HOST);
   sevRtn = dstWorkSession->getShareholder( BF::HOST, dstrShareholderNum, pShareholder );
   if( (sevRtn >= WARNING) || !pShareholder )
   {
      return;
   }

   // Get Address List from Shareholder
   pShareholder->getAddressList(pAddressList, BF::HOST );

   // Get Account Entity Cross Reference object
   dstWorkSession->getAccountEntityXref( BF::HOST, pAccountEntityXref );
   pAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST );

   // Get Entity ID
   pAccountEntityXref->GetEntityIdForAccountOwnerSequence1( dstrAccountNum, BF::HOST, dstrEntityId );
   dstWorkSession->getEntity( BF::HOST, dstrEntityId, pEntity );

   // Create Iterator for Address List and select obj with Address Code = 01
   paddrIter = new BFObjIter( *pAddressList, BF::HOST );
   criteria = new BFData();
   criteria->setElementValue( ifds::AddrCode, I_( "01" ), true, NULL );
   paddrIter->positionOnNextMatch( *criteria, BF::HOST );    
   delete criteria;

   // Get Entity ID List
   sevRtn = pEntity->getEntityIdsList(pEntityIDList, BF::HOST);

   // ITERATE
   Configuration::iterator xiter = cfgWorkTable.begin();
   while( xiter != cfgWorkTable.end() )
   {
      dstrMappingID = ( *xiter ).getKey();
      dstrMappingID.strip().stripAll( I_CHAR('\t') );
      lMappingID = dstrMappingID.asInteger();

      // Find in Array
      for( iCtr = 0, bFound = false; iCtr < NUM_FIELDS_IN_MAPPING; ++iCtr )
      {
         if( aMapping[iCtr].m_lMappingFieldId == lMappingID )
         {
            bFound = true;
            break;
         }
      }

      dstrValue = NULL_STRING;

      if( bFound )
      {
         // Get Value
         switch( aMapping[iCtr].m_nSource )
         {
            case SOURCE::ACCOUNT : 
               pAccount->getField( aMapping[iCtr].m_idField, dstrValue, BF::HOST );
               break;
            case SOURCE::ADDRESS_CODE01 :
               paddrIter->getObject()->getField( aMapping[iCtr].m_idField, dstrValue, BF::HOST);
               break;
            case SOURCE::ENTITY :
               pEntity->getField( aMapping[iCtr].m_idField, dstrValue, BF::HOST );
               break;
            case SOURCE::SHAREHOLDER :
               pShareholder->getField( aMapping[iCtr].m_idField, dstrValue, BF::HOST );
               break;
            case SOURCE::USERSESSION_GLOBAL :
               rpGIUserSession.getGlobal( WORK_GLOBAL, aMapping[iCtr].m_idField, dstrValue );
               break;
            case SOURCE::TRADE :
               {
                  dstWorkSession->getTradesList(pWorksessionTradesList, BF::HOST);
                  BFObjIter iterTrades( *pWorksessionTradesList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
                  if( !iterTrades.end() )
                  {
                     iterTrades.getObject()->getField(aMapping[iCtr].m_idField, dstrValue, BF::HOST);
                  }
               }
               break;
            case SOURCE::AWD_FIELD : break;

            case SOURCE::GENERATED :   // May move this to separate fn
               switch( lMappingID )
               {
                  case 990000 : 
                     {
                        if ( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
	                     {
                           dstrValue = I_("MAS"); // For Transfer Agency - lux
                        }
                        else if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
                        {
                           dstrValue = I_("COR");  // For Transfer Agency - canadian
                        }
                     }
                     break;  
                  case 990001 : 
                     {
                        // Amount Type (Shares/Cash) AMTT - Valid values (S)hares || (C)ash - For Luxembourg
                        // From first Trade Object; based on ifds::AmtType return 'C' or 'S' appropriately.
                        dstWorkSession->getTradesList(pWorksessionTradesList, BF::HOST);
                        BFObjIter iterTrades( *pWorksessionTradesList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
                        if( !iterTrades.end() )
                        {
                           DString dstrTemp;
                           iterTrades.getObject()->getField(ifds::AmtType, dstrTemp, BF::HOST);
                           dstrTemp.strip().upperCase();
                           if( !dstrTemp.empty() )
                           {
                              dstrValue = (dstrTemp == I_("D")) ? I_("C") : I_("S");
                           }
                        }
                     }
                     break;
                  case 990002 :
                     {
                        // For Luxembourg - Payment Method PAYM - Valid values (C)heque || (W)ire
                        // From first Trade Object; based on ifds::PayMethod return 'W' or 'C' appropriately.
                        dstWorkSession->getTradesList(pWorksessionTradesList, BF::HOST);
                        BFObjIter iterTrades( *pWorksessionTradesList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
                        if( !iterTrades.end() )
                        {
                           DString dstrTemp;
                           iterTrades.getObject()->getField(ifds::PayMethod, dstrTemp, BF::HOST);
                           dstrTemp.strip().upperCase(); // I_("WIRE") || I_("CHQ");
                           if( !dstrTemp.empty() )
                           {
                              dstrValue = (dstrTemp == I_("WIRE")) ? I_("W") : I_("C");
                           }
                        }
                     }
                     break;
                  case 990003 :
                     {
                        // For Luxembourg - FX (Foreign Exchange Transaction)
                        // From first Trade Object; based on ifds::ExchRate return 'Y' or 'N' appropriately.
                        dstWorkSession->getTradesList(pWorksessionTradesList, BF::HOST);
                        BFObjIter iterTrades( *pWorksessionTradesList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
                        if( !iterTrades.end() )
                        {
                           DString dstrTemp;
                           iterTrades.getObject()->getField(ifds::ExchRate, dstrTemp, BF::HOST, false);
                           dstrTemp.strip().stripLeading('0');
                           dstrValue = dstrTemp.empty() ? ICHARS_N : ICHARS_Y;
                        }
                     }
                     break;
                  case 990004 :
                     {
                        // For Transfer Agency - Populating the Amount field with either Amount or Purchase Total
                        dstWorkSession->getTradesList( pWorksessionTradesList, BF::HOST);
                        BFObjIter iterTrades( *pWorksessionTradesList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
                        DString dstrTemp, dstrPurchaseTotal;

                        // Amount - From Purchase Total if it exists
                        pWorksessionTradesList->getField( ifds::PurchaseTotal, dstrPurchaseTotal, BF::HOST, false );
                        double dPurchaseTotal = DSTCommonFunctions::convertToDouble( dstrPurchaseTotal );
                        if( dPurchaseTotal != 0.0 )
                        {
                           dstrPurchaseTotal.strip().stripLeading('0');
                           dstrValue = dstrPurchaseTotal;
                        }
                        else
                        {
                           dstrPurchaseTotal = NULL_STRING;
                        }

                        // Here is the issue...  What if the trades were all redemptions or a combination of purchase & redemptions?
                        // What value should be used when PurchaseTotal is 0.00?
                        // Currently, if PurchaseTotal is 0.00, then the first Amount value will be used.
                        // This will probably have to be revisited when the rule is defined.
                        // [UH]

                        if( !iterTrades.end() )
                        {
                           // Amount (Share/Gross) AMTV.  Take from Trade object.
                           if( dstrPurchaseTotal.empty() )
                           {
                              iterTrades.getObject()->getField(ifds::Amount, dstrTemp, BF::HOST);
                              dstrTemp.strip().stripLeading('0');
                              dstrValue = dstrTemp;
                           }
                        }

                     }
                     break;
               }
               break;
         }

         // Filters
         if( !dstrValue.empty() )
         {
            if( aMapping[iCtr].m_lFilterFlags & STRIP )
               dstrValue.strip();
            if( aMapping[iCtr].m_lFilterFlags & STRIP_LEADING_ZEROS )
               dstrValue.stripLeading('0');
            if( aMapping[iCtr].m_lFilterFlags & UPPERCASE )
               dstrValue.upperCase();
            if( aMapping[iCtr].m_lFilterFlags & AWD_DATE_FORMAT )
            {
               // Store date as YYYY-MM-DD; perhaps the dashes aren't required
               DString dstrTempDate;
               dstrTempDate = dstrValue.substr( dstrDateMask.find(ICHARS_YYYY), 4);
               dstrTempDate += ICHARS_MINUS;
               dstrTempDate += dstrValue.substr( dstrDateMask.find(ICHARS_MM), 2);
               dstrTempDate += ICHARS_MINUS;
               dstrTempDate += dstrValue.substr( dstrDateMask.find(ICHARS_DD), 2);
               dstrValue = dstrTempDate;
            }
         }

         // Store
         if( !dstrValue.empty() )
         {
            data.setElementValue( dstrMappingID, dstrValue, true);
         }

      }

      ++xiter;
   }   

   delete paddrIter;
}


// CURRENT IMPLEMENTATION
void AWDCommon::getExportAwdConvertedData( BFData &data, GenericInterface &rpGIUserSession )
{
   BFData data2;
   DString awdCData( NULL_STRING ), dstrAccountNum, dstrEntityId;
   MFAccount *pAcct = NULL;
   Shareholder *pShareholder = NULL;
   AddressList *pAddressList = NULL;
   Entity *pEntity = NULL;
// EntityIdsList *pEntityIDList = NULL;  
   AccountEntityXref *pAccountEntityXref = NULL;
   WorksessionTradesList *pWorksessionTradesList = NULL;

   BFCPSession *pSession = rpGIUserSession.getSession();

   DString dstrMarket = DSTCommonFunctions::getMarket();

   if( dstrMarket == MARKET_IDS::LUXEMBOURG )
   {
      // Luxembourg
      ConfigManager *pMgr2 = ConfigManager::getManager( WORKSTATION );
      Configuration cfgTable2 = pMgr2->retrieveConfig( SETTINGS );

      rpGIUserSession.getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, awdCData );
      awdCData.strip().stripLeading('0');
      if( !awdCData.empty() )
      {
         // iFast Account Number
         data.setElementValue( AWD::Account_Num, awdCData, true );

         // Pheonix Account Number (from Other Reference Number)
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(rpGIUserSession.getBFWorkSession());
         dstWorkSession->getMFAccount( BF::HOST, awdCData, pAcct );        
         pAcct->getField(ifds::XrefNum, awdCData, BF::HOST);
         if( !awdCData.empty() )
         {
            data.setElementValue( AWD::Phoenix_Account, awdCData, true );
         }

         // Get Date Mask from Registry
         DString dstrDateMask = GetConfigValueAsString( I_( "LocaleFormats" ), I_( "HostMasks" ), I_("D") );
         dstrDateMask.upperCase();

         // Transaction information
         dstWorkSession->getTradesList(pWorksessionTradesList, BF::HOST);
         BFObjIter iterTrades( *pWorksessionTradesList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
         DString dstrTemp, dstrTempDate, dstrAWDValue;
         if( !iterTrades.end() )
         {
            // Transaction Number
            iterTrades.getObject()->getField(ifds::TransNum, dstrTemp, BF::HOST);
            dstrTemp.strip();
            data.setElementValue( AWD::Order_Number, dstrTemp, true);

            // Amount (Share/Gross) AMTV
            iterTrades.getObject()->getField(ifds::Amount, dstrTemp, BF::HOST);
            dstrTemp.strip().stripLeading('0');
            data.setElementValue( AWD::Amount, dstrTemp, true );

            // Amount Type (Shares/Cash) AMTT - Valid values (S)hares || (C)ash
            iterTrades.getObject()->getField(ifds::AmtType, dstrTemp, BF::HOST);
            if( !dstrTemp.empty() )
            {
               dstrAWDValue = (dstrTemp == I_("D")) ? I_("C") : I_("S");
               data.setElementValue( AWD::Amount_Type, dstrAWDValue, true );
            }

            // Payment Method PAYM - Valid values (C)heque || (W)ire
/*
            iterTrades.getObject()->getField(ifds::PayMethod, dstrTemp, BF::HOST);
         dstrTemp.strip().upperCase(); // I_("WIRE") || I_("CHQ");
         if (!dstrTemp.empty()) {
           dstrAWDValue = (dstrTemp == I_("WIRE")) ? I_("W") : I_("C");
           data.setElementValue( AWD::Payment_Method, dstrAWDValue, true );
         }
*/
            // Old -- mapping TradesPayType to Payment_Method (This will be replaced with the above)
            iterTrades.getObject()->getField(ifds::TradesPayType, dstrTemp, BF::HOST);
            if( !dstrTemp.empty() )
            {
               dstrAWDValue = (dstrTemp == I_("E")) ? I_("W") : I_("C");
               data.setElementValue( AWD::Payment_Method, dstrAWDValue, true );
            }

            // Trade Date
            iterTrades.getObject()->getField(ifds::EffectiveDate, dstrTemp, BF::HOST, false);
            dstrTempDate = dstrTemp.substr( dstrDateMask.find(ICHARS_YYYY), 4);
            dstrTempDate += ICHARS_MINUS;
            dstrTempDate += dstrTemp.substr( dstrDateMask.find(ICHARS_MM), 2);
            dstrTempDate += ICHARS_MINUS;
            dstrTempDate += dstrTemp.substr( dstrDateMask.find(ICHARS_DD), 2);
            // Store date as YYYY-MM-DD; perhaps the dashes aren't required
            data.setElementValue( AWD::Trade_Date, dstrTempDate, true );

            // Fund
            iterTrades.getObject()->getField(ifds::FromFund, dstrTemp, BF::HOST);
            data.setElementValue( AWD::Fund, dstrTemp, true );

            // Settlement Date
            iterTrades.getObject()->getField(ifds::SettleDate, dstrTemp, BF::HOST, false);
            dstrTempDate = dstrTemp.substr( dstrDateMask.find(ICHARS_YYYY), 4);
            dstrTempDate += ICHARS_MINUS;
            dstrTempDate += dstrTemp.substr( dstrDateMask.find(ICHARS_MM), 2);
            dstrTempDate += ICHARS_MINUS;
            dstrTempDate += dstrTemp.substr( dstrDateMask.find(ICHARS_DD), 2);
            // Store date as YYYY-MM-DD; perhaps the dashes aren't required
            data.setElementValue( AWD::Settlement_Date, dstrTempDate, true );

            // FX (Foreign Exchange Transaction)
            iterTrades.getObject()->getField(ifds::ExchRate, dstrTemp, BF::HOST, false);
            dstrTemp.strip().stripLeading('0');
            data.setElementValue( AWD::FX, dstrTemp.empty() ? ICHARS_N : ICHARS_Y, true);
         }
      }
   }
   else
   {
      // Default (Canadian)
      ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
      Configuration cfgTable = pMgr->retrieveConfig( SessionTags::WORK_TABLE );
      ConfigManager *pMgr2 = ConfigManager::getManager( WORKSTATION );
      Configuration cfgTable2 = pMgr2->retrieveConfig( SETTINGS );
      BFSession *pBFSession = rpGIUserSession.getBFSession();

      // Statically define 'COR' for System_ID. for Transfer Agency
      if ( !cfgTable.getValueAsString( AWD::System_ID ).stripAll( I_CHAR('\t') ).empty() ) {
         data.setElementValue( AWD::System_ID, I_("COR"), true );
      }

      // Caller Name
      if( !cfgTable.getValueAsString( AWD::Caller_Name ).stripAll( I_CHAR('\t') ).empty() )
      {
         if( pBFSession->isBFWorkSession() )
         {
            rpGIUserSession.getGlobal( WORK_GLOBAL, ifds::CallerName, awdCData );
         }
         awdCData.strip();
         short n;
         while ( (n = awdCData.find(I_(";"))) != -1) awdCData[n] = I_(',');
         data.setElementValue( AWD::Caller_Name, awdCData, true);
      }

      // AWD Voice Integration 
      // ----------------------------------------------------------------------------------
      // Caller Full Name
      if( !cfgTable.getValueAsString( I_("CallerFullName")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("CallerFullName") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("CallerFullName"), awdCData, true );
      }
      // Home Phone Number
      if( !cfgTable.getValueAsString( I_("CallerHomeNumber")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("CallerHomeNumber") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("CallerHomeNumber"), awdCData, true );
      }
      // Caller Business Number
      if( !cfgTable.getValueAsString( I_("CallerBusinessNumber")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("CallerBusinessNumber") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("CallerBusinessNumber"), awdCData, true );
      }
      // Call Business Extension
      if( !cfgTable.getValueAsString( I_("CallerBusinessExtension")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("CallerBusinessExtension") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("CallerBusinessExtension"), awdCData, true );
      }
      // Caller Relationship
      if( !cfgTable.getValueAsString( I_("CallerRelationship")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("CallerRelationship") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("CallerRelationship"), awdCData, true );
      }
      // Start Date/Time of Call
      if( !cfgTable.getValueAsString( I_("CallStartDateTime")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("CallStartDateTime") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("CallStartDateTime"), awdCData, true );
      }
      // Operator Extension
      if( !cfgTable.getValueAsString( I_("OperatorExtension")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("OperatorExtension") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("OperatorExtension"), awdCData, true );
      }
      // Start Date/Time of Object
      if( !cfgTable.getValueAsString( I_("ObjectStartDateTime")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("ObjectStartDateTime") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("ObjectStartDateTime"), awdCData, true );
      }
      // End Date/Time of Object
      if( !cfgTable.getValueAsString( I_("ObjectEndDateTime")).stripAll( I_CHAR('\t') ).empty() )
      {
         awdCData = pSession->getSessionData( I_("ObjectEndDateTime") );
         awdCData.stripLeading().stripTrailing();
         data.setElementValue( I_("ObjectEndDateTime"), awdCData, true );
      }
      // Operator ID
      if( !cfgTable.getValueAsString( I_("OperatorID")).stripAll( I_CHAR('\t') ).empty() )
      {
         const DSTCSecurity* pSecurity = dynamic_cast< const DSTCSecurity* >( rpGIUserSession.getBFWorkSession()->getSecurity( DSTCHost::getPrimaryHost() ) );
         const DString dstrUserId = pSecurity->getUserId();
         awdCData = dstrUserId;
         awdCData.stripLeading().stripTrailing().upperCase();
         data.setElementValue( I_("OperatorID"), awdCData, true );
      }
      // ----------------------------------------------------------------------------------
      

      // Last Account Account Number (Account Number)
      if( pBFSession->isBFWorkSession() )
      {
         rpGIUserSession.getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, awdCData );
      }
      awdCData.strip().stripLeading('0');

      if( !awdCData.empty() )
      {
         if( !cfgTable.getValueAsString( AWD::Account_Num ).stripAll( I_CHAR('\t') ).empty() )
         {
            data.setElementValue( AWD::Account_Num, awdCData, true);
         }

         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(rpGIUserSession.getBFWorkSession());

         dstWorkSession->getMFAccount( BF::HOST, awdCData, pAcct );

         // Caller Name
         if( !cfgTable.getValueAsString( AWD::Caller_Name ).stripAll( I_CHAR('\t') ).empty() )
         {
            awdCData = pSession->getSessionData( I_( "CallerName" ));
            awdCData.strip();
            short n;
            while ( (n = awdCData.find(I_(";"))) != -1) awdCData[n] = I_(',');
            data.setElementValue( AWD::Caller_Name, awdCData, true);
         }

         // Currency Name
         if( !cfgTable.getValueAsString( AWD::Currency ).stripAll( I_CHAR('\t') ).empty() )
         {
            pAcct->getField(ifds::CurrencyName, awdCData, BF::HOST);
            awdCData.strip().stripLeading('0');
            data.setElementValue( AWD::Currency, awdCData, true);
         }

         // Sales Rep - Code
         if( !cfgTable.getValueAsString( AWD::RepresentativeCode ).stripAll( I_CHAR('\t') ).empty() )
         {
            pAcct->getField(ifds::Slsrep, awdCData, BF::HOST);
            awdCData.strip();
            data.setElementValue( AWD::RepresentativeCode, awdCData, true);
         }

         // Sales Rep - Name
         if( !cfgTable.getValueAsString( AWD::RepresentativeName ).stripAll( I_CHAR('\t') ).empty() )
         {
            pAcct->getField(ifds::SlsrepName, awdCData, BF::HOST);
            awdCData.strip();
            short n;
            while ( (n = awdCData.find(I_(";"))) != -1) awdCData[n] = I_(',');
            data.setElementValue( AWD::RepresentativeName, awdCData, true);
         }

         // Broker Code
         if( !cfgTable.getValueAsString( AWD::Broker_Code ).stripAll( I_CHAR('\t') ).empty() )
         {
            pAcct->getField(ifds::BrokerCode, awdCData, BF::HOST);
            awdCData.strip();
            data.setElementValue( AWD::Broker_Code, awdCData, true);
         }

         // Branch Code
         if( !cfgTable.getValueAsString( AWD::Branch_Code ).stripAll( I_CHAR('\t') ).empty() )
         {
            pAcct->getField(ifds::BranchCode, awdCData, BF::HOST);
            awdCData.strip();
            data.setElementValue( AWD::Branch_Code, awdCData, true);
         }

         pAcct->getField(ifds::ShrNum, awdCData, BF::HOST);
         SEVERITY sevRtn=dstWorkSession->getShareholder( BF::HOST, awdCData, pShareholder );    
         if( WARNING >= sevRtn )
         {
            // Group Number
            if( !cfgTable.getValueAsString( AWD::Group_Code ).stripAll( I_CHAR('\t') ).empty() )
            {
               pShareholder->getField(ifds::GroupCode, awdCData, BF::HOST);
               awdCData.strip();
               data.setElementValue( AWD::Group_Code, awdCData, true);
            }


            pShareholder->getAddressList(pAddressList, BF::HOST );
            if( pAddressList )
            {
               BFObjIter iter( *pAddressList, BF::HOST );
               if( !iter.end() )
               {
                  data2.setElementValue( ifds::AddrCode, I_( "01" ), true, NULL );
                  iter.positionOnNextMatch( data2, BF::HOST );

                  // Address Line 1
                  if( !cfgTable.getValueAsString( AWD::Address1 ).stripAll( I_CHAR('\t') ).empty() )
                  {
                     iter.getObject()->getField(ifds::AddrLine1, awdCData, BF::HOST);
                     awdCData.strip();
                     data.setElementValue( AWD::Address1, awdCData, true);
                  }

                  // Address Line 2
                  if( !cfgTable.getValueAsString( AWD::Address2 ).stripAll( I_CHAR('\t') ).empty() )
                  {
                     iter.getObject()->getField(ifds::AddrLine2, awdCData, BF::HOST);
                     awdCData.strip();
                     data.setElementValue( AWD::Address2, awdCData, true);
                  }

                  // Address Line 3
                  if( !cfgTable.getValueAsString( AWD::Address3 ).stripAll( I_CHAR('\t') ).empty() )
                  {
                     iter.getObject()->getField(ifds::AddrLine3, awdCData, BF::HOST);
                     awdCData.strip();
                     data.setElementValue( AWD::Address3, awdCData, true);
                  }

                  // Address Line 4
                  if( !cfgTable.getValueAsString( AWD::Address4 ).stripAll( I_CHAR('\t') ).empty() )
                  {
                     iter.getObject()->getField(ifds::AddrLine4, awdCData, BF::HOST);
                     awdCData.strip();
                     data.setElementValue( AWD::Address4, awdCData, true);
                  }

                  // Address Line 5
                  if( !cfgTable.getValueAsString( AWD::Address5 ).stripAll( I_CHAR('\t') ).empty() )
                  {
                     iter.getObject()->getField(ifds::AddrLine5, awdCData, BF::HOST);
                     awdCData.strip();
                     data.setElementValue( AWD::Address5, awdCData, true);
                  }
               }
            }
         }

         dstWorkSession->getAccountEntityXref( BF::HOST, pAccountEntityXref );
         pAcct->getField( ifds::AccountNum, dstrAccountNum, BF::HOST );
         pAccountEntityXref->GetEntityIdForAccountOwnerSequence1( dstrAccountNum, BF::HOST, dstrEntityId );
         dstWorkSession->getEntity( BF::HOST, dstrEntityId, pEntity );

         if( pEntity )
         {
            // First Name
            if( !cfgTable.getValueAsString( AWD::Entity_FName ).stripAll( I_CHAR('\t') ).empty() )
            {
               pEntity->getField(ifds::FirstName, awdCData, BF::HOST);
               awdCData.strip();
               short n;
               while ( (n = awdCData.find(I_(";"))) != -1) awdCData[n] = I_(',');
               data.setElementValue( AWD::Entity_FName, awdCData, true);
            }

            // Last Name
            if( !cfgTable.getValueAsString( AWD::Entity_LName ).stripAll( I_CHAR('\t') ).empty() )
            {
               pEntity->getField(ifds::LastName, awdCData, BF::HOST);
               awdCData.strip();
               short n;
               while ( (n = awdCData.find(I_(";"))) != -1) awdCData[n] = I_(',');
               data.setElementValue( AWD::Entity_LName, awdCData, true);
            }

            // SIN Number
            if( !cfgTable.getValueAsString( AWD::SIN_Num ).stripAll( I_CHAR('\t') ).empty() )
            {
               pEntity->getField(ifds::SIN, awdCData, BF::HOST);
               awdCData.strip().stripLeading('0');
               data.setElementValue( AWD::SIN_Num, awdCData, true);
            }
         }

         // Transaction information
         dstWorkSession->getTradesList(pWorksessionTradesList, BF::HOST);
         BFObjIter iterTrades( *pWorksessionTradesList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
         DString dstrTemp;
/*
         DString dstrPurchaseTotal;
         // Amount - From Purchase Total if it exists
         if ( !cfgTable.getValueAsString( AWD::Amount ).stripAll( I_CHAR('\t') ).empty() ) {
            pWorksessionTradesList->getField( ifds::PurchaseTotal, dstrPurchaseTotal, false );
            double dPurchaseTotal = DSTCommonFunctions::convertToDouble( dstrPurchaseTotal );
            if ( dPurchaseTotal != 0.0) {
               dstrPurchaseTotal.strip().stripLeading('0');
               data.setElementValue( AWD::Amount, dstrPurchaseTotal, true );
            } else {
               dstrPurchaseTotal = NULL_STRING;
            }
         }
*/
         // Here is the issue...  What if the trades were all redemptions or a combination of purchase & redemptions?
         // What value should be used when PurchaseTotal is 0.00?
         // Currently, if PurchaseTotal is 0.00, then the first Amount value will be used.
         // This will probably have to be revisited when the rule is defined.
         // [UH]

         if( !iterTrades.end() )
         {
            // Amount (Share/Gross) AMTV.  Take from Trade object.
            if( !cfgTable.getValueAsString( AWD::Amount ).stripAll( I_CHAR('\t') ).empty() )
            {
               iterTrades.getObject()->getField(ifds::Amount, dstrTemp, BF::HOST);
               dstrTemp.strip().stripLeading('0');
               data.setElementValue( AWD::Amount, dstrTemp, true );
            }

            // Batch Number
            // NOTE:  Do not remove leading zeros.
            if( !cfgTable.getValueAsString( AWD::Batch_Num ).stripAll( I_CHAR('\t') ).empty() )
            {
               iterTrades.getObject()->getField(ifds::Batch, dstrTemp, BF::HOST);
               dstrTemp.strip();
               data.setElementValue( AWD::Batch_Num, dstrTemp, true);
            }
         }
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AWDCommon.cpp-arc  $
 * 
 *    Rev 1.42   Oct 26 2005 11:33:38   popescu
 * Incident 437014 - corrected System field value - MAS-COR
 *  
 * 
 *    Rev 1.41   Dec 14 2004 15:01:52   popescu
 * some of the cross-edits have been renamed
 * 
 *    Rev 1.40   Nov 22 2004 13:09:54   popescu
 * PET 1117/56. fees processing
 * 
 *    Rev 1.39   Sep 29 2004 14:51:26   HERNANDO
 * PTS10033961 - Check for BFWorkSession before a getGlobal with WORK_GLOBAL.
 * 
 *    Rev 1.38   May 09 2004 20:11:32   popescu
 * PET 985, FN 01, LSIF Trade Entry
 * 
 *    Rev 1.37   Dec 30 2003 16:10:58   HERNANDO
 * PET910 - Added support for 10 new fields for AWD Voice Integration.  These fields are:
 * CallerFullName
 * CallerHomeNumber
 * CallerBusinessNumber
 * CallerBusinessExtension
 * CallerRelationship
 * OperatorExtension
 * OperatorID
 * CallStartDateTime
 * ObjectStartDateTime
 * ObjectEndDateTime
 * 
 *    Rev 1.36   May 27 2003 18:30:16   popescu
 * due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
 * 
 *    Rev 1.35   May 15 2003 16:08:20   HERNANDO
 * Removed Stripping of Leading Zeros from Batch Number.
 * 
 *    Rev 1.34   Mar 21 2003 18:32:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.33   Nov 19 2002 15:28:58   HERNANDO
 * Undid changes for PTS 10009814.
 * PTS 10010849 - Replace semi-colons with commas to prevent Encorr errors.
 * 
 *    Rev 1.32   Oct 09 2002 23:55:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.31   Sep 16 2002 14:04:18   HERNANDO
 * PTS 10009814 - Removed 'COR' from Transfer Agency code.
 * 
 *    Rev 1.30   Aug 29 2002 12:57:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.29   Aug 26 2002 17:19:20   HERNANDO
 * Precautionary code - removed tabs from values referenced in the .ini tables.
 * 
 *    Rev 1.28   Aug 07 2002 18:01:32   HERNANDO
 * No longer use PurchaseTotal field.  Strictly use Amount field from first trade.  Affects TA and E&P (Market Canada).
 * 
 *    Rev 1.27   Jul 29 2002 13:02:32   HERNANDO
 * Revert to old Payment Method mapping until the newer version is approved.
 * 
 *    Rev 1.26   Jul 26 2002 15:59:54   HERNANDO
 * Added getDataForAWD - a revised version of getExportAwdConvertedData and getExportAwdConvertedDataB combined.
 * 
 *    Rev 1.25   Jul 17 2002 13:21:22   HERNANDO
 * Cdn Mkt - Added RepName, Branch and Group.
 * 
 *    Rev 1.24   Jun 21 2002 14:21:08   HERNANDO
 * Revised PaymentMethod AWD field for Lux.
 * 
 *    Rev 1.23   Jun 20 2002 17:36:06   HERNANDO
 * Luxembourg Date change.  Now storing date for AWD as YYYY-MM-DD, the AWD Server mask should be able to display in anyway.  The dashes may not be necessary but are probably ignored.
 * 
 *    Rev 1.22   May 28 2002 12:19:44   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.21   22 May 2002 19:15:46   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.20   19 Apr 2002 18:40:04   HERNANDO
 * Using PurchaseTotal for AWD Amount field if !0.  StripLeading zeros from Batch Number.
 * 
 *    Rev 1.19   Mar 26 2002 17:09:32   HERNANDO
 * Enhancement for TA processing.  Added Branch_Number.  Checks table before populating.
 * 
 *    Rev 1.18   Mar 22 2002 17:08:54   HERNANDO
 * Fix - TA populated with Amount field instead of Account Balance for AWD Amount field.
 * 
 *    Rev 1.17   Mar 15 2002 17:59:22   HERNANDO
 * Added Batch Number to getExportAwdConvertedData for Transfer Agency.
 * 
 *    Rev 1.16   Jan 29 2002 15:50:30   HERNANDO
 * Removed unused fields for Transfer Agency; added 'COR' for System_ID -- undiscovered bug.  Store values in SessionData.
 * 
 *    Rev 1.15   Jul 25 2001 14:17:52   HERNANDO
 * Fix.
 * 
 *    Rev 1.14   Jul 25 2001 13:48:44   HERNANDO
 * Lux Revision - Checks for first Added Trades object.
 * 
 *    Rev 1.13   Jul 23 2001 16:08:48   HERNANDO
 * Dates in Lux implementation uses Date Mask from Registry.
 * 
 *    Rev 1.12   Jul 17 2001 15:14:14   HERNANDO
 * Revised Lux - Added FX field; update Phoenix value if exists.
 * 
 *    Rev 1.11   Jul 11 2001 14:53:04   HERNANDO
 * Revised for Lux - Shares/Cash, Payment Method, Order Number.
 * 
 *    Rev 1.10   Jul 09 2001 17:39:22   HERNANDO
 * Revised getExportAwdConvertedData for Luxembourg.
 * 
 *    Rev 1.9   Jul 05 2001 17:35:22   HERNANDO
 * Cleaned up getExportAwdConvertedDataB.
 * 
 *    Rev 1.8   Jun 15 2001 17:43:56   HERNANDO
 * Added basics for Luxembourg.
 * 
 *    Rev 1.7   03 May 2001 14:07:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Sep 18 2000 17:50:16   HERNANDO
 * Revised getExportAwdConvertedDataB
 * 
 *    Rev 1.5   Jun 26 2000 18:12:18   HERNANDO
 * Improved Speed & Readability; fixed bugs
 * 
 *    Rev 1.4   Jun 26 2000 16:43:22   HERNANDO
 * Improved Speed & Readability; fixed bugs
 * 
 *    Rev 1.3   Apr 05 2000 10:40:56   DT24433
 * removed unused headers, added revision log
 * 
*/ 


