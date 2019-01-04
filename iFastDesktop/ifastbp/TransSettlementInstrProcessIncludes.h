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
// ^FILE   : TransSettlementInstrProcessIncludes.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransSettlementInstrProcess
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

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_vw.hpp>
#include <ifastdataimpl\dse_dstc0115_req.hpp>
//#include <ifastdataimpl\dse_dstcglob_vw.hpp>

const BFFieldId IsClearingAcct (10001, I_("IsClearingAccount"));

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ORIGINAL_TRADE_CBO;   
//	extern IFASTBP_LINKAGE const BFContainerId FROM_TRANS_SETTLEMENT_LOCATION_CBO;   
//	extern IFASTBP_LINKAGE const BFContainerId TO_TRANS_SETTLEMENT_LOCATION_CBO;   
	extern IFASTBP_LINKAGE const BFContainerId FROM_ACCOUNT_CBO;   
	extern IFASTBP_LINKAGE const BFContainerId TO_ACCOUNT_CBO;   
}

namespace TRANS_SETTLEMENT_LOCATION
{   
	//parameters
	extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT;
	// what screen launched this process   
	extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCREEN;
	// if it's from the Transaction History screen, is it History or Pending mode?
	// Y for Pending, N for History, blank if not from Transaction History	
	extern IFASTBP_LINKAGE const I_CHAR * const PENDING_HISTORY;
	// List Item Key	
	extern IFASTBP_LINKAGE const I_CHAR * const MAIN_LIST_KEY;
	extern IFASTBP_LINKAGE const I_CHAR * const FROM_CLEARING_ACCOUNT;
	extern IFASTBP_LINKAGE const I_CHAR * const TO_CLEARING_ACCOUNT;
   extern IFASTBP_LINKAGE const I_CHAR * const SIDE;
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/TransSettlementInstrProcessIncludes.h-arc  $
//
//   Rev 1.3   Nov 29 2004 20:30:10   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.2   Nov 25 2004 14:58:46   popescu
//PET 1117/06, settle locations
//
//   Rev 1.1   Nov 24 2004 21:35:30   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.0   Oct 14 2004 12:28:30   VADEANUM
//Initial revision.
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
