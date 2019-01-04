#pragma once
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MgmtCoRefreshProcessIncludes.h-arc  $
//
//   Rev 1.3   Mar 21 2003 17:45:06   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   22 May 2002 18:20:20   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:18:00   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   09 Jul 2001 15:29:40   SMITHDAV
//Initial revision.
 */
namespace IFASTBP_PROC
{
}
