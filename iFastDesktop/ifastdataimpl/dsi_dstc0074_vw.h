// BFDataImpl header file for DataSet DSTC0074.VW
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
   extern const BFTextFieldId UpdateStatus;
   extern const BFIntegerFieldId WarnCode1;
   extern const BFTextFieldId WarnDesc1;
   extern const BFIntegerFieldId WarnCode2;
   extern const BFTextFieldId WarnDesc2;
   extern const BFIntegerFieldId WarnCode3;
   extern const BFTextFieldId WarnDesc3;
   extern const BFIntegerFieldId WarnCode4;
   extern const BFTextFieldId WarnDesc4;
   extern const BFIntegerFieldId WarnCode5;
   extern const BFTextFieldId WarnDesc5;
   extern const BFNumericFieldId RepeatCount;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_UpdateStatus;
   extern const BFDataFieldProperties s_FldProp_WarnCode1;
   extern const BFDataFieldProperties s_FldProp_WarnDesc1;
   extern const BFDataFieldProperties s_FldProp_WarnCode2;
   extern const BFDataFieldProperties s_FldProp_WarnDesc2;
   extern const BFDataFieldProperties s_FldProp_WarnCode3;
   extern const BFDataFieldProperties s_FldProp_WarnDesc3;
   extern const BFDataFieldProperties s_FldProp_WarnCode4;
   extern const BFDataFieldProperties s_FldProp_WarnDesc4;
   extern const BFDataFieldProperties s_FldProp_WarnCode5;
   extern const BFDataFieldProperties s_FldProp_WarnDesc5;
   extern const BFDataFieldProperties s_FldProp_RepeatCount;
}


class dsi_DSTC0074_VW : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0074_VW();
   virtual ~dsi_DSTC0074_VW();

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
   BFTextField_1 UpdateStatus_;
   BFIntegerField WarnCode1_;
   BFTextField_60 WarnDesc1_;
   BFIntegerField WarnCode2_;
   BFTextField_60 WarnDesc2_;
   BFIntegerField WarnCode3_;
   BFTextField_60 WarnDesc3_;
   BFIntegerField WarnCode4_;
   BFTextField_60 WarnDesc4_;
   BFIntegerField WarnCode5_;
   BFTextField_60 WarnDesc5_;
   BFNumericField RepeatCount_;

};
