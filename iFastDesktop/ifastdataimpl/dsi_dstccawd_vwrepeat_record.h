// BFDataImpl header file for DataSet DSTCCAWD.VWRepeat_Record
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
   extern const BFTextFieldId ConfirmID;
   extern const BFTextFieldId Batch;
   extern const BFTextFieldId BusinessArea;
   extern const BFTextFieldId WorkType;
   extern const BFTextFieldId StatusDesc;
   extern const BFTextFieldId WorkAssgn;
   extern const BFTextFieldId AWDComment;
   extern const BFTextFieldId Remark1;
   extern const BFTextFieldId Remark2;
   extern const BFTextFieldId Remark3;
   extern const BFTextFieldId Remark4;
   extern const BFTextFieldId Remark5;
   extern const BFTextFieldId Remark6;
   extern const BFTextFieldId Remark7;
   extern const BFTextFieldId Remark8;
   extern const BFTextFieldId Remark9;
   extern const BFTextFieldId Remark10;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_ConfirmID;
   extern const BFDataFieldProperties s_FldProp_Batch;
   extern const BFDataFieldProperties s_FldProp_BusinessArea;
   extern const BFDataFieldProperties s_FldProp_WorkType;
   extern const BFDataFieldProperties s_FldProp_StatusDesc;
   extern const BFDataFieldProperties s_FldProp_WorkAssgn;
   extern const BFDataFieldProperties s_FldProp_AWDComment;
   extern const BFDataFieldProperties s_FldProp_Remark1;
   extern const BFDataFieldProperties s_FldProp_Remark2;
   extern const BFDataFieldProperties s_FldProp_Remark3;
   extern const BFDataFieldProperties s_FldProp_Remark4;
   extern const BFDataFieldProperties s_FldProp_Remark5;
   extern const BFDataFieldProperties s_FldProp_Remark6;
   extern const BFDataFieldProperties s_FldProp_Remark7;
   extern const BFDataFieldProperties s_FldProp_Remark8;
   extern const BFDataFieldProperties s_FldProp_Remark9;
   extern const BFDataFieldProperties s_FldProp_Remark10;
}


class dsi_DSTCCAWD_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTCCAWD_VWRepeat_Record();
   virtual ~dsi_DSTCCAWD_VWRepeat_Record();

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
   BFTextField<20> ConfirmID_;
   BFTextField_60 Batch_;
   BFTextField_60 BusinessArea_;
   BFTextField_60 WorkType_;
   BFTextField_60 StatusDesc_;
   BFTextField_60 WorkAssgn_;
   BFTextField_1 AWDComment_;
   BFTextField<100> Remark1_;
   BFTextField<100> Remark2_;
   BFTextField<100> Remark3_;
   BFTextField<100> Remark4_;
   BFTextField<100> Remark5_;
   BFTextField<100> Remark6_;
   BFTextField<100> Remark7_;
   BFTextField<100> Remark8_;
   BFTextField<100> Remark9_;
   BFTextField<100> Remark10_;

};
