// BFDataImpl header file for DataSet DSTC0179.VWRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Monday, March 05, 2018 23:18:37


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
    extern const BFTextFieldId AMSCode;
    extern const BFDecimalFieldId Percentage;
    extern const BFTextFieldId Currency;
    extern const BFDateFieldId EffectiveDate;
    extern const BFDecimalFieldId AMSCodeVer;
    extern const BFTextFieldId AMSCodeInUse;
    extern const BFTextFieldId Name;
    extern const BFTextFieldId AMSType;
    extern const BFTextFieldId DefaultAlloc;
    extern const BFTextFieldId FundAlloc;
    extern const BFTextFieldId EnglishShortName;
    extern const BFTextFieldId EnglishLongName;
    extern const BFTextFieldId EnglishName;
    extern const BFTextFieldId FrenchShortName;
    extern const BFTextFieldId FrenchLongName;
    extern const BFTextFieldId FrenchName;
    extern const BFTextFieldId ForeignRelFund;
    extern const BFTextFieldId ForeignRelClass;
    extern const BFTextFieldId RoundingFund;
    extern const BFTextFieldId RoundingClass;
    extern const BFDateFieldId GrandFatheredDate;
    extern const BFDateFieldId NextRebDate;
    extern const BFDateFieldId LastRebDate;
    extern const BFDecimalFieldId ThresholdAmt;
    extern const BFTextFieldId WireEleg;
    extern const BFTextFieldId ModUser;
    extern const BFDateFieldId ProcessDate;
    extern const BFDateFieldId ModDate;
    extern const BFTextFieldId Username;
    extern const BFNumericFieldId DayOfWeek;
    extern const BFNumericFieldId AMSRecId;
    extern const BFTextFieldId VerifyPrecreate;
    extern const BFDateFieldId LastEffectiveDate;
    extern const BFTextFieldId GrandFatherStamped;
    extern const BFTextFieldId AssocFund;
    extern const BFTextFieldId AssocClass;
    extern const BFIntegerFieldId SchedSetupFreqID;
    extern const BFDecimalFieldId Amount;
    extern const BFTextFieldId ParentFndClsTrdg;
    extern const BFTextFieldId RebalReq;
    extern const BFTextFieldId TargetMixOption;
    extern const BFTextFieldId AMSDeltaRequestUUID;
    extern const BFDateFieldId LastAMSModDate;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_AMSCode;
    extern const BFDataFieldProperties s_FldProp_Percentage;
    extern const BFDataFieldProperties s_FldProp_Currency;
    extern const BFDataFieldProperties s_FldProp_EffectiveDate;
    extern const BFDataFieldProperties s_FldProp_AMSCodeVer;
    extern const BFDataFieldProperties s_FldProp_AMSCodeInUse;
    extern const BFDataFieldProperties s_FldProp_Name;
    extern const BFDataFieldProperties s_FldProp_AMSType;
    extern const BFDataFieldProperties s_FldProp_DefaultAlloc;
    extern const BFDataFieldProperties s_FldProp_FundAlloc;
    extern const BFDataFieldProperties s_FldProp_EnglishShortName;
    extern const BFDataFieldProperties s_FldProp_EnglishLongName;
    extern const BFDataFieldProperties s_FldProp_EnglishName;
    extern const BFDataFieldProperties s_FldProp_FrenchShortName;
    extern const BFDataFieldProperties s_FldProp_FrenchLongName;
    extern const BFDataFieldProperties s_FldProp_FrenchName;
    extern const BFDataFieldProperties s_FldProp_ForeignRelFund;
    extern const BFDataFieldProperties s_FldProp_ForeignRelClass;
    extern const BFDataFieldProperties s_FldProp_RoundingFund;
    extern const BFDataFieldProperties s_FldProp_RoundingClass;
    extern const BFDataFieldProperties s_FldProp_GrandFatheredDate;
    extern const BFDataFieldProperties s_FldProp_NextRebDate;
    extern const BFDataFieldProperties s_FldProp_LastRebDate;
    extern const BFDataFieldProperties s_FldProp_ThresholdAmt;
    extern const BFDataFieldProperties s_FldProp_WireEleg;
    extern const BFDataFieldProperties s_FldProp_ModUser;
    extern const BFDataFieldProperties s_FldProp_ProcessDate;
    extern const BFDataFieldProperties s_FldProp_ModDate;
    extern const BFDataFieldProperties s_FldProp_Username;
    extern const BFDataFieldProperties s_FldProp_DayOfWeek;
    extern const BFDataFieldProperties s_FldProp_AMSRecId;
    extern const BFDataFieldProperties s_FldProp_VerifyPrecreate;
    extern const BFDataFieldProperties s_FldProp_LastEffectiveDate;
    extern const BFDataFieldProperties s_FldProp_GrandFatherStamped;
    extern const BFDataFieldProperties s_FldProp_AssocFund;
    extern const BFDataFieldProperties s_FldProp_AssocClass;
    extern const BFDataFieldProperties s_FldProp_SchedSetupFreqID;
    extern const BFDataFieldProperties s_FldProp_Amount;
    extern const BFDataFieldProperties s_FldProp_ParentFndClsTrdg;
    extern const BFDataFieldProperties s_FldProp_RebalReq;
    extern const BFDataFieldProperties s_FldProp_TargetMixOption;
    extern const BFDataFieldProperties s_FldProp_AMSDeltaRequestUUID;
    extern const BFDataFieldProperties s_FldProp_LastAMSModDate;
}


class dsi_DSTC0179_VWRepeat_Record : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0179_VWRepeat_Record();
    virtual ~dsi_DSTC0179_VWRepeat_Record();

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
    BFDataField* aFlds_[43];
    // Field Declarations
    BFTextField_60 AMSCode_;
    BFDecimalField Percentage_;
    BFTextField<200> Currency_;
    BFDateField EffectiveDate_;
    BFDecimalField AMSCodeVer_;
    BFTextField_1 AMSCodeInUse_;
    BFTextField_60 Name_;
    BFTextField<3> AMSType_;
    BFTextField_1 DefaultAlloc_;
    BFTextField_1 FundAlloc_;
    BFTextField_60 EnglishShortName_;
    BFTextField_60 EnglishLongName_;
    BFTextField_60 EnglishName_;
    BFTextField_60 FrenchShortName_;
    BFTextField_60 FrenchLongName_;
    BFTextField_60 FrenchName_;
    BFTextField_60 ForeignRelFund_;
    BFTextField_60 ForeignRelClass_;
    BFTextField_60 RoundingFund_;
    BFTextField_60 RoundingClass_;
    BFDateField GrandFatheredDate_;
    BFDateField NextRebDate_;
    BFDateField LastRebDate_;
    BFDecimalField ThresholdAmt_;
    BFTextField_1 WireEleg_;
    BFTextField_60 ModUser_;
    BFDateField ProcessDate_;
    BFDateField ModDate_;
    BFTextField_60 Username_;
    BFNumericField DayOfWeek_;
    BFNumericField AMSRecId_;
    BFTextField_1 VerifyPrecreate_;
    BFDateField LastEffectiveDate_;
    BFTextField_1 GrandFatherStamped_;
    BFTextField<4> AssocFund_;
    BFTextField_2 AssocClass_;
    BFIntegerField SchedSetupFreqID_;
    BFDecimalField Amount_;
    BFTextField_2 ParentFndClsTrdg_;
    BFTextField_1 RebalReq_;
    BFTextField_1 TargetMixOption_;
    BFTextField_60 AMSDeltaRequestUUID_;
    BFDateField LastAMSModDate_;
};
