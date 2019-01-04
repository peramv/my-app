// BFDataImpl header file for DataSet DSTC0242.REQRepeat_Record
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
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId ClassCode;
   extern const BFIntegerFieldId FundDetlRid;
   extern const BFIntegerFieldId FundDetlVer;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_RunMode;
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_ClassCode;
   extern const BFDataFieldProperties s_FldProp_FundDetlRid;
   extern const BFDataFieldProperties s_FldProp_FundDetlVer;
}


class dsi_DSTC0242_REQRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0242_REQRepeat_Record();
   virtual ~dsi_DSTC0242_REQRepeat_Record();

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
   BFDataField* aFlds_[5];
   // Field Declarations
   BFTextField_60 RunMode_;
   BFTextField<200> FundCode_;
   BFTextField<120> ClassCode_;
   BFIntegerField FundDetlRid_;
   BFIntegerField FundDetlVer_;

};
