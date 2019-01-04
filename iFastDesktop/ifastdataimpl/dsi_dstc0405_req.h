// BFDataImpl header file for DataSet DSTC0405.REQ
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
   extern const BFTextFieldId SessionId;
   extern const BFTextFieldId User_Id;
   extern const BFTextFieldId LanguageCode;
   extern const BFTextFieldId CompanyId;
   extern const BFTextFieldId Track;
   extern const BFTextFieldId Activity;
   extern const BFTextFieldId NextKey;
   extern const BFNumericFieldId AccountNum;
   extern const BFTextFieldId TransType;
   extern const BFTextFieldId Fund;
   extern const BFTextFieldId Class;
   extern const BFTextFieldId DepositType;
   extern const BFTextFieldId RedCode;
   extern const BFDateFieldId TradeDate;
   extern const BFDateFieldId SettleDate;
   extern const BFTextFieldId AmountType;
   extern const BFDecimalFieldId Amount;
   extern const BFTextFieldId GrossOrNet;
   extern const BFDecimalFieldId RESPBenefId;
   extern const BFDecimalFieldId Fee;
   extern const BFTextFieldId FlatPrcnt;
   extern const BFIntegerFieldId OCRdmYear;
   extern const BFIntegerFieldId RESPContrDetlTaxYear;
   extern const BFDecimalFieldId AssistedContrAmt;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_SessionId;
   extern const BFDataFieldProperties s_FldProp_User_Id;
   extern const BFDataFieldProperties s_FldProp_LanguageCode;
   extern const BFDataFieldProperties s_FldProp_CompanyId;
   extern const BFDataFieldProperties s_FldProp_Track;
   extern const BFDataFieldProperties s_FldProp_Activity;
   extern const BFDataFieldProperties s_FldProp_NextKey;
   extern const BFDataFieldProperties s_FldProp_AccountNum;
   extern const BFDataFieldProperties s_FldProp_TransType;
   extern const BFDataFieldProperties s_FldProp_Fund;
   extern const BFDataFieldProperties s_FldProp_Class;
   extern const BFDataFieldProperties s_FldProp_DepositType;
   extern const BFDataFieldProperties s_FldProp_RedCode;
   extern const BFDataFieldProperties s_FldProp_TradeDate;
   extern const BFDataFieldProperties s_FldProp_SettleDate;
   extern const BFDataFieldProperties s_FldProp_AmountType;
   extern const BFDataFieldProperties s_FldProp_Amount;
   extern const BFDataFieldProperties s_FldProp_GrossOrNet;
   extern const BFDataFieldProperties s_FldProp_RESPBenefId;
   extern const BFDataFieldProperties s_FldProp_Fee;
   extern const BFDataFieldProperties s_FldProp_FlatPrcnt;
   extern const BFDataFieldProperties s_FldProp_OCRdmYear;
   extern const BFDataFieldProperties s_FldProp_RESPContrDetlTaxYear;
   extern const BFDataFieldProperties s_FldProp_AssistedContrAmt;
}


class dsi_DSTC0405_REQ : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0405_REQ();
   virtual ~dsi_DSTC0405_REQ();

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
   BFDataField* aFlds_[24];
   // Field Declarations
   BFTextField_60 SessionId_;
   BFTextField_60 User_Id_;
   BFTextField_60 LanguageCode_;
   BFTextField_60 CompanyId_;
   BFTextField_1 Track_;
   BFTextField_60 Activity_;
   BFTextField<100> NextKey_;
   BFNumericField AccountNum_;
   BFTextField_60 TransType_;
   BFTextField_60 Fund_;
   BFTextField_60 Class_;
   BFTextField_60 DepositType_;
   BFTextField_60 RedCode_;
   BFDateField TradeDate_;
   BFDateField SettleDate_;
   BFTextField_60 AmountType_;
   BFDecimalField Amount_;
   BFTextField_1 GrossOrNet_;
   BFDecimalField RESPBenefId_;
   BFDecimalField Fee_;
   BFTextField_1 FlatPrcnt_;
   BFIntegerField OCRdmYear_;
   BFIntegerField RESPContrDetlTaxYear_;
   BFDecimalField AssistedContrAmt_;

};
