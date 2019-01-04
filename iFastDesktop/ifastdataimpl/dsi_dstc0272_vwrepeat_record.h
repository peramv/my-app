// BFDataImpl header file for DataSet DSTC0272.VWRepeat_Record
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
   extern const BFTextFieldId ExtTransferType;
   extern const BFTextFieldId Description;
   extern const BFTextFieldId FirstLetter;
   extern const BFIntegerFieldId FirstLetterDays;
   extern const BFTextFieldId SecondLetter;
   extern const BFIntegerFieldId SecondLetterDays;
   extern const BFTextFieldId ThirdLetter;
   extern const BFIntegerFieldId ThirdLetterDays;
   extern const BFTextFieldId SubsequentLetter;
   extern const BFIntegerFieldId SubsequentLetterFreq;
   extern const BFDateFieldId ProcessDate;
   extern const BFTextFieldId Username;
   extern const BFDateFieldId ModDate;
   extern const BFTextFieldId ModUser;
   extern const BFDecimalFieldId Version;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_ExtTransferType;
   extern const BFDataFieldProperties s_FldProp_Description;
   extern const BFDataFieldProperties s_FldProp_FirstLetter;
   extern const BFDataFieldProperties s_FldProp_FirstLetterDays;
   extern const BFDataFieldProperties s_FldProp_SecondLetter;
   extern const BFDataFieldProperties s_FldProp_SecondLetterDays;
   extern const BFDataFieldProperties s_FldProp_ThirdLetter;
   extern const BFDataFieldProperties s_FldProp_ThirdLetterDays;
   extern const BFDataFieldProperties s_FldProp_SubsequentLetter;
   extern const BFDataFieldProperties s_FldProp_SubsequentLetterFreq;
   extern const BFDataFieldProperties s_FldProp_ProcessDate;
   extern const BFDataFieldProperties s_FldProp_Username;
   extern const BFDataFieldProperties s_FldProp_ModDate;
   extern const BFDataFieldProperties s_FldProp_ModUser;
   extern const BFDataFieldProperties s_FldProp_Version;
}


class dsi_DSTC0272_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0272_VWRepeat_Record();
   virtual ~dsi_DSTC0272_VWRepeat_Record();

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
   BFDataField* aFlds_[15];
   // Field Declarations
   BFTextField_60 ExtTransferType_;
   BFTextField_60 Description_;
   BFTextField_60 FirstLetter_;
   BFIntegerField FirstLetterDays_;
   BFTextField_60 SecondLetter_;
   BFIntegerField SecondLetterDays_;
   BFTextField_60 ThirdLetter_;
   BFIntegerField ThirdLetterDays_;
   BFTextField_60 SubsequentLetter_;
   BFIntegerField SubsequentLetterFreq_;
   BFDateField ProcessDate_;
   BFTextField_60 Username_;
   BFDateField ModDate_;
   BFTextField_60 ModUser_;
   BFDecimalField Version_;

};
