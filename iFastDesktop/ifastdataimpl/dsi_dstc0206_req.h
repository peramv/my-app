// BFDataImpl header file for DataSet DSTC0206.REQ
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
   extern const BFTextFieldId NextKey;
   extern const BFTextFieldId SessionId;
   extern const BFTextFieldId User_Id;
   extern const BFTextFieldId LanguageCode;
   extern const BFTextFieldId CompanyId;
   extern const BFTextFieldId Track;
   extern const BFTextFieldId Activity;
   extern const BFTextFieldId SearchType;
   extern const BFTextFieldId WireOrdNum;
   extern const BFNumericFieldId TransNum;
   extern const BFNumericFieldId AccountNum;
   extern const BFTextFieldId TransType;
   extern const BFTextFieldId rxCompCode;
   extern const BFTextFieldId BrokerCode;
   extern const BFTextFieldId IntrCode;
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId SettleCurrency;
   extern const BFDateFieldId TradeDate;
   extern const BFDateFieldId SettleDate;
   extern const BFDateFieldId StartDate;
   extern const BFDateFieldId EndDate;
   extern const BFNumericFieldId OverrideRepeats;
   extern const BFTextFieldId VolSettleType;
   extern const BFTextFieldId ExternalIdType;
   extern const BFTextFieldId ExternalId;
   extern const BFTextFieldId RegAgentCode;
   extern const BFTextFieldId ExcludeStopSettle;
   //Property Externs
   extern const BFDataFieldProperties s_FldProp_NextKey;
   extern const BFDataFieldProperties s_FldProp_SessionId;
   extern const BFDataFieldProperties s_FldProp_User_Id;
   extern const BFDataFieldProperties s_FldProp_LanguageCode;
   extern const BFDataFieldProperties s_FldProp_CompanyId;
   extern const BFDataFieldProperties s_FldProp_Track;
   extern const BFDataFieldProperties s_FldProp_Activity;
   extern const BFDataFieldProperties s_FldProp_SearchType;
   extern const BFDataFieldProperties s_FldProp_WireOrdNum;
   extern const BFDataFieldProperties s_FldProp_TransNum;
   extern const BFDataFieldProperties s_FldProp_AccountNum;
   extern const BFDataFieldProperties s_FldProp_TransType;
   extern const BFDataFieldProperties s_FldProp_rxCompCode;
   extern const BFDataFieldProperties s_FldProp_BrokerCode;
   extern const BFDataFieldProperties s_FldProp_IntrCode;
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_SettleCurrency;
   extern const BFDataFieldProperties s_FldProp_TradeDate;
   extern const BFDataFieldProperties s_FldProp_SettleDate;
   extern const BFDataFieldProperties s_FldProp_StartDate;
   extern const BFDataFieldProperties s_FldProp_EndDate;
   extern const BFDataFieldProperties s_FldProp_OverrideRepeats;
   extern const BFDataFieldProperties s_FldProp_VolSettleType;
   extern const BFDataFieldProperties s_FldProp_ExternalIdType;
   extern const BFDataFieldProperties s_FldProp_ExternalId;
   extern const BFDataFieldProperties s_FldProp_RegAgentCode;
   extern const BFDataFieldProperties s_FldProp_ExcludeStopSettle;
}


class dsi_DSTC0206_REQ : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0206_REQ();
   virtual ~dsi_DSTC0206_REQ();

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
   BFDataField* aFlds_[27];
   // Field Declarations
   BFTextField<100> NextKey_;
   BFTextField_60 SessionId_;
   BFTextField_60 User_Id_;
   BFTextField_60 LanguageCode_;
   BFTextField_60 CompanyId_;
   BFTextField_1 Track_;
   BFTextField_60 Activity_;
   BFTextField_60 SearchType_;
   BFTextField<20> WireOrdNum_;
   BFNumericField TransNum_;
   BFNumericField AccountNum_;
   BFTextField_60 TransType_;
   BFTextField_60 rxCompCode_;
   BFTextField_60 BrokerCode_;
   BFTextField_60 IntrCode_;
   BFTextField<200> FundCode_;
   BFTextField_60 SettleCurrency_;
   BFDateField TradeDate_;
   BFDateField SettleDate_;
   BFDateField StartDate_;
   BFDateField EndDate_;
   BFNumericField OverrideRepeats_;
   BFTextField_60 VolSettleType_;
   BFTextField_60 ExternalIdType_;
   BFTextField_60 ExternalId_;
   BFTextField_60 RegAgentCode_;
   BFTextField_10 ExcludeStopSettle_;
};
