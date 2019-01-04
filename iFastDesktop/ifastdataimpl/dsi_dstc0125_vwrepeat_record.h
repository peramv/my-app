// BFDataImpl header file for DataSet DSTC0125.VWRepeat_Record
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
   extern const BFDateFieldId EffectiveDate;
   extern const BFTextFieldId BusDayCode;
   extern const BFTextFieldId IncludeCode;
   extern const BFDateFieldId StopDate;
   extern const BFTextFieldId SundayIsBusDay;
   extern const BFTextFieldId MondayIsBusDay;
   extern const BFTextFieldId TuesdayIsBusDay;
   extern const BFTextFieldId WednesdayIsBusDay;
   extern const BFTextFieldId ThursdayIsBusDay;
   extern const BFTextFieldId FridayIsBusDay;
   extern const BFTextFieldId SaturdayIsBusDay;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_BusDayCode;
   extern const BFDataFieldProperties s_FldProp_IncludeCode;
   extern const BFDataFieldProperties s_FldProp_StopDate;
   extern const BFDataFieldProperties s_FldProp_SundayIsBusDay;
   extern const BFDataFieldProperties s_FldProp_MondayIsBusDay;
   extern const BFDataFieldProperties s_FldProp_TuesdayIsBusDay;
   extern const BFDataFieldProperties s_FldProp_WednesdayIsBusDay;
   extern const BFDataFieldProperties s_FldProp_ThursdayIsBusDay;
   extern const BFDataFieldProperties s_FldProp_FridayIsBusDay;
   extern const BFDataFieldProperties s_FldProp_SaturdayIsBusDay;
}


class dsi_DSTC0125_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0125_VWRepeat_Record();
   virtual ~dsi_DSTC0125_VWRepeat_Record();

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
   BFDataField* aFlds_[11];
   // Field Declarations
   BFDateField EffectiveDate_;
   BFTextField_60 BusDayCode_;
   BFTextField_60 IncludeCode_;
   BFDateField StopDate_;
   BFTextField_1 SundayIsBusDay_;
   BFTextField_1 MondayIsBusDay_;
   BFTextField_1 TuesdayIsBusDay_;
   BFTextField_1 WednesdayIsBusDay_;
   BFTextField_1 ThursdayIsBusDay_;
   BFTextField_1 FridayIsBusDay_;
   BFTextField_1 SaturdayIsBusDay_;

};
