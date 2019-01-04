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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

#include <ifastdataimpl\dse_dstc0090_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId BROKER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_BROKER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FAMILY_CODE_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SearchBroker;
   extern CLASS_IMPORT const BFTextFieldId SearchBrokerUsing;
   extern CLASS_IMPORT const BFTextFieldId BrokerListHeading;
   extern CLASS_IMPORT const BFTextFieldId BrokerListHeadingPayments;
   extern CLASS_IMPORT const BFTextFieldId BrokerListHeadingFundBroker;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerProcessIncludes.h-arc  $
 * 
 *    Rev 1.8   Nov 08 2011 11:56:06   dchatcha
 * P0188902 FN02 - DYN Household Project
 * 
 *    Rev 1.7   Mar 25 2009 07:26:14   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search.
 * 
 *    Rev 1.6   Jul 10 2003 22:19:42   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.5   Mar 21 2003 17:37:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:21:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:15:22   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Feb 15 2000 18:56:18   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:00   SMITHDAV
 * Initial revision.
// 
//    Rev 1.1   Jan 22 2000 15:42:16   WINNIE
// To get search work

  */


