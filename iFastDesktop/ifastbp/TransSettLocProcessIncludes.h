#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransSettLocProcessIncludes.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransSettLocProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <dataimpl\dse_dstc0004_vw.hpp>
#include <dataimpl\dse_dstc0022_vw.hpp>
#include <dataimpl\dse_dstc0054_vw.hpp>
#include <dataimpl\dse_dstc0115_req.hpp>
//#include <dataimpl\dse_dstcglob_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ORIGINAL_TRADE_CBO;   
	extern IFASTBP_LINKAGE const BFContainerId FROM_TRANS_SETTLEMENT_LOCATION_CBO;   
	extern IFASTBP_LINKAGE const BFContainerId TO_TRANS_SETTLEMENT_LOCATION_CBO;   
	extern IFASTBP_LINKAGE const BFContainerId FROM_ACCOUNT_CBO;   
	extern IFASTBP_LINKAGE const BFContainerId TO_ACCOUNT_CBO;   
}

namespace TRANS_SETTLEMENT_LOCATION
{   
	//parameters
	const I_CHAR * const ACCOUNT               = I_("FromAccount");	
	// what screen launched this process   
	const I_CHAR * const FROM_SCREEN           = I_("FromScreen");
	// if it's from the Transaction History screen, is it History or Pending mode?
	// Y for Pending, N for History, blank if not from Transaction History	
	const I_CHAR * const PENDING_HISTORY       = I_("PendingHistory");
	// List Item Key	
	const I_CHAR * const MAIN_LIST_KEY         = I_("MainListKey");

	const I_CHAR * const FROM_CLEARING_ACCOUNT = I_("FromClearingAccount");
	const I_CHAR * const TO_CLEARING_ACCOUNT   = I_("ToClearingAccount");

}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/TransSettLocProcessIncludes.h-arc  $
//
//   Rev 1.2   Nov 26 2003 13:57:46   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support.
//
//   Rev 1.1   Nov 25 2003 11:48:44   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support.
//
//   Rev 1.0   Nov 10 2003 15:24:14   VADEANUM
//Initial revision.
//
