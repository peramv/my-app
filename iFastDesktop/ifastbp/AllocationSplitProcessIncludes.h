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
//    AUTHOR : Serban Popescu
//    DATE   : June 2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AllowMultiFundTransfer;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllocationSplitProcessIncludes.h-arc  $
//
//   Rev 1.1   Sep 01 2003 21:21:06   popescu
//PET 809 FN 02, CIBC Multi fund enhancement
//
//   Rev 1.0   Aug 14 2003 15:50:42   popescu
//Initial revision.
 */

