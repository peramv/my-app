// BFDataImpl header file for DataSet DSTC0023.REQ
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
   extern const BFTextFieldId FundCode;
   extern const BFTextFieldId ClassCode;
   extern const BFDateFieldId FromDate;
   extern const BFDateFieldId ToDate;
   extern const BFTextFieldId PrevDatePressed;
   extern const BFTextFieldId NextDatePressed;
   extern const BFTextFieldId NextKey;
   extern const BFTextFieldId SessionId;
   extern const BFTextFieldId User_Id;
   extern const BFTextFieldId LanguageCode;
   extern const BFTextFieldId CompanyId;
   extern const BFTextFieldId Track;
   extern const BFTextFieldId Activity;
   extern const BFTextFieldId SearchFundType;
   extern const BFTextFieldId FundWKN;
   extern const BFTextFieldId FundISIN;
   extern const BFNumericFieldId OverrideRepeats;
   extern const BFTextFieldId BrokerCode;
   extern const BFTextFieldId BranchCode;
   extern const BFTextFieldId SalesRepCode;
   extern const BFTextFieldId IgnoreFundLoadGrp;
   extern const BFTextFieldId ExcludeClass;
   extern const BFTextFieldId GetLastIDRate;
   extern const BFTextFieldId GetTransType;
   extern const BFTextFieldId GetNextAvailRate;
   extern const BFTextFieldId CUSIP;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_FundCode;
   extern const BFDataFieldProperties s_FldProp_ClassCode;
   extern const BFDataFieldProperties s_FldProp_FromDate;
   extern const BFDataFieldProperties s_FldProp_ToDate;
   extern const BFDataFieldProperties s_FldProp_PrevDatePressed;
   extern const BFDataFieldProperties s_FldProp_NextDatePressed;
   extern const BFDataFieldProperties s_FldProp_NextKey;
   extern const BFDataFieldProperties s_FldProp_SessionId;
   extern const BFDataFieldProperties s_FldProp_User_Id;
   extern const BFDataFieldProperties s_FldProp_LanguageCode;
   extern const BFDataFieldProperties s_FldProp_CompanyId;
   extern const BFDataFieldProperties s_FldProp_Track;
   extern const BFDataFieldProperties s_FldProp_Activity;
   extern const BFDataFieldProperties s_FldProp_SearchFundType;
   extern const BFDataFieldProperties s_FldProp_FundWKN;
   extern const BFDataFieldProperties s_FldProp_FundISIN;
   extern const BFDataFieldProperties s_FldProp_OverrideRepeats;
   extern const BFDataFieldProperties s_FldProp_BrokerCode;
   extern const BFDataFieldProperties s_FldProp_BranchCode;
   extern const BFDataFieldProperties s_FldProp_SalesRepCode;
   extern const BFDataFieldProperties s_FldProp_IgnoreFundLoadGrp;
   extern const BFDataFieldProperties s_FldProp_ExcludeClass;
   extern const BFDataFieldProperties s_FldProp_GetLastIDRate;
   extern const BFDataFieldProperties s_FldProp_GetTransType;
   extern const BFDataFieldProperties s_FldProp_GetNextAvailRate;
   extern const BFDataFieldProperties s_FldProp_CUSIP;
}


class dsi_DSTC0023_REQ : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0023_REQ();
   virtual ~dsi_DSTC0023_REQ();

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
   BFDataField* aFlds_[26];
   // Field Declarations
   BFTextField<200> FundCode_;
   BFTextField<120> ClassCode_;
   BFDateField FromDate_;
   BFDateField ToDate_;
   BFTextField_1 PrevDatePressed_;
   BFTextField_1 NextDatePressed_;
   BFTextField<100> NextKey_;
   BFTextField_60 SessionId_;
   BFTextField_60 User_Id_;
   BFTextField_60 LanguageCode_;
   BFTextField_60 CompanyId_;
   BFTextField_1 Track_;
   BFTextField_60 Activity_;
   BFTextField_60 SearchFundType_;
   BFTextField_60 FundWKN_;
   BFTextField_60 FundISIN_;
   BFNumericField OverrideRepeats_;
   BFTextField_60 BrokerCode_;
   BFTextField_60 BranchCode_;
   BFTextField_60 SalesRepCode_;
   BFTextField_1 IgnoreFundLoadGrp_;
   BFTextField_60 ExcludeClass_;
   BFTextField_1 GetLastIDRate_;
   BFTextField<30> GetTransType_;
   BFTextField<30> GetNextAvailRate_;
   BFTextField_60 CUSIP_;
};
