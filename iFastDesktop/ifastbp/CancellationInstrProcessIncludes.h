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
//
// ^FILE   : CancellationInstrProcess.h
// ^AUTHOR : 
// ^DATE   : 10/30/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <bfproc/bfcontainerid.hpp>
#include <ifastbp\TransCancelProcessincludes.h>

namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId CRITERIA; 
   extern IFASTBP_LINKAGE const BFContainerId CANCELLATION_INSTR_LIST;   
}

namespace CANCEL_INSTR
{
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_TYPE;
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_USING;
}




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CancellationInstrProcessIncludes.h-arc  $
//
//   Rev 1.1   Nov 24 2005 16:20:18   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.0   Nov 04 2005 11:40:06   ZHANGCEL
//Initial revision.
 */

