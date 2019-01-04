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
//    AUTHOR : Shaobo Huang
//    DATE   : 17/09/99
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here
#include <ifastdataimpl\dse_dstc0061_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Need to define list and search Id's to be used by a GUI object talking to the
// process.

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId WHEREUSED_LIST;
}
namespace WHEREUSEDPROC
{
//CP20030319   const int WHEREUSED_LIST = 1;

   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_NAME;
   extern IFASTBP_LINKAGE const I_CHAR * const BIRTHENTITY_NAME;
   extern IFASTBP_LINKAGE const I_CHAR * const CALLER;
   extern IFASTBP_LINKAGE const I_CHAR * const WHEREUSEDLG;

}


