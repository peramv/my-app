//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
//    ^FILE   : FillSearchCriteria.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : June 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : FillSearchCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "fillsearchcriteria.hpp"
#include "agent.hpp"
#include "agentlist.hpp"
#include "branch.hpp"
#include "branchlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "financialinstitution.hpp"
#include "mgmtco.hpp"
#include "FundSponsorsList.hpp"

#include "FundBrokerList.hpp"  //59F
#include "AggregatedOrderList.hpp"
#include "FeeModelList.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_("FillSearchCriteria");
   const I_CHAR * const LABEL1_MNEMONIC = I_("L1");
   const I_CHAR * const LABEL2_MNEMONIC = I_("L2");
   const I_CHAR * const LABEL3_MNEMONIC = I_("L3");
   const I_CHAR * const LABEL4_MNEMONIC = I_("L4");
	const I_CHAR * const LABEL5_MNEMONIC = I_("L5");
	const I_CHAR * const LABEL6_MNEMONIC = I_("L6");
	const I_CHAR * const LABEL7_MNEMONIC = I_("L7");

   const I_CHAR * const COMMA = I_(",");
   const I_CHAR * const OTHER = I_("07");
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND_CLASS_CODES;
	extern const long ERR_FUND_CLASS_MUST_BOTH_BE_BLANK;
   extern const long ERR_FEEMODEL_CODE_NOT_SETUP;
   extern const long ERR_FEEMODEL_CODE_NOT_ACTIVE;
   extern const long ERR_FUND_BROKER_CODE_IS_EMPTY;
   extern const long ERR_FUND_BROKER_CODE_NOT_EXISTING;
}

namespace ifds
{
   //field ids used
   //search criteria subst sets
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesSearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesF4SearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId MainSearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId BrokerFeaturesSearchCriteria;   
   extern CLASS_IMPORT const BFTextFieldId DTFFeaturesSearchCriteria;

   extern CLASS_IMPORT const BFTextFieldId FundSponsorFeeModelSearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId FundSponsorFeeModelUsing;
   extern CLASS_IMPORT const BFTextFieldId FundSponsorFeeModelLabel;
   extern CLASS_IMPORT const BFTextFieldId FundSponsorFeeModelSearchCriteriaNo;
   //using subst sets
 //59F
   extern CLASS_IMPORT const BFTextFieldId FundBrokerSearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId FundBrokerUsing;
   extern CLASS_IMPORT const BFTextFieldId FundBrokerLabel;
   extern CLASS_IMPORT const BFTextFieldId FundBrokerSearchCriteriaNo;

   // AggregatedOrder
   extern CLASS_IMPORT const BFTextFieldId AggregateSearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId AggregateSearchUsing;
   extern CLASS_IMPORT const BFTextFieldId AggregateSearchLabel;
   extern CLASS_IMPORT const BFTextFieldId AggregateSearchCriteriaNo; 


   //broker features
   extern CLASS_IMPORT const BFTextFieldId BrokerFeaturesSearchPayToEntityUsing;
   extern CLASS_IMPORT const BFTextFieldId BrokerFeaturesSearchPaymentInstructionsUsing;
   extern CLASS_IMPORT const BFTextFieldId BrokerFeaturesSearchBankingUsing;
   extern CLASS_IMPORT const BFTextFieldId BrokerFeaturesSearchHistoricalInfoUsing;
   //fi features
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesSearchInstitutionsUsing;
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesF4SearchInstitutionsUsing;
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesSearchTransitsUsing;
   //dtf features
   extern CLASS_IMPORT const BFTextFieldId DTFFeaturesSearchDailyTransactionsFeesUsing;
   //labels subst set
   extern CLASS_IMPORT const BFTextFieldId MainSearchLabels;
   extern CLASS_IMPORT const BFTextFieldId BrokerFeaturesSearchLabels;
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesSearchLabels;
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesF4SearchLabels;
   extern CLASS_IMPORT const BFTextFieldId DTFFeaturesSearchLabels;
   extern CLASS_IMPORT const BFTextFieldId FinancialInstitutionsCodeLabel;

   //number of search criterias
   extern CLASS_IMPORT const BFTextFieldId MainSearchCriteriaNo;
   extern CLASS_IMPORT const BFTextFieldId BrokerFeaturesSearchCriteriaNo;
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesSearchCriteriaNo;
   extern CLASS_IMPORT const BFTextFieldId FIFeaturesF4SearchCriteriaNo;
   extern CLASS_IMPORT const BFTextFieldId DTFFeaturesSearchCriteriaNo;

   //helper fields
   extern CLASS_IMPORT const BFTextFieldId SearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId SearchUsing;
   extern CLASS_IMPORT const BFTextFieldId SearchLabels;
   extern CLASS_IMPORT const BFTextFieldId FillSearchType;
   //label fields
   extern CLASS_IMPORT const BFTextFieldId SearchLabel1;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel2;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel3;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel4;
	extern CLASS_IMPORT const BFTextFieldId SearchLabel5;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel6;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel7;
   //criteria fields
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria1;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria2;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria3;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria4;
	extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria5;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria6;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria7;
   //should change the name of the field
   extern CLASS_IMPORT const BFTextFieldId HowManySearchCriterias;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   //substitutions sets fillers
   //for FI_FEATURES (search criteria)
   extern CLASS_IMPORT const BFTextFieldId FinancialInstitutionsCategoryForSearch;
   //for FI_FEATURES_F4 (search criteria 1)
   extern CLASS_IMPORT const BFTextFieldId FinancialInstitutionsCategory;
   extern CLASS_IMPORT const BFTextFieldId BankIdType;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankType;
   //for DTF search
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId DTFSearchFeeCode;
   extern CLASS_IMPORT const BFTextFieldId DTFSearchRecordType;
	extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;

   extern CLASS_IMPORT const BFTextFieldId FundBrokerCode;   //59F
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate; 

	extern CLASS_IMPORT const BFDateFieldId FromDate; 
	extern CLASS_IMPORT const BFDateFieldId ToDate;
	extern CLASS_IMPORT const BFTextFieldId rxOrdStatus;
	extern CLASS_IMPORT const BFTextFieldId FundBroker;
	extern CLASS_IMPORT const BFTextFieldId FundCode;
	extern CLASS_IMPORT const BFTextFieldId FundWKN;
	extern CLASS_IMPORT const BFTextFieldId FundISIN;
	extern CLASS_IMPORT const BFTextFieldId RoutingRef;
	extern CLASS_IMPORT const BFTextFieldId OmnibusID;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,        State Flags,       Group Flags 
   { ifds::SearchCriteria,          BFCBO::REQUIRED,  0 }, 
   { ifds::SearchUsing,             BFCBO::REQUIRED,  0 }, 
   { ifds::SearchLabels,            BFCBO::REQUIRED,  0 }, 
   { ifds::FillSearchType,          BFCBO::REQUIRED,  0 }, 
   { ifds::SearchLabel1,            BFCBO::NONE,      0 }, 
   { ifds::SearchLabel2,            BFCBO::NONE,      0 }, 
   { ifds::SearchLabel3,            BFCBO::NONE,     0 }, 
   { ifds::SearchLabel4,            BFCBO::NONE,     0 }, 
	{ ifds::SearchLabel5,            BFCBO::NONE,      0 }, 
   { ifds::SearchLabel6,            BFCBO::NONE,     0 }, 
   { ifds::SearchLabel7,            BFCBO::NONE,     0 }, 
   { ifds::SearchFieldCriteria1,    BFCBO::NONE,     0 }, 
   { ifds::SearchFieldCriteria2,    BFCBO::NONE,     0 }, 
   { ifds::SearchFieldCriteria3,    BFCBO::NONE,     0 }, 
   { ifds::SearchFieldCriteria4,    BFCBO::NONE,     0 }, 
	{ ifds::SearchFieldCriteria5,    BFCBO::NONE,     0 }, 
   { ifds::SearchFieldCriteria6,    BFCBO::NONE,     0 }, 
   { ifds::SearchFieldCriteria7,    BFCBO::NONE,     0 }, 
   { ifds::HowManySearchCriterias,  BFCBO::NONE,     0 }, 
   { ifds::FundClass,               BFCBO::NONE,     0 }, 
	{ ifds::FromDate,                BFCBO::NONE,     0 },
	{ ifds::ToDate,                  BFCBO::NONE,     0 },
};

static const int NUM_FIELDS = sizeof ( classFieldInfo ) / sizeof ( BFCBO::CLASS_FIELD_INFO );

