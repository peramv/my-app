// BFDataImpl header file for DataSet DSTC0230.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


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
   extern const BFNumericFieldId FeeID;
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId ClassCode;
   extern const BFTextFieldId FundFromCode;
   extern const BFTextFieldId ClassFromCode;
   extern const BFTextFieldId FeeCode;
   extern const BFTextFieldId ParamFeeType;
   extern const BFDecimalFieldId Rate;
   extern const BFDecimalFieldId MinFee;
   extern const BFDecimalFieldId MaxFee;
   extern const BFDateFieldId EffectiveDate;
   extern const BFDateFieldId StopDate;
   extern const BFTextFieldId FreqMinMaxApp;
   extern const BFTextFieldId OnPW;
   extern const BFTextFieldId OnFW;
   extern const BFTextFieldId Active;
   extern const BFDateFieldId ProcessDate;
   extern const BFDateFieldId ModDate;
   extern const BFTextFieldId Username;
   extern const BFTextFieldId ModUser;
   extern const BFTextFieldId CommGroup;
   extern const BFTextFieldId BrokerCode;
   extern const BFTextFieldId AllowOverrideType;
   extern const BFTextFieldId BasedOn;
   extern const BFTextFieldId Currency;
   extern const BFTextFieldId HowPaid;
   extern const BFTextFieldId ShGroup;
   extern const BFNumericFieldId FeeParamRid;
   extern const BFTextFieldId BranchCode;
   extern const BFTextFieldId SlsrepCode;
   extern const BFTextFieldId FamilyCode;
   extern const BFTextFieldId BranchName;
   extern const BFTextFieldId SlsrepName;
   extern const BFTextFieldId FamilyName;
   extern const BFTextFieldId BrokerName;
   extern const BFTextFieldId ShGroupName;
   extern const BFTextFieldId FeeModelCode;
   extern const BFTextFieldId ChargeOption;
   extern const BFTextFieldId AppliedMethod;
   extern const BFTextFieldId FundList;
   extern const BFDecimalFieldId ThresholdAmt;
   extern const BFTextFieldId ThresholdCurrency;
   extern const BFTextFieldId DistributionChannel;
   extern const BFTextFieldId FundLink;
   extern const BFTextFieldId TaxInclusive;
   extern const BFDateFieldId FMLastProcDate;
   extern const BFNumericFieldId ThrshldRecID;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_FeeID;
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_ClassCode;
   extern const BFDataFieldProperties s_FldProp_FundFromCode;
   extern const BFDataFieldProperties s_FldProp_ClassFromCode;
   extern const BFDataFieldProperties s_FldProp_FeeCode;
   extern const BFDataFieldProperties s_FldProp_ParamFeeType;
   extern const BFDataFieldProperties s_FldProp_Rate;
   extern const BFDataFieldProperties s_FldProp_MinFee;
   extern const BFDataFieldProperties s_FldProp_MaxFee;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_StopDate;
   extern const BFDataFieldProperties s_FldProp_FreqMinMaxApp;
   extern const BFDataFieldProperties s_FldProp_OnPW;
   extern const BFDataFieldProperties s_FldProp_OnFW;
   extern const BFDataFieldProperties s_FldProp_Active;
   extern const BFDataFieldProperties s_FldProp_ProcessDate;
   extern const BFDataFieldProperties s_FldProp_ModDate;
   extern const BFDataFieldProperties s_FldProp_Username;
   extern const BFDataFieldProperties s_FldProp_ModUser;
   extern const BFDataFieldProperties s_FldProp_CommGroup;
   extern const BFDataFieldProperties s_FldProp_BrokerCode;
   extern const BFDataFieldProperties s_FldProp_AllowOverrideType;
   extern const BFDataFieldProperties s_FldProp_BasedOn;
   extern const BFDataFieldProperties s_FldProp_Currency;
   extern const BFDataFieldProperties s_FldProp_HowPaid;
   extern const BFDataFieldProperties s_FldProp_ShGroup;
   extern const BFDataFieldProperties s_FldProp_FeeParamRid;
   extern const BFDataFieldProperties s_FldProp_BranchCode;
   extern const BFDataFieldProperties s_FldProp_SlsrepCode;
   extern const BFDataFieldProperties s_FldProp_FamilyCode;
   extern const BFDataFieldProperties s_FldProp_BranchName;
   extern const BFDataFieldProperties s_FldProp_SlsrepName;
   extern const BFDataFieldProperties s_FldProp_FamilyName;
   extern const BFDataFieldProperties s_FldProp_BrokerName;
   extern const BFDataFieldProperties s_FldProp_ShGroupName;
   extern const BFDataFieldProperties s_FldProp_FeeModelCode;
   extern const BFDataFieldProperties s_FldProp_ChargeOption;
   extern const BFDataFieldProperties s_FldProp_AppliedMethod;
   extern const BFDataFieldProperties s_FldProp_FundList;
   extern const BFDataFieldProperties s_FldProp_ThresholdAmt;
   extern const BFDataFieldProperties s_FldProp_ThresholdCurrency;
   extern const BFDataFieldProperties s_FldProp_DistributionChannel;
   extern const BFDataFieldProperties s_FldProp_FundLink;
   extern const BFDataFieldProperties s_FldProp_TaxInclusive;
   extern const BFDataFieldProperties s_FldProp_FMLastProcDate;
   extern const BFDataFieldProperties s_FldProp_ThrshldRecID;
}


class dsi_DSTC0230_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0230_VWRepeat_Record();
   virtual ~dsi_DSTC0230_VWRepeat_Record();

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
   BFDataField* aFlds_[47];
   // Field Declarations
   BFNumericField FeeID_;
   BFTextField<200> FundCode_;
   BFTextField<120> ClassCode_;
   BFTextField_60 FundFromCode_;
   BFTextField_60 ClassFromCode_;
   BFTextField_60 FeeCode_;
   BFTextField_60 ParamFeeType_;
   BFDecimalField Rate_;
   BFDecimalField MinFee_;
   BFDecimalField MaxFee_;
   BFDateField EffectiveDate_;
   BFDateField StopDate_;
   BFTextField_60 FreqMinMaxApp_;
   BFTextField_1 OnPW_;
   BFTextField_1 OnFW_;
   BFTextField_60 Active_;
   BFDateField ProcessDate_;
   BFDateField ModDate_;
   BFTextField_60 Username_;
   BFTextField_60 ModUser_;
   BFTextField<25> CommGroup_;
   BFTextField_60 BrokerCode_;
   BFTextField_60 AllowOverrideType_;
   BFTextField_60 BasedOn_;
   BFTextField<200> Currency_;
   BFTextField_60 HowPaid_;
   BFTextField_60 ShGroup_;
   BFNumericField FeeParamRid_;
   BFTextField_60 BranchCode_;
   BFTextField_60 SlsrepCode_;
   BFTextField_60 FamilyCode_;
   BFTextField_60 BranchName_;
   BFTextField_60 SlsrepName_;
   BFTextField<40> FamilyName_;
   BFTextField_60 BrokerName_;
   BFTextField_60 ShGroupName_;
   BFTextField_60 FeeModelCode_;
   BFTextField_60 ChargeOption_;
   BFTextField_1 AppliedMethod_;
   BFTextField<1000> FundList_;
   BFDecimalField ThresholdAmt_;
   BFTextField_60 ThresholdCurrency_;
   BFTextField_60 DistributionChannel_;
   BFTextField<30> FundLink_;
   BFTextField_10 TaxInclusive_;
   BFDateField FMLastProcDate_;
   BFNumericField ThrshldRecID_;

};
