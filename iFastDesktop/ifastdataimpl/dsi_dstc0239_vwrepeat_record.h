// BFDataImpl header file for DataSet DSTC0239.VWRepeat_Record
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
   extern const BFIntegerFieldId ContractID;
   extern const BFDateFieldId EffectiveDate;
   extern const BFDateFieldId MaturityDate;
   extern const BFDecimalFieldId GuarAmt;
   extern const BFDecimalFieldId GuarUnits;
   extern const BFNumericFieldId TransId;
   extern const BFDecimalFieldId TransAmt;
   extern const BFDecimalFieldId TransUnits;
   extern const BFIntegerFieldId ResetID;
   extern const BFDecimalFieldId InstrAmt;
   extern const BFDateFieldId ContractGapDate;
   extern const BFDateFieldId ModDate;
   extern const BFTextFieldId ModUser;
   extern const BFTextFieldId Username;
   extern const BFDateFieldId ProcessDate;
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId ClassCode;
   extern const BFIntegerFieldId ProtContractRId;
   extern const BFDecimalFieldId MktValue;
   extern const BFDecimalFieldId GainOrLossAmt;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_ContractID;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_MaturityDate;
   extern const BFDataFieldProperties s_FldProp_GuarAmt;
   extern const BFDataFieldProperties s_FldProp_GuarUnits;
   extern const BFDataFieldProperties s_FldProp_TransId;
   extern const BFDataFieldProperties s_FldProp_TransAmt;
   extern const BFDataFieldProperties s_FldProp_TransUnits;
   extern const BFDataFieldProperties s_FldProp_ResetID;
   extern const BFDataFieldProperties s_FldProp_InstrAmt;
   extern const BFDataFieldProperties s_FldProp_ContractGapDate;
   extern const BFDataFieldProperties s_FldProp_ModDate;
   extern const BFDataFieldProperties s_FldProp_ModUser;
   extern const BFDataFieldProperties s_FldProp_Username;
   extern const BFDataFieldProperties s_FldProp_ProcessDate;
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_ClassCode;
   extern const BFDataFieldProperties s_FldProp_ProtContractRId;
   extern const BFDataFieldProperties s_FldProp_MktValue;
   extern const BFDataFieldProperties s_FldProp_GainOrLossAmt;
}


class dsi_DSTC0239_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0239_VWRepeat_Record();
   virtual ~dsi_DSTC0239_VWRepeat_Record();

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
   BFDataField* aFlds_[20];
   // Field Declarations
   BFIntegerField ContractID_;
   BFDateField EffectiveDate_;
   BFDateField MaturityDate_;
   BFDecimalField GuarAmt_;
   BFDecimalField GuarUnits_;
   BFNumericField TransId_;
   BFDecimalField TransAmt_;
   BFDecimalField TransUnits_;
   BFIntegerField ResetID_;
   BFDecimalField InstrAmt_;
   BFDateField ContractGapDate_;
   BFDateField ModDate_;
   BFTextField_60 ModUser_;
   BFTextField_60 Username_;
   BFDateField ProcessDate_;
   BFTextField<200> FundCode_;
   BFTextField<120> ClassCode_;
   BFIntegerField ProtContractRId_;
   BFDecimalField MktValue_;
   BFDecimalField GainOrLossAmt_;

};
