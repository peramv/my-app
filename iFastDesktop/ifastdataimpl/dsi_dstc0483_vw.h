// BFDataImpl header file for DataSet DSTC0483.VW
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, January 19, 2018 09:37:30


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
    extern const BFTextFieldId MoreAvailable;
    extern const BFTextFieldId AMSCode;
    extern const BFNumericFieldId AccountNum;
    extern const BFDateFieldId EffectiveDate;
    extern const BFTextFieldId Status;
    extern const BFDateFieldId ProcessDate;
    extern const BFTextFieldId Username;
    extern const BFTextFieldId AMSDeltaRequestUUID;
    extern const BFNumericFieldId RepeatCount;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_MoreAvailable;
    extern const BFDataFieldProperties s_FldProp_AMSCode;
    extern const BFDataFieldProperties s_FldProp_AccountNum;
    extern const BFDataFieldProperties s_FldProp_EffectiveDate;
    extern const BFDataFieldProperties s_FldProp_Status;
    extern const BFDataFieldProperties s_FldProp_ProcessDate;
    extern const BFDataFieldProperties s_FldProp_Username;
    extern const BFDataFieldProperties s_FldProp_AMSDeltaRequestUUID;
    extern const BFDataFieldProperties s_FldProp_RepeatCount;
}


class dsi_DSTC0483_VW : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0483_VW();
    virtual ~dsi_DSTC0483_VW();

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
    BFDataField* aFlds_[9];
    // Field Declarations
    BFTextField_1 MoreAvailable_;
    BFTextField_60 AMSCode_;
    BFNumericField AccountNum_;
    BFDateField EffectiveDate_;
    BFTextField_60 Status_;
    BFDateField ProcessDate_;
    BFTextField_60 Username_;
    BFTextField_60 AMSDeltaRequestUUID_;
    BFNumericField RepeatCount_;
};
