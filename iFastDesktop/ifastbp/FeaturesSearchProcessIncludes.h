#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//    AUTHOR : Serban Popescu
//    DATE   : June 2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


const BFFieldId IsBFSearchCriteria1Broker(1);
const BFFieldId IsBFSearchCriteria2Branch(2);
const BFFieldId IsBFSearchCriteria3SlsRep(3);
const BFFieldId IsFISearchCriteria1Name(4);
const BFFieldId IsFISearchCriteria3Name(5);
const BFFieldId IsFISearchCriteria3Code(6);
const BFFieldId IsDTFSearchCriteria2Fund(7);
const BFFieldId IsDTFSearchCriteria3Class(8);
const BFFieldId IsFMSearchCriteriaFeeModel(9);
const BFFieldId IsFMSearchCriteriaSponsor(10);
const BFFieldId IsFMSearchCriteriaFundBrokerCode(11);
const BFFieldId IsFMSearchCriteriaFundBrokerName(12);
const BFFieldId isFMSearchCriteriaAggregationTradeDate(13);
const BFFieldId isFMSearchCriteriaAggregationAggrOrdNo(14);
const BFFieldId isFMSearchCriteriaAggregationRoutRefNo(15);
const BFFieldId isFMSearchCriteriaAggregationStatus(16);

namespace 
{
   const I_CHAR *const SEARCH = I_("Search");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId SearchUsing;
   //labels
   extern CLASS_IMPORT const BFTextFieldId SearchLabel1;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel2;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel3;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel4;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel5;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel6;
   extern CLASS_IMPORT const BFTextFieldId SearchLabel7;
   //fields
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria1;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria2;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria3;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria4;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria5;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria6;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria7;
   extern CLASS_IMPORT const BFTextFieldId HowManySearchCriterias;
   extern CLASS_IMPORT const BFTextFieldId FillSearchType;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SEARCH_CRITERIA_FILLER;
}

namespace SEARCH_TYPE
{
   extern CLASS_IMPORT I_CHAR * const BROKER_FEATURES;
   extern CLASS_IMPORT I_CHAR * const FI_FEATURES;
   extern CLASS_IMPORT I_CHAR * const DAILY_TRANSACTIONS_FEES;
   extern CLASS_IMPORT I_CHAR * const FUNSSPONSORFEEMODEL;
   extern CLASS_IMPORT I_CHAR * const FUNDBROKER;
   extern CLASS_IMPORT I_CHAR * const SYSTEM;
	extern CLASS_IMPORT I_CHAR * const AGGREGATEDORDER;
}

namespace BF_SEARCH_CRITERIA
{
   //payment instructions
   extern CLASS_IMPORT I_CHAR * const PAY_TO_ENTITY;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_INSTRUCTIONS;
   extern CLASS_IMPORT I_CHAR * const BANKING;
   extern CLASS_IMPORT I_CHAR * const HISTORICAL_INFO;
}

namespace BF_SEARCH_PAY_TO_ENTITY_USING
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
}

namespace BF_SEARCH_PAYMENT_INSTRUCTIONS_USING
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SLSREP;
}

namespace BF_SEARCH_BANKING_USING
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SLSREP;
}

namespace BF_SEARCH_HISTORICAL_INFO_USING
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const SLSREP;
}

namespace FI_SEARCH_CRITERIA
{
   extern CLASS_IMPORT I_CHAR * const INSTITUTIONS;
   extern CLASS_IMPORT I_CHAR * const TRANSITS;
}

namespace FI_SEARCH_INSTITUTIONS_USING
{
   extern CLASS_IMPORT I_CHAR * const NAME;
   extern CLASS_IMPORT I_CHAR * const CODE;
}

namespace FI_SEARCH_TRANSITS_USING
{
   extern CLASS_IMPORT I_CHAR * const NAME;
}

namespace DTF_SEARCH_CRITERIA
{
   extern CLASS_IMPORT I_CHAR * const DAILY_TRANSACTIONS_FEES;
   extern CLASS_IMPORT I_CHAR * const CLASS_EFF_HURDLE_RATE ;
}

namespace DTF_DAILY_TRANSACTIONS_FEES_USING
{
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const EFFECTIVE_DATE;
}

namespace FEEMODEL_SEARCH_CRITERIA
{
   extern CLASS_IMPORT I_CHAR * const FUNDSPONSORMODEL;
}

namespace FEEMODEL_USING
{
   extern CLASS_IMPORT I_CHAR * const ALLFEEMODEL;
   extern CLASS_IMPORT I_CHAR * const FEEMODELCODE;
   extern CLASS_IMPORT I_CHAR * const FUNDSPONSORCODE;
}

namespace FUNDBROKER_SEARCH_CRITERIA 
{
   extern CLASS_IMPORT I_CHAR * const FUNDBROKER;
}

namespace FUNDBROKER_USING
{
   extern CLASS_IMPORT I_CHAR * const ALLFUNDBROKER;
   extern CLASS_IMPORT I_CHAR * const FUNDBROKERCODE;
   extern CLASS_IMPORT I_CHAR * const FUNDBROKERNAME;
}

namespace AGGREGATION_SEARCH_CRITERIA
{
   extern CLASS_IMPORT I_CHAR * const AGGREGATION;
}



namespace AGGREGATION_USING
{
   extern CLASS_IMPORT I_CHAR * const TRADEDATE;
   extern CLASS_IMPORT I_CHAR * const AGGRORDERNO;
   extern CLASS_IMPORT I_CHAR * const ROUTINGREFNO;
	extern CLASS_IMPORT I_CHAR * const STATUS;
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeaturesSearchProcessIncludes.h-arc  $
//
//   Rev 1.8   Dec 07 2004 12:32:02   zhangcel
//PET1117 FN08 -- Fix crash when switch search using
//
//   Rev 1.7   Nov 26 2004 14:44:10   zhangcel
//PET1117/FN8 -- Aggregated Order related changes
//
//   Rev 1.6   Nov 05 2004 15:42:10   ZHANGCEL
//PET1117/08 Add sreaching logic for AggregatedOrder
//
//   Rev 1.5   Oct 19 2004 14:38:18   FENGYONG
//PET1117 FN54 - Fund Broker Static
//
//   Rev 1.4   Aug 10 2004 11:11:00   FENGYONG
//PET117 FN5 - Client Condition Fee
//
//   Rev 1.3   Feb 03 2004 16:23:30   VADEANUM
//PET 859 FN23 - ADL - removed Fee search param
//
//   Rev 1.2   Jan 28 2004 21:35:14   popescu
//PET 859, FN 23, modified resources (dialogs and menu item) and coded for the features search dialog
//
//   Rev 1.1   Oct 27 2003 19:48:26   popescu
//CIBC PET809, FN 13, added Transit Search by name
//
//   Rev 1.0   Oct 04 2003 16:06:06   popescu
//Initial revision.
//
//   Rev 1.2   Jul 02 2003 17:49:28   popescu
//work for payment instructions feature 
//
//   Rev 1.1   Jun 30 2003 16:56:08   popescu
//added historical info search to the Broker Features search;
//moved some param names to the mfcaniterprocparam namespace
//
//   Rev 1.0   Jun 27 2003 18:15:18   popescu
//Initial revision.
//
 * 
 */

