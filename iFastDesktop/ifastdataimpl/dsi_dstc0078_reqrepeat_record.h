// BFDataImpl header file for DataSet DSTC0078.REQRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Thursday, October 01, 2015 12:20:28


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
   extern const BFNumericFieldId EntityId;
   extern const BFDateFieldId EffectiveDate;
   extern const BFTextFieldId Salutation;
   extern const BFTextFieldId LastName;
   extern const BFTextFieldId FirstName;
   extern const BFTextFieldId BirthLastName;
   extern const BFTextFieldId BirthFirstName;
   extern const BFTextFieldId Gender;
   extern const BFDateFieldId DofBirth;
   extern const BFTextFieldId SIN;
   extern const BFTextFieldId OccupationCode;
   extern const BFTextFieldId LanguageCode;
   extern const BFTextFieldId HomePhone;
   extern const BFTextFieldId HomeFax;
   extern const BFTextFieldId BusinessPhone;
   extern const BFTextFieldId BusinessExt;
   extern const BFTextFieldId BusinessFax;
   extern const BFTextFieldId Telex;
   extern const BFTextFieldId Email;
   extern const BFDateFieldId DofDeath;
   extern const BFDateFieldId DofDeathNotice;
   extern const BFNumericFieldId EntityIdentityVer;
   extern const BFNumericFieldId EntityIdentityRid;
   extern const BFTextFieldId HomePhoneCntry;
   extern const BFTextFieldId HomePhoneArea;
   extern const BFTextFieldId BusinessPhoneCntry;
   extern const BFTextFieldId BusinessPhoneArea;
   extern const BFTextFieldId HomeFaxCntry;
   extern const BFTextFieldId HomeFaxArea;
   extern const BFTextFieldId BusFaxCntry;
   extern const BFTextFieldId BusFaxArea;
   extern const BFTextFieldId EmployeeClass;
   extern const BFTextFieldId Nationality;
   extern const BFTextFieldId OtherOccupation;
   extern const BFNumericFieldId SpouseEntityID;
   extern const BFTextFieldId BirthPlace;
   extern const BFTextFieldId RiskLevel;
   extern const BFDateFieldId TaxJurisDeff;
   extern const BFTextFieldId TaxJuris;
   extern const BFTextFieldId EUSDTaxOption;
   extern const BFTextFieldId UpdShrTaxJuris;
   extern const BFTextFieldId CountryOfBirth;
   extern const BFTextFieldId ContactName;
   extern const BFTextFieldId Email2;
   extern const BFTextFieldId SecondPhoneNum;
   extern const BFTextFieldId SecondPhoneNumExt;
   extern const BFTextFieldId FATCAFFI;
   extern const BFTextFieldId CountryOfExposure;
   extern const BFTextFieldId VerifyStatDetails;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_RunMode;
   extern const BFDataFieldProperties s_FldProp_EntityId;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_Salutation;
   extern const BFDataFieldProperties s_FldProp_LastName;
   extern const BFDataFieldProperties s_FldProp_FirstName;
   extern const BFDataFieldProperties s_FldProp_BirthLastName;
   extern const BFDataFieldProperties s_FldProp_BirthFirstName;
   extern const BFDataFieldProperties s_FldProp_Gender;
   extern const BFDataFieldProperties s_FldProp_DofBirth;
   extern const BFDataFieldProperties s_FldProp_SIN;
   extern const BFDataFieldProperties s_FldProp_OccupationCode;
   extern const BFDataFieldProperties s_FldProp_LanguageCode;
   extern const BFDataFieldProperties s_FldProp_HomePhone;
   extern const BFDataFieldProperties s_FldProp_HomeFax;
   extern const BFDataFieldProperties s_FldProp_BusinessPhone;
   extern const BFDataFieldProperties s_FldProp_BusinessExt;
   extern const BFDataFieldProperties s_FldProp_BusinessFax;
   extern const BFDataFieldProperties s_FldProp_Telex;
   extern const BFDataFieldProperties s_FldProp_Email;
   extern const BFDataFieldProperties s_FldProp_DofDeath;
   extern const BFDataFieldProperties s_FldProp_DofDeathNotice;
   extern const BFDataFieldProperties s_FldProp_EntityIdentityVer;
   extern const BFDataFieldProperties s_FldProp_EntityIdentityRid;
   extern const BFDataFieldProperties s_FldProp_HomePhoneCntry;
   extern const BFDataFieldProperties s_FldProp_HomePhoneArea;
   extern const BFDataFieldProperties s_FldProp_BusinessPhoneCntry;
   extern const BFDataFieldProperties s_FldProp_BusinessPhoneArea;
   extern const BFDataFieldProperties s_FldProp_HomeFaxCntry;
   extern const BFDataFieldProperties s_FldProp_HomeFaxArea;
   extern const BFDataFieldProperties s_FldProp_BusFaxCntry;
   extern const BFDataFieldProperties s_FldProp_BusFaxArea;
   extern const BFDataFieldProperties s_FldProp_EmployeeClass;
   extern const BFDataFieldProperties s_FldProp_Nationality;
   extern const BFDataFieldProperties s_FldProp_OtherOccupation;
   extern const BFDataFieldProperties s_FldProp_SpouseEntityID;
   extern const BFDataFieldProperties s_FldProp_BirthPlace;
   extern const BFDataFieldProperties s_FldProp_RiskLevel;
   extern const BFDataFieldProperties s_FldProp_TaxJurisDeff;
   extern const BFDataFieldProperties s_FldProp_TaxJuris;
   extern const BFDataFieldProperties s_FldProp_EUSDTaxOption;
   extern const BFDataFieldProperties s_FldProp_UpdShrTaxJuris;
   extern const BFDataFieldProperties s_FldProp_CountryOfBirth;
   extern const BFDataFieldProperties s_FldProp_ContactName;
   extern const BFDataFieldProperties s_FldProp_Email2;
   extern const BFDataFieldProperties s_FldProp_SecondPhoneNum;
   extern const BFDataFieldProperties s_FldProp_SecondPhoneNumExt;
   extern const BFDataFieldProperties s_FldProp_FATCAFFI;
   extern const BFDataFieldProperties s_FldProp_CountryOfExposure;
   extern const BFDataFieldProperties s_FldProp_VerifyStatDetails;
}


