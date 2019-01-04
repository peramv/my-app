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
#include <ifastdataimpl\dse_dstc0250_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0200_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0218_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0090_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId AMS_FUND_ALLOC_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AMSMSTR_LIST;
   extern IFASTBP_LINKAGE const BFContainerId BROKER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId BROKERAMS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId BROKERAMSSEARCH;
}

namespace  BROKE_AMS
{
   extern IFASTBP_LINKAGE const I_CHAR * const REFRESH_ALLOCTION;
	
	const BFFieldId HAS_OBJECT_UPDATE(1001);


}

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int BROKERAMS_LIST = 1;
//CP20030319const int BROKER_LIST = 2;
//CP20030319const int AMSMSTR_LIST = 3;
//CP20030319const int BROKERAMSSEARCH = 4;
//CP20030319const int AMS_FUND_ALLOC_LIST = 5;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//

