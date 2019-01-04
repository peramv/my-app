// BFDataImpl header file for DataSet DSTC0054.VW
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Monday, October 29, 2018 11:44:02


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
    extern const BFTextFieldId Broker;
    extern const BFTextFieldId Branch;
    extern const BFTextFieldId SlsrepCode;
    extern const BFTextFieldId SettleCurrency;
    extern const BFTextFieldId SettleCurrName;
    extern const BFDecimalFieldId ExchRate;
    extern const BFDecimalFieldId Fee;
    extern const BFTextFieldId FlatPercent;
    extern const BFTextFieldId FeeCurrency;
    extern const BFTextFieldId BELFee;
    extern const BFDecimalFieldId AdminFeeAmt;
    extern const BFDecimalFieldId OverrideDSC;
    extern const BFTextFieldId OverrideDSCDesc;
    extern const BFDecimalFieldId OverrideAmt;
    extern const BFTextFieldId OverrideTax;
    extern const BFDecimalFieldId FedRate;
    extern const BFTextFieldId TransRatePUDFed;
    extern const BFDecimalFieldId ProvRate;
    extern const BFTextFieldId TransRatePUDProv;
    extern const BFTextFieldId ProvSales;
    extern const BFTextFieldId ProvSalesName;
    extern const BFTextFieldId DepositType;
    extern const BFTextFieldId DepositTypeDesc;
    extern const BFTextFieldId RedCode;
    extern const BFTextFieldId RedCodeDesc;
    extern const BFTextFieldId Payment;
    extern const BFTextFieldId PayType2;
    extern const BFTextFieldId PayTypeDesc;
    extern const BFTextFieldId AddrCode;
    extern const BFTextFieldId AddrLine;
    extern const BFTextFieldId SuppressCode;
    extern const BFTextFieldId ChqSupCodeDesc;
    extern const BFTextFieldId OrderSource;
    extern const BFTextFieldId OrderSrcDesc;
    extern const BFTextFieldId SettleSource;
    extern const BFTextFieldId SettleSrcDesc;
    extern const BFTextFieldId SrcOfFund;
    extern const BFTextFieldId SrcOfFundDesc;
    extern const BFTextFieldId SrcOfAccount;
    extern const BFTextFieldId SettleType;
    extern const BFTextFieldId SettleTypeDesc;
    extern const BFTextFieldId ExpGNSettle;
    extern const BFTextFieldId SettledBy;
    extern const BFTextFieldId SettledByDesc;
    extern const BFTextFieldId RoundFlag;
    extern const BFTextFieldId RoundFlagDesc;
    extern const BFTextFieldId CreditFreq;
    extern const BFTextFieldId CreditFreqDesc;
    extern const BFTextFieldId ExtraCommission;
    extern const BFTextFieldId CertRequired;
    extern const BFTextFieldId CertIssued;
    extern const BFTextFieldId ConfirmRequired;
    extern const BFTextFieldId OnStmt;
    extern const BFTextFieldId RecptIssued;
    extern const BFTextFieldId ExclMFCSSettle;
    extern const BFDateFieldId GuaranteeDate;
    extern const BFDateFieldId MaturityDate;
    extern const BFDecimalFieldId InterestRate;
    extern const BFTextFieldId BrokerName;
    extern const BFTextFieldId BranchName;
    extern const BFTextFieldId SlsrepName;
    extern const BFTextFieldId SlsrepAltName;
    extern const BFTextFieldId DepId;
    extern const BFTextFieldId Remarks1;
    extern const BFTextFieldId Remarks2;
    extern const BFTextFieldId Remarks3;
    extern const BFTextFieldId RejCode;
    extern const BFTextFieldId RejCodeDesc;
    extern const BFTextFieldId Accountable;
    extern const BFTextFieldId AcctableDesc;
    extern const BFDateFieldId DepositDate;
    extern const BFTextFieldId TimeStamp;
    extern const BFDateFieldId ProcessDate;
    extern const BFTextFieldId Allocation;
    extern const BFDecimalFieldId CansimRate;
    extern const BFTextFieldId InitPurch;
    extern const BFTextFieldId BackDatedReason;
    extern const BFTextFieldId SplitComm;
    extern const BFDateFieldId DealDate;
    extern const BFTextFieldId DealTime;
    extern const BFDecimalFieldId DSCOverrideCode;
    extern const BFDecimalFieldId DSCOverrideAmt;
    extern const BFNumericFieldId AccountTo;
    extern const BFTextFieldId FundTo;
    extern const BFTextFieldId ClassToCode;
    extern const BFTextFieldId TransType;
    extern const BFTextFieldId rxFundCode;
    extern const BFTextFieldId rxClassCode;
    extern const BFDecimalFieldId Amount;
    extern const BFTextFieldId AmountType;
    extern const BFTextFieldId GrossNetMethod;
    extern const BFTextFieldId UseEnteredFee;
    extern const BFDecimalFieldId ExchInFee;
    extern const BFTextFieldId ExchInFlatPercent;
    extern const BFTextFieldId TransModPerm;
    extern const BFTextFieldId FirstName;
    extern const BFTextFieldId LastName;
    extern const BFTextFieldId InitPurchDesc;
    extern const BFTextFieldId ConfirmReqDesc;
    extern const BFTextFieldId RecptIssuedDesc;
    extern const BFTextFieldId Baycom;
    extern const BFTextFieldId BayComTo;
    extern const BFTextFieldId BankChrgs;
    extern const BFDateFieldId ValueDate;
    extern const BFTextFieldId PayMethod;
    extern const BFTextFieldId ACHProcessor;
    extern const BFTextFieldId ToBrokerCode;
    extern const BFTextFieldId ToSlsRepCode;
    extern const BFTextFieldId NetworkID;
    extern const BFTextFieldId ExtTransNum;
    extern const BFTextFieldId SendRefNum;
    extern const BFTextFieldId PartRefNum;
    extern const BFTextFieldId MasterRefNum;
    extern const BFDecimalFieldId ExchOutFee;
    extern const BFTextFieldId ExchOutFlatPrcnt;
    extern const BFTextFieldId ChargeERSTTRFee;
    extern const BFTextFieldId ChargeWDFee;
    extern const BFIntegerFieldId MirTransNum;
    extern const BFTextFieldId BorrowedFunds;
    extern const BFNumericFieldId TransSeq;
    extern const BFTextFieldId FrSettlLocCode;
    extern const BFTextFieldId FrDeliveryTo;
    extern const BFTextFieldId FrSettlLocDescription;
    extern const BFTextFieldId FrInFavourOf;
    extern const BFTextFieldId FrForAccount;
    extern const BFTextFieldId FrClearingMethod;
    extern const BFTextFieldId ToSettlLocCode;
    extern const BFTextFieldId ToDeliveryTo;
    extern const BFTextFieldId ToSettlLocDescription;
    extern const BFTextFieldId ToInFavourOf;
    extern const BFTextFieldId ToForAccount;
    extern const BFTextFieldId ToClearingMethod;
    extern const BFDecimalFieldId FeeTo;
    extern const BFTextFieldId ADLFeeCharge;
    extern const BFTextFieldId LSIFCode;
    extern const BFTextFieldId AltAccount;
    extern const BFTextFieldId RefNum;
    extern const BFTextFieldId FundWKN;
    extern const BFTextFieldId FundISIN;
    extern const BFTextFieldId FundToWKN;
    extern const BFTextFieldId FundToISIN;
    extern const BFTextFieldId AcqFeeOption;
    extern const BFTextFieldId SettleDateOverriden;
    extern const BFTextFieldId FrSettlInstrCode;
    extern const BFTextFieldId ToSettlInstrCode;
    extern const BFTextFieldId FundBrokerCode;
    extern const BFTextFieldId AggregateOption;
    extern const BFDateFieldId BrkSettlDate;
    extern const BFTextFieldId OtherConfirmType;
    extern const BFDecimalFieldId ExternalPrice;
    extern const BFDateFieldId ExternalSettleDate;
    extern const BFDecimalFieldId ExternalSettleAmt;
    extern const BFDecimalFieldId ROAAmount;
    extern const BFTextFieldId DeliveryMethod;
    extern const BFNumericFieldId AdjTransNum;
    extern const BFNumericFieldId TransId;
    extern const BFNumericFieldId SplitCommRebookTransID;
    extern const BFDecimalFieldId Cost;
    extern const BFDecimalFieldId TIS;
    extern const BFTextFieldId OverrideCost;
    extern const BFTextFieldId OverrideTIS;
    extern const BFTextFieldId MCHFileIndicator;
    extern const BFTextFieldId SecRecFileIndicator;
    extern const BFTextFieldId ESGSettle;
    extern const BFTextFieldId NSCCControlNumber;
    extern const BFTextFieldId PayInstructExists;
    extern const BFTextFieldId PayInstrOption;
    extern const BFTextFieldId MFPayment;
    extern const BFTextFieldId Indc;
    extern const BFDateFieldId ModDate;
    extern const BFTextFieldId ModUser;
    extern const BFTextFieldId RcptStatus;
    extern const BFTextFieldId LinkedEntityName;
    extern const BFDecimalFieldId LinkedEntityId;
    extern const BFTextFieldId StcPendTrdAuthorization;
    extern const BFDecimalFieldId AssocTransId;
    extern const BFTextFieldId GRRepayReason;
    extern const BFTextFieldId RESPReportHRDC;
    extern const BFIntegerFieldId RESPContrDetlTaxYear;
    extern const BFTextFieldId Tainted;
    extern const BFIntegerFieldId OCRdmYear;
    extern const BFDecimalFieldId AssistedContrAmt;
    extern const BFDecimalFieldId AcctOwnerID;
    extern const BFTextFieldId AcctOwnerName;
    extern const BFTextFieldId NetworkRespRequired;
    extern const BFDecimalFieldId EAPCESGPaid;
    extern const BFTextFieldId IntInvestUUID;
    extern const BFTextFieldId InvHisNumber;
    extern const BFTextFieldId InvHisStatus;
    extern const BFTextFieldId IntCalcMthd;
    extern const BFTextFieldId IntInvestType;
    extern const BFIntegerFieldId InvestTerm;
    extern const BFDecimalFieldId IntRate;
    extern const BFDateFieldId GIMaturityDate;
    extern const BFTextFieldId IntCredFreq;
    extern const BFDateFieldId NextIntCredDate;
    extern const BFDecimalFieldId AddlAmt;
    extern const BFTextFieldId CommRedRate;
    extern const BFTextFieldId ForcedRate;
    extern const BFDecimalFieldId InvHisInvestId;
    extern const BFTextFieldId PFCrystalisation;
    extern const BFTextFieldId PendTrdContract;
    extern const BFDateFieldId ValuationDt;
    extern const BFTextFieldId PaymentInfo;
    extern const BFTextFieldId GuaranteesOverride;
    extern const BFTextFieldId RedemOrder;
    extern const BFTextFieldId RightToCancel;
    extern const BFTextFieldId RDRAdvice;
    extern const BFTextFieldId SDRTExemptCode;
    extern const BFDecimalFieldId ForcedRateAmt;
    extern const BFTextFieldId PSDAdvice;
    extern const BFTextFieldId PymtRoutingMthd;
    extern const BFDateFieldId EventReceiptDate;
    extern const BFTextFieldId EventReceiptTime;
    extern const BFTextFieldId SourceOfTrade;
    extern const BFTextFieldId ChannelOfTrade;
    extern const BFTextFieldId Platform;
    extern const BFTextFieldId SettleNetwork;
    extern const BFTextFieldId DeliveryNetwork;
    extern const BFTextFieldId Verified;
    extern const BFTextFieldId VerifiedBy;
    extern const BFTextFieldId ToCashMsgType;
    extern const BFTextFieldId ToIntermediaryBank;
    extern const BFTextFieldId ToReceivingBank;
    extern const BFTextFieldId ToBeneficiary;
    extern const BFTextFieldId ToSpecialInstructions;
    extern const BFTextFieldId ToSettlementAccount;
    extern const BFTextFieldId ToInternalSettlementAccount;
    extern const BFTextFieldId FrCashMsgType;
    extern const BFTextFieldId FrIntermediaryBank;
    extern const BFTextFieldId FrReceivingBank;
    extern const BFTextFieldId FrBeneficiary;
    extern const BFTextFieldId FrSpecialInstructions;
    extern const BFTextFieldId FrSettlementAccount;
    extern const BFTextFieldId FrInternalSettlementAccount;
    extern const BFDecimalFieldId G1Impact;
    extern const BFDecimalFieldId G2Impact;
    extern const BFNumericFieldId CrossSysAcctNum;
    extern const BFTextFieldId AggregationType;
    extern const BFTextFieldId SourceofFundsChecked;
    extern const BFTextFieldId ExternalInstitution;
    extern const BFTextFieldId FundLFC;
    extern const BFTextFieldId FundToLFC;
    extern const BFTextFieldId RefundAmtOpt;
    extern const BFTextFieldId Deconversion;
    extern const BFTextFieldId OrderRouting;
    extern const BFDateFieldId TradeInDate;
    extern const BFDateFieldId ValuationInDt;
    extern const BFTextFieldId FrCSDLocation;
    extern const BFTextFieldId FrCSDAcctNum;
    extern const BFTextFieldId ToCSDLocation;
    extern const BFTextFieldId ToCSDAcctNum;
    extern const BFTextFieldId PricingCode;

    extern const BFTextFieldId DilutionLinkNum;
    extern const BFTextFieldId FSRVLinkNum;
    extern const BFTextFieldId PriceInCode;
    extern const BFTextFieldId FullMoneyOutIndc;
    extern const BFTextFieldId GateOverrideIndicator;
    extern const BFDateFieldId RDSPPaymtDate;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_Broker;
    extern const BFDataFieldProperties s_FldProp_Branch;
    extern const BFDataFieldProperties s_FldProp_SlsrepCode;
    extern const BFDataFieldProperties s_FldProp_SettleCurrency;
    extern const BFDataFieldProperties s_FldProp_SettleCurrName;
    extern const BFDataFieldProperties s_FldProp_ExchRate;
    extern const BFDataFieldProperties s_FldProp_Fee;
    extern const BFDataFieldProperties s_FldProp_FlatPercent;
    extern const BFDataFieldProperties s_FldProp_FeeCurrency;
    extern const BFDataFieldProperties s_FldProp_BELFee;
    extern const BFDataFieldProperties s_FldProp_AdminFeeAmt;
    extern const BFDataFieldProperties s_FldProp_OverrideDSC;
    extern const BFDataFieldProperties s_FldProp_OverrideDSCDesc;
    extern const BFDataFieldProperties s_FldProp_OverrideAmt;
    extern const BFDataFieldProperties s_FldProp_OverrideTax;
    extern const BFDataFieldProperties s_FldProp_FedRate;
    extern const BFDataFieldProperties s_FldProp_TransRatePUDFed;
    extern const BFDataFieldProperties s_FldProp_ProvRate;
    extern const BFDataFieldProperties s_FldProp_TransRatePUDProv;
    extern const BFDataFieldProperties s_FldProp_ProvSales;
    extern const BFDataFieldProperties s_FldProp_ProvSalesName;
    extern const BFDataFieldProperties s_FldProp_DepositType;
    extern const BFDataFieldProperties s_FldProp_DepositTypeDesc;
    extern const BFDataFieldProperties s_FldProp_RedCode;
    extern const BFDataFieldProperties s_FldProp_RedCodeDesc;
    extern const BFDataFieldProperties s_FldProp_Payment;
    extern const BFDataFieldProperties s_FldProp_PayType2;
    extern const BFDataFieldProperties s_FldProp_PayTypeDesc;
    extern const BFDataFieldProperties s_FldProp_AddrCode;
    extern const BFDataFieldProperties s_FldProp_AddrLine;
    extern const BFDataFieldProperties s_FldProp_SuppressCode;
    extern const BFDataFieldProperties s_FldProp_ChqSupCodeDesc;
    extern const BFDataFieldProperties s_FldProp_OrderSource;
    extern const BFDataFieldProperties s_FldProp_OrderSrcDesc;
    extern const BFDataFieldProperties s_FldProp_SettleSource;
    extern const BFDataFieldProperties s_FldProp_SettleSrcDesc;
    extern const BFDataFieldProperties s_FldProp_SrcOfFund;
    extern const BFDataFieldProperties s_FldProp_SrcOfFundDesc;
    extern const BFDataFieldProperties s_FldProp_SrcOfAccount;
    extern const BFDataFieldProperties s_FldProp_SettleType;
    extern const BFDataFieldProperties s_FldProp_SettleTypeDesc;
    extern const BFDataFieldProperties s_FldProp_ExpGNSettle;
    extern const BFDataFieldProperties s_FldProp_SettledBy;
    extern const BFDataFieldProperties s_FldProp_SettledByDesc;
    extern const BFDataFieldProperties s_FldProp_RoundFlag;
    extern const BFDataFieldProperties s_FldProp_RoundFlagDesc;
    extern const BFDataFieldProperties s_FldProp_CreditFreq;
    extern const BFDataFieldProperties s_FldProp_CreditFreqDesc;
    extern const BFDataFieldProperties s_FldProp_ExtraCommission;
    extern const BFDataFieldProperties s_FldProp_CertRequired;
    extern const BFDataFieldProperties s_FldProp_CertIssued;
    extern const BFDataFieldProperties s_FldProp_ConfirmRequired;
    extern const BFDataFieldProperties s_FldProp_OnStmt;
    extern const BFDataFieldProperties s_FldProp_RecptIssued;
    extern const BFDataFieldProperties s_FldProp_ExclMFCSSettle;
    extern const BFDataFieldProperties s_FldProp_GuaranteeDate;
    extern const BFDataFieldProperties s_FldProp_MaturityDate;
    extern const BFDataFieldProperties s_FldProp_InterestRate;
    extern const BFDataFieldProperties s_FldProp_BrokerName;
    extern const BFDataFieldProperties s_FldProp_BranchName;
    extern const BFDataFieldProperties s_FldProp_SlsrepName;
    extern const BFDataFieldProperties s_FldProp_SlsrepAltName;
    extern const BFDataFieldProperties s_FldProp_DepId;
    extern const BFDataFieldProperties s_FldProp_Remarks1;
    extern const BFDataFieldProperties s_FldProp_Remarks2;
    extern const BFDataFieldProperties s_FldProp_Remarks3;
    extern const BFDataFieldProperties s_FldProp_RejCode;
    extern const BFDataFieldProperties s_FldProp_RejCodeDesc;
    extern const BFDataFieldProperties s_FldProp_Accountable;
    extern const BFDataFieldProperties s_FldProp_AcctableDesc;
    extern const BFDataFieldProperties s_FldProp_DepositDate;
    extern const BFDataFieldProperties s_FldProp_TimeStamp;
    extern const BFDataFieldProperties s_FldProp_ProcessDate;
    extern const BFDataFieldProperties s_FldProp_Allocation;
    extern const BFDataFieldProperties s_FldProp_CansimRate;
    extern const BFDataFieldProperties s_FldProp_InitPurch;
    extern const BFDataFieldProperties s_FldProp_BackDatedReason;
    extern const BFDataFieldProperties s_FldProp_SplitComm;
    extern const BFDataFieldProperties s_FldProp_DealDate;
    extern const BFDataFieldProperties s_FldProp_DealTime;
    extern const BFDataFieldProperties s_FldProp_DSCOverrideCode;
    extern const BFDataFieldProperties s_FldProp_DSCOverrideAmt;
    extern const BFDataFieldProperties s_FldProp_AccountTo;
    extern const BFDataFieldProperties s_FldProp_FundTo;
    extern const BFDataFieldProperties s_FldProp_ClassToCode;
    extern const BFDataFieldProperties s_FldProp_TransType;
    extern const BFDataFieldProperties s_FldProp_rxFundCode;
    extern const BFDataFieldProperties s_FldProp_rxClassCode;
    extern const BFDataFieldProperties s_FldProp_Amount;
    extern const BFDataFieldProperties s_FldProp_AmountType;
    extern const BFDataFieldProperties s_FldProp_GrossNetMethod;
    extern const BFDataFieldProperties s_FldProp_UseEnteredFee;
    extern const BFDataFieldProperties s_FldProp_ExchInFee;
    extern const BFDataFieldProperties s_FldProp_ExchInFlatPercent;
    extern const BFDataFieldProperties s_FldProp_TransModPerm;
    extern const BFDataFieldProperties s_FldProp_FirstName;
    extern const BFDataFieldProperties s_FldProp_LastName;
    extern const BFDataFieldProperties s_FldProp_InitPurchDesc;
    extern const BFDataFieldProperties s_FldProp_ConfirmReqDesc;
    extern const BFDataFieldProperties s_FldProp_RecptIssuedDesc;
    extern const BFDataFieldProperties s_FldProp_Baycom;
    extern const BFDataFieldProperties s_FldProp_BayComTo;
    extern const BFDataFieldProperties s_FldProp_BankChrgs;
    extern const BFDataFieldProperties s_FldProp_ValueDate;
    extern const BFDataFieldProperties s_FldProp_PayMethod;
    extern const BFDataFieldProperties s_FldProp_ACHProcessor;
    extern const BFDataFieldProperties s_FldProp_ToBrokerCode;
    extern const BFDataFieldProperties s_FldProp_ToSlsRepCode;
    extern const BFDataFieldProperties s_FldProp_NetworkID;
    extern const BFDataFieldProperties s_FldProp_ExtTransNum;
    extern const BFDataFieldProperties s_FldProp_SendRefNum;
    extern const BFDataFieldProperties s_FldProp_PartRefNum;
    extern const BFDataFieldProperties s_FldProp_MasterRefNum;
    extern const BFDataFieldProperties s_FldProp_ExchOutFee;
    extern const BFDataFieldProperties s_FldProp_ExchOutFlatPrcnt;
    extern const BFDataFieldProperties s_FldProp_ChargeERSTTRFee;
    extern const BFDataFieldProperties s_FldProp_ChargeWDFee;
    extern const BFDataFieldProperties s_FldProp_MirTransNum;
    extern const BFDataFieldProperties s_FldProp_BorrowedFunds;
    extern const BFDataFieldProperties s_FldProp_TransSeq;
    extern const BFDataFieldProperties s_FldProp_FrSettlLocCode;
    extern const BFDataFieldProperties s_FldProp_FrDeliveryTo;
    extern const BFDataFieldProperties s_FldProp_FrSettlLocDescription;
    extern const BFDataFieldProperties s_FldProp_FrInFavourOf;
    extern const BFDataFieldProperties s_FldProp_FrForAccount;
    extern const BFDataFieldProperties s_FldProp_FrClearingMethod;
    extern const BFDataFieldProperties s_FldProp_ToSettlLocCode;
    extern const BFDataFieldProperties s_FldProp_ToDeliveryTo;
    extern const BFDataFieldProperties s_FldProp_ToSettlLocDescription;
    extern const BFDataFieldProperties s_FldProp_ToInFavourOf;
    extern const BFDataFieldProperties s_FldProp_ToForAccount;
    extern const BFDataFieldProperties s_FldProp_ToClearingMethod;
    extern const BFDataFieldProperties s_FldProp_FeeTo;
    extern const BFDataFieldProperties s_FldProp_ADLFeeCharge;
    extern const BFDataFieldProperties s_FldProp_LSIFCode;
    extern const BFDataFieldProperties s_FldProp_AltAccount;
    extern const BFDataFieldProperties s_FldProp_RefNum;
    extern const BFDataFieldProperties s_FldProp_FundWKN;
    extern const BFDataFieldProperties s_FldProp_FundISIN;
    extern const BFDataFieldProperties s_FldProp_FundToWKN;
    extern const BFDataFieldProperties s_FldProp_FundToISIN;
    extern const BFDataFieldProperties s_FldProp_AcqFeeOption;
    extern const BFDataFieldProperties s_FldProp_SettleDateOverriden;
    extern const BFDataFieldProperties s_FldProp_FrSettlInstrCode;
    extern const BFDataFieldProperties s_FldProp_ToSettlInstrCode;
    extern const BFDataFieldProperties s_FldProp_FundBrokerCode;
    extern const BFDataFieldProperties s_FldProp_AggregateOption;
    extern const BFDataFieldProperties s_FldProp_BrkSettlDate;
    extern const BFDataFieldProperties s_FldProp_OtherConfirmType;
    extern const BFDataFieldProperties s_FldProp_ExternalPrice;
    extern const BFDataFieldProperties s_FldProp_ExternalSettleDate;
    extern const BFDataFieldProperties s_FldProp_ExternalSettleAmt;
    extern const BFDataFieldProperties s_FldProp_ROAAmount;
    extern const BFDataFieldProperties s_FldProp_DeliveryMethod;
    extern const BFDataFieldProperties s_FldProp_AdjTransNum;
    extern const BFDataFieldProperties s_FldProp_TransId;
    extern const BFDataFieldProperties s_FldProp_SplitCommRebookTransID;
    extern const BFDataFieldProperties s_FldProp_Cost;
    extern const BFDataFieldProperties s_FldProp_TIS;
    extern const BFDataFieldProperties s_FldProp_OverrideCost;
    extern const BFDataFieldProperties s_FldProp_OverrideTIS;
    extern const BFDataFieldProperties s_FldProp_MCHFileIndicator;
    extern const BFDataFieldProperties s_FldProp_SecRecFileIndicator;
    extern const BFDataFieldProperties s_FldProp_ESGSettle;
    extern const BFDataFieldProperties s_FldProp_NSCCControlNumber;
    extern const BFDataFieldProperties s_FldProp_PayInstructExists;
    extern const BFDataFieldProperties s_FldProp_PayInstrOption;
    extern const BFDataFieldProperties s_FldProp_MFPayment;
    extern const BFDataFieldProperties s_FldProp_Indc;
    extern const BFDataFieldProperties s_FldProp_ModDate;
    extern const BFDataFieldProperties s_FldProp_ModUser;
    extern const BFDataFieldProperties s_FldProp_RcptStatus;
    extern const BFDataFieldProperties s_FldProp_LinkedEntityName;
    extern const BFDataFieldProperties s_FldProp_LinkedEntityId;
    extern const BFDataFieldProperties s_FldProp_StcPendTrdAuthorization;
    extern const BFDataFieldProperties s_FldProp_AssocTransId;
    extern const BFDataFieldProperties s_FldProp_GRRepayReason;
    extern const BFDataFieldProperties s_FldProp_RESPReportHRDC;
    extern const BFDataFieldProperties s_FldProp_RESPContrDetlTaxYear;
    extern const BFDataFieldProperties s_FldProp_Tainted;
    extern const BFDataFieldProperties s_FldProp_OCRdmYear;
    extern const BFDataFieldProperties s_FldProp_AssistedContrAmt;
    extern const BFDataFieldProperties s_FldProp_AcctOwnerID;
    extern const BFDataFieldProperties s_FldProp_AcctOwnerName;
    extern const BFDataFieldProperties s_FldProp_NetworkRespRequired;
    extern const BFDataFieldProperties s_FldProp_EAPCESGPaid;
    extern const BFDataFieldProperties s_FldProp_IntInvestUUID;
    extern const BFDataFieldProperties s_FldProp_InvHisNumber;
    extern const BFDataFieldProperties s_FldProp_InvHisStatus;
    extern const BFDataFieldProperties s_FldProp_IntCalcMthd;
    extern const BFDataFieldProperties s_FldProp_IntInvestType;
    extern const BFDataFieldProperties s_FldProp_InvestTerm;
    extern const BFDataFieldProperties s_FldProp_IntRate;
    extern const BFDataFieldProperties s_FldProp_GIMaturityDate;
    extern const BFDataFieldProperties s_FldProp_IntCredFreq;
    extern const BFDataFieldProperties s_FldProp_NextIntCredDate;
    extern const BFDataFieldProperties s_FldProp_AddlAmt;
    extern const BFDataFieldProperties s_FldProp_CommRedRate;
    extern const BFDataFieldProperties s_FldProp_ForcedRate;
    extern const BFDataFieldProperties s_FldProp_InvHisInvestId;
    extern const BFDataFieldProperties s_FldProp_PFCrystalisation;
    extern const BFDataFieldProperties s_FldProp_PendTrdContract;
    extern const BFDataFieldProperties s_FldProp_ValuationDt;
    extern const BFDataFieldProperties s_FldProp_PaymentInfo;
    extern const BFDataFieldProperties s_FldProp_GuaranteesOverride;
    extern const BFDataFieldProperties s_FldProp_RedemOrder;
    extern const BFDataFieldProperties s_FldProp_RightToCancel;
    extern const BFDataFieldProperties s_FldProp_RDRAdvice;
    extern const BFDataFieldProperties s_FldProp_SDRTExemptCode;
    extern const BFDataFieldProperties s_FldProp_ForcedRateAmt;
    extern const BFDataFieldProperties s_FldProp_PSDAdvice;
    extern const BFDataFieldProperties s_FldProp_PymtRoutingMthd;
    extern const BFDataFieldProperties s_FldProp_EventReceiptDate;
    extern const BFDataFieldProperties s_FldProp_EventReceiptTime;
    extern const BFDataFieldProperties s_FldProp_SourceOfTrade;
    extern const BFDataFieldProperties s_FldProp_ChannelOfTrade;
    extern const BFDataFieldProperties s_FldProp_Platform;
    extern const BFDataFieldProperties s_FldProp_SettleNetwork;
    extern const BFDataFieldProperties s_FldProp_DeliveryNetwork;
    extern const BFDataFieldProperties s_FldProp_Verified;
    extern const BFDataFieldProperties s_FldProp_VerifiedBy;
    extern const BFDataFieldProperties s_FldProp_ToCashMsgType;
    extern const BFDataFieldProperties s_FldProp_ToIntermediaryBank;
    extern const BFDataFieldProperties s_FldProp_ToReceivingBank;
    extern const BFDataFieldProperties s_FldProp_ToBeneficiary;
    extern const BFDataFieldProperties s_FldProp_ToSpecialInstructions;
    extern const BFDataFieldProperties s_FldProp_ToSettlementAccount;
    extern const BFDataFieldProperties s_FldProp_ToInternalSettlementAccount;
    extern const BFDataFieldProperties s_FldProp_FrCashMsgType;
    extern const BFDataFieldProperties s_FldProp_FrIntermediaryBank;
    extern const BFDataFieldProperties s_FldProp_FrReceivingBank;
    extern const BFDataFieldProperties s_FldProp_FrBeneficiary;
    extern const BFDataFieldProperties s_FldProp_FrSpecialInstructions;
    extern const BFDataFieldProperties s_FldProp_FrSettlementAccount;
    extern const BFDataFieldProperties s_FldProp_FrInternalSettlementAccount;
    extern const BFDataFieldProperties s_FldProp_G1Impact;
    extern const BFDataFieldProperties s_FldProp_G2Impact;
    extern const BFDataFieldProperties s_FldProp_CrossSysAcctNum;
    extern const BFDataFieldProperties s_FldProp_AggregationType;
    extern const BFDataFieldProperties s_FldProp_SourceofFundsChecked;
    extern const BFDataFieldProperties s_FldProp_ExternalInstitution;
    extern const BFDataFieldProperties s_FldProp_FundLFC;
    extern const BFDataFieldProperties s_FldProp_FundToLFC;
    extern const BFDataFieldProperties s_FldProp_RefundAmtOpt;
    extern const BFDataFieldProperties s_FldProp_Deconversion;
    extern const BFDataFieldProperties s_FldProp_OrderRouting;
    extern const BFDataFieldProperties s_FldProp_TradeInDate;
    extern const BFDataFieldProperties s_FldProp_ValuationInDt;
    extern const BFDataFieldProperties s_FldProp_FrCSDLocation;
    extern const BFDataFieldProperties s_FldProp_FrCSDAcctNum;
    extern const BFDataFieldProperties s_FldProp_ToCSDLocation;
    extern const BFDataFieldProperties s_FldProp_ToCSDAcctNum;
    extern const BFDataFieldProperties s_FldProp_PricingCode;

    extern const BFDataFieldProperties s_FldProp_DilutionLinkNum;
    extern const BFDataFieldProperties s_FldProp_FSRVLinkNum;
    extern const BFDataFieldProperties s_FldProp_PriceInCode;
    extern const BFDataFieldProperties s_FldProp_FullMoneyOutIndc;
    extern const BFDataFieldProperties s_FldProp_GateOverrideIndicator;
    extern const BFDataFieldProperties s_FldProp_RDSPPaymtDate;
}


