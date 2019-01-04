// BFDataImpl header file for DataSet DSTC0262.VWRepeat_Record
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
   extern const BFTextFieldId RuleType;
   extern const BFDecimalFieldId OverrideDecimal;
   extern const BFTextFieldId OverrideLogical;
   extern const BFTextFieldId OverrideFundLevel;
   extern const BFTextFieldId AMSTaxJurisCode;
   extern const BFTextFieldId AMSResProvCode;
   extern const BFTextFieldId AMSTaxType;
   extern const BFTextFieldId AMSAcctType;
   extern const BFTextFieldId AMSAcctDesignation;
   extern const BFTextFieldId OnLineEWI;
   extern const BFTextFieldId CycleEWI;
   extern const BFTextFieldId ESGEWI;
   extern const BFNumericFieldId AMSRuleId;
   extern const BFTextFieldId ModUser;
   extern const BFDateFieldId ModDate;
   extern const BFDateFieldId ProcessDate;
   extern const BFTextFieldId Username;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_RuleType;
   extern const BFDataFieldProperties s_FldProp_OverrideDecimal;
   extern const BFDataFieldProperties s_FldProp_OverrideLogical;
   extern const BFDataFieldProperties s_FldProp_OverrideFundLevel;
   extern const BFDataFieldProperties s_FldProp_AMSTaxJurisCode;
   extern const BFDataFieldProperties s_FldProp_AMSResProvCode;
   extern const BFDataFieldProperties s_FldProp_AMSTaxType;
   extern const BFDataFieldProperties s_FldProp_AMSAcctType;
   extern const BFDataFieldProperties s_FldProp_AMSAcctDesignation;
   extern const BFDataFieldProperties s_FldProp_OnLineEWI;
   extern const BFDataFieldProperties s_FldProp_CycleEWI;
   extern const BFDataFieldProperties s_FldProp_ESGEWI;
   extern const BFDataFieldProperties s_FldProp_AMSRuleId;
   extern const BFDataFieldProperties s_FldProp_ModUser;
   extern const BFDataFieldProperties s_FldProp_ModDate;
   extern const BFDataFieldProperties s_FldProp_ProcessDate;
   extern const BFDataFieldProperties s_FldProp_Username;
}


class dsi_DSTC0262_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0262_VWRepeat_Record();
   virtual ~dsi_DSTC0262_VWRepeat_Record();

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
   BFDataField* aFlds_[17];
   // Field Declarations
   BFTextField_60 RuleType_;
   BFDecimalField OverrideDecimal_;
   BFTextField_1 OverrideLogical_;
   BFTextField_1 OverrideFundLevel_;
   BFTextField_60 AMSTaxJurisCode_;
   BFTextField_60 AMSResProvCode_;
   BFTextField_60 AMSTaxType_;
   BFTextField_60 AMSAcctType_;
   BFTextField_60 AMSAcctDesignation_;
   BFTextField_1 OnLineEWI_;
   BFTextField_1 CycleEWI_;
   BFTextField_1 ESGEWI_;
   BFNumericField AMSRuleId_;
   BFTextField_60 ModUser_;
   BFDateField ModDate_;
   BFDateField ProcessDate_;
   BFTextField_60 Username_;

};
