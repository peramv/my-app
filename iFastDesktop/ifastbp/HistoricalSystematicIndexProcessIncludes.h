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

#include <ifastdataimpl\dse_dstc0160_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_substitute_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId HISTORICAL_SYSTEMATIC_INDEX_LIST;
}
namespace HISTSYSINDEX
{
   extern IFASTBP_LINKAGE const I_CHAR * const PARM_TRANSACTIONNUMBER;
}

//CP20030319const int HISTORICAL_SYSTEMATIC_INDEX_LIST = 1;

