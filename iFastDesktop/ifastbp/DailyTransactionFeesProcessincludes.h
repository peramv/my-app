#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//    AUTHOR : Monica Vadeanu
//    DATE   : Jan 2004
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Inquiry View
#include <ifastdataimpl\dse_dstc0284_vw.hpp>

namespace IFASTBP_PROC
{   
	extern IFASTBP_LINKAGE const BFContainerId DAILY_TRANSACTION_FEES_LIST;
}

namespace ifds
{
   //field ids used, not found in the above view
   extern CLASS_IMPORT const BFTextFieldId    FundName;   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DailyTransactionFeesProcessincludes.h-arc  $
//
//   Rev 1.1   Feb 10 2004 16:26:38   VADEANUM
//PET 859 FN23 - ADL - first working version
//
//   Rev 1.0   Feb 03 2004 16:52:00   VADEANUM
//Initial revision.
*/

