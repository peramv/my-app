// BFDataImpl header file for DataSet DSTC0406.REQ
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
   extern const BFTextFieldId TradeType;
   extern const BFNumericFieldId TransId;
   extern const BFNumericFieldId AccountNum;
   extern const BFTextFieldId TransType;
   extern const BFDateFieldId EffectiveDate;
   extern const BFTextFieldId DepositType;
   extern const BFTextFieldId RedCode;
   extern const BFNumericFieldId AccountTo;
   extern const BFNumericFieldId OverrideRepeats;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_SessionId;
   extern const BFDataFieldProperties s_FldProp_User_Id;
   extern const BFDataFieldProperties s_FldProp_LanguageCode;
   extern const BFDataFieldProperties s_FldProp_CompanyId;
   extern const BFDataFieldProperties s_FldProp_Track;
   extern const BFDataFieldProperties s_FldProp_Activity;
   extern const BFDataFieldProperties s_FldProp_NextKey;
   extern const BFDataFieldProperties s_FldProp_TradeType;
   extern const BFDataFieldProperties s_FldProp_TransId;
   extern const BFDataFieldProperties s_FldProp_AccountNum;
   extern const BFDataFieldProperties s_FldProp_TransType;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_DepositType;
   extern const BFDataFieldProperties s_FldProp_RedCode;
   extern const BFDataFieldProperties s_FldProp_AccountTo;
   extern const BFDataFieldProperties s_FldProp_OverrideRepeats;
}


class dsi_DSTC0406_REQ : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0406_REQ();
   virtual ~dsi_DSTC0406_REQ();

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
   BFDataField* aFlds_[16];
   // Field Declarations
   BFTextField_60 SessionId_;
   BFTextField_60 User_Id_;
   BFTextField_60 LanguageCode_;
   BFTextField_60 CompanyId_;
   BFTextField_1 Track_;
   BFTextField_60 Activity_;
   BFTextField<100> NextKey_;
   BFTextField_60 TradeType_;
   BFNumericField TransId_;
   BFNumericField AccountNum_;
   BFTextField_60 TransType_;
   BFDateField EffectiveDate_;
   BFTextField_60 DepositType_;
   BFTextField_60 RedCode_;
   BFNumericField AccountTo_;
   BFNumericField OverrideRepeats_;

};
