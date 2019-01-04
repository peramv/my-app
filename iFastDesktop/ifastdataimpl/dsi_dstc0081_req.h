// BFDataImpl header file for DataSet DSTC0081.REQ
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, November 13, 2015 00:04:49


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
    extern const BFTextFieldId SessionId;
    extern const BFTextFieldId User_Id;
    extern const BFTextFieldId LanguageCode;
    extern const BFTextFieldId CompanyId;
    extern const BFTextFieldId RunMode;
    extern const BFNumericFieldId AccountNum;
    extern const BFTextFieldId MaritalCode;
    extern const BFTextFieldId Employer;
    extern const BFDecimalFieldId EmployedYrs;
    extern const BFTextFieldId IndustryCode;
    extern const BFTextFieldId OccupationCode;
    extern const BFTextFieldId AnnualIncomeCode;
    extern const BFTextFieldId NetWorthCode;
    extern const BFTextFieldId InvObjCode;
    extern const BFTextFieldId InvKnowledgeCode;
    extern const BFTextFieldId InvHorizonCode;
    extern const BFTextFieldId RiskToleranceCode;
    extern const BFTextFieldId OtherInvestments;
    extern const BFTextFieldId AdvisorCode;
    extern const BFTextFieldId WitnessName;
    extern const BFTextFieldId WitnessAddr1;
    extern const BFTextFieldId WitnessAddr2;
    extern const BFDateFieldId EffectiveDate;
    extern const BFTextFieldId PersonalSecCode;
    extern const BFDecimalFieldId PrimMstrVer;
    extern const BFDateFieldId ProcessDate;
    extern const BFTextFieldId Track;
    extern const BFTextFieldId Activity;
    extern const BFTextFieldId InvestPhilosophyCode;
    extern const BFTextFieldId OccupationFreeFormat;
    extern const BFDecimalFieldId GrowthPercent;
    extern const BFDecimalFieldId IncomePercent;
    extern const BFDecimalFieldId SafetyPercent;
    extern const BFTextFieldId RepByBranch;
    extern const BFNumericFieldId RepNo;
    extern const BFTextFieldId SAMFinHealthCode;
    extern const BFTextFieldId TypeOfBusFreeFormat;
    extern const BFDateFieldId AcctProcessDate;
    extern const BFTextFieldId AcctRepBranch;
    extern const BFNumericFieldId AcctRepNo;
    extern const BFNumericFieldId AcctKYCVer;
    extern const BFTextFieldId MemorablePlace;
    extern const BFTextFieldId MemorableWord;
    extern const BFDateFieldId MemorableDate;
    extern const BFTextFieldId BrokerCode;
    extern const BFTextFieldId BranchCode;
    extern const BFTextFieldId AgentCode;
    extern const BFTextFieldId KYCComment;
    extern const BFTextFieldId EmploymentType;
    extern const BFTextFieldId ResidenceType;
    extern const BFDecimalFieldId ResAmount;
    extern const BFDateFieldId KYCMailedDate;
    extern const BFDecimalFieldId AnnualIncomeAmount;
    extern const BFDateFieldId IncomeLevelDate;
    extern const BFDecimalFieldId NetWorthAmount;
    extern const BFDateFieldId NetWorthDate;
    extern const BFTextFieldId RefferalCode;
    extern const BFTextFieldId ReferenceName;
    extern const BFTextFieldId SpecialtyCode;
    extern const BFDecimalFieldId TolerancePrcnt;
    extern const BFDecimalFieldId ShortTermPrcnt;
    extern const BFDecimalFieldId AggressivePrcnt;
    extern const BFDateFieldId PrcntDate;
    extern const BFIntegerFieldId ShrKYCVer;
    extern const BFTextFieldId TypeOfInvestor;
    extern const BFTextFieldId InvestingOnBehalf;
    extern const BFTextFieldId CountryCode;
    extern const BFTextFieldId InitialPayment;
    extern const BFTextFieldId SourceOfIncome;
    extern const BFTextFieldId PowerOfAttorney;
    extern const BFTextFieldId ComplianceCode;
    extern const BFTextFieldId RegulatoryStandard;
    extern const BFNumericFieldId EntityId;
    extern const BFTextFieldId NumOfDependents;
    extern const BFTextFieldId AssociateCorpName1;
    extern const BFTextFieldId AssociateCorpName2;
    extern const BFTextFieldId AssociateCorpName3;
    extern const BFTextFieldId AssociateCorpName4;
    extern const BFTextFieldId AssociateCorpName5;
    extern const BFTextFieldId AssociateCorpName6;
    extern const BFTextFieldId AssociateCorpName7;
    extern const BFTextFieldId AssociateCorpName8;
    extern const BFTextFieldId AssociateCorpName9;
    extern const BFTextFieldId AssociateCorpName10;
    extern const BFTextFieldId RoleInCorp1;
    extern const BFTextFieldId RoleInCorp2;
    extern const BFTextFieldId RoleInCorp3;
    extern const BFTextFieldId RoleInCorp4;
    extern const BFTextFieldId RoleInCorp5;
    extern const BFTextFieldId RoleInCorp6;
    extern const BFTextFieldId RoleInCorp7;
    extern const BFTextFieldId RoleInCorp8;
    extern const BFTextFieldId RoleInCorp9;
    extern const BFTextFieldId RoleInCorp10;
    extern const BFTextFieldId SuppressKYCLetter;
    extern const BFTextFieldId KYCInfoFormat;
    extern const BFTextFieldId ProfileNum;
    extern const BFTextFieldId RefNum;
    extern const BFTextFieldId ProfileValue;
    extern const BFDateFieldId LastReviewDate;
    extern const BFTextFieldId SolicitPublicContrib;
    extern const BFTextFieldId InvReason;
    extern const BFTextFieldId KYCBusinessType;
    extern const BFTextFieldId KYCLegalForm;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_SessionId;
    extern const BFDataFieldProperties s_FldProp_User_Id;
    extern const BFDataFieldProperties s_FldProp_LanguageCode;
    extern const BFDataFieldProperties s_FldProp_CompanyId;
    extern const BFDataFieldProperties s_FldProp_RunMode;
    extern const BFDataFieldProperties s_FldProp_AccountNum;
    extern const BFDataFieldProperties s_FldProp_MaritalCode;
    extern const BFDataFieldProperties s_FldProp_Employer;
    extern const BFDataFieldProperties s_FldProp_EmployedYrs;
    extern const BFDataFieldProperties s_FldProp_IndustryCode;
    extern const BFDataFieldProperties s_FldProp_OccupationCode;
    extern const BFDataFieldProperties s_FldProp_AnnualIncomeCode;
    extern const BFDataFieldProperties s_FldProp_NetWorthCode;
    extern const BFDataFieldProperties s_FldProp_InvObjCode;
    extern const BFDataFieldProperties s_FldProp_InvKnowledgeCode;
    extern const BFDataFieldProperties s_FldProp_InvHorizonCode;
    extern const BFDataFieldProperties s_FldProp_RiskToleranceCode;
    extern const BFDataFieldProperties s_FldProp_OtherInvestments;
    extern const BFDataFieldProperties s_FldProp_AdvisorCode;
    extern const BFDataFieldProperties s_FldProp_WitnessName;
    extern const BFDataFieldProperties s_FldProp_WitnessAddr1;
    extern const BFDataFieldProperties s_FldProp_WitnessAddr2;
    extern const BFDataFieldProperties s_FldProp_EffectiveDate;
    extern const BFDataFieldProperties s_FldProp_PersonalSecCode;
    extern const BFDataFieldProperties s_FldProp_PrimMstrVer;
    extern const BFDataFieldProperties s_FldProp_ProcessDate;
    extern const BFDataFieldProperties s_FldProp_Track;
    extern const BFDataFieldProperties s_FldProp_Activity;
    extern const BFDataFieldProperties s_FldProp_InvestPhilosophyCode;
    extern const BFDataFieldProperties s_FldProp_OccupationFreeFormat;
    extern const BFDataFieldProperties s_FldProp_GrowthPercent;
    extern const BFDataFieldProperties s_FldProp_IncomePercent;
    extern const BFDataFieldProperties s_FldProp_SafetyPercent;
    extern const BFDataFieldProperties s_FldProp_RepByBranch;
    extern const BFDataFieldProperties s_FldProp_RepNo;
    extern const BFDataFieldProperties s_FldProp_SAMFinHealthCode;
    extern const BFDataFieldProperties s_FldProp_TypeOfBusFreeFormat;
    extern const BFDataFieldProperties s_FldProp_AcctProcessDate;
    extern const BFDataFieldProperties s_FldProp_AcctRepBranch;
    extern const BFDataFieldProperties s_FldProp_AcctRepNo;
    extern const BFDataFieldProperties s_FldProp_AcctKYCVer;
    extern const BFDataFieldProperties s_FldProp_MemorablePlace;
    extern const BFDataFieldProperties s_FldProp_MemorableWord;
    extern const BFDataFieldProperties s_FldProp_MemorableDate;
    extern const BFDataFieldProperties s_FldProp_BrokerCode;
    extern const BFDataFieldProperties s_FldProp_BranchCode;
    extern const BFDataFieldProperties s_FldProp_AgentCode;
    extern const BFDataFieldProperties s_FldProp_KYCComment;
    extern const BFDataFieldProperties s_FldProp_EmploymentType;
    extern const BFDataFieldProperties s_FldProp_ResidenceType;
    extern const BFDataFieldProperties s_FldProp_ResAmount;
    extern const BFDataFieldProperties s_FldProp_KYCMailedDate;
    extern const BFDataFieldProperties s_FldProp_AnnualIncomeAmount;
    extern const BFDataFieldProperties s_FldProp_IncomeLevelDate;
    extern const BFDataFieldProperties s_FldProp_NetWorthAmount;
    extern const BFDataFieldProperties s_FldProp_NetWorthDate;
    extern const BFDataFieldProperties s_FldProp_RefferalCode;
    extern const BFDataFieldProperties s_FldProp_ReferenceName;
    extern const BFDataFieldProperties s_FldProp_SpecialtyCode;
    extern const BFDataFieldProperties s_FldProp_TolerancePrcnt;
    extern const BFDataFieldProperties s_FldProp_ShortTermPrcnt;
    extern const BFDataFieldProperties s_FldProp_AggressivePrcnt;
    extern const BFDataFieldProperties s_FldProp_PrcntDate;
    extern const BFDataFieldProperties s_FldProp_ShrKYCVer;
    extern const BFDataFieldProperties s_FldProp_TypeOfInvestor;
    extern const BFDataFieldProperties s_FldProp_InvestingOnBehalf;
    extern const BFDataFieldProperties s_FldProp_CountryCode;
    extern const BFDataFieldProperties s_FldProp_InitialPayment;
    extern const BFDataFieldProperties s_FldProp_SourceOfIncome;
    extern const BFDataFieldProperties s_FldProp_PowerOfAttorney;
    extern const BFDataFieldProperties s_FldProp_ComplianceCode;
    extern const BFDataFieldProperties s_FldProp_RegulatoryStandard;
    extern const BFDataFieldProperties s_FldProp_EntityId;
    extern const BFDataFieldProperties s_FldProp_NumOfDependents;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName1;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName2;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName3;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName4;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName5;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName6;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName7;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName8;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName9;
    extern const BFDataFieldProperties s_FldProp_AssociateCorpName10;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp1;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp2;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp3;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp4;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp5;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp6;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp7;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp8;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp9;
    extern const BFDataFieldProperties s_FldProp_RoleInCorp10;
    extern const BFDataFieldProperties s_FldProp_SuppressKYCLetter;
    extern const BFDataFieldProperties s_FldProp_KYCInfoFormat;
    extern const BFDataFieldProperties s_FldProp_ProfileNum;
    extern const BFDataFieldProperties s_FldProp_RefNum;
    extern const BFDataFieldProperties s_FldProp_ProfileValue;
    extern const BFDataFieldProperties s_FldProp_LastReviewDate;
    extern const BFDataFieldProperties s_FldProp_SolicitPublicContrib;
    extern const BFDataFieldProperties s_FldProp_InvReason;
    extern const BFDataFieldProperties s_FldProp_KYCBusinessType;
    extern const BFDataFieldProperties s_FldProp_KYCLegalForm;
}


