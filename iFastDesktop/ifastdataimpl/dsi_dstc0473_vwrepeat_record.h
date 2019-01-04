// BFDataImpl header file for DataSet DSTC0473.VWRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, November 04, 2016 11:49:47


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
    extern const BFTextFieldId RegTransferMstrUUID;
    extern const BFTextFieldId RegTransferAllocUUID;
    extern const BFTextFieldId FundCode;
    extern const BFTextFieldId ClassCode;
    extern const BFDecimalFieldId AllocAmount;
    extern const BFDecimalFieldId Version;
    extern const BFDateFieldId ModDate;
    extern const BFTextFieldId ModUser;
    extern const BFDateFieldId ProcessDate;
    extern const BFTextFieldId Username;
    extern const BFDecimalFieldId Commission;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_RegTransferMstrUUID;
    extern const BFDataFieldProperties s_FldProp_RegTransferAllocUUID;
    extern const BFDataFieldProperties s_FldProp_FundCode;
    extern const BFDataFieldProperties s_FldProp_ClassCode;
    extern const BFDataFieldProperties s_FldProp_AllocAmount;
    extern const BFDataFieldProperties s_FldProp_Version;
    extern const BFDataFieldProperties s_FldProp_ModDate;
    extern const BFDataFieldProperties s_FldProp_ModUser;
    extern const BFDataFieldProperties s_FldProp_ProcessDate;
    extern const BFDataFieldProperties s_FldProp_Username;
    extern const BFDataFieldProperties s_FldProp_Commission;
}


class dsi_DSTC0473_VWRepeat_Record : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0473_VWRepeat_Record();
    virtual ~dsi_DSTC0473_VWRepeat_Record();

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
    BFDataField* aFlds_[11];
    // Field Declarations
    BFTextField_60 RegTransferMstrUUID_;
    BFTextField_60 RegTransferAllocUUID_;
    BFTextField<200> FundCode_;
    BFTextField<120> ClassCode_;
    BFDecimalField AllocAmount_;
    BFDecimalField Version_;
    BFDateField ModDate_;
    BFTextField_60 ModUser_;
    BFDateField ProcessDate_;
    BFTextField_60 Username_;
    BFDecimalField Commission_;
};
