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

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0020_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0020_req.hpp>
#include <ifastdataimpl\dse_dstc0020_vw.hpp>

//name of the params used at transfering the search criteria to the business process 

//CP20030319const int HISTORICAL_MARKET_VALUE_LIST = 1;
//CP20030319const int FUND_DETAIL_LIST = 2;
//CP20030319const int MFACCOUNT_CBO = 3;


namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId HISTORICAL_MARKET_VALUE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}
namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ACBSettlPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId MktValSettlPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId ACBTotalPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId MktValTotalPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId FundGroupTotalSettledValue;
}

const BFFieldId AMT_INV_APPL(10135, I_("AMT_INV_APPL"));
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalMarketValueProcessIncludes.h-arc  $
 * 
 *    Rev 1.9   Mar 21 2003 17:41:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Feb 17 2003 14:23:54   popescu
 * Added a field for th calculation of the total market value by FundGroup
 * 
 *    Rev 1.7   Oct 09 2002 23:53:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   22 May 2002 18:20:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:17:28   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Feb 05 2002 10:39:50   YINGBAOL
 * file clean up
 * 
 *    Rev 1.3   28 Dec 2001 14:53:26   KOVACSRO
 * Removed HISTORICAL_MARKET_VALUE.
 * 
 *    Rev 1.2   Jul 07 2000 10:21:50   ZHANGCEL
 * Changed for C2 improvment
 * 
 *    Rev 1.1   Feb 15 2000 18:56:32   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
