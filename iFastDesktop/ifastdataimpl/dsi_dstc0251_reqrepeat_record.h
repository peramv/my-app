// BFDataImpl header file for DataSet DSTC0251.REQRepeat_Record
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
   extern const BFTextFieldId AMSCode;
   extern const BFDateFieldId EffectiveDate;
   extern const BFTextFieldId GoodBad;
   extern const BFNumericFieldId BrokerAMSRId;
   extern const BFDecimalFieldId BrokerAMSVer;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_RunMode;
   extern const BFDataFieldProperties s_FldProp_AMSCode;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_GoodBad;
   extern const BFDataFieldProperties s_FldProp_BrokerAMSRId;
   extern const BFDataFieldProperties s_FldProp_BrokerAMSVer;
}


class dsi_DSTC0251_REQRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0251_REQRepeat_Record();
   virtual ~dsi_DSTC0251_REQRepeat_Record();

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
   BFDataField* aFlds_[6];
   // Field Declarations
   BFTextField_60 RunMode_;
   BFTextField_60 AMSCode_;
   BFDateField EffectiveDate_;
   BFTextField_1 GoodBad_;
   BFNumericField BrokerAMSRId_;
   BFDecimalField BrokerAMSVer_;

};
