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
// ^FILE   : ManualDividendAdjustment.hpp
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : ManualDividendAdjustment
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\ManualDividend.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ManualDividendAdjustment : public ManualDividend
{
public:
    ManualDividendAdjustment (BFAbstractCBO &parent);
    virtual ~ManualDividendAdjustment();

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
    SEVERITY validateCurrencyTaxType (const DString &accountNum, 
                                      const DString &currency, 
                                      const BFDataGroupId &idDataGroup);

    virtual SEVERITY validateEffectiveDateAgainstIDRecord(const BFDataGroupId &idDataGroup);
    virtual SEVERITY validateNegMoneyMktInt(const DString &strValue, const BFDataGroupId &idDataGroup, const bool &addConditions = true);
    virtual SEVERITY validateESGSettle (const DString &strValue, const BFDataGroupId &idDataGroup);
    virtual SEVERITY doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup);
    virtual void setDefaultEffectiveDate(const BFDataGroupId &idDataGroup);
    virtual void setDefaultToFundClass(const BFDataGroupId &idDataGroup);
    virtual void updateReinvestmentRateForCash(const BFDataGroupId &idDataGroup);

    //Derive classes should implement its own below medthod if rate is not required.
    virtual bool isDivRateRequired();
    virtual bool isReinvestmentRateRequired();

    //Returned value is not rounded yet.
    virtual BigDecimal calculateAmount(const DString &calculateFrom, const BFDataGroupId &idDataGroup);
    virtual BigDecimal calculateNumUnitDividendsFromAmount(const BFDataGroupId &idDataGroup);
    virtual BigDecimal calculateNumUnitEligDividendsFromAmount(const BFDataGroupId &idDataGroup);

    virtual void getDivRate(BigDecimal &dDivRate, DString &strUnitId, const BFDataGroupId &idDataGroup, const DString &getTransType = NULL_STRING, const DString &getNextAvailRate = I_("N"));
    virtual void getReinvestmentRate(BigDecimal &dReinvestmentRate, DString &strUnitId, const BFDataGroupId &idDataGroup);
    virtual void getAVRateFromFundFromClass(BigDecimal &dAVRate, DString &strUnitId, const BFDataGroupId &idDataGroup);
    virtual void getAVRate(const DString &dstrFund,const DString &dstrClass, const DString &dstrTradeDate, BigDecimal &dAVRate, DString &strUnitId, const BFDataGroupId &idDataGroup);
    
    DString getRoundedValue(const DString &precisionField, const DString &value, const BFDataGroupId &idDataGroup);
    SEVERITY validateAccountHolding(const DString &fundCode, const DString &classCode, const BFDataGroupId &idDataGroup);
    SEVERITY validateFundCategory(const DString &fundCode, const BFDataGroupId &idDataGroup);
    SEVERITY validateAddrCode(const BFDataGroupId &idDataGroup);
    SEVERITY validateAcctBalanceForNegMoneyMkt(const BFDataGroupId &idDataGroup);
    bool isRoundCalToCents(const BFDataGroupId &idDataGroup);
    bool isFoundActiveAddrCode(const DString &searchAddrCode, const BFDataGroupId &idDataGroup);
    void updateRates(const BFDataGroupId &idDataGroup);
    SEVERITY addressRelatedChanges (const BFDataGroupId &idDataGroup);
    
public:
    bool isCASHSettleESGElig(const BFDataGroupId & idDataGroup);

    virtual SEVERITY setField ( const BFFieldId &idField, 
                               const DString &dstrValue,
                               const BFDataGroupId &idDataGroup, 
                               bool bFormatted = true, 
                               bool bSideEffect = false, 
                               bool bCheckCurrentValue = true);

   virtual void getField ( const BFFieldId &idField, 
                           DString &fieldValue, 
                           const BFDataGroupId &idDataGroup, 
                           bool formattedReturn = false) const;
   
private:

};
