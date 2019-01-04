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


const BFFieldId IsSearchCriteria1Broker(1);
const BFFieldId IsSearchCriteria2Branch(2);
const BFFieldId IsSearchCriteria3SlsRep(3);

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
   //fields
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria1;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria2;
   extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria3;
   extern CLASS_IMPORT const BFTextFieldId HowManySearchCriterias;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SEARCH_CRITERIA_FILLER;
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

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerFeaturesSearchProcessIncludes.h-arc  $
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

