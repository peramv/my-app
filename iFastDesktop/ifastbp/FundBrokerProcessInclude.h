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
//    Copyright 2002 by Internantional Financial.
//
//******************************************************************************

//#include <ifastdataimpl\dse_dstc0305_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUND_BROKER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FEE_PARAM_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_IDS_LIST;
}
namespace FUNDBROKER
{
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCR;
   
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDBROKER_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCHTYPE;   
   extern IFASTBP_LINKAGE const I_CHAR * const FUNDBROKER_NAME;
   extern IFASTBP_LINKAGE const I_CHAR * const SYSTEM;
   extern IFASTBP_LINKAGE const I_CHAR * const ALL;
   const  BFFieldId NEWITEM(100);
   const  BFFieldId ISNAMEUPDATE(101);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundBrokerProcessInclude.h-arc  $
//
//   Rev 1.1   Nov 04 2004 10:59:36   FENGYONG
//PET1117 FN54 - Fund broker static temp check in for 59 build
//
//   Rev 1.0   Oct 19 2004 14:42:12   FENGYONG
//Initial revision.
 * 
 */