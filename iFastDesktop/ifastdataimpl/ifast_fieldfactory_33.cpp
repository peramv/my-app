// Data Field Factory Function
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 16:00:00 2015

#include "stdafx.h"




#include <bfdata/bfdatafield.hpp>
#include <bfdata/bfdataid.hpp>

namespace ifds
{
   extern const BFDateFieldId GIMaturityDate;
   extern const BFTextFieldId PaymentInfo;
   extern const BFTextFieldId AmtOrdType;
   extern const BFTextFieldId FeeScaleSysInvestTermHeading;
   extern const BFTextFieldId FbPortfolio;
   extern const BFTextFieldId FbBranch;
   extern const BFTextFieldId FbSettleType;
   extern const BFTextFieldId FbAcctDesig;
   extern const BFTextFieldId FbAgent;
   extern const BFTextFieldId FbDealer;
   extern const BFTextFieldId FbTemplate;
   extern const BFTextFieldId AcctServicer;
   extern const BFTextFieldId RegAcct;
   extern const BFTextFieldId RegName;
   extern const BFDecimalFieldId RegAddrID;
   extern const BFIntegerFieldId RegEntityAddrVersion;
   extern const BFDecimalFieldId RegEntityAddrXrefRId;
   extern const BFIntegerFieldId RegEntityAddrXrefVer;
   extern const BFTextFieldId RegAddrLine1;
   extern const BFTextFieldId RegAddrLine2;
   extern const BFTextFieldId RegAddrLine3;
   extern const BFTextFieldId RegAddrLine4;
   extern const BFTextFieldId FundBrokerRegAddr;
   extern const BFTextFieldId RegProvince;
   extern const BFTextFieldId RegCountry;
   extern const BFTextFieldId RegPostalCode;
   extern const BFIntegerFieldId ContractVer;
   extern const BFTextFieldId ContractMatBasedOn;
   extern const BFDateFieldId RefMatDate;
   extern const BFIntegerFieldId LWAAgeUsed;
   extern const BFDateFieldId LWAStartDate;
   extern const BFDecimalFieldId LWARateApplied;
   extern const BFTextFieldId ReqUnitAdj;
   extern const BFTextFieldId DefaultVer;
   extern const BFTextFieldId SegFundIncl;
   extern const BFTextFieldId MaturityInstructionsPayType;
   extern const BFTextFieldId IsDuringNASU;
   extern const BFTextFieldId MatInstrXEdit;
   extern const BFTextFieldId MatInstrDetailXEdit;
   extern const BFIntegerFieldId IntInvestVer;
   extern const BFIntegerFieldId DistribDetlVersion;
   extern const BFIntegerFieldId BankAcctVersion;
   extern const BFTextFieldId GIInvestmentDetailsHeading;
   extern const BFTextFieldId GISelectedInvestmentsHeading;
   extern const BFDecimalFieldId MaturityID;
   extern const BFTextFieldId ERISAProhibited;
   extern const BFTextFieldId PendTrdContrTransList;
   extern const BFTextFieldId PFCrystalisation;
   extern const BFTextFieldId PendTrdContract;
   extern const BFDateFieldId ValuationDt;
   extern const BFTextFieldId SearchIndexType;
   extern const BFDecimalFieldId HurdleRate;
   extern const BFTextFieldId InputDataType;
   extern const BFTextFieldId DaysBasis;
   extern const BFTextFieldId OrgType;
   extern const BFTextFieldId SubOrgType;
   extern const BFTextFieldId hasERISAProhibitedFund;
   extern const BFDateFieldId UserDefinedMaturityDate;
   extern const BFTextFieldId TradesSearchTransType;
   extern const BFTextFieldId Selected;
   extern const BFTextFieldId InvNum;
   extern const BFDecimalFieldId Principal;
   extern const BFDecimalFieldId ValueAtMaturity;
   extern const BFDecimalFieldId PrincRedeemed;
   extern const BFDecimalFieldId AccruedInterest;
   extern const BFDecimalFieldId MVA;
   extern const BFDecimalFieldId AmountNet;
   extern const BFTextFieldId StmtFreqDefault;
   extern const BFTextFieldId StmtFreqList;
   extern const BFTextFieldId StmtFrequency;
   extern const BFTextFieldId StmtFrequencyDisabled;
   extern const BFTextFieldId TerritoryCode;
   extern const BFDataId DSTC0430_REQ;
   extern const BFDataId DSTC0430_VW;
   extern const BFDataId DSTC0430_VWRepeat_Record;
   extern const BFDataId DSTC0431_REQ;
   extern const BFDataId DSTC0431_REQRepeat_Record;
   extern const BFDataId DSTC0431_VW;
   extern const BFDecimalFieldId InstId;
   extern const BFTextFieldId ADCD;
   extern const BFTextFieldId SegMatInstDetlUUID;
   extern const BFTextFieldId UserName2;
   extern const BFTextFieldId BankAcctCurr;
   extern const BFTextFieldId BankCntry;
   extern const BFTextFieldId BankPstl;
   extern const BFTextFieldId CorrespBankPstl;
   extern const BFTextFieldId CorrespBankCntry;
   extern const BFTextFieldId SOFforSGMR;
   extern const BFTextFieldId AccountCommitmentsHeading;
   extern const BFTextFieldId ProcType;
   extern const BFTextFieldId AccountCommitActivityHeading;
   extern const BFIntegerFieldId ClsPerTerm;
   extern const BFTextFieldId NewContrAllowed;
   extern const BFDateFieldId LWAElectDate;
   extern const BFTextFieldId BankInstrComboMaturityInterest;
   extern const BFTextFieldId ContractMaturityInstrHeading;
   extern const BFTextFieldId ContractMaturDateCrossEdit;
   extern const BFTextFieldId LoanNumber;
   extern const BFTextFieldId MatInstrAddress;
   extern const BFTextFieldId RedemOrder;
   extern const BFTextFieldId SelInvRunMode;
   extern const BFTextFieldId SelInvAmtType;
   extern const BFDecimalFieldId SelInvAmount;
   extern const BFTextFieldId SuppressMVA;
   extern const BFTextFieldId SuppressAdmin;
   extern const BFDecimalFieldId MarketValue;
   extern const BFTextFieldId IsInvSelected;
   extern const BFTextFieldId MatInstrAddrCode;
   extern const BFTextFieldId IsValueDateUpdatable;
   extern const BFTextFieldId LifeAnnuityExist;
   extern const BFDecimalFieldId ExternalAssets;
   extern const BFTextFieldId CommitmentStatus;
   extern const BFTextFieldId CommitApplicable;
   extern const BFDataId DSTC0432_REQ;
   extern const BFDataId DSTC0432_VW;
   extern const BFTextFieldId AcctCommitMstrUUID;
   extern const BFTextFieldId CommitmentUUID;
   extern const BFTextFieldId CommitmentCode;
   extern const BFTextFieldId CommitmentDesc;
   extern const BFDateFieldId CommitDeff;
   extern const BFDateFieldId CommitEndDate;
   extern const BFTextFieldId OrigBeneName;
   extern const BFTextFieldId CommitStatus;
   extern const BFTextFieldId CommitStatusDesc;
   extern const BFDecimalFieldId CommitAmt;
   extern const BFNumericFieldId OrigAccountNum;
   extern const BFDecimalFieldId CommissionPaid;
   extern const BFDecimalFieldId MaxSurrCharges;
   extern const BFDecimalFieldId CommittedPACS;
   extern const BFDecimalFieldId PaidPACS;
   extern const BFDecimalFieldId MissingPACS;
   extern const BFNumericFieldId PACID;
   extern const BFDateFieldId PACDeff;
   extern const BFDecimalFieldId PACAmt;
   extern const BFDateFieldId PACStopDate;
   extern const BFDataId DSTC0433_REQ;
   extern const BFDataId DSTC0433_VW;
   extern const BFDataId DSTC0433_VWRepeat_Record;
   extern const BFTextFieldId AcctCommitDetlUUID;
   extern const BFDateFieldId DetlDeff;
   extern const BFDecimalFieldId DetlAmt;
   extern const BFDateFieldId DetlStopDate;
   extern const BFDecimalFieldId DetlCommClawBack;
   extern const BFTextFieldId AcctCommitActivityUUID;
   extern const BFDecimalFieldId ActivityAmt;
   extern const BFDateFieldId ActivityDeff;
   extern const BFDecimalFieldId ActivityCommClawBack;
   extern const BFDataId DSTC0434_VW;
   extern const BFBigDecimalFieldId DSTC0434_REQ;
   extern const BFDataId DSTC0435_REQ;
   extern const BFDataId DSTC0435_VW;
   extern const BFDataId DSTC0435_VWRepeat_Record;
   extern const BFTextFieldId InstructionType;
   extern const BFDecimalFieldId SurrChrgApplied;
   extern const BFDecimalFieldId CommitMstrVer;
   extern const BFIntegerFieldId TransitNum;
   extern const BFIntegerFieldId CMPolicyYear;
   extern const BFIntegerFieldId CMPolicyTerm;
   extern const BFDateFieldId CMMaturityDate;
   extern const BFTextFieldId SourceOfFunds;
   extern const BFTextFieldId InsurAgeType;
   extern const BFTextFieldId PayType3;
   extern const BFTextFieldId AmountType1;
   extern const BFTextFieldId CommitCode;
   extern const BFTextFieldId ValidTaxTypes;
   extern const BFTextFieldId ValidPayFreq;
   extern const BFTextFieldId ParentFund;
   extern const BFTextFieldId ParentClass;
   extern const BFTextFieldId BankInstrComboAccountCommitment;
   extern const BFDataId DSTC0436_REQ;
   extern const BFDataFieldProperties s_FldProp_GIMaturityDate;
   extern const BFDataFieldProperties s_FldProp_PaymentInfo;
   extern const BFDataFieldProperties s_FldProp_AmtOrdType;
   extern const BFDataFieldProperties s_FldProp_FeeScaleSysInvestTermHeading;
   extern const BFDataFieldProperties s_FldProp_FbPortfolio;
   extern const BFDataFieldProperties s_FldProp_FbBranch;
   extern const BFDataFieldProperties s_FldProp_FbSettleType;
   extern const BFDataFieldProperties s_FldProp_FbAcctDesig;
   extern const BFDataFieldProperties s_FldProp_FbAgent;
   extern const BFDataFieldProperties s_FldProp_FbDealer;
   extern const BFDataFieldProperties s_FldProp_FbTemplate;
   extern const BFDataFieldProperties s_FldProp_AcctServicer;
   extern const BFDataFieldProperties s_FldProp_RegAcct;
   extern const BFDataFieldProperties s_FldProp_RegName;
   extern const BFDataFieldProperties s_FldProp_RegAddrID;
   extern const BFDataFieldProperties s_FldProp_RegEntityAddrVersion;
   extern const BFDataFieldProperties s_FldProp_RegEntityAddrXrefRId;
   extern const BFDataFieldProperties s_FldProp_RegEntityAddrXrefVer;
   extern const BFDataFieldProperties s_FldProp_RegAddrLine1;
   extern const BFDataFieldProperties s_FldProp_RegAddrLine2;
   extern const BFDataFieldProperties s_FldProp_RegAddrLine3;
   extern const BFDataFieldProperties s_FldProp_RegAddrLine4;
   extern const BFDataFieldProperties s_FldProp_FundBrokerRegAddr;
   extern const BFDataFieldProperties s_FldProp_RegProvince;
   extern const BFDataFieldProperties s_FldProp_RegCountry;
   extern const BFDataFieldProperties s_FldProp_RegPostalCode;
   extern const BFDataFieldProperties s_FldProp_ContractVer;
   extern const BFDataFieldProperties s_FldProp_ContractMatBasedOn;
   extern const BFDataFieldProperties s_FldProp_RefMatDate;
   extern const BFDataFieldProperties s_FldProp_LWAAgeUsed;
   extern const BFDataFieldProperties s_FldProp_LWAStartDate;
   extern const BFDataFieldProperties s_FldProp_LWARateApplied;
   extern const BFDataFieldProperties s_FldProp_ReqUnitAdj;
   extern const BFDataFieldProperties s_FldProp_DefaultVer;
   extern const BFDataFieldProperties s_FldProp_SegFundIncl;
   extern const BFDataFieldProperties s_FldProp_MaturityInstructionsPayType;
   extern const BFDataFieldProperties s_FldProp_IsDuringNASU;
   extern const BFDataFieldProperties s_FldProp_MatInstrXEdit;
   extern const BFDataFieldProperties s_FldProp_MatInstrDetailXEdit;
   extern const BFDataFieldProperties s_FldProp_IntInvestVer;
   extern const BFDataFieldProperties s_FldProp_DistribDetlVersion;
   extern const BFDataFieldProperties s_FldProp_BankAcctVersion;
   extern const BFDataFieldProperties s_FldProp_GIInvestmentDetailsHeading;
   extern const BFDataFieldProperties s_FldProp_GISelectedInvestmentsHeading;
   extern const BFDataFieldProperties s_FldProp_MaturityID;
   extern const BFDataFieldProperties s_FldProp_ERISAProhibited;
   extern const BFDataFieldProperties s_FldProp_PendTrdContrTransList;
   extern const BFDataFieldProperties s_FldProp_PFCrystalisation;
   extern const BFDataFieldProperties s_FldProp_PendTrdContract;
   extern const BFDataFieldProperties s_FldProp_ValuationDt;
   extern const BFDataFieldProperties s_FldProp_SearchIndexType;
   extern const BFDataFieldProperties s_FldProp_HurdleRate;
   extern const BFDataFieldProperties s_FldProp_InputDataType;
   extern const BFDataFieldProperties s_FldProp_DaysBasis;
   extern const BFDataFieldProperties s_FldProp_OrgType;
   extern const BFDataFieldProperties s_FldProp_SubOrgType;
   extern const BFDataFieldProperties s_FldProp_hasERISAProhibitedFund;
   extern const BFDataFieldProperties s_FldProp_UserDefinedMaturityDate;
   extern const BFDataFieldProperties s_FldProp_TradesSearchTransType;
   extern const BFDataFieldProperties s_FldProp_Selected;
   extern const BFDataFieldProperties s_FldProp_InvNum;
   extern const BFDataFieldProperties s_FldProp_Principal;
   extern const BFDataFieldProperties s_FldProp_ValueAtMaturity;
   extern const BFDataFieldProperties s_FldProp_PrincRedeemed;
   extern const BFDataFieldProperties s_FldProp_AccruedInterest;
   extern const BFDataFieldProperties s_FldProp_MVA;
   extern const BFDataFieldProperties s_FldProp_AmountNet;
   extern const BFDataFieldProperties s_FldProp_StmtFreqDefault;
   extern const BFDataFieldProperties s_FldProp_StmtFreqList;
   extern const BFDataFieldProperties s_FldProp_StmtFrequency;
   extern const BFDataFieldProperties s_FldProp_StmtFrequencyDisabled;
   extern const BFDataFieldProperties s_FldProp_TerritoryCode;
   extern const BFDataFieldProperties s_FldProp_DSTC0430_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0430_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0430_VWRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_DSTC0431_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0431_REQRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_DSTC0431_VW;
   extern const BFDataFieldProperties s_FldProp_InstId;
   extern const BFDataFieldProperties s_FldProp_ADCD;
   extern const BFDataFieldProperties s_FldProp_SegMatInstDetlUUID;
   extern const BFDataFieldProperties s_FldProp_UserName2;
   extern const BFDataFieldProperties s_FldProp_BankAcctCurr;
   extern const BFDataFieldProperties s_FldProp_BankCntry;
   extern const BFDataFieldProperties s_FldProp_BankPstl;
   extern const BFDataFieldProperties s_FldProp_CorrespBankPstl;
   extern const BFDataFieldProperties s_FldProp_CorrespBankCntry;
   extern const BFDataFieldProperties s_FldProp_SOFforSGMR;
   extern const BFDataFieldProperties s_FldProp_AccountCommitmentsHeading;
   extern const BFDataFieldProperties s_FldProp_ProcType;
   extern const BFDataFieldProperties s_FldProp_AccountCommitActivityHeading;
   extern const BFDataFieldProperties s_FldProp_ClsPerTerm;
   extern const BFDataFieldProperties s_FldProp_NewContrAllowed;
   extern const BFDataFieldProperties s_FldProp_LWAElectDate;
   extern const BFDataFieldProperties s_FldProp_BankInstrComboMaturityInterest;
   extern const BFDataFieldProperties s_FldProp_ContractMaturityInstrHeading;
   extern const BFDataFieldProperties s_FldProp_ContractMaturDateCrossEdit;
   extern const BFDataFieldProperties s_FldProp_LoanNumber;
   extern const BFDataFieldProperties s_FldProp_MatInstrAddress;
   extern const BFDataFieldProperties s_FldProp_RedemOrder;
   extern const BFDataFieldProperties s_FldProp_SelInvRunMode;
   extern const BFDataFieldProperties s_FldProp_SelInvAmtType;
   extern const BFDataFieldProperties s_FldProp_SelInvAmount;
   extern const BFDataFieldProperties s_FldProp_SuppressMVA;
   extern const BFDataFieldProperties s_FldProp_SuppressAdmin;
   extern const BFDataFieldProperties s_FldProp_MarketValue;
   extern const BFDataFieldProperties s_FldProp_IsInvSelected;
   extern const BFDataFieldProperties s_FldProp_MatInstrAddrCode;
   extern const BFDataFieldProperties s_FldProp_IsValueDateUpdatable;
   extern const BFDataFieldProperties s_FldProp_LifeAnnuityExist;
   extern const BFDataFieldProperties s_FldProp_ExternalAssets;
   extern const BFDataFieldProperties s_FldProp_CommitmentStatus;
   extern const BFDataFieldProperties s_FldProp_CommitApplicable;
   extern const BFDataFieldProperties s_FldProp_DSTC0432_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0432_VW;
   extern const BFDataFieldProperties s_FldProp_AcctCommitMstrUUID;
   extern const BFDataFieldProperties s_FldProp_CommitmentUUID;
   extern const BFDataFieldProperties s_FldProp_CommitmentCode;
   extern const BFDataFieldProperties s_FldProp_CommitmentDesc;
   extern const BFDataFieldProperties s_FldProp_CommitDeff;
   extern const BFDataFieldProperties s_FldProp_CommitEndDate;
   extern const BFDataFieldProperties s_FldProp_OrigBeneName;
   extern const BFDataFieldProperties s_FldProp_CommitStatus;
   extern const BFDataFieldProperties s_FldProp_CommitStatusDesc;
   extern const BFDataFieldProperties s_FldProp_CommitAmt;
   extern const BFDataFieldProperties s_FldProp_OrigAccountNum;
   extern const BFDataFieldProperties s_FldProp_CommissionPaid;
   extern const BFDataFieldProperties s_FldProp_MaxSurrCharges;
   extern const BFDataFieldProperties s_FldProp_CommittedPACS;
   extern const BFDataFieldProperties s_FldProp_PaidPACS;
   extern const BFDataFieldProperties s_FldProp_MissingPACS;
   extern const BFDataFieldProperties s_FldProp_PACID;
   extern const BFDataFieldProperties s_FldProp_PACDeff;
   extern const BFDataFieldProperties s_FldProp_PACAmt;
   extern const BFDataFieldProperties s_FldProp_PACStopDate;
   extern const BFDataFieldProperties s_FldProp_DSTC0433_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0433_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0433_VWRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_AcctCommitDetlUUID;
   extern const BFDataFieldProperties s_FldProp_DetlDeff;
   extern const BFDataFieldProperties s_FldProp_DetlAmt;
   extern const BFDataFieldProperties s_FldProp_DetlStopDate;
   extern const BFDataFieldProperties s_FldProp_DetlCommClawBack;
   extern const BFDataFieldProperties s_FldProp_AcctCommitActivityUUID;
   extern const BFDataFieldProperties s_FldProp_ActivityAmt;
   extern const BFDataFieldProperties s_FldProp_ActivityDeff;
   extern const BFDataFieldProperties s_FldProp_ActivityCommClawBack;
   extern const BFDataFieldProperties s_FldProp_DSTC0434_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0434_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0435_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0435_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0435_VWRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_InstructionType;
   extern const BFDataFieldProperties s_FldProp_SurrChrgApplied;
   extern const BFDataFieldProperties s_FldProp_CommitMstrVer;
   extern const BFDataFieldProperties s_FldProp_TransitNum;
   extern const BFDataFieldProperties s_FldProp_CMPolicyYear;
   extern const BFDataFieldProperties s_FldProp_CMPolicyTerm;
   extern const BFDataFieldProperties s_FldProp_CMMaturityDate;
   extern const BFDataFieldProperties s_FldProp_SourceOfFunds;
   extern const BFDataFieldProperties s_FldProp_InsurAgeType;
   extern const BFDataFieldProperties s_FldProp_PayType3;
   extern const BFDataFieldProperties s_FldProp_AmountType1;
   extern const BFDataFieldProperties s_FldProp_CommitCode;
   extern const BFDataFieldProperties s_FldProp_ValidTaxTypes;
   extern const BFDataFieldProperties s_FldProp_ValidPayFreq;
   extern const BFDataFieldProperties s_FldProp_ParentFund;
   extern const BFDataFieldProperties s_FldProp_ParentClass;
   extern const BFDataFieldProperties s_FldProp_BankInstrComboAccountCommitment;
   extern const BFDataFieldProperties s_FldProp_DSTC0436_REQ;
   BFDataField* createField_33( const BFFieldId id )
   {
      BFDataField* pField = NULL;
      switch( id.getId() )
      {
         case 40006600: pField = new BFDateField( GIMaturityDate, &s_FldProp_GIMaturityDate ); break; 
         case 40006601: pField = new BFTextField_1( PaymentInfo, &s_FldProp_PaymentInfo ); break; 
         case 40006602: pField = new BFTextField_10( AmtOrdType, &s_FldProp_AmtOrdType ); break; 
         case 40006603: pField = new BFTextField_60( FeeScaleSysInvestTermHeading, &s_FldProp_FeeScaleSysInvestTermHeading ); break; 
         case 40006604: pField = new BFTextField<50>( FbPortfolio, &s_FldProp_FbPortfolio ); break; 
         case 40006605: pField = new BFTextField<35>( FbBranch, &s_FldProp_FbBranch ); break; 
         case 40006606: pField = new BFTextField_1( FbSettleType, &s_FldProp_FbSettleType ); break; 
         case 40006607: pField = new BFTextField<50>( FbAcctDesig, &s_FldProp_FbAcctDesig ); break; 
         case 40006608: pField = new BFTextField<50>( FbAgent, &s_FldProp_FbAgent ); break; 
         case 40006609: pField = new BFTextField<50>( FbDealer, &s_FldProp_FbDealer ); break; 
         case 40006610: pField = new BFTextField_2( FbTemplate, &s_FldProp_FbTemplate ); break; 
         case 40006611: pField = new BFTextField<35>( AcctServicer, &s_FldProp_AcctServicer ); break; 
         case 40006612: pField = new BFTextField<50>( RegAcct, &s_FldProp_RegAcct ); break; 
         case 40006613: pField = new BFTextField<50>( RegName, &s_FldProp_RegName ); break; 
         case 40006615: pField = new BFDecimalField( RegAddrID, &s_FldProp_RegAddrID ); break; 
         case 40006616: pField = new BFIntegerField( RegEntityAddrVersion, &s_FldProp_RegEntityAddrVersion ); break; 
         case 40006617: pField = new BFDecimalField( RegEntityAddrXrefRId, &s_FldProp_RegEntityAddrXrefRId ); break; 
         case 40006618: pField = new BFIntegerField( RegEntityAddrXrefVer, &s_FldProp_RegEntityAddrXrefVer ); break; 
         case 40006619: pField = new BFTextField<50>( RegAddrLine1, &s_FldProp_RegAddrLine1 ); break; 
         case 40006620: pField = new BFTextField<50>( RegAddrLine2, &s_FldProp_RegAddrLine2 ); break; 
         case 40006621: pField = new BFTextField<50>( RegAddrLine3, &s_FldProp_RegAddrLine3 ); break; 
         case 40006622: pField = new BFTextField<50>( RegAddrLine4, &s_FldProp_RegAddrLine4 ); break; 
         case 40006623: pField = new BFTextField<200>( FundBrokerRegAddr, &s_FldProp_FundBrokerRegAddr ); break; 
         case 40006624: pField = new BFTextField<50>( RegProvince, &s_FldProp_RegProvince ); break; 
         case 40006625: pField = new BFTextField<50>( RegCountry, &s_FldProp_RegCountry ); break; 
         case 40006626: pField = new BFTextField_10( RegPostalCode, &s_FldProp_RegPostalCode ); break; 
         case 40006627: pField = new BFIntegerField( ContractVer, &s_FldProp_ContractVer ); break; 
         case 40006628: pField = new BFTextField<25>( ContractMatBasedOn, &s_FldProp_ContractMatBasedOn ); break; 
         case 40006629: pField = new BFDateField( RefMatDate, &s_FldProp_RefMatDate ); break; 
         case 40006630: pField = new BFIntegerField( LWAAgeUsed, &s_FldProp_LWAAgeUsed ); break; 
         case 40006631: pField = new BFDateField( LWAStartDate, &s_FldProp_LWAStartDate ); break; 
         case 40006632: pField = new BFDecimalField( LWARateApplied, &s_FldProp_LWARateApplied ); break; 
         case 40006633: pField = new BFTextField_1( ReqUnitAdj, &s_FldProp_ReqUnitAdj ); break; 
         case 40006634: pField = new BFTextField_1( DefaultVer, &s_FldProp_DefaultVer ); break; 
         case 40006635: pField = new BFTextField_1( SegFundIncl, &s_FldProp_SegFundIncl ); break; 
         case 40006639: pField = new BFTextField_60( MaturityInstructionsPayType, &s_FldProp_MaturityInstructionsPayType ); break; 
         case 40006640: pField = new BFTextField_10( IsDuringNASU, &s_FldProp_IsDuringNASU ); break; 
         case 40006641: pField = new BFTextField<20>( MatInstrXEdit, &s_FldProp_MatInstrXEdit ); break; 
         case 40006642: pField = new BFTextField<20>( MatInstrDetailXEdit, &s_FldProp_MatInstrDetailXEdit ); break; 
         case 40006645: pField = new BFIntegerField( IntInvestVer, &s_FldProp_IntInvestVer ); break; 
         case 40006647: pField = new BFIntegerField( DistribDetlVersion, &s_FldProp_DistribDetlVersion ); break; 
         case 40006648: pField = new BFIntegerField( BankAcctVersion, &s_FldProp_BankAcctVersion ); break; 
         case 40006649: pField = new BFTextField_60( GIInvestmentDetailsHeading, &s_FldProp_GIInvestmentDetailsHeading ); break; 
         case 40006650: pField = new BFTextField_60( GISelectedInvestmentsHeading, &s_FldProp_GISelectedInvestmentsHeading ); break; 
         case 40006651: pField = new BFDecimalField( MaturityID, &s_FldProp_MaturityID ); break; 
         case 40006652: pField = new BFTextField_10( ERISAProhibited, &s_FldProp_ERISAProhibited ); break; 
         case 40006653: pField = new BFTextField_60( PendTrdContrTransList, &s_FldProp_PendTrdContrTransList ); break; 
         case 40006654: pField = new BFTextField<5>( PFCrystalisation, &s_FldProp_PFCrystalisation ); break; 
         case 40006655: pField = new BFTextField<5>( PendTrdContract, &s_FldProp_PendTrdContract ); break; 
         case 40006656: pField = new BFDateField( ValuationDt, &s_FldProp_ValuationDt ); break; 
         case 40006657: pField = new BFTextField_60( SearchIndexType, &s_FldProp_SearchIndexType ); break; 
         case 40006658: pField = new BFDecimalField( HurdleRate, &s_FldProp_HurdleRate ); break; 
         case 40006659: pField = new BFTextField<5>( InputDataType, &s_FldProp_InputDataType ); break; 
         case 40006660: pField = new BFTextField<5>( DaysBasis, &s_FldProp_DaysBasis ); break; 
         case 40006661: pField = new BFTextField<5>( OrgType, &s_FldProp_OrgType ); break; 
         case 40006662: pField = new BFTextField<5>( SubOrgType, &s_FldProp_SubOrgType ); break; 
         case 40006663: pField = new BFTextField_2( hasERISAProhibitedFund, &s_FldProp_hasERISAProhibitedFund ); break; 
         case 40006664: pField = new BFDateField( UserDefinedMaturityDate, &s_FldProp_UserDefinedMaturityDate ); break; 
         case 40006665: pField = new BFTextField_60( TradesSearchTransType, &s_FldProp_TradesSearchTransType ); break; 
         case 40006667: pField = new BFTextField_1( Selected, &s_FldProp_Selected ); break; 
         case 40006668: pField = new BFTextField_60( InvNum, &s_FldProp_InvNum ); break; 
         case 40006670: pField = new BFDecimalField( Principal, &s_FldProp_Principal ); break; 
         case 40006672: pField = new BFDecimalField( ValueAtMaturity, &s_FldProp_ValueAtMaturity ); break; 
         case 40006673: pField = new BFDecimalField( PrincRedeemed, &s_FldProp_PrincRedeemed ); break; 
         case 40006674: pField = new BFDecimalField( AccruedInterest, &s_FldProp_AccruedInterest ); break; 
         case 40006675: pField = new BFDecimalField( MVA, &s_FldProp_MVA ); break; 
         case 40006676: pField = new BFDecimalField( AmountNet, &s_FldProp_AmountNet ); break; 
         case 40006677: pField = new BFTextField_60( StmtFreqDefault, &s_FldProp_StmtFreqDefault ); break; 
         case 40006678: pField = new BFTextField_60( StmtFreqList, &s_FldProp_StmtFreqList ); break; 
         case 40006679: pField = new BFTextField_60( StmtFrequency, &s_FldProp_StmtFrequency ); break; 
         case 40006680: pField = new BFTextField_10( StmtFrequencyDisabled, &s_FldProp_StmtFrequencyDisabled ); break; 
         case 40006681: pField = new BFTextField<30>( TerritoryCode, &s_FldProp_TerritoryCode ); break; 
         case 40006688: pField = new BFDecimalField( InstId, &s_FldProp_InstId ); break; 
         case 40006689: pField = new BFTextField_10( ADCD, &s_FldProp_ADCD ); break; 
         case 40006690: pField = new BFTextField_60( SegMatInstDetlUUID, &s_FldProp_SegMatInstDetlUUID ); break; 
         case 40006691: pField = new BFTextField_60( UserName2, &s_FldProp_UserName2 ); break; 
         case 40006692: pField = new BFTextField_60( BankAcctCurr, &s_FldProp_BankAcctCurr ); break; 
         case 40006693: pField = new BFTextField_60( BankCntry, &s_FldProp_BankCntry ); break; 
         case 40006694: pField = new BFTextField_60( BankPstl, &s_FldProp_BankPstl ); break; 
         case 40006696: pField = new BFTextField_10( CorrespBankPstl, &s_FldProp_CorrespBankPstl ); break; 
         case 40006699: pField = new BFTextField_60( CorrespBankCntry, &s_FldProp_CorrespBankCntry ); break; 
         case 40006700: pField = new BFTextField_60( SOFforSGMR, &s_FldProp_SOFforSGMR ); break; 
         case 40006701: pField = new BFTextField_60( AccountCommitmentsHeading, &s_FldProp_AccountCommitmentsHeading ); break; 
         case 40006702: pField = new BFTextField_60( ProcType, &s_FldProp_ProcType ); break; 
         case 40006703: pField = new BFTextField_60( AccountCommitActivityHeading, &s_FldProp_AccountCommitActivityHeading ); break; 
         case 40006704: pField = new BFIntegerField( ClsPerTerm, &s_FldProp_ClsPerTerm ); break; 
         case 40006705: pField = new BFTextField_10( NewContrAllowed, &s_FldProp_NewContrAllowed ); break; 
         case 40006706: pField = new BFDateField( LWAElectDate, &s_FldProp_LWAElectDate ); break; 
         case 40006707: pField = new BFTextField_60( BankInstrComboMaturityInterest, &s_FldProp_BankInstrComboMaturityInterest ); break; 
         case 40006708: pField = new BFTextField<100>( ContractMaturityInstrHeading, &s_FldProp_ContractMaturityInstrHeading ); break; 
         case 40006709: pField = new BFTextField_60( ContractMaturDateCrossEdit, &s_FldProp_ContractMaturDateCrossEdit ); break; 
         case 40006710: pField = new BFTextField<20>( LoanNumber, &s_FldProp_LoanNumber ); break; 
         case 40006711: pField = new BFTextField_60( MatInstrAddress, &s_FldProp_MatInstrAddress ); break; 
         case 40006712: pField = new BFTextField_10( RedemOrder, &s_FldProp_RedemOrder ); break; 
         case 40006713: pField = new BFTextField_1( SelInvRunMode, &s_FldProp_SelInvRunMode ); break; 
         case 40006714: pField = new BFTextField_60( SelInvAmtType, &s_FldProp_SelInvAmtType ); break; 
         case 40006718: pField = new BFDecimalField( SelInvAmount, &s_FldProp_SelInvAmount ); break; 
         case 40006719: pField = new BFTextField_2( SuppressMVA, &s_FldProp_SuppressMVA ); break; 
         case 40006720: pField = new BFTextField_2( SuppressAdmin, &s_FldProp_SuppressAdmin ); break; 
         case 40006721: pField = new BFDecimalField( MarketValue, &s_FldProp_MarketValue ); break; 
         case 40006724: pField = new BFTextField_2( IsInvSelected, &s_FldProp_IsInvSelected ); break; 
         case 40006725: pField = new BFTextField_2( MatInstrAddrCode, &s_FldProp_MatInstrAddrCode ); break; 
         case 40006727: pField = new BFTextField_1( IsValueDateUpdatable, &s_FldProp_IsValueDateUpdatable ); break; 
         case 40006728: pField = new BFTextField<3>( LifeAnnuityExist, &s_FldProp_LifeAnnuityExist ); break; 
         case 40006729: pField = new BFDecimalField( ExternalAssets, &s_FldProp_ExternalAssets ); break; 
         case 40006730: pField = new BFTextField<25>( CommitmentStatus, &s_FldProp_CommitmentStatus ); break; 
         case 40006731: pField = new BFTextField<25>( CommitApplicable, &s_FldProp_CommitApplicable ); break; 
         case 40006734: pField = new BFTextField_60( AcctCommitMstrUUID, &s_FldProp_AcctCommitMstrUUID ); break; 
         case 40006735: pField = new BFTextField_60( CommitmentUUID, &s_FldProp_CommitmentUUID ); break; 
         case 40006736: pField = new BFTextField_60( CommitmentCode, &s_FldProp_CommitmentCode ); break; 
         case 40006737: pField = new BFTextField_60( CommitmentDesc, &s_FldProp_CommitmentDesc ); break; 
         case 40006738: pField = new BFDateField( CommitDeff, &s_FldProp_CommitDeff ); break; 
         case 40006739: pField = new BFDateField( CommitEndDate, &s_FldProp_CommitEndDate ); break; 
         case 40006740: pField = new BFTextField_60( OrigBeneName, &s_FldProp_OrigBeneName ); break; 
         case 40006741: pField = new BFTextField_60( CommitStatus, &s_FldProp_CommitStatus ); break; 
         case 40006742: pField = new BFTextField_60( CommitStatusDesc, &s_FldProp_CommitStatusDesc ); break; 
         case 40006744: pField = new BFDecimalField( CommitAmt, &s_FldProp_CommitAmt ); break; 
         case 40006747: pField = new BFNumericField( OrigAccountNum, &s_FldProp_OrigAccountNum ); break; 
         case 40006749: pField = new BFDecimalField( CommissionPaid, &s_FldProp_CommissionPaid ); break; 
         case 40006750: pField = new BFDecimalField( MaxSurrCharges, &s_FldProp_MaxSurrCharges ); break; 
         case 40006751: pField = new BFDecimalField( CommittedPACS, &s_FldProp_CommittedPACS ); break; 
         case 40006752: pField = new BFDecimalField( PaidPACS, &s_FldProp_PaidPACS ); break; 
         case 40006753: pField = new BFDecimalField( MissingPACS, &s_FldProp_MissingPACS ); break; 
         case 40006754: pField = new BFNumericField( PACID, &s_FldProp_PACID ); break; 
         case 40006755: pField = new BFDateField( PACDeff, &s_FldProp_PACDeff ); break; 
         case 40006756: pField = new BFDecimalField( PACAmt, &s_FldProp_PACAmt ); break; 
         case 40006757: pField = new BFDateField( PACStopDate, &s_FldProp_PACStopDate ); break; 
         case 40006761: pField = new BFTextField_60( AcctCommitDetlUUID, &s_FldProp_AcctCommitDetlUUID ); break; 
         case 40006762: pField = new BFDateField( DetlDeff, &s_FldProp_DetlDeff ); break; 
         case 40006763: pField = new BFDecimalField( DetlAmt, &s_FldProp_DetlAmt ); break; 
         case 40006764: pField = new BFDateField( DetlStopDate, &s_FldProp_DetlStopDate ); break; 
         case 40006765: pField = new BFDecimalField( DetlCommClawBack, &s_FldProp_DetlCommClawBack ); break; 
         case 40006766: pField = new BFTextField_60( AcctCommitActivityUUID, &s_FldProp_AcctCommitActivityUUID ); break; 
         case 40006767: pField = new BFDecimalField( ActivityAmt, &s_FldProp_ActivityAmt ); break; 
         case 40006768: pField = new BFDateField( ActivityDeff, &s_FldProp_ActivityDeff ); break; 
         case 40006769: pField = new BFDecimalField( ActivityCommClawBack, &s_FldProp_ActivityCommClawBack ); break; 
         case 40006771: pField = new BFBigDecimalField( DSTC0434_REQ, &s_FldProp_DSTC0434_REQ ); break; 
         case 40006776: pField = new BFTextField_60( InstructionType, &s_FldProp_InstructionType ); break; 
         case 40006778: pField = new BFDecimalField( SurrChrgApplied, &s_FldProp_SurrChrgApplied ); break; 
         case 40006779: pField = new BFDecimalField( CommitMstrVer, &s_FldProp_CommitMstrVer ); break; 
         case 40006780: pField = new BFIntegerField( TransitNum, &s_FldProp_TransitNum ); break; 
         case 40006781: pField = new BFIntegerField( CMPolicyYear, &s_FldProp_CMPolicyYear ); break; 
         case 40006782: pField = new BFIntegerField( CMPolicyTerm, &s_FldProp_CMPolicyTerm ); break; 
         case 40006784: pField = new BFDateField( CMMaturityDate, &s_FldProp_CMMaturityDate ); break; 
         case 40006786: pField = new BFTextField<50>( SourceOfFunds, &s_FldProp_SourceOfFunds ); break; 
         case 40006787: pField = new BFTextField_60( InsurAgeType, &s_FldProp_InsurAgeType ); break; 
         case 40006788: pField = new BFTextField_60( PayType3, &s_FldProp_PayType3 ); break; 
         case 40006793: pField = new BFTextField<25>( AmountType1, &s_FldProp_AmountType1 ); break; 
         case 40006794: pField = new BFTextField<30>( CommitCode, &s_FldProp_CommitCode ); break; 
         case 40006795: pField = new BFTextField_60( ValidTaxTypes, &s_FldProp_ValidTaxTypes ); break; 
         case 40006796: pField = new BFTextField_60( ValidPayFreq, &s_FldProp_ValidPayFreq ); break; 
         case 40006797: pField = new BFTextField_60( ParentFund, &s_FldProp_ParentFund ); break; 
         case 40006798: pField = new BFTextField_60( ParentClass, &s_FldProp_ParentClass ); break; 
         case 40006799: pField = new BFTextField<30>( BankInstrComboAccountCommitment, &s_FldProp_BankInstrComboAccountCommitment ); break; 
      }
      return pField;
   }
}
