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
// ^FILE   : MatSweepInstructionsListProcessIncludes.cpp
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

#include <ifastdataimpl\dse_dstc0427_req.hpp> 
#include <ifastdataimpl\dse_dstc0427_vwrepeat_record.hpp> 
#include <ifastdataimpl\dse_dstc0428_req.hpp> 
#include <ifastdataimpl\dse_dstc0428_vwrepeat_record.hpp> 
#include <ifastdataimpl\dse_dstc0429_req.hpp> 
#include <ifastdataimpl\dse_dstc0429_reqrepeat_record.hpp> 

const BFContainerId SHAREHOLDER_ADDRESS (1);

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MAT_SWEEP_INSTRUCTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MAT_SWEEP_INSTR_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId TRADE;
   extern IFASTBP_LINKAGE const BFContainerId INVESTMENT_HISTORY_LIST;
}

const BFFieldId IsInstrCopyAllowed (101, I_("IsInstrCopyAllowed"));

namespace
{
	const I_CHAR * const CALLER			= I_("Caller");
	const I_CHAR * const INSTR_TYPE		= I_("InstrType");
	const I_CHAR * const COA			= I_("AcctCOA");
	const I_CHAR * const TRADE			= I_("TradeEntry");
	const I_CHAR * const INV_HISTORY	= I_("InvHistory");
	const I_CHAR * const ACCOUNT_NUM	= I_("AccountNum");
	const I_CHAR * const TRANS_ID_VALUE	= I_( "TransId" );
	const I_CHAR * const INVEST_ID		= I_( "InvHisInvestId" );
	const I_CHAR * const FUND			= I_( "InvestmentHistoryClass" );
	const I_CHAR * const CLASS			= I_( "InvestmentHistoryFund" );
	const I_CHAR * const TRANS_NUM		= I_("TransNum");
	const I_CHAR * const INV_NUM		= I_( "InvestmentHistoryNumber" );
	const I_CHAR * const INV_STATUS		= I_( "InvestmentHistoryStatus" );
	const I_CHAR * const SEARCHBY		= I_( "InvestmentHistorySearch" );
    const I_CHAR * const TRADE_LIST_KEY = I_("ListKey");
	const I_CHAR * const LIST_KEY_INV	= I_("ListKeyInvestment");
	const I_CHAR * const LIST_KEY_DETL	= I_("ListKeyDetail");
    const I_CHAR * const INV_PRINCIPAL  = I_( "PrincipalAmount" );
    const I_CHAR * const INV_ACCRUED	= I_( "AccruedAmount " );
	const I_CHAR * const CALC_METHOD	= I_( "CalcMethod" );
	const I_CHAR * const INV_TYPE		= I_( "InvType" );
	const I_CHAR * const TERM			= I_( "Term" );
	const I_CHAR * const FREQEUNCY		= I_( "Freqeuncy" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId MatSweepInstructListHeading;
	extern CLASS_IMPORT const BFTextFieldId MatSweepInstructDetailsListHeading;
	extern CLASS_IMPORT const BFTextFieldId MatInstrLevel;
	extern CLASS_IMPORT const BFTextFieldId Address;
	extern CLASS_IMPORT const BFNumericFieldId ShrNum;
	//address related fields
	extern CLASS_IMPORT const BFTextFieldId MatInstrAddress;
	extern CLASS_IMPORT const BFTextFieldId Name;
	extern CLASS_IMPORT const BFTextFieldId Name1;
	extern CLASS_IMPORT const BFTextFieldId Name2;
	extern CLASS_IMPORT const BFTextFieldId AddrLine1;
	extern CLASS_IMPORT const BFTextFieldId AddrLine2;
	extern CLASS_IMPORT const BFTextFieldId AddrLine3;
	extern CLASS_IMPORT const BFTextFieldId AddrLine4;
	extern CLASS_IMPORT const BFTextFieldId AddrLine5;
	extern CLASS_IMPORT const BFTextFieldId PostalCode;
	extern CLASS_IMPORT const BFTextFieldId CountryCode;
	extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
	extern CLASS_IMPORT const BFTextFieldId InvHisStatus;
}
