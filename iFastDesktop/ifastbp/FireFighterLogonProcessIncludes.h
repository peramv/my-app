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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0276_vw.hpp>
#include <ifastdataimpl\dse_dstc0276_req.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FIRE_FIGHTER_LOGON_INFO;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId FFDesc;
}  

namespace FIREFIGHTER  
{
	const BFFieldId IS_THE_SAME_VERSION(1000);
	const BFFieldId IS_ACCESSID_R(2000);
	const BFFieldId IS_ACCESSID_F(3000);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FireFighterLogonProcessIncludes.h-arc  $
//
//   Rev 1.3   Sep 12 2005 15:58:12   ZHANGCEL
//PET1235 - FN02 -- Apply same logic for FFID
//
//   Rev 1.2   Aug 22 2005 10:49:42   ZHANGCEL
//PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
//
//   Rev 1.1   Dec 11 2003 11:53:24   linmay
//added field IS_THE_SAME_VERSION
//
//   Rev 1.0   Dec 09 2003 09:03:32   linmay
//Initial Revision
//
*/
