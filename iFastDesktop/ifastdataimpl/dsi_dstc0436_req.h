// BFDataImpl header file for DataSet DSTC0436.REQ
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
   extern const BFNumericFieldId AccountNum;
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId ClassCode;
   extern const BFDateFieldId TradeDate;
   extern const BFTextFieldId ValidateType;
   extern const BFTextFieldId TransType;
   extern const BFNumericFieldId TransId;
   extern const BFNumericFieldId AccountTo;
   extern const BFTextFieldId FundTo;
   extern const BFTextFieldId ClassTo;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_SessionId;
   extern const BFDataFieldProperties s_FldProp_User_Id;
   extern const BFDataFieldProperties s_FldProp_LanguageCode;
   extern const BFDataFieldProperties s_FldProp_CompanyId;
   extern const BFDataFieldProperties s_FldProp_Track;
   extern const BFDataFieldProperties s_FldProp_Activity;
   extern const BFDataFieldProperties s_FldProp_AccountNum;
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_ClassCode;
   extern const BFDataFieldProperties s_FldProp_TradeDate;
   extern const BFDataFieldProperties s_FldProp_ValidateType;
   extern const BFDataFieldProperties s_FldProp_TransType;
   extern const BFDataFieldProperties s_FldProp_TransId;
   extern const BFDataFieldProperties s_FldProp_AccountTo;
   extern const BFDataFieldProperties s_FldProp_FundTo;
   extern const BFDataFieldProperties s_FldProp_ClassTo;
}


class dsi_DSTC0436_REQ : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0436_REQ();
   virtual ~dsi_DSTC0436_REQ();

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
   BFNumericField AccountNum_;
   BFTextField<200> FundCode_;
   BFTextField<120> ClassCode_;
   BFDateField TradeDate_;
   BFTextField_60 ValidateType_;
   BFTextField_60 TransType_;
   BFNumericField TransId_;
   BFNumericField AccountTo_;
   BFTextField_60 FundTo_;
   BFTextField_60 ClassTo_;

};
