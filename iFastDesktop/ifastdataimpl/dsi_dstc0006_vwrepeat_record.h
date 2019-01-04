// BFDataImpl header file for DataSet DSTC0006.VWRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Monday, August 08, 2016 02:17:43


#pragma once
#include <commonport.h>
#include <clientlocale.hpp>

#undef IFAST_DATAIMPL_LINKAGE
#ifdef IFAST_DATAIMPL_DLL
   #define IFAST_DATAIMPL_LINKAGE CLASS_EXPORT
#else
   #define IFAST_DATAIMPL_LINKAGE CLASS_IMPORT
#endif

namespace ifds
{
    //Field Externs
    extern const BFTextFieldId BrokerCode;
    extern const BFTextFieldId BranchCode;
    extern const BFTextFieldId SalesRepCode;
    extern const BFTextFieldId BrokerName;
    extern const BFTextFieldId BranchName;
    extern const BFTextFieldId SlsrepName;
    extern const BFDecimalFieldId Amount;
    extern const BFTextFieldId AmountType;
    extern const BFTextFieldId AmountTypeDesc;
    extern const BFTextFieldId GrossOrNet;
    extern const BFDecimalFieldId Fee;
    extern const BFTextFieldId FlatPercent;
    extern const BFTextFieldId FeeCurrency;
    extern const BFTextFieldId FeeCurrDesc;
    extern const BFDecimalFieldId AdminFeeAmt;
    extern const BFTextFieldId AdminFeeCurr;
    extern const BFTextFieldId AdminFeeCurrDesc;
    extern const BFTextFieldId PayType;
    extern const BFTextFieldId PayTypeDesc;
    extern const BFNumericFieldId InstCode;
    extern const BFDecimalFieldId SwiftCode;
    extern const BFDecimalFieldId RefNumber;
    extern const BFTextFieldId TransitNo;
    extern const BFTextFieldId BankAcctNum;
    extern const BFTextFieldId BankAcctName;
    extern const BFTextFieldId SourceOfBankAcct;
    extern const BFTextFieldId BankAcctCurrency;
    extern const BFTextFieldId BankCurrDesc;
    extern const BFTextFieldId BankAcctType;
    extern const BFTextFieldId BankAcctTypeDesc;
    extern const BFTextFieldId SrcOfFund;
    extern const BFTextFieldId SrcOFundDesc;
    extern const BFTextFieldId January;
    extern const BFTextFieldId February;
    extern const BFTextFieldId March;
    extern const BFTextFieldId April;
    extern const BFTextFieldId May;
    extern const BFTextFieldId June;
    extern const BFTextFieldId July;
    extern const BFTextFieldId August;
    extern const BFTextFieldId September;
    extern const BFTextFieldId October;
    extern const BFTextFieldId November;
    extern const BFTextFieldId December;
    extern const BFTextFieldId EndOfMonth;
    extern const BFNumericFieldId DayOfWeek;
    extern const BFDateFieldId LastProcessDate;
    extern const BFTextFieldId AddrCode;
    extern const BFTextFieldId StatusCode;
    extern const BFDateFieldId EffectiveDate;
    extern const BFDateFieldId ProcessDate;
    extern const BFDateFieldId ModDate;
    extern const BFDateFieldId StopDate;
    extern const BFTextFieldId Username;
    extern const BFTextFieldId ModUser;
    extern const BFTextFieldId AddrLine1;
    extern const BFTextFieldId AddrLine2;
    extern const BFTextFieldId AddrLine3;
    extern const BFTextFieldId AddrLine4;
    extern const BFTextFieldId AddrLine5;
    extern const BFTextFieldId PostalCode;
    extern const BFTextFieldId InstName;
    extern const BFTextFieldId SlsrepAltName;
    extern const BFTextFieldId FundCode;
    extern const BFTextFieldId ClassCode;
    extern const BFNumericFieldId PACSWPId;
    extern const BFTextFieldId TransType;
    extern const BFDecimalFieldId BankDetlVer;
    extern const BFTextFieldId PayReason1;
    extern const BFTextFieldId FundToCode;
    extern const BFTextFieldId ClassToCode;
    extern const BFNumericFieldId AccountTo;
    extern const BFTextFieldId BELFee;
    extern const BFTextFieldId BatchUser;
    extern const BFTextFieldId BatchName;
    extern const BFNumericFieldId BatchTrace;
    extern const BFDateFieldId BatchDate;
    extern const BFTextFieldId TransferType;
    extern const BFTextFieldId Frequency;
    extern const BFTextFieldId FlatPercentDesc;
    extern const BFTextFieldId FrequencyDesc;
    extern const BFTextFieldId TransTypeDesc;
    extern const BFTextFieldId EntityType;
    extern const BFDecimalFieldId EntityTypeSeq;
    extern const BFNumericFieldId TransNum;
    extern const BFTextFieldId SplitComm;
    extern const BFDateFieldId NextProcessDate;
    extern const BFTextFieldId BankIdType;
    extern const BFTextFieldId BankIdValue;
    extern const BFTextFieldId ACHProcessor;
    extern const BFDecimalFieldId BankId;
    extern const BFTextFieldId FFC;
    extern const BFTextFieldId FFC1;
    extern const BFTextFieldId BankAddr1;
    extern const BFTextFieldId BankAddr2;
    extern const BFTextFieldId BankAddr3;
    extern const BFTextFieldId BankAddr4;
    extern const BFTextFieldId BankAddr5;
    extern const BFTextFieldId BankContact;
    extern const BFTextFieldId BankCountry;
    extern const BFTextFieldId BankPostal;
    extern const BFDecimalFieldId VUBExpectedAmt;
    extern const BFDecimalFieldId VUBCollectedAmt;
    extern const BFTextFieldId PlanCode;
    extern const BFTextFieldId IndexExist;
    extern const BFDecimalFieldId InitialAmt;
    extern const BFTextFieldId VUBPayOption;
    extern const BFTextFieldId AnnualMaint;
    extern const BFTextFieldId VUBFeeType;
    extern const BFDecimalFieldId VUBFeeFrac1;
    extern const BFDecimalFieldId VUBFeeFrac2;
    extern const BFDateFieldId AnnualFeeDate;
    extern const BFDecimalFieldId VUBFeeRate;
    extern const BFDecimalFieldId ExchInFee;
    extern const BFTextFieldId ExchInFlatPercent;
    extern const BFTextFieldId ModPerm;
    extern const BFDecimalFieldId ExchOutFee;
    extern const BFTextFieldId ExchOutFlatPrcnt;
    extern const BFTextFieldId PayMethod;
    extern const BFTextFieldId FedTaxPUDOverride;
    extern const BFDecimalFieldId FedRate;
    extern const BFTextFieldId ProvTaxPUDOverride;
    extern const BFDecimalFieldId ProvRate;
    extern const BFTextFieldId PayReason2;
    extern const BFTextFieldId StopReasonPAC;
    extern const BFTextFieldId NonFinConfirms;
    extern const BFTextFieldId VerifyStat;
    extern const BFTextFieldId RDRAdvice;
    extern const BFDateFieldId EventReceiptDate;
    extern const BFTextFieldId EventReceiptTime;
    extern const BFTextFieldId SourceOfTrade;
    extern const BFTextFieldId ChannelOfTrade;
    extern const BFTextFieldId Platform;
    extern const BFTextFieldId PSDAdvice;
    extern const BFDateFieldId SignatureDate;
    extern const BFDecimalFieldId YearlyAmount;
    extern const BFDecimalFieldId CPIRate;
    extern const BFDecimalFieldId PayoutFactorRate;
    extern const BFTextFieldId AmtTypeOvrd;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_BrokerCode;
    extern const BFDataFieldProperties s_FldProp_BranchCode;
    extern const BFDataFieldProperties s_FldProp_SalesRepCode;
    extern const BFDataFieldProperties s_FldProp_BrokerName;
    extern const BFDataFieldProperties s_FldProp_BranchName;
    extern const BFDataFieldProperties s_FldProp_SlsrepName;
    extern const BFDataFieldProperties s_FldProp_Amount;
    extern const BFDataFieldProperties s_FldProp_AmountType;
    extern const BFDataFieldProperties s_FldProp_AmountTypeDesc;
    extern const BFDataFieldProperties s_FldProp_GrossOrNet;
    extern const BFDataFieldProperties s_FldProp_Fee;
    extern const BFDataFieldProperties s_FldProp_FlatPercent;
    extern const BFDataFieldProperties s_FldProp_FeeCurrency;
    extern const BFDataFieldProperties s_FldProp_FeeCurrDesc;
    extern const BFDataFieldProperties s_FldProp_AdminFeeAmt;
    extern const BFDataFieldProperties s_FldProp_AdminFeeCurr;
    extern const BFDataFieldProperties s_FldProp_AdminFeeCurrDesc;
    extern const BFDataFieldProperties s_FldProp_PayType;
    extern const BFDataFieldProperties s_FldProp_PayTypeDesc;
    extern const BFDataFieldProperties s_FldProp_InstCode;
    extern const BFDataFieldProperties s_FldProp_SwiftCode;
    extern const BFDataFieldProperties s_FldProp_RefNumber;
    extern const BFDataFieldProperties s_FldProp_TransitNo;
    extern const BFDataFieldProperties s_FldProp_BankAcctNum;
    extern const BFDataFieldProperties s_FldProp_BankAcctName;
    extern const BFDataFieldProperties s_FldProp_SourceOfBankAcct;
    extern const BFDataFieldProperties s_FldProp_BankAcctCurrency;
    extern const BFDataFieldProperties s_FldProp_BankCurrDesc;
    extern const BFDataFieldProperties s_FldProp_BankAcctType;
    extern const BFDataFieldProperties s_FldProp_BankAcctTypeDesc;
    extern const BFDataFieldProperties s_FldProp_SrcOfFund;
    extern const BFDataFieldProperties s_FldProp_SrcOFundDesc;
    extern const BFDataFieldProperties s_FldProp_January;
    extern const BFDataFieldProperties s_FldProp_February;
    extern const BFDataFieldProperties s_FldProp_March;
    extern const BFDataFieldProperties s_FldProp_April;
    extern const BFDataFieldProperties s_FldProp_May;
    extern const BFDataFieldProperties s_FldProp_June;
    extern const BFDataFieldProperties s_FldProp_July;
    extern const BFDataFieldProperties s_FldProp_August;
    extern const BFDataFieldProperties s_FldProp_September;
    extern const BFDataFieldProperties s_FldProp_October;
    extern const BFDataFieldProperties s_FldProp_November;
    extern const BFDataFieldProperties s_FldProp_December;
    extern const BFDataFieldProperties s_FldProp_EndOfMonth;
    extern const BFDataFieldProperties s_FldProp_DayOfWeek;
    extern const BFDataFieldProperties s_FldProp_LastProcessDate;
    extern const BFDataFieldProperties s_FldProp_AddrCode;
    extern const BFDataFieldProperties s_FldProp_StatusCode;
    extern const BFDataFieldProperties s_FldProp_EffectiveDate;
    extern const BFDataFieldProperties s_FldProp_ProcessDate;
    extern const BFDataFieldProperties s_FldProp_ModDate;
    extern const BFDataFieldProperties s_FldProp_StopDate;
    extern const BFDataFieldProperties s_FldProp_Username;
    extern const BFDataFieldProperties s_FldProp_ModUser;
    extern const BFDataFieldProperties s_FldProp_AddrLine1;
    extern const BFDataFieldProperties s_FldProp_AddrLine2;
    extern const BFDataFieldProperties s_FldProp_AddrLine3;
    extern const BFDataFieldProperties s_FldProp_AddrLine4;
    extern const BFDataFieldProperties s_FldProp_AddrLine5;
    extern const BFDataFieldProperties s_FldProp_PostalCode;
    extern const BFDataFieldProperties s_FldProp_InstName;
    extern const BFDataFieldProperties s_FldProp_SlsrepAltName;
    extern const BFDataFieldProperties s_FldProp_FundCode;
    extern const BFDataFieldProperties s_FldProp_ClassCode;
    extern const BFDataFieldProperties s_FldProp_PACSWPId;
    extern const BFDataFieldProperties s_FldProp_TransType;
    extern const BFDataFieldProperties s_FldProp_BankDetlVer;
    extern const BFDataFieldProperties s_FldProp_PayReason1;
    extern const BFDataFieldProperties s_FldProp_FundToCode;
    extern const BFDataFieldProperties s_FldProp_ClassToCode;
    extern const BFDataFieldProperties s_FldProp_AccountTo;
    extern const BFDataFieldProperties s_FldProp_BELFee;
    extern const BFDataFieldProperties s_FldProp_BatchUser;
    extern const BFDataFieldProperties s_FldProp_BatchName;
    extern const BFDataFieldProperties s_FldProp_BatchTrace;
    extern const BFDataFieldProperties s_FldProp_BatchDate;
    extern const BFDataFieldProperties s_FldProp_TransferType;
    extern const BFDataFieldProperties s_FldProp_Frequency;
    extern const BFDataFieldProperties s_FldProp_FlatPercentDesc;
    extern const BFDataFieldProperties s_FldProp_FrequencyDesc;
    extern const BFDataFieldProperties s_FldProp_TransTypeDesc;
    extern const BFDataFieldProperties s_FldProp_EntityType;
    extern const BFDataFieldProperties s_FldProp_EntityTypeSeq;
    extern const BFDataFieldProperties s_FldProp_TransNum;
    extern const BFDataFieldProperties s_FldProp_SplitComm;
    extern const BFDataFieldProperties s_FldProp_NextProcessDate;
    extern const BFDataFieldProperties s_FldProp_BankIdType;
    extern const BFDataFieldProperties s_FldProp_BankIdValue;
    extern const BFDataFieldProperties s_FldProp_ACHProcessor;
    extern const BFDataFieldProperties s_FldProp_BankId;
    extern const BFDataFieldProperties s_FldProp_FFC;
    extern const BFDataFieldProperties s_FldProp_FFC1;
    extern const BFDataFieldProperties s_FldProp_BankAddr1;
    extern const BFDataFieldProperties s_FldProp_BankAddr2;
    extern const BFDataFieldProperties s_FldProp_BankAddr3;
    extern const BFDataFieldProperties s_FldProp_BankAddr4;
    extern const BFDataFieldProperties s_FldProp_BankAddr5;
    extern const BFDataFieldProperties s_FldProp_BankContact;
    extern const BFDataFieldProperties s_FldProp_BankCountry;
    extern const BFDataFieldProperties s_FldProp_BankPostal;
    extern const BFDataFieldProperties s_FldProp_VUBExpectedAmt;
    extern const BFDataFieldProperties s_FldProp_VUBCollectedAmt;
    extern const BFDataFieldProperties s_FldProp_PlanCode;
    extern const BFDataFieldProperties s_FldProp_IndexExist;
    extern const BFDataFieldProperties s_FldProp_InitialAmt;
    extern const BFDataFieldProperties s_FldProp_VUBPayOption;
    extern const BFDataFieldProperties s_FldProp_AnnualMaint;
    extern const BFDataFieldProperties s_FldProp_VUBFeeType;
    extern const BFDataFieldProperties s_FldProp_VUBFeeFrac1;
    extern const BFDataFieldProperties s_FldProp_VUBFeeFrac2;
    extern const BFDataFieldProperties s_FldProp_AnnualFeeDate;
    extern const BFDataFieldProperties s_FldProp_VUBFeeRate;
    extern const BFDataFieldProperties s_FldProp_ExchInFee;
    extern const BFDataFieldProperties s_FldProp_ExchInFlatPercent;
    extern const BFDataFieldProperties s_FldProp_ModPerm;
    extern const BFDataFieldProperties s_FldProp_ExchOutFee;
    extern const BFDataFieldProperties s_FldProp_ExchOutFlatPrcnt;
    extern const BFDataFieldProperties s_FldProp_PayMethod;
    extern const BFDataFieldProperties s_FldProp_FedTaxPUDOverride;
    extern const BFDataFieldProperties s_FldProp_FedRate;
    extern const BFDataFieldProperties s_FldProp_ProvTaxPUDOverride;
    extern const BFDataFieldProperties s_FldProp_ProvRate;
    extern const BFDataFieldProperties s_FldProp_PayReason2;
    extern const BFDataFieldProperties s_FldProp_StopReasonPAC;
    extern const BFDataFieldProperties s_FldProp_NonFinConfirms;
    extern const BFDataFieldProperties s_FldProp_VerifyStat;
    extern const BFDataFieldProperties s_FldProp_RDRAdvice;
    extern const BFDataFieldProperties s_FldProp_EventReceiptDate;
    extern const BFDataFieldProperties s_FldProp_EventReceiptTime;
    extern const BFDataFieldProperties s_FldProp_SourceOfTrade;
    extern const BFDataFieldProperties s_FldProp_ChannelOfTrade;
    extern const BFDataFieldProperties s_FldProp_Platform;
    extern const BFDataFieldProperties s_FldProp_PSDAdvice;
    extern const BFDataFieldProperties s_FldProp_SignatureDate;
    extern const BFDataFieldProperties s_FldProp_YearlyAmount;
    extern const BFDataFieldProperties s_FldProp_CPIRate;
    extern const BFDataFieldProperties s_FldProp_PayoutFactorRate;
    extern const BFDataFieldProperties s_FldProp_AmtTypeOvrd;
}


