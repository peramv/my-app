// BFDataImpl header file for DataSet DSTC0021.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:58 2015


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
   extern const BFTextFieldId RecType;
   extern const BFTextFieldId CheqNum;
   extern const BFDecimalFieldId RefNumber;
   extern const BFDecimalFieldId Fee;
   extern const BFDecimalFieldId FedTax;
   extern const BFDecimalFieldId ProvTax;
   extern const BFDecimalFieldId Amount;
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId ClassCode;
   extern const BFNumericFieldId TransNum;
   extern const BFTextFieldId TransType;
   extern const BFTextFieldId Currency;
   extern const BFTextFieldId Salutation;
   extern const BFTextFieldId PayeeName;
   extern const BFTextFieldId AddrLine1;
   extern const BFTextFieldId AddrLine2;
   extern const BFTextFieldId AddrLine3;
   extern const BFTextFieldId AddrLine4;
   extern const BFTextFieldId AddrLine5;
   extern const BFTextFieldId PostalCode;
   extern const BFTextFieldId BrokerChq;
   extern const BFTextFieldId DeliveryCode;
   extern const BFTextFieldId DeliveryCodeDesc;
   extern const BFDateFieldId PrintDate;
   extern const BFNumericFieldId ChequeAge;
   extern const BFTextFieldId BankAcctNum;
   extern const BFDateFieldId BankRecDate;
   extern const BFDateFieldId ProcessDate;
   extern const BFTextFieldId Username;
   extern const BFDateFieldId ModDate;
   extern const BFTextFieldId ModUser;
   extern const BFDateFieldId CanDate;
   extern const BFTextFieldId CancelUser;
   extern const BFTextFieldId ChqStatus;
   extern const BFTextFieldId ChqStatDesc;
   extern const BFNumericFieldId rxAcctNum;
   extern const BFTextFieldId Memo1;
   extern const BFTextFieldId Memo2;
   extern const BFTextFieldId CountryCode;
   extern const BFTextFieldId CountryName;
   extern const BFTextFieldId CurrencyName;
   extern const BFTextFieldId PayType2;
   extern const BFDecimalFieldId ClawBackTotal;
   extern const BFTextFieldId ChqId;
   extern const BFTextFieldId ChqStage;
   extern const BFDateFieldId StageStampDate;
   extern const BFDateFieldId RemittanceDate;
   extern const BFTextFieldId ChqComments;
   extern const BFNumericFieldId VersionNum;
   extern const BFTextFieldId StageAssignBy;
   extern const BFTextFieldId GovtChqNo;
   extern const BFDateFieldId GovtChqIssueDate;
   extern const BFTextFieldId GovtChqCurrency;
   extern const BFTextFieldId GovtChqStatus;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_RecType;
   extern const BFDataFieldProperties s_FldProp_CheqNum;
   extern const BFDataFieldProperties s_FldProp_RefNumber;
   extern const BFDataFieldProperties s_FldProp_Fee;
   extern const BFDataFieldProperties s_FldProp_FedTax;
   extern const BFDataFieldProperties s_FldProp_ProvTax;
   extern const BFDataFieldProperties s_FldProp_Amount;
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_ClassCode;
   extern const BFDataFieldProperties s_FldProp_TransNum;
   extern const BFDataFieldProperties s_FldProp_TransType;
   extern const BFDataFieldProperties s_FldProp_Currency;
   extern const BFDataFieldProperties s_FldProp_Salutation;
   extern const BFDataFieldProperties s_FldProp_PayeeName;
   extern const BFDataFieldProperties s_FldProp_AddrLine1;
   extern const BFDataFieldProperties s_FldProp_AddrLine2;
   extern const BFDataFieldProperties s_FldProp_AddrLine3;
   extern const BFDataFieldProperties s_FldProp_AddrLine4;
   extern const BFDataFieldProperties s_FldProp_AddrLine5;
   extern const BFDataFieldProperties s_FldProp_PostalCode;
   extern const BFDataFieldProperties s_FldProp_BrokerChq;
   extern const BFDataFieldProperties s_FldProp_DeliveryCode;
   extern const BFDataFieldProperties s_FldProp_DeliveryCodeDesc;
   extern const BFDataFieldProperties s_FldProp_PrintDate;
   extern const BFDataFieldProperties s_FldProp_ChequeAge;
   extern const BFDataFieldProperties s_FldProp_BankAcctNum;
   extern const BFDataFieldProperties s_FldProp_BankRecDate;
   extern const BFDataFieldProperties s_FldProp_ProcessDate;
   extern const BFDataFieldProperties s_FldProp_Username;
   extern const BFDataFieldProperties s_FldProp_ModDate;
   extern const BFDataFieldProperties s_FldProp_ModUser;
   extern const BFDataFieldProperties s_FldProp_CanDate;
   extern const BFDataFieldProperties s_FldProp_CancelUser;
   extern const BFDataFieldProperties s_FldProp_ChqStatus;
   extern const BFDataFieldProperties s_FldProp_ChqStatDesc;
   extern const BFDataFieldProperties s_FldProp_rxAcctNum;
   extern const BFDataFieldProperties s_FldProp_Memo1;
   extern const BFDataFieldProperties s_FldProp_Memo2;
   extern const BFDataFieldProperties s_FldProp_CountryCode;
   extern const BFDataFieldProperties s_FldProp_CountryName;
   extern const BFDataFieldProperties s_FldProp_CurrencyName;
   extern const BFDataFieldProperties s_FldProp_PayType2;
   extern const BFDataFieldProperties s_FldProp_ClawBackTotal;
   extern const BFDataFieldProperties s_FldProp_ChqId;
   extern const BFDataFieldProperties s_FldProp_ChqStage;
   extern const BFDataFieldProperties s_FldProp_StageStampDate;
   extern const BFDataFieldProperties s_FldProp_RemittanceDate;
   extern const BFDataFieldProperties s_FldProp_ChqComments;
   extern const BFDataFieldProperties s_FldProp_VersionNum;
   extern const BFDataFieldProperties s_FldProp_StageAssignBy;
   extern const BFDataFieldProperties s_FldProp_GovtChqNo;
   extern const BFDataFieldProperties s_FldProp_GovtChqIssueDate;
   extern const BFDataFieldProperties s_FldProp_GovtChqCurrency;
   extern const BFDataFieldProperties s_FldProp_GovtChqStatus;
}


