// BFDataImpl header file for DataSet DSTC0086.VWRepeat_Record
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
   extern const BFTextFieldId IntermName;
   extern const BFTextFieldId IntermCode;
   extern const BFTextFieldId AllowWire;
   extern const BFTextFieldId MMWire;
   extern const BFTextFieldId VolSettleType;
   extern const BFTextFieldId SWPSettleESGElig;
   extern const BFTextFieldId CashIDSettleESGElig;
   extern const BFTextFieldId NFUpdate;
   extern const BFTextFieldId IntrCssStatus;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_IntermName;
   extern const BFDataFieldProperties s_FldProp_IntermCode;
   extern const BFDataFieldProperties s_FldProp_AllowWire;
   extern const BFDataFieldProperties s_FldProp_MMWire;
   extern const BFDataFieldProperties s_FldProp_VolSettleType;
   extern const BFDataFieldProperties s_FldProp_SWPSettleESGElig;
   extern const BFDataFieldProperties s_FldProp_CashIDSettleESGElig;
   extern const BFDataFieldProperties s_FldProp_NFUpdate;
   extern const BFDataFieldProperties s_FldProp_IntrCssStatus;
}


class dsi_DSTC0086_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0086_VWRepeat_Record();
   virtual ~dsi_DSTC0086_VWRepeat_Record();

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
   BFDataField* aFlds_[9];
   // Field Declarations
   BFTextField_60 IntermName_;
   BFTextField_60 IntermCode_;
   BFTextField_1 AllowWire_;
   BFTextField_1 MMWire_;
   BFTextField_60 VolSettleType_;
   BFTextField_1 SWPSettleESGElig_;
   BFTextField_1 CashIDSettleESGElig_;
   BFTextField<20> NFUpdate_;
   BFTextField<50> IntrCssStatus_;

};
