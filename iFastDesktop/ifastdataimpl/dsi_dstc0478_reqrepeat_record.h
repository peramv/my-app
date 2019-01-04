// BFDataImpl header file for DataSet DSTC0478.REQRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Wednesday, April 19, 2017 06:12:23


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
    extern const BFTextFieldId RunMode;
    extern const BFTextFieldId RiskLevel;
    extern const BFTextFieldId CountryOfExposure;
    extern const BFTextFieldId RiskDetlUUID;
    extern const BFDateFieldId EffectiveDate;
    extern const BFDateFieldId StopDate;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_RunMode;
    extern const BFDataFieldProperties s_FldProp_RiskLevel;
    extern const BFDataFieldProperties s_FldProp_CountryOfExposure;
    extern const BFDataFieldProperties s_FldProp_RiskDetlUUID;
    extern const BFDataFieldProperties s_FldProp_EffectiveDate;
    extern const BFDataFieldProperties s_FldProp_StopDate;
}


class dsi_DSTC0478_REQRepeat_Record : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0478_REQRepeat_Record();
    virtual ~dsi_DSTC0478_REQRepeat_Record();

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
    BFDataField* aFlds_[6];
    // Field Declarations
    BFTextField_60 RunMode_;
    BFTextField_60 RiskLevel_;
    BFTextField_6 CountryOfExposure_;
    BFTextField_60 RiskDetlUUID_;
    BFDateField EffectiveDate_;
    BFDateField StopDate_;
};
