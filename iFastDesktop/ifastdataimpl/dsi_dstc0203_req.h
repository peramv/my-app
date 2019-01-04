// BFDataImpl header file for DataSet DSTC0203.REQ
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
   extern const BFTextFieldId RunMode;
   extern const BFNumericFieldId AccountNum;
   extern const BFDateFieldId EffectiveDate;
   extern const BFNumericFieldId MinWithAge;
   extern const BFTextFieldId PenSourceLine1;
   extern const BFTextFieldId PenSourceLine2;
   extern const BFTextFieldId PenSourceLine3;
   extern const BFDecimalFieldId UniSexPer;
   extern const BFDecimalFieldId SexDistinctPer;
   extern const BFIntegerFieldId LIPPenInfoVer;
   extern const BFIntegerFieldId LIPPenInfoRid;
   extern const BFNumericFieldId ShrNum;
   extern const BFTextFieldId Track;
   extern const BFTextFieldId Activity;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_SessionId;
   extern const BFDataFieldProperties s_FldProp_User_Id;
   extern const BFDataFieldProperties s_FldProp_LanguageCode;
   extern const BFDataFieldProperties s_FldProp_CompanyId;
   extern const BFDataFieldProperties s_FldProp_RunMode;
   extern const BFDataFieldProperties s_FldProp_AccountNum;
   extern const BFDataFieldProperties s_FldProp_EffectiveDate;
   extern const BFDataFieldProperties s_FldProp_MinWithAge;
   extern const BFDataFieldProperties s_FldProp_PenSourceLine1;
   extern const BFDataFieldProperties s_FldProp_PenSourceLine2;
   extern const BFDataFieldProperties s_FldProp_PenSourceLine3;
   extern const BFDataFieldProperties s_FldProp_UniSexPer;
   extern const BFDataFieldProperties s_FldProp_SexDistinctPer;
   extern const BFDataFieldProperties s_FldProp_LIPPenInfoVer;
   extern const BFDataFieldProperties s_FldProp_LIPPenInfoRid;
   extern const BFDataFieldProperties s_FldProp_ShrNum;
   extern const BFDataFieldProperties s_FldProp_Track;
   extern const BFDataFieldProperties s_FldProp_Activity;
}


class dsi_DSTC0203_REQ : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0203_REQ();
   virtual ~dsi_DSTC0203_REQ();

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
   BFDataField* aFlds_[18];
   // Field Declarations
   BFTextField_60 SessionId_;
   BFTextField_60 User_Id_;
   BFTextField_60 LanguageCode_;
   BFTextField_60 CompanyId_;
   BFTextField_60 RunMode_;
   BFNumericField AccountNum_;
   BFDateField EffectiveDate_;
   BFNumericField MinWithAge_;
   BFTextField<40> PenSourceLine1_;
   BFTextField<40> PenSourceLine2_;
   BFTextField<40> PenSourceLine3_;
   BFDecimalField UniSexPer_;
   BFDecimalField SexDistinctPer_;
   BFIntegerField LIPPenInfoVer_;
   BFIntegerField LIPPenInfoRid_;
   BFNumericField ShrNum_;
   BFTextField_1 Track_;
   BFTextField_60 Activity_;

};
