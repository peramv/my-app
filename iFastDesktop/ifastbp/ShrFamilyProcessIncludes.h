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



//#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0233_vwrepeat_record.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FAMILY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER;
   extern IFASTBP_LINKAGE const BFContainerId FAMILY_CODE_LIST;
}
namespace SHR_FAMILY
{
//CP20030319   const int FAMILY_LIST   = 1;
//CP20030319   const int SHAREHOLDER   = 2;
}
namespace SHRFAMILYLIST
{
   //extern IFASTBP_LINKAGE const I_CHAR * const SHR_FAMILY;
   extern IFASTBP_LINKAGE const I_CHAR * const SHR_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AcctNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId FamilyCodeExist;
   
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFamilyProcessIncludes.h-arc  $
//
//   Rev 1.6   Nov 08 2011 11:53:16   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.5   Mar 21 2003 17:48:20   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Jan 15 2003 16:51:50   sanchez
//added extern CLASS_IMPORT const BFTextFieldId FamilyCodeExist;
//
//   Rev 1.3   Jan 14 2003 17:34:06   sanchez
//addd
////******************************************************************************
////              Revision Control Entries
////******************************************************************************
///* $Log:   Y:/VCS/BF iFAST/ifastcbo/MFAccount.cpp-arc  $
// * /
 */