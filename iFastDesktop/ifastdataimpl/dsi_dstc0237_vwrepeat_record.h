// BFDataImpl header file for DataSet DSTC0237.VWRepeat_Record
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
   extern const BFDecimalFieldId ProtectedFundRId;
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId ClassCode;
   extern const BFDateFieldId EffectiveDate;
   extern const BFDateFieldId StopDate;
   extern const BFTextFieldId InsurCode;
   extern const BFDecimalFieldId InsurCost;
   extern const BFTextFieldId ContractGapType;
   extern const BFNumericFieldId ResetsAllowed;
   extern const BFNumericFieldId MaturityYears;
   extern const BFDateFieldId ModDate;
   extern const BFTextFieldId ModUser;
   extern const BFTextFieldId Username;
   extern const BFDateFieldId ProcessDate;
   extern const BFNumericFieldId VersionNum;
   extern const BFTextFieldId FundNumber;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_ProtectedFundRId;
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_ClassCode;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_StopDate;
   extern const BFDataFieldProperties s_FldProp_InsurCode;
   extern const BFDataFieldProperties s_FldProp_InsurCost;
   extern const BFDataFieldProperties s_FldProp_ContractGapType;
   extern const BFDataFieldProperties s_FldProp_ResetsAllowed;
   extern const BFDataFieldProperties s_FldProp_MaturityYears;
   extern const BFDataFieldProperties s_FldProp_ModDate;
   extern const BFDataFieldProperties s_FldProp_ModUser;
   extern const BFDataFieldProperties s_FldProp_Username;
   extern const BFDataFieldProperties s_FldProp_ProcessDate;
   extern const BFDataFieldProperties s_FldProp_VersionNum;
   extern const BFDataFieldProperties s_FldProp_FundNumber;
}


class dsi_DSTC0237_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0237_VWRepeat_Record();
   virtual ~dsi_DSTC0237_VWRepeat_Record();

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
   BFDataField* aFlds_[16];
   // Field Declarations
   BFDecimalField ProtectedFundRId_;
   BFTextField<200> FundCode_;
   BFTextField<120> ClassCode_;
   BFDateField EffectiveDate_;
   BFDateField StopDate_;
   BFTextField_6 InsurCode_;
   BFDecimalField InsurCost_;
   BFTextField_2 ContractGapType_;
   BFNumericField ResetsAllowed_;
   BFNumericField MaturityYears_;
   BFDateField ModDate_;
   BFTextField_60 ModUser_;
   BFTextField_60 Username_;
   BFDateField ProcessDate_;
   BFNumericField VersionNum_;
   BFTextField<5> FundNumber_;

};
