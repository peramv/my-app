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
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0334_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MSG_DETAIL_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId MsgDetailHeading;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MSG_DETAIL;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/MsgDetailProcessIncludes.h-arc  $
//
//   Rev 1.0   Feb 21 2005 11:09:02   hernando
//Initial revision.
