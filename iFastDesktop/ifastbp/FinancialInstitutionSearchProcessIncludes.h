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
//    DATE   : October, 2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0100_vw.hpp>
#include <ifastdataimpl\dse_dstc0100_req.hpp>

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
   extern CLASS_IMPORT const BFTextFieldId FillSearchType;
   //heading sets, for F4 search
   extern CLASS_IMPORT const BFTextFieldId TransitsSearchHeading;
   extern CLASS_IMPORT const BFTextFieldId FinancialInstitutionsSearchHeading;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SEARCH_CRITERIA_FILLER;
   extern IFASTBP_LINKAGE const BFContainerId FINANCIAL_INSTITUTION_LIST;
}

namespace SEARCH_TYPE
{
   extern CLASS_IMPORT I_CHAR * const FI_FEATURES;
   extern CLASS_IMPORT I_CHAR * const FI_FEATURES_F4;
}

namespace FI_SEARCH_CRITERIA
{
   extern CLASS_IMPORT I_CHAR * const INSTITUTIONS_F4;
}

namespace FI_SEARCH_INSTITUTIONS_F4_USING
{
   extern CLASS_IMPORT I_CHAR * const NAME;
   extern CLASS_IMPORT I_CHAR * const CODE;
}

namespace FI_CATEGORY
{
   extern CLASS_IMPORT I_CHAR * const BANK;
   extern CLASS_IMPORT I_CHAR * const BANK_TRANSIT;
   extern CLASS_IMPORT I_CHAR * const INSTITUTION;
   extern CLASS_IMPORT I_CHAR * const INSTITUTION_TRANSIT;
   extern CLASS_IMPORT I_CHAR * const OTHER;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FinancialInstitutionSearchProcessIncludes.h-arc  $
//
//   Rev 1.0   Oct 04 2003 16:06:12   popescu
//Initial revision.
//
 */

