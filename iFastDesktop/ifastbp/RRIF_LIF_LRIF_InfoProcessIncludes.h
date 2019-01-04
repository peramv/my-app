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

#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0064_vw.hpp>
#include <ifastdataimpl\dse_dstc0067_vw.hpp>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0130_vw.hpp>
#include <ifastdataimpl\dse_dstc0130_req.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>


namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_LIF_LRIF_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_LIF_LRIF_CALCULATE_ADD;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_LIF_LRIF_CALCULATE_MODIFY;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_LIF_LRIF_INFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_FROM_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RRIF_TO_ALLOC_LIST;


}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddress;
   extern CLASS_IMPORT const BFTextFieldId MonthIndicator;
   extern CLASS_IMPORT const BFTextFieldId RRIFSrcOfFund; 
   extern CLASS_IMPORT const BFTextFieldId RRIFSrcOfAcct; 
}


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace RRIF_LIF_LRIF
{
   const BFFieldId ORG_KEY(1100);
   const BFFieldId DEST_KEY(1200);
   const BFFieldId IS_ORIGPLANDEFFAPPLIED(1300);

   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const LAST_NAME_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const FIRST_NAME_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const RRIF_LIF_LRIF;
   const BFFieldId AreAllRRIFRecordsInactive (8000);//added for CHG0041174
}

