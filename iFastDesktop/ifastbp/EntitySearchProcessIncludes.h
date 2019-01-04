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
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Need to define list and search Id's to be used by a GUI object talking to the
// process.

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_IDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_SEARCH_LIST;
}
namespace ENTSRCHLIT //entity search literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const FIRST_VALUE;
   extern IFASTBP_LINKAGE const I_CHAR * const SECOND_VALUE;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR * const TRADE_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR * const ALLENTITY;
   extern IFASTBP_LINKAGE const I_CHAR * const EXACTSEARCH;
   extern IFASTBP_LINKAGE const I_CHAR * const WHERE_USED_CODE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId VerifySearchHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId EntityIDSHeadingSet;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntitySearchProcessIncludes.h-arc  $
 * 
 *    Rev 1.8   Apr 27 2012 09:51:54   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.7   12 Jul 2007 18:41:10   popescu
 * GAP 6 - CIF - added two new search types on the main screen - by CIF and by AccessID
 * 
 */
