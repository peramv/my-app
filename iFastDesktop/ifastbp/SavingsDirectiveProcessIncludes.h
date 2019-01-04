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
// ^FILE   : SavingsDirectiveProcessinclude.h
// ^AUTHOR : 
// ^DATE   : 05 Nov 2005
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

#include <ifastdataimpl\dse_dstc0358_vw.hpp>
#include <ifastdataimpl\dse_dstc0358_req.hpp>

#include <bfproc/bfcontainerid.hpp>

namespace IFASTBP_PROC
{   
   extern IFASTBP_LINKAGE const BFContainerId SAVINGS_DIRECTIVE;
}


namespace SAVINGS_DIRECTIVE
{
   const I_CHAR * const TRANSID     = I_( "TransId" );   
	const I_CHAR * const ACCOUNTNUM = I_( "AccountNum" );   
	const I_CHAR * const FUND = I_( "Fund" );   
	const I_CHAR * const CLASS = I_( "Class" );   
	const I_CHAR * const TIS_TYPE = I_( "TISType" );   
	const I_CHAR * const TIS = I_( "TIS" );   
	const I_CHAR * const COST_TYPE = I_( "CostType" );   
	const I_CHAR * const COST = I_( "Cost" );   
	const I_CHAR * const VERSION = I_( "EUSDOverrideVer" );   
	const I_CHAR * const TRADEDATE = I_( "TradeDate" );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SavingsDirectiveProcessIncludes.h-arc  $
//
//   Rev 1.0   Nov 29 2005 17:02:50   AGUILAAM
//Initial revision.
//
*/



