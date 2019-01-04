// BFDataImpl header file for DataSet DSTC0083.VW
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Wednesday, February 07, 2018 16:50:16


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
    extern const BFTextFieldId SysCurrency;
    extern const BFTextFieldId ShrNumCtrl;
    extern const BFTextFieldId ShrNumVal;
    extern const BFTextFieldId AcctNumCtrl;
    extern const BFTextFieldId AcctNumVal;
    extern const BFTextFieldId DefaultGrp;
    extern const BFTextFieldId GrpCodeLevel;
    extern const BFTextFieldId TaxTypeUpd;
    extern const BFTextFieldId MktMailDef;
    extern const BFTextFieldId RepByBranch;
    extern const BFTextFieldId BrokerBranch;
    extern const BFTextFieldId CapAddress;
    extern const BFTextFieldId CountryVal;
    extern const BFTextFieldId MandatoryId;
    extern const BFTextFieldId BirthNameMand;
    extern const BFTextFieldId SinException;
    extern const BFTextFieldId ShadowNominee;
    extern const BFDecimalFieldId BankValid1;
    extern const BFTextFieldId BankValid2;
    extern const BFDecimalFieldId BankLayout;
    extern const BFTextFieldId SYMBrkUpd;
    extern const BFTextFieldId BrokerFund;
    extern const BFDecimalFieldId PACMinAmt;
    extern const BFDecimalFieldId PACAmtEdit;
    extern const BFTextFieldId GICAllocOnly;
    extern const BFTextFieldId DisableFee4Alloc;
    extern const BFTextFieldId BusRounding;
    extern const BFTextFieldId MultiCurrency;
    extern const BFTextFieldId SplitComm;
    extern const BFTextFieldId AcctFeeParm;
    extern const BFTextFieldId CappedFund;
    extern const BFTextFieldId BankingFormat;
    extern const BFDecimalFieldId InstCodeMax;
    extern const BFIntegerFieldId TransitNoMax;
    extern const BFDecimalFieldId BankAcctNumMax;
    extern const BFDateFieldId CurrBusDate;
    extern const BFTextFieldId MandAddLines;
    extern const BFDateFieldId CurrSysDate;
    extern const BFTimeFieldId CurrSysTime;
    extern const BFTextFieldId ChkDuplicationTrade;
    extern const BFTextFieldId InvAdvice;
    extern const BFTextFieldId AcqFeeDefault;
    extern const BFDateFieldId LastCycleDate;
    extern const BFTextFieldId AccountableMandatory;
    extern const BFTextFieldId SplitAcCode;
    extern const BFTextFieldId TRExclRedCodes;
    extern const BFTextFieldId TIKRedCodes;
    extern const BFTextFieldId DealDateTime;
    extern const BFTextFieldId EFTPurchase;
    extern const BFTextFieldId EFTPurchFuture;
    extern const BFTextFieldId GrpContribution;
    extern const BFTextFieldId AllowFractions;
    extern const BFTextFieldId SplitCommTransTypes;
    extern const BFTextFieldId CashReceiptTrack;
    extern const BFTextFieldId DepositId2;
    extern const BFTextFieldId DepositIdMandatory;
    extern const BFTextFieldId DefaultPurchPayType;
    extern const BFIntegerFieldId EFTPurchaseLeadDays;
    extern const BFTextFieldId CharWireNum;
    extern const BFTextFieldId WireNumMandatory;
    extern const BFTextFieldId WireNumDefault;
    extern const BFTextFieldId SrcOfFundMandatory;
    extern const BFTextFieldId RRIFPrevYear;
    extern const BFTextFieldId RRIFOrPayment;
    extern const BFTextFieldId RRIFValidation;
    extern const BFIntegerFieldId FundAllocLimit;
    extern const BFTextFieldId AMSOrder;
    extern const BFTextFieldId DefSetlCurrency;
    extern const BFDateFieldId PrevBusDate;
    extern const BFTextFieldId CurrChkByTaxType;
    extern const BFTextFieldId EuroAddrFormat;
    extern const BFTextFieldId InvalidCurr;
    extern const BFTextFieldId TaxTypeByCurrChk;
    extern const BFTextFieldId SegClient;
    extern const BFTextFieldId CotClient;
    extern const BFTextFieldId ResClient;
    extern const BFTextFieldId LipClient;
    extern const BFTextFieldId T550ReportMethod;
    extern const BFTextFieldId ShrEFTConsol;
    extern const BFTextFieldId PACSWPEFTConsol;
    extern const BFTextFieldId Unseizable;
    extern const BFTextFieldId RdLckdE;
    extern const BFTextFieldId RdLckdW;
    extern const BFTextFieldId TitleRestrict;
    extern const BFTextFieldId EditDeffs;
    extern const BFTextFieldId RoundFlag;
    extern const BFTextFieldId RedAccruedInt;
    extern const BFTextFieldId PQLIFLIRARedCodes;
    extern const BFTextFieldId PQLIFLIRAJuris;
    extern const BFIntegerFieldId PQLIFLIRAAage;
    extern const BFIntegerFieldId PQLIFLIRAMaxPrct;
    extern const BFTextFieldId PQLIFLIRATaxType;
    extern const BFTextFieldId AutoBanking;
    extern const BFTextFieldId RdAcctCurrency;
    extern const BFTextFieldId BankSrcAcct;
    extern const BFTextFieldId SourceOffFund;
    extern const BFTextFieldId ModRecipType;
    extern const BFDecimalFieldId SpecAcctNum;
    extern const BFTextFieldId TradeCutOff;
    extern const BFTextFieldId PartTransAsFull;
    extern const BFTextFieldId CheqDeliveryDefault;
    extern const BFTextFieldId SplitComm100;
    extern const BFTextFieldId CashDistribRule;
    extern const BFTextFieldId ValidDistributionPayType;
    extern const BFTextFieldId AllFundsTransfers;
    extern const BFTextFieldId TfrToDiffSH;
    extern const BFTextFieldId DeathRedCode;
    extern const BFTextFieldId SpouseBenefReLn;
    extern const BFTextFieldId ChildBenefReLn;
    extern const BFTextFieldId MultiAcctEachShrNum;
    extern const BFTextFieldId UpdOrdType;
    extern const BFIntegerFieldId CommissionType;
    extern const BFTextFieldId Residency1;
    extern const BFTextFieldId Residency2;
    extern const BFTextFieldId Residency3;
    extern const BFTextFieldId DefltRedCodeFlag;
    extern const BFTextFieldId DefltRedCode;
    extern const BFTextFieldId FundEligSlsRepLvl;
    extern const BFTextFieldId WrapAccount;
    extern const BFTextFieldId DistribFundsValidate;
    extern const BFTextFieldId XSFundsValidate;
    extern const BFTextFieldId ClientAMSType;
    extern const BFIntegerFieldId ClassRule;
    extern const BFTextFieldId ProfileCodeDflt;
    extern const BFTextFieldId MgmtFeePayOptDflt;
    extern const BFTextFieldId MgmtCoPayReq;
    extern const BFTextFieldId SplitPreferenceOption;
    extern const BFTextFieldId RES2Client;
    extern const BFTextFieldId QESIClient;
    extern const BFDateFieldId PSE_EAPEditDate;
    extern const BFDateFieldId EligDateforCLB;
    extern const BFDateFieldId NonTrustStartDate;
    extern const BFDateFieldId NonTrustStopDate;
    extern const BFTextFieldId IsNonTrustee;
    extern const BFTextFieldId AutoDocTracking;
    extern const BFTextFieldId DfltConfDetlKeyValue;
    extern const BFTextFieldId DfltConfDetlDefValue;
    extern const BFTextFieldId FundSERVClient;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_SysCurrency;
    extern const BFDataFieldProperties s_FldProp_ShrNumCtrl;
    extern const BFDataFieldProperties s_FldProp_ShrNumVal;
    extern const BFDataFieldProperties s_FldProp_AcctNumCtrl;
    extern const BFDataFieldProperties s_FldProp_AcctNumVal;
    extern const BFDataFieldProperties s_FldProp_DefaultGrp;
    extern const BFDataFieldProperties s_FldProp_GrpCodeLevel;
    extern const BFDataFieldProperties s_FldProp_TaxTypeUpd;
    extern const BFDataFieldProperties s_FldProp_MktMailDef;
    extern const BFDataFieldProperties s_FldProp_RepByBranch;
    extern const BFDataFieldProperties s_FldProp_BrokerBranch;
    extern const BFDataFieldProperties s_FldProp_CapAddress;
    extern const BFDataFieldProperties s_FldProp_CountryVal;
    extern const BFDataFieldProperties s_FldProp_MandatoryId;
    extern const BFDataFieldProperties s_FldProp_BirthNameMand;
    extern const BFDataFieldProperties s_FldProp_SinException;
    extern const BFDataFieldProperties s_FldProp_ShadowNominee;
    extern const BFDataFieldProperties s_FldProp_BankValid1;
    extern const BFDataFieldProperties s_FldProp_BankValid2;
    extern const BFDataFieldProperties s_FldProp_BankLayout;
    extern const BFDataFieldProperties s_FldProp_SYMBrkUpd;
    extern const BFDataFieldProperties s_FldProp_BrokerFund;
    extern const BFDataFieldProperties s_FldProp_PACMinAmt;
    extern const BFDataFieldProperties s_FldProp_PACAmtEdit;
    extern const BFDataFieldProperties s_FldProp_GICAllocOnly;
    extern const BFDataFieldProperties s_FldProp_DisableFee4Alloc;
    extern const BFDataFieldProperties s_FldProp_BusRounding;
    extern const BFDataFieldProperties s_FldProp_MultiCurrency;
    extern const BFDataFieldProperties s_FldProp_SplitComm;
    extern const BFDataFieldProperties s_FldProp_AcctFeeParm;
    extern const BFDataFieldProperties s_FldProp_CappedFund;
    extern const BFDataFieldProperties s_FldProp_BankingFormat;
    extern const BFDataFieldProperties s_FldProp_InstCodeMax;
    extern const BFDataFieldProperties s_FldProp_TransitNoMax;
    extern const BFDataFieldProperties s_FldProp_BankAcctNumMax;
    extern const BFDataFieldProperties s_FldProp_CurrBusDate;
    extern const BFDataFieldProperties s_FldProp_MandAddLines;
    extern const BFDataFieldProperties s_FldProp_CurrSysDate;
    extern const BFDataFieldProperties s_FldProp_CurrSysTime;
    extern const BFDataFieldProperties s_FldProp_ChkDuplicationTrade;
    extern const BFDataFieldProperties s_FldProp_InvAdvice;
    extern const BFDataFieldProperties s_FldProp_AcqFeeDefault;
    extern const BFDataFieldProperties s_FldProp_LastCycleDate;
    extern const BFDataFieldProperties s_FldProp_AccountableMandatory;
    extern const BFDataFieldProperties s_FldProp_SplitAcCode;
    extern const BFDataFieldProperties s_FldProp_TRExclRedCodes;
    extern const BFDataFieldProperties s_FldProp_TIKRedCodes;
    extern const BFDataFieldProperties s_FldProp_DealDateTime;
    extern const BFDataFieldProperties s_FldProp_EFTPurchase;
    extern const BFDataFieldProperties s_FldProp_EFTPurchFuture;
    extern const BFDataFieldProperties s_FldProp_GrpContribution;
    extern const BFDataFieldProperties s_FldProp_AllowFractions;
    extern const BFDataFieldProperties s_FldProp_SplitCommTransTypes;
    extern const BFDataFieldProperties s_FldProp_CashReceiptTrack;
    extern const BFDataFieldProperties s_FldProp_DepositId2;
    extern const BFDataFieldProperties s_FldProp_DepositIdMandatory;
    extern const BFDataFieldProperties s_FldProp_DefaultPurchPayType;
    extern const BFDataFieldProperties s_FldProp_EFTPurchaseLeadDays;
    extern const BFDataFieldProperties s_FldProp_CharWireNum;
    extern const BFDataFieldProperties s_FldProp_WireNumMandatory;
    extern const BFDataFieldProperties s_FldProp_WireNumDefault;
    extern const BFDataFieldProperties s_FldProp_SrcOfFundMandatory;
    extern const BFDataFieldProperties s_FldProp_RRIFPrevYear;
    extern const BFDataFieldProperties s_FldProp_RRIFOrPayment;
    extern const BFDataFieldProperties s_FldProp_RRIFValidation;
    extern const BFDataFieldProperties s_FldProp_FundAllocLimit;
    extern const BFDataFieldProperties s_FldProp_AMSOrder;
    extern const BFDataFieldProperties s_FldProp_DefSetlCurrency;
    extern const BFDataFieldProperties s_FldProp_PrevBusDate;
    extern const BFDataFieldProperties s_FldProp_CurrChkByTaxType;
    extern const BFDataFieldProperties s_FldProp_EuroAddrFormat;
    extern const BFDataFieldProperties s_FldProp_InvalidCurr;
    extern const BFDataFieldProperties s_FldProp_TaxTypeByCurrChk;
    extern const BFDataFieldProperties s_FldProp_SegClient;
    extern const BFDataFieldProperties s_FldProp_CotClient;
    extern const BFDataFieldProperties s_FldProp_ResClient;
    extern const BFDataFieldProperties s_FldProp_LipClient;
    extern const BFDataFieldProperties s_FldProp_T550ReportMethod;
    extern const BFDataFieldProperties s_FldProp_ShrEFTConsol;
    extern const BFDataFieldProperties s_FldProp_PACSWPEFTConsol;
    extern const BFDataFieldProperties s_FldProp_Unseizable;
    extern const BFDataFieldProperties s_FldProp_RdLckdE;
    extern const BFDataFieldProperties s_FldProp_RdLckdW;
    extern const BFDataFieldProperties s_FldProp_TitleRestrict;
    extern const BFDataFieldProperties s_FldProp_EditDeffs;
    extern const BFDataFieldProperties s_FldProp_RoundFlag;
    extern const BFDataFieldProperties s_FldProp_RedAccruedInt;
    extern const BFDataFieldProperties s_FldProp_PQLIFLIRARedCodes;
    extern const BFDataFieldProperties s_FldProp_PQLIFLIRAJuris;
    extern const BFDataFieldProperties s_FldProp_PQLIFLIRAAage;
    extern const BFDataFieldProperties s_FldProp_PQLIFLIRAMaxPrct;
    extern const BFDataFieldProperties s_FldProp_PQLIFLIRATaxType;
    extern const BFDataFieldProperties s_FldProp_AutoBanking;
    extern const BFDataFieldProperties s_FldProp_RdAcctCurrency;
    extern const BFDataFieldProperties s_FldProp_BankSrcAcct;
    extern const BFDataFieldProperties s_FldProp_SourceOffFund;
    extern const BFDataFieldProperties s_FldProp_ModRecipType;
    extern const BFDataFieldProperties s_FldProp_SpecAcctNum;
    extern const BFDataFieldProperties s_FldProp_TradeCutOff;
    extern const BFDataFieldProperties s_FldProp_PartTransAsFull;
    extern const BFDataFieldProperties s_FldProp_CheqDeliveryDefault;
    extern const BFDataFieldProperties s_FldProp_SplitComm100;
    extern const BFDataFieldProperties s_FldProp_CashDistribRule;
    extern const BFDataFieldProperties s_FldProp_ValidDistributionPayType;
    extern const BFDataFieldProperties s_FldProp_AllFundsTransfers;
    extern const BFDataFieldProperties s_FldProp_TfrToDiffSH;
    extern const BFDataFieldProperties s_FldProp_DeathRedCode;
    extern const BFDataFieldProperties s_FldProp_SpouseBenefReLn;
    extern const BFDataFieldProperties s_FldProp_ChildBenefReLn;
    extern const BFDataFieldProperties s_FldProp_MultiAcctEachShrNum;
    extern const BFDataFieldProperties s_FldProp_UpdOrdType;
    extern const BFDataFieldProperties s_FldProp_CommissionType;
    extern const BFDataFieldProperties s_FldProp_Residency1;
    extern const BFDataFieldProperties s_FldProp_Residency2;
    extern const BFDataFieldProperties s_FldProp_Residency3;
    extern const BFDataFieldProperties s_FldProp_DefltRedCodeFlag;
    extern const BFDataFieldProperties s_FldProp_DefltRedCode;
    extern const BFDataFieldProperties s_FldProp_FundEligSlsRepLvl;
    extern const BFDataFieldProperties s_FldProp_WrapAccount;
    extern const BFDataFieldProperties s_FldProp_DistribFundsValidate;
    extern const BFDataFieldProperties s_FldProp_XSFundsValidate;
    extern const BFDataFieldProperties s_FldProp_ClientAMSType;
    extern const BFDataFieldProperties s_FldProp_ClassRule;
    extern const BFDataFieldProperties s_FldProp_ProfileCodeDflt;
    extern const BFDataFieldProperties s_FldProp_MgmtFeePayOptDflt;
    extern const BFDataFieldProperties s_FldProp_MgmtCoPayReq;
    extern const BFDataFieldProperties s_FldProp_SplitPreferenceOption;
    extern const BFDataFieldProperties s_FldProp_RES2Client;
    extern const BFDataFieldProperties s_FldProp_QESIClient;
    extern const BFDataFieldProperties s_FldProp_PSE_EAPEditDate;
    extern const BFDataFieldProperties s_FldProp_EligDateforCLB;
    extern const BFDataFieldProperties s_FldProp_NonTrustStartDate;
    extern const BFDataFieldProperties s_FldProp_NonTrustStopDate;
    extern const BFDataFieldProperties s_FldProp_IsNonTrustee;
    extern const BFDataFieldProperties s_FldProp_AutoDocTracking;
    extern const BFDataFieldProperties s_FldProp_DfltConfDetlKeyValue;
    extern const BFDataFieldProperties s_FldProp_DfltConfDetlDefValue;
    extern const BFDataFieldProperties s_FldProp_FundSERVClient;
}


