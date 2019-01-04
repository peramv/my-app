// BFDataImpl header file for DataSet DSTC0486.VWRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Monday, July 02, 2018 11:08:31


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
    extern const BFDecimalFieldId RejErrNum;
    extern const BFTextFieldId RejFundCode;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_RejErrNum;
    extern const BFDataFieldProperties s_FldProp_RejFundCode;
}


class dsi_DSTC0486_VWRepeat_Record : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0486_VWRepeat_Record();
    virtual ~dsi_DSTC0486_VWRepeat_Record();

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
    BFDataField* aFlds_[2];
    // Field Declarations
    BFDecimalField RejErrNum_;
    BFTextField_60 RejFundCode_;
};
