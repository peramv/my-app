// BFDataImpl header file for DataSet DSTC0244.REQRepeat_Record
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
   extern const BFTextFieldId RunMode;
   extern const BFNumericFieldId AccountNum;
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId ClassCode;
   extern const BFDateFieldId ResetDate;
   extern const BFTextFieldId ResetType;
   extern const BFIntegerFieldId CanResetId;
   extern const BFDateFieldId BatchEffective;
   extern const BFTextFieldId BatchName;
   extern const BFDecimalFieldId Trace;
   extern const BFNumericFieldId VersionNum;
   extern const BFIntegerFieldId ProtContractRId;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_RunMode;
   extern const BFDataFieldProperties s_FldProp_AccountNum;
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_ClassCode;
   extern const BFDataFieldProperties s_FldProp_ResetDate;
   extern const BFDataFieldProperties s_FldProp_ResetType;
   extern const BFDataFieldProperties s_FldProp_CanResetId;
   extern const BFDataFieldProperties s_FldProp_BatchEffective;
   extern const BFDataFieldProperties s_FldProp_BatchName;
   extern const BFDataFieldProperties s_FldProp_Trace;
   extern const BFDataFieldProperties s_FldProp_VersionNum;
   extern const BFDataFieldProperties s_FldProp_ProtContractRId;
}


class dsi_DSTC0244_REQRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0244_REQRepeat_Record();
   virtual ~dsi_DSTC0244_REQRepeat_Record();

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
   BFDataField* aFlds_[12];
   // Field Declarations
   BFTextField_60 RunMode_;
   BFNumericField AccountNum_;
   BFTextField<200> FundCode_;
   BFTextField<120> ClassCode_;
   BFDateField ResetDate_;
   BFTextField_60 ResetType_;
   BFIntegerField CanResetId_;
   BFDateField BatchEffective_;
   BFTextField_60 BatchName_;
   BFDecimalField Trace_;
   BFNumericField VersionNum_;
   BFIntegerField ProtContractRId_;

};
