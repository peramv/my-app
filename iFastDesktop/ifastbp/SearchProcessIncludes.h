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

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//name of the params used at transfering the search criteria to the business process
namespace IFASTBP_PROC
{
}

namespace SRCHLIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_CRITERIA_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_USING_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const FIRST_VALUE;
   extern IFASTBP_LINKAGE const I_CHAR * const SECOND_VALUE;
   extern IFASTBP_LINKAGE const I_CHAR * const THIRD_VALUE;
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR * const BACKGROUND_SEARCH;
   extern IFASTBP_LINKAGE const I_CHAR * const ALLENTITY;
   extern IFASTBP_LINKAGE const I_CHAR * const EXACTSEARCH;
};

namespace MFCAN_IP_PARAM
{
   extern IFASTBP_LINKAGE const I_CHAR * const OTHER_REF_NUMBER;
};

namespace ACCDETLIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SearchProcessIncludes.h-arc  $
 * 
 *    Rev 1.9   Nov 05 2004 16:25:32   FENGYONG
 * PET1117 FN54 Fund Broker Static : Add AllEntityField and ExactSearch 
 * 
 *    Rev 1.8   Oct 01 2004 16:20:32   FENGYONG
 * PET1117FN54 - FundBroker Static
 * 
 *    Rev 1.7   Jun 27 2003 18:13:20   popescu
 * Pay To Entity feature, dialog, process and CBO
 * 
 *    Rev 1.6   Mar 21 2003 17:47:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:53:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:19:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:26   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   07 Mar 2001 15:41:56   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:48   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:22   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.5   Dec 02 1999 17:57:02   POPESCUS
 * Fixed crashes in search
 * 
 *    Rev 1.4   Oct 18 1999 09:48:12   POPESCUS
 * New search criterias
 * 
 *    Rev 1.3   Jul 28 1999 13:16:08   POPESCUS
 * Added a new process for entity search
 * 
 *    Rev 1.2   Jul 23 1999 10:20:40   POPESCUS
 * Added a new process that will fill the dstc front end combos
 * 
 *    Rev 1.1   Jul 08 1999 10:03:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
