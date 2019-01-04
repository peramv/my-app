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
//    Copyright 2003 International Financial Data Services
//    AUTHOR : Yong Mei Feng
//    DATE   : August 2003
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

//include the data sets
#include <dataimpl\dse_substitute_vw.hpp>
#include <dataimpl\dse_dstc0004_vw.hpp>
#include <dataimpl\dse_dstc0069_vw.hpp>
#include <dataimpl\dse_dstc0115_req.hpp>
#include <dataimpl\dse_dstcglob_vw.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRADES_LIST;
}

namespace TRADE_TAXRATE_PARAM
{
	extern IFASTBP_LINKAGE const I_CHAR * const MAIN_LIST_KEY;
	extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
	extern IFASTBP_LINKAGE const I_CHAR * const TRANSACTION_TYPE;

	extern IFASTBP_LINKAGE const I_CHAR * const OVERRIDE_TAX;
	extern IFASTBP_LINKAGE const I_CHAR * const FED_TAX_RATE;
	extern IFASTBP_LINKAGE const I_CHAR * const PROV_TAX_RATE;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradesTaxRateProcessIncludes.h-arc  $
//
//   Rev 1.2   Sep 24 2003 10:41:24   VADEANUM
//PTS 10021736 - Withholding Tax Default Rates.
//
//   Rev 1.1   Sep 23 2003 12:36:02   VADEANUM
//PTS 10021736 - Withholding Tax Default Rates.
//
//   Rev 1.0   Aug 15 2003 10:26:56   FENGYONG
//Initial Revision
 * 
*/

