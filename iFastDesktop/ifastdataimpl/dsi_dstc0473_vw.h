// BFDataImpl header file for DataSet DSTC0473.VW
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, November 04, 2016 11:42:13


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
    extern const BFNumericFieldId RepeatCount;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_RepeatCount;
}


class dsi_DSTC0473_VW : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0473_VW();
    virtual ~dsi_DSTC0473_VW();

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
    BFDataField* aFlds_[1];
    // Field Declarations
    BFNumericField RepeatCount_;
};
