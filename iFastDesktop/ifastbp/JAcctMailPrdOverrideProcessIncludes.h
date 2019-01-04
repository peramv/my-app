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
//
// ^FILE   : JAcctMailPrdOverrideProcessIncludes.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 29/09/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the API
//
//******************************************************************************


// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int ENTITY_LIST = 1;

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


namespace IFASTBP_PROC
{
  extern IFASTBP_LINKAGE const BFContainerId ACCT_MAILING_OVERRIDE_LIST;
  extern IFASTBP_LINKAGE const BFContainerId DECODE_ACCTID_CBO;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctMailPrdOverrideProcessIncludes.h-arc  $
//
//   Rev 1.0   Oct 24 2005 17:37:36   ZHANGCEL
//Initial revision.
//
 */

