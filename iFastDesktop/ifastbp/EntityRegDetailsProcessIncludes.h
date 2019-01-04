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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : EntityRegDetailsProcessIncludes.h
// ^AUTHOR : 
// ^DATE   : 23 December 2013
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

//#include <ifastdataimpl\dse_dstc0301_vw.hpp>
//#include <ifastdataimpl\dse_dstc0301_vwrepeat_record.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

const BFFieldId EntityCaption (10000, I_("EntityCaption"));
const BFFieldId DefaultRadioBox (10001, I_("DefaultRadioBox"));
const BFFieldId ShrCaption (10002, I_("ShrCaption"));
const BFFieldId AccountCaption (10003, I_("AccountCaption"));
// Need to define list and search ID's to be used by a GUI object talking to the
// process.

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_REG_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_REG_JURIS_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_LIST;
}

namespace ifds
{   
   //extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}