namespace SEARCH_TYPE
{
   extern CLASS_EXPORT I_CHAR * const MAIN = I_("Main");
   extern CLASS_EXPORT I_CHAR * const BROKER_FEATURES = I_("Broker Features");
   extern CLASS_EXPORT I_CHAR * const FI_FEATURES = I_("FI Features");
   extern CLASS_EXPORT I_CHAR * const FI_FEATURES_F4 = I_("FI Features F4");
   extern CLASS_EXPORT I_CHAR * const DAILY_TRANSACTIONS_FEES = I_("Daily Transactions Fees");
   extern CLASS_EXPORT I_CHAR * const FUNSSPONSORFEEMODEL = I_("FundSponsor Fee Model");
   extern CLASS_EXPORT I_CHAR * const SYSTEM = I_("System");
   extern CLASS_EXPORT I_CHAR * const FUNDBROKER = I_("Fund Broker");
	extern CLASS_EXPORT I_CHAR * const AGGREGATEDORDER = I_("AggregatedOrders");
}

namespace BF_SEARCH_CRITERIA
{
   //payment instructions
   extern CLASS_EXPORT I_CHAR * const PAY_TO_ENTITY            = I_("BFSC01");
   extern CLASS_EXPORT I_CHAR * const PAYMENT_INSTRUCTIONS     = I_("BFSC02");
   extern CLASS_EXPORT I_CHAR * const BANKING                  = I_("BFSC03");
   extern CLASS_EXPORT I_CHAR * const HISTORICAL_INFO          = I_("BFSC04");
}

namespace BF_SEARCH_PAY_TO_ENTITY_USING
{
   extern CLASS_EXPORT I_CHAR * const BROKER = I_("BFSC01U01");
   extern CLASS_EXPORT I_CHAR * const CLIENT = I_("BFSC01U02");
}

namespace BF_SEARCH_PAYMENT_INSTRUCTIONS_USING
{
   extern CLASS_EXPORT I_CHAR * const BROKER = I_("BFSC02U01");
   extern CLASS_EXPORT I_CHAR * const BRANCH = I_("BFSC02U02");
   extern CLASS_EXPORT I_CHAR * const SLSREP = I_("BFSC02U03");
   extern CLASS_EXPORT I_CHAR * const CLIENT = I_("BFSC02U04");
}

namespace BF_SEARCH_BANKING_USING
{
   extern CLASS_EXPORT I_CHAR * const BROKER = I_("BFSC03U01");
   extern CLASS_EXPORT I_CHAR * const BRANCH = I_("BFSC03U02");
   extern CLASS_EXPORT I_CHAR * const SLSREP = I_("BFSC03U03");
}

namespace BF_SEARCH_HISTORICAL_INFO_USING
{
   extern CLASS_EXPORT I_CHAR * const BROKER = I_("BFSC04U01");
   extern CLASS_EXPORT I_CHAR * const SLSREP = I_("BFSC04U02");
}

namespace FI_SEARCH_CRITERIA
{
   extern CLASS_EXPORT I_CHAR * const INSTITUTIONS = I_("FISC01");
   extern CLASS_EXPORT I_CHAR * const INSTITUTIONS_F4 = I_("FISC02");
   extern CLASS_EXPORT I_CHAR * const TRANSITS = I_("FISC03");
}

namespace FI_SEARCH_INSTITUTIONS_USING
{
   extern CLASS_EXPORT I_CHAR * const NAME  = I_("FISC01U01");
   extern CLASS_EXPORT I_CHAR * const CODE  = I_("FISC01U02");
}

namespace FI_SEARCH_INSTITUTIONS_F4_USING
{
   extern CLASS_EXPORT I_CHAR * const NAME  = I_("FISC02U01");
   extern CLASS_EXPORT I_CHAR * const CODE  = I_("FISC02U02");
}

namespace FI_SEARCH_TRANSITS_USING
{
   extern CLASS_EXPORT I_CHAR * const NAME  = I_("FISC03U01");
}

namespace DTF_SEARCH_CRITERIA
{
   extern CLASS_EXPORT I_CHAR * const DAILY_TRANSACTIONS_FEES = I_("DTFSC01");
   extern CLASS_EXPORT I_CHAR * const CLASS_EFF_HURDLE_RATE   = I_("DTFSC02");
}

namespace DTF_DAILY_TRANSACTIONS_FEES_USING
{
   extern CLASS_EXPORT I_CHAR * const FUND_CLASS       = I_("DTFSC01U01");
   extern CLASS_EXPORT I_CHAR * const EFFECTIVE_DATE   = I_("DTFSC01U02");
}

namespace FEEMODEL_SEARCH_CRITERIA
{
   extern CLASS_EXPORT I_CHAR * const FUNDSPONSORMODEL = I_("FSFMFSC01");
}

namespace FEEMODEL_USING
{
   extern CLASS_EXPORT I_CHAR * const ALLFEEMODEL       = I_("FSFMFSC01U01");
   extern CLASS_EXPORT I_CHAR * const FEEMODELCODE      = I_("FSFMFSC01U02");
   extern CLASS_EXPORT I_CHAR * const FUNDSPONSORCODE   = I_("FSFMFSC01U03");
}

namespace FUNDBROKER_SEARCH_CRITERIA
{
   extern CLASS_EXPORT I_CHAR * const FUNDBROKER = I_("FBSC01");
}

namespace FUNDBROKER_USING
{
   extern CLASS_EXPORT I_CHAR * const ALLFUNDBROKER       = I_("FBSC01U01");
   extern CLASS_EXPORT I_CHAR * const FUNDBROKERCODE      = I_("FBSC01U02");
   extern CLASS_EXPORT I_CHAR * const FUNDBROKERNAME      = I_("FBSC01U03");
}


namespace AGGREGATION_SEARCH_CRITERIA
{
   extern CLASS_EXPORT I_CHAR * const AGGREGATION = I_("AGGSC01");
}

namespace AGGREGATION_USING
{
   extern CLASS_EXPORT I_CHAR * const TRADEDATE      = I_("AGGSC01U02");
   extern CLASS_EXPORT I_CHAR * const AGGRORDERNO    = I_("AGGSC01U01");
   extern CLASS_EXPORT I_CHAR * const ROUTINGREFNO   = I_("AGGSC01U03");
	extern CLASS_EXPORT I_CHAR * const STATUS         = I_("AGGSC01U04");
}

//user access function codes
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const BANKING_BROKER_CODE;
   extern CLASS_IMPORT I_CHAR * const BANKING_BRANCH_CODE;
   extern CLASS_IMPORT I_CHAR * const BANKING_REP_CODE;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_INSTRUCTIONS;
   extern CLASS_IMPORT I_CHAR * const PAY_TO_ENTITY;
   extern CLASS_IMPORT I_CHAR * const INSTITUTION_MAINTENANCE;
   extern CLASS_IMPORT I_CHAR * const DAILY_TRANSACTIONS_FEES;
	extern CLASS_IMPORT I_CHAR * const AGGREGATE_OPTION;
	extern CLASS_IMPORT I_CHAR * const AGGREGATED_ORDER_INFORMATION;
}

namespace FI_CATEGORY
{
   extern I_CHAR * const BANK;
   extern I_CHAR * const BANK_TRANSIT;
   extern I_CHAR * const INSTITUTION;
   extern I_CHAR * const INSTITUTION_TRANSIT;
   extern I_CHAR * const OTHER;
}

struct _sPermissions 
{
//   _sPermissions (
//      const DString& criteriaCode,
//      const DString& permission) :
//   _criteriaCode (criteriaCode),
//   _permission (permission)
//   {};
   const DString _criteriaCode;
   const DString _permission;
};

