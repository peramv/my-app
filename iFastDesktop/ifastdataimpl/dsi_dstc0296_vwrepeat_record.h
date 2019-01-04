// BFDataImpl header file for DataSet DSTC0296.VWRepeat_Record
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
   extern const BFTextFieldId ToFund;
   extern const BFTextFieldId ToClass;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_ToFund;
   extern const BFDataFieldProperties s_FldProp_ToClass;
}


class dsi_DSTC0296_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0296_VWRepeat_Record();
   virtual ~dsi_DSTC0296_VWRepeat_Record();

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
   BFDataField* aFlds_[2];
   // Field Declarations
   BFTextField_60 ToFund_;
   BFTextField_60 ToClass_;

};
