// BFDataImpl header file for DataSet DSTC0259.REQRepeat_Record
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
   extern const BFTextFieldId BrokerCode;
   extern const BFTextFieldId PaymentFor;
   extern const BFTextFieldId PayToEntity;
   extern const BFDateFieldId EffectiveDate;
   extern const BFDateFieldId StopDate;
   extern const BFDecimalFieldId PayEntityId;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_RunMode;
   extern const BFDataFieldProperties s_FldProp_BrokerCode;
   extern const BFDataFieldProperties s_FldProp_PaymentFor;
   extern const BFDataFieldProperties s_FldProp_PayToEntity;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_StopDate;
   extern const BFDataFieldProperties s_FldProp_PayEntityId;
}


class dsi_DSTC0259_REQRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0259_REQRepeat_Record();
   virtual ~dsi_DSTC0259_REQRepeat_Record();

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
   BFTextField_60 BrokerCode_;
   BFTextField_60 PaymentFor_;
   BFTextField_60 PayToEntity_;
   BFDateField EffectiveDate_;
   BFDateField StopDate_;
   BFDecimalField PayEntityId_;

};
