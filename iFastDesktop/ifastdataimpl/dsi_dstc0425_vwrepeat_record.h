// BFDataImpl header file for DataSet DSTC0425.VWRepeat_Record
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
   extern const BFTextFieldId InvHisIncomeUUID;
   extern const BFDateFieldId InvHisIntDate;
   extern const BFDecimalFieldId InvHisIntAmt;
   extern const BFTextFieldId InvestStatus1;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_InvHisIncomeUUID;
   extern const BFDataFieldProperties s_FldProp_InvHisIntDate;
   extern const BFDataFieldProperties s_FldProp_InvHisIntAmt;
   extern const BFDataFieldProperties s_FldProp_InvestStatus1;
}


class dsi_DSTC0425_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0425_VWRepeat_Record();
   virtual ~dsi_DSTC0425_VWRepeat_Record();

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
   BFDataField* aFlds_[4];
   // Field Declarations
   BFTextField<50> InvHisIncomeUUID_;
   BFDateField InvHisIntDate_;
   BFDecimalField InvHisIntAmt_;
   BFTextField_60 InvestStatus1_;

};
