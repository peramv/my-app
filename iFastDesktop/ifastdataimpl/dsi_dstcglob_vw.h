// BFDataImpl header file for DataSet DSTCGLOB.VW
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
   extern const BFTextFieldId Operator_Extension;
   extern const BFTextFieldId Profile;
   extern const BFTextFieldId Registry_Directory;
   extern const BFNumericFieldId Using_AWD;
   extern const BFNumericFieldId LastActiveAccountNum;
   extern const BFNumericFieldId LastActiveShrNum;
   extern const BFTextFieldId Management_Co;
   extern const BFTextFieldId Search_Type;
   extern const BFTextFieldId System;
   extern const BFTextFieldId CallerName;
   extern const BFTextFieldId CallerPhoneNumber;
   extern const BFNumericFieldId LastActiveEntityId;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_Operator_Extension;
   extern const BFDataFieldProperties s_FldProp_Profile;
   extern const BFDataFieldProperties s_FldProp_Registry_Directory;
   extern const BFDataFieldProperties s_FldProp_Using_AWD;
   extern const BFDataFieldProperties s_FldProp_LastActiveAccountNum;
   extern const BFDataFieldProperties s_FldProp_LastActiveShrNum;
   extern const BFDataFieldProperties s_FldProp_Management_Co;
   extern const BFDataFieldProperties s_FldProp_Search_Type;
   extern const BFDataFieldProperties s_FldProp_System;
   extern const BFDataFieldProperties s_FldProp_CallerName;
   extern const BFDataFieldProperties s_FldProp_CallerPhoneNumber;
   extern const BFDataFieldProperties s_FldProp_LastActiveEntityId;
}


class dsi_DSTCGLOB_VW : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTCGLOB_VW();
   virtual ~dsi_DSTCGLOB_VW();

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
   BFDataField* aFlds_[12];
   // Field Declarations
   BFTextField_10 Operator_Extension_;
   BFTextField<40> Profile_;
   BFTextField<100> Registry_Directory_;
   BFNumericField Using_AWD_;
   BFNumericField LastActiveAccountNum_;
   BFNumericField LastActiveShrNum_;
   BFTextField_2 Management_Co_;
   BFTextField<50> Search_Type_;
   BFTextField<4> System_;
   BFTextField<100> CallerName_;
   BFTextField_60 CallerPhoneNumber_;
   BFNumericField LastActiveEntityId_;

};
