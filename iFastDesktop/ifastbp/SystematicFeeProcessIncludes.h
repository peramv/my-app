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

// Should include data set includes used by entity here
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0006_req.hpp>
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0007_req.hpp>
#include <ifastdataimpl\dse_dstc0007_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_req.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int SYSTEMATIC_LIST           = 1;
//CP20030319const int MFACCOUNT_CBO             = 2;
//CP20030319const int FUND_DETAIL_LIST          = 3;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId SYSTEMATIC_LIST;
}
namespace SYSTEMATICFEELIT
{
   extern const I_CHAR * const ACCOUNT_NUM;
   extern const I_CHAR * const LIST_KEY;

   const BFFieldId PRIMARY_ACCOUNT_OWNER(600);
}
