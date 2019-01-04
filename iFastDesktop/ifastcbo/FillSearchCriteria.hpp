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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : FillSearchCriteria.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : June 2003
//
// ^CLASS     : FillSearchCriteria
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class FundClassRules;

class IFASTCBO_LINKAGE FillSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:
   FillSearchCriteria (BFAbstractCBO &parent);
   virtual ~FillSearchCriteria();

   SEVERITY init (
      const DString &fillSearchType, 
      const BFDataGroupId &idDataGroup);
   bool isBFSearchCriteria1Broker (
      const BFDataGroupId &idDataGroup);
   bool isBFSearchCriteria2Branch (
      const BFDataGroupId &idDataGroup);
   bool isBFSearchCriteria3SlsRep (
      const BFDataGroupId &idDataGroup);
   bool isFISearchCriteria1Name (
      const BFDataGroupId &idDataGroup);
   bool isFISearchCriteria3Name (
      const BFDataGroupId &idDataGroup);
   bool isFISearchCriteria3Code (
      const BFDataGroupId &idDataGroup);
   bool isDTFSearchCriteria2EffectiveDate (
      const BFDataGroupId &idDataGroup);
   bool isDTFSearchCriteria2FundCode (
      const BFDataGroupId &idDataGroup);
   bool isDTFSearchCriteria3ClassCode (
      const BFDataGroupId &idDataGroup);
//types of searches
   bool isFIFeaturesSearch (
      const BFDataGroupId &idDataGroup);
   bool isFIFeaturesF4Search (
      const BFDataGroupId &idDataGroup);
   bool isBrokersFeaturesSearch (
      const BFDataGroupId &idDataGroup);
   bool isMainSearch (
      const BFDataGroupId &idDataGroup);
   bool isDTFSearch (
      const BFDataGroupId &idDataGroup);
   
   bool isFMSearchCriteriaSponsor( const BFDataGroupId &idDataGroup );
   bool isFMSearchCriteriaFeeModel( const BFDataGroupId &idDataGroup );
   bool isFMSearchCriteriaFundBrokerCode( const BFDataGroupId &idDataGroup );
   bool isFMSearchCriteriaFundBrokerName( const BFDataGroupId &idDataGroup );

	bool isFMSearchCriteriaAggregatedOrder( const BFDataGroupId &idDataGroup );

   bool isFMSearchCriteriaAggregationTradeDate( const BFDataGroupId &idDataGroup );
   bool isFMSearchCriteriaAggregationAggrOrdNo( const BFDataGroupId &idDataGroup );
   bool isFMSearchCriteriaAggregationRoutRefNo( const BFDataGroupId &idDataGroup );
   bool isFMSearchCriteriaAggregationStatus( const BFDataGroupId &idDataGroup );
protected:
   SEVERITY doValidateField (
      const BFFieldId &idField, 
      const DString &strValue, 
      const BFDataGroupId &idDataGroup);
   SEVERITY doApplyRelatedChanges (
      const BFFieldId &idField, 
      const BFDataGroupId &idDataGroup);
private:
   SEVERITY assignSearchLabels (
      const BFDataGroupId &idDataGroup);
   SEVERITY assignFISearchLabel3 (   
      const BFDataGroupId &idDataGroup);
   SEVERITY setFirstSubstCode (
      const BFFieldId &idSubstField, 
      const BFDataGroupId &idDataGroup);
   SEVERITY setHowManySearchCriterias (
      const DString &searchUsingCode,
      const BFDataGroupId &idDataGroup);
   SEVERITY checkUAFForSearchCriteria (
      DString &newSubstList, 
      const BFFieldId &idSubstField, 
      const BFDataGroupId &idDataGroup);
   SEVERITY checkSecurityAndSetSubstituteValuesForField (
      const BFFieldId &idField, 
      const BFFieldId &idSubstField, 
      const BFDataGroupId &idDataGroup);
   SEVERITY setDefaultBankTypeToSearchCriteria2 (
      const BFDataGroupId &idDataGroup);
   SEVERITY setCurrentBussinessDateToSearchCriteria2 (
      const BFDataGroupId &idDataGroup);
   SEVERITY FundSponsorFeeModelUsingRelatedChanges( 
      const BFDataGroupId& idDataGroup );
   SEVERITY ValidateModelCode( const BFDataGroupId& idDataGroup, const DString& dstrValue);
   SEVERITY FundBrokerCodeUsingRelatedChanges( 
      const BFDataGroupId& idDataGroup );

	SEVERITY AggregatedOrderUsingTradeDateRelatedChanges( 
      const BFDataGroupId& idDataGroup );

	SEVERITY AggregatedOrderUsingAggrOrdNoRelatedChanges( 
      const BFDataGroupId& idDataGroup );

	SEVERITY AggregatedOrderUsingRoutRefNoRelatedChanges( 
      const BFDataGroupId& idDataGroup );

	SEVERITY AggregatedOrderUsingStatusRelatedChanges( 
      const BFDataGroupId& idDataGroup );

   std::map<DString, DString> _mpermissions;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FillSearchCriteria.hpp-arc  $
//
//   Rev 1.8   Nov 26 2004 14:42:12   zhangcel
//PET1117/FN8 -- Aggregated Order related changes
//
//   Rev 1.7   Nov 14 2004 14:40:48   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Oct 19 2004 14:39:24   FENGYONG
//PET1117 FN54 - Fund Broker Static
//
//   Rev 1.5   Aug 10 2004 11:24:30   FENGYONG
//PET 1117 FN 5 - Client condition Fee
//
//   Rev 1.4   Feb 03 2004 16:29:26   VADEANUM
//PET 859 FN23 - ADL - removed Fee search param
//
//   Rev 1.3   Jan 28 2004 21:35:20   popescu
//PET 859, FN 23, modified resources (dialogs and menu item) and coded for the features search dialog
//
//   Rev 1.2   Oct 04 2003 15:59:26   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.1   Jul 23 2003 14:08:56   popescu
//Added security checking to payment instructions and pay to entity screens
//
//   Rev 1.0   Jun 27 2003 18:16:48   popescu
//Initial revision.
 */