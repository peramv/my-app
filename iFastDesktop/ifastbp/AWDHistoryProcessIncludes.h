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
//    Copyright 2013 by DST Systems, Inc.
//
//******************************************************************************

#include <ifastdataimpl\dse_awdhistwrk_vw.hpp>
#include <ifastdataimpl\dse_awdhistsrc_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId AWDWORK_LIST;
   extern IFASTBP_LINKAGE const BFContainerId AWDSOURCE_LIST;
}

namespace AWDHIST_PROC
{
   const BFFieldId AWDImageAuth(10001, I_("AWDImageAuth"));

}
