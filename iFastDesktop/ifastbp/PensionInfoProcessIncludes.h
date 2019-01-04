#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************

#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0202_vw.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId PENSION_INFO;
}
namespace PENSION_INFO
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );   
   const I_CHAR * const REFRESH = I_( "Refresh" );   
//CP20030319   const int PENSION_INFO = 1;
//CP20030319   const int MFACCOUNT_CBO = 2;
   const BFFieldId PORTION_CURRENT_MARKET_VALUE(10);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PensionInfoProcessIncludes.h-arc  $
//
//   Rev 1.4   Mar 21 2003 17:45:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:53:32   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Aug 29 2002 12:53:12   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.1   Aug 09 2002 16:13:08   HSUCHIN
//added refresh tag
//
//   Rev 1.0   Jun 02 2002 17:59:12   HSUCHIN
//Initial revision.
 */