class dsi_DSTC0006_VWRepeat_Record : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0006_VWRepeat_Record();
    virtual ~dsi_DSTC0006_VWRepeat_Record();

    virtual BFDataImpl* clone();

    virtual BFDataField* getElement( const BFFieldId& id );
    virtual const BFDataField* getElement( const BFFieldId& id ) const;
    virtual BFDataField* getElementByIndex( unsigned int iField );
    virtual const BFDataField* getElementByIndex( unsigned int iField ) const;


    virtual unsigned long getLargestDefinedField( void ) const;
    virtual unsigned long getDefinedByteLength( void ) const;
    virtual bool exists( const BFFieldId& id ) const;
    static bool fieldExists( const BFFieldId& id );

private:
    BFDataField* aFlds_[139];
    // Field Declarations
    BFTextField_60 BrokerCode_;
    BFTextField_60 BranchCode_;
    BFTextField_60 SalesRepCode_;
    BFTextField_60 BrokerName_;
    BFTextField_60 BranchName_;
    BFTextField_60 SlsrepName_;
    BFDecimalField Amount_;
    BFTextField_60 AmountType_;
    BFTextField_60 AmountTypeDesc_;
    BFTextField_1 GrossOrNet_;
    BFDecimalField Fee_;
    BFTextField_1 FlatPercent_;
    BFTextField_60 FeeCurrency_;
    BFTextField_60 FeeCurrDesc_;
    BFDecimalField AdminFeeAmt_;
    BFTextField_60 AdminFeeCurr_;
    BFTextField_60 AdminFeeCurrDesc_;
    BFTextField_60 PayType_;
    BFTextField_60 PayTypeDesc_;
    BFNumericField InstCode_;
    BFDecimalField SwiftCode_;
    BFDecimalField RefNumber_;
    BFTextField_60 TransitNo_;
    BFTextField_60 BankAcctNum_;
    BFTextField_60 BankAcctName_;
    BFTextField_60 SourceOfBankAcct_;
    BFTextField_60 BankAcctCurrency_;
    BFTextField_60 BankCurrDesc_;
    BFTextField_60 BankAcctType_;
    BFTextField_60 BankAcctTypeDesc_;
    BFTextField_60 SrcOfFund_;
    BFTextField_60 SrcOFundDesc_;
    BFTextField_1 January_;
    BFTextField_1 February_;
    BFTextField_1 March_;
    BFTextField_1 April_;
    BFTextField_1 May_;
    BFTextField_1 June_;
    BFTextField_1 July_;
    BFTextField_1 August_;
    BFTextField_1 September_;
    BFTextField_1 October_;
    BFTextField_1 November_;
    BFTextField_1 December_;
    BFTextField_1 EndOfMonth_;
    BFNumericField DayOfWeek_;
    BFDateField LastProcessDate_;
    BFTextField_60 AddrCode_;
    BFTextField_1 StatusCode_;
    BFDateField EffectiveDate_;
    BFDateField ProcessDate_;
    BFDateField ModDate_;
    BFDateField StopDate_;
    BFTextField_60 Username_;
    BFTextField_60 ModUser_;
    BFTextField_60 AddrLine1_;
    BFTextField_60 AddrLine2_;
    BFTextField_60 AddrLine3_;
    BFTextField_60 AddrLine4_;
    BFTextField_60 AddrLine5_;
    BFTextField<9> PostalCode_;
    BFTextField_60 InstName_;
    BFTextField_60 SlsrepAltName_;
    BFTextField<200> FundCode_;
    BFTextField<120> ClassCode_;
    BFNumericField PACSWPId_;
    BFTextField_60 TransType_;
    BFDecimalField BankDetlVer_;
    BFTextField_60 PayReason1_;
    BFTextField_60 FundToCode_;
    BFTextField_60 ClassToCode_;
    BFNumericField AccountTo_;
    BFTextField_1 BELFee_;
    BFTextField_60 BatchUser_;
    BFTextField_60 BatchName_;
    BFNumericField BatchTrace_;
    BFDateField BatchDate_;
    BFTextField<80> TransferType_;
    BFTextField_60 Frequency_;
    BFTextField_60 FlatPercentDesc_;
    BFTextField_60 FrequencyDesc_;
    BFTextField_60 TransTypeDesc_;
    BFTextField_60 EntityType_;
    BFDecimalField EntityTypeSeq_;
    BFNumericField TransNum_;
    BFTextField_1 SplitComm_;
    BFDateField NextProcessDate_;
    BFTextField<50> BankIdType_;
    BFTextField<30> BankIdValue_;
    BFTextField<15> ACHProcessor_;
    BFDecimalField BankId_;
    BFTextField<40> FFC_;
    BFTextField<40> FFC1_;
    BFTextField<40> BankAddr1_;
    BFTextField<40> BankAddr2_;
    BFTextField<40> BankAddr3_;
    BFTextField<40> BankAddr4_;
    BFTextField<40> BankAddr5_;
    BFTextField<50> BankContact_;
    BFTextField<15> BankCountry_;
    BFTextField_10 BankPostal_;
    BFDecimalField VUBExpectedAmt_;
    BFDecimalField VUBCollectedAmt_;
    BFTextField_6 PlanCode_;
    BFTextField_1 IndexExist_;
    BFDecimalField InitialAmt_;
    BFTextField_60 VUBPayOption_;
    BFTextField_1 AnnualMaint_;
    BFTextField_2 VUBFeeType_;
    BFDecimalField VUBFeeFrac1_;
    BFDecimalField VUBFeeFrac2_;
    BFDateField AnnualFeeDate_;
    BFDecimalField VUBFeeRate_;
    BFDecimalField ExchInFee_;
    BFTextField_1 ExchInFlatPercent_;
    BFTextField_1 ModPerm_;
    BFDecimalField ExchOutFee_;
    BFTextField_60 ExchOutFlatPrcnt_;
    BFTextField_60 PayMethod_;
    BFTextField_1 FedTaxPUDOverride_;
    BFDecimalField FedRate_;
    BFTextField_1 ProvTaxPUDOverride_;
    BFDecimalField ProvRate_;
    BFTextField_60 PayReason2_;
    BFTextField_60 StopReasonPAC_;
    BFTextField_10 NonFinConfirms_;
    BFTextField_60 VerifyStat_;
    BFTextField_60 RDRAdvice_;
    BFDateField EventReceiptDate_;
    BFTextField<8> EventReceiptTime_;
    BFTextField_60 SourceOfTrade_;
    BFTextField_60 ChannelOfTrade_;
    BFTextField_60 Platform_;
    BFTextField<20> PSDAdvice_;
    BFDateField SignatureDate_;
    BFDecimalField YearlyAmount_;
    BFDecimalField CPIRate_;
    BFDecimalField PayoutFactorRate_;
    BFTextField_10 AmtTypeOvrd_;
};
