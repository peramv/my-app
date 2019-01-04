// BFDataImpl header file for DataSet DSTC0309.VW_Repeat_Record
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
   extern const BFIntegerFieldId TransFeeCode;
   extern const BFTextFieldId TransType;
   extern const BFTextFieldId RedCodeDecl;
   extern const BFTextFieldId DepTypeDecl;
   extern const BFTextFieldId INDCDecl;
   extern const BFTextFieldId TaxJurisDecl;
   extern const BFTextFieldId TransFeeOverrideAllowed;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_TransFeeCode;
   extern const BFDataFieldProperties s_FldProp_TransType;
   extern const BFDataFieldProperties s_FldProp_RedCodeDecl;
   extern const BFDataFieldProperties s_FldProp_DepTypeDecl;
   extern const BFDataFieldProperties s_FldProp_INDCDecl;
   extern const BFDataFieldProperties s_FldProp_TaxJurisDecl;
   extern const BFDataFieldProperties s_FldProp_TransFeeOverrideAllowed;
}


class dsi_DSTC0309_VW_Repeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0309_VW_Repeat_Record();
   virtual ~dsi_DSTC0309_VW_Repeat_Record();

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
   BFIntegerField TransFeeCode_;
   BFTextField_60 TransType_;
   BFTextField_60 RedCodeDecl_;
   BFTextField_60 DepTypeDecl_;
   BFTextField_60 INDCDecl_;
   BFTextField_60 TaxJurisDecl_;
   BFTextField_1 TransFeeOverrideAllowed_;

};
