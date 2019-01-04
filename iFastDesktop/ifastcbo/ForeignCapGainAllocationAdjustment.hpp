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
// ^FILE   : ForeignCapGainAllocationAdjustment.hpp
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : ForeignCapGainAllocationAdjustment
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\ManualDividendAdjustment.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ForeignCapGainAllocationAdjustment : public ManualDividendAdjustment
{
public:
    ForeignCapGainAllocationAdjustment (BFAbstractCBO &parent);
    virtual ~ForeignCapGainAllocationAdjustment();

protected:
    virtual SEVERITY doValidateField(const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup);
    virtual void doInitWithDefaultValues(const BFDataGroupId &idDataGroup);
    virtual SEVERITY doInit(const BFDataGroupId &idDataGroup);
    virtual SEVERITY doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup);

    virtual SEVERITY validateFundClass(const DString &fundCode, 
                                       const DString &classCode, 
                                       const DString &accountNum, 
                                       const BFDataGroupId &idDataGroup);

    virtual SEVERITY validateToFundClass(const DString &fundCode, 
                                         const DString &classCode, 
                                         const DString &accountNum, 
                                         const BFDataGroupId &idDataGroup);

    virtual SEVERITY validateFromToFundClass(const DString &fromCode,
                                             const DString &fromClass,
                                             const DString &toCode,
                                             const DString &toClass,
                                             const BFDataGroupId &idDataGroup);

    virtual void setDefaultEffectiveDate(const BFDataGroupId &idDataGroup);
    virtual void setDefaultToFundClass(const BFDataGroupId &idDataGroup);
    virtual bool isReinvestmentRateRequired();

    //Returned value is not rounded yet.
    virtual BigDecimal calculateNumUnitDividendsFromAmount(const BFDataGroupId &idDataGroup);

private:

};
