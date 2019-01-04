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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_req.hpp>
#include <ifastdataimpl\dse_dstc0071_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CRITERIA;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_ADDRESS_LIST;
 }

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId EntityAddressListHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId SearchUsingSet;
 
}

namespace 
{
	const I_CHAR *PARM_SEARCHITEMFOUND      = I_( "SEARCHITEMFOUND" );

}