class dsi_DSTC0078_REQRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0078_REQRepeat_Record();
   virtual ~dsi_DSTC0078_REQRepeat_Record();

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
    BFDataField* aFlds_[50];
   // Field Declarations
   BFTextField_60 RunMode_;
   BFNumericField EntityId_;
   BFDateField EffectiveDate_;
   BFTextField<25> Salutation_;
   BFTextField<80> LastName_;
   BFTextField_60 FirstName_;
   BFTextField_60 BirthLastName_;
   BFTextField_60 BirthFirstName_;
   BFTextField_60 Gender_;
   BFDateField DofBirth_;
   BFTextField_60 SIN_;
   BFTextField_60 OccupationCode_;
   BFTextField_60 LanguageCode_;
   BFTextField_60 HomePhone_;
   BFTextField_60 HomeFax_;
   BFTextField_60 BusinessPhone_;
   BFTextField_60 BusinessExt_;
   BFTextField_60 BusinessFax_;
   BFTextField_60 Telex_;
   BFTextField_60 Email_;
   BFDateField DofDeath_;
   BFDateField DofDeathNotice_;
   BFNumericField EntityIdentityVer_;
   BFNumericField EntityIdentityRid_;
   BFTextField_60 HomePhoneCntry_;
   BFTextField_60 HomePhoneArea_;
   BFTextField_60 BusinessPhoneCntry_;
   BFTextField_60 BusinessPhoneArea_;
   BFTextField_60 HomeFaxCntry_;
   BFTextField_60 HomeFaxArea_;
   BFTextField_60 BusFaxCntry_;
   BFTextField_60 BusFaxArea_;
   BFTextField_10 EmployeeClass_;
   BFTextField_60 Nationality_;
   BFTextField<40> OtherOccupation_;
   BFNumericField SpouseEntityID_;
   BFTextField<40> BirthPlace_;
   BFTextField_60 RiskLevel_;
   BFDateField TaxJurisDeff_;
   BFTextField_60 TaxJuris_;
   BFTextField<40> EUSDTaxOption_;
   BFTextField_2 UpdShrTaxJuris_;
   BFTextField_60 CountryOfBirth_;
   BFTextField<80> ContactName_;
   BFTextField_60 Email2_;
   BFTextField_60 SecondPhoneNum_;
   BFTextField_60 SecondPhoneNumExt_;
   BFTextField_60 FATCAFFI_;
   BFTextField_6 CountryOfExposure_;
   BFTextField_60 VerifyStatDetails_;
};
