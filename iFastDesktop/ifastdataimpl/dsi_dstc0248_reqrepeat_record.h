// BFDataImpl header file for DataSet DSTC0248.REQRepeat_Record
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
   extern const BFDecimalFieldId Version;
   extern const BFNumericFieldId RecId;
   extern const BFTextFieldId IndexCode;
   extern const BFDateFieldId EffectiveDate;
   extern const BFDecimalFieldId ClosingValue;
   extern const BFDecimalFieldId HurdleRate;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_RunMode;
   extern const BFDataFieldProperties s_FldProp_Version;
   extern const BFDataFieldProperties s_FldProp_RecId;
   extern const BFDataFieldProperties s_FldProp_IndexCode;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_ClosingValue;
   extern const BFDataFieldProperties s_FldProp_HurdleRate;
}


class dsi_DSTC0248_REQRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0248_REQRepeat_Record();
   virtual ~dsi_DSTC0248_REQRepeat_Record();

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
   BFDataField* aFlds_[7];
   // Field Declarations
   BFTextField_60 RunMode_;
   BFDecimalField Version_;
   BFNumericField RecId_;
   BFTextField_60 IndexCode_;
   BFDateField EffectiveDate_;
   BFDecimalField ClosingValue_;
   BFDecimalField HurdleRate_;

};
