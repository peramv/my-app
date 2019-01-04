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
// ^FILE   : JAcctTransProcessinclude.h
// ^AUTHOR : Yongmei Feng
// ^DATE   : 03/11/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0118_vw.hpp>
#include <ifastdataimpl\dse_dstc0118_req.hpp>

// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int ACCOUNT_INQUIRY_LIST = 1;
//CP20030319const int ACCOUNT_INQUIRY_LIST_DETAILS = 2;

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_INQUIRY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_INQUIRY_LIST_DETAILS;
}
namespace ACCINQUIRYLIT //entity search literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const FIRSTNAME;
   extern IFASTBP_LINKAGE const I_CHAR * const LASTNAME;
   extern IFASTBP_LINKAGE const I_CHAR * const SIN_NO;
   extern IFASTBP_LINKAGE const I_CHAR * const SHRNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNTNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ALTACCOUNTNUM;
   extern IFASTBP_LINKAGE const I_CHAR * const BROKERCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const BRANCHCODE;
   extern IFASTBP_LINKAGE const I_CHAR * const SLSREP;
   extern IFASTBP_LINKAGE const I_CHAR * const CORPINDIV;
   extern IFASTBP_LINKAGE const I_CHAR * const NEXTORPREVIOUS;
   extern IFASTBP_LINKAGE const I_CHAR * const NEXT_KEY;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountInquiryProcessIncludes.h-arc  $
//
//   Rev 1.5   Mar 21 2003 17:34:34   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:52:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:22:06   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:14:48   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Mar 18 2001 18:17:56   VASILEAD
//Fixes for UAT release
 * 
 *    Rev 1.6   Dec 14 2000 15:53:56   FENGYONG
 * remove #3
 * 
 */


