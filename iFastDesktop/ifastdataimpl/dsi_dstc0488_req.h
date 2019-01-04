// BFDataImpl header file for DataSet DSTC0488.REQ
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Thursday, August 30, 2018 11:10:05


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
    extern const BFTextFieldId Track;
    extern const BFTextFieldId Activity;
    extern const BFNumericFieldId AccountNum;
    extern const BFNumericFieldId TransNum;
    extern const BFTextFieldId TransType;

    //Property Externs
    extern const BFDataFieldProperties s_FldProp_SessionId;
    extern const BFDataFieldProperties s_FldProp_User_Id;
    extern const BFDataFieldProperties s_FldProp_LanguageCode;
    extern const BFDataFieldProperties s_FldProp_CompanyId;
    extern const BFDataFieldProperties s_FldProp_Track;
    extern const BFDataFieldProperties s_FldProp_Activity;
    extern const BFDataFieldProperties s_FldProp_AccountNum;
    extern const BFDataFieldProperties s_FldProp_TransNum;
    extern const BFDataFieldProperties s_FldProp_TransType;
}


class dsi_DSTC0488_REQ : public BFDataImpl 
{
public:
    // Constructors
    dsi_DSTC0488_REQ();
    virtual ~dsi_DSTC0488_REQ();

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
    BFTextField_60 SessionId_;
    BFTextField_60 User_Id_;
    BFTextField_60 LanguageCode_;
    BFTextField_60 CompanyId_;
    BFTextField_1 Track_;
    BFTextField_60 Activity_;
    BFNumericField AccountNum_;
    BFNumericField TransNum_;
    BFTextField_60 TransType_;
};
