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

#include <ifastdataimpl\dse_dstc0340_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId USER_DEF_MAT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId UserDefMatHeading;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/UserDefMatProcessIncludes.h-arc  $
//
//   Rev 1.0   Mar 20 2005 17:19:40   hernando
//Initial revision.
