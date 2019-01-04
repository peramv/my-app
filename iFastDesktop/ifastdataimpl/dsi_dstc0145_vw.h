// BFDataImpl header file for DataSet DSTC0145.VW
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
   extern const BFDateFieldId BODate;
   extern const BFTextFieldId BOTime;
   extern const BFTextFieldId BOZone;
   extern const BFDateFieldId FIDate;
   extern const BFTextFieldId FITime;
   extern const BFTextFieldId FIZone;
   extern const BFDecimalFieldId ConfNum;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_BODate;
   extern const BFDataFieldProperties s_FldProp_BOTime;
   extern const BFDataFieldProperties s_FldProp_BOZone;
   extern const BFDataFieldProperties s_FldProp_FIDate;
   extern const BFDataFieldProperties s_FldProp_FITime;
   extern const BFDataFieldProperties s_FldProp_FIZone;
   extern const BFDataFieldProperties s_FldProp_ConfNum;
}


class dsi_DSTC0145_VW : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0145_VW();
   virtual ~dsi_DSTC0145_VW();

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
   BFDateField BODate_;
   BFTextField<15> BOTime_;
   BFTextField<15> BOZone_;
   BFDateField FIDate_;
   BFTextField_10 FITime_;
   BFTextField_10 FIZone_;
   BFDecimalField ConfNum_;

};