class dsi_DSTC0083_VW : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0083_VW();
    virtual ~dsi_DSTC0083_VW();

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
    BFDataField* aFlds_[138];
    // Field Declarations
    BFTextField_60 SysCurrency_;
    BFTextField_60 ShrNumCtrl_;
    BFTextField_1 ShrNumVal_;
    BFTextField_60 AcctNumCtrl_;
    BFTextField_1 AcctNumVal_;
    BFTextField_60 DefaultGrp_;
    BFTextField_60 GrpCodeLevel_;
    BFTextField_1 TaxTypeUpd_;
    BFTextField_1 MktMailDef_;
    BFTextField_1 RepByBranch_;
    BFTextField_1 BrokerBranch_;
    BFTextField_1 CapAddress_;
    BFTextField_1 CountryVal_;
    BFTextField_60 MandatoryId_;
    BFTextField_1 BirthNameMand_;
    BFTextField<200> SinException_;
    BFTextField_1 ShadowNominee_;
    BFDecimalField BankValid1_;
    BFTextField_1 BankValid2_;
    BFDecimalField BankLayout_;
    BFTextField_1 SYMBrkUpd_;
    BFTextField_1 BrokerFund_;
    BFDecimalField PACMinAmt_;
    BFDecimalField PACAmtEdit_;
    BFTextField_1 GICAllocOnly_;
    BFTextField_1 DisableFee4Alloc_;
    BFTextField_1 BusRounding_;
    BFTextField_1 MultiCurrency_;
    BFTextField_1 SplitComm_;
    BFTextField_1 AcctFeeParm_;
    BFTextField_60 CappedFund_;
    BFTextField_1 BankingFormat_;
    BFDecimalField InstCodeMax_;
    BFIntegerField TransitNoMax_;
    BFDecimalField BankAcctNumMax_;
    BFDateField CurrBusDate_;
    BFTextField_60 MandAddLines_;
    BFDateField CurrSysDate_;
    BFTimeField CurrSysTime_;
    BFTextField_1 ChkDuplicationTrade_;
    BFTextField_1 InvAdvice_;
    BFTextField_1 AcqFeeDefault_;
    BFDateField LastCycleDate_;
    BFTextField_1 AccountableMandatory_;
    BFTextField_1 SplitAcCode_;
    BFTextField_60 TRExclRedCodes_;
    BFTextField_60 TIKRedCodes_;
    BFTextField_1 DealDateTime_;
    BFTextField_1 EFTPurchase_;
    BFTextField_1 EFTPurchFuture_;
    BFTextField_1 GrpContribution_;
    BFTextField_1 AllowFractions_;
    BFTextField_60 SplitCommTransTypes_;
    BFTextField_1 CashReceiptTrack_;
    BFTextField_1 DepositId2_;
    BFTextField_60 DepositIdMandatory_;
    BFTextField_10 DefaultPurchPayType_;
    BFIntegerField EFTPurchaseLeadDays_;
    BFTextField_1 CharWireNum_;
    BFTextField_1 WireNumMandatory_;
    BFTextField_1 WireNumDefault_;
    BFTextField_1 SrcOfFundMandatory_;
    BFTextField_1 RRIFPrevYear_;
    BFTextField_1 RRIFOrPayment_;
    BFTextField_1 RRIFValidation_;
    BFIntegerField FundAllocLimit_;
    BFTextField_1 AMSOrder_;
    BFTextField_1 DefSetlCurrency_;
    BFDateField PrevBusDate_;
    BFTextField_1 CurrChkByTaxType_;
    BFTextField_1 EuroAddrFormat_;
    BFTextField_60 InvalidCurr_;
    BFTextField_60 TaxTypeByCurrChk_;
    BFTextField_1 SegClient_;
    BFTextField_1 CotClient_;
    BFTextField_1 ResClient_;
    BFTextField_1 LipClient_;
    BFTextField_1 T550ReportMethod_;
    BFTextField_1 ShrEFTConsol_;
    BFTextField_1 PACSWPEFTConsol_;
    BFTextField_1 Unseizable_;
    BFTextField_1 RdLckdE_;
    BFTextField_1 RdLckdW_;
    BFTextField_1 TitleRestrict_;
    BFTextField_1 EditDeffs_;
    BFTextField_60 RoundFlag_;
    BFTextField_1 RedAccruedInt_;
    BFTextField_60 PQLIFLIRARedCodes_;
    BFTextField_60 PQLIFLIRAJuris_;
    BFIntegerField PQLIFLIRAAage_;
    BFIntegerField PQLIFLIRAMaxPrct_;
    BFTextField_60 PQLIFLIRATaxType_;
    BFTextField_1 AutoBanking_;
    BFTextField_1 RdAcctCurrency_;
    BFTextField_1 BankSrcAcct_;
    BFTextField_1 SourceOffFund_;
    BFTextField_1 ModRecipType_;
    BFDecimalField SpecAcctNum_;
    BFTextField_1 TradeCutOff_;
    BFTextField_1 PartTransAsFull_;
    BFTextField_10 CheqDeliveryDefault_;
    BFTextField_1 SplitComm100_;
    BFTextField_1 CashDistribRule_;
    BFTextField_10 ValidDistributionPayType_;
    BFTextField_1 AllFundsTransfers_;
    BFTextField_1 TfrToDiffSH_;
    BFTextField_60 DeathRedCode_;
    BFTextField_60 SpouseBenefReLn_;
    BFTextField_60 ChildBenefReLn_;
    BFTextField_1 MultiAcctEachShrNum_;
    BFTextField_1 UpdOrdType_;
    BFIntegerField CommissionType_;
    BFTextField_60 Residency1_;
    BFTextField_60 Residency2_;
    BFTextField_60 Residency3_;
    BFTextField_1 DefltRedCodeFlag_;
    BFTextField_60 DefltRedCode_;
    BFTextField_1 FundEligSlsRepLvl_;
    BFTextField_1 WrapAccount_;
    BFTextField_1 DistribFundsValidate_;
    BFTextField_10 XSFundsValidate_;
    BFTextField_60 ClientAMSType_;
    BFIntegerField ClassRule_;
    BFTextField_60 ProfileCodeDflt_;
    BFTextField_60 MgmtFeePayOptDflt_;
    BFTextField_1 MgmtCoPayReq_;
    BFTextField_60 SplitPreferenceOption_;
    BFTextField_10 RES2Client_;
    BFTextField_10 QESIClient_;
    BFDateField PSE_EAPEditDate_;
    BFDateField EligDateforCLB_;
    BFDateField NonTrustStartDate_;
    BFDateField NonTrustStopDate_;
    BFTextField_1 IsNonTrustee_;
    BFTextField_10 AutoDocTracking_;
    BFTextField_60 DfltConfDetlKeyValue_;
    BFTextField_60 DfltConfDetlDefValue_;
    BFTextField_1 FundSERVClient_;
};
