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
// ^FILE   : ProgressiveIntRateProcessIncludes.h
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

#include <ifastdataimpl\dse_dstc0423_req.hpp>
#include <ifastdataimpl\dse_dstc0423_vwrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0423_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId PROGRESSIVE_INTEREST_RATE_LIST;
}

namespace PROGINTRATE
{
	//Fields names
	const I_CHAR * const TRANS_ID_VALUE		= I_( "TransId" );
	const I_CHAR * const ACCOUNT_NUM_VALUE	= I_( "AccountNum" );
	const I_CHAR * const INVEST_ID			= I_( "InvHisInvestId" );

	const I_CHAR * const FUND				= I_( "InvestmentHistoryClass" );
	const I_CHAR * const CLASS				= I_( "InvestmentHistoryFund" );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ProgressiveIntRateProcessIncludes.h-arc  $
//
//   Rev 1.1   Dec 01 2011 18:02:46   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.0   Nov 27 2011 21:15:14   wp040100
//Initial revision.
//
//
 * 
 * 
// 
*/