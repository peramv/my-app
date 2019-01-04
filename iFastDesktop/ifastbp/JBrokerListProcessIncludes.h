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

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0090_vwrepeat_record.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int BROKER_LIST = 1;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId BROKER_LIST;
}
namespace BROKERLISTLIT  //stands for account details literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const BROKERCODE;  
   extern IFASTBP_LINKAGE const I_CHAR * const BROKERNAME;  
   extern IFASTBP_LINKAGE const I_CHAR * const REQUESTTYPE; 
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JBrokerListProcessIncludes.h-arc  $
 * 
 *    Rev 1.5   Mar 21 2003 17:43:32   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:20:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:17:46   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Mar 24 2000 12:22:48   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:19:46   FENGYONG
// Initial revision.
// 
// Initial revision.
 * 
 *
 */