const _sPermissions permissions [] = 
{
   {BF_SEARCH_CRITERIA::PAY_TO_ENTITY,               UAF::PAY_TO_ENTITY}, 
   {BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS,        UAF::PAYMENT_INSTRUCTIONS}, 
   {BF_SEARCH_CRITERIA::BANKING,                     UAF::BANKING_INSTRUCTION}, 
   {BF_SEARCH_BANKING_USING::BROKER,                 UAF::BANKING_BROKER_CODE}, 
   {BF_SEARCH_BANKING_USING::BRANCH,                 UAF::BANKING_BRANCH_CODE}, 
   {BF_SEARCH_BANKING_USING::SLSREP,                 UAF::BANKING_REP_CODE}, 
   {FI_SEARCH_CRITERIA::INSTITUTIONS,                UAF::INSTITUTION_MAINTENANCE}, 
   {DTF_SEARCH_CRITERIA::DAILY_TRANSACTIONS_FEES,    UAF::DAILY_TRANSACTIONS_FEES},
   {DTF_SEARCH_CRITERIA::CLASS_EFF_HURDLE_RATE,      UAF::DAILY_TRANSACTIONS_FEES},
   {AGGREGATION_SEARCH_CRITERIA::AGGREGATION,		 UAF::AGGREGATED_ORDER_INFORMATION}, 
};
//******************************************************************************
FillSearchCriteria::FillSearchCriteria (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME , NULL_STRING );
   registerMemberData (NUM_FIELDS,
                      (const CLASS_FIELD_INFO *)&classFieldInfo,
                      0,
                      NULL);

   int permsize = sizeof (permissions) / sizeof (_sPermissions);

   for (int i = 0; i < permsize; i++)
   {
      _mpermissions.insert (std::map<DString, DString>::value_type (
         permissions [i]._criteriaCode, permissions [i]._permission));
   }

	addCrossEdit(ifds::FundClass, ifds::SearchFieldCriteria2 ); 
   addCrossEdit(ifds::FundClass, ifds::SearchFieldCriteria3 ); 
}

//******************************************************************************
FillSearchCriteria::~FillSearchCriteria ()
{
   TRACE_DESTRUCTOR ( CLASSNAME );
}

//******************************************************************************
SEVERITY FillSearchCriteria::init (
   const DString &fillSearchType, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //set the defaults
   setFieldNoValidate (ifds::FillSearchType, fillSearchType, 
      idDataGroup, false, true, false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::doApplyRelatedChanges (
   const BFFieldId &idField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::SearchCriteria)
   {
      DString searchCriteria;

      getField (idField, searchCriteria, idDataGroup, false);
      if (searchCriteria == BF_SEARCH_CRITERIA::PAY_TO_ENTITY)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::BrokerFeaturesSearchPayToEntityUsing);
      }
      else if (searchCriteria == BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::BrokerFeaturesSearchPaymentInstructionsUsing);
      }
      else if (searchCriteria == BF_SEARCH_CRITERIA::BANKING)
      {
         //check the security, by calling the below method,
         //private method
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchUsing, 
            ifds::BrokerFeaturesSearchBankingUsing, idDataGroup);
      }
      else if (searchCriteria == BF_SEARCH_CRITERIA::HISTORICAL_INFO)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::BrokerFeaturesSearchHistoricalInfoUsing);
      }
      else if (searchCriteria == FI_SEARCH_CRITERIA::INSTITUTIONS)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::FIFeaturesSearchInstitutionsUsing);
      }
      else if (searchCriteria == FI_SEARCH_CRITERIA::INSTITUTIONS_F4)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::FIFeaturesF4SearchInstitutionsUsing);
      }
      else if (searchCriteria == FI_SEARCH_CRITERIA::TRANSITS)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::FIFeaturesSearchTransitsUsing);         
      }
      else if ( DTF_SEARCH_CRITERIA::DAILY_TRANSACTIONS_FEES == searchCriteria || 
                DTF_SEARCH_CRITERIA::CLASS_EFF_HURDLE_RATE == searchCriteria )
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::DTFFeaturesSearchDailyTransactionsFeesUsing);
      }
      else if ( searchCriteria == FEEMODEL_SEARCH_CRITERIA::FUNDSPONSORMODEL)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::FundSponsorFeeModelUsing);
      }
      else if ( searchCriteria == FUNDBROKER_SEARCH_CRITERIA::FUNDBROKER)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::FundBrokerUsing);
      } //59F
		
		else if ( searchCriteria == AGGREGATION_SEARCH_CRITERIA::AGGREGATION)
      {
         setFieldAllSubstituteValues (ifds::SearchUsing, 
            idDataGroup, ifds::AggregateSearchUsing);
      }

      setFirstSubstCode (ifds::SearchUsing, idDataGroup);
   }
   else if (idField == ifds::FillSearchType)
   {
      DString fillSearchType;

      getField (idField, fillSearchType, idDataGroup, false);
      if (fillSearchType == SEARCH_TYPE::MAIN)
      {
         setFieldAllSubstituteValues (ifds::SearchLabels, 
            idDataGroup, ifds::MainSearchLabels);
         //check the security, by calling the below method, 
         //private method
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchCriteria, 
            ifds::MainSearchCriteria, idDataGroup);
         setFieldAllSubstituteValues (ifds::HowManySearchCriterias, 
            idDataGroup, ifds::MainSearchCriteriaNo);
      }
      else if (fillSearchType == SEARCH_TYPE::BROKER_FEATURES)
      {
         setFieldAllSubstituteValues (ifds::SearchLabels, 
            idDataGroup, ifds::BrokerFeaturesSearchLabels);
         //check the security, by calling the below method,
         //private method
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchCriteria, 
            ifds::BrokerFeaturesSearchCriteria, idDataGroup);
         setFieldAllSubstituteValues (ifds::HowManySearchCriterias, 
            idDataGroup, ifds::BrokerFeaturesSearchCriteriaNo);
      }
      else if (fillSearchType == SEARCH_TYPE::FI_FEATURES)
      {
         setFieldAllSubstituteValues (ifds::SearchLabels, 
            idDataGroup, ifds::FIFeaturesSearchLabels);
         //check the security, by calling the below method,
         //private method
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchCriteria, 
            ifds::FIFeaturesSearchCriteria, idDataGroup);
         setFieldAllSubstituteValues (ifds::HowManySearchCriterias, 
            idDataGroup, ifds::FIFeaturesSearchCriteriaNo);
      }
      else if (fillSearchType == SEARCH_TYPE::FI_FEATURES_F4)
      {
         setFieldAllSubstituteValues (ifds::SearchLabels, 
            idDataGroup, ifds::FIFeaturesF4SearchLabels);
         //check the security, by calling the below method,
         //private method
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchCriteria, 
            ifds::FIFeaturesF4SearchCriteria, idDataGroup);
         setFieldAllSubstituteValues (ifds::HowManySearchCriterias, 
            idDataGroup, ifds::FIFeaturesF4SearchCriteriaNo);
      }
      else if (fillSearchType == SEARCH_TYPE::DAILY_TRANSACTIONS_FEES)
      {
         setFieldAllSubstituteValues (ifds::SearchLabels, 
            idDataGroup, ifds::DTFFeaturesSearchLabels);
         //check the security, by calling the below method,
         //private method
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchCriteria, 
            ifds::DTFFeaturesSearchCriteria, idDataGroup);
         setFieldAllSubstituteValues (ifds::HowManySearchCriterias, 
            idDataGroup, ifds::DTFFeaturesSearchCriteriaNo);
      }
      else if( fillSearchType == SEARCH_TYPE::FUNSSPONSORFEEMODEL)
      {
         setFieldAllSubstituteValues (ifds::SearchLabels, 
            idDataGroup, ifds::FundSponsorFeeModelLabel);
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchCriteria, 
            ifds::FundSponsorFeeModelSearchCriteria, idDataGroup);
         setFieldAllSubstituteValues (ifds::HowManySearchCriterias, 
            idDataGroup, ifds::FundSponsorFeeModelSearchCriteriaNo);
      }
      else if( fillSearchType == SEARCH_TYPE::FUNDBROKER)
      {
         setFieldAllSubstituteValues (ifds::SearchLabels, 
            idDataGroup, ifds::FundBrokerLabel);
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchCriteria, 
            ifds::FundBrokerSearchCriteria, idDataGroup);
         setFieldAllSubstituteValues (ifds::HowManySearchCriterias, 
            idDataGroup, ifds::FundBrokerSearchCriteriaNo);
      } //59F
		else if( fillSearchType == SEARCH_TYPE::AGGREGATEDORDER)
      {
         setFieldAllSubstituteValues (ifds::SearchLabels, 
            idDataGroup, ifds::AggregateSearchLabel);
         checkSecurityAndSetSubstituteValuesForField (ifds::SearchCriteria, 
            ifds::AggregateSearchCriteria, idDataGroup);
         setFieldAllSubstituteValues (ifds::HowManySearchCriterias, 
            idDataGroup, ifds::AggregateSearchCriteriaNo);
      }

      setFirstSubstCode (ifds::SearchCriteria, idDataGroup);
   }
   else if (idField == ifds::SearchUsing)
   {
      assignSearchLabels (idDataGroup);
      if (isFISearchCriteria3Code (idDataGroup) || 
         isFISearchCriteria3Name (idDataGroup))
      {
         setFieldAllSubstituteValues (ifds::SearchFieldCriteria2, 
            idDataGroup, ifds::BankIdType);
         if (isFIFeaturesSearch (idDataGroup))
         {
            setFieldAllSubstituteValues (ifds::SearchFieldCriteria1, 
               idDataGroup, ifds::FinancialInstitutionsCategoryForSearch);
            setFirstSubstCode (ifds::SearchFieldCriteria1, idDataGroup);
            setDefaultBankTypeToSearchCriteria2 (idDataGroup);
         } 
         else if (isFIFeaturesF4Search (idDataGroup))
         {
            setFieldAllSubstituteValues (ifds::SearchFieldCriteria1, 
               idDataGroup, ifds::FinancialInstitutionsCategory);            
            //this freezes the F4 search, keep it this way until further notice....
            setFieldReadOnly (ifds::SearchFieldCriteria1, 
               idDataGroup, true);
            setFieldReadOnly (ifds::SearchFieldCriteria2, 
               idDataGroup, true);
            if (isFISearchCriteria3Code (idDataGroup))
            {
               assignFISearchLabel3 (idDataGroup);
            }
         }
         //clear the 3rd search criteria
         setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
            idDataGroup, false, true, true);
      }
      else if (isDTFSearch (idDataGroup))
      {
         setFieldAllSubstituteValues (ifds::SearchFieldCriteria1, 
            idDataGroup, ifds::DTFSearchRecordType);
         setFirstSubstCode (ifds::SearchFieldCriteria1, idDataGroup);         
         //clear the 2nd search criteria
         setFieldNoValidate (ifds::SearchFieldCriteria2, NULL_STRING, 
            idDataGroup, false, true, true);
			//clear the 3rd search criteria
			setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
            idDataGroup, false, true, true);
         if (isDTFSearchCriteria2EffectiveDate (idDataGroup))
         {
            setCurrentBussinessDateToSearchCriteria2 (idDataGroup);
         }
      }
      else if( isFMSearchCriteriaSponsor( idDataGroup ) )
      {
         FundSponsorFeeModelUsingRelatedChanges( idDataGroup );
      } 