class dsi_DSTC0081_REQ : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0081_REQ();
    virtual ~dsi_DSTC0081_REQ();

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
    BFDataField* aFlds_[104];
    // Field Declarations
    BFTextField_60 SessionId_;
    BFTextField_60 User_Id_;
    BFTextField_60 LanguageCode_;
    BFTextField_60 CompanyId_;
    BFTextField_60 RunMode_;
    BFNumericField AccountNum_;
    BFTextField_60 MaritalCode_;
    BFTextField_60 Employer_;
    BFDecimalField EmployedYrs_;
    BFTextField_60 IndustryCode_;
    BFTextField_60 OccupationCode_;
    BFTextField_60 AnnualIncomeCode_;
    BFTextField_60 NetWorthCode_;
    BFTextField_60 InvObjCode_;
    BFTextField_60 InvKnowledgeCode_;
    BFTextField_60 InvHorizonCode_;
    BFTextField_60 RiskToleranceCode_;
    BFTextField_1 OtherInvestments_;
    BFTextField_60 AdvisorCode_;
    BFTextField_60 WitnessName_;
    BFTextField_60 WitnessAddr1_;
    BFTextField_60 WitnessAddr2_;
    BFDateField EffectiveDate_;
    BFTextField_60 PersonalSecCode_;
    BFDecimalField PrimMstrVer_;
    BFDateField ProcessDate_;
    BFTextField_1 Track_;
    BFTextField_60 Activity_;
    BFTextField_60 InvestPhilosophyCode_;
    BFTextField<40> OccupationFreeFormat_;
    BFDecimalField GrowthPercent_;
    BFDecimalField IncomePercent_;
    BFDecimalField SafetyPercent_;
    BFTextField_1 RepByBranch_;
    BFNumericField RepNo_;
    BFTextField_60 SAMFinHealthCode_;
    BFTextField_60 TypeOfBusFreeFormat_;
    BFDateField AcctProcessDate_;
    BFTextField_60 AcctRepBranch_;
    BFNumericField AcctRepNo_;
    BFNumericField AcctKYCVer_;
    BFTextField_60 MemorablePlace_;
    BFTextField_60 MemorableWord_;
    BFDateField MemorableDate_;
    BFTextField_60 BrokerCode_;
    BFTextField_60 BranchCode_;
    BFTextField_60 AgentCode_;
    BFTextField<200> KYCComment_;
    BFTextField_60 EmploymentType_;
    BFTextField_60 ResidenceType_;
    BFDecimalField ResAmount_;
    BFDateField KYCMailedDate_;
    BFDecimalField AnnualIncomeAmount_;
    BFDateField IncomeLevelDate_;
    BFDecimalField NetWorthAmount_;
    BFDateField NetWorthDate_;
    BFTextField_60 RefferalCode_;
    BFTextField_60 ReferenceName_;
    BFTextField_60 SpecialtyCode_;
    BFDecimalField TolerancePrcnt_;
    BFDecimalField ShortTermPrcnt_;
    BFDecimalField AggressivePrcnt_;
    BFDateField PrcntDate_;
    BFIntegerField ShrKYCVer_;
    BFTextField_60 TypeOfInvestor_;
    BFTextField<3> InvestingOnBehalf_;
    BFTextField_60 CountryCode_;
    BFTextField_60 InitialPayment_;
    BFTextField<3> SourceOfIncome_;
    BFTextField<3> PowerOfAttorney_;
    BFTextField_60 ComplianceCode_;
    BFTextField_60 RegulatoryStandard_;
    BFNumericField EntityId_;
    BFTextField_60 NumOfDependents_;
    BFTextField_60 AssociateCorpName1_;
    BFTextField_60 AssociateCorpName2_;
    BFTextField_60 AssociateCorpName3_;
    BFTextField_60 AssociateCorpName4_;
    BFTextField_60 AssociateCorpName5_;
    BFTextField_60 AssociateCorpName6_;
    BFTextField_60 AssociateCorpName7_;
    BFTextField_60 AssociateCorpName8_;
    BFTextField_60 AssociateCorpName9_;
    BFTextField_60 AssociateCorpName10_;
    BFTextField_60 RoleInCorp1_;
    BFTextField_60 RoleInCorp2_;
    BFTextField_60 RoleInCorp3_;
    BFTextField_60 RoleInCorp4_;
    BFTextField_60 RoleInCorp5_;
    BFTextField_60 RoleInCorp6_;
    BFTextField_60 RoleInCorp7_;
    BFTextField_60 RoleInCorp8_;
    BFTextField_60 RoleInCorp9_;
    BFTextField_60 RoleInCorp10_;
    BFTextField<3> SuppressKYCLetter_;
    BFTextField_60 KYCInfoFormat_;
    BFTextField_60 ProfileNum_;
    BFTextField_60 RefNum_;
    BFTextField_60 ProfileValue_;
    BFDateField LastReviewDate_;
    BFTextField_10 SolicitPublicContrib_;
    BFTextField_10 InvReason_;
    BFTextField_60 KYCBusinessType_;
    BFTextField_60 KYCLegalForm_;
};