class dsi_DSTC0021_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0021_VWRepeat_Record();
   virtual ~dsi_DSTC0021_VWRepeat_Record();

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
   BFDataField* aFlds_[54];
   // Field Declarations
   BFTextField_60 RecType_;
   BFTextField_60 CheqNum_;
   BFDecimalField RefNumber_;
   BFDecimalField Fee_;
   BFDecimalField FedTax_;
   BFDecimalField ProvTax_;
   BFDecimalField Amount_;
   BFTextField<200> FundCode_;
   BFTextField<120> ClassCode_;
   BFNumericField TransNum_;
   BFTextField_60 TransType_;
   BFTextField<200> Currency_;
   BFTextField<25> Salutation_;
   BFTextField_60 PayeeName_;
   BFTextField_60 AddrLine1_;
   BFTextField_60 AddrLine2_;
   BFTextField_60 AddrLine3_;
   BFTextField_60 AddrLine4_;
   BFTextField_60 AddrLine5_;
   BFTextField<9> PostalCode_;
   BFTextField_1 BrokerChq_;
   BFTextField_60 DeliveryCode_;
   BFTextField_60 DeliveryCodeDesc_;
   BFDateField PrintDate_;
   BFNumericField ChequeAge_;
   BFTextField_60 BankAcctNum_;
   BFDateField BankRecDate_;
   BFDateField ProcessDate_;
   BFTextField_60 Username_;
   BFDateField ModDate_;
   BFTextField_60 ModUser_;
   BFDateField CanDate_;
   BFTextField_60 CancelUser_;
   BFTextField_60 ChqStatus_;
   BFTextField_60 ChqStatDesc_;
   BFNumericField rxAcctNum_;
   BFTextField_60 Memo1_;
   BFTextField_60 Memo2_;
   BFTextField_60 CountryCode_;
   BFTextField_60 CountryName_;
   BFTextField_60 CurrencyName_;
   BFTextField_60 PayType2_;
   BFDecimalField ClawBackTotal_;
   BFTextField_60 ChqId_;
   BFTextField_60 ChqStage_;
   BFDateField StageStampDate_;
   BFDateField RemittanceDate_;
   BFTextField<100> ChqComments_;
   BFNumericField VersionNum_;
   BFTextField_60 StageAssignBy_;
   BFTextField_60 GovtChqNo_;
   BFDateField GovtChqIssueDate_;
   BFTextField_60 GovtChqCurrency_;
   BFTextField_60 GovtChqStatus_;

};
