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
// ^FILE   : RESPBeneficiaryAllocationListProcessIncludes.cpp
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

#include <ifastdataimpl\dse_dstc0402_Req.hpp> 
#include <ifastdataimpl\dse_dstc0402_VWRepeat_Record.hpp> 
#include <ifastdataimpl\dse_dstc0111_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId RESP_BENEF_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RESP_TRANSACTION;
   extern IFASTBP_LINKAGE const BFContainerId TRANSACTION;
   extern IFASTBP_LINKAGE const BFContainerId PENDING_TRANSACTION;
	extern IFASTBP_LINKAGE const BFContainerId TRADE;
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId RESPBenefAllocHeading;
	extern CLASS_IMPORT const BFTextFieldId TransType;
	extern CLASS_IMPORT const BFTextFieldId GrossOrNet;
   extern CLASS_IMPORT const BFTextFieldId AllowManualDelete;
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
   const I_CHAR *const  TRANSID		= I_( "TransId" );
   const I_CHAR *const  HRDCPending	= I_( "HRDCPending" );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPBeneficiaryAllocationListProcessIncludes.h-arc  $
//
//   Rev 1.4   Oct 27 2010 10:23:38   jankovii
//IN 2305655 - FN03 QESI - RESP Beneficiary Allocation History Button
//
//   Rev 1.3   Mar 31 2010 15:15:32   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.2   Mar 29 2010 23:06:38   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.15   Mar 29 2010 10:49:40   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
*/