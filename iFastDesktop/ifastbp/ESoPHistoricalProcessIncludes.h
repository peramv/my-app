#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0178_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ESOP_HISTORICAL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
}
namespace ESOP_HISTORICAL
{
//container IDs
//CP20030319   const int MFACCOUNT             =  1;
//CP20030319   const int ESOP_HISTORICAL_LIST =  2;

   const I_CHAR * const ACCOUNT_NUMBER   = I_( "AccountNum" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId EsopHistoricalHeadingSet;
}

