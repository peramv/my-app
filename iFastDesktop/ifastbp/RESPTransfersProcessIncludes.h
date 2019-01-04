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

//******************************************************************************
//
// ^FILE   : RESPTransfersIncludes.cpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0406_Req.hpp> 
#include <ifastdataimpl\dse_dstc0406_VW.hpp> 
#include <ifastdataimpl\dse_dstc0406_VWRepeat_Record.hpp> 
#include <ifastdataimpl\dse_dstc0111_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>

namespace RECORD_LEVEL
{
   extern CLASS_IMPORT const I_CHAR *BENEFICIARY; 
   extern CLASS_IMPORT const I_CHAR *ACCOUNT; 
}

const BFFieldId IsAcctLevelOverrideApplicable (20000, I_("IsAcctLevelOverrideApplicable"));
const BFFieldId ReadBeneDefaults (20001, I_("ReadBeneDefaults"));
const BFFieldId IsInternalTransfer (20002, I_("IsInternalTransfer"));
const BFFieldId IsAnyRESPBenefQCResident (20003, I_("IsAnyRESPBenefQCResident"));  


// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId RESP_TRANSFER_LIST;
	extern IFASTBP_LINKAGE const BFContainerId RESP_TRANSFER_PLAN;
	extern IFASTBP_LINKAGE const BFContainerId RESP_BENEF_ALLOC_LIST;
	extern IFASTBP_LINKAGE const BFContainerId RESP_TRANSACTION;
	extern IFASTBP_LINKAGE const BFContainerId TRANSACTION;
	extern IFASTBP_LINKAGE const BFContainerId PENDING_TRANSACTION;
	extern IFASTBP_LINKAGE const BFContainerId TRADE;
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId RESPTransferHeading;
	extern CLASS_IMPORT const BFTextFieldId TransType;
	extern CLASS_IMPORT const BFTextFieldId GrossOrNet;
	extern CLASS_IMPORT const BFTextFieldId RESPQCResidentFound;
}

namespace
{
   const I_CHAR * const CALLER = I_("Caller");
   const I_CHAR * const ACCOUNT_NUM = I_("AccountNum");
   const I_CHAR * const TRADE_LIST_KEY = I_("ListKey");
   const I_CHAR * const RESP_TRANS_LIST_KEY = I_("RESP_TransListKey");
   const I_CHAR * const DECIMAL_DIGITS = I_("DecimalDigits");
   const I_CHAR * const HISTORY_PENDING_FIELD = I_( "HistoryPending" );
   const I_CHAR * const TRANS_HIST = I_( "RESPTransactionsDlg" );
   const I_CHAR * const TRADE_ENTRY = I_( "TradeEntry" );
   const I_CHAR * const TRANS_TYPE = I_( "TransType" );
   const I_CHAR * const DEPOSIT_TYPE = I_( "DepositType" );
   const I_CHAR * const RED_CODE = I_( "RedCode" );
}

/* $Log::   
*/