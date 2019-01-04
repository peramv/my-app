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
// ^FILE   : RESPTransactionsProcessIncludes.h
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/20/2000
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

#include <ifastdataimpl\dse_dstc0111_vw.hpp>
#include <ifastdataimpl\dse_dstc0111_req.hpp>
#include <ifastdataimpl\dse_dstc0111_req.hpp>
#include <ifastdataimpl\dse_dstc0410_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId GrantRepayablePurch;
   extern CLASS_IMPORT const BFTextFieldId RepHRDC;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId RESPTRANSACTIONS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RESP_CRITERIA;
}
namespace RESPTRANSACTIONSNAMES
{
   extern IFASTBP_LINKAGE const I_CHAR * const YES;
   extern IFASTBP_LINKAGE const I_CHAR * const NO;
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const HISTORY_PENDING_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const LAST_NAME_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const FIRST_NAME_FIELD;
   extern IFASTBP_LINKAGE const I_CHAR * const TRANSACTIONS_PENDING;
   extern IFASTBP_LINKAGE const I_CHAR * const HISTORY;
   extern IFASTBP_LINKAGE const I_CHAR * const PENDING;
}


// Need to define list and search ID's to be used by a GUI object talking to the
// process.
//CP20030319const int RESPTRANSACTIONS_LIST = 1;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPTransactionsProcessIncludes.h-arc  $
 * 
 *    Rev 1.10   Aug 06 2010 14:01:20   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.9   Jun 09 2010 15:11:08   jankovii
 * IN 2131626 - PETP0165541 -  Mapping Issues on the RESP Trans History Screen.
 * 
 *    Rev 1.8   May 11 2010 08:19:22   popescu
 * QESI - RESP Fixes
 * 
 *    Rev 1.7   Jul 25 2008 18:36:10   daechach
 * in#1089944 - iFast/Desktop RESP Transaction History Screen
 * 
 *    Rev 1.6   Mar 21 2003 17:47:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:53:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:20:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:14   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Mar 22 2000 09:02:38   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.3   Mar 02 2000 12:00:08   PETOLESC
// Corrected qa issues.
// 
//    Rev 1.2   Feb 16 2000 10:06:46   PETOLESC
// Included the list in MFAccount.
// 
//    Rev 1.1   Feb 07 2000 11:02:32   PETOLESC
// Minor corrections and code cleaning.
 * 
 *
 */

