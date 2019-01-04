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
//    Copyright 2002 by Internantional Financial.
//
//******************************************************************************


#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_dstc0323_vw.hpp>
#include <ifastdataimpl\dse_dstc0323_req.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId AGGREGATED_ORDER_LIST;
	extern IFASTBP_LINKAGE const BFContainerId PENDING_TRADE;
//	extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   
}
namespace AGGREGATE
{
   
	const I_CHAR * const FROM_DATE				= I_( "FromDate" );
	const I_CHAR * const TO_DATE					= I_( "ToDate" ); 
	const I_CHAR * const STATUS					= I_( "Status" ); 
	const I_CHAR * const FUND_BROKER_CODE		= I_( "FundBroker" ); 
	const I_CHAR * const FUND_CODE				= I_( "FundCode" ); 
	const I_CHAR * const AGGR_ORDER_NUMBER		= I_( "OmnibusID" ); 
	const I_CHAR * const ROUTING_REF_NUMBER	= I_( "RoutingRef" ); 
	const I_CHAR * const ALL						= I_( "All" ); 
	const I_CHAR * const SEARCH_TYPE				= I_( "SearchType" ); 
	const I_CHAR * const WKN						= I_( "FundWKN" );
	const I_CHAR * const ISIN						= I_( "FundISIN" );
}


namespace AGGREGATE_SEARCHTYPE
{
	const I_CHAR * const BY_TRADE_DATE				= I_( "DEFF" );
	const I_CHAR * const BY_AGGR_ORD_NUM			= I_( "AORDNUM " );
	const I_CHAR * const BY_ROUT_REF_NUM			= I_( "ROUTREF" );
	const I_CHAR * const BY_ORDER_STATUS			= I_( "ORDSTAT" );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AggregatedOrderProcessInclude.h-arc  $
//
//   Rev 1.5   Jan 14 2005 15:07:52   zhangcel
//Fix currency display issue
//
//   Rev 1.4   Dec 15 2004 18:48:12   zhangcel
//PET1117-FN08 -- Changed Routing search type
//
//   Rev 1.3   Dec 09 2004 17:58:30   zhangcel
//PET1117 - FN 08 -- Add FundDetailList
//
//   Rev 1.2   Nov 26 2004 16:16:34   zhangcel
//PET 1117 FN08 -- Added two parameters
//
//   Rev 1.1   Nov 19 2004 16:52:40   zhangcel
//PET 1117 FN 8 -- Namespace problem 
//
//   Rev 1.0   Nov 18 2004 17:22:20   zhangcel
//Initial revision.
 * 
 */