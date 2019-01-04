#pragma once



//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntityRegDetails.hpp
// ^AUTHOR : 
// ^DATE   : 09 January 2014
//
// ^CLASS    : EntityRegDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

class BFData;
class MgmtCoOptions;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE EntityRisk : public MFCanBFCbo, private boost::noncopyable
{
public:
    EntityRisk (BFAbstractCBO &parent);
    virtual ~EntityRisk();
    SEVERITY init (const BFData &data); 
    SEVERITY initNew (const BFDataGroupId &idDataGroup);
    void setAllFieldReadOnly(bool isReadonly, const BFDataGroupId &idDataGroup);
    bool effectiveDateApplicable(const BFDataGroupId &idDataGroup);

protected:
    virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
    virtual SEVERITY doValidateField(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
    virtual SEVERITY doApplyRelatedChanges(const BFFieldId &idField, const BFDataGroupId &idDataGroup);
    virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);

private:
    void initializeSubstitutionList(const BFFieldId& idField, 
                                    const DString &dstrGroupCode, 
                                    const BFDataGroupId& idDataGroup);
    void updateEntityRisk(const BFDataGroupId& idDataGroup);

    SEVERITY commonInit(const BFDataGroupId &idDataGroup);
};