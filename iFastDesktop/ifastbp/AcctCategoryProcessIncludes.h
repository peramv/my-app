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
// ^FILE   : AcctCategoryProcessIncludes.cpp
// ^AUTHOR :  Robert Kovacs
// ^DATE   : 01/22/2003
//
// -----------------------------------------------------------------------------


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0245_vwrepeat_record.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CATEGORY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
}
namespace ACCT_CATEGORY
{
//CP20030319   const int MFACCOUNT     = 1;
//CP20030319   const int CATEGORY_LIST = 2;

}
namespace ACCTCATEGORYLIST
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId AcctCategoryExist;
   extern CLASS_IMPORT const BFTextFieldId PaymentIdMethod;
   extern CLASS_IMPORT const BFTextFieldId AcctCategHeading;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFDateFieldId ModDate;

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctCategoryProcessIncludes.h-arc  $
//
//   Rev 1.2   Aug 09 2007 14:00:46   jankovii
//PET 2388 FN01 - Swift Payment Method ID.
//
//   Rev 1.1   Mar 21 2003 17:35:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 23 2003 17:02:06   KOVACSRO
//Initial revision.

 */