class dsi_DSTC0054_VW : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0054_VW();
    virtual ~dsi_DSTC0054_VW();

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
    BFDataField* aFlds_[259];
    // Field Declarations
    BFTextField_60 Broker_;
    BFTextField_60 Branch_;
    BFTextField_60 SlsrepCode_;
    BFTextField_60 SettleCurrency_;
    BFTextField_60 SettleCurrName_;
    BFDecimalField ExchRate_;
    BFDecimalField Fee_;
    BFTextField_1 FlatPercent_;
    BFTextField_60 FeeCurrency_;
    BFTextField_1 BELFee_;
    BFDecimalField AdminFeeAmt_;
    BFDecimalField OverrideDSC_;
    BFTextField_60 OverrideDSCDesc_;
    BFDecimalField OverrideAmt_;
    BFTextField_1 OverrideTax_;
    BFDecimalField FedRate_;
    BFTextField_1 TransRatePUDFed_;
    BFDecimalField ProvRate_;
    BFTextField_1 TransRatePUDProv_;
    BFTextField_60 ProvSales_;
    BFTextField_60 ProvSalesName_;
    BFTextField_60 DepositType_;
    BFTextField_60 DepositTypeDesc_;
    BFTextField_60 RedCode_;
    BFTextField_60 RedCodeDesc_;
    BFTextField_60 Payment_;
    BFTextField_60 PayType2_;
    BFTextField_60 PayTypeDesc_;
    BFTextField_60 AddrCode_;
    BFTextField_60 AddrLine_;
    BFTextField_2 SuppressCode_;
    BFTextField_60 ChqSupCodeDesc_;
    BFTextField_60 OrderSource_;
    BFTextField_60 OrderSrcDesc_;
    BFTextField_2 SettleSource_;
    BFTextField_60 SettleSrcDesc_;
    BFTextField_60 SrcOfFund_;
    BFTextField_60 SrcOfFundDesc_;
    BFTextField_60 SrcOfAccount_;
    BFTextField_60 SettleType_;
    BFTextField_60 SettleTypeDesc_;
    BFTextField_1 ExpGNSettle_;
    BFTextField_60 SettledBy_;
    BFTextField_60 SettledByDesc_;
    BFTextField_60 RoundFlag_;
    BFTextField_60 RoundFlagDesc_;
    BFTextField_60 CreditFreq_;
    BFTextField_60 CreditFreqDesc_;
    BFTextField_1 ExtraCommission_;
    BFTextField_1 CertRequired_;
    BFTextField_1 CertIssued_;
    BFTextField_1 ConfirmRequired_;
    BFTextField_1 OnStmt_;
    BFTextField_1 RecptIssued_;
    BFTextField_1 ExclMFCSSettle_;
    BFDateField GuaranteeDate_;
    BFDateField MaturityDate_;
    BFDecimalField InterestRate_;
    BFTextField_60 BrokerName_;
    BFTextField_60 BranchName_;
    BFTextField_60 SlsrepName_;
    BFTextField_60 SlsrepAltName_;
    BFTextField_60 DepId_;
    BFTextField<50> Remarks1_;
    BFTextField<50> Remarks2_;
    BFTextField<50> Remarks3_;
    BFTextField_60 RejCode_;
    BFTextField_60 RejCodeDesc_;
    BFTextField_60 Accountable_;
    BFTextField_60 AcctableDesc_;
    BFDateField DepositDate_;
    BFTextField_60 TimeStamp_;
    BFDateField ProcessDate_;
    BFTextField_1 Allocation_;
    BFDecimalField CansimRate_;
    BFTextField_1 InitPurch_;
    BFTextField_2 BackDatedReason_;
    BFTextField_1 SplitComm_;
    BFDateField DealDate_;
    BFTextField_60 DealTime_;
    BFDecimalField DSCOverrideCode_;
    BFDecimalField DSCOverrideAmt_;
    BFNumericField AccountTo_;
    BFTextField_60 FundTo_;
    BFTextField_60 ClassToCode_;
    BFTextField_60 TransType_;
    BFTextField_60 rxFundCode_;
    BFTextField_60 rxClassCode_;
    BFDecimalField Amount_;
    BFTextField_60 AmountType_;
    BFTextField_2 GrossNetMethod_;
    BFTextField_1 UseEnteredFee_;
    BFDecimalField ExchInFee_;
    BFTextField_1 ExchInFlatPercent_;
    BFTextField_1 TransModPerm_;
    BFTextField_60 FirstName_;
    BFTextField<80> LastName_;
    BFTextField_60 InitPurchDesc_;
    BFTextField_60 ConfirmReqDesc_;
    BFTextField_60 RecptIssuedDesc_;
    BFTextField_60 Baycom_;
    BFTextField_60 BayComTo_;
    BFTextField_60 BankChrgs_;
    BFDateField ValueDate_;
    BFTextField_60 PayMethod_;
    BFTextField<15> ACHProcessor_;
    BFTextField_60 ToBrokerCode_;
    BFTextField_60 ToSlsRepCode_;
    BFTextField_60 NetworkID_;
    BFTextField_60 ExtTransNum_;
    BFTextField_60 SendRefNum_;
    BFTextField_60 PartRefNum_;
    BFTextField_60 MasterRefNum_;
    BFDecimalField ExchOutFee_;
    BFTextField_60 ExchOutFlatPrcnt_;
    BFTextField_1 ChargeERSTTRFee_;
    BFTextField_1 ChargeWDFee_;
    BFIntegerField MirTransNum_;
    BFTextField_1 BorrowedFunds_;
    BFNumericField TransSeq_;
    BFTextField_60 FrSettlLocCode_;
    BFTextField_60 FrDeliveryTo_;
    BFTextField_60 FrSettlLocDescription_;
    BFTextField_60 FrInFavourOf_;
    BFTextField_60 FrForAccount_;
    BFTextField_60 FrClearingMethod_;
    BFTextField_60 ToSettlLocCode_;
    BFTextField_60 ToDeliveryTo_;
    BFTextField_60 ToSettlLocDescription_;
    BFTextField_60 ToInFavourOf_;
    BFTextField_60 ToForAccount_;
    BFTextField_60 ToClearingMethod_;
    BFDecimalField FeeTo_;
    BFTextField_6 ADLFeeCharge_;
    BFTextField_60 LSIFCode_;
    BFTextField_60 AltAccount_;
    BFTextField_60 RefNum_;
    BFTextField_60 FundWKN_;
    BFTextField_60 FundISIN_;
    BFTextField_60 FundToWKN_;
    BFTextField_60 FundToISIN_;
    BFTextField_60 AcqFeeOption_;
    BFTextField_1 SettleDateOverriden_;
    BFTextField_60 FrSettlInstrCode_;
    BFTextField_60 ToSettlInstrCode_;
    BFTextField_60 FundBrokerCode_;
    BFTextField_60 AggregateOption_;
    BFDateField BrkSettlDate_;
    BFTextField_60 OtherConfirmType_;
    BFDecimalField ExternalPrice_;
    BFDateField ExternalSettleDate_;
    BFDecimalField ExternalSettleAmt_;
    BFDecimalField ROAAmount_;
    BFTextField_60 DeliveryMethod_;
    BFNumericField AdjTransNum_;
    BFNumericField TransId_;
    BFNumericField SplitCommRebookTransID_;
    BFDecimalField Cost_;
    BFDecimalField TIS_;
    BFTextField_1 OverrideCost_;
    BFTextField_1 OverrideTIS_;
    BFTextField_60 MCHFileIndicator_;
    BFTextField_60 SecRecFileIndicator_;
    BFTextField_60 ESGSettle_;
    BFTextField_60 NSCCControlNumber_;
    BFTextField_1 PayInstructExists_;
    BFTextField_60 PayInstrOption_;
    BFTextField<3> MFPayment_;
    BFTextField_60 Indc_;
    BFDateField ModDate_;
    BFTextField_60 ModUser_;
    BFTextField_60 RcptStatus_;
    BFTextField_60 LinkedEntityName_;
    BFDecimalField LinkedEntityId_;
    BFTextField_60 StcPendTrdAuthorization_;
    BFDecimalField AssocTransId_;
    BFTextField_60 GRRepayReason_;
    BFTextField_10 RESPReportHRDC_;
    BFIntegerField RESPContrDetlTaxYear_;
    BFTextField_10 Tainted_;
    BFIntegerField OCRdmYear_;
    BFDecimalField AssistedContrAmt_;
    BFDecimalField AcctOwnerID_;
    BFTextField_60 AcctOwnerName_;
    BFTextField_1 NetworkRespRequired_;
    BFDecimalField EAPCESGPaid_;
    BFTextField_60 IntInvestUUID_;
    BFTextField<20> InvHisNumber_;
    BFTextField<20> InvHisStatus_;
    BFTextField_60 IntCalcMthd_;
    BFTextField_60 IntInvestType_;
    BFIntegerField InvestTerm_;
    BFDecimalField IntRate_;
    BFDateField GIMaturityDate_;
    BFTextField_60 IntCredFreq_;
    BFDateField NextIntCredDate_;
    BFDecimalField AddlAmt_;
    BFTextField_10 CommRedRate_;
    BFTextField_10 ForcedRate_;
    BFDecimalField InvHisInvestId_;
    BFTextField<5> PFCrystalisation_;
    BFTextField<5> PendTrdContract_;
    BFDateField ValuationDt_;
    BFTextField_1 PaymentInfo_;
    BFTextField_10 GuaranteesOverride_;
    BFTextField_10 RedemOrder_;
    BFTextField_60 RightToCancel_;
    BFTextField_60 RDRAdvice_;
    BFTextField_1 SDRTExemptCode_;
    BFDecimalField ForcedRateAmt_;
    BFTextField<20> PSDAdvice_;
    BFTextField_60 PymtRoutingMthd_;
    BFDateField EventReceiptDate_;
    BFTextField<8> EventReceiptTime_;
    BFTextField_60 SourceOfTrade_;
    BFTextField_60 ChannelOfTrade_;
    BFTextField_60 Platform_;
    BFTextField<50> SettleNetwork_;
    BFTextField_60 DeliveryNetwork_;
    BFTextField_1 Verified_;
    BFTextField_60 VerifiedBy_;
    BFTextField<50> ToCashMsgType_;
    BFTextField<50> ToIntermediaryBank_;
    BFTextField<50> ToReceivingBank_;
    BFTextField<50> ToBeneficiary_;
    BFTextField<50> ToSpecialInstructions_;
    BFTextField<50> ToSettlementAccount_;
    BFTextField<50> ToInternalSettlementAccount_;
    BFTextField<50> FrCashMsgType_;
    BFTextField<50> FrIntermediaryBank_;
    BFTextField<50> FrReceivingBank_;
    BFTextField<50> FrBeneficiary_;
    BFTextField<50> FrSpecialInstructions_;
    BFTextField<50> FrSettlementAccount_;
    BFTextField<50> FrInternalSettlementAccount_;
    BFDecimalField G1Impact_;
    BFDecimalField G2Impact_;
    BFNumericField CrossSysAcctNum_;
    BFTextField_10 AggregationType_;
    BFTextField_10 SourceofFundsChecked_;
    BFTextField_60 ExternalInstitution_;
    BFTextField_60 FundLFC_;
    BFTextField_60 FundToLFC_;
    BFTextField_60 RefundAmtOpt_;
    BFTextField_1 Deconversion_;
    BFTextField_10 OrderRouting_;
    BFDateField TradeInDate_;
    BFDateField ValuationInDt_;
    BFTextField_60 FrCSDLocation_;
    BFTextField_60 FrCSDAcctNum_;
    BFTextField_60 ToCSDLocation_;
    BFTextField_60 ToCSDAcctNum_;
    BFTextField_60 PricingCode_;

    BFTextField<20> DilutionLinkNum_;
    BFTextField<20> FSRVLinkNum_;
    BFTextField_60 PriceInCode_;
    BFTextField_60 FullMoneyOutIndc_;
    BFTextField_60 GateOverrideIndicator_;
    BFDateField RDSPPaymtDate_;
};
