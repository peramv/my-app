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
// FILE   : RDSPTransfersProcessIncludes.cpp
// AUTHOR :  
// DATE   : 
//
// -----------------------------------------------------------------------------


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0488_req.hpp> 
#include <ifastdataimpl\dse_dstc0488_vw.hpp> 

// Need to define list and search ID's to be used by a GUI object talking to the process.
namespace IFASTBP_PROC
{	
	extern IFASTBP_LINKAGE const BFContainerId TRADE;	
	extern IFASTBP_LINKAGE const BFContainerId RDSP_TRANSFER;

}

namespace ifds
{	
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId GrantAmountNA;
	extern CLASS_IMPORT const BFTextFieldId ExtAccount;
	extern CLASS_IMPORT const BFTextFieldId ExtSpecimenPlanNo;
	extern CLASS_IMPORT const BFDecimalFieldId NontaxContrib;
	extern CLASS_IMPORT const BFDecimalFieldId Rollovers;
	extern CLASS_IMPORT const BFDecimalFieldId CDSGrant;
	extern CLASS_IMPORT const BFDecimalFieldId CDSBond;
	extern CLASS_IMPORT const BFDecimalFieldId CurrYrFMV;
	extern CLASS_IMPORT const BFDecimalFieldId PrevYrGrantBond;
	extern CLASS_IMPORT const BFDecimalFieldId PrevYrContrib;
	extern CLASS_IMPORT const BFDecimalFieldId PrevYrNonTaxRedAmt;
	extern CLASS_IMPORT const BFDecimalFieldId PrevYrTaxRedAmt;
	extern CLASS_IMPORT const BFDecimalFieldId CurrYrNonTaxRedAmt;
	extern CLASS_IMPORT const BFDecimalFieldId CurrYrTaxRedAmt;
}

namespace
{
   const I_CHAR * const CALLER = I_("Caller");
   const I_CHAR * const ACCOUNT_NUM = I_("AccountNum");
   const I_CHAR * const TRADE_LIST_KEY = I_("ListKey"); 
   const I_CHAR * const DECIMAL_DIGITS = I_("DecimalDigits");  
   const I_CHAR * const TRADE_ENTRY = I_( "TradeEntry" );
   const I_CHAR * const TRANS_TYPE = I_( "TransType" );
   const I_CHAR * const DEPOSIT_TYPE = I_( "DepositType" );
   const I_CHAR * const RED_CODE = I_( "RedCode" );
}
