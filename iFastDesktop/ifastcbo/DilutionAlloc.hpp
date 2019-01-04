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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DilutionAlloc.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : DilutionAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

//
#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IntermediaryList;
class Broker;
class TransactionList;

class IFASTCBO_LINKAGE DilutionAlloc : public MFCanBFCbo, private boost::noncopyable
{
public:
   DilutionAlloc( BFAbstractCBO &parent );
   virtual ~DilutionAlloc();
   SEVERITY init (const BFData& data);
   SEVERITY initNew (const BFDataGroupId& idDataGroup); //for creating new object
   SEVERITY initNew (const BFData& data, const BFDataGroupId& idDataGroup); // clone
   void setFieldsReadOnly (const BFDataGroupId& idDataGroup, bool bReadOnly);   
   SEVERITY setRespDateInvalid (const BFDataGroupId& idDataGroup);
   SEVERITY setTradeDateToRespDate ( const DString &tradeDate, 
                                     const BFDataGroupId &idDataGroup);
SEVERITY refreshNSMEligibility(const BFFieldId& idField, const BFDataGroupId& idDataGroup);
protected:
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );   
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup);
private:
   SEVERITY validatePercent (const BFDataGroupId& idDataGroup);
   SEVERITY validateAccountability ( const DString &dstrAccountableCode, 
                                     const BFDataGroupId &idDataGroup);
   SEVERITY validateBillingToEntityDilutionNSMXEdit( const BFDataGroupId &idDataGroup);
   SEVERITY validateDilutionNSM(const BFDataGroupId &idDataGroup);
   SEVERITY validateAssociatedAcctNum (const DString &dstrAssociatedAcctNum, const BFDataGroupId& idDataGroup);
   SEVERITY checkAccountStatus (const DString &dstrAssociatedAcctNum, const BFDataGroupId& idDataGroup);
   SEVERITY loadIntermCodeSubstitutionList( const BFDataGroupId& idDataGroup );
   SEVERITY setBrokerName( const DString &brokerCode, const BFDataGroupId &idDataGroup);
   SEVERITY getBroker ( Broker *&pBroker, const BFDataGroupId &idDataGroup);
   SEVERITY billingToEntityReleatedChanges( const DString &billingToEntityType,
                                            const BFDataGroupId &idDataGroup);

   SEVERITY loadBillToEntityTypeSubstList (const BFDataGroupId &idDataGroup);
   SEVERITY billingToEntityFieldsReleatedChanges(const BFDataGroupId &idDataGroup);
   void  CommInit(const BFData* pData,const BFDataGroupId& idDataGroup);
   
   SEVERITY refreshIsDilutionNSMEligible (DString& eligibility, const BFDataGroupId &idDataGroup);

   DString getAdjTransNum(const BFDataGroupId& idDataGroup);

   IntermediaryList* _pIntermediaryList;
   DString           dstrInterCodesList;
   bool              bInitNewWithDataSet_;
};
