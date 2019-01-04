// BFDataImpl header file for DataSet DSTC0448.VWRepeat_Record
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
   extern const BFNumericFieldId EntityId;
   extern const BFTextFieldId WhereUseKey;
   extern const BFTextFieldId HoldingCompName;
   extern const BFDateFieldId Deff;
   extern const BFDateFieldId StopDate;
   extern const BFTextFieldId AggregationMethod;
   extern const BFDateFieldId ProcessDate;
   extern const BFTextFieldId Username;
   extern const BFDateFieldId ModDate;
   extern const BFTextFieldId ModUser;
   extern const BFTextFieldId GBCD;
   extern const BFTextFieldId CompanyUsage;
   extern const BFTextFieldId Language;
   extern const BFNumericFieldId EntityWhereUseRid;
   extern const BFIntegerFieldId EntityWhereUseVer;
   extern const BFTextFieldId FeeModelExist;
   extern const BFTextFieldId FeeAggregationExist;
   extern const BFTextFieldId BillingInstrExist;
   extern const BFTextFieldId ReportGroupExist;
   extern const BFDateFieldId FirstChildRecDeff;
   extern const BFDateFieldId ShrAcctLastProcDate;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_EntityId;
   extern const BFDataFieldProperties s_FldProp_WhereUseKey;
   extern const BFDataFieldProperties s_FldProp_HoldingCompName;
   extern const BFDataFieldProperties s_FldProp_Deff;
   extern const BFDataFieldProperties s_FldProp_StopDate;
   extern const BFDataFieldProperties s_FldProp_AggregationMethod;
   extern const BFDataFieldProperties s_FldProp_ProcessDate;
   extern const BFDataFieldProperties s_FldProp_Username;
   extern const BFDataFieldProperties s_FldProp_ModDate;
   extern const BFDataFieldProperties s_FldProp_ModUser;
   extern const BFDataFieldProperties s_FldProp_GBCD;
   extern const BFDataFieldProperties s_FldProp_CompanyUsage;
   extern const BFDataFieldProperties s_FldProp_Language;
   extern const BFDataFieldProperties s_FldProp_EntityWhereUseRid;
   extern const BFDataFieldProperties s_FldProp_EntityWhereUseVer;
   extern const BFDataFieldProperties s_FldProp_FeeModelExist;
   extern const BFDataFieldProperties s_FldProp_FeeAggregationExist;
   extern const BFDataFieldProperties s_FldProp_BillingInstrExist;
   extern const BFDataFieldProperties s_FldProp_ReportGroupExist;
   extern const BFDataFieldProperties s_FldProp_FirstChildRecDeff;
   extern const BFDataFieldProperties s_FldProp_ShrAcctLastProcDate;
}


class dsi_DSTC0448_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0448_VWRepeat_Record();
   virtual ~dsi_DSTC0448_VWRepeat_Record();

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
   BFDataField* aFlds_[21];
   // Field Declarations
   BFNumericField EntityId_;
   BFTextField_10 WhereUseKey_;
   BFTextField<80> HoldingCompName_;
   BFDateField Deff_;
   BFDateField StopDate_;
   BFTextField<20> AggregationMethod_;
   BFDateField ProcessDate_;
   BFTextField_60 Username_;
   BFDateField ModDate_;
   BFTextField_60 ModUser_;
   BFTextField_1 GBCD_;
   BFTextField<30> CompanyUsage_;
   BFTextField_60 Language_;
   BFNumericField EntityWhereUseRid_;
   BFIntegerField EntityWhereUseVer_;
   BFTextField_10 FeeModelExist_;
   BFTextField_10 FeeAggregationExist_;
   BFTextField_10 BillingInstrExist_;
   BFTextField_10 ReportGroupExist_;
   BFDateField FirstChildRecDeff_;
   BFDateField ShrAcctLastProcDate_;

};