/*      else if( isFMSearchCriteriaFundBrokerCode( idDataGroup ) )
      {
         FundBrokerCodeUsingRelatedChanges( idDataGroup );
      } //59F*/
		else if( isFMSearchCriteriaAggregationTradeDate( idDataGroup ) )
      {
         AggregatedOrderUsingTradeDateRelatedChanges( idDataGroup );
      }
		else if( isFMSearchCriteriaAggregationAggrOrdNo( idDataGroup ) )
      {
         AggregatedOrderUsingAggrOrdNoRelatedChanges( idDataGroup );
      }
		else if( isFMSearchCriteriaAggregationRoutRefNo( idDataGroup ) )
      {
         AggregatedOrderUsingRoutRefNoRelatedChanges( idDataGroup );
      }
		else if( isFMSearchCriteriaAggregationStatus( idDataGroup ) )
      {
         AggregatedOrderUsingStatusRelatedChanges( idDataGroup );
      }
      else //the rest of SearchUsing(s), all search types
      {
         setFieldAllSubstituteValues (ifds::SearchFieldCriteria1, 
            idDataGroup, NULL_STRING);
         setFieldAllSubstituteValues (ifds::SearchFieldCriteria2, 
            idDataGroup, NULL_STRING);
         //clear the search criteria fields
         setFieldNoValidate (ifds::SearchFieldCriteria1, NULL_STRING, 
            idDataGroup, false, true, true);
         setFieldNoValidate (ifds::SearchFieldCriteria2, NULL_STRING, 
            idDataGroup, false, true, true);
         setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
            idDataGroup, false, true, true);
         setFieldNoValidate (ifds::SearchFieldCriteria4, NULL_STRING, 
            idDataGroup, false, true, true);
			setFieldNoValidate (ifds::SearchFieldCriteria5, NULL_STRING, 
            idDataGroup, false, true, true);
         setFieldNoValidate (ifds::SearchFieldCriteria6, NULL_STRING, 
            idDataGroup, false, true, true);
         setFieldNoValidate (ifds::SearchFieldCriteria7, NULL_STRING, 
            idDataGroup, false, true, true);
      }
   }
   else if (idField == ifds::SearchFieldCriteria1 && 
      isBFSearchCriteria1Broker (idDataGroup))
   {
      setFieldNoValidate (ifds::SearchFieldCriteria2, NULL_STRING, 
         idDataGroup, false, true, true);
      setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
         idDataGroup, false, true, true);
   }
   else if (idField == ifds::SearchFieldCriteria2 && 
      isBFSearchCriteria2Branch (idDataGroup))
   {
      setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
         idDataGroup, false, true, true);
   }
   else if (idField == ifds::SearchFieldCriteria1 && 
      isFIFeaturesSearch (idDataGroup) && 
      isFISearchCriteria3Code (idDataGroup))
   {
      DString searchFieldCriteria1;

      getField (ifds::SearchFieldCriteria1, searchFieldCriteria1, 
         idDataGroup, false);
      if (searchFieldCriteria1 == FI_CATEGORY::INSTITUTION ||
         searchFieldCriteria1 == FI_CATEGORY::OTHER)
      {
         setFieldNoValidate (ifds::SearchFieldCriteria2, OTHER, 
            idDataGroup, false, true, true);
         setFieldReadOnly (ifds::SearchFieldCriteria2, idDataGroup, true);
      }
      else 
      {
         setDefaultBankTypeToSearchCriteria2 (idDataGroup);
         if (!isFIFeaturesF4Search (idDataGroup))
         {
            setFieldReadOnly (ifds::SearchFieldCriteria2, idDataGroup, false);
         }
      }
   }
   else if (idField == ifds::SearchFieldCriteria2 && 
      isFISearchCriteria3Code (idDataGroup))
   {
      assignFISearchLabel3 (idDataGroup);
   }
	 else if (idField == ifds::SearchFieldCriteria6 && 
      isFMSearchCriteriaAggregationTradeDate (idDataGroup))
   {
		DString dstrFundWKN, dstrFundCode, dstrClassCode;
		getField (ifds::SearchFieldCriteria6, dstrFundWKN, idDataGroup);
		dstrFundWKN.strip().upperCase();
      getWorkSession ().GetFundClassCodeByWKN  ( dstrFundWKN, dstrFundCode, dstrClassCode);
		setFieldNoValidate (ifds::SearchFieldCriteria5, 
                          dstrFundCode, idDataGroup, false, true, true, true);
   }
	else if (idField == ifds::SearchFieldCriteria7 && 
      isFMSearchCriteriaAggregationTradeDate (idDataGroup))
   {
		DString dstrFundISIN,dstrFundCode, dstrClassCode;
		getField (ifds::SearchFieldCriteria7, dstrFundISIN, idDataGroup);
		dstrFundISIN.strip().upperCase();

      getWorkSession ().GetFundClassCodeByISIN( dstrFundISIN, dstrFundCode, dstrClassCode);
		setFieldNoValidate (ifds::SearchFieldCriteria5, 
                          dstrFundCode, idDataGroup, false, true, true, true);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::FundSponsorFeeModelUsingRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("FundSponsorFeeModelUsingRelatedChanges"));

   FundSponsorsList * pFundSponsorsList;
   DString dstrSubList;
   if (getMgmtCo().getFundSponsorsList(pFundSponsorsList) <= WARNING && pFundSponsorsList)
   {
      pFundSponsorsList->getFundSponsorCodeSubstList(dstrSubList);      
   }

   setFieldAllSubstituteValues(ifds::SearchFieldCriteria1, idDataGroup, dstrSubList);

   setFirstSubstCode (ifds::SearchFieldCriteria1, idDataGroup);         
   //clear the 2nd search criteria
   setFieldNoValidate (ifds::SearchFieldCriteria2, NULL_STRING, 
      idDataGroup, false, true, true);
	//clear the 3rd search criteria
	setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
      idDataGroup, false, true, true);

   return GETCURRENTHIGHESTSEVERITY ();
}
//59F
//******************************************************************************
SEVERITY FillSearchCriteria::FundBrokerCodeUsingRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("FundSponsorFeeModelUsingRelatedChanges"));

   FundBrokerList * pFundBrokerList;
   DString dstrSubList;
   if (getWorkSession ().getFundBrokerList(pFundBrokerList, idDataGroup, true) <= WARNING && pFundBrokerList)
   {
      pFundBrokerList->getFundBrokerCodeSubstList(dstrSubList);      
   }

   setFieldAllSubstituteValues(ifds::SearchFieldCriteria1, idDataGroup, dstrSubList);

   setFirstSubstCode (ifds::SearchFieldCriteria1, idDataGroup);         
   //clear the 2nd search criteria
   setFieldNoValidate (ifds::SearchFieldCriteria2, NULL_STRING, 
      idDataGroup, false, true, true);
	//clear the 3rd search criteria
	setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
      idDataGroup, false, true, true);

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY FillSearchCriteria::AggregatedOrderUsingTradeDateRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("FundSponsorFeeModelUsingRelatedChanges"));

	DString currBusDate, dstrFundCode, dstrClassCode, dstrFundWKN, dstrFundISIN;

   getWorkSession().getOption (ifds::CurrBusDate, currBusDate, 
      BF::HOST, false );
   setFieldNoValidate (ifds::SearchFieldCriteria1, 
      currBusDate, idDataGroup, false, true, true );
	setFieldNoValidate (ifds::SearchFieldCriteria2, 
      currBusDate, idDataGroup, false, true, true );
   //setFieldAllSubstituteValues(ifds::SearchFieldCriteria1, idDataGroup, ifds::FromDate);
   //setFieldAllSubstituteValues(ifds::SearchFieldCriteria2, idDataGroup, ifds::ToDate);
	setFieldAllSubstituteValues(ifds::SearchFieldCriteria3, idDataGroup, ifds::rxOrdStatus);

