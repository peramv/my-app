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

//******************************************************************************
//
// ^FILE   : RedDocumentListProcessIncludes.cpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0390_req.hpp> 
#include <ifastdataimpl\dse_dstc0390_reqrepeat_record.hpp> 

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId DOCUMENT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
}

const BFFieldId CrtEntityId (10001, I_("CrtEntityId"));
const BFFieldId DeathEntityId (10002, I_("DeathEntityId"));
const BFFieldId TaxCompliantEntityId (10003, I_("TaxCompliantEntityId"));
const BFFieldId AccountholderRiskEntityId (10004, I_("AccountholderRiskEntityId"));
const BFFieldId HasRegStandard (10005, I_("HasRegStandard"));
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId RegDocName;
   extern CLASS_IMPORT const BFTextFieldId DocumentListHeading;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFTextFieldId Username;
}
