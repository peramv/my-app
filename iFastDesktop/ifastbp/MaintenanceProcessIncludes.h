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
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by entity here

// Defining fields to use



// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0088_vwrepeat_record.hpp>

//CP20030319const int GROUP_LIST = 1;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId GROUP_LIST;
}
namespace MAINTLIT  //stands for account details literals
{

   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const PHONE_NUM_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const ALT_ACCOUNT_NUM_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const BROKER_CODE_FIELD;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MaintenanceProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 21 2003 17:44:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:28   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:20:32   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:17:54   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Aug 14 2000 17:29:42   FENGYONG
//Add fields
//
//   Rev 1.0   Aug 02 2000 13:44:22   VASILEAD
//Initial revision.
 * 
 */