/*	FundBrokerList * pFundBrokerList;
   DString dstrSubList;
   if (getWorkSession ().getFundBrokerList(pFundBrokerList, idDataGroup, true) <= WARNING && pFundBrokerList)
   {
      pFundBrokerList->getFundBrokerCodeSubstList(dstrSubList);      
   }
   
	setFieldAllSubstituteValues(ifds::SearchFieldCriteria4, idDataGroup, dstrSubList);
*/
	getField (ifds::SearchFieldCriteria6, dstrFundWKN, idDataGroup);
	getField (ifds::SearchFieldCriteria7, dstrFundISIN, idDataGroup);

	getWorkSession ().GetFundClassCodeByISIN ( dstrFundISIN, dstrFundCode,dstrClassCode);
   getWorkSession ().GetFundClassCodeByWKN  ( dstrFundWKN, dstrFundCode, dstrClassCode);

	 setFieldNoValidate (ifds::SearchFieldCriteria5, 
      dstrFundCode, idDataGroup, false, true, true, false);
	//setFieldAllSubstituteValues(ifds::SearchFieldCriteria5, idDataGroup, ifds::FundCode);
	//setFieldAllSubstituteValues(ifds::SearchFieldCriteria6, idDataGroup, ifds::FundWKN);
	//setFieldAllSubstituteValues(ifds::SearchFieldCriteria7, idDataGroup, ifds::FundISIN);
  
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY FillSearchCriteria::AggregatedOrderUsingAggrOrdNoRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("FundSponsorFeeModelUsingRelatedChanges"));

   setFieldNoValidate (ifds::SearchFieldCriteria2, NULL_STRING, 
      idDataGroup, false, true, true);

	setFieldAllSubstituteValues(ifds::SearchFieldCriteria1, idDataGroup, ifds::OmnibusID);

	setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria4, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria5, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria6, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria7, NULL_STRING, 
      idDataGroup, false, true, true);
  
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY FillSearchCriteria::AggregatedOrderUsingRoutRefNoRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("FundSponsorFeeModelUsingRelatedChanges"));

   setFieldNoValidate (ifds::SearchFieldCriteria2, NULL_STRING, 
      idDataGroup, false, true, true);

	setFieldAllSubstituteValues(ifds::SearchFieldCriteria1, idDataGroup, ifds::RoutingRef);

	setFieldNoValidate (ifds::SearchFieldCriteria3, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria4, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria5, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria6, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria7, NULL_STRING, 
      idDataGroup, false, true, true);
  
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY FillSearchCriteria::AggregatedOrderUsingStatusRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("FundSponsorFeeModelUsingRelatedChanges"));

   setFieldAllSubstituteValues(ifds::SearchFieldCriteria1, idDataGroup, ifds::rxOrdStatus);

	setFieldNoValidate (ifds::SearchFieldCriteria2, NULL_STRING, 
      idDataGroup, false, true, true);
		
	//setFieldAllSubstituteValues(ifds::SearchFieldCriteria3, idDataGroup, ifds::FundBroker);

	setFieldNoValidate (ifds::SearchFieldCriteria4, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria5, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria6, NULL_STRING, 
      idDataGroup, false, true, true);
	setFieldNoValidate (ifds::SearchFieldCriteria7, NULL_STRING, 
      idDataGroup, false, true, true);
  
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::doValidateField (const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   
   if (idField == ifds::SearchFieldCriteria1 && 
      isBFSearchCriteria1Broker (idDataGroup))
   {
      if (strValue != NULL_STRING) //check for existance
      {
         BrokerList brokerList (*this);

         if (brokerList.init2 (strValue, NULL_STRING, I_("L"), 
            NULL_STRING, NULL_STRING) <= WARNING)
         {
            BFObjIter bfIter (brokerList, idDataGroup);
            
            bfIter.begin ();
            if (!bfIter.end ())
            {       
               Broker* pBroker = dynamic_cast<Broker*> (bfIter.getObject ());
               DString dstrCurrBusDate;

               getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, 
                  idDataGroup, false); 
               pBroker->checkEffective (dstrCurrBusDate, idDataGroup);
            }
         }
      }
   }
   else if (idField == ifds::SearchFieldCriteria2 && 
      isBFSearchCriteria2Branch (idDataGroup))
   {
      DString brokerCode;

      getField (ifds::SearchFieldCriteria1, brokerCode, idDataGroup);
      if (brokerCode != NULL_STRING && strValue != NULL_STRING)
      {
         BranchList branchList (*this);

         if (branchList.init (brokerCode, strValue) <= WARNING)
         {
            BFObjIter bfIter (branchList, idDataGroup);

            bfIter.begin ();
            if (!bfIter.end ())
            {
               Branch* pBranch = dynamic_cast <Branch*> (bfIter.getObject ());
               DString dstrCurrBusDate;
         
               //chech the effectiveness of the branch
               getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, 
                  idDataGroup, false); 
               pBranch->checkEffective (dstrCurrBusDate, idDataGroup);
            }
         }
      }
   }
   else if (idField == ifds::SearchFieldCriteria3 && 
      isBFSearchCriteria3SlsRep (idDataGroup))
   {
      DString brokerCode, branchCode;

      getField (ifds::SearchFieldCriteria1, brokerCode, idDataGroup);
      getField (ifds::SearchFieldCriteria2, branchCode, idDataGroup);
      if (brokerCode != NULL_STRING && branchCode != NULL_STRING && 
         strValue != NULL_STRING)
      {
         AgentList agentList (*this);

         if (agentList.init (brokerCode, branchCode, strValue) <= WARNING)
         {
            BFObjIter bfIter (agentList, idDataGroup);

            bfIter.begin ();
            if (!bfIter.end ())
            {       
               Agent *pAgent = dynamic_cast<Agent*> (bfIter.getObject ());
               DString dstrCurrBusDate;

               //chech the effectiveness of the slsrep
               getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, 
                  idDataGroup, false); 
               pAgent->checkEffective (dstrCurrBusDate, idDataGroup);
            }
         }
      }
   }
   else if (idField == ifds::SearchFieldCriteria3 && 
      isFISearchCriteria3Code (idDataGroup))
   {
      DString category, 
         type;

      getField (ifds::SearchFieldCriteria1, category, idDataGroup, false);
      getField (ifds::SearchFieldCriteria2, type, idDataGroup, false);
      if (FinancialInstitution::institution (category))
      {
         FinancialInstitution::validateFICode (category, type, strValue);
      }
      else
      {
         FinancialInstitution::validateFITransitNum (
            FinancialInstitution::getParentCategory (category), type, strValue);
      }
   }
   else if (idField == ifds::SearchFieldCriteria2 && 
      isDTFSearchCriteria2FundCode (idDataGroup))
   {
      FundMasterList *pFundMasterList = NULL;
      DString fundCode;

      getField (ifds::SearchFieldCriteria2, fundCode, idDataGroup, false);
      fundCode.strip().upperCase();
      if (!fundCode.empty() && 
         getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING &&
         pFundMasterList)
      {
         if (!pFundMasterList->IsFundExist (fundCode, idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
         }
      }
   }
   else if (idField == ifds::SearchFieldCriteria3 && 
      isDTFSearchCriteria3ClassCode (idDataGroup))
   {
      FundDetail *pFundDetail = NULL;
      DString fundCode, 
         classCode;

      getField (ifds::SearchFieldCriteria2, fundCode, idDataGroup, false);
      getField (ifds::SearchFieldCriteria3, classCode, idDataGroup, false);
      fundCode.strip().upperCase();
      classCode.strip().upperCase();
      if (!classCode.empty())
      {
         if (!getWorkSession().getFundDetail (
               fundCode, 
               classCode, 
               idDataGroup, 
               pFundDetail) ||
            !pFundDetail)
         {
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
         }
      }
   }
	else if ( idField == ifds::FundClass &&
		       ( isDTFSearchCriteria2FundCode (idDataGroup) ||
				   isDTFSearchCriteria3ClassCode (idDataGroup) ) )
	{
		DString dstrFundCode, dstrClassCode;
		getField (ifds::SearchFieldCriteria2, dstrFundCode,  idDataGroup, false );
      getField (ifds::SearchFieldCriteria3, dstrClassCode, idDataGroup, false );

		if ( ( !dstrFundCode.strip().empty() &&  dstrClassCode.strip().empty() ) ||
			  ( dstrFundCode.strip().empty() &&  !dstrClassCode.strip().empty() ) )
		{
			ADDCONDITIONFROMFILE (CND::ERR_FUND_CLASS_MUST_BOTH_BE_BLANK );
		}
	}
   else if (idField == ifds::SearchFieldCriteria1 && 
      isFMSearchCriteriaFeeModel (idDataGroup)) 
   {
      DString dstrFeeModelCode;
      getField (ifds::SearchFieldCriteria1, dstrFeeModelCode, idDataGroup);
      ValidateModelCode(idDataGroup, dstrFeeModelCode);
   }
   else if ( ( idField == ifds::SearchFieldCriteria3 && isFMSearchCriteriaAggregationStatus (idDataGroup) ) ||
             ( idField == ifds::SearchFieldCriteria4 && isFMSearchCriteriaAggregationTradeDate (idDataGroup) ) 
           )
   {
      FundBrokerList fundBrokerList ( getWorkSession() ); 
      DString dstrFundBrokerCode;
      
      getField ( idField, dstrFundBrokerCode, idDataGroup );
      
      if( dstrFundBrokerCode != NULL_STRING )
      {
         if ( fundBrokerList.init ( dstrFundBrokerCode, NULL_STRING, idDataGroup, I_("N"), NULL_STRING ) <= WARNING )
                      
         {
            BFObjIter iter( fundBrokerList, idDataGroup );
            if( !(iter.getNumberOfItemsInList() > 0) )
            {
               ADDCONDITIONFROMFILE ( CND::ERR_FUND_BROKER_CODE_NOT_EXISTING );         
            }
         }
      }
      else
      {
         ADDCONDITIONFROMFILE(CND::ERR_FUND_BROKER_CODE_IS_EMPTY);
      }
   }
      
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::ValidateModelCode( const BFDataGroupId& idDataGroup, const DString& dstrValue)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateModelCode"));
   
   DString currBusDate;

   getWorkSession().getOption (ifds::CurrBusDate, currBusDate, 
      BF::HOST, false);

   FeeModelList * pFeeModelList;
   getWorkSession().getFeeModelList(pFeeModelList, idDataGroup);
   if(pFeeModelList)
   {
      int ret = pFeeModelList->isValidFeeModelCode(idDataGroup, dstrValue, currBusDate);
      if(ret == 1)
      {
         DString dstrTemp;                 
			addIDITagValue( dstrTemp, I_("FEEMODELCODE"), dstrValue );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FEEMODEL_CODE_NOT_SETUP, dstrTemp);	
      }
      if(ret == 2 )
      {
         DString dstrTemp;                 
			addIDITagValue( dstrTemp, I_("FEEMODELCODE"), dstrValue );
         addIDITagValue( dstrTemp, I_("DATE"), currBusDate );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FEEMODEL_CODE_NOT_ACTIVE, dstrTemp);	
      }
   }      
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY FillSearchCriteria::setDefaultBankTypeToSearchCriteria2 (
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setDefaultBankTypeToSearchCriteria2"));

   //try to set the default bank type, based on the system configuration            
   DString defaultBankType;

   getWorkSession().getOption (ifds::DefaultBankType, defaultBankType, 
      BF::HOST, false);
   if (defaultBankType.empty())
   {
      setFirstSubstCode (ifds::SearchFieldCriteria2, idDataGroup);
   }
   else 
   {
      setFieldNoValidate (ifds::SearchFieldCriteria2, 
         defaultBankType, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::setCurrentBussinessDateToSearchCriteria2 (
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setCurrentBussinessDateToSearchCriteria2"));

   //try to set current business date, based on the system configuration            
   DString currBusDate;

   getWorkSession().getOption (ifds::CurrBusDate, currBusDate, 
      BF::HOST, false);
   setFieldNoValidate (ifds::SearchFieldCriteria2, 
      currBusDate, idDataGroup, false, true, true, false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::assignFISearchLabel3 (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("assignFISearchLabel3"));
      
   setFieldNoValidate (ifds::SearchLabel3, NULL_STRING, 
      idDataGroup, false, true, false);

   DString fiSearchLabels3, 
      searchCriteria2;

   BFProperties *pProperties = getFieldProperties (ifds::FinancialInstitutionsCodeLabel, 
      idDataGroup);
   
   pProperties->getAllSubstituteValues (fiSearchLabels3);
   getField (ifds::SearchFieldCriteria2, searchCriteria2, idDataGroup, false);

   I_CHAR *temp = const_cast<I_CHAR*> (fiSearchLabels3.c_str ());

   do
   {
      DString fullLabelCode;
      DString labelDescription;

      temp = parseIdiString (temp, fullLabelCode, labelDescription);
      
      DString::size_type labelPos = fullLabelCode.find (searchCriteria2);

      if (labelPos != DString::npos)
      {
         setFieldNoValidate (ifds::SearchLabel3, labelDescription, 
            idDataGroup, false, true, true);
         break;
      }
   } while (temp && temp != NULL_STRING && *temp);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::assignSearchLabels (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("assignSearchLabels"));
      
   DString label1 (NULL_STRING), 
      label2 (NULL_STRING), 
      label3 (NULL_STRING),
      label4 (NULL_STRING),
		label5 (NULL_STRING),
		label6 (NULL_STRING),
	   label7 (NULL_STRING);

   //resetting the labels
   setFieldNoValidate (ifds::SearchLabel1, label1, 
      idDataGroup, false, true, false);
   setFieldNoValidate (ifds::SearchLabel2, label2, 
      idDataGroup, false, true, false);
   setFieldNoValidate (ifds::SearchLabel3, label3, 
      idDataGroup, false, true, false);
   setFieldNoValidate (ifds::SearchLabel4, label4, 
      idDataGroup, false, true, false);
	setFieldNoValidate (ifds::SearchLabel5, label5, 
      idDataGroup, false, true, false);
   setFieldNoValidate (ifds::SearchLabel6, label6, 
      idDataGroup, false, true, false);
   setFieldNoValidate (ifds::SearchLabel7, label7, 
      idDataGroup, false, true, false);


   DString searchLabels, 
      searchUsingCode;

   BFProperties *pProperties = getFieldProperties (ifds::SearchLabels, idDataGroup);
   
   pProperties->getAllSubstituteValues (searchLabels);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   //based on the 'using' code we need to search into the SearchLabels 
   //list and retrieve the right labels; 
   //the labels contain in their code the 'using' code
   I_CHAR *temp = const_cast<I_CHAR*> (searchLabels.c_str ());

   do
   {
      DString fullLabelCode;
      DString labelDescription;

      temp = parseIdiString (temp, fullLabelCode, labelDescription);
      
      //find the pos of the searchUsingCode
      DString::size_type labelPos = fullLabelCode.find (searchUsingCode);

      if (labelPos != DString::npos)
      {
         DString labelCode = fullLabelCode.substr (labelPos);
         DString::size_type commaPos = labelCode.find (COMMA);

         if (commaPos != DString::npos)
         {
            labelCode = labelCode.substr (0, commaPos);
         }
         if (labelCode.find (LABEL1_MNEMONIC) != DString::npos)
         {
            setFieldNoValidate (ifds::SearchLabel1, labelDescription, 
               idDataGroup, false, true, true);
            label1 = labelDescription;
         }
         else if (labelCode.find (LABEL2_MNEMONIC) != DString::npos)
         {
            setFieldNoValidate (ifds::SearchLabel2, labelDescription, 
               idDataGroup, false, true, true);
            label2 = labelDescription;
         }
         else if (labelCode.find (LABEL3_MNEMONIC) != DString::npos)
         {
            setFieldNoValidate (ifds::SearchLabel3, labelDescription, 
               idDataGroup, false, true, true);
            label3 = labelDescription;
         }
         else if (labelCode.find (LABEL4_MNEMONIC) != DString::npos)
         {
            setFieldNoValidate (ifds::SearchLabel4, labelDescription, 
               idDataGroup, false, true, true);
            label4 = labelDescription;
         }
			else if (labelCode.find (LABEL5_MNEMONIC) != DString::npos)
         {
            setFieldNoValidate (ifds::SearchLabel5, labelDescription, 
               idDataGroup, false, true, true);
            label5 = labelDescription;
         }
			else if (labelCode.find (LABEL6_MNEMONIC) != DString::npos)
         {
            setFieldNoValidate (ifds::SearchLabel6, labelDescription, 
               idDataGroup, false, true, true);
            label6 = labelDescription;
         }
			else if (labelCode.find (LABEL7_MNEMONIC) != DString::npos)
         {
            setFieldNoValidate (ifds::SearchLabel7, labelDescription, 
               idDataGroup, false, true, true);
            label7 = labelDescription;
         }
      }
   } while (temp && temp != NULL_STRING && *temp);

   if (label1 == NULL_STRING && 
      label2 == NULL_STRING && 
      label3 == NULL_STRING &&
      label4 == NULL_STRING &&
		label5 == NULL_STRING && 
      label6 == NULL_STRING &&
      label7 == NULL_STRING )

   {
      setFieldNoValidate (ifds::HowManySearchCriterias, I_("0"), 
         idDataGroup, true, true, false);
   }
   else 
   {
      //set the how many search criterias field, based on the search using code
      setHowManySearchCriterias (searchUsingCode, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::setFirstSubstCode (const BFFieldId &idSubstField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFirstSubstCode"));
      
   DString substList, 
      firstCode,
      firstDescription;

   BFProperties *pProperties = getFieldProperties (idSubstField, idDataGroup);
   
   pProperties->getAllSubstituteValues (substList);

   I_CHAR *temp = const_cast<I_CHAR*> (substList.c_str ());

   temp = parseIdiString (temp, firstCode, 
      firstDescription);
   if (idSubstField == ifds::SearchUsing)
   {
      //set the how many search criterias field, based on the search using code
      setHowManySearchCriterias (firstCode, idDataGroup);
   }
   setFieldNoValidate (idSubstField, firstCode, 
      idDataGroup, false, true, true);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::setHowManySearchCriterias (const DString &searchUsingCode,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setHowManySearchCriterias" ));
      
   DString substList, 
      dstrCriteriaNo (I_("0"));

   BFProperties *pProperties = getFieldProperties (ifds::HowManySearchCriterias, idDataGroup);
   
   pProperties->getAllSubstituteValues (substList);

   I_CHAR *temp = const_cast<I_CHAR*> (substList.c_str ());

   do
   {
      DString searchUsingCodes;
      DString searchCriteriaNo;

      temp = parseIdiString (temp, searchUsingCodes, searchCriteriaNo);
      //find the pos of the searchUsingCode
      DString::size_type pos = searchUsingCodes.find (searchUsingCode);
      //we have a match
      if (pos != DString::npos)
      {
         dstrCriteriaNo = searchCriteriaNo;
         break;
      }

   } while (temp && temp != NULL_STRING && *temp);
   setFieldNoValidate (ifds::HowManySearchCriterias, dstrCriteriaNo, 
      idDataGroup, true, true, false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool FillSearchCriteria::isBFSearchCriteria1Broker (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return searchCriteriaCode == BF_SEARCH_CRITERIA::PAY_TO_ENTITY ||
      searchCriteriaCode == BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS ||
      searchCriteriaCode == BF_SEARCH_CRITERIA::BANKING ||
      searchCriteriaCode == BF_SEARCH_CRITERIA::HISTORICAL_INFO;
}

//******************************************************************************
bool FillSearchCriteria::isBFSearchCriteria2Branch (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return (searchCriteriaCode == BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS &&
      (searchUsingCode == BF_SEARCH_PAYMENT_INSTRUCTIONS_USING::BRANCH || 
      searchUsingCode == BF_SEARCH_PAYMENT_INSTRUCTIONS_USING::SLSREP)) ||
      (searchCriteriaCode == BF_SEARCH_CRITERIA::BANKING &&
      (searchUsingCode == BF_SEARCH_BANKING_USING::BRANCH || 
      searchUsingCode == BF_SEARCH_BANKING_USING::SLSREP)) ||
      (searchCriteriaCode == BF_SEARCH_CRITERIA::HISTORICAL_INFO &&
      searchUsingCode == BF_SEARCH_HISTORICAL_INFO_USING::SLSREP);

}

//******************************************************************************
bool FillSearchCriteria::isBFSearchCriteria3SlsRep (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return (searchCriteriaCode == BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS &&      
      searchUsingCode == BF_SEARCH_PAYMENT_INSTRUCTIONS_USING::SLSREP) ||
      (searchCriteriaCode == BF_SEARCH_CRITERIA::BANKING &&      
      searchUsingCode == BF_SEARCH_BANKING_USING::SLSREP) ||
      (searchCriteriaCode == BF_SEARCH_CRITERIA::HISTORICAL_INFO &&
      searchUsingCode == BF_SEARCH_HISTORICAL_INFO_USING::SLSREP);

}

//******************************************************************************
bool FillSearchCriteria::isFISearchCriteria1Name (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return (searchCriteriaCode == FI_SEARCH_CRITERIA::INSTITUTIONS &&      
      searchUsingCode == FI_SEARCH_INSTITUTIONS_USING::NAME);

}

//******************************************************************************
bool FillSearchCriteria::isFISearchCriteria3Name (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return searchCriteriaCode == FI_SEARCH_CRITERIA::INSTITUTIONS_F4 &&
      searchUsingCode == FI_SEARCH_INSTITUTIONS_F4_USING::NAME;
}

//******************************************************************************
bool FillSearchCriteria::isFISearchCriteria3Code (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return (searchCriteriaCode == FI_SEARCH_CRITERIA::INSTITUTIONS && 
      searchUsingCode == FI_SEARCH_INSTITUTIONS_USING::CODE) ||
      (searchCriteriaCode == FI_SEARCH_CRITERIA::INSTITUTIONS_F4 &&
      searchUsingCode == FI_SEARCH_INSTITUTIONS_F4_USING::CODE);
}

//******************************************************************************
bool FillSearchCriteria::isDTFSearchCriteria2FundCode (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, 
      searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return ( ( DTF_SEARCH_CRITERIA::DAILY_TRANSACTIONS_FEES == searchCriteriaCode ||
              DTF_SEARCH_CRITERIA::CLASS_EFF_HURDLE_RATE == searchCriteriaCode   )  && 
             searchUsingCode == DTF_DAILY_TRANSACTIONS_FEES_USING::FUND_CLASS);
}
//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaSponsor( const BFDataGroupId &idDataGroup )
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return searchCriteriaCode == FEEMODEL_SEARCH_CRITERIA::FUNDSPONSORMODEL && 
      searchUsingCode == FEEMODEL_USING::FUNDSPONSORCODE;      
}
//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaFeeModel( const BFDataGroupId &idDataGroup )
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return searchCriteriaCode == FEEMODEL_SEARCH_CRITERIA::FUNDSPONSORMODEL && 
      searchUsingCode == FEEMODEL_USING::FEEMODELCODE;      
}

//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaFundBrokerCode( const BFDataGroupId &idDataGroup )
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return searchCriteriaCode == FUNDBROKER_SEARCH_CRITERIA::FUNDBROKER && 
      searchUsingCode == FUNDBROKER_USING::FUNDBROKERCODE;      
}

//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaFundBrokerName( const BFDataGroupId &idDataGroup )
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return searchCriteriaCode == FUNDBROKER_SEARCH_CRITERIA::FUNDBROKER && 
      searchUsingCode == FUNDBROKER_USING::FUNDBROKERNAME;      
} //59F

//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaAggregationTradeDate( const BFDataGroupId &idDataGroup )
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return (searchCriteriaCode == AGGREGATION_SEARCH_CRITERIA::AGGREGATION && 
      searchUsingCode == AGGREGATION_USING::TRADEDATE);      
}

//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaAggregationAggrOrdNo( const BFDataGroupId &idDataGroup )
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return (searchCriteriaCode == AGGREGATION_SEARCH_CRITERIA::AGGREGATION && 
      searchUsingCode == AGGREGATION_USING::AGGRORDERNO);      
}
//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaAggregationRoutRefNo( const BFDataGroupId &idDataGroup )
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return (searchCriteriaCode == AGGREGATION_SEARCH_CRITERIA::AGGREGATION && 
      searchUsingCode == AGGREGATION_USING::AGGRORDERNO);      
}

//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaAggregationStatus( const BFDataGroupId &idDataGroup )
{
   DString searchCriteriaCode, searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return (searchCriteriaCode == AGGREGATION_SEARCH_CRITERIA::AGGREGATION && 
      searchUsingCode == AGGREGATION_USING::STATUS );      
}

//******************************************************************************
bool FillSearchCriteria::isFMSearchCriteriaAggregatedOrder( const BFDataGroupId &idDataGroup )
{
	DString searchCriteriaCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
	return searchCriteriaCode == AGGREGATION_SEARCH_CRITERIA::AGGREGATION;
}
//******************************************************************************
bool FillSearchCriteria::isDTFSearchCriteria3ClassCode (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, 
      searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return ( ( DTF_SEARCH_CRITERIA::DAILY_TRANSACTIONS_FEES == searchCriteriaCode  || 
              DTF_SEARCH_CRITERIA::CLASS_EFF_HURDLE_RATE == searchCriteriaCode  ) && 
              searchUsingCode == DTF_DAILY_TRANSACTIONS_FEES_USING::FUND_CLASS);
}

//******************************************************************************
bool FillSearchCriteria::isDTFSearchCriteria2EffectiveDate (const BFDataGroupId &idDataGroup)
{
   DString searchCriteriaCode, 
      searchUsingCode;

   getField (ifds::SearchCriteria, searchCriteriaCode, idDataGroup, false);
   getField (ifds::SearchUsing, searchUsingCode, idDataGroup, false);

   return searchCriteriaCode == DTF_SEARCH_CRITERIA::DAILY_TRANSACTIONS_FEES && 
      searchUsingCode == DTF_DAILY_TRANSACTIONS_FEES_USING::EFFECTIVE_DATE;
}

//******************************************************************************
bool FillSearchCriteria::isMainSearch (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isFIFeaturesSearchType "));

   DString searchType;

   getField (ifds::FillSearchType, searchType, idDataGroup, false);
   return searchType == SEARCH_TYPE::MAIN;
}

//******************************************************************************
bool FillSearchCriteria::isFIFeaturesSearch (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isFIFeaturesSearch"));

   DString searchType;

   getField (ifds::FillSearchType, searchType, idDataGroup, false);
   return searchType == SEARCH_TYPE::FI_FEATURES;
}

//******************************************************************************
bool FillSearchCriteria::isFIFeaturesF4Search (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isFIFeaturesSearch"));

   DString searchType;

   getField (ifds::FillSearchType, searchType, idDataGroup, false);
   return searchType == SEARCH_TYPE::FI_FEATURES_F4;
}

//******************************************************************************
bool FillSearchCriteria::isBrokersFeaturesSearch (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isBrokersFeaturesSearch"));

   DString searchType;

   getField (ifds::FillSearchType, searchType, idDataGroup, false);
   return searchType == SEARCH_TYPE::BROKER_FEATURES;
}

//******************************************************************************
bool FillSearchCriteria::isDTFSearch (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDTFSearch"));

   DString searchType;

   getField (ifds::FillSearchType, searchType, idDataGroup, false);
   return searchType == SEARCH_TYPE::DAILY_TRANSACTIONS_FEES;
}

//******************************************************************************
SEVERITY FillSearchCriteria::checkUAFForSearchCriteria (DString& newSubstList, 
   const BFFieldId &idField, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkUAFForSearchCriteria"));
      
   DString substList, 
      code,
      description;

   BFProperties *pProperties = getFieldProperties (idField, idDataGroup);
   
   pProperties->getAllSubstituteValues (substList);
   newSubstList = NULL_STRING;
   I_CHAR *temp = const_cast<I_CHAR*> (substList.c_str ());

   do
   {
      temp = parseIdiString (temp, code, description);

      std::map<DString, DString>::iterator iter;
      iter = _mpermissions.find (code);
      bool add = iter == _mpermissions.end () || 
         getWorkSession ().hasReadPermission ( (*iter).second);

      if (add)
      {
         newSubstList += code + I_("=") + description + I_(";");
      }
   } 
   while (temp && temp != NULL_STRING && *temp);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FillSearchCriteria::checkSecurityAndSetSubstituteValuesForField (
   const BFFieldId &idField, const BFFieldId &idSubstField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
      CLASSNAME, I_("checkSecurityAndSetSubstituteValuesForField"));

   //set the default subst list
   setFieldAllSubstituteValues (idField, idDataGroup, idSubstField);

   //build a the new one, as the subs-set of the default one,
   //looking at the permissions
   DString searchCriteriaSubstList;

   checkUAFForSearchCriteria (searchCriteriaSubstList, idField, idDataGroup);
   //set it again
   setFieldAllSubstituteValues (idField, idDataGroup, searchCriteriaSubstList);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FillSearchCriteria.cpp-arc  $
// 
//    Rev 1.23   Mar 26 2009 01:50:38   kitticha
// IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. Code review.
// 
//    Rev 1.22   Mar 25 2009 07:27:18   kitticha
// IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search.
// 
//    Rev 1.21   Jan 31 2005 16:14:18   zhangcel
// PTS ticket 10038229 -- Fix searching issue for AggregatedOrder searching by TradeDate
// 
//    Rev 1.20   Jan 14 2005 14:11:12   zhangcel
// PTS ticket 10037813 -- fix showing fund Broker substition list issue.
// 
//    Rev 1.19   Dec 07 2004 10:31:16   zhangcel
// PET1117 - FN8 -- Changed User identify functionality for AggregatedOrders
// 
//    Rev 1.18   Nov 26 2004 19:08:56   Fengyong
// change fund broker code select from combo to edit box
// 
//    Rev 1.17   Nov 26 2004 14:40:52   zhangcel
// PET1117/FN8 -- Aggregated Order related changes
// 
//    Rev 1.16   Nov 05 2004 15:40:30   ZHANGCEL
// PET1117/08 Add sreaching logic for AggregatedOrder
// 
//    Rev 1.15   Oct 25 2004 17:27:50   FENGYONG
// Un comment PET1117 FN54 - Fund Broker static codes 
// 
//    Rev 1.13   Oct 19 2004 14:39:16   FENGYONG
// PET1117 FN54 - Fund Broker Static
// 
//    Rev 1.12   Aug 10 2004 11:24:26   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.11   Mar 25 2004 10:02:28   VADEANUM
// PTS 10028469 - For DAL search, both Fund and Class cannot be blank.
// 
//    Rev 1.10   Feb 03 2004 16:33:14   VADEANUM
// PET 859 FN23 - ADL - removed Fee search param
// 
//    Rev 1.9   Jan 28 2004 21:35:18   popescu
// PET 859, FN 23, modified resources (dialogs and menu item) and coded for the features search dialog
// 
//    Rev 1.8   Jan 12 2004 17:55:14   popescu
// PTS 10020577, added F4 institution search and F4 transit search on banking instriuctions screen, for corresponding edit fields
// 
//    Rev 1.7   Oct 27 2003 19:48:34   popescu
// CIBC PET809, FN 13, added Transit Search by name
// 
//    Rev 1.6   Oct 19 2003 16:44:18   popescu
// CIBC, PET809, FN 13 banking work
// 
//    Rev 1.5   Oct 04 2003 15:59:18   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.4   Sep 02 2003 17:57:54   popescu
// added validation to check for the effectiveness of the broker, branch and salesrep. If this is not in place creating a payment instructions record can cause issues
// 
//    Rev 1.3   Jul 23 2003 14:08:40   popescu
// Added security checking to payment instructions and pay to entity screens
// 
//    Rev 1.2   Jul 02 2003 17:49:32   popescu
// work for payment instructions feature 
// 
//    Rev 1.1   Jun 30 2003 16:55:56   popescu
// added historical info search to the Broker Features search;
// moved some param names to the mfcaniterprocparam namespace
// 
//    Rev 1.0   Jun 27 2003 18:16:44   popescu
// Initial revision.
// 
 */