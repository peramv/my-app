#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AdvisorFee.hpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 26 December 2013
//
// ^CLASS    : AdvisorFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\MgmtFee.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
    #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
    #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AdvisorFee: virtual public MgmtFee
{
public:
    AdvisorFee(BFAbstractCBO &parent);
    virtual ~AdvisorFee();

protected:
    virtual SEVERITY doInit(const BFDataGroupId &idDataGroup);
    virtual void doInitWithDefaultValues(const BFDataGroupId &idDataGroup);
    virtual SEVERITY doValidateField(const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup);

    virtual SEVERITY validateFundClass(const DString &fundCode, 
                                       const DString &classCode, 
                                       const DString &accountNum, 
                                       const BFDataGroupId &idDataGroup);

    virtual SEVERITY transTypeRelatedChanges(const BFDataGroupId &idDataGroup);

private:
};