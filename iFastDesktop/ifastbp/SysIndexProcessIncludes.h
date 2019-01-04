#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : BankInstrProcessIncludes.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 05/01/2001
//
//******************************************************************************

#include <ifastdataimpl\dse_dstc0139_vw.hpp>
#include <ifastdataimpl\dse_dstc0139_req.hpp>
#include <ifastdataimpl\dse_dstc0006_vw.hpp>

#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//name of the substitute list fields
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SYS_INDEX_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SYSTEMATIC;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PayReason;
}              

namespace SYSINDEXLIT
{
   extern IFASTBP_LINKAGE const I_CHAR* const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR* const INSTRUCTION;
   extern IFASTBP_LINKAGE const I_CHAR* const DEFAULT;
}

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace SYS_INDEX_DEF
{
//CP20030319   const int SYS_INDEX_LIST  = 1;
//CP20030319   const int SYSTEMATIC_CBO  = 2;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SysIndexProcessIncludes.h-arc  $
//
//   Rev 1.5   Jun 10 2003 11:48:20   popescu
//change name of the systematic cbo container to be compliant with the standard, re-named the ACCOUNT_DISTRIBUTION_BANK_LIST in ACCOUNT_DISTRIBUTION since nobody was using it, and re-used the id for banking instructions process
//
//   Rev 1.4   Mar 21 2003 17:48:42   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:53:38   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   22 May 2002 18:19:44   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:18:40   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   03 May 2001 13:42:14   BUZILAMI
//Initial revision.
 * 
 *
 */
