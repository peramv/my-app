// BFDataImpl header file for DataSet DSTC0450.VW
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
   extern const BFTextFieldId MoreAvailable;
   extern const BFTextFieldId NextKey;
   extern const BFTextFieldId DefaultReportingFFI;
   extern const BFNumericFieldId RepeatCount;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_MoreAvailable;
   extern const BFDataFieldProperties s_FldProp_NextKey;
   extern const BFDataFieldProperties s_FldProp_DefaultReportingFFI;
   extern const BFDataFieldProperties s_FldProp_RepeatCount;
}


class dsi_DSTC0450_VW : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0450_VW();
   virtual ~dsi_DSTC0450_VW();

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
   BFDataField* aFlds_[4];
   // Field Declarations
   BFTextField_1 MoreAvailable_;
   BFTextField<100> NextKey_;
   BFTextField<64> DefaultReportingFFI_;
   BFNumericField RepeatCount_;

};
