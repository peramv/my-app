// BFDataImpl header file for DataSet DSTC0419.VWRepeat_Record
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
   extern const BFTextFieldId ProdPortfolioPlanUUID;
   extern const BFTextFieldId PortfolioPlanCode;
   extern const BFTextFieldId PortfolioPlanName;
   extern const BFTextFieldId DefaultPlan;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_ProdPortfolioPlanUUID;
   extern const BFDataFieldProperties s_FldProp_PortfolioPlanCode;
   extern const BFDataFieldProperties s_FldProp_PortfolioPlanName;
   extern const BFDataFieldProperties s_FldProp_DefaultPlan;
}


class dsi_DSTC0419_VWRepeat_Record : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0419_VWRepeat_Record();
   virtual ~dsi_DSTC0419_VWRepeat_Record();

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
   BFTextField_60 ProdPortfolioPlanUUID_;
   BFTextField_60 PortfolioPlanCode_;
   BFTextField_60 PortfolioPlanName_;
   BFTextField_10 DefaultPlan_;

};
