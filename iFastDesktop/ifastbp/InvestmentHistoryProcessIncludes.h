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
// ^FILE   : InvestmentHistoryProcessIncludes.h
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

#include <ifastdataimpl\dse_dstc0421_req.hpp>
#include <ifastdataimpl\dse_dstc0421_vwrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0421_vw.hpp>

#include <ifastdataimpl\dse_dstc0424_req.hpp>
#include <ifastdataimpl\dse_dstc0424_vwrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0424_vw.hpp>

#include <ifastdataimpl\dse_dstc0425_req.hpp>
#include <ifastdataimpl\dse_dstc0425_vwrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0425_vw.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
const BFContainerId INVESTMENT_HISTORY_SEARCH (1001);

namespace IFASTBP_PROC
{
   //extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId INVESTMENT_HISTORY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INVESTMENT_HISTORY_TRAN_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INVESTMENT_HISTORY_INT_LIST;
}

namespace INVHISTORYPROC	//stands for investment history process -
{
	//Fields names
	const I_CHAR * const TRANS_ID_VALUE		= I_( "TransId" );
	const I_CHAR * const TRANS_NUM			= I_("TransNum");
	const I_CHAR * const ACCOUNT_NUM_VALUE	= I_( "AccountNum" );
	const I_CHAR * const INVEST_ID			= I_( "InvHisInvestId" );
	const I_CHAR * const INV_PRINCIPAL		= I_( "PrincipalAmount" );
    const I_CHAR * const INV_ACCRUED		= I_( "AccruedAmount " );

	const I_CHAR * const FUND				= I_( "InvestmentHistoryClass" );
	const I_CHAR * const CLASS				= I_( "InvestmentHistoryFund" );
	const I_CHAR * const INV_NUM			= I_( "InvestmentHistoryNumber" );
	const I_CHAR * const INV_STATUS			= I_( "InvestmentHistoryStatus" );
	const I_CHAR * const SEARCHBY			= I_( "InvestmentHistorySearch" );
	const I_CHAR * const CALC_METHOD		= I_( "CalcMethod" );
	const I_CHAR * const INV_TYPE			= I_( "InvType" );
	const I_CHAR * const TERM				= I_( "Term" );
	const I_CHAR * const FREQEUNCY			= I_( "Freqeuncy" );

}