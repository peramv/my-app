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
// ^FILE   : TradeSettleLocationsProcessIncludes.cpp
// ^AUTHOR :  
// ^DATE   : July, 2009
//
// -----------------------------------------------------------------------------


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0397_req.hpp> 
#include <ifastdataimpl\dse_dstc0397_vwrepeat_record.hpp> 

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId TRADE;
	extern IFASTBP_LINKAGE const BFContainerId TRADE_MULTI_SETTLEMENT_LOC_LIST;
}

