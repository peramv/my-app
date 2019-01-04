// BFDataImpl header file for DataSet DSTC0139.VWRepeat_Record
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
   extern const BFTextFieldId CompoundDate;
   extern const BFDecimalFieldId IndexAmt;
   extern const BFTextFieldId IndexType;
   extern const BFTextFieldId IndexFrequency;
   extern const BFDateFieldId StartDate;
   extern const BFDateFieldId EndDate;
   extern const BFDateFieldId NextIndexDate;
   extern const BFNumericFieldId TransNum;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_CompoundDate;
   extern const BFDataFieldProperties s_FldProp_IndexAmt;
   extern const BFDataFieldProperties s_FldProp_IndexType;
   extern const BFDataFieldProperties s_FldProp_IndexFrequency;
   extern const BFDataFieldProperties s_FldProp_StartDate;
   extern const BFDataFieldProperties s_FldProp_EndDate;
   extern const BFDataFieldProperties s_FldProp_NextIndexDate;
   extern const BFDataFieldProperties s_FldProp_TransNum;
}


class dsi_DSTC0139_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0139_VWRepeat_Record();
   virtual ~dsi_DSTC0139_VWRepeat_Record();

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
   BFDataField* aFlds_[8];
   // Field Declarations
   BFTextField_60 CompoundDate_;
   BFDecimalField IndexAmt_;
   BFTextField<3> IndexType_;
   BFTextField_2 IndexFrequency_;
   BFDateField StartDate_;
   BFDateField EndDate_;
   BFDateField NextIndexDate_;
   BFNumericField TransNum_;

};
