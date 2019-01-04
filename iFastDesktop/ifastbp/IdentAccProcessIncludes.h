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
//    Copyright 2000 by DST Systems, Inc.
//    AUTHOR : Mihai Virgil Buzila
//    DATE   : 03 Feb 2000
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

//include the data sets
#include <ifastdataimpl\dse_substitute_vw.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_IDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId ENTITY_SEARCH_LIST;
   extern IFASTBP_LINKAGE const BFContainerId SEARCH_ACCOUNTS;
   extern IFASTBP_LINKAGE const BFContainerId SEARCH_INIT;
   extern IFASTBP_LINKAGE const BFContainerId SEARCH_MORE;
}
namespace IDENTACCPROC
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const CREATE_NEW_ACCOUNT;
   extern IFASTBP_LINKAGE const I_CHAR * const CREATE_NEW_SHAREHOLDER;
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_SYSTEMATIC;


//CP20030319   const int ENTITY_SEARCH_LIST = 1;
//CP20030319   const int ENTITY_IDS_LIST = 2;
//CP20030319   const int ACCOUNT_LIST = 3;
//CP20030319   const int SEARCH_INIT = 200;
//CP20030319   const int SEARCH_MORE = 201;
//CP20030319   const int SEARCH_ACCOUNTS = 202;

   const BFFieldId FIRST_VALUE(100);
   const BFFieldId SECOND_VALUE(101);
   const BFFieldId SEARCH_CODE(102);
   const BFFieldId ACC_HOLDER_KANA_NAME(103);
   const BFFieldId ACC_HOLDER_KANJI_NAME(104);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/IdentAccProcessIncludes.h-arc  $
 * 
 *    Rev 1.12   Mar 21 2003 17:41:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Mar 07 2003 15:01:04   PURDYECH
 * Fixed some bad container IDs
 * 
 *    Rev 1.10   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:52:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:20:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   19 Mar 2002 13:17:34   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.6   Aug 10 2001 14:07:48   YINGBAOL
 * disable NASU if it is lauched from Systematic and Allocation
 * 
 *    Rev 1.5   Oct 11 2000 14:19:36   KOVACSRO
 * Added CREATE_NEW_ACCOUNT and CREATE_NEW_SHAREHOLDER
 * 
 *    Rev 1.4   Mar 07 2000 15:45:02   POPESCUS
 * more work on the account search screen
 * 
 *    Rev 1.3   Mar 03 2000 19:33:58   POPESCUS
 * save the work
 * 
 *    Rev 1.2   Mar 03 2000 12:11:08   POPESCUS
 * account search work
 * 
 *    Rev 1.1   Feb 29 2000 15:37:00   BUZILA
 * changes
// 
*